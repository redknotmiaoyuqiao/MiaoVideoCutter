package com.redknot.miaovideocutter;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.redknot.miaovideocutter.jni.MiaoVideoCutterJNI;

public class MainActivity extends AppCompatActivity {

    private TextView version_txt = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        version_txt = (TextView) findViewById(R.id.version_txt);
        version_txt.setText(MiaoVideoCutterJNI.get_core_version() + "");
    }
}
