package com.redknot.miaovideocutter.view;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.redknot.miaovideocutter.R;
import com.redknot.miaovideocutter.format.VideoFormatSession;
import com.redknot.miaovideocutter.jni.MiaoVideoCutterJNI;
import com.redknot.miaovideocutter.view.adapter.TimelineAdapter;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class TimelineView extends RelativeLayout {

    private TextView timeline_main_log = null;
    private RecyclerView timeline_main_recycler_view;
    private TimelineAdapter timelineAdapter;
    private Context context = null;

    public TimelineView(Context context) {
        super(context);
        init(context);
    }

    public TimelineView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public TimelineView(Context context, AttributeSet attrs, int defStyleAttr)  {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    private void init(Context context){
        View inflate = inflate(getContext(), R.layout.miaovideocutter_timeline_view, this);
        timeline_main_log = inflate.findViewById(R.id.timeline_main_log);
        timeline_main_recycler_view = inflate.findViewById(R.id.timeline_main_recycler_view);
        this.context = context;
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);

        Log.e("onMeasure", "width:" + widthMeasureSpec);
        Log.e("onMeasure", "height:" + heightMeasureSpec);
    }

    public int loadVideo(String videoPath){
        return loadVideo(videoPath, -1,1.0);
    }

    public int loadVideo(String videoPath, int _targetHeight, double timeInterval){
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

        double videoDur = videoFormatSession.getDefVideoStreamDuration();
        Log.e("MiaoCutter TimeLine", "Video Duration:" + videoDur);
        logStr += "Video Duration:" + videoDur + "\n";

        double audioDur = videoFormatSession.getDefAudioStreamDuration();
        Log.e("MiaoCutter TimeLine", "Audio Duration:" + audioDur);
        logStr += "Audio Duration:" + audioDur + "\n";

        int width = videoFormatSession.getWidth();
        int height = videoFormatSession.getHeight();
        Log.e("MiaoCutter TimeLine", "Width:" + width);
        Log.e("MiaoCutter TimeLine", "Height:" + height);
        logStr += "Width:" + width + "\n";
        logStr += "Height:" + height + "\n";

        int targetWidth = width;
        int targetHeight = height;

        timeline_main_log.setText(logStr);

        // new Thread(new TTT(videoFormatSession, timeInterval)).start();

        timeline_main_log.setVisibility(View.GONE);



        timelineAdapter = new TimelineAdapter(videoFormatSession);

        LinearLayoutManager linearLayoutManager = new LinearLayoutManager(this.context);
        linearLayoutManager.setOrientation(LinearLayoutManager.HORIZONTAL);

        timeline_main_recycler_view.setLayoutManager(linearLayoutManager);
        timeline_main_recycler_view.setAdapter(timelineAdapter);

        return 0;
    }
}
