package com.redknot.miaovideocutter.view;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.redknot.miaovideocutter.R;
import com.redknot.miaovideocutter.format.VideoFormatSession;

import java.io.File;

public class TimelineView extends RelativeLayout {

    private LinearLayout timeline_main_layout = null;
    private TextView timeline_main_log = null;

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
        timeline_main_log = inflate.findViewById(R.id.timeline_main_log);
    }

    public int loadVideo(String videoPath){
        String logStr = "";
        Log.e("MiaoCutter TimeLine","" + videoPath);
        logStr += videoPath + "\n";
        File videoFile = new File(videoPath);
        if(!videoFile.exists()){
            return -1;
        }

        VideoFormatSession videoFormatSession = new VideoFormatSession(videoPath);
        int streamCount = videoFormatSession.getStreamCount();
        Log.e("MiaoCutter TimeLine", "Stream Count:" + streamCount);
        logStr += "Stream Count:" + streamCount + "\n";

        int videoStreamIndex = videoFormatSession.getVideoStreamIndex();
        Log.e("MiaoCutter TimeLine", "Video Stream Index:" + videoStreamIndex);
        logStr += "Video Stream Index:" + videoStreamIndex + "\n";

        int audioStreamIndex = videoFormatSession.getAudioStreamIndex();
        Log.e("MiaoCutter TimeLine", "Audio Stream Index:" + audioStreamIndex);
        logStr += "Audio Stream Index:" + audioStreamIndex + "\n";

        timeline_main_log.setText(logStr);

        return 0;
    }
}
