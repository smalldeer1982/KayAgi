#include<bits/stdc++.h>
using namespace std;
int n,a[1005],b[1005],sum=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(a[i+1]==1||i==n){
			cnt+=1;
			sum+=1;
			b[cnt]=sum;
			sum=0;
		}
		else{
			sum+=1;
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++){
		cout<<b[i]<<" ";
	}
	return 0;
}
