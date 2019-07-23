#include "com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI.h"
#include "JniUtil.hpp"
#include "MiaoVideoFormat/MiaoVideoFormat.hpp"
#include "MiaoBase/MiaoDebug.hpp"
#include "YuvSet.hpp"
#include <string.h>

JNIEXPORT jlong JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1GetFrameYUV
(JNIEnv *, jclass, jlong _miaoVideoFragment, jint stream_index, jdouble time)
{
    MiaoVideoFragment * miaoVideoFragment = (MiaoVideoFragment *)_miaoVideoFragment;
    if(miaoVideoFragment == NULL){
        return NULL;
    }

    int width = 0;
    int height = 0;
    unsigned char * yuvData = NULL;
    int yuvDataLen = 0;
    int ret = miaoVideoFragment->GetFrameYUV(stream_index, time, &width, &height, &yuvData, &yuvDataLen);

    if(ret){
        return NULL;
    }

    YuvSet * yuvSet = new YuvSet(width, height, YUV_TYPE_420P, yuvData, yuvDataLen);

    if(yuvData != NULL){
        free(yuvData);
        yuvData = NULL;
    }

    return (jlong)yuvSet;
}


JNIEXPORT jintArray JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1GetRGBA8888
(JNIEnv * env, jclass, jlong _yuvSet)
{
    YuvSet * yuvSet = (YuvSet *)_yuvSet;

    int rgbaBufLen = 1280 * 720 * 4;
    unsigned char * rgbaBuf = (unsigned char *)malloc(rgbaBufLen * sizeof(unsigned char));

    int rgbaIntDataLen = rgbaBufLen / 4;
    int * rgbaIntData = (int *)rgbaBuf;
    for(int i=0;i<rgbaIntDataLen;i++){
        rgbaIntData[i] = 0xFF0000FF;
    }

    jintArray jarray = env->NewIntArray(rgbaIntDataLen);
    env->SetIntArrayRegion(jarray, 0, rgbaIntDataLen, (jint *)rgbaIntData);
    free(rgbaBuf);

    return jarray;
}


JNIEXPORT jint JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1YuvUninit
(JNIEnv *, jclass, jlong _yuvSet)
{
    YuvSet * yuvSet = (YuvSet *)_yuvSet;
    if(yuvSet != NULL){
        delete yuvSet;
        yuvSet = NULL;
    }
    return 0;
}
