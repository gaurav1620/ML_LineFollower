//NEURAL NETWORK WITH 8 INPUT ,8 HIDDEN AND 2 OUTPUT NODES
//Designed by :
/**********************************************************************
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

***********************************************************************/ 
// 4 th July 2019
#include<iostream>
#include<vector>
#include </home/samiksha/Desktop/Codes/IntellegentLineFollower/Eigen/Dense>
#include <math.h> 
using namespace std;
using namespace Eigen;


//************************************************************************
//Change this to give more number of training cases than 2;
int trainCases = 9;

//And this too
Matrix<Matrix<float,8,1>,9,1> matInput;
Matrix<Matrix<float,2,1>,9,1> matExpectedOutput;
//************************************************************************



Matrix<float,8,1> inputs;

Matrix<float,8,1> Ain;
Matrix<float,8,1> Aout;
Matrix<float,8,8> weightsA;
Matrix<float,8,1> biasA;


Matrix<float,2,1> Bin;
Matrix<float,2,1> Bout;
Matrix<float,2,8> weightsB;
Matrix<float,2,1> biasB;

Matrix<float,2,1> expectedOutputs;

float lr = 0;


float sigmoid(float x){
	float denominator = (1 + exp(-x));
	return 1/denominator;
}

/***************************************************************************************************/
void init(){

	//TAKING INPUT VALUES

	cout<<"\nEnter the 8 input values for each Training  case : \n";

	for(int i = 0;i < trainCases;i++){
		Matrix<float,8,1>tmp;
		for(int j = 0;j < 8;j++){
			cout<<"\nEnter the value for Training Case : "<<i+1<<" and Input number : "<<j+1<<" : ";
			float var;
			cin>>var;
			tmp(j,0) = var;
		}
		matInput(i,0) = tmp;
	}


	//TAKING DESIRED VALUES
	cout<<"\nEnter the 2 Desired values for Each test case: \n";

	for(int i = 0;i < trainCases;i++){
		Matrix<float,2,1> tmp;
		for(int j = 0;j < 2;j++){
			cout<<"\nEnter the desired output for Case : "<<i+1<<" and index : "<<j+1<<" : ";
			cin>>tmp(j,0);
		}
		matExpectedOutput(i,0) = tmp;
	}
	//cin>>expectedOutputs(0,0)>>expectedOutputs(1,0);


	//GET THE LEARNING RATE
	cout<<"\nEnter the learning rate : \n";
	cin>>lr;

	// GIVING RANDOM WTS FOR LAYER 1
	srand ( time(NULL) );
	for(int i = 0;i < 8 ;i++){
		for(int j = 0;j < 8;j++){
			//Gives a random value between -1 and 1
			float den = rand()%5 + 1;
			float num = rand()%3 -1;
			//Inportant step
			weightsA(i,j) = (num/den);
		}
	}


	//GIVING RANDOM WTS FOR LAYER 2
	srand ( time(NULL) );
	for(int i = 0;i < 2 ;i++){
		for(int j = 0;j < 8;j++){
			//Gives a random value between -1 and 1
			float den = rand()%5 + 1;
			float num = rand()%3 -1;
			//Inportant step
			weightsB(i,j) = (num/den);
		}
	}


	//ASSIGNING RANDOM BIASES FOR LAYER 1   (Bias here are taken between 0 and 1)
	srand ( time(NULL) );
	for(int i = 0;i < 8 ;i++){
		float den = rand()%5 + 1;
		float num = 1;

		biasA(i,0) = num/den;
	}
	//ASSIGNING RANDOM BIASES FOR LAYER 2   (Bias here are taken between 0 and 1)
	srand ( time(NULL) );
	for(int i = 0;i < 2 ;i++){
		float den = rand()%5 + 1;
		float num = 1;

		biasB(i,0) = num/den;
	}
}

/***************************************************************************************************/

void feedForward(){

	//OUTPUT 1 IS THE WEIGHTED SUM OF THE INPUTS
	Ain = (weightsA*inputs)+biasA;


	//INPUTS 2 IS THE OUTPUT OF LAYER 1 AFTER PASSING THROUGH SIGMOID
	for(int i = 0;i < 8;i++){
		Aout(i,0) = sigmoid(Ain(i,0)); 
	}

	//OUTPUT 2 THE WEIGHTED SUM FOR LAYER 2
	Bin =( weightsB*Aout )+ biasB;

	//FINAL OUTPUT IS THE FINAL OUTPUT (LOL !)
	for(int i = 0;i < 2;i++){
		Bout(i,0) = sigmoid(Bin(i,0));
	}

	//cout<<"\nExpected ouptputs : \n"<<expectedOutputs(0,0)<< " and "<<expectedOutputs(1,0)<<endl;
	//cout<<"\nFinal outputs : "<<Bout(0,0)<<" and "<<Bout(1,0)<<endl;
}

/***************************************************************************************************/

void backProp(){
	//WE JUST NEED TO ADJUST AND TUNE THE WT'S AND BIASES IN THE BACK PROP

	//SUM OF TOTAL SQUARED ERROR
	float Cost = 0;
	for(int i = 0;i < 2; i++){
		Cost += (Bout(i,0)-expectedOutputs(i,0))*(Bout(i,0)-expectedOutputs(i,0));
	}


	Matrix<float,8,8> deltaA; // with learning rate
	Matrix<float,2,8> deltaB; // with learning rate
	
	//BackProp for LAYER B
	for(int i = 0;i < 2;i++){
		for(int j = 0;j < 8;j++){
			
			float delta = 0;
			//CHECK THIS CHECK THIS CHECK THIS CHECK THIS CHECK THIS
			float a = 2*(Bout(i,0) - expectedOutputs(i,0));  // dC / dBout
			float b = Bout(i,0)*(1-Bout(i,0));                 // dBout / dBin
			float c = Aout(j,0);	      					 // dBin / dW(i)

			delta = a*b*c;

			deltaB(i,j) =  lr *delta;

			//CHECK THIS CHECK THIS CHECK THIS CHECK THIS CHECK THIS 

		}
	}

	//BackProp for LAYER A
	for(int i = 0;i < 8;i++){
		for(int j = 0;j < 8;j++){
			
			float delta = 0;
			//CHECK THIS CHECK THIS CHECK THIS CHECK THIS CHECK THIS

			float c  = inputs(j,0);                  // dAin / dW
			float b  = Aout(i,0)*(1 - Aout(i,0));    // dAout / dAin
			float a;                                 //dC / dAout

			float a0; 
			float a1;
			
			float a00 = 2*(Bout(0,0) - expectedOutputs(0,0));   //dC0/dBout
			float a01 = Bout(0,0)*(1 - Bout(0,0));				//dBout/dBin
			float a02 = weightsB(0,i);

			a0 = a00*a01*a02;
			

			float a10 = 2*(Bout(1,0) - expectedOutputs(1,0));   //dC0/dBout
			float a11 = Bout(1,0)*(1 - Bout(1,0));				//dBout/dBin
			float a12 = weightsB(1,i);

			a1 = a10*a11*a12;

			a = a0+a1;

			delta = a*b*c;
			deltaA(i,j) = lr * delta;


			//CHECK THIS CHECK THIS CHECK THIS CHECK THIS CHECK THIS 

		}
	}


	//UPDATING  WEIGHTS FOR LAYER B 
	for(int i = 0;i < 2;i++){
		for(int j = 0;j < 8;j++){
			weightsB(i,j) -=  deltaB(i,j);
		}
	}

	//UPDATING  WEIGHTS FOR LAYER A
	for(int i = 0;i < 8;i++){
		for(int j = 0;j < 8;j++){
			weightsA(i,j) -=  deltaA(i,j);
		}
	}
}

/***************************************************************************************************/

void debugPrint(){
	//	DEBUG
	cout<<"\ninputs : \n"<<inputs<<endl;
	cout<<"\nweightsA : \n"<<weightsA<<endl;
	cout<<"\nbiasA : \n"<<biasA<<endl;
	cout<<"\nAin : \n"<<Ain<<endl;
	cout<<"\nAout : \n"<<Aout<<endl;

	cout<<"\nweightsB : \n"<<weightsB<<endl;
	cout<<"\nbiasB : \n"<<biasB<<endl;
	cout<<"\nBin : \n"<<Bin<<endl;
	cout<<"\nBout : \n"<<Bout<<endl;

	cout<<"\n\nExpected outputs : "<<expectedOutputs<<endl;

}

/***************************************************************************************************/

void train(int epoch){
	//*********DEBUG************ 
	//for(int j = 0;j < trainCases;j++){
		for(int i = 0;i < epoch;i++){
			
			int j = i%trainCases;

			inputs = matInput(j,0);
			expectedOutputs = matExpectedOutput(j,0);
			feedForward();
			backProp();
			feedForward();
			// cout<<"\n\n";
			// debugPrint();
			// cout<<"\n\n";
		}
	//}
	
}

/***************************************************************************************************/

void CheckTraining(){
	cout<<"Enter the 8 inputs : \n";
	Matrix<float,8,1> tst;
	for(int i = 0;i < 8;i++){
		cin>>tst(i,0);
	}

	inputs = tst;
	feedForward();
	cout<<Bout(0,0)<<" and "<<Bout(1,0)<<endl;

}

/***************************************************************************************************/

int main(void){
	//INITIALISATION
	init();
	feedForward();

	//debugPrint();
	train(100000);

	// inputs = matInput(0,0);
	// expectedOutputs = matExpectedOutput(0,0);
	// feedForward();

	// inputs = matInput(1,0);
	// expectedOutputs = matExpectedOutput(1,0);
	// feedForward();
	int i = 0;
	while(i = 1){
		CheckTraining();
	}
	//debugPrint();

}

