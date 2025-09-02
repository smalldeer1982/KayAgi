# Alyona and towers

## 题目描述

Alyona has built $ n $ towers by putting small cubes some on the top of others. Each cube has size $ 1×1×1 $ . A tower is a non-zero amount of cubes standing on the top of each other. The towers are next to each other, forming a row.

Sometimes Alyona chooses some segment towers, and put on the top of each tower several cubes. Formally, Alyouna chooses some segment of towers from $ l_{i} $ to $ r_{i} $ and adds $ d_{i} $ cubes on the top of them.

Let the sequence $ a_{1},a_{2},...,a_{n} $ be the heights of the towers from left to right. Let's call as a segment of towers $ a_{l},a_{l+1},...,a_{r} $ a hill if the following condition holds: there is integer $ k $ ( $ l<=k<=r $ ) such that $ a_{l}&lt;a_{l+1}&lt;a_{l+2}&lt;...&lt;a_{k}&gt;a_{k+1}&gt;a_{k+2}&gt;...&gt;a_{r} $ .

After each addition of $ d_{i} $ cubes on the top of the towers from $ l_{i} $ to $ r_{i} $ , Alyona wants to know the maximum width among all hills. The width of a hill is the number of towers in it.

## 说明/提示

The first sample is as follows:

After addition of $ 2 $ cubes on the top of each towers from the first to the third, the number of cubes in the towers become equal to $ [7,7,7,5,5] $ . The hill with maximum width is $ [7,5] $ , thus the maximum width is $ 2 $ .

After addition of $ 1 $ cube on the second tower, the number of cubes in the towers become equal to $ [7,8,7,5,5] $ . The hill with maximum width is now $ [7,8,7,5] $ , thus the maximum width is $ 4 $ .

After addition of $ 1 $ cube on the fourth tower, the number of cubes in the towers become equal to $ [7,8,7,6,5] $ . The hill with maximum width is now $ [7,8,7,6,5] $ , thus the maximum width is $ 5 $ .

## 样例 #1

### 输入

```
5
5 5 5 5 5
3
1 3 2
2 2 1
4 4 1
```

### 输出

```
2
4
5
```

# 题解

## 作者：MyukiyoMekya (赞：19)

线段树打标记

首先我们对整个数组做一次差分，这样可以更好的反应两个数之间的大小关系，以及**可以把区间加变成单点加**

**这样就不用 pushdown 传 lazytag 了**

转换为差分后就可以把问题转换一下：

求 $[l,r]$ 之间最长的一个连续段使得：由一个连续的负数段和一个连续的正数段拼接起来

先说明节点信息意思：$u$ 当前节点，$lson$ 左子节点，$rson$ 右子节点

$ans_u$ 当前节点的答案，

$up_{u}$ 当前节点区间从最左开始往右的答案的长度

$down_{u}$ 当前节点区间从最右开始往左的答案的长度

转移：

显然，$ans_u=\max(ans_{lson},ans_{rson})$

如果 $lson$ 和 $rson$ 区间的交点的两个位置中有 1 个是 0，或者 $lson$ 的交点是负数而 $rson$ 的交点是正数

那么说明 $lson$ 和 $rson$ 不可能把两个区间合并拼成一个新答案

所以，$up_u=up_{lson},down_u=down_{rson}$

如果可以合并：

那么可以更新一下答案： $ans_u=\max(ans_{lson},ans_{rson},down_{lson}+up_{rson})$

如果 $up_{lson}$ 的长度恰好等于 $lson$ 的区间长度，那么就可以把 $up_{lson}$ 和 $up_{rson}$ 合并在一起变成 $up_u$

否则 $up_u=up_{lson}$

$down_u$ 的更新同理

```cpp
// This code writed by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
using namespace std;
const int MaxN=300050;
struct Node
{
	int Ans;
	int l,r;
	int uplen,downlen;
}tr[MaxN<<2];
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
#define lson (u<<1)
#define rson (u<<1|1)
int a[MaxN],inp[MaxN];
int n;
inline int getsign(int x)
{
	if(!x)
		return 0;
	return x>0?1:-1;
}
inline void checkmax(int &x,int y)
{
	if(x<y)
		x=y;
	return;
}
inline void pushup(int u)
{
	tr[u].Ans=max(tr[lson].Ans,tr[rson].Ans);
	checkmax(tr[u].Ans,max(tr[lson].uplen,tr[rson].downlen));
	if(!a[tr[lson].r]||!a[tr[rson].l]||
		getsign(a[tr[lson].r])<getsign(a[tr[rson].l]))
	{
		tr[u].uplen=tr[lson].uplen,tr[u].downlen=tr[rson].downlen;
	}
	else
	{
		checkmax(tr[u].Ans,tr[lson].downlen+tr[rson].uplen);
		if(tr[lson].uplen==tr[lson].r-tr[lson].l+1)
			tr[u].uplen=tr[lson].uplen+tr[rson].uplen;
		else
			tr[u].uplen=tr[lson].uplen;
		if(tr[rson].downlen==tr[rson].r-tr[rson].l+1)
			tr[u].downlen=tr[rson].downlen+tr[lson].downlen;
		else
			tr[u].downlen=tr[rson].downlen;
	}
	return;
}
inline void print()
{
	for(int i=1;i<=20;++i)
	{
		puts("======================");
		printf("Node [ %lld , %lld ]\n",tr[i].l,tr[i].r);
		printf("Ans %lld\n",tr[i].Ans);
		printf("up  %lld   down  %lld\n",tr[i].uplen,tr[i].downlen);
	}
	puts("-=-==");
	for(int i=1;i<=6;++i)
		printf("%d ",a[i]);puts("");
	puts("======");
	return;
}
inline void buildtr(int u,int l,int r)
{
	tr[u].l=l;tr[u].r=r;
	if(l==r)
	{
		if(!a[l])
			tr[u].Ans=tr[u].uplen=tr[u].downlen=0;
		else
			tr[u].uplen=tr[u].downlen=tr[u].Ans=1;
		return;
	}
	reg int mid=(l+r)>>1;
	buildtr(lson,l,mid);
	buildtr(rson,mid+1,r);
	pushup(u);
	return;
}
inline void modify(int u,int l,int r,int p,int k)
{
	if(l==r)
	{
		a[l]+=k;
		if(!a[l])
			tr[u].Ans=tr[u].uplen=tr[u].downlen=0;
		else
			tr[u].Ans=tr[u].uplen=tr[u].downlen=1;
		return;
	}
	reg int mid=(l+r)>>1;
	if(p<=mid)
		modify(lson,l,mid,p,k);
	else
		modify(rson,mid+1,r,p,k);
	pushup(u);
	return;
}
signed main(void)
{
//	freopen("J.in","r",stdin);
//	freopen("J.out","w",stdout);
	int m;
	cin>>n;
	for(int i=1;i<=n;++i)
		read(inp[i]);
	if(n==1)
	{
		cin>>m;
		for(int i=1;i<=m;++i)
			puts("1");
		return 0;
	}
	for(int i=1;i<n;++i)
		a[i]=inp[i+1]-inp[i];
	buildtr(1,1,n-1);
	cin>>m;
	reg int l,r,d;
	for(int i=1;i<=m;++i)
	{
		// puts("O-oooooooooo AAAAE-A-A-I-A-U- JO-oooooooooooo AAE-O-A-A-U-U-A- E-eee-ee-eee AAAAE-A-E-I-E-A- JO-ooo-oo-oo-oo EEEEO-A-AAA-AAAA");
		read(l);read(r);read(d);
		if(l!=1)
			modify(1,1,n-1,l-1,d);
		if(r!=n)
			modify(1,1,n-1,r,-d);
//		if(l!=1)
//			printf("modify %d +\n",l-1);
//		if(r!=n)
//			printf("modify %d -\n",r);
		printf("%lld\n",tr[1].Ans+1);
//		print();
	}
	return 0;
}
```



  

---

## 作者：lx_zjk (赞：11)

这道题做过小白逛公园后应该还是比较显然的吧~~QAQ~~

思路挺简单的 重点是区间合并

我维护了10个量

### 1.区间左端点值 $lc$
### 2.区间右端点值 $rc$
### 3.区间长度 $len$
### 4.区间从左端点开始最长的下降序列 $l$_$line$
### 5.区间从右端点开始最长的上升序列 $r$_$line$
### 6.以左端点结束的先升再降序列
### 7.以右端点结束的先升再降序列
### 8.区间的最长的答案
### 9. 用于下传的$tag$~~常规操作~~
### 10.区间左端点l
### 11.区间右端点r
(其中因为9.10.11)是个人习惯

因为关于(1 - 8)的维护比较复杂 ~~并且我很懒~~ 所以我将其放入结构体 并重载了运算符$+$

然后就是个十分$easy$的区间修改了

至于问什么要维护这些操作呢

考虑两个区间合并 这里的端点代指区间最高点

分类讨论

### 区间最高点在左边
$c.ans = max(a.rmax + b.l_line, a.ans)$

### 区间最高点在右边
$c.ans = max(b.lmax + a.r_line, b.ans)$

这就是这8个个变量之所以要维护的原因 思维难度不大 代码难度：要仔细就行了

# code

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 2139062143;

#define DEBUG(x) std::cerr << #x << ' = ' << x << std::endl

inline ll read() {
    ll f = 1, x = 0;char ch;
    do {ch = getchar();if (ch == '-')f = -1;} while (ch > '9' || ch < '0');
    do {x = x * 10 + ch - '0';ch = getchar();} while (ch >= '0' && ch <= '9');
    return f * x;
}

const int MAX_N = 3E5 + 50;

struct Node {
	ll len, lc, rc, lmax, rmax, dat, l_line, r_line; 
};

Node operator + (const Node a, const Node b) {
	Node c;
	c.len = a.len + b.len;
	c.lc = a.lc; c.rc = b.rc;
	c.l_line = a.l_line;
	if (a.l_line == a.len && a.rc > b.lc)
		c.l_line = max(c.l_line, a.l_line + b.l_line);
	c.r_line = b.r_line;
	if (b.r_line == b.len && a.rc < b.lc)
		c.r_line = max(c.r_line, a.r_line + b.r_line);
	c.lmax = a.lmax;
	c.rmax = b.rmax;
	if (a.lmax == a.len && a.rc > b.lc)
		c.lmax = max(c.lmax, a.lmax + b.l_line);
	if (a.r_line == a.len && a.rc < b.lc)
		c.lmax = max(c.lmax, a.r_line + b.lmax);
	
	if (c.rmax == b.len && a.rc < b.lc)
        c.rmax += a.r_line;
    if (b.l_line == b.len && a.rc > b.lc)
        c.rmax = max(c.rmax, b.l_line + a.rmax);
//	if (b.lmax == a.len && a.rc < b.lc)
//		c.rmax = max(c.rmax, b.lmax + a.r_line);	
	
	c.dat = max(a.dat, b.dat);
	if (a.rc > b.lc)
		c.dat = max(c.dat, a.rmax + b.l_line);
	if (a.rc < b.lc)
		c.dat = max(c.dat, b.lmax + a.r_line);
	return c;
}

int n, a[MAX_N], m;

struct segment_tree {
	int l, r;
	ll tag;
	Node x;
} t[MAX_N << 2];

#define ls(p) (p << 1)
#define rs(p) (p << 1 | 1)

void build (int p, int l, int r) {
	t[p].l = l; t[p].r = r;
	if (l == r) {
		t[p].x.lc = t[p].x.rc = a[l];
		t[p].x.len = t[p].x.lmax = t[p].x.rmax = t[p].x.dat = t[p].x.l_line = t[p].x.r_line = 1;
		return ;
	}
	int mid = (l + r) >> 1;
	build (ls(p), l, mid);
	build (rs(p), mid + 1, r);
	t[p].x = t[ls(p)].x + t[rs(p)].x;
}

void push_down (int p) {
	if (t[p].tag == 0) return;
	t[ls(p)].x.lc += t[p].tag;
	t[rs(p)].x.rc += t[p].tag;
	t[ls(p)].x.rc += t[p].tag;
	t[rs(p)].x.lc += t[p].tag;
	t[ls(p)].tag += t[p].tag;
	t[rs(p)].tag += t[p].tag;
	t[p].tag = 0;
}

void change (int p, int l, int r, int v) {
	if (l <= t[p].l && t[p].r <= r) {
		t[p].x.lc += v;
		t[p].x.rc += v;
		t[p].tag += v;
		return;
	}
	push_down(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid)
		change (ls(p), l, r, v);
	if (r > mid)
		change (rs(p), l, r, v);
	t[p].x = t[ls(p)].x + t[rs(p)].x;
}

inline Node query (int p, int l, int r) {
	if (l <= t[p].l && t[p].r <= r)
		return t[p].x;
	push_down(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (r <= mid)
		return query(ls(p), l, r);
	if (l > mid)
		return query(rs(p), l, r);
	Node a = query(ls(p), l, r), b = query(rs(p), l, r);
	return a + b;
}

int main() {
	n = read();
	for (int i = 1; i <= n; i ++ ) a[i] = read();
	build (1, 1, n);
	m = read();
	for (int i = 1; i <= m; i ++ ) {
		int l = read(), r = read(), d = read();
		change (1, l, r, d);
		printf("%lld\n", query(1, 1, n).dat);
	}
	return 0;
}


```

---

## 作者：chlchl (赞：6)

同学推荐的一道题，感觉是道好题，挺有思维难度的。

## 题意简述
给定 $n$ 个数和 $m$ 个操作，每个操作是区间加，并且查询整个数组中最长的连续单峰子段（不知道啥意思的看题目解释）。

## 做法
本题**线段树**好题。

如果没做过小白逛公园（~~啊其实我也没做过~~），我们一步一步来。

首先，单峰子段不好直接维护，先考虑维护连续上升子段和连续下降子段。我们考虑，对于线段树每个节点维护的一个区间，其最长单峰区间的组成主要有以下几种：

![](https://cdn.luogu.com.cn/upload/image_hosting/s1sza3mm.png?x-oss-process=image/resize,m_lfit,h_350,w_400)

分界线为左右儿子分界点（即区间中点）。

根据这些情况，我们可以大概知道维护哪些值了。

1. 左右端点的值（$lval,rval$）。这是用于左右区间拼接时判断边界大小关系的。
2. 以左端点开始的最长单减子段（$iseq$）。
3. 以右端点结束的最长单增子段（$dseq$）。
4. 以左端点开始的最长单峰子段（$lans$）。
5. 以右端点结束的最长单峰子段（$rans$）。$2,3,4,5$ 都是用来拼接整个区间的单峰区间的。后面会详细讲到。
6. 整个区间的最长单峰区间（$ans$）。
7. 万年不变的懒标记（$tag$）。

``pushdown``、建树、更新这种函数跟普通的线段树没啥区别，就不讲了。只要注意建树时区间长度之类的初始值都是 $1$（**一个元素也符合条件的**）。

讲讲怎么合并区间吧。

1. 左右端点：分别继承左、右儿子的左、右端点就好。
2. $dseq$：$dseq_o=dseq_{ls(o)}$，这很容易理解，左端点是一样的。只是，如果 $dseq_{ls(o)}$ 等于区间长度，并且左儿子右端点大于右儿子左端点，意味着可以**加上右儿子的 $dseq$**。
3. $iseq$ 类似。
4. $lans$：首先还是继承 $lans_{ls(o)}$。
- 左峰型，加上右儿子的单减区间。
- 中峰型，加上右儿子的单减区间。
- 右峰型，加上右儿子的单峰区间。具体满足什么条件自己推，也可以看代码。
5. $rans$ 类似。
6. $ans$：三种方式：左右儿子分别的答案、左儿子单增+右儿子单减、左儿子单峰+右儿子单减。

## 代码
来个没有指针和结构体的。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 3e5 + 10;
const int M = N << 2;
int n, m;
ll a[N], lval[M], rval[M], dseq[M], iseq[M], lans[M], rans[M], tag[M], ans[M];

#define ls(o) (o << 1)
#define rs(o) (o << 1 | 1)

void pushup(int o, int l, int r){
	int mid = (l + r) >> 1, llen = mid - l + 1, rlen = r - mid;
	lval[o] = lval[ls(o)], rval[o] = rval[rs(o)];
	
	iseq[o] = iseq[rs(o)];//以右端点结束的最长上升子段 
	if(iseq[rs(o)] == rlen && lval[rs(o)] > rval[ls(o)])	iseq[o] += iseq[ls(o)];
	dseq[o] = dseq[ls(o)];//以左端点开始的最长下降子段
	if(dseq[ls(o)] == llen && rval[ls(o)] > lval[rs(o)])	dseq[o] += dseq[rs(o)];
	
	lans[o] = lans[ls(o)];
	if(iseq[ls(o)] == llen){
		if(rval[ls(o)] > lval[rs(o)])	lans[o] += dseq[rs(o)];//中峰 
		else if(rval[ls(o)] < lval[rs(o)])	lans[o] += lans[rs(o)];//右峰 
	}else if(lans[ls(o)] == llen && rval[ls(o)] > lval[rs(o)])	lans[o] += dseq[rs(o)];//左峰 
	
	rans[o] = rans[rs(o)];
	if(dseq[rs(o)] == rlen){//同理 
		if(rval[ls(o)] > lval[rs(o)])	rans[o] += rans[ls(o)];
		else if(rval[ls(o)] < lval[rs(o)])	rans[o] += iseq[ls(o)];
	}else if(rans[rs(o)] == rlen && rval[ls(o)] < lval[rs(o)])	rans[o] += iseq[ls(o)];
	
	ans[o] = max(ans[ls(o)], ans[rs(o)]);//更新答案 
	if(rval[ls(o)] > lval[rs(o)])	ans[o] = max(ans[o], max(iseq[ls(o)], rans[ls(o)]) + dseq[rs(o)]);
	else if(rval[ls(o)] < lval[rs(o)])	ans[o] = max(ans[o], iseq[ls(o)] + lans[rs(o)]);
}

void pushdown(int o, int l, int r){//第一次感觉pushdown如此简短 
	if(!tag[o])	return ;
	lval[ls(o)] += tag[o], lval[rs(o)] += tag[o];
	rval[ls(o)] += tag[o], rval[rs(o)] += tag[o];
	tag[ls(o)] += tag[o], tag[rs(o)] += tag[o];
	tag[o] = 0;
}

void build(int o, int l, int r){
	if(l == r){
		lval[o] = rval[o] = a[l], dseq[o] = iseq[o] = lans[o] = rans[o] = ans[o] = 1;
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls(o), l, mid), build(rs(o), mid + 1, r);
	pushup(o, l, r);
}

void update(int o, int l, int r, int s, int t, ll x){
	if(l > t || r < s)	return ;
	if(l >= s && r <= t){
		lval[o] += x, rval[o] += x, tag[o] += x;
		return ; 
	}
	pushdown(o, l, r);
	int mid = (l + r) >> 1;
	if(s <= mid)	update(ls(o), l, mid, s, t, x);
	if(t > mid)	update(rs(o), mid + 1, r, s, t, x);
	pushup(o, l, r);
}

int main(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++)	scanf("%lld", &a[i]);
	build(1, 1, n);
	scanf("%d", &m);
	while(m--){
		int l, r; ll d;
		scanf("%d%d%lld", &l, &r, &d);
		update(1, 1, n, l, r, d);
		printf("%lld\n", ans[1]);//第一个节点就是答案，不要想着如何查询了，查个几把 
	}
	return 0;
} 
```



---

## 作者：Terac (赞：5)

[$\texttt{Link}$](https://www.luogu.com.cn/problem/CF739C)  

## 题意  

给定一个序列，支持以下操作：  

- 区间加  

- 整体查询最长的单峰序列（一部分严格单调递增，另一部分严格单调递减）。

## 思路
线段树的简单题，做法和思路基本和 [P4513](https://www.luogu.com.cn/problem/P4513) 差不多，难点在于怎么上传整合各子区间的信息。  

为方便处理左右两个子区间的边界问题，维护区间内以下 9 个量：  

1. 左端点权值 $\text{lv}$。  

2. 右端点权值 $\text{rv}$。

3. 从左端点开始的最长下降序列 $\text{dec}$。  

4. 从右端点结束的最长上升序列 $\text{inc}$。

5. 从左端点开始的最长的单峰序列 $\text{lans}$。  

6. 从右端点结束的最长的单峰序列 $\text{rans}$。

7. 区间内最长的单峰序列 $\text{ans}$。  

8. 区间加的懒标记 $\text{tag}$。  

9. 区间长度 $\text{len}$。  

懒标记的下传很常规，修改 $\text{lv}$ 和 $\text{rv}$ 即可。  

重点是上传的部分。  

定义 $ls$ 为左区间，$rs$ 为右区间。

分类讨论：

- 对于 $\text{lv}$ 和 $\text{rv}$ 直接继承左右区间即可。  

- 对于 $\text{dec}$，分两类讨论：
  - 若 $\text{dec}_{ls} = \text{len}_{ls}$ 且 $\text{lv}_{rs}>\text{rv}_{ls}$，说明下降序列一直延续到了右区间，$\text{dec}\gets \text{dec}_{ls}+\text{dec}_{rs}$。   
  - 若 $\text{dec}_{ls} \not= \text{len}_{ls}$ 或 $\text{lv}_{rs}\leq\text{rv}_{ls}$，$\text{dec}\gets \text{dec}_{ls}$。  
- 对于 $\text{inc}$，分两类讨论：
  - 若 $\text{inc}_{rs} = \text{len}_{rs}$ 且 $\text{rv}_{ls}<\text{lv}_{rs}$，说明上升序列一直延续到了左区间，$\text{inc}\gets \text{inc}_{rs}+\text{inc}_{ls}$。   
  - 若 $\text{inc}_{rs} \not= \text{len}_{rs}$ 或 $\text{rv}_{ls}\ge\text{lv}_{rs}$，$\text{inc}\gets \text{inc}_{rs}$。   

- 对于 $\text{lans}$，若 $\text{inc}_{ls}=\text{len}_{ls}$，说明左区间是一个上升序列，否则直接继承左子树即可，分五类讨论：  
    - 若 $\text{rv}_{ls}=\text{lv}_{rs}$，此时答案延续不到右区间，$\text{lans}\gets\text{lans}_{ls}$。
    - 若 $\text{inc}_{ls}=\text{len}_{ls}$ 且 $\text{rv}_{ls}<\text{lv}_{rs}$，说明左区间的上升序列在右区间还可延续，$\text{lans}\gets\text{lans}_{ls}+\text{lans}_{rs}$。  
    - 若 $\text{inc}_{ls}=\text{len}_{ls}$ 且 $\text{rv}_{ls}>\text{lv}_{rs}$，说明左区间的上升序列在右区间不可延续，右区间只可下降，$\text{lans}\gets\text{lans}_{ls}+\text{dec}_{rs}$。  
    - 若 $\text{lans}_{ls}=\text{len}_{ls}$ 且 $\text{rv}_{ls}>\text{lv}_{rs}$，说明左区间可能可以令右区间下降增加长度，$\text{lans}=\text{lans}_{ls}+\text{dec}_{rs}$。
    - 其余情况说明左区间无法连接到右区间，$\text{lans}\gets\text{lans}_{ls}$。
  
- $\text{rans}$ 也类似的处理。  

- 对于 $\text{ans}$，有三种继承的情况： 
  - 从 $\text{ans}_{ls}$ 和 $\text{ans}_{rs}$ 继承来，$\text{ans}\gets\max(\text{ans}_{ls},\text{ans}_{rs})$。   
  - 若 $\text{rv}_{ls}>\text{lv}_{rs}$，此时最大值在左区间，$\text{ans}\gets\text{rans}_{ls}+\text{dec}_{rs}$。  
  - 若 $\text{rv}_{ls}<\text{lv}_{rs}$，此时最大值在右区间，$\text{ans}\gets\text{lans}_{rs}+\text{inc}_{ls}$。  
    
其他操作就和普通线段树一样了。  

本题还有一个稍微简单些的做法，维护一个差分数组，每次整体查询由相邻的连续正数段和连续负数段构成的最长子段，这样每次修改就变成单点加，不需要区间加的懒标记了，维护这个问题的操作和朴素的线段树差不多。  

时间复杂度为线段树的 $n\log n$。  

这个数据范围要开 `long long`。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10;
int n, m;
ll a[N];
struct Segment {
	int l, r, len;
	int inc, dec, lans, rans, ans;
	ll tag, lv, rv;
} t[N << 2];
#define ls x << 1
#define rs x << 1 | 1
void pushup(int x) {
	t[x].lv = t[ls].lv, t[x].rv = t[rs].rv;
	t[x].inc = t[rs].inc;
	if(t[rs].inc == t[rs].len && t[rs].lv > t[ls].rv) t[x].inc += t[ls].inc;
	t[x].dec = t[ls].dec;
	if(t[ls].dec == t[ls].len && t[ls].rv > t[rs].lv) t[x].dec += t[rs].dec;
	t[x].lans = t[ls].lans;
	if(t[ls].inc == t[ls].len) {
		if(t[ls].rv < t[rs].lv) t[x].lans += t[rs].lans;
		if(t[ls].rv > t[rs].lv) t[x].lans += t[rs].dec;
	}
	else if(t[ls].lans == t[ls].len && t[ls].rv > t[rs].lv) t[x].lans += t[rs].dec;
	t[x].rans = t[rs].rans;
	if(t[rs].dec == t[rs].len) {
		if(t[rs].lv < t[ls].rv) t[x].rans += t[ls].rans;
		if(t[rs].lv > t[ls].rv) t[x].rans += t[ls].inc;
	}
	else if(t[rs].rans == t[rs].len && t[rs].lv > t[ls].rv) t[x].rans += t[ls].inc;
	t[x].ans = max(t[ls].ans, t[rs].ans);
	if(t[ls].rv < t[rs].lv) t[x].ans = max(t[x].ans, t[ls].inc + t[rs].lans);
	if(t[ls].rv > t[rs].lv) t[x].ans = max(t[x].ans, t[rs].dec + t[ls].rans);
}
void pushdown(int x) {
	if(!t[x].tag) return;
	t[ls].lv += t[x].tag, t[ls].rv += t[x].tag;
	t[rs].lv += t[x].tag, t[rs].rv += t[x].tag;
	t[ls].tag += t[x].tag, t[rs].tag += t[x].tag;
	t[x].tag = 0;
}
void build(int x, int l, int r) {
	t[x].l = l, t[x].r = r, t[x].len = r - l + 1;
	t[x].lv = a[l], t[x].rv = a[r];
	if(l == r) {
		t[x].inc = t[x].dec = t[x].lans = t[x].rans = t[x].ans = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushup(x);
}
void update(int x, int l, int r, ll val) {
	if(l <= t[x].l && t[x].r <= r) {
		t[x].lv += val, t[x].rv += val, t[x].tag += val;
		return;
	}
	pushdown(x);
	if(l <= t[ls].r) update(ls, l, r, val);
	if(t[rs].l <= r) update(rs, l, r, val);
	pushup(x);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	build(1, 1, n);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) {
		int l, r;
		ll d;
		scanf("%d%d%lld", &l, &r, &d);
		update(1, l, r, d);
		printf("%d\n", t[1].ans);
	}
	return 0;
}
```


---

## 作者：da32s1da (赞：4)

线段树好题！

考虑怎么维护这个**先上升再下降的最长序列**。

非常套路地维护7个参数：
- **(1)**当前区间最长的**先上升再下降序列**
- **(2)**以区间**左端点开始**的最长的**先上升再下降序列**
- **(3)**以区间**右端点结束**的最长的**先上升再下降序列**
- **(4)**以区间**左端点开始**的最长的**下降序列**
- **(5)**以区间**右端点结束**的最长的**上升序列**
- **(6)**区间左端点的**权值**
- **(7)**区间右端点的**权值**
- **(8)**区间大小  （我没维护）

考虑怎么将左右儿子信息合并。
- **(6)**为**左儿子(6)**
- **(7)**为**右儿子(7)**
- **(4)**为**左儿子(4)**,但若**左儿子(4)=左儿子(8)**且**左儿子(7)>右儿子(6)**,还要加上**右儿子(4)**
- **(5)**为**右儿子(5)**,但若**右儿子(5)=右儿子(8)**且**左儿子(7)<右儿子(6)**,还要加上**左儿子(4)**
- **(2)**为**左儿子(2)**,但有**两种额外的情况**。
 - **左儿子(5)=左儿子(8)**且**左儿子(7)<右儿子(6)**,那么**(2)**可能是**左儿子(5)+右儿子(2)**
 - **左儿子(3)=左儿子(8)**且**左儿子(7)>右儿子(6)**,那么**(2)**可能是**左儿子(2)+右儿子(4)**
- **(3)**为**右儿子(3)**,但有**两种额外的情况**。
 - **右儿子(4)=右儿子(8)**且**左儿子(7)>右儿子(6)**,那么**(3)**可能是**左儿子(3)+右儿子(4)**
 - **右儿子(2)=右儿子(8)**且**左儿子(7)<右儿子(6)**,那么**(2)**可能是**左儿子(5)+右儿子(2)**
- **(1)**用新更新的**(2,3,4,5)**和**左儿子和右儿子的(1)**更新。但有**两种额外的情况**。
 - 若**左儿子(7)>右儿子(6)**,用**左儿子(3)+右儿子(4)**更新。
 - 若**左儿子(7)<右儿子(6)**,用**左儿子(5)+右儿子(2)**更新。

呼。。这样就合并完了。

然后就比较裸了。**注意开long long！**

~~据说可用差分来做~~

```
#include<cstdio>
const int N=3e5+50;
typedef long long LL;
int n,m,x,y;
LL z;
int mx[N<<3];//answer
int mxl1[N<<3],mxr1[N<<3];//left down and right on 
int mxl2[N<<3],mxr2[N<<3];//left on-down and right on-down
LL vl[N<<3],vr[N<<3];//left val and right val
LL bj[N<<3];//add tag 
inline int max(int u,int v){return u>v?u:v;}
void gx(int now,int ls,int rs){
	int noww=now<<1,nrs=ls+rs>>1;
	vl[now]=vl[noww];
	vr[now]=vr[noww|1];
	//left down 
	mxl1[now]=mxl1[noww];
	if(mxl1[noww]==nrs-ls+1&&vr[noww]>vl[noww|1])
	mxl1[now]+=mxl1[noww|1];
	//right on
	mxr1[now]=mxr1[noww|1];
	if(mxr1[noww|1]==rs-nrs&&vr[noww]<vl[noww|1])
	mxr1[now]+=mxr1[noww];
	//left on-down
	mxl2[now]=mxl2[noww];
	if(mxl2[noww]==nrs-ls+1&&vr[noww]>vl[noww|1])
	mxl2[now]+=mxl1[noww|1];
	if(mxr1[noww]==nrs-ls+1&&vr[noww]<vl[noww|1])
	mxl2[now]=max(mxl2[now],mxr1[noww]+mxl2[noww|1]);
	//right on-down
	mxr2[now]=mxr2[noww|1];
	if(mxr2[noww|1]==rs-nrs&&vr[noww]<vl[noww|1])
	mxr2[now]+=mxr1[noww];
	if(mxl1[noww|1]==rs-nrs&&vr[noww]>vl[noww|1])
	mxr2[now]=max(mxr2[now],mxl1[noww|1]+mxr2[noww]);
	
	mx[now]=max(mx[noww],mx[noww|1]);
	mx[now]=max(mx[now],max(mxl1[now],mxr1[now]));
	mx[now]=max(mx[now],max(mxl2[now],mxr2[now]));
	if(vr[noww]<vl[noww|1])mx[now]=max(mx[now],mxr1[noww]+mxl2[noww|1]);
	if(vr[noww]>vl[noww|1])mx[now]=max(mx[now],mxr2[noww]+mxl1[noww|1]);
}
void mktree(int now,int ls,int rs){
	if(ls==rs){
		scanf("%d",&x);//读入
		vl[now]=vr[now]=x;//初始化左右端点数值
		mx[now]=mxl1[now]=mxl2[now]=mxr1[now]=mxr2[now]=1;
        //初始化各种参数
		return;
	}
	int noww=now<<1,nrs=ls+rs>>1;
	mktree(noww,ls,nrs);
	mktree(noww|1,nrs+1,rs);
	gx(now,ls,rs);
}
void bjxc(int now,int ls,int rs){//标记下传
	if(!bj[now])return;
	int noww=now<<1;
	vl[noww]+=bj[now];vl[noww|1]+=bj[now];
	vr[noww]+=bj[now];vr[noww|1]+=bj[now];
	bj[noww]+=bj[now];bj[noww|1]+=bj[now];
	bj[now]=0;
}
void jia(int now,int ls,int rs,int zuo,int you,LL val){
	if(ls>you||rs<zuo)return;
	if(ls>=zuo&&rs<=you){
		vl[now]+=val;//左端点加
		vr[now]+=val;//右端点加
		bj[now]+=val;//区间加标记
		return;
	}
	bjxc(now,ls,rs);
	int noww=now<<1,nrs=ls+rs>>1;
	jia(noww,ls,nrs,zuo,you,val);
	jia(noww|1,nrs+1,rs,zuo,you,val);
	gx(now,ls,rs);
}
int main(){
	scanf("%d",&n);
	mktree(1,1,n);//建树
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%I64d",&x,&y,&z);
		jia(1,1,n,x,y,z);//区间加
		printf("%d\n",mx[1]);//输出答案
	}
}
```

---

## 作者：Gold14526 (赞：3)

$\rm Problem:$[Alyona and towers](https://www.luogu.com.cn/problem/CF739C)

$\rm Difficulty:2500$

### 题意

给出一个长度为 $n(1\le n\le3\times10^5)$ 的序列 $a(1\le a_i\le10^9)$，$q(1\le q\le3\times10^5)$ 次区间加，每次操作后回答最长的区间 $[l,r]$ 长度使得

$$\exists k\! \in\![l,r],a_l<a_{l+1}<a_{l+2}<...<a_k>a_{k+1}>a_{k+2}>...>a_r$$

### 广义矩乘

没学过矩乘请前往[矩乘模板](https://www.luogu.com.cn/problem/B2105)或看其它题解的思路。

我们先回顾常用的矩乘，假设 $A$ 为一个 $n \times k$ 的矩阵，$B$ 为一个 $k \times m$ 的矩阵，$C=A \times B$。

那么对于 $1\le i \le n,1 \le j \le m$ ，有：

$$C_{i,j}=\sum_{p=1}^k A_{i,p}\times B_{p,j}$$

广义矩乘就是把求和和乘法换成别的运算。

在广义矩阵乘法中，对于 $1\le i \le n,1 \le j \le m$ ，有：

$$C_{i,j}=\oplus_{p=1}^k A_{i,p}\otimes B_{p,j}$$

这里要求两种算法有分配律，即对于任意 $x,y,z$，满足：

$$(x\oplus y)\otimes z=(x\otimes z)\oplus(y\otimes z)$$

例如，在常用的矩乘中，有 $(x+y)\times z=(x\times z)+(y\times z)$.

### 本题做法

本题中，我们使用的广义矩阵乘法为 $C_{i,j}=\max_{p=1}^k A_{i,p}+ B_{p,j}$，两种运算显然满足分配律。

考虑直接 dp 怎么做。

设 $f_i$ 表示以 $i$ 结尾的最长上升子串长度，不难得出转移式：

$$f_i=\begin{cases}f_{i-1}+1 & a_i>a_{i-1} \\ 1 & a_i\le a_{i-1}\end{cases}$$

设 $g_i$ 表示以 $i$ 结尾的最长先上升后下降子串长度，不难得出转移式：

$$g_i=\begin{cases}\max(f_{i-1}+1,g_{i-1}+1) & a_i<a_{i-1} \\ 1 & a_i\ge a_{i-1}\end{cases}$$

设 $ans_i$ 表示到 $i$ 为止最长满足要求的子串长度，即 $ans_i=\max\{f_i,g_i,ans_{i-1}\}$。

将 $f_i$ 和 $g_i$ 的转移式代入可得：

$ans_i=\begin{cases}\max\{1,f_{i-1}+1,ans_{i-1}\} & a_i>a_{i-1} \\ \max(1,ans_{i-1}) & a_i=a_{i-1} \\ \max\{1,f_{i-1}+1,g_{i-1}+1,ans_{i-1}\} & a_i<a_{i-1}\end{cases}$

于是，我们可以得出状态矩阵：

$$\begin{bmatrix} f_i & g_i & 0 & ans_i \end{bmatrix}$$

以及三个转移矩阵。

当 $a_i>a_{i-1}$ 时，转移矩阵为：

$$\begin{bmatrix} 1 & -\infin & -\infin & 1 \\ -\infin & -\infin & -\infin & -\infin \\ 1 & 1 & 0 & 1 \\ -\infin & -\infin & -\infin & 0 \end{bmatrix}$$

当 $a_i=a_{i-1}$ 时，转移矩阵为：

$$\begin{bmatrix} -\infin & -\infin & -\infin & -\infin \\ -\infin & -\infin & -\infin & -\infin \\ 1 & 1 & 0 & 1 \\ -\infin & -\infin & -\infin & 0 \end{bmatrix}$$

当 $a_i<a_{i-1}$ 时，转移矩阵为：

$$\begin{bmatrix} -\infin & 1 & -\infin & 1 \\ -\infin & 1 & -\infin & 1 \\ 1 & 1 & 0 & 1 \\ -\infin & -\infin & -\infin & 0 \end{bmatrix}$$

注意本题中的区间加减并不用真的去区间加减，只需要在差分数组上修改两个位置就好了，$a_i$ 和 $a_{i-1}$ 之间的大小关系可以直接用差分数组的正负性体现，于是每次修改只需两次单点修改和一次全局查询就好了。

复杂度 $O(\xi^3n\log n)$，其中 $\xi$ 为矩阵边长，本做法中 $\xi=4$。

### 代码

这个做法虽然在码长和效率上不占优势，但是它好写啊，线段树是标准线段树，以及矩阵都只需要复制下来改一改就可以了。

```cpp
#include<bits/stdc++.h>
#define cint const int
#define iint inline int
#define uint unsigned int
#define iuint inline unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ill inline long long
#define ull unsigned long long
#define iull inline unsigned long long
#define cull const unsigned long long
#define sh short
#define csh const short
#define ish inline short
#define ush unsigned short
#define iush inline unsigned short
#define cush const unsigned short
using namespace std;
iint read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch-'0');
		ch=getchar();
	}
	return x;
}
cint inf=1e9;
struct matrix{
	short n,m;
	int a[4][4];
}f,emp,A,B,C;
matrix operator*(const matrix x,const matrix y)
{
	matrix z;
	z.n=x.n;
	z.m=y.m;
	for(short i=0;i<x.n;++i)
	{
		for(short j=0;j<y.m;++j)
		{
			z.a[i][j]=-inf;
			for(short k=0;k<x.m;++k)
			{
				z.a[i][j]=max(z.a[i][j],x.a[i][k]+y.a[k][j]);
			}
		}
	}
	return z;
}
inline void init()
{
	emp.n=emp.m=4;
	for(short i=0;i<4;++i)
	{
		for(short j=0;j<4;++j)
		{
			emp.a[i][j]=(i==j?0:-inf);
		}
	}
	f.n=1;
	f.m=4;
	f.a[0][0]=f.a[0][1]=f.a[0][2]=f.a[0][3]=0;
	B.n=B.m=4;
	for(short i=0;i<4;++i)
	{
		for(short j=0;j<4;++j)
		{
			B.a[i][j]=(i==2?(j==2?0:1):-inf);
		}
	}
	B.a[3][3]=0;
	A=C=B;
	A.a[0][0]=A.a[0][3]=1;
	C.a[0][1]=C.a[1][1]=C.a[0][3]=C.a[1][3]=1;
}
int n,q;
ll a[300001];
namespace T{
	struct node{
		int l,r;
		matrix prod;
	}t[1200001];
	void Build(cint p,cint l,cint r)
	{
		t[p].l=l;
		t[p].r=r;
		if(l==r)
		{
			if(a[l]>0)t[p].prod=A;
			else if(a[l]==0)t[p].prod=B;
			else t[p].prod=C;
			return;
		}
		cint mid=l+r>>1;
		Build(p<<1,l,mid);
		Build(p<<1|1,mid+1,r);
		t[p].prod=t[p<<1].prod*t[p<<1|1].prod;
	}
	void build()
	{
		Build(1,1,n);
	}
	void Update(cint p,cint x)
	{
		if(t[p].l>x||t[p].r<x)return;
		if(t[p].l==x&&t[p].r==x)
		{
			if(a[x]>0)t[p].prod=A;
			else if(a[x]==0)t[p].prod=B;
			else t[p].prod=C;
			return;
		}
		Update(p<<1,x);
		Update(p<<1|1,x);
		t[p].prod=t[p<<1].prod*t[p<<1|1].prod;
	}
	void update(cint x)
	{
		Update(1,x);
	}
	iint ask()
	{
		return (f*t[1].prod).a[0][3];
	}
}
void solve()
{
	cint l=read();
	cint r=read();
	cint d=read();
	a[l]+=d;
	T::update(l);
	if(r!=n)
	{
		a[r+1]-=d;
		T::update(r+1);
	}
	printf("%d\n",T::ask());
}
int main()
{
	init();
	n=read();
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
	}
	for(int i=n;i>=1;--i)
	{
		a[i]-=a[i-1];
	}
	T::build();
	q=read();
	while(q--)solve();
	return 0;
}
```

---

## 作者：BFSDFS123 (赞：2)

考虑对序列差分。

负数说明两个数左大右小，正数说明两个数左小右大。

那我们只需要求一段区间，满足是一段正数和一段负数拼起来。

然后发现区间修改转换为了单点修改。

考虑维护以下的东西：

- 区间的答案（长度）。
- 从区间左端点开始的满足条件的答案（长度）。（以下简称左答案）
- 从区间右端点开始的满足条件的答案（长度）。（以下简称右答案）

为了更新这三个答案，再维护：

- 区间长度。
- 区间左端点的值。
- 区间右端点的值。

显然区间的答案首先可能是两个子区间的答案的最大值。

设左区间右端点的答案为 $x$，右区间左端点的答案为 $y$。

若 $x=0$ 或 $y=0$ 或 $x<0,y>0$，则两个子区间一定不能拼成大区间的答案。

为什么？

当 $x$ 或 $y$ 等于 $0$ 的时候，说明左右两数相等，故不能满足题目要求。

当 $x<0,y>0$ 时，此时原数组的 $a,b,c$ 满足 $a>b<c$，也不满足要求。

此时区间的左答案等于左子区间的左答案，区间的右答案等于右子区间的右答案。

当两个子区间可能拼成大区间的答案时，可能成为区间的答案的值为左子区间的右答案与右子区间的左答案的和。

当左子区间的左答案等于左子区间的长度的时候，区间的左答案等于左子区间的长度加上右子区间的左答案。

如果不满足条件，区间的左答案等于左子区间的左答案。

同理，当右子区间的右答案等于右子区间的长度的时候，区间的右答案等于右子区间的长度加上左子区间的左答案。

如果不满足条件，区间的右答案等于右子区间的右答案。

是不是觉得十分抽象？可以结合代码理解一下。

记得开 ``long long``。

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define LL_inf 1145141919810
#define ull unsigned long long
#define ll long long
using namespace std;
#define int long long
const int Maxn=3e5+10;
int tmp[Maxn];
struct Segmenttree{
	struct segtree{
		int res; // 区间答案 
		int len; // 长度 
		int lres,rres; // 左答案 右答案 
		int lval,rval; // 左值 右值 
	}t[Maxn<<2];
	#define ls node<<1
	#define rs node<<1|1 
	void pushup(int node)
	{
		t[node].res=max(t[ls].res,t[rs].res);
		t[node].res=max(t[node].res,max(t[ls].lres,t[rs].rres));
		t[node].lval=t[ls].lval;
		t[node].rval=t[rs].rval;
		t[node].len=t[ls].len+t[rs].len;
		int val1=t[ls].rval,val2=t[rs].lval;
		bool flag=true;
		if(val1==0 || val2==0 || (val1<0 && val2>0)) 
		{
			flag=false;
		}
		if(!flag)
		{
			t[node].lres=t[ls].lres;
			t[node].rres=t[rs].rres;
		}else{
			t[node].res=max(t[node].res,t[ls].rres+t[rs].lres);
			
			if(t[ls].lres==t[ls].len)
			{
				t[node].lres=t[ls].len+t[rs].lres;
			}else{
				t[node].lres=t[ls].lres;
			}
			
			if(t[rs].rres==t[rs].len)
			{
				t[node].rres=t[ls].rres+t[rs].len;
			}else{
				t[node].rres=t[rs].rres;
			}
		}
	}
	void build(int node,int l,int r)
	{
		if(l==r)
		{
			t[node].len=1;
			t[node].lval=t[node].rval=tmp[l];
			if(!tmp[l])
			{
				t[node].res=t[node].lres=t[node].rres=0;
			}else{
				t[node].res=t[node].lres=t[node].rres=1;
			}		
			return ;
		}
		int mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(node);
	}
	void update(int node,int l,int r,int pos,int val)
	{
		if(l==r)
		{
			tmp[l]+=val;
			t[node].len=1;
			t[node].lval=t[node].rval=tmp[l];
			if(!tmp[l])
			{
				t[node].res=t[node].lres=t[node].rres=0;
			}else{
				t[node].res=t[node].lres=t[node].rres=1;
			}
			return ;
		}
		int mid=(l+r)>>1;
		if(pos<=mid)
		{
			update(ls,l,mid,pos,val);
		}else{
			update(rs,mid+1,r,pos,val);
		}
		pushup(node);
	}
}seg;
int n;
int Ar[Maxn];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&Ar[i]);
	}
	for(int i=1;i<n;i++)
	{
		tmp[i]=Ar[i+1]-Ar[i];
	}
	int m;
	scanf("%lld",&m);
	if(n==1)
	{
		for(int i=1;i<=m;i++)
		{
			puts("1");
		}
		return 0;
	}
	seg.build(1,1,n-1);
	while(m--)
	{
		int l,r,d;
		scanf("%lld%lld%lld",&l,&r,&d);
		if(l!=1)
		{
			seg.update(1,1,n-1,l-1,d);
		}
		if(r!=n)
		{
			seg.update(1,1,n-1,r,-d);
		}
		
		printf("%lld\n",seg.t[1].res+1);
	}
	return 0;
}
```

---

## 作者：zesqwq (赞：2)

#  CF739C Alyona and towers

## Analysis

感觉和许多线段树题很相似，于是考虑线段树。

我们发现这个东西维护起来非常麻烦，考虑可以差分它，然后问题就变成了求最长的一个正数段接上一个负数段。

我们给线段树的每个节点给 $6$ 个信息：$\text{lv}$ 和 $\text{rv}$ 表示最左边的值和最右边的值，$\text{lans}$ 和 $\text{rans}$ 表示从最左侧开始和最右侧开始的答案，$\text{len}$ 表示该节点的长度，$\text{ans}$ 表示该节点的答案。

当左右节点合并信息时，就可以先判断左端点 $\text{rv}$ 和右断点 $\text{lv}$ 是否符合要求，然后再选择性的信息。

合并过程还是比较简单的，略加思考就可以知道了。

## code

采用 $\text{zkw}$ 线段树实现。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;

const int N = 3e5 + 10;
int n, a[N], limit, m;
long long s[N];
struct Node {
    long long lv, rv, ans, lans, rans;
    int len;
} w[N << 2];
inline void pushup(Node &u, Node ls, Node rs) {
    u.lv = ls.lv, u.rv = rs.rv, u.len = ls.len + rs.len, u.ans = max(ls.ans, rs.ans), u.lans = ls.lans, u.rans = rs.rans;
    if (ls.rv > 0 || rs.lv < 0) {
        u.ans = max(u.ans, ls.rans + rs.lans);
        if (ls.lans == ls.len) u.lans = ls.len + rs.lans;
        if (rs.rans == rs.len) u.rans = rs.len + ls.rans;
    }
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), s[i] = a[i] - a[i - 1];
    cin >> m, s[1] = 0, limit = 1;
    while (limit <= n) limit <<= 1;
    for (int i = 1; i <= n; i++) w[limit + i] = {s[i], s[i], (bool)s[i], (bool)s[i], (bool)s[i], 1};
    for (int i = limit; i; i--) pushup(w[i], w[i << 1], w[i << 1 | 1]);
    int l, r, d;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &l, &r, &d);
        if (l != 1) {
            s[l] += d, w[limit + l] = {s[l], s[l], (bool)s[l], (bool)s[l], (bool)s[l], 1};
            for (int i = limit + l >> 1; i; i >>= 1) pushup(w[i], w[i << 1], w[i << 1 | 1]);
        }
        if (r != n) {
            s[r + 1] -= d, w[limit + r + 1] = {s[r + 1], s[r + 1], (bool)s[r + 1], (bool)s[r + 1], (bool)s[r + 1], 1};
            for (int i = limit + r + 1 >> 1; i; i >>= 1) pushup(w[i], w[i << 1], w[i << 1 | 1]);
        }
        printf("%lld\n", w[1].ans + 1);
    }
    return 0;
}
```

---

## 作者：tzc_wk (赞：2)

[Codeforces 题目传送门](https://codeforces.com/contest/739/problem/C) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF739C)

~~可能有人会问我为什么为这道 *2500 的 D1C 写题解，我觉得大概是想要在写题解数量上 dd ycx 吧，因为 ycx 到目前为止写了 143 篇题解，而这也是我的第 143 篇题解（（（~~

大概和 CF1149C Tree Generator™ 比较像？做过那题这题基本可以一眼秒了（

线段树。每个区间维护以下八个值：

- 区间第一个元素的值 $fst$
- 区间最后一个元素的值 $lst$
- 区间长度 $len$
- 以左端点为开头的最长下降前缀的长度 $llen$
- 以右端点为开头的最长上升后缀的长度 $rlen$
- 以左端点为开头的先上升再下降的最长前缀长度 $l\_tower$
- 以右端点为结尾的先上升再下降的最长前缀长度 $r\_tower$
- 这段区间中最长的先上升后下降子序列的长度 $mx$

考虑合并左右两个区间：

- $fst$ 就直接继承左儿子的 $fst$ 即可
- $lst$ 就直接继承右儿子的 $lst$ 即可
- $len$ 就直接将左右儿子的 $len$ 加起来即可
- $llen$ 分两种情况，如果左儿子的 $llen$ 就等于其 $len$，并且左儿子的 $lst$ 大于右儿子的 $fst$，那么该节点的 $llen$ 等于左右节点的 $llen$ 之和。否则该节点的 $llen$ 等于左儿子的 $llen$。$rlen$ 也同理
- $l\_tower$ 分三种情况，如果左儿子本身就是上升序列，即左儿子的 $rlen$ 等于其 $len$，并且左儿子的 $lst$ 小于右儿子的 $fst$，那么 $l\_tower$ 就等于左儿子的 $rlen$ 与右儿子的 $l\_tower$ 的和。如果左儿子的 $l\_tower$ 等于其 $len$，并且左儿子的 $lst$ 大于右儿子的 $fst$，那么 $l\_tower$ 就等于左儿子的 $len$ 与右儿子的 $llen$ 之和。否则 $l\_tower$ 等于左儿子的 $l\_tower$。$r\_tower$ 也同理。
- $mx$ 分四种情况，首先它可以从左右儿子的 $mx$ 分别继承来，即它首先等于左右儿子 $mx$ 的较大者。其次如果左儿子的 $lst$ 小于右儿子的 $fst$，那么 $mx$ 可以用左儿子的 $rlen$ 与右儿子的 $l\_tower$ 之和更新；如果左儿子的 $lst$ 大于右儿子的 $fst$，那么 $mx$ 可以用左儿子的 $r\_tower$ 与右儿子的 $llen$ 之和更新

写个结构体维护一下即可。区间修改就直接打个标记。

芜湖~做完了，记得开 `long long`，复杂度线对。

```cpp
const int MAXN=3e5;
int n,qu,a[MAXN+5];
struct data{
	ll fst,lst;int len,llen,rlen,l_tower,r_tower,mx;
	data(){fst=lst=len=llen=rlen=l_tower=r_tower=mx=0;}
	data(int _fst,int _lst,int _len,int _llen,int _rlen,int _l_tower,int _r_tower,int _mx):
	fst(_fst),lst(_lst),len(_len),llen(_llen),rlen(_rlen),l_tower(_l_tower),r_tower(_r_tower),mx(_mx){}
	friend data operator +(data a,data b){
		data c;
		c.fst=a.fst;c.lst=b.lst;c.len=a.len+b.len;
		c.llen=(a.llen==a.len&&a.lst>b.fst)?(a.llen+b.llen):a.llen;
		c.rlen=(b.rlen==b.len&&a.lst<b.fst)?(b.rlen+a.rlen):b.rlen;
		c.l_tower=(a.rlen==a.len&&a.lst<b.fst)?(a.l_tower+b.l_tower):
				  ((a.l_tower==a.len&&a.lst>b.fst)?(a.l_tower+b.llen):(a.l_tower));
		c.r_tower=(b.llen==b.len&&a.lst>b.fst)?(b.r_tower+a.r_tower):
				  ((b.r_tower==b.len&&a.lst<b.fst)?(b.r_tower+a.rlen):(b.r_tower));
		c.mx=max(a.mx,b.mx);
		if(a.lst>b.fst) c.mx=max(c.mx,a.r_tower+b.llen);
		if(a.lst<b.fst) c.mx=max(c.mx,a.rlen+b.l_tower);
		return c;
	}
};
struct node{int l,r;ll lz;data v;} s[MAXN*4+5];
void pushup(int k){s[k].v=s[k<<1].v+s[k<<1|1].v;}
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;if(l==r){s[k].v=data(a[l],a[l],1,1,1,1,1,1);return;}
	int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);pushup(k);
}
void pushdown(int k){
	if(s[k].lz){
		s[k<<1].lz+=s[k].lz;s[k<<1].v.fst+=s[k].lz;s[k<<1].v.lst+=s[k].lz;
		s[k<<1|1].lz+=s[k].lz;s[k<<1|1].v.fst+=s[k].lz;s[k<<1|1].v.lst+=s[k].lz;
		s[k].lz=0;
	}
}
void modify(int k,int l,int r,int x){
	if(l<=s[k].l&&s[k].r<=r){
		s[k].lz+=x;s[k].v.fst+=x;s[k].v.lst+=x;
		return;
	} pushdown(k);int mid=s[k].l+s[k].r>>1;
	if(r<=mid) modify(k<<1,l,r,x);
	else if(l>mid) modify(k<<1|1,l,r,x);
	else modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
	pushup(k);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	build(1,1,n);scanf("%d",&qu);
	while(qu--){
		int l,r,v;scanf("%d%d%d",&l,&r,&v);
		modify(1,l,r,v);printf("%d\n",s[1].v.mx);
	}
	return 0;
}
```



---

## 作者：Msents (赞：1)

### 题意

给你一个数组，每次区间加后求最长单峰。

### 思路

考虑一个区间加的常用 trick，将数组差分，于是每次区间加只需要在差分数组上修改两处即可。

单峰的定义在差分数组上变为前一部分为正整数，后一部分为负整数的子序列。

考虑使用两个 set 维护最长单峰，第一个 set 用来维护单峰的划分情况，第二个 multiset 用来维护所有已划分出的单峰的长度。

由于差分后单峰定义只和子序列里元素的符号有关，所以只用管元素符号变化的情况，但是要注意 0 元素的特判。

~~省流：大分讨~~

当正数变负数时，若该元素不为单峰里的最后一个元素，将该元素所在的单峰按该元素的位置切成两半，若该元素为单峰里的第一个元素且前面不是 0，则将该元素合并到前面一个单峰上去，注意若该元素之后的数都为负数，则后面的数也要合并到前面去。

负数变正数时同理。

当非 0 变为 0 时，前后切割即可。

当 0 变非 0 时，左右分情况合并。

对于维护单峰长度，每次操作时将会被影响的单峰的长度在第二个 multiset 里删除，操作完后再塞回 multiset 就行。

~~上面的简化了很多情况写的时候还是要注意多分析。~~

思路还算简单，代码也许不是很易懂，反正我写的依托（~~总比线段树分讨好写~~）。

码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MaxN=300000;
typedef multiset<int,greater<int>>::iterator Iter;
multiset<int,greater<int>>ans;
struct ODT{
	ODT(int l,int r):l(l),r(r){
		it=ans.insert(r-l+1);
	}
	ODT(const ODT&obj){
		l=obj.l;
		r=obj.r;
		it=ans.insert(*obj.it);
	}
	~ODT(){
		ans.erase(it);
	}
	int l,r;
	Iter it;
	bool operator<(const ODT&obj)const{return l>obj.l;}
};
multiset<ODT>tree;
int n,a[MaxN+1],m;
int arr[MaxN+1];
set<ODT>::iterator Merge(set<ODT>::iterator it,int pos,int val){
	arr[pos]+=val;
	int l=it->l,r=it->r;
	auto p=tree.lower_bound(ODT(l-1,0));
	if(p!=tree.end()&&p->r+1==l&&(arr[p->r]>0||(arr[p->r]<0&&arr[l]<0))){
		int temp=p->l;
		tree.erase(it);
		tree.erase(p);
		it=tree.emplace(temp,r);
	}
	l=it->l,r=it->r;
	p=tree.lower_bound(ODT(r+1,0));
	if(p!=tree.end()&&r==p->l-1&&(arr[r]>0||(arr[r]<0&&arr[p->l]<0))){
		int temp=p->r;
		tree.erase(it);
		tree.erase(p);
		it=tree.emplace(l,temp);
	}
	arr[pos]-=val;
	return it;
}
void Update(int pos,int x){
	if(pos<=1)return;
	if(pos>n)return;
	if(arr[pos]==0&&arr[pos]+x!=0){
		Merge(tree.emplace(pos,pos),pos,x);
	}else if(arr[pos]!=0&&arr[pos]+x==0){
		auto it=tree.lower_bound(ODT(pos,0));
		int l=it->l,r=it->r;
		tree.erase(it);
		if(arr[pos]>0){
			if(l<=pos-1)Merge(tree.emplace(l,pos-1),pos,x);
			if(pos+1<=r)Merge(tree.emplace(pos+1,r),pos,x);
		}else{
			if(l<=pos-1)Merge(tree.emplace(l,pos-1),pos,x);
			if(pos+1<=r)Merge(tree.emplace(pos+1,r),pos,x);
		}
	}else{
		auto it=tree.lower_bound(ODT(pos,0));
		int l=it->l,r=it->r;
		if(arr[pos]>0&&arr[pos]+x<0){
			tree.erase(it);
			Merge(tree.emplace(l,pos),pos,x);
			if(pos+1<=r)Merge(tree.emplace(pos+1,r),pos,x);
		}else if(arr[pos]<0&&arr[pos]+x>0){
			tree.erase(it);
			if(l<=pos-1)Merge(tree.emplace(l,pos-1),pos,x);
			Merge(tree.emplace(pos,r),pos,x);
		}
	}
	arr[pos]+=x;
}
void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	arr[1]=0;
	for(int i=2;i<=n;i++)arr[i]=a[i]-a[i-1];
	int last=1,p=1;
	while(p<=n){
		int cnt=0;
		while(p<=n&&arr[p]>0)p++,cnt++;
		while(p<=n&&arr[p]<0)p++;
		if(last>=p){
			p++;
			last=p;
		}else{
			tree.emplace(last,p-1);
			last=p;
		}
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		int l,r,d;
		cin>>l>>r>>d;
		Update(l,d);
		Update(r+1,-d);
		cout<<max(1ll,*ans.begin()+1)<<'\n';
	}
}
#undef int
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	Solve();
	return 0;
}
```

---

## 作者：Buried_Dream (赞：1)

[更好的阅读体验](https://www.cnblogs.com/tttttttle/p/16643433.html)

图片加载不出来建议用上面的链接阅读。

## 题意：

维护区间加，全局最长单峰序列。

## Solution：

维护 $8$ 个量。

$lval$：左端点的权值。

$rval$：右端点的权值。

$lmax$：以左端点开始的最长的下降序列长度。

$rmax$：以右端点结束的最长的上升序列长度。

$lans$：以左端点开始的最长的单峰序列长度。

$rans$：以右端点结束的最长的单峰序列长度。

$ans$： 区间内最长的单峰序列长度。

$tag$：区间加法懒标记。

考虑怎么用左右两个儿子更新父节点的信息。

![](https://img2022.cnblogs.com/blog/2882377/202208/2882377-20220831153331837-1331456490.png)

用 $lson$ 来表示左儿子，$rson$ 来表示右儿子，$rt$ 来表示父节点。

## $lval$

显然父节点的 $lval$ 是左儿子的 $lval$。

## $rval$

显然父节点的 $rval$ 是右儿子的 $rval$。

## $lmax$

![](https://img2022.cnblogs.com/blog/2882377/202208/2882377-20220831153621597-342695701.png)


如果说左儿子的 $lmax$ 等于左儿子的区间长度，说明了左区间是个下降区间，如果同时左儿子的 $rval$ 大于了右儿子的 $lval$ 说明了父节点的 $lmax$ 能向右区间伸展，这个时候 $rt.lmax = lson.lmax + rson.lmax$。

![](https://img2022.cnblogs.com/blog/2882377/202208/2882377-20220831153953862-851309421.png)


否则无法跨过右区间，直接继承左儿子的值：$rt.lmax = lson.lmax$。

##  $rmax$

![](https://img2022.cnblogs.com/blog/2882377/202208/2882377-20220831154027895-1379254488.png)



如果说右儿子的 $rmax$ 等于右儿子的区间长度，说明了右区间是个上升区间，如果同时左儿子的 $rval$ 小于了右儿子的 $lval$ 说明了父节点的 $rmax$ 能向左区间伸展，这个时候 $rt.rmax = lson.rmax + rson.rmax$。

![](https://img2022.cnblogs.com/blog/2882377/202208/2882377-20220831154133290-1499560588.png)

否则无法跨过左区间，直接继承右儿子的值： $rt.rmax = rson.rmax$。

## $lans$

![](https://img2022.cnblogs.com/blog/2882377/202208/2882377-20220831154621088-2102604441.png)

如果说左儿子的 $rmax$ 等于左儿子的区间长度，说明了左儿子是个上升区间。

这个时候分两种情况：
- $lson.rval < rson.lval$ 说明了还能通过右儿子的 $lans$ 继续扩展：$rt.lans = lson.rmax + rson.lans$。

- $lson.rval > rson.lval$ 说明了只能通过右儿子的 $lmax$ 继续扩展： $rt.lans = lson.rmax + rson.lmax$。

![](https://img2022.cnblogs.com/blog/2882377/202208/2882377-20220831155009328-290452649.png)

如果说左儿子的 $lans$ 等于区间长度，想用右儿子扩展的话，必须满足 $lson.rval > rson.lval$，这个时候：$rt.lans = lson.lans + rson.lmax$。 

否则无法通过右区间来更新，直接继承左儿子的值：$rt.lans = lson.lans$。

## $rans$

![](https://img2022.cnblogs.com/blog/2882377/202208/2882377-20220831155428033-1863683230.png)

如果说右儿子的 $lmax$ 等于右儿子的区间长度，说明了右儿子是个下降区间。

这个时候分两种情况：

- $lson.rval > rson.lval$ 说明了还能通过左儿子的 $rans$ 继续扩展：$rt.rans = lson.rans + rson.lmax$。

- $lson.rval < rson.lval$ 说明了只能通过左儿子的 $rmax$ 继续扩展： $rt.rans = lson.rmax + rson.lmax$。

![](https://img2022.cnblogs.com/blog/2882377/202208/2882377-20220831155728879-669242948.png)


如果说右儿子的 $lans$ 等于区间长度，想用左儿子扩展的话，必须满足 $lson.rval < rson.lval$，这个时候：$rt.rans = lson.rmax + rson.lans$。 

否则无法通过右区间来更新，直接继承左儿子的值：$rt.rans = rson.rans$。

## $ans$

![](https://img2022.cnblogs.com/blog/2882377/202208/2882377-20220831160122166-839361757.png)

答案可能是左右儿子答案的最大值。

![](https://img2022.cnblogs.com/blog/2882377/202208/2882377-20220831160201578-490810725.png)

也可能是 $lson.rmax $ 和 $rson.lmax$ 接起来。

![](https://img2022.cnblogs.com/blog/2882377/202208/2882377-20220831160246312-987541829.png)


也可能是 $lson.lans$ 和 $rson.lmax$ 接起来。

![](https://img2022.cnblogs.com/blog/2882377/202208/2882377-20220831160319493-656971773.png)


也可能是 $rson.rans$ 和 $lson.rmax$ 接起来。

最后取个 $\max$ 就行了。

然后修改就是普通的区间修改。

```cpp
/**
 *	author: TLE_Automation
 *	creater: 2022.8.28
**/
#include<cmath>
#include<queue>
#include<cstdio>
#include<bitset>
#include<cstring>
#include<iostream>
#include<algorithm>
#define gc getchar 
#define INF 0x3f3f3f3f
#define int long long
using namespace std;
typedef long long ll;
const int Maxn = 6e5 + 10;
const int mod = 998244353;
const ll inf = 0x3f3f3f3f3f3f3f3f;
#define debug cout << "i ak ioi" << "\n"
inline void print(int x) {if (x < 0) putchar('-'), x = -x; if(x > 9) print(x / 10); putchar(x % 10 + '0');}
inline char readchar() {static char buf[100000], *p1 = buf, *p2 = buf; return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;}
inline int read() { int res = 0, f = 0; char ch = gc();for (; !isdigit(ch); ch = gc()) f |= (ch == '-'); for (; isdigit(ch); ch = gc()) res = (res << 1) + (res << 3) + (ch ^ '0'); return f ? -res : res;}

namespace Seg {
	#define lson rt << 1
	#define rson rt << 1 | 1
	struct Node { int l, r, len, lval, rval, lmax, rmax, lans, rans, ans, tag; } tree[Maxn << 2];
	void pushup(int rt) {
		tree[rt].lval = tree[lson].lval, tree[rt].rval = tree[rson].rval;
		
		if(tree[lson].lmax == tree[lson].len && tree[lson].rval > tree[rson].lval) 
			tree[rt].lmax = tree[lson].lmax + tree[rson].lmax;
		else tree[rt].lmax = tree[lson].lmax;
		
		if(tree[rson].rmax == tree[rson].len && tree[rson].lval > tree[lson].rval) 
			tree[rt].rmax = tree[rson].rmax + tree[lson].rmax;
		else tree[rt].rmax = tree[rson].rmax;
		
		if(tree[lson].rmax == tree[lson].len && tree[lson].rval < tree[rson].lval) 
			tree[rt].lans = tree[lson].rmax + tree[rson].lans;
		else if(tree[lson].rmax == tree[lson].len && tree[lson].rval > tree[rson].lval) 
			tree[rt].lans = tree[lson].rmax + tree[rson].lmax;
		else if(tree[lson].lans == tree[lson].len && tree[lson].rval > tree[rson].lval)
			tree[rt].lans = tree[lson].lans + tree[rson].lmax;
		else tree[rt].lans = tree[lson].lans;
		
		if(tree[rson].lmax == tree[rson].len && tree[rson].lval < tree[lson].rval)
			tree[rt].rans = tree[rson].rans + tree[lson].rans;
		else if(tree[rson].lmax == tree[rson].len && tree[rson].lval > tree[lson].rval)
			tree[rt].rans = tree[rson].rans + tree[lson].rmax;
		else if(tree[rson].rans == tree[rson].len && tree[lson].rval < tree[rson].lval) 
			tree[rt].rans = tree[rson].rans + tree[lson].rmax;
		else tree[rt].rans = tree[rson].rans;
		
		tree[rt].ans = max(tree[lson].ans, tree[rson].ans);
		if(tree[lson].rval != tree[rson].lval )tree[rt].ans = max(tree[rt].ans, tree[lson].rmax + tree[rson].lmax);
		if(tree[lson].rval < tree[rson].lval) tree[rt].ans = max(tree[rt].ans, tree[lson].rmax + tree[rson].lans);
		if(tree[lson].rval > tree[rson].lval) tree[rt].ans = max(tree[rt].ans, tree[rson].lmax + tree[lson].rans);
	}
	void build(int rt, int l, int r) {
		tree[rt].len = r - l + 1;
		tree[rt].l = l, tree[rt].r = r;
		if(l == r) {
			int x = read();
			tree[rt].lval = tree[rt].rval = x;
			tree[rt].lmax = tree[rt].rmax = 1;
			tree[rt].lans = tree[rt].rans = tree[rt].ans = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(lson, l, mid), build(rson, mid + 1, r);
		pushup(rt);
	}
	void pushdown(int rt) {
		if(!tree[rt].tag) return;
		tree[lson].tag += tree[rt].tag, tree[rson].tag += tree[rt].tag;
		tree[lson].lval += tree[rt].tag, tree[lson].rval += tree[rt].tag;
		tree[rson].lval += tree[rt].tag, tree[rson].rval += tree[rt].tag;		
		tree[rt].tag = 0;
	}
	void change(int rt, int l, int r, int k) {
		if(tree[rt].l > r || tree[rt].r < l) return;
		if(tree[rt].l >= l && tree[rt].r <= r) {
			tree[rt].lval += k, tree[rt].rval += k, tree[rt].tag += k; return;
		} pushdown(rt);
		change(lson, l, r, k), change(rson, l, r, k), pushup(rt);
	} 
} 
using namespace Seg;
signed main() 	
{
	
//	freopen("in.in", "r", stdin);
//	freopen("baoli.out", "w", stdout);
	int n = read();
	build(1, 1, n);
	int Q = read();
	for(int i = 1; i <= Q; i++) {
		int l = read(), r = read(), k = read();
		change(1, l, r, k), printf("%lld\n", tree[1].ans);
	}
	return (0 - 0);
}

/**
 * _ooOoo_
 * o8888888o
 * 88" . "88
 * (| -_- |)
 *  O\ = /O
 * ___/`---'\____
 * .   ' \\| |// `.
 * / \\||| : |||// \
 * / _||||| -:- |||||- \
 * | | \\\ - /// | |
 * | \_| ''\---/'' | |
 * \ .-\__ `-` ___/-. /
 * ___`. .' /--.--\ `. . __
 * ."" '< `.___\_<|>_/___.' >'"".
 * | | : `- \`.;`\ _ /`;.`/ - ` : | |
 * \ \ `-. \_ __\ /__ _/ .-` / /
 * ======`-.____`-.___\_____/___.-`____.-'======
 * `	=---='
 *          .............................................
 *           佛曰：bug泛滥，我已瘫痪！
 */
```

---

## 作者：smallpeter (赞：0)

# 题面翻译

现在有$n$个数，$m$个操作，**每次区间加一个数**，对于**每一次**操作，你要找出**最长**的$\ a_l...a_r\ $，满足

$$\exists k\! \in\![l,r],a_l<a_{l+1}<a_{l+2}<...<a_k>a_{k+1}>a_{k+2}>...>a_r$$

输出其长度。

# 解题思路

对于这种区间查询加上区间修改的问题，很容易通过线段树维护。发现我的做法是有点麻烦的，要分很多种情况进行考虑，建议理清楚思路后，静下心来写代码。

为了方便下文讲述，把题目所求的子段叫做单峰子段，单峰子段的最大值称作峰点，单调递减的子段称作单减子段，单调递增子段的子段称作单增子段。

首先根据题目规定，要维护区间单峰子段。我们分类讨论一下峰点的位置：（其中红色的向上的三角形表示峰点，逐渐收窄的三角形表示值的单调递减）

1. 峰点在左
![](https://cdn.luogu.com.cn/upload/image_hosting/x1euk4tn.png)
 
2. 峰点在右

![](https://cdn.luogu.com.cn/upload/image_hosting/qtybjqpu.png)

如果我们直接枚举峰点的话，复杂度直接原地爆炸。那我们怎么做呢？

发现实际上峰点在左的情况可以拆为两个部分：

![](https://cdn.luogu.com.cn/upload/image_hosting/5zbrynf6.png)

第一部分是左区间的后缀单峰子段，第二部分是右区间的前缀单减子段，我们假设左区间的右端点为 $mid$，当 $a_{mid}>a_{mid+1}$ 的时候可以向右拓展。否则直接继承左区间。当峰点在右区间的时候求法也类似，就不再重复，读者可自行推导。

接下来我们还要维护六个东西：前缀单峰子段，前缀单减子段，后缀单峰子段，后缀单增子段，区间左端的值，区间右端的值。

区间左右端的值很容易维护，每次修改的时候直接加就好了。

接下来是前缀单峰子段，与维护单峰子段一个道理，也是拆成两段：

![](https://cdn.luogu.com.cn/upload/image_hosting/cpdm9n9u.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/2gyhqakh.png)

如果左区间可为一个单峰子段且 $a_{mid}>a_{mid+1}$，即可向右拓展。否则直接继承左区间。

后缀单峰子段与前缀单峰子段类似，读者可自行推导。

接下来是前缀单减子段：

![](https://cdn.luogu.com.cn/upload/image_hosting/bvdk940w.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/ggyhezxq.png)

如果左区间为单减子段，即可向右拓展。否则直接继承左区间。

后缀单增子段与前缀单减子段类似，读者可自行推导。

不难发现随区间修改操作而变化的只有左右端点的值，于是下传懒标记也非常方便。

再略微总结一下，一共要维护七个东西，区间最左端的值、区间最右端的值、前缀单减子段，后缀单增子段、前缀单峰子段、后缀单峰子段、单峰子段。

# 代码

未经过~~美化~~的代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long

const LL N=3e5+10;

LL n,a[N],q,lq,rq,xq;

struct Tree{
	LL lv;//区间最左端的值 
	LL rv;//区间最右端的值
	LL qzup;//区间前缀最长上升子段
	LL qzdn;//区间前缀最长下降子段
	LL hzup;//区间后缀最长上升子段
	LL hzdn;//区间后缀最长下降子段
	LL qzmx;//区间前缀最长峰顶子段
	LL hzmx;//区间后缀最长峰顶子段
	LL mx;//区间最长峰顶子段 （这才是我要求的啊QwQ） 
	LL lazy;//懒标记 
}tree[N<<2]; 

void pushup(LL w,LL l,LL r){
	LL mid=(l+r)>>1;
	LL lfl=l,lfr=mid,rtl=mid+1,rtr=r;
	tree[w].lv=tree[w<<1].lv;
	tree[w].rv=tree[w<<1|1].rv;
	tree[w].qzup=tree[w<<1].qzup;
	if(tree[w<<1].qzup==(lfr-lfl+1)&&tree[w<<1].rv<tree[w<<1|1].lv){
		tree[w].qzup=(lfr-lfl+1)+tree[w<<1|1].qzup;
	}
	tree[w].qzdn=tree[w<<1].qzdn;
	if(tree[w<<1].qzdn==(lfr-lfl+1)&&tree[w<<1].rv>tree[w<<1|1].lv){
		tree[w].qzdn=(lfr-lfl+1)+tree[w<<1|1].qzdn;
	}
	tree[w].hzup=tree[w<<1|1].hzup;
	if(tree[w<<1|1].hzup==(rtr-rtl+1)&&tree[w<<1].rv<tree[w<<1|1].lv){
		tree[w].hzup=(rtr-rtl+1)+tree[w<<1].hzup;
	}
	tree[w].hzdn=tree[w<<1|1].hzdn;
	if(tree[w<<1|1].hzdn==(rtr-rtl+1)&&tree[w<<1].rv>tree[w<<1|1].lv){
		tree[w].hzdn=(rtr-rtl+1)+tree[w<<1].hzdn;
	}
	tree[w].qzmx=tree[w<<1].qzmx;
	if(tree[w<<1].qzmx==(lfr-lfl+1)&&tree[w<<1].rv>tree[w<<1|1].lv){
		tree[w].qzmx=max(tree[w].qzmx,(lfr-lfl+1)+tree[w<<1|1].qzdn);
	}
	if(tree[w<<1].qzup==(lfr-lfl+1)&&tree[w<<1].rv<tree[w<<1|1].lv){
		tree[w].qzmx=max(tree[w].qzmx,(lfr-lfl+1)+tree[w<<1|1].qzmx);
	}
	tree[w].hzmx=tree[w<<1|1].hzmx;
	if(tree[w<<1|1].hzdn==(rtr-rtl+1)&&tree[w<<1].rv>tree[w<<1|1].lv){
		tree[w].hzmx=max(tree[w].hzmx,(rtr-rtl+1)+tree[w<<1].hzmx);
	}
	if(tree[w<<1|1].hzmx==(rtr-rtl+1)&&tree[w<<1].rv<tree[w<<1|1].lv){
		tree[w].hzmx=max(tree[w].hzmx,(rtr-rtl+1)+tree[w<<1].hzup);
	}
	tree[w].mx=max(tree[w<<1].mx,tree[w<<1|1].mx);
	if(tree[w<<1].rv>tree[w<<1|1].lv){
		tree[w].mx=max(tree[w].mx,tree[w<<1].hzmx+tree[w<<1|1].qzdn);
	}
	if(tree[w<<1].rv<tree[w<<1|1].lv){
		tree[w].mx=max(tree[w].mx,tree[w<<1].hzup+tree[w<<1|1].qzmx);
	}
	return ;
}

void pushdown(LL w,LL l,LL r){
	if(tree[w].lazy==0) return ;
	tree[w<<1].lazy+=tree[w].lazy;
	tree[w<<1|1].lazy+=tree[w].lazy;
	tree[w<<1].lv+=tree[w].lazy;
	tree[w<<1].rv+=tree[w].lazy;
	tree[w<<1|1].lv+=tree[w].lazy;
	tree[w<<1|1].rv+=tree[w].lazy;
	tree[w].lazy=0;
	return ;
}

void bulid(LL l,LL r,LL w){
	tree[w].hzdn=tree[w].hzmx=tree[w].hzup=tree[w].lv=tree[w].mx=tree[w].qzdn=tree[w].qzmx=tree[w].qzup=tree[w].rv=0;
	if(l==r){
		tree[w].hzdn=tree[w].hzmx=tree[w].hzup=tree[w].mx=tree[w].qzdn=tree[w].qzmx=tree[w].qzup=1;
		tree[w].lv=tree[w].rv=a[l];
		return ;
	} 
	LL mid=(l+r)>>1;
	bulid(l,mid,w<<1);
	bulid(mid+1,r,w<<1|1);
	pushup(w,l,r);
	return ;
}

void change(LL l,LL r,LL w,LL lx,LL rx,LL x){
	if(l>=lx&&r<=rx){
		tree[w].lazy+=x;
		tree[w].lv+=x;
		tree[w].rv+=x;
		return ;
	}
	pushdown(w,l,r);
	LL mid=(l+r)>>1;
	if(mid>=lx){
		change(l,mid,w<<1,lx,rx,x);
	}
	if(mid<rx){
		change(mid+1,r,w<<1|1,lx,rx,x);
	}
	pushup(w,l,r);
	return ;
}

Tree query(LL l,LL r,LL w,LL lx,LL rx){
	if(l>=lx&&r<=rx){
		return tree[w];
	}
	pushdown(w,l,r);
	LL mid=(l+r)>>1;
	if(mid>rx){
		return query(l,mid,w<<1,lx,rx);
	}
	if(mid<=lx){
		return query(mid+1,r,w<<1|1,lx,rx);
	}
	Tree lf=query(l,mid,w<<1,lx,rx),rt=query(mid+1,r,w<<1|1,lx,rx),ans;
	ans.lv=lf.lv;
	ans.rv=rt.rv;
	ans.qzup=lf.qzup;
	if(lf.qzup==(mid-l+1)&&lf.rv<rt.lv){
		ans.qzup=(mid-l+1)+rt.qzup;
	}
	ans.qzdn=lf.qzdn;
	if(lf.qzdn==(mid-l+1)&&lf.rv>rt.lv){
		ans.qzdn=(mid-l+1)+rt.qzdn;
	}
	ans.hzup=rt.hzup;
	if(rt.hzup==(r-mid+1+1)&&lf.rv<rt.lv){
		ans.hzup=(r-mid+1+1)+lf.hzup;
	}
	ans.hzdn=rt.hzdn;
	if(rt.hzdn==(r-mid+1+1)&&lf.rv>rt.lv){
		ans.hzdn=(r-mid+1+1)+lf.hzdn;
	}
	ans.qzmx=lf.qzmx;
	if(lf.qzmx==(mid-l+1)&&lf.rv>rt.lv){
		ans.qzmx=max(ans.qzmx,(mid-l+1)+rt.qzdn);
	}
	if(lf.qzup==(mid-l+1)&&lf.rv<rt.lv){
		ans.qzmx=max(ans.qzmx,(mid-l+1)+rt.qzmx);
	}
	ans.hzmx=rt.hzmx;
	if(rt.hzdn==(r-mid+1+1)&&lf.rv>rt.lv){
		ans.hzmx=max(ans.hzmx,(r-mid+1+1)+lf.hzmx);
	}
	if(rt.hzmx==(r-mid+1+1)&&lf.rv<rt.lv){
		ans.hzmx=max(ans.hzmx,(r-mid+1+1)+lf.hzup);
	}
	ans.mx=max(lf.mx,rt.mx);
	if(lf.rv<rt.lv){
		ans.mx=max(ans.mx,lf.hzmx+rt.qzdn);
	}
	if(lf.rv>rt.lv){
		ans.mx=max(ans.mx,lf.hzup+rt.qzmx);
	}
	return ans; 
}

int main(){
	scanf("%lld",&n);
	for(LL i=1;i<=n;i++) scanf("%lld",&a[i]);
	bulid(1,n,1);
	scanf("%lld",&q);
	while(q--){
		scanf("%lld%lld%lld",&lq,&rq,&xq);
		change(1,n,1,lq,rq,xq);
		printf("%lld\n",query(1,n,1,1,n).mx);
	}
	return 0;
}
```

可以看到是有不少重复，无用的部分。于是我修改了一下代码（优化了无用部分，然后加了一点注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long

const LL N=3e5+10;

LL n,a[N],q,lq,rq,xq;

struct Tree{
	LL lv;//区间最左端的值 
	LL rv;//区间最右端的值
//useless	LL qzup;//区间前缀最长上升子段
	LL qzdn;//区间前缀最长下降子段
	LL hzup;//区间后缀最长上升子段
//useless	LL hzdn;//区间后缀最长下降子段
	LL qzmx;//区间前缀最长峰顶子段
	LL hzmx;//区间后缀最长峰顶子段
	LL mx;//区间最长峰顶子段 （这才是我要求的啊QwQ） 
	LL lazy;//懒标记 
}tree[N<<2]; 

void merge(Tree &x,Tree lf,Tree rt,LL l,LL r){
	LL mid=(l+r)>>1;
	LL lfl=l,lfr=mid,rtl=mid+1,rtr=r;
	x.lv=lf.lv;
	x.rv=rt.rv;
	x.qzdn=lf.qzdn;//直接继承
	if(lf.qzdn==(lfr-lfl+1)&&lf.rv>rt.lv){//可以向右拓展 
		x.qzdn=(lfr-lfl+1)+rt.qzdn;
	}
	x.hzup=rt.hzup;//直接继承
	if(rt.hzup==(rtr-rtl+1)&&lf.rv<rt.lv){//可以向左拓展 
		x.hzup=(rtr-rtl+1)+lf.hzup;
	}
	x.qzmx=lf.qzmx;//直接继承 
	if(lf.qzmx==(lfr-lfl+1)&&lf.rv>rt.lv){//可以向右拓展 
		x.qzmx=max(x.qzmx,(lfr-lfl+1)+rt.qzdn);
	}
	if(lf.hzup==(lfr-lfl+1)&&lf.rv<rt.lv){//可以向右拓展 
		x.qzmx=max(x.qzmx,(lfr-lfl+1)+rt.qzmx);
	}
	x.hzmx=rt.hzmx;//直接继承
	if(rt.qzdn==(rtr-rtl+1)&&lf.rv>rt.lv){//可以向左拓展 
		x.hzmx=max(x.hzmx,(rtr-rtl+1)+lf.hzmx);
	}
	if(rt.hzmx==(rtr-rtl+1)&&lf.rv<rt.lv){//可以向左拓展 
		x.hzmx=max(x.hzmx,(rtr-rtl+1)+lf.hzup);
	}
	x.mx=max(lf.mx,rt.mx);//直接继承
	if(lf.rv>rt.lv){//峰点可以在左边，且可以向右拓展
		x.mx=max(x.mx,lf.hzmx+rt.qzdn);
	}
	if(lf.rv<rt.lv){//峰点可以在右边，且可以向左拓展
		x.mx=max(x.mx,lf.hzup+rt.qzmx);
	}
	return ;
}

void pushup(LL w,LL l,LL r){
	merge(tree[w],tree[w<<1],tree[w<<1|1],l,r);
	return ;
}

void pushdown(LL w,LL l,LL r){
	if(tree[w].lazy==0) return ;
	tree[w<<1].lazy+=tree[w].lazy;
	tree[w<<1|1].lazy+=tree[w].lazy;
	tree[w<<1].lv+=tree[w].lazy;
	tree[w<<1].rv+=tree[w].lazy;
	tree[w<<1|1].lv+=tree[w].lazy;
	tree[w<<1|1].rv+=tree[w].lazy;
	tree[w].lazy=0;
	return ;
}

void bulid(LL l,LL r,LL w){
	tree[w].hzmx=tree[w].hzup=tree[w].lv=tree[w].mx=tree[w].qzdn=tree[w].qzmx=tree[w].rv=0;
	if(l==r){
		tree[w].hzmx=tree[w].hzup=tree[w].mx=tree[w].qzdn=tree[w].qzmx=1;
		tree[w].lv=tree[w].rv=a[l];
		return ;
	} 
	LL mid=(l+r)>>1;
	bulid(l,mid,w<<1);
	bulid(mid+1,r,w<<1|1);
	pushup(w,l,r);
	return ;
}

void change(LL l,LL r,LL w,LL lx,LL rx,LL x){
	if(l>=lx&&r<=rx){
		tree[w].lazy+=x;
		tree[w].lv+=x;
		tree[w].rv+=x;
		return ;
	}
	pushdown(w,l,r);
	LL mid=(l+r)>>1;
	if(mid>=lx){
		change(l,mid,w<<1,lx,rx,x);
	}
	if(mid<rx){
		change(mid+1,r,w<<1|1,lx,rx,x);
	}
	pushup(w,l,r);
	return ;
}

Tree query(LL l,LL r,LL w,LL lx,LL rx){
	if(l>=lx&&r<=rx){
		return tree[w];
	}
	pushdown(w,l,r);
	LL mid=(l+r)>>1;
	if(mid>rx){
		return query(l,mid,w<<1,lx,rx);
	}
	if(mid<=lx){
		return query(mid+1,r,w<<1|1,lx,rx);
	}
	Tree lf=query(l,mid,w<<1,lx,rx),rt=query(mid+1,r,w<<1|1,lx,rx),ans;
	merge(ans,lf,rt,lx,rx);
	return ans;
}

int main(){
	scanf("%lld",&n);
	for(LL i=1;i<=n;i++) scanf("%lld",&a[i]);
	bulid(1,n,1);
	scanf("%lld",&q);
	while(q--){
		scanf("%lld%lld%lld",&lq,&rq,&xq);
		change(1,n,1,lq,rq,xq);
		printf("%lld\n",query(1,n,1,1,n).mx);
	}
	return 0;
}
```

---

## 作者：xfrvq (赞：0)

[$\tt Link$](/problem/CF739C)。

简单 $^{\ast}2500$，寄之。

---

一眼使用线段树维护序列，然后线段树的节点维护区间的答案。

考虑节点的 `push_up`，我们应该讨论最长的单峰子段

1. 上升部分和下降部分全部在左边/右边
2. 上升全部在左，下降部分在左部分在右
3. 下降全部在右，上升部分在左部分在右

为了实现第二、三种情况的判断，我们在线段树的节点中维护：

+ 从左边开始的最长下降子段 $ld$
+ 从右边开始的最长上升子段 $ru$
+ 从左边开始的最长单峰子段 $al$
+ 从右边开始的最长单峰子段 $ar$

讨论答案 $ans$ 如何得到，应该是以下三种情况取 $\max$。

* 第一种：左边的答案，右边的答案。
* 第二种：判断 $mid$ 处是否满足单调下降，然后把左边的 $ar$ 和右边的 $ld$ 加起来。
* 第三种：判断 $mid$ 处是否满足单调上升，然后把左边的 $ru$ 和右边的 $al$ 加起来。

然后讨论 $ld,ru,al,ar$ 的维护。

+ $ld$ 讨论 *左边前缀* 和 *左边全部，右边前缀* 两种情况
+ $ru$ 讨论 *右边后缀* 和 *右边全部，左边后缀* 两种情况
+ $al$ 讨论 *左边前缀* 和 *上升全部在左，下降部分在左部分在右* 和 *上升部分在左部分在右，下降全部在右* 两种情况
+ $ar$ 讨论 *右边前缀* 和 *下降全部在右，上升部分在左部分在右* 和 *下降部分在左部分在右，上升全部在左* 两种情况

为了判断 $mid$ 处的单调性，我们维护最左值 $lv$ 和最右值 $rv$。

还要维护区间的长度 $len$。

转移看下面 $\downarrow$。

```cpp
node mrg(const node &a,const node &b){
    node res;
    res.len = a.len + b.len;
    res.lv = a.lv; res.rv = b.rv;
    res.ld = a.ld; res.ru = b.ru;
    if(a.ld == a.len && a.rv > b.lv) res.ld = a.len + b.ld;
    if(b.ru == b.len && a.rv < b.lv) res.ru = b.len + a.ru;
    res.al = a.al; res.ar = b.ar;
    if(a.al == a.len && a.rv > b.lv) res.al = a.len + b.ld;
    if(a.ru == a.len && a.rv < b.lv) res.al = a.len + b.al;
    if(b.ar == b.len && a.rv < b.lv) res.ar = b.len + a.ru;
    if(b.ld == b.len && a.rv > b.lv) res.ar = b.len + a.ar;
    res.ans = max(a.ans,b.ans);
    if(a.rv > b.lv) chkmax(res.ans,a.ar + b.ld);
    if(a.rv < b.lv) chkmax(res.ans,a.ru + b.al);
    return res;
}
```

另：可以差分后维护正负段，更好写。

---

## 作者：ningago (赞：0)

 题意：

- 区间加，区间（全局）求最长合唱队列。

重点分析 pushup 部分：

下文 $Len(k)$ 表示区间 $k$ 的长度，$ls,rs$ 表示左右儿子。方便起见，计 $x=\max\{y\}$ 表示将 $x$ 赋值为 $x,y$ 中的较大数。

计 $last$ 为区间最后一个数：

- $last_k = last_{rs}$。

计 $first$ 为区间第一个数：

- $first_k = first_{ls}$。

计 $len$ 为最长合唱队形：
- $len_k = \max\{len_{ls},len_{rs}\}$；

- 如果 $last_{ls} > first_{rs}$，则 $len_k = \max\{suclen_{ls} + predown_{rs}\}$；
- 如果 $last_{ls} < fisrt_{rs}$，则 $len_k = \max\{sucup_{ls} + prelen_{rs}\}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/5nperfw6.png)

其中 $suclen$ 为最长后缀合唱队形：

- $suclen_k = \max\{suclen_{rs}\}$；
- 如果 $len_{rs} = Len(rs)$ 且 $last_{ls} < first_{rs}$，则 $suclen_k = \max\{sucup_{ls} + len_{rs}\}$；
- 如果 $sucdown_{rs} = Len(rs)$ 且 $last_{ls} > first_{rs}$，则 $suclen_k = \max\{suclen_{ls} + sucdown_{rs}\}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/8v3k7hyp.png)

其中 $prelen$ 为最长前缀合唱队形：

- $prelen_k = \max\{prelen_{ls}\}$；
- 如果 $len_{ls} = Len(ls)$ 且 $last_{ls} > first_{rs}$，则 $prelen_k = \max\{len_{ls} + predown_{rs}\}$；
- 如果 $preup_{ls} = Len(ls)$ 且 $last_{ls} < first_{rs}$，则 $prelen_k = \max\{preup_{ls} + prelen_{rs}\}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/x1hxuik8.png)

其中 $predown$ 为最长前缀连续下降序列长度：

- $predown_k = \max\{predown_{ls}\}$；
- 如果 $predown_{ls} = Len(ls)$ 且 $last_{ls} > first_{rs}$，则 $predown_k = \max\{predown_{ls} + predown_{rs}\}$。

其中 $preup$ 为最长前缀连续上升序列长度：

- $preup_k = \max\{preup_{ls}\}$；
- 如果 $preup_{ls} = Len(ls)$ 且 $last_{ls} < first_{rs}$，则 $preup_k = \max\{preup_{ls} + preup_{rs}\}$。

其中 $sucdown$ 为最长后缀连续下降序列长度：

- $sucdown_k = \max\{sucdown_{rs}\}$；
- 如果 $sucdown_{rs} = Len(rs)$ 且 $last_{ls} > first_{rs}$，则 $predown_k = \max\{sucdown_{ls} + sucdown_{rs}\}$。

其中 $sucup$ 为最长后缀连续上升序列长度：

- $sucup_k = \max\{sucup_{rs}\}$；
- 如果 $sucup_{rs} = Len(rs)$ 且 $last_{ls} < first_{rs}$，则 $sucup_k = \max\{sucup_{ls} + sucup_{rs}\}$。

其他操作就是模板了。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

using std::max;

#define N 600010
#define int long long

int n,m;
int a[N];

struct Tree
{
    int l,r;
    int lazy;
    int last,first,len;
    int suclen,prelen;
    int sucdown,sucup,predown,preup;
    void init(int z)
    {
        last = first = z;
        len = suclen = prelen = 1;
        sucdown = sucup = predown = preup = 1;
    }
    void push(int z)
    {
        last += z;
		first += z;
    }
}tr[N << 2];

#define lson k << 1
#define rson k << 1 | 1
#define len(k) (tr[k].r - tr[k].l + 1)

void pushup(int k)
{
    tr[k].last = tr[rson].last;
    tr[k].first = tr[lson].first;
	
	tr[k].len = max(tr[lson].len,tr[rson].len);
	if(tr[lson].last > tr[rson].first)
		tr[k].len = max(tr[k].len,tr[lson].suclen + tr[rson].predown);
	if(tr[lson].last < tr[rson].first)
		tr[k].len = max(tr[k].len,tr[lson].sucup + tr[rson].prelen);

	tr[k].suclen = tr[rson].suclen;
	if(tr[rson].sucdown == len(rson) && tr[lson].last > tr[rson].first)
		tr[k].suclen = max(tr[k].suclen,tr[lson].suclen + tr[rson].sucdown);
	if(tr[rson].len == len(rson) && tr[lson].last < tr[rson].first)
		tr[k].suclen = max(tr[k].suclen,tr[lson].sucup + tr[rson].len);
	
	tr[k].prelen = tr[lson].prelen;
	if(tr[lson].preup == len(lson) && tr[lson].last < tr[rson].first)
		tr[k].prelen = max(tr[k].prelen,tr[lson].preup + tr[rson].prelen);
	if(tr[lson].len == len(lson) && tr[lson].last > tr[rson].first)
		tr[k].prelen = max(tr[k].prelen,tr[lson].len + tr[rson].predown);
	
	tr[k].predown = tr[lson].predown;
	if(tr[lson].predown == len(lson) && tr[lson].last > tr[rson].first)
		tr[k].predown = max(tr[k].predown,tr[lson].predown + tr[rson].predown);

	tr[k].preup = tr[lson].preup;
	if(tr[lson].preup == len(lson) && tr[lson].last < tr[rson].first)
		tr[k].preup = max(tr[k].preup,tr[lson].preup + tr[rson].preup);

	tr[k].sucdown = tr[rson].sucdown;
	if(tr[rson].sucdown == len(rson) && tr[lson].last > tr[rson].first)
		tr[k].sucdown = max(tr[k].sucdown,tr[lson].sucdown + tr[rson].sucdown);

	tr[k].sucup = tr[rson].sucup;
	if(tr[rson].sucup == len(rson) && tr[lson].last < tr[rson].first)
		tr[k].sucup = max(tr[k].sucup,tr[lson].sucup + tr[rson].sucup);

}

void build(int k,int l,int r)
{
	tr[k].l = l,tr[k].r = r;
	tr[k].lazy = 0;
	if(l == r)
	{
		tr[k].init(a[l]);
		return;
	}
	int mid = l + r >> 1;
	build(lson,l,mid);
	build(rson,mid + 1,r);
	pushup(k);
}

void pushdown(int k)
{
	if(tr[k].lazy != 0)
	{
		tr[lson].push(tr[k].lazy);
		tr[lson].lazy += tr[k].lazy;
		tr[rson].push(tr[k].lazy);
		tr[rson].lazy += tr[k].lazy;
		tr[k].lazy = 0;
	}
}

void change(int k,int ql,int qr,int z)
{
	int l = tr[k].l,r = tr[k].r;
	if(ql <= l && r <= qr)
	{
		tr[k].push(z);
		tr[k].lazy += z; 
		return;
	}
	pushdown(k);
	int mid = l + r >> 1;
	if(ql <= mid)
		change(lson,ql,qr,z);
	if(mid < qr)
		change(rson,ql,qr,z);
	pushup(k);
}

signed main()
{
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++)
		scanf("%lld",&a[i]);
	build(1,1,n);
	scanf("%lld",&m);
	for(int t = 1,l,r,z;t <= m;t++)
	{
		scanf("%lld%lld%lld",&l,&r,&z);
		change(1,l,r,z);
		printf("%lld\n",tr[1].len);
	}
	return 0;
}
```

---

## 作者：PPL_ (赞：0)

# 前言

大工程，用时1.5h

舒服~

# 题目

[洛谷](https://www.luogu.com.cn/problem/CF739C)

[CF](http://codeforces.com/contest/739/problem/C)

# 讲解

[更好的阅读体验？](https://www.cnblogs.com/PPLPPL/p/14179882.html)

线段树板题，细节很多。

如果这道[[USACO08FEB]Hotel G(洛谷)](https://www.luogu.com.cn/problem/P2894)没有做过建议做了再来看。

这道题的思路就变得清晰易懂了。

为方便描述和理解，我们把先上升后下降的序列叫做`山峰`。

对于一个区间，我们需要维护以下数据：

- 左端点开始的上升序列长度$ul$。

- 左端点开始的下降序列长度$dl$。

- 左端点开始的山峰长度$udl$。

- 右端点结束的上升序列长度$ur$。(**从左往右**是**单增**的)

- 右端点结束的下降序列长度$dr$。(**从左往右**是**单减**的)

- 右端点结束的山峰长度$udr$。(**从左往右**是**先单增后单减**的)

- 区间山峰最大值$ans$。      

- 区间加的懒标记$lz$。

- 区间左端点值$l$。

- 区间右端点值$r$。

我们发现区间加对一个区间的答案并不影响，所以我们的重难点就在区间合并上。

区间加不多赘述。

$l,r$可以直接由子区间得到。

对于$ans$，我们可以先取子区间$ans$的最大值，然后我们的$ans$更新就只可能是跨区间了，分类讨论即可。

$ul,ur,dl,dr,udl,udr$与$ans$类似，分类讨论即可。

其实合并区间总体上分为两部分：

一是子区间直接更新此区间。

二是跨区间更新。

对于这道题这个更新思路显得尤为重要，不然很容易混乱。

详见代码。

# 代码

```cpp
#define lc (x<<1)
#define rc (x<<1|1)
struct SegmentTree
{
	struct node
	{
		int ul,ur,dl,dr,udl,udr,ans;
		LL lz,l,r;
	}t[MAXN << 2];
	
	void up(int x,int l,int mid,int r)
	{
		//子区间不跨区间，直接更新此区间 
		t[x].l = t[lc].l; t[x].r = t[rc].r;
		t[x].ans = Max(t[lc].ans,t[rc].ans);
		int llen = mid-l+1,rlen = r-mid;//左右区间长度 
		t[x].ul = t[lc].ul; t[x].dl = t[lc].dl;
		t[x].ur = t[rc].ur; t[x].dr = t[rc].dr;
		t[x].udl = t[lc].udl; t[x].udr = t[rc].udr; 
		//分类讨论跨区间更新 
		if(t[lc].r < t[rc].l)
		{
			if(t[lc].ul == llen) t[x].ul += t[rc].ul; 
			if(t[rc].ur == rlen) t[x].ur += t[lc].ur;
			if(t[rc].udr == rlen) t[x].udr += t[lc].ur;
			if(t[lc].ul == llen) t[x].udl = Max(t[x].udl,llen + t[rc].udl);
			t[x].ans = Max(t[x].ans,t[rc].udl + t[lc].ur);
		}
		else if(t[lc].r > t[rc].l)
		{
			if(t[lc].dl == llen) t[x].dl += t[rc].dl;
			if(t[rc].dr == rlen) t[x].dr += t[lc].dr;
			if(t[lc].udl == llen) t[x].udl += t[rc].dl;
			if(t[rc].dr == rlen) t[x].udr = Max(t[x].udr,rlen + t[lc].udr);
			t[x].ans = Max(t[x].ans,t[lc].udr + t[rc].dl);
		}
	}
	
	void down(int x)
	{
		if(!t[x].lz) return;
		t[lc].l += t[x].lz; t[lc].r += t[x].lz; t[lc].lz += t[x].lz;
		t[rc].l += t[x].lz; t[rc].r += t[x].lz; t[rc].lz += t[x].lz;
		t[x].lz = 0;
	}
	
	void Build(int x,int l,int r)
	{
		if(l == r)
		{
			t[x].l = t[x].r = Read();
			t[x].ul = t[x].ur = t[x].dl = t[x].dr = t[x].udl = t[x].udr = 1;
			t[x].ans = 1;
			t[x].lz = 0;
			return;
		}
		int mid = (l+r) >> 1;
		Build(lc,l,mid);
		Build(rc,mid+1,r);
		up(x,l,mid,r);
	}
	
	void Add(int x,int l,int r,int ql,int qr,int val)
	{
		if(ql <= l && r <= qr)
		{
			t[x].l += val; t[x].r += val; t[x].lz += val; 
			return;
		}
		int mid = (l+r) >> 1;
		down(x);
		if(ql <= mid) Add(lc,l,mid,ql,qr,val);
		if(mid+1 <= qr) Add(rc,mid+1,r,ql,qr,val);
		up(x,l,mid,r);
	}
}st;

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n = Read();
	st.Build(1,1,n);
	for(int T = Read(); T ;-- T)
	{
		int l = Read(),r = Read(),val = Read();
		st.Add(1,1,n,l,r,val);
		Put(st.t[1].ans,'\n');
	}
	return 0;
}
```

---

## 作者：eee_hoho (赞：0)

题意：维护区间最大的先上升后下降的子段长度，支持区间加

这个题似乎很熟悉，想必你肯定做过它的简化版——最大上升子序列

那么遇到这样的题我们应该怎么做呢，别着急，我们一步一步来

- 我们肯定是要用线段树维护答案，那么左右儿子怎么合并答案呢，有这么几种情况：

![](https://cdn.luogu.com.cn/upload/pic/72005.png)

>- 前两种情况就是继承左右儿子的$ans$

>- 第三种是左儿子中以右端点结尾的$ans+$右儿子中以左端点开始的最长下降序列长度（左儿子的右端点$>$右儿子的左端点）

>- 第四种是右儿子中以左端点开始的$ans+$左儿子中以右端点结束的最长上升序列长度（左儿子的左端点$<$右儿子的左端点）

- 维护以左右端点开始或结尾的$zans,yans$也是类似的，以$zans$来说

![](https://cdn.luogu.com.cn/upload/pic/72007.png)

>- 第一种情况就是左儿子的$zans$

>- 第二种情况是左儿子的$zans+$右儿子中以左端点开始的最长下降序列长度（左儿子的右端点$>$右儿子的左端点）

>- 第三种情况是左儿子的区间长度$+$右儿子的$zans$（左儿子中以右端点结尾的最长上升序列长度$=$左儿子的区间长度并且左儿子的右端点$<$右儿子的左端点）

- 然后是维护左右端点开始或结束的最长下降或上升的序列长度$zlen,ylen$，以$zlen$来说

![](https://cdn.luogu.com.cn/upload/pic/72011.png)

>- 第一种情况是左儿子的$zlen$
>- 第二种情况是左儿子的$zlen+$右儿子的$zlen$（左儿子的$zlen=$左儿子的区间长度并且左儿子的右端点$>$右儿子的左端点）

然后这道题就做完啦

我们整理一下刚才要维护的东西
- 答案$ans$

- 左端点$z$

- 右端点$y$ 

- 区间长度$len$
 
- 左端点开始的答案$zans$
 
- 左端点开始的最长下降序列长度$zlen$

- 右端点结束的答案$yans$
 
- 右端点结束的最长上升序列长度$ylen$

至于区间加的操作，对于一个子树而言只影响左右端点，所以正常的打标记下放就可以了

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 300000
#define zrt k << 1
#define yrt k << 1 | 1
using namespace std;
int n,m,a[N + 5];
struct node
{
    int ans,za,ya,zl,yl,len;
    long long z,y,tag;
};
struct Seg
{
    node s[N * 4 + 5];
    node upd(node x,node y)
    {
        node k;
        k.len = x.len + y.len;
        k.z = x.z;
        k.y = y.y;
        k.zl = x.zl;
        if (x.zl == x.len && x.y > y.z)
            k.zl += y.zl;
        k.yl = y.yl;
        if (y.yl == y.len && x.y < y.z)
            k.yl += x.yl;
        k.za = x.za;
        if (k.za == x.len && x.y > y.z)
            k.za += y.zl;
        if (x.yl == x.len && x.y < y.z)
            k.za = max(k.za,x.yl + y.za);
        k.ya = y.ya;
        if (k.ya == y.len && x.y < y.z)
            k.ya += x.yl;
        if (y.zl == y.len && x.y > y.z)
            k.ya = max(k.ya,y.zl + x.ya);
        k.ans = max(x.ans,y.ans);
        if (x.y > y.z)
            k.ans = max(k.ans,x.ya + y.zl);
        if (x.y < y.z)
            k.ans = max(k.ans,y.za + x.yl);
        return k;
    }
    void build(int k,int l,int r)
    {
        if (l == r)
        {
            s[k].ans = 1;
            s[k].ya = 1;
            s[k].za = 1;
            s[k].zl = 1;
            s[k].yl = 1;
            s[k].z = (long long)a[l];
            s[k].y = (long long)a[l];
            s[k].len = 1;
            return;
        }
        int mid = l + r >> 1;
        build(zrt,l,mid);
        build(yrt,mid + 1,r);
        s[k] = upd(s[zrt],s[yrt]);
    }
    void jia(int k,int l,int r,long long z)
    {
        s[k].z += z;
        s[k].y += z;
        s[k].tag += z;
    }
    void pushdown(int k,int l,int r,int mid)
    {
        if (!s[k].tag)
            return;
        jia(zrt,l,mid,s[k].tag);
        jia(yrt,mid + 1,r,s[k].tag);
        s[k].tag = 0;
    }
    void add(int k,int l,int r,int x,int y,long long z)
    {
        if (l >= x && r <= y)
        {
            jia(k,l,r,z);
            return;
        }
        int mid = l + r >> 1;
        pushdown(k,l,r,mid);
        if (x > mid)
            add(yrt,mid + 1,r,x,y,z);
        else
            if (y <= mid)
                add(zrt,l,mid,x,y,z);
            else
                add(zrt,l,mid,x,y,z),add(yrt,mid + 1,r,x,y,z);
        s[k] = upd(s[zrt],s[yrt]);
    }
}tree;
int main()
{
    scanf("%d",&n);
    for (int i = 1;i <= n;i++)
        scanf("%d",&a[i]);
    tree.build(1,1,n);
    scanf("%d",&m);
    int l,r;
    long long z;
    for (int i = 1;i <= m;i++)
    {
        scanf("%d%d%lld",&l,&r,&z);
        tree.add(1,1,n,l,r,z);
        printf("%d\n",tree.s[1].ans);
    }
    return 0;
}
```

---

