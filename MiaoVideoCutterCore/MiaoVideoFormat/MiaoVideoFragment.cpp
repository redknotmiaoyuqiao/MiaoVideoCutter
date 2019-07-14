#include "MiaoVideoFormat.hpp"
#include "MiaoBase/Miao.hpp"
#include "MiaoVideoCodec/MiaoVideoCodec.hpp"

MiaoVideoFragment::MiaoVideoFragment(char * videoPath)
{
    miao_str_cpy(&this->videoPath,videoPath);
}

MiaoVideoFragment::~MiaoVideoFragment()
{
    this->Close();
    if(this->videoPath != NULL) {
        free(this->videoPath);
        this->videoPath = NULL;
    }
}

int MiaoVideoFragment::Open()
{
    if(this->videoPath == NULL) {
        return -1;
    }

    if (avformat_open_input(&pFormatCtx, this->videoPath, NULL, NULL) != 0) {
        return -1;
    }

    avformat_find_stream_info(pFormatCtx,0);
    av_dump_format(pFormatCtx, 0, this->videoPath, 0);

    return 0;
}

int MiaoVideoFragment::Close()
{
	if(pFormatCtx != NULL) {
        avformat_close_input(&pFormatCtx);
		avformat_free_context(pFormatCtx);
		pFormatCtx = NULL;
	}

    return 0;
}

int MiaoVideoFragment::GetStreamCount()
{
    if(this->pFormatCtx == NULL) {
        return -1;
    }

    return this->pFormatCtx->nb_streams;
}

int MiaoVideoFragment::GetVideoStreamInfo(int streamIndex, int * width, int * height)
{
    if(this->pFormatCtx == NULL) {
        return -1;
    }
    if(streamIndex >= this->pFormatCtx->nb_streams) {
        return -1;
    }
    if(streamIndex < 0){
        return -1;
    }

    AVStream * stream = this->pFormatCtx->streams[streamIndex];

    *width  = stream->codec->width;
    *height = stream->codec->height;

    return 0;
}

int MiaoVideoFragment::GetStreamType(int streamIndex)
{
    if(this->pFormatCtx == NULL) {
        return -1;
    }
    if(streamIndex >= this->pFormatCtx->nb_streams) {
        return -1;
    }
    if(streamIndex < 0){
        return -1;
    }

    AVStream * stream = this->pFormatCtx->streams[streamIndex];
    if(stream->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
        return STREAM_TYPE_VIDEO;
    }
    else if(stream->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
        return STREAM_TYPE_AUDIO;
    }
    else {
        return STREAM_TYPE_OTHER;
    }
    return STREAM_TYPE_UNKNOW;
}

int MiaoVideoFragment::GetFrameCount(int streamIndex)
{
    if(this->pFormatCtx == NULL) {
        return -1;
    }
    if(streamIndex >= this->pFormatCtx->nb_streams) {
        return -1;
    }
    if(streamIndex < 0){
        return -1;
    }

    AVStream * stream = this->pFormatCtx->streams[streamIndex];
    return stream->nb_frames;
}

int MiaoVideoFragment::GetFrameData(int streamIndex, int frameIndex)
{
    // printf("Frame Index: %d\n", frameIndex);

    AVPacket * pkt = av_packet_alloc();
    av_seek_frame(pFormatCtx, streamIndex, 0, AVSEEK_FLAG_FRAME);
    int index = 0;
    while(1){
        if(index > frameIndex){
            break;
        }
        int ret = av_read_frame(pFormatCtx, pkt);
        if(ret != 0){
            goto END;
        }
        index++;
    }
    // printf("PTS:%lld\n", pkt->pts);
END:
    av_packet_free(&pkt);
    return 0;
}

double MiaoVideoFragment::GetStreamDuration(int streamIndex)
{
    if(this->pFormatCtx == NULL) {
        return -1;
    }
    if(streamIndex >= this->pFormatCtx->nb_streams) {
        return -1;
    }
    if(streamIndex < 0){
        return -1;
    }

    AVStream * stream = this->pFormatCtx->streams[streamIndex];
    
    return stream->duration * av_q2d(stream->time_base);
}

int MiaoVideoFragment::GetFrameYUV(int streamIndex, double targetTime, int * width, int * height, unsigned char * * _yuvData, int * _yuvDataLen)
{
    if(this->pFormatCtx == NULL) {
        return -1;
    }
    if(streamIndex >= this->pFormatCtx->nb_streams) {
        return -1;
    }
    if(streamIndex < 0){
        return -1;
    }

    if(GetStreamType(streamIndex) != STREAM_TYPE_VIDEO){
        return -1;
    }

    AVStream * stream = this->pFormatCtx->streams[streamIndex];

    AVPacket * pkt = av_packet_alloc();

    MiaoVideoDecoder videoDecoder;

    int64_t k = (int64_t) (targetTime / av_q2d(stream->time_base)) + stream->start_time;
    av_seek_frame(pFormatCtx, streamIndex, k, AVSEEK_FLAG_BACKWARD);

    unsigned char * yuvData = NULL;
    int yuvDataLen = 0;

    while(1){
        int ret = av_read_frame(pFormatCtx, pkt);
        if(ret != 0){
            goto END;
        }
        if(pkt->stream_index == streamIndex){
            double time = pkt->pts * av_q2d(stream->time_base);
            if(time >= targetTime){
                *_yuvData = yuvData;
                *_yuvDataLen = yuvDataLen;
                goto END;
            }
            videoDecoder.DecodeSendFrame(stream, pkt);
            
            if(yuvData != NULL){
                free(yuvData);
                yuvData = NULL;
            }
            int ret = videoDecoder.DecodeRecvFrame(width, height, &yuvData, &yuvDataLen);
            if(ret){
            }
        }
    }

END:
    av_packet_free(&pkt);
    return 0;
}