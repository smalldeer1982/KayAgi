# [ABC318G] Typical Path Problem

## 题目描述

给出一个有 $n$ 个顶点和 $m$ 条边的无向连通图 $G$，没有重边和自环。

顶点的编号为 $1 \sim n$，边的编号为 $1 \sim m$，第 $i$ 条边连接顶点 $u_i$ 和 $v_i$。

给出图上三个不同的顶点 $A,B,C$。判断是否有从点 $A$ 经过点 $B$ 到点 $C$ 的简单路径。

简单路径指路径上的点互不相同，即不重复经过同一个点。

## 说明/提示

- $3 \le n \le 2 \times 10^5$
- $n-1 \le m \le \min(\frac{n(n-1)}{2}, 2 \times 10^5)$
- $1 \le A,B,C \le n$
- $1 \le u_i < v_i \le n$

## 样例 #1

### 输入

```
6 7
1 3 2
1 2
1 5
2 3
2 5
2 6
3 4
4 5```

### 输出

```
Yes```

## 样例 #2

### 输入

```
6 6
1 3 2
1 2
2 3
2 5
2 6
3 4
4 5```

### 输出

```
No```

## 样例 #3

### 输入

```
3 2
1 3 2
1 2
2 3```

### 输出

```
No```

# 题解

## 作者：shinzanmono (赞：15)

我们考虑，简单路径的要求是每一个点和每一条边都只能通过一次。限制点和边的通过次数，这种事情最在行的就是 Dinic。

我们将原图建成一个网络。

先将每个点 $u$ 拆成入点 $u$ 和出点 $u'$，从 $u$ 向 $u'$ 连一条流量为 $1$ 的边，表示一个点只能经过一次。其中，额外从 $B$ 到 $B'$ 连一条边，表示 $B$ 可以经过两次。

将 $S$ 向 $B$ 连一条流量为 $2$ 的边，表示从 $B$ 发出了 $2$ 条路径。

将 $A',C'$ 分别向 $T$ 连一条流量为 $1$ 的边，表示最后 $A,C$ 是否可以到达。

接着，把每一条无向边链接为 $U'\rightarrow V$ 与 $V'\rightarrow U$，每一条边的流量为 $1$表示每一条边只能经过一次。

如果存在满足题意的路径，那么从源点到汇点的最大流为 $2$，这样就可以解决这道题。

时间复杂度分析：

由于所有边权都可以视作单位容量，最多增广 $2$ 轮，所以总的时间复杂度为 $O(N)$，带有常数 $2$，可以通过此题。

---

## 作者：_sunkuangzheng_ (赞：9)

 

**【题目大意】**

给定 $n(1 \le n \le 2 \times 10^5)$ 个点 $m(1 \le m \le 2 \times 10^5)$ 条边的无向连通图，问是否存在一条从 $a$ 到 $c$ 经过 $b$ 的简单路径。

**【题目分析】**

本题可以使用圆方树解决，需要的前置知识：点双连通分量，圆方树。（相信点开这篇题解的您肯定会这些捏 qwq）

我们首先对原图建出圆方树，对样例建的圆方树如下图。（其中加粗的为方点）

![](https://cdn.luogu.com.cn/upload/image_hosting/ov76f2ad.png)

因为一个点双连通分量会建一个方点，所以我们得到一个关键结论：**若从 $a$ 到 $c$ 的路径上存在一个方点 $u$，满足 $u$ 与 $b$ 直接相连，那么有解**。上面的例子里，$8$ 号点就是那个方点，$8$ 号点与 $3$ 号点直接相连，所以有解。

这样做的正确性也比较显然，因为方点所连的圆点在一个点双连通分量里，所以若存在满足上述条件的方点，就一定有一条路径可以经过点 $b$ 并继续前进直到 $c$。

时间复杂度为 $\mathcal O(n+m)$。

**【代码】**

代码实现上，建好圆方树后先以 $c$ 为根 dfs 一遍求出每个点的父亲，再从 $a$ 开始向上跳，找路径上的方点。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5+5;
vector<int> g[maxn],gr[maxn];
int n,m,a,b,c,u,v,dfn[maxn],low[maxn],ti,s[maxn],top,tp,tot,fa[maxn];
void tarjan(int u){
    low[u] = dfn[u] = ++ti,s[++top] = u;
    for(int v : g[u]){
        if(!dfn[v]){
            tarjan(v),low[u] = min(low[u],low[v]);
            if(dfn[u] == low[v]){
                gr[++tot].push_back(u),gr[u].push_back(tot);
                while(s[top] != v) tp = s[top --],gr[tot].push_back(tp),gr[tp].push_back(tot);
                gr[tot].push_back(v),gr[v].push_back(tot),top --;
            }
        }else low[u] = min(low[u],dfn[v]);
    }
}void dfs(int u,int fat){
    fa[u] = fat;
    for(int v : gr[u]) if(v != fat) dfs(v,u);
}bool calc(int u){
    while(u != c){
        if(u > n) for(int v : gr[u]) if(v == b) return 1;
        u = fa[u];
    }return 0;
}
int main(){
    cin >> n >> m >> a >> b >> c,tot = n;
    for(int i = 1;i <= m;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
    for(int i = 1;i <= n;i ++) if(!dfn[i]) tarjan(i);dfs(c,0);
    cout << (calc(a) ? "Yes" : "No");
}
```

---

## 作者：Register_int (赞：5)

[Over all](/blog/const1e7/abc318-solution)

这题如果不用 flow 来做的话分讨还是比较繁杂的。

先缩点双，分几种情况考虑：

#### 1. A 与 B 在同一个点双内 或者 B 与 C 在同一个点双内（不包含割点）。

此时可以发现，从 A 或 C 点必然能够到达 B 点，且可以选出两条不经过同一个点的路径，因此必定有解。

#### 2. A 与 C 在同一个点双内，且 B 是该点双的一个割点。

此时也可以选出这样的一条路径。

#### 3. 其他。

在以 B 为根在缩点后的树上进行深搜，当 A 与 C 不在同一个子树内时或均与 B 在同一个点时则有解，否则无解。

时间复杂度 $O(n+m)$。

感谢 Castilian 提供的一组 hack 数据。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 4e5 + 10;

struct edge {
    int v, nxt;
} e[MAXN << 1];

int head[MAXN], tot;

inline 
void add(int u, int v) {
    e[++tot] = { v, head[u] }, head[u] = tot;
}

inline 
void clear() {
    memset(head, 0, sizeof head), tot = 0;
}

int dfn[MAXN], low[MAXN], num;

int cnt, c[MAXN], id[MAXN]; bool cut[MAXN];

stack<int> s;
vector<int> scc[MAXN];

inline 
void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++num, s.push(u);
    int son = 0, x = 0;
    for (int i = head[u], v; i; i = e[i].nxt) {
        v = e[i].v;
        if (!dfn[v]) {
            son++;
            tarjan(v, u), low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                cut[u] = 1;
                for (cnt++, x = 0; x != v;) scc[cnt].push_back(x = s.top()), s.pop();
                scc[cnt].push_back(u);
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
    if (!fa && !son) scc[++cnt].push_back(u), cut[u] = 1;
}

map<int, bool> mp[MAXN];

inline 
void build(int n) {
    tarjan(1, 0), clear(), num = cnt;
    for (int i = 1; i <= n; i++) if (cut[i]) c[i] = ++num;
    for (int i = 1; i <= cnt; i++) {
        for (int u : scc[i]) {
            if (cut[u]) add(i, c[u]), add(c[u], i), mp[u][i] = 1;
            else id[u] = i;
        }
    }
}

inline 
int get(int u) {
    return id[u] ? id[u] : c[u];
}

int col[MAXN];

void dfs(int u, int f, int x) {
    col[u] = x;
    for (int i = head[u]; i; i = e[i].nxt) if (e[i].v != f) dfs(e[i].v, u, x);
}

int x, y, z;

int n, m;

int main() {
    scanf("%d%d%d%d%d", &n, &m, &x, &y, &z);
    for (int i = 1, u, v; i <= m; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
    build(n);
    if (get(x) == get(y) || get(y) == get(z) || get(x) == get(z) && mp[y][get(x)]) return puts("Yes"), 0;
    for (int i = head[get(y)]; i; i = e[i].nxt) dfs(e[i].v, get(y), e[i].v);
    puts(col[get(x)] != col[get(z)] ? "Yes" : "No");
}
```

---

## 作者：ForgotDream_CHN (赞：3)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17674617.html)

> 给定无向连通图，问是否存在一条从 $A$ 到 $C$ 经过 $B$ 的简单路径。  
> $n \le 3 \times 10^5$。

怎么这个 G 这么简单我还没写完啊？怎么这个 G 这么简单我还没写完啊？怎么这个 G 这么简单我还没写完啊？怎么这个 G 这么简单我还没写完啊？怎么这个 G 这么简单我还没写完啊？怎么这个 G 这么简单我还没写完啊？

官方题解网络流，不知道怎么想的。

我们把图缩个点双，然后根据点双的性质，即同一个点双内部的一对点之间至少存在两条简单路径，发现 $A$ 到 $C$ 存在经过 $B$ 的简单路径的充要条件是在缩点之后 $B$ 所在的点双在点双树上 $A$ 到 $C$ 的路径上。那么直接大力建个圆方树然后在圆方树上跳 LCA 就行。

时间复杂度严格 $\mathcal{O}\left(n + m\right)$，貌似薄纱了官方题解。

[代码 link。](https://atcoder.jp/contests/abc318/submissions/45196663)

---

## 作者：lfxxx (赞：2)

因为是图上路径是否经过某个点的问题，所以考虑建出圆方树，然后根据圆方树的性质，$a$ 到 $c$ 存在经过 $b$ 的路径等价于 $a,c$ 在圆方树上的路径经过 $b$ 或者 $b$ 所连接的方点，考虑暴力在圆方树上跳 LCA 即可，时间复杂度 $O(n + m)$。

```cpp
#include<bits/stdc++.h> 

using namespace std;

const int maxn = 4e5+114;

int n,m,cnt;
std::vector<int> G[maxn],T[maxn<<1];
int fa[maxn];

int dfn[maxn], low[maxn], dfc;
int stk[maxn],tp;
int f[maxn];
int dep[maxn<<1];
int val[maxn<<1];
int a,b,c;
void Tarjan(int u) {
  low[u] = dfn[u] = ++dfc;            
  stk[++tp] = u;                 
  for (int v : G[u]){               
    if (!dfn[v]) {                    
      Tarjan(v);                          
      low[u] = std::min(low[u], low[v]);  
      if (low[v] == dfn[u]) { 
        ++cnt;   
        for (int x = 0; x != v; --tp) {
          x = stk[tp];
          T[cnt].push_back(x);
          T[x].push_back(cnt);
          val[cnt]|=val[x];
        }
        val[cnt]|=val[u];
        T[cnt].push_back(u);
        T[u].push_back(cnt);
      }
    }else
      low[u] = std::min(low[u], dfn[v]);
  }
}
void build(){
	cnt=n;
	for(int u=1;u<=n;u++){
		if(!dfn[u]) Tarjan(u), --tp;
	}
	for(int i=n+1;i<=cnt;i++){
		for(int u:T[i]){
			f[u]=i;
		}	
	} 
}
void dfs(int u,int father){
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(int v:T[u]){
		if(v==father) continue;
		dfs(v,u);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	int a,b,c;
	cin>>a>>b>>c;
	val[b]=1;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	build();
	dfs(1,0);
	int ans=0;
	ans|=(val[a]|val[c]);
	while(a!=c){
		if(dep[a]<dep[c]) swap(a,c);
		a=fa[a];
		ans|=(val[a]|val[c]);
	} 
	cout<<(ans==1?"Yes\n":"No\n");
	return 0;
}
```

其实这题还可以多组询问，考虑把询问挂在 $b$ 上然后树剖即可。时间复杂度是 $O(q \log n + n \log n + m)$ 的。

---

## 作者：是青白呀 (赞：1)

## 题意

给出一个有 $N$ 个节点、$M$ 条边的简单无向连通图，问是否存在一条从节点 $A$ 出发，经过节点 $B$ 到达节点 $C$ 的简单路径。这里，简单路径是指途径的点不重复的路径。

## 分析
不难想到可以找到 $A$、$C$ 两点间的所有简单路径，判断 $B$ 点是否在其中任意一条上。不难想到对于原图建立圆方树。

圆方树有一个很优秀的性质：对于原图上的任意两个点，它们之间所有简单路径上的点的集合，等于圆方树上与两点间路径上的所有方点连接的所有圆点的集合。因而，我们直接判断与 $B$ 连接的所有方点中，是否存在一个方点在 $A$ 到 $C$ 的路径上即可。可以以 $A$ 或 $C$ 为根在圆方树上 dfs。 

## Code

```cpp
#include<bits/stdc++.h> 
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) x*2
#define rs(x) x*2+1
#define mp make_pair
#define fir first
#define sec second
#define pii pair<int,int>
#define lowbit(x) x&-x
//Coded by Qingbai666 
using namespace std;
const int N=2e5+5;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,m,a,b,c,cntf,low[N],dfn[N],cnt;
struct tree{
	int to[4*N],nxt[N*4],fir[N*2],np,vis[N*2];
	void add(int x,int y){
		to[++np]=y,nxt[np]=fir[x];
		fir[x]=np;
	}
	void dfs(int x,int f){
		if(x==c)vis[x]=1;
		for(int i=fir[x];i;i=nxt[i]){
			int j=to[i];
			if(j!=f){
				dfs(j,x);
				vis[x]|=vis[j];
			}
		} 
	}
	bool check_access(int x){
		if(vis[x])return 1;
		for(int i=fir[x];i;i=nxt[i])
			if(to[i]>n&&vis[to[i]])return 1;
		return 0;
	}
	bool check(){
		dfs(a,0);
		if(check_access(b)&&vis[c])return 1;
		else return 0;
	}
}T;
struct edge{
	int to[2*N],nxt[N*2],fir[N],np;
	void add(int x,int y){
		to[++np]=y,nxt[np]=fir[x];
		fir[x]=np;
	}
	stack<int>stk;
	void tarjan(int x){
		stk.push(x);
		low[x]=dfn[x]=++cnt;
		for(int i=fir[x];i;i=nxt[i]){
			int j=to[i];
			if(dfn[j]){
				low[x]=min(low[x],dfn[j]);
				continue;
			}
			else{
				tarjan(j);
				low[x]=min(low[x],low[j]);
				if(low[j]>=dfn[x]){
				    cntf++;
					while(stk.top()!=j){
						int nw=stk.top();
						T.add(nw,cntf),T.add(cntf,nw);
						stk.pop();
					}
					T.add(j,cntf),T.add(cntf,j),stk.pop();
					T.add(x,cntf),T.add(cntf,x);
				}
			}
		}
	}
}G;
int main(){
	read(n),read(m),read(a),read(b),read(c),cntf=n;
	rep(i,1,m){
		int x,y;
		read(x),read(y);
		G.add(x,y),G.add(y,x);
	}
	G.tarjan(1);
	if(T.check())printf("Yes\n");
	else printf("No\n");
   return 0;
}
```

---

## 作者：lsj2009 (赞：1)

> <https://atcoder.jp/contests/abc318/tasks/abc318_g>。
>
> 给定一张简单无向连通图，判断是否存在一条图上简单路径使得经过 $b$ 从 $a$ 到 $c$。
>
> $n,m\le 2\cdot 10^5$。

首先可以直接园方树。

~~但是我赛时以为是边双。但是我赛时以为是边双。但是我赛时以为是边双。~~

这里讲一种人类智慧做法。

注意到一个点只能经过一次，所以我们考虑拆点，跑网络流。

首先拆点，$u$ 到 $u'$ 连一条容量为 $1$ 的边，代表一个点只能走一次。

然后把超级源点向 $a,c$ 分别连一条流量为 $1$ 的边，把 $b$ 作为超级汇点。

对于原图上的边 $u,v$ 则是 $u'$ 到 $v$ 连一条 $\text{inf}$ 的边，即对边不做限制。

然后跑最大流，如果最大流为 $2$ 则有解，否则无解。

为什么这样是对的？这里其实运用到了 $\text{meet-in-the-middle}$ 的思想，又因为原图无向连通，所以存在 $a,c$ 经过 $b$ 的路径，等价于存在一条 $a$ 到 $b$ 的路径和一条 $c$ 到 $b$ 的路径且两路径无交集。

至于复杂度，由于流量至多为 $2$，即最多增广两次，所以复杂度为 $\Theta(n+m)$。

---

## 作者：happybob (赞：1)

典中典。

考虑如果 $A \rightarrow B$ 的路径中必须要经过的点与 $B \rightarrow C$ 必须要经过的点，除了 $B$ 点之外还有交集，那显然没有这样的 $A \rightarrow B \rightarrow C$ 的简单路径。

然后显而易见的这是圆方树板子，两个点之间必须要经过的点是圆方树上两点路径上所有圆点。因为只有一次询问，所以随便把路径拉出来就没了。

---

## 作者：不知名用户 (赞：0)

圆方树板子题。

题意：给定一张无向联通图，给定三个点 $A,B,C$ 问是否有从 $A$ 到 $C$ 且经过 $B$ 的简单路径。

只用把每个实际点（圆点）与它所在的点双的虚拟节点（方点）连一条边建立圆方树，然后将 $A$ 到 $C$ 的路径上每一个圆点连接的方点都打标记，看 $B$ 是否有标记即可。路径直接暴力跳即可。

一定把数组开大，没给 $fa$ 数组开大，害得我没有场切。附[悲惨的赛场记录](https://atcoder.jp/contests/abc318/submissions?f.Task=&f.LanguageName=&f.Status=&f.User=genyi_sith)。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

int n, a, b, c;

int stk[N], top;

int dfn[N], low[N], cur;

int cnt;

int h[N], e[N*2], ne[N*2], idx;

vector<int>g[N*10];

int H[N*10], E[N*10], NE[N*10], IDX; 

inline void add(int a, int b)
{
	e[++idx] = b;ne[idx] = h[a];h[a] = idx;
}

inline void Add(int a, int b)
{
	E[++IDX] = b;NE[IDX] = H[a];H[a] = IDX;
}

void tarjan(int x)
{
	dfn[x] = low[x] = ++cur;
	stk[++top] = x;
	for(int i=h[x];i;i=ne[i])
	{
		int j = e[i];
		if(dfn[j]) low[x] = min(low[x],dfn[j]);
		else
		{
			tarjan(j);
			low[x] = min(low[x],low[j]);
			if(low[j]==dfn[x])
			{
				cnt++;
				int d = n + cnt, flg = 1;
				while(flg)
				{
					if(stk[top]==j) flg = 0;
					Add(stk[top],d);
					Add(d,stk[top]);
					top--;
				}
				Add(x,d);
				Add(d,x);
			}
		}
	}
}

int f[N*10], dep[N*10];

void dfs(int x, int fa)
{
	dep[x] = dep[fa] + 1;
	f[x] = fa;
	for(int i=H[x];i;i=NE[i])
	{
		int j = E[i];
		if(j==fa) continue;
		dfs(j,x);
	}
}

int mk[N];

inline void up(int &x)
{
	if(x>n)
	{
		for(int i=H[x];i;i=NE[i])
			mk[E[i]] = 1;
	}
	x = f[x];
}

int main()
{
	int m, i;
	cin>>n>>m>>a>>b>>c;
	while(m--)
	{
		int x, y;
		cin>>x>>y;
		add(x,y), add(y,x);
	}
	tarjan(1);
	dfs(1,0);
	int d1 = a, d2 = c;
	if(dep[d1]>dep[d2]) swap(d1,d2);
	while(dep[d1]<dep[d2])
		up(d2);
	while(d1!=d2)
	{
		up(d1);
		up(d2);
	}
	if(d1>n)
	{
		for(int i=H[d1];i;i=NE[i])
			mk[E[i]] = 1;
	}
	if(mk[b]) cout<<"Yes";
	else cout<<"No";
	return 0;
}return 0;
}
```

---

## 作者：WilliamFranklin (赞：0)

### 主要思路

一道经典网络流题。

首先建图：

因为除了 $B$ 点，其他点就只能被经过一次，所以拆点。在第 $i\left(i \neq B\right)$ 个点与 $i + n$ 之间连一条容量为 $1$ 的边，在 $B$ 与 $B + n$ 之间连一条容量为 $10^9$ 的边。

然后建立一个超级源点 $S$ 和超级汇点 $T$，在 $S$ 与 $B$ 之间连一条容量为 $10^9$ 的边，在 $A + n$ 与 $T$ 之间连一条容量为 $1$ 的边，在 $C + n$ 与 $T$ 之间连一条容量为 $1$ 的边。

最后，我们就只用求一下最大流，看一看值是不是等于 $2$ 即可。

废话不多说，上代码。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Tb, Ta) for(auto Ti = (Tb); Ti >= (Ta); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx) 
const int N = 2e5 + 5;
int h[N * 2], e[N * 6], ne[N * 6], f[N * 6], idx, n, m, a, b, c, S, T, cur[N * 2], d[N * 2];
bool vis[N * 2];
void add(int a, int b, int c) {
	e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx++;
	e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx++;
} 
bool bfs() {
	memset(d, -1, sizeof(d));
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push(S);
	vis[S] = 1, d[S] = 0, cur[S] = h[S];
	while (q.size()) {
		int t = q.front();
		q.pop();
		for (int i = h[t]; ~i; i = ne[i]) {
			int j = e[i];
			if (vis[j] || !f[i]) continue;
			d[j] = d[t] + 1, vis[j] = 1, cur[j] = h[j];
			if (j == T) return 1;
			q.push(j);
		}
	}
	return 0;
}
int dfs(int x, int limit) {
	if (x == T) return limit;
	int flow = 0;
	for (int i = cur[x]; (~i) && flow < limit; i = ne[i]) {
		int j = e[i];
		cur[x] = i;
		if (d[j] != d[x] + 1 || !f[i]) continue;
		int k = dfs(j, min(f[i], limit - flow));
		if (!k) d[j] = -1;
		f[i] -= k;
		f[i ^ 1] += k;
		flow += k;
	}
	return flow;
}
int dinic() {
	int ans = 0, flow;
	while (bfs()) while (flow = dfs(S, 1e9)) ans += flow;
	return ans;
}
int main() {
	memset(h, -1, sizeof(h));
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m >> a >> b >> c;
	For(i, 1, n) if (i != b) add(i, i + n, 1);
	add(b, b + n, 1e9);
	For(i, 1, m) {
		int a, b;
		cin >> a >> b;
		add(a + n, b, 1), add(b + n, a, 1);
	}
	S = 0, T = 2 * n + 1;
	add(S, b, 1e9), add(a + n, T, 1), add(c + n, T, 1);
	int ans = dinic();
	//cout << ans << endl;
	if (ans == 2) cout << "Yes";
	else cout << "No";
	return 0;
}
```

WilliamFranklin 温馨提醒您：

AT318，G 题最大流

边数要算好，不然满屏 T + WA

### 谢谢观看！

---

## 作者：User_Unauthorized (赞：0)

## 题意

给定一个 $N$ 个节点和 $M$ 条边组成的简单无向联通图，给定三个节点 $A,B,C$，求是否存在一条简单路径满足 $A \rightarrow B \rightarrow C$。

（$3 \le N, M \le 2 \times 10^5$）。

## 题解

**[$\tt{cnblogs}$](https://www.cnblogs.com/User-Unauthorized/p/solution-ABC318G.html)**

因为简单路径要求每个节点至多经过一次，故不存在合法的简单路径当且仅当存在一个割点同时存在于路径 $A \rightarrow B$ 和路径 $B \rightarrow C$ 上。故建立圆方树后跑两遍 $\tt{DFS}$ 即可，第一遍标记路径 $A \rightarrow B$ 上的点，第二遍检查路径 $B \rightarrow C$ 上是否有被标记且为割点的点。

总复杂度 $\mathcal{O}(N + M)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::vector<bool> bitset;

valueType N, M;
valueType A, B, C;

ValueVector dfn, low;
ValueMatrix G, tree, dcc;
bitset cut, path;
std::stack<valueType> S;

void tarjan(valueType x, valueType from) {
    static valueType time = 0;

    dfn[x] = low[x] = ++time;

    S.push(x);

    valueType son = 0;

    for (auto const &iter: G[x]) {
        if (iter == from)
            continue;

        if (!dfn[iter]) {
            ++son;

            tarjan(iter, x);

            low[x] = std::min(low[x], low[iter]);

            if (low[iter] >= dfn[x]) {
                cut[x] = true;

                dcc.emplace_back();
                dcc.back().emplace_back(x);

                int y;

                do {
                    y = S.top();
                    S.pop();
                    dcc.back().emplace_back(y);
                } while (y != iter);
            }
        } else {
            low[x] = std::min(low[x], dfn[iter]);
        }
    }

    if (from == 0 && son == 1)
        cut[x] = false;
}

void build() {
    for (valueType i = 0; i < dcc.size(); ++i) {
        valueType const x = N + i + 1;

        for (auto const &iter: dcc[i]) {
            tree[x].push_back(iter);
            tree[iter].push_back(x);
        }
    }
}

bool dfs(valueType x, valueType from, valueType TOP) {
    if (x == TOP)
        return path[x] = true;

    for (auto const &iter: tree[x]) {
        if (iter == from)
            continue;

        if (dfs(iter, x, TOP))
            return path[x] = true;
    }

    return path[x] = false;
}

bool check(valueType x, valueType from, valueType TOP, bool &result) {
    if (x == TOP)
        return true;

    for (auto const &iter: tree[x]) {
        if (iter == from)
            continue;

        if (check(iter, x, TOP, result)) {
            if (path[x] && cut[x])
                result = false;

            return true;
        }
    }

    return false;
}

int main() {
    std::cin >> N >> M;

    std::cin >> A >> B >> C;

    G.resize(N + 10);
    tree.resize(2 * N + 10);
    dfn.resize(N + 10, 0);
    low.resize(N + 10, 0);
    cut.resize(2 * N + 10, false);
    path.resize(2 * N + 10, false);

    for (valueType i = 0; i < M; ++i) {
        valueType u, v;

        std::cin >> u >> v;

        G[u].push_back(v);
        G[v].push_back(u);
    }

    tarjan(1, 0);

    build();

    dfs(A, 0, B);

    bool result = true;

    check(C, 0, B, result);

    if (result)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;
}
```

---

