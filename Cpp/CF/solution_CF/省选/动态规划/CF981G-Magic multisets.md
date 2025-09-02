# Magic multisets

## 题目描述

In the School of Magic in Dirtpolis a lot of interesting objects are studied on Computer Science lessons.

Consider, for example, the magic multiset. If you try to add an integer to it that is already presented in the multiset, each element in the multiset duplicates. For example, if you try to add the integer $ 2 $ to the multiset $ \{1, 2, 3, 3\} $ , you will get $ \{1, 1, 2, 2, 3, 3, 3, 3\} $ .

If you try to add an integer that is not presented in the multiset, it is simply added to it. For example, if you try to add the integer $ 4 $ to the multiset $ \{1, 2, 3, 3\} $ , you will get $ \{1, 2, 3, 3, 4\} $ .

Also consider an array of $ n $ initially empty magic multisets, enumerated from $ 1 $ to $ n $ .

You are to answer $ q $ queries of the form "add an integer $ x $ to all multisets with indices $ l, l + 1, \ldots, r $ " and "compute the sum of sizes of multisets with indices $ l, l + 1, \ldots, r $ ". The answers for the second type queries can be large, so print the answers modulo $ 998244353 $ .

## 说明/提示

In the first example after the first two queries the multisets are equal to $ [\{1, 2\},\{1, 2\},\{\},\{\}] $ , after the third query they are equal to $ [\{1, 1, 2, 2\},\{1, 1, 2, 2\},\{1\},\{1\}] $ .

In the second example the first multiset evolves as follows:

 $ \{\} \to \{3\} \to \{3, 3\} \to \{2, 3, 3\} \to \{1, 2, 3, 3\} \to \{1, 1, 2, 2, 3, 3, 3, 3\} $ .

## 样例 #1

### 输入

```
4 4
1 1 2 1
1 1 2 2
1 1 4 1
2 1 4
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 7
1 1 1 3
1 1 1 3
1 1 1 2
1 1 1 1
2 1 1
1 1 1 2
2 1 1
```

### 输出

```
4
8
```

# 题解

## 作者：xfrvq (赞：7)

[$\tt Link$](/problem/CF981G)。

考虑一个集合的 $\tt size$ 在一次操作后发生的变化

+ 如果集合原来就有这个数：$\mathtt{size}\gets\mathtt{size}\times2$。
+ 如果集合原来没有这个数：$\mathtt{size}\gets\mathtt{size}+1$。

区间 $+1$ 区间 $\times2$，可以使用线段树维护。

现在问题就是在 $[L,R]$ 中按照原来是否有 $x$ 分成一些子区间，然后分别处理。

考虑对每个颜色维护一棵 $\tt ODT$ 其值域为 $v\in\{0,1\}$（用这个来找到每个区间是需要 $+1$ 还是 $\times2$）。

+ 第 $x$ 棵 $\tt ODT$ 的节点 $\{l,r,0\}$ 代表 $[l,r]$ 的集合都不包含 $x$。
+ 第 $x$ 棵 $\tt ODT$ 的节点 $\{l,r,1\}$ 代表 $[l,r]$ 的集合都包含 $x$ 。

初始化每棵 $\tt ODT$ 都是 $\{1,n,0\}$。

修改：先完成 $\tt split$，然后对于 $v=0$ 在线段树上 $+1$，$v=1$ 就在线段树上 $\times2$。

其实挺好写的。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e5 + 5;
const int S = N << 2;
const int mod = 998244353;

int n,q;

namespace sgt{
	int T[S];
	int tag0[S],tag1[S];
	
	#define lc (i << 1)
	#define rc (i << 1 | 1)
	#define mid (L + R >> 1)
	#define ls lc,L,mid
	#define rs rc,mid + 1,R
	#define cur i,L,R
	#define id int i = 1,int L = 1,int R = n
	
	#define psu T[i] = (T[lc] + T[rc]) % mod
	
	void chg0(int i,int x){
		T[i] = 1LL * T[i] * x % mod;
		tag0[i] = 1LL * tag0[i] * x % mod;
		tag1[i] = 1LL * tag1[i] * x % mod;
	}
	
	void chg1(int i,int L,int R,int x){
		T[i] = (0LL + T[i] + 1LL * x * (R - L + 1) % mod) % mod;
		tag1[i] = (tag1[i] + x) % mod;
	}
	
	void psd(id){
		if(tag0[i] != 1){
			chg0(lc,tag0[i]);
			chg0(rc,tag0[i]);
			tag0[i] = 1;
		}
		if(tag1[i] != 0){
			chg1(ls,tag1[i]);
			chg1(rs,tag1[i]);
			tag1[i] = 0;
		}
	}
	
	void build(id){
		tag0[i] = 1,tag1[i] = 0;
		if(L == R) return;
		build(ls); build(rs);
	}
	
	void upd0(int l,int r,id){
		if(l <= L && R <= r) return chg0(i,2),void();
		psd(cur); if(l <= mid) upd0(l,r,ls);
		if(r > mid) upd0(l,r,rs); psu;
	}
	
	void upd1(int l,int r,id){
		if(l <= L && R <= r) return chg1(cur,1),void();
		psd(cur); if(l <= mid) upd1(l,r,ls);
		if(r > mid) upd1(l,r,rs); psu;
	}
	
	ll qry(int l,int r,id){
		if(l <= L && R <= r) return T[i]; psd(cur);
		ll res = 0;
		if(l <= mid) res = qry(l,r,ls);
		if(r > mid) (res += qry(l,r,rs)) %= mod;
		return res;
	}
}

namespace odt{
	struct node{
		int l,r;
		mutable bool v;
		node(int l,int r = 0,int v = 0) : l(l),r(r),v(v){}
		bool operator<(const node& p) const { return l < p.l; }
	};
	
	set<node> s[N];
	
	void build(){
		for(int i = 1;i <= n;++i)
			s[i].insert(node(1,n,0));
	}
	
	set<node>::iterator split(int p,int i){
		auto it = s[i].upper_bound(node(p));
		--it;
		if(it->l > p || it->r < p) return s[i].end();
		if(it->l == p) return it;
		int l = it->l,r = it->r; bool v = it->v;
		s[i].erase(it);
		s[i].insert(node(l,p - 1,v));
		return s[i].insert(node(p,r,v)).first;
	}
	
	void upd(int l,int r,int x){
		auto ir = split(r + 1,x),il = split(l,x);
		for(auto it = il;it != ir;++it)
			it->v ? sgt::upd0(it->l,it->r) : sgt::upd1(it->l,it->r);
		s[x].erase(il,ir); s[x].insert(node(l,r,1));
	}
}

int main(){
	scanf("%d%d",&n,&q);
	sgt::build();
	odt::build();
	int t = 0;
	while(q--){
		int op,l,r,x;
		scanf("%d%d%d",&op,&l,&r);
		if(op == 1){
			scanf("%d",&x);
			odt::upd(l,r,x);
		} else printf("%lld\n",sgt::qry(l,r));
	}
	return 0;
}
```

---

## 作者：walk_alone (赞：5)

区间修改+区间查询——线段树没得跑了。

首先先搞一个最暴力的做法：开一个 $n^2$ 的大 bool 数组，或者 $n$ 个长度为 $n$ 的 bitset，一行表示一个数在哪些区间有哪些区间没有。每次修改的时候依次去查这个区间有没有这个数，来决定到底是 $\times 2$ 还是 $+1$。（那你这还不如不用线段树直接暴力修改得了，反正都要落实到叶节点的，复杂度还少一个 $\log n$）。

暴力肯定是不用继续往下想了，所以我们要更优化的方法。注意到我们都是区间操作，那我们可以只用**区间端点**表示一个数的有无。举个例子，对于数字$5$，如果我们有区间 $[1,3],[5,7],[9,9]$，这表示我们在区间 $[1,3],[5,7],[9,9]$ 上都有数字 $5$，而第 $4,8$ 个集合没有数字 $5$。那么这样我们就可以用一个 pair 来记录一个区间而非很多个 01 位，同时用一个 set 去存储、维护这些区间。所以我们一共需要维护 $n$ 个 set 里面的若干的区间。



区间查询没什么好说的，直接线段树一拉就好了。主要是修改怎么办。

显然我们下来的也是个区间，那么就会和我们对应的 set 里已经有的区间产生交集关系。之后我们得让这次修改的区间去和已经有的区间进行合并操作。这是官方题解的思路，用的并查集维护。个人觉得这个方法过于繁琐，因而讲另外一个方法。

这次我们反选——我们记录尚未有这个数的区间。初始的时候所有的都是$[1,n]$表示全部都是空集。来了一个区间，相当于执行的是区间拆分操作——将已经有的区间断开。虽然一般意义上拆分比合并要麻烦，但是在这里情况刚好是反过来。

考虑以下两种情况（下文用数字来代表对应位置）：

1、区间不完全包含：

$$\cdots a_4\overbrace{a_5a_6a_7a_8}^\text{ 原始区间}a_9 a_{10} \cdots$$

此时需要添加 $[7,10]$。考虑将原始区间拆分成 $[5,6]$ 与 $[7,8]$。然后现在所有有的区间要么没有交集要么完整覆盖，转进下一种情况：

2、区间完全包含：直接从 set 里移走这个区间即可。

在具体实现上，我们先对区间整体 $\times 2$，然后对于存在的区间，该段 $/2 +1$ ，然后将区间删除。这样代码实现会简单很多。

```cpp
#include <cstdio>
#include <algorithm>
#include <set>
#include <utility>
using namespace std;
const long long mod = 998244353LL, inv = 499122177LL;
struct node
{
    long long sum;
    long long addtag;
    long long multag;
};
struct node t[800005];
set<pair<int, int>> noexist[200005];//set维护的区间

//线段树，没啥好说的
void build(int place,int left,int right)
{
    t[place].multag = 1;
    if(left==right)
        return;
    int mid = (left + right) >> 1;
    build(place << 1, left, mid);
    build(place << 1 | 1, mid + 1, right);
    t[place].sum = (t[place << 1].sum + t[place << 1 | 1].sum) % mod;
}
void pushdown(int place,int left,int right)
{
    if(t[place].multag!=1)
    {
        t[place << 1].multag = (t[place << 1].multag * t[place].multag) % mod;
        t[place << 1 | 1].multag = (t[place << 1 | 1].multag * t[place].multag) % mod;
        t[place << 1].addtag = (t[place << 1].addtag * t[place].multag) % mod;
        t[place << 1 | 1].addtag = (t[place << 1 | 1].addtag * t[place].multag) % mod;
        t[place << 1].sum = (t[place << 1].sum * t[place].multag) % mod;
        t[place << 1 | 1].sum = (t[place << 1 | 1].sum * t[place].multag) % mod;
        t[place].multag = 1;
    }
    if(t[place].addtag)
    {
        t[place << 1].addtag = (t[place << 1].addtag + t[place].addtag) % mod;
        t[place << 1 | 1].addtag = (t[place << 1 | 1].addtag + t[place].addtag) % mod;
        int mid = (left + right) >> 1;
        t[place << 1].sum = (t[place << 1].sum + (mid - left + 1) * t[place].addtag) % mod;
        t[place << 1 | 1].sum = (t[place << 1 | 1].sum + (right - mid) * t[place].addtag) % mod;
        t[place].addtag = 0;
    }
    return;
}
void change(int place,int left,int right,int start,int end,long long mulx,long long addx)//乘+加一体的修改操作，先乘后加。如果只乘2就*2+0，如果只加1不乘就*1+1
{
    if(start<=left && right<=end)
    {
        t[place].multag = (t[place].multag * mulx) % mod;
        t[place].sum = (t[place].sum * mulx) % mod;
        t[place].addtag = (t[place].addtag * mulx) % mod;
        t[place].sum = (t[place].sum + (long long)(right - left + 1) * addx % mod) % mod;
        t[place].addtag = (t[place].addtag + addx) % mod;
        return;
    }
    pushdown(place, left, right);
    int mid = (left + right) >> 1;
    if(start<=mid)
        change(place << 1, left, mid, start, end, mulx, addx);
    if(end>mid)
        change(place << 1 | 1, mid + 1, right, start, end, mulx, addx);
    t[place].sum = (t[place << 1].sum + t[place << 1 | 1].sum) % mod;
}
long long query(int place,int left,int right,int start,int end)
{
    if(left>right)
        return 0;
    if(start<=left && right<=end)
        return t[place].sum;
    pushdown(place, left, right);
    int mid = (left + right) >> 1;
    long long ans = 0;
    if(start<=mid)
        ans = (ans + query(place << 1, left, mid, start, end)) % mod;
    if(end>mid)
        ans = (ans + query(place << 1 | 1, mid + 1, right, start, end)) % mod;
    return ans;
}
void split(int x,int place)//断开区间的操作，即类型1。
{
    auto iter = lower_bound(noexist[x].begin(), noexist[x].end(), make_pair(place, place));//由于lower_bound的特性，找到的是待修改的后一个，因而要往前跳一个
    if(iter==noexist[x].begin())
        return;
    iter--;
    pair<int, int> temp = *(iter);
    if(temp.second>=place)
    {
        noexist[x].erase(iter);//原始区间记得删除，因为已经分裂成两个子区间了
        if(temp.first<place)
            noexist[x].insert(make_pair(temp.first, place - 1));//如果开头区间都不比place小，那么证明这个区间一个数都不含，直接删去不必再添加到set中
        noexist[x].insert(make_pair(place, temp.second));//后段区间必加
    }
}
int main()
{
    int n, q, op, l, r, x;
    scanf("%d%d", &n, &q);
    build(1, 1, n);
    for (int i = 1; i <= n;i++)
        noexist[i].insert(make_pair(1, n));
    while(q--)
    {
        scanf("%d", &op);
        if(op==1)
        {
            scanf("%d%d%d", &l, &r, &x);
            split(x, l);
            split(x, r + 1);
            change(1, 1, n, l, r, 2, 0);
            while(1)//从前到后找本次待修改区间中有哪些set里的区间是完整覆盖的，这些区间执行完+1后要全部删除
            {
                auto iter = lower_bound(noexist[x].begin(), noexist[x].end(), make_pair(l, l));
                if(iter==noexist[x].end() || iter->first>r)
                    break;
                change(1, 1, n, iter->first, iter->second, inv, 1);
                noexist[x].erase(iter);
            }
        }
        else//朴素的区间查询
        {
            scanf("%d%d", &l, &r);
            printf("%lld", query(1, 1, n, l, r));
            printf("\n");
        }
    }
    return 0;
}
```


---

## 作者：Terac (赞：4)

$\texttt{update 2022.10.25}$
修改了下格式。

[$\texttt{link}$](https://www.luogu.com.cn/problem/CF981G)

## 题意

给定 $n$ 个可重集，初始为空。向可重集中加入一个正整数 $x$，如果  $x$ 已经在该可重集出现，则可重集中每一个元素出现次数翻倍，否则直接加入。

$q$ 次操作：
- 下标在 $\left[l,r\right]$ 的可重集加入数 $x$

- 查询下标在 $\left[l,r\right]$ 的可重集大小的和，对 $998244353$ 取模。

数据范围：$1\le n,q\le2\times 10^5,1\le x\le n$

## 题解

这个题跟 [P8416](https://www.luogu.com.cn/problem/P8146) 处理方法有点像。

有 $1\le x\le n$，考虑每个 $x$ 分开处理，用 $0$ 和 $1$ 表示可重集中有没有 $x$。

这个问题相当于给定一个序列，加入数 $x$ 相当于把序列区间推平成 $1$。

这种区间推平问题很自然地想到颜色段均摊，即 ODT。

有个很经典的 trick 就是用 ODT 把区间推平转成区间加。

于是我们开 $n$ 棵珂朵莉树维护集合是否有 $x$，再用一棵线段树维护集合大小的和即可。

这个题可以先把区间的集合大小乘 $2$，再把序列上为 $0$ 的数除以 $2$ 再加 $1$，所以用线段树维护区间乘区间加即可。

然后这个复杂度的正确性，因为颜色段均摊每次 `split` 最多增加 $O(1)$ 个区间，每个区间删除 $O(1)$ 次，因为最多 $q$ 次操作，所以区间总数是 $O(q)$ 级别的，所以总时间复杂度为 $O(n+q\log n)$。

注意 `split` 要先分裂 $r+1$，不然可能会越界，经典错误了属于是。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, mod = 998244353, inv2 = mod + 1 >> 1;
int n, q;
namespace segment_tree {
	#define ls x << 1
	#define rs x << 1 | 1
	int tagm[N << 2], taga[N << 2], sum[N << 2];
	void build(int x, int l, int r) {
		if(l == r) return;
		int mid = l + r >> 1;
		taga[x] = 0, tagm[x] = 1;
		build(ls, l, mid), build(rs, mid + 1, r);
	}
	void pushup(int x) { sum[x] = (sum[ls] + sum[rs]) % mod; }
	void pusha(int x, int l, int r, int v) {
		if(!v) return;
		taga[x] = (taga[x] + v) % mod;
		sum[x] = (sum[x] + 1ll * (r - l + 1) * v) % mod;
	}
	void pushm(int x, int v) {
		if(v == 1) return;
		tagm[x] = 1ll * tagm[x] * v % mod;
		taga[x] = 1ll * taga[x] * v % mod;
		sum[x] = 1ll * sum[x] * v % mod;
	}
	void pushdown(int x, int l, int r) {
		int mid = l + r >> 1;
		pushm(ls, tagm[x]), pushm(rs, tagm[x]);
		tagm[x] = 1;
		pusha(ls, l, mid, taga[x]), pusha(rs, mid + 1, r, taga[x]);
		taga[x] = 0;
	}
	void updatea(int x, int l, int r, int L, int R, int v) {
		if(L <= l && r <= R) { pusha(x, l, r, v); return; }
		pushdown(x, l, r);
		int mid = l + r >> 1;
		if(mid >= L) updatea(ls, l, mid, L, R, v);
		if(mid < R) updatea(rs, mid + 1, r, L, R, v);
		pushup(x);
	}
	void updatem(int x, int l, int r, int L, int R, int v) {
		if(L <= l && r <= R) { pushm(x, v); return; }
		pushdown(x, l, r);
		int mid = l + r >> 1;
		if(mid >= L) updatem(ls, l, mid, L, R, v);
		if(mid < R) updatem(rs, mid + 1, r, L, R, v);
		pushup(x);
	}
	int query(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return sum[x];
		pushdown(x, l, r);
		int mid = l + r >> 1, res = 0;
		if(mid >= L) res = (res + query(ls, l, mid, L, R)) % mod;
		if(mid < R) res = (res + query(rs, mid + 1, r, L, R)) % mod;
		return res;
	}
} using namespace segment_tree;
struct old_driver_tree {
	struct odt {
		int l, r;
		mutable int v;
		odt(int L = 0, int R = 0, int V = 0) { l = L, r = R, v = V; }
		friend bool operator < (const odt &qwq, const odt &awa) {
			return qwq.l < awa.l;
		}
	};
	set<odt> s;
	void init() { s.insert(odt(1, n)); }
	#define IT set<odt>::iterator
	#define pii pair<int, int>
	IT split(int x) {
		IT it = s.lower_bound(odt(x, 0, 0));
		if(it != s.end() && it -> l == x) return it;
		--it;
		int L = it -> l, R = it -> r, V = it -> v;
		s.erase(it);
		s.insert(odt(L, x - 1, V));
		return s.insert(odt(x, R, V)).first;
	}
	void assign(int l, int r) {
		updatem(1, 1, n, l, r, 2);
		IT itr = split(r + 1), itl = split(l);
		for(IT it = itl; it != itr; ++it)
			if(!(it -> v))
           updatem(1, 1, n, it -> l, it -> r, inv2),
				updatea(1, 1, n, it -> l, it -> r, 1);
		s.erase(itl, itr);
		s.insert(odt(l, r, 1));
	}
} t[N];
int main() {
	scanf("%d%d", &n, &q);
	build(1, 1, n);
	for(int i = 1; i <= n; i++)
		t[i].init();
	while(q--) {
		int opt, l, r, x;
		scanf("%d%d%d", &opt, &l, &r);
		if(opt == 1) {
			scanf("%d", &x);
			t[x].assign(l, r); 
		}
		
		else printf("%d\n", query(1, 1, n, l, r));
	}
	return 0;
}
```


---

## 作者：SunsetSamsara (赞：3)

## 题意

有 $n$ 个可重集，修改和询问操作为：

1. 操作表示为 $1\ l\ r\ x$，对于在 $l$ 到 $r$ 的每一个可重集，如果存在 $x$，则所有元素的数量翻倍，否则加入 $x$

2. 询问表现为 $2\ l\ r$，查询 $l$ 到 $r$ 的可重集大小之和。

$n \le 2 \times 10^5,\ q\le 2 \times 10^5$

## 分析

乍看上去，这道题的空间似乎要 $O(n^2)$ 才能存的下整整 $n$ 个可重集的空间。那么，有什么不需要 $O(n^2)$ 空间的数据结构，能够存下这些信息呢？显然有珂朵莉树和动态开点线段树。在这道题中，我用的是珂朵莉树（动态开点似乎也能做，但细节更多，好像没人写）。

开 $n$ 棵珂朵莉树，每棵珂朵莉树维护一个值在一段区间的可重集内的出现情况。这样的话，插入操作就会变成区间把一个值赋为 $1$。于是，如何维护修改就很明显了：在第 $x$ 珂朵莉树上遍历一段区间，如果当前的连续区间值为 $1$，那么这段区间在所有珂朵莉树上的大小就都乘上 $2$，否则这段区间在所有珂朵莉树上的大小都加上 $1$。至于这个乘 $2$ 和加 $1$ 的操作嘛，使用线段树维护就可以了。

## 代码

```cpp
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <set>
using std::set;
#define lld long long
template<typename Tp>
inline const Tp &min(register const Tp &x, register const Tp &y) { return x < y ? x : y; }
template<typename Tp>
inline const Tp &max(register const Tp &x, register const Tp &y) { return x < y ? y : x; }
template<typename Tp>
inline void swap(register Tp &x, register Tp &y) { static Tp t; t = x, x = y, y = t; }
int n, q;
struct node { int l, r, v; };
inline bool operator < (const node &x, const node &y) { return x.l < y.l; }
#define iter set<node>::iterator
const lld mod = 998244353;
set<node> s[200010];
iter split(int id, int x) {
	iter it = s[id].lower_bound((node){x, 0, 0});
	if (it != s[id].end() && it -> l == x) return it;
	-- it;
	int l = it -> l, r = it -> r, v = it -> v;
	s[id].erase(it);
	s[id].insert((node){l, x - 1, v});
	it = s[id].insert((node){x, r, v}).first;
	return it;
}
struct segment {
	int l, r;
	lld s, add, mul;
} tr[800010];
void pushup(int k) {
	tr[k].s = (tr[k << 1].s + tr[k << 1 | 1].s) % mod;
}
void update1(int k, lld add) {
	tr[k].s = (tr[k].s + add * (tr[k].r - tr[k].l + 1)) % mod;
	tr[k].add = (tr[k].add + add) % mod;
}
void update2(int k, lld mul) {
	tr[k].s = (tr[k].s * mul) % mod;
	tr[k].add = (tr[k].add * mul) % mod;
	tr[k].mul = (tr[k].mul * mul) % mod;
}
void update(int k, lld add, lld mul) {
	update2(k, mul);
	update1(k, add);
}
void pushdown(int k) {
	if (tr[k].l != tr[k].r) {
		update(k << 1, tr[k].add, tr[k].mul);
		update(k << 1 | 1, tr[k].add, tr[k].mul);
		tr[k].add = 0, tr[k].mul = 1;
	}
}
void build(int k, int l, int r) {
	tr[k].l = l, tr[k].r = r, tr[k].add = 0, tr[k].mul = 1;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
}
void modify1(int k, int l, int r, lld s) {
	if (l <= tr[k].l && tr[k].r <= r) {
		tr[k].add = (tr[k].add + s) % mod;
		tr[k].s = (tr[k].s + s * (tr[k].r - tr[k].l + 1) % mod) % mod;
		return;
	}
	pushdown(k);
	int mid = (tr[k].l + tr[k].r) >> 1;
	if (l <= mid) modify1(k << 1, l, r, s);
	if (mid < r) modify1(k << 1 | 1, l, r, s);
	pushup(k);
}
void modify2(int k, int l, int r, lld s) {
	if (l <= tr[k].l && tr[k].r <= r) {
		tr[k].add = (tr[k].add * s) % mod;
		tr[k].mul = (tr[k].mul * s) % mod;
		tr[k].s = (tr[k].s * s) % mod;
		return;
	}
	pushdown(k);
	int mid = (tr[k].l + tr[k].r) >> 1;
	if (l <= mid) modify2(k << 1, l, r, s);
	if (mid < r) modify2(k << 1 | 1, l, r, s);
	pushup(k);
}
void assign(int l, int r, int id) {
	iter itr = split(id, r + 1), itl = split(id, l), tl = itl;
	for (; itl != itr; ++ itl) {
		if (itl -> v) modify2(1, itl -> l, itl -> r, 2);
		else modify1(1, itl -> l, itl -> r, 1);
	}
	s[id].erase(tl, itr);
	s[id].insert((node){l, r, 1});
}
lld query(int k, int l, int r) {
	if (l <= tr[k].l && tr[k].r <= r) return tr[k].s;
	int mid = (tr[k].l + tr[k].r) >> 1;
	lld res = 0;
	pushdown(k);
	if (l <= mid) res = query(k << 1, l, r);
	if (mid < r) res = (res + query(k << 1 | 1, l, r)) % mod;
	return res;
}
int main() {
	scanf("%d%d", &n, &q);
	build(1, 1, n);
	for (int i = 1; i <= n; ++ i) s[i].insert((node){1, n, 0});
	for (int op, l, r, k; q --; ) {
		scanf("%d%d%d", &op, &l, &r);
		if (r < l) swap(l, r);
		if (op == 1) {
			scanf("%d", &k);
			assign(l, r, k);
		} else printf("%d\n", query(1, l, r));
	}
}
```

---

## 作者：_Yonder_ (赞：2)

我永远喜欢珂朵莉！

看到区间查询，区间修改，很容易想到线段树。但是题目的加入操作，看起来就不像懒标记可以维护的，所以肯定要再套一个数据结构，他要满足以下操作：

* 区间对没出现过 $x$，和出现过 $x$ 的可重集分别进行操作。

* 区间标记某个数在其中所有的可重集内都出现过了。

看到后者，你能想到什么？没错，就是珂朵莉树！那么这题就很简单啦，我们只需建 $n$ 个珂朵莉树就可以了，时间复杂度 $O(q\log n)$，应该不需要数据随机？
# Code
```
#include<bits/stdc++.h>
#define S std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define rep(i,l,r) for(register int i=l;i<=r;i++)
#define per(i,l,r) for(register int i=l;i>=r;i--)
#define ll long long
#define itset set<node>::iterator
using namespace std;
template<typename P>inline void read(P&x){bool f=0;x=0;char c=getchar();while(!isdigit(c)) f|=c=='-',c=getchar();while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();x=f?~(x-1):x;}
template<typename P>inline void write(P x){if(x<0) putchar('-'),x=-x;if(x>9) write(x/10);putchar((x%10)^48);}
const int N=2e5+5,mod=998244353;
int tr[N<<2],add[N<<2],mul[N<<2];
int n,q,op,l,r,x;
inline void ca(int p,int pl,int pr,int d){tr[p]=(tr[p]+(pr-pl+1)*1ll*d%mod)%mod;add[p]=(add[p]+d)%mod;}
inline void cm(int p,int d){tr[p]=(tr[p]*1ll*d)%mod;mul[p]=(mul[p]*1ll*d)%mod;add[p]=(add[p]*1ll*d)%mod;}
inline void push_up(int p){tr[p]=(tr[p<<1]+tr[p<<1|1])%mod;}
inline void push_down(int p,int pl,int pr){
	int mid=pl+pr>>1;if(mul[p]^1) cm(p<<1,mul[p]),cm(p<<1|1,mul[p]),mul[p]=1;
	if(add[p]) ca(p<<1,pl,mid,add[p]),ca(p<<1|1,mid+1,pr,add[p]),add[p]=0;
}inline void change(int l,int r,int op,int p=1,int pl=1,int pr=n){
	if(l<=pl&&pr<=r){op?ca(p,pl,pr,1):cm(p,2);return;}
	int mid=pl+pr>>1;push_down(p,pl,pr);
	if(l<=mid) change(l,r,op,p<<1,pl,mid);
	if(r>mid) change(l,r,op,p<<1|1,mid+1,pr);
	push_up(p);
}inline int ask(int l,int r,int p=1,int pl=1,int pr=n){
	if(l<=pl&&pr<=r) return tr[p];int mid=pl+pr>>1,ans=0;
	push_down(p,pl,pr);
	if(l<=mid) ans=ask(l,r,p<<1,pl,mid);
	if(r>mid) ans=(ans+ask(l,r,p<<1|1,mid+1,pr))%mod;
	return ans;
}
struct node{
    int l,r;mutable int v;
    node(int L,int R=-1,int V=0):l(L),r(R),v(V){}
    bool operator<(const node&b)const{return l<b.l;}
};
struct Chtholly{//我永远喜欢珂朵莉！
    set<node> s;
	inline itset split(int pos){
		itset it=s.lower_bound(node(pos));
		if(it!=s.end()&&it->l==pos) return it;
		it--;if(it->r<pos) return s.end();
		int l=it->l,r=it->r,v=it->v;
		s.erase(it);s.insert(node(l,pos-1,v));
		return s.insert(node(pos,r,v)).first;
	}inline void assign(int l,int r){
		itset rit=split(r+1),lit=split(l);
		for(itset it=lit;it!=rit;it++)
			change(it->l,it->r,!it->v);
		s.erase(lit,rit);s.insert(node(l,r,1));
	}
}c[N];
int main(){
	S;cin>>n>>q;memset(mul,1,sizeof(mul));
	for(register int i=1;i<=n;i++) c[i].s.insert(node(1,n));
	while(q--){
		cin>>op>>l>>r;
		if(op&1) cin>>x,c[x].assign(l,r);
		else cout<<ask(l,r)<<endl;
	}
	return 0;
}
```

---

## 作者：qfpjm (赞：2)

# 题解

- 这是一道线段树结合 ODT 的题。

- 对于向区间中的集合中加入 `x`，我们 ODT 来维护对于每一个集合，加入 `x` 是对集合大小进行 $+1$ 还是 $\times 2$ 操作。

- 对于这个 $+1,\times 2$ 的操作，我们用线段树维护即可。

- ODT 中 `v` 的值域为 $\{1,0\}$，对于每个集合的初始化为 $\{1,n,0\}$（我曾因为漏写半天找不出错）。

- 代码也十分好些，ODT 只有 `split` 和一个简单的判断函数，线段树几乎就是模板。

# 代码

```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for(register int i = a; i <= b; ++i)

using namespace std;
 
const int maxn = 2e5 + 5, mod = 998244353;

struct node
{
    int l; mutable int r, v;
    node(int L = 0, int R = -1, int V = 0){l = L, r = R, v = V;}
    inline bool operator <(const node &x) const{return l < x.l;} 
}; set <node> t[maxn];

int n, q;

struct segment_tree
{
    #define ls (x<<1)
    #define rs (x<<1|1)
    #define m(x) a[x].ml
    #define d(x) a[x].ad
    #define s(x) a[x].sum
    struct tree
    {
        int sum, ml, ad;
    }a[maxn << 2];
    inline void up(int x)
    {
        a[x].sum = (a[ls].sum + a[rs].sum) % mod;
    }
    inline void build(int x, int l, int r)
    {
        a[x].ml = 1; 
		if(l == r)
			return;
        int mid = l + r >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
    }
    inline void dw(int x, int l, int r)
    {
        if(m(x) != 1)
        {
            m(ls) = 1ll * m(ls) * m(x) % mod, m(rs) = 1ll * m(rs) * m(x) % mod;
            d(ls) = 1ll * d(ls) * m(x) % mod, d(rs) = 1ll * d(rs) * m(x) % mod;
            s(ls) = 1ll * s(ls) * m(x) % mod, s(rs) = 1ll * s(rs) * m(x) % mod;
            m(x) = 1;
        } 
        if(d(x))
        { int mid = l + r >> 1;
            d(ls) = (d(ls) + d(x)) % mod, d(rs) = (d(rs) + d(x)) % mod;
            s(ls) = (s(ls) + 1ll * d(x) * (mid - l + 1) % mod) % mod;
            s(rs) = (s(rs) + 1ll * d(x) * (r - mid) % mod) % mod;   
            d(x) = 0;
        }
    }
    inline void add(int x, int l, int r, int L, int R)
    {
        if(l >= L and r <= R)
        {
            d(x) = (d(x) + 1) % mod, s(x) = (s(x) + r - l + 1) % mod; return;
        } 
        int mid = l + r >> 1; dw(x, l, r);
        if(L <= mid)
			add(ls, l, mid, L, R); 
		if(R > mid) 
			add(rs, mid + 1, r, L, R);
        up(x);
    }
    inline void mul(int x, int l, int r, int L, int R)
    {
        if(l >= L and r <= R)
        {
            m(x) = 2ll * m(x) % mod, s(x) = 2ll * s(x) % mod, d(x) = 2ll * d(x) % mod;
            return;
        } 
        int mid = l + r >> 1; dw(x, l, r);
        if(L <= mid) 
			mul(ls, l, mid, L, R); 
		if(R > mid) 
			mul(rs, mid + 1, r, L, R);
        up(x);
    }
    inline int qry(int x, int l, int r, int L, int R)
    {
        if(l >= L and r <= R) 
			return s(x);
        int mid = l + r >> 1, ans = 0; dw(x, l, r);
        if(L <= mid) 
			ans = (ans + qry(ls, l, mid, L, R)) % mod; 
        if(R > mid) 
			ans = (ans + qry(rs, mid + 1, r, L, R)) % mod;
        up(x); 
		return ans;
    }
}T;
 
set <node> :: iterator split(int pos, int k)
{
    set <node> :: iterator it = t[k].lower_bound(node(pos));
    if(it != t[k].end() and it->l == pos) 
		return it;
    it--; 
    int v = it->v, r = it->r; it->r = pos - 1;
    return t[k].insert(node(pos, r, v)).first;
}
 
inline void mdf(int k, int l, int r)
{
    set <node> :: iterator itr = split(r + 1, k), itl = split(l, k);
    for(set <node> :: iterator it = itl; it != itr; ++it)
        if(it->v) 
			T.mul(1, 1, n, it->l, it->r);
        else 
			T.add(1, 1, n, it->l, it->r);
    t[k].erase(itl, itr);
	t[k].insert(node(l, r, 1));
}
 
int main()
{
    scanf("%d%d", &n, &q);
    rep(i, 1, n)
		t[i].insert(node(1, n + 1));
    T.build(1, 1, n);
    while(q--)
    { 
        int opt, l, r, k;
        scanf("%d%d%d", &opt, &l, &r);
        if(opt == 1)
			scanf("%d", &k), mdf(k, l, r);
        else
			printf("%d\n", T.qry(1, 1, n, l, r));      
    }
    return 0;
}
```


---

## 作者：_lgh_ (赞：1)

**[题目传送门](https://www.luogu.com.cn/problem/CF981G)**

考虑对于每个可重集，添加怎么维护 size。对于一个可重集，如果这个数存在，那么 size 乘二，否则 size 加一。

因为是对一段添加并且值域为 $n$，所以容易想到用 ODT 来维护数 $x$ 是否存在。如果某一段的值为 0，就对这一段区间加。否则，就区间乘 2。线段树实现即可。

容易犯错的是没有保证 ODT 的复杂度正确，即在 ODT 上跳完之后没有将遍历的区间推平。

代码很好写。

[code](https://codeforces.com/contest/981/submission/230921147).

---

## 作者：orz_z (赞：0)

### CF981G Magic multisets

近似某月赛 `E` 题 `risrqnis`。

首先想到树套树，空间爆炸，排除。

用一棵线段树维护区间集合答案，支持 $\times 2$ 和 $+1$ 操作。

怎样维护区间集合添加操作呢，观察到加的数都是同一个数，考虑一个数据结构，建 $n$ 个，维护每个颜色的出现区间，加数即区间推平。

考虑到经典 `trick` 颜色端均摊，即 `ODT`，每次推平最多增加 $\mathcal O(1)$ 个区间，每个区间删除 $\mathcal O(1)$ 次，时间复杂度均摊正确。

综上，`ODT` 维护颜色的出现区间，线段树维护答案。

时间复杂度 $\mathcal O(n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define he putchar('\n')
#define ha putchar(' ')

namespace Fread
{
    const int SIZE = 1 << 23;
    char buf[SIZE], *S, *T;
    inline char getchar()
    {
        if (S == T)
        {
            T = (S = buf) + fread(buf, 1, SIZE, stdin);
            if (S == T)
                return '\n';
        }
        return *S++;
    }
}

namespace Fwrite
{
    const int SIZE = 1 << 23;
    char buf[SIZE], *S = buf, *T = buf + SIZE;
    inline void flush()
    {
        fwrite(buf, 1, S - buf, stdout);
        S = buf;
    }
    inline void putchar(char c)
    {
        *S++ = c;
        if (S == T)
            flush();
    }
    struct NTR
    {
        ~NTR()
        {
            flush();
        }
    } ztr;
}

#ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#endif

inline int read()
{
	int x = 0;
	char c = getchar();
	while(c < '0' || c > '9')
		c = getchar();
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x;
}

inline void write(int x)
{
	if(x < 0)
	{
		putchar('-');
		x = -x;
	}
	if(x > 9) write(x / 10);
	putchar(x % 10 + 48);
}

const ll _ = 2e5 + 1, mod = 998244353;

int n, q;

int tr[_ << 2], t1[_ << 2], t2[_ << 2];

void build(int o, int l, int r)
{
	if(l == r) return;
	int mid = (l + r) >> 1;
	t1[o] = 0, t2[o] = 1;
	build(o << 1, l, mid), build(o << 1 | 1, mid + 1, r);
}

void push1(int o, int l, int r, ll v)
{
	if(!v) return;
	t1[o] = (t1[o] + v) % mod;
	tr[o] = (tr[o] + 1ll * (r - l + 1) * v) % mod;
}

void push2(int o, ll v)
{
	if(v == 1) return;
	t1[o] = 1ll * t1[o] * v % mod;
	t2[o] = 1ll * t2[o] * v % mod;
	tr[o] = 1ll * tr[o] * v % mod;
}

void pushdown(int o, int l, int r)
{
	int mid = (l + r) >> 1;
	push2(o << 1, t2[o]), push2(o << 1 | 1, t2[o]), t2[o] = 1;
	push1(o << 1, l, mid, t1[o]), push1(o << 1 | 1, mid + 1, r, t1[o]), t1[o] = 0;
}

void upd(int o, int l, int r, int L, int R, int v, int id)
{
	if(L <= l && r <= R)
	{
		if(id == 1) push1(o, l, r, v);
		else push2(o, v);
		return;
	}
	pushdown(o, l, r);
	int mid = (l + r) >> 1;
	if(L <= mid) upd(o << 1, l, mid, L, R, v, id);
	if(R > mid) upd(o << 1 | 1, mid + 1, r, L, R, v, id);
	tr[o] = (tr[o << 1] + tr[o << 1 | 1]) % mod;
}

int qry(int o, int l, int r, int L, int R)
{
	if(L <= l && r <= R) return tr[o];
	pushdown(o, l, r);
	int mid = (l + r) >> 1, res = 0;
	if(L <= mid) res = qry(o << 1, l, mid, L, R);
	if(R > mid) res = (res + qry(o << 1 | 1, mid + 1, r, L, R)) % mod;
	return res % mod;
}

struct Odt
{
	#define It set<odt>::iterator
	struct odt
	{
		int l, r, v;
		odt(int L = 0, int R = 0, int V = 0) { l = L, r = R, v = V; }
		friend bool operator < (const odt &a, const odt &b) { return a.l < b.l; }
	};
	set<odt> s;
	void init() { s.insert(odt(1, n, 0)); }
	It split(int x)
	{
		It it = s.lower_bound(odt(x, 0, 0));
		if(it != s.end() && it -> l == x) return it;
		--it;
		int L = it -> l, R = it -> r, V = it -> v;
		s.erase(it), s.insert(odt(L, x - 1, V));
		return s.insert(odt(x, R, V)).first;
	}
	void assign(int l, int r)
	{
		It itr = split(r + 1), itl = split(l);
		for(It it = itl; it != itr; ++it)
			if(!(it -> v)) upd(1, 1, n, it -> l, it -> r, 1, 1);
			else upd(1, 1, n, it -> l, it -> r, 2, 0);
		s.erase(itl, itr), s.insert(odt(l, r, 1));
	}
} t[_];

signed main()
{
	n = read(), q = read();
	build(1, 1, n);
	for(int i = 1; i <= n; ++i) t[i].init();
	int opt, l, r, x;
	while(q--)
	{
		opt = read(), l = read(), r = read();
		if(opt == 1)
			x = read(), t[x].assign(l, r);
		else
			write(qry(1, 1, n, l, r)), he;
	}
	return 0;
}
```



---

