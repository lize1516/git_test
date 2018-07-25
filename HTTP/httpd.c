#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<signal.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<errno.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

#define CHARMAX 1024
#define HOME_PAGE "index.html"

int startup(int port)
{
    int sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        perror("socket");
        exit(1);
    }
       
    int opt=1;    
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    addr.sin_port=htons(port);
   
    if(bind(sock,(struct sockaddr*)&addr,sizeof(addr))<0)
    {
        perror("bind");
        exit(2);
    }
    if(listen(sock,5)<0)
    {
        perror("listen");
        exit(3);
    }
    
    return sock;
}

int get_line(int sock,char* line,int size)
{
    char ch='c';
    int i=0;
    while(i<size-1&&ch!='\n')
    {
        int s=recv(sock,&ch,1,0);
        if(s>0)
        {       
            if(ch=='\r')
            {
                recv(sock,&ch,1,MSG_PEEK);
                if(ch=='\n')
                    recv(sock,&ch,1,0);
                else
                    ch='\n';
            }
            line[i++]=ch;
        }
        else
            break;
    }
    line[i]='\0';
    return i;
}

void clear_header(int sock)
{
    char line[CHARMAX];
    do{
        get_line(sock,line,CHARMAX);
    }while(strcmp(line,"\n"));
}

void show_404(int sock)
{
    clear_header(sock);
	char path[CHARMAX]="./wwwroot/404.html";
    int fd=open(path,O_RDONLY);
    
    struct stat st;
    stat(path,&st);
    
    char line[CHARMAX];
    sprintf(line,"HTTP/1.0 200 OK\r\n");
    send(sock,line,strlen(line),0);
    sprintf(line,"Content-Type:text/html;charset=ISO 10646:2003 Unicode 4.0\r\n");
    send(sock,line,strlen(line),0);
    sprintf(line,"\r\n");
    send(sock,line,strlen(line),0);

    sendfile(sock,fd,NULL,st.st_size);

}
void echo_error(int sock,int code)    //错误码处理
{
    switch(code)
    {
        case 403:
            break;
        case 404:
			show_404(sock);
            break;
        case 500:
            break;
        default:
            break;
    
    }

}

int echo_www(int sock,char* path,int len)
{
    clear_header(sock);
    int fd=open(path,O_RDONLY);
    if(fd<0)
        return 404;

    char line[CHARMAX];
    sprintf(line,"HTTP/1.0 200 OK\r\n");
    send(sock,line,strlen(line),0);
    sprintf(line,"Content-Type:text/html;charset=ISO 10646:2003 Unicode 4.0\r\n");
    send(sock,line,strlen(line),0);
    sprintf(line,"\r\n");
    send(sock,line,strlen(line),0);

    sendfile(sock,fd,NULL,len);
    return 200;
}

int exe_cgi(int sock,char path[],char method[],char*query_string)
{
    char line[CHARMAX];
    char method_env[CHARMAX];
    char query_string_env[CHARMAX];
    char content_length_env[CHARMAX/8];
    int content_length=0;
    if(strcasecmp(method,"GET")==0)
    {
        clear_header(sock);
    }
    else
    {
        //POST方法
        do{
            get_line(sock,line,CHARMAX);
            if(strncmp(line,"Content-Length: ",16)==0)
            {
                content_length=atoi(line+16);
            }
        }while(strcmp(line,"\n"));
        
        if(content_length==-1)
        {
            return 404;
        }
    }

    int input[2];
    int output[2];

    pipe(input);
    pipe(output);
    
   //signal(SIGPIPE,SIG_IGN);

    pid_t id=fork();
    if(id<0)
    {
        return 404;
    }
    else if(id==0)
    {

        close(input[1]);  //关闭写端
        close(output[0]); //关闭读端

        dup2(input[0],0);   //重定向
        dup2(output[1],1);

        sprintf(method_env,"METHOD=%s",method);
        putenv(method_env);
        if(strcasecmp(method,"GET")==0)
        {
            sprintf(query_string_env,"QUERY_STRING=%s",query_string);
            putenv(query_string_env);
        }
        else
        {
            //POST
            sprintf(content_length_env,"CONTENT_LENGTH=%d",content_length);
            putenv(content_length_env);
        }

        execl(path,path,NULL);     //path 路径   path 执行方式  NULL
        exit(1);
    }
    else
    {
        //father process

        close(input[0]);   //关闭读端
        close(output[1]);  //关闭写端

        
        char ch='c';
        if(strcasecmp(method,"POST")==0)
        {
            int i=0;
            for(;i<content_length;i++)
            {
                recv(sock,&ch,1,0);
                write(input[1],&ch,1);
            }
        }

        sprintf(line,"HTTP/1.0 200 OK\r\n");
        send(sock,line,strlen(line),0);
        sprintf(line,"Content-Type:text/html;charset=utf-8\r\n");
        send(sock,line,strlen(line),0);
        sprintf(line,"\r\n");
        send(sock,line,strlen(line),0);

        while(read(output[0],&ch,1)>0)
        {
            send(sock,&ch,1,0);
        } 

        waitpid(id,NULL,0);

        close(input[1]);
        close(output[0]);
    }
}

void* handler(void* arg)
{   
   // printf("nihao\n");
    int sock=(int)arg;
    char line[CHARMAX];
    char method[CHARMAX/32];
    char path[CHARMAX];
    char url[CHARMAX];
    int errCode=0;
    int cgi=0;
    char* query_string=NULL;
    
//////////////////////////测试查看报头
    /*do{
        get_line(sock,line,CHARMAX);
        printf("%s",line);
    }while(strcmp(line,"\n"));
    */
///////////////////////////////////
    get_line(sock,line,sizeof(line));
    int i=0;
    int j=0;
    while(i<sizeof(method)-1&&j<sizeof(line)&&!isspace(line[j]))
    {
        method[i++]=line[j++];
    }
    method[i]='\0';


    if(strcasecmp(method,"POST")&&strcasecmp(method,"GET"))
    {
        errCode=404;
        goto end;
    }
    
    while(j<sizeof(line)&&isspace(line[j])) //jump space
        j++;
    
    i=0;
    while(i<sizeof(url)-1&&j<sizeof(line)&&!isspace(line[j]))
    {
        url[i++]=line[j++];
    }
    url[i]='\0';
    
    if(strcasecmp(method,"GET")==0)
    {
        query_string=url;
        while(*query_string!='\0')
        {
            if(*query_string=='?')
            {
                *query_string='\0';
                query_string++;
                cgi=1;
                break;
            }
            query_string++;
        }
    }
    else
    {     //POST方法
        cgi=1;
    }

    sprintf(path,"wwwroot%s",url);      //url ----->path
    if(path[sizeof(path)-1]=='/')
    {
        strcat(path,HOME_PAGE);
    }
    
    //stat
    struct stat st;
    if(stat(path,&st)<0)
    {
        errCode=404;
        goto end;
    }
    else
    {
        if(S_ISDIR(st.st_mode))
        {
            strcat(path,HOME_PAGE);
        }
        else if(((st.st_mode&S_IXUSR)||\
                    (st.st_mode&S_IXGRP)||(st.st_mode&S_IXOTH)))
        {
            cgi=1;
        }
        if(cgi)
        {
            //printf("dahaizi\n");   //测试
            exe_cgi(sock,path,method,query_string);
        }
        else
        {
            //path 
            errCode=echo_www(sock,path,st.st_size);
        }
    
    }


end:
    if(errCode!=200)
    {
        echo_error(sock,errCode);
    }
    close(sock);
}

int main(int argc,char* argv[])
{
   // daemon(1,1);  将进程变成守护进程

    if(argc!=2)
    {
        printf("Usage: \n\t%s [port]\n",argv[0]);
        return 404;
    }
    int listen_sock=startup(atoi(argv[1]));   
    signal(SIGPIPE,SIG_IGN);    //或略SIGPIPE

    for(;;)
    {
        struct sockaddr_in client;
        socklen_t len=sizeof(client);
        int client_sock=accept(listen_sock,(struct sockaddr*)&client,&len);

        if(client_sock<0)
        {
            perror("accept");
            continue;
        } 
           
        pthread_t tid;
        pthread_create(&tid,NULL,handler,(void*)client_sock);
        pthread_detach(tid);
    }
    return 0;
}

