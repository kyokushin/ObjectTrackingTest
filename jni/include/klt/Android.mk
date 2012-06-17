LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

MY_SRC_FILES := $(wildcard *.c)

LOCAL_MODULE    := klt
LOCAL_SRC_FILES := convolve.c error.c \
			klt.c klt_util.c pnmio.c \
			pyramid.c selectGoodFeatures.c \
			storeFeatures.c trackFeatures.c \
			writeFeatures.c
LOCAL_LDLIBS +=  -llog -ldl -lm
LOCAL_CPP_EXTENSION := .c

include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_SHARED_LIBRARY)
