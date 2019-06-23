#include <stdio.h>

#include <MiaoVideoFormat/MiaoVideoFormat.hpp>
#include <windows.h>

FILE * fd = NULL;

int main()
{
	fd = fopen("c://Temp/miaocutter.h264", "wb");

    MiaoAVLoader * miaoavloader = new MiaoAVLoader((char *)"C://Temp/demo.mp4");
    miaoavloader->Open();

    int streamNum = miaoavloader->GetStreamsNum();
    printf("Stream Num : %d\n", streamNum);

    for(int i=0;i<streamNum;i++){
		unsigned char * data = NULL;
		int dataLen;
        int ret = miaoavloader->GetExtradata(i, &data, &dataLen);

		if (ret) {
			continue;
		}

		printf("Data Len : %d\n", dataLen);
		for (int j = 0; j < dataLen;j++) {
			printf(" %d ", data[j]);
		}
		printf("\n");

		fwrite(data, dataLen, 1, fd);

		free(data);
    }

    
    while(1){
		unsigned char * data = NULL;
		int dataLen;
        int ret = miaoavloader->ReadFrame(&data, &dataLen);

		if (data != NULL) {
			for (int i = 0; i < 5;i++) {
				printf(" %d ", data[i]);
			}
			printf("\n");

			fwrite(data, dataLen, 1, fd);

			free(data);
		}


        if(ret){
            break;
        }
    }
   

	delete miaoavloader;

    printf("Test!!!\n");


	fclose(fd);

	system("pause");

    return 0;
}