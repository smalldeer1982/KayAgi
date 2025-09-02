# 「EVOI-RD2」旅行家

## 题目描述

小 A 是一个热衷于旅行的旅行家。有一天，他来到了一个城市，这个城市由 $n$ 个景点与 $m$ 条连接这些景点的道路组成。每个景点有一个**美观度** $a_i$。

定义一条**旅游路径**为两个景点之间的一条非严格简单路径，也就是点可以重复经过，而边不可以。

接下来有 $q$ 个旅游季，每个旅游季中，小 A 将指定两个顶点 $x$ 和 $y$，然后他将走遍 $x$ 到 $y$ 的**所有旅游路径**。 

所有旅游季结束后，小 A 会统计他所经过的所有景点的美观度之和（重复经过一个景点只统计一次美观度）。他希望你告诉他这个美观度之和。

## 说明/提示

**【数据规模与范围】**

**本题采用捆绑测试**

+ Subtask 1 (30 pts)：$3 \leq n \leq 500,m \leq 2 \times 10^5,q=200$。
+ Subtask 2 (30 pts)：$3 \leq n \leq 3 \times 10^5,m \leq 2 \times 10^6,q=10^6$。
+ Subtask 3 (40 pts)：$3 \leq n \leq 5 \times 10^5,m \leq 2 \times 10^6,q=10^6$。

对于 $100\%$ 的数据，保证 $3 \leq n \leq 5 \times  10^5$，$m \leq 2 \times 10^6$，$q=10^6$，$1 \leq a_i \leq 100$，且该图联通，没有重边和自环。

---

**对于题面的解释：**


![](https://cdn.luogu.com.cn/upload/image_hosting/a2oku1vq.png)

上图与样例无关。

如图，为城市的景点分布图，为无向图。  
假设 $6$ 号顶点为 $x$ 景点，$5$ 号顶点为 $y$ 景点。  
很显然，路径 $6 \rightarrow 2 \rightarrow 4 \rightarrow 5$ 和路径 $6 \rightarrow 2 \rightarrow 1 \rightarrow 3 \rightarrow 5$ 都是合法的，这两条路径满足了都是简单路径的条件，并且都是在一次旅游季中行走的。  
虽然 $6 \rightarrow 2$ 这条边经过了 $2$ 次，但仍旧是合法的，因为它们不是在一条路径中经过的。

简单来说，一次旅游季会走不定条路径，每条路径必须是简单路径，但是每条简单路径之间可以有重边。

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
1 2
2 3
1 4
4 3
3 5
3
1 2
1 4
1 3
```

### 输出

```
10```

## 样例 #2

### 输入

```
5 6
1 2 3 4 5
1 2
2 3
1 4
1 5
4 3
3 5
3
1 2
1 4
1 3
```

### 输出

```
15```

# 题解

## 作者：Noby_Glds (赞：10)

~~算法标签才是一切灵感的源泉~~
### 思路：
打开标签一看：缩点。

我们分析下面给的图，可以发现，我们把两条从 $1$ 到 $6$ 的路径叠起来，就可以覆盖由红色框框圈住的强连通分量，从而获得该强连通分量内所有的点的权值。

![](https://cdn.luogu.com.cn/upload/image_hosting/zjqjebkh.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

因此我们可以先缩点，把图简化成一棵树。

再打开标签一看：LCA。

接下来，因为一条边只能经过一次，所以会出现下面这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/8gl6sksz.png?x-oss-process=image/resize,m_lfit,h_170,w_225)（注：此图跟上图不匹配。）

发现没？不就是求两个点的 LCA，再把这两个点与 LCA 之间所有的点（包括这两个点和 LCA）的权值加入答案嘛。

但如何维护答案呢？

又打开标签一看：差分。

我们可以用树上差分来记录**一个点的经过次数**和**该点的儿子的经过次数**的差。

最后往下一个 dfs，把差分数组合并，如果该点被经过至少一次，则把该点权值加入答案。
### 代码：
```cpp
#include<bits/stdc++.h>
#define N 2000010
#define int long long
using namespace std;
struct hhh{
	int v,next;
}dl[2*N];
int n,m,q,x,y,u[N],v[N],tot,cnt,top,sum,logn,ans;
int a[N],head[N],dfn[N],low[N],stk[N],vis[N],col[N],jh[N],used[N],dep[N],f[N][30],yys[N];//yys即差分数组
void qxx(int u,int v){
	dl[++tot].v=v;
	dl[tot].next=head[u];
	head[u]=tot;
}
void tarjan(int x,int fa){//缩点
	dfn[x]=low[x]=++cnt;
	stk[++top]=x;
	vis[x]=1;
	for(int i=head[x];i;i=dl[i].next){
		int v=dl[i].v;
		if(v==fa) continue;
		if(!dfn[v]) tarjan(v,x),low[x]=min(low[x],low[v]);
		else if(vis[v]) low[x]=min(low[x],low[v]);
	}
	if(dfn[x]==low[x]){
		sum++;
		while(stk[top+1]!=x){
			col[stk[top]]=sum;
			jh[sum]+=a[stk[top]];
			vis[stk[top]]=0;
			top--;
		}
	}
}
void build(int u,int h){//建立LCA
	dep[u]=h;
	for(int i=1;i<=logn;i++){
		if(h<=(1<<i)) break;
		f[u][i]=f[f[u][i-1]][i-1];
	}
	for(int i=head[u];i;i=dl[i].next){
		int v=dl[i].v;
		if(vis[v]) continue;
		vis[v]=1;
		f[v][0]=u;
		build(v,h+1);
	}
}
int lca(int x,int y){//求LCA
	if(dep[x]<dep[y]) swap(x,y);
	int cha=dep[x]-dep[y];
	for(int i=0;i<=logn;i++) if(cha&(1<<i)) x=f[x][i];
	if(x==y) return x;
	for(int i=logn;i>=0;i--){
		if(!dep[f[x][i]]||f[x][i]==f[y][i]) continue;
		x=f[x][i],y=f[y][i];
	}
	return f[x][0];
}
void Go(int x){//合并差分数组
	for(int i=head[x];i;i=dl[i].next){
		int v=dl[i].v;
		if(v==f[x][0]) continue;
		Go(v);
		yys[x]+=yys[v]; 
	}
	if(yys[x]) ans+=jh[x];
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
		qxx(u[i],v[i]),qxx(v[i],u[i]);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i,-1);
	tot=0;
	memset(head,0,sizeof(head));
	for(int i=1;i<=m;i++) if(col[u[i]]!=col[v[i]]) qxx(col[u[i]],col[v[i]]),qxx(col[v[i]],col[u[i]]);
	vis[1]=1;
	logn=log2(sum)+1;
	build(1,1);
	cin>>q;
	while(q--){
		cin>>x>>y;
		int fa=lca(col[x],col[y]);
		yys[col[x]]++,yys[col[y]]++;
		yys[fa]--,yys[f[fa][0]]--;
	}
	Go(1);
	cout<<ans;
	return 0;
}
```


---

## 作者：一E孤行 (赞：8)

## P7924 出题人题解

+ **分析**

就拿题目里的图片分析吧吧qwq

![](https://cdn.luogu.com.cn/upload/image_hosting/a2oku1vq.png)

很显然， $6$ 节点到 $5$ 节点有两种方式可以到达，我们可以观察到，由于这个图是无向图，所以只要有两条及以上的路径，就会形成一个环，此外这个环可能不是简单环。

那这是什么呢？ 很显然，边双联通分量！

那这个时候就可以对这个图进行边双缩点，可得，缩完点后一定是一颗树。这时候两点之间所有的路径就是两点所在树的点之间的路径了，这个路径肯定是唯一的。由于题目要求，一个点的价值只能取一次，所以我们要看看哪些树上的点被覆盖过就好了，树上差分可以很简单的解决这个问题。

代码思路：缩点，每一个大点中保存该边双中的所有小点的权值和。然后对大点重新建图，由上面的分析可得，一定是棵树。然后就愉快的跑 LCA 然后差分就好了。

由于本题时间限制比较紧，建议采用快读和树剖跑 LCA 防止超时问题。

注意，二次建图的时候不要从 $1$ 到 $n$ 然后遍历邻接表，要提前存好然后进行遍历。

+ **Code**

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cstring>
#include<ctime>
#include<cmath>
using namespace std;
#define maxn 4000005
struct aaa{
	int to,nxt;
}a[maxn];
inline int read() {
	int res=0; char ch;
	do ch=getchar(); while(ch<'0' || ch>'9');
	while(ch>='0' && ch<='9') res=res*10+(ch&15), ch=getchar();
	return res;
}
int head[maxn],color[maxn],col,dfn[maxn],low[maxn],cnt,sum[maxn],val[maxn];
#include<stack>
stack<int> s;
bool vis[maxn];
void dfs(int u,int fa) {
	low[u]=dfn[u]=++cnt;
	s.push(u);
	vis[u]=true;
	for(int i=head[u];i!=-1;i=a[i].nxt) {
		int v=a[i].to;
		if(v==fa) continue;
		if(!dfn[v]) {
			dfs(v,u);
			low[u]=min(low[u],low[v]);
		} else if(vis[v]) low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]) {
		int y; col++;
		while(1) {
			y=s.top();
			s.pop();
			vis[y]=0;
			sum[col]+=val[y]; color[y]=col;
			if(y==u) break;
		}
	}
}
int n,m,tot;
void add(int x,int y) {
	a[tot].to=y;
	a[tot].nxt=head[x];
	head[x]=tot++;
}
int Tot,Head[maxn];
aaa b[maxn];
void Add(int x,int y) {
	b[Tot].to=y;
	b[Tot].nxt=Head[x];
	Head[x]=Tot++;
}
int ci;
int fa[maxn],top[maxn],son[maxn],d[maxn],dep[maxn],siz[maxn];
void dfs1(int u,int f) {
	fa[u]=f;
	dep[u]=dep[f]+1;
	siz[u]=1;
	int maxsiz=0;
    ci++;
	for(int i=Head[u];i!=-1;i=b[i].nxt) {
		int v=b[i].to;
		if(v==f) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>maxsiz) {
			maxsiz=siz[v];
			son[u]=v;
		}
	}
}
void dfs2(int u,int t) {
	top[u]=t;
	if(son[u]) dfs2(son[u],t);
	for(int i=Head[u];i!=-1;i=b[i].nxt) {
		int v=b[i].to;
		if(v==fa[u] || v==son[u]) continue;
		dfs2(v,v);
	}
}
int lca(int x,int y) {
	while(top[x]!=top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int ans;
bool viss[maxn];
void dfs3(int u) {
	viss[u]=true;
	for(int i=Head[u];i!=-1;i=b[i].nxt) {
		int v=b[i].to;
		if(v==fa[u] || viss[v]) continue;
		dfs3(v);
		d[u]+=d[v];
	}
	if(d[u] > 0) ans+=sum[u];
}
int from[maxn],to[maxn];
int main() { 
    //int c1=clock();
#ifdef LOCAL
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int c1=clock();
    //=========================================
    //  freopen("in4.in","r",stdin);
	 memset(head,-1,sizeof(head));
	 memset(Head,-1,sizeof(Head));
     scanf("%d%d",&n,&m);
	 for(int i=1;i<=n;i++) {
		 val[i]=read();
	 }
	 for(int i=1;i<=m;i++) {
		 from[i]=read();
		 to[i]=read();
		 int x=from[i],y=to[i];
		 add(x,y);
		 add(y,x);
	 }
	 dfs(1,0);
	 for(int i=1;i<=m;i++) {
		 if(color[from[i]] != color[to[i]]) {
			 Add(color[from[i]],color[to[i]]);
			 Add(color[to[i]],color[from[i]]);
		 }
	 }
	 dfs1(1,0);
	 dfs2(1,1);
	 int q;
	 q=read();
	 for(int i=1;i<=q;i++) {
		 int x,y;
		 x=read();
		 y=read();
		 x=color[x];
		 y=color[y];
		 d[x]++;
		 d[y]++;
		 d[lca(x,y)]--;
		 d[fa[lca(x,y)]]--;
	 }	 
	 dfs3(1);
	 printf("%d\n",ans);
	//=========================================
	cerr<<"Time Used:"<<clock()-c1<<"ms"<<endl;
    return 0;
}
```

---

## 作者：0xFF (赞：5)

#### 题目大意


------------
给定一个有 $n$ 个点 $m$ 条边的无向图，每个点有一个点权。有 $q$ 组询问，每次询问顶点 $x$ 到顶点 $y$ 之间的所有**非严格简单路径**所包含的点权值之和，每个点权值只会被计算一次。

#### 题目分析


------------
根据题目描述，每个点权只会被累加一次，故我们可以处理出总共有多少个点在所有的询问中被覆盖，计算出这些点的权值之和即可。

首先考虑如何在时间范围内实现每个点只被累加一次。

以样例为例：

![样例1](https://cdn.luogu.com.cn/upload/image_hosting/wqllhj01.png)

三次询问共覆盖了 $1,2,3,4$ 这 $4$ 个点，故答案为 $10$。

考虑第一组询问 ```1 2``` 从 $1$ 到 $2$ 共有两条路径，分别是 $1→2$ 与
$1→4→3→2$。仔细观察不难发现：由于图是无向的，所以从顶点 $x$ 到顶点 $y$ 如果有多条路径，那么必定行成**环**。我们可以考虑将此无向图中所有的边双连通分量缩点，也就是说图中所有的边双连通分量可以等效成一个点，这个点的点权值就是此边双连通分量中所有点的权值之和。

经过这样操作之后，整张图上就没有环了，那么必然形成一棵树。题目中要求两个顶点之间的点权和，可以通过树上差分解决。

树上差分是利用两点的最近公共祖先为中转点来维护某一点经过的次数。

在本题中，我们利用树上差分维护操作完成后至少被经过一次的点的点权和。

#### 代码实现


------------

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#define INF 0x3f3f3f3f
using namespace std;

inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}

const int N=5000050;
const int M=5050;

int n,m,a[N],Vis[N],tot,dfn[N],low[N],stk[N],sc,Belong[N],Sum[N],t,cnt;
int pre[N],Size[N],depth[N],fa[N],son[N],Tot,head[N],Head[N],top[N];
bool vis[N]; 
int Cnt,Q;
struct node{
	int u,v,nxt;
}edge[N],E[N];
void Add_edge(int u,int v){
	edge[++cnt].u=u;
	edge[cnt].v=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}
void Add(int u,int v){
	E[++Cnt].v=v;
	E[Cnt].u=u;
	E[Cnt].nxt=Head[u];
	Head[u]=Cnt;
}

int dep[N],f[N][21];

void dfs(int now,int fath){
	dep[now]=dep[fath]+1;
	f[now][0]=fath;
	for(int i=1;(1<<i)<=dep[now];i++){
		f[now][i]=f[f[now][i-1]][i-1];
	}
	for(int i=Head[now];i;i=E[i].nxt){
		if(E[i].v != fath) dfs(E[i].v,now);
	}
}

int LCA(int x,int y){
	if(dep[x]>dep[y]) swap(x,y);
	for(int i=20;i>=0;i--)
	if(dep[x]+(1<<i)<=dep[y]) 
	y=f[y][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--){
		if(f[x][i]==f[y][i]) continue;
		else{
			y=f[y][i];
			x=f[x][i];
		}
	}
	return f[x][0];
}  
void tarjan(int now,int fath){
    low[now]=dfn[now]=++tot;
    stk[++sc]=now;vis[now]=1;
    for(int i=head[now];i;i=edge[i].nxt){
        int to=edge[i].v;
        if(!dfn[to]) tarjan(to,now),low[now]=min(low[now],low[to]);
        else if(vis[to]&&to!=fath) low[now]=min(low[now],dfn[to]);
    }
    if(dfn[now]==low[now]){
        int pre=stk[sc--];
        Sum[++t]+=a[pre];
        Belong[pre]=t;vis[pre]=0;
        while(pre!=now){
            pre=stk[sc--],Sum[t]+=a[pre];
            Belong[pre]=t;vis[pre]=0;
        }
    }
}
long long Ans;
void Dfs(int now,int fath){
	for(int i=Head[now];i;i=E[i].nxt){
		if(E[i].v != fath) Dfs(E[i].v,now),
		Vis[now] += Vis[E[i].v];
	}
	if(Vis[now]) Ans+=Sum[now];
} 

signed main() {
    n=read(); m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1,u,v;i<=m;i++){
   	    u=read();v=read();
		Add_edge(u,v);Add_edge(v,u);
    }
    Q=read();
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i,0);
    for(int i=1;i<=cnt;i+=2){
   	    if(Belong[edge[i].u]^Belong[edge[i].v]){
   	        Add(Belong[edge[i].u],Belong[edge[i].v]);
   	        Add(Belong[edge[i].v],Belong[edge[i].u]);	
		}
    } 
    memset(dfn,0,sizeof dfn);
    for(int i=1;i<=Q;i++){
   	    int u=read(),v=read();
        int Lca=LCA(Belong[u],Belong[v]);
   	    Vis[Belong[u]]++;Vis[Belong[v]]++;
   	    Vis[Lca]--;
       	Vis[fa[Lca]]--;
       	Vis[f[Lca][0]]--;
   }
   Dfs(Belong[1],0); 
   printf("%lld\n",Ans);
   return 0;
}
```


---

## 作者：我是逍逍 (赞：3)

### 前言
感觉上出题人想卡 $O(n\log n)$，所以在这里提供一种线性做法。（将崇高的敬意献给 **Tarjan**）  

### 思路 & 算法
由无向图中的简单路径想到可以使用 **Tarjan** 算法缩点，建树；对于每个旅游季的统计，可以使用树上差分维护。  

旅游季单次操作的复杂度为 $O(\log n)$，为求解 **LCA** 的时间复杂度。但是本题的数据量非常大，直接树上倍增十分卡常，而本人又不愿意写树剖，因此，我们请出时间复杂度为 $O(n+m+q)$ 的 **Tarjan LCA** 算法。

#### Tarjan LCA
这个算法采用离线的方法，结合并查集，线性求解树上 **LCA** 问题。方法为首先储存好所有的询问，接着 **DFS** 遍历树，在回溯的过程中，求解 **LCA**。具体如下：  
1. 标记 $vis_u=true$；
2. 遍历 $u$ 的树边 $(u,v)$，向下递归，回溯时将并查集 $v$ 合并到 $u$；
1. 遍历与当前节点 $u$ 有关的询问，对于每一个询问，查询 **LCA** 的另一目标点 $v$ 的 $vis_v$ 状态。若 $vis_v$ 为真，则此时点 $v$ 所属的并查集则为 $(u,v)$ 的 **LCA**。

### 实现 & 代码
要注意的细节不多，只是代码偏长，**Tarjan LCA** 的代码量不比树剖小很多。

```cpp
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

const int Max = 500005;

int n, m, q, a[Max], c[Max], cnt, s[Max], w[Max], par[Max], ans;
vector<int> g[Max], G[Max], Q[Max]; // 分别为原图、缩点后的图、询问

namespace TarjanDCC { // Tarjan 求双连通分量
	int t, dfn[Max], low[Max], w[Max];
	stack<int> st;
	bool ins[Max];

	void tarjan(int u, int _u = 0) {
	    dfn[u] = low[u] = ++t;
	    st.push(u);
	    ins[u] = true;

	    for (int v: g[u])
	        if (v != _u) {
	            if (!dfn[v]) {
	                tarjan(v, u);
	                low[u] = min(low[u], low[v]);
	            } else if (ins[v])
	                low[u] = min(low[u], dfn[v]);
	        }

	    if (dfn[u] == low[u]) {
	        int v;
	        ++cnt;
	        do {
	            v = st.top();
	            st.pop();
	            ins[v] = false;
	            c[v] = cnt;
	            s[cnt] += a[v];
	        } while (v != u);
	    }
	}

	void rebuild() { // 重新建图
		for (int i = 1; i <= n; i++)
	        for (auto j: g[i])
	            if (c[i] != c[j])
	                G[c[i]].push_back(c[j]);
	}

	void main() {
		tarjan(1);
		rebuild();
	}
}

namespace TarjanLCA { // Tarjan 求 LCA
	int anc[Max]; // 并查集数组
	bool vis[Max];

	void init() { // 并查集初始化
		for (int i = 1; i <= cnt; i++) 
			anc[i] = i;
	}

	int findAncestor(int u) {
		return anc[u] == u ? u : anc[u] = findAncestor(anc[u]);
	}

	void merge(int u, int v) {
		u = findAncestor(u), v = findAncestor(v);
		anc[v] = u;
	}

	void tarjan(int u, int _u = 0) {
		vis[u] = true;
		par[u] = _u;

		for (int v: G[u]) 
			if (!vis[v]) {
				tarjan(v, u);
				merge(u, v);
			}

		for (int v: Q[u])
			if (vis[v]) { // 求出 LCA 之后直接树上差分
				int lca = findAncestor(v);
				w[u]++, w[v]++;
				w[lca]--;
				w[par[lca]]--;
			}
	}

	void main() {
		init();
		tarjan(c[1]);
	}
}

void read(int &x) {
    x = 0;
    char ch;
    while (!isdigit(ch = getchar()));
    do x = x * 10 + ch - '0';
    while (isdigit(ch = getchar()));
} 

int main() {
    read(n), read(m);
    for (int i = 1; i <= n; i++)
        read(a[i]);

    for (int i = 1, u, v; i <= m; i++) {
        read(u), read(v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    TarjanDCC::main();

    read(q);
    for (int i = 1, u, v; i <= q; i++) {
        read(u), read(v);
    	u = c[u], v = c[v];
    	Q[u].push_back(v);
    	Q[v].push_back(u);
    }

    TarjanLCA::main();
    
    // 由 Tarjan 缩点算法的性质，
    // DCC 编号为逆拓扑序，
    // 可以直接 For 循环求子树和。
    for (int i = 1; i <= cnt; i++) { 
        if (w[i] > 0)
            ans += s[i];
        w[par[i]] += w[i];
    }

    cout << ans << endl;
    return 0;
}
```

---

## 作者：exited (赞：2)

Update ：核心证明已给出。

## 题面翻译：
给出一张无向图，每一个点有点权。现给出 $q$ 组 $(x,y)$，求所有 $x$ 到所有对应 $y$ 的路径上的**边双连通分量**的点权和。

有点懵，对吧？为什么是边双连通分量呢？来看：
## 分析

### 缩点

如图（黑色为点编号，红色为点权）：
![](https://cdn.luogu.com.cn/upload/image_hosting/beexkade.png)
当有这么一对 $(1,6)$ 时，小 $A$ 会把从 $1$ 到 $5$ 的路径都走遍，再走到 $6$。

如果往后走不会走到死胡同里，就接着走。

_Q_: 那这个“死胡同”是什么？

_A_: 一个新的边双连通分量 。（~~毕竟算法标签里有缩点嘛~~）

_Q_: 为什么？

_A_:

我们知道，两个边双是由一条割边连接起来的，而且在一个连通图中，任意两个边双的路径唯一。

即：从甲边双到乙边双间有一条边与之相连，而这条边便是从甲到乙的“必经之路”

而题目中说：点可以重复经过，而边不可以。

即在同一条路径中，一条边不能经过两次。

而在同一个边双里面，由于没有割边的限制，于是可以保证里面的点便都可以到达，而不会出现走回头路的情况。

因为同一个边双里的点之间的路径上没有割边，且路径不唯一。

但是如果过了终点所在的边双，就不能够通过割边返回了。

于是一个旅游季的答案为：从 $x$ 到 $y$ 所经过边双里的点的点权之和。

还不明白什么是边双，以及如何缩点的OIer请自行查找博客。

#### PS：
这些点可以缩到一起：
![](https://cdn.luogu.com.cn/upload/image_hosting/ticp3wck.png)

------------

### LCA

缩完点，这个图立马清晰得多了：
![](https://cdn.luogu.com.cn/upload/image_hosting/k3k4jnxi.png)

对于一个无向图，由于它是连通的，所以剩下来的是一个无根树。

而求两个点所在的边双的路径的话，就有请 LCA 登场！

LCA 之前要先跑一遍 DFS 转换为有根树。

LCA 用的便是~~喜闻乐见~~的倍增大法。代码里有完整模板。

------------

### 树上差分

由于要统计点权之和，_**而且**_ 重复经过的只统计一次！

所以传统的树上差分改一下，改成标记差分：过一个点，标记++。

标记 $\geq 1$ 的，加入到答案内即可。

一定要注意：是**点权**而不是**边权**。

模板也在代码内。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=800005;
int n,m,a[N],tot,head[N],q,dfn[N],low[N],inx,st[N],top,bel[N],cnt,val[N],dis[N];
long long cha[N];
bool in[N];
struct EDGE{
	int v,nxt;
}ed[N<<3];
void add(int u,int v){
	ed[++tot]={v,head[u]};
	head[u]=tot;
}
void tarjan(int x,int f){
	low[x]=dfn[x]=++inx;
	st[++top]=x;in[x]=true;
	for(int i=head[x];i;i=ed[i].nxt){
		int v=ed[i].v;
		if(v==f) continue;
		if(!dfn[v]){
			tarjan(v,x);
			low[x]=min(low[x],low[v]);
		}
		else if(in[v]) low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x]){
		int y;++cnt;
		while(y=st[top--]){
			val[cnt]+=a[y];
			in[y]=false;
			bel[y]=cnt;
			if(x==y) break;
		}
	}
}
int u[N<<2],v[N<<2],dep[N],fa[N][25];
void dfs(int x,int dept,int f){
	dep[x]=dept;fa[x][0]=f;
	dis[x]=val[x]+dis[f];
	for(int i=head[x];i;i=ed[i].nxt){
		int v=ed[i].v;
		if(v==f) continue;
		dfs(v,dept+1,x);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	while(dep[x]>dep[y])
		x=fa[x][(int)log2(dep[x]-dep[y])-1];
	if(x==y) return x;
	for(int i=20;i>=0;i--)
		if(fa[x][i]!=fa[y][i]){
			x=fa[x][i];
			y=fa[y][i];
		}
	return fa[x][0];
}
int dfs2(int x,int f){
	for(int i=head[x];i;i=ed[i].nxt){
		int v=ed[i].v;
		if(v==f) continue;
		dfs2(v,x);
		cha[x]+=cha[v];
	}
	return cha[x];
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u[i],&v[i]);
		add(u[i],v[i]);
		add(v[i],u[i]);
	}
	tarjan(1,0);//缩点，因为图是连通的，所以任选一点作为起点
	tot=0;
	memset(head,0,sizeof head);
	for(int i=1;i<=m;i++){
		u[i]=bel[u[i]],v[i]=bel[v[i]];
		if(u[i]!=v[i]) add(u[i],v[i]),add(v[i],u[i]);
	}
	dfs(bel[1],1,0);
	cin>>q;
	for(int i=1;i<=20;i++)
		for(int j=1;j<=cnt;j++)
			fa[j][i]=fa[fa[j][i-1]][i-1];
	int x,y;
	int ans=0;
	for(int i=1;i<=q;i++){ // LCA、树上差分
		scanf("%d%d",&x,&y);
		x=bel[x],y=bel[y];
		int s=lca(x,y);
		cha[x]++;
		cha[y]++;
		cha[s]--;
		cha[fa[s][0]]--;
	}
	dfs2(bel[1],0);//还原标记
	for(int i=1;i<=cnt;i++)
		if(cha[i])
			ans+=val[i];
	cout<<ans;
	return 0;
}
```


---

## 作者：fanypcd (赞：2)

```
定义一条旅游路径为两个景点之间的一条非严格简单路径，也就是点可以重复经过，而边不可以。

指定两个顶点 x 和 y，走遍 x 到 y 的所有旅游路径。
```

手玩一下，发现一个处于同一个边双里面的所有点，如果有任意一个能够被经过，那么整个连通分量的点都能被经过。（它们可以等效为一个点）

再想一想，有向图中强连通分量缩成一个点是什么（有向无环图，DAG），那么连通的无向图中边双连通分量缩成一个点后，原图就是一个无向无环图，即树。

好，我们将原图用 tarjan 把所有边双缩成一个点，现在问题转变为了，给你一棵树， $n$ 个节点，$n - 1$ 条边，每个点有点权。有 $q$ 次操作，每次操作经过 $x$ 到 $y$ 的简单路径上的所有点，回答操作完成后至少被经过一次的点的点权的和。

如果是操作中询问就是树链剖分的板子，操作后询问就是树上差分的板子。

LCA 算法的话倍增和轻重链剖分都可以，凭个人喜好吧（其实个人感觉加强成操作中回答询问后反而省得专门写一个求 LCA 的算法）。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define N 500005
#define M 2000005
class Graph
{
	public:
	int first[N], Next[M << 1], to[M << 1], vis[M << 1], tot;
	inline void add(int x, int y)
	{
		Next[++tot] = first[x];
		first[x] = tot;
		to[tot] = y;
		return;
	}
};
Graph G1, G2;
int n, m, a[N];
int dfn[N], low[N], sign;
int cnt, sum[N], bel[N];
int sta[N], top;
void tarjan(int u, int pre)
{
	dfn[u] = low[u] = ++sign;
	sta[++top] = u;
	for(int i = G1.first[u]; i; i = G1.Next[i])
	{
		int v = G1.to[i];
		if(!dfn[v])
		{
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
		}
		else if(v != pre)
		{
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(low[u] == dfn[u])
	{
		cnt++;
		while(sta[top] != u)
		{
			bel[sta[top]] = cnt;
			sum[cnt] += a[sta[top]];
			top--;
		}
		bel[sta[top]] = cnt;
		sum[cnt] += a[sta[top]];
		top--;
	}
	return;
}
inline void link()
{
	for(int u = 1; u <= n; u++)
	{
		for(int i = G1.first[u]; i; i = G1.Next[i])
		{
			int v = G1.to[i];
			if(bel[u] != bel[v])
			{
				G2.add(bel[u], bel[v]);
			}
		}
	}
	return;
}
int dep[N], fa[N][25], vis[N];
void dfs(int u)
{
	for(int i = 1; i <= 20; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for(int i = G2.first[u]; i; i = G2.Next[i])
	{
		int v = G2.to[i];
		if(dep[v])
		{
			continue;
		}
		dep[v] = dep[u] + 1;
		fa[v][0] = u;
		dfs(v);
	}
	return;
}
inline int lca(int x, int y)
{
	if(dep[x] > dep[y])
	{
		swap(x, y);
	}
	for(int i = 20; i >= 0; i--)
	{
		if(dep[fa[y][i]] >= dep[x])
		{
			y = fa[y][i];
		}
	}
	if(x == y)
	{
		return x;
	}
	for(int i = 20; i >= 0; i--)
	{
		if(fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}
void solve(int u)
{
	for(int i = G2.first[u]; i; i = G2.Next[i])
	{
		int v = G2.to[i];
		if(v == fa[u][0])
		{
			continue;
		}
		solve(v);
		vis[u] += vis[v];
	}
	return;
}
signed main()
{
	read(n), read(m);
	for(int i = 1; i <= n; i++)
	{
		read(a[i]);
	}
	int x, y;
	for(int i = 1; i <= m; i++)
	{
		read(x), read(y);
		G1.add(x, y), G1.add(y, x);
	}
	for(int i = 1; i <= n; i++)
	{
		if(!dfn[i])
		{
			tarjan(i, i);
		}
	}
	link();
	dep[bel[1]] = 1;
	dfs(bel[1]);
	int q;
	read(q);
	while(q--)
	{
		read(x), read(y);
		vis[bel[x]]++;
		vis[bel[y]]++;
		int lc = lca(bel[x], bel[y]);
		vis[lc]--;
		vis[fa[lc][0]]--;
	}
	solve(bel[1]);
	int ans = 0;
	for(int i = 1; i <= cnt; i++)
	{
		if(vis[i])
		{
			ans += sum[i];
		}
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：ask_silently (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7924)

给一个不需要求 lca 的做法。

## 题目分析

由于是所有的简单路径同时点可以同时经过，又因为是无向图，所以想到了求出点双然后做 dp，然而这道题比较简单，不需要做 dp。

很明显，在一个点双中的一定可以被多条简单路径完全覆盖，所以一定可以全部选上。由于有多个源点和多个汇点，所以考虑建立一个超级源点和一个超级汇点。

将超级源点向每个源点连一条双向边，同时将超级汇点向每个汇点连一条双向边，此时在新图上求点双。根据点双的定义，易知源点和超级源点属于一个点双，同时汇点与超级汇点属于同一个点双。

求出点双后是一棵树，那最后的答案就是源点到汇点的路径上值总和。

可以发现，这样做似乎一个源点的终点有多个，但发现并不影响。因为在树上的路径即计算上去的点双一定有一个源点可以走到，同时走到之后依旧可以不通过重复的边到达属于自己的汇点，所以一定可以加上该点的答案。同时任意一个源点走到不属于这个路径的点双后，必须再次经过割边才能走到属于汇点的点双，不符合题意。

由此我们证明了新的答案一定不大于原答案和新的答案一定不小于原答案，所以这种做法的答案与原答案相同，证毕。

时间复杂度 $O(n+m)$。

## AcCode


```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=5e5+10;
const int M=4e6+10;

int n,m,idx,dn,cnt,idx1;
int a[N],val[N],dp[N];
int head[N],nxt[2*M],ver[2*M];
int dfn[N],low[N],bein[N];
int head1[N],nxt1[2*M],ver1[2*M];

bool vis[N],vis1[N];

stack<int> s;

inline int read(){
	int t=0,f=1;
	register char c=getchar();
	while(c<'0'||c>'9') f=(c=='-')?(-1):(f),c=getchar();
	while(c>='0'&&c<='9') t=(t<<3)+(t<<1)+(c^48),c=getchar();
	return t*f;
}

void add(int u,int v){
	nxt[++idx]=head[u];
	head[u]=idx;
	ver[idx]=v;
}

void dfs(int u,int v){
	dfn[u]=++dn,low[u]=dfn[u],vis[u]=true;
	s.push(u);
	for(int i=head[u];i;i=nxt[i]){
		int dao=ver[i];
		if(dao==v) continue;
		if(!vis[dao]){
			dfs(dao,u);
			low[u]=min(low[u],low[dao]);
		}else low[u]=min(low[u],dfn[dao]);
	}
	if(low[u]==dfn[u]){
//		cout<<"u:"<<u<<"\n";
		cnt++;
		while(s.top()!=u) bein[s.top()]=cnt,s.pop();
		bein[s.top()]=cnt,s.pop();
	}
}

void dfs1(int u,int v){
	vis1[u]=true;
	for(int i=head1[u];i;i=nxt1[i]){
		int dao=ver1[i];
		if(vis1[dao]) continue;
		dp[dao]+=dp[u];
		dfs1(dao,u);
	}
}

void add1(int u,int v){
	nxt1[++idx1]=head1[u];
	head1[u]=idx1;
	ver1[idx1]=v;
}

bool visu[N],visv[N];

signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	int q=read();
	while(q--){
		int u=read(),v=read();
		if(!visu[u]) visu[u]=true,add(0,u),add(u,0);
		if(!visv[v]) visv[v]=true,add(n+1,v),add(v,n+1);
	}
	dfs(0,0);
	for(int i=0;i<=n+1;i++){
		val[bein[i]]+=a[i],dp[bein[i]]=val[bein[i]];
		for(int j=head[i];j;j=nxt[j]){
			int dao=ver[j];
			if(bein[dao]==bein[i]) continue;
			add1(bein[i],bein[dao]);
			add1(bein[dao],bein[i]);
		}
	}
	dfs1(bein[0],0);
	cout<<dp[bein[n+1]]<<"\n";
	return 0;
}


```

---

