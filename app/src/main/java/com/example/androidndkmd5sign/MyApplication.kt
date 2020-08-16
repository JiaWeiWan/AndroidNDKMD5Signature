package com.example.androidndkmd5sign

import android.app.Application

class MyApplication: Application() {
    override fun onCreate() {
        super.onCreate()
        MD5Utlis.signatureVerify(this)
    }
}