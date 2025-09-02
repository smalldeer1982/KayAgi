#include<bits/stdc++.h>
using namespace std;
int n,a[1000005],sum=-1,ans;
bool flag=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(a[i]!=sum){
			ans+=1;
			sum=a[i];
		}
	}
	cout<<ans;
	return 0;
}
