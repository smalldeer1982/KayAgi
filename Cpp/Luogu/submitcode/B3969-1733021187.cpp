#include<bits/stdc++.h>
using namespace std;
int n,b,a[1000005],sum=0;
void prime(){
	for(int i=2;i<=n;i++){
		if(!a[i]){
			for(int j=i;j<=n;j+=i){
				a[j]=i;
			}
		}
	}
}
int main(){
	cin>>n>>b;
	a[1]=1;
	prime();
	for(int i=1;i<=n;i++){
		if(a[i]<=b){
			sum+=1;
		}
	}
	cout<<sum;
	return 0;
}