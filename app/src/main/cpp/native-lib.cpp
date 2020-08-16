#include <jni.h>
#include <string>
#include <android/log.h>
#include "md5.h"

//额外附加的字符串
static const char *EXTRA_SIGNATURE = "wjw";
//效验签名
static int is_verify = 0;
static const char *PACKAGE_NAME = "com.example.androidndkmd5sign";
static const char *APP_SIGNATURE = "308201dd30820146020101300d06092a864886f70d010105050030373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b3009060355040613025553301e170d3137303630323136303333325a170d3437303532363136303333325a30373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b300906035504061302555330819f300d06092a864886f70d010101050003818d00308189028181009dcc30c5ba99a660eab115a360cb0bfd8714ac0d5662fff16e61d89c81b8dda700bad879d7e9b5e897332453ec5993b872d6c78db563ace5dde4e3df575427038b1a22841939443269db1e6e9926847079d536727e2a43ca23e4d1dcd0e5ea52ed5779d1cebe43e298b6bad22185b6dfb1d1c8fa250e65ad6481c0e6c7aec6f90203010001300d06092a864886f70d0101050500038181000cf3649ffccda8ae7d447f8e7c566f634352f7a0371c1889c3cc6aceff8f9dfc3f7cec3897ce16846bd6efefe8bed4f5bc197b7540c47214a12f020c1f27a4b54c766db5a57e33aaafa670c58bd99fff65211ed0d601a3408ad982445d59b1bc9eb7cf9d4db945e9e53bdc61aa822d42fc6192ee7fb62782bd914bde8c0c6735";

using namespace std;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndkmd5sign_MD5Utlis_00024Companion_signatureParams(JNIEnv *env,
                                                                           jobject thiz,
                                                                           jstring params_) {

    if (is_verify == 0) {
        return env->NewStringUTF("error_signature");
    }
    const char *params = env->GetStringUTFChars(params_, 0);
    //MD5 签名规则，加点料
    //1、字符前面加点料
    string signature_str(params);
    signature_str.insert(0, EXTRA_SIGNATURE);
    //2、后面去掉两位
    signature_str = signature_str.substr(0, signature_str.length() - 2);

//    __android_log_print(ANDROID_LOG_ERROR, "this", "signature_str: %s", signature_str.c_str());

    //3、md5加密
    MD5 *ctx = new MD5(signature_str);
//    __android_log_print(ANDROID_LOG_ERROR, "this", "MD5 2: %s", ctx->toStr().c_str());

    env->ReleaseStringUTFChars(params_, params);

    return env->NewStringUTF(ctx->toStr().c_str());
}
//C调用java代码获取包名和签名
/**
 * PackageInfo packageInfo = context.getPackageManager().getPackageInfo(context.getPackageName(), PackageManager.GET_SIGNATURES);
 *   Signature[] signatures = packageInfo.signatures;
 *   return signatures[0].toCharsString();
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidndkmd5sign_MD5Utlis_00024Companion_signatureVerify(JNIEnv *env,
                                                                           jobject thiz,
                                                                           jobject contenxt) {
    //1、获取包名；
    jclass j_clz = env->GetObjectClass(contenxt);
    jmethodID j_mid = env->GetMethodID(j_clz, "getPackageName", "()Ljava/lang/String;");
    jstring j_package_name = (jstring) env->CallObjectMethod(contenxt, j_mid);

    //2、比对包名是否一样；
    const char *c_package_name = env-> GetStringUTFChars(j_package_name, NULL);
    if (strcmp(c_package_name, PACKAGE_NAME) != 0) {
        return;
    }
//    __android_log_print(ANDROID_LOG_ERROR, "this", "包名一致：%s", c_package_name);

    //3、获取签名
    //3.1、获取PackageManager
    j_mid = env->GetMethodID(j_clz, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    jobject pack_manager = env->CallObjectMethod(contenxt, j_mid);
    //3.2、获取PackageInfo
    j_clz = env->GetObjectClass(pack_manager);
    j_mid = env->GetMethodID(j_clz, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject package_info = env->CallObjectMethod(pack_manager, j_mid, j_package_name, 64);
    //3.3、获取signatures 数组
    j_clz = env->GetObjectClass(package_info);
    jfieldID j_fid = env->GetFieldID(j_clz, "signatures", "[Landroid/content/pm/Signature;");
    jobjectArray signatures = (jobjectArray)env->GetObjectField(package_info, j_fid);
    //3.4、获取signatures[0]
    jobject signatures_first = env->GetObjectArrayElement(signatures, 0);
    //3.5、调用signatures[0].toCharsString()
    j_clz = env->GetObjectClass(signatures_first);
    j_mid = env->GetMethodID(j_clz, "toCharsString", "()Ljava/lang/String;");
    jstring j_signature_str = (jstring)env->CallObjectMethod(signatures_first, j_mid);
    const char * c_signature_str = env->GetStringUTFChars(j_signature_str, NULL);
    //4、比对签名是否一样；
    if (strcmp(c_signature_str, APP_SIGNATURE) != 0) {
        return;
    }
//    __android_log_print(ANDROID_LOG_ERROR, "this", "签名校验成功：%s", c_signature_str);

    //签名验证成功
    is_verify = 1;

}