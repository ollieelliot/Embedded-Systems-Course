#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct complex{
    double real;
    double imaginary;

}complex;

complex conjugate();
complex multiply();
complex division();
complex add();
complex sub();
complex recip();
complex mag();


int main(){
    
    complex _complex, _complex2, _compin, _compin2;

    _complex.real = 2;
    _complex.imaginary = 3;

    _complex2.real = 5;
    _complex2.imaginary = 7;


    
    /* printf("(Conjugate) Real: %f Imaginary: %f\n", conjugate(_complex).real, conjugate(_complex).imaginary);
    printf("(Multiply) Real: %f Imaginary: %f\n", multiply(_complex, _complex2).real, multiply(_complex, _complex2).imaginary);
    printf("(Division) Real: %f Imaginary: %f\n", division(_complex, _complex2).real, division(_complex, _complex2).imaginary);
    printf("(Add) Real: %f Imaginary: %f\n", add(_complex, _complex2).real, add(_complex, _complex2).imaginary);
    printf("(Subtraction) Real: %f Imaginary: %f\n", sub(_complex, _complex2).real, sub(_complex, _complex2).imaginary);
    printf("(Reciprocal) Real: %f Imaginary: %f\n", recip(_complex).real, recip(_complex).imaginary);
    printf("(Magnitude) Real: %f", mag(_complex).real);
    */

    printf("Enter the real-part of z1: ");
    scanf("%lf", &_compin.real); 

    printf("Enter the imaginary-part of z1: ");
    scanf("%lf", &_compin.imaginary); 

    printf("Enter the real-part of z2: ");
    scanf("%lf", &_compin2.real); 

    printf("Enter the imaginary-part of z2: ");
    scanf("%lf", &_compin2.imaginary); 

    printf("(Add) Real: %f Imaginary: %f\n", add(_compin, _compin2).real, add(_compin, _compin2).imaginary);
    printf("(Subtraction) Real: %f Imaginary: %f\n", sub(_compin, _compin2).real, sub(_compin, _compin2).imaginary);
    printf("(Multiply) Real: %f Imaginary: %f\n", multiply(_compin, _compin2).real, multiply(_compin, _compin2).imaginary);
    printf("(Division) Real: %f Imaginary: %f\n", division(_compin, _compin2).real, division(_compin, _compin2).imaginary);
    printf("(Magnitude) Real: %f\n", mag(_compin).real);
    printf("(Reciprocal) Real: %f Imaginary: %f\n", recip(_compin).real, recip(_compin).imaginary);


    return 0;
}


complex conjugate(struct complex z){

    z.imaginary = -z.imaginary;
    return z;   
};

complex multiply(struct complex z1, struct complex z2){
    struct complex _z;

    _z.real = z1.real * z2.real - z1.imaginary * z2.imaginary;
    _z.imaginary = z1.imaginary * z2.real + z1.real * z2.imaginary;
    return _z;
};

complex division(struct complex z1, struct  complex z2){
  struct complex _z;
 
  _z.real = (z1.real * z2.real + z1.imaginary * z2.imaginary) / (z2.real * z2.real + z2.imaginary * z2.imaginary);
  _z.imaginary = (z1.imaginary * z2.real - z1.real * z2.imaginary) / (z2.real * z2.real + z2.imaginary * z2.imaginary);
    return _z;
};

complex add(struct complex z1, struct complex z2){

    z1.real = z1.real + z2.real;
    z1.imaginary = z1.imaginary + z2.imaginary;
    return z1;
}

complex sub(struct complex z1, struct complex z2){

    z1.real = z1.real - z2.real;
    z1.imaginary = z1.imaginary - z2.imaginary;
    return z1;
}

complex recip(struct complex z){
    struct complex _z;

    _z.real = z.real / (z.real * z.real + z.imaginary * z.imaginary);
    _z.imaginary = -z.imaginary / (z.real * z.real + z.imaginary * z.imaginary);
    return _z;
}

complex mag(struct complex z){
    
    z.real = sqrt(z.real * z.real + z.imaginary * z.imaginary);
    return z;
}







