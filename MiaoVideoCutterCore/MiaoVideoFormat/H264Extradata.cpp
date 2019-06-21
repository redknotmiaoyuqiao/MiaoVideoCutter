#include "MiaoExtradata.hpp"

H264Extradata::H264Extradata()
{

}

H264Extradata::~H264Extradata()
{

}

int H264Extradata::GetExtradata(uint8_t * origin, int originLen, uint8_t * * outData, int * outDataLen)
{
	printf("This is H264 Extradata\n");
	// Get Sps and PPS

	int spsLength = origin[6] * 0xFF + origin[7];
	int ppsLength = origin[8 + spsLength + 1] * 0xFF + origin[8 + spsLength + 2];

	uint8_t * sps = (uint8_t *)malloc(spsLength * sizeof(char));
	uint8_t * pps = (uint8_t *)malloc(ppsLength * sizeof(char));

	printf("SpsLen:%d\n", spsLength);
	printf("PPSLen:%d\n", ppsLength);
	for (int i = 0; i < spsLength; i++)
	{
		sps[i] = origin[i + 8];
	}

	for (int i = 0; i < ppsLength; i++)
	{
		pps[i] = origin[i + 8 + 2 + 1 + spsLength];
	}

	printf("Sps Type:%d\n", sps[0] & 31);
	printf("Pps Type:%d\n", pps[0] & 31);

	uint8_t * startCodeSps = (uint8_t *)malloc((spsLength + 4) * sizeof(char));
	uint8_t * startCodePps = (uint8_t *)malloc((spsLength + 4) * sizeof(char));

	free(sps);
	free(pps);


	return 0;
}