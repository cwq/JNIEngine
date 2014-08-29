LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LS_CPP=$(subst $(LOCAL_PATH)/,,$(wildcard $(1)/*.cpp))
LOCAL_MODULE    := JNIEngine
ANDROID_SRC_HOME := E:/androidsource/Android4.4
LOCAL_C_INCLUDES += $(ANDROID_SRC_HOME)/hardware/libhardware/include \
$(ANDROID_SRC_HOME)/system/core/include \
$(ANDROID_SRC_HOME)/frameworks/native/include
#LOCAL_SRC_FILES := com_cwq_jni_JNILib.cpp Resource.cpp GraphicsTexture.cpp OpenglESHelper.cpp OpenglESProgram.cpp ComOGLESProgram.cpp TextureManager.cpp
LOCAL_SRC_FILES := $(call LS_CPP,$(LOCAL_PATH))
LOCAL_LDLIBS    := -landroid -llog -lEGL -lGLESv2 -lui
LOCAL_STATIC_LIBRARIES := png

include $(BUILD_SHARED_LIBRARY)

$(call import-module,libpng)