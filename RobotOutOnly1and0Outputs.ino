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



  wA0[0] = 1.80179;
	wA0[1] = 2.01899;
	wA0[2] = 1.88838;
	wA0[3] = 1.99875;
	wA0[4] = -3.9057;
	wA0[5] = -1.80465;
	wA0[6] = -1.87315;
	wA0[7] = -2.1279;

	wA1[0] = -0.196959;
	wA1[1] = -0.0300831;
	wA1[2] = -0.999692;
	wA1[3] = -0.723621;
	wA1[4] = -1.24417;
	wA1[5] = -0.433323;
	wA1[6] = -0.0413366;
	wA1[7] = 0.00196512;

	wA2[0] = -1.97712;
	wA2[1] = -1.92077;
	wA2[2] = -2.04932;
	wA2[3] = -3.15301;
	wA2[4] = 0.280017;
	wA2[5] = 2.43434;
	wA2[6] = 3.4888;
	wA2[7] = 3.21117;

	wA3[0] = -2.28972;
	wA3[1] = -1.51772;
	wA3[2] = -1.81125;
	wA3[3] = -0.0248169;
	wA3[4] = 1.59863;
	wA3[5] = 0.231971;
	wA3[6] = 0.420838;
	wA3[7] = 0.248853;

	wA4[0] = 0.564476;
	wA4[1] = 1.03434;
	wA4[2] = 0.943398;
	wA4[3] = 0.933148;
	wA4[4] = -3.12753;
	wA4[5] = -0.547809;
	wA4[6] = -0.809043;
	wA4[7] = -0.197098;

	wA5[0] = 0.459009;
	wA5[1] = 0.129353;
	wA5[2] = 0.300809;
	wA5[3] = 1.4403;
	wA5[4] = 0.420752;
	wA5[5] = -0.163962;
	wA5[6] = -0.351315;
	wA5[7] = -0.315508;

	wA6[0] = -2.19212;
	wA6[1] = -2.37827;
	wA6[2] = -2.37037;
	wA6[3] = -3.47046;
	wA6[4] = 1.59897;
	wA6[5] = 2.97674;
	wA6[6] = 2.91353;
	wA6[7] = 3.18955;

	wA7[0] = 1.29598;
	wA7[1] = 1.37067;
	wA7[2] = 0.810142;
	wA7[3] = 2.09451;
	wA7[4] = 0.247456;
	wA7[5] = -2.90146;
	wA7[6] = -1.47714;
	wA7[7] = -1.81936;
//****************************
	bA[0] = 0.2;
	bA[1] = 0.25;
	bA[2] = 0.33333;
	bA[3] = 1;
	bA[4] = 0.33333;
	bA[5] = 1;
	bA[6] = 0.5;
	bA[7] = 0.2;
//*****************************
	wB1[0] = -6.41075;
	wB1[1] = -0.116365;
	wB1[2] = 4.11152;
	wB1[3] = 4.68083;
	wB1[4] = -3.51854;
	wB1[5] = 1.06427;
	wB1[6] = 6.41269;
	wB1[7] = -1.18444;

	wB2[0] = 2.93617;
	wB2[1] = -1.37745;
	wB2[2] = -7.69566;
	wB2[3] = -0.258522;
	wB2[4] = -0.355373;
	wB2[5] = 1.84616;
	wB2[6] = -7.15329;
	wB2[7] = 4.93551;
//******************************
	bB[0] = 0.2;
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
	Ain[0] = sensor_value[0]*wA0[0] + sensor_value[1]*wA0[1] + sensor_value[2]*wA0[2] + sensor_value[3]*wA0[3] + sensor_value[4]*wA0[4] + sensor_value[5]*wA0[5] + sensor_value[6]*wA0[6] + sensor_value[7]*wA0[7];
	Ain[1] = sensor_value[0]*wA1[0] + sensor_value[1]*wA1[1] + sensor_value[2]*wA1[2] + sensor_value[3]*wA1[3] + sensor_value[4]*wA1[4] + sensor_value[5]*wA1[5] + sensor_value[6]*wA1[6] + sensor_value[7]*wA1[7];
	Ain[2] = sensor_value[0]*wA2[0] + sensor_value[1]*wA2[1] + sensor_value[2]*wA2[2] + sensor_value[3]*wA2[3] + sensor_value[4]*wA2[4] + sensor_value[5]*wA2[5] + sensor_value[6]*wA2[6] + sensor_value[7]*wA2[7];
	Ain[3] = sensor_value[0]*wA3[0] + sensor_value[1]*wA3[1] + sensor_value[2]*wA3[2] + sensor_value[3]*wA3[3] + sensor_value[4]*wA3[4] + sensor_value[5]*wA3[5] + sensor_value[6]*wA3[6] + sensor_value[7]*wA3[7];
	Ain[4] = sensor_value[0]*wA4[0] + sensor_value[1]*wA4[1] + sensor_value[2]*wA4[2] + sensor_value[3]*wA4[3] + sensor_value[4]*wA4[4] + sensor_value[5]*wA4[5] + sensor_value[6]*wA4[6] + sensor_value[7]*wA4[7];
	Ain[5] = sensor_value[0]*wA5[0] + sensor_value[1]*wA5[1] + sensor_value[2]*wA5[2] + sensor_value[3]*wA5[3] + sensor_value[4]*wA5[4] + sensor_value[5]*wA5[5] + sensor_value[6]*wA5[6] + sensor_value[7]*wA5[7];
	Ain[6] = sensor_value[0]*wA6[0] + sensor_value[1]*wA6[1] + sensor_value[2]*wA6[2] + sensor_value[3]*wA6[3] + sensor_value[4]*wA6[4] + sensor_value[5]*wA6[5] + sensor_value[6]*wA6[6] + sensor_value[7]*wA6[7];
	Ain[7] = sensor_value[0]*wA7[0] + sensor_value[1]*wA7[1] + sensor_value[2]*wA7[2] + sensor_value[3]*wA7[3] + sensor_value[4]*wA7[4] + sensor_value[5]*wA7[5] + sensor_value[6]*wA7[6] + sensor_value[7]*wA7[7];

	for(int i = 0;i < 8;i++){
		Aout[i] = Sigmoid(Ain[i]);
	}

	Bin[0] = Aout[0]*wB1[0] + Aout[1]*wB1[1] + Aout[2]*wB1[2] + Aout[3]*wB1[3] + Aout[4]*wB1[4] + Aout[5]*wB1[5] + Aout[6]*wB1[6] + Aout[7]*wB1[7];
	Bin[1] = Aout[0]*wB2[0] + Aout[1]*wB2[1] + Aout[2]*wB2[2] + Aout[3]*wB2[3] + Aout[4]*wB2[4] + Aout[5]*wB2[5] + Aout[6]*wB2[6] + Aout[7]*wB2[7];

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
