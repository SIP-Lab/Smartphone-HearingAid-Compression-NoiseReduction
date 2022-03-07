package com.dsp.matlab;//
//  This copyrighted © code is written for and is part of the book
//  Smartphone-Based Real-Time Digital Signal Processing
//

import android.graphics.Canvas;

import com.androidplot.Plot;
import com.androidplot.PlotListener;
import com.androidplot.xy.XYSeries;

import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.concurrent.locks.ReentrantReadWriteLock;


/**
 * A convenience class used to create instances of XYPlot generated from Lists of Numbers.
 */
public class BetterXYSeries implements XYSeries, PlotListener {

    @SuppressWarnings("rawtypes")
	@Override
    public void onBeforeDraw(Plot source, Canvas canvas) {
        lock.readLock().lock();
    }

    @SuppressWarnings("rawtypes")
	@Override
    public void onAfterDraw(Plot source, Canvas canvas) {
        lock.readLock().unlock();
    }

    public enum ArrayFormat {
        Y_VALS_ONLY,
        XY_VALS_INTERLEAVED
    }

    private volatile LinkedList<Number> yVals = new LinkedList<Number>();
    private volatile String title = null;
    private ReentrantReadWriteLock lock = new ReentrantReadWriteLock(true);


    public BetterXYSeries(String title) {
        this.title = title;
    }


    /**
     * Sets individual y value based on index
     * @param value
     * @param index
     */
    public void setY(Number value, int index) {
        lock.writeLock().lock();
        try {
            yVals.set(index, value);
        } finally {
            lock.writeLock().unlock();
        }
    }

    public void addFirst(Number y) {
        lock.writeLock().lock();
        try {
            yVals.addFirst(y);
        } finally {
            lock.writeLock().unlock();
        }
    }
    
    public void addFloatArray(float[] y){
        lock.writeLock().lock();
        try {
        	int newSize = yVals.size() + y.length;
        	
        	if (newSize > Settings.graphPoints) {
        		yVals.subList(0, (newSize - Settings.graphPoints)).clear();
            }

    		for(int i=0;i<y.length;i++){
    			yVals.addLast(y[i]);
    		}
        } finally {
            lock.writeLock().unlock();
        }
    }
    
    public void replaceFloatArray(float[] y){
        lock.writeLock().lock();
        try {
        	yVals.clear();
    		for(int i=0;i<y.length;i++){
    			yVals.addLast(y[i]);
    		}
        } finally {
            lock.writeLock().unlock();
        }
    }

    /**
     *
     * @return Pair<Number, Number> with first equal to x-val and second equal to y-val.
     */
    public Number removeFirst() {
        lock.writeLock().lock();
        try {
            if (size() <= 0) {
                throw new NoSuchElementException();
            }
            return yVals.removeFirst();
        } finally {
            lock.writeLock().unlock();
        }
    }

    public void addLast(Number y) {
        lock.writeLock().lock();
        try {
            yVals.addLast(y);
        } finally {
            lock.writeLock().unlock();
        }
    }

    /**
     *
     * @return Pair<Number, Number> with first equal to x-val and second equal to y-val.
     */
    public Number removeLast() {
        lock.writeLock().lock();
        try {
            if (size() <= 0) {
                throw new NoSuchElementException();
            }
            return yVals.removeLast();
        } finally {
            lock.writeLock().unlock();
        }
    }

    @Override
    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        lock.writeLock().lock();
        try {
            this.title = title;
        } finally {lock.writeLock().unlock();}
    }

    @Override
    public int size() {
        return yVals != null ? yVals.size() : 0;
    }

    @Override
    public Number getX(int index) {
    	return index*Settings.binStep;
    }

    @Override
    public Number getY(int index) {
        return yVals.get(index);
    }
}

