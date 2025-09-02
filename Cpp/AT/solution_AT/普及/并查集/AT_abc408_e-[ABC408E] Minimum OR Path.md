# [ABC408E] Minimum OR Path

## 题目描述

给定一个连通无向图，该图有 $N$ 个顶点和 $M$ 条边，且无自环，顶点编号从 $1$ 到 $N$，边编号从 $1$ 到 $M$。边 $i$ 双向连接顶点 $u_i$ 和 $v_i$，其边权为 $w_i$。

在从顶点 $1$ 到顶点 $N$ 的简单路径（即不会多次访问同一顶点的路径）中，求出该路径中所有边的权值的按位 $\mathrm{OR}$ 的最小可能值。

什么是按位 $\mathrm{OR}$ 运算？

非负整数 $A$ 和 $B$ 的按位 $\mathrm{OR}$，即 $A\ \mathrm{OR}\ B$，定义如下：

- 如果 $A$ 和 $B$ 的二进制表示中 $2^k$ 位至少有一位为 $1$，则 $A\ \mathrm{OR}\ B$ 的二进制表示中 $2^k(k \geq 0)$ 位上的数字为 $1$，否则为 $0$。

例如，$3\ \mathrm{OR}\ 5 = 7$（二进制表示为：$011\ \mathrm{OR}\ 101 = 111$）。
一般而言，$k$ 个非负整数 $p_1, p_2, p_3, \dots, p_k$的按位 $\mathrm{OR}$ 定义为 $(\dots ((p_1\ \mathrm{OR}\ p_2)\ \mathrm{OR}\ p_3)\ \mathrm{OR}\ \dots\ \mathrm{OR}\ p_k)$，并且可以证明这与 $p_1, p_2, p_3, \dots p_k$ 的顺序无关。

## 说明/提示

### 约束

- $2\le N\le 2×10^5$
- $N-1\le M\le 2×10^5$
- $1\le u_i\le v_i\le N$
- $0\le w_i\le2^{30}$
- 给定图为连通图。
- 所有输入值均为整数。

### 样例 1 提示：

按顺序遍历边 $1,3,5$，并按顺序访问顶点 $1,2,3,4$，最终的按位 $\mathrm{OR}$ 为 $1\ \mathrm{OR}\ 2\ \mathrm{OR}\ 3=3$。

不可能使按位 $\mathrm{OR}$ 小于 $3$，因此输出 $3$。

### 样例 2 提示：

该图可能包含重边。

## 样例 #1

### 输入

```
4 5
1 2 1
1 3 4
2 3 2
2 4 4
3 4 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3 5
1 2 1
1 2 2
1 2 3
1 2 4
2 3 4```

### 输出

```
4```

## 样例 #3

### 输入

```
8 12
4 5 16691344
5 7 129642441
2 7 789275447
3 8 335307651
3 5 530163333
5 6 811293773
3 8 333712701
1 2 2909941
2 3 160265478
5 7 465414272
1 3 903373004
6 7 408299562```

### 输出

```
468549631```

# 题解

## 作者：Moya_Rao (赞：50)

还是很兴奋的。

最近打 ABC 状态不咋好，这回搞了 $5$ 题，还是很兴奋的。

行吧！那就来讲讲这个题目吧！

就是给你一个图，有 $n$ 个点，$m$ 条无向边，每条边呢还有一个权值。要你找到从 $1$ 到 $n$ 的所有简单路径中，经过的边的权值或值最小的。要求输出这个或值。

首先可以打一个暴搜。肯定是对的，是吧，但是会超时。我赛时就是这样傻乎乎弄了一次，然后吃了一发罚时。

考虑到是或运算，肯定是有问题的。普通的搜索肯定过不了。

涉及到位运算，一般都是拆位，是吧？那就往这个方向想。

我们从高位开始枚举。为什么不从低位开始？因为有一条显而易见的结论：如果当前这一位可以为 $0$，肯定是比当前这一位为 $1$ 的答案优的。为啥啊，因为后面的所有都为 $1$ 也超不过现在这一位为 $1$。

那就行了。从高位开始枚举，尝试让最终答案的这一位填上 $0$。那咋整？并查集！

我们枚举每一条边，如果这个边的权值 $w$ 在当前枚举到的这一位上确实是 $0$，我们就可以用并查集把这个边连接的两个点弄到一个集合里去。

枚举完了，我们就判断一下，$1$ 和 $n$ 是不是联通的。如果是，那么这一位就可以为 $0$；不是的话，这一位就只能是 $1$ 咯，那 $ans$ 就要加上这一位为 $1$ 的答案了。

最后输出就可以了。

编起来很简单的，但还是附一份赛时代码吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
struct line{int u,v,w;}ln[N];
int n,m,ans,fa[N];bool is[N];
int FF(int u){return (fa[u]==u?u:fa[u]=FF(fa[u]));}
void Merge(int u,int v){fa[FF(v)]=FF(u);return;}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++)cin>>ln[i].u>>ln[i].v>>ln[i].w;
    for(int x=29;x>=0;x--){
        for(int i=1;i<=n;i++)fa[i]=i;
        for(int i=1;i<=m;i++){
            if((ln[i].w>>x)&1)continue;bool OK=1;
            for(int o=29;o>x;o--)if(!is[o]&&((ln[i].w>>o)&1))OK=0;
            if(!OK)continue;
            if(FF(ln[i].u)!=FF(ln[i].v))Merge(ln[i].u,ln[i].v);
        }
        if(FF(1)!=FF(n))is[x]=1,ans|=(1<<x);
    }
    cout<<ans<<"\n";
    return 0;
}
```

如果觉得本篇题解还不错的话，麻烦你点一个小小的赞，万分感谢！

---

## 作者：Crazyouth (赞：7)

## 分析

运用处理二进制的常用贪心策略，从大到小枚举答案的二进制下第 $t$ 位，如果能取 $0$ 就取 $0$。沿着这个思路，判断能否取 $1$ 的条件就是在不违反之前的条件的前提下，把图中所有第 $t$ 位是 $1$ 的边删除，判断 $1$ 是否还能走到 $n$。这样一来，“之前的条件”也很明确了，如果之前的某一个位置 $t_0$ 能取 $0$，在枚举到 $t_0$ 的时候我们就删除那些 $t_0$ 位是 $1$ 的边，之后永久地不访问那些边。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=200010;
struct edge
{
	int u,v,w,cu=1;
}e[N];
int fa[N];
int find(int x)
{
	if(x==fa[x]) return x;
	fa[x]=find(fa[x]);
	return fa[x];
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	int ans=0;
	for(int t=30;~t;t--)
	{
		for(int i=1;i<=n;i++) fa[i]=i;
		for(int i=1;i<=m;i++)
		{
			int fu=find(e[i].u),fv=find(e[i].v);
			if(fu==fv||!e[i].cu||(e[i].w>>t&1)) continue;
			fa[fu]=fv;
		}
		if(find(n)==find(1))
		{
			for(int i=1;i<=m;i++)
			if(e[i].w>>t&1) e[i].cu=0;
		}
		else
		ans+=1<<t;
	}
	cout<<ans;
}

---

## 作者：littlebug (赞：7)

需要运用一些我没有的东西（脑子）。

## Solution

可以注意到，最小的路径按位或和就相当于：**最小的 $x$ 满足 $1 \sim n$ 存在一条路径上面的权值或和 $\le x$**。

那么问题就转化成了求 $x$ 的最小值。

首先 $x = 2^{30} - 1$ 一定满足条件，这是显然的。然后贪心地，从大到小遍历每个 $x$ 的二进制位，依次判断当前位置是否可以置为 $0$ 就可以了。

因为是从大到小，所以不会出现小的位置置 $0$ 导致本来能置 $0$ 的大的位置无法置 $0$ ，于是贪心正确性显然。

至于判断一个 $x$ 是否满足条件，可以用类似 kruskal 的方式，开个 dsu，把每条满足限制的边都练上，然后判断 $1$ 和 $n$ 在不在同一个即合理就可以了。

时间复杂度 $O(m \log V \alpha(n))$。

## Code

```cpp
int n,m;
struct edge{int u,v,w;} e[N];

struct __dsu { ... // 省略了一些 dsu 板子

il void solve()
{
    read(n,m); rep(i,1,m) read(e[i].u,e[i].v,e[i].w);

    int x=(1ll<<30)-1;
    rpe(i,29,0)
    {
        x-=(1ll<<i);

        dsu.init(n);
        rep(j,1,m) (e[j].w|x)==x && (dsu.merge(e[j].u,e[j].v),1);

        if(dsu.find(1)!=dsu.find(n)) x+=(1ll<<i);
    }

    write(x);
}
```

---

华风夏韵，洛水天依！

---

## 作者：sSkYy (赞：3)

## 题意

给你一张无向图，无自环，可能有重边，有边权。

求从顶点 $1$ 到顶点 $N$ 的简单路径中，边权按位或的最小值。

边权在 `int` 范围内。

## 题解

考虑到或运算的性质，有 $1$ 得 $1$，我们贪心地按二进制从高位到低位计算答案，每次只关心该位上是否能置 $0$，且不影响高位的答案。

正确性证明：在高位最优的情况下才能考虑低位是否能更优，这是显然的。

代码框架就是将答案初始化为 $2^{31}-1$，即全是 $1$，然后从高位到低位枚举，每次跑一遍 BFS，如果能找到一条路径使得该位的或运算结果为 $0$ 且不影响更高位，那么就更新答案。

时间复杂度 $O(n+m)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m;
vector<pair<int,int>> e[N];
queue<int> q;
int vis[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) vis[i]=31;
	
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		e[u].emplace_back(v,w);
		e[v].emplace_back(u,w);
	}
	
	int ans=(1<<30)-1; 
    for(int bit=29;bit>=0;--bit){
        int tmp=ans&~(1<<bit);
        while(!q.empty()) q.pop();
        q.push(1);
        vis[1]=bit;
        bool found=false;

        while(!q.empty()&&!found){
            int u=q.front();
            q.pop();
            for(auto [v,w]:e[u]){
                if(vis[v]!=bit&&(w|tmp)==tmp){
                    if(v==n){
                        found=true;
                        break;
                    }
                    vis[v]=bit;
                    q.push(v);
                }
            }
        }
        if(found) ans=tmp;
    }
	cout<<ans;
	return 0;
}
```

---

## 作者：xiaoyin2011 (赞：2)

## AT_abc408_e [ABC408E] 最小或路径 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc408_e)

### 题目大意

$N$ 个点 $M$ 条边的无向带权连通图，给出按位或意义下的 $1$ 到 $N$ 的最短路。$w < 2^{30}$。

### 思路及实现

直接枚举每个点显然不行，此时考虑按位或对于答案的意义。

发现二进制下更高位的位值带来的权重总是让它比低位高，所以优先保障它成为 $0$ 也许更容易出现最优解。

因此从最高位（题目里限制的 $29$ 位）开始到 $0$ 位贪心。

接下来尝试令答案中这位等于 $0$。因为按位或的性质，一旦沾染了 $1$ 就没法洗干净了，所以需要遍历边时排除所有这一位是 $1$ 的边。然后在并查集中把所有能用的边都连起来，观察点 $1$ 和 $N$ 是否连通。

如果连通，说明这位等于 $0$ 下有可行解，并且它的或最短路也比这位 $1$ 要更小。所以为了避免污染这一位变成 $1$，避免后续判断，把这一位等于 $1$ 的边全部打上删除标记，再进入下一位。

最优解则靠一位一位贪心，直到选择足够少，才会做出答案上的让步。最后解一定是合法且最优的。

但是上述都是连通，如果不连通，只能向事实低头了。在答案里将这一位作为 $1$ 意味着这一位一定会被污染至少一次。同时，这一位 $1$ 的边也不会被删除。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, M, u[200005], v[200005], w[200005];
bool del[200005];
ll fa[200005];
int find(int x)
{
	if (fa[x] != x)
		fa[x] = find(fa[x]);
	return fa[x];
}
ll ans = 0;
int main()
{
    scanf("%lld%lld", &N, &M);
    for (int i = 1; i <= M; i++)
        scanf("%lld%lld%lld", &u[i], &v[i], &w[i]);
    for (int bit = 29; bit >= 0; bit--)
	{
        for (int i = 1; i <= N; i++) 
            fa[i] = i;
        for (int i = 1; i <= M; i++)
		{
            if (del[i]) continue;
            if (w[i] & (1 << bit)) continue;
            int a = find(u[i]), b = find(v[i]);
            if (a != b) fa[b] = a;
        }
		if (find(1) == find(N))
            for (int i = 1; i <= M; i++)
			{
                if (del[i]) continue;
                if (w[i] & (1 << bit)) del[i] = 1;
            }
		else
			ans |= (1 << bit);
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：P2441M (赞：2)

## 题意
给定一张 $n$ 个点、$m$ 条边的无向图，边有边权，求 $1$ 到 $n$ 的按位或最短路。$2\leq n\leq 2\times 10^5$，$n-1\leq m\leq 2\times 10^5$，$0\leq w_i<2^{30}$。

## 题解

好像上世纪做过这道典题。

直接 Dijkstra 是假的，因为按位或不满足三角形不等式的贪心性质。

考虑拆位。经典地，由于 $2^i>\sum_{j=0}^{i-1}2^j$，我们贪心地从高到低枚举答案的每一位，当前位如果能设为 $0$ 就必然设为 $0$。

当枚举到第 $i$ 位时，我们已经确定了答案的高于 $i$ 位的部分，且得到了一个集合 $E_{lim}$ 表示限定只能从中选边。初始时 $E_{lim}=E$。令边集 $E_i$ 表示所有 $w$ 的第 $i$ 位为 $0$ 的边构成的集合，那么要让答案的第 $i$ 位变成 $0$，我们选出的边就必须是 $E_i\cap E_{lim}$ 的子集。如果将所有 $E_i\cap E_{lim}$ 的边选上，$1$ 和 $n$ 依然不连通，说明当前位只能设为 $1$。否则当前位设为 $0$，然后我们令 $E_{lim}\leftarrow E_i\cap E_{lim}$。

用并查集维护上述过程即可。时间复杂度 $\mathcal{O}(m\log{n}\log{\max{w}})$ 或 $\mathcal{O}(m\alpha(n)\log{\max{w}})$。

## 代码
```cpp
#include <iostream>
#include <vector>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e5 + 5, M = 4e5 + 5, B = 35;

int n, m, ans;

struct Edge {
	int id, x, y;
};
int v[M];
vector<Edge> edges[B];

struct DSU {
	int fa[N];
	inline void init() { for (int i = 1; i <= n; ++i) fa[i] = i; }
	inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	inline void unite(int x, int y) { fa[find(x)] = find(y); }
} d;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; ++i) {
    	cin >> u >> v >> w;
    	for (int j = 29; j >= 0; --j)
    		if (!(w >> j & 1)) edges[j].push_back({i, u, v});
    }
    for (int i = 1; i <= m; ++i) v[i] = 1;
    for (int i = 29; i >= 0; --i) {
    	d.init();
    	for (Edge e : edges[i]) if (v[e.id]) d.unite(e.x, e.y);
    	if (d.find(1) != d.find(n)) ans |= 1 << i;
    	else {
    		for (Edge e : edges[i]) if (v[e.id]) ++v[e.id];
    		for (int j = 1; j <= m; ++j)
    			if (v[j] == 2) v[j] = 1;
    			else v[j] = 0;
    	}
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Xuan_qwq (赞：1)

同步发表于 [My blog](https://www.cnblogs.com/Xuan-qwq/p/18905640)。

>#### translation:
>最短路，路径权值为路径上所有边边权按位或的结果。

从高位到低位判断最终结果能否在该位以下即可。

具体的，利用并查集求最小生成树，每次取出最大边边权的最高位 $2^k$，去除所有边权 $\ge 2^{k+1}$ 的边，剩下的所有边去掉 $2^k$ 这一位，然后重复，直到没有剩下的边或者剩下的边权都为 $0$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct edge{
	int x,y,w;
	bool operator < (const edge & B) const {
		return w<B.w;
	}
}e[200005];
int n,m;
int fa[200005];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
} 
signed main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>e[i].x>>e[i].y>>e[i].w;
	}
	sort(e,e+m);
	int ans=0;
	for(int k=29;k>=0;k--){
		for(int i=1;i<=n;i++)fa[i]=i;
		int mx=0;
		for(int i=0;i<m;i++){
			int fx=find(e[i].x),fy=find(e[i].y);
			mx=e[i].w;
			if(fx==fy)continue;
			fa[fx]=fy;
			if(find(1)==find(n))break;
		}
		int S=log2(mx);
		if(m==0||mx==0)break;
		ans|=(1<<S);
		m=lower_bound(e,e+m,edge{0,0,1<<(S+1)})-e;
		for(int i=0;i<m;i++)if(e[i].w&(1<<S))e[i].w-=(1<<S);
		sort(e,e+m);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ALLIN2624 (赞：1)

## Meaning

在所有从顶点 $1$ 到顶点 $N$ 的简单路径中，找到路径上所有边权的按位或值的最小值。

## Solve

显然按位考虑。

因为要求最小值，所以从大到小枚举二进制位更新答案。运用贪心思想，能不选就不选，答案一定更优。

设当前枚举到第 $w(0\leq w\leq30)$ 位，当前记录的答案是 $ans$，初始值为 $2^{30}-1$。如果图中存在至少一条合法路径，使得路径上至少一条边的边权在第 $w$ 位上为 1 且已记录过为 1 的位上为 1，则说明第 $w$ 位可以不选，$ans\leftarrow ans-2^w$。

如何判断路径的存在性？简单的 bfs 可以实现。

详见代码实现。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define all(v) (v).begin(), (v).end()
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define up(v, l, r) for (i32 v = (l); v <= (r); v++)
#define dn(v, l, r) for (i32 v = (r); v >= (l); v--)
#define run(v, f) for_each(all(v), f)

namespace {
	using i32 = int32_t;
	using i64 = int64_t;
	using u32 = uint32_t;
	using u64 = uint64_t;
#if defined(LOCAL) || defined(linux)
	using i128 = __int128_t;
	using u128 = __uint128_t;
#else
	using i128 = int64_t;
	using u128 = uint64_t;
#endif
	template <typename Tp> using art = vector<Tp>;
	
	struct IO_t {
		istream &inner;
		ostream &outter;
		IO_t(istream &_inner = cin, ostream &_outter = cout): inner(_inner), outter(_outter)
			{ ios::sync_with_stdio(0); inner.tie(0), outter.tie(0); }
		void sp() { outter << " "; }
		void ln() { outter << "\n"; }
		template <typename Tp> void in(Tp &x) { inner >> x; }
		template <typename Tp> void out(Tp x) { outter << x; }
		template <typename Tp> void sp(Tp x) { out(x), out(' '); }
		template <typename Tp> void ln(Tp x) { out(x), out('\n'); }
		template <typename Tp> void in(art<Tp> &a) { for (auto &u : a) in(u); }
		template <typename Tp> void out(art<Tp> a) { for (auto &u : a) out(u); }
		template <typename Tp> void sp(art<Tp> a) { for (auto &u : a) sp(u); }
		template <typename Tp> void ln(art<Tp> a) { for (auto &u : a) ln(u); }
		template <typename Tp, typename... Args> void in(Tp &x, Args& ...args) { in(x), in(args...); }
		template <typename Tp, typename... Args> void out(Tp x, Args... args) { out(x), out(args...); }
		template <typename Tp, typename... Args> void sp(Tp x, Args... args) { sp(x), sp(args...); }
		template <typename Tp, typename... Args> void ln(Tp x, Args... args) { ln(x), ln(args...); }
	} IO, dbg(cin, cerr);
	
	const i32 N = 2e5;
	
	using pii = pair<i32, i32>;
	
	art<pii> G[N + 5];
	bitset<N + 5> vis;
	i32 n, m, ans = (1 << 30) - 1;
	
	bool check(i32 msk) {
		vis.reset();
		queue<pair<i32, i32>> q;
		q.push({1, 0}), vis.set(1);
		while (!q.empty()) {
			auto it = q.front();
			q.pop();
			i32 u = it.first, c = it.second;
			if (u == n) return true;
			for (auto it : G[u]) {
				i32 v = it.first, w = it.second;
				if (!vis[v] && (c | w | msk) == msk) {
					vis.set(v), q.push({v, c | w});
				}
			}
		}
		return false;
	}
	
	void solve() {
		IO.in(n, m);
		up(i, 1, m) {
			i32 u, v, w;
			IO.in(u, v, w);
			G[u].emplace_back(v, w);
			G[v].emplace_back(u, w);
		}
		dn(i, 0, 30)
			if (check(ans & ~(1 << i))) ans &= ~(1 << i);
		IO.ln(ans);
	}
}

signed main() {
	signed T = 1;
	// cin >> T;
	while (T--) solve();
	return 0;
}
```

夹带了一点私货，望见谅。

## Ponder

如果只判断第 $w$ 位是不是 1 可行吗？

根据**继承**的思想，只有把先前决定下的状态也算上，才能保证图中一定存在该路径。

这部分写给一个经常卡在类似题的 OIer。

---

## 作者：niuqichongtian (赞：1)

# [E - Minimum OR Path](/contests/abc408/tasks/abc408_e) 题解 

从顶点 $1$ 到顶点 $N$ ，是否能只通过边权 $w$ 满足 $w\ \mathrm{OR}\ x=x$ 的边到达终点？若可以，设 $X$ 是 $x$ 的集合，那么 $X$ 集合的最小值就是问题的答案。


鉴于 $x\ \mathrm{OR}\ 2^k \in X$ 对任意 $x\in X$ 成立，我们知道下面的贪心方法是正确答案。

- $x=2^{30}-1$ 时满足 $x\in X$ 。
- $k=29,28,\ldots,0$ 的顺序如下。
    - 判断 $x$ 的 $k$ 位是否可以是 $0$ 。也就是说，判断 $x'=x-2^k$ 是否包含在 $X$ 中，如果是，则将 $x$ 替换为 $x'$ 。否则不做任何操作。

每个决策问题都可以用 DSU（即并查集）等方法来解决。

上述方法可以很好地解决这个问题。计算复杂度为 $O((N+M)\alpha(N)\log \max_i w_i)$ 或 $O((N+M)\log \max_i w_i)$ 。

[实现示例 (Python3)](https://atcoder.jp/contests/abc408/submissions/66240244)

```py
from atcoder import dsu

n, m = map(int, input().split())
a = [()] * m
for i in range(m):
    u, v, w = map(int, input().split())
    a[i] = (u - 1, v - 1, w)
x = (1 << 30) - 1
for k in range(29, -1, -1):
    x ^= 1 << k
    d = dsu.DSU(n)
    for u, v, w in a:
        if (x | w) == x:
            d.merge(u, v)
    if not d.same(0, n - 1):
        x |= 1 << k
print(x)

```


---
> 转载自 [sounansya](/users/sounansya)。[原页面](https://atcoder.jp/contests/abc408/editorial/13159)。

---

## 作者：時空 (赞：0)

[In Luogu](https://www.luogu.com.cn/problem/AT_abc408_e)

被 D 卡了快 1h，快结束才看到 E。但是这玩意有原啊，赛时水掉了。

经典的套路题，看到这种按位或的贡献，容易想到按位贪心。

我们从高位到低位考虑，显然我们尽量使高位为 $0$，这个策略是不劣的。

更具体地，对于答案二进制下的第 $x$ 位，如果我们可以选取某些边，使这些边按位或后第 $x$ 位为 $0$，并且通过这些边能从 $1$ 号点到 $n$ 号点，那么答案的第 $x$ 位就可以为 $0$。我们便选取这些边，将其它没选的边标记不能选，继续向低位考虑即可。

判断联通可以用并查集。

这么说可能不是很清楚，具体见代码，个人认为写的很清楚了。

[Code](https://atcoder.jp/contests/abc408/submissions/66358064)

---

## 作者：xy_mc (赞：0)

小蒟蒻读完题后还以为是 dijkstra 的变形，信心满满的写完之后发现样例二不对，终究是场切不了吗……

### 加芝士（$5$ 元）：

- 位运算；
- 贪心；
- 并查集。

读完题后我们发现，由于题目让求最小值，那我们不妨枚举答案二进制的每一位，尽可能的使这一位为 $0$，否则为 $1$。

那么怎样才会使这一位为 $0$ 呢？回想一下按位或的性质，发现，只要途径路径长度的二进制在这一位为 $1$，则答案的这一位就必定为 $1$，如果所有长度的这一位都为 $0$，则答案这一位为 $0$。那么我们就可以将这一位为 $0$ 的所有路径合并，如果 $1$ 号节点和 $n$ 号节点联通，则这一位可以为零，并把其他路径删掉，否则将答案的这一位标为 $1$。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ks8e9mf0.png)(画图技术有待提高)。

很容易想到开一个数组去标记这个路径是否被删除，但是这样太麻烦也太慢了，这里有一种巧妙的方法：用两个 $30$ 位的二进制数来标记，这里表示为 $\text{tmp}$ 和 $\text{ppp}$，删的边如上图。对于每一位，现将 $\text{tmp}$ 赋值给 $\text{ppp}$，并将 $\text{ppp}$ 的这一位设为 $1$，判断的时候只要判断 `!(G[j].w&ppp)` 就可以，可以判断出这一位是否为 $0$，最后如果图联通，将 $\text{ppp}$ 赋值给 $\text{tmp}$。以此类推，如果 $\text{ppp}$ 的多位为 $1$，则可以判出某一路径的多位为 $0$。


### code：

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int,int>
#define pll pair<ll,ll>
#define yes "Yes"
#define no "No"
#define debug(x) cout<<#x<<" = "<<x<<"\n"
#define rep(i,x,y) for(int i=x;i<=(y);++i)
#define per(i,x,y) for(int i=x;i>=(y);--i)

typedef long long ll;
typedef unsigned long long ull;

namespace fast{
	inline int sf(){
		int x=0,f=1;char c=getchar();
		while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
		while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
		return x*f;
	}
	inline void out(int n){
		if(n<0){putchar('-');n=-n;}
		if(n>9)out(n/10);
		putchar(n%10^48);
	}
}

using namespace std;
using namespace fast;

const int INF=0x3f3f3f3f;
const ll LNF=0x3f3f3f3f3f3f3f3f;
const int N=2e5+10;

int n,m;
struct node{
	int u,v,w;
}G[N];
int f[N];

int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}

void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy) f[fy]=fx;
}

int getans(int n){
	int ans=0,tmp=0;
	per(i,29,0){
		int ppp=(tmp|(1<<i)); //设为 1；
		rep(j,0,n-1) f[j]=j; //初始化；
		rep(j,0,m-1) if(!(G[j].w&ppp)) merge(G[j].u,G[j].v); //判 0；
		if(find(0)==find(n-1)) tmp=ppp;
		else ans|=(1<<i);
	}
	return ans;
}
void solve(){
	n=sf(),m=sf();
	rep(i,0,m-1) G[i].u=sf()-1,G[i].v=sf()-1,G[i].w=sf(); //记得减 1；
	cout<<getans(n);
}

int main(){
	int t=1;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Toorean (赞：0)

给出无向连通图 $G$，求 $1$ 到 $N$ 点的最小或路径。

如若用 Dijkstra 的套路来做，我们发现这种贪心是错误的。因此我们考虑生成树。

我们从大到小枚举答案的二进制位，判断当前二进制位是否在答案中是必要的。具体来说，假设当前判断的二进制位为 $p$，我们令 $x=\sum\limits_{i=0}^{p-1} 2^i$，如若 $p$ 位是不必要的，那么在进行生成树时，对于 $1$ 到 $N$ 的路径上所有的边，或运算和最高位**必然**小于 $p$。换句话说，假设 $w$ 为路径上一边权，那么对于所有的 $w$，都有 $w\operatorname{OR}x=w$。反之，如果不能使路径上的点都满足这个条件，那么 $p$ 位是必要的。

综上，可以在 $\mathcal O(n\log n)$ 的时间内解决（假设 $n$ 与 $m$ 同阶，且并查集复杂度 $\mathcal O(\alpha(n))$ 可以认为是常数）。

---

## 作者：Halberd_Cease (赞：0)

省流：小丑石山暴力做法 2500ms 卡过。

注意到直接写最短路会 WA 样例 2，因为不能以当前点的最短距离去扩展下一个点的最短距离，若无论如何从 $1$ 到 $n$ 的路径上都要经过一个二进制位更高的权值，那么贪心每个点取最小权值是假的，比如考虑如下图：

```
1 2 1
1 2 2
2 3 2
```

若直接最短路，那么点 $2$ 的距离是 $1$，点 $3$ 的距离是 $3$。

上面的分析启示我们在二进制位从高往低考虑。讨论当前二进制位，若无论如何到 $n$ 点都必须经过这一位为 $1$ 的边，那么答案的这一位一定为 $1$。否则，不论如何都不应该走这一位为 $1$ 的边，于是将所有的这一位为 $1$ 的边删掉，然后考虑下一位。

答案在枚举二进制位的过程中累加。总时间复杂度 $O(n\log V+m\log V)$，寻找当前位是否有只经过 $0$ 的路径可以使用 dfs 直接搜，但是小丑笔者赛时选择了 01bfs 喜提最裂解。

[submission](https://atcoder.jp/contests/abc408/submissions/66333147)

---

## 作者：_zuoqingyuan (赞：0)

简单题。下文用 OR 运算代表二进制或运算，第 $k$ 位表示位权为 $2^k$ 那一位。

# 思路分析

因为 OR 运算的性质，对于一条异或路径，只要一条边的边权第 $k$ 位为 $1$，那么最后 OR 和第 $k$ 位也为 $1$。反过来说，要使得 OR 和第 $k$ 位 $0$，则只能经过边权第 $k$ 位为 $0$ 的边。

我们比较两个二进制数的大小，是从高位往地位看。对于本题，不妨从高位往低位贪心，让高位尽可能为 $0$。当前最优就是全局最优。

假设每条边都有一个标记，现在已经确定了 $k+1\sim 30$ 位的最小值，且得到这个最小值只能经过有标记的边。要使第 $k$ 位尽可能小，我们检查只经过有标记的且边权第 $k$ 位为 $0$ 的边，能否从 $1$ 走到 $n$，这是个连通性问题，可以用并查集快速做。

若能从 $1$ 到 $n$，则说明最优答案第 $k$ 位为 $0$，将所有有标记但边权第 $k$ 位为 $1$ 的边标记删除。若不能，则最优答案第 $k$ 位为 $1$。从 $30$ 到 $0$ 逐位枚举即可。

每次做一次并查集，时间复杂度 $O(n+m)$，总时间复杂度 $O((n+m)\log V)$。


```cpp

#include <iostream>
#include <cstdio>
using namespace std;
const int N=2e5+10;
int n,m,u[N],v[N],w[N],mk[N],f[N],ans;
void reset(){
	for(int i=1;i<=n;i++)f[i]=i;
}
int found(int x){
	return f[x]==x?x:f[x]=found(f[x]);
}
bool check(int k){
	reset();
	for(int i=1;i<=m;i++){
		if(mk[i])continue;
		if(!((w[i]>>k)&1)){
			int x=found(u[i]);
			int y=found(v[i]);
			if(x!=y)f[x]=y;
		}
	}
	return (found(1)==found(n));
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d %d %d",u+i,v+i,w+i);
	for(int i=30;i--;i>=1){
		if(check(i)){
			for(int j=1;j<=m;j++){
				if(mk[j])continue;
				if((w[j]>>i)&1)mk[j]=1;
			}
		}else ans|=(1<<i);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

