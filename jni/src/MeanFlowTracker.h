#ifndef MeanFlowTracker_h
#define MeanFlowTracker_h

#include "mftrack.h"

namespace ys {

	class MeanFlowTracker {
		public:
			MeanFlowTracker()
				:_klt_ctx(0),_klt_list1(0),_klt_list2(0),
				_old_image(0)
			{}
			~MeanFlowTracker(){
				release();
			}

			void init( unsigned char *image,
					Size &size, Rect *rect );

			void release();

			int update( unsigned char* image, Rect *tracked );

			KLT_FeatureList getF(){
				return _klt_list2;
			}
			void copyImage(
					const unsigned char *src,
					unsigned char *dst, Size &size );

		private:
			KLT_TrackingContext _klt_ctx;
			KLT_FeatureList _klt_list1,_klt_list2;
			Rect _old_track_rect;
			unsigned char *_old_image;
			Size _size;

	};

}
#endif
