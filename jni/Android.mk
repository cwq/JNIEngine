LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LS_CPP=$(subst $(LOCAL_PATH)/,,$(wildcard $(1)/*.cpp))

LOCAL_MODULE    := JNIEngine

#LOCAL_SRC_FILES := com_cwq_jni_JNILib.cpp Resource.cpp GraphicsTexture.cpp OpenglESHelper.cpp OpenglESProgram.cpp ComOGLESProgram.cpp TextureManager.cpp
LOCAL_SRC_FILES := $(call LS_CPP,$(LOCAL_PATH))
LOCAL_LDLIBS    := -landroid -llog -lEGL -lGLESv2
LOCAL_STATIC_LIBRARIES := png

include $(BUILD_SHARED_LIBRARY)

$(call import-module,libpng)