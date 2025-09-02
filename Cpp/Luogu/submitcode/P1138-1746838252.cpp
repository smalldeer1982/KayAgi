#include<bits/stdc++.h>
using namespace std;
int n,k,a[10005],sum;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	int x=0;
	for(int i=1;i<=n;i++){
		x+=1;
		int sum=i;
		while(a[sum]==a[i]){
			sum+=1;
		}
		i=sum-1;
		if(x==k){
			cout<<a[i];
			return 0;
		}
	}
	cout<<"NO RESULT";
	return 0;
} 