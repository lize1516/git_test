#include<stdio.h>
#include "../../lib/include/mysql.h"
#include<stdlib.h>
#include<string.h>

void insert_data(char*name,char* num,char*sex,char*phone)
{
 
	MYSQL* mysql_fd=mysql_init(NULL);
    if(mysql_real_connect(mysql_fd,"127.0.0.1","root",\
                "xiong","25_class",3306,NULL,0)==NULL)
	{	return;}
	
	char sql[1024];
   sprintf(sql,"insert into student_info(name,num,sex,phone) \
            values('%s','%s','%s','%s')",name,num,sex,phone);
    mysql_query(mysql_fd,sql);
	mysql_close(mysql_fd);



	printf("<html>");
	printf("<head>");
		printf("<meta http-equiv=\"refresh\" content=\"0;http://118.25.216.111:7979/cgi/bin/select\">");

	printf("</body>");
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
   // printf("arg:%s\n",data);
	
	char name[24];
	char num[12];
	char sex[9];
	char phone[16];

	strtok(data,"=&");
	strcpy(name,strtok(NULL,"=&"));
	strtok(NULL,"=&");
	strcpy(num,strtok(NULL,"=&"));
	strtok(NULL,"=&");
	strcpy(sex,strtok(NULL,"=&"));
	strtok(NULL,"=&");
	strcpy(phone,strtok(NULL,"=&"));
	
	insert_data(name,num,sex,phone);
	return 0;
}
