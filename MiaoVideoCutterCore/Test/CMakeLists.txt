include_directories (./)
include_directories (../)
include_directories (${FFMPEG_INC_DIR})

add_executable(
    Test      
    main.cpp   
)

target_link_libraries(Test MiaoVideoFormat)