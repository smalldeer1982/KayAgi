# Sasha and Array

## 题目描述

斐波那契数列 $f_n$ 由以下递推式定义：

- $f_1=f_2=1$
- $f_n=f_{n-1}+f_{n-2}\;(n>2)$

你得到了 $n$ 个整数 $a_1,a_2,\cdots,a_n$.

你需要执行 $m$ 个操作，操作分两种：

- `1 l r x`：对所有 $l\le i\le r$，将 $a_i$ 加上 $x$.
- `2 l r`：求 $\sum\limits_{i=l}^r f_{a_i} \bmod (10^9+7)$.

## 说明/提示

$1\le n,m\le 10^5$

$1\le a_i\le 10^9$

## 样例 #1

### 输入

```
5 4
1 1 2 1 1
2 1 5
1 2 4 2
2 2 4
2 1 5
```

### 输出

```
5
7
9
```

# 题解

## 作者：YoungNeal (赞：25)

~~哦我这份代码好像能过QWQ~~

题解在博客[食用](https://www.cnblogs.com/YoungNeal/p/9113761.html)效果更佳哦~

## Description

给定一个数列，维护两种操作

操作 $1$，将区间 $[l,r]$ 的数字统一加 $x$。

操作 $2$，求 $\sum \limits_{i=l}^r f(val[i])$，其中 $f(i)$ 表示斐波那契数列的第 $i$ 项。‘

答案对 $10^9+7$ 取模。

## Solution

线段树维护矩阵。

因为是斐波那契数列，容易想到用矩阵快速幂来求这个东西。

想这样做的话，要想清楚两个问题：

1. 因为题目中求的是和，那么知道 $[l,mid]$ 和$[mid+1,r]$ 的答案能否快速合并出 $[l,r]$ 的答案呢？
2. 如果知道了 $[l,r]$ 的答案，对于区间加 $x$ 操作，能否快速得知操作后的答案呢？

对于第一个问题，由于矩阵具有分配律，即 $a\times b+a\times c=a\times(b+c)$，所以对于一段区间的矩阵可以相加维护。

对于第二个问题，显然将 $[l,r]$ 的矩阵乘上转移矩阵的 $x$ 次方即可。

综上，两个问题想清楚之后，我们用线段树来维护区间中的矩阵。

## Code

```cpp
// By YoungNeal
#include<cstdio>
#include<cctype>
#define N 100005
#define int long long
const int mod=1e9+7;

int n,m;
int val[N];

struct Matrix{
	int m[4][4];

	void clear(){
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++)
				m[i][j]=0;
		}
	}

	void init(){
		for(int i=0;i<4;i++)
			m[i][i]=1;
	}

	void print(){
		for(int i=1;i<=2;i++){
			for(int j=1;j<=2;j++)
				printf("i=%I64d,j=%I64d,m=%I64d\n",i,j,m[i][j]);
		}
	}

	bool empty(){
		if(m[1][1]!=1) return 0;
		if(m[1][2]!=0) return 0;
		if(m[2][1]!=0) return 0;
		if(m[2][2]!=1) return 0;
		return 1;
	}

	Matrix operator*(const Matrix &y) const {
		Matrix z; z.clear();
		for(int i=1;i<=2;i++){
			for(int k=1;k<=2;k++){
				for(int j=1;j<=2;j++)
					z.m[i][j]=(z.m[i][j]+m[i][k]*y.m[k][j])%mod;
			}
		}
		return z;
	}

	friend Matrix operator+(Matrix a,Matrix b){
		Matrix c;c.clear();
		for(int i=1;i<=2;i++){
			for(int j=1;j<=2;j++)
				c.m[i][j]=(a.m[i][j]+b.m[i][j])%mod;
		}
		return c;
	}

};

Matrix dw,fir;
Matrix mat[N<<2],lazy[N<<2];

int getint(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}

Matrix ksm(Matrix a,int b){
	Matrix ret; ret.clear(); ret.init();
	while(b){
		if(b&1) ret=ret*a;
		a=a*a;
		b>>=1;
	}
	return ret;
}

void pushup(int cur){
	mat[cur]=mat[cur<<1]+mat[cur<<1|1];
}

void build(int cur,int l,int r){
	mat[cur].clear();
	lazy[cur].clear();
	lazy[cur].init();
	if(l==r){
		mat[cur]=fir*ksm(dw,val[l]-1);
		return;
	}
	int mid=l+r>>1;
	build(cur<<1,l,mid);
	build(cur<<1|1,mid+1,r);
	pushup(cur);
}

void pushdown(int cur,int l,int r){
	if(lazy[cur].empty()) return;
	mat[cur<<1]=mat[cur<<1]*lazy[cur];
	lazy[cur<<1]=lazy[cur<<1]*lazy[cur];
	mat[cur<<1|1]=mat[cur<<1|1]*lazy[cur];
	lazy[cur<<1|1]=lazy[cur<<1|1]*lazy[cur];
	lazy[cur].clear();
	lazy[cur].init();
}

void modify(int cur,int ql,int qr,int l,int r,Matrix x){
	if(ql<=l and r<=qr){
		mat[cur]=mat[cur]*x;
		lazy[cur]=lazy[cur]*x;
		return;
	}
	pushdown(cur,l,r);
	int mid=l+r>>1;
	if(ql<=mid)
		modify(cur<<1,ql,qr,l,mid,x);
	if(mid<qr)
		modify(cur<<1|1,ql,qr,mid+1,r,x);
	pushup(cur);
}

Matrix query(int cur,int ql,int qr,int l,int r){
	if(ql<=l and r<=qr)
		return mat[cur];
	pushdown(cur,l,r);
	Matrix ret;ret.clear();
	int mid=l+r>>1;
	if(ql<=mid)
		ret=ret+query(cur<<1,ql,qr,l,mid);
	if(mid<qr)
		ret=ret+query(cur<<1|1,ql,qr,mid+1,r);
	return ret;
}

signed main(){
	dw.clear(); fir.clear();
	dw.m[1][1]=1;fir.m[1][1]=1;
	dw.m[1][2]=1;fir.m[1][2]=1;
	dw.m[2][1]=1;fir.m[2][1]=0;
	dw.m[2][2]=0;fir.m[2][2]=0;
	n=getint(),m=getint();
	for(int i=1;i<=n;i++)
		val[i]=getint();
	build(1,1,n);
	while(m--){
		if(getint()==1){
			int l=getint(),r=getint(),x=getint();
			modify(1,l,r,1,n,ksm(dw,x));
		}
		else{
			int l=getint(),r=getint();
			printf("%I64d\n",query(1,l,r,1,n).m[1][2]%mod);
		}
	}
	return 0;
}
```



---

## 作者：qwaszx (赞：19)

怎么全是矩阵啊emmm来个不一样的做法

首先我们有结论$f_{n+m}=f_nf_{m-1}+f_{n+1}f_m=f_nf_{m+1}+f_{n+1}f_m-f_nf_m$

证明可以通过展开$f_n$得到:

$\begin{aligned}f_n&=f_2f_{n-1}+f_1f_{n-2}\\&=f_3f_{n-2}+f_2f_{n-3}\\&=f_4f_{n-3}+f_3f_{n-4}\\&\cdots\\&=f_{m+1}f_{n-m}+f_{m}f_{n-m-1}\end{aligned}$

类似地有$f_{n+1+m}=f_nf_m+f_{n+1}f_{m+1}$

于是我们只要维护区间$f_n$的和以及$f_{n+1}$的和就好了.对于标记，我们也维护$f_m$和$f_{m+1}$，然后和区间和一样修改

剩下的问题就是快速计算$f_n$的值了.题解都是矩阵快速幂，然而我们有更快的做法

众所周知$f_n=\frac{1}{\sqrt{5}}\left((\tfrac{1+\sqrt{5}}{2})^n-(\tfrac{1-\sqrt{5}}{2})^n\right)$，我们可以考虑直接按照这个式子计算.然而$\sqrt{5}$在模$1e9+7$下不存在，所以我们手写一个$a+b\sqrt{5}$类型，重载加减乘法运算

另一点是快速幂还有$log$的复杂度比较烦，我们使用光速幂，具体地，有

$a^b=a^{32768x+y}=(a^{32768})^xa^y$，预处理$a$和$a^{32768}$的$0$到$32767$次幂即可$O(1)$求幂.

然后就以吊打当前rank2 10s的速度A掉了这道题233

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int LIM=32768,inv2=500000004,inv5=400000003,mod=1e9+7,N=2e6;
struct comp
{
    int a,b;
    comp operator +(const comp &t)const{return (comp){(a+t.a)%mod,(b+t.b)%mod};}
    comp operator -(const comp &t)const{return (comp){(a-t.a)%mod,(b-t.b)%mod};}
    comp operator *(const comp &t)const{return (comp){(1ll*a*t.a+5ll*b*t.b)%mod,(1ll*a*t.b+1ll*b*t.a)%mod};}
}pw0[2][LIM+100],pw1[2][LIM+100];
const comp F0={inv2,inv2},F1={inv2,mod-inv2};
struct Node
{
    int s1,s2;
    Node operator +(const Node &a)const{return (Node){(s1+a.s1)%mod,(s2+a.s2)%mod};}
    Node operator *(const Node &a)const{return (Node){(1ll*s1*a.s2+1ll*(s2-s1)*a.s1)%mod,(1ll*s1*a.s1+1ll*s2*a.s2)%mod};}
}a[N],tag[N];
int w[N],n,m;
void make()
{
    pw0[0][0]=pw1[0][0]=pw0[1][0]=pw1[1][0]=(comp){1,0};
    for(int i=1;i<=LIM;i++)pw0[0][i]=pw0[0][i-1]*F0,pw0[1][i]=pw0[1][i-1]*F1;
    comp t0=pw0[0][LIM],t1=pw0[1][LIM];
    for(int i=1;i<=LIM;i++)pw1[0][i]=pw1[0][i-1]*t0,pw1[1][i]=pw1[1][i-1]*t1;
}
comp qpower(int n,int f){return pw1[f][(n>>15)&32767]*pw0[f][n&32767];}
int F(int n){return ((comp){0,inv5}*(qpower(n,0)-qpower(n,1))).a;}
void build(int rot,int lt,int rt)
{
    tag[rot]=(Node){0,1};
    if(lt==rt){a[rot]=(Node){F(w[lt]),F(w[lt]+1)};return;}
    int mid=(lt+rt)>>1;
    build(rot<<1,lt,mid),build(rot<<1|1,mid+1,rt);
    a[rot]=a[rot<<1]+a[rot<<1|1];
}
void upd(int rot,Node x){a[rot]=a[rot]*x,tag[rot]=tag[rot]*x;}
void pushdown(int rot)
{
    if(tag[rot].s1!=0||tag[rot].s2!=1)
    {
        Node t=tag[rot];tag[rot]=(Node){0,1};
        upd(rot<<1,t),upd(rot<<1|1,t);
    }
}
void update(int rot,int lt,int rt,int lq,int rq,Node x)
{
    if(lt>=lq&&rt<=rq){upd(rot,x);return;}
    int mid=(lt+rt)>>1;pushdown(rot);
    if(lq<=mid)update(rot<<1,lt,mid,lq,rq,x);
    if(rq>mid)update(rot<<1|1,mid+1,rt,lq,rq,x);
    a[rot]=a[rot<<1]+a[rot<<1|1];
}
int query(int rot,int lt,int rt,int lq,int rq)
{
    if(lt>=lq&&rt<=rq)return a[rot].s1;
    int mid=(lt+rt)>>1;pushdown(rot);
    if(rq<=mid)return query(rot<<1,lt,mid,lq,rq);
    else if(lq>mid)return query(rot<<1|1,mid+1,rt,lq,rq);
    else return (query(rot<<1,lt,mid,lq,mid)+query(rot<<1|1,mid+1,rt,mid+1,rq))%mod;
}
int main()
{
    scanf("%d%d",&n,&m);make();
    for(int i=1;i<=n;i++)scanf("%d",w+i);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int opt,l,r,x;
        scanf("%d%d%d",&opt,&l,&r);
        if(opt==1)scanf("%d",&x),update(1,1,n,l,r,(Node){F(x),F(x+1)});
        else printf("%d\n",(query(1,1,n,l,r)+mod)%mod);
    }
}
```

---

## 作者：Link_Cut_Y (赞：12)

### 题目大意

$f_i$ 表示第 $i$ 个斐波那契数。

给定长度为 $n$ 的序列 $\{a\}$ 和 $m$ 次操作，每次操作如下：

 1. ```1 l r x``` 表示将 $a_l \sim a_r$ 中的每一个数加上 $x$ 。
 
 2. ```2 l r``` 表示询问 $(\sum_{i = l}^{r} f_{a_i}) \mod{10 ^ 9 + 7}$ 。
 
### 题目分析

这道题是上课的时候 djh 出给我们的。~~当时一眼秒出正解~~。

我们可以首先想想下面几个问题：

1. 求斐波那契数列第 $n$ 项 $(n \leq 10 ^ {18})$ 。
	
   正解：矩阵快速幂。
    
2. 求斐波那契数列前 $n$ 项和$(n \leq 10 ^ {5})$ 。
	
   Dalao1：还是快速幂啊！
   
   Dalao2：前缀和啊！
   
3. 在第二题上再加上修改呢？

	正解：线段树。
    
将矩阵当做点放到线段树上维护，被称为矩阵线段树。

在线段树上操作，需要满足分配律和结合律，而这两点矩阵全都满足。

因此我们就可以在 $O(m \log {n})$ 复杂度内解决这个问题了。


---------

考虑矩阵 $\begin{bmatrix}
 f_{n} & f_{n - 1}\\
 0 & 0
\end{bmatrix}$
，当它乘 $\begin{bmatrix}
 1 & 1\\
 1 & 0
\end{bmatrix}$ 时，就可以得到 $\begin{bmatrix}
 f_{n + 1} & f_{n}\\
 0 & 0
\end{bmatrix}$，完成求斐波那契第 $n$ 项。

我们将矩阵 $\begin{bmatrix}
 1 & 1\\
 1 & 0
\end{bmatrix}$ 称为转移矩阵。用 $A$ 来表示。

将每一个 $f_{a_i}$ 用矩阵快速幂求出来扔到树上，需要 $O(n \log{n})$ 左右的复杂度。

考虑操作一。

将 $l \sim r$ 中每一个斐波那契数的下标增加 $x$，相当于将每一个数整体右移越过了 $x$ 个斐波那契数。也就是将每一个数乘以 $x$ 个转移矩阵。由于矩阵乘法具有结合律，因此我们可以将每一个数乘以 $A^x$ 。

用公式表示一下就是：

$$ {\forall } i \in [l, r], f_i = f_i \times A ^ x$$

考虑操作二。

线段树维护区间和即可。

-----------

### 代码

```
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define int long long

using namespace std;

const int N = 100010, mod = 1e9 + 7;
int a[N], n, m;
struct Matrix
{
	int a[2][2];
	void clear(int x) {memset(a, x, sizeof a);}
	void makeI() { a[0][0] = 1; a[0][1] = 0; a[1][0] = 0; a[1][1] = 1; }
	bool empty() {return ((a[0][0] == 1) and (a[0][1] == 0) and (a[1][0] == 0) and (a[1][1] == 1));}
}Turn, st;

Matrix operator + (const Matrix& A, const Matrix& B) {
	Matrix res;
	res.clear(0);
	for (int i = 0; i <= 1; i ++ )
		for (int j = 0; j <= 1; j ++ )
			res.a[i][j] = (A.a[i][j] + B.a[i][j]) % mod;
	return res;
}
Matrix operator * (const Matrix& A, const Matrix& B) {
	Matrix res;
	res.clear(0);
	for (int i = 0; i <= 1; i ++ )
		for (int j = 0; j <= 1; j ++ )
			for (int k = 0; k <= 1; k ++ )
				(res.a[i][j] += (A.a[i][k] * B.a[k][j])) %= mod;
	return res;
}
Matrix operator ^ (Matrix A, int b) {
	Matrix res;
	res.makeI();
	while (b) {
		if (b & 1) res = res * A;
		A = A * A;//, A = A % mod;
		b >>= 1;
	}
	return res;
}

namespace Segment_Tree
{
	struct Tree
	{
		int l, r;
		Matrix sum, add;
		#define ls u << 1
		#define rs u << 1 | 1
	}tr[N << 2];
	
	void pushup(int u) {
		tr[u].sum = tr[ls].sum + tr[rs].sum;
	}
	void pushdown(int u) {
		if (!tr[u].add.empty()) {
			tr[ls].add = tr[ls].add * tr[u].add;
			tr[rs].add = tr[rs].add * tr[u].add;
			tr[ls].sum = tr[ls].sum * tr[u].add;
			tr[rs].sum = tr[rs].sum * tr[u].add;
			tr[u].add.makeI();
		}
	}
	void build(int u, int l, int r) {
		tr[u] = {l, r};
		tr[u].add.a[0][0] = tr[u].add.a[1][1] = 1;
		if (l == r) {
			if (a[l] == 1) tr[u].sum.a[0][0] = 1;
			else tr[u].sum.a[0][0] = tr[u].sum.a[0][1] = 1;
			if(a[l] > 2) tr[u].sum = tr[u].sum * (Turn ^ (a[l] - 2));
			return;
		}
		int mid = l + r >> 1;
		build(ls, l, mid), build(rs, mid + 1, r);
		pushup(u);
	}
	void modify(int u, int l, int r, Matrix v) {
		if (tr[u].l >= l && tr[u].r <= r) {
			tr[u].add = tr[u].add * v, tr[u].sum = tr[u].sum * v;
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) modify(ls, l, r, v);
		if (r > mid) modify(rs, l, r, v);
		pushup(u);
	}
	int query(int u, int l, int r) {
		if (tr[u]. l >= l && tr[u].r <= r) return tr[u].sum.a[0][0];
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1, res = 0;
		if (l <= mid) res = (res + query(ls, l, r)) % mod;
		if (r > mid) res = (res + query(rs, l, r)) % mod;
		return res;
	}
}
using namespace Segment_Tree;

signed main()
{
	// Init
	{
		Turn.a[0][0] = Turn.a[0][1] = Turn.a[1][0] = 1;
	}
	
	// Input
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i ++ )
		scanf("%lld", &a[i]);
	build(1, 1, n);
	
	// Methods
	while (m -- )
	{
		int op, l, r, v;
		scanf("%lld%lld%lld", &op, &l, &r);
		if (op == 1) {
			scanf("%lld", &v);
			modify(1, l, r, Turn ^ v);
		}
		else {
			printf("%lld\n", query(1, l, r) % mod);
		}
	}
	return 0;
}
```

---

## 作者：KEBrantily (赞：5)

线段树维护矩阵。

本以为会调不知道多长时间，结果不到 50 mins 就完成了。

初始想法是维护原序列，在求值的时候再求斐波那契数。但是感觉跑的慢。

然后决定维护斐波那契数列（非矩阵），但是发现每次 `update` 时构造新矩阵比较麻烦。

最后才想到把矩阵当成点来维护。

测完跑了 1.1min，看了下题解区发现思路也差不太多？

## Solution

我们在每个点维护 $\begin{bmatrix}
f_i & f_{i-1}      \\
\end{bmatrix}$ 这样一个矩阵。

对于建树，我们直接矩阵快速幂处理出当前 $f_{a_i}$ 所在的矩阵即可。

对于取和操作，和维护整数时一样，每次统计矩阵 `sum.z[1][1]` 的值即可。

剩下的操作才是重点。

对于修改操作，在原数列上是 $a_i \to a_i +k$，换到斐波那契数就是 $f_{a_i}\to f_{a_i+k}$，也就是向后移 $k$ 项。

根据矩阵求斐波那契数列的式子，我们在当前点维护的矩阵上乘一个 $\begin{bmatrix}
1 & 1      \\
1 & 0	
\end{bmatrix}^{k-1}$ 即可。而这个矩阵用矩阵快速幂现求即可。

对于节点信息的上传和懒标记的下传，我们直接相加。下传的懒标记就是上面的 $k-1$ 次方矩阵。

因为矩阵的乘法满足分配律，所以我们先将矩阵相加再相乘对答案无影响。

至于重载加法乘法运算符什么的就不赘述了。

### 几个问题

- 注意取模并开 `long long`。

- 注意每次矩阵快速幂时要将 $\begin{bmatrix}
1 & 1      \\
1 & 0	
\end{bmatrix}$ 这个矩阵重置。

- 注意懒标记初始是单位矩阵而不是零矩阵。

- 建树时记得特判一下 $a[i]=1\ \texttt{or} \ 2$ 的情况。

## Code

写的比较丑，大家将就看吧。

```cpp
#include<queue>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define maxn 400010
#define INF 0x3f3f3f3f
#define Mod 1000000007
#define int long long

using namespace std;

int n,m,a[maxn];

int read(){
  int s=0,w=1;char ch=getchar();
  while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
  while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
  return s*w;
}

struct Matrix{
  int z[4][4];
  Matrix(){memset(z,0,sizeof z);}
  Matrix operator * (const Matrix &b) const{
    Matrix res;
    for(int i=1;i<=2;i++)
      for(int j=1;j<=2;j++)
        for(int k=1;k<=2;k++)
          res.z[i][k]=(res.z[i][k]+z[i][j]*b.z[j][k])%Mod;
    return res;
  }
  
  Matrix operator + (const Matrix &b) const{
    Matrix res;
    res.z[1][1]=(z[1][1]+b.z[1][1])%Mod;
    res.z[1][2]=(z[1][2]+b.z[1][2])%Mod;
    res.z[2][1]=(z[2][1]+b.z[2][1])%Mod;
    res.z[2][2]=(z[2][2]+b.z[2][2])%Mod;
    return res;
  }
}ans,X;

Matrix quickpow(Matrix Now,int y){
  while(y){
    if(y&1) Now=Now*X;
    X=X*X;y>>=1;
  }
  return Now;
}

namespace Seg{
  #define ls x<<1
  #define rs x<<1|1

  Matrix sum[maxn],lazy[maxn];
  void pushup(int x){
    sum[x]=sum[ls]+sum[rs];
  }
  
  void pushdown(int x){
    if(lazy[x].z[1][1]==1&&lazy[x].z[2][2]==1&&!lazy[x].z[1][2]&&!lazy[x].z[2][1]) return;
    sum[ls]=sum[ls]*lazy[x];sum[rs]=sum[rs]*lazy[x];
    lazy[ls]=lazy[ls]*lazy[x];lazy[rs]=lazy[rs]*lazy[x];
    lazy[x].z[1][1]=lazy[x].z[2][2]=1;lazy[x].z[1][2]=lazy[x].z[2][1]=0;
  }
  
  void build(int x,int l,int r){
    lazy[x].z[1][1]=lazy[x].z[2][2]=1;
    if(l==r){
      X.z[2][2]=0;
      ans.z[1][1]=ans.z[1][2]=1;
      X.z[1][1]=X.z[1][2]=X.z[2][1]=1;
      if(a[l]==1) sum[x].z[1][1]=1;
      else if(a[l]==2) sum[x].z[1][1]=sum[x].z[1][2]=1;
      else sum[x]=quickpow(ans,a[l]-2);
      return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);build(rs,mid+1,r);
    pushup(x);
  }
  
  void update(int x,int l,int r,int L,int R,Matrix k){
    if(L<=l&&R>=r){
      sum[x]=sum[x]*k;
      lazy[x]=lazy[x]*k;
      return;
    }
    int mid=l+r>>1;pushdown(x);
    if(L<=mid) update(ls,l,mid,L,R,k);
    if(R>=mid+1) update(rs,mid+1,r,L,R,k);
    pushup(x);
  }
  
  int query(int x,int l,int r,int L,int R){
    int ans=0;
    if(L<=l&&R>=r)
      return sum[x].z[1][1]%Mod;
    int mid=l+r>>1;pushdown(x);
    if(L<=mid) ans=(ans+query(ls,l,mid,L,R))%Mod;
    if(R>=mid+1) ans=(ans+query(rs,mid+1,r,L,R))%Mod;
    return ans;
  }
}

signed main(){
  n=read();m=read();
  for(int i=1;i<=n;i++) a[i]=read();
  Seg::build(1,1,n);
  for(int i=1,opt,x,y,k;i<=m;i++){
    opt=read();x=read();y=read();
    if(opt==1){
      k=read();X.z[2][2]=0;
      X.z[1][1]=X.z[1][2]=X.z[2][1]=1;
      Matrix Base=quickpow(X,k-1);
      Seg::update(1,1,n,x,y,Base);
    }
    else printf("%lld\n",Seg::query(1,1,n,x,y)%Mod);
  }
  return 0;
}
```

---

## 作者：TianTian2008 (赞：4)

需要掌握线段树和一点线性代数的基础。

根据斐波那契数列定义 $F_n=F_{n-1}+F_{n-2}$，有 $\begin{bmatrix}1&1\\1&0\end{bmatrix}\begin{bmatrix}F_{n-1}\\F_{n-2}\end{bmatrix}=\begin{bmatrix}F_{n}\\F_{n-1}\end{bmatrix}$。故可以使用矩阵描述转移，快速求出 $F_n$。

若初始向量设为 $\begin{bmatrix}F_2\\F_1\end{bmatrix}$ 则 $\begin{bmatrix}F_{n}\\F_{n-1}\end{bmatrix}=\begin{bmatrix}1&1\\1&0\end{bmatrix}^{n-2}\begin{bmatrix}F_2\\F_1\end{bmatrix}$，可能出现指数 $n-2\leqslant0$ 的情况。不妨拓宽斐波那契数列的定义，按照 $F_n=F_{n-1}+F_{n-2}$ 推出 $F_{-1}=1,F_0=0$ 并把初始向量设为 $\begin{bmatrix}F_0\\F_{-1}\end{bmatrix}$，此时 $\begin{bmatrix}F_{n}\\F_{n-1}\end{bmatrix}=\begin{bmatrix}1&1\\1&0\end{bmatrix}^n\begin{bmatrix}F_0\\F_{-1}\end{bmatrix}$，无需考虑指数为负的情况。同时由于初始向量为 $\begin{bmatrix}F_0\\F_{-1}\end{bmatrix}=\begin{bmatrix}0\\1\end{bmatrix}$，二阶矩阵乘其等价于取二阶矩阵的 $(1,2)$ 元。

要求区间和可以使用线段树维护，维护的节点为由初始向量转移到所求区间和的矩阵。考虑区间合并的操作

$\begin{bmatrix}F_a+F_b\\F_{a-1}+F_{b-1}\end{bmatrix}$

$=\begin{bmatrix}F_a\\F_{a-1}\end{bmatrix}+\begin{bmatrix}F_b\\F_{b-1}\end{bmatrix}$

$=\begin{bmatrix}1&1\\1&0\end{bmatrix}^a\begin{bmatrix}F_{0}\\F_{-1}\end{bmatrix}+\begin{bmatrix}1&1\\1&0\end{bmatrix}^b\begin{bmatrix}F_{0}\\F_{-1}\end{bmatrix}$

$=(\begin{bmatrix}1&1\\1&0\end{bmatrix}^a+\begin{bmatrix}1&1\\1&0\end{bmatrix}^b)\begin{bmatrix}F_{0}\\F_{-1}\end{bmatrix}$

即使用线段树合并斐波那契数列区间和时可以直接把转移矩阵相加。

而把 $[l,r]$ 区间加上 $x$ 的操作相当于把区间内的斐波那契数都向后转移 $x$ 项，故把区间内的节点乘上转移矩阵的 $x$ 次方 $\begin{bmatrix}1&1\\1&0\end{bmatrix}^x$即可。

到此，得出了此题的思路。

```
#include <iostream>
#include <cstdio>
#define mod 1000000007
using namespace std;
typedef long long ll;
ll n,m;
struct matrix
{
	ll a[3][3];
	matrix(ll a11=0,ll a12=0,ll a21=0,ll a22=0)
	{
		a[1][1]=a11;
		a[1][2]=a12;
		a[2][1]=a21;
		a[2][2]=a22;
	}
	friend bool operator!=(matrix a,matrix b)
	{
		return (a.a[1][1]!=b.a[1][1])|(a.a[1][2]!=b.a[1][2])|(a.a[2][1]!=b.a[2][1])|(a.a[2][2]!=b.a[2][2]);
	}
	friend matrix operator+(matrix a,matrix b)
	{
		return matrix((a.a[1][1]+b.a[1][1])%mod,(a.a[1][2]+b.a[1][2])%mod,(a.a[2][1]+b.a[2][1])%mod,(a.a[2][2]+b.a[2][2])%mod);
	}
	friend matrix operator*(matrix a,matrix b)
	{
		return matrix((a.a[1][1]*b.a[1][1]+a.a[1][2]*b.a[2][1])%mod,(a.a[1][1]*b.a[1][2]+a.a[1][2]*b.a[2][2])%mod,(a.a[2][1]*b.a[1][1]+a.a[2][2]*b.a[2][1])%mod,(a.a[2][1]*b.a[1][2]+a.a[2][2]*b.a[2][2])%mod);//矩阵阶数固定，乘法可以把循环展开 
	}
	friend matrix operator^(matrix x,ll y)
	{
		matrix res(1,0,0,1);//矩阵乘法单位元，即矩阵的0次方
		while(y)
		{
			if(y&1) res=res*x;
			x=x*x;
			y>>=1;
		}
		return res;
	}
}zero,unit(1,0,0,1),base(1,1,1,0),val[400001],lazy[400001];
void pushup(ll rt)
{
	val[rt]=val[rt<<1]+val[rt<<1|1];
}
void pushdown(ll rt)
{
	lazy[rt<<1]=lazy[rt<<1]*lazy[rt];
	lazy[rt<<1|1]=lazy[rt<<1|1]*lazy[rt];
	val[rt<<1]=val[rt<<1]*lazy[rt];
	val[rt<<1|1]=val[rt<<1|1]*lazy[rt];
	lazy[rt]=unit; 
}
void build(ll rt,ll l,ll r)
{
	if(l>r) return;
	lazy[rt]=unit;
	if(l==r)
	{
		ll x;
		scanf("%lld",&x);
		val[rt]=base^x;
		return;
	}
	ll mid=l+r>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	pushup(rt);
}
void upd(ll rt,ll l,ll r,ll L,ll R,matrix m)//参数传递的是矩阵的幂而不是矩阵的指数，防止超时 
{
	if(l>R||r<L) return;
	if(L<=l&&r<=R)
	{
		lazy[rt]=m*lazy[rt];
		val[rt]=m*val[rt];
		return;
	}
	if(lazy[rt]!=unit) pushdown(rt);
	ll mid=l+r>>1;
	upd(rt<<1,l,mid,L,R,m);
	upd(rt<<1|1,mid+1,r,L,R,m);
	pushup(rt);
}
matrix query(ll rt,ll l,ll r,ll L,ll R)
{
	if(l>R||r<L) return zero;
	if(L<=l&&r<=R) return val[rt];
	if(lazy[rt]!=unit) pushdown(rt);
	ll mid=l+r>>1;
	return query(rt<<1,l,mid,L,R)+query(rt<<1|1,mid+1,r,L,R);
}
int main()
{
	scanf("%lld%lld",&n,&m);
	build(1,1,n);
	for(int i=1;i<=m;++i)
	{
		ll op;
		scanf("%lld",&op);
		if(op==1)
		{
			ll l,r,x;
			scanf("%lld%lld%lld",&l,&r,&x);
			upd(1,1,n,l,r,base^x);
		}
		else
		{
			ll l,r;
			scanf("%lld%lld",&l,&r);
			printf("%lld\n",query(1,1,n,l,r).a[1][2]);//取矩阵的(1,2)元
		}
	}
	return 0;
}
```

---

## 作者：huangkx (赞：4)

## 思路

考虑用矩阵表示斐波那契数。

容易得知，$f _ 0 = 0$，$f _ 1 = 1$，令 $2 \leq k$，$\begin {bmatrix} f _ k \\ f _ {k - 1} \end {bmatrix} = \begin {bmatrix} 1 & 1 \\ 1 & 0 \end {bmatrix} \times \begin {bmatrix} f _ {k - 1} \\ f _ {k - 2} \end {bmatrix}$。

那么，令 $1 \leq k$，$\begin {bmatrix} f _ k \\ f _ {k - 1} \end {bmatrix} = \begin {bmatrix} 1 & 1 \\ 1 & 0 \end {bmatrix} ^ {k - 1} \times \begin {bmatrix} 1 \\ 0 \end {bmatrix}$。

所以，对于序列上的每一个位置 $i$，需要维护 $\begin {bmatrix} 1 & 1 \\ 1 & 0 \end {bmatrix} ^ {a _ i - 1}$。令 $b _ i = \begin {bmatrix} 1 & 1 \\ 1 & 0 \end {bmatrix} ^ {a _ i - 1}$，则题目中的操作可以转化为如下操作：

- 操作 $1$（修改）：对于所有的 $l \leq i \leq r$，$b _ i \leftarrow b _ i \times \begin {bmatrix} 1 & 1 \\ 1 & 0 \end {bmatrix} ^ x$。
- 操作 $2$（查询）：求 $(\sum ^ r _ {i = l} b _ i) \times \begin {bmatrix} 1 \\ 0 \end {bmatrix}$。

先封装矩阵类，再用线段树维护矩阵即可。注意线段树上的懒标记也要用矩阵表示。

令 $v = 10 ^ 9$，则时间复杂度为 $O(n \log v + m ( \log n + \log v))$。

## 代码

```cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define LL long long
#define RI register int
#define RLL register long long
using namespace std;
namespace IO
{
	inline int read()
	{
		int f = 1, x = 0;
		char c = getchar();
		while(c < '0' || c > '9'){
			if(c == '-') f = -1;
			c = getchar();
		}
		while(c >= '0' && c <= '9'){
			x = x * 10 + c - '0';
			c = getchar();
		}
		return f * x;
	}
	inline LL read_LL()
	{
		LL f = 1, x = 0;
		char c = getchar();
		while(c < '0' || c > '9'){
			if(c == '-') f = -1;
			c = getchar();
		}
		while(c >= '0' && c <= '9'){
			x = x * 10 + c - '0';
			c = getchar();
		}
		return f * x;
	}
	inline void write(int x)
	{
		if(x < 0){
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	inline void write_LL(LL x)
	{
		if(x < 0){
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace IO;
void solve();
int main()
{
	solve();
	return 0;
}
const int MAXN = 1e5;
const int N = 2;
const LL MOD = 1e9 + 7;
struct Matrix{
	LL a[N + 1][N + 1];
	Matrix()
	{
		memset(a, 0, sizeof a);
	}
	void Build()
	{
		memset(a, 0, sizeof a);
		for(int i = 1; i <= N; i ++) a[i][i] = 1;
	}
	void Initialize_1()
	{
		a[2][2] = 0;
		a[1][1] = a[1][2] = a[2][1] = 1;
	}
	void Initialize_2()
	{
		a[1][2] = a[2][1] = a[2][2] = 0;
		a[1][1] = 1;
	}
};
Matrix operator + (Matrix &x, Matrix &y)
{
	Matrix z = Matrix();
	for(int i = 1; i <= N; i ++){
		for(int j = 1; j <= N; j ++){
			z.a[i][j] = (x.a[i][j] + y.a[i][j]) % MOD;
		}
	}
	return z;
}
Matrix operator * (Matrix &x, Matrix &y)
{
	Matrix z = Matrix();
	for(int k = 1; k <= N; k ++){
		for(int i = 1; i <= N; i ++){
			for(int j = 1; j <= N; j ++){
				z.a[i][j] = (z.a[i][j] + x.a[i][k] * y.a[k][j] % MOD) % MOD;
			}
		}
	}
	return z;
}
Matrix operator ^ (Matrix x, LL p)
{
	Matrix y = Matrix();
	y.Build();
	while(p > 0){
		if(p % 2 == 1) y = y * x;
		x = x * x;
		p = p / 2;
	}
	return y;
}
struct Segment_Tree{
	struct Node{
		Matrix sum;
		Matrix tag;
		Node()
		{
			sum = Matrix();
			tag = Matrix();
			tag.Build();
		}
	};
	vector < Node > tree;
	void Initialize(int n)
	{
		tree.clear();
		for(int i = 1; i <= (n << 2); i ++) tree.push_back(Node());
	}
	void Add_Tag(int u, Matrix tag)
	{
		tree[u].sum = tree[u].sum * tag;
		tree[u].tag = tree[u].tag * tag;
	}
	void Push_Up(int u)
	{
		tree[u].sum = tree[u << 1].sum + tree[u << 1 | 1].sum;
	}
	void Push_Down(int u)
	{
		Add_Tag(u << 1, tree[u].tag);
		Add_Tag(u << 1 | 1, tree[u].tag);
		tree[u].tag.Build();
	}
	void Build(int u, int l, int r, Matrix a[])
	{
		if(l > r) return;
		if(l == r){
			tree[u].sum = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		Build(u << 1, l, mid, a);
		Build(u << 1 | 1, mid + 1, r, a);
		Push_Up(u);
	}
	void Multiply(int u, int l, int r, int L, int R, Matrix V)
	{
		if(l > r || l > R || r < L) return;
		if(l >= L && r <= R){
			Add_Tag(u, V);
			return;
		}
		int mid = (l + r) >> 1;
		Push_Down(u);
		Multiply(u << 1, l, mid, L, R, V);
		Multiply(u << 1 | 1, mid + 1, r, L, R, V);
		Push_Up(u);
	}
	Matrix Query_Sum(int u, int l, int r, int L, int R)
	{
		if(l > r || l > R || r < L) return Matrix();
		if(l >= L && r <= R) return tree[u].sum;
		int mid = (l + r) >> 1;
		Push_Down(u);
		Matrix res_1 = Query_Sum(u << 1, l, mid, L, R);
		Matrix res_2 = Query_Sum(u << 1 | 1, mid + 1, r, L, R);
		return res_1 + res_2;
	}
};
int n, m;
int type, l, r, x;
int a[MAXN + 5];
Matrix b[MAXN + 5];
Matrix tmp_1, tmp_2;
Segment_Tree tree;
void solve()
{
	n = read(), m = read();
	for(int i = 1; i <= n; i ++){
		a[i] = read();
		b[i].Initialize_1();
		b[i] = b[i] ^ (a[i] - 1);
	}
	tree.Initialize(n);
	tree.Build(1, 1, n, b);
	while(m --){
		type = read(), l = read(), r = read();
		if(type == 1){
			x = read();
			tmp_1.Initialize_1();
			tmp_1 = tmp_1 ^ x;
			tree.Multiply(1, 1, n, l, r, tmp_1);
		}
		if(type == 2){
			tmp_1 = tree.Query_Sum(1, 1, n, l, r);
			tmp_2.Initialize_2();
			tmp_2 = tmp_1 * tmp_2;
			write(tmp_2.a[1][1]), putchar('\n');
		}
	}
}
```

## 闲话

我随手把矩阵大小开了 $7 \times 7$，结果收获了一堆 MLE。

2022.5.25

---

## 作者：FutaRimeWoawaSete (赞：2)

第一次写线段树维护矩乘啊……结果直接写爆了。              

观察到答案就是斐波那契数列求和，我们不妨用矩阵乘法维护答案：       

记矩阵 

$$Base =  
\begin{bmatrix}
1&1\\
1&0\\
\end{bmatrix}
$$

而矩阵 
$$Init = 
\begin{bmatrix}
1&0
\end{bmatrix}
$$

我们可知：        

$f_{x} = Init \times Base ^ {x - 1}$              

考虑区间加 $w$，那么这个式子应该变成：      

$f_{x + w} = Init \times Base ^ {x + w - 1}$          

由于我们在线段树上维护的是一个和的形式：          

$\sum_{i = l}^r f_{a_i + w} = \sum_{i = l}^r Init \times Base ^ {a_i + w - 1}$。           

由于我们先前在线段树上维护的是 $\sum_{i = l} ^ r Init \times Base ^ {a_i - 1}$，所以我们只需要在此时对于整体乘上一个 $Base ^ w$ 即可。      

下传的标记最好也要写成矩阵，不知道为什么自己直接下传区间加的值就挂了而直接下传矩阵就没问题……而且这也会快一只 $\log x$。

时间复杂度 $O(8n \log n)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5 , MOD = 1e9 + 7;
int a[Len],n,q;
struct node
{
	int a[3][3];
	node(){memset(a , 0 , sizeof a);}
	inline void build(){for(int i = 1 ; i <= 2 ; i ++) a[i][i] = 1;}
	inline void clear(){memset(a , 0 , sizeof a);}
	inline bool empty()
	{
		for(int i = 1 ; i <= 2 ; i ++)
			for(int j = 1 ; j <= 2 ; j ++) if(a[i][j]) return false;
		return true;
	}
	node operator + (const node &B)
	{
		node C;
		for(int i = 1 ; i <= 2 ; i ++)
			for(int j = 1 ; j <= 2 ; j ++) 	
				C.a[i][j] = (a[i][j] + B.a[i][j]) % MOD;
		return C; 
	}
	node operator * (const node &y)
	{
		node z;
		for(int i = 1 ; i <= 2 ; i ++)
			for(int j = 1 ; j <= 2 ; j ++) 
				for(int k = 1 ; k <= 2 ; k ++)
					z.a[i][j] = (z.a[i][j] + 1ll * a[i][k] * y.a[k][j] % MOD) % MOD;
		return z;
	}
}tree[Len << 2],tag[Len << 2],Base,Mul,BBase,ADD,upd;
node qpow(node qk,int b)
{
	node res;res.build();
	while(b)
	{
		if(b & 1) res = res * qk;
		qk = qk * qk;
		b = b >> 1;
	}
	return res;
}
#define ls(p) p << 1
#define rs(p) p << 1 | 1
inline void Mod(int &x){if(x > MOD) x -= MOD;}
void push_up(int x){tree[x] = tree[ls(x)] + tree[rs(x)];}
void push_down(int p)
{
	if(!tag[p].empty())
	{
		tag[ls(p)] = tag[ls(p)] * tag[p] , tag[rs(p)] = tag[rs(p)] * tag[p];
		tree[ls(p)] = tree[ls(p)] * tag[p];
		tree[rs(p)] = tree[rs(p)] * tag[p];
		tag[p].clear();
		tag[p].build();
	}
}
void build(int p,int l,int r)
{
	tree[p].clear();
	tag[p].clear();
	tag[p].build();
	if(l == r)
	{
		tree[p] = BBase * qpow(Base , a[l] - 1);
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	push_up(p);
}
void update(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r)
	{
		tag[p] = tag[p] * upd;
		tree[p] = tree[p] * upd;
		return;
	}
	push_down(p);
	int mid = (l + r) >> 1;
	if(nl <= mid) update(ls(p) , l , mid , nl , nr);
	if(nr > mid) update(rs(p) , mid + 1 , r , nl , nr);
	push_up(p);
}
void query(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r){ADD = ADD + tree[p];return;}
	push_down(p);
	int mid = (l + r) >> 1;
	if(nl <= mid) query(ls(p) , l , mid , nl , nr);
	if(nr > mid) query(rs(p) , mid + 1 , r , nl , nr);
}
int opt,l,r,w;
int main()
{
	BBase.a[1][1] = 1 , BBase.a[1][2] = 0;
	Base.a[1][1] = 1 , Base.a[1][2] = 1 , Base.a[2][1] = 1 , Base.a[2][2] = 0;
	scanf("%d %d",&n,&q);
	for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
	build(1 , 1 , n);
	while(q --)
	{
		scanf("%d %d %d",&opt,&l,&r);
		if(opt == 1) 
		{
			scanf("%d",&w);
			upd = qpow(Base , w);
			update(1 , 1 , n , l , r);
		}
		else
		{
			ADD.clear();
			query(1 , 1 , n , l , r);
			printf("%d\n",ADD.a[1][1]);
		}
	}
	return 0;
}
```

---

## 作者：1saunoya (赞：2)

~~我们考虑线性代数上面的矩阵知识~~

啊呸，是基础数学

斐波那契的矩阵就不讲了

定义矩阵 $f_x$ 是第 $x$ 项的斐波那契矩阵

因为
$f_i * f_j = f_{i+j}$

然后又因为 $\texttt{AB+AC=A(B+C)}$

所以 $\sum_{i=l}^{r} f(a_i+x) = f(x)\sum_{i=l}^{r} f(a_i)$

线段树板子题，维护一个矩阵，这题没了

```cpp
// by Isaunoya
#include <bits/stdc++.h>
using namespace std;

#define rep(i, x, y) for (register int i = (x); i <= (y); ++i)
#define Rep(i, x, y) for (register int i = (x); i >= (y); --i)
#define int long long

const int _ = 1 << 21;
struct I {
	char fin[_], *p1 = fin, *p2 = fin;
	inline char gc() {
		return (p1 == p2) && (p2 = (p1 = fin) + fread(fin, 1, _, stdin), p1 == p2) ? EOF : *p1++;
	}
	inline I& operator>>(int& x) {
		bool sign = 1;
		char c = 0;
		while (c < 48) ((c = gc()) == 45) && (sign = 0);
		x = (c & 15);
		while ((c = gc()) > 47) x = (x << 1) + (x << 3) + (c & 15);
		x = sign ? x : -x;
		return *this;
	}
	inline I& operator>>(double& x) {
		bool sign = 1;
		char c = 0;
		while (c < 48) ((c = gc()) == 45) && (sign = 0);
		x = (c - 48);
		while ((c = gc()) > 47) x = x * 10 + (c - 48);
		if (c == '.') {
			double d = 1.0;
			while ((c = gc()) > 47) d = d * 0.1, x = x + (d * (c - 48));
		}
		x = sign ? x : -x;
		return *this;
	}
	inline I& operator>>(char& x) {
		do
			x = gc();
		while (isspace(x));
		return *this;
	}
	inline I& operator>>(string& s) {
		s = "";
		char c = gc();
		while (isspace(c)) c = gc();
		while (!isspace(c) && c != EOF) s += c, c = gc();
		return *this;
	}
} in;
struct O {
	char st[100], fout[_];
	signed stk = 0, top = 0;
	inline void flush() {
		fwrite(fout, 1, top, stdout), fflush(stdout), top = 0;
	}
	inline O& operator<<(int x) {
		if (top > (1 << 20)) flush();
		if (x < 0) fout[top++] = 45, x = -x;
		do
			st[++stk] = x % 10 ^ 48, x /= 10;
		while (x);
		while (stk) fout[top++] = st[stk--];
		return *this;
	}
	inline O& operator<<(char x) {
		fout[top++] = x;
		return *this;
	}
	inline O& operator<<(string s) {
		if (top > (1 << 20)) flush();
		for (char x : s) fout[top++] = x;
		return *this;
	}
} out;
#define pb emplace_back
#define fir first
#define sec second

template < class T > inline void cmax(T & x , const T & y) {
	(x < y) && (x = y) ;
}
template < class T > inline void cmin(T & x , const T & y) {
	(x > y) && (x = y) ;
}

const int mod = 1e9 + 7 ;
const int maxn = 1e5 + 51 ;
struct matrix {
	int a[3][3] ;
	matrix () {
		rep(i , 1 , 2) rep(j , 1 , 2) a[i][j] = 0 ;
	}
	void clr() {
		rep(i , 1 , 2) rep(j , 1 , 2) a[i][j] = 0 ;
		rep(i , 1 , 2) a[i][i] = 1 ;
	}
	bool empty() {
		if(a[1][1] ^ 1) return false ;
		if(a[1][2] || a[2][1]) return false ;
		if(a[2][2] ^ 1) return false ;
		return true ;
	}
	matrix operator * (const matrix & other) const {
		matrix res ;
		rep(i , 1 , 2) rep(j , 1 , 2) {
			res.a[i][j] = 0 ;
			rep(k , 1 , 2) res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j]) % mod ;
		}
		return res ;
	}
	matrix operator + (const matrix & other) const {
		matrix res ;
		rep(i , 1 , 2) rep(j , 1 , 2) res.a[i][j] = (a[i][j] + other.a[i][j] >= mod) ? a[i][j] + other.a[i][j] - mod : a[i][j] + other.a[i][j] ;
		return res ; 
	}
} ;
matrix qwq ;
matrix qpow(matrix a , int k) {
	matrix res = a ; -- k ;
	for( ; k ; a = a * a , k >>= 1)
		if(k & 1) res = res * a ;
	return res ;
}
int n , m ;
int a[maxn] ;
matrix s[maxn << 2] , tag[maxn << 2] ;
void build(int l , int r , int o) {
	tag[o].clr() ;
	if(l == r) {
		s[o] = qpow(qwq , a[l]) ;
		return ;
	}
	int mid = l + r >> 1 ;
	build(l , mid , o << 1) ;
	build(mid + 1 , r , o << 1 | 1) ;
	s[o] = s[o << 1] + s[o << 1 | 1] ;
}
void psd(int o) {
	if(tag[o].empty()) return ;
	tag[o << 1] = tag[o << 1] * tag[o] ;
	tag[o << 1 | 1] = tag[o << 1 | 1] * tag[o] ;
	s[o << 1] = s[o << 1] * tag[o] ;
	s[o << 1 | 1] = s[o << 1 | 1] * tag[o] ;
	tag[o].clr() ;
}
void upd(int a , int b , int l , int r , matrix x , int o) {
	if(a <= l && r <= b) {
		s[o] = s[o] * x ;
		tag[o] = tag[o] * x ;
		return ;
	}
	psd(o) ;
	int mid = l + r >> 1 ;
	if(a <= mid) upd(a , b , l , mid , x , o << 1) ;
	if(b > mid) upd(a , b , mid + 1 , r , x , o << 1 | 1) ;
	s[o] = s[o << 1] + s[o << 1 | 1] ;
}
matrix qry(int a , int b , int l , int r , int o) {
	if(a <= l && r <= b) {
		return s[o] ;
	} psd(o) ;
	int mid = l + r >> 1 ;
	matrix res ;
	if(a <= mid) res = res + qry(a , b , l , mid , o << 1) ;
	if(b > mid) res = res + qry(a , b , mid + 1 , r , o << 1 | 1) ;
	return res ;
}
signed main() {
#ifdef _WIN64
	freopen("testdata.in" , "r" , stdin) ;
#endif
	qwq.a[1][1] = qwq.a[1][2] = qwq.a[2][1] = 1 ;
	qwq.a[2][2] = 0 ;
	in >> n >> m ;
	rep(i , 1 , n) in >> a[i] ;
	build(1 , n , 1) ;
	while(m --) {
		int opt ;
		in >> opt ;
		if(opt == 1) {
			int l , r , v ;
			in >> l >> r >> v ;
			upd(l , r , 1 , n , qpow(qwq , v) , 1) ;
		}
		else {
			int l , r ;
			in >> l >> r ;
			out << qry(l , r , 1 , n , 1).a[1][2] << '\n' ;
		}
	}
	return out.flush(), 0;
}
```

---

## 作者：Suzt_ilymtics (赞：2)

这道题太野蛮了！

[题目传送](https://www.luogu.com.cn/problem/CF718C)

[更~~好~~差的阅读体验？](https://www.cnblogs.com/Silymtics/p/14898122.html)

## Solution

需要维护两个操作，区间加和区间求和。

考虑线段树。

但是斐波那契数怎么搞？

$O(n)$ 预处理？显然会爆掉。

我们知道矩阵快速幂可以在 $\log x$ 的时间内求出一个斐波那契数。

考虑一个及其野蛮的操作，把线段树内维护的点换成矩阵。

我们知道，对于第 $n - 1$ 项，有：

$$\begin{bmatrix}
f_{n - 1} & f_{n - 2}      \\
\end{bmatrix} \times \begin{bmatrix}
1 & 1      \\
1 & 0 
\end{bmatrix} = \begin{bmatrix}
f_{n} & f_{n - 1}      \\
\end{bmatrix}$$

设 $base = \begin{bmatrix}
1 & 1      \\
1 & 0 
\end{bmatrix}$

假设我们有矩阵 $ z = \begin{bmatrix} f_{a_i} & f_{a_i-1} \end {bmatrix}$ ，如果对其加上 $x$ ，我们可以直接进行这么一步操作：

$$\begin{bmatrix} f_{a_i+x} & f_{a_i-1+x} \end {bmatrix} = z \times base^x$$

注意这里的乘法指的是矩阵乘法。

怎么区间合并？直接相加就行。

我们可以手模一下，发现它满足分配律，即：

$$\begin{bmatrix} f_a & f_{a-1} \end{bmatrix} \times base + \begin{bmatrix} f_b & f_{b-1} \end{bmatrix} \times base = \begin{bmatrix} f_a+f_b & f_{a-1} + f_{b-1} \end{bmatrix} \times base$$

所以就可以直接进行合并了！

只要我们把矩阵当成点来看，那么区间修改查询等操作就和普通的线段树没有什么区别了。

预处理复杂度 $O(\sum_{i=1}^n \log a_i)$，单次修改和查询都是 $O(\log x)$，可能会带一个 $8$ 的常数。所以复杂度是正确的，可以通过。

题解区好像有用通项公式直接算的，通过预处理某些东西后跑起来也是飞快。

### Tips

- lazy 要初始化为单位矩阵，push_down 时相关判断也应进行修改。
- 注意取模。
- $a_i <= 2$ 时要单独构造，其他情况使用快速幂即可。
- 修改的时候可以直接把 $base^x$ 这个矩阵传进去，减少计算量。

实现细节看代码吧，~~自以为自己的马蜂很好看~~

## Code 

```cpp
/*
Work by: Suzt_ilymics
Problem: 不知名屑题
Knowledge: 垃圾算法
Time: O(能过)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define int long long
#define LL long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 1e5+5;
const int INF = 1e9+7;
const int mod = 1e9+7;

struct Matrix {
    int a[3][3];
    Matrix () { memset(a, false, sizeof a); }
    void Init() { a[1][1] = a[2][2] = 1, a[1][2] = a[2][1] = 0; }
    bool pd() { return a[1][1] == 1 && a[2][2] == 1 && a[1][2] == 0 && a[2][1] == 0; }
    Matrix operator + (const Matrix b) {
        Matrix res;
        for(int i = 1; i <= 2; ++i) 
            for(int j = 1; j <= 2; ++j) 
                res.a[i][j] = (a[i][j] + b.a[i][j]) % mod;
        return res;
    }
    Matrix operator * (const Matrix b) {
        Matrix res;
        for(int k = 1; k <= 2; ++k) 
            for(int i = 1; i <= 2; ++i) 
                for(int j = 1; j <= 2; ++j) 
                    res.a[i][j] = (res.a[i][j] + a[i][k] * b.a[k][j]) % mod;
        return res;
    }
    Matrix operator ^ (int b) { 
        Matrix res, Base;
        for(int i = 1; i <= 2; ++i) res.a[i][i] = 1;
        for(int i = 1; i <= 2; ++i) for(int j = 1; j <= 2; ++j) Base.a[i][j] = a[i][j];
        while(b) {
            if(b & 1) res = res * Base;
            Base = Base * Base;
            b >>= 1;
        }
        return res;
    }
}base, ans;

int n, m, a[MAXN];

int read(){
    int s = 0, f = 0;
    char ch = getchar();
    while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
    return f ? -s : s;
}

namespace Seg {
    #define lson i << 1
    #define rson i << 1 | 1
    struct Tree {
        Matrix sum, lazy;
    }tree[MAXN << 2];
    void Push_up(int i) { tree[i].sum = tree[lson].sum + tree[rson].sum; }
    void Build(int i, int l, int r) {
        tree[i].lazy.Init();
        if(l == r) {
            if(a[l] == 1) tree[i].sum.a[1][1] = 1;
            else if(a[l] == 2) tree[i].sum.a[1][1] = tree[i].sum.a[1][2] = 1;
            else tree[i].sum = ans * (base ^ (a[l] - 2));
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid), Build(rson, mid + 1, r);
        Push_up(i);
    }
    void Push_down(int i) {
        if(tree[i].lazy.pd()) return ;
        tree[lson].lazy = tree[lson].lazy * tree[i].lazy;
        tree[rson].lazy = tree[rson].lazy * tree[i].lazy;
        tree[lson].sum = tree[lson].sum * tree[i].lazy;
        tree[rson].sum = tree[rson].sum * tree[i].lazy;
        tree[i].lazy.Init();
    }
    void Modify(int i, int l, int r, int L, int R, Matrix k) {
        if(L <= l && r <= R) {
            tree[i].lazy = tree[i].lazy * k, tree[i].sum = tree[i].sum * k;
            return ;
        }
        Push_down(i);
        int mid = (l + r) >> 1;
        if(mid >= L) Modify(lson, l, mid, L, R, k);
        if(mid < R) Modify(rson, mid + 1, r, L, R, k);
        Push_up(i);
    }
    int Query(int i, int l, int r, int L, int R) {
        if(L <= l && r <= R) return tree[i].sum.a[1][1];
        Push_down(i);
        int mid = (l + r) >> 1, ans = 0;
        if(mid >= L) ans = (ans + Query(lson, l, mid, L, R)) % mod;
        if(mid < R) ans = (ans + Query(rson, mid + 1, r, L, R)) % mod;
        return ans;
    }
}

signed main()
{
    base.a[1][1] = base.a[1][2] = base.a[2][1] = 1;
    ans.a[1][1] = ans.a[1][2] = 1;
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    Seg::Build(1, 1, n);
    for(int i = 1, opt, l, r, k; i <= m; ++i) {
        opt = read(), l = read(), r = read();
        if(opt == 1) {
            k = read();
            Seg::Modify(1, 1, n, l, r, base^k);
        } else {
            printf("%lld\n", Seg::Query(1, 1, n, l, r));
        }
    }
    return 0;
}
```

---

## 作者：partychicken (赞：1)

这道题貌似没什么好说的

~~神TM动态dp板子，我觉得跟dp半毛钱关系都没有啊~~

斐波那契用矩阵优化一下，然后用线段树维护一下就能过了，码量不大，封装完了极其好写

$$f[i]=f[i-1]+f[i-2]$$

$$f[n]=\begin{bmatrix}0&1\\1&1\\ \end{bmatrix}^{n-1}\times \begin{bmatrix}0\\1\\ \end{bmatrix}$$

然后，初始值都设为$\begin{bmatrix}1&0\\0&1\\ \end{bmatrix}$,然后做区间乘，区间求和，用线段树维护一下就好了。

具体细节看代码吧，自我感觉码风良好:-D

```
#include<bits/stdc++.h>

using namespace std;

const int mod=1e9+7;

struct Matrix
{
    int a[3][3];

    Matrix()
    {
        memset(a,0,sizeof(a));
    }

    Matrix(bool I)
    {
        memset(a,0,sizeof(a));
        for(int i=1;i<=2;i++)
        {
            a[i][i]=1;
        }
    }

    Matrix operator*(const Matrix &other)const
    {
        Matrix res;
        for(int i=1;i<=2;i++)
        {
            for(int j=1;j<=2;j++)
            {
                for(int k=1;k<=2;k++)
                {
                    res.a[i][j]+=1ll*a[i][k]*other.a[k][j]%mod;
                    res.a[i][j]%=mod;
                }
            }
        }
        return res;
    }

    Matrix operator*=(const Matrix &other)
    {
        return *this=*this*other;
    }

    Matrix operator+(const Matrix &other)const
    {
        Matrix res;
        for(int i=1;i<=2;i++)
        {
            for(int j=1;j<=2;j++)
            {
                res.a[i][j]=a[i][j]+other.a[i][j];
                res.a[i][j]%=mod;
            }
        }
        return res;
    }
};

int n,m;

class SEG
{
    private:
        struct Node
        {
            Matrix sum,mul;

            Node():sum(1),mul(1){}
        }nd[400010];

        void pushdown(int x)
        {
            nd[x<<1].sum*=nd[x].mul;
            nd[x<<1].mul*=nd[x].mul;
            nd[x<<1|1].sum*=nd[x].mul;
            nd[x<<1|1].mul*=nd[x].mul;
            nd[x].mul=Matrix(1);
        }

        void update(int x)
        {
            nd[x].sum=nd[x<<1].sum+nd[x<<1|1].sum;
        }

        void modify(int x,int nl,int nr,int ql,int qr,Matrix val)
        {
            if(nl>qr||nr<ql) return;
            if(nl>=ql&&nr<=qr)
            {
                nd[x].sum*=val;
                nd[x].mul*=val;
                return;
            }
            pushdown(x);
            int mid=nl+nr>>1;
            modify(x<<1,nl,mid,ql,qr,val);
            modify(x<<1|1,mid+1,nr,ql,qr,val);
            update(x);
        }

        Matrix query(int x,int nl,int nr,int ql,int qr)
        {
            if(nl>qr||nr<ql) return Matrix(); 
            if(nl>=ql&&nr<=qr) return nd[x].sum;
            pushdown(x);
            int mid=nl+nr>>1;
            return query(x<<1,nl,mid,ql,qr)+query(x<<1|1,mid+1,nr,ql,qr);
        }

    public:
        void modify(int l,int r,Matrix val)
        {
            modify(1,1,n,l,r,val);
        }

        Matrix query(int l,int r)
        {
            return query(1,1,n,l,r);
        }
}seg;

int sec[100010];

Matrix qpow(Matrix a,int b)
{
    Matrix res(1);
    for(;b;b>>=1)
    {
        if(b&1)
        {
            res=res*a;
        }
        a=a*a;
    }
    return res;
}

int main()
{
    Matrix bas;
    bas.a[1][2]=bas.a[2][2]=bas.a[2][1]=1;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>sec[i];
        seg.modify(i,i,qpow(bas,sec[i]-1));
    }
    for(int i=1;i<=m;i++)
    {
        int opt,l,r;
        cin>>opt>>l>>r;
        if(opt==1)
        {
            int tmp;
            cin>>tmp;
            seg.modify(l,r,qpow(bas,tmp));
        }
        else
        {
            cout<<seg.query(l,r).a[2][2]<<'\n';
        }
    }
}
```

---

## 作者：xiezheyuan (赞：0)

## 题面

定义 $F_i$ 为 斐波那契数列的第 $i$ 项的数。你需要实现一个数据结构 $a[]$，支持：

`1 l r x`：将 $[l,r]$ 的数加上 $x$。

`2 l r`：求 $\sum\limits_{i=l}^{r}{F_{a[i]}}$。

$1 \le n,m \le 10^{5},1 \le a[i] \le 10^{9}$

## 思路

不难看出是线段树，但是怎么计算 $F_i$ 呢？

如果暴力去计算 $F_i$，显然是不靠谱的（时间复杂度是 $O(i)$）。

如果使用斐波那契末项计算公式（参见 [P1720 月落乌啼算钱（斐波那契数列）](https://www.luogu.com.cn/problem/P1720)）也不靠谱，不容易维护。

如果做过 [P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962) 的同学可能知道，可以用矩阵快速幂计算。

大致公式如下：

$$([1\ 1] \times \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^{i-1})_{1,2} = F_i$$

[OI-Wiki](https://oi-wiki.org/math/matrix/#_9) 上有证明。

然后就是维护一个区间修改区间查询线段树。时间复杂度是 $O(n\log^2n)$。

## 代码

代码里面有封装好了的矩阵模板，供大家随意使用。

```cpp
#include <bits/stdc++.h>
#define ls (i<<1)
#define rs (i<<1|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;

const int MOD = 1e9+7;

struct Matrix{
	int a[3][3];
	const int size = 2;
	Matrix(){
		memset(a,0,sizeof(a));
	}
	Matrix(int aba){
		a[aba][aba]=1;
		a[aba][aba+1]=0;
		a[aba+1][aba]=0;
		a[aba+1][aba+1]=1;
	}
	Matrix(int A,int b,int c,int d){
		a[1][1]=A;
		a[1][2]=b;
		a[2][1]=c;
		a[2][2]=d;
	}
	Matrix operator*(const Matrix &ano) const {
		Matrix ans;
		for(int i=1;i<=size;i++){
			for(int k=1;k<=size;k++){
				for(int j=1;j<=size;j++){
					ans.a[i][k]=(ans.a[i][k]+a[i][j]*ano.a[j][k])%MOD;
				}
			}
		}
		return ans;
	}	
	Matrix operator+(const Matrix aa){
		Matrix res;
		for(int i=1;i<=size;i++){
			for(int j=1;j<=size;j++){
				res.a[i][j]=a[i][j]+aa.a[i][j];
				res.a[i][j]%=MOD;
			}
		}
		return res;
	}
	void operator=(const Matrix A){
		for(int i=1;i<=size;i++){
			for(int j=1;j<=size;j++){
				a[i][j]=A.a[i][j];
			}
		}
	}
	bool empty(){
		return (a[1][1]==0)&&(a[1][2]==0)&&(a[2][1]==0)&&(a[2][2]==0);
	}
	Matrix operator^(int power){
		Matrix res(1);
		Matrix base = (*this);
		while(power){
			if(power&1){
				res=res*base;
			}
			base=base*base;
			power>>=1;
		}
		return res;
	}
};



const int SIZE = 1e5+5;
Matrix t[SIZE<<2],tag[SIZE<<2];
int v[SIZE];
const Matrix unit(1);
int n,m;

inline void pushup(int i){
	t[i]=t[ls]+t[rs];
}

void build(int i,int l,int r){
	tag[i]=unit;
	if(l==r){
		t[i]=Matrix(1,1,0,0)*(Matrix(1,1,1,0)^(v[l]-1));
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(i);
}

void pushdown(int i){
	if(tag[i].empty()){
		return;
	}
	t[ls]=t[ls]*tag[i];
	tag[ls]=tag[ls]*tag[i];
	t[rs]=t[rs]*tag[i];
	tag[rs]=tag[rs]*tag[i];
	tag[i]=unit;
}

void update(int i,int ql,int qr,int l,int r,Matrix x){
	if(ql<=l && qr>=r){
		t[i]=t[i]*x;
		tag[i]=tag[i]*x;
		return;
	}
	pushdown(i);
	if(ql<=mid){
		update(ls,ql,qr,l,mid,x);
	}
	if(qr>mid){
		update(rs,ql,qr,mid+1,r,x);
	}
	pushup(i);
}

Matrix query(int i,int ql,int qr,int l,int r){
	if(ql<=l && qr>=r){
		return t[i];
	}
	pushdown(i);
	Matrix res;
	if(ql<=mid){
		res = res + query(ls,ql,qr,l,mid);
	}
	if(qr > mid){
		res = res+query(rs,ql,qr,mid+1,r);
	}
	return res;
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>v[i];
	}
	build(1,1,n);
	while(m--){
		int op,l,r,x;
		cin>>op;
		if(op==1){
			cin>>l>>r>>x;
			update(1,l,r,1,n,Matrix(1,1,1,0)^x);
		}
		else{
			cin>>l>>r;
			cout<<(query(1,l,r,1,n).a[1][2]%MOD)<<'\n';
		}
	}
	return 0;
}

```


---

## 作者：orz_z (赞：0)

### 题目大意

在本题中，我们用 $f_i$ 来表示第 $i$ 个斐波那契数 $f_1=f_2=1,f_i=f_{i-1}+f_{i-2}(i\ge 3)$。

给定一个 $n$ 个数的序列 $a$。

有 $m$ 次操作，操作有两种：

* 将 $a_l\sim a_r$ 加上 $x$。

* 求 $\displaystyle\left(\sum_{i=l}^r f_{a_i}\right)\bmod (10^9+7)$。

$1\le n,m\le 10^5$，$1\le a_i\le 10^9$。

### 解题思路

两个操作，区间加，区间求和。

显然线段树。

斐波那契数怎么搞？

$\mathcal O(n)$ 预处理显然爆。

显然用 $\mathcal O(\log n)$ 的矩阵快速幂来求。

设 $base=\begin{pmatrix}1&1\\1&0\end{pmatrix}$，则有 $\begin{bmatrix} f_n && f_{n-1} \\ f_{n-1} && f_{n-2}\end{bmatrix}=\begin{pmatrix}1&0\\0&1\end{pmatrix} * base^{n-1}$。

由于矩阵具有分配律，即 $a\times b+a\times c=a\times(b+c)$，所以对于一段区间的矩阵可以相加维护，所以 $\sum\limits_{i=l}^{r}f(a_i+x)=f_x*\sum\limits_{i=l}^{r}(a_i)$。

线段树满足所有条件！！！

线段树上每个点都搞成一个矩阵即可。

具体请看代码。

### CODE

```cpp
#include <bits/stdc++.h>

#define int long long

inline int read()
{
    int s = 0, f = 0;
    char ch = getchar();
    while (!isdigit(ch))
        f |= (ch == '-'), ch = getchar();
    while (isdigit(ch))
        s = (s << 1) + (s << 3) + ch - '0', ch = getchar();
    return f ? -s : s;
}

using namespace std;

const int _ = 1e5 + 5;

const int INF = 1e9 + 7;

const int mod = 1e9 + 7;

struct Matrix
{
    int a[3][3];
    Matrix() { memset(a, false, sizeof a); }
    void Init() { a[1][1] = a[2][2] = 1, a[1][2] = a[2][1] = 0; }
    bool pd() { return a[1][1] == 1 && a[2][2] == 1 && a[1][2] == 0 && a[2][1] == 0; }
    Matrix operator+(const Matrix b)
    {
        Matrix res;
        for (int i = 1; i <= 2; ++i)
            for (int j = 1; j <= 2; ++j)
                res.a[i][j] = (a[i][j] + b.a[i][j]) % mod;
        return res;
    }
    Matrix operator*(const Matrix b)
    {
        Matrix res;
        for (int k = 1; k <= 2; ++k)
            for (int i = 1; i <= 2; ++i)
                for (int j = 1; j <= 2; ++j)
                    res.a[i][j] = (res.a[i][j] + a[i][k] * b.a[k][j]) % mod;
        return res;
    }
    Matrix operator^(int b)
    {
        Matrix res, Base;
        for (int i = 1; i <= 2; ++i)
            res.a[i][i] = 1;
        for (int i = 1; i <= 2; ++i)
            for (int j = 1; j <= 2; ++j)
                Base.a[i][j] = a[i][j];
        while (b)
        {
            if (b & 1)
                res = res * Base;
            Base = Base * Base;
            b >>= 1;
        }
        return res;
    }
} base, ans;

int n, m, a[_];

namespace Seg_tree
{
#define lson i << 1
#define rson i << 1 | 1
    struct Tree
    {
        Matrix sum, lazy;
    } tree[_ << 2];
    void Push_up(int i) { tree[i].sum = tree[lson].sum + tree[rson].sum; }
    void Build(int i, int l, int r)
    {
        tree[i].lazy.Init();
        if (l == r)
        {
            if (a[l] == 1)
                tree[i].sum.a[1][1] = 1;
            else if (a[l] == 2)
                tree[i].sum.a[1][1] = tree[i].sum.a[1][2] = 1;
            else
                tree[i].sum = ans * (base ^ (a[l] - 2));
            return;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid), Build(rson, mid + 1, r);
        Push_up(i);
    }
    void Push_down(int i)
    {
        if (tree[i].lazy.pd())
            return;
        tree[lson].lazy = tree[lson].lazy * tree[i].lazy;
        tree[rson].lazy = tree[rson].lazy * tree[i].lazy;
        tree[lson].sum = tree[lson].sum * tree[i].lazy;
        tree[rson].sum = tree[rson].sum * tree[i].lazy;
        tree[i].lazy.Init();
    }
    void Modify(int i, int l, int r, int L, int R, Matrix k)
    {
        if (L <= l && r <= R)
        {
            tree[i].lazy = tree[i].lazy * k, tree[i].sum = tree[i].sum * k;
            return;
        }
        Push_down(i);
        int mid = (l + r) >> 1;
        if (mid >= L)
            Modify(lson, l, mid, L, R, k);
        if (mid < R)
            Modify(rson, mid + 1, r, L, R, k);
        Push_up(i);
    }
    int Query(int i, int l, int r, int L, int R)
    {
        if (L <= l && r <= R)
            return tree[i].sum.a[1][1];
        Push_down(i);
        int mid = (l + r) >> 1, ans = 0;
        if (mid >= L)
            ans = (ans + Query(lson, l, mid, L, R)) % mod;
        if (mid < R)
            ans = (ans + Query(rson, mid + 1, r, L, R)) % mod;
        return ans;
    }
}

signed main()
{
    base.a[1][1] = base.a[1][2] = base.a[2][1] = 1;
    ans.a[1][1] = ans.a[1][2] = 1;
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    Seg_tree::Build(1, 1, n);
    for (int i = 1, opt, l, r, k; i <= m; ++i)
    {
        opt = read(), l = read(), r = read();
        if (opt == 1)
        {
            k = read();
            Seg_tree::Modify(1, 1, n, l, r, base ^ k);
        }
        else
        {
            printf("%lld\n", Seg_tree::Query(1, 1, n, l, r));
        }
    }
    return 0;
}
```



---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/CF718C)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到区间修改和查询，不难想到使用线段树维护区间。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑到初始的$a$和增加的$x$总是正数，我们便不难想到使用矩阵和向量来实现动态维护每一个位置上面的$f(a_i)$。设转移矩阵为$T$，初始向量$\boldsymbol p$为$\begin{bmatrix}f(1)&f(0)\end{bmatrix}$（$f(0)=0$）。则位置$i$上的初始值为$\boldsymbol p\times T^{a_i}$。每次将区间$[l,r]$的$a$加上$x$，就相当于在区间$[l,r]$乘上$T^x$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;查询就把区间的向量求和，再取第一项就好了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;时间复杂度为$O(2^3m\log_2n)$
# 代码
```cpp
#include <cstdio>
#include <cstring>

const int mod = 1e9 + 7;
const int MAXN = 1e5 + 5, MAXSIZ = 3;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ){ f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ), x = -x; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

struct matrix
{
    int mat[MAXSIZ][MAXSIZ], n, m;
    matrix(){ n = m = 0, memset( mat, 0, sizeof mat ); }
    matrix( const int N, const int M ) { n = N, m = M, memset( mat, 0, sizeof mat ); }
    int* operator [] ( const int indx ) { return mat[indx]; }
    matrix operator * ( matrix other ) const 
    {
        matrix ret = matrix( n, other.m );
        for( int i = 1 ; i <= n ; i ++ )
            for( int j = 1 ; j <= m ; j ++ )
                if( mat[i][j] )
                    for( int k = 1 ; k <= ret.m ; k ++ ) 
                    {
                        ret[i][k] += 1ll * mat[i][j] * other[j][k] % mod;
                        if( ret[i][k] > mod ) ret[i][k] -= mod;
                    }
        return ret;
    }
    bool operator == ( matrix other ) const
    {
        if( n ^ other.n || m ^ other.m ) return false;
        for( int i = 1 ; i <= n ; i ++ )
            for( int j = 1 ; j <= m ; j ++ )
                if( mat[i][j] ^ other[i][j] ) return false;
        return true;
    }
    bool operator != ( matrix other ) const { return ! ( *this == other ); }
    void operator *= ( matrix other ) { *this = *this * other; }
};

struct vector
{
    int vec[MAXSIZ], n;
    vector(){ n = 0, memset( vec, 0, sizeof vec ); }
    vector( const int N ) { n = N, memset( vec, 0, sizeof vec ); }
    int& operator [] ( const int indx ) { return vec[indx]; }
    vector operator * ( matrix other ) const
    {
        vector ret = vector( n );
        for( int i = 1 ; i <= n ; i ++ )
            for( int j = 1 ; j <= ret.n ; j ++ ) 
            {
                ret[i] += 1ll * vec[j] * other[j][i] % mod;
                if( ret[i] > mod ) ret[i] -= mod;
            }
        return ret;
    }
    vector operator + ( vector other ) const 
    {
        vector ret = *this;
        for( int i = 1 ; i <= n ; i ++ ) 
        {
            ret[i] += other[i];
            if( ret[i] > mod ) ret[i] -= mod;
        }
        return ret;
    }
    void operator *= ( matrix other ) { *this = *this * other; }
    void operator += ( vector other ) { *this = *this + other; }
};

struct segmentTreeNode
{
	vector s; matrix tag;
	#define s( a ) ( segTree[a].s )
	#define tag( a ) ( segTree[a].tag )
}segTree[MAXN << 2];

matrix I, B;
vector A;

int a[MAXN];
int N, M;

void upt( const int x ) { s( x ) = s( x << 1 ) + s( x << 1 | 1 ); }
void prod( const int x, const matrix v ) { s( x ) *= v, tag( x ) *= v; }
void normalize( const int x ) { if( tag( x ) != I ) prod( x << 1, tag( x ) ), prod( x << 1 | 1, tag( x ) ), tag( x ) = I; }

void init()
{ 
	I = matrix( 2, 2 ); for( int i = 1 ; i <= 2 ; i ++ ) I[i][i] = 1; 
	B = matrix( 2, 2 ); B[1][1] = B[2][1] = B[1][2] = 1;
	A = vector( 2 ); A[1] = 1;
}

matrix qkpow( matrix base, int indx )
{
	if( indx < 0 ) return I;
	matrix ret = I;
	while( indx )
	{
		if( indx & 1 ) ret *= base;
		base *= base, indx >>= 1;
	}
	return ret;
}

void build( const int u, const int l, const int r )
{
	if( l > r ) return ;
	tag( u ) = I; int mid = l + r >> 1;
	if( l == r ) { s( u ) = A * qkpow( B, a[l] - 1 ); return; }
	build( u << 1, l, mid ), build( u << 1 | 1, mid + 1, r );
	upt( u );
}

void update( const int x, const int l, const int r, const int segL, const int segR, const matrix v )
{
	int mid = l + r >> 1;
	if( segL <= l && r <= segR ) { prod( x, v ); return; }
	if( l == r ) return; normalize( x );
	if( segL <= mid ) update( x << 1, l, mid, segL, segR, v );
	if( segR > mid ) update( x << 1 | 1, mid + 1, r, segL, segR, v );
	upt( x ); 
}

int query( const int x, const int l, const int r, const int segL, const int segR )
{
	int mid = l + r >> 1, ret = 0;
	if( segL <= l && r <= segR ) return s( x )[1];
	if( l == r ) return 0; normalize( x );
	if( segL <= mid ) ( ret += query( x << 1, l, mid, segL, segR ) ) %= mod;
	if( segR > mid ) ( ret += query( x << 1 | 1, mid + 1, r, segL, segR ) ) %= mod;
	return ret;
}

int main()
{
	matrix tmp;
	int opt, optL, optR, optV;
	init();
	read( N ), read( M );
	for( int i = 1 ; i <= N ; i ++ ) read( a[i] );
	build( 1, 1, N );
	while( M -- )
	{
		read( opt ), read( optL ), read( optR );
		if( opt == 1 ) 
		{
			read( optV );
			tmp = qkpow( B, optV );
			update( 1, 1, N, optL, optR, tmp );
		}
		else write( query( 1, 1, N, optL, optR ) ), putchar( '\n' );
	}
	return 0;
}
```

---

## 作者：i207M (赞：0)

## 题目总结

![](https://cdn.luogu.com.cn/upload/pic/20451.png )

## 数据范围

$ 1<=n<=100000 , 1<=m<=100000 $

## 解题思路

考虑到快速求出斐波那契数列的值，我们可以考虑矩阵乘法，而此题询问的时区间和，我们可以用线段树维护；

![](https://cdn.luogu.com.cn/upload/pic/20454.png )

![](https://cdn.luogu.com.cn/upload/pic/20455.png )

对于区间，$ [l,r] $，线段树的节点存放的是此区间内的和，以及lazy标记；

其实我的做法和上面有一点不一样；初始化时，每个节点的值为base矩阵的X次方（不是X-1），以为我计算答案时，乘以的矩阵是$[f[0],f[-1]]$，即$[0,1]$，所以我的答案就是$m[2][1]$；然后一层层的pushup，即求出左右子区间的矩阵的和（矩阵具有结合律）

修改时找到对应区间，然后打标记，pushup即可；

每次查询时求出对应区间的矩阵和即可，记得pushdown；

## 易错误区

别忘了初始化sz；

记得及时下放标记！我会另开一篇来写；

**最重要的：此题卡常！优化了半天~~还是很慢~~**

一些细节优化一下，快读快输，inline，define；

比较重要的是pushdown操作，在pushdown时要特判lazy标记是否为单位元，这样可以直接跳过，这样优化很大；

## 代码展示

```cpp
%:pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
using namespace std;
#define ll long long
#define ull unsigned long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
#define int ll
il char gc() {
	static const int BS = 1 << 22;
	static unsigned char buf[BS], *st, *ed;
	if (st == ed) ed = buf + fread(st = buf, 1, BS, stdin);
	return st == ed ? EOF : *st++;
}
#define gc getchar
template<class T>void in(T &x)
{
	x = 0; bool f = 0; char c = gc();
	while (c < '0' || c > '9') {if (c == '-') f = 1; c = gc();}
	while (isdigit(c)) {x = (x << 3) + (x << 1) + (c ^ 48); c = gc();}
	if (f) x = -x;
}
//#undef gc
void out(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) out(x / 10);
	putchar(x % 10 + '0');
}
#define N 100010<<3
#define Maxsz 4
#define md 1000000007
il void mod(int &x) {
	while (x > md) x -= md;
	while (x < 0) x += md;
}
struct Mat {
	int sz;
	int m[Maxsz][Maxsz];
	il void clear() {mem0(m);}
	Mat () {sz = 2; clear();}
	Mat operator*(const Mat &x)const {
		Mat res; res.sz = sz;
		for (ri i = 1; i <= sz; ++i) {
			for (ri k = 1; k <= sz; ++k) {
				for (ri j = 1; j <= sz; ++j) {
					mod(res.m[i][j] += m[i][k] * x.m[k][j] % md);
				}
			}
		}
		return res;
	}
	void operator*=(const Mat &x) {
		*this = (*this) * x;
	}
	Mat operator+(const Mat &x)const {
		Mat res = *this;
		for (ri i = 1; i <= sz; ++i) {
			for (ri j = 1; j <= sz; ++j) {
				mod(res.m[i][j] += x.m[i][j]);
			}
		}
		return res;
	}
	void operator+=(const Mat &x) {
		for (ri i = 1; i <= sz; ++i) {
			for (ri j = 1; j <= sz; ++j) {
				mod(m[i][j] += x.m[i][j]);
			}
		}
	}
	void toe() {
		clear();
		for (ri i = 1; i <= sz; ++i)
			m[i][i] = 1;
	}
	il bool empty() {
		return (m[1][1] == 1 && m[2][2] == 1 && m[1][2] == 0 && m[2][1] == 0);
	}
	void print() {
		for (ri i = 1; i <= sz; ++i) {
			for (ri j = 1; j <= sz; ++j)
				printf("%lld ", m[i][j]);
			puts("");
		}
	}
	Mat qpow(int x) {
		Mat res = *this, mul = res; --x;
		for (; x; x >>= 1, mul *= mul) if (x & 1) res *= mul;
		return res;
	}
};
#define ls (x<<1)
#define rs (x<<1|1)
#define gm int mid=(l+r)>>1
#define now tre[x]
Mat tre[N];
Mat bs;
int n, m, a[N], rt;
Mat lz[N];
il void up(int x) {
	tre[x] = tre[ls] + tre[rs];
}
void build(int x, int l, int r) {
	lz[x].toe();
	if (l == r) {
		now = bs.qpow(a[l]);
		return;
	}
	gm;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	up(x);
}
il void down(int x) {
	if (!lz[x].empty()) {
		now *= lz[x];
		lz[ls] *= lz[x], lz[rs] *= lz[x], lz[x].toe();
	}
}
void update(int x, int l, int r, int ql, int qr, const Mat &k) {
	if (ql <= l && r <= qr) {
		lz[x] *= k;
		down(x);
		return;
	}
	down(x);
	gm;
	if (ql <= mid) update(ls, l, mid, ql, qr, k);
	else down(ls);
	if (mid < qr) update(rs, mid + 1, r, ql, qr, k);
	else down(rs);
	up(x);
}
Mat query(int x, int l, int r, int ql, int qr) {
	down(x);
	if (ql <= l && r <= qr) {
		return tre[x];
	}
	gm;
	Mat ret;
	if (ql <= mid) ret = query(ls, l, mid, ql, qr);
	if (mid < qr) ret += query(rs, mid + 1, r, ql, qr);
	return ret;
}
signed main() {
	bs.m[1][1] = bs.m[1][2] = bs.m[2][1] = 1;
	in(n), in(m);
	for (ri i = 1; i <= n; ++i) in(a[i]);
	build(rt = 1, 1, n);
	int op, l, r, x; Mat t;
	while (m--) {
		in(op), in(l), in(r);
		if (op == 1) {
			in(x);
			t = bs.qpow(x);
			update(rt, 1, n, l, r, t);
		}
		else {
			out(query(rt, 1, n, l, r).m[2][1]);
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：硫代硫酸钠 (赞：0)

矩阵快速幂+线段树

考虑F(i)=A^i, 其中A是斐波那契矩阵快速幂中的矩阵。

注意到F(i+x)= A^i$\times$A^x

故$\Sigma_l^r$ F(i+x)=$\Sigma_l^r$ F(i)$\times$A^x

线段树维护即可。

[我的代码本地能过交上去不能过，真是有毒]

[不过既然luogu允许非正解我就不要脸地交了]

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define size 400010
#define ll long long
#define db double
#define il inline
#define rint register int
#define gc getchar()
#define rep(i,s,n) for (register int i=s;i<=n;i++)
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1 
#define mmid int mid=(l+r)>>1;
const ll mod=1e9+7;

using namespace std;

il ll r()
{
	char c; ll x,f=1;
	for (c=gc;!isdigit(c);c=gc) if (c=='-') f=-1; x=c-'0';
	for (c=gc;isdigit(c);c=gc) x=x*10+c-'0'; return x;
}

struct jz {ll a[3][3];} matr;
void clear(jz &x) {memset(x.a,0,sizeof(x.a));}
void setone(jz &x) {clear(x); rep(i,1,2) x.a[i][i]=1;}
void setfib(jz &x) { clear(x);x.a[1][1]=x.a[2][1]=x.a[1][2]=1;}
void turn(jz from,jz &to) {rep(i,1,2) rep(j,1,2) to.a[i][j]=from.a[i][j];}
bool notone(jz x) {if (x.a[1][1]==1&&x.a[2][2]==1&&x.a[1][2]==0&&x.a[2][1]==0) return 0; return 1;} 
jz plu(jz a,jz b)
{
	jz c; clear(c);
	rep(i,1,2) rep(j,1,2) c.a[i][j]=(ll)(a.a[i][j]+b.a[i][j])%mod;
	return c;
}

jz mul(jz a,jz b)
{
	jz c; clear(c);
	rep(k,1,2) rep(i,1,2) rep(j,1,2)
		c.a[i][j]= (c.a[i][j]+(ll)a.a[i][k]*b.a[k][j]%mod)%mod; 
	return c;
}

jz ksm(jz x,ll y)
{
	jz res; setone(res);
	if (y<=0) return res;
	while (y)
	{
		if (y&1) turn(mul(res,x),res);
		turn (mul(x,x),x);
		y>>=1;
	}
}

jz tree[size],col[size],A[size];
ll a[size],n,m;

void update(int rt) {turn(plu(tree[rt<<1],tree[rt<<1|1]),tree[rt]);}

void build(int l,int r,int rt)
{
	if (l==r) 
	{
		turn(A[l],tree[rt]); setone(col[rt]); return ;
	}
	mmid; build(lson);build(rson); update(rt);
}

void color(int l,int r,int rt,jz tmp1) 
{
	 turn(mul(tmp1,col[rt]),col[rt]);
	turn(mul(tmp1,tree[rt]),tree[rt]);
}

void pushc(int l,int r,int rt)
{
	if (notone(col[rt]))
	{
		mmid; color(lson,col[rt]); color(rson,col[rt]);
	}
	setone(col[rt]);
}

void modify(int l,int r,int rt,int nowl,int nowr, jz v)
{
	if (nowl<=l&&r<=nowr) {color(l,r,rt,v); return;}
	pushc(l,r,rt); mmid;
	if (nowl<=mid) modify(lson,nowl,nowr,v);
	if (mid<nowr) modify(rson,nowl,nowr,v); update(rt);
}

jz query(int l,int r,int rt,int nowl,int nowr)
{
	if (nowl<=l&&r<=nowr) return tree[rt];
	pushc(l,r,rt); mmid; jz ans; clear(ans);
	if (nowl<=mid) turn(plu(query(lson,nowl,nowr),ans),ans);
	if (mid<nowr) turn(plu(query(rson,nowl,nowr),ans),ans);
 	return ans;
	
}


int main()
{
	freopen("01.in","r",stdin);
	freopen("02.out","w",stdout);
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&a[i]),setfib(A[i]);
	rep(i,1,n) turn (ksm(A[i],a[i]),A[i]);
	rep(i,1,n<<2) setone(col[i]);
	build(1,n,1);
	rep(i,1,m)
	{
		int dir,x,y,z;
		scanf("%d%d%d",&dir,&x,&y);
		if (dir==1)
		{
			scanf("%d",&z); jz tmp; setfib(tmp); turn(ksm(tmp,z),tmp);
			modify(1,n,1,x,y,tmp);
		}
		else 
		{
			jz tmp; clear(tmp); turn (query(1,n,1,x,y),tmp);
			cout<<tmp.a[1][2]%mod<<endl;
		}
	}
	return 0;
}



```

---

## 作者：ExplodingKonjac (赞：0)

题意：维护一段序列，支持区间加和区间斐波那契数列和。

## 解题思路

显然这题的瓶颈就在于区间加，因为，一堆斐波那契数的下标同时加多少似乎并没有什么公式或者性质……

于是我开始了胡乱思考（

我们知道斐波那契数列的通项公式：

$$
f_n=\frac{1}{\sqrt5}\left(\left(\frac{1+\sqrt5}{2}\right)^n-\left(\frac{1-\sqrt5}{2}\right)^n\right)
$$

然后这里面下标都变成了指数，那么只用维护两三个量，区间加就变成了区间乘……手写一下无理数运算……貌似也可以做。。。

正解显然不是这样，但确实需要把区间加变成区间乘。有什么东西可以通过乘法方便地维护一个递推数列呢？

（好像真有人这么做，还跑得很快？）

## 使用矩阵

你肯定已经学过了[矩阵乘法](https://baike.baidu.com/item/%E7%9F%A9%E9%98%B5%E4%B9%98%E6%B3%95/5446029)和[矩阵快速幂](https://zhuanlan.zhihu.com/p/137677246)。

想想你做过的第一道矩阵快速幂题：求 $f_i\ (1\le i\le 10^{18})$。

我们有：

$$
\begin{bmatrix}1&1\\1&0\end{bmatrix}\begin{bmatrix}f_i\\f_{i-1}\end{bmatrix}=\begin{bmatrix}f_{i+1}\\f_i\end{bmatrix}
$$

那么我们就可以用**线段树**在序列上每一个位置**维护一个矩阵** $A_i$，假设原数列为 $\{a_i\}$，则

$$
A_i=\begin{bmatrix}f_{a_i}\\f_{a_i-1}\end{bmatrix}
$$

线段树合并区间时可以直接把两个矩阵相加。

区间修改的时候，由于矩阵乘法**满足分配律**，所以区间加的时候可以直接乘上 $\displaystyle{\begin{bmatrix}1&1\\1&0\end{bmatrix}}^x$，$x$为需要加的数。

至于查询时就将包含的区间的矩阵中信息加起来就可以了。

实现细节见代码：

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MOD=1e9+7;
int n,m;
class Matrix22 //实现矩阵类
{
 private:
    LL a[2][2]; //矩阵用2*2的数组储存
 public:
    Matrix22(LL a00=0,LL a01=0,LL a10=0,LL a11=0) //构造函数
        { a[0][0]=a00,a[0][1]=a01,a[1][0]=a10,a[1][1]=a11; }
    inline LL &operator ()(int i,int j) //更加方便地获取元素
        { return a[i][j]; }
    //重载加法和乘法
    //因为矩阵大小是固定的所以没有使用for循环
    //而且这样常数还比较小（？）
    friend inline Matrix22 operator +(const Matrix22 &x,const Matrix22 &y)
    {
        return Matrix22((x.a[0][0]+y.a[0][0])%MOD,
                        (x.a[0][1]+y.a[0][1])%MOD,
                        (x.a[1][0]+y.a[1][0])%MOD,
                        (x.a[1][1]+y.a[1][1])%MOD);
        //对应项相加
    }
    friend inline Matrix22 operator *(const Matrix22 &x,const Matrix22 &y)
    {
        return Matrix22((x.a[0][0]*y.a[0][0]+x.a[0][1]*y.a[1][0])%MOD,
                        (x.a[0][0]*y.a[0][1]+x.a[0][1]*y.a[1][1])%MOD,
                        (x.a[1][0]*y.a[0][0]+x.a[1][1]*y.a[1][0])%MOD,
                        (x.a[1][0]*y.a[0][1]+x.a[1][1]*y.a[1][1])%MOD);
        //用矩阵乘法法则推一下就可以得到了
    }
}base,trans,a[100005];
template<typename T>
T quickPow(T a,LL b) //快速幂
{
    T res=a;b--;
    while(b)
    {
        if(b&1)	res=res*a;
        a=a*a,b>>=1;
    }
    return res;
}
struct TreeNode //线段树节点，我用了指针写法
{
    Matrix22 val,tag;
    TreeNode *lc,*rc;
    TreeNode(): val(),tag(1,0,0,1) //tag需要初始化为单位矩阵 
        { lc=rc=nullptr; }
}*rt;
typedef TreeNode *pNode;
void build(int l,int r,pNode &i=rt) //建树
{
    i=new TreeNode;
    if(l==r)	i->val=a[l];
    else
    {
        int mid=(l+r)>>1;
        build(l,mid,i->lc),build(mid+1,r,i->rc);
        i->val=i->lc->val+i->rc->val;
    }
}
inline void addTag(pNode &i,const Matrix22 &tg) //打tag
    { i->val=tg*i->val,i->tag=tg*i->tag; } //注意这里的tg需要左乘
                                           //矩阵乘法没有交换律，反过来就错了
inline void pushdown(pNode &i) //下传标记
{
    addTag(i->lc,i->tag),addTag(i->rc,i->tag);
    i->tag=Matrix22(1,0,0,1); //自己的标记重新赋为单位矩阵
}
void modify(int lq,int rq,const Matrix22 &x,int l=1,int r=n,pNode i=rt)
// 区间修改，和板子一模一样
{
    if(l>=lq && r<=rq)	addTag(i,x);
    else
    {
        int mid=(l+r)>>1;
        pushdown(i);
        if(mid>=lq) modify(lq,rq,x,l,mid,i->lc);
        if(mid<rq)  modify(lq,rq,x,mid+1,r,i->rc);
        i->val=i->lc->val+i->rc->val;
    }
}
LL query(int lq,int rq,int l=1,int r=n,pNode &i=rt)
// 区间查询
{
    if(l>=lq && r<=rq)	return i->val(0,0); //这里矩阵的(0,0)位置是答案
    LL mid=(l+r)>>1,ans=0;
    pushdown(i);
    if(mid>=lq) ans+=query(lq,rq,l,mid,i->lc);
    if(mid<rq)  ans+=query(lq,rq,mid+1,r,i->rc);
    return ans%MOD;
}
int main()
{
    scanf("%d%d",&n,&m);
    base(1,0)=trans(0,0)=trans(0,1)=trans(1,0)=1;
    // 你看，很方便吧（
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        a[i]=quickPow(trans,x)*base; //数组a初始化
    }
    build(1,n);
    while(m--) // 应该不用注释了
    {
        int opt,l,r,x;
        scanf("%d%d%d",&opt,&l,&r);
        if(opt==1)
            scanf("%d",&x),modify(l,r,quickPow(trans,x));
        else
            printf("%lld\n",query(l,r));
    }
    return 0;
}
```

这题有50多个测试点，每个测试点5s时限，因此评测异常艰辛（

调完样例后居然一遍过了，而且总时间34s感觉还行

---

