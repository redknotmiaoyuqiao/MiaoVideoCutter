#ifndef	MIAO_VIDEO_CUTTER_CORE_CODEC
#define	MIAO_VIDEO_CUTTER_CORE_CODEC

#include <stdio.h>

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
}

class MiaoVideoCodec;

class MiaoVideoCodec
{
private:
    AVCodecContext * codecCtx = NULL;
    AVCodec * videoCodec = NULL;
    AVFrame * pFrame = NULL;
public:
    MiaoVideoCodec();
    ~MiaoVideoCodec();

    int InitCodec();

    int DecodeFrame(unsigned char * rawData, int rawDataLen, uint64_t pts, uint64_t dts, unsigned char * * yuvData, int * yuvDataLen);
};

#endif