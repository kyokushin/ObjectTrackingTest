package jp.dip.firstnote.objecttrackingtest;

import org.opencv.core.CvType;
import org.opencv.core.Mat;

import android.content.Context;
import android.graphics.Bitmap;
import android.view.SurfaceHolder;

public class TrackerView extends CameraViewBase {

    private Mat mYuv;
    private Mat mRgba;
    private Mat mGraySubmat;
    private Mat mIntermediateMat;
    
	public TrackerView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected Bitmap processFrame(byte[] data) {
		// TODO Auto-generated method stub
		return null;
	}
	@Override
    public void surfaceChanged(SurfaceHolder _holder, int format, int width, int height) {
        super.surfaceChanged(_holder, format, width, height);

        synchronized (this) {
            // initialize Mats before usage
            mYuv = new Mat(getFrameHeight() + getFrameHeight() / 2, getFrameWidth(), CvType.CV_8UC1);
            mGraySubmat = mYuv.submat(0, getFrameHeight(), 0, getFrameWidth());

            mRgba = new Mat();
            mIntermediateMat = new Mat();
        }
    }
	
	
	@Override
    public void run() {
        super.run();

        synchronized (this) {
            // Explicitly deallocate Mats
            if (mYuv != null)
                mYuv.release();
            if (mRgba != null)
                mRgba.release();
            if (mGraySubmat != null)
                mGraySubmat.release();
            if (mIntermediateMat != null)
                mIntermediateMat.release();

            mYuv = null;
            mRgba = null;
            mGraySubmat = null;
            mIntermediateMat = null;
        }
    }
}
