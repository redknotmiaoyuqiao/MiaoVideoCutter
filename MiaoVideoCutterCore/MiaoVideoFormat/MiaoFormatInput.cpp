#include "MiaoVideoFormat.hpp"

MiaoFormatInput::MiaoFormatInput(char * filePath) : MiaoFormatIO(filePath)
{

}

MiaoFormatInput::~MiaoFormatInput()
{

}

int MiaoFormatInput::ReadFrame(unsigned char * * frameData, int * frameDataLen, int * pts, int * dts, int * frameType)
{
    
    return 0;
}