#include "Miao.hpp"
#include <string.h>

int miao_str_cpy(char * * dist, char * src)
{
    int src_len = strlen(src) + 1;
    char * _dist = (char *)malloc(src_len);
    memcpy(_dist, src, src_len);
    *dist = _dist;

    return 0;
}