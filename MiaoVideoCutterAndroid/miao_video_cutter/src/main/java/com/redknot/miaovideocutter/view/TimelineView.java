package com.redknot.miaovideocutter.view;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import com.redknot.miaovideocutter.R;
import com.redknot.miaovideocutter.format.VideoFormatSession;

import java.io.File;

public class TimelineView extends RelativeLayout {

    private LinearLayout timeline_main_layout = null;

    public TimelineView(Context context) {
        super(context);
        init();
    }

    public TimelineView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public TimelineView(Context context, AttributeSet attrs, int defStyleAttr)  {
        super(context, attrs, defStyleAttr);
        init();
    }

    private void init(){
        View inflate = inflate(getContext(), R.layout.miaovideocutter_timeline_view, this);
        timeline_main_layout = inflate.findViewById(R.id.timeline_main_layout);
    }

    public int loadVideo(String videoPath){
        Log.e("MiaoCutter TimeLine","" + videoPath);
        File videoFile = new File(videoPath);
        if(!videoFile.exists()){
            return -1;
        }

        VideoFormatSession videoFormatSession = new VideoFormatSession(videoPath);
        int streamCount = videoFormatSession.getStreamCount();
        Log.e("MiaoCutter TimeLine", "Stream Count:" + streamCount);

        int videoStreamIndex = videoFormatSession.getVideoStreamIndex();
        Log.e("MiaoCutter TimeLine", "Video Stream Index:" + videoStreamIndex);
        int audioStreamIndex = videoFormatSession.getAudioStreamIndex();
        Log.e("MiaoCutter TimeLine", "Audio Stream Index:" + audioStreamIndex);

        return 0;
    }
}
