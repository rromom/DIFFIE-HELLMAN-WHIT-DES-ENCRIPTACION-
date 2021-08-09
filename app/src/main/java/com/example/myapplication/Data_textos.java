package com.example.myapplication;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

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

public class Data_textos extends AppCompatActivity {

    File doc;

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_data_textos);
        doc = new File(getExternalFilesDir("DES"),"texto.csv");
        if (!doc.exists()){
           print("El Archivo no existe");
           return;
        }
        PieChartView pieview = (PieChartView) findViewById(R.id.chart1);
        PieChartView linecharte = (PieChartView) findViewById(R.id.chart2);
        PieChartView linechartd = (PieChartView) findViewById(R.id.chart3);
        PieChartView TiempoA = (PieChartView) findViewById(R.id.chart5);
        PieChartView myView_names = (PieChartView) findViewById(R.id.chart6);
        PieChartView myView_total = (PieChartView) findViewById(R.id.chart4);
        PieChartView myView_TTE = (PieChartView) findViewById(R.id.chart7);
        PieChartView myView_B = (PieChartView) findViewById(R.id.chart8);
        PieChartView myView_TTD = (PieChartView) findViewById(R.id.chart9);


        TextView txt_dis = (TextView) findViewById(R.id.txt_dist);


        //PieChartView pieview1 = (PieChartView) findViewById(R.id.chart5);
        //PieChartView pieview2 = (PieChartView) findViewById(R.id.chart6);



        List<Texto> values = new ArrayList<Texto>();
        int cont=0;
        try {
            CSVReader Reader = new CSVReader (new FileReader(doc));
            String[] record;
            while ((record = Reader.readNext()) != null) {
                if (cont!=0){
                    values.add(new Texto(
                            record[0],
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
                            Integer.parseInt(record[16])));
                    //Log.d("impresiones",record[7]);
                }
                cont++;
            }
            String dispositivo = null;
            List pieData = new ArrayList<>();
            List pietiempoe = new ArrayList<>();
            List pietiempod = new ArrayList<>();
            List pietiempoa = new ArrayList<>();
            List names = new ArrayList<>();
            List total = new ArrayList<>();
            List A = new ArrayList<>();
            List TTE = new ArrayList<>();
            List B = new ArrayList<>();
            List TTD = new ArrayList<>();
            Random Rand = new Random();
            cont=0;
            for (Texto texto:values) {
                float r = Rand.nextFloat();
                float g = Rand.nextFloat();
                float b = Rand.nextFloat();
                dispositivo=texto.getDispositivo();
                //linedatae.add(new PointValue(cont, texto.getTiempoE()).setLabel(texto.getNombre()));
                pieData.add(new SliceValue(texto.getMemoria(),Color.rgb(r,g,b)).setLabel(""+texto.getMemoria()));
                pietiempoe.add(new SliceValue(texto.getTiempoE(),Color.rgb(r,g,b)).setLabel(String.valueOf(texto.getTiempoE())));
                pietiempod.add(new SliceValue(texto.getTiempoD(),Color.rgb(r,g,b)).setLabel(String.valueOf(texto.getTiempoD())));
                pietiempoa.add(new SliceValue(texto.getTiempoA(),Color.rgb(r,g,b)).setLabel(String .valueOf(texto.getTiempoA())));
                names.add(new SliceValue(1,Color.rgb(r,g,b)).setLabel(texto.getNombre()));
                total.add(new SliceValue(texto.getTiempoT(),Color.rgb(r,g,b)).setLabel(String .valueOf(texto.getTiempoT())));
                A.add(new SliceValue(texto.getTiempoA(),Color.rgb(r,g,b)).setLabel(String .valueOf(texto.getTiempoA())));
                TTE.add(new SliceValue(texto.getTiempoTE(),Color.rgb(r,g,b)).setLabel(String .valueOf(texto.getTiempoTE())));
                B.add(new SliceValue(texto.getTiempoB(),Color.rgb(r,g,b)).setLabel(String .valueOf(texto.getTiempoB())));
                TTD.add(new SliceValue(texto.getTiempoTD(),Color.rgb(r,g,b)).setLabel(String .valueOf(texto.getTiempoTD())));
                cont++;
            }
            txt_dis.setText("Dispositivo: "+dispositivo);
            PieChartData myPieChartData1 = new PieChartData(pieData);
            PieChartData myPieChartData2 = new PieChartData(pietiempoe);
            PieChartData myPieChartData3 = new PieChartData(pietiempod);
            PieChartData myPieChartData4 = new PieChartData(pietiempoa);
            PieChartData myPieChartData5 = new PieChartData(names);
            PieChartData myPieChartData6 = new PieChartData(total);
            PieChartData myPieChartData7 = new PieChartData(TTE);
            PieChartData myPieChartData8 = new PieChartData(B);
            PieChartData myPieChartData9 = new PieChartData(TTD);


            myPieChartData1.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData2.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData3.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData4.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData5.setHasLabels(true).setValueLabelTextSize(10);
            myPieChartData6.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData7.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData8.setHasLabels(true).setValueLabelTextSize(12);
            myPieChartData9.setHasLabels(true).setValueLabelTextSize(12);

            //myPieChartData.setHasCenterCircle(true).setCenterText1("Uso de la memoria "+dispositivo).setCenterText1FontSize(20);
            //myPieChartData2.setHasCenterCircle(true).setCenterText1("Tiempo de Encriptacion").setCenterText1FontSize(20);
            //myPieChartData3.setHasCenterCircle(true).setCenterText1("Tiempo de Desencriptacion").setCenterText1FontSize(20);


            pieview.setPieChartData(myPieChartData1);
            linecharte.setPieChartData(myPieChartData2);
            linechartd.setPieChartData(myPieChartData3);
            TiempoA.setPieChartData(myPieChartData4);
            myView_names.setPieChartData(myPieChartData5);
            myView_total.setPieChartData(myPieChartData6);
            myView_TTE.setPieChartData(myPieChartData7);
            myView_B.setPieChartData(myPieChartData8);
            myView_TTD.setPieChartData(myPieChartData9);

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