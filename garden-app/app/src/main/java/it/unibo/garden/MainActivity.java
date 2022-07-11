package it.unibo.garden;

import static it.unibo.garden.btlib.BluetoothUtils.getPairedDeviceByName;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.os.StrictMode;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import it.unibo.garden.bt.BluetoothDeviceNotFound;
import it.unibo.garden.btlib.BluetoothChannel;
import it.unibo.garden.btlib.BluetoothUtils;
import it.unibo.garden.btlib.ConnectToBluetoothServerTask;
import it.unibo.garden.btlib.ConnectionTask;
import it.unibo.garden.http.Http;
import it.unibo.garden.utils.ClientConfig;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.Timer;
import java.util.TimerTask;
import java.util.UUID;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class MainActivity extends AppCompatActivity {
    private BluetoothChannel btChannel;
    private final List<Button> buttons = new ArrayList<>();
    private final Timer timer = new Timer();
    private boolean isAutoModeOn = true;
    private static final String HTTP_URL = "https://4640-95-238-240-43.eu.ngrok.io/api/data";

    @SuppressLint("MissingPermission")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        buttons.addAll(
                Arrays.asList(
                        findViewById(R.id.btnLed1),
                        findViewById(R.id.btnLed2),
                        findViewById(R.id.btnIncreaseLed3),
                        findViewById(R.id.btnDecreaseLed3),
                        findViewById(R.id.btnIncreaseLed4),
                        findViewById(R.id.btnDecreaseLed4),
                        findViewById(R.id.btnIrrigation),
                        findViewById(R.id.btnIncreaseSpeed),
                        findViewById(R.id.btnDecreaseSpeed),
                        findViewById(R.id.btnRequireManualMode),
                        findViewById(R.id.btnRequireAutoMode)
                )
        );

        for (Button b : buttons) {
            b.setEnabled(false);
        }

        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();

        if(btAdapter != null && !btAdapter.isEnabled()) {
            startActivityForResult(
                    new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE),
                    ClientConfig.bluetooth.ENABLE_BT_REQUEST
            );
        }

        findViewById(R.id.btnRequireManualMode).setEnabled(true);
        findViewById(R.id.btnAlarm).setVisibility(View.INVISIBLE);
        initUi();
        this.connectToBTServer();

        /***********************/
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder()
                .permitAll().build();
        StrictMode.setThreadPolicy(policy);
        /***********************/

        TimerTask getApiDataTask = new TimerTask() {
            @Override
            public void run() {
                if (isAutoModeOn && isNetworkAvailable()) {

                    Http.get(HTTP_URL, response -> {
                        if (response.code() == HttpURLConnection.HTTP_OK) {
                            try {
                                JSONArray newResponse = new JSONArray(response.contentAsString());

                                if (newResponse.length() > 0) {
                                    JSONObject jsonResponse = newResponse.getJSONObject(0);

                                    int intensity = jsonResponse.getInt("intensity");
                                    int temperature = jsonResponse.getInt("temperature");
                                    String state = jsonResponse.getString("state");

                                    if (state.equals("alarm")) {
                                        findViewById(R.id.btnAlarm).setVisibility(View.VISIBLE);
                                        findViewById(R.id.btnRequireManualMode).setEnabled(false);

                                        isAutoModeOn = false;
                                    }

                                    ((TextView) findViewById(R.id.textLed3)).setText(String.valueOf(intensity));
                                    ((TextView) findViewById(R.id.textLed4)).setText(String.valueOf(intensity));
                                    ((TextView) findViewById(R.id.textIrrigationSpeed)).setText(String.valueOf(temperature));
                                    ((TextView) findViewById(R.id.textState)).setText(state);
                                }
                            } catch (IOException | JSONException e) {
                                e.printStackTrace();
                            }
                        }
                    });
                }
            }
        };

        timer.schedule(getApiDataTask, 0, 3000);
    }

    private void initUi() {
        findViewById(R.id.btnRequireManualMode).setOnClickListener(listener -> {
            // get data from api - json format and set ui accordingly
            for (Button b : buttons) {
                b.setEnabled(true);
            }
            isAutoModeOn = false;

            // set manual mode enabling to false
            listener.setEnabled(false);

            btChannel.sendMessage("manual");

            String content = null;
            try {
                // example
                content = new JSONObject()
                        .put("intensity", ((TextView) findViewById(R.id.textLed3)))
                        .put("temperature", ((TextView) findViewById(R.id.textIrrigationSpeed)))
                        .put("state", "manual").toString();
            } catch (JSONException e) {
                e.printStackTrace();
            }

            Http.post(HTTP_URL, Objects.requireNonNull(content).getBytes(), response -> {});
        });

        findViewById(R.id.btnRequireAutoMode).setOnClickListener(listener -> {
            for (Button b : buttons) {
                b.setEnabled(false);
            }
            listener.setEnabled(false);
            isAutoModeOn = true;

            // re-enable manual mode
            findViewById(R.id.btnRequireManualMode).setEnabled(true);

            btChannel.sendMessage("auto");
        });

        findViewById(R.id.btnLed1).setOnClickListener(listener -> {
            // send bluetooth message
            btChannel.sendMessage("L1");
        });

        findViewById(R.id.btnLed2).setOnClickListener(listener -> {
            // send bluetooth message
            btChannel.sendMessage("L2");
        });

        findViewById(R.id.btnIncreaseLed3).setOnClickListener(listener -> {
            // send bluetooth message
            TextView textLed3 = findViewById(R.id.textLed3);
            int currentIntensity = Integer.parseInt(textLed3.getText().toString());
            if (currentIntensity < 4) {
                int newIntensity = currentIntensity + 1;
                textLed3.setText(String.valueOf(newIntensity));
                btChannel.sendMessage("3i" + newIntensity);
            }
        });

        findViewById(R.id.btnDecreaseLed3).setOnClickListener(listener -> {
            // send bluetooth message
            TextView textLed3 = findViewById(R.id.textLed3);
            int currentIntensity = Integer.parseInt(textLed3.getText().toString());
            if (currentIntensity > 0) {
                int newIntensity = currentIntensity - 1;
                textLed3.setText(String.valueOf(newIntensity));
                btChannel.sendMessage("3i" + newIntensity);
            }
        });

        findViewById(R.id.btnIncreaseLed4).setOnClickListener(listener -> {
            // send bluetooth message
            TextView textLed4 = findViewById(R.id.textLed4);
            int currentIntensity = Integer.parseInt(textLed4.getText().toString());
            if (currentIntensity < 4) {
                int newIntensity = currentIntensity + 1;
                textLed4.setText(String.valueOf(newIntensity));
                btChannel.sendMessage("4i" + newIntensity);
            }
        });

        findViewById(R.id.btnDecreaseLed4).setOnClickListener(listener -> {
            // send bluetooth message
            TextView textLed4 = findViewById(R.id.textLed4);
            int currentIntensity = Integer.parseInt(textLed4.getText().toString());
            if (currentIntensity > 0) {
                int newIntensity = currentIntensity - 1;
                textLed4.setText(String.valueOf(newIntensity));
                btChannel.sendMessage("4i" + newIntensity);
            }
        });

        findViewById(R.id.btnIrrigation).setOnClickListener(listener -> {
            // send bluetooth message
            btChannel.sendMessage("irrigation");
        });

        findViewById(R.id.btnIncreaseSpeed).setOnClickListener(listener -> {
            // send bluetooth message
            TextView textIrrigationSpeed = findViewById(R.id.textIrrigationSpeed);
            int currentSpeed = Integer.parseInt(textIrrigationSpeed.getText().toString());
            if (currentSpeed < 5) {
                int newSpeed = currentSpeed + 1;
                textIrrigationSpeed.setText(String.valueOf(newSpeed));
                btChannel.sendMessage("s" + newSpeed);
            }
        });


        findViewById(R.id.btnDecreaseSpeed).setOnClickListener(listener -> {
            // send bluetooth message
            TextView textIrrigationSpeed = findViewById(R.id.textIrrigationSpeed);
            int currentSpeed = Integer.parseInt(textIrrigationSpeed.getText().toString());
            if (currentSpeed > 0) {
                int newSpeed = currentSpeed - 1;
                textIrrigationSpeed.setText(String.valueOf(newSpeed));
                btChannel.sendMessage("s" + newSpeed);
            }
        });

        findViewById(R.id.btnAlarm).setOnClickListener(listener -> {
            // send bluetooth message
            btChannel.sendMessage("alarm");
            findViewById(R.id.btnRequireManualMode).setEnabled(true);
            ((TextView) findViewById(R.id.textState)).setText("auto");

            isAutoModeOn = true;

            // make it invisible once clicked
            listener.setVisibility(View.INVISIBLE);
        });
    }

    @Override
    protected void onStop() {
        super.onStop();
        btChannel.close();
    }

    @Override
    protected void onActivityResult(final int requestCode, final int resultCode,
                                    @Nullable final Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == ClientConfig.bluetooth.ENABLE_BT_REQUEST && resultCode == RESULT_OK) {
            Log.d(ClientConfig.APP_LOG_TAG, "Bluetooth enabled!");
        }

        if (requestCode == ClientConfig.bluetooth.ENABLE_BT_REQUEST && resultCode == RESULT_CANCELED) {
            Log.d(ClientConfig.APP_LOG_TAG, "Bluetooth not enabled!");
        }
    }

    private void connectToBTServer() {
        BluetoothDevice serverDevice = null;
        try {
            serverDevice = getPairedDeviceByName(ClientConfig.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME);
        } catch (BluetoothDeviceNotFound e) {
            e.printStackTrace();
        }
        // !!! Choose the right UUID value
        final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();

//        final UUID uuid = BluetoothUtils.generateUuidFromString(ClientConfig.bluetooth.BT_SERVER_UUID);

        new ConnectToBluetoothServerTask(serverDevice, uuid, new ConnectionTask.EventListener() {
            @Override
            public void onConnectionActive(final BluetoothChannel channel) {
                btChannel = channel;
            }

            @Override
            public void onConnectionCanceled() {
            }
        }).execute();
    }

    private boolean isNetworkAvailable() {
        ConnectivityManager connectivityManager
                = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo activeNetworkInfo = connectivityManager.getActiveNetworkInfo();
        return activeNetworkInfo != null && activeNetworkInfo.isConnected();
    }
}
