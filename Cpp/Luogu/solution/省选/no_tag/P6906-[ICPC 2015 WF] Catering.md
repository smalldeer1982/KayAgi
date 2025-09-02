# [ICPC 2015 WF] Catering

## 题目描述

Paul 拥有一家餐饮公司，生意兴隆。公司有 $k$ 个餐饮团队，每个团队负责一套餐饮设备。每周，公司会接受 $n$ 个不同活动的餐饮请求。对于每个请求，他们会派遣一个餐饮团队及其设备到活动地点。团队负责送餐、安装设备，并指导主办方如何使用设备和提供餐饮。活动结束后，主办方负责将设备归还给 Paul 的公司。

不幸的是，有些周的餐饮团队数量少于请求数量，因此一些团队可能需要用于多个活动。在这种情况下，公司不能等待主办方归还设备，必须让团队留在现场以便将设备转移到另一个地点。公司可以准确估算从任何地点到任何其他地点移动一套设备的成本。鉴于这些成本，Paul 希望准备一份“高级餐饮地图”以满足请求，同时最小化设备的总移动成本（包括首次移动的成本），即使这意味着不使用所有可用的团队。Paul 需要你的帮助来编写一个程序来完成这个任务。请求按活动时间的升序排序，并且选择这些请求的方式是，对于任何 $i < j$，都有足够的时间将用于第 $i$ 个请求的设备运输到第 $j$ 个请求的地点。

## 说明/提示

时间限制：4000 毫秒，内存限制：1048576 kB。

国际大学生程序设计竞赛（ACM-ICPC）世界总决赛 2015。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 2
40 30 40
50 10
50
```

### 输出

```
80
```

## 样例 #2

### 输入

```
3 2
10 10 10
20 21
21
```

### 输出

```
40
```

# 题解

## 作者：Alex_Wei (赞：3)

> XIX. [P6906 [ICPC2015 WF] Catering](https://www.luogu.com.cn/problem/P6906)

比较简单的网络流。

拆点限制每个点只能经过一次。$in_i \to out_i$ 连容量 $1$，容量下界 $1$，权值 $0$ 的边；$out_i\to in_j(i < j)$ 连容量 $1$，权值 $w(i, j)$ 的边；$in_1\to out_1$ 连容量 $k$，权值 $0$ 的边。$out_i\to T$ 连容量 $1$，权值 $0$ 的边。

我们发现直接流 $in_1\to T$ 会出错，因为并不一定需要满流。因此，考虑从 $1$ 到 $k$ 枚举最优流量，每次添加 $in_1\to out_1$ 容量 $1$，权值 $0$ 的边，将任意时刻最小费用取 $\min$ 即可。时间复杂度是 $n$ 次有源汇上下界费用流。

避免上下界网络流的方法：我们知道 $in_i\to out_i$ 的流量恰为 $1$ 且无权，不妨将其权值设为一个绝对值小于两倍边权的负数，如 $-10 ^ 7$，那么最小费用方案中每条 $in_i\to out_i$ 流量必为 $1$，将求得最小值加上 $10 ^ 7 n$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using uint = unsigned int;
using lll = __int128;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ull = unsigned long long;
inline ll read() {
  ll x = 0, sgn = 0;
  char s = getchar();
  while(!isdigit(s)) sgn |= s == '-', s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return sgn ? -x : x;
}
inline void print(int x) {
  if(x < 0) return putchar('-'), print(-x);
  if(x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
bool Mbe;
constexpr int N = 200 + 5;
constexpr int M = 1e4 + 5;
constexpr int inf = 1e7;
struct flow {
  int cnt = 1, hd[N], nxt[M << 1], to[M << 1], limit[M << 1], cst[M << 1];
  void add(int u, int v, int w, int c) {
    nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v, limit[cnt] = w, cst[cnt] = c;
    nxt[++cnt] = hd[v], hd[v] = cnt, to[cnt] = u, limit[cnt] = 0, cst[cnt] = -c;
  }
  int in[N], dis[N], fr[N];
  int mincost(int S, int T) {
    int cost = 0;
    while(1) {
      queue<int> q;
      memset(dis, 0x3f, sizeof(dis));
      dis[S] = 0, q.push(S);
      while(!q.empty()) {
        int t = q.front();
        q.pop(), in[t] = 0;
        for(int i = hd[t]; i; i = nxt[i]) {
          int it = to[i], d = dis[t] + cst[i];
          if(limit[i] && d < dis[it]) {
            dis[it] = d, fr[it] = i;
            if(!in[it]) q.push(it), in[it] = 1;
          }
        }
      }
      if(dis[T] > 1e9) return cost;
      int fl = 1064;
      for(int i = T; i != S; i = to[fr[i] ^ 1]) fl = min(fl, limit[fr[i]]);
      for(int i = T; i != S; i = to[fr[i] ^ 1]) limit[fr[i]] -= fl, limit[fr[i] ^ 1] += fl;
      cost += fl * dis[T];
    }
  }
} g;
int n, k;
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n >> k;
  int T = n * 2 + 2;
  for(int i = 0; i < n; i++)
    for(int j = i + 1; j <= n; j++)
      g.add(i * 2 + 1, j * 2, 1, read());
  for(int i = 1; i <= n; i++) g.add(i * 2, i * 2 + 1, 1, -inf), g.add(i * 2 + 1, T, 1, 0);
  int ans = 1e9, cur = 0;
  for(int i = 1; i <= k; i++) {
    g.add(0, 1, 1, 0);
    ans = min(ans, cur += g.mincost(0, T));
  }
  cout << ans + inf * n << endl;
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/9/25
author: Alex_Wei
start coding at 7:52
finish debugging at 8:15
*/
```

---

## 作者：ddxrS_loves_zxr (赞：1)

使用有源汇上下界网络流。

先考虑每一个活动 $i$，可以拆点成 $in_i$ 和 $out_i$。

- 从 $in_i$ 连边到 $out_i$，下界 $1$，容量 $1$，费用 $0$，用来限制每个活动必须走一次且只能走一次。
- 从 $out_i$ 连向汇点 $t$，下界 $0$，容量 $+\infty$，费用 $0$，表示到了这个点就不再往后走了。

接下来考虑源点 $1$ 号点，与其他点类似，连 $in_1$ 到 $out_1$，下界 $0$，容量 $k$，费用 $0$，因为这个点可以传出 $k$ 次。然后 $out_1$ 连向 $t$，下界 $0$，容量 $+\infty$，费用 $0$。

对于给出的所有边，连 $out_i$ 到 $in_j$，下界 $0$，容量 $1$，费用 $w_{i,j}$。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e4 + 5, M = 4e6 + 5, INF = 0x3f3f3f3f;
int n, k, s, t, S, T; ll tmp;
struct edge {int to, nxt; ll w, cost;} edge[M];
ll deg[N];
int head[N], tcnt = 2;
void addedge(int u, int v, ll L, ll R, ll cost) {
	deg[u] -= L, deg[v] += L, tmp += L * cost;
    edge[tcnt] = { v, head[u], R - L, cost }, head[u] = tcnt++;
    edge[tcnt] = { u, head[v], 0, -cost }, head[v] = tcnt++;
}
int vis[N], dis[N], pre[N];
bool spfa() {
    queue<int> q;
    memset(vis, 0, sizeof vis), memset(dis, 0x3f, sizeof dis), memset(pre, -1, sizeof pre);
    dis[s] = 0, q.push(s);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = false;
        for (int p = head[x]; p; p = edge[p].nxt) {
            int y = edge[p].to; ll val = edge[p].w, cost = edge[p].cost;
            if (val > 0 && dis[y] > dis[x] + cost) {
                pre[y] = p, dis[y] = dis[x] + cost;
                if (!vis[y]) vis[y] = true, q.push(y);
            }
        }
    }
    return ~pre[t];
}
ll ssp() {
    ll flow = 0, ans = 0;
    while (spfa()) {
        ll minn = INF;
        for (int p = t; ~pre[p]; p = edge[pre[p] ^ 1].to) minn = min(minn, edge[pre[p]].w);
        for (int p = t; ~pre[p]; p = edge[pre[p] ^ 1].to) ans += minn * edge[pre[p]].cost, edge[pre[p]].w -= minn, edge[pre[p] ^ 1].w += minn;
        flow += minn;
    }
	return ans;
}
int main() {
#ifdef ddxrS
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
	cin>>n>>k; n++; S = 1, T = n + n + 1, s = n + n + 2, t = n + n + 3; 
    addedge(1, 1 + n, 1, k, 0), addedge(1 + n, T, 0, INF, 0);
    for(int i = 2; i <= n; i++) addedge(i, i + n, 1, 1, 0), addedge(i + n, T, 0, INF, 0);
    for(int i = 1; i <= n; i++)
        for(int j = i + 1, a; j <= n; j++) cin>>a, addedge(i + n, j, 0, INF, a);
	addedge(T, S, 0, INF, 0);
	for(int i = 1; i <= T; i++) {
		if(deg[i] > 0) addedge(s, i, 0, deg[i], 0);
		else if(deg[i] < 0) addedge(i, t, 0, -deg[i], 0);
	}
	cout<<tmp + ssp()<<'\n';
    cerr << clock() * 1.0 / CLOCKS_PER_SEC << '\n';
    return 0;
}
```

---

## 作者：MSqwq (赞：1)

一道 nice easy problem  
前置知识：网络流  

题意：  
给你 $n + 1$ 个点的图，然后对于任意两点都有一条边，现在有 $k$ 个人从 $0$ 点出发，每个人都能沿着任意边走到某个点（可以是 $0$ 点，也就是不动)停下来要求对于任意点 $i$ 恰好存在一个人经过，问所有人经过的边权和最大为多少。  

题解：  
先观察一下样例一的图：  
![](https://img-blog.csdnimg.cn/eddccbb826ee43a3969bff36b5d62bab.png#pic_center)  
分析一下，假设每个人走动形成的轨迹是一个新图，那么在这张图中，原点的出度小于等于 $k$。其他点分两类讨论，对于不是终点的点的入度和出度都为 $1$ ，否则入度为 $1$ ，出度为 $0$。因此可以构建出这样的网络流模型。  

![](https://img-blog.csdnimg.cn/cfea1979e9f44842abc15a69d1507b8c.png#pic_center)  
然后来证明一下正确性：  
首先是 $0$ 点的出度一定是小于等于 $k$ 的，因为从 $st$ 点出发的流量最大只有 $k$，此外点 $n+1$ 的唯一流量只能来源于 $0$ 点，这条边一定会被算到最大流中，故 $0$ 点出度至少是 $1$，所以这里是合理的。  
然后再考虑除 $0$ 点外在原图中每个点的入度，由于从 $st$ 点出发的流量是不小于流入 $en$ 点的最大流量，故 $n+1 \rightarrow n+n$ 的节点都会向 $en$ 点贡献流量，由于每个节点流量为 $1$ 的限制，并且 $n+1 \rightarrow n+n$ 的节点的流量都必定来自 $0 \rightarrow n-1$，相当于原图中 $1 - n$ 的节点入度都为 $1$。而原图中每个节点（$1 - n$）的出度可为 $0$ 可为 $1$ ，对应着网络流中的 $1 - n$ 号节点向 $n+1 - n+n$ 号节点的连边关系（如果不连边为 $0$ 否则为 $1$，由于 $1 - n$ 号节点流量最大为 $1$，所以出度最大为 $1$）。   
会建图之后其实代码就很好写了，代码如下：  
```
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<functional>
#define ll long long
using namespace std;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0',c=getchar();}
	return x*f;
}
const int N=510,M=1e5;
struct MSqwq{
	int to,next,z,c;
}e[M];
int elast[N],k=1;
void add(int x,int y,int z,int c)
{
	//cout<<x<<" "<<y<<" "<<z<<endl;
	e[++k]={y,elast[x],z,c},elast[x]=k;
	e[++k]={x,elast[y],0,-c},elast[y]=k;
}
int n,m,st,en;
int in[N],out[N],dis[N],cnt[N],flo[N],fe[N];
int ans;

bool bfs(int st,int en)
{
	queue<int>q;q.push(st);
	for(int i=0;i<=N-10;i++)dis[i]=INF,cnt[i]=0,flo[i]=0;
	dis[st]=0,cnt[st]=1,flo[st]=INF;
	while(!q.empty())
	{
		int now=q.front();q.pop();	
		//cout<<now<<endl;
		for(int i=elast[now];i;i=e[i].next)
		{
			int to=e[i].to;
			if(e[i].z!=0&&dis[to]>dis[now]+e[i].c)
			{
				dis[to]=dis[now]+e[i].c;
				flo[to]=min(flo[now],e[i].z);
				fe[to]=i;
				if(!cnt[to])cnt[to]=1,q.push(to);
			}
		}
		cnt[now]=0;
	}
	if(flo[en]>0)return true;
	return false;
}

void dfs(int st,int en)
{
	while(bfs(st,en))
	{
		ans+=flo[en]*dis[en];
		int now=fe[en];
		e[now].z-=flo[en],e[now^1].z+=flo[en];
		int to=e[now^1].to;
		while(to!=st)
		{
			to=e[now^1].to;
			now=fe[to];
			e[now].z-=flo[en],e[now^1].z+=flo[en];
		}
	}
}

int main()
{
	int n=read(),m=read();
	int st=2*n+1,en=2*n+2;
	add(st,0,m,0);
	for(int i=1;i<n;i++)add(st,i,1,0);
	for(int i=0;i<n;i++)add(n+i+1,en,1,0);
	for(int i=0;i<n;i++)
		for(int j=i+1;j<=n;j++)add(i,n+j,1,read());
	dfs(st,en);
	printf("%d\n",ans);
}

```


---

