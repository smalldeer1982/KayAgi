# Tram

## 题目背景

电车开了，他的声音在我的脑海中萦绕不散：

「留下来，跟我来。」

我回头去看车站，他不见了。

我在德辅道寻找他的身影。

路人不多，但他却消失了。

我把窗拉下来，微风轻拂我的脸。

他到哪儿去了？

路人、街道、高楼大厦。

在我身边轻轻地流走。



## 题目描述

你就要出道了！

你的教练和同学为你联系了摄影师，你们来到德辅道边拍宣传照。

街上一共有 $n$ 幢楼房，从左到右排成一列，从 $1$ 到 $n$ 编号，编号为 $i$ 的楼房的高度是 $a_i$。

一张照片可以用二元组 $(l,r)$ 描述，其中 $1\le l\le r\le n$，这张照片中包含了编号在 $[l,r]$ 之间的所有楼房。

摄影师认为，一张照片是美丽的，当且仅当其同时满足下面的两个条件：

- 对于任意的 $i<j<k$，如果高度为 $i$ 和 $k$ 的楼房都在照片中出现过，那么高度为 $j$ 的楼房也在照片中出现过。
- 对于任意的 $i$，高度为 $i$ 的楼房要么不出现在照片中，要么在照片中出现恰好 $i$ 次。

摄像师问你，一共能拍出多少不同的美丽的照片呢？

两张照片 $(l_1,r_1)$ 和 $(l_2,r_2)$ 不同，当且仅当 $l_1\ne l_2$ 或 $r_1\ne r_2$。

## 说明/提示

**本题采用捆绑测试**。你只有通过 subtask 中的所有测试点才能获得该 subtask 的分数。

- Subtask 1(10 points)：$n\le 200$；
- Subtask 2(5 points)：$n\le 1000$；
- Subtask 3(10 points)：$n\le 6000$；
- Subtask 4(20 points)：$n\le 3\times 10^4$；
- Subtask 5(30 points)：$n\le 10^5$；
- Subtask 6(25 points)：$n\le 10^6$。


对于所有数据满足：$1\le n,a_i\le 10^6$。

注意答案的大小可能超过 $32$ 位有符号整数的范围。

本题输入数据量较大，请使用较快的读入方式。

## 样例 #1

### 输入

```
10
2 2 1 1 2 2 3 1 3 3 ```

### 输出

```
8```

# 题解

## 作者：disposrestfully (赞：4)

满足第二个条件的区间不会很多,而判断这样的一个区间是否满足第一个条件只要查询最值,所以我们只需要找出所有满足第二个条件的区间,这可以枚举左端点,用线段树维护合法的右端点集合,复杂度$O(Ans\times logn)$.

我们现在需要估计满足第二个条件的区间到底有多少个,一个显然的上界是$O(n\sqrt{n})$,但这个界很松.

考虑把序列中所有数按照权值从小到大加入.假设我们现在加入的是权值为$x$的所有数,一共$k$个,在加入之前序列中合法子区间的数量是$Cnt$.现在我们考虑加入的数对答案的影响,把所有区间分成下面几类.

>原本的合法区间,没有被加入任何数.
>
>原本的合法区间,中间恰好被加入了$x$个$x$.

以上这些区间不以$x$开头也不以$x$结尾,至多$Cnt$个.

>   原本的合法区间,在开头加上了$x$个$x$
>
>   原本的合法区间,在末尾加上了$x$个$x$
>
>   以$x$开头结尾的合法区间.

第三类区间的数量至多是$k-x+1$.

将连续的$x$个$x$称为一块,考虑相邻的两个块,如果它们之间的距离是$d$,那么它们至多会对区间个数产生$2\times min(d,x-1)$的贡献.所以第一二类区间的数量至多是$(\frac{k}{x}+1)\times 2\times (x-1)$.

容易看出最终合法区间的个数是$O(n)$级别的.

线段树，$O(nlog{n}).$

PS：这题实现的时候需要注意一下常数问题，不恰当的实现方式可能会导致2到3倍~~（甚至30倍）~~的常数。而另外一些log做法的常数似乎也要这个级别......

bonus:找到线性做法。

以下代码来自EndSaH

```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using LL = long long;

const int maxN = 1e6 + 5;

int n, m, ans, rig;
vector<int> pos[maxN];
int a[maxN];

template<typename _Tp>
inline bool Chkmin(_Tp& x, const _Tp& y)
{ return x > y ? x = y, true : false; }

template<typename _Tp>
inline bool Chkmax(_Tp& x, const _Tp& y)
{ return x < y ? x = y, true : false; }

int read()
{
    int x = 0;
    char ch;
    while (!isdigit(ch = getchar()));
    while (x = x * 10 + (ch & 15), isdigit(ch = getchar()));
    return x;
}

namespace RMQ
{
    int lg2[maxN];
    int mini[22][maxN], maxi[22][maxN];

    void Init()
    {
        for (int i = 2; i <= n; ++i)
            lg2[i] = lg2[i >> 1] + 1;

        for (int i = 1; i <= n; ++i)
            mini[0][i] = maxi[0][i] = a[i];
        for (int i = 1; i < 21; ++i)
            for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            {
                mini[i][j] = min(mini[i - 1][j], mini[i - 1][j + (1 << (i - 1))]);
                maxi[i][j] = max(maxi[i - 1][j], maxi[i - 1][j + (1 << (i - 1))]);
            }
    }

    int Query_min(int l, int r)
    {
        int t = lg2[r - l + 1];
        return min(mini[t][l], mini[t][r - (1 << t) + 1]);
    }

    int Query_max(int l, int r)
    {
        int t = lg2[r - l + 1];
        return max(maxi[t][l], maxi[t][r - (1 << t) + 1]);
    }

    bool Check(int l, int r)
    {
        //cout << l << ' ' << r << endl;
        int a = Query_min(l, r), b = Query_max(l, r);
        return LL(a + b) * (b - a + 1) / 2 == r - l + 1;
    }
}

namespace SEG
{
    int maxi[maxN * 4], tag[maxN * 4];

    inline void add(int x, int addv)
    { maxi[x] += addv, tag[x] += addv; }

    inline void Pushdown(int x)
    {
        if (tag[x])
        {
            add(x << 1, tag[x]), add(x << 1 | 1, tag[x]);
            tag[x] = 0;
        }
    }

    inline void Pushup(int x)
    { maxi[x] = max(maxi[x << 1], maxi[x << 1 | 1]); }

    void Add(int ql, int qr, int addv, int l = 1, int r = n, int x = 1)
    {
        if (ql <= l and r <= qr)
        {
            add(x, addv);
            return;
        }

        int mid = (l + r) >> 1;
        Pushdown(x);
        if (ql <= mid)
            Add(ql, qr, addv, l, mid, x << 1);
        if (mid < qr)
            Add(ql, qr, addv, mid + 1, r, x << 1 | 1);
        Pushup(x);
    }

    void Find(int l = 1, int r = n, int x = 1)
    {
        if (maxi[x] != m)
            return;
        if (l == r)
        {
            ans += RMQ::Check(l, rig);
            return;
        }
        int mid = (l + r) >> 1;
        Pushdown(x);
        Find(l, mid, x << 1);
        Find(mid + 1, r, x << 1 | 1);
    }
}

int main()
{
   // freopen("tram.in", "r", stdin);
   // freopen("tram.out", "w", stdout);
    ios::sync_with_stdio(false);
    n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read(), m = max(m, a[i]);
    RMQ::Init();

    for (int i = 1; i <= m; ++i)
        pos[i].push_back(0);

    for (int i = 1; i <= n; ++i)
    {
        rig = i;
        int t = a[i];
        SEG::Add(i, i, m);
        SEG::Add(pos[t].back() + 1, i, -1);
        pos[t].push_back(i);

        if ((int)pos[t].size() >= t + 1)
        {
            int a = pos[t].size() - t - 1;
            SEG::Add(pos[t][a] + 1, pos[t][a + 1], 1);
            if (a > 0)
                SEG::Add(pos[t][a - 1] + 1, pos[t][a], -1);
        }
        SEG::Find();
    }
    cout << ans << endl;

    return 0;
}

---

## 作者：YLWang (赞：3)

我们从题目的特殊性入手。发现题目提醒你答案可能会超过 int。冷静分析一波发现答案上界是 $O(n\sqrt{n})$ 级别的，且大多数情况是 $O(n)$ 的。

我们再发现去掉值域连续的性质之后答案上界是不会变的。

于是拿一个线段树维护每个数可以取的区间，暴力把所有可能的位置都拿出来就可以了。

复杂度 $O(n\sqrt{n}\log n)$，且多数情况是 $O(n\log n)$。

```cpp
const int MAXN = 1e6 + 5;
int smn[MAXN][20], smx[MAXN][20], n, a[MAXN], lg2[MAXN], rk[MAXN];
vector < int > pos[MAXN];
inline int check(int l, int r) {
	int d = lg2[r - l + 1], mn = min(smn[l][d], smn[r - (1 << d) + 1][d]), mx = max(smx[l][d], smx[r - (1 << d) + 1][d]);
	return 1ll * (mx + mn) * (mx - mn + 1) == 2 * (r - l + 1);
}
struct SMT {
	static const int N = MAXN << 2;
	#define ls (k << 1)
	#define rs (k << 1 | 1)
	#define mid ((l + r) >> 1)
	int mn[N], tag[N];
	inline void pushr(int k, int v) {
		mn[k] += v, tag[k] += v;
	}
	inline void pushdown(int k) {
		if(tag[k])
			pushr(ls, tag[k]), pushr(rs, tag[k]), tag[k] = 0;
	}
	void update(int k, int l, int r, int ql, int qr, int val) {
		if(l == ql && r == qr) return pushr(k, val);
		pushdown(k);
		if(qr <= mid) update(ls, l, mid, ql, qr, val);
		else if(mid < ql) update(rs, mid+1, r, ql, qr, val);
		else update(ls, l, mid, ql, mid, val), update(rs, mid+1, r, mid+1, qr, val);
		mn[k] = min(mn[ls], mn[rs]);
	}
	int query(int k, int l, int r, int ql, int qr) { 
		if(mn[k]) return 0;
		if(l == r) return check(l, qr);
		pushdown(k);
		int res = 0;
		if(mid >= ql) res += query(ls, l, mid, ql, qr);
		if(mid < qr) res += query(rs, mid+1, r, ql, qr); 
		return res;
	}
}tr;
signed main()
{
	#ifndef ONLINE_JUDGE 
    	file("pro");
    #endif
    n = read();
    For(i, 1, 1000000) pos[i].pb(0);
    For(i, 1, n) smn[i][0] = smx[i][0] = a[i] = read(), pos[a[i]].pb(i), rk[i] = pos[a[i]].size() - 1;
    lg2[1] = 0; For(i, 2, n) lg2[i] = lg2[i >> 1] + 1;
    For(j, 1, 19) {
		For(i, 1, (n - (1 << (j - 1)))) {
			smn[i][j] = min(smn[i][j - 1], smn[i + (1 << (j - 1))][j - 1]);
			smx[i][j] = max(smx[i][j - 1], smx[i + (1 << (j - 1))][j - 1]);
		}
	}
	int ans = 0;
	For(i, 1, n) {
		tr.update(1, 1, n, pos[a[i]][rk[i]-1] + 1, i, 1);
		if(rk[i] < a[i]) continue;
		tr.update(1, 1, n, pos[a[i]][rk[i] - a[i]] + 1, pos[a[i]][rk[i] - a[i] + 1], -1);
		if(rk[i] != a[i]) tr.update(1, 1, n, pos[a[i]][rk[i] - a[i] - 1] + 1, pos[a[i]][rk[i] - a[i]], 1);
		ans += tr.query(1, 1, n, 1, i);
	}
	cout << ans << endl;
    return FastIO::Fflush(), 0;
}
/*

*/


```

---

## 作者：lprdsb (赞：1)

### 题意

- 给定一个序列，定义一个好的区间：
  1. 对于区间里出现的数$a_i$恰好出现$a_i$次
  2. 区间里的数的值域连续

- 求好的区间数量

考虑以某个点$i$结束的好的区间的最后起始位置，然后向前拓展，发现最多拓展$n$次，并且每次拓展一定会将值域向小/大拓展至少1，考虑到从$1$一直加到$\sqrt n$就会大于$n$，所以说好的区间不会超过$n\sqrt n$级别

那么只需要$o(1)$或者$o(\log n)$的复杂度内找到一个可行位置再加进答案就行

于是从左往右，每次对当前数维护可行的区间就好

具体的操作是，假设当前数为$x$那么找到前$x$个的位置，这中间是不能选的，以及前$x+1$个$x$之前的位置也是不能选的

所以就可以线段树，每次将不能选的位置$+1$，维护区间最小值，然后在线段树上二分即可

```cpp
#include<bits/stdc++.h>
#define For(i, a, b) for(int i = (a), en = (b); i <= en; ++i)
#define Rof(i, a, b) for(int i = (a), en = (b); i >= en; --i)
#define Tra(u, i) for(int i = hd[u]; ~i; i = e[i].net)
#define cst const
#define LL long long
#define DD double
#define LD long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define inf 0x3f3f3f3f
#define Inf 0x3f3f3f3f3f3f3f3f
#define eps 1e-12
#define maxn 1000000
using namespace std;

int n, a[maxn + 5], as = 0, pre[maxn + 5], net[maxn + 5], to[maxn + 5], cnt[maxn + 5];
map<int, int> ma;
void chkmn(int &x, int y){if(x > y) x = y;}
void chkmx(int &x, int y){if(x < y) x = y;}
int tr[2][maxn + 5];
void ins(int ty, int x, int y){
	x = maxn - x + 1;
	while(x <= maxn) ty ? chkmx(tr[ty][x], y) : chkmn(tr[ty][x], y), x += x & -x;
}
int que(int ty, int x){
	x = maxn - x + 1; int asi = ty ? 0 : inf;
	while(x) ty ? chkmx(asi, tr[ty][x]) : chkmn(asi, tr[ty][x]), x -= x & -x;
	return asi;
}
struct Node{int mn, lpr;} poi[4 * maxn + 5];
struct Tree{
	#define ls rt << 1
	#define rs rt << 1 | 1
	#define mn(rt) poi[rt].mn
	#define lpr(rt) poi[rt].lpr
	void upd(int rt){mn(rt) = min(mn(ls), mn(rs));}
	void mson(int rt, int x){
		mn(rt) += x;
		lpr(rt) += x;
	}
	void spr(int rt){
		if(!lpr(rt)) return;
		mson(ls, lpr(rt));
		mson(rs, lpr(rt));
		lpr(rt) = 0;
	}
	void mdy(int rt, int nl, int nr, int ql, int qr, int x){
		if(ql > qr) return;
		if(ql <= nl && qr >= nr) return mson(rt, x);
		spr(rt);
		int mid = nl + nr >> 1;
		if(ql <= mid) mdy(ls, nl, mid, ql, qr, x);
		if(qr > mid) mdy(rs, mid + 1, nr, ql, qr, x);
		upd(rt);
	}
	void sol(int rt, int nl, int nr, int ql, int qr){
		if(mn(rt)) return;
		if(nl == nr){
			int mn = que(0, nl), mx = que(1, nl);
			if((mn + mx) * (mx - mn + 1) / 2 == qr - nl + 1) as++;
			return;
		}
		spr(rt);
		int mid = nl + nr >> 1;
		if(ql <= mid) sol(ls, nl, mid, ql, qr);
		if(qr > mid) sol(rs, mid + 1, nr, ql, qr);
	}
	void quee(int rt, int nl, int nr){
		if(nl == nr) return (void)(cout << mn(rt) << " ");
		spr(rt);
		int mid = nl + nr >> 1;
		quee(ls, nl, mid); quee(rs, mid + 1, nr);
	}
} tr1;

template <class T>
void read(T &x){
	char ch;
	bool ok;
	for(ok = 0, ch = getchar(); !isdigit(ch); ch = getchar()) if(ch == '-') ok = 1;
	for(x = 0; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	if(ok) x = -x;
}

void mdy(int x, int y){
	if(!x) return;
	if(cnt[x] > a[x]) tr1.mdy(1, 1, n, to[x] + 1, x, y), tr1.mdy(1, 1, n, 1, pre[to[x]], y);
	else if(cnt[x] == a[x]) tr1.mdy(1, 1, n, to[x] + 1, x, y);
	else tr1.mdy(1, 1, n, 1, x, y);
	ins(0, x, a[x]);
	ins(1, x, a[x]);
	//if(x == 2) cout << que(0, x) << endl;
}

int main(){
	//freopen("in", "r", stdin);
	memset(tr[0], inf, sizeof tr[0]);
	read(n);
	For(i, 1, n){
		read(a[i]);
		net[pre[i] = ma[a[i]]] = i;
		ma[a[i]] = i;
		cnt[i] = cnt[pre[i]] + 1;
		if(a[i] == 1) to[i] = i;
		else if(cnt[i] > a[i]) to[i] = net[to[pre[i]]];
		else if(cnt[i] == a[i]) to[i] = to[pre[i]];
		else if(cnt[i] == 1) to[i] = i;
		else to[i] = to[pre[i]];
		mdy(pre[i], -1);
		mdy(i, 1);
		tr1.sol(1, 1, n, 1, i);
		/*tr1.quee(1, 1, n);
		puts("");*/
	}
	printf("%d\n", as);
	return 0;
}
```

---

