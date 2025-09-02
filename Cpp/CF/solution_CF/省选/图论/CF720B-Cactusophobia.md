# Cactusophobia

## 题目描述

树是一个没有循环的连通无向图。

仙人掌图是一个无环、无平行边的连通无向图，每个边最多只属于一个环。Vasya 有一个仙人掌图，图的每一个边都有颜色。

Vasya 想移除最少数量的边，这样他的仙人掌图就变成了一棵树。

Vasya移除后，树上有尽可能多的不同颜色的边。请帮助他找出树上可以有多少种不同的颜色。

简单来说，就是让你求把这棵仙人掌删边成一棵 n 个节点的树后剩余的颜色最多种类数。

## 样例 #1

### 输入

```
4 4
1 2 4
2 3 1
3 4 2
4 2 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7 9
1 2 1
2 3 4
3 1 5
1 4 5
4 5 2
5 1 6
1 6 4
6 7 6
7 1 3
```

### 输出

```
6
```

# 题解

## 作者：xtx1092515503 (赞：9)

一种严格 $O(n)$ 的非网络流解法。一种 $O(n)$ 的非网络流解法。

------

Observation 1. 我们明显可以用点双或类似科技把每个环扒出来分开处理——显然它们是互相独立的。于是问题等价于每个环删掉一条边。

Observation 2. 若一条边不在任何环上，则无论最后怎么删东西，这条边都会留下，也即此种颜色一定会留下。于是，对于一个包含此种颜色的环，我们完全可以删掉环上此种颜色的边使其符合要求，并保留了环上其它所有颜色——也就是说，这使得环上其它所有颜色也变得一定会留下了。明显这些新增加的一定会留下的颜色还可以去继续把其它环变得一定会留下，于是发现这会形成一波连锁反应。至于连锁反应应该如何在保证复杂度的前提下模拟，我们待会再说。

Observation 3. 若一个环上某种颜色出现了至少两次，明显可以删掉其中一个而使该颜色仍然存在，且此环就符合了要求。也就是说，此种情形下，该环上所有颜色也是一定会留下的。明显这些一定留下的颜色也可以促生 Observation 2 中的连锁反应。

Observation 4. 在上述三个 Observation 全部执行完毕时，我们得到了一堆一定留下的颜色，以及一堆内部不出现重复颜色或是必留下的颜色的环。

Observation 5. 参照样例2，我们发现若有数种颜色在多个环中同时出现，且这种“同时出现”的关系成环，则所有涉及到的环上颜色同时可以留下。更形式化地说，如果我们建一张新图，图上每个点对应着 Observation 4 得到的环，且对于拥有相同颜色的两个环，在它们在新图上对应的点间连一条边（如果如果有多种颜色都同时出现，要连重边）。这样得到的新图上若出现了**不全由一种颜色产生**的环（重边也算环），则环所在的整个连通块上的点所对应的环都是一定留下的。而相反，对于新图上没有成环的连通块，会且只会删掉一种颜色，因为找不到一种删边的方式使得被删掉的所有边所对应的颜色都在其它环上有备份。

Observation 6. 因为不同的环间拥有相同颜色的关系是有传递性的，故由同一种颜色在新图中产生的边是成团的，可以达到 $n^2$ 级别。为了消减边数，我们额外开点表示每种颜色，然后从每个环到其所包含的颜色连无向边。明显在连通性上，这个图与 Observation 5 中建立的图相同，并且也排除了那些全由同一种颜色构成的环，同时保留了由不同种颜色形成的环。因此，该图与 Observation 5 中图等价，且点、边数皆为 $O(n)$ 级别。使用并查集维护连通性和判断是否成环，时间复杂度 $O(n\alpha)$，可被看作 $O(n)$。

Observation 7. 我们回到 Observation 2 中提出的“维护连锁反应”的模拟。考虑在执行完 Observation 3 的操作得到全部初始的一定留下颜色后，直接建出 Observation 6 的图。此时，所有一定留下的颜色所在连通块里的颜色，也是一定留下的——因为我们发现连锁反应总是沿着不同环间出现的相同颜色的关系传播的，也即图上连的边。

Conclusion: 于是我们只需执行 Observation 3&6，建出图后，舍去那些一定留下颜色所在的连通块，然后找到所有无环的连通块，用总颜色数减去其数量即可。

时间复杂度 $O(n\alpha)$。

当然，本人的实现不很精细，在扒环的时候使用了 `map`，因此带上了 $\log$。当然，扒环也可以通过在求点双的过程中这搞搞那搞搞在线性时间内处理出来，偷懒不想用了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,dfn[10100],low[10100],tot;
vector<int>v[10100];
map<pair<int,int>,int>mp;
vector<vector<int> >circ;
stack<int>s;
bool sub[101000];//colours that have substitudes.
void Tarjan(int x){
	dfn[x]=low[x]=++tot,s.push(x);
	for(auto y:v[x]){
		if(!dfn[y]){
			Tarjan(y),low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				vector<int>u;
				while(s.top()!=y)u.push_back(s.top()),s.pop();u.push_back(s.top()),s.pop();
				u.push_back(x);
				if(u.size()<3)continue;//not a circle.
				vector<int>ed;
				for(int i=0;i<u.size();i++){
					auto tmp=make_pair(min(u[i],u[(i+1)%u.size()]),max(u[i],u[(i+1)%u.size()]));
					ed.push_back(mp[tmp]),mp.erase(tmp);
				}
				int tmp=ed.size();
				sort(ed.begin(),ed.end()),ed.resize(unique(ed.begin(),ed.end())-ed.begin());
				if(ed.size()!=tmp)for(auto i:ed)sub[i]=true;
				else circ.push_back(ed);
			}
		}else low[x]=min(low[x],dfn[y]);
	}
}
int dsu[20100],res;
bool sp[20100];
int find(int x){return dsu[x]==x?x:dsu[x]=find(dsu[x]);}
bool merge(int x,int y){x=find(x),y=find(y);if(x==y)return true;dsu[y]=x;return false;}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y,z;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z),v[x].push_back(y),v[y].push_back(x);
		if(x>y)swap(x,y);mp[make_pair(x,y)]=z;
	}
	Tarjan(1);
	for(auto i:mp)sub[i.second]=true;
//	for(int i=1;i<=m;i++)printf("%d ",sub[i]);puts("");puts("");
//	for(auto i:circ){for(auto j:i)printf("%d ",j);puts("");}
	int N=circ.size();
	for(int i=1;i<=m+N;i++)dsu[i]=i;
	for(int i=0;i<N;i++)for(auto j:circ[i])if(merge(m+i+1,j))sub[j]=true;
	for(int i=1;i<=m;i++)if(sub[i])sp[find(i)]=true;else if(sp[find(i)])sub[i]=true;
	res=m;
	for(int i=1;i<=m+N;i++)if(dsu[i]==i&&!sp[i])res--;
	printf("%d\n",res);
	return 0;
}
```



---

## 作者：RainFestival (赞：5)

$\texttt{codeforces}$ 评分 $2400$

我们将问题分为两步：

第一步，我们要将一颗仙人掌删成树，边需要分两种情况：

+ **在环中，此时这个环内需要删除一条边。**

+ **不在环中，所有边都可以留下。**

第二步，我们建立一个网络流图，它有一个源点 $s$，一个汇点 $t$，还有两部分点：

1. 一部分是图中的边集合（环或者单独边），用 $i$ 表示。

2. 一部分是颜色，用 $i'$ 表示。

+ 连接 $(s,i)$ 容量为第 $i$ 号边集合能保留的边数。

+ 连接 $(i,j')$ 容量为第 $i$ 号边集合内颜色为 $j$ 的边的数量。

+ 连接 $(j',t)$ 容量为 $1$。

从 $s$ 到 $t$ 的最大流就是答案。

另外，根据[官方题解](https://codeforces.ml/blog/entry/47183)第二步有一种 $O(n)$ 的做法，很抱歉，我不会。[官方题解](https://codeforces.ml/blog/entry/47183)也没有给出。

请不要在意代码中 graph2 中的 $\texttt{dinic}$ 写法，这是从 loj127 拉的我的 $\text{92pts}$ 板子，之前害怕本题 $n=10^4$ 卡不过去。

代码稍长：

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cstdlib>
#include<utility>
int n,m,p,x[20005],y[20005],cnt,f[20005],col[50005],sz[50005];
struct graph1
{
	struct edge
	{
		int to,id;
	};
	std::vector<edge> a[300005];
	std::vector<int> cyc[300005];
	int n,m,cnt,p[300005],dep[300005],used[300005],x[300005],y[300005];
	void add(int x,int y,int v)
	{
		a[x].push_back(edge{y,v});
		a[y].push_back(edge{x,v});
	}
	void dfs(int v,int fa,int d,int lst)
	{
		p[d]=lst;dep[v]=d;
		for (int i=0;i<a[v].size();i++)
		{
			int u=a[v][i].to,now=a[v][i].id;
			if (u==fa) continue;
			if (!dep[u]) dfs(u,v,d+1,now);
			else if (dep[u]<dep[v])
			{
				int x=++cnt;
				for (int j=dep[u]+1;j<=dep[v];j++) cyc[x].push_back(p[j]),used[p[j]]=1;
				cyc[x].push_back(now);used[now]=1;
			}
		}
	}
	void add_edge()
	{
		for (int i=1;i<=m;i++) add(x[i],y[i],i);
	}
	void solve()
	{
		add_edge();
		cnt=0;
		for (int i=1;i<=n;i++) if (!dep[i]) dfs(i,-1,1,-1);
		for (int i=1;i<=m;i++) if (!used[i]) cyc[++cnt].push_back(i);
	}
};
struct graph2
{
#define maximum_flow 1000000000
#define maximum_cap 16777216
	struct edge
	{
		int to,cap,opp,id;
	};
	std::vector<edge> a[20005];
	int n,s,t,dep[20005],nxt[20005],can[20005];
	void add(int x,int y,int v)
	{
		int p=a[x].size(),q=a[y].size();
		a[x].push_back(edge{y,v,q,1});
		a[y].push_back(edge{x,0,p,-1});
	}
	void pre()
	{
		for (int i=1;i<=n;i++) nxt[i]=1,can[i]=0;
	}
	int bfs(int lim,int opt)
	{
		std::queue<int> q;
		for (int i=1;i<=n;i++) dep[i]=0;
		q.push(s);dep[s]=1;
		while (!q.empty())
		{
			int v=q.front();q.pop();
			for (int i=0;i<a[v].size();i++)
            {
                int u=a[v][i].to;
                if (!dep[u]&&a[v][i].cap>=lim&&a[v][i].id>=opt) dep[u]=dep[v]+1,q.push(u);
			}
	    }
	    return dep[t];
	}
	int dfs(int v,int now,int lim,int opt)
	{
		if (!nxt[v]) now=0;
		if (v==t||!now) return now;
		int ss=0;
		for (int i=can[v];i<a[v].size();i++,can[v]++)
		{
			int u=a[v][i].to;
			if (dep[v]+1!=dep[u]||a[v][i].cap<lim||a[v][i].id<opt) continue;
			int k=dfs(u,std::min(now,a[v][i].cap),lim,opt);
			if (!k) continue;
			a[v][i].cap=a[v][i].cap-k,a[u][a[v][i].opp].cap=a[u][a[v][i].opp].cap+k;
			ss=ss+k,now=now-k;
			if (!now) break;
		}
		if (!ss) nxt[v]=0;
		return ss;
	}
	int dinic(int ss,int tt)
	{
		s=ss,t=tt;
		int ans=0;
		for (int i=maximum_cap;i;i=i/2) while (bfs(i,1)) pre(),ans=ans+dfs(s,maximum_flow,i,1);
		for (int i=maximum_cap;i;i=i/2) while (bfs(i,-1)) pre(),ans=ans+dfs(s,maximum_flow,i,-1);
		return ans;
	}
#undef maximum_flow
#undef maximum_cap
};
graph1 g1;
graph2 g2;
int main()
{
	scanf("%d%d",&n,&m);g1.n=n;g1.m=m;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&g1.x[i],&g1.y[i],&col[i]);
		p=std::max(p,col[i]);
	}
	g1.solve();
	int cnt=g1.cnt;
	int s=p+cnt+1,t=p+cnt+2;
	for (int i=1;i<=cnt;i++)
	{
		g2.add(s,i,std::max(1,(int)g1.cyc[i].size()-1));
		for (int j=0;j<g1.cyc[i].size();j++)
		{
			int xx=g1.cyc[i][j];
			g2.add(i,cnt+col[xx],1);
		}
	}
    for (int i=1;i<=p;i++) g2.add(i+cnt,t,1);
    g2.n=p+cnt+2;
    int ans=g2.dinic(s,t);
    printf("%d\n",ans);
    return 0;
}
```

时间效率良好

---

