include_directories (./)
include_directories (../)
include_directories (${FFMPEG_INC_DIR})

add_library(
    MiaoVideoAndroid
    SHARED
    com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI.h
    JniInterface.cpp
    VideoFormatSessionJni.cpp
    JniUtil.cpp
)

target_link_libraries(MiaoVideoAndroid Miao)
target_link_libraries(MiaoVideoAndroid MiaoVideoFormat)