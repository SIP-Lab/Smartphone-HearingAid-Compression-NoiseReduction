//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//
package com.dsp.matlab;

import java.util.concurrent.BlockingQueue;
import android.util.Log;

import com.androidplot.util.Redrawer;

public class Filter implements Runnable{
	
	private BlockingQueue<WaveFrame> input;
	private BlockingQueue<WaveFrame> output;
	private Thread filter;
	private static final String TAG = Filter.class.getName();
	private int counter2;
	private int counter1;

	public Filter(BlockingQueue<WaveFrame> input, BlockingQueue<WaveFrame> output) {
		this.input = input;
		this.output = output;
        filter = new Thread(this);
        filter.start();
	}

	public void run() {
		try {
			Filters.initialize(Settings.blockSize);
			loop:while(true) {
				WaveFrame currentFrame = null;
				currentFrame = input.take();
				if(currentFrame == Settings.STOP){
					Filters.finish();
					output.put(currentFrame);
					break loop;
				}
				
				long then = System.nanoTime();
				currentFrame.setFiltered(Filters.compute(currentFrame.getFloats(), Settings.Fs, Settings.overlap, Settings.VAD_threshold, Settings.NR_threshold, Settings.WDRC_low_threshold, Settings.WDRC_upper_threshold));
				currentFrame.setVAD(Filters.getVAD());
				currentFrame.setSPL(Filters.getSPL());
				currentFrame.setFilter(Filters.getFilter());
				long elapsed = System.nanoTime() - then;
				currentFrame.setElapsed(elapsed);
				output.put(currentFrame);

                //Update the graph with data
				if(Settings.graphReady.get()) {
					float [] displayData = currentFrame.getFloats();
					if( ! Settings.output )
					{
						displayData = currentFrame.getFiltered();
					}
					Settings.getDataListener().notifyDataArray(displayData);
				}
			}
		} catch (InterruptedException e) {
			Thread.currentThread().interrupt();
			e.printStackTrace();
		}
	}
}