# Case of Computer Network

## 题目描述

Andrewid the Android is a galaxy-known detective. Now he is preparing a defense against a possible attack by hackers on a major computer network.

In this network are $ n $ vertices, some pairs of vertices are connected by $ m $ undirected channels. It is planned to transfer $ q $ important messages via this network, the $ i $ -th of which must be sent from vertex $ s_{i} $ to vertex $ d_{i} $ via one or more channels, perhaps through some intermediate vertices.

To protect against attacks a special algorithm was developed. Unfortunately it can be applied only to the network containing directed channels. Therefore, as new channels can't be created, it was decided for each of the existing undirected channels to enable them to transmit data only in one of the two directions.

Your task is to determine whether it is possible so to choose the direction for each channel so that each of the $ q $ messages could be successfully transmitted.

## 说明/提示

In the first sample test you can assign directions, for example, as follows: $ 1→2 $ , $ 1→3 $ , $ 3→2 $ , $ 4→3 $ . Then the path for for the first message will be $ 1→3 $ , and for the second one — $ 4→3→2 $ .

In the third sample test you can assign directions, for example, as follows: $ 1→2 $ , $ 2→1 $ , $ 2→3 $ . Then the path for the first message will be $ 1→2→3 $ , and for the second one — $ 2→1 $ .

## 样例 #1

### 输入

```
4 4 2
1 2
1 3
2 3
3 4
1 3
4 2
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3 2 2
1 2
3 2
1 3
2 1
```

### 输出

```
No
```

## 样例 #3

### 输入

```
3 3 2
1 2
1 2
3 2
1 3
2 1
```

### 输出

```
Yes
```

# 题解

## 作者：关怀他人 (赞：13)

### CF 555E
#### Solution
首先将原图进行边双缩点，不难发现可以将$s$和$t$都在同一个边双里的询问忽略，因为可以通过给边双内的边定向使得其中任意两点都能互相到达。

于是在缩点后原图就变成了一颗树，那么限制$(s,t)$相当于将树上$s\to t$的路径上的边全部定向，具体可以通过树上差分计算每条边$(u,v)$被定向成$u\to v$的次数$a$和$v\to u$的次数$b$，最后只需dfs一遍判断每条边的$a$和$b$是否有一个为$0$即可。

#### Code
```cpp
int n,m,Q,len = 1,tim,colNum,tot;
int head[MAXN],vis[MAXN << 1],low[MAXN],dfn[MAXN],col[MAXN];
int dep[MAXN],f[MAXN][LOG],up[MAXN],down[MAXN],belong[MAXN];
vector<int> g[MAXN];

struct Edge{
	int to,next;
} e[MAXN << 1];

struct Query{
	int u,v;
} q[MAXN];

void add_edge(int u,int v){
    e[++len] = (Edge){v,head[u]};
    head[u] = len;
}

void tarjan(int u,int fa){
	dfn[u] = low[u] = ++tim;
	for(int i = head[u];i != -1;i = e[i].next){
		int v = e[i].to;
		if(v == fa) continue;
		if(!dfn[v]){
			tarjan(v,u);
			low[u] = min(low[u],low[v]);
			if(low[v] > dfn[u])
				vis[i] = vis[i ^ 1] = 1;
		}else
			low[u] = min(low[u],dfn[v]);
	}
}

void dfs1(int u){
	col[u] = colNum;
	for(int i = head[u];i != -1;i = e[i].next){
		int v = e[i].to;
		if(col[v] || vis[i]) continue;
		dfs1(v);
	}
}

void dfs2(int u,int fa){
	belong[u] = tot;
	dep[u] = dep[fa] + 1;
	f[u][0] = fa;
	for(int i = 1;i < LOG;i++)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for(auto v : g[u]){
		if(v == fa) continue;
		dfs2(v,u);
	}
}

int LCA(int u,int v){
	if(dep[u] < dep[v]) swap(u,v);
	for(int i = LOG - 1;i >= 0;i--){
		if(dep[f[u][i]] >= dep[v])
			u = f[u][i];
	}
	if(u == v) return u;
	for(int i = LOG - 1;i >= 0;i--){
		if(f[u][i] != f[v][i]){
			u = f[u][i];
			v = f[v][i];
		}
	}
	return f[u][0];
}

bool Check(int u,int fa){
	for(auto v : g[u]){
		if(v == fa) continue;
		if(!Check(v,u) || (up[v] && down[v]))
			return false;
		up[u] += up[v];
		down[u] += down[v];
	}
	return true;
}

int main(){
	memset(head,-1,sizeof(head));
	scanf("%d%d%d",&n,&m,&Q);
	for(int i = 1,u,v;i <= m;i++){
		scanf("%d%d",&u,&v);
		add_edge(u,v); add_edge(v,u);
	}
	for(int i = 1;i <= n;i++)
		if(!dfn[i]) tarjan(i,0);
	for(int i = 1;i <= n;i++)
		if(!col[i]) colNum++, dfs1(i);
	for(int i = 1;i <= n;i++){
		for(int j = head[i];j != -1;j = e[j].next){
			int v = e[j].to;
			if(col[i] < col[v]){
				g[col[i]].push_back(col[v]);
				g[col[v]].push_back(col[i]);
			}
		}
	}
	for(int i = 1;i <= colNum;i++)
		if(!belong[i]) tot++, dfs2(i,0);
	for(int i = 1,u,v;i <= Q;i++){
		scanf("%d%d",&u,&v);
		q[i] = (Query){col[u],col[v]};
	}
	for(int i = 1;i <= Q;i++){
		int u = q[i].u,v = q[i].v;	
		if(u == v) continue;
		if(belong[u] != belong[v]){
			printf("No\n");
			return 0;
		}
		int lca = LCA(u,v);
		up[u] += 1, up[lca] -= 1;
		down[v] += 1, down[lca] -= 1;
	}
	for(int i = 1;i <= colNum;i++){
		if(!f[i][0] && !Check(i,0)){
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
	return 0;
}
```

---

## 作者：Alex_Wei (赞：10)

### [CF555E Case of Computer Network](https://www.luogu.com.cn/problem/CF555E)

对于一个边双，我们总可以给其内部的边安排一个定向方式，使得其任何一个点都可以到达另外所有点。即 E-BCC 一定可以定向为 SCC。本质上是 **边双具有耳分解**。

证明：首先给出引理，对于一个强连通的点集 $S$，设有向路径 $P = u\to p_1 \to \cdots \to v$，若 $u, v\in S$，则将所有 $p_i$ 添加进 $S$ 集合后，$S$ 仍然强连通。这一点容易证明。

根据引理，对于一个边双 $G = (V, E)$，我们首先找到其中任意一个环 $P$，将其定向成有向环。设初始的强连通集为 $P$ 的点集。接下来，不断选取两端均属于 $S$ 的一条所有边均没有被定向的链 $C$，将其定向成有向链并将链上所有点加入 $S$。

$C$ 必然存在。考虑边 $(u, v)$ 满足 $u\in S$ 且 $v\notin S$。当 $S \neq V$ 时这样的边必然存在，否则 $G$ 不连通。从 $u$ 出发走到 $v$，最终必然会回到 $S$。因为 $G$ 边双连通所以除去 $(u, v)$ 这条边，$v$ 必然能回到 $u$，自然一定能回到 $S$。第一次回到 $S$ 时已经走过的路径就是一个合法的 $C$。

由于 $G$ 大小有限，所以上述过程最终一定结束，此时 $S = V$，即 $V$ 强连通。将还没有被定向的边随意定向，结论得证。

因此，我们先对原图边双缩点得到一棵树，如果 $s, t$ 不连通自然无解，否则，$s$ 所在边双 $G(s)$ 必须可达 $t$ 所在边双 $G(t)$，因此 $G(s)$ 到 $G(t)$ 的简单路径上所有边的定向已经确定。如果存在一条边的定向矛盾则无解，可以通过 LCA + 树上差分实现对一条链的标记。开两个差分数组分别记录当前点到它父亲的连边是否被钦定为向上或向下，若同时有值则无解。

时间复杂度为 $\mathcal{O}(m + (n + q)\log n)$，瓶颈在于求 LCA。使用四毛子可以做到线性。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int K = 18;
const int N = 2e5 + 5;
int n, m, q, cur, blk[N], lg[N];
vector<int> g[N], root;
vector<pair<int, int>> e[N];
int dn, dfn[N], low[N], top, stc[N], cn, col[N];
void form(int id) {for(int x = (cn++, 0); x != id; ) col[x = stc[top--]] = cn;}
void tarjan(int id, int eid) {
  dfn[id] = low[id] = ++dn, stc[++top] = id, blk[id] = cur;
  for(auto _ : e[id]) {
    if(_.second == eid) continue;
    int it = _.first;
    if(!dfn[it]) {
      tarjan(it, _.second), low[id] = min(low[id], low[it]);
      if(low[it] > dfn[id]) form(it);
    }
    else low[id] = min(low[id], dfn[it]);
  }
  if(!eid) form(id);
}
int dep[N], mi[K][N];
int get(int x, int y) {return dep[x] < dep[y] ? x : y;}
void dfs(int id, int ff) {
  dep[id] = dep[ff] + 1;
  mi[0][dfn[id] = ++dn] = ff;
  for(int it : g[id]) if(it != ff) dfs(it, id);
}
int lca(int u, int v) {
  if(u == v) return u;
  if((u = dfn[u]) > (v = dfn[v])) swap(u, v);
  int d = lg[v - (u++)];
  return get(mi[d][u], mi[d][v - (1 << d) + 1]);
}
int up[N], down[N];
void flush(int id, int ff) {
  for(int it : g[id]) if(it != ff) flush(it, id), up[id] += up[it], down[id] += down[it];
  if(up[id] && down[id]) puts("No"), exit(0);
}
int main() {
#ifdef ALEX_WEI
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif
  cin >> n >> m >> q;
  for(int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    e[u].push_back({v, i});
    e[v].push_back({u, i});
  }
  for(int i = 1; i <= n; i++) if(!dfn[i]) cur++, tarjan(i, 0);
  for(int i = 1; i <= n; i++)
    for(auto it : e[i])
      if(col[i] != col[it.first])
        g[col[i]].push_back(col[it.first]);
  dn = 0;
  for(int i = 1; i <= cn; i++) if(!dep[i]) dfs(i, 0), root.push_back(i);
  for(int i = 2; i <= cn; i++) lg[i] = lg[i >> 1] + 1;
  for(int i = 1; i <= lg[cn]; i++)
    for(int j = 1; j + (1 << i) - 1 <= cn; j++)
      mi[i][j] = get(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]);
  for(int i = 1; i <= q; i++) {
    int s, t;
    scanf("%d%d", &s, &t);
    if(blk[s] != blk[t]) puts("No"), exit(0);
    if((s = col[s]) == (t = col[t])) continue; // add this line
    int d = lca(s, t);
    up[s]++, up[d]--, down[t]++, down[d]--;
  }
  for(int it : root) flush(it, 0);
  puts("Yes");
  return cerr << "Time: " << clock() << endl, 0;
}
/*
2022/5/26
start coding at 7:03
finish debugging at 7:20
*/
```

---

## 作者：RainAir (赞：5)

## 题目大意
给你一个 $n$ 个点 $m$ 条边的图，以及 $q$ 对点 $(s,t)$，让你分配 $m$ 条边的方向。问是否存在一种分配方案，使每对点的 $s$ 能走到 $t$。 
其中 $ 1\leq n,m,q \leq 2*10^5$

## 题解
我们考虑一下边双联通分量的性质：同一边双联通分量的任意两点至少存在两条不存在同一条边的路径。

那么我们很自然的把这些边双缩成一个点，这样这个无向图就变成了树。

考虑每一对点 $(s,t)$，如果它们在同一个边双里那么肯定存在一种方案使得满足这对限制；如果不在同一个边双里就可以看成是树上的两个点，于是我们只需要解决这个题目在树上怎么做就可以了。

我们对于每个节点 $i$ ，定义 $up_i$ 和 $down_i$ 两个标记，运用树上差分的方式来判断一下是否有矛盾就可以了。

时间复杂度瓶颈在于求 $lca$ 的复杂度。
```c++
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 300000+5;
struct Edge{
    int to,next;
}e1[MAXN<<1],e2[MAXN<<1];
int head1[MAXN],head2[MAXN],cnt1 = 1,cnt2 = 1,bel[MAXN];
int low[MAXN],dfn[MAXN],st[MAXN],top,block;
int N,M,Q;int f[MAXN][50],dep[MAXN],par[MAXN],up[MAXN],down[MAXN];
bool ins[MAXN];

inline int find(int x){
    return x == par[x] ? x : par[x] = find(par[x]);
}

inline bool Union(int x,int y){
    int fx = find(x),fy = find(y);
    if(fx == fy) return false;
    par[fy] = fx;return true;
}

inline void add1(int u,int v){
    e1[++cnt1] = (Edge){v,head1[u]};head1[u] = cnt1;
}

inline void add2(int u,int v){
    e2[++cnt2] = (Edge){v,head2[u]};head2[u] = cnt2;
}
//int ts = 0;
inline void dfs1(int v,int fa){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;st[++top] = v;ins[v] = true;
    for(int i = head1[v];i;i = e1[i].next){
        if(i != fa){
            // DEBUG(e1[i].to);
            if(!dfn[e1[i].to]){
                dfs1(e1[i].to,i^1);
                low[v] = std::min(low[v],low[e1[i].to]);
            }
            else if(ins[e1[i].to]) low[v] = std::min(low[v],dfn[e1[i].to]);
        }
    }
    if(dfn[v] != low[v]) return;
    block++;int r = -1;
    while(r != v){
        r = st[top--];ins[r] = false;bel[r] = block;
    }
}

inline void rebuild(){
    FOR(v,1,N){
        for(int i = head1[v];i;i = e1[i].next){
            if(bel[v] != bel[e1[i].to]){
                if(Union(bel[v],bel[e1[i].to]))
                    add2(bel[v],bel[e1[i].to]),
                    add2(bel[e1[i].to],bel[v]);
            }
        }
    }
}

float log2N;

void dfs2(int v,int fa){
    FOR(i,1,log2N){
        if(dep[v] <= (1<<i)) break;
        f[v][i] = f[f[v][i-1]][i-1];
    }
    for(int i = head2[v];i;i = e2[i].next){
        if(e2[i].to == fa) continue;
        //DEBUG(v);DEBUG(e2[i].to);
        dep[e2[i].to] = dep[v] + 1;
        f[e2[i].to][0] = v;
        dfs2(e2[i].to,v);
    }
}

int lca(int x,int y){
    int dx = dep[x],dy = dep[y];
    if(dx != dy){
        if(dx < dy) std::swap(x,y),std::swap(dx,dy);
        int d = dx-dy;
        FOR(i,0,log2N) if((1<<i)&d) x = f[x][i];
    }
    if(x == y) return x;
    ROF(i,log2N,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

bool ans;

void dfs3(int v){
    if(!ans) return;
    for(int i = head2[v];i;i = e2[i].next){
        if(dep[e2[i].to] > dep[v]){
            dfs3(e2[i].to);
            if(!ans) return;
            up[v] += up[e2[i].to];down[v] += down[e2[i].to];
        }
    }
    if(up[v] && down[v]) ans = false;
}

int main(){
    scanf("%d%d%d",&N,&M,&Q);
    FOR(i,1,N) par[i] = i;
    FOR(i,1,M){
        int u,v;scanf("%d%d",&u,&v);
        add1(u,v);add1(v,u);
    }
    FOR(i,1,N) if(!dfn[i]) dfs1(i,0);
    //FOR(u,1,N) printf("%d %d\n",low[u],dfn[u]);
    rebuild();log2N = log2(1.0*block);CLR(f,-1);
    FOR(v,1,block){
        if(find(v) == v) dep[v] = 1,dfs2(v,0);
    }
    // FOR(i,1,N) printf("%d ",dep[i]);puts("");
    ans = true;
    FOR(i,1,Q){
        int u,v;scanf("%d%d",&u,&v);
        u = bel[u],v = bel[v];
        if(u == v) continue;
        if(find(u) != find(v)){
            ans = false;break;
        }
        int l = lca(u,v);// DEBUG(l);
        up[u]++;down[v]++;up[l]--;down[l]--;
    }
    if(ans) FOR(i,1,block){
        if(i == find(i)) dfs3(i);
        if(!ans) break;
    }
    //FOR(i,1,N) printf("%d %d\n",up[i],down[i]);
    puts(ans ? "Yes" : "No");
    return 0;
}
```

---

## 作者：RQ。。。 (赞：4)

# T1 CF555E Case of Computer Network

给定一张 n 个点 m 条边的无向图。
给定 q 组有向点对(s,t)。
询问是否存在使得所有 s 都能到达 t 的无向图中每条边的定向方案。
$n,m,q \le 2 \times 10^5$



**solution**

其实吧，这题没有想象中那么难。

先$Tarjan$ 求割边，缩点，然后得到一棵树。

对于一个询问$(u  , v)$。

若u，v在同一个边双中一定存在一种方法使得这个边双的中的点两两互达，(边双中有环嘛。。)

若不在一个联通块里，(不在一棵树里)，那么肯定无解。

若都在一个树上就，将这条路劲上的边都打上一个标记，即可，具体实现可以用树上差分的方法。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
inline int read()
{
	register int x = 0 , f = 0; register char c = getchar();
	while(c < '0' || c > '9') f |= c == '-' , c = getchar();
	while(c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48) , c = getchar();
	return f ? -x : x;
}
int n , m , q , cnt = 1 , dfn_id , col_id , tag_id;
int head[N] , dfn[N] , vis[N << 1] , low[N] , col[N] , tag[N] , d[N] , s1[N] , s2[N] , f[N][20];
vector<int> G[N];
struct edge { int v , nex; }e[N << 1];
inline void add(int u , int v) { e[++cnt].v = v; e[cnt].nex = head[u]; head[u] = cnt; }

void Tarjan(int x , int f)
{
	dfn[x] = low[x] = ++dfn_id;
	for(int i = head[x] , v; i ; i = e[i].nex) if(i != f)
	{
		v = e[i].v;
		if(!dfn[v]) 
		{
			Tarjan(v , i ^ 1) , low[x] = min(low[x] , low[v]);
			if(low[v] > dfn[x]) vis[i] = vis[i ^ 1] = 1;
		}
		else low[x] = min(low[x] , dfn[v]);
	}
}

void dfs1(int x)
{
	col[x] = col_id;
	for(int i = head[x] ; i ; i = e[i].nex) if(!col[e[i].v] && !vis[i]) dfs1(e[i].v);
}

void dfs2(int x)
{
	tag[x] = tag_id;
	for(auto v : G[x]) if(v != f[x][0]) 
	{
		f[v][0] = x; d[v] = d[x] + 1;
		for(int i = 1 ; i < 20 ; ++i) f[v][i] = f[f[v][i-1]][i-1];
		dfs2(v);
	}
}

int LCA(int x , int y)
{
	if(d[x] < d[y]) swap(x , y);
	for(int i = 19 ; ~i ; --i) if(d[f[x][i]] >= d[y]) x = f[x][i];
	if(x == y) return x;
	for(int i = 19 ; ~i ; --i) if(f[x][i] != f[y][i]) x = f[x][i] , y = f[y][i];
	return f[x][0];
}

bool check(int x)
{
	for(auto v : G[x]) if(v != f[x][0])
	{
		if(!check(v) || (s1[v] && s2[v])) return false;
		s1[x] += s1[v]; s2[x] += s2[v];
	}
	return true;
}

int main()
{
	n = read(); m = read(); q = read();
	for(int i = 1 , u , v; i <= m ; ++i) u = read() , v = read() , add(u , v) , add(v , u);
	for(int i = 1 ; i <= n ; ++i) if(!dfn[i]) Tarjan(i , -1);
	for(int i = 1 ; i <= n ; ++i) if(!col[i]) col_id++ , dfs1(i);
	for(int i = 1 ; i <= n ; ++i) for(int j = head[i] ; j ; j = e[j].nex) if(col[i] < col[e[j].v]) G[col[i]].push_back(col[e[j].v]) , G[col[e[j].v]].push_back(col[i]);
	for(int i = 1 ; i <= col_id ; ++i) if(!tag[i]) tag_id++ , d[i] = 1 , dfs2(i);
	for(int i = 1 , u , v ; i <= q ; ++i)
	{
		u = read(); v = read(); u = col[u]; v = col[v]; if(u == v) continue;
		if(tag[u] != tag[v]) return puts("No") , 0;
		int p = LCA(u , v);
		s1[u]++; s1[p]--; s2[v]++; s2[p]--;
	}
	for(int i = 1 ; i <= col_id ; ++i) if(d[i] == 1 && !check(i)) return puts("No") , 0;
	puts("Yes");
	return 0;	
}
```



---

## 作者：xht (赞：4)

> [CF555E Case of Computer Network](https://codeforc.es/contest/555/problem/E)

## 题意

- 给定一张 $n$ 个点 $m$ 条边的无向图。
- 给定 $q$ 组有向点对 $(s, t)$。
- 询问是否存在**使得所有 $s$ 都能到达 $t$** 的无向图中每条边的定向方案。
- $n,m,q \le 2 \times 10^5$。

## 题解

先求边双，缩点变成森林。

判定时先求 lca，树上差分一下即可，时间复杂度 $\mathcal O(n \log n)$。

## 代码

```cpp
const int N = 2e5 + 7;
int n, m, q;
int h[N], e[N<<1], t[N<<1], p = 1;
int dfn[N], low[N], num;
int b[N<<1], c[N], k;
int hc[N], ec[N<<1], tc[N<<1], pc = 1;
int v[N], w, f[N][20], d[N], g1[N], g2[N];

inline void add(int x, int y, int z = 1) {
	e[++p] = y;
	t[p] = h[x];
	h[x] = p;
	if (z) add(y, x, 0);
}

void tarjan(int x, int f) {
	dfn[x] = low[x] = ++num;
	for (int i = h[x]; i; i = t[i]) {
		if (i == f) continue;
		int y = e[i];
		if (dfn[y]) low[x] = min(low[x], dfn[y]);
		else {
			tarjan(y, i ^ 1), low[x] = min(low[x], low[y]);
			if (low[y] > dfn[x]) b[i] = b[i^1] = 1;
		}
	}
}

void dfs(int x) {
	c[x] = k;
	for (int i = h[x]; i; i = t[i]) {
		if (b[i]) continue;
		int y = e[i];
		if (c[y]) continue;
		dfs(y);
	}
}

inline void addc(int x, int y, int z = 1) {
	ec[++pc] = y;
	tc[pc] = hc[x];
	hc[x] = pc;
	if (z) addc(y, x, 0);
}

void dfsc(int x) {
	v[x] = w;
	for (int i = hc[x]; i; i = tc[i]) {
		int y = ec[i];
		if (y == f[x][0]) continue;
		f[y][0] = x, d[y] = d[x] + 1;
		for (int j = 0; f[y][j]; j++)
			f[y][j+1] = f[f[y][j]][j];
		dfsc(y);
	}
}

inline int lca(int x, int y) {
	if (d[x] > d[y]) swap(x, y);
	for (int i = 19; ~i; i--)
		if (d[f[y][i]] >= d[x]) y = f[y][i];
	if (x == y) return x;
	for (int i = 19; ~i; i--)
		if (f[x][i] ^ f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}

bool dfspd(int x) {
	for (int i = hc[x]; i; i = tc[i]) {
		int y = ec[i];
		if (y == f[x][0]) continue;
		if (!dfspd(y) || (g1[y] && g2[y])) return 0;
		g1[x] += g1[y], g2[x] += g2[y];
	}
	return 1;
}

int main() {
	rd(n), rd(m), rd(q);
	for (int i = 1, x, y; i <= m; i++)
		rd(x), rd(y), add(x, y);
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) tarjan(i, 0);
	for (int i = 1; i <= n; i++)
		if (!c[i]) ++k, dfs(i);
	for (int x = 1; x <= n; x++)
		for (int i = h[x]; i; i = t[i]) {
			int y = e[i];
			if (c[x] >= c[y]) continue;
			addc(c[x], c[y]);
		}
	for (int i = 1; i <= k; i++)
		if (!v[i]) ++w, d[i] = 1, dfsc(i);
	for (int i = 1, x, y; i <= q; i++) {
		rd(x), rd(y), x = c[x], y = c[y];
		if (x == y) continue;
		if (v[x] != v[y]) return prints("No"), 0;
		int z = lca(x, y);
		++g1[x], --g1[z], ++g2[y], --g2[z];
	}
	for (int i = 1; i <= n; i++)
		if (d[i] == 1 && !dfspd(i)) return prints("No"), 0;
	prints("Yes");
	return 0;
}
```

---

## 作者：wrpwrp (赞：3)

```cpp
题目大意：
	给你一个n个点m条边的无向图和q个有序点对，问是否可以找到一种边的定向方式使得任意一对(s,t),s可以到t
数据范围:
	n,m,q<=2e5
解题过程：
	其实如果这是一颗树的话很好搞，把s到lca(s,t) 向上连，lca(s,t)到t向下连即可(然而事情并不是这样子的...)
	我们考虑什么样的情况是一定可行的呢？每两个点之间都有两条以上的路径，那就可以一边向前，一边向后，绝对可以，
	也就是求双联通分量以内是一定可以的，所以考虑缩点。惊奇的发现得到了一片森林，那不就好搞了嘛！
	特判在不同树上的情况，直接在缩点的时候暴力搞定就行。在同一棵树上可以树剖/树上差分维护。最后一遍dfs判定标记是否重复就行了
	那么现在问题就是怎没求双联通分量了...我并不会诶....
	（使用现场学习算法即可）
	upd:代码真难调啊emmmm

```

```cpp
#include <cstdio>

#define R register
const int MAXN=2e5+10;
const int MAXM=MAXN<<1;

inline int read()
{
	#define C getchar()
	char a=C;int x=0,f=1;
	for(;a>'9'||a<'0';a=C) if(a=='-') f=-1;
	for(;a>='0'&&a<='9';a=C) x=x*10+a-'0';
	return x*f;
	#undef C
}

inline int min(int x,int y) { return x<y?x:y;}

int n,m,q;
struct edge
{
	int fr,to,next;
}e1[MAXM];

struct Edge
{
	int to,next;
}e2[MAXM];
int head1[MAXN],cnt1=1;
int head2[MAXN],cnt2=1;

inline void add1(int x,int y)
{
	cnt1++;
	e1[cnt1].fr=x;
	e1[cnt1].to=y;
	e1[cnt1].next=head1[x];
	head1[x]=cnt1;
}

inline void add2(int x,int y)
{
	cnt2++;
	e2[cnt2].to=y;
	e2[cnt2].next=head2[x];
	head2[x]=cnt2;
}

int dfn[MAXN],low[MAXN];
int col[MAXN],num;
int st[MAXN],tp;
int vis[MAXN];
int tot;
int be[MAXN];

inline void tarjan(int x,int fr)
{
	dfn[x]=low[x]=++num;
	col[x]=col[0];
	st[++tp]=x,vis[x]=1;
	for(R int i=head1[x];i;i=e1[i].next)
	{
		if((i^1)==fr) continue;
		int y=e1[i].to;
		if(!dfn[y])
		{
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
		}
		else
			if(vis[y]) low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x])
	{
		int y=0;tot++;
		while(y!=x)
		{
			y=st[tp];tp--;
			be[y]=tot;vis[y]=0;
		}
	}
}

int dep[MAXN],fa[MAXN],top[MAXN],siz[MAXN],son[MAXN];

inline void dfs1(int x,int fx)
{
	dep[x]=dep[fx]+1;
	fa[x]=fx;
	siz[x]=1;
	for(R int i=head2[x];i;i=e2[i].next)
	{
		int y=e2[i].to;
		if(y==fx) continue;
		dfs1(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]]) son[x]=y;
	}
}

inline void dfs2(int x,int topx)
{
	top[x]=topx;
	if(son[x]) dfs2(son[x],topx);
	for(R int i=head2[x];i;i=e2[i].next)
	{
		int y=e2[i].to;
		if(y==fa[x]||y==son[x]) continue;
		dfs2(y,y);
	}
}

inline int lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]>dep[top[y]])
			x=fa[top[x]];
		else
			y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}

int up[MAXN],down[MAXN];
int tag[MAXN];

inline void dfs3(int x)
{
	tag[x]=1;
	for(R int i=head2[x];i;i=e2[i].next)
	{
		int y=e2[i].to;
		if(y==fa[x]) continue;
		dfs3(y);
		up[x]+=up[y];
		down[x]+=down[y];
	}
}

int main()
{
	n=read();m=read();q=read();
	for(R int i=1;i<=m;i++)
	{
		int x=read();int y=read();
		add1(x,y);add1(y,x);
	}
	for(R int i=1;i<=n;i++)
		if(!dfn[i])
		{
			col[0]++;
			tarjan(i,0);
		}
	for(R int i=2;i<=cnt1;i+=2)
	{
		int x=e1[i].fr;
		int y=e1[i].to;
		if(be[x]==be[y]) continue;
		add2(be[x],be[y]);
		add2(be[y],be[x]);
	}
	for(R int i=1;i<=n;i++)
		if(!dep[i])
		{
			dfs1(i,0);
			dfs2(i,i);
		}
	for(R int i=1;i<=q;i++)
	{
		int x=read(),y=read();
		if(col[x]!=col[y])
		{
			printf("No\n");return 0;
		}
		x=be[x],y=be[y];
		int LCA=lca(x,y);
		up[x]++;up[LCA]--;
		down[y]++;down[LCA]--;
	}
	for(R int i=1;i<=n;i++)
		if(!tag[i]) dfs3(i);
	for(R int i=1;i<=n;i++)
		if(up[i]&&down[i])
		{
			printf("No\n");
			return 0;
		}
	printf("Yes\n");
	return 0;
}
```


---

## 作者：81179332_ (赞：3)

对于一个边双连通分量中的点，显然我们可以调整边的方向使得分量中任意两点间互相可达

所以我们首先边双缩点，然后忽略掉在同一边双分量的要求

缩点后形成了一棵树，不在同一棵树的要求是不可能满足的，对于剩下的要求，我们在树上差分即可

```cpp
//timeuse:25min
const int N = 200010,M = N;
int q;int s[N],t[N];
struct Tree
{
	int n;EE(1);
	int fa[N][20],dep[N];
	int col_id,col[N];
	void dfs(int u)
	{
		col[u] = col_id;
		for(int i = 1;i < 20;i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
		for(int i = head[u],v;i;i = e[i].nxt) if((v = e[i].to) != fa[u][0])
			fa[v][0] = u,dep[v] = dep[u] + 1,dfs(v);
	}
	int lca(int x,int y)
	{
		if(dep[x] < dep[y]) swap(x,y);
		int h = dep[x] - dep[y];for(int i = 0;i < 20;i++) if(h & (1 << i)) x = fa[x][i];
		if(x == y) return x;
		for(int i = 19;~i;i--) if(fa[x][i] != fa[y][i]) x = fa[x][i],y = fa[y][i];
		return fa[x][0];
	}
	int s1[N],s2[N];
	bool check(int u)
	{
		for(int i = head[u],v;i;i = e[i].nxt) if((v = e[i].to) != fa[u][0])
		{
			if(!check(v) || s1[v] && s2[v]) return 0;
			s1[u] += s1[v],s2[u] += s2[v];
		}return 1;
	}
	void solve()
	{
		for(int i = 1;i <= n;i++) if(!col[i]) col_id++,dep[i] = 1,dfs(i);
		for(int i = 1;i <= q;i++)
		{
			int u = s[i],v = t[i];
			if(col[u] != col[v]) { puts("No");return; }
			int z = lca(u,v);
			s1[u]++,s1[z]--,s2[v]++,s2[z]--;
		}
		for(int i = 1;i <= n;i++) if(dep[i] == 1 && !check(i)) { puts("No");return; }
		puts("Yes");
	}
}T;
struct Graph
{
	int n,m;
	EE(1);bool vis[M << 1];
	int dfn[N],low[N],idx;
	void Tarjan(int u,int fa)
	{
		dfn[u] = low[u] = ++idx;
		for(int i = head[u];i;i = e[i].nxt) if(i != fa)
		{
			int v = e[i].to;
			if(!dfn[v])
			{
				Tarjan(v,i ^ 1),low[u] = min(low[u],low[v]);
				if(low[v] > dfn[u]) vis[i] = vis[i ^ 1] = 1;
			}
			else low[u] = min(low[u],dfn[v]);
		}
	}
	int col_id,col[N];
	void dfs(int u)
	{
		col[u] = col_id;
		for(int i = head[u],v;i;i = e[i].nxt) if(!col[v = e[i].to] && !vis[i]) dfs(v);
	}
	void build()
	{
		n = read(),m = read(),q = read();
		for(int i = 1;i <= m;i++) add_edge(read(),read());
		for(int i = 1;i <= n;i++) if(!dfn[i]) Tarjan(i,-1);
		for(int i = 1;i <= n;i++) if(!col[i]) col_id++,dfs(i);
		T.n = col_id;
		for(int u = 1;u <= n;u++) for(int i = head[u],v;i;i = e[i].nxt)
			if(col[u] < col[v = e[i].to]) T.add_edge(col[u],col[v]);
		for(int i = 1;i <= q;i++)
		{
			s[i] = col[read()],t[i] = col[read()];
			if(s[i] == t[i]) i--,q--;
		}
	}
}G;
int main()
{
	G.build(),T.solve();
	return 0;
}
```

---

## 作者：Rainy_chen (赞：3)

### 题目翻译
给一张无向图，不保证联通。  
之后给出$q$组询问，每组询问形如$u,v$。  

你需要将每条边变为有向边，然后给出是否存在一种方案使得q组询问的u都能到达v。

### 题解
虽然写的很长，但是确实是一道比较板子的题。

---

#### 前置知识 - 边双联通分量
边双联通图是指一个没有割边的图。  
于是边双联通分量就是原图中的某个极大边双联通子图。

如果需要求出一张图的边双，可以先求出所有的割边，然后剩下的点各自形成联通块即是边双。

当然也可以使用tarjan算法去直接求边双，具体实现较为简单，可以直接参考代码。

边双的一个十分优良的性质是其中任何两个点之间至少有两条不同的路径。

---

考虑上述所说的边双性质，如果两点之间有两条不同的路径，那么不妨将他们分别设为正向边与反向边，于是这个边双就形成了一个环。

于是我们知道在边双中一定存在满足题意的方案。

所以我们将所有的边双缩点，于是得到了一片森林。

在树上很容易满足题目中要求的询问，只需要将$u \to lca$设为正向边，将$v\to lca$设为反向边即可。

我们考虑在什么情况下无法满足某组询问
- 不连通。 两个点在不同的树中，记录一下每个点属于哪棵树即可解决。
- 与其他询问冲突。 两个点到lca的路径上的某条边与将要设置的方向不同。

考虑到在设置边的方向的时候是设置的树上一条链的所有边，我们可以把边的标记转移到点上后采用树上差分的方法维护标记。 

具体而言，对于某个标记$u\to v$，我们只需要`tag[u]++;tag[v]--;`，之后只需要dfs一遍，从叶子节点递归向前累加标记，就可以求出每一个点上获得的标记。

如果某个点有两种标记（正向边和反向边），那么我们就知道这个点对应的边出现了冲突，于是原问题无解。  

于是对于每组询问先判是否连通，然后打标记，最后dfs一遍判断是否合法即可。
  
然后你发现你至少需要写三个板子，也就是缩点，lca和树上差分，这就导致这道题的代码比较长。。。

```cpp
#include<bits/stdc++.h>

using namespace std;
typedef int int_t;

int_t read(){
    int_t x = 0,w = 1;char ch = 0;
    while(!isdigit(ch)) {ch = getchar(); if(ch == '-') w = -1;}
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return x * w;
}

const int_t maxn = 200010;

struct E{
    int_t to;
    E* nxt;
    E* rev;
    E(int_t to,E* nxt):to(to),nxt(nxt){}
};

E* head[maxn];
E* nhead[maxn];
int_t col[maxn],dfn[maxn],low[maxn],cols,son[maxn],fa[maxn],siz[maxn],dep[maxn],top[maxn],tag1[maxn],tag2[maxn],bel[maxn];
bool instk[maxn],vis[maxn];

void tarjan(int_t rt,E* frm,int_t from){
    static stack<int_t> stk;
    static int_t cnt = 0;
    bel[rt] = from; instk[rt] = true; dfn[rt] = low[rt] = ++ cnt;
    stk.push(rt);
    for(E* e = head[rt];e;e=e -> nxt){
        if(e == frm) continue;
        if(!dfn[e -> to]) tarjan(e -> to,e -> rev,from),low[rt] = min(low[rt],low[e -> to]);
        else if(instk[e -> to]) low[rt] = min(low[rt],dfn[e -> to]);
    }
    if(dfn[rt] == low[rt]){
        ++cols;
        while(true){
            int_t r = stk.top();stk.pop();
            col[r] = cols;
            if(r == rt) break;
        }
    }
}

void dfs1(int_t rt){
    siz[rt] = vis[rt] = 1;
    for(E* e = nhead[rt];e;e = e -> nxt){
        if(vis[e -> to]) continue;
        fa[e -> to] = rt;
        dep[e -> to] = dep[rt] + 1;
        dfs1(e -> to);
        siz[rt] += siz[e -> to];
        if(siz[e -> to] > siz[son[rt]]) son[rt] = e -> to;
    }
}

void dfs2(int_t rt,int_t top){
    ::top[rt] = top; vis[rt] = true;
    if(son[rt]) dfs2(son[rt],top);
    for(E* e = nhead[rt];e;e = e -> nxt) if(!vis[e -> to]) dfs2(e -> to,e -> to);
}

int_t LCA(int_t u,int_t v){
    while(top[u] != top[v])
        if(dep[top[u]] > dep[top[v]]) u = fa[top[u]];
        else v = fa[top[v]];
    return dep[u] > dep[v] ? v : u;
}

bool dfs(int_t rt){
    vis[rt] = true;
    for(E* e = nhead[rt];e;e = e -> nxt){
        if(vis[e -> to]) continue;
        if(!dfs(e -> to)) return false;
        tag1[rt] += tag1[e -> to];
        tag2[rt] += tag2[e -> to];
    }
    return !tag1[rt] || !tag2[rt];
}

int main(){
    int_t n = read(),m = read(),q = read();
    while(m--){
        int_t u = read(),v = read();
        head[u] = new E(v,head[u]); 
        head[v] = new E(u,head[v]);
        head[u] -> rev = head[v];
        head[v] -> rev = head[u];
    }
    for(int_t i=1;i<=n;i++) if(!dfn[i]) tarjan(i,0,i);
    for(int_t i=1;i<=n;i++)
        for(E* e = head[i];e;e = e -> nxt)  
            if(col[i] != col[e -> to])
                nhead[col[i]] = new E(col[e -> to],nhead[col[i]]), nhead[col[e -> to]] = new E(col[i],nhead[col[e -> to]]);
    for(int_t i=1;i<=cols;i++) if(!siz[i]) dfs1(i);
    memset(vis,0,sizeof vis);
    for(int_t i=1;i<=cols;i++) if(i==bel[i]) dfs2(i,i);
    while(q--){
        int_t s = read(),t = read();
        if(bel[s] != bel[t]){puts("No");return 0;}
        s = col[s],t = col[t];
        if(s == t) continue;
        int_t lca = LCA(s,t);
        tag1[s]++;tag2[t]++;tag1[lca]--;tag2[lca]--;
    }
    memset(vis,0,sizeof(vis));
    for(int_t i=1;i<=cols;i++) if(bel[i] == i) if(!dfs(i)){puts("No");return 0;}
    puts("Yes");
}
```

---

## 作者：Piwry (赞：2)

这里来一个结尾 lct 的做法

---

一开始先是双连通分量缩点变成一棵树，之后在树上选定边的方向。

正解应该是用树上差分，但由于我最近刚好做了些 lct 就（无脑地）想到用 lct 维护这棵树。

我们考虑给边建点，并维护一个值表示边的状态。当值分别为：

- `[-1]` 表示未给定状态
- `[0]` 表示这个点原来不是边，不需要给定状态
- `[1]` 表示这条边向根走
- `[2]` 表示这条边向叶走

但 lct 维护的树往往根是不断变化的，因此我们要随着根的变化维护边的状态。发现只有在换根操作时，**从原来根到新根**的路径会被影响，因此只要在处理 rev（“翻转深度”）标签的同时维护边状态就行了。

至于检测违法的情况，只要在给边赋值时同时检查即可（如果将 `1` 改为 `2` 或反之就将一个全局的标记改变）。**同时最后要查询每个点以保证标记清空。**

这样我们就可以愉快地套 lct 做这道题了。但由于 lct 最后的最坏复杂度（取决于缩点情况）可能达到 $O(qlog(n)^2)$，想要过后面的大数据是基本不可能的（[卡在点36](https://codeforces.com/contest/555/submission/80559267)）。

（但个人认为这种边处理方式还是挺具有**代表性**的，于是才写了这篇题解（

---

### CODE

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using std::min;

const int MAXN =4e5+50;

/*------------------------------Tarjan------------------------------*/

int n, m, CNT, COL;
int first[MAXN], col[MAXN], dfn[MAXN], low[MAXN];
int stk[MAXN], tot;

struct edge{
	int net, from, to;
	bool isbge;
}e[MAXN];

void tarjan(int u, int edg =-1){
	stk[tot++] =u;
	low[u] =dfn[u] =++CNT;
	edge *E;
	for(int l =first[u]; l != -1; l =E->net){
		E =&e[l];
		if(!dfn[E->to]){
			tarjan(E->to, l), low[u] =min(low[u], low[E->to]);
			if(low[E->to] > dfn[u]) E->isbge =e[l^1].isbge =1;
		}
		else if((l^1) != edg) low[u] =min(low[u], dfn[E->to]);
	}
	if(low[u] == dfn[u]){
		++COL;
		do col[stk[--tot]] =COL; while(stk[tot] != u);
	}
}

inline void addedge(int u, int v, int i){
	edge &E1 =e[i<<1], &E2 =e[(i<<1)|1];
	E1.net =first[u], E1.from =u, E1.to =v, first[u] =i<<1;
	E2.net =first[v], E2.from =v, E2.to =u, first[v] =(i<<1)|1;
}

/*------------------------------LCT------------------------------*/

int f[MAXN], c[2][MAXN], val[MAXN], cache[MAXN];
bool rev[MAXN], lzy[MAXN], WRONG;

inline bool isroot(int x){ int y =f[x]; return (c[0][y] != x && c[1][y] != x) || y == 0; }

inline bool get(int x){ return c[1][f[x]] == x; }

inline void pushdown(int x){
	if(x == 0) return;
	if(rev[x]){
		rev[c[0][x]] ^=1, rev[c[1][x]] ^=1;
		c[0][x] ^=c[1][x] ^=c[0][x] ^=c[1][x];
		if(val[x] == 1) val[x] =2;
		else if(val[x] == 2) val[x] =1;
		if(cache[x] == 1) cache[x] =2;
		else if(cache[x] == 2) cache[x] =1;
		rev[x] =0;
	}
	if(lzy[x]){
		int lc =c[0][x], rc =c[1][x];
		pushdown(lc), pushdown(rc);
		lzy[lc] =lzy[rc] =1;
		cache[lc] =cache[rc] =cache[x];
		if(val[x] != -1 && val[x] != 0 && cache[x] != val[x]) WRONG =1;
		if(val[x] == -1) val[x] =cache[x];
		lzy[x] =0;
	}
}

inline void rotate(int x){
	bool r =get(x), r2 =get(f[x]);
	int y =f[x], z =f[y], a =c[!r][x];
	f[x] =z; if(!isroot(y)) c[r2][z] =x;
	f[y] =x; c[!r][x] =y;
	f[a] =y; c[r][y] =a;
}

inline void pushall(int x){
	if(!isroot(x)) pushall(f[x]);
	pushdown(x);
}

inline void splay(int x){
	pushall(x);
	for(; !isroot(x); rotate(x)){
		int y =f[x];
		if(!isroot(y)) rotate((get(y) == get(x)) ? y : x);
	}
}

inline void access(int x){
	for(int pre =0; x; pre =x, x =f[x]){
		splay(x);
		c[1][x] =pre;
	}
}

inline void setroot(int x){
	access(x), splay(x);
	rev[x] =1;
}

inline void link(int x, int y){
	setroot(x);
	f[x] =y;
	splay(y);
}

inline void updata(int x, int y){/*x to y*/
	setroot(x), access(y), splay(y);/*1up 2 down*/
	cache[y] =2, lzy[y] =1;
}

inline void query(int x){
	access(x), splay(x);
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char cc =getchar();
	while(cc < '0' || cc > '9') cc =getchar();
	while(cc >= '0' && cc <= '9') x = (x<<3) + (x<<1) + (48^cc), cc =getchar();
	return x;
}

int main(){
	n =read(), m =read(); int Q =read();
	memset(first, -1, sizeof(first));
	for(int i =0; i < m; ++i) addedge(read(), read(), i);
	for(int i =1; i <= n; ++i) if(!dfn[i]) tarjan(i);
	int COL2 =COL;
	for(int i =0; i < (m<<1); ++i)
		if(e[i].isbge){
			e[i^1].isbge =0;
			++COL2;
			val[COL2] =-1;
			link(col[e[i].from], COL2), link(col[e[i].to], COL2);
		}
	for(int i =0; i < Q; ++i){
		int x =read(), y =read();
		if(col[x] == col[y]) continue;
		updata(col[x], col[y]);
		if(WRONG) return puts("No") && 0;
	}
	for(int i =COL+1; i <= COL2; ++i){
		query(i);
		if(WRONG) return puts("No") && 0;
	}
	puts("Yes");
}
```


---

## 作者：Farkas_W (赞：1)

### 思路：

$\quad$先缩点(找边双)，注意一条边只能走一次，缩完点后图就变成了一棵树(或森林，可能有不连通的情况，注意要额外记录是否在一个连通块中)。

$\quad$对于每一个询问 $x$ -> $y$ ，若在一个强连通分量中(边双)不考虑，直接跳过，若不在一个连通块(树)中，直接输出 $"No"$ ，否则对 $x$ 到 $y$ 的路径修改，从x向上跳是修改 $up$ 数组，从 $y$ 向上跳时修改 $down$ 数组，在同一条链上时判断深度，注意方向是从 $x$ 到 $y$ 的方向，修改的是边权最后一次跳要 $+1$ ，最后判断每一条边是否只有向上跳或向下跳(边的方向)，若两个都有就输出 $"No"$ ，有矛盾，最后输出 $"Yes"$ 即可。

前置知识：$Tarjan$ 缩点 $+$ 树链剖分 $+$ 线段树

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cstring>
using namespace std;
#define re register int
#define int long long
#define LL long long
#define il inline
#define next nee
#define inf 1e18
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=2e5+5;
int n,m,q1,next[N<<1],go[N<<1],u[N],v[N],head[N],tot,dfn[N],top[N];
int size[N],cnt,c[N],dep[N],low[N],d[N],father[N],son[N],seg[N];
bool b[N<<1],flag,up[N<<2],down[N<<2];
stack<int>q;
il void Add(int x,int y)
{
  next[++tot]=head[x];
  head[x]=tot;
  go[tot]=y;
}
il void Tarjan(int x,int fa)//缩点
{
  dfn[x]=low[x]=++cnt;d[x]=fa;
  q.push(x);
  for(re i=head[x];i;i=next[i])
    {
      if(b[i]||b[i^1])continue;b[i]=1;
      int y=go[i];
      if(!dfn[y])Tarjan(y,fa),low[x]=min(low[x],low[y]);
      else if(!c[y])low[x]=min(low[x],dfn[y]);
    }
  if(dfn[x]==low[x])
    {
      c[x]=++c[0];
      while(q.top()!=x)
	{
	  c[q.top()]=c[0];
	  q.pop();
	}
      q.pop();
    }
}
il void dfs1(int x,int fa)
{
  dep[x]=dep[fa]+1;father[x]=fa;size[x]=1;
  for(re i=head[x];i;i=next[i])
    {
      int y=go[i];
      if(y==fa)continue;
      dfs1(y,x);
      size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;
    }
}
il void dfs2(int x,int topf)
{
  top[x]=topf;seg[x]=++seg[0];
  if(!son[x])return;
  dfs2(son[x],topf);
  for(re i=head[x];i;i=next[i])
    {
      int y=go[i];
      if(top[y])continue;
      dfs2(y,y);
    }
}
il void pushdown(int k,int l,int r,int mid)
{
  if(down[k])down[k<<1]=down[k<<1|1]=1;
  if(up[k])up[k<<1]=up[k<<1|1]=1;
}
il void change1(int k,int l,int r,int x,int y,int z)
{
  if(x<=l&&y>=r){if(z==1)down[k]=1;else up[k]=1;return;}
  int mid=l+r>>1;
  if(down[k]||up[k])pushdown(k,l,r,mid);
  if(x<=mid)change1(k<<1,l,mid,x,y,z);
  if(y>mid)change1(k<<1|1,mid+1,r,x,y,z);
}
il void change(int x,int y)
{
  int fx=top[x],fy=top[y];
  while(fx!=fy)
    {
      if(dep[fx]>dep[fy]){
	change1(1,1,c[0],seg[fx],seg[x],2);
	x=father[fx];fx=top[x];
      }
      else {
	change1(1,1,c[0],seg[fy],seg[y],1);
	y=father[fy];fy=top[y];
      }
    }
  if(seg[y]+1<=seg[x])change1(1,1,c[0],seg[y]+1,seg[x],2);
  else if(seg[x]+1<=seg[y])change1(1,1,c[0],seg[x]+1,seg[y],1);
}
il bool check(int k,int l,int r)//最后检查每一条边
{
  if(l==r){if(down[k]&&up[k])return 0;else return 1;}
  int mid=l+r>>1;
  if(down[k]||up[k])pushdown(k,l,r,mid);
  return min(check(k<<1,l,mid),check(k<<1|1,mid+1,r));
}
signed main()
{
  n=read();m=read();q1=read();tot=1;
  for(re i=1;i<=m;i++)
    {
      re x=read(),y=read();
      u[i]=x;v[i]=y;
      Add(x,y);Add(y,x);
    }
  for(re i=1;i<=n;i++)
  if(!dfn[i])Tarjan(i,i);//缩点
  memset(next,0,sizeof(next));
  memset(head,0,sizeof(head));
  memset(go,0,sizeof(go));
  tot=0;
  for(re i=1;i<=m;i++)
    {
      int x=c[u[i]],y=c[v[i]];
      if(x!=y)Add(x,y),Add(y,x);
    }
  for(re i=1;i<=n;i++)//树剖预处理
    if(!dep[i])dfs1(i,0),dfs2(i,i);//可能有多棵树
  for(re i=1;i<=q1;i++)
    {
      int u1=read(),v1=read();
      if(d[u1]!=d[v1]){puts("No");return 0;}//是否在一个连通块中
      if(c[u1]!=c[v1])change(c[u1],c[v1]);//若不在一个强连通分量，就修改
      }
  if(check(1,1,c[0]))puts("Yes");
  else puts("No");
  return 0;
}
```

---

## 作者：installb (赞：0)

首先缩点成边双森林，定根，每条路径拆成向上和向下两部分，如果有一条边既要向上又要向下，那就无解了。  

这个用树上差分实现，维护点信息对应其父边信息。

这里简单地讲一下如果要求具体方案的做法。   
对于割边，看覆盖这条边的路径是向上还是向下的即可。

边双经过定向可以成为一个强连通分量。  
无向图的 dfs 树只有返祖边和树边，没有横叉边。  
把边双单独拿出来建个 dfs 树的话，树边向儿子，返祖边向祖先连即可。  
一路往下走到叶子之后，一定会存在一条路能够回到根，否则这个叶子就不会在边双里面了（由于没有横叉边，它能走到的所有点是一棵完整的子树，且该子树根不是树的根），到根以后，就可以往下走到任何一个节点了。

好吧，代码并没有写求方案。  

注意图不连通。。

```cpp
using namespace std;
typedef long long LL;
const LL N = 400005;

LL ec = 1,to[N << 1],nxt[N << 1],bri[N << 1],hed[N] = {0};
void add_edge(LL f,LL t){
	++ ec; to[ec] = t; nxt[ec] = hed[f]; hed[f] = ec;
}

LL dfn[N] = {0},dfc = 0,low[N],col[N];
LL dep[N],fa[25][N];

void tarjan(LL u,LL fe){
	dfn[u] = low[u] = ++ dfc;
	for(LL i = hed[u];i;i = nxt[i]){
		LL v = to[i];
		if(!dfn[v]){
			tarjan(v,i);
			low[u] = min(low[u],low[v]);
			if(low[v] > dfn[u]) bri[i] = bri[i ^ 1] = 1;
		}
		else if(i != (fe ^ 1)) low[u] = min(low[u],dfn[v]);
	}
}

void dfs_dcc(LL u,LL id){
	col[u] = id;
	for(LL i = hed[u];i;i = nxt[i]){
		LL v = to[i];
		if(bri[i] || col[v]) continue;
		dfs_dcc(v,id);
	}
}

LL u[N << 1],v[N << 1],n,m,q,cco = 0;
LL val[2][N];
void rebuild(){
	LL ec2 = ec;
	ec = 0; memset(hed,0,sizeof(hed));
	for(LL i = 1;i <= ec2;i ++){
		if(col[u[i]] == col[v[i]]) continue;
		add_edge(col[u[i]],col[v[i]]);
		add_edge(col[v[i]],col[u[i]]);
	}
}

LL com[N],rt[N],ccm = 0;
void dfs(LL u,LL f,LL id){
	fa[0][u] = f;
	dep[u] = dep[f] + 1;
	com[u] = id;
	for(LL i = hed[u];i;i = nxt[i]){
		LL v = to[i];
		if(v == f) continue;
		dfs(v,u,id);
	}
}

void init_lca(){
	for(LL i = 1;i <= 20;i ++){
		for(LL u = 1;u <= cco;u ++){
			fa[i][u] = fa[i - 1][fa[i - 1][u]];
		}
	}
}

LL get_lca(LL x,LL y){
	if(dep[x] < dep[y]) swap(x,y);
	for(LL i = 20;i >= 0;i --) if(fa[i][x] && dep[fa[i][x]] >= dep[y]) x = fa[i][x];
	if(x == y) return x;
	for(LL i = 20;i >= 0;i --){
		if(fa[i][x] == fa[i][y]) continue;
		x = fa[i][x]; y = fa[i][y];
	}
	return fa[0][x];
}

void modify(LL x,LL y,LL v){
	if(dep[x] < dep[y]) swap(x,y);
	val[v][x] ++; val[v][y] --;
}

void dfs_sum(LL u,LL f){
	for(LL i = hed[u];i;i = nxt[i]){
		LL v = to[i];
		if(v == f) continue;
		dfs_sum(v,u);
		val[0][u] += val[0][v];
		val[1][u] += val[1][v];
	}
}

LL query(){
	for(LL i = 1;i <= ccm;i ++) dfs_sum(rt[i],0);
	for(LL i = 1;i <= cco;i ++) if(val[0][i] && val[1][i]) return 0;
	return 1;
}

int main(){
	ios::sync_with_stdio(false);
	cin >> n >> m >> q;
	for(LL i = 1;i <= m;i ++){
		cin >> u[i] >> v[i];
		add_edge(u[i],v[i]);
		add_edge(v[i],u[i]);
	}
	for(LL i = 1;i <= n;i ++) if(!dfn[i]) tarjan(i,0);
	cco = 0;
	for(LL i = 1;i <= n;i ++){
		if(col[i]) continue;
		cco ++; dfs_dcc(i,cco);
	}
	rebuild();
	for(LL i = 1;i <= cco;i ++){
		if(com[i]) continue;
		ccm ++; rt[ccm] = i; dfs(i,0,ccm);
	}
	init_lca();
	while(q --){
		cin >> u[0] >> v[0];
		u[0] = col[u[0]]; v[0] = col[v[0]];
		if(com[u[0]] != com[v[0]]){
			cout << "No" << endl;
			return 0;
		}
		LL lca = get_lca(u[0],v[0]);
		modify(u[0],lca,0); modify(lca,v[0],1);
	}
	cout << (query() ? "Yes" : "No") << endl;
	return 0;
}
```

---

## 作者：MikukuOvO (赞：0)

首先考虑一个边双连通分量中的点一定合法，这样我们考虑缩点，在无向图上类似有向图跑$Tarjan$即可。

然后我们会得到一个森林，首先判断不在同一颗树就一定不合法，接着考虑在同一棵树的两个点，我们按照题意将$u$到$lca$设为正向边，$lca$到$v$设为反向边，树上差分实现即可。

代码：

```cpp
const int N=2e5+5;

struct EDGE
{
	int fr,to,nxt;
};

int n,m,q,cnt,col_cnt,num,top,id;
bool flag=true;
int head[N],dfn[N],low[N],stk[N],col[N];
int up[N],dn[N],anc[N],f[N][25],bel[N],dep[N];
bool ins[N],vis[N];
EDGE e[N*2];
vc<int>t[N];

void add(int x,int y)
{
	e[++cnt].to=y;
	e[cnt].fr=x;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
void link(int x,int y)
{
	add(x,y),add(y,x);
}
void Tarjan(int x,int fa)
{
	col[x]=col_cnt;
	dfn[x]=low[x]=++id;
	stk[++top]=x,ins[x]=true;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(i==fa) continue;
		if(!dfn[v]) Tarjan(v,i^1),low[x]=min(low[x],low[v]);
		else if(ins[v]) low[x]=min(low[x],dfn[v]);
	}
	if(dfn[x]==low[x])
	{
		++num;
		while(stk[top+1]!=x)
		{
			bel[stk[top]]=num;
			ins[stk[top]]=false;
			--top;
		}
	}
}
void dfs(int x,int fa,int d)
{
	anc[x]=fa,f[x][0]=fa,dep[x]=d;
	for(int i=1;i<=20;++i) f[x][i]=f[f[x][i-1]][i-1];
	for(auto v:t[x])
	{
		if(v==fa) continue;
		dfs(v,x,d+1);
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;--i) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;--i) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
void check(int x)
{
	vis[x]=true;
	for(auto v:t[x])
	{
		if(v==anc[x]) continue;
		check(v);
		up[x]+=up[v],dn[x]+=dn[v];
	}
	if(up[x]&&dn[x]) flag=false;
}
int main()
{
	gi(n),gi(m),gi(q),cnt=1;
	for(int i=1,x,y;i<=m;++i) gi(x),gi(y),link(x,y);
	for(int i=1;i<=n;++i) if(!dfn[i]) ++col_cnt,Tarjan(i,0);
	for(int i=2,x,y;i<=cnt;i+=2)
	{
		x=e[i].fr,y=e[i].to;
		if(bel[x]==bel[y]) continue;
		t[bel[x]].pub(bel[y]),t[bel[y]].pub(bel[x]);
	}
	for(int i=1;i<=num;++i) if(!dep[i]) dfs(i,0,1);
	for(int i=1,x,y;i<=q;++i)
	{
		gi(x),gi(y);
		if(col[x]!=col[y]) flag=false;
		if(!flag) break;
		x=bel[x],y=bel[y];
		int l=lca(x,y);
		++up[x],--up[l];
		++dn[y],--dn[l];
	}
	for(int i=1;i<=num;++i) if(!vis[i]) check(i);
	if(flag) say("Yes");
	else say("No");
	end();
}
```

---

## 作者：孑彧 (赞：0)

# CF555E Case of Computer Network

### 题目大意

- 给定一张 n个点 m 条边的无向图。
- 给定 q 组有向点对 (s, t)。
- 询问是否存在使得所有 s都能到达 t 的无向图中每条边的定向方案。
- $n,m,q \le 2 \times 10^5。$

### 思路

首先一个非常显然的地方就是假如这张图是不连通的，而且正好有点对位于不连通的部分上，那么这个是绝对不能满足的~~这不是废话嘛~~

其次我们可以断定一个边双连通分量有一种合法的定边方式使得其中所有点可以互达。

这个东西非常的~~显然~~，所以在这里就不证明，有兴趣的可以自己证明。

所以我们的目标就出来了，那就是先对整张图寻找边双，然后缩起来，这样我们就解决了那q个询问中的一部分。

然后我们会发现，在缩完所有边双之后，这整张图就变成了一个森林！

那么对于森林上的边的顺序的问题，我们就可以用差分来解决了！

### 代码

```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#define maxn 210000 
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		x=(x<<3)+(x<<1)+(c^48); 
		c=getchar();
	}
	return x*f;
}
//此上是快读部分 
struct Edge{
	int x,to,next;
}e[maxn<<1],ed[maxn<<1];
int head1[maxn],head2[maxn],ecnt1=1,ecnt2=1;
void adde1(int x,int y){
	e[++ecnt1].x=x;
	e[ecnt1].to=y;
	e[ecnt1].next=head1[x];
	head1[x]=ecnt1;
}
void adde2(int x,int y){
	ed[++ecnt2].x=x;
	ed[ecnt2].to=y;
	ed[ecnt2].next=head2[x];
	head2[x]=ecnt2;
}
//两个边集以及加边操作 
int n,m,q;//三个量 
int s[maxn],d[maxn];//差分数组 
bool brige[maxn<<1];//判断桥 
int low[maxn],dfn[maxn],cnt;//tarjan 
int colo;//染色 
void tarjan(int x,int edg){
	dfn[x]=low[x]=++cnt;
	for(int i=head1[x];i;i=e[i].next){
		int to=e[i].to;
		if(!dfn[to]){
			tarjan(to,i);
			low[x]=min(low[x],low[to]);
			if(low[to]>low[x]){
				brige[i]=brige[i^1]=1;
			}
		}
		else{
			if(i!=(edg^1)){
				low[x]=min(low[x],dfn[to]);
			}
		}
	}
}
//求桥 
int col[maxn];
void color(int x){
	col[x]=colo;
	for(int i=head1[x];i;i=e[i].next){
		int to=e[i].to;
		if(brige[i]){//由于缩掉点双后只剩桥边 
			if(col[to]){//防止重复建边 
				adde2(colo,col[to]);
				adde2(col[to],colo);
			}
			continue;
		}
		if(col[to]){
			continue;
		}
		color(to);
	}
}
void block(){
	for(int i=1;i<=n;i++){
		if(!col[i]){
			colo++;
			color(i);
		}
	}
}
//缩点以及重建边，这个地方也可以直接找边双，不过我忘了怎么找了
int fa[maxn],top[maxn],dep[maxn],tot[maxn],son[maxn],maxf[maxn];
void dfs1(int now,int f,int deep,int mf){
	maxf[now]=mf;
	fa[now]=f;
	dep[now]=deep;
	tot[now]=1;
	int maxson=0;
	for(int i=head2[now];i;i=ed[i].next){
		int to=ed[i].to;
		if(to==f){
			continue;
		}
		dfs1(to,now,deep+1,mf);
		tot[now]+=tot[to];
		if(tot[to]>maxson){
			maxson=tot[to];
			son[now]=to;
		}
	}
}
void dfs2(int now,int topf){
	top[now]=topf;
	if(!son[now]){
		return;
	}
	dfs2(son[now],topf);
	for(int i=head2[now];i;i=ed[i].next){
		int to=ed[i].to;
		if(to==fa[now]||to==son[now]){
			continue;
		}
		dfs2(to,to);
	}
}
inline int lca(int a,int b){
	while(top[a]!=top[b]){
		if(dep[top[a]]>=dep[top[b]]) a=fa[top[a]];
		else b=fa[top[b]];
	}
	return dep[a]<dep[b]?a:b;
}
//树链剖分以及求lca
bool flag=1;
bool vis[maxn];
void last_dfs(int x,int fa){
	vis[x]=1;
	for(int i=head2[x];i;i=ed[i].next){
		int to=ed[i].to;
		if(to==fa){
			continue;
		}
		last_dfs(to,x);
		s[x]+=s[to];
		d[x]+=d[to];
		if(s[x]&&d[x]){
			flag=0;
		}
	}
} 
//最后的dfs，用来统计差分数组 
int main(){
	n=read();
	m=read();
	q=read();
	int x,y;
	for(int i=1;i<=m;i++){
		x=read();
		y=read();
		adde1(x,y);
		adde1(y,x);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i,0);
		} 
	}
	block();//把点双都缩掉 
	for(int i=1;i<=n;i++){
		if(fa[i]){
			continue;
		}
		dfs1(i,0,1,i);
		dfs2(i,i);
	}//树链剖分预处理 
	for(int i=1;i<=q;i++){
		x=read();
		y=read();
		if(col[x]==col[y]){
			continue;
		} //假如两者在同一个点双中，那么必定可达 
		x=col[x];
		y=col[y]; 
		if(maxf[x]!=maxf[y]){
			printf("No");
			return 0;
		}//假如两者不连通，那么绝对不可能满足 
		int l=lca(x,y);
		s[x]+=1;
		s[l]-=1;
		d[l]-=1;
		d[y]+=1;
		//进行差分 
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			last_dfs(i,0);
			if(!flag){
				printf("No");
				return 0;
			}
		}
	}//统计差分 
	printf("Yes");
	return 0;
}
```

~~我的代码好丑~~

### 后记

国集作业第一题



---

