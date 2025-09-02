# Pawns

## 题目描述

You are given a chessboard consisting of $ n $ rows and $ n $ columns. Rows are numbered from bottom to top from $ 1 $ to $ n $ . Columns are numbered from left to right from $ 1 $ to $ n $ . The cell at the intersection of the $ x $ -th column and the $ y $ -th row is denoted as $ (x, y) $ . Furthermore, the $ k $ -th column is a special column.

Initially, the board is empty. There are $ m $ changes to the board. During the $ i $ -th change one pawn is added or removed from the board. The current board is good if we can move all pawns to the special column by the followings rules:

- Pawn in the cell $ (x, y) $ can be moved to the cell $ (x, y + 1) $ , $ (x - 1, y + 1) $ or $ (x + 1, y + 1) $ ;
- You can make as many such moves as you like;
- Pawns can not be moved outside the chessboard;
- Each cell can not contain more than one pawn.

The current board may not always be good. To fix it, you can add new rows to the board. New rows are added at the top, i. e. they will have numbers $ n+1, n+2, n+3, \dots $ .

After each of $ m $ changes, print one integer — the minimum number of rows which you have to add to make the board good.

## 样例 #1

### 输入

```
5 3 5
4 4
3 5
2 4
3 4
3 5```

### 输出

```
0
1
2
2
1```

# 题解

## 作者：KellyFrog (赞：12)

提供一个非二分图做法

首先将问题转化成直线上的问题，显然两个问题是等价的：

直线上有一堆点，点上有一些球（一个点上有很多球），同时把所有球放开，球会往前滚到第一个空的点停在那，问最后一个球会滚到那；支持加球、减球。

考虑直接用线段树维护这个过程，记 $f_i$ 表示第 $i$ 个点会有几个球经过（包括停下来的那个）

显然最后的局面和放球的顺序无关，那么加一个球就找到右边第一个 $f_i=0$ 的 $j$，然后 $f_{i}\sim f_j$ 加 $1$

滚过一个点的 $f_i$ 个小球根本没有区别，所以减一个球就是找到第一个 $f_i=1$ 的 $j$，然后 $f_{i}\sim f_j$ 减 $1$

不难发现，第二类操作的 $f_i=1$ 前面不可能出现 $f_i=0$，否则就是一个位置停了两个球

那么直接线段树维护最小值、严格次小值即可，注意下标要开大

复杂度 $O(n+m\log n)$

代码因为 `pushup` 图省事所以常数极大，要跑 2.9s

```cpp
// Problem: CF1373G Pawns
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1373G
// Memory Limit: 250 MB
// Time Limit: 3000 ms

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

/*template ends here*/

const int N = 6e5 + 5;
const int inf = 0x3f3f3f3f;

struct Node {
	int lazy;
	int mx, mxpos;
	int smx, smxpos;
	Node() : mx(inf), smx(inf) {}
	Node(int lazy, int mx, int mxpos, int smx, int smxpos) : lazy(lazy), mx(mx), mxpos(mxpos), smx(smx), smxpos(smxpos) {}
};

Node tree[N<<2];
set<pair<int, int>> s;

inline Node merge(const Node& x, const Node& y) {
	vector<pair<int, int>> v;
	v.pb(mp(x.mx, x.mxpos)); v.pb(mp(x.smx, x.smxpos));
	v.pb(mp(y.mx, y.mxpos)); v.pb(mp(y.smx, y.smxpos));
	sort(v.begin(), v.end());
	if(v[0].fi >= inf) return Node(0, inf, 0, inf, 0);
	vector<pair<int, int>> ret;
	ret.pb(v[0]);
	for(int i = 1; i < v.size(); i++) {
		if(v[i].fi != v[i-1].fi) {
			ret.pb(v[i]);
		}
	}
	return Node(0, ret[0].fi, ret[0].se, ret[1].fi, ret[1].se);
}

inline void pushup(int cur) {
	tree[cur] = merge(tree[cur << 1], tree[cur << 1 | 1]);
}

inline void setlazy(int cur, int x) {
	tree[cur].lazy += x;
	tree[cur].mx += x;
	tree[cur].smx += x;
}

inline void pushdown(int cur) {
	if(tree[cur].lazy) {
		setlazy(cur << 1, tree[cur].lazy);
		setlazy(cur << 1 | 1, tree[cur].lazy);
		tree[cur].lazy=  0;
	}
}

inline void add(int cur, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(cur, x), void();
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) add(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) add(cur << 1 | 1, ql, qr, x, mid + 1, r);
	pushup(cur);
}

Node qres; bool isfirst;

inline void query(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		if(isfirst) qres = tree[cur], isfirst = 0;
		else qres = merge(qres, tree[cur]);
		return;
	}
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) query(cur << 1, ql, qr, l, mid);
	if(mid < qr) query(cur << 1 | 1, ql, qr, mid + 1, r);	
}

inline void build(int cur, int l, int r) {
	if(l == r) {
		tree[cur] = Node(0, 0, l, inf, l);
		return;
	}
	int mid = l + r >> 1;
	build(cur << 1, l, mid);
	build(cur << 1 | 1, mid + 1, r);
	pushup(cur);
}

inline int querypos(int cur, int l, int r) {
	if(l == r) return l;
	pushdown(cur);
	int mid = l + r >> 1;
	auto check = [&](int x) { return 0 < x && x < inf; };
	if(check(tree[cur<<1|1].mx) || check(tree[cur<<1|1].smx)) return querypos(cur << 1 | 1, mid + 1, r);
	else return querypos(cur << 1, l, mid);
}

int n, m, k;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k >> m;
	
	build(1, 1, n*2+m);
	
	int q = m;
	while(q--) {
		int x, y;
		cin >> x >> y;
		int p = y + abs(x - k);
			
		if(s.count(mp(x, y))) {
			s.erase(mp(x, y));
			isfirst = 1;
			query(1, p, n*2+m, 1, n*2+m);
			int pos = qres.mx == 1 ? qres.mxpos : qres.smxpos;
			add(1, p, pos, -1, 1, n*2+m);
		} else {
			s.insert(mp(x, y));
			isfirst = 1;
			query(1, p, n*2+m, 1, n*2+m);
			int pos = qres.mxpos;
			add(1, p, pos, 1, 1, n*2+m);
		}
		cout << max(0, querypos(1, 1, n*2+m) - n) << "\n";
	}
	return 0;
}

```

---

## 作者：duyi (赞：11)

## 题解 CF1373F Pawns

首先，发现“挪动过程中，每个格子里**不能有多个棋子**”，这个要求并不重要：我们只要保证了**最终局面下**每个格子里不超于一个棋子，那在移动的过程中，总能巧妙地安排先后顺序，使得这个过程满足条件。

对每个棋子$i$，它会有一个至少要达到的$y$坐标，不妨设为$a_i$。容易发现：$a_i=y_i+|x_i-k|$。也就是说，对于任意$j\geq a_i$，棋子$i$最终移动到$(k,j)$都是合法的。

设答案为$s$。有这样一个比较自然的结论：$s$可行，当且仅当$\forall j\in\{a_i\}$，【$a_i\geq j$的$i$的数量】小于等于【$s-j+1$】。如果$s\geq \max\{a_i\}$，则这个条件，也可以表述为：$\forall j\in[1,s]$，......。

这个结论，可以用Hall定理来证明：把每个棋子$i$看做二分图左部的点，每个格子$j$看做二分图右部的点。从$i$向所有$j\in[a_i,s]$连边。那么存在完美匹配，当且仅当对左边的任意一个点集$S$，右边“与$S$里至少一个点相邻”的点的数量大于等于$|S|$。这与我们的结论是等价的。

当然，现在我们还不知道$s$的值，这是我们要求出的。对所有$j\in[1,2n]$，我们记$f(j)$表示【$a_i\geq j$的$i$的数量】。根据前面的讨论，一个$s$ ($s\geq\max\{a_i\}$)能作为答案，当且仅当$\forall j\in[1,s]:f(j)\leq s-j+1$。移项得：$s\geq f(j)+j-1$。又因为对于$j\in(\max\{a_i\},s]$，$f(j)+j-1$一定小于$s$，所以不用考虑他们。我们只要对$j\in[1,\max\{a_i\}]$，查询$f(j)+j-1$的**区间最大值**即可。

当新加入一个$a_i$时，造成的影响是，对$j\in[1,a_i]$这个区间，所有$f(j)$会加$1$，所以我们要支持**区间加**。对$\max\{a_i\}$，可以用一个$\texttt{multiset}$维护，比较简单。

总结来说，我们主要需要维护一棵线段树，支持区间加、查询区间最大值。需要注意的是，线段树的值域（也就是$\max\{a_i\}$的理论最大值），是$2n$而不是$n$。

参考代码：

```cpp
//problem:CF1373G
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

template<typename T>inline void ckmax(T& x,T y){x=(x>y?x:y);}

const int MAXN=4e5;
int n,K,m;

struct SegmentTree{
	int maxv[MAXN*5+5],tag[MAXN*4+5];
	void push_up(int p){
		maxv[p]=max(maxv[p<<1],maxv[p<<1|1]);
	}
	void build(int p,int l,int r){
		if(l==r){
			maxv[p]=l-1;
			return;
		}
		int mid=(l+r)>>1;
		build(p<<1,l,mid);
		build(p<<1|1,mid+1,r);
		push_up(p);
	}
	void upd(int p,int v){
		tag[p]+=v;
		maxv[p]+=v;
	}
	void push_down(int p){
		if(tag[p]){
			upd(p<<1,tag[p]);
			upd(p<<1|1,tag[p]);
			tag[p]=0;
		}
	}
	void range_add(int p,int l,int r,int ql,int qr,int v){
		if(ql<=l && qr>=r){
			upd(p,v);
			return;
		}
		int mid=(l+r)>>1;
		push_down(p);
		if(ql<=mid)
			range_add(p<<1,l,mid,ql,qr,v);
		if(qr>mid)
			range_add(p<<1|1,mid+1,r,ql,qr,v);
		push_up(p);
	}
	int query_max(int p,int l,int r,int ql,int qr){
		if(ql<=l && qr>=r)
			return maxv[p];
		int mid=(l+r)>>1;
		push_down(p);
		int res=0;
		if(ql<=mid)
			res=query_max(p<<1,l,mid,ql,qr);
		if(qr>mid)
			ckmax(res,query_max(p<<1|1,mid+1,r,ql,qr));
		push_up(p);
		return res;
	}
	SegmentTree(){}
}T;

int main() {
	cin>>n>>K>>m;
	T.build(1,1,n*2);
	set<pii>s1;
	multiset<int>s2;
	s2.insert(n+1);
	for(int i=1;i<=m;++i){
		int x,y;cin>>x>>y;
		if(!s1.count(mk(x,y))){
			//加入
			s1.insert(mk(x,y));
			int p=y+abs(x-K);
			//cout<<"ins "<<p<<endl;
			s2.insert(p);
			int maxp=(*s2.rbegin());
			T.range_add(1,1,n*2,1,p,1);
			cout<<T.query_max(1,1,n*2,1,maxp)-n<<endl;
		}
		else{
			//删除
			s1.erase(mk(x,y));
			int p=y+abs(x-K);
			//cout<<"del "<<p<<endl;
			s2.erase(s2.find(p));
			int maxp=(*s2.rbegin());
			T.range_add(1,1,n*2,1,p,-1);
			cout<<T.query_max(1,1,n*2,1,maxp)-n<<endl;
		}
	}
	return 0;
}
```



---

## 作者：STrAduts (赞：10)

小清新线段树题（（

每个位置的边只能向靠右的三个方向走，最后要走到一条基准线上。即对于一个点 $(x, y)$，它最后应该落在 $(k, y + |k - x|)$。

士兵可以一个一个进行移动，所以互相的移动行程不会互相干扰。考虑利用这个性质将题目从二维转换为一维。

即：有一队士兵排好队，每个士兵有一个预选定的位置。当轮到第 $i$ 位士兵选位置时，若预选定位置有其它士兵，则选择当前选定位置右边紧挨着的位置，直到当前选定位置上不再有其他士兵后站入该位置。试问至少需要新加入多少个格子可以收容所有士兵。

盲目感觉这种“当前放不了就考虑下一个”的题目常常会考虑维护一些后缀，所以接下来我们引入后缀。

如果构造一个数组 $A$，且初始时 $\forall A_i = -1 \space s.t. i \in [1, n]$。且定义数组 $f$，表示有 $f_i$ 个士兵预选定了 $i$ 这个位置。则答案为序列 $A + f$ 的后缀和最大值。（建议自己手 Rua 一下。

但对于 $i > n$ 的部分，这样是不好处理的。因为在原题中，这些位置也应该参与到“新加入位置”的贡献中。于是更改 $A$ 的构造方式。

在 $i \in [1, n]$ 的部分，我们直接令 $A_i = -(n - i + 1)$，即直接储存后缀。

而 $i > n$ 的部分，我们尝试分析其贡献。如果要使用 $n + 2$ 这个位置，则我们需要先添加一个 $n + 1$ 的位置，也就是第 $n + 2$ 项初值应该为 $1$。同理可知 $n + 1 \dots n + n$ 等位置，故也可令 $i > n$ 的部分中 $A_i = -(n - i + 1)$。

不难发现，现在答案为 $\max \{ A_i + g_i \} \space s.t. i \in [1, w]$，其中 $w$ 是预选定位置最靠右的一个，$g$ 是 $f$ 的后缀序列。

$f$ 是动态更新的，每次更新会先区间修改 $g$，最终作用于 $A + f$。故 $A + g$ 可以直接使用区修区查的线段树维护。$w$ 使用 `set`，加一个计数器维护即可。

总时间复杂度 $O(n \log n)$。这里使用的是常数较小的 zkw 线段树。

```cpp
#include <map>
#include <set>
#include <cstdio>
using namespace std;

int Abs (int x) { return x < 0 ? -x : x; }
int Max (int x, int y) { return x > y ? x : y; }
int Min (int x, int y) { return x < y ? x : y; }

int Read () {
    int x = 0, k = 1;
    char s = getchar ();
    while (s < '0' || s > '9') {
        if (s == '-')
            k = -1;
        s = getchar ();
    }
    while ('0' <= s && s <= '9') 
        x = (x << 3) + (x << 1) + (s ^ 48), s = getchar ();
    return x * k;
}

void Write (int x) {
    if (x < 0)
        putchar ('-'), x = -x;
    if (x > 9)
        Write (x / 10);
    putchar (x % 10 + '0');
}

void Print (int x, char s) { Write (x), putchar (s); }

const int Inf = 1e9;
const int Maxn = 4e5 + 5;

set <int> s;
map <int, int> Vis[Maxn];
int a[Maxn], Tr[Maxn * 3], Lazy[Maxn * 3], Cnt[Maxn], p;

void Make_Tree (int n) {
    p = 1;
    while (p < n + 2)
        p <<= 1;
	Tr[p + n + 1] = Tr[p] = -Inf;
    for (int i = 1; i <= n; i++)
        Tr[p + i] = a[i];    
    for (int i = p + n + 1; i > 1; i--)
        Tr[i >> 1] = Max (Tr[i], Tr[i ^ 1]);
}

void Update (int l, int r, int x) {
    for (l += p - 1, r += p + 1; (l ^ r) != 1; l >>= 1, r >>= 1) {
        if (!(l & 1))
            Tr[l ^ 1] += x, Lazy[l ^ 1] += x;
        if (r & 1)
            Tr[r ^ 1] += x, Lazy[r ^ 1] += x;
        Tr[l >> 1] = Max (Tr[l], Tr[l ^ 1]) + Lazy[l >> 1];
        Tr[r >> 1] = Max (Tr[r], Tr[r ^ 1]) + Lazy[r >> 1];
    }
    for (; l > 1; l >>= 1)
        Tr[l >> 1] = Max (Tr[l], Tr[l ^ 1]) + Lazy[l >> 1];
}

int Query (int l, int r) {
    int Res = -Inf, Resl = -Inf, Resr = -Inf;
    for (l += p - 1, r += p + 1; (l ^ r) != 1; l >>= 1, r >>= 1) {
        if (!(l & 1))
            Resl = Max (Resl, Tr[l ^ 1]);
        if (r & 1)
            Resr = Max (Resr, Tr[r ^ 1]);
        Resl += Lazy[l >> 1], Resr += Lazy[r >> 1];
    }
    Res = Max (Resl, Resr);
    for (; l > 1; l >>= 1)
        Res += Lazy[l >> 1];
    return Res;
}

int main () {
    int n = Read (), k = Read (), m = Read ();
    for (int i = 1; i <= 2 * n; i++)
        a[i] = -(n - i + 1);
    Make_Tree (n << 1);
    for (int i = 1, x, y; i <= m; i++) {
        x = Read (), y = Read ();
        if (!Vis[x][y]) {
            if (!Cnt[y + Abs (x - k)])
                s.insert (y + Abs (x - k));
            Cnt[y + Abs (x - k)]++;
            Update (1, y + Abs (x - k), 1), Vis[x][y] = true;
        }
        else {
            Cnt[y + Abs (x - k)]--;
            if (!Cnt[y + Abs (x - k)])
                s.erase (y + Abs (x - k));            
            Update (1, y + Abs (x - k), -1), Vis[x][y] = false;
        }
        if (s.empty ())
            Print (0, '\n');
        else 
            Print (Max (0, Query (1, *s.rbegin ())), '\n');   
    }
    return 0;
}
```

---

## 作者：yangchenxiao (赞：8)

首先由于有 $(x,y+1)$ 的操作，那么完全没有必要考虑成二维问题，直接将每个点的坐标设为 $y+|x-k|$，即直接走过去的位置即可。   
那么在一条线段上，每个位置只能放一个球，球只能向右移动，最少要移动多少呢？    
如果把每个位置的球的数量减一，那么答案就是最大后缀和。   
于是问题变为单点修改，最大后缀和，线段树维护即可。    
需要注意的细节是需要求最后一个球所在位置的最大后缀和（这个位置用 $multiset$ 维护），因此线段树上还得来个二分。

非常简短的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
const int maxn=4e5+5;
int n,k,m,x,y;
multiset<int>s;map<pair<int,int>,int>vis;
int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
struct Seg{int l,r,rmx,sum;}t[maxn*4];
void update(Seg &p,Seg ls,Seg rs){
	p.sum=ls.sum+rs.sum;
	p.rmx=max(rs.rmx,ls.rmx+rs.sum);
}
void build(int p,int l,int r){
	t[p].l=l,t[p].r=r;t[p].rmx=t[p].sum=-1;
	int mid=l+r>>1;if(l==r)return ;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	return update(t[p],t[p<<1],t[p<<1|1]);
}
void change(int p,int pos,int op){
	if(t[p].l==t[p].r)return t[p].rmx+=op,t[p].sum+=op,void();
	int mid=t[p].l+t[p].r>>1;change(p<<1|(pos>mid),pos,op);
	return update(t[p],t[p<<1],t[p<<1|1]);
}
Seg ask(int p,int pos){
	if(t[p].r<=pos)return t[p];
	int mid=t[p].l+t[p].r>>1;Seg res;
	if(pos<=mid)return ask(p<<1,pos);
	update(res,ask(p<<1,pos),ask(p<<1|1,pos));
	return res;
}
int main(){
	n=read(),k=read(),m=read();build(1,1,n+m);
	for(int i=1;i<=m;i++){
		x=read(),y=read();
		int op=(vis[mp(x,y)]?-1:1),pos=y+abs(x-k);
		vis[mp(x,y)]+=op;change(1,pos,op);
		op==1?s.insert(pos):s.erase(s.find(pos));
		if(!s.size()){puts("0");continue;}
		int mx=max(n,*--s.end());Seg res=ask(1,mx);
		printf("%d\n",max(0,mx-n+res.rmx));
	}
	return 0;
}
````

---

## 作者：NATO (赞：3)

做分治题做的。

### 思路浅析：

先将题目中我们要求的东西明确一下：

有一堆球，对于一个球 $(x_i,y_i)$ 可以放的位置最小为 $|x_i-k|+y_i$，每个位置只能放一个球，问 $\max(\max\limits_{i=1}where_i,n)-n$ 的最小值，支持加球和删球。

考虑我们加一个球 $(x,y)$ 该怎么办。

策略是显然的，贪心地填入 $|x-k|+y$ 及以后第一个没有填的位置即可，这个操作可以使用线段树二分查找后并插入在 $O(\log n)$ 的时间内完成，维护一个最大填入位置即可。

但是删除呢？？？

emm...一开始笔者天真地认为直接把删除的球放的位置置为未放就可以了，但错误显而易见：可能我其它放的球可以放到这个位置了，求出的最大填入位置就不一定是最小的了。

嗯，添加容易删除难，这不是明确暗示我们使用线段树分治吗？

那么简单搞一下每个球的出现时间扔到时间线段树上，遍历时按添加球的做法做一下，叶节点统计答案，最后撤销即可。

时间复杂度是高贵的 $O(n\log n^2)$，优点在于思维量少，不用动脑。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 800000
using namespace std;
#define ls(id) id*2
#define rs(id) id*2+1
struct px
{
	ll x,y;
};
vector<px>last[800005];
void add(ll id,ll l,ll r,ll ml,ll mr,px a)
{
	if(ml<=l&&r<=mr)
	{
		last[id].push_back(a);return;
	}
	ll mid=l+r>>1;
	if(ml<=mid)add(ls(id),l,mid,ml,mr,a);
	if(mr>mid)add(rs(id),1+mid,r,ml,mr,a);
}
ll n,k,q;
ll ans[200005];
struct tree
{
	ll maxn,sz;
}tr[3200005];
struct bk
{
	ll uid;tree what;
};
map<pair<ll,ll>,ll>st,ed;
void update(ll id,ll l,ll r,ll ml,stack<bk>&a)
{
	a.push((bk){id,tr[id]});
	if(l==r)
	{
		tr[id].sz=1;tr[id].maxn=l;
		return;
	}
	ll mid=l+r>>1;
	if(ml<=mid)update(ls(id),l,mid,ml,a);
	else update(rs(id),mid+1,r,ml,a);
	tr[id].sz=tr[ls(id)].sz+tr[rs(id)].sz;
	tr[id].maxn=max(tr[ls(id)].maxn,tr[rs(id)].maxn);
}
ll get_where(ll id,ll l,ll r)
{
	if(l==r)return l;
	ll mid=l+r>>1;
	if(tr[ls(id)].sz!=mid-l+1)return get_where(ls(id),l,mid);
	return get_where(rs(id),1+mid,r);
}
void find_where(ll id,ll l,ll r,ll ml,ll mr,ll &val)
{
	if(tr[id].sz==r-l+1)return;
	if(ml<=l&&r<=mr)
	{
		val=get_where(id,l,r);return;
	}
	ll mid=l+r>>1;
	if(ml<=mid)find_where(ls(id),l,mid,ml,mr,val);
	if(val)return;
	if(mr>mid)find_where(rs(id),1+mid,r,ml,mr,val);
}
void solve(ll id,ll l,ll r)
{
	stack<bk>a;
	for(auto it:last[id])
	{
		ll x=it.x,y=it.y;
		ll ml=abs(x-k)+y,can=0;
		find_where(1,1,MAXN,ml,MAXN,can);
		update(1,1,MAXN,can,a);
	}
	ll mid=l+r>>1;
	if(l!=r)
	{
		solve(ls(id),l,mid);
		solve(rs(id),1+mid,r);
	}
	else ans[l]=max(n,tr[1].maxn)-n;
	while(!a.empty())
	{
		bk now=a.top();a.pop();
		tr[now.uid]=now.what;
	}
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k>>q;
	for(ll i=1;i<=q;++i)
	{
		ll x,y;
		cin>>x>>y;
		if(!st[{x,y}])
		{
			st[{x,y}]=i;ed[{x,y}]=0;
		}
		else 
		{
			add(1,1,q,st[{x,y}],i-1,(px){x,y});
			ed[{x,y}]=i-1;
			st[{x,y}]=0;
		}
	}
	for(auto it:st)
	{
		if(it.second==0)continue;
		if(!ed[it.first])
		ed[it.first]=q;
		add(1,1,q,it.second,ed[it.first],(px){it.first.first,it.first.second});
	}
	solve(1,1,q);
	for(ll i=1;i<=q;++i)cout<<ans[i]<<'\n';
}
```

---

## 作者：caidzh (赞：3)

事实上，题目中给出的**一个格子中不能有多个棋子**的条件只限定了最终状态，中间移动的过程完全可以认为一个格子上可以存在多个棋子

然后可以想到求出一个棋子最近能到达的特殊列上的格子

不妨对于棋子$i$称这个值为$a_i$，其值显然等于$a_i=y_i+|x_i-k|$

设答案为$s$，此时构建一个二分图匹配的模型，棋子作为左部点，格子作为右部点，棋子$i$向行数处于$[a_i,s]$的点连边，要求存在完美匹配，使用 Hall 定理

此时我们考虑维护这样的一个东西：加入一个点$i$的时候将$a_i$位置加$1$，由 Hall 定理，存在完美匹配的条件是对于每个$j$，$[j,s]$区间的和$\le s-j+1$

所以如果令$[j,s]$区间的和为$p_j$，要求是$p_j+j-1\le s$

可以使用线段树来维护区间最值
```cpp
const int maxn=600010,mod=998244353;
int n,m,k;set<pair<int,int> >s;
set<int>v;set<int>::reverse_iterator it;
int mx[maxn<<2],lzy[maxn<<2],cnt[maxn];
void pushup(int x){
	mx[x]=max(mx[ls],mx[rs]);
}
void Build(int x,int l,int r){
	if(l==r){
		mx[x]=l-1;return;
	}int mid=l+r>>1;Build(ls,l,mid);
	Build(rs,mid+1,r);pushup(x);
}
void pushdown(int x){
	mx[ls]+=lzy[x];mx[rs]+=lzy[x];
	lzy[ls]+=lzy[x];lzy[rs]+=lzy[x];lzy[x]=0;
}
void update(int x,int l,int r,int L,int R,int k){
	if(l>=L&&r<=R){
		mx[x]+=k;lzy[x]+=k;return;
	}int mid=l+r>>1;pushdown(x);if(mid>=L)update(ls,l,mid,L,R,k);
	if(mid<R)update(rs,mid+1,r,L,R,k);pushup(x);
}
int Query(int x,int l,int r,int L,int R){
	if(l>=L&&r<=R)return mx[x];
	int mid=l+r>>1,ans=0;pushdown(x);pushup(x);
	if(mid>=L)ans=max(ans,Query(ls,l,mid,L,R));
	if(mid<R)ans=max(ans,Query(rs,mid+1,r,L,R));return ans;
}
int main(){
	n=read();k=read();m=read();Build(1,1,2*n+m);
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),is=1,a=y+abs(x-k);
		if(s.count(mp(x,y))){
			cnt[a]--;
			if(!cnt[a])v.erase(a);
			is=-1;s.erase(mp(x,y));
		}
		else{
			cnt[a]++;
			if(cnt[a]==1)v.insert(a);
			s.insert(mp(x,y));
		}update(1,1,2*n+m,1,a,is);
		if(!v.size()){cout<<0<<endl;continue;}it=v.rbegin();
		int ans=max(Query(1,1,2*n+m,1,*it),n);cout<<ans-n<<endl;
	}return 0;
}
```


---

## 作者：licn (赞：3)

# **线段树做法**

## **题目分析：**
每次移动必须向右移动一位，我们先以最快速度移动到第 $k$ 行，需要 $|x-k|$ 步。那么当移动到第 $k$ 行时，在不考虑重叠的情况下至少在第 $y+|x-k|$ 列。那么就变成了一个线性的问题，可将题目理解为：在一条线上，给出了线的长度和第 $i$ 次操作添加或删除的点的位置（可重叠），每个点只能向右移动。要使每个点移动到不与其他点重叠的位置上，至少将原线的长度增加多少？

再化简，给出一些点可以放置的位置的最小值，这些点任意两个不能放在同一个位置。问所有点中，位置最大的减 $n$ 的值最小是多少？

## **做法：**

由于只能向右放，我们用 $v_{i}$ 来记录初始位置为 $i$ 的个数。它必须向右边放 $v_{i}$ 个，我们给 $v$ 数组一开始的值赋为 $-1$ 显然放一个点不需要向右边放，从 $1$ 开始到初始位置最大的点这个区间从右端点开始连续 $v_{i}$ 的和，我们称之为后缀和。最大的后缀和就表示会向这个区间的右端点超出多少，那么右端点加最大后缀和就是所有点中，移动后位置的最大值。

## **怎么求？**

### **最大连续后缀和的和：**
如果暴力去求，复杂度是 $O(n)$，是不可取的。可修改、可查询并且是线性的我们会想到线段树。用 $rmax_{p}$ 表示 $l_{p}$ 到 $r_{p}$ 这个区间中最大后缀和。我们还需要用 $data_{p}$ 来维护区间的和。

$rmax_{p}=\max(rmax_{rson},rmax_{lson}+data_{rson})$ 复杂度为 $O(n \log n)$。

### **初始位置的最大值：**
如果记录最大值,那么删了怎么办？~~（显然不行）~~

当然你可以使用 `multiset` 容器来维护。用线段树怎么维护？

我们做二分。如果有初始位置在右区间里，我们就缩小区间在右边找，否则在左区间里找。由于 $data_{p}$ 记录区间和，我么就直接判断当 $data_{rson}>-(r_{rson}-l_{lson}+1)$ 在右区间里找，否则进入左区间。

最后我们用移动后位置的最大值减去 $n$ 就是每一次的答案。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;//多开一点，总没坏处
int n,ans,m,k;
map<pair<int,int>,int>v;
struct node
{
	int l,r,data,rmax;
}t[N<<4];
void pushup(int p)//更新值
{
	t[p].data=t[p<<1].data+t[p<<1|1].data;
	t[p].rmax=max(t[p<<1|1].rmax,t[p<<1].rmax+t[p<<1|1].data);
}
void build(int p,int l,int r)//建树
{
	t[p].l=l,t[p].r=r;
	if(l==r)
	{
		t[p].data=t[p].rmax=-1;//初始赋为-1
		return;
	}
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	pushup(p);
}
void add(int p,int x,int k)//单点修改
{
	if(t[p].l==t[p].r)
	{
		t[p].data+=k;
		t[p].rmax+=k;
		return;
	}
	int mid=t[p].l+t[p].r>>1;
	if(x<=mid)add(p<<1,x,k);
	else add(p<<1|1,x,k);
	pushup(p);
}
int query(int p)//二分查询最大初始值
{
	if(t[p].l==t[p].r)return t[p].l;
	if(t[p<<1|1].data>-(t[p<<1|1].r-t[p<<1|1].l+1))return query(p<<1|1);
	else return query(p<<1);
}
node query2(int p,int l,int r)//查询最大后缀和
{
	if(l<=t[p].l&&t[p].r<=r)return t[p];
	int mid=t[p].l+t[p].r>>1;
	if(l>mid)return query2(p<<1|1,l,r);
	else if(r<=mid)return query2(p<<1,l,r);
	else
	{
		node tl=query2(p<<1,l,r);
		node tr=query2(p<<1|1,l,r);
		node x;
		x.data=tl.data+tr.data;//切记不要手滑不打，我被坑惨了
		x.rmax=max(tl.rmax+tr.data,tr.rmax);
		return x;
	}
}
int main(){
	cin>>n>>k>>m;
	build(1,1,2*n);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		int z=abs(x-k)+y;
		if(v[make_pair(x,y)])add(1,z,-1),v[make_pair(x,y)]=0;
		else add(1,z,1),v[make_pair(x,y)]=1;
		int p=max(n,query(1));
		cout<<max(0,p-n+query2(1,1,p).rmax)<<endl;//不能比0小
	}
	return 0;
}

---

## 作者：xyzfrozen (赞：1)

提供一种新做法。

每个棋子最快到达 $k$ 行的位置就是 $(k,y+\lvert x-k \rvert)$，之后就是找一个位置放它。

把这个问题进一步抽象：

给定一个 $[1,+\infty]$ 01 串，初始全部为 $0$，每个棋子有一个限制，需要在 $lim=y+\lvert x-k \rvert$ 及之后找到第一个为 $0$，改为 $1$。

添加棋子就是完成上述操作，考虑线段树单点修改+线段树二分，$O(q\log n)$。

比较麻烦的就是这个删棋子，我们考察删掉一个棋子的影响就是可能会挪动别的棋子来填这个位置，但是我们贪心的想，如果要填这个位置，只可能是合法的最远棋子来填。

给这个模型抽象一下，设当前被删掉的棋子为 $now$：

每个棋子有两个属性，$x=lim$，$y=pos$（串上填棋子的位置），我们要做就是把 $x_i \leq y_{now} \lor \max y_i \geq y_{now}$ 的那个棋子填到 $y_{now}$。

注意，我们如果又挪动了一个棋子，那么这个棋子空出来的位置又会给新的棋子用，我们需要一直递归处理，线段树单点修在 $x_i$ 对 $y_i$ 取 $\max$ +前缀 $\max$ 查询。

在每次插入棋子的时候用 `set` 维护一下最右的 $1$ 的位置。

[仅供参考](https://codeforces.com/contest/1373/submission/246424198)

---

## 作者：daniEl_lElE (赞：1)

首先计算出所有棋子最近到达第 $k$ 行的位置，记为 $t$。

所以说在移动的时候可以贪心，从左往右找到大于等于 $t$ 的空余位置加入。

如何维护？我们考虑最后一个极长连续段，设起点为 $p$，那么所有最近到达 $t\geq p$ 的棋子都会被放到 $p$ 及以后。由于我们设的是最后一个极长连续段的起点，故可以假设所有 $t\geq p$ 的棋子都在 $t$ 为第一个。记这样的棋子个数为 $cnt_p$，那么这种情况下最大的一列至少是 $p+cnt_p-1$。于是答案就是 $\max(0,\max_{i=1}^{2n}(i+cnt_i-1)-n)$。

容易发现可以在线段树上先每个位置塞入 $i$，然后动态区间加维护 $cnt_i$。复杂度 $O(q\log n)$。

小细节是，要维护一个目前最右边的 $t$。这个很容易解决。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
struct sgt{
	int f[1600005],lzt[1600005];
	void pushdown(int i){
		f[i*2]+=lzt[i];
		f[i*2+1]+=lzt[i];
		lzt[i*2]+=lzt[i];
		lzt[i*2+1]+=lzt[i];
		lzt[i]=0;
	}
	void build(int i,int l,int r){
		if(l==r){
			f[i]=l;
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=max(f[i*2],f[i*2+1]);
	}
	void change(int i,int l,int r,int ql,int qr,int tag){
		if(ql<=l&&r<=qr){
			lzt[i]+=tag;
			f[i]+=tag;
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,tag);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,tag);
		f[i]=max(f[i*2],f[i*2+1]);
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(ql>r||qr<l) return 0;
		pushdown(i);
		return max(qry(i*2,l,mid,ql,qr),qry(i*2+1,mid+1,r,ql,qr));
	}
}tree;
map<pair<int,int>,int> mp;
map<int,int> cnt;
priority_queue<int> pq;
signed main(){
	int n,k,m; cin>>n>>k>>m;
	tree.build(1,1,2*n);
	while(m--){
		int x,y; cin>>x>>y;
		int toc=llabs(x-k)+y;
		if(mp[make_pair(x,y)]){
			cnt[toc]--;
			while(!pq.empty()&&!cnt[pq.top()]) pq.pop();
			tree.change(1,1,2*n,1,toc,-1);
		}
		else{
			pq.push(toc);
			cnt[toc]++;
			tree.change(1,1,2*n,1,toc,1);
		}
		mp[make_pair(x,y)]^=1;
		if(pq.empty()) cout<<0<<"\n";
		else cout<<max(0ll,tree.qry(1,1,2*n,1,pq.top())-n-1)<<"\n";
	}
	return 0;
}

```

---

## 作者：TernaryTree (赞：0)

这不是我们线段树分治板子题吗，没脑子是这样的。

首先一个点 $(x,y)$ 能到所有 $j\ge y+|k-x|$ 的 $(k,j)$，那么我们先线段树分治，把每个点出现时间扔到时间轴对应区间上，然后剩下的就是如下问题：

- 将可重集 $S$ 加入一个数 $k$
- 查询，令 $S$ 中所有数有一个大于等于自己本身的编号，并使编号两两不同的最小编号

动态维护答案，贪心地每次插入时找 $\ge i$ 的最小的没有被编号的位置即可。用可撤销并查集即可。复杂度是低劣的两只 $\log$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

const int maxn = 1e6 + 10;
const bool multidata = 0;

template<typename T = int>
T read() {
	T x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

template<typename T = int>
void write(T x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write<T>(x / 10), pc(x % 10 + '0');
}

int n, k, q, res[maxn], ans;
map<pii, int> in;
vector<pii> tr[maxn << 2];
int fa[maxn], dep[maxn], ed[maxn];

void insert(int u, int l, int r, int ql, int qr, pii v) {
	if (ql <= l && r <= qr) {
		tr[u].push_back(v);
		return;
	}
	if (ql <= mid) insert(lc, ql, qr, v);
	if (qr > mid) insert(rc, ql, qr, v);
}

struct op {
	int u, v, d, e;
};

op st[maxn]; int cnt;

int find(int x) { return fa[x] == x ? x : find(fa[x]); }
void merge(int u, int v) {
	u = find(u), v = find(v);
	if (u == v) return;
	if (dep[u] < dep[v]) swap(u, v);
	st[++cnt] = {u, v, dep[u] == dep[v], ed[u]};
	if (dep[u] == dep[v]) dep[u]++;
	fa[v] = u;
	ed[u] = max(ed[u], ed[v]);
}

int check(int x) {
	int p = find(x), tmp = ed[p];
	merge(p, tmp + 1);
	return tmp;
}

void solve(int u, int l, int r) {
	int lst = ans, pa = cnt;
	for (pii i : tr[u]) {
		int x = i.sc + abs(k - i.fs), y = check(x);
//		cout << l << " " << r << " " << x << " " << y << endl; 
 		ans = max(ans, y);
	}
	if (l == r) {
		res[l] = max(ans - n, 0ll);
	} else {
		solve(lc), solve(rc);
	}
	// rollback
	ans = lst;
	while (cnt > pa) {
		fa[st[cnt].v] = st[cnt].v;
		dep[st[cnt].u] -= st[cnt].d;
		ed[st[cnt].u] = st[cnt].e;
		--cnt;
	}
}

void fake_main() {
	n = read(), k = read(), q = read();
	rep(i, 1, maxn - 1) fa[i] = ed[i] = i, dep[i] = 1;
	rep(i, 1, q) {
		int x = read(), y = read();
		if (in.count({x, y})) {
			int l = in[{x, y}], r = i - 1;
			insert(1, 1, q, l, r, {x, y});
			in.erase({x, y});
		} else {
			in[{x, y}] = i;
		}
	}
	for (pair<pii, int> i : in) {
		int l = i.sc, r = q;
		insert(1, 1, q, l, r, i.fs);
	}
	solve(1, 1, q);
	rep(i, 1, q) write(res[i]), pc('\n');
}

signed main() {
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}
```

---

## 作者：forest114514 (赞：0)

### CF1373G Pawns

大家的做法实在是太智慧了，什么 Hall 定理还是 set 维护亦或者线段树上二分根本想不到，本蒟蒻只会简单无脑分讨做法。

还是讲讲怎么无脑分讨做法吧：（我们称士兵为一个棋子）

首先大家都知道一个在 $(x,y)$ 的点最后会到 $(k,y+|x-k|)$，然后我们对 $k$ 的格子上的棋子考虑即可。

对于 $k$ 行格子的一个区间区间，我们维护以下标记：$sum$ 区间棋子总数，$pos$ 区间最右边的棋子的位置，$res$ 区间中放不下的棋子的数量，然后考虑合并两个区间记为 $l/r$。

1. 区间有放不下的棋子

   首先 $pos$ 一定是区间右端点。

   对于 $res$ 的判断，此时有两种情况，**右边区间本来放不下**或者 **右边放得下但加上左边的 $res_l$ 后放不下**。

   1. **右边区间本来放不下**：直接特判一下 $res_r$ 的增加，首先此时右边剩下的可放格子数为 $len_r-(sum_r-res_r)$，所以此时 $res=res_r+\max(0,res_l-len_r+(sum_r-res_r))$；
   2. **右边放得下但加上左边的 $res_l$ 后放不下**： $res$ 就是 $res_l+sum_r-len_r$。

2. 区间所有棋子都放得下

   $res$ 肯定为 0，我们只用考虑 $pos$ 的位置。

   只用考虑右区间有无棋子。（我们令右边区间左端点为 $L_r$）

   1. 没有棋子：如果 $res_l=0$ 的话 $pos$ 就是 $pos_l$，否则就是 $L_r+res_l-1$。
   2. 有棋子：考虑左边的棋子能否在 $pos_r$ 之前用完即可，此时 $pos$ 为 $\max(pos_r,L_r+sum_r+res_l-1)$。

带修改可以用线段树维护分治，这种做法常数小，还是可以的，最后记得线段树长度是 $2n$ 因为 $y+|x-k|$ 最大是 $n+|n-1|=2n-1$。

关键代码：

```cpp
const int N=4e5+100;
int n,k,q;
struct SGT{
	int l,r,sum,pos,res;
}tr[N<<2];
void build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	tr[x].pos=-1,tr[x].res=0,tr[x].sum=0;
	if(l==r) return;
	int mid=l+r>>1;
	build(ls(x),l,mid);build(rs(x),mid+1,r);
}
void pushup(int x){
	tr[x].sum=tr[ls(x)].sum+tr[rs(x)].sum;
	if(tr[rs(x)].res>0){//右边本来装不下 
		tr[x].pos=tr[x].r;
		int ad=tr[rs(x)].r-tr[rs(x)].l+1-(tr[rs(x)].sum-tr[rs(x)].res);//右边剩下的空位数量 
		tr[x].res=tr[rs(x)].res+max(0,tr[ls(x)].res-ad);
		return;
	}
	if(tr[rs(x)].sum+tr[ls(x)].res>tr[rs(x)].r-tr[rs(x)].l+1){//右边+左边后装不下 
		tr[x].pos=tr[x].r;
		tr[x].res=tr[rs(x)].sum+tr[ls(x)].res-(tr[rs(x)].r-tr[rs(x)].l+1);
	}
	//装得下 
	else{
		if(!tr[rs(x)].sum){//右边没有 
			tr[x].pos=tr[ls(x)].res?tr[rs(x)].l+tr[ls(x)].res-1:tr[ls(x)].pos;//左边有剩下的就右边，否则左边 
		}
		else{//右边有 
			if(tr[rs(x)].sum+tr[ls(x)].res>tr[rs(x)].pos-tr[rs(x)].l+1){//右边超过了右端点 
				tr[x].pos=tr[rs(x)].sum+tr[ls(x)].res+tr[rs(x)].l-1;
			}	
			else{//右边没有超过右端点 
				tr[x].pos=tr[rs(x)].pos;
			}
		}	
		tr[x].res=0;
	}
}
void update(int x,int l,int r,int u,int op){
	if(l==r){
		tr[x].sum+=op;
		if(tr[x].sum) tr[x].res=tr[x].sum-1,tr[x].pos=l; 
		else tr[x].res=0,tr[x].pos=-1;
		return;
	} 
	int mid=l+r>>1;
	if(mid>=u) update(ls(x),l,mid,u,op);
	else update(rs(x),mid+1,r,u,op);
	pushup(x); 
}
map<pii,bool> vis;
signed main(){
	read(n,k,q);
	build(1,1,n*2);
	while(q--){
		int x,y;
		read(x,y);
		int pos=y+abs(x-k);
		if(!vis[mp(x,y)])update(1,1,n*2,pos,1),vis[mp(x,y)]=1;
		else update(1,1,n*2,pos,-1),vis[mp(x,y)]=0;
		write(max(0,tr[1].pos+tr[1].res-n),'\n');
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

首先肯定要考虑暴力怎么做。

我们声称下列结论是对的。令目前棋子集合为 $(x_1,y_1),(x_2,y_2),\cdots,(x_m,y_m)$，则令序列 $a_i = y_i + \left| x_i-k \right|$。将 $a$ 升序排序，则 $\max\{n,\max \limits_{i=1}^m (a_i+m-i)\}-n$ 即为答案。

怎么证明这个结论？注意到每个棋子如果要移动到第 $k$ 行，则移动到这一行的最靠左的列应为第 $y_i + \left| x_i - k \right|$ 列。方案合法当且仅当每个后缀列的点数不超过列数，即二分图匹配中的 Hall 定理。

进一步，考虑怎么优化这个暴力。维护一棵线段树，动态维护 $a_i+m-i$ 即可，只需要区间加与查询全局最值。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <array>
#include <set>
#include <map>
using namespace std;

constexpr int N = 4e5 + 5;

int n, k, m;
set<pair<int, int>> st;

class SegmentTree
{
public:
	struct Node
	{
		int l, r, maxn, tag;
	};
	array<Node, N << 2> tr;
	void pushtag(int u, int v)
	{
		tr[u].tag += v, tr[u].maxn += v;
	}
	void pushdown(int u)
	{
		if (tr[u].tag)
		{
			pushtag(u << 1, tr[u].tag);
			pushtag(u << 1 | 1, tr[u].tag);
			tr[u].tag = 0;
		}
	}
	void pushup(int u)
	{
		tr[u].maxn = max(tr[u << 1].maxn, tr[u << 1 | 1].maxn);
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, (int)-1e9, 0 };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
	}
	void update(int u, int l, int r, int v)
	{
		if (tr[u].l >= l and tr[u].r <= r)
		{
			pushtag(u, v);
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) update(u << 1, l, r, v);
		if (r > mid) update(u << 1 | 1, l, r, v);
		pushup(u);
	}
}sgt;

map<int, int> cnt;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	sgt.build(1, 1, N - 1);
	cin >> n >> k >> m;
	while (m--)
	{
		int x, y;
		cin >> x >> y;
		int nv = y + abs(x - k);
		if (!st.count(make_pair(x, y)))
		{
			sgt.update(1, 1, nv, 1);
			if (++cnt[nv] == 1) sgt.update(1, nv, nv, (int)1e9 + nv);
			st.emplace(x, y);
		}
		else
		{
			st.erase(st.find(make_pair(x, y)));
			sgt.update(1, 1, nv, -1);
			if (--cnt[nv] == 0) sgt.update(1, nv, nv, (int)-1e9 - nv);
		}
		int ret = max(n, sgt.tr[1].maxn - 1);
		cout << ret - n << "\n";
	}
	return 0;
}
```

---

