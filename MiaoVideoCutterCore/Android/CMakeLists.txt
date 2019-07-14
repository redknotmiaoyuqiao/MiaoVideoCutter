include_directories (./)
include_directories (../)
include_directories (${FFMPEG_INC_DIR})

add_library(
    MiaoVideoAndroid
    SHARED
    com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI.h
    JniInterface.cpp
    JniUtil.cpp
    VideoFormatSessionJni.cpp
    VideoFormatSessionYuvFrameJni.cpp
    YuvSet.cpp
)

target_link_libraries(MiaoVideoAndroid Miao)
target_link_libraries(MiaoVideoAndroid MiaoVideoFormat)

target_link_libraries(MiaoVideoAndroid ${FFMPEG_LIB_AVCODEC})
target_link_libraries(MiaoVideoAndroid ${FFMPEG_LIB_AVFORMAT})
target_link_libraries(MiaoVideoAndroid ${FFMPEG_LIB_AVUTIL})

find_library(log-lib log)
target_link_libraries(MiaoVideoAndroid ${log-lib})
