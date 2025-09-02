#include<bits/stdc++.h>
using namespace std;
long long n,m,a[100005],b[100005];
bool check(long long x){
	long long pre=-1e18,num=0;
	for(int i=1;i<=m;i++){
		long long sp=max(pre+x,a[i]);
		if(sp>b[i]){
			continue;
		}
		long long sum=(b[i]-sp)/x+1;
		num+=sum;
		pre=sp+(sum-1)*x;
		if(num>=n){
			return true;
		}
	}
	return false;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i]>>b[i];
	}
	sort(a+1,a+m+1);
	sort(b+1,b+m+1);
	long long l=1,r=1e18+5;
	while(l<r){
		long long mid=(l+r+1)/2;
		if(check(mid)){
			l=mid;
		}
		else{
			r=mid-1;
		}
	}
	cout<<l;
	return 0;
}