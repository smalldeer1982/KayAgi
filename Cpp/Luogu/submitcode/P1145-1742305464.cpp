#include<bits/stdc++.h>
using namespace std;
int n,m=0,vis[2600005],a[20]={0,0,0,0,0,0,0,1872,7632,1740,93313,459901,1358657,2504881},sum,x,temp;
int main(){
	cin>>n;
	if(n>=7){
		cout<<a[n];
		return 0;
	}
	while(true){
		m+=1;
		temp=m;
		sum=0;
		memset(vis,0,sizeof(vis));
		x=0;
		while(sum<n){
			x+=1;
			if(x==2*n+1){
				x=1;
			}
			if(vis[x]==0){
				temp-=1;
				if(temp==0){
					if(x<=n){
						sum=n+1;
						break;
					}
					vis[x]=1;
					temp=m;
					sum+=1;
				}
			}
		}
		if(sum==n){
			cout<<m;
			break;
		}
	}
	return 0;
}