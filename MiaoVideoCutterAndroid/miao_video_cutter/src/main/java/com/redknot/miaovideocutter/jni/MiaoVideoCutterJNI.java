package com.redknot.miaovideocutter.jni;

public class MiaoVideoCutterJNI {
    static {
        System.loadLibrary("MiaoVideoAndroid");
    }

    public static native String get_core_version();
}
