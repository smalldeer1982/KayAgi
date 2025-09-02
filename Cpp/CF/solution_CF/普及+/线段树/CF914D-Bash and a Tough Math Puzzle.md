# Bash and a Tough Math Puzzle

## 题目描述

Bash likes playing with arrays. He has an array $ a_{1},a_{2},...\ a_{n} $ of $ n $ integers. He likes to guess the greatest common divisor (gcd) of different segments of the array. Of course, sometimes the guess is not correct. However, Bash will be satisfied if his guess is almost correct.

Suppose he guesses that the gcd of the elements in the range $ [l,r] $ of $ a $ is $ x $ . He considers the guess to be almost correct if he can change at most one element in the segment such that the gcd of the segment is $ x $ after making the change. Note that when he guesses, he doesn't actually change the array — he just wonders if the gcd of the segment can be made $ x $ . Apart from this, he also sometimes makes changes to the array itself.

Since he can't figure it out himself, Bash wants you to tell him which of his guesses are almost correct. Formally, you have to process $ q $ queries of one of the following forms:

- $ 1lrx $ — Bash guesses that the gcd of the range $ [l,r] $ is $ x $ . Report if this guess is almost correct.
- $ 2iy $ — Bash sets $ a_{i} $ to $ y $ .

Note: The array is $ 1 $ -indexed.

## 说明/提示

In the first sample, the array initially is $ {2,6,3} $ .

For query $ 1 $ , the first two numbers already have their gcd as $ 2 $ .

For query $ 2 $ , we can achieve a gcd of $ 3 $ by changing the first element of the array to $ 3 $ . Note that the changes made during queries of type $ 1 $ are temporary and do not get reflected in the array.

After query $ 3 $ , the array is now $ {9,6,3} $ .

 For query $ 4 $ , no matter which element you change, you cannot get the gcd of the range to be $ 2 $ .

## 样例 #1

### 输入

```
3
2 6 3
4
1 1 2 2
1 1 3 3
2 1 9
1 1 3 2
```

### 输出

```
YES
YES
NO
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
6
1 1 4 2
2 3 6
1 1 4 2
1 1 5 2
2 5 10
1 1 5 2
```

### 输出

```
NO
YES
NO
YES
```

# 题解

## 作者：Siyuan (赞：17)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io)

---

> 题目链接：[Codeforces 914D](https://codeforces.com/contest/914/problem/D)

给定一个长度为 $n$ 的数列 $a_i$ 和 $q$ 次操作，有两种操作：

- $1,l,r,x$：询问是否可以改动至多一个数使得下标在 $[l,r]$ 内的数的的 $\gcd$ 为 $x$。如果可以则输出 $\texttt{YES}$ 否则输出 $\texttt{NO}$。
- $2,i,y$：将 $a_i$ 修改为 $y$。

数据范围：$1\leqslant n\leqslant 5\times 10^5$，$1\leqslant q\leqslant 4\times 10^5$，$1\leqslant a_i\leqslant 10^9$

------

## Solution

这是一道线段树裸题 QAQ

我们只需要直接查询区间内不能整除 $x$ 的数的数量 $cnt$。

- 如果 $cnt>1$，那么不可能通过修改至多 $1$ 个数达到要求。
- 如果 $cnt=1$，那么直接将那个数修改成 $x$ 即可。
- 如果 $cnt=0$，那么任意选择一个数修改成 $x$ 即可。

**时间复杂度**：$O(n\log^2 n)$

------

## Code

```cpp
#include <cstdio>
#define lson rt<<1
#define rson rt<<1|1

const int N=5e5+5;
int n,q,cnt,seg[N<<2];

int gcd(int x,int y) {
    return y?gcd(y,x%y):x;
}
void pushup(int rt) {
    seg[rt]=gcd(seg[lson],seg[rson]);
}
void build(int rt,int l,int r) {
    if(l==r) {
        scanf("%d",&seg[rt]);
        return;
    }
    int mid=(l+r)>>1;
    build(lson,l,mid);
    build(rson,mid+1,r);
    pushup(rt);
}
void modify(int x,int rt,int l,int r,int val) {
    if(l==r) {
        seg[rt]=val;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) modify(x,lson,l,mid,val);
    else modify(x,rson,mid+1,r,val);
    pushup(rt);
}
void query(int x,int y,int rt,int l,int r,int d) {
    if(cnt>1) return;
    if(l==r) {
        ++cnt;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid&&seg[lson]%d) query(x,y,lson,l,mid,d);
    if(mid<y&&seg[rson]%d) query(x,y,rson,mid+1,r,d);
}
int main() {
    scanf("%d",&n);
    build(1,1,n);
    for(scanf("%d",&q);q--;) {
        int opt;
        scanf("%d",&opt);
        if(opt==1) {
            int l,r,x;
            scanf("%d%d%d",&l,&r,&x);
            cnt=0,query(l,r,1,1,n,x);
            puts(cnt>1?"NO":"YES");
        } else {
            int x,k;
            scanf("%d%d",&x,&k);
            modify(x,1,1,n,k);
        }
    }
    return 0;
}
```



---

## 作者：fanypcd (赞：5)

[CF914D Bash and a Tough Math Puzzle](https://www.luogu.com.cn/problem/CF914D)

线段树的小 trick。

用线段树维护区间的最大公约数。

对于操作 2 直接暴力修改就好了。

对于操作 1，首先定义一个全局的答案 $ans$。

查询的任意时刻如果发现 $ans \geq 2$ 立马返回。

我们发现操作 1 的本质就是查询一个区间内不能被 x 整除的数的个数是否大于等于 2。

但是区间查询时如果当前节点被完全覆盖也不能直接返回，可以想到如下的 trick:

- 如果区间 gcd 能被 x 整除，直接返回（显然所有数都能被 x 整除）。
- 如果区间左右两子区间的 gcd 都不能被 x 整除，$ans \to ans+2$，显然至少有 2 个值不合法。
- 否则就是区间的一半部分有可能不合法，递归处理即可。
- 如果当前节点表示的区间长度为 1，判断并返回。

复杂度 $O(n \log n \log a_i)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define N 500005
int gcd(int a, int b)
{
	if(!b)
	{
		return a;
	}
	return gcd(b, a % b);
}
int num[N], ans;
struct node
{
	int l, r, gd;
};
class segment_tree
{
	private:
	node tree[N << 2];
	inline void pushup(int root)
	{
		tree[root].gd = gcd(tree[root << 1].gd, tree[root << 1 | 1].gd);
		return;
	}
	public:
	void build(int root, int l, int r)
	{
		tree[root].l = l;
		tree[root].r = r;
		if(l == r)
		{
			tree[root].gd = num[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(root << 1, l, mid);
		build(root << 1 | 1, mid + 1, r);
		pushup(root);
		return;
	}
	void update(int root, int pos, int v)
	{
		if(tree[root].l == tree[root].r)
		{
			tree[root].gd = v;
			return;
		}
		int mid = (tree[root].l + tree[root].r) >> 1;
		if(pos <= mid)
		{
			update(root << 1, pos, v);
		}
		else
		{
			update(root << 1 | 1, pos, v);
		}
		pushup(root);
	}
	void query(int root, int L, int R, int x)
	{
		if(ans >= 2)
		{
			return;
		}
		if(tree[root].l == tree[root].r)
		{
			ans += (tree[root].gd % x != 0);
			return;
		}
		if(L <= tree[root].l && tree[root].r <= R)
		{
			if(tree[root].gd % x == 0)
			{
				return;
			}
			int state1 = tree[root << 1].gd % x, state2 = tree[root << 1 | 1].gd % x;
			if(state1 && state2)
			{
				ans += 2;
				return;
			}
			if(state1)
			{
				query(root << 1, L, R, x);
			}
			else
			{
				query(root << 1 | 1, L, R, x);
			}
			return;
		}
		int mid = (tree[root].l + tree[root].r) >> 1;
		if(L <= mid && tree[root << 1].gd % x)
		{
			query(root << 1, L, R, x);
		}
		if(mid < R && tree[root << 1 | 1].gd % x)
		{
			query(root << 1 | 1, L, R, x);
		}
		return;
	}
};
segment_tree T;
int n, q;
signed main()
{
	read(n);
	for(int i = 1; i <= n; i++)
	{
		read(num[i]);
	}
	T.build(1, 1, n);
	int opt, l, r, x;
	read(q);
	while(q--)
	{
		read(opt);
		if(opt == 1)
		{
			read(l), read(r), read(x);
			ans = 0;
			T.query(1, l, r, x);
			if(ans <= 1)
			{
				printf("YES\n");
			}
			else
			{
				printf("NO\n");
			}
		}
		else
		{
			read(l), read(x);
			T.update(1, l, x);
		}
	}
	return 0;
}
```

---

## 作者：Ba_creeper (赞：3)

#### 解题思路

对于操作 $1$，关键是如何查找 $[l,r]$ 中不能整除 $x$ 的个数。

可以想到用线段树暴力优化求解：

用线段树维护区间 $\gcd$，**如果一段区间的 $\gcd$ 都能整除 $x$，那么这段区间的所有数也都能整除 $x$**，那么我们可以利用这个特点，节省大部分递归时间。

每次查询，用 $cnt$ 表示区间中不能整除 $x$ 的个数。

- 如果 $cnt=0$，那么不需要修改即可满足题意，输出为 `YES`。
- 如果 $cnt=1$，说明只需要修改一个数即可满足题意，输出为 `YES`。
- 如果 $cnt=2$，说明至少需要修改两个数才能满足题意，不符合条件，输出为 `NO`。

查询时还需要一点小剪枝，即查询过程中只要 $cnt>1$ 时，立即停止查询，输出 `NO`。

操作 $2$ 为线段树最基本的单点修改。

#### 核心代码
```cpp
/* 查询 */
void check(node *now, ll l, ll r, ll k)
{
    if (l <= now->L && now->R <= r + 1 && now->gcd % k == 0) 
        return; //优化线段树的查询过程

    if (l <= now->L && now->R <= r + 1 && now->L + 1 == now->R){
        if (now->gcd % k != 0){
            cnt++; 
            if (cnt >= 2)
                return; //剪枝
        }
        return;
    }

    ll mid = (now->L + now->R) >> 1;
    if (l < mid)
        check(now->lc, l, r, k);
    if (r >= mid)
        check(now->rc, l, r, k);
}

/* 单点修改 + 维护gcd */
void add(node *now,ll x,ll k)
{
    if(now->L + 1 == now->R)
        now->gcd = k; //修改
    
    else
    {
        ll mid=(now->L + now->R)>>1;
        if(x<mid)
            add(now->lc,x,k);
        if(x>=mid)
            add(now->rc,x,k);
        now->gcd = gcd(now->lc->gcd,now->rc->gcd); //维护gcd
    }
}

/* 主函数 */
int main()
{
    n=read();
    node *root;
    root=new node;
    build(root,1,n+1);

    for(int i=1;i<=n;++i){
        ll x=read();
        add(root,i,x);
    }
    m=read();
    for(int i=1;i<=m;++i){
        ll opt=read();
        if(opt==1){
            ll l=read(),r=read(),k=read();
            cnt=0; //勿忘初始化
            check(root,l,r,k);
            if(cnt>1)
            puts("NO");
            else puts("YES");
        }
        else{
            ll x=read(),k=read();
            add(root,x,k);
        }
    }
    return 0;
}
```

#### 推荐题目
本题是关于线段树暴力优化的问题，还有两道题与这道题思想类似：

[CF438D The Child and Sequence](https://www.luogu.com.cn/problem/CF438D)；

[P4145 上帝造题的七分钟2 / 花神游历各国](https://www.luogu.com.cn/problem/P4145)。

---

## 作者：zhanghzqwq (赞：3)

### [题目传送门](https://www.luogu.com.cn/problem/CF914D)

最近我一直在搞这种线段树暴力修改查询加上优化的题，例如[花神游历各国](https://www.luogu.com.cn/problem/P4145)。

### 一.题意

给你一个序列，长度不超过5e5，问能否修改一个数使一段区间的gcd等于x，支持单点修改。

### 二.思路

一看到题，这啥啊，细想一下发现是道模板题。

我们的目标是能否修改一个数使一段区间的gcd等于x，这个东西就是在问是否只有一个数或没有数不能被x整除。

**证明**（~~这**还用证？~~）：

设cnt为区间内不能被x整除的数的个数。

当cnt==0时：随便把一个数修改为x。

当cnt==1时：把这个数修改为x。

当cnt>1时：因为只能修改一个数，所以不能使gcd==x。

### 三.代码实现

我们用一棵线段树维护区间gcd，递归到子节点的时候如果子节点不能被x整除，cnt就++；

注意：如果只这么写的话，复杂度会炸的。

我们想一想，**如果一段区间的gcd都是x的倍数的话，那么这段区间的所有数都能被x整除。** 这样就不用继续递归了。

于是，我们就能节省大部分递归时间，不过还是会炸（亲测T#68）

所以我们在递归的时候只要cnt>1了，就不做递归了，直接return就行了。

单点修改不用讲吧，应该都会。

代码：

```cpp
#include<cstdio>
using namespace std;
const int MAXN=5e5+5;
int n,m;
int a[MAXN];
int cnt;
int gcd(int x,int y){//辗转相除求gcd
	if(y==0) return x;
	return gcd(y,x%y);
}
int tree[MAXN<<2];
inline int lc(int p){return p<<1;}
inline int rc(int p){return p<<1|1;}
void pushUp(int p){//区间合并
	tree[p]=gcd(tree[lc(p)],tree[rc(p)]);
}
void build(int p,int l,int r){//建树
	if(l==r){
		tree[p]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(lc(p),l,mid);
	build(rc(p),mid+1,r);
	pushUp(p);
}
void update(int p,int l,int r,int x,int d){//单点修改
	if(l==r){
		tree[p]=d;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid){
		update(lc(p),l,mid,x,d);
	}else{
		update(rc(p),mid+1,r,x,d);
	}
	pushUp(p);
}
void query(int p,int l,int r,int ql,int qr,int x){
	if(cnt>1||tree[p]%x==0){//这里是优化的关键
		return;
	}
	if(l==r){//否则cnt++
		cnt++;
		return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid){
		query(lc(p),l,mid,ql,qr,x);
	}
	if(mid<qr){
		query(rc(p),mid+1,r,ql,qr,x);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	build(1,1,n);
	scanf("%d",&m);
	while(m--){
		int op;
		scanf("%d",&op);
		if(op==1){
			int ql,qr,x;
			scanf("%d%d%d",&ql,&qr,&x);
			cnt=0;//注意初始化
			query(1,1,n,ql,qr,x);
			if(cnt>1){
				printf("NO\n");
			}else{
				printf("YES\n");
			}
		}else{
			int x,d;
			scanf("%d%d",&x,&d);
			update(1,1,n,x,d);
		}
	}
	return 0;//完结撒花
} 
```

这道题做完可以去做[CF438D](https://www.luogu.com.cn/problem/CF438D)，也是暴力优化线段树的题qwq

---

## 作者：xfrvq (赞：2)

## 不太难的线段树题

[原题链接](https://www.luogu.com.cn/problem/CF914D)

[博客食用](https://www.luogu.com.cn/blog/368107/solution-cf914d)

### 思路

`push_up` 用$\gcd$ 实现 

建树时把每个叶子节点的$val$ 赋值为读入初始数组的对应项，**树的结构体不用$l,r$**

单点修改和查询把当前$L,R$ 往下传

对于每次查询，统计无法整除$x$ 的数的个数$cnt$ 

$cnt = 1$ 则修改那个无法整除的数为$x$ ，输出 `YES`

$cnt = 0$ 则随便选一个数改为$x$ ，输出 `YES`

$cnt \ge 2$ 找不到修改方案，输出 `NO`

**查询时的细节：**

当$cnt \ge 2$ 时退出递归，当当前节点的值（它所有子孙的最大公因数）是$x$的倍数时也退出递归

否则会TLE

### 代码

说的那么多了，代码应该不难写了

如下：

```cpp
#include<stdio.h>
inline int readint(){
	register int x = 0,f = 0,c = getchar();
	for(;c < '0' || c > '9';c = getchar()) f = c == '-' ? -1 : 0;
	for(;c >= '0' && c <= '9';c = getchar()) x = x * 10 + (c ^ 48);
	return x ^ f;
}
#define Re readint()
const int maxn = 500001;
int n,m,a[maxn];
#define lc(i) ((i) << 1)
#define rc(i) ((i) << 1 | 1)
struct node{int val;} T[2000001];
int cnt;
int gcd(int a,int b){
	return b == 0 ? a : gcd(b,a % b);
}
void push_up(int i){
	T[i].val = gcd(T[lc(i)].val,T[rc(i)].val);
}
void build(int L,int R,int i){
	if(L == R){
		T[i].val = a[L];
		return;
	}
	int mid = L + R >> 1;
	build(L,mid,lc(i));
	build(mid + 1,R,rc(i));
	push_up(i);
}
void update(int p,int v,int L,int R,int i){
	if(L == R){
		T[i].val = v;
		return;
	}
	int mid = L + R >> 1;
	if(p <= mid) update(p,v,L,mid,lc(i));
	else update(p,v,mid + 1,R,rc(i));
	push_up(i);
}
void query(int L,int R,int l,int r,int i,int x){
	if(cnt > 1) return;
   if(T[i].val % x == 0) return;
   if(L == R){
       ++cnt;
       return;
   }
	int mid = L + R >> 1;
	if(l <= mid) query(L,mid,l,r,lc(i),x);
	if(r > mid) query(mid + 1,R,l,r,rc(i),x);
}
int main(){
	n = Re;
	for(int i = 1;i <= n;++i) a[i] = Re;
	build(1,n,1);
	m = Re;
	for(int i = 1;i <= m;++i){
		int p = Re;
		if(p == 1){
			cnt = 0;
			int l = Re,r = Re,x = Re;
			query(1,n,l,r,1,x);
			printf("%s\n",cnt < 2 ? "YES" : "NO");
		} else {
			int i = Re,y = Re;
			update(i,y,1,n,1);
		}
	}
	return 0;
}
```

---

## 作者：raincity (赞：2)

## 题意简述

给定 $a_1,a_2, \ldots a_n$，$m$ 次操作，操作为单点修改或者询问是否可以在 $a_{l},a_{l+1},\ldots a_r$ 中改动至多一个数使得 $gcd(a_l,a_{l+1},\ldots a_r)=x$。

## 分析

首先需要知道什么情况下可以在 $a_{l},a_{l+1},\ldots a_r$ 中改动至多一个数使得 $gcd(a_l,a_{l+1},\ldots a_r)=x$。

只能改动至多一个数，那么设 $a_{l},a_{l+1},\ldots a_r$ 中有 $cnt$ 个数不是 $x$ 的倍数，那么显然有：

1. 当 $cnt=0$ 时，任意改一个数为 $x$ 即可。
2. 当 $cnt=1$ 时，把非 $x$ 的倍数改为 $x$。
3. 当 $cnt > 2$ 时，不可能成功。

那么可以在 $a_{l},a_{l+1},\ldots a_r$ 中改动至多一个数使得 $gcd(a_l,a_{l+1},\ldots a_r)=x$ 等价于在 $a_{l},a_{l+1},\ldots a_r$ 中至多有 1 个数不是 $x$ 的倍数。需要支持快速查询在一个区间内是否有至少 2 个数是 $x$ 的倍数、单点修改。

一看就知道树状数组做不了，所以考虑线段树（暴论）。

可以在每一个节点记录区间 $gcd$，如果 $x|gcd$ 就直接返回。看起来十分暴力，但是可以 AC。具体的时间复杂度在文末分析。

## 代码

显然不会把 $AC$ 代码直接放出来，学过线段树的都知道错在哪里了（保证错在全局变量），防无脑 ctj。

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 5e5 + 5;
int n, m, cnt, gcd[N], a[N];

int __gcd(int x, int y) {
	int res = 1;
	while (x > 1 && y > 1) {
		while (!(x & 1) && !(y & 1)) x >>= 1, y >>= 1, res <<= 1;
		while (!(x & 1)) x >>= 1;
		while (!(y & 1)) y >>= 1;
		if (x ^ y) {
			if (x > y)
				x -= y;
			else
				y -= x;
		}
		else
			return res * x;
	}
	return res;
}

#define ls k << 1
#define rs k << 1 | 1
#define pushup() gcd[k] = __gcd(gcd[ls], gcd[rs])
#define mid ((l + r) >> 1)

void modify(int k, int l, int r, int pos, int val) {
	if (l == r) {
		gcd[k] = val;
		return;
	}
	if (pos <= mid)
		modify(ls, l, mid, pos, val);
	else
		modify(rs, mid + 1, r, pos, val);
	pushup();
}

void query(int k, int l, int r, int ql, int qr, int val) {
	if (l == r) {
		cnt++;
		return;
	}
	if (ql <= mid && cnt <= 1 && gcd[ls] % val)
		query(ls, l, mid, ql, qr, val);
	if (qr > mid && cnt <= 1 && gcd[rs] % val)
		query(rs, mid + 1, r, ql, qr, val);
}

void build(int k, int l, int r) {
	if (l == r) {
		gcd[k] = a[l];
		return;
	}
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushup();
}

char bufin[1 << 21], *p1, *p2, bufout[N << 2];
int tot;

inline char gc() {
	if (p1 == p2) {
		p1 = bufin, p2 = p1 + fread(bufin, 1, 1 << 21, stdin);
		if (p1 == p2)
			return EOF;
	}
	return *p1++;
}

inline void read(int &ret) {
	char ch = gc();
	ret = 0;
	while (ch < '0' || ch > '9') ch = gc();
	while (ch >= '0' && ch <= '9') ret = ret * 10 + ch - '0', ch = gc();
}

inline void write(bool op) {
    if (op)
        bufout[tot++] = 'Y', bufout[tot++] = 'E', bufout[tot++] = 'S';
    else
        bufout[tot++] = 'N', bufout[tot++] = 'O';
    bufout[tot++] = '\n';
}

inline void flush() { fwrite(bufout, 1, tot, stdout); }  

int main() {
	read(n);
	for (register int i = 1; i <= n; i++) read(a[i]);
	build(1, 1, n);
	read(m);
	for (register int T = 1; T <= m; T++) {
		int op, x, y, z;
		read(op), read(x), read(y);
		if (op == 1) {
			read(z);
			cnt = 0;
			query(1, 1, n, x, y, z);
			write(cnt <= 1);
		}
		else
			modify(1, 1, n, x, y);
	}
	flush();
	return 0;
}
```

## 时间复杂度
`if (ql <= mid && cnt <= 1 && gcd[ls] % val)` 和 `if (qr > mid && cnt <= 1 && gcd[rs] % val)` 是那个 $gcd$ 优化。

首先分析查询的时间复杂度。

有了 `gcd[ls] % val` 和 `gcd[rs] % val` 的判断，我们可以保证每一个访问到的线段树节点都管辖了至少一个不是 $val$ 的倍数的数；有了 `cnt <= 1` 的判断，我们可以保证访问到的所有不是 $val$ 的倍数的数都是前 2 个之一。单次时间 $O(\log n)$。

然后分析修改复杂度。

修改了 $\log n$ 个节点，时间为 $gcd$ 时间乘以 $\log n$。$gcd$ 不超过 $\log a$，单次时间不超过 $\log n \log a$。

总时间复杂度不超过 $O(m\log n\log a)$。实际测试更加优秀，大概是 $O(m \log n)$ 带上一个 1 至 2 的常数。

#### THE END

---

## 作者：PrincessYR✨～ (赞：2)

这是一道线段树的模板题，外加找最大公约数。

先来讲一下线段树哦：

1. 建树：

先来看一下线段树长啥样

![](https://bkimg.cdn.bcebos.com/pic/bd3eb13533fa828bcb5fe85ffe1f4134970a5a09?x-bce-process=image/watermark,g_7,image_d2F0ZXIvYmFpa2U5Mg==,xp_5,yp_5)

（注：图片来自百度百科）

最下面一层是我们要读入的数组a[i]。

我们从顶端开始建树，根据二叉树的性质我们可以知道一棵树的左儿子的序号为父亲的序号乘二，右儿子为乘二加一。

我们一直往下递推，知道左端点等于右端点，及一个区间只包含一个数。及搜到最后一层，我们便将a数组的只赋给线段树，当回到父节点是在根据需要判断。

例如这道题要求最小值，我们使父亲节点取字节点的最小值（如果求和，则将子节点的值加起来）。

建树代码：

```
void build(int k,int l,int r)//k为结点编号，l为区间的左端，r为右端
{
	lazy[k]=0;
	if(l==r)
	{
		sum[k]=a[l];
		return ;
	}
	int mid=(l+r)/2;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	sum[k]=min(sum[k*2],sum[k*2+1]);
}
```

如果求和：

我们只需要在最开始时将


```
sum[k]=min(sum[k*2],sum[k*2+1]);
```

中的等式右边改为自己想要的即可

在这道题中只让我们求最大公约数，所以，我们sum就存最大公约数，具体讲解在下方。

2. 加减标记：

一般来说加减就一直搜，将所有点都改一遍。然而这样时间复杂度十分高，十分容易超时。

那么我们就引入了懒惰标记，lazy。

lazy就是将我们要更改的只存储起来，不向下传，等到什么时候要求这个区间的值时，再将值更改。

代码：

```
void pushdown(int k)
{
	lazy[k*2]+=lazy[k];//将lazy传给左儿子
	lazy[k*2+1]+=lazy[k];//将lazy传给右儿子
	sum[k*2]+=lazy[k];//左儿子加上lazy
	sum[k*2+1]+=lazy[k];//右儿子加上lazy
	lazy[k]=0;//将父亲节点的lazy清零
}


void gx(int L,int R,int e,int l,int r,int k)
{
	if(L<=l&&R>=r)//如果当前查询的区间完全包含在内
	{
		lazy[k]+=e;//lazy记录
		sum[k]+=e;//当前节点加e
		return ; 
	}
	pushdown(k);//将lazy传给子节点
	int mid=(l+r)/2;
	if(L<=mid)//如果左节点有要查询的值
	{
		gx(L,R,e,l,mid,k*2);//查询左边
	}
	if(mid<R)//如果右节点有要查询的值
	{
		gx(L,R,e,mid+1,r,k*2+1);//查询右边的值
	}
	sum[k]=min(sum[k*2],sum[k*2+1]);
}
```
2. 最小值查询：
```
int qh(long k,int l,int r,int L,int R)//注意，本代码中sum求的是最小值
{
	if(L<=l&&R>=r)//如果包含在内，直接返回最小值
	{
		return sum[k];
	}
	else 
	{
		pushdown(k);//更新子节点，将lazy下传
		long long re=2147483647485;
		int mid=(l+r)/2;
		if(L<=mid)//如果在左半只
		re=min(re,qh(k*2,l,mid,L,R));
		if(R>mid)//如果在右半只
		re=min(re,qh(k*2+1,mid+1,r,L,R));
		return re;
	}
}
```

3. 求和求和查询：

```
int query(int ls,int rs,int l,int r,int p)
{
	if(rs<l||r<ls)
	{
		return 0;
	}
	if(ls<=l&&r<=rs) 
	{
		return sum[p];
	}
	pushdown(p,l,r);
	int mid=(l+r)/2;
	return query(ls,rs,l,mid,p*2)+query(ls,rs,mid+1,r,p*2+1);
}
```


最后来看一看这道题：

>如果我们可以在数列[l,r]位置中改动至多一个数使得它们的最大公约数是x，那么这个猜测就被认为是接近正确的(注意我们不需要在数列中进行实际的改动)。

题目说，我们可以改动一个数，那么我们来想想，我们该一个数，那么肯定是将这个数改为其他所有数的最大公约数，因为这样，我们才能使尽量少改数。

那么也就是说，如果只有其中的一个数不符合，那么我们就只改它一个就可以了，如果多于一个就需要输出NO。

那么我们就可以求在搜索过程中找有几个数不能被整除，如果大于一，说名我们需要改不知一个数，才能是x为其最大公约数。如果小于等于一，则说明我只需要改一个数或者不改，就能是使大公约数为x。

下面上代码：

```
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int n,m,a[500005],sum[500005<<2];
int q,b,c,d,tot;
int zd(int x,int y) //求最大公约数
{
    return y?zd(y,x%y):x;
}
void pushup(int k)//将父亲节点的sum转化为子节点的最大公约数
{
	sum[k]=zd(sum[k<<1],sum[k<<1|1]);
}
void build(int k,int l,int r)//建树
{
	if(l==r)
	{
		sum[k]=a[l];
		return ;
	}
	int m=(l+r)>>1;
	build(k<<1,l,m);
	build(k<<1|1,m+1,r);
	pushup(k);
}
void jia(int b,int c,int l,int r,int k)//节点加和
{
	if(l==r&&r==b)如果搜到b则将值更改为c
	{
		sum[k]=c;
		return ;
	}
	int m=(l+r)>>1;
	if(b<=m)//如果在左半只，搜索左半只
	{
		jia(b,c,l,m,k<<1);
	}
	else//如果在右半只，搜索右半只
	{
		jia(b,c,m+1,r,k<<1|1);
	}
	pushup(k);//更新父节点sum
}
void pd(int b,int c,int d,int l,int r,int k)
{
	if(tot>1) return ;//一个小小的一优化，否则会TLE
	if(l==r) 
	{
		tot++;
		return ;
	}
	int m=(l+r)>>1;
	if(b<=m&&sum[k<<1]%d!=0)//如果有无法整除的数，也就是但前最大公约数不符合，就继续往下搜索，判断需要改几个
	{
		pd(b,c,d,l,m,k<<1);
	}
	if(c>m&&sum[k<<1|1]%d!=0)
	{
		pd(b,c,d,m+1,r,k<<1|1);
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	build(1,1,n);
	m=read();
	for(int i=1;i<=m;i++)
	{
		q=read();
		if(q==2)
		{
			b=read();c=read();
			jia(b,c,1,n,1);
		}
		else
		{
			b=read();c=read();d=read();
			tot=0;
			pd(b,c,d,1,n,1);
			if(tot>1)
			puts("NO");
			else puts("YES");
		}
	}
	return 0;
 } 
```


---

## 作者：Great_Influence (赞：1)

线段树裸题。

题目要求：查询一段区间，给定x，问是否能够通过修改区间内一个数，使得全区间$\gcd =x$。支持单点修改。

直接查询区间内不能整除x的数数量是否大于1即可。如果大于1，则不可能通过只修改1个数达到要求。如果等于1，直接将那个数修改成x即可。如果没有，则任意修改一个数使之变成x即可。

使用线段树维护，时间复杂度$O(q\log _2n)$

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline void read(int &x)
{
    int s=0,f=1;char k=getchar();
    while(!isdigit(k)&&(k^'-'))k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}
inline void file()
{
	#ifndef ONLINE_JUDGE
		freopen("h.in","r",stdin);
		freopen("h.out","w",stdout);
	#endif
}
const int MAXN=5e5+7;
static int n,p[MAXN<<2];
inline int gcd(int a,int b)
{
	if(a<b)swap(a,b);
	while(b)swap(a,b),b%=a;
	return a;
}
inline void pushup(int h,int l,int r){p[h]=gcd(p[h<<1],p[h<<1|1]);}
void make_tree(int h,int l,int r)
{
	if(l==r){read(p[h]);return;}
	int mid=(l+r)>>1;
	make_tree(h<<1,l,mid);
	make_tree(h<<1|1,mid+1,r);
	pushup(h,l,r);
}
short query(int h,int l,int r,int x,int y,int z)
{
	if(p[h]%z==0)return 1;
	if(l==r)return 2;
	int mid=(l+r)>>1;
	if(x<=mid)
	{
		short ans=query(h<<1,l,mid,x,y,z);
		if(!ans)return 0;
		if(ans==1)return y>mid?query(h<<1|1,mid+1,r,x,y,z):1;
		return y>mid?(query(h<<1|1,mid+1,r,x,y,z)==1?2:0):2;
	}
	if(y>mid)return query(h<<1|1,mid+1,r,x,y,z);
}
void modify(int h,int l,int r,int x,int y)
{
	if(l==r){p[h]=y;return;}
	static int mid;mid=(l+r)>>1;
	if(x<=mid)modify(h<<1,l,mid,x,y);
	else modify(h<<1|1,mid+1,r,x,y);
	pushup(h,l,r);
}
inline void init()
{
	read(n);
	make_tree(1,1,n);
}
static int m;
inline void solve()
{
	static int opt,l,r,x;
	read(m);
	Rep(i,1,m)
	{
		read(opt);read(l);read(r);
		if(opt==1)
		{
			read(x);
			printf("%s\n",!query(1,1,n,l,r,x)?"NO":"YES");
		}
		else modify(1,1,n,l,r);
	}
}
int main()
{
	file();
	init();
	solve();
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：1)

这是一道几乎为模板的线段树裸题。题目要求的是单点更新，区间查询。

因为题目求的为 $\gcd$，所以线段树合并的时候肯定要写成 `tree[cur] = gcd (tree[cur << 1],tree[cur << 1 | 1])`，至于如何写 `gcd (int x,int y) ` 函数，在此就不赘述。

首先讲区间查询。**至多**修改一个数，若能使其满足题意则输出 `YES`，否则为 `NO`。即修改的数为 $0$ 或 $1$ 时为 `YES`，其余情况均为 `NO`。和普通线段树的查询差不多，不过需要优化的有两个细节。一是当需要修改的数已经超过 $1$ 时，即可停止程序，因为答案此时一定为 `NO`；二是若整段的 $\gcd$ 已经为 $x$ 的倍数，也就是说至少把一个数修改为 $x$ 后就会满足题意，故可以停止程序之间输出 `NO`。

其次是单点修改，十分简单，几乎和模板的修改没有区别。唯一要注意的是在修改后，线段树的合并方式为 `tree[cur] = gcd (tree[cur << 1],tree[cur << 1 | 1])`，不要与 `tree[cur] = tree[cur << 1] + tree[cur << 1 | 1]` 混淆。

最后给一个完整代码：

```cpp

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 5e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,m,cnt,a[MAX],tree[MAX << 2];
int gcd (int x,int y);
void build (int cur,int l,int r);
void query (int cur,int l,int r,int x,int y,int v);
void modify (int cur,int l,int r,int x,int v);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();
	for (int i = 1;i <= n;++i) a[i] = read ();
	build (1,1,n);
	m = read ();
	for (int i = 1;i <= m;++i)
	{
		int ty = read ();
		if (ty == 1)
		{
			int l = read (),r = read (),x = read ();
			cnt = 0;
			query (1,1,n,l,r,x);
			if (cnt > 1) printf ("NO\n");//需要修改的大于 1 则无法完成
			else printf ("YES\n");
		}
		else 
		{
			int x = read (),v = read ();
			modify (1,1,n,x,v);
		}
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
int gcd (int x,int y)//辗转相除
{
	if (x < y) swap (x,y);//确定大小
	return (y == 0) ? x : gcd (y,x % y);
}
void build (int cur,int l,int r)
{
	if (l == r)
	{
		tree[cur] = a[l];
		return ;
	}
	int mid = (l + r) >> 1;
	build (cur << 1,l,mid);
	build (cur << 1 | 1,mid + 1,r);
	tree[cur] = gcd (tree[cur << 1],tree[cur << 1 | 1]);
}
void query (int cur,int l,int r,int x,int y,int v)
{
	if (cnt > 1 || tree[cur] % v == 0) return ;//优化程序的地方
	if (l == r)
	{
		++cnt;//需要改动的数的个数 + 1
		return ;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) query (cur << 1,l,mid,x,y,v);
	if (y > mid) query (cur << 1 | 1,mid + 1,r,x,y,v);
}
void modify (int cur,int l,int r,int x,int v)
{
	if (l == r && l == x)
	{
		tree[cur] = v;//单点修改
		return ;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) modify (cur << 1,l,mid,x,v);
	else modify (cur << 1 | 1,mid + 1,r,x,v);
	tree[cur] = gcd (tree[cur << 1],tree[cur << 1 | 1]);//合并方式要注意
}
```

---

## 作者：phmaprostrate (赞：0)

## 分析
题意~~显然~~，直接分析，首先关于 $gcd()$ 是可以进行区间维护的，于是我们可以用线段树维护整个区间的 $gcd()$ .
然后，对于一个 $x$ 因为要求只能修改一个，转化一下，就是区间 $l$ 到 $r$ 只能有一个数不是 $x$ 的倍数。

于是，我们可以在把线段树的区间操作进行更改。

```cpp
void query(int u,int l,int r,int d){
	if(cnt > 1)return;
	if(tr[u].gcd % d == 0) {return;}
	if(tr[u].l == tr[u].r) {cnt ++;return;}
	int mid = tr[u].l + tr[u].r >> 1;
	if(l <= mid) query(u << 1,l,r,d);
	if(r > mid)query(u << 1 | 1,l,r,d);
}
```
$cnt$ 代表当前已经有多少个不是 $x$ 的倍数的数，当大于 $1$ 时就返回，因为找到的是不能整除的，能整除的就返回，能搜到就说明一定不是 $x$ 的倍数，就自增即可。

最后，此题卡输入输出，无语。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 10;
const int M = 4e5 + 10;
int n,m,a[N],cnt = 0;
struct node {
	int l,r,gcd;
} tr[4 * N];
int read() {
	int x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') {
		x = x * 10 +ch - '0';
		ch = getchar();
	}
	return x;
}
int GCD(int x,int y) {
	if(y == 0) return x;
	else return GCD(y,x % y);
}
void push_up(int u) {
	tr[u].gcd = GCD(tr[u << 1].gcd,tr[u << 1 | 1].gcd);
}
void build(int u,int l,int r) {
	tr[u].l = l,tr[u].r = r;
	if(l == r) {
		tr[u].gcd = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1,l,mid),build(u << 1 | 1,mid + 1,r);
	push_up(u);
}
void modify(int u,int x,int d) {
	if(tr[u].l == tr[u].r && tr[u].l == x) {
		tr[u].gcd = d;
		return;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if(x <= mid) modify(u << 1,x,d);
	if(x > mid) modify(u << 1 | 1,x,d);
	push_up(u);
}
void query(int u,int l,int r,int d) {
	if(cnt > 1)return;
	if(tr[u].gcd % d == 0) {
		return;
	}
	if(tr[u].l == tr[u].r) {
		cnt ++;
		return;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if(l <= mid) query(u << 1,l,r,d);
	if(r > mid)query(u << 1 | 1,l,r,d);
}
signed main() {
	n = read();
	for(int i = 1 ; i <= n ; i ++) a[i] = read();
	build(1,1,n);
	m = read();
	for(int i = 1 ; i <= m ; i ++) {
		int k;
		k = read();
		if(k == 1) {
			int l,r,x;
			l = read(),r = read(),x = read();
			cnt = 0;
			query(1,l,r,x);
			if(cnt > 1) puts("NO");
			else puts("YES");
		} else {
			int x,d;
			x = read(),d = read();
			modify(1,x,d);
		}
	}

	return 0;
}

```


---

## 作者：_Dreamer_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF914D)

### Solution

我们的目标是  修改**至多**一个数 使得这段区间内的  $\gcd=k$ 我们在线段树 向上更新的时候维护区间 $\gcd$ 即可

在查询的时候开一个全局变量 $res$ 表示将当前这段区间修改的时候至少要改几个

更具体的

建立一颗线段树 

其每个结点的值就是这个节点所对应的 最大公约数大小
我们在合并时  只需让 $x$ 节点的值 为 左孩子节点权值  和 右孩子节点权值的 $\gcd$ 即可

小 tips

- $res>1$ 的时候直接 return 剩下的再改也达不到要求
- 只在区间 $\gcd$ 不能整除 $k$ 时向下递归


如果 $res=0,1$ 输出 YES
否则输出 NO 即可

通过这个记录 $res$ 的操作 最多只会访问到两个叶子节点  所以查询的复杂度是 $\log n$ 级别的

修改操作和普通线段树一样 也是 $\log$ 级别的
建树是 $n\log n$ 的

所以总的时间复杂度是 $O(n\log\ n)$

### Code

```cpp

#include<bits/stdc++.h>
using namespace std;
const int N=500005;
#define ls (x<<1)
#define rs ls|1
#define mid ((l+r)>>1)
#define Lson ls,l,mid
#define Rson rs,mid+1,r
int gcd(int a,int b)
{
	if(b==0)return a;
	return gcd(b,a%b);
}
struct node
{
	int g;
	friend node operator + (node a,node b)
	{
		node ans;ans.g=0;
		ans.g=gcd(a.g,b.g);
		return ans;
	}
}a[N<<2];
void build(int x,int l,int r)
{
	if(l==r)
	{
		scanf("%d",&a[x].g);
		return;
	}
	build(Lson);build(Rson);
	a[x]=a[ls]+a[rs];
}
void change(int x,int l,int r,int L,int R,int k)
{
	if(L<=l&&r<=R)
	{
		a[x].g=k;
		return;
	}
	if(L<=mid)change(Lson,L,R,k);
	if(mid<R )change(Rson,L,R,k);
	a[x]=a[ls]+a[rs];
}
int res=0;
void query(int x,int l,int r,int L,int R,int k)
{
	if(res>1)
	{
		return;
	}
	if(l==r)
	{
		res++;
		return;
	}
	if(L<=mid&&a[ls].g%k)query(Lson,L,R,k);
	if(mid<R &&a[rs].g%k)query(Rson,L,R,k);
}
int n,m;
int main()
{
	scanf("%d",&n);
	build(1,1,n);
	scanf("%d",&m);
	while(m--)
	{
		int opt,l,r,k;
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d%d",&l,&r,&k);
			res=0;
			query(1,1,n,l,r,k);
			puts(res>1?"NO":"YES");
		}
		else
		{
			scanf("%d%d",&l,&k);
			change(1,1,n,l,l,k);
		}
	}
	return 0;
}

```

---

## 作者：tgs9311 (赞：0)

# 分块

看到没有写分块的，那我就写一篇分块的题解

这道题很像[P4145](https://www.luogu.com.cn/problem/P4145)，都是暴力修改+优化

# 对于修改操作和查询操作分类讨论：

1. ## 修改
	
    修改很简单，直接单点修改并更新区间lazy标记（区间gcd值）

2. ## 查询

	显然，对于区间内不能被x整除的数的个数大于1时显然怎么改也不能符合要求。
   
   所以我们只要查询区间内不能被x整除的数的个数就好了
   
   那么如何把区间gcd值改为不能被x整除的数呢？
   
   我们容易知道，如果区间gcd值 $mod x=0$,那么这个区间里的数肯定都能被x整除
   
   如果不等于0，就暴力遍历即可
   
# 优化

1.	数据量比较大，使用快读
2. 将频繁使用的循环变量改为register
3. 查询时如果区间内不能被x整除的数的个数已经$>2$，就直接输出NO并return

这样就可以用分块通过本题啦

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace FAST_IO
{
	template<typename T> void read(T &a)
	{
		a=0;
		int f=1;
		char c=getchar();
		while(!isdigit(c))
		{
			if(c=='-')
			{
				f=-1;
			}
			c=getchar();
		}
		while(isdigit(c))
		{
			a=a*10+c-'0';
			c=getchar();
		}
		a=a*f;
	}
	template <typename T> void write(T a)
	{
		if(a<0)
		{
			a=-a;
			putchar('-');
		}
		if(a>9)
		{
			write(a/10);
		}
		putchar(a%10+'0');
	}
	template <typename T> void writeln(T a)
	{
		write(a);
		puts("");
	}
}//快读
const int maxn=5e5+999;
int belong[maxn],l[maxn],r[maxn],num,_size;
int n,a[maxn],add[maxn],lazy[maxn];
void build()
{
	_size=sqrt(n);
	num=n/_size;
	if(n%_size)
	{
		num++;
	}
	for(int i=1;i<=num;i++)
	{
		l[i]=(i-1)*_size+1;
		r[i]=i*_size;
	}
	r[num]=n;
	for(int i=1;i<=n;i++)
	{
		FAST_IO::read(a[i]);
		belong[i]=i/_size;
		if(i%_size)
		{
			belong[i]++;
		}
		lazy[belong[i]]=__gcd(lazy[belong[i]],a[i]);
	}
} 
void update(int pos,int c)
{
	int x=belong[pos];
	a[pos]=c;
	lazy[x]=0;
	for(register int i=l[x];i<=r[x];i++)
	{
		lazy[x]=__gcd(lazy[x],a[i]);
	}
}
void ask1(int ls,int rs ,int xt)
{
	int ans=0;
	int x=belong[ls],y=belong[rs];
	register int i,j;
	if(x==y)
	{
		for(i=ls;i<=rs;i++)
		{
			if(a[i]%xt!=0)
			{
				ans++;
			}
		}
	}
	else
	{
		for(i=ls;i<=r[x];i++)
		{
			if(a[i]%xt!=0)
			{
				ans++;
			}
		}			
		if(ans>=2)
		{
			puts("NO");
			return;
		}
		for(i=x+1;i<=y-1;i++)
		{
			if(lazy[i]%xt!=0)
			{
				for(j=l[i];j<=r[i];j++)
				{
					if(a[j]%xt!=0)
					{
						ans++;
					}
				}			
				if(ans>=2)
				{
					puts("NO");
					return;
				}	
			}
		}
		for(i=l[y];i<=rs;i++)
		{
			if(a[i]%xt!=0)
			{
				ans++;				
			}
		}
	}
	if(ans>=2)
	{
		puts("NO");
	}
	else
	{
		puts("YES");
	}
}
int op,ltt,rtt,x;
signed main()
{
	int f;
	FAST_IO::read(n);
	build();
	FAST_IO::read(f);
	while(f--)
	{
		FAST_IO::read(op);
		FAST_IO::read(ltt);
		FAST_IO::read(rtt);
		if(op==1)
		{
			FAST_IO::read(x);
			ask1(ltt,rtt,x);
		}
		else
		{
			update(ltt,rtt);
		}	
	}
}
```


---

## 作者：king_xbz (赞：0)

就是简单的线段树优化暴力.

我们让线段树$t[x].tot$维护其子树的最大公约数

我们统计在范围内的序列中有几个数满足$x\%y=0$,如果为0个或者一个,那么都可以实现,否则就不能实现.

当然,单纯的暴力只会收获无穷无尽的TLE,所以我们需要优化剪枝的操作.

这里需要用一个计数器$num$,当$num>1$的时候就直接结束线段树的递归操作,这个剪枝的操作可以保证我们通过此题.

代码:

```cpp
#include<bits/stdc++.h>
#define fint register int
#define H 5001
#define N 1437985
#define tt t[x].tot
#define ls x<<1
#define rs x<<1|1
#define ll t[x].l
#define rr t[x].r
#define tg t[x].tag
using namespace std;
struct node
{
	int l;
	int r;
	int tot;
	int tag;
}
t[N];
int a[N];
int num;
inline int read();
void build(int x,int l,int r);
void modify(int x,int pos,int y);
void query(int x,int l,int r,int y);
inline void pushup(int x);
int gcd(int x,int y);
inline void todo(int x,int y,int z);
int main()
{
	int n;
	n=read();
	for(fint i=1;i<=n;i++)
	a[i]=read();
	build(1,1,n);
	int m;
	m=read();
	while(m--)
	{
		int op;
		op=read();
		int x,y,z;
		if(op==1)
		x=read(),y=read(),z=read(),todo(x,y,z);
		else
		x=read(),y=read(),modify(1,x,y);
	}
	return 0;
}

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

void build(int x,int l,int r)
{
	ll=l,rr=r;
	if(l==r)
	{
		tt=a[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(x);
	return ;
}

void modify(int x,int pos,int y)
{
	if(ll==rr)
	{
		tt=y;
		return ;
	}
	int mid=(ll+rr)>>1;
	if(pos<=mid)
	modify(ls,pos,y);
	else
	modify(rs,pos,y);
	pushup(x);
	return ;
}

void query(int x,int l,int r,int y)
{
	if(num>1||tt%y==0)
	return ;
	if(ll==rr)
	{
		num++;
		return ;
	}
	int mid=(ll+rr)>>1;
	int tot=0;
	if(l<=mid)
	query(ls,l,r,y);
	if(r>mid)
	query(rs,l,r,y);
	return ;
}

inline void pushup(int x)
{
	tt=gcd(t[ls].tot,t[rs].tot);
	return ;
}

int gcd(int x,int y)
{
	if(y==0)
	return x;
	return gcd(y,x%y);
}

inline void todo(int x,int y,int z)
{
	num=0;
	query(1,x,y,z);
	if(num>1)
	puts("NO");
	else
	puts("YES");
	return ;
}
```
这样的话,我们就可以轻松通过此题,祝大家AC愉快!


---

## 作者：Elgo87 (赞：0)

很容易看出这题是一道**线段树**的板子题，适合用来练手。

考虑用线段树来维护当前区间的**最大公约数**。


- 对于 $1$ 操作，查询时只需查询区间内最大公约数是否能通过**一次及以下的改动**使得 $\gcd(a_{l...r})=x$。

- 对于 $2$ 操作，直接找到当前结点修改即可。

代码应该很好写，套一下模板就行了。

```cpp
# include <iostream>
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <string>
# include <stack>
# include <queue>
# include <vector>
# define max(a,b) ((a)>(b) ? (a) : (b))
# define min(a,b) ((a)<(b) ? (a) : (b))
# define abs(a,b) ((a)> 0  ? (a) : -(a))
# define int long long
using namespace std;

inline void read(int& num) {
	num = 0; int nev = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') nev = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { num = (num<<1) + (num<<3) + (ch ^ 48); ch = getchar(); }
}

inline void print(const int& x) {
	if (x < 0) { putchar('-'); print(-x); return ; }
	if (x < 10) { putchar(x+'0'); return ;}
	print(x/10), putchar(x%10 + '0'); return ;
}

int gcd(int n, int m)
{
	if (m != 0) return gcd(m, n%m);
	else return n;
}


int a[514514 << 2];
int tree[514514 << 2];

void build(int k, int l, int r)
{
	if (l == r) {
		tree[k] = a[l];
		return ;
	}
	int mid = l + r >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	tree[k] = gcd(tree[k<<1],  tree[k<<1 | 1]);
}

void modify(int k, int l, int r, int p, int v)
{
	if (l > p || r < p) return;
	if (l == r)
	{
		tree[k] = v;
		return ;
	}
	int mid = l + r >> 1;
	modify(k << 1, l, mid, p, v);
	modify(k << 1 | 1, mid + 1, r, p, v);
	tree[k] = gcd(tree[k<<1], tree[k<<1 | 1]);
}


int ans = 0;      //ans 存储需要修改多少次才能使得最大公约数等于 x
void query(int k, int l, int r, int x, int y, int v)
{
	if (l > y || r < x || ans > 1) return ;
	if (l == r)     { ans++;   return ;}
	
	int mid = l + r >> 1;
	if (tree[k<<1] % v) query(k << 1, l, mid, x, y, v);
	if (tree[k<<1|1] % v) query(k << 1 | 1, mid + 1, r, x, y, v);
}

signed main()
{
	int n;
	read(n);
	for (int i = 1; i <= n; i ++)   read(a[i]);
	build(1,1,n);
	
	int q;
	read(q);
	for (int i = 1; i <= q; i ++)
	{
		int op;
		read(op);
		if (op == 1)
		{
			int l, r, x;
			read(l), read(r), read(x);
			ans = 0;
			query (1,1,n,l,r,x);
			if (ans > 1) puts("NO");
			else puts("YES");
		}
		else
		{
			int i,y;
			read(i), read(y);
			modify(1,1,n, i, y);
		}
	}
	return 0;
}

```

---

## 作者：银河AI (赞：0)

### 解题思路

操作 $2$ 的单点修改应该就不用多说了。

接下来分析操作 $1$ ，

本题的关键如何查找 $[l,r]$ 中模 $x$ 不等于 $0$ 的个数。

我们考虑用线段树实现。

我们用线段树来存储一段区间内的 $\gcd$。

查询的时候，用 $cnt$，来代表查询区间 $[l,r]$ 中模 $x$ 不等于 $0$ 的个数。

如果 $cnt=1$，那么说明这段区间内只有一个数模 $x$ 不等于 $0$，那么我们只需要将这个数改为 $x$，那么这一段的 $\gcd$ 就是 $x$ ，满足题意。

如果 $cnt=0$，那么则不需要更改。

如果 $cnt>1$ 那么说明至少需要改两个以上的数才能满足题意，所以不行。

查询的时候可以实现一点小剪枝：

如果 $cnt$ 已经大于 $1$ 了，那么则不需要找了。

还有查询的时候注意: 我们只需要查询 $\gcd$ 不等于 $x$ 的区间。

具体的实现放在代码里了。

接下来放上AC代码。

### AC代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+1;
int n,m,cnt;
int a[N],tr[N<<2];
inline int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
void build(int p,int l,int r){
	if(l==r){tr[p]=a[l];return ;}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);build(p<<1|1,mid+1,r);
	tr[p]=gcd(tr[p<<1],tr[p<<1|1]);
}
void add(int p,int l,int r,int x,int k){
	if(l==x&&r==x){tr[p]=k;return ;}
	int mid=(l+r)>>1;
	if(x<=mid) add(p<<1,l,mid,x,k);
	else add(p<<1|1,mid+1,r,x,k);
	tr[p]=gcd(tr[p<<1],tr[p<<1|1]);
}
void ask(int p,int l,int r,int x,int y,int z){
	if(cnt>1) return ;
	if(l==r){cnt++;return ;}
	int mid=(l+r)>>1;
	if(x<=mid&&tr[p<<1]%z) ask(p<<1,l,mid,x,y,z);
	if(y>mid&&tr[p<<1|1]%z) ask(p<<1|1,mid+1,r,x,y,z);
}
int opt,x,y,z;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	build(1,1,n);
	scanf("%lld",&m);
	while(m--){
		scanf("%d",&opt);
		if(opt==1){
			scanf("%lld%lld%lld",&x,&y,&z);
			ask(1,1,n,x,y,z);
			if(cnt>1) printf("NO\n");
			else printf("YES\n");
			cnt=0;
		}
		else{
			scanf("%lld%lld",&x,&y);
			add(1,1,n,x,y);
		}
	}
} 
```


---

