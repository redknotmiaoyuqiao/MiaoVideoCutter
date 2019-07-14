package com.redknot.miaovideocutter.app;

import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.widget.Toast;

import com.redknot.miaovideocutter.jni.MiaoVideoCutterJNI;
import com.redknot.miaovideocutter.view.TimelineView;

public class FilterActivity extends AppCompatActivity {

    private TimelineView filter_timeline_view = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_filter);

        String path = Environment.getExternalStorageDirectory() + "/dudu.mp4";


        filter_timeline_view = findViewById(R.id.filter_timeline_view);
        int ret = filter_timeline_view.loadVideo(path);
        if(ret < 0){
            Toast.makeText(this, getText(R.string.toast_video_file_not_found), Toast.LENGTH_LONG).show();
        }
    }
}
