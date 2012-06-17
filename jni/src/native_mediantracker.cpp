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
  (JNIEnv *env, jobject thiz){
	ys::MeanFlowTracker *trackerP = new ys::MeanFlowTracker();
	return (jlong)trackerP;
}

/*
 * Class:     jp_dip_firstnote_objecttrackingtest_MedianTracker
 * Method:    nativeInit
 * Signature: (JJIIII)V
 */
JNIEXPORT void JNICALL Java_jp_dip_firstnote_objecttrackingtest_MedianTracker_nativeInit
  (JNIEnv *env, jobject thiz, jlong trackerAddr, jlong matAddr, jint sx, jint sy, jint ex, jint ey){

	ys::MeanFlowTracker *trackerP = (ys::MeanFlowTracker*)trackerAddr;
	cv::Mat *image = (Mat*)matAddr;
	ys::Size size( image->cols, image->rows );
	ys::Rect rect;
	rect.sx = sx; rect.sy = sy; rect.ex = ex; rect.ey;

	trackerP->init( image->data, size, &rect );
}

/*
 * Class:     jp_dip_firstnote_objecttrackingtest_MedianTracker
 * Method:    nativeRelease
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_jp_dip_firstnote_objecttrackingtest_MedianTracker_nativeRelease
  (JNIEnv *env, jobject thiz, jlong trackerAddr){

	ys::MeanFlowTracker *trackerP = (ys::MeanFlowTracker*)trackerAddr;
	delete trackerP;
}

/*
 * Class:     jp_dip_firstnote_objecttrackingtest_MedianTracker
 * Method:    nativeUpdate
 * Signature: (JJLorg/opencv/core/Rect;)Z
 */
JNIEXPORT jboolean JNICALL Java_jp_dip_firstnote_objecttrackingtest_MedianTracker_nativeUpdate
  (JNIEnv *env, jobject thiz, jlong trackerAddr, jlong matAddr, jobject rectObj){

	ys::MeanFlowTracker *trackerP = (ys::MeanFlowTracker*)trackerAddr;
	cv::Mat *image = (Mat*)trackerAddr;

	//TODO:ここでトラッキングの処理。
	ys::Rect trackedRect;

	trackerP->update( image->data, &trackedRect );

	//トラッキング処理完了後、値の受け渡し
	jclass rectClass = env->GetObjectClass(rectObj);
	jfieldID fId = env->GetFieldID(rectClass, "x", "I" );
	env->SetIntField( rectObj, fId, (jint)trackedRect.sx );

	fId = env->GetFieldID( rectClass, "y", "I" );
	env->SetIntField( rectObj, fId, (jint)trackedRect.sy );

	fId = env->GetFieldID( rectClass, "width", "I" );
	env->SetIntField( rectObj, fId, (jint)(trackedRect.ex - trackedRect.sx ));

	fId = env->GetFieldID( rectClass, "height", "I" );
	env->SetIntField( rectObj, fId, (jint)(trackedRect.ey - trackedRect.sy ));

}

#ifdef __cplusplus
}
#endif
