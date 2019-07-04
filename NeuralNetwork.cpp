#include<iostream>
#include<vector>
#include </home/samiksha/Desktop/Codes/IntellegentLineFollower/Eigen/Dense>

#include <math.h> 
using namespace std;


float sigmoid(float x){
	float denominator = (1 + exp(-x));
	return 1/denominator;

}

float myRandom(){
	//gives random float between -1 and +1 example -0.124
	srand ( time(NULL) );
	float den = rand()%10 + 1;
	float num = rand()%3 -1;
	return (num/den);
}

//weighted_Sum_Adding_Bias_And_Passing_Through_Sigmoid
float wtSumFor_I_H(float inpArr[8],float wtArr[8],float bias){

	float sum = 0;

	for(int i = 0;i < 8 ;i++)
		sum += inpArr[i] * wtArr[i];

	return sigmoid(sum + bias);
}



//Gives random weights
void init_Weight_Matrix(float* matrix[8][8]){


	for(int i = 0;i < 8; i++){
		for(int j = 0;j < 8; i++){
			*matrix[i][j] = myRandom();
		}
	}
}




void train(){



}

float feedForward(){


}


int main(void){

	vector<vector<int>> v;

	for(int i = 0;i < 8; i++){

		vector<int> tmp;
		for(int j = 0; j < 8; j++){
			int h = i*10;
			tmp.push_back(h+j);
		}
		v.push_back(tmp);
		
	}


	for(int i = 0;i < v.size(); i++){

		if(i == 0){
			for(int j = 0; j < v[i].size(); j++){

			cout<<v[i][j]<<"  ";
		}
		cout<<endl;
	}else{
		for(int j = 0; j < v[i].size(); j++){

			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}

		
	}

}