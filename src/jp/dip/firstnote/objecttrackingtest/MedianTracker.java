package jp.dip.firstnote.objecttrackingtest;

import org.opencv.android.Utils;
import org.opencv.core.Mat;
import org.opencv.core.Rect;
import org.opencv.core.CvType;

public class MedianTracker {

	private long trackerAddr;
	
	public native void nativeInit( long matAddr, Rect rect );
	public native void nativeRelease();
	public native void nativeUpdate( long  matAddr, Rect rect );
	
	static {
		System.loadLibrary("mediantracker");
	}
	
}
