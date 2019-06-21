#ifndef	MIAO_VIDEO_CUTTER_CORE_EXTRADATA
#define	MIAO_VIDEO_CUTTER_CORE_EXTRADATA

#include <stdint.h>
#include "MiaoVideoFormat.hpp"

class MiaoExtradata;
class MiaoExtradataFactory;
class H264Extradata;

class MiaoExtradataFactory
{
public:
	static MiaoExtradata * GetMiaoExtradata(int type, int codec);
};


class MiaoExtradata
{
public:
	MiaoExtradata();
	virtual ~MiaoExtradata();
	virtual int GetExtradata(uint8_t * origin, int originLen, uint8_t * * outData, int * outDataLen);
};


class H264Extradata : public MiaoExtradata
{
public:
	H264Extradata();
	virtual ~H264Extradata();

	virtual int GetExtradata(uint8_t * origin, int originLen, uint8_t * * outData, int * outDataLen);
};

#endif