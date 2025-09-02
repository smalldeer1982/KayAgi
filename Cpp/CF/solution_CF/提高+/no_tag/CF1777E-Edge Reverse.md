# Edge Reverse

## 题目描述

You will be given a weighted directed graph of $ n $ nodes and $ m $ directed edges, where the $ i $ -th edge has a weight of $ w_i $ ( $ 1 \le i \le m $ ).

You need to reverse some edges of this graph so that there is at least one node in the graph from which every other node is reachable. The cost of these reversals is equal to the maximum weight of all reversed edges. If no edge reversal is required, assume the cost to be $ 0 $ .

It is guaranteed that no self-loop or duplicate edge exists.

Find the minimum cost required for completing the task. If there is no solution, print a single integer $ -1 $ .

## 说明/提示

In the first test case, an edge exists from $ 1 $ to $ 2 $ , so all nodes are reachable (from $ 1 $ ).

In the second test case, no nodes are reachable from any node no matter what edges we reverse, so the answer is $ -1 $ .

In the third test case, reversing the $ 4 $ -th or $ 5 $ -th edge allows all nodes to be reachable from $ 1 $ . We choose the $ 5 $ -th edge here because its weight is smaller.

## 样例 #1

### 输入

```
4
2 1
1 2 3
5 4
1 2 10
2 3 10
3 1 10
4 5 10
4 5
1 2 10000
2 3 20000
1 3 30000
4 2 500
4 3 20
4 5
1 2 10000
2 3 20000
1 3 30000
4 2 5
4 3 20```

### 输出

```
0
-1
20
5```

# 题解

## 作者：MinimumSpanningTree (赞：7)

[题目链接](https://www.luogu.com.cn/problem/CF1777E)

要使最大值最小，那么基本可以确定本题是二分了。先二分最终答案，再判断最大值为 $x$ 可不可行。由于不可能同一条边两个方向都走，所以可以直接把反转边变成无向边，相当于添加了一条原有边的反向边。加边对于本题来说当然是有利无害的，所以我们可以将边权小于等于 `mid` 的边全部增添它们的反向边。

接下来就要想办法判断是否存在一个点能到达其他点了。因为增加边后图有很多边，同时可能存在一些环，我们难以较快地找出能到达所有点的点。于是考虑缩点，得到一个 DAG 之后我们就很好处理了，只要除了起点的点入度不为 $0$ 就可以满足要求。

另外还有一点，缩点后建边时不需要去重，因为我们是要找入度为 $0$ 的点的个数，而入度为 $0$ 的点不存在指向它的边，所以不去重边是一样的。之前加了去重边就被卡了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<unordered_map>
using namespace std;
const int N=2e5+100;
int n,m,sbt,u[N],v[N],w[N],l,r,mid,t[N],k,rk,rt[N],b[N],bk,scc[N],cnt,d[N];
bool flag[N];
struct node
{
	int id,last,val;
}a[N*2],ra[N*2];
void add(int a1,int a2)
{
	a[++k].id=a2;
	a[k].last=t[a1];
	t[a1]=k;
}
void radd(int a1,int a2)
{
	ra[++rk].id=a2;
	ra[rk].last=rt[a1];
	rt[a1]=rk;
}
void dfs1(int x)
{
	flag[x]=true;
	for(int i=t[x];i;i=a[i].last)
	{
		if(!flag[a[i].id]) dfs1(a[i].id);
	} 
	b[++bk]=x;
}
void dfs2(int x,int c)
{
	scc[x]=c;
	for(int i=rt[x];i;i=ra[i].last)
	{
		if(!scc[ra[i].id]) dfs2(ra[i].id,c);
	}
}
void kosaraju()
{
	bk=cnt=0;
	for(int i=1;i<=n;i++) flag[i]=false,scc[i]=0;
	for(int i=1;i<=n;i++)
	{
		if(!flag[i]) dfs1(i);
	}
	for(int i=n;i>=1;i--)
	{
		if(!scc[b[i]]) dfs2(b[i],++cnt); 
	}
}
bool check(int x)
{
	int c0=0;
	//unordered_map<int,bool> um[N];
	k=rk=0;
	for(int i=1;i<=n;i++) t[i]=rt[i]=0;
	for(int i=1;i<=m;i++)
	{
		add(u[i],v[i]),radd(v[i],u[i]);
		if(w[i]<=x) add(v[i],u[i]),radd(u[i],v[i]);
	}
	kosaraju();
	for(int i=1;i<=n;i++) d[i]=0;
    //for(int i=1;i<=n;i++) printf("%d",scc[i]);
	for(int i=1;i<=m;i++)
	{
		if(scc[u[i]]!=scc[v[i]]/*&&!um[u[i]].count(v[i])*/)
		{
			//um[u[i]][v[i]]=true;
			d[scc[v[i]]]++;
		}
		if(w[i]<=x)
		{
			if(scc[u[i]]!=scc[v[i]]/*&&!um[v[i]].count(u[i])*/)
			{
				//um[v[i]][u[i]]=true;
				d[scc[u[i]]]++;
			}
		}
	}
	for(int i=1;i<=cnt;i++)
	{
		if(!d[i]) c0++;
	}
	return c0<=1;
}
int main()
{
	scanf("%d",&sbt);
	while(sbt--)
	{
		l=-1,r=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++) 
		{
			scanf("%d%d%d",&u[i],&v[i],&w[i]);
			r=max(r,w[i]+1);
		}
		while(l+1<r)
		{
			mid=(l+r)>>1;
			if(check(mid)) r=mid;
			else l=mid;
			//printf("%d %d\n",l,r);
		} 
		check(r)?printf("%d\n",r):printf("-1\n");
        //cout<<check(30001);
	}
	return 0;
}
```

---

## 作者：ExplodingKonjac (赞：5)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1777E)**

挺妙的，可惜赛时没有想到。

## 题目分析

我们发现一件事，如果我们定了那个起点，我们就能够画出一个到每个节点的路径树。如果我们定下了一些“可以反转”的边，那么这些边可以看做是无向的，因为在路径树上，这条边两种方向都可以做到。

考虑到这些，就能二分答案了。二分答案 $mid$，就将边权小于等于 $mid$ 的边设置成“可以反转”，也就是无向。对这个新图缩点，得到一个 DAG。那么满足条件显然等价于该 DAG 只有一个入度为 $0$ 的点。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

// 快读

using LL=long long;
using LD=long double;
using UI=unsigned int;
using ULL=unsigned long long;
constexpr int INF=1e9;

int T,n,m,nn,eu[200005],ev[200005],ew[200005];
vector<int> g[200005];
int top,tim,dfn[200005],low[200005],st[200005],col[200005],deg[200005];
bool vis[200005];
void tarjan(int u)
{
	dfn[u]=low[u]=++tim;
	st[++top]=u,vis[u]=true;
	for(auto &v: g[u])
		if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if(vis[v]) low[u]=min(low[u],dfn[v]);
	if(low[u]==dfn[u])
	{
		int x,y=++nn;
		do x=st[top--],vis[x]=false,col[x]=y;
		while(x!=u);
	}
}
bool check(int lim)
{
	for(int i=1;i<=n;i++) g[i].clear();
	for(int i=1;i<=m;i++)
	{
		g[eu[i]].push_back(ev[i]);
		if(ew[i]>lim) continue;
		g[ev[i]].push_back(eu[i]);
	}
	for(int i=1;i<=n;i++) dfn[i]=low[i]=col[i]=deg[i]=0;
	tim=top=nn=0;
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(int u=1;u<=n;u++) for(auto &v: g[u]) if(col[u]!=col[v]) deg[col[v]]++;
	int res=0;
	for(int i=1;i<=nn;i++) res+=!deg[i];
	return res==1;
}
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n>>m;
		for(int i=1;i<=m;i++) qin>>eu[i]>>ev[i]>>ew[i];
		int l=0,r=INF;
		while(l<r)
		{
			int mid=(l+r)>>1;
			if(check(mid)) r=mid;
			else l=mid+1;
		}
		qout.writeln(l==INF?-1:l);
	}
	return 0;
}
```


---

## 作者：wangyishan (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/CF1777E)

----

比较正常的一道题目。

首先看到题目中要求“最大值最小”，想到二分。

这里推荐一个二分的万能写法：（永远不会错）
```cpp
int l=1,r=n,ans=-1;//多一个变量记录答案
while(l<=r){
	int mid=(long long)(l+r)>>1;
     if(check(mid)){//检查 mid 是否合法
       ans=mid;
       l=mid+1;//求最大值
       // r=mid-1;(求最小值）
     }else
       r=mid-1;
}
return ans;
```

然后问题就是如何写 `check`。
注意到题面中将一条边的方向取反就相当于将这条边变为双向边（感性理解一下，这条边既可以往前走又可以往后走，我们只会用到其中一个方向）。

但是这样还是不够，我们需要缩点。缩点之后这张图就是一个 DAG，原题目的条件就转化为这个 DAG 上有且只有一个入度为 0 的点。这个条件是充分必要的。

done.

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f
int n,m;
struct edge{
    int v,w;
    edge(int a,int b){v=a,w=b;}
};
vector<edge>e[200050];
vector<int>p[200050];
int vis[200050];
int stk[200050],top,cnt,col;
int dfn[200050],low[200050];
int scc[200050],siz[200050];
int in[200050];
int u[200050],v[200050],w[200050];
void tarjan(int x){
    stk[++top]=x;
    vis[x]=1;
    dfn[x]=low[x]=++cnt;
    for(auto i:p[x]){
        if(!dfn[i]){
            tarjan(i);
            low[x]=min(low[x],low[i]);
        }else if(vis[i])
            low[x]=min(low[x],dfn[i]);
    }
    if(low[x]==dfn[x]){
        int p,q=++col;
        do p=stk[top--],vis[p]=0,scc[p]=q;while(p!=x);
    }
}
bool check(int x){
    top=cnt=col=0;
    for(int i=1;i<=n;i++){
        vis[i]=0;dfn[i]=low[i]=0;scc[i]=siz[i]=0;in[i]=0;
        p[i].clear();
    }
    for(int i=1;i<=m;i++){
        p[u[i]].emplace_back(v[i]);
        if(w[i]<=x)p[v[i]].emplace_back(u[i]);
    }
    for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
    for(int i=1;i<=m;i++)
        if(scc[u[i]]!=scc[v[i]])
            in[scc[v[i]]]++;
    int ct=0;
    for(int i=1;i<=col;i++)ct+=(in[i]==0);
    return ct==1;
}
void solve(){
    cin>>n>>m;
    int mmax=0;
    for(int i=1;i<=n;i++){e[i].clear();p[i].clear();}
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i]>>w[i];
    }
    int l=0,r=inf,ans=inf;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else l=mid+1;
    }
    cout<<(ans==inf?-1:ans)<<endl;
}
signed main(){
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}

```

---

## 作者：loser_seele (赞：1)

前置知识：求有向图强连通分量。

首先不难发现一个结论：如果一条边可以翻转，那么我们可以将其视为无向边。这个是显然的性质。

然后发现固定了答案之后，小于等于答案的所有边被翻转肯定更优，因为每可以多翻转一条边代表在原图上加一条边，肯定不会使得答案变差。

于是考虑二分答案，对于所有小于等于答案的边建无向边，否则建有向边，问题转化为了确定是否有一个点能到达其他所有点。

这题是一个原题 [P2341](https://www.luogu.com.cn/problem/P2341)，但是原题是其他所有点能到达多少点，建反向边即可互相转化。

我们首先求出所有强联通分量，然后从拓扑序最小的强连通分量里随便选一个点（这样显然不影响答案，因为它能到达分量内所有点），如果这样的变量超过一个则它们互相不能遍历，这个在后面会判断。然后从这个点开始 dfs 一遍，如果存在无法到达的点就是无解。

求所有强连通分量可以跑 kosaraju 算法在线性时间复杂度内解决，此处不再详述。

时间复杂度 $ \mathcal{O}((n+m)\log{c}) $，可以通过。不过好像就我一个没写 Tarjan 的，常数太大喜提最劣解，差点过不去，不过时限 4 秒卡过去了。

代码：

```cpp
#include <bits/stdc++.h>
#define MAX_N 1000000+16
using namespace std;
vector<int>G[MAX_N];
vector<int>rG[MAX_N];
vector<int>vs;
bool vis[MAX_N];
int cmp[MAX_N];
int n,m,V;
int u[MAX_N],v[MAX_N],w[MAX_N];
void add_edge(int from,int to)
{
G[from].push_back(to);
rG[to].push_back(from);
} 
void dfs(int v)
{
   vis[v]=1;
   for(int i=0;i<G[v].size();i++)
   	if(!vis[G[v][i]])
   	dfs(G[v][i]);
   vs.push_back(v);
}
void rdfs(int v,int k)
{
	vis[v]=1;
	cmp[v]=k;
	for(int i=0;i<rG[v].size();i++)
	{
		if(!vis[rG[v][i]])
		rdfs(rG[v][i],k);
	}
}
int scc()
{
	for(int v=0;v<V;v++)
    vis[v]=0;
	vs.clear();
	for(int v=0;v<V;v++)
	{
		if(!vis[v])
		dfs(v);
	}
	for(int v=0;v<V;v++)
    vis[v]=0;
	int k=0;
	for(int i=vs.size()-1;i>=0;i--)
	{
		if(!vis[vs[i]])
		rdfs(vs[i],k++);
	} 
	return k;
}
bool check(int mid)
{
    for(int v=0;v<V;v++)
    G[v].clear();
    for(int v=0;v<V;v++)
    rG[v].clear(),cmp[v]=0;
    for(int i=0;i<m;i++)
		if(w[i]<=mid)
		    add_edge(v[i]-1,u[i]-1),add_edge(u[i]-1,v[i]-1);
        else
            add_edge(v[i]-1,u[i]-1);		
    int res=scc();
	int u=0,num=0;
	for(int v=0;v<V;v++)
	{
		if(cmp[v]==res-1)
		{
			u=v;
			num++;
		}
	}
	for(int v=0;v<V;v++)
    vis[v]=0;
	rdfs(u,0);
	for(int v=0;v<V;v++)
    {
    	if(!vis[v])
    	{
    		num=0;
    		break;
		}
	}	
	return num;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
	scanf("%d%d",&n,&m);
	V=n;
	for(int i=0;i<m;i++)
	cin>>u[i]>>v[i]>>w[i];		
	int l=0,r=1e9;
    while(l<=r)
    {
    int mid=(l+r)>>1;
    if(check(mid))
    r=mid-1;
    else
    l=mid+1;
    //cout<<mid<<' '<<check(mid)<<'\n';
    }
    if(l>=1e9)
    cout<<-1<<'\n';
    else
    cout<<l<<'\n';
    }
}
```


---

## 作者：MSqwq (赞：1)

题意：  
给你一个有向无环图，你可以去反转一些边（即交换边的两个端点），代价是所有反转边的权值最大值，问你最小代价使得至少有一个点可以去到所有点，如果不存在就输出 $-1$。 

------------
题解：  
先思考一个问题，如果没有反转的操作，如何判断至少有一个点可以去到所有点，那其实就是入度为 $0$ 的点小于等于 $1$，这个很显然，如果大于 $1$，那么肯定就去不了另外的那些点，只有唯一或者无情况才会成立。  
知道这个很显然的结论之后差不多就做完了，那么如何将我们的问题变为上述模型呢，**缩点**，如何考虑代价呢，二分答案，这是一个很经典的套路，二分答案套 tarjan，多次缩点去找二分的极点。如何实现反转的操作呢，就是假设我二分的是 $x$ 那么边权小于等于 $x$ 的边我可以反转也可以不反转，那么我直接变成双向边不就好了，这样缩点后我再用上面的结论就是一个很好的 check，然后就做完这题了。  
无解的情况就是不连通，可以并查集搞一搞就行，如果联通是一定可以成立，这个很好证明，就是你大不了全部重新定向嘛，很显然是可以的，然后就做完了。  
复杂度是 $\log w\times(n+m)$，当然你排个序二分边也行，会快一点，就是 $\log n \times (n+m)$。我赛时写的是前者就给前者代码了，后者也很好写，其实都是同理啦。  
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=998244353;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}

const int N=3e5+10,M=6e5+10;
struct qwq{
	int to,z,ne;
}e[M];
struct ms{
	int x,y,z;
}a[M];
int elast[N],num;
void add(int x,int y,int z){e[++num]={y,z,elast[x]},elast[x]=num;}
int dfn[N],low[N],v[N],be[N],scc,tot;
stack<int>s;
int n,m;
int cnt[N];
void tarjan(int x)
{
	dfn[x]=low[x]=++tot;s.push(x),v[x]=1;
	for(int i=elast[x];i;i=e[i].ne)
	{
		int to=e[i].to;
		if(!dfn[to])tarjan(to),low[x]=min(low[x],low[to]);
		else if(v[to])low[x]=min(low[x],dfn[to]);
	}
	if(low[x]==dfn[x])
	{
		scc++;int to;
		do{
			to=s.top();s.pop();v[to]=0;
			be[to]=scc;
		}while(x!=to);
	}
}
int f[N];
int find(int x){return f[x]=f[x]==x?x:find(f[x]);}
bool check(int mid)
{
	scc=0;
	for(int i=1;i<=n;i++)cnt[i]=0;
	for(int i=1;i<=n;i++)elast[i]=0;num=0;
	for(int i=1;i<=n;i++)dfn[i]=0,low[i]=0;
	while(!s.empty())s.pop();
	
	for(int i=1;i<=m;i++)
	{
		if(a[i].z<=mid)add(a[i].x,a[i].y,a[i].z),add(a[i].y,a[i].x,a[i].z);
		else add(a[i].x,a[i].y,a[i].z);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
	
	int sum=0;
	for(int i=1;i<=m;i++)
	{
		if(be[a[i].x]==be[a[i].y])continue;
		if(a[i].z<=mid)cnt[be[a[i].x]]++,cnt[be[a[i].y]]++;
		else cnt[be[a[i].y]]++;	
	}

	for(int i=1;i<=scc;i++)
		if(!cnt[i])sum++;
	if(sum<=1)return true;
	return false;
}

void solve()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)f[i]=i;
	int l=0,r=0;
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read(),z=read();
		int fx=find(x),fy=find(y);
		if(fx!=fy)f[fx]=fy;
		a[i].x=x,a[i].y=y,a[i].z=z;
		r=max(r,z);
	}
	int flag=-1;
	for(int i=1;i<=n;i++)
	{
		if(flag==-1)flag=find(i);
		else if(flag!=-1&&flag!=find(i))
		{
			cout<<-1<<endl;
			return;
		}
	}
	int ans=-1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans<<endl;
}
int main()
{
	int T=read();
	while(T--)solve();
	return 0;
}
```



---

## 作者：__ZengJunjie__ (赞：0)

[题目链接](https://codeforces.com/problemset/problem/1777/E)  

## 题目解析:
题目已经很明白了，就是花费固定代价将图中每条边变成有向边，使图中有点能与其他点联通，求最小代价。  
考虑二分答案，对于一个 $mid$，将边权小于等于 $mid$ 的边反转。对于这个点进行缩点，得到一个 DAG，可以看出当这个 DAG 有且只有一个入度为 $0$ 的点时满足条件。

## 代码部分:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,res,sccno[200010],du[200010];
bool vis[200010];
struct edge{
	long long u,v,w;
}bian[200010];
vector<long long>g[200010],rg[200010],stk;
void DFS(long long u){
	if(vis[u])return ;
	vis[u]=1;
	for(int i=0;i<g[u].size();i++){
		long long v=g[u][i];
		DFS(v);
	}
	stk.push_back(u);
} 
void DFS2(long long u){
	if(sccno[u])return ;
	sccno[u]=res;
	for(int i=0;i<rg[u].size();i++){
		long long v=rg[u][i];
		DFS2(v);
	}
}
void kosaraju(){
	for(int i=1;i<=n;i++)DFS(i);
	for(int i=n-1;i>=0;i--){
		if(!sccno[stk[i]]){
			res++;
			DFS2(stk[i]);
		}
	}
}
bool check(long long x){
	for(int i=0;i<=n;i++)
		sccno[i]=vis[i]=du[i]=0;
	stk.clear(),res=0;
	for(int i=1;i<=n;i++)
		g[i].clear(),rg[i].clear();
	for(int i=1;i<=m;i++){
		g[bian[i].u].push_back(bian[i].v);
		rg[bian[i].v].push_back(bian[i].u);
		if(bian[i].w<=x){
			g[bian[i].v].push_back(bian[i].u);
			rg[bian[i].u].push_back(bian[i].v);
		}
	}
	kosaraju();
	for(int i=1;i<=n;i++){
		for(int j=0;j<g[i].size();j++){
			long long k=g[i][j];
			if(sccno[i]!=sccno[k])du[sccno[k]]++;
		}
	}
	long long cnt=0;
	for(int i=1;i<=res;i++)
		if(du[i]==0)cnt++;
	if(cnt==1)return true;
	else return false;
}
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=m;i++)scanf("%lld%lld%lld",&bian[i].u,&bian[i].v,&bian[i].w);
		long long l=0,r=1e9,ans=1e18;
		while(l<=r){
			long long mid=(l+r)/2;
			if(check(mid))r=mid-1,ans=mid;
			else l=mid+1;
		}
		if(ans==1e18)printf("-1\n");
		else printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：fire_and_sweets (赞：0)

首先把所有边按照边权排序。

然后，我们考虑二分答案。遇到答案 $mid$，我们把边权小于等于 $mid$ 的边变成无向边。这就代表着这条边可以选择反转也可以选择不反转。

我们发现这个新图有一个很麻烦的地方：可能有环。为了把他变成一个 DAG，我们对这个图进行缩点。显然，如果 DAG 中最多有一个入度为 $0$ 的点，则 $mid$ 合法。

使用 Tarjan 算法即可。

```
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 200010, M = 400010;

struct Node
{
	int x, y, z;
	bool operator < (const Node& _) const {
		return z < _.z;
	}
};

int n, m;
Node a[M];
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt;
int din[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u, in_stk[u] = true;
    
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
    }
    
    if (low[u] == dfn[u])
    {
        ++ scc_cnt;
        int y;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            id[y] = scc_cnt;
        }   
        while (y != u);
    }
}

void suo()
{
	for (int i = 1; i <= n; i ++ )
		id[i] = dfn[i] = din[i] = 0;
	top = scc_cnt = timestamp = 0;
	for (int i = 1; i <= n; i ++ )
        if (!dfn[i]) tarjan(i);

    for (int i = 1; i <= n; i ++ )
        for (int j = h[i]; ~j; j = ne[j])
        {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) din[b] ++ ;
        }
}

bool check(int mid)
{
    for (int i = 1; i <= n; i ++ ) h[i] = -1;
	idx = 0;
	for (int i = 1; i <= m; i ++ )
	{
		add(a[i].x, a[i].y);
		if (a[i].z <= mid) add(a[i].y, a[i].x);
	}
	suo();
	int res = 0;
	for (int i = 1; i <= scc_cnt; i ++ )
		if (din[i] == 0) res ++ ;
	return res <= 1;
}

void solve()
{
    cin >> n >> m;
    int l = 0, r = 0;
    for (int i = 1; i <= m; i ++ )
		cin >> a[i].x >> a[i].y >> a[i].z, r = max(r, a[i].z);
    sort(a + 1, a + m + 1);
    int res = -1;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (check(mid)) r = mid - 1, res = mid;
		else l = mid + 1;
	}
	cout << res << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int T;
	cin >> T;
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
比较简单的题，在 $5.3$ 的时候随机跳的，但是 $5.5$ 才真正开始写这题，有点颓废。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
首先对于能翻转的边，他就可以视作双向边。

因为对于一条有向边，我们肯定不会用到他和他的反边，所以直接把其视作双向边即可。

那么不难发现如果我们把边的单/双向都定下来后，图就已经建出来了，考虑如何判断即可。

考虑对这张图进行 tarjan 缩点，这样图就变成了一个 DAG。

对于一个 DAG，存在一个点能到达其他所有的点显然即为当且仅当只有一个入度为 $0$ 的点。

接着来考虑怎么定下边的单/双向。

显然的是答案具有单调性，直接大力二分即可。

而对于无解的情况，没必要再判断个图是否连通，看下 $ans$ 是不是极大值即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;
const int N=2e5+10,V=5e5,mod=998244353,INF=0x3f3f3f3f3f3f3f3f;
int T,n,m,ans,top,cnt,tot,u[N],v[N],w[N],dfn[N],low[N],cl[N],mp[N],st[N],in[N];vector<int>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void tarjan(int u)
{
    dfn[u]=low[u]=++cnt;st[++top]=u,mp[u]=1;
    for(auto v:e[u])
        if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
        else if(mp[v]) low[u]=min(low[u],dfn[v]);
    if(low[u]==dfn[u])
    {
        int x,y=++tot;
        do x=st[top--],mp[x]=0,cl[x]=y;while(x!=u);
    }
}
inline bool check(int x)
{
    for(int i=1;i<=n;i++) e[i].clear(),in[i]=dfn[i]=low[i]=cl[i]=0;
    for(int i=1;i<=m;i++)
    {
        e[u[i]].emplace_back(v[i]);
        if(w[i]<=x) e[v[i]].emplace_back(u[i]);
    }tot=cnt=top=0;
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    for(int u=1;u<=n;u++) for(auto v:e[u]) in[cl[v]]+=cl[u]!=cl[v];
    int res=0;for(int i=1;i<=tot;i++) res+=!in[i];return res==1;
}
signed main()
{
    T=read();
    while(T--)
    {
        n=read(),m=read();for(int i=1;i<=n;i++) e[i].clear();ans=INF;
        for(int i=1;i<=m;i++) u[i]=read(),v[i]=read(),w[i]=read();
        int l=0,r=INF;while(l<=r) check(mid)?(ans=mid,r=mid-1):l=mid+1;
        print(ans==INF?-1:ans);put('\n');
    }
    genshin:;flush();return 0;
}
```

---

## 作者：LinuF (赞：0)

### [原题链接](https://www.luogu.com.cn/problem/CF1777E)

### 思路
看到求最小成本，想到直接二分答案。显然二分出答案 $mid$，对于权值小于等于 $mid$ 的边，可以任意选择方向，我们考虑建反向边。

这样题目就被转化成了要求是否能从一个点出发，遍历完所有点。这是一个套路，将原图缩点，然后找到是否有且仅有一个入度为 $0$ 的点即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename types>
inline void read(types &x){
    x = 0; char c = getchar(); int f = 1;
    while (!isdigit(c)){ if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    x *= f; return;
}
inline void read(){}
template<typename types, typename... Args>
void read(types &x, Args&... args){
    read(x), read(args...);
    return;
}
template<typename types>
void write(types x){
    if (x < 0) putchar('-'), x = -x;
    types k = x / 10;
    if (k) write(k);
    putchar(x - k * 10 + '0');
    return;
}
const int N=4e5+5;
struct EDGE{
    int u,v,w;
}e[N];
int head[N],ne[N],to[N],idx;
int dfn[N],timestamp,low[N],stk[N],top,in_stk[N],id[N],cnt,n,m,d[N];
void add(int u,int v){
    ne[++idx]=head[u];head[u]=idx;to[idx]=v;
}
void tarjan(int u){
    dfn[u]=low[u]=++timestamp;
    in_stk[u]=true;stk[++top]=u;
    for(int i=head[u];i;i=ne[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in_stk[v]) low[u]=min(low[u],dfn[v]);
    }    
    if(low[u]==dfn[u]){
        int y=0;
        ++cnt;
        do{
            y=stk[top--];
            id[y]=cnt;
            in_stk[y]=false;
        }while(y!=u);
    }
}
inline bool check(int mid){
    for(int i=1;i<=m;i++){
        if(e[i].w<=mid){
            add(e[i].u,e[i].v);add(e[i].v,e[i].u);
        }
        else add(e[i].u,e[i].v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    // for(int i=1;i<=n;i++){
    //     cout<<id[i]<<' ';
    // }
    // cout<<endl;
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=ne[i]){
            int v=to[i];
            if(id[u]!=id[v]){
                d[id[v]]++;
            }
        }
    }

    int ans=0;
    for(int i=1;i<=cnt;i++){
        if(d[i]==0){
            ans++;
        }
    }
    for(int i=1;i<=n;i++){
        d[i]=0;head[i]=0;id[i]=0;in_stk[i]=false;dfn[i]=low[i]=0;
    }
    idx=0;timestamp=0;top=0;cnt=0;
    
    if(ans==1){
        return true;
    }
    return false;
}
void solve(){
    read(n,m);
    for(int i=1;i<=m;i++){
        read(e[i].u,e[i].v,e[i].w);
    }
    int l=0,r=1e9;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid)){
            r=mid;
        }
        else l=mid+1;
    }
    if(!check(l)){
        puts("-1");
    }
    else{
        write(l);puts("");
    }
}
int main(){
#ifndef ONLINE_JUDGE
    freopen(".in","r",stdin);
#endif  
    int T;
    read(T);
    while(T--)
        solve();
    return 0;
}
```


---

## 作者：Hisaishi_Kanade (赞：0)

简单题。考虑到最大值最小，我们可以直接二分答案 $P$。

考虑如何 check。这个题的询问等价于缩点后是否恰好存在一个点入度为 $0$。

如果一条边是可以翻转的（$w_i\le P$），则建立他的反边。对着这个新建图跑一次缩点即可。

二分 $P$ 的话复杂度的 $\log$ 在 $w$ 上，不如先将边权排序然后二分这个边权的位置（显然答案是某个边权，或者 $0$，或者 $-1$），在重新建边的处理上常数或许会略小。复杂度 $O((n+m)\log m)$。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
using namespace std;
const int N=4e5+5;
int i, cnt0, tot, cnt, tp, t, n, m, j, sen, mid, l, r;
int ins[N], low[N], dfn[N], col[N], siz[N], q[N], in[N];
class echi
{
public:
	int u, v, w;
	inline void input() {scanf("%d %d %d", &u, &v, &w);}
	inline const bool operator<(const echi &other) const {return w<other.w; }
} d[N]; vector<int> e[N];
inline void tarjan(int x)
{
	dfn[x]=low[x]=++tot; q[++tp]=x; ins[x]=true;
	for(auto nxt : e[x])
	{
		if(!dfn[nxt]) 
		{
			tarjan(nxt);
			low[x]=min(low[x], low[nxt]);
		} else if(ins[nxt]) low[x]=min(low[x], dfn[nxt]);
	}
	if(low[x]==dfn[x])
	{
		++cnt;
		do
		{
			sen=q[tp]; --tp; ins[sen]=false;
			col[sen]=cnt;
			++siz[cnt];
		}while (sen!=x);
	}
}
#define add(x, y) e[x].emplace_back(y)
inline const bool check(int k)
{	tot=tp=cnt0=cnt=0; rep(i, 1, n) dfn[i]=col[i]=low[i]=0;
	rep(i, 1, n) e[i].clear();
	rep(i, 1, k) add(d[i].u, d[i].v), add(d[i].v, d[i].u);
	rep(i, k+1, m) add(d[i].u, d[i].v);
	rep(i, 1, n) if(!dfn[i]) tarjan(i);
	rep(i, 1, cnt) in[i]=0; rep(i, 1, n) for(auto nxt : e[i]) if(col[i]!=col[nxt]) ++in[col[nxt]]; rep(i, 1, cnt) cnt0+=in[i]==0;
	return cnt0==1;
}
int main()
{
	scanf("%d", &t); while(t--)
	{
		scanf("%d %d", &n, &m);
		rep(i, 1, m) d[i].input(); sort(d+1, d+m+1);
		l=0, r=m;// printf("%d\n", check(m));
		while(l<=r)
		{
			mid=l+r>>1;
			if(check(mid)) r=mid-1;
			else l=mid+1;
		}
		if(l==m+1) puts("-1");
		else printf("%d\n", d[l].w);
	}
}
```

---

## 作者：masonpop (赞：0)

比较有意思的题。

容易发现，对一张有向图缩点后，存在一个点能够到达所有的点等价于只有一个入度为 $0$ 的点。

这道题是让反转的边权最大值最小化，考虑二分答案。

注意到，如果一条有向边能够反转，我们可以将其视为两边都能走的无向边。把这些边全部设成无向边后再缩点判定即可。

注意每次判定时需要重置整张图，要清空。时间复杂度 $O(n\log V)$，$V$ 是答案的范围。[代码](https://codeforces.com/contest/1777/submission/210093891)。

---

## 作者：Fzrcy (赞：0)

最大值最小，二分无疑了。考虑二分答案 $Mid$，对于所有边权小于等于 $Mid$ 的有向边变为无向边，然后缩点变成一个 DAG，若在原图中存在一个点能够到达图中其他节点的节点，当且仅当在 DAG 中只有一个点的入度为 $0$。

[代码](https://codeforces.com/contest/1777/submission/205341889)。

---

## 作者：zhouyuhang (赞：0)

二分答案。

考虑怎么 check：如果题目条件略加改动，将可以重定向某些边改为将这些变成双向边，则由 [经典结论](https://www.luogu.com.cn/problem/P2341) 知这张图合法当且仅当只有一个强联通分量入度为 $0$。下面将证明即使是重定向边，这一方法依旧正确。

记将可重定向边看作双向边的图为 $G'$，这些双向边构成的集合为 $E'$。若 $G'$ 中不存在可以到达其他所有点的点，则显然无论怎样定向也都不会存在。若 $G'$ 中存在这样的点，记其为 $s$，则必然存在 $(u,v)\in E'$，使得存在 $s\to u$ 的某一条路径，不经过任何 $E'$ 中的元素。此时我们发现，对于 $(u,v)$ 这条可重定向的边，选择 $u\to v$ 一定不劣于选择 $v\to u$（假如选择了 $v\to u$，这条边会使你到达点 $u$ 这一原本就可以到达的点，因此这条边没有任何价值），故我们可以将 $(u,v)$ 定向为 $u\to v$，并将其从 $E'$ 中删去。归纳即可。

复杂度 $\mathcal O((n+m)\log V)$

---

## 作者：L0vely_NaiL0ng (赞：0)

我们发现答案具有单调性，因为越大的代价意味着可以比小的代价翻转更多边，更有可能满足条件，所以我们二分代价。

对于代价 $v$，任何权值小于等于 $v$ 的边都可以翻转，我们将这些边改为双向的，因为如果有一个点出发能到达所有点，这条双向边只会经过 $1$ 次，根据实际可以确定是原来的边还是翻转后的边。

所以二分后问题转化为：现在有一个有向图，问是否存在一个点出发可以到达所有点。

因为处于同一个强联通分量的点都两两可以互相到达，到达其中任何一个点也意味着到达了其中所有点，所以这些点对于问题求解的贡献都是一样的，我们可以缩点。

现在问题进一步转化为：有一个有向无环图，问是否存在一个点出发可以到达所有点。

我先直接给出结论：上面这个问题相当于问“是否有且只有 $1$ 个点的入度为 $0$”。

我们给出简单的证明：因为这是一个有向无环图，所以至少有 $1$ 个点的入度为 $0$，如果有 $\ge 2$ 个点入度为 $0$，那么这些点显然不能互相到达，所以只有 $1$ 个点的入度为 $0$，且如果只有 $1$ 个点入度为 $0$，图应该形如一棵树上面有很多前向边（从祖宗到子孙的有向边），这个图显然从这棵树的根开始可以遍历所有点。

具体实现要注意多组数据有很多变量、数组要清空，但千万不要直接整个数组清零，会超时。

复杂度为二分复杂度乘单次判定的复杂度（即缩点复杂度）：$O((n + m) \log w)$（$w$ 为边权值的最大值，代码中为 $10^9 + 1$）。

code ：

```
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, M = 4e5 + 5;
int n, m, a[N];
int head[N], ver[M], nex[M], tot, num;
struct node {
	int x, y, z;
} edge[M];
int dfn[N], low[N], scc[N], cnt, st[N], t, d[N];
bool flag[N];
void add(int x, int y) {
	ver[++tot] = y; nex[tot] = head[x];head[x] = tot; return;
}
void dfs(int x) {
	dfn[x] = low[x] = ++num; st[++t] = x; flag[x] = 1;
	for (int i = head[x]; i; i = nex[i]) {
		int y = ver[i];
		if (!dfn[y]) {
			dfs(y); low[x] = min(low[x], low[y]);
		} else if (flag[y]) low[x] = min(low[x], dfn[y]);
	}
	if (dfn[x] == low[x]) {
		++cnt;
		while (1) {
			scc[st[t]] = cnt; flag[st[t]] = 0; t--; 
			if (st[t + 1] == x) break;
		}
	}
	return;
}
bool check(int x) {	
	for (int i = 1; i <= n; i++) {
		dfn[i] = low[i] = flag[i] = head[i] = scc[i] = d[i] = 0;
	}
	for (int i = 1; i <= tot; i++) nex[i] = 0;
	tot = t = cnt = 0;
	for (int i = 1; i <= m; i++) {
		add(edge[i].x, edge[i].y);
		if (edge[i].z <= x) {
			add(edge[i].y, edge[i].x);
		}
	}
	num = 0;
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) dfs(i);
	for (int i = 1; i <= m; i++) {
		if (scc[edge[i].x] == scc[edge[i].y]) continue;
		d[scc[edge[i].y]]++;
	}
	int cont = 0;
	for (int i = 1; i <= cnt; i++)
		if (d[i] == 0) cont++;
	return cont == 1;
}
void solve() {
	cin >> n >> m;
	int l = 0, r = 0, res;
	for (int i = 1; i <= m; i++) {
		int x, y, z; cin >> x >> y >> z;
		edge[i] = {x, y, z};
		r = max(r, z);
	}
	res = 1e9 + 1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			res = mid; r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	if (res == 1e9 + 1) res = -1;
	cout << res << endl;
	return ;
}
int main() {
	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1777E 题解



## 思路分析

最小化最大值，直接想二分，每次检查权值 $\le k$ 的边是否翻转。

我们注意到，一条可以选择翻不翻转的边可以看成一条双向边，因为没有简单路径会同时经过 $u\to v$ 和 $u\gets v$，否则就产生了环，这一定不优。

因此每次把权值 $\le k$ 的边当成双向的，用 tarjan 缩点后判断 DAG 上入度为 $0$ 的点是否唯一即可。

时间复杂度 $\Theta((n+m)\log w)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1,INF=1e9;
int n,m,ver[MAXN][2],w[MAXN],deg[MAXN];
vector <int> G[MAXN];
int dfn[MAXN],low[MAXN],dfncnt,stk[MAXN],top,bel[MAXN],scccnt;
bool ins[MAXN];
inline void tarjan(int p) {
	dfn[p]=low[p]=++dfncnt;
	stk[++top]=p,ins[p]=true;
	for(int v:G[p]) {
		if(!dfn[v]) {
			tarjan(v);
			low[p]=min(low[p],low[v]);
		} else if(ins[v]) low[p]=min(low[p],low[v]);
	}
	if(dfn[p]==low[p]) {
		++scccnt;
		int k;
		do {
			k=stk[top--];
			bel[k]=scccnt;
			ins[k]=false;
		} while(k!=p);
	}
}
inline bool check(int k) {
	for(int i=1;i<=n;++i) {
		deg[i]=0,dfn[i]=0;
		ins[i]=false;
		G[i].clear();
	}
	dfncnt=0,top=0,scccnt=0;
	for(int i=1;i<=m;++i) {
		if(w[i]<=k) {
			G[ver[i][0]].push_back(ver[i][1]);
			G[ver[i][1]].push_back(ver[i][0]);
		} else G[ver[i][0]].push_back(ver[i][1]);
	}
	for(int i=1;i<=n;++i) if(!dfn[i]) tarjan(i);
	for(int u=1;u<=n;++u) {
		for(int v:G[u]) {
			if(bel[u]!=bel[v]) ++deg[bel[v]];
		}
	}
	int cnt=0;
	for(int i=1;i<=scccnt;++i) if(!deg[i]) ++cnt;
	return cnt==1;
}
inline void solve() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i) scanf("%d%d%d",&ver[i][0],&ver[i][1],&w[i]);
	int l=0,r=INF,res=-1;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid)) res=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",res);
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

