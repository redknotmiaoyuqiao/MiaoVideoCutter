#include "com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI.h"
#include "JniUtil.hpp"
#include "MiaoVideoFormat/MiaoVideoFormat.hpp"

JNIEXPORT jlong JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1init
(JNIEnv * env, jclass, jstring videoPath)
{
    char * videoPathStr = jstringToChar(env, videoPath);

    MiaoVideoFragment * miaoVideoFragment = new MiaoVideoFragment(videoPathStr);
    miaoVideoFragment->Open();

    free(videoPathStr);
    return (jlong)miaoVideoFragment;
}

JNIEXPORT jint JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1uninit
(JNIEnv *, jclass, jlong _miaoVideoFragment)
{
    MiaoVideoFragment * miaoVideoFragment = (MiaoVideoFragment *)_miaoVideoFragment;
    if(miaoVideoFragment == NULL){
        return -1;
    }
    miaoVideoFragment->Close();
    delete miaoVideoFragment;
    miaoVideoFragment = NULL;

    return 0;
}


JNIEXPORT jint JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1GetStreamCount
(JNIEnv *, jclass, jlong _miaoVideoFragment)
{
    MiaoVideoFragment * miaoVideoFragment = (MiaoVideoFragment *)_miaoVideoFragment;
    if(miaoVideoFragment == NULL){
        return -1;
    }

    return miaoVideoFragment->GetStreamCount();;
}


JNIEXPORT jint JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1GetStreamType
(JNIEnv *, jclass, jlong _miaoVideoFragment, jint stream_index)
{
    MiaoVideoFragment * miaoVideoFragment = (MiaoVideoFragment *)_miaoVideoFragment;
    if(miaoVideoFragment == NULL){
        return -1;
    }
    return miaoVideoFragment->GetStreamType(stream_index);
}


JNIEXPORT jint JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1GetFrameCount
(JNIEnv *, jclass, jlong)
{
    return 0;
}