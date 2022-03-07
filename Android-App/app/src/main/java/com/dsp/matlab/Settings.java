//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
package com.dsp.matlab;

import android.media.AudioFormat;
import android.media.MediaRecorder;

import java.util.concurrent.atomic.AtomicBoolean;

public class Settings {
	
	public static final WaveFrame STOP = new WaveFrame(new float[1], -32768);

	//recorder settings
	public static final int FORMAT = AudioFormat.ENCODING_PCM_16BIT;
	public static final int SOURCE = MediaRecorder.AudioSource.DEFAULT;
	public static int Fs = 8000;
	public static int blockSize = 256;
	public static int delay = 0;
	public static boolean playback = false;
	public static boolean output = false;
	public static int debugLevel = 4;

	public static boolean overlap = false;
	public static float VAD_threshold = 0.75f;
	public static int NR_threshold = 55;
	public static int WDRC_low_threshold = 50;
	public static int WDRC_upper_threshold = 75;

	public static int secondConstant = Fs/blockSize;
	//Graph items
	public static int graphPoints = blockSize;
	private static DataListener graphListener;
	public static AtomicBoolean graphReady = new AtomicBoolean(false);
	public static float binStep = 1.f/Fs;
	private static Monitor main;
	//Graph items

	public static CharSequence[] samplingRates = {"8000 Hz"};
	public static CharSequence[] samplingRateValues = {"8000"};
	
	public static void setDelay(int time){
		delay = time;
	}

	public static void setBlockSize(int framesize1){blockSize=framesize1;}

	public static void setSamplingFrequency(int freq){
		Fs = freq;
		secondConstant = Fs/blockSize;
		binStep = 1.f/Fs;
	}
	public static void setOverlap(boolean overLap){overlap = overLap;}
	public static void setVAD_threshold(float vadthreshold){VAD_threshold = vadthreshold;}
	public static void setNR_threshold(int nr_threshold){NR_threshold = nr_threshold;}
	public static void setWDRC_low_threshold(int wdrc_low_threshold){WDRC_low_threshold = wdrc_low_threshold;}
	public static void setWDRC_upper_threshold(int wdrc_upper_threshold){WDRC_upper_threshold = wdrc_upper_threshold;}

	public static void setCallbackInterface(Monitor uiInterface) {
		main = uiInterface;
	}
	public static Monitor getCallbackInterface() {
		return main;
	}

	public static void graphListener(DataListener listener) {
		graphListener = listener;
	}

	public static DataListener getDataListener(){
		return graphListener;
	}

	public static void setPlayback(boolean flag){
		playback = flag;
	}
	
	public static void setOutput(int stream){
		output = false; //filtered signal
		if(stream == 1){
			output = true; //original signal
		}
	}
	
	public static String getOutput(){
		if (output == true){
			return "Original";
		} else {
			return "Filtered";
		}
	}
	
	public static void setDebugLevel(int level){
		debugLevel = level;
	}
	
	public static void setRates(CharSequence[] rates){
		samplingRates = rates;
	}
	
	public static void setRateValues(CharSequence[] rateValues){
		samplingRateValues = rateValues;
	}
}
