#include <Math.h>
bool sensor_value[8];
double w1[8];
double w2[2];
double b2[2];
double b1[1];
double predictionArray[2]={0,0};
double Z;
double A;
double ZZ[2];
double AA[2];
void setup() {
  pinMode(51,INPUT);
  pinMode(49,INPUT);
  pinMode(47,INPUT);
  pinMode(45,INPUT);
  pinMode(50,INPUT);
  pinMode(48,INPUT);
  pinMode(46,INPUT);
  pinMode(44,INPUT);

  pinMode(22,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(28,OUTPUT);

  Serial.begin(9600);



  w1[0]=-2.18923523;
  w1[1]=-3.41938433;
  w1[2]=-3.86338789;
  w1[3]=-2.35007917;
  w1[4]= 2.33945419;
  w1[5]= 2.16638758;
  w1[6]= 3.40659723;
  w1[7]= 3.90511339;

  w2[0]= 2.02033755;
  w2[1]=-2.03282775;

  b2[0]=-0.18288889;
  b2[1]=-0.04979374;

  b1[0]=0.03597459;
}

void loop() {
   sensor_value[0]=digitalRead(51);
   sensor_value[1]=digitalRead(49);
   sensor_value[2]=digitalRead(47);
   sensor_value[3]=digitalRead(45);
   sensor_value[4]=digitalRead(50);
   sensor_value[5]=digitalRead(48);
   sensor_value[6]=digitalRead(46);
   sensor_value[7]=digitalRead(44);

   Serial.print(sensor_value[0]);
   Serial.print(sensor_value[1]);
   Serial.print(sensor_value[2]);
   Serial.print(sensor_value[3]);
   Serial.print(sensor_value[4]);
   Serial.print(sensor_value[5]);
   Serial.print(sensor_value[6]);
   Serial.println(sensor_value[7]);

   prediction();
   Serial.print(predictionArray[0]);
   Serial.print(",");
   Serial.println(predictionArray[1]);
   act();


}

void act(){
  int pwm1=map2(predictionArray[0],0,1,0,150);
  int pwm2=map2(predictionArray[1],0,1,0,150);
  analogWrite(22,pwm2);
  digitalWrite(24,LOW);
  analogWrite(26,pwm1);
  digitalWrite(28,LOW);
  Serial.print(pwm2);
  Serial.print(",");
  Serial.println(pwm1);

}

int map2(float x, float in_min, float in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void prediction(){
    Z=((sensor_value[0]*w1[0] + sensor_value[1]*w1[1] + sensor_value[2]*w1[2] + sensor_value[3]*w1[3] + sensor_value[4]*w1[4] + sensor_value[5]*w1[5] + sensor_value[6]*w1[6] + sensor_value[7]*w1[7]) +b1[0]);
    A=tanh2(Z);

    ZZ[0]=((w2[0]*A + b2[0]));
    ZZ[1]=((w2[1]*A + b2[1]));

    AA[0]= Sigmoid(ZZ[0]);
    AA[1]= Sigmoid(ZZ[1]);

    predictionArray[0]=AA[0];
    predictionArray[1]=AA[1];
  }


double tanh2(double x){
  double x0 = exp(x);
  double x1 = 1.0 / x0;

  return ((x0 - x1) / (x0 + x1));
}

double Sigmoid(double x){
    return 1 / (1 + exp(-x));
}
