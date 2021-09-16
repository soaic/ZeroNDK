//
// Created by soaic on 2021/8/31.
//

#include <jni.h>
#include <android/log.h>
#include <opencv2/opencv.hpp>
#include "MapBitmapUtil.h"

using namespace cv;

void find_card_area(Mat &mat) {
    // 降噪
    Mat blur;
    GaussianBlur(mat,blur,Size(5,5), BORDER_DEFAULT, BORDER_DEFAULT);

    // 梯度增强， x 轴和 y 轴
    Mat grad_x, grad_y;
    Scharr(blur, grad_x, CV_32F, 1, 0);
    Scharr(blur, grad_y, CV_32F, 0, 1);
    Mat grad_abs_x, grad_abs_y;
    convertScaleAbs(blur, grad_abs_x);
    convertScaleAbs(blur, grad_abs_y);

    Mat grad;
    addWeighted(grad_abs_x, 0.5, grad_abs_y, 0.5, 0, grad);
    imwrite("/storage/emulated/0/orc/grad_n.jpg", grad);

    // 二值化，进行轮廓查找
    Mat gray;
    cvtColor(grad, gray, COLOR_BGRA2GRAY);
    Mat binary;
    threshold(gray, binary, 40, 255, THRESH_BINARY);

    imwrite("/storage/emulated/0/orc/binary_n.jpg", grad);
}

extern "C" JNIEXPORT void JNICALL
Java_com_soaic_zerondk_OpenCvUtil_faceInfo(JNIEnv *env, jclass clazz, jobject bitmap) {
    __android_log_print(ANDROID_LOG_ERROR, "OpenCvUtil", "Java_com_soaic_zerondk_OpenCvUtil_faceInfo");

    // 将 bitmap 转成 openCv 能操作的 c++ mat 矩阵
    Mat mat;
    MapBitmapUtil::bitmap2mat(env, bitmap, mat);

    find_card_area(mat);
}