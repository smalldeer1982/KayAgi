# [ABC342G] Retroactive Range Chmax

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc342/tasks/abc342_g

長さ $ N $ の整数列 $ A=(A\ _\ 1,A\ _\ 2,\ldots,A\ _\ N) $ が与えられます。

$ Q $ 個の操作を順に処理してください。 操作は次の $ 3 $ 種類のいずれかです。

- タイプ $ 1 $ の操作は整数の $ 3 $ つ組 $ (l,r,x) $ で表され、$ i=l,l+1,\ldots,r $ に対して、$ A\ _\ i $ を $ \max\lbrace\ A\ _\ i,x\rbrace $ で置き換えることに対応する。
- タイプ $ 2 $ の操作は整数 $ i $ で表され、$ i $ 回目の操作を取り消すことに対応する（ただし、$ i $ 回目の操作はタイプ $ 1 $ の操作であり、これまでに取り消されていないことが保証される）。数列 $ A $ は、最初の状態からはじめてこれまでのタイプ $ 1 $ の操作のうち**取り消されていない**操作がすべて行われた状態になる。
- タイプ $ 3 $ の操作は整数 $ i $ で表され、現在の $ A\ _\ i $ の値を出力することに対応する。

## 说明/提示

### 制約

- $ 1\leq\ N\leq2\times10\ ^\ 5 $
- $ 1\leq\ A\ _\ i\leq10\ ^\ 9\ (1\leq\ i\leq\ N) $
- $ 1\leq\ Q\leq2\times10\ ^\ 5 $
- タイプ $ 1 $ の操作において、$ 1\leq\ l\leq\ r\leq\ N $ かつ $ 1\leq\ x\leq10\ ^\ 9 $
- タイプ $ 2 $ の操作において、$ i $ はそれ以前に与えられた操作の回数以下かつ $ 1\leq\ i $
- タイプ $ 2 $ の操作において、$ i $ 番目の操作はタイプ $ 1 $ の操作
- タイプ $ 2 $ の操作における $ i $ は重複しない
- タイプ $ 3 $ の操作において、$ 1\leq\ i\leq\ N $
- 入力はすべて整数
 
### Sample Explanation 1

はじめ、数列 $ A $ は $ (2,7,1,8,2,8) $ です。 $ 1,2,3 $ 回目の操作では $ A\ _\ 1,A\ _\ 3,A\ _\ 4 $ の値である $ 2,1,8 $ をそれぞれ出力してください。 $ 4 $ 回目の操作では $ A\ _\ 1,A\ _\ 2,A\ _\ 3,A\ _\ 4,A\ _\ 5 $ の値を $ \max\lbrace\ A\ _\ i,4\rbrace $ で置き換えます。 この操作の直後、$ A $ は $ (4,7,4,8,4,8) $ となります。 $ 5,6,7 $ 回目の操作ではこの時点での $ A\ _\ 1,A\ _\ 3,A\ _\ 4 $ の値である $ 4,4,8 $ をそれぞれ出力してください。 $ 8 $ 回目の操作では $ A\ _\ 3,A\ _\ 4,A\ _\ 5,A\ _\ 6 $ の値を $ \max\lbrace\ A\ _\ i,9\rbrace $ で置き換えます。 この操作の直後、$ A $ は $ (4,7,9,9,9,9) $ となります。 $ 9,10,11 $ 回目の操作ではこの時点での $ A\ _\ 1,A\ _\ 3,A\ _\ 4 $ の値である $ 4,9,9 $ をそれぞれ出力してください。 $ 12 $ 回目の操作では $ 4 $ 回目の操作を取り消します。 この操作の直後、$ A $ は $ (2,7,9,9,9,9) $ となります。 $ 13,14,15 $ 回目の操作ではこの時点での $ A\ _\ 1,A\ _\ 3,A\ _\ 4 $ の値である $ 2,9,9 $ をそれぞれ出力してください。

## 样例 #1

### 输入

```
6
2 7 1 8 2 8
15
3 1
3 3
3 4
1 1 5 4
3 1
3 3
3 4
1 3 6 9
3 1
3 3
3 4
2 4
3 1
3 3
3 4```

### 输出

```
2
1
8
4
4
8
4
9
9
2
9
9```

## 样例 #2

### 输入

```
24
721 78 541 256 970 478 370 467 344 542 43 166 619 17 592 222 983 729 338 747 62 452 815 838
35
3 10
3 8
3 8
3 13
3 9
1 1 17 251
3 3
3 19
3 13
3 22
3 1
3 15
3 18
3 10
3 15
1 16 19 883
1 8 23 212
3 5
3 13
2 6
3 15
1 5 18 914
2 17
3 20
1 23 23 56
3 13
2 25
3 13
3 13
3 10
2 16
1 17 22 308
3 19
3 17
3 7```

### 输出

```
542
467
467
619
344
541
338
619
452
721
592
729
542
592
970
619
592
747
914
914
914
914
338
983
914```

# 题解

## 作者：DengDuck (赞：9)

老外不会数据结构！老外不会数据结构！

水题。由于有删除，线段树把一个节点的所有的懒标记维护在一个可重集里面，然后删除时删掉对应的所有标记。

查询时，走到某一个节点，就取一下这里储存的标记最大值即可。

时间复杂度为 $\mathcal O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pLL pair<LL,LL>
#define fir first
#define sec second
using namespace std;
const LL N=3e5+5;
LL n,a[N],L[N],R[N],X[N];
struct node
{
	LL l,r;
	multiset<pLL>s;
}t[N*4];
void build(LL rt,LL l,LL r)
{
	t[rt].l=l,t[rt].r=r;
	t[rt].s.clear();
	if(l==r)return;
	LL mid=(l+r)/2;
	build(rt*2,l,mid),build(rt*2+1,mid+1,r);
}
void ins(LL rt,LL l,LL r,LL x,LL id)
{
	if(t[rt].r<l||r<t[rt].l)return;
	if(l<=t[rt].l&&t[rt].r<=r)
	{
	//	cout<<l<<' '<<r<<endl;
		t[rt].s.insert({x,id});
		return;
	}
	ins(rt*2,l,r,x,id),ins(rt*2+1,l,r,x,id);
}
void del(LL rt,LL l,LL r,LL x,LL id)
{
	if(t[rt].r<l||r<t[rt].l)return;
	if(l<=t[rt].l&&t[rt].r<=r)
	{
		t[rt].s.erase({x,id});
		return;
	}
	del(rt*2,l,r,x,id),del(rt*2+1,l,r,x,id);
}
LL Q(LL rt,LL x)
{
	LL mx=0;
	
	if(!t[rt].s.empty())mx=max(mx,(*t[rt].s.rbegin()).fir);
//	cout<<mx<<endl;
	if(t[rt].l==t[rt].r)return mx;
	LL mid=(t[rt].l+t[rt].r)/2;
	if(x<=mid)return max(mx,Q(rt*2,x));
	return max(mx,Q(rt*2+1,x));
}
int main()
{
	cin>>n;
	build(1,1,n);
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		ins(1,i,i,a[i],0);
	}
	LL q;
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		LL op;
		cin>>op;
		if(op==1)
		{
			LL l,r,x;
			cin>>L[i]>>R[i]>>X[i];
			l=L[i],r=R[i],x=X[i];
			ins(1,l,r,x,i);
		}
		else if(op==2)
		{
			LL x;
			cin>>x;
			del(1,L[x],R[x],X[x],x);
		}
		else
		{
			LL x;
			cin>>x;
			cout<<Q(1,x)<<endl;
		}
	}
}
```

---

## 作者：EmptyAlien (赞：5)

## 题意

- 给定一个长度为 $n$ 的序列 $a$。

- 有 $q$ 次操作。

- 1 操作：对所有 $i \in [l, r]$ 进行 $a_i = max(a_i, x)$。

- 2 操作：取消第 $i$ 次操作，保证第 $i$ 为 1 操作，即新的状态为从前往后做除了 $i$ 操作外的所有操作得到的状态。

- 3 操作：询问 $a_i$。

## 思想

如果没有 2 操作就是吉老师线段树裸题。

但是加上了 2 操作就变得十分棘手。

实际上我们并不要求复杂度一定是 $\mathcal{O}(n\log n)$，$\mathcal{O}(n\log^2n)$ 也可以。

我们仍旧使用线段树，但是每个节点维护一个 multiset。

维护当前节点取过 max 的数值和原本的值。

这样撤销只要在 multiset 里删除相应 $x$ 即可。

询问就返回 multiset 里最大的一个。

取 max 就在 multiset 里加入 $x$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 8e5 + 5;

struct SegTree {
    multiset<int, greater<>> body[MAXN];
    int ls[MAXN], rs[MAXN];

    void build(int k, int l, int r) {
        ls[k] = l;
        rs[k] = r;
        body[k].clear();
        if (l == r)
            return;
        int lc = k * 2;
        int rc = k * 2 + 1;
        int mid = l + r >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
    }

    void update(int k, int l, int r, int x) {
        if (l <= ls[k] && rs[k] <= r) {
            body[k].insert(x);
            return;
        }
        int mid = ls[k] + rs[k] >> 1;
        int lc = k * 2;
        int rc = k * 2 + 1;
        if (r <= mid)
            update(lc, l, r, x);
        else if (l > mid)
            update(rc, l, r, x);
        else {
            update(lc, l, mid, x);
            update(rc, mid + 1, r, x);
        }
    }

    void cancel(int k, int l, int r, int x) {
        if (l <= ls[k] && rs[k] <= r) {
            body[k].erase(body[k].find(x));
            return;
        }
        int mid = ls[k] + rs[k] >> 1;
        int lc = k * 2;
        int rc = k * 2 + 1;
        if (r <= mid)
            cancel(lc, l, r, x);
        else if (l > mid)
            cancel(rc, l, r, x);
        else {
            cancel(lc, l, mid, x);
            cancel(rc, mid + 1, r, x);
        }
    }

    int query(int k, int x) {
        if (ls[k] == rs[k])
            return *body[k].begin();
        int ans = 0;
        if (body[k].size())
            ans = *body[k].begin();
        int mid = ls[k] + rs[k] >> 1;
        int lc = k * 2;
        int rc = k * 2 + 1;
        if (x <= mid)
            ans = max(ans, query(lc, x));
        else
            ans = max(ans, query(rc, x));
        return ans;
    }
} segtree;

struct Query {
    int l, r, x;
} a[MAXN];

int n, q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    segtree.build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        segtree.update(1, i, i, x);
    }

    cin >> q;
    for (int i = 1; i <= q; i++) {
        int opt, x;
        cin >> opt;
        if (opt == 1) {
            cin >> a[i].l >> a[i].r >> a[i].x;
            segtree.update(1, a[i].l, a[i].r, a[i].x);
        } else if (opt == 2) {
            cin >> x;
            segtree.cancel(1, a[x].l, a[x].r, a[x].x);
        } else {
            cin >> x;
            cout << segtree.query(1, x) << endl;
        }
    }

    return 0;
}
```

---

## 作者：apiad (赞：3)

连续一个月都是线段树。。

赛后发现 G 水啊。赛时却卡着最后两分钟把 D 赶出来，是的，确实 C 题 D 题有点令人恶心。

来讲讲这次 G 为啥水。

显然，这是一个数据结构题，我们想想可以用线段树来维护。

有一个操作对区间内的每一个 $a_i$ 都变成 $\max(a_i,x)$，很容易想到，对于点 $a_i$，最后查询的时候改变它的一定是这些修改操作中最大的 $x$。因此，我们可以对线段树上每一个点里维护一个 set，用来记录的是这些 $x$。

对于撤回操作，我们也可以开一个 set 来维护，记录的是哪些数删除。到了查询的过程中，对之前的操作进行删除即可。

```cpp
//Author: gsczl71
//Copyright (c) 2024 gsczl71 All rights reserved.

#include<bits/stdc++.h>
#define ll long long
#define i128 __int128
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<long long, long long>
#define fs first
#define sc second
#define endl '\n'
#define debug puts("AK IOI")
#define re register
#define pb push_back
#define mem(a,x) memset((a),(x),sizeof(a))
#define vi vector<int>
using namespace std;
// #define int long long
const int mod = 1e9+7;
//const int mod = 998244353;
const int inf = 0x3f3f3f3f,N = 2e5+5,M = 2e5+5;
const ll linf = 0x3f3f3f3f3f3f3f3f;
int n,a[N];set<int> dlt;
struct SegTree{
	int l,r;set<pii> st; // val id
}t[N<<2];
void build(int p,int l,int r){
	t[p]={l,r};if(l==r)return ;
	int mid = (l+r)>>1;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
}void modify(int p,int l,int r,int x,int id){
	if(l<=t[p].l&&r>=t[p].r){t[p].st.insert({-x,id});return ;}
	int mid = (t[p].l+t[p].r)>>1;
	if(mid >= l)modify(p<<1,l,r,x,id);
	if(mid < r)modify(p<<1|1,l,r,x,id);
}int query(int p,int x,int val){
	while(dlt.count((*t[p].st.begin()).sc)) t[p].st.erase(t[p].st.begin());
	val=max(val,-(*t[p].st.begin()).fs);
	if(t[p].l==t[p].r) return max(val,a[x]);
	int mid=(t[p].l+t[p].r)>>1;
	if(x <= mid) return query(p<<1,x,val);
	else return query(p<<1|1,x,val);
}void solve(){
	cin>>n;for(int i=1;i<=n;i++)cin>>a[i];build(1,1,n);
	int q;cin >> q;for(int i =1;i <= q;i++){
		int op;cin >> op;
		if(op==1){int l,r,x;cin >> l>>r>>x;modify(1,l,r,x,i);}
		else if(op==2){int x;cin >> x;dlt.insert(x);}
		else{int x;cin >>x;cout<<query(1,x,0)<<endl;}
	}
}signed main(){
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T=1;
//	cin >> T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：lzyqwq (赞：2)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/p/18031708)**

**[题目传送门](https://atcoder.jp/contests/abc342/tasks/abc342_g)**

> - 给出长度为 $n$ 的数组 $a_1\sim a_n$。有 $q$ 次操作，$3$ 种类型：
>
>    - $1\space l\space r\space x$，对于 $i\in[l,r]$，执行 $a_i\leftarrow \max(a_i,x)$。
>
>     - $2\space x$，取消第 $x$ 次操作，保证这是操作 $1$。即在 $a$ 数组初始状态上按顺序执行从初始时刻到当前时刻除 $x$ 以外的所有 $1$ 操作后得到新的数组 $b$，然后令 $a\leftarrow b$。
>
>     - $3\space x$，查询 $a_x$。

考虑建立线段树，每个节点维护一个集合 $S_i$。记 $a$ 数组的初始状态为 $A$ 数组。对于一个对应下标为 $p$ 的叶子节点 $u$，记它根链路径上的点构成的集合为 $P$，我们在线段树上实时维护 $p=\max\{A_p,\max\limits_{i\in P}\max\limits_{j\in S_i}j\}$。

对于 $1$ 操作，在线段树上找到覆盖这个区间的节点，则这些子树内部的所有叶子都仍要对 $x$ 取 $\max$，因此在这些节点的 $S$ 上插入 $x$。

$2$ 操作类似，在线段树上找到覆盖这个区间的节点，则这些子树内部的所有叶子原本要对 $x$ 取 $\max$，这个操作取消后就不需要对它取 $\max$ 了，因此在这些 $S$ 中删除 $x$。

$3$ 操作，直接单点查询然后对根链上的 $S$ 取 $\max$ 即可。

用 `multiset` 维护 $S$，时间复杂度为 $\mathcal{O}(n+q\log^2 n)$，空间复杂度为 $\mathcal{O}(q+n\log n)$。

**[AC Code](https://atcoder.jp/contests/abc342/submissions/50593142)**

---

## 作者：ran_qwq (赞：1)

这里提供两种做法。

## 1. 线段树维护 STL

赛时做法。

操作之后还会取消，所以不能像普通线段树一样下传标记。

考虑**标记永久化**，在每个节点上用 STL 维护要加的操作。删除时就把操作删掉，询问就取所有操作的最大值即可。

我们需要一个快速插入，快速删除，快速查询的数据结构，用 set、multiset、map、multimap 都可以。

时间复杂度 $O(n\log^2n)$。

[code，这里使用的是 multiset。](https://atcoder.jp/contests/abc342/submissions/50599298)

## 2. 线段树分治

容易发现，一个操作其实可以写成 $(l,r,s,t,x)$ 的形式，表示位置范围为序列区间 $[l,r]$，时间范围为时间区间 $[s,t]$，取 max 的数是 $x$。

把操作离线下来，用[线段树分治](https://www.luogu.com.cn/blog/743048/cyz-love-zwx)消掉时间维，写一个支持撤销的线段树维护即可。

时间复杂度 $O(n\log^2n)$。

---

## 作者：yizcdl2357 (赞：1)

以此题解纪念我的第一场 ABC。

# 题意

维护一个长为 $n$ 的序列 $a$，要求支持以下 $q$ 次操作：

1. 区间 $[l,r]$ 对 $x$ 取 $\max$。
2. 撤销某个 1 操作。
3. 单点查询 $a_x$。

$n,q\le 2\times10^5$。

# 解法

如果没有 2 操作？显然是我们熟悉的线段树。

由于是单点查询，我们可以使用**标记永久化**技巧，只维护 $mx_i$ 作为节点 $i$ 的永久化标记，修改时对所有叶子节点进行 $mx_i\leftarrow \max(mx_i,x)$，查询时将一路上经过的所有节点的 $mx_i$ 取最大值。

当然懒标记线段树也是可以的，~~但是代码复杂度显著增加，ABC 可不敢这么玩~~。

考虑 2 操作。看到“撤销”我们自然想到了**线段树分治**，即用 $O(\log n)$ 的复杂度将删除操作转化为加入操作的技巧。

即维护每个 1 操作的“生存时间”（即从操作命令发出到被撤销的时间区间），然后对时间轴开一颗线段树，将每个 1 操作视为时间轴线段树上的区间操作，查询时对时间轴线段树进行遍历，走进一个节点时将这个节点上的所有操作在区间 $\max$ 线段树上进行，接着递归遍历其子节点，最后走出这个节点时将将这个节点上的所有操作撤销即可。

将区间 $\max$ 线段树可撤销化也很简单：开一个栈，每对 $mx$ 数组进行一次操作就往栈里存储该元素修改前的值，撤销时复原栈顶元素即可。

时间复杂度 $O(n\log ^2 n)$。

# 代码
```cpp
#include<bits/stdc++.h>
#define N 200000
#define L 40
#define ls id<<1,l,(l+r)>>1
#define rs id<<1|1,((l+r)>>1)+1,r
using namespace std;
struct que{
	int t1,t2,l,r,x;
};
struct xds{
	int mx[4*N+5],stk[L*N+5][2],tp;
	inline void build(int id,int l,int r)
	{
		if(l==r)
		{
			cin>>mx[id];
			return;
		}
		build(ls),build(rs);
	}
	inline void upd(int id,int l,int r,int x,int y,int z)
	{
		if(r<x||l>y) return;
		if(x<=l&&r<=y)
		{
			stk[++tp][0]=id,
			stk[tp][1]=mx[id],
			mx[id]=max(mx[id],z);
			return;
		}
		upd(ls,x,y,z),upd(rs,x,y,z);
	}
	inline int query(int id,int l,int r,int x)
	{
		if(r<x||l>x) return -1;
		if(l==r) return mx[id];
		return max(max(query(ls,x),query(rs,x)),mx[id]);
	}
	inline void wd()
	{
		mx[stk[tp][0]]=stk[tp][1];
		tp--;
	}
};
xds t;
int n,q,ask[N+5],ans[N+5];
que qu[N+5];
vector<que> v[4*N+5];
inline void add(int id,int l,int r,que x)
{
	if(r<x.t1||l>x.t2) return;
	if(x.t1<=l&&r<=x.t2){v[id].push_back(x);return;}
	add(ls,x),add(rs,x);
}
inline void solve(int id,int l,int r)
{
//	cout<<id<<' '<<l<<' '<<r<<endl;
	int tp=t.tp;
	for(que i:v[id])
		t.upd(1,1,n,i.l,i.r,i.x);
	if(l==r)
	{
		if(ask[l])
			ans[l]=t.query(1,1,n,ask[l]);
	}
	else solve(ls),solve(rs);
	while(t.tp>tp) t.wd();
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	t.build(1,1,n);
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		int tp,x,y,z;
		cin>>tp>>x;
		if(tp==1)
		{
			cin>>y>>z;
			qu[i]=(que){i,0,x,y,z};
		}
		if(tp==2)
			qu[x].t2=i-1;
		if(tp==3)
			ask[i]=x;
	}
	for(int i=1;i<=q;i++)
		if(qu[i].t1&&!qu[i].t2) qu[i].t2=q;
	for(int i=1;i<=q;i++)
		if(qu[i].t1) add(1,1,q,qu[i]);
	solve(1,1,q);
	for(int i=1;i<=q;i++)
		if(ans[i])
			cout<<ans[i]<<'\n';
	return 0;
}
```

~~好像只有我写了这么复杂的解法，还调了 40min。~~

~~我一开始脑抽甚至写了吉司机线段树。~~

---

## 作者：rainygame (赞：1)

> 评价：G < E < F。

考虑线段树维护。对每个线段树结点，维护一个 `multiset` 这个结点取过 $\max$ 的数。这个“懒标记”不需要下传。

对于撤销操作，直接从 `multiset` 里面删即可。

查询就查从对应叶子结点到根的所有结点的 `multiset` 最大值即可。

时间复杂度 $O(n \log^2 n)$，空间复杂度 $O(n \log n)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200001

int n, q;
int a[MAXN];

struct Que{int l, r, x;}que[MAXN];
struct Node{
    int l, r;
    multiset<int, greater<int>> mst;
}tree[MAXN<<2];

void build(int p, int l, int r){
    tree[p].l = l;
    tree[p].r = r;
    if (l == r) return;
    int mid((l+r)>>1);
    build(p<<1, l, mid);
    build(p<<1|1, mid+1, r);
}

void add(int p, int L, int R, int k){
    if (tree[p].l >= L && tree[p].r <= R){
        tree[p].mst.insert(k);
        return;
    }

    int mid((tree[p].l+tree[p].r)>>1);
    if (L <= mid) add(p<<1, L, R, k);
    if (R > mid) add(p<<1|1, L, R, k);
}

void remove(int p, int L, int R, int k){
    if (tree[p].l >= L && tree[p].r <= R){
        tree[p].mst.erase(tree[p].mst.find(k));
        return;
    }

    int mid((tree[p].l+tree[p].r)>>1);
    if (L <= mid) remove(p<<1, L, R, k);
    if (R > mid) remove(p<<1|1, L, R, k);
}

int query(int p, int k){
    int maxn(tree[p].mst.size() ? *tree[p].mst.begin() : 0);
    if (tree[p].l == tree[p].r) return maxn;
    int mid((tree[p].l+tree[p].r)>>1);
    if (k <= mid) return max(maxn, query(p<<1, k));
    return max(maxn, query(p<<1|1, k));
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i(1); i<=n; ++i) cin >> a[i];
    build(1, 1, n);

    cin >> q;
    for (int i(1), opt, x; i<=q; ++i){
        cin >> opt;
        if (opt == 1){
            cin >> que[i].l >> que[i].r >> que[i].x;
            add(1, que[i].l, que[i].r, que[i].x);
        }else if (opt == 2){
            cin >> x;
            remove(1, que[x].l, que[x].r, que[x].x);
        }else{
            cin >> x;
            cout << max(a[x], query(1, x)) << '\n';
        }
    }

    return 0;
}

```


---

## 作者：FReQuenter (赞：0)

区间修改，单点查询，我们考虑标记永久化。

但是中间有个撤销的问题。所以考虑把标记单独记录下来，不要计算。撤销就直接撤销对应的标记，查询的时候按照正常的标记永久化取所有标记的最大值。

所以需要一个快速插入、删除、取最大值的东西来维护标记。set，map，priority_queue 等都行。时间复杂度 $O(n\log^2n)$。

再给出另一个做法。考虑一次修改，相当于在当前时刻一直到被删除前生效，没有撤销。那么使用线段树分治就可以解决这个问题。内部可以使用标记永久化的线段树维护标记。同样是 $O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>
#define MAXN 200005
using namespace std;
multiset<int> tag[MAXN<<2];
int n,q,a[MAXN],L[MAXN],R[MAXN],X[MAXN];
void add(int root,int l,int r,int ql,int qr,int v,int op){
	if(ql<=l&&qr>=r){
		if(op) tag[root].insert(v);
		else tag[root].erase(tag[root].lower_bound(v));
		return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid) add(root<<1,l,mid,ql,qr,v,op);
	if(qr>mid) add(root<<1|1,mid+1,r,ql,qr,v,op);
} 
int qry(int root,int l,int r,int x,int v){
	if(tag[root].size()) v=max(v,*tag[root].rbegin());
	if(l==r) return max(a[l],v);
	int mid=(l+r)>>1;
	if(x<=mid) return qry(root<<1,l,mid,x,v);
	return qry(root<<1|1,mid+1,r,x,v);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>q;
	for(int i=1;i<=q;i++){
		int op,l,r,x;
		cin>>op;
		if(op==1){
			cin>>l>>r>>x;
			add(1,1,n,l,r,x,1);
			L[i]=l,R[i]=r,X[i]=x;
		}
		else if(op==2){
			cin>>x;
			add(1,1,n,L[x],R[x],X[x],0);
		}
		else{
			cin>>x;
			cout<<qry(1,1,n,x,-1)<<'\n';
		}
	}
}
```

---

## 作者：Unnamed114514 (赞：0)

容易想到线段树。

使用标记永久化，每个节点需要维护的是取 `max` 的值。

显然只有当前的最大值有用，又因为 $2$ 操作要删除，所以说线段树上每个点开个 `multiset` 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define inf 0x3f3f3f3f3f3f3f3fll
#define eps 1e-10
#define endl '\n'
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int N=2e5+5;
int n,q,l[N],r[N],x[N],a[N];
multiset<int> s[N<<2];
inline void Insert(int p,int l,int r,int ql,int qr,int x){
	if(ql<=l&&r<=qr){
		s[p].insert(x);
		return;
	}
	int mid=l+r>>1;
	if(ql<=mid) Insert(ls,l,mid,ql,qr,x);
	if(mid<qr) Insert(rs,mid+1,r,ql,qr,x);
}
inline void Delete(int p,int l,int r,int ql,int qr,int x){
	if(ql<=l&&r<=qr){
		s[p].erase(s[p].lower_bound(x));
		return;
	}
	int mid=l+r>>1;
	if(ql<=mid) Delete(ls,l,mid,ql,qr,x);
	if(mid<qr) Delete(rs,mid+1,r,ql,qr,x);
}
inline int query(int p,int l,int r,int pos){
	if(l==r) return *s[p].rbegin();
	int mid=l+r>>1;
	if(pos<=mid) return max(*s[p].rbegin(),query(ls,l,mid,pos));
	return max(*s[p].rbegin(),query(rs,mid+1,r,pos));
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=(n<<2);++i) s[i].insert(-inf);
	cin>>q;
	for(int i=1,op;i<=q;++i){
		cin>>op;
		if(op==1){
			cin>>l[i]>>r[i]>>x[i];
			Insert(1,1,n,l[i],r[i],x[i]);
		} else if(op==2){
			int pos;
			cin>>pos;
			Delete(1,1,n,l[pos],r[pos],x[pos]);
		} else{
			int pos;
			cin>>pos;
			cout<<max(a[pos],query(1,1,n,pos))<<endl;
		}
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

我会无脑做法，哈哈！

考虑没有删除操作怎么做？直接每个点维护一个标记，下传直接取 $\max$ 就好。

要删除，直接考虑线段树分治，删除变撤销。然而取 $\max$ 貌似不好直接撤销。考虑标记永久化，这样就不需要下传。单次区间修改影响 $O(\log n)$ 个节点，直接记录下来撤销即可。复杂度应该是 $O(n \log^2 n)$ 的，然而我赛时实现套了个 `map` 变成了 $O(n \log^3 n)$，仍然过了。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long

const int N = 2e5 + 5, MOD = 1e9 + 7, HSMOD = 1610612741, HSMOD2 = 998244353; // Remember to change

int n, m, q, t, a[N];
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

long long qpow(long long a, long long b)
{
	long long res = 1ll, base = a;
	while (b)
	{
		if (b & 1ll) res = res * base % MOD;
		base = base * base % MOD;
		b >>= 1ll;
	}
	return res;
}

bool isprime(int x)
{
	if (x == 1) return 0;
	for (int i = 2; 1ll * i * i <= x; i++) if (x % i == 0) return 0;
	return 1;
}

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

template<typename T>
class Bit
{
public:
	T lowbit(T x)
	{
		return x & -x;
	}
	T tr[N];
	void add(T x, T y)
	{
		while (x < N)
		{
			tr[x] += y;
			x += lowbit(x);
		}
	}
	T query(T x)
	{
		T sum = 0;
		while (x)
		{
			sum += tr[x];
			x -= lowbit(x);
		}
		return sum;
	}
};

map<int, int> vv;

class SegmentTree
{
public:
	struct Node
	{
		int l,r,tag;
	}tr[N<<2];
	void ptag(int u,int v)
	{
		if(!vv.count(u))vv[u]=tr[u].tag;
		tr[u].tag=max(tr[u].tag,v);
	}
	void build(int u,int l,int r)
	{
		tr[u]={l,r,0};
		if(l==r) return;
		int mid=l+r>>1;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
	}
	void update(int u,int l,int r,int v)
	{
		if(tr[u].l>=l and tr[u].r<=r)
		{
			ptag(u,v);
			return;
		}
		int mid=tr[u].l+tr[u].r>>1;
		if(l<=mid) update(u<<1,l,r,v);
		if(r>mid) update(u<<1|1,l,r,v);
	}
	int query(int u,int x)
	{
		if(tr[u].l==tr[u].r) 
		{
			return max(a[tr[u].r],tr[u].tag);
		}
		int res=tr[u].tag;
		int mid=tr[u].l+tr[u].r>>1;
		if(x<=mid) res=max(res,query(u<<1,x));
		else res=max(res, query(u<<1|1,x));
		return res;
	}
}sgt;

struct Ope
{
	int l,r,v;
	Ope()=default;
	Ope(int l,int r,int v):l(l),r(r),v(v){}
};

Ope od[N];
int qr[N];

class Timesgt
{
public:
	struct Node
	{
		int l,r;
		vector<Ope> vec;
	}tr[N<<2];
	void build(int u,int l,int r)
	{
		tr[u]={l,r};
		tr[u].vec.clear();
		if(l==r) return;
		int mid=l+r>>1;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
	}
	void update(int u,int l,int r,Ope& op)
	{
		if(tr[u].l>=l and tr[u].r<=r)
		{
			tr[u].vec.emplace_back(op);
			return;
		}
		int mid=tr[u].l+tr[u].r>>1;
		if(l<=mid) update(u<<1,l,r,op);
		if(r>mid) update(u<<1|1,l,r,op);
	}
	void solve(int u)
	{
		vv.clear();
		for(auto&[l,r,v]:tr[u].vec)
		{
			sgt.update(1,l,r,v);
		}
		if(tr[u].l==tr[u].r)
		{
			if(qr[tr[u].l])
			{
				cout<<sgt.query(1,qr[tr[u].l])<<"\n";
			}
			for(auto&[u,v]:vv) sgt.tr[u].tag=v;
			vv.clear();
			return;
		}
		vector<pair<int, int>> gg;
		for(auto&[uu,vg]:vv) gg.emplace_back(make_pair(uu,vg));
		vv.clear();
		solve(u<<1);
		solve(u<<1|1);
		for(auto&[uu,vg]:gg) 
		{
			sgt.tr[uu].tag=vg;
		}
	}
}s;

int ed[N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin>>n;
	sgt.build(1,1,n);
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>m;
	s.build(1,1,m);
	for(int i=1;i<=m;i++)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			cin>>od[i].l>>od[i].r>>od[i].v;
		}
		else if(op==2)
		{
			int x;
			cin>>x;
			//cout<<"!!!: " << x<<" "<<i-1<<"\n";
			s.update(1,x,i-1,od[x]);
			ed[x]=i;
		}
		else
		{
			int g;
			cin>>g;
			qr[i]=g;
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(od[i].l&&!ed[i]) 
		{
			s.update(1,i,m,od[i]);
		}
	}
	s.solve(1);
	return 0;
}


```


---

## 作者：cancan123456 (赞：0)

一句话题解：线段树套 `multiset`。

详细题解：看到区间操作我们考虑线段树，由于只有单点查询考虑标记永久化，就是线段树每个节点开一个 `multiset`，记录完全包含此节点的操作中的所有 $x$。

插入操作找到线段树上的 $O(\log n)$ 个区间全部插入 $x$ 即可，删除操作类似，注意只删除一个，应当使用这种方式：

```cpp
s.erase(s.find(x));
```

查询操作将对应的叶子节点到根所有节点的 `multiset` 最大值取出并全部取最大值即可。

时间复杂度为 $O(n\log n+q\log^2n)$，可以通过此题。

```cpp
#include <cstdio>
#include <set>
using namespace std;
const int N = 200005;
int a[N];
struct Node {
	int l, r;
	multiset < int > s;
} node[4 * N];
void build(int p, int l, int r) {
	node[p].l = l;
	node[p].r = r;
	if (l == r) {
		node[p].s.insert(a[l]);
	} else {
		int mid = (l + r) / 2;
		build(2 * p, l, mid);
		build(2 * p + 1, mid + 1, r);
	}
}
void add(int p, int l, int r, int x) {
	if (l <= node[p].l && node[p].r <= r) {
		node[p].s.insert(x);
	} else {
		int mid = (node[p].l + node[p].r) / 2;
		if (l <= mid) {
			add(2 * p, l, r, x);
		}
		if (mid + 1 <= r) {
			add(2 * p + 1, l, r, x);
		}
	}
}
void del(int p, int l, int r, int x) {
	if (l <= node[p].l && node[p].r <= r) {
		multiset < int > & s = node[p].s;
		s.erase(s.find(x));
	} else {
		int mid = (node[p].l + node[p].r) / 2;
		if (l <= mid) {
			del(2 * p, l, r, x);
		}
		if (mid + 1 <= r) {
			del(2 * p + 1, l, r, x);
		}
	}
}
int max(const multiset < int > & s) {
	if (s.empty()) {
		return 0;
	} else {
		multiset < int > :: iterator it = s.end();
		it--;
		return *it;
	}
}
int query(int p, int pos) {
	if (node[p].l == node[p].r) {
		return max(node[p].s);
	} else {
		int mid = (node[p].l + node[p].r) / 2;
		if (pos <= mid) {
			return max(query(2 * p, pos), max(node[p].s));
		} else {
			return max(query(2 * p + 1, pos), max(node[p].s));
		}
	}
}
int lll[N], rrr[N], xxx[N];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	build(1, 1, n);
	int q;
	scanf("%d", &q);
	for (int op, l, r, x, p, i = 1; i <= q; i++) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d %d %d", &l, &r, &x);
			add(1, l, r, x);
			lll[i] = l;
			rrr[i] = r;
			xxx[i] = x;
		} else if (op == 2) {
			scanf("%d", &p);
			del(1, lll[p], rrr[p], xxx[p]);
		} else {
			scanf("%d", &p);
			printf("%d\n", query(1, p));
		}
	}
	return 0;
}
```

---

