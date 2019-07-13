include_directories (./)
include_directories (../)
include_directories (${FFMPEG_INC_DIR})

add_library(
    MiaoVideoCodec
    MiaoVideoCodec.cpp
)

target_link_libraries(MiaoVideoCodec Miao)
target_link_libraries(MiaoVideoCodec ${FFMPEG_LIB_AVCODEC})
target_link_libraries(MiaoVideoCodec ${FFMPEG_LIB_AVFORMAT})
target_link_libraries(MiaoVideoCodec ${FFMPEG_LIB_AVUTIL})
