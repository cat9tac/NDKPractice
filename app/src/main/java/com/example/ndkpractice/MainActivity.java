package com.example.ndkpractice;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "ndkpractice_MainActivity";

    private Lib mLib;

    // Used to load the 'nativte-lib' library on application startup.
    private TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mLib = new Lib();

        // Example of a call to a native method
        tv = findViewById(R.id.sample_text);
        // tv.setText(stringFromJNI());
        tv.setText(mLib.returnName());
        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mLib.updateNum();
                tv.setText("" + mLib.getNum1());
            }
        });
        //printArray();

    }

    private void printArray() {
        int[] arr = new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int len = arr.length;

        for (int i = 0; i < len; i++) {
            Log.d(TAG, " start " + arr[i]);
        }
        mLib.arrayProcess(arr);

        for (int i = 0; i < len; i++) {
            Log.d(TAG, "end " + arr[i]);
        }
    }


}
