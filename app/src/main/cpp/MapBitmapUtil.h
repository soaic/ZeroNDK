//
// Created by soaic on 2021/9/2.
//

#ifndef ZERONDK_MAPBITMAPUTIL_H
#define ZERONDK_MAPBITMAPUTIL_H

#include <jni.h>
#include <opencv2/opencv.hpp>
using namespace cv;


class MapBitmapUtil {
public:
    static void map2bitmap(JNIEnv* env, Mat mat, jobject& bitmap);
    static void bitmap2mat(JNIEnv* env, jobject bitmap, Mat& mat);
};


#endif //ZERONDK_MAPBITMAPUTIL_H
