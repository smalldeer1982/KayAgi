# [SDCPC 2023] Not Another Path Query Problem

## 题目描述

**【题目背景】**

> 都什么年代了还在做传统路径查询问题？


在阅读《Distributed Exact Shortest Paths in Sublinear Time》这篇论文后，您学会了如何在 $\mathcal{O}(D^{1/3} \cdot (n \log n)^{2/3})$ 的复杂度内解决分布式单源最短路问题。为了测试您是否真的学有所成，小青鱼为您准备了如下问题。

小青鱼有一张包含 $n$ 个节点与 $m$ 条无向边的图，节点编号从 $1$ 到 $n$。第 $i$ 条边连接节点 $u_i$ 和 $v_i$，边权为 $w_i$。

对于任意一条连接节点 $u$ 和 $v$ 的路径，定义路径的价值为路径上所有边的边权进行按位与（bitwise AND）计算的结果。

小青鱼很喜欢高价值的路径，因此他设定了一个固定的阈值 $V$。称小青鱼喜爱一条路径，当且仅当这条路径的价值至少为 $V$。

接下来，小青鱼将会提出 $q$ 次询问，第 $i$ 次询问可以用一对整数 $(u_i, v_i)$ 表示。对于每次询问，您需要判断节点 $u_i$ 到 $v_i$ 是否存在一条小青鱼喜爱的路径。

## 样例 #1

### 输入

```
9 8 4 5
1 2 8
1 3 7
2 4 1
3 4 14
2 5 9
4 5 7
5 6 6
3 7 15
1 6
2 7
7 6
1 8
```

### 输出

```
Yes
No
Yes
No
```

## 样例 #2

### 输入

```
3 4 1 4
1 2 3
1 2 5
2 3 2
2 3 6
1 3
```

### 输出

```
Yes
```

# 题解

## 作者：FFFFFAN (赞：14)

RT，本题还真不是一道路径查询题，这里提供一个并查集做法。

## 题意

给定一个无向图和一个常数 $V$，有多次询问，每次询问两个点之间是否存在一条路径，使得路径上所有边的边权进行按位与计算的结果不小于 $V$。

## 思路

首先来思考一下按位与运算的性质。发现，**两个数相与的结果一定不大于这两个数**，因为按位与运算只有可能把二进制位上的 $1$ 变成 $0$，而 $0$ 不可能会变成 $1$，所以一直做按位与运算只会越来越小。

这引导我们从二进制上分析，假设从高位往低位分析，那么两个数按位与后不小于另一个数，必须存在 $i$，使得高于 $i$ 的所有位中，要么三个数同为 $1$，要么另一个数这一位为 $0$ 而这两个数的这一位可为 $1$ 也可为 $0$，也是**按位与的结果的一段前缀要不小于另一个数的相同位置的一段前缀**。

推广到更多数的情况，那么一些边的边权按位与的结果要不小于 $V$，也就是这些边的边权都存在一个前缀满足上面的条件，那么这些边权按位与的结果就一定会满足上面的条件。

$V,w_i\lt 2^{60}$，即前缀只有 $60$ 个，我们考虑按每一条边的边权前缀将这些边分类，满足第 $i$ 个边集里面的所有边的边权的按位与的前 $i$ 位这个前缀大于 $V$ 的前 $i$ 位的前缀。

这样，如果 $u$ 到 $v$ 存在一条路径满足路径上的所有边都在同一个集合里面，那么这条路径上所有边的边权的按位与就会不小于 $V$，相当于**判断 $u$ 和 $v$ 是否在某个全部由同一边集的边形成的子图中是联通的**，而这用并查集可以很好的维护。

当然，某一条边的边权如果有多个前缀满足条件，那这条边会同时存在于多个边集中。并且我们要特殊处理一下边权等于 $V$ 的所有边，由这些边形成的子图中的任意两点也是满足题意的。

建边的时间复杂度 $O(m)$，一次查询的时间复杂度就是并查集的时间复杂度。

## 代码

```cpp
#include<cstdio>
using namespace std;

int n, m, q, fa[100005][65], b[65];
long long V;

int find(int x, int i) {
	return x==fa[x][i] ? x : fa[x][i]=find(fa[x][i], i);
}

int main() {
	scanf("%d%d%d%lld", &n, &m, &q, &V);
	for(int i=1; i<=n; ++i)
		for(int j=0; j<=61; ++j)	fa[i][j] = i;
	for(int j=60; ~j; --j)
		if(V&(1ll<<j))	b[j] = 1;
	for(int i=1; i<=m; ++i) {
		int u, v;
		long long w;
		scanf("%d%d%lld", &u, &v, &w);
		for(int j=60; ~j; --j) {
			bool f = (w&(1ll<<j));
			if((!b[j]) && f)	fa[find(u, j)][j] = find(v, j);
			else if(b[j] && (!f))	break;
		}
		if((w&V) >= V)	fa[find(u, 61)][61]=find(v, 61);
	}
	for(int i=1; i<=q; ++i) {
		int u, v, flag=0;
		scanf("%d%d", &u, &v);
		for(int j=61; ~j; --j)
			if(find(u, j) == find(v, j)) {
				flag = 1;
				break;
			}
		puts(flag ? "Yes" : "No");
	}
	return 0;
}
```

## 附录

### 原题链接

[[SDCPC2023] Not Another Path Query Problem - 洛谷](https://www.luogu.com.cn/problem/P9565)

### 参考文献

扶苏姐姐的课

---

## 作者：OldDriverTree (赞：5)

一道考察位运算性质的好题。

# Solution

考虑一条路径按位与的结果 $\ge V$ 需要满足的条件。

必然会在二进制下存在一个 $pos$ 满足 $pos$ 前面的位置 $i$ 都满足如果 $V$ 位置 $i$ 为 $1$，那么路径上的每个数位置 $i$ 都要为 $1$，且 $V$ 位置 $pos$ 上的数为 $0$，路径上的每个数 $pos$ 位置都要为 $1$。

还有一种情况：$V$ 为路径上每个数的子集。

由于 $pos$ 只有 $60$ 种，考虑开 $61$ 个并查集维护。

询问时枚举 $pos$ 的位置，判断这个并查集中的两个点是否连通即可。

时间复杂度 $O((m+q)\log V\log n)$。

# Code

```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+1;
int n,m,q; ll V;

template<typename T>
void read(T &x) {
	x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
}
struct DSU {
	int fa[N];
	void init() { for (int i=1;i<=n;i++) fa[i]=i; }
	int find(int x) { return fa[x]^x?fa[x]=find(fa[x]):x; }
	void merge(int x,int y) { fa[find(x)]=find(y); }
	bool query(int x,int y) { return find(x)==find(y); }
}T[61];

bool judge(int x,int y)
{
	for (int i=60;~i;i--)
		if (T[i].query(x,y) )
			return true;
	
	return false;
}
int main()
{
	read(n),read(m),read(q),read(V);
	for (int i=0;i<=60;i++) T[i].init();
	while (m--) {
		int x,y; ll z=0;
		read(x),read(y),read(z);
		for (int i=59;~i;i--) {
			if (!(V>>i&1)&&(z>>i&1) ) T[i].merge(x,y);
			else if ( (V>>i&1)&&!(z>>i&1) ) break;
		}
		if ( (z&V)==V) T[60].merge(x,y);
	}
	while (q--) {
		int x,y; read(x),read(y);
		puts(judge(x,y)?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：naroto2022 (赞：1)

# P9565 题解

[博客园里看效果更佳](https://www.cnblogs.com/naroto2022/p/18695295)

### 题面

[原题传送门](https://www.luogu.com.cn/problem/P9565)

### 思路

我们先设一个路径的与和为 $val$。

首先我们要知道按位与的操作从二进制下的每一位来看，最终的结果为 $1$ 的要求为路径上边的权值在这一位都为 $1$，然后既然在得到这个结果的过程按二进制拆开，那么我们比大小也按二进制下来比较。

那么对于两个数 $a,b$，若 $a>b$，则有两种情况：

1. $a$ 的最高位比 $b$ 高，如 $a=8,b=4$，`100` 和 `10`。
2. $a$ 的前几位和 $b$ 一样，在第一个不一样的位置 $a$ 为 $1$，$b$ 为 $0$，如 $a=5,b=4$，`101` 和 `100`。

于是接下来就可以考虑这道题的做法了。

我们就是考虑从大到小枚举路径的与和，并设置一个数 $num$，设当前枚举的是 $2^k$，如果 $V$ 的第 $k$ 位为 $1$，则令 $num\gets num+2^k$，否则就将所有满足 `w[i]&num=num` 的边取出来，用一个并查集维护一下，然后一个个询问遍历过去，如果两个点联通，那么这个询问就输出 `Yes`，最后在判断 `w[i]&V=V` 的边是否满足每一个询问。

于是就有人问了，为什么 $V$ 的第 $k$ 位为 $1$，就令 $num\gets num+2^k$，其实很简单，因为如果到当前部分询问还是 `No`，那么就说明目前得保证路径的 $val$ 大于等于 $V$，那么就得保证 $val$ 和 $V$ 的前几位相等，于是这个做法的正确性就是对的啦。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
const int MN=5e5+5;
ll n,m,k,v,fa[MN],sz[MN],ans[MN],num;
struct edge{ll u,v,w;}e[MN];
struct question{ll u,v;}q[MN];
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
ll find(ll x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void merge(ll x, ll y){
    x=find(x);y=find(y);
    if(x==y) return;
    if(sz[x]>sz[y]) swap(x,y);
    fa[x]=y;sz[y]+=sz[x];
}
int main(){
    n=read();m=read();k=read();v=read();
    for(int i=1; i<=m; i++) e[i].u=read(),e[i].v=read(),e[i].w=read();
    for(int i=1; i<=k; i++) q[i].u=read(),q[i].v=read();
    for(int i=1; i<=n; i++) fa[i]=i,sz[i]=1;
    for(int i=1; i<=m; i++) if((e[i].w&v)==v) merge(e[i].u,e[i].v);
    for(int i=1; i<=k; i++) if(find(q[i].u)==find(q[i].v)) ans[i]=1;
    for(int i=63; ~i; i--){
        num|=(1ll<<i);
        if(!((v>>i)&1)){
            for(int i=1; i<=n; i++) fa[i]=i,sz[i]=1;
            for(int i=1; i<=m; i++) if((e[i].w&num)==num) merge(e[i].u,e[i].v);
            for(int i=1; i<=k; i++) if(find(q[i].u)==find(q[i].v)) ans[i]=1;
            num^=(1ll<<i);
        }
    }
    for(int i=1; i<=k; i++) if(ans[i]) printf("Yes\n");else printf("No\n");
    return 0;
}
```

---

## 作者：Z3k7223 (赞：1)

## Problem

给定一张带权无向图和常数 $V$，每次询问是否存在一条 $u$ 到 $v$ 的路径，路径上的边权按位与之和不小于 $V$。

## Solution

注意到 $V$ 是给定的，这时候可以思考在哪些条件下边权按位与之和会大于等于 $V$，并预处理出来。

设我们构造出来的边权是 $x$，考虑在二进制下比较两数，有 $V\le x$ 当且仅当存在一位数，$V$ 与 $x$ 在前面都相等，且 $x$ 在该位为 $1$ 而 $V$ 在该位为 $0$。又因为 $x$ 后面的其它位我们都不关心，根据一个贪心的思想，不妨设 $x$ 后面的位全为 $0$，容易发现这样的 $x$ 的个数取决于 $V$ 二进制下 $0$ 的个数，是 $O(\log V)$ 的，因此可以直接计算出所有 $x$，只要有一条路径满足按位或的结果包含任意一个 $x$ 就是有解。

到这里做法就很显然了，对于每个 $x$ 维护一个并查集，维护包含该 $x$ 的边的连通性，查询也同理，这样就实现了一个 $O((m+q) \log V \log n)$ 的做法。

## Code

这里的 $t$ 和 $k$ 即为上文的 $x$ 和 $V$，注意 $V$ 本身也是一个有效的 $x$。

常数可能写大了点，加个同步流才过。

记得开 `long long`。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5 + 10;
int n, m, q;
ll k;
int fa[65][N];
ll t[65], tot;

int find(int i, int x) {
	if (fa[i][x] == x) {
		return x;
	}
	return fa[i][x] = find(i, fa[i][x]);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> q >> k;
	for (ll i = 0; i <= 62; i++) {
		for (int j = 1; j <= n; j++) {
			fa[i][j] = j;
		}
		if (i <= 60 && !((1ll << i)&k)) {
			t[++tot] = ((k >> i) | 1) << i;
		}
	}
	t[0] = k;
	for (int i = 1; i <= m; i++) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		for (ll j = 0; j <= tot; j++) {
			if ((w & t[j]) == t[j] && find(j, u) != find(j, v)) {
				fa[j][find(j, u)] = find(j, v);
			}
		}
	}
	while (q--) {
		int u, v;
		cin >> u >> v;
		int flag = 0;
		for (int i = 0; i <= tot; i++) {
			if (find(i, u) == find(i, v)) {
				flag = 1;
				break;
			}
		}
		cout << (flag ? "Yes\n" : "No\n");
	}
	return 0;
}
```

---

## 作者：Fire_Raku (赞：1)

[P9565 [SDCPC2023] Not Another Path Query Problem](https://www.luogu.com.cn/problem/P9565)

位运算+并查集

从价值至少为 $V$ 入手，枚举一段二进制上长为 $i$ 的**前缀**，第 $i+1$ 位取 $1$，并且比 $V$ 要大，这样 $i+1$ 之后的位就可以任意取了（不妨现在都先为 $0$），设这样构成的二进制串为 $s$。

考虑按位与的性质，随着路径增加，价值不增。并且如果想要二进制上其中一位为 $1$，那么路径上所有边的二进制上这一位都得是 $1$。回到上面枚举的 $s$，不妨固定我们需要 $s$ 上的所有 $1$，那么满足条件的边就是二进制上至少有这些 $1$ 的边。这些边集与所有点构成一张新的图，如果 $u$ 和 $v$ 在这张图上连通，那么就可以找到一条满足条件的路径，使得价值 $\ge s\ge v$。

判断连通性，用并查集。最多有 $60$ 个边集，只需要其中一个连通即可。记得开 `longlong`！

复杂度 $O(m\log n)$。

```cpp
#include <bits/stdc++.h>
#define pii std::pair<int, int>
#define mk std::make_pair
#define fi first
#define se second
#define pb push_back

using i64 = long long;
using ull = unsigned long long;
const i64 iinf = 0x3f3f3f3f, linf = 0x3f3f3f3f3f3f3f3f;
const int N = 5e5 + 10;
i64 n, m, q, V;
struct node {
	i64 u, v, w;
} e[N];
std::vector<int> v[61];
struct DSU {
	int fa[N];
	void init(int n) {for(int i = 1; i <= n; i++) fa[i] = i;}
	int find(int x) {
		return x != fa[x] ? fa[x] = find(fa[x]) : fa[x];
	}
	void merge(int x, int y) {
		if(x == y) return;
		fa[x] = y;
 	}
} dsu[61];
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
	std::cin >> n >> m >> q >> V;

	for(int i = 1; i <= m; i++) {
		std::cin >> e[i].u >> e[i].v >> e[i].w;
	}

	for(i64 i = 60; i >= 0; i--) {
		dsu[i].init(n);
		i64 s = 0;
		if(i && ((V >> (i - 1)) & 1LL)) continue;

		if(i) s |= (1LL << (i - 1));
		for(i64 j = 59; j >= i; j--) {
			s |= ((1LL << j) & V);
		}
		for(int j = 1; j <= m; j++) {
			i64 w = e[j].w;
			if((s & w) == s) v[i].pb(j);
		}
		
		for(auto id : v[i]) {
			int x = dsu[i].find(e[id].u), y = dsu[i].find(e[id].v);
			dsu[i].merge(x, y);
		}
	}	

	while(q--) {
		int u, v;
		std::cin >> u >> v;

		bool flg = 0;
		for(int i = 60; i >= 0; i--) {
			if(dsu[i].find(u) == dsu[i].find(v)) {
				flg = 1;
				break;
			}
		}

		std::cout << (flg ? "Yes\n" : "No\n");
	}
	return 0;
}
```

---

## 作者：SDLTF_凌亭风 (赞：1)

SDCPC2023 是 SD 在集训期间和机房同学一起打的第一场 XCPC 复现赛。当时这个题没做出来，现在某谷又把它拿出来讲，那就让我来试试刀吧！（你小子？）

首先研究一下与操作。几个数做与运算，结果肯定是越来越小。

一个显然的性质是，要尽可能避免这个减小的程度，路径上的点应该具有尽可能长的公共前缀。

所以，这个题只需要去枚举最长公共前缀的长度就好啦！

另外，请你一定要注意变量的类型，**切不可全用全开双龙**。

部分代码实现如下：

```cpp
void bfs(int S, ll t) {
	queue<int> q;
	q.push(S);
	bel[S] = S;
	while(!q.empty()) {
		auto u = q.front(); q.pop();
		for(int i = 0, fn; i < e[u].size(); ++ i) {
			fn = e[u][i]; ll val = v[u][i];
			if(bel[fn] || (val & t) != t) continue;
			q.push(fn),	marker[fn] = S;
		}
	}
}
inline void calc(ll  t) {
	memset(bel, 0, sizeof(int) * (n + 3));
	for(int i = 1; i <= n; ++ i) if(!bel[i]) bfs(i, t);
	for(int i = 1; i <= q; ++ i) ans[i] = ans[i] || marker[ask[i][0]] == cnt[marker[i][1]];
}
```

---

## 作者：fengziyi (赞：1)

显然，这不是一道路径查询问题。

给定一 $n$ 点 $m$ 边带权无向图和定值 $V$。  
定义一条路径的权值为路径上所有边按位与的结果。  
$q$ 次查询，每次询问一对 $u, v$ 之间是否存在一条路径，其权值 $\geq V$。

位运算，考虑按位枚举。

二进制下大小判定：$a > b$ 当且仅当 $a$ 存在一个前缀大于 $b$ 的等长前缀。

考虑枚举满足约束的路径权值的前缀。

```cpp
for (i64 pre = V; pre < (1ll << 60); pre += lowbit(pre))
	checker(pre);
```
如果一条路径上所有边的权值的前缀都为如上代码中的 $pre$，那么这条路径上所有边按位与的结果，即这条路径的权值，前缀为 $pre$。  

根据以上大小判定定理，这样的路径满足约束。

所以可以通过一次 BFS 将这样的路径上的点全部放入连通块并染色。

把所有询问离线下来，每次查询两个点是否同属一个联通块即可。

```cpp
inline void bfs(int s, i64 pre)
{
	queue<int> q;
	q.push(s); col[s] = s;
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		for (int i = h[u]; i; i = e[i].nxt)
		{
			int v = e[i].v; i64 w = e[i].w;
			if (!col[v] && (pre & w) == pre)
				q.push(v), col[v] = s;
		}
	}
}
inline void checker(i64 pre)
{
	fill(col + 1, col + n + 5, 0);
	for (int i = 1; i <= n; ++i)
		if (!col[i]) bfs(i, pre);
	for (int i = 1; i <= q; ++i)
		res[i] = res[i] || (col[qry[i].u] == col[qry[i].v]);
}
```

仿佛 BFS 染色在 Codeforces Gym 上会 TLE on Test 113，不过在洛谷能过。

复杂度 $O(m\log V + q)$ 是正确的，写个并查集维护可能常数会小一点。

---

## 作者：_liuyi_ (赞：1)

# 思路
这是一道非常好的二进制拆位的题目。看到题目涉及按位与的和大于 $v$，我们考虑对 $v$ 进行拆位，对于 $v$ 的第 $i$ 位，如果为 $0$，$cnt$ 第 $i$ 位就为 $1$ ，前 $i-1$ 位与 $v$ 保持一致，剩下全为 $0$，容易证明 $v\le cnt$。然后我们开始枚举，只保留有用的边，什么样的边是有用的呢，只有当 $cnt \& s \ge s$，$s$ 表示第 $i$ 条边的边权，实际上在二进制中就是 $cnt$ 为 $1$ 的那位 $s$ 那位也为 $1$，这样的边明显只会让按位与更大，那么我们把这条边加入后，然后去枚举每个询问中的两个点在新的图中是否连通，可以用并查集维护。最后别忘记枚举 $cnt=v$ 的情况。时间复杂度，因为 $m,q$ 同阶，并查集复杂度可以看成常数，所以最终复杂度为 $O((n+m)\log v)$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define mem(a, x) memset(a, x, sizeof(a)) 
#define pb push_back
#define SZ(x) ((int)(x).size())
#define debug(x) cout<<#x<<":"<<x<<endl;
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
typedef long long ll;
typedef pair<int,int> PII;
typedef unsigned long long ull;
typedef double db;
typedef vector<int> VI;
const int N=1e5+10,M=5e5+10;
const int mod=1e9+7;
template<class T> void yesno(T b){if(b)puts("yes");else puts("no");}
template<class T> void YesNo(T b){if(b)puts("Yes");else puts("No");}
template<class T> void YESNO(T b){if(b)puts("YES");else puts("NO");}
//const int mod=998244353;
int fa[N],n,m,q,pos[M][2],can[M];
ll v;
struct node{
	int u,v;
	ll w;
}e[M];
inline int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
inline void mg(int x,int y){
	x=find(x);y=find(y);
	if(x!=y) fa[x]=y;
	return;
}
int main(){
	scanf("%d%d%d%lld",&n,&m,&q,&v);
	rep(i,1,n) fa[i]=i;
	rep(i,1,m) scanf("%d%d%lld",&e[i].u,&e[i].v,&e[i].w);
	rep(i,1,q) scanf("%d%d",&pos[i][0],&pos[i][1]);
	rep(i,0,59){
		if(!((1ll<<i)&v)){
			ll cnt=(((v>>i)+1)<<i);
			rep(i,1,n) fa[i]=i;
			rep(i,1,m) if((e[i].w&cnt)==cnt) mg(e[i].u,e[i].v);
			rep(i,1,q) if(find(pos[i][0])==find(pos[i][1])) can[i]=1;
		}
	}
	rep(i,1,n) fa[i]=i;
	rep(i,1,m) if((e[i].w&v)==v) mg(e[i].u,e[i].v);
	rep(i,1,q) if(find(pos[i][0])==find(pos[i][1])) can[i]=1;
	rep(i,1,q) YesNo(can[i]);
	return 0;
}
```


---

## 作者：MrPython (赞：0)

还记得如何比较两个数的大小吗？在两个数数位长度都相同的情况下，从高位开始依次比较。题目中数据的值域为 $[0,2^{60})$，我们比较最多约 $60$ 次即可得知答案。

我们依次考虑 $V$ 二进制前缀的若干位。

开 $60$ 个并查集。对于长度为 $i$ 后缀，我们将其最后一位强制赋上 $1$，记这个值为 $s$。  
然后，倘若当前边长度为 $i$ 的后缀中，$s$ 所有为 $1$ 的位 $i$ 都为 $1$，就把这条边加进并查集 $i$。这样，可以保证并查集 $i$ 的**所有边之与运算之和，其长度为 $i$ 的前缀大于等于 $s$**。
> 证明：二进制意义下，$a<b$ 的一个必要条件是存在某一位 $i$，$a$ 的第 $i$ 位为 $0$，$b$ 的第 $i$ 位为 $1$。而在我们的操作中，保证了 $s$ 为 $1$ 的所有位，边权的当前位也必定为 $1$。该必要条件无法被满足。

查询时，从高位到低位扫一遍 $60$ 个并查集。若能遍历到这一位，说明我们已经考虑过前面的位了，只关心这一位的内容即可。每一位根据 $V$ 的二进制位分类讨论：
- $V$ 的当前位为 $0$：我们加入并查集的时候最后一位被修改为了 $1$。倘若并查集告诉我们这两个点联通，则这两点之间存在一条略大于 $V$ 的路径，直接打飞，否则继续枚举；
- $V$ 的当前位为 $1$：此时并查集存入的正是 $V$ 的前缀。若两点不联通，就肯定不存在大于等于 $V$ 的路径了，直接打飞，否则继续枚举。

不过，这套方法只能考虑到是否存在**大于** $V$ 的边。特殊处理一下，再单独拉个并查集把等于的扔进去就对了。

```cpp
#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
using Graph = vector<vector<size_t>>;
struct DSU {
  vector<ptrdiff_t> fa;
  DSU(size_t n): fa(n, -1) {}
  size_t find(size_t x) { return fa[x] < 0 ? x : fa[x] = find(fa[x]); }
  size_t setSize(size_t x) { return -fa[find(x)]; }
  bool check(size_t x, size_t y) { return find(x) == find(y); }
  void merge(size_t x, size_t y) {
    if (check(x, y)) return;
    if (setSize(x) > setSize(y)) swap(x, y);
    fa[find(y)] -= setSize(x);
    fa[find(x)] = find(y);
  }
};
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t n, m, q;
  uli k;
  fin >> n >> m >> q >> k;
  vector<DSU> ds(61, DSU{n});
  while (m--) {
    size_t u, v;
    uli w;
    fin >> u >> v >> w;
    --u, --v;
    for (size_t i = 0; i < 60; ++i)
      if (((w >> i) & (k >> i | 1)) == (k >> i | 1)) ds[i].merge(u, v);
    if ((w & k) == k) ds[60].merge(u, v);
  }
  while (q--) {
    size_t x, y;
    fin >> x >> y;
    --x, --y;
    if (ds[60].check(x, y)) goto yes;
    for (size_t i = 59; i < 60; --i) {
      bool tst = ds[i].check(x, y);
      if (((k >> i) & 1) && !tst) goto no;
      if (!((k >> i) & 1) && tst) goto yes;
    }
  no:
    fout << "No\n";
    continue;
  yes:
    fout << "Yes\n";
  }
  return 0;
}
```

---

## 作者：Hadtsti (赞：0)

### 题意简述

给定 $n(1\le n\le 10^5)$ 个结点 $m(1\le m\le 5\times 10^5)$ 条边的有权无向图 $G$，定义一条路径的权值为其经过边的边权的按位与和。给定 $V$ 和 $q$ 组询问，每组询问求 $x$ 和 $y$ 之间是否存在一条权值大于等于 $V$ 的路径。

$V$ 和边权均为 $[0,2^{60})$ 内的整数。

### 题目分析

考虑大于等于 $V$ 的数 $U$ 在二进制下长什么样子。不妨设 $x$ 是最大的满足 $U>>x$ 与 $V>>x$ 相等的整数，则有（注：下文一个数的第 $i$ 位都是指该数在 $60$ 位二进制下最高的第 $i$ 位）：

- $U$ 前 $x$ 位与 $V$ 相同。

- 若 $U\neq V$，则 $U$ 第 $x+1$ 位为 $1$，而 $V$ 的第 $x+1$ 位为 $0$。$U$ 的第 $x+2$ 及往后的位任意取。

而若想让路径权值 $U\ge V$，$U$ 必定对应上文中的一个符合条件的 $x$。那么对于固定的 $x$，使得最终 $U$ 满足条件的边权 $z$ 的前 $x+1$ 位都是固定的，后面的位任取。根据这一特点，又注意到题目中对边权进行的是按位与运算，我们判断一条边能否出现在权值 $U$ 对应 $x$ 为某值的路径中，就等价于判断其边权 $z$ 是否满足前 $x+1$ 位符合上文 $U$ 的特点。我们直接对不同的 $x$，计算出一个数 $a_x$ 使得其前 $x+1$ 位符合条件，剩下位全为 $0$，然后判断 $(z\land x)=x$ 是否成立即可。

那么对一种 $x$，每条边能否存在于对应情况中都是确定的，所以判断两个点之间是否存在满足条件的路径可以通过并查集实现。最终复杂度为 $O(n+m\alpha(n)+q\alpha(n))$。另外由于 $x$ 最多有 $61$ 种取值，带一个比较大的常数。实现细节看代码。

~~多说一句，这个题在 SDCPC2024 作为热身赛题目试机用了，当时我写出来一直 T，后来发现是评测机太慢导致不加按秩合并过不了。但洛谷不加照样能过……~~

### 代码实现
~~代码的常数是 64，这里给的是没加按秩合并的版本~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,x,y,fa[70][100010],cnt;
long long V,z,bs,con[70];
template<typename T>void rd(T &x)
{
	x=0;
	char c=getchar();
	T f=1;
	for(;c>'9'||c<'0';c=getchar())
		if(c=='-')
			f=-1;
	for(;c<='9'&&c>='0';c=getchar())
		x=(x<<3)+(x<<1)+c-'0';
	x*=f;
}
int getf(int op,int x)
{
	return x==fa[op][x]?x:fa[op][x]=getf(op,fa[op][x]);
}
inline void add(int op,int x,int y)
{
	int X=getf(op,x),Y=getf(op,y);
	if(X!=Y)
		fa[op][X]=Y;
}
int main()
{
	rd(n),rd(m),rd(q),rd(V);
	for(int i=59;i>=0;i--)
	{
		if(V>>i&1)
			bs+=(1ll<<i);
		else
			con[++cnt]=bs+(1ll<<i);
	}
	con[++cnt]=bs;
	for(int i=1;i<=cnt;i++) 
		for(int j=1;j<=n;j++)
			fa[i][j]=j;
	for(int i=1;i<=m;i++)
	{
		rd(x),rd(y),rd(z);
		for(int j=1;j<=cnt;j++)
			if((z&con[j])==con[j])
				add(j,x,y);
	}
	while(q--)
	{
		rd(x),rd(y);
		bool fg=0;
		for(int i=1;i<=cnt;i++)
			if(getf(i,x)==getf(i,y))
			{
				fg=1;
				break;
			}
		puts(fg?"Yes":"No");
	}
	return 0;
}
```

---

