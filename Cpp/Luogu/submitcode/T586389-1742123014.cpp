#include<bits/stdc++.h>
using namespace std;
int n,a[100005],maxn,sum=1;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	maxn=a[n];
	for(int i=n-1;i>=1;i--){
		if(a[i]!=a[i+1]){
			break;
		}
		else{
			sum+=1;
		}
	}
	cout<<maxn<<" "<<sum;
	return 0;
}
