package com.example.codengine.iotapp;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.os.Handler;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        setContentView(R.layout.splash);
//        //display the logo during 5 seconds,
//        new CountDownTimer(5000,1000){
//            @Override
//            public void onTick(long millisUntilFinished){}
//
//            @Override
//            public void onFinish(){
//                //set the new Content of your activity
//                setContentView(R.layout.activity_main);
//            }
//        }.start();
        setContentView(R.layout.activity_main);

        /*ListStatusTask listStatusTask = new ListStatusTask();
        listStatusTask.execute();*/

        Button p1 = findViewById(R.id.button);
        Button p2 = findViewById(R.id.button1);
        Button p3 = findViewById(R.id.button2);

        p1.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v)
            {
                Intent plant1 = new Intent( MainActivity.this , Plant1Activity.class);
                plant1.putExtra("pnum","1");
                startActivity(plant1);
            }
        });

        p2.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v)
            {
                Intent plant2 = new Intent(v.getContext(), Plant2Activity.class);
                plant2.putExtra("pnum","2");
                startActivity(plant2);
            }
        });

        p3.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v)
            {
                Intent plant3 = new Intent(v.getContext(), Plant3Activity.class);
                plant3.putExtra("pnum","3");
                startActivity(plant3);
            }
        });





    }



}
