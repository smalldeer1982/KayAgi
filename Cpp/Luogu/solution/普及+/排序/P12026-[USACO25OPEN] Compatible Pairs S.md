# [USACO25OPEN] Compatible Pairs S

## 题目描述

在遥远的乡村，农夫约翰的奶牛并非普通的农场动物——它们隶属于一个秘密的奶牛情报网络。每头奶牛都有一个由精英密码学家精心分配的ID号码。但由于农夫约翰随意的标记系统，部分奶牛出现了重复ID的情况。

农夫约翰记录到共有 $N$（$1\le N\le 2\cdot 10^5$）个不同的ID号码，对于每个唯一ID $d_i$（$0\le d_i\le 10^9$），有 $n_i$（$1\le n_i\le 10^9$）头奶牛共享该ID。

奶牛们只能成对交流，它们的加密通信有一个严格规则：两头奶牛仅当不是同一头牛且它们的ID号码之和等于 $A$ 或 $B$（$0\le A\le B\le 2\cdot 10^9$）时才能交换信息。每头奶牛同一时间只能参与一次对话（即不能同时属于多对通信组合）。

农夫约翰希望最大化互不干扰的通信对数来确保最佳信息流通。你能计算出最多可以同时建立多少对通信吗？


## 说明/提示

解释：
ID为 $0$ 的奶牛可与 ID 为 $4$ 奶牛通信（ID 之和为 $4$）。由于共有 $100$ 头 ID $0$ 的奶牛和 $200$ 头 ID $4$ 的奶牛，最多可组成 $100$ 对通信组合。

ID 为 $4$ 的奶牛还可与 ID 为 $1$ 的奶牛通信（ID 之和为$5$）。此时剩余 $100$ 头 ID $4$ 的奶牛和 $10$ 头 ID $1$ 的奶牛可组成 $10$ 对通信组合。

最后，ID 为 $2$ 的奶牛可与其他同 ID 奶牛通信。$17$ 头 ID $2$ 的奶牛最多可组成 $8$ 对通信组合（$\lfloor17/2\rfloor=8$）。

总计 $100+10+8=118$ 对通信组合，可以证明这是最大可能值。

- 测试点 $3\sim4$：$A=B$。
- 测试点 $5\sim7$：$N\le 1000$。
- 测试点 $8\sim12$：无额外限制。

## 样例 #1

### 输入

```
4 4 5
17 2
100 0
10 1
200 4```

### 输出

```
118```

# 题解

## 作者：_determination_ (赞：8)

咋全都是拓扑啊，给出一种更加无脑（数据结构学傻了导致的）做法。

看到做匹配，直接想到网络流。但是我只会二分图匹配。所以我们要先证明，如果给可以消除的点连边，最后连出来的都是二分图。

这个是显然的，首先扔掉自环，这个最后考虑就好了。

然后考虑如果出现一个环 $a,b,c$，那么就要求 $a+b,a+c,b+c$ 只有两种不同的数。显然这是不可能的。至于环更长的情况也不可能。

然后我们就可以直接上网络流跑二分图匹配了！

[荣获最劣解第一页。](https://www.luogu.com.cn/record/221389640)

网络流这玩意很玄学，虽然理论复杂度很高，但是实际情况下你可以相信他的常数。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
mt19937 rnd(time(0));
const int mod=998244353,inf=0x3f3f3f3f3f3f3f3f;
const int N=2e5+10,M=2e5+10;
int n,A,B;
int a[N],b[N];
map<int,int>mp;
vector<int>e[N];
int col[N];
void dfs(int x)
{
	for ( auto v:e[x] )
		if(!col[v]){col[v]=3-col[x];dfs(v);}
		else assert(col[v]!=col[x]);
}
namespace FLOW{
	vector<pair<int,int>>e[N];
	vector<int>id[N];
	void add(int u,int v,int w)
	{
//		cerr << "add: " << u << " " <<v << " " <<w  << endl;
		id[u].push_back(e[v].size());
		id[v].push_back(e[u].size());
		e[u].push_back({v,w});
		e[v].push_back({u,0});
	}
	int dep[N],gap[N];
	const int S=0,T=N-5;
	queue<int>q;
	void bfs()
	{
		memset(dep,0x3f,sizeof(dep));
		dep[T]=0,q.push(T);
		while(!q.empty())
		{
			int x=q.front();q.pop();
			gap[dep[x]]++;
			for ( auto v:e[x] )if(dep[v.first]>dep[x]+1)dep[v.first]=dep[x]+1,q.push(v.first);
		}
	}
	int dfs(int x,int flow)
	{
		if(x==T)return flow;
		int used=0;
		for ( int i = 0 ; i < e[x].size() ; i++ )
		{
			int v=e[x][i].first,w=e[x][i].second;
			if(!w||dep[v]!=dep[x]-1)continue;
			int f=dfs(v,min(w,flow-used));
			used+=f;
			e[x][i].second-=f;
			e[v][id[x][i]].second+=f;
			if(used==flow)return used;
		}
		gap[dep[x]]--;
		if(!gap[dep[x]])dep[S]=T+5;
		dep[x]++;
		gap[dep[x]]++;
		return used;
	}
	void solve()
	{
		bfs();
		int maxflow=0;
		while(dep[S]<T+5)
		{
			maxflow+=dfs(S,inf);
//			cerr << maxflow << endl;
		}
		for ( auto i:e[S] )
		{
			int v=i.first,w=i.second;
			if(b[v]+b[v]==A||b[v]+b[v]==B)maxflow+=w/2;
		}
		for ( auto i:e[T] )
		{
			int v=i.first,w=i.second;
			if(b[v]+b[v]==A||b[v]+b[v]==B)maxflow+=(a[v]-w)/2;
		}
		cout << maxflow << endl;
	}
	//todo
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >>n >> A>>B;
	for ( int i = 1 ; i <= n ; i++ )
	{
		cin >> a[i] >> b[i];
		mp[b[i]]=i;
	}
	for ( int i = 1 ; i <= n ; i++ )
	{
		if(mp[A-b[i]]&&mp[A-b[i]]!=i)
//			cerr << "add " << i << " " << mp[A-b[i]] << endl,
			e[i].push_back(mp[A-b[i]]);
		if(mp[B-b[i]]&&mp[B-b[i]]!=i)
//			cerr << "add " << i << " " << mp[B-b[i]] << endl,
			e[i].push_back(mp[B-b[i]]);
	}
	for ( int i = 1 ; i <= n ; i++ )if(!col[i]){col[i]=2;dfs(i);}
	for ( int i = 1 ; i <= n ; i++ )
	{
		if(col[i]==1)FLOW::add(FLOW::S,i,a[i]);
		else FLOW::add(i,FLOW::T,a[i]);
		if(col[i]==1)for ( auto v:e[i] )FLOW::add(i,v,inf);
	}
	FLOW::solve();
	return 0;
}
```

---

## 作者：qW__Wp (赞：6)

建一个无向图。对于每个 $id$：

+ 若 $id \le A$，将其向 $A - id$ 连边。
+ 若 $id \le B$，将其向 $B - id$ 连边

特别的，当 $A = B$ 时，只向 $A - id$ 连边。

手玩几个数据发现一个规律：这个无向图除自环外无环。由于每个点的度数为 $1$ 或 $2$，且图连通，因此这是一条链或带自环的链。

最优策略显然是从链的两端向内进行信息流动。使用拓扑排序即可。

```C++
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5 + 5;

int id[N], w[N], d[N];
int hd[N], cnt;
bool vis[N];

struct Edge {
	int to, nx;
} e[N << 1];

unordered_map<int, int> col;

void add(int u, int v) {
	e[ ++ cnt] = {v, hd[u]}, hd[u] = cnt;
	d[u] ++;
}

signed main() {
	int n, A, B; cin >> n >> A >> B;
	for (int i = 1; i <= n; i ++) {
		cin >> w[i] >> id[i];
		col[id[i]] = i; // 存每个id图上对应点编号
	}
	for (int i = 1; i <= n; i ++) {
		if (id[i] <= A && col[A - id[i]]) {
			add(i, col[A - id[i]]);
		}
		if (A == B) continue;
		if (id[i] <= B && col[B - id[i]]) {
			add(i, col[B - id[i]]);
		}
	}
	// 以下拓扑排序
	queue<int> q;
	for (int i = 1; i <= n; i ++) {
		if (d[i] == 1) q.push(i);
	}
	int ans = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = hd[u]; i; i = e[i].nx) {
			int v = e[i].to;
			if (v == u) { // 自环
				ans += w[u] / 2;
				w[u] %= 2;
			} else if (w[v]) { // 可以产生贡献才加入队列
				int res = min(w[v], w[u]);
				w[v] -= res, w[u] -= res;
				ans += res;
				q.push(v);
			}
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：donaldqian (赞：4)

容易想到建图，即将 $d_i$ 和 $A-d_i$ 连边，$d_i$ 和 $B-d_i$ 连边。特别地，当 $A=B$ 时只需要建一条边。

然后我们会发现这个图不可能存在长度 $\ge 3$ 的环，证明如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/11ezzqxh.png)

然后这个图就是一条链带个自环之类的东西了，拓扑就完了。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 200010;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte, in[maxn];
void addedge (int u, int v) { in[v]++, to[++cnte] = v, nxt[cnte] = head[u], head[u] = cnte; }

bool vis[maxn];
unordered_map <int, int> mp;
long long ans; queue <int> que;
int n, a, b, t, d[maxn], v[maxn];

signed main () {
	scanf("%d%d%d", &n, &a, &b);
	for (int i = 1; i <= n; i++) scanf("%d%d", &v[i], &d[i]), mp[d[i]] = i;
	for (int i = 1; i <= n; i++) {
		if (mp.find (a - d[i]) != mp.end ()) addedge (i, mp[a - d[i]]);
		if (a != b && mp.find (b - d[i]) != mp.end ()) addedge (i, mp[b - d[i]]);
	}
	for (int i = 1; i <= n; i++) if (in[i] == 1) que.push (i);
	while (!que.empty ()) {
		int u = que.front (); que.pop ();
		for (int i = head[u]; i; i = nxt[i]) {
			if (vis[to[i]]) continue;
			if (to[i] == u) ans += v[u] / 2, v[u] &= 1;
			else t = min (v[u], v[to[i]]), ans += t, v[u] -= t, v[to[i]] -= t;
			if (--in[to[i]] == 1) que.push (to[i]);
		}
		vis[u] = 1;
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：czxuyang (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P12026)
## 题外话
我看一大堆神犇都用图论来做，很少有贪心做法，我就写个贪心做法的题解。
## 1. 题义简述
对于每个奶牛，有一个 ID 号码，当两头牛的 ID 号码之和等于 $A$ 或 $B$ 时，可以建立通信（不能同时属于多对通信组合），求最多可以同时建立多少对通信。

## 2. 思路
由于每头奶牛只能通信一次，且题目要求得最大通信次数，可以证明贪心算法是成立的，那么怎么贪呢？ 

观察题目可以想到：反正每头奶牛只能参与一次对话，那么当它们遇到能匹配的奶牛时就立刻匹配，因为无论是哪头奶牛匹配成功，通信总次数是不变的（任意两头奶牛都只会算通信一次）。

我们可以用一个 map 来存储每个 ID 的奶牛数量，$d$ 来存储不同的 ID，让 $d_i$ 先匹配 $B$，再匹配 $A$。因为想让配对数尽可能的多，就要匹配所有能匹配的奶牛，这样的方式可以正确找出总量。

## 3.代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
map<int,int> mp;
vector<int> g;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n,a,b,ans=0;
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){
		int u,v;
		cin>>u>>v;
		mp[v]=u;
		g.push_back(v);
	}
	sort(g.begin(),g.end());
	for(auto x:g){
		int pa=a-x,pb=b-x;
		if(mp[pb]>0 && pb>=0){
			if(pb==x) ans+=mp[pb]/2,mp[pb]%=2;
			else{
				int minn=min(mp[x],mp[pb]);
				ans+=minn;
				mp[x]-=minn;
				mp[pb]-=minn;
			}
		}
		if(mp[pa]>0 && pa>=0){
			if(pa==x) ans+=mp[pa]/2,mp[pa]%=2;
			else{
				int minn=min(mp[x],mp[pa]);
				ans+=minn;
				mp[x]-=minn;
				mp[pa]-=minn;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Swordmaker (赞：3)

# P12026 [USACO25OPEN] Compatible Pairs S

# 思路分析

通俗易懂地来说，本题是一道图论题。

题目要求我们将 $d_i$ 和 $A-d_i$ 以及 $B-d_i$ 连边。

不难发现，最后这张图的情况一定是形如一条链的样子，其中部分点可能有自环。

然后，我们需要遍历这条链。

最佳的选择显然是从这条链的两端向中间拓展。

但是，这里存在一个遍历优先级的问题。

比如，我们考虑下面这个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/abvquzsh.png)

最优的选择是将点 $2$ 和点 $5$ 以及点 $3$ 和点 $4$ 先配对，再将点 $3$ 剩下的进行配对，答案为 $125$。

由此，我们得出一个结论：

自环的遍历优先级**低于**链！

# code

于是，代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+15;
const int inf=1e19;
struct node
{
	int id,num;
}a[N];
int n,s,t,ans=0;
int b[N];
bool vis[N],spj[N];
vector<int> g[N];
queue<int> q;
void addedge(int u,int v)
{
	g[u].push_back(v);
	return;
}
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c-'0');
		c=getchar();
	}
	return x*f;
}
bool cmp(node c,node d)
{
	return c.id<d.id;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	n=read(),s=read(),t=read();
	for(int i=1;i<=n;i++)
	{
		a[i].num=read();
		a[i].id=read();
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)//离散化 
	{
		b[i]=a[i].id;
	}
	for(int i=n+1;i<=n+3;i++)
	{
		b[i]=inf;
	}
	for(int i=1;i<=n;i++)//加边 
	{
		int x=s-b[i];
		int y=t-b[i];
		int l=lower_bound(b+1,b+n+1,x)-b;
		int r=lower_bound(b+1,b+n+1,y)-b;
		if(l>=1&&l<=n&&b[i]+b[l]==s) 
		{
			if(i==l) spj[i]=true;
			else addedge(i,l);
		}
		if(r>=1&&r<=n&&b[i]+b[r]==t&&s!=t) 
		{
			if(i==r) spj[i]=true;
			else addedge(i,r);
		}
	}
	for(int i=1;i<=n;i++)
	{
		if((int)g[i].size()==1) q.push(i);//从边缘开始遍历 
	}
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(auto v:g[u])
		{
			if(!a[v].num) continue;
			int x=min(a[u].num,a[v].num);
			a[u].num-=x,a[v].num-=x;
			ans+=x;
			q.push(v);
		}
	}
	for(int i=1;i<=n;i++)//最后判断有自环且有剩余的情况 
	{
		if(spj[i]&&a[i].num>=2) ans=ans+a[i].num/2;
	}
	cout<<ans<<"\n";
	return 0;
} 
```

---

## 作者：CommandSR (赞：2)

## 题意简述

我们有 $n$ 个不同的奶牛 ID，即 $d_i$，对应 $n_i$ 头奶牛。奶牛可以两两配对，但必须满足以下条件：

1. 不能是同一头牛，但可以是相同 ID 的不同牛。
2. 它们的 ID 之和必须等于给定的 $A$ 或 $B$。

目标是计算最多可以组成多少对满足条件的配对。

## 基本思路

首先不难想到图论建模，对于每个 ID，连一条 $d_i \rightarrow A-d_i$ 和 $d_i \rightarrow B-d_i$ 的边，当然连边时要满足 $A-d_i$ 或 $B-d_i$ 的 ID 存在。

不难发现连出来的图是一个无向图，并且不会出现除自环以外的环，这样就可以使用类似无向图上拓扑排序（或者说是 BFS）的方法遍历整张图。

从一条链的端点进入，每次贪心的对一条边连接的点对 $u \rightarrow v$ 能配对的全部配对。

一些细节问题：

1. 注意 $A=B$ 的情况。
2. 遍历整张图时自环要特判。


## AC Code

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for (int i = a; i <= b; ++i)
#define _F(i, a, b) for (int i = a; i >= b; --i)
#define ll long long
using namespace std;
ll rd() {
	ll p = 0, f = 1; char ch = getchar();
	while (ch>'9' || ch<'0') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch>='0' && ch<='9') p = p*10+ch-'0', ch = getchar();
	return p * f;
}
const int N = 4e5 + 5;
ll n, a, b;
unordered_map <ll, ll> dx;
struct C {
	ll num, id;
} c[N];
bool cmp(C u, C v) {
	return u.id < v.id;
}
struct edge {int to, nxt;} e[N<<1];
ll hd[N], ec, ind[N];
bool vis[N];
void AddEdge(int u, int v) {
	e[++ec].to = v, e[ec].nxt = hd[u], hd[u] = ec, ++ind[u];
}
queue <int> q;
ll res;
void Topo() {
	F(i, 1, n) if (ind[i]==1) q.push(i);
	ll cur = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = hd[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (v == u) {
				res += (c[u].num >> 1);
				c[u].num %= 2;
			} else if (c[v].num) {
				cur = min(c[u].num, c[v].num);
				c[u].num -= cur, c[v].num -= cur;
				res += cur;
				q.push(v);
			}
		}
	}
}
int main() {
	n = rd(), a = rd(), b = rd();
	F(i, 1, n) c[i].num = rd(), c[i].id = rd();
	F(i, 1, n) dx[c[i].id] = i;
	F(i, 1, n) {
		if (c[i].id <= a && dx[a-c[i].id]) {
			AddEdge(i, dx[a-c[i].id]);
		}
		if (a!=b && c[i].id <= b && dx[b-c[i].id]) {
			AddEdge(i, dx[b-c[i].id]);
		}
	}
	Topo();
	cout << res << '\n';
	return 0;
}
```

---

## 作者：Little_x_starTYJ (赞：1)

## 前言
把此题放到 T2 然后模拟考最为期末成绩，目前感觉快 AFO 了。最后 $20 + 100 + 20 + 10 = 150pts$。想要考试的四道原题的家人们可以私信我要题号。

## 解题思路
直接建图跑 dfs。下文默认认为每种奶牛的编号为 $d_i$。

首先应该很容易想到对于每一个建一条 $d_i$ 与 $a - d_i$ 的无向边。再建一条 $d_i$ 与 $b - d_i$ 的无向边，如果 $a = b$，建一条边就够了，免得重边对自己产生影响，注意，需要保证 $a - d_i$ 或者 $b - d_i$ 存在于给出的 $n$ 个 ID 中。

然后贪心。如果存在某个 $d_i = \frac{a}{2}$ 或者 $d_i = \frac{b}{2}$，那么它其实是可以自己跟自己组队的。但是如果它与 $d_j$ 有连边（如果 $d_i = \frac{a}{2}$，那么可能存在与 $b - d_i$ 即 $d_j$ 的连边，反之亦然），那么其实先将 $d_i$ 与 $d_j$ 进行组队，再与自己组队是更优的。

比如：$a = 3, b = 4, d_i = 2, n_i = 101, d_j = 1,n_j = 99$，那么 $d_i$ 与 $d_j$ 进行组队，可以产生 $99$ 的贡献，然后再自己跟自己组队又可以产生 $1$ 的贡献（两头牛才能组队），总贡献为 $99 + 1 = 100$。但是先和自己组队产生 $50$ 的贡献，余下一头牛跟 $d_j$ 组队，产生 $1$ 的贡献，总贡献为 $50 + 1 = 51$。

其余不包含 $\frac{a}{2},\frac{b}{2}$ 的连通块只需要能产生贡献就产生贡献即可，因为不能自己跟自己产生贡献，所以不用考虑某两个数产生贡献的不同方式会对父亲的答案产生影响。因此直接跑一遍 dfs，从叶子节点开始对父亲进行贡献即可，看不懂的同学可以看看代码，自认为码风优良。

考虑包含 $\frac{a}{2}$ 的连通块，因为包含 $\frac{b}{2}$ 的连通块同理。

由于先与其他牛组队是最优的，因此以 $\frac{a}{2}$ 为根，从叶子递归上来，统计答案，最后再判一下如果根还可以通过自己跟自己组队的方式产生贡献，由于是两头牛产生 $1$ 的贡献，所以总共产生 $\frac{n_i}{2}$ 的贡献。

如果 $\frac{a}{2}$ 与 $\frac{b}{2}$ 在同一个连通块呢？确实可以，但一定是 $a = b$ 的情况，因为 $\frac{a}{2} + \frac{b}{2} = a$，解得 $b = a$，相当于是同一个点，但由于打了标记，所以不用考虑。

似乎除了自环不会出现其他环，因此是二叉树？懒得想了，留给聪明的读者思考吧。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
unordered_map<int, int> f;
vector<int> v[200010];
int d[200010], num[200010], ans;
int n, a, b;
bool vis[200010];
inline void dfs(int x, int fa) {
	vis[x] = 1;
	for (auto u : v[x]) {
		if (!vis[u]) {
			dfs(u, x);
		}
	}
	if (fa != 0) {  //放后面就是先儿子后父亲，放 dfs 前面相反
		if (num[fa] > num[x]) {
			num[fa] -= num[x];
			ans += num[x];
			num[x] = 0;
		} else {
			num[x] -= num[fa];
			ans += num[fa];
			num[fa] = 0;
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> a >> b;
	for (int i = 1; i <= n; i++) {
		cin >> num[i] >> d[i];
		f[d[i]] = i;
	}
	for (int i = 1; i <= n; i++) {
		if (f.count(a - d[i])) {
			v[i].push_back(f[a - d[i]]);
			v[f[a - d[i]]].push_back(i);
		}
		if (a != b && f.count(b - d[i])) {
			v[f[b - d[i]]].push_back(i);
			v[i].push_back(f[b - d[i]]);
		}
	}
	if (a % 2 == 0 && f.count(a / 2)) {
		dfs(f[a / 2], 0);
		ans += num[f[a / 2]] / 2;
	}
	if (a != b && b % 2 == 0 && f.count(b / 2)) {
		dfs(f[b / 2], 0);
		ans += num[f[b / 2]] / 2;
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			dfs(i, 0);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：A2ure_Sky (赞：1)

## 简化题意

每个奶牛有一个 ID，并且对于每个 $i$，有 $n_i$ 头奶牛的 ID 都是 $d_i$，要给奶牛们做匹配，求最大匹配数。

匹配规则如下：

- 两头牛不是同一头。

- 它们的 $d_i$ 之和等于 $A$ 或 $B$。

注意要开 `long long`。

## 分析

像这种求匹配数的题目，如果先从简单的方面去想的话，通常会考虑建图，或者是考虑维护一个堆之类的，当然这只是一个初步的想法，不代表一定可以这样做。

由样例可知，匹配只有两种情况，一种是不同的 $d_i$ 之间的匹配，另一种是相同的 $d_i$ 之间的匹配。

#### 我们先不考虑相同的 $d_i$ 之间的匹配，看看这种情况怎么做。

因为我们只关心匹配数而不关心怎样匹配，所以可以将 ID 都是 $d_i$ 的奶牛们看做一个点，该点的点权即为 $n_i$，那么一个匹配就可以看做一条边。

注意到，对于一个点最多连两条边，因为 $d_i$ 之和只能是 $A$ 或者 $B$，换句话说，这张图就是一条条链。

对于点 $u$ 和 $v$ 的匹配，产生的贡献为 $\min(n_u,n_v)$。

考虑一条链，因为一个点连着两条边不太好考虑，所以我们先考虑链的两端，由于端点 $u$ 只能和一个点 $v$ 匹配，所以直接匹配肯定不会劣，于是我们直接匹配 $u$ 和 $v$：

- 将两个点同时减去 $\min(n_u,n_v)$。
- 答案加上 $\min(n_u,n_v)$。

做完如上操作后，我们发现点 $v$ 变成了新的点 $u'$，于是我们可以重复以上操作，得出答案。

**现在回到问题本身，相同 ID 之间也可能匹配，和我们建出来图怎么以及以上做法如何相适应呢？**

你会发现不太好适应，但事实上，我们会发现这两种匹配方式之间是有优先级的，一定是先匹配不同的 $d_i$，再匹配相同的 $d_i$。

为什么呢？考虑如下样例：

```
2 4 5
11 2
5 3
```

我们发现有两种匹配方式：

- ID 为 2 的先自己跟自己产生 5 组匹配，剩下一个 ID 为 2 的和 ID 为 3 的产生 1 组匹配，答案为 6。

- ID 为 2 的先和 ID 为 3 的产生 5 组匹配，剩下的六个 ID 为 2 的自己跟自己产生 3 组匹配，答案为 8。

为什么后者比前者优呢？因为在前者，没人跟 ID 为 3 的匹配了，多余的 ID 为 3 的被浪费了，没有参与匹配，但是自己跟自己始终是可以匹配的，不需要借助别人，不会被浪费，所以可以放在最后匹配，以确保总的浪费最少。

**细节**：注意到 subtask 1：$A=B$ 的情况，不要建重边，导致边的度数计算错误。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long 

using namespace std;
const int maxn=2e5+5;

int N,A,B,ans;
int deg[maxn],n[maxn],d[maxn];
vector<int> e[maxn];
map<int,int> m;
bool vis[maxn];

inline void add(int i,int j){ 
	e[i].emplace_back(j),e[j].emplace_back(i);
}

void dfs(int u){
	vis[u]=true;
	for(int v:e[u]){
		if(vis[v]) continue;
		int tmp=min(n[u],n[v]);
		ans+=tmp;
		n[u]-=tmp,n[v]-=tmp;
		dfs(v);
	}
	
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin>>N>>A>>B;
	
	for(int i=1;i<=N;i++){
		cin>>n[i]>>d[i];
		m[d[i]]=i;
	}
	
	for(int i=1;i<=N;i++){
		int D=d[i];
		if(2*D<A && m[A-D]){
			int j=m[A-D];
			deg[i]++,deg[j]++;
			add(i,j);
		}
		if(A!=B && 2*D<B && m[B-D]){
			int j=m[B-D];
			deg[i]++,deg[j]++;
			add(i,j);
		}
	}
	
	for(int i=1;i<=N;i++)
		if(!vis[i]&&deg[i]==1) dfs(i);
	
	for(int i=1;i<=N;i++)
		if(2*d[i]==A||2*d[i]==B)
			ans+=n[i]/2;
		
	cout<<ans;
	return 0;
}
```

---

## 作者：ztrztr (赞：1)

## 题目链接
<https://www.luogu.com.cn/problem/P12026>

## 算法 & 数据结构
图论，拓扑排序，建图。

## 思路
### Subtask 1
这个 Subtask 是 $A = B$。

我们首先想到建立一个图，每个 ID 号码为一个点，如果有一个 ID 的牛可以和另一个 ID 的牛交流，那么我们建立一个从第一个 ID 到第二个 ID 的边。

因为题目定义，所以如果一个 ID 可以和另外一个 ID 交流，另外一个 ID 也可以和这个 ID 交流。

由于 $A = B$，那么每一个 ID 最多存在一个 ID 可以交流，所以一共有很多独立的 ID 对，每个 ID 对的两个 ID 可以互相交流。

答案就是统计一下每个 ID 对就行了。

### 满分
我们假定 $A \not = B$，因为 $A = B$ 的情况分析过了。

由于一个点的度数最多为 $2$，那么只有可能是一个环或者一个链加一堆自环。

可以通过假设一个点是 $x$，然后根据一个边上的两点的和是 $A$ 或 $B$ 来证明不可能存在环。

那么只有可能是一个链加一堆自环了，可以用拓扑排序，然后计算。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, a, b;
int d[1000005], m[1000005], con[1000005], ans, c[1000005], su[1000005], in[1000005], vis[1000005];
vector <int> e[200005];
map <int, int> mp, mi;

signed main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);
	cin >> n >> a >> b;
	for (int i = 1; i <= n; i ++) {
		cin >> m[i] >> d[i];
		mp[d[i]] += m[i];
		mi[d[i]] = i;
	}
	for (int i = 1; i <= n; i ++) {
		if (mp[a - d[i]]) {
			

			e[i].push_back(mi[a - d[i]]);
			in[mi[a - d[i]]] ++;
		}
		if (mp[b - d[i]] && a - d[i] != b - d[i]) {
			
			if (a - d[i] != b - d[i]) e[i].push_back(mi[b - d[i]]), in[mi[b - d[i]]] ++;
		} 
	}

	queue <int> q;
	for (int i = 1; i <= n; i ++) if (in[i] == 1) q.push(i);
	while (q.size()) {
		int nw = q.front();
		q.pop();
		for (auto x : e[nw]) {
			if (vis[x]) continue;
			if (x == nw) ans += m[x] / 2, m[x] %= 2;
			else {
				int tmp = min(m[nw], m[x]);
				ans += tmp;
				m[x] -= tmp;
				m[nw] -= tmp;
			}
			if (-- in[x] == 1) q.push(x);
		}
		vis[nw] = 1;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：lhz2022 (赞：1)

题面也是比较清楚的。

把能够通话抽象成一个图，就是说如果 $d_i+d_j=a$ 或 $d_i+d_j=b$ 则把 $i,j$ 连接一条边。

那么最后我们得到的图是一个怎么样的图呢？首先，由于每个 $d_i$ 都互不相同，所以我们可以得知，一个节点最多只能和两个节点连边。

其次，图中不可能存在环。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9fo7w06g.png)此时如果 $a=b$，则节点 $1$ 的权值将会等于节点 $4$ 的权值，不满足题目中的两两不等的条件！![](https://cdn.luogu.com.cn/upload/image_hosting/jc25fm9h.png)

这里既不能是 $a$ 也不能是 $b$，否则将会存在 $d_i=d_j$，也不符合题意。

我们就可以知道：我们生成出来的图一定是由链组成的森林。

考虑一项比较特殊的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/4nsepxmh.png)

我们尽量使奶牛数量多的优先和 $n$ 分配。

如果存在 $d_i\times2=a$ 或 $d_i\times2=b$，那么它自己就可以和编号和自己相同的人通讯，我们一定要尽量让 $d_i$ 和别的奶牛分配，因为除此之外它还能和自己通讯。容易证明，$d_i$ 一定是链的头或者尾。

对于每一条链，我们可以通过 dfs 的方法把链暂时存放在数组中，方便我们计算这一条链的贡献。

大致是这样求的：

```cpp
for(int j=1;j<sz;++j){
	int xx=min(cnt[r[j]],cnt[r[j+1]]);
	ans+=xx;
	cnt[r[j]]-=xx,cnt[r[j+1]]-=xx;
}
```

最后统计总和即可，时间复杂度线性。

[代码](https://www.luogu.com.cn/paste/15ej9bkq)

---

## 作者：LittleAcbg (赞：1)

并不难的一道题目。首先，我们画一张图，将可以通讯的奶牛连起来。例如 $A=3,B=5$ 时：

![](https://cdn.luogu.com.cn/upload/image_hosting/11x49vyo.png)

例如 $2$ 和 $3$ 之间有连边是因为 $2+3=5=B$，边权代表两者的和。

还可以多画几张图观察，会发现图总是**一些**链（注意不止一个），也可能有自环（当 $A$ 或 $B$ 为偶数时产生）。

当然，有的 ID 可能没有奶牛，这个时候图上的链会被割成更小的链。可以发现每一条链的端点一定是最大的。我们只需要从大到小枚举端点，然后 DFS 处理一条链即可。注意特判自环的情况。

ID 太大，需要进行离散化处理。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+9;
int n,a,b;
bool vst[N];
long long ans;
map<int, int> id;
struct Info {int n,d;} t[N];
bool operator < (const Info&a, const Info&b) {return a.d < b.d;}
void dfs(int u)
{
	vst[u] = 1;
	if (id.count(a - t[u].d)) // 尝试 A 类通讯
	{
		int v = id[a - t[u].d],delta = min(t[u].n, t[v].n);
		if (u == v) delta = t[u].n / 2; // 特判自环
		t[u].n -= delta;
		t[v].n -= delta;
		ans += delta;
		if (!vst[v]) dfs(v);
	}
	if (id.count(b - t[u].d)) // 尝试 B 类通讯
	{
		int v = id[b - t[u].d],delta = min(t[u].n, t[v].n);
		if (u == v) delta = t[u].n / 2; // 特判自环
		t[u].n -= delta;
		t[v].n -= delta;
		ans += delta;
		if (!vst[v]) dfs(v);
	}
}
int main()
{
	scanf("%d%d%d", &n, &a, &b);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &t[i].n, &t[i].d);
	sort(t + 1, t + n + 1); // 按 ID 从大到小排序，便于从大到小枚举所有 ID
	for (int i = 1; i <= n; ++i) id[t[i].d] = i; // 离散化数组，注意不是原题 ID
	for (int i = n; i >= 1; --i) if (!vst[i]) dfs(i); // 从大到小枚举出现了的 ID，DFS 处理链条
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：nbhs23a28 (赞：1)

本题可以说是银组最简单的一道题。省流思路提示：贪心。~~（怎么铜组和银组出了三道贪心）~~

根据题意，对于每个 $d_i$，有且只有 $A-d_i,B-d_i$ 可与之匹配。那么，如何匹配才能最大化通信对数呢？我们不妨按照 $d_i$ 排序，对于最小的 $d_i$，显然应优先与 $B-d_i$ 匹配，因为 $B-d_i$ 只能与之匹配，其余尽可能地与 $A-d_i$ 匹配（贪心），同理对于次小值及每一个 ID，按序逐个进行操作即可。

实现细节见代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
long long aa,b,d[200010],ans;
struct Node{
 int cnt,dd;
 bool operator<(const Node& x){
  return dd<x.dd;
 }
}a[200010];
signed main()
{cin>>n>>aa>>b;
 if(aa==b) aa=0;
 for(int i=1;i<=n;i++)
 cin>>a[i].cnt>>a[i].dd;
 sort(a+1,a+1+n);
 for(int i=1;i<=n;i++)
 d[i]=a[i].dd;
 for(int i=1;i<=n;i++)
 {int id1=lower_bound(d+1,d+1+n,b-d[i])-d;
  if(id1<i) break;
  if(a[i].cnt==0) continue;
  if(d[id1]==b-d[i])
  {if(id1==i)
   {ans+=a[i].cnt/2;
    break;
   }
   if(a[i].cnt<=a[id1].cnt)
   {ans+=a[i].cnt;
    a[id1].cnt-=a[i].cnt;
    a[i].cnt=0;
    continue;
   }
   ans+=a[id1].cnt;
   a[i].cnt-=a[id1].cnt;
   a[id1].cnt=0;
  }
  int id2=lower_bound(d+1,d+1+n,aa-d[i])-d;
  if(id2<i||id2==n+1) continue;
  if(d[id2]==aa-d[i])
  {if(id2==i)
   {ans+=a[i].cnt/2;
    a[i].cnt=a[i].cnt%2;
    continue;
   }

   if(a[i].cnt>=a[id2].cnt)
   {ans+=a[id2].cnt;
    a[i].cnt-=a[id2].cnt;
    a[id2].cnt=0;
   }
   else
   {ans+=a[i].cnt;
    a[id2].cnt-=a[i].cnt;
    a[i].cnt=0;
   }
  }
 }
 cout<<ans;
}
```

---

## 作者：fanminghao000 (赞：1)

## 题解

发现题解区的大佬基本都是用图论建模 + 拓扑排序做的，但本蒟蒻根本想不到图论怎么做，所以这里给一种更直接的贪心方法。

先说结论，将 $d$ 升序排列后，$d_i$ 应该优先和 $B-d_i$ 配对，再和 $A-d_i$ 配对。

证明显然，我们想让配对数尽可能的多，就要物尽其用，把能匹配的都匹配上。将 $d$ 升序排序后考虑，对于 $d_i$ , $B-d_i$ 已经是最后一次可能的匹配了，而 $A-d_i$ 还可能可以和 $B-(A-d_i)=d_i+B-A$ 配对，所以我们要榨干 $B-d_i$ 的最后一点利用价值，先和它匹配。

实现起来也并不难，就是将 $d$ 排序后分别和 $B-d_i$ 和 $A-d_i$ 算贡献。值域太大的话开个 map 就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int,int> 
#define fi first
#define se second
vector<int> v;
map<int,int> id;
bool cmp(pii x,pii y){
	return x.se<y.se;
}
int n,a,b,ans=0;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){
		int x,d;cin>>x>>d;
		id[d]=x;
		v.push_back(d);
	}
	sort(v.begin(),v.end());
	for(auto x:v){
		int pa=a-x,pb=b-x;
		if(id[pb]>0&&pb>=0){//应该优先匹配pb 
			if(pb==x) ans+=id[pb]/2,id[pb]%=2;
			else{
				int mi=min(id[x],id[pb]);
				ans+=mi;
				id[x]-=mi,id[pb]-=mi;
			}
		} 
		if(id[pa]>0&&pa>=0){
			if(pa==x) ans+=id[pa]/2,id[pa]%=2;
			else {
				int mi=min(id[x],id[pa]);
				ans+=mi;
				id[x]-=mi,id[pa]-=mi; 
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Yiyi_52MIYEON1314 (赞：0)

# 题意
有 $N$ 个不同的号码，对于每一个唯一号码 $d_i$，有 $n_i$ 头奶牛共享它。

当两头不同的奶牛的号码和为 $A$ 或 $B$ 时可以通话，且每头奶牛只能参加一个通话。

求最多有多少对通话。

# 思路
考虑建图连边。

那么每头奶牛出度最多为 $2$，可以连向号码为 $A-d_i$ 或 $B-d_i$ 的奶牛。当 $A=B$ 是时连 一条。

我们可以发现这个图除自环外无其他环，证明如下。

我们设三个点构成了环分别是 $a$，$b$，$c$。设 $a+b=A$，因为号码是唯一的，所以三个点互不相同，所以 $b+c=B$，但 $a+c$ 无论等于多少都会出现相同的情况，所以不成立。   

最优方案显然是先让入度为 $0$ 的点先配对，然后依次往上，所以用拓扑排序的思想即可实现。

# 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int M=2e5+10;
int N,A,B,n[M],d[M],ans,in[M];
map<int,int> mp;
vector<int> e[M];
queue<int> q;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	freopen("skiing.in","r",stdin);
	freopen("skiing.out","w",stdout);
	cin>>N>>A>>B;
	for(int i=1;i<=N;i++)cin>>n[i]>>d[i],mp[d[i]]=i;//方便后面查询 
	for(int i=1;i<=N;i++){	//最多连两条边 
		//反正后面都会遍历到mp[A-d[i]]/mp[A-d[i]]，随便谁朝谁连都可以 
		if(d[i]<=A&&mp[A-d[i]])e[i].push_back(mp[A-d[i]]),in[mp[A-d[i]]]++;
		if(A==B)continue;
		if(d[i]<=B&&mp[B-d[i]])e[i].push_back(mp[B-d[i]]),in[mp[B-d[i]]]++;
	}
	//拓扑顺序 
	for(int i=1;i<=N;i++)if(in[i]==1)q.push(i);	//只有一条边的优先抵消 
	while(!q.empty()){
		int cur=q.front();q.pop();
		for(auto i:e[cur]){
			if(i==cur){	//自环 
				ans+=n[i]/2;
				n[i]%=2;
				continue;
			}
			if(n[i]){	//有贡献 
				int res=min(n[i],n[cur]);
				ans+=res;
				n[i]-=res,n[cur]-=res;
				q.push(i);//删掉一条边后也只剩一条了 
			}
		}
	}
	cout<<ans; 
	return 0;
}

```
### 谢谢！

---

## 作者：gdutliuyun827 (赞：0)

## P12026 [USACO25OPEN] Compatible Pairs S 题解

### 思路
本题是一道图论题。简单来说就是连接 $d_{i}$ 和 $A-d_{i}$，$d_{i}$ 和 $B-d_{i}$。特别的，当 $A=B$ 时，$d_{i}$ 只向 $A−d_{i}$ 建边。

接着，我们自己画几个图就不难发现一个规律：图中不可能有长度 $\ge3$ 的环。即图是一个或一些链条和长度 $<3$ 的环。因此要使最终答案最大，自然每条链或环是从一端往另一端进行匹配。于是这个图我们就可以进行拓扑排序。

注意：本题答案需要开 long long，判断 $A=B$ 的情况，特判自环。

### 代码

```cpp
#include <bits/stdc++.h>

#define maxn 200005

using namespace std;

struct cow
{
    int id,num;
};

struct edge
{
    int to,nx;
};

cow cw[maxn];
int head[maxn];
edge a[maxn*2];
map<int,int> id;
int ru[maxn];
bool vis[maxn];

bool cmp(cow a,cow b)
{
    return a.id<b.id;
}

void add_edge(int x,int y,int &cnt)
{
    a[cnt].to=y;
    a[cnt].nx=head[x];
    head[x]=cnt++;
}

int main()
{
    int n,x,y;   //x=A,y=B
    cin>>n>>x>>y;

    for(int i=0;i<n;i++)
        cin>>cw[i].num>>cw[i].id,id[cw[i].id]=i;

    int m=1;
    for(int i=0;i<n;i++)
    {
        if(id.count(x-cw[i].id))
            add_edge(i,id[x-cw[i].id],m),ru[id[x-cw[i].id]]++;
        if(id.count(y-cw[i].id)&&x!=y)  //A=B 就不再建一条边
            add_edge(i,id[y-cw[i].id],m),ru[id[y-cw[i].id]]++;
    }
    //建图

    queue<int> que;
    for(int i=0;i<n;i++)
        if(ru[i]==1)    que.push(i),vis[i]=1;  //由于建双向图，所以入度为1即可

    long long ans=0;   //开 long long
    while(!que.empty())
    {
        int h=que.front();
        que.pop();

        for(int i=head[h];i;i=a[i].nx)
        {
            int to=a[i].to;

            if(h==to)   //特判自环
            {
                ans+=cw[h].num/2;
                cw[h].num-=cw[h].num/2*2;
                vis[h]=1;
                continue;
            }

            int tp=min(cw[h].num,cw[to].num);
            ans+=tp;
            cw[to].num-=tp;
            cw[h].num-=tp;

            if(!vis[a[i].to])
                que.push(to);
            vis[to]=1;
        }
    }

    cout<<ans<<endl;

    return 0;
}

```

---

