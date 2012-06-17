#include "../include/klt/klt.h"
#ifndef mftrack_h
#define mftrack_h

namespace ys {
	struct Point {
		int x;
		int y;
		Point(int x,int y): x(x), y(y){}
		Point(){}
	};
	struct Size {
		int width;
		int height;
		Size( int width, int height ): width(width), height(height){}
		Size(){}
	};
	struct Rect {
		int sx,sy;
		int ex,ey;
	};
	struct CRect{
		int width;
		int height;
		int cw_start;
		int cw_end;
		int ch_start;
		int ch_end;
		CRect( int w, int h ):
			width(w),height(h){
				cw_start = -width/2;
				cw_end = width + cw_start;
				ch_start = -height/2;
				ch_end = height + ch_start;
			}
	};

	void printKLTFeature( KLT_FeatureList list, int n=10 );

	void copyKLTFeature( const KLT_FeatureList src, KLT_FeatureList dst );

	//指定した領域同士のNCCを計算する
	//src1, src2:NCCを計算する画像
	//p1,p2:NCCを計算する領域の中心座標
	//size:NCCを計算するサイズ
	float nccRect( const unsigned char *src1, const Size &size1, const Point &p1,
		   	const unsigned char *src2, const Size &size2, const Point &p2,
		   	const CRect &ncc_rect);

	int predictScaleMove( const KLT_FeatureList list1,
		   const KLT_FeatureList list2, const ys::Rect &track,
			float *scale, ys::Point *moved );

	int predictScaleMove2( const KLT_FeatureList list1,
		   const KLT_FeatureList list2, const ys::Rect &track,
			float *scale, ys::Point *moved );

	//MedianFlowTrackerを行う
	//image1, size1:トラッキング開始画像
	//image2, size2:トラッキング対象画像
	//nPoint:トラッキングに利用する特徴点の数
	//start_rect:トラッキング対象となる矩形
	//tracked_rect:トラッキングされた矩形
	int klttrack( const unsigned char *image1, const ys::Size &size1,
			const unsigned char *image2, const ys::Size &size2,
			const ys::Rect &start_rect,
			KLT_TrackingContext context,
			KLT_FeatureList list1,
			KLT_FeatureList list2,
			ys::Rect *tracked_rect);

	int mftrack( const unsigned char *image1, const ys::Size &size1,
			const unsigned char *image2, const ys::Size &size2,
			const ys::Rect &start_rect,
			KLT_TrackingContext context,
			KLT_FeatureList lsit1,
			KLT_FeatureList list2,
			ys::Rect *tracked_rect);

}
#endif
