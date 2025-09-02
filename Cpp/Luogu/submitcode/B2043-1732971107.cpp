#include<bits/stdc++.h>
using namespace std;
int n;
bool flag=0;
int main(){
	cin>>n;
	if(n%3==0){
		cout<<3<<" ";
		flag=1;
	}
	if(n%5==0){
		cout<<5<<" ";
		flag=1;
	}
	if(n%7==0){
		cout<<7<<" ";
		flag=1;
	}
	if(flag==0){
		cout<<"n";
	}
	return 0;
}