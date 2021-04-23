#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double avmag();
double minmag();
double maxmag();
double var();

typedef struct complex{
    double _re;
    double _im;
}complex;

int main(){

    double re[] = {10.00000,5.000000,3.333333,2.500000,2.000000,1.666667,1.428571,1.250000,1.111111,1.000000,0.909091,
                0.833333,0.769231,0.714286,0.666667,0.625000,0.588235,0.555556,0.526316,0.500000,0.476190,0.454545,
                0.434783,0.416667,0.400000,0.384615,0.370370,0.357143,0.344828,0.333333,0.322581,0.312500,0.303030,
                0.294118,0.285714,0.277778,0.270270,0.263158,0.256410,0.250000,0.243902,0.238095,0.232558,0.227273,
                0.222222,0.217391,0.212766,0.208333,0.204082,0.200000,0.196078,0.192308,0.188679,0.185185,0.181818,
                0.178571,0.175439,0.172414,0.169492,0.166667,0.163934,0.161290,0.158730,0.156250,0.153846,0.151515,
                0.149254,0.147059,0.144928,0.142857,0.140845,0.138889,0.136986,0.135135,0.133333,0.131579,0.129870,
                0.128205,0.126582,0.125000,0.123457,0.121951,0.120482,0.119048,0.117647,0.116279,0.114943,0.113636,
                0.112360,0.111111,0.109890,0.108696,0.107527,0.106383,0.105263,0.104167,0.103093,0.102041,0.101010,0.100000};

    double im[] = {7.000000,3.500000,2.333333,1.750000,1.400000,1.166667,1.000000,0.875000,0.777778,0.700000,0.636364,0.583333,
                0.538462,0.500000,0.466667,0.437500,0.411765,0.388889,0.368421,0.350000,0.333333,0.318182,0.304348,0.291667,0.280000,0.269231,
                0.259259,0.250000,0.241379,0.233333,0.225806,0.218750,0.212121,0.205882,0.200000,0.194444,0.189189,0.184211,0.179487,0.175000,
                0.170732,0.166667,0.162791,0.159091,0.155556,0.152174,0.148936,0.145833,0.142857,0.140000,0.137255,0.134615,0.132075,0.129630,
                0.127273,0.125000,0.122807,0.120690,0.118644,0.116667,0.114754,0.112903,0.111111,0.109375,0.107692,0.106061,0.104478,0.102941,
                0.101449,0.100000,0.098592,0.097222,0.095890,0.094595,0.093333,0.092105,0.090909,0.089744,0.088608,0.087500,0.086420,0.085366,
                0.084337,0.083333,0.082353,0.081395,0.080460,0.079545,0.078652,0.077778,0.076923,0.076087,0.075269,0.074468,0.073684,0.072917,
                0.072165,0.071429,0.070707,0.070000};
    
    int len = (int)(sizeof(re)/sizeof(re[0])); //size of array divided by the size of the datatype = length of array
    complex comp_Arr[len];

    for (int i = 0; i < len; i++)
    {
        comp_Arr[i]._re = re[i];
        comp_Arr[i]._im = im[i];
    };

    printf("----------------------------------------\n");
    printf("Size of re[]: %d\n", len);  
    printf("Average magnitude: %lf\n", avmag(comp_Arr, len));
    printf("Minimum magnitude: %lf\n", minmag(comp_Arr, len));
    printf("Maximum magnitude: %lf\n", maxmag(comp_Arr, len));
    printf("Variance magnitude: %lf\n", var(comp_Arr, len));

    return 0;
}

double avmag(complex arr[], int length){

    double mag = 0;
    for (int i = 0; i < length; i++)
    {   
        mag += sqrt(arr[i]._re * arr[i]._re + arr[i]._im * arr[i]._im);
    };
 
    return  mag/length;
}

double minmag(complex arr[], int length){
    double mag = 0, min = 0;
    min = sqrt(arr[0]._re * arr[0]._re + arr[0]._im * arr[0]._im);

     for (int i = 0; i < length; i++)
    {   
        mag = sqrt(arr[i]._re * arr[i]._re + arr[i]._im * arr[i]._im);
        if (mag < min){
            min = mag;
        };

    };
    return min;
}

double maxmag(complex arr[], int length){
    double mag = 0, max = 0;
    max = sqrt(arr[0]._re * arr[0]._re + arr[0]._im * arr[0]._im);

     for (int i = 0; i < length; i++)
    {   
        mag = sqrt(arr[i]._re * arr[i]._re + arr[i]._im * arr[i]._im);
        
        if (mag > max){
            max = mag;
        };
    };
    return max;
}

double var(complex arr[], int length){
    double mag, avg, _var = 0;

    avg = avmag(arr, length);

    for (int i = 0; i < length; i++)
    {
        mag = sqrt(arr[i]._re * arr[i]._re + arr[i]._im * arr[i]._im);
        _var += pow((mag-avg),2);
    };
    return _var/length;
}