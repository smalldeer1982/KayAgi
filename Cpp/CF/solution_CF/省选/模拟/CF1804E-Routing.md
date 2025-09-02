# Routing

## 题目描述

Ada operates a network that consists of $ n $ servers and $ m $ direct connections between them. Each direct connection between a pair of distinct servers allows bidirectional transmission of information between these two servers. Ada knows that these $ m $ direct connections allow to directly or indirectly transmit information between any two servers in this network. We say that server $ v $ is a neighbor of server $ u $ if there exists a direct connection between these two servers.

Ada needs to configure her network's WRP (Weird Routing Protocol). For each server $ u $ she needs to select exactly one of its neighbors as an auxiliary server $ a(u) $ . After all $ a(u) $ are set, routing works as follows. Suppose server $ u $ wants to find a path to server $ v $ (different from $ u $ ).

1. Server $ u $ checks all of its direct connections to other servers. If it sees a direct connection with server $ v $ , it knows the path and the process terminates.
2. If the path was not found at the first step, server $ u $ asks its auxiliary server $ a(u) $ to find the path.
3. Auxiliary server $ a(u) $ follows this process starting from the first step.
4. After $ a(u) $ finds the path, it returns it to $ u $ . Then server $ u $ constructs the resulting path as the direct connection between $ u $ and $ a(u) $ plus the path from $ a(u) $ to $ v $ .

As you can see, this procedure either produces a correct path and finishes or keeps running forever. Thus, it is critically important for Ada to configure her network's WRP properly.

Your goal is to assign an auxiliary server $ a(u) $ for each server $ u $ in the given network. Your assignment should make it possible to construct a path from any server $ u $ to any other server $ v $ using the aforementioned procedure. Or you should report that such an assignment doesn't exist.

## 样例 #1

### 输入

```
6 7
1 2
2 3
3 1
4 5
5 6
4 6
2 5```

### 输出

```
Yes
2 5 2 5 2 5```

## 样例 #2

### 输入

```
3 2
1 2
2 3```

### 输出

```
Yes
2 1 2```

## 样例 #3

### 输入

```
4 4
1 3
2 3
4 1
4 2```

### 输出

```
Yes
3 3 1 1```

## 样例 #4

### 输入

```
6 5
1 2
2 3
3 4
4 5
5 6```

### 输出

```
No```

# 题解

## 作者：JWRuixi (赞：9)

~~RMJ 真的完蛋了……~~
### 题意
给定一个 $n$ 个点 $m$ 条边的 **无向联通图**，称 $y$ 是 $x$ 的邻居，当且仅当无向边 $(x,y)$ 存在。

你需要构造一个序列 $(a_1,\dots,a_n)$，满足：
- 对于任意 $1\leq i\leq n$，无向边 $(i,a_i)$ 存在；
- 对于任意 $x,y(x\neq y)$，初始时 $i$ 为 $x$，然后不断让 $i$ 变为 $a_i$，存在某个 $i$，使得 $y$ 是其一个邻居。

或报告无解。
### 分析
首先转换题意，可以按照给的方式构造一个基环树，且环上挂的树高最多为 $1$，那也就是说从原图上抓一颗基环树下来，且环外的每个点都直接想换连边。

看到数据范围 $n\leq20$ 激动了，直接暴力枚举环是哪一个集合不就结束了！结果发现不会通过集合构造对应的环……

仔细思考了一下，感觉是很套路的 dp。直接找环可能有困难，所以我们考虑先找一条链，在把首位接上。直接设 $f_{S,i}$ 表示选的集合为 $S$，起点是 $i$，可能的终点集合。仔细一想，这是一个环耶，那我们把上面每一个点都当起点算一遍不是很傻，所以直接设 $\min(S)$ 为起点，这样就可以省掉一维了！

找答案可以直接每次枚举可能终点，让后从他下一个点连过来。

总复杂度 $\mathcal O(n2^n)$，随便跑。
### code
```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define LL long long
#define writesp(x) write(x), putchar(' ')
#define writeln(x) write(x), putchar('\n')
#define FileIO(ch) freopen(ch".in", "r", stdin), freopen(ch".out", "w", stdout)
using namespace std;

namespace IO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
#if ONLINE_JUDGE
#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
#else
#define gh() getchar()
#endif
    inline long long read() {
        char ch = gh();
        long long x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    template <typename _Tp>
    inline void write(_Tp x) {
    	static char stk[64], *top = stk;
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        do *top++ = x % 10, x /= 10;
        while (x);
        while (top != stk) putchar((*--top) | 48);  
    }
}

using IO::read;
using IO::write;

const int maxn(25), maxb((1 << 20) + 7);
int n, m, g[maxn], f[maxb], p[maxn];

inline int lowbit (int x) { return x & (-x); }

int main() {
	n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read();
		g[u] |= 1 << v - 1;
		g[v] |= 1 << u - 1;
	}
	for (int i = 1; i <= n; i++) f[1 << i - 1] = 1 << i - 1;
	for (int s = 0; s < (1 << n); s++) {
		if (__builtin_popcount(s) < 2) continue;
		for (int i = 1; i <= n; i++) {
			if (s >> i - 1 & 1) {
				if ((1 << i - 1) == lowbit(s)) continue;
				if (f[s ^ (1 << i - 1)] & g[i]) f[s] |= (1 << i - 1);
			}
		}
	}
	for (int s = 0; s < (1 << n); s++) {
		bool flg = 1;
		int x = __lg(lowbit(s)) + 1;
		if (!(f[s] & g[x])) continue;
		for (int i = 1; i <= n; i++) {
			if (s >> i - 1 & 1) continue;
			if (!(g[i] & s)) { flg = 0; break; }
		}
		if (!flg) continue;
		for (int i = 1; i <= n; i++) if (!(s >> i - 1 & 1)) p[i] = __lg(lowbit(s & g[i])) + 1;
		int t = s;
		while (t) {
			for (int i = 1; i <= n; i++) if ((f[t] >> i - 1 & 1) && (g[x] >> i - 1 & 1)) {
				p[x] = i, t ^= (1 << i - 1), x = i;
				break;
			}
		}
		break;
	}
	if (!p[1]) return puts("No");
	puts("Yes");
	for (int i = 1; i <= n; i++) writesp(p[i]);
}
// I love WHQ!
```

---

## 作者：houzhiyuan (赞：3)

$O(n2^n)$，也许是踩标了。

题目意思转化一下就是找一棵基环树，然后要求除了环上的点，其他点都要有一条连向环的边。

一个简单的想法是找出所有环，然后去判定。

找环直接状压，最简单的想法是设 $f_{S,i,j}$ 表示点集是 $S$，一条链开头是 $i$，末尾是 $j$ 是否可行，然后判断 $i,j$ 是否有边就可以找环。

直接做复杂度 $O(n^32^n)$，因为要枚举下一个点。

注意到由于是一个环，所以起点无所谓，因此直接令 $i$ 为 $S$ 中最小的点。

然后转移枚举另一个点 $k$，相当于判定 $j,k$ 之间是否有边。

注意到这个东西可以再状压，令 $f_{S}$ 表示所有合法的 $j$ 构成的集合，那么只需要判断与 $k$ 相连的点集与 $f_{S}$ 是否有交就可以转移了，这样复杂度 $O(n2^n)$。

输出方案也比较简单，找到链的末尾点，然后倒着往回跑即可。

```cpp
#include<bits/stdc++.h>
#define V vector
#define Vi vector<int>
#define sz(a) ((int)a.size())
#define fi first
#define se second
#define Int pair<int,int>
#define Inf ((int)1e9)
#define pb push_back
#define ins insert
#define For(i, x, y) for (auto i = (x); i <= (y); i++)
#define Rep(i, x, y) for (auto i = (x); i >= (y); i--)
using namespace std;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	Vi d(n);
	for (int i = 1, x, y; i <= m; i++) {
		cin >> x >> y, x--, y--;
		d[x] |= 1 << y, d[y] |= 1 << x;
	}
	Vi f(1 << n), g(1 << n);
	for (int i = 0; i < n; i++)f[1 << i] = 1 << i;
	for (int i = 0; i < 1 << n; i++)
		for (int j = 0; j < n; j++)
			if (!(i & (1 << j)) && (f[i]&d[j]) && ((i & -i) < 1 << j))
				f[i + (1 << j)] |= (1 << j);
	for (int i = 0; i < 1 << n; i++)
		for (int j = 0; j < n; j++)
			if ((f[i] & (1 << j)) && (d[j] & (i & -i)))
				g[i] |= 1 << j;
	Vi lg(1 << n);
	for (int i = 0; i < n; i++)lg[1 << i] = i;
	auto write = [&](int now) {
		Vi Ans(n);
		for (int i = 0; i < n; i++)if (!(now & (1 << i))) {
				int t = d[i] & now;
				Ans[i] = lg[t & -t];
			}
		int sta = lg[g[now] & -g[now]];
		for (int t = lg[g[now] & -g[now]]; now;) {
			now -= 1 << t;
			if (!now)Ans[t] = sta;
			for (int i = 0; i < n; i++)if ((d[t]&f[now]) & (1 << i)) {
					Ans[t] = i;
					t = i;
					break;
				}
		}
		cout << "Yes\n";
		for (int i = 0; i < n; i++)cout << Ans[i] + 1 << ' ';
		cout << '\n';
	};
	for (int i = 0; i < 1 << n; i++)if (g[i]) {
			int ff = 1;
			for (int j = 0; j < n; j++)if (!(d[j]&i))ff = 0;
			if (ff)return write(i), 0;
		}
	cout << "No\n";
	return 0;
}
```

---

## 作者：AzusidNya (赞：1)

## CF1804E Routing

不难的状压。

考虑建一张新图，其中 $i$ 向 $a_i$ 连有向边，这是个内向基环树。下面称 $a_i$ 为 $i$ 的父亲节点。

然后两个条件变成，新图中的每一条边都在原图中作为无向边出现过，每个非环上的节点必须能一步跳到环上，也就是与环的距离必须为 $1$。

也就是我们要在原图中找一个子图满足上面的条件。

考虑先找到环，然后再枚举环外的节点，判断它们出边集合是否与环上的点有交，如果有交就令其父亲为环上任意一个点即可。

$n \le 20$，很自然地想到状压。现在的目标是对于每个集合判定是否有一个环能恰好经过集合内的节点一次。

然后有个很暴力的想法。设 $f(S, u, v)$ 表示是否存在一条从 $u$ 经过 $S$ 所有点刚好一次到达 $v$ 的路径。转移是显然的。但是这样似乎时空复杂度都炸了。考虑优化。

这个做法的瓶颈是，对于所有 $i \in S$，所有的 $f(S, i, i)$ 都是等价的，也就是等价的路径会判断环长次。考虑直接钦定起点为 $S$ 中编号最小的点为起点，设 $f(S, v)$ 表示是否存在以 $S$ 中编号最小的节点为起点，经过 $S$ 中的点恰好一次后到达 $v$ 的路径。转移为枚举 $v$ 满足 $w$ 的编号大于 $S$ 中编号最小的节点的编号的出边 $(v, w)$，然后 $f(S, v)$ 转移到 $f(S \cup w, w)$ 即可。特殊地如果 $v$ 有 $S$ 内编号最小的节点的出边，那么标记存在一个环经过 $S$ 中的节点恰好一次。

 找到环后，对于所有环按上面的方法枚举集合外节点并判断出边即可，如果所有环都找不到答案则无解。输出答案不难，对于环上的点，在转移时记录转移点，递归的得到父亲节点即可。对于不在环上的点，任意指定环上的点作为父亲即可。

时间复杂度 $O(n ^ 2 2 ^ n)$。

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<cstring>
// #define int long long
#define eb emplace_back
#define mp make_pair
// #define DEBUG
using namespace std;
const int P = 998244353, inf = 0x3f3f3f3f;
using pii = pair<int, int>;
using piii = pair<int, pii>;
using piiii = pair<pii, pii>;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;
namespace azus{
	int St;
	int n, m;
	bool f[1048577][21], g[1048577];
	int h[1048577], fa[1048577][21];
	int st[1048577], lim[21];
	int Ed;
	int main(){
		cin >> n >> m;
		for(int i = 1, u, v; i <= m; i ++){
			cin >> u >> v;
			lim[u] |= (1 << (v - 1));
			lim[v] |= (1 << (u - 1));
		}
		for(int i = 1; i < (1 << n); i ++)
			st[i] = __builtin_ctz(i) + 1;
		for(int i = 1; i <= n; i ++)
			f[(1 << i - 1)][i] = 1;
		for(int i = 1; i < (1 << n); i ++){
			for(int j = 1; j <= n; j ++){
				if(!((1 << j - 1) & i))
					continue;
				for(int k = st[i] + 1; k <= n; k ++){
					if(!(lim[j] & (1 << k - 1))) continue;
					if((1 << k - 1) & i) continue;
					f[i | (1 << k - 1)][k] |= f[i][j];
					if(f[i][j]) fa[i | (1 << k - 1)][k] = j;
				}
				if(lim[j] & (1 << st[i] - 1)){ g[i] |= f[i][j]; if(f[i][j]) h[i] = j;}
			}
		}
		g[0] = 1;
		for(int s = 1; s < (1 << n); s ++){
			if(!g[s]) continue;
			vector<int> c(n + 1, 0);
			bool flg = 0;
			for(int i = 1; i <= n; i ++){
				if((1 << i - 1) & s) continue;
				if(!(lim[i] & s)){
					flg = 1; break;
				}
				c[i] = st[lim[i] & s];
			}
			if(flg) continue;
			int u = st[s], x = s, y;
			c[u] = h[s]; u = h[s];
			while(u != st[s]){
				c[u] = fa[x][u], y = x ^ (1 << u - 1);
				u = fa[x][u], x = y;
			}
			cout << "Yes\n";
			for(int i = 1; i <= n; i ++)
				cout << c[i] << " ";
			cout << "\n";
			return 0;
		}
		cout << "No\n";
		return 0;
	}
}
signed main(){
#ifndef DEBUG
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
#endif
	int T = 1;
	while(T --)
		azus::main();
	return 0;
}
```

---

## 作者：幽云蓝 (赞：1)

CF1804E。

把定 $a(i)$ 当做选边，留下选择的边，删去其他边，那么形成的图一定是一个内向基环树森林。

现在我们证明一定有一种答案满足以下条件：

1. 形成的基环树森林只有一棵树；
2. 这棵树的非环上点都直接连向环上点。

考虑调整法，假设我们找到了任意一组答案。若第一个条件不被满足，那么我们把两棵树的单独拎出来，既然它们能互相到达，那么事实上我们可以把它们的环合并成一个大环，证明是显然的。同理，合并成一棵树后，由于环上点能到达所有点，那么所有点也一定能直接连向环上点。

于是预处理 $f_{S}$ 表示点集 $S$ 的所有点的邻域的并是否为图的所有点。接下来我们从点 $1$ 开始枚举，然后用状压 dp 找出所有从 $1$ 开始回到 $1$ 的环，状态形如是否存在一条从枚举点出发的路径经过了点集 $S$ 且终点为 $x$，如果找到一个答案就退出，否则把当前结点删了，枚举下一个点继续找。复杂度是单次进行 $dp$ 时的 $n^22^n$。

然后这个时候就有人说了，主播主播，你这个 $n^22^n$ 这么拉，能过 $20$ 吗？别急。考虑之前的状态，我们直接把终点集合压起来统一转移，发现枚举一个新点后的转移就是集合求交，可以用位运算加速。由于 $n$ 才 $20$ 所以复杂度就变成 $n2^n$ 了。

注意题目中给的图是个无向图，没看清以为是有向做了一年。

---

## 作者：2018ljw (赞：1)

题目大意：给一张无向图，无自环重边。要给每个点选择一条有向出边，使得最后所有点对间均存在一条路径，满足只有最后一步经过的边可以未被选择。

有向出边，就是说若选择 $(x,y)$ 但没选择 $(y,x)$，那么从 $y$ 走到 $x$ 的边视为未被选择。

先考察一下选中边最后大概构成了一个什么图。由于每个点恰有一个出度，所以不难发现，只保留选中的边，最后形成的应该是一个基环内向树森林。接下来继续考察性质。

以下称被选中的边为树边，其余边为非树边，并且均按有解情况考虑。

- 存在一种构造方案，基环树的环上点的每个子树大小均为 $1$。

如图，黑边为树边，红边为非树边。手绘图可能略丑，见谅。

$1$ 号点是可以很容易到达环上的。但根据构造要求，环上的点也一定要能到达 $1$ 号点。

由于是基环内向树，因此环上的点不可能通过走树边来靠近 $1$ 号点，换而言之 $1$ 号点一定与环上的点有边（图中红边）。

![](https://cdn.luogu.com.cn/upload/image_hosting/9jkb4xsx.png)

进一步的，我们断掉 $1$ 与父亲的连边，连上红边。如此做下去，每个基环树一定是一个环挂着一堆单个节点，显然对于这个子图而言合法。

- 存在一种构造方案，森林中只有一棵树。

若我们需要两个环上的点能相互到达，必然需要满足，只考虑两端点分别在两个环上的点的非树边，则每个点都会被至少覆盖一次。否则总会有一条路径传过去后必须再走树边才可到达。同时，环上的点对另一环的所有子树也必须有边，理由相同。

那么如图，我们随便选取跨越两个环的一条边，将这条边替换进我们的方案里。

![](https://cdn.luogu.com.cn/upload/image_hosting/smr07vby.png)

此时 $(3,4)$ 这条路径看起来会有麻烦，因为 $3$ 不能通过原来的环走到 $4$ 了。但由于左侧环对右侧环所有点均有边，所以 $3$ 依旧可以通过左侧环到达 $4$。换而言之，此时的图依旧合法。然后接着沿用性质一压缩子树即可。

所以可得：有解时，**存在一种构造方案，使得图是一个基环内向树，且所有不在环上的点对应的树边均直接指向环**。

然后这题就看起来可做多了。

环外的点肯定要后处理，先考虑确定环。观察到 $n\le20$，考虑状压。

设 $dp_{S,x}$ 表示走完点集 $S$，最后一步位于 $x$ 时，**可行的起点集合**。转移时，枚举 $x$ 的出点 $y$ 即可。

那么对于一个 $dp_{S,x}$，其能构成一个环，当且仅当 $x$ 存在一个可到达的点，属于可行的起点集合。所以读入的时候顺手预处理每个点能到达哪些点。

但我们还要关注一个问题：环上的点要能够一步到达环外的所有点。相似的，用预处理出来的取并集现判断就行。

确定环的起点和终点后，我们就可以通过正常的动态规划构造方案的流程，记录可行转移点，倒推出环上的所有点的顺序了。

之后，对于环外的点，直接随便连到一个它能到达的环上的点即可。

```
#include<cstdio>
int n,r[21];
int a[21][21],dp[1048576][21];
int to[21];
void dx(int s,int st,int nw){
	if(s==(s&(-s)))return;
	int i,nx=s-(1<<nw);
	for(i=0;i<n;i++){
		if(!(s&(1<<i)))continue;
		if(!a[i][nw])continue;
		if(!(dp[nx][i]&(1<<st)))continue;
		to[i]=nw;
		dx(nx,st,i);
		break;
	}
}
int main(){
	int i,j,k,m;
	scanf("%d%d",&n,&m);
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		x--;y--;
		a[x][y]=a[y][x]=1;
		r[x]|=1<<y;
		r[y]|=1<<x;
	}
	m=1<<n;
	for(i=0;i<n;i++)dp[1<<i][i]=1<<i;
	for(i=1;i<m;i++){
		for(j=0;j<n;j++){
			if(!(i&(1<<j)))continue;
			if(!dp[i][j])continue;
			for(k=0;k<n;k++){
				if(!a[j][k])continue;
				if(i&(1<<k))continue;
				dp[i|(1<<k)][k]|=dp[i][j];
			}
		}
	}
	int rh=0,rs=0,rd=0;
	for(i=1;i<m;i++){
		if((i&(-i))==i)continue;
		int ch=0;
		for(j=0;j<n;j++)if(i&(1<<j))ch|=r[j];
		if((ch|i)!=m-1)continue;
		for(j=0;j<n;j++){
			if(!dp[i][j])continue;
			bool te=0;
			for(k=0;k<n;k++){
				if(!a[j][k])continue;
				if(!(dp[i][j]&(1<<k)))continue;
				rs=k;te=1;
				break;
			}
			if(!te)continue;
			rd=j;rh=i;
			break;
		}
		if(!rh)continue;
		break;
	}
	if(!rh)return printf("No"),0;
	printf("Yes\n");
	dx(rh,rs,rd);to[rd]=rs;
	for(i=0;i<n;i++){
		if(rh&(1<<i))continue;
		for(j=0;j<n;j++){
			if(!(rh&(1<<j)))continue;
			if(!a[i][j])continue;
			to[i]=j;
		}
	}
	for(i=0;i<n;i++)printf("%d ",to[i]+1);
}
```

---

## 作者：Purslane (赞：0)

# Solution

最后显然是一棵基环树。

> 你可能会觉得是基环树森林。但你别急。

合法的充要条件是所有不在环上的点离环的距离都是 $1$。

如果有两个环，那么发现第一个环上所有点到第二个环的距离依然都是 $1$，因此我们可以直接把第一个环拆了，连到第二个环上。

我们现在需要找到一个环，使得其他点到他的距离为 $1$。显然可以枚举环上节点的集合（共 $2^n$ 种），问题转化为了找原图一个子图的哈密顿回路，把它们串成一个环。

先不妨断环为链。为了降低复杂度，我们把环上编号最小的那个当做链的一条端点，因此就可以设 $dp_{S,l}$ 为是否能把 $S$ 中的点串成一条链，一端是 $\log_2 \text{lowbit } S$，另一端是 $l$。暴力转移即可。

复杂度 $O(n^22^n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=21;
int n,m,flg[MAXN][MAXN],nb[MAXN],dp[1<<MAXN][MAXN],p[MAXN];
void output(int st,int lb,int k) {
	int orik=k,ST=st;
	while(k!=lb) p[k]=dp[st][k],st-=(1<<k-1),k=p[k];
	p[lb]=orik;
	st=ST;
	ffor(i,1,n) if(!(st&(1<<i-1))) {
		ffor(j,1,n) if(flg[i][j]&&(st&(1<<j-1))) {p[i]=j;break ;}	
	}
	cout<<"YES\n";
	ffor(i,1,n) cout<<p[i]<<' ';
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,m) {int u,v;cin>>u>>v,flg[u][v]=flg[v][u]=1,nb[u]|=(1<<v-1),nb[v]|=(1<<u-1);}
	ffor(i,1,n) dp[1<<i-1][i]=n+1;
	ffor(st,1,(1<<n)-1) ffor(l,1,n) if((st&(1<<l-1))&&dp[st][l]) {
		ffor(nxt,1,n) if(!(st&(1<<nxt-1))&&flg[l][nxt]&&(1<<nxt-1)>=(st&-st)) dp[st|(1<<nxt-1)][nxt]=l;
	}
	ffor(st,1,(1<<n)-1) {
		int OR=0,lb=n+1;
		ffor(j,1,n) if(st&(1<<j-1)) lb=min(lb,j),OR|=nb[j];
		if((OR|st)==(1<<n)-1) ffor(k,1,n) if(st&(1<<k-1)) if(dp[st][k]&&flg[lb][k]) return output(st,lb,k),0;
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

有人没想到以 $\min_{i\in S} i$ 为起点。

容易发现这是一棵基环树，并且题目限制满足的充要条件就是环上的点满足。把环断一条边变成链。

先钦定起点为 $u$，设 $dp_{S,i}$ 为当前链上点集为 $S$，终点为 $i$ 是否可行。转移就是 $dp_{S,i}\to dp_{S\cup j,j}$。但是 $O(2^nn^3)$ 不太可能。

于是考虑优化。设 $f_{S}$ 为一个二进制串，第 $i$ 位为 $1$ 表示链上点集为 $S$ 时 $i+1$ 可以作为终点。考虑转移，再维护一个 $g_{S}$，第 $i$ 位为 $1$ 表示点集为 $S$ 时，存在一个可行的终点与 $i+1$ 直接连边。简单转移。

构造时枚举上一个点是什么。注意要满足终点、连边的若干条件限制。并且具体实现时可以只维护 $g$。时间复杂度 $O(2^nn^2)$。

code：

```cpp
int n,m,c[23],ans[23],f[N],dp[N];
void solve(int u,int S,int v){
	vector<int> g;
	g.eb(v+1);
	S^=1<<v++;
	while(S){
		int p=0;
		rep(i,0,n-1){
			if(!(S>>i&1)||!(c[v]>>i&1)){
				continue;
			}
			if(dp[S^(1<<i)]>>i&1){
				p=i;
				break;
			}
		}
		v=p+1;
		g.eb(p+1);
		S^=1<<p;
	}
	int lst=0;
	queue<int> q;
	for(int i:g){
		ans[i]=lst;
		lst=i;
		q.push(i);
	}
	ans[*g.begin()]=lst;
	while(q.size()){
		int u=q.front();
		q.pop();
		rep(v,1,n){
			if(ans[v]||!(c[u]>>(v-1)&1)){
				continue;
			}
			ans[v]=u;
			q.push(v);
		}
	}
	rep(i,1,n){
		printf("%d ",ans[i]);
	}
}
void Yorushika(){
	scanf("%d%d",&n,&m);
	rep(i,1,m){
		int u,v;scanf("%d%d",&u,&v);
		c[u]|=1<<(v-1),c[v]|=1<<(u-1);
	}
	rep(i,1,n){
		c[i]|=1<<(i-1);
	}
	const int k=1<<n;
	rep(S,0,k-1){
		int T=0;
		rep(i,0,n-1){
			if(S>>i&1){
				T|=c[i+1];
			}
		}
		if(__builtin_popcount(T)==n){
			f[S]=1;
		}
	}
	rep(u,1,n){
		mems(dp,0);
		dp[0]=1<<(u-1),dp[1<<(u-1)]=c[u];
		rep(S,0,k-1){
			rep(i,0,n-1){
				if(!(S>>i&1)){
					continue;
				}
				if(dp[S^(1<<i)]>>i&1){
					dp[S]|=c[i+1];
					if(__builtin_popcount(S)>1&&f[S]&&(c[u]>>i&1)){
						puts("Yes");
						solve(u,S,i);
						return;
					}
				}
			}
		}
	}
	puts("No");
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：youdu666 (赞：0)

调了一个下午，写篇题解庆祝一下。

### 思路：深搜

啊对对对，就是深搜，但是有玄学剪枝。

暴力搜出每一个点是否放在环上，然后直接看不选的点能不能一步走到选的点，选的点能不能形成一个环。

理论复杂度是 $O(n^22^n)$ 的，常数小其实应该能过，但是像我这种人傻常数大的就一直最后几个点超时。于是我掐指一算，在环上的数字一定不会很多，于是，每次搜索的时候先搜当前点不在环上再搜在环上，直接从超时变成了连时限的四分之一都没到。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=25;
int n,m,x,y,to[N],root,cmt;
bool on_hoop[N],hpp,vis[N];
struct ege{
	int ed,nxt;
}e[N*N];int num;
int head[N];
std::vector<int> g[N];
inline double TimE(void)
{
	return (double)clock()/CLOCKS_PER_SEC;
}
inline void add(int x,int y)
{
	e[++num].nxt=head[x];
	e[num].ed=y;
	head[x]=num;
}
bool dfs(int u)
{
	if(u==root)
	{
		if(cmt<=1)
			return true;
		else
			return false;
	}
	if(to[u] or vis[u])return false;
	vis[u]=true;
	for(int t=head[u];t;t=e[t].nxt)
	{
		int v=e[t].ed;
		if(on_hoop[v]==false or vis[v])continue;
		to[u]=v;
		cmt--;
		if(dfs(v))
		{
			vis[u]=false;
			return true;
		}
		cmt++;
	}
	vis[u]=false;
	to[u]=0;
	return false;
}
inline void chk(void)
{
	int yp=0;
	for(int i=1;i<=n;i++)
		to[i]=0,yp+=on_hoop[i];
	for(int i=1;i<=n;i++)
	{
		if(on_hoop[i])
		{
			int cnt=0;
			for(int t=head[i];t;t=e[t].nxt)
			{
				int v=e[t].ed;
				if(on_hoop[v])
					cnt++;
			}
			if((cnt<2 and yp>2) or cnt<1)
				return;
		}
		else
		{
			bool fk=true;
			for(int t=head[i];t;t=e[t].nxt)
			{
				int v=e[t].ed;
				if(on_hoop[v])
				{
					to[i]=v;
					fk=false;
					break;
				}
			}
			if(fk)return;
		}
	}
	if(yp>1)
	for(int i=1;i<=n;i++)
	{
		if(not to[i])
		{
			root=i;
			bool fk=false;
			for(int t=head[i];t;t=e[t].nxt)
			{
				int v=e[t].ed;
				if(on_hoop[v])
				{
					to[i]=v;
					cmt=yp;
					if(dfs(v))
					{
						fk=true;
						break;
					}
				}
			}	
			if(not fk)return;
			break;
		}
	}
	cout<<"Yes\n";
	for(int i=1;i<=n;i++)
		cout<<to[i]<<' ';
	cout<<'\n';
	exit(0);
}
void dfss(int u)
{
	if(TimE()>1.95)
	{
		cout<<"No\n";
		exit(0);
	}
	if(u>n)
	{
		chk();
		return;
	}
		// cout<<"MA";
		on_hoop[u]=false;
		dfss(u+1);
		on_hoop[u]=true;
		dfss(u+1);
}
signed main()
{
	// srand(time(0)+20071112+715+502);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	while(m--)
	{
		cin>>x>>y;
		add(x,y),add(y,x);
	}
	dfss(1);
	cout<<"No\n";
}
```


---

## 作者：Forwarcl (赞：0)

没想到 $O(2^nn^2)$ 可以过 $20$。  
但是我会乱搞。

首先，如果对每个 $i$ 连有向边 $i\to a_i$，那图是一个基环森林。  

定义 $adj(x)=\{x\}\cup\{y\mid (x,y)\in E\}$（邻居和自己），那合法的充要条件是：对于每个（基环森林上的）环，其 $adj(x)$ 的并集是 $\{1,\dots,n\}$。  
充分性显然；至于必要性，如果不满足，那环上的点一定走不到那个不在并集里的点。

有了这个结论，可以发现，森林中如果有 $\ge 2$ 个环，那一定可以只保留其中一个环。所以我们可以默认只有一个环。

有这样一个做法：找一棵生成树，然后枚举每条**原图的边**（可以是树边），看其在生成树上构成的环上的 $adj(x)$ 并集是否是 $\{1,\dots,n\}$。这样做是不对的，因为答案中的环可能包含多条非树边。

但是我们可以随机边的顺序，按照这个顺序构造一个生成树（类似 kruskal，不联通就连）。这样可以构造出很多种生成树，对每种都执行上面的算法，加个卡时，就可以 ac 了。也欢迎各位 hack。

[提交记录](https://codeforc.es/contest/1804/submission/197641789)

彩蛋：一开始写的是
```cpp
std::shuffle(edg + 1, edg + m + 1, std::mt19937 (1206));
```
也就是说，每次随机的都是同一个顺序。。这样会 wa on test 21。


---

