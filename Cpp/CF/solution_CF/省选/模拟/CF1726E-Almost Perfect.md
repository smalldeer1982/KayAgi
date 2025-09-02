# Almost Perfect

## 题目描述

A permutation $ p $ of length $ n $ is called almost perfect if for all integer $ 1 \leq i \leq n $ , it holds that $ \lvert p_i - p^{-1}_i \rvert \le 1 $ , where $ p^{-1} $ is the inverse permutation of $ p $ (i.e. $ p^{-1}_{k_1} = k_2 $ if and only if $ p_{k_2} = k_1 $ ).

Count the number of almost perfect permutations of length $ n $ modulo $ 998244353 $ .

## 说明/提示

For $ n = 2 $ , both permutations $ [1, 2] $ , and $ [2, 1] $ are almost perfect.

For $ n = 3 $ , there are only $ 6 $ permutations. Having a look at all of them gives us:

- $ [1, 2, 3] $ is an almost perfect permutation.
- $ [1, 3, 2] $ is an almost perfect permutation.
- $ [2, 1, 3] $ is an almost perfect permutation.
- $ [2, 3, 1] $ is NOT an almost perfect permutation ( $ \lvert p_2 - p^{-1}_2 \rvert = \lvert 3 - 1 \rvert = 2 $ ).
- $ [3, 1, 2] $ is NOT an almost perfect permutation ( $ \lvert p_2 - p^{-1}_2 \rvert = \lvert 1 - 3 \rvert = 2 $ ).
- $ [3, 2, 1] $ is an almost perfect permutation.

So we get $ 4 $ almost perfect permutations.

## 样例 #1

### 输入

```
3
2
3
50```

### 输出

```
2
4
830690567```

# 题解

## 作者：Demeanor_Roy (赞：6)

- [原题链接](https://www.luogu.com.cn/problem/CF1726E)

------------

考虑对一个排列 $p$ 取逆的实质：

- 对于 $p$ 中一任意置换环 $C$，将 $C$ 中的边取反。

故 $p_i$ 与 $p^{-1}_i$ 为某 $p$ 中置换环 $C$ 里距离为 $2$ 的点。

对于某个环 $C$，若每个元素有两个距其距离为 $2$ 的点，则环中极值一定不合法。据此分讨， $p$ 中置换环 $C$ 只能为一元、二元、四元环，且四元环需满足对顶点值相邻。

预处理 $f_i$ 表示 $i$ 个元素划分一、二元环的方案，枚举最后一个元素所处环，有转移：$f_i=f_{i-1}+(i-1)f_{i-2}$。

对于给定 $n$，不妨枚举四元环个数 $t$。注意到一个四元环可以看作两对相邻元素拼接，故总方案可看作先选取 $2t$ 对相邻元素，再两两组合，且别忘记四元环正反定向不同，故有贡献系数 $2$。综上，可得：

$$Ans=\sum_{t}{{{n -2t} \choose {2t}}2^tf(n-4t){\prod_{j=0}^{2j+1 < 2t}{(2j+1)}}}$$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=3e5+10,mod=998244353;
int T,n,f[N],pw[N],inv[N],fct[N],ofct[N],finv[N];
inline int C(int x,int y){return 1ll*fct[x]*finv[y]%mod*finv[x-y]%mod;}

inline void init()
{
	f[0]=pw[0]=fct[0]=inv[0]=finv[0]=1;
	f[1]=fct[1]=inv[1]=finv[1]=ofct[1]=1;pw[1]=2;
	for(int i=2;i<N;i++) 
	{
		pw[i]=pw[i-1]*2%mod;
		f[i]=(f[i-1]+1ll*(i-1)*f[i-2])%mod;
		fct[i]=1ll*fct[i-1]*i%mod;
		inv[i]=(mod-1ll*mod/i*inv[mod%i]%mod)%mod;
		finv[i]=1ll*finv[i-1]*inv[i]%mod;
		if(i&1) ofct[i]=1ll*ofct[i-2]*i%mod;
	}
}
inline int calc(int x){return x>0?ofct[x]:1;}
inline void solve()
{
	scanf("%d",&n);
	int ans=0;
	for(int t=0;t<=n/4;t++) ans=(ans+1ll*C(n-t*2,t*2)*calc(t*2-1)%mod*pw[t]%mod*f[n-t*4])%mod;
	printf("%d\n",ans);
}
int main()
{
	init();
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：steven144 (赞：5)

### 题解

这道题首先可以转换为，求满足以下三种条件的排列数。

- $p(i)=i,$
- $p(i)=j,p(j)=i(i<j),$
- $p(i)=j,p(i+1)=j+1,p(j)=i+1,p(j+1)=i(|i-j|>1).$

前两种情况可以看做一元环和二元环，记 $f(i)$ 为长度为 $i$ 的排列，只考虑前两种情况的数量，则 $f(i)=f(i-1)+(i-1)\times f(i-2)$。

第三种情况，可以看做四元环，但它不太好处理，我们一步一步来。

记四元环数量为 $k$。

首先我们只看 $i$ 和 $j$，那么就相当于从 $[1,n-1]$ 中选 $2k$ 个数，使它们两两不相邻（$i$ 和 $j$ 的范围为什么是 $[1,n-1]$ 而不是 $[1,n]$ 呢？这是因为要保证 $i+1$ 和 $j+1$ 也在 $[1,n]$ 里）。

记 $x_0,x_1,x_2,\dots ,x_{2k}$ 为选出的这 $2k$ 个数中两两之间的空隙长度，则
$$x_0\ge0,x_{2k}\ge0,$$
$$\forall 1\le i\le 2k-1,x_i\ge 1,$$
$$\sum_{i=0}^{2k} x_i=n-1-2k.$$
记
$$x_0^{'}=x_0+1,x_k^{'}=x_k+1,$$
$$\forall 1\le i\le 2k-1,x_i^{'}=x_i,$$
则
$$\sum_{i=0}^{2k} x_i^{'}=n-2k+1,$$
$$\forall 0\le i\le 2k,x_i^{'}\ge 1.$$
经过上面的转化，根据插板法可知，答案为 $\binom{n-2k}{2k}$。

$i$ 和 $j$ 已经选完了，将它们组合在一起，就相当于把 $2k$ 个数划分为 $k$ 个有序二元组的方案数。将这 $2k$ 个数任意排列，其中相邻两项视为一个二元组，方案数为 $(2k)!$，而 $k$ 个二元组任意排列，方案数为 $k!$，所以答案为 $\frac{(2k)!}{k!}$。

将一元环、二元环和四元环的方案统计到一起，最终答案为
$$\sum_{k=0}^{\lfloor \frac{n}{4}\rfloor}\binom{n-2k}{2k}\frac{(2k)!}{k!}f(n-4k).$$

### 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define int long long
#define mod 998244353
#define N 300005
const int maxn=300000;
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'|c>'9')
	{
		if(c=='-') f=-f;
		c=getchar();
	} 
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return f*x;
}
int T;
int n;
int fast_pow(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1) ret=ret*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ret;
}
int ifac[N],fac[N],f[N];
void init()
{
	fac[0]=ifac[0]=1;
	for(int i=1;i<=maxn;i++) fac[i]=fac[i-1]*i%mod;
	ifac[maxn]=fast_pow(fac[maxn],mod-2);
	for(int i=maxn-1;i;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
	f[0]=f[1]=1;
	for(int i=2;i<=maxn;i++) f[i]=(f[i-1]+(i-1)*f[i-2]%mod)%mod;
}
int C(int n,int m){return fac[n]*ifac[m]%mod*ifac[n-m]%mod;}
signed main()
{
	T=rd();init();
	while(T--)
	{
		n=rd();
		int ans=0;
		for(int k=0;k<=n/4;k++)
		{
			ans=(ans+C(n-2*k,2*k)*fac[2*k]%mod*ifac[k]%mod*f[n-4*k]%mod)%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：4)

题意：求长度为 $n$ 的排列中，满足 $|p_i-p_i^{-1}|\le 1$ 的 $p$ 的数量。

容易发现原条件等价于 $|i-p_{p_i}|\le 1$。

考虑一个排列平方后的样子。长度为奇数的环环长不变，长度为偶数的环会拆分成两个环长为原来一半的环。

如果有一个环满足其中所有的 $i$ 都有 $|i-q_i|\le 1$，假设其中某一项为 $x$，那么其相邻两项只能为 $x-1$ 和 $x+1$，再扩展两项为 $x-2$ 和 $x+2$，以此类推，直到推到只剩一项或者两项，容易发现这时矛盾。考虑特殊情况（有可能与 $x$ 相邻的只有一项或没有），只有环长不超过 $2$ 时合法。

因此平方后的序列环长只能为 $1$ 或 $2$，反推回来环长就可以是 $1$、$2$ 或 $4$。

环长为 $1$ 或 $2$ 的情况很好算，长为 $n$ 的排列方案数 $f_n=f_{n-1}+f_{n-2}(n-1)$。

环长为 $4$ 时一定是形如 $i\rightarrow j\rightarrow i+1\rightarrow j\pm1\rightarrow i$ 的，注意到 $i\rightarrow j\rightarrow i+1\rightarrow j+1\rightarrow i$ 可以转成 $j\rightarrow i+1\rightarrow j+1\rightarrow i\rightarrow j$，与另外一类等价。

所以我们枚举四元环的个数。有 $i$ 个四元环说明需要 $2i$ 个相邻数对，有 $\binom{n-2i}{2i}$ 种取法，而还有 $i$ 个相邻数对需要翻转，有 $\binom{2i}{i}$ 种翻转方式。最后我们可以任意匹配所有翻转的相邻数对和未翻转的相邻数对，总共有 $n!$ 种方式。

因此，答案为 $\sum\limits_{i=0}^{\lfloor\frac n4\rfloor}\binom{n-2i}{2i}\binom{2i}{i}(i!)f_{n-4i}$。

---

## 作者：Polaris_Australis_ (赞：4)

### 题意

一个长度为 $n$ 的排列 $p$，他的逆排列 $p^{-1}$ 满足 $p_{p_i^{-1}}=i$，求有多少个长度为 $n$ 的排列 $p$，满足 $\forall 1\le i\le n$，$|p_i-p_i^{-1}|\le 1$。

### 题解

经过手画发现，最终 $p$ 只有一下四种置换环：

1. $a_i=i$。
2. $a_i=j$，$a_j=i$。
3. $a_i=j$，$a_{i+1}=j-1$，$a_{j-1}=i$，$a_j=i+1$。
4. $a_i=j$，$a_{i+1}=j+1$，$a_j=i+1$，$a_{j+1}=i$。

如果只考虑一元环和二元环，可以直接预处理。设 $f_i$ 表示长度为 $i$ 的只有一元环和二元环的排列的个数，则 $f_i=f_{i-2}\times (i-1)+f_{i-1}$。

之后考虑四元环的处理，我们枚举有 $i$ 个四元环，则需要 $2\times i$ 组相邻数对，方案数为 $\tbinom{n-2\times i}{2\times i}$，我们发现，四元环的两个相邻数对总有一组是大小反转的，所以需要选出一半是反转的，反转的与未反转的任意顺序连接，则总方案数为 $\sum\limits_{i=0}^{\lfloor \frac{n}{4}\rfloor}\tbinom{n-2\times i}{2\times i}\times \tbinom{2\times i}{i}\times (i!)\times f_{n-4\times i}$。

### 代码

```c++
// Problem: E. Almost Perfect
// Contest: Codeforces - Codeforces Round #819 (Div. 1 + Div. 2) and Grimoire of Code Annual Contest 2022
// URL: https://codeforces.com/contest/1726/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
namespace Std{
void read(int &x){
	x=0;
	int y=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')y=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c&15);
		c=getchar();
	}
	x*=y;
}
int qp(int x,int y){
	int cmp=1;
	while(y){
		if(y&1)(cmp*=x)%=mod;
		(x*=x)%=mod;
		y>>=1;
	}
	return cmp;
}
int fac[300010],ifac[300010],f[300010],n,t;
int C(int x,int y){
	if(y>x)return 0;
	return fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
void main(){
	fac[0]=1;
	for(int i=1;i<=300000;++i)fac[i]=(fac[i-1]*i)%mod;
	ifac[300000]=qp(fac[300000],mod-2);
	for(int i=299999;~i;--i)ifac[i]=(ifac[i+1]*(i+1))%mod;
	f[0]=f[1]=1;
	for(int i=2;i<=300000;++i)f[i]=(f[i-2]*(i-1)+f[i-1])%mod;
	read(t);
	while(t--){
		read(n);
		int ans=0;
		for(int i=0;i*4<=n;++i){
			ans+=C(n-2*i,2*i)*C(2*i,i)%mod*fac[i]%mod*f[n-4*i]%mod;
		}
		printf("%lld\n",ans%mod);
	}
}
}  // namespace Std
#undef int
int main(){
	Std::main();
	return 0;
}
```

---

## 作者：MortisM (赞：4)

> [CF1726E Almost Perfect](https://codeforces.com/contest/1726/problem/E)

挺好的一道数学题，vp 时没有通过，不过赛时过的人为什么这么多？看来还是我太菜了。后来看了题解，FFT 的方法完全不懂/kk（不会 FFT QAQ）。但是搞懂了一种简单一些的方法，有点妙，遂发个题解。

首先，你需要一个 **关键性质：**（P.S. 感觉这个性质不是人能想到的？）

> 如果将 $i\to p_i$ 连边的话，最终图上的环只有可能是 $(i)$ 或 $(i,j)$ 或 $(i,j,i+1,j+1)$。

证明如下：

首先，证明不可能有长度 $=3$ 的环。假设这个环存在，设为 $(a,b,c)$，则根据定义可知 $p^{-1}_b=a$ 且 $p_b=c$。因为 $a,b,c$ 对称，所以不妨设 $a<b<c$，又因为 $|p_b|-|p^{-1}_b|\leq 1$，即 $|a-c|\leq 1$，矛盾，所以不存在。

再证明不存在长度 $\geq 5$ 的环，方法与上面的类似。假设环存在，设为 $(a_1,a_2,...,a_k)$，每次跳两个 $-1$，那么最后回跳到 $>k$ 的，就往回绕，一定会绕到重复的，有重复的就矛盾了，所以不存在。

因为 $(i),(i,j)$ 和 $(i,j,i+1,j+1)$ 的存在性都是显然的，除了 $(i,j,i+1,j+1)$ 的必要性也是显然的，所以下证 $(i,j,i+1,j+1)$ 的必要性。设环为 $(a,b,c,d)$，则考虑 $|a-c|=1,|b-d|=1$。
+ 若 $b<d$，则环为 $(a,b,a+1,b+1)$。
+ 若 $b\geq d$，则环为 $(a,d+1,a+1,d)$，可变为 $(d,a,d+1,a+1)$。

有了这个关键性质以后，就可以枚举 $(i,j,i+1,j+1)$ 的环的个数为 $s$，则选出的方案有 $\binom{n-2s}{2s}$ 种，加上内部选举的方案有：

$$
\binom{n-2s}{2s}\cdot\frac{(2s)!}{s!}
$$

设 $I_x$ 表示选 $(i)$ 或 $(i,j)$ 的长度为 $x$ 的方案数，则：

$$
I_x=I_{x-1}+(x-1)\cdot I_{x-2}
$$

答案为：

$$
\binom{n-2s}{2s}\cdot\frac{(2s)!}{s!}\cdot I_{n-4s}
$$

时间复杂度 $O(N)$。

***

**Code**

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define mod 998244353
#define MOD 1000000007
#define F first
#define S second
#define ll long long
#define N 300005
using namespace std;
int n,dp[N],fac[N],inv[N],ifac[N];
int binom(int x,int y){
	return 1LL*fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
void solve(){
	scanf("%d",&n);
	int ans=0;
	for(int i=0;i<=n/4;i++){
		int cur=binom(n-2*i,2*i);
		cur=1LL*cur*fac[2*i]%mod*ifac[i]%mod;
		cur=1LL*cur*dp[n-4*i]%mod;
		ans=(ans+cur)%mod;
	}
	printf("%d\n",ans);
}
int main(){
	dp[0]=1;
	dp[1]=1;
	for(int i=2;i<N;i++){
		dp[i]=(dp[i-1]+1LL*(i-1)*dp[i-2]%mod)%mod;
	}
	fac[0]=inv[0]=ifac[0]=1;
	for(int i=1;i<N;i++){
		fac[i]=1LL*fac[i-1]*i%mod;
		if(i==1){
			inv[i]=1;
		}
		else{
			inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod;
		}
		ifac[i]=1LL*ifac[i-1]*inv[i]%mod;
	}
	int t;
	scanf("%d",&t);
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：foreverlasting (赞：3)

题意：问长度为 $n$ 的排列数，满足对任意的 $i$，$|p_i-j|\leq 1$，其中 $j$ 满足 $p_j=i$。

题解：考虑 $p_i$ 表示 $i$ 向 $p_i$ 连一条有向边。经过一定的手玩，可以发现最终序列一定只包含相邻二元组构成的四元环 (例如 $(i,j,i+1,j+1)$)，二元环 (例如 $(i,j)$) 和自环 (例如 $(i,i)$)。考虑枚举四元环的数量和二元环的数量，以及它们分别是谁，那么答案就是
$$
\sum_{k=0}^{\frac{n}{4}} \binom{n-2k}{2k}\cdot \frac{(2k)!2^k}{k!2^k}\sum_{i=0}^{\frac{n-4k}{2}}\binom{n-4k}{2i} \frac{(2i)!}{2^ii!}
$$
解释下这个式子的含义，$k$ 为四元环数量，那么四元环的方案就是先挑出二元组，考虑 $n-2k$ 的序列中挑出 $2k$ 个位置，然后这些位置扩展成两个，然后这些二元组两两匹配，那就是先把它们排成一排，即 $(2k)!$，然后相邻的二元组匹配，这样交换相邻和已经匹配好再排列是重复的，所以要除以 $k!2^k$。另一方面，任意一个四元环都有 $(i,j,i+1,j+1)$ 或 $(i+1,j,i,j+1)$ 两种，所以再乘上 $2^k$。而后半部分就是二元环，$i$ 为二元环数量，与四元环同理的思路写出了式子。

然后稍微做一下化简，于是答案为 
$$
\sum_{k=0}^{\frac{n}{4}} \frac{(n-2k)!}{k!}\sum_{i=0}^{\frac{n-4k}{2}}\frac{1}{(n-4k-2i)!2^ii!}
$$
此时后半部分已经可以卷积了，时间复杂度 $O(n\log n)$。

不过可以更进一步思考后半部分是啥，注意到后半部分实际上就是求 $[x^n] F\ast G$，其中 $F(x)=\sum_{n\geq 0} \frac{1}{n!}x^n,G(x)=\sum_{n\geq 0}\frac{1}{x^ii!}x^{2i}$。而这两种的封闭形式是容易的，即 $F(x)=e^x,G(x)=e^{\frac{x^2}{2}}$，于是就是要求 
$$
[x^n]e^{\frac{x^2}{2}+x}
$$
注意到 $\frac{x^2}{2}+x$ 求导后很简单，就是 $x+1$。于是设 $H(x)=e^{\frac{x^2}{2}+x}=\sum_{n\geq 0} h_nx^n$，而 $H'(x)=H(x)(x+1)=h_0+\sum_{n\geq 1} (h_n+h_{n-1})x^n=\sum_{n\geq 0} (n+1)h_{n+1}x^n$，于是有 $h_n=\frac{h_{n-1}+h_{n-2}}{n},n\geq 2$。因此就线性递推出 $h_n$，答案式子也就线性求出了。时间复杂度 $O(n)$。

```cpp
//2022.10.13 by ljz
//email 573902690@qq.com
//if you find any bug in my code
//please tell me
const int N=3e5+10;
Z fac[N],inv[N],finv[N],ipw[N],f[N];
namespace MAIN {
	inline void MAIN(const int &Case) {
		int n=read();
		Z ans=0;
		for(int k=0;k<=n/4;k++){
			ans+=f[n-4*k]*fac[n-2*k]*finv[k];
		}
		printf("%d\n",ans);
	}
}

int main() {
	Z inv2=Z{2}.inverse();
	fac[0]=fac[1]=inv[0]=inv[1]=ipw[0]=finv[0]=finv[1]=1,ipw[1]=inv2;
	f[0]=f[1]=1;
	for(int i=2;i<=N-10;i++)fac[i]=fac[i-1]*i,inv[i]=inv[kcz%i]*(kcz-kcz/i),ipw[i]=ipw[i-1]*inv2;
	for(int i=2;i<=N-10;i++)finv[i]=finv[i-1]*inv[i],f[i]=(f[i-1]+f[i-2])*inv[i];
	int Case = read();
	for (int T = 1; T <= Case; T++)MAIN::MAIN(T);
	return 0;
}
```



---

## 作者：qinyubo (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1726E)

题目大意：$T$ 组数据，每组给定一个 $n$，求对于所有 $n$ 阶排列 $p$，设其逆为 $q$，有多少个使得对于任意 $1\le i\le n$ 有 $|p_i-q_i|\le1$。其中，$p$ 的逆 $q$ 为满足 $q_{p_i}=i$ 的唯一排列。

$1\le T\le10^3,1\le\sum n\le3\times10^5$

小清新数学题。

首先发现，对于任意 $i$ 有 $|p_i-q_i|=1$ 等价于对于任意 $i$ 有 $|p_{p_i}-i|=1$。

然后，很容易想到把排列转换成有向图，即 $i$ 向 $p_i$ 连边，那么，这个图实际上是由若干个环构成。

那么，条件就是任意点 $i$ 沿边跳两下跳到 $j$ 都有 $|i-j|\le1$。

于是，我们可以两下两下的跳，由于 $i$ 一定在某个环里，可以发现最后一定会跳回 $i$：$i\to i_1\to i_2\to\cdots\to i_k\to i$。

然后，我们发现，只要 $k\ge2$，即跳的步数超过 $2$，那么这个排列一定不合法。

为什么呢？

考虑由于 $i_1\ne i$，必有 $i_1=i+1$ 或 $i_1=i-1$。

如果 $i_1=i+1$，则由于 $i_2\ne i_1$，必有 $i_2=i_1+1$ 或 $i_2=i_1-1$。

而 $i_2\ne i=(i+1)-1=i_1-1$，故 $i_2=i_1+1=i+2$。

同理，$i_3=i_2+1=i+3$，$i_4=i+4$，$\cdots$，$i_k=i+k$。由于 $k\ge2$，故 $i_k=i+k\ge i+2$，故 $|i_k-i|\ge2$，不合法。

$i_1=i-1$ 情况类似。

然后，我们就可以把 $p$ 拆成环，考虑每个环的合法性。

一元环、二元环的合法性是平凡的，因为其上面任何一个点跳两步都会跳回自己。

三元环可以吗？不行。假设这个三元环是 $\begin{pmatrix}a&b&c\\b&c&a\end{pmatrix}$，那么从 $a$ 开始跳就会跳出 $a\to c\to b\to a$，跳的步数超过 $2$，不合法。

四元环呢？可以，但有条件。假设这个四元环是 $\begin{pmatrix}a&b&c&d\\b&c&d&a\end{pmatrix}$，那么 $a\to c\to a$，$b\to d\to b$，所以 $|a-c|\ge1$，$|b-d|\ge1$，而 $a\ne c$，$b\ne d$ 故 $|a-c|=|b-d|=1$。

然后，五元环、六元环及更长的环一定要跳超过 $3$ 步才能回来。所以，题目等价于求只由一元环、二元环和满足下列条件的四元环的 $n$ 阶排列个数：

- 若这个四元环是 $(a,b,c,d)$，那么 $|a-c|=|b=d|=1$。

发现一元环和二元环没有多余的限制，发现只由一元环、二元环构成的排列个数只与长度有关。于是设 $f_i$ 为长度为 $i$ 的，只由一元环、二元环构成的排列个数。

可以推出式子来：

$$f_i=f_{i-1}+(i-1)f_{i-2}$$

$f_{i-1}$ 表示第 $i$ 个元素自成一环，$(i-1)f_{i-2}$ 表示枚举第 $i$ 个和前面 $i-1$ 个中的某一个凑成二元环。

于是，想到把 $n$ 个元素选出若干个组成四元环，再乘上剩下来的元素的 $f$ 值。

而两个相邻的、没有重复元素的元素对可以组成两种四元环，即 $(a,a+1)$ 和 $(b,b+1)$ 可以组成 $(a,b,a+1,b+1)$ 和 $(a,b+1,a+1,b)$ 两个不同的四元环，而一个相邻的元素对可以对应这对元素间的间隔，那么选出两个这样的元素对就是在 $n$ 个元素的 $n-1$ 个间隔中选出两个不相邻的间隔。

假设我们要选出 $k$ 个四元环，那么我们要选出 $2k$ 个不相邻的间隔，再把这 $2k$ 个间隔两两配对组成 $k$ 个四元环，那么我们最终的答案是

$$\sum_kf_{n-4k}g_kh_k2^k$$

其中 $g_k$ 为 $n-1$ 个间隔选出 $2k$ 个不相邻的间隔的方案个数，$h_k$ 为把 $2k$ 个间隔两两配对的方案数，多出来一个 $2^k$ 是因为每一个间隔的配对可以产生两种四元环。

$h_k$ 是简单的，考虑枚举第 $2k$ 个间隔和前 $2k-1$ 个间隔中的哪个配对，即

$$h_k=(2k-1)h_{k-2}$$

递推得 $h_k=(2k-1)\times(2k-3)\times\cdots\times3\times1=\dfrac{(2k)!}{k!2^k}$。

而 $g_k$ 可以用组合意义推出来。

$g_k$ 等价于有 $n-1$ 个排成一排的一样的球，选 $2k$ 个，使得其两两不相邻。

可以先选出 $2k$ 个球排成一排，再把剩下的 $n-2k-1$ 个球插到 $2k$ 个球的间隙里，使它们不相邻。（注意，由于球是一样的，所以选出 $2k$ 个球排成一排的方案数是 $1$）

由于不能相邻，我们可以先把 $n-2k-1$ 个球中选 $2k-1$ 个插到 $2k$ 个球的间隙里，确保不能相邻。（这里的方案数也是 $1$）剩下 $n-4k$ 个球。

然后，我们要把 $n-4k$ 个球放到 $2k$ 个球包括两端的 $2k+1$ 个间隙里，没有限制，用隔板法可知是 $\dbinom{n-2k}{2k}$。

所以，最终答案即为：

$$\sum_kf_{n-4k}\dbinom{n-2k}{2k}\dfrac{(2k)!}{k!2^k}2^k=\sum_kf_{n-4k}\dfrac{(n-2k)!}{(n-4k)!k!}$$

代码里 $a$ 是阶乘，$b$ 是阶乘的逆元，还是很好写的。

```cpp
#include <bits/stdc++.h>
#define P 998244353ll
#define ll long long
using namespace std;
namespace QYB {
    ll f[300005], a[300005], b[300005];
    int main() {
        f[0] = f[1] = a[0] = 1; b[300000] = 988693096ll;
        for (int i = 2; i <= 300000; i++) f[i] = (f[i - 2] * (i - 1) % P + f[i - 1]) % P;
        for (int i = 1; i <= 300000; i++) a[i] = a[i - 1] * i % P;
        for (int i = 300000; i >= 1; i--) b[i - 1] = b[i] * i % P;
        int t; scanf("%d", &t);
        while (t--) {
            int n; ll ans = 0; scanf("%d", &n);
            for (int i = 0; i * 4 <= n; i++) {
                (ans += f[n - 4 * i] * a[n - 2 * i] % P * b[n - 4 * i] % P * b[i] % P) %= P;
            } printf("%lld\n", ans);
        } return 0;
    }
} int main() {
    return QYB::main();
}
```

---

## 作者：MSqwq (赞：2)

一道好玩的数论题  
题意：  
询问一个长度为 $n$ 的排列有多少种合法的排列方式。  
合法的定义: $ \lvert p_i - p_i^{-1}\rvert \le 1$，($p_i^{-1}=k$ 当且仅当 $p_k = i$)   
做法：  
很显然就是去组成若干个环，这里就给出结论了，其实模拟几组数据就不难发现  
环有三种。  
1 只有一个元素 $p_i = i$。   
2 两个元素 $p_i = j$，$p_j = i$ 。  
3 四个元素 $p_i = j$，$p_j = i + 1$，$p_{i + 1} = j + 1$，$p_{j + 1}$ = $i$ 。

我们首先固定二元环和四元环的数量  
先讨论四元环，设四元环的数量为 $s$。  
可能不好理解，所以举个例子：  
$p_i = 3 \ 4\  2\  1$  
$p_i^{-1} = 4 \ 3\  1\  2$   
那么我们从 $[1, n - 1]$ ( 因为 $i$,$j$ 即可确定 $i + 1$,$j + 1$ ，所以本质是选两个数，且不能越界)里面选择 $s$ 的总方案数为  ${n - 2s\choose 2s} \frac{(2s)!}{s!}$。    
组合数是因为不能选择连续的, 所以采用隔板法。  
由于我们最后得到的是 $s$ 个四元环, 需要对这 $2s$ 个元素分类, 最后得到 $\frac{(2s)!}{s!}$ 种。

然后我们来讨论二元环和自环的情况  
设 $dp[i]$ 为 长度为 $i$ 的排列中只有自环和二元环的情况时的方案数。  
每次新加入一个元素$i$，$i$ 自己可以构成一个元素为 $1$ 的环，方案数是 $f[i - 1]$ ,其次 $i$ 自己可以与任意一个数构成一个大小为 $2$ 的环，方案数是 $f[i - 2] \times (i - 1)$，表示有 $i - 1$ 个选择合成一个 $2$ 个元素的环。  

那么最终答案为 $\sum\limits_{s = 0}^{\lfloor{\frac{x}{4}} \rfloor}{n - 2s\choose 2s}\frac{(2s)!}{s!} dp_{n - 4s}$。  

代码：  
```
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<math.h>
#define ll long long
using namespace std;
const int mod=998244353;
const int INF=0x3f3f3f3f;

inline int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0',c=getchar();}
    return x*f;
}
ll quickpow(ll a,ll b)
{
    ll s=1;
    while(b)
    {
        if(b&1)s=s*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    
    return s;
}

const int N=3e5+10;
ll f[N],in[N],nin[N];
ll C(ll n,ll m)
{
    if(n<m)return 0;
    return in[n]*nin[m]%mod*nin[n-m]%mod;
} 

void solve()
{
	int n=read();
	ll ans=0;
	for(ll i=0;i<=n/4;i++)ans=(ans+C(n-2*i,2*i)*in[2*i]%mod*nin[i]%mod*f[n-4*i]%mod)%mod;
	printf("%lld\n",ans);
}

int main()
{
	f[0]=1;
	f[1]=1;
	for(int i=2;i<=N-10;i++)f[i]=(f[i-1]+(i-1)*f[i-2]%mod)%mod;

	in[0]=1;
	in[1]=1;
	for(int i=2;i<=N-10;i++)in[i]=in[i-1]*i%mod;
	
	nin[N-10]=quickpow(in[N-10],mod-2);
	for(int i=N-11;i>=0;i--)nin[i]=nin[i+1]*(1ll+i)%mod;
	int T=read();
	while(T--)solve();
	return 0;
}
```


---

## 作者：TernaryTree (赞：0)

将 $i\to p_i$ 连边，则 $q_i$ 为 $i$ 在图上唯一的入点。根据 $|p_i-q_i|\le 1$，即图上任意点的入点出点差 $\le 1$。

显然这样的图由若干个环构成。对于一个环，考虑其长度。

- 长度为 $1$ 或 $2$，则必定满足。
- 长度为 $3$，容易发现不可能满足。
- 长度为 $4$，则当且仅当环中两组相对的点对的差都 $\le 1$。
- 长度 $\ge 5$，同样不可能满足。

枚举长度为 $4$ 的环个数 $i$，则剩余 $n-4i$ 个点的组合方式可通过枚举长度为 $2$ 的环个数得到。令有 $i$ 个点的所有环长度 $\le 2$ 的排列方案数为 $f_i$，有：

$$
\begin{aligned}
f_i&=\sum_{j=0}^{\lfloor\frac i2\rfloor}\dfrac{i!}{2^j(i-2j)!j!} \\
&=i!\sum_{j=0}^{\lfloor\frac i2\rfloor}\dfrac{1}{2^j(i-2j)!j!}
\end{aligned}
$$

令 $g_i=\dfrac{1}{2^i\cdot i!}$，$h_i=\dfrac{1}{i!}$，则

$$
\begin{aligned}
f_i&=i!\sum_{j=0}^{\lfloor\frac i2\rfloor}g_jh_{i-2j}
\end{aligned}
$$

类似卷积形式，但是 $i-2j$ 不好处理。令 $p_i=f_{2i}$，$q_i=f_{2i+1}$。代入得到

$$
\begin{aligned}
p_i&=f_{2i}=(2i)!\sum_{j=0}^{i}g_jh_{2(i-j)} \\
q_i&=f_{2i+1}=(2i+1)!\sum_{j=0}^{i}g_jh_{2(i-j)+1}
\end{aligned}
$$

令 $x_i=h_{2i}$，$y_{i}=h_{2i+1}$，然后就能开心卷了。

最终答案为：

$$
\sum_{i=0}^{\lfloor\frac n4\rfloor} f_{n-4i}\cdot \dbinom{n-2i}{2i}\cdot \dfrac{(2i)!}{i!}
$$

其中 $\dbinom{n-2i}{2i}$ 表示在 $n$ 里面选 $2i$ 对相邻的数的方案数，$\dfrac{(2i)!}{2^i\cdot i!}\cdot 2^i$ 是分组方案数，每组还能选正反两个方向。

总复杂度 $\Theta(n\log n+\sum n)$。常数略大，喜提次劣解。

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

const int maxn = (1 << 20) + 10;
const bool multidata = 1;
const int mod = 0x3b800001, groot = 3;
const int inv2 = (mod + 1) >> 1;

int read() {
	int x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

void write(int x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write(x / 10), pc(x % 10 + '0');
}

int omg[maxn], inv[maxn], rev[maxn];

int power(int a, int b, int p = mod) {
	int t = 1;
	a %= p;
	while (b) {
		if (b & 1) t = t * a % p;
		a = a * a % p, b >>= 1;
	}
	return t;
}

void getrev(int n) {
	rev[0] = 0;
	for (int i = 1; i < n; i++) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? (n >> 1) : 0);
}

void getw(int n) {
	int x = power(groot, (mod - 1) / n), y = power(x, mod - 2);
	omg[0] = inv[0] = 1;
	for (int i = 1; i < n; i++) {
		omg[i] = omg[i - 1] * x % mod;
		inv[i] = inv[i - 1] * y % mod;
	}
}

void ntt(int * a, int n, int * w) {
	for (int i = 0; i < n; i++) if (rev[i] < i) swap(a[rev[i]], a[i]);
	for (int len = 2; len <= n; len <<= 1) {
		int m = len >> 1;
		for (int i = 0; i < n; i += len) {
			for (int j = 0; j < m; j++) {
				int x = w[n / len * j], y = x * a[i + j + m] % mod;
				a[i + j + m] = (a[i + j] - y + mod) % mod;
				a[i + j] = (a[i + j] + y) % mod;
			}
		}
	}
}

int tmpa[maxn], tmpb[maxn], tmpc[maxn], tmpd[maxn], tmpe[maxn], tmpf[maxn], tmpg[maxn];

void Mul(int * a, int * b, int * c, int n, int m) {
	memset(tmpa, 0, sizeof(tmpa));
	memset(tmpb, 0, sizeof(tmpb));
	for (int i = 0; i < n; i++) tmpa[i] = a[i];
	for (int i = 0; i < m; i++) tmpb[i] = b[i];
	memcpy(tmpb, b, sizeof(int) * (m + 5));
	int lim = 1;
	while (lim <= n + m - 1) lim <<= 1;
	getrev(lim), getw(lim);
	ntt(tmpa, lim, omg), ntt(tmpb, lim, omg);
	for (int i = 0; i < lim; i++) c[i] = tmpa[i] * tmpb[i] % mod;
	ntt(c, lim, inv);
	int pw = power(lim, mod - 2);
	for (int i = 0; i < lim; i++) c[i] = c[i] * pw % mod;
}

int fac[maxn], ifac[maxn], pw[maxn], ipw[maxn];
int f[maxn], g[maxn], h[maxn], p[maxn], q[maxn];
int x[maxn], y[maxn];

void init(int n) {
	fac[0] = 1; rep(i, 1, n) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], mod - 2); per(i, n - 1, 0) ifac[i] = ifac[i + 1] * (i + 1) % mod;
	pw[0] = ipw[0] = 1; rep(i, 1, n) pw[i] = pw[i - 1] * 2 % mod, ipw[i] = ipw[i - 1] * inv2 % mod;
	rep(i, 0, n) g[i] = ifac[i] * ipw[i] % mod, h[i] = ifac[i];
	rep(i, 0, n) x[i] = h[i * 2], y[i] = h[i * 2 + 1];
	Mul(g, x, p, n / 2, n / 2), Mul(g, y, q, n / 2, n / 2);
	rep(i, 0, n / 2) f[i * 2] = p[i], f[i * 2 + 1] = q[i];
	rep(i, 0, n) f[i] = f[i] * fac[i] % mod;
}

int C(int n, int m) {
	if (n < 0 || n < m || m < 0) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int n, ans;

void fake_main() {
	n = read(), ans = 0;
	rep(i, 0, n / 4) (ans += f[n - i * 4] * C(n - i * 2, i * 2) % mod * fac[i * 2] % mod * ifac[i] % mod) %= mod;
	write(ans), pc('\n');
}

signed main() {
	init(3.2e5);
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}
```

---

