package com.soaic.zerondk;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import com.squareup.leakcanary.LeakCanary;

public class MainActivity extends AppCompatActivity {
    private ImageView img;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        img = findViewById(R.id.img);
        img.setImageResource(R.drawable.card);

        LeakCanary.install(getApplication());

    }

    public void jniTest(View view) {
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(),R.drawable.card);
        OpenCvUtil.faceInfo(bitmap);
    }
}