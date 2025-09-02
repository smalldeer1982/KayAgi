#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,fa[1005],ans=0;
void init(){
	ans=0;
	for(int i=1;i<=1000;i++){
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
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(true){
		init();
		cin>>n;
		if(n==0){
			break;
		}
		cin>>m;
		for(int i=1;i<=m;i++){
			int x,y;
			cin>>x>>y;
			merge(x,y);
		}
		for(int i=1;i<=n;i++){
			if(fa[i]==i){
				ans+=1;
			}
		}
		cout<<ans-1<<endl;
	}
	return 0;
}
