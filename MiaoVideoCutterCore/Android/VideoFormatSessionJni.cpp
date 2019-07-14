#include "com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI.h"
#include "JniUtil.hpp"
#include "MiaoVideoFormat/MiaoVideoFormat.hpp"
#include "MiaoBase/MiaoDebug.hpp"

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


JNIEXPORT jdouble JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1GetStreamDuration
(JNIEnv *, jclass, jlong _miaoVideoFragment, jint stream_index)
{
    MiaoVideoFragment * miaoVideoFragment = (MiaoVideoFragment *)_miaoVideoFragment;
    if(miaoVideoFragment == NULL){
        return -1;
    }

    return miaoVideoFragment->GetStreamDuration(stream_index);
}


JNIEXPORT jint JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1GetStreamWidth
(JNIEnv *, jclass, jlong _miaoVideoFragment, jint stream_index)
{
    MiaoVideoFragment * miaoVideoFragment = (MiaoVideoFragment *)_miaoVideoFragment;
    if(miaoVideoFragment == NULL){
        return -1;
    }

    int width = 0;
    int height = 0;

    int ret = miaoVideoFragment->GetVideoStreamInfo(stream_index, &width, &height);
    if(ret){
        return -1;
    }

    return width;
}

JNIEXPORT jint JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1GetStreamHeight
(JNIEnv *, jclass, jlong _miaoVideoFragment, jint stream_index)
{
    MiaoVideoFragment * miaoVideoFragment = (MiaoVideoFragment *)_miaoVideoFragment;
    if(miaoVideoFragment == NULL){
        return -1;
    }

    int width = 0;
    int height = 0;

    int ret = miaoVideoFragment->GetVideoStreamInfo(stream_index, &width, &height);
    if(ret){
        return -1;
    }

    return height;
}


JNIEXPORT void JNICALL Java_com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI_video_1format_1session_1demo
(JNIEnv * env, jclass, jstring videoPath)
{
    char * videoPathStr = jstringToChar(env, videoPath);

    RedLog("Video Path : %s\n", videoPathStr);
    AVFormatContext *           ic          = NULL;
    AVCodec *                   c           = NULL;
    AVCodecContext *            cc          = NULL;
    AVPacket *                  pkt         = NULL;
    AVFrame *                   frame       = NULL;

    ic = avformat_alloc_context();
    if(avformat_open_input(&ic, videoPathStr, 0, 0) < 0){
        RedLog("Open Input Error\n");
        return;
    }
    RedLog("Open Input Success\n");

    int st_idx = -1;

    for(int i=0; i<ic->nb_streams; ++i){
        if(ic->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
            st_idx= i;
            break;
        }
    }
    if(-1 == st_idx){
        avformat_close_input(&ic);
        return;
    }

    avformat_find_stream_info(ic, 0);
    av_dump_format(ic, 0, "", 0);

    av_dump_format(ic, 0, videoPathStr, 0);

    c       = avcodec_find_decoder((AVCodecID)ic->streams[st_idx]->codecpar->codec_id);
    cc      = ic->streams[st_idx]->codec;
    if(avcodec_open2(cc, c, 0) <0){
        RedLog("Open Codec Error\n");
        return;
    }


    frame = av_frame_alloc();
    AVFrame * frameYUV = av_frame_alloc();

    int got_pict = 0;

    pkt = av_packet_alloc();
    while(av_read_frame(ic, pkt) >=0) {
        if (pkt->stream_index == st_idx) {
            RedLog("PTS:%lld\n", pkt->pts);
            RedLog("DTS:%lld\n", pkt->dts);

            int ret = avcodec_decode_video2(cc, frame, &got_pict, pkt);
            RedLog("Ret:%d\n",ret);
            if (ret >= 0) {
                RedLog("Decode !!!!!!!!\n");
                if (got_pict) {
                    RedLog("Decode Success\n");
                }
            }
        }
    }
    free(videoPathStr);
}