# Surprise me!

## 题目描述

Tired of boring dates, Leha and Noora decided to play a game.

Leha found a tree with $ n $ vertices numbered from $ 1 $ to $ n $ . We remind you that tree is an undirected graph without cycles. Each vertex $ v $ of a tree has a number $ a_{v} $ written on it. Quite by accident it turned out that all values written on vertices are distinct and are natural numbers between $ 1 $ and $ n $ .

The game goes in the following way. Noora chooses some vertex $ u $ of a tree uniformly at random and passes a move to Leha. Leha, in his turn, chooses (also uniformly at random) some vertex $ v $ from remaining vertices of a tree $ (v≠u) $ . As you could guess there are $ n(n-1) $ variants of choosing vertices by players. After that players calculate the value of a function $ f(u,v)=φ(a_{u}·a_{v}) $ $ · $ $ d(u,v) $ of the chosen vertices where $ φ(x) $ is Euler's totient function and $ d(x,y) $ is the shortest distance between vertices $ x $ and $ y $ in a tree.

Soon the game became boring for Noora, so Leha decided to defuse the situation and calculate expected value of function $ f $ over all variants of choosing vertices $ u $ and $ v $ , hoping of at least somehow surprise the girl.

Leha asks for your help in calculating this expected value. Let this value be representable in the form of an irreducible fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809E/2c40be71c60fe708ee9e4e80e2cd7a26163f3bd6.png). To further surprise Noora, he wants to name her the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809E/e621f869f3b1e6ca6c81000c1f17dc3c0088747c.png).

Help Leha!

## 说明/提示

Euler's totient function $ φ(n) $ is the number of such $ i $ that $ 1<=i<=n $ ,and $ gcd(i,n)=1 $ , where $ gcd(x,y) $ is the greatest common divisor of numbers $ x $ and $ y $ .

There are $ 6 $ variants of choosing vertices by Leha and Noora in the first testcase:

- $ u=1 $ , $ v=2 $ , $ f(1,2)=φ(a_{1}·a_{2})·d(1,2)=φ(1·2)·1=φ(2)=1 $
- $ u=2 $ , $ v=1 $ , $ f(2,1)=f(1,2)=1 $
- $ u=1 $ , $ v=3 $ , $ f(1,3)=φ(a_{1}·a_{3})·d(1,3)=φ(1·3)·2=2φ(3)=4 $
- $ u=3 $ , $ v=1 $ , $ f(3,1)=f(1,3)=4 $
- $ u=2 $ , $ v=3 $ , $ f(2,3)=φ(a_{2}·a_{3})·d(2,3)=φ(2·3)·1=φ(6)=2 $
- $ u=3 $ , $ v=2 $ , $ f(3,2)=f(2,3)=2 $

Expected value equals to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809E/fd763e469519b65bfd50af11acb740e2ea841c2a.png). The value Leha wants to name Noora is $ 7·3^{-1}=7·333333336=333333338 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809E/23c9d8b560378dc3e1bda3c6cf2ad52a14105af7.png).

In the second testcase expected value equals to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809E/cfbdadeb4c85e39ef43a1fbfa72abe8eae49472c.png), so Leha will have to surprise Hoora by number $ 8·1^{-1}=8 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809E/23c9d8b560378dc3e1bda3c6cf2ad52a14105af7.png).

## 样例 #1

### 输入

```
3
1 2 3
1 2
2 3
```

### 输出

```
333333338
```

## 样例 #2

### 输入

```
5
5 4 3 1 2
3 5
1 2
4 3
2 5
```

### 输出

```
8
```

# 题解

## 作者：Soulist (赞：24)

套路得一麻批

题意：

给一颗树，求：

$$\frac{1}{n(n-1)}\sum_{i=1}^n\sum_{j=1}^n\varphi(a_i*a_j)·dist(i,j)$$

对$10^9+7$取模

首先我们知道

$$\varphi(x)=x*\prod_{p|x}(1-\dfrac{1}{p})$$

所以就有：

$$\varphi(x)*\varphi(y)=x*y*\prod_{p|x}(1-\dfrac{1}{p})*\prod_{p|y}(1-\dfrac{1}{p})$$

设$k=gcd(x,y)$

我们假装让$\varphi(x)*\varphi(y)=\varphi(xy)=x*y*\prod_{p|xy}(1-\dfrac{1}{p})$

不难发现有少乘的嫌疑...

被少计算的是$gcd$质因数分解后的那些因数，所以我们可以得出：

$$\varphi(xy)=\dfrac{\varphi(x)*\varphi(y)*gcd(x,y)}{\varphi(gcd(x,y))}$$

忽略掉前面的系数，我们知道我们要求的是：

$$\sum_{i=1}^n\sum_{j=1}^n\dfrac{\varphi(a_i)*\varphi(a_j)*gcd(a_i,a_j)}{\varphi(gcd(a_i,a_j))}·dist(i,j)$$

$$\sum_{i=1}^n\sum_{j=1}^n\dfrac{\varphi(a_i)*\varphi(a_j)*gcd(a_i,a_j)}{\varphi(gcd(a_i,a_j))}(dep_x+dep_y-dep_{lca})$$

这样做显然很不好做

我们考虑枚举$gcd$，可以发现每个$gcd$对答案造成的贡献固定

于是就有：

$$\sum_{d=1}^n\dfrac{d}{\varphi(d)}\sum_{i=1}^n\sum_{j=1}^n\varphi(a_i)\varphi(a_j)(gcd(a_i,a_j)==d)dist(i,j)$$

看到了一个恰好等于...

我们考虑记

$$f(d)=\sum_{i=1}^n\sum_{j=1}^n\varphi(a_i)\varphi(a_j)(gcd(a_i,a_j)==d)dist(i,j)$$

假装有：

$$F(x)=\sum_{x|d}f(d)$$

我们考虑求解$F(x)$

不难发现

$$F(x)=\sum_{i=1}^n\sum_{j=1}^n\varphi(a_i)\varphi(a_j)[x|gcd(a_i,a_j)]dist(i,j)$$

且有：

$$f(x)=\sum_{x|d}F(d)*\mu(\dfrac{d}{x})$$

可以发现涉及到的点可以直接枚举出来，而且因为$a$为$1-n$的排列，所以涉及到的点的总数应该是可以由调和级数得到为$O(n\log n)$的

于是我们枚举$x$，对于所有$x|d$的点拿下来建虚树，中间那个艾弗森括号就可以忽略了

现在式子变成，给的$m$个点，点有点权，求：

$$\sum_{i=1}^m\sum_{j=1}^mv_i*v_j*dist(i,j)$$

$$\sum_{i=1}^m\sum_{j=1}^mv_i*v_j*(dep_i+dep_j-2*dep_{lca})$$

设$s=v_i*v_j$

$$\sum_{i=1}^m\sum_{j=1}^ms*dep_i+s*dep_j-2*s*dep_{lca}$$

我们将其拆成$3$个$\sum$的形式

$$\sum_{i=1}^m\sum_{j=1}^mv_i*v_j*dep_i+\sum_{i=1}^m\sum_{j=1}^mv_i*v_j*dep_j-2\sum_{i=1}^m\sum_{j=1}^mv_i*v_j*dep_{lca}$$

不难发现前面两个是相同的

$$2\sum_{i=1}^mv_i*dep_i\sum_{j=1}^mv_j-2*\sum_{i=1}^m\sum_{j=1}^mv_i*v_j*dep_{lca}$$

前面那个显然是可以$O(m)$预处理出来的

于是问题的关键就在于后面那一坨

我们考虑在虚树上$dp$，可以发现只需要在$lca$处合并答案即可，所以记$dp_i$表示$i$内部的子树权值总和即可，复杂度同样$O(m)$

当然建立虚树的复杂度是带$\log$的，所以总复杂度为$O(n\log^2n)$ 

qwq

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int N = 4e5 + 5 ; 
const int P = 1e9 + 7 ;
int n, cnt, head[N], w[N], rev[N], vis[N], dp[N], Ans ; 
int phi[N], mu[N], p[N], F[N], f[N], top, s[N] ; 
int dfn[N], Fa[N], dep[N], sz[N], Son[N], Top[N], idnex ; 
bool isp[N] ; 
struct E {
	int to, next ; 
} e[N * 2] ;
void add( int x, int y ) {
	e[++ cnt] = (E){ y, head[x] }, head[x] = cnt , 
	e[++ cnt] = (E){ x, head[y] }, head[y] = cnt ; 
}
void init() {
	mu[1] = 1, phi[1] = 1 ; rep( i, 2, n ) {
		if( !isp[i] ) phi[i] = i - 1, mu[i] = -1, p[++ top] = i ;
		for( re int j = 1; j <= top && p[j] * i <= n; ++ j ) {
			isp[i * p[j]] = 1 ; 
			if( i % p[j] == 0 ) { phi[i * p[j]] = phi[i] * p[j] ; break ; } 
			phi[i * p[j]] = phi[i] * phi[p[j]], mu[i * p[j]] = - mu[i] ; 
		}
	}
}
inline void dfs( int x, int fa ) {
	dfn[x] = ++ idnex, Fa[x] = fa, dep[x] = dep[fa] + 1, sz[x] = 1 ; 
	Next( i, x ) {
		int v = e[i].to ; if( v == fa ) continue ; 
		dfs( v, x ), sz[x] += sz[v] ;
		if( sz[v] > sz[Son[x]] ) Son[x] = v ; 
	}
}
inline void dfs2( int x, int high ) {
	Top[x] = high ; 
	if( Son[x] ) dfs2( Son[x], high ) ;
	Next( i, x ) {
		int v = e[i].to ; if( v == Fa[x] || v == Son[x] ) continue ; 
		dfs2( v, v ) ; 
	}
}
inline int LCA( int x, int y ) {
	while( Top[x] != Top[y] ) {
		if( dep[Top[x]] < dep[Top[y]] ) swap( x, y ) ;
		x = Fa[Top[x]] ; 
	}
	return ( dep[x] < dep[y] ) ? x : y ; 
}
inline void Dp( int x, int fa ) {
	if( vis[x] ) Ans = ( Ans + 2 * phi[w[x]] * phi[w[x]] * dep[x] % P ) % P, dp[x] = phi[w[x]] ; 
	Next( i, x ) {
		int v = e[i].to ; if( v == fa ) continue ; 
		Dp( v, x ), Ans = ( Ans + 4 * dp[x] * dp[v] % P * dep[x] % P ) % P, 
		dp[x] = ( dp[x] + dp[v] ) % P, dp[v] = 0 ;
	}
	head[x] = 0 ; 
}
int fpow( int x, int k ) {
	int ans = 1, base = x ; 
	while( k ) {
		if( k & 1 ) ans = ( ans * base ) % P ;
		base = ( base * base ) % P, k >>= 1 ;
	}
	return ans ;  
}
int K[N], tot ; 
bool cmp( int x, int y ) {
	return dfn[x] < dfn[y] ; 
} 
void insert( int x ) {
	if( top == 1 && x != 1 ) { s[++ top] = x; return ; }
	int lca = LCA( s[top], x ) ; if( lca == x ) return ; 
	while( top > 1 && dfn[s[top - 1]] > dfn[lca] ) add( s[top - 1], s[top] ), -- top ; 
	if( dfn[lca] < dfn[s[top]] ) add( lca, s[top] ), -- top ; 
	if( dfn[lca] > dfn[s[top]] ) s[++ top] = lca ; 
	s[++ top] = x ; 
}
void input() {
	n = gi(), init(), top = 0 ;
	rep( i, 1, n ) w[i] = gi(), rev[w[i]] = i ; 
	rep( i, 2, n ) add( gi(), gi() ) ; 
	dfs( 1, 1 ), dfs2( 1, 1 ), memset( head, 0, sizeof(head) ) ;
}
void solve() {
	rep( i, 1, n ) {
		if( i > n / 2 ) break ; 
		int Re = 0, Sum = 0 ;
		for( re int j = i; j <= n; j += i ) {
			vis[rev[j]] = 1, Sum = ( Sum + phi[j] * dep[rev[j]] % P ) % P,  
			Re = ( Re + phi[j] ) % P, K[++ tot] = rev[j] ; 
		}
		sort( K + 1, K + tot + 1, cmp ), s[top = 1] = 1 ;
		rep( i, 1, tot ) insert( K[i] ) ;
		while( top > 1 ) add( s[top - 1], s[top] ), -- top ; 
		Sum *= Re, Sum %= P, Dp( 1, 1 ), dp[1] = head[1] = 0, F[i] = ( Sum * 2 - Ans + P ) % P ;
		for( re int j = i; j <= n; j += i ) vis[rev[j]] = 0 ; Ans = 0, tot = 0, cnt = 0 ;
	}
}
void Get_F() {
	rep( i, 1, n ) for( re int j = i; j <= n; j += i ) 
	f[i] += F[j] * mu[j / i], f[i] = ( f[i] + P ) % P ;
	rep( i, 1, n ) Ans = ( Ans + i * fpow( phi[i], P - 2 ) % P * f[i] ) % P ; 
	int Ks = Ans * fpow( n, P - 2 ) % P ; Ks = Ks * fpow( n - 1, P - 2 ) % P ;
	printf("%I64d\n", ( Ks + P ) % P ) ;
}
signed main()
{
	input(), solve(), Get_F() ; 
	return 0 ;
}
```

---

## 作者：GKxx (赞：8)

半节政治课把这题推出来了。

$ans=\frac{1}{n(n-1)}\sum\limits_{i=1}^n\sum\limits_{j=1}^n\varphi(a_ia_j)dist(i,j)$

注意到$a_i$是$1$到$n$的排列，因此为了方便可以设$p_{a_i}=i$，那么

$ans=\frac{1}{n(n-1)}\sum\limits_{i=1}^n\sum\limits_{j=1}^n\varphi(ij)dist(p_i,p_j)$

如果把欧拉函数$\varphi(n)$按照$\varphi(n)=n\prod(1-\frac{1}{q_i})$（$q_i$是$n$的质因子）展开，考虑重复的质因子的贡献，不难发现

$\varphi(xy)=\frac{\varphi(x)\varphi(y)\gcd(x,y)}{\varphi(\gcd(x,y))}$

于是

$ans=\frac{1}{n(n-1)}\sum\limits_{i=1}^n\sum\limits_{j=1}^n\frac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}dist(p_i,p_j)$

按套路枚举$\gcd$并反演

$ans=\frac{1}{n(n-1)}\sum\limits_{d=1}^n\frac{d}{\varphi(d)}\sum\limits_{i=1}^n\sum\limits_{j=1}^n\varphi(i)\varphi(j)dist(p_i,p_j)[\gcd(i,j)=d]$

$=\frac{1}{n(n-1)}\sum\limits_{d=1}^n\frac{d}{\varphi(d)}\sum\limits_{k=1}^{\lfloor \frac{n}{d}\rfloor}\mu(k)\sum\limits_{i=1}^{\lfloor\frac{n}{dk}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{n}{dk}\rfloor}\varphi(idk)\varphi(jdk)dist(p_{idk},p_{jdk})$

枚举$T=dk$

$ans=\frac{1}{n(n-1)}\sum\limits_{T=1}^n\sum\limits_{d|T}\frac{d\mu(\frac{T}{d})}{\varphi(d)}\sum\limits_{i=1}^{\lfloor\frac{n}{T}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{n}{T}\rfloor}\varphi(iT)\varphi(jT)dist(p_{iT},p_{jT})$

式子推到这里就行了。首先$\sum\limits_{d|T}\frac{d\mu(\frac{T}{d})}{\varphi(d)}$是关于$T$的函数，可以枚举$d$再枚举它的倍数来$O(n\log n)$预处理。至于这里的$\mu$和$\varphi$，可以用埃氏筛或者线性筛预处理。

再看后面那一串，发现我们可以把所有点权是$T$的倍数的点都找出来建虚树，所有虚树的总点数是$O(n+\frac{n}{2}+\frac{n}{3}+...+\frac{n}{n})=O(n\log n)$，可以承受。

于是下面的问题就是，给一棵树，求出

$\sum\limits_i\sum\limits_jb_ib_jdist(i,j)$

其中$b_i=\varphi(a_i)[T|a_i]$（这里要小心，虚树上除了关键点外的点权为0）

据说这是个很简单的$DP$，不过我还是大力推了一波式子...

树形$DP$的话，考虑合并两棵子树的答案![](https://cdn.luogu.com.cn/upload/pic/46105.png)

设$X,V$分别表示以$x,v$为根的子树，$g_x$表示以$x$为根的子树的答案，那么$g_x=g_x+g_v+w(x,v)$，其中

$w(x,v)=\sum\limits_{i\in X}\sum\limits_{j\in V}b_ib_jdist(i,j)$

$=\sum\limits_{i\in X}b_i\sum\limits_{j\in V}b_jdist(i,j)$

$=\sum\limits_{i\in X}b_i\sum\limits_{j\in V}b_j(dist(i,x)+len+dist(v,j))$

$=(\sum\limits_{i\in X}b_idist(i,x)\sum\limits_{j\in V}b_j)+(len\sum\limits_{i\in X}b_i\sum\limits_{j\in V}b_j)+(\sum\limits_{i\in X}b_i\sum\limits_{j\in V}b_jdist(v,j))$

于是我们把$i$和$x$，$j$和$V$都放到了一起。如果设

$f_x=\sum\limits_{i\in X}b_idist(i,x)$

$s_x=\sum\limits_{i\in X}b_i$，

那么$w(x,v)=f_xs_v+lens_xs_v+s_xf_v$，就可以转移了。至于$f$和$s$的转移也很方便，$f_x=f_x+f_v+lens_v,\ s_x=s_x+s_v$

于是这道题就做完了。

求$LCA$建虚树的部分，我用的是欧拉序+ST表，貌似比倍增快很多（因为要频繁求$LCA$）

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

template <typename T> inline void read(T& t) {
    int f = 0, c = getchar(); t = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
    if (f) t = -t;
}
template <typename T> void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> inline void writeln(T x) { write(x); puts(""); }
template <typename T> inline bool chkmin(T &x, const T &y) { return y < x ? (x = y, 1) : 0; }
template <typename T> inline bool chkmax(T &x, const T &y) { return x < y ? (x = y, 1) : 0; }

typedef long long LL;
const int maxn = 2e5 + 207;
const LL mod = 1e9 + 7;

struct Tree {
    int v[maxn << 1], w[maxn << 1], head[maxn], next[maxn << 1], tot;
    void ae(int x, int y, int z = 0) {
        v[++tot] = y; w[tot] = z; next[tot] = head[x]; head[x] = tot;
        v[++tot] = x; w[tot] = z; next[tot] = head[y]; head[y] = tot;
    }
};
Tree T, V;
int dep[maxn], st[maxn], ed[maxn], euler[maxn << 2], xys;
int md[30][maxn << 2], lg[maxn << 2];
int p[maxn];

void dfs1(int x, int fa) {
    dep[x] = dep[fa] + 1;
    euler[++xys] = x;
    st[x] = xys;
    for (int i = T.head[x], v = T.v[i]; i; i = T.next[i], v = T.v[i])
        if (v != fa) { dfs1(v, x); euler[++xys] = x; }
    ed[x] = xys;
}
inline void init() {
    for (int i = 2; i <= xys; ++i) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= xys; ++i) md[0][i] = euler[i];
    for (int j = 1; 1 << j <= xys; ++j)
        for (int i = 1; i + (1 << j) - 1 <= xys; ++i) {
            int k = i + (1 << (j - 1));
            if (dep[md[j - 1][i]] < dep[md[j - 1][k]])
                md[j][i] = md[j - 1][i];
            else
                md[j][i] = md[j - 1][k];
        }
}
inline int getlca(int x, int y) {
    int l = st[x], r = ed[y];
    if (l > r) l = st[y], r = ed[x];
    int k = lg[r - l + 1], t = r - (1 << k) + 1;
    return dep[md[k][l]] < dep[md[k][t]] ? md[k][l] : md[k][t];
}
inline int getdist(int x, int y) { return dep[x] + dep[y] - (dep[getlca(x, y)] << 1); }

LL tmp[maxn], invphi[maxn];
int phi[maxn];
int mu[maxn], pri[maxn];
bool ff[maxn];

inline LL qpow(LL x, LL k) {
    LL s = 1;
    for (; k; x = x * x % mod, k >>= 1)
        if (k & 1) s = s * x % mod;
    return s;
}
inline void sieve(int n) {
    mu[1] = phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!ff[i]) { phi[i] = i - 1; mu[i] = -1; pri[++pri[0]] = i; }
        for (int j = 1; j <= pri[0]; ++j) {
            int x = i * pri[j];
            if (x > n) break;
            ff[x] = 1;
            if (i % pri[j]) {
                mu[x] = -mu[i];
                phi[x] = phi[i] * phi[pri[j]];
            } else {
                mu[x] = 0;
                phi[x] = phi[i] * pri[j];
                break;
            }
        }
    }
}

inline bool cmp(int a, int b) { return st[a] < st[b]; }

int stk[maxn], top;
int vs[maxn], vk;
inline void insert(int x) {
    if (!top) { stk[++top] = x; return; }
    int l = getlca(x, stk[top]);
    while (top > 1 && dep[stk[top - 1]] > dep[l]) {
        int u = stk[top - 1], v = stk[top];
        V.ae(u, v, getdist(u, v));
        --top;
    }
    if (dep[l] < dep[stk[top]]) {
        V.ae(l, stk[top], getdist(l, stk[top]));
        --top;
    }
    if (!top || dep[stk[top]] < dep[l]) stk[++top] = l;
    stk[++top] = x;
}
inline void build() {
    std::sort(vs + 1, vs + vk + 1, cmp);
    top = 0;
    if (vs[1] != 1) stk[top = 1] = 1;
    V.tot = 0;
    for (int i = 1; i <= vk; ++i) insert(vs[i]);
    while (top > 1) {
        int u = stk[top], v = stk[top - 1];
        V.ae(u, v, getdist(u, v));
        --top;
    }
}

LL f[maxn], g[maxn], s[maxn];
int b[maxn], a[maxn];

void dfs2(int x, int ffa) {
    f[x] = g[x] = 0;
    s[x] = b[x];
    for (int i = V.head[x]; i; i = V.next[i]) {
        int v = V.v[i], w = V.w[i];
        if (v != ffa) {
            dfs2(v, x);
            g[x] = (g[x] + g[v] + s[v] * (f[x] + s[x] * w % mod) % mod + f[v] * s[x] % mod) % mod;
            s[x] = (s[x] + s[v]) % mod;
            f[x] = (f[x] + f[v] + s[v] * w % mod) % mod;
        }
    }
    V.head[x] = 0;
    b[x] = 0;
}

int n;

int main() {
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]), p[a[i]] = i, T.head[i] = 0;
    T.tot = 0;
    for (int i = 1; i != n; ++i) {
        int x, y; read(x); read(y); T.ae(x, y);
    }
    dfs1(1, 0);
    init();
    sieve(n);
    for (int i = 1; i <= n; ++i) invphi[i] = qpow(phi[i], mod - 2);
    for (int d = 1; d <= n; ++d)
        for (int i = d; i <= n; i += d) {
            tmp[i] = (tmp[i] + 1ll * d * mu[i / d] % mod * invphi[d] % mod) % mod;
            if (tmp[i] < 0) tmp[i] += mod;
        }
    LL ans = 0;
    for (int i = 1; i <= n; ++i) {
        vk = 0;
        for (int j = i; j <= n; j += i) {
            vs[++vk] = p[j];
            b[p[j]] = phi[j];
        }
        build();
        dfs2(1, 0);
        ans = (ans + tmp[i] * 2ll * g[1] % mod) % mod;
    }
    ans = ans * qpow(n, mod - 2) % mod * qpow(n - 1, mod - 2) % mod;
    writeln(ans);
    return 0;
}
```

---

## 作者：zyc070419 (赞：4)

## CF809E Surprise me!

#### 前言

蒟蒻很少的完全独立做出来的 $\texttt{CF3100}$ 的题目，写篇题解纪念一下，而且感觉思路和题解区不太一样。

#### 题解

然后我们来考虑一下这道题，本题要求
$$
\dfrac{1}{n\times (n-1)}\sum_{i}\sum_{i\not= j}\varphi(a_i\times a_j)\times dis(i,j)
$$
因为这里面有一个 $dis(i,j)$ 跟数论的式子没一点儿关系，所以说尝试先把 $dis(i,j)$ 拆一下，一般来说就拆成 $depth_i+depth_j-2\times depth_{lca(i,j)}$。然后乘法分配律一下就变成了三部分：
$$
\dfrac{1}{n\times (n-1)}\sum_{i}\sum_{i\not= j}\varphi(a_i\times a_j)\times depth_i\\
\dfrac{1}{n\times (n-1)}\sum_{i}\sum_{i\not= j}\varphi(a_i\times a_j)\times depth_j\\
\dfrac{1}{n\times (n-1)}\sum_{i}\sum_{i\not= j}\varphi(a_i\times a_j)\times depth_{lca(i,j)}
$$
容易发现前两个式子本质是一样的，所以说其实这道题就分成了两部分，分开考虑如何计算。

先说一下，有一个比较常见的套路就是 $\varphi(i\times j)=\dfrac{\varphi(i)\times \varphi(j)\times \gcd(i,j)}{\varphi(\gcd(i,j))}$，证明的话就是把欧拉函数的计算式搞出来，然后对应一下 $\varphi(i\times j)$ 和 $\varphi(i),\varphi(j)$ 的算式推一推就行，其他题解也有证明这里就不叙说了。

对于第一部分，可以比较套路的拆式子莫反即可，大概就是（记 $a_{pos_i}=i$）：
$$
\begin{aligned}
 &\dfrac{1}{n\times (n-1)}\sum_{i}\sum_{i\not= j}\varphi(a_i\times a_j)\times depth_i\\
=&\dfrac{1}{n\times (n-1)}\sum_{k=1}^{n}\dfrac{k}{\varphi(k)}\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\varphi(ik)\times depth_{pos_{ik}}\sum_{j=1}^{\lfloor\frac{n}{k}\rfloor}\varphi(jk)\sum_{d|i,d|j}\mu(d)\\
=&\dfrac{1}{n\times (n-1)}\sum_{k=1}^{n}\dfrac{k}{\varphi(k)}\sum_{d=1}^{\lfloor\frac{n}{k}\rfloor}\mu(d)\sum_{i=1}^{\lfloor\frac{n}{kd}\rfloor}\varphi(ikd)\times depth_{pos_{ikd}}\sum_{j=1}^{\lfloor\frac{n}{kd}\rfloor}\varphi(jkd)\\
=&\dfrac{1}{n\times (n-1)}\sum_{D=1}^{n}\sum_{d|D}\dfrac{d\times \mu(\frac{D}{d})}{\varphi(d)}\sum_{i=1}^{\lfloor\frac{n}{D}\rfloor}\varphi(iD)\times depth_{pos_{iD}}\sum_{j=1}^{\lfloor\frac{n}{D}\rfloor}\varphi(jD)\\
\end{aligned}
$$
如果我们记 $val_D=\sum_{d|i}\dfrac{d\times \mu(\frac{D}{d})}{\varphi(d)}$，上面的式子就相当于：
$$
\dfrac{1}{n\times (n-1)}\sum_{i=1}^{n}val_i\sum_{ij\le n}\varphi(ij)\times depth_{pos_{ij}}\sum_{ik\le n}\varphi(ik)
$$
然后由于 $val$ 可以 $\mathcal O(n\log n)$ 预处理，上面这个式子也可以 $\mathcal O(n\log n)$ 计算，所以第一部分总的复杂度就是 $\mathcal O(n\log n)$。当然这一部分应该是能做到更优的复杂度的，可以欧拉筛筛一下 $val$，然后最后一步的式子也可以数论分块做到 $\mathcal O(n+\sqrt n)$，但是本题瓶颈并不在这里就没这个必要了。

对于第二部分，因为式子中跟 $lca$ 有关，所以说我们将它放到树上去做，即我们对于树上的每一个节点 $x$ 算出来以 $x$ 作为 $lca$ 的点对 $i,j$ 的答案，即对于每个店我们要快速计算（记 $son_{x,i}$ 表示 $x$ 的第 $i$ 个儿子，$subtree(x)$ 表示以 $x$ 为跟的子树内的点的集合，$num_x$ 表示 $x$ 的儿子的数量）：
$$
depth_{x}(\sum_{i=1}^{num_x}\sum_{j=1}^{i-1}\sum_{p\in subteee(son_{x,i})}\sum_{q\in subtree(son_{x,j})}\varphi(a_p\times a_q)+\sum_{p\in subtree(x),p\not= x}\varphi(a_p\times a_x))
$$
换句话说就是进行 $\mathcal O(num_x)$ 次操作，每次操作内容为给定两个数集，求从两个数集中选两个数 $x,y$ 并计算所有选择方案中 $\varphi(x\times y)$ 的和。

因为其实上面的操作本质就是两个集合的合并，然后就能想到树上启发式合并，那么问题就变成了给定一个数 $p$ 和一个数集 $S$，快速求出 $\sum_{q\in S}\varphi(pq)$，还是先推一下式子：
$$
\begin{aligned}
 &\sum_{q\in S}\varphi(pq)\\
=&p\sum_{k|p}\dfrac{k}{\varphi(k)}\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}[ik\in S]\varphi(ik)\sum_{d|i}\mu(d)\\
=&p\sum_{k|p}\dfrac{k}{\varphi(k)}\sum_{kd|p}\mu(d)\sum_{i=1}^{\lfloor\frac{n}{kd}\rfloor}[ikd\in S]\varphi(ikd)\\
=&p\sum_{D|p}\sum_{d|D}\dfrac{d\times \mu(\frac{D}{d})}{\varphi(d)}\sum_{i=1}^{\lfloor\frac{n}{D}\rfloor}[iD\in S]\varphi(iD)\\
=&p\sum_{D|p}val_D\sum_{i=1}^{\lfloor\frac{n}{D}\rfloor}[iD\in S]\varphi(iD)\\
\end{aligned}
$$
所以说只要我们能维护 $S$ 中所有是 $D$ 的倍数的数的 $\varphi$ 值的和就能在 $\mathcal O(d(p))$ 的复杂度内完成这个任务，而显然维护这个和是轻松的，能在 $\mathcal O(d(q))$ 的复杂度内完成，所以说这一部分的复杂度就是$\mathcal O(\log n\sum d(i))$，其实还挺快的。

综上，这道题的复杂度就是 $\mathcal O(n\log n+\log n\sum d(i))$，代码在[这里](https://www.luogu.com.cn/paste/q0a6jusx)，拿下了最优解。

---

## 作者：Liuxizai (赞：3)

[My Blog](https://liuxizai.ac.cn/archives/solutions-2024-1.html)

由于本题值域较小，时限较宽松，我们可以有一些对数学没啥要求，比较暴力的做法。

考虑点分治，处理所有跨过分治中心的路径。

现在我们需要计算 $i$ 对路径权值和的贡献。考虑 $\varphi(a_i\cdot a_j)\operatorname{dis}(i,j)$，由于已经做了点分治，式子可以化为 $\varphi(a_i\cdot a_j)(dep_i+dep_j)$，这里关于 $i$ 的项不方便完全提取出来，我们先将其化为 $\varphi(a_i)\cdot dep_i\cdot\frac{\varphi(a_i\cdot a_j)}{\varphi(a_i)}$。注意 $\frac{\varphi(a_i\cdot a_j)}{\varphi(a_i)}$ 并不等于 $\varphi(a_j)$，但是我们知道两式之间不一样的因式取决于 $a_i$ 和 $a_j$ 的公共质因子。具体来说，如果 $a_i$ 和 $a_j$ 有公共质因子 $p$，则 $\frac{\varphi(a_i\cdot a_j)}{\varphi(a_i)}$ 会将 $\varphi(a_j)$ 中 $(1-\frac1p)$ 的因式去掉，因为这个因式已经在 $\varphi(a_i)$ 中算过了。

注意 $1\le a_i\le 2\times 10^5$，这意味着 $a_i$ 的质因子个数不超过 $6$ 个，我们直接枚举 $a_i$ 和 $a_j$ 有哪些公共质因子。如果当前枚举的公共质因子的乘积为 $p_0$，我们查询满足 $p_0\mid a_j$ 的 $\varphi(a_j)$ 之和，这里只能做到确定 $a_i$ 和 $a_j$ 的公共质因子包含现在枚举的这些数，所以还需要使用 FMT 进行一步容斥。接下来我们就知道了满足 $a_i$ 与 $a_j$ 的所有公共质因子恰好是某个集合的 $\varphi(a_j)$ 之和，从中除去对应的 $(1-\frac1p)$ 然后贡献到答案中即可。

总复杂度为 $O(n\log n\cdot \omega(n)2^{\omega(n)})$，其中用 $\omega(n)$ 表示 $\le n$ 的正整数最多有多少个质因子，本题中 $\omega(n)=6$。瓶颈在 FMT，不知道有没有办法去掉。

[Submission #240300581](https://codeforces.com/contest/809/submission/240300581)


---

## 作者：Weng_Weijie (赞：3)

题解：

$$ Ans = \frac{1}{n(n-1)}\sum_{i=1}^n\sum_{j=1}^n\varphi(a_ia_j)dist(i,j) $$

根据$\varphi$的通项和考虑重复质因子贡献得到 $$ \varphi(ij) = \frac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}$$

$$\sum_{i=1}^n\sum_{j=1}^n\varphi(a_ia_j)dist(i,j)=\sum_{i=1}^n\sum_{j=1}^n\frac{\varphi(a_i)\varphi(a_j)\gcd(a_i,a_j)}{\varphi(\gcd(a_i,a_j))}dist(i,j) $$

枚举 $\gcd$

$$ \sum_{d=1}^n\frac{d}{\varphi(d)}\sum_{i=1}^n\sum_{j=1}^n[\gcd(a_i,a_j)=d]\varphi(a_i)\varphi(a_j)dist(i,j)$$

莫比乌斯反演

$$\sum_{d=1}^n\frac{d}{\varphi(d)}\sum_{k=1}^n\mu(k)\sum_{kd|a_i}\sum_{kd|a_j}\varphi(a_i)\varphi(a_j)dist(i,j)$$

枚举 $kd$

$$\sum_{T=1}^n\sum_{d|T}\frac{d\mu(\frac{T}{d})}{\varphi(d)}\sum_{T|a_i}\sum_{T|a_j}\varphi(a_i)\varphi(a_j)dist(i,j)$$

然后后面的东西可以通过拉出权值为T的倍数的点做树形dp求，需要建虚树

发现总点数是 $O(n\log n)$ 个, 于是时间复杂度是 $O(n\log^2n)$

代码：
```cpp
#include <cstdio>
#include <algorithm>
#define N 200005
const int mod = 1000000007;
using LL = long long;
namespace tree {
	
struct edge { int to, nxt; } e[N << 1];
int head[N], tot, n, a[N], f[18][N], dep[N], idx, dfn[N];
void addedge(int x, int y) {
	e[++tot] = (edge) { y, head[x] }; head[x] = tot;
	e[++tot] = (edge) { x, head[y] }; head[y] = tot;
}
void dfs0(int x) {
	dfn[x] = ++idx;
	for (int i = 1; i < 18; i++) f[i][x] = f[i - 1][f[i - 1][x]];
	for (int i = head[x]; i; i = e[i].nxt) if (e[i].to != f[0][x]) 
		f[0][e[i].to] = x, dep[e[i].to] = dep[x] + 1, dfs0(e[i].to);
}
int lca(int x, int y) {
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = dep[x] - dep[y]; i; i &= i - 1) x = f[__builtin_ctz(i)][x];
	for (int i = 17; i + 1; i--) if (f[i][x] != f[i][y]) x = f[i][x], y = f[i][y];
	return x == y ? x : f[0][x];
}

}
void up(int &x, int y) { if ((x += y) >= mod) x -= mod; }

namespace number {
	int phi[N], miu[N], pr[N], pt, F[N], inv[N], sie[N];
	int pow(int x, int y) {
		int ans = 1;
		for (; y; y >>= 1, x = static_cast<LL> (x) * x % mod)
			if (y & 1) ans = static_cast<LL> (ans) * x % mod;
		return ans;
	}
	void sieve(int R) {
		phi[1] = miu[1] = 1;
		for (int i = 2; i <= R; i++) {
			if (!sie[i]) phi[i] = i - 1, miu[i] = mod - 1, pr[++pt] = i;
			for (int j = 1, t; j <= pt && (t = i * pr[j]) <= R; j++) {
				sie[t] = 1; 
				if (i % pr[j] == 0) { phi[t] = phi[i] * pr[j], miu[t] = 0; break; }
				phi[t] = phi[i] * (pr[j] - 1), up(miu[t] = 0, mod - miu[i]);
			}
		}
		inv[1] = 1; for (int i = 2; i <= R; i++) inv[i] = static_cast<LL> (inv[mod % i]) * (mod - mod / i) % mod;
		for (int i = 1; i <= R; i++)
			for (int j = i, t = 1; j <= R; j += i, t++)
				up(F[j], static_cast<LL> (i) * inv[phi[i]] % mod * miu[t] % mod);
	}
}
namespace vtree {
	int head[N], tot, size[N], val[N], sum = 0, ans = 0;
	struct edge { int to, nxt, len; } e[N << 1];
	void addedge(int x, int y, int z) {
		e[++tot] = (edge) { y, head[x], z }; head[x] = tot;
		e[++tot] = (edge) { x, head[y], z }; head[y] = tot;
	}
	void addedge(int x, int y) {
		addedge(x, y, std::abs(tree::dep[x] - tree::dep[y]));
	}
	int dfs0(int x, int f) {
		size[x] = 0;
		for (int i = head[x]; i; i = e[i].nxt)
			if (e[i].to != f) up(size[x], dfs0(e[i].to, x)), up(ans, static_cast<LL> (size[e[i].to]) * (sum - size[e[i].to] + mod) % mod * e[i].len * 2 % mod);
		up(size[x], val[x]); val[x] = 0; head[x] = 0;
		return size[x];
	}
}
int query[N], ans, stack[N], top, n, a[N], map[N], x, y;
int main() {
	std::scanf("%d", &n);
	for (int i = 1; i <= n; i++) std::scanf("%d", &a[i]), map[a[i]] = i;
	for (int i = 1; i < n; i++) std::scanf("%d%d", &x, &y), tree::addedge(x, y);
	number::sieve(n), tree::dfs0(1);
	for (int i = 1; i <= n; i++) {
		int tot = 0; vtree::sum = vtree::ans = vtree::tot = 0;
		for (int j = i; j <= n; j += i) query[++tot] = map[j], up(vtree::sum, number::phi[j]), vtree::val[map[j]] = number::phi[j];
		std::sort(query + 1, query + tot + 1, [] (int i, int j) { return tree::dfn[i] < tree::dfn[j]; });
		int rt = query[1];
		for (int j = 2; j <= tot; j++) rt = tree::lca(rt, query[j]);
		stack[top = 1] = rt;
		for (int j = 1; j <= tot; j++) {
			int lca = tree::lca(query[j], stack[top]);
			while (tree::dep[lca] < tree::dep[stack[top - 1]]) vtree::addedge(stack[top], stack[top - 1]), --top;
			if (lca != stack[top]) vtree::addedge(lca, stack[top--]);
			if (stack[top] != lca) stack[++top] = lca;
			if (stack[top] != query[j]) stack[++top] = query[j];
		}
		while (--top) vtree::addedge(stack[top + 1], stack[top]);
		vtree::dfs0(rt, 0);
		up(ans, static_cast<LL> (number::F[i]) * vtree::ans % mod);
	}
	std::printf("%d\n", static_cast<LL> (ans) * number::pow(static_cast<LL> (n) * (n - 1) % mod, mod - 2) % mod);
	
	return 0;
}
```



---

## 作者：Nemlit (赞：2)

我们要求的柿子是张这样子的：

$$\frac{1}{n * (n - 1)} * \sum_{i = 1}^n\sum_{j = 1}^{n}\phi(a_i*a_j)*dis(i, j)$$

其中$a_i$为一个排列，$dis(i, j)$表示在树上的距离

这种题的套路一般是先拆柿子，但是这道题的式子……

我们要从一个性质下手：
$$\phi(a * b) = \frac{\phi(a) * \phi(b) * gcd(a, b)}{\phi(gcd(a, b))}$$

代入原式得：

$$\frac{1}{n * (n - 1)} * \sum_{i = 1}^n\sum_{j = 1}^{n}\frac{\phi(a_i) * \phi(a_j) * gcd(a_i, a_j)}{\phi(gcd(a_i, a_j))}*dis(i, j)$$

先忽略前面的数，只看后面的$\sum$，枚举$gcd(a_i, a_j)$，得到

$$\sum_{k = 1}^n\frac{k}{\phi(k)}\sum_{i = 1}^n\sum_{j = 1}^{n}\phi(a_i) * \phi(a_j)*dis(i, j)*[gcd(a_i, a_j) == k]$$

然后反演一波，得到：

$$\sum_{k = 1}^n\frac{k}{\phi(k)}\sum_{i = 1}^n\sum_{j = 1}^{n}\phi(a_i) * \phi(a_j)*dis(i, j)*\sum_{(x * k|a[i]) \& (x * k | a[j])}\mu(x)$$

枚举$k * x$

$$\sum_{T = 1}^n\sum_{k|T}\frac{k}{\phi(k)}\sum_{i = 1}^n\sum_{j = 1}^{n}\phi(a_i) * \phi(a_j)*dis(i, j)*\sum_{(T|a[i]) \& (T | a[j])}\mu(\frac{T}{k})$$

交换顺序得：
$$\sum_{T = 1}^n\sum_{k|T}\frac{k}{\phi(k)} * \mu(\frac{T}{k})\sum_{a[i]\ |\ T}\sum_{a[j]\ |\ T}\phi(a_i) * \phi(a_j)*dis(i, j)$$

我们考虑枚举T，对于后面的柿子，我们可以单独拎出来，对所有$a[i] | T$用树形DP求出后面柿子的答案，前面的柿子可以提前与处理出来

由于虚树的总点数是$(nlogn)$个（并不会证明），所以复杂度正确，但由于虚树上的DP和普通DP有一定差异，所以我们还需要对后面的柿子继续化简

$$\sum_{a[i]\ |\ T}\sum_{a[j]\ |\ T}\phi(a_i) * \phi(a_j)*dis(i, j)$$

拆开$dis(i, j)$得：

$$\sum_{a[i]\ |\ T}\sum_{a[j]\ |\ T}\phi(a_i) * \phi(a_j)*(dep[i] + dep[j] - 2 * dep[lca(i, j)])$$

令$val[i] = \phi(a_i)$，把所有$a[i] | T$拎出来，假设有x个

$$\sum_{i= 1}^{x}\sum_{j = 1}^xval[i] * val[j]*(dep[i] + dep[j] - 2 * dep[lca(i, j)])$$

$$\sum_{i= 1}^{x}\sum_{j = 1}^xval[i] * val[j]*dep[i] + \sum_{i= 1}^{x}\sum_{j = 1}^xval[i] * val[j] * dep[j] -2 *  \sum_{i= 1}^{x}\sum_{j = 1}^xval[i] * val[j] * dep[lca(i, j)])$$
$$2 * \sum_{i= 1}^{x}val[i] *dep[i] \sum_{j = 1}^xval[j]  -2 *  \sum_{i= 1}^{x}\sum_{j = 1}^xval[i] * val[j] * dep[lca(i, j)])$$

前面的柿子可以与处理出来，后面的柿子只需要我们在虚树上枚举lca，求出$\sum_{i= 1}^{x}\sum_{j = 1}^xval[i] * val[j]*[lca(i, j) == lca]$

这个值其实不难求，记录$f(x)= \sum_{i = 1}^xval[i]$即可
## $Code:$
```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define mod 1000000007
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i, s, t) for(re int i = s; i <= t; ++ i)
#define Next(i, u) for(re int i = head[u]; i; i = e[i].next)
#define mem(k, p) memset(k, p, sizeof(k))
#define maxn 400005
int n, m, Go[maxn], head[maxn], cnt, rev[maxn];
struct edge { int v, next; }e[maxn << 1];
il void add(int u, int v) {
    e[++ cnt] = (edge){v, head[u]}, head[u] = cnt;
    e[++ cnt] = (edge){u, head[v]}, head[v] = cnt;
}
il int mul(int a, int b) { return 1ll * a * b % mod; }
il int qpow(int a, int b) {
    int r = 1;
    while(b) {
        if(b & 1) r = mul(a, r);
        a = mul(a, a), b >>= 1;
    }
    return r;
}

int prim[maxn], tot, Vis[maxn], phi[maxn], mu[maxn], F[maxn], ans, G[maxn];
il void init(int n) {
    mu[1] = phi[1] = 1;
    rep(i, 2, n) {
        if(!Vis[i]) prim[++ cnt] = i, mu[i] = -1, phi[i] = i - 1;
        rep(j, 1, cnt) {
            if(i * prim[j] > n) break;
            Vis[i * prim[j]] = 1;
            if(i % prim[j] == 0) {
                phi[i * prim[j]] = phi[i] * prim[j];
                break;
            }
            mu[i * prim[j]] = -mu[i], phi[i * prim[j]] = phi[i] * phi[prim[j]];
        }
    }
    rep(i, 1, n) 
        for(re int j = i; j <= n; j += i) 
        	F[j] = (F[j] + mul(mul(i, qpow(phi[i], mod - 2)), mu[j / i])) % mod, F[j] = (F[j] + mod) % mod;
}

int fa[maxn], dep[maxn], Top[maxn], dfn[maxn], col, son[maxn], size[maxn];
il void dfs1(int u, int fr) {
    size[u] = 1, fa[u] = fr, dep[u] = dep[fr] + 1;
    Next(i, u) {
        int v = e[i].v;
        if(v == fr) continue;
        dfs1(v, u), size[u] += size[v];
        if(size[v] > size[son[u]]) son[u] = v;
    }
}
il void dfs2(int u, int fr) {
    dfn[u] = ++ col, Top[u] = fr;
    if(son[u]) dfs2(son[u], fr);
    Next(i, u) if(e[i].v != fa[u] && e[i].v != son[u]) dfs2(e[i].v, e[i].v);
}
il int LCA(int u, int v) {
    while(Top[u] != Top[v]) dep[Top[u]] > dep[Top[v]] ? u = fa[Top[u]] : v = fa[Top[v]];
    return dep[u] > dep[v] ? v : u;
}

int st[maxn], top, a[maxn], tmp, pax, vis[maxn], f[maxn], val[maxn], g[maxn];
il bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
il void insert(int x) {
    if(top == 1 && x != 1) return (void)(st[++ top] = x);
    int lca = LCA(st[top], x);
    if(x == lca) return;
    while(top > 1 && dep[st[top - 1]] > dep[lca]) {
        add(st[top], st[top - 1]), -- top; 
    }
    if(dep[st[top]] > dep[lca]) add(lca, st[top]), -- top;
    if(dep[st[top]] < dep[lca]) st[++ top] = lca;
    st[++ top] = x;
}
il void build(int n) {
    sort(a + 1, a + n + 1, cmp), st[top = 1] = 1;
    rep(i, 1, n) insert(a[i]);
    while(top > 1) add(st[top - 1], st[top]), -- top;
}
il void get_dis(int u, int fr) {
    if(vis[u]) f[u] = mul(phi[Go[u]], dep[u]), val[u] = phi[Go[u]];
    int sum = val[u];
    Next(i, u) {
        int v = e[i].v;
        if(v == fr) continue;
        get_dis(v, u);
        g[u] = (g[u] + mul(val[v], sum)) % mod;
        sum = (sum + val[v]) % mod;
        f[u] = (f[u] + f[v]) % mod, val[u] = (val[u] + val[v]) % mod;
    }
    g[u] = mul(g[u], dep[u]);
}
il void dfs_mem(int u, int fr) {
    Next(i, u) if(e[i].v != fr) dfs_mem(e[i].v, u);
    tmp = (tmp + g[u]) % mod, head[u] = vis[u] = f[u] = val[u] = g[u] = 0;
}
il void solve() {
    rep(T, 1, n / 2) {
        pax = tmp = cnt = 0;
        for(re int i = T; i <= n; i += T) a[++ pax] = rev[i], vis[rev[i]] = 1;
        build(pax), get_dis(1, 0);
        G[T] = 2ll * mul(f[1], val[1]) % mod;
        dfs_mem(1, 0), tmp = mul(2, tmp);
        rep(i, 1, pax) tmp = (tmp + mul(dep[a[i]], mul(phi[Go[a[i]]], phi[Go[a[i]]]))) % mod;
        G[T] = (G[T] - 2ll * tmp % mod + mod) % mod;
    }
}
int main() {
    n = read(), init(n);
	rep(i, 1, n) Go[i] = read(), rev[Go[i]] = i;
    rep(i, 1, n - 1) add(read(), read());
    dfs1(1, 0), dfs2(1, 1), mem(head, 0), solve();
    rep(i, 1, n) ans = (ans + mul(G[i], F[i])) % mod;
    printf("%d", mul((ans + mod) % mod, qpow(mul(n, n - 1), mod - 2)));
	return 0;
}
```

---

## 作者：xgzc (赞：2)

这道题目的话，推式子比较休闲，写起来。。。

首先上套路，根据$\varphi$的一些性质，我们可以证明$\varphi(ij) = \frac{\varphi(i)\varphi(j)\gcd(i, j)}{\varphi(gcd(i,j))}$。

开推：首先设$\textbf{f}(x) = \frac x {\varphi(x)}, \textbf g = \textbf f * \mu, p_{a_i} = i$，

那么有（我的这种推法是~~学的rqy的~~比较简单的，建议参阅）：

$$\begin{aligned}&\sum_{i=1}^n\sum_{j=1}^n\varphi(a_i*a_j)\cdot \mathrm{dist}(i,j) \\=& \sum_{i=1}^n\sum_{j=1}^n\varphi(i)\varphi(j)\mathrm{dist}(p_i, p_j)\textbf f(\gcd(i,j)) \\=& \sum_{i=1}^n\sum_{j=1}^n\varphi(i)\varphi(j)\mathrm{dist}(p_i, p_j)\sum_{d\mid i, d\mid j} \textbf g(d) \\=& \sum_{d=1}^n\textbf g(d)\sum_{d\mid i}\sum_{d\mid j}\varphi(i)\varphi(j)\mathrm{dist}(p_{i},p_{j})\end{aligned}$$

$\textbf g$可以枚举倍数求，复杂度调和级数。

然后后面那一坨可以枚举倍数，将所有是$d$的倍数的点全部拉出来建一棵虚树，做一遍树形$\mathrm{dp}$就可以了。

虚树的总点数在$\mathrm{O}(n\log n)$级别，所以总复杂度约为$\mathrm{O}(n\log^2n)$

代码见我的[$\texttt{blog}$](https://www.cnblogs.com/cj-xxz/p/10597132.html)

---

## 作者：Fading (赞：1)

很套路的一道题。

不过$sb$错调了一个半小时...

好的我们开始化简式子：

设$b_{a_i}=i$,即树上权值为$a_i$的编号$i$

$$\frac 1{n(n-1)}\sum_{i=1}^n\sum_{j=1}^n\varphi(a_ia_j)dis(i,j)$$

$$\because\varphi(a_ia_j)=\frac {\varphi(a_i)\varphi(a_j)\gcd(a_i,a_j)}{\varphi(\gcd(a_i,a_j)}$$

$$\therefore\ =\frac 1{n(n-1)}\sum_{i=1}^n\sum_{j=1}^n\frac {\varphi(a_i)\varphi(a_j)\gcd(a_i,a_j)}{\varphi(\gcd(a_i,a_j))}dis(i,j)$$

枚举$gcd$

$$=\frac 1{n(n-1)}\sum_{d=1}^n\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)==d]\frac {\varphi(i)\varphi(j)d}{\varphi(d)}dis(b_i,b_j)$$

$$=\frac 1{n(n-1)}\sum_{d=1}^n\frac {d}{\varphi(d)}\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)==d]\varphi(i)\varphi(j)dis(b_i,b_j)$$

$$=\frac 1{n(n-1)}\sum_{d=1}^n\frac {d}{\varphi(d)}\sum_{i=1}^{\lfloor \frac nd\rfloor}\sum_{j=1}^{\lfloor \frac nd\rfloor}[\gcd(i,j)==1]\varphi(id)\varphi(jd)dis(b_i,b_j)$$

$$\frac 1{n(n-1)}\sum_{d=1}^n\frac {d}{\varphi(d)}\sum_{i=1}^{\lfloor \frac nd\rfloor}\sum_{j=1}^{\lfloor \frac nd\rfloor}\sum_{e|i,e|j}\mu(e)\varphi(id)\varphi(jd)dis(b_{id},b_{jd})$$

$$=\frac 1{n(n-1)}\sum_{d=1}^n\frac {d}{\varphi(d)}\sum_{e=1}^{\lfloor \frac nd\rfloor}\mu(e)\sum_{i=1}^{\lfloor\frac n{de}\rfloor}\sum_{j=1}^{\lfloor\frac n{de}\rfloor}\varphi(ide)\varphi(jde)dis(b_{ide},b_{jde})$$

设

$$f(d)=\sum_{e=1}^{\lfloor \frac nd\rfloor}\mu(e)\sum_{i=1}^{\lfloor\frac n{de}\rfloor}\sum_{j=1}^{\lfloor\frac n{de}\rfloor}\varphi(ide)\varphi(jde)dis(b_{ide},b_{jde})$$

套路用完了，然而发现根本没有办法处理？这时候发现右边的项全部都是$ide,jde$，考虑把这个缩成$i,j$?

设$e=ed$

$$f(d)=\sum_{d|e}\mu(\frac ed)\sum_{i=1}^{\lfloor\frac n{e}\rfloor}\sum_{j=1}^{\lfloor\frac n{e}\rfloor}\varphi(ie)\varphi(je)dis(b_{ie},b_{je})$$

设$i=ei,j=ej$

$$f(d)=\sum_{d|e}\mu(\frac ed)\sum_{e|a_i}^{}\sum_{e|a_j}\varphi(i)\varphi(j)dis(b_{i},b_{j})$$

$$f(d)=\sum_{d|e}\mu(\frac ed)\sum_{e|a_i}^{}\sum_{e|a_j}\varphi(a_i)\varphi(a_j)dis(i,j)$$

代入回去

$$=\frac 1{n(n-1)}\sum_{d=1}^n\frac {d}{\varphi(d)}\sum_{d|e}\mu(\frac ed)\sum_{e|a_i}^{}\sum_{e|a_j}\varphi(a_i)\varphi(a_j)dis(i,j)$$

$$=\frac 1{n(n-1)}\sum_{e=1}^n\frac {d\mu(\frac ed)}{\varphi(d)}\sum_{d|e}\sum_{e|a_i}^{}\sum_{e|a_j}\varphi(a_i)\varphi(a_j)dis(i,j)$$

设$g(e)=\sum_{d|e}\frac {d\mu(\frac ed)}{\varphi(d)}$

现在，$g$可以调和级数暴力枚举（也可以线性筛）

怎么求后面的一坨呢？（对于每一个$e$）

发现$e$的倍数是不算特别多的，对于每一个$e$的倍数，只有$\lfloor\frac ne\rfloor$个

所以我们可以对每一个$e$建虚树，复杂度$O(nlog^2_2n)$

考虑这个奇怪的式子：

$$=\sum_{i}^{}\sum_{j}\varphi(a_i)\varphi(a_j)(dep[i]+dep[j]-2dep[lca(i,j)])$$

$$=\sum_{i}\varphi(a_i)dep[i]\cdot\sum_{j}\varphi(a_j)+\sum_{i}\varphi(a_i)\cdot\sum_{j}\varphi(a_j)dep[j]-2\sum_{i}\sum_{j}\varphi(a_i)\varphi(a_j)dep[lca(i,j)]$$

$$=2\sum_{i}\varphi(a_i)dep[i]\cdot\sum_{j}\varphi(a_j)-2\sum_{i}\sum_{j}\varphi(a_i)\varphi(a_j)dep[lca(i,j)]$$

前面这个式子直接出来。

后面这个式子怎么求？类似点分治一样枚举虚树上$lca(i,j)=u$的点

$$\sum_{i}\sum_{j}\varphi(a_i)\varphi(a_j)dep[lca(i,j)]$$

$$=dep[u]\sum_{i}\varphi(a_i)\sum_{j}\varphi(a_j)$$

发现$i,j$属于根节点或者根节点的不同子树，像并查集一样合并，乘一乘，就好了。

细节：不要忘记算上$u$自己的答案！$(u,u)$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 1000000007
using namespace std;
#ifdef Fading
#define gc getchar
#endif
#ifndef Fading
inline char gc(){
	static char now[1<<16],*S,*T;
	if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
	return *S++;
}
#endif
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
struct edge{
    int to,nxt;
}g[1000001];
int tcnt,head[300001],N,tpos[400001][2],dep[500001],f[500001][20],n,m,tot;
inline void made(int from,int to){
    g[++tot].to=to;g[tot].nxt=head[from];head[from]=tot; 
}
void dfs(int u,int fa){
	tpos[u][0]=++tcnt;
    dep[u]=dep[fa]+1;f[u][0]=fa;
    for (int i=1;i<=19;i++) f[u][i]=f[f[u][i-1]][i-1];
    for (int i=head[u];i;i=g[i].nxt){
        int v=g[i].to;
        if (v==fa) continue;
        dfs(v,u);
    }
	tpos[u][1]=++tcnt;
}
inline int lca(int x,int y){
    if (dep[x]<dep[y]) swap(x,y);
    for (int i=19;i>=0;i--){
        if (dep[f[x][i]]>=dep[y]) x=f[x][i];
    }
    if (x==y) return x;
    for (int i=19;i>=0;i--){
        if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    }
    return f[x][0];
}
ll a[300001],yyy,NN,b[300001],mu[300001],inv[300001];
bool vis[300001];
ll phi[300001],G[300001],p[300001];
inline void init(){
	n=read();
	for (int i=1;i<=n;i++) a[i]=read(),b[a[i]]=i;
	for (int i=1;i<n;i++){
		int x=read(),y=read();made(x,y);made(y,x);
	}
	mu[1]=phi[1]=inv[0]=inv[1]=1;
	for (int i=2;i<=n;i++) inv[i]=(ljc-(ljc/i)*inv[ljc%i]%ljc)%ljc;
    for (int i=2;i<=n;i++){
        if (!vis[i]){mu[i]=-1;phi[i]=i-1;p[++yyy]=i;}
        for (int j=1;j<=yyy;j++){
            if (p[j]*i>n) break;
            vis[i*p[j]]=1;
            if (i%p[j]==0){
            	phi[i*p[j]]=p[j]*phi[i];mu[i*p[j]]=0;break;
            }
            mu[i*p[j]]=-mu[i];phi[i*p[j]]=(p[j]-1)*phi[i];
        }
    }
    NN=inv[n]*inv[n-1]%ljc;
	for (int i=1;i<=n;i++){
		for (int j=i;j<=n;j+=i){
			G[j]=(G[j]+1LL*inv[phi[i]]*i%ljc*(ljc+mu[j/i])%ljc)%ljc; 
		}
	}
	dfs(1,0);
}
namespace VT{
	int head[211111],tot;
	ll a[211111],sz[211111];
	struct edge{
		int to,nxt;
	}g[1000001];
	inline void made(int from,int to){
		g[++tot].to=to;g[tot].nxt=head[from];head[from]=tot;
	}
	ll dp(int u){
		sz[u]=phi[a[u]];
		ll NOW=sz[u]*sz[u]%ljc,tmp=0;//NOW先加上自己的答案
		for (int i=head[u];i;i=g[i].nxt){
			int v=g[i].to;
			tmp=(tmp+dp(v))%ljc;//tmp表示子树的答案和
			NOW=(NOW+2*sz[u]*sz[v]%ljc)%ljc;//乘2是由于无序
			sz[u]=(sz[u]+sz[v])%ljc;
		}
		return (NOW*dep[u]%ljc+tmp)%ljc;
	}
}
int sta[1000001],top,has[1000001],que[1000001];
inline bool cmp(int x,int y){
    int k1=(x>0)?tpos[x][0]:tpos[-x][1],k2=(y>0)?tpos[y][0]:tpos[-y][1];
    return k1<k2;
}
signed main(){
	init();
	ll ANS=0;
	for (int i=1;i<=n;i++){
		int L=0;ll now=0,ai=0,dai=0;
		for (int j=i;j<=n;j+=i){
			que[++L]=b[j];has[que[L]]=1;VT::a[b[j]]=j;
			ai=(ai+phi[j])%ljc;
			dai=(dai+phi[j]*dep[b[j]]%ljc)%ljc;
		}
		now=2*dai%ljc*ai%ljc;
		sort(que+1,que+1+L,cmp);
		int cnt=L;
		for (int j=1;j<cnt;j++){
			int lc=lca(que[j],que[j+1]);
			if (!has[lc]) has[lc]=1,que[++L]=lc;
		}
		cnt=L;
		for (int j=1;j<=cnt;j++) que[++L]=-que[j];
		if (!has[1]) que[++L]=1,que[++L]=-1,has[1]=1;
		sort(que+1,que+1+L,cmp);
		for (int j=1;j<=L;j++){
			if (que[j]>0){
				if (top) VT::made(sta[top],que[j]);
				sta[++top]=que[j];
			}else{
				has[sta[top--]]=0;
			}
		}
		VT::tot=0;
		now=(now-2*(VT::dp(1))%ljc+ljc)%ljc;
		for (int j=1;j<=L;j++){
			if (que[j]>0) VT::head[que[j]]=0,VT::a[que[j]]=0;
		}
		ANS=(ANS+now*G[i]%ljc)%ljc;
	}
	cout<<ANS*NN%ljc;
	return 0;
}

```


---

## 作者：_ctz (赞：1)

[安利$blog$](https://ctz45562.github.io/2019/08/05/%E6%B4%9B%E8%B0%B7-CF809E-Surprise-me/)

[传送门](https://www.luogu.org/problem/CF809E)

转换一下$a_i$的定义：权值为$i$的点的编号。

这样求的答案就成了$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\phi(i*j)dis(a_i,a_j)$

反演还是很套路的：

$=\sum\limits_{i=1}^n\sum\limits_{j=1}^n\dfrac{\phi(i)\phi(j)gcd(i,j)}{\phi(gcd(i,j))}dis(a_i,a_j)$

$=\sum\limits_{d=1}^n\dfrac{d}{\phi(d)}\sum\limits_{i=1}^n\phi(i)\sum\limits_{j=1}^n\phi(j)[gcd(i,j)=d]dis(a_i,a_j)$

$=\sum\limits_{d=1}^n\dfrac{d}{\phi(d)}\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\phi(id)\sum\limits_{j=1}^{\lfloor\frac{n}{d}\rfloor}\phi(jd)dis(a_{id},a_{jd})\sum\limits_{a|gcd(i,j)}\mu(a)$

$=\sum\limits_{d=1}^n\dfrac{d}{\phi(d)}\sum\limits_{a=1}^{\lfloor\frac{n}{d}\rfloor}\mu(a)\sum\limits_{i=1}^{\lfloor\frac{n}{ad}\rfloor}\phi(iad)\sum\limits_{j=1}^{\lfloor\frac{n}{ad}\rfloor}\phi(jad)dis(a_{iad},a_{jad})$

令$T=ad$，枚举$T$：

$=\sum\limits_{d=1}^n\dfrac{d}{\phi(d)}\sum\limits_{T=1}^n[d|T]\mu(\dfrac{T}{d})\sum\limits_{i=1}^{\lfloor\frac{n}{T}\rfloor}\phi(iT)\sum\limits_{j=1}^{\lfloor\frac{n}{T}\rfloor}\phi(jT)dis(a_{iT},a_{jT})$

$=\sum\limits_{T=1}^n\sum\limits_{i=1}^{\lfloor\frac{n}{T}\rfloor}\phi(iT)\sum\limits_{j=1}^{\lfloor\frac{n}{T}\rfloor}\phi(jT)dis(a_{iT},a_{jT})\sum\limits_{d|T}\mu(\dfrac{T}{d})\dfrac{d}{\phi(d)}$

最后面$\sum\limits_{d|T}$的一坨是个卷积形式，可以线筛，不过$O(n\log n)$枚举倍数预处理就够了。

看中间那一坨，考虑它的含义，其实就是把编号为$a_{iT}$的点拿出来，点权为$\phi(iT)$，求它们两两之间$value(i)*value(j)*dis(i,j)$之和。

而这个式子是个调和级数，总点数是$O(n\log n)$的，大力对点集$\{a_{iT}|i\in \mathbb{Z}\}$上虚树。

记$siz(i)$为点$i$的子树权值和，考虑每条边$edge(i,j)$的贡献，为$length(edge(i,j))*siz(j)*(siz(root)-siz(j))$。

于是就能$O(n\log^2n)$解决辣。

代码：

``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>

#define maxn 200005
#define inf 0x3f3f3f3f

const int mod = 1e9 + 7;

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
int deep[maxn],seg[maxn],a[maxn],all;
vector<int>p;
bool vis[maxn];
namespace origin{
	int top[maxn],fa[maxn],son[maxn],siz[maxn],h[maxn],num;
	struct edge{
		int pre,to;
	}e[maxn<<1];
	inline void add(int from,int to){
		e[++num].pre=h[from],h[from]=num,e[num].to=to;
	}
	void dfs1(int node=1){
		siz[node]=1;
		int x;
		for(register int i=h[node];i;i=e[i].pre){
			x=e[i].to;
			if(siz[x])continue;
			fa[x]=node,deep[x]=deep[node]+1,dfs1(x),siz[node]+=siz[x];
			if(siz[x]>siz[son[node]])son[node]=x;
		}
	}
	void dfs2(int node=1){
		seg[node]=++all;
		if(son[node]){
			int x=son[node];
			top[x]=top[node],dfs2(x);
			for(register int i=h[node];i;i=e[i].pre){
				x=e[i].to;
				if(!seg[x])top[x]=x,dfs2(x);
			}
		}
	}
	int lca(int x,int y){
		while(top[x]!=top[y])deep[top[x]]<deep[top[y]]?y=fa[top[y]]:x=fa[top[x]];
		return deep[x]<deep[y]?x:y;
	}
}
namespace virt{
	int siz[maxn],h[maxn],num,ans;
	struct edge{
		int pre,to,l;
	}e[maxn<<1];
	inline void add(int from,int to){
		int l=abs(deep[from]-deep[to]);
		e[++num].pre=h[from],h[from]=num,e[num].to=to,e[num].l=l;
		e[++num].pre=h[to],h[to]=num,e[num].to=from,e[num].l=l;
	}
	bool cmp(int x,int y){return seg[x]<seg[y];}
	struct Monostack{
		int sta[maxn],top;
		void push(int x){sta[++top]=x;}
		void clear(){
			for(register int i=2;i<=top;++i)add(sta[i],sta[i-1]);
			top=0;
		}
		void check(int x){
			if(x==1)return;
			int l=origin::lca(x,sta[top]);
			h[x]=0;
			if(l!=sta[top]){
				while(seg[l]<seg[sta[top-1]])add(sta[top],sta[top-1]),--top;
				--top;
				if(l!=sta[top])h[l]=0,add(sta[top+1],l),push(l);
				else add(sta[top+1],l);
			}
			push(x);
		}
	}s;
	void build(){
		h[1]=0,s.push(1);
		for(vector<int>::iterator iter=p.begin();iter!=p.end();++iter)s.check(*iter);
		s.clear();
	}
	void dfs(int node=1,int fa=0){
		if(!vis[node])siz[node]=0;
		int x;
		for(register int i=h[node];i;i=e[i].pre){
			x=e[i].to;
			if(x!=fa)dfs(x,node),(siz[node]+=siz[x])%=mod;
		}
	}
	void calc(int node=1,int fa=0){
		int x;
		for(register int i=h[node];i;i=e[i].pre){
			x=e[i].to;
			if(x!=fa)calc(x,node),(ans+=1ll*e[i].l*siz[x]%mod*(siz[1]-siz[x])%mod)%=mod;
		}
	}
	int solve(){
		sort(p.begin(),p.end(),cmp);
		num=0,ans=0,build(),dfs(),calc();
		for(vector<int>::iterator iter=p.begin();iter!=p.end();++iter)vis[*iter]=siz[*iter]=0;
		return ans;
	}
}
namespace mobius{
	int phi[maxn],mu[maxn],f[maxn],prime[maxn>>2],inv[maxn],cnt;
	bool is[maxn];
	void solve(int n){
		int ans=0;
		is[1]=phi[1]=mu[1]=inv[1]=1;
		for(register int i=2;i<=n;++i){
			inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
			if(!is[i])prime[++cnt]=i,phi[i]=i-1,mu[i]=-1;
			for(register int j=1;j<=cnt&&i*prime[j]<=n;++j){
				is[i*prime[j]]=1;
				if(i%prime[j]==0){
					mu[i*prime[j]]=0,phi[i*prime[j]]=phi[i]*prime[j];
					break;	
				}
				phi[i*prime[j]]=phi[i]*(prime[j]-1),mu[i*prime[j]]=-mu[i];
			}
		}
		for(register int i=1;i<=n;++i)
			for(register int j=i;j<=n;j+=i)
				(f[j]+=1ll*mu[j/i]*i*inv[phi[i]]%mod)%=mod;
		for(register int i=1;i<=n;++i){
			p.clear();
			for(register int j=i;j<=n;j+=i)
				p.push_back(a[j]),vis[a[j]]=1,virt::siz[a[j]]=phi[j];
			(ans+=1ll*virt::solve()*f[i]%mod)%=mod;
		}
		ans=1ll*(ans<<1)*inv[n]%mod*inv[n-1]%mod;
		printf("%d\n",(ans+mod)%mod);
	}
}
int main(){
	using namespace origin;
	int n=read(),x,y;
	for(register int i=1;i<=n;++i)a[read()]=i;
	for(register int i=1;i<n;++i)x=read(),y=read(),add(x,y),add(y,x);
	dfs1(),dfs2();
	mobius::solve(n);
}

```



---

## 作者：p_b_p_b (赞：1)

[$$\large \color{purple} My\;Blog$$](https://www.cnblogs.com/p-b-p-b/p/10644803.html)

---------------------------

非常套路的一道题，很适合我在陷入低谷时提升信心……

------------------------

## 思路

显然我们需要大力推式子。

设$p_{a_i}=i$，则有

$$n(n-1)ans=\sum_i \sum_j \varphi(ij)dis(p_i,p_j)$$
$$=\sum_i \sum_j \frac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))} dis(i,j)$$
$$=\sum_d \frac{d}{\varphi(d)} \sum_i\sum_j [\gcd(i,j)=d]\varphi(i)\varphi(j)dis(i,j)$$
$$=\sum_d \frac{d}{\varphi(d)} \sum_{k=1}^{n/d} \mu(k) \sum_{i=1}^{n/dk} \sum_{j=1}^{n/dk} \varphi(idk)\varphi(jdk)dis(p_{idk},p_{jdk})$$
$$=\sum_{T=1}^n (\sum_{d|T} \frac{d\mu(T/d)}{\varphi(d)})\sum_{i=1}^{n/T} \sum_{j=1}^{n/T} \varphi(iT)\varphi(jT)dis(p_{iT},p_{jT})$$
现在思路已经非常清晰了。

$f(T)=\sum_{d|T}\frac{d\mu(T/d)}{\varphi(d)}$：这显然可以调和级数$O(n\log n)$得到。

现在就是要求

$$X=\sum_{i\in S} \sum_{j\in S} \varphi(i)\varphi(j)dis(p_i,p_j)$$

显然通过调和级数我们发现$\sum|S|$是$O(n\log n)$级别的。

考虑把$dis(p_i,p_j)$拆开，我们得到

$$X=\sum_{i\in S}\sum_{j\in S} \varphi(i)\varphi(j)(dep_{p_i}+dep_{p_j}-2dep_{lca(p_i,p_j)})$$
$$=M-2\sum_{i\in S}\varphi(i)\sum_{j\in S} \varphi(j)dep_{lca(p_i,p_j)}$$
其中$M$可以很容易求出，只需要求出后面。

后面其实是个经典套路，可以用大众化的DP或是用“ [HNOI2015]开店”相同的方法（链上加，求到根的距离）做。

由于我是个SB，我选了后者，写了个树上差分。

然后各种SB错误调了1个小时……

-----------------------------------

## 代码

```cpp
#include<bits/stdc++.h>
clock_t t=clock();
namespace my_std{
	using namespace std;
	#define pii pair<int,int>
	#define fir first
	#define sec second
	#define MP make_pair
	#define rep(i,x,y) for (int i=(x);i<=(y);i++)
	#define drep(i,x,y) for (int i=(x);i>=(y);i--)
	#define go(x) for (int i=head[x];i;i=edge[i].nxt)
	#define templ template<typename T>
	#define sz 202020
	#define mod 1000000007ll
	typedef long long ll;
	typedef double db;
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	templ inline T rnd(T l,T r) {return uniform_int_distribution<T>(l,r)(rng);}
	templ inline bool chkmax(T &x,T y){return x<y?x=y,1:0;}
	templ inline bool chkmin(T &x,T y){return x>y?x=y,1:0;}
	templ inline void read(T& t)
	{
		t=0;char f=0,ch=getchar();double d=0.1;
		while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
		while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
		if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
		t=(f?-t:t);
	}
	template<typename T,typename... Args>inline void read(T& t,Args&... args){read(t); read(args...);}
	char __sr[1<<21],__z[20];int __C=-1,__zz=0;
	inline void Ot(){fwrite(__sr,1,__C+1,stdout),__C=-1;}
	inline void print(register int x)
	{
		if(__C>1<<20)Ot();if(x<0)__sr[++__C]='-',x=-x;
		while(__z[++__zz]=x%10+48,x/=10);
		while(__sr[++__C]=__z[__zz],--__zz);__sr[++__C]='\n';
	}
	void file()
	{
		#ifndef ONLINE_JUDGE
		freopen("a.in","r",stdin);
		#endif
	}
	inline void chktime()
	{
		#ifndef ONLINE_JUDGE
		cout<<(clock()-t)/1000.0<<'\n';
		#endif
	}
	#ifdef mod
	ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x%mod) if (y&1) ret=ret*x%mod;return ret;}
	ll inv(ll x){return ksm(x,mod-2);}
	#else
	ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x) if (y&1) ret=ret*x;return ret;}
	#endif
//	inline ll mul(ll a,ll b){ll d=(ll)(a*(double)b/mod+0.5);ll ret=a*b-d*mod;if (ret<0) ret+=mod;return ret;}
}
using namespace my_std;

int pri[sz],mu[sz],phi[sz],cnt;
bool npri[sz];
ll f[sz];
void init()
{
	mu[1]=phi[1]=1;
	#define x i*pri[j]
	rep(i,2,sz-1)
	{
		if (!npri[i]) pri[++cnt]=i,mu[i]=-1,phi[i]=i-1;
		for (int j=1;j<=cnt&&x<sz;j++)
		{
			npri[x]=1;
			if (i%pri[j]) mu[x]=-mu[i],phi[x]=(pri[j]-1)*phi[i];
			else { phi[x]=pri[j]*phi[i]; break; }
		}
	}
	#undef x
	rep(i,1,sz-1) for (int j=i;j<sz;j+=i) (f[j]+=1ll*i*mu[j/i]*inv(phi[i])%mod)%=mod;
}

int n;
int p[sz];
struct hh{int t,nxt;}edge[sz<<1];
int head[sz],ecnt;
void make_edge(int f,int t)
{
	edge[++ecnt]=(hh){t,head[f]};
	head[f]=ecnt;
	edge[++ecnt]=(hh){f,head[t]};
	head[t]=ecnt;
}

int fa[sz][30],dep[sz],dfn[sz],c;
void dfs(int x,int f)
{
	dep[x]=dep[fa[x][0]=f]+1;dfn[x]=++c;
	rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
	#define v edge[i].t
	go(x) if (v!=f) dfs(v,x);
	#undef v
}
int lca(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	drep(i,20,0)
		if (fa[x][i]&&dep[fa[x][i]]>=dep[y])
			x=fa[x][i];
	if (x==y) return x;
	drep(i,20,0)
		if (fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

namespace Solve
{
	int m;
	struct hhh{int id,p;}S[sz];
	struct hh{int t,nxt;}edge[sz<<1];
	int head[sz],ecnt;
	void make_edge(int f,int t)
	{
		edge[++ecnt]=(hh){t,head[f]};
		head[f]=ecnt;
		edge[++ecnt]=(hh){f,head[t]};
		head[t]=ecnt;
	}
	
	int st[sz],top;
	void insert(int x)
	{
		if (top<=1) return void(st[++top]=x);
		int lca=::lca(x,st[top]);
		if (lca==st[top]) return void(st[++top]=x);
		while (top>1)
		{
			int q=st[top-1],&p=st[top];
			if (dfn[q]==dfn[lca]) { make_edge(q,p); --top; break; }
			if (dfn[q]<dfn[lca]) { make_edge(lca,p); p=lca; break; }
			make_edge(p,q),--top;
		}
		st[++top]=x;
	}
	
	ll D[sz];
	#define v edge[i].t
	void dfs1(int x,int fa)
	{
		go(x) 
			if (v!=fa) 
				dfs1(v,x),(D[x]+=D[v])%=mod;
	}
	void dfs2(int x,int fa){go(x) if (v!=fa) dfs2(v,x);D[x]=D[x]*(dep[x]-dep[fa])%mod;}
	void dfs3(int x,int fa){(D[x]+=D[fa])%=mod;go(x) if (v!=fa) dfs3(v,x);}
	void del(int x,int fa){D[x]=0;go(x) if (v!=fa) del(v,x);head[x]=0;}
	#undef v
	
	ll solve()
	{
		bool flg=0;
		rep(i,1,m) flg|=(S[i].p==1);
		if (!flg) S[++m]=(hhh){0,1};
		sort(S+1,S+m+1,[](const hhh &x,const hhh &y){return dfn[x.p]<dfn[y.p];});
		rep(i,1,m) insert(S[i].p);
		while (top>1) make_edge(st[top],st[top-1]),--top;
		top=0;
		rep(i,1,m) (D[S[i].p]+=phi[S[i].id])%=mod;
		dfs1(1,0);D[1]=0;dfs2(1,0);dfs3(1,0);
		ll ret=0;
		rep(i,1,m) (ret+=phi[S[i].id]*D[S[i].p]%mod)%=mod;
		rep(i,1,m) S[i]=(hhh){0,0};
		del(1,0);
		ecnt=m=0;
		return ret;
	}
}

ll solve(int T)
{
	ll ret,S1=0,S2=0;
	for (int i=T;i<=n;i+=T) 
		Solve::S[++Solve::m]=(Solve::hhh){i,p[i]},
		(S1+=phi[i])%=mod,
		(S2+=1ll*(dep[p[i]]-1)*phi[i]%mod)%=mod;
	ret=S1*S2*2%mod;
	ll t=Solve::solve();
	ret=(ret-2ll*t+mod+mod)%mod;
	return ret*f[T]%mod;
}

int main()
{
	file();
	init();
	read(n);
	int x,y;
	rep(i,1,n) read(x),p[x]=i;
	rep(i,1,n-1) read(x,y),make_edge(x,y);
	dfs(1,0);
	ll ans=0;
	rep(T,1,n) (ans+=solve(T)+mod)%=mod;
	cout<<ans*inv(1ll*n*(n-1)%mod)%mod;
	return 0;
}
```

---

## 作者：asuldb (赞：0)

[题目](https://www.luogu.org/problemnew/show/CF809E)

这是一道神仙题

看到这样一个鬼畜的柿子

$$\sum_{i=1}^n\sum_{j=1}^n\varphi(a_i\times a_j)\times dis(i,j)$$

又是树上距离又是$\varphi$的看起来根本就不知道怎么搞啊

首先需要知道一个这样的性质

$$\varphi(a\times b)=\frac{\varphi(a)\times \varphi(b)\times d}{\varphi(d)},d=(a,b)$$

这个性质非常显然

设$a=p^{k_1},b=p^{k_2},k_1<k_2$

于是$d=p^{k_1}$

$$\varphi(a\times b)=\varphi(p^{k_1+k_2})=p^{k_1+k_2-1}(p-1)$$

$$\frac{\varphi(a)\times \varphi(b)\times d}{\varphi(d)}=\frac{p^{k_1-1}p^{k_2-1}(p-1)^2p^{k_1}}{p^{k_1-1}(p-1)}=p^{k_1+k_2-1}(p-1)$$

这个东西显然是积性的，扩展到多个质因子也是成立的

于是写成

$$\sum_{i=1}^n\sum_{j=1}^n\frac{\varphi(a_i)\times \varphi(a_j)\times (a_i,a_j)}{\varphi((a_i,a_j))}\times dis(i,j)$$

套路枚举$gcd$

$$\sum_{d=1}^n\frac{d}{\varphi(d)}\sum_{i=1}^n\sum_{j=1}^n[(a_i,a_j)=d]\varphi(a_i)\times \varphi(a_j)\times dis(i,j)$$

考虑设后面那个东西叫

$$f(d)=\sum_{i=1}^n\sum_{j=1}^n[(a_i,a_j)=d]\varphi(a_i)\times \varphi(a_j)\times dis(i,j)$$

显然我们还需要一个函数叫

$$F(d)=\sum_{i=1}^n\sum_{j=1}^n[d|(a_i,a_j)]\varphi(a_i)\times \varphi(a_j)\times dis(i,j)$$

我们可以直接反演了

$$F(d)=\sum_{d|n}f(n)$$

$$f(d)=\sum_{d|n}\mu(\frac{n}{d})F(n)$$

现在的问题就是求出$F$，我们就可以做了

显然树上的点都有一个约数$d$的时候，任意两点的的$gcd$就会是$d$的倍数

我们如果把$d|a_i$的$i$拿出来，建出一棵虚树，搞一个树形$dp$

求一下

$$dp_i=\sum_{j=1}^ndis(i,j)\varphi(a_j)$$

就好了，这就是一个小学生$dp$求树上带权重心了

代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#define re register
#define LL long long
const int maxn=2e5+5;
const LL mod=1e9+7;
inline int read() {
	char c=getchar();int x=0;while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
struct E{int v,nxt,w;}e[maxn<<1];
int dfn[maxn],son[maxn],deep[maxn],a[maxn],b[maxn],P[maxn];
int Top[maxn],st[maxn],num,n,__,top,head[maxn],fa[maxn];
int f[maxn],p[maxn>>1],mu[maxn],phi[maxn];
LL dp[maxn],sum[maxn],S,inv[maxn],F[maxn];
inline int cmp(int a,int b) {return dfn[a]<dfn[b];}
inline LL ksm(LL a,int b) {
	LL S=1;
	while(b) {if(b&1) S=S*a%mod;b>>=1;a=a*a%mod;}
	return S;
}
inline void add(int x,int y,int w) {
	e[++num].v=y;e[num].nxt=head[x];
	head[x]=num;e[num].w=w;
}
void dfs1(int x) {
	int maxx=-1;sum[x]=1;
	for(re int i=head[x];i;i=e[i].nxt) {
		if(deep[e[i].v]) continue;
		deep[e[i].v]=deep[x]+1,fa[e[i].v]=x; 
		dfs1(e[i].v);sum[x]+=sum[e[i].v];
		if(sum[e[i].v]>maxx) maxx=sum[e[i].v],son[x]=e[i].v;
	}
}
void dfs2(int x,int topf) {
	Top[x]=topf;dfn[x]=++__;
	if(!son[x]) return;
	dfs2(son[x],topf);
	for(re int i=head[x];i;i=e[i].nxt)
	if(!Top[e[i].v]) dfs2(e[i].v,e[i].v);
}
inline int LCA(int x,int y) {
	while(Top[x]!=Top[y]) {
		if(deep[Top[x]]<deep[Top[y]]) std::swap(x,y);
		x=fa[Top[x]];
	}
	if(deep[x]<deep[y]) return x;return y;
}
inline void ins(int x) {
	if(top<=1) {st[++top]=x;return;}
	int lca=LCA(st[top],x);
	if(lca==st[top]) {st[++top]=x;return;}
	while(top>1&&dfn[st[top-1]]>=dfn[lca])
		add(st[top-1],st[top],deep[st[top]]-deep[st[top-1]]),top--;
	if(lca!=st[top]) {add(lca,st[top],deep[st[top]]-deep[lca]);st[top]=lca;}
	st[++top]=x;
}
void dfs(int x) {
	sum[x]=f[x]*phi[a[x]];
	for(re int i=head[x];i;i=e[i].nxt) {
		dfs(e[i].v);
		sum[x]+=sum[e[i].v];
		dp[x]+=(dp[e[i].v]+sum[e[i].v]*(LL)e[i].w%mod)%mod;
		dp[x]%=mod;
	}
}
void reDfs(int x) {
	for(re int i=head[x];i;i=e[i].nxt) {
		LL now=dp[x]-(dp[e[i].v]+sum[e[i].v]*(LL)e[i].w%mod)%mod;
		now=(now+mod)%mod;
		dp[e[i].v]=(dp[e[i].v]+now+((S-sum[e[i].v])*(LL)e[i].w)%mod)%mod;
		reDfs(e[i].v);
	}
}
void clear(int x) {
	f[x]=dp[x]=sum[x]=0;
	for(re int i=head[x];i;i=e[i].nxt) clear(e[i].v);
	head[x]=0;
}
int main() {
	n=read();
	for(re int i=1;i<=n;i++) a[i]=read();
	for(re int x,y,i=1;i<n;i++)
		x=read(),y=read(),add(x,y,0),add(y,x,0);
	deep[1]=1,dfs1(1),dfs2(1,1);
	for(re int i=1;i<=n;i++) b[a[i]]=i;
	f[1]=mu[1]=phi[1]=1;
	for(re int i=2;i<=n;i++) {
		if(!f[i]) p[++p[0]]=i,mu[i]=-1,phi[i]=i-1;
		for(re int j=1;j<=p[0]&&p[j]*i<=n;j++) {
			f[p[j]*i]=1;
			if(i%p[j]==0) {
				phi[p[j]*i]=p[j]*phi[i];
				break;
			}
			mu[p[j]*i]=-1*mu[i];
			phi[p[j]*i]=(p[j]-1)*phi[i];
		}
	}
	inv[1]=1;
	for(re int i=2;i<=n;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	memset(head,0,sizeof(head));
	memset(f,0,sizeof(f));
	memset(sum,0,sizeof(sum));
	for(re int k=1;k<=n;k++) {
		int tot=0;
		num=0,top=0;
		for(re int j=k;j<=n;j+=k)
			P[++tot]=b[j],f[P[tot]]=1;
		std::sort(P+1,P+tot+1,cmp);
		int rt=P[1];
		for(re int i=2;i<=tot;i++) rt=LCA(rt,P[i]);
		if(!f[rt]) st[++top]=rt;
		for(re int i=1;i<=tot;i++) ins(P[i]);
		while(top) add(st[top-1],st[top],deep[st[top]]-deep[st[top-1]]),top--;
		dfs(rt);S=sum[rt];reDfs(rt);
		for(re int i=1;i<=tot;i++)
			F[k]=(F[k]+(LL)phi[a[P[i]]]*dp[P[i]]%mod)%mod;
		clear(rt);
	}
	LL ans=0;
	for(re int i=1;i<=n;i++) {
		LL now=0;
		for(re int j=i;j<=n;j+=i) 
			now=(now+F[j]*mu[j/i]%mod)%mod,now=(now+mod)%mod;
		ans=(ans+now*(LL)i%mod*inv[phi[i]]%mod)%mod;
	}
	LL now=(LL)n*(LL)(n-1);
	now%=mod;
	printf("%lld\n",ksm(now,mod-2)*ans%mod);
	return 0;
}
```


---

## 作者：Taduro (赞：0)

这是道莫比乌斯反演+虚树的好题啊。

首先我们知道
$$
\phi(i\times j)=\frac{\phi(i)\times \phi(j)\times gcd(i,j)}{\phi(gcd(i,j))}
$$
一般$\phi$里出现乘积的题都要这么化，之后就变成了一个数学题。

不管$\frac{1}{n(n-1)}$，原式就变成了：

$
\sum_{i=1}^n\sum_{j=1}^n\frac{\varphi(a_i)\times \phi(a_j)\times gcd(a_i,a_j)}{\phi(gcd(a_i,a_j))}\times dist(i,j)
$


$a_i$在$\phi$里面让人没法推下去，所以令$b_{a_i}=i$，就会得到一个等价的式子，相当于在枚举$a_i$

$
\sum_{i=1}^n\sum_{j=1}^n\frac{\varphi(i)\times \phi(j)\times gcd(i,j)}{\phi(gcd(i,j))}\times dist(b_i,b_j)
$

似乎可以反演的样子，先继续枚举gcd：

$
\sum_{d=1}^n\frac{d}{\phi(d)}\sum_{i=1}^n\sum_{j=1}^n[(i,j)=d]\phi(i)\phi(j)\times dist(b_i,b_j)
$

下面是套路，虽然我必须要写，但大家可以跳过到下面的结论

$
\sum_{d=1}^n\frac{d}{\phi(d)}\sum_{i=1}^{n/d}\sum_{j=1}^{n/d}[(i,j)=1]\phi(id)\phi(jd)\times dist(b_{id},b_{jd})
$

$
=\sum_{d=1}^n\frac{d}{\phi(d)}\sum_{i=1}^{n/d}\sum_{j=1}^{n/d}\phi(id)\phi(jd)\times dist(b_{id},b_{jd})\sum_{k|(i,j)}\mu(k)
$

$
=\sum_{d=1}^n\frac{d}{\phi(d)}\sum_{k=1}^{n/d}\mu(k)\sum_{i=1}^{n/dk}\sum_{j=1}^{n/dk}\phi(idk)\phi(jdk)\times dist(b_{idk},b_{jdk})
$

令$T=dk$
$
=\sum_{T=1}^n\sum_{d|T}\frac{d}{\phi(d)}\mu(\frac{T}{d})\sum_{i=1}^{n/T}\sum_{j=1}^{n/T}\phi(iT)\phi(jT)\times dist(b_{iT},b_{jT})
$

跳过部分就到这里了。

首先令$f(T)=\sum_{d|T}\frac{d}{\phi(d)}\mu(\frac{T}{d})$，这个函数是可以线筛或者，枚举d去埃筛的，我用的是线筛：

当T是质数时，$f(T)=\frac{1}{T-1}$，当T是质数的m次幂(m>1)时，$f(T)=0$

这个可以自己算一下，由于里面有个$\mu$所以只用枚举d=1或d=质数的一次幂 就行了。

看后面这个式子，它其实就是：

$
\sum_{i=1}[i|T]\sum_{j=1}[j|T]\phi(i)\phi(j)\times dist(b_i,b_j)
$


我们之前为了方便去掉了$a_i$，加回来的话就是：

$
\sum_{i=1}[a_i|T]\sum_{j=1}[a_j|T]\phi(a_i)\phi(a_j)\times dist(i,j)
$

这个东西的求法是对$a_i|T$的点建一棵虚树，一共建n棵虚树，之后去dp或者枚举每一条边计算贡献，由于$a_i$是一个排列，所以n棵虚树的总点数是调和级数$nlogn$的。

```c++
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define mod 1000000007
using namespace std;
struct node{
	int next,to,z;
}w[400001];
int head[200001],stack[200001],size[200001];
int prime[100001],o[200001],phi[200001],num;
int deep[200001],st[400001][18],logg[400001];
int n,sum,ans,a[200001],b[200001],d[200001],m;
int f[200001],low[200001],cnt,top,idx[200001];
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline int dec(int x,int y){return x-y<0?x-y+mod:x-y;}
inline int mul(int x,int y){return 1ll*x*y-1ll*x*y/mod*mod;}
inline void link(int x,int y){
	w[++cnt].next=head[x];
	w[cnt].to=y; head[x]=cnt;
	w[cnt].z=deep[y]-deep[x];
}
inline int ksm(int x,int y){
	int num=1;
	while (y){
		if (y&1) num=mul(x,num);
		x=mul(x,x); y>>=1;
	}
	return num;
}
inline int cmp(int x,int y){
	if (deep[x]<deep[y]) return x; return y;
}
inline bool cmp2(int x,int y){return idx[x]<idx[y];}
inline void euler(){
	phi[1]=o[1]=f[1]=1;
	for (int i=2; i<=n; i++){
		if (!o[i]){
			prime[++prime[0]]=i;
			phi[i]=i-1; low[i]=i;
			f[i]=ksm(i-1,mod-2);
		}
		for (int j=1; j<=prime[0]&&i*prime[j]<=n; j++){
			o[i*prime[j]]=1;
			if (i%prime[j]==0){
				low[i*prime[j]]=low[i]*prime[j];
				if (low[i]!=i) f[i*prime[j]]=mul(f[i/low[i]],f[low[i]*prime[j]]);
				phi[i*prime[j]]=prime[j]*phi[i];
				break;
			}
			phi[i*prime[j]]=phi[i]*phi[prime[j]];
			f[i*prime[j]]=mul(f[i],f[prime[j]]);
			low[i*prime[j]]=prime[j];
		}
	}
//	memset(f,0,sizeof(f));
//	for (int d=1; d<=n; d++)
//		for (int t=d; t<=n; t+=d)
//			f[t]=add(f[t],mul(mul(d,so[phi[d]]),mu[t/d]));
}
void dfs(int x,int fa){
	st[++num][0]=x; idx[x]=num;
	for (int i=head[x]; i; i=w[i].next){
		if (w[i].to!=fa){
			deep[w[i].to]=deep[x]+1;
			dfs(w[i].to,x);
			st[++num][0]=x;
		}
	}
}
inline int lca(int x,int y){
	x=idx[x],y=idx[y];
	if (x>y) swap(x,y);
	int k=logg[y-x+1];
	return cmp(st[x][k],st[y-(1<<k)+1][k]);
}
inline void ins(int x){
	if (x==1) return;
	if (!top){
		stack[++top]=x;
		return;
	}
	int l=lca(stack[top],x);
	while (top&&deep[stack[top-1]]>deep[l])
		link(stack[top-1],stack[top]),top--;
	if (deep[stack[top]]>deep[l]) link(l,stack[top]),top--;
	if (stack[top]!=l) stack[++top]=l;
	stack[++top]=x;
}
void get_pre(int x){
	size[x]=phi[a[x]]*o[x];
	for (int i=head[x]; i; i=w[i].next){
		get_pre(w[i].to);
		size[x]=add(size[x],size[w[i].to]);
	}
	head[x]=0;
}
void debug(){
	for (int x=1; x<=n; x++)
		for (int i=head[x]; i; i=w[i].next)
			printf("%d %d %d\n",x,w[i].to,w[i].z);
}
int main(){
	int x,y;
	scanf("%d",&n);
	for (int i=1; i<=n; i++)
		scanf("%d",&a[i]),b[a[i]]=i;
	for (int i=1; i<n; i++){
		scanf("%d%d",&x,&y);
		link(x,y); link(y,x);
	}
	euler(); dfs(1,0);
	for (int i=2; i<=num; i++) logg[i]=logg[i>>1]+1;
	for (int j=1; j<=logg[num]; j++)
		for (int i=1; i+(1<<(j-1))-1<=num; i++)
			st[i][j]=cmp(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	stack[0]=1;
	memset(head,0,sizeof(head));
	memset(o,0,sizeof(o));
	for (int t=1; t<=n; t++){
		if (!f[t]) continue;
		m=cnt=sum=0;
		for (int i=t; i<=n; i+=t) d[++m]=b[i],o[b[i]]=1;
		sort(d+1,d+m+1,cmp2);
		for (int i=1; i<=m; i++) ins(d[i]);
		while (top) link(stack[top-1],stack[top]),top--;
//		printf("%d\n",t); debug();
		get_pre(1);
//		if (a[1]%t) size[1]=dec(size[1],phi[a[1]]);
		for (int i=1; i<=cnt; i++){
			y=w[i].to;
			sum=add(sum,mul(mul(w[i].z,dec(size[1],size[y])),size[y]));
		}
		sum=add(sum,sum);
		ans=add(ans,mul(f[t],sum));
//		printf("%d\n",sum);
		for (int i=1; i<=m; i++) o[d[i]]=0;
	}
	printf("%d\n",mul(mul(ans,ksm(n,mod-2)),ksm(n-1,mod-2)));
	return 0;
}
```



---

## 作者：i207M (赞：0)

hu~，这道题断断续续写了我一天...

给定一棵树，每个点有权值$a_i$（是一个排列），求出$\sum\sum dis(i,j)\phi(a_ia_j)$

首先，有一个重要的式子：

$$\phi(ab)=\phi(a)\phi(b)g/\phi(g),g=\gcd(a,b)$$

然后代入，

$$\begin{aligned}Ans&=\sum_{i=1}^n\sum_{j=1}^n\varphi(a_i)\varphi(a_j)\frac{gcd(a_i,a_j)}{\varphi(gcd(a_i,a_j)}dist(i,j)\\&=\sum_{d=1}^n\frac{d}{\varphi(d)}\sum_{i=1}^n\sum_{j=1}^n[gcd(a_i,a_j)=d]\varphi(a_i)\varphi(a_j)dist(i,j)\\\end{aligned}$$

设

$$g(d)=\sum_{i=1}^n\sum_{j=1}^n[gcd(a_i,a_j)=d]\varphi(a_i)\varphi(a_j)dist(i,j)$$

再设

$$f(d)=\sum_{i=1}^n\sum_{j=1}^n[d|gcd(a_i,a_j)]\varphi(a_i)\varphi(a_j)dist(i,j)$$

于是g可以由f反演得到。

于是答案就能算了。

如何解决dis的问题？把那些是倍数的点拿出来建个虚树。

~~可能点分治也可以代替虚树做~~

```
#define N 200005
int n;
bool notp[N];
int pri[N],cntp,phi[N],mu[N];
void sieve()
{
	notp[1]=1,mu[1]=phi[1]=1;
	for(ri i=2; i<=n; ++i)
	{
		if(!notp[i]) pri[++cntp]=i,phi[i]=i-1,mu[i]=-1;
		for(ri j=1,t; j<=cntp&&(t=pri[j]*i)<=n; ++j)
		{
			notp[t]=1;
			if(i%pri[j]==0) {phi[t]=phi[i]*pri[j],mu[t]=0; break;}
			else phi[t]=phi[i]*(pri[j]-1),mu[t]=-mu[i];
		}
	}
}
int a[N];
vector<int>E[N];
int dfn[N],dk;
int b[N][18],dep[N];
void pfs(int x,int _fa)
{
	b[x][0]=_fa,dep[x]=dep[_fa]+1,dfn[x]=++dk;
	for(ri i=1; i<=17&&b[x][i-1]; ++i) b[x][i]=b[b[x][i-1]][i-1];
	for(solid v:E[x]) if(v!=_fa) pfs(v,x);
	E[x].clear();
}
il int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(ri i=17; i>=0; --i)
		if(dep[b[x][i]]>=dep[y]) x=b[x][i];
	if(x==y) return x;
	for(ri i=17; i>=0; --i)
		if(b[x][i]!=b[y][i]) x=b[x][i],y=b[y][i];
	return b[x][0];
}
bool cmp(const int &a,const int &b)
{
	return dfn[a]<dfn[b];
}
int st[N],tp;
void ins(int x)
{
	if(!tp) {st[++tp]=x; return;}
	int f=lca(x,st[tp]);
	while(tp>1&&dfn[f]<dfn[st[tp-1]]) E[st[tp-1]].pb(st[tp]),--tp;
	if(dfn[f]<dfn[st[tp]]) E[f].pb(st[tp--]);
	if(f!=st[tp]) st[++tp]=f;
	st[++tp]=x;
}
bool vis[N];
int sump[N];
int fuc;
void dfs(int x)
{
	if(vis[x])
	{
		sump[x]=phi[a[x]];
		dec(fuc,mul(dep[x],mul(phi[a[x]],phi[a[x]])));
	}
	int lcap=0;
	for(solid v:E[x])
	{
		dfs(v);
		inc(lcap,mul(sump[x],sump[v]));
		inc(sump[x],sump[v]);
	}
	lcap=mul(dep[x],mul(2,lcap));
	dec(fuc,lcap);
}
void cfs(int x)
{
	sump[x]=0,vis[x]=0;
	for(solid v:E[x]) cfs(v);
	E[x].clear();
}
int id[N];
int f[N],g[N];
signed main()
{
	in(n);
	for(ri i=1; i<=n; ++i) in(a[i]),id[a[i]]=i;
	for(ri i=1,a,b; i<n; ++i)
	{
		in(a,b);
		E[a].pb(b),E[b].pb(a);
	}
	pfs(1,0);
	sieve();
	for(ri d=1; d<=n; ++d)
	{
		static int lis[N]; int cnt=0,s1=0,s2=0;
		fuc=0;
		for(ri i=d; i<=n; i+=d)
		{
			vis[lis[++cnt]=id[i]]=1;
			inc(s1,phi[i]);
			inc(s2,mul(dep[id[i]],phi[i]));
		}
		sort(lis+1,lis+1+cnt,cmp);
		tp=0;
		for(ri i=1; i<=cnt; ++i) ins(lis[i]);
		while(tp>1) E[st[tp-1]].pb(st[tp]),--tp;
		dfs(st[1]);
		fuc=mul(2,add(mul(s1,s2),fuc));
		f[d]=fuc;
		cfs(st[1]);
	}
	for(ri i=1; i<=n; ++i)
		for(ri j=1; j*i<=n; ++j)
			if(mu[j]==1) inc(g[i],f[j*i]);
			else if(mu[j]==-1) dec(g[i],f[j*i]);
	int ans=0;
	for(ri i=1; i<=n; ++i) inc(ans,mul(g[i],mul(i,mdinv(phi[i]))));
	ans=mul(ans,mdinv(mul(n,n-1)));
	out(ans);
	return 0;
}
```


---

