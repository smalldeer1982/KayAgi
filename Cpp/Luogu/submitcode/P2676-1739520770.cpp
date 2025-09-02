#include<bits/stdc++.h>
using namespace std;
int n,k,a[20005],sum;
bool cmp(int x,int y){
	if(x>y){
		return true;
	}
	return false;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		sum+=a[i];
		if(sum>=k){
			cout<<i;
			break;
		}
	}
	return 0;
}