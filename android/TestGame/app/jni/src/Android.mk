LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

# Add your application source files here...
LOCAL_SRC_FILES := \
        Animation.cpp
        AssetManager.cpp
        Collision.cpp
        Entity.cpp
        EntityManager.cpp
        FontManager.cpp
        Game.cpp
        Main.cpp
        Map.cpp
        TextureManager.cpp

LOCAL_SHARED_LIBRARIES := SDL2 \
SDL2_image \
SDL2_mixer \
SDL2_ttf \
SDL2_net

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
