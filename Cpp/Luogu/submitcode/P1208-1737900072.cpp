#include<bits/stdc++.h>
using namespace std;
int n,m,sum,ans,cnt=1;
struct farmer{
	int c,p;
}a[2000005];
bool cmp(farmer x,farmer y){
	if(x.c<y.c){
		return true;
	}
	return false;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i].c>>a[i].p;
	}
	sort(a+1,a+n+1,cmp);
	while(sum<n){
		if(sum+a[cnt].p>=n){
			ans+=(n-sum)*a[cnt].c;
			sum+=a[cnt].p;
		}
		else{
			ans+=a[cnt].c*a[cnt].p;
			sum+=a[cnt].p;
		}
		cnt+=1;
	}
	cout<<ans;
	return 0;
}
