# Incessant Rain

## 题目描述

**注意本题的内存限制与通常不同。**

银狼给了你一个长度为 $n$ 的数组 $a$ 和 $q$ 个查询。在每个查询中，她替换数组中的一个元素。在每个查询后，她将询问你 $k$ 的最大值，使得存在一个整数 $x$ 和 $a$ 的一个子数组 $^*$，其中 $x$ 是该子数组的 $k$-多数。

若 $y$ 在数组 $b$ 中出现了至少 $\left\lfloor\frac{|b|+1}{2}\right\rfloor+k$ 次（其中 $|b|$ 表示 $b$ 的长度），则称 $y$ 是数组 $b$ 的 $k$-多数。注意 $b$ 可能不存在一个 $k$-多数。

$^*$ 若数组 $a$ 在删除开头和结尾的若干（可能为零或者全部）元素后可以得到数组 $b$，则称 $b$ 是 $a$ 的一个子数组。

## 样例 #1

### 输入

```
2
5 5
1 2 3 4 5
3 4
1 4
2 4
4 3
2 3
7 8
3 2 3 3 2 2 3
2 3
5 3
6 3
3 4
4 4
7 4
6 4
2 4```

### 输出

```
1 1 2 1 0 
2 2 3 2 1 1 1 2```

# 题解

## 作者：ddxrS_loves_zxr (赞：5)

### 题目大意

如果整数 $y$ 是数组 $b$ 的 $k$-多数，要满足 $y$ 至少在 $b$ 中出现 $\lceil\frac{|b|}{2}\rceil+k$ 次。

给定一个数组 $a$ 然后有 $q$ 次单点赋值，在每次操作后求出一个最大的 $k$ 使得存在一个数 $x$ 是 $a$ 的某个子数组的 $k$-多数。

### 思路

假设我们已经确定了 $k$-多数是 $x$，考虑求最大的 $k$。

将原数组的每一个位置重新赋值：将等于 $x$ 的位置赋成 $1$，其他位置赋成 $-1$。求出最大子段和 $s$，那么 $k$ 最大为 $\lfloor\frac{s}{2}\rfloor$。

每次单点修改只需要改变正负号。以上过程可以使用线段树维护。

现在考虑枚举 $x$，但每次都全部跑一边肯定会超时。可以发现，对于当前的 $x$，有一些操作是无用的。准确来说，会改变当前数组取值的操作，假设是将 $a_i$ 修改为 $y$，要么满足 $a_i=x$ 要么满足 $y=x$。因此我们只需要将这些操作记录下了，然后只跑这些操作，复杂度就对了。

以及，为什么限定池不能歪银狼？

```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define fi first 
#define se second
#define lc p << 1
#define rc p << 1 | 1 
typedef long long ll;
using namespace std;
const int N = 3e5 + 5, inf = 0x3f3f3f3f;
int n, q, a[N];
int tr[N << 2], mxl[N << 2], mxr[N << 2], sm[N << 2];
vector<pii> vec[N];
void pushup(int p) {
	sm[p] = sm[lc] + sm[rc];
	mxl[p] = max(mxl[lc], sm[lc] + mxl[rc]);
	mxr[p] = max(mxr[lc] + sm[rc], mxr[rc]);
	tr[p] = max({tr[lc], tr[rc], mxr[lc] + mxl[rc]});
}
void clear(int p, int l, int r, int op) {
	int mid = l + r >> 1;
	if(l == r) return tr[p] = mxl[p] = mxr[p] = sm[p] = -1, void();
	if(tr[lc] >= 0 || op) clear(lc, l, mid, op);
	if(tr[rc] >= 0 || op) clear(rc, mid + 1, r, op);
	pushup(p);
}
void change(int p, int l, int r, int x) {
	int mid = l + r >> 1;
	if(l == r) return tr[p] *= -1, mxl[p] *= -1, mxr[p] *= -1, sm[p] *= -1, void();
	(x <= mid ? change(lc, l, mid, x) : change(rc, mid + 1, r, x));
	pushup(p);
}
int ans[N << 2];
void update(int p, int l, int r, int ql, int qr, int x) {
	if(ql > qr) return;
	int mid = l + r >> 1;
	if(ql <= l && r <= qr) return ans[p] = max(ans[p], x), void();
	if(ql <= mid) update(lc, l, mid, ql, qr, x);
	if(mid < qr) update(rc, mid + 1, r, ql, qr, x);
}
void print(int p, int l, int r, int mx) {
	int mid = l + r >> 1;
	if(l == r) return cout<<max(mx, ans[p]) / 2<<' ', ans[p] = 0, void();
	print(lc, l, mid, max(mx, ans[p])), print(rc, mid + 1, r, max(mx, ans[p]));
	ans[p] = 0;
}
void solve() {
	cin>>n>>q;
	for(int i = 1; i <= n; i++) cin>>a[i], vec[a[i]].push_back({0, i});
	for(int i = 1, x, y; i <= q; i++) {
		cin>>x>>y;
		if(a[x] != y) vec[a[x]].push_back({i, x}), vec[a[x] = y].push_back({i, x});
	} 
	for(int i = 1; i <= n; i++) {
		clear(1, 1, n, i == 1);
		for(int j = 0; j < vec[i].size();) {
			int k = j;
			while(k < vec[i].size() && vec[i][j].fi == vec[i][k].fi) change(1, 1, n, vec[i][k].second), k++;
			update(1, 1, q, max(1, vec[i][j].fi), (k < vec[i].size() ? vec[i][k].fi - 1 : q), tr[1]);
			j = k;
		}
		vec[i].clear();
	}
	print(1, 1, q, 0), cout<<'\n';
}
signed main() {
#ifdef ddxrS  
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
#endif 
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t; cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：xyvsvg (赞：2)

注意到同时处理多个值比较困难（可能需要动态开点之类的），于是考虑枚举 $x$，并一次回答多个询问。

我们对于 $x\in[1,n]$，将有关 $x$ 的查询都记录下来，然后枚举每个 $x$，使用线段树维护即可。具体的，我们拆式子不难发现：如果 $a_i=x$，令 $b_i=1$，否则令 $b_i=-1$，则数组 $b$ 的最大子段和除以二再向下取整即为答案，套板子即可。

为了使复杂度正确，我们不能每次都单开一个线段树，而是要把当前 $x$ 影响的数都还原（类似 cdq 分治时的还原树状数组），这样可以时复杂度为 $O(q\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int inf=0x3f3f3f3f;
struct Info
{
    int sum=0,pref=-inf,suff=-inf,res=-inf;
    Info operator+(const Info&o)const
    {
        return {sum+o.sum,max(pref,sum+o.pref),max(o.suff,suff+o.sum),max({res,o.res,suff+o.pref})};
    }
};
struct SegmentTree
{
    int n;
    vector<Info>sgt;
    constexpr int ls(int p)
    {
        return p<<1;
    }
    constexpr int rs(int p)
    {
        return p<<1|1;
    }
    void build(int p,int l,int r)
    {
        if(l+1==r)
            sgt[p]={-1,-1,-1,-1};
        else
        {
            int mid=l+r>>1;
            build(ls(p),l,mid);
            build(rs(p),mid,r);
            sgt[p]=sgt[ls(p)]+sgt[rs(p)];
        }
    }
    SegmentTree(int n_)
    {
        n=n_;
        sgt.resize(n<<2|3);
        build(1,1,n+1);
    }
    void modify(int p,int l,int r,int k,int x)
    {
        if(l+1==r)
            sgt[p].sum+=x,sgt[p].pref+=x,sgt[p].suff+=x,sgt[p].res+=x;
        else
        {
            int mid=l+r>>1;
            if(k<mid)
                modify(ls(p),l,mid,k,x);
            else
                modify(rs(p),mid,r,k,x);
            sgt[p]=sgt[ls(p)]+sgt[rs(p)];
        }
    }
    int query()
    {
        return sgt[1].res;
    }
};
typedef array<int,3> A;
void solve()
{
    int n,m;
    cin>>n>>m;
    SegmentTree sgt(n);
    vector<int>a(n+10);
    vector<vector<A> >qs(n+10);
    multiset<int>bst;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        qs[a[i]].push_back({0,i,2});
        bst.insert(-1);
    }
    for(int d=0;d<m;++d)
    {
        int i,x;
        cin>>i>>x;
        qs[a[i]].push_back({d,i,-2});
        qs[a[i]=x].push_back({d,i,2});
    }
    vector<vector<int> >add(m),del(m);
    vector<int>mk(n+10);
    for(int x=1;x<=n;++x)
    {
        for(auto[d,i,k]:qs[x])
        {
            del[d].push_back(sgt.query());
            sgt.modify(1,1,n+1,i,k);
            add[d].push_back(sgt.query());
        }
        for(auto[d,i,k]:qs[x])
            sgt.modify(1,1,n+1,i,-k);
    }
    for(int i=0;i<m;++i)
    {
        for(int x:add[i])
            bst.insert(x);
        for(int x:del[i])
            assert(bst.count(x)),
                bst.erase(bst.lower_bound(x));
        cout<<(*bst.rbegin()>>1)<<" \n"[i==m-1];
    }
}
int main()
{
    int t;
    cin>>t;
    while(t--)
        solve();
    return 0;
}
```

---

## 作者：lao_wang (赞：0)

## 正文

读题可知，在一个子序列中是 $K$ 多数的数（$k>0$） ，他一定是该序列的绝对众数。

题目就变成了找一个子序列使得其绝对众数数字数量减去其他数字数量的差最大。

尝试枚举绝对众数 $x$。

将所有除 $x$ 的值设为 $-1$，将所有 $x$ 的值设为 $1$。

可以发现，若 $x$ 有解则该序列的最大子段和就是当绝对众数为 $x$ 时差的最大值；若无解就不管他。

先考虑怎么样将该值转化为原题目的答案。

若 $n$ 为奇数，令绝对众数有 $x$ 个，其他值有 $y$ 个。

则有：

$$n=\lfloor \dfrac{x+y}{2} \rfloor +1+k+y$$

$$k=2\times\lfloor \dfrac{x+y}{2} \rfloor+1-\lfloor \dfrac{x+y}{2} \rfloor-1-y$$

$$k=\lfloor \dfrac{x-y}{2} \rfloor$$

若 $n$ 为偶数，令绝对众数有 $x$ 个，其他值有 $y$ 个。

则有：

$$n=\lfloor \dfrac{x+y}{2} \rfloor +1+k+y$$

$$k=2\times\lfloor \dfrac{x+y}{2} \rfloor-\lfloor \dfrac{x+y}{2} \rfloor-y$$

$$k=\lfloor \dfrac{x-y}{2} \rfloor$$

所以对于每个 $x$，都有 $k=\lfloor \dfrac{x-y}{2} \rfloor$。

这样的复杂度是 $O(nq\log n)$ 的。

发现每次询问的修改只会影响 2 颗线段树一个叶子的值，所以将他离线后在枚举答案的过程中按时间序更改当前线段树的值并记录答案。

复杂度 $O((n+q)\log n)$

## 代码

```cpp
#include<bits/stdc++.h>
#define N 612345
using namespace std ;
int T , n , q , a[N] ;
struct node {
	int ls , rs , sum , dp , l , r , ans , lazy ;
} tr[N<<2];
struct questions{
	int x , i , k ;
};
vector<int> wh[N] ;
vector<questions> opt[N] ;
void push_up(int num) {
	tr[num].ls = max(tr[num<<1].ls,tr[num<<1].sum+tr[num<<1|1].ls) ;
	tr[num].rs = max(tr[num<<1|1].rs,tr[num<<1|1].sum+tr[num<<1].rs) ;
	tr[num].sum = tr[num<<1|1].sum+tr[num<<1].sum ;
	tr[num].dp = max(tr[num<<1].dp,max(tr[num<<1|1].dp,tr[num<<1].rs+tr[num<<1|1].ls)) ;
}
void push_down(int num){
	if(!tr[num].lazy) return ;
	int x=tr[num].lazy ;
	tr[num].lazy = 0 ;
	tr[num<<1].lazy = max(tr[num<<1].lazy,x) , tr[num<<1].ans = max(tr[num<<1].ans,x) , tr[num<<1|1].lazy = max(tr[num<<1|1].lazy,x) , tr[num<<1|1].ans =  max(tr[num<<1|1].ans,x) ;
}
void made(int num,int l,int r) {
	tr[num].l = l , tr[num].r = r ;
	tr[num].ans = tr[num].lazy = 0 ;
	if(l==r){
		tr[num].sum = tr[num].ls = tr[num].rs = tr[num].dp = -1 ;
		return ;
	}
	int mid=(l+r)>>1 ;
	made(num<<1,l,mid) ;
	made(num<<1|1,mid+1,r) ;
	push_up(num) ;
}
void change(int num,int x,int k){
	if(tr[num].l==tr[num].r){
		tr[num].sum = tr[num].dp = tr[num].ls = tr[num].rs = k ;
		return ;
	}
	int mid=(tr[num].l+tr[num].r)>>1 ;
	if(mid>=x) change(num<<1,x,k) ;
	else change(num<<1|1,x,k) ;
	push_up(num) ;
}
void change(int num,int l,int r,int k){
	if(tr[num].l>=l&&tr[num].r<=r){
		tr[num].ans = max(tr[num].ans,k) ;
		tr[num].lazy = tr[num].ans ;
		return ;
	}
	int mid=(tr[num].l+tr[num].r)>>1 ;
	if(mid>=l) change(num<<1,l,r,k) ;
	if(mid<r) change(num<<1|1,l,r,k) ;
}
int ask(int num,int x){
	if(tr[num].l==tr[num].r) return tr[num].ans ;
	push_down(num) ;
	int mid=(tr[num].l+tr[num].r)>>1 ;
	if(mid>=x) return ask(num<<1,x) ;
	else return ask(num<<1|1,x) ;
}
signed main() {
	cin >> T ;
	while(T--){
		scanf("%d%d",&n,&q) ;
		for(int i=1;i<=n;i++) wh[i].clear() , opt[i].clear() ;
		for(int i=1;i<=n;i++) scanf("%d",a+i) , wh[a[i]].push_back(i) ;
		made(1,1,max(n,q)) ;
		for(int i=1;i<=q;i++){
			int x , y ;
			scanf("%d%d",&x,&y) ;
			opt[a[x]].push_back(questions{x,i,-1}) ;
			opt[y].push_back(questions{x,i,1}) ;
			a[x] = y ;
		}
		for(int i=1;i<=n;i++){
			int last1=1 , last2=0 ;
			for(auto x:opt[i-1]) change(1,x.x,-1) ;
			for(auto x:wh[i-1]) change(1,x,-1) ;
			for(auto x:wh[i]) change(1,x,1) ;
			last2 = tr[1].dp/2 ;
			for(auto x:opt[i]){
				if(last1) change(1,last1,x.i-1,last2) ;
				change(1,x.x,x.k) ;
				last1 = x.i , last2 = tr[1].dp/2 ;
			}
			change(1,last1,q,last2) ;
		}
		for(int i=1;i<=q;i++) printf("%d ",ask(1,i)) ;
		puts("") ;
	}
	return 0 ;
}

```

---

## 作者：Imerance1018 (赞：0)

转化很妙的题，转化想到了就很 template 了。

## Description
[传送门](https://codeforces.com/problemset/problem/2117/H)

## Solution

先对每个数分别考虑。

对于每个整数 $x$，定义数组 $b_{x,i}$，当且仅当 $a_i=x$ 时 $b_{x,i} \gets 1$, 其余情况 $b_{x,i} \gets -1$。

那么就把这个问题转化成了求最大子段和问题，证明显然。

如果 $b_{x,i}$ 的最大子段和是 $s_x$，那么 $x$ 最大可能成为 $\lfloor\frac{s}{2}\rfloor$ 多数。

对每个 $x$ 开一棵线段树维护 $s_x$，然后再用一个 multiset 维护每个数的答案，只需支持插入，删除，求最大值即可。

具体地说，先把每个 $x$ 的最大子段和做一遍，（注意到这一步可以所有 $x$ 共用 $1$ 棵线段树，算完就清空）把值插入 multiset，对于修改操作再更新涉及的两个值的最大子段和即可，时间复杂度为 $O(n\log n+q\log n)$。

~~完结撒花。~~

显然我们并没有认真读题。

这样的空间复杂度是 $O(n^2)$ 的，会爆空间。（因为存在修改，不能用类似共用节点的套路）

那只能所有的数值共用 $1$ 棵线段树了。显然，这样我们无法在线处理修改操作。必须离线。

具体地说，把操作离线下来之后将波及到的两个数产生的新 $s$ 值再开头计算旧权值时一并计算，等到询问需要时再删除旧 $s$ 值并加入新值即可。

空间复杂度为 $O(n)$，时间复杂度不变，可以通过本题。

完结撒花。

## Code

[submission](https://codeforces.com/contest/2117/submission/323653663)

---

