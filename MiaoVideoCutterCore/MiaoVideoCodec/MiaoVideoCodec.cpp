#include "MiaoVideoCodec.hpp"
#include "MiaoBase/MiaoDebug.hpp"

MiaoVideoCodec::MiaoVideoCodec()
{
    // videoCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
    // codecCtx = avcodec_alloc_context3(videoCodec);
    pFrame = av_frame_alloc();
}

MiaoVideoCodec::~MiaoVideoCodec()
{
    // TODO 释放资源
}

int MiaoVideoCodec::DecodeFrame(unsigned char * rawData, int rawDataLen, uint64_t pts, uint64_t dts, unsigned char * * yuvData, int * yuvDataLen)
{
    AVPacket packet = {0}; 
    av_init_packet(&packet);

    packet.data = (unsigned char *)rawData;
    packet.size = rawDataLen;

    int ret = avcodec_send_packet(codecCtx, &packet);
    if (ret < 0) {
        return -1;
    }

    while(avcodec_receive_frame(codecCtx, pFrame) == 0) {
        
    }

    return 0;
}

int MiaoVideoCodec::DecodeFrameFFmpeg(AVPacket * pkt, unsigned char * * yuvData, int * yuvDataLen)
{
    int ret = avcodec_send_packet(codecCtx, pkt);
    if (ret < 0) {
        return -1;
    }

    while(avcodec_receive_frame(codecCtx, pFrame) == 0) {

    }
    return 0;
}

int MiaoVideoCodec::DecodeFrameFFmpegSendFrame(AVStream * stream, AVPacket * pkt)
{
    if(videoCodec == NULL){
        videoCodec = avcodec_find_decoder(stream->codec->codec_id);
        codecCtx = stream->codec;
        int ret = avcodec_open2(codecCtx, videoCodec, NULL);
        RedLog("avcodec_open2 ret: %d\n", ret);
    }
    int ret = avcodec_send_packet(codecCtx, pkt);
    RedLog("avcodec_send_packet ret:%d\n",ret);
    return ret;
}

int MiaoVideoCodec::DecodeFrameFFmpegRecvFrame(int * width, int * height, unsigned char * * yuvData, int * yuvDataLen)
{
    int ret = avcodec_receive_frame(codecCtx, pFrame);
    //// RedLog("avcodec_receive_frame ret:%d\n",ret);
    if(ret == 0){
        *width = pFrame->width;
        *height = pFrame->height;
    }

    return ret;
}