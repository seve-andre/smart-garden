package it.unibo.garden;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
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
import android.widget.Toast;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import it.unibo.garden.btlib.BluetoothChannel;
import it.unibo.garden.btlib.BluetoothUtils;
import it.unibo.garden.btlib.ConnectToBluetoothServerTask;
import it.unibo.garden.btlib.ConnectionTask;
import it.unibo.garden.btlib.exceptions.BluetoothDeviceNotFound;
import it.unibo.garden.http.Http;
import it.unibo.garden.utils.ClientConfig;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
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

    @SuppressLint("MissingPermission")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();

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

        if (btAdapter != null && !btAdapter.isEnabled()) {
            startActivityForResult(
                    new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE),
                    ClientConfig.bluetooth.ENABLE_BT_REQUEST
            );

            try {
                this.connectToBTServer();
            } catch (BluetoothDeviceNotFound bluetoothDeviceNotFound) {
                Toast.makeText(this, "Bluetooth device not found !", Toast.LENGTH_LONG)
                        .show();
                bluetoothDeviceNotFound.printStackTrace();
            }
        }

        findViewById(R.id.btnRequireManualMode).setEnabled(true);
        findViewById(R.id.btnAlarm).setVisibility(View.INVISIBLE);
        initUi();

        /***********************/
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder()
                .permitAll().build();
        StrictMode.setThreadPolicy(policy);
        /***********************/

        TimerTask getApiDataTask = new TimerTask() {
            @Override
            public void run() {
                if (isAutoModeOn && isNetworkAvailable()) {
                    Log.d("getApiData", "insideeee");

                    Http.get("https://9226-95-238-240-43.eu.ngrok.io/api/data", response -> {
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
        });

        findViewById(R.id.btnRequireAutoMode).setOnClickListener(listener -> {
            for (Button b : buttons) {
                b.setEnabled(false);
            }
            listener.setEnabled(false);
            isAutoModeOn = true;

            // re-enable manual mode
            findViewById(R.id.btnRequireManualMode).setEnabled(true);
        });

        findViewById(R.id.btnLed1).setOnClickListener(listener -> {
            // send bluetooth message
            btChannel.sendMessage("ciao");
        });

        findViewById(R.id.btnLed2).setOnClickListener(listener -> {
            // send bluetooth message
        });

        findViewById(R.id.btnIncreaseLed3).setOnClickListener(listener -> {
            // send bluetooth message
        });

        findViewById(R.id.btnDecreaseLed3).setOnClickListener(listener -> {
            // send bluetooth message
        });

        findViewById(R.id.btnIncreaseLed4).setOnClickListener(listener -> {
            // send bluetooth message
        });

        findViewById(R.id.btnDecreaseLed4).setOnClickListener(listener -> {
            // send bluetooth message
        });

        findViewById(R.id.btnIrrigation).setOnClickListener(listener -> {
            // send bluetooth message
        });

        findViewById(R.id.btnIncreaseSpeed).setOnClickListener(listener -> {
            // send bluetooth message
        });


        findViewById(R.id.btnDecreaseSpeed).setOnClickListener(listener -> {
            // send bluetooth message
        });

        findViewById(R.id.btnAlarm).setOnClickListener(listener -> {
            // send bluetooth message

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

    private void connectToBTServer() throws BluetoothDeviceNotFound {
        final BluetoothDevice serverDevice = BluetoothUtils
                .getPairedDeviceByName(ClientConfig.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME);
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
//                btChannel.close();
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
