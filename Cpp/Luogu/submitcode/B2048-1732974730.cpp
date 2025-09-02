#include<bits/stdc++.h>
using namespace std;
int x,sum=0;
char c;
int main(){
	cin>>x>>c;
	if(x<=1000){
		sum+=8;
	}
	else{
		sum+=8;
		if(x%500==0){
			sum+=(x-1000)/500*4;
		}
		else{
			sum+=((x-1000)/500+1)*4;
		}
	}
	if(c=='y'){
		sum+=5;
	}
	cout<<sum;
	return 0;
}