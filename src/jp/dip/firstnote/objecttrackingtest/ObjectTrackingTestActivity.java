package jp.dip.firstnote.objecttrackingtest;

import org.opencv.core.Mat;
import org.opencv.core.Rect;

import android.app.Activity;
import android.os.Bundle;

public class ObjectTrackingTestActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        Mat mat = new Mat( 320,240, 1);
        Rect rect = new Rect();
        
        MedianTracker tracker = new MedianTracker();
        tracker.init(mat, rect);
        tracker.release();
        tracker.update(mat, rect);
    }
}