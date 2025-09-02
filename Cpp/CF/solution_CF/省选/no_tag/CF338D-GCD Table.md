# GCD Table

## 题目描述

Consider a table $ G $ of size $ n×m $ such that $ G(i,j)=GCD(i,j) $ for all $ 1<=i<=n,1<=j<=m $ . $ GCD(a,b) $ is the greatest common divisor of numbers $ a $ and $ b $ .

You have a sequence of positive integer numbers $ a_{1},a_{2},...,a_{k} $ . We say that this sequence occurs in table $ G $ if it coincides with consecutive elements in some row, starting from some position. More formally, such numbers $ 1<=i<=n $ and $ 1<=j<=m-k+1 $ should exist that $ G(i,j+l-1)=a_{l} $ for all $ 1<=l<=k $ .

Determine if the sequence $ a $ occurs in table $ G $ .

## 说明/提示

Sample 1. The tenth row of table $ G $ starts from sequence {1, 2, 1, 2, 5, 2, 1, 2, 1, 10}. As you can see, elements from fifth to ninth coincide with sequence $ a $ .

Sample 2. This time the width of table $ G $ equals 8. Sequence $ a $ doesn't occur there.

## 样例 #1

### 输入

```
100 100 5
5 2 1 2 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
100 8 5
5 2 1 2 1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
100 100 7
1 2 3 4 5 6 7
```

### 输出

```
NO
```

# 题解

## 作者：Siyuan (赞：20)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-Codeforces-338D-GCD-Table/)

---

## Description

> 题目链接：[Codeforces 338D](https://codeforces.com/contest/338/problem/D)

有一张 $n\times m$ 的表格，第 $i$ 行第 $j$ 列的元素是 $\gcd(i,j)$。给定一个长度为 $k$ 的序列 $a_i$，询问是否存在 $x,y$，满足 $\forall i,1\le i\le k,\gcd(x,y+i-1)=a_i$（即这个序列在表格的某一行出现过）。

数据范围：$1\le n,m\le 10^{12}$，$1\le k\le 10^4$，$1\le a_i\le 10^{12}$

------

## Solution

由于我们要保证 $\gcd(x,y)=a_i$，显然 $\operatorname{lcm}(a_1,a_2,\dots,a_k)\mid x$。

我们尝试证明：如果有解，那么 $x$ 的值可以为 $\operatorname{lcm}(a_1,a_2,\dots,a_k)$。

如果有解，且 $x=K\cdot\operatorname{lcm}(a_1,a_2,\dots,a_k)$，那么意味着 $\gcd(K,y)=0$，这样一来我们给 $y$ 平白无故地增加了限制。因此如果 $x=K\cdot\operatorname{lcm}(a_1,a_2,\dots,a_k)$ 时有解，那么在 $x=\operatorname{lcm}(a_1,a_2,\dots,a_k)$ 时一定也有解。

在确定了 $x$ 的值之后，还需要满足 $a_i\mid y+i-1$，即满足下列同余方程：
$$\begin{cases}y=0\pmod{a_1} \\y=-1\pmod{a_2} \\\vdots \\y=-k+1\pmod{a_k}\end{cases}$$
这个方程显然可以通过**扩展中国剩余定理**来求解 $y$ 即可。

但是我们发现，求出 $y$ 之后的解 $(x,y)$ 不一定就是合法的，这是为什么呢？

其实我们通过这样的思路，推导出解**只满足必要性**，而**不满足充分性**。因此我们还需要将 $(x,y)$ 代入 $\gcd(x,y+i-1)=a_i(1\le i\le k)$ 验证。

**时间复杂度**：$O(k\log a_i)$

------

## Code

```cpp
#include <cstdio>
typedef long long LL;

const int N=1e4+5;
int k;
LL x,y,m[N],r[N];

LL mul(LL x,LL p,LL mod) {
	if(p<0) x=-x,p=-p;
	LL ret=0;
	for(;p;p>>=1,x=(x+x)%mod) if(p&1) ret=(ret+x)%mod;
	return ret;
}
LL exgcd(LL a,LL b,LL &x,LL &y) {
	if(!b) {x=1,y=0;return a;}
	LL d=exgcd(b,a%b,y,x);
	y-=a/b*x; return d;
}
LL gcd(LL x,LL y) {
	return y?gcd(y,x%y):x;
}
LL lcm(LL x,LL y) {
	return x/gcd(x,y)*y;
}
LL China(int n) {
	LL M=m[1],R=r[1];
	for(int i=2;i<=n;++i) {
		LL a=M,b=m[i],c=r[i]-R,x,y,d=exgcd(a,b,x,y);
		if(c%d) return -1;
		a/=d,b/=d,c/=d,x=(mul(x,c,b)+b)%b;
		R+=x*M,M*=m[i]/d,R=(R+M)%M;
	}
	R=(R+M-1)%M+1;
	if(R<1||R+k-1>y) return -1;
	return R;
}
int main() {
	scanf("%lld%lld%d",&x,&y,&k);
	LL xx=1;
	for(int i=1;i<=k;++i) {
		scanf("%lld",&m[i]);
		if((xx=lcm(xx,m[i]))>x) return puts("NO"),0;
		r[i]=((m[i]-i+1)%m[i]+m[i])%m[i];
	}
	LL yy=China(k);
	if(yy==-1) return puts("NO"),0;
	for(int i=1;i<=k;++i) {
		if(gcd(xx,yy+i-1)!=m[i]) return puts("NO"),0;
	}
	return puts("YES"),0;
}
```



---

## 作者：fanfansann (赞：3)

 
**Problem**

有一张 $n\times m$ 的表格 $G$，第 $i$ 行第 $j$ 列的元素是 $G(i,j)=\gcd(i,j)$ 。给定一个长度为 $k$ 的序列 $a_i$ ，询问是否存在 $x,y$，满足 $\forall i,1\le i\le k,G(x,y+i-1)=\gcd(x,y+i-1)=a_i$ （即问是否有在表格范围内的解 $(x,y)$  ）。

数据范围：$1\le n,m\le 10^{12},1\le k\le 10^4,1\le a_i\le 10^{12}$

**Solution**

根据题意显然可以列出：

$$ 
\left\{
\begin{aligned}
\gcd(x,y+1-1) & = & a_1 \\
\gcd(x,y+2-1) & = & a_2 \\ \cdots\\
\gcd(x,y+k-1)& = & a_k
\end{aligned}
\right.
$$

我们知道 $\gcd(a,b) =c$，经典套路，显然有：$a=k_1c,b=k_2c,k_1\nmid k_2$

即：
$$
a\mid c,b\mid c\Rightarrow x\mid a_i,y+i-1\mid a_i
$$

即：

$$
\begin{aligned}&x\equiv0 \bmod a_i&\\&y\equiv(1-i)\bmod a_i\end{aligned}
$$

所以我们可以列出一个同余方程组：

$$
\left\{
\begin{aligned}&y\equiv(1-1)\bmod a_1&\\&y\equiv(1-2)\bmod a_2\\&\ \ \ \ \ \ \ \ \ \ \ \ \ \ \cdots&\\&y\equiv(1-k)\bmod a_k\end{aligned}
\right.
$$

显然 $a_i$ 不一定是质数，所以我们直接使用拓展中国剩余定理求解即可，这样我们就可以求出一个合法的 $y$。

那么如何求出最小的（不容易越界）且合法的 $x$ 呢，显然 $x$ 可以整除所有的 $a_i$，那么满足条件的最小的 $x$ 显然是 $\text{lcm}\{ a_{i} \}$。

求出 $x,y$ 以后验证一下开头列出来的 $\gcd$ 是否完全相同，以及 $G(x,y+i-1)$ 中的 $(x,y+i-1)$ 是否在 $G$ 函数的定义域内即可。（我们只需要判断 $x,y+i-1,y+k-1$ 是否越界即可）

**Hint**

- 这里如果给定的模数均为 $1$ 的话，直接用 excrt 板子求出来的是 $0$ ，此时应该是答案取任意值均可，但是这里如果答案取 $0$ 的话 $y<1$ 会判负，实际上是有解的，所以这里要特判一下。 

- 龟速乘的时候，如果乘的是负数的话需要 $a,b$ 同时取反，否则会死循环hhh

**Code**

```cpp
// Problem: D. GCD Table
// Contest: Codeforces - Codeforces Round #196 (Div. 1)
// URL: https://codeforces.com/problemset/problem/338/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
using namespace std;
using ll = long long;
const int N = 1e4 + 7;

int n, m, k, t;
int a[N], LCM;
int ai[N], bi[N];

template <typename T> inline void read(T& t) {
    int f = 0, c = getchar(); t = 0; 
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
    if (f) t = -t;
}

template <typename T> void print(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) print(x / 10);
    putchar(x % 10 + 48);
} 

int gcd(int a, int b)
{
	if(b == 0) return a;
	return gcd(b, a % b);
}

int lcm(int a, int b)
{
	return a / gcd(a, b) * b;
}

int exgcd(int a, int b, int &x, int &y)
{
	if(b == 0) {
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a % b, x, y);
	int z = x;
	x = y, y = z - a / b * y; 
	return d;
}

int mul(int a, int b, int c)
{
	if(b < 0) a = - a, b = - b;
	int res = 0;
	while(b) {
		if(b & 1) res = (res + a) % c;
		a = (a + a) % c;
		b >>= 1;
	}
	return res;
}

ll excrt(int n)
{
	ll x, y, k;
	ll M = bi[1], ans = ai[1];
	for(int i = 2; i <= n; ++ i) {
		ll a = M, b = bi[i], c = (ai[i] - ans % b + b) % b;
		ll d = exgcd(a, b, x, y);
		ll bg = b / d;
		if(c % d != 0) return -1;
		x = mul(x, c / d, bg);
		ans += x * M;
		M *= bg;
		ans = (ans % M + M) % M;
	} 
	ans = (ans % M + M) % M;
	if(ans == 0) ans = M;//ans = 1;
	return ans;
}

signed main()
{
	LCM = 1;
	read(n), read(m), read(k);
	for(int i = 1; i <= k; ++ i) {
		read(a[i]);
		LCM = lcm(LCM, a[i]);
	}
	if(k > m) return puts("NO"), 0;
	for(int i = 1; i <= k; ++ i) {
		bi[i] = a[i];
		ai[i] = (1 - i + a[i]) % a[i];
	}

	int x = LCM, y = excrt(k); 
	if(y == -1) return puts("NO"), 0;
	for(int i = 1; i <= k; ++ i) {
		if(gcd(x, y + i - 1) != a[i]) 
			return puts("NO"), 0;
	}     

	if(y < 1 || x < 1 || y + k - 1 > m || x > n) 
		return puts("NO"), 0;
	return puts("YES"), 0;
}
```

---

## 作者：dsjkafdsaf (赞：3)

# [My blog](https://www.cnblogs.com/dsjkafdsaf/)
## 题目描述

一张$n\times m$ 的表，第$i $行第$j 列$是。

$GCD(i,j)$你有一个长度为$k$ 的数列$A$，询问是否存在$i,j$。

满足对任意的$l$，均有$GCD(i,j+l-1)=a_l(1\leq l\leq k)$。

## Input

第一行有$3$个整数$n,m,k$。

第二行有$k$个整数表示数组$A$。

$ 1<=n,m<=10^{12}1<=k<=10000 $

$ 1<=a_{i}<=10^{12}$

## Output

若存在输出$YES$，否则输出$NO$。

## Sample Input

```
100 100 5
5 2 1 2 1

100 8 5
5 2 1 2 1

100 100 7
1 2 3 4 5 6 7
```
## Sample Output
```
YES

NO

NO
```
更好的阅读体验：[my blog](https://www.cnblogs.com/dsjkafdsaf/p/11577373.html)

题目中要求我们在表中找到数列$A$。

即：
$$
\begin{cases}
GCD(i,j)=A_1 \\
GCD(i,j+1)=A_2 \\
...... \\
GCD(i,j+k-1)=A_k\\
\end{cases}
$$

由于$GCD$内外可以同时除掉一个数，所以我们同时除掉$A_i$。

有：
$$
\begin{cases}
GCD(i/A_1,j/A_1)=1 \\
GCD(i/A_2,(j+1)/A_2)=1 \\
...... \\
GCD(i/A_k,(j+k-1)/A_k)=1\\
\end{cases}
$$

题目开始变得明朗了起来。

首先，我们发现$i$必定能整除所有的$A_i$，即$i$一定是$LCM(A)$的倍数。

同时，我们又发现$j/A_1$为整数，$(j+1)/A_2$为整数，即：
$$
\begin{cases}
j=0\%A_1 \\
j+1=0\%A_2 \\
...... \\
j+k-1=0\%A_k\\
\end{cases}
$$

我们可以利用中国剩余定理解出$j$的解集。

我们发现$j$的解集一定是$Ans+k*LCM(A)$。

让我们再回到之前的解题中去。

$i=t*LCM(A),j=Ans+k*LCM(A)$。

让我们证明$i$取$LCM(A)$时最优：

***

$j$的解集和$i$并没有关系.

在上面的条件中，我们要求$GCD(t*(LCM(A)/A_i),(j+i-1)/A_i)=1$.

我们发现若$t$不等于$1$时，在$GCD$中必定会多带入一个因子，这样的话会使$GCD$为$1$变的比较麻烦。

所以，我们取$i=LCM(A)$一定是最优的。

***

即然$i$已经取了$LCM(A)$,那$j$自然是取$Ans$了，否则的话由会多了$LCM(A)$的项。

最后带入检验即可。

### 一个坑点：两个数相乘会炸long long，要用快速乘。

```cpp

#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
#define reg register
#define clr(a,b) memset(a,b,sizeof a)
#define Mod(x) (x>=mod)&&(x-=mod)
#define abs(a) ((a)<0?-(a):(a))
#define debug(x) cerr<<#x<<"="<<x<<endl;
#define debug2(x,y) cerr<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl;
#define debug3(x,y,z) cerr<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl;
#define rep(a,b,c) for(reg int a=(b),a##_end_=(c); a<=a##_end_; ++a)
#define ret(a,b,c) for(reg int a=(b),a##_end_=(c); a<a##_end_; ++a)
#define drep(a,b,c) for(reg int a=(b),a##_end_=(c); a>=a##_end_; --a)
#define erep(i,G,x) for(int i=(G).Head[x]; i; i=(G).Nxt[i])
#pragma GCC optimize(2)
 
inline int Read(void) {
	int res=0,f=1;
	char c;
	while(c=getchar(),c<48||c>57)if(c=='-')f=0;
	do res=(res<<3)+(res<<1)+(c^48);
	while(c=getchar(),c>=48&&c<=57);
	return f?res:-res;
}
 
template<class T>inline bool Min(T &a, T const&b) {
	return a>b?a=b,1:0;
}
template<class T>inline bool Max(T &a, T const&b) {
	return a<b?a=b,1:0;
}
const int N=1e4+5,M=305,mod1=97,mod2=3761599;
 
bool MOP1;
 
int n,k,m,mod[N],res[N];
 
bool MOP2;
 
int Exgcd(int a, int b, int &x, int &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	int g=Exgcd(b,a%b,y,x);
	y-=a/b*x;
	return g;
}
 
inline int Mul(int x,int y,int mod) {
	int res=0,f=0;
	if(y<0)f=1,y=-y;
	while(y) {
		if(y&1)res=(res+x)%mod;
		x=x+x%mod,y>>=1;
	}
	return f?-res:res;
}
 
inline int Excrt(void) {
	int M=mod[1],ans=res[1],x,y;
	rep(i,2,k) {
		int g=Exgcd(M,mod[i],x,y);
		if((res[i]-ans)%g)return -1;
		y=mod[i]/g;
		x=Mul(x,(res[i]-ans)/g,y);
		x=(x+y)%y;
		ans=M*x+ans,M=M/g*mod[i],ans%=M;
	}
	int z=(ans%M+M)%M;
	if(!z)z=M;
	return z;
}
 
int vis[1000005];
 
inline void _main(void) {
	n=Read(),m=Read(),k=Read();
	rep(i,1,k)mod[i]=Read(),res[i]=((1-i)%mod[i]+mod[i])%mod[i];
	int LCM=1;
	rep(i,1,k) {
		LCM=LCM/__gcd(LCM,mod[i])*mod[i];
		if(LCM<0||LCM>n)return(void)puts("NO");
	}
	int Now=Excrt();
	if(Now==-1)return(void)puts("NO");
	if(Now+k-1>m)return(void)puts("NO");
	rep(i,1,k)if(__gcd(Now+i-1,LCM)!=mod[i])return(void)puts("NO");
	return(void)puts("YES");
}
 
signed main() {
	_main();
	return 0;
}
```

---

## 作者：Refined_heart (赞：1)

[CF338D GCD Table](https://www.luogu.com.cn/problem/CF338D)

$$\text{Solution}$$

我们依次来考虑 $i,j$ 需要满足的条件。

首先，既然满足所有 $1\leq l\leq k$ 满足 $\gcd(i,j+l-1)=a_l,$ 那么可以合理导出 $\forall a_l,a_l|i\to \text{lcm}(a)_{i=1}^{k}|i$

也就是 $i$ 应当是 $\text{lcm}$ 的倍数形式。

那么，设最小公倍数为 $M,$ 设 $i=k\times M,$ 有一个推论：$k=1$ 最优。

证明：若 $k\not =1,$ 则 $\gcd(i,j+l-1)=\gcd(k\times M,j+l-1)$ 

我们发现，$\gcd$ 的式子里面平白无故多了一个 $k.$ 同时，假定 $j$ 满足条件，那么当 $i$ 取最小的时候，不合法当且仅当 $\gcd(i,j+l-1)>a_l,$ 而将 $i\to M\times k$ 并不会将答案变小，所以并不优。

那么 $i$ 的构造就显然了，直接取最小公倍数即可。

考虑 $j$ 如何构造。容易发现， $j$ 需要满足的性质应该是 $a_l|j+l-1,$ 也就是 $j+l-1\equiv 0(\bmod a_l)\to j\equiv 1-l(\bmod a_l)$

于是这就是一堆同余方程组了，但我们还会发现 $a_l$ 之间并不互质。所以我们需要 ExCRT 来解决。

考虑无解，我们发现，解决方程组只是必要条件，直接带入检验即可。

一些细节：

* 注意解扩展中国剩余定理的时候，方程的解是相对于前 $k-1$ 个方程的，所以对应解出来的数不能随便模别的数

* 注意到扩展欧几里得的通解形如 $x=x_0+k\times \frac{c}{\gcd(a,b)}$ 如果我们要让它最小就让它取正数后对 $\frac{c}{\gcd(a,b)}$ 取模即可

* 这题数据范围大，会爆，需要龟速乘

* 当解要大的时候就算无解了，因为超出了表格的范围

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e4+10;
int n,m,k,a[N],ans1=1,ans2;
inline int gcd(int x,int y){return !y?x:gcd(y,x%y);}
void Exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1;y=0;
		return;
	}
	Exgcd(b,a%b,x,y);
	int t=x;x=y;y=t-a/b*y;
}
inline int LCM(int x,int y){return x/gcd(x,y)*y;}
inline int Min(int x,int y){return x>y?y:x;}
inline int Max(int x,int y){return x<y?y:x;}
int Mul(int x,int y,int p){
	if(y<0)x=-x,y=-y;
	int s=0;
	while(y){
		if(y&1)s=(s+x)%p;
		x=(x+x)%p;y>>=1;
	}
	return s;
}
void solve(int *A,int *b,int len){
	int M=b[1];
	int xx=0;
	for(int i=2;i<=k;++i){
		int r=A[i]-xx;
		int t,y;
		int d=gcd(M,b[i]);
		if(r%d!=0){
			puts("NO");
			exit(0);
		}
		Exgcd(M,b[i],t,y);
		int nM=LCM(M,b[i]);
		t=Mul(t,r/d,b[i]/d);
		xx=(xx%nM+t%nM*M%nM)%nM;
		if(M>m){
			puts("NO");
			exit(0);
		}
		M=nM;
		xx%=M;xx+=M;xx%=M;
	}
	xx%=M;xx+=M;xx%=M;
	if(xx==0)xx=M;
	if(xx>m){
		puts("NO");
		exit(0);
	}
	ans2=xx;
	for(int i=1;i<=k;++i){
		if(gcd(ans1,ans2+i-1)!=a[i]){
			puts("NO");
			exit(0);
		}
	}
	puts("YES");
}
int num[N];
signed main(){
// 	freopen("in.txt","r",stdin);
	cin>>n>>m>>k;
	for(int i=1;i<=k;++i)cin>>a[i];
	for(int i=1;i<=k;++i){
		ans1=LCM(ans1,a[i]);
		if(ans1>n){
			puts("NO");
			return 0;
		}
	}
	for(int i=1;i<=k;++i)num[i]=(((a[i]-i+1+a[i])%a[i])+a[i])%a[i];
	solve(num,a,k);
	return 0;
}
```

---

## 作者：两年打铁 (赞：1)

由题意可知

$gcd(x,y+l-1)=a_l$ 

设$x=na_l,y+l-1=ma_l$ 

再将$x,y$ 模$a_l$ 得 $x \   mod \  a_l =0$ ，  $y=(1-l)\ mod(a_l)$ 

我们就得到了关于y的同余方程组，用EXCRT解即可

因为x无法解得，我们可以由 所有a的lcm所得

因为lcm与y的gcd是$a_l$ 的倍数，而又是x的约数，那么我们选lcm就是最优的

``` cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+7; 
#define ll long long 
#define int long long 
void read(int &x)
{
	x=0;
	char ch=getchar();
	int pd=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			pd=-pd;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=pd;
}
void write(const int &x)
{
	char ggg[10001];
	int s=0;
	int tmp=x;
	if(tmp==0)
	{
		putchar('0');
		return;
	}
	if(tmp<0)
	{
		tmp=-tmp;
		putchar('-');
	}
	while(tmp>0)
	{
		ggg[s++]=tmp%10+'0';
		tmp/=10;
	}
	while(s>0)
	{
		putchar(ggg[--s]);
	}
}

int gcd(int x,int y)
{
	return !x?y:gcd(y%x,x);
}

ll l,n,m,aa[10010];
ll a[N],b[N];
ll ans,lcm,x,y,bg;
ll mul(ll a,ll b,ll P) 
{
    ll s=0;
    for (;b;b>>=1,a=(a+a)%P) if (b&1) s=(s+a)%P;
    return s;
}
ll exgcd(ll a,ll b,ll &x,ll &y) 
{
    if (!b) {x=1,y=0;return a;}
    ll gd=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return gd;
}
ll excrt() 
{
    ans=a[1],lcm=b[1],x,y;
    for (ll i=2;i<=l;i++) 
	{
        ll B=b[i],A=(a[i]-ans%B+B)%B;
        ll gd=exgcd(lcm,B,x,y),bg=B/gd;
        if (A%gd) return -1;
        x=(x+bg)%bg;
		x=mul(x,A/gd,bg);
        ans+=x*lcm;
        lcm*=bg;
        ans%=lcm;
    }
    return ans==0?lcm:ans;
}

signed main() 
{
    read(n);
    read(m);
    read(l);
    if(l>m)
    {
    	puts("NO");
    	return 0;
	}
    for(register int i=1;i<=l;++i)
    {
    	read(aa[i]);
    	b[i]=aa[i];
	}
	for(register int i=1;i<=l;++i)
	{
		a[i]=(1-i);
		while(a[i]<aa[i])
		{
			a[i]+=aa[i];
		}
		a[i]%=aa[i];
	}
	int yy=excrt();
	if(yy==-1)
	{
		puts("NO");
		return 0;
	 } 
	if(yy+l-1>m)
	{
		puts("NO");
		return 0;
	}
	if(lcm>n)
	{
		puts("NO");
		return 0;
	} 
	for(register int i=1;i<=l;++i)
	{
		if(gcd(lcm,yy+i-1)!=aa[i])
		{
			puts("NO");
			return 0;
		}
	} 
	puts("YES");
}
```

---

## 作者：hfjh (赞：1)

# CF338D GCD Table 题解

## 题目描述

你有一个长度为 $k$ 的数列 $a$，

询问是否存在 $x\in[1,n]~~~y\in[1,m]$ 使得     $~~\forall i~~~ \gcd(x,y+i-1)=a_i$ 成立。

## 解析

我们转换一下可以得到：

$$
\forall i ~~\left\{ 
\begin{matrix}
x\equiv 0\pmod{a_i} \\
y+i-1\equiv 0\pmod{a_i}
\end{matrix}
\right.



$$

前面一个 $x$ 很好解决，直接**最大公倍数**。

$y$ 可以转化一下：

$$
y\equiv 1-i\pmod{a_i}
$$

经典**扩展中国剩余定理**。

但是我们因为分开考虑的 $x$ 与 $y$ 得到的不一定是**充要条件**。

我们需要再次验证一下。
> 直接用得到的 $x,y$ 跑一遍就行了。

## 温馨提示

1.在运算过程中会爆  ```long long```  需要龟速乘。

2.在运算过程中**最大公倍数**也就是 $x$ 会爆```long long```，我们需要判断一下有没有超过 $n$ 如果超过直接 NO。

3.计算 $y$ 的时候有可能 $y = 0$ 在这个情况下我们考虑 $y = 0$ 和 $y = x$ 是等价的我们可以直接赋值成 $x$ 就可以了。

> 考虑 $x$ 还表示了 $a$ 数列的最大公倍数。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 1e4 + 10;
int k;
ll n, m, a[N], x = 1,y = 0,M;
ll mmul(ll x,ll k,ll p){
	ll ans = 0,d = x;
	while(k){
		if(k & 1) ans = (ans + d) % p;
		k >>= 1;
		d = d * 2 % p;
	}
	return ans;
}
ll gcd(ll a,ll b){
	if(b == 0) return a;
	return gcd(b, a % b);
}
void exgcd(ll a,ll b,ll &x,ll &y){
	if(b == 0){
		x = 1,y = 0;
		return ;
	}
	exgcd(b, a % b, x, y);
	ll z = x;
	x = y;
	y = z - (a / b) * y;
}
ll jfc(ll a,ll b,ll c){
	ll x = 0,y = 0,g;
	g = gcd(a,b);
	a /= g,b /= g;
	if(c % g) return -1;
	exgcd(a, b, x, y);
	return mmul((x % b + b) % b,c / g,b);
}
void input(){
	cin>>n>>m>>k;
	for(int i = 1; i <= k; ++i){
		cin>>a[i];
	}
}
bool op(){
	for(int i = 1;i <= k; ++i){
		ll now = jfc(x,a[i],(((1 - i + a[i]- y) % a[i] + a[i]) % a[i]));
		if(now == -1) return 0;
		y = (mmul(now,x,x * a[i] / gcd(x,a[i])) + y) % (x * a[i] / gcd(x,a[i]));
		x = x * a[i] / gcd(x,a[i]);
		if(x > n) return 0;
	}	
	if(y == 0) y = x;
	if((y + k - 1) > m) return 0;
	return 1;
}
bool pd(){
	for(int i = 1;i <= k; ++i){
		ll now = gcd(x,y + i * 1ll - 1ll);
		if(now != a[i]) return 0 ;
	}
	return 1;
}
int main(){
	input();
	if(op() && pd()){
		cout<<"YES";	
	}else{
		cout<<"NO";
	}
	return 0;
}
```

---

## 作者：Albatross_LC (赞：0)

### 思路：

若选中的的起始位置为 $(i,j)$，则：

$$
\left\{\begin{aligned} \gcd(i,j)=a_1 \\ \gcd(i,j+1)=a_2 \\ \gcd(i,j+2)=a_3\end{aligned}\right.
\Leftrightarrow 
\left\{\begin{aligned} j \equiv 0 \pmod{a_1} \\ j \equiv -1 \pmod{a_2} \\ j \equiv -2 \pmod{a_3}\end{aligned}\right.
$$

上式可以通过 `excrt` 求得 $j$ 的通解：$j=j_0+M\cdot x$，$M=\operatorname{lcm}(a_1,a_2\dots a_k) $，且 $i$ 是 $M$ 的倍数，$i=M+M\cdot y$。

若 $g=\gcd(M, j_0)$，$g\prime =\gcd(M+M\cdot y, j_0+M\cdot x)$，可以看出 $g \mid g\prime $。

只需要判断 $j=j_0$，$i=M$ 是否成立就行了，因为 $\gcd(i,j+t)$ 有可能是 $a_{t+1}$ 的倍数，这样条件就不成立。

### Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e4 + 10;
int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int nx, ny;
    int d = exgcd(b, a % b, nx, ny);
    x = ny;
    y = nx - a / b * ny;
    return d;
}
int lcm(int a, int b) { return a / __gcd(a, b) * b; }
pair<int, int> excrt(int k, int *a, int *r) {
    int M = r[1], ans = a[1];
    for (int i = 2; i <= k; i++) {
        int x0, y0;
        int c = a[i] - ans;
        int g = exgcd(M, r[i], x0, y0);
        if (c % g != 0) return {-1, -1};
        x0 = (__int128)x0 * (c / g) % (r[i] / g);
        ans = x0 * M + ans;
        M = lcm(M, r[i]);
        ans = (ans % M + M) % M;
    }
    return {ans, M};
}
int n, m, k, a[N];
int b[N];
signed main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) cin >> a[i], b[i] = -(i - 1);
    pair<int, int> x = excrt(k, b, a);
    if (x.first == 0) x.first = x.second;
    if (x.first > m - k + 1 || x.second > n || x.first == -1) {
        cout << "NO";
    } else {
        for (int i = 0; i < k; i++)
            if (__gcd(x.first + i, x.second) != a[i + 1]) {
                cout << "NO";
                return 0;
            }
        cout << "YES";
    }
}
```

---

## 作者：orz_z (赞：0)

## 题目描述

给你 $n,m,k,p$。

你有一个长度为 $k$ 的数列 $a$。

询问是否存在 $x,y$，$1 \leq x \leq n, 1 \leq y + k-1\leq m$，满足 $\forall 1 \leq l \leq k,\gcd(x,y+l-1)=a_l$。

若存在，输出 `YES`，否则，输出 `NO`。

对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^{12},1 \leq m \leq 10^{12}, 1 \leq k \leq 10^5,1 \leq a_i \leq 10^{12}$。

## 解题思路

前置知识：`exCRT`。

根据题意显然可以列出：
$$
\begin{cases}\gcd(x,y+1-1)=a_1 \\ \gcd(x,y+2-1)=a_2 \\ \cdots \\ \gcd(x,y+k-1)=a_k\end{cases}
$$
我们知道 $\gcd(a,b)=c$，显然有：$a=p_1c,b=p_2c,p_1\nmid p_2$，

即：
$$
a \mid c,b \mid c \Rightarrow x \mid a_i,y + i-1 \mid a_i
$$
即：

$$
x \equiv 0 \pmod{a_i}
$$

和

$$
y \equiv 1-i \pmod{a_i}
$$

整理出：
$$
\begin{cases}y \equiv (1-1) \pmod{a_1} \\ y \equiv (2-1) \pmod{a_2} \\  \\ \cdots \\ y \equiv (k-1) \pmod{a_k}\end{cases}
$$
显然 $a_i$ 之间不一定互质，所以我们直接使用拓展中国剩余定理求解即可，这样我们就可以求出一个合法的 $y$。

显然 $x$ 可以整除所有的 $a_i$ ，那么满足条件的最小的 $x$ 显然是 $\text{lcm}\{a_{i}\}$。

求出 $x,y$ 以后验证是否在范围内即可。

时间复杂度 $\mathcal{O}(n \log n)$。

## CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int read()
{
    int f = 1, x = 0;
    char c = getchar();
    while(c < '0' || c > '9'){if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9'){x = x * 10 + c - '0'; c = getchar();}
    return f * x;
}

const int maxn = 100010;

int n, p;

int a, b;

int Lcm = 1;

int ai[maxn], bi[maxn];

int js(int x, int mod)
{
	if(x < mod) return x;
	return x % mod + mod;
}

int gcd(int a, int b)
{
	if(!b) return a;
	return gcd(b, a % b);
}

int lcm(int a, int b)
{
	return a / gcd(a, b) * b;
}

int mul(int a, int b, int mod)
{
	if(b < 0) a = -a, b = -b;
    int res = 0;
    while(b > 0)
    {
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

int exgcd(int a, int b, int &x, int &y)
{
    if(b == 0){x = 1; y = 0; return a;}
    int gcd = exgcd(b, a % b, x, y);
    int tp = x;
    x = y; y = tp - a / b * y;
    return gcd;
}

int excrt()
{
    int x, y, k;
    int M = bi[1], ans = ai[1];
    for(int i = 2; i <= n; ++i)
    {
        int a = M, b = bi[i], c = (ai[i] - ans % b + b) % b;
        int gcd = exgcd(a, b, x, y), bg = b / gcd;
        if(c % gcd != 0) return -1;
        x = mul(x, c / gcd, bg);
        ans += x * M;
        M *= bg;
        ans = (ans % M + M) % M;
    }
    ans = (ans % M + M) % M;
    if(ans == 0) ans = M;
    return ans;
}

int phi(int x)
{
	int o = x;
	for(int i = 2; i * i <= x; ++i)
	{
		if(x % i == 0)
		{
			while(x % i == 0) x /= i;
			o = o / i * (i - 1);
		}
	}
	if(x > 1) o = o / x * (x - 1);
	return o;
}

int qpow(int x, int y, int mod)
{
	int res = 1ll;
	while(y)
	{
		if(y & 1ll) res = js(res * x, mod);
		x = js(x * x, mod);
		y >>= 1ll;
	}
	return x;
}

int solve(int l, int r, int mod)
{
	if(l == r || mod == 1) return js(l, mod);
	return qpow(l, solve(l + 1, r, phi(mod)), mod);
}

signed main()
{
    a = read(), b = read(), n = read(), p = read();
    for(int i = 1; i <= n; ++i)
    {
    	bi[i] = read();
		ai[i] = (1 - i + bi[i]) % bi[i];
		Lcm = lcm(Lcm, bi[i]);
	}
	if(n > b) return puts("NO"), 0;
	int x = Lcm, y = excrt();
	if(y == -1) return puts("NO"), 0;
	for(int i = 1; i <= n; ++i)
		if(gcd(x, y + i - 1) != bi[i])
			return puts("NO"), 0;
	if(y < 1 || x < 1 || y + n - 1 > b || x > a) 
		return puts("NO"), 0;
	puts("YES");
	return 0;
}
```

---

