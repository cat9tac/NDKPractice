#include <jni.h>
#include <string>
#include <__locale>

#define LOG_TAG "ndkpractice_jni"
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ndkpractice_Lib_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_ndkpractice_Lib_returnName(JNIEnv *env, jobject thiz) {
    // TODO: implement returnName()
    //方式一
    //std::string hello = "NDKPractice";
    // return env->NewStringUTF(hello.c_str());//构建UTF-8编码格式的字符串实例

    //方式二
    const jbyte *str;
    jboolean isCopy;

    jstring javaString = env->NewStringUTF("hello world  NDKPractice !");
    str = (jbyte *) (env->GetStringUTFChars(javaString, &isCopy));
    if (0 != str) {
        printf("%s  java string : %s", LOG_TAG, str);
    }
    env->ReleaseStringUTFChars(javaString, reinterpret_cast<const char *>(str));
    return javaString;

}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_ndkpractice_Lib_arrayProcess(JNIEnv *env, jobject thiz,
                                              jintArray int_arr) {
    //jni 提供两种访问java数组元素的方法，一复制成C数组，二提供直接指向数组元素的指针

    jint length = env->GetArrayLength(int_arr);
    // 一将java传下来的引用数组类型通过 GetIntArrayRegion复制int_arr到nativeArray，
    // 处理完再将nativeArray复制给int_arr并释放nativeArray
    /*  jint nativeArray[length];
      env->GetIntArrayRegion(int_arr, 0, length, nativeArray);
      for (int i = 0; i < length; i++) {
          nativeArray[i] *= 10;
      }
      env->SetIntArrayRegion(int_arr, 0, length, nativeArray);*/

    // 方法 二 通过GetIntArrayElements获取指向java数组的直接指针，
    // 用完之后需要使用ReleaseIntArrayElements立即释放，否则出现内存泄漏
    jint *nativeDirectArray;
    jboolean isCopy;
    nativeDirectArray = env->GetIntArrayElements(int_arr, &isCopy);
    for (int i = 0; i < length; i++) {
        nativeDirectArray[i] *= 10;
    }
    env->ReleaseIntArrayElements(int_arr, nativeDirectArray, 0);

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_ndkpractice_Lib_updateNum(JNIEnv *env, jobject thiz) {
    // TODO: implement updateNum()
    jclass clazz;
    clazz = env->GetObjectClass(thiz);
    //获取到num1实例域的Id
    jfieldID num1Id;
    //GetFieldID 传入clazz，实例域名的字符串，以及类型签名
    num1Id = env->GetFieldID(clazz, "num1", "I");
    jint num1;
    //通过FiledId 获取到这个实例域
    num1 = (jint) (env->GetIntField(thiz, num1Id));
    printf("%s num %d", LOG_TAG, num1);
    num1 += 100;
    env->SetIntField(thiz, num1Id, num1);
    //获取到callback方法的Id
    jmethodID callbackId;
    //GetMethodID中 传入clazz，方法名字符串，以及方法签名
    callbackId = env->GetMethodID(clazz, "callback", "(I)V");
    //调用实例方法
    env->CallVoidMethod(thiz, callbackId, num1);
}