#include<bits/stdc++.h>
using namespace std;
int n,m,b[32005],dp[32005];
struct node{
	int num,v,p,q;
}a[32005];
bool cmp(node x,node y){
	if(x.num==y.num){
		return x.q<y.q;
	}
	return x.num<y.num;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y,z;
		cin>>x>>y>>z;
		if(z==0){
			a[i].num=i,a[i].v=x,a[i].p=x*y,a[i].q=0;
		}
		else{
			b[z]+=1;
			a[i].num=z,a[i].v=x,a[i].p=x*y,a[i].q=b[z];
		}
	}
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++){
		if(a[i].q){
			continue;
		}
		for(int j=n;j>=a[i].v;j--){
			dp[j]=max(dp[j],dp[j-a[i].v]+a[i].p);
			if(a[i+1].num==a[i].num&&j>=a[i].v+a[i+1].v){
				dp[j]=max(dp[j],dp[j-a[i].v-a[i+1].v]+a[i].p+a[i+1].p);
			}
			if(a[i+2].num==a[i].num&&j>=a[i].v+a[i+2].v){
				dp[j]=max(dp[j],dp[j-a[i].v-a[i+2].v]+a[i].p+a[i+2].p);
			}
			if(a[i+2].num==a[i].num&&j>=a[i].v+a[i+1].v+a[i+2].v){
				dp[j]=max(dp[j],dp[j-a[i].v-a[i+1].v-a[i+2].v]+a[i].p+a[i+1].p+a[i+2].p);
			}
		}
	}
	cout<<dp[n];
	return 0;
}
