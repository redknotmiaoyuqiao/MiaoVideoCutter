#include <stdio.h>

#include <MiaoVideoFormat/MiaoVideoFormat.hpp>

int main()
{
    MiaoAVLoader * miaoavloader = new MiaoAVLoader((char *)"C://Temp/demo.mp4");
    miaoavloader->Open();

    int streamNum = miaoavloader->GetStreamsNum();
    printf("Stream Num : %d\n", streamNum);

    for(int i=0;i<streamNum;i++){
        miaoavloader->GetExtradata(i);
    }

    
    while(1){
        int ret = miaoavloader->ReadFrame();
        if(ret){
            break;
        }
    }
   

	delete miaoavloader;

    printf("Test!!!\n");

	system("pause");

    return 0;
}