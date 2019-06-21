include_directories (./)
include_directories (../)
include_directories (${FFMPEG_INC_DIR})

add_library(
    MiaoVideoFormat
    MiaoFormatOutput.cpp 
    MiaoFormatInput.cpp
    MiaoFormatIO.cpp
    MiaoAVLoader.cpp
	MiaoExtradata.cpp
	MiaoExtradataFactory.cpp
	H264Extradata.cpp
)

target_link_libraries(MiaoVideoFormat Miao)
target_link_libraries(MiaoVideoFormat ${FFMPEG_LIB_AVFORMAT})
