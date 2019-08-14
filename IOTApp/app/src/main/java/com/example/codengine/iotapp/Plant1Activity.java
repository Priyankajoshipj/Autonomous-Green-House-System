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

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;


public class Plant1Activity extends AppCompatActivity {

    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.plant1_activity);
        Intent intent = getIntent();
        final String pnum = intent.getStringExtra("pnum");

        Button water = findViewById(R.id.button3);
        Button light = findViewById(R.id.button4);
       // _stackBlurManager = new StackBlurManager(getBitmapFromAsset(this, "yourFile.png"));
        water.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent i2 = new Intent(Plant1Activity.this,Wateractivity.class);
                i2.putExtra("pnum",pnum);
                i2.putExtra("operation","0");
                startActivity(i2);
            }
        });

        light.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent i3 = new Intent(Plant1Activity.this,Wateractivity.class);
                i3.putExtra("pnum",pnum);
                i3.putExtra("operation","1");
                startActivity(i3);
            }
        });


        Plant1task p1 = new Plant1task();
        p1.execute();
    }



    class Plant1task extends AsyncTask<Void, Void, boolean[]> {
        private final String LOG_TAG = getClass().getSimpleName();

        String jsonresponse, humidval, tempval,timestampval,lightval,soil_moisture, append = "";

        @Override
        protected boolean[] doInBackground(Void... params)
        {
            HttpURLConnection urlConnection = null;
            BufferedReader reader = null;


            try {



                String baseUrl = "http://192.168.137.198";
                URL url = new URL(baseUrl);

                // Create the request to OpenWeatherMap, and open the connection
                urlConnection = (HttpURLConnection) url.openConnection();
                urlConnection.setRequestMethod("GET");
                urlConnection.connect();
                InputStream inputStream = urlConnection.getInputStream();
                final StringBuilder buffer = new StringBuilder();
                if (inputStream != null)
                {
                    reader = new BufferedReader(new InputStreamReader(inputStream));

                    String line;
                    while ((line = reader.readLine()) != null) {
                        buffer.append(line).append("\n");
                    }

                    if (buffer.length() != 0) {
                        jsonresponse = buffer.toString();
                        Log.i(LOG_TAG, jsonresponse);
                    }




                    try {
                        List<String> temperature = new ArrayList<String>();
                        List<String> timestamp = new ArrayList<String>();
                        List<String> humidity = new ArrayList<String>();

                        JSONObject partition = new JSONObject(jsonresponse);
                        JSONArray p1 = partition.getJSONArray("0013A200410809DD");
                        for(int i =0; i< p1.length(); i++)
                        {
                            JSONObject test = p1.getJSONObject(i);
                            tempval = test.getString("temperature");
                            humidval = test.getString("humidity");
                            timestampval = test.getString("timestamp");
                            lightval = test.getString("light");
                            soil_moisture = test.getString("soil_moisture");
                            append += timestampval +"  \t" + humidval + "  \t" + tempval+ "  \t"+ lightval + "  \t" + soil_moisture +"\n";



                        }
                    }
                    catch (JSONException j)
                    {

                    }
                    Button b1 = findViewById( R.id.button2);
                    b1.setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View view) {
                            TextView tv1 = findViewById(R.id.textView2);
                            tv1.setText("Timestamp"+"\t"+"Humidity"+ "\t" + "Temperature"+"\t"+"Light Intensity"+"\t"+"Moisture"+"\n"+append);
                        }
                    });



                }

            } catch (IOException e) {
                Log.e("PlaceholderFragment", "Error ", e);
            } finally {
                if (urlConnection != null) {
                    urlConnection.disconnect();
                }
                if (reader != null) {
                    try {
                        reader.close();

                    } catch (final IOException e) {
                        Log.e("PlaceholderFragment", "Error closing stream", e);
                    }
                }

            }
            return null;
        }

        //  @Override
        protected void onPostExecute(boolean[] b) {

            new Handler().postDelayed(new Runnable() {
                public void run() {
                    new Plant1task().execute();
                }
            }, 1000);
        }


    }

}

