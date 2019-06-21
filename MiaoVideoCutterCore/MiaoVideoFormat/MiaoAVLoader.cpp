#include "MiaoVideoFormat.hpp"
#include "MiaoBase/Miao.hpp"
#include "MiaoVideoFormat/MiaoExtradata.hpp"

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

	Close();
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
	
	MiaoExtradata * miao = MiaoExtradataFactory::GetMiaoExtradata(type, codec);
	if (miao != NULL) {
		ret = miao->GetExtradata(avstream->codec->extradata, avstream->codec->extradata_size, NULL, NULL);
		delete miao;
	}

    return ret;
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

int MiaoAVLoader::Close()
{
	avformat_close_input(&pFormatCtx);

	if(pFormatCtx != NULL){
		avformat_free_context(pFormatCtx);
		pFormatCtx = NULL;
	}
	
	return 0;
}