#include<bits/stdc++.h>
using namespace std;
int n;
long long a[200005],s[200005],sum=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=s[i-1]+a[i];
	}
	for(int i=1;i<=n;i++){
		sum+=a[i]*(s[n]-s[i]);
	}
	cout<<sum;
	return 0;
}