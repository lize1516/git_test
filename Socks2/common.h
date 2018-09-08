#ifndef __COMMON_H__
#define __COMMON_H__

#include<stdio.h>
#include<stdarg.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<assert.h>
#include<map>
#include<iostream>
using namespace std;

#include<sys/types.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>
#include<netdb.h>
#include<fcntl.h>

#define __TRACE__
#define __DEBUG__

static string GetFileName(const string& path)
{
	char ch='/';
#ifdef _WIN32
	ch='\\';
#endif
	size_t pos=path.rfind(ch);
	if(pos==string::npos)           //static const size_t npos= -1;
		return path;
	else
		return path.substr(pos+1);
}

inline static void __TraceDebug(const char* filename,int line,const char* function,const char* format, ...)
{
#ifdef __TRACE__
	
	fprintf(stdout,"[TRACE][%s]-[%d]-[%s]:",GetFileName(filename).c_str(),line,function);
	va_list args;
	va_start(args,format);
	vfprintf(stdout,format,args);
	va_end(args);
	fprintf(stdout,"\n");
#endif
}

inline static void __ErrorDebug(const char* filename,int line,const char* function,const char* format, ...)
{
#ifdef __DEBUG__
	
	fprintf(stdout,"[ERROR][%s]-[%d]-[%s]:",GetFileName(filename).c_str(),line,function);

	va_list args;
	va_start(args,format);
	vfprintf(stdout,format,args);
	va_end(args);

	fprintf(stdout," errmsg:%s,errno:%d \n",strerror(errno),errno);
#endif
}

#define TraceLog(...) \
	__TraceDebug(__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__);

#define ErrorLog(...) \
	__ErrorDebug(__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__);

#endif   //__COMMON_H__

