#ifndef	MIAO_VIDEO_CUTTER_CORE_FORMAT
#define	MIAO_VIDEO_CUTTER_CORE_FORMAT

#define STREAM_TYPE_VIDEO 0x1
#define STREAM_TYPE_AUDIO 0x2
#define STREAM_TYPE_OTHER 0x0
#define STREAM_TYPE_UNKNOW -0x01

#define STREAM_CODEC_H264 0x1
#define STREAM_CODEC_UNKNOW 0x0

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
}

class MiaoFormatIO;
class MiaoFormatOutput;
class MiaoFormatInput;
class MiaoVideoFrameHead;
class MiaoAVLoader;
class MiaoVideoFragment;

// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct MiaoVideoFrameHead
{
    int8_t frameHead[4];
    int8_t frameType;
    uint64_t pts;
    uint64_t dts;
    uint32_t frameDataLen; 
} MiaoVideoFileHead;

// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

class MiaoVideoFragment
{
private:
    char * videoPath = NULL;
    AVFormatContext * pFormatCtx = NULL;
public:
    MiaoVideoFragment(char * videoPath);
    ~MiaoVideoFragment();

    int             Open();
    int             Close();

    int             GetStreamCount();
    int             GetStreamType(int streamIndex);
    int             GetFrameCount(int streamIndex);
    double          GetStreamDuration(int streamIndex);
    
    int             GetFrameData(int streamIndex, int frameIndex);

    int             GetFrameYUV(int streamIndex, double time, int * width, int * height, unsigned char * * yuvData, int * yuvDataLen);
};

class MiaoFormatIO
{
public:
    char * filePath = NULL;
    FILE * file = NULL;
public:
    MiaoFormatIO(char * filePath);
    ~MiaoFormatIO();

    int Open();
    int Close();
};


class MiaoFormatOutput : public MiaoFormatIO
{
public:
    MiaoFormatOutput(char * filePath);
    ~MiaoFormatOutput();

    int WriteFrame(unsigned char * frameData, int frameDataLen, int pts, int dts, int frameType);
};


class MiaoFormatInput : public MiaoFormatIO
{
public:
    MiaoFormatInput(char * filePath);
    ~MiaoFormatInput();

    int ReadFrame(unsigned char * * frameData, int * frameDataLen, int * pts, int * dts, int * frameType);
};


class MiaoAVLoader
{
private:
    char * filePath = NULL;

    AVFormatContext * pFormatCtx = NULL;
public:
    MiaoAVLoader(char * filePath);
    ~MiaoAVLoader();

    int Open();
    int GetStreamsNum();
    int GetStreamsTypeCodec(int streamIndex, int * type, int * codec);
    int GetExtradata(int streamIndex, unsigned char * * data, int * dataLen);
    
    int ReadFrame(unsigned char * * data, int * dataLen);

	int Close();
};


#endif