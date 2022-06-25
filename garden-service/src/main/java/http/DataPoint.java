package http;

public class DataPoint {

    private int tempLvl;
    private int fotoResLvl;
    private long time;
    private String stato;
    private String manMode;

    public DataPoint(int temperatureLevel, int fotoresLevel, long time, String stato, String s) {
        this.tempLvl = temperatureLevel;
        this.fotoResLvl = fotoresLevel;
        this.time = time;
        this.stato = stato;
        this.manMode = s;
    }

    public int getTempLevel() {
        return tempLvl;
    }

    public int getFotoResLevel() {
        return fotoResLvl;
    }

    public long getTime() {
        return time;
    }

    public String getStato() {
        return stato;
    }

    public String getManMode() {
        return manMode;
    }

}
