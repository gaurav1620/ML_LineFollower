#include<iostream>
#include<vector>
#include <Eigen/Dense>
#include <math.h> 
using namespace std;
using namespace Eigen;


float sigmoid(float x){
	float denominator = (1 + exp(-x));
	return 1/denominator;

}

int main(void){

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
		if(sigmoid(output_1(i,0))>0.5){
			sigOut(i,0) = 1;
		}else{
			sigOut(i,0) = 0;
		}

	}
	cout<<"Sigmoid : \n"<<sigOut<<endl;




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

	//Passing weighted sum through the sigmoid
	for(int i = 0; i < 2;i++){
		if(sigmoid(tmp(i,0)) > 0.5){
			output_2(i,0) = 1;
		}else{
			output_2(i,0) = 0;
		}
	}

	cout<<"\nFinal outputs : \n"<<output_2<<endl;


}

