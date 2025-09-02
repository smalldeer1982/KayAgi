# Wonderful Impostors

## 题目描述

你是一位名为 Gigi Murin 的骄傲主播。今天，你将与编号为 $1$ 到 $n$ 的 $n$ 名观众进行一场游戏。

在游戏中，每位玩家要么是船员，要么是冒名顶替者。你并不知道每位观众的角色。

共有 $m$ 条编号为 $1$ 到 $m$ 的陈述，每条陈述要么为真，要么为假。对于每条从 $1$ 到 $m$ 的 $i$，陈述 $i$ 属于以下两种类型之一：

- $0\:a_i\:b_i$（$1 \leq a_i \leq b_i \leq n$）——在观众 $a_i, a_i + 1, \ldots, b_i$ 中没有冒名顶替者；
- $1\:a_i\:b_i$（$1 \leq a_i \leq b_i \leq n$）——在观众 $a_i, a_i + 1, \ldots, b_i$ 中至少有一名冒名顶替者。

回答 $q$ 个以下形式的问题：

- $l\:r$（$1 \leq l \leq r \leq m$）——陈述 $l, l + 1, \ldots, r$ 是否可能全部为真？

注意，题目不保证所有观众中至少有一名冒名顶替者，也不保证所有观众中至少有一名船员。

## 说明/提示

在第一个测试用例中，有 $4$ 名观众和 $3$ 条陈述。陈述如下：

- 陈述 $1$：在观众 $1$、$2$ 和 $3$ 中至少有一名冒名顶替者；
- 陈述 $2$：在观众 $2$、$3$ 和 $4$ 中至少有一名冒名顶替者；
- 陈述 $3$：在观众 $2$ 和 $3$ 中没有冒名顶替者。

可以看出，陈述 $1$、$2$ 和 $3$ 可能全部为真。例如，以下是其中一种可能的情况：

- 观众 $1$ 是冒名顶替者；
- 观众 $2$ 是船员；
- 观众 $3$ 是船员；
- 观众 $4$ 是冒名顶替者。

在第二个测试用例中，有 $5$ 名观众和 $2$ 条陈述。陈述如下：

- 陈述 $1$：在观众 $1$、$2$、$3$、$4$ 和 $5$ 中至少有一名冒名顶替者；
- 陈述 $2$：在观众 $1$、$2$、$3$、$4$ 和 $5$ 中没有冒名顶替者。

可以看出，陈述 $1$ 可能为真，陈述 $2$ 也可能为真。然而，陈述 $1$ 和 $2$ 不可能同时为真。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
4 3
1 1 3
1 2 4
0 2 3
1
1 3
5 2
0 1 5
1 1 5
3
1 1
2 2
1 2
1 2
0 1 1
1 1 1
2
1 1
2 2
7 9
1 2 2
1 4 5
0 5 6
1 2 2
1 1 1
0 4 7
0 3 7
0 2 7
0 6 6
5
1 5
2 6
3 7
4 8
5 9```

### 输出

```
YES
YES
YES
NO
YES
YES
YES
NO
YES
NO
YES```

# 题解

## 作者：conti123 (赞：6)

# CF2096F

[题目](https://codeforces.com/problemset/problem/2096/F)

### 暴力

显然有一个 $O(qm\log n)$ 的暴力，对于每组询问逐条便利语句，是 $0$ 类型则将区间 $[a_i,b_i]$ 赋值为 $0$。赋值完后将剩下的空位赋值为 $1$，并检查每个 $1$ 类型的语句是否合法。

## 优化

### 分析

考虑优化。

注意到题目不强制在线，只要求出 $mxl_i$ 为对于 $i$ 语句前面最前的语句使得语句 $[mxl_i,i]$ 可以同时成立。

显然 $mxl_i$ 单调不降，则可以用双指针维护。

我们用 $c_i$ 表示 $i$ 这个位置被 $0$ 语句覆盖的次数。

>新加入一个 $1$ 语句 $i$

我们只需要判断 $\min_{j=a_i}^{b_i}c_j$ 是否大于 $0$ 即可，等于则合法。

>删除一个 $0$ 语句 $i$

我们要让 $j\in[a_i,b_i]$ 的 $c_j$ 减一。

显然 $c$ 的维护可以开一颗线段树。

我们用 $mx_i$ 表示类型为 $1$ 且右端点为 $i$ 的询问的左端点的最大值。即 $mx_i=\max_{x_j=1,b_j=i}a_j$

>新加入一个 $0$ 语句 $i$

先将区间 $[a_i,b_i]$ 的 $c$ 加 $1$

考虑找出最大的区间 $[x,y]$ 满足 $x\le a_i,b_i\le y,\min_{j=x}^yc_j>0$，然后判断 $\max_{j=x}^ymx_j$ 是否小于 $x$ 即可，小于即合法。

>删除一个 $1$ 语句 $i$

考虑如何维护 $mx_{i}$，可以直接暴力的搞一个线段树维护 $mx_i$ 的最大值，再用 $n$ 个 `multiset` 维护 $mx_i$，这样单次修改的均摊复杂度是 $O(\log n)$ 的。

最后讲一下如何找到 $x,y$。可以得出 $x$ 为 $[0,a_i-1]$ 中最右边的 $c_x$ 为 $0$ 的位置再加 $1$，$y$ 为 $[b_i+1,n+1]$ 中最左边的 $c_y$ 为 $0$ 的位置再减 $1$。可以线段树上二分维护。

最终我们开两个线段树和 $n$ 个 `multiset`，总时间复杂度为 $O(m\log n)$，可以通过此题。

### 代码

代码：

```cpp
#define ls x<<1
#define rs x<<1|1
#define mid ((l+r)>>1)
struct TR_{
	int mi[N<<2],add[N<<2];
	void pushup(int x){
		mi[x]=min(mi[ls],mi[rs]);
	}
	void pushdown(int x){
		if(add[x]){
			int &ad=add[x];
			mi[ls]+=ad,mi[rs]+=ad;
			add[ls]+=ad,add[rs]+=ad;
			ad=0;
		}
	}
	int ask(int x,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)
			return mi[x];
		int res=1e9;
		pushdown(x);
		if(ql<=mid)
			res=min(res,ask(ls,l,mid,ql,qr));
		if(qr>mid)
			res=min(res,ask(rs,mid+1,r,ql,qr));
		return res;
	}
	void modify(int x,int l,int r,int ql,int qr,int k){
		if(ql<=l&&r<=qr){
			mi[x]+=k,add[x]+=k;
			return ;
		}
		pushdown(x);
		if(ql<=mid)
			modify(ls,l,mid,ql,qr,k);
		if(qr>mid)
			modify(rs,mid+1,r,ql,qr,k);
		pushup(x);
	}
	int askl(int x,int l,int r,int ql,int qr){
		if(l==r)
			return !mi[x]?l:n+1;
		pushdown(x);
		if(ql<=l&&r<=qr){
			if(!mi[ls])
				return askl(ls,l,mid,ql,qr);
			return askl(rs,mid+1,r,ql,qr);
		}
		int res=n+1;
		if(ql<=mid)
			res=min(res,askl(ls,l,mid,ql,qr));
		if(qr>mid)
			res=min(res,askl(rs,mid+1,r,ql,qr));
		return res;
	}
	int askr(int x,int l,int r,int ql,int qr){
		if(l==r)
			return !mi[x]?l:0;
		pushdown(x);
		if(ql<=l&&r<=qr){
			if(!mi[rs])
				return askr(rs,mid+1,r,ql,qr);
			return askr(ls,l,mid,ql,qr);
		}
		int res=0;
		if(ql<=mid)
			res=max(res,askr(ls,l,mid,ql,qr));
		if(qr>mid)
			res=max(res,askr(rs,mid+1,r,ql,qr));
		return res;
	}
}A;
multiset<int>ps[N];
struct TR__{
	int mx[N<<2];
	void pushup(int x){
		mx[x]=max(mx[ls],mx[rs]);
	}
	void modify(int x,int l,int r,int pos,int k,int type){
		if(l==r){
			if(type==1)
				ps[l].insert(k);
			else
				ps[l].erase(ps[l].find(k));
			if(!ps[l].empty())
				mx[x]=*ps[l].rbegin();
			else
				mx[x]=0;
			return ;
		}
		if(pos<=mid)
			modify(ls,l,mid,pos,k,type);
		else
			modify(rs,mid+1,r,pos,k,type);
		pushup(x);
	}
	int ask(int x,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)
			return mx[x];
		int res=0;
		if(ql<=mid)
			res=max(res,ask(ls,l,mid,ql,qr));
		if(qr>mid)
			res=max(res,ask(rs,mid+1,r,ql,qr));
		return res;
	}
}B;
int mxl[N];
int opt[N],opx[N],opy[N];
void cl(int n){
	for(int i=1;i<=4*n;i++)
		A.mi[i]=A.add[i]=0,B.mx[i]=0;
	for(int i=1;i<=n;i++)
		ps[i].clear();
}
void solve(){
	cin>>n>>m;
	int l=1;
	for(int r=1;r<=m;r++){
		int op,x,y;
		cin>>op>>x>>y;
		opt[r]=op,opx[r]=x,opy[r]=y;
		if(!op)
			A.modify(1,1,n,x,y,1);
		else
			B.modify(1,1,n,y,x,1);
		while(l<=r){
			if(!op){
				int al=A.askr(1,1,n,1,x)+1,ar=A.askl(1,1,n,y,n)-1;
				if(B.ask(1,1,n,al,ar)<al)
					break;
			}
			else
				if(A.ask(1,1,n,x,y)==0)
					break;
			if(!opt[l])
				A.modify(1,1,n,opx[l],opy[l],-1);
			else
				B.modify(1,1,n,opy[l],opx[l],-1);
			l++;
		}
		mxl[r]=l;
	}
	int q;
	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		cout<<(l>=mxl[r]?"YES\n":"NO\n");
	}
	cl(n);
}
```

---

## 作者：XZhuRen (赞：3)

线段树板子题，赛时怎么没写出来……

发现两种限制，我们称：

$x=0$ 为 $0$ 类线段。

$x=1$ 为 $1$ 类线段。

记线段为 $[l,r]$，左闭右闭。

合法的充要条件即所有 $1$ 类线段不被 $0$ 类线段的并集覆盖。

首先发现容易求的是每个右端点的最左左端点。

然后考虑扫描线的过程会带来什么：

每次增量一条线段只会使得与它有关的不合法：

考虑这次增量的是什么线段：

>$0$ 类：每次右移左端点使得没有 $1$ 连续段包含它。

>$1$ 类：每次右移左端点使得它的连续段不会包含任意一个 $0$ 类。

考虑维护：

第一种，判断区间内是否有线段包含它。这是简单的二维前缀问题，直接加入一条 $1$ 类的时候对于区间 $[1,l]$ 记录值 $r$，判断时取左端点 $l$ 上是否有值不大于 $r$。

第二种，做区间覆盖，标记永久化线段树即可，维护区间至少覆盖一次的点数。

查找连续段端点用的也是第二种线段树，直接线段树上二分即可。

其中第一种线段树精细实现可以做到 $\mathcal{O}(\log n)$，我比较懒直接用了 `multiset`，多了一个 $\log$。

[提交记录](https://codeforces.com/contest/2096/submission/317333850)，代码不想放。

---

## 作者：ddxrS_loves_zxr (赞：2)

先考虑对于一次询问我们可以如何判断。

将询问区间内所有的 0 类型的条件拿出来，并将它们所对应的区间加 $1$。之后看每一个 1 类型的条件，要求在它对应的区间里存在至少一个位置为 $0$，即不会被若干 0 类型的条件的并所包含。

接下来考虑多次询问怎么做。如果对于每一个 $i$ 我们可以求出一个最小的 $j$ 使得区间 $[j,i]$ 中的条件都满足限制，那么对于一个 $r=i$ 的询问，只需要满足 $j\le l$ 即可。

让我们考虑用双指针来维护。当我们新加入一个条件 $[L,R]$ 后：

- 若为 0 类型，那么它可能自己或与左右的区间合并起来来使得一个 1 类型的条件被包含。注意到，这样 1 类型的条件一定与当前新加入的 0 类型条件有交，否则它会在之前就被判断掉。所以，我们每次可以求出 $[1,L]$ 中最后一个为 $0$ 的位置 $ql$ 和 $[R,n]$ 中第一个为 $0$ 的位置 $qr$，之后就只需要看是否存在一个 1 类型的条件被 $[ql+1,qr-1]$ 包含，被包含就说明现在不合法，左指针需要增加。

- 若为 1 类型，要不合法就只可能是它被若干 0 类型条件的并所包含，若是其它 1 类型的条件不合法也会在之前就被判断掉。当然，这个也很好判断，只需要看 $[L,R]$ 的最小值是否为 $0$，若不为 $0$ 就说明现在不合法，左指针需要增加。

说一些实现上的事情。对于 0 类型的条件，可以使用线段树维护区间加减，区间 min 和区间最左边及最右边的最小值位置，这些都比较常规。对于 1 类型的条件，同样使用线段树维护每个右端点所对应的左端点的最大值，由于有加有删，所以可以在每个叶子上用一个 multiset 来维护存在的值。这样，对于每次询问 $[ql+1,qr-1]$ 中是否有 1 类型的条件，就只需要看区间 $[ql+1,qr-1]$ 中最大的左端点是否大于等于 $ql+1$。

时间复杂度 $O(m\log n)$。

更具体的可以看代码，~~虽然这份代码写得很丑~~。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
const int N = 2e5 + 5, inf = 0x3f3f3f3f;
int n, m, q, ans[N];
int p[N], l[N], r[N];
vector<pair<int, int> > que[N];
int tr[N << 2], pr[N << 2], sf[N << 2], tag[N << 2];
multiset<int> st[N]; int mn[N << 2];
inline void clear(int p, int l, int r) {
	int mid = l + r >> 1;
	tr[p] = tag[p] = 0, pr[p] = r, sf[p] = l, mn[p] = -inf;
	if(l == r) return st[l].clear(), void();
	clear(p << 1, l, mid), clear(p << 1 | 1, mid + 1, r);
}
inline void pushdown(int p) {
	tr[p << 1] += tag[p], tr[p << 1 | 1] += tag[p];
	tag[p << 1] += tag[p], tag[p << 1 | 1] += tag[p];
	tag[p] = 0;
}
inline void change(int p, int l, int r, int ql, int qr, int x) {
	int mid = l + r >> 1;
	if(ql <= l && r <= qr) return tr[p] += x, tag[p] += x, void();
	pushdown(p);
	if(ql <= mid) change(p << 1, l, mid, ql, qr, x);
	if(mid < qr) change(p << 1 | 1, mid + 1, r, ql, qr, x);
	tr[p] = min(tr[p << 1], tr[p << 1 | 1]);
    if(tr[p] == tr[p << 1]) sf[p] = sf[p << 1];
    else sf[p] = sf[p << 1 | 1];
    if(tr[p] == tr[p << 1 | 1]) pr[p] = pr[p << 1 | 1];
    else pr[p] = pr[p << 1];
}
inline int query(int p, int l, int r, int ql, int qr) {
	int mid = l + r >> 1;
	if(ql <= l && r <= qr) return tr[p];
	pushdown(p);
	if(qr <= mid) return query(p << 1, l, mid, ql, qr);
	else if(mid < ql) return query(p << 1 | 1, mid + 1, r, ql, qr);
	else return min(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
}
inline int askl(int p, int l, int r, int ql, int qr) {
	int mid = l + r >> 1;
	if(ql <= l && r <= qr) return (tr[p] == 0 ? pr[p] : 0);
	pushdown(p);
	if(qr <= mid) return askl(p << 1, l, mid, ql, qr);
	else if(mid < ql) return askl(p << 1 | 1, mid + 1, r, ql, qr);
	else return max(askl(p << 1, l, mid, ql, qr), askl(p << 1 | 1, mid + 1, r, ql, qr));
}
inline int askr(int p, int l, int r, int ql, int qr) {
	int mid = l + r >> 1;
	if(ql <= l && r <= qr) return (tr[p] == 0 ? sf[p] : n + 1);
	pushdown(p);
	if(qr <= mid) return askr(p << 1, l, mid, ql, qr);
	else if(mid < ql) return askr(p << 1 | 1, mid + 1, r, ql, qr);
	else return min(askr(p << 1, l, mid, ql, qr), askr(p << 1 | 1, mid + 1, r, ql, qr));
}
inline void update(int p, int l, int r, int x, int y) {
	int mid = l + r >> 1;
	if(l == r) {
		if(y > 0) st[l].insert(-y);
		else st[l].erase(st[l].find(y));
		if(!st[l].empty()) mn[p] = -(*st[l].begin());
		else mn[p] = -inf;
		return;
	}
	if(x <= mid) update(p << 1, l, mid, x, y);
	else update(p << 1 | 1, mid + 1, r, x, y);
	mn[p] = max(mn[p << 1], mn[p << 1 | 1]);
}
inline int ask(int p, int l, int r, int ql, int qr) {
    int mid = l + r >> 1;
	if(ql <= l && r <= qr) return mn[p];
	if(qr <= mid) return ask(p << 1, l, mid, ql, qr);
	else if(mid < ql) return ask(p << 1 | 1, mid + 1, r, ql, qr);
	else return max(ask(p << 1, l, mid, ql, qr), ask(p << 1 | 1, mid + 1, r, ql, qr));
}
void solve() {
    cin>>n>>m;
    clear(1, 1, n);
	for(int i = 1; i <= m; i++) cin>>p[i]>>l[i]>>r[i];
	cin>>q;
	for(int i = 1, l, r; i <= q; i++) cin>>l>>r, que[r].push_back({l, i});
	for(int L = 1, R = 1; R <= m; R++) {
        if(p[R] == 0) {
            change(1, 1, n, l[R], r[R], 1);
			while(L <= R) {
                int posl = askl(1, 1, n, 1, l[R]) + 1, posr = askr(1, 1, n, r[R], n) - 1;
				if(ask(1, 1, n, 1, posr) < posl) break;
				if(p[L] == 0) change(1, 1, n, l[L], r[L], -1);
				else update(1, 1, n, r[L], -l[L]);
				L++;
			}
		} else {
            update(1, 1, n, r[R], l[R]);
			while(L <= R) {
                if(query(1, 1, n, l[R], r[R]) == 0) break;
				if(p[L] == 0) change(1, 1, n, l[L], r[L], -1);
				else update(1, 1, n, r[L], -l[L]);
				L++;
			}
		}
		for(auto x : que[R]) ans[x.second] = (x.first >= L);
	}
	for(int i = 1; i <= q; i++) cout<<(ans[i] ? "YES" : "NO")<<'\n';
	for(int i = 1; i <= m; i++) que[i].clear();
}
int main() {
#ifdef ddxrS
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
	int t; cin>>t;
	while(t--) solve();
    cerr<<clock() * 1.0 / CLOCKS_PER_SEC<<'\n';
	return 0;
}
```

---

## 作者：MrPython (赞：2)

注意：全文左闭右开。

~~Hint 0: CF 的数据结构题难度自动 -500。~~

---

Hint 1: 若干个需求可能被同时满足的充分必要条件是什么？对于单次询问，如何暴力回答？

将所有没有内鬼的区间并起来，记作 $S$，那么 $S$ 中的任意一个人都是船员。倘若存在一个有内鬼的区间是 $S$ 的子集，便出现了冲突。

我们可以开一颗值域为 $n$ 的线段树，初始为 $0$，将所有没有内鬼的区间在线段树上执行区间 $+1$ 操作。然后对于所有有内鬼的区间挨个检查，若这段区间的最小值不是 $0$，则说明这段区间被完全包含掉了。

---

Hint 2：在线处理询问好像很难做。有什么离线处理的方法吗？

每个区间的回答都是 YES 或 NO，并且一段区间 $S$ 的子区间的回答一定不会劣于 $S$。由此我们联想到 [\[NOI2024\] 集合](https://www.luogu.com.cn/problem/P10785) 中的双指针离线。具体来说，固定左边界（记为 $l$），一直向右移动右边界直到出现冲突（记此时的右边界为 $r$），此时对于左边界为 $l$ 的所有询问，其右边界小于 $r$ 的都合法，大于等于 $r$ 的都不合法。

---

Hint 3：当新增一条区间内有内鬼的条件，该如何检查加入该条件后是否会产生冲突？请注意你的实现应该易于从中删除一组询问。

跟暴力做法类似，开一颗值域为 $n$ 的线段树，初始为 $0$。每加入一个区间内没有内鬼的条件，就在线段树上对应范围执行区间 $+1$ 操作。想要检查添加区间存在内鬼的条件后会不会出现冲突，只需要判断对应区间的最小值是不是 $0$ 就好了。删除也很简单，执行区间 $-1$ 操作即可。

---

Hint 4：当新增一条区间内没有内鬼的条件，该如何检查加入该条件后是否会产生冲突？

最为复杂的情况如图。黑色表示不存在内鬼的约束，红色表示存在内鬼的约束。  
![](https://cdn.luogu.com.cn/upload/image_hosting/am83rqbu.png)

若干个区间并起来的结果为若干个互不相交的大区间。添加一个新的区间只会对其中一小部分有影响，其他的不变。有影响的大区间范围可以通过在上面所说的线段树上二分取得。具体来讲，通过线段树二分找到第一个为 $0$ 的数。

找到一个大区间 $[l,r)$ 后，还需要判断这个大区间有没有完全包含一个存在内鬼的区间。这相当于要处理一个二维偏序问题：是否存在二元组 $(x,y)$ 满足 $l\leq x<r$ 且 $y \leq r$？再开一颗单点修改、区间 min 线段树，将第一关键字 $x$ 作为下标，线段树上存放**所有第一关键字为 $x$ 的二元组中最小的 $y$**。在新增 / 删除区间有内鬼的约束时，同步维护一个数组套 multiset，下标为 $x$ 的 multiset 存放所有第一关键字为 $x$ 的二元组所对应的 $y$，在线段树上同步取其最小值。查询时，查询 $[l,r)$ 的区间最小值是否小于 $r$ 即可。

```cpp
// https://github.com/Mr-Python-in-China/mp-oi-library/blob/main/library/
#include <mrpython/typical_segment_tree.hpp>
#include <mrpython/lazy_segment_tree.hpp>
#include <iostream>
#include <set>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
struct Question {
  bool c;
  size_t l, r;
};
struct AddMinNode {
  using T = ui;
  using Lazy = ui;
  static T merge_data(T l, T r) { return min(l, r); }
  static Lazy merge_lazy(T l, T r) { return l + r; }
  static T operate(T x, Lazy y, size_t) { return x + y; }
};
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t T;
  fin >> T;
  while (T--) {
    size_t n, m;
    fin >> n >> m;
    vector<Question> a(m);
    for (auto& i : a) {
      char c;
      fin >> c;
      i.c = c == '1';
      fin >> i.l >> i.r;
      --i.l;
    }
    size_t q;
    fin >> q;
    vector<pair<size_t, size_t>> ql(q);
    for (auto& [l, r] : ql) fin >> l >> r, --l;
    mrpython::lazy_segment_tree_from_node<AddMinNode>::type rgn(n, 0, 0);
    mrpython::typical_segment_tree_min<size_t> rgr(n, n + 1);
    vector<multiset<size_t>> rgv(n, {n + 1});

    vector<size_t> ans(m);
    for (size_t dl = 0, dr = 0; dl < m; ++dl) {
      auto check = [&](Question const& t) {
        if (t.c)
          return !rgn.getd(t.l, t.r);
        else {
          size_t rl = rgn.find_last_left(t.l - 1, [](ui x) { return x == 0; }) +
                      1,
                 rr = rgn.find_first_right(t.r, [](ui x) { return x == 0; });
          return rgr.get(rl, rr) > rr;
        }
      };
      while (dr < m && check(a[dr])) {
        if (a[dr].c) {
          rgv[a[dr].l].emplace(a[dr].r);
          rgr.set(a[dr].l, mrpython::const_function(*rgv[a[dr].l].begin()));
        } else
          rgn.set(a[dr].l, a[dr].r, 1);
        ++dr;
      }
      ans[dl] = dr;
      if (a[dl].c) {
        rgv[a[dl].l].erase(rgv[a[dl].l].find(a[dl].r));
        rgr.set(a[dl].l, mrpython::const_function(*rgv[a[dl].l].begin()));
      } else
        rgn.set(a[dl].l, a[dl].r, -1);
    }

    for (auto [l, r] : ql) fout << (r <= ans[l] ? "YES\n" : "NO\n");
  }
  return 0;
}
```

---

## 作者：Eternatis (赞：1)

限制显然有单调性，若每一条限制支持删除，我们可以和 NOI2024D1T1 一样，使用双指针维护每个左端点对应的最大右端点来直接回答询问。

我们需要考虑三个问题：如何 check 一个限制能否被加入，如何加入限制，如何删除限制。

考虑如何 check。若我们要加入一个 1 限制，我们只需要判断是否区间内每个位置都被 0 限制覆盖过，考虑到 0 限制的插入删除，我们用线段树维护每个位置的被覆盖次数，则操作只有区间加减 $1$ 与区间最小值。

若加入一个 0 限制，则稍微有些麻烦，我们展开分析一下：

我们称一个满足**每个位置**都被 **0 限制**覆盖过的区间为**被覆盖段**。当我们加入一个 0 限制时，不合法的充要条件是存在一个 1 限制，满足其之前与**零或多个**被覆盖段有交，而加入当前 0 限制后被**恰好一个**被覆盖段包含。第一个条件看似是废话，实际上告诉了我们一个重要的信息：包含这个 1 限制的被覆盖段就是加入 0 限制后新产生的被覆盖段！

我们考虑如何找到这个被覆盖段，设当前 0 限制对应的区间为 $[l,r]$，我们在维护覆盖次数的线段树上二分到最大的未被覆盖过的点 $l'$，且满足 $l'<l$，$r'$ 同理为满足 $r'>r$ 最小的未覆盖点，则 $[l'+1,r'-1]$ 就是新的被覆盖段。

我们要判断是否有 1 限制被 $[l'+1,r'-1]$ 包含，只需要判断右端点在这个区间里的限制，左端点最大值是否不小于 $l'+1$ 即可。考虑再用一棵线段树维护，在每个叶子上挂一个 set 来支持插入删除和查询最大值。

总复杂度 $O(n\log^2n)$。

可以参照代码理解。

code：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N    200010
#define int  long long
#define pii  pair<int,int>
#define st   first
#define ed   second
#define pb   push_back
#define il   inline
#define ins  insert
#define INF  0x3f3f3f3f3f3f3f3f
il int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int T=1,n,m,q,k;
int op[N],l[N],r[N],R[N];
struct node1{
	int w,tag;
};
struct sgt1{
	node1 t[N<<2];
	il void pushup(int x){
		t[x].w=min(t[x<<1].w,t[x<<1|1].w);
	}
	il void mdf(int x,int k){
		t[x].w+=k,t[x].tag+=k;
	}
	il void pushdown(int x){
		int &k=t[x].tag;
		mdf(x<<1,k),mdf(x<<1|1,k);
		t[x].tag=0;
	}
	il void build(int x,int l,int r){
		t[x].w=t[x].tag=0;
		if(l==r)return ;
		int mid=(l+r)>>1;
		build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	}
	il void upd(int x,int l,int r,int ql,int qr,int k){
		if(ql<=l&&qr>=r){mdf(x,k);return ;}
		pushdown(x);
		int mid=(l+r)>>1;
		if(ql<=mid)upd(x<<1,l,mid,ql,qr,k);
		if(qr>mid)upd(x<<1|1,mid+1,r,ql,qr,k);
		pushup(x);
	}
	il int que(int x,int l,int r,int ql,int qr){
		if(ql<=l&&qr>=r)return t[x].w;
		pushdown(x);
		int mid=(l+r)>>1,ans=INF;
		if(ql<=mid)ans=min(ans,que(x<<1,l,mid,ql,qr));
		if(qr>mid)ans=min(ans,que(x<<1|1,mid+1,r,ql,qr));
		return ans;
	}
	il int fnd(int x,int l,int r,int op){
		if(l==r)return l;
		pushdown(x);
		int mid=(l+r)>>1;
		if(op==0){
			if(t[x<<1|1].w==0)return fnd(x<<1|1,mid+1,r,op);
			else return fnd(x<<1,l,mid,op);
		}
		else{
			if(t[x<<1].w==0)return fnd(x<<1,l,mid,op);
			else return fnd(x<<1|1,mid+1,r,op);
		}
	}
	il int fd(int x,int l,int r,int ql,int qr,int op){
		if(ql<=l&&qr>=r){
			if(t[x].w==0)return fnd(x,l,r,op);
			else return -1;
		}
		pushdown(x);
		int mid=(l+r)>>1;
		if(qr<=mid)return fd(x<<1,l,mid,ql,qr,op);
		if(ql>mid)return fd(x<<1|1,mid+1,r,ql,qr,op);
		if(op==0){
			int w=fd(x<<1|1,mid+1,r,ql,qr,op);
			return w==-1?fd(x<<1,l,mid,ql,qr,op):w;
		}
		else{
			int w=fd(x<<1,l,mid,ql,qr,op);
			return w==-1?fd(x<<1|1,mid+1,r,ql,qr,op):w;
		}
	}
}T1;
struct node2{
	int w;
	set<pii> s;
};
struct sgt2{
	node2 t[N<<2];
	il void build(int x,int l,int r){
		t[x].w=0,t[x].s.clear();
		if(l==r)return ;
		int mid=(l+r)>>1;
		build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	}
	il void pushup(int x){
		t[x].w=max(t[x<<1].w,t[x<<1|1].w);
	}
	il void upd(int x,int l,int r,int p,pii k,int op){
		if(l==r){
			if(op==0)t[x].s.erase(k);
			else t[x].s.ins(k);
			if(t[x].s.empty())t[x].w=0;
			else t[x].w=(*t[x].s.rbegin()).st;
			return ;
		}
		int mid=(l+r)>>1;
		if(p<=mid)upd(x<<1,l,mid,p,k,op);
		else upd(x<<1|1,mid+1,r,p,k,op);
		pushup(x);
	}
	il int que(int x,int l,int r,int ql,int qr){
		if(ql<=l&&qr>=r)return t[x].w;
		int mid=(l+r)>>1,ans=0;
		if(ql<=mid)ans=max(ans,que(x<<1,l,mid,ql,qr));
		if(qr>mid)ans=max(ans,que(x<<1|1,mid+1,r,ql,qr));
		return ans;
	}
}T2;
il bool check(int id){
	if(op[id]==1)return T1.que(1,0,m,l[id],r[id])==0;
	else{
		int L=T1.fd(1,0,m,0,l[id]-1,0)+1,R=T1.fd(1,0,m,r[id]+1,m,1)-1;
		return T2.que(1,0,m,0,R)<L;
	}
}
il void add(int id){
	if(op[id]==0)T1.upd(1,0,m,l[id],r[id],1);
	else T2.upd(1,0,m,r[id],(pii){l[id],id},1);
}
il void del(int id){
	if(op[id]==0)T1.upd(1,0,m,l[id],r[id],-1);
	else T2.upd(1,0,m,r[id],(pii){l[id],id},0);
}
il void solve(){
	m=read()+1;n=read();
	for(int i=1;i<=n;i++)op[i]=read(),l[i]=read(),r[i]=read();
	T1.build(1,0,m),T2.build(1,0,m);
	for(int i=1,j=0;i<=n;i++){
		while(j<n&&check(j+1))j++,add(j);
		R[i]=j;del(i);
	}
	q=read();
	while(q--){
		int l=read(),r=read();
		if(R[l]>=r)puts("YES");
		else puts("NO");
	}
}
signed main(){
	T=read();
	while(T--)solve();
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：1)

设 $f_r$ 表示最小的左端点 $l$，使得 $[l,r]$ 区间的询问均可合法。在处理询问时，转化为判断是否 $f_r \le l$ 合法即可。

首先考虑如何求出 $f_i$。尝试使用双指针，当前 $[l,r]$ 区间的询问均合法，当加入 $r'=r + 1$ 后，若区间不合法，则进行 $l' = l + 1$ 操作直到 $[l',r']$ 合法。

那么现在的难点便是如何检验区间的合法性。

定义标记数组 $\{v_1,v_2,\cdots,v_n\}$，初始均为 $0$。当 $x_i = 0$ 时，进行区间加 $1$ 操作。当 $x_i = 1$ 时，若某一时刻 $\min\{v_{a_i},v_{a_{i + 1}},\cdots,v_{b_i}\} > 0$，则说明该时刻的情况不合法。当 $x_i = 1$ 时，我们可以直接通过线段树维护区间最小值来判断合法性。但是最棘手的部分是当加入 $x_i = 0$ 的操作时，会影响到之前 $x_i = 1$ 的部分。

令 $p_i$ 表示所有 $x_j = 1$ 且 $b_j = p_i$ 的操作所对应的 $a_j$ 的最大值，即 $p_i = \max\limits_{x_j = 1,b_j = i} \{a_j\}$。当增加一个 $x_i  = 0$ 的操作时，设 $[x,y]$ 表示在加入 $[a_i,b_i]$ 区间后，满足 $\min\{v_{x},v_{a_{i + 1}},\cdots,v_{y}\} > 0$ 且 $[a_i,b_i] \subseteq [x,y]$ 的最大区间，若 $\max \{p_x,p_{x + 1},\cdots,p_y\} < x$，即可说明该操作的合法性。考虑维护 $p_i$，线段树维护最大值即可。当然，由于涉及 $a_i$ 的删减，用 multiset 处理单点，后上传到线段树上即可实现。

最后考虑如何快速求出加入 $[a_i,b_i]$ 后的扩展区间 $[x,y]$。线段树与二分的结合显然可以实现，但是总时间复杂度为 $O(n \log^2 n)$，亲测会超时，故考虑线段树二分。注意，应该找到 $a_i$ 从左往右数第一个 $v_i$ 为 $0$，$b_i$ 右侧第一个为 $v_i$ 为 $0$ 的位置。

因此，最后的时间复杂度为 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define init(x) memset (x,0,sizeof (x))
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define pii pair <int,int>
using namespace std;
const int MAX = 2e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
struct node
{
    int ty,l,r;
} a[MAX];
int t,n,m,q,f[MAX];
multiset <int> s[MAX];
class seg1
{
    int n;vector <int> tree,tmp;
    void pushdown (int cur)
    {
        if (!tmp[cur]) return ;
        tree[cur << 1] += tmp[cur];tree[cur << 1 | 1] += tmp[cur];
        tmp[cur << 1] += tmp[cur];tmp[cur << 1 | 1] += tmp[cur];
        tmp[cur] = 0;
    }
    void pushup (int cur) {tree[cur] = min (tree[cur << 1],tree[cur << 1 | 1]);}
    public : 
    seg1 (int n) : n (n),tree (4 * n + 1,0),tmp (4 * n + 1,0) {}
    void modify (int cur,int l,int r,int x,int y,int v)
    {
        if (x <= l && y >= r)
        {
            tree[cur] += v;tmp[cur] += v;
            return ;
        }
        int mid = (l + r) >> 1;
        pushdown (cur);
        if (x <= mid) modify (cur << 1,l,mid,x,y,v);
        if (y > mid) modify (cur << 1 | 1,mid + 1,r,x,y,v);
        pushup (cur);
    }
    int query (int cur,int l,int r,int x,int y)
    {
        if (x <= l && y >= r) return tree[cur];
        int mid = (l + r) >> 1,res = INF;
        pushdown (cur);
        if (x <= mid) res = min (res,query (cur << 1,l,mid,x,y));
        if (y > mid) res = min (res,query (cur << 1 | 1,mid + 1,r,x,y));
        return res;
    }
    int search_L (int cur,int l,int r,int x,int y)
    {
        if (l == r) return !tree[cur] ? l : n + 1;
        pushdown (cur);
        if (x <= l && y >= r)
        {
            int mid = (l + r) >> 1;
            if (!tree[cur << 1]) return search_L (cur << 1,l,mid,x,y);
            else return search_L (cur << 1 | 1,mid + 1,r,x,y);
        }
        else
        {
            int mid = (l + r) >> 1,res = n + 1;
            if (x <= mid) res = search_L (cur << 1,l,mid,x,y);
            if (res == n + 1 && y > mid) res = search_L (cur << 1 | 1,mid + 1,r,x,y);
            return res;
        }
    }
    int search_R (int cur,int l,int r,int x,int y)
    { 
        if (l == r) return !tree[cur] ? l : 0;
        pushdown (cur);
        if (x <= l && y >= r)
        {
            int mid = (l + r) >> 1;
            if (!tree[cur << 1 | 1]) return search_R (cur << 1 | 1,mid + 1,r,x,y);
            else return search_R (cur << 1,l,mid,x,y);
        }
        else
        {
            int mid = (l + r) >> 1,res = 0;   
            
            if (y > mid) res = search_R (cur << 1 | 1,mid + 1,r,x,y);
            if (!res && x <= mid) res = search_R (cur << 1,l,mid,x,y);
            return res;
        }
    }
};
class seg2
{
    int n;vector <int> tree;
    void pushup (int cur) {tree[cur] = max (tree[cur << 1],tree[cur << 1 | 1]);}
    public :
    seg2 (int n) : n (n),tree (4 * n + 1,0) {for (int i = 1;i <= n;++i) s[i].clear ();}
    void modify (int cur,int l,int r,int x,int v,int ty)
    {
        if (l == r)
        {
            if (!ty) s[l].insert (v);
            else s[l].erase (s[l].find (v));
            if (!s[l].empty ()) tree[cur] = *(--s[l].end ());
            else tree[cur] = 0;
            return ;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) modify (cur << 1,l,mid,x,v,ty);
        else modify (cur << 1 | 1,mid + 1,r,x,v,ty);
        pushup (cur);
    }
    int query (int cur,int l,int r,int x,int y)
    {
        if (x <= l && y >= r) return tree[cur];
        int mid = (l + r) >> 1,res = 0;
        if (x <= mid) res = max (res,query (cur << 1,l,mid,x,y));
        if (y > mid) res = max (res,query (cur << 1 | 1,mid + 1,r,x,y));
        return res;
    }
};
int main ()
{
    t = read ();
    while (t--)
    {
        n = read ();m = read ();
        seg1 tr1 (n + 1);seg2 tr2 (n + 1);
        for (int i = 1;i <= m;++i) a[i].ty = read (),a[i].l = read (),a[i].r = read ();
        int l = 1,r = 0;
        while (r < m)
        {
            ++r;
            if (!a[r].ty) tr1.modify (1,1,n,a[r].l,a[r].r,1);
            else tr2.modify (1,1,n,a[r].r,a[r].l,0);
            while (l <= r) 
            {
                if (!a[r].ty)
                {
                    int dl = tr1.search_R (1,1,n,1,a[r].l) + 1,dr = tr1.search_L (1,1,n,a[r].r,n) - 1;
                    if (tr2.query (1,1,n,dl,dr) < dl) break;
                }
                else if (!tr1.query (1,1,n,a[r].l,a[r].r)) break;
                if (!a[l].ty) tr1.modify (1,1,n,a[l].l,a[l].r,-1);
                else tr2.modify (1,1,n,a[l].r,a[l].l,1);
                ++l;
            }
            f[r] = l;
        }
        q = read ();
        while (q--)
        {
            int l = read (),r = read ();
            puts (f[r] <= l ? "YES" : "NO");
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
```

---

