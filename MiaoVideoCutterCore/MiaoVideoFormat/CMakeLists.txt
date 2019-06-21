include_directories (./)
include_directories (../)

add_library(
    MiaoVideoFormat
    MiaoFormatOutput.cpp 
    MiaoFormatInput.cpp
    MiaoFormatIO.cpp
    MiaoAVLoader.cpp
)

target_link_libraries(MiaoVideoFormat Miao)
target_link_libraries(MiaoVideoFormat avformat)