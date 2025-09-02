# 【MX-X5-T3】「GFOI Round 1」Cthugha

## 题目背景

原题链接：<https://oier.team/problems/X5D>。

---

> [Cthugha - USAO](https://music.163.com/#/song?id=1833853372)

## 题目描述

给定一张 $n \times m$ 的网格图，行编号为 $1,2,\dots ,n$，列编号为 $1,2,\dots ,m$。我们用 $(i, j)$ 来描述第 $i$ 行第 $j$ 列的格子。每个格子有一个整数权值 $a_{i,j}$，**注意格子的权值可以是负数**。

给定 $q$ 个人位于网格图上，第 $i$ 个人的初始位置在 $(x_i, y_i)$，**注意不保证每个人初始位置互不相同**。

定义某人**走一步**为：若这个人当前坐标在 $(x,y)$，则将该人移动至 $(x+1,y),(x-1,y),(x,y+1),(x,y-1)$ 其中之一。设移动后到达 $(x^{\prime},y^{\prime})$，此时需要满足 $1\leq x^{\prime}\leq n,1\leq y^{\prime}\leq m$。

在任意时刻，允许任意两个人位于同一个格子。

定义一个人的**权值**为其走若干步后所有经过的格子的权值和（包括起点和终点），注意若一个格子被经过 $k$ 次则其权值需要被累加 $k$ 次。

特别地，若一个人没有走，则其**权值**为其初始位置格子的权值。

定义**总权值**为每个人走若干步数，所有人权值的最大值。

求最终所有人都走到同一个格子的最小**总权值**，或报告不存在最小**总权值**（即最小总权值为负无穷）。

## 说明/提示

**【样例解释 #1】**

总权值最小的情况是第一个人不走，此时经过点只有 $(2,2)$，所以答案为 $a_{2,2}=5$。

**【样例解释 #2】**

总权值最小的情况是两个人走到 $(2,3)$，路线分别为 $(2,2)\rightarrow (2,3)$ 和 $(3,3) \rightarrow (2,3)$，答案为 $\max(a_{2,2}+a_{2,3},a_{3,3}+a_{2,3}) = \max(11, 15) = 15$。

**【样例解释 #5】**

总权值最小的情况是三个人都没有走，权值都为 $a_{1,1}=-1$，答案即为 $-1$。

**【样例解释 #6】**

容易证明最小总权值为负无穷，所以输出 `No`。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | $n\times m \leq $| $q\leq $ | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $9$ | $9$ | 无 | $11$ |
| $2$ | $10^5$ | $1$ | 无 | $3$ |
| $3$ | $10^5$ | $50$ | A | $24$ |
| $4$ | $10^3$ | $50$ | 无  | $21$ |
| $5$ | $10^5$ | $50$ | 无 | $41$ |

- 特殊性质 A：$a_{i,j} \geq 1$。

对于所有数据，满足 
$1\leq n,m\leq 10^5$，$1\leq n\times m\leq 10^5$，$1\leq q\leq 50$，$1 \le x_i \le n$，$1 \le y_i \le m$，$1\leq |a_{i,j}|\leq 10^9$。

## 样例 #1

### 输入

```
3 3 1
1 2 3
4 5 6
7 8 9
2 2```

### 输出

```
5```

## 样例 #2

### 输入

```
3 3 2
1 2 3
4 5 6
7 8 9
2 2
3 3```

### 输出

```
15```

## 样例 #3

### 输入

```
3 3 3
1 4 -3
4 -1 4
7 8 9
1 1
2 2
3 3```

### 输出

```
10```

## 样例 #4

### 输入

```
3 3 9
1 4 -3
4 -1 4
7 8 9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3```

### 输出

```
11```

## 样例 #5

### 输入

```
3 3 3
-1 4 4
4 -1 4
7 8 -1
1 1
1 1
1 1 ```

### 输出

```
-1```

## 样例 #6

### 输入

```
3 3 3
1 4 -5
4 -1 4
7 8 9
1 1
2 2
3 3```

### 输出

```
No```

# 题解

## 作者：Aventurine_stone (赞：7)

### 前言：
我这道题用的 spfa 做的，有人可能会说 spfa 肯定会被后来的 hack 数据卡爆。但是仔细看题会发现，这道题是构造不了菊花图的，那么加上 SLF 优化即可通过此题，当然我又额外加了 LLL 优化，直接跑得飞起。  
[AC 记录。](https://www.luogu.com.cn/record/179009691)
## 1. 题目分析
看到这道题，我首先想到的便是先用 spfa 判一下负环，再在每个网格点上都跑一次 spfa，从而求出最小总权值。但这样时间复杂度肯定爆炸，我们可以反过来想。
## 2. 题目做法
用 spfa 判负环是不需要的，我们只需要判断网格中相邻的两个值加起来是否小于 $0$ 便可，若有小于 $0$ 的便存在负环。简单证明一下，如果有三个格子，两个负格子中间夹一个正格子，并且两个负数的和的绝对值大于此正数，但每个负数的绝对值都小于此正数，这种情况下，如果想要反复跑这三个点，那么之后的情况便是走一次负格子回过来必定会再跑一次正格子，权值会越跑越大。其他情况也都是这个情况和两数相加是否小于零情况的延伸，证毕。  
因为 $q$ 很小，我们只需要以每个人的位置为源点，每个都跑一遍 spfa 即可。然后每个点的总权值都取每个人走到此点的最短距离的最大值。  
最后输出所有点的总权值的最小值即可。
## 3. 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
int n,m,q,z;
#define pot(x,y) (x-1)*m+y
using namespace std;
const int N=100010,M=400010;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
		c=='-'?f=-1:1,c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x*f;
}
int head[N],ne[M],e[M],w[M],idx;
inline void add(int x,int y,int z)
{
	ne[++idx]=head[x];
	head[x]=idx;
	e[idx]=y,w[idx]=z;
}
int a[N],t;
ll dist[N],mx[N];
bool vis[N];
deque<int>d;
ll sum,num;
void spfa(int x)
{
	for(int i=1;i<=z;i++)
		dist[i]=LONG_LONG_MAX,vis[i]=0;
	dist[x]=0;
	d.push_front(x);
	num=1;
	while(!d.empty())
	{
		t=d.front();
		d.pop_front();
		if(num&&dist[t]>sum/num)//LLL优化 
		{
			d.push_back(t);
			continue;
		}
		sum-=dist[t],num--;
		vis[t]=0;
		for(int i=head[t];i;i=ne[i])
		{
			int c=e[i];
			ll s=dist[t]+w[i];
			if(s<dist[c])
			{
				if(vis[c])
					sum-=dist[c]-s;
				dist[c]=s;
				if(!vis[c])
				{
					vis[c]=1;
					sum+=s,num++;
					if(!d.empty()&&s<=dist[d.front()])//SLF优化 
						d.push_front(c);
					else
						d.push_back(c); 
				}
			}
		}
	}
	for(int i=1;i<=z;i++)
		mx[i]=max(mx[i],dist[i]+a[i]);
}
inline void end()
{
	printf("No");
	exit(0);
}
ll mn;
int x,y;
int main()
{
	n=read(),m=read(),q=read();
	z=n*m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			t=pot(i,j);
			a[t]=read();
			if(j>1)
			{
				x=pot(i,j-1);
				if(a[x]+a[t]<0)
					end();
				add(t,x,a[t]);
			}
			if(i>1)
			{
				x=pot(i-1,j);
				if(a[x]+a[t]<0)
					end();
				add(t,x,a[t]);
			}
			if(j<m)
				add(t,pot(i,j+1),a[t]);
			if(i<n)
				add(t,pot(i+1,j),a[t]);
		}
	}
	for(int i=1;i<=z;i++)
		mx[i]=-LONG_LONG_MAX;
	while(q--)
	{
		x=read(),y=read();
		spfa(pot(x,y));
	}
	mn=LONG_LONG_MAX;
	for(int i=1;i<=z;i++)
		mn=min(mn,mx[i]);
	printf("%lld",mn);
	return 0;
}
```

---

## 作者：w9095 (赞：6)

[P11131 【MX-X5-T3】「GFOI Round 1」Cthugha](https://www.luogu.com.cn/problem/P11131)

有意思的最短路题目，需要对迪杰斯特拉算法有深入的理解。

首先，不存在最小值的条件是相邻的两个格子加起来值小于 $0$，此时在这两个格子之间反复横跳，就没有最小值。

观察到 $q$ 很小，所以我们把网格建成一个图，对于每一个人跑一遍到每一个点的最短路，然后按照对于每一个点取所有人的最大值。统计答案是取最小值即可。

注意有负权边，而 SPFA 死了，所以考虑迪杰斯特拉。如果你对迪杰斯特拉有深入了解，直接把 SPFA 换成迪杰斯特拉，然后就过了。

因为迪杰斯特拉的正确性基于第一次取到这个点是就是最优答案，而在这个图中如果出去绕一下回来距离变小了，证明不存在最小值。如果存在最小值，绕回来之后一定距离变大，满足条件。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge
{
	long long v,nxt,d;
}e[2000000];
long long n,m,t,l,r,h[200000],a[200000],dis[200000],ans[200000],cnt=0;
bool vis[200000];
priority_queue<pair<long long,long long> >q;
void end()
{
	printf("No\n");
	exit(0);
}

long long has(long long x,long long y)
{
	return (x-1)*m+y;
}

void add_edge(long long u,long long v,long long d)
{
	e[++cnt].nxt=h[u];
	e[cnt].v=v;
	e[cnt].d=d;
	h[u]=cnt;
}

int main()
{
	scanf("%lld%lld%lld",&n,&m,&t);
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++)
	        {
	    	scanf("%lld",&a[has(i,j)]);
	    	if(i!=1&&a[has(i,j)]+a[has(i-1,j)]<0)end();
	    	if(j!=1&&a[has(i,j)]+a[has(i,j-1)]<0)end();
	        }
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++)
	        {
	        if(i!=1)add_edge(has(i,j),has(i-1,j),a[has(i-1,j)]);
	        if(j!=1)add_edge(has(i,j),has(i,j-1),a[has(i,j-1)]);
	        if(i!=n)add_edge(has(i,j),has(i+1,j),a[has(i+1,j)]);
	        if(j!=m)add_edge(has(i,j),has(i,j+1),a[has(i,j+1)]);
			}
	for(int i=1;i<=n*m;i++)ans[i]=-1e18;
	for(int i=1;i<=t;i++)
	    {
	    scanf("%lld%lld",&l,&r);
	    for(int i=1;i<=n*m;i++)dis[i]=1e18,vis[i]=0;
	    dis[has(l,r)]=a[has(l,r)],q.push(make_pair(-dis[has(l,r)],has(l,r)));
	    while(!q.empty())
	       {
	       	long long x=q.top().second;
	       	q.pop();
	       	if(vis[x])continue;
	       	vis[x]=1;
	       	for(int i=h[x];i;i=e[i].nxt)
	       	    if(dis[e[i].v]>dis[x]+e[i].d)dis[e[i].v]=dis[x]+e[i].d,q.push(make_pair(-dis[e[i].v],e[i].v));
		   }
		for(int i=1;i<=n*m;i++)ans[i]=max(ans[i],dis[i]);
		}
	long long mi=1e18;
	for(int i=1;i<=n*m;i++)mi=min(mi,ans[i]);
	printf("%lld\n",mi);
	return 0;
}
```

---

## 作者：VitrelosTia (赞：4)

以下令 $N = n \times m$。

暴力就是枚举终点，对于每个人跑单源最短路，但是有负权，需要使用 spfa，那这样的复杂度是 $O(N^2q)$ 的，无法通过。 

我们不妨把目光转到 `No` 的情况，显然是跑最短路的时候出现了负环，但是我们知道跑负环的复杂度非常地高，然后我们发现只要相邻的两个数的是负数就可以在这里来回走，也就是负环了。

那其实也就解决了一个问题，就是有负权，怎么解决的呢？就是对于两个相邻的点 $x, y$ 之间连 $w_x + w_y$ 的边，由于这个边权是负数的情况都被判掉了，那这样就都是正权边了。那实际原图上的答案也是简单的，容易发现一条路径上开头和结尾算了一次权，其他都是两次，处理是简单的。这样我们运用 dijkstra 就可以做到 $O(N \log N q)$ 的复杂度了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef pair <int, int> pii;

const int N = 1e5 + 5, K = 55;
const int dic[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
int n, m, k, w[N];
int id(int x, int y) { return (x - 1) * m + y; }
pii pos(int o) { return (o % m == 0) ? make_pair(o / m, m) : make_pair(o / m + 1, o % m); }

struct Node {
	int u, l;
	bool operator < (const Node &x) const { return l > x.l; }
}; priority_queue <Node> q;
int dis[K][N]; bool vis[N];
void dij(int s, int o) {
	memset(vis, false, sizeof vis); memset(dis[o], 0x3f, sizeof dis[o]);
	q.push({s, dis[o][s] = 0});
	while (!q.empty()) {
		int u = q.top().u, x = pos(u).first, y = pos(u).second; q.pop();
		if (vis[u]) continue; vis[u] = true;
		for (int i = 0; i < 4; i++) {
			int dx = x + dic[i][0], dy = y + dic[i][1], v = id(dx, dy);
			if (dx < 1 || dx > n || dy < 1 || dy > m) continue;
			if (dis[o][v] > dis[o][u] + w[u] + w[v]) q.push({v, dis[o][v] = dis[o][u] + w[u] + w[v]});
		}
	}
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
		cin >> w[id(i, j)];
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
		int u = id(i, j);
		for (int o = 0; o < 4; o++) {
			int dx = i + dic[o][0], dy = j + dic[o][1], v = id(dx, dy);
			if (dx < 1 || dx > n || dy < 1 || dy > m) continue;
			if (w[u] < 0 && w[u] + w[v] < 0) return cout << "No", 0;
		}
	}
	for (int o = 1, x, y; o <= k; o++) {
		cin >> x >> y;
		dij(id(x, y), o);
		for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
			dis[o][id(i, j)] = (dis[o][id(i, j)] + w[id(x, y)] + w[id(i, j)]) / 2; 
	}
	int ans = LLONG_MAX;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
		int u = id(i, j), s = LLONG_MIN;
		for (int o = 1; o <= k; o++) s = max(s, dis[o][u]);
		ans = min(ans, s);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：happybob (赞：2)

SPFA 已经复活了。

先判负环，容易发现如果存在两个相邻点的点权和为负数则有负环。

然后需要对 $q$ 个起点做网格图最短路。鉴于我不会 Dijkstra，直接对每个点开始做 SPFA 即可。

但是这样显然会被卡。注意到有个优化是，加入队列时，如果比队头的最短路距离更小则加入队头，否则加入队尾。直接使用这个即可通过，只是有点慢。

考虑另一个优化，若某个点进入队列时进队次数在 $[L,R]$ 内，则加入队首，否则加入队尾。取 $L=2,R=\sqrt{V}$。

同时使用两种优化，可以在 $600$ 毫秒内通过。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 1e5 + 5;

int n, m, q, L = 2, R;

array<vector<int>, N> a, cnt, vis;
array<vector<ll>, N> dist, maxn;

array<int, 4> dx = { 0, 0, -1, 1 };
array<int, 4> dy = { -1, 1, 0, 0 };
ll ans = (ll)1e18;

void spfa(int x, int y)
{
	for (int i = 1; i <= n; i++)
	{
		fill(dist[i].begin(), dist[i].end(), (ll)1e18);
		fill(cnt[i].begin(), cnt[i].end(), 0);
		fill(vis[i].begin(), vis[i].end(), 0);
	}
	deque<pair<int, int>> q;
	q.emplace_back(x, y);
	dist[x][y] = a[x][y];
	cnt[x][y] = 1;
	while (q.size())
	{
		auto [x, y] = q.front();
		vis[x][y] = 0;
		q.pop_front();
		for (int k = 0; k < 4; k++)
		{
			int nx = x + dx[k], ny = y + dy[k];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && dist[nx][ny] > dist[x][y] + a[nx][ny])
			{
				dist[nx][ny] = dist[x][y] + a[nx][ny];
				if (!vis[nx][ny])
				{
					vis[nx][ny] = 1;
					cnt[nx][ny]++;
					if (q.empty()) q.emplace_back(nx, ny);
					else
					{
						if (dist[nx][ny] < dist[q.front().first][q.front().second]) q.emplace_front(nx, ny);
						else
						{
							if (cnt[nx][ny] >= L && cnt[nx][ny] <= R) q.emplace_front(nx, ny);
							else q.emplace_back(nx, ny);
						}
					}
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++)
	{
		a[i].resize(m + 1), dist[i].resize(m + 1), maxn[i].resize(m + 1);
		fill(dist[i].begin(), dist[i].end(), (ll)1e18);
		fill(maxn[i].begin(), maxn[i].end(), (ll)-1e18);
		for (int j = 1; j <= m; j++) cin >> a[i][j];
		cnt[i].resize(m + 1), vis[i].resize(m + 1);
	}
	R = (int)sqrt(n * m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				int ni = i + dx[k], nj = j + dy[k];
				if (ni >= 1 && ni <= n && nj >= 1 && nj <= m && a[i][j] + a[ni][nj] < 0)
				{
					cout << "No\n";
					return 0;
				}
			}
		}
	}
	for (int i = 1; i <= q; i++)
	{
		int x, y;
		cin >> x >> y;
		spfa(x, y);
		for (int j = 1; j <= n; j++)
		{
			for (int k = 1; k <= m; k++) maxn[j][k] = max(maxn[j][k], dist[j][k]);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++) ans = min(ans, maxn[i][j]);
	}
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：aCssen (赞：1)

### Solution
根据题意，答案为 $\min_{1 \le i \le n,1 \le j \le m}\max_{1 \le k \le q}dis_{k,i,j}$。其中 $dis_{k,i,j}$ 为 $k$ 这个人到 $(i,j)$ 格子的最短路。

考虑何时答案为 No。容易发现如果相邻两个数的和 $<0$ 那么我可以不断走这两个数进而达到负无穷。否则所有相邻数的和都为非负数，那么考虑对于可以互相到达的两个点 $(i_1,j_1),(i_2,j_2)$ 连边，边权设为 $a_{i_1,j_1}+a_{i_2,j_2}$。这样是一张边权非负的图，可以直接跑 Dijkstra。

这样两个点间的最短路是多少呢？考虑一条路径，除起点和终点外，每个点的权值在它的前驱和后继结点各贡献一次，所以将这个最短路的值加上起点，终点的权值后除二即是真实的最短路。

这个题只保证了 $nm\le 10^5$，并没有保证 $n,m$ 的大小，这可怎么办呢？对于最短路的部分。我们可以将 $(i,j)$ 的编号设为 $(i-1)m+j$，这其实就是从上到下，从左到右依次编号。对于输入的部分，可以用 vector 存储数据，使用时仅需调用 `.resize(m+1)` 即可生成一个长度为 $m+1$，下标在 $[0,m]$ 的数组。

### Code

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
typedef long long ll;
namespace FastIO{
	template<typename T=int> T read(){
		T x=0;int f=1;char c=getchar();
		while(!isdigit(c)){if(c=='-') f=~f+1;c=getchar();}
		while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
		return x*f;
	}
	template<typename T> void write(T x){
		if(x<0){putchar('-');x=-x;}
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	template<typename T> void Write(T x,char c='\n'){write(x);putchar(c);}
}
using namespace FastIO;
const int maxn=1e5+5;
const int maxm=4e5+5;
int head[maxn],ver[maxm],nxt[maxm],edge[maxm],Sx[55],Sy[55],dx[5]={0,-1,0,1,0},dy[5]={0,0,-1,0,1},tot,n,m;
vector<int>a[maxn];
ll dis[55][maxn];
bool vis[maxn];
void add_edge(int u,int v,int w){
	ver[++tot]=v,edge[tot]=w,nxt[tot]=head[u],head[u]=tot;
}
priority_queue<pair<ll,int> >q;
void dijkstra(int s,int id){
	memset(dis[id],0x3f,sizeof(dis[id]));
	memset(vis,false,sizeof(vis));
	dis[id][s]=0;q.push(make_pair(0,s));
	while(!q.empty()){
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i],z=edge[i];
			if(dis[id][x]+z<dis[id][y]){
				dis[id][y]=dis[id][x]+z;
				q.push(make_pair(-dis[id][y],y));
			}
		}
	}
}
int main(){
	int n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++) a[i].resize(m+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) a[i][j]=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=1;k<=4;k++){
				int x=i+dx[k],y=j+dy[k];
				if(x>=1&&x<=n&&y>=1&&y<=m){
					if(a[i][j]+a[x][y]<0){
						printf("No");
						return 0;
					}
					add_edge((i-1)*m+j,(x-1)*m+y,a[i][j]+a[x][y]);
				}
			}
		}
	}
	for(int i=1;i<=q;i++){
		Sx[i]=read(),Sy[i]=read();
		dijkstra((Sx[i]-1)*m+Sy[i],i);
	}
	ll ans=9e18;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ll val=-9e18;
			for(int k=1;k<=q;k++) val=max(val,(dis[k][(i-1)*m+j]+a[Sx[k]][Sy[k]]+a[i][j])/2);
			ans=min(ans,val);
		}
	}
	write(ans);
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11131)

## 思路

预处理出每个人到每个点的最短路，如果图中**不存在负环**，那么每个人到任意一点的最小值一定是确定的。然后遍历每个点，找距离每个人最大值最小的那个点。

跑这种情况，我们选择迪杰斯特拉算法，时间复杂度 $\mathcal{O}(nmq\log nm)$，在本题 $1\le nm\le 10^5,1\le q\le 50$ 的范围内可以跑过。

接下来我们考虑负环。众所周知，迪杰斯特拉不能判断负环，所以这里我们可以采用一种“逃课”的方法——点标记，来判断。

显然，在迪杰斯特拉算法中，每个点不会遍历很多遍。这时候我们每次遍历到一个点，就让这个点的标记 $-1$，如果这个点标记等于 $0$ 了，说明遍历次数太多，很显然已经进负环了。这时候我们直接输出 `No`，结束整个程序。

- 记得开 `long long`。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define fi first
#define se second
using namespace std;
ll read(){
	ll k=0;bool flag=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')flag=0;c=getchar();}
	while(isdigit(c)){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	if(flag)return k;return -k;
}
const int N=1e5+10,M=60;
ll n,m,q,x[N],y[N],ans=LLONG_MAX;
vector<ll>dis[M][N],a[N];//用 vector 存这种图很方便。
const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};
vector<int>vis[N];
void dij(int id){
	priority_queue<pair<ll,pii>,vector<pair<ll,pii>>,greater<pair<ll,pii>>>pq;
	dis[id][x[id]][y[id]]=a[x[id]][y[id]];
	pq.push({0,{x[id],y[id]}});
	for(int i=1;i<=n;++i){
		vis[i].clear();
		for(int j=0;j<=m;++j)vis[i].pb(20);//设定一个合适的标记值。
	}
	while(pq.size()){
		auto k=pq.top().se;
		pq.pop();
		if(!--vis[k.fi][k.se]){//进负环。
			cout<<"No";
			exit(0);
		}
		for(int i=0;i<4;++i){
			int xx=k.fi+dx[i];
			int yy=k.se+dy[i];
			if(xx<1||xx>n||yy<1||yy>m)continue;
			ll w=a[xx][yy];
			if(dis[id][xx][yy]>dis[id][k.fi][k.se]+w){
				dis[id][xx][yy]=dis[id][k.fi][k.se]+w;
				pq.push({dis[id][xx][yy],{xx,yy}});
			}
		}
	}
	return ;
}
signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;++i){
		a[i].pb(0);//占位，让他下标从 1 开始。
		for(int j=1;j<=m;++j)a[i].pb(read());
	}
	for(int i=1;i<=q;++i){
		x[i]=read(),y[i]=read();
		for(int j=1;j<=n;++j){
			for(int k=0;k<=m;++k)dis[i][j].pb(1e18);
		}
	}
	for(int i=1;i<=q;++i)dij(i);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			ll tmp=LLONG_MIN;
			for(int k=1;k<=q;++k)tmp=max(dis[k][i][j],tmp);
			ans=min(ans,tmp);
		}
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/178790239)

---

## 作者：zhoumurui (赞：0)

### 题面展示

给定一张 $n \times m$ 的网格图，每个格子有一个整数权值 $a_{i,j}$。

定义两个格子之间的距离为从一个格子到另一个格子经过的所有格子（包括起点和终点）的权值和，多次经过同一个格子时权值重复计算。

给定网格图上 $q$ 个点，找到图上的一个点，最小化该点到 $q$ 个点的距离之和并输出。

如果这个距离可以无限小，输出 `No`。


### 解题思路

本题解为 spfa 玄学优化做法。

容易想到最短路。

跑 dijkstra 算法只能获得 $24$ 分，因为有负边权。spfa 算法的得分则是 $33$ 分，这年头谁不顺手卡个 spfa。~~不卡 spfa 这题就成黄题了。~~

本题解对 spfa 进行两个玄学优化。

- 将一个点插入队尾时，如果起点到队头点的距离比到该点的距离更大，则改为将该点插入队头。

- 将一个点入队完毕后，如果起点到队头的距离比到队尾的距离大，交换队头和队尾。

然后成功通过此题。


### 核心代码展示

```cpp
void spfa(int st){
    deque<int> q;
    q.push_front(st);
    memset(dis,0x3f,sizeof(dis));
    memset(cnt,0,sizeof(cnt));
    dis[st]=0;
    cnt[st]=1;
    while (!q.empty()){
        int now=q.front();
        q.pop_front();
        for (int i=h[now];i;i=ne[i]){
            int nxt=e[i];
            if (dis[nxt]>dis[now]+le[i]){
                dis[nxt]=dis[now]+le[i];
                ++cnt[nxt];
                if (cnt[nxt]>=n*m){
                    cout<<"No";
                    exit(0);
                }
                else if ((!q.empty())&&dis[q.front()]>dis[nxt]){
                    q.push_front(nxt);
                }
                else q.push_back(nxt);
                if (dis[q.front()]>dis[q.back()]){
                    int z=q.front();
                    int t=q.back();
                    q.pop_front();
                    q.pop_back();
                    q.push_front(t);
                    q.push_back(z);
                }
            }
        }
        
    }
    for (int i=1;i<=n*m;i++){
        ans[i]=max(ans[i],dis[i]+val[st]);
    }
}
signed main(){
    ios::sync_with_stdio(0);
    memset(ans,-128,sizeof(ans));
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>q;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            cin>>val[x(i,j)];
            for (int k=0;k<4;k++){
                int di=i+dx[k],dj=j+dy[k];
                if (x(di,dj)){
                    add(x(di,dj),x(i,j),val[x(i,j)]);
                }
            }
        }
    }
    for (int i=1;i<=q;i++){
        int z,t;
        cin>>z>>t;
        spfa(x(z,t));
    }
    int mn=0x3f3f3f3f3f3f3f3fLL;
    for (int i=1;i<=n*m;i++){
        mn=min(mn,ans[i]);
    }
    cout<<mn;
    return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# P11131解题报告

## 前言

关于 SPFA，它诈尸了。

## 思路分析

首先转化题意为网格图点权最短路。

注意到网格图上有负权点，使用裸 SPFA 的复杂度是 $O(n^2m^2q)$ 的，不能通过本题。

考虑使用堆优化 SPFA，将复杂度降为 $O(nmq \log nm)$。

关于堆优化 SPFA，其实就是将 SPFA 中的队列变为优先队列，具体实现请看代码，不再赘述。

下面考虑证明堆优化 SPFA 的正确性。

首先明确，堆优化 SPFA 在一般图中进行的只是常数优化，但在本题中，堆优化 SPFA 优化了复杂度。

考虑 SPFA 的本质死因。SPFA 死因是每更新一个点的最短路，可能导致大量的点被再次松弛，使复杂度退化至 $O(nm)$。

****重要性质：在网格图点权最短路中，堆中弹出的正权点的最短路是单调不降的。****

换言之，当一个正权点的最短路是当前全局最小最短路时，它不会再次被松弛。这也符合迪杰斯特拉算法的要求。

提醒一下图中是没有零权点的。

考虑分情况讨论松弛。为了方便，设 $u$ 松弛 $v$。$dis_u$ 和 $dis_v$ 表示源点到 $u$ 和 $v$ 的最短路。

- 当 $u,v$ 都是正权点时，满足 $dis_u > dis_v$。

- 当 $u,v$ 都是负权点时，$u,v$ 构成了网格图中的一个负环，不合法。

- 当 $u$ 是负权点，$v$ 是正权点时，不难发现 $dis_u > dis_v$ 依然成立，同时既然 $dis_u$ 是目前全局最短路，$dis_u$ 一定不小于之前弹出的正权点最短路。

- 当 $u$ 是正权点，$v$ 是负权点时，因为不存在负权点到负权点的松弛，所以 $v$ 只能松弛到下一个正权点。设这个正权点为 $z$。因为图中不存在负环，所以 $a_x+a_y+a_z > 0$。所以一定满足 $dis_u > dis_z$。

证毕。~~感觉证的很感性？~~、

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
#define id(i,j) (m*(i-1)+j)
using namespace std;
const int inf=1e18;
int n,m,t,x,y,a[100005],minn;
int head[100005],nxt[1000005],target[1000005],tot;
void add(int x,int y){
	tot++;
	nxt[tot]=head[x];
	head[x]=tot;
	target[tot]=y;
}
struct node{
	int x,dis;
	bool operator <(const node &a)const{
		return a.dis<dis;
	}
};
priority_queue<node> q;
int dis[55][100005],vis[100005],cnt[100005];
void spfa(int id,int s){
	memset(dis[id],0x7f,sizeof(dis[id]));
	memset(vis,0,sizeof(vis));
	memset(cnt,0,sizeof(cnt));
	dis[id][s]=a[s];
	q.push((node){s,dis[id][s]});
	while(q.size()){
		int x=q.top().x;
		q.pop();
		vis[x]=0;
		cnt[x]++;
		if(cnt[x]>n*m){
			cout<<"No";
			exit(0);
		}
		for(int i=head[x];i;i=nxt[i]){
			int y=target[i];
			if(dis[id][y]>dis[id][x]+a[y]){
				dis[id][y]=dis[id][x]+a[y];
				if(vis[y]) continue;
				vis[y]=1;
				q.push((node){y,dis[id][y]});
			}
		}
	} 
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[id(i,j)];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i!=1) add(id(i,j),id(i-1,j));
			if(j!=1) add(id(i,j),id(i,j-1));
			if(i!=n) add(id(i,j),id(i+1,j));
			if(j!=m) add(id(i,j),id(i,j+1));
		}
	}
	for(int i=1;i<=t;i++){
		cin>>x>>y;
		spfa(i,id(x,y));
	}
	minn=inf;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int maxn=-inf;
			for(int k=1;k<=t;k++){
				maxn=max(maxn,dis[k][id(i,j)]);
			}
			//cout<<i<<' '<<j<<' '<<maxn<<endl;
			minn=min(minn,maxn);
		}
	}
	cout<<minn;
	return 0;
}
```

## 后记

感觉梦熊题目质量还是一如既往的高，让人耳目一新。

---

