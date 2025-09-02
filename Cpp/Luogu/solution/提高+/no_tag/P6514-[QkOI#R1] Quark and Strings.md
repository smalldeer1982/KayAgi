# [QkOI#R1] Quark and Strings

## 题目描述

你需要维护一个字符串序列 $\{S_n\}$，其中有 $n$ 个字符串，初始全为空。接下来有 $q$ 次操作，支持两种操作，下面设当前为第 $i$ 次操作，且本题中字符集为 $[1,q]\cap \N_+$：

- `1 l r`，表示在所有编号在 $[l,r]$ 内的字符串末尾添加字符 $i$，这里 $i$ 是一个 $[1,q]$ 范围内的整数。
- `2 l r`，表示询问所有编号在 $[l,r]$ 内的字符串的最长公共子序列长度。当 $l=r$ 时，我们认为其最长公共子序列长度即为该字符串的长度。

## 说明/提示

### 样例解释

对于第一组样例：  
第一次操作后，序列为 $\{[1],[1],[1],[],[]\}$。  
第二次操作后，序列为 $\{[1,2],[1,2],[1,2],[2],[2]\}$。  
第三次操作，容易发现询问的最长公共子序列为 $[2]$，长度为 $1$。

---

### 数据范围

**本题采用捆绑测试。**

- Subtask 1（10 pts）：$n,q\le 500$。
- Subtask 2（20 pts）：$n,q\le 1000$。
- Subtask 3（15 pts）：$n\le 1000$，操作 $1$ 不超过 $500$ 次，时限 $2000$ms。
- Subtask 4（15 pts）：$n\le 1000$，操作 $2$ 不超过 $500$ 次，时限 $2000$ms。
- Subtask 5（40 pts）：无特殊限制，时限 $3000$ms。

对于 $100\%$ 的数据，$1\le n,q\le 10^5$，除了特殊标明的 Subtask，其它 Subtask 时限均为 $1000$ms。

## 样例 #1

### 输入

```
5 3
1 1 3
1 1 5
2 1 4
```

### 输出

```
1```

## 样例 #2

### 输入

```
8 8
2 8 8
1 3 8
2 5 8
1 1 8
1 1 1
2 3 5
2 1 7
1 2 7```

### 输出

```
0
1
2
1```

# 题解

## 作者：Ireliaღ (赞：7)

比赛中思考过程最短的一道题。

考虑转化一下题意，每次修改相当于添加一条从$l$到$r$的线段，每次查询就是询问贯穿区间$[l, r]$的线段个数。

把每条线段的左端点当做第一维，右端点当做第二维，那么这条线段可以对应坐标系中的一个点，查询就可以看做询问$x \in [1, l]$且$y \in [r, n]$的矩形上的点数，剩下的就是一个kd-tree的模板了。

代码如下

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int MAXN = 1e5 + 5;
const double A = 0.7;

struct Data{
	int x[2];
	
	Data(int a, int b) {
		x[0] = a;
		x[1] = b;
	}
	
	Data() {}
};

int operator == (const Data &a, const Data &b) {
	return a.x[0] == b.x[0] && a.x[1] == b.x[1];
}

struct Node{
	Data pos;
	Node *ch[2];
	int cnt, sum, cov;
	int mn[2], mx[2];
	
	Node(Data pos, int cnt) : pos(pos), cnt(cnt) {
		cov = 1;
		sum = cnt;
		for (int i = 0; i < 2; i++) mn[i] = mx[i] = pos.x[i];
		ch[0] = ch[1] = NULL;
	}
	
	Node() {}
}npool[MAXN];

int Comp0(Node *a, Node *b) {
	if (a->pos.x[0] != b->pos.x[0]) return a->pos.x[0] < b->pos.x[0];
	else return a->pos.x[1] < b->pos.x[1];
}

int Comp1(Node *a, Node *b) {
	if (a->pos.x[1] != b->pos.x[1]) return a->pos.x[1] < b->pos.x[1];
	else return a->pos.x[0] < b->pos.x[0];
}

int n, m;
int ncnt;
Node *rt;
Node *tree[MAXN];
int tcnt;

Node *New(Data pos, int cnt) {
	npool[ncnt] = Node(pos, cnt);
	return &npool[ncnt++];
}

void Update(Node *now) {
	now->cov = 1 + (now->ch[0] ? now->ch[0]->cov : 0) + (now->ch[1] ? now->ch[1]->cov : 0);
	now->sum = now->cnt + (now->ch[0] ? now->ch[0]->sum : 0) + (now->ch[1] ? now->ch[1]->sum : 0);
	for (int i = 0; i < 2; i++) now->mn[i] = now->mx[i] = now->pos.x[i];
	for (int i = 0; i < 2; i++) {
		if (now->ch[i]) {
			for (int j = 0; j < 2; j++) {
				now->mn[j] = min(now->mn[j], now->ch[i]->mn[j]);
				now->mx[j] = max(now->mx[j], now->ch[i]->mx[j]);
			}
		}
	}
}

int Bad(Node *now) {
	int ls = now->ch[0] ? now->ch[0]->cov : 0;
	int rs = now->ch[1] ? now->ch[1]->cov : 0;
	return 1.0 * ls > A * now->cov || 1.0 * rs > A * now->cov;
}

void DFS(Node *now) {
	if (!now) return;
	DFS(now->ch[0]);
	DFS(now->ch[1]);
	tree[++tcnt] = now;
	now->ch[0] = now->ch[1] = NULL;
	Update(now);
}

void Rebuild(Node *&now, int l, int r, int d) {
	if (l > r) return;
	int mid = l + r >> 1;
	if (d) nth_element(tree + l, tree + mid, tree + r + 1, Comp1);
	else nth_element(tree + l, tree + mid, tree + r + 1, Comp0); 
	now = tree[mid];
	Rebuild(now->ch[0], l, mid - 1, (d + 1) % 2);
	Rebuild(now->ch[1], mid + 1, r, (d + 1) % 2);
	Update(now);
}

void Maintain(Node *&now, int d) {
	if (Bad(now)) {
		tcnt = 0;
		DFS(now);
		Rebuild(now, 1, tcnt, d);
	}
}

void Insert(Node *&now, Data pos, int cnt, int d) {
	if (!now) {
		now = New(pos, cnt);
		return;
	}
	if (pos == now->pos) {
		now->cnt += cnt;
		Update(now);
		return;
	}
	if (pos.x[d] < now->pos.x[d]) Insert(now->ch[0], pos, cnt, (d + 1) % 2);
	else Insert(now->ch[1], pos, cnt, (d + 1) % 2);
	Update(now);
	Maintain(now, d);
}

int Inside(Node *now, int mn[], int mx[]) {
	for (int i = 0; i < 2; i++) {
		if (now->pos.x[i] < mn[i] || now->pos.x[i] > mx[i]) return 0;
	}
	return 1;
}

int AllIn(Node *now, int mn[], int mx[]) {
	for (int i = 0; i < 2; i++) {
		if (now->mn[i] < mn[i] || now->mx[i] > mx[i]) return 0;
	}
	return 1;
}

int AllOut(Node *now, int mn[], int mx[]) {
	for (int i = 0; i < 2; i++) {
		if (now->mn[i] > mx[i] || now->mx[i] < mn[i]) return 1;
	}
	return 0;
}

int Query(Node *now, int mn[], int mx[]) {
	if (!now) return 0;
	if (AllIn(now, mn, mx)) return now->sum;
	if (AllOut(now, mn, mx)) return 0;
	return (Inside(now, mn, mx) ? now->cnt : 0) + Query(now->ch[0], mn, mx) + Query(now->ch[1], mn, mx);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int op, x, y;
	int mn[2], mx[2];
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> op >> x >> y;
		if (op == 1) {
			Insert(rt, Data(x, y), 1, 0);
		} else {
			mn[0] = 1; mx[0] = x;
			mn[1] = y; mx[1] = n;
			cout << Query(rt, mn, mx) << '\n';
		}
	}
	return 0;
}
```

---

## 作者：Froggy (赞：4)

欸为什么大家喜欢树套树，短小精悍的CDQ分治不香么？

---

题意很容易转化，考虑每个修改操作对后面查询操作的贡献。

显然当前查询操作 $i$，会对后面每个查询操作 $j$ 只要满足 $l_i\leq l_j,r_i\geq r_j$ 就会产生 $1$ 的贡献。

那么查询操作 $j$ 就是统计有多少个修改操作 $i$ 满足 $i<j,l_i\leq l_j,r_i\geq r_j$。

显然的三维偏序问题，把询问离线然后CDQ分治解决即可。

（嗯，是个裸到不能再裸的题目了。。）

放一下极短的 ↓

***code**:* 

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 100010
int n,m,qs,ans[N];
struct BIT{           //树状数组板子
	int bit[N];
	inline int lowbit(int x){
		return x&(-x);
	}
	void Add(int x,int d){
		while(x<=n){
			bit[x]+=d;
			x+=lowbit(x);
		}
	}
	int Ask(int x){
		int ans=0;
		while(x){
			ans+=bit[x];
			x-=lowbit(x);
		}
		return ans;
	}
}A;
struct Op{
	int id,l,r,type;
}a[N];
bool cmp(Op x,Op y){
	return x.r==y.r?(x.l==y.l?x.type<y.type:x.l<y.l):x.r>y.r;  //按右端点排序
}
void CDQ(int l,int r){
	if(l>=r)return;
	int mid=(l+r)>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	sort(a+l,a+mid+1,cmp),sort(a+mid+1,a+r+1,cmp);
	int i=l,j=mid+1;
	while(j<=r){
		while(a[i].r>=a[j].r&&i<=mid){        //左边对右边的贡献，CDQ分治常规操作
			if(a[i].type==1)A.Add(a[i].l,1);
			++i;
		}
		if(a[j].type==2)ans[a[j].id]+=A.Ask(a[j].l);
		++j;
	}
	for(int j=l;j<i;++j){
		if(a[j].type==1)A.Add(a[j].l,-1);
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		int opt=read(),l=read(),r=read();
		a[i].id=(opt==2?++qs:0),a[i].l=l,a[i].r=r,a[i].type=opt;  //离线存询问
	}
	CDQ(1,m);
	for(int i=1;i<=qs;++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}

```

[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/)

#### 呱!!


---

## 作者：1saunoya (赞：2)

首先出题人的题解写了，就是个区间加法，单点查询。

给个奇怪的 KDT 做法，跑的海星。

我们把点离线下来，就变成了区间加单点查询的问题了。

注意的一点是，这个必须要把查询方式改一下，这样查询就能变成 $1\log$ 的。修改应该是 $2\log$，而不是大家平常所知道的 $n^{2-\frac{1}{k}}$。

让它变成 $1\log$  的办法很简单，当成线段树，用 zkw 线段树的思想，平衡树用个栈 $pushdown$ 一下就行了。

写的很奇怪？不用卡常就能轻松 1s/3s（

```cpp
inline int inc(int x, int y) {
	return x + y;
}

const int maxn = 2e5 + 52;
int x[2], y[2];
int t[maxn], val[maxn][2], K;
bool cmp(int a, int b) {
	return val[a][K] < val[b][K];
}

int mn[maxn][2], mx[maxn][2], ch[maxn][2], sum[maxn];
int fa[maxn]; 
int add[maxn];
#define ls ch[x][0]
#define rs ch[x][1]
inline void up(int x) {
	add[x] = 0;
	for(int i = 0 ; i < 2 ; i ++) {
		mn[x][i] = min(val[x][i], min(mn[ls][i], mn[rs][i]));
		mx[x][i] = max(val[x][i], max(mx[ls][i], mx[rs][i]));
	}
}

void bld(int &x, int l, int r, int k) {
	if(l > r) return;
	K = k;
	int mid = l + r >> 1;
	nth_element(t + l, t + mid, t + r + 1, cmp);
	x = t[mid],  bld(ls, l, mid - 1, k ^ 1);
	bld(rs, mid + 1, r, k ^ 1), up(x);
	fa[ls] = x;
	fa[rs] = x;
}

inline void down(int x) {
	if(add[x]) {
		sum[ls] = inc(sum[ls], add[x]);
		sum[rs] = inc(sum[rs], add[x]);
		add[ls] = inc(add[ls], add[x]);
		add[rs] = inc(add[rs], add[x]);
		add[x] = 0;
	}
}

int allin, allout, thisin;

inline void chk(int u) {
	allin = allout = thisin = 1;
	for (int i = 0; i < 2; i++) {
		if (x[i] > mn[u][i] || mx[u][i] > y[i]) {
			allin = 0;
			if (x[i] > val[u][i] || val[u][i] > y[i]) {
				thisin = 0;
				if (x[i] > mx[u][i] || y[i] < mn[u][i]) {
					allout = 0;
				}
			}
		}
	}
	allout ^= 1;
}

void mdf(int x, int y) {
	if(!x) return;
	chk(x);
	if(allout) return;
	if(thisin) {
		sum[x] = inc(sum[x], y);
	}
	if(allin) {
		add[x] = inc(add[x], y);
		return;
	}
	down(x); 
	mdf(ls, y), mdf(rs, y);
}

int n, q;
struct qwq {
	int op, l, r;
} a[maxn];

int root;
int top = 0;
signed main() {
#ifdef LOCAL
	freopen("testdata.in", "r", stdin);
#endif
	io in;
	in >> n >> q;
	mn[0][0] = mn[0][1] = maxn;
	mx[0][0] = mx[0][1] = 0;
	for(register int i = 1 ; i <= q ; i ++) {
		int op, l, r;
		in >> op >> l >> r;
		a[i] = { op, l, r };
		if(op == 2)
			t[++ top] = i, val[i][0] = l, val[i][1] = r;
	}
	root = 0;
	bld(root, 1, top, 0);
	static int st[maxn], tp = 0;
	for(register int i = 1 ; i <= q ; i ++) {
		int op, l, r;
		op = a[i].op;
		l = a[i].l;
		r = a[i].r;
		if(op == 1) {
			x[0] = x[1] = l;
			y[0] = y[1] = r;
			mdf(root, 1);
		} else {
			int x = fa[i];
			while(x) st[++ tp] = x, x = fa[x];
			while(tp) down(st[tp --]);
			out << sum[i] << '\n';
		}
	}
	return 0;
}
```

---

## 作者：LCuter (赞：2)

## D - Quark and Strings

##### $\text{Description}$

你需要维护一个字符串序列 $\{S_n\}$，其中有 $n$ 个字符串，字符集为 $[1,q]\cap N_+$，初始全为空。接下来有 $q$ 次操作，支持两种操作（设当前为第 $i$ 次操作）：

- `1 l r`，表示在所有编号在 $[l,r]$ 内的字符串末尾添加一个字符 $i$（数字）
- `2 l r`，表示询问所有编号在 $[l,r]$ 内的字符串的最长公共子序列长度。

$n,q\le 10^5$

##### $\text{Solution}$

注意操作 $1$ 只会添加之前未出现过的字符，可以得知，现在添加的字符只会在这一次操作中出现，所以一个 $[L,R]$ 的修改操作，实际上只会对 $l\ge L,r\le R$ 的 $[l,r]$ 询问操作贡献 $1$ 。

我们可以将问题转换为以下问题：

> 维护一个矩阵，其中第 $i$ 行第 $j$ 列的元素为 $a_{i,j}$，初始全为 $0$。支持两个操作：
>
> - `1 l r`，表示对所有满足 $i,j\in[l,r]$ 的 $a_{i,j}$ 执行$\mathbf{a_{i,j}\gets a_{i,j}+1}$。
> - `2 l r`，表示询问 $a_{l,r}$ 的值。

利用二维差分，可以将操作 $1$ 变为单点加 $1$，操作 $2$ 变为询问矩形内所有数的和，从而可以使用树套树解决。

---

## 作者：zyn_ (赞：1)

注意到：

A：修改操作每次加的字符都不同，第 $i$ 次操作加字符 $i$。

B：每个字符串始终保持单调递增。

因此若干字符串的 LCS 的长度 $a$ 就是每个字符串包含的字符集的交集 $S$ 的大小 $x$。

证明？

首先 $a$ 不大于 $x$，否则由 A，LCS 中无字符出现超过 $1$ 次，故 LCS 中有 $a>x$ 种字符，与 $x$ 的定义矛盾。

其次，设 $S$ 中元素从小到大排列为 $s_{1\dots x}$，则由 B，$s_1s_2\dots s_x$ 是一个 LCS，故 $a$ 不小于 $x$。

综上 $a=x$。

于是问题变为，有一个区间集合，每次加入一个区间，或询问集合中有多少区间包含一个指定区间。

一看是个动态二维数点，做完了。可以线段树或 KD-Tree 或 CDQ 分治。

这里使用了码量极小的二维 BIT，时间复杂度 $O(q\log^2 n)$。注意不能直接开 $O(n^2)$ 的数组，内层数组需要用 `unordered_map`。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,op,l,r;
unordered_map<int,int> mp[100009];
void upd(int x,int y){
    for(int i=x;i<=n;i+=i&-i)
        for(int j=y;j<=n;j+=j&-j)
            ++mp[i][j];
}
int qr(int x,int y){
    int r=0;
    for(int i=x;i;i-=i&-i)
        for(int j=y;j;j-=j&-j)
            r+=mp[i][j];
    return r;
}
int main(){
    scanf("%d%d",&n,&q);
    while(q--){
        scanf("%d%d%d",&op,&l,&r);
        if(op==1)upd(l,n-r+1);
        else printf("%d\n",qr(l,n-r+1));
    }
    return 0;
}
```

---

## 作者：kind_Ygg (赞：0)

还是我最喜欢的 BIT。
## 题目大意
和其他题解有些不一样。  
初始有一张长度为 $n$ 的桌子，桌子上最开始没有任何东西，$q$ 次询问，对于每个询问输入 $op$，$l$ 和 $r$。  
- $1\le n,q\le 10^5$
- $op\in[1,2]$
- $1\le l,r \le n$

当 $op$ 为 $1$ 时，代表用一条彩带覆盖 $[l,r]$ 这段位置；否则询问 $[l,r]$ 这段区间有多少条彩带完全覆盖（完全覆盖的意思是：假定一条彩带覆盖了 $[l_1,r_1]$，询问的位置是 $[l_2,r_2]$，当 $l_1\le l_2$ 且 $r_2\le r_1$，我们就说彩带完全覆盖这个位置）。
## 思路
考虑这样一个问题，当一条彩带覆盖了 $[l_i,r_i]$ 这个位置时，对什么做出了贡献。如果对 $[L,R]$ 做出了贡献，就要保证 $l_i\le L$ 且 $R\le r_i$。那么，我们将所有$l_i\le L$ 且 $R\le r_i$ 的区间彩带数增加 1。

求和的话，由于我们统计了答案，可以直接输出。

我们直接将 $[L,R]$ 封装成数组，那就变成二维区间加问题了，用二维 BIT 可以轻松解决。但由于 $n$ 的范围很大，建议用 `unordered_map` 存下，稍微卡卡常就过了。
## 时间复杂度
二维树状数组的时间复杂度是 $O(q\log^2 n)$，但用 `unordered_map` 常数有点大，建议手写哈希表。

---

## 作者：AtomAlpaca (赞：0)

## 题意

维护一个字符串序列 $\{S_n\}$，有两种操作共 $q$ 次，设当前为第 $i$ 次操作。

- `1 l r`，表示在所有编号在 $[l,r]$ 内的字符串末尾添加字符 $i$。
- `2 l r`，表示询问所有编号在 $[l,r]$ 内的字符串的最长公共子序列长度。

$1\le n,q\le 10^5$

## 题解
发现每次往后面加的都是一个独一无二的字符，我们其实要求的就是 $[l, r]$ 内都含有的字符种类。

考虑用一个 $(t, l, r)$ 三元组来描述一个操作，分别表示操作的时间、左端点、右端点，那么对于一个询问操作 $x$，我们其实就是要求 $t_y < t_x, l_y \le l_x, r_y \ge r_x$ 的修改操作 $y$ 的数量，这就是一个三维偏序的形式，我们用 CDQ 分治做一下就好了。复杂度 $O(n \log^2{n})$。代码相当简洁。

## 代码

```c++
#include <bits/stdc++.h>

const int MAX = 1e5 + 5;
int n, q, op, l, r, t;
int ans[MAX];
struct N { int t, l, r, x; } a[MAX];

bool cmpl(N a, N b) { return a.l == b.l ? a.r > b.r  : a.l < b.l; }
bool cmpt(N a, N b) { return a.t == b.t ? cmpl(a, b) : a.t < b.t; }

struct BIT
{
  int t[MAX];
  int lbt(int x) { return x & -x; }
  void add(int x) { if (!x) { return ; } while (x <= n) { ++t[x]; x += lbt(x); } }
  int qry(int x) { int res = 0; while (x) { res += t[x]; x -= lbt(x); } return res; }
  void clear() { for (int i = 1; i <= n; ++i) { t[i] = 0; } }
} st;

void solve(int l, int r)
{
  if (l == r) { return ; }
  int k = l + ((r - l) >> 1); solve(l, k); solve(k + 1, r);
  std::sort(a + l, a + k + 1, cmpl); std::sort(a + k + 1, a + r + 1, cmpl);
  int L = l, R = k + 1; st.clear();
  for (; R <= r; ++R)
  {
    while (L <= k and a[L].l <= a[R].l) { if (!a[L].x) { st.add(a[L].r); } ++L; }
    if (a[R].x) { ans[a[R].x] += st.qry(n) - st.qry(a[R].r - 1); }
  }
}

int main()
{
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= q; ++i)
  {
    scanf("%d%d%d", &op, &l, &r);
    a[i] = {i, l, r, (op == 2 ? ++t : 0)};
  }
  solve(1, q);
  for (int i = 1; i <= t; ++i) { printf("%d\n", ans[i]); }
}
```

---

## 作者：a326820068122c (赞：0)

~~这其实就是个三维偏序的板子。~~

考虑转化一下题意，每次修改相当于添加一条从 $l$ 到 $r$ 的线段，每次查询就是询问贯穿区间 $[l,r]$ 的线段个数。

把每条线段的左端点当做第一维，右端点当做第二维，那么这条线段可以对应坐标系中的一个点，查询就可以看做询问 $x\in [1,l] \land y \in [r, n]$ 的矩形上的点数

这时候有很多方法，我来列举一下优劣：

树套树：时间 $O(n\log^2n)$，空间 $O(n\log^2n)$，代码量大，在线

二维树状树组 $+$ 哈希表：时间 $O(n\log^2n)$，空间 $O(n\log^2n)$，代码量小，在线

KD-Tree: 时间 $O(n\sqrt n)$，空间 $O(n)$，代码量较大，在线

CDQ 分治：时间 $O(n\log^2n)$，空间 $O(n)$，代码量小，只能离线

这题耗时貌似是:

CDQ 分治 $<$ 二维树状树组 $+$ 哈希表 $<$ 树套树 $<$ KD-Tree

由于其他几个解法在其他几个题解里都有提及，本文重点讲二维树状树组 $+$ 哈希表的做法

二维树状树组的相较于优点是常数比较小，缺点是不能够直接动态开点，这时候可以使用哈希表来动态开点

这题空间对于此解法有点卡，所以我采用将原来哈希表里的 `long long` 改称一个 `int+char` 存储来压缩空间 

此外这题把存储 $r$ 的值翻转过来会比较好做

最后放一下代码:

```cpp
#include <bits/stdc++.h>
#define for1(i,n) for(i=1;i<=(n);i++)
using namespace std;
const int N=55000005,H=1073741823,Z=100007,V=55000000,P=54989993;
typedef long long ll;
int n,m,a[N],h[N];
char c[N];
void f(int x,int y){
	ll z=(ll)x*Z+y;
	int i,xx=z&H;
	char yy=z>>30;
	for(i=z%V;~c[i]&&(c[i]!=yy||h[i]!=xx);i>=P?i-=P:i+=10007);
	h[i]=xx;c[i]=yy;a[i]++;
}
int g(int x,int y){
	ll z=(ll)x*Z+y;
	int i,xx=z&H;
	char yy=z>>30;
	for(i=z%V;~c[i]&&(c[i]!=yy||h[i]!=xx);i>=P?i-=P:i+=10007);
	return a[i];
}
void add(int x,int y){
	int i,j;
	for(i=x;i<=n;i+=i&-i)
		for(j=y;j<=n;j+=j&-j) f(i,j);
}
int gsum(int x,int y){
	int i,j,ans=0;
	for(i=x;i;i-=i&-i)
		for(j=y;j;j-=j&-j) ans+=g(i,j);
	return ans;
}
int main(){
	memset(c,-1,sizeof(c));
	int i,opt,x,y;
	scanf("%d%d",&n,&m);
	for1(i,m){
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1) add(x,n-y+1);
		else printf("%d\n",gsum(x,n-y+1));
	}
	return 0;
}

```

---

