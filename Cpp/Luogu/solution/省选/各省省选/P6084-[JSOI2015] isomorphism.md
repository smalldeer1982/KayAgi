# [JSOI2015] isomorphism

## 题目描述

一个无向树的度数为 $2$ 的结点称为假结点，其它结点称为真结点。一个无向树的简化树其结点由原树的全体真结点组成，两个真结点之间有边当且仅当它们在原树中有边，或者在原树中有一条联结这两个结点的路，其中间节点全是假结点。两个无向树各自的简化树如果同构，即存在结点之间的一一对应，使得在一个树中的任意两个结点之间有边当且仅当它们的对应结点在另一个树中有边，则称原来的两个无向树实质同构。

给定若干个无向树，将相互实质同构的无向树只保留一个其余删除。统计剩下的相互不实质同构的无向树个数，并将它们的简化树结点个数从小到大输出。

## 说明/提示

#### 数据范围

对于 $100\%$ 的数据，$2\leq m\leq 20, 2\leq n\leq 10^4$。

## 样例 #1

### 输入

```
2
4
1 4
2 4
3 4
5
1 3
2 3
3 4
4 5```

### 输出

```
1
4```

# 题解

## 作者：Great_Influence (赞：5)

这道题可以分成两部分。

1. 缩树。
2. 树同构。

第一步直接在原树上重新建树即可，关键在于第二步。

这里的主要问题在于对无根树判同构很麻烦，因此我们可以考虑直接将无根树转换成有根树。

至于选什么点做根， 这个就很明显了：重心。

唯一的问题在于一棵树的重心可能有两个。不过这两个重心肯定是直接相连的，我们把相连的边断开看做两棵树即可。

然后跑你最喜欢的有根树哈希算法就可以了。我这里选择的哈希值计算方法是:

$$Hash[u]=\oplus(Hash[v]-W[u])*W[v]$$

其中 $W[u]$ 是随机出来的某种系数。

代码:
```cpp
#include<bits/stdc++.h>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define rep(i,a,b) for(register int i=(a);i<(b);++i)
#define pb push_back
#define mp make_pair
using namespace std;

inline void Chkmax(int&u,int v){u<v?u=v:0;}

const int MAXN = 1e4 + 7;

vector <int> ed[MAXN];

set < pair<int, unsigned long long> > G;

static int rt1, rt2, d[MAXN];

static int sz[MAXN], F[MAXN];

static unsigned long long w[MAXN];

void getcentr(int u, int fa, int al)
{
	sz[u] = 1, F[u] = 0;
	for(int v : ed[u]) if(v ^ fa) getcentr(v, u, al), Chkmax(F[u], sz[v]), sz[u] += sz[v];
	Chkmax(F[u], al - sz[u]);
	if(!rt1 || F[u] < F[rt1]) rt1 = u, rt2 = fa;
}

static unsigned long long hs[MAXN];

void geths(int u, int fa)
{
	sz[u] = 1;
	hs[u] = 0;
	for(int v : ed[u]) if(v ^ fa) geths(v, u), sz[u] += sz[v];
	for(int v : ed[u]) if(v ^ fa)
		hs[u] ^= (hs[v] - w[sz[u]]) * w[sz[v]];
	hs[u] ^= w[sz[u]];
}

inline unsigned long long calc(int n, int zz)
{
	rt1 = rt2 = 0;
	Rep(i, 1, n) if(d[i] == 1) {getcentr(i, 0, zz); break;}
	//cerr << rt1 << ' ' << rt2 <<endl;
	if(F[rt1] == F[rt2])
	{
		geths(rt1, rt2), geths(rt2, rt1);
		return hs[rt1] ^ hs[rt2];
	}
	geths(rt1, 0);
	return hs[rt1];
}

static vector <int> us[MAXN];

static pair <int, int> cn[MAXN];

void shrink(int u, int fa, int tf, int & n)
{
	if(d[u] == 2) {for(int v : us[u]) if(v ^ fa) shrink(v, u, tf, -- n);}
	else
	{
		if(tf) ed[u].pb(tf), ed[tf].pb(u);
		for(int v : us[u]) if(v ^ fa) shrink(v, u, u, n);
	}
}

#define read(x) cin>>x

inline void init()
{
	static int n, m, u, v;
	srand(time(NULL));
	Rep(i, 1, 10000) w[i] = rand() | (unsigned long long)rand() << 30;
	read(m);
	Rep(i, 1, m)
	{
		read(n);
		Rep(i, 1, n) us[i].resize(0), ed[i].resize(0), d[i] = 0;
		Rep(i, 1, n - 1) read(u), read(v), ++ d[u], ++ d[v], us[u].pb(v), us[v].pb(u);
		int s = n;
		Rep(i, 1, n) if(d[i] == 1) {shrink(i, 0, 0, s); break;}
		G.insert(mp(s, calc(n, s)));
	}
}

inline void solve()
{
	cout << G.size() << endl;
	for(auto z : G) printf("%d ", z.first);
	puts("");
}

int main()
{
	init();
	solve();
	return 0;
}
```

---

