# 「MCOI-02」Ancestor 先辈

## 题目背景

这题跟 MC 有关的就是题目背景出现了三次 MC，提示说明出现了一次 MC。

```
           ▃▆█▇▄▖
       ▟◤▖　　　  ◥█  
   ◢◤ 　  ◢▐　　     ▐▉
 ▗◤　  　   ▂ ▗▖　 ▕ █▎
 ◤　▗▅▖ ◥▄　 ▀▀▀◣　█▊
▐　▕▎  ◥▖◣◤　 　　◢██
█◣　◥▅█▀　     　▐███◤
▐█▙▂　　　      ◢███◤
　◥██◣　　　　 ◢▄◤
　　　▀██▅▇▀▎▇
```

## 题目描述

对于两个序列 $a,b$，如果满足：

$$ \forall i \leq \min(n,m),s.t.\ a_i \leq b_i $$

那么我们称 $a$ 比 $b$ 屑（$n$ 为 $a$ 的长度，$m$ 为 $b$ 的长度）。

如果对于一个序列 $a$，它比它的所有后缀都屑，那么我们称这个序列为先辈。

给定一个长为 $n$ 的序列 $a_i$，共有 $k$ 次操作，包括以下两种：

- `1 l r x` 区间 $[l,r]$ 加上 $x$。
- `2 l r` 查询区间 $[l,r]$ 是不是先辈。

## 说明/提示

#### 样例说明

对于样例 $1$：

1. 询问区间 $[1,3]$ 是否为先辈，不是，输出 `No`。
2. 区间 $[3,4]$ 加上 $9$，现在序列为 $\{1,9,10,18,8,1,0\}$。
3. 询问区间 $[1,4]$ 是否为先辈，是，输出 `Yes`。
4. 区间 $[5,6]$ 加上 $11$，现在序列为 $\{1,9,10,18,19,12,0\}$。
5. 询问区间 $[2,6]$ 是否为先辈，不是，输出 `No`。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（1 pts）$\ \ $：询问操作的区间长度均为 $1$。
- Subtask 2（9 pts）$\ \ $：$n,k \le 10^3$。
- Subtask 3（10 pts）：$n,k\le 5\times 10^3$。
- Subtask 4（10 pts）：只有查询操作。
- Subtask 5（10 pts）：修改操作的数量不超过 $100$。
- Subtask 6（20 pts）：$n,k \le 10^5$。
- Subtask 7（40 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n,k \le 10^6$，$|a_i|,|x| \le 10^9$。

**本题强制 $O2$ 优化。**

#### 说明

Minecraft OI Round 2 C

- Maker：happydef
- Tester：tarjin

## 样例 #1

### 输入

```
7 5
1 9 1 9 8 1 0
2 1 3
1 3 4 9
2 1 4
1 5 6 11
2 2 6```

### 输出

```
No
Yes
No```

# 题解

## 作者：EDqwq (赞：26)

### 定义&本质：

屑其实是什么意思呢？

就是把两个序列头对齐放在一起，只要下面的数全部大于等于上面的数，上面的就比下面的屑。

例如1 3 4 6 7和8 8 8 8

1 3 4 6 7

8 8 8 8

此时，8大于1，8大于3，8大于4，8大于6，所以上面的序列比下面的屑。

那相信先辈是什么意思大家也懂了。

但要什么时候一个序列才是先辈呢？

既然要一个序列的**后缀**把原序列屑掉，那么这个后缀对齐原序列的头之后，肯定所有的数都大于等于上面的原序列的数，换句话说，也就是需要这个序列是一个**不下降序列**。

于是这道题就很简单了。

***

### 思路：

可以用万能的线段树来做。

我们合并的时候怎么才能判断这个合并出来的区间是不是先辈呢？

我们只需要判断，左边和右边的是不是先辈，然后判断左末和右头满不满足不下降即可。

于是这道题就没有难点了，剩下的都是线段树基本操作。

注意在query里面要用新的merge函数更新即可。

***

### 代码：

```cpp
/*
  Author: EnderDeer
  Online Judge: Luogu
*/

#include<bits/stdc++.h>

#define int long long

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

struct node{
	int l;
	int r;
	int lw;
	int rw;
	bool flag;
}e[10000010];

int n,m;
int a[10000010];
int lazy[10000010];

void merge(int i){
	e[i].lw = e[i * 2].lw;
	e[i].rw = e[i * 2 + 1].rw;
	if(e[i * 2].rw <= e[i * 2 + 1].lw && e[i * 2].flag && e[i * 2 + 1].flag)e[i].flag = true;
	else e[i].flag = false;
}

void renewans(node &x,node &y,node &z){
	x.lw = y.lw;
	x.rw = z.rw;
	if(y.flag && z.flag && y.rw <= z.lw)x.flag = true;
	else x.flag = false;
}

void pushup(int i,int w){
	e[i].lw += w;
	e[i].rw += w;
	lazy[i] += w;
}

void pushdown(int i){
	if(e[i].l == e[i].r)return ;
	pushup(i * 2,lazy[i]);
	pushup(i * 2 + 1,lazy[i]);
	lazy[i] = 0;
}

void build(int i,int l,int r){
	e[i].l = l;
	e[i].r = r;
	if(l == r){
		e[i].lw = e[i].rw = a[l];
		e[i].flag = true;
		return ;
	}
	int mid = (l + r) / 2;
	build(i * 2,l,mid);
	build(i * 2 + 1,mid + 1,r);
	merge(i);
}

void update(int i,int l,int r,int w){
	if(e[i].l >= l && e[i].r <= r){
		pushup(i,w);
		return ; 
	}
	pushdown(i);
	int mid = (e[i].l + e[i].r) / 2;
	if(mid >= l)update(i * 2,l,r,w);
	if(mid < r)update(i * 2 + 1,l,r,w);
	merge(i);
}

node query(int i,int l,int r){
	if(e[i].l >= l && e[i].r <= r)return e[i];
	pushdown(i);
	int mid = (e[i].l + e[i].r) / 2;
	node ans;
	node ans1;
	node ans2;
	if(mid >= r)return query(i * 2,l,r);
	else if(mid < l)return query(i * 2 + 1,l,r);
	else {
		ans1 = query(i * 2,l,mid);
		ans2 = query(i * 2 + 1,mid + 1,r);
		renewans(ans,ans1,ans2);
	}
	return ans;
}

signed main(){
	cin>>n>>m;
	for(int i = 1;i <= n;i ++)a[i] = read();
	build(1,1,n);
	while(m --){
		int op;
		int l,r,w;
		op = read();
		if(op == 1){
			l = read(),r = read(),w = read();
			update(1,l,r,w);
		}
		else {
			l = read(),r = read();
			node ans = query(1,l,r);
			if(ans.flag == true)puts("Yes");
			else puts("No");
		}
	}
	return 0;
}
```

---

## 作者：Hexarhy (赞：15)

### Preface

数据结构练手题。不过写的时候中途翻帖子发现线段树常数大会 T，改用树状数组了。

建议先通过[P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)。

### Solution

容易发现一个序列为先辈的充要条件时**这个区间（不严格）单调递增**。

具体证明请参考其余题解，本文将重点将数据结构实现方面。

不难想到，判断一个子序列单调递增，等价于判断这个子序列的**差分数组 $s_i$ 均非负**。考虑如何很好地维护。

一种简单的想法是：$s_i<0$ 对应成 $0$，否则 $s_i$ 为正数对应成 $1$。那么树状数组就维护这个只由 $0/1$ 组成的区间和即可。

至于查询，只要 $(l,r]$ 的区间和等于 $r-l$ 即可。开区间是因为区间首一定满足单调递增的性质。

对于区间 $[l,r]$ 加 $x$，对于差分数组 $s_i$ 的影响只是两端，即 $s_l=s_l+x,s_{r+1}=s_{r+1}-x$。在此基础上维护树状数组即可，只需要单点修改。具体地说，对当前数 $a$，要改成 $b$，等价于在这个位置加上 $b-a$。

### Notice

- 注意等号是否取到。

- 开 `long long`。

### Code

**本代码需要C++ 11。**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;
typedef const int cint;
cint MAXN=1e6+5;
int n,m;
int a[MAXN],s[MAXN];

class BIT//模板
{
private:
	int tree[MAXN];
	#define lowbit(x) (x&(-x))
public:
	void modify(int pos,cint x)
	{
		for(;pos<=n;pos+=lowbit(pos))	tree[pos]+=x;
	}
	int query(int pos)
	{
		int res=0;
		for(;pos;pos-=lowbit(pos))	res+=tree[pos];
		return res;
	}
}t;

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1;i<=n;i++)	s[i]=a[i]-a[i-1];//求差分数组
	auto trans=[=](const ll x){return int(x>=0);};//把非负转为1
	for(int i=1;i<=n;i++)	t.modify(i,trans(s[i]));
	while(m--)
	{
		int opt,l,r;cin>>opt>>l>>r;
		if(opt==1)//按照刚才说的更新答案
		{
			int x;cin>>x;
			t.modify(l,trans(s[l]+x)-trans(s[l]));s[l]+=x;
			t.modify(r+1,trans(s[r+1]-x)-trans(s[r+1]));s[r+1]-=x;
		}
		if(opt==2)
			cout<<(t.query(r)-t.query(l)==r-l?"Yes":"No")<<endl;
	}
	return 0;
}
```

---

## 作者：试试事实上吗 (赞：9)

线段树入门题。

题意很清晰，通过观察屑的定义，可以发现先辈有如下性质：

​												对于长度为$n$序列$a$，如果它是先辈，那么它满足：

​                                                                 $a_1\le a_2\le a_3 \cdots\le a_n$

为什么呢？通过观察，我们发现先辈的后缀中除了它自己外，它的最长后缀的需要满足的关系最强（即如上性质），而其他后缀需要满足的关系是它的子集，比如第二长的后缀需要满足的关系是$a_1\le a_3, a_2\le a_4 \cdots$，显然更弱，所以说问题转化成了：

1. 区间加
2. 询问一个区间是否单调上升

然后变成了线段树裸题。

具体做法：线段树维护区间左端点的值$lv$，区间右端点的值$rv$，区间是否是先辈。$pushup$时，如果一段区间的左右儿子都是先辈，并且左儿子的$rv$小于等于右儿子的$lv$，则这段区间是先辈，询问同理。

不要试图抄我的代码，直接交会$wa$一个点

代码（很短的）：

```cpp
inline void update(int u,ll k)
{
    tr[u].lv+=k;tr[u].rv+=k;tr[u].la+=k;
}

inline void pushup(Node &u,const Node &a,const Node &b)
{
    u.lv=a.lv;u.rv=b.rv;
    u.is=a.is&&b.is&&(a.rv<b.lv);
}

inline void pushdown(int u)
{
    if(!tr[u].la) return;
    update(u<<1,tr[u].la);update(u<<1|1,tr[u].la);
    tr[u].la=0;
}

void build(int u,int l,int r)
{
    if(l==r) {tr[u].lv=tr[u].rv=a[l];tr[u].is=1;return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid);build(u<<1|1,mid+1,r);
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

void modify(int u,int l,int r,int x,int y,ll val)
{
    if(x<=l&&r<=y) return update(u,val);
    int mid=(l+r)>>1;
    pushdown(u);
    if(x<=mid) modify(u<<1,l,mid,x,y,val);
    if(y>mid) modify(u<<1|1,mid+1,r,x,y,val);
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

Node query(int u,int l,int r,int x,int y)
{
    if(x<=l&&r<=y) return tr[u];
    int mid=(l+r)>>1;
    pushdown(u);
    if(y<=mid) return query(u<<1,l,mid,x,y);
    if(x>mid) return query(u<<1|1,mid+1,r,x,y);
    Node ans;pushup(ans,query(u<<1,l,mid,x,y),query(u<<1|1,mid+1,r,x,y));
    return ans;
}

template<typename T>
inline void read(T &x)
{
    char c;int f=1;
    while(!isdigit(c=getchar())) (c=='-')&&(f=-1);
    x=c^48;
    while(isdigit(c=getchar())) x=x*10+(c^48);
    x*=f;
}

int main()
{
    int t,opt,x,y;
    ll val;
    read(n);read(t);
    for(int i=1;i<=n;++i) read(a[i]);
    build(1,1,n);
    while(t--)
    {
        read(opt);read(x);read(y);
        if(opt==1) read(val),modify(1,1,n,x,y,val);
        else printf("%s\n",query(1,1,n,x,y).is?"Yes":"No");
    }
    return 0;
}
```





---

## 作者：SDqwq (赞：6)

### 思路

我们要确定 $a$ 是否比 $a$ 后缀屑，由于只比较 $\min(n,m)$，所以可以考虑用 $a$ 的每个前缀与其相等长度的后缀进行比较。

要使每个前缀都比跟它长度相等的后缀屑，我们依次看每一项需要满足的条件。

对于 $a_1$，发现对于长度为 $1$ 的后缀，$a_1\le a_n$；对于长度为 $2$ 的后缀，$a_1\le a_{n-1}$；......；对于长度为 $n-1$ 的后缀，$a_1\le a_2$。那么 $a_1$ 就必须小于等于 $a_2$ 到 $a_n$ 的所有数。

同理，$a_i$ 必须小于等于 $a_{i+1}$ 到 $a_n$ 的所有数。

于是我们知道，$a$ 是先辈等价于 $a$ 单调不降。

再来观察操作，我们要查询一个区间是否为先辈，也就是区间是否单调不降。

一个很常见的套路是考虑将序列差分，若该区间对应的差分序列都 $\ge0$ 则说明单调不降。

考虑用线段树维护差分序列的区间 $\min$，修改操作在两个端点修改，查询时在线段树中查询最小值，若 $\ge0$ 则为先辈。

### 代码

```cpp
#include <cstdio>
#include <iostream>
#define ll long long
#define lson p << 1
#define rson p << 1 | 1
using namespace std;
const int N = 1e6 + 5;

ll a[N];

struct node {
	int l, r;
	ll mn;
} t[N << 2];
void pushup(int p) {t[p].mn = min(t[lson].mn, t[rson].mn);}
void build(int p, int l, int r) {
	t[p].l = l;
	t[p].r = r;
	if (l == r) return t[p].mn = a[l + 1] - a[l], void();
	int mid = l + r >> 1;
	build(lson, l, mid);
	build(rson, mid + 1, r);
	pushup(p);
}
void update(int p, int x, ll d) {
	if (t[p].l == t[p].r) return t[p].mn += d, void();
	int mid = t[p].l + t[p].r >> 1;
	if (x <= mid) update(lson, x, d);
	else update(rson, x, d);
	pushup(p);
}
ll query(int p, int l, int r) {
	if (l <= t[p].l && r >= t[p].r) return t[p].mn;
	int mid = t[p].l + t[p].r >> 1;
	ll res = 1e18;
	if (l <= mid) res = min(res, query(lson, l, r));
	if (r > mid) res = min(res, query(rson, l, r));
	return res;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	build(1, 1, n - 1);
	while (m--) {
		int op, l, r;
		ll x;
		scanf("%d %d %d", &op, &l, &r);
		r = min(r, n);
		if (op & 1) {
			scanf("%lld", &x);
			if (l > 1) update(1, l - 1, x);
			update(1, r, -x);
		}
		else puts(query(1, l, r - 1) >= 0 ? "Yes" : "No");
	}
	return 0;
}
```

---

## 作者：Transfixion_ (赞：4)

题目链接：[$\texttt{Link}$](https://www.luogu.com.cn/problem/P6812)
## $\textbf{Description}$
屑和先辈的定义都很直观，只要不是和我一样把**后缀**当成**后缀和**就能得出结论：

> 一个区间为先辈的充要条件为该区间**不严格**单调递增。

那么本题就变成了 给定一个序列，要求实现：

- 区间加。

- 查询区间是否单增。

## $\textbf{Solution}$
主要来看看操作二。

显然地，一个序列非严格单增的充要条件为原序列的差分数组非负。

所以我们考虑差分：若一个区间的差分数组均非负，那么这个区间非严格单增。

查询区间非负如何用 $O(\log n)$ 的数据结构做呢？

其中一种可行的方案是负数映射为 $0$，非负数映射为 $1$，然后用树状数组维护区间和。

这样判断区间 $[l,r]$ 是否非严格递增就等价于判断区间 $(l,r]$ 的和与 $r-l$ 是否相等。

至于区间加，用差分可以很好地实现。对于一次区间加，我们同时对差分数组和树状数组进行修改。

其中差分的时间复杂度为 $O(1)$，树状数组是 $O(\log n) $。

注意要开 `long long`。

## $\textbf{AC Code}$
```cpp
#include <bits/stdc++.h>
#define int long long
const int N = 1e6 + 5;
int a[N], d[N];
int n, k;

inline int f(const int& x) {
	return x >= 0;
}

struct BIT {
	int c[N];
	inline int lowbit(int x) {
		return x & (-x);
	}
	
	inline void add(int x, int v) {
		for(; x <= n; x += lowbit(x))
			c[x]+=v;
	}
	inline int qry(int x) {
		int res = 0; 
		for(; x; x -= lowbit(x))
			res += c[x];
		return res;
	}
} bit;

inline void modify(int l, int r, int v) {
	bit.add(l, f(d[l] + v) - f(d[l]));
	bit.add(r + 1, f(d[r + 1] - v) - f(d[r + 1]));
	d[l] += v, d[r + 1] -= v;
}

inline bool check(int l, int r) {
	return bit.qry(r) - bit.qry(l) == r - l;
}

signed main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> k;
    for(int i = 1; i <= n; i++) {
    	std::cin >> a[i];
		d[i] = a[i] - a[i - 1];
    	bit.add(i, f(d[i]));
	}
	for(int opt, l, r, x; k--; ) {
		std::cin >> opt >> l >> r;
		if(opt == 1) {
			std::cin >> x;
			modify(l, r, x);
		} else {
			if(check(l, r)) puts("Yes");
			else puts("No");
		}
	}
    return 0;
}
```

---

## 作者：loveJY (赞：4)

> 结论:一个区间是先辈的充要条件是这个区间单调不降

证明:

区间单调不降的条件是对于任意一个区间元素$a_i$满足大于等于他前面的所有元素$a_j$

1. 充分性:

那么我们会发现对于一个先辈判断中任意一个后缀的一个元素一定只会和他前面的元素比较大小,而该区间不降,所以这个比较一定符合条件,所以我们就能得出所有的屑比较都能成立

由此可得出该区间是先辈

2. 必要性

其实没必要证明这一步,我们只需要找到充分条件就好....

一个区间已经是先辈,那么我们会发现对于任意的$i<j$,我们选取先辈比较中的以$j-i$号元素开头的后缀比较,那么这组比较中第i次比较一定是比较了i和j两个元素,并满足了$a_i<=a_j$,进而可知任何i<j均有$a_i<=a_j$,所以该区间不降

### 做法:

问题变成:

* 查询某区间是否单调不降
* 区间修改

利用线段树维护原序列差分数组,那么我们能看出第一个$[l,r]$查询只需要看$[l+1,r]$这一段差分数组的最小值是否大于等于0即可

同理,我们区间修改就变成了线段树上两个单点修改:$l$处$+x$
,$r+1$处$-x$

update in 2020/9/17：

由于加强了数据，只开1e6的数组并不能通过

而且由于线段树的神奇机制在超过n的边界处会有些问题

所以代码有些更改

code:

```cpp

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e6 + 7;//开大
const int inf = 1e9 + 7;
int n, m, root;
int a[MAXN], b[MAXN];
int ls[MAXN], rs[MAXN], minx[MAXN], T;
inline void build(int &k, int l, int r) {
	if(!k) {
		k = ++T;
	}
	if(l == r) {
		minx[k] = b[l];
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls[k], l, mid);
	build(rs[k], mid + 1, r);
	minx[k] = min(minx[ls[k]], minx[rs[k]]);
}

inline void modify(int k, int l, int r, int P, int V) {
	if(l == r) {
		minx[k] += V;
		return;
	}
	int mid = (l + r) >> 1;
	if(P <= mid)modify(ls[k], l, mid, P, V);
	else modify(rs[k], mid + 1, r, P, V);
	minx[k] = min(minx[ls[k]], minx[rs[k]]);
}

inline int query(int k, int l, int r, int L, int R) {
	if(L <= l && r <= R) {
		return minx[k];
	}
	int mid = (l + r) >> 1;
	if(R <= mid)return query(ls[k], l, mid, L, R);
	else if(L > mid)return query(rs[k], mid + 1, r, L, R);
	else return min(query(ls[k], l, mid, L, R), query(rs[k], mid + 1, r, L, R));
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= n; ++i) {
		b[i] = a[i] - a[i - 1];
	}
	build(root, 1, n);
	for(int i = 1, opt, l, r, x; i <= m; ++i) {
		scanf("%d", &opt);
		if(opt == 1) {
			scanf("%d%d%d", &l, &r, &x);
			modify(root, 1, n, l, x);
			if(r+1<=n)//判边界
				modify(root, 1, n, r + 1, -x);
		} else {
			scanf("%d%d", &l, &r);
			if(l == r) {
				puts("Yes");
				continue;
			}
			int minx = query(root, 1, n, l + 1, r);
			if(minx < 0)puts("No");
			else puts("Yes");
		}
	}
	return 0;
}




```

---

## 作者：DPair (赞：2)

提供一种本题的另类解法

## 思路

首先不难发现，一个区间是 “先辈” 当且仅当它 **单调不降**

考虑它比它每一个后缀都 “屑” ，结合其定义显然每一位要小于等于后面的所有位，也就是单调不降

此时已经可以直接上线段树了，但是线段树的做法比较 naive ，还有一些性质我们尚未发掘

发现一个区间不 “先辈” 是必然存在 $a_i > a_{i + 1}$

差分之后发现就是 $a_{i+1}-a_i < 0$

因此判断差分后区间内是否存在负数即可

显然差分之后区间加变成了单点修改，那么正负性可以直接在原序列上操作

考虑这样还是要用线段树什么的

但是注意到我们现在维护的其实是一个 01 序列，支持单点修改区间查询 1 是否存在

因此我们考虑压位，这里可以使用压位 Trie

压位 Trie 支持维护一个集合支持加点删点以及查询前驱后继，我们考虑查询 $l$ 的 **严格后继** ，判断其是否在区间中即可

然后就能轻松拿到最优解了

## 代码
~~贺的自己日报~~
```cpp
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,s,t) for(int i=(s),i##END=(t);i<=i##END;++i)
#define per(i,t,s) for(int i=(t),i##END=(s);i>=i##END;--i)
#define REP(i,s,t) for(int i=(s),i##END=(t);i<i##END;++i)
#define PER(i,t,s) for(int i=(t),i##END=(s);i>i##END;--i)
#define elif else if
namespace MyMinMax{
template <typename T>
inline T mn(const T x, const T y) {return x < y ? x : y;}
template <typename T>
inline T mx(const T x, const T y) {return x > y ? x : y;}
template <typename T>
inline bool chmin(T &x, const T y) {return (x > y) && ((x = y), 1);}
template <typename T>
inline bool chmax(T &x, const T y) {return (x < y) && ((x = y), 1);}
template <typename T, typename ...Args>
inline T mx(const T x, const Args ...args) {return mx(x, mx(args...));}
template <typename T, typename ...Args>
inline T mn(const T x, const Args ...args) {return mn(x, mn(args...));}
}
using namespace MyMinMax;

// 省略了丑陋的快读

typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL INFll = 0x3f3f3f3f3f3f3f3fll;
/* My Code begins here */

namespace BITWISE{
    inline int clz(unsigned long long x){return __builtin_clzll(x);}
    inline int ctz(unsigned long long x){return __builtin_ctzll(x);}
} // namespace BITWISE
using namespace BITWISE;

typedef unsigned long long ull;
const int g = 6;
const int mod = (1 << g) - 1;
ull BUFF[1 << 20], *BT = BUFF + sizeof(BUFF) / sizeof(ull);
inline ull *alloc(int sz){return BT -= sz;}
struct Trie{
    int dep;ull *a[5];
    Trie(int sz){
        dep = 1; for(;;++ dep){
            int cnt = (sz + (1ull << g * dep) - 1) >> g * dep;
            a[dep - 1] = alloc(cnt);
            if(cnt == 1) return ;
        }
    }
    inline void ins(int x){
        for (int i = 0;i < dep;++ i){
            ull p = 1ull << (x >> i * g & mod); 
            if(a[i][x >> (i + 1) * g] & p) return ;
            a[i][x >> (i + 1) * g] |= p;
        }
    }
    inline void del(int x){
        for (int i = 0;i < dep;++ i)
            if(a[i][x >> (i + 1) * g] &= ~(1ull << (x >> i * g & mod))) return ;
    }
    inline int succ(int x){
        for (int i = 0;i < dep;++ i){
            int cur = (x >> i * g) & mod;ull v = a[i][x >> (i + 1) * g];
            if(v >> cur > 1){
                int res = x >> (i + 1) * g << (i + 1) * g;
                res += (ctz(v >> (cur + 1)) + cur + 1) << i * g;
                for (int j = i - 1;~j;-- j) res += ctz(a[j][res >> (j + 1) * g]) << j * g;
                return res;
            }
        }
        return 1919810;
    }
};

Trie s(1 << 20);

const int MAXN = 1e6 + 5;
int n, m; LL a[MAXN];

signed main() {
    read(n, m); read(a, a + n); per(i, n - 1, 1) a[i] -= a[i - 1];
    REP(i, 0, n) if(a[i] < 0) s.ins(i);
    while(m --) {
        int opt = read(); int l = read() - 1; int r = read() - 1;
        if(opt == 2) print(s.succ(l) > r? "Yes" : "No");
        else { const int x = read();
            if(a[l] < 0 && a[l] + x >= 0) s.del(l);
            if(a[l] >= 0 && a[l] + x < 0) s.ins(l);
            if(r + 1 < n) {
                if(a[r + 1] < 0 && a[r + 1] - x >= 0) s.del(r + 1);
                if(a[r + 1] >= 0 && a[r + 1] - x < 0) s.ins(r + 1);
            } a[l] += x; a[r + 1] -= x;
        }
    }
}
```

---

## 作者：HPXXZYY (赞：2)

$\color{blue}{\texttt{[Solution]}}$

一看 `屑` 和 `先辈` 的定义，我们就不由自主地联想到：如果一个序列 $a_{1 \cdots k}$ 满足：

$$a_1 \leq a_2 \leq a_3 \leq a_4 \leq \cdots \leq a_k$$

那么序列 $a$ 就是一个 `先辈`。

> 为什么呢？如果序列 $a$ 是一个 `先辈` 的话，因为它比它的所有后缀都 `屑`，我们考虑后缀 $a_{2 \cdots k}$，有：
> $$a_1 \leq a_2,a_2 \leq a_3,a_3 \leq a_4, \cdots ,a_{k-1} \leq a_k$$
> 所以有 $a_1 \leq a_2 \leq a_3 \leq \cdots \leq a_k$。

所以如果一个序列 $a$ 内部元素递增（**非严格**）的话，它就一个 `先辈`。

如何判断一个序列 $a$ 内部元素是否非严格递增呢？我们知道，如果一个数大于等于另一个数，那么它们的差 $\geq 0$，所以，我们可以考虑差分。

我们将序列差分（记差分数组为 $\texttt{c}$），如果 $\forall i \in [l+1,r],c_i \geq 0$，则序列 $a_{l \cdots r}$ 就是一个 `先辈`。

如何快速地查询呢？肯定不能一个一个数地判断。怎么办呢？很简单，如果 $\min\limits_{i \in [l+1,r]} c_i \geq 0$ 的话，序列 $a_{l \cdots r}$ 就是一个 `先辈`。

所以我们对序列差分，用一个线段树维护这个序列即可（修改变成单点修改，查询变成询问最小值）。

时间复杂度：$O(k \times \log n+n \times \log n)$。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=1e6+100;
typedef long long ll;
ll minn[N<<2];int n,m,a[N];
inline void pushup(int o){
	minn[o]=min(minn[o<<1],minn[o<<1|1]);
}
void build(int o,int l,int r){
	if (l==r){minn[o]=a[l]-a[l-1];return;}
	register int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	pushup(o);return;
}
void update(int o,int l,int r,int p,ll v){
	if (l==r){minn[o]+=v;return;}
	register int mid=(l+r)>>1;
	if (p<=mid) update(o<<1,l,mid,p,v);
	else update(o<<1|1,mid+1,r,p,v);
	pushup(o);return;
}
ll query(int o,int l,int r,int p,int q){
	if (p<=l&&r<=q) return minn[o];
	int mid=(l+r)>>1;ll ans=1ll<<60;
	if (p<=mid) ans=min(ans,query(o<<1,l,mid,p,q));
	if (mid<q) ans=min(ans,query(o<<1|1,mid+1,r,p,q));
	return ans;
}
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	build(1,1,n);//建树 
	for(int i=1;i<=m;i++){
		int opt=read(),l,r,v;
		if (opt==1){
			l=read();r=read();v=read();
			update(1,1,n,l,v);//c[l]+=v
			update(1,1,n,r+1,-v);//a[r+1]-=v
		}
		else{
			l=read();r=read();
			if (query(1,1,n,l+1,r)>=0)
				printf("Yes\n");//递增 
			else printf("No\n");//非增 
		}
	}
	return 0;
}
```

---

## 作者：Skyjoy (赞：2)

# upd2020.9.17: 修改了题解中的一些被 hack 的细节问题还有数据的扩大问题

**hacker ： @[zimindaada](https://www.luogu.com.cn/user/134635)**

# 线段树模板题

~~这道题屑爆了~~

# 题目思路

> 显然，当一个数列 $a$ 单调不递减时，即 $a_1\le a_2\le ... \le a_n$ 时，这个 $a$ 就是个先辈序列

以上结论，我们只需要全部取 $|b|=1$ 即可简单说明

那这道题就转化成了整这样的操作：

- 区间修改

- 查询一个区间是否单调不递减

由此可知，我们为了查询一个区间的单调性，我们用一个线段树维护一手差分序列。但是每一次都查询一整个区间的效率着实不高，所以我们只需要查询差分序列的最小值是否非负即可，即看 $[l+1,r]$ 区间内
的差分值的最小值是否非负

所以我们只需要将查询是否单调不递减的操作改成查询 $[l+1,r]$ 中的最小值，然后将区间修改改成对 $l$ 点加 $x$ 、对 $r+1$ 点加 $-x$ 的修改操作。**注意：因为单点修改时可能会修改到** $n+1$ **，所以我们递归操作时的上界必须改成** $n+1$ ，详情见代码

# 代码讲解：

直接苟爆线段树模板

```cpp
#include<bits/stdc++.h>
#define ls(k) k<<1
#define rs(k) k<<1|1
using namespace std;
const int N=1000010;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
} 
int tree[N<<2],a[N],w[N],n,m,op,l,r,x;
void pushup(int k){
	tree[k]=min(tree[ls(k)],tree[rs(k)]);
}
void build(int k,int l,int r){
	if(l==r){
		tree[k]=w[l];
		return;
	}
	int mid=(l+r)/2;
	build(ls(k),l,mid),build(rs(k),mid+1,r);
	pushup(k);
}
void modify(int q,int l,int r,int k,int v){//单点修改
	if(l==r){
		tree[k]+=v;
		return;
	}
	int mid=(l+r)/2;
	if(q<=mid){
		modify(q,l,mid,ls(k),v);
	}
	else{
		modify(q,mid+1,r,rs(k),v);
	}
	pushup(k);
}
int query(int ql,int qr,int l,int r,int k){//区间查询
	int res=0x7fffffff;
	if(ql<=l&&r<=qr){
		return tree[k];
	}
	int mid=(l+r)/2;
	if(ql<=mid){
		res=min(res,query(ql,qr,l,mid,ls(k)));
	}
	if(mid<qr){
		res=min(res,query(ql,qr,mid+1,r,rs(k)));
	}
	return res;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(int i=1;i<=n;i++){
		w[i]=a[i]-a[i-1];
	}
	build(1,1,n+1);//注意了
	while(m--){
		op=read();
		if(op==1){
			l=read(),r=read(),x=read();
			modify(l,1,n+1,1,x),modify(r+1,1,n+1,1,-x);
		}
		if(op==2){
			l=read(),r=read();
			if(query(l+1,r,1,n+1,1)>=0){
				printf("Yes\n");
			}
			else{
				printf("No\n");
			}
		}
	}
	return 0;
}
```

# 总结：

线段树的题目通常支持的操作不难，可是题意通常会表达得比较隐晦，所以我们一定要开动小脑筋，这样才能发现题目中的深意，从而解决问题

# 联赛已经开始报名了，祝各位小伙伴们厚积薄发，在最终阶段认真冲刺，取得理想的成绩！

---

## 作者：Spasmodic (赞：2)

可能是全场最水的一道题……

### 1.题意
我相信我已经说的很清楚了。
### 2.题解
先看部分分。
#### Subtask 1
读题分。

全部输出 $\texttt{Yes}$ 即可。
#### Subtask 2
暴力模拟即可，复杂度 $O(n^2k)$，期望得分 $10$ 分。
#### Subtask 3
这里需要用到一个小结论：一个序列是先辈的充分必要条件是这个序列单调不降。

充分条件显然，必要条件只要取条件里的后缀为序列的第二个后缀即可。

暴力模拟即可，复杂度 $O(nk)$，期望得分 $20$ 分。
#### Subtask 4
考虑使用 ST表 维护序列。

考虑预处理的时候怎么合并。

我们会发现，合并之后的结果是先辈当且仅当左边是先辈且右边是先辈且左边最大值不大于右边最小值。

你也许会以为我还要维护最大值和最小值，其实不然，因为他是先辈，所以直接取左端点和右端点就行了。

查询只要保证左边和右边都是先辈即可，总复杂度为 $O(n\log n+k)$，结合 Subtask 3 期望得分 $30$ 分。

#### Subtask 5
同上，每次修改时重构 ST表。

设查询个数为 $q$ ，则总复杂度为 $O(nq\log n+k-q)$，结合 Subtask 3 期望得分 $40$ 分。
#### Subtask 6
考虑分块，每块维护这一块是不是先辈。

修改的时候在完整的块上打区间减的 tag，这是因为整体做减法不会影响是不是先辈，当然边角是暴力减法，然后块内重构，复杂度$O(\sqrt n)$。

查询的时候只要将区间分成 $O(\sqrt n)$ 段（边角部分一个一段，中间一块作为一段），然后只要每段都是先辈，且每段的最后一项小于等于下一段的第一项即可。

总复杂度 $O(k\sqrt n)$，期望得分 $60$ 分。
#### Subtask 7
考虑线段树维护区间，每个节点维护区间最小值，最大值以及是不是先辈。

修改的时候直接打区间减的 lazy-tag，这是因为整体做减法不会影响是不是先辈。

查询的时候同时查三个信息，将两条信息合并与 Subtask 4 中的讲解类似。

总复杂度 $O(k\log n)$，期望得分 $100$ 分。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=500005,INF=0x3f3f3f3f3f3f3f3f;
ll n,m,h[N];
struct node{
    ll mi,ma;
    bool xianbei;
    node(ll _mi=0,ll _ma=0,ll _xianbei=0){mi=_mi,ma=_ma,xianbei=_xianbei;}
    node operator+(const node&x)const{
        node ret;
        ret.mi=min(mi,x.mi),ret.ma=max(ma,x.ma);
        ret.xianbei=xianbei&&(x.xianbei)&&(x.mi>=ma);
        return ret;
    }
}sum[N<<2];
ll add[N<<2];
void pushup(ll k){sum[k]=sum[k<<1]+sum[k<<1|1];}
void build(ll k,ll l,ll r){
    if(l==r){
        sum[k]=node(h[l],h[l],1);
        return;
    }
    ll mid=l+r>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    pushup(k);
}
void Add(ll k,ll l,ll r,ll v){
    add[k]+=v;
    sum[k].mi+=v;
    sum[k].ma+=v;
}
void pushdown(ll k,ll l,ll r,ll mid){
    if(!add[k])return;
    Add(k<<1,l,mid,add[k]);
    Add(k<<1|1,mid+1,r,add[k]);
    add[k]=0;
}
void modify(ll k,ll l,ll r,ll x,ll y,ll v){
    if(x<=l&&r<=y){
        Add(k,l,r,v);
        return;
    } 
    ll mid=l+r>>1;
    pushdown(k,l,r,mid);
    if(x<=mid)modify(k<<1,l,mid,x,y,v);
    if(mid<y)modify(k<<1|1,mid+1,r,x,y,v);
    pushup(k);
}
node query(ll k,ll l,ll r,ll x,ll y){
    if(x<=l&&r<=y)return sum[k];
    ll mid=l+r>>1;
    node ret=node(INF,-INF,1);
    pushdown(k,l,r,mid);
    if(x<=mid)ret=ret+query(k<<1,l,mid,x,y);
    if(mid<y)ret=ret+query(k<<1|1,mid+1,r,x,y);
    return ret;
} 
int main(){
    scanf("%lld%lld",&n,&m);
    for(ll i=1;i<=n;i++)scanf("%lld",&h[i]);
    build(1,1,n);
    for(ll t,l,r,v;m--;){
        scanf("%lld%lld%lld",&t,&l,&r);
        if(t==1)scanf("%lld",&v),modify(1,1,n,l,r,v);
        else puts(query(1,1,n,l,r).xianbei?"Yes":"No");
    }
    return 0;
}
```
---

UPD：在加强数据之后，上面的代码因为常数过大T飞了，我们需要一个新的做法。

考虑维护差分数列，显然 $[l,r]$ 事先辈等价于 $[l+1,r]$ 这段区间内的差分序列全部非负。

那么我们直接用树状数组维护即可，复杂度 $O(n\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000005;
int n,m;
ll h[N],g[N],bit[N];
int sgn(ll x){return x>=0?1:0;}
void update(ll id,ll x){for(;id<=n;id+=id&-id)bit[id]+=x;}
ll sum(ll id){ll ret=0;for(;id;id-=id&-id)ret+=bit[id];return ret;}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%lld",&h[i]),g[i]=h[i]-h[i-1],update(i,sgn(g[i]));
    ll v;
    for(int t,l,r;m--;){
        scanf("%d%d%d",&t,&l,&r);
        if(t==1){
			scanf("%lld",&v);
			update(l,sgn(g[l]+v)-sgn(g[l]));g[l]+=v;
			update(r+1,sgn(g[r+1]-v)-sgn(g[r+1]));g[r+1]-=v;
		}
        else puts(sum(r)-sum(l)==r-l?"Yes":"No");
    }
    return 0;
}
```

---

## 作者：云浅知处 (赞：1)

随机跳题跳到的萌萌题。

注意到一个结论：**对于 $a_1,a_2,\cdots,a_k$，它是「先辈」当且仅当它必然是一个不降序列。**

事实上，如果这个序列是「先辈」，那么取后缀 $a_2,a_3,\cdots,a_k$，我们得到：

$$
\forall\ i\le n-1,a_i\le a_{i+1}
$$

这表明它是不降的，充分性得证。必要性是显然的。

这样一来，我们需要支持的操作就只有两种：

- 区间加；
- 查询一个区间是否为不降序列。

考虑差分：令 $c_i=a_{i+1}-a_i$，那么 $a_l,a_{l+1},\cdots,a_r$ 单调不降等价于 $\forall\ l\le i\le r-1,c_i\ge 0$，即

$$
\min_{i\in[l,r-1]}c_i\ge 0
$$

而区间加相当于差分序列上的单点修改。这样，只需要支持差分序列上的单点修改与区间查询最小值，用线段树维护即可。

```cpp
#include<bits/stdc++.h>

#define int long long
#define lson(o) (o<<1)
#define rson(o) (o<<1|1)

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

const int INF=1e15;
const int MN=1e6+5; 
int n,q;
int a[MN],c[MN];

struct SegTree{
	int d[MN<<2];
	
	inline void pushup(int o){
		d[o]=min(d[lson(o)],d[rson(o)]);
	}
	
	inline void build(int l,int r,int o){
		if(l==r){d[o]=c[l];return ;}
		int mid=(l+r)>>1;
		build(l,mid,lson(o));
		build(mid+1,r,rson(o));
		pushup(o);
	}
	
	inline int query(int l,int r,int ql,int qr,int o){
		if(l<=ql&&qr<=r)return d[o];
		int mid=(ql+qr)>>1,ans=INF;
		if(l<=mid)ans=min(ans,query(l,r,ql,mid,lson(o)));
		if(r>mid)ans=min(ans,query(l,r,mid+1,qr,rson(o)));
		return ans;
	}
	
	inline void modify(int pos,int k,int ql,int qr,int o){
		if(ql==qr){d[o]+=k;return ;}
		int mid=(ql+qr)>>1;
		if(pos<=mid)modify(pos,k,ql,mid,lson(o));
		else modify(pos,k,mid+1,qr,rson(o));
		pushup(o);
	}
};

SegTree tree;

signed main(void){
	
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read();n-=1;
	for(int i=1;i<=n;i++)c[i]=a[i+1]-a[i];
	tree.build(1,n,1);
	
	while(q--){
		int op=read(),l=read(),r=read();
		if(op==1){
			int x=read();
			tree.modify(l-1,x,1,n,1);
			tree.modify(r,-x,1,n,1);
		}
		else puts((l==r)?("Yes"):((tree.query(l,r-1,1,n,1)>=0)?("Yes"):("No")));
	}

    return 0;
}
```

---

## 作者：H0ndomach1 (赞：1)

# [洛谷P6812](https://www.luogu.com.cn/problem/P6812)
## 维护：
由题可得，**先辈序列即为不下降序列**，需满足 $a_i \le a_j$ 并且 $i \le j$。判断一个序列是否为先辈我们比较的是一个元素和前一个元素的大小关系。所以我们可以将原序列进行一次差分来对比其是否为先辈序列。  
	如果差分后的序列中的某个元素小于 $0$，说明其原序列中对应的元素小于前面的元素,则序列不为先辈。如果差分后序列中的元素均大于等于 $0$，说明其符合条件。
	所以我们可以利用线段树维护某段区间最小值并且判断最小值是否小于 $0$。
    
------------
## 修改：
对于题目的区间加法，由于差分数组在区间加法中的特性，对原序列 $[l,r]$，相当于在差分序列中 $l$ 处 $+x$,$r+1$ 处 $-x$。所以我们只需要对这两个点进行单点修改即可。
**至此，我们就将原问题转化成了线段树区间查询和单点修改的模板题。** 
## 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define MAXN 1008600
#define int long long
using namespace std;
int n,m,ch;
int c[MAXN];
int a[MAXN];
struct T{
    int l,r;
    long long val;
}t[MAXN*4];

inline void updata(int node){
    t[node].val=min(t[node<<1].val,t[node<<1|1].val);//维护区间最小值
}
int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

inline void build(int l,int r,int node){
    t[node].l=l;
    t[node].r=r;
    if(l==r){
        t[node].val=c[l];
        return;
    }
    int mid=(l+r)/2;
    build(l,mid,node<<1);
    build(mid+1,r,node<<1|1);
    updata(node);
}

inline void change(int p,int node,int k){
    if(t[node].l==t[node].r){
        t[node].val+=k; 
        return;
    }
    
    int mid=(t[node].l+t[node].r)/2;
    if(p<=mid)change(p,node<<1,k);
    else change(p,node<<1|1,k); 
    updata(node);
}


inline long long ask(int l,int r,int node){
    long long ans=0x7fffffff;
    if(l<=t[node].l&&t[node].r<=r){
        return t[node].val;
    }
    int mid=(t[node].l+t[node].r)/2;
    if(l<=mid)ans=min(ans,ask(l,r,node<<1));
    if(r>mid)ans=min(ans,ask(l,r,node<<1|1));
    return ans;
}

signed main(){
    scanf("%d%d",&n,&m);

    for(int i=1;i<=n;i++){
        cin>>a[i];
    }

    for(int i=1;i<=n;i++){
       c[i]=a[i]-a[i-1];
    }

    int l,r,x,y;
    build(1,n+1,1);

    for(int i=1;i<=m;i++){
        ch=read();l=read();r=read();//若用cin会TLE

        if(ch==1){
            x=read();
            change(l,1,x);
            change(r+1,1,-x);
        }

        if(ch==2){
            if(ask(l+1,r,1)>=0)cout<<"Yes"<<"\n";
            else cout<<"No"<<"\n";
        }
        
    }

    return 0;
}
```
              

---

## 作者：killer_queen4804 (赞：1)

之前看题解做的，是用的线段树，现在又回来做发现自己用树状数组就过了，而且代码更短，思路也比线段树的简单。我们通过题意知道如果这个区间是个非递减区间的话那么这个区间就是屑，那怎样来判断是否是非递减区间呢，很容易可以想到差分，设 $b$ 为差分数组，如果 $b$ 所对应的区间内有负数 $b[i]$ 说明第 $i$ 个元素是比第 $i-1$ 个元素要小的，所以不是非递减区间也就不是屑，但我们不可能去一个元素一个元素的去遍历，我们可以让 $b[i]<0$ 的价值为 $0$，$b[i]\geq0$ 的为 $1$，用树状数组 $t$ 去维护这个价值，如果 $ask(r)-ask(l)=r-l$ 说明这区间满足条件，因为 $b[l]$ 作为区间首一定是递增（只有 $1$ 个元素一定是单调递增的呀）的所以要从 $l+1$ 开始，所以才有的上面的式子，这个题也就比线段树更优雅的做完了
```cpp
#include<bits/stdc++.h>
#define ll long long
#define lowbit(i) ((-i)&(i))
using namespace std;
const ll inf=1e18;
const ll mod=1e9+7;
ll n,k,a[1000006],t[1000006],b[1000006];
void add(ll x,ll y){
    for(int i=x;i<=n;i+=lowbit(i))
        t[i]+=y;
}
ll ask(ll x){
    ll res=0;
    for(int i=x;i;i-=lowbit(i))
        res+=t[i];
    return res;
}
int main(){
	//freopen("in.txt","r",stdin);
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]),b[i]=a[i]-a[i-1],add(i,b[i]>=0);
    // cout<<ask(1)<<" "<<ask(2)<<" "<<ask(3)<<" "<<ask(4)<<" "<<ask(5)<<endl;
    while(k--){
        ll op,x,l,r;
        scanf("%lld",&op);
        if(op==1){
            scanf("%lld%lld%lld",&l,&r,&x);
            ll tm1=b[l],tm2=b[r+1];
            b[l]+=x;b[r+1]-=x;
           // cout<<ask(l)<<" s "<<l<<" ";
            if(tm1>=0&&b[l]<0) add(l,-1);
            if(tm1<0&&b[l]>=0){add(l,1);}
            if(tm2>=0&&b[r+1]<0) add(r+1,-1);
            if(tm2<0&&b[r+1]>=0) add(r+1,1);

            //cout<<ask(l)<<" "<<tm1<<" "<<b[l]<<endl;
        }
        else{
            scanf("%lld%lld",&l,&r);
            //cout<<ask(r)<<" "<<ask(l)<<" ss "<<endl;
            if(ask(r)-ask(l)==r-l) printf("Yes\n");
            else printf("No\n");
        }
    }
	return 0;
}

```


---

## 作者：JackMerryYoung (赞：1)

# 前言

~~作为学校作业，写了一天才写出来，真是吐血。~~

这是一道有关线段树的题目，其实肥肠简单，只不过容易写挂。

这道题目看起来定义有一点复杂，但是抛开理解难度不说，代码难度不大。

那么，废话不多说，开始讲题啦！

# 正文

观察屑的定义，我们发现将两个数列 $A$ 和 $B$ 按序一一对应，将多余部分去掉，如果 $A$ 的所有数都不比 $B$ 中与其对应的数小，那么 $B$ 就比 $A$ 屑。

那么既然有以上定义，不难发现如果一个数列是不降的，那么这个数列就是一个先辈。

何以见得？我们知道，显然，如果 $B$ 比 $A$ 屑，而 $C$ 又比 $B$ 屑，那么 $C$ 肯定比 $A$ 屑。

那么将这个问题递归求解。

我们先有三项：

$$
A_1 \le A_2 \le A_3
$$

令数列 $M_1 = \{A_3\}$，$M_2 = \{A_2, A_3\}$，$M_3 = \{A_1, A_2, A_3\}$。

$\because$ 将 $M_1$ 与 $M_2$ 排名，发现 $M_2$ 比 $M_1$ 屑，

又 $\because$ 将 $M_2$ 与 $M_3$ 排名，发现 $M_3$ 比 $M_2$ 屑，

$\therefore$ 归纳知 $M_3$ 屑于 $M_2$ 屑于 $M_1$。

又 $\because$ $M_1$、$M_2$ 都为 $M_3$ 的后缀。

$\therefore$ $M_3$ 比它任何的后缀都屑。

$\therefore$ 原命题得证。

那么推广一下结论：

对于一个长度为 $N$ 的数列 $A$，若符合

$$
\forall i \le N, s.t. A_{i-1} \le A_i
$$

那么 $A$ 为先辈。

下面介绍两种维护方式。

## 左右端点法

这种方式简单易懂，但有概率写挂。

维护区间的左右端点值，合并时判断是否为先辈。

判断方法：

若左、右区间都是先辈，且左区间的右端点值小于等于右区间的左端点值（保证不降），那么这整个区间都是先辈。

但是要写 Lazy，很讨厌，空间有可能要炸，怎么办？

第二种熟悉简单的方法出来了。

## 差分最小法

观察不降数列的性质，若有一个长度为 $N$ 的数列 $A$，若符合

$$
\forall i \le N, s.t. A_{i-1} \le A_i
$$

设差分数组 $X$，则有

$$
\forall i \le N, X_i = A_{i-1} - A_i
$$

那么，我们就有

$$
\forall i \le N, X_i \ge 0
$$

反过来，结论仍成立，即若 $X_{min}\ge 0$，则 $A$ 为先辈。

那么我们只要维护区间最小值即可。而这种事情线段树完全能够胜任。

# 代码

~~你们最想要的..~~ 

Talk is$\color{white}\text{n't}$ cheap, $\color{white}\text{Don't}$ show me the code..

``` cpp
#include <bits/stdc++.h>
#define ll long long
#define MAXN int(1e6 + 5)
using namespace std;

int N, K;
ll minn[MAXN * 4ll];
int arr[MAXN];

void merge(int p);
void build(int now_l, int now_r, int p);
void modify(int i, int now_l, int now_r, ll val, int p);
ll getans(int l, int r, int now_l, int now_r, int p);

int main()
{
	scanf("%d %d", &N, &K);
	for(int i = 1; i <= N; ++ i)
		scanf("%lld", &arr[i]);

	build(1, N, 1);
	for(int i = 1; i <= K; ++ i)
	{
		long long opt, l, r, x;
		scanf("%lld %lld %lld", &opt, &l, &r);
		if(opt == 1)
		{
			scanf("%lld", &x);
			modify(l, 1, N, x, 1);
			modify(r + 1, 1, N, -x, 1);
		}
		else
		{
			ll ans = getans(l + 1, r, 1, N, 1);
			if(ans >= 0) printf("Yes\n");
			else printf("No\n");
		}
	}
	return 0;
}

void merge(int p)
{
	minn[p] = min(minn[p << 1], minn[(p << 1) | 1]);
}

void build(int now_l, int now_r, int p)
{
	if(now_l == now_r)
	{
		minn[p] = arr[now_l] - arr[now_l - 1];
		return;
	}

	int mid = (now_l + now_r) >> 1;
	build(now_l, mid, p << 1);
	build(mid + 1, now_r, (p << 1) | 1);
	merge(p);
}

void modify(int i, int now_l, int now_r, ll val, int p)
{
	if(now_l == now_r) 
	{
		minn[p] += val;
		return;
	}

	int mid = (now_l + now_r) >> 1;
	if(i <= mid) modify(i, now_l, mid, val, p << 1);
	if(i >= mid + 1) modify(i, mid + 1, now_r, val, (p << 1) | 1);
	merge(p);
}

ll getans(int l, int r, int now_l, int now_r, int p)
{
	if(l <= now_l && r >= now_r)
		return minn[p];

	int mid = (now_l + now_r) >> 1;
	ll res = LLONG_MAX;
	if(l <= mid) res = min(res, getans(l, r, now_l, mid, p << 1));
	if(r >= mid + 1) res = min(res, getans(l, r, mid + 1, now_r, (p << 1) | 1));
	return res;
}
```

注：这里写的是差分法，第一种方法很多题解区大佬都想得到，我由于写挂了这里就不展示代码了。而且差分法跑得很快，代码十分简短，思维难度也没有很高，建议学习差分这种优秀思想。

---

## 作者：naroanah (赞：0)

### 简述题意：

- 进行区间修改；

- 查询某区间是否单调不递减。

这道题树状数组我感觉比较简单好理解，码量也不算太长，所以这道题用树状数组很合适。

### 前置芝士：

- [树状数组 2](https://www.luogu.com.cn/problem/P3368)
- 差分

### 做法:

这道题主要难点就是查询。

我们可以维护一个差分数组 $b$，如果一个序列单调不递减，那么对于 $\forall i \in [l+1,r]$，每一个 $b_i \ge 0$。

这样的话，我们可以把 $b_i \ge 0$ 看作 1，$b_i<0$ 看作是 0（即符合条件和不符合条件），用树状数组来维护这个01序列，最后查询区间和是否等于 $r-l$ 即可。

**一点小细节：** 记得开 long long ，读入的时候要用 `lld` ~~因为这些问题爆蛋了几次~~。

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
typedef long long ll;
typedef unsigned long long ull;
#define si(x) scanf("%lld",&x)
const ll MAXN=1e6+10;
ll tree[MAXN]; //树状数组
ll b[MAXN]; //差分
ll a[MAXN];
ll n,m;
bool check(ll x){
    return x>=0?1:0;
}
ll lowbit(ll x){ //树状数组基本操作
    return x&-x;
}
void add(ll x,ll k){
    while(x<=n){
        tree[x]+=k;
        x+=lowbit(x);
    }
}
ll sumq(ll x){
    ll ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}
int main() {
    si(n);
    si(m);
    for(int i=1;i<=n;i++) {
        si(a[i]);
        b[i]=a[i]-a[i-1]; //进行差分操作
        add(i,check(b[i])); //把差分结果转成0、1，用树状数组维护
    }
    for(int i=1;i<=m;i++){
        ll opt,x,l,r;
        si(opt);
        si(l);
        si(r);
        if(opt==1) {
            si(x);
            if(check(b[l]+x)&&!check(b[l])) add(l,1); //负数变正数就+1
            if(!check(b[l]+x)&&check(b[l])) add(l,-1);//正数变负数就-1
            b[l]+=x; //差分修改
            if(check(b[r+1]-x)&&!check(b[r+1])) add(r+1,1); //同理
            if(!check(b[r+1]-x)&&check(b[r+1])) add(r+1,-1);
            b[r+1]-=x;
        }else{
            if(sumq(r)-sumq(l)==r-l) cout<<"Yes"<<endl; //判断是否每个b[i]都是非负数
            else cout<<"No"<<endl;
        }
    }
	return 0;
}
```












---

## 作者：Scrutiny (赞：0)

树状数组码量小、常数小，非常适合本题.

经过样例的提示可以知道，先辈即为不降序列.

考虑维护差分数组 b，其中 $b_i=a_i-a_{i-1}$.

那么操作 $1$ 即为：`b[l]+=k,b[r+1]-=k;`.

而一个序列是先辈的充要条件是：对于任意 $i\in[l+1,r]$，有 $b_i\ge0.$

因此我们维护另一个树状数组 t.

当 $b_i\ge 0$ 时，$t_i=1$；否则 $t_i=0.$

故操作 $1$ 变为对 $t$ 数组的更新：如果更新后的 $b_i$ 非负而原先的 $b_i$ 是负数，那么 $t_i=t_i+1$；如果更新后的 $b_i$ 是负数而原先的 $b_i$ 非负，那么 $t_i=t_i-1$；否则 $t_i$ 不变.

总结一下，得到这段代码：

```cpp
int check(long long x){
	return (x>=0);
}
void upd(long long *tt,int i,long long x){
	while(i<=n){
		tt[i]+=x;
		i+=lowbit(i);
	}
}
	upd(t,l,check(b[l]+k)-check(b[l]));
	b[l]+=k;
	upd(t,r+1,check(b[r+1]-k)-check(b[r+1]));
	b[r+1]-=k;
```

而对于查询操作，判断是否满足 $\sum\limits_{i=1}^rt_i-\sum\limits_{i=1}^lt_i=r-l$ 即可.

特别注意，$t_l$ 正负性与答案无关，因此不用计入.

**CODE:**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000010],n,m,l,r,k,op,t[1000010],b[1000010];
int lowbit(int i){
	return i&(-i);
}
int check(long long x){
	return (x>=0);
}
void upd(long long *tt,int i,long long x){
	while(i<=n){
		tt[i]+=x;
		i+=lowbit(i);
	}
}
long long sum(long long *tt,int x){
	long long ans=0;
	while(x){
		ans+=tt[x];
		x-=lowbit(x);
	}
	return ans;
}
int main(){
	std::ios::sync_with_stdio(0);
	cin>>n>>m;
	for(register int i=1;i<=n;++i){
		cin>>a[i];
		upd(t,i,check(a[i]-a[i-1]));
		b[i]=a[i]-a[i-1];
	}
	for(register int i=1;i<=m;++i){
		cin>>op;
		if(op==1){
			cin>>l>>r>>k;
			upd(t,l,check(b[l]+k)-check(b[l]));
			b[l]+=k;
			upd(t,r+1,check(b[r+1]-k)-check(b[r+1]));
			b[r+1]-=k;
		}
		else{
			cin>>l>>r;
			if(sum(t,r)-sum(t,l)==r-l){
				printf("Yes\n");
			}
			else{
				printf("No\n");
			}
		}
	}
}
```



---

## 作者：registerGen (赞：0)

# Solution

提供另一种实现思路。

那个裸的结论就不细说了，具体可以见其它题解。

> 如果一个序列是先辈，当且仅当该序列单调不减。

然后我们发现：**一个序列单调不减，等价于它的差分序列中的每一项都 $\ge 0$，即差分序列的 最小值 $\ge 0$。**

于是只需维护原序列的差分序列，支持单点加，区间查询最小值。

上线段树即可。

# Code

```cpp
#include<cstdio>
#include<algorithm>

typedef long long ll;

const int N=5e5;

struct Node{
	ll v;
};

int n,m,a[N+10],d[N+10];
Node t[(N<<2)+10];

// 线段树模板
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
inline void pushUp(int i){t[i].v=std::min(t[ls(i)].v,t[rs(i)].v);}
void build(int i,int l,int r){
	if(l==r)return t[i].v=d[l],void();
	int mid=(l+r)>>1;
	build(ls(i),l,mid),build(rs(i),mid+1,r);
	pushUp(i);
}void modify(int i,int l,int r,int pos,int v){
	if(l==r)return t[i].v+=v,void();
	int mid=(l+r)>>1;
	if(pos<=mid)modify(ls(i),l,mid,pos,v);else modify(rs(i),mid+1,r,pos,v);
	pushUp(i);
}ll query(int i,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return t[i].v;
	int mid=(l+r)>>1;
	ll res=0x3f3f3f3f3f3f3f3fLL;
	if(ql<=mid)res=std::min(res,query(ls(i),l,mid,ql,qr));
	if(qr>mid) res=std::min(res,query(rs(i),mid+1,r,ql,qr));
	return res;
}
#undef ls
#undef rs

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<=n;i++)
		d[i]=a[i]-a[i-1];
	build(1,1,n+1);
	while(m--){
		int opt,l,r,k;
		scanf("%d%d%d",&opt,&l,&r);
		if(opt==1)scanf("%d",&k),modify(1,1,n+1,l,k),modify(1,1,n+1,r+1,-k);
		else puts(query(1,1,n+1,l+1,r)>=0?"Yes":"No");
		// 注意，由于我们关心的是 min(a_{l+1}-a_l,...,a_r-a_{r-1}) 即差分序列的第 l+1 项到第 r 项，所以要查询的区间是 [l+1,r]
	}
	return 0;
}
```

---

