#include "YuvSet.hpp"
#include <stdlib.h>
#include <string.h>
#include "MiaoBase/MiaoDebug.hpp"

YuvSet::YuvSet(int width, int height, int type, unsigned char * data, int dataLen)
{
    this->width     = width;
    this->height    = height;
    this->type      = type;
    this->dataLen   = dataLen;
    this->data      = (unsigned char *)malloc(this->dataLen * sizeof(unsigned char));

    memcpy(data, this->data, dataLen);
}

YuvSet::~YuvSet()
{
    if(this->data == NULL){
        free(this->data);
        this->data = NULL;
    }
}