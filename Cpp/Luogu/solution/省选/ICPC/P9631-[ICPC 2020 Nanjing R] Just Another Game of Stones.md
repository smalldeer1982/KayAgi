# [ICPC 2020 Nanjing R] Just Another Game of Stones

## 题目描述

Kotori 和 Umi 正在玩由 Honoka 主持的石子游戏。规则与经典游戏相同：有若干堆石子，玩家轮流从一堆中移走任意数量的石子。不能进行合法移动的玩家输掉游戏。

然而这次情况会有些不同。作为主持人，Honoka 将从 $n$ 个候选石子堆中准备游戏，其中第 $i$ 堆最初有 $a_i$ 个石子。Honoka 将执行 $q$ 次以下两种类型的操作：

- 给定三个整数 $l$、$r$ 和 $x$，对于所有 $l \le i \le r$，将第 $i$ 个候选石子堆中的石子数量更改为 $\max(b_i, x)$，其中 $b_i$ 是当前第 $i$ 个候选石子堆中的石子数量。
- 给定三个整数 $l$、$r$ 和 $x$，开始一个由 $(r-l+2)$ 堆组成的石子游戏，其中第 $i$ 堆包含 $b_{l-1+i}$ 个石子，$1 \le i < (r-l+2)$，并且第 $(r-l+2)$ 堆包含 $x$ 个石子。注意，此操作仅查询答案，不会影响 $n$ 个候选石子堆的状态。

Kotori 总是第一个行动。作为 Kotori 的忠实粉丝，你想知道对于每个石子游戏，如果双方都使用最佳策略，Kotori 在第一步中确保胜利的方法数。我们认为两种方法不同，如果 Kotori 从不同的堆中取石子，或者从同一堆中取不同数量的石子。

## 说明/提示

对于第一个操作，玩家将进行一个由 $1$、$2$、$1$ 和 $1$ 个石子组成的石子游戏。Kotori 唯一的获胜方式是将有 $2$ 个石子的堆减少到 $1$ 个石子。

在第二个操作之后，候选石子堆中的石子数量变为 $1$、$3$、$3$、$4$ 和 $1$。

对于第四个操作，玩家将进行一个由 $1$、$3$、$3$、$4$ 和 $4$ 个石子组成的石子游戏。Kotori 的获胜方式是将有 $1$ 个石子的堆减少到 $0$ 个石子，或者将任何有 $3$ 个石子的堆减少到 $2$ 个石子。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 4
1 2 1 4 1
2 1 3 1
1 2 4 3
2 2 4 4
2 1 4 4```

### 输出

```
1
0
3```

# 题解

## 作者：WhitD (赞：4)

## 题目大意
给定 $n$ 个石堆，第 $i$ 个石堆的石子数为 $a_i$，有 $q$ 次操作：

`1 l r x` 表示令所有 $a_i=\max(a_i,x),i\in[l,r]$。

`2 l r x` 表示用石堆 $[l,r]$ 和一个石子数为 $x$ 的石堆进行 Nim 游戏，求出第一次先手取完石子后游戏变为后手必败局面的可操作总数。

（如果你还不了解 Nim 游戏，[点这里](https://oi-wiki.org//math/game-theory/impartial-game/)）。
## 思路
我们知道，Nim 游戏中所有石堆的石子数异或和为 $0$ 的局面为先手必败局面，所以第一步需要保证取完石子后剩下石堆的石子数异或和为 $0$（相当于把先手必败的局面给对手）才能赢得游戏。

设当前异或和为 $s$，某一石堆里的石子数为 $a_i$，我们需要取走 $a_i-a_i\oplus s$ 个石子才能保证取完后异或和为 $0$（也就是令 $a_i=a_i\oplus s$），那么当 $a_i\ge a_i\oplus s$ 时就可以对该石堆进行一次操作，因此操作二所求答案就是 $\sum_{i=l}^r[a_i\ge a_i\oplus s]$。同时我们知道异或本质上是不进位的加法，考虑 $s$ 的最高位 $1$，若 $a_i$ 在此位也是 $1$，则 $a_i\ge a_i\oplus s$ 恒成立，反之恒不成立。

可以用吉司机线段树（Segment Tree Beats）维护操作一（取 $\max$），同时对于线段树的每个节点都维护区间的异或和，并且记录每一种二进制位为1的数字的数量，向上合并时直接暴力即可。

（如果你还不了解吉司机线段树，[点这里](https://oi-wiki.org/ds/seg-beats/)）。

## AC 代码
```cpp
#include<iostream>
#define mid ((l+r)>>1)
#define ls (rt<<1)
#define rs (rt<<1|1)
using namespace std;
const int N=200005;
struct node
{
 	int cnt[31],ccnt,p,op,sum,tag;
}tr[N<<2];
int a[N],n,m;
struct SegmentTreeBeats
{
 	void pushup(int rt)
	{
 		if(tr[ls].p<tr[rs].p)
		{
 			tr[rt].p=tr[ls].p;
 			tr[rt].ccnt=tr[ls].ccnt;
 			tr[rt].op=min(tr[ls].op,tr[rs].p);
 			tr[rt].sum=tr[ls].sum^tr[rs].sum;
 			for(int i=0;i<=30;i++)
			 	tr[rt].cnt[i]=tr[ls].cnt[i]+tr[rs].cnt[i];
 		}
 		else if(tr[ls].p>tr[rs].p)
		{
 			tr[rt].p=tr[rs].p;
 			tr[rt].ccnt=tr[rs].ccnt;
 			tr[rt].op=min(tr[rs].op,tr[ls].p);
 			tr[rt].sum=tr[rs].sum^tr[ls].sum;
 			for(int i=0;i<=30;i++)
			 	tr[rt].cnt[i]=tr[ls].cnt[i]+tr[rs].cnt[i];
 		}
 		else
		{
 			tr[rt].p=tr[ls].p;
 			tr[rt].ccnt=tr[ls].ccnt+tr[rs].ccnt;
 			tr[rt].op=min(tr[ls].op,tr[rs].op);
 			tr[rt].sum=tr[ls].sum^tr[rs].sum;
 			for(int i=0;i<=30;i++)
			 	tr[rt].cnt[i]=tr[ls].cnt[i]+tr[rs].cnt[i];
 		}
 	}
 	void pushtag(int rt,int x)
	{
 		if(tr[rt].p>=x)
		 	return ;
 		if(tr[rt].ccnt&1)
 			tr[rt].sum^=tr[rt].p,tr[rt].sum^=x;
 		for(int i=0;i<=30;i++)
		{
 			if(tr[rt].p>>i&1)
			 	tr[rt].cnt[i]-=tr[rt].ccnt;
 			if(x>>i&1)
			 	tr[rt].cnt[i]+=tr[rt].ccnt;
 		}
 		tr[rt].p=x;
 		tr[rt].tag=x;
 	}
 	void pushdown(int rt)
	{
 		if(tr[rt].tag==-1)
		 	return ;
 		pushtag(ls,tr[rt].tag);
		pushtag(rs,tr[rt].tag);
 		tr[rt].tag=-1;
 	}
 	void build(int rt,int l,int r)
	{
 		tr[rt].tag=-1;
 		if(l==r)
		{
 			tr[rt].p=a[l];
 			tr[rt].sum=a[l];
 			tr[rt].ccnt=1;
 			tr[rt].op=1e18;
 			for(int i=0;i<=30;i++)
 				if(a[l]>>i&1)
				 	tr[rt].cnt[i]++;
 			return ;
 		}
 		build(ls,l,mid);
 		build(rs,mid+1,r);
 		pushup(rt);
 	}
 	void modify(int rt,int l,int r,int cl,int cr,int x)
	{
 		if(tr[rt].p>=x)
		 	return ;
 		if(l>=cl&&r<=cr&&tr[rt].op>x)
		{
 			pushtag(rt,x);
 			return ;
 		}
 		pushdown(rt);
 		if(cl<=mid)
		 	modify(ls,l,mid,cl,cr,x);
 		if(cr>mid)
		 	modify(rs,mid+1,r,cl,cr,x);
 		pushup(rt);
 	}
 	int qsum(int rt,int l,int r,int cl,int cr)
	{
 		if(l>=cl&&r<=cr)
 			return tr[rt].sum;
 		pushdown(rt);
 		int sum=0;
 		if(cl<=mid)
		 	sum^=qsum(ls,l,mid,cl,cr);
 		if(cr>mid)
		 	sum^=qsum(rs,mid+1,r,cl,cr);
 		return sum;
 	}
 	int qbit(int rt,int l,int r,int cl,int cr,int x)
	{
 		if(l>=cl&&r<=cr)
 			return tr[rt].cnt[x];
 		pushdown(rt);
 		int sum=0;
 		if(cl<=mid)
		 	sum+=qbit(ls,l,mid,cl,cr,x);
 		if(cr>mid)
		 	sum+=qbit(rs,mid+1,r,cl,cr,x);
 		return sum;
 	}
}tree;
int main()
{
 	cin>>n>>m;
 	for(int i=1;i<=n;i++)
		cin>>a[i]; 
 	tree.build(1,1,n);
 	while(m--)
	{
 		int op,l,r,x;
 		cin>>op>>l>>r>>x;
 		if(op&1)
 			tree.modify(1,1,n,l,r,x);
 		else
		{
 			int sum=tree.qsum(1,1,n,l,r),max=-1;
 			sum^=x;
 			for(int i=30;i>=0;i--)
			{
 				if(sum>>i&1)
				{
 					max=i;
 					break;
 				}
 			}
 			if(max==-1)
			 	cout<<0<<endl;
 			else
 				cout<<tree.qbit(1,1,n,l,r,max)+(x>>max&1)<<endl;
 		}
 	}
 	return 0;
}
```


---

## 作者：tribool4_in (赞：2)

吉司机线段树。

操作为区间修改取 $\max$，这是吉司机线段树模板，容易维护。

考虑询问如何实现。考虑 Nim 游戏的结论：令 $s=x\oplus a_l\oplus a_{l+1}\oplus\dots\oplus a_r$，先手必败当且仅当 $s=0$。可以用线段树维护区间异或和，这样可以判断先手是否必胜。

考虑如何得出可操作方案数。不妨把 $x$ 算入 $a$，则如果此时先手有必胜策略，策略显然是 $a_i\gets a_i\oplus s$。而 Nim 游戏要求是减少数量，因此转化为询问满足 $a_i>a_i\oplus s$ 的数量。

考虑异或的性质。对于 $s$ 二进制下的最高为 $1$ 的位，显然存在 $a_i$ 当前位为 $1$。对于该位为 $1$ 的 $a_i$，异或上 $s$ 之后显然会变小；反之则一定变大。因此只需要统计某一位为 $1$ 的数的个数即可。这些信息用吉司机线段树均容易维护。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, q, a[N];
struct node {
    int mn, se, mncnt, tag;
    int xors, cnt[30];
} t[N << 2];
void push_up(int p) {
    t[p].xors = t[p << 1].xors ^ t[p << 1 | 1].xors;
    for (int i = 0; i < 30; i++) t[p].cnt[i] = t[p << 1].cnt[i] + t[p << 1 | 1].cnt[i];
    if (t[p << 1].mn == t[p << 1 | 1].mn) {
        t[p].mn = t[p << 1].mn, t[p].mncnt = t[p << 1].mncnt + t[p << 1 | 1].mncnt;
        t[p].se = min(t[p << 1].se, t[p << 1 | 1].se);
    } else if (t[p << 1].mn < t[p << 1 | 1].mn) {
        t[p].mn = t[p << 1].mn, t[p].mncnt = t[p << 1].mncnt;
        t[p].se = min(t[p << 1].se, t[p << 1 | 1].mn);
    } else if (t[p << 1].mn > t[p << 1 | 1].mn) {
        t[p].mn = t[p << 1 | 1].mn, t[p].mncnt = t[p << 1 | 1].mncnt;
        t[p].se = min(t[p << 1].mn, t[p << 1 | 1].se);
    }
}
void build(int p, int l, int r) {
    t[p].tag = -1;
    if (l == r) {
        t[p].mn = t[p].xors = a[l], t[p].se = INT_MAX, t[p].mncnt = 1;
        for (int i = 0; i < 30; i++) t[p].cnt[i] = (a[l] >> i & 1);
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    push_up(p);
}
void set_tag(int p, int v) {
    if (t[p].mn >= v) return;
    t[p].xors ^= ((t[p].mncnt & 1) * (t[p].mn ^ v));
    for (int i = 0; i < 30; i++)
        t[p].cnt[i] += ((v >> i & 1) - (t[p].mn >> i & 1)) * t[p].mncnt;
    t[p].mn = t[p].tag = v;
}
void push_down(int p) {
    if (t[p].tag == -1) return;
    set_tag(p << 1, t[p].tag), set_tag(p << 1 | 1, t[p].tag);
    t[p].tag = -1;
}
void update(int p, int l, int r, int x, int y, int v) {
    if (t[p].mn >= v) return;
    if (x <= l && r <= y && v < t[p].se) {
        set_tag(p, v);
        return;
    }
    push_down(p);
    int mid = (l + r) >> 1;
    if (x <= mid) update(p << 1, l, mid, x, y, v);
    if (mid < y) update(p << 1 | 1, mid + 1, r, x, y, v);
    push_up(p);
}
int query1(int p, int l, int r, int x, int y) {
    if (x <= l && r <= y) return t[p].xors;
    push_down(p);
    int mid = (l + r) >> 1, res = 0;
    if (x <= mid) res ^= query1(p << 1, l, mid, x, y);
    if (mid < y) res ^= query1(p << 1 | 1, mid + 1, r, x, y);
    return res;
}
int query2(int p, int l, int r, int x, int y, int k) {
    if (x <= l && r <= y) return t[p].cnt[k];
    push_down(p);
    int mid = (l + r) >> 1, res = 0;
    if (x <= mid) res += query2(p << 1, l, mid, x, y, k);
    if (mid < y) res += query2(p << 1 | 1, mid + 1, r, x, y, k);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    for (int i = 1, op, l, r, x; i <= q; i++) {
        cin >> op >> l >> r >> x;
        if (op == 1) {
            update(1, 1, n, l, r, x);
        } else {
            int y = query1(1, 1, n, l, r) ^ x, b = -1;
            for (int j = 0; j < 30; j++)
                if (y >> j & 1) b = j;
            if (b == -1) {
                cout << "0\n";
                continue;
            }
            int ans = query2(1, 1, n, l, r, b) + (x >> b & 1);
            cout << ans << '\n';
        }
    }
    return 0;
}
```

---

## 作者：nnn233 (赞：0)

# 题解：P9631 \[ICPC 2020 Nanjing R] Just Another Game of Stones

[题目传送门](https://www.luogu.com.cn/problem/P9631)

> ## 题意简述
>
> 给定一个序列 A，维护两种操作：
>
> - 区间 $\max(a_i,x)$；
> - 用区间 $[l,r]$ 的数加上 $x$ 玩一局 Nim 游戏，求有多少种方案在**进行一次操作后**游戏变为**先手必败**状态。

前置芝士：吉司机线段树，简单博弈论。

---

### 解题思路

如果你学过吉司机线段树或做过 [P6242	【模板】线段树 3（区间最值操作、区间历史最值）](https://www.luogu.com.cn/problem/P6242)，那操作一是相对好维护的，重点在操作二。

---

### 操作二

操作二其实就是简单 Nim 问题，如果你学过或看过博弈论（没学过建议详细阅读 [OI Wiki 中 Nim 游戏 部分](https://oi-wiki.org/math/game-theory/impartial-game/#nim-%E5%92%8C)），一定知道 Nim 问题的结论：

> 定义 Nim 和 $=a_1 \oplus a_2 \oplus \ldots \oplus a_n$。\
> 当且仅当 Nim 和为 0 时，该状态为必败状态；否则该状态为必胜状态。

那操作二实际要求的是什么？进行一次操作使得 Nim 和为 $0$ 有多少种方案，怎么求呢？其实在 [OI Wiki 中 Nim 和 部分关于 定理 2 的证明](https://oi-wiki.org/math/game-theory/impartial-game/#%E8%AF%81%E6%98%8E) 基本已经告诉你了。

> 定理 2：对于 $a_1 \oplus a_2 \oplus \ldots \oplus a_n \neq 0$ 的局面，一定存在某种移动使得 $a_1 \oplus a_2 \oplus \ldots \oplus a_n = 0$。
>
> 不妨假设 $a_1 \oplus a_2 \oplus \ldots a_n = k \neq 0$。如果我们要将 $a_i$ 改为 $a_i'$，则 $a_i'=a_i \oplus k$。
>
> 假设 $k$ 的二进制最高位 $1$ 为 $d$，即 $2^d \le k < 2^{d + 1}$。根据异或定义，一定有奇数个 **$a_i$ 的二进制第 $d$ 位为 $1$。满足这个条件的 $a_i$ 一定也满足 $a_i > a_i \oplus k$**，因而这也是个合法的移动。

精简一点，设 $a_1 \oplus a_2 \oplus \ldots a_n = k \neq 0$，$k$ 的二进制最高位 $1$ 为 $d$，只用统计一下区间内有多少个 $a_i$ 的二进制第 $d$ 位为 $1$ 就是答案了。

那这个要怎么快速维护呢？

我们维护异或和来快速求出 $k$，同时维护二进制下第 $i$ 位为 $1$ 的数的数量来快速查询就行了。

至于询问中额外的一堆石子数为 $x$ 的石堆，说实话意义不明，可能是防一手其他的奇怪算法吧，总之查询完区间信息后把关于 $x$ 的信息合并进去就好了。

线段树信息合并 $O(\log n)$，单次操作 $O(\log^2 n)$，总复杂度 $O(m\log^2 n)$。

### CODE

```
//#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
bool Mbe;
//#define int long long
#define pb emplace_back
typedef long long ll;
const int mod=1e9+7;
const int N=2e5+50;
const int inf=2e9;
int n,m,q,k;
int a[N];
#define lc (u<<1)
#define rc (lc|1)
#define mid (l+r>>1)
#define ls lc,l,mid
#define rs rc,mid+1,r
#define root 1,1,n
struct segtree_beats{
    int mf,ms,mt,xors;
    int f[32];
    int tag;
}t[N<<2];
inline int lb(int x){return x&-x;}
inline void pushup(int u){
    t[u].mf=min(t[lc].mf,t[rc].mf);
    t[u].ms=min(t[u].mf==t[lc].mf?t[lc].ms:t[lc].mf,t[u].mf==t[rc].mf?t[rc].ms:t[rc].mf);
    t[u].mt=(t[u].mf==t[lc].mf?t[lc].mt:0)+(t[u].mf==t[rc].mf?t[rc].mt:0);
    t[u].xors=t[lc].xors^t[rc].xors;
    for(int i=0;i<=31;i++)t[u].f[i]=t[lc].f[i]+t[rc].f[i];
}
inline void build(int u,int l,int r){
    t[u].tag=0;
    if(l==r){
        t[u].mf=t[u].xors=a[l],t[u].ms=inf,t[u].mt=1;
        for(int i=0;(1<<i)<=a[l];i++)if((1<<i)&a[l])t[u].f[i]++;
        return ;
    }
    build(ls);
    build(rs);
    pushup(u);
}
inline void work(int u,int v){
    if(t[u].mt%2)t[u].xors^=t[u].mf;
    for(int i=0;(1<<i)<=t[u].mf;i++)if((1<<i)&t[u].mf)t[u].f[i]-=t[u].mt;
    t[u].mf+=v,t[u].tag+=v;
    for(int i=0;(1<<i)<=t[u].mf;i++)if((1<<i)&t[u].mf)t[u].f[i]+=t[u].mt;
    if(t[u].mt%2)t[u].xors^=t[u].mf;
}
inline void pushdown(int u){
    int mini=min(t[lc].mf,t[rc].mf);
    if(t[lc].mf==mini)work(lc,t[u].tag);
    if(t[rc].mf==mini)work(rc,t[u].tag);
    t[u].tag=0;
}
inline void update(int u,int l,int r,int s,int e,int v){
    if(s<=l&&r<=e){
        if(v<=t[u].mf)return;
        if(v<t[u].ms){
            work(u,v-t[u].mf);
            return ;
        }
    }
    pushdown(u);
    if(s<=mid)update(ls,s,e,v);
    if(mid<e)update(rs,s,e,v);
    pushup(u);
}
inline segtree_beats merge(segtree_beats x,segtree_beats y){
    segtree_beats res;
    res.xors=x.xors^y.xors;
    for(int i=0;i<=31;i++){
        res.f[i]=x.f[i]+y.f[i];
    }
    return res;
}
inline segtree_beats query(int u,int l,int r,int s,int e){
    if(s<=l&&r<=e)return t[u];
    pushdown(u);
    if(s<=mid&&mid<e)return merge(query(ls,s,e),query(rs,s,e));
    if(s<=mid)return query(ls,s,e);
    if(mid<e)return query(rs,s,e);
}
bool Med;
signed main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    //ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif
    //freopen("P9631.cpp.in","r",stdin);
    //freopen("P9631.cpp.out","w",stdout);
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(root);
    while(q--){
        int opt,l,r,x;
        cin>>opt>>l>>r>>x;
        if(opt==1)update(root,l,r,x);
        else{
            segtree_beats tmp=query(root,l,r);
            ll ans=0;
            for(int i=0;(1<<i)<=x;i++)if((1<<i)&x)tmp.f[i]++;
            tmp.xors^=x;
            if(tmp.xors){
                for(int i=0;(1<<i)<=tmp.xors;i++)if((1<<i)&tmp.xors)k=i;
                ans+=tmp.f[k];
                // cout<<tmp.xors<<" "<<k<<"!\n";
            }else ans=0;
            // for(int i=0;i<=31;i++)cout<<tmp.f[i]<<" ";cout<<"\n";
            cout<<ans<<'\n';
        }
    }
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
/*
 
*/
 
/*
文件名: P9631.cpp
创建时间: 2025-04-01 08:33:11
作者: nnn233
*/
```

---

## 作者：StayAlone (赞：0)

相当简单的题目。

跨越一年半，偶然间再次打开这道题，原来真的能看到自己的成长。

---------

查询实际上就是，问先手有多少种方案，使得操作后的异或和为 $0$。

先不考虑多余添加的石堆 $x$，这在本题中相当不重要。

如果先手拿第 $i$ 个石堆，则要求拿完后 $a_i\oplus\text{others}=0$，即 $a_i=\text{others}$。那么当 $a_i>\text{others}$ 时，贡献一种方案，否则不贡献方案。问题转化为求 $a_i>\text{others}$ 的数量。设区间异或和为 $s$，问题转化为求 $a_i>a_i\oplus s$ 的数量。

$s$ 是好求的，考虑怎样的 $a_i$ 能使得 $a_i>a_i\oplus s$。

考虑 $s$ 的 $\text{highbit}$，$a_i$ 异或 $s$ 时，更高位不变，$\text{highbit}$ 位取反，后面不管。则当且仅当 $a_i$ 的 $\text{highbit(s)}$ 位是 $1$，异或后变成 $0$，满足 $a_i>a_i\oplus s$。

因此只需要在线段树上维护异或和、每一位的数量。

区间取 $\max$ 只需额外维护区间最小值、次小值和最小值数量即可。时间复杂度 $\mathcal O(n\log n\log V)$。

一遍过了。

[AC record](https://www.luogu.com.cn/record/212434329)
```cpp
int n, m;

struct setr {
    #define STZ MAXN << 2
    int mi[STZ], sem[STZ], xr[STZ], mcnt[STZ], cnt[31][STZ], tag[STZ];

    il void pushup(int x) {
        if (mi[ls(x)] == mi[rs(x)]) {
            mi[x] = mi[ls(x)]; mcnt[x] = mcnt[ls(x)] + mcnt[rs(x)];
            sem[x] = min(sem[ls(x)], sem[rs(x)]);
        } else if (mi[ls(x)] < mi[rs(x)]) {
            mi[x] = mi[ls(x)]; mcnt[x] = mcnt[ls(x)];
            sem[x] = min(sem[ls(x)], mi[rs(x)]);
        } else {
            mi[x] = mi[rs(x)]; mcnt[x] = mcnt[rs(x)];
            sem[x] = min(sem[rs(x)], mi[ls(x)]);
        } xr[x] = xr[ls(x)] ^ xr[rs(x)];
        rep1(i, 0, 30) cnt[i][x] = cnt[i][ls(x)] + cnt[i][rs(x)];
    }

    il void change(int x, int v) {
        if (v <= mi[x]) return;
        rep1(i, 0, 30) cnt[i][x] += ((v >> i & 1) - (mi[x] >> i & 1)) * mcnt[x];
        (mcnt[x] & 1) && (xr[x] ^= mi[x] ^ v);
        mi[x] = tag[x] = v;
    }

    il void pushdown(int x) {
        if (!~tag[x]) return;
        change(ls(x), tag[x]); change(rs(x), tag[x]); tag[x] = -1;
    }

    il void init(int x, int l, int r) {
        tag[x] = -1;
        if (l == r) {
            int &v = mi[x]; read(v); sem[x] = inf; xr[x] = v; mcnt[x] = 1;
            rep1(i, 0, 30) cnt[i][x] = v >> i & 1;
            return;
        } int mid = l + r >> 1;
        init(ls(x), l, mid); init(rs(x), mid + 1, r);
        pushup(x);
    }

    il int query_xor(int x, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return xr[x];
        int mid = l + r >> 1; pushdown(x);
        return query_xor(ls(x), l, mid, ql, qr) ^ query_xor(rs(x), mid + 1, r, ql, qr);
    }

    il int query(int x, int l, int r, int ql, int qr, int k) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return cnt[k][x];
        int mid = l + r >> 1; pushdown(x);
        return query(ls(x), l, mid, ql, qr, k) + query(rs(x), mid + 1, r, ql, qr, k);
    }

    il void chkmax(int x, int l, int r, int ql, int qr, int k) {
        if (l > qr || r < ql) return;
        if (k <= mi[x]) return;
        if (l >= ql && r <= qr && k < sem[x]) return change(x, k);
        int mid = l + r >> 1; pushdown(x);
        chkmax(ls(x), l, mid, ql, qr, k); chkmax(rs(x), mid + 1, r, ql, qr, k);
        pushup(x);
    }
} T;

il int highbit(int x) {
    if (!x) return -1;
    int c = 0;
    while (x) x >>= 1, ++c;
    return c - 1;
}

int main() {
	read(n, m); T.init(1, 1, n);
	int op, l, r, x; while (m--) {
		read(op, l, r, x);
		if (op == 1) T.chkmax(1, 1, n, l, r, x);
        else {
            int v = highbit(T.query_xor(1, 1, n, l, r) ^ x);
            printf("%d\n", ~v ? T.query(1, 1, n, l, r, v) + (x >> v & 1) : 0);
        }
	}
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

容易知道我们要使得经过操作后 Nim 和为 $0$，才可以使得后手必败。

设进行游戏的石碓是 $a$，整个所有石堆的异或和为 $S$。

设在第 $i$ 堆中取 $t$ 个棋子，则要满足 $S \oplus a_i \oplus (a_i - t) = 0$，转化得，$S \oplus a_i= a_i - t$，故 $t = a_i - S \oplus a_i$

若 $t > 0$，则是一个可行的方案；即 $a_i - S \oplus a_i > 0$，即 $a_i > S \oplus a_i$。

然后我们来仔细研究一下 $x$ 什么时候才会大于 $S \oplus x$，设 $x$ 从高到低位为 $x_1, \cdots, x_l$，$S$ 从高到低位是 $s_1, \cdots, s_l$。

现在我们来考虑 $0/1$ 值域下，显然只有 $x = 1, S = 1$ 时才会满足 $x > S \oplus x$。

故若 $x > S \oplus x$，设前面有 $k$ 位相同的，即 $x_i = s_i \oplus x_i$，则 $s_i = 0$；必须有 $x_{k + 1} = 1, s_{k + 1} = 1$。

由此可得若 $x > S \oplus x$，只需要 $x_{k + 1} = 1$ 即可，即 $S$ 的二进制为 $1$ 的最高位对应 $x$ 处也要为 $1$。

现在我们就只需要支持区间取 $\max$，求区间异或和，判断区间有多少个数二进制位第 $k$ 位是 $1$。

直接区间维护 $sum_k$ 表示第 $k$ 位是 $1$ 的数的个数和区间异或和，区间最大/严格次小值，最小值的出现词素，然后吉司机线段树就做完了。

时间复杂度均摊为 $O(N \log N \log W)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 10, M = 30, INF = 2e9;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, q, op, l, r, x, ans;
int a[N];
struct Infor{
	int Min, _Min, cnt;
	int sum;
	int num[M];
	Infor(){
		memset(num, 0, sizeof(num));
		Min = _Min = cnt = sum = 0; 
	}
};
struct Node{
	int l, r;
	int tag;
	Infor data;
}X[N << 2];
inline Infor merge(Infor A, Infor B){
	Infor ans;
	ans.sum = A.sum ^ B.sum;
	ans.Min = min(A.Min, B.Min);
	if(A.Min == B.Min){
		ans.cnt = A.cnt + B.cnt;
		ans._Min = min(A._Min, B._Min); 
	}
	else{
		if(A.Min == ans.Min){
			ans.cnt = A.cnt;
			ans._Min = min(A._Min, B.Min);
		}
		else{
			ans.cnt = B.cnt;
			ans._Min = min(A.Min, B._Min);
		}
	}
	for(int i = 0; i < M; ++i)
	  ans.num[i] = A.num[i] + B.num[i];
	return ans;
}
inline void pushup(int k){
	X[k].data = merge(X[k << 1].data, X[k << 1 | 1].data);
}
inline void build(int k, int l, int r){
	X[k].l = l, X[k].r = r;
	if(l == r){
		X[k].data.cnt = 1;
		X[k].data._Min = INF; 
		X[k].data.sum = X[k].data.Min = a[l];
		for(int i = 0; i < M; ++i)
		  X[k].data.num[i] = (a[l] >> i) & 1;
		return ;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
inline void add(int k, int v){
	if(v <= X[k].data.Min || v <= X[k].tag)
	  return ;
	for(int i = 0; i < M; ++i)
	  if((X[k].data.Min >> i) & 1)
	    X[k].data.num[i] -= X[k].data.cnt;
	if(X[k].data.cnt & 1)
	  X[k].data.sum ^= X[k].data.Min;
	X[k].data.Min = v;
	for(int i = 0; i < M; ++i)
	  if((X[k].data.Min >> i) & 1)
	    X[k].data.num[i] += X[k].data.cnt;
	if(X[k].data.cnt & 1)
	  X[k].data.sum ^= X[k].data.Min;
	X[k].tag = v;
}
inline void push_down(int k){
	if(X[k].tag){
		add(k << 1, X[k].tag);
		add(k << 1 | 1, X[k].tag);
		X[k].tag = 0;
	}
}
inline void update(int k, int l, int r, int v){
	if(v <= X[k].data.Min)
	  return ;
	if(X[k].l == l && r == X[k].r && v < X[k].data._Min){
		add(k, v);
		return ;
	}
	push_down(k);
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  update(k << 1, l, r, v);
	else if(l > mid)
	  update(k << 1 | 1, l, r, v);
	else{
		update(k << 1, l, mid, v);
		update(k << 1 | 1, mid + 1, r, v);
	}
	pushup(k);
}
inline Infor query(int k, int l, int r){
	if(X[k].l == l && r == X[k].r)
	  return X[k].data;
	push_down(k);
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  return query(k << 1, l, r);
	else if(l > mid)
	  return query(k << 1 | 1, l, r);
	else
	  return merge(query(k << 1, l, mid), query(k << 1 | 1, mid + 1, r));
}
inline int get(int x){
	for(int i = M - 1; i >= 1; --i)
	  if(x & (1 << i))
	    return i;
	return 0;
}
int main(){
	n = read(), q = read();
	for(int i = 1; i <= n; ++i)
	  a[i] = read();
	build(1, 1, n);
	while(q--){
		op = read(), l = read(), r = read(), x = read();
		if(op == 1)
		  update(1, l, r, x);
		else{
			auto now = query(1, l, r);
			int sum = now.sum ^ x;
			int t = get(sum);
			if(!sum){
				puts("0");
				continue;
			}
			write(now.num[t] + ((x >> t) & 1));
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：qnqfff (赞：0)

### 思路

操作 $1$ 可以使用吉司机线段树，考虑 $2$ 操作怎么做，只要先手取完石子后异或和 $sum$ 为 $0$ 就满足条件，一个点能满足要求当且仅当这堆石子能取出 $a_i\oplus sum$，即 $a_i\ge a_i\oplus sum$，考虑拉出 $sum$ 的最高位 $pos$，只需统计第 $pos$ 位为 $1$ 的 $a_i$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){char c=getchar();int p=0,flg=1;while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,m,a[200010];struct seg{int l,r,mi,_mi,cnt,sum,_sum[31],tag;}t[800010];
#define lson now<<1
#define rson now<<1|1
void pushup(int now){
	t[now].mi=min(t[lson].mi,t[rson].mi);t[now].cnt=t[lson].cnt*(t[now].mi==t[lson].mi)+t[rson].cnt*(t[now].mi==t[rson].mi);if(t[lson].mi<t[rson].mi) t[now]._mi=min(t[lson]._mi,t[rson].mi);else if(t[lson].mi==t[rson].mi) t[now]._mi=min(t[lson]._mi,t[rson]._mi);else t[now]._mi=min(t[lson].mi,t[rson]._mi);
	t[now].sum=t[lson].sum^t[rson].sum;for(int i=0;i<=30;i++) t[now]._sum[i]=t[lson]._sum[i]+t[rson]._sum[i];
}
void build(int now,int l,int r){
	t[now]={l,r};if(l==r){t[now].mi=t[now].sum=a[l];t[now]._mi=1e18;t[now].cnt=1;for(int i=0;i<=30;i++) if(a[l]>>i&1) t[now]._sum[i]++;return ;}
	int mid=(l+r)>>1;build(lson,l,mid);build(rson,mid+1,r);pushup(now);
}
void puttag(int now,int v){
	if(t[now].mi>=v) return ;if(t[now].cnt&1) t[now].sum^=t[now].mi^v;
	for(int i=0;i<=30;i++){if(t[now].mi>>i&1) t[now]._sum[i]-=t[now].cnt;if(v>>i&1) t[now]._sum[i]+=t[now].cnt;}t[now].mi=t[now].tag=v;
}
void pushdown(int now){if(!t[now].tag) return ;puttag(lson,t[now].tag);puttag(rson,t[now].tag);t[now].tag=0;}
void modify(int now,int l,int r,int v){
	if(l<=t[now].l&&t[now].r<=r){if(t[now].mi>=v) return ;if(t[now]._mi>v){puttag(now,v);return ;}}
	pushdown(now);int mid=(t[now].l+t[now].r)>>1;if(l<=mid) modify(lson,l,r,v);if(mid<r) modify(rson,l,r,v);pushup(now);
}
int query(int now,int l,int r){
	if(l<=t[now].l&&t[now].r<=r) return t[now].sum;
	pushdown(now);int mid=(t[now].l+t[now].r)>>1,res=0;if(l<=mid) res^=query(lson,l,r);if(mid<r) res^=query(rson,l,r);return res;
}
int query(int now,int l,int r,int x){
	if(l<=t[now].l&&t[now].r<=r) return t[now]._sum[x];
	pushdown(now);int mid=(t[now].l+t[now].r)>>1,res=0;if(l<=mid) res+=query(lson,l,r,x);if(mid<r) res+=query(rson,l,r,x);return res; 
}
signed main(){
	n=read();m=read();for(int i=1;i<=n;i++) a[i]=read();build(1,1,n);
	while(m--){
		int opt=read(),l=read(),r=read(),x=read();if(!(opt^1)) modify(1,l,r,x);
		else{int sum=query(1,l,r)^x;if(!sum){cout<<0<<'\n';continue;}for(int i=30;~i;i--) if(sum>>i&1){cout<<query(1,l,r,i)+(x>>i&1)<<'\n';break;}}	
	}
	return 0;
}
```

---

## 作者：zheng_zx (赞：0)

## P9631 Just Another Game of Stones

[题目传送门](https://www.luogu.com.cn/problem/P9631)

### 分析

---

吉司机线段树 + ```Nim``` 游戏。对于一个异或和为 $x$ 的局面，需要操作成异或和为 $0$ 才能保证必胜，也就是说对于某堆大小为 $y$ 的石子，需要拿掉 $y-(x \oplus y)$ 颗石子才能满足要求。所以，合法的第一步操作数量就是满足 $y-(x \oplus y)>0$ 的石子堆的数量，移项之后得到 $y>x \oplus y$。考虑对于 $x$ 里最高的二进制位 $1$，如果 $y$ 这一位也是 $1$，显然有 $y>x \oplus y$ ，反之 $y<x \oplus y$。所以问题变为求区间的异或和，还有区间中某一个二进制位为 $1$ 的数字的数量。

考虑用线段树维护区间取 $\max$ 操作，同时每个节点维护区间的异或和，区间里每一种二进制位为 $1$ 的数字的数量，用 ```segment tree beats``` 的技巧，我们只需要维护一个区间的最小值从 $a$ 变为 $b$ 的情况，对于异或和，根据最小值的数量的奇偶性来判断是否变化。对于每一种二进制位，根据最小值和其数量进行修改即可。

---

## 作者：luan341502 (赞：0)

对于操作 $1$ 直接套上[吉司机线段树](https://oi-wiki.org/ds/seg-beats/)即可。

对于操作 $2$，考虑 nim 游戏的解决方案。

考虑异或运算，因为获得二进制下每位的奇偶情况有利于我们判断。

若异或和 $s=a_l \oplus a_{l+1} \oplus \dots \oplus a_r=0$，则先手必输。

反之后手必输。此时我们考虑取完后使 $s'=0$，设取走 $k$ 个石子，必然有 $s \oplus k \leq k$，因为这一操作的意义就是在 $k$ 上取走二进制位数上的 $1$，使本来对于所有堆来说每一位上的奇数个 $1$ 去掉 $1$ 个，变为偶数个。这样是为了使最终局面每一位上都是 $0$ 个 $1$，即率先全部取完。因此要求的就是满足 $a_i \oplus s \leq s$ 的个数，这时可以对第 $i$ 堆进行取走操作。

挂上赛时队友 [Zzzcr](https://www.luogu.com.cn/user/761491) 的代码。orz。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO {
#define _r return *this
	constexpr int S = (1 << 21), dgt = 2, ir = 1; char b[S], *p1 = b, *p2 = b, pb[S], *p = pb;
  void Fl() { fwrite(pb, 1, p - pb, stdout), p = pb; }
#define _R Fr &operator>>
  struct Fr { bool _b(char c) { return c == ' ' || c == '\n' || c == '\r' || c == '\t'; }
  char gc() { if (p1 == p2) p2 = (p1 = b) + fread(b, 1, S, stdin); return p1 == p2 ? ' ' : *p1++; }
  template <class T> _R(T &x) { char c = gc(); T f = 1;
		for (x = 0; !isdigit(c);) { if(c == '-') f = -1; c = gc(); }
    while (isdigit(c)) x = (x * 10) + (c ^ 48), c = gc(); x *= f; _r; }
  _R(char *s) { int l = 0; char c; operator>>(c); for (; !_b(c); s[l++] = c, c = gc()) ; s[l] = '\0'; _r; }
  _R(string &s) { s = ""; char c = gc(); while(_b(c)) c = gc(); while(!_b(c)) s += c, c = gc(); _r; }
	_R(double &x) { double t = 1, s = 0; char c = gc(); for (x = 0; !isdigit(c); c = gc()) s = (c == '-');
		for (; isdigit(c); c = gc()) x = x * 10 + (c - 48);
		if (c == '.') for (c = gc(); isdigit(c); c = gc()) x += (t /= 10.0) * (c - 48), s && (x = -x); _r; }
  _R(char &c) { do c = gc(); while (_b(c)); _r; } } in;
#define _W Fw &operator<<
  struct Fw { void pt(char c) { *p++ = c; if (p - pb == S) Fl(); }
  template <class T> _W(T x) { if (!x) { pt(48); _r; } x < 0 && (pt('-'), x = -x); int s[64], t = 0;
		while (x) s[++t] = x % 10, x /= 10; while (t) pt(s[t--] + 48); _r; }
  _W(char c) { pt(c); _r; }
	_W(const char *s) { operator<<((char *)s); _r; }
	_W(char *s) { int c = 0; while (s[c]) pt(s[c++]); _r; }
	_W(double x) { int k = 0; x < 0 && (pt('-'), x = -x), ir && (x += 5 * pow(10, -dgt - 1)),
  	operator<<(int(x)), pt('.'), x -= int(x);
		while (k++ < dgt) pt(int(x *= 10) + 48), x -= int(x); _r; }
	_W(string s) { for(int i = 0; s[i] != '\0'; ++i) pt(s[i]); _r; }
	~Fw() { Fl(); } } out;
} using IO::in; using IO::out; // by zzzcr
namespace zzzcr {
#define _f(i, a, b) for (int i = a; i <= b; ++i)
#define _d(i, a, b) for (int i = a; i >= b; --i)
#define l(w) t[w].l
#define r(w) t[w].r
#define m(w) t[w].m
#define mn(w) t[w].mn
#define c(w) t[w].c
#define s(w) t[w].s
#define tag(w) t[w].tag
#define sc(A) scanf("%d",&A)
#define put(A) printf("%d\n",A)
inline int ls(int p) { return p << 1; }
inline int rs(int p) { return p << 1 | 1; }
using namespace std;
constexpr int N = 2e5 + 10, inf = 1.1e9;
int n, q, a[N];
struct wy {
	int l, r, m, c, mn, s, tag, b[32];
} t[N << 2];
inline void pushup(int p)
{
	if (m(ls(p)) == m(rs(p))) {
		m(p) = m(ls(p)), c(p) = c(ls(p)) + c(rs(p));
		mn(p) = min(mn(ls(p)), mn(rs(p)));
	} else {
		if (m(ls(p)) < m(rs(p))) {
			m(p) = m(ls(p)), c(p) = c(ls(p));
			mn(p) = min(mn(ls(p)), m(rs(p)));
		} else {
			m(p) = m(rs(p)), c(p) = c(rs(p));
			mn(p) = min(mn(rs(p)), m(ls(p)));
		}
	}
	s(p) = s(ls(p)) ^ s(rs(p));
	_f(i, 0, 29) t[p].b[i] = (t[ls(p)].b[i] + t[rs(p)].b[i]);
}
inline void build(int p, int l, int r)
{
	l(p) = l, r(p) = r, tag(p) = -1;
	if (l == r) {
		m(p) = a[l], mn(p) = inf;
		c(p) = 1, s(p) = a[l];
		_f(i, 0, 29) t[p].b[i] = (a[l] >> i) & 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p), l, mid), build(rs(p), mid + 1, r);
	pushup(p);
}
inline void pushdown(int p)
{
	int x = tag(p); tag(p) = -1;
	if (m(ls(p)) < x) {
		_f(i, 0, 29) t[ls(p)].b[i] += (((x >> i) & 1) - ((m(ls(p)) >> i) & 1)) * c(ls(p));
		if (c(ls(p)) & 1)
			s(ls(p)) = s(ls(p)) ^ m(ls(p)) ^ x;
		m(ls(p)) = x, tag(ls(p)) = x;
	} if (m(rs(p)) < x) {
		_f(i, 0, 29) t[rs(p)].b[i] += (((x >> i) & 1) - ((m(rs(p)) >> i) & 1)) * c(rs(p));
		if (c(rs(p)) & 1) s(rs(p)) = s(rs(p)) ^ m(rs(p)) ^ x;
		m(rs(p)) = x, tag(rs(p)) = x;
	}
}
inline void modify(int p, int l, int r, int x)
{
	if (l <= l(p) && r >= r(p)) {
		if (m(p) >= x) return;
		if (mn(p) >= x) {
			_f(i, 0, 29) t[p].b[i] += (((x >> i) & 1) - ((m(p) >> i) & 1)) * c(p);
			if (c(p) & 1) s(p) = s(p) ^ m(p) ^ x;
			m(p) = x, tag(p) = x;
			return;
		}
	}
	int mid = (l(p) + r(p)) >> 1;
	if (tag(p) != -1) pushdown(p);
	if (l <= mid) modify(ls(p), l, r, x);
	if (r > mid) modify(rs(p), l, r, x);
	pushup(p);
}
inline int query(int p, int l, int r)
{
	if (l <= l(p) && r >= r(p)) return s(p);
	int mid = (l(p) + r(p)) >> 1;
	if (tag(p) != -1) pushdown(p);
	if (r <= mid) return query(ls(p), l, r);
	if (l > mid) return query(rs(p), l, r);
	return query(ls(p), l, r) ^ query(rs(p), l, r);
}
inline int query(int p, int l, int r, int x)
{
	if (l <= l(p) && r >= r(p)) return t[p].b[x];
	int mid = (l(p) + r(p)) >> 1;
	if (tag(p) != -1) pushdown(p);
	if (r <= mid) return query(ls(p), l, r, x);
	if (l > mid) return query(rs(p), l, r, x);
	return query(ls(p), l, r, x) + query(rs(p), l, r, x);
}
int main()
{
	in >> n >> q;
	_f(i, 1, n) in >> a[i];
	build(1, 1, n);
	_f(i, 1, q)
	{
		int op, l, r, x;
		in >> op >> l >> r >> x;
		if (op & 1) modify(1, l, r, x);
		else {
			int ret = query(1, l, r) ^ x, res;
			if (!ret) {
				out << 0 << '\n';
				continue;
			}
			_f(j, 0, 29) if ((ret >> j) & 1) res = j;
			out << query(1, l, r, res) + ((x >> res) & 1) << '\n';
		}
	}
	return 0;
}} // namespace zzzcr
signed main() { zzzcr::main(); return 0; }
```


---

