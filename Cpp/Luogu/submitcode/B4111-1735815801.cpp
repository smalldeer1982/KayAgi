#include<bits/stdc++.h>
using namespace std;
int n,m,sum=0,a[105],b[105];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			sum+=(a[i]+b[j])*max(a[i],b[j]);
		}
	}
	cout<<sum;
	return 0;
}
