#include <jni.h>
#include <string>
#include "ArrayList.hpp"
#include "android/log.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_soaic_zerondk_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";


    ArrayList<int> *arrayList = new ArrayList<int>(10);

    for (int i = 0; i < 10; ++i) {
        arrayList->add(i);
    }

    __android_log_print(ANDROID_LOG_ERROR, "TAG", "size=%d", arrayList->size());

    for (int i = 0; i < arrayList->size(); ++i) {
        __android_log_print(ANDROID_LOG_ERROR, "TAG", "i=%d", arrayList->get(i));
    }

    arrayList->remove(5);

    __android_log_print(ANDROID_LOG_ERROR, "TAG", "size=%d", arrayList->size());

    for (int i = 0; i < arrayList->size(); ++i) {
        __android_log_print(ANDROID_LOG_ERROR, "TAG", "i=%d", arrayList->get(i));
    }


    return env->NewStringUTF(hello.c_str());
}

class Parcel {
    char* mData;
    int mDataPosition = 0;

public:
    Parcel() {
        mData = static_cast<char *>(malloc(1024));
    }
    void writeInt(jint value) {
        *reinterpret_cast<jlong*>(mData + mDataPosition) = value;
        mDataPosition = sizeof(int);
    }

    void setDataPosition(jint position) {
        mDataPosition = position;
    }

    int readInt() {
        int value = *reinterpret_cast<jlong*>(mData + mDataPosition);
        mDataPosition += sizeof(int);
        return value;
    }

    void writeString(const char* c_str) {
        int len = strlen(c_str);
        *reinterpret_cast<jlong*>(mData + mDataPosition) = len;
        mDataPosition += sizeof(int);
        strcat(mData, c_str);
        mDataPosition += len;
    }

    char* readString() {
        int len = *reinterpret_cast<jlong*>(mData + mDataPosition);
        mDataPosition += sizeof(int);
        char* str = strsub(mData, mDataPosition, mDataPosition+len);
        mDataPosition += len;
        return str;
    }

    char* strsub(char* str, int start, int end) {
        // 开辟一个字符串存储
        int len = end - start;
        //char* sub = (char*)malloc((end-start)*sizeof(char)+1); // +1为了添加结尾字符，用完要记得free
        char sub[len+1];

        str += start;
        for(int i=0; i<len; i++) {
            sub[i] = *str;
            str++; // 指针往后挪1
        }
        // 标记字符串结尾，否则printf无法判断结尾
        sub[len] = '\0';
        return sub;
    }
};



extern "C" JNIEXPORT jlong JNICALL
Java_com_soaic_zerondk_Parcel_createParcel(JNIEnv *env, jobject obj) {
    auto* parcel = new Parcel();
    return reinterpret_cast<jlong>(parcel);

}

extern "C" JNIEXPORT void JNICALL
Java_com_soaic_zerondk_Parcel_writeIntData(JNIEnv *env, jobject obj, jlong native_obj, jint value) {
    auto* parcel = reinterpret_cast<Parcel *>(native_obj);
    parcel-> writeInt(value);
}

extern "C" JNIEXPORT void JNICALL
Java_com_soaic_zerondk_Parcel_setJniDataPosition(JNIEnv *env, jobject obj, jlong native_obj, jint position) {
    auto* parcel = reinterpret_cast<Parcel *>(native_obj);
    parcel->setDataPosition(position);
}

extern "C" JNIEXPORT jint JNICALL
Java_com_soaic_zerondk_Parcel_readJniInt(JNIEnv *env, jobject obj, jlong native_obj) {
    auto* parcel = reinterpret_cast<Parcel *>(native_obj);
    return parcel->readInt();
}
extern "C" JNIEXPORT void JNICALL
Java_com_soaic_zerondk_Parcel_writeJniString(JNIEnv *env, jobject thiz, jlong native_obj, jstring str) {
    auto* parcel = reinterpret_cast<Parcel *>(native_obj);
    const char* c_str = env->GetStringUTFChars(str, reinterpret_cast<jboolean *>(false));
    parcel->writeString(c_str);
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_soaic_zerondk_Parcel_readJniString(JNIEnv *env, jobject thiz, jlong native_obj) {
    auto* parcel = reinterpret_cast<Parcel *>(native_obj);
    return env->NewStringUTF(parcel->readString());
}
