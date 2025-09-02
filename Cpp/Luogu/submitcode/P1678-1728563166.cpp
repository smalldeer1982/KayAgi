#include<bits/stdc++.h>
using namespace std;
int m,n,a[100005],b[100005],ans=0,k;
int main(){
	cin>>m>>n;
	for(int i=0;i<m;i++){
		cin>>a[i];
	}
	for(int i=0;i<n;i++){
		cin>>b[i];
	}
	sort(a,a+m);
	for(int i=0;i<n;i++){
		if(a[0]>=b[i]){
			ans+=a[0]-b[i];
		}
		else if(a[m-1]<=b[i]){
			ans+=b[i]-a[m-1];
		}
		else
		{
			k=lower_bound(a,a+m,b[i])-a;
			ans+=min(a[k]-b[i],b[i]-a[k-1]);
		}
	}
	cout<<ans;
	return 0;
}