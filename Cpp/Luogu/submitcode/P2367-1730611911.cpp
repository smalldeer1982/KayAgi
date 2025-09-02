#include<bits/stdc++.h>
using namespace std;
int n,p,a[5000005],b[5000005],minn=1e9;
int main(){
	cin>>n>>p;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=a[i]-a[i-1];
	}
	for(int i=1;i<=p;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		b[x]+=z;
		b[y+1]-=z;
	}
	for(int i=1;i<=n;i++){
		b[i]=b[i-1]+b[i];
		minn=min(minn,b[i]);
	}
	cout<<minn;
	return 0;
}