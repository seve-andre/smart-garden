package it.unibo.garden.btlib;

public interface ExtendedRunnable extends Runnable {
    void write(byte[] bytes);
    void cancel();
}
