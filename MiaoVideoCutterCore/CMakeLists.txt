PROJECT(MIAO_VIDEO_CUTTER_CORE)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
    ADD_DEFINITIONS(-D__LINUX__)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    set(FFMPEG_INC_DIR "C://ffmpeg/ffmpeg_out/include")
    set(FFMPEG_LIB_AVFORMAT "C://ffmpeg/ffmpeg_out/bin/avformat.lib")
    set(FFMPEG_LIB_AVCODEC "C://ffmpeg/ffmpeg_out/bin/avcodec.lib")
    ADD_SUBDIRECTORY(Test)
    ADD_SUBDIRECTORY(MiaoBase)
    ADD_SUBDIRECTORY(MiaoVideoFormat)
    ADD_SUBDIRECTORY(MiaoVideoCodec)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
    ADD_DEFINITIONS(-D__IOS__)
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
