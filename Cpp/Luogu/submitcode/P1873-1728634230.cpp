#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000005];
int judge(int h){
	long long sum=0;
	for(int i=1;i<=n;i++){
		sum+=max(a[i]-h,0);
	}
	if(sum>=m){
		return 1;
	}
	return 0;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	int l=0,r=400001;
	while(l<r){
		int mid=(l+r)/2;
		if(judge(mid)){
			l=mid+1;
		}
		else{
			r=mid;
		}
	}
	cout<<l-1;
	return 0;
} 