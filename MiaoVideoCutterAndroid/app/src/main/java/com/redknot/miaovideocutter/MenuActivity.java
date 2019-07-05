package com.redknot.miaovideocutter;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;

public class MenuActivity extends AppCompatActivity {

    private MyClickListener listener = null;
    private Button menu_btn_filter = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);

        listener = new MyClickListener();

        menu_btn_filter = (Button) findViewById(R.id.menu_btn_filter);

        menu_btn_filter.setOnClickListener(listener);
    }

    private class MyClickListener implements View.OnClickListener
    {
        @Override
        public void onClick(View v) {
            if(v == menu_btn_filter){
                Intent intent = new Intent(MenuActivity.this,FilterActivity.class);
                startActivity(intent);
            }
        }
    }
}
