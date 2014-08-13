LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := JNIEngine
LOCAL_SRC_FILES := JNIEngine.cpp

include $(BUILD_SHARED_LIBRARY)
