#include<stdio.h>
#include "../../lib/include/mysql.h"
#include<stdlib.h>
#include<string.h>

void select_data( )
{
	MYSQL* mysql_fd=mysql_init(NULL);
    if(mysql_real_connect(mysql_fd,"127.0.0.1","root",\
                "xiong","25_class",3306,NULL,0)==NULL)
    {
        printf("connect falied!\n");
        return;
    }
    //printf("connect mysql success!\n");   //测试代码
	
    char sql[1024];
    sprintf(sql,"select *from student_info"); 
   
    mysql_query(mysql_fd,sql);
    
   MYSQL_RES* res=mysql_store_result(mysql_fd); 
   int row=mysql_num_rows(res);
   int col=mysql_num_fields(res);
   MYSQL_FIELD* field=mysql_fetch_fields(res);

   printf("<html>\n");
   printf("<head>\n");
   printf("<meta charset=\"UTF-8\">\n"); 
	   printf("<title> 查看信息网页</title>");
	   printf("<style>");
	   printf("body{text-align:center}");
	   printf("</style>");
   printf("</head>\n");

  printf(" <body style=\"background-color:PowderBlue;\"> \n");
  printf("<h1> 人员信息表</h1>");
  printf("<table border=\"1\" align=\"center\" cellpadding=\"10\">\n");

    int i=0;
    printf("<tr>\n");
    for(;i<col;i++)
    {
        printf("<td>%s</td>",field[i].name);
    }
    printf("</tr>\n");
    for(i=0;i<row;i++)
    {
        MYSQL_ROW rowData=mysql_fetch_row(res);
        int j=0;
        printf("<tr>\n");
        for(;j<col;j++)
        {
            printf("<td>%s</td>",rowData[j]);
        }
        printf("</tr>\n");
    }
    printf("</table>\n");

	printf("<br>");
    printf("<div>");
	printf("<p> <a href=\"http://118.25.216.111:7979/\"> <input type=\"image\" src=\"/imag/back.jpg\" onmousemove=\"this.src='/imag/back.jpg'\" onmouseout=\"this.src='/imag/back.jpg'\" style=\"width:50px;height:45px\"> </a></p>");
	printf("</div>");
	
    printf("</body>\n");
    printf("</html>\n");

	mysql_close(mysql_fd);
}

int main()
{
	
	select_data();
	return 0;
}
