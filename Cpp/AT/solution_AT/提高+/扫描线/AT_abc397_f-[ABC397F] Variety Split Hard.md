# [ABC397F] Variety Split Hard

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc397/tasks/abc397_f

> 本题是 C 题的强化版，分割个数变为 $3$ 个。

给定一个长度为 $N$ 的整数序列 $A = (A_1, A_2, \ldots, A_N)$。

当在 $A$ 的两个位置将其分割为 $3$ 个非空的连续子序列时，求这三个子序列中不同整数的种类数之和的最大可能值。

更严格地说，对于满足 $1 \leq i < j \leq N-1$ 的整数对 $(i, j)$，分别计算子序列 $(A_1, A_2, \ldots, A_i)$、$(A_{i+1}, A_{i+2}, \ldots, A_j)$ 和 $(A_{j+1}, A_{j+2}, \ldots, A_N)$ 中不同整数的种类数之和，并求这些和的最大值。

## 说明/提示

### 约束条件

- $3 \leq N \leq 3 \times 10^5$
- $1 \leq A_i \leq N$ ($1 \leq i \leq N$)
- 输入均为整数

### 样例解释 1

当 $(i, j) = (2, 4)$ 时，分割为 $(3, 1)$、$(4, 1)$ 和 $(5)$ 这三个连续子序列，各自的种类数分别为 $2, 2, 1$，和为 $5$。由于无法得到比 $5$ 更大的值，因此答案是 $5$。其他如 $(i, j) = (1, 3)$、$(2, 3)$、$(3, 4)$ 等情况也能得到和为 $5$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3 1 4 1 5```

### 输出

```
5```

## 样例 #2

### 输入

```
10
2 5 6 4 4 1 1 3 1 4```

### 输出

```
9```

# 题解

## 作者：qwertim (赞：9)

线段树板子题。

假设我们固定第一个子数组的右端点为 $x$，考虑第二个子数组的右端点 $y$ 放在哪里更优。

对于一个数 $p$：
- 当 $x$ 右边仅有一个 $p$ 时，发现 $y$ 不管在哪里，这个数都能且仅能产生 $1$ 的贡献。
- 当 $x$ 右边有至少两个 $p$ 时，设 $p$ 在 $x$ 右边第一次出现的位置位于 $q_0$，最后一次出现的位置位于 $q_1$。

则当 $y⊆[q_0,q_1)$ 时，$p$ 会产生 $2$ 的贡献（两子数组均有），除此之外会产生 $1$ 的贡献。

所以我们可以维护一个支持区间加，区间求 max 的线段树。倒序枚举 $x$，遇到一个之前出现过的 $a_i$，区间对 $[i,l_{a_i})$ 加 $1$ 即可（$l_{a_i}$ 为 $a_i$ 上一次出现的位置），最后对 $(x,n)$ 区间求 max 即为最大答案。

提交记录：[Submission #63913475](https://atcoder.jp/contests/abc397/submissions/63913475)。

---

## 作者：cherry2010 (赞：5)

[[ABC397F] Variety Split Hard](https://www.luogu.com.cn/problem/AT_abc397_f)

将序列分成三个部分，需要划两刀。考虑枚举其中一刀，那么就只需要快速计算另一刀的贡献。

记前一刀下标为 $L$，后一刀下标为 $R$，那么整个序列将会被分成三个部分，如下图所示。

![](https://pic1.imgdb.cn/item/67d64e8c88c538a9b5bf11e2.png)

考虑枚举 $R$，那么 3 部分可以通过预处理计算。需要快速得到 $L$ 在 1 到 $R$ 中任意位置时的前两部分贡献最大值，考虑使用线段树。具体地，线段树下标为 $i$ 的位置表示 $L=i$ 时前两部分的贡献和。1 部分的贡献同样可以预处理得到，那么最后的问题就是计算 2 部分的贡献了。

本质上这是一个区间并集问题，并集问题考虑维护变化量。观察发现，如果 $R$ 从左往右做扫描线，$R$ 比 $R-1$ 多加入 $a_R$。我们记 $x$ 在 $a$ 数组中上一次出现的位置为 $pre_x$。那么 $a_R$ 就只会对 $pre_{a_R}+1$ 到 $R$ 的所有位置的 2 部分贡献加 1，对 $pre_{a_R}$ 前面的没有影响。这放在线段树上就是区间加操作。

那么就在对 $R$ 做扫描线的同时，维护线段树进行区间加、区间求最大值的操作即可。实现时注意三个部分的边界，容易算重。

[Code](https://atcoder.jp/contests/abc397/submissions/63809061)

---

## 作者：Yxy7952 (赞：4)

[题目传送门](https://atcoder.jp/contests/abc397/tasks/abc397_f)
## 题目大意

题目要求将序列 $A$ 在两个位置 $i$ 和 $j$（$1 \leq i < j \leq N-1$）分割成 3 段，分别是：

- 第一段：$A_1, A_2, \ldots, A_i$
- 第二段：$A_{i+1}, A_{i+2}, \ldots, A_j$
- 第三段：$A_{j+1}, A_{j+2}, \ldots, A_N$

目标是最大化这三段中不同整数种类数的和。

## 思路

看到 $N \leq 3 \times 10^5$ 的数据范围，显然暴力枚举所有分割点 $(i, j)$ 的方法会超时（复杂度为 $O(N^2)$ 或更高）。考虑维护两端区间的贡献和，再枚举第二个分割点。

发现，第一次出现的数字不管在哪段区间，贡献都会 $+1$。在代码中，这个变量为 $sum$。

又发现，如果有第二次以上出现的数字，当分割点在 $[上一次出现这个数字的位置 + 1,这一个数字的位置]$ 的区间内时，贡献会 $+1$。

显然，有多段区间会 $+1$，我们只需知道哪段区间的数最大（也就是在这段区间内设置第一个分割点时，贡献最大），这个最大的数就是第二段区间会产生的贡献。

区间加和区间最大值的问题，可以用线段树维护。

之后把贡献记录在一个数组里，再从右往左求一遍第三段区间的贡献就好了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std ; 
int n , vis[300005] , f[300005] , ans , a[300005] ; 
int tree[1200005] , tag[1200005]  ; 
int ls(int p){ return p << 1 ; }
int rs(int p){ return p << 1 | 1 ; }
void push_up(int p){ tree[p] = max(tree[ls(p)] , tree[rs(p)]) ; }
void push_down(int p){
    tag[ls(p)] += tag[p] , tree[ls(p)] += tag[p] ; 
    tag[rs(p)] += tag[p] , tree[rs(p)] += tag[p] ; 
    tag[p] = 0 ; 
}
void update(int p , int pl , int pr , int L , int R){
    if(L <= pl && pr <= R){ tree[p]++ , tag[p]++ ; return ; }
    if(pr < L || R < pl) return ; 
    int mid = (pl + pr) >> 1 ; 
    push_down(p) ; 
    update(ls(p) , pl , mid , L , R) , update(rs(p) , mid + 1 , pr , L , R) ; 
    push_up(p) ; 
}
signed main(){
    ios::sync_with_stdio(0) ; 
    cin.tie(0) ; cout.tie(0) ; 
    cin >> n ; int sum = 0 ; 
    for(int i = 1 ; i <= n ; i++){
        cin >> a[i] ; 
        if(vis[a[i]]) update(1 , 1 , n , vis[a[i]] + 1 , i) ; //多次出现，区间 +1
        else sum++ ;//第一次出现，总贡献 +1
        vis[a[i]] = i ; f[i] = sum + tree[1] ; //记录数字最后一次出现的位置，和第二个分割点在 i 的贡献。
    }
    int g = 0 ; memset(vis , 0 , sizeof(vis)) ; 
    for(int i = n ; i > 1 ; i--){
        g += (!vis[a[i]]) ; 
        vis[a[i]]++ ; ans = max(ans , g + f[i - 1]) ; //一边遍历，一边记录分割点在哪里时贡献最大。
    }
    cout << ans ; 
    return 0 ; 
}
```

---

## 作者：rainygame (赞：4)

设 $w(l,r)$ 表示 $[l,r]$ 的权值。令 $g_i=w(1,i),h_i=w(i,n),f_i=\max\limits_{j=1}^{i-1}g_j+w(j+1,i)$，则答案就是 $\max\limits_{i=2}^{n-1}f_i+h_{i+1}$。难点在于求出 $f_i$。

考虑猜测 $f_i$ 满足决策单调性。这个可以通过证明 $w(l,r)$ 满足四边形不等式证明，当然也可以感性理解。设 $f_i$ 的最优决策点为 $p_i$，那么 $w(1,p_i)+w(p_i+1,i)\ge w(1,j)+w(j+1,i)$。对于新加的一个数 $a_{i+1}$，$f_{i+1}=\max\limits_{j=1}^iw(1,j)+w(j+1,i)+[a_{i+1} \ 不在 \ [j+1,i]\  中]$。由于当 $p_{i+1}<p_i$ 时，$w(1,p_{i+1})+w(p_{i+1}+1,i)\le w(1,p_i)+w(p_i+1,i),[a_{i+1} \ 不在 \ [p_{i+1}+1,i]\  中]\le [a_{i+1} \ 不在 \ [p_i+1,i]\  中]$，显然不优。所以有 $p_{i+1}\ge p_i$。

既然满足决策单调性，那么就直接决策单调性分治，时间复杂度 $O(n\log n)$。[submission](https://atcoder.jp/contests/abc397/submissions/63790568)

---

## 作者：Air2011 (赞：4)

## F-Variety Split Hard

### 题意

给定一个长度为 $n$ 的序列 $a$，你可以把其划分成 $3$ 个非空部分，三部分应连续，使这三部分不同的数的个数和最大，输出这个最大值 $s$。

### 思路

首先感觉这个非空的限制没有什么用，因为我们要使不同的数的个数和最大，应该尽量使他们划分为不同的两部分，而为了使其处于不同的两部分，我们的划分不可能非空。

我们注意到 $s$ 一定不小于 $a$ 中数的种类数，之后我们考虑怎样划分才能使 $s$ 尽可能大，我们画一下图，$x,y,z \ne 1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/fty615jt.png)

只有分界线是红线时两个 $1$ 才会产生贡献。

我们很自然想到可以用 线段树 来维护，我们把上图两个 $1$ 产生的额外贡献计为一个 $1$，我们维护用线将 $a_i$ 与 $a_{i+1}$ 分离开的额外贡献，计为 $f_i$，$i \le n-1$。

那么，对于两个相同且这两个数相对相邻，如上图的两个 $1$，我们就可以从第一个 $1$ 的位置开始，到第二个 $1$ 的位置**减一**结束，因为把分界线放至第二个 $1$ 后无法产生额外贡献。

这样找最大值我们就得到的 ABC397C 的一种唐诗解法。

我们考虑要划两条线，所以我们要考虑如果我们把线放到位置 $i$ 上，有哪些位置上的额外贡献回减，也就是在 $i$ 的左边的和在 $i$ 右边的相同的数，且在之前加过这个区间的两数，如果我把第二条线放到这两数形成的左闭右开区间内，那么我们应该要把这个额外贡献减去，体现在线段树上就是区间减。

但我们需要每一个 $i$ 都要这样做，复杂度会炸，我们可以只考虑变化量。

考虑我们选 $f_i \to f_{i+1}$ 的变化，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3umoc80g.png)

画线的三段区间为进行区间加的区间，如果我们只考虑变化的话，那么对于 $i=2$，往后转移时，会加上 $i=3$ 往后的第一个相等的 $3$，进行区间减，对于 $i=2$ 往前的第一个相等的 $2$（未找到），进行区间加（抵消之前区间减的影响，因为当我们把线防止 $i=3,i+1=4$ 之间时，之前在 $i=2$ 以前的区间减都无法影响到当前状态），我们需要记录一个值，表示进行区间减前的当前值和进行区间减后的最大值表示当前的权值，最后只要统计上答案即可。

最后代码：[Submissions-63843860](https://atcoder.jp/contests/abc397/submissions/63843860)

---

## 作者：封禁用户 (赞：3)

ds 还是不会。唉……

## Solution

考虑先确定一个点，假设确定靠右的那个点，于是只需要求把左边这一块划分为两个子串的最大贡献即可。

设选定的右边的点为 $i$，左边的为 $j$，原序列划分为 $[1,j],(j,i],(i,n]$，那么可以注意到在 $i \gets i+1$ 的时候，对于每个 $j$，其贡献的变化量是容易确定的。

如果设 $pre_i$ 为 $a_i$ 上一次出现的位置，那么只有在 $j \ge pre_i$ 的时候，$i \gets i+1$ 才会产生 $+1$ 的贡献，否则没有贡献变化。

然后发现这个东西可以拿个线段树维护，就做完了。具体地，维护一个线段树支持区间加、全局最大值；每次 $i \gets i+1$ 相当于区间 $[pre_i , i-2]$ 加 $1$，$i-1$ 单点加 $l_{i-1} + 1$；$i$ 的答案即为全局最大值加上 $r_{i+1}$。

其中 $l_i$ 为 $1 \sim i$ 的不同元素个数，$r_i$ 为 $i \sim n$ 的不同元素个数。

## Code

```cpp
int n,a[MAXN],l[MAXN],r[MAXN],pre[MAXN];
int vis[MAXN];

class __segment_tree
{
#define lc v[pos<<1]
#define rc v[pos<<1|1]
#define lcp pos<<1
#define rcp pos<<1|1
	
private:
	
	int *a;
	struct node{int mx,tag;} v[MAXN<<2];
	int k,lt,rt;
	
	il void pushup(int pos)
	{
		v[pos].mx=max(lc.mx,rc.mx);
	}
	
	il void addtag(int l,int r,int pos,int k)
	{
		v[pos].mx+=k;
		v[pos].tag+=k;
	}
	
	il void pushdown(int l,int r,int pos)
	{
		if(!v[pos].tag) return;
		int mid=l+r>>1;
		addtag(l,mid,lcp,v[pos].tag),addtag(mid+1,r,rcp,v[pos].tag);
		v[pos].tag=0;
	}
	
	il void update(int l,int r,int pos)
	{
		if(l>=lt && r<=rt) return addtag(l,r,pos,k);
		pushdown(l,r,pos);
		int mid=l+r>>1;
		mid>=lt && (update(l,mid,lcp),1);
		mid+1<=rt && (update(mid+1,r,rcp),1);
		pushup(pos);
	}
	
	il int query(int l,int r,int pos)
	{
		if(l>=lt && r<=rt) return v[pos].mx;
		pushdown(l,r,pos);
		int mid=l+r>>1,res=-9e18;
		mid>=lt && (res=max(res,query(l,mid,lcp)));
		mid+1<=rt && (res=max(res,query(mid+1,r,rcp)));
		return res;
	}
	
public:
	il void upd(int l,int r,int _k) {if(l>r) return; k=_k,lt=l,rt=r; update(1,n,1);}
	il int q(int l,int r) {if(l>r) return 0; lt=l,rt=r; return query(1,n,1);}
	
#undef lc
#undef rc
#undef lcp
#undef rcp
} tr;

signed main()
{
	read(n),_::r(a,n);
	
	rep(i,1,n) l[i]=l[i-1]+(!vis[a[i]]),pre[i]=vis[a[i]],vis[a[i]]=i;
	rep(i,1,n) vis[i]=0;
	rpe(i,n,1) r[i]=r[i+1]+(!vis[a[i]]),vis[a[i]]=i;
	rep(i,1,n) vis[i]=0;
	
	int ans=0;
	rep(i,2,n)
	{
		tr.upd(pre[i],i-1,1);
		tr.upd(i-1,i-1,l[i-1]);
		ans=max(ans,tr.q(1,n)+r[i+1]);
	}
	
	write(ans);
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：EmptyAlien (赞：2)

提供一个容易想到的简单的线段树做法。

正如题面所说，此题为 C 题的加强版，故我们参考 C 题的思路将问题拆开。

题目要求分裂为三个子串使每个串不同数字的数量之和最大，我们考虑算出**对于每个前缀，分裂为两个子串使得两串不同数字数量之和的最大的值**，这样对于右侧只需按照 C 题的方法计算即可，最终统计答案的时候枚举右边那个分界点统计答案即可。

现在我们的问题在于如何对于每个前缀计算分裂为两串的答案。

我们发现这等价于每一次给序列的末尾添加一个元素，动态维护其答案。

但是新加的值可能会影响到很多分割点位置的答案，也就是说每一个分割点都有可能成为答案。

我们就想能不能使用数据结构动态维护每个分割点的答案，这样只要每次求一个最大值就行了。

我们继续分析末尾添加一个元素会对哪些分割点的答案产生影响。

我们发现每增加一个新元素 $a_i$，我们找到它在序列中上一个出现的位置 $j$（如果没有就是 $0$）。

对于 $j$ 被分割到左侧一半的时候，该分割点的答案应该加一，因为 $j$ 右侧没有与她相同的元素，$a_i$ 就是新出现的一个，应该加 $1$。

对于 $j$ 被分割到右边一半的时候，该分割点的答案不变，因为 $a_i$ 已经在 $j$ 的位置上出现过了，不是新的一个不同的元素。

但是注意，我们在维护的时候都是考虑右边一半的元素，左边一半的我们根本没管，但这个问题相当好解决，因为一旦你的分割点确定了，你左边的他一半就钉死了，不可能再动了。所以我们先预处理出每个分割点左边的那一半的答案再扔到数据结构里统计即可。

回顾一下上面的过程我们发现是区间加，区间最大值，使用线段树维护即可。

复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 3e5 + 5;
int n;
int a[MAXN], pre[MAXN], suf[MAXN];
struct Seg {
    struct Node {
        int l, r, mx, lz;
    } tr[MAXN << 2];

    void pull(int k) {
        int lc = k * 2;
        int rc = lc + 1;
        tr[k].mx = max(tr[lc].mx, tr[rc].mx);
    }

    void lazy(int k, int v) {
        tr[k].mx += v;
        tr[k].lz += v;
    }

    void push(int k) {
        if (tr[k].lz == 0) return;
        int lc = k * 2;
        int rc = lc + 1;
        lazy(lc, tr[k].lz);
        lazy(rc, tr[k].lz);
        tr[k].lz = 0;
    }

    void build(int k, int l, int r) {
        tr[k] = {l, r, pre[l - 1], 0};
        if (l == r) return;
        int lc = k * 2;
        int rc = lc + 1;
        int mid = tr[k].l + tr[k].r >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pull(k);
    }

    void update(int k, int l, int r, int v) {
        if (tr[k].l == l && tr[k].r == r) return lazy(k, v);
        push(k);
        int lc = k * 2;
        int rc = lc + 1;
        int mid = tr[k].l + tr[k].r >> 1;
        if (r <= mid)
            update(lc, l, r, v);
        else if (l > mid)
            update(rc, l, r, v);
        else
            update(lc, l, mid, v), update(rc, mid + 1, r, v);
        pull(k);
    }

    int query(int k, int l, int r) {
        if (tr[k].l == l && tr[k].r == r) return tr[k].mx;
        push(k);
        int lc = k * 2;
        int rc = lc + 1;
        int mid = tr[k].l + tr[k].r >> 1;
        int ans = 0;
        if (r <= mid)
            ans = query(lc, l, r);
        else if (l > mid)
            ans = query(rc, l, r);
        else
            ans = max(query(lc, l, mid), query(rc, mid + 1, r));
        return ans;
    }
} seg; // 线段树

int last[MAXN];
int lef[MAXN];
int ans[MAXN];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    set<int> st;
    for (int i = 1; i <= n; i++) { // 预处理分割点左侧的答案
        st.insert(a[i]);
        pre[i] = st.size();
    }
    st.clear();
    for (int i = n; i >= 1; i--) { // 预处理最终统计答案时的右侧答案
        st.insert(a[i]);
        suf[i] = st.size();
    }

    seg.build(1, 1, n);
    for (int i = 1; i <= n; i++) { // 找出上一次出现的位置
        lef[i] = last[a[i]];
        last[a[i]] = i;
    }

    int res = 0;
    for (int i = 2; i <= n; i++) { // 动态维护
        seg.update(1, lef[i] + 1, i, 1);
        ans[i] = seg.query(1, 2, i);
    }

    for (int i = 2; i < n; i++) { // 统计答案
        res = max(res, ans[i] + suf[i + 1]);
    }
    cout << res << endl;
    return 0;
}
```

---

## 作者：Statax (赞：2)

## 思路

与 C 题类似，我们记前缀答案为 $L_i$，后缀答案为$R_i$。

同时新引进 $nxt_i$ 表示 $[i + 1, n]$ 中第一个和 $a_i$ 相等的数的下标，没有就为 $0$。

分三次的答案不小于分两次的答案，所以我们的答案转换为 $L_i + R_{i + 1} + 额外贡献$。

这个额外贡献来源于某些元素原本在同一部分中，现在被拆分到不同部分，导致某些元素的贡献增加。

具体而言，对于 $a_i$ 而言，其能**额外**对 $[i, nxt_i - 1]$ 做出 $1$ 的贡献，其中 $nxt_i \ne 0$。
而当遍历到 $i$ 时，我们要查的就是 $[i + 1, n]$ 额外贡献中的最大值。

所以这个**区间修改**，**区间查询**的过程可以用线段树、平衡树维护。

## 代码

时间复杂度 $O(n \log n)$，带点常数。

线段树就不放了，模板。
```cpp
signed main () {
//	freopen (".in", "r", stdin);
//	freopen (".out", "w", stdout);
	read (n);
	for (int i = 1; i <= n; ++i) read (a[i]);
	for (int i = n; i >= 1; --i) nxt[i] = lst[a[i]], lst[a[i]] = i;
	for (int i = 1; i <= n; ++i) Lst.insert (a[i]), L[i] = Lst.size ();
	for (int i = n; i >= 1; --i) Rst.insert (a[i]), R[i] = Rst.size ();
	
	build (1, 1, n);
	for (int i = 1; i < n; ++i) 
		if (nxt[i])
			modify (1, i, nxt[i] - 1, 1);
			
	int ans = 0;
	for (int i = 1; i < n; ++i) {
		if (nxt[i])
			modify (1, i, nxt[i] - 1, -1);
		ans = max (ans, L[i] + R[i + 1] + query (1, i + 1, n));
	} 
    
    printf ("%d\n", ans);
			
	
	return 0;
}
```

---

## 作者：Milthm (赞：1)

首先这种给你一个序列让你求什么东西的问题肯定要先枚举一个什么东西，于是设当前枚举到了 $now$。

据此，我们可以设 $f_i$ 表示 $a_1\sim a_i$ 的不同元素个数加上 $a_{i+1}\sim a_{now}$ 的不同元素个数，我们先来看看每次从 $now-1$ 的状态到 $now$ 的状态，$f$ 有怎样的变化：

设 $lst_i$ 表示上一个与 $a_i$ 一样的元素的下标，没有则设为 $0$，则有 $f_i=\sum\limits_{j=1}^i[lst_j=0]+\sum\limits_{j=i+1}^{now}[lst_j\le i]$。前面的东西十分好处理，后面这个东西随着 $now$ 的变化而变化，且我们发现每次枚举到 $now$ 都会给满足 $lst_{now} \le i <now $ 的 $f_i$ 加一。

然后，我们只需要每次将答案与 $\max(f_i,i<now)+g_{i+1}$ 取最大值即可，其中 $g_i$ 表示 $a_i\sim a_n$ 的不同元素个数。

于是我们发现需要对 $f$ 进行以下操作：

- 区间加。

- 区间最大值。

采用线段树即可解决，时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
#define N 500005 
using namespace std;
int n,a[N],g[N],maxn[N*4],z[N*4],vis[N],lst[N],ans;
set<int>s;
void pushup(int x){
	maxn[x]=max(maxn[x*2],maxn[x*2+1]);
}
void pushdown(int x){
	if(z[x]){
		maxn[x*2]+=z[x];maxn[x*2+1]+=z[x];
		z[x*2]+=z[x];z[x*2+1]+=z[x];z[x]=0;
	}
}
void update(int x,int l,int r,int ql,int qr,int v){
	if(ql>qr)return;
	if(ql<=l&&r<=qr){
		maxn[x]+=v;z[x]+=v;return;
	}
	int mid=(l+r)>>1;pushdown(x);
	if(ql<=mid)update(x*2,l,mid,ql,qr,v);
	if(qr>mid)update(x*2+1,mid+1,r,ql,qr,v);
	pushup(x);
}
int query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return maxn[x];
	int mid=(l+r)>>1,ans=0;pushdown(x);
	if(ql<=mid)ans=max(ans,query(x*2,l,mid,ql,qr));
	if(qr>mid)ans=max(ans,query(x*2+1,mid+1,r,ql,qr));
	return ans;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=n;i>=1;--i)s.insert(a[i]),g[i]=s.size();
	for(int i=1;i<=n;++i){
		lst[i]=vis[a[i]];
		vis[a[i]]=i;
	}
	int sum0=0;
	for(int i=1;i<n;++i){
		if(!lst[i])++sum0;
		update(1,1,n,i,i,sum0);update(1,1,n,max(lst[i],1),i-1,1);
	//	for(int j=1;j<=n;++j)cout<<query(1,1,n,j,j)<<" ";cout<<'\n';
		if(i!=1)ans=max(ans,query(1,1,n,1,i-1)+g[i+1]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Crazyouth (赞：1)

## 分析

首先算出两个数组 $b_i$ 表示 $[i,n]$ 内的不同数个数，$f_i$ 表示 $[1,i]$ 的不同数个数，这样当我们枚举第一个断点 $i$，答案就是最大的 $b_{j+1}+ans_{i+1\sim j}$ 加上当前的 $f_i$，其中 $ans_{i+1\sim j}$ 表示 $i+1\sim j$ 的不同数个数。我们在线段树上维护上面一堆，这时当我们枚举的数从 $i$ 变到 $i+1$ 时，只会影响那些下一个 $a_i$ 位置之前的数的 $i+1$ 到它们的不同数个数，也就是对那些位置的线段树上区间减一，答案就是从 $i+1$ 到 $n$ 的线段树取 $\max$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=300010;
int mx[N<<2],lz[N<<2];
void upd(int l,int r,int s,int t,int p,int c)
{
	if(l<=s&&t<=r)
	{
		mx[p]+=c;
		lz[p]+=c;
		return;
	}
	int m=s+t>>1;
	if(lz[p])
	{
		lz[p<<1]+=lz[p];
		lz[p<<1|1]+=lz[p];
		mx[p<<1]+=lz[p];
		mx[p<<1|1]+=lz[p];
		lz[p]=0;
	}
	if(l<=m) upd(l,r,s,m,p<<1,c);
	if(r>m) upd(l,r,m+1,t,p<<1|1,c);
	mx[p]=max(mx[p<<1],mx[p<<1|1]);
}
int qry(int l,int r,int s,int t,int p)
{
	if(l<=s&&t<=r) return mx[p];
	int m=s+t>>1;
	if(lz[p])
	{
		lz[p<<1]+=lz[p];
		lz[p<<1|1]+=lz[p];
		mx[p<<1]+=lz[p];
		mx[p<<1|1]+=lz[p];
		lz[p]=0;
	}
	int ans=0;
	if(l<=m) ans=qry(l,r,s,m,p<<1);
	if(r>m) ans=max(ans,qry(l,r,m+1,t,p<<1|1));
	return ans;
}
set<int> st;
int f[N],a[N],fr[N];
vector<int> pos[N];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],pos[a[i]].push_back(i);
	for(int i=n;i;i--)
	{
		st.insert(a[i]);
		f[i]=st.size();
	}
	st.clear();
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		st.insert(a[i]);
		fr[i]=st.size();
		upd(i,i,1,n,1,f[i+1]+st.size());
	}
	for(int i=1;i<n-1;i++)
	{
		int nxt=(lower_bound(pos[a[i]].begin(),pos[a[i]].end(),i+1)!=pos[a[i]].end()?(*lower_bound(pos[a[i]].begin(),pos[a[i]].end(),i+1)):n+1);
		upd(i,nxt-1,1,n,1,-1);
		ans=max(ans,fr[i]+qry(i+1,n,1,n,1));
	}
	cout<<ans;
}

---

## 作者：cyq32ent (赞：1)

赛事试图手敲线段树，TLE。

我们将拆分表示为 $\{[0,i],(i,j],(j,N]\}$。我们设前缀不同数目为 $P_i$，后缀为 $S_i$，区间 $(i,j]$ 的不同数目为 $f(i,j)$。瓶颈在计算 $f(i,j)$。

设 $r_i$ 为 $A_i$ 上一次出现的位置。我们考虑固定 $j$。我们设 $d_i=P_i+f(i,j)$，则此时答案为 $\max_{i<j}d_i$。我们注意到 $d$ 可以由 $j-1$ 时的情况递推得来：我们考虑向中间段区间添加 $A_j$，并考虑 $A_j$ 对 $d$ 的贡献。因为区间 $(r_j,j]$ 中，$A_j$ 是唯一的。所以当且仅当当 $r_j\leq i<j$ 时，$f(i,j)=f(i,j-1)+1$。所以，我们可以直接在 $d$ 上的 $[r_j,j)$ 区间上加一。用线段树实现即可。

初始化时，将 $d_i$ 设为 $P_i$。

代码：（省去了冗长的线段树模板）

```cpp
int N,a[314159],P[314159],S[314159],m1[314159],m2[314159],pr[314159],ans;
vector<int>ar(314159);
int main(){
	cin>>N;
	for(int i=1;i<=N;i++)cin>>a[i];
	for(int i=1;i<=N;i++){
		if(!m1[a[i]])m1[a[i]]=i,P[i]=P[i-1]+1,pr[i]=0;
		else P[i]=P[i-1],pr[i]=m1[a[i]],m1[a[i]]=i;
	}for(int i=N;i;i--){
		if(!m2[a[i]])m2[a[i]]=1,S[i]=S[i+1]+1;
		else S[i]=S[i+1];
	}ar[1]=2;for(int i=2;i<=N;i++)ar[i]=P[i];ans=2+S[3];
	SegTree s(ar);
	for(int j=3;j<N;j++){
		s.range_add(max(1,pr[j]),j-1,1);
		ans=max(ans,s.range_max(1,j-1)+S[j+1]);
	}cout<<ans;
	return 0;
}
```

---

## 作者：xyx404 (赞：1)

## 题意：
将数组分割成三个非空连续子数组，使得三个子数组中不同元素的数量之和最大。

## 思路：
线段树。

可以先把[线段树的加法模版](https://www.luogu.com.cn/problem/P3372)做了再来看。

定义数组 $pre$，其中 $pre_i$ 表示前 $i$ 个元素中不同元素的数量。  
定义数组 $suf$，其中 $suf_i$ 表示从位置 $i$ 到末尾的不同元素数量。

这样就可以差不多可以把这道题的弱化版，[本场的 C 题](https://atcoder.jp/contests/abc397/tasks/abc397_c)写出来。

接下来继续考虑本题。

定义 $mid(i,j)$ 是对于 $A$ 数组中的所有满足下标 $i \le k \le j$ 的 $A_k$ 的不同元素个数。  
用数学方式可以表示为 $mid(i, j)= \left| \{ A_k \mid i \leq k \leq j \} \right|$。

对于每个分割点 $j$（第二个分割点的位置），我们需要找到最优的第一个分割点 $i$，使得 $pre_i+mid(i+1,j)+suf_{j+1}$ 的值最大。

我们可以使用线段树维护每个位置 $i$ 的 $pre_i+mid(i+1,j)$ 的最大值。

在维护中间段时，当 $A_j$ 出现重复时，只有 $i \ge l$ 的分割点会使中间段包含新的 $A_j$，因此要让区间 $[l,j−1]$ 维护的值加一。

定义一个变量 $maxx$ 用来存答案。

对每个 $j$，查询线段树维护的区间 $[1,j−1]$ 的值，加上 $suf_{j+1}$ 后更新全局最大值。

总时间复杂度 $O(N \log N)$。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
const int N=3e5+5;
int n,a[N*4],pre[N*4],suf[N*4],las[N*4];
vector<int>value(N*4),lazy(N*4);
void build(int now,int l,int r){
	if(l==r){
		value[now]=pre[l];
		return;// 别忘了 return 赛时 15 分钟打忘记加喜提 RE
	}
	int mid=l+(r-l)/2;
	build(2*now,l,mid);
	build(2*now+1,mid+1,r);
	value[now]=max(value[now*2],value[now*2+1]);
}
void push(int now){// 懒标记
	if(lazy[now]==0)return;
	value[2*now]+=lazy[now];
	value[2*now+1]+=lazy[now];
	lazy[2*now]+=lazy[now];
	lazy[2*now+1]+=lazy[now];
	lazy[now]=0;
}
void change(int now,int l,int r,int ql,int qr,int val){
	if(qr<l||ql>r)return;
	if(ql<=l&&r<=qr){
		value[now]+=val;
		lazy[now]+=val;
		return;
	}
	push(now);
	int mid=l+(r-l)/2;
	change(2*now,l,mid,ql,qr,val);
	change(2*now+1,mid+1,r,ql,qr,val);
	value[now]=max(value[2*now],value[now*2+1]);
}
int ans(int now,int l,int r,int ql,int qr){
	if(qr<l||ql>r)return 0;
	if(ql<=l&&r<=qr){
		return value[now];
	}
	push(now);
	int mid=l+(r-l)/2;
	return max(ans(now*2,l,mid,ql,qr),ans(now*2+1,mid+1,r,ql,qr));
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	unordered_set<int>spre;
	pre[0]=0;
	for(int i=1;i<=n;i++){// 处理前 i 个元素中不同元素的数量
		spre.insert(a[i]);
		pre[i]=spre.size();
	}
	unordered_set<int>ssuf;
	suf[n+1]=0;
	for(int i=n;i>=1;i--){// 处理从位置 i 到末尾的不同元素数量。
		ssuf.insert(a[i]);
		suf[i]=ssuf.size();
	}
	build(1,1,n-1);// 建树
	int maxx=0;
	for(int j=1;j<=n-1;j++){
		int x=a[j];
		int l=las[x];
		int le=max(l,1);
		int r=j-1;
		if(l<=r){
			change(1,1,n-1,le,r,1);
		}
		las[x]=j;
		if(j>=2){
			int cm=ans(1,1,n-1,1,j-1);
			int cs=cm+suf[j+1];
			maxx=max(maxx,cs);
		}
	}
	cout<<maxx;
	return 0;
}

```
[提交记录](https://atcoder.jp/contests/abc397/submissions/63863040)。

---

## 作者：yuhong056 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc397_f)

# 题目大意

给定数组 $A$，求出将其划分成 $3$ 个非空连续子数组时不同数字数量之和的最大可能值。

# 解题思路

## step1. 简化题目：

如果我们通过枚举得出最右区间的左端点，题目就变成了：

> 给定一个数组 $A$，求出将其划分成 $2$ 个非空连续子数组时不同数字数量之和的最大可能值。

## step2. 解决简化后的题目

如果通过 [AT\_abc397\_c](https://atcoder.jp/contests/abc397/tasks/abc397_c) 的思路去解决，单次时间复杂度为 $O(N)$，总时间复杂度为 $O(N^2)$，无法通过此题。

考虑在某个点右边拆分对答案的贡献：

当一个数前面已经出现过，那么在当前位置与上一次出现位置之间拆分，答案就会增加 $1$。

原因：如果不在当前位置与上一次出现位置之间拆分，此时两个相同的数会在同一段，所以只会统计一次。而在当前位置与上一次出现位置之间拆分，此时前一段会包含此数，后一段也会包含此数，所以会统计两次。

综上所述，如果遇到一个前面出现过的数，就将在 $[\text{上一次出现位置}, \text{当前位置})$ 处划分对答案的贡献加 $1$。

因此，我们需要：

> 知道当前数上一次出现位置。
>
> 在较低时间复杂度内将一段区间内贡献值 $+1$。
>
> 在较低时间复杂度内知道当前范围内最大贡献值。

知道当前数上一次出现位置比较简单，使用标记数组即可。至于剩下的操作……

## step3. 数据结构优化

首先，我们需要快速**区间修改**（将一段区间内贡献值 $+1$）。

其次，我们还需要快速**区间查询**（知道当前范围内最大贡献值）。

没错，就是~~万能的~~线段树！

我们需要进行区间加、区间查询最大值。接下来，明确了要做的操作，就可以写代码了！

# CODE

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 15;

struct Node{//线段树节点值
	int Max;
};

struct Tag{//线段树懒标记
	int add;
	bool operator == (const Tag &oth) {
		return oth.add == add;
	}
};

struct Segtree{//线段树
	Node tr[MAXN << 2];
	Tag tag[MAXN << 2];
	const Node E = {0};//单位元
	const Tag I = {0};//恒等映射
	
	Node comb(const Node &a, const Node &b) {// 信息合并运算
		return {max(a.Max, b.Max)};
	}
	
	Tag F(const Tag &n, const Tag &y) {// 懒标记函数复合运算
		return {n.add + y.add};
	}
	
	Node f(const Node &x, const Tag &t) {// 懒标记对信息的函数运算
		return {x.Max + t.add};
	}

  //因为一开始每个点拆分对答案的贡献都为0，所以无需建树

	void down(int id) {// 懒标记下放
		if(tag[id] == I)return;
		tr[id << 1] = f(tr[id << 1], tag[id]);
		tag[id << 1] = F(tag[id << 1], tag[id]);
		tr[id << 1 | 1] = f(tr[id << 1 | 1], tag[id]);
		tag[id << 1 | 1] = F(tag[id << 1 | 1], tag[id]);
		tag[id] = I;
	}
	
	void change(int id, int l, int r, int cl, int cr, Tag tg) {// 区间修改
		if(cl <= l && cr >= r) {
			tr[id] = f(tr[id], tg);
			tag[id] = F(tag[id], tg);
			return;
		}
		down(id);
		int mid = l + r >> 1;
		if(cl <= mid)change(id << 1, l, mid, cl, cr, tg);
		if(cr > mid)change(id << 1 | 1, mid + 1, r, cl, cr, tg);
		tr[id] = comb(tr[id << 1], tr[id << 1 | 1]);
	}
	
	Node ask(int id, int l, int r, int al, int ar) {// 区间查询
		if(al <= l && ar >= r)return tr[id];
		if(ar < l || al > r)return E;
		down(id);
		int mid = l + r >> 1;
		return comb(ask(id << 1, l, mid, al, ar), ask(id << 1 | 1, mid + 1, r, al, ar));
	}
}T;

int n;

int ls[MAXN]/*此数上一次出现位置*/, a[MAXN];
int cnt[MAXN][2]/*每个数出现次数，0代表最右段，1代表左段*/, ans[2]/*有多少个不同的数，0代表最右段，1代表左段*/;
int maxn;

#define all 1, 1, n

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		cnt[a[i]][0]++;
		if(cnt[a[i]][0] == 1)ans[0]++;
	}
	for(int i = 1; i < n; i++) {
		if(ls[a[i]]) {
			T.change(all, ls[a[i]], i - 1, {1});
		}
		ls[a[i]] = i;
		cnt[a[i]][0]--;
		if(cnt[a[i]][0] == 0)ans[0]--;
		cnt[a[i]][1]++;
		if(cnt[a[i]][1] == 1)ans[1]++;
		//cout << a[i] << ' ' << ans[1] << ' ' << ans[0] << '\n';
		if(i > 1) {
			maxn = max(maxn, ans[1] + T.ask(all, 1, i - 1).Max + ans[0]);
		}
	}
	cout << maxn;
	return 0;
}

```

这是本蒟蒻的第一篇题解，管理员大大求过！

---

## 作者：I_will_AKIOI (赞：1)

题目要求分成三段，因此我们先从小到大枚举第二个分割点，把最后一段分出来。接着就需要快速求把 $[1,i]$ 分成两段的答案。

因为 $i$ 是递增的，计算相邻两个 $i$ 对答案的贡献，记录每一个分割点对答案的贡献，然后选出最优的第一个分割点。记 $last_{num}$ 表示最近的 $num$ 出现的下标。

如果 $a_i$ 从未出现过，那么加入 $a_i$ 之后，会对所有的分割点贡献 $1$。否则，如果选择区间 $[last_{a_i},i-1]$，那么分割点的两边都会出现 $a_i$，因此此时 $a_i$ 还会额外对这个区间内的分割点贡献 $1$。

然后我们就只要选出 $[1,i]$ 中对答案贡献最大的分割点，再加上分割区间 $[i+1,n]$ 的答案。发现选出分割点的过程需要支持区间加和区间最大值，于是线段树维护。

绝对不会告诉你我赛时最后 $9$ 分钟极限敲完代码，但是因为没建树而痛失 F。

```cpp
#include<bits/stdc++.h>
#define N 300005
#pragma GCC optimize("O3")
using namespace std;
struct Data{int l,r,maxx,tag;}t[N*4];
int n,ans,a[N],last[N],suf[N];
bool vis[N];
void maketag(int k,int x)
{
	t[k].maxx+=x;
	t[k].tag+=x;
	return;
}
void pushdown(int k)
{
	maketag(k*2,t[k].tag);
	maketag(k*2+1,t[k].tag);
	t[k].tag=0;
	return;
}
void build(int k,int l,int r)
{
	t[k].l=l,t[k].r=r;
	if(l==r) return;
	int mid=l+r>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	return;
}
void update(int k,int l,int r,int x)
{
	if(l<=t[k].l&&t[k].r<=r) {maketag(k,x);return;}
	pushdown(k);
	int mid=t[k].l+t[k].r>>1;
	if(l<=mid) update(k*2,l,r,x);
	if(r>mid) update(k*2+1,l,r,x);
	t[k].maxx=max(t[k*2].maxx,t[k*2+1].maxx);
	return;
}
int query(int k,int l,int r)
{
	if(l<=t[k].l&&t[k].r<=r) return t[k].maxx;
	pushdown(k);
	int mid=t[k].l+t[k].r>>1,res=0;
	if(l<=mid) res=max(res,query(k*2,l,r));
	if(r>mid) res=max(res,query(k*2+1,l,r));
	return res;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=n;i>=1;i--)
	{
		if(vis[a[i]]==0) suf[i]=suf[i+1]+1;
		else suf[i]=suf[i+1];
		vis[a[i]]=1;
	}
	build(1,1,n);
	for(int i=1;i<=n;i++)
	{
		if(last[a[i]]==0) update(1,1,n,1);
		else update(1,last[a[i]],i-1,1);
		last[a[i]]=i;
		ans=max(ans,suf[i+1]+query(1,1,i));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ljy05 (赞：0)

分成 $3$ 段不好做怎么办？我们从小到大枚举 $i$，把 $1 \sim i$ 分成两段，把 $i+1 \sim N$ 分成一段再拼起来就行了。

求 $i+1 \sim N$ 分成一段是很简单的，所以我们要快速的算出把 $1 \sim i$ 在哪里分开。如果一个数 $k$ 在 $1 \sim i$ 中第一次出现的位置是 $l_k$，最后一次出现的位置是 $r_k$，我们分开的位置在 $x$，如果 $x$ 在 $l_k$ 和 $r_k$ 之间，$k$ 就会贡献 $2$ 的答案，否则只会贡献 $1$ 的答案。

为了最大化答案，我们要让贡献 $2$ 的数最多，并且还要对于每个 $i$ 都求出最大的贡献，所以我们需要一棵线段树。我们将树上 $l_k+1 \sim r_k$ 的区间加一，最后值最大的位置就是理想的分割点。我们用树上最大的值加上 $1 \sim i$ 中出现的数的种类数，就是 $1 \sim i$ 的最大贡献。

求出了 $1 \sim i$ 的最大贡献，还要递推出 $1 \sim i+1$ 的最大贡献。两个贡献的差别很小，只需要往树里面多加一个区间 $r_{A_{i+1}}+1 \sim i$ 即可。然后我们就在 $O(N \log N)$ 的时间内完成了本题。

AC记录：https://atcoder.jp/contests/abc397/submissions/63819853

丑陋的AC代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct nde{
	int l,r,v,lzy;
} st[1200010];//线段树
int lp[300010],rel[300010];//这个数上一次出现的位置，i~n的种类数
int a[300010];
int n;
void bt(int p,int l,int r){//建树
	st[p].l=l;
	st[p].r=r;
	if(l<r){
		bt(p*2,l,(l+r)/2);
		bt(p*2+1,(l+r)/2+1,r);
	}
}
void mkl(int p,int x){//打懒标记
	st[p].v+=x;
	st[p].lzy+=x;
}
void psd(int p){//下放
	if(st[p].l<st[p].r&&st[p].lzy>0){
		mkl(p*2,st[p].lzy);
		mkl(p*2+1,st[p].lzy);
	}
	st[p].lzy=0;
}
void upd(int p){//更新
	if(st[p].l<st[p].r) st[p].v=max(st[p*2].v,st[p*2+1].v);
}
void mdf(int p,int l,int r){//区间修改
	l=max(l,st[p].l);
	r=min(r,st[p].r);
	if(l>r) return ;
	if(st[p].l==l&&st[p].r==r){
		mkl(p,1);
		return ;
	}
	psd(p);
	mdf(p*2,l,r);
	mdf(p*2+1,l,r);
	upd(p);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=n;i>0;i--){//求i~n的贡献
		if(lp[a[i]]==0) rel[i]=rel[i+1]+1;
		else rel[i]=rel[i+1];
		lp[a[i]]=i;
	}
	for(int i=1;i<=n;i++) lp[i]=0;
	int ans=0,cnt=0;
	bt(1,1,n);
	for(int i=1;i<n;i++){
		if(lp[a[i]]>0) mdf(1,lp[a[i]]+1,i);
		else cnt++;
		lp[a[i]]=i;
		ans=max(ans,cnt+st[1].v+rel[i+1]);
	}
	printf("%d\n",ans);
  return 0;
}
```

---

## 作者：刘梓轩2010 (赞：0)

可以看看这个 [CF833B](https://codeforces.com/problemset/problem/833/B)。

## 题意

给你一个序列，你要把这个序列分成连续的三段，每一段的权值为每一段中不同的数的个数，问你这个序列的最大权值是多少。

## 思路

首先发现可以预处理来第一段和最后一段的权值，设为 $ans1$ 和 $ans2$，$ans1_i$ 即为从 $1$ 到 $i$ 这一段的权值，$ans2_i$ 即为从 $i$ 到 $n$ 这一段的权值，于是我们就有了 $O(n^2)$ 的 dp 做法。

设 $f_i$ 表示以 $i$ 为第二段结尾的最大权值，答案即为 $\max f_i$。

$$f_i=\max_{j=1}^{i-1} ans1_j+val(j+1,i)+ans2_j$$

$val(i,j)$ 即为从 $i$ 到 $j$ 这一段的权值。

考虑优化。

我们发现，难点在于如何计算 $val(j+1,i)$。

考虑说我们可以把每一个 $ans1$ 扔到线段树上，一个点 $j$ 就表示说以 $j$ 为第一段的结尾最大权值，然后我们枚举第二段的结尾 $i$，每次 dp。

我们记 $a_i$ 上一次出现的位置为 $la_i$。

考虑说我们每个数只对于起点在 $[la_i+1,i]$ 这个闭区间的所有区间有 $1$ 的贡献，也就是线段树上 $[la_i,i-1]$ 这个区间。

最后一段的直接加上即可。

然后每次转移找最大值。

复杂度 $O(n\log n)$。

不理解可以结合代码食用。

## Code
```c++
#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define fi first
#define se second
using namespace std;
const int N=3e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
int n;
int a[N];
int ans1[N],ans2[N];
unordered_map<int,int> mp;
int ans;
int pre[N],nxt[N];
struct Node
{
	int l,r,w;
	int lt;
}tr[N<<2];
void build(int rt,int l,int r)
{
    tr[rt].l=l,tr[rt].r=r;
    if(l==r)
    {
        tr[rt].w=ans1[l];
        return ;
    }
    int mid=(tr[rt].l+tr[rt].r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    tr[rt].w=max(tr[rt<<1].w,tr[rt<<1|1].w);
}
void pushdown(int rt)
{
    int &tag=tr[rt].lt;
    tr[rt<<1].w+=tag;
    tr[rt<<1|1].w+=tag;
    tr[rt<<1].lt+=tag;
    tr[rt<<1|1].lt+=tag;
    tag=0;
}
void add(int rt,int l,int r,int k)
{
    if(tr[rt].l>=l&&tr[rt].r<=r)
    {
        tr[rt].w+=k;
        tr[rt].lt+=k;
        return ;
    }
    pushdown(rt);
    int mid=(tr[rt].r+tr[rt].l)>>1;
    if(l<=mid) add(rt<<1,l,r,k);
    if(r>mid) add(rt<<1|1,l,r,k);
    tr[rt].w=max(tr[rt<<1].w,tr[rt<<1|1].w);
}
int check(int rt,int l,int r)
{
    if(tr[rt].l>=l&&tr[rt].r<=r) return tr[rt].w;
    pushdown(rt);
    int mid=(tr[rt].l+tr[rt].r)>>1;
    int res=0;
    if(l<=mid) res=max(res,check(rt<<1,l,r));
    if(r>mid) res=max(res,check(rt<<1|1,l,r));
    return res;
}
signed main()
{
	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
	{
	    pre[i]=mp[a[i]];
	    mp[a[i]]=i;
	    ans1[i]=mp.size();
    }
    mp.clear();
    for(int i=n;i>=1;i--)
    {
        nxt[i]=mp[a[i]];
        mp[a[i]]=i;
        ans2[i]=mp.size();
    }
    build(1,1,n);
    for(int i=2;i<n;i++)
    {
        add(1,(pre[i]?pre[i]:1),i-1,1);
        ans=max(check(1,1,i-1)+ans2[i+1],ans);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Dtw_ (赞：0)

## 题意
给你一个序列 $n$，你要把他分成 $3$ 段，每一段的权值为不同的数的个数，求 $3$ 段的权值和的最大值。
## Solution
考虑枚举一个后缀，然后那么后缀的贡献已经知道了，考虑前面的数分成两段的贡献。

我们可以把两段的贡献拆成一个前缀的贡献加上中间一段的贡献。

前缀的贡献可以直接预处理出来，那么如何计算中间一段的贡献？

那我们记 $la_i$ 表示 $i$ 上一次出现的位置，那么当前这个数会对 $[la_i, i - 1]$ 产生贡献。为啥是 $la_i$ 而不是 $la_i + 1$ 呢？因为 $la_i$ 这个位置被包括在第 $1$ 段里了，所以当前这个 $i$ 可以贡献到 $la_i$ 这个位置上。

然后就做完了。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 3e5 + 10, inf = 0x3f3f3f3f;

int n, a[N], f[N], t[N], g[N], la[N];

int tr[N << 2], tag[N << 2];

#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define mid (l + r) / 2

void push_up(int rt) { tr[rt] = max(tr[lson], tr[rson]); }

void build(int rt, int l, int r)
{
    if (l == r) return tr[rt] = f[l], void();
    build(lson, l, mid);
    build(rson, mid + 1, r);
    push_up(rt);
}

void push_down(int rt)
{
    int &u = tag[rt];
    if (!u) return;
    tag[lson] += u, tag[rson] += u, tr[lson] += u, tr[rson] += u;
    u = 0;
}

void update(int rt, int l, int r, int sp, int ep)
{
    if (sp <= l && r <= ep) return tr[rt]++, tag[rt]++, void();
    push_down(rt);
    if (sp <= mid) update(lson, l, mid, sp, ep);
    if (ep > mid) update(rson, mid + 1, r, sp, ep);
    push_up(rt);
}

int query(int rt, int l, int r, int sp, int ep)
{
    if (sp <= l && r <= ep) return tr[rt];
    int res = 0; push_down(rt);
    if (sp <= mid) res = query(lson, l, mid, sp, ep);
    if (ep > mid) res = max(res, query(rson, mid + 1, r, sp, ep));
    return res;
}

int main()
{
    fst
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++)
    {
        t[a[i]]++;
        if (t[a[i]] == 1) f[i]++;
        f[i] += f[i - 1];
    }
    memset(t, 0, sizeof t);
    for (int i = n; i >= 1; i--)
    {
        t[a[i]]++;
        if (t[a[i]] == 1) g[i]++;
        g[i] += g[i + 1];
    }
    build(1, 0, n);
    int res = 0;
    for (int i = 2; i <= n; i++)
    {
        update(1, 0, n, la[a[i]], i - 1);
        res = max(res, query(1, 0, n, 1, i - 1) + g[i + 1]);
        la[a[i]] = i;
    }
    cout << res;
    return 0;
}
```

---

## 作者：可爱的小棉羊 (赞：0)

水题，先枚举第一个分割点，考虑后两个区间的贡献。

显然，每种出现的数至少会造成 $1$ 的贡献。

又发现如果一种数有一个划在左边，有一个划在右边就会造成 $2$ 的贡献。

那么就简单了，记 $fir_k$ 为目前右边两区间并中第一个出现 $k$ 的位置，$last_k$ 为最后的位置，在从右往左扫枚举第一个端点 $i$ 中是可以维护的。

所谓造成 $2$ 的贡献，我们选取的位置 $j$ 就得 $\in[fir_k,last_k)$。

每次维护这些区间就是做区间加，最大贡献就是一个区间 $\max$。

时间复杂度 $O(n\log n)$。

[代码](https://atcoder.jp/contests/abc397/submissions/63830747)

---

## 作者：zhangbo1000 (赞：0)

首先考虑分两段的情况，也就是这次比赛的 C 题。

设 $b_i$ 为前 $i$ 个数中不同数的个数，$c_i$ 为后 $i$ 个数中不同数的个数，那么答案为 $b_i+c_{n-i}$ 的最大值，时间复杂度 $O(n)$。

然后考虑分三段，发现如果第一段确定了划到那里，后面两段的分隔就是上个问题。

所以我们考虑维护“只考虑后 $i$ 个数，上个问题的答案”然后枚举 $i$。

考虑在数列开头加上第 $i$ 个数的影响：$c$ 需要在开头加上整个数列的 $c_i$，$b$ 先在开头加上 $0$，然后设第 $i$ 个数后面第一个相同的数的位置为 $f_i$（如果没有则定义为 $n+1$），则 $b_{i}\sim b_{f_i-1}$ 都需要加一。

所以我们可以用支持区间加，区间最大值的线段树维护。

时间复杂度 $O(n\log n)$。

[代码和评测记录。](https://atcoder.jp/contests/abc397/submissions/63821970)

---

## 作者：xiao7_Mr_10_ (赞：0)

注意到简化版的做法：设 $pre_i$ 表示 $[1,i]$ 的不同种类数，$last_i$ 表示 $[i,n]$ 的不同种类数。

这两个数组显然我们可以 $O(n)$ 处理，再枚举唯一的端点，计算贡献即可。

对于分成三段的情况也很简单，我们枚举**第二段的末尾**。第三段的贡献就可以直接算，考虑如何找到另一个端点使得结果最优。

直接扫描线，维护以某个位置为第二段起始点的答案，设这个位置为 $x$，初始状态肯定是 $pre_{x-1}$。然后就是非常简单的维护不同种类数，再加上初始状态，求最大值，做完了。

时间复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
struct Point{
	int col[N],ans;
	void add(int x){col[x]++;if(col[x]==1)ans++;}
	void del(int x){
		col[x]--;
		if(col[x]==0)ans--;
	}
}f,g;
int n,a[N],pre[N],pos[N],tag[N<<2],last[N],c[N<<2];
void updata(int x){
	c[x]=max(c[x<<1],c[x<<1|1]);
}
void build(int x,int l,int r){
	if(l==r){
		c[x]=pre[l-1];
		return;
	}int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);updata(x);
}void pushdown(int x,int k){
	tag[x]+=k,c[x]+=k;
}void down(int x){
	pushdown(x<<1,tag[x]),pushdown(x<<1|1,tag[x]);tag[x]=0;
}void change(int x,int l,int r,int s,int t,int k){
	if(l>=s&&r<=t){
		pushdown(x,k);
		return;
	}int mid=(l+r)>>1;down(x);
	if(s<=mid)change(x<<1,l,mid,s,t,k);
	if(t>mid)change(x<<1|1,mid+1,r,s,t,k);updata(x);
}
int query(int x,int l,int r,int s,int t){
	if(l>=s&&r<=t)return c[x];int mid=(l+r)>>1;down(x);
	if(s>mid)return query(x<<1|1,mid+1,r,s,t);
	else{
		if(t<=mid)return query(x<<1,l,mid,s,t);
		return max(query(x<<1,l,mid,s,t),query(x<<1|1,mid+1,r,s,t));
	}
}int ans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++)cin >>a[i];
	for(int i = 1;i <= n;i++)f.add(a[i]),pre[i]=f.ans; 
	for(int i= n;i >= 1;i--)g.add(a[i]),last[i]=g.ans;
	build(1,1,n);
	for(int i = 1;i < n;i++){
		change(1,1,n,pos[a[i]]+1,i,1);pos[a[i]]=i;
		ans=max(ans,query(1,1,n,1,i)+last[i+1]);
	}cout <<ans;
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

这是一篇视频题解。

![](bilibili:BV12EQDYWEFU?t=957)

[参考代码](https://atcoder.jp/contests/abc397/submissions/63800323)

---

## 作者：_Weslie_ (赞：0)

ABC 没见过这么简单的 F，感觉最多 $1500$ 不能再多了。

## Solution AT_abc397_f

### Idea

设 $[l,r]$ 表示 $\{a_l,a_{l+1},\cdots,a_r\}$。

设 $F(l,r)$ 表示 $[l,r]$ 中不同数的个数。

我们把三个区间分别表示为：第一段 $[1,l]$、第二段 $[l+1,r]$ 以及第三段 $[r+1,n]$。

我们先预处理出对于每一个 $i$，$F(1,i)$ 和 $F(i,n)$。这一部分是简单的（直接开一个桶就可以）。

然后我们考虑枚举 $r$。因为 $ans=F(1,l)+F(l+1,r)+F(r+1,n)$，所以我们需要维护 $F(1,l)+F(l+1,r)$ 的最大值。

这个如何维护呢？我们考虑建一棵区间修改区间 $\max$ 的线段树，维护 $F(1,l)+F(l+1,r)$。

我们考虑记录 $pos_i$ 为 $a_i$ 上一次出现的位置。不难发现，对于 $pos_i+1\le l\le i-1$，都有 $a_i$ 在 $[l+1,i]$ 中是第一次出现的，也就是说，$a_i$ 对这些 $F(1,l)+F(l+1,i)$ 贡献为 $1$。因为这一段 $l$ 是连续的，所以我们可以用线段树来维护。

然后统计答案是简单的，只需要枚举 $r$，用线段树找出 $F(1,l)+F(l,r)$ 的最大值（其中 $1\le l<r$）。

### Code

```
#include<bits/stdc++.h>
// #define int long long
using namespace std;
inline int read(){
	int x=0,y=1;
	char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-')y=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*y;
}
const int N=500005;
int n,q,a[N],tr[4*N],mrk2[4*N],lst[N],ansl[N],ansr[N],mp[N],pre[N];
void pd(int l,int r,int cntt){
	if(l==r)return;
	int mid=(l+r)>>1;
	tr[cntt*2]+=mrk2[cntt];
	tr[cntt*2+1]+=mrk2[cntt];
	mrk2[cntt*2]+=mrk2[cntt];
	mrk2[cntt*2+1]+=mrk2[cntt];
	mrk2[cntt]=0;
	return;
}
int build2(int l,int r,int cntt){
	if(l==r)return tr[cntt]=ansl[l];
	int mid=(l+r)>>1;
	return tr[cntt]=max(build2(l,mid,cntt*2),build2(mid+1,r,cntt*2+1));
}
int add2(int l,int r,int cntt,int al,int ar,int y){
	pd(l,r,cntt);
	if(l>ar||r<al)return tr[cntt];
	if(l>=al&&r<=ar){
		mrk2[cntt]+=y;
		return tr[cntt]=tr[cntt]+y; 
	}
	int mid=(l+r)>>1;
	return tr[cntt]=max(add2(l,mid,cntt*2,al,ar,y),add2(mid+1,r,cntt*2+1,al,ar,y));
}
int src2(int l,int r,int cntt,int sl,int sr){
	pd(l,r,cntt);
	if(l>sr||r<sl)return 0;
	if(l>=sl&&r<=sr)return tr[cntt];
	int mid=(l+r)>>1;
	return max(src2(l,mid,cntt*2,sl,sr),src2(mid+1,r,cntt*2+1,sl,sr));
}
signed main(){
	n=read();
	for(int i=1;i<=n ;i++)a[i]=read();	
    for(int i=1;i<=n;i++){
        mp[a[i]]++;
        ansl[i]=ansl[i-1];
        if(mp[a[i]]==1)ansl[i]++;
    }
    memset(mp,0,sizeof mp);
    for(int i=n;i>=1;i--){
        mp[a[i]]++;
        ansr[i]=ansr[i+1];
        if(mp[a[i]]==1)ansr[i]++;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        pre[i]=lst[a[i]];lst[a[i]]=i;
    }
    build2(1,n,1);
    for(int i=1;i<=n;i++){
        int l=pre[i];if(l==0)l=1;
        if(l!=i)add2(1,n,1,l,i-1,1);
        ans=max(ans,ansr[i+1]+src2(1,n,1,1,i-1));
    }
    printf("%d",ans);
	return 0;
}

---

## 作者：doumingze (赞：0)

维护一段区间内数字种类数量还不会做的先去把 C 写了再过来。

有两个游标，那就考虑枚举一个游标的位置，并考虑是否能够很快求出另一个游标的位置。我这里的做法是枚举后一个游标（记其位置为 $i$，代表第三段的起点，即计算 $[i,n]$ 内的答案），计算前一个游标在 $[1, i-1]$ 之间的最大答案。

令 $j$ 为第二段的起点，考虑在枚举的过程中动态维护对于每一个 $j \in [2, i-1]$ 的答案（即当断点为 $j$ 的时候最大的第一段与第二段的权值和，记为 $g_j$），求一次最大值即可。

考虑枚举的过程中每一个 $i$ 对这些答案的贡献有什么变化。$i$ 位置的 $g_i$ 先初始化为前 $i-1$ 个数作为一段时的答案。我们发现，记录 $a_i$ 这个数在序列中上一次出现的位置为 $k$，那么加入一个 $i$ 之后（游标变为 $i+1$），会对 $j \in [k + 1, i]$ 这段区间内所有的 $g_j$ 产生一个 $+1$ 的贡献。这一段请读者画图理解。

那么区间加、区间求 $\max$，不难想到线段树。于是题就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define lc (u << 1)
#define rc (u << 1 | 1)

typedef long long LL; 
const int N = 3e5 + 10, M = 2 * N;
int n;
int a[N], pre[N], las[N];
int cnt[N], cnt1[N], cur, cur2;
struct tree{
	int l, r;
	LL maxv, add;
}tr[4 * N];

void pushup(int u)
{
	tr[u].maxv = max(tr[lc].maxv, tr[rc].maxv);
}

void pushdown(int u)
{
	if(tr[u].add)
	{
		tr[lc].maxv += tr[u].add;
		tr[rc].maxv += tr[u].add; 
		tr[lc].add += tr[u].add;
		tr[rc].add += tr[u].add;
		tr[u].add = 0;
	}
}

void build(int u, int l, int r)
{
	tr[u] = {l, r, 0, 0};
	if(l == r) return;
	int mid = l + r >> 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
}

void update(int u, int l, int r, LL k)
{
	if(tr[u].l >= l && tr[u].r <= r)
	{
		tr[u].maxv += k;
		tr[u].add += k;
		return;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if(l <= mid) update(lc, l, r, k);
	if(mid < r) update(rc, l, r, k);
	pushup(u);
}

int query(int u, int l, int r)
{
	if(tr[u].l >= l && tr[u].r <= r) return tr[u].maxv;
	int mid = tr[u].l + tr[u].r >> 1;
	int ret = 0;
	pushdown(u);
	if(l <= mid) ret = query(lc, l, r);
	if(mid < r) ret = max(ret, query(rc, l, r));
	return ret;
}

int main()
{
	cin >> n;
	build(1, 1, n);
	for(int i = 1; i <= n; i ++)
	{
		scanf("%d", &a[i]);
		pre[i] = las[a[i]];
		las[a[i]] = i;
		if(!cnt[a[i]]) cur ++;
		cnt[a[i]] ++;
	}
	cnt[a[1]] --;
	if(!cnt1[a[1]]) cur2 ++;
	cnt1[a[1]] ++;
	if(!cnt[a[1]]) cur --;
	update(1, pre[1] + 1, 1, 1);
	cnt[a[2]] --;
	if(!cnt1[a[2]]) cur2 ++;
	cnt1[a[2]] ++;
	if(!cnt[a[2]]) cur --;
	update(1, 2, 2, query(1, 1, 1));
	update(1, pre[2] + 1, 2, 1);
	int ans = 0;
	for(int i = 3; i <= n; i ++)
	{
		ans = max(ans, cur + query(1, 2, i - 1));
		update(1, i, i, cur2);
		if(!cnt1[a[i]]) cur2 ++;
		cnt1[a[i]] ++;
		update(1, pre[i] + 1, i, 1);
		cnt[a[i]] --;
		if(!cnt[a[i]]) cur --;
	}
	printf("%d\n", ans);
	return 0;
}

```

*由于本题是赛后 50s 过的，并且在赛后发生了一些其他令我难以忘却、难以释怀的事情，有感而发，作此篇。*

*遗憾作为生命的一条线索，贯穿着我们的生活。*

---

## 作者：include13_fAKe (赞：0)

简单线段树题。晚上因为体育训练+英语补习导致 ABC 没打成，没看题解过了。

但我们机房咋全卡在 D 上面了呢？


---

看到三段区间，可以用 [P9746](https://www.luogu.com.cn/problem/P9746) 的方法将左边两端区间一起维护。设 $ans1_i$ 表示前 $i$ 个数分裂为两段的最大答案。

因为 $O(n^2)$ 计算无法承受，所以考虑 $O(n\log n)$ 的计算方法。

维护每一个数字最先出现的位置。以及在 $[1,i]$ 中最后出现的位置（如果存在）。对于每一个 $i$，都要从 $[1,i)$ 扫一遍，求出 **开始位置 $\le i$ 的数和结束位置 $>i$ 的数的和** 的最大值。

用线段树优化计算过程，具体而言，对于每一个 $i$，若这个数是 **第一次出现**，将 $[i,n]$ 距离内的数全部 $+1$。

巡到所有的数时，因为肯定是当前最后一次出现的，考虑将该数的 $[1,i-1]$ 部分的贡献值全部改为 $1$。需要进行一定的差分。

查询线段树 $[1,i]$ 的最大值即可。

对于最后一个区间，直接暴力计算，设 $ans2_i$ 表示 $[i,n]$ 中出现的不同的数的数量，最终答案即为 $\max_{2\le i\le n-1}ans1_i+ans2_{i+1}$。

时间复杂度 $O(n\log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=3*114514;
int ans1[N];	//左边两个区间的答案 
int ans2[N];	//右边区间的答案 
struct node{
	int l,r;
	int max1;
	int tag;	//标记  
}tree[N*8];
int n; 
int a[N];
bool st[N];	//是否前面已经有了数 
int ed[N];	//最后出现位置  
void pushup(int id){
	tree[id].max1=max(tree[id*2].max1,tree[id*2+1].max1);
}
void pushdown(int id){
	tree[id*2].max1+=tree[id].tag;
	tree[id*2].tag+=tree[id].tag;
	tree[id*2+1].max1+=tree[id].tag;
	tree[id*2+1].tag+=tree[id].tag;
	tree[id].tag=0;
}
void build(int id,int l,int r){
//	cout<<id<<' '<<l<<' '<<r<<endl;
	tree[id].l=l,tree[id].r=r;
	if(l==r){
		tree[id].max1=0,tree[id].tag=0;
		return;
	}
	int mid=l+r>>1;
	build(id*2,l,mid),build(id*2+1,mid+1,r);
	pushup(id);
} 
void modify(int id,int l,int r,int x){
	if(l>r)	return;
	int l1=tree[id].l,r1=tree[id].r;
	pushdown(id);
	if(l1>=l&&r1<=r){
		tree[id].tag+=x;
		tree[id].max1+=x;
		return;
	}
	int mid=l1+r1>>1;
	if(l<=mid)	modify(id*2,l,r,x);
	if(r>mid)	modify(id*2+1,l,r,x);
	pushup(id);
}
int query(int id,int l,int r){
	int l1=tree[id].l,r1=tree[id].r;
	pushdown(id);
	if(l1>=l&&r1<=r)	return tree[id].max1;
	int mid=l1+r1>>1;
	int ret=0;
	if(l<=mid)	ret=max(ret,query(id*2,l,r));
	if(r>mid)	ret=max(ret,query(id*2+1,l,r));
	pushup(id);
	return ret;
}
int include13=0;
int cx[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		if(!st[a[i]]){
			st[a[i]]=1;
			modify(1,i,n,1);
		}
		if(ed[a[i]]){
			modify(1,1,ed[a[i]]-1,-1);
		}
		ed[a[i]]=i;
		modify(1,1,i-1,1);
		if(i>=2){
			ans1[i]=query(1,1,i);
//			cout<<ans1[i]<<' ';
		}
	} 
//	cout<<ans1[n]<<endl;
	for(int i=n;i>=3;i--){
		cx[a[i]]++;
		if(cx[a[i]]==1)	ans2[i]=ans2[i+1]+1;
		else	ans2[i]=ans2[i+1];
	}
	for(int i=2;i<n;i++){
		include13=max(include13,ans1[i]+ans2[i+1]);
	}
	cout<<include13<<endl;
//	cout<<endl;
} //ABC397F 
```

---

## 作者：_zuoqingyuan (赞：0)

# 题意简述

给定一个长为 $n$ 的序列，将序列划分为非空的三段 $[1,i],[i+1,j],[j+1,n]$，使得各段中数字种类数之和最大。

# 思路分析

下文中，我们称 $x$ 第一次出现的位置 $p$ 对序列的数字种类数有贡献。记数字 $x$ 上一次出现的位置为 $lst_x$（若第一次出现则 $lst_x=0$）。

首先预处理出后缀的数字种类数，然后枚举 $j$，这下只需要考虑如何找到最优的 $i<j$。

注意到将 $[1,j]$ 划分成 $[1,i],[i+1,j]$。对于 $[1,j]$ 有贡献的位置，无论被划分到 $[1,i]$ 还是 $[i+1,j]$，都仍然对前两段产生 $1$ 的贡献，我们称这部分的贡献为基础贡献。但对于 $1\le lst_{a_{p}}\le i<p$ 的位置 $p$，则产生的新的贡献。我们称这些位置产生的贡献为额外贡献。

考虑扫描线，当扫到位置 $j$ 时，线段树上第 $i$ 个位置上是在 $i$ 分割产生的额外的贡献，因为基础贡献一定，所以尽可能让额外贡献最大，需查询前缀最大值。对于新加入的位置 $p$，当分割位置 $i$ 满足 $lst_{a_{p}}\le i<p$ 时会产生 $1$ 的额外贡献，需要区间加。

区间加区间 $\max$，懒标记线段树即可做到 $O(n\log n)$，最后加上后缀 $f_{j+1}$ 更新答案即可。

时间复杂度 $O(n\log n)$。


```cpp
#include <iostream>
#include <cstdio>
#define ls (p<<1)
#define rs (p<<1|1)
using namespace std;
const int N=3e5+10;
struct sgt{
    int mx[N<<2],tag[N<<2];
    void push_up(int p){
        mx[p]=max(mx[ls],mx[rs]);
    }
    void push_down(int p){
        if(!tag[p])return;
        mx[ls]+=tag[p],tag[ls]+=tag[p];
        mx[rs]+=tag[p],tag[rs]+=tag[p];
        tag[p]=0;
    }
    void build(int p,int l,int r){
        mx[p]=tag[p]=0;
        if(l==r)return;int mid=(l+r)>>1;
        build(ls,l,mid),build(rs,mid+1,r);
    }
    void change(int p,int l,int r,int L,int R,int v){
        if(L<=l&&r<=R){
            mx[p]+=v,tag[p]+=v;
        }else{
            int mid=(l+r)>>1;push_down(p);
            if(L<=mid)change(ls,l,mid,L,R,v);
            if(R>mid)change(rs,mid+1,r,L,R,v);
            push_up(p);
        }
        return;
    }
    int ask(int p,int l,int r,int L,int R){
        if(L<=l&&r<=R)return mx[p];
        int mid=(l+r)>>1,cnt=0;push_down(p);
        if(L<=mid)cnt=max(cnt,ask(ls,l,mid,L,R));
        if(R>mid)cnt=max(cnt,ask(rs,mid+1,r,L,R));
        push_up(p);return cnt;
    }
}tr;
int n,f[N],t[N],lst[N],ans,a[N],res;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",a+i);
    for(int i=n;i>=1;i--){
        if(!t[a[i]])f[i]++;
        t[a[i]]++,f[i]+=f[i+1];
    }
    for(int i=1;i<=n;i++)t[i]=0;
    tr.build(1,1,n);
    for(int i=1;i<=n;i++){
        if(!t[a[i]])res++;
        if(lst[a[i]])tr.change(1,1,n,lst[a[i]],i-1,1);
        if(i>1)ans=max(ans,f[i+1]+res+tr.ask(1,1,n,1,i-1));
        t[a[i]]++,lst[a[i]]=i;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：AAA404 (赞：0)

简单题，F<<E。

考虑两个分割点 $l,r$ 把序列分为 $[1,l],[l+1,r],[r+1,n]$ 三段，枚举 $r$。

考虑分别计算三段，最后一段可以扫描线时直接拿桶维护。

对于第一部分，可以预处理出前缀颜色数 $C_l$，这是 naive  的。

那么所有问题来到中间一部分，计算 $[l+1,r]$ 的颜色数，记为 $f(l+1,r)$。

要找的其实是最大的 $C_l+f(l+1,r)$，考虑扫描线过程中加入一个数会对其同颜色前缀后一个位置到本身的 $f$ 值有 $1$ 的贡献，即 $[pre_{a_r}+1,r]$ 均自增。

然后发现是区间加，前缀查最值，线段树一下就行，初始值就是 $C_l$。

时间复杂度：$O(n\log n)$，代码很好写就不放了。

---

## 作者：lzyqwq (赞：0)

记 $w(l,r)$ 表示 $[l,r]$ 的颜色数。若 $l>r$ 则为 $0$。

首先容易处理出 $w(1,x)$ 和 $w(x,n)$。考虑枚举第二个分割位置 $j$，那么第一个分割位置为 $i$ 时贡献为 $w(1,i)+w(i+1,j)+w(j+1,n)$。记 $p_i$ 为 $i$ 的前驱。考虑扫到每个 $j$ 时维护 $f_i=w(1,i)+w(i+1,j)$，则 $j$ 右移 $1$ 时会对于 $i\in [p_j,j-1]$ 的 $f_i$ 产生 $1$ 的增量。

此时需要支持区间加、区间查询最大值。线段树维护即可。

时间复杂度 $\mathcal{O}(n\log n)$。空间复杂度 $\mathcal{O}(n)$。

---

## 作者：xxr___ (赞：0)

### 闲话：
还是挺典的题，场上大概十分钟左右切，代码也很好写，记录一下。
### 思路：
首先看到分成三段，就不难想到先找一个前缀分成两段，在加上最后那个后缀的贡献，后者很简单，考虑前者怎么求？

- 首先，如果所有字符都不相同，再怎么划分都是 $i$ 个对吧，如果出现了好几次，令一个位置的数和他最近的相同的数的位置是 $j$，那么如果我们断点选择 $[j,i-1]$ 就能把这个颜色计算两遍，这是我们想要得到的，因为要最大化嘛。
- 然后一个做法便呼吁出来了，对于所有的这样的 $(i,j),j\leq i,a_j=a_i$ 我们将 $[j,i-1]$ 在线段树上加一，最后求个最大值加上那些只出现了一次的那些数的个数再加上后缀的那个取个最大值就好了嘛。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define pre(i,l,r) for(int i=(l);i>=(r);--i)
typedef long long ll;
const int N=2e6+5;
int a[N],lst[N],tot[N],lz[N],t[N],n;
ll ls(int p){
	return p<<1;
}
ll rs(int p){
	return p<<1|1;
}
void pushup(int p){
	t[p]=max(t[ls(p)],t[rs(p)]);
}
void tag(int p,int l,int r,ll k){
	t[p]+=k;
	lz[p]+=k;
}
void pushdown(int p,int l,int r){
	int mid=(l+r)>>1;
	tag(ls(p),l,mid,lz[p]);
	tag(rs(p),mid+1,r,lz[p]);
	lz[p]=0;
}
void update(int p,int l,int r,int L,int R,ll k){
	if(L<=l&&R>=r){
		tag(p,l,r,k);
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(p,l,r);
	if(L<=mid){
		update(ls(p),l,mid,L,R,k);
	}
	if(R>=mid+1){
		update(rs(p),mid+1,r,L,R,k);
	}
	pushup(p);
}
ll query(int p,int l,int r,int L,int R){
	if(L<=l&&R>=r){
		return t[p];
	}
	int mid=(l+r)>>1;
	pushdown(p,l,r);
	ll s=0;
	if(L<=mid){
		s=max(s,query(ls(p),l,mid,L,R));
	}
	if(R>=mid+1){
		s=max(s,query(rs(p),mid+1,r,L,R));
	}
	return s;
}
bool vs[N];

int32_t main(){
	cin>>n;
	rep(i,1,n) cin>>a[i];
	pre(i,n,1){
		tot[i]=tot[i+1];
		if(!vs[a[i]]){
			vs[a[i]]=1;
			tot[i]++;
		}
	}
	fill(vs+1,vs+n+1,0);
	int cnt=0,mx=0;
	rep(i,1,n-1){
		if(lst[a[i]]){
			update(1,1,n,lst[a[i]],i-1,1);
		}else{
			++cnt;
		}
		lst[a[i]]=i;
		mx=max((long long)mx,tot[i+1]+cnt+query(1,1,n,1,i));
	}
	cout<<mx;
	return 0;
}
```

---

## 作者：wflhx2011 (赞：0)

因为是 C 题加强版，发现可以直接用 C 题做法预处理出第一段和第三段的答案。

设 $ans1_i$ 表示从 $1$ 到 $i$ 的答案，$ans2_i$ 表示从 $i$ 到 $n$ 的答案。

那么只需先枚举一个断点 $i$，在枚举第二个断点 $j$ 时，顺便把第二段的答案 $res(i+1,j)$ 求出，再分别加上 $ans1_i$，$ans2_j$，最终答案即为和的最大值。

上面为 $O(n^2)$ 暴力，考虑优化。

既然是求最大值考虑用数据结构。首先一定是要枚举一个断点的，因为顺序枚举，所以考虑保留第二个断点，直接求出前两段答案和的最大值，这样和在现在一定最大。

那么可以用线段树维护。对于 $ans1$ 可以在建树时加到线段树。对于遍历到的每个数，考虑求出它贡献的范围。

设 $pre_i$ 表示 $a_i$ 上次出现的位置，那么这个数会对起点在 $[pre_i+1,i]$ 区间产生 $1$ 的贡献，也就是第一个断点在 $[pre_i,i-1]$ 的区间。

那就是线段树的区间加和区间最大值了。

最后加上最后一段的答案，不断取最大值。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300005],pre[300005],ans1[300005],ans2[300005],ans,tr[1200005],tag[1200005];
inline void pushup(int rt)
{
	tr[rt]=max(tr[rt<<1],tr[rt<<1|1]);
}
void build(int l,int r,int rt)
{
	if(l==r)
	{
		tr[rt]=ans1[l];
		return ;
	}
	int mid=(l+r)/2;
	build(l,mid,rt<<1);
	build(mid+1,r,rt<<1|1);
	pushup(rt);
	return ;
}
void pushdown(int rt)
{
	if(tag[rt])
	{
		tr[rt<<1]+=tag[rt];
		tr[rt<<1|1]+=tag[rt];
		tag[rt<<1]+=tag[rt];
		tag[rt<<1|1]+=tag[rt];
		tag[rt]=0; 
	}
}
void add(int L,int R,int c,int l,int r,int rt)
{
	if(L<=l&&r<=R)
	{
		tr[rt]+=c;
		tag[rt]+=c;
		return ;
	}
	pushdown(rt);
	int mid=(l+r)/2;
	if(L<=mid)
		add(L,R,c,l,mid,rt<<1);
	if(mid+1<=R)
		add(L,R,c,mid+1,r,rt<<1|1);
	pushup(rt);
	return ;
}
int qu(int L,int R,int l,int r,int rt)
{
	if(L<=l&&r<=R)
		return tr[rt];
	pushdown(rt);
	int mid=(l+r)/2,res=0;
	if(L<=mid)
		res=max(res,qu(L,R,l,mid,rt<<1));
	if(mid+1<=R)
		res=max(res,qu(L,R,mid+1,r,rt<<1|1));
	return res; 
}
unordered_map<int,int> m;
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		pre[i]=m[a[i]];
		m[a[i]]=i;
		ans1[i]=m.size();
	}
	m.clear();
	for(int i=n;i>=1;i--)
	{
		m[a[i]]=i;
		ans2[i]=m.size();
	}
	build(1,n,1);
	for(int i=2;i<n;i++)
	{
		add((pre[i]?pre[i]:1),i-1,1,1,n,1);
		ans=max(qu(1,i-1,1,n,1)+ans2[i+1],ans);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：0)

## 开始解题！

跟 C 题是差不多的。

首先考虑 $pre_i$ 表示 $a_1 \sim a_i$ 不同数字的数量，$suf_i$ 表示 $a_i \sim a_n$ 不同数字的数量。

然后我们再令 $lst_i$ 表示 $a_i$ 上一次出现的位置，若不存在，即为 $0$。

显然上面的这三个信息完全可以 $O(n)$ 预处理出来。如不懂，可以看代码。

令 $w(l, r)$ 表示 $a_l \sim a_r$ 不同数字的数量。而在 $r \rightarrow r + 1$ 的时候，对于 $l \in [lst_{i + 1}, i + 1]$，$w(l, r + 1) = w(l, r) + 1$，剩下的 $w(l, r + 1) = w(l, r)$，根据这个特点，我们可以在线段树上维护 $pre + w$ 的最大值，枚举 $i$，每次对 $[i, i]$ 和 $[lst_{i + 1}, i]$ 区间修改即可。由于这个最大值刚好是全局最大值所以直接加上根节点 $w_1$ 即可。

更详细的可以看代码。

code ：

```cpp
#include <bits/stdc++.h>
#define ll unsigned long long
#define db double
#define vec vector
#define pll pair<ll, ll>
#define mkp make_pair
#define endl "\n"

using namespace std;

const ll mod = 998244353;

namespace fastio {
	char buf[1 << 21], *p1 = buf, *p2 = buf;
	
	const ll getc() {
	    return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
	}
	
	const ll read() {
		ll x = 0, f = 1;
		
		char ch = getc();
		
		while (ch < '0' || ch > '9') {
			if (ch == '-') f = -1; ch = getc();
		}
		
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();
		}
		
		return x * f;
	}
	
	const void write(ll x) {
		if (x < 0) {
			putchar('-'), x = -x;
		}
		
	    ll sta[35], top = 0;
	    
	    do {
	        sta[top++] = x % 10, x /= 10;
	    } while (x);
	    
	    while (top) putchar(sta[--top] + 48);
	}
}

#define rd fastio::read
#define wt fastio::write
#define gc fastio::getc

ll n, m, q, a[300005], lst[300005], las[300005], pre[300005], suf[300005]; // string s;

ll opt, l, r, ans = 0;

ll w[1200005], tag[1200005];

void update(ll u, ll l, ll r, ll x, ll L = 1, ll R = n) {
    if (l <= L && R <= r) {
        w[u] += x, tag[u] += x; return ;
    }
    
    w[u << 1] += tag[u], w[u << 1 | 1] += tag[u];
    
    tag[u << 1] += tag[u], tag[u << 1 | 1] += tag[u], tag[u] = 0;
    
    ll mid = (L + R) >> 1;
    
    if (l <= mid) {
        update(u * 2, l, r, x, L, mid);
    }
    
    if (r > mid) {
        update(u * 2 + 1, l, r, x, mid + 1, R);
    }
    
    w[u] = max(w[u << 1], w[u << 1 | 1]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
    
    ll i, j, k, x, y, z, res = 0, now;
    
    n = rd();
    
    for (i = 1; i <= n; i++) a[i] = rd();
    
    for (i = 1; i <= n; i++) {
        if (!las[a[i]]) {
            pre[i] = pre[i - 1] + 1;
        } else {
            pre[i] = pre[i - 1];
        }
        
        lst[i] = las[a[i]];
        
        las[a[i]] = i;
    }
    
    memset(las, 0, sizeof(las));
    
    for (i = n; i; i--) {
        if (!las[a[i]]) {
            suf[i] = suf[i + 1] + 1;
        } else {
            suf[i] = suf[i + 1];
        }
        
        las[a[i]] = i;
    }
    
    for (i = 1; i < n; i++) {
        ans = max(ans, suf[i + 1] + w[1]);
        
        update(1, i, i, pre[i], 1, n);
        
        update(1, lst[i + 1], i, 1, 1, n);
    }
    
    wt(ans);    
    
	return 0;
}
```

[AC record](https://atcoder.jp/contests/abc397/submissions/63903172)

---

