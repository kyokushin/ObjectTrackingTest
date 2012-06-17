
#include <iostream>

#include <cmath>
#include <assert.h>
#include <algorithm>

#include "mftrack.h"
#include "median.h"

void ys::printKLTFeature( KLT_FeatureList list, int n){

	for( int i=0; i<n; i++ ){
		KLT_Feature f = list->feature[i];
		std::cout<< "\t" << f->x << ","
			<< f->y
			<< ":" << f->val<<std::flush;

		std::cout<<std::endl;

	}
}

template<class T>
void printArray(const T *a, int n){
	for(int ii=0; ii<n; ii++){
		std::cout << "[" << ii << ":" << a[ii] << "]" <<std::flush;
	}

}
template<class T>
void printArray(const T *a, int n, int i, int j, int k, int l, int r ){
	for(int ii=0; ii<n; ii++){
		if( ii == l ) std::cout<< "{" <<std::flush;
		std::cout << "[" << a[ii] << "]" <<std::flush;
		if( ii == r ) std::cout<< "}" <<std::flush;
	}
	std::cout<< ",i:" << i << ",j:" << j << ",mpos:" << k <<std::endl;

}

void ys::copyKLTFeature( const KLT_FeatureList src, KLT_FeatureList dist ){
	int n = src->nFeatures;
	for( int i=0; i<n; i++ ){
		KLT_Feature df = dist->feature[i];
		KLT_Feature sf = src->feature[i];
		df->x = sf->x;
		df->y = sf->y;
		df->val = sf->val;
	}

}

float ys::nccRect( const unsigned char *src1, const Size &size1, const Point &p1,
		   	const unsigned char *src2, const Size &size2, const Point &p2,
			const CRect &ncc_rect){
	float den = 0.0;
	float num1 = 0.0, num2 = 0.0;
	
	for( int i=ncc_rect.ch_start; i<ncc_rect.ch_end; i++ ){
		for( int h=ncc_rect.cw_start; h<ncc_rect.cw_end; h++ ){
			unsigned char val1 = src1[(p1.y + i)*size1.width + h + p1.x];
		   	unsigned char val2 = src2[(p2.y + i)*size2.width + h + p2.x];
			den += val1 * val2;
			num1 += val1 * val1;
			num2 += val2 * val2;
		}
	}
	
	return den/sqrt( num1 * num2 );
}


int ys::predictScaleMove( const KLT_FeatureList list1,
		   const KLT_FeatureList list2, const ys::Rect &track, 
			float *scale, ys::Point *moved ){

	assert( list1->nFeatures == list2->nFeatures );
	assert( scale != NULL );
	assert( moved != NULL );

	int n = list1->nFeatures;

	float *scales = new float[n*(n-1)/2];
	int *ofx = new int[n];
	int *ofy = new int[n];

	int count_s = 0;
	int count_m = 0;
	for(int i=0; i<n; i++){
		KLT_Feature f1i = list1->feature[i];
		KLT_Feature f2i = list2->feature[i];
		if( f2i->val != KLT_TRACKED
				|| f1i->x < track.sx || track.ex <= f1i->x
				|| f1i->y < track.sy || track.ey <= f1i->y
				)		
			continue;//トラックできたscaleだけ分かれば良い
		
		for( int j=0; j<i; j++ ){
			KLT_Feature f1j = list1->feature[j];
			KLT_Feature f2j = list2->feature[j];
			if( f2j->val != KLT_TRACKED
				|| f1j->x < track.sx || track.ex <= f1j->x
				|| f1j->y < track.sy || track.ey <= f1j->y
			  )
				continue;//トラックできたscaleだけ分かれば良い

			//2点間の距離を計算
			int sub_x = f1i->x - f1j->x;
			int sub_y = f1i->y - f1j->y;
			float distance1 = sqrt(sub_x * sub_x + sub_y * sub_y);

			sub_x = f2i->x - f2j->x;
			sub_y = f2i->y - f2j->y;
			float distance2 = sqrt(sub_x * sub_x + sub_y * sub_y);

			//スケールを計算
			scales[ count_s ] = distance2 / distance1;
			count_s++;
		}

		ofx[count_m] = f2i->x - f1i->x;
		ofy[count_m] = f2i->y - f1i->y;
		count_m++;
	}
	*scale = median<float>( scales, count_s );
	moved->x = median<int>( ofx, count_m );
	moved->y = median<int>( ofy, count_m );


	delete[] scales;
	delete[] ofx;
	delete[] ofy;

	return count_m;
}

int ys::predictScaleMove2( const KLT_FeatureList list1,
		   const KLT_FeatureList list2, const ys::Rect &track, 
			float *scale, ys::Point *moved ){

	float avg_x = 0;
	float avg_y = 0;
	float avg_scale = 0;
	int count_m = 0;
	int count_s = 0;
	for( int i=0; i<list1->nFeatures; i++ ){
		KLT_Feature f1i = list1->feature[i];
		KLT_Feature f2i = list2->feature[i];

		if( f2i->val != KLT_TRACKED
				|| f1i->x < track.sx || track.ex <= f1i->x
				|| f1i->y < track.sy || track.ey <= f1i->y
				)		
			continue;

		for( int j=0; j<i; j++ ){
			KLT_Feature f1j = list1->feature[j];
			KLT_Feature f2j = list2->feature[j];
			if( f2j->val != KLT_TRACKED
				|| f1j->x < track.sx || track.ex <= f1j->x
				|| f1j->y < track.sy || track.ey <= f1j->y
			  )
				continue;//トラックできたscaleだけ分かれば良い

			//2点間の距離を計算
			int sub_x = f1i->x - f1j->x;
			int sub_y = f1i->y - f1j->y;
			float distance1 = sqrt(sub_x * sub_x + sub_y * sub_y);

			sub_x = f2i->x - f2j->x;
			sub_y = f2i->y - f2j->y;
			float distance2 = sqrt(sub_x * sub_x + sub_y * sub_y);

			//スケールを計算
			avg_scale += distance2/distance1;
			count_s++;
		}

		avg_x += f2i->x - f1i->x;
		avg_y += f2i->y - f1i->y;
		count_m++;
	}
	avg_x /= count_m;
	avg_y /= count_m;
	moved->x = avg_x + 0.5;
	moved->y = avg_y + 0.5;
	*scale = avg_scale / count_s;

	return count_m;
}

#define MOVE_AVERAGE
int ys::klttrack( const unsigned char *image1, const ys::Size &size1,
		const unsigned char *image2, const ys::Size &size2,
		const ys::Rect &start_rect,
		KLT_TrackingContext context,
		KLT_FeatureList list1,
		KLT_FeatureList list2,
		ys::Rect *tracked_rect){

	assert( list1->nFeatures > 0 );
	assert( list1->nFeatures == list2->nFeatures );

	for( int i=0; i<list1->nFeatures; i++ ){
		list2->feature[i]->x = list1->feature[i]->x;
		list2->feature[i]->y = list1->feature[i]->y;
		list2->feature[i]->val = list1->feature[i]->val;
	}


	KLTTrackFeatures( context, (KLT_PixelType*)image1, (KLT_PixelType*)image2, size1.width, size1.height, list2 );
	
	
	float scale;
	ys::Point moved;
	int count_m = predictScaleMove( list1, list2, start_rect, &scale, &moved );

	float sx =  0.5*( scale - 1 ) * (start_rect.ex - start_rect.sx);
	float sy =  0.5*( scale - 1 ) * (start_rect.ey - start_rect.sy);

	tracked_rect->sx = start_rect.sx - sx + moved.x;
	tracked_rect->sy = start_rect.sy - sy + moved.y;
	tracked_rect->ex = start_rect.ex + sx + moved.x;
	tracked_rect->ey = start_rect.ey + sy + moved.y;


	return count_m;
}

int ys::mftrack( const unsigned char *image1, const ys::Size &size1,
		const unsigned char *image2, const ys::Size &size2,
		const ys::Rect &start_rect,
		KLT_TrackingContext context,
		KLT_FeatureList list1,
		KLT_FeatureList list2,
		ys::Rect *tracked_rect){

	assert( list1->nFeatures == list2->nFeatures );
	for( int i=0; i<list1->nFeatures; i++ ){
		list2->feature[i]->x = list1->feature[i]->x;
		list2->feature[i]->y = list1->feature[i]->y;
		list2->feature[i]->val = list1->feature[i]->val;
	}

	KLTTrackFeatures( context, (KLT_PixelType*)image1, (KLT_PixelType*)image2, size1.width, size1.height, list2 );

	float scale;
	ys::Point moved;
	int result = predictScaleMove( list1, list2, start_rect, &scale, &moved );

	float sx = 0.5 * ( scale - 1 ) * (start_rect.ex - start_rect.sx);
	float sy = 0.5 * ( scale - 1 ) * (start_rect.ey - start_rect.sy);

	tracked_rect->sx = start_rect.sx - sx + moved.x;
	tracked_rect->sy = start_rect.sy - sy + moved.y;
	tracked_rect->ex = start_rect.ex + sx + moved.x;
	tracked_rect->ey = start_rect.ey + sy + moved.y;


	return result;
}
