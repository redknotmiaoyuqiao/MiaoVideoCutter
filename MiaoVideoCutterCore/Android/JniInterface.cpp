#include "com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI.h"

#include <stdio.h>
#include <string.h>
#include <string>

jstring charTojstring(JNIEnv * env, const char * pat);

JNIEXPORT jstring JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_get_1core_1version
  (JNIEnv * env, jclass)
{
    return env->NewStringUTF("l.0.0");
}

jstring charTojstring(JNIEnv * env, const char * pat)
{
    jclass strClass = (env)->FindClass("Ljava/lang/String;");
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = (env)->NewByteArray(strlen(pat));
    (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
    jstring encoding = (env)->NewStringUTF("UTF-8");
    return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
}