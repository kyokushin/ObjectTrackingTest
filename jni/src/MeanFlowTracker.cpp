#include "MeanFlowTracker.h"


#include <iostream>
using namespace std;
void ys::MeanFlowTracker::init( unsigned char *image,
		Size &size, Rect *rect ){
#ifdef DEBUG
	cout<< "*** init: ***" <<endl;
#endif


	_klt_ctx = KLTCreateTrackingContext();
	_klt_ctx->sequentialMode = TRUE;
	//_klt_ctx->nPyramidLevels = 2;
	//_klt_ctx->nSkippedPixels = 2;
	//KLTSetVerbosity( 0 );

	_klt_list1 = KLTCreateFeatureList(100);
	_klt_list2 = KLTCreateFeatureList(100);

	_old_image = new unsigned char[size.width*size.height];
	copyImage( image, _old_image, size );

	_size = size;
	_old_track_rect = *rect;

	//KLTSelectGoodFeatures( _klt_ctx, (KLT_PixelType*)_old_image,
	KLTSelectGoodFeatures( _klt_ctx, (KLT_PixelType*)_old_image,
			size.width, size.height, _klt_list2 );

	printKLTFeature( _klt_list2 );

#ifdef DEBUG
	cout<< "--- init: ---" <<endl;
#endif
}

void ys::MeanFlowTracker::release(){
	if( _klt_ctx ){
		KLTFreeTrackingContext( _klt_ctx );
		_klt_ctx = 0;
	}
	if( _klt_list1 ){
		KLTFreeFeatureList( _klt_list1 );
		_klt_list1 = 0;
	}
	if( _klt_list2 ){
		KLTFreeFeatureList( _klt_list2 );
		_klt_list2 = 0;
	}
	if( _old_image ){
		delete[] _old_image;
	}
}

int ys::MeanFlowTracker::update( unsigned char* image, Rect *tracked ){

#ifdef DEBUG
	cout<< "*** update ***" <<endl;
#endif

	//2->1へ
	copyKLTFeature( _klt_list2, _klt_list1);

	int result = klttrack( _old_image, _size,
			image, _size,
			_old_track_rect,
			_klt_ctx, _klt_list1, _klt_list2, tracked);

	//printKLTFeature( _klt_list2 );

	copyImage( image, _old_image, _size );

	_old_track_rect = *tracked;

	KLTReplaceLostFeatures(
			_klt_ctx,
			image, _size.width, _size.height,
			_klt_list2 );
#ifdef DEBUG
	cout<< "--- update ---" <<endl;
#endif
	return result;
}


void ys::MeanFlowTracker::copyImage(
		const unsigned char *src,
		unsigned char *dst, Size &size ){

	for( int i=0; i<size.height*size.width; i++ ){
			dst[i] = src[i];
	}
}



