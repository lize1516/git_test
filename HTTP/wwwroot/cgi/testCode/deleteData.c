#include<stdio.h>
#include "../../lib/include/mysql.h"
#include<stdlib.h>
#include<string.h>

void delete_data(char*name,char*num)
{
	MYSQL* mysql_fd=mysql_init(NULL);
    if(mysql_real_connect(mysql_fd,"127.0.0.1","root",\
                "xiong","25_class",3306,NULL,0)==NULL)
    {
       // printf("connect falied!\n");
        return;
    }
   // printf("connect mysql success!\n");
	
    char sql[1024];
    sprintf(sql,"delete from student_info where \
            name='%s' and num='%s'",name,num);
    mysql_query(mysql_fd,sql);
	mysql_close(mysql_fd);
	
	printf("<html>");
	printf("head");
		printf("<meta http-equiv=\"refresh\" content=\"0;http://118.25.216.111:7979/cgi/bin/select\">");
	printf("/head");
	printf("</html>");
}

int main()
{
	char data[1024];
	if(getenv("METHOD"))
	{
		if(strcasecmp("GET",getenv("METHOD"))==0)
		{
			strcpy(data,getenv("QUERY_STRING"));
		}
		else
		{
			int content_length=atoi(getenv("CONTENT_LENGTH"));
			int i=0;
			for(;i<content_length;i++)
			{
				read(0,data+i,1);
			}
			data[i]=0;
		}
	}
//	printf("arg:%s\n",data);
	
	char name[24];
	char num[12];

	strtok(data,"=&");
	strcpy(name,strtok(NULL,"=&"));
	strtok(NULL,"=&");
	strcpy(num,strtok(NULL,"=&"));
	
	delete_data(name,num);
	return 0;
}
