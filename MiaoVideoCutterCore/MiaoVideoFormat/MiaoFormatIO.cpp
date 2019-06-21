#include "MiaoVideoFormat.hpp"

#include <string.h>
#include <stdio.h>

MiaoFormatIO::MiaoFormatIO(char * filePath)
{
    int filePathLen = strlen(filePath) + 1;
    this->filePath = (char *)malloc(sizeof(char) * filePathLen);
    memcpy(this->filePath,filePath,filePathLen);
}

MiaoFormatIO::~MiaoFormatIO()
{
    if(this->filePath != NULL){
        free(this->filePath);
        this->filePath = NULL;
    }
    if(this->file != NULL){
        this->Close();
        this->file = NULL;
    }
}

int MiaoFormatIO::Open()
{
    this->file = fopen(this->filePath, "w");
    if(this->file == NULL){
        return -1;
    }
    return 0;
}

int MiaoFormatIO::Close()
{
    if(this->file != NULL){
        fclose(this->file);
    }
    return 0;
}
