package com.example.myapplication;

public class Texto {
    public String Dispositivo;
    public String Nombre;
    public int Tamanio;
    public int P;
    public int G;
    public int privada;
    public int publica;
    public int A;
    public int B;
    public float TiempoA;
    public float TiempoE;
    public float TiempoTE;
    public float TiempoB;
    public float TiempoD;
    public float TiempoTD;
    public float TiempoT;
    public int Memoria;

    public Texto(String dispositivo, String nombre, int tamanio, int p, int g, int privada, int publica, int a, int b, float tiempoA, float tiempoE, float tiempoTE, float tiempoB, float tiempoD, float tiempoTD, float tiempoT, int memoria) {
        Dispositivo = dispositivo;
        Nombre = nombre;
        Tamanio = tamanio;
        P = p;
        G = g;
        this.privada = privada;
        this.publica = publica;
        A = a;
        B = b;
        TiempoA = tiempoA;
        TiempoE = tiempoE;
        TiempoTE = tiempoTE;
        TiempoB = tiempoB;
        TiempoD = tiempoD;
        TiempoTD = tiempoTD;
        TiempoT = tiempoT;
        Memoria = memoria;
    }

    public String getDispositivo() {
        return Dispositivo;
    }

    public void setDispositivo(String dispositivo) {
        Dispositivo = dispositivo;
    }

    public String getNombre() {
        return Nombre;
    }

    public void setNombre(String nombre) {
        Nombre = nombre;
    }

    public int getTamanio() {
        return Tamanio;
    }

    public void setTamanio(int tamanio) {
        Tamanio = tamanio;
    }

    public int getP() {
        return P;
    }

    public void setP(int p) {
        P = p;
    }

    public int getG() {
        return G;
    }

    public void setG(int g) {
        G = g;
    }

    public int getPrivada() {
        return privada;
    }

    public void setPrivada(int privada) {
        this.privada = privada;
    }

    public int getPublica() {
        return publica;
    }

    public void setPublica(int publica) {
        this.publica = publica;
    }

    public int getA() {
        return A;
    }

    public void setA(int a) {
        A = a;
    }

    public int getB() {
        return B;
    }

    public void setB(int b) {
        B = b;
    }

    public float getTiempoA() {
        return TiempoA;
    }

    public void setTiempoA(float tiempoA) {
        TiempoA = tiempoA;
    }

    public float getTiempoE() {
        return TiempoE;
    }

    public void setTiempoE(float tiempoE) {
        TiempoE = tiempoE;
    }

    public float getTiempoTE() {
        return TiempoTE;
    }

    public void setTiempoTE(float tiempoTE) {
        TiempoTE = tiempoTE;
    }

    public float getTiempoB() {
        return TiempoB;
    }

    public void setTiempoB(float tiempoB) {
        TiempoB = tiempoB;
    }

    public float getTiempoD() {
        return TiempoD;
    }

    public void setTiempoD(float tiempoD) {
        TiempoD = tiempoD;
    }

    public float getTiempoTD() {
        return TiempoTD;
    }

    public void setTiempoTD(float tiempoTD) {
        TiempoTD = tiempoTD;
    }

    public float getTiempoT() {
        return TiempoT;
    }

    public void setTiempoT(float tiempoT) {
        TiempoT = tiempoT;
    }

    public int getMemoria() {
        return Memoria;
    }

    public void setMemoria(int memoria) {
        Memoria = memoria;
    }

    @Override
    public String toString() {
        return "Texto{" +
                "Dispositivo='" + Dispositivo + '\'' +
                ", Nombre='" + Nombre + '\'' +
                ", Tamanio=" + Tamanio +
                ", P=" + P +
                ", G=" + G +
                ", privada=" + privada +
                ", publica=" + publica +
                ", A=" + A +
                ", B=" + B +
                ", TiempoA=" + TiempoA +
                ", TiempoE=" + TiempoE +
                ", TiempoTE=" + TiempoTE +
                ", TiempoB=" + TiempoB +
                ", TiempoD=" + TiempoD +
                ", TiempoTD=" + TiempoTD +
                ", TiempoT=" + TiempoT +
                ", Memoria=" + Memoria +
                '}';
    }
}


