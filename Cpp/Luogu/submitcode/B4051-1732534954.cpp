#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],b[100005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=m;i++){
		if(n!=1){
			if(b[i]>=0){
				a[n]+=b[i];
			}
			else{
				a[1]+=b[i];
			}
		}
		else{
			a[1]+=b[i];
		}
	}
	cout<<a[n];
	return 0;
}