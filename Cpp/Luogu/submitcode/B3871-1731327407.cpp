#include<bits/stdc++.h>
using namespace std;
long long n,sum=0,x;
bool flag=1;
int main(){
	cin>>n;
	x=n;
	for(long long i=2;i<=sqrt(n);i++){
		sum=0;
		while(x%i==0){
			sum+=1;
			x/=i;
		}
		if(flag==1&&sum>=1){
			if(sum>1){
				cout<<i<<"^"<<sum;
			}
			else if(sum==1){
				cout<<i;
			}
			flag=0;
		}
		else{
			if(sum>1){
				cout<<" * "<<i<<"^"<<sum;
			}
			else if(sum==1){
				cout<<" * "<<i;
			}
		}
	}
	if(x==n){
		cout<<x;
	}
	else if(x>1){
		cout<<" * "<<x;
	}
	return 0;
}