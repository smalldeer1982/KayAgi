#include<bits/stdc++.h>
using namespace std;
int n,q,y,a[1000005];
int judge(int l,int r,int x){
	if(l<r){
		int mid=(l+r)/2;
		if(a[mid]>=x){
			return judge(l,mid,x);
		}
		else{
			return judge(mid+1,r,x);
		}
	}
	if(a[l]==x){
		return l;
	}
	else{
		return -1;
	}
}

int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=q;i++){
		cin>>y;
		cout<<judge(1,n+1,y)<<" ";

	}
	return 0;
}