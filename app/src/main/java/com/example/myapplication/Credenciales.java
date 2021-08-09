package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class Credenciales extends AppCompatActivity {

    EditText edt_p,edt_g,edt_b;

    Button btn_env;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_credenciales);

        edt_p = (EditText) findViewById(R.id.edt_p);
        edt_g = (EditText) findViewById(R.id.edt_g);
        edt_b = (EditText) findViewById(R.id.edt_b);

        btn_env = (Button) findViewById(R.id.btn_cambiar);

        SharedPreferences myPreferences=PreferenceManager.getDefaultSharedPreferences(Credenciales.this);

        btn_env.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if (!validar_p()){return;};
                if (!validar_g()){return;};
                if (!valida_b()){return;};

                SharedPreferences.Editor myEditor = myPreferences.edit();

                String p =edt_p.getText().toString();
                String g =edt_g.getText().toString();
                String b =edt_b.getText().toString();

                myEditor.putString("P", p);
                myEditor.putString("G", g);
                myEditor.putString("B", b);
                myEditor.commit();

                Generate_pass(p,g,b);

                Intent myIntent = new Intent(Credenciales.this,MainActivity.class);
                startActivity(myIntent);
            }
        });

    }
    private boolean valida_b(){
        String text = edt_b.getText().toString();
        String text2 = edt_p.getText().toString();
        if (text.isEmpty()){
            print("Ingrese la clave publica");
            return false;
        }
        int b = Integer.parseInt(text);
        int p = Integer.parseInt(text2);
        if (b>=p){
            print("La clave publica tiene que ser menor a P");
            return false;
        }
        return true;
    }


    private boolean validar_g(){
        String text = edt_g.getText().toString();
        String text2 = edt_p.getText().toString();
        if (text.isEmpty()){
            print("Ingrese el numero G");
            return false;
        }
        int g = Integer.parseInt(text);
        int p = Integer.parseInt(text2);
        if (g>=p){
            print("G debe ser menor a P");
            return false;
        }
        return true;
    }

    private boolean validar_p(){
        String text=edt_p.getText().toString();
        if (text.isEmpty()){
            print("Ingrese el numero P");
            return false;
        }
        if (!esPrimo(Integer.parseInt(text))){
            print("El numero P no es primo");
            return  false;
        }
        return true;
    }

    public static boolean esPrimo(int numero) {
        if (numero == 0 || numero == 1 || numero == 4) {
            return false;
        }
        for (int x = 2; x < numero / 2; x++) {
            if (numero % x == 0)
                return false;
        }
        return true;
    }

    private void print(String text){
        Toast.makeText(this,text,Toast.LENGTH_LONG).show();
    }

    public native String Generate_pass(String P,String G, String B);
}