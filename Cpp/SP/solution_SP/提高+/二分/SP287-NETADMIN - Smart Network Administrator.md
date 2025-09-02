# NETADMIN - Smart Network Administrator

## 题目描述

 The citizens of a small village are tired of being the only inhabitants around without a connection to the Internet. After nominating the future network administrator, his house was connected to the global network. All users that want to have access to the Internet must be connected directly to the admin's house by a single cable (every cable may run underground along streets only, from the admin's house to the user's house). Since the newly appointed administrator wants to have everything under control, he demands that cables of different colors should be used. Moreover, to make troubleshooting easier, he requires that no two cables of the same color go along one stretch of street.

 Your goal is to find the minimum number of cable colors that must be used in order to connect every willing person to the Internet.

## 样例 #1

### 输入

```
2
5 5 4
2 3 4 5
1 2
1 3
2 3
2 4
3 5
8 8 3
4 5 7
1 2
1 8
8 7
1 3
3 6
3 2
2 4
2 5```

### 输出

```
2
1```

# 题解

## 作者：yingjingxu_NaS2O3 (赞：5)

## 思路

注意到题面中给出的一句话“使得经过最多次数的边经过次数最少”，引导我们往二分考虑。

显然可以二分最多经过次数，下界为 $1$，上界为 $k$，然后验证在此经过次数内能否使 $k$ 个特殊点都到达 $1$ 号点。

考虑将经过次数限制转为流量限制，跑最大流，若最大流 $f_{\max}\ge k$，则可行。

使用 Dinic 跑最大流，时间复杂度 $O(n^2m)$，总时间复杂度 $O(n^2m\log k)$ 且跑不满，可以通过。

## 代码

注意多测清空。

```cpp
#include <bits/stdc++.h>
#define int long long
#define __BEGIN_MULTITEST__ \
	signed T; \
	scanf("%d",&T); \
	while(T--) \
	{
#define __END_MULTITEST__ }
using namespace std;
//using namespace __gnu_cxx;
//using namespace __gnu_pbds;
namespace Dinic
{
	int head[200005],cur[200005],d[200005];
	bool vis[200005];
	int cnt=1,n,m;
	struct node{int to,nxt,w;} e[500005];
	void initdinic() {cnt=1; memset(head,0,sizeof head); memset(vis,0,sizeof vis);}
	void add(int u,int v,int w)
	{
		e[++cnt].to=v;
		e[cnt].w=w;
		e[cnt].nxt=head[u];
		head[u]=cnt;
	}
	void AddEdge(int u,int v,int w)
	{
		add(u,v,w);
		add(v,u,0);
	}
	bool bfs(int s,int t)
	{
		for(int i=1;i<=n;i++)
			d[i]=1e18;
		queue<int> q;
		q.push(s);
		cur[s]=head[s];
		d[s]=0;
		while(!q.empty())
		{
			int tmp=q.front();
			q.pop();
			for(int i=head[tmp];i;i=e[i].nxt)
				if(e[i].w>0&&d[e[i].to]==1e18)
				{
					q.push(e[i].to);
					cur[e[i].to]=head[e[i].to];
					d[e[i].to]=d[tmp]+1;
					if(e[i].to==t)
						return 1; 
				}
		}
		return 0;
	}
	int dfs(int u,int t,int sum)
	{
		if(u==t)
			return sum;
		int ret=0;
		for(int i=cur[u];i&&sum;i=e[i].nxt)
		{
			cur[u]=i;
			if(e[i].w>0&&d[e[i].to]==d[u]+1)
			{
				int k=dfs(e[i].to,t,min(sum,e[i].w));
				if(!k)
					d[e[i].to]=1e18;
				e[i].w-=k;
				e[i^1].w+=k;
				ret+=k;
				sum-=k;
			}
		}
		return ret;
	}
	int s,t;
	int dinic(int &ans)
	{
		while(bfs(s,t))
			ans+=dfs(s,t,1e18);
		return ans;
	}
}
int k;
int u[200005],v[200005],spe[200005];
using namespace Dinic;
bool check(int x)
{
	initdinic();
	for(int i=1;i<=m;i++)
	{
		AddEdge(u[i],v[i],x);
		AddEdge(v[i],u[i],x);
	}
	s=n+1;
	t=1;
	for(int i=1;i<=k;i++)
		AddEdge(s,spe[i],1);
	int ans=0;
	dinic(ans);
	return ans>=k;
}
signed main()
{
	__BEGIN_MULTITEST__
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=k;i++)
		scanf("%lld",&spe[i]);
	for(int i=1;i<=m;i++)
		scanf("%lld%lld",&u[i],&v[i]);
	int l=1,r=k;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(mid))
			r=mid-1;
		else
			l=mid+1;
	}
	printf("%lld\n",r+1);
	__END_MULTITEST__
	return 0;
}
```

---

## 作者：BitByBit (赞：2)

网络流水题。
# 题意
多测，每次给定 $n$ 个点 $m$ 条边的无向图，并给出 $k$ 个关键节点，找出每个关键节点到 $1$ 的一条路径，求图中被这些路径经过次数最多的边，被经过的次数是多少。
# 解析
不难想到网络流，但是这个最大经过次数最小很难直接算。于是想到二分。二分出每条边的容量 $mid$，每次重新建图，对于原图中的无向边都变成两条容量为 $mid$ 的有向边。超级源点向 $k$ 个关键节点连容量为 $1$ 的边，汇点为 $1$ 然后跑最大流，如果最大流等于 $k$ 说明每个关键节点都有一条到汇点的路径，所以是合法的。  
使用 Dinic 求最大流，时间复杂度：$\Theta(t n^2 m \log k)$，跑不满，能过。
# 程序
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define infll 0x3f3f3f3f3f3f3f3f
#define N 10010
#define M 500010
int n,m,k,s,t,tot=1;
int A[N],X[M],Y[M];
ll maxflow;
int Head[N],Son[M],Next[M];
ll Cap[M];
deque<int>Q;
int Cur[N];
ll Dis[N];
inline void add(int x,int y,ll z)
{
	Son[++tot]=y;
	Cap[tot]=z;
	Next[tot]=Head[x];
	Head[x]=tot;
}
bool bfs()
{
	memset(Dis,0x3f,sizeof(Dis));
	memcpy(Cur,Head,sizeof(Cur));
	Q.clear();
	Q.push_back(s);
	Dis[s]=0;
	while(!Q.empty())
	{
		int x=Q.front();
		Q.pop_front();
		for(int i=Head[x];i;i=Next[i])
		{
			int y=Son[i];
			if(Cap[i]>0&&Dis[y]==infll)
			{
				Q.push_back(y);
				Dis[y]=Dis[x]+1;
				if(y==t)return 1;
			}
		}
	}
	return 0;
}
ll dfs(int x,ll flow)
{
	if(x==t)return flow;
	ll res=0;
	for(int i=Cur[x];i&&flow;i=Next[i])
	{
		int y=Son[i];
		Cur[x]=i;
		if(Cap[i]>0&&Dis[y]==Dis[x]+1)
		{
			ll k=dfs(y,min(flow,Cap[i]));
			if(!k)Dis[y]=infll;
			Cap[i]-=k;
			Cap[i^1]+=k;
			res+=k;
			flow-=k;
		}
	}
	return res;
}
void Dinic()//网络流板子
{
	while(bfs())maxflow+=dfs(s,infll);
}
bool check(int mid)//每次重新建图跑一遍最大流
{
	tot=1;
	memset(Head,0,sizeof(Head));
	maxflow=0;
	for(int i=1;i<=k;i++)
	{
		add(s,A[i],1);
		add(A[i],s,0);
	}
	for(int i=1;i<=m;i++)
	{
		add(X[i],Y[i],mid);
		add(Y[i],X[i],0);
		add(Y[i],X[i],mid);
		add(X[i],Y[i],0);
	}
	Dinic();
	return maxflow==k;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int _;
	cin>>_;
	while(_--)
	{
		int ans=-1;
		cin>>n>>m>>k;
		s=n+1;
		t=1;
		for(int i=1;i<=k;i++)
			cin>>A[i];
		for(int i=1;i<=m;i++)
			cin>>X[i]>>Y[i];
		int l=1,r=k;
		while(l<=r)//二分答案
		{
			int mid=(l+r)>>1;
			if(check(mid))
			{
				ans=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		cout<<ans<<'\n';
	}
	return 0;
}

```

---

## 作者：gavinliu266 (赞：0)

# 思路
看到题目可以想到二分这个次数，具体的就是 check 函数怎么写。

这里需要限制每条边的流过次数，可以想到限制流量，然后跑一边最大流的模板。如果超过了流量限制则无法流过，求出的最大流会变小，这样就可以判断是否合法了。

这里采用了 Dinic 算法来求出最大流。

# 代码实现
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
struct Dinic {
    struct Edge { int from, to, cap; };
    vector<Edge> edges;
    vector<int> G[505];
    int n, m = 0, u;
    int d[505], cur[505];
    inline void init() {
        m = 0;
        for(int i = 0; i <= n; ++i) G[i].clear();
        edges.clear();
    }
    inline void addEdge(int from, int to, int cap) {
        edges.push_back({from, to, cap});
        G[from].push_back((++m) - 1);
    }
    inline bool bfs() {  // 使用 bfs 分层
        memset(d, 0, sizeof(d));
        queue<int> q;
        d[0] = 1, q.push(0);
        while(!q.empty()) {
            u = q.front(), q.pop();
            for(auto p : G[u]) {
                Edge& e = edges[p];
                if(!d[e.to] && e.cap) {
                    d[e.to] = d[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return (bool)d[1];
    }
    int dfs(int x, int a) {  // 使用 dfs 增广
        if(x == 1 || !a) return a;
        int flow = 0, f;
        for(int& i = cur[x]; i < G[x].size(); ++i) {
            Edge& e = edges[G[x][i]];
            if(d[x] + 1 == d[e.to] && (f = dfs(e.to, min(a, e.cap)))) {
                e.cap -= f;
                edges[G[x][i] ^ 1].cap += f;
                flow += f;
                a -= f;
                if(!a) break;
            }
        }
        return flow;
    }
    int maxFlow() {
        int flow = 0;
        while(bfs()) {
            memset(cur, 0, sizeof(cur));
            flow += dfs(0, 505);  // k 最大为 500，给到 505 或者 k + 1
        }
        return flow;
    }
} S;
struct Ed { int from, to; };
vector<Ed> ed;
vector<int> s;
int t, m, k, l, r, u, v, mid;
inline bool ck(int x) {
    S.init();  // 每次 check 都要初始化
    for(auto p : ed)
        S.addEdge(p.from, p.to, x), S.addEdge(p.to, p.from, x);  // 注意双向边
    for(auto p : s)
        S.addEdge(0, p, 1), S.addEdge(p, 0, 0);  // 把 0 号点作为超级原点
    int flow = S.maxFlow();
    return flow >= k;
}
int main() {
    scanf("%d", &t);
    while(t--) {
        ed.clear();
        s.clear();  // 初始化
        scanf("%d%d%d", &S.n, &m, &k);
        for(int i = 0; i < k; ++i)
            scanf("%d", &u), s.push_back(u);
        for(int i = 0; i < m; ++i)
            scanf("%d%d", &u, &v), ed.push_back({u, v});
        l = 0, r = k;
        while(l <= r) {  // 二分
            mid = (l + r) >> 1;
            if(ck(mid)) r = mid - 1;
            else l = mid + 1;
        }
        printf("%d\n", l);
    }
}
```

---

## 作者：CQ_Bab (赞：0)

# 前言
我们可以发现这道题一眼就是二分了，但是唯一的问题就是如何写 check 函数。
# 思路
这里我们可以看到 `标签` 中有 `网络流` 那么我们就来想一下如何写，这里我们可以将 S 与所有的特殊点都连上一条流量为 $1$ 的边，然后由于我们传进来的一个数为 $x$ 然后在将所有正常的边都变成流量为 $x$ 的边，这里即可代表每一条边的最多能走 $x$ 次。

然后我们直接跑一个正常的网络流即可，然后我们就判断 $maxflow$ 与 $k$ 的关系即可，若大于等于就满足条件。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int tot=1;
const int N=1e5+10;
int head[N],n,m,k;
struct node {
	int x,y,z;
} edg[N];
int d[N],s;
int a[N],t;
void add(int x,int y,int z) {
	edg[++tot]= {y,head[x],z};
	head[x]=tot;
	if(x!=s) edg[++tot]= {x,head[y],z};
	else edg[++tot]={x,head[y],0};
	head[y]=tot;
}
int x[N],y[N];
int bfs() {
	queue<int>q;
	q.push(s);
	memset(d,0,sizeof d);
	d[s]=1;
	while(q.size()) {
		int x=q.front();
		q.pop();
		for(int i=head[x]; ~i; i=edg[i].y) {
			int to=edg[i].x;
			if(!d[to]&&edg[i].z) {
				d[to]=d[x]+1;
				q.push(to);
				if(to==t) return 1;
			}
		}
	}
	return false;
}
int dinic(int x,int flow) {
	if(x==t) return flow;
	int pl=false;
	for(int i=head[x]; ~i&&flow; i=edg[i].y) {
		int to=edg[i].x;
		if(d[to]==d[x]+1&&edg[i].z) {
			int k=dinic(to,min(edg[i].z,flow));
			if(!k) d[to]=-1;
			edg[i].z-=k;
			pl+=k;
			edg[i^1].z+=k;
			flow-=k;
		}
	}
	return pl;
}
bool check(int ff) {
	memset(head,-1,sizeof head);
	tot=1;
	t=1;
	s=n+1;
	rep(i,1,k) add(s,a[i],1);
	rep(i,1,m) add(x[i],y[i],ff);
	int flow=0;
	while(bfs()) flow+=dinic(s,INT_MAX);
	return flow>=k;
}
fire main() {
	int T;
	cin>>T;
	while(T--) {
		in(n),in(m),in(k);
		rep(i,1,k) in(a[i]);
		rep(i,1,m) cin>>x[i]>>y[i];
		int l=0,r=k+1,ans=0;
		while(l<=r) {
			int mid=l+r>>1;
			if(check(mid)) r=mid-1,ans=mid;
			else l=mid+1;
		}
		print(ans);
		end;
	}
	return false;
}

```

---

## 作者：happybob (赞：0)

有趣题。

容易发现答案可以二分，重点在于怎么写 `check`。

我们假设现在二分的是 $x$，我们要判断若对于每条边，只能经过 $x$ 次，$k$ 个点是否可以全部到达 $1$。容易发现这个东西可以转化为网络流，从源点 $S$ 向 $k$ 个特殊点连容量为 $1$ 的边，原图上每条边的容量为 $x$。由题知，汇点 $T=1$，我们只需要判断 $S \rightarrow T$ 的最大流是否为 $k$ 即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <climits>
using namespace std;

const int N = 2e5 + 5;

int t, n, m, k;
int e[N], h[N], ne[N], c[N], idx;
int S = 0, T = 1;
int d[N], cur[N];
int a[N];
int u[N], v[N];

inline void add(int x, int y, int z)
{
	e[idx] = y, ne[idx] = h[x], c[idx] = z, h[x] = idx++;
}

inline bool bfs()
{
	queue<int> q;
	q.push(S);
	for (int i = 0; i <= n; i++) d[i] = -1, cur[i] = -1;
	d[S] = 0, cur[S] = h[S];
	while (q.size())
	{
		int u = q.front();
		q.pop();
		for (int i = h[u]; ~i; i = ne[i])
		{
			int j = e[i];
			if (d[j] == -1 && c[i] > 0)
			{
				d[j] = d[u] + 1;
				cur[j] = h[j];
				if (j == T) return 1;
				q.push(j);
			}
		}
	}
	return 0;
}

inline int dfs(int u, int lim)
{
	if (u == T) return lim;
	int res = 0;
	for (int i = cur[u]; ~i && res < lim; i = ne[i])
	{
		cur[u] = i;
		int j = e[i];
		if (d[j] == d[u] + 1 && c[i] > 0)
		{
			int p = dfs(j, min(lim - res, c[i]));
			if (p == 0) d[j] = -1;
			res += p;
			c[i] -= p;
			c[i ^ 1] += p;
		}
	}
	return res;
}

inline int dinic()
{
	int res = 0, p;
	while (bfs())
	{
		while (p = dfs(S, INT_MAX)) res += p;
	}
	return res;
}

inline bool check(int g)
{
	for (int i = 0; i < N; i++)
	{
		e[i] = h[i] = ne[i] = c[i] = 0;
		h[i] = -1;
	}
	idx = 0;
	for (int i = 1; i <= k; i++)
	{
		add(S, a[i], 1);
		add(a[i], S, 0);
	}
	for (int i = 1; i <= m; i++)
	{
		add(u[i], v[i], g);
		add(v[i], u[i], g);
	}
	int gg = dinic();
	//printf("!: %d %d\n", g, gg);
	return gg == k;
}

int main()
{
	memset(h, -1, sizeof h);
	scanf("%d", &t);
	while (t--)
	{
		idx = 0;
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 1; i <= k; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= m; i++)
		{
			scanf("%d%d", &u[i], &v[i]);
		}
		int l = 0, r = k + 1, ans = -1;
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (check(mid)) ans = mid, r = mid - 1;
			else l = mid + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
```


---

## 作者：ZolaWatle (赞：0)

## SP287 题解

### 题目大意

一张无向图中给出 $k$ 个点，要求这些点各通过一条路径到达 $1$ 点，并使得这组路径中经过次数最多的边经过的次数最少。

### 解题思路

看到这样的问法，首先考虑二分答案。我们设经过次数最多的边被经过 $c$ 次，二分这个 $c$，每次检验是否有一组路径满足要求。很显然，$c$ 越大，满足要求的可能性就越大，因此，如果检验出其不满足要求，我们向上二分 $c$，反之则向下。我们知道，由于只给定了 $k$ 个点，因此每条边的经过次数最多为 $k$ 次。至此，我们确立了二分的边界。

那么如何判断这样的 $c$ 是否满足要求呢？

可以考虑建立网络流模型。我们令超级源点 $s$ 为零号点，超级汇点 $t$ 为 $1$ 号点（目的地）。对于每一个指定的点 $x$，连边 $(s, x)$，其流量为 $1$；对于每一条边和每一次二分到的 $c$，连边 $(\text{from}_i, \text{to}_i)$，由于是无向边，我们还应该连它的反向边，其流量为 $c$。然后跑一遍最大流。

最大流跑完之后，每一条 $s - t$ 的流量为 $1$ 的流表示某一指定点 $x$ 到点 $1$ 的一条路径。由于在建图时，每条边的流量限制为 $c$，这也就保证了每一条边的经过次数不超过 $c$。如果总流量不足 $k$，则说明只有这 $k$ 个点中的某些点能在这样的 $c$ 的限制下到达点 $1$，不满足要求。反之，满足要求，往小了去二分。二分完成后的 $l$ 即是答案。

### 完整代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define ll long long
#define re register int
#define rl register ll
#define rep(i,a,b) for(re i=(a),i##end=(b);i<=i##end;++i)
#define pre(i,a,b) for(re i=(a),i##end=(b);i>=i##end;--i)
using namespace std;

const int N=1e3+1,M=1e5+1,INF=0x3f3f3f3f;
int T,l,r;
int n,m,k,s,t=1,a[N],fr[M],to[M];
int tot,head[N],now[N],d[N];
struct Edge{int to,val,nxt;}E[M];

inline int rint()
{
	re x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
	return x*f;
}

inline void add(int x,int y,int z)
{
	E[++tot].to=y;
	E[tot].val=z;
	E[tot].nxt=head[x];
	head[x]=tot;
}
inline void rebuild(int lim)
{
	memset(head,0,sizeof(head));
	tot=1;
	rep(i,1,k) add(s,a[i],1),add(a[i],s,0);
	rep(i,1,m) add(fr[i],to[i],lim),add(to[i],fr[i],lim);
}

inline int bfs()
{
	queue <int> q;
	memset(d,INF,sizeof(d));
	q.push(s),d[s]=0;
	while(!q.empty())
	{
		re x=q.front();
		q.pop();
		for(re i=head[x];i;i=E[i].nxt)
		{
			re y=E[i].to;
			if(E[i].val&&d[y]==INF)
			{
				d[y]=d[x]+1;
				q.push(y);
				if(y==t) return 1;
			}
		}
	}
	return 0;
}
inline int dfs(int x,int w)
{
	if(x==t||!w) return w;
	re ret=0;
	for(re i=now[x];i&&w;i=E[i].nxt)
	{
		re y=E[i].to;
		now[x]=i;
		if(E[i].val&&d[y]==d[x]+1)
		{
			re rem=dfs(y,min(w,E[i].val));
			if(!rem) d[y]=INF;
			E[i].val-=rem,E[i^1].val+=rem;
			ret+=rem,w-=rem;
		}
	}
	return ret;
}
inline int Dinic()
{
	re maxflow=0;
	while(bfs())
	{
		memcpy(now,head,sizeof(head));
		maxflow+=dfs(s,INF);
	}
	return maxflow;
}

inline int judge(int lim)
{
	rebuild(lim);
	if(Dinic()>=k)
		return 1;
	return 0;
}

int main()
{
	T=rint();

	while(T--)
	{
		n=rint(),m=rint(),k=rint();
		rep(i,1,k) a[i]=rint();
		rep(i,1,m) fr[i]=rint(),to[i]=rint();
		l=0,r=k;
		while(l<r)
		{
			re mid=l+r>>1;
			if(judge(mid))
				r=mid;
			else l=mid+1;
		}
		printf("%d\n",l);
	}
	
	return 0;
}
```

感谢阅读！

---

