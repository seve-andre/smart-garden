package http;

public class DataPoint {

    private final int intensity;
    private final int temperature;
    private final String state;

    public DataPoint(int intensity, int temperature, String state) {
        this.intensity = intensity;
        this.temperature = temperature;
        this.state = state;
    }

    public int getLightIntensity() {
        return intensity;
    }

    public int getTemperature() {
        return temperature;
    }

    public String getState() {
        return state;
    }
}
