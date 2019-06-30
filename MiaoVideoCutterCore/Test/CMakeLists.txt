include_directories (./)
include_directories (../)
include_directories (${FFMPEG_INC_DIR})

add_executable(
    Test      
    main.cpp   
)

add_executable(
    VideoFragment
    VideoFragment.cpp
)

target_link_libraries(Test MiaoVideoFormat)
target_link_libraries(VideoFragment MiaoVideoFormat)