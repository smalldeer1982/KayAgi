# Pokémon Army (hard version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that the easy version has no swap operations. You can make hacks only if all versions of the problem are solved.

Pikachu is a cute and friendly pokémon living in the wild pikachu herd.

But it has become known recently that infamous team R wanted to steal all these pokémon! Pokémon trainer Andrew decided to help Pikachu to build a pokémon army to resist.

First, Andrew counted all the pokémon — there were exactly $ n $ pikachu. The strength of the $ i $ -th pokémon is equal to $ a_i $ , and all these numbers are distinct.

As an army, Andrew can choose any non-empty subsequence of pokemons. In other words, Andrew chooses some array $ b $ from $ k $ indices such that $ 1 \le b_1 < b_2 < \dots < b_k \le n $ , and his army will consist of pokémons with forces $ a_{b_1}, a_{b_2}, \dots, a_{b_k} $ .

The strength of the army is equal to the alternating sum of elements of the subsequence; that is, $ a_{b_1} - a_{b_2} + a_{b_3} - a_{b_4} + \dots $ .

Andrew is experimenting with pokémon order. He performs $ q $ operations. In $ i $ -th operation Andrew swaps $ l_i $ -th and $ r_i $ -th pokémon.

Andrew wants to know the maximal stregth of the army he can achieve with the initial pokémon placement. He also needs to know the maximal strength after each operation.

Help Andrew and the pokémon, or team R will realize their tricky plan!

## 说明/提示

Let's look at the third test case:

Initially we can build an army in such way: \[1 2 5 4 3 6 7\], its strength will be $ 5-3+7=9 $ .

After first operation we can build an army in such way: \[2 1 5 4 3 6 7\], its strength will be $ 2-1+5-3+7=10 $ .

After second operation we can build an army in such way: \[2 1 5 4 3 7 6\], its strength will be $ 2-1+5-3+7=10 $ .

After third operation we can build an army in such way: \[2 1 4 5 3 7 6\], its strength will be $ 2-1+5-3+7=10 $ .

After forth operation we can build an army in such way: \[1 2 4 5 3 7 6\], its strength will be $ 5-3+7=9 $ .

After all operations we can build an army in such way: \[1 4 2 5 3 7 6\], its strength will be $ 4-2+5-3+7=11 $ .

## 样例 #1

### 输入

```
3
3 1
1 3 2
1 2
2 2
1 2
1 2
1 2
7 5
1 2 5 4 3 6 7
1 2
6 7
3 4
1 2
2 3```

### 输出

```
3
4
2
2
2
9
10
10
10
9
11```

# 题解

## 作者：Mophie (赞：11)

# [CF1420C2](https://www.luogu.com.cn/problem/CF1420C2)题解

赛后查看代码发现一堆人都是线段树来搞，这对于一道C2来讲有点太麻烦了一些吧……

我们可以发现，这是一个一加一减的形式，然后我看几个数据，可以发现——

每次的加都是一段递增数列的最后一项，每次减都是一段递减数列的最后一项，也就是一段递增的第一项。

这个事情还是非常好证明的，用贪心就可以证出。

如果这样求加减的话，那这道题就简单了。

结论是如果相邻两项 $a_i>a_{i+1}$ ，则 $ans=ans+(a_i-a_{i+1})$

证明的话因为如果 $a_i>a_{i+1}$ ，那么说明这是一段递增的数列，那么不断的加上，最后可以得到一段中的 $a_{max}-a_{min}$ ，即就是我们刚刚得到的结论。

交换上只需把原本的交换位置上对答案的贡献减掉，再把交换后对答案的贡献加上即可。

### Code：

```cpp
#include<bits/stdc++.h>
#define N 300005
using namespace std;
long long tmp,l,r,taxi,n,a[N],ans,q;
int main(){
	scanf("%lld",&taxi);
	for(register int ttt=1;ttt<=taxi;ttt++)
	{
		scanf("%lld%lld",&n,&q);
		a[n+1]=0,a[0]=0,ans=0;
		for(register int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(register int i=0;i<=n;i++)
		{
			if(a[i]>=a[i+1])ans+=(a[i]-a[i+1]);
		}
		printf("%lld\n",ans);
		for(register int i=1;i<=q;i++)
		{
			scanf("%lld%lld",&l,&r);
			if(a[l-1]>=a[l])ans-=(a[l-1]-a[l]);
			if(a[l]>=a[l+1])ans-=(a[l]-a[l+1]);
			if(a[r-1]>=a[r]&&r-1!=l)ans-=(a[r-1]-a[r]);
			if(a[r]>=a[r+1])ans-=(a[r]-a[r+1]);
			//cout<<i<<" "<<ans<<endl;
			swap(a[l],a[r]);//swap(l,r); 
			if(a[l-1]>=a[l])ans+=(a[l-1]-a[l]);
			if(a[l]>=a[l+1])ans+=(a[l]-a[l+1]);
			if(a[r-1]>=a[r]&&r-1!=l)ans+=(a[r-1]-a[r]);
			if(a[r]>=a[r+1])ans+=(a[r]-a[r+1]);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```








---

## 作者：Karry5307 (赞：4)

### 题意

给定一个长度为 $n$ 的序列 $a$，有 $q$ 次操作，每次操作交换 $a_l$ 和 $a_r$，在操作前和每次操作后求出 $a$ 中所有子序列的交替和的最大值

$\texttt{Data Range:}1\leq n,q\leq 3\times 10^5$

### 题解

考虑先将数组差分一下，所以这个时候选一个系数为 $-1$ 一个系数为 $1$ 的位置出来相当于在差分数组上选一段区间。

所以问题变成在差分数组上选若干不相交区间使得和最大，只需要把那些大于 $0$ 的选出来即可。

对于交换操作的话可以把原来这两个位置的贡献减掉然后把新的贡献加回来，可能需要一些分类讨论。

具体实现可以看代码。

### 代码

```cpp
// This code is written by Karry5307
#include<bits/stdc++.h>
// Definition
#define For(i,x,y) for(register int i=(x);i<(y);i++)
#define Forr(i,x,y) for(register int i=(x);i<=(y);i++)
#define Rep(i,x,y) for(register int i=(x);i>(y);i--)
#define Repp(i,x,y) for(register int i=(x);i>=(y);i--)
#define ve vector
#define iter iterator
#define pb emplace_back
#define popb pop_back
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
#define F first
#define S second
#define PY return (void)puts("Yes")
#define PN return (void)puts("Yes")
#define P0 return (void)puts("0")
#define P1 return (void)puts("-1")
using namespace std;
// Typedefs
typedef int ll;
#define ll long long
typedef long long int li;
typedef unsigned int ul;
typedef unsigned long long int ull;
typedef double db;
typedef long double ldb;
typedef pair<ll,ll> pii;
typedef pair<li,li> pll;
const ll MAXN=6e5+51,MOD=998244353,inf=0x3f3f3f3f;
// Structures and variables
ll test,n,qcnt,l,r,res;
ll x[MAXN],f[MAXN],g[MAXN];
// Fast IO
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-') ch=getchar();
    if(ch=='-') neg=-1,ch=getchar();
    while(isdigit(ch)) num=(num<<3)+(num<<1)+(ch-'0'),ch=getchar();
    return neg==1?num:-num;
} 
inline li readu()
{
    register li num=0;
    register char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) num=(num<<3)+(num<<1)+(ch-'0'),ch=getchar();
    return num;
} 
template<class T>
inline void writep(T x)
{
	if(x<0){return (void)putchar('-'),writep(-x);}
	if(x<10){return (void)putchar(x|48);}
	writep(x/10),putchar((x%10)|48);
}
template<class T>
inline void write(T x,char ch=' '){writep(x),putchar(ch);}
template<class T>
inline void writeln(T x){writep(x),putchar('\n');}
// chkmin and chkmax
template<class T>
inline void chkmax(T &x,const T &y){x=x>y?x:y;}
template<class T>
inline void chkmin(T &x,const T &y){x=x<y?x:y;}
// Functions
template<class T,class Compare>
inline void sort(ve<T>&v,Compare cmp=less<T>()){sort(all(v),cmp);}
template<class T>
inline void reverse(ve<T>&v){reverse(all(v));}
template<class T>
inline void clear(T *arr){memset(arr,0,sizeof(arr));}
template<class T>
inline void setInf(T *arr){memset(arr,0x3f,sizeof(arr));}
// Math funcs
inline ll qpow(ll base,ll exponent)
{
	li res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%MOD;
		}
		base=(li)base*base%MOD,exponent>>=1;
	}
	return res;
}
inline ll gcd(ll x,ll y)
{
	return !y?x:gcd(y,x%y);
}
inline li lcm(ll x,ll y)
{
	return x/gcd(x,y)*y;
}
// Functions
inline void solve()
{
	n=read(),qcnt=read(),res=0;
	for(register int i=1;i<=n;i++)
	{
		x[i]=read(),res+=max(0ll,x[i]-x[i-1]);
	}
	printf("%lld\n",res);
	for(register int i=0;i<qcnt;i++)
	{
		l=read(),r=read(),res-=max(0ll,x[l]-x[l-1])+max(0ll,x[r]-x[r-1]);
		l!=n?res-=max(0ll,x[l+1]-x[l]):1,r!=n?res-=max(0ll,x[r+1]-x[r]):1;
		l+1==r?res+=max(0ll,x[r]-x[l]):1,swap(x[l],x[r]);
		res+=max(0ll,x[l]-x[l-1])+max(0ll,x[r]-x[r-1]);
		l!=n?res+=max(0ll,x[l+1]-x[l]):1,r!=n?res+=max(0ll,x[r+1]-x[r]):1;
		l+1==r?res-=max(0ll,x[r]-x[l]):1,printf("%lld\n",res);
	}
}
int main()
{
	test=read();
	for(register int i=0;i<test;i++)
	{
		solve();
	}
}
```

---

## 作者：STDquantum (赞：3)

先看一下如果没有 $q$，也就是 C1 如何做。

两种方法：

### 第一种

设 $f_{i,0/1}$ 为 $i$ 可选可不选，前 $i$ 个能达到的最大值。

其中 $i$ 若选，则 $0$ 代表答案中 $a_i$ 系数为负，$1$ 代表答案中 $a_i$ 系数为正。

若 $i$ 不选，则 $0$ 代表距离 $i$ 最近的一个已选的元素 $a_j$ 在答案中系数为负，$1$ 代表距离 $i$ 最近的一个已选的元素 $a_j$ 在答案中系数为正。

那么就有转移 $f_{i,0}=\max\{f_{i-1,1}-a_i,f_{i-1,0}\}$ 和 $f_{i,1}=\max\{f_{i-1,0}+a_i,f_{i-1,1}\}$。

由于 $a_i$ 一定为正，所以系数为正的数字个数一定比系数为负的数字个数多 $1$，那么答案就是 $f_{n,1}$。

转移只用到了 $i-1$ 的状态，所以可以把第一维去掉。

记得开`long long`。

### 第二种

先给结论：定义 $a_0=a_{n+1}=0$，对于波峰 $i$ 有 $a_i\gt a_{i-1}$ 且 $a_i\gt a_{i+1}$，对于波谷 $i$ 有 $a_i\lt a_{i-1}$ 且 $a_i\gt a_{i+1}$。所有波峰、波谷都要选，波峰系数为正，波谷系数为负。

感性证明：可以考虑一加一减的一个二元组 $(a_i,a_j)$，其中 $i\lt j$。若是选一个波峰和一个波谷一定是局部最优的。若 $a_i$ 不是波峰，对答案贡献会减小，若 $a_j$ 不是波谷，对答案贡献也会减小。所以把所有二元组都统计上一定是最优的。

所以沿途判断是波峰就加、是波谷就减就好。

---

第一种没法继承了，时间复杂度会变成 $\mathcal{O}(n^2)$。

所以考虑怎么把第二种加上修改操作。

每一个 $a_i$ 是否被计入答案、系数是否为正只和 $a_{i-1}$ 与 $a_{i+1}$ 有关，所以修改 $x$ 这个位置所影响的只有 $[x-1,x+1]$ 这个区间的每一个 $a$。所以去掉这些地方的贡献，然后交换一下，再把这些地方贡献统计上就行。

最好用函数封装一下加上贡献和去掉贡献的过程，不然那个代码长的要死。

时间复杂度 $\mathcal{O}(t\cdot(n+q))$，常数巨大（把里面的最长为 $12$ 的循环当做常数），但完全能跑过。

```cpp
typedef long long ll;
const int N = 3e5 + 10;

int n, q, t, a[N];
ll ans;
inline void del(int x) { // 去掉贡献
  if (a[x] > a[x - 1] && a[x] > a[x + 1]) {
    ans -= a[x];
  } else if (a[x] < a[x - 1] && a[x] < a[x + 1]) {
    ans += a[x];
  }
}
inline void add(int x) { // 加上贡献
  if (a[x] > a[x - 1] && a[x] > a[x + 1]) {
    ans += a[x];
  } else if (a[x] < a[x - 1] && a[x] < a[x + 1]) {
    ans -= a[x];
  }
}
inline void main() {
  for (read(t); t--;) {
    read(n), read(q);
    for (int i = 1; i <= n; ++i) { read(a[i]); }
    a[n + 1] = ans = 0; // 多组数据，所以a[n+1]一定要设为0！
    for (int i = 1; i <= n; ++i) { add(i); }
    write(ans), putchar('\n');
    for (int i = 1, l, r; i <= q; ++i) {
      read(l), read(r);
      /* 边界的设定：首先不能超过[1,n]，其次两个循环修改区间不能重合 */
      for (int j = max(1, l - 1); j <= l + 1; ++j) del(j);
      for (int j = max(l + 2, r - 1); j <= min(n, r + 1); ++j) del(j);
      swap(a[l], a[r]);
      for (int j = max(1, l - 1); j <= l + 1; ++j) add(j);
      for (int j = max(l + 2, r - 1); j <= min(n, r + 1); ++j) add(j);
      write(ans), putchar('\n');
    }
  }
}
```


---

## 作者：Graphcity (赞：2)

动态 DP，哈哈。

考虑将序列翻转，变成最后一个数为正贡献，倒数第二个数为负贡献，倒数第三个数为正贡献，$\cdots\cdots$，依此类推。

维护一个二元组 $(mn,mx)$ 表示到现在为止这个序列的最小值和最大值。加入一个数 $k$ 时，有转移：$mn'=\min(mn,k-mx),mx'=\max(mx,k-mn)$。

考虑利用矩阵乘法刻画转移：

$$
[-mn,mx]\times \begin{bmatrix}0 & k\\ -k & 0\end{bmatrix}=[-mn',mx']
$$

这里存的是 $-mn$ 是为了把形式修改成能够变成 $(\max,+)$ 卷积的样子。

然后上线段树动态 DP 就好了。总时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=3e5;
const ll inf=1e18;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,a[Maxn+5];

struct Matrix
{
    ll f[2][2];
    inline ll&operator()(int a,int b) {return f[a][b];}
} t[Maxn*4+5];
inline Matrix operator*(Matrix a,Matrix b)
{
    Matrix c; c(0,0)=c(0,1)=c(1,0)=c(1,1)=-inf;
    For(i,0,1) For(j,0,1) For(k,0,1)
        c(i,k)=max(c(i,k),a(i,j)+b(j,k)); return c;
}
inline Matrix Get(int x)
{Matrix k; k(0,0)=k(1,1)=0,k(0,1)=x,k(1,0)=-x; return k;}
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline void push_up(int p) {t[p]=t[ls(p)]*t[rs(p)];}
inline void Modify(int l,int r,int p,int k)
{
    if(l==r) {t[p]=Get(a[k]); return;}
    int mid=(l+r)>>1;
    if(k<=mid) Modify(l,mid,ls(p),k);
    else Modify(mid+1,r,rs(p),k);
    push_up(p);
}
inline void Solve()
{
    n=read(),m=read();
    For(i,1,n) a[i]=read();
    reverse(a+1,a+n+1);
    For(i,1,n) Modify(1,n,1,i);
    printf("%lld\n",max(t[1](0,1),t[1](1,1)));
    while(m--)
    {
        int x=read(),y=read();
        x=n-x+1,y=n-y+1;
        swap(a[x],a[y]),Modify(1,n,1,x),Modify(1,n,1,y);
        printf("%lld\n",max(t[1](0,1),t[1](1,1)));
    }
}

int main()
{
    int T=read();
    while(T--) Solve();
    return 0;
}
```

---

## 作者：Anita_Hailey (赞：1)

## [C. Pokémon Army](https://codeforces.com/contest/1420/problem/C2)

针对于两个问题，给出不同的解答。

**easy version:** 我们可以用 dp 来解决这个问题，考虑设计状态 $dp[i][0/1]$ 表示递推至 $i$ 位置为止，现在序列长度是偶数（奇数）的最大价值。这样子我们只要 $O(n)$ 可以解决这个问题。

**hard version:** 加入了 $\text{swap}$ 操作，这个题目维护的东西显然可以区间合并，那么，可以在线段树上每个区间维护四个值，分别是序列长度是偶数（奇数）的最大（小）值，满足合并律。只要写一个单点修改，全局查询的线段树即可。$n\le 300000$ 勉强跑过。听说正解是 $O(n+q)$ 差分的。（我要是 $\text{Modify}$ 操作呢 kk） 我这个复杂度是 $O(n+q\lg n)$

具体的实现就是大概写个线段树？然后正常维护一下dp值就好了

```c++
 const int N = 304001, mod = 1e9 + 7;
 int n, t, a[ N ], q;
 long long f[ N ][ 2 ];
 struct Node
 {
  int l, r;
  long long mx0, mx1, mn0, mn1;
 }elvahs[ N * 4 ];
 inline int ls( int k ) { return k << 1; }
 inline int rs( int k ) { return k << 1 | 1; }
#define l( i ) elvahs[ i ].l
#define r( i ) elvahs[ i ].r
#define mx0( i ) elvahs[ i ].mx0
#define mx1( i ) elvahs[ i ].mx1
#define mn0( i ) elvahs[ i ].mn0
#define mn1( i ) elvahs[ i ].mn1
 void Up( int k )
 {
  mx1( k ) = std::max( mx1( ls( k ) ) - mn0( rs( k ) ), mx0( ls( k ) ) + mx1( rs( k ) ) );
  mx0( k ) = std::max( mx1( ls( k ) ) - mn1( rs( k ) ), mx0( ls( k ) ) + mx0( rs( k ) ) );
  mn1( k ) = std::min( mn1( ls( k ) ) - mx0( rs( k ) ), mn0( ls( k ) ) + mn1( rs( k ) ) );
  mn0( k ) = std::min( mn1( ls( k ) ) - mx1( rs( k ) ), mn0( ls( k ) ) + mn0( rs( k ) ) );
  return;
 }
 void Build( int k, int l, int r )
 {
  l( k ) = l;
  r( k ) = r;
  if( l == r )
  {
   a[ l ] = mx1( k ) = mn1( k ) = rdi( );
   mx0( k ) = 0, mn0( k ) = 0;
   return;
  }
  int mid = l + r >> 1;
  Build( ls( k ), l, mid );
  Build( rs( k ), mid + 1, r );
  return Up( k );
 }
 void Modify( int k, int pos, int x )
 {
  if( l( k ) == r( k ) )
  {
   mx1( k ) = mn1( k ) = x;
   return;
  }
  int mid = l( k ) + r( k ) >> 1;
  pos <= mid ? Modify( ls( k ), pos, x ) : Modify( rs( k ), pos, x );
  return Up( k );
 }
 void Fakemain( )
 {
  t = rdi( );
  while( t-- )
  {
   n = rdi( );
   q = rdi( );
   Build( 1, 1, n );
   ptl( mx1( 1 ) );
   int L, R;
   while( q-- )
   {
    L = rdi( ), R = rdi( );
    Modify( 1, L, a[ R ] );
    Modify( 1, R, a[ L ] );
    std::swap( a[ L ], a[ R ] );
    ptl( mx1( 1 ) );
   }
  }
  return;
 }
```

---

## 作者：LJC00125 (赞：1)

## 题意

给出一个序列$a$，要求求出一个单调递增的下标序列$b$，使得:

$$ans=\sum\limits_{i=1}^{x}(-1)^{i-1}a_{b_i}$$

最大，输出这个最大值。

同时有$q$次修改，每次修改有两个参数$l,r$，交换$a_l$和$a_r$ 求每次操作后的答案。

## solution

我们先考虑C1的解法，即没有修改操作。我们很容易想到一个dp，dp[i][j]表示前i个数，这个数是加或是减所能取到的最大值。

这个转移很容易，就是:

$$dp[i][1]=max(dp[i-1][1],dp[i-1][0]+a[i])$$

$$dp[i][0]=max(dp[i-1][0],dp[i-1][1]-a[i])$$

最后的答案就是$max(dp[n][0],dp[n][1])$。

观察这个dp转移的式子，不难发现，当且仅当$a[i]\leq a[i+1]$的时候 这个dp的最大值才会发生变化。所以我们可以发现这个dp等价于:

$$ans=\sum\limits_{i=2}^nmax(0,a[i]-a[i-1])$$

所以我们对于每次的修改操作，维护一下这个差分数组的大于等于0的数的和

具体地，我们在修改前把两个位置的相邻的差分的贡献减去，然后加上改变之后两边的差分数组的贡献。

在cf上我竟然用了个Segment_Tree来完成这件事，太蠢了就不放代码了。

---

## 作者：liaiyang (赞：0)

我们贪心的考虑，会发现如果相邻两项递减，那么答案会加上两项之差。

每一次交换两项统计答案。

时间复杂度 $O(n+q)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define min(a,b) (a<b?a:b) 
#define P pair<int,int>
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-x))
mt19937 rnd(time(0));
inline int read(int u=0, char c=getchar(), bool f=false){
    for (;!isdigit(c);c=getchar()) f|=c=='-';
    for (;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+c-'0';
    return f?-u:u;
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar(x%10+48);
}
inline void wt(int x,char k){wt(x),putchar(k);}
const int inf=~0U>>1,linf=~0ULL>>1; 
const int mod=998244353;
const int N=3e5+10;
int T,n,q,ans,a[N];
main(){
    T=rd;
    while(T--){
        n=rd,q=rd,ans=0;
        a[n+1]=0;
        for(int i=1;i<=n;i++) a[i]=rd;
        for(int i=0;i<=n;i++) if(a[i]>a[i+1]) ans+=a[i]-a[i+1];
        wt(ans,'\n');
        for(int i=1;i<=q;i++){
            int l=rd,r=rd;
            if(a[l-1]>a[l]) ans-=a[l-1]-a[l];
            if(a[l]>a[l+1]) ans-=a[l]-a[l+1];
            if(a[r-1]>a[r]&&r-1!=l) ans-=a[r-1]-a[r];
            if(a[r]>a[r+1]) ans-=a[r]-a[r+1];
            swap(a[l],a[r]);
            if(a[l-1]>a[l]) ans+=a[l-1]-a[l];
            if(a[l]>a[l+1]) ans+=a[l]-a[l+1];
            if(a[r-1]>a[r]&&r-1!=l) ans+=a[r-1]-a[r];
            if(a[r]>a[r+1]) ans+=a[r]-a[r+1];
            wt(ans,'\n');
        }
    }
    return 0;
}//
```

---

## 作者：ql12345 (赞：0)

# 不一样的方法

~~用单调性做这题谁都会，也不难~~

我来说一个我没调出来的方法（我用单调性切了这道题，我下面说的方法过了C1和C2第二个点，第二个点T=1000，如果算法错误应该不会过吧）

## 算法：分块+dp

### Part 1（0.0版本，C1做法）：

~~笔者太菜，~~ 不看C2先看C1，显然可以想到用dp（最简单的方法，个人认为比单调性好写）

f[i][0/1]表示已经扫了i个数，最后一次运算是加（1）减（0）

初始化：f[2][0]=max(0,a[1]-a[2]), f[2][1]=max(0,max(a[1],a[2]))

转移方程：

f[i][0]=max(0,max(f[i-1][0],f[i-1][1]-a[i]));

f[i][1]=max(0,max(f[i-1][1],f[i-1][0]+a[i]));

说明：都对0取max是因为：~~笔者胆小，怕出事，~~ 这样如果没用也不会错

然后C1就秒了~

### Part 2（1.0.版本，正文）：

如果带修改呢？

~~笔者小气~~，舍不得C1浪费的那点时间和代码，想本着 **“保护大多数已有结果”** 的原则，只修改一部分

这么复杂的信息，显然是用分块比较好维护，一看范围——3e5——能过！

于是分块就出来了~

**详细做法：**

一个块有4种状态：块内第一个是+，最后一个是-......依次类推4种情况

每种情况统计出答案，对于修改，l和r所在的块暴力重新dp O(n^2)

修改完之后对整块进行dp，O(n^2)

### Part 3（笔者改上述算法的经历）：

~~CF提交了30遍~~

~~还没改出来~~

第三个点有一组数据在q=0的时候就错了，用C1朴素算法跑这组数据是对的

用C2代码（上述出错）交C1也是AC

所以就很玄学：

CF C1题数据太水？

C1都能过，说明这个代码在q=0时是对的呀，为什么会错？

因为无法下载数据，本地对拍 以及 手造类似过不了的那个点的数据 都是没问题的

# 所以，该题解，大家看个算法就过吧！

------------

以下是最接近正确的C2代码，希望有兴趣的大佬可以告诉我错哪里了：

### Code（如果笔者自相矛盾，以代码注释为准）：

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
template<typename T>void read(T &ff){
	T rr=1;ff=0;re char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')rr=-1;ch=getchar();}
	while(isdigit(ch)){ff=(ff<<1)+(ff<<3)+(ch^48);ch=getchar();}
	ff*=rr;
}
const int N=300010,T=1010,K=310;
int t,n,q,num,a[N],f[T+10][K+10][4],g[T+10][2];
#define bel(x) (x-1)/(K-1)+1//块的实际大小是K-1！
#define pos(i,j) (i-1)*(K-1)+j
void dp1(re int i){//块内dp
	//0:+ ~ -   1:+ ~ +   2:- ~ -   3:- ~ + 第一个是什么，最后一个是什么
	f[i][2][0]=max((int)0,a[pos(i,1)]-a[pos(i,2)]);
	f[i][2][1]=max(a[pos(i,1)],a[pos(i,2)]);
	f[i][2][2]=max(-a[pos(i,1)],-a[pos(i,2)]);
	f[i][2][3]=max((int)0,-a[pos(i,1)]+a[pos(i,2)]);
	for(re int j=3;j<K;++j){
		if(pos(i,j)>n){
			f[i][j][0]=f[i][j-1][0],f[i][j][1]=f[i][j-1][1],
			f[i][j][2]=f[i][j-1][2],f[i][j][3]=f[i][j-1][3];
			continue;
		}
		f[i][j][0]=max(f[i][j-1][0],f[i][j-1][1]-a[pos(i,j)]);
		f[i][j][1]=max(f[i][j-1][1],f[i][j-1][0]+a[pos(i,j)]);
		f[i][j][2]=max(f[i][j-1][2],f[i][j-1][3]-a[pos(i,j)]);
		f[i][j][3]=max(f[i][j-1][3],f[i][j-1][2]+a[pos(i,j)]);
	}
}
void dp2(){//整块dp
	g[1][0]=f[1][K-1][1],g[1][1]=max((int)0,f[1][K-1][0]);
	for(re int i=2;i<=num;++i){//0:+ 1:-
		g[i][0]=max(g[i-1][0]+f[i][K-1][3],g[i-1][1]+f[i][K-1][1]);
		g[i][1]=max(g[i-1][0]+f[i][K-1][2],g[i-1][1]+f[i][K-1][0]);
	}
	printf("%lld\n",max(g[num][1],g[num][0]));
	for(re int i=1;i<=num;++i)g[i][0]=g[i][1]=0;
}
signed main(){
	read(t);while(t--){
		read(n),read(q); for(re int i=1;i<=n;++i)read(a[i]);
		if(n==1){++q;while(q--)printf("%lld\n",a[1]);continue;}
		num=bel(n); for(re int i=1;i<=num;++i)dp1(i);//预处理
		dp2();
		int l,r;while(q--){
			read(l),read(r);
			swap(a[l],a[r]);dp1(bel(l)),dp1(bel(r));//暴力修改
			dp2();
		}
		for(re int i=1;i<=n;++i)a[i]=0;
		for(re int i=1;i<=num;++i)
			for(re int j=1;j<K;++j)
				for(re int l=0;l<4;++l)f[i][j][l]=0;
	}
	return 0;
}
```

---

