# 「EVOI-RD1」马戏团

## 题目背景

WuuTue拥有一家马戏团，马戏团会在全国巡演，最近WuuTue的马戏团来到了T市。

## 题目描述

T市有一条专门的演出街，演出街是一条东西走向的笔直街道，街道上从西往东有 $n$ 个舞台，舞台的编号为 $1, 2, \dots, n$。

WuuTue计划在T市的演出街上进行 $M$ 场演出，其中第 $i$ 场演出要占用从 $l_i$ 到 $r_i$ 的连续舞台（包括 $l_i$ 和 $r_i$ ），同时WuuTue知道，第 $i$ 场比赛将会获得 $v_i$ 元的收益。

由于演出街的舞台都是设计给人表演使用的，如果要供动物表演使用的话，需要进行加固，其中加固第 $i$ 个舞台需要花费 $c_i$ 元钱，并且只需要加固一次，可以重复使用。也就是说如果有多个演出都用到了舞台 $i$，那么只需要花费一次加固的费用就可以了。

当然，如果WuuTue发现某场演出可能由于加固费用过高无法盈利，也可能会取消演出。

因为WuuTue太蒻了，所以请帮助WuuTue计算，他最多可以获得多少元钱的收入。

## 说明/提示

**本题采用捆绑测试**

对于 $20\%$ 的数据， $1 \le n , m \le 100$。

另有 $20\%$ 的数据， $v_i = c_i = 1$。

另有 $20\%$ 的数据， $l_i = r_i$。

对于 $100\%$ 的数据， $1 \le n , m \le 10^6 , 0 \le v_i , c_i \le 10^9 , 1 \le l_i \le r_i \le n$。

## 样例 #1

### 输入

```
7 4
3
2
3
2
1
2
3
1 2 5
2 3 5
3 5 3
7 7 5```

### 输出

```
4```

## 样例 #2

### 输入

```
2 1
0
3
1 2 5```

### 输出

```
2```

## 样例 #3

### 输入

```
3 1
10
10
10
1 3 10```

### 输出

```
0```

# 题解

## 作者：灵华 (赞：7)

## P7867 马戏团 - 官方题解

#### 题外话
先说两句，这个题确实是挺那啥，题目本身不难，但是却很容易就把解法想的非常麻烦 ~~（我一开始就想成了图论~~ ，最后在几位爷的指正下修正了做法，其实这题还是比较简单的。

***

先分析一下题意，简化一下就是：

给定一个序列，然后给出几个区间的左右端点和其价值，让你选择其中的几个，总花费是区间的在序列上的 **并集** 之和，总价值是这些 **选择的区间的价值之和** ，最后要求的答案就是总价值减总花费的最大值。

我们设 $f_i$ 表示前 $i$ 个舞台且以第 $i$ 个舞台作为 **最后一个** 区间的 **右端点** 所能产生的最大利益。然后先处理出 $sum(j,i)$ 表示所有区间的左右端点在 $j \sim i$ 这段里面的价值之和 和 $s(j,i)$ 表示第 $j$ 个到第 $i$ 个舞台所要的费用。

显然，我们最后选完区间，会发现我们选择的所有区间一定是几个 **不相交** 的 **连续区间** ，那我们考虑枚举每个点当做某个区间的 **右端点** ，再枚举当前这个区间的左端点，求一个当前这个区间的最大值，最后再把每一个区间的最大值加起来，就是答案了。

$sum(j,i)$ 的处理我们可以用一个vector数组 $vc_i$ 记录以 $i$ 为右端点的区间，然后我们每次枚举 $i$ 的时候就把新的 $i$ 数组内的区间的影响加进去，每一个区间我们会影响的 $sum(j,i)$ 里面的 $j$ 值就只有当
$j \le$ 当前区间的左端点
这个条件满足的时候会有影响，所以我们把 $1$ 到当前这个区间的左端点给区间加上当前区间的价值（ ~~可能会有点绕，~~ 仔细想想就明白了）。

$s(j,i)$ 的处理就用一个前缀和就好了。

由此，我们可以得出这么一个方程式：

$$
f_i = \max ( f_{i-1} , \max ( f_{j-1} + sum(j,i) + s(j,i)  (1 \le j \le i ) ) )
$$

上面那个式子第二个 $max$ 之前的东西都很好理解，说一下第二个 $max$ 里面的东西。

$f_{j-1}$ 表示第 $j$ 个之前最大的利益，所以这后半部分的式子表示有一个从 $j$ 到 $i$ 的区间我们全部选择。

这样子我们就得到了一个时间复杂度是 $O(n^2)$ 级别的解法，但是数据范围是 $10^6$，所以肯定会炸，考虑优化。

我们发现这整个式子其实是由两个 $max$ 组成的，而且我们发现第一个 $max$  可以 $O(1)$ 做，第二个 $max$ 可以用线段树来优化，而且我们加入新的区间时也可以用线段树来区间加，所以总复杂度为 $O(n \log n)$。

具体实现的话，看代码吧。~~码风稍微有点奇怪，希望不影响阅读。~~

## **Code：**

```cpp
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std ;

const long long INF = 0x3f3f3f3f3f3f3f3f ;

struct Node
{
	int l , r ;
	long long v ;
} q[1000005] ;

int n , m ;
long long s[1000005] , f[1000005] , t[4000005] , lz[4000005] ;
vector < int > vc[1000005] ;

void build ( int k , int l , int r )
{
	if ( l == r )
	{
		t [ k ] = s [ l - 1 ] ;
		return ;
	}
	int mid = ( l + r ) >> 1 ;
	build ( k << 1 , l , mid ) ;
	build ( k << 1 | 1 , mid + 1 , r ) ;
	t [ k ] = max ( t [ k << 1 ] , t [ k << 1 | 1 ] ) ;
}

void pushdown ( int k )
{
	if ( lz [ k ] )
	{
		t [ k << 1 ] += lz [ k ] ;
		t [ k << 1 | 1 ] += lz [ k ] ;
		lz [ k << 1 ] += lz [ k ] ;
		lz [ k << 1 | 1 ] += lz [ k ] ;
		lz [ k ] = 0 ;
	}
}

void change ( int k , int l , int r , int x , int y , long long z )
{
	if ( x <= l && r <= y )
	{
		t [ k ] += z ;
		lz [ k ] += z ;
		return ;
	}
	pushdown ( k ) ;
	int mid = ( l + r ) >> 1 ;
	if ( x <= mid )
		change ( k << 1 , l , mid , x , y , z ) ;
	if ( y > mid )
		change ( k << 1 | 1 , mid + 1 , r , x , y , z ) ;
	t [ k ] = max ( t [ k << 1 ] , t [ k << 1 | 1 ] ) ;
}

long long query ( int k , int l , int r , int x , int y )
{
	if ( x <= l && r <= y )
		return t [ k ] ;
	pushdown ( k ) ;
	int mid = ( l + r ) >> 1 ;
	long long res = -INF ;
	if ( x <= mid )
		res = query ( k << 1 , l , mid , x , y ) ;
	if ( y > mid )
		res = max ( res , query ( k << 1 | 1 , mid + 1 , r , x , y ) ) ;
	return res ;
}

int main ( )
{
	cin >> n >> m ;
	for ( int i = 1 ; i <= n ; ++ i )
	{
		long long x ;
		cin >> x ;
		s [ i ] = s [ i - 1 ] + x ;
	}
	for ( int i = 1 ; i <= m ; ++ i )
	{
		cin >> q [ i ] .l >> q [ i ] .r >> q [ i ] .v ;
		vc [ q [ i ] .r ] .push_back ( i ) ;
	}
	f [ 0 ] = 0 ;
	build ( 1 , 1 , n ) ;
	for ( int i = 1 ; i <= n ; ++ i )
	{
		for ( int j = 0 ; j < ( int ) vc [ i ] .size ( ) ; ++ j )
			change ( 1 , 1 , n , 1 , q [ vc [ i ] [ j ] ] .l , q [ vc [ i ] [ j ] ] .v ) ;
		f [ i ] = max ( f [ i - 1 ] , query ( 1 , 1 , n , 1 , i ) - s [ i ] ) ;
		change ( 1 , 1 , n , i + 1 , i + 1 , f [ i ] ) ;
	}
	cout << f [ n ] << endl ;
	return 0 ;
}
```

---

## 作者：do_while_true (赞：6)

设 $f_i$ 为仅考虑前 $i$ 个位置的答案。

$f_i=\max\{f_j-sum(j+1,i)+calc(j+1,i),f_{i-1}\}$

$sum(j+1,i)$ 为 $c$ 区间和，$calc(i,j)$ 为完全在 $[i,j]$ 中的演出收益和。

做一个扫描线（或者叫线段树优化 dp）即可解决。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
#define pb push_back
#define mp std::make_pair
#define fir first
#define sec second
typedef std::pair<int, int> pii;
typedef std::vector<int> veci;
typedef std::vector<pii> vecpii;
typedef long long ll;
ll Abs(ll x) { return x < 0 ? -x : x; }
ll Max(ll x, ll y) { return x > y ? x : y; }
template <typename T>
T& read(T& r) {
    r = 0; bool w = 0; char ch = getchar();
    while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
    while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
    return r = w ? -r : r;
}
const int N = 2000100;
int n, m;
ll c[N], f[N];
#define ls tree[x].lson
#define rs tree[x].rson
#define tl tree[x].l
#define tr tree[x].r
int trnt;
struct SGT {
	int l, r, lson, rson;
	ll mx, tag;
}tree[N << 1];
inline void pushup(int x) { tree[x].mx = Max(tree[ls].mx, tree[rs].mx); }
inline void pushdown(int x) {
	if(tree[x].tag) {
		ll p = tree[x].tag;
		tree[ls].mx += p; tree[rs].mx += p; 
		tree[ls].tag += p; tree[rs].tag += p;
		tree[x].tag = 0;
	}
}
int build(int l, int r) {
	int x = ++trnt;
	tl = l; tr = r;
	if(l == r) return x;
	ls = build(l, (l+r)>>1); rs = build(tree[ls].r+1, r);
	pushup(x); return x;
}
void modify(int x, int l, int r, ll v) {
	if(tl >= l && tr <= r) {
		tree[x].mx += v;
		tree[x].tag += v;
		return ;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if(mid >= l) modify(ls, l, r, v);
	if(mid < r) modify(rs, l, r , v);
	pushup(x);
}
ll query(int x, int l, int r) {
	if(tl >= l && tr <= r) return tree[x].mx;
	int mid = (tree[x].l + tree[x].r) >> 1; ll sumq = 0;
	pushdown(x);
	if(mid >= l) sumq = Max(sumq, query(ls, l, r));
	if(mid < r) sumq = Max(sumq, query(rs, l, r));
	pushup(x);
	return sumq;
}
void Modify(int l, int r, ll v) { modify(1, l+1, r+1, v); }
ll Query(int l, int r) { return query(1, l+1, r+1); }
#undef ls
#undef rs
#undef tl
#undef tr
struct Node {
	int l, r;
	ll v;
}q[N];
bool cmp(Node x, Node y) {
	return x.r < y.r;
}
signed main() {
	read(n); read(m);
	for(int i = 1; i <= n; ++i) read(c[i]);
	build(1, n+1);
	for(int i = 1; i <= m; ++i) read(q[i].l), read(q[i].r), read(q[i].v);
	std::sort(q + 1, q + m + 1, cmp);
	int top = 1;
	for(int i = 1; i <= n; ++i) {
		Modify(0, i-1, -c[i]);
		while(q[top].r == i && top <= m) {
			Modify(0, q[top].l-1, q[top].v);
			++top;
		}
		f[i] = Query(0, i-1);
		f[i] = Max(f[i], f[i-1]);
		Modify(i, i, f[i]);
	}
	printf("%lld\n", f[n]);
	return 0;
}
```

---

## 作者：ask_silently (赞：2)

# 思路分析

设 $dp_{i,j}$ 为选择第 $j$ 个至第 $i$ 个连续舞台的最大收益。分类讨论一下。

- 对于 $j<i$ 的情况，我们考虑 $dp_{i,j}$ 比 $dp_{i-1,j}$ 的答案多了什么。发现其实是多了所有演出中 $r_k=i$ 且 $j \le l_k$ 的收益，但是又多加固了第 $i$ 个舞台，所以要减去 $c_i$。所以得到状态转移方程：

$$dp_{i,j}=dp_{i-1,j}-c_i+\sum^{m}_{k=1}[j \le l_k,r_k=i]v_k,j<i$$

- 对于 $j=i$ 的情况，我们发现上一个状态可以是任意 $dp_{n,m}(1 \le n \le m < i)$，但我们可以发现，我们每次更新答案更新的就是这些东西，所以得到状态转移方程：

$$dp_{i,i}=ans-c_i+\sum^{m}_{k=1}[ l_k=r_k=i]v_k,j=i$$

但我们会发现当我们从状态 $dp_{i-1,j}$ 转移的时候，没有加上 $j \le l_k < i,r_k=i$ 的 $v_k$ 值。有没有感觉这个式子有点熟悉，其实这东西就是 $dp_{i,j}$ 的转移方程，更新答案的时候会一起更新求最大值，所以可以不用管它。

首先先来优化空间，发现 $dp_{i,j}$ 的转移只和 $dp{i-1,j}$ 有关，所以可以滚动数组省去 $i$ 这一维。

那如何优化时间呢？我们可以发现，对于每一个演出，它一定会更新所有满足 $i=r_k,j \le l_k$ 的 $dp_{i,j}$ 即 $dp_j$。所以当我们枚举 $i$ 的时候，可以找到所有 $r_k=i$ 的演出，然后将 $1 \le j \le l_k$ 的 $dp_j$ 都加上一个 $v_k$。

区间加操作，我们可以维护线段树，线段树的每个点表示每个 $dp$ 值，然后此操作就可以变成 $O(\log(n))$ 的时间复杂度了。

那如何找到所有的 $r_k=i$ 的演出呢，我们可以使用双指针的思路来维护，这样均摊时间复杂度加起来是 $O(n+m)$ 的，这样我们的时间复杂度就变为 $O((n+m) \times \log(n))$ 的了。然后就可以愉快的切掉此题。

这，就是传说中的线段树优化 DP。

# AC code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mid (l+r>>1)

const int N=1e6+10;

int n,m,ans;
int cost[N],tr[N<<2],lan[N<<2];

struct node{
	int l,r,v;
}a[N];

inline int read(){
	int t=0,f=1;
	register char c=getchar();
	while(c<'0'||c>'9') f=(c=='-')?(-1):(f),c=getchar();
	while(c>='0'&&c<='9') t=(t<<3)+(t<<1)+(c^48),c=getchar();
	return t*f;
}

bool cmp(node x,node y){return x.r<y.r;}

void pushup(int bian){tr[bian]=max(tr[bian<<1],tr[bian<<1|1]);}

void pushdown(int bian){
	tr[bian<<1]+=lan[bian];
	tr[bian<<1|1]+=lan[bian];
	lan[bian<<1]+=lan[bian];
	lan[bian<<1|1]+=lan[bian];
	lan[bian]=0;
}

void update(int bian,int l,int r,int L,int R,int x){
	if(L<=l&&R>=r){tr[bian]+=x,lan[bian]+=x;return;}
	if(lan[bian]) pushdown(bian);
	if(L<=mid) update(bian<<1,l,mid,L,R,x);
	if(R>mid) update(bian<<1|1,mid+1,r,L,R,x);
	pushup(bian);
}

signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) cost[i]=read();
	for(int i=1;i<=m;i++) a[i].l=read(),a[i].r=read(),a[i].v=read();
	sort(a+1,a+1+m,cmp);
	for(int i=1,j=1;i<=n;i++){
		update(1,1,n,1,i,-cost[i]);
		update(1,1,n,i,i,ans);
		while(a[j].r==i&&j<=m) update(1,1,n,1,a[j].l,a[j].v),j++;
		ans=max(ans,tr[1]); //此时的 tr[1] 就是所有 dp 的最大值 
	}
	cout<<ans;
	return 0;
}

```

---

