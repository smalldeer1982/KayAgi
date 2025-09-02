# Lunar New Year and a Recursive Sequence

## 题目描述

农历新年即将到来，Bob 最近收到了一份来自朋友的礼物——一个递归数列！他非常喜欢这个数列，想要玩一玩。

设 $f_1, f_2, \ldots, f_i, \ldots$ 是一个无限的正整数序列。Bob 知道，对于 $i > k$，$f_i$ 可以通过如下递推公式得到：

$$
f_i = \left(f_{i - 1}^{b_1} \cdot f_{i - 2}^{b_2} \cdot \cdots \cdot f_{i - k}^{b_k}\right) \bmod p,
$$

简写为

$$
f_i = \left(\prod_{j = 1}^{k} f_{i - j}^{b_j}\right) \bmod p,
$$

其中 $p = 998\,244\,353$（一个常用的大质数），$b_1, b_2, \ldots, b_k$ 是已知的整数常数，$x \bmod y$ 表示 $x$ 除以 $y$ 的余数。

Bob 不小心丢失了 $f_1, f_2, \ldots, f_k$ 的值，这让他非常苦恼——这些正是数列的基础！幸运的是，Bob 还记得数列的前 $k-1$ 项：$f_1 = f_2 = \ldots = f_{k-1} = 1$，以及第 $n$ 项的值：$f_n = m$。请你帮他找出任意一个可能的 $f_k$ 的值。如果不存在这样的 $f_k$，无论 Bob 多么伤心，也请你告诉他无法恢复他心爱的数列。

## 说明/提示

在第一个样例中，有 $f_4 = f_3^2 \cdot f_2^3 \cdot f_1^5$。因此，代入 $f_3 = 4$，得到 $f_4 = 16$。注意，可能有多个答案。

在第三个样例中，$f_7 = 1$ 使得 $f_{23333} = 1$。

在第四个样例中，没有任何 $f_1$ 能使 $f_{88888} = 66666$，因此输出 $-1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2 3 5
4 16
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
4 7 1 5 6
7 14187219
```

### 输出

```
6
```

## 样例 #3

### 输入

```
8
2 3 5 6 1 7 9 10
23333 1
```

### 输出

```
1
```

## 样例 #4

### 输入

```
1
2
88888 66666
```

### 输出

```
-1
```

## 样例 #5

### 输入

```
3
998244352 998244352 998244352
4 2
```

### 输出

```
-1
```

## 样例 #6

### 输入

```
10
283 463 213 777 346 201 463 283 102 999
2333333 6263423
```

### 输出

```
382480067
```

# 题解

## 作者：Itst (赞：8)

[MyBlog](https://www.cnblogs.com/Itst/p/10344913.html)

### 前置芝士：原根、矩阵快速幂、BSGS

------

好久没写数论题了写一次调了1h

首先发现递推式是一个乘方的形式，线性递推和矩阵快速幂似乎都做不了，那么是否能够把乘方运算变成加法运算和乘法运算呢？

使用原根！学过$NTT$的都知道$998244353$的原根$G=3$。

使用原根之后，可以得到一个等价的新递推式：$G^{g_i} = \prod\limits _ {j=1}^k G^{g_{i - j} \times b_j} \mod 998244353(G^{g_i} \equiv f_i\mod 998244353)$，它等价于$g_i = \sum\limits_{j=1}^k g_{i-j} \times b_j \mod 998244352$。这样就可以矩阵快速幂得出当$f_k$等于某个值$G^p$时$f_n$的值了。

可现在知道的是$f_n$的值，不知道$f_k$的值。

考虑：令$G_k=1$，得到$G_n$的值$x$，那么可以知道$f_k^x \equiv f_n \mod 998244353$。

这是一个模意义下的高次剩余方程，要怎么求解呢？

同样使用原根。设$f_{k} = G^b \mod 998244353$，通过$BSGS$求出$f_n = G^y \mod 998244353$，那么原式变成$G^{bx} \equiv G^y \mod 998244353$，即$bx \equiv y \mod 998244352$。逆元求解方程得到$b$，也就得到了$f_k$。

一些打比赛时被坑到的点：

①$998244352 = 2^{23} \times 7 \times 17$，求逆元要用欧拉定理或者拓展欧几里得

②$998244351 \times 998244351 \times 100 > 2^{63}$，这意味着矩阵相乘不能算完再一起取模

```c++
#include<bits/stdc++.h>
#define int long long
//This code is written by Itst
using namespace std;

inline int read(){
    int a = 0;
    char c = getchar();
    bool f = 0;
    while(!isdigit(c)){
	    if(c == '-')
			f = 1;
        c = getchar();
    }
    while(isdigit(c)){
		a = (a << 3) + (a << 1) + (c ^ '0');
		c = getchar();
	}
	return f ? -a : a;
}

const int MOD = 998244353 , G = 3;
int K;
struct matrix{
	int a[100][100];
	int* operator [](int x){return a[x];}
	matrix(){memset(a , 0 , sizeof(a));}
	matrix operator *(matrix b){
		matrix c;
		for(int i = 0 ; i < K ; ++i)
			for(int j = 0 ; j < K ; ++j)
				for(int k = 0 ; k < K ; ++k)
					c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % (MOD - 1);
		return c;
	}
}S , T;

inline int gcd(int a , int b){
	int r = a % b;
	while(r){
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}

inline int poww(int a , int b , int mod = MOD){
	int times = 1;
	while(b){
		if(b & 1)
			times = times * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return times;
}

map < int , int > Hash;

inline int BSGS(int x){
	int t = sqrt(MOD) + 1 , times = x;
    for(int i = 0 ; i < t ; i++){
        Hash[times] = i;
        times = times * G % MOD;
    }
    times = poww(G , t);
    int now = times;
    for(int i = 1 ; i <= t + 1 ; i++){
        if(Hash.count(now)){
            return i * t - Hash[now];
        }
        now = now * times % MOD;
    }
	return -1;
}

int phi(int x){
	int times = x;
	for(int i = 2 ; i * i <= x ; ++i){
		if(x % i == 0){
			times = times / i * (i - 1);
			while(x % i == 0)
				x /= i;
		}
	}
	if(x - 1)
		times = times / x * (x - 1);
	return times;
} 

signed main(){
	#ifndef ONLINE_JUDGE
	//freopen("in" , "r" , stdin);
	//freopen("out" , "w" , stdout);
	#endif
	K = read();
	for(int i = 0 ; i < K ; ++i)
		T[K - i - 1][K - 1] = read() % (MOD - 1);
	int N = read() - K;
	int t = BSGS(read());
	for(int i = 0 ; i + 1 < K ; ++i)
		T[i + 1][i] = 1;
	S[0][K - 1] = 1;
	while(N){
		if(N & 1)
			S = S * T;
		T = T * T;
		N >>= 1;
	}
	int cur = S[0][K - 1] , p = gcd(cur , MOD - 1);
	if(t % p != 0)
		puts("-1");
	else{
		t /= p;
		cur /= p;
		int mod = (MOD - 1) / p; 
		cout << poww(G , poww(cur , phi(mod) - 1 , mod) * t % mod);
	}
	return 0;
}
```

---

## 作者：zhiyangfan (赞：7)

## CF1106F Lunar New Year and a Recursive Sequence
> 定义无穷正整数序列 $f_1,f_2,\cdots$，对于任意的 $i>k$，$f_i$ 是如下递归定义的：
> $$f_i=\prod_{j=1}^k f_{i-j}^{b_j}\bmod{p}$$
> 其中 $p=998,244,353$。给出序列 $b_1,b_2,\cdots,b_k$，已知 $f_1=f_2=\cdots=f_{k-1}=1,f_n=m$，求 $f_k$ 可能的值，或报告无解。($1\le k\le 100,1\le b_i,m<p,k<n\le 10^9$，你需要保证 $1\le f_k<p$)

发现 $\prod$ 和乘方这种东西非常不好处理，但这个形式和常系数齐次递推确实很像。说明这道题可能要求我们把 $\prod$ 变为 $\sum$，乘方变为乘法，这样就能凑成常系数齐次递推的形式。

考虑在实数意义下，这种事非常好办，直接取对数即可。而在模意义下，我们可以取离散对数。具体来讲，我们想找到一个 $c$，满足存在一个 $l$，使得：
$$c^l\equiv a\pmod{p}$$
则 $a$ 的离散对数就可以定义为 $l$。发现关键在于 $c$ 的选择，合适的 $c$ 应该让尽可能多的数拥有离散对数。注意到原根的性质有一条：
> 对于所有的 $t(t\bot p)$，在模 $p$ 意义下都能被 $p$ 的原根 $g$ 的幂次的形式表示。

又因为此题 $p$ 是质数，所以我们只需选择它的原根 $3$ 作为 $c$，即可保证所有的正整数都存在离散对数。而求离散对数的过程相当于求解这样一个同余方程：
$$a^x\equiv b\pmod{p}$$
可以用 $\rm BSGS$ 在 $\mathcal{O}(\sqrt{p})$ 的时间复杂度内轻松实现。但需要注意，求解的 $x$ 和离散对数是模 $\varphi(p)$ 同余的。

设 $f_i$ 的离散对数为 $lf_i$，则上式可以化为：
$$lf_i=\sum_{j=1}^kb_jlf_{i-j}\bmod{\varphi(p)}$$
发现可以用矩阵乘法表示这个过程，即：
$$\begin{bmatrix}lf_{i-k}&lf_{i-k+1}&\ldots&lf_{i-1}\end{bmatrix}\begin{bmatrix}0&0&\ldots&0&b_k\\1&0&\ldots&0&b_{k-1}\\\vdots&\vdots&\ddots&\vdots&\vdots\\0&0&\ldots&1&b_1\end{bmatrix}=\begin{bmatrix}lf_{i-k+1}&lf_{i-k+2}&\ldots&lf_i\end{bmatrix}$$
如果设转移矩阵为 $\mathbf{A}$，则整个过程相当于：
$$\begin{bmatrix}0&0&\ldots&lf_k\end{bmatrix}\times\mathbf{A}^{n-k}=\begin{bmatrix}\ldots&\ldots&\ldots&lf_n\end{bmatrix}$$
观察到 $1$ 的离散对数是 $0$ 即可得到初始矩阵。注意到我们只关心 $lf_n$ 的值，所以根据上面的等式，我们可以得到如下同余式：
$$lf_k(\mathbf{A}^{n-k})_{k,k}\equiv lf_n\pmod{\varphi(p)}$$
由于矩阵是已知的，所以不妨把 $(\mathbf{A}^{n-k})_{k,k}$ 设为一个常量 $a$，再把 $lf_k$ 设为 $x$，$lf_n$ 设为 $b$，则我们现在只需要解一个线性同余方程就够了：
$$ax\equiv b\pmod{\varphi(p)}$$
可以用 $\rm exgcd$ 轻松判无解和求出通解。求出 $x$ 后，$f_k$ 即为 $g^x\bmod{p}$。时间复杂度 $\mathcal{O}(k^3\log n+\sqrt{p})$。计算的时候注意模数在这一步到底是 $p$ 还是 $\varphi(p)$。
```cpp
#include <cmath>
#include <cstdio>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
const int N = 110, mod = 998244353; typedef long long ll; int b[N];
int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }
int exgcd(int a, int b, int& x, int& y)
{
	if (!b) { x = 1; y = 0; return a; }
	int r = exgcd(b, a % b, x, y);
	int t = x; x = y; y = t - a / b * y;
	return r;
}
struct Matrix
{
	int a[N][N], n, m;
	void norm(int N)
	{
		n = m = N;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) a[i][j] = (i == j);
	}
	Matrix operator*(const Matrix& A)
	{
		Matrix ret; ret.n = n; ret.m = A.m;
		for (int i = 1; i <= ret.n; ++i)
			for (int j = 1; j <= ret.m; ++j)
			{
				int add = 0;
				for (int k = 1; k <= m; ++k) 
					(add += (ll)a[i][k] * A.a[k][j] % (mod - 1)) %= (mod - 1);
				ret.a[i][j] = add;
			}
		return ret;
	}
}A, I;
inline Matrix ksm(Matrix A, int b)
{
	Matrix ret = I;
	while (b)
	{
		if (b & 1) ret = ret * A;
		A = A * A; b >>= 1;
	}
	return ret;
}
inline int ksm(int a, int b, int mod)
{
	int ret = 1;
	while (b)
	{
		if (b & 1) ret = (ll)ret * a % mod;
		a = (ll)a * a % mod; b >>= 1;
	}
	return ret;
}
namespace BSGS
{
	__gnu_pbds::gp_hash_table<int, int> mp; int mod, sqr;
	inline void initMod(int _mod) { mod = _mod; sqr = ceil(sqrt(mod)); }
	inline int getSol(int a, int b)
	{
		mp.clear(); int lef = (ll)a * b % mod;
		for (int B = 1; B <= sqr; ++B, lef = (ll)lef * a % mod) mp[lef] = B;
		int rig = ksm(a, sqr, mod), aa = rig;
		for (int A = 1; A <= sqr; ++A, rig = (ll)rig * aa % mod)
			if (mp.find(rig) != mp.end()) return A * sqr - mp[rig];
		return -1;
	}
}
int main()
{
	int k; scanf("%d", &k); A.norm(k); I.norm(k);
	for (int i = 1; i <= k; ++i) scanf("%d", b + i);
	for (int j = 1; j < k; ++j)
	{
		for (int i = 1; i <= k; ++i) A.a[i][j] = 0;
		A.a[j + 1][j] = 1;
	}
	for (int i = 1; i <= k; ++i) A.a[i][k] = b[k - i + 1];
	int n, m; scanf("%d%d", &n, &m); A = ksm(A, n - k);
	BSGS::initMod(mod); int g = 3; m = BSGS::getSol(g, m);
	if (m % gcd(A.a[k][k], mod - 1)) return puts("-1"), 0;
	int x, y; exgcd(A.a[k][k], mod - 1, x, y);
	x = (ll)m / gcd(A.a[k][k], mod - 1) * x % (mod - 1); 
	(x += mod - 1) %= (mod - 1);
	printf("%d\n", ksm(g, x, mod)); 
	return 0;
}
```
如果本题是任意质数作为模数，则我们就需要求出原根。根据引理：
> 一个数 $n$ 如果有原根，则它的最小原根级别是 $\mathcal{O}(n^{0.25})$。

我们可以暴力枚举原根，并判断是否可行。判断根据以下引理：
> 一个数 $g$ 是数 $n$ 的原根当且仅当 $\gcd(g,n)=1$，且对于 $\varphi(n)$ 的所有质因数 $p$，都有 $g^{\frac{\varphi(n)}{p}}\not\equiv1\pmod{n}$。

可以在 $\mathcal{O}(p^{0.75}\log p)$ 的时间复杂度内求解。

---

## 作者：周道_Althen (赞：4)

### 写在前面

$\ \ \ \ \ \ \,$这场比赛是wc2019回家那天晚上举办的，从8点到10点刚好在动车上，饥寒交迫，还拉肚子（吃不惯粤菜），就没有参加，是后面写的。

$\ \ \ \ \ \ \,$这套题在洛谷上面五颜六色的，很有意思啊（除了没有红的），题目也算可做，感觉很过年很快乐呢（~~嘤嘤~~

$\ \ \ \ \ \ \,$~~顺便打个全套题解的广告[【Codeforces Round #536 (Div. 2)【己亥年农历新年赛】简略题解】](https://blog.csdn.net/weixin_43973966/article/details/87389814)~~

---

$\ \ \ \ \ \ \,$感觉这道题操作比E题麻烦一点，但是确实比E题好想呢。

## $\ \ \ \ \ \ \,$前置知识：矩阵快速幂，扩展GCD求逆元，BSGS，欧拉定理，原根

$\ \ \ \ \ \ \,$~~（本题解不会讲这些东西，只是会提到为什么用和怎么用，溜了溜了~~

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190215213423624.jpg)

$\ \ \ \ \ \ \,$看到是一个有 $k$ 项的递推式，马上就可以想到矩乘，而前 $k-1$ 项已经确定了是 $1$，我们不妨设要求的 $f_k$ 为 $a$ 。根据他给的式子啊，我们就容易发现，这个递推式的每一项都应该是 $a^x$ 的形式，知道第 $n$ 项是 $a$ 的多少次方就要好处理一些了。

$\ \ \ \ \ \ \,$这样子处理为指数的形式的话，稍微观察一下矩阵乘法就定义好了：

$\ \ \ \ \ \ \,$转移矩阵：$A=$

$$\begin{bmatrix}0&0&\cdots&0&b_k\\ 1&0&\cdots&0&b_{k-1}\\0&1&\cdots&0&b_{k-2}\\\vdots&\vdots&\ddots&\vdots&\vdots\\0&0&\cdots&1&b_1\end{bmatrix}$$

$\ \ \ \ \ \ \,$初始矩阵：$S=$

$$\begin{bmatrix}0,0,\cdots,0,1\end{bmatrix}$$

$\ \ \ \ \ \ \,$那么第 $n$ 项的指数，就是 $S\cdot A^{n-k}$ 的第 $k$ 项，矩阵乘法取模的时候，根据欧拉定理，因为模数是素数，直接每次模 $mod-1$ 就好了。

$\ \ \ \ \ \ \,$现在问题是，我们知道 $x$，$m$，$mod$，$a^x\%mod=m$，如何求 $a$ 呢？

$\ \ \ \ \ \ \,$好在他给我们的模数很特殊，我们很清楚他的原根为 $3$ ，那么我们可以重新把 $a$ 定义为 $3^s\%mod$，所以原式化为:

$$3^{sx}\%mod=m$$

$\ \ \ \ \ \ \,$我们可以很轻松用 BSGS 算法知道 $sx\%(mod-1)$的取值，而我们又知道 $x\%(mod-1)$ 的取值，要求$s$的取值，用到逆元，发现这里的模数并不是素数啊，扩展GCD处理一下就好咯~

$\ \ \ \ \ \ \,$然后我们就知道 $s$ 的取值了（也有可能无解），那么答案也就出来了：$f_k=3^s$。

$\ \ \ \ \ \ \,$复杂度的话，$O(k^3\log n+\sqrt {mod} +\log n)$ 这个样子。

```cpp
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cstdio>
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<cmath>
#include<map>
#include<set>
using namespace std;
const int inf=0x7fffffff;
const double eps=1e-10;
const double pi=acos(-1.0);
//char buf[1<<15],*S=buf,*T=buf;
//char getch(){return S==T&&(T=(S=buf)+fread(buf,1,1<<15,stdin),S==T)?0:*S++;}
inline int read(){
	int x=0,f=1;char ch;ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=0;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch&15);ch=getchar();}
	if(f)return x;else return -x;
}
const int mod=998244353;
struct matrix{
	int x,y;
	int a[101][101];
};
int K,m,n;
matrix S,A,T;
matrix operator *(matrix m1,matrix m2){
	matrix t;t.x=m1.x;t.y=m2.y;
	for(int i=1;i<=m1.x;i++)
	for(int j=1;j<=m2.y;j++){
	  	t.a[i][j]=0;
	  	for(int k=1;k<=m1.y;k++)
	  	t.a[i][j]=(1ll*t.a[i][j]+1ll*m1.a[i][k]*m2.a[k][j])%(mod-1);
	}
	return t;
}
matrix power(matrix a,int b){
	matrix ans=a;b--;
	while(b){
		if(b&1ll)ans=ans*a;
		a=a*a;b>>=1;
	}
	return ans;
}
int power(int a,int b,int mod){
	int ans=1;
	while(b){
		if(b&1)ans=(1ll*ans*a)%mod;
		a=(1ll*a*a)%mod;
		b>>=1;
	}
	return ans;
}
long long BSGS(long long a,long long b,long long c){
  	map<int,int>hash;hash.clear();b%=c;
  	int t=(int)sqrt(c)+1;
  	for(int j=0;j<t;j++){
    	int val=(int)(b*power(a,j,c)%c);
    	hash[val]=j;
  	}
  	a=power(a,t,c);
  	if(a==0){
  		if(b==0)return 1;
    	else return -1;
  	}
  	for(int i=0;i<=t;i++){
    	int val=power(a,i,c);
    	int j=hash.find(val)==hash.end()?-1:hash[val];
    	if(j>=0&&i*t-j>=0)return i*t-j;
  	}
  	return -1;
}
void exgcd(long long a,long long b,long long &d,long long &x,long long &y){
	if(!b){d=a;x=1;y=0;return;}
	exgcd(b,a%b,d,y,x);y-=x*(a/b);
}
int main()
{
	K=read();S.x=1;
	A.x=A.y=S.y=K;S.a[1][K]=1;
	for(int i=2;i<=K;i++)A.a[i][i-1]=1;
	for(int i=K;i>=1;i--)A.a[i][K]=read();
	n=read();m=read();
	T=S*power(A,n-K);
	long long t=BSGS(3ll,1ll*m,mod);
	long long g,x,y;
	exgcd(T.a[1][K],mod-1,g,x,y);
  	if(t%g)puts("-1");
  	else{
   		x=(t/g*x%(mod-1)+mod-1)%(mod-1);
    	printf("%d\n",power(3,x,mod));
  	}
	return 0;
}

```


---

## 作者：Prean (赞：4)

居然没人写常系数齐次线性递推/jy

题意明确。

首先我们注意到这个系数是在幂上面的，这道题的各种信息都是建立在乘法上的，十分不好处理，考虑求一个 $ \ln $ 将这些信息建立在加法上。
$$ \ln f[n]=\sum_{i=1}^kb[i]\ln f[n-i] $$
可以发现这个问题变成了一般的常系数齐次线性递推。

然后发现 $ f_1 \sim f_{k-1} $ 在取了 $ \ln $ 之后全部都变成了 $ 0 $。

考虑使用常系数齐次线性递推的老算法，因为老算法算的实际上是前 $ k $ 项对第 $ n $ 项的贡献。

所以跑一遍老算法就能够得到有 $ x \times \ln f[k] = \ln f[n] $，也就是 $ f[k]^x = f[n] $。

于是只需要在模质数的意义下做 $ k $ 次剩余即可。
```cpp
#include<unordered_map>
#include<cstdio>
typedef unsigned ui;
const ui M=205,MOD=119<<23,mod=MOD|1;
ui len,n,m,p[M];
inline ui pow(ui a,ui b=mod-2){
	ui ans(1);for(;b;b>>=1,a=1ull*a*a%mod)if(b&1)ans=1ull*ans*a%mod;return ans;
}
inline ui Ln(const ui&x){
	ui i,y;const ui X=3,Y=393213064,M=31596;std::unordered_map<ui,ui>hs;
	if(hs.empty()){
		for(y=1,i=1;i<=M&&(y=1ull*y*X%mod);++i)hs[y]=i;hs[1]=0;
	}
	for(y=1,i=1;i<=M&&(y=1ull*y*Y%mod);++i)if(hs.find(1ull*y*x%mod)!=hs.end())return(hs[1ull*y*x%mod]+i*M)%MOD;
	return-1;
}
inline void times(ui*f,ui*g,ui*P,const ui&len){
	ui i,j,t;static ui sav[M];
	for(i=0;i^len;++i)if(f[i])for(j=0;j^len;++j)if(g[j])sav[i+j]=(sav[i+j]+1ull*f[i]*g[j])%MOD;
	for(i=len*2-1;i>=len;--i)if(sav[i])for(t=sav[i],j=len;~j;--j)sav[i-j]=(sav[i-j]+1ull*t*P[j])%MOD;
	for(i=0;i^len;++i)f[i]=sav[i],sav[i]=0;
}
inline ui Solve(ui*P,const ui&len,ui n){
	static ui f[M],sav[M];if(len^1)f[1]=1;else f[0]=p[1];sav[0]=1;
	for(;n;n>>=1,times(f,f,P,len))if(n&1)times(sav,f,P,len);return sav[len-1];
}
ui gcd(const ui&a,const ui&b){
	return b?gcd(b,a%b):a;
}
void exgcd(int a,int b,int&x,int&y){
	if(!b)return x=1,y=0,void();exgcd(b,a%b,y,x);y-=a/b*x;
}
signed main(){
	ui i,ans(0);int a,b,x,y;scanf("%u",&len);p[0]=MOD-1;for(i=1;i<=len;++i)scanf("%u",p+i);scanf("%u%u",&n,&m);
	if(n<len)return printf("-1"),0;
	a=Solve(p,len,n-1);b=Ln(m);i=gcd(a,MOD);
	if(b%i)return printf("-1"),0;a/=i;b/=i;exgcd(a,MOD/i,x,y);
	printf("%u",pow(3,1ull*b*(x+MOD/i)%(MOD/i)));
}
```

---

## 作者：zhongyuwei (赞：3)

题意：有一个无限长的正整数序列$f_1,f_2\cdots $。已知对于所有的$i>k$，满足$f_i = \prod_{j=1}^k f_{i-j} ^{b_j}\mod p$，其中$p=998244353$。已知这个序列的前$k-1$项均为$1$，序列的第$n$项为$m$，问序列的第$k$项是多少。无解输出$-1$，否则，输出任意一组解即可。输出的解必须满足$1\le f_k< p$。$1\le k\le 100,1\le n_i < p,k<n\le 10^9,1\le m<p$。

---

### 前置芝士：原根，矩阵快速幂，BSGS求解方程$a^x\equiv b\mod c$，扩展欧几里得

这里说一下原根的性质：

1）如果$g$是$p$的原根，那么$g$的幂次可以遍历$p$的既约剩余系。即对于任意$x< p$且$gcd(x,p)=1$，$x$一定可以被表示成$g^k$的形式。

2）设$M$为奇质数，只有$2,4$或者形如$M^k,2M^k$的数存在原根。这里，众所周知$998244353$的最小正原根为$3$。

---

我们考虑将所有的数表示为原根的幂次。设$g^{L_i}=f_i$，那么可以得到$L_i=\sum b_jL_{i-j}\mod (p-1)$，这是一个线性递推的形式，可以用矩阵快速幂加速。我们设$L_k = x$，那么对于任意的$i>k$，我们可以用前面的递推式，将$L_i$表示为$k_ix+y_i$的形式。并且，由于$L_1=L_2=L_3\cdots = L_{k-1} =0$，显然对于任意$i>k,y_i=0$。

现在我们知道第$n$项，用$BSGS$算法可以在$\sqrt p$的时间内算出$L_n$。并且，通过矩阵乘法我们算出了$k_i$。这样我们就得到了方程$k_ix\equiv L_n\mod (p-1)$，也就是$k_ix +r(p-1)=L_n$。用扩展欧几里得算法求解即可。

``` cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
#define ll long long
using namespace std;
template <class T>
inline void read(T &x)
{
	x=0; char c=getchar();  int f=1;
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)) x=x*10-'0'+c,c=getchar(); x*=f;
}
const int mod=998244353;
int Pow(int x,int y,int mod){int res=1; while(y){if(y&1)res=res*(ll)x%mod; x=x*(ll)x%mod,y>>=1;} return res;}
map<int,int> mp;
int cal(int x,int b) //x ^ a = b %mod 
{
	if(b==1) return 0;
	int M=ceil(sqrt(mod)),t=b;
	mp[t]=0;
	for(int i=1;i<=M;++i) t=t*(ll)x%mod,mp[t]=i;//,cout<<t<<' '<<i<<endl;
	//t x^M 
	t=Pow(x,M,mod); int q=t;
	for(int i=1;i<=M;++i)
	{
		if(mp.count(q)) return i*M-mp[q];
		q=q*(ll)t%mod;
	}
	return -1;
}
int len;
struct Mat{
	int a[110][110];
	Mat (){memset(a,0,sizeof(a));}
	void E(){for(int i=1;i<=len;++i) for(int j=1;j<=len;++j) a[i][j]=i==j;}
}D;

Mat Mul(Mat A,Mat B)
{
	Mat C;
	for(int i=1;i<=len;++i)
	for(int k=1;k<=len;++k)
	if(A.a[i][k])
	{
		for(int j=1;j<=len;++j)
			C.a[i][j]=(C.a[i][j]+A.a[i][k]*(ll)B.a[k][j])%(mod-1);
	}
	return C;
}
Mat mpow(Mat x,int y)
{
	Mat res; res.E();
	while(y){if(y&1) res=Mul(res,x); x=Mul(x,x),y>>=1;} return res;
}
int exgcd(int &x,int &y,int a,int b)
{
	if(!b){x=1,y=0; return a;}
	int g=exgcd(y,x,b,a%b); y-=a/b*x; return g;
}
int b[110];
int main()
{
	int m,n,X; read(m);
	for(int i=1;i<=m;++i) read(b[i]);
	read(n),read(X);
	for(int i=2;i<=m;++i) D.a[i][i-1]=1;
	for(int i=1;i<=m;++i) D.a[i][m]=b[m-i+1];
	len=m;
	D=mpow(D,n-m);
	int xi=D.a[m][m],y=cal(3,X);
	
	// xi * x = y mod (mod-1)
	// xi * x + k(mod-1) = y
	
	int x1,y1,g=exgcd(x1,y1,xi,mod-1);
	if(y%g){puts("-1");return 0;}
	
	x1=x1%(mod-1)*(ll)(y/g%(mod-1))%(mod-1);
	x1=(x1+mod-1)%(mod-1);
	int ans=Pow(3,x1,mod);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Linge_Zzzz (赞：1)

# Sol

首先观察递推形式：

$$
f_1=f_2=\cdots=f_{k-1}=1\\
f_i=\prod_{j=1}^kf_{i-j}^{b_i}
$$

可得出 $f_i$ 能表示成 $f_k$ 的正整数次幂的形式，考虑求出这个指数是多少。

因为指数比较难处理，我们设 $r_i$ 满足 $f_i=f_k^{r_i}$，那么就转化为下面的式子：

$$
r_1=r_2=\cdots=r_{k-1}=0,r_k=1\\
r_i=\sum_{j=1}^kb_ir_{i-j}
$$

这显然是一个线性递推，我们使用矩阵快速幂求出 $r_n$，可得到 $f_k^{r_n}\equiv m\pmod{998244353}$。

这不是我们 $n$ 次剩余吗。$g=3$ 是 $p=998244353$ 的原根，设 $f_k=g^x$，于是有 $(g^{r_n})^x\equiv m\pmod{998244353}$。BSGS 解出 $x$ 后，$g^x$ 就是 $f_k$ 的解。

时间复杂度 $O(k^3\log n+\sqrt p)$。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define intl __int128
typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
const int N=1e9+10,K=110,INF=0x3f3f3f3f3f3f3f3f,mod=998244353,pmod=mod-1;
int k,b[K],n,m;
struct Mat{
	int a[K][K];
	Mat(){memset(a,0,sizeof(a));}
	int *operator[](int x){return a[x];}
};
Mat operator*(Mat &X,Mat &Y){
	Mat Z;
	for(int i=1;i<=k;i++)
		for(int j=1;j<=k;j++)
			for(int t=1;t<=k;t++)
				Z[i][j]=(Z[i][j]+X[i][t]*Y[t][j]%pmod)%pmod;
	return Z;
}
Mat qpow(Mat A,int p){
	Mat R=A;
	p--;
	while(p){
		if(p&1)R=R*A;
		A=A*A;
		p>>=1;
	}
	return R;
}
Mat A,T;
int qpow(int a,int p){
	int res=1;
	while(p){
		if(p&1)res=res*a%mod;
		a=a*a%mod;
		p>>=1;
	}
	return res;
}
int BSGS(int a,int n){
	unordered_map<int,int> s;
	int t=sqrt(mod)+1,k=qpow(a,t);
	for(int i=0,x=1;i<=t;i++,x=x*a%mod)s[x*n%mod]=i;
	int ans=-1;
	for(int i=1,x=k;i<=t;i++,x=x*k%mod){
		if(s.count(x)){
			if(i*t-s[x]==0)continue;
			ans=i*t-s[x];
			break;
		}
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>k;
	for(int i=1;i<=k;i++)cin>>b[i];
	cin>>n>>m;
	for(int i=1;i<k;i++)T[i+1][i]=1;
	for(int i=1;i<=k;i++)T[i][k]=b[k-i+1];
	A[1][k]=1;
	T=qpow(T,n-k);
	A=A*T;
	int p=A[1][k],g=3;
	int x=BSGS(qpow(3,p),m);
	if(x==-1){
		cout<<-1<<'\n';
	}else{
		cout<<qpow(g,x)<<'\n';
	}
	return 0;
}
```

---

## 作者：Fan_sheng (赞：1)

一道数论好题。

题目的式子带乘方，难以进行操作。然后又发现 $f_i<p$，想到用原根化幂为乘。

> 如果 $p$ 有原根 $g$，对 $\forall n<p\land\gcd(n,p)=1$，$n$ 可以表示为 $g^k\bmod p$。

$998244353$ 是质数，原根为 $3$，那么题目的式子就可以化为
$$
3^{T_i}\equiv\prod_{j=1}^k3^{T_{i-j}b_j}\pmod p
$$

根据欧拉定理 $a^b\equiv a^{b\bmod \varphi(p)}$，$p$ 为质数，有

$$
T_i\equiv\sum_{j=1}^kT_{i-j}b_j\pmod {p-1}
$$

发现这是一个递推式，如果知道 $T_k$，可以矩阵快速幂得到 $T_n$。

$$
\begin{bmatrix}
T_{i-k},T_{i-k+1},\cdots,T_{i-1}
\end{bmatrix}*
\begin{bmatrix}
&0,0,&\cdots,&0,0,&b_k\\
&1,0,&\cdots,&0,0,&b_{k-1}\\
&0,1,&\cdots,&0,0,&b_{k-2}\\
&\cdots,&\cdots,&\cdots,&\cdots\\
&0,0,&\cdots,&1,0,&b_2\\
&0,0,&\cdots,&0,1,&b_1\\
\end{bmatrix}=
\begin{bmatrix}
T_{i-k+1},T_{i-k+2},\cdots,T_i
\end{bmatrix}
$$

具体地，由于已知 $f_1=f_2=\cdots=f_{k-1}=1$，即 $T_1=T_2=\cdots=T_{k-1}=0$，如果设上式中那个 $k\times k$ 大小的转移矩阵为 $R$，我们有

$$
\begin{bmatrix}
0,0,\cdots,0,T_k
\end{bmatrix}*
R^{n-k}=
\begin{bmatrix}
T_{n-k+1},T_{n-k+2},\cdots,T_{n}
\end{bmatrix}
$$

也就是说，设 $R^{n-k}$ 右下角的值为 $r$，
$$
rT_k\equiv T_n\pmod {p-1}
$$
$$
3^{rT_k}\equiv 3^{T_n}\equiv m\pmod p
$$

就可以 BSGS 求解，得到 $rT_k\bmod p-1$ 的值，记作 $X$。（BSGS 求的是 $[1,p-1]$ 的最小整数解）

$$
rT_k\equiv X\pmod {p-1}
$$

最后使用 exgcd 求解线性同余方程，得到 $T_k$ 的一个特解，以及 $f_k=3^{T_k}$。

无解的情况：

- BSGS 无解。

- exgcd 无解。

Code
```cpp
#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
typedef long long ll;
ll n,m,k;
map<ll,ll>mp;
struct Matrix{
	ll a[103][103];
	friend Matrix operator *(Matrix a,Matrix b){
		Matrix c;
		memset(c.a,0,sizeof(c.a));
		for(ll i=1;i<=k;i++)
		for(ll j=1;j<=k;j++)
		for(ll p=1;p<=k;p++)c.a[i][j]=(c.a[i][j]+a.a[i][p]*b.a[p][j]%(mod-1))%(mod-1);
		return c;
	}
}base;
inline Matrix Matrix_quickpow(Matrix a,ll b){
	Matrix ans;
	for(ll i=1;i<=k;i++)
	for(ll j=1;j<=k;j++)ans.a[i][j]=(i==j);
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;b>>=1;
	}return ans;
}
inline ll quickpow(ll a,ll b){
	ll ans=1;a%=mod;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;b>>=1;
	}return ans;
}
inline ll BSGS(){
	ll len=ceil(sqrt(mod)),res=m;
	for(ll i=0;i<len;i++){
		mp[res]=i;
		res=res*3%mod;
	}
	ll ans=res=quickpow(3,len);
	for(ll i=1;i<=len;i++){
		if(mp[ans])return i*len-mp[ans];
		ans=ans*res%mod;
	}return -1;
}
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){x=1,y=0;return a;}
	ll res=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return res;
}
int main(){
	scanf("%lld",&k);
	for(ll i=1;i<k;i++)base.a[i+1][i]=1;
	for(ll i=1;i<=k;i++)scanf("%lld",&base.a[k-i+1][k]);
	scanf("%lld%lld",&n,&m);
	ll tmp=BSGS(),x,y,d;
	if(tmp<0)printf("-1"),exit(0);
	d=exgcd(Matrix_quickpow(base,n-k).a[k][k],mod-1,x,y);
	if(tmp%d)printf("-1"),exit(0);
	x=(__int128)x*tmp/d%(mod-1);
	printf("%lld",quickpow(3,(x+mod-1)%(mod-1)));return 0;
}
```


---

## 作者：SuperTNT (赞：1)

# CF1106 Lunar New Year and a Recursive Sequence [题解]

> ## 题目
>
> 给出式子$f_i=\prod\limits_{j=1}^k f_{i-j}^{b_j} \pmod {998244353}$，给出$f_n=m$，求$f_k$最小正整数值，为了方便起见我们将$998244353$定义为$p$
>
> ## 思路
>
> 一眼看上去似乎从$f_n$推是不可行的，通过手模几组小样例可以发现$f_n$只与$f_k$的指数级有关，所以我们思考从$f_k$转移到$f_n$，用一个函数来表示$f_k$的指数，我们设$g(n)$表示第$n$项为$f_k^{g_n}$，则$f_n=f_k^{g_n}$，$g_n=g_{n-1}b_1+g_{n-2}b_2+\cdots+g_{n-k}b_k$，我们不难发现这是个递推式子，我们可以将其用矩阵递推来优化
>
> 我们可以定义矩阵$\begin{bmatrix}g_{n-k},g_{n-k+1},\cdots ,g_{n}\end{bmatrix}$
>
> $\begin{bmatrix}g_{n-k},g_{n-k+1},\cdots ,g_{n}\end{bmatrix} \times A= \begin{bmatrix}g_{n-k+1},g_{n-k+2},\cdots ,g_{n+1}\end{bmatrix}$
>
> 设后面一项矩阵为$C$，前面一项矩阵为$B$
>
> $A$是单位矩阵，接下来我们求单位矩阵，根据矩阵定义$C_{i,j}=\sum\limits_{i=1}^m A_{i,k}B_{k,j}$，
>
> 我们想要得出$g_{n+1}$,我们必须要使矩阵第$k$列为
> $$
> \left[
>  \begin{matrix}
>    \cdots & \cdots & \cdots & \cdots & b_k\\
>    \vdots & \vdots & \vdots & \vdots & b_{k-1} \\
>    \vdots & \vdots& \vdots & \vdots & \vdots \\
>    \cdots & \cdots & \cdots & \cdots & b_1
>   \end{matrix} 
> \right]
> $$
> 由此递推出其他位置应该为
> $$
> \left[
>  \begin{matrix}
>    0 & 0 & \cdots & 0 & b_k\\
>    1 & 0& \cdots & 0 & b_{k-1} \\
>    0 & 1& \cdots & \cdots & b_{k-2}\\
>    \vdots & \vdots & \ddots & \cdots & \vdots\\
>    0 & 0 & \cdots & 1 & b_1
>   \end{matrix} 
> \right]
> $$
> 由题意可知，初始矩阵：$B=\begin{bmatrix}0,0,\cdots ,1\end{bmatrix}$
>
> 那么$ g_n=C_{1,k}=B\times A^{n-k}$
>
> 我们可以发现给出的模数是个质数，因此在计算矩阵乘法时我们可以使用欧拉定理给每次的数模$p-1$就行了
>
> 现在我们知道$f_n=m=f_k^{g_n} \pmod p$，可以转化为$x^a\equiv m \pmod p$，我们只有$x$不知道，可以看出该式可以用原根和$BSGS$来求，$p$的原根是$3$我们可以先自己写个程序求出来（~~当然某些大佬已经背住1e9数的原根了~~)，可以将$x$转化为$3^{sa} \equiv m \pmod p$，因为$3$与$p$互质，因此可以用欧拉定理先求出$sa \% (p-1)$，我们知道$a \% (p-1)$的值，只要知道$s$的逆元即可，此处注意$p-1$并不是质数，因此要用$exgcd$来求逆元，这样就知道$s$的值了
>
> 复杂度$O(k^3\log n+\sqrt {mod} +\log n)$
>
> ## 代码
>
> ```c++
> #include <bits/stdc++.h>
> 
> #define re register
> 
> #define ll long long
> 
> namespace TNT
> {
>  const int mod = 998244353;
>  const int MAXN = 110;
> 
>  int k, n, m;
> 
>  inline int read()
>  {
>      int x = 0;
>      char ch = getchar();
>      while (ch < '0' || ch > '9')
>          ch = getchar();
>      while (ch >= '0' && ch <= '9')
>      {
>          x = x * 10 + ch - '0';
>          ch = getchar();
>      }
>      return x;
>  }
> 
>  struct array
>  {
>      int ar[MAXN][MAXN];
>      int x, y;
>  } a, asum, s;
> 
>  array operator*(array x, array y)
>  {
>      array c;
>      c.x = x.x;
>      c.y = y.y;
>      for (re int i = 1; i <= x.x; i++)
>          for (re int j = 1; j <= y.y; j++)
>          {
>              c.ar[i][j] = 0;
>              for (re int z = 1; z <= x.y; z++)
>                  c.ar[i][j] = 1ll * (1ll * c.ar[i][j] + 1ll * x.ar[i][z] * y.ar[z][j]) % (mod - 1);
>          }
>      return c;
>  }
> 
>  inline array qpow(array x, int y)
>  {
>      array ans = x;
>      y--;
>      while (y)
>      {
>          if (y & 1)
>              ans = ans * x;
>          x = x * x;
>          y >>= 1;
>      }
>      return ans;
>  }
> 
>  inline int power(int x, int y)
>  {
>      int ans = 1;
>      while (y)
>      {
>          if (y & 1)
>              ans = 1ll * ans * x % mod;
>          x = 1ll * x * x % mod;
>          y >>= 1;
>      }
>      return ans;
>  }
> 
>  int exgcd(int a, int b, ll &x, ll &y)
>  {
>      if (!b)
>      {
>          x = 1, y = 0;
>          return a;
>      }
> 
>      int d = exgcd(b, a % b, x, y);
>      int g = x;
>      x = y;
>      y = g - a / b * y;
> 
>      return d;
>  }
> 
>  std::map<int, int> hs;
> 
>  inline int BSGS(int G)
>  {
>      m %= mod;
>      int t = sqrt(mod) + 1,tmp = m % mod;
> 
>      hs[tmp] = 0;
>      for (int i = 1; i < t; i++)
>      {
>          tmp = 1ll * tmp * G % mod;
>          hs[tmp] = i;
>      }
> 
>      G = power(G, t);
> 
>      if (!G)
>      {
>          if (!m)
>              return 1;
>          else
>              return -1;
>      }
> 
>      tmp = 1;
>      if(hs.find(tmp) != hs.end())
>          return 0;
> 
>      for (int i = 1; i <= t; i++)
>      {
>          tmp = 1ll * tmp * G % mod;
>          if(hs.find(tmp) != hs.end())
>              return i * t - hs[tmp];
>      }
>      return -1;
>  }
> 
>  inline void main()
>  {
>      k = read();
>      s.x = 1;
>      a.x = a.y = s.y = k;
>      s.ar[1][k] = 1;
> 
>      for (re int i = 2; i <= k; i++)
>          a.ar[i][i - 1] = 1;
> 
>      for (re int i = k; i >= 1; i--)
>          a.ar[i][k] = read();
> 
>      n = read(), m = read();
> 
>      asum = s * qpow(a, n - k);
> 
>      int t = BSGS(3);
> 
>      ll x, y;
> 
>      int d = exgcd(asum.ar[1][k], mod - 1, x, y);
> 
>      if (t % d)
>          puts("-1");
>      else
>      {
>          x = (t / d * x % (mod - 1) + mod - 1) % (mod - 1);
>          printf("%d\n", power(3, x));
>      }
>      return;
>  }
> }
> 
> int main()
> {
>  TNT::main();
>  return 0;
> }
> ```
>
> 



---

## 作者：__ycx2010__ (赞：0)

## Solution

考虑将乘方换成乘法的形式，由于 $998244353$ 存在一个原根 $G = 3$，所以每一个 $[1,P)$ 范围内的整数都可以用 $3$ 的非负整数次幂表示。

设 $f_i \equiv G^{g_i} (\bmod\space 998244353)$，那么有关于 $g$ 的转移方程：

$$g_i = \sum_{j = 1}^k g_{i-j}b_j$$

于是可以列出上式转移时的矩阵形式：

$$
A = \begin{bmatrix}
 0 & 0 & \cdots &0 & 0 & b_k\\
 1 & 0 &\cdots & 0 & 0 & b_{k-1}\\
 0 & 1 & \cdots &0 & 0 & b_{k-2}\\
\vdots & \vdots & \ddots & \vdots & \vdots & \vdots & \\
 0 & 0 & \cdots & 1 & 0 & b_2\\
 0 & 0 & \cdots & 0 & 1 & b_1
\end{bmatrix}
$$

则有

$\begin{bmatrix}
 g_1 &g_2 & \cdots  & g_k
\end{bmatrix} A^{n - k} = \begin{bmatrix}
 g_{n-k+1} & \cdots & g_{n-1} & g_n
\end{bmatrix}$

$g_n$ 的值可以用 BSGS 在 $O(\sqrt{p})$ 的复杂度内求出。

我们可以先使用矩阵快速幂求出 $A^{n-k}$，因为 $g_{1\sim k-1} = 0$，所以有同余式：

$$g_k (A^{n-k})_{k,k} \equiv g_n (\bmod\space 998244352)$$

那么接下来就可以用 exgcd 求出 $g_k$，答案为 $G^{g_k}$。

时间复杂度为 $O(k^3\log n + \sqrt{p})$ 。

## Code

```
#include <bits/stdc++.h>
using namespace std;

const int P = 998244353;
int n, m, k;

struct Matrix {
	int a[110][110];
	void init() {
		for (int i = 0; i < k; i ++ )
			for (int j = 0; j < k; j ++ )
				a[i][j] = 0;
	}
	Matrix operator * (const Matrix &b) const {
		Matrix c;
		c.init();
		for (int i = 0; i < k; i ++ )
			for (int j = 0; j < k; j ++ )
				for (int kk = 0; kk < k; kk ++ )
					c.a[i][j] = (c.a[i][j] + 1ll * a[i][kk] * b.a[kk][j] % (P - 1)) % (P - 1);
		return c;
	}
};

Matrix qpow(Matrix T, int x) {
	Matrix G = T;
	x -- ;
	while (x) {
		if (x & 1) G = G * T;
		T = T * T;
		x >>= 1;
	}
	return G;
}

int qpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1ll * res * a % P;
		a = 1ll * a * a % P;
		b >>= 1;
	}
	return res;
}

int exgcd(int a, int b, int &x, int &y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

int BSGS(int a, int b, int p) {
	int t = (int)sqrt(p) + 1, cur = 1, nw = 1;
	map<int, int> hash;
	for (int i = 1; i <= t; i ++ ) {
		cur = 1ll * cur * a % p;
		hash[1ll * b * cur % p] = i;
	}
	for (int i = 1; i <= t; i ++ ) {
		nw = 1ll * nw * cur % p;
		if (hash[nw]) return i * t - hash[nw];
	}
	return -1;
}

signed main() {
	scanf("%d", &k);
	vector<int> b(k);
	for (int i = 0; i < k; i ++ ) scanf("%d", &b[i]);
	scanf("%d%d", &n, &m);
	Matrix A;
	for (int i = 0; i < k; i ++ )
		for (int j = 0; j < k; j ++ )
			if (j == k - 1) A.a[i][j] = b[k - i - 1];
			else if (i == j + 1) A.a[i][j] = 1;
			else A.a[i][j] = 0;
	A = qpow(A, n - k);
	int x, y, d;
	int lm = BSGS(3, m, P);
	d = exgcd(A.a[k - 1][k - 1], P - 1, x, y);
	if (lm % d != 0) puts("-1");
	else printf("%d", qpow(3, (1ll * x * lm / d % (P - 1) + P - 1) % (P - 1)));
	return 0;
}
```

---

## 作者：Memory_of_winter (赞：0)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/10345347.html)

### 题目大意

有一串$n(n\leqslant10^9)$个数的数列，给你$b_1\sim b_k(k\leqslant100)$。当$i>k$时：
$$f_i=(\prod\limits_{i=1}^kf_{i-j}^{b_i})\bmod{998244353}$$
已知$f_1=f_2=\cdots=f_{k-1}=1,f_n=m$，问最小的正整数$f_k$可能是多少

谁可以告诉我为什么我交翻译的时候LATEX全部出锅了？

### 题解

写一下式子，发现可以用矩阵快速幂求出$f_n=f_k^x\bmod{998244353}$中的$x$（幸好这道题不需要线性齐次递推，不然玩完），复杂度$O(k^3\log_2n)$。

接下来就是求$f_k^x\equiv m\pmod{998244353}$
$$\begin{aligned}x\ln(f_k)\equiv\ln(m)\pmod{\varphi(998244353)}\\\ln(f_k)\equiv\ln(m)x^{-1}\pmod{998244352}\\f_k\equiv\exp(\ln(m)x^{-1})\pmod{998244353}\end{aligned}$$

但是$x$在$\pmod{998244352}$下可能没有逆元，怎么办呢？可以用$exgcd$求出$\dfrac{\gcd(x,998244352)}x$，然后把$\ln(m)$除掉$\gcd(x,998244352)$，若有余数则无解。

### 卡点

比赛结束后$5min$发现可以除掉$\gcd$来做，然后自闭



### C++ Code：

```cpp
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <set>
const int mod = 998244353, __mod = mod - 1;
#define maxn 105

int Tim, n, m, k;
int b[maxn];
struct Matrix {
	int s[maxn][maxn];
	inline Matrix operator * (const Matrix &rhs) const {
		Matrix res;
		for (int i = 0; i < k; ++i) {
			for (int j = 0; j < k; ++j) {
				long long t = 0;
				for (int l = 0; l < k; ++l) (t += static_cast<long long> (s[i][l]) * rhs.s[l][j]) %= __mod;
				res.s[i][j] = t;
			}
		}
		return res;
	}
} base, res;

namespace Math {
	std::map<int, int> mp;
	bool init = false;
	long long BSGS(long long y, long long z) {
		y %= mod, z %= mod;
		if (!y) return -1;
		long long tmp = 1, t = sqrt(mod - 1) + 1;
		if (!init) {
			mp.clear();
			for (int i = 0; i <= t; i++) {
				mp[tmp * z % mod] = i;
				if (i != t) tmp = tmp * y % mod;
			}
			init = true;
		}
		long long tmp6 = tmp;
		for (int i = 1; i <= t; i++) {
			if (mp.count(tmp6)) return i * t - mp[tmp6];
			tmp6 = tmp6 * tmp % mod;
		}
		return -1;
	}

	inline int pw(int base, int p) {
		static int res;
		for (res = 1; p; p >>= 1, base = static_cast<long long> (base) * base % mod) if (p & 1) res = static_cast<long long> (res) * base % mod;
		return res;
	}

	long long exgcd(long long a, long long b, long long &x, long long &y) {
		if (!b) {
			x = 1, y = 0;
			return a;
		}
		long long t = exgcd(b, a % b, y, x);
		y -= a / b * x;
		return t;
	}
	long long retgcd;
	long long inv(long long a) {
		long long x, y;
		retgcd = exgcd(a, __mod, x, y);
		return (x % __mod + __mod) % __mod;
	}
}

int main() {
	std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
	std::cin >> k;
	for (int i = 0; i < k; ++i) std::cin >> base.s[i][0];
	for (int i = 1; i < k; ++i) base.s[i - 1][i] = 1;
	res.s[0][0] = 1;
	std::cin >> n >> m;
	for (n -= k; n; n >>= 1, base = base * base) if (n & 1) res = res * base;
	const long long y = res.s[0][0];
	long long lnz = Math::BSGS(3, m);
	long long t = Math::inv(y);
	if (lnz % Math::retgcd) {
		puts("-1");
		return 0;
	}
	lnz = lnz / Math::retgcd * t % __mod;
	std::cout << Math::pw(3, lnz) << '\n';
	return 0;
}

```

---

