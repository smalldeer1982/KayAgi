# Split

## 题目描述

Let's call an array $ b_1, b_2, \ldots, b_m $ ( $ m \ge 2 $ ) good if it can be split into two parts such that all elements in the left part are strictly smaller than all elements in the right part. In other words, there must exist an index $ 1 \le i < m $ such that every element from $ b_1, \ldots, b_i $ is strictly smaller than every element from $ b_{i+1}, \ldots, b_m $ .

Given an array $ a_1, a_2, \ldots a_n $ consisting of distinct integers from $ 1 $ to $ n $ . There are $ q $ queries. Each query consists of two numbers $ l $ and $ r $ . For each query, determine whether the array $ a_l, a_{l+1}, \ldots, a_r $ is good.

## 说明/提示

In the first example:

- The array $ [3,2,1,4,5] $ can be split into two parts: $ [3,2,1] $ and $ [4,5] $ .
- The array $ [3,2,1] $ cannot be split into two parts such that all elements in the left part are smaller than all elements in the right part.
- The array $ [3,2,1,4] $ can be split into two parts: $ [3,2,1] $ and $ [4] $ .
- The array $ [3,2] $ cannot be split into two parts such that all elements in the left part are smaller than all elements in the right part.
- The array $ [2,1,4,5] $ can be split into two parts: $ [2,1] $ and $ [4,5] $ .

In the second example:

- The array $ [2,4,3] $ can be split into two parts: $ [2] $ and $ [4,3] $ .
- The array $ [6,2,4,3,5] $ cannot be split into two parts such that all elements in the left part are smaller than all elements in the right part.
- The array $ [4,3,5] $ can be split into two parts: $ [4,3] $ and $ [5] $ .

## 样例 #1

### 输入

```
5
3 2 1 4 5
5
1 5
1 3
1 4
1 2
2 5```

### 输出

```
Yes
No
Yes
No
Yes```

## 样例 #2

### 输入

```
6
1 6 2 4 3 5
3
3 5
2 6
4 6```

### 输出

```
Yes
No
Yes```

# 题解

## 作者：樱雪喵 (赞：16)

## Description

定义一个序列是好的，当且仅当它存在某种划分成左右两部分的方案，使左半部分的最大值严格小于右半部分的最小值。

现给出长度为 $n$ 的序列 $a$，保证 $a$ 是一个 $1\sim n$ 的排列。  
$q$ 次询问，每次询问 $a$ 的子区间 $[l,r]$ 是否为好的序列。

$n,q\le 3\times 10^5$。

## Solution

考虑对于一个确定的序列怎么搞。我们枚举一个值域分界点 $i$，把 $\le i$ 的分在一边，$>i$ 的分在另一边，判断它们是否恰好是原序列的某种划分。

然而这个东西没有单调性，从其它角度优化这个过程。  
我们对于每个**下标** $i$，不考虑具体的询问，而是考虑能使 $a_i$ 成为合法的**值域**分界点的区间 $[l,r]$ 中 $l,r$ 的范围。

首先，$a_i$ 一定在左半部分，且是左半部分的最大值。那么令 $x$ 为 $i$ 向左找第一个 $a_x>a_i$ 的位置。则左端点有限制 $x< l\le i$。  
右半部分需满足全部值大于 $a_i$。那么令 $y$ 为 $i$ 右侧第一个 $a_y>a_i$ 的位置，有限制 $r\ge y$。同时令 $z$ 为 $y$ 右侧第一个 $a_z<a_i$ 的位置，有限制 $y\le r < z$。

把询问 $[l,r]$ 看作点的坐标，这是一个矩阵加单点查询问题，使用树状数组 + 扫描线维护。

```cpp
const int N=3e5+5;
int n,m,a[N],pos[N],ans[N],tot;
struct node {int tp,l,r,x,k,y,id;}q[N<<2];
set<int> ls,rs;
il bool cmp(node x,node y)
{
    if(x.x!=y.x) return x.x<y.x;
    else return x.tp<y.tp;
}
struct BIT
{
    int tr[N];
    il void modify(int x,int k) {for(;x<=n;x+=x&(-x)) tr[x]+=k;}
    il void add(int l,int r,int k) {modify(l,k),modify(r+1,-k);} 
    il int query(int x) {int res=0;for(;x;x-=x&(-x)) res+=tr[x];return res;}
}tr;
int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),pos[a[i]]=i,rs.insert(i);
    for(int I=1;I<=n;I++)
    {
        int i=pos[I];
        rs.erase(i);
        auto itx=rs.lower_bound(i),ity=rs.upper_bound(i);
        int x=(itx==rs.begin()||itx==rs.end())?0:*prev(itx);
        int y=(ity==rs.end())?n+1:*ity;
        auto itz=ls.upper_bound(y);
        int z=(itz==ls.end())?n+1:*itz;
        q[++tot]={1,x+1,i,y,1,0,0};
        q[++tot]={1,x+1,i,z,-1,0,0};
        ls.insert(i);
    }
    m=read();
    for(int i=1;i<=m;i++)
    {
        int l=read(),r=read();
        q[++tot]={2,0,0,r,0,l,i};
    }
    sort(q+1,q+tot+1,cmp);
    for(int i=1;i<=tot;i++)
    {
        if(q[i].tp==1) tr.add(q[i].l,q[i].r,q[i].k);
        else ans[q[i].id]=tr.query(q[i].y);
    }
    for(int i=1;i<=m;i++) printf(ans[i]?"Yes\n":"No\n");
    return 0;
}
```

---

## 作者：yhk1001 (赞：11)

提供一个在线倍增做法。

考虑从左向右扫过区间，只需检查 $\max \left\{ a_l, a_{l + 1}, \dots, a_i \right\} < \min \left\{ a_{i + 1}, a_{i + 2}, \dots, a_r \right\}$ 是否成立。显然不等式左侧一定是 $\left[ l, r \right]$ 的前缀最大值，如果固定 $\max$，那么不等式右侧的区间长度越小越好，因为 $\min$ 不降。

为方便起见，令 $a_{n + 1} = \infty$。

设 $f_i$ 表示 $i$ 之后第一个大于 $a_i$ 的数的位置，则 $l, f_l, f_{f_l}, \dots$ 就是 $\left[ l, r \right]$ 的所有前缀 $\max$ 位置。不妨设 $p$ 是一个前缀 $\max$，只需检查 $\min \left\{ a_{f_p}, a_{f_p + 1}, \dots, a_r \right\}$ 是否大于 $a_p$。令 $g_i$ 表示最大的 $j$，使 $\min \left\{ a_{f_i}, a_{f_i + 1}, \dots, a_j \right\} > a_i$。条件转化为 $g_p \geqslant r$。只要有一个 $p$ 满足要求，$\left[ l, r \right]$ 就合法，因此只需 $\max \left\{ g_l, g_{f_l}, g_{f_{f_l}}, \dots \right\} > r$。

$f$ 可以倒序单调栈处理，$g$ 可以 st 表求区间 $\min$ 配合二分解决。其余部分可以预处理 $jmp_{i, j} / Max_{i, j}$ 表示从 $i$ 开始，跳 $2^j$ 次 $f$ 到达的位置 / 途中最大 $g$。都是显然的，可以配合代码看看。

预处理最好处理到 $n + 1$，避免不必要的麻烦。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

// #define Debug
// #define LOCAL
// #define TestCases

const int N = 3e5, Lg = 18;

int n, q;
int a[N + 5];

int stk[N + 5], top;
int f[N + 5];

int st[N + 5][Lg + 5];
int g[N + 5];
int queryMin(int l, int r)
{
	int k = log2(r - l + 1);
	return min(st[l][k], st[r - (1 << k) + 1][k]);
}

int jmp[N + 5][Lg + 5], Max[N + 5][Lg + 5];
bool calc(int l, int r)
{
	int mx = 0;
	for (int k = Lg; k >= 0; k--)
	{
		if (jmp[l][k] > r)
			continue;
		mx = max(mx, Max[l][k]);
		l = jmp[l][k];
	}
	return mx >= r;
}

void solve()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);

	a[n + 1] = N + 1;
	stk[++top] = n + 1;
	for (int i = n; i > 0; i--)
	{
		while (a[stk[top]] < a[i])
			top--;
		f[i] = stk[top];
		stk[++top] = i;
	}

	for (int i = 1; i <= n + 1; i++)
		st[i][0] = a[i];
	for (int k = 1; (1 << k) <= n + 1; k++)
		for (int i = 1; i + (1 << k) - 1 <= n + 1; i++)
			st[i][k] = min(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
	for (int i = 1; i <= n; i++)
	{
		int l = f[i], r = n + 1;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (queryMin(f[i], mid) > a[i])
			{
				g[i] = mid;
				l = mid + 1;
			}
			else
				r = mid - 1;
		}
	}

	f[n + 1] = g[n + 1] = n + 1;
	for (int i = 1; i <= n + 1; i++)
	{
		jmp[i][0] = f[i];
		Max[i][0] = g[i];
	}
	for (int k = 1; k <= Lg; k++)
	for (int i = 1; i <= n + 1; i++)
	{
		jmp[i][k] = jmp[ jmp[i][k - 1] ][k - 1];
		Max[i][k] = max(Max[i][k - 1], Max[ jmp[i][k - 1] ][k - 1]);
	}

	scanf("%d", &q);
	for (int i = 1, l, r; i <= q; i++)
	{
		scanf("%d%d", &l, &r);
		if (calc(l, r))
			puts("Yes");
		else
			puts("No");
	}
	return ;
}

int main()
{
	#ifdef LOCAL
	freopen("data.in", "r", stdin);
	freopen("mycode.out", "w", stdout);
	#endif
	
	int T = 1;
	
	#ifdef TestCases
	scanf("%d", &T);
	#endif
	
	while (T--)
		solve();
	return 0;
}
```

---

## 作者：EuphoricStar (赞：4)

$a_l, a_{l + 1}, \ldots a_r$ 是好的当且仅当 $\exists k \in [l, r - 1], \max\limits_{i = l}^k a_i < \min\limits_{i = k + 1}^r a_i$，称此时的 $k$ 为分割点。

对 $r$ 扫描线，单调栈维护极长的一些区间 $[L_i, R_i]$ 使得 $\min\limits_{j = L_i}^r a_j = \min\limits_{j = R_i}^r a_j$。由 $\max$ 的不减性可得以 $L_i$ 为分割点一定不劣。

可以 ST 表 + 二分对每个 $L_i$ 求出一个 $b_i$ 使得 $l$ 取 $[b_i, L_i - 1]$ 时，$[l, r]$ 以 $L_i$ 为分割点是好的。

把 $[b_i, L_i - 1]$ 扔到树状数组上，如果对于一个询问的 $l$ 有区间覆盖它就合法。

时间复杂度 $O((n + q) \log n)$。

[code](https://codeforces.com/contest/1887/submission/229264130)

---

## 作者：耶梦加得 (赞：2)

对于一种分割方案，我们只关心左半部分的最大值，以及右半部分的最小值。序列元素互异，启发我们直接枚举左半部分的最大值，令其为 $a_i$，考虑哪些区间满足这个限制。

令 $x_l$ 为 $i$ 左侧最近的大于 $i$ 的位置，$x_r$ 为 $i$ 右侧最近的大于 $i$ 的位置。（这里“大于”指位置上的值的大小关系，下文“小于”同理。）

显然，设我们的区间为 $[l,r]$，则 $l\le i$ 且 $l > x_l$（否则 $i$ 不是最大值），又因为右半部分显然至少有一个大于 $a_i$ 的值，我们要求 $r \ge x_r$。

进一步的，易知我们把分界点放在 $x_r$ 前是不劣的（相对于任何一个 $(i, x_r)$ 间的其他位置，左半部分最大值不增，右半部分的最小值不降），此时我们只需要求 $[x_r,r]$ 区间不存在小于 $a_i$ 的数。令 $y$ 为 $x_r$ 右侧第一个小于 $i$ 的位置，则限制等价于 $r < y$。

把限制整合一下：$x_l \le l \le i, x_r \le r < y$，长得就很二维数点。问题转化为求一个点是否被矩形覆盖，直接做就行。

找 $x_l, x_r, y$ 的过程可以直接拿一个 set 搞，毕竟我们问询的形式只有“左右侧大/小于 $a_i$ 的最近位置”，故我们只要递增地枚举 $a_i$ 就可以方便地用 set 维护。

Code：

```cpp
#include<bits/stdc++.h>
#define ao 300007
using namespace std;
int n, m;
struct event {
    int x, l, r, id;
    inline bool operator < (const event & b) const {
        return x == b.x ? id < b.id : x < b.x;
    }
} tr[1000007];
int tot;
int a[ao], pos[ao];
set<int> des, asc;
int ans[ao];
int c[ao];
inline void modify(int x, int v) {
    for(; x <= n; x += x & -x) c[x] += v;
}
inline int ask(int x) {
    int ret = 0;
    for(; x; x -= x & -x) ret += c[x];
    return ret;
}
signed main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]); pos[a[i]] = i;
        des.insert(i);
    }
    des.insert(0); asc.insert(n + 1);
    for(int i = 1; i < n; asc.insert(pos[i++])) {
        des.erase(pos[i]);
        set<int> :: iterator it = des.upper_bound(pos[i]);
        if(it == des.end()) continue;
        int xr = *it; int xl = *--it;
        int y = *asc.upper_bound(xr);
        tr[++tot] = (event){xl + 1, xr, y, 0};
        tr[++tot] = (event){pos[i] + 1, xr, y, -1};
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; ++i) {
        int l, r; scanf("%d %d", &l, &r);
        tr[++tot] = (event){l, r, r, i};
    }
    sort(tr + 1, tr + tot + 1);
    for(int i = 1; i <= tot; ++i) {
        if(tr[i].id == 0) {
            modify(tr[i].l, 1);
            modify(tr[i].r, -1);
        } else if(tr[i].id == -1) {
            modify(tr[i].l, -1);
            modify(tr[i].r, 1);
        } else {
            ans[tr[i].id] = ask(tr[i].l);
        }
    }
    for(int i = 1; i <= m; ++i) {
        if(ans[i]) puts("Yes");
        else puts("No");
    }
    return 0;
}

```


---

## 作者：苏联小渣 (赞：1)

把题目条件转化一下，变成了询问是否存在 $l \le x<r$ 使得 $\max\{a_l,...,a_x\}<\min\{a_{x+1},...,a_r\}$。

max 和 min 套起来不是很好处理，考虑枚举其中一者，这里考虑枚举 max。

枚举最大值 $a_x$，那么可以用单调栈求出左/右第一个比它大的数，记作 $l_x,r_x$。那么此时我们就需要统计出哪些区间满足 $l_x <l \le x,r > x$ 且存在一个 $x<y \le r$ 使得 $[y,r]$ 的最小值比 $a_x$ 大。

我们发现一个很关键的性质，就是 $[x,r_x-1]$ 中的数肯定是要比 $a_x$ 小的。那么也就是说，合法的 $r$ 肯定满足 $r \ge r_x$。我们考虑如何选取 $y$ 最优。我们发现，$y$ 的选取一定满足 $x<y \le r_x$，而 $r$ 固定时，$y$ 越大则能取到的最小值越大，这样肯定越优（因为区间长度扩大最小值单调不增），所以 $y$ 取 $r_x$ 肯定最优。

现在问题就转化成了，找到一个最大的 $r_{\max}$ 使得 $[r_x,r_{\max}]$ 的最小值比 $a_x$ 大，那么所有左端点在 $[l_x+1,x]$，右端点在 $[r_x,r_{\max}]$ 内的区间 $[l,r]$ 都是合法的。

最大的 $r$ 显然可以通过线段树上二分求得；然后问题就转化成了矩形覆盖单点求值，发现不强制在线，考虑扫描线：在 $r_x$ 处给区间 $[l_x+1,x]$ 加一，在 $r_{\max}+1$ 处给区间 $[l_x+1,x]$ 减一，最后对于一组询问 $[l,r]$，当扫描到 $r$ 时单点查询 $l$ 的值就好了。这个可以通过树状数组实现，不过我脑抽写了线段树。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int n, q, pos, mn, flag, l, r, a[300010], fl[300010], fr[300010], ans[300010];
stack <int> st;
struct Add{
	int l, r, op;
};
struct Query{
	int l, id;
};
vector <Add> add[300010];
vector <Query> ask[300010];
struct segment{
	#define lc(x) x<<1
	#define rc(x) x<<1|1
	int d[1200010];
	void pushup(int k){
		d[k] = min(d[lc(k)], d[rc(k)]);
	}
	void build(int k, int l, int r){
		if (l == r){
			d[k] = a[l];
			return ;
		}
		int mid = l + r >> 1;
		build(lc(k), l, mid);
		build(rc(k), mid+1, r);
		pushup(k);
	}
	void find(int k, int l, int r, int lim){
		if (l == r){
			if (min(mn, d[k]) > lim) pos = l;
			return ;
		}
		int mid = l + r >> 1;
		if (min(mn, d[lc(k)]) < lim) find(lc(k), l, mid, lim);
		else{
			mn = min(mn, d[lc(k)]), pos = mid;
			find(rc(k), mid+1, r, lim);
		}
	}
	void query(int k, int l, int r, int x, int y, int lim){
		if (x > y) return ;
		if (x <= l && r <= y){
			if (min(mn, d[k]) < lim){
				if (!flag) find(k, l, r, lim);
				mn = min(mn, d[k]);
				flag = 1;
			}
			else{
				mn = min(mn, d[k]);
				pos = r;
			}
			return ;
		}
		int mid = l + r >> 1;
		if (x <= mid) query(lc(k), l, mid, x, y, lim);
		if (y > mid) query(rc(k), mid+1, r, x, y, lim);
	}
}S;
struct segment2{
	#define lc(x) x<<1
	#define rc(x) x<<1|1
	int d[1200010], tag[1200010];
	void pushdown(int k){
		if (tag[k]){
			tag[lc(k)] += tag[k], tag[rc(k)] += tag[k];
			d[lc(k)] += tag[k], d[rc(k)] += tag[k];
			tag[k] = 0;
		}
	}
	void modify(int k, int l, int r, int x, int y, int val){
		if (x <= l && r <= y){
			d[k] += val, tag[k] += val;
			return ;
		}
		int mid = l + r >> 1;
		pushdown(k);
		if (x <= mid) modify(lc(k), l, mid, x, y, val);
		if (y > mid) modify(rc(k), mid+1, r, x, y, val);
	}
	int query(int k, int l, int r, int x){
		if (l == r) return d[k];
		int mid = l + r >> 1;
		pushdown(k);
		if (x <= mid) return query(lc(k), l, mid, x);
		else return query(rc(k), mid+1, r, x);
	}
}T;
int main(){
	scanf ("%d", &n);
	for (int i=1; i<=n; i++){
		scanf ("%d", &a[i]);
	}
	S.build(1, 1, n);
	for (int i=1; i<=n; i++){
		while (!st.empty() && a[st.top()] < a[i]) st.pop();
		if (st.empty()) fl[i] = 0;
		else fl[i] = st.top();
		st.push(i);
	}
	while (!st.empty()) st.pop();
	for (int i=n; i>=1; i--){
		while (!st.empty() && a[st.top()] < a[i]) st.pop();
		if (st.empty()) fr[i] = n+1;
		else fr[i] = st.top();
		st.push(i);
	}
	for (int i=1; i<=n; i++){
		int l = fl[i]+1, r = fr[i]-1;
		pos = flag = 0, mn = 1e9;
		S.query(1, 1, n, r+1, n, a[i]);
		if (pos){
			add[r+1].push_back((Add){l, i, 1});
			add[pos+1].push_back((Add){l, i, -1});
		}
	}
	scanf ("%d", &q);
	for (int i=1; i<=q; i++){
		scanf ("%d%d", &l, &r);
		ask[r].push_back((Query){l, i});
	}
	for (int i=1; i<=n; i++){
		for (int j=0; j<add[i].size(); j++){
			int l = add[i][j].l, r = add[i][j].r, op = add[i][j].op;
			T.modify(1, 1, n, l, r, op);
		}
		for (int j=0; j<ask[i].size(); j++){
			int l = ask[i][j].l, id = ask[i][j].id;
			if (T.query(1, 1, n, l)) ans[id] = 1;
		}
	}
	for (int i=1; i<=q; i++){
		printf (ans[i] ? "Yes\n" : "No\n");
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

考虑这个条件，不妨枚举右半部分最小值所在位置 $p$，找到这个位置左侧与右侧最后一个不小于他的位置 $r_1,r_2$。令 $l_2=r_1-1$，找到 $l_2$ 左侧最后一个不大于他的位置 $l_1$。容易使用 st 表预处理然后对于每个位置 $O(\log n)$ 求出。不难发现符合要求的 $l,r$ 满足 $l_1\leq l\leq l_2$ 且 $r_1\leq r\leq r_2$。将每个限制差分并扔进一个 vector，离线使用扫描线即可 $O((n+q)\log n)$ 解决。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int stmin[20][300005],stmax[20][300005],a[300005],ans[300005];
vector<pair<pair<int,int>,int>> tag[300005];
vector<pair<int,int>> qry[300005];
struct sgt{
	int f[2000005];
	void pushdown(int i){
		f[i*2]+=f[i];
		f[i*2+1]+=f[i];
		f[i]=0;
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			f[i]+=cg;
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
	}
	int qry(int i,int l,int r,int pos){
		if(l==r){
			return f[i];
		} 
		pushdown(i);
		if(pos<=mid) return qry(i*2,l,mid,pos);
		if(pos>mid) return qry(i*2+1,mid+1,r,pos);
	}
}tree;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],stmin[0][i]=stmax[0][i]=a[i];
	for(int j=1;j<=19;j++) for(int i=1;i<=n-(1<<j)+1;i++) stmin[j][i]=min(stmin[j-1][i],stmin[j-1][i+(1<<(j-1))]),stmax[j][i]=max(stmax[j-1][i],stmax[j-1][i+(1<<(j-1))]);
	for(int i=1;i<=n;i++){
		int r=i;
		for(int j=19;j>=0;j--) if(stmin[j][r+1]>=a[i]&&r+(1<<j)<=n) r+=(1<<j);
		int l1=i;
		for(int j=19;j>=0;j--) if(l1>(1<<j)&&stmin[j][l1-(1<<j)]>=a[i]) l1-=(1<<j);
		if(l1==1) continue;
		int l2=l1-1;
		for(int j=19;j>=0;j--) if(l2>(1<<j)&&stmax[j][l2-(1<<j)]<a[i]) l2-=(1<<j);
		tag[l1].push_back(make_pair(make_pair(l2,l1-1),1));
		tag[r+1].push_back(make_pair(make_pair(l2,l1-1),-1)); 
	}
	int m; cin>>m;
	for(int i=1;i<=m;i++){
		int l,r; cin>>l>>r;
		qry[r].push_back(make_pair(i,l));
	}
	for(int i=1;i<=n;i++){
		for(auto v:tag[i]) tree.change(1,1,n,v.first.first,v.first.second,v.second);
		for(auto v:qry[i]) ans[v.first]=tree.qry(1,1,n,v.second);
	}
	for(int i=1;i<=m;i++){
		cout<<(ans[i]?"YES":"NO")<<"\n";
	}
	return 0;
}
```

---

## 作者：shenxinge (赞：0)

### 题目翻译

定义一个序列 $a_1,...a_n$ 是好的仅当存在一个点 $x$，使得 $\max_{i \in \left[1,x\right]} a_i$ 小于 $\min_{i \in \left[x+1,n \right]} a_i$。

现在你有一个序列 $a_1,...,a_n$，给出 $q$ 组询问 $l,r$，你要回答序列 $a_l,...,a_r$ 是否是好的。

$1 \le n \le 3 \times 10^5$，$1 \le q \le 1 \times 10^5$

### 做法

考虑从小到大加入，考虑到形如：

$$x,x,x,x,x,x,1,x,x,x,x,x$$

加入此时 $1$ 的位置是 $p$，那么 $\forall q \in \left(p,n\right] , [p,q]$ 都是好的。

此时加入 $2$ 位置是 $s$，如果 $2$ 和 $1$ 相连，即形如：

$$x,x,x,x,x,2,1,x,x,x,x,x$$

那么此时 ${1,2}$ 的区间为 $\left[s,p\right]$，那么 $\forall q \in \left(p,n\right]，[s,q]$ 都是好的。

如果 $2$ 和 $1$ 不相连，即形如：

$$x,x,x,x,2,x,1,x,x,x,x,x$$

那么 $\forall q \in \left(s,p\right]，[s,q]$ 都是好的。

于是可以用一条线段表示在位置上连续的已经插入的数。

假如新加入的数合并后的线段是 $\left[l,r\right]$，这条线段的后继的左端点为 $ed$。

那么对于任意问题 $(ql,qr)$ 对于 $\forall ql \in \left[l,r\right],qr \in \left(r,ed\right)$ 的问题的答案都是好的。

扫描线扫 $ql$，然后依次加入用 `set` 进行线段合并，查询 $qr$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std; constexpr int maxn(3e5+10);
int n,m,a[maxn],p[maxn]; 
vector<pair<int,int> > q[maxn]; 
set<pair<int,int> > s;
vector<tuple<int,int,int> > modi[maxn]; 
// 从小到大插入 
int sum[maxn<<2],tag[maxn<<2];
inline void push_up(int rt){
	sum[rt]=sum[rt<<1]+sum[rt<<1|1]; 
} 
inline void apply(int rt,int v){
	sum[rt]+=v,tag[rt]+=v;
}
inline void push_down(int rt){
	if(tag[rt]) apply(rt<<1,tag[rt]),apply(rt<<1|1,tag[rt]),tag[rt]=0;
}
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
inline void update(int L,int R,int v,int l,int r,int rt){ if(L>R) return;
	if(L<=l&&r<=R) return void(apply(rt,v));
	int mid=(l+r)>>1; push_down(rt);
	if(L<=mid) update(L,R,v,lson); 
	if(R>mid) update(L,R,v,rson);
	push_up(rt);
}
inline int query(int p,int l,int r,int rt){
	if(l==r) return sum[rt];
	int mid=(l+r)>>1; push_down(rt);
	if(p<=mid) return query(p,lson);
	else return query(p,rson);
}
#define root 1,n,1
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	cin >> n; for(int i=1;i<=n;i++) cin >> a[i],p[i]=i;
	sort(p+1,p+1+n,[&](int x,int y){return a[x]<a[y];});
	cin >> m; for(int i=1,l,r;i<=m;i++) cin >> l >> r,q[l].emplace_back(r,i);
	s.insert({0,0}),s.insert({n+1,n+1});
	for(int i=1;i<=n;i++){ int x=p[i]; auto it=s.insert({x,x}).first;
		if(prev(it)->first!=0&&prev(it)->second==x-1){
			int l=prev(it)->first; s.erase(it),s.erase({l,x-1});
			it=s.insert({l,x}).first;
		}
		if(next(it)->first!=n+1&&next(it)->first==x+1){
			int l=it->first,r=next(it)->second; s.erase(it),s.erase({x+1,r});
			it=s.insert({l,r}).first;
		}
		int l1=it->first,r1=it->second,l2=r1+1,r2=next(it)->first-1; 
	//	printf("x: %d l1: %d r1: %d l2: %d r2: %d\n",x,l1,r1,l2,r2);
		modi[l1].emplace_back(l2,r2,1),modi[r1+1].emplace_back(l2,r2,-1); 
	} static int ans[maxn];
	for(int i=1;i<=n;i++){
		for(auto E:modi[i]) update(get<0>(E),get<1>(E),get<2>(E),root);
		for(auto E:q[i]) ans[E.second]=query(E.first,root);
	}
	for(int i=1;i<=m;i++)
		if(ans[i]) puts("Yes");
		else puts("No");
	return 0;
}
```


---

## 作者：蒟蒻君HJT (赞：0)

赛时假了两次，遗憾离场。都什么时候了还在场切 2200-2400 呢？

考虑枚举拆出来的区间，右半边的最小值 $a_i$。求出每个 $a_i$ 左边第一个比它小的位置，右边第一个比它小的位置，记作 $l_i,r_i$。可知最小值为 $a_i$ 时，合法区间拆出来的右半边的右端点 $R\in [i,r_i-1]$，拆出来的左半边的右端点为 $l_i$。

左半边最多延伸到哪里？显然是最大的 $j$ 满足 $a_{j-1}<a_i$。也就是说左半边的左端点 $L\in[j,l_i]$。

以上所有东西都可以单调栈 + 二分 + RMQ 在线性对数的复杂度求出。

现在得到若干合法左右端点所在区间对 $([a,b],[c,d])$。每个询问合法的充要条件是其左右端点被某个区间对包含。相当于矩形加单点求值。扫描线即可。


[for reference only.](https://codeforces.com/contest/1887/submission/229360606)

---

