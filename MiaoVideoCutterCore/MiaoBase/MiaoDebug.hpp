#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>

#ifdef __ANDROID__
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3platform.h>
#else
#include <glad/glad.h>
#endif

#ifdef __ANDROID__
#include <android/log.h>
#define LOG_TAG "Miao Video Cutter"
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define RedLog(format, ...) LOG_ERROR(format, ##__VA_ARGS__)
#define BaseRedLog(format, ...) LOG_ERROR(format, ##__VA_ARGS__)

#else

#define RedLog(format, ...) RedPrintf(__FILE__, __FUNCTION__ ,__LINE__,format, ##__VA_ARGS__)
#define BaseRedLog(format, ...) printf(format, ##__VA_ARGS__)

#endif

#define glCheckError() glCheckError_(__FILE__, __LINE__)


static void RedPrintf(const char *file, const char *function,int line,char * format,...)
{
    BaseRedLog("\033[;31m%s (%d) \033[0m",file,line);

    va_list ap;
    char *p;
    char *sval;
    int ival;
    double dval;
    va_start(ap,format);

    for(p=format;*p;p++)
    {
        if(*p!='%')
        {
            BaseRedLog("%c", *p);
            continue;
        }
        switch(*++p)
        {
            case 'd':
                ival=va_arg(ap,int);
                BaseRedLog("%d",ival);
                break;
            case 'f':
                dval=va_arg(ap,double);
                BaseRedLog("%f",dval);
                break;
            case 's':
                sval=va_arg(ap,char *);
                BaseRedLog("%s",sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);  //结束时清理工作
    BaseRedLog("\n");
}