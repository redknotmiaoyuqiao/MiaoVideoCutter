package com.redknot.miaovideocutter.view.adapter;

import android.graphics.Bitmap;
import android.os.Handler;
import android.os.Message;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import com.redknot.miaovideocutter.R;
import com.redknot.miaovideocutter.format.VideoFormatSession;
import com.redknot.miaovideocutter.view.bean.FrameBean;

import java.util.LinkedList;
import java.util.List;

public class TimelineAdapter extends RecyclerView.Adapter<TimelineAdapter.TimelineFrame> {

    private List<FrameBean> frameList = null;
    private VideoFormatSession videoFormatSession = null;
    private GetFrameHandler handler = null;

    public TimelineAdapter(VideoFormatSession videoFormatSession){
        this.videoFormatSession = videoFormatSession;
        frameList = new LinkedList<FrameBean>();

        double videoDur = videoFormatSession.getDefVideoStreamDuration();
        int count = (int)(videoDur / 1.0f);

        for(int i=0;i<count;i++){
            FrameBean frameBean = new FrameBean();
            frameBean.setTime(i * 1.0f);
            frameList.add(frameBean);
        }
    }

    @NonNull
    @Override
    public TimelineFrame onCreateViewHolder(@NonNull ViewGroup parent, int i) {
        View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.miaovideocutter_timeline_adapter_frame, parent, false);
        return new TimelineFrame(v);
    }

    @Override
    public void onBindViewHolder(@NonNull TimelineFrame timelineFrame, int i) {
        // i = i -1;

        if(i < 0 ){
            timelineFrame.timeline_snapshot_img.setImageBitmap(null);
            return;
        }

        FrameBean frame = this.frameList.get(i);
        Bitmap bmp = frame.getBmp();
        if(bmp == null) {
            timelineFrame.timeline_snapshot_img.setImageBitmap(null);
            if(!frame.isBmpProcess()){
                frame.setBmpProcess(true);
                handler = new GetFrameHandler(frame);
                GetFrameThread t = new GetFrameThread(handler, videoFormatSession, frame.getTime());
                new Thread(t).start();
            }
        }
        else{
            timelineFrame.timeline_snapshot_img.setImageBitmap(bmp);
        }
    }

    @Override
    public int getItemCount() {
        return frameList.size();
    }

    public class TimelineFrame extends RecyclerView.ViewHolder{

        public ImageView timeline_snapshot_img = null;

        public TimelineFrame(View v) {
            super(v);
            timeline_snapshot_img = v.findViewById(R.id.timeline_snapshot_img);
        }
    }

    private class GetFrameHandler extends Handler
    {
        private FrameBean frame;

        public GetFrameHandler(FrameBean frame){
            this.frame = frame;
        }

        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            Bitmap bmp = (Bitmap) msg.obj;
            this.frame.setBmp(bmp);
            frame.setBmpProcess(false);
            TimelineAdapter.this.notifyDataSetChanged();
            Log.e("MiaoCutter TimeLine", "Start Thread to Get RGBA Ok!!!!");
        }
    }

    private class GetFrameThread implements Runnable
    {
        private GetFrameHandler handler = null;
        private VideoFormatSession videoFormatSession = null;
        private double time;

        public GetFrameThread(GetFrameHandler handler, VideoFormatSession videoFormatSession, double time){
            this.handler = handler;
            this.videoFormatSession = videoFormatSession;
            this.time = time;
        }

        @Override
        public void run() {
            synchronized (videoFormatSession)
            {
                Log.e("MiaoCutter TimeLine", "Start Thread to Get RGBA");
                int[] rgba8888 = videoFormatSession.getRGBA8888Frame(this.time);
                Log.e("YUV Frame", "yuvFrame:" + rgba8888.length);
                Log.e("YUV Frame", "yuvFrame Time:" + this.time);

                int targetWidth = videoFormatSession.getWidth();
                int targetHeight = videoFormatSession.getHeight();

                Bitmap bmp = Bitmap.createBitmap(targetWidth,targetHeight, Bitmap.Config.RGB_565);
                bmp.setPixels(rgba8888, 0, targetWidth , 0,0, targetWidth, targetHeight);

                Message msg = new Message();
                msg.obj = bmp;
                this.handler.sendMessage(msg);
            }
        }
    }
}
