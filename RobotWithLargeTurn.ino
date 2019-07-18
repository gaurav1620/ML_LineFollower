/*#################################################################
 * NEURAL NETWORK WITH 8 INPUT ,8 HIDDEN AND 2 OUTPUT NODES IS IMPLEMENTED
 * FOR LINE FOLLOWER ROBOTS

 * Designed by :

   ______
  / ____/___ ___  ___________ __   __
 / / __/ __ `/ / / / ___/ __ `/ | / /
/ /_/ / /_/ / /_/ / /  / /_/ /| |/ /
\____/\__,_/\__,_/_/   \__,_/ |___/

    __ __ __          _
   / //_// /_  ____ _(_)________  ____ ______
  / ,<  / __ \/ __ `/ / ___/ __ \/ __ `/ ___/
 / /| |/ / / / /_/ / / /  / / / / /_/ / /
/_/ |_/_/ /_/\__,_/_/_/  /_/ /_/\__,_/_/

****************************************************************
// 6 th July 2019

@ Website : gaurav1620.rf.gd
@ Github  : gaurav1620
@ Insta   : may_be_gaurav
@ Gmail   : gauravak007@gmail.com

*/
//**********************/
bool sensor_value[8];
//**********************
double wA0[8];
double wA1[8];
double wA2[8];
double wA3[8];
double wA4[8];
double wA5[8];
double wA6[8];
double wA7[8];

double bA[8];

double Ain[8];

double Aout[8];
//*******************
double wB1[8];
double wB2[8];

double bB[2];

double Bin[2];

double Bout[2];
//*******************
double leftPrediction;
double rightPrediction;
//*********************

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



  wA0[0] = -2.28245;
	wA0[1] = -4.12845;
	wA0[2] = -0.562375;
	wA0[3] = -0.958423;
	wA0[4] = 1.74;
	wA0[5] = 1.35868;
	wA0[6] = 1.37488;
	wA0[7] = 1.47787;

	wA1[0] = -1.00149;
	wA1[1] = -0.550018;
	wA1[2] = -0.006477;
	wA1[3] = -0.715557;
	wA1[4] = 0.359846;
	wA1[5] = 0.924652;
	wA1[6] = 0.749147;
	wA1[7] = 0.982414;

	wA2[0] = 2.02013;
	wA2[1] = 2.17946;
	wA2[2] = 1.48533;
	wA2[3] = 1.39509;
	wA2[4] = 1.5992;
	wA2[5] = 1.74185;
	wA2[6] = 1.67136;
	wA2[7] = 1.63269;

	wA3[0] = 5.81176;
	wA3[1] = 3.88947;
	wA3[2] = 0.365129;
	wA3[3] = 0.186225;
	wA3[4] = -2.49149;
	wA3[5] = -1.94248;
	wA3[6] = -1.92349;
	wA3[7] = -1.98113;

	wA4[0] = 0.642795 ;
	wA4[1] = 0.682665;
	wA4[2] = 1.90355;
	wA4[3] = 3.06243;
	wA4[4] = -0.675524;
	wA4[5] = -1.42912;
	wA4[6] = -1.54401;
	wA4[7] = -1.72358;

	wA5[0] = 1.28697;
	wA5[1] = 1.53704;
	wA5[2] = 0.503285;
	wA5[3] = 1.09371;
	wA5[4] = 0.816037;
	wA5[5] = 0.547863;
	wA5[6] = 0.471673;
	wA5[7] = 0.229155;

	wA6[0] = 0.606196;
	wA6[1] = 0.637708;
	wA6[2] = 0.0797779;
	wA6[3] = -0.0463626;
	wA6[4] = 1.26417;
	wA6[5] = 0.819408;
	wA6[6] = 0.269309;
	wA6[7] = 0.551134;

	wA7[0] = 0.266362;
	wA7[1] = 0.124049;
	wA7[2] = 0.680007;
	wA7[3] = 1.81854;
	wA7[4] = -0.680579;
	wA7[5] = -0.382614;
	wA7[6] = -0.912337;
	wA7[7] = -0.979748;
//****************************
	bA[0] = 0.25;
	bA[1] = 0.25;
	bA[2] = 1;
	bA[3] = 0.33333;
	bA[4] = 0.33333;
	bA[5] = 0.2;
	bA[6] = 0.2;
	bA[7] = 0.5;
//*****************************
	wB1[0] = 0.472654;
	wB1[1] = -1.49352;
	wB1[2] = 5.24377;
	wB1[3] = -6.14199;
	wB1[4] = -1.7891;
	wB1[5] = 2.08002;
	wB1[6] = 0.927592;
	wB1[7] = -0.85561;

	wB2[0] = -4.48667;
	wB2[1] = -1.28503;
	wB2[2] = 0.636357;
	wB2[3] = 3.03941;
	wB2[4] = 4.99231;
	wB2[5] = 1.38586;
	wB2[6] = -0.397905;
	wB2[7] = 2.7715;
//******************************
	bB[0] = 0.25;
	bB[1] = 0.25;
//******************************

}

void loop(){
	sensor_value[0]=digitalRead(51);
	sensor_value[1]=digitalRead(49);
	sensor_value[2]=digitalRead(47);
	sensor_value[3]=digitalRead(45);
	sensor_value[4]=digitalRead(50);
	sensor_value[5]=digitalRead(48);
	sensor_value[6]=digitalRead(46);
	sensor_value[7]=digitalRead(44);

	prediction();
	Serial.print(leftPrediction);
	Serial.print(",");
	Serial.println(rightPrediction);
	act();

}

void prediction(){
	Ain[0] = sensor_value[0]*wA0[0] + sensor_value[1]*wA0[1] + sensor_value[2]*wA0[2] + sensor_value[3]*wA0[3] + sensor_value[4]*wA0[4] + sensor_value[5]*wA0[5] + sensor_value[6]*wA0[6] + sensor_value[7]*wA0[7] + bA[0];
	Ain[1] = sensor_value[0]*wA1[0] + sensor_value[1]*wA1[1] + sensor_value[2]*wA1[2] + sensor_value[3]*wA1[3] + sensor_value[4]*wA1[4] + sensor_value[5]*wA1[5] + sensor_value[6]*wA1[6] + sensor_value[7]*wA1[7] + bA[1];
	Ain[2] = sensor_value[0]*wA2[0] + sensor_value[1]*wA2[1] + sensor_value[2]*wA2[2] + sensor_value[3]*wA2[3] + sensor_value[4]*wA2[4] + sensor_value[5]*wA2[5] + sensor_value[6]*wA2[6] + sensor_value[7]*wA2[7] + bA[2];
	Ain[3] = sensor_value[0]*wA3[0] + sensor_value[1]*wA3[1] + sensor_value[2]*wA3[2] + sensor_value[3]*wA3[3] + sensor_value[4]*wA3[4] + sensor_value[5]*wA3[5] + sensor_value[6]*wA3[6] + sensor_value[7]*wA3[7] + bA[3];
	Ain[4] = sensor_value[0]*wA4[0] + sensor_value[1]*wA4[1] + sensor_value[2]*wA4[2] + sensor_value[3]*wA4[3] + sensor_value[4]*wA4[4] + sensor_value[5]*wA4[5] + sensor_value[6]*wA4[6] + sensor_value[7]*wA4[7] + bA[4];
	Ain[5] = sensor_value[0]*wA5[0] + sensor_value[1]*wA5[1] + sensor_value[2]*wA5[2] + sensor_value[3]*wA5[3] + sensor_value[4]*wA5[4] + sensor_value[5]*wA5[5] + sensor_value[6]*wA5[6] + sensor_value[7]*wA5[7] + bA[5];
	Ain[6] = sensor_value[0]*wA6[0] + sensor_value[1]*wA6[1] + sensor_value[2]*wA6[2] + sensor_value[3]*wA6[3] + sensor_value[4]*wA6[4] + sensor_value[5]*wA6[5] + sensor_value[6]*wA6[6] + sensor_value[7]*wA6[7] + bA[6];
	Ain[7] = sensor_value[0]*wA7[0] + sensor_value[1]*wA7[1] + sensor_value[2]*wA7[2] + sensor_value[3]*wA7[3] + sensor_value[4]*wA7[4] + sensor_value[5]*wA7[5] + sensor_value[6]*wA7[6] + sensor_value[7]*wA7[7] + bA[7];

	for(int i = 0;i < 8;i++){
		Aout[i] = Sigmoid(Ain[i]);
	}

	Bin[0] = Aout[0]*wB1[0] + Aout[1]*wB1[1] + Aout[2]*wB1[2] + Aout[3]*wB1[3] + Aout[4]*wB1[4] + Aout[5]*wB1[5] + Aout[6]*wB1[6] + Aout[7]*wB1[7] + bB[0];
	Bin[1] = Aout[0]*wB2[0] + Aout[1]*wB2[1] + Aout[2]*wB2[2] + Aout[3]*wB2[3] + Aout[4]*wB2[4] + Aout[5]*wB2[5] + Aout[6]*wB2[6] + Aout[7]*wB2[7] + bB[1];

	Bout[0] = Sigmoid(Bin[0]);
	Bout[1] = Sigmoid(Bin[1]);

	rightPrediction = Bout[0];
	leftPrediction  = Bout[1];

}
void act(){
	float lPwm = leftPrediction  * 255;
	float rPwm = rightPrediction * 255;

	analogWrite(22,lPwm);
  digitalWrite(24,LOW);
  analogWrite(26,rPwm);
  digitalWrite(28,LOW);

	// //DEBUG
	// Serial.print(pwm2);
  // Serial.print(",");
  // Serial.println(pwm1);
}
double Sigmoid(double x){
    return 1 / (1 + exp(-x));
}

//EOF
//##############################################################################
