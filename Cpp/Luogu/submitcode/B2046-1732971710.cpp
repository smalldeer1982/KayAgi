#include<bits/stdc++.h>
using namespace std;
int n;
double x,y;
int main(){
	cin>>n;
	x=n/1.2;
	y=50+n/3.0;
	if(x>y){
		cout<<"Bike";
	}
	else if(x<y){
		cout<<"Walk";
	}
	else{
		cout<<"All";
	}
	return 0;
}