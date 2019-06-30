#include "MiaoVideoCodec.hpp"

MiaoVideoCodec::MiaoVideoCodec()
{
    videoCodec = avcodec_find_decoder(AV_CODEC_ID_H264);  
    codecCtx = avcodec_alloc_context3(videoCodec);
    pFrame = av_frame_alloc();
}

MiaoVideoCodec::~MiaoVideoCodec()
{
    // TODO 释放资源
}

int MiaoVideoCodec::InitCodec()
{
    avcodec_open2(codecCtx, videoCodec, NULL);
    return 0;
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