#include "MiaoVideoFormat.hpp"
#include "MiaoBase/Miao.hpp"

MiaoAVLoader::MiaoAVLoader(char * filePath)
{
    miao_str_cpy(&this->filePath,filePath);
}

MiaoAVLoader::~MiaoAVLoader()
{
    if(this->filePath != NULL)
    {
        free(this->filePath);
        this->filePath = NULL;
    }
}

int MiaoAVLoader::Open()
{
    if(this->filePath == NULL)
    {
        return -1;
    }

    if (avformat_open_input(&pFormatCtx, this->filePath, NULL, NULL) != 0) 
    {
        return -1;
    }

    avformat_find_stream_info(pFormatCtx,0);

    av_dump_format(pFormatCtx, 0, this->filePath, 0);

    return 0;
}

int MiaoAVLoader::GetStreamsNum()
{
    if(this->pFormatCtx == NULL)
    {
        return -1;
    }

    return this->pFormatCtx->nb_streams;
}

int MiaoAVLoader::GetExtradata(int streamIndex)
{
    AVStream * avstream = pFormatCtx->streams[streamIndex];
    int type, codec;
    int ret = GetStreamsTypeCodec(streamIndex, &type, &codec);
    if(ret){
        return -1;
    }

    if(type == STREAM_TYPE_VIDEO){
        if(codec == STREAM_CODEC_H264){
            // Get Sps and PPS
            int spsLength = avstream->codec->extradata[6] * 0xFF + avstream->codec->extradata[7];  
            int ppsLength = avstream->codec->extradata[8 + spsLength + 1] * 0xFF + avstream->codec->extradata[8 + spsLength + 2];

            uint8_t * sps = (uint8_t *)malloc(spsLength * sizeof(char));
            uint8_t * pps = (uint8_t *)malloc(ppsLength * sizeof(char));

            printf("SpsLen:%d\n",spsLength);
            printf("PPSLen:%d\n",ppsLength);
            for (int i=0;i<spsLength;i++)  
            {  
                sps[i] = avstream->codec->extradata[i + 8];
            }
            
            for (int i=0;i<ppsLength;i++)  
            {  
                pps[i] = avstream->codec->extradata[i + 8 + 2 + 1 + spsLength];
            }

            printf("Sps Type:%d\n", sps[0] & 31);
            printf("Pps Type:%d\n", pps[0] & 31);

            free(sps);
            free(pps);
        }
    }

    return 0;
}

int MiaoAVLoader::GetStreamsTypeCodec(int streamIndex, int * type, int * codec)
{
    if(pFormatCtx->streams[streamIndex]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
        *type = STREAM_TYPE_VIDEO;
        if(pFormatCtx->streams[streamIndex]->codec->codec_id == AV_CODEC_ID_H264) {
            *codec = STREAM_CODEC_H264;
        }
        else {
            *codec = STREAM_CODEC_UNKNOW;
        }
    }
    else if(pFormatCtx->streams[streamIndex]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
        *type = STREAM_TYPE_AUDIO;
        *codec = STREAM_CODEC_UNKNOW;
    }
    else {
        *type = STREAM_TYPE_OTHER;
        *codec = STREAM_CODEC_UNKNOW;
    }
    return 0;
}

int MiaoAVLoader::ReadFrame()
{
    AVPacket pkt = {0};
    int ret = av_read_frame(pFormatCtx,&pkt);

    if(!ret) {
        int64_t pts = pkt.pts;
        int streamIndex = pkt.stream_index;
    
        if(pFormatCtx->streams[streamIndex]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            // printf("Stream Index : %d\n", streamIndex);
            // printf("Pts : %ld\n",pts);
            uint8_t * data = pkt.data;
            int data_len = pkt.size;
        }
    }

    return ret;
}