package mx.easysoft.securelockmx;

import android.content.Intent;
import android.os.TestLooperManager;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

public class MainActivity extends AppCompatActivity {

    EditText usr;
    EditText pwd;
    TextView txtStatus;
    private FirebaseAuth mAuth;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setTheme(R.style.AppTheme);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mAuth = FirebaseAuth.getInstance();


        usr = findViewById(R.id.txt_usr);
        pwd = findViewById(R.id.txt_pwd);
        txtStatus = findViewById(R.id.status);
    }

    public void login(View v){

        if(!usr.getText().toString().isEmpty() && !pwd.getText().toString().isEmpty()) {

            String email = usr.getText().toString();
            String pass = pwd.getText().toString();

            mAuth.signInWithEmailAndPassword(email, pass)
                    .addOnCompleteListener(this, new OnCompleteListener<AuthResult>() {
                        @Override
                        public void onComplete(@NonNull Task<AuthResult> task) {
                            if (task.isSuccessful()) {

                                FirebaseUser user = mAuth.getCurrentUser();

                                txtStatus.setText(user.getUid());

                                Intent menu = new Intent(getApplicationContext(), menu.class);
                                startActivity(menu);
                            } else {

                                Toast.makeText(MainActivity.this, "Authentication failed.",
                                        Toast.LENGTH_SHORT).show();

                                txtStatus.setText("Try Again");
                            }

                            // ...
                        }
                    });
        }
        else
        {
            Toast.makeText(MainActivity.this,"Ingrese usuario y contraseña!",Toast.LENGTH_LONG).show();
        }

}
}
