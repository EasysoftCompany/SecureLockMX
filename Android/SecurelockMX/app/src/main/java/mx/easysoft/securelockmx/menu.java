package mx.easysoft.securelockmx;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

public class menu extends AppCompatActivity {

    BluetoothSocket mmSocket;
    BluetoothDevice mmDevice;
    OutputStream mmOutputStream;
    InputStream mmInputStream;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);
    }

    public void changeStatus(View v){
        FirebaseDatabase database = FirebaseDatabase.getInstance();
        final DatabaseReference myRef = database.getReference("LOCK_STATUS");
        myRef.setValue("OPEN");
        Handler handler = new Handler();
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                // Do something after 5s = 5000ms
                myRef.setValue("CLOSE");
            }
        }, 3000);

    }

    public void logout (View v){
        Intent mainClass = new Intent(getApplicationContext(), MainActivity.class);
        startActivity(mainClass);

    }

    public void BT_Conn (View v){
        BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if(mBluetoothAdapter == null)
        {
            Toast toast1 =
                    Toast.makeText(getApplicationContext(),
                            "No bluetooth adapter available", Toast.LENGTH_SHORT);

            toast1.show();
        }

        if(!mBluetoothAdapter.isEnabled())
        {
            Intent enableBluetooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBluetooth, 0);
        }

        Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
        if(pairedDevices.size() > 0)
        {
            for(BluetoothDevice device : pairedDevices)
            {
                if(device.getName().equals("SecureLockMX"))
                {
                    mmDevice = device;

                    Toast toast1 = Toast.makeText(getApplicationContext(),"Connected to SecureLockMX", Toast.LENGTH_SHORT);
                    toast1.show();
                    break;
                }
            }
        }


        try {
            UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"); //Standard SerialPortService ID
            mmSocket = mmDevice.createRfcommSocketToServiceRecord(uuid);
            mmSocket.connect();
            mmOutputStream = mmSocket.getOutputStream();
            mmInputStream = mmSocket.getInputStream();

            //CADENA SHA-254
            String msg = "d975205d410502c5d490b74f58704a1d6f4ffeb11ff3140b561deea721ee3bb7" + "\n";
            mmOutputStream.write(msg.getBytes());
            mmOutputStream.close();
            mmInputStream.close();
            mmSocket.close();

            Toast toast2 = Toast.makeText(getApplicationContext(),"Cerradura Abierta!", Toast.LENGTH_SHORT);
            toast2.show();

        }catch(Exception ex){
            System.err.println("ERROR " + ex.toString());
        }
    }
}
