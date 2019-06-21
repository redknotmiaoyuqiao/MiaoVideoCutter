#include "MiaoExtradata.hpp"

MiaoExtradata * MiaoExtradataFactory::GetMiaoExtradata(int type, int codec)
{
	if (type == STREAM_TYPE_VIDEO) {
		if (codec == STREAM_CODEC_H264) {
			return new H264Extradata();
		}
	}
	return NULL;
}