#include<bits/stdc++.h>
using namespace std;
int x;
bool flag=1,flag1=1;
int main(){
	for(int i=1;i<=8;i++){
		cin>>x;
		if(x!=i){
			flag=0;
		}
		if(x!=8-i+1){
			flag1=0;
		}
	}
	if(flag==1){
		cout<<"ascending";
	}
	else if(flag1==1){
		cout<<"descending";
	}
	else{
		cout<<"mixed";
	}
	return 0;
} 