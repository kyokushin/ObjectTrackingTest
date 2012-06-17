LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

OPENCV_CAMERA_MODULES:=off
OPENCV_MK_PATH:=$(LOCAL_PATH)/../../../OpenCV-2.3.1/share/OpenCV/OpenCV.mk

include $(OPENCV_MK_PATH)

LOCAL_MODULE    := mediantracker

MY_PREFIX := $(LOCAL_PATH)
LOCAL_SRC_FILES :=  native_mediantracker.cpp MeanFlowTracker.cpp mftrack.cpp
LOCAL_STATIC_LIBRARIES := libklt
#LOCAL_SHARED_LIBRARIES := libklt
LOCAL_LDLIBS +=  -llog -ldl

include $(BUILD_SHARED_LIBRARY)