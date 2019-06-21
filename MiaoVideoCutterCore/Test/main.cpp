#include <stdio.h>

#include <MiaoVideoFormat/MiaoVideoFormat.hpp>

int main()
{
    MiaoAVLoader miaoavloader((char *)"/home/redknot/demo.mp4");
    miaoavloader.Open();

    int streamNum = miaoavloader.GetStreamsNum();
    printf("Stream Num : %d\n", streamNum);

    for(int i=0;i<streamNum;i++){
        miaoavloader.GetExtradata(i);
    }

    /* 
    while(1){
        int ret = miaoavloader.ReadFrame();
        if(ret){
            break;
        }
    }
    */

    printf("Test!!!\n");

    return 0;
}