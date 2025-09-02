# [ARC025C] ウサギとカメ

## 题目描述

兔子和乌龟在图上比赛。

一个图有 $N$ 个节点，节点从 $1$ 到 $N$ 被编号，节点与节点相连的边不会重合，且形成的图是无向图。

在比赛中，从所有节点中选择目的地 $A$、兔子的起点 $B$、乌龟的起点 $C$。$A,B,C$ 互不相同。比赛开始后，兔子以每秒 $R$ 米、乌龟以每秒 $T$ 米的速度向目的地前进。

乌龟想知道通过进行最佳路线是，求当 $A,B,C$ 的组时，兔子任何路是比乌龟后面到达目的地的的个数。

## 说明/提示

样例 1 解释：

可以考虑以下 $2$ 种。
- （目的地，兔子的出发点，乌龟的出发点）为 $(2,4,1)$ 时，乌龟直接去目的地的话，$4$ 秒就到了。另一方面，兔子不管怎么走都至少要花 $4.5$ 秒。
- （目的地，兔子的出发点，乌龟的出发点）是 $(4,3,2)$ 的情况下，乌龟直接去目的地的话 $4$ 秒到达。另一方面，兔子不管怎么走都至少要花 $4.5$ 秒。
顺便说一下（目的地，兔子的开始地点，乌龟的开始地点）是 $(1,4,3)$ 的情况下，兔子和乌龟到达目的地需要 $3$ 秒以上。如果彼此进行了最合适的移动，因为同时到达，所以不满足条件。

## 样例 #1

### 输入

```
4 5 2 1
1 2 4
1 3 3
1 4 6
2 3 5
3 4 4```

### 输出

```
2```

## 样例 #2

### 输入

```
5 4 7 7
1 2 1
2 3 1
3 4 1
4 5 1```

### 输出

```
26```

# 题解

## 作者：Vegetableless (赞：3)

一道水题。

对于每个点之间的最短路，我们可以跑 $n$ 次 dijkstra（因为这题并没有负边权），接下来考虑枚举三个点。

显然 $O(N^3)$ 的枚举会超时。根据小学知识，通过一段路程的时间为：$\Large\frac{s}{v}$，而题目的条件为乌龟到终点的用时要少于兔子到终点的用时，我们可以列出不等式：

$$\large\frac{dis1}{v_{\text{turtle}}} < \frac{dis2}{v_{\text{rabbit}}}$$

$dis1$ 是乌龟所在起点到终点的路程，$dis2$ 是兔子所在起点到终点的路程。运用初中数学知识，将不等式变为：

$$\large\frac{dis1}{v_{\text{turtle}}} \times v_{\text{rabbit}} < dis2$$

那么我们可以考虑去枚举乌龟所在的起点，根据这个不等式二分查找第一个比上述分式大的 $dis2$ 即可。

时间复杂度 $O(N^2 \log N)$

```cpp
/*
by Vegetableless

警钟长鸣：一定要开 long long 
*/

#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 3e3 + 5;
const int INF = 1e9 + 7;

inline int read(){
	register char ch = getchar();
	register int x = 0;
	register bool f = 0;
	while(!isdigit(ch)) f = (ch == '-') , ch = getchar();
	while(isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48) , ch = getchar();
	return f ? -x : x;
}

template <typename T> inline void write(T x){
  	if(!x) putchar(48);
	if(x < 0) putchar('-') , x = -x;
	int out[101];
	int w_top = 0;
	while(x)
		out[++w_top] = x % 10 , x /= 10;
	while(w_top)
		putchar(out[w_top] ^ 48) , w_top--;
	putchar(10);
}

int n , m , r , t;

bool vis[N];

int head[2 * N] , tot;
double dis[N][N]; 

struct Edge{
	int next , to , w;
}e[2 * N];

inline void adds(int u , int v , int w){
	e[++tot].to = v;
	e[tot].next = head[u];
	e[tot].w = w;
	head[u] = tot;
}

struct Node{
	double dis;
	int pos;
	
	bool operator >(const Node &x) const{return dis > x.dis;}
};

priority_queue<Node , std::vector<Node > , std::greater<Node > >q;

inline void dijkstra(int fa){
	for(register int i = 1;i <= n;++i) vis[i] = 0;
	
	while(!q.empty()) q.pop();
	q.push({0.0 , fa});
	while(!q.empty()){
		Node u = q.top();
		q.pop();
		if(vis[u.pos]) continue;
		vis[u.pos] = 1;
		for(register int i = head[u.pos];i;i = e[i].next){
			int v = e[i].to , w = e[i].w;
			if(dis[fa][v] > dis[fa][u.pos] + w){
				dis[fa][v] = dis[fa][u.pos] + w;
				if(!vis[v])
					q.push({dis[fa][v] , v});
			}
		}
	}
}

int ans;

signed main(){
	n = read() , m = read() , r = read() , t = read();
	for(register int i = 1;i <= m;++i){
		int u = read() , v = read() , w = read();
		adds(u , v , w);
		adds(v , u , w);
	}
	for(register int i = 1;i <= n;++i)
		for(register int j = 1;j <= n;++j)
			dis[i][j] = (i == j) ? 0 : INF;
	
	for(register int i = 1;i <= n;++i) dijkstra(i);//以每个点为源点跑一边 dijkstra 
	
	for(register int i = 1;i <= n;++i) std::sort(dis[i] + 1 , dis[i] + 1 + n);//先排一遍序 
	
	for(register int i = 1;i <= n;++i){
		for(register int j = 2;j <= n;++j){//第一个点是 i，距离为 0 
			int ubt = upper_bound(dis[i] + 2 , dis[i] + n + 1 , dis[i][j] / t * 1.0 * r * 1.0) - dis[i];//二分查找 
			ans += n - ubt + 1;//ubt 后面的所有点的 dis2 肯定比分式大 
			if(ubt <= j) ans--;//因为三个点不同，所以不能算进去 j 点
		}
	}//这里是二分，也可以用双指针解决 O(N^2)，原理一样。 
	
	write(ans);
	return 0;
}
//dis1 / t < dis2 / ra
//dis1 / t * ra < dis2
```

[AC记录](https://atcoder.jp/contests/arc025/submissions/46758526)

---

## 作者：_Kenma_ (赞：1)

## 前言

这里提供一种 $O(nm \log m)$ 的做法。

## 思路分析

考虑枚举 $C$，建反图求出每个点到 $C$ 的最短路。

再枚举 $A$，不难发现，对于固定的 $A,C$，$B$ 合法当且仅当 $Tdis_A < Rdis_B$，可以排序后双指针处理。

但是还有一个问题，我们求出的 $(A,B,C)$ 没有保证 $A,B,C$ 互不相同。

考虑容斥一下：

- $A=B$：当且仅当 $R>T$ 时，方案数为 $n(n-1)$，否则方案数为 $0$；

- $A=C$：方案数为 $0$；

- $B=C$：方案数为 $n(n-1)$；

- $A=B=C$：方案数为 $0$。

做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e18;
int n,m,r,p,x,y,w,a[200005],b[200005],vis[200005],ans;
vector<int> v[200005],t[200005];
struct node{
	int x,dis;
	bool operator <(const node &a)const{
		return a.dis<dis;
	}
};
priority_queue<node> q;
void dij(int *dis,int s,int g){
	for(int i=1;i<=n;i++){
		dis[i]=inf;
		vis[i]=0;
	}
	dis[s]=0;
	q.push((node){s,dis[s]});
	while(q.size()){
		int x=q.top().x;
		q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=0;i<v[x].size();i++){
			int y=v[x][i],w=t[x][i]*g;
			if(dis[y]>dis[x]+w){
				dis[y]=dis[x]+w;
				q.push((node){y,dis[y]});
			}
		}
	}
}
signed main(){
	//freopen("in.in","r",stdin);
	//freopen("out.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>r>>p;
	for(int i=1;i<=m;i++){
		cin>>x>>y>>w;
		v[x].push_back(y);
		v[y].push_back(x);
		t[x].push_back(w);
		t[y].push_back(w);
	}
	for(int i=1;i<=n;i++){
		dij(a,i,p);
		dij(b,i,r);
		sort(a+1,a+1+n);
		sort(b+1,b+1+n);
		int l=1,r=0;
		while(l<=n){
			while(r+1<=n && b[r+1]<a[l]) r++;
			ans+=r;
			l++;
		}
	}
	ans-=n*(n-1);
	if(r<p) ans-=n*(n-1);
	cout<<ans<<'\n';
	return 0;
}
```

---

