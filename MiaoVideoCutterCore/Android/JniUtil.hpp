#ifndef	MIAO_VIDEO_CUTTER_CORE_JNI_UTIL
#define	MIAO_VIDEO_CUTTER_CORE_JNI_UTIL

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <jni.h>

#ifdef	__cplusplus
extern	"C" {
#endif

char * jstringToChar(JNIEnv * env, jstring jstr);

#ifdef	__cplusplus
}
#endif

#endif