package com.example.androidndkmd5sign

import android.content.pm.PackageManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
////        var packageInfo = packageManager.getPackageInfo(packageName, PackageManager.GET_SIGNATURES);
////        val signatures = packageInfo.signatures;
////        Log.e("this", signatures[0].toCharsString())

        sample_text.text = MD5Utlis.signatureParams("phone=15351304173&password=123456")
    }

}
