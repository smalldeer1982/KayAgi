# The Three Little Pigs

## 题目描述

Three little pigs from all over the world are meeting for a convention! Every minute, a triple of 3 new pigs arrives on the convention floor. After the $ n $ -th minute, the convention ends.

The big bad wolf has learned about this convention, and he has an attack plan. At some minute in the convention, he will arrive and eat exactly $ x $ pigs. Then he will get away.

The wolf wants Gregor to help him figure out the number of possible attack plans that involve eating exactly $ x $ pigs for various values of $ x $ ( $ 1 \le x \le 3n $ ). Two attack plans are considered different, if they occur at different times or if the sets of little pigs to eat are different.

Note that all queries are independent, that is, the wolf does not eat the little pigs, he only makes plans!

## 说明/提示

In the example test, $ n=2 $ . Thus, there are $ 3 $ pigs at minute $ 1 $ , and $ 6 $ pigs at minute $ 2 $ . There are three queries: $ x=1 $ , $ x=5 $ , and $ x=6 $ .

If the wolf wants to eat $ 1 $ pig, he can do so in $ 3+6=9 $ possible attack plans, depending on whether he arrives at minute $ 1 $ or $ 2 $ .

If the wolf wants to eat $ 5 $ pigs, the wolf cannot arrive at minute $ 1 $ , since there aren't enough pigs at that time. Therefore, the wolf has to arrive at minute $ 2 $ , and there are $ 6 $ possible attack plans.

If the wolf wants to eat $ 6 $ pigs, his only plan is to arrive at the end of the convention and devour everybody.

Remember to output your answers modulo $ 10^9+7 $ !

## 样例 #1

### 输入

```
2 3
1
5
6```

### 输出

```
9
6
1```

## 样例 #2

### 输入

```
5 4
2
4
6
8```

### 输出

```
225
2001
6014
6939```

# 题解

## 作者：pigstd (赞：22)

考虑对于所有的 $x$ 求出答案，考虑答案的生成函数。

显然 $\dbinom{3j}{i}=[x^i](1+x)^{3j}$，那么有 $\displaystyle ans_i=\sum_{j=1}^n\dbinom{3j}{i}=[x^i]\sum_{i=1}^n(1+x)^{3i}=[x^i]\frac {(x+1)^{3n+3}-(x+1)^3}{(x+1)^3-1}$。

好难啊 $3\times 10^6$ 跑 MTT 跑个锤子（赛时真实想法）。

学多项式学魔怔了，直接大除法即可。

[code](https://codeforces.com/contest/1549/submission/124578681)。

---

## 作者：Doubeecat (赞：10)

> 给定一个 $n$ 和 $q$，有 $q$ 次询问，每次询问给定一个 $x$。
>
> 要求你求出 $\sum\limits_{i =1}^{n} \binom{3i}{x}$
>
> $1 \leq n \leq 10^6,1 \leq q \leq 2\times 10^5,x \leq 3n$

~~感谢学弟让我这只千年大鸽子第一次有如此热情熬夜赶工~~

首先观察题目这个式子，我们发现，实际上因为是  $3i$ ，我们可以分成三类来计算：$3i,3i+1,3i+2$ 这样会方便我们的思考。

自然的，直接求和如果没有一些科技是不太现实的，我们考虑 DP。

设 $f_{i,k}$ 表示 $\sum\limits_{i = 0}^{n-1}\binom{3i + k}{x}$ ，这样定义的好处在于，我们发现答案可以直接表示为  $\binom{3n}{x} + f_{n-1,0}$.

接下来我们考虑怎么计算 $f_{x,k}$，我们回想一下有组合恒等式 
$$
\displaystyle{ \sum^n_{i=r}{i\choose r}={n+1\choose r+1} }
$$

也就是说，有
$$
\displaystyle{ \sum^{3n-1}_{i=0}{i\choose x}= \sum\limits_{i = 0}^{n-1}\binom{3i}{x} + \sum\limits_{i = 0}^{n-1}\binom{3i + 1}{x} + \sum\limits_{i = 0}^{n-1}\binom{3i + 2}{x} = {3n\choose x+1} }
$$
变成我们刚才的定义就得到了一个优美的式子
$$
\displaystyle{f_{i,0} + f_{i,1} + f_{i,2} = {3i\choose x+1}}
$$
我们得到了一个关系式，但是这远远不够，我们需要发掘更多性质。

由帕斯卡公式 $\binom{n-1}{m}+\binom{n-1}{m-1} = \binom{n}{m}$ 我们可以得到
$$
\sum_{i=0}^{n-1} {3i \choose x} + \sum_{i=0}^{n-1} {3i \choose x-1} = \sum_{i=0}^{n-1} {3i+1 \choose x}
$$
我们可以将 $i = 0,1$ 带入，得到下面两个式子

$$
f_{i,1} = f_{i-1,0} + f_{i,0} \\
f_{i,2} = f_{i-1,1} + f_{i,1}
$$

至此，我们发现上面的三个式子组成了一个三元一次方程组，此时我们可以换元，尝试解出 $f_{i,0}$ 直接的递推式。

把后面两个式子都代回第一个式子中易得

$$
3f_{i,0}={3i\choose x+1} - 2f_{i-1,0} - f_{i-1,1} \\
f_{i,0} = \frac{{3i\choose x+1} - 2f_{i-1,0} - f_{i-1,1}} {3}
$$

所以，我们就得到了总的递推公式：
$$
\left\{
	\begin{aligned} 
	f_{i,0} &= \frac{{3i\choose x+1} - 2f_{i-1,0} - f_{i-1,1}} {3} \\
	f_{i,1} &= f_{i-1,0} + f_{i,0} \\
	f_{i,2} &= f_{i-1,1} + f_{i,1}
	\end{aligned}
\right.
$$


边界条件为 $f_{0,0} = f_{0,1} = f_{0,2} = n$

对于 $1$ 到 $3n$ 的 $f_{i,0/1/2}$ 预处理一遍，注意需要使用线性求逆元，否则可能被卡常，时间复杂度 $O(n+q)$

---

## 作者：Aestas16 (赞：6)

记 $f_{i, j}\ (0 \le j \le 2)$ 为 $\sum^{n - 1}_{i = 0} \binom{3i + m}{x}$ 的值，则对于一个询问 $x$，答案为 $f_{x, 0} + \binom{3n}{x}$。

那么显然有：
- $f_{i, 0} + f_{i, 1} + f_{i, 2} = \binom{3n}{i + 1}$。
- $f_{i, 1} = f_{i, 0} + f_{i - 1, 0}$。
- $f_{i, 2} = f_{i, 1} + f_{i - 1, 1}$。
- 边界条件 $f_{0, 0} = f_{0, 1} = f_{0, 2} = n$。

根据上述式子预处理递推求出 $f$ 即可，时间复杂度 $\Theta(n + q)$。

代码很简单就不放了。

---

## 作者：Prean (赞：2)

数学好久没碰已经不会 GF 咯！

在这里提供一个单反做法。
$$\sum_{i=0}^{n}\binom{i}{m}[3\mid i]$$
$$\sum_{i=0}^{n}\binom{i}{m}\frac{1}{3}\sum_{j=0}^{2}w_3^{ij}$$
$$\frac{1}{3}\sum_{j=0}^{2}\sum_{i=0}^{n}\binom{i}{m}(w_3^j)^i$$
$$F_j[m]=\sum_{i=0}^{n}\binom{i}{m}(w_3^j)^i$$
$$F_j[m]=\sum_{i=0}^{n}(\binom{i-1}{m}+\binom{i-1}{m-1})(w_3^j)^i$$
$$F_j[m]=w_3^j(\sum_{i=0}^{n-1}\binom{i}{m}(w_3^j)^i+\sum_{i=0}^{n-1}\binom{i}{m-1}(w_3^j)^i)$$
$$F_j[m]=w_3^j(F_j[m]-\binom{n}{m}w_3^{nj}+F_j[m-1]-\binom{n}{m-1}w_3^{nj})$$
$$F_j[m]=w_3^j(F_j[m]+F_j[m-1]-\binom{n+1}{m}w_3^{nj})$$
$$F_j[m]=\frac{w_3^jF_j[m-1]-\binom{n+1}{m}w_3^{(n+1)j}}{1-w_3^j}$$
根据题意这里有 $3\mid n$。
$$F_j[m]=\frac{w_3^jF_j[m-1]-\binom{n+1}{m}w_3^j}{1-w_3^j}$$
$$F_j[m]=\frac{w_3^j}{1-w_3^j}\times(F_j[m-1]-\binom{n+1}{m})$$
记 $w_3^0=1,w_3^1=x,w_3^2=x^2$，然后将单位根看做多项式做长度为 $3$ 的循环卷积即可。（这里 $x=\frac{\sqrt{3}i-1}{2},x^2=\frac{-\sqrt{3}i-1}{2}$）

求逆元？

你可以手搓逆元，但是得根据 $x$ 的意义来搓。

也就是说不可能凑出来 $1+0x+0x^2$，只能凑出来 $a+bx+cx^2$ 满足 $a-\frac{b+c}{2}=1$ 且 $b=c$。

设 $(1-x)\times(t_0+t_1x+t_2x^2)=a+bx+bx^2$。

其实只需要凑出来 $b=c$ 就行了。。。第一个限制可以通过除以一个常数来解决。

那么就是 $a=t_0-t_2,b=t_1-t_0=t_2-t_1$

~~只需要满足 $2\times a\neq b+c$ 就行了~~

$b+c=t_2-t_0$，保证 $t_2\neq t_0$ 就可以了。。。

可以得到一组解是 $t_0=0,t_1=1,t_2=2$。

此时 $(1-x)(x+2x^2)=-2+x+x^2,a-\frac{b+c}{2}=-3$

所以逆元是 $-\frac{1}{3}x-\frac{2}{3}x^2$。

同理可得 $-\frac{2}{3}x-\frac{1}{3}x^2$ 是 $1-x^2$ 的逆元。

复杂度 $O(n3^3)$，应该是可以过去的。~~需要注意 $j=0$ 的时候 $F$ 的值是一个组合数~~

听说好像有 $O(n3^2)$ 的简单 GF 做法。果然还是我太菜了。
$$ans_x=\frac{F_0[x]+F_1[x]+F_2[x]}{3}$$
```cpp
#include<cstdio>
typedef unsigned ui;
typedef unsigned long long ull;
const ui M=3e6+5,inv3=333333336,mod=1e9+7;
ui n,q,F0[M],fac[M],ifac[M];
struct poly{
	ui f0,f1,f2;
	poly(const ui&f0=0,const ui&f1=0,const ui&f2=0):f0(f0),f1(f1),f2(f2){}
	inline ui&operator[](const ui&x){
		return x==0?f0:x==1?f1:f2;
	}
	inline poly operator*(const ui&x)const{
		return poly(1ull*f0*x%mod,1ull*f1*x%mod,1ull*f2*x%mod);
	}
	inline poly operator+(const poly&g)const{
		return poly((f0+g.f0)%mod,(f1+g.f1)%mod,(f2+g.f2)%mod);
	}
	inline poly operator-(const poly&g)const{
		return poly((f0+mod-g.f0)%mod,(f1+mod-g.f1)%mod,(f2+mod-g.f2)%mod);
	}
	inline poly operator*(poly g){
		ull ans[3];ans[0]=ans[1]=ans[2]=0;
		for(ui i=0;i^3;++i)for(ui j=0;j^3;++j)ans[i+j>=3?i+j-3:i+j]+=1ull*(*this)[i]*g[j];
		return poly(ans[0]%mod,ans[1]%mod,ans[2]%mod);
	}
}c,F1[M],F2[M];
inline ui C(const ui&n,const ui&m){
	return 1ull*ifac[m]*ifac[n-m]%mod*fac[n]%mod;
}
inline poly pow(poly a,ull b){
	poly ans(1);for(;b;b>>=1,a=a*a)if(b&1)ans=ans*a;return ans;
}
inline ui pow(ui a,ui b){
	ui ans(1);for(;b;b>>=1,a=1ull*a*a%mod)if(b&1)ans=1ull*ans*a%mod;return ans;
}
signed main(){
	scanf("%u%u",&n,&q);n*=3;fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(ui i=2;i<=n+1;++i)fac[i]=1ull*fac[i-1]*i%mod,ifac[i]=1ull*(mod-mod/i)*ifac[mod%i]%mod;
	for(ui i=2;i<=n+1;++i)ifac[i]=1ull*ifac[i]*ifac[i-1]%mod;
	for(ui i=0;i<=n;++i)F0[i]=C(n+1,i+1);
	c=poly(0,1,0)*poly(0,mod-inv3,(mod-2ull)*inv3%mod);
	F1[0]=poly(1,0,0);for(ui i=1;i<=n;++i)F1[i]=c*(F1[i-1]-C(n+1,i));
	c=poly(0,0,1)*poly(0,(mod-2ull)*inv3%mod,mod-inv3);
	F2[0]=poly(1,0,0);for(ui i=1;i<=n;++i)F2[i]=c*(F2[i-1]-C(n+1,i));
	while(q--){
		ui x;scanf("%u",&x);
		poly ans=poly(F0[x])+F1[x]+F2[x];
		printf("%u\n",(ans.f0+500000003ull*(ans.f1+ans.f2))%mod*inv3%mod);
	}
}
```

---

## 作者：rui_er (赞：2)

萌新的第一场 div1 肯定要发篇题解纪念一下（）

貌似我的做法跟官方题解两种和目前所有题解都不一样/fad

首先观察到题目显然是让我们求 $\sum\limits_{i=1}^n\binom{3i}{x}$，考虑能不能预处理。

根据组合数性质列出如下式子：

当 $x=1$ 时，答案为 $3,6,9,\cdots$（暂且称为式子 $1-1$）。

类似地列出两个不是答案的式子 $2,5,8,\cdots$（式子 $1-2$）和 $1,4,7,\cdots$（式子 $1-3$）。

也就是说，式子 $x-1$ 是由无穷多个 $\binom{3i}{x}$ 组成的，$x-2$ 和 $x-3$ 是由无穷多个 $\binom{3i-1}{x}$ 和 $\binom{3i-2}{x}$ 组成的。

继续写 $x=2,3,\cdots$ 可以得到下表：

|式子编号|式子|
|:-:|:-:|
|$1-1$|$3,6,9,\cdots$|
|$1-2$|$2,5,8,\cdots$|
|$1-3$|$1,4,7,\cdots$|
|$2-1$|$3\times 2,6\times 5,9\times 8,\cdots$|
|$2-2$|$2\times 1,5\times 4,8\times 7,\cdots$|
|$2-3$|$0,4\times 3,7\times 6,\cdots$|
|$3-1$|$3\times 2\times 1,6\times 5\times 4,9\times 8\times 7,\cdots$|
|$3-2$|$0,5\times 4\times 3,8\times 7\times 6,\cdots$|
|$3-3$|$0,4\times 3\times 2,7\times 6\times 5,\cdots$|

列出这么多已经足够了，考虑如何进行递推。

我们容易观察到 $x-1$ （是式子编号，下同）减去 $x-2$ 的结果恰好是 $(x-1)-2$ 的整数倍，$x-2$ 减去 $x-3$ 的结果恰好是 $(x-1)-3$ 的整数倍。前者的最后几项与后者的前几项是相同的，将它们用分配率提取出来可以得到递推式，因此所有的 $x-2$ 和 $x-3$ 式子都能求了。再根据他们计算所有的 $x-1$ 式子即可。

初始状态显然在 $i\in[1,n]$ 的限制下，$1-1,1-2,1-3$ 式子的和分别是 $\frac{3n+3}{2},\frac{3n+1}{2},\frac{3n-1}{2}$。

输出答案时不要忘了乘以一个 $(x!)^{-1}$。

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
using namespace std;
typedef long long ll;
const ll N = 7e6+5, mod = 1e9+7;

ll n, q, fac[N], inv[N], facinv[N], ans[N];
template<typename T> void chkmin(T &x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T &x, T y) {if(x < y) x = y;}
void initC(ll lim) {
	fac[0] = inv[0] = facinv[0] = 1;
	fac[1] = inv[1] = facinv[1] = 1;
	rep(i, 2, lim) {
		fac[i] = fac[i-1] * i % mod;
		inv[i] = (mod - mod / i) * inv[mod%i] % mod;
		facinv[i] = (mod - mod / i) * facinv[mod%i] % mod;
	}
	rep(i, 2, lim) facinv[i] = facinv[i-1] * facinv[i] % mod;
}

int main() {
	scanf("%lld", &n);
	initC(3*n+1);
	ll qwq = 0, qaq = 0;
	qwq = (3 * n - 1) % mod * n % mod * inv[2] % mod;
	qaq = (3 * n + 1) % mod * n % mod * inv[2] % mod;
	ans[1] = (3 * n + 3) % mod * n % mod * inv[2] % mod;
	rep(i, 2, 3*n) {
		ll diff1 = qwq * i % mod;
		ll diff2 = qaq * i % mod;
		ll total = fac[3*n+1] * facinv[3*n-i] % mod * inv[i+1] % mod;
		ll tmp = (2 * diff1 % mod + diff2) % mod;
		qwq = (total + mod - tmp) % mod * inv[3] % mod;
		qaq = (qwq + diff1) % mod;
		ans[i] = (qaq + diff2) % mod * facinv[i] % mod;
	}
	for(scanf("%lld", &q);q;q--) {
		ll x;
		scanf("%lld", &x);
		printf("%lld\n", ans[x]);
	}
	return 0;
}
```

---

## 作者：registerGen (赞：2)

题目相当于让我们求：

$$\sum_{i=0}^n\binom{3i}x$$

考虑用 dp 求出这个式子。设：

$$f_{x,j}=\sum_{i=0}^n\binom{3i+j}x,0\le j\le 2$$

那么答案就是 $f_{x,0}$。

我们运用公式 $\binom nm=\binom{n-1}m+\binom{n-1}{m-1}$，可以推出 $f_{x,1},f_{x,2}$ 的转移方程：

$$f_{x,j}=\sum_{i=0}^n\binom{3i+j}x=\sum_{i=0}^n\binom{3i+j-1}x+\sum_{i=0}^n\binom{3i+j-1}{x-1}=f_{x,j-1}+f_{x-1,j-1},1\le j\le 2$$

我们运用公式 $\sum_{i=0}^n\binom ix=\binom{n+1}{x+1}$，可以推出 $f_{x,0}$ 的转移方程：

$$f_{x,0}=(f_{x,0}+f_{x,1}+f_{x,2})-f_{x,1}-f_{x,2}=\sum_{i=0}^{3n+2}\binom ix-f_{x,1}-f_{x,2}=\binom{3n+3}{x+1}-f_{x,1}-f_{x,2}$$

于是，我们得到了一个方程组：

$$
\begin{cases}
f_{x,0}=\binom{3n+3}{x+1}-f_{x,1}-f_{x,2}\\
f_{x,1}=f_{x,0}+f_{x-1,0}\\
f_{x,2}=f_{x,1}+f_{x-1,1}
\end{cases}
$$

解得：

$$
\begin{cases}
f_{x,0}=\dfrac{\binom{3n+3}{x+1}-2f_{x-1,0}-f_{x-1,1}}{3}\\
f_{x,1}=f_{x,0}+f_{x-1,0}\\
f_{x,2}=f_{x,1}+f_{x-1,1}
\end{cases}
$$

边界：$f_{0,0}=f_{0,1}=f_{0,2}=n+1$。

```cpp
typedef long long ll;

const int N=1e6;
const int P=1e9+7;

int n,m,f[N*3+10][3];
int fac[N*3+10],ifac[N*3+10];

inline int qpow(int a,int b,int p){
	int res=1;
	while(b){if(b&1)res=1LL*res*a%p;a=1LL*a*a%p;b>>=1;}
	return res;
}

inline int inv(int a,int p){return qpow(a,p-2,p);}

void initComb(int p){
	int lim=std::min(n*3+5,p-1);
	fac[0]=1;for(int i=1;i<=lim;i++)fac[i]=1LL*fac[i-1]*i%p;
	ifac[lim]=inv(fac[lim],p);for(int i=lim-1;i>=0;i--)ifac[i]=1LL*ifac[i+1]*(i+1)%p;
}

inline int C(int a,int b,int p){if(a<b)return 0;else return 1LL*fac[a]*ifac[b]%p*ifac[a-b]%p;}

void mian(){
	scanf("%d%d",&n,&m);
	initComb(P);
	f[0][0]=f[0][1]=f[0][2]=n+1;
	int inv3=inv(3,P);
	for(int i=1;i<=n*3;i++){
		f[i][0]=1LL*(((C(3*n+3,i+1,P)-2*f[i-1][0]%P-f[i-1][1])%P+P)%P)*inv3%P;
		f[i][1]=(f[i][0]+f[i-1][0])%P;
		f[i][2]=(f[i][1]+f[i-1][1])%P;
	}
	while(m--){
		int x;scanf("%d",&x);
		printf("%d\n",f[x][0]);
	}
}
```

---

## 作者：littleKtian (赞：2)

简单生成函数练习题（？）。

------------
为了方便描述，文中所有的 $t$ 表示每次询问的数，以防和生成函数中的 $x$ 搞混。

------------

题意即对于所有询问的 $t$，求 $\sum\limits_{i=1}^n\dbinom{3i}{t}$。

转换成生成函数的形式，那么上式就变成了 $\left[x^t\right]\sum\limits_{i=1}^n\left(1+x\right)^{3i}$。

记 $F(x)=\sum\limits_{i=1}^n\left(1+x\right)^{3i}$，由等比数列公式易知 $F(x)=\dfrac{(1+x)^3-(1+x)^{3(n+1)}}{1-(1+x)^3}$。

式子上面直接用组合数公式可以 $O(n)$ 算出，下面因为最高次项只有三次，所以直接暴力做除法即可。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define p 1000000007
using namespace std;
int jc[3000005],ny[3000005];
int n,q,a[3000005],b[3000005];
int dr()
{
	int xx=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')xx=xx*10+ch-'0',ch=getchar();
	return xx;
}
int C(int x,int y){return 1ll*jc[x]*ny[y]%p*ny[x-y]%p;}
int main()
{
	n=dr(),q=dr();
	jc[0]=ny[0]=ny[1]=1;
	for(int i=1;i<=3*n+3;i++)jc[i]=1ll*i*jc[i-1]%p;
	for(int i=2;i<=3*n+3;i++)ny[i]=1ll*(p-p/i)*ny[p%i]%p;
	for(int i=1;i<=3*n+3;i++)ny[i]=1ll*ny[i]*ny[i-1]%p;
	for(int i=0;i<=3*n+3;i++)a[i]=C(3*n+3,i);
	a[0]-=1,a[1]-=3,a[2]-=3,a[3]-=1;
	a[0]+=a[0]<0?p:0,a[1]+=a[1]<0?p:0,a[2]+=a[2]<0?p:0,a[3]+=a[3]<0?p:0;
	for(int i=1;i<=3*n+3;i++)a[i-1]=a[i];
	for(int i=3*n+2;i>1;i--)
	{
		b[i-2]=a[i];
		a[i-1]=((a[i-1]-3ll*a[i])%p+p)%p,a[i-2]=((a[i-2]-3ll*a[i])%p+p)%p;
	}
	while(q--)printf("%d\n",b[dr()]);
}
```


---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2500}$
---
### 解题思路：

一句话题意就是求：$\sum_{i=1}^n\dbinom{3i}{x}$，其中令 $3i<x$ 时 $\dbinom{3i}{x}=0$。

---
容易想到的方法有两个，直接瞎做就是 $\dbinom{3i}{t}=(1+x)^{3i}[x^t]$，求和就是 $\sum_{i=1}^{n}\dbinom{3i}{t}=\sum_{i=1}^n(1+x)^{3i}[x^t]=\dfrac{(1+x)^3-(1+x)^{3n+3}}{1-(1+x)^3}$。

这个式子分母次数为 $3$，直接暴力大除法 $O(n)$ 算。

---
另一种就是用组合恒等式推。

直接求 $f_{x,0}=\sum_{i=1}^n\dbinom{3i}{x}$ 之间断层太大，不方便直接算出相邻的两项之间的关系，所以引入 $f_{x,1}=\sum_{i=1}^n\dbinom{3i+1}{x}$ 和 $f_{x,2}=\sum_{i=1}^n\dbinom{3i+2}{x}$。

首先根据最基本的 $\dbinom{n}{m}=\dbinom{n-1}{m-1}+\dbinom{n-1}{m}$ 得到 $f_{x,2}=f_{x,1}+f_{x-1,1}$ 和 $f_{x,1}=f_{x,0}+f_{x-1,0}$。

但明显，只有这些是不够的，考虑组合恒等式 $\sum_{i=1}^n\dbinom{i}{x}=\dbinom{n+1}{x+1}$，该恒等式的证明可以用归纳法得出，也可以将最低项 $\dbinom{x}{x}$ 等价变为 $\dbinom{x+1}{x+1}$ 然后一层一层向上化简得到结果。

有了这个恒等式，就有 $f_{x,0}+f_{x,1}+f_{x,2}=\dbinom{3n+3}{x+1}$。

这样解一下方程就能得到：$f_{x,0}=\dfrac{\dbinom{3n+3}{x+1}-2\times f_{x-1,0}-f_{x-1,1}}{3}$，而根据之前的  $f_{x,1}=f_{x,0}+f_{x-1,0}$，就能直接 $O(n)$ 预处理出所有答案了。

---
### 代码：

采用第一种方法。

```cpp
#include<cstdio>
using namespace std;
#define int long long
const int MOD=1000000007;
int n,T,x,f[4000006],F[4000006],a[4000006],ans[4000006],b[4000006];
int pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b=b>>1;
	}
	return ans;
}
int C(int n,int m){
	if(n<m)return 0;
	return f[n]*F[m]%MOD*F[n-m]%MOD;
}
signed main(){
	scanf("%lld%lld",&n,&T);
	f[0]=1;F[0]=1;
	for(int i=1;i<=3*n+5;i++)f[i]=(f[i-1]*i)%MOD;
	F[3*n+5]=pow(f[3*n+5],MOD-2);
	for(int i=3*n+4;i>=1;i--)F[i]=F[i+1]*(i+1)%MOD;
	a[0]=-1;a[1]=-3;a[2]=-3;a[3]=-1;
	for(int i=0;i<=3*n+3;i++)a[i]+=C(3*n+3,i);
	for(int i=3*n+3;i>=3;i--){
		ans[i-3]=a[i];
		a[i-1]=((a[i-1]-3*a[i]+MOD)%MOD+MOD)%MOD;
		a[i-2]=((a[i-2]-3*a[i]+MOD)%MOD+MOD)%MOD;
	}
	while(T--){
		scanf("%lld",&x);
		printf("%lld\n",ans[x]);
	}
	return 0;
}
```


---

## 作者：stOqwqOrz (赞：0)

[LG CF1548C](https://www.luogu.com.cn/problem/CF1548C)

[CF1548C](https://codeforces.com/problemset/problem/1548/C)

**简要题意**

- 给定 $n,q$，有 $q$ 次询问，每次给定 $x$，求 $\sum_{i=1}^n \binom{3i}{x}$

**Solution 1 （生成函数）**

- $\binom{y}{t}=(1+x)^y[x^t]$，那么 $Ans=\sum_{i=1}^n (1+x)^{3i}[x^t]$ 

- 根据等比数列公式，$Ans=\frac{(1+x)^3-(1+x)^{3n+3}}{1-(1+x)^3}$
- 这个可以直接暴力除，列竖式递推

**Solution 2 （dp + 组合数学）**

- 设 $f_{x,j}=\sum_{i=0}^n \binom{3i+j}{x}$，答案就是 $f_{x,0}$

- $f_{x,0}+f_{x,1}+f_{x,2}=\sum_{i=0}^{3n+2} \binom{i}{x}=\binom{3n+3}{x+1}$ 
- 因为 $\binom{n}{m}=\binom{n}{m-1}+\binom{n-1}{m-1}$，$f_{x,1}=f_{x-1,1}+f_{x-1,0},f_{x,2}=f_{x-1,2}+f_{x-1,1}$
- 根据上面三个式子就可以递推下去了

**参考代码（生成函数）：**

```cpp
const int N=3e6+10;
int fac[N],ifac[N],ans[N],num[N],n,q;
inline int C(int x,int y) {
	if(x<y) return 0;
	return MOD(MOD(fac[x]*ifac[y])*ifac[x-y]);
}

signed main(){
//start at 20:45
//end at 20:58
#ifdef LOCAL
    Fin("1");
#endif
    auto init = [&] (){
    	fac[0]=ifac[0]=1;
    	FOR(i,1,3*n+3) fac[i]=MOD(fac[i-1]*i);ifac[3*n+3]=ksm(fac[3*n+3],mod-2);
    	ROF(i,3*n+2,1) ifac[i]=MOD(ifac[i+1]*(i+1));
    };n=read(),q=read();init();
    FOR(i,0,3*n+3) num[i]=C(3*n+3,i);
    num[0]=dec(num[0],1);num[1]=dec(num[1],3);num[2]=dec(num[2],3);num[3]=dec(num[3],1);
    ROF(i,3*n+3,3) {
    	ans[i-3]=num[i];
    	num[i-1]=dec(num[i-1],MOD(3*num[i]));
    	num[i-2]=dec(num[i-2],MOD(3*num[i]));
    }
    while(q--) printf("%d\n",ans[read()]);
#ifdef LOCAL        
    fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
    return 0;
}
```



---

## 作者：hihihi198 (赞：0)

赛时没想出来，于是来写篇题解。

**题意：**

给定 $ n $，共 $ q $ 个询问，对每个询问输入一个 $ x $，求 $ \sum_{i=0}^n\binom{3i}x $，对 $ 10^9+7 $ 取模。

**题解：**

看到组合数，一开始肯定想推式子，然后发现推不出（至少我是这样）。可以考虑 DP 来递推。用一个数组 $ f_{x,k} $ ($ k\in\{0,1,2\} $) 来表示 $ \sum_{i=0}^{n}\binom{3i+k}{x} $。

这里我们可以想一想怎么递推。首先想到的肯定是我们最常用的递推式 $ \binom nm=\binom {n-1}m+\binom{n-1}{m-1} $。用它可以得出如下式子：
$$
(1)\ f_{x,0}=\sum_{i=0}^n\binom{3i}x=\sum_{i=0}^{n-1}\binom{3i+2}x+\sum_{i=0}^{n-1}\binom{3i+2}{x-1}=f_{x,2}+f_{x-1,2}-\binom{3n+2}x-\binom{3n+2}{x-1}
$$
$$
(2)\ f_{x,1}=\sum_{i=0}^n\binom{3i+1}x=\sum_{i=0}^n\binom{3i}x+\sum_{i=0}^n\binom{3i}{x-1}=f_{x,0}+f_{x-1,0}
$$
$$
(3)\ f_{x,2}=\sum_{i=0}^n\binom{3i+2}x=\sum_{i=0}^n\binom{3i+1}x+\sum_{i=0}^n\binom{3i+1}{x-1}=f_{x,1}+f_{x-1,1}
$$

你会发现我们的转移方程中包含了本阶段的状态！并且容易发现，如果把 (2) 式带入 (3) 式，再把 (3) 带入 (1)，我们将得到：
$$
f_{x,0}=f_{x,0}+f_{x-1,0}+f_{x-1,1}+f_{x-1,2}-\binom{3n+2}x-\binom{3n+2}{x-1}
$$
$ f_{x,0} $ 被消掉了，我们什么也没得到。我们只好想其它办法。

等等！$ f_{x,0} $ 被消掉之后的式子是：
$$
f_{x-1,0}+f_{x-1,1}+f_{x-1,2}=\binom{3n+2}x+\binom{3n+2}{x-1}
$$
化一下：
$$
f_{x,0}+f_{x,1}+f_{x,2}=\binom{3n+2}{x+1}+\binom{3n+2}{x}=\binom{3n+3}{x+1}
$$
用这个式子替换掉 (1) 式，就得出了一个可解的方程组：
$$
(1)\ f_{x,0}+f_{x,1}+f_{x,2}=\binom{3n+3}{x+1}
$$
$$
(2)\ f_{x,1}=f_{x,0}+f_{x-1,0}
$$
$$
(3)\ f_{x,2}=f_{x,1}+f_{x-1,1}
$$
解一下：
$$
f_{x,0}=\frac13[\binom{3n+3}{x+1}-2f_{x-1,0}-f_{x-1,1}]
$$
我们成功解决了状态转移方程。边界很简单：$ f_{0,0}=f_{0,1}=f_{0,2}=n+1 $。

我们预处理出 $ f $ 数组。对于每个询问，答案就是 $ f_{x,0} $。

通过以上分析，我们发现 $ f_{x,2} $ 并没有什么卵用，所以在代码中可以不计算它。

如果直接用快速幂求逆元，时间复杂度为 $ O(n\log P+q) $（$ P $ 表示模数），会被毒瘤数据卡掉。所以我们要去学习一下[线性预处理任意 n 个数的逆元](https://www.luogu.com.cn/problem/P5431)。于是时间复杂度为 $ O(n+\log P+q) $。这样就能通过了。

**AC Code (C++11, \#124640483)**
```cpp
#include<cctype>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
using namespace std;
template<typename T>inline void read(T&x){
	register int c=getchar();x=0;bool f=0;
	for(;!isdigit(c);c=getchar())f^=!(c^45);
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
	if(f)x=-x;
}
template<typename T,typename... Args>inline void read(T&x,Args&...args){
	read(x);read(args...);
}
template<typename T>inline void write(T x){
	static int sta[35];register int top=0;
	if(x<0)x=-x,putchar('-');
	do{sta[top++]=x%10,x/=10;}while(x);
	while(top)putchar(sta[--top]+'0');
}
template<typename T>inline void write(T x,const char &c){
	write(x),putchar(c);
}
const int N=1e6+20,P=1e9+7;
inline ll quickPow(ll a,ll b){
	ll ret=1;
	while(b){
		if(b&1)(ret*=a)%=P;
		(a*=a)%=P;b>>=1;
	}
	return ret;
}
ll fact[N*3],inv[N*3],s[N*3],sv[N*3];
inline ll C(int n,int m){
	if(n<m)return 0;
	if(m==0)return 1;
	return fact[n]*inv[m]%P*inv[n-m]%P;
}
int n,q;
ll f[N*3][2];
int main(){
	read(n,q);f[0][0]=f[0][1]=n+1;fact[0]=s[0]=1;
	for(register int i=1;i<=3*n+3;i++){
		fact[i]=fact[i-1]*i%P;
		s[i]=s[i-1]*fact[i]%P;
	}
	sv[n*3+3]=quickPow(s[n*3+3],P-2);
	for(register int i=n*3+3;i>=1;i--)sv[i-1]=sv[i]*fact[i]%P;
	for(register int i=1;i<=n*3+3;i++)inv[i]=sv[i]*s[i-1]%P;
	ll inv3=quickPow(3,P-2);
	for(register int x=1;x<=3*n;x++){
		f[x][0]=inv3*(((C(3*n+3,x+1)-2*f[x-1][0]+2*P)%P-f[x-1][1]+P)%P)%P;
		f[x][1]=(f[x][0]+f[x-1][0])%P;
	}
	int X;
	while(q--){
		read(X);
		write(f[X][0],'\n');
	}
	return 0;
}
```

---

