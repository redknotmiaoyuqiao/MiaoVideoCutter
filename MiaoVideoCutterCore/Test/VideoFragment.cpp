#include <stdio.h>
#include <MiaoVideoFormat/MiaoVideoFormat.hpp>

int main()
{
    MiaoVideoFragment * fragment = new MiaoVideoFragment((char *)"C://Temp/dudu.mp4");

    fragment->Open();

    int streamCount = fragment->GetStreamCount();
    printf("Stream Count : %d\n", streamCount);

    for(int streamIndex=0; streamIndex<streamCount; streamIndex++) {
        int streamType = fragment->GetStreamType(streamIndex);
        if(streamType == STREAM_TYPE_VIDEO) {
            int frameCount = fragment->GetFrameCount(streamIndex);
            printf("Video Frame Count : %d\n", frameCount);
            double dur = fragment->GetStreamDuration(streamIndex);
            printf("Video Frame Dur : %f\n", dur);

            int width;
            int height;
            unsigned char * yuvData = NULL;
            int yuvDataLen;
            fragment->GetFrameYUV(streamIndex, 10.0, &width, &height, &yuvData, &yuvDataLen);
            if(yuvData != NULL){
                free(yuvData);
            }
        }
        else if(streamType == STREAM_TYPE_AUDIO) {
            int frameCount = fragment->GetFrameCount(streamIndex);
            printf("Audio Frame Count : %d\n", frameCount);
        }        
    }

    fragment->Close();

    delete fragment;

    return 0;
}