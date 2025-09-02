#include<bits/stdc++.h>
using namespace std;
long long n,a[1005],c[1005],dp[1005]={1},cnt=0;
void prime(){
	for(int i=2;i<=sqrt(1000);i++){
		if(a[i]){
			for(int j=i*i;j<=1000;j+=i){
				a[j]=0;
			}
		}
	}
}
int main(){
	for(int i=1;i<=1000;i++){
		a[i]=1;
	}
	a[1]=0;
	prime();
	cin>>n;
	for(int i=1;i<=n;i++){
		if(a[i]==1){
			cnt+=1;
			c[cnt]=i;
		}
	}
	for(int i=1;i<=cnt;i++){
		for(int j=c[i];j<=n;j++){
			dp[j]+=dp[j-c[i]];
		}
	}
	cout<<dp[n];
	return 0;
}
