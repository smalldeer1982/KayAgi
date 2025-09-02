#include<bits/stdc++.h>
using namespace std;
int n,dist,a[100005],ans=0;
int main(){
	cin>>n>>dist;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=2;i<=n-1;i++){
		if(a[i+1]-a[i-1]<=dist){
			a[i]=a[i-1];
			ans+=1;
		}
	}
	cout<<ans;
	return 0;
}
