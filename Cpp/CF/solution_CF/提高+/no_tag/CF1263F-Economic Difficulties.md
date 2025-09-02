# Economic Difficulties

## 题目描述

An electrical grid in Berland palaces consists of 2 grids: main and reserve. Wires in palaces are made of expensive material, so selling some of them would be a good idea!

Each grid (main and reserve) has a head node (its number is $ 1 $ ). Every other node gets electricity from the head node. Each node can be reached from the head node by a unique path. Also, both grids have exactly $ n $ nodes, which do not spread electricity further.

In other words, every grid is a rooted directed tree on $ n $ leaves with a root in the node, which number is $ 1 $ . Each tree has independent enumeration and nodes from one grid are not connected with nodes of another grid.

Also, the palace has $ n $ electrical devices. Each device is connected with one node of the main grid and with one node of the reserve grid. Devices connect only with nodes, from which electricity is not spread further (these nodes are the tree's leaves). Each grid's leaf is connected with exactly one device.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1263F/d2ac1cff6c110584bcbf1b1d6ee6c7fd9565b72f.png)In this example the main grid contains $ 6 $ nodes (the top tree) and the reserve grid contains $ 4 $ nodes (the lower tree). There are $ 3 $ devices with numbers colored in blue.It is guaranteed that the whole grid (two grids and $ n $ devices) can be shown in this way (like in the picture above):

- main grid is a top tree, whose wires are directed 'from the top to the down',
- reserve grid is a lower tree, whose wires are directed 'from the down to the top',
- devices — horizontal row between two grids, which are numbered from $ 1 $ to $ n $ from the left to the right,
- wires between nodes do not intersect.

Formally, for each tree exists a depth-first search from the node with number $ 1 $ , that visits leaves in order of connection to devices $ 1, 2, \dots, n $ (firstly, the node, that is connected to the device $ 1 $ , then the node, that is connected to the device $ 2 $ , etc.).

Businessman wants to sell (remove) maximal amount of wires so that each device will be powered from at least one grid (main or reserve). In other words, for each device should exist at least one path to the head node (in the main grid or the reserve grid), which contains only nodes from one grid.

## 说明/提示

For the first example, the picture below shows one of the possible solutions (wires that can be removed are marked in red):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1263F/4795ef7afbe6829915a70b3156912a9c85a389da.png)The second and the third examples can be seen below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1263F/3308f2d3e2d311107604cc49eb4ad70916b447d6.png)

## 样例 #1

### 输入

```
3
6
4 1 1 4 2
6 5 3
4
1 1 1
3 4 2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4
6
4 4 1 1 1
3 2 6 5
6
6 6 1 1 1
5 4 3 2
```

### 输出

```
6
```

## 样例 #3

### 输入

```
5
14
1 1 11 2 14 14 13 7 12 2 5 6 1
9 8 3 10 4
16
1 1 9 9 2 5 10 1 14 3 7 11 6 12 2
8 16 13 4 15
```

### 输出

```
17
```

# 题解

## 作者：lalaouye (赞：2)

我是网络流锰锌，这道题折磨了我很久。

我们发现这里面每条边可选可不选，并且都有一定的限制条件，于是我们的思路可以往网络流方面靠拢。那么题目要求最大化，我们发现用最大流并不好做，于是考虑转化为最小割。其中要割的边就是我们要选的边数。

根据套路很自然的我们先考虑将 $S$ 向每个点连边，每条边流量为 $1$，意思是选这条边的代价。思路清晰的，我们考虑有哪些限制。首先，我们选一条连接叶子的边，那么必须将上面的边全部选上，为了满足这个条件，我们把每个条边上面连接的边向自己连边，边权为无限，因为这样如果我们要割掉一条边，那么上面的边显然也要割掉，不然这是无意义的。

然后最难的地方是如何处理电机的两端。我们需要建出两个中至少选择一个的关系。我们可以将图改造一下，把第二棵树代表边的每个点向 $T$ 连边，边权为 $1$，再把每个儿子向父亲连边，边权为无限，然后对于电机两端的点，我们将第一棵树的店连向第二棵树的店，流量也为无限。我们发现，这样子建图就非常合理，可以满足需要的关系。

这样子建图的边数仅仅是 $\mathcal{O}(n)$ 级别的，所以很容易跑过。

代码：

```
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define rrp(i, l, r) for (int i = r; i >= l; -- i)
#define eb emplace_back
#define inf 1000000000
#define linf 10000000000000000
#define pii pair <int, int>
using namespace std;
const int N = 5e4 + 5;
inline int rd ()
{
	int x = 0, f = 1;
	char ch = getchar ();
	while (! isdigit (ch)) { if (ch == '-') f = -1; ch = getchar (); }
	while (isdigit (ch)) { x = (x << 1) + (x << 3) + ch - 48; ch = getchar (); }
	return x * f;
}
int n, a, b, p[N], x[N], q[N], y[N], s, t; 

namespace mf
{
  int h[N], to[N], nxt[N], val[N], tot = 1;
  int dep[N];
  queue <int> q;
  void init ()
  {
    rep (i, 0, t) h[i] = 0;
    tot = 1;
  }
  void add (int u, int v, int w)
  {
    to[++ tot] = v;
    val[tot] = w;
    nxt[tot] = h[u];
    h[u] = tot;
    
    to[++ tot] = u;
    val[tot] = 0;
    nxt[tot] = h[v];
    h[v] = tot;
  }
  int bfs ()
  {
    q.push (s);
    rep (i, 0, t) dep[i] = 0;
    dep[s] = 1;
    while (! q.empty ())
    {
      int u = q.front ();
      q.pop ();
      for (int i = h[u]; i; i = nxt[i])
      {
        int v = to[i], w = val[i];
        if (! w || dep[v]) continue;
        dep[v] = dep[u] + 1;
        q.push (v);
      }
    }
    return dep[t];
  }
  int dfs (int u, int g)
  {
    if (u == t) return g;
    int flow = 0;
    for (int i = h[u]; i; i = nxt[i])
    {
      int v = to[i], w = val[i];
      if (! w || dep[v] != dep[u] + 1) continue;
      int tmp = dfs (v, min (g, w));
      flow += tmp, val[i ^ 1] += tmp;
      val[i] -= tmp, g -= tmp;
    }
    if (! flow) dep[u] = 0;
    return flow;
  }
  int solve ()
  {
    int flow = 0;
    while (bfs ()) flow += dfs (s, inf);
    return flow;
  }
}

signed main ()
{
  n = rd ();
  a = rd ();
  rep (i, 2, a)
  {
    int j = rd ();
    if (j == 1) continue;
    mf::add (j, i, inf);
  }
  rep (i, 1, n) x[i] = rd ();
  b = rd ();
  rep (i, 2, b)
  {
    int j = rd ();
    if (j == 1) continue;
    mf::add (i + a, j + a, inf);
  }
  rep (i, 1, n)
  {
    y[i] = rd ();
    mf::add (x[i], y[i] + a, inf);
  }
  t = a + b + 1;
  rep (i, 2, a) mf::add (0, i, 1);
  rep (i, 2, b) mf::add (a + i, t, 1);
  printf ("%d\n", a - 1 + b - 1 - mf::solve ());
}

/*
1
6 2 6
1 2 1 3 2 2 
*/
```

---

## 作者：EastPorridge (赞：2)

愤怒愤怒，唯一给的一篇题解写的 dp 我看不懂，所以写网络流了。

两种建图方法，先考虑一种 $O(\text{能过})$ 的，我们没法做保证联通下最大去多少边，但我们可以建图跑最小割找最少保留多少边。

先把边化点来看，超级源点 $S$ 到点 $i$ 满流量表示我们要保留这个点，则 $i$ 的父亲 $fa_i$ 到 $i$ 之间的流量得用 $+\infty$，因为如果保留 $i$，则 $fa_i$ 也必须保留，否则就不符合连通条件。

同时两棵树的根节点之间流量也是 $+\infty$，因为我们割不掉非树边，另外一棵树跟上面第一棵树同理，$i \rightarrow fa_i,i \rightarrow T$ 对称过去就可以了。

最后的答案就是 $a$ 树边 $+$ $b$ 树边 $-$ 最小割。

让这个复杂度变得正确，我们显然得往二分图上面靠，此时设 $i$ 为第 $i$ 条边，首先把它变成二分图的形状。

$S \rightarrow i,i+a \rightarrow T$ 建流量为 $1$ 的边。

考虑 $a$ 树的 $i$ 边和 $b$ 树的 $j$ 边不能同时删的情况，首先每条边删掉之后肯定在某种 dfs 序上会影响一整段区间，显然如果 $[l_i,r_i] \cap [l_j,r_j] \ne \varnothing$，我们肯定不能同时删掉 $i,j$，因为一棵树上每条边影响的区间是单独唯一的，此时 $i \rightarrow j$ 的流量为 $+\infty$，这样把图建出来，必须保留边的数量就是图上最小割。

最后的答案就是 $a+b-$ 最小割，它是个二分图，时间复杂度 $O(m \sqrt n)$。

给的第一种的代码。

### Code.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,imax=0x3f3f3f3f;
int n,a,b,s,t,cur[N],h[N],fa[N],fb[N],ta[N],tb[N],idx,ne[N<<1],e[N<<1],f[N<<1],d[N];
void add(int u,int v,int c)
{
	ne[idx]=h[u],e[idx]=v,f[idx]=c,h[u]=idx++;
	ne[idx]=h[v],e[idx]=u,f[idx]=0,h[v]=idx++;
}
bool bfs()
{
	queue<int> q; q.emplace(s);
	memset(d,-1,sizeof d); d[s]=0; cur[s]=h[s];
	while(! q.empty())
	{
		int u=q.front(); q.pop();
		for(int i=h[u];~i;i=ne[i])
		{
			int j=e[i];
			if(! ~d[j] && f[i])
			{
				cur[j]=h[j]; d[j]=d[u]+1;
				if(j == t) return 1;
				q.emplace(j);
			}
		}
	}
	return 0;
}
int find(int u,int fl)
{
	if(u == t) return fl; int flu=0;
	for(int i=cur[u];~i && flu < fl;i=ne[i])
	{
		cur[u]=i; int j=e[i];
		if(d[j] == d[u] + 1 && f[i])
		{
			int res=find(j,min(fl-flu,f[i]));
			if(! res) d[j]=-1;
			f[i]-=res; f[i^1]+=res; flu+=res;
		}
	}
	return flu;
}
int dinic()
{
	int res=0,fl;
	while(bfs()) while((fl=find(s,imax))) res+=fl;
	return res;
}
int main()
{
	memset(h,-1,sizeof h); scanf("%d%d",&n,&a);
	for(int i=2;i<=a;i++) scanf("%d",fa+i);
	for(int i=1;i<=n;i++) scanf("%d",ta+i);
	scanf("%d",&b); 
	for(int i=2;i<=b;i++) scanf("%d",fb+i);
	for(int i=1;i<=n;i++) scanf("%d",tb+i);
	s=a+b+2; t=a+b+3;
	for(int i=2;i<=a;i++) {add(s,i,1); add(fa[i],i,imax);}
	for(int i=2;i<=b;i++) {add(a+i,t,1); add(a+i,a+fb[i],imax);}
	for(int i=1;i<=n;i++) add(ta[i],a+tb[i],imax);
	printf("%d\n",a+b-2-dinic());
	return 0;
}
```

---

## 作者：pyyyyyy (赞：2)


## 题目大意
给你两棵树，结点分别是1～A与1～B，然后给了N台设备，并且A树和B树的叶子结点(两棵树的叶子节点数量相同)都是链接电机的。问，最多可以删掉几条边使得每个设备都能连到任意一棵（或两棵）树的根节点（1号点）
## 思路
对于每棵树，维护$val[cnt][i][j]$，$cnt$是那个树表示我删掉这个子树的所有边之后，$[i,j]$这个范围的设备不保证能够全部连上我的根。

用一个$f[i]$表示$[1,i]$区间内，全都能连上根最多能删除多少条边，那么转移就是$f[i]=max(f[i],f[j-1]+max(val[cnt][j][i]))$
## 代码
```cpp
#include<bits/stdc++.h>
#include<vector>
using namespace std;
const int N=2019;
vector<int> G[2][N];
int f[N];
int val[2][N][N],l[2][N],r[2][N],size[2][N];
int x,n,a;
void dfs(int num,int x)
{
	if(x!=1) size[num][x]=1;
	for(int i=0;i<G[num][x].size();++i)
	{
		int to=G[num][x][i];
		dfs(num,to);
		size[num][x]+=size[num][to];
		l[num][x]=min(l[num][x],l[num][to]);
		r[num][x]=max(r[num][x],r[num][to]); 
	} 
	val[num][l[num][x]][r[num][x]]=max(val[num][l[num][x]][r[num][x]],size[num][x]);
}
void read() {
	cin>>n;
	for(int cnt=0; cnt<=1; ++cnt) {
		cin>>a;
		for(int i=1; i<=a; i++) l[cnt][i]=a+1,r[cnt][i]=0;
		for(int i=2; i<=a; ++i) {
			cin>>x;
			G[cnt][x].push_back(i);
		}
		for(int i=1; i<=n; ++i) {
			cin>>x;
			l[cnt][x]=r[cnt][x]=i;
		}
		dfs(cnt,1);
	}
}
int main() {
	read();
	for(int i=1;i<=n;++i)
		for(int j=i;j<=n;++j)
			f[j]=max(f[j],f[i-1]+max(val[0][i][j],val[1][i][j]));
	cout<<f[n];
	return 0;
}


```
推荐看看这篇博客[传送门](https://blog.csdn.net/qq_41730082/article/details/103321955)

---

## 作者：ShanQing (赞：1)

给一个边数 $n^2$ 但比较无脑的最小割解法，但是由于是二分图所以能过。   

首先正难则反，求最少的加边数。   

关于网络流的建图，以其中一边的树为例，令每个点对应父亲边并向子树内所有叶子连边（叶子是单独开点），边权为 $+\infty$。然后根节点向每个边的对应点连边，边权为 $1$。另一个树的建图同理，边方向取反即可。最后就是电机连接的两个叶子之间连 $+\infty$ 的边，这一步是套路的。   

例如由第一个样例建出的图是这样的，其中圆点表示点的父亲边，方点表示叶子。   

![](https://cdn.luogu.com.cn/upload/image_hosting/yvx97uya.png)   

在这个网络流的图中，原图保留一个边在此处表现为根节点和那条边的对应点断开。反之原图上割掉一个边在此处表现为保留根节点向那条边对应点的边。   

这样一个叶子和根连通在网络流上就表现为其所有祖先边对应点都和根断开。所以最小割的意义就是每个电机的两个连接的叶子中都有一个和对应的根连通。因此只要在这张图上直接跑最小割即可。   

最后答案即为 $(a-1)+(b-1)-$ 最小割。即总边数减去保留边数。   

二分图上 Dinic 的复杂度为 $O(E\sqrt{V})$。在这里 $E$ 为 $10^6$ 级别，$V$ 为 $10^3$ 级别。只要代码常数不要太大就能过。   

## code

写得很shit。   

```cpp
#include <bits/stdc++.h>
//#include <windows.h>
#define ED cerr<<endl;
#define TS cerr<<"I AK IOI"<<endl;
#define cr(x) cerr<<x<<endl;
#define cr2(x,y) cerr<<x<<" "<<y<<endl;
#define cr3(x,y,z) cerr<<x<<" "<<y<<" "<<z<<endl;
#define cr4(x,y,z,w) cerr<<x<<" "<<y<<" "<<z<<" "<<w<<endl;
#define pii pair<int,int>
#define mk make_pair
#define fi first
#define se second
using namespace std;
const int N=2e3+50,M=6e3+5,INF=1e9,mod=1e9+7;
int n,a,b,s,t;

struct edge {
	int ne,to,w;
}e[N*N];
int _head[M],head[M],tot=1;

void add(int head[],int u,int v,int w) {
	e[++tot]={head[u],v,w};
	head[u]=tot;
} 

int leaf[M],id[M],len=0;
int dfn[M],sz[M],rnk[M],idx=0;
int dis[M],cur[M];
int l[N],r[N];

void _dfs(int u) {
	id[u]=-1;
	dfn[u]=++idx,sz[u]=1,rnk[idx]=u;
	for(int i=_head[u];i;i=e[i].ne) {
		int to=e[i].to;
		id[u]=0,_dfs(to);
		sz[u]+=sz[to]; 
	}
	if(id[u]==-1) leaf[++len]=u,id[u]=len;
}

bool bfs() {
	for(int i=1;i<=a+b+n+n;++i) {
		dis[i]=-1,cur[i]=head[i];
	}
	queue<int> q;
	dis[s]=1,q.push(s);
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].ne) {
			int to=e[i].to;
			if(e[i].w&&dis[to]==-1) {
				dis[to]=dis[u]+1;
				if(to==t) return true;
				q.push(to);
			}
		}
	}
	return false;
}

int dfs(int u,int flow) {
	if(u==t) return flow;
	int used=0,to;
	for(int i=cur[u];i;i=e[i].ne) {
		cur[u]=i,to=e[i].to;
		if(e[i].w&&dis[to]==dis[u]+1) {
			int x=dfs(to,min(e[i].w,flow));
			e[i].w-=x,e[i^1].w+=x;
			flow-=x,used+=x;
			if(!flow) break;
		}
	}
	if(!used) dis[u]=-1;
	return used;
} 

int Dinic() {
	int res=0;
	while(bfs()) res+=dfs(s,INF);
	return res;
}

int main()
{
	scanf("%d",&n);
	int fa;
	scanf("%d",&a);
	for(int i=2;i<=a;++i) {
		scanf("%d",&fa);
		add(_head,fa,i,1);
	}
	_dfs(1);
	for(int i=1;i<=n;++i) {
		scanf("%d",&l[i]);
	}
	scanf("%d",&b);
	int all=a+b;
	for(int i=a+2;i<=all;++i) {
		scanf("%d",&fa);
		add(_head,a+fa,i,1);
	}
	_dfs(a+1);
	if(!(tot&1)) ++tot;//处理反边 
	s=1,t=a+1;
	for(int i=1;i<=n;++i) {
		scanf("%d",&r[i]);
		add(head,all+id[l[i]],all+id[a+r[i]],INF);
		add(head,all+id[a+r[i]],all+id[l[i]],0);
	}
	for(int i=2;i<=a;++i) {
		add(head,s,i,1);
		add(head,i,s,0);
		for(int j=1;j<=n;++j) {
			int to=leaf[j];
			if(dfn[to]>=dfn[i]&&dfn[to]<=dfn[i]+sz[i]-1) {
				add(head,i,j+all,INF);
				add(head,j+all,i,0);
			}
		}
	}
	for(int i=a+2;i<=all;++i) {
		add(head,i,t,1);
		add(head,t,i,0);
		for(int j=n+1;j<=len;++j) {
			int to=leaf[j];
			if(dfn[to]>=dfn[i]&&dfn[to]<=dfn[i]+sz[i]-1) {
				add(head,j+all,i,INF);
				add(head,i,j+all,0);
			}
		}
	}
	printf("%d\n",a+b-2-Dinic());
	return 0;
}
```

---

## 作者：forgotmyhandle (赞：0)

[原题传送门](http://codeforces.com/problemset/problem/1263/F)

[你谷传送门](https://www.luogu.com.cn/problem/CF1263F)

## 分析
考虑 dp。设 $w[0/1][l][r]$ 为区间 $[l, r]$ 内的设备**不**与上 / 下树连通且不影响其他设备与上 / 下树连通性时可以删除的最多边数。可以枚举 $l$，递推 $r$。假设我们现在要从区间 $[l, r)$ 得到区间 $[l, r]$ 的答案，考虑可以多删哪些边。发现多删去的边一定是 $x[r]$ 及其若干祖先组成的一条链。于是可以观察这条链最多可以延伸到哪个点。由于我们要保证 $x[r + 1]$ 与 $x[l - 1]$ 与根的连通性，于是这两个点的祖先都不能删。于是这条链最长就是到 $LCA(x[r], x[r + 1]$ 与 $LCA(x[r], x[l - 1])$ 中较深的那个。由于 $[l, r)$ 这个状态已经保证了 $x[r]$ 与根的连通性，所以这条链里的边都可以随便删，不用考虑删重复的问题。

接下来定义 $f[i]$ 为只考虑 $[1, i]$ 这个区间里的设备时，使其中每台设备都与任意一根连通时所能删去的最多边数。于是有转移 $f[i] = \max_{0 \leq j < i} \{ f[j] + \max \{ w[0][j + 1][i], w[1][j + 1][i] \} \}$。这个式子应该比较好理解。

## 代码
```cpp
#include <iostream>
using namespace std;
int n, a, b;
int x[1005][2];
class Tree {
public:
    int head[20005], nxt[20005], to[20005], ecnt;
    void add(int u, int v) { to[++ecnt] = v, nxt[ecnt] = head[u], head[u] = ecnt; }
    int n, lf;
    int top[10005], son[10005], dep[10005], sz[10005], f[10005];
    int dp[1005][1005];
    void dfs1(int x, int fa, int d) {
        dep[x] = d;
        sz[x] = 1;
        f[x] = fa;
        for (int i = head[x]; i; i = nxt[i]) {
            int v = to[i];
            if (v != fa) {
                dfs1(v, x, d + 1);
                sz[x] += sz[v];
                if (sz[son[x]] < sz[v]) 
                    son[x] = v;
            }
        }
    }
    void dfs2(int x, int t) {
        top[x] = t;
        if (!son[x]) 
            return;
        dfs2(son[x], t);
        for (int i = head[x]; i; i = nxt[i]) {
            int v = to[i];
            if (v != f[x] && v != son[x]) 
                dfs2(v, v);
        }
    }
    void ini() { dfs1(1, 0, 1), dfs2(1, 1); }
    int LCA(int x, int y) {
        if (!x || !y) 
            return 1;
        while (top[x] ^ top[y]) (dep[top[x]] < dep[top[y]]) ? (y = f[top[y]]) : (x = f[top[x]]);
        return (dep[x] < dep[y] ? x : y);
    }
    void main() {
        cin >> n;
        for (int i = 2, x; i <= n; i++) {
            cin >> x;
            add(x, i);
            add(i, x);
        }
        ini();
    }
    void Solve(int a) {
        for (int i = 1; i <= lf; i++) {
            for (int j = i; j <= lf; j++) {
                int l1 = LCA(x[i - 1][a], x[j][a]), l2 = LCA(x[j][a], x[j + 1][a]);
                if (dep[l1] < dep[l2]) 
                    swap(l1, l2);
                dp[i][j] = dp[i][j - 1] + dep[x[j][a]] - dep[l1];
            }
        }
    }
} T[2];
int dp[1005];
int main() {
    cin >> n;
    T[0].main();
    for (int i = 1; i <= n; i++) cin >> x[i][0];
    T[1].main();
    for (int i = 1; i <= n; i++) cin >> x[i][1];
    T[0].lf = T[1].lf = n;
    T[0].Solve(0);
    T[1].Solve(1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) 
            dp[i] = max(dp[i], dp[j] + max(T[0].dp[j + 1][i], T[1].dp[j + 1][i]));
    }
    cout << dp[n];
    return 0;
}
```

---

