#include <jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>
#include <android/log.h>

#include "MeanFlowTracker.h"

using namespace std;
using namespace cv;

extern "C" {

/*
 * Class:     jp_dip_firstnote_objecttrackingtest_MedianTracker
 * Method:    nativeInit
 * Signature: (JLorg/opencv/core/Rect;)V
 */
JNIEXPORT void JNICALL Java_jp_dip_firstnote_objecttrackingtest_MedianTracker_nativeInit
(JNIEnv *env, jobject thiz, jlong matAddr, jobject rectObj)
{
	__android_log_write( ANDROID_LOG_DEBUG,"Tag","call init");

}

/*
 * Class:     jp_dip_firstnote_objecttrackingtest_MedianTracker
 * Method:    nativeRelease
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jp_dip_firstnote_objecttrackingtest_MedianTracker_nativeRelease
  (JNIEnv *env, jobject thiz)
{

	__android_log_write( ANDROID_LOG_DEBUG,"Tag","call release");

}

/*
 * Class:     jp_dip_firstnote_objecttrackingtest_MedianTracker
 * Method:    nativeUpdate
 * Signature: (JLorg/opencv/core/Rect;)V
 */
JNIEXPORT void JNICALL Java_jp_dip_firstnote_objecttrackingtest_MedianTracker_nativeUpdate
  (JNIEnv *env, jobject thiz, jlong matAddr, jobject rectObj)
{

	__android_log_write( ANDROID_LOG_DEBUG,"Tag","call update");

}
}
