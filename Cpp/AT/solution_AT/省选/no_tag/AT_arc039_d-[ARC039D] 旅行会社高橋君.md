# [ARC039D] 旅行会社高橋君

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc039/tasks/arc039_d

高橋君とあなたはTK国でHS会社という旅行会社を経営しています。 TK国は $ N $ 個の頂点と $ M $ 本の辺からなる連結な単純無向グラフです。各頂点にはそれぞれ $ 1 $ から $ N $ の番号が振られています。

HS会社では、顧客ごとに旅行計画を立てて提供するサービスを行っています。 これまでは、旅行計画を温もりのある手作業で作成していました。 ですが突然の旅行ブームがTK国に訪れ、ナウでヤングな若者は皆旅行をするようになりました。もちろん会社は大忙し、とうとうコンピューターに頼ることにしました。

HS会社では、顧客から始点、中継点、終点という $ 3 $ つの頂点を与えられるので、始点から中継点を通り終点へと到着するような旅行計画を提供しています。 ただし、顧客が退屈しないように、同じ辺を複数回通るような旅行計画は提供しないようにしています。同じ頂点を複数回通る事に制限はありません。つまり旅行計画は、始点から中継点を通り終点に到着するトレイルです。

あなたはとりあえず、顧客ごとにそのような旅行計画は存在するのかどうかだけを判別するプログラムを書くことにしました。

## 说明/提示

### Sample Explanation 1

以下にこの入力でのTK国を図示する。 !\[\](http://arc039.contest.atcoder.jp/img/arc/039/vn240wsdnl23fn4zd0i/D\_sample1.png) 一例として、 - $ 1 $ 番目の顧客には $ 1\ -\ 2\ -\ 3 $ - $ 3 $ 番目の顧客には $ 2\ -\ 3\ -\ 5\ -\ 4\ -\ 3 $ - $ 4 $ 番目の顧客には $ 3\ -\ 4\ -\ 5 $ という旅行計画が提供できる。 また、 $ 2 $ 番目の顧客に提供できる旅行計画は存在しない。

### Sample Explanation 2

以下にこの入力でのTK国を図示する。 !\[\](http://arc039.contest.atcoder.jp/img/arc/039/vn240wsdnl23fn4zd0i/D\_sample2.png)

### Sample Explanation 3

以下にこの入力でのTK国を図示する。 !\[\](http://arc039.contest.atcoder.jp/img/arc/039/vn240wsdnl23fn4zd0i/D\_sample3.png)

## 样例 #1

### 输入

```
5 5
1 2
2 3
3 4
4 5
5 3
4
1 2 3
1 3 2
2 4 3
3 4 5```

### 输出

```
OK
NG
OK
OK```

## 样例 #2

### 输入

```
7 7
4 7
1 7
2 6
2 4
3 4
3 5
3 7
11
3 5 6
6 4 7
5 7 3
4 7 2
4 3 6
2 7 6
1 2 4
2 7 3
7 1 4
3 2 5
2 6 7```

### 输出

```
NG
OK
OK
OK
OK
NG
NG
OK
NG
NG
NG```

## 样例 #3

### 输入

```
7 8
2 5
5 4
4 2
2 1
1 6
6 3
3 7
7 6
10
3 6 2
1 4 5
1 5 6
6 2 4
5 2 6
3 1 7
7 2 6
5 4 2
6 7 5
2 5 1```

### 输出

```
OK
OK
NG
OK
OK
NG
NG
OK
OK
OK```

# 题解

## 作者：World_Creater (赞：2)

这就是远古 ARC 的图图题。

看到题目中边不重复的限制，考虑往割边上想。

考虑边双缩点。这样一个边双内的点可以在满足限制的情况下互相到达。

因为边双连通分量内没有割点，所以它类似于很多个环套起来在多一些无用边，那我们把多出来的边扔掉只留下环套环的话它一定是一个欧拉图，这样就一定满足限制了。

边双缩点完后是一棵树，对于这个这棵树，我们想要知到：从起点出发能不能在边不重复的情况下，先经过中转点，再到达终点。

由于树上两点只有一条简单路径，因此我们只需要判定这个中转点是不是在起点和终点间的唯一简单路径即可，可以通过拆 LCA 来轻松做到。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct graph{
	int nxt[400005],head[100005],go[400005],k=1;
	void add(int u,int v)
	{
		nxt[++k]=head[u];
		head[u]=k;
		go[k]=v;
	}
}G1;
vector<int> G2[100005];
stack<int> sta;
int n,m;
int low[200005],dfn[200005],idx,sd[200005],cnt,vis[200005],f[100005][18],dep[100005],t;
void tarjan(int x,int fa)
{
	sta.emplace(x);
	t++;
	dfn[x]=low[x]=++idx;
	for(int i=G1.head[x];i;i=G1.nxt[i])
	{
		if(i==fa||(i^1)==fa) continue ;
		int g=G1.go[i];
		if(!dfn[g])
		{
			tarjan(g,i);
			low[x]=min(low[x],low[g]);
			if(low[g]>dfn[x])
			{
				int p;
				cnt++;
				do{
					assert(!sta.empty());
					p=sta.top();
					sta.pop();
					sd[p]=cnt;
				}while(p!=g);
			}
		}
		else low[x]=min(low[x],dfn[g]);
	}
}
void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	f[x][0]=fa;
	for(int i=1;(1<<i)<=dep[x];i++)
	{
		f[x][i]=f[f[x][i-1]][i-1];
	}
	for(auto g:G2[x])
	{
		if(g!=fa) dfs(g,x);
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	assert(dep[x]!=0);
	assert(dep[y]!=0);
	for(int i=__lg(dep[x]);dep[x]>dep[y];i--)
	{
		if(dep[x]-(1<<i)>=dep[y]) x=f[x][i];
	}
	if(x==y) return x;
	for(int i=__lg(dep[x]);i>=0;i--)
	{
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	}
	return f[x][0];
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		G1.add(u,v);
		G1.add(v,u);
	}
	G1.add(0,1);
	G1.add(1,0);
	tarjan(0,0);
	for(int i=1;i<=n;i++)
	{
		for(int j=G1.head[i];j;j=G1.nxt[j])
		{
			int g=G1.go[j];
			if(sd[i]!=sd[g])
			{
				G2[sd[i]].emplace_back(sd[g]);
				G2[sd[g]].emplace_back(sd[i]);
			}
		}
	}
	for(int i=1;i<=cnt;i++)
	{
		sort(G2[i].begin(),G2[i].end());
		G2[i].erase(unique(G2[i].begin(),G2[i].end()),G2[i].end());
	}

	dfs(1,0);
	int q;
	cin>>q;
	while(q--)
	{
		int u,v,w;
		cin>>u>>v>>w;
		u=sd[u];
		v=sd[v];
		w=sd[w];
		int p=lca(u,w);
		if(lca(v,p)==p&&(lca(u,v)==v||lca(v,w)==v)) puts("OK");
		else puts("NG");
	}
}
```

---

## 作者：__phiu (赞：0)

## Solution

由于一个边只能经过一次，不难想到把每个边双连通分量进行缩点，这样每个连通分量内一定是满足不重复经过的。

考虑不同强连通分量连边后，一定与其它强连通分量有且仅有一条边，因为这是连通图且他们不边双连通，也就是树的结构，那么经过中点 $z$ 等同于经过其所在的连通分量，保证起点和终点的路径中一定有中点即可，也就是起点和终点的公共祖先是中点祖先，并且中点是两者其中一个的祖先，用倍增跑 LCA 即可

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>g1[2000050],g2[2000050];
int n,m,q;
int in[2000050];
int st[2000050];
int dfn[2000500],low[2000500];
int idx,cnt;
int top;
bool vis[2000050];
void Tarjan(int now,int fa)
{
	dfn[now]=low[now]=++idx;
	st[++top]=now;
	vis[now]=1;
	for(int i=0;i<g1[now].size();i++)
	{
		int to=g1[now][i];
		if(to==fa)
			continue;
		if(!dfn[to])
		{
			Tarjan(to,now);
			if(low[to]>dfn[now])
			{
				int x;
				++cnt;
				do{
					x=st[top];
					top--;
					vis[x]=0;
					in[x]=cnt;
				}while(x!=to);			
			}
			low[now]=min(low[now],low[to]);
		}
		else if(vis[now])
			low[now]=min(low[now],dfn[to]);
	}
}
int dep[200050],fa[200050][32];
void dfs(int now,int f)
{
	dep[now]=dep[f]+1;
	fa[now][0]=f;
	for(int i=1;(1<<i)<=dep[now];i++)
		fa[now][i]=fa[fa[now][i-1]][i-1];
	for(int i=0;i<g2[now].size();i++)
		if(g2[now][i]!=f)
			dfs(g2[now][i],now);
}
int lca(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(int i=29;i>=0;i--)
		if(dep[x]-(1<<i)>=dep[y])
			x=fa[x][i];
	if(x==y)
		return x;
	for(int i=29;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		g1[x].push_back(y);
		g1[y].push_back(x);  
	}
	g1[0].push_back(1);
	g1[1].push_back(0);
	Tarjan(0,0); 
	for(int x=1;x<=n;x++)
	{
		for(int now=0;now<g1[x].size();now++)
		{
			int y=g1[x][now];
			if(in[x]!=in[y])
				g2[in[x]].push_back(in[y]),g2[in[y]].push_back(in[x]);  
		}
	}
	for(int i=1;i<=cnt;i++)
	{
		sort(g2[i].begin(),g2[i].end());
		g2[i].erase(unique(g2[i].begin(),g2[i].end()),g2[i].end()); 
	}
	dfs(1,0);
	int q;
	cin>>q;
	while(q--)
	{
		int x,y,z;
		cin>>x>>z>>y;
		x=in[x],z=in[z],y=in[y];
		int p=lca(x,y);
		if(lca(z,p)==p and (lca(x,z)==z or lca(y,z)==z))
			cout<<"OK"<<endl;
		else
			cout<<"NG"<<endl;
	}
}
```


---

