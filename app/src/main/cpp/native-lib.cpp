#include <jni.h>
#include <string>
#include<iostream>
#include<cstring>
#include <android/log.h>
#include <stdio.h>
#include <memory.h>
#include <sstream>
#include <ctime>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define SIZE          8192  /* buffer size for reading /proc/<pid>/status */


using namespace std;

typedef bool    (*PSubKey)[16][48];
enum {ENCRYPT,DECRYPT}; //choice: encryption; decryption
static bool SubKey[2][16][48]; // 16 circle key
static bool Is3DES; // 3 times DES flag
static char Tmp[256], deskey[16]; //Temporary storage string, key string



static void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type);//Standard DES encryption/decryption
static void SetKey(const char* Key, int len);// Set the key
static void SetSubKey(PSubKey pSubKey, const char Key[8]);// Set the subkey
static void F_func(bool In[32], const bool Ki[48]);// f function
static void S_func(bool Out[32], const bool In[48]);// S box instead
static void Transform(bool *Out, bool *In, const char *Table, int len);// Transform
static void Xor(bool *InA, const bool *InB, int len);// Xor
static void RotateL(bool *In, int len, int loop);// rotate left
static void ByteToBit(bool *Out, const char *In, int bits);// Byte group is converted to bit group
static void BitToByte(char *Out, const bool *In, int bits);// Bit group is converted to byte group



//Encryption and decryption function:
bool DES_Act(char *Out,char *In,long datalen,const char *Key,int keylen,bool Type = ENCRYPT);

int mem_total();

std::string resp1;
std::string time_enc;
std::string time_des;
std::string time_total;
std::string mem;
std::string time_a;
std::string time_b;
std::string time_ek;
std::string time_dk;

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetTimeEnc(JNIEnv *env, jobject object){
    return env->NewStringUTF(time_enc.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetTimeDes(JNIEnv *env, jobject object){
    return env->NewStringUTF(time_des.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetTime(JNIEnv *env, jobject object){
    return env->NewStringUTF(time_total.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetMEM(JNIEnv *env, jobject object){
    return env->NewStringUTF(mem.c_str());
}




long long int dpower(int a,int b,int mod)
{
    long long int t;
    if(b==1)
        return a;
    t=dpower(a,b/2,mod);
    if(b%2==0)
        return (t*t)%mod;
    else
        return (((t*t)%mod)*a)%mod;
}

int dp, dg, db,da;
long long int dx,dy,dka,dkb;

string tostring(long long int input){
    std::string number;
    std::stringstream strstream;
    strstream << input;
    strstream >> number;
    return  number.c_str();
}

std::string la;
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetParams(JNIEnv *env, jobject object, jstring s, jstring k){
    unsigned t0_enc, t1_enc, t0_des, t1_des, tt1, tt2,ta0,ta1,tb0,tb1,tek0,tek1,tdk0,tdk1;
    tt1 = clock();
    //__android_log_print(ANDROID_LOG_DEBUG, "", "dg %d", dg);
    //__android_log_print(ANDROID_LOG_DEBUG, "", "dp %d", dp);
    //__android_log_print(ANDROID_LOG_DEBUG, "", "db %d", db);
    //incio proceso de encriptacion
    tek0=clock();
    //clave privada
    ta0=clock();
    la=env->GetStringUTFChars(k, 0);
    da= stoi(la);
    //__android_log_print(ANDROID_LOG_DEBUG, "", "da %d", da);
    dx = dpower(dg, da, dp);
    //__android_log_print(ANDROID_LOG_DEBUG, "", "dx %d", dx);
    dka = dpower(dx, db, dp);
    //__android_log_print(ANDROID_LOG_DEBUG, "", "dy %d", dka);
    ta1=clock();

    std::string text = env->GetStringUTFChars(s, 0);
    std::string llav = tostring(dka);

    int tn = text.length();
    int ln = llav.length();

    char texto[tn + 1];
    char llavea[ln + 1];

    strcpy(texto, text.c_str());
    strcpy(llavea, llav.c_str());

    tn = tn * 4;
    ln = ln * 4;
    char encrypt_text[tn + 1];
    char decrypt_text[tn + 2];

    memset(encrypt_text, 0,
           sizeof(encrypt_text));
    memset(decrypt_text, 0, sizeof(decrypt_text));

    // DES encryption:

    t0_enc = clock();
    DES_Act(encrypt_text, texto, sizeof(texto), llavea, sizeof(llavea), ENCRYPT);
    t1_enc = clock();

    //Fin proceso de encriptacion
    tek1=clock();

    //Incio proceso de desencriptacion
    tdk0=clock();
    //Clave publica

    tb0=clock();
    dy = dpower(dg, db, dp);
    dkb = dpower(dy, da, dp);
    tb1=clock();
    std::string llavb = tostring(dkb);
    int lnb = llavb.length();
    char llaveb[lnb + 1];
    strcpy(llaveb, llavb.c_str());

    //DES desencryoption
    t0_des = clock();
    DES_Act(decrypt_text, encrypt_text, sizeof(texto), llaveb, sizeof(texto), DECRYPT);
    t1_des = clock();
    //Fin Proceso de desencriptacion
    tdk1=clock();
    tt2 = clock();

    double time3 = (double(tt2 - tt1) / CLOCKS_PER_SEC);
    time_total = to_string(time3);
    mem = to_string(mem_total()).append("");
    double time = (double(t1_enc - t0_enc) / CLOCKS_PER_SEC);
    time_enc = to_string(time);
    double time2 = (double(t1_des - t0_des) / CLOCKS_PER_SEC);
    time_des = to_string(time2);
    double timea = (double(ta1-ta0)/CLOCKS_PER_SEC);
    time_a = to_string(timea);
    double timeb= (double(tb1-tb0)/CLOCKS_PER_SEC);
    time_b = to_string(timeb);
    double timedek = (double (tek1-tek0)/ CLOCKS_PER_SEC);
    time_ek=to_string(timedek);
    double  timeddk = (double (tdk1-tdk0)/CLOCKS_PER_SEC);
    time_dk = to_string(timeddk);

    //__android_log_print(ANDROID_LOG_DEBUG, "", "MEM1 %d", mem1);
    //__android_log_print(ANDROID_LOG_DEBUG, "", "MEM2 %d", mem2);

    return 0;
}

int mem_total ()
{
    char a[SIZE], *p, *q;
    int data, stack;
    int n, v, fd;
    pid_t pid= getpid();

    p = a;
    sprintf (p, "/proc/%d/status", pid);
    fd = open (p, O_RDONLY);
    if (fd < 0)
        return -1;
    do
        n = read (fd, p, SIZE);
    while ((n < 0) && (errno == EINTR));
    if (n < 0)
        return -2;
    do
        v = close (fd);
    while ((v < 0) && (errno == EINTR));
    if (v < 0)
        return -3;
    data = stack = 0;
    q = strstr (p, "VmData:");
    if (q != NULL)
    {
        sscanf (q, "%*s %d", &data);
        q = strstr (q, "VmStk:");
        if (q != NULL)
            sscanf (q, "%*s %d\n", &stack);
    }
    return (data + stack);
}

const static char IP_Table[64] =
        {
                58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
                62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
                57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
                61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
        };


// Inverse initial replacement IP1 table
const static char IP1_Table[64] =
        {
                40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
                38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
                36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
                34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25
        };


// Extended replacement E table
static const char Extension_Table[48] =
        {
                32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
                8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
                16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
                24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
        };


// P box replacement table
const static char P_Table[32] =
        {
                16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
                2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25
        };


// Key replacement table
const static char PC1_Table[56] =
        {
                57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
                10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
                63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
                14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
        };


// Compressed permutation table
const static char PC2_Table[48] =
        {
                14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
                23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
                41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
                44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
        };


// The number of digits moved per round
const static char LOOP_Table[16] =
        {
                1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
        };


// S box design
const static char S_Box[8][4][16] =
        {
                // S box 1
                14,	 4,	13,	 1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
                0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
                4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
                15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
                // S box 2
                15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
                3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
                0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
                13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
                // S box 3
                10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
                13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
                13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
                1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
                // S box 4
                7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
                13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
                10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
                3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
                // S box 5
                2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
                14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
                4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
                11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
                // S box 6
                12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
                10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
                9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
                4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
                // S box 7
                4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
                13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
                1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
                6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
                // S box 8
                13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
                1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
                7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
                2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
        };



//The following is the function called in the DES algorithm:

// Byte conversion function
void ByteToBit(bool *Out, const char *In, int bits)
{
    for(int i=0; i<bits; ++i)
        Out[i] = (In[i>>3]>>(i&7)) & 1;//In[i/8] This function is to take out 1 byte: when i=0~7, take In[ 0], when i=8~15, take In[1],...
    //In[i/8] >> (i%8), is to shift the 1 byte taken out by 0~7 bits to the right, that is, take out each bit of that byte in turn
    //The function of the whole function is: to convert each byte in In into 8 bits in turn, and the final result is stored in Out
}

// Bit conversion function
void BitToByte(char *Out, const bool *In, int bits)
{
    memset(Out, 0, bits>>3);//initialize each byte to 0
    for(int i=0; i<bits; ++i)
        Out[i>>3] |= In[i]<<(i&7);//i>> 3-bit operation, bitwise right shift by three bits is equal to i divided by 8, i&7 bitwise AND operation is equal to i and remainder 8. ；
}

// transformation function
void Transform(bool *Out, bool *In, const char *Table, int len)
{
    for(int i=0; i<len; ++i)
        Tmp[i] = In[ Table[i]-1 ];
    memcpy(Out, Tmp, len);
}

// Implementation of XOR function
void Xor(bool *InA, const bool *InB, int len)
{
    for(int i=0; i<len; ++i)
        InA[i] ^= InB[i];//Exclusive OR operation, the same is 0, the difference is 1
}

// Rotation function
void RotateL(bool *In, int len, int loop)
{
    memcpy(Tmp, In, loop);//Tmp accepts the loop bytes removed from the left
    memcpy(In, In+loop, len-loop);//In update, the remaining bytes move forward loop bytes
    memcpy(In+len-loop, Tmp, loop);//The left removed byte is added to the position of In's len-loop
}

// Implementation of S function
void S_func(bool Out[32], const bool In[48]) //Convert 8 groups, each group of 6 bits string, into 8 groups, each group 4 bits
{
    for(char i=0,j,k; i<8; ++i,In+=6,Out+=4)
    {
        j = (In[0]<<1) + In[5];//Take the binary number composed of the first and sixth digits as the ordinate of the S box
        k = (In[1]<<3) + (In[2]<<2) + (In[3]<<1) + In[4];//Take the second, third, fourth, and fifth digits The binary number is the abscissa of the S box
        ByteToBit(Out, &S_Box[i][j][k], 4);
    }
}

// Implementation of F function
void F_func(bool In[32], const bool Ki[48])
{
    static bool MR[48];
    Transform(MR, In, Extension_Table, 48); //First perform E extension
    Xor(MR, Ki, 48); //Xor again
    S_func(In, MR); //Each set of strings passes through their own S box
    Transform(In, In, P_Table, 32); //Finally P transformation
}

// set the subkey
void SetSubKey(PSubKey pSubKey, const char Key[8])
{
    static bool K[64], *KL=&K[0], *KR=&K[28]; //After removing the 8-bit parity from the 64-bit key string, divide it into two
    ByteToBit(K, Key, 64); //Conversion format
    Transform(K, K, PC1_Table, 56);

    for(int i=0; i<16; ++i) // Generate 48-bit subkey from 56-bit key
    {
        RotateL(KL, 28, LOOP_Table[i]); //Two sub-keys are shifted to the left
        RotateL(KR, 28, LOOP_Table[i]);
        Transform((*pSubKey)[i], K, PC2_Table, 48);
    }
}

// set the key
void SetKey(const char* Key, int len)
{
    memset(deskey, 0, 16);
    memcpy(deskey, Key, len>16?16:len);//memcpy(a,b,c) function, copy the content of the byte from the address b to the length of c to a
    SetSubKey(&SubKey[0], &deskey[0]);// Set the subkey
    Is3DES = len>8 ? (SetSubKey(&SubKey[1], &deskey[8]), true) : false;
}

// DES encryption and decryption function
void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type)
{
    static bool M[64], tmp[32], *Li=&M[0], *Ri=&M[32]; //64 bits of plaintext are divided into two parts after IP replacement
    ByteToBit(M, In, 64);
    Transform(M, M, IP_Table, 64);
    if( Type == ENCRYPT) //Encryption
    {
        for(int i=0; i<16; ++i) //When encrypting: subkey K0~K15
        {
            memcpy(tmp, Ri, 32);
            F_func(Ri, (*pSubKey)[i]); // call F function
            Xor(Ri, Li, 32); //Xor of Li and Ri
            memcpy(Li, tmp, 32);
        }
    }
    else //decryption
    {
        for(int i=15; i>=0; --i) // When decrypting: the order of Ki is opposite to encryption
        {
            memcpy(tmp, Li, 32);
            F_func(Li, (*pSubKey)[i]);
            Xor(Li, Ri, 32);
            memcpy(Ri, tmp, 32);
        }
    }
    Transform(M, M, IP1_Table, 64); //Finally, after inverse initial replacement IP-1, the ciphertext/plaintext is obtained
    BitToByte(Out, M, 64);
}

// DES encryption and decryption function (can encrypt long plaintext in segments)
bool DES_Act(char *Out, char *In, long datalen, const char *Key, int keylen, bool Type)
{
    if( !( Out && In && Key && (datalen=(datalen+7)&0xfffffff8) ) )
        return false;
    SetKey(Key, keylen);
    if( !Is3DES )
    {// 1 DES
        for(long i=0,j=datalen>>3; i<j; ++i,Out+=8,In+=8)
            DES(Out, In, &SubKey[0], Type);
    }
    else
    {// 3 times DES encryption: add (key0)-solution (key1)-add (key0) decryption:: solution (key0)-add (key1)-solution (key0)
        for(long i=0,j=datalen>>3; i<j; ++i,Out+=8,In+=8) {
            DES(Out, In,  &SubKey[0], Type);
            DES(Out, Out, &SubKey[1], !Type);
            DES(Out, Out, &SubKey[0], Type);
        }
    }
    return true;
}
std::string lp;
std::string lg;
std::string lb;
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_Credenciales_Generate_1pass(JNIEnv *env, jobject thiz, jstring p,
                                                           jstring g, jstring b) {
    /*dp=std::stoi(env->GetStringUTFChars(p,0));
    dg=std::stoi(env->GetStringUTFChars(g,0));
    db=std::stoi(env->GetStringUTFChars(b,0));
     */
    lp=env->GetStringUTFChars(p, 0);
    lg=env->GetStringUTFChars(g, 0);
    lb=env->GetStringUTFChars(b, 0);
    dp=stoi(lp);
    dg=stoi(lg);
    db=stoi(lb);

    /*__android_log_print(ANDROID_LOG_DEBUG, "", "dp %d", dp);
    __android_log_print(ANDROID_LOG_DEBUG, "", "dg %d", dg);
    __android_log_print(ANDROID_LOG_DEBUG, "", "db %d", db);
     */
    return 0;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetDA(JNIEnv *env, jobject thiz) {
    return  env->NewStringUTF(tostring(da).c_str());
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetDB(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(tostring(db).c_str());
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetDP(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(tostring(dp).c_str());
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetDG(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(tostring(dg).c_str());
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetAK(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(tostring(dka).c_str());
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetBK(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(tostring(dkb).c_str());
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetTA(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(time_a.c_str());
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetTE(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(time_ek.c_str());
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetTB(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(time_b.c_str());
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_GetTD(JNIEnv *env, jobject thiz) {
        return env->NewStringUTF(time_dk.c_str());
}