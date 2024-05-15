/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT License.
 */
#include <jni.h>
#include "ort_genai_c.h"
#include "utils.h"

using namespace Helpers;

extern "C" JNIEXPORT jlong JNICALL
Java_ai_onnxruntime_1genai_GeneratorParams_createGeneratorParams(JNIEnv* env, jobject thiz, jlong model_handle) {
  const OgaModel* model = reinterpret_cast<const OgaModel*>(model_handle);
  OgaGeneratorParams* generator_params = nullptr;
  ThrowIfError(env, OgaCreateGeneratorParams(model, &generator_params));

  return reinterpret_cast<jlong>(generator_params);
}

extern "C" JNIEXPORT void JNICALL
Java_ai_onnxruntime_1genai_GeneratorParams_destroyGeneratorParams(JNIEnv* env, jobject thiz, jlong native_handle) {
  OgaGeneratorParams* generator_params = reinterpret_cast<OgaGeneratorParams*>(native_handle);
  OgaDestroyGeneratorParams(generator_params);
}

extern "C" JNIEXPORT void JNICALL
Java_ai_onnxruntime_1genai_GeneratorParams_setSearchOptionNumber(JNIEnv* env, jobject thiz, jlong native_handle,
                                                                 jstring option_name, jdouble value) {
  OgaGeneratorParams* generator_params = reinterpret_cast<OgaGeneratorParams*>(native_handle);
  CString name{env, option_name};

  ThrowIfError(env, OgaGeneratorParamsSetSearchNumber(generator_params, name, value));
}

extern "C" JNIEXPORT void JNICALL
Java_ai_onnxruntime_1genai_GeneratorParams_setSearchOptionBool(JNIEnv* env, jobject thiz, jlong native_handle,
                                                               jstring option_name, jboolean value) {
  OgaGeneratorParams* generator_params = reinterpret_cast<OgaGeneratorParams*>(native_handle);
  CString name{env, option_name};

  ThrowIfError(env, OgaGeneratorParamsSetSearchBool(generator_params, name, value));
}

extern "C" JNIEXPORT void JNICALL
Java_ai_onnxruntime_1genai_GeneratorParams_setInputSequences(JNIEnv* env, jobject thiz, jlong native_handle,
                                                             jlong sequences_handle) {
  OgaGeneratorParams* generator_params = reinterpret_cast<OgaGeneratorParams*>(native_handle);
  const OgaSequences* sequences = reinterpret_cast<const OgaSequences*>(sequences_handle);

  ThrowIfError(env, OgaGeneratorParamsSetInputSequences(generator_params, sequences));
}

extern "C" JNIEXPORT void JNICALL
Java_ai_onnxruntime_1genai_GeneratorParams_setInputIDs(JNIEnv* env, jobject thiz, jlong native_handle,
                                                       jintArray tokenIds, jint sequenceLength, jint batchSize) {
  OgaGeneratorParams* generator_params = reinterpret_cast<OgaGeneratorParams*>(native_handle);

  auto num_tokens = env->GetArrayLength(tokenIds);
  jint* jtokens = env->GetIntArrayElements(tokenIds, nullptr);
  const int32_t* tokens = reinterpret_cast<const int32_t*>(jtokens);  // convert between 32-bit types

  ThrowIfError(env, OgaGeneratorParamsSetInputIDs(generator_params, tokens, num_tokens, sequenceLength, batchSize));
}