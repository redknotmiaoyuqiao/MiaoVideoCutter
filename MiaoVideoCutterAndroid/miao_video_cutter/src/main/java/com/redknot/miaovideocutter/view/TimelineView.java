package com.redknot.miaovideocutter.view;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
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

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class TimelineView extends RelativeLayout {

    private LinearLayout timeline_main_layout = null;
    private TextView timeline_main_log = null;
    private List<ImageView> snapshotList = null;

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
        timeline_main_layout = inflate.findViewById(R.id.timeline_main_layout);
        timeline_main_log = inflate.findViewById(R.id.timeline_main_log);
        snapshotList = new ArrayList<ImageView>();
        this.context = context;
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

        // MiaoVideoCutterJNI.video_format_session_demo(videoPath);

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

        int snapshotCount = (int)(videoDur / timeInterval);
        Log.e("YUV Frame", "Snapshot Count:" + snapshotCount);


        for(int i=0;i<snapshotCount;i++){
            int[] rgba8888 = videoFormatSession.getRGBA8888Frame(i * timeInterval);
            Log.e("YUV Frame", "yuvFrame:" + rgba8888.length);
            Log.e("YUV Frame", "yuvFrame:" + i);

            ImageView snapshotImage = new ImageView(this.context);

            Bitmap bmp = Bitmap.createBitmap(targetWidth,targetHeight, Bitmap.Config.ARGB_8888);
            bmp.setPixels(rgba8888, 0, targetWidth, 0,0, targetWidth, targetHeight);

            snapshotImage.setImageBitmap(bmp);

            timeline_main_layout.addView(snapshotImage);
        }

        timeline_main_log.setVisibility(View.GONE);

        return 0;
    }


    private class TTT implements Runnable
    {
        private VideoFormatSession videoFormatSession = null;
        private double timeInterval;

        public TTT(VideoFormatSession videoFormatSession, double timeInterval)
        {
            this.videoFormatSession = videoFormatSession;
            this.timeInterval = timeInterval;
        }

        @Override
        public void run() {
            int snapshotCount = (int)(15.3 / timeInterval);

            for(int i=0;i<snapshotCount;i++){
                //
                // byte[] yuvFrame = videoFormatSession.getYuvFrame(i * timeInterval);
                // Log.e("YUV Frame", "yuvFrame:" + yuvFrame.length);
            }
        }
    }
}
