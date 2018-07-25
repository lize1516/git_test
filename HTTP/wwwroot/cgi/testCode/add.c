#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

void cal(char* data)
{
   // printf("%s\n",data);
    int d1,d2;
    sscanf(data,"num1=%d&num2=%d",&d1,&d2);

    printf("<html>\n");
	printf("<head>");
	 //<meta http-equiv="refresh" content="10; 这里加入要跳转的页面的地址 ">
	 
	printf("<meta charset=\"UTF-8\">");
	   printf("<title> 简单计算器</title>");
	   printf("<style>");
	   printf("body{text-align:center}");
	   printf("</style>");
	printf("</head>");
    printf(" <body style=\"background-color:PowderBlue;\"> ");
	printf("<h4> 简单的计算器 </h4>");
	printf("<table border=\"1\" align=\"center\" cellpadding=\"10\" width=\"400px\" height=\"300px\">"); //bordercolor="blue"
	printf("<tr> <td>%d</td> <td> + </td> <td>%d</td> <td>=</td> <td>%d</td> </tr>",d1,d2,d1+d2);
	printf("<tr> <td>%d</td> <td> + </td> <td>%d</td> <td>=</td> <td>%d</td> </tr>",d1,d2,d1-d2);
	printf("<tr> <td>%d</td> <td> + </td> <td>%d</td> <td>=</td> <td>%d</td> </tr>",d1,d2,d1*d2);
	printf("<tr> <td>%d</td> <td> + </td> <td>%d</td> <td>=</td> <td>%d</td> </tr>",d1,d2,d1/d2);
	printf("<tr> <td>%d</td> <td> + </td> <td>%d</td> <td>=</td> <td>%d</td> </tr>",d1,d2,d1%d2);
	printf("</table>");
	
	printf("<br>");
    printf("<div>");
	printf("<p> <a href=\"http://118.25.216.111:7979/\"> <input type=\"image\" src=\"/imag/back.jpg\" onmousemove=\"this.src='/imag/back.jpg'\" onmouseout=\"this.src='/imag/back.jpg'\" style=\"width:50px;height:45px\"> </a></p>");
	printf("</div>");

	printf("</body>");
    printf("</html>\n");
}

int main()
{
    char method[32];
    char buff[1024];

    if(getenv("METHOD")!=NULL)
    {
        strcpy(method,getenv("METHOD"));
        if(strcasecmp(method,"GET")==0)
        {
            strcpy(buff,getenv("QUERY_STRING"));
           // printf("%s\n",buff);
        }
        else if(strcasecmp(method,"POST")==0)
        {
            int content_len=atoi(getenv("CONTENT_LENGTH"));
            char ch;
            int i=0;
            for(;i<content_len;i++)
            {
                read(0,&ch,1);
                buff[i]=ch;
            }
            buff[i]='\0';
        }
        else
        {
            return 404;
        }
    
        cal(buff);
        return 200;
    }
    return 404;
}
