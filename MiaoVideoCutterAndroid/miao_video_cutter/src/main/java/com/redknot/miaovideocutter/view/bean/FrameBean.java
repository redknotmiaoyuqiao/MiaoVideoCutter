package com.redknot.miaovideocutter.view.bean;

import android.graphics.Bitmap;

public class FrameBean {
    private int width;
    private int height;
    private double time;

    private boolean bmpProcess = false;
    private Bitmap bmp = null;

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public Bitmap getBmp() {
        return bmp;
    }

    public void setBmp(Bitmap bmp) {
        this.bmp = bmp;
    }

    public double getTime() {
        return time;
    }

    public void setTime(double time) {
        this.time = time;
    }

    public boolean isBmpProcess() {
        return bmpProcess;
    }

    public void setBmpProcess(boolean bmpProcess) {
        this.bmpProcess = bmpProcess;
    }
}
