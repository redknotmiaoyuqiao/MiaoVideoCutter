package com.redknot.miaovideocutter.jni;

public class MiaoVideoCutterJNI {
    static {
        System.loadLibrary("MiaoVideoAndroid");
        System.loadLibrary("avcodec");
        System.loadLibrary("avformat");
        System.loadLibrary("swresample");
        System.loadLibrary("avutil");
    }

    public static native String get_core_version();

    public static native void       video_format_session_demo                       (String videoPath);

    public static native long       video_format_session_init                       (String videoPath);
    public static native int        video_format_session_uninit                     (long session_id);
    public static native int        video_format_session_GetStreamCount             (long session_id);
    public static native int        video_format_session_GetStreamType              (long session_id, int stream_index);
    public static native double     video_format_session_GetStreamDuration          (long session_id, int stream_index);
    public static native int        video_format_session_GetStreamWidth             (long session_id, int stream_index);
    public static native int        video_format_session_GetStreamHeight            (long session_id, int stream_index);
    public static native int        video_format_session_GetFrameCount              (long session_id);

    public static native long       video_format_session_GetFrameYUV                (long session_id, int stream_index, double time);
    public static native byte[]     video_format_session_GetYuvFrame                (long yuv_set_id);
    public static native byte[]     video_format_session_GetYuvFrameScale           (long yuv_set_id, int targetWidth, int targetHeight);
    public static native byte[]     video_format_session_GetRGB565Frame             (long yuv_set_id, int targetWidth, int targetHeight);
    public static native int        video_format_session_YuvUninit                  (long yuv_set_id);
}
