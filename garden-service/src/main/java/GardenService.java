import http.DataService;
import io.vertx.core.Vertx;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.client.WebClient;
import jssc.SerialPortException;
import serial.CommChannel;
import serial.SerialCommChannel;

public class GardenService {
    public static void main(String[] args) throws Exception {
        String host = "localhost"; // "b1164b27.ngrok.io";
        int port = 8080;

        /*Vertx vertx = Vertx.vertx();
        WebClient client = WebClient.create(vertx);
        CommChannel channel = new SerialCommChannel("Com5", 115200);*/

        Vertx vertx = Vertx.vertx();
        DataService service = new DataService(8080);
        vertx.deployVerticle(service);

        /*while (true) {
            client.get(port, host, "/api/data")
                    .send()
                    .onSuccess(res -> {
                        System.out.println("Getting - Received response with status code: " + res.statusCode());
                        JsonObject response = res.bodyAsJsonArray().getJsonObject(0);

                        System.out.println(response.encodePrettily());
                    })
                    .onFailure(
                            err -> System.out.println("Something went wrong " + err.getMessage())
                    );

            if (channel.isMsgAvailable()) {
                String msg = channel.receiveMsg();
            }
        }*/
    }
}
