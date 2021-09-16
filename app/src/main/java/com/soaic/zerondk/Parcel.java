package com.soaic.zerondk;

public class Parcel {

    public final long nativeObj;

    static {
        System.loadLibrary("native-lib");
    }

    public Parcel() {
        nativeObj = createParcel();
    }

    public void writeInt(int value) {
        writeIntData(nativeObj, value);
    }

    public void setDataPosition(int position) {
        setJniDataPosition(nativeObj, position);
    }

    public int readInt() {
        return readJniInt(nativeObj);
    }

    public void writeString(String str) {
        writeJniString(nativeObj, str);
    }
    public String readString() {
        return readJniString(nativeObj);
    }

    public native String readJniString(long nativeObj);
    public native void writeJniString(long nativeObj, String str) ;
    public native long createParcel();
    public native void writeIntData(long nativeObj, int value);
    public native void setJniDataPosition(long nativeObj, int position);
    public native int readJniInt(long nativeObj);



}
