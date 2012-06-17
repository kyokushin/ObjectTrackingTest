package jp.dip.firstnote.objecttrackingtest;

import org.opencv.android.Utils;
import org.opencv.core.Mat;
import org.opencv.core.Rect;
import org.opencv.core.CvType;

public class MedianTracker {

	private long trackerAddr;
	
	public MedianTracker(){
		trackerAddr = nativeNew();
	}
	public void init( Mat mat, Rect rect ){
		nativeInit( trackerAddr, mat.getNativeObjAddr(), rect.x, rect.y, rect.x + rect.width, rect.y + rect.height);
	}
	
	public void release(){
		nativeRelease( trackerAddr );
	}
	
	public boolean update( Mat mat, Rect rect ){
		return nativeUpdate( trackerAddr, mat.getNativeObjAddr(), rect);
	}

	private native long nativeNew();
	private native void nativeInit( long trackerAddr, long matAddr, int sx, int sy, int ex, int ey);
	private native void nativeRelease( long trackerAddr);
	private native boolean nativeUpdate( long trackerAddr, long  matAddr, Rect rect );
	
	static {
		System.loadLibrary("mediantracker");
	}
	
}
