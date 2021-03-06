#ifndef	MIAO_VIDEO_CUTTER_CORE_CODEC
#define	MIAO_VIDEO_CUTTER_CORE_CODEC

#include <stdio.h>

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
}

class MiaoVideoCodec;
class MiaoVideoDecoder;

class MiaoCodecCtx
{

};

class MiaoVideoDecoder
{
private:
    AVCodecContext * codecCtx = NULL;
    AVCodec * videoCodec = NULL;
    AVFrame * pFrame = NULL;
public:
    MiaoVideoDecoder();
    ~MiaoVideoDecoder();

    int DecodeSendFrame(AVStream * stream, AVPacket * pkt);
    int DecodeRecvFrame(int * width, int * height, unsigned char * * yuvData, int * yuvDataLen);
};



class MiaoVideoCodec
{
private:
    AVCodecContext * codecCtx = NULL;
    AVCodec * videoCodec = NULL;
    AVFrame * pFrame = NULL;
public:
    MiaoVideoCodec();
    ~MiaoVideoCodec();



    int DecodeFrame(unsigned char * rawData, int rawDataLen, uint64_t pts, uint64_t dts, unsigned char * * yuvData, int * yuvDataLen);

    int DecodeFrameFFmpeg(AVPacket * pkt, unsigned char * * yuvData, int * yuvDataLen);
    int DecodeFrameFFmpegSendFrame(AVStream * stream, AVPacket * pkt);
    int DecodeFrameFFmpegRecvFrame(int * width, int * height, unsigned char * * yuvData, int * yuvDataLen);
};

#endif