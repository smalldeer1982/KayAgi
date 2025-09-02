#include<bits/stdc++.h>
using namespace std;
int n,m;
long long sum=0,sum1=0;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			sum+=min(n-i+1,m-j+1);
			sum1+=(n-i+1)*(m-j+1)-min(n-i+1,m-j+1);
		}
	}
	cout<<sum<<" "<<sum1;
	return 0;
}