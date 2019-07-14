#ifndef	MIAO_VIDEO_CUTTER_CORE_ANDROID_YUV_SET
#define	MIAO_VIDEO_CUTTER_CORE_ANDROID_YUV_SET

#include <stdlib.h>
#include <stdio.h>

#define YUV_TYPE_420P 0x1

class YuvSet
{
private:
    int width = 0;
    int height = 0;
    int type = 0;
    unsigned char * data = NULL;
    int dataLen = 0;
    
public:
    YuvSet(int width, int height, int type, unsigned char * data, int dataLen);
    ~YuvSet();
};

#endif