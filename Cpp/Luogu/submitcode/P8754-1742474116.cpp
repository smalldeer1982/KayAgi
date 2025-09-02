#include<bits/stdc++.h>
using namespace std;
long long n,a[1000005],ans=1;
int main(){
	cin>>n;
	long long x=n;
	for(long long i=2;i<=sqrt(n);i++){
		while(x%i==0){
			x/=i;
			a[i]+=1;
		}
	}
	for(int i=2;i<=1000000;i++){
		if(a[i]%2==1){
			ans*=i;
		}
	}
	if(x>1){
		ans*=x;
	}
	cout<<ans;
	return 0;
}
