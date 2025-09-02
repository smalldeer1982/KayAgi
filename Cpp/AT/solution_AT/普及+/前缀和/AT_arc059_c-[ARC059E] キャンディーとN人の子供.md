# [ARC059E] キャンディーとN人の子供

## 题目描述

AtCoder 幼儿园里有 $N$ 个小朋友，编号 $1\sim N$，Evi 先生要把 $C$ 颗糖果分给他们。

小朋友可以得到任意多颗糖果。如果第 $i$ 个小朋友得到了 $a$ 颗糖，那么他会得到 $x_i^a$ 的愉悦度，其中 $x_i$ 是第 $i$ 个小朋友的兴奋度。幼儿园活跃指数定义为 $N$         个小朋友愉悦度的乘积。

令 $f(x_1,x_2,\cdots,x_N)$ 表示所有分糖果的方案对应的幼儿园活跃指数的和。

现在给出 $A_i,B_i(1\le i\le N)$，求 $\sum_{x_1=A_1}^{B_1} \sum_{x_2=A_2}^{B_2} \cdots \sum_{x_N=A_N}^{B_N} f(x_1,x_2,...,x_N)$，对 $10 ^ 9 + 7$ 取模。

## 样例 #1

### 输入

```
2 3
1 1
1 1```

### 输出

```
4```

## 样例 #2

### 输入

```
1 2
1
3```

### 输出

```
14```

## 样例 #3

### 输入

```
2 3
1 1
2 2```

### 输出

```
66```

## 样例 #4

### 输入

```
4 8
3 1 4 1
3 1 4 1```

### 输出

```
421749```

## 样例 #5

### 输入

```
3 100
7 6 5
9 9 9```

### 输出

```
139123417```

# 题解

## 作者：Sangber (赞：6)

### 前言
今天练习赛出了这道题，由于我太菜没有在考场上做出来。  
翻了题解后，感觉题解讲的并不是十分直观，所以自己写一篇。

----
### 题目大意
~~太长了，不讲了。~~  
数据范围：  
$1\leq N\leq 400$  
$1\leq C\leq 400$  
$1\leq A_i,B_i\leq 400$

----
### 解题思路
考虑 $\text{DP}$（至于为什么是 $\text{DP}$ 。。。靠经验吧）  
设 $f[i][j]$ 表示当前 $\text{DP}$ 到了第 $i$ 个人，已经发了 $j$ 个糖果的答案。  
那么转移方程为：  
$$f[i][j]=\sum_{k=0}^jf[i-1][j-k]\left( \sum_{x=A_i}^{B_i}x^k \right)$$
这样来理解：  
我们枚举一个 $k\ (0 \leq k \leq j)$，表示我们当前这个人也就是第 $i$ 个人分到了 $k$ 个糖果。  
我们需要在之前的 $i-1$ 个人的答案中都乘上当前这个人的贡献：$\sum\limits_{x=A_i}^{B_i}x^k$。  
这就是转移方程的意义。  
此外我们加一个前缀和优化就可以达到 $O(n^3)$ 的复杂度。

----
### 细节注意事项
+ 注意取模的问题，减法记得加一个模数再去模
+ 中间运算记得用 $\text{long long}$

----
### 参考代码
```cpp
/*--------------------------------
  Author: The Ace Bee
  Blog: www.cnblogs.com/zsbzsb
  This code is made by The Ace Bee
--------------------------------*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <ctime>
#define rg register
using namespace std;
template < typename T > inline void read(T& s) {
	s = 0; int f = 0; char c = getchar();
	while (!isdigit(c)) f |= (c == '-'), c = getchar();
	while (isdigit(c)) s = s * 10 + (c ^ 48), c = getchar();
	s = f ? -s : s;
}

typedef long long LL;
const int p = 1000000007;
const int _ = 410;

int n, c, a[_], b[_];
LL pw[_][_], f[_][_];

int main() {
	read(n), read(c);
	for (rg int i = 1; i <= n; ++i) read(a[i]);
	for (rg int i = 1; i <= n; ++i) read(b[i]);

	for (rg int i = 1; i < _; ++i) pw[i][0] = 1ll;
	for (rg int i = 1; i < _; ++i)
		for (rg int j = 1; j < _; ++j)
			pw[i][j] = 1ll * pw[i][j - 1] * i % p;
	
	for (rg int i = 1; i < _; ++i)
		for (rg int j = 0; j < _; ++j)
			pw[i][j] = (pw[i][j] + pw[i - 1][j]) % p;

	f[0][0] = 1;
	for (rg int i = 1; i <= n; ++i)
		for (rg int j = 0; j <= c; ++j)
			for (rg int k = 0; k <= j; ++k)
				f[i][j] = (f[i][j] + 1ll * f[i - 1][j - k] * (pw[b[i]][k] - pw[a[i] - 1][k] + p) % p) % p;

	printf("%lld\n", f[n][c]);
	
	return 0;
}
```
**完结撒花$qwq$**

---

## 作者：Caicz (赞：4)


### [在博客食用更佳](https://www.luogu.com.cn/blog/224229/solution-at2021)

------------
[题目链接](https://www.luogu.com.cn/problem/AT2021)
交不了的可以直接去[Atcoder](https://atcoder.jp/contests/arc059/tasks/arc059_c)

  当时上课看到这题时，就被这一堆$\sum$吓住了，然后甚至连题都没读懂，就开始讲正解了，但下来以后再看这道题，似乎也不是很难...
  
**首先这是一道动规题，那么我们直接设 $dp[i][j]$ 表示算到第$i$个小朋友，所有的方案数的答案**

我们先由部分点开始思考：

> 对于每一个 $a_i$ 满足 $a_i=b_i$ 那么我们的状态转移方程就可以写为
$$
dp[i][j]+=dp[i-1][j-k] * a_i^k,(0\le k \le j)
$$
边界条件为，$dp[i][0]=1,(i=0,1,2,3\cdots n)$ 这样的时间复杂度就为 $O(n^3)$可以通过

但是如果$a_i\ne b_i$呢？我们的状态转移方程就应该为
$$
dp[i][j]+=dp[i-1][j-k] * \sum_{x=a_i}^{b_i}x^k,(0\le k \le j)
$$
那么边界条件就应该为，$dp[i][0]=dp[i-1][0] * (b_i-a_i+1),(i=0,1,2,3\cdots n)$

等等，这样不就是$O(n^4)$了吗？但我们仔细观察后面式子 $\sum_{x=a_i}^{b_i}x^k$ 发现这是一个**定值**，且因为 $1\le a_i\le b_i\le 400$ ，同时这还是**一段连续的区间的k次方和**，所以我们可以预先预处理出来所有的k的次方和的前缀和即可

>> **_talk is cheap , show you the code_**

~~~cpp
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define ll long long
#define maxn 405
using namespace std;
const int mod=1e9+7;
ll dp[maxn][maxn];
int a[maxn],b[maxn],n,m;
ll sum[maxn][maxn];

inline int read()
{
	int num,sign=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')sign=-1;
	num=c-'0';
	while((c=getchar())>='0'&&c<='9')
		num=(num<<1)+(num<<3)+c-'0';
	return num*sign;
}

inline ll fast(ll a,ll b)
{
	ll ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return ans;
}

inline void pre()
{
	for(register int i=1;i<=n;++i)sum[i][0]=b[i]-a[i]+1;
	for(register int i=1;i<=n;++i)//懒得想前缀和怎么打的同学可以直接暴力求解k次方和(亲测可过)
		for(register int k=1;k<=m;++k)
			for(register int j=a[i];j<=b[i];++j)
				sum[i][k]=(sum[i][k]+fast(j,k))%mod;
}

signed main(void)
{
	n=read(),m=read();
	for(register int i=1;i<=n;++i)a[i]=read();
	for(register int i=1;i<=n;++i)b[i]=read();
	pre();
	dp[0][0]=1;
	for(register int i=1;i<=n;++i)dp[i][0]=(dp[i-1][0]*sum[i][0])%mod;
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=m;++j)
			for(register int k=0;k<=j;++k)
				dp[i][j]=(dp[i][j]+(dp[i-1][j-k]*sum[i][k])%mod)%mod;
	printf("%lld",dp[n][m]);
	return 0;
}

~~~


---

## 作者：henry_y (赞：4)

[可以选择在我的博客观看](https://www.cnblogs.com/henry-1202/p/atcoder_training.html)

## 总结：dp+前缀和优化

好像不是特别难的样子...不过一大堆sigma我一开始看着有点萌币

其实就是当你这个人拿了x个糖果之后呢，前面的方案也就要相应的乘上$\sum_{i=a[i]}^{b[i]} i^m$，所以这个转移是$O(n^4)$的

不过因为$ai,bi$都是固定的所以直接前缀和优化一下就行了

数据也就$400$，$O(n^3)$能过了

但是注意转移时的取模，我之前没搞好$wa$了好几个点...

```
#include <bits/stdc++.h>

using namespace std ; 

#define N 500
#define ll long long
const ll mod = 1e9+7 ; 

ll n , m ;
ll a[ N ] , b[ N ] ;
ll sum[ N ][ N ] , l[ N ][ N ] ;
ll f[ N ][ N ] ;
//f[ i ][ j ]前i个人一共分了j个糖果 
//l[ i ][ j ]储存i的j次方
//sum[ i ][ j ]对l维护前缀和 

int main() {
	scanf( "%lld%lld" , &n ,&m ) ;
	for( int i = 1 ; i <= n ; i ++ ) {
		scanf( "%lld" , &a[ i ] ) ;
	}
	for( int i = 1 ; i <= n ; i ++ ) {
		scanf( "%lld" , &b[ i ] ) ;
	}
	for( int i = 1 ; i < N ; i ++ ) {
		l[ i ][ 0 ] = 1 ;
		for( int j = 1 ; j < N ; j ++ ) {
			l[ i ][ j ] = l[ i ][ j - 1 ] * i  ;
			l[ i ][ j ] %= mod ;
		}
	}
	for( int i = 1 ; i < N ; i ++ ){
		for( int j = 0 ; j < N ; j ++ ) {
			sum[ i ][ j ] += sum[ i - 1 ][ j ] + l[ i ][ j ] ;
			sum[ i ][ j ] %= mod ;
		}
	} 
	f[ 0 ][ 0 ] = 1 ;
	for( int i = 1 ; i <= n ; i ++ ) {
		for( int j = 0 ; j <= m ; j ++ ) {
			for( int k = 0 ; k <= j ; k ++ ) {
				f[ i ][ j ] = ( f[ i ][ j ] % mod + ( 1ll * f[ i - 1 ][ j - k ] *( ( sum[ b[ i ] ][ k ] - sum[ a[ i ] - 1 ][ k ] ) % mod )  + mod ) % mod + mod ) % mod  ;
			}
		} 
	} 
	printf( "%lld\n" , f[ n ][ m ] ) ;
	return 0 ;
} 
```

---

## 作者：nxd_oxm (赞：2)

定义 $g(x_1,x_2,...,x_i,c)$ 为所有分 $c$ 颗糖果的方案对应的幼儿园活跃指数的和。答案即为
$$\sum_{x_1=A_1}^{B_1} \sum_{x_2=A_2}^{B_2} \cdots \sum_{x_N=A_N}^{B_N} g(x_1,x_2,...,x_N,C)$$

----

可以发现，我们能将
$$\sum_{x_1=A_1}^{B_1} \sum_{x_2=A_2}^{B_2} \cdots \sum_{x_i=A_i}^{B_i} g(x_1,x_2,...,x_i,c)$$
拆成
$$\bigg(\sum_{lst=0}^{c} \sum_{x_1=A_1}^{B_1} \sum_{x_2=A_2}^{B_2} \cdots \sum_{x_{i-1}=A_{i-1}}^{B_{i-1}} g(x_1,x_2,...,x_{i-1},lst) \bigg) \times \sum_{x_i=A_i}^{B_i} (x_i)^{c-lst}$$

于是，定义 $pr_{i,j,k}= \sum_{w=i}^{j} w^k$，$f_{i,j}$ 为前 $i$ 个小朋友分 $j$ 颗糖，转移同上，即：

$$\bigg(\sum_{lst=0}^{c}f_{i-1,lst} \bigg) \times pr_{A_i,B_i,lst-c}$$

$pr_{i,j,k}$ 预处理即可，复杂度 $\mathcal{O}(W^2N)$。[code](https://atcoder.jp/contests/arc059/submissions/58920101)。

---

## 作者：AsunderSquall (赞：2)

提供一个复杂度 $O(n^2 \log n)$ 但是并不会跑得更快（~~而且一定跑得更慢~~）的算法   
~~而且是嘴巴的没去写过~~  
~~其实只是来水题解的~~


首先我们来考虑 $O(n^3)$ 做法。  
假如 $\{x_i\}$ 已经确定了，怎么计算。  
设 $f_{i,j}$ 表示考虑前 $i$ 个 $a$，并且总和为 $j$ 的时候，前 $i$ 个的乘积。那么可以简单地列出转移方程。  
$$f_{i,j}=\sum_{k=0}^j f_{i-1,j-k}\cdot x_i^k$$  

然后我们把 $x_i^k$ 替换成 $\sum _{l=a_i}^{b_i} l^k$ 就是正确答案。  
因为考虑你每一位选的 $x$ 是互相独立的，然后每一位选的 $a$ 也是独立的，所以这样就是正确答案。  

代码：  
```cpp
int n,c;
int a[N],b[N];
int p[N][N],s[N][N],f[N][N],S[N][N];
signed main()
{
	rd(n);rd(c);
	for (int i=1;i<=n;i++) rd(a[i]);
	for (int i=1;i<=n;i++) rd(b[i]);
	for (int i=1;i<=400;i++) {int t=1;for (int j=0;j<=c;j++) {p[i][j]=t;t=t*i%mod;}}
	for (int k=0;k<=c;k++) for (int i=1;i<=400;i++) s[i][k]=(s[i-1][k]+p[i][k])%mod;
	for (int k=0;k<=c;k++) for (int i=1;i<=n;i++) S[i][k]=s[b[i]][k]-s[a[i]-1][k];
	f[0][0]=1;
	for (int i=1;i<=n;i++) for (int j=0;j<=c;j++) for (int k=0;k<=j;k++) f[i][j]=(f[i][j]+f[i-1][j-k]*S[i][k])%mod;
	cout<<(f[n][c]+mod)%mod<<endl;
}
```

我们发现 `for (int i=1;i<=n;i++) for (int j=0;j<=c;j++) for (int k=0;k<=j;k++) f[i][j]=(f[i][j]+f[i-1][j-k]*S[i][k])%mod;`  
这个是复杂度瓶颈，然后发现这是个卷积形式。  
那么我们用 MTT 或者三模 NTT 之类的就能降低复杂度。  
~~但是显然会跑得更慢~~

---

## 作者：harmis_yz (赞：1)

题解摘自 [CSP2024 前做题情况](https://www.luogu.com.cn/article/3yyu431w)。

## 分析

考虑 DP。

发现数据范围不大，定义状态函数 $f_{i,j}$ 表示前 $i$ 个小朋友，一共得到 $j$ 颗糖的愉悦度。那么有：$f_{i,j}=\sum\limits_{k=0}^{j}(f_{i-1,j-k}\times \sum\limits_{w=a_i}^{b_i}w^k)$。

观察式子，发现 $\sum\limits_{w=a_i}^{b_i}w^k$ 可以通过前缀和预处理出来。令 $s_{i,j}=\sum\limits_{k=0}^{i}k^j$。那么转移方程可以写成：$f_{i,j}=\sum\limits_{k=0}^{j}(f_{i-1,j-k}\times (s_{b_i,k}-s_{a_i-1,k}))$。时间复杂度 $O(n^3)$。

## 代码

```cpp
  	for(re int j=0;j<N;++j)
  	for(re int i=1;i<N;++i) s[i][j]=(s[i-1][j]+qmi(i,j,p))%p;
  	f[0][0]=1;
  	for(re int i=1;i<=n;++i)
  	for(re int j=0;j<=m;++j)
  	for(re int k=0;k<=j;++k) f[i][j]=(f[i][j]+f[i-1][j-k]*((s[b[i]][k]-s[a[i]-1][k])%p+p)%p)%p;
  	printf("%lld\n",f[n][m]);
```

---

## 作者：Leaper_lyc (赞：0)

### 解题思路
关注到题目数据范围仅有 $400$，推测复杂度大概 $O(n^3)$，考虑 dp。

设 $f_{i,j}$ 表示前 $i$ 个人一共分到 $j$ 颗糖的答案。

枚举第 $i$ 个人有 $k$ 颗，则前 $i-1$ 人一共有 $j-k$ 颗。也就是说 $f_{i,j}$ 是由 $f_{i-1,j-k}$ 转移到的。 

得出状态转移方程：

$$
f_{i,j}=\sum\limits_{k=0}^j f_{i-1,j-k}(\sum\limits_{x={A_i}}^{B_i}x^k)
$$

两个 $\sum$ 均可以用前缀和优化掉。

时间复杂度：$O(n^3)$。

代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define int long long
const int _ = 405;
const int mod = 1e9 + 7;
int n, c;
int a[_], b[_];
int f[_][_];
int p[_][_];
signed main() {
    cin >> n >> c;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i < _; i++) {
        p[i][0] = 1;
        for (int j = 1; j < _; j++)
            p[i][j] = p[i][j - 1] * i % mod;
    }
    for (int i = 1; i < _; i++)
        for (int j = 0; j < _; j++)
            p[i][j] = (p[i][j] + p[i - 1][j]) % mod;
    f[0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= c; j++)
			for (int k = 0; k <= j; k++)
				f[i][j] = (f[i][j] + 1ll * f[i - 1][j - k] * (p[b[i]][k] - p[a[i] - 1][k] + mod) % mod) % mod;
    cout << f[n][c];
}
```

---

## 作者：Ancers (赞：0)

### 题目
[传送门](https://www.luogu.org/problem/AT2021)
### 题解
机房大佬好像有非常简单易懂的题解但是我不懂（雾  
然后乱想了一下有了一点思路
是个DP  
用f[k][n]表示把n个糖果分给k个孩子所得到的x[i]^a[i]的乘积的和（显然就是答案），  
f[k-1][n-m]表示把n-m个糖果分给k-1个孩子得到的结果，也就是说给了第k个孩子m个糖果。  
考虑转移，情况有两种：  
1.a[i]==b[i]的情况，f[k][n] += f[k-1][n-m] * (a[i]^m)。  
2.a[i]!=b[i]的情况，f[k][n] += f[k-1][n-m] * (a[i]^m + (a[i]+1)^m + ... + b[i]^m);  
关键点是在如何处理这一部分：(a[i]^m + (a[i]+1)^m + ... + b[i]^m);  
这里提供一种可行的 效率可观的 求法  
sum[i]表示a^i+(a+1)^i+(a+2)^i+……+b^i;
```cpp
void calc(int a,int b){
	memset(sum,0,sizeof(sum));
	for (int i(a);i<=b;++i){
		ll t=1;
		for (int j(0);j<=c;++j){
			sum[j]=sum[j]+t,sum[j]%=mod;//如果只是看看不懂的话建议手动模拟
			t=t*i%mod;//每一次操作t的幂数都+1
		}
	}
}
```
### 代码
```cpp
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
const int mod(1e9+7),maxn(405);
int n,c;
ll sum[maxn],f[maxn][maxn];
int a[maxn],b[maxn];
void init(){
	n=read(),c=read();
	for (int i(1);i<=n;++i) a[i]=read();
	for (int i(1);i<=n;++i) b[i]=read();
	f[0][0]=1;
}

void calc(int a,int b){
	memset(sum,0,sizeof(sum));
	for (int i(a);i<=b;++i){
		ll t=1;
		for (int j(0);j<=c;++j){
			sum[j]=sum[j]+t,sum[j]%=mod;
			t=t*i%mod;
		}
	}
}

signed main(){
	init();
	for (int i(1);i<=n;++i){
		calc(a[i],b[i]);
		for (int j(0);j<=c;++j)
			for (int k(0);k<=j;++k)
				f[i][j]=(f[i][j]+f[i-1][j-k]*sum[k])%mod;
	}
	printf("%d\n",f[n][c]);					 
	return 0; 
}

```

---

