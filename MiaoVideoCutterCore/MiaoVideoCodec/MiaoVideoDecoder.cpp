#include "MiaoVideoCodec.hpp"

MiaoVideoDecoder::MiaoVideoDecoder()
{
    pFrame = av_frame_alloc();
}

MiaoVideoDecoder::~MiaoVideoDecoder()
{

}

int MiaoVideoDecoder::DecodeSendFrame(AVStream * stream, AVPacket * pkt)
{
    if(videoCodec == NULL){
        videoCodec = avcodec_find_decoder(stream->codec->codec_id);
        codecCtx = stream->codec;
        int ret = avcodec_open2(codecCtx, videoCodec, NULL);
    }
    int ret = avcodec_send_packet(codecCtx, pkt);
    return ret;
}

int MiaoVideoDecoder::DecodeRecvFrame(int * _width, int * _height, unsigned char * * _yuvData, int * _yuvDataLen)
{
    int ret = avcodec_receive_frame(codecCtx, pFrame);
    if(ret == 0){
        *_width = pFrame->width;
        *_height = pFrame->height;

        int width = pFrame->width;
        int height = pFrame->height;

        int picSize = width * height;
        int newSize = picSize * 1.5;

        unsigned char * buf = (unsigned char *)malloc(newSize);

        int a=0,i;
        for (i=0; i<height; i++)
        {
            memcpy(buf+a,pFrame->data[0] + i * pFrame->linesize[0], width);
            a+=width;
        }
        for (i=0; i<height/2; i++)
        {
            memcpy(buf+a,pFrame->data[1] + i * pFrame->linesize[1], width/2);
            a+=width/2;
        }
        for (i=0; i<height/2; i++)
        {
            memcpy(buf+a,pFrame->data[2] + i * pFrame->linesize[2], width/2);
            a+=width/2;
        }

        int yuvDataLen = newSize;

        unsigned char * y = buf;
        int y_length = width * height;
        unsigned char * v = buf + y_length;
        int v_length = y_length / 4;
        unsigned char * u = buf + y_length + v_length;
        int u_length = y_length / 4;

        unsigned char * yuvpData = (unsigned char *)malloc(yuvDataLen);
        memcpy(yuvpData, y, y_length);
        memcpy(yuvpData + y_length,u,u_length);
        memcpy(yuvpData + y_length + u_length,v,v_length);

        *_yuvData = yuvpData;
        *_yuvDataLen = newSize;

        free(buf);
    }
    return ret;
}