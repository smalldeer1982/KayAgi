#include<bits/stdc++.h>
using namespace std;
long long n,a[305],ans=0,now;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	ans+=a[n]*a[n];
	ans+=(a[n]-a[1])*(a[n]-a[1]);
	now=a[1];
	for(int i=2;i<=n/2;i++){
		for(int j=1;j<=2;j++){
			if(j==2){
				ans+=(now-a[i])*(now-a[i]);
				now=a[i];
			}
			else{
				ans+=(now-a[n-i+1])*(now-a[n-i+1]);
				now=a[n-i+1];
			}
		}
	}
	if(n%2==1){
		ans+=(now-a[n/2+1])*(now-a[n/2+1]);
	}
	cout<<ans;
	return 0;
}