# [ABC346G] Alone

## 题目描述

给定一个整数序列 $A = (A_1, A_2, \ldots, A_N)$。

请计算满足以下条件的整数对 $(L, R)$ 的个数：

- $1 \leq L \leq R \leq N$。
- 在 $A_L, A_{L+1}, \ldots, A_R$ 中，存在某个只出现一次的数。更严格地说，存在某个整数 $x$，使得 $A_i = x$ 且 $L \leq i \leq R$ 的 $i$ 恰好有 $1$ 个。

## 说明/提示

## 限制条件

- $2 \leq N \leq 2 \times 10^5$
- $1 \leq A_i \leq N$
- 输入的所有值均为整数

## 样例解释 1

满足条件的整数对 $(L, R)$ 有 $12$ 个，分别为 $(1, 1), (1, 3), (1, 4), (2, 2), (2, 3), (2, 4), (3, 3), (3, 4), (3, 5), (4, 4), (4, 5), (5, 5)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
2 2 1 2 1```

### 输出

```
12```

## 样例 #2

### 输入

```
4
4 4 4 4```

### 输出

```
4```

## 样例 #3

### 输入

```
10
1 2 1 4 3 3 3 2 2 4```

### 输出

```
47```

# 题解

## 作者：Lotus_Land (赞：13)

### 题意

给定一个整数序列 $A=(A_1,A_2,\dots,A_N)$。

找出满足以下条件的整数对 $(L,R)$ 的数量：

- $1\leq L\leq R \leq N$。
- 在 $A$ 的子序列 $A_L,A_{L+1},\dots,A_R$ 中，有一个数恰好出现一次。
  更确切地说，存在一个整数 $x$，恰好有一个整数 $i$ 满足 $A_i=x$ 且 $L\leq i\leq R$。

### 分析

要枚举区间肯定是不行的，我们可以试试先枚举区间中的唯一整数。

对于每个 $A_i$，如果它在 $A_L,A_{L+1},\dots,A_R$ 中只出现一次，那么 $A_L,A_{L+1},\dots,A_{i-1}$ 与 $A_{i+1},A_{i+2},\dots,A_R$ 都不等于 $A_i$。设 $l_i$ 为满足此条件的最小 $L$， $r_i$ 为满足此条件的最大 $R$，则由乘法原理可得  $A_i$ 对答案的贡献为 $(i-l_i+1)\times(r_i-i+1)$。

$l_i$ 与 $r_i$ 的求法：

```cpp
for(int i=1; i<=n; i++) {
	l[i]=mp[a[i]]+1;
	mp[a[i]]=i;
}
mp.clear();
for(int i=n; i>=1; i--) {
	if(mp[a[i]])r[i]=mp[a[i]]-1;
	else r[i]=n;
	mp[a[i]]=i;
}
```

但这样很明显会重复统计，因为一个区间中可能有多个数只出现了一次。如何去重？

发现求答案就是求 $N$ 个左下角为 $(l_i,i)$，右上角为 $(i,r_i)$ 的矩形的面积并。用扫描线做就好了。

```cpp
#include<bits/stdc++.h>
#define lc(p) ((p)*2)
#define rc(p) ((p)*2+1)
#define mkpr make_pair
#define LL long long
using namespace std;
inline LL read() {
	char ch=getchar();
	LL x=0;
	bool t=0;
	while(ch<'0'||ch>'9')   t|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return t?-x:x;
}
int n,a[200005],l[200005],r[200005];
map<int,int>mp;
LL ans;
struct Edge{
	int ll,rr,hh,ff;
}e[200005<<1];
int edgecnt,cnt;
void add_edge(int l,int r,int h,int f){
	e[++edgecnt].ll=l;
	e[edgecnt].rr=r;
	e[edgecnt].hh=h;
	e[edgecnt].ff=f;
}
bool cmp(Edge a,Edge b){
	if(a.hh==b.hh)return a.ff>b.ff;
	return a.hh<b.hh; 
}
struct Tree{
	int sum,len;
}tr[200005<<2];
void pushup(int p,int l,int r){
	if(tr[p].sum) tr[p].len=r-l+1;
	else if(l==r)tr[p].len=0;
	else tr[p].len=tr[lc(p)].len+tr[rc(p)].len;
}
void modify(int p,int l,int r,int ql,int qr,int val){
	if(ql<=l&&r<=qr){
		tr[p].sum+=val;
		pushup(p,l,r);
		return ;
	}
	int mid=(l+r)>>1;
	if(ql<=mid)modify(lc(p),l,mid,ql,qr,val);
	if(qr>mid)modify(rc(p),mid+1,r,ql,qr,val);
	pushup(p,l,r);
}
int main() {
	cin>>n;
	for(int i=1; i<=n; i++)cin>>a[i];
	for(int i=1; i<=n; i++) {
		l[i]=mp[a[i]]+1;
		mp[a[i]]=i;
	}
	mp.clear();
	for(int i=n; i>=1; i--) {
		if(mp[a[i]])r[i]=mp[a[i]]-1;
		else r[i]=n;
		mp[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		add_edge(i,r[i]+1,l[i],1);
		add_edge(i,r[i]+1,i+1,-1);
	}
	sort(e+1,e+1+edgecnt,cmp);
	for(int i=1;i<edgecnt;i++){
		modify(1,1,n+1,e[i].ll,e[i].rr-1,e[i].ff);
		ans+=1ll*tr[1].len*(e[i+1].hh-e[i].hh);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：forgotmyhandle (赞：5)

唉。比赛最后五分钟才过 F，然后一分钟把这题秒了。可是没时间写了。赛后实现了一下，一发过。唉。

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc346_g)

[原题传送门](https://atcoder.jp/contests/abc346/tasks/abc346_g)

## 分析
记 $pos_{i, j, k}$ 表示 $i$ 在 $j$ 及其右边出现第 $k$ 次的位置。

我们考虑枚举左端点 $l$，数一数合法右端点的个数。题目说要存在只出现一次的数，那我们随便考虑一个数 $x$，看右端点 $r$ 符合什么条件时 $x$ 在 $[l, r]$ 内只出现一次。显然当且仅当 $r \in [pos_{x, l, 1}, pos_{x, l, 2})$ 时符合要求。如果再往左，则 $x$ 不会出现。若再往右，则 $x$ 会出现至少两次。因此 $x$ 对 $l$ 提供的合法右端点区间为 $[pos_{x, l, 1}, pos_{x, l, 2} - 1]$。既然题目要求至少有一个 $x$ 符合要求，那我们就把所有数提供的合法区间求一个并集，这样就得到对于一个 $l$ 来说所有合法的右端点集合。

接下来我们考虑对这个并集进行一个维护。我们要在每次 $l$ 往右走之后求出新的并集。可以发现 $l$ 每次往右，都有且仅有一个值给 $l$ 贡献的区间会发生变化，这个值就是 $a_l$。$a_l$ 这个值给 $l$ 贡献的区间会从 $[l, pos_{l, a_l, 2}]$ （注意到 $l$ 即为 $pos_{l, a_l, 1}$）变为 $[pos_{l, a_l, 2}, pos_{l, a_l, 3}]$，也就是类似于往后移了一个区间。所以我们只需要在一开始搞出所有 $pos_{1, x, k}$，然后再搞出最初的并集，然后每次 $l$ 往右走时都换一下 $a_l$ 的贡献区间即可。

然后发现这个并集大小的维护实际上是要我们支持区间加 / 减，查询区间非 $0$ 数个数，同时保证任意时刻所有数非负。于是直接把扫描线维护矩形面积并的线段树拿过来即可。具体地，维护区间内最小值及其个数，查询时若区间最小值为 $0$，则返回区间长度减去最小值个数，否则返回区间长度。这样就做完了。

总时间复杂度 $\mathcal{O}(n \log n)$。

## 代码
```cpp
#include <iostream>
#include <vector>
#define int long long
using namespace std;
int n;
int a[200005];
vector<int> pos[200005];
struct Segment_Tree {
    int mn[800005], mcnt[800005], tg[800005];
    void tag(int o, int v) {
        mn[o] += v;
        tg[o] += v;
    }
    void pushdown(int o) {
        if (!tg[o]) 
            return;
        tag(o << 1, tg[o]);
        tag(o << 1 | 1, tg[o]);
        tg[o] = 0;
    }
    void pushup(int o) {
        if (mn[o << 1] < mn[o << 1 | 1]) 
            mn[o] = mn[o << 1], mcnt[o] = mcnt[o << 1];
        else if (mn[o << 1] > mn[o << 1 | 1]) 
            mn[o] = mn[o << 1 | 1], mcnt[o] = mcnt[o << 1 | 1];
        else 
            mn[o] = mn[o << 1], mcnt[o] = mcnt[o << 1] + mcnt[o << 1 | 1];
    }
    void Build(int o, int l, int r) {
        mcnt[o] = r - l + 1;
        if (l == r) 
            return;
        int mid = (l + r) >> 1;
        Build(o << 1, l, mid);
        Build(o << 1 | 1, mid + 1, r);
    }
    void Add(int o, int l, int r, int L, int R, int v) {
        if (L <= l && r <= R) {
            tag(o, v);
            return;
        }
        pushdown(o);
        int mid = (l + r) >> 1;
        if (L <= mid) 
            Add(o << 1, l, mid, L, R, v);
        if (R > mid) 
            Add(o << 1 | 1, mid + 1, r, L, R, v);
        pushup(o);
    }
    int Query(int o, int l, int r, int L, int R) {
        if (R < L) 
            return 0;
        if (L <= l && r <= R) 
            return (mn[o] == 0 ? mcnt[o] : 0);
        pushdown(o);
        int mid = (l + r) >> 1;
        if (R <= mid) 
            return Query(o << 1, l, mid, L, R);
        if (L > mid) 
            return Query(o << 1 | 1, mid + 1, r, L, R);
        return Query(o << 1, l, mid, L, R) + Query(o << 1 | 1, mid + 1, r, L, R);
    }
} seg;
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], pos[i].emplace_back(1);
    for (int i = 1; i <= n; i++) pos[a[i]].emplace_back(i);
    for (int i = 1; i <= n; i++) pos[i].emplace_back(n + 1), pos[i].emplace_back(n + 2);
    seg.Build(1, 1, n + 2);
    for (int i = 1; i <= n; i++) seg.Add(1, 1, n + 2, pos[i][1], pos[i][2] - 1, 1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int tmp = seg.Query(1, 1, n + 2, i, n);
        ans += (n - i + 1 - tmp);
        seg.Add(1, 1, n + 2, pos[a[i]][pos[a[i]][0]], pos[a[i]][pos[a[i]][0] + 1] - 1, -1);
        pos[a[i]][0]++;
        seg.Add(1, 1, n + 2, pos[a[i]][pos[a[i]][0]], pos[a[i]][pos[a[i]][0] + 1] - 1, 1);
    }
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：TankYu (赞：5)

跟 std 相似的思路，但有所不同。

考虑转化原问题，对每个 $a_i$，找到对应的 $L_i,R_i$，使得 $A_{L_i},A_{L_i + 1},\cdots,A_{R_i}$ 中 $A_i$ 恰出现一次。

因为值域很小，这个只需记录 $A_i$ 左右的上一次出现位置即可。

然后对 $\forall i$，取 $\forall l \in \left[L_i,i\right]$，$r \in \left[i,R_i\right]$，则 $(l,r)$ 是合法的。

那么接下来就是考虑去重的问题。

注意到这个东西长得非常像区间向区间连边，不妨考虑 DS 优化建图，由于是两个区间能想到线段树，考虑线段树优化建图的基本套路，在一棵树上把区间拆开在连到一个虚点。

然后注意到计算只需要一棵树的叶子能到达的点数之和，所以一棵树就可以，那么在线段树上可以直接每个点维护一个 set，然后暴力插入区间。

因为区间一共就 $n$ 个，一个区间在线段树上至多拆成 $\log n$ 个区间，所以 set 暴力维护区间的合并没有问题，每次合并，都至少使区间总数少 $1$，所以复杂度为 $O(n\log(n \log n))$。

查询的时候，遍历线段树的叶子，然后一路走到根，把上面所有区间并起来，遍历线段树的复杂度是 $O(n \log n)$，维护集合的复杂度为 $O(n \log n)$，这是因为一个叶子最多到 $n$ 个点。

赛后 $10$ 分钟调出来的，比较火大。

```cpp
#define LL long long
#define fi first
#define se second
#define mp make_pair
using namespace std;

struct node
{
    int l;
    int r;
    set<pair<int, int>> s;
} t[200010 << 2];

int L[200010], R[200010];
int lst[200010];
int a[200010];

void build(int rt, int l, int r)
{
    t[rt].l = l, t[rt].r = r;
    if (l == r)
    {
        return;
    }
    int mid = (l + r) / 2;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    return;
}

int match_l, match_r;

void link(int rt, int l, int r)
{
    t[rt].s.insert(mp(l, r));
    int nl = l, nr = r;
    for (auto i = t[rt].s.find(mp(l, r)); i != t[rt].s.begin();)
    {
        auto it = i;
        it--;
        if (it->second >= i->first)
        {
            nl = it->first, nr = max(i->second, it->second);
            t[rt].s.erase(i);
            t[rt].s.erase(it);
            t[rt].s.insert(mp(nl, nr));
            i = t[rt].s.find(mp(nl, nr));
        }
        else
        {
            break;
        }
    }
    std::set<std::pair<int, int>>::iterator i = t[rt].s.find(mp(nl, nr)), it;
    it = i;
    it++;
    for (; it != t[rt].s.end();)
    {
        if (i->second >= it->first)
        {
            nl = i->first, nr = max(i->second, it->second);
            t[rt].s.erase(i);
            t[rt].s.erase(it);
            t[rt].s.insert(mp(nl, nr));
            i = t[rt].s.find(mp(nl, nr));
            it = i;
            it++;
        }
        else
        {
            break;
        }
    }
}

void match(int rt, int l, int r)
{
    if (l <= t[rt].l && t[rt].r <= r)
    {
        link(rt, match_l, match_r);
        return;
    }
    int mid = (t[rt].l + t[rt].r) / 2;
    if (l <= mid)
    {
        match(rt << 1, l, r);
    }
    if (r > mid)
    {
        match(rt << 1 | 1, l, r);
    }
    return;
}

void find(int rt, int x)
{
    for (auto i : t[rt].s)
    {
        link(0, i.fi, i.se);
    }
    if (t[rt].l == t[rt].r)
    {
        return;
    }
    int mid = (t[rt].l + t[rt].r) / 2;
    if (x <= mid)
    {
        find(rt << 1, x);
    }
    else
    {
        find(rt << 1 | 1, x);
    }
    return;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        lst[i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        L[i] = lst[a[i]] + 1;
        lst[a[i]] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        lst[i] = n + 1;
    }
    for (int i = n; i >= 1; i--)
    {
        R[i] = lst[a[i]] - 1;
        lst[a[i]] = i;
    }
    build(1, 1, n);
    for (int i = 1; i <= n; i++)
    {
        match_l = i, match_r = R[i];
        match(1, L[i], i);
    }
    LL ans = 0;
    for (int i = 1; i <= n; i++)
    {
        t[0].s.clear();
        find(1, i);
        for (auto i : t[0].s)
        {
            ans += i.se - i.fi + 1;
        }
    }
    cout << ans;
    return 0;
}
```

---

