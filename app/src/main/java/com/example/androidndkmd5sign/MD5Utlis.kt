package com.example.androidndkmd5sign

import android.content.Context

class MD5Utlis {

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */


    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }

        external fun signatureParams(data: String): String

        external fun signatureVerify(contenxt: Context)
    }
}