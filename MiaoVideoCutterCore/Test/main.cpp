#include <stdio.h>

#include <MiaoVideoFormat/MiaoVideoFormat.hpp>

int main()
{
    MiaoFormatOutput formatOutput((char *)"c://a.h264");
    formatOutput.Open();
    formatOutput.Close();

    MiaoAVLoader miaoavloader((char *)"c://b");
    
    

    printf("Test!!!\n");

	system("pause");

    return 0;
}