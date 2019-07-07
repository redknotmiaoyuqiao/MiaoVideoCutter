include_directories (./)
include_directories (../)
include_directories (${FFMPEG_INC_DIR})

add_library(
    MiaoVideoCodec
    MiaoVideoCodec.cpp
)

target_link_libraries(MiaoVideoCodec Miao)