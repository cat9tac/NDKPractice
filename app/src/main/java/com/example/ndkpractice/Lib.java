package com.example.ndkpractice;

import android.util.Log;

/**
 * 创建时间: 2020/3/29
 * 编写人：Administrator
 * 功能描述：
 **/
public class Lib {
    private static final String TAG = "ndkpractice_Lib";

    private int num1 = 1;
    private static int num2 = 1;

    static {
        System.loadLibrary("native-lib");
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String returnName();

    public native void arrayProcess(int[] intArr);

    public native void updateNum();

    public int getNum1() {
        return num1;
    }

    public void callback(int num) {
        Log.d(TAG, "hello callback  result " + num);
    }
}
