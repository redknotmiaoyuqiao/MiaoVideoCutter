package com.redknot.miaovideocutter.format;

import android.util.Log;

import com.redknot.miaovideocutter.constant.Constant;
import com.redknot.miaovideocutter.jni.MiaoVideoCutterJNI;

public class VideoFormatSession {



    private long video_format_session_id = -1;

    public VideoFormatSession(String videoPath){
        this.video_format_session_id = MiaoVideoCutterJNI.video_format_session_init(videoPath);
    }

    public int Uninit(){
        return MiaoVideoCutterJNI.video_format_session_uninit(video_format_session_id);
    }

    public int getStreamCount(){
        return MiaoVideoCutterJNI.video_format_session_GetStreamCount(video_format_session_id);
    }

    public int getStreamType(int streamIndex){
        return MiaoVideoCutterJNI.video_format_session_GetStreamType(video_format_session_id ,streamIndex);
    }

    public int getVideoStreamIndex(){
        int streamCount = this.getStreamCount();
        for(int i=0;i<streamCount;i++){
            int streamType = getStreamType(i);
            if(streamType == Constant.STREAM_TYPE_VIDEO){
                return i;
            }
        }
        return -1;
    }

    public int getAudioStreamIndex(){
        int streamCount = this.getStreamCount();
        for(int i=0;i<streamCount;i++){
            int streamType = getStreamType(i);
            if(streamType == Constant.STREAM_TYPE_AUDIO){
                return i;
            }
        }
        return -1;
    }
}
