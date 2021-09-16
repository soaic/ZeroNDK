//
// Created by soaic on 2021/9/2.
//

#include <jni.h>
#include <opencv2/opencv.hpp>
#include <android/bitmap.h>
#include "MapBitmapUtil.h"

void MapBitmapUtil::bitmap2mat(JNIEnv *env, jobject bitmap, Mat &mat) {
    // 锁定画布
    void* pixels = 0;
    AndroidBitmap_lockPixels(env, bitmap, &pixels);

    // 获取信息判断格式
    auto* bitmapInfo = new AndroidBitmapInfo();
    AndroidBitmap_getInfo(env, bitmap, bitmapInfo);
    mat.create(bitmapInfo->height, bitmapInfo->width, CV_8UC2);

    if(bitmapInfo->format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        // argb -> CV-8UC4
        Mat temp(bitmapInfo->height, bitmapInfo->width, CV_8UC4, pixels);
        cvtColor(temp, mat, COLOR_BGRA2BGR565);
    } else if (bitmapInfo->format == ANDROID_BITMAP_FORMAT_RGB_565) {
        // rgb  -> CV-8UC2
        Mat temp(bitmapInfo->height, bitmapInfo->width, CV_8UC2, pixels);
        temp.copyTo(temp);
    }
    // 解锁画布
    AndroidBitmap_unlockPixels(env, bitmap);
}

void MapBitmapUtil::map2bitmap(JNIEnv *env, Mat mat, jobject& bitmap) {
    // 获取图片的宽高，及格式信息
    AndroidBitmapInfo bitmapInfo;
    AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);
    void *pixels;
    AndroidBitmap_lockPixels(env, bitmap, &pixels);

    if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC4, pixels);
        if(mat.type() == CV_8UC1) {
            cvtColor(mat, temp, COLOR_GRAY2BGRA);
        } else if (mat.type() == CV_8UC2) {
            cvtColor(mat, temp, COLOR_BGR5652BGRA);
        } else if (mat.type() == CV_8UC4) {
            mat.copyTo(temp);
        }
    } else {
        // bitmapInfo = ANDROID_BITMAP_FORMAT_RGB_565
        Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC2, pixels);
        if(mat.type() == CV_8UC1) {
            cvtColor(mat, temp, COLOR_GRAY2BGR565);
        } else if (mat.type() == CV_8UC2) {
            mat.copyTo(temp);
        } else if (mat.type() == CV_8UC4) {
            cvtColor(mat, temp, COLOR_BGRA2BGR565);
        }
    }
    // 解锁画布
    AndroidBitmap_unlockPixels(env, bitmap);

}
