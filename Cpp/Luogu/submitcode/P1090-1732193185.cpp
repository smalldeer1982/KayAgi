#include<bits/stdc++.h>
using namespace std;
long long n,a[10005],sum=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}	
	sort(a+1,a+1+n);
	for(int i=1;i<=n-1;i++){
		a[i+1]+=a[i];
		sum+=a[i+1];
		sort(a+1+i,a+1+n);
	}
	cout<<sum;
	return 0;
}