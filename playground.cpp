#include <iostream>
#include <Eigen/Dense>
#include <math.h> 

using namespace Eigen;
using namespace std;

int main (void){
	// srand ( time(NULL) );
	// for(int i = 0;i < 100 ;i++){

		
	// float den = rand()%10 + 1;
	// float num = rand()%3 -1;
	// cout<<(num/den)<<endl;

	// }

	Matrix<int,3,3> m,n;
	m<<1,2,3,4,5,6,7,8,9;
	cout<<m<<endl;

	cout<<"Transpose is : \n";
	cout<<m.transpose()<<endl<<endl;

	cout<<"Original : \n";
	cout<<m<<endl;

	//cannot directly do m = m.transpose()
	//or m.transpose()

	n = m.transpose();
	m = n;


	cout<<"\nOriginal n : \n";
	cout<<m<<endl;
}