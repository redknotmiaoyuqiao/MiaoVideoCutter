include_directories (./)
include_directories (../)

add_library(
    MiaoVideoAndroid
    SHARED
    com_redknot_miaovideocutter_jni_MiaoVideoCutterJNI.h
    JniInterface.cpp
)

target_link_libraries(MiaoVideoAndroid Miao)