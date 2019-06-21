#include "MiaoVideoFormat.hpp"
#include "MiaoBase/Miao.hpp"

extern "C" {
    #include <libavformat/avformat.h>
}

MiaoAVLoader::MiaoAVLoader(char * filePath)
{
    av_register_all();
    miao_str_cpy(&this->filePath,filePath);
}

MiaoAVLoader::~MiaoAVLoader()
{
    if(this->filePath != NULL){
        free(this->filePath);
        this->filePath = NULL;
    }
}