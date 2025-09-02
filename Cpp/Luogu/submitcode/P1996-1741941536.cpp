#include<bits/stdc++.h>
using namespace std;
int n,k,vis[105],sum,x,temp;
int main(){
	cin>>n>>k;
	temp=k;
	while(sum<n){
		x+=1;
		if(x==n+1){
			x=1;
		}
		if(vis[x]==0){
			temp-=1;
			if(temp==0){
				vis[x]=1;
				temp=k;
				sum+=1;
				cout<<x<<" ";
			}
		}
	}
	return 0;
}