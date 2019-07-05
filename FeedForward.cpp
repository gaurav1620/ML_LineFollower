/**********************************************************************
 * NEURAL NETWORK WITH 8 INPUT ,8 HIDDEN AND 2 OUTPUT NODES
 * Made for  LINE FOLLOWER robots.
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
// 4 th July 2019

@ Website : gaurav1620.rf.gd
@ Github  : gaurav1620
@ Insta   : may_be_gaurav 
@ Gmail   : gauravak007@gmail.com

*/
#include<iostream>
#include<vector>
#include <Eigen/Dense>
#include <math.h> 
using namespace std;
using namespace Eigen;


float sigmoid(float x){
	float denominator = (1 + exp(-x));
	float f =  1/denominator;
	if(f > 0.5){
		return 1;
	}
	return 0;
}

float sigmoidVal(float x){
	float denominator = (1 + exp(-x));
	float f =  1/denominator;
	return f;
}

int main(void){

	Matrix<float,2,1> expectedOutput;

	//Layer One.

	Matrix<float,8,8> weights_1;
	Matrix<float,8,1> inputs_1;
	Matrix<float,8,1> bais_1;
	Matrix<float,8,1> output_1;

	Matrix<float,8,1> input_2;
	Matrix<float,2,1>  bias_2;
	Matrix<float,2,8> weights_2;
	Matrix<float,2,1> output_2; 

	// Init Random Weights
	srand ( time(NULL) );
	for(int i = 0;i < 8 ;i++){

		for(int j = 0;j < 8;j++){

			//Gives a random value between -1 and 1
			float den = rand()%10 + 1;
			float num = rand()%3 -1;

			//Inportant step
			weights_1(i,j) = (num/den);
		}
	}


	// Take the values for the biases of layer 1
	cout<<"Enter the Input values"<<endl;
	for(int i = 0;i < 8;i++){

		cin>>inputs_1(i,0);
		bais_1(i,0) = 0;

	}

	cout<<"Enter the expected output values (2): \n";
	for(int i = 0; i < 2;i++){
		cin>>expectedOutput(i,0);
	}

	cout<<"The Weights are : \n";
	cout<<weights_1<<endl<<endl<<endl;

	cout<<"Inputs are : \n";
	cout<<inputs_1<<endl<<endl<<endl;

	cout<<"Bias are : \n";
	cout<<bais_1<<endl<<endl<<endl;


	cout<<"\nMultiplying wt and inputs : \n";
	cout<<weights_1 * inputs_1<<endl<<endl;

	//Output of the 
	output_1 = weights_1 * inputs_1;
	cout<<"\nOutput for layer 1  :  "<<endl;
	cout<<output_1<<endl;

	//Adding the biases
	output_1 += bais_1;

	cout<<"\nOutput for layer 1 after adding bias(initial is zero)  :  "<<endl;
	cout<<output_1<<endl;



	Matrix <float,8,1> sigOut;

	//Sigmoid gives a value between 0 and 1 so if the val is >0.5 we take the output of the neuron as 1 else 0
	for(int i = 0;i < 8;i++){
		sigOut(i,0) = sigmoidVal(output_1(i,0));

	}
	cout<<"SigmoidVal: \n"<<sigOut<<endl;




	//INPUT 2 Algorithm

	input_2 = sigOut;

	//init rand weights
	srand ( time(NULL) );
	for(int i = 0;i < 2 ;i++){

		for(int j = 0;j < 8;j++){
			float den = rand()%10 + 1;
			float num = rand()%3 -1;

			//Inportant step
			weights_2(i,j) = (num/den);
		}
	}

	cout<<"\nWeights for Layer 2 : \n"<<weights_2<<endl;


	Matrix<float,2,1> tmp;
	tmp = weights_2*input_2;

	cout<<"\nInputs after multiplying with weights : \n"<<tmp<<endl;

	bias_2<<0,0;
	tmp+= bias_2;

	cout<<"\nweighted sum after adding biases : \n"<<tmp<<endl;

	// sigmoid values;
	Matrix<float,2,1> sigVal;

	//Passing weighted sum through the sigmoid
	for(int i = 0; i < 2;i++){
		output_2(i,0) = sigmoid(tmp(i,0));
		sigVal(i,0) = sigmoidVal(tmp(i,0));
	}


	cout<<"\nOutput Confidence : \n"<<sigVal<<endl<<endl;

	cout<<"\nFinal outputs : \n"<<output_2<<endl;

	float cost = 0;

	for(int i = 0; i < 2;i++){
		cost += (expectedOutput(i,0)-sigVal(i,0))*(expectedOutput(i,0)-sigVal(i,0));

	}

	cout<<"\nCost = "<<cost<<endl;

	float avgCost = cost/2;

	cout<<"\nAverage Cost  =  "<<avgCost<<endl;

}

