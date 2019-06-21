include_directories (./)
include_directories (../)

add_library(
    MiaoVideoFormat
    MiaoFormatOutput.cpp 
    MiaoFormatInput.cpp
    MiaoFormatIO.cpp
)

# target_link_libraries(Test pthread)