# PRMQUER - Prime queries

## 题目描述

&#8195;这是一个简单的题目

&#8195;给定 $N$ 个数，你需要对它们依次进行 $Q$ 次操作。每次操作的格式如下。

 1. 三个整数 $A$ $V$ $l$ 表示给第 $l$ 个数加上 $V$ 。
 
 2. 四个整数 $R$ $a$ $l$ $r$ 表示把区间 $[l,r]$ 的数都变为 $a$ 。
 
 3. 三个整数 $Q$ $l$ $r$ 表示询问区间 $[l,r]$ 里，小于等于 $10^7$ 的素数有多少个。
 
 &#8195;数据保证任何时刻这 $N$ 个数都不会有一个数大于 $10^9$ 。

## 说明/提示

- $1\leq N\leq10^5$

- $1\leq Q\leq10^5$
 
- $V\leq10^3$

- $A[i] \leq10^8$

- $a \leq10^7$

- $1\leq l\leq r \leq N$

## 样例 #1

### 输入

```
5 10
1 2 3 4 5
A 3 1
Q 1 3
R 5 2 4
A 1 1
Q 1 1
Q 1 2
Q 1 4
A 3 5
Q 5 5
Q 1 5```

### 输出

```
2
1
2
4
0
4```

# 题解

## 作者：liangbowen (赞：16)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/SP19568)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16845969.html)

好的线段树练习题。

## 思路

我们要维护三个操作：

1. 单点加。
2. 区间推平。
3. 区间查询质数。

区间推平可以想到珂朵莉树，但是我不会，于是考虑线段树。

容易想到，判断质数部分可以预处理。用[欧拉筛](https://www.luogu.com.cn/problem/P3383)，这一点不用多说了吧。

为了叙述方便，用 $\operatorname{isprime}(x)$ 表示 $x$ 是否为质数。

然后就是很套路的线段树了，只用维护一个覆盖（$cov_i$）的 tag 和总答案（$sum_i$）。

区间推平与查询和线段树板子几乎一样。单点修改时，把 $cov_i$ 加上 $k$，$sum_i = \operatorname{isprime}(cov_i + k)$。

至于下传，也很简单：$sum_i = \operatorname{isprime}(k) \times (r - l + 1)$，$cov_i = k$。

然后？就没有然后了。代码非常好打，感觉只有蓝。

## 完整代码

懒得打注释了，上面都说清楚了吧。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 4e5 + 5, MX = 1e7;
bool flag[MX + 5];
int prime[MX + 5], cur;
void euler() //欧拉筛 
{
	flag[0] = flag[1] = true;
	for (int i = 2; i <= MX; i++)
	{
		if (!flag[i]) prime[++cur] = i;
		for (int j = 1; j <= cur; j++)
		{
			if (i * prime[j] > MX) break;
			flag[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}
bool isp(int x) {return x <= MX && !flag[x];}
struct SegmentTree
{
	int sum[N], cov[N];
	inline int ls(int x) {return x << 1;}
	inline int rs(int x) {return x << 1 | 1;}
	void pushup(int pos) {sum[pos] = sum[ls(pos)] + sum[rs(pos)];}
	void build(int l, int r, int pos)
	{
		if (l == r)
		{
			cin >> cov[pos];
			sum[pos] = isp(cov[pos]);
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, ls(pos)), build(mid + 1, r, rs(pos));
		pushup(pos);
	}
	void lazy(int l, int r, int pos, int k)
	{
		sum[pos] = isp(k) * (r - l + 1);
		cov[pos] = k;
	}
	void pushdown(int l, int r, int pos)
	{
		if (!cov[pos]) return;
		int mid = (l + r) >> 1;
		lazy(l, mid, ls(pos), cov[pos]);
		lazy(mid + 1, r, rs(pos), cov[pos]);
		cov[pos] = 0;
	}
	void update(int l, int r, int pos, int id, int k) //单点加 
	{
		if (l == r)
		{
			cov[pos] += k, sum[pos] = isp(cov[pos]);
			return;
		}
		pushdown(l, r, pos);
		int mid = (l + r) >> 1;
		if (id <= mid) update(l, mid, ls(pos), id, k);
		else update(mid + 1, r, rs(pos), id, k);
		pushup(pos);
	}
	void modify(int l, int r, int pos, int L, int R, int k) //区间推平 
	{
		if (L <= l && r <= R) return lazy(l, r, pos, k);
		pushdown(l, r, pos);
		int mid = (l + r) >> 1;
		if (L <= mid) modify(l, mid, ls(pos), L, R, k);
		if (mid < R) modify(mid + 1, r, rs(pos), L, R, k);
		pushup(pos);
	}
	int query(int l, int r, int pos, int L, int R)
	{
		if (L <= l && r <= R) return sum[pos];
		pushdown(l, r, pos);
		int mid = (l + r) >> 1, ans = 0;
		if (L <= mid) ans += query(l, mid, ls(pos), L, R);
		if (mid < R) ans += query(mid + 1, r, rs(pos), L, R);
		return ans;
	}
} seg;
int main()
{
	ios::sync_with_stdio(false);
	euler();
	int n, T;
	cin >> n >> T;
	seg.build(1, n, 1);
	while (T--)
	{
		char c;
		cin >> c;
		if (c == 'A')
		{
			int k, id;
			cin >> k >> id;
			seg.update(1, n, 1, id, k);
		}
		else if (c == 'R')
		{
			int k, l, r;
			cin >> k >> l >> r;
			seg.modify(1, n, 1, l, r, k);
		}
		else if (c == 'Q')
		{
			int l, r;
			cin >> l >> r;
			cout << seg.query(1, n, 1, l, r) << '\n';
		}
	}
	return 0;
}
```

希望能帮助到大家！

---

## 作者：MiniLong (赞：11)

# SP19568 PRMQUER - Prime queries
## 题意
维护一段序列，支持 **单点加，区间推平，区间质数个数** 操作。

## 思路
看到区间推平，单点加就能想到是线段树。

难点只在于求区间质数个数。

用 sum 记录区间质数个数，change_tag 记录区间修改懒标记。

判断质数用埃筛预处理即可。

更新直接用左右子树的 sum 相加即可。

下传标记的时候是判断父节点的 sum 是否大于 $ 0 $（就是区间推平后是否都是质数）然后乘上子树的 size 就好。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define ls x << 1
#define rs x << 1 | 1
using namespace std;
const int N = 1e5 + 5, M = 1e7 + 5;
int n, q, w[N];
bool m[M];
struct Tree{
	int l, r, sum, cz;
}a[N * 4];
bool prime(int x){
	return ((x <= 1e7) && (m[x]));
}
void update(int x){
	a[x].sum = a[ls].sum + a[rs].sum;
}
void pushdown(int x){
	if(a[x].cz){
		a[ls].sum = (a[x].sum > 0) * (a[ls].r - a[ls].l + 1), a[rs].sum = (a[x].sum > 0) * (a[rs].r - a[rs].l + 1);
		a[ls].cz = a[rs].cz = a[x].cz;
		a[x].cz = 0;
	}
}
void build(int x, int l, int r){
	a[x].l = l, a[x].r = r;
	if(l == r){
		a[x].sum = prime(w[l]), a[x].cz = w[l];
		return;
	}
	int mid = l + r >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	update(x);
}
void add(int x, int p, int v){
	if(a[x].l == a[x].r){
		a[x].cz += v, a[x].sum = prime(a[x].cz);
		return;
	}
	pushdown(x);
	int mid = a[x].l + a[x].r >> 1;
	if(p <= mid) add(ls, p, v);
	else add(rs, p, v);
	update(x);
}
void change(int x, int l, int r, int v){
	if(a[x].l >= l && a[x].r <= r){
		a[x].cz = v, a[x].sum = prime(v) * (a[x].r - a[x].l + 1);
		return;
	}
	pushdown(x);
	int mid = a[x].l + a[x].r >> 1;
	if(l <= mid) change(ls, l, r, v);
	if(r > mid) change(rs, l, r, v);
	update(x);
}
int query(int x, int l, int r){
	if(a[x].l >= l && a[x].r <= r) return a[x].sum;
	pushdown(x);
	int mid = a[x].l + a[x].r >> 1, sum = 0;
	if(l <= mid) sum += query(ls, l, r);
	if(r > mid) sum += query(rs, l, r);
	return sum;
}
void dfs(int x = 1){
	if(x == 1) cout << "==============" << endl;
	printf("l: %lld, r: %lld, sum: %lld, cz: %lld\n", a[x].l, a[x].r, a[x].sum, a[x].cz);
	if(a[ls].l) dfs(ls);
	if(a[rs].l) dfs(rs); 
}
signed main(){
	memset(m, 1, sizeof m);
	m[0] = m[1] = 0;
	for(int i = 2; i <= 1e7; ++i){
		if(!m[i]) continue;
		for(int j = i + i; j <= 1e7; j += i){
			m[j] = 0;
		}
	}
	scanf("%lld%lld", &n, &q);
	for(int i = 1; i <= n; ++i){
		scanf("%lld", &w[i]);
	}
	build(1, 1, n);
	while(q--){
		char opt[2];
		int l, r, v;
		scanf("%s%lld%lld", opt, &l, &r);
		if(opt[0] == 'A') {
			add(1, r, l);
		}
		if(opt[0] == 'R'){
			scanf("%lld", &v);
			change(1, r, v, l);
		}
		if(opt[0] == 'Q'){
			printf("%lld\n", query(1, l, r));
		}
	}
	return 0;
}
```

---

## 作者：Engulf (赞：8)

## 前置芝士

- 珂朵莉树（模板：CF896C）
- 线性筛（模板：P3383）

## 分析

看到区间推平操作，基本上都可以使用珂朵莉树，非常幸运的是，此题数据随机，并没有卡掉我们可爱的珂朵莉~

### 操作 1 单点修改

单点修改 $x$ 可以看作区间修改 $[x,x]$。

```cpp
if (p[0] == 'A')
{
    scanf("%lld%lld", &x, &l);
    split(l + 1), split(l)->v += x;
}
```

### 操作 2 区间赋值

这是珂朵莉树的基本操作 `assign()`。

### 操作 3 查询区间质数个数

值域在 $10^7$，可以使用埃筛或者线性筛判定质数，建议使用线性筛。

```cpp
const int N = 1e7 + 10;
int primes[N], cnt;
bool st[N];
void init(int n)
{
	st[0] = st[1] = true;
	for (int i = 2; i <= n; i ++ )
	{
		if (!st[i]) primes[cnt ++ ] = i;
		for (int j = 0; primes[j] * i <= n; j ++ )
		{
			st[primes[j] * i] = true;
			if (i % primes[j] == 0) break;
		}
	}
}

if (p[0] == 'Q')
{
    scanf("%lld%lld", &l, &r);
    iter itr = split(r + 1), itl = split(l);
    int res = 0;
    for (iter i = itl; i != itr; i ++ )
        if (i->v <= 1e7 && !st[i->v])
            res += i->r - i->l + 1;
    printf("%lld\n", res);
}
```

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct Node
{
	int l, r;
	mutable int v;
	Node(int l, int r = 0, int v = 0) : l(l), r(r), v(v) {}
	bool operator<(const Node &x) const
	{
		return l < x.l;
	}
};
set<Node> s;
typedef set<Node>::iterator iter;
iter split(int pos)
{
	iter it = s.lower_bound(Node(pos));
	if (it != s.end() && it->l == pos) return it;
	it -- ;
	if (it->r < pos) return s.end();
	int l = it->l, r = it->r, v = it->v;
	s.erase(it);
	s.insert(Node(l, pos - 1, v));
	return s.insert(Node(pos, r, v)).first;
}
void assign(int l, int r, int v)
{
	iter itr = split(r + 1), itl = split(l);
	s.erase(itl, itr);
	s.insert(Node(l, r, v));
}

const int N = 1e7 + 10;
int primes[N], cnt;
bool st[N];
void init(int n)
{
	st[0] = st[1] = true;
	for (int i = 2; i <= n; i ++ )
	{
		if (!st[i]) primes[cnt ++ ] = i;
		for (int j = 0; primes[j] * i <= n; j ++ )
		{
			st[primes[j] * i] = true;
			if (i % primes[j] == 0) break;
		}
	}
}

signed main()
{
	init(1e7);
	int n, q;
	scanf("%lld%lld", &n, &q);
	for (int i = 1, x; i <= n; i ++ )
	{
		scanf("%lld", &x);
		s.insert(Node(i, i, x));
	}
	while (q -- )
	{
		char p[3];
		scanf("%s", p);
		int l, r, x;
		if (p[0] == 'A')
		{
			scanf("%lld%lld", &x, &l);
			split(l + 1), split(l)->v += x;
		}
		if (p[0] == 'R')
		{
			scanf("%lld%lld%lld", &x, &l, &r);
			assign(l, r, x);
		}
		if (p[0] == 'Q')
		{
			scanf("%lld%lld", &l, &r);
			iter itr = split(r + 1), itl = split(l);
			int res = 0;
			for (iter i = itl; i != itr; i ++ )
				if (i->v <= 1e7 && !st[i->v])
					res += i->r - i->l + 1;
			printf("%lld\n", res);
		}
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：7)

[传送门](https://www.luogu.com.cn/problem/SP19568)

### 前言

发现题解区全都是珂朵莉树，如果遇到特殊数据会被卡 TLE，所以本蒟蒻使用线段树通过了此题。

这是洛谷上本题第一个复杂度正确的 AC 记录！

### 分析

#### Step1 分析操作 & 选择 DS

一个约定：「满足条件的数」这里指 $\le 10^7$ 的素数。

暴力显然会超时，不考虑。

首先看最独特的操作 $3$，可以发现，数据结构必然要在子结构内统计「满足条件的数」的个数。先用线性筛 $O(n)$ 预处理，这样就能保证单次判断一个数是否为「满足条件的数」的时间复杂度为 $O(1)$。

然后看另外两个操作，一个是单点加，一个是区间赋值。

线段树！

#### Step2 上线段树

这里我建了两棵线段树，一棵用来维护数列，另一棵用来维护区间内满「满足条件的数」的个数和。


线段树需要支持的操作有：区间加，区间赋值，区间求和（单点就是长度为 $1$ 的区间）。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int NR = 1e5 + 5, SIZE = 1e7 + 5;

struct SegNode
{
	int sum, lazy1, lazy2;
};

int n, q, pcnt, p[SIZE];
bool isp[SIZE];
SegNode t1[NR << 2], t2[NR << 2];

void getprime(int n)
{
	memset(isp, 1, sizeof isp);
	isp[0] = isp[1] = 0;
	for (int i = 2; i <= n; ++i)
	{
		if (isp[i]) p[++pcnt] = i;
		for (int j = 1; j <= pcnt && i * p[j] <= n; ++j)
		{
			isp[i * p[j]] = 0;
			if (!(i % p[j])) break;
		}
	}
}

bool check(int x)
{
	return x <= 1e7 && isp[x];
}

void pushup(SegNode *t, int p)
{
	t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
}

void pushdown(SegNode *t, int p, int l, int r)
{
	int mid = l + r >> 1;
	if (~t[p].lazy1)
	{
		t[p << 1].lazy1 = t[p].lazy1;
		t[p << 1].sum = (mid - l + 1) * t[p].lazy1;
		t[p << 1 | 1].lazy1 = t[p].lazy1;
		t[p << 1 | 1].sum = (r - mid) * t[p].lazy1;
		t[p].lazy1 = -1;
	}
	if (t[p].lazy2)
	{
		t[p << 1].lazy2 += t[p].lazy2;
		t[p << 1].sum += (mid - l + 1) * t[p].lazy2;
		t[p << 1 | 1].lazy2 = t[p].lazy2;
		t[p << 1 | 1].sum += (r - mid) * t[p].lazy2;
		t[p].lazy2 = 0;
	}
} 

void assign(SegNode *t, int p, int l, int r, int x, int y, int k)
{
	if (l > y || r < x) return;
	if (l >= x && r <= y)
	{
		t[p].sum = (r - l + 1) * k;
		t[p].lazy1 = k;
		t[p].lazy2 = 0;
		return;
	}
	pushdown(t, p, l, r);
	int mid = l + r >> 1;
	assign(t, p << 1, l, mid, x, y, k);
	assign(t, p << 1 | 1, mid + 1, r, x, y, k);
	pushup(t, p);
}

void add(SegNode *t, int p, int l, int r, int x, int y, int k)
{
	if (l > y || r < x) return;
	if (l >= x && r <= y)
	{
		t[p].sum += (r - l + 1) * k;
		t[p].lazy2 += k;
		return;
	}
	pushdown(t, p, l, r);
	int mid = l + r >> 1;
	add(t, p << 1, l, mid, x, y, k);
	add(t, p << 1 | 1, mid + 1, r, x, y, k);
	pushup(t, p);
}

int query(SegNode *t, int p, int l, int r, int x, int y)
{
	if (l > y || r < x) return 0;
	if (l >= x && r <= y) return t[p].sum;
	pushdown(t, p, l, r);
	int mid = l + r >> 1;
	return query(t, p << 1, l, mid, x, y) + query(t, p << 1 | 1, mid + 1, r, x, y);
}

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	getprime(1e7);
	for (int i = 0; i < (NR << 2); ++i)
		t1[i].lazy1 = t2[i].lazy1 = -1;
	cin >> n >> q;
	for (int i = 1; i <= n; ++i)
	{
		int x; cin >> x;
		add(t1, 1, 1, n, i, i, x);
		if (check(x)) add(t2, 1, 1, n, i, i, 1);
	}
	while (q--)
	{
		char op; cin >> op;
		if (op == 'A')
		{
			int x, i; cin >> x >> i;
			add(t1, 1, 1, n, i, i, x);
			bool chk = check(query(t1, 1, 1, n, i, i));
			assign(t2, 1, 1, n, i, i, chk);
		}
		if (op == 'R')
		{
			int x, l, r; cin >> x >> l >> r;
			assign(t1, 1, 1, n, l, r, x);
			assign(t2, 1, 1, n, l, r, check(x));
		}
		if (op == 'Q')
		{
			int l, r; cin >> l >> r; 
			cout << query(t2, 1, 1, n, l, r) << endl;
		}
	}
	return 0;
}
```

---

## 作者：BFSDFS123 (赞：4)

一道珂朵莉树的好题，将数据结构和数学巧妙地结合在了一起。

你若不知道珂朵莉树是什么，请移步到[这篇博客](https://www.cnblogs.com/linzhengmin/p/10995150.html)。

---

翻译讲的很清楚了，此题要求我们做三个操作：

1. 单点修改
2. 区间覆盖
3. 计算区间内的质数

看到前两个操作你想到了什么？线段树？分块？但第三个操作有点难办。

等等，区间覆盖？我们可以使用珂朵莉树来轻松解决。

珂朵莉树最基本的板子不用说了，那么我们怎么计算区间内的质数呢？

我们可以用素数筛法来预处理出 $10^7$ 以内的所有质数。当然，因为这道题数比较小，所以我们可以直接使用埃氏筛来解决。[线性筛模板题](https://www.luogu.com.cn/problem/P3383)

我们只用修改查询答案那一部分，其他部分与模板没有任何不同。

代码：

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define LL_inf 1145141919810
#define ull unsigned long long
#define ll long long
using namespace std;
#define int long long
const int Maxn=1e5+10;
const int Maxm=1e7+10;
int vis[Maxm],prime[Maxm],cnt=0;
void init() //筛素数
{
	vis[0]=1;
	vis[1]=1;
	for(int i=2;i<=Maxm-10;i++)
	{
		if(vis[i]==0)
		{
			prime[++cnt]=i;
		}
		for(int j=1;j<=cnt,i*prime[j]<=Maxm-10;j++)
		{
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				break;
			}
		}
	}
	return ;
}
//珂朵莉树板子
struct Node{
	int l,r;
	mutable int val;
	Node(int L,int R=-1,int Val=0)
	{
		l=L;
		r=R;
		val=Val;
	} 
	bool operator<(const Node &rhs)const{
		return l<rhs.l; 
	}
};
set<Node> st;
set<Node>::iterator split(int pos)
{
	set<Node>::iterator it=st.lower_bound(Node(pos));
	if(it!=st.end() && it->l==pos)
	{
		return it;
	}
	--it;
	Node tmp=*it;
	st.erase(it);
	st.insert(Node(tmp.l,pos-1,tmp.val));
	return st.insert(Node(pos,tmp.r,tmp.val)).first;
}
void assign(int l,int r,int val)
{
	set<Node>::iterator itr=split(r+1),itl=split(l);
	st.erase(itl,itr);
	st.insert(Node(l,r,val));
}
void add(int l,int r,int val)
{
	set<Node>::iterator itr=split(r+1),itl=split(l);
	for(;itl!=itr;itl++)
	{
		itl->val+=val;
	}
}
int query(int l,int r)
{
	set<Node>::iterator itr=split(r+1),itl=split(l);
	int cnt=0;
	for(;itl!=itr;itl++) 
	{
		int x=itl->val;
		if(x>1e7) continue; 
		if(vis[x]==0)
		{
			cnt+=(itl->r-itl->l+1);
		}
	}
	return cnt;
}
signed main()
{
	init();
	int n,T;
	scanf("%lld%lld",&n,&T);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%lld",&x);
		st.insert(Node(i,i,x));
	}
	while(T--)
	{
		char opt;
		cin>>opt;
		switch(opt)
		{
			case 'A':{
				int val,x;
				scanf("%lld%lld",&val,&x);
				add(x,x,val);
				break;
			}
			case 'R':{
				int x,l,r;
				scanf("%lld%lld%lld",&x,&l,&r);
				assign(l,r,x);
				break;
			}
			default:{
				int l,r;
				scanf("%lld%lld",&l,&r);
				printf("%lld\n",query(l,r));
				break;
			}
		}
//		set<Node>::iterator itr=split(n+1),itl=split(1);
//		for(;itl!=itr;itl++)
//		{
//			printf("%d %d:%d\n",itl->l,itl->r,itl->val);
//		}
	}
	return 0;
}

```



---

## 作者：itisover (赞：2)

何须ODT？？？线段树即可

维护每个位置是否是符合条件的数 (0/1)，顺便维护每个位置上的值是多少。

对于操作 `'A'`，就是查询这个位置上的值，并判断加上 $V$ 后是否符合条件，如果符合条件就修改为 $1$，反之 $0$，顺带维护每个位置上的值。

对于操作 `'R'`，就是判断赋值的那个数是否符合条件，如果符合就区间改成 $1$，反之 $0$，顺带维护每个位置上的值。

对于操作 `'Q'`，维护区间是否符合条件的数和可以。

对于判断是否符合条件，可以欧筛标记出 $10^7$ 以内的质数。

```cpp
#include<bits/stdc++.h>
using namespace std;
template <class T>
inline T read(){
	T r=0,f=0;char c=getchar();
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) r=(r<<3)+(r<<1)+(c^48),c=getchar();
	return f?-r:r;
}
const int _=1e5+5,__=1e7+5;
int n,m,a[_];
int sum[_<<2],val[_<<2];
int pr[__],pn;
bool v[__],lazy[_<<2];
#define ls x<<1
#define rs x<<1|1
bool check(int x){return x>1&&x<=1e7&&!v[x];}
void pushdown(int x,int l,int r,int mid){
	if(lazy[x]){
		sum[ls]=(sum[x]>0)*(mid-l+1),sum[rs]=(sum[x]>0)*(r-mid); 
		val[ls]=val[rs]=val[x]; 	
		lazy[ls]=lazy[rs]=1;lazy[x]=0;
	}
}
void update(int x,int l,int r,int xl,int xr,int c){
	if(xl<=l&&xr>=r){sum[x]=(r-l+1)*check(c),lazy[x]=1,val[x]=c;return;}
	int mid=l+r>>1; pushdown(x,l,r,mid);
	if(xl<=mid) update(ls,l,mid,xl,xr,c);
	if(xr>mid) update(rs,mid+1,r,xl,xr,c);
	sum[x]=sum[ls]+sum[rs];
}
int query(int x,int l,int r,int xl,int xr){
	if(xl<=l&&xr>=r) return sum[x];
	int mid=l+r>>1; pushdown(x,l,r,mid);
	return xr<=mid?query(ls,l,mid,xl,xr):xl>mid?query(rs,mid+1,r,xl,xr):query(ls,l,mid,xl,xr)+query(rs,mid+1,r,xl,xr);
}
int get(int x,int l,int r,int p){
	if(l==r) return val[x];
	int mid=l+r>>1; pushdown(x,l,r,mid);
	return p<=mid?get(ls,l,mid,p):get(rs,mid+1,r,p);
}
void build(int x,int l,int r){
	if(l==r){sum[x]=check(a[l]),val[x]=a[l];return;}
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	sum[x]=sum[ls]+sum[rs];
}
void init(){
	for(int i=2;i<=1e7;++i){
		if(!v[i]) pr[++pn]=i;
		for(int j=1;j<=pn&&pr[j]*i<=1e7;++j){v[pr[j]*i]=1; if(i%pr[j]==0) break;}
	}
}
int main(){
	init();
	n=read<int>(),m=read<int>();
	for(int i=1;i<=n;++i) a[i]=read<int>();
	build(1,1,n);
	int x,y,z; char opt[2];
	while(m--){
		scanf("%s",opt);
		switch(opt[0]){
			case 'A':y=read<int>(),x=read<int>(),z=get(1,1,n,x),update(1,1,n,x,x,z+y);break;
			case 'R':x=read<int>(),y=read<int>(),z=read<int>(),update(1,1,n,y,z,x);break;
			case 'Q':x=read<int>(),y=read<int>(),printf("%d\n",query(1,1,n,x,y));break;
		}
	}
	return 0;
}
```

---

## 作者：CYZZ (赞：1)

# [Prime queries](https://www.luogu.com.cn/problem/SP19568)
首先，这是一道线段树板子题~~但蒟蒻我依然交了十几发~~。
# 思路分析
这题只需要用线段树完成单点修改，区间修改和查询质数个数三种操作。难点在于如何维护质数个数。

质数先用埃氏筛预处理。

我们注意到，此题不需要实现查询区间和。所以 $ tree $ 数组可以用来储存区间的质数个数，$ lazy $ 数组用于储存更新后的序列，然后就和线段树板子没有区别了。注意下传时要判断更新后值是否为质数。
# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,q,a[100005],tree[400005],tag[400005];
bool p[10000005];
void init()//埃氏筛 
{
	memset(p,1,sizeof p);
	p[0]=0;
	p[1]=0;
	for(int i=2;i<=1e7;++i)
	{
		if(!p[i])
			continue;
		for(int j=i+i;j<=1e7;j+=i)
		{
			p[j]=0;
		}
	}
}
bool prime(int x)
{
	return (x<=1e7)*(p[x]);//判断质数+大小 
}
void push_down(int p,int l,int r)
{
	if(!tag[p])
		return ;
	int mid=(l+r)/2;
	tree[2*p]=(tree[p]>0)*(mid-l+1);
	tree[2*p+1]=(tree[p]>0)*(r-mid);
	tag[2*p]=tag[2*p+1]=tag[p];
	tag[p]=0;
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		tree[p]=prime(a[l]);
		tag[p]=a[l];
		return ;
	}
	int mid=(l+r)/2;
	build(2*p,l,mid);
	build(2*p+1,mid+1,r);
	tree[p]=tree[2*p]+tree[2*p+1];
}
void update(int p,int l,int r,int pos,int add)
{
	if(l==r)
	{
		tag[p]+=add;
		tree[p]=prime(tag[p]);
		return ;
	}
	push_down(p,l,r);
	int mid=(l+r)/2;
	if(pos<=mid)
		update(2*p,l,mid,pos,add);
	else
		update(2*p+1,mid+1,r,pos,add);
	tree[p]=tree[2*p]+tree[2*p+1];
}
void modify(int p,int l,int r,int x,int y,int add)
{
	if(x<=l&&y>=r)
	{
		tag[p]=add;
		tree[p]=prime(add)*(r-l+1);
		return ;
	}
	push_down(p,l,r);
	int mid=(l+r)/2;
	if(x<=mid)
		modify(2*p,l,mid,x,y,add);
	if(y>mid)
		modify(2*p+1,mid+1,r,x,y,add);
	tree[p]=tree[2*p]+tree[2*p+1];
}
int query(int p,int l,int r,int x,int y)
{
	if(x<=l&&y>=r)
		return tree[p];
	push_down(p,l,r);
	int mid=(l+r)/2,ans=0;
	if(x<=mid)
		ans+=query(2*p,l,mid,x,y);
	if(y>mid)
		ans+=query(2*p+1,mid+1,r,x,y);
	return ans;
}
signed main()
{
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	init();
	build(1,1,n);
	for(int i=1;i<=q;i++)
	{
		int x,y;
		char ope;
		cin >> ope >> x >> y;
		if(ope=='A')
			update(1,1,n,y,x);//注意顺序 
		if(ope=='R')
		{
			int v;
			scanf("%lld",&v);
			modify(1,1,n,y,v,x);//注意顺序 
		}
		if(ope=='Q')
			printf("%lld\n",query(1,1,n,x,y));
	}
}
```
希望本篇题解可以帮到大家！

---

## 作者：Arghariza (赞：1)

实际上，我们发现只关心 $10^7$ 以内的质数，于是我们做一遍素数筛，预处理出 $10^7$ 以内数是质数还是合数即可。

由于修改时只需要判断一次是否是素数，于是可以直接使用线段树维护。

每个线段树节点维护区间小于 $10^7$ 素数个数和区间覆盖标记，对于叶子节点再记录上面的数值即可。

复杂度 $O(m\log n)$，非常好写。

```cpp
#include <bits/stdc++.h>
#define int long long
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 2e5 + 100;
const int maxw = 1e7 + 100;
struct seg { int vl, to, co; seg () { co = -1; } } tr[maxn << 1];
int n, m, tot, pr[maxw], v[maxw];

void init(int lim) {
	v[1] = 1;
	for (int i = 2; i <= lim; i++) {
		if (!v[i]) pr[++tot] = i;
		for (int j = 1; j <= tot && i * pr[j] <= lim; j++) {
			v[i * pr[j]] = 1;
			if (i % pr[j] == 0) break;
		} 
	}
}

#define ls x << 1
#define rs x << 1 | 1
#define mid ((l + r) >> 1)
bool isp(int c) { return c <= 1e7 && !v[c]; }
void pushup(int x) { tr[x].to = tr[ls].to + tr[rs].to; }
void pushcov(int x, int l, int r, int c) { tr[x].vl = c, tr[x].to = (r - l + 1) * isp(c), tr[x].co = c; }
void pushdown(int x, int l, int r) {
	if (tr[x].co == -1) return;
	pushcov(ls, l, mid, tr[x].co);
	pushcov(rs, mid + 1, r, tr[x].co);
	tr[x].co = -1;
}

void update(int l, int r, int p, int c, int x) {
	if (l == r) return tr[x].vl += c, tr[x].to = isp(tr[x].vl), void(); 
	pushdown(x, l, r);
	if (p <= mid) update(l, mid, p, c, ls);
	else update(mid + 1, r, p, c, rs);
	pushup(x);
}

void cover(int l, int r, int s, int t, int c, int x) {
	if (s <= l && r <= t) return pushcov(x, l, r, c);
	pushdown(x, l, r);
	if (s <= mid) cover(l, mid, s, t, c, ls);
	if (t > mid) cover(mid + 1, r, s, t, c, rs);
	pushup(x);
}

int query(int l, int r, int s, int t, int x) {
	if (s <= l && r <= t) return tr[x].to;
	pushdown(x, l, r);
	int res = 0;
	if (s <= mid) res += query(l, mid, s, t, ls);
	if (t > mid) res += query(mid + 1, r, s, t, rs);
	return res;
}

int qc(int l, int r, int x) {
	if (l == r) return write(tr[x].vl), putchar(' ');
	pushdown(x, l, r);
	qc(l, mid, ls), qc(mid + 1, r, rs);
} 

signed main() {
	n = read(), m = read(), init(1e7);
	for (int i = 1; i <= n; i++) update(1, n, i, read(), 1);
//	qc(1, n, 1), puts("");
	while (m--) {
		char op; cin >> op;
		int l = read(), r = read();
		if (op == 'A') update(1, n, r, l, 1);
		else if (op == 'Q') write(query(1, n, l, r, 1)), puts("");
		else cover(1, n, r, read(), l, 1);
//		qc(1, n, 1), puts("");
	}
	return 0;
}
/*
10 10
7 2 4 12 2 10 5 8 1 11 
R 6 1 4
Q 1 9
Q 4 8
R 19 9 10
Q 1 5
Q 8 9
A 3 3
Q 2 7
A 2 1
A 7 0

2
2
1
1
2

*/
```

---

## 作者：rai1gun (赞：1)

### 1.题意

选择 $a_x$，将 $a_x+k$。

选择区间 $[l,r]$，将这个区间的每个数变成 $k$。

询问区间 $[l,r]$ 中，共有多少个 $\leq 10^7$ 的质数。


### 2.题目思路

这道题确实不难 ~~（但我还是错了）~~。

用线段树维护这个序列即可。

单点修改与区间修改并不难，相信大家都会。

至于质数的话，只需要用欧拉筛一边质数，然后判断即可。

实现还有不少细节，千万不要错了。

线段树里存 $4$ 个变量，左端点，右端点，区间质数个数 $\texttt{sum}$，以及 $\texttt{lazytag}$。

### 3.题目代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 0x7f7f7f7f
#define map unorded_map
#define re register
#define ll long long
#define ull unsigned long long
#define fi first
#define se second
#define Mod 998244353
#define F1(i,a,b,k) for(re int i=a;i<=b;i+=k)
#define F2(i,a,b,k) for(re int i=a;i>=b;i-=k)
namespace Fast_Io{
    template<typename T> inline void read(T &t){
        t=0;
        char c=getchar();
        int f=1;
        while(!isdigit(c)){
            if(c=='-') f=-f;
            c=getchar();
        }
        while(isdigit(c)){
            t=(t<<3)+(t<<1)+(c^'0');
            c=getchar();
        }
        t*=f;
    }
    template<typename T,typename ... Args> inline void read(T &t,Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> inline void print(T x,char c='\0'){
        if(x<0){
            x=-x;
            putchar('-');
        }
        if(x>9){
            print(x/10);
        }
        putchar(x%10+'0');
        if(c!='\0'){
            putchar(c);
        }
    }
    template<typename T> inline T abs(T x){return x<0?-x:x;}
    inline int lowbit(int x){return x&(-x);}
}
using namespace Fast_Io;
const int N = 1e5+5;
int n,m,a[N],sz;
struct Tree{
    int l,r,sum,lazy_tag;
}tr[N*4];
const int M = 1e7+5;
bool prime[M];
int loc[M];
inline void Prime(int n){
    memset(prime,1,sizeof(prime));
    prime[0]=prime[1]=0;
    F1(i,2,n-1,1){
        if(prime[i]) loc[++sz]=i;
        for(int j=1;j<=sz && i*loc[j]<=n;j++){
            prime[i*loc[j]]=0;
            if(i%loc[j]==0) break;
        }
    }
}
inline void pushup(int p){tr[p].sum=tr[p*2].sum+tr[p*2+1].sum;}
inline bool check(int p){return p<=(1e7)&&prime[p];}
inline void bulid(int p,int l,int r){
    tr[p].l=l,tr[p].r=r;
    if(l==r){
        tr[p].lazy_tag=a[l];
        tr[p].sum=check(a[l]);
        return ;
    }
    int mid=l+r>>1;
    bulid(p*2,l,mid);
    bulid(p*2+1,mid+1,r);
    pushup(p);
}
inline void pushdown(int p){
    if(tr[p].lazy_tag){
        int mid=tr[p].l+tr[p].r>>1;
        tr[p*2].sum=(tr[p].sum>0)*(mid-tr[p].l+1);
        tr[p*2+1].sum=(tr[p].sum>0)*(tr[p].r-mid);
        tr[p*2].lazy_tag=tr[p].lazy_tag;
        tr[p*2+1].lazy_tag=tr[p].lazy_tag;
        tr[p].lazy_tag=0;
    }
    return ;
}
inline int query(int p,int ql,int qr){
    if((ql<=tr[p].l && tr[p].r<=qr) || !tr[p].sum) return tr[p].sum;
    pushdown(p);
    int mid=tr[p].l+tr[p].r>>1,ans=0;
    if(ql<=mid) ans+=query(p*2,ql,qr);
    if(qr>mid) ans+=query(p*2+1,ql,qr);
    return ans;
}
inline void update(int p,int id,int k){
    if(tr[p].l==tr[p].r){
        tr[p].lazy_tag+=k;
        tr[p].sum=check(tr[p].lazy_tag);
        return ;
    }
    pushdown(p);
    int mid=tr[p].l+tr[p].r>>1;
    if(id<=mid) update(p*2,id,k);
    else update(p*2+1,id,k);
    pushup(p);
}
inline void update2(int p,int ul,int ur,int k){
    if(ul<=tr[p].l && tr[p].r<=ur){
        tr[p].sum=(tr[p].r-tr[p].l+1)*check(k);
        tr[p].lazy_tag=k;
        return ;
    }
    pushdown(p);
    int mid=tr[p].l+tr[p].r>>1;
    if(ul<=mid) update2(p*2,ul,ur,k);
    if(ur>mid) update2(p*2+1,ul,ur,k);
    pushup(p);
}
int main(){
    Prime(M);
    read(n,m);
    F1(i,1,n,1) read(a[i]);
    bulid(1,1,n);
    while(m--){
        int l,r,k;
        char op;
        cin>>op;
        if(op=='A'){
            read(k,l);
            update(1,l,k);
        }else if(op=='R'){
            read(k,l,r);
            update2(1,l,r,k);
        }else{
            read(l,r);
            print(query(1,l,r),'\n');
        }
    }
    return 0;
}

```

---

## 作者：_caiji_ (赞：1)

观察题目，发现它说了这么多其实是想让我们写一个数据结构支持：
- 单点修改（区间长为 $1$ 的区间修改）；
- 区间赋值；
- 区间计算 $<10^7$ 的素数个数。

看到"区间赋值"这个操作，我们不难想到 [Old Driver Tree](https://www.luogu.com.cn/blog/ACdreamer/solution-cf896c) 这一暴力数据结构。本题数据较水，所以使用 Old Driver Tree 是可以通过的，大胆去写吧。

另外，题目已经说了素数最大 $10^7$，为了更容易通过，最好使用线性筛预处理出所有素数，然后每次 $O(1)$ 判断素数。

下面给出我的代码实现：
```cpp
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;
template<int N> struct LS{//线性筛板子
	//https://www.luogu.com.cn/blog/cicos/notprime
    int p[N+10],n;
    bool isnp[N+10];
    LS(){
        isnp[0]=isnp[1]=1;
        for(int i=2;i<=N;i++){
            if(!isnp[i]) p[++n]=i;
            for(int j=1;j<=n&&i*p[j]<=N;j++){
                if(isnp[i*p[j]]=1,i%p[j]==0) break; 
                //上面这个是逗号表达式，固定从左往右，返回最后一个值
            }
        }
    }
    bool operator()(int x){return !isnp[x];}
};
LS<10000000> p;
//  1234567 个 0 别数错了
template<class T> struct ODT{
    struct node{
        int l,r;
        mutable T v;
        operator int()const{return r-l+1;}
        //https://zh.cppreference.com/w/cpp/language/cast_operator
        //注意 const 不能少
        node(int l,int r=-1,T v=0):l(l),r(r),v(v){}
        bool operator<(const node &b)const{return l<b.l;}
    }; 
    set<node> s;
    typedef typename set<node>::iterator IT;
    void init(int n,T a[]){
        s.insert(node(n+1,n+1));
        for(int i=1;i<=n;i++) s.insert(node(i,i,a[i]));
    }
    IT split(int pos){
        IT it=s.lower_bound(node(pos));
        if(it!=s.end()&&it->l==pos) return it;
        T v=(--it)->v;
        //如果你像我一样压行，一定要注意优先级问题，--it 加一对括号
        int l=it->l,r=it->r;
        s.erase(it);
        s.insert(node(l,pos-1,v));
        return s.insert(node(pos,r,v)).first;
    }
    void assign(int l,int r,T v){
        IT R=split(r+1),L=split(l);
        s.erase(L,R);
        s.insert(node(l,r,v));
    }
    void add(int l,int r,T v){
        IT R=split(r+1),L=split(l);
        for(IT it=L;it!=R;++it) it->v+=v;
    }
    int query(int l,int r){
        int ans=0;
        IT R=split(r+1),L=split(l);
        for(IT it=L;it!=R;++it) ans+=p(min(it->v,10000000))*(*it);
        //同样 (*it) 的括号也不能少
        return ans;
    }
    void output(){
        for(IT it=s.begin();it!=s.end();++it){
            for(int i=it->l;i<=it->r;i++){
                cout<<it->v<<" |"[i==it->r];
            }
        }
        cout<<endl;
    }
};
ODT<int> a;
int n,m,ipu[100010];
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>ipu[i];
    a.init(n,ipu);
    for(int i=1;i<=m;i++){char op;
        cin>>op;
        //或 scanf(" %c",&op)，注意空格
        if(op=='A'){
            int l,v;
            cin>>v>>l;//注意输入格式
            a.add(l,l,v);
        }else if(op=='R'){
            int l,r,v;
            cin>>v>>l>>r;
            a.assign(l,r,v);
        }else{
            int l,r;
            cin>>l>>r;
            cout<<a.query(l,r)<<endl;
        }
        //a.output();
    }
    return 0;
}
```


---

## 作者：a2lyaXNhbWUgbWFyaXNh (赞：0)

### 前言

有区间推平，第一时间想到的就是珂朵莉树。~~还好数据够水。~~

秉着能写 odt 绝不写线段树的原则，这篇题解诞生了。

### 做法

#### 操作 1

单点修改。当成 l~l 区间修改就行。

#### 操作 2

区间赋值。珂朵莉树基本操作。

#### 重点：操作 3

$10^7$ 的查询范围可以用线性筛。

**但是**，请注意，判断的时候你不能 

```cpp
if(!f[it->v]&&it->v<=10000000) 
```
判，会 RE。你得 

```cpp
if(it->v<=10000000&&!f[it->v]) 
```
这样判。

因为根据短路的原则（即，对于逻辑与运算，第一个为假就不会继续计算，表达式直接为假；对于逻辑或运算，第一个为真就不会继续计算，表达式直接为真），你才躲掉了毒瘤数据。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define TIPS "ctjzm"
#define IT set<node>::iterator
typedef long long TYPE;

int prime[10000007];
bool f[10000007];

void sieve(){
    int n=10000000;
    f[0]=f[1]=1;
	int cnt=1;
	for(int i=2;i<=n;i++){
		if(!f[i])
			prime[cnt++]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
			f[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}	
	}
}//线性筛

struct node{
	unsigned int l,r;
	mutable TYPE v;
	node(unsigned int left,unsigned int right=0,TYPE value=0);
};
bool operator<(node a,node b){
	return a.l<b.l;
}
node::node(unsigned int left,unsigned int right,TYPE value){
	l=left;
	r=right;
	v=value;
}
set<node>odt; 
inline IT split(unsigned int p){
	IT it=odt.lower_bound(node(p));
	if(it!=odt.end()&&it->l==p)
		return it;
	--it;
	unsigned r=it->r,l=it->l;
	TYPE v=it->v;
	odt.erase(it);
	odt.insert(node(l,p-1,v));
	return odt.insert(node(p,r,v)).first;	
}//珂朵莉树核心——分裂操作
inline void assign(int l, int r, int v) {
	IT itr=split(r+1),itl=split(l);
	odt.erase(itl, itr);
	odt.insert(node(l, r, v));
}//操作2+珂朵莉树核心——推平操作
//祖传珂朵莉树模板↑
inline void update(int p,int v){
    split(p+1),split(p)->v+=v;
}//操作 1，单点修改
inline int getsum(int l,int r){
    long long sum=0;
    IT itr=split(r+1),itl=split(l);
    for(IT it=itl;it!=itr;++it)
        if(it->v<=10000000&&!f[it->v])
            sum+=it->r-it->l+1;
    return sum;        
}//操作3，统计素数

int n,m,x,y,z;
char ch;
int main(){
    sieve();//预处理
    cin>>n>>m;
    for(unsigned i=1;i<=n;++i){
        int t;
        cin>>t;
        odt.insert(node(i,i,t));
    }
    for(unsigned i=1;i<=m;++i){
        cin>>ch;
        switch(ch){
            case 'A':
                cin>>x>>y;
                update(y,x);
            break;
            case 'R':
                cin>>x>>y>>z;
                assign(y,z,x);
            break;
            case 'Q':
                cin>>x>>y;
                cout<<getsum(x,y)<<endl;
            break;
        }
    }
    return 0;//好习惯
}
```

---

## 作者：Register_int (赞：0)

给定 $n$ 个数，需要支持：  
1. 单点加
2. 区间推平
3. 区间质数个数

看到 $2$ 操作就大概可以知道用什么数据结构维护了。这里用的是颜色均摊段。  
考虑如何实现 $1,3$ 操作。$1$ 操作很明显，直接将这个点分裂出来，再更新，最后插回去就可以了。$3$ 操作就先筛出所有质数，每次询问先把区间分裂出来，再逐个判断每一个区间是否是质数，最后累加返回答案。  
时间复杂度 $O(\text{能过})$。  
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e5 + 10;
const int MAXM = 1e7 + 10;

int p[MAXM], tot;
bool vis[MAXM];

inline 
void init(int n) {
	vis[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) p[++tot] = i;
		for (int j = 1; j <= tot; j++) {
			if (i * p[j] > n) break;
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
}

struct node {
	int l, r;
	mutable int v;
	bool operator < (const node &rhs) const { return l < rhs.l; }
};

set<node> s;

inline 
auto split(int pos) {
	auto it = s.lower_bound({ pos });
	if (it != s.end() && it->l == pos) return it;
	it--;
	int l = it->l, r = it->r, v = it->v;
    s.erase(it), s.insert({ l, pos - 1, v });
    return s.insert({ pos, r, v }).first;
}

inline 
void assign(int l, int r, int v) {
	auto end = split(r + 1), begin = split(l);
	s.erase(begin, end), s.insert({ l, r, v });
}

inline 
void modify(int x, int k) {
	split(k + 1);
	auto it = split(k); x += it->v;
	s.erase(it), s.insert({ k, k, x });
}

inline 
int query(int l, int r) {
	auto end = split(r + 1), begin = split(l);
	int res = 0;
	for (auto it = begin; it != end; ++it) {
		if (it->v <= 1e7 && !vis[it->v]) res += it->r - it->l + 1;
	}
	return res;
}

int n, q, x, y, z;

char opt[5];

int main() {
	init(1e7);
	scanf("%d%d%d", &n, &q, &x), z = 1;
	for (int i = 2; i <= n; i++) {
		scanf("%d", &y);
		if (x != y) s.insert({ z, i - 1, x }),z = i;
		x = y;
	}
	s.insert({ z, n, x });
	while (q--) {
		scanf("%s%d%d", opt, &x, &y);
		if (*opt == 'A') modify(x, y);
		if (*opt == 'R') scanf("%d", &z), assign(y, z, x);
		if (*opt == 'Q') printf("%d\n", query(x, y));
	} 
}
```

---

## 作者：Setsugesuka (赞：0)

仔细观察题意，发现题目要我们维护下面这些操作。

1. 单点修改

2. 区间赋值

3. 询问区间里小于 $1e7$ 的素数个数

自然地想到用欧拉筛预处理哪些数是素数，然后用 $ODT$ 去维护这些操作。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e7+10;

struct node
{
    int l,r;
    mutable long long v;
    node(int L,int R=-1,long long V=0):l(L),r(R),v(V) {}
    bool operator <(const node &o) const
    {
        return l<o.l;
    }
};

int prime[MAXN],tot=0,p[MAXN];

inline void init()
{
    prime[1]=prime[0]=1;
    for(int i=2;i<=MAXN-10;i++)
    {
        if(prime[i]==0)
            p[++tot]=i;
        for(int j=1;j<=tot&&i*p[j]<=MAXN-10;j++)
        {
            prime[i*p[j]]=1;
            if(i%p[j]==0)
                break;
        }
    }
}

set<node> s;

inline set<node>::iterator split(int pos)
{
    set<node>::iterator it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos) return it;
    --it;
    int L=it->l,R=it->r;
    long long V=it->v;
    s.erase(it);
    s.insert(node(L,pos-1,V));
    return s.insert(node(pos,R,V)).first;
}

inline void assignval(int l,int r,long long v)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,v));
}

inline void add(int l,int r,long long v)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    for(itl;itl!=itr;itl++)
    {
        itl->v+=v;
    }
}

inline int query(int l,int r)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    int ret=0;
    for(itl;itl!=itr;itl++)
    {
        if(itl->v>10000000)
            continue;
        else if(!prime[itl->v])
            ret+=(itl->r-itl->l+1);
    }
    return ret;
}

int n,m;

int main()
{
    init();
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int sr;
        scanf("%d",&sr);
        s.insert(node(i,i,sr));
    }
    while(m--)
    {
        char op;
        cin>>op;
        if(op=='A')
        {
            int v,l;
            scanf("%d %d",&v,&l);
            add(l,l,v);
        }
        else if(op=='R')
        {
            int v,l,r;
            scanf("%d %d %d",&v,&l,&r);
            assignval(l,r,v);
        }
        else
        {
            int l,r;
            scanf("%d %d",&l,&r);
            cout<<query(l,r)<<endl;
        }
    }
    return 0;
}
```


---

## 作者：Hanx16Kira (赞：0)

# PRMQUER - Prime queries

[SP19568(Luogu)](https://www.luogu.com.cn/problem/SP19568)

## Solution

[SP13015](https://www.luogu.com.cn/problem/SP13015) 双倍经验（甚至还少了单点修改的操作）

既然有区间推平的操作那就用珂朵莉树水一水吧~~（逃~~

区间推平操作是珂朵莉树自带的，所以就不在这里详细阐述了，先来看单点修改怎么做（我最开始看成区间加了所以用区间加实现的）。单点加可以看作一个长度为 $1$ 的区间进行区间加操作，假设点的位置为 $pos$ 那么就可以看作 $[pos,pos]$ 这个区间的区间加操作，直接取出区间对这个区间的 $v$ 值进行加法操作即可。

然后是查询。注意到询问的质数范围是 $(0,10^7]$ 这一数量级的，所以可以先用质数筛法筛出 $10^7$ 内的质数（我用的埃筛实现的），那么对于一个询问区间 $[l,r]$ ，先将这个区间取出，然后依次扫描这个区间内珂朵莉树的节点，如果当前节点的 $v$ 值是符合条件的质数，那么这个区间就会对答案产生 $r-l+1$ 的贡献，统计这个贡献即可。

另外需要注意的是，节点的 $v$ 值可能会超过 $10^7$ ，所以直接调用质数数组可能导致下标越界，所以要先判断。

### Code

```c++
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof a)
using namespace std;
template<typename T> void read(T &k)
{
    k=0;T flag=1;char b=getchar();
    while (!isdigit(b)) {flag=(b=='-')?-1:1;b=getchar();}
    while (isdigit(b)) {k=k*10+b-48;b=getchar();}
    k*=flag;
}
const int _MAXN=1e7,_SIZE=1e5;
bool prime[_MAXN+5];
void preWork()//埃筛
{
    prime[1]=1;
    for (int i=2;i<=_MAXN;i++)
        if (!prime[i])
            for (int j=2;j*i<=_MAXN;j++)
                prime[j*i]=1;
}
struct NODE{//珂朵莉树
    int l,r;
    mutable int v;
    NODE (int l,int r=0,int v=0) : l(l),r(r),v(v) {}
    bool operator< (const NODE &a) const {return l<a.l;}
};
set <NODE> ctlt;
auto split(int pos)
{
    auto it=ctlt.lower_bound(NODE(pos));
    if (it!=ctlt.end() && it->l==pos) return it;
    it--;
    if (it->r<pos) return ctlt.end();
    int l=it->l,r=it->r,v=it->v;
    ctlt.erase(it);
    ctlt.insert(NODE(l,pos-1,v));
    return ctlt.insert(NODE(pos,r,v)).first;
}
void assign(int l,int r,int x)
{
    auto itr=split(r+1),itl=split(l);
    ctlt.erase(itl,itr);
    ctlt.insert(NODE(l,r,x));
}
void modify(int l,int r,int v)//区间加（用于实现单点加）
{
    auto itr=split(r+1),itl=split(l);
    for (auto it=itl;it!=itr;it++) it->v+=v;
}
int query(int l,int r)//区间查询
{
    auto itr=split(r+1),itl=split(l);
    int res=0;
    for (auto it=itl;it!=itr;it++)
        if (it->v<=10000000 && !prime[it->v]) res+=it->r-it->l+1;//需要注意v值可能大于1e7，直接查看数组会导致下标越界，所以先进行判断
    return res;
}
int n,q;
int a[_SIZE+5];
int main()
{
    preWork();
    read(n),read(q);
    for (int i=1;i<=n;i++) read(a[i]),ctlt.insert(NODE(i,i,a[i]));//读入+建树
    for (int i=1;i<=q;i++)
    {
        char op[2];scanf("%s",op);
        if (op[0]=='A')
        {
            int pos,x;
            read(x),read(pos);
            modify(pos,pos,x);
        }
        else if (op[0]=='R')
        {
            int l,r,x;
            read(x),read(l),read(r);
            assign(l,r,x);
        }
        else
        {
            int l,r;
            read(l),read(r);
            printf("%d\n",query(l,r));
        }
    }
    return 0;
}
```

---

## 作者：happybob (赞：0)

## 题意

写一种数据结构，支持单点加，区间推平，查找区间质数个数。

## 解放

发现三种操作有一个区间推平操作，果断想到可以 ODT，单点加也是裸的，但是区间质数个数怎么维护呢？

注意到，题目要求的是 $\leq 10^7$ 的质数，所以可以考虑先用筛法预处理，线性筛和埃氏筛均可。然后套上一个区间求和的 ODT 即可。

注意，其实 ODT 的复杂度不一定是对的，如果数据根本没有区间推平操作，并且特意卡 ODT，那么 ODT 可能会超时，不过这题没卡那么严。

代码（使用埃氏筛）：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;

const int N = 1e7 + 5;

int n, q;

bool is_prime[N];

inline void Init()
{
	memset(is_prime, 1, sizeof is_prime);
	is_prime[2] = true;
	is_prime[1] = is_prime[0] = false;
	for (int i = 2; i <= (int)1e7; i++)
	{
		if (is_prime[i])
		{
			for (long long j = (long long)i * i; j <= (long long)1e7; j += i) is_prime[j] = false;
		}
	}
}

class Old_Driver_Tree
{
public:
	struct Node
	{
		int l, r;
		mutable int v;
		Node(int _l, int _r, int _v) : l(_l), r(_r), v(_v) {}
		bool operator<(const Node& g) const
		{
			return l < g.l;
		}
	};
	set<Node> odt;
	auto split(int x)
	{
		if (odt.empty()) return odt.begin();
		if (x > n) return odt.end();
		auto it = --odt.upper_bound(Node(x, 0, 0));
		if (it != odt.end() && it->l == x) return it;
		int l = it->l, r = it->r, v = it->v;
		if (odt.size()) odt.erase(it);
		odt.insert(Node(l, x - 1, v));
		return odt.insert(Node(x, r, v)).first;
	}
	void assign(int l, int r, int v)
	{
		auto itr = split(r + 1), itl = split(l), g = itl;
		if (odt.size()) odt.erase(g, itr);
		odt.insert(Node(l, r, v));
	}
	void add(int x, int v)
	{
		auto itr = split(x + 1), itl = split(x), g = itl;
		for (; itl != itr; ++itl)
		{
			itl->v += v;
		}
	}
	int query(int l, int r)
	{
		auto itr = split(r + 1), itl = split(l);
		int res = 0;
		for (; itl != itr; ++itl)
		{
			if (itl->v <= (int)1e7 && is_prime[itl->v])
			{
				res += itl->r - itl->l + 1;
			}
		}
		return res;
	}
};

Old_Driver_Tree odt;

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> q;
	Init();
	for (int i = 1; i <= n; i++)
	{
		int v;
		cin >> v;
		odt.assign(i, i, v);
	}
	while (q--)
	{
		int l, r;
		char ch;
		cin >> ch >> l >> r;
		if (ch == 'A')
		{
			odt.add(r, l);
		}
		else if (ch == 'R')
		{
			int x;
			cin >> x;
			odt.assign(r, x, l);
		}
		else cout << odt.query(l, r) << "\n";
	}
	return 0;
}
```


---

## 作者：Usada_Pekora (赞：0)

题意写的很明白了，这里就不讲了。

思路：建一棵线段树，每个节点维护区间内 $\leq 10^7$ 的质数的个数和，以及当前节点的值。

对于操作 A ，直接线段树单点修改 $i$ 的值，然后判断修改后的数是不是  $\leq 10^7$ 的质数，一路更新回去。

对于操作 R ，考虑维护一个 Lazytag 表示当前区间是否被覆盖为 $\leq 10^7$ 的质数，为 $0$ 表示覆盖为条件不符的数，为 $1$ 表示被覆盖为条件符合的数，为 $-1$ 表示没有覆盖。如果当前区间被覆盖了，就下推，子区间的值继承自当前区间， 再分 tag 的情况讨论，tag 为 $1$ ，则将左右子区间的符合条件的个数和设置为区间长度，为 $0$ 则设置为 $0$ 。

对于操作 Q ， 直接对 $[l,r]$ 求和即可，常规的线段树区间查询。

质数处理方面，因为范围是 $10^7$ ，所以直接采用欧拉筛即可，不过似乎埃氏筛或者预处理 $\sqrt {10^7}$ 范围的质数也可以勉强卡过？

代码如下，一些细节和坑点注释在代码里了。复杂度为 $O(N + Q\log_2 N)$ 。不开 O2 不卡常数 660ms 还是比较快的。

```cpp
#include <bits/stdc++.h>
#define ls (p << 1)
#define rs (p << 1 | 1)
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 int128;
typedef __uint128_t uint128;
const int mod = 1e9 + 7;
using namespace std;
inline int read() {
	int x = 0, f = 0, ch = getchar();
	while(ch < '0' || ch > '9') f |= ch == '-', ch = getchar();
	while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
inline int readc() {
	int ch = getchar();
	while(ch < 'A' || ch > 'Z') ch = getchar();
	return ch;
}
const int N = 1e5 + 5, P = 1e7, inf = 1e9 + 7;
int sum[N << 2], pcnt, prime[P], tag[N << 2], b[N << 2], a[N], n, m; 
//sum 表示区间符合条件质数个数，tag是lazytag， b是当前区间被覆盖的值，没有被覆盖默认为0（其实最好设置成inf，我懒得设置了，毕竟只有被覆盖了才会下推），a是初始数组
// prime 要开大，不要吝啬内存，否则会RE
bool np[P + 1];
inline void init() { // 欧拉筛预处理质数
	for(int i = 2; i <= P; i++) {
		if(!np[i]) prime[++pcnt] = i;
		for(int j = 1; i * prime[j] <= P && j <= pcnt; j++) {
			np[i * prime[j]] = true;
			if(!i % prime[j]) break;
		}
	}
}
inline int check(int x) {
	return x > 1 && x < P && !np[x];
}
inline void pushup(int p) {
	sum[p] = sum[ls] + sum[rs];
}
inline void build(int p, int l, int r) {
	tag[p] = -1;// build赋初值
	if(l == r) {
		sum[p] = check(a[l]);
		b[p] = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushup(p);
}
inline void pushdown(int p, int l, int r) {
	if(~tag[p]) {
		int mid = l + r >> 1;
		sum[ls] = (mid - l + 1) * tag[p];// 区间长度直接乘上是否符合条件，不用if语句判断
		sum[rs] = (r - mid) * tag[p];
		tag[ls] = tag[rs] = tag[p];
		b[ls] = b[rs] = b[p];
		tag[p] = -1;
	}
}
inline void modify(int p, int l, int r, int x, int k) {
	if(l == r) {
		sum[p] = check(b[p] + k);//单点加，其实可以写成把[l,l]覆盖成 val[l,l] + k 的格式。
		b[p] += k;
		return;
	}
	int mid = l + r >> 1;
	pushdown(p, l, r);
	if(x <= mid) modify(ls, l, mid, x, k);
	else modify(rs, mid + 1, r, x, k);
	pushup(p);
}
inline void cover(int p, int l, int r, int L, int R, int k) {
	if(L <= l && r <= R) {
		tag[p] = check(k);
		sum[p] = (r - l + 1) * tag[p]; 
		b[p] = k;
		return;
	}
	int mid = l + r >> 1;
	pushdown(p, l, r);
	if(L <= mid) cover(ls, l, mid, L, R, k);
	if(R > mid) cover(rs, mid + 1, r, L, R, k);
	pushup(p);
}
inline int query(int p, int l, int r, int L, int R) {
	if(L <= l && r <= R) return sum[p];
	int mid = l + r >> 1, res = 0;
	pushdown(p, l, r);
	if(L <= mid) res += query(ls, l, mid, L, R);
	if(R > mid) res += query(rs, mid + 1, r, L, R);
	return res;
}
signed main() {
	init();
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	build(1, 1, n);
	for(int op, l, r, v; m; m--) {
		op = readc();//注意输入格式，V和LR是反着来的，一开始按照常规思路被坑了好久
		if(op == 'A') v = read(), l = read(), modify(1, 1, n, l, v);
		else if(op == 'R') v = read(), l = read(), r = read(), cover(1, 1, n, l, r, v);
		else l = read(), r = read(), printf("%d\n", query(1, 1, n, l, r));
	}
	return 0;
}
```


---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP19568)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/04/30/SP19568%20PRMQUER/)

## 前言

一道线段树比较板子的题目，应该没有紫，个人评价是蓝。

### 前置芝士

线段树，线性筛

## 分析

题目有一个操作是让我们求出某一个区间内质数的个数，看到 $10^7$ 的范围直接用线性筛预处理出 $1 - 10^7$ 中的所有质数，然后来考虑怎么线段树维护信息。

首先我们来考虑线段树中一个区间的属性，首先我们有查询区间个数的操作，所以我们用 $sum$ 表示一个区间内质数的个数，然后有区间覆盖，再来一个懒标记就可以。

对于每个操作 $A$，我们直接在对应的位置上加上这个数，然后判断新的数是不是质数，如果是质数就把这个区间的 $sum$ 变成 $1$ 反之则是 $0$。

对于每个操作 $R$，我们判断区间覆盖的数是否是质数，如果是就把对应区间的 $sum$ 改为这个区间的长度，反之则是 $0$，注意修改完要 `pushdown` 一下。

对于每个操作 $Q$，直接线段树求和板子即可。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10, M = 1e7 + 10;
struct node
{
    int l, r, val;
    int sum;
} t[N << 2];
int primes[M], v[M];
int a[N];

inline void init()
{
    memset(v, 1, sizeof v);
    v[1] = 0;
    int cnt = 0;
    for (int i = 2; i < M; i++)
    {
        if (v[i])
            primes[++cnt] = i;
        for (int j = 1; j <= cnt && primes[j] <= M / i; j++)
        {
            v[i * primes[j]] = 0;
            if (i % primes[j] == 0)
                break;
        }
    }
}

inline int check(int n)
{
    return (n <= 1e7 && v[n]);
}

inline void pushup(int p)
{
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
}

inline void pushdown(int p)
{
    if (!t[p].val) return;
    
    t[p << 1].val = t[p << 1 | 1].val = t[p].val;
    t[p << 1].sum = (t[p << 1].r - t[p << 1].l + 1) * (t[p].sum > 0);
    t[p << 1 | 1].sum = (t[p << 1 | 1].r - t[p << 1 | 1].l + 1) * (t[p].sum > 0);

    t[p].val = 0;
}

inline void build(int p, int l, int r)
{
    t[p].l = l;
    t[p].r = r;
    if (l == r)
    {
        t[p].val = a[l];
        t[p].sum = check(t[p].val);
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline void modify(int p, int x, int k)
{
    if (t[p].l == t[p].r)
    {
        t[p].val += k;
        t[p].sum = check(t[p].val);
        return;
    }
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (x <= mid) modify(p << 1, x, k);
    else modify(p << 1 | 1, x, k); 
    pushup(p);
}

inline void cover(int p, int l, int r, int k)
{
    if (l <= t[p].l && t[p].r <= r)
    {
        t[p].val = k;
        t[p].sum = (t[p].r - t[p].l + 1) * check(t[p].val);
        return;
    }
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) cover(p << 1, l, r, k);
    if (r > mid) cover(p << 1 | 1, l, r, k);
    pushup(p);
}

inline int ask(int p, int l, int r)
{
    if (l <= t[p].l && t[p].r <= r) return t[p].sum;
    pushdown(p);
    int res = 0;
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) res += ask(p << 1, l, r);
    if (r > mid) res += ask(p << 1 | 1, l, r);
    return res;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    init();
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build(1, 1, n);
    while (m--)
    {
        char op;
        cin >> op;
        if (op == 'A')
        {
            int x, k;
            scanf("%d%d", &k, &x);
            modify(1, x, k);
        }
        else if (op == 'R')
        {
            int l, r, k;
            scanf("%d%d%d", &k, &l, &r);
            cover(1, l, r, k);
        }
        else
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", ask(1, l, r));
        }
    }
    return 0;
}
```







---

## 作者：panyanppyy (赞：0)

> 这是一个简单的题目

## Problem
给定 $n\le10^5$ 个数，$q\le10^5$ 次操作。
1. 单点修改第 $l$ 个数加上 $V$。

2. 区间修改 $\left[l,r\right]$ 的数都变为 $a$。
3. 区间查询 $\left[l,r\right]$ 小于等于 $10^7$ 的素数有多少个。

## Solution
欧拉筛 $\times$ 线段树

第一个想法自然是预处理 $1\sim10^7$ 内的所有数是否为质数。

**维护区间**：

建立一颗线段树 $t$ 有两个个值：

$sum$ 区间质数个数，$val$ 区间修改后的 $tag$（叶子结点存当前值）。
1. 单点加：

	直接加，$sum=$ 加完是质数。
2. 区间修改：

	修改记一个 $val$ 区间标记，如果 $val$ 是质数，$sum=$ 区间长度，否则为 $0$。
3. 区间查询：

	直接查询区间 $sum$ 即可。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
using namespace std;
template<typename T_=int>inline T_ read(){
	T_ x=0;bool y=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')y=1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return y?~(x-1):x;
}
const int N=1e5+1,M=1e7+1;
vector<int>s;
bool f[M];
struct qjc{
	int sum,val;
}t[N<<2];
int n,q,a[N];
inline void prime(){
	memset(f,1,sizeof(f)),f[0]=f[1]=0;
	for(int i=2;i<M;i++){
		if(f[i])s.emplace_back(i);
		for(int j=0;j<(int)s.size()&&i*s[j]<M;j++){
			f[i*s[j]]=0;
			if(!(i%s[j]))break;
		}
	}
}//欧拉筛
inline bool ss(int x){return x<M&&f[x];}
inline void push_up(int rt){t[rt].sum=t[rt<<1].sum+t[rt<<1|1].sum;}
inline void up(int rt,int k,int x){t[rt].sum=k,t[rt].val=x;}
inline void push_down(int l,int r,int rt){
	if(!t[rt].val)return;
	int mid=(l+r)>>1;
	up(rt<<1,(mid-l+1)*(t[rt].sum>0),t[rt].val);
	up(rt<<1|1,(r-mid)*(t[rt].sum>0),t[rt].val);
	t[rt].val=0;
}
inline void build(int l,int r,int rt){
	if(l==r){
		t[rt].val=a[l];
		t[rt].sum=ss(a[l]);
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,rt<<1);
	build(mid+1,r,rt<<1|1);
	push_up(rt);
}
inline void add(int x,int k,int l,int r,int rt){
	if(l==r){
		t[rt].val+=k;
		t[rt].sum=ss(t[rt].val);
		return;
	}
	push_down(l,r,rt);
	int mid=(l+r)>>1;
	if(x<=mid)add(x,k,l,mid,rt<<1);
	else add(x,k,mid+1,r,rt<<1|1);
	push_up(rt);
}
inline void update(int L,int R,int k,int l,int r,int rt){
	if(L<=l&&r<=R)return up(rt,(r-l+1)*ss(k),k);
	push_down(l,r,rt);
	int mid=(l+r)>>1;
	if(L<=mid)update(L,R,k,l,mid,rt<<1);
	if(R>mid)update(L,R,k,mid+1,r,rt<<1|1);
	push_up(rt);
}
inline int query(int L,int R,int l,int r,int rt){
	if((L<=l&&r<=R)||!t[rt].sum)return t[rt].sum;
	push_down(l,r,rt);
	int mid=(l+r)>>1,ans=0;
	if(L<=mid)ans+=query(L,R,l,mid,rt<<1);
	if(R>mid)ans+=query(L,R,mid+1,r,rt<<1|1);
	return ans;
}//线段树
char op;
int main(){prime();
	n=read(),q=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	build(1,n,1);
	for(int i=1,l,r,k;i<=q;i++){
		scanf(" %c",&op);
		switch(op){
			case'A':
				k=read(),l=read();
				add(l,k,1,n,1);
				break;
			case'R':
				k=read(),l=read(),r=read();
				update(l,r,k,1,n,1);
				break;
			case'Q':
				l=read(),r=read();
				printf("%d\n",query(l,r,1,n,1));
				break;
		}
	}
	return 0;
}
```

---

