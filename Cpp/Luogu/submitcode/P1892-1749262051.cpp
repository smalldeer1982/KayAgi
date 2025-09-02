#include<bits/stdc++.h>
using namespace std;
int n,m,p;
int fa[2005];
void init(){
	for(int i=1;i<=2000;i++){
		fa[i]=i;
	}
}
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y){
	int fx,fy;
	fx=find(x);
	fy=find(y);
	if(fx!=fy){
		fa[fx]=fy;
	}
}
 main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	cin>>n>>m;
	while(m--){
		char c;
		int u,v;
		cin>>c>>u>>v;
		if(c=='F'){
			merge(u,v);
		}
		else{
			merge(u+n,v);
			merge(v+n,u);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(fa[i]==i){
			ans+=1;
		}
	}
	cout<<ans;
	return 0;
} 