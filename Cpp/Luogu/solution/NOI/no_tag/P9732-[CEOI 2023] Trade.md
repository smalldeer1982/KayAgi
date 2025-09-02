# [CEOI 2023] Trade

## 题目背景

译自 CEOI2023 Day2 T1 [Trade](https://www.ceoi2023.de/wp-content/uploads/2023/09/4-trade.pdf)。

## 题目描述

有 $n$ 个机器人排成一排，第 $i$ 个机器人的购买价是 $c_i$ 欧元，卖出价是 $s_i$ 欧元。

给定 $1\le k\le n$，你需要购买一段长度至少为 $k$ 的区间中所有的机器人，然后选择其中的恰好 $k$ 个机器人来卖出。

你需要求出：
1. 你能够得到的最大收益；
2. 在收益最大化的前提下，哪些机器人可以在某种最优方案中被卖出。

## 说明/提示

样例一中最优方案是购买第 $3\sim 5$ 个机器人然后将它们卖出，但仍然会亏损 $1$ 欧元。

样例二中最大收益为 $2$ 欧元，可以购买 $1,2,3$ 并卖出 $1,3$，也可以购买 $3,4$ 并卖出 $3,4$，也可以购买 $3,4,5$ 并卖出 $3,5$，因此 $1,3,4,5$ 都有可能在某种最优方案中被卖出，输出 `10111`。

### 数据规模与约定

对于全部数据，$1\le k\le n \le 250000$，$1\le c_i,s_i\le 10^9$。

- Subtask 1（5+5 points）：$n \le 200$。
- Subtask 2（5+5 points）：$n \le 6000$。
- Subtask 3（5+5 points）：$k=2$。
- Subtask 4（10+15 points）：$k\le 200$。
- Subtask 5（25+20 points）：无特殊限制。

在每个子任务中，如果第一行的输出正确，可以获得子任务前半部分的分数，如果第二行的输出也正确，可以获得子任务全部的分数。

## 样例 #1

### 输入

```
5 3
3 5 2 3 6
2 1 5 2 3```

### 输出

```
-1
00111```

## 样例 #2

### 输入

```
5 2
1 6 1 5 2
4 1 6 2 4```

### 输出

```
2
10111```

# 题解

## 作者：AzusagawaKaede (赞：14)

一道有点奇怪思路的题.

考虑第一问，容易发现要选出一个长度不小于 $k$ 的区间，最大化 区间前 $k$ 大 $s$ 的和减去区间 $c$ 和.

记区间 $[l, r]$ 前 $k$ 大 $s$ 的和减去区间 $c$ 和为 $w(l, r)$. 那么可以发现 $w(l, r)$ 满足四边形不等式，证明考虑区间 $c$ 和会被消掉，于是对于 $a < b < c < d$ 有 $w(a, c) + w(b, d) \ge w(a, d) + w(b, c)$.

那么第一问可以通过决策单调性分治解决，可以使用权值线段树维护区间前 $k$ 大和，移动左右端点，计算答案，当然也可以直接上主席树. 这一步的时间复杂度是 $\mathcal{O}(n\log^2 n)$. 

记第一问的答案为 $ans$，考虑第二问，我们将 $w=ans$ 的区间称为最优区间，一个数可以被选，当且仅当其为某个最优区间中的前 $k$ 大.

一个直接的想法是找出所有最优区间，用线段树维护每个点能被选所需要达到的最小值，然而最优区间的数目可以达到 $\Theta(n^2)$ 级别，因此需要进行一定的优化. 

考虑如果有两个最优区间 $[l_1, r_1], [l_2, r_2]$ 满足 $l_1< l_2 < r_2 < r_1$. 由四边形不等式有 $w(l_1, r_2) + w(l_2, r_1)\ge w(l_1, r_1) + w(l_2, r_2)$，即 $w(l_1, r_2) + w(l_2, r_1)\ge 2\times ans$，因此 $[l_1, r_2]$ 和 $[l_2, r_1]$ 也是最优区间. 易知只需要将 $[l_1, r_2], [l_2, r_2], [l_2, r_1]$ 三个区间计入考虑，需要计入考虑的左端点关于右端点单调不减，于是这是一个类双指针状物.

在分治过程中，对于每个 $r$ 计算最大的使 $w(l, r)$ 最大的 $l$. 将如此得到的所有最优区间存起来. 于是对于所有可以为最优区间右端点的 $r$，都得到了其对应的最大左端点 $l$，那么做一次双指针统计答案即可.

code:
```cpp
#include<bits/stdc++.h>

using i64 = long long;
#define int i64
const int N = 250005;

int n, k;

int c[N], s[N];
int v[N], len;
i64 sum[N];

namespace seg_t1 {

struct node {
    int l, r, c;
    i64 s;
}tree[N << 2];

#define ls(p) (p << 1)
#define rs(p) (ls(p) | 1)
#define l(p)  tree[p].l
#define r(p)  tree[p].r
#define c(p)  tree[p].c
#define s(p)  tree[p].s

inline void pushup(int p) {
    c(p) = c(ls(p)) + c(rs(p));
    s(p) = s(ls(p)) + s(rs(p));
}

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
}

void add(int p, int x, int val) {
    if (x > r(p) || x < l(p)) return;
    if (l(p) == x && r(p) == x) {
        c(p) += val;
        s(p) = 1ll * c(p) * v[l(p)];
        return;
    }
    add(ls(p), x, val);
    add(rs(p), x, val);
    pushup(p);
}

int qc(int p, int l, int r) {
    if (l > r(p) || r < l(p)) return 0;
    if (l <= l(p) && r(p) <= r) return c(p);
    return qc(ls(p), l, r) + qc(rs(p), l, r);
}

i64 qs(int p, int l, int r) {
    if (l > r(p) || r < l(p)) return 0;
    if (l <= l(p) && r(p) <= r) return s(p);
    return qs(ls(p), l, r) + qs(rs(p), l, r);
}

inline int bs(int k) {
    k = c(1) - k + 1;
    int cur = 1;
    while (l(cur) != r(cur)) {
        if (k > c(ls(cur))) k -= c(ls(cur)), cur = rs(cur);
        else cur = ls(cur);
    }
    return l(cur);
}

inline i64 get_ksum() {
    int x = bs(k);
    return qs(1, x + 1, len) + 1ll * (k - qc(1, x + 1, len)) * v[x];
}


#undef ls
#undef rs
#undef l
#undef r
#undef c
#undef s

}

using seg_t1::add;
using seg_t1::get_ksum;
using seg_t1::bs;

int _l = 1, _r;

inline void ins(int x) {
    add(1, s[x], 1);
}

inline void del(int x) {
    add(1, s[x], -1);
}

inline i64 g_res(int l, int r) {
    while (_l > l) ins(--_l);
    while (_r < r) ins(++_r);
    while (_l < l) del(_l++);
    while (_r > r) del(_r--);
    return get_ksum() - (sum[_r] - sum[_l - 1]);
}

i64 ans = -(1ll << 60);
std::vector<std::pair<int, int> > vc;

inline void solve(int l, int r, int ql, int qr) {
    if (l > r) return;
    int p = (l + r) >> 1;
    int pos = 0;
    i64 res = -(1ll << 60);
    for (int i = std::min(qr, p - k + 1); i >= ql; i--) {
        if (g_res(i, p) > res) {
            pos = i;
            res = g_res(i, p);
        }
    }
    if (res > ans) {
        ans = res;
        vc.clear();
    }
    if (res == ans) vc.emplace_back(pos, p);
    solve(l, p - 1, ql, pos);
    solve(p + 1, r, pos, qr);
}

bool f[N];

namespace seg_t2 {

struct node {
    int l, r, v;
}tree[N << 2];

#define ls(p) (p << 1)
#define rs(p) (ls(p) | 1)
#define l(p)  tree[p].l
#define r(p)  tree[p].r
#define v(p)  tree[p].v

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    v(p) = 0x7fffffff;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
}

void chkmin(int p, int l, int r, int v) {
    if (l > r(p) || r < l(p)) return;
    if (l <= l(p) && r(p) <= r) {
        v(p) = std::min(v(p), v);
        return;
    }
    chkmin(ls(p), l, r, v);
    chkmin(rs(p), l, r, v);
}

inline int qry(int p, int x) {
    if (x > r(p) || x < l(p)) return 0x7fffffff;
    if (l(p) == r(p)) return v(p);
    return std::min(v(p), std::min(qry(ls(p), x), qry(rs(p), x)));
}

}

using seg_t2::chkmin;
using seg_t2::qry;

signed main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> c[i];
    for (int i = 1; i <= n; i++) std::cin >> s[i];

    memcpy(v, s, sizeof s);
    std::sort(v + 1, v + n + 1);
    len = std::unique(v + 1, v + n + 1) - v - 1;
    for (int i = 1; i <= n; i++) s[i] = std::lower_bound(v + 1, v + len + 1, s[i]) - v;
    
    for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + c[i];

    seg_t1::build(1, 1, len);
    solve(k, n, 1, n);
    seg_t2::build(1, 1, n);
    std::sort(vc.begin(), vc.end());
    for (const auto &[ml, r] : vc) {
        static int l = 1;
        for (; l <= ml; l++) 
            if (g_res(l, r) == ans) chkmin(1, l, r, bs(k));
        l = ml;
    }
    std::cout << ans << '\n';
    for (int i = 1; i <= n; i++) std::cout << (s[i] >= qry(1, i));
    std::cout << '\n';
}
```


---

## 作者：EuphoricStar (赞：10)

考虑第一问，设一个区间的价值 $g(l, r)$ 为 $f(l, r) - a_r + a_{l - 1}$，其中 $a_i = \sum\limits_{j = 1}^i c_j$，$f(l, r)$ 为 $[l, r]$ 中最大的 $k$ 个 $b_i$ 的和，设 $p_i$ 为以 $i$ 为右端点，区间价值最大的左端点，那么 $p_i$ 满足决策单调性，也就是 $p_i \le p_{i + 1}$。

证明即证：

$$g(a, c) + g(b, d) \ge g(a, b) + g(c, d)$$

其中 $a \le b \le c \le d$。化简得：

$$f(a, c) + f(b, d) \ge f(a, b) + f(c, d)$$

即证：

$$f(a, b) + f(a + 1, b + 1) \ge f(a, b + 1) + f(a + 1, b)$$

考虑 $[a, b + 1]$ 相当于是 $[a + 1, b]$ 的加入两个单点 $a$ 和 $b$，它们能替换 $[a + 1, b]$ 中前 $k$ 大的最小值和次小值，但是如果换成 $[a, b]$ 和 $[a + 1, b + 1]$，那么 $a$ 和 $b$ 只能分别替换 $[a + 1, b]$ 的最小值，所以 $[a, b], [a + 1, b + 1]$ 一定不劣。

所以第一问就可以直接基于这个利用分治算，$g(l, r)$ 可以维护 $l, r$ 的指针然后移动指针的同时用树状数组维护。

对于第二问，对于每个点求**最大**的 $p_i$，然后把所有 $g(p_i, i)$ 等于答案的 $[p_i, i]$ 从左往右扫，那么右端点为 $i$，左端点在 $l \sim p_i$ 之间（其中 $l$ 为上一个 $g(p_j, j)$ 等于答案的 $p_j$）的区间会对第二问的答案有贡献。就相当于现在有一些形如 $(l, r, k)$ 的操作，意义是把 $l \sim r$ 且 $b_i \ge k$ 的 $i$ 的答案设为 $1$，那么直接对 $k$ 扫描线，链表或并查集维护全部 $b_i \ge k$ 且还没被覆盖过的点即可。

总时间复杂度 $O(n \log^2 n)$。

[code](https://loj.ac/s/2036478)

---

## 作者：henryhu2006 (赞：7)

可以通过贪心进一步概括题意为：找到所有区间 $[l,r]$，使得区间 $s_i$ 的前 $k$ 大之和减去 $c_i$ 区间和最大。第一问求最大值；第二问将所有最大的区间中 $\ge k$ 大值的全部设为可能。

## 结论
设以 $l$ 为左端点的所有区间中最优的 $r$ 为 $opt(l)$（如果有多个则要统一标准，例如靠右），则 $opt(l)$ 随着 $l$ 增加单调不降。

证明这个结论需要利用 DP。设 $f(r,i)$ 表示，以 $r$ 为目前右端点，已经选择了 $i$ 个前 $k$ 大的值，答案最大是多少。只要满足 $i\le k$，因为选择了不是 $k$ 大的值作为 $k$ 大显然不优。

决策 $r$ 是否作为前 $k$ 大，于是有转移方程：

$$
f(r,i)=\max\{f(r-1,i),f(r-1,i-1)+s_i\}-c_i
$$

可以将 DP 转移看作一张 DAG，$(r-1,i)$ 向 $(r,i)$ 连边权为 $-c_i$ 的边；$(r-1,i-1)$ 向 $(r,i)$ 连边权为 $s_i-c_i$ 的边；则第一问即求该图的最长路。

如果 $l_1,l_2$ 不满足上述性质，设 $l_1<l_2$，$opt(l_2)<opt(l_1)$。可以发现它们对应的路径一定有公共点，可以用[原版题解](https://www.ceoi2023.de/wp-content/uploads/2023/09/4-trade-spoiler.pdf)的图来理解这一点。

![](https://cdn.luogu.com.cn/upload/image_hosting/cc0o0mfw.png)

在途中节点 $v$ 的右侧，如果 $v\to r_1$ 更优，则 $l_2$ 选择 $r_1$ 更优；若 $v\to r_2$ 更优，则 $l_1$ 选择 $r_2$ 更优。

和之前的假设矛盾，因此结论成立。

## 解法一

有了类似“决策单调性”一样的结论，可以使用分治。设当前要解决区间 $[l,r]$ 的最优决策点，取中点 $m$，对于可能的右端点范围都计算一遍答案，取最优点将可能范围划分，向下分治处理 $[l,m-1]$ 和 $[m+1,r]$。

计算答案可以使用主席树算前 $k$ 大的和。

对于第二问，我们需要给区间 $\ge$ 第 $k$ 大的所有值都设为可行。可以在线段树上打标记，表示此节点所对应的区间中的值达到多少可以被设为可行。

可以利用双指针证明左右端点移动次数是 $\mathcal O(n)$ 的，但不影响复杂度。

因此时间复杂度 $\mathcal O(n\log ^2n)$。

## 解法二

[原版题解](https://www.ceoi2023.de/wp-content/uploads/2023/09/4-trade-spoiler.pdf)还给出了一种空间复杂度 $\mathcal O(n)$ 的做法，利用到 $k$ 是定值的性质。

可以用对顶堆维护前 $k$ 大的和，并按照分治的顺序直接移动左右端点，移动次数是 $\mathcal O(n\log n)$ 的，所以时间复杂度依然是 $\mathcal O(n\log^2n)$。

## 代码
用第一种解法。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2.5e5+5,inf=1e9;
int n,k,a[N],b[N],d[N],rt[N],now;
ll s[N],c[N],ans=-1e18;
inline void read(int &ret){
	ret=0; int ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch))
		ret=ret*10+(ch^48),ch=getchar();
}
namespace chair{
	int tot;
	struct node{int ls,rs,num; ll sum;} t[N*35];
	void add(int &x,int y,int l,int r,int p){
		x=++tot,t[x]=t[y],t[x].num+=1,t[x].sum+=p;
		if(l==r) return;
		int mid=l+r>>1;
		if(p<=mid) add(t[x].ls,t[y].ls,l,mid,p);
		else add(t[x].rs,t[y].rs,mid+1,r,p);
	}
	ll ask(int x,int y,int l,int r,int k){
		if(l==r){now=l; return 1ll*k*l;}
		int mid=l+r>>1,num=t[t[y].rs].num-t[t[x].rs].num;
		if(k<=num) return ask(t[x].rs,t[y].rs,mid+1,r,k);
		else return t[t[y].rs].sum-t[t[x].rs].sum
			+ask(t[x].ls,t[y].ls,l,mid,k-num);
	}
}
namespace seg{
	int t[N*4];
	void add(int x,int l,int r,int ql,int qr,int v){
		if(ql<=l&&r<=qr){t[x]=min(t[x],v); return;}
		int mid=l+r>>1;
		if(ql<=mid) add(x<<1,l,mid,ql,qr,v);
		if(qr>mid) add(x<<1|1,mid+1,r,ql,qr,v);
	}
	int ask(int x,int l,int r,int p){
		if(l==r) return t[x];
		int mid=l+r>>1;
		if(p<=mid) return min(t[x],ask(x<<1,l,mid,p));
		else return min(t[x],ask(x<<1|1,mid+1,r,p));
	}
}
ll calc(int l,int r){
	return chair::ask(rt[l-1],rt[r],1,inf,k)-s[r]+s[l-1];
}
struct op{int l,r,v;}; vector<op> vec;
void solve(int l,int r,int L,int R){
	if(l>r) return;
	int mid=l+r>>1,y; ll mx=-1e18;
	for(int i=max(mid+k-1,L);i<=R;++i)
		c[i]=calc(mid,i),d[i]=now,mx=max(mx,c[i]);
	if(mx>ans) vec.clear(),ans=mx;
	for(int i=max(mid+k-1,L);i<=R;++i)
		if(c[i]==mx){
			y=i;
			if(mx==ans) vec.push_back({mid,i,d[i]});
		}
	solve(l,mid-1,L,y);
	solve(mid+1,r,y,R);
}
int main(){
	read(n),read(k);
	memset(seg::t,63,sizeof(seg::t));
	for(int i=1;i<=n;++i) read(a[i]),s[i]=s[i-1]+a[i];
	for(int i=1;i<=n;++i)
		read(b[i]),chair::add(rt[i],rt[i-1],1,inf,b[i]);
	solve(1,n-k+1,k,n);
	for(auto p:vec) seg::add(1,1,n,p.l,p.r,p.v);
	cout<<ans<<endl;
	for(int i=1;i<=n;++i)
		putchar(48+(seg::ask(1,1,n,i)<=b[i])); 
	return 0;
} 
```

---

## 作者：i_love_xqh (赞：6)

设 $val[l,r]$ 表示该区间的答案，容易发现 $val$ 满足四边形不等式，考虑设 $l<l'$ 且 $val[l,r]<val[l',r]$，当 $r$ 增大时，增加的和相等，而前 $k$ 大的和对 $[l',r']$ 的贡献显然更大，所以仍然 $val[l,r']<val[l',r']$。所以决策点单调不降，通过整体二分加主席树可 $O(n\log^2 n)$ 解决第一问，设答案为 $ans$。

设 $l<l'<r'<r$，考虑由于满足 $val[l,r']+val[l',r]\ge val[l,r]+val[l',r']$，假设 $[l,r]$ 和 $[l',r']$ 区间答案都是 $ans$，则显然可以得到 $val[l,r']=val[l',r]=ans$，因为答案是所有最优区间前 $k$ 大的并集，而 $[l,r']$ 和 $[l',r]$ 显然包含了 $[l,r]$ 的答案，所以 $[l,r]$ 就不用考虑，也就是说可以用双指针得到所有区间。对于每个区间将答案跟第 $k$ 大取 $\min$ 即可。

---

## 作者：gan1234 (赞：6)

[题目链接](https://www.luogu.com.cn/problem/P9732)

### 题意

题意可以贪心的转化成：定义一个长度至少为 $k$ 的区间的值为该区间前 $k$ 大的 $s_i$ 之和减去区间所有 $c_i$ 之和，求出最大的的区间值，并且把所有最大的区间的前 $k$ 大 $s_i$ 标记为 $1$。

### 分析

考虑从 $1$ 到 $n-k+1$ 枚举区间的左端点 $l$，求出最大区间的右端点 $r$。我们发现没有必要每次求 $r$ 都从 $l+k-1$ 枚举到 $n$。

分析可得出一个性质：设 $l<i<j<r$，枚举左端点到 $l$ 时，若求出 $r$ 是最大的区间右端点，那么区间 $[i,j]$ 的值一定不大于 $[l,r]$。假如存在 $[i,j]$ 的值大于 $[l,r]$，那么 $[l,j]$ 的值就一定也大于 $[l,r]$，与原条件相矛盾，因此不可能。

这个性质意味着，如果我们已经求出了 $l$ 的最大右端点 $r$，那么我们在求 $l+1$ 时不用管 $l+1\sim r-1$ 了，一定没有 $[l,r]$ 更大，所以我们要求的右端点单调不减。

### 解法

对于这种决策点单调不减的问题，我们直接上分治求，$solve(l,r,x,y)$ 表示区间 $[l,r]$ 中每个点的最大右端点范围在 $[x,y]$，先枚举求出中点 $mid$ 的右端点 $t$，再递归求解 $solve(l,mid-1,x,t)$ 和 $solve(mid+1,r,t,y)$。

那么如何求 $mid$ 的 $r$ 呢？我们可以从 $x$ 枚举到 $y$，使用 set 和双指针快速求出区间 $[mid,i]$ 的值。具体来说，定义 $L,R$ 左右两个指针，用 set 维护 $[L,R]$ 里的 $s_i$，定义 $sum$ 表示 set 里前 $k$ 大 $s_i$ 之和，定义 $val$ 表示第 $k$ 大的值。每次移动左右指针时在 set 里插入删除值，同时更新 $sum$ 和 $val$。由于分治的树形结构，每次指针都不会移动太多，总移动次数最多为 $O(n\log n)$ 次。

当然，你也可以使用平衡树或可持久化线段树来解决这个问题。

现在我们只剩下第二问了。我们可以在分治的过程中存下所有最大的区间和该区间的 $val$，如果位于该区间的数大于 $val$，那么就把它标记为 $1$。显然这个可以线段树区间取 $min$ 单点求值来解决，用线段树给所有区间打上标记 $val$，再枚举每个点判断 $s_i$ 是否大于 $val$。

分治加双指针 set 时间复杂度为 $O(n\log^2n)$，第二问线段树的时间复杂度为 $O(n\log n)$，总时间复杂度为 $O(n\log^2n)$，空间复杂度为 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define MAXN 250005
#define int long long
#define P pair<int,int>
using namespace std;
int n,k,ans=-1e15;
int a[MAXN],b[MAXN],sa[MAXN];
vector<int>nxt[MAXN];
struct Seg_Tree{
    int l,r,mn;
}dat[MAXN<<2];
void build(int l,int r,int k){
    dat[k].l=l;dat[k].r=r;dat[k].mn=2e9;
    if(l==r)return ;
    int m=(l+r)/2;
    build(l,m,k+k);
    build(m+1,r,k+k+1);
}
void update(int x,int y,int z,int k){
    if(dat[k].l==x&&dat[k].r==y){
        dat[k].mn=min(dat[k].mn,z);
        return ;
    }
    int m=(dat[k].l+dat[k].r)/2;
    if(y<=m)update(x,y,z,k+k);
    else if(x>m)update(x,y,z,k+k+1);
    else update(x,m,z,k+k),update(m+1,y,z,k+k+1);
}
int query(int x,int k){
    if(dat[k].l==x&&dat[k].r==x)return dat[k].mn;
    int m=(dat[k].l+dat[k].r)/2;
    if(x<=m)return min(dat[k].mn,query(x,k+k));
    else return min(dat[k].mn,query(x,k+k+1));
}
set<P>S;
int L,R,sum,pos;
void add(int x){
    S.insert(P{-b[x],x});
    set<P>::iterator it=S.lower_bound(P{-b[pos],pos});it--;
    if(b[x]>b[pos]||(b[x]==b[pos]&&x<pos))sum-=-b[pos]+b[x],pos=(*it).second;
}
void del(int x){
    if(b[x]>b[pos]||(b[x]==b[pos]&&x<pos)||x==pos)pos=(*S.upper_bound(P{-b[pos],pos})).second,sum+=-b[pos]+b[x];
    S.erase(P{-b[x],x});
}
void move(int l,int r){
    while(L>l)add(--L);
    while(R<r)add(++R);
    while(L<l)del(L++);
    while(R>r)del(R--);
    
}
void solve(int l,int r,int x,int y){
    if(l>r)return ;
    int mid=(l+r)/2;
    int mx=-1e15,id=0;
    for(int i=max(mid+k-1,x);i<=y;i++){
        move(mid,i);
        if(-sum-(sa[i]-sa[mid-1])>mx){
            mx=-sum-(sa[i]-sa[mid-1]),id=i;nxt[mid].clear();nxt[mid].push_back(i);
        }else if(-sum-(sa[i]-sa[mid-1])==mx)nxt[mid].push_back(i),id=i;
    }
    ans=max(ans,mx);
    solve(l,mid-1,x,id);
    solve(mid+1,r,id,y);
}
signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>k;
    for(int i=1;n>=i;i++)cin>>a[i],sa[i]=sa[i-1]+a[i];
    for(int i=1;n>=i;i++)cin>>b[i];
    for(int i=1;n>=i;i++)S.insert(P{-b[i],i});
    int t=k;
    for(auto i=S.begin();t;i++,t--){
        sum+=(*i).first;
        pos=(*i).second;
    }
    L=1,R=n;
    solve(1,n-k+1,k,n);
    cout<<ans<<endl;
    
    build(1,n,1);
    for(int i=1;n-k+1>=i;i++){
        for(int j=0;nxt[i].size()>j;j++){
            move(i,nxt[i][j]);
            if(-sum-(sa[nxt[i][j]]-sa[i-1])==ans)update(i,nxt[i][j],b[pos],1);
        }
    }
    for(int i=1;n>=i;i++)cout<<(query(i,1)<=b[i]);
    return 0;
}
```




---

## 作者：xcyyyyyy (赞：5)

复习一波四边形不等式优化。

对于 $f_i=\min \limits_{j\leq i}w(i,j)$ 来说，交叉小于包含，即为四边形不等式。若 $w$ 满足四边形不等式，那么对于 $j$ 来说，$\exist p(j)\geq \max p(i)(i\lt j)$。

---

回到这道题上，考虑很多算法后我已经意识到了这道题需要使用特殊性质，考虑了什么凸函数求和呀什么 wqs 二分啊发现全部不管用。我居然搞忘了决策单调性了。

首先考虑第一个小问：

设 $f(l,r)$ 表示第一次选择 $l，r$ 的最大值， $p(i)$ 表示右端点为 $i$ 时左端点为 $p(i)$，$f(p(i),i)$ 最大。

考虑四边形不等式，我们现在需要证明：

$$
f(a-1,b)+f(a,b+1)\geq f(a,b)+f(a-1,b+1)
$$

不妨设 $g(l,r)$ 表示 $[l,r]$ 中前 $k$ 大的值之和，那么 $f(l,r)=g(l,r)-(pr_r-pr_{l-1})$，我们发现上式中 $(pr_r-pr_{l-1})$ 可以抵消，那么原式就变成了：

$$
g(a-1,b)+g(a,b+1)\geq g(a,b)+g(a-1,b+1)
$$

用 $g$ 的意义来刻画这个东西，本来是 $g(a,b)$ 的值，我们向左扩一个，又向右扩一个，若他们啥也没有替换出来或者只替换出来一个那左右两个式子相等；如果替换出来了两个，如果这两个相等或者分别为次小值和最小值，那么 $a-1,b+1$ 还要抢位置，这肯定没有他们独占一边好，所以该式成立。

那么我们就可以用决策单调性分治来计算这个东西了。

---

区间前 $k$ 大可以决策单调性分治的时候算，也可以把序列拍到主席树上去。

接下来再考虑如何计算第二个小问：

我们称 $ f(l,r)=ans$ 的区间为合法区间，$kth(l,r)$ 表示 $[l,r]$ 区间内第 $k$ 大的数。

对于一个合法区间 $[l,r]$，对于 $l \leq i \leq r,a_i\geq kth(l,r)$，那么 $i$ 下标的答案为 $1$，此时我们称 $i$ 被 $ [l,r]$ 认可。

所以我们肯定不能只算合法的 $[p(i),i]$ 这几个区间。

如果我们把暴力找出所有合法区间，再暴力拍到线段树上，时间复杂度为 $O(n^2 \log n)$，我们第一问的精心实现完全作废。

不妨考虑四边形不等式，若存在 $f(a,d),f(b,c)=ans，a \lt b \leq c \lt d$，那么我们有：

$$
f(a,c)+f(b,d) \geq f(a,d)+f(b,c)
$$

由于 $f(a,d),f(b,c)=ans$，又因为 $ans$ 的最小性，我们可以得出 $f(a,c),f(b,d)=ans$。

同时又因为刚刚我们对四边形不等式的证明，若存在 $i$ 被 $[a,d]$ 认可，那么他一定会在 $[a,c],[b,d],[b,c]$ 中至少一个中也被认可。换个说法就是，我们不需要考虑 $[a,d]$ 的贡献。

上面的推导说明，只要存在$A \subset B(l_A\neq l_B ,r_A \neq r_B)$，那么我们一定能找到其他几个合法区间来代替 $A$ 的作用。

既然合法区间之间不存在包含关系，那么我们所需要的合法区间按照右端点排序后，左端点一定是递增的形式。

因为对于每个 $i$ 都已经求出对应的 $p(i)$ 了，我们只需要对应的把一些可能没有考虑的合法区间算上即可。

下面给出做法：~实在不想理解的也不用理解了~

首先我们需要求出对于一个 $i$ 最大的 $p(i$)。

具体的说，我们从左往右考虑合法区间 $[p(i),i]$，对于上一个区间 $[p(j),j]$,$(i \gt j)$ 来说，我们可能还需要计算一些夹在 $[p(j),j]$，$[p(i),i]$ 中的区间。

$r\in(j,i)$ 中的区间一定没有合法的了，但是我们可能还需要一些 $r=i$ 的区间，所以我们只需要再多考虑满足 $l\in[p(j),p(i)),r=i$ 的合法 $[l,r]$ 区间即可，不存在 $j \lt i$ 的时候 $p(j)=1$。

不长的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls(x) tr[x].ls
#define rs(x) tr[x].rs
#define cnt(x) tr[x].cnt
#define sum(x) tr[x].sum
#define MX 1000000000
#define N 250005
#define ll long long
int n,k;
ll pr[N],b[N],p[N],ans=-0x7fffffffffffffff;

struct Node{int ls,rs,cnt;ll sum;};
Node tr[N<<5];int tot,rt[N];
inline void pull(int rt){
    cnt(rt)=cnt(ls(rt))+cnt(rs(rt));
    sum(rt)=sum(ls(rt))+sum(rs(rt));
}
void upd(int &rt,int l,int r,int x){
    tr[++tot]=tr[rt];rt=tot;
    if(l==r)return ++tr[rt].cnt,tr[rt].sum+=x,void();
    int m=(l+r)>>1;
    if(m>=x)upd(ls(rt),l,m,x);
    else upd(rs(rt),m+1,r,x);
    pull(rt);
}
ll ask(int p,int q,int l,int r,int k){
    if(l==r)return 1ll*k*l;
    int m=(l+r)>>1;
    if(cnt(rs(q))-cnt(rs(p))>=k)return ask(rs(p),rs(q),m+1,r,k);
    else return ask(ls(p),ls(q),l,m,k-(cnt(rs(q))-cnt(rs(p))))+sum(rs(q))-sum(rs(p));
}
ll kth(int p,int q,int l,int r,int k){
    if(l==r)return l;
    int m=(l+r)>>1;
    if(cnt(rs(q))-cnt(rs(p))>=k)return kth(rs(p),rs(q),m+1,r,k);
    else return kth(ls(p),ls(q),l,m,k-(cnt(rs(q))-cnt(rs(p))));
}
inline ll f(int l,int r){return ask(rt[l-1],rt[r],1,MX,k)-(pr[r]-pr[l-1]);}

void solve(int l,int r,int lmid,int rmid){
    if(l>r)return;
    int mid=(l+r)>>1;ll w=-0x7fffffffffffffff;
    for(int i=min(rmid,mid-k+1);i>=lmid;i--)
        if(f(i,mid)>w)w=f(i,mid),p[mid]=i;
    solve(l,mid-1,lmid,p[mid]);
    solve(mid+1,r,p[mid],rmid);
}

vector<ll> ad[N],dl[N];
inline void add(int l,int r){
    ll x=kth(rt[l-1],rt[r],1,MX,k);
    dl[r+1].push_back(x);
    ad[l].push_back(x);
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%lld",&pr[i]),pr[i]+=pr[i-1];
    for(int i=1;i<=n;i++)scanf("%lld",&b[i]),rt[i]=rt[i-1],upd(rt[i],1,MX,b[i]);
    solve(k,n,1,n);
    for(int i=k;i<=n;i++)ans=max(ans,f(p[i],i));
    p[0]=1;
    for(int i=k,j=0,x;i<=n;i++)if(f(p[i],i)==ans){
        add(p[i],i);
        for(int k=p[j];k<p[i];k++)if(f(k,i)==ans)add(k,i);
        j=i;
    }
    printf("%lld\n",ans);
    multiset<ll> S;
    for(int i=1;i<=n;i++){
        for(int x:ad[i])S.insert(x);
        for(int x:dl[i])S.erase(S.lower_bound(x));
        if(S.size()&&b[i]>=*S.begin())putchar('1');
        else putchar('0');
    }
}
```

---

## 作者：_fairytale_ (赞：3)

对于一段区间，我们肯定卖出其中 $s$ 前 $k$ 大的波特。所以设 $f(l,r)$ 表示 $[l,r]$ 中 $s$ 的前 $k$ 大之和，$w(l,r)$ 表示 $f(l,r)-\sum_{i=l}^r c_i$，即 $[l,r]$ 的答案。

枚举区间右端点 $r$，现在我们要找到使得 $w(l,r)$ 最大的 $l$。

猜测这个问题有决策单调性，于是我们需要证，对于 $a\le b\le c < d$，有 $w(b,c)-w(a,c)\le w(b,d)-w(a,d)$，即如果 $c$ 的决策点在 $a$，接下来的决策点只会在 $a$ 以后。

证明：

首先不等号两侧含有 $c$ 的部分是相等的，所以只需证 $f(b,c)-f(a,c)\le f(b,d)-f(a,d)$，移项得 $f(a,d)-f(a,c)\le f(b,d)-f(b,c)$，即证 $[b,c]$ 变成 $[b,d]$ 之后增加的量不小于 $[a,c]$ 变成 $[a,d]$ 之后增加的量。

考虑 $[a,c]$ 变成 $[a,d]$ 之后新增的作为前 $k$ 大的数，它们一定也作为 $[b,d]$ 的前 $k$ 大，且它们使 $[b,c]$ 增加的量一定不小于使 $[a,c]$ 增加的量，证明可以把这些数和它们替换掉的数对应起来考虑。而 $[b,c]$ 这个区间新增的至少是这些数，所以命题成立。

$f(l,r)$ 不难通过可持久化值域线段树求得，至此我们可以使用决策单调性分治解决第一问。

称 $w(l,r)$ 取到答案的区间为最优区间。

对于第二问，一个波特会被卖出去当且仅当它是某个最优区间的前 $k$ 大。

可是最优区间既有相交也有包含，如果需要考虑的区间的右端点随着左端点单调不降就好了。

如果 $[b,c]$ 是最优区间，则我们不需要考虑与 $[b,c]$ 端点不重合，且包含 $[b,c]$ 的最优区间。这是因为，考虑某个最优区间 $[a,d]$ 满足 $a<b\le c<d$，再考虑 $[a,c]$ 和 $[b,d]$ 两个区间，由 $w(a,c)+w(b,d)\ge w(a,d)+w(b,c)=2ans$ 和 $ans$ 的最大性得 $[a,c]$ 和 $[b,d]$ 也是最优区间。又因为 $[a,d]$ 的前 $k$ 大一定至少在 $[a,c]$ 和 $[b,d]$ 当中的一个取到，所以不需考虑 $[a,d]$。

因此，我们如果按照右端点单调递增的顺序考虑所有最优区间，那么左端点也单调不降。

于是我们做一个双指针，找到 $\mathcal O(n)$ 个区间，它们每一个都是“把 $[l,r]$ 中 $s\ge x$ 的位置设为 $1$”的形式，容易维护。

记 $p_r$ 表示使 $w(l,r)=ans$ 的**最大**的 $l$，双指针的使用把 $l$ 移到 $p_r$ 即可。双指针的时候记得只有当前右端点是某个最优右端点的时候才移动左端点！！！

关于为什么不能取 $q_r$ 表示使 $w(l,r)=ans$ 的最小的 $l$：考虑双指针的算法流程，取 $p_r$ 会使我们漏算某些端点不重合包含某些区间的区间，而取 $q_r$ 会使我们漏算某些被某些区间端点不重合包含的区间。在本题 $p_r$ 是我们需要的。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define rep(x,qwq,qaq) for(int x=(qwq);x<=(qaq);++x)
#define per(x,qwq,qaq) for(int x=(qwq);x>=(qaq);--x)
using namespace std;
template<class _T>
void ckmax(_T &x,_T y){
	x=max(x,y);
}
#define infll 0x3f3f3f3f3f3f3f3f
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,k;
	cin>>n>>k;
	vector<int>c(n+1),s(n+1);
	rep(i,1,n)cin>>c[i];
	rep(i,1,n)cin>>s[i];
	vector<ll>pre(n+1);
	rep(i,1,n)pre[i]=pre[i-1]+c[i];
	struct node{int ls,rs,cnt;ll sum;};
	vector<node>t(n<<6);
	vector<int>rt(n+1);int tot=0;
	auto mdf=[&](auto &mdf,int &p,int lsp,int x,int l=1,int r=1e9)->void{
		t[p=++tot]=t[lsp];
		++t[p].cnt,t[p].sum+=x;
		if(l==r)return;
		if(mid>=x)mdf(mdf,t[p].ls,t[lsp].ls,x,l,mid);
		else mdf(mdf,t[p].rs,t[lsp].rs,x,mid+1,r);
	};
	rep(i,1,n)mdf(mdf,rt[i],rt[i-1],s[i]);
	auto q=[&](auto &q,int L,int R,int k,int l=1,int r=1e9)->ll{
		if(l==r)return 1ll*l*k;
		int d=t[t[R].rs].cnt-t[t[L].rs].cnt;
		if(d>=k)return q(q,t[L].rs,t[R].rs,k,mid+1,r);
		else return t[t[R].rs].sum-t[t[L].rs].sum+q(q,t[L].ls,t[R].ls,k-d,l,mid);
	};
	vector<int>p(n+1);
	auto w=[&](int l,int r)->ll{
		return q(q,rt[l-1],rt[r],k)-(pre[r]-pre[l-1]);
	};
	ll ans=-infll;
	auto solve=[&](auto &solve,int l,int r,int L,int R)->void{//[l,r] 的最优决策点在 [L,R] 中 
		if(l>r)return;
		ll best=-infll;
		rep(i,L,min(R,mid-k+1)){
			ll s=w(i,mid);
			if(s>=best)best=s,p[mid]=i;
		}
		ckmax(ans,best);
		solve(solve,l,mid-1,L,p[mid]);
		solve(solve,mid+1,r,p[mid],R);
	};
	solve(solve,k,n,1,n);
	cout<<ans<<'\n';
	struct T{int op,l,r,x;};
	vector<T>m;
	auto q2=[&](auto &q2,int L,int R,int k,int l=1,int r=1e9)->int{
		if(l==r)return l;
		int d=t[t[R].rs].cnt-t[t[L].rs].cnt;
		if(d>=k)return q2(q2,t[L].rs,t[R].rs,k,mid+1,r);
		else return q2(q2,t[L].ls,t[R].ls,k-d,l,mid);
	};
	for(int l=1,r=k;r<=n;++r){if(w(p[r],r)!=ans)continue;for(;l<=p[r];++l)if(w(l,r)==ans)m.push_back({-1,l,r,q2(q2,rt[l-1],rt[r],k)});if(l>1)--l;}
	rep(i,1,n)m.push_back({1,i,i,s[i]});
	sort(m.begin(),m.end(),[](const T&x,const T&y){return x.x!=y.x?x.x>y.x:x.op>y.op;});
	set<int>z;vector<int>a(n+1);
	for(T&t:m){
		if(t.op==1)z.insert(t.l);
		else for(auto it=z.lower_bound(t.l),itr=z.upper_bound(t.r);it!=itr;it=z.erase(it))a[*it]=1;
	}
	rep(i,1,n)cout<<a[i];cout<<'\n';
	return 0;
}
```

---

## 作者：Lucyna_Kushinada (赞：1)

# P9732 [CEOI 2023] Trade

## 简要题意

有长度为 $n$ 的序列 $s$ 与 $c$ 和一个整数 $k$。

请选定一个区间 $[l,r] (r-l+1\ge k)$，并选定其中恰好 $k$ 个下标组成集合 $A$。

请你最大化 $\displaystyle \sum_{x\in A} s_x-\sum_{i=l}^r c_i$，并求出在价值最大化的前提下，有哪些下标能在某种最优方案中被选入集合 $A$。

## 题解

知识点：决策单调性，主席树，双指针。

一个显然的事实，所选定的 $k$ 个 $s_i$ 一定是该区间内 $s_i$ 的前 $k$ 大。

设当前考虑到右端点为 $r$ 的区间，设其最优决策点为 $l'$，当 $r$ 增大时，思考 $l'$ 如何变化。

> 答案是显然的，$l'$ 一定单调不减，倘若 $l'$ 在 $r$ 变大之后突然变小，则说明 $l'$ 的新位置的 $s_i$ 会被选入前 $k$ 大，否则只会产生 $-c_i$ 的负贡献，既然如此，为什么不在 $r$ 没增大的时候到这个位置呢？毕竟随着区间左右扩大，前 $k$ 大是单调不减的。故得证。

所以这题满足决策单调性，且满足四边形不等式。

那第一问就是个分治处理决策单调性的板子了，用主席树可以做到时间复杂度 $O(n \log^2n)$，来看第二问。

显然，$i$ 被选入当且仅当 $s_i$ 大于等于某个最优区间 $[l,r]$ 的第 $k$ 大。

一个显然的思路是，在转移的过程中处理出所有最有区间，遍历每个区间，标记该区间中 $s_i$ 大于等于第 $k$ 大的 $i$。

但是最优区间最坏情况下有 $O(n^2)$，得去除大部分无用的区间。

先考虑两个最优区间 $[a,d],[b,c]$ 满足 $a<b\le c<d$，由四边形不等式得出 $w(a,c)+w(b,d)\ge w(a,d)+w(b,c)$，又因为 $w(a,d)=w(b,c)=ans$，则一定有 $w(a,c)=w(b,d)=ans$。

这时候 $[a,d]$ 是无用的，因为任何一个在这个区间里当前 $k$ 大的 $s_i$，都能在被它包含的 $[a,c],[b,c],[b,d]$ 取到，而且这些区间更小，在这里的数有更多机会取得前 $k$ 大。

处理出 $pre_i$，表示以 $i$ 为右端点且最靠右（最有机会）的最优决策点（不一定能得到答案），可以证明 $pre_i$ 随 $i$ 增大是单调不减的。

所以对于两个相邻且满足 $[pre_i,i],[pre_j,j]$ 能计算出答案的 $i,j(j<i)$，就如上面所说，枚举 $k\in [pre_j,pre_i]$ 为左端点（不用枚举 $[j,i]$，因为 $pre_i$ 是最靠右的，所以一定没有合法的），和 $i$ 搭配，看是否能计算出答案，如果能就去线段树上区间取 $\min$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define bg(x) (x).begin()
#define ed(x) (x).end()

#define N 252507
#define int long long

int n,m,c[N],s[N],rt[N],pre[N];
int L=1,R=0,ans=-1e18;

struct hjt{
    #define mid ((l+r)>>1)

    int cnt=0;

    struct node{
        int ls,rs,s,c;
    }tr[N*32];

    inline void ins(int pre,int &k,int l,int r,int d){
        k=++cnt;

        tr[k]=tr[pre];
        tr[k].c++;
        tr[k].s+=d;

        if(l==r){
            return;
        }

        if(d<=mid){
            ins(tr[pre].ls,tr[k].ls,l,mid,d);
        }
        else{
            ins(tr[pre].rs,tr[k].rs,mid+1,r,d);
        }
    }

    inline int ask(int x,int y,int l,int r,int d){
        if(l==r){
            return min(d,tr[y].c-tr[x].c)*l;
        }

        int cc=tr[tr[y].rs].c-tr[tr[x].rs].c;
        int ss=tr[tr[y].rs].s-tr[tr[x].rs].s;

        if(cc<d){
            return ask(tr[x].ls,tr[y].ls,l,mid,d-cc)+ss;
        }
        return ask(tr[x].rs,tr[y].rs,mid+1,r,d);
    }

    inline int qry(int x,int y,int l,int r,int d){
        if(l==r){
            return l;
        }

        int cc=tr[tr[y].rs].c-tr[tr[x].rs].c;

        if(cc<d){
            return qry(tr[x].ls,tr[y].ls,l,mid,d-cc);
        }
        return qry(tr[x].rs,tr[y].rs,mid+1,r,d);
    }

    #undef mid
}t;

struct segt{
    #define mid ((l+r)>>1)

    int tr[N<<2],mn[N<<2];

    inline void build(int k,int l,int r){
        tr[k]=mn[k]=1e9+1;

        if(l==r){
            return;
        }

        build(k*2,l,mid);
        build(k*2+1,mid+1,r);
    }

    inline void un(int k){
        tr[k]=min(tr[k*2],tr[k*2+1]);
    }

    inline void addt(int k,int d){
        mn[k]=min(mn[k],d);

        tr[k]=min(tr[k],mn[k]);
    }

    inline void pd(int k){
        if(mn[k]<1e9+1){
            addt(k*2,mn[k]);
            addt(k*2+1,mn[k]);
            mn[k]=1e9+1;
        }
    }

    inline void upd(int L,int R,int k,int l,int r,int d){
        if(L<=l&&R>=r){
            addt(k,d);
            return;
        }

        pd(k);

        if(L<=mid){
            upd(L,R,k*2,l,mid,d);
        }
        if(R>mid){
            upd(L,R,k*2+1,mid+1,r,d);
        }

        un(k);
    }

    inline int ask(int L,int R,int k,int l,int r){
        if(L<=l&&R>=r){
            return tr[k];
        }

        pd(k);

        int ans=1e9+1;

        if(L<=mid){
            ans=ask(L,R,k*2,l,mid);
        }
        if(R>mid){
            ans=min(ans,ask(L,R,k*2+1,mid+1,r));
        }

        return ans;
    }

    #undef mid
}b;

inline int calc(int i,int mid){
    int now=t.ask(rt[i-1],rt[mid],1,1e9+1,m);
    int sc=c[mid]-c[i-1];

    return now-sc;
}

inline void sol(int l,int r,int ql,int qr){
    if(l>r){
        return;
    }

    pr be={-1e18,0};
    int mid=(l+r)>>1;

    rep(i,ql,min(mid-m+1,qr)){
        int res=calc(i,mid);

        be=max(be,{res,i});
    }

    // cout<<mid<<" from "<<be.se<<' '<<be.fi<<"\n";

    pre[mid]=be.se;
    ans=max(ans,be.fi);

    sol(l,mid-1,ql,be.se);
    sol(mid+1,r,be.se,qr);
}

signed main(){
    // freopen("Trade.in","r",stdin);
    // freopen("Trade.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n>>m;

    rep(i,1,n){
        cin>>c[i];
        c[i]+=c[i-1];
    }

    rep(i,1,n){
        cin>>s[i];
        t.ins(rt[i-1],rt[i],1,1e9+1,s[i]);
    }

    sol(m,n,1,n);

    cout<<ans<<"\n";

    b.build(1,1,n);

    pre[0]=1;
    int i=m,j=0;

    while(i<=n){
        if(calc(pre[i],i)==ans){
            b.upd(pre[i],i,1,1,n,t.qry(rt[pre[i]-1],rt[i],1,1e9+1,m));

            rep(k,pre[j],pre[i]-1){
                if(calc(k,i)==ans){
                    b.upd(k,i,1,1,n,t.qry(rt[k-1],rt[i],1,1e9+1,m));
                }
            }

            j=i;
        }

        i++;
    }

    rep(i,1,n){
        cout<<(s[i]>=b.ask(i,i,1,1,n));
    }

    return 0;
}
```

---

## 作者：Mirasycle (赞：1)

全局最优区间选择问题，肯定猜测最优区间满足决策单调性，事实上这种区间前 $k$ 大之和状物（本题还多了一个减去区间 $c$ 之和）也确实具有决策单调性。于是可以直接用主席树维护区间前 $k$ 大之和，然后分治计算答案。

第二问就很神秘了。需要找到最优区间，然后标记区间内那些 $\ge k$ 的数。可是最坏情况下可能的区间会有 $O(n^2)$ 个，我们难以一一处理。这个时候很多区间都是无用的，我们需要找到一些有用区间。

考虑两个最优区间 $[x_1,y_1]$ 和 $[x_2,y_2]$，满足 $x_1<x_2\le y_2<y_1$，这个时候其实 $[x_1,y_1]$ 是无用的。

> 由于本题具有决策单调性，所以根据四边形不等式，有 $w(x_1,y_2)+w(x_2,y_1)\ge w(x_1,y_1)+w(x_2,y_2)=2\times \max w(l,r)$，又因为 $w(x_1,y_2)\le \max w(l,r)$ 且 $w(x_2,y_1)\le \max w(l,r)$，所以可以得到 $w(x_1,y_2)=w(x_2,y_1)=\max w(l,r)$，故区间 $[x_1,y_2]$ 和区间 $[x_2,y_1]$ 也是最优区间。对于一个小区间，竞争少，所以一个数成为前 $k$ 大的可能性也就更大，所以区间 $[x_1,y_1]$ 是不如拆分出的区间 $[x_1,y_2]$，$[x_2,y_1]$，$[x_2,y_2]$。

这是一个双指针状物，所以对于每个 $i$，我们只需要求出其最大的决策点 $p_i$ 即可。同时注意我们上面是 $y_2<y_1$，所以除了 $[p_i,i]$ 之外，还有一些 $r=i$ 的区间，把所有 $l\in[p_j,p_i]$ 之间的最优区间都加进去即可（其中 $j$ 是 $i$ 前面第一个最优的右端点）。这样子我们一共形成了 $O(n)$ 个有效区间，我们只需要标记这些区间中的区间前 $k$ 大值即可。

于是就转化为有若干区间操作 $(l,r,v)$，要求覆盖区间内 $\ge v$ 的数字，可以对于 $v$ 进行扫描线之后用并查集直接合并即可。

时间复杂度 $O(n\log ^2n)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int V=1e9;
const int maxn=2.5e5+10;
const ll inf=1e16;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
int n,K,b[maxn],p[maxn],d[maxn],rt[maxn]; 
ll a[maxn],f[maxn],ans;
struct node{
	int l,r,v;
	bool operator < (const node &rhs){ return v<rhs.v; }
}; vector<node> vec;
bool cmp(int x,int y){ return b[x]<b[y]; }
struct SegmentTree{
	#define mid (l+r>>1)
	int val[maxn<<6],ls[maxn<<6],rs[maxn<<6],tot=0; ll sum[maxn<<6];
	void pushup(int p){ val[p]=val[ls[p]]+val[rs[p]]; sum[p]=sum[ls[p]]+sum[rs[p]]; }
	void build(int &p,int q,int l,int r,int x){
		p=++tot; ls[p]=ls[q]; rs[p]=rs[q];
		val[p]=val[q]; sum[p]=sum[q]; 
		if(l==r){ val[p]++; sum[p]+=x; return ; }
		if(x<=mid) build(ls[p],ls[q],l,mid,x);
		else build(rs[p],rs[q],mid+1,r,x);
		pushup(p);
	}
	ll query(int p,int q,int l,int r,int k){
		if(l==r) return 1ll*k*l; 
		int z=val[rs[q]]-val[rs[p]];
		if(z>=k) return query(rs[p],rs[q],mid+1,r,k);
		else return sum[rs[q]]-sum[rs[p]]+query(ls[p],ls[q],l,mid,k-z);
	}
	int get(int p,int q,int l,int r,int k){
		if(l==r) return l; 
		int z=val[rs[q]]-val[rs[p]];
		if(z>=k) return get(rs[p],rs[q],mid+1,r,k);
		else return get(ls[p],ls[q],l,mid,k-z);
	}
}seg;
struct DSU{
	int fa[maxn];
	void init(){ for(int i=1;i<=n+1;i++) fa[i]=i; }
	int find(int x){ return x==fa[x]?x:fa[x]=find(fa[x]); }
	void merge(int u){ fa[u]=u+1; }
}dsu;
ll calc(int l,int r){
	if(r-l+1<K) return -inf;
	return -a[r]+a[l-1]+seg.query(rt[l-1],rt[r],1,V,K);  
}
void solve(int pl,int pr,int l,int r){
	if(l>r) return ;
	p[mid]=pl; f[mid]=-inf+1;
	for(int i=pl;i<=min(pr,mid);i++)
		if(f[mid]<=calc(i,mid)){
			f[mid]=calc(i,mid);
			p[mid]=i;
		}
	solve(pl,p[mid],l,mid-1); solve(p[mid],pr,mid+1,r);
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>K;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1];
	for(int i=1;i<=n;i++) cin>>b[i],seg.build(rt[i],rt[i-1],1,V,b[i]);
	solve(1,n,1,n); ans=f[max_element(f+1,f+1+n)-f]; int lst=0; p[0]=1;
	for(int i=1;i<=n;i++){
		if(f[i]!=ans) continue;
		for(int j=p[lst];j<=p[i];j++)
			if(calc(j,i)==ans) vec.pb((node){j,i,seg.get(rt[j-1],rt[i],1,V,K)});
		lst=i;
	}
	for(int i=1;i<=n;i++) p[i]=i;
	sort(p+1,p+1+n,cmp); sort(vec.begin(),vec.end());
	int to=0; dsu.init();
	for(auto z:vec){
		int val=z.v;
		while(b[p[to+1]]<val&&to<n) dsu.merge(p[++to]);
		for(int i=dsu.find(z.l);i<=z.r;i=dsu.find(i+1)){ d[i]=1; dsu.merge(i); }
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++) cout<<d[i];
	return 0;
}
```

---

## 作者：tzl_Dedicatus545 (赞：1)

考虑如何计算答案。

首先肯定是求 $a_r-a_{l-1}-\max_k{b[l:r]}$ 状物。这个东西显然有决策单调性。决策单调性分治即可。

然后考虑咋构造方案。

你肯定是想找到一些小区间 $[l_i,r_i]$，然后覆盖掉每个区间里的非严格前 $k$ 大。覆盖的过程是简单的，你大概只用找到第 $k$ 打，然后做一次区间 `chkmin` 就行，询问的时候就是查 $b_i$ 是否大于 `chkmin` 出来的值。

然后关于怎么找到这个区间，你可以感性理解一下包含一定是不优的。

严谨证明的话考虑区间 $l_1<l_2<r_2<r_1$，决策单调性一下你发现两两都是合法区间，那么我们只用求 $[l_2,r_2],[l_1,r_2],[l_2,r_1]$ 即可。

复杂度 $O(n\log^2n)$

---

## 作者：JWRuixi (赞：1)

## P9732 [CEOI2023] Trade

### 题意

给定长度为 $n$ 的序列 $\{a_n\}$，$\{b_n\}$，和常数 $k$，你可以进行如下操作：

- 选择一个长度 $\ge k$ 的区间 $[L, R]$，获得收益 $-\sum\limits_{i = L}^R a_i$；
- 在 $[L, R]$ 内选定 $k$ 个互不相同的位置 $p_{1, \dots, k}$，获得收益 $\sum\limits_{i \le k} b_{p_i}$。

求可能的最大收益。

### 分析

对于每一个对应最优答案的区间，那么区间 $[L, R]$ 中的一个点 $i$ 合法当且仅当 $b_i \ge \max_k(L, R)$。

记 $S_k(L, R)$ 为 $b_{L, \dots, R}$ 的前 $k$ 大值的和。发现 $S_k$ 是满足四边形不等式的，也就是说记 $w(L, R) = S_k(L, R) - \sum\limits_{L \le i \le R} a_i$，那么 $w$ 也是满足四边形不等式的。

称 $R$ 对应 $L$，当且仅当 $w(L, R) = \max\limits_{L + k - 1\le i \le n} w(L, i)$。那么可以发现对于递增的 $R$，其对应的 $L$ 的极值也是单调递增的。

>  证明：记 $L_1$ 为 $R_1$ 对应的 $L$ 的最小值，$L_2$（$L_2 < L_1$）为 $R_2$（$R_2 > R_1$）对应的 $L$ 的最小值。那么有 $w(L_1, R_1) + w(L_2, R_2) \le w(L_1, R_2) + w(L_2, R_1)$，若：
>
> - $w(L_1, R_2) < w(L_1, R_1)$，则 $w(L_2, R_1) > w(L_2, R_2)$，与“$R_2$ 对应 $L_2$”矛盾；
> - $w(L_1, R_2) = w(L_1, R_1)$，则 $w(L_2, R_1) = w(L_2, R_2)$，则 $R_1$ 对应 $L_2$，与”$R_1$ 对应 $L_1$“矛盾；
> - $w(L_1, R_2) > w(L_1, R_1)$，与“$R_1$ 对应 $L_1$”矛盾。

于是用二分栈维护指针移动，用主席树计算 $S_k$，可以做到 $\mathcal O(n \log^2 n)$ 求解第一问。

我们发现如果某一个对应最优解的区间 $[L, R]$ 包含了一个更小的最优区间 $[L', R']$，那么就可以忽略前者。原因是：$[L, R']$ 和 $[L', R]$ 都是最优区间，且两者 $\max_k$ 都不大于 $[L, R]$。

于是我们要求满足区间不包含。考虑对右端点扫描线，记此时合法区间集合为 $S$，$l = \max\limits_{[L, R] \in S} L$。设当前扫到 $r$，我们发现我们不需要考虑左端点小于 $l$ 的可能合法区间。而对于每个 $L$，我们只需要记录其第一次成为合法区间的时间节点，也就是最小的对应它的 $R$。

于是考虑二分栈对于每个 $R$ 求出一个区间 $[A_R, B_R]$ 表示：$\forall L \in [A_R, B_R]$，$R$ 是最小的对应 $L$ 的右端点。再在扫描线的过程中记录 $l = \max\limits_{[L, R] \in S} L$，那么对于当前扫到的 $r$，只用考虑 $[l, r]$ 和 $[i, r]$（$A_r \le i \le B_r$）。

时间复杂度 $\mathcal O(n\log^2 n)$。

## Code

代码：<https://pastebin.com/M4g9R0zP>。

---

## 作者：Otomachi_Una_ (赞：0)

水题解/se

即 $f(l,r)$ 表示选区间 $[l,r]$ 能带来的收益。$f$ 能通过可持久化线段树做到 $\mathcal O(\log)$ 在线求。

$f$ 是满足四边形不等式的，求最值能直接决策单调性。这样子就能通过第一问。

第二问，相当于 $i$ 在某个 $f(l,r)$ 最优的区间里，$b_i$ 排到了前 $k$ 大。在在决策单调性的时候维护一次啊最优区间即可。

---

