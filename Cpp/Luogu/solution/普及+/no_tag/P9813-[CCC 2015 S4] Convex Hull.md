# [CCC 2015 S4] Convex Hull

## 题目描述

给定一个 $n$ 个点，$m$ 条边的无向图，每条边有两个边权 $t_{i}$ 和 $h_{i}$。

你需要找到一条从 $s$ 到 $t$ 的路径，满足路径上边的 $h_{i}$ 之和 $<k$ 且 $t_{i}$ 之和最小，只需要输出这个最小值即可，如果无法找到满足条件的路径，输出 $-1$。

## 说明/提示

**【数据范围】：**

对于 $20\%$ 的数据，$k = 1$，$2 \leq n \leq 200$。

对于另外 $20\%$ 的数据，$k = 1$，$2 \leq n \leq 2 \times 10^{3}$。

对于 $100\%$ 的数据，$0 \leq h_{i} \leq 200$，$1 \leq t_{i} \leq 10^{5}$，$1 \leq k \leq 200$，$2 \leq n \leq 2 \times 10^{3}$，$1 \leq m \leq 10^{4}$，$s \neq t$。

## 样例 #1

### 输入

```
10 4 7
1 2 4 4
1 3 7 2
3 1 8 1
3 2 2 2
4 2 1 6
3 4 1 1
1 4 6 12
1 4```

### 输出

```
7```

## 样例 #2

### 输入

```
3 3 3
1 2 5 1
3 2 8 2
1 3 1 3
1 3```

### 输出

```
-1```

# 题解

## 作者：xpsroc (赞：7)

## Solution

一眼看此题有两个边权好像很复杂。

再看数据范围，直接分层图也炸不了。

按照第二个边权的值分层图，这样按照数据最多分二百层的图。

只需要每次建边时把每层图的起点与加上第二个边权的另一层图的终点建边就好了（当然不要忘记建本题为无向图）。

最后跑一遍 Dijkstra 就可以了。

接下来放代码。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<functional>
#include<queue>
using namespace std;
#define int long long
const int N=2050;
int k,n,m,s,t;
typedef pair<int,int >pr;
priority_queue<pr, vector<pr >, greater<pr> >q;
int h[N*205],d[N*205],vis[N*205];//写分层图别忘了数组范围 
struct ed{
	int ne,to,sum;
}a[40100000];
int cnt=0;
void add(int u,int v,int w){
	a[++cnt].ne=h[u];a[cnt].to=v;a[cnt].sum=w;
	h[u]=cnt;
}
const int Inf=0x7f7f7f7f;
signed main(){
	cin>>k>>n>>m;
	for(int i=1; i<=m; i++){
		int ax,bx,cx,dx;cin>>ax>>bx>>cx>>dx;
		for(int j=0; j<=k; j++){
			add(ax+j*n,bx+j*n+dx*n,cx);//分层图核心思想 
			add(bx+j*n,ax+j*n+dx*n,cx);//建两条边 
		}
	}
	cin>>s>>t;
	//Dijkstra 
	for(int i=1; i<=n*204; i++)d[i]=Inf;
	q.push(make_pair(0,s));d[s]=0;
	while(!q.empty()){
		pr it=q.top();q.pop();
		int kkx=it.first,u=it.second;
		if(vis[u]==1)continue;
		vis[u]=1;
		for(int i=h[u]; i!=0; i=a[i].ne){
			int v=a[i].to;
			if(d[v]>d[u]+a[i].sum){
				d[v]=d[u]+a[i].sum;
				q.push(make_pair(d[v],v));
			}
		}
	}
	int anss=Inf;
	for(int i=0; i<k; i++){
		if(d[t+i*n]!=Inf)anss=min(anss,d[t+i*n]);
	}//判断只需要前k层中有一层的终点能到达就行了。 
	if(anss==Inf)cout<<-1<<endl;
	else cout<<anss<<endl;
}
```


---

## 作者：kaneki_02 (赞：5)

## 思路
这道题显然是一道**最短路**的题目，但是多了一个权值 $h_i$，需要满足路径上 $h_i$ 的和小于 $k$。

那么我们考虑如何解决使 $h_i$ 合法的问题，直接在 Dijkstra 的 $Dis_i$ 数组后**多加一维**，用来保证合法性，每次在松弛的时候选出 $Dis_i,_j$ 中最小的入队即可，一开始我以为这复杂度是过不了的 $O(k(n+m)\log n)$，结果一看范围如此之小，直接就这样写了。

再说一下 $Dis_i,_j$ 数组的转移，对于一条边 $u$ 到 $v$，枚举合法的状态 $j$ 从 $0$ 到 $k-h_u$，若 $Dis_u,_j+t_u<Dis_v,_{j+h_u}$ 那就进行松弛，并**更新此次最小值进行入队**，最后更新答案即可。

## 代码
```c++
#include<bits/stdc++.h>
using namespace std;
#define MAXN 2005
#define MAXM 20005//双向边开两倍
int N,M,K,In1,In2,In3,In4,S,T,head[MAXN],tot,dis[MAXN][205];
int ans=0x3f3f3f3f;
struct tree{
    int v,nxt,t,h;
}E[MAXM];
void build(int u,int v,int t,int h){
    E[++tot]={v,head[u],t,h};
    head[u]=tot;
}
void dj(){
    memset(dis,0x3f,sizeof(dis));//和普通dj一样
    dis[S][0]=0;
    priority_queue<pair<int,int> >q;
    q.push(make_pair(0,S));
    while(!q.empty()){
        int now=q.top().second;q.pop();
        for(int i=head[now];i;i=E[i].nxt){
            int v=E[i].v,t=E[i].t,h=E[i].h;
            int minn=0x3f3f3f3f;
            for(int j=0;j<K-h;j++){//枚举所有合法状态
                if(dis[now][j]+t<dis[v][j+h]){//松弛
                    dis[v][j+h]=dis[now][j]+t;
                    minn=min(minn,dis[v][j+h]);//找到当前点最优解
                }
            }
            if(minn!=0x3f3f3f3f) q.push(make_pair(-minn,v));//不习惯重载，直接放负的
        }
    }
}
int main(){
    scanf("%d%d%d",&K,&N,&M);
    for(int i=1;i<=M;i++){
        scanf("%d%d%d%d",&In1,&In2,&In3,&In4);//用In做变量名是好文明（不会重名
        build(In1,In2,In3,In4);
        build(In2,In1,In3,In4);
    }
    scanf("%d%d",&S,&T);
    dj();
    for(int i=0;i<K;i++)ans=min(ans,dis[T][i]);//找终点的所有合法状态中的最优解
    if(ans!=0x3f3f3f3f){//若不可达
        cout<<ans;
    }else puts("-1");
    return 0;
}
```



 

---

## 作者：过氧化氢_syq0057 (赞：5)

## Solution

很像朴素的最短路，就是多了一维 $h_i$ 的限制。

显然此题可以用分层图解决。

但是众所周知，很多分层图的题都可以用二维 $dis$ 和 $vis$ 跑 dij 来写。

看到 $1 \le k \le 200$ 我们可以想到开数组 $dis[i][j]$ 表示跑到第 $i$ 个点，途经 $h$ 值之和为 $j$ 的最短路径。

这样我们在松弛时加一条限制 $h + edgeh[i]<k$，并把松弛方程改为 $dis[v][h + edgeh[i]] = dis[u][h] + edge[i]$。

其中 $edge[i]$ 表示边的 $t$ 权值，$edgeh[i]$ 表示边的 $h$ 权值。

下面奉上堆优化 dij 的代码。

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <functional>
#include <queue>
using namespace std;
const int N = 10005;
const int M = 20005;
const int P = 205;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
int k, n, m;
int s, t;
int head[N], ver[M], edge[M], edgeh[M], Next[M], tot;
int dis[N][P];
bool vis[N][P];
int ans;
struct node {
	int x;
	int dist;
	int H;
	bool operator < (node s) const {
		return dist > s.dist;
	}
};
void ADD(int x, int y, int z, int h) {
	ver[++tot] = y;
	edge[tot] = z;
	edgeh[tot] = h;
	Next[tot] = head[x];
	head[x] = tot;
}
int Min(int x, int y) {
	return x < y ? x : y;
}
priority_queue<node> Q;
void dijkstra(int st) {
	memset(dis, 0x3f, sizeof(dis));
	dis[st][0] = 0;
	Q.push((node){st, 0, 0});
	int q, u, v, h;
	while (!Q.empty()) {
		u = Q.top().x, h = Q.top().H;
		Q.pop();
		if (vis[u][h]) continue;
		vis[u][h] = 1;
		for (int i=head[u]; ~i; i=Next[i]) {
			v = ver[i];
			if (h + edgeh[i] < k && dis[v][h + edgeh[i]] > dis[u][h] + edge[i]) {
				dis[v][h + edgeh[i]] = dis[u][h] + edge[i];
				if (!vis[v][h + edge[i]]) Q.push((node){v, dis[v][h + edgeh[i]], h + edgeh[i]});
			}
		}
	}
}
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d%d%d", &k, &n, &m);
	int x, y, z, h;
	for (int i=1; i<=m; i++) {
		scanf("%d%d%d%d", &x, &y, &z, &h);
		ADD(x, y, z, h), ADD(y, x, z, h);
	}
	scanf("%d%d", &s, &t);
	dijkstra(s);
	ans = INF;
	for (int i=0; i<k; i++)
		ans = Min(ans, dis[t][i]);
	if (ans != INF) printf("%d\n", ans);
	else printf("-1\n");
	return 0;
}
```

跑的不慢吧，好像比 std 慢一点 /ch。

---

## 作者：Lyco_Reco (赞：3)

读题后不难发现，如果没有 $\sum h_{i}<k$ 的条件，这就是一道最短路的板子题，于是我们考虑如何处理这个条件。

运用分层图最短路的思想，建 $k$ 层图，第 $j$ 层图表示 $\sum h_{i}=j$ 的状态，于是我们以 $t_{i}$ 为边权，根据每条边 $h_{i}$ 的值，在不同层数的点之间建边，最后跑一遍最短路即可。

```cpp
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define int long long
#define maxn 3010
int k,n,m,s,t;
int head[maxn*400],nxt[maxn*1600],to[maxn*1600],val[maxn*1600],tot;
int dis[maxn*400],vis[maxn*400];
struct node{
	int id,dist;
	friend bool operator<(node a,node b){
		return a.dist>b.dist;
	}
};
priority_queue<node> q;
void add(int u,int v,int w){
	to[++tot]=v;
	val[tot]=w;
	nxt[tot]=head[u];
	head[u]=tot;
}
void madoka(){
	memset(dis,0x7f,sizeof(dis));
	dis[s]=0;
	q.push((node){s,0});
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(vis[u]){
			continue;
		}
		vis[u]=1;
		for(int i=head[u];i;i=nxt[i]){
			int v=to[i];
			if(dis[v]>dis[u]+val[i]){
				dis[v]=dis[u]+val[i];
				q.push((node){v,dis[v]});
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>k>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,t,h;
		cin>>u>>v>>t>>h;
		for(int j=0;j+h<k;j++){
			add(u+j*n,v+(j+h)*n,t);
			add(v+j*n,u+(j+h)*n,t);
		}
	}
	cin>>s>>t;
	madoka();
	int ans=0x7f7f7f7f;
	for(int i=0;i<k;i++){
		ans=min(ans,dis[i*n+t]);
	}
	cout<<(ans>=1e9? -1:ans);
	return 0;
}
```


---

## 作者：Ifyoung (赞：2)

[$\Large \text{题面}$](https://www.luogu.com.cn/problem/P9813) $\Large \text{以及}$ [$\Large \text{PDF视图}$](https://dmoj.ca/problem/ccc15s4/pdf)

[别样的阅读体验](https://www.cnblogs.com/Ifyoung/p/17789267.html) / [别样的阅读体验](https://ifyoungy.github.io/2023/10/26/P9813-Convex-Hull-%E9%A2%98%E8%A7%A3/)

题目内容说的很直白了，接下来讲解做法。

# 思路

可以发现这是一个最短路问题，在最基础的模板上增加了一个“路径上边的 $h_i$ 之和 $<k$”的限制。

为方便讲解，我们将“路径上边的 $h_i$ 之和”用一个字母 $p$ 代替。

考虑仍然使用 Dijkstra 算法（堆优化），并且进行一些细微的改动。

首先，$dis$ 数组要增加一维，即由 $dis[i]$ 变成 $dis[i][j]$，同时，其定义变成 **从起点到节点 $i$，$p$ 恰好为 $j$ 的最短路径**。

下面考虑对于算法实现过程的改动，具体表现为 **更新** 时的改动。

考虑当前点的“答案”，即当前点的 $p$ 为某个小于 $k$ 的值时距离起点的距离，是如何得到的。

可以类比一下 **背包** 的思想，会发现当前点的“答案”是通过相邻节点 **对应位置** 上的答案加上两点之间的距离转移来的。

那么什么是“**对应位置**”呢？

这个“位置”指的是下标，两点之间的下标应相差一个相应的 $h$。

下面是形式化一些的表达：

假设当前的节点为 $u$，遍历到的相邻节点为 $v$，那么 **更新** 的方程为 $dis[v][i + h[u]]=dis[u][i]+t[u]$，其中 $0 \leq i < k - h[u]$（$i$ 不能小于 $0$，同时 $i+h[u]$ 要小于 $k$）。

直观地讲就是 **下标** 增加了一个 $h[u]$，**值** 增加了一个 $t[u]$。（不难理解了吧……）

# 实现

$Code$

```
#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> PII;

const int K = 210, N = 2e3 + 5, M = 1e4 + 5; // 数据范围

int k, n, m, s, t;
int he[N], tot;
struct edge {
	int to, nxt, t, h;
} e[M << 1]; // 双向边
int dis[N][K];
bool vis[N];
int ans = 0x3f3f3f3f; // 初始化成最大值，最终找到最小值

void add(int u, int v, int t, int h) {
	e[ ++ tot] = (edge) {v, he[u], t, h};
	he[u] = tot;
}

void dijkstra(int s) {
	memset(dis, 0x3f, sizeof dis); // 类似于普通的 Dijkstra 中的初始化
	dis[s][0] = 0;
	priority_queue <PII, vector <PII>, greater <PII> > q; // 小根堆
	q.push({0, s});
	while (q.size()) {
		auto p = q.top();
		q.pop();
		int u = p.second;
		for (int i = he[u]; i; i = e[i].nxt) {
			int v = e[i].to, h = e[i].h, t = e[i].t;
			int minn = 0x3f3f3f3f; // 要取一个“最小值”
			for (int j = 0; j < k - h; j ++ ) { // 循环区间合法
				if (dis[v][j + h] > dis[u][j] + t) {
					dis[v][j + h] = dis[u][j] + t;
					minn = min(minn, dis[v][j + h]); // 要在更新后的数据中找到“最小值”，以进行接下来的更新
				}
			}
			if (minn != 0x3f3f3f3f) // 如果“更新成功”
                q.push({minn, v}); // 那么就把“最小值”放进堆里，进行接下来的更新
		}
	}
}

int main() {
	cin >> k >> n >> m;
	for (int i = 1, u, v, t, h; i <= m; i ++ ) {
		cin >> u >> v >> t >> h;
		add(u, v, t, h), add(v, u, t, h); // 建双向边
	}
	cin >> s >> t;
	dijkstra(s); // 从起点开始
	for (int i = 0; i < k; i ++ ) ans = min(ans, dis[t][i]); // 在 p 所有小于 k 的答案中找最小值
	if (ans >= 0x3f3f3f3f / 2) // 一种技巧，即起点并不能通向终点，但终点会被其旁边的点更新
        puts("-1"); // 但是又不会变小太多，所以用正无穷的一半即可完成判定
	else  cout << ans << endl;
	return 0;
}
```

---

## 作者：xiaoming007 (赞：1)

观察数据范围发现 $k$ 很小啊，$n$ 也只有 $2 \times 10^3$，于是可以定义数组 $dis_{x,y}$ 表示从 $s$ 到 $x$ 所选择路径 $h_i$ 总和为 $y$ 的的最小 $\sum t_i$ 值，于是就转化成了一个模板的分层图问题。

具体地，从 $dis_{s,0}$ 出发，此处 $t_i$ 总和为 $0$，然后对于每一条连出来的边，将第二维的 $h_i$ 累加，若超过 $k$，则不选用，若没超过 $k$，说明可以经过，与原本的 $dis$ 取 $\min$ 即可。

答案为 $\min _{i=0}^{k} dis_{t,i}$，注意答案是正无穷时无解。

复杂度 $O(nk \log nk)$，此处默认 $n,m$ 同阶。

```cpp
#include <queue>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
#define open(x) freopen(#x".in", "r", stdin);freopen(#x".out", "w", stdout);
#define close fclose(stdin);fclose(stdout);
#define all(x) x.begin(), x.end()
namespace FastIO {
	template <typename T = int>
	inline T read() {
		T s = 0, w = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') w = -1;
			c = getchar();
		}
		while (isdigit(c)) s = (s << 1) + (s << 3) + (c ^ 48), c = getchar();
		return s * w;
	}
	template <typename T>
	inline void read(T &s) {
		s = 0;
		int w = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') w = -1;
			c = getchar();
		}
		while (isdigit(c)) s = (s << 1) + (s << 3) + (c ^ 48), c = getchar();
		s = s * w;
	}
	template <typename T, typename... Args> inline void read(T &x, Args &...args) {
		read(x), read(args...);
	}
	template <typename T>
	inline void write(T x, char ch) {
		if (x < 0) x = -x, putchar('-');
		static char stk[25];
		int top = 0;
		do {
			stk[top++] = x % 10 + '0', x /= 10;
		} while (x);
		while (top) putchar(stk[--top]);
		putchar(ch);
		return;
	}
} using namespace FastIO;
#define fi first
#define se second
using pii = pair<int, int>;
using piii = pair<int, pii>;
int dis[2010][201];
bool vis[2010][201];
struct node {
	int to, t, h;
};
vector<node> g[2010];
signed main() {
	int k = read(), n = read(), m = read(), s, t;
	while (m--) {
		int a, b, c, d;
		read(a, b, c, d);
		g[a].push_back({b, c, d});
		g[b].push_back({a, c, d});
	}
	priority_queue<piii, vector<piii>, greater<piii> > q; // t 作排序值 
	read(s, t);
	for (int i = 1; i <= n; ++i) for (int j = 0; j <= k; ++j) dis[i][j] = 0x3f3f3f3f;
	q.push({0, {0, s}}); // t, h, s
	dis[s][0] = 0;
	while (!q.empty()) {
		piii tp = q.top();
		q.pop();
		if (vis[tp.se.se][tp.se.fi]) continue;
		vis[tp.se.se][tp.se.fi] = 1;
		//cout << tp.se.se << '\n';
		for (const auto&i : g[tp.se.se]) {
			if (tp.se.fi + i.h < k && tp.fi + i.t <= dis[i.to][tp.se.fi + i.h]) {
				dis[i.to][tp.se.fi + i.h] = tp.fi + i.t;
				q.push({tp.fi + i.t, {tp.se.fi + i.h, i.to}});
			}
		}
	}
	int ans = 0x3f3f3f3f;
	for (int i = 0; i <= k; ++i) ans = min(ans, dis[t][i]);
	write(ans == 0x3f3f3f3f ? -1 : ans, '\n');
	return 0;
}
```

---

## 作者：Bulyly (赞：0)

简单题。

我们发现 $k$ 的范围很小，结合 $n$ 的范围很容易想到拆点。进一步发现对于到每个点当前 $h$ 的和为 $j$ 时，我们考虑的最优状态即 $t$ 最小。于是做法就出来了，跑分层图即可。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const int N=2e3+10,M=2e4+10;
int n,m,k,s,t,d[N][210];
int e[M],ne[M],h[N],w1[M],w2[M],idx;
bool st[N][210];

inline void add(int a,int b,int c,int d) {
	e[++idx]=b,ne[idx]=h[a],w1[idx]=c,w2[idx]=d,h[a]=idx;
}

struct node {
	int w,f,id;
	bool operator<(const node &t) const {
		return w>t.w;
	}
};

inline void dijkstra() {
	memset(d,0x3f,sizeof d);
	memset(st,0,sizeof st);
	priority_queue<node> q;
	q.push({0,0,s});d[s][0]=0;
	while(q.size()) {
		node u=q.top();q.pop();
//		cout<<u.id<<"\n";
		if(st[u.id][u.f]) continue;
		st[u.id][u.f]=1;
		for(int i=h[u.id];i;i=ne[i]) {
			int v=e[i];
			if(w2[i]+u.f>=k) continue;
			if(d[v][u.f+w2[i]]>u.w+w1[i]) d[v][u.f+w2[i]]=u.w+w1[i],q.push({u.w+w1[i],u.f+w2[i],v});
		}
	}
	
}

int main() {
	scanf("%d%d%d",&k,&n,&m);
	for(int i=1;i<=m;i++)  {
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		add(a,b,c,d),add(b,a,c,d);
	}
	scanf("%d%d",&s,&t);	
	dijkstra();
	int ans=1e9;
	for(int i=0;i<k;i++) ans=min(ans,d[t][i]);
	if(ans==1e9) puts("-1");
	else cout<<ans<<"\n";
	return 0;             		
}
```

---

## 作者：UniGravity (赞：0)

## Solution P9813 [CCC 2015 S4] Convex Hull

~~因为 CSP-J 2023 T4 考了分层图，所以这道题一眼就看出来了...~~

### 思路分析
观察到 $h_i$ 的和必须 $<k$ ，而 $k$ 和 $n$ 都很小，显然想到分层图。

那么怎么分呢？

设 $(i,j)$ 表示到达点 $i$，$h_i$ 的和为 $j$，那么这样连边即可：$(u_i,j)\leftrightarrow(v_i,j+h_i)(0\le j<k-h_i)$

此时在新图上跑一遍最短路就结束了，统计时记得特判。

### 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 400005, INF = 0x3f3f3f3f;

int k, n, m;
vector< pair< int, int > > edge[N];
int s, t;

int dis[N];
bool vis[N];

inline void dijkstra() {
	memset(dis, INF, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	
	priority_queue< pair< int, int >, vector< pair< int, int > >, greater< pair< int, int > > > q;
	
	dis[s] = 0;
	q.push({0, s});
	
	int x, y, w;
	while (!q.empty()) {
		x = q.top().second;
		q.pop();
		if (vis[x]) continue;
		vis[x] = true;
		
		for (int i = 0; i < edge[x].size(); i++) {
			y = edge[x][i].first;
			w = edge[x][i].second;
			if (dis[x] + w < dis[y]) {
				dis[y] = dis[x] + w;
				q.push({dis[y], y});
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &k, &n, &m);
	int u, v, w, h;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d %d", &u, &v, &w, &h);
		for (int j = 0; j + h < k; j++) {
			edge[u + j * n].push_back({v + (j + h) * n, w});
			edge[v + j * n].push_back({u + (j + h) * n, w});
		}
	} 
	scanf("%d %d", &s, &t);
	
	dijkstra();
	int ans = INF;
	for (int i = 0; i < k; i++) {
		ans = min(ans, dis[t + i * n]);
	}
	if (ans != INF) printf("%d", ans);
	else printf("-1");
	return 0;
}
 
```

---

