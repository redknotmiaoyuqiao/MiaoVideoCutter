#include "com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI.h"
#include "JniUtil.hpp"
#include "MiaoVideoFormat/MiaoVideoFormat.hpp"
#include "MiaoBase/MiaoDebug.hpp"
#include "YuvSet.hpp"

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

    // int ret = 0;
    // yuvDataLen = 1280 * 720 * 1.5;
    // yuvData = (unsigned char *) malloc(yuvDataLen);

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


JNIEXPORT jbyteArray JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1GetYuvFrame
(JNIEnv *, jclass, jlong)
{

}


JNIEXPORT jbyteArray JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1GetYuvFrameScale
(JNIEnv *, jclass, jlong, jint, jint)
{

}


JNIEXPORT jbyteArray JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1GetRGB565Frame
(JNIEnv *, jclass, jlong, jint, jint)
{

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
