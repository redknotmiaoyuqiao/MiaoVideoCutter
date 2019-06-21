#ifndef	MIAO_VIDEO_CUTTER_CORE_FORMAT
#define	MIAO_VIDEO_CUTTER_CORE_FORMAT

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

class MiaoFormatIO;
class MiaoFormatOutput;
class MiaoFormatInput;
class MiaoVideoFrameHead;
class MiaoAVLoader;

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
public:
    MiaoAVLoader(char * filePath);
    ~MiaoAVLoader();

    int ReadFrame();
};

#endif