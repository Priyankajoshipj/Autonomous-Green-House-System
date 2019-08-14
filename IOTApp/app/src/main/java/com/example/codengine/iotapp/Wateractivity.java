package com.example.codengine.iotapp;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.*;

public class Wateractivity extends AppCompatActivity {

    String pnum,operation,join;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_wateractivity);

        Button b1 = findViewById(R.id.button3);
        Intent intent = getIntent();
         pnum = intent.getStringExtra("pnum");
         operation = intent.getStringExtra("operation");
         join = pnum + operation;

        //TaskStart p1;


        b1.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                StartThread s = new StartThread();
                s.start();
                //s.interrupt();

            }
        });

        Button b2 = findViewById(R.id.button4);
        b2.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                    StopThread s = new StopThread();
                    s.start();
            }
        });
    }

        class StartThread extends Thread
        {

            String baseUrl = "http://192.168.137.198:7015/";
            BufferedReader reader; String respose = " ";
            HttpURLConnection urlConnection = null;                             //ongoback
            //Button bb = findViewById(R.id.button3);                           //INTENT EXTRA???
            // bb.setOnClickListener(new View.OnClickListener() {

            public void run() {
                try
                {
                    final URL url = new URL(baseUrl);
                    urlConnection = (HttpURLConnection) url.openConnection();
                    urlConnection.setRequestMethod("POST");
                    urlConnection.setRequestProperty("Content-Type", "application/json");
                    urlConnection.setUseCaches(false);

                    try (DataOutputStream outputPost = new DataOutputStream(urlConnection.getOutputStream()))
                    {    //RUN A WHILE LOOP ON RESPONSE? //there has to be a stop
                        String response = "{\"task\":"+ join+"1" + "}";
                        outputPost.write(response.getBytes());
                    }
                    urlConnection.connect();


                    InputStream inputStream = urlConnection.getInputStream();
                    this.interrupt();
                }
                catch (Exception e)
                {

                }
                finally
                {
                    urlConnection.disconnect();
                }
            }

        }


    class StopThread extends Thread
    {

        String baseUrl = "http://192.168.137.198:7015";
        BufferedReader reader; String respose = " ";
        HttpURLConnection urlConnection = null;                             //ongoback
        //Button bb = findViewById(R.id.button3);                           //INTENT EXTRA???
        // bb.setOnClickListener(new View.OnClickListener() {



        public void run()
        {
            try
            {
                final URL url = new URL(baseUrl);
                urlConnection = (HttpURLConnection) url.openConnection();
                urlConnection.setRequestMethod("POST");
                urlConnection.setRequestProperty("Content-Type", "application/json");
                urlConnection.setUseCaches(false);
                // urlConnection.setDoOutput(true);
                try (DataOutputStream outputPost = new DataOutputStream(urlConnection.getOutputStream())) {
                    //RUN A WHILE LOOP ON RESPONSE? //there has to be a stop
                    String response = "{\"task\":"+ join +"0" + "}";
                    outputPost.write(response.getBytes());
                }
                urlConnection.connect();


                InputStream inputStream = urlConnection.getInputStream();
                this.interrupt();
            }
            catch (Exception e)
            {

            }
            finally
            {
                urlConnection.disconnect();
            }
        }

    }


}








