LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

# LOCAL_SRC_FILES := $(notdir $(wildcard $(LOCAL_PATH)/*.cpp))
LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/Animator.cpp \
				   ../../Classes/GameScene.cpp \
				   ../../Classes/Horse.cpp \
				   ../../Classes/Man.cpp \
				   ../../Classes/MyCamera.cpp \
				   ../../Classes/Objects.cpp \
				   ../../Classes/tile_background.cpp \
				   ../../Classes/UI.cpp \
				   ../../Classes/Pattern.cpp \
				   ../../Classes/LobbyScene.cpp \
				   ../../Classes/TouchChecker.cpp \
				   ../../Classes/WELLRAND.cpp \
				   ../../Classes/Loading.cpp \
				   ../../Classes/Walls.cpp \
				   ../../Classes/PauseLayer.cpp \
                   ../../Classes/AppDelegate.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
