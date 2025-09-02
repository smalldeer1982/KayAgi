#include<bits/stdc++.h>
using namespace std;
long long n,x,a[100005],sum=0;
int main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n-1;i++){
		if(a[i]+a[i+1]>x){
			sum+=(a[i]+a[i+1]-x);
			if(a[i+1]-(a[i]+a[i+1]-x)<0){
				a[i+1]=0;
				a[i]-=(x-a[i+1]);
			}
			else{
				a[i+1]-=(a[i]+a[i+1]-x);
			}
		}
	}
	cout<<sum;
	return 0;
}
