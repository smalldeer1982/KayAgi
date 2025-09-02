#include<bits/stdc++.h>
using namespace std;
long long n,m,p[100005],b[100005],ans=0;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>p[i];
		if(i>1){
			b[min(p[i],p[i-1])+1]+=1;
			b[max(p[i],p[i-1])+1]-=1; 
		}
	}
	for(int i=1;i<=n;i++){
		b[i]=b[i]+b[i-1];
	}
	for(int i=2;i<=n;i++){
		long long x,y,z;
		cin>>x>>y>>z;
		ans+=min(x*b[i],y*b[i]+z);
	}
	cout<<ans;
	return 0;
}