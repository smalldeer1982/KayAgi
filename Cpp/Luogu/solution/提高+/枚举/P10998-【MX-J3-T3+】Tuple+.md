# 【MX-J3-T3+】Tuple+

## 题目背景

原题链接：<https://oier.team/problems/J3F>。

## 题目描述

你有 $m$ 个三元组 $(u_i,v_i,w_i)$，保证 $1\le u_i<v_i<w_i\le n$ 且三元组两两不同。有多少组 $(a,b,c,d)$ 满足 $1\le a<b<c<d\le n$，且在这 $m$ 个三元组当中，存在四个三元组 $(a,b,c),\allowbreak (a,b,d),\allowbreak (a,c,d),\allowbreak (b,c,d)$？

## 说明/提示

**【样例解释 #1】**

有 $(1,2,3,4),(3,4,5,6),(1,2,3,7)$ 符合题意。

**【数据范围】**

保证 $4\le n \le 3\times 10^5$，$4\le m\le 3\times 10^5$。

本题没有部分分。

## 样例 #1

### 输入

```
7 11
1 2 3
2 3 4
1 3 4
1 2 4
3 4 5
4 5 6
3 5 6
3 4 6
1 2 7
2 3 7
1 3 7
```

### 输出

```
3
```

## 样例 #2

### 输入

```
9 30
1 2 3
1 2 5
1 2 6
1 3 4
1 3 5
1 3 6
1 3 7
1 3 8
1 3 9
1 4 5
1 4 6
1 4 9
1 7 9
2 3 4
2 3 5
2 3 6
2 3 7
2 3 8
2 3 9
2 4 9
2 5 8
2 6 7
2 7 9
3 4 5
3 4 8
3 4 9
3 5 9
3 7 8
3 7 9
3 8 9
```

### 输出

```
7
```

# 题解

## 作者：CommonAnts (赞：38)

## 思路

这个问题研究的是满足条件的四元组个数，那么我们应该研究“满足条件的四元组”的结构，以及如何从题目的三元组找到对应的四元组。

经过一些尝试和观察或者打表，可以发现这个题答案不可能特别大。

因此，考虑如何高效地枚举可能的四元组。

## 算法

考虑一个三元组 $(u,v,w)$ 属于哪些合法四元组。可以发现，$(u,v,w)$ 所属的合法四元组个数，等于满足“ $(u,v,x),(u,w,x),(v,w,x)$ 三个三元组都存在”的 $x$ 的个数。（这里还是有序的 $u\lt v\lt w\lt x$）

所以，我们定义 $S(u,v)$ 表示使得 $(u,v,x)$ 三元组存在的 $x$ 的的集合。

**朴素算法 1** 我们预处理算出所有非空的 $S(u,v)$，然后对于每个三元组 $(u,v,w)$ 直接暴力计算 $S(u,v),S(v,w),S(u,w)$ 的交集大小，累加起来就是答案。

**定理 上述算法的时间复杂度是 $O(m^{4/3})$。**

**证明如下：**

首先注意到，暴力求这三个集合交集大小的时间复杂度同阶于其中**最小的**一个集合大小，只要枚举最小的那个集合里的元素查询在不在其它集合里即可。

所以时间复杂度 $\sim\sum_{(u,v,w)} \min(\lvert S(u,v) \rvert, \lvert S(u,w) \rvert, \lvert S(v,w) \rvert)$

现在只要分析 $S$ 的大小。为了方便，我们之后称 $1$ 到 $n$ 是无向图上的点，称 $S(u,v)$ 是无向图上 $(u,v)$ 的边权。那么：

1. 所有边权和为 $m$
2. 我们要最大化图上前 $m$ 大的三元环边权最小值之和，这是上述算法时间复杂度的上界。

容易证明，如果一个图中有 $i$ 个不同的三元环，那么图里至少有 $\sim i^{2/3}$ 条边。（参见三元环计数的分析。）

所以第 $i$ 大的三元环边权最小值不会超过 $\sim\frac{m}{i^{2/3}}$。

所以，前述朴素算法 1 时间复杂度上界不超过 $\sim\sum_{i=1}^m \frac{m}{i^{2/3}}\sim \int_1^m \frac{m}{i^{2/3}} \mathrm di+O(m) =O(m^{4/3})$。

这个朴素算法 1 就可以通过本题。

## 参考程序

这个 $O(m^{4/3}\log m)$ 程序使用了 `std::map`，改为hash表（散列表）可以去掉复杂度中的 $\log$。

```cpp
#include<bits/stdc++.h>

using namespace std;
typedef pair<int,int> p_t;

const int MX=300005;
map<p_t, set<int>> d;
int n,m;
int u[MX],v[MX],w[MX];

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i]>>w[i];
        d[make_pair(u[i],v[i])].insert(w[i]);
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        set<int> *W=&d[make_pair(u[i],v[i])], *V=&d[make_pair(u[i],w[i])], *U=&d[make_pair(v[i],w[i])];
        if(U->size()>V->size())swap(U,V);
        if(V->size()>W->size())swap(V,W);
        if(U->size()>V->size())swap(U,V); // 冒泡排序，找到最小的一个集合，保证求交集复杂度
        for(auto j:*U)if(V->find(j)!=V->end()&&W->find(j)!=W->end()){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：yummy (赞：18)

# C+. Tuple+ 官方题解

本题考察的主要知识点：

- 【6】时间复杂度分析（三元环计数）

## yummy 的 $O(m\sqrt m)$

类似三元环计数，记录每个结点的度数（连接三角形数），然后重排每个 $(u,v,w)$ 使得 $\deg u\ge \deg v\ge \deg w$（若度数相同，按照编号排序）。

称 $a$ 指向 $(b,c)$ 当且仅当存在 $(a,b,c)$。称 $(b,c)$ 指向 $d$ 当且仅当存在 $(b,c,d)$。

枚举 $a$，然后枚举所有被 $a$ 指向的 $(b,c)$，然后枚举 $(b,c)$ 指向的所有 $d$，用 `unordered_map` 检查 $(a,b,d)$ 和 $(a,c,d)$ 是否存在。

---

时间复杂度 $\le O(m\sqrt m)$ 的证明：考虑每个 $(b,c,d)$ 会贡献几次访问，也就是有几个 $a$ 指向给定的 $(b,c)$。

- 如果 $\deg b>\sqrt m$，则 $\deg a>\sqrt m$（因为度数排过序），这样的 $a$ 不超过 $O(\sqrt m)$ 个。
- 如果 $\deg b<\sqrt m$，则 $a$ 的个数不超过 $\deg b$，从而 $a$ 不超过 $O(\sqrt m)$ 个。

时间复杂度一个可能的取等条件：考虑一个数据，令 $n=\sqrt m$，然后连边所有 $(a,b,b\bmod n+1)$，那么每条 $(b,c,d)$ 都会被 $O(n)$ 个 $(a,b,c)$ 贡献，这个数据下代码时间复杂度是 $O(m\sqrt m)$。

## EI 的 $O(m^{4/3})$

记录每个结点的度数，按度数从小到大的顺序重排 $(u,v,w)$。

接下来枚举所有 $a$，记录所有被 $a$ 指向的 $(b,c)$，对这些 $(b,c)$ 跑三元环计数。

---

时间复杂度为 $O(m^{4/3})$ 的证明：首先 $k$ 条边的三元环计数是 $O(k^{1.5})$ 的。讨论 $\deg a$。

- 如果 $\deg a>m^{2/3}$，则 $a$ 是后 $m^{1/3}$ 个点之一，$a$ 最多指向 $(m^{1/3})^2$ 个数对，贡献的总时间复杂度为 $m^{1/3}\cdot ((m^{1/3})^2)^{1.5}=m^{4/3} $。

- 如果 $\deg a< m^{2/3}$，则 $a$ 仍然最多指向 $\deg a<m^{2/3}$ 个数对，同时 $\sum \deg a=O(m)$。

  考察 $\sum (\deg a)^{1.5}$ 的最大值， 因为 $f(x)=x^{1.5}$ 的凹凸性，这个最大值在一些 $\deg a=m^{2/3}$，另一些 $\deg a=0$ 的时候取到最大值 $m^{1/3}(m^{2/3})^{1.5}=m^{4/3}$。

---

## 作者：cyffff (赞：4)

[$\text{Link}$](https://www.luogu.com.cn/problem/P10998)

有意思，记录一下。
## 题意

给出 $m$ 个互不相同的无序三元组 $(u,v,w)$，求有多少无序四元组 $(a,b,c,d)$ 使得三元组 $(a,b,c),(a,b,d),(a,c,d),(b,c,d)$ 均存在。

$m\le 3\times 10^5$。

Bonus：$m\le 2\times 10^6$。
## 题解

回忆无向图三元环计数的做法，使所有边从度数小的点指向度数大的点，其中度数相同的比较编号。此时图形成 DAG，三元环中一个点指向另外两个点，枚举该点 $u$，标记其所有出点，枚举 $u\to v\to w$ 即可。

考虑计算复杂度，令定向后每个点的出度为 $\text{deg}'(u)$：
- 如果 $\text{deg}(u)\le m^{1/2}$，显然 $\text{deg}'(u)\le \text{deg}(u)\le m^{1/2}$。
- 如果 $\text{deg}(u)\ge m^{1/2}$，那么定向后每一个 $u\to v$ 均有 $\text{deg}(v)\ge \text{deg}(u)\ge m^{1/2}$，所以 $\text{deg}'(u)\le m^{1/2}$。

所以 $\text{deg}'(u)\le m^{1/2}$。我们在 $O(m^{3/2})$ 的时间复杂度内枚举到了每一个三元环，同时这也说明了三元环数量的上界。

回到本题，限制为三元组，相对难以处理，我们考虑强制满足一维的限制以化为二维的问题。假如枚举 $a$，则对于所有的三元组 $(a,x,y)$，我们在 $x,y$ 间连边，枚举建出的图上的所有三元环并检查这三点是否包含在同一三元组内即可。时间复杂度 $O(m^{3/2})$。

考虑类似三元环计数的优化：我们令 $\text{deg}(i)$ 表示包含 $i$ 的三元组数量，则我们将每个三元组内部重排使得其 $\text{deg}(u)\le \text{deg}(v)\le \text{deg}(w)$，其中度数相同的比较编号。

考虑计算复杂度，令 $\text{deg}'(u)$ 表示重排后三元组 $(u,x,y)$ 的数量：
- 如果 $\text{deg}(u)\le m^{2/3}$，显然 $\text{deg}'(u)\le \text{deg}(u)\le m^{2/3}$。
- 如果 $\text{deg}(u)\ge m^{2/3}$，那么重排后每一个 $(u,v,w)$ 均有 $\text{deg}(w)\ge\text{deg}(v)\ge \text{deg}(u)\ge m^{2/3}$，所以 $\text{deg}'(u)\le m^{2/3}$。

那么 $\text{deg}'(u)\le m^{2/3}$ 且 $\sum\text{deg}'(u)=m$，复杂度为 $\sum(\text{deg}'(u))^{3/2}$，这在 $\forall i\in[1,m^{1/3}],\text{deg}'(i)=m^{2/3}$ 时取得最大值 $O(m^{4/3})$。

如果本题中三元组变为 $k$ 元组，我们仍可依照类似的方式将其变为 $k-1$ 元组的子问题，时间复杂度可做到 $O(m^{1/k+1})$。

---

## 作者：irris (赞：4)

## Preface

> 图论 / 暴力 / 根号分治

$*1800$，$6.5$。

## Solution

考虑一个 $\mathcal O(\frac{n\min(n, m)}{w})$ 的暴力 A：

- 枚举一个三元组 $(a, b, c)$。
- 将 $(a, b, *)$、$(b, c, *)$、$(a, c, *)$ 对应的 `bitset` 取交集大小得到 $d$ 的个数。

在离散化后可以得到如上能通过 Easy Version 的暴力。

如果我们把一个三元组当做图论中的三元环的话，考虑一个 $\mathcal O(nm)$ 的暴力 B：

- 枚举一条存在的连边 $(u, v)$，这总共只有 $\leq 3m$ 条。
- 对于每个三元组 $(a, b, c)$，若其中包含 $u, v$ 中的
    - $2$ 个，则标记其中的另一个节点；
    - $1$ 个，则标记另外两个节点的连边存在与 $u$（或 $v$）的联系。
- 随后枚举每条连边 $(x, y)$，若 $(x, y)$ 同时与 $u, v$ 有联系且 $x, y$ 均被标记则合法。
- 最终的答案应当除以 $6$。

考虑结合暴力 A 和暴力 B。设 $c_{i, j}$ 表示边 $(i, j)$ 出现的次数。设阈值 $Z$。若 $c_{a, b} \leq Z$ 且 $c_{a, c} \leq Z$ 且 $c_{b, c} \leq Z$，使用暴力 A，并且将对应的 bitset 中的 $1$ 排序后用 $\mathcal O(\text{count})$ 的时间复杂度统计，时间复杂度为 $\mathcal O(m\log m + mZ)$；

否则，枚举所有 $c_{u, v} > Z$ 的边 $(u, v)$，**钦定它在所有 $\bm 6$ 条边中所有出现次数大于 $\bm Z$ 的边中按某顺序是最小的（避免算重）**，施加暴力 B 即可，时间复杂度为 $\mathcal O(\frac{m^2}{Z})$。

取 $Z = \mathcal O(\sqrt m)$，时间复杂度 $\mathcal O(m\sqrt m)$。

## Code

给出一份比较好看的、精细的（无 $\log$）参考实现。

```cpp
#include <bits/stdc++.h>

using pii = std::pair<int, int>;
std::map<pii, int> id;
std::map<int, pii> rid;
#define mp std::make_pair

const int Z = 1000;

#define MAXM 300001
int a[MAXM], b[MAXM], c[MAXM], buc[MAXM], tri[MAXM * 3], cnt[MAXM * 3];
int ida[MAXM], idb[MAXM], idc[MAXM];

struct Node {
	int v, b;
	Node () {}
	Node (int V, int B) : v(V), b(B) {}
	const bool operator < (const Node &k) const { return v < k.v; }
}; std::vector<Node> p[MAXM * 3];
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	int n, m, k = 0, ans = 0; std::cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		std::cin >> a[i] >> b[i] >> c[i];
		if (!id.count(mp(a[i], b[i]))) id[mp(a[i], b[i])] = ++k, rid[k] = mp(a[i], b[i]);
		if (!id.count(mp(a[i], c[i]))) id[mp(a[i], c[i])] = ++k, rid[k] = mp(a[i], c[i]);
		if (!id.count(mp(b[i], c[i]))) id[mp(b[i], c[i])] = ++k, rid[k] = mp(b[i], c[i]);
		ida[i] = id[mp(b[i], c[i])], idb[i] = id[mp(a[i], c[i])], idc[i] = id[mp(a[i], b[i])];
		++cnt[ida[i]], ++cnt[idb[i]], ++cnt[idc[i]], p[idc[i]].push_back(Node(c[i], i));
	} for (int i = 1; i <= k; ++i) std::sort(p[i].begin(), p[i].end());
	for (int i = 1, A, B, C; i <= m; ++i) {
		A = ida[i], B = idb[i], C = idc[i];
		if (cnt[A] > Z || cnt[B] > Z || cnt[C] > Z) continue;
		for (int i = 0, j = 0, k = 0; i < p[A].size() && j < p[B].size() && k < p[C].size(); ++i) {
			while (j < p[B].size() && p[B][j] < p[A][i]) ++j;
			while (k < p[C].size() && p[C][k] < p[A][i]) ++k;
			if (j == p[B].size() || k == p[C].size()) break;
			ans += (int)(p[B][j].v == p[A][i].v && p[C][k].v == p[A][i].v &&
			cnt[ida[p[A][i].b]] <= Z && cnt[idb[p[A][i].b]] <= Z &&
			cnt[ida[p[B][j].b]] <= Z && cnt[idb[p[B][j].b]] <= Z);
		}
	} for (int i = 1, u, v, t, x, y; i <= k; ++i) if (cnt[i] > Z) {
		u = rid[i].first, v = rid[i].second;
		for (int j = 1; j <= m; ++j) 
			 if (a[j] == u && b[j] == v) { if ((cnt[ida[j]] <= Z || ida[j] > i) && (cnt[idb[j]] <= Z || idb[j] > i)) buc[c[j]] = 1; } 
		else if (a[j] == u && c[j] == v) { if ((cnt[ida[j]] <= Z || ida[j] > i) && (cnt[idc[j]] <= Z || idc[j] > i)) buc[b[j]] = 1; }
		else if (b[j] == u && c[j] == v) { if ((cnt[idb[j]] <= Z || idb[j] > i) && (cnt[idc[j]] <= Z || idc[j] > i)) buc[a[j]] = 1; }
		else if (a[j] == u) tri[ida[j]] |= 1;
		else if (b[j] == u) tri[idb[j]] |= 1;
		else if (c[j] == u) tri[idc[j]] |= 1;
		else if (a[j] == v) tri[ida[j]] |= 2;
		else if (b[j] == v) tri[idb[j]] |= 2;
		else if (c[j] == v) tri[idc[j]] |= 2;
		for (auto u : id) {
			t = u.second, x = u.first.first, y = u.first.second;
			ans += (int)(tri[t] == 3 && buc[x] && buc[y] && (t > i || cnt[t] <= Z));
		}
		for (int j = 1; j <= n; ++j) buc[j] = 0;
		for (int j = 1; j <= k; ++j) tri[j] = 0;
	} std::cout << ans << '\n';
	return 0;
}
```

---

## 作者：RiceFruit (赞：3)

提供一个实现简单，常数极小的 $n\sqrt n$ 做法。

+ 根号分治

为了叙述方便，下文认为 $n,m$ 同阶。

## 思路

考虑枚举四元组前两位 $a,b$，设前两个为 $a,b$ 的三元组数量为 $s$，分类讨论：

+ $s<B$ 此时我们先暴力枚举所有合法的 $c$，再枚举所有合法的 $d$，判断即可。复杂度 $\Theta(B^2)$。

+ $s\ge B$ 此时我们考虑枚举所有合法的 $c,d$ 的对，这个最多只有 $n$ 个，判断是否合法即可，复杂度 $\Theta(n)$。

最终复杂度 $(n\cdot B+\dfrac{n^2}{B})\cdot w$，取 $B=\sqrt n$ 可以得到最优复杂度 $\Theta(n\sqrt n\cdot w)$，其中 $w$ 为判断一个三元组是否出现的复杂度，可以 $\Theta(1)$，本人用了 `set`，复杂度 $\Theta(\log n)$，但似乎严重跑不满。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 300300, B = 2025, p = 1000377, base = 103110;
int n, m, ans;
bool apr[p];
set<ll> S;
struct A{
    int a, b, c;
    void rd() {
        scanf("%d%d%d", &a, &b, &c);
        long long ans = 1ll * a * base * base + 1ll * b * base + c;
        S.insert(ans);
        return;
    }
    bool operator<(const A &_)const{
        if (a != _.a) return a < _.a;
        if (b != _.b) return b < _.b;
        return c < _.c;
    }
} a[N];
bool fid(int a, int b, int c) {
    return S.find(1ll * a * base * base + 1ll * b * base + c) != S.end();
}
bool ok(int a, int b, int c, int d) {
    return 1 <= a && a < b && b < c && c < d && d <= n;
}
vector<int> s[N];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) a[i].rd();
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; ++i) s[a[i].a].push_back(i);
    for (int i = 1, la = -1, lb = -1; i <= m; ++i) {
        la = a[i].a, lb = a[i].b;
        int j = i;
        while (j < m && a[j + 1].a == la && a[j + 1].b == lb) ++j;
        if (j - i + 1 < B) {
            vector<int> cd;
            for (int k = j - 1; k >= i; --k) {
                cd.push_back(a[k + 1].c);
                for (int x : cd)
                    if (fid(la, a[k].c, x) && fid(lb, a[k].c, x) && ok(la, lb, a[k].c, x)) ++ans;
            }
        }
        else {
            for (int id : s[la]) {
                if (fid(lb, a[id].b, a[id].c) && fid(la, lb, a[id].b) && fid(la, lb, a[id].c) && ok(la, lb, a[id].b, a[id].c)) ++ans;
            }
        }
        i = j;
    }
    cout << ans;
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：2)

## 思路分析

可以先看[这篇](https://www.luogu.com.cn/article/wiqb3sny)题解。

最核心的，也能用到这里的是这几句：

> 所以这时候，我们考虑换一种记录方式：对于 $u_i,v_i$，有哪些 $w_i$。这个东西可以用 `set` 维护。\
> 但是还有问题，这样做最极限情况下仍然会把前面的点枚举完，复杂度退化为类似于哈希做法。\
> 其实，我们发现我们就是在枚举其中一个的点，验证另外两个中有没有。显然，我们如果枚举大小最小的那个，时间复杂度会更优。

在这里我们只需要做一个小修改：因为哈希值太大了，所以我们直接用 `unordered_map` 代替数组，并在更改前使用常引用来降低复杂度。依旧能卡过此题。

证明一下复杂度。

首先我们假定出题人没有卡 `unordered_map`，因此视其复杂度为常数。如果卡了可以用原始类型替换质数表。

这个东西的复杂度在所有的值都尽可能地重复的时候被卡满。那么其中元素最少的最多时会有多少个元素呢？

容易发现，当取 $1,2,3$，并且以此增量进行构造时能最大化每一个元素对对应的元素个数。此时对应最少的就是 $(2,3)$。当每新增一个数 $x$ 时，都只与 $(2,3)$ 增加一个三元组，而他仍需要寻找相同个数的其他对来保证自己大小足够。不难发现，这样子的最大复杂度为 $O(m^\frac{4}{3})$。完全图可以卡满。注意带个 $\log$。

复杂度证毕。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#ifdef _WIN32
#define getchar_unlocked getchar
#define putchar_unlocked putchar
#endif
inline int read() {
	int r = 0; char c = getchar_unlocked();
	while (c < '0' || c>'9') c = getchar_unlocked();
	while (c >= '0' && c <= '9') r = r * 10 + (c ^ 48), c = getchar_unlocked();
	return r;
}
int n,m,ans; unordered_map<long long,set<int>>v; set<int>::iterator it;
inline long long gh(const int&a,const int&b){
	return (long long)a*n+b;
}
signed main(){
	n=read(); m=read();
	for(int i=1,l,r,x;i<=m;++i){
		l=read(); r=read(); x=read();
		const set<int>&va=v[gh(l,r)];
		int sa=va.size();
		const set<int>&vb=v[gh(l,x)];
		int sb=vb.size();
		const set<int>&vc=v[gh(r,x)];
		int sc=vc.size();
		if(sa<=sb&&sa<=sc)
			for(it=va.begin();it!=va.end();++it){
				if(vb.count(*it)&&vc.count(*it)) ans++;
			}
		else if(sb<=sa&&sb<=sc)
			for(it=vb.begin();it!=vb.end();++it){
				if(va.count(*it)&&vc.count(*it)) ans++;
			}
		else
			for(it=vc.begin();it!=vc.end();++it){
				if(vb.count(*it)&&va.count(*it)) ans++;
			}
		v[gh(l,r)].insert(x);
		v[gh(l,x)].insert(r);
		v[gh(r,x)].insert(l);
	}
	cout<<ans<<endl;
} 
```

时间复杂度写全：$O(m^\frac{4}{3}\log \sqrt[3]{m})$。对应到极限数据大约为 $1.2\times10^8$，很极限了，但是可以卡过。希望审核通过，也真心希望不要再把我这篇题解莫名的给撤了。

---

## 作者：SCma (赞：1)

# 游记

因为蓝桥杯而迟到 2 小时才参加的比赛，其实我也没想到能够切一道蓝题的，挺开心的。

---

# 原 T3 $\texttt{48pts}$ 做法

**观察样例**：
对于四元组 $(a,b,c,d)\ (a<b<c<d)$，按照字典序排序有如下组合：
1. $(a, b, c)$
2. $(a, b, d)$
3. $(a, c, d)$
4. $(b, c, d)$

**思路分析**：  
枚举的关键在于利用 $u$（即 $a$），记录每个 $u$ 对应的 $v,w$ 值，枚举 $d$ 即可得到 $\texttt{48pts}$ 的做法。具体实现时通过哈希表记录三元组的存在性。

**代码实现**：
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define MIN(a,b,c) min(min(a,b),c)
#define MAX(a,b,c) max(max(a,b),c)
#define ri register int
#define int long long
#define fixedset(a) fixed << setprecision(a)
#define ls(x) x<<1
#define rs(x) x<<1|1
#define MAXN 9.2211e18
#define inf 2114514
#define mf 5011
#define sf 1011
using namespace std;
mt19937_64 randint{std::chrono::steady_clock::now().time_since_epoch().count()};
int n,m,index_,ans,pos[inf];
vector<pair<int,int> > num[inf];
map<int,bool> tik; 
map<int,int> Isappeared;
bool check(int x,int y,int z){return tik[x*mf*mf*sf+y*mf*sf+z];}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//freopen(".in","r",stdin);
   	//freopen(".out","w",stdout);

	cin >> n >> m;
	for(ri i=1;i<=m;i++){
		int a,b,c;
		cin >> a >> b >> c;
		num[a].push_back(make_pair(b,c));
		tik[a*mf*mf*sf+b*mf*sf+c]++; 
		Isappeared[a]++;
		if(Isappeared[a]==3) pos[++index_]=a; 
	}
	
	for(ri i=1;i<=index_;i++){
		for(ri j=0;j<num[pos[i]].size();j++){
			int a=pos[i],b=num[pos[i]][j].first,c=num[pos[i]][j].second;
			for(ri d=c+1;d<=n;d++) if(check(a,b,c) && check(a,b,d) && check(a,c,d) && check(b,c,d)) ans++;
		}
	}
	
	cout << ans << endl;
	return 0;
}
```

---

# 正解

**优化思路**：  
通过减少 $d$ 的枚举次数，选择以 $(u,v)$ 为前缀中三元组数量最少的部分进行枚举。具体实现时对每个 $(a,b,c)$ 筛选出对应的最小候选集。

**代码实现**：
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define MIN(a,b,c) min(min(a,b),c)
#define MAX(a,b,c) max(max(a,b),c)
#define ri register int
#define int long long
#define fixedset(a) fixed << setprecision(a)
#define ls(x) x<<1
#define rs(x) x<<1|1
#define MAXN 9.2211e18
#define inf 2114514
#define mf 50111
#define sf 101
using namespace std;
mt19937_64 randint{std::chrono::steady_clock::now().time_since_epoch().count()};
int n,m,index_,ans,pos[inf];
vector<pair<int,int> > num[inf];
map<int,vector<int>  > num1;
map<int,bool> tik; 
map<int,int> Isappeared;
bool check(int x,int y,int z){return tik[x*mf*mf*sf+y*mf*sf+z];}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//freopen(".in","r",stdin);
   	//freopen(".out","w",stdout);

	cin >> n >> m;
	for(ri i=1;i<=m;i++){
		int a,b,c;
		cin >> a >> b >> c;
		num[a].push_back(make_pair(b,c));
		num1[a*mf*mf*sf+b*mf*sf].push_back(c);
		tik[a*mf*mf*sf+b*mf*sf+c]++;
		Isappeared[a]++;
		if(Isappeared[a]==3) pos[++index_]=a;
	}
	
	for(ri i=1;i<=index_;i++){
		for(ri j=0;j<num[pos[i]].size();j++){
			int index__=0;
			int a=pos[i],b=num[pos[i]][j].first,c=num[pos[i]][j].second;
			int tmp=MIN(num1[a*mf*mf*sf+c*mf*sf].size(),num1[a*mf*mf*sf+b*mf*sf].size(),num1[b*mf*mf*sf+c*mf*sf].size());
			if(tmp==num1[a*mf*mf*sf+c*mf*sf].size()) index__=a*mf*mf*sf+c*mf*sf;
			else if(tmp==num1[a*mf*mf*sf+b*mf*sf].size()) index__=a*mf*mf*sf+b*mf*sf;
			else if(tmp==num1[b*mf*mf*sf+c*mf*sf].size()) index__=b*mf*mf*sf+c*mf*sf;
			for(ri k=0;k<tmp;k++){
				int d=num1[index__][k];
				if(check(a,b,c) && check(a,b,d) && check(a,c,d) && check(b,c,d)) ans++;
			}
		}
	}
	
	cout << ans << endl;
	return 0;
}
```

**提交记录**：[$\texttt{Link}$](https://www.luogu.com.cn/record/174699581)

---

## 作者：Supor__Shoep (赞：1)

一个比较自然的思路就是对于每个三元组 $(u_i,v_i,w_i)$，把 $(v_i,w_i)$ 这个二元组放在属于 $u_i$ 的 vector 里面。然后对于每一个 $i\in [1,n-3]$，把 $i$ 的 vector 里面的所有二元组 $(x,y)$ 当作一条连接 $x,y$ 的无向边，则我们的目的是在图中找出所有的三元环 $(p_1,p_2,p_3)$，如果这个三元组被给出了，我们就让它与 $i$ 组成一个合法的四元组 $(i,p_1,p_2,p_3)$（$i<p_1<p_2<p_3$）。

无向图找三元环的话就是一个比较模板的题目了。我们考虑给每条无向边定向，对于 $(x,y)$ 这条边，设 $d_i$ 表示 $i$ 的度数，若 $d_x>d_y$ 或者 $d_x=d_y\wedge x>y$，我们就定向为 $x\to y$。

然后我们就枚举每一个点 $x$，然后枚举 $x$ 指向的某个点 $y$，再枚举 $y$ 指向的另一个点 $z$，若 $(x,z)$ 存在连边，则 $(x,y,z)$ 构成一个三元环。时间复杂度可以分类讨论证明一下：设边数为 $M$，若 $d_x\leq \sqrt{M}$，则 $d_z\leq d_y\leq d_x\leq \sqrt{M}$，那么此次枚举就是 $O(\sqrt{M})$ 的；若 $d_x>\sqrt{M}$，则此次枚举最劣是 $O(M)$ 的，而度数大于 $\sqrt{M}$ 的点最多只有 $\sqrt{M}$ 个，所以综合起来的复杂度就是 $O(M\sqrt{M})$。

由此，我们可以在规定的时间内找出所有的三元环，接着判一下每个三元环是否被给出即可。这里最好是先找完所有三元环，然后再一次性的挨个判断，不然判断时的 $O(\log m)$ 可能会堆积在 $O(M\sqrt{M})$ 这个时间复杂度上。

对于我们枚举的 $i$，设其 vector 中存了 $M_i$ 条边，则有 $\sum M_i=m$，我们的总时间复杂度为 $O(\sum M_i\sqrt{M_i})$。

> 结论：$a\sqrt{a}+b\sqrt{b}<(a+b)\sqrt{a+b}$，其中 $a,b>0$。
>
> 证明：将两边同时平方可得 $a^3+b^3+2ab\sqrt{ab}<a^3+b^3+3ab^2+3a^2b$。去掉相同项就能化简为 $\sqrt{ab}<1.5(a+b)$，根据均值不等式 $a+b\geq 2\sqrt{ab}$ 即可证明 $\sqrt{ab}<1.5(a+b)$ 成立。

拓展一下这个结论可以知道 $\sum M_i\sqrt{M_i}< (\sum M_i)\sqrt{\sum M_i}=m\sqrt{m}$。因此我们的最劣时间复杂度为 $O(m\sqrt{m})$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=3e5+5;
int n,m;
int u[MAXN],v[MAXN],w[MAXN];
vector<pair<int,int> > vec[MAXN];
int stk[MAXN<<1],cnt;
int in[MAXN];
int head[MAXN],nxt[MAXN<<1],to[MAXN<<1],tot;
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
vector<int> v1[MAXN];
int vis[MAXN];
map<pair<pair<int,int>,int>,int> mp;
vector<pair<pair<int,int>,int> > temp;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)	cin>>u[i]>>v[i]>>w[i],vec[u[i]].push_back(make_pair(v[i],w[i]));
	int res=0;
	for(int s=1;s<=n-3;s++)
	{
		if(!vec[s].size())	continue;
		cnt=0,tot=0;
		for(auto j:vec[s])	stk[++cnt]=j.first,stk[++cnt]=j.second,add(j.first,j.second),add(j.second,j.first);
		for(auto j:vec[s])	in[j.first]++,in[j.second]++;
		sort(stk+1,stk+cnt+1),cnt=unique(stk+1,stk+cnt+1)-stk-1;
		for(int i=1;i<=cnt;i++)
		{
			for(int j=head[stk[i]];j;j=nxt[j])
			{
				if(in[stk[i]]>in[to[j]]||in[stk[i]]==in[to[j]]&&stk[i]>to[j])	v1[stk[i]].push_back(to[j]);
			}
		}
		temp.clear();
		for(int i=1;i<=cnt;i++)
		{
			for(int j:v1[stk[i]])	vis[j]=1;
			for(int j:v1[stk[i]])
			{
				for(int k:v1[j])
				{
					if(vis[k])	temp.push_back(make_pair(make_pair(stk[i],j),k));
				}
			}
			for(int j:v1[stk[i]])	vis[j]=0;
		}
		for(auto j:temp)
		{
			if(j.first.first>j.first.second)	swap(j.first.first,j.first.second);
			if(j.first.second>j.second)	swap(j.first.second,j.second);
			if(j.first.first>j.first.second)	swap(j.first.first,j.first.second);
			mp[j]++;
		}
		for(int i=1;i<=cnt;i++)	head[stk[i]]=0,in[stk[i]]=0,v1[stk[i]].clear();
	}
	for(int i=1;i<=m;i++)	res+=mp[make_pair(make_pair(u[i],v[i]),w[i])];
	cout<<res;
	return 0;
}
```

---

## 作者：liangbowen (赞：0)

[blog](https://www.cnblogs.com/liangbowen/p/18424606)。获得题解区最劣复杂度做法（

---

对于这种三元环（？）的样子的题，直接考虑**根号分治**。

考虑枚举 $(a,b)$，假设 $u=a,v=b$ 的三元组有 $S$ 个，根号分治：

+ $S\le B$，暴力从 $S$ 个里面选两个作为 $c,d$，暴力检验，$O(S^2)$。
+ $S>B$，由于条件要求存在 $(a,c,d)$，于是可能的 $c,d$ 只有 $O(m)$ 个，暴力检验，$O(m)$。

注意到情况二最多出现 $O(\dfrac mB)$ 个，于是有总复杂度 $O(mB^2+\dfrac{m^2}B)$，取 $B=\sqrt[3]m$ 做到 $O(m^{5/3})$。

由于根号分治比较难卡，所以根本跑不满，勉强过了。

[code](https://www.luogu.com.cn/paste/oivkfh61)，时间复杂度 $O(m^{5/3})$，代码中取 $B=70$。

---

## 作者：hhhqx (赞：0)

## 转化问题
这题给的条件都很和善，确认一下有没有漏条件：

- 三元组两两不同。
- $1 \le u_i < v_i < w_i \le n$。
- $1 \le a < b < c < d \le n$。

可以先找到一个三元组钦定其为 $(a, b, c)$，问题变为快速求合法的 $d$ 的个数。

设满足 $u_i = x$ 且 $v_i = y$ 的所有 $i$ 对应的所有 $w_i$ 构成一个集合，设这个几何为 $S(x, y)$。

则问题变为求 $S(a, b)$ 和 $S(a, c)$ 和 $S(b, c)$ 的交集中大于 $c$ 的元素个数。

## 初步做法

现在就有了一个用 `bitset` 的做法了。预处理出每个集合，接着枚举出 $(a, b, c)$ 直接用 `&` 运算求出集合大小（至于元素大于 $c$ 这个限制，可以再 `&` 上一个 $c + 1$ 到 $n$ 都为 $1$ 的 `bitset`）。但是这样复杂度 $O(\frac{nm}{w})$ 跑不过。

## 正确做法

发现每个集合的大小之和小于等于 $m$，考虑根号分治。

对于 $S(a, b)$ 和 $S(a, c)$ 和 $S(b, c)$ 中最小的集合大小，如果是小于等于 $B$，则可以暴力算，但是要用一个 `set`，复杂度 $O(mB \log m)$。如果是大于 $B$，就可以用初步做法来做，只不过预处理的时候只用预处理至多 $\frac{m}{B}$ 个，空间复杂度 $O(\frac{nm}{Bw})$ 时间复杂度 $O(\frac{m^2}{Bw})$。

最后复杂度 $O(mB \log m + \frac{m^2}{Bw})$，空间复杂度 $O(\frac{nm}{Bw})$，$B$ 大概可以取 $500$。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using PII = pair<int, int>;

const int MAXN = 3e5 + 3, B = 500;

struct Node{
  int x, y, z, p;
}a[MAXN];

int n, m, k = 0, __sz[MAXN], _p[MAXN];
map<PII, int> mp;
map<int, int> _mp;
set<int> sz[MAXN];
int id[4];
bitset<MAXN> _sz[700];

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  vector<PII> p;
  for(int i = 1; i <= m; i++){
    cin >> a[i].x >> a[i].y >> a[i].z;
    p.push_back({a[i].x, a[i].y});
  }
  sort(p.begin(), p.end());
  for(int i = 0; i < p.size(); i++){ // 离散化 pair
    if(i == 0 || p[i] != p[i - 1]) mp[p[i]] = ++k, _p[k] = k;
  }
  for(int i = 1; i <= m; i++) a[i].p = mp[{a[i].x, a[i].y}], __sz[a[i].p]++;

  sort(_p + 1, _p + 1 + k, [](int i, int j){ return __sz[i] > __sz[j]; }); // 按大小排序 且 重编编号
  for(int i = 1; i <= k; i++) _mp[_p[i]] = i;

  for(int i = 1; i <= m; i++){ // 添加
    a[i].p = _mp[a[i].p], sz[a[i].p].insert(a[i].z);
  }
  for(int i = 1; i <= m; i++){
    if(sz[a[i].p].size() > B) _sz[a[i].p].set(a[i].z);
  }

  sort(a + 1, a + 1 + m, [](Node i, Node j){ return i.z > j.z; }); // 排序

  bitset<MAXN> st; // 处理查询
  LL ans = 0;
  for(int i = 1, j = n; i <= m; i++){
    while(j > a[i].z) st.set(j), j--; // 用来剩空间
    PII xx = {a[i].x, a[i].y}, yy = {a[i].x, a[i].z}, zz = {a[i].y, a[i].z};
    if(mp.find(xx) == mp.end() || mp.find(yy) == mp.end() || mp.find(zz) == mp.end()) continue;
    id[0] = _mp[mp[xx]], id[1] = _mp[mp[yy]], id[2] = _mp[mp[zz]];
    sort(id, id + 3, [](int i, int j){ return sz[i].size() < sz[j].size(); });

    if(sz[id[0]].size() <= B){
      for(int x : sz[id[0]]){
        if(x <= a[i].z) continue;
        ans += sz[id[1]].find(x) != sz[id[1]].end() && sz[id[2]].find(x) != sz[id[2]].end();
      }
    }else{
      ans += (_sz[id[0]] & _sz[id[1]] & _sz[id[2]] & st).count();
    }
  }
  cout << ans;
  return 0;
}
```

---

