#include "MiaoVideoFormat.hpp"
#include <string.h>

MiaoFormatOutput::MiaoFormatOutput(char * filePath) : MiaoFormatIO(filePath)
{

}

MiaoFormatOutput::~MiaoFormatOutput()
{

}

int MiaoFormatOutput::WriteFrame(unsigned char * frameData, int frameDataLen, int pts, int dts, int frameType)
{
    return 0;
}