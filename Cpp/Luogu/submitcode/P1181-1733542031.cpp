#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],sum,ans=0;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(sum+a[i]>m){
			ans+=1;
			sum=a[i];
		}
		else{
			sum+=a[i];
		}
	}
	if(sum>0){
		ans+=1;
	}
	cout<<ans;
	return 0;
}