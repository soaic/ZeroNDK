package com.soaic.zerondk;

import android.graphics.Bitmap;

public class OpenCvUtil {

    static {
        System.loadLibrary("OpenCvUtil");
    }


    public static native void faceInfo(Bitmap bitmap);


}
