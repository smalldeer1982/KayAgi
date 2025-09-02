#include<bits/stdc++.h>
using namespace std;
int n,q,a[1000005],b[100005];
int find(int x){
	int l=1,r=n+1,mid;
	while(l<r){
		mid=(l+r)/2;
		if(a[mid]>=x){
			r=mid;	
		}
		else{
			l=mid+1;
		}
	}
	if(a[l]==x){
		return l;
	}
	return -1;
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=q;i++){
		scanf("%d",&b[i]);
	}
	for(int i=1;i<=q;i++){
		cout<<find(b[i])<<" ";
	}
	return 0;
}