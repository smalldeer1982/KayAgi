# Count Seconds

## 题目描述

Cirno has a DAG (Directed Acyclic Graph) with $ n $ nodes and $ m $ edges. The graph has exactly one node that has no out edges. The $ i $ -th node has an integer $ a_i $ on it.

Every second the following happens:

- Let $ S $ be the set of nodes $ x $ that have $ a_x > 0 $ .
- For all $ x \in S $ , $ 1 $ is subtracted from $ a_x $ , and then for each node $ y $ , such that there is an edge from $ x $ to $ y $ , $ 1 $ is added to $ a_y $ .

Find the first moment of time when all $ a_i $ become $ 0 $ . Since the answer can be very large, output it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case:

- At time $ 0 $ , the values of the nodes are $ [1, 1, 1] $ .
- At time $ 1 $ , the values of the nodes are $ [0, 1, 1] $ .
- At time $ 2 $ , the values of the nodes are $ [0, 0, 1] $ .
- At time $ 3 $ , the values of the nodes are $ [0, 0, 0] $ .

So the answer is $ 3 $ .

 In the second test case: - At time $ 0 $ , the values of the nodes are $ [1, 0, 0, 0, 0] $ .
- At time $ 1 $ , the values of the nodes are $ [0, 1, 0, 0, 1] $ .
- At time $ 2 $ , the values of the nodes are $ [0, 0, 1, 0, 0] $ .
- At time $ 3 $ , the values of the nodes are $ [0, 0, 0, 1, 0] $ .
- At time $ 4 $ , the values of the nodes are $ [0, 0, 0, 0, 1] $ .
- At time $ 5 $ , the values of the nodes are $ [0, 0, 0, 0, 0] $ .

 So the answer is $ 5 $ .In the third test case:

The first moment of time when all $ a_i $ become $ 0 $ is $ 6\cdot 998244353 + 4 $ .

## 样例 #1

### 输入

```
5
3 2
1 1 1
1 2
2 3
5 5
1 0 0 0 0
1 2
2 3
3 4
4 5
1 5
10 11
998244353 0 0 0 998244353 0 0 0 0 0
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
1 3
7 9
5 6
1293 1145 9961 9961 1919
1 2
2 3
3 4
5 4
1 4
2 4
6 9
10 10 10 10 10 10
1 2
1 3
2 3
4 3
6 3
3 5
6 5
6 1
6 2```

### 输出

```
3
5
4
28010
110```

# 题解

## 作者：Cxny (赞：12)

可以以网络流类比来理解题意。

每个点都有一个初始流量，每秒钟向下游每一个点推送 $1$ 的流量，求多少秒后流完。

注意，每个点每秒减少的流量为 $1$，而非推送的流量。

---

考虑初始流量不为 $0$ 且有上下游的点，其接受上游所有流量而向下游输送 $1$ 的流量。因此，该点流完的时间自然是**上游流到该点的流量与初始流量之和**。

但有可能该点流量流完后上游流量还未流到，即点权在过程中变为 $0$，后来又变为正数。

由于 $n$ 个点的 DAG 最长路长度一定不大于 $n$ ，因此我们可以先模拟前 $n$ 秒。此时，**所有可能被流到的点一定有流量，即在此之后不会有点权在中途变为 $0$。**

这是因为一个点如果被流到，上游输送的流量不小于 $1$，而其每秒向下游只推送 $1$ 的流量，因此在上游全部流完之前其点权**单调不减**。

而在 $n$ 秒内流量已经沿着路径得到了充分流动，所有能被流到的点都已经被流到。

模拟 $n$ 轮之后再按最开始提到的方法跑拓扑即可。

注意特判初始流量全为 $0$ 的情况。

完整代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e3 + 10, inf = 2e9, mod = 998244353;
int T, n, m, a[maxn], tmp[maxn], deg[maxn], out[maxn], t;
vector<int> edge[maxn];
queue<int> q;
signed main(){
	scanf("%lld", &T);
	while(T--){
		scanf("%lld%lld", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), edge[i].clear(), out[i] = deg[i] = 0;
		for(int i = 1; i <= m; i++){
			int x, y;
			scanf("%lld%lld", &x, &y);
			edge[x].push_back(y);
			deg[y]++, out[x]++;
		}
		bool flag = 0;
		for(int i = 1; i <= n; i++) if(a[i]){
			flag = 1; break;
		}
		if(!flag){
			puts("0");
			continue;
		}
		flag = 0;
		for(int i = 1; i <= n; i++){
			bool suc = 0;
			for(int j = 1; j <= n; j++) if(a[j]){
				a[j]--;
				for(auto v : edge[j]) tmp[v]++;
			}
			for(int j = 1; j <= n; j++){
				a[j] += tmp[j], tmp[j] = 0;
				if(a[j]) suc = 1;
			}
			if(!suc){
				printf("%lld\n", i);
				flag = 1; break;
			}
		}
		if(flag) continue;
		for(int i = 1; i <= n; i++) if(!deg[i]) q.push(i);
		for(int i = 1; i <= n; i++) if(!out[i]) t = i;
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(auto v : edge[u]){
				(a[v] += a[u]) %= mod;
				deg[v]--;
				if(!deg[v]) q.push(v);
			}
		}
		printf("%lld\n", (a[t] + n) % mod);
	}
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：2)

~~前前后后想了几天才想明白，拉了。~~

看到这个题首先朴素的想法是：

+ 拓扑排序。
+ 每个点变为 $0$ 的时间是这个点点权以及之前所有点权之和。
+ 答案为最大的时间。

但是这是不对的，存在一些点会变成 $0$ 然后又变成正数最后再变成 $0$。

如何处理这样的情况呢？我们考虑这种情况最坏会出现在什么时候。

定义源点——入度为 $0$ 的点，汇点——出度为 $0$ 的点。

这种情况为什么会出现，就是说这个点自己本身的点权已经减为 $0$，而来自源点的权值还没到达。如果来自源点的权值到达过了，它减为 $0$ 之后就不可能再变回正数。

对于一张 DAG，源点到汇点的最长路显然不会超过 $n$。走过这一条最长路之后，来自源点的权值每个点都收到了，所以也就说明，最多 $n$ 秒之后，这种情况不再出现。

既然排除了这种情况，我们现在就可以直接拓扑了。

总复杂度 $O(tn^2)$。

几个重要的点：

+ 记得检查 $ans\le n$ 的情况。
+ 及时清空。
+ 及时取模。

```cpp 
#include <queue>
#include <vector>
#include <iostream>
#define rep(i,l,r) for(i=l;i<=r;++i)
const int N=1005,p=998244353;
using namespace std;
vector<int> e[N];
queue<int> q;
bool fl;
int t,n,m,i,j,u,v,cnt,mid;
int in[N],out[N],delta[N],order[N];
long long f[N];
inline const bool check(int id)
{int i;
	rep(i,1,n)
		if(f[i])
			return false;
	if(id!=-1)
		cout<<id<<"\n";
	return true;;
}
int main()
{
//	ios::sync_with_stdio(false);
//	cin.tie(0);
	cin>>t;
	while(t--)
	{
		cnt=0;
		cin>>n>>m;
		rep(i,1,n)
		{
			vector<int>().swap(e[i]);
			in[i]=out[i]=0;
		}
		rep(i,1,n)
			cin>>f[i];
		rep(i,1,m)
		{
			cin>>u>>v;
			++in[v];
			++out[u];
			e[u].emplace_back(v);
		}
		if(check(0))
		    continue;
		rep(j,1,n)
			delta[i]=0;
		rep(i,1,n)
		{
			rep(j,1,n)
				if(f[j])
				{
					--f[j];
					for(auto nxt:e[j])
						++delta[nxt];
				}
			rep(j,1,n)
			{
				f[j]+=delta[j];
				delta[j]=0;
			}
			if(check(i))
				break;
		}
		if(check(-1))
			continue;
		rep(i,1,n)
			if(in[i]==0)
			{
				order[++cnt]=i;
				q.push(i);
			}
		while(!q.empty())
		{
			mid=q.front();q.pop();
			for(auto nxt:e[mid])
			{
				if(!--in[nxt])
				{
					order[++cnt]=nxt;
					q.push(nxt);
				}
			}
		}
		rep(i,1,n)
		{
			for(auto nxt:e[order[i]])
				(f[nxt]+=f[order[i]])%=p;
		}
		cout<<(n+f[order[n]])%p<<'\n';
	}
}
```

---

## 作者：Andrewzdm (赞：2)

赛时把题意读错了，凉了。

整个流程就好比是一个漫水的过程。

众所周知，在没有什么思路的时候，比较好的办法是手玩模拟一下样例。

不妨先思考没有点权为 $0$ 的情况：入度为 $0$ 的点只减不增，把自己的点权贡献给出边连向的点，点权减到 $0$ 之后删去，从而又有新的一批点只减不增……

**可不就是拓扑排序吗！** 只要把拓扑序在前面的点的点权一直传递下去到汇点，就结束了，这部分很好算。

但问题出现了：我们发现汇点有可能点权为0，这个时候不会把点权排出去，不能用上面的方法直接算。

然而经过 $n$ 轮后，所有的点的点权一定可以传递到汇点，假如在这前 $n$ 轮中不是所有点的点权都变成了 $0$，那么一定会使得汇点点权 $>0$。

上代码，复杂度 $O(nm+n^2)$。一些细节见代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int mod = 998244353;
int n, m;
vector<int> g[maxn];
int in[maxn], a[maxn], add[maxn];
int ans;
bool del[maxn];
queue<int> q;
int tpo[maxn], tim;
inline int read();

void bruteforce()
/*
这里a和add的值都不要取模
因为可能涉及a是998244353的倍数的情况，取模后会出现错误
而且此处不取模是不会溢出的
*/
{
    ans++;
    fill(add + 1, add + n + 1, false);
    for(int i = 1; i <= n; ++i)
        if(a[i] > 0)
            for(int v : g[i])
                add[v]++;
    for(int i = 1; i <= n; ++i)
        if(a[i] > 0)
            a[i]--;
    for(int i = 1; i <= n; ++i) a[i] += add[i];
    return;
}

void toposolve()
{
    tim = 0;
    for(int i = 1; i <= n; ++i)
        if(in[i] == 0)
            q.push(i);
    while(!q.empty())
    {
        int p = q.front(); q.pop();
        tpo[++tim] = p;
        for(int v : g[p])
            if((--in[v]) == 0)
                q.push(v);
    }
    for(int i = 1; i <= n; ++i)
        a[i] %= mod;
    for(int i = 1; i <= n; ++i)
    {
        for(int j : g[tpo[i]])
            a[j] = (a[j] + a[tpo[i]]) % mod;
    }
    ans = (ans + a[tpo[n]]) % mod;
    return;
}

void work()
{
    ans = 0;
    n = read(); m = read();
    fill(in + 1, in + n + 1, 0);
    fill(del + 1, del + n + 1, false);
    for(int i = 1; i <= n; ++i) a[i] = read();
    for(int i = 1; i <= n; ++i) g[i].clear();
    for(int i = 1; i <= m; ++i)
    {
        int x, y;
        x = read(); y = read();
        g[x].push_back(y);
        in[y]++;
    }
    for(int i = 1; i <= n; ++i)
    {
        bool flag = true;
        for(int j = 1; j <= n; ++j)
            if(a[j] != 0)
            {
                flag = false;
                break;
            }  //记得check，可能没跑满n轮就结束了
        if(flag)
        {
            cout << ans << endl;
            return;
        }
        bruteforce();
    }
    toposolve();
    cout << ans << endl;
    return;
}

int main()
{
    int T;
    T = read();
    while(T--) work();
    return 0;
}

inline int read()
{
    int x = 0; bool f = true; char ch = getchar();
    while(!isdigit(ch)) { if(ch == '-') f = false; ch = getchar(); }
    while(isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    return f ? x : -x;
}
```

---

## 作者：BigSmall_En (赞：2)

## [CF1704E](https://codeforces.com/contest/1704/problem/E) solution

> 给定一个只有 $n$ 个点 $m$ 条边且只有一个点出度为 $0$ 的有向无环图，点有点权且非负。每次可以选择将所有点权大于 $0$ 的点的点权减 $1$，同时他的每条出边上的点权 加 $+1$，问需要经过多少次才能将图中所有的点的值变为 $0$。

模拟一类简单的情况，图中只有两个点 $u,v$，存在一条从 $u$ 到 $v$ 的有向边，$u$ 点的值为 $3$，$v$ 点的值为 $0$。

发现 $u$ 点在 $0,1,2$ 三个时刻可以给 $v$ 加 $1$，所以 $v$ 点必须要给自身减 $3$ 才能变为 $0$，但是 $v$ 点不能在 $0,1,2$ 时刻给自己分别 $-1$，而只能选择在 $1,2,3$ 时刻，即自身有值的时候才能给自己减 $1$。这两个 $-1$ 的过程是存在时间差的。我们可以认为 $u$ 点在 $1$ 时刻给 $v$ 点 $+3$，$v$ 点可以在自己获得贡献的同一时刻将自己的值减去。

那么再假设现在有 $w$ 点，存在一条 $v$ 到 $w$ 的有向边，$w$ 点取值为 $0$。容易发现 $w$ 点只能在 $2,3,4$ 时刻给自己 $-1$，也就是说 $v$ 点在 $2$ 时刻给 $w$ 点 $+3$。

于是我们定义一个桶 $bot_{i,j}$，表示 $i$ 点在 $j$ 时刻从前驱节点得到的值的总和。

对于 $i$ 点的初始值 $a_i$，我们可以认为存在一个超级点在 $0$ 时刻给 $i$ 点 $+3$。

```cpp
for(int i=1;i<=n;++i){
    a[i]=read();
    bot[i][0].lef=a[i];
}
```

假设现在存在有向边 $u\to v$，那么可以得到转移
$$
bot_{v,j+1}\gets bot_{u,j}
$$
因为这是个有向图，所以可以考虑使用拓扑排序进行无后效性的转移。

对每条边的转移是 $O(n)$ 的，所以整个拓扑的时间复杂度是 $O(nm)$。

```CPP
for(int i=1;i<=m;++i){
    int u=read(),v=read();
    edge[u].push_back(v);++ind[v];
}
queue<int>q;
for(int i=1;i<=n;++i)
    if(!ind[i]){q.push(i);}
while(!q.empty()){
    int u=q.front();q.pop();
    for(auto v:edge[u]){
        for(int i=1;i<=n;++i)
            bot[v][i]=bot[v][i]+bot[u][i-1];
        if(!--ind[v])q.push(v);
    }
}
```

现在我们求得了每个节点的 $bot$ 值，那么统计答案的时候显然不能简单地对 $bot_i$ 中的元素求和。假设我们计算了到 $j-1$ 时刻 $i$ 节点剩余的值为 $k$，且 $bot_{i,j}\neq 0$，如果 $k=0$，那么答案就是 $j+bot_{i,j}$；如果 $k>0$，那么答案才是 $k+bot_{i,j}$。

```cpp
ll ans=0;
for(int i=1;i<=n;++i){
    ll tmp=0;
    for(int j=0;j<=n;++j){
        if(bot[i][j]){
            tmp=max((ll)j,tmp);
            tmp+=bot[i][j];
        }
    }
    ans=max(ans,tmp);
}
```

但是上面的计算不足以通过此题，因为 $bot_{i,j}$ 中的值很大，甚至会超过 `__int128` 的范围，但是为了满足答案的正确性又不能时时取模。

解决这个问题还是要从题目本身入手，题目保证了只存在一个点出度为 $0$，那么只用对这个点计算答案即可。记录拓扑排序中的最后一个点为 $las$，其实答案就是计算 $bot_{las}$。（但我在做的时候竟然没看到这个条件，最后随便取了个 $las$ 发现过了，过了好几个小时重温的时候才发现有出度限制这个条件。）

这样我们用一个结构体记录这个值本身是否超过模数，和这个值对模数取模后的值，就可以开心地判断与 $j$ 的大小了。（不知道大佬们有没有更好的实现方法）

```cpp
struct number{
	bool tim;ll lef;
	inline void init(){tim=0,lef=0;}
	number(){init();}
	number operator+(const number &a){
		number tmp;
		tmp.tim=(tim|a.tim);
		if(a.lef+lef>=MOD){
			tmp.tim|=1;
			tmp.lef=a.lef+lef-MOD;
		}else tmp.lef=a.lef+lef;
		return tmp;
	}
};
number ans;
for(int j=0;j<=n;++j){
    if(bot[las][j].tim||bot[las][j].lef){
        if(!ans.tim&&ans.lef<j)ans.lef=j;
        ans=ans+bot[las][j];
    }
}
printf("%lld\n",ans.lef);
```

代码块已经很全面了，完整代码就不贴了，总时间复杂度为平方级别。

---

## 作者：DaiRuiChen007 (赞：1)

# CF1704E 题解



## 思路分析

首先考虑一个最简单的想法，统计每个点会收到多少流量，最后答案为汇点接受的流量。

但是这个想法无法处理部分 $a_i=0$ 的情况，这个时候某个点可能会在若干秒后获得流量然后开始工作。

不过也不是所有存在 $a_i=0$ 的情况都不能这么统计，如果对于某个 $a_i=0$ 的点所有的祖先都为 $0$ 那么意味着这些点不会再获得流量，那么这样的情况称为“平凡的”零权点，这样的点对的统计答案没有影响。

注意到如下的观察：

> 观察：
>
> 在至少 $n$ 秒后就不存在非“平凡”的零权点。
>
> 证明如下，考虑非“平凡”的零权点的生成，每个非“平凡”的零权点可以理解为祖先有流量正在运输，还没有抵达当前节点的点。
>
> 那么注意到一个祖先的流量到当前点的延迟时间为这两个点的距离。
>
> 由于 DAG 上最长链长度是 $\le n$ 的，因此在 $n$ 轮之后每个 $a_i>0$ 的祖先都开始向当前节点运输流量。
>
> 而且由于每个祖先运输流量的时间是连续的，因此当 $a_i=0$ 时其祖先一定没有流量还在运输。

根据上面的观察，我们可以先预处理出原图的拓扑序，然后模拟 $n$ 轮后的答案，再用一次统计计算出最终的结果。

时间复杂度 $\Theta(nm)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1001,MOD=998244353;
vector <int> G[MAXN];
int a[MAXN],deg[MAXN];
inline void solve() {
	int n,m;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]),deg[i]=0,G[i].clear();
	for(int i=1;i<=m;++i) {
		int u,v;
		scanf("%lld%lld",&u,&v);
		G[u].push_back(v);
		++deg[v];
	}
	queue <int> q;
	vector <int> ord;
	for(int i=1;i<=n;++i) if(!deg[i]) q.push(i);
	while(!q.empty()) {
		int p=q.front(); q.pop();
		ord.push_back(p);
		for(int v:G[p]) {
			--deg[v];
			if(!deg[v]) q.push(v);
		}
	}
	for(int t=1;t<=n;++t) {
		bool ok=true;
		for(int i=1;i<=n;++i) if(a[i]!=0) ok=false;
		if(ok) {
			printf("%lld\n",t-1);
			return ;
		}
		vector <int> flow;
		for(int u:ord) if(a[u]!=0) flow.push_back(u);
		for(int u:flow) {
			--a[u];
			for(int v:G[u]) ++a[v];	
		}
	}
	for(int u:ord) for(int v:G[u]) a[v]=(a[v]+a[u])%MOD;
	printf("%lld\n",(a[ord[n-1]]+n)%MOD);
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1BU4y1Y7Tc)

### 2 思路

我们可以发现，如果 $a_i$ 不为 $0$ 或者 $a_i$ 永远为 $0$，问题会更好解决（怎么解决等会再讲）。

那么，我们就可以先暴力模拟 $n$ 次。如果这 $n$ 次（或更少）模拟能够流完，就输出答案。

如果 $u$ 点可以到达 $v$ 点，那么它们的距离不超过 $n$。这意味着，模拟 $n$ 次后，如果一个点会拿到流量，它肯定已经拿到了（虽然不一定拿完，但没关系）。

在模拟完 $n$ 次后，如果 $a_i=0$，说明它的上游已经没有任何的流量可以给过来了。这样就保证 $a_i>0$ 或 $a_i$ 永远为 $0$。

那么我们可以建一个反图。在这上面找到所有流量的终点（题目保证它唯一），从这里开始。

设点 $u$ 的流量全部流完需要 $dp_u$ 的时间。

那么，$dp_u=a_u+\sum_vdp[v]$，其中 $v$ 是 $u$ 的上游。

最后输出终点的流量流完的时间即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 1000
#define mod 998244353
int t;
int n;
int m;
long long a[max_n+2];
long long cnt[max_n+2];
struct E{
	int v,nx;
};
E e[max_n+2];
int fir[max_n+2];
E e2[max_n+2];
int fir2[max_n+2];
int r[max_n+2];
long long ans;
int pos;
long long dp[max_n+2];
bool check(){
	for(int i=1;i<=n;++i){
		if(a[i])return false;
	}
	return true;
}
long long dfs(int u){
	if(~dp[u])return dp[u];
	dp[u]=a[u]%mod;
	for(int i=fir2[u];i;i=e2[i].nx)dp[u]=(dp[u]+dfs(e2[i].v))%mod;
	return dp[u];
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1704E_1.in","r",stdin);
	freopen("CF1704E_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)scanf("%lld",a+i);
		memset(fir,0,sizeof(fir));
		memset(fir2,0,sizeof(fir2));
		memset(r,0,sizeof(r));
		for(int i=1,u,v;i<=m;++i){
			scanf("%d%d",&u,&v);
			e[i]=(E){v,fir[u]};
			fir[u]=i;
			e2[i]=(E){u,fir2[v]};
			fir2[v]=i;
			++r[u];
		}
		if(check()){
			printf("0\n");
			continue;
		}
		ans=0;
		for(int ca=1;ca<=n;++ca){
			for(int i=1;i<=n;++i)cnt[i]=0;
			for(int u=1;u<=n;++u){
				if(!a[u])continue;
				--cnt[u];
				for(int i=fir[u];i;i=e[i].nx)++cnt[e[i].v];
			}
			for(int i=1;i<=n;++i)a[i]+=cnt[i];
			if(check()){
				ans=ca;
				break;
			}
		}
		if(ans){
			printf("%lld\n",ans);
			continue;
		}
		for(int i=1;i<=n;++i){
			if(!r[i]){
				pos=i;
				break;
			}
		}
		memset(dp,-1,sizeof(dp));
		printf("%lld\n",(dfs(pos)+n)%mod);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/82185827)

By **dengziyue**

---

## 作者：cachejtt (赞：1)

## 题意
你有一个有向无环图，初始在一些点上有一些值，每一秒，选取所有当前值大于零的点，将其值减一，并将其所有出度连接到的点值加一（若无出度则没有这一步），问你经过多久所有的点的值均变成 $0$。

## 思路
考虑递推，以 $f_i$ 表示第 $i$ 个点流完的时间，那么显然 $f_i$ 应当从它前面的点转移过来，这意味着那个点将会有值流入 $i$。对于转移顺序，可以预先处理，从入度为 $0$ 的点开始，逐步向下转移，每次转移完后其连向的点入度减一。

因此对于每个点 $i$，遍历其出边并更新即可。

但是注意到此时每个点的值不一定为正数，所以需要先做 $n$ 步，来保证一定有值流过所有点（若此时还有点值为 $0$，说明根本经过不了这个点）。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ll long long
#define endl "\n"
#define int ll
using namespace std;
int t,n,m,a[1005],d[1005],vis[1005],step;
vector<int> e[1005];
int q[1005];
const int p=998244353;
bool ab(){
  rep(i,1,n){
    if(a[i]>0)return 1;
  }
  return 0;
}
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  int u,v;
  rep(kk,1,t){
    memset(vis,0,sizeof(vis));
    memset(d,0,sizeof(d));
    cin>>n>>m;
    rep(i,1,n)cin>>a[i],e[i].clear();
    rep(i,1,m){
      cin>>u>>v;
      e[u].push_back(v);
      d[v]++;
    }
    
    rep(l,1,n){
      rep(i,1,n){
        if(d[i]==0 && vis[i]==0){
          vis[i]=1;
          q[l]=i;;
          for(int j:e[i])d[j]--;
          break;
        }
      }
    }
    step=0;
    while(step<=n){
      if(!ab())break;
      step++;
      nrep(i,n,1){
        if(a[q[i]]!=0){
          a[q[i]]--;
          for(int j:e[q[i]])a[j]++;
        }
      }
    }
    if(!ab()){
      cout<<step<<endl;
      continue;
    }
    
    rep(i,1,n){
      for(int j : e[q[i]]){
        a[j]+=(a[q[i]]%p);
        a[j]%=p;
      } 
    }
    cout<<(step+a[q[n]]+p)%p<<endl;
  }
  return 0;
}
```

---

## 作者：Rosent (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1704E)

一句话题意就是，在一个 DAG 上每秒非零权值的点都会将 $1$ 的权值流动到它的下一个点，求每个点权值全部流到 $0$ 的时间。**有且仅有一个点没有出边**。

我会拓扑排序 dp。

很明显假了。因为在中途可能有某个点的权值为 $0$，此时它肯定不能将权值流到下一个点。

考虑以下数据：
```
4 3
2 0 0 1
1 2
2 3
3 4
```

可以通过手动模拟得知答案为 $5$，而按照上面的策略无法得到该答案。

---

考虑改进这种贪心方法。给定的图为无边权 DAG，显然其最长路为 $m$。

在 $m$ 秒后所有的点都一定被流动到了点权。

所以我们可以先暴力模拟前 $m$ 秒，然后跑拓扑排序 dp。

时间复杂度 $O(nm)$。

注意特判。

代码：

```cpp
struct EDGE {
    int to, nxt;
}e[maxn];
int n, m, cnt = 0, idx = -1;
int head[maxn], in[maxn], out[maxn], a[maxn];

void add(int u, int v) {
    e[++cnt].nxt = head[u];
    e[cnt].to = v;
    head[u] = cnt;
}

void topo() {
    queue <int> q;
    for (int i = 1; i <= n; i++) {
        if(in[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (int i = head[t]; i; i = e[i].nxt) {
            int v = e[i].to;
            a[v] = (a[v] + a[t]) % mod;
            in[v] --;
            if(in[v] == 0) {
                q.push(v);
            }
        }
    }
}

void brute() {
    queue <int> q;
    for (int i = 1; i <= n; i++) {
        if(a[i] > 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        a[t] --;
        for (int i = head[t]; i; i = e[i].nxt) {
            int v = e[i].to;
            a[v] ++;
        }
    }
}

void clear() {
    memset(e, 0, sizeof(e));
    memset(head, 0, sizeof(head));
    memset(in, 0, sizeof(in));
    memset(a, 0, sizeof(a));
    memset(out, 0, sizeof(out));
    cnt = 0; idx = -1;
}

signed main() {
    int T;
    cin >> T;
    while (T--) {
        bool qaq = false;
        clear();
        n = read();
        m = read();
        int maxx = 0;
        for (int i = 1; i <= n; i++) {
            a[i] = read();
            maxx = max(maxx, a[i]);
        }
        for (int i = 1; i <= m; i++) {
            int u, v;
            u = read(); v = read();
            in[v] ++; out[u] ++;
            add(u, v);
        }
        if (maxx == 0) {
            cout << 0 << endl;
            continue;
        }
        for (int i = 1; i <= n; i++) {
            if (out[i] == 0) {
                idx = i;
                break;
            }
        }
        for (int i = 1; i <= m; i++) {
            brute();
            bool flag = false;
            for (int j = 1; j <= n; j++) {
                if (a[j] > 0) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                cout << i << endl;
                qaq = true;
                break;
            }
        }
        if (qaq) {
            continue;
        }
        topo();
        cout << (m + a[idx]) % mod << endl;
    }
    return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2200}$
---
### 解题思路：

读完题目之后首先有一个很朴素的想法，就是直接将 $a_i$ 全部加到其所有出边所连接的点中，直接用最大的那一个作为答案。

然后问题很快就出现了，这样的一个算法成立当且仅当对于任意的点，每一个时刻都流出了一个单位的权值，如果中途有一个点在某一个时刻到达 $0$ 但后来又被增加至一个正数，就会造成计算失误。

再次转化上面的情况，发现这种事情发生当且仅当从那个没有出边的点开始到某一个有权值的点的某一条路径上存在一个或者更多的初始权值为 $0$ 的点。

具体考虑某一条从无出边那那个点到一个无入边的点的路径，在进行一开始的那种快速操作之前，要求对于这条路径上的一个前缀不等于 $0$。可以发现，最后一个有权值的点的影响在不超过路径长度次操作之后一定会让前缀部位 $0$，如果某一个点此时为 $0$，可以证明这个点的后缀也一定全部为 $0$。

由于任意的路径长度都不会超过 $n$，只需要先进行 $n$ 次朴素的操作，然后再用一开始的那个方法做一下就好了。

---

细节上，一个是特判一下全是 $0$ 的情况，另一种由于已经是取模过后的结果，最大的哪一个不一定是没有出边的那一个。

----
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MOD=998244353,MAXN=2005;
int T,n,m,a[MAXN],x,y,tot,head[MAXN],nxt[MAXN],num[MAXN],flag,q[MAXN],l,r,d[MAXN],maxn,tmp[MAXN],o[MAXN];
void init(){
	for(int i=1;i<=n;i++)a[i]=d[i]=o[i]=0;
	for(int i=1;i<=n;i++)head[i]=0;
	for(int i=1;i<=tot;i++)nxt[i]=num[i]=0;
	maxn=0;tot=0;
}
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		init();
		scanf("%lld%lld",&n,&m);
		flag=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			if(a[i]!=0)flag=1;
		}
		for(int i=1;i<=m;i++){
			scanf("%lld%lld",&x,&y);
			add(x,y);
			d[y]++;o[x]++;
		}
		if(flag==0){
			printf("0\n");
			continue;
		}
		for(int i=1;i<=n;i++){
			flag=0;
			for(int j=1;j<=n;j++){
				if(a[j]==0)continue;
				a[j]--;
				for(int k=head[j];k;k=nxt[k])
				tmp[num[k]]++;
			}
			for(int k=1;k<=n;k++)
			a[k]+=tmp[k],tmp[k]=0;			
			for(int j=1;j<=n;j++)
			if(a[j]!=0)flag=1;
			if(flag==0){
				printf("%lld\n",i);
				break;
			}
		}
		if(flag==0)continue;
		r=0;l=1;
		for(int i=1;i<=n;i++)
		if(d[i]==0)q[++r]=i;
		while(l<=r){
			int now=q[l];
			for(int i=head[now];i;i=nxt[i]){
				a[num[i]]=(a[num[i]]+a[now])%MOD;
				d[num[i]]--;
				if(d[num[i]]==0)q[++r]=num[i];
			}
			l++;
		}
		for(int i=1;i<=n;i++)
		if(o[i]==0)
		printf("%lld\n",(a[i]+n)%MOD);
	}
	return 0;
}
/*
1
4 3
1 1 0 0
2 1
3 1
4 1

*/
```



---

