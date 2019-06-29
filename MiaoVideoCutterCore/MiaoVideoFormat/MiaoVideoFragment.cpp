#include "MiaoVideoFormat.hpp"
#include "MiaoBase/Miao.hpp"

MiaoVideoFragment::MiaoVideoFragment(char * videoPath)
{
    miao_str_cpy(&this->videoPath,videoPath);
}

MiaoVideoFragment::~MiaoVideoFragment()
{
    if(this->videoPath != NULL)
    {
        free(this->videoPath);
        this->videoPath = NULL;
    }
}

int MiaoVideoFragment::Open()
{
    return 0;
}

int MiaoVideoFragment::Close()
{
    return 0;
}

int MiaoVideoFragment::GetStreamCount()
{
    return 0;
}

int MiaoVideoFragment::GetStreamType(int streamIndex)
{
    return 0;
}

int MiaoVideoFragment::GetFrameCount(int streamIndex)
{
    return 0;
}