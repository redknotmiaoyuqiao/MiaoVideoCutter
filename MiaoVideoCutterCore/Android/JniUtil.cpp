#include "JniUtil.hpp"

#include <string.h>

char * jstringToChar(JNIEnv * env, jstring jstr) {
    char* pStr = NULL;

    jclass     jstrObj   = env->FindClass("java/lang/String");
    jstring    encode    = env->NewStringUTF("utf-8");
    jmethodID  methodId  = env->GetMethodID(jstrObj, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray byteArray = (jbyteArray)(env)->CallObjectMethod(jstr, methodId, encode);
    jsize      strLen    = env->GetArrayLength(byteArray);
    jbyte      *jBuf     = env->GetByteArrayElements(byteArray, JNI_FALSE);

    pStr = (char*)malloc(strLen + 1);
    if (!pStr) {
        return NULL;
    }
    memcpy(pStr, jBuf, strLen);
    pStr[strLen] = 0;


    env->ReleaseByteArrayElements(byteArray, jBuf, 0);

    return pStr;
}