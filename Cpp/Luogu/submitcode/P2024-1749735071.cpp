#include<bits/stdc++.h>
using namespace std;
int n,m,ans=0;
int fa[300005];
struct node{
	int u,v,w;
}e[300005];
void init(){
	for(int i=1;i<=n*3;i++){
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
		fa[fy]=fx;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	init();
	while(m--){
		int op,x,y;
		cin>>op>>x>>y;
		if(x>n||y>n){
			ans+=1;
			continue;
		}
		if(op==1){
			if(find(x+n)==find(y)||find(x+2*n)==find(y)){
				ans+=1;
				continue;
			}
			merge(x,y);
			merge(x+n,y+n);
			merge(x+2*n,y+2*n);
		}
		else{
			if(x==y){
				ans+=1;
				continue;
			}
			if(find(x)==find(y)||find(x+2*n)==find(y)){
				ans+=1;
				continue;
			}
			merge(x,y+2*n);
			merge(x+n,y);
			merge(x+2*n,y+n);
		}
	}	
	cout<<ans<<'\n';
	return 0;
} 