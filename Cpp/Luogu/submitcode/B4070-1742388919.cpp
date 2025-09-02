#include<bits/stdc++.h>
using namespace std;
long long n,a[1000005];
int ans=0;
int maths(long long x){
	for(int i=10;i>=1;i--){
		if((1+i)*i/2<=x){
			return i;
		}
	}
}
int main(){
	cin>>n;
	for(long long i=2;i<=sqrt(n);i++){
		while(n%i==0){
			n/=i;
			a[i]+=1;
		}
	}
	for(int i=2;i<=1000000;i++){
		if(a[i]>=1){
			ans+=maths(a[i]);
		}
	}
	if(n>1){
		ans+=1;
	}
	cout<<ans;
	return 0;
}
