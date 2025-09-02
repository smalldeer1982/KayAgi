# The Tree

## 题目描述

Abendsen 给 Juliana 分配了一个任务。在这个任务中，Juliana 有一棵包含 $n$ 个结点的有根树，结点编号为 $1$ 的结点是树的根。每个结点可以是黑色或白色。最开始，所有结点都是白色的。Juliana 需要处理 $q$ 个操作。每个操作有三种类型：

1. 如果结点 $v$ 是白色的，将其标记为黑色；否则，对 $v$ 的所有直接儿子执行此操作。
2. 将以 $v$ 为根的子树中的所有结点（包括 $v$ 本身）都标记为白色。
3. 查询第 $i$ 个结点的颜色。

如下图所示，是操作 “1 1” 的示例（对应第一个样例测试）。结点 $1$ 和 $2$ 已经是黑色，因此该操作会递归作用于它们的儿子。你能帮助 Juliana 处理所有这些操作吗？

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017G/e1bfda7a1b03fca247e99f6625980764a1349b36.png)

## 说明/提示

第一个样例如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017G/cc16931f19a766fcc45c465ac34ccd83cbd711fb.png)

第二个样例如图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017G/f4ed5ffcf5834fcc15d2af9cfb118e0f9239a3e6.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8 10
1 2 1 2 5 4 5
1 2
3 2
3 1
1 1
1 1
3 5
3 7
3 4
2 2
3 5
```

### 输出

```
black
white
black
white
black
white
```

## 样例 #2

### 输入

```
8 11
1 1 2 3 3 6 6
1 1
1 1
1 3
3 2
3 4
3 6
3 7
2 3
1 6
3 7
3 6
```

### 输出

```
black
white
black
white
white
black
```

# 题解

## 作者：皎月半洒花 (赞：27)

这是真神题。

首先观察发现，操作的复杂度向修改倾斜，即询问复杂度比较低，可以考虑询问的时候搞点事情。

考虑 $(1)$ 操作的本质。因为要向询问倾斜，所以考虑如果某个点 $z$ 会被 `1 x` 影响到 ，那么必然有 $x\sim z$ 这条路径上除了 $x$ 之外的所有点都已经被染黑了。

考虑忽略 $(2)$ 操作时，如何通过维护权值实现这个事情。一开始将全部的点权设为 $0$，每次 $(1)$ 操作就是对该点进行单点 $+1$ 。这样询问就可以考虑询问 $root\to x$ 这条路径上，是否存在一个后缀 $(s,x)$ 的权和等于 $(s,x)$ 的长度。这样直接做本质上是一个树链上的线段树二分，但其实可以用一个比较传统的技巧优化这个过程，即差分。考虑把每个点的初始点权设为 $-1$ ，这样就是询问是否存在一个后缀，其和 $\geqslant 0$ 。这个可以通过维护链上的最大后缀和来做，写起来简单一些。

然后考虑加上 $(2)$ 操作后如何快速维护。发现 $(2)$ 操作的本质是让整棵子树的点权均变为 $-1$ 。但这还不够，因为 $(2)$ 本质上是强制让某个点 $x$ 变成白色，而上面那个做法本质上是对修改离线，最后再分别确定每个修改对答案的贡献。不过也有比较简单的解决方式，即让 `2 x` 中的 $x$ 单点减一个权值 $v$ ，使得 $root\to x$ 上的最大后缀和也为 $-1$ 。不难发现 $v=qry(x)+1$ 。

于是最后就可以用 $n\log ^2n $ 的复杂度解决这个问题了。

```cpp
#include <cstdio>

#include <vector>

#include <cstring>

#define p_b push_back

using std :: max ;
using std :: min ;
using std :: vector ;

const int N = 300010 ;

int ans ;
int cnt ;
int n, q ;
int sz[N] ;
int fa[N] ;
int _id[N] ;
int dfn[N] ;
int son[N] ;
int dep[N] ;
int top[N] ;

vector <int> E[N] ;

void dfs1(int x, int da){
    dep[x] = dep[da] + 1 ;
    sz[x] = 1, fa[x] = da ;
    for (auto y : E[x]){
        if (y == da) continue ;
        dfs1(y, x) ; sz[x] += sz[y] ;
        if (sz[y] > sz[son[x]]) son[x] = y ;
    }
}
void dfs2(int x, int tp){
    top[x] = tp ; ++ cnt ;
    _id[dfn[x] = cnt] = x ;
    if (son[x])
        dfs2(son[x], tp) ;
    for (auto y : E[x])
        if (y != fa[x] && y != son[x]) dfs2(y, y) ;
}

int seg[N * 3] ;
int val[N * 3] ;
int tag[N * 3] ;

#define lc (rt << 1)
#define rc (rt << 1 | 1)

void _up(int rt){
    seg[rt] = seg[lc] + seg[rc] ;
    val[rt] = max(val[rc], val[lc] + seg[rc]) ;
}
void _down(int rt, int l, int r){
    if (!tag[rt]) return ;
    int mid = (l + r) >> 1 ;
    seg[rc] =  - (r - mid) ;
    seg[lc] =  - (mid - l + 1) ;
    val[lc] = -1, val[rc] = -1 ;
    tag[rc] = tag[lc] = 1, tag[rt] = 0 ;
}
void build(int rt, int l, int r){
    if (l == r)
        return void(seg[rt] = val[rt] = -1) ;
    int mid = (l + r) >> 1 ;
    build(rc, mid + 1, r) ;
    build(lc, l, mid) ; _up(rt) ;
}
void upd(int rt, int l, int r, int p, int v){
    if (l == r){
        seg[rt] += v ;
        val[rt] += v ;
        return void() ;
    }
    _down(rt, l, r) ;
    int mid = (l + r) >> 1 ;
    if (p <= mid) upd(lc, l, mid, p, v) ;
    else upd(rc, mid + 1, r, p, v) ;
    _up(rt) ;
}
void cov(int rt, int l, int r, int cl, int cr){
    if (cl <= l && r <= cr){
        seg[rt] = - (r - l + 1) ;
        val[rt] = -1 ; return void(tag[rt] = 1) ;
    }
    int mid = (l + r) >> 1 ; _down(rt, l, r) ;
    if (cr > mid) cov(rc, mid + 1, r, cl, cr) ;
    if (cl <= mid) cov(lc, l, mid, cl, cr) ; _up(rt) ;
}
int sum(int rt, int l, int r, int ql, int qr){
    if (ql <= l && r <= qr) return seg[rt] ;
    int mid = (l + r) >> 1, ret = 0 ; _down(rt, l, r) ;
    if (ql <= mid) ret += sum(lc, l, mid, ql, qr) ;
    if (qr > mid) ret += sum(rc, mid + 1, r, ql, qr) ;
    return ret ;
}
int qry(int rt, int l, int r, int ql, int qr){
     _down(rt, l, r) ;
    if (ql <= l && r <= qr) return val[rt] ;
    int mid = (l + r) >> 1, ret = - n ; _down(rt, l, r) ;
    if (ql <= mid) ret = max(ret, qry(lc, l, mid, ql, qr)) ;
    if (qr > mid) ret = max(ret + sum(rc, mid + 1, r, ql, qr), qry(rc, mid + 1, r, ql, qr)) ;
    return ret ;
}
int Q(int x){
    int ret, v = 0 ;
    ret = -(n + 1) ;
    while (top[x] > 1){
        ret = max(ret, v + qry(1, 1, n, dfn[top[x]], dfn[x])) ;
        v += sum(1, 1, n, dfn[top[x]], dfn[x]) ; x = fa[top[x]] ;
    }
//    printf("%d\n", qry(1, 1, n, dfn[top[x]], dfn[x])) ;
    ret = max(ret, v + qry(1, 1, n, 1, dfn[x])) ; return ret ;
}
int main(){
    scanf("%d%d", &n, &q) ; int x, z ;
    for (int y = 2 ; y <= n ; ++ y)
        scanf("%d", &x), E[x].p_b(y), E[y].p_b(x) ;
    dfs1(1, 0) ; dfs2(1, 1) ; build(1, 1, n) ;
//    for (int i = 1 ; i <= n ; ++ i) printf("%d%c", top[i], " \n"[i == n]) ;
//        printf("%d %d\n", i, sz[i]) ;
    while (q --){
        scanf("%d%d", &z, &x) ;
        if (z == 1) upd(1, 1, n, dfn[x], 1) ;
        else if (z == 2){
            cov(1, 1, n, dfn[x], dfn[x] + sz[x] - 1) ;
            upd(1, 1, n, dfn[x], - Q(x) - 1) ;
        }
        else if (z == 3){
//            printf("%d\n", Q(x)) ;
            ans = (bool)(Q(x) >= 0) ;
            puts(ans ? "black" : "white") ;
        }
    }
    return 0 ;
}
```



---

## 作者：I_am_Accepted (赞：20)

我们称 1 操作为「晕开」，2 操作为「清空」。

发现朴素晕开的时间复杂度我们受不了 qwq，尝试用树剖方式与询问摊一下。

若在一个位置晕开一次黑色，我们就单点加 $1$，若所有的初始点权均为 $-1$，则单点询问 $x$ 时相当于问：

从根到 $x$ 路径上的点权的最大后缀和（不可空）是否 $\ge 0$。

原因是每个点要消耗一个单位，所以初始值为 $-1$，而每次晕开相当于向下多扩展 $1$。

清空 $x$ 如何？首先我们要让 $x$ 子树内的点权均清空为 $-1$，然后要阻断此时从上层来的墨量，所以用 $x$ 「吸收」，即 $x$ 点权再减 $x$ 处的询问值再 $-1$。

询问则树剖跳链，线段树维护区间和，区间最大后缀和即可。

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define debug(...) cerr<<"#"<<__LINE__<<": "<<__VA_ARGS__<<endl
#define ll long long
const ll mod=1;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
#define int ll
#define N 100005
struct node{
	int sum,ans;
	node(int s=0,int a=0){ sum=s,ans=a; }//ans(suf) can't be empty
	friend node operator+(node x,node y){ return node(x.sum+y.sum,max(y.ans,x.ans+y.sum)); }
}t[N<<2];
bool lz[N<<2];
vector<int> e[N];
int n,q,sz[N],wson[N],dfn[N],top[N],f[N],tim=0;
void dfs(int rt,int fa){
	sz[rt]=1;
	f[rt]=fa;
	for(int i:e[rt]) if(i!=fa){
		dfs(i,rt);
		sz[rt]+=sz[i];
		if(sz[i]>sz[wson[rt]]) wson[rt]=i;
	}
}
void dfs2(int rt,int tp){
	top[rt]=tp;
	dfn[rt]=++tim;
	if(wson[rt]) dfs2(wson[rt],tp);
	for(int i:e[rt]) if(i!=f[rt] && i!=wson[rt]){
		dfs2(i,i);
	}
}
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid ((l+r)>>1)
void build(int rt,int l,int r){
	lz[rt]=false;
	if(l==r){
		t[rt]=node(-1,-1);
		return ;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	t[rt]=t[ls]+t[rs];
}
void tag(int rt,int l,int r){
	lz[rt]=true;
	t[rt]=node(-(r-l+1),-1);
}
void pd(int rt,int l,int r){
	if(lz[rt]){
		lz[rt]=false;
		tag(ls,l,mid);
		tag(rs,mid+1,r);
	}
}
void add(int rt,int l,int r,int id,int val){
	if(l==r){
		t[rt].sum+=val;
		t[rt].ans+=val;
		return ;
	}
	pd(rt,l,r);
	if(id<=mid) add(ls,l,mid,id,val);
	else add(rs,mid+1,r,id,val);
	t[rt]=t[ls]+t[rs];
}
void cle(int rt,int l,int r,int x,int y){//clean to val -1
	if(x<=l && r<=y){
		tag(rt,l,r);
		return ;
	}
	pd(rt,l,r);
	if(x<=mid) cle(ls,l,mid,x,y);
	if(y>mid) cle(rs,mid+1,r,x,y);
	t[rt]=t[ls]+t[rs];
}
node query(int rt,int l,int r,int x,int y){
	if(l==x && r==y) return t[rt];
	pd(rt,l,r);
	if(y<=mid) return query(ls,l,mid,x,y);
	else if(x>mid) return query(rs,mid+1,r,x,y);
	else return query(ls,l,mid,x,mid)+query(rs,mid+1,r,mid+1,y);
}
int Que(int x){
	node res=query(1,1,n,dfn[top[x]],dfn[x]);
	x=f[top[x]];
	while(x){
		res=query(1,1,n,dfn[top[x]],dfn[x])+res;
		x=f[top[x]];
	}
	return res.ans;
}
signed main(){ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n>>q;
	int opt,x;
	For(i,2,n){
		cin>>x;
		e[x].pb(i);
		e[i].pb(x);
	}
	dfs(1,0);
	dfs2(1,1);
	build(1,1,n);
	For(i,1,q){
		cin>>opt>>x;
		if(opt==1){
			add(1,1,n,dfn[x],1);
		}else if(opt==2){
			cle(1,1,n,dfn[x],dfn[x]+sz[x]-1);
			add(1,1,n,dfn[x],-1-Que(x));//make this node's max suf=-1
		}else{
			cout<<(Que(x)>=0?"black":"white")<<endl;
		}
	}
return 0;}
```

---

## 作者：yijan (赞：11)

怎么都没人写好写又好懂的官方题解的做法？

考虑对询问分块。

设块大小为 $s$ ，那么每一个询问块用到过的点的数量是 $O(s)$ 的。

考虑把询问的这 $s$ 个点拿出来建虚树（这里可以 $O(n)$ 建虚树的）。我们对于一个虚树上的边，存一下这边在原树上的点的个数，白色点的个数。

然后考虑第一个操作，我们可以直接在新树上模拟进行操作。具体来说，修改一个点，如果这个点是白色直接修改，否则查一下当前操作这个点的数量是否足以递归进一个子树。递归操作即可。说白了，对关键点修改直接改，对非关键点延到块处理完了再改。复杂度是 $O(s)$。

考虑第二个操作，暴力修改子树，把每条边上白色点的个数变成原树上点的个数即可。复杂度 $O(s)$。

考虑询问，直接输出这个点的颜色即可。复杂度 $O(1)$。

考虑对一个块操作完了，我们遍历这个树，对于每个点都可以通过类似建立虚树时的办法把每个未被询问的点的颜色还原。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 200006
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
typedef long long ll;
int n , q;
int A[MAXN] , fa[MAXN];

vi G[MAXN];
int head[MAXN] , to[MAXN << 1] , nex[MAXN << 1] , wto[MAXN << 1] , dto[MAXN << 1] , ecn;
void ade( int u , int v , int w , int ww ) {
	to[++ ecn] = v , nex[ecn] = head[u] , head[u] = ecn , wto[ecn] = w , dto[ecn] = ww;
} 

int mark[MAXN] , black[MAXN];
void afs( int u , int f , int w , int d ) {
	if( mark[u] ) {
		if( f != -1 ) ade( f , u , w , d );
		for( int& v : G[u] ) afs( v , u , 0 , 0 );
	} else {
		if( !black[u] ) ++ w;
		for( int& v : G[u] ) afs( v , f , w , d + 1 );
	}
}

int pu[MAXN];
void rever( int u ) {
	if( !black[u] ) return void( black[u] = 1 );
	++ pu[u];
	for( int i = head[u] ; i ; i = nex[i] ) if( wto[i] + 1 <= pu[u] )
		rever( to[i] );
}

int cov[MAXN]; // the whole subtree is white
void cover( int u ) {
	black[u] = pu[u] = 0;
	cov[u] = 1;
	for( int i = head[u] ; i ; i = nex[i] ) wto[i] = dto[i] , cover( to[i] );
}

int re[MAXN];
void cfs( int u , int p , int cl ) {
	if( mark[u] ) 
		p = pu[u] , cl |= cov[u];
	else {
		black[u] = re[u];
		if( cl ) black[u] = 0;
		if( !black[u] && p ) black[u] = 1 , -- p;
	}
	for( int v : G[u] ) cfs( v , p , cl );
}

int op[MAXN] , pt[MAXN];

void solve() {
	cin >> n >> q;
	int blo = sqrt( q );
	int u;
	rep( i , 2 , n ) scanf("%d",&u) , fa[i] = u , G[u].pb( i );
	rep( i , 1 , q ) scanf("%d%d",op + i,pt + i);
	int s = ( q - 1 ) / blo + 1;
	rep( i , 1 , s ) {
		int l = ( i - 1 ) * blo + 1 , r = min( q , i * blo );
		rep( i , 1 , n ) re[i] = black[i] , mark[i] = cov[i] = pu[i] = head[i] = 0;
		rep( i , l , r ) mark[pt[i]] = 1;
		afs( 1 , -1 , 0 , 0 );
		rep( i , l , r ) {
			if( op[i] == 1 ) rever( pt[i] );
			else if( op[i] == 2 ) cover( pt[i] );
			else puts( black[pt[i]] ? "black" : "white" );
		}
		cfs( 1 , 0 , 0 );
	}
}

signed main() {
//    int T;cin >> T;while( T-- ) solve();
    solve();
}


```



---

## 作者：Alex_Wei (赞：8)

> [CF1017G The Tree](https://www.luogu.com.cn/problem/CF1017G)

先考虑树是一条链的情况。换言之，考虑 $x$ 及其祖先 $a$。对 $a$ 进行一次操作一，对 $x$ 的影响为找到从根到 $x$ 这条链上从 $a$ 开始第一个白点并将其染黑。对 $a$ 进行一次操作二，对 $x$ 的影响为将 $a$ 到 $x$ 的所有点染黑。

我们必须找到在执行操作一不依赖于找到第一个白点的算法，否则算法无法扩展到树上。换种角度考虑，存在 $x$ 的祖先 $b$ 使得路径 $b \to x$ 上所有节点被执行操作一的次数之和不小于路径长度，这是 $x$ 为黑点的充要条件。因此，考虑线段树维护每个节点被执行操作一的次数 **减 $1$**，查询时求根到 $x$ 路径上后缀最大值是否 $\geq 0$。

对于二操作呢？首先 $x$ 子树内的所有操作一全部作废。问题在于这样做了之后并不能保证 $x$ 子树内全部变成白点。但我们发现 $x$ 子树内的黑点一定是从 $dep_x$ 到某个深度 $d$ 的所有节点，因为子树内不存在操作一，黑点只能从 $x$ 的祖先贡献。这启发我们进行 $d - dep_x + 1$ 次 “负操作一”，也就是把黑节点吸回去。

具体地，求出根到 $x$ 路径后缀最大值 $v$，若 $v \geq 0$ 说明节点 $v$ 为黑色，需要执行 $v + 1$ 次负操作 $1$，即将 $x$ 被执行操作一的次数减去 $v + 1$。

线段树维护区间赋值，单点修改，区间查询后缀最大值。套上树剖，时间复杂度 $\mathcal{O}(n + q\log ^ 2 n)$。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
inline int read() {
  int x = 0;
  char s = getchar();
  while(!isdigit(s)) s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return x;
}
inline void print(int x) {
  if(x < 0) return putchar('-'), print(-x);
  if(x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
bool Mbe;
constexpr int N = 1e5 + 5;
bool laz[N << 2];
int len[N << 2];
struct dat {
  int sum, suf;
  dat operator + (const dat &x) {return {sum + x.sum, max(x.suf, suf + x.sum)};}
} val[N << 2];
void tag(int x) {val[x] = {-len[x], -1}, laz[x] = 1;}
void down(int x) {if(laz[x]) tag(x << 1), tag(x << 1 | 1), laz[x] = 0;}
void build(int l, int r, int x) {
  len[x] = r - l + 1, val[x] = {-len[x], -1};
  if(l == r) return;
  int m = l + r >> 1;
  build(l, m, x << 1), build(m + 1, r, x << 1 | 1);
}
void modify(int l, int r, int ql, int qr, int x) {
  if(ql <= l && r <= qr) return tag(x);
  int m = l + r >> 1;
  down(x);
  if(ql <= m) modify(l, m, ql, qr, x << 1);
  if(m < qr) modify(m + 1, r, ql, qr, x << 1 | 1);
  val[x] = val[x << 1] + val[x << 1 | 1];
}
void toggle(int l, int r, int p, int x, int v, int type) {
  if(l == r) return val[x].sum = val[x].suf = type ? v : val[x].sum + v, void();
  int m = l + r >> 1;
  down(x);
  if(p <= m) toggle(l, m, p, x << 1, v, type);
  else toggle(m + 1, r, p, x << 1 | 1, v, type);
  val[x] = val[x << 1] + val[x << 1 | 1];
}
dat query(int l, int r, int ql, int qr, int x) {
  if(ql <= l && r <= qr) return val[x];
  int m = l + r >> 1;
  dat ans = {0, -1};
  down(x);
  if(m < qr) ans = query(m + 1, r, ql, qr, x << 1 | 1) + ans;
  if(ql <= m) ans = query(l, m, ql, qr, x << 1) + ans;
  return ans;
}
int n, q;
vector<int> e[N];
int sz[N], dep[N], fa[N], son[N];
int dn, dfn[N], top[N];
void dfs1(int id) {
  sz[id] = 1, dep[id] = fa[id] + 1;
  for(int it : e[id]) {
    dfs1(it), sz[id] += sz[it];
    if(sz[it] > sz[son[id]]) son[id] = it;
  }
}
void dfs2(int id, int tp) {
  dfn[id] = ++dn, top[id] = tp;
  if(son[id]) dfs2(son[id], tp);
  for(int it : e[id]) if(it != son[id]) dfs2(it, it);
}
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0);
  cin >> n >> q;
  for(int i = 2; i <= n; i++) cin >> fa[i], e[fa[i]].push_back(i);
  dfs1(1), dfs2(1, 1);
  build(1, n, 1);
  for(int i = 1; i <= q; i++) {
    int op, x;
    cin >> op >> x;
    if(op == 1) toggle(1, n, dfn[x], 1, 1, 0);
    if(op == 2) {
      modify(1, n, dfn[x], dfn[x] + sz[x] - 1, 1);
      dat cur = {0, -1};
      int u = fa[x];
      while(u) cur = query(1, n, dfn[top[u]], dfn[u], 1) + cur, u = fa[top[u]];
      if(cur.suf >= 0) toggle(1, n, dfn[x], 1, -cur.suf - 1, 1);
    }
    if(op == 3) {
      dat cur = {0, -1};
      while(x && cur.suf < 0) cur = query(1, n, dfn[top[x]], dfn[x], 1) + cur, x = fa[top[x]];
      if(cur.suf >= 0) puts("black");
      else puts("white");
    }
  }
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/9/8
author: Alex_Wei
start coding at 13:00
finish debugging at 13:45
*/
```

---

## 作者：feecle6418 (赞：4)

设 $f(x)$ 表示 $x$ 到根这段里面有几个白点。

- 操作 1：将某个 dfs 序区间内 $f(l)\sim f(r)$ 中的每个数 $x$ 改为 $\max(x-1,A)$（$A=f(fa)$）。
- 操作 2：先查询 $f(fa)$，将区间内第 $i$ 个数改为 $d_i+B$。$d$ 表示深度。
- 操作 3：查询 $f(x),f(fa)$。

这东西显然可以分块维护，打两个标记

- 块内是否全部改为了 $d$ 数组加上某个值
- 现在块内的所有 $x\to \max(x+P,Q)$ 了（如果有第一个标记，$x$ 就等于 $d_i$，否则 $x$ 就等于块上一次 pushdown 后的值）

查询时把标记 pushdown。显然复杂度是 $O(n\sqrt n)$。

---

## 作者：9AC8E2 (赞：4)

并不明白大家为什么写得这么短

---

## 不考虑全部染白的情况



显然,操作之间是没有顺序的.记录每个点染色的次数 $wal$,以及到根的染色次数 $depth$.如果 $a$ 最后为黑色,那么其充要条件为存在一个 $b$,满足 $depth_a-depth_b+wal_b\geq deep_a-deep_b+1$

移项得 $depth_b-deep_b-w_b\leq depth_a-deep_a-1$

查询的时候查询一下根到自己最大值即可,修改的时候子树加即可



## 考虑全部染白的情况

首先当然需要清空子树内所有点的染色次数,并将维护 $depth$.如果子树的根节点 $y$ 此时为白色,那么当然无事发生.但是,如果 $y$ 此时为黑色,那么说明 $y$ 的祖先会对 $y$ 及其子树内的点产生影响.

考虑如果 $y$ 不会被影响,那么其子树内的其余所有点都不会被影响.那就给 $wal_y$ (以及 $depth_y$ )加上一个最小的权值 $c$ ,满足 $\min_{b\text{为}y\text{的祖先}}\{depth_b-deep_b-w_b\}>depth_y-deep_y-1+c$

移项得 $c=\min_{b\text{为}y\text{的祖先}}\{depth_b-deep_b-wal_b\}-depth_y+deep_y$

那么,我们在树剖之后需要一颗线段树来维护一下操作

- 区间加 $depth$
- 区间赋值 $depth$
- 单点修改 $wal$
- 区间清零 $wal$
- 单点加 $wal$
- 区间查询 $depth-deep-wal$ 最小值
- 单点查询 $depth$

## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define Ri register
template<typename T>inline T read(Ri T&t)
{Ri T f=1;Ri char ch=getchar();t=0;
while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
while(ch>='0'&&ch<='9')t=t*10+ch-'0',ch=getchar();t*=f;return t;}
template<typename T,typename...Args>
inline void read(T&t,Args&...args)
{read(t);read(args...);}
const long long p=998244353;
inline long long power(Ri long long x,Ri long long k=p-2)
{Ri long long re=1;for(;k;k>>=1,x=x*x%p)if(k&1)re=re*x%p;return re;}
int n,Q;
int head[100005],ne[200005],to[200005],total=1;
inline void add(int a,int b)
{
	total++;
	to[total]=b;
	ne[total]=head[a];
	head[a]=total;
}
int deep[100005];
int size[100005];
int fa[100005],son[100005];
int id[100005],id_top;
int fid[100005];
int top[100005];
void dfs1(int now)
{
	size[now]=1;
	deep[now]=deep[fa[now]]+1;
	for(int i=head[now];i;i=ne[i])
		if(to[i]!=fa[now])
		{
			fa[to[i]]=now;
			dfs1(to[i]);
			size[now]+=size[to[i]];
			if(size[to[i]]>size[son[now]])son[now]=to[i];
		}
}
void dfs2(int now,int topf)
{
	top[now]=topf;
	id[now]=++id_top;
	fid[id_top]=now;
	if(son[now])dfs2(son[now],topf);
	for(int i=head[now];i;i=ne[i])
		if(to[i]!=fa[now]&&to[i]!=son[now])
			dfs2(to[i],to[i]);
}
struct SGT
{
	int lcs,rcs;
	int Depth,Wal;
	int value;//deep+Depth-Wal的最大值 
	int Add_lazy,Rev_lazy;//兹磁区间加depth,区间赋值depth
	bool Cle_lazy;//兹磁区间清零wal,单点修改wal,单点加wal 
	int min_Depth_Deep;//用来在区间清零Wal之后维护value \min\{depth+deep\}
	int min_Depth_Wal;//用来在区间赋值depth之后维护value \min\{deep-wal\}  
	int min_Deep;//用来在区间清零Wal和区间赋值depth之后维护 mDD,mDW \min\{deep\}
	 
	#define mid ((l+r)>>1)
	#define lc v[p].lcs
	#define rc v[p].rcs
	#define depth v[p].Depth
	#define wal v[p].Wal
	#define val v[p].value
	#define a_laz v[p].Add_lazy
	#define r_laz v[p].Rev_lazy
	#define c_laz v[p].Cle_lazy
	#define mDD v[p].min_Depth_Deep
	#define mDW v[p].min_Depth_Wal
	#define mD v[p].min_Deep
}v[200005];
int tot;
void build(int l,int r,int & p)
{
	p=++tot;
	r_laz=-1;
	if(l==r)return mD=mDD=mDW=val=-deep[fid[l]],void();
	build(l,mid,lc);
	build(mid+1,r,rc);
	mD=min(v[lc].min_Deep,v[rc].min_Deep);
	mDD=min(v[lc].min_Depth_Deep,v[rc].min_Depth_Deep);
	mDW=min(v[lc].min_Depth_Wal,v[rc].min_Depth_Wal);
	val=min(v[lc].value,v[rc].value);
	if(val==v[lc].value)wal=v[lc].Wal,depth=v[lc].Depth;
	if(val==v[rc].value)wal=v[rc].Wal,depth=v[rc].Depth;
}
void push_down(int l,int r,int p)//注意下放顺序和标记清空 
{
	if(r_laz!=-1)
	{
		v[lc].Rev_lazy=r_laz;
		v[rc].Rev_lazy=r_laz;
		v[lc].Add_lazy=0;
		v[rc].Add_lazy=0;
		v[lc].min_Depth_Deep=v[lc].min_Deep+r_laz;
		v[rc].min_Depth_Deep=v[rc].min_Deep+r_laz;
		v[lc].value=v[lc].min_Depth_Wal+r_laz;
		v[rc].value=v[rc].min_Depth_Wal+r_laz;
		v[lc].Depth=r_laz;
		v[rc].Depth=r_laz;
		r_laz=-1;
	}
	if(a_laz)
	{
		v[lc].Add_lazy+=a_laz;
		v[rc].Add_lazy+=a_laz;
		v[lc].value+=a_laz;
		v[rc].value+=a_laz;
		v[lc].Depth+=a_laz;
		v[rc].Depth+=a_laz;
		v[lc].min_Depth_Deep+=a_laz;
		v[rc].min_Depth_Deep+=a_laz;
		a_laz=0; 
	}
	if(c_laz)
	{
		v[lc].Cle_lazy=c_laz;
		v[rc].Cle_lazy=c_laz;
		v[lc].value=v[lc].min_Depth_Deep;
		v[rc].value=v[rc].min_Depth_Deep;
		v[lc].Wal=0;
		v[rc].Wal=0;
		v[lc].min_Depth_Wal=v[lc].min_Deep;
		v[rc].min_Depth_Wal=v[rc].min_Deep;
		c_laz=0;
	}
}
void push_up(int l,int r,int p)
{
	val=min(v[lc].value,v[rc].value);
	if(val==v[lc].value)wal=v[lc].Wal,depth=v[lc].Depth;
	if(val==v[rc].value)wal=v[rc].Wal,depth=v[rc].Depth;
	mDD=min(v[lc].min_Depth_Deep,v[rc].min_Depth_Deep);
	mDW=min(v[lc].min_Depth_Wal,v[rc].min_Depth_Wal);
}
void revise1(int l,int r,int p,int nl,int nr,int vals)//区间加depth
{
	if(nl<=l&&r<=nr)
	{
		val+=vals;
		depth+=vals;
		mDD+=vals;
		a_laz+=vals;
		return;
	}
	push_down(l,r,p);
	if(nl<=mid)revise1(l,mid,lc,nl,nr,vals);
	if(mid+1<=nr)revise1(mid+1,r,rc,nl,nr,vals);
	push_up(l,r,p);
}
void revise2(int l,int r,int p,int nl,int nr,int vals)//区间赋值depth
{
	if(nl<=l&&r<=nr)
	{
		val=mDW+vals;
		depth=vals;
		mDD=mD+vals;
		a_laz=0;
		r_laz=vals;
		return;
	}
	push_down(l,r,p);
	if(nl<=mid)revise2(l,mid,lc,nl,nr,vals);
	if(mid+1<=nr)revise2(mid+1,r,rc,nl,nr,vals);
	push_up(l,r,p);
}
void revise3(int l,int r,int p,int pos,int vals)//单点修改wal
{
	if(l==r&&l==pos)
	{
		wal=vals;
		val=mDD+wal;
		mDW=mD+vals;
		return;
	}
	push_down(l,r,p);
	if(pos<=mid)revise3(l,mid,lc,pos,vals);
	if(mid+1<=pos)revise3(mid+1,r,rc,pos,vals);
	push_up(l,r,p);
}
void revise4(int l,int r,int p,int nl,int nr)//区间清零wal
{
	if(nl<=l&&r<=nr)
	{
		wal=0;
		val=mDD;
		mDW=mD;
		c_laz=1;
		return;
	}
	push_down(l,r,p);
	if(nl<=mid)revise4(l,mid,lc,nl,nr);
	if(mid+1<=nr)revise4(mid+1,r,rc,nl,nr);
	push_up(l,r,p);
}
void revise5(int l,int r,int p,int pos,int vals)//单点加wal
{
	if(l==r&&l==pos)
	{
		wal+=vals;
		val-=vals;
		mDW-=vals;
		return;
	}
	push_down(l,r,p);
	if(pos<=mid)revise5(l,mid,lc,pos,vals);
	if(mid+1<=pos)revise5(mid+1,r,rc,pos,vals);
	push_up(l,r,p);
}
int enquire(int l,int r,int p,int nl,int nr)//区间查询value最小值
{
	if(nl<=l&&r<=nr)return val;
	push_down(l,r,p);
	int re=1e9;
	if(nl<=mid)re=min(re,enquire(l,mid,lc,nl,nr));
	if(mid+1<=nr)re=min(re,enquire(mid+1,r,rc,nl,nr));
	return re;
}
int enquire(int l,int r,int p,int pos)//单点查询depth
{
	if(l==r&&l==pos)return depth;
	push_down(l,r,p);
	if(pos<=mid)return enquire(l,mid,lc,pos);
	if(mid+1<=pos)return enquire(mid+1,r,rc,pos);
}
int enquire(int x)//查询到根的value最大值 
{
	int re=1e9;
	while(x)
	{
		re=min(re,enquire(1,n,1,id[top[x]],id[x]));
		x=fa[top[x]];
	}
	return re;
}

int main()
{
	read(n,Q);
	for(int i=2,x;i<=n;i++)
		read(x),
		add(x,i),
		add(i,x);
	dfs1(1);dfs2(1,1);
	int root;build(1,n,root);
	while(Q--)
	{
		int opt,x;read(opt,x);
		if(opt==1)
		{
			revise1(1,n,1,id[x],id[x]+size[x]-1,1);
			revise5(1,n,1,id[x],1);
		}
		if(opt==2)
		{
			revise4(1,n,1,id[x],id[x]+size[x]-1);
			int fmax;
			if(fa[x])fmax=enquire(1,n,1,id[fa[x]]);
			else fmax=0;
			revise2(1,n,1,id[x],id[x]+size[x]-1,fmax);
			int mx=enquire(x);
			int mi=enquire(1,n,1,id[x]);
			int c=mx-mi+deep[x];
			if(c<0)
			{
				revise5(1,n,1,id[x],c);
				revise1(1,n,1,id[x],id[x],c);
			}
			int X=enquire(1,n,1,id[x]);
			revise2(1,n,1,id[x],id[x]+size[x]-1,X); 
		}
		if(opt==3)
		{
			int mx=enquire(x);
			int mi=enquire(1,n,1,id[x]);
			if(mx<=mi-deep[x]-1)printf("black\n");
			else printf("white\n");
		}
	}
	return 0;
}
```

---

## 作者：ppp204 (赞：3)

[**Linker**](https://www.luogu.org/problem/CF1017G)

> 做法：树链剖分+线段树

首先$O(n^2)$的暴力还是挺好想的，就不多阐述了。

然后看没有2操作的该怎么写。

当没有2操作的时候，我们可以通过一种特殊的形式来记录点的染色：通过给这个点加权值。

假设x是y的祖先，若x可以影响到y的话，不难发现，需要满足的性质就是 $x\to y\ \text{这一段路上的总权值}>=dep[x]-dep[y]+1$

记录这一段路上的总权值为$dis$，移项得到 $dis+dep[x]>=dep[y]+1$

利用线段树维护$dis+dep[x]$,然后对于向上跳的过程直接树链剖分向上跳。

也就是说通过树链剖分+线段树就能写出来。这里代码就不放出来了。

再看如果有了2操作我们该如何写。

首先把这一整课子树清空是肯定要的。

然后就看如果祖先的$dis$的影响到了下面的节点该如何操作。

再来看看刚刚的式子 : $dis+dep[x]>=dep[y]+1$

我们发现可以找到x的祖先的$dis+dep$的**最大值**(其实就是再往上跳一遍),也会影响到他的子树(虽然说子树的每个点的$dis+dep$已经清零了，但是还是可以从上面转移下来)

于是我们找到这个值以后，再让x的权值减去它就好了(相当于差分)

```cpp
//代码很丑，勿喷
#include<bits/stdc++.h>
#define re register
#define rep(i,a,b) for(re int i=a,i##end=b; i<=i##end; i++)
#define drep(i,a,b) for(re int i=a,i##end=b; i>=i##end; i--)
#define repp(i,a,b) for(re int i=a,i##end=b; i<i##end; i++)
#define drepp(i,a,b) for(re int i=a,i##end=b; i>i##end; i--)
#define Erep(i,x) for(re int i=head[x]; i; i=Edge[i].nxt)
#define lowbit(x) ((x)&-(x))
#define debug(x) cerr<<#x<<" = "<<x<<endl
#define ms(x,a) memset(x,a,sizeof x)
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define fi first
#define se second
#define coint const int
#define coll const ll
#define CM cerr<<(&S2-&S1)/1024./1024.<<"MB"<<endl
typedef long long ll;
using namespace std;
template<class T>inline T rd(){
	static char ch;static bool neg;static T x;
	for(ch=0, neg=0; ch>'9'||ch<'0'; neg|=(ch=='-'),ch=getchar());
	for(x=0; ch>='0'&&ch<='9'; x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar());
	return neg?-x:x;
}
template<class T>inline T Max(const T &x, const T &y) { return x>y?x:y; }
template<class T>inline T Min(const T &x, const T &y) { return x<y?x:y; }

coint N=100000+5,M=200000+5;
struct edge{
	int to,nxt;
}Edge[N<<1];
int head[N],tcnt;
inline void AddEdge(coint u, coint v){
	Edge[++tcnt]=(edge)<%v,head[u]%>;
	head[u]=tcnt; return;
}

struct Ask{
	int opt,x;
	inline void read() { opt=rd<int>(); x=rd<int>(); return; }
}ask[M];

int n,m;

int dep[N],f[N],sz[N],son[N],top[N],L[N],R[N],ID[N],dfn;

void pre_dfs(coint x, coint fa){
	int &SZ=sz[x],&SON=son[x]; SZ=1;
	Erep(i,x){
		int y=Edge[i].to;
		if(y==fa) continue;
		dep[y]=dep[x]+1; f[y]=x;
		pre_dfs(y,x);
		SZ+=sz[y];
		SON=(sz[SON]<sz[y]?y:SON);
	}
	return;
}

void dfs_top(coint x, coint fa, coint tp){
	top[x]=tp; L[x]=++dfn; ID[dfn]=x;
	coint &SON=son[x];
	if(SON) dfs_top(SON,x,tp);
	Erep(i,x){
		int y=Edge[i].to;
		if(y==fa || y==SON) continue;
		dfs_top(y,x,y);
	} R[x]=dfn;
	return;
}

struct node{
	int sum,mx;
	friend node operator + (const node &x, const node &y){
		return (node)<%x.sum+y.sum,Max(x.mx+y.sum,y.mx)%>;
	}
};

struct Segment_Tree{
	node sum[N<<2];
	int lazy[N<<2];
	inline void Up(coint p){
		coint ls=p<<1,rs=ls|1;
		sum[p]=sum[ls]+sum[rs];
		return;
	}
	inline void Down(coint p){
		int &x=lazy[p];
		if(!x) return;
		coint ls=p<<1,rs=ls|1;
		lazy[ls]=lazy[rs]=1;
		sum[ls]=sum[rs]=(node)<%0,0%>;
		x=0; return;
	}
	void Build(coint p, coint l, coint r){
		sum[p]=(node)<%0,0%>; lazy[p]=0;
		if(l==r) return;
		coint mid=(l+r)>>1,ls=p<<1,rs=ls|1;
		Build(ls,l,mid); Build(rs,mid+1,r);
		return;
	}
	void Upd1(coint p, coint l, coint r, coint L, coint R){
		if(l==L && r==R){
			sum[p]=(node)<%0,0%>;
			lazy[p]=1;
			return;
		}
		Down(p);
		coint mid=(l+r)>>1,ls=p<<1,rs=ls|1;
		if(R<=mid) Upd1(ls,l,mid,L,R);
		else if(L>mid) Upd1(rs,mid+1,r,L,R);
		else Upd1(ls,l,mid,L,mid),Upd1(rs,mid+1,r,mid+1,R);
		Up(p); return;
	}
	void Upd2(coint p, coint l, coint r, coint x, coint val){
		if(l==r){
			sum[p]=(node)<%val,dep[ID[l]]+val%>;
			return;
		}
		Down(p);
		coint mid=(l+r)>>1,ls=p<<1,rs=ls|1;
		if(x<=mid) Upd2(ls,l,mid,x,val);
		else Upd2(rs,mid+1,r,x,val);
		Up(p); return;
	}
	node Que(coint p, coint l, coint r, coint L, coint R){
		if(l==L && r==R) return sum[p];
		Down(p);
		coint mid=(l+r)>>1,ls=p<<1,rs=ls|1;
		if(R<=mid) return Que(ls,l,mid,L,R);
		if(L>mid) return Que(rs,mid+1,r,L,R);
		return Que(ls,l,mid,L,mid)+Que(rs,mid+1,r,mid+1,R);
	}
}sgtr;

inline int Get_Max(int x){
	node res=(node)<%0,0%>;
	int tpx=top[x];
	while(x){
		res=sgtr.Que(1,1,n,L[tpx],L[x])+res;
		x=f[tpx]; tpx=top[x];
	}
	return res.mx;
}

inline void solve(){
	pre_dfs(1,0); dfs_top(1,0,1);
	rep(i,1,m){
		coint opt=(ask[i].opt),x=ask[i].x;
		switch(opt){
			case 1:{
				sgtr.Upd2(1,1,n,L[x],sgtr.Que(1,1,n,L[x],L[x]).sum+1);
				break;
			}
			case 2:{
				sgtr.Upd1(1,1,n,L[x],R[x]);
				int tmp=Get_Max(x);
				if(tmp>=dep[x]+1) sgtr.Upd2(1,1,n,L[x],dep[x]-tmp);
				break;
			}
			default:{
				puts(Get_Max(x)>=dep[x]+1?"black":"white");
				break;
			}
		}
	}
	return;
}


int main(){
	n=rd<int>(),m=rd<int>();
	rep(i,2,n){
		int x=rd<int>();
		AddEdge(x,i); AddEdge(i,x);
	}
	rep(i,1,m) ask[i].read();
	solve();
	return 0;
}

```

---

## 作者：newbiechd (赞：3)

# CF1017G The Tree

[蒟蒻的Blog](https://www.cnblogs.com/cj-chd/)

树链剖分好题。

乍一看还以为是道沙比题，然后发现修改操作有点不一样。

但是如果你对基本操作还不太熟练，可以看看我的[树链剖分总结](https://www.cnblogs.com/cj-chd/p/10038820.html)

有三个操作：

1. 从一个点往下染黑，是黑色节点就继续染，一直染到白色节点为止；
2. 染白一棵子树；
3. 查询一个点的颜色。

主要是第一个操作不好处理。由于每次只询问一个点的信息，考虑把一个点的颜色用从根节点到这个点的**最大后缀和**来表达：最大后缀和小于零则为白色，反之则为黑色。首先把树上每一个点的权值都定为$-1$，对于每个1操作，把该点的权值++；对于每个2操作，把一棵子树的权值全都变成$-1$，并在该子树的根节点减去一个权值，使得大树根节点到子树根节点的最大后缀和恰为$-1$；对于3查询，查询一个根节点到这个点的最大后缀和，$<0$白色，$\ge  0$黑色。可以证(shou)明(wan)，这样做正确地在$O(n(log n)^2)$的复杂度内维护了树上的信息。

如果你不会在树上维护最大后缀和，可以先考虑在区间上维护，用线段树维护一个区间和、一个区间最大后缀和就好了，合并信息的方法就很容易看出了，查询的时候也可以用同样的方法合并，放到树上来之后合并的方法还是没有变。

```cpp
#include<cstdio>
#include<cctype>
#define R register
#define I inline
using namespace std;
const int S=200003,M=800003,inf=0x3f3f3f3f;
char buf[1000000],*p1,*p2;
I char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,S,stdin),p1==p2)?EOF:*p1++;}
I int rd(){
	R int f=0; R char c=gc();
	while(c<48||c>57) c=gc();
	while(c>47&&c<58) f=f*10+(c^48),c=gc();
	return f;
}
struct O{int f,g;};
struct N{int f,g,b;}a[M];
int h[S],s[S],g[S],d[S],t[S],p[S],q[S],r[S],f[S],c,e,n;
I int max(int x,int y){return x>y?x:y;}
O operator+(O x,O y){return (O){max(x.f+y.g,y.f),x.g+y.g};}
I void add(int x,int y){s[++c]=h[x],h[x]=c,g[c]=y;}
I void upd(int k,int l,int r){a[k].f=-1,a[k].g=-(r-l+1),a[k].b=1;}
I void psu(int k,int p,int q){a[k].f=max(a[q].f,a[p].f+a[q].g),a[k].g=a[p].g+a[q].g;}
I void psd(int k,int l,int r){
	if(a[k].b){
		R int p=k<<1,q=p|1,m=l+r>>1;
		upd(p,l,m),upd(q,m+1,r),a[k].b=0;
	}
}
void bld(int k,int l,int r){
	if(l==r){a[k].f=a[k].g=-1; return ;}
	R int p=k<<1,q=p|1,m=l+r>>1;
	bld(p,l,m),bld(q,m+1,r),psu(k,p,q);
}
void mdf1(int k,int l,int r,int x,int v){
	if(l==r){a[k].f+=v,a[k].g+=v; return ;}
	R int p=k<<1,q=p|1,m=l+r>>1;
	psd(k,l,r);
	if(x<=m) mdf1(p,l,m,x,v);
	else mdf1(q,m+1,r,x,v);
	psu(k,p,q);
}
void mdf2(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y){upd(k,l,r); return ;}
	R int p=k<<1,q=p|1,m=l+r>>1;
	psd(k,l,r);
	if(x<=m) mdf2(p,l,m,x,y);
	if(m<y) mdf2(q,m+1,r,x,y);
	psu(k,p,q);
}
O qry(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y) return (O){a[k].f,a[k].g};
	R int p=k<<1,q=p|1,m=l+r>>1;
	O o=(O){-inf,0};
	psd(k,l,r);
	if(x<=m) o=o+qry(p,l,m,x,y);
	if(m<y) o=o+qry(q,m+1,r,x,y);
	return o;
}
void dfs1(int x,int f){
	d[x]=d[f]+1,p[x]=f,t[x]=1;
	for(R int i=h[x],y,m=0;i;i=s[i])
		if((y=g[i])^f){
			dfs1(y,x),t[x]+=t[y];
			if(t[y]>m) q[x]=y,m=t[y];
		}
}
void dfs2(int x,int t){
	f[x]=++e,r[x]=t;
	if(q[x]) dfs2(q[x],t);
	for(R int i=h[x],y;i;i=s[i])
		if((y=g[i])^p[x]&&y^q[x])
			dfs2(y,y);
}
I int qry0(int x){
	R int o=-inf,v=0; O u;
	while(x)
		u=qry(1,1,n,f[r[x]],f[x]),o=max(o,u.f+v),v+=u.g,x=p[r[x]];
	return o;
}
int main(){
	R int Q,i,x,y;
	for(n=rd(),Q=rd(),i=2;i<=n;++i)
		x=rd(),add(x,i);
	dfs1(1,0),dfs2(1,1),bld(1,1,n);
	for(i=1;i<=Q;++i){
		x=rd(),y=rd();
		if(x==1)
			mdf1(1,1,n,f[y],1);
		if(x==2)
			mdf2(1,1,n,f[y],f[y]+t[y]-1),mdf1(1,1,n,f[y],-(qry0(y)+1));
		if(x==3)
			qry0(y)>=0?printf("black\n"):printf("white\n");
	}
	return 0;
}

```

跑的还算快。

---

## 作者：tzc_wk (赞：2)

[Codeforces 题面传送门](https://codeforces.ml/contest/1017/problem/G) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1017G)

好题。

首先这个修改操作看起来就有点鸡肋，我们考虑将其进行转化。我们不妨从修改对询问的贡献的角度来看待这些修改，那么不难发现，对于一个点 $x$，一个点 $y$ 的修改能够使 $x$ 变成黑色，当且仅当 $y$ 是 $x$ 的祖先，并且 $x$ 到 $y$​ 路径上所有点的操作次数之和大于 $x,y$ 之间的距离，这样 $y$ 的修改才能影响到 $x$。可以注意到，我们可以将模型进行如下转化：每个点有一个点权，初始是 $-1$，每次操作将某个点的点权加 $1$，或者询问一个点 $x$ 到根路径上是否存在另一个点 $y$，满足 $x,y$ 之间路径上的点权之和 $\ge 0$。不难发现该问题和原问题是等价的，线段树 + 树链剖分维护后缀最大值即可解决。

如果没有 $2$ 操作那么问题这么做就解决了，接下来考虑怎样处理 $2$ 操作，一个很直观的想法是将 $x$ 子树内所有点权值设为 $-1$，但是问题真的就这么简单吗？不难发现有可能出现这样的情况：在 clear $x$ 的子树之前，$x$ 的父亲进行了很多次操作导致点权很大，此时你即便把 $x$ 权值设为 $-1$，$x$ 到根节点路径上权值的最大前缀和还是 $\ge 0$。怎么办呢？由于我们强制要将 $x$ 的权值设为 $-1$，因此我们要适当减小 $x$ 点的权值，使得 $x$ 点到根节点路径上的最大前缀和 $=-1$，很明显，我们需要让 $x$ 点的权值减去 $\text{此时 }x\text{ 点到根节点路径上的最大前缀和}+1$，直接线段树上单点修改即可。

时间复杂度 $n\log^2n$。

```cpp
const int MAXN = 1e5;
const int INF = 0x3f3f3f3f;
int n, qu, hd[MAXN + 5], to[MAXN + 5], nxt[MAXN + 5], ec = 0;
void adde(int u, int v) {to[++ec] = v; nxt[ec] = hd[u]; hd[u] = ec;}
int fa[MAXN + 5], siz[MAXN + 5], wson[MAXN + 5], dep[MAXN + 5];
int top[MAXN + 5], dfn[MAXN + 5], edt[MAXN + 5], tim = 0;
void dfs1(int x) {
	siz[x] = 1;
	for (int e = hd[x]; e; e = nxt[e]) {
		int y = to[e]; dep[y] = dep[x] + 1; dfs1(y); siz[x] += siz[y];
		if (siz[y] > siz[wson[x]]) wson[x] = y;
	}
}
void dfs2(int x, int tp) {
	top[x] = tp; dfn[x] = ++tim; if (wson[x]) dfs2(wson[x], tp);
	for (int e = hd[x]; e; e = nxt[e]) if (to[e] != wson[x]) dfs2(to[e], to[e]);
	edt[x] = tim;
}
struct dat {
	int sum, mxsuf;
	dat() {sum = mxsuf = 0;}
	friend dat operator + (dat x, dat y) {
		dat res; res.sum = x.sum + y.sum;
		res.mxsuf = max(y.mxsuf, y.sum + x.mxsuf);
		return res;
	}
};
struct node {int l, r, tg; dat v;} s[MAXN * 4 + 5];
void pushup(int k) {s[k].v = s[k << 1].v + s[k << 1 | 1].v;}
void build(int k, int l, int r) {
	s[k].l = l; s[k].r = r; if (l == r) return s[k].v.sum = s[k].v.mxsuf = -1, void();
	int mid = l + r >> 1; build(k << 1, l, mid); build(k << 1 | 1, mid + 1, r); pushup(k);
}
void tag(int k) {s[k].tg = 1; s[k].v.sum = -(s[k].r - s[k].l + 1); s[k].v.mxsuf = -1;}
void pushdown(int k) {if (s[k].tg) tag(k << 1), tag(k << 1 | 1), s[k].tg = 0;}
void assign(int k, int l, int r) {
	if (l <= s[k].l && s[k].r <= r) return tag(k), void(); pushdown(k); int mid = s[k].l + s[k].r >> 1;
	if (r <= mid) assign(k << 1, l, r); else if (l > mid) assign(k << 1 | 1, l, r);
	else assign(k << 1, l, mid), assign(k << 1 | 1, mid + 1, r); pushup(k);
}
void modify(int k, int p, int v) {
	if (s[k].l == s[k].r) return s[k].v.sum += v, s[k].v.mxsuf += v, void(); pushdown(k);
	int mid = s[k].l + s[k].r >> 1; (p <= mid) ? modify(k << 1, p, v) : modify(k << 1 | 1, p, v); pushup(k);
}
dat query(int k, int l, int r) {
	if (l <= s[k].l && s[k].r <= r) return s[k].v; pushdown(k); int mid = s[k].l + s[k].r >> 1;
	if (r <= mid) return query(k << 1, l, r); else if (l > mid) return query(k << 1 | 1, l, r);
	else return query(k << 1, l, mid) + query(k << 1 | 1, mid + 1, r);
}
int askmx(int x) {
	int csum = 0, mx = -INF;
	while (x) {
		dat D = query(1, dfn[top[x]], dfn[x]);
		chkmax(mx, csum + D.mxsuf); csum += D.sum;
		x = fa[top[x]];
	}
//	printf("%d\n", mx);
	return mx;
}
int main() {
	scanf("%d%d", &n, &qu);
	for (int i = 2; i <= n; i++) scanf("%d", &fa[i]), adde(fa[i], i);
	dfs1(1); dfs2(1, 1); build(1, 1, n);
//	for (int i = 1; i <= n; i++) printf("%d%c", top[i], " \n"[i == n]);
//	for (int i = 1; i <= n; i++) printf("%d %d\n", dfn[i], edt[i]);
	while (qu--) {
		int opt, x; scanf("%d%d", &opt, &x);
		if (opt == 1) modify(1, dfn[x], 1);
		else if (opt == 2) {
			if (dfn[x] != edt[x]) assign(1, dfn[x] + 1, edt[x]);
			modify(1, dfn[x], -(askmx(x) + 1));
		} else printf("%s\n", (askmx(x) >= 0) ? "black" : "white");
	}
	return 0;
}
```



---

## 作者：Tyyyyyy (赞：2)

## CF1017G

### 题意简述
给定一棵树，支持三种操作：

- 给定一个点，不断往下递归直到找到白点，把白点染黑。如果当前点是黑点要递归它的所有儿子。

- 子树染白。

- 单点查颜色。

$1\leq n,q\leq 10^5$。

### 题目分析
我们发现这个第一种操作很烦，而且查询只查单点，不难想到根号重构。我们将操作的时间轴分为每 $\sqrt{n}$ 个操作一块，那么每一块内考虑时，我们本质上只关心这一块内的操作涉及到的 $\sqrt{n}$ 个结点。

我们考虑对于一个确定的块怎么维护其中的操作。我们可以对这 $\sqrt{n}$ 个关键点建一个类似于虚树的东西，在有祖先关系的相邻两关键点之间连边。考虑我们需要在边上记录什么信息，逐条操作分析：

- 对于第一种操作，每一次操作可以在相邻两关键点之间的链上消除一个白点。所以我们需要记录这条链上的白点个数。

- 对于第二种操作，我们需要清空这个子树，同时重置链上的白点个数。所以我们需要记录这条链上的结点数量。

对于维护操作本身而言，因为这棵新树上只有 $\sqrt{n}$ 个结点，我们暴力 dfs 的同时维护上述信息即可。查询是简单的。

现在还剩下一个问题：在相邻两块之间如何重构这个新树？我们知道每一次操作一可以消除一个链上的白点，而操作二相当于重置所有这个子树内的操作一。我们在操作的过程中再维护一下这个点做了多少次操作一，模拟操作过程即可维护出树上结点颜色的变化了。

时间复杂度为 $O(n\sqrt{n})$。因为递归常数比较大，实测取块长为 $600$ 左右效率最高。

Code：
```cpp
const int N=1e5+10,S=600;
int n,q,p[N],t[N],v[N];
vector<int>G[N];
vector<pair<int,pii> >g[N];
bool vis[N],clr[N],tmp[N],col[N];
int tag[N];
void init()
{
	for(int i=1;i<=n;i++)
		vis[i]=clr[i]=0,g[i].resize(0),tmp[i]=col[i],tag[i]=0;
}
void build(int u,int fa,int cnt,int d)
{
	if(vis[u])
	{
		if(fa)g[fa].push_back({u,{cnt,d}});
		for(int v:G[u])build(v,u,0,0);
	}
	else for(int v:G[u])build(v,fa,cnt+(!col[u]),d+1);
}
void rebuild(int u,int tg,bool clear)
{
	if(vis[u])tg=tag[u],clear|=clr[u];
	else
	{
		col[u]=tmp[u];
		if(clear)col[u]=0;
		if(!col[u]&&tg)col[u]=1,tg--;
	}
	for(int v:G[u])rebuild(v,tg,clear);
}
void upd1(int u)
{
	if(!col[u])return col[u]=1,void();
	tag[u]++;
	for(auto edge:g[u])
	{
		int v=edge.fi,cnt=edge.se.fi;
		if(cnt<tag[u])upd1(v);
	}
}
void upd2(int u)
{
	col[u]=0,tag[u]=0,clr[u]=1;
	for(auto &edge:g[u])
	{
		edge.se.fi=edge.se.se;
		upd2(edge.fi);
	}
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=2;i<=n;i++)scanf("%d",&p[i]),G[p[i]].push_back(i);
	for(int i=1;i<=q;i++)scanf("%d%d",&t[i],&v[i]);
	for(int i=1;i<=q;i+=S)
	{
		int R=min(q,i+S-1);
		init();
		for(int j=i;j<=R;j++)vis[v[j]]=1;
		build(1,0,0,0);
		for(int j=i;j<=R;j++)
			if(t[j]==1)upd1(v[j]);
			else if(t[j]==2)upd2(v[j]);
			else
			{
				if(col[v[j]])puts("black");
				else puts("white");
			}
		rebuild(1,0,0);
	}
	IO::pchar(0);
	return 0;
}
const int N=1e5+10,S=600;
int n,q,p[N],t[N],v[N];
vector<int>G[N];
vector<pair<int,pii> >g[N];
bool vis[N],clr[N],tmp[N],col[N];
int tag[N];
void init()
{
	for(int i=1;i<=n;i++)
		vis[i]=clr[i]=0,g[i].resize(0),tmp[i]=col[i],tag[i]=0;
}
void build(int u,int fa,int cnt,int d)
{
	if(vis[u])
	{
		if(fa)g[fa].push_back({u,{cnt,d}});
		for(int v:G[u])build(v,u,0,0);
	}
	else for(int v:G[u])build(v,fa,cnt+(!col[u]),d+1);
}
void rebuild(int u,int tg,bool clear)
{
	if(vis[u])tg=tag[u],clear|=clr[u];
	else
	{
		col[u]=tmp[u];
		if(clear)col[u]=0;
		if(!col[u]&&tg)col[u]=1,tg--;
	}
	for(int v:G[u])rebuild(v,tg,clear);
}
void upd1(int u)
{
	if(!col[u])return col[u]=1,void();
	tag[u]++;
	for(auto edge:g[u])
	{
		int v=edge.fi,cnt=edge.se.fi;
		if(cnt<tag[u])upd1(v);
	}
}
void upd2(int u)
{
	col[u]=0,tag[u]=0,clr[u]=1;
	for(auto &edge:g[u])
	{
		edge.se.fi=edge.se.se;
		upd2(edge.fi);
	}
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=2;i<=n;i++)scanf("%d",&p[i]),G[p[i]].push_back(i);
	for(int i=1;i<=q;i++)scanf("%d%d",&t[i],&v[i]);
	for(int i=1;i<=q;i+=S)
	{
		int R=min(q,i+S-1);
		init();
		for(int j=i;j<=R;j++)vis[v[j]]=1;
		build(1,0,0,0);
		for(int j=i;j<=R;j++)
			if(t[j]==1)upd1(v[j]);
			else if(t[j]==2)upd2(v[j]);
			else
			{
				if(col[v[j]])puts("black");
				else puts("white");
			}
		rebuild(1,0,0);
	}
	return 0;
}
```

---

## 作者：TammyZhao (赞：2)

# 题解

- 树链剖分 $+$ 线段树。

- 考虑操作 $1$，对于一个点 $x$，一个点 $y$ 的修改能够使 $x$ 变成黑色，当且仅当 $y$ 是 $x$ 的祖先，并且 $x$ 到 $y$ 路径上所有点的操作次数之和大于  $x,y$ 之间的距离。

- 然后将模型进行如下转化：每个点有一个点权，初始是 $-1$，每次操作将某个点的点权加 $1$，或者询问一个点 $x$ 到根路径上是否存在另一个点 $y$，满足 $x,y$ 之间路径上的点权之和 $\ge0$，线段树 $+$ 树链剖分维护后缀最大值即可。

- 接下来考虑操作 $2$，即使 $x$ 和 $x$ 子树内的点到根节点路径上权值的最大前缀和为 $-1$。很明显，我们需要让 $x$ 点的权值减去此时 $x$ 点到根节点路径上的最大前缀和 $+1$，线段树单点修改即可。注意还需将 $x$ 子树内除 $x$ 的点权值设为 $-1$。

- 时间复杂度 $\mathcal O(n \log^2 n)$，代码不放了。

---

## 作者：FutaRimeWoawaSete (赞：0)

考虑一种比较显然的性质：对于查询操作 $3$ 的 $x_1$，只有 $1,2$ 操作中 $x$ 在 $x_1$ 祖先链上的操作会影响当前查询的答案。

假设我们要确定从一个祖先点 $z$ 开始向下，是否能把 $z \sim x$ 路径全染成黑点，记初始时所有点点权为 $-1$，一次 $1$ 操作对于点权 $+1$，那么问题变为了询问是否有一条祖先--子孙的路径 $z \sim x$ 满足链上权值和 $\geq 0$，也等价于查询根到 $x$ 上关于 $x$ 的最大后缀。

将所有操作进行构造转化：

- 操作 $1$：对于 $x$ 点权 $+1$；

- 操作 $2$：对于 $x$ 子树内的点权区间赋值成 $-1$，对于 $x$ 点权加上 $-\max(z,x) - 1$；

- 操作 $3$：查询根到 $x$ 上关于 $x$ 的最大后缀。

关于操作 $2$ 的正确性，可以理解成去除之前历史状态下祖先链对于当前子树的影响。可以发现这样处理后完美地规避了互相影响的问题。

这样时间复杂度就变成 $O(n \log ^ 2  n)$ 了。

同时还存在一种基于操作分块与序列分块的做法。操作分块即每 $\sqrt q$ 个操作建立虚树，涉及到的点都做成关键点后暴力模拟三个操作，进行一些处理后修改操作都可以做到与虚树点数相关，时间复杂度就平衡了。

序列分块可以[传送门](https://www.luogu.com.cn/blog/feecle6418/solution-cf1017g)。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
int n,m,head[Len],cnt,dfn[Len],tim,siz[Len],son[Len],dep[Len],top[Len],fa[Len];
struct node
{
	int next,to;
}edge[Len << 1];
void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
void dfs1(int x,int f)
{
	dep[x] = dep[f] + 1;
	fa[x] = f;
	siz[x] = 1;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		dfs1(to , x);
		siz[x] += siz[to];
		if(siz[son[x]] < siz[to]) son[x] = to;
	}
}
void dfs2(int x,int topf)
{
	top[x] = topf;
	dfn[x] = ++ tim;
	if(!son[x]) return;
	dfs2(son[x] , topf);
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == fa[x] || to == son[x]) continue;
		dfs2(to , to);
	}
}
int tag[Len << 2],sum[Len << 2],mx[Len << 2],v[Len << 2];
#define ls(p) p << 1
#define rs(p) p << 1 | 1
void push_up(int x)
{
	sum[x] = sum[ls(x)] + sum[rs(x)];
	mx[x] = max(mx[rs(x)] , mx[ls(x)] + sum[rs(x)]);
}
void push_down(int p,int l,int r)
{
	if(tag[p])
	{
		int mid = (l + r) >> 1;
		tag[ls(p)] = tag[rs(p)] = tag[p];
		sum[ls(p)] = -(mid - l + 1) , sum[rs(p)] = -(r - mid);
		v[ls(p)] = v[rs(p)] = mx[ls(p)] = mx[rs(p)] = -1;
		tag[p] = 0;
	}
} 
void build(int p,int l,int r)
{
	tag[p] = 0;
	if(l == r)
	{
		v[p] = mx[p] = sum[p] = -1;
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	push_up(p);
}
void updp(int p,int l,int r,int idx,int w)
{
	if(l == r)
	{
		v[p] += w;
		mx[p] += w;
		sum[p] += w;
		return;	
	}
	push_down(p , l , r);
	int mid = (l + r) >> 1;
	if(idx <= mid) updp(ls(p) , l , mid , idx , w);
	else updp(rs(p) , mid + 1 , r , idx , w);
	push_up(p);
}
void cover(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r)
	{
		tag[p] = 1;
		v[p] = mx[p] = -1;
		sum[p] = -(r - l + 1);
		return;
	}
	push_down(p , l , r);
	int mid = (l + r) >> 1;
	if(nl <= mid) cover(ls(p) , l , mid , nl , nr);
	if(nr > mid) cover(rs(p) , mid + 1 , r , nl , nr);
	push_up(p);
}
int qs(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) return sum[p];
	push_down(p , l , r);
	int mid = (l + r) >> 1 , res = 0;
	if(nl <= mid) res += qs(ls(p) , l , mid , nl , nr);
	if(nr > mid) res += qs(rs(p) , mid + 1 , r , nl , nr);
	return res;
}
int qmx(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) return mx[p];
	push_down(p , l , r);
	int mid = (l + r) >> 1 , res = -1e9;
	if(nl <= mid) res = max(res , qmx(ls(p) , l , mid , nl , nr));
	if(nr > mid) res = max(qmx(rs(p) , mid + 1 , r , nl , nr) , res + qs(rs(p) , mid + 1 , r , nl , nr));
	return res;
}
int Qchain(int x)
{
	int res = -1e9 , w = 0;
	while(top[x])
	{
		res = max(res , w + qmx(1 , 1 , n , dfn[top[x]] , dfn[x]));
		w += qs(1 , 1 , n , dfn[top[x]] , dfn[x]);
		x = fa[top[x]];
	}
	return res;
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 2 ; i <= n ; i ++) 
	{
		int f;scanf("%d",&f);
		add(f , i);
	}
	dfs1(1 , 0);
	dfs2(1 , 1);
	build(1 , 1 , n);
	for(int i = 1 ; i <= m ; i ++)
	{
		int opt,x;scanf("%d %d",&opt,&x);
		if(opt == 1) updp(1 , 1 , n , dfn[x] , 1);
		else if(opt == 2)
		{
			cover(1 , 1 , n , dfn[x] , dfn[x] + siz[x] - 1);
			updp(1 , 1 , n , dfn[x] , -Qchain(x) - 1);
		}
		else if(opt == 3)
		{
			int flg = Qchain(x);
			puts(flg >= 0 ? "black" : "white");	
		}
	}
	return 0;
}
```

---

## 作者：EndSaH (赞：0)

[也许更好的阅读体验](https://endsah.cf/blog/CF1017G-The-Tree/)

暴力染色不太好维护。考虑如何查询一个节点是否被染色，如果把 1 这个染色操作视作单点加 1，那么如果存在一个祖先（包含 $x$），其到 $x$ 的路径权值和大于等于路径长度，那么 $x$ 便被染色。

于是便有了一个思路：把路径长度设为负的，也就是初始把所有点权视为 -1，然后查询就直接查询根到 $x$ 的所有后缀和的最大值是否 $\ge 0$ 即可。

（前缀指根到 $x$，后缀指 $x$ 到根）

树直接想怎么维护所有后缀和的最大值可能不直观，丢到序列上就很好想：一个区间的后缀最大值为 左区间的后缀最大值 + 右区间权值和，右区间后缀最大值 这两个值中大的那个。于是线段树维护，查询直接对那 $\log$ 个区间按上面这个方法从右往左合并。

在树上也是一样的，树剖提区间。因为是从 $x$ 往根跳，所以区间默认从右往左，直接合并就行。

考虑怎样在当前这个思路下正确维护 2 操作。首先肯定得区间覆盖为 -1，还得让**覆盖操作之后**子树内所有节点到根的后缀和最大值为 -1，而子树内所有节点的后缀路径要么不包含 $x$，此时肯定后缀最大值是他自己到他自己的路径，值为 -1；要么包含 $x$，这个有可能不对（因为有上面节点的影响），所以直接在覆盖之后查 $x$ 的后缀和最大值，给 $x$ 单点加这个 `-(查到的值 + 1)` 即可，这样就能确保所有节点到根的后缀和最大值为 -1 了。

一定得记得合并顺序。

代码：（指针警告）

```cpp
/**********************************************************
 * Author        : EndSaH
 * Email         : hjxhb1@gmail.com
 * Created Time  : 2019-08-16 14:21
 * FileName      : bigbro.cpp
 * Website       : https://endsah.cf
 * *******************************************************/

#include <cstdio>
#include <cctype>
#include <vector>

typedef std::pair<int, int> pii;

#define fir first
#define sec second
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define Debug(s) debug("The message in line %d, Function %s: %s\n", __LINE__, __FUNCTION__, s)
#define getchar() (ipos == iend and (iend = (ipos = _ibuf) + fread(_ibuf, 1, __bufsize, stdin), ipos == iend) ? EOF : *ipos++)
#define putchar(ch) (opos == oend ? fwrite(_obuf, 1, __bufsize, stdout), opos = _obuf : 0, *opos++ = (ch))
#define __bufsize (1 << 21 | 1)

char _ibuf[__bufsize], _obuf[__bufsize], _stk[50];
char *ipos = _ibuf, *iend = _ibuf, *opos = _obuf, *oend = _obuf + __bufsize, *stkpos = _stk;

struct END
{ ~END() { fwrite(_obuf, 1, opos - _obuf, stdout); } }
__;

inline int read()
{
    register int x = 0;
    register char ch;
    while (!isdigit(ch = getchar()));
    while (x = (x << 3) + (x << 1) + (ch & 15), isdigit(ch = getchar()));
    return x;
}

template <typename _INT>
inline void write(_INT x)
{
    while (*++stkpos = x % 10 ^ 48, x /= 10, x);
    while (stkpos != _stk)
        putchar(*stkpos--);
}

inline void Puts(const char* str)
{
    while (*str)
        putchar(*str++);
    putchar('\n');
}

template <typename _Tp>
inline bool Chkmax(_Tp& x, const _Tp& y)
{ return x < y ? x = y, true : false; }

template <typename _Tp>
inline bool Chkmin(_Tp& x, const _Tp& y)
{ return x > y ? x = y, true : false; }

const int maxN = 2e5 + 2;

int n, m, dfst;
int fa[maxN], top[maxN], son[maxN], dfn[maxN], size[maxN];
std::vector<int> G[maxN];

inline pii Merge(pii l, pii r)
{ return pii(l.fir + r.fir, std::max(r.sec, l.sec + r.fir)); }

namespace SEG
{
    typedef struct Node* ptr;

    ptr root;

    struct Node
    {
        int l, r;
        pii info;
        bool tag;
        ptr lson, rson;

        Node() { }

        Node(int _l, int _r) : l(_l), r(_r)
        { this->tag = false; }

        void Cover()
        { this->tag = true, this->info = pii(this->l - this->r - 1, -1); }

        void Pushup()
        { this->info = Merge(this->lson->info, this->rson->info); }

        void Pushdown()
        {
            if (this->tag)
                this->lson->Cover(), this->rson->Cover(), this->tag = false;
        }
    };

    inline ptr New(int l, int r)
    {
        static ptr mempool = new Node[n << 2];
        return new(mempool++) Node(l, r);
    }

    void Build(int l, int r, ptr& cur = root)
    {
        cur = New(l, r);
        if (l == r)
        {
            cur->info = pii(-1, -1);
            return;
        }
        int mid = (l + r) >> 1;
        Build(l, mid, cur->lson), Build(mid + 1, r, cur->rson);
        cur->Pushup();
    }

    void Add(int pos, int addval, ptr cur = root)
    {
        if (cur->l == cur->r)
        {
            cur->info = pii(cur->info.fir + addval, cur->info.sec + addval);
            return;
        }
        cur->Pushdown();
        int mid = (cur->l + cur->r) >> 1;
        if (pos <= mid)
            Add(pos, addval, cur->lson);
        else
            Add(pos, addval, cur->rson);
        cur->Pushup();
    }

    pii Query(int ql, int qr, ptr cur = root)
    {
        if (ql <= cur->l and cur->r <= qr)
            return cur->info;
        cur->Pushdown();
        pii res(0, -1e9);
        int mid = (cur->l + cur->r) >> 1;
        if (mid < qr)
            res = Merge(Query(ql, qr, cur->rson), res);
        if (ql <= mid)
            res = Merge(Query(ql, qr, cur->lson), res);
        return res;
    }

    void Cover(int ql, int qr, ptr cur = root)
    {
        if (ql <= cur->l and cur->r <= qr)
        {
            cur->Cover();
            return;
        }
        if (ql > cur->r or qr < cur->l)
            return;
        cur->Pushdown();
        Cover(ql, qr, cur->lson), Cover(ql, qr, cur->rson);
        cur->Pushup();
    }
}

void DFS1(int u)
{
    size[u] = 1;
    for (int v : G[u]) if (v != fa[u])
    {
        DFS1(v);
        size[u] += size[v];
        if (size[v] > size[son[u]])
            son[u] = v;
    }
}

void DFS2(int u)
{
    dfn[u] = ++dfst;
    if (son[u])
        top[son[u]] = top[u], DFS2(son[u]);
    for (int v : G[u]) if (!top[v])
        top[v] = v, DFS2(v);
}

inline int Query(int x)
{
    pii res(0, -1e9);
    while (top[x] != 1)
    {
        res = Merge(SEG::Query(dfn[top[x]], dfn[x]), res);
        x = fa[top[x]];
    }
    res = Merge(SEG::Query(1, dfn[x]), res);
    return res.sec;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("bigbro.in", "r", stdin);
    freopen("bigbro.out", "w", stdout);
#endif
    n = read(), m = read();
    for (int i = 2; i <= n; ++i)
        G[fa[i] = read()].push_back(i);
    DFS1(1);
    top[1] = 1, DFS2(1);
    SEG::Build(1, n);
    while (m--)
    {
        int opt = read(), x = read(), val;
        switch (opt)
        {
        case 1 :
            SEG::Add(dfn[x], 1);
            break;
        case 2 :
            SEG::Cover(dfn[x], dfn[x] + size[x] - 1);
            SEG::Add(dfn[x], -Query(x) - 1);
            break;
        case 3 :
            Puts(Query(x) >= 0 ? "Yes" : "No");
            break;
        }
    }
    return 0;
}
```

---

