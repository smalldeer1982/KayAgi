# [SEERC 2020] Disk Sort

## 题目描述

你有 $n+1$ 根棍子，一开始 $1 \sim n$ 的每根棍子上面都会存在 $3$ 个盘，颜色不超过 $n$ 种。

每次操作，你可以选择一对 $(a_i,b_i)$，表示将 $a_i$ 最顶上的圆盘放到 $b_i$ 最上面（$a_i$ 的圆盘数量至少为 $1$，$b_i$ 的数量至多为 $2$）。

你需要构造出一种合法方案使得操作结束后每个盘上的颜色都一样且 $n+1$ 号为空。

## 样例 #1

### 输入

```
4
2 3 1 4
2 1 1 4
2 3 3 4```

### 输出

```
8
3 5
3 5
2 3
2 5
2 3
5 2
5 2
5 2
```

## 样例 #2

### 输入

```
2
1 2
1 2
1 2```

### 输出

```
0```

# 题解

## 作者：Unnamed114514 (赞：1)

首先，在构造过程中，我们应**始终保持一根空柱子**，这样我们构造的方式始终相同。

注意到在这种情况下，至少有一种未解决的颜色有一个盘在最顶上，因为解决的颜色只会占一个最顶上的盘，最顶上的盘一共有 $n$ 个，所以一定会有剩的。

我们找到这种颜色，并求出它的三个位置，剩下的问题下放到手玩即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,c[3][N],tot[N],top[N];
bool vis[N];
vector<pair<int,int> > ans;
void upd(int a,int b){
	ans.emplace_back(make_pair(a,b));
	c[--top[b]][b]=c[top[a]++][a];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=0;i<3;++i) for(int j=1;j<=n;++j) cin>>c[i][j];
	top[n+1]=3;
	for(int T=1;T<n;++T){
		int emp=0;
		for(int i=1;i<=n+1;++i) if(top[i]==3){
			emp=i;
			break;
		}
		for(int i=1;i<=n+1;++i) if(i!=emp&&!vis[c[0][i]]){
			vis[c[0][i]]=1;
			int tot=0;
			pair<int,int> p[3];
			for(int j=0;j<3;++j) for(int k=1;k<=n+1;++k) if(k!=emp&&c[j][k]==c[0][i]) p[tot++]=make_pair(j,k);
			if(!p[2].first) upd(p[0].second,emp),upd(p[1].second,emp),upd(p[2].second,emp),upd(p[2].second,p[0].second),upd(p[2].second,p[1].second);
			else if(!p[1].first){
				if(p[0].second==p[2].second){
					upd(p[0].second,emp),upd(p[1].second,emp);
					if(p[2].first==1) upd(p[0].second,emp),upd(p[0].second,p[1].second);
					else upd(p[0].second,p[1].second),upd(p[0].second,emp);
				} else if(p[1].second==p[2].second){
					upd(p[0].second,emp),upd(p[1].second,emp);
					if(p[2].first==1) upd(p[1].second,emp),upd(p[1].second,p[0].second);
					else upd(p[1].second,p[0].second),upd(p[1].second,emp);
				} else{
					upd(p[0].second,emp),upd(p[1].second,emp),upd(p[2].second,p[0].second);
					if(p[2].first==1) upd(p[2].second,emp),upd(p[2].second,p[1].second);
					else upd(p[2].second,p[1].second),upd(p[2].second,emp);
				}
			} else{
				if(p[0].second==p[1].second){
					if(p[2].second!=p[0].second){
						if(p[1].first==1){
							upd(p[0].second,emp),upd(p[0].second,emp),upd(p[2].second,p[0].second);
							if(p[2].first==1) upd(p[2].second,emp),upd(p[2].second,p[0].second);
							else upd(p[2].second,p[0].second),upd(p[2].second,emp);
						} else upd(p[2].second,emp),upd(p[2].second,emp),upd(p[0].second,p[2].second),upd(p[0].second,emp),upd(p[0].second,p[2].second);
					}
				} else if(p[0].second==p[2].second){
					if(p[2].first==1) upd(p[0].second,emp),upd(p[0].second,emp),upd(p[1].second,p[0].second),upd(p[1].second,emp),upd(p[1].second,p[0].second);
					else{
						if(p[1].first==1) upd(p[0].second,emp),upd(p[1].second,p[0].second),upd(p[1].second,emp),upd(p[0].second,p[1].second),upd(p[0].second,p[1].second),upd(p[0].second,emp);
						else upd(p[1].second,emp),upd(p[1].second,emp),upd(p[0].second,p[1].second),upd(p[0].second,emp),upd(p[0].second,p[1].second);
					}
				} else if(p[1].second==p[2].second) upd(p[1].second,emp),upd(p[0].second,p[1].second),upd(emp,p[0].second);
				else{
					if(p[1].first==1){
						upd(p[0].second,emp),upd(p[1].second,p[0].second),upd(p[1].second,emp),upd(p[2].second,p[1].second);
						if(p[2].first==1) upd(p[2].second,emp),upd(p[2].second,p[1].second);
						else upd(p[2].second,p[1].second),upd(p[2].second,emp);
					} else upd(p[2].second,emp),upd(p[2].second,emp),upd(p[0].second,p[2].second),upd(p[1].second,p[0].second),upd(p[1].second,emp),upd(p[1].second,p[2].second);
				}
			}
			for(int i=1;i<=n+1;++i) if(top[i]!=0&&top[i]!=3) exit(0);
			break;
		}
	}
	int emp=0;
	for(int i=1;i<=n+1;++i) if(top[i]==3){
		emp=i;
		break;
	}
	if(emp!=n+1) upd(n+1,emp),upd(n+1,emp),upd(n+1,emp);
	cout<<ans.size()<<endl;
	for(auto p:ans) cout<<p.first<<' '<<p.second<<endl;
	return 0;
}
```

---

## 作者：Coffins (赞：1)

模拟赛出的题，~~不知道为何感觉有点水~~

手玩发现貌似可以逐个还原（？

但是一细找发现又寄了，如果所有 $i$ 都在最下面那么 3 个空位不够用。

然而真寄了吗？

其实我们定义一个数字 $i$ 的权值为其三个盘的深度之和，每次排序取权值最小的还原就可以完成所有过程了。

这是因为在我们限定了每次取最小后，我们还原的 $i$ 的三个盘的深度排列只能是 $\{1,2,3\}$，$\{1,2,2\}$，$\{1,1,3\}$，$\{1,1,2\}$，$\{1,1,1\}$ 之一，其他的都不可能作为最小出现，否则深度为 1 的点数量就一定会小于深度为 2 或 3 的点，就不合法了。

这样我们分类讨论一下这 5 种情况，发现每次最多只需要 6 次操作，这样就成功把次数压缩到 $6n$ 了。

你可能会问，如果最后的空位不在 $n+1$ 上怎么办，实际上我们只需要还原 $n-1$ 次，最后一种自动就排好了，所以我们在最后手动花 3 次把空位移过去即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
using pii=pair<int,int>;
int n,tme,c[N];bool vs[N];
int d[N][4],ps[N][4];
vector<pii> vc;
struct Node
{
	int a,b,c;
	Node(int x=0,int y=0,int z=0):
	a(x),b(y),c(z){}
};int cr;vector<pii> rs;
bool operator==(Node x,Node y)
{return x.a==y.a&&x.b==y.b&&x.c==y.c;}
int mp[4][N],h[N];
void ins(int x,int y)
{
	rs.push_back({x,y});
	int vl=mp[h[x]][x],t;
	for(int i=1;i<=3;i++)
	{
		if(d[vl][i]==h[x]&&ps[vl][i]==x)
		t=i;
	}h[x]++,h[y]--;
	mp[h[y]][y]=vl;
	d[vl][t]=h[y],ps[vl][t]=y;
}
void solve(int p,vector<pii> vc)
{
	int x,y,z;Node nd(vc[0].first,vc[1].first,vc[2].first);
	x=vc[0].second,y=vc[1].second,z=vc[2].second;
	if(nd==Node(1,2,3))
	{
	    if(x==y&&y==z)return;
		ins(x,cr);
		if(x!=y)ins(y,x);
		ins(y,cr);
		if(z!=y)ins(z,y),ins(z,y);
		ins(z,cr);cr=z;
	}else if(nd==Node(1,2,2))
	{
		ins(x,cr);
		if(x==y)ins(y,cr),ins(z,x),ins(z,cr),ins(z,x),cr=z;
		else if(x==z)ins(z,cr),ins(y,x),ins(y,cr),ins(y,x),cr=y;
		else ins(y,x),ins(y,cr),ins(z,y),ins(z,cr),ins(z,y),cr=z;
	}else if(nd==Node(1,1,3))
	{
		ins(x,cr),ins(y,cr);
		if(z!=x)ins(z,x);
		if(z!=y)ins(z,y);
		ins(z,cr);cr=z;
	}else if(nd==Node(1,1,2))
	{
		ins(x,cr),ins(y,cr);
		if(z==x)ins(z,cr),ins(z,y);
		else if(z==y)ins(z,cr),ins(z,x);
		else ins(z,x),ins(z,cr),ins(z,y);
		cr=z;
	}else if(nd==Node(1,1,1))
	{
		ins(x,cr),ins(y,cr),ins(z,cr);
		ins(z,x),ins(z,y);cr=z;
	}
}
int main()
{
	cin>>n;cr=n+1;h[n+1]=4;
	for(int j=1;j<=3;j++)
	for(int i=1;i<=n;i++)
	{
		int vl;cin>>vl;c[vl]++;
		d[vl][c[vl]]=j;
		ps[vl][c[vl]]=i;
		mp[j][i]=vl,h[i]=1;
	}//cout<<"===\n";
	for(int t=1;t<=n;t++)
	{
		vc.clear();
		for(int i=1;i<=n;i++)
		if(!vs[i])
		{
			int s=0;
			for(int j=1;j<=3;j++)s+=d[i][j];
			vc.push_back({s,i});
		}sort(vc.begin(),vc.end());
		int id=vc[0].second;vc.clear();
		for(int i=1;i<=3;i++)
		vc.push_back({d[id][i],ps[id][i]});
		sort(vc.begin(),vc.end());
		solve(id,vc);vs[id]=1;
		/*for(int i=1;i<=n+1;i++)
		{
			for(int j=3;j>=h[i];j--)
			cout<<mp[j][i]<<' ';
			cout<<'\n';
		}cout<<"===\n";*/
	}if(cr!=n+1)ins(n+1,cr),ins(n+1,cr),ins(n+1,cr);
	cout<<rs.size()<<'\n';
	for(auto el:rs)cout<<el.first<<' '<<el.second<<'\n';
	return 0;
}


```

---

