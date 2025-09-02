#include<bits/stdc++.h>
using namespace std;
int l,m,u,v,a[10005],sum;
int main(){
	cin>>l>>m;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		for(int j=u;j<=v;j++){
			a[j]=1;
		}
	}
	for(int i=0;i<=l;i++){
		if(a[i]==0){
			sum+=1;
		}
	}
	cout<<sum;
	return 0;
}