package com.dsp.matlab;//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;

import com.androidplot.Plot;
import com.androidplot.util.Redrawer;
import com.androidplot.xy.BoundaryMode;
import com.androidplot.xy.LineAndPointFormatter;
import com.androidplot.xy.StepMode;
import com.androidplot.xy.XYPlot;

import java.util.Arrays;

public class DataGraphActivity extends Activity implements DataListener
{
    private XYPlot dataPlot = null;
    private BetterXYSeries dataSeries = null;
    private Redrawer redrawer;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.datagraph);
        
        dataPlot = (XYPlot) findViewById(R.id.dataPlot);
        dataPlot.setRangeBoundaries(0, 1, BoundaryMode.GROW);
        //fs/2 in khz //since we're doing time series
        // limit to window size
        dataPlot.setDomainBoundaries(0, (float)Settings.blockSize/Settings.Fs, BoundaryMode.FIXED);
        //dataPlot.setDomainBoundaries(0, (Settings.Fs*.001f)/2, BoundaryMode.FIXED);
        dataPlot.setDomainStep(StepMode.SUBDIVIDE, 11);
        dataPlot.setRangeStep(StepMode.SUBDIVIDE, 11);
        dataPlot.setLinesPerRangeLabel(1);
        dataPlot.setDomainLabel( Settings.getOutput() );
        dataPlot.getDomainTitle().pack();
        dataPlot.setRangeLabel("Amplitude");
        dataPlot.getRangeTitle().pack();

        //FIXME and where did these go?
//        dataPlot.setRangeValueFormat(new DecimalFormat("#.#"));
//        dataPlot.setDomainValueFormat(new DecimalFormat("#.#"));
        
        dataPlot.getLayoutManager().remove(dataPlot.getLegend());

        dataSeries = new BetterXYSeries("Time Series");
    	dataPlot.addSeries(dataSeries, new LineAndPointFormatter(Color.rgb(100, 230, 50), null, null, null));
    	Settings.graphListener(this);
    	Settings.graphReady.set(true);

    	redrawer = new Redrawer(Arrays.asList(new Plot[]{dataPlot}), 60, false);
    }

    public void onResume() {
    	super.onResume();
        dataPlot.setDomainLabel( Settings.getOutput() );
    	redrawer.start();
    }

    public void onPause() {
    	Settings.graphReady.set(false);
    	redrawer.pause();
        super.onPause();
    }

    public void onDestroy() {
        dataSeries = null;
        dataPlot = null;
        Settings.graphListener(null);
        Settings.graphReady.set(false);
        redrawer.finish();
        super.onDestroy();
    }

    public synchronized void notifyDataArray(float[] dataValues) {
		dataSeries.replaceFloatArray(dataValues);
    }
}