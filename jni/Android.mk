LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := JNIEngine
LOCAL_SRC_FILES := JNIEngine.cpp Resource.cpp GraphicsTexture.cpp OpenglESHelper.cpp OpenglESProgram.cpp ComOGLESProgram.cpp
LOCAL_LDLIBS    := -landroid -llog -lGLESv2
LOCAL_STATIC_LIBRARIES := png

include $(BUILD_SHARED_LIBRARY)

$(call import-module,libpng)