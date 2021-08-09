package com.example.myapplication;

import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import com.opencsv.CSVReader;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import lecho.lib.hellocharts.model.PieChartData;
import lecho.lib.hellocharts.model.SliceValue;
import lecho.lib.hellocharts.view.PieChartView;

public class Data_image extends AppCompatActivity {
    File doc;
    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_data_image);


        doc = new File(getExternalFilesDir("DES"),"image.csv");
        if (!doc.exists()){
            print("El Archivo no existe");
            return;
        }
        PieChartView pieview = (PieChartView) findViewById(R.id.charti1);
        PieChartView linecharte = (PieChartView) findViewById(R.id.charti2);
        PieChartView linechartd = (PieChartView) findViewById(R.id.charti3);
        PieChartView pieview_a = (PieChartView) findViewById(R.id.charti4);
        PieChartView pieview_tte = (PieChartView) findViewById(R.id.charti5);
        PieChartView pieview_b = (PieChartView) findViewById(R.id.charti6);
        PieChartView pieview_ttd = (PieChartView) findViewById(R.id.charti7);
        PieChartView pieview_tt = (PieChartView) findViewById(R.id.charti8);
        PieChartView pieview_name = (PieChartView) findViewById(R.id.charti9);

        TextView txt_dis = (TextView) findViewById(R.id.txt_dis);



        List<Texto> values = new ArrayList<Texto>();
        int cont=0;
        try {
            CSVReader Reader = new CSVReader (new FileReader(doc));
            String[] record;
            while ((record = Reader.readNext()) != null) {
                if (cont!=0){
                    values.add(new Texto(record[0],
                            record[1],
                            Integer.parseInt(record[2]),
                            Integer.parseInt(record[3]),
                            Integer.parseInt(record[4]),
                            Integer.parseInt(record[5]),
                            Integer.parseInt(record[6]),
                            Integer.parseInt(record[7]),
                            Integer.parseInt(record[8]),
                            Float.parseFloat(record[9]),
                            Float.parseFloat(record[10]),
                            Float.parseFloat(record[11]),
                            Float.parseFloat(record[12]),
                            Float.parseFloat(record[13]),
                            Float.parseFloat(record[14]),
                            Float.parseFloat(record[15]),
                            Integer.parseInt(record[16])
                            ));
                    //Log.d("impresiones",record[7]);
                }
                cont++;
            }
            String dispositivo = null;
            List pieData = new ArrayList<>();
            List Tiempoa = new ArrayList<>();
            List pietiempoe = new ArrayList<>();
            List pietiempod = new ArrayList<>();
            List pietiempote = new ArrayList<>();
            List pietiempob = new ArrayList<>();
            List pietiempottd = new ArrayList<>();
            List pietiempott = new ArrayList<>();
            List names = new ArrayList<>();

            Random Rand = new Random();
            ArrayList<String> documentos=null;
            cont=0;
            for (Texto texto:values) {
                float r = Rand.nextFloat();
                float g = Rand.nextFloat();
                float b = Rand.nextFloat();
                dispositivo=texto.getDispositivo();
                //linedatae.add(new PointValue(cont, texto.getTiempoE()).setLabel(texto.getNombre()));
                pieData.add(new SliceValue(texto.getMemoria(), Color.rgb(r,g,b)).setLabel(""+texto.getMemoria()));
                pietiempoe.add(new SliceValue(texto.getTiempoE(),Color.rgb(r,g,b)).setLabel(String.valueOf(texto.getTiempoE())));
                pietiempod.add(new SliceValue(texto.getTiempoD(),Color.rgb(r,g,b)).setLabel(String.valueOf(texto.getTiempoD())));
                Tiempoa.add(new SliceValue(texto.getTiempoA(),Color.rgb(r,g,b)).setLabel(String.valueOf(texto.getTiempoA())));
                pietiempote.add(new SliceValue(texto.getTiempoTE(),Color.rgb(r,g,b)).setLabel(String.valueOf(texto.getTiempoTE())));
                pietiempob.add(new SliceValue(texto.getTiempoB(),Color.rgb(r,g,b)).setLabel(String.valueOf(texto.getTiempoB())));
                pietiempottd.add(new SliceValue(texto.getTiempoTD(),Color.rgb(r,g,b)).setLabel(String.valueOf(texto.getTiempoTD())));
                pietiempott.add(new SliceValue(texto.getTiempoT(),Color.rgb(r,g,b)).setLabel(String.valueOf(texto.getTiempoT())));
                names.add(new SliceValue(1,Color.rgb(r,g,b)).setLabel(texto.getNombre()));
                cont++;
            }
            txt_dis.setText("Dispositivo: "+dispositivo);
            PieChartData myPieChartData = new PieChartData(pieData);
            PieChartData myPieChartData2 = new PieChartData(pietiempoe);
            PieChartData myPieChartData3 = new PieChartData(pietiempod);
            PieChartData myPieChartData4 = new PieChartData(Tiempoa);
            PieChartData myPieChartData5 = new PieChartData(pietiempote);
            PieChartData myPieChartData6 = new PieChartData(pietiempob);
            PieChartData myPieChartData7 = new PieChartData(pietiempottd);
            PieChartData myPieChartData8 = new PieChartData(pietiempott);
            PieChartData myPieChartData9 = new PieChartData(names);


            myPieChartData.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData2.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData3.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData4.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData5.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData6.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData7.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData8.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData9.setHasLabels(true).setValueLabelTextSize(10);

            //myPieChartData.setHasCenterCircle(true).setCenterText1("Uso de la memoria "+dispositivo).setCenterText1FontSize(20);
            //myPieChartData2.setHasCenterCircle(true).setCenterText1("Tiempo de Encriptacion").setCenterText1FontSize(20);
            //myPieChartData3.setHasCenterCircle(true).setCenterText1("Tiempo de Desencriptacion").setCenterText1FontSize(20);

            pieview.setPieChartData(myPieChartData);
            linecharte.setPieChartData(myPieChartData2);
            linechartd.setPieChartData(myPieChartData3);
            pieview_a.setPieChartData(myPieChartData4);
            pieview_tte.setPieChartData(myPieChartData5);
            pieview_b.setPieChartData(myPieChartData6);
            pieview_ttd.setPieChartData(myPieChartData7);
            pieview_tt.setPieChartData(myPieChartData8);
            pieview_name.setPieChartData(myPieChartData9);

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public  void print(String text){
        Toast.makeText(this,text,Toast.LENGTH_LONG).show();
    }


}