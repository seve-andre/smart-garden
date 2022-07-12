import gui.DashboardGui;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.client.HttpRequest;
import io.vertx.ext.web.client.WebClient;
import io.vertx.ext.web.codec.BodyCodec;

public class DataVerticle extends AbstractVerticle {
    private final DashboardGui gui;
    private HttpRequest<JsonArray> request;

    public DataVerticle(DashboardGui gui) {
        this.gui = gui;
    }

    @Override
    public void start() {
        String host = "localhost";
        int port = 8080;

        request = WebClient.create(vertx)
                .get(port, host, "/api/data")
                .as(BodyCodec.jsonArray());

        vertx.setPeriodic(3000, handler -> fetchData());
    }

    private void fetchData() {
        request.send()
                .onSuccess(res -> {
                    System.out.println("Getting - Received response with status code: " + res.statusCode());

                    JsonArray newResponse = res.body();
                    if (!newResponse.isEmpty()) {
                        JsonObject jsonResponse = newResponse.getJsonObject(0);

                        int intensity = jsonResponse.getInteger("intensity");
                        int temperature = jsonResponse.getInteger("temperature");
                        String state = jsonResponse.getString("state");
                        gui.setIntensity(intensity);
                        gui.setTemperature(temperature);
                        gui.setState(state);
                    }
                })
                .onFailure(err -> System.out.println("Something went wrong " + err.getMessage()));
    }
}
