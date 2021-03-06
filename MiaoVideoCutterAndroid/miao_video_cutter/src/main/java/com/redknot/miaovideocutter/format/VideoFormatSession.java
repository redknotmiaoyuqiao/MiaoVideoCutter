package com.redknot.miaovideocutter.format;

import android.util.Log;

import com.redknot.miaovideocutter.constant.Constant;
import com.redknot.miaovideocutter.jni.MiaoVideoCutterJNI;

public class VideoFormatSession {

    private long video_format_session_id = -1;

    public VideoFormatSession(String videoPath)
    {

        this.video_format_session_id = MiaoVideoCutterJNI.video_format_session_init(videoPath);
    }

    public int Uninit()
    {
        return MiaoVideoCutterJNI.video_format_session_uninit(video_format_session_id);
    }

    public int getStreamCount()
    {
        return MiaoVideoCutterJNI.video_format_session_GetStreamCount(video_format_session_id);
    }

    public int getStreamType(int streamIndex)
    {
        return MiaoVideoCutterJNI.video_format_session_GetStreamType(video_format_session_id ,streamIndex);
    }

    public int getVideoStreamIndex()
    {
        int streamCount = this.getStreamCount();
        for(int i=0;i<streamCount;i++){
            int streamType = getStreamType(i);
            if(streamType == Constant.STREAM_TYPE_VIDEO){
                return i;
            }
        }
        return -1;
    }

    public int getAudioStreamIndex()
    {
        int streamCount = this.getStreamCount();
        for(int i=0;i<streamCount;i++){
            int streamType = getStreamType(i);
            if(streamType == Constant.STREAM_TYPE_AUDIO){
                return i;
            }
        }
        return -1;
    }

    public double getStreamDuration(int streamIndex)
    {
        return MiaoVideoCutterJNI.video_format_session_GetStreamDuration(video_format_session_id, streamIndex);
    }

    public double getDefVideoStreamDuration()
    {
        // MiaoVideoCutterJNI.video_format_session_GetFrameYUV(video_format_session_id, getVideoStreamIndex(), 3.0);
        return getStreamDuration(getVideoStreamIndex());
    }

    public double getDefAudioStreamDuration()
    {
        return getStreamDuration(getAudioStreamIndex());
    }

    public int getWidth()
    {
        int streamIndex = getVideoStreamIndex();
        return MiaoVideoCutterJNI.video_format_session_GetStreamWidth(video_format_session_id, streamIndex);
    }
    public int getHeight()
    {
        int streamIndex = getVideoStreamIndex();
        return MiaoVideoCutterJNI.video_format_session_GetStreamHeight(video_format_session_id, streamIndex);
    }

    public int[] getRGBA8888Frame(double time)
    {
        int streamIndex = getVideoStreamIndex();
        long yuvSet = MiaoVideoCutterJNI.video_format_session_GetFrameYUV(video_format_session_id, streamIndex, time);
        int[] rgbaData = MiaoVideoCutterJNI.video_format_session_GetRGBA8888(yuvSet);
        int ret = MiaoVideoCutterJNI.video_format_session_YuvUninit(yuvSet);

        return rgbaData;
    }
}
