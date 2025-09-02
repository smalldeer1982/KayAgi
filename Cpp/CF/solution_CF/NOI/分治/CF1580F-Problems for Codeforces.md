# Problems for Codeforces

## 题目描述

XYMXYM 与 CQXYM 将为 Codeforces 准备 $n$ 个题目。第 $i$ 个题目的难度为整数 $a_i$ 且 $a_i\geq 0$。所有题目的难度必须满足 $a_i+a_{i+1}\lt m\,\space(1\leq i\lt n)$ 且 $a_1+a_n\lt m$，其中 $m$ 为一个固定整数。XYMXYM 想知道题目难度有多少种可能的方案，结果对 $998244353$ 取模。

两种题目难度的方案 $a$ 和 $b$ 是不同的当且仅当存在一个整数 $i,\space (1\leq i\leq n)$ 满足 $a_i\neq b_i$。

## 说明/提示

在第一个样例中，合法的方案为 $[0,0,0],[0,0,1],[0,1,0],[1,0,0]$，而 $[1,0,1]$ 不合法因为 $a_1+a_n\geq m$。

## 样例 #1

### 输入

```
3 2```

### 输出

```
4```

## 样例 #2

### 输入

```
5 9```

### 输出

```
8105```

## 样例 #3

### 输入

```
21038 3942834```

### 输出

```
338529212```

# 题解

## 作者：FZzzz (赞：8)

神题。

考虑两个相邻的数中至多有一个数不小于 $\lceil\dfrac m2\rceil$。且若两个相邻的数都小于 $\lceil\dfrac m2\rceil$，则这这个位置一定满足条件。

这启发我们将环在每个这样的位置处划分成若干段，那么每一段的长度必然为奇数，其中小于 $\lceil\dfrac m2\rceil$ 的数（以下简称“小数”）和不小于 $\lceil\dfrac m2\rceil$ 的数（简称“大数”）交替出现，并且段与段之间无关。

如果我们求出每个长度的合法段的数量，我们自然可以一次求逆求出把这些段拼接成每个长度的大段的数量，然后枚举跨过最后一个和第一个数的段的长度求得题目所求序列个数。但若 $n$ 为偶数，我们可能无法找到两个相邻的小数，这种情况稍后讨论。至此问题转化为如何求出每个长度的段数。

考虑，将一个段内的所有大数减去 $\lceil\dfrac m2\rceil$，这样相邻的数只需和小于 $\lfloor\dfrac m2\rfloor$，并且第一个数和最后一个数不视为相邻。以下将“相邻两数和小于 $m$ 的序列，首尾不视为相邻”简称为“$m$ 的合法序列”。顺着这个思路可以发现，除段长为 $1$ 的情况以外（可以简单特殊处理），某一长度的 $\lfloor\dfrac m2\rfloor$ 的合法序列个数与 $m$ 的合法段数一一对应。为了方便，这里把长度为偶数的合法段定义为以小数开头的小大交错的段，满足相邻数（第一个与最后一个不视为相邻）和小于 $m$。

那么现在我们可以把问题规模在 $m$ 这一维减半，现在我们只需要考虑如何从每个长度的合法段数得到序列上的答案。用类似的思想，找到第一组和最后一组相邻的小数。特别地，如果第一个或者最后一个数是小数，那么也算作两组相邻的小数。那么两边两段长度很显然是偶数，中间是若干段奇数段拼起来。但我们还漏掉了一种情况：如果没有相邻的小数，则把大数减去 $\lceil\dfrac m2\rceil$，小数加上 $\lceil\dfrac m2\rceil$，可以对应到等长的一组合法段。如果设 $A$ 为奇数段的 OGF，$B$ 为偶数段的 OGF，则可以容易地得到合法序列的 OGF 为：
$$\frac{B^2}{1-A}+A$$
可以 $O(n\log n)$ 求解。于是总复杂度为 $O(n\log n\log m)$。

但我们还遗留了一个问题：$n$ 为偶数的情况如何处理。对于这种情况，我们同样可以以上面的方法将 $m$ 减半。由于第一个数有可能是大数也有可能是小数，所以 $m$ 的答案是 $\lfloor\dfrac m2\rfloor$ 的答案乘以 $2$，再加上用合法段拼接的方案数。于是问题得到完整解决，时间复杂度 $O(n\log n\log m)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=5e4+5;
int n,m;
const int mod=998244353,g=3,invg=332748118;
int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b%2==1) ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b/=2;
	}
	return ans;
}
typedef vector<int> poly;
int rev[maxn*6],w[maxn*6],w2[maxn*6],invn;
void init(int n){
	for(int i=1;i<n;i++) rev[i]=rev[i>>1]>>1|((i&1)?n>>1:0);
	for(int i=1;i<n;i*=2){
		w[i]=1;
		int wn=ksm(g,(mod-1)/(i*2));
		for(int j=1;j<i;j++) w[i+j]=1ll*w[i+j-1]*wn%mod;
	}
	for(int i=1;i<n;i*=2){
		w2[i]=1;
		int wn=ksm(invg,(mod-1)/(i*2));
		for(int j=1;j<i;j++) w2[i+j]=1ll*w2[i+j-1]*wn%mod;
	}
	invn=ksm(n,mod-2);
}
poly FFT(poly F,bool flag){
	int n=F.size();
	for(int i=0;i<n;i++) if(i<rev[i]) swap(F[i],F[rev[i]]);
	for(int i=1;i<n;i*=2) for(int j=0;j<n;j+=i*2)
		for(int k=j;k<j+i;k++){
			int t=1ll*F[k+i]*(flag?w[i+k-j]:w2[i+k-j])%mod;
			F[k+i]=(F[k]-t+mod)%mod;
			F[k]=(F[k]+t)%mod;
		}
	if(!flag) for(int i=0;i<n;i++) F[i]=1ll*F[i]*invn%mod;
	return F;
}
poly Inv(poly F){
	int n=F.size();
	if(n==1) return {ksm(F[0],mod-2)};
	poly G=Inv(poly(F.begin(),F.begin()+(n+1)/2));
	int len=1;
	while(len<n*2-1) len*=2;
	F.resize(len);
	G.resize(len);
	init(len);
	F=FFT(F,1);
	G=FFT(G,1);
	for(int i=0;i<len;i++) F[i]=(2-1ll*F[i]*G[i]%mod+mod)%mod*G[i]%mod;
	F=FFT(F,0);
	F.resize(n);
	return F;
}
int ans=0;
poly solve(int m){
	if(!m){
		poly F(n+1);
		F[0]=1;
		return F;
	}
	poly F=solve(m/2),G(n+1);
	for(int i=0;i<=n;i+=2){
		G[i]=F[i];
		F[i]=0;
	}
	F[1]=(m+1)/2;
	poly H(n+1);
	H[0]=1;
	for(int i=1;i<=n;i++) H[i]=(mod-F[i])%mod;
	H=Inv(H);
	ans=n%2==0?(1ll*ans*2%mod+H[n])%mod:H[n];
	for(int i=1;i<=n;i+=2) ans=(ans+1ll*F[i]*H[n-i]%mod*(i-1)%mod)%mod;
	int len=1;
	while(len<n*3+1) len*=2;
	G.resize(len);
	H.resize(len);
	init(len);
	G=FFT(G,1);
	H=FFT(H,1);
	for(int i=0;i<len;i++) G[i]=1ll*G[i]*G[i]%mod*H[i]%mod;
	G=FFT(G,0);
	for(int i=0;i<=n;i++) F[i]=(F[i]+G[i])%mod;
	return F;
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	m=readint();
	solve(m);
	printf("%d\n",ans);
	#ifdef LOCAL
	fprintf(stderr,"%d\n",(int)clock());
	#endif
	return 0;
}
```
>这个 F
>
>不错
>
>很牛逼
>
>我十足喜欢这个想法
>
>这确实值得一做
>
>让人耳目一新的小清新多项式
>
>难度不高但真的想不到第一步怎么转化
>
>但做完之后倒过来看整个题又是在凸显这个唯一的 idea
>
>很棒，你们出题的时候都学学
>
>——fyk

---

## 作者：OshamaScramble (赞：5)

## 题意

求长度为 $n$，相邻两个数（包括 $1$ 和 $n$）之和 $<m$ 的序列个数，对 $998244353$ 取模，$n \leq 5\times 10^4$, $m \leq 10^9$。

## 题解

为方便表述，下文将用大写字母表示小写字母的 OGF，用 $m/2$ 替代  $\left\lfloor\dfrac{m}{2}\right\rfloor$。

将 $< \left\lceil\dfrac{m}{2}\right\rceil$ 的数叫做「小数」（用 $\tt S$ 表示），$\ge \left\lceil\dfrac{m}{2}\right\rceil$ 的数叫做「大数」（用 $\tt B$ 表示），那这个环有两种情况：

1. 被分成若干个 $\tt{SBS\dots BS}$（以 $\tt S$ 开头， 以 $\tt S$ 结尾，且 $\tt SB$ 交替）的「奇段」；
2. 整个环是 $\tt SB$ 交替的。

### Part 1

先考虑第一种情况的计数，我们断环为链，统计由奇段拼成的链的个数。不妨长度为 $i$ 的奇段有 $a_i$ 种方案，用若干奇段拼成长度为 $i$ 的链有 $t_i$ 种方案，则考虑其 OGF 有 $T(x) = \dfrac{1}{1-A(x)}$。分两种讨论：

- 环的断点恰好是奇段的断点，此时环等同于链，方案数为 $t_n$；
- 否则我们枚举被断开的奇段的长度 $i$，方案数为 $(i-1)t_{n-i}a_i$。

故 $res=t_n + \sum (i-1)t_{n-i}a_i$，如何求 $a$？

称相邻两个数（不含 $1$ 和 $n$）之和 $<k$ 的序列为「$k$ 序列」，有个牛逼转化：将奇段的所有大数减去 $\left\lceil\dfrac{m}{2}\right\rceil$ 后，与所有的「$m/2$ 序列」一一对应。不妨加一维 $m$，$f_{m,i}$ 表示长为 $i$ 的「$m$ 序列」个数，$a_{m,i}$ 同理，则有 $a_{m,i} = f_{m/2,i}$（注意对 $a_{m,1}$ 并不适用），考虑求 $f$。

序列和环的不同点在于，序列的首尾不一定是奇段：可能是开头形如 $\tt{BSB\dots BS}$，中间一堆奇段，结尾形如 $\tt{SBS\dots SB}$ 的形式。我们把 $\tt{BSB\dots BS}$ 这种 $\tt B$ 开头 $\tt S$ 结尾，且 $\tt BS$ 交替的段叫「偶段」（特别地，偶段可以为空），则序列的组成一定是 偶段 + 若干奇段 + 反的偶段，这让我们想到 GF：不妨设长度为 $i$ 的偶段有 $b_i$ 种方案，则 $F(x) = \dfrac{B(x)^2}{1-A(x)}$。但它是错误的，漏掉了一种情况：$\tt BSB\dots SB$。对于这种情况，容易发现和奇段一一对应，所以 $F(x) = A(x)+\dfrac{B(x)^2}{1-A(x)}$。同样的，上面的牛逼转化对于偶段仍然适用，也就是 $b_{m,i} = f_{m/2,i}$，这样的话可以用 $F_{m/2}$ 推得 $A_m,B_m$，然后推得 $F_m$。

因为 $m$ 每次减半，所以 $F_i$ 只有 $O(\log m)$ 个，复杂度是 $O(n \log n \log m)$。

### Part 2

整个环是 $\tt SB$ 交替的，这种情况只会出现在 $n$ 为偶数时。记 $g_k$ 表示长度为 $n$ 且 $m=k$ 时 $\tt SB$ 交替的序列个数，$ans_k$ 表示 $m=k$ 时的答案。

我们发现将所有大数减去 $\left\lceil\dfrac{m}{2}\right\rceil$ 后，就是一个规模为 $m/2$ 的子问题，所以考虑用 $ans_{m/2}$ 还原回 $g_k$ 的方式：奇数位 $+\left\lceil\dfrac{m}{2}\right\rceil$，或偶数位 $+\left\lceil\dfrac{m}{2}\right\rceil$，故 $g_m = 2\cdot ans_{m/2}$。结合 Part 1 求得的答案 $res_m$ 可以得到 $ans_m=res_m + g_m$，就以 $O(n \log n \log m)$ 的复杂度完成了这道题。


```cpp
int n,m,rs;
poly solve(int m){
	if(!m)return poly(n+1,1);
	poly F=solve(m/2),A(n+1),B(n+1,1);
	FOR(i,1,n)(i&1?A[i]:B[i])=F[i];
	A[1]=(m+1)/2;
	poly I=Inv(poly(1,1)-A);
	F=A+B*B*I,rs=n&1?I[n]:(2ll*rs+I[n])%mod;
	FOR(i,3,n)rs=(rs+(i-1ll)*I[n-i]%mod*A[i])%mod;
	return F.fit(n+1);
}
signed main(){
	scanf("%d%d",&n,&m);
	solve(m),printf("%d",rs);
	return 0;
}
```

---

## 作者：热言热语 (赞：2)

非常有趣的一道多项式科技题。

官方题解的复杂度为 $O(n\log n\log m)$，同时 Elegia 给出了 $O(n\log n)$ 做法。两种做法都非常的 Amazing。

这篇题解主要参考了官方题解的评论中 [Elegia 的做法](https://codeforces.com/blog/entry/95477?#comment-845806) 与 [mmaxio 的解析](https://codeforces.com/blog/entry/95477?#comment-846451)，谨此致谢。

#### 一、$n$ 为偶数

转化题意，令 $b_i=\begin{cases}a_i,&i\bmod2=1\\m-1-a_i,&i\bmod2=0\end{cases}$，只需 $b_i\in[0,m)$ 且 $b_1\le b_2\ge b_3\le\cdots\ge b_{n-1}\le b_n\ge b_1$。

保留所有的 $\le$，对 $\ge$ 进行容斥。先不考虑环的情况，即忽略 $b_n\ge b_1$ 这个条件。

设 $f(k)$ 表示钦定 $k$ 个 $\ge$ 不成立（把 $k$ 个 $\ge$ 改为 $<$，忽略其余的 $\ge$）的方案数，则答案为 $\displaystyle\sum_{k=0}^{\frac n2-1}(-1)^kf(k)$。

在 $f(k)$ 的限制下，$\{b_i\}$ 被分成 $\frac n2-k$ 条形如 $c_1\le c_2<c_3\le\cdots<c_{2l-1}\le c_{2l}$ 的链，且不同链的取值相互独立。容易发现，长度为 $2l$ 的链一共有 $f_l=\dbinom{m+l}{2l}$ 种。

记 $F(z)=\displaystyle\sum_{i=1}^\infty f_iz^i$。如果忽略 $b_n\ge b_1$，则方案数 $f_0(k)=[z^{\frac n2}]F^{\frac n2-k}(z)$，于是答案即为
$$
\begin{aligned}
\sum_{k=0}^{\frac n2-1}(-1)^kf(k)
&=[z^{\frac n2}]\sum_{k=0}^{\frac n2-1}(-1)^kF^{\frac n2-k}(z)\\
&=[z^{\frac n2}]\sum_{k=0}^{\frac n2-1}(-1)^{\frac n2-k-1}F^{k+1}(z)\\
&=(-1)^{\frac n2-1}[z^{\frac n2}]{F(z)\over1+F(z)}
\end{aligned}
$$
现在考虑 $b_n\ge b_1$ 的影响，此时 $b_1$ 所在的链不一定从 $1$ 开始。设这条链的长度为 $2l$，则 $b_1$ 可以是它的第 $1,3,5,\cdots,2l-1$ 个元素，共 $l$ 种可能。此时方案数 $f(k)=[z^{\frac n2-1}]F'(z)F^{\frac n2-k-1}(z)$，于是答案即为 $(-1)^{\frac n2-1}[z^{\frac n2-1}]\dfrac{F'(z)}{1+F(z)}$。

实现上，组合数可以预处理 $n$ 以内阶乘的逆元后递推计算，求出 $F(z)$ 后求逆即可。总时间复杂度 $O(n\log n)$。

#### 二、$n$ 为奇数

记 $m_0=\lfloor\frac m2\rfloor,m_1=\lceil\frac m2\rceil$。若 $a_i<m_1$，则称 $a_i$ 是大的，否则称 $a_i$ 是小的。容易发现相邻的 $a_i$ 不能同时为大的。将 $\{a_i\}$ 视为一个环，则它可以被划分为若干段，每段形如「小大小……小大小」，且每段长度均为奇数。

把所有大的元素减去 $m_1$，于是 $0\le a_i\le m_0$。如果 $a_i=m_0$，则 $m$ 为奇数，$a_i$ 原来是小的元素，且 $a_i$ 两侧均不是大的，即 $a_i=m_0$ 只能在长度为 $1$ 的一段取到，特殊处理即可。

设 $p_d$ 表示长度为 $2d+1$ 的段 $\{b_i\}$ 的方案数。可以发现，问题被转化成类似的形式，而且没有了环的限制。仿照之前的做法，将偶数位的 $b_i\gets m_0-1-b_i$，则只需 $b_i\in[0,m_0)$ 且 $b_1\le b_2\ge b_3\le\cdots\ge b_{2d-1}\le b_{2d}\ge b_{2d+1}$。

同样地，设 $f(k)$ 表示钦定 $k$ 个 $\ge$ 不成立的方案数，则 $p_d=\displaystyle\sum_{k=0}^d(-1)^kf(k)$。

在 $f(k)$ 的限制下，$\{b_i\}$ 同样被分成了 $d-k+1$ 条链。与之前不同的是，最后一条链的长度为奇数 $2l+1$，一共有 $g_l=\dbinom{m_0+l}{2l+1}$ 种。其它链的长度均为偶数，方案数与 $n$ 为偶数且忽略环的情况相同。

记 $G(z)=\displaystyle\sum_{i=0}^\infty g_iz^i$，则 $f(k)=[z^d]F^{d-k}(z)G(z)$（这里的 $F(z)$ 即 $n$ 为偶数情况的），所以 $p_d=(-1)^d[z^d]\dfrac{G(z)}{1+F(z)}$。

记 $P(z)=\displaystyle\sum_{i=0}^\infty p_iz^i={G(-z)\over1+F(-z)}$。注意当 $m$ 为奇数时，$P(z)$ 还要加上 $1z^0$，对应单独一段 $a_i=m_0$ 的情况。

同样地，设 $b_1$ 所在的段的长度为 $2d+1$，则 $b_1$ 可以是它的第 $1,2,3,\cdots,2d+1$ 个元素，共 $2d+1$ 种可能。

记 $Q(z)=\displaystyle\sum_{i=0}^\infty(2i+1)p_iz^i$，则答案为 $\displaystyle[z^{\frac{n-1}2}]Q(z)\sum_{i=0}^\infty z^iP^{2i}(z)=[z^{\frac{n-1}2}]{Q(z)\over1-zP^2(z)}$。这里的 $zP^2(z)$ 是因为总段数一定是奇数，除第一段外剩下偶数段，而长为 $2a+1,2b+1$ 的两段总长为 $2(a+b+1)$，所以还要再乘一个 $z$。

代码实现同 $n$ 为偶数的情况，但多了一些多项式变换。时间复杂度仍为 $O(n\log n)$。

---

## 作者：tzc_wk (赞：0)

[Codeforces 题面传送门](https://codeforces.ml/contest/1580/problem/F) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1580F)

~~好题，可能是这场 div1 质量最高的题（~~

首先思考如何判定一个序列是不是好的，考虑这样一个策略：令 $X=\lceil\dfrac{m}{2}\rceil$，那么如果存在两个相邻的 $\ge X$ 的数那么显然不符合要求，否则我们将环上所有相邻且均 $<X$ 的位置找出来，在所有这样的两个位置之间切一刀，这样可以得到许多段，令 $m\leftarrow\lfloor\dfrac{m}{2}\rfloor$，然后对每一段分别判定即可。

考虑用类似于分治的思想来解决这个问题。即对 $m$ 进行分治。考虑一次分治过程，我们要解决 $m=M$ 时的子问题。方便起见我们假设 $n$ 是奇数，$M$ 是偶数。我们考虑将 $\ge\dfrac{M}{2}$ 的数记作 $1$，将 $<\dfrac{M}{2}$ 的数记作 $0$，那么由于 $n$ 是奇数，必然存在相邻两位置 $i$ 和 $i\bmod n+1$，满足它们都是 $0$。我们按照上面的思路，将序列从所有这样的位置处断开，那么我们肯定会得到若干个连续段，每段内部肯定形如 $010101…10$，不妨假设段长为 $len$（显然，$len$ 应为奇数）。那么显然如果我们将所有 $1$ 的位置上的数都减去 $\dfrac{M}{2}$，我们将得到一个长度为 $len$ 的、且任意相邻两项之和 $<\dfrac{M}{2}$ 的序列（注意：**此处头尾两项不算相邻！**），记这样的序列个数为 $F(\dfrac{M}{2},i)$。

考虑倘若我们已经知道了 $F$，如何求解答案，记 $dp_i$ 表示用长度为奇数且任意相邻两项之和 $<\dfrac{M}{2}$ 的序列 拼成长度为 $i$ 的段的方案数，有 $dp_i=\sum\limits_{j=0}^{i-1}dp_j·F(\dfrac{M}{2},i-j)$，可以使用多项式求逆优化到 $n\log n$。解出 DP 数组后我们枚举 $1$ 所在的段的长度 $l$，显然这一段的起点有 $l$​ 种可能的位置，于是 $ans=\sum\limits_{l=1}^nl·F(\dfrac{M}{2},l)·dp_{n-l}$。

接下来考虑怎么求 $F$，考虑一段长度为奇数且相邻元素之和 $<X$ 的序列怎么构成。我们还是记 $<\dfrac{X}{2}$ 的为 $0$，$\ge\dfrac{X}{2}$ 的为 $1$，那么考虑取出第一个相邻的 $0$（这里，首尾相邻也算相邻，方便后面的计算），那么可以发现，除了开头或结尾都是 $0$ 的情况，其余情况下第一段和最后一段的长度都是偶数，而实际上对于开头或结尾是 $0$ 的情况，我们也可以视作长度为 $0$ 的连续段（毕竟，长度为 $1$ 且唯一的元素为 $1$ 的序列个数，等于长度为 $0$ 的序列个数），也就是说符合条件的序列都可以视作开头一段长度为偶数的连续段，中间若干段长度为奇数的连续段，最后又有一个长度为偶数的连续段。不过仔细想想发现我们漏了一种情况：由于开头和结尾不算相邻，因此对于形如 $101…01$ 的序列，它实际上是符合要求的序列，但由于我们想当然地认为长度为奇数的序列只可能形如 $0101..010$，我们就没有将其统计在内。因此我们考虑分治地计算 $F(\dfrac{X}{2},i)$，如果我们记这部分中下标为奇数部分的 OGF 为 $A$，下标为偶数部分的 OGF 为 $B$，那么 $F(X,i)$ 的 OGF 就是：
$$
\dfrac{1}{1-A}·B^2+A
$$
同样可以 FFT 求。

这样我们就解决了 $n$​ 为奇数，每一步 $M$​ 都是偶数也就是 $m$​ 是 $2$​ 的整数次幂的情况，接下来考虑在原算法的基础上，解决 $n$​ 是偶数或某一步 $M$​ 是奇数的情况。

首先是 $n$ 是偶数的情况，不难发现加上 $n$ 是偶数的时候，“一定存在两个相邻的 $0$”的结论就不一定成立了，这时候有且仅有两种情况会被我们漏算：$1010…10$ 和 $0101…01$，递归的时候额外传个参数记录下这种情况的方案数即可。具体细节见代码。

接下来是某一步 $M$ 是奇数的情况。一个让我们比较为难的地方是，将 $\ge\lceil\dfrac{M}{2}\rceil$ 的数减去 $\lceil\dfrac{M}{2}\rceil$ 后，会导致两边范围不一样，不过仔细想一下就会发现 $\lceil\dfrac{M}{2}\rceil-1$ 这个数很特别：它不能与 $1$ 挨着，因此它只可能出现在长度为 $1$ 的连续段中，因此只用特殊处理下 $F(M,1)$ 即可。

时间复杂度 $n\log n\log m$。

```cpp
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/hash_policy.hpp>
// #include <ext/pb_ds/priority_queue.hpp>
using namespace std;
// using namespace __gnu_pbds;
#define fi first
#define se second
#define fill0(a) memset(a, 0, sizeof(a))
#define fill1(a) memset(a, -1, sizeof(a))
#define fillbig(a) memset(a, 63, sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define mt make_tuple
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
template <typename T1, typename T2> void chkmin(T1 &x, T2 y){
	if (x > y) x = y;
}
template <typename T1, typename T2> void chkmax(T1 &x, T2 y){
	if (x < y) x = y;
}
typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long double ld;
#ifdef FASTIO
namespace fastio {
	#define FILE_SIZE 1 << 23
	char rbuf[FILE_SIZE], *p1 = rbuf, *p2 = rbuf, wbuf[FILE_SIZE], *p3 = wbuf;
	inline char getc() {
		return p1 == p2 && (p2 = (p1 = rbuf) + fread(rbuf, 1, FILE_SIZE, stdin), p1 == p2) ? -1: *p1++;
	}
	inline void putc(char x) {(*p3++ = x);}
	template <typename T> void read(T &x) {
		x = 0; char c = getc(); T neg = 0;
		while (!isdigit(c)) neg |= !(c ^ '-'), c = getc();
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getc();
		if (neg) x = (~x) + 1;
	}
	template <typename T> void recursive_print(T x) {
		if (!x) return;
		recursive_print (x / 10);
		putc (x % 10 ^ 48);
	}
	template <typename T> void print(T x) {
		if (!x) putc('0');
		if (x < 0) putc('-'), x = -x;
		recursive_print(x);
	}
	template <typename T> void print(T x,char c) {print(x); putc(c);}
	void readstr(char *s) {
		char c = getc();
		while (c <= 32 || c >= 127) c = getc();
		while (c > 32 && c < 127) s[0] = c, s++, c = getc();
		(*s) = 0;
	}
	void printstr(string s) {
		for (int i = 0; i < s.size(); i++) putc(s[i]);
	}
	void printstr(char *s) {
		int len = strlen(s);
		for (int i = 0; i < len; i++) putc(s[i]);
	}
	void print_final() {fwrite(wbuf, 1, p3 - wbuf, stdout);}
}
using namespace fastio;
#endif
const int MAXN = 50000;
const int MAXP = 262144;
const int pr = 3;
const int ipr = 332748118;
const int MOD = 998244353;
int n, m;
typedef vector<int> vi;
void add(int &x, int y) {((x += y) >= MOD) && (x -= MOD);}
int qpow(int x, int e) {
	int ret = 1;
	for (; e; e >>= 1, x = 1ll * x * x % MOD)
		if (e & 1) ret = 1ll * ret * x % MOD;
	return ret;
}
int rev[MAXP + 5], LEN;
void FFT(vi &a, int len, int type) {
	int lg = 31 - __builtin_clz(len);
	for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << lg - 1);
	for (int i = 0; i < len; i++) if (rev[i] < i) swap(a[rev[i]], a[i]);
	static int W[MAXP + 5];
	for (int i = 0; i < len; i++) W[i] = 0; W[0] = 1;
	for (int i = 2; i <= len; i <<= 1) {
		int wW = qpow((type < 0) ? ipr : pr, (MOD - 1) / i);
		for (int j = (i >> 1) - 1; ~j; j--) W[j] = (j & 1) ? (1ll * W[j >> 1] * wW % MOD) : W[j >> 1];
		for (int j = 0; j < len; j += i) {
			for (int k = 0; k < (i >> 1); k++) {
				int X = a[j + k], Y = 1ll * W[k] * a[(i >> 1) + j + k] % MOD;
				a[j + k] = (X + Y) % MOD; a[(i >> 1) + j + k] = (X - Y + MOD) % MOD;
			}
		}
	}
	if (type < 0) {
		int ivn = qpow(len, MOD - 2);
		for (int i = 0; i < len; i++) a[i] = 1ll * a[i] * ivn % MOD;
	}
}
vi conv(vi a, vi b) {
	int LEN = 1; while (LEN < a.size() + b.size()) LEN <<= 1;
	a.resize(LEN, 0); b.resize(LEN, 0); FFT(a, LEN, 1); FFT(b, LEN, 1);
	for (int i = 0; i < LEN; i++) a[i] = 1ll * a[i] * b[i] % MOD;
	FFT(a, LEN, -1); return a;
}
vi getinv(vi a, int len) {
	vi b(len, 0); b[0] = qpow(a[0], MOD - 2);
	for (int i = 2; i <= len; i <<= 1) {
		vi c(b.begin(), b.begin() + (i >> 1));
		vi d(a.begin(), a.begin() + i);
		c = conv(c, c); d = conv(c, d);
		for (int j = 0; j < i; j++) b[j] = (2 * b[j] % MOD - d[j] + MOD) % MOD;
	}
	return b;
}
pair<vi, pii> solve(int x) {
	if (x == 1) {
		vector<int> F(n + 1);
		for (int i = 0; i <= n; i++) F[i] = 1;
		return mp(F, mp(1, 0));
		// se.fi: num of seqs with at least one adjacent numbers < floor(x/2)
		// se.se: num of seqs with no one adjacent numbers < floor(x/2)
	}
	auto T = solve(x >> 1);
	vi _F = T.fi, F(n + 1), odd(LEN), even(n + 1);
	_F[1] = x + 1 >> 1; odd[0] = 1;
	for (int j = 0; j <= n; j++) if (j & 1) odd[j] = (MOD - _F[j]) % MOD;
	vector<int> H = getinv(odd, LEN);
	for (int j = 0; j <= n; j++) if (~j & 1) even[j] = _F[j];
	vector<int> mul = conv(conv(even, even), H);
	for (int j = 0; j <= n; j++) F[j] = (mul[j] + ((j & 1) ? _F[j] : 0)) % MOD;
	int ss1 = 0, ss2 = 2ll * (T.se.fi + T.se.se) % MOD;
	for (int j = 1; j <= n; j++) if (j & 1) ss1 = (ss1 + 1ll * _F[j] * j % MOD * H[n - j]) % MOD;
	return mp(F, mp(ss1, ss2));
}
int main() {
	scanf("%d%d", &n, &m); LEN = 1; while (LEN <= n + n) LEN <<= 1;
	auto T = solve(m); printf("%d\n", (T.se.fi + (~n & 1) * T.se.se) % MOD);
	return 0;
}
```



---

