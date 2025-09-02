#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,a[maxn],t[maxn];
int sum[maxn];//大于i的数有几个 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		t[a[i]]+=1;
	}
	for(int i=0;i<=maxn;i++){
		sum[i]=sum[i-1]+t[i];
	}
	for(int i=1;i<=maxn;i++){
		sum[i]=n-sum[i]+t[i]; 
	}
	for(int i=maxn;i>=0;i--){
		if(sum[i]>=i){
			cout<<i;
			break;
		}
	}
	return 0;
}
