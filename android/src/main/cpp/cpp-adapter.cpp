#include <jni.h>
#include <jsi/jsi.h>
#include <MMKV.h>
#include "MmkvHostObject.h"

using namespace facebook;

std::string getPropertyAsStringOrEmptyFromObject(jsi::Object& object, const std::string& propertyName, jsi::Runtime& runtime) {
    jsi::Value value = object.getProperty(runtime, propertyName.c_str());
    return value.isString() ? value.asString(runtime).utf8(runtime) : "";
}


void install(jsi::Runtime& jsiRuntime) {
    // MMKV.createNewInstance()
    auto mmkvCreateNewInstance = jsi::Function::createFromHostFunction(jsiRuntime,
                                                                       jsi::PropNameID::forAscii(jsiRuntime, "mmkvCreateNewInstance"),
                                                                       0,
                                                                       [](jsi::Runtime& runtime,
                                                                          const jsi::Value& thisValue,
                                                                          const jsi::Value* arguments,
                                                                          size_t count) -> jsi::Value {
                                                                         if (count != 1) {
                                                                             throw jsi::JSError(runtime, "MMKV.createNewInstance(..) expects one argument (object)!");
                                                                         }
                                                                         jsi::Object config = arguments[0].asObject(runtime);

                                                                         std::string instanceId = getPropertyAsStringOrEmptyFromObject(config, "id", runtime);
                                                                         std::string path = getPropertyAsStringOrEmptyFromObject(config, "path", runtime);
                                                                         std::string encryptionKey = getPropertyAsStringOrEmptyFromObject(config, "encryptionKey", runtime);

                                                                         auto instance = std::make_shared<MmkvHostObject>(instanceId, path, encryptionKey);
//                                                                         jsiRuntime.global().setProperty(jsiRuntime, "mmkvCreateNewInstance", std::move(instance));
                                                                         return jsi::Object::createFromHostObject(runtime, instance);
                                                                       });
    jsiRuntime.global().setProperty(jsiRuntime, "mmkvCreateNewInstance", std::move(mmkvCreateNewInstance));
    auto x =  jsiRuntime.global().getProperty(jsiRuntime, "mmkvCreateNewInstance");

}
std::string jstringToStdString(JNIEnv *env, jstring jStr) {
    if (!jStr) return "";

    const auto stringClass = env->GetObjectClass(jStr);
    const auto getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const auto stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    auto length = (size_t) env->GetArrayLength(stringJbytes);
    auto pBytes = env->GetByteArrayElements(stringJbytes, nullptr);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reactnativemmkv_MmkvModule_nativeInstall(JNIEnv *env, jclass clazz, jlong jsiPtr, jstring path) {
    MMKV::initializeMMKV(jstringToStdString(env, path));

    auto runtime = reinterpret_cast<jsi::Runtime*>(jsiPtr);
    if (runtime) {
        install(*runtime);
    }
    // if runtime was nullptr, MMKV will not be installed. This should only happen while Remote Debugging (Chrome), but will be weird either way.
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reactnativemmkv_MmkvModule_nativeInstall2(JNIEnv *env, jclass clazz, jlong jsiPtr, jstring path) {
    MMKV::initializeMMKV(jstringToStdString(env, path));

    auto runtime = reinterpret_cast<jsi::Runtime*>(jsiPtr);
    if (runtime) {
       // install(*runtime);
    }
    // if runtime was nullptr, MMKV will not be installed. This should only happen while Remote Debugging (Chrome), but will be weird either way.
}



jint obtainArraySize(jsi::Runtime& jsiRuntime) {
    auto v = jsiRuntime.global().getProperty(jsiRuntime, "arrayable");
    if (jsiRuntime.global().hasProperty(jsiRuntime, "arrayable")) {
        auto maybeArray = jsiRuntime.global().getProperty(jsiRuntime, "arrayable");
        if (maybeArray.isObject() && maybeArray.asObject(jsiRuntime).isArray(jsiRuntime)) {
            return maybeArray.asObject(jsiRuntime).asArray(jsiRuntime).size(jsiRuntime);
        }
    }
    return 0;
    //std::shared_ptr<MmkvHostObject> f =  std::static_pointer_cast<MmkvHostObject>(v.asObject(jsiRuntime).asHostObject(jsiRuntime));
    return v.asObject(jsiRuntime).asArray(jsiRuntime).size(jsiRuntime);
    // return f->sampleArray->size(jsiRuntime);
}


jint obtainArraySize2(jsi::Runtime& jsiRuntime) {
    if (jsiRuntime.global().hasProperty(jsiRuntime, "nativeInstance")) {

        auto maybeNativeInstance = jsiRuntime.global().getProperty(jsiRuntime, "nativeInstance");
        if (maybeNativeInstance.isObject() && maybeNativeInstance.asObject(jsiRuntime).isHostObject(jsiRuntime)) {
            std::shared_ptr<MmkvHostObject> f =  std::static_pointer_cast<MmkvHostObject>(maybeNativeInstance.asObject(jsiRuntime).asHostObject(jsiRuntime));
            int size = f->arraySize;
            return size;
        }
    }
    return 0;
}

jint obtainArraySize3(jsi::Runtime& jsiRuntime) {
    if (jsiRuntime.global().hasProperty(jsiRuntime, "arraySize")) {

        auto maybeNativeInstance = jsiRuntime.global().getProperty(jsiRuntime, "arraySize");
        if (maybeNativeInstance.isNumber()) {
           // std::shared_ptr<MmkvHostObject> f =  std::static_pointer_cast<MmkvHostObject>(maybeNativeInstance.asObject(jsiRuntime).asHostObject(jsiRuntime));
            return maybeNativeInstance.asNumber();
        }
    }
    return 0;
}

jint obtainArraySize4(jsi::Runtime& jsiRuntime) {
    auto v = jsiRuntime.global().getProperty(jsiRuntime, "arrayable");
    if (jsiRuntime.global().hasProperty(jsiRuntime, "arrayable")) {
        auto maybeArray = jsiRuntime.global().getProperty(jsiRuntime, "arrayable");
        if (maybeArray.isObject() && maybeArray.asObject(jsiRuntime).isArray(jsiRuntime)) {
            return maybeArray.asObject(jsiRuntime).asArray(jsiRuntime).length(jsiRuntime);
        }
    }
    return 0;
    //std::shared_ptr<MmkvHostObject> f =  std::static_pointer_cast<MmkvHostObject>(v.asObject(jsiRuntime).asHostObject(jsiRuntime));
    return v.asObject(jsiRuntime).asArray(jsiRuntime).size(jsiRuntime);
    // return f->sampleArray->size(jsiRuntime);
}



extern "C"
JNIEXPORT jint JNICALL
Java_com_reactnativemmkv_MmkvModule_getArraySize(JNIEnv *env, jclass clazz, jlong jsiPtr) {
    auto runtime = reinterpret_cast<jsi::Runtime*>(jsiPtr);
    return 100;
    //return obtainArraySize3(*runtime);
}


unsigned long long obtainValueAtIndex(jsi::Runtime& jsiRuntime, jint index) {
    if (jsiRuntime.global().hasProperty(jsiRuntime, "arrayable")) {
        auto maybeArray = jsiRuntime.global().getProperty(jsiRuntime, "arrayable");
        if (maybeArray.isObject() && maybeArray.asObject(jsiRuntime).isArray(jsiRuntime)) {
            return maybeArray.asObject(jsiRuntime).asArray(jsiRuntime).getValueAtIndex(jsiRuntime, index).asNumber();
        }
    }
    return 0;
    //   std::shared_ptr<MmkvHostObject> module =  std::static_pointer_cast<MmkvHostObject>(v.asObject(jsiRuntime).asHostObject(jsiRuntime));
    // return module->sampleArray->getValueAtIndex(jsiRuntime, index).asString(jsiRuntime).utf8(jsiRuntime);
}



std::string obtainValueAtIndexString(jsi::Runtime& jsiRuntime, jint index) {
    if (jsiRuntime.global().hasProperty(jsiRuntime, "arrayable")) {
        auto maybeArray = jsiRuntime.global().getProperty(jsiRuntime, "arrayable");
        if (maybeArray.isObject() && maybeArray.asObject(jsiRuntime).isArray(jsiRuntime)) {
            return maybeArray.asObject(jsiRuntime).asArray(jsiRuntime).getValueAtIndex(jsiRuntime, index).asString(jsiRuntime).utf8(jsiRuntime);
        }
    }
    return "FFF";
    //   std::shared_ptr<MmkvHostObject> module =  std::static_pointer_cast<MmkvHostObject>(v.asObject(jsiRuntime).asHostObject(jsiRuntime));
    // return module->sampleArray->getValueAtIndex(jsiRuntime, index).asString(jsiRuntime).utf8(jsiRuntime);
}





extern "C"
JNIEXPORT jlong JNICALL
Java_com_reactnativemmkv_MmkvModule_getValueAtIndex(JNIEnv *env, jclass clazz, jlong jsiPtr, jint index) {
    auto runtime = reinterpret_cast<jsi::Runtime*>(jsiPtr);
    auto x = obtainValueAtIndex(*runtime, index);
    return x;
//    int byteCount = value.length();
//    jbyte* pNativeMessage = const_cast<jbyte *>(reinterpret_cast<const jbyte *>(value.c_str()));
//    jbyteArray bytes = env->NewByteArray(byteCount);
//    env->SetByteArrayRegion(bytes, 0, byteCount, pNativeMessage);
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_reactnativemmkv_MmkvModule_getValueAtIndexString(JNIEnv *env, jclass clazz, jlong jsiPtr, jint index) {
    auto runtime = reinterpret_cast<jsi::Runtime*>(jsiPtr);
    auto value = obtainValueAtIndexString(*runtime, index);
    int byteCount = value.length();
    jbyte* pNativeMessage = const_cast<jbyte *>(reinterpret_cast<const jbyte *>(value.c_str()));
    jbyteArray bytes = env->NewByteArray(byteCount);
    env->SetByteArrayRegion(bytes, 0, byteCount, pNativeMessage);
    return  bytes;
}
