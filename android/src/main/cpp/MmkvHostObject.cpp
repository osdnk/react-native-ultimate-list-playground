//
//  MmkvHostObject.cpp
//  Mmkv
//
//  Created by Marc Rousavy on 03.09.21.
//  Copyright © 2021 Facebook. All rights reserved.
//

#include "MmkvHostObject.h"
#include <MMKV.h>
#include <android/log.h>

//std::optional<jsi::Array> sampleArray;


MmkvHostObject::MmkvHostObject(const std::string& instanceId, const std::string& path, const std::string& cryptKey) {
  __android_log_print(ANDROID_LOG_INFO, "RNMMKV", "Creating MMKV instance \"%s\"... (Path: %s, Encryption-Key: %s)",
                      instanceId.c_str(), path.c_str(), cryptKey.c_str());
  this->path = path.size() > 0 ? new std::string(path) : nullptr;
  this->encryptionKey = cryptKey.size() > 0 ? new std::string(cryptKey) : nullptr;
  instance = MMKV::mmkvWithID(instanceId, mmkv::DEFAULT_MMAP_SIZE, MMKV_SINGLE_PROCESS, this->path, this->encryptionKey);
  if (instance == nullptr) {
    throw std::runtime_error("Failed to create MMKV instance!");
  }
}

MmkvHostObject::~MmkvHostObject() {
  instance->close(); // also calls destructor
  if (path) {
    delete path;
  }
  if (encryptionKey) {
    delete encryptionKey;
  }
}

std::vector<jsi::PropNameID> MmkvHostObject::getPropertyNames(jsi::Runtime& rt) {
  std::vector<jsi::PropNameID> result;
  result.push_back(jsi::PropNameID::forUtf8(rt, std::string("set")));
  result.push_back(jsi::PropNameID::forUtf8(rt, std::string("getBoolean")));
  result.push_back(jsi::PropNameID::forUtf8(rt, std::string("getString")));
  result.push_back(jsi::PropNameID::forUtf8(rt, std::string("getNumber")));
  result.push_back(jsi::PropNameID::forUtf8(rt, std::string("delete")));
  result.push_back(jsi::PropNameID::forUtf8(rt, std::string("getAllKeys")));
  result.push_back(jsi::PropNameID::forUtf8(rt, std::string("deleteAll")));
  return result;
}

jsi::Value MmkvHostObject::get(jsi::Runtime& runtime, const jsi::PropNameID& propNameId) {
  auto propName = propNameId.utf8(runtime);
  auto funcName = "MMKV." + propName;

    if (propName == "setArray") {
        // MMKV.set(key: string, value: string | number | bool)
        return jsi::Function::createFromHostFunction(runtime,
                                                     jsi::PropNameID::forAscii(runtime, funcName),
                                                     1,  // key, value
                                                     [this](jsi::Runtime& runtime,
                                                            const jsi::Value& thisValue,
                                                            const jsi::Value* arguments,
                                                            size_t count) -> jsi::Value {
                                                         sampleArray = arguments[0].getObject(runtime).getArray(runtime);
                                                         //jsi::Array* x = (jsi::Array*) arguments[0];

//                                                         if (arguments[1]) {
//
//                                                         }
//const auto x = arguments[0];

                                                         return jsi::Value::undefined();
                                                     });
    }

    if (propName == "setArraySize") {
        return jsi::Function::createFromHostFunction(runtime,
                                                     jsi::PropNameID::forAscii(runtime, funcName),
                                                     1,  // key
                                                     [this](jsi::Runtime& runtime,
                                                            const jsi::Value& thisValue,
                                                            const jsi::Value* arguments,
                                                            size_t count) -> jsi::Value {
            auto v = arguments[0].asNumber();
            arraySize = v;
                                                         return jsi::Value::undefined();

                                                     });
    }

    if (propName == "getKluska") {
        return jsi::Function::createFromHostFunction(runtime,
                                                     jsi::PropNameID::forAscii(runtime, funcName),
                                                     1,  // key
                                                     [this](jsi::Runtime& runtime,
                                                            const jsi::Value& thisValue,
                                                            const jsi::Value* arguments,
                                                            size_t count) -> jsi::Value {
                                                            return jsi::Value(runtime, jsi::String::createFromUtf8(runtime, "Klucha"));
                                                     });
    }

  return jsi::Value::undefined();
}
