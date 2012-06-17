#include <jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>
#include <android/log.h>

#include "MeanFlowTracker.h"

using namespace std;
using namespace cv;
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     jp_dip_firstnote_objecttrackingtest_MedianTracker
 * Method:    nativeNew
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_jp_dip_firstnote_objecttrackingtest_MedianTracker_nativeNew
  (JNIEnv *, jobject);

/*
 * Class:     jp_dip_firstnote_objecttrackingtest_MedianTracker
 * Method:    nativeInit
 * Signature: (JJIIII)V
 */
JNIEXPORT void JNICALL Java_jp_dip_firstnote_objecttrackingtest_MedianTracker_nativeInit
  (JNIEnv *, jobject, jlong, jlong, jint, jint, jint, jint);

/*
 * Class:     jp_dip_firstnote_objecttrackingtest_MedianTracker
 * Method:    nativeRelease
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_jp_dip_firstnote_objecttrackingtest_MedianTracker_nativeRelease
  (JNIEnv *, jobject, jlong);

/*
 * Class:     jp_dip_firstnote_objecttrackingtest_MedianTracker
 * Method:    nativeUpdate
 * Signature: (JJLorg/opencv/core/Rect;)Z
 */
JNIEXPORT jboolean JNICALL Java_jp_dip_firstnote_objecttrackingtest_MedianTracker_nativeUpdate
  (JNIEnv *, jobject, jlong, jlong, jobject);

#ifdef __cplusplus
}
#endif
