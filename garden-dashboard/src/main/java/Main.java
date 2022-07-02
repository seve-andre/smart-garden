import gui.DashboardGui;
import io.vertx.core.Vertx;

public class Main {
    public static void main(String[] args) {
        DashboardGui gui = new DashboardGui();
        Vertx vertx = Vertx.vertx();
        vertx.deployVerticle(new DataVerticle(gui));
    }
}
