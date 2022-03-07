//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
package com.dsp.matlab;

public class Filters {

	static {
		System.loadLibrary("matlabNative");
	}

	//JNI Method Calls	
	public static native float[] compute(float[] in, int Fs, boolean overlap, float VAD_T, int NR_threshold, int WDRC_Low_Threshold, int WDRC_Upper_Threshold);
	public static native double getVAD();
	public static native double getSPL();
	public static native int getFilter();
	public static native void initialize(int framesize);
	public static native void finish();
}
