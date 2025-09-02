#include<bits/stdc++.h>
using namespace std;
int n,m;
int fa[200005];
struct node{
	int u,v,w;
}e[200005];
bool cmp(node a,node b){
	return a.w>b.w;
} 
void init(){
	for(int i=1;i<=n*2;i++){
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
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	sort(e+1,e+1+m,cmp);
	for(int i=1;i<=m;i++){
		if(find(e[i].u)==find(e[i].v)){
			cout<<e[i].w<<endl;
			return 0;
		}
		merge(e[i].v,e[i].u+n);
		merge(e[i].u,e[i].v+n);
	}
    cout<<0<<endl;
	return 0;
} 