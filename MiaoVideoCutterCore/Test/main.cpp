#include <stdio.h>

#include <MiaoVideoFormat/MiaoVideoFormat.hpp>

int main()
{
    MiaoFormatOutput formatOutput((char *)"c://a.h264");
    formatOutput.Open();
    formatOutput.Close();

    printf("Test!!!\n");
    return 0;
}