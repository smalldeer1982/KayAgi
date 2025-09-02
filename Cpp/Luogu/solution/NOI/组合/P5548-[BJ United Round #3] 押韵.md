# [BJ United Round #3] 押韵

## 题目背景

韵要怎么押？棋要怎么下？敌要怎么杀？旗要怎么插？

## 题目描述

现在你想要写一首歌词，一共有 $nd$ 个字，你一共设计了 $k$ 种韵脚，每个字恰好要符合一种韵脚。  

并且只有当每种韵脚在歌词中出现的字数恰为 $d$ 的倍数时，这首歌才好听。

试问一共有多少种韵脚的搭配方法，使得歌词好听？

你只需要回答方案数对于 $1049874433$ 取模的结果即可。

## 说明/提示

对于 $100\%$ 的数据，保证：  
$0 \le n \le 10^9$  
$1\le k \le 2000$  
$d\in \{ 1,2,3,4,6 \}$

By：EntropyIncreaser

## 样例 #1

### 输入

```
2 2 2```

### 输出

```
8```

## 样例 #2

### 输入

```
2 3 4```

### 输出

```
213```

## 样例 #3

### 输入

```
2 4 6```

### 输出

```
5548```

# 题解

## 作者：Elegia (赞：14)


事实上本题是 [UOJ #450. 【集训队作业2018】复读机](http://uoj.ac/problem/450) 的一个加强版。

#### 算法一

$n\le 5\times 10^4$，我可以做多项式快速幂！这个多项式就是 $(\sum_{j\ge 0} \frac{x^{jd}}{(jd)!})^k$。这个模数不太友好，你可能需要 MTT……常数应该很大。

时间复杂度 $\Theta(n\log n) \sim \Theta(n\log n \log k)$，前者是进行多项式 $\ln , \exp$ 达到的复杂度，但是常数可能很大。

预计得分 $20\%$。

#### 算法二

我们考察 $(\sum_{j\ge 0} \frac{x^{jd}}{(jd)!})^k$ 可以如何表示。

事实上与周期函数有关的，我们可以自然想到类似 DFT 的形式，也就是考虑到 $\sum_{j=0}^{d - 1} \omega_d^{cj} = d[d | c]$，因此我们可以知道上面的那个多项式实际上是

$$
\frac1d \sum_{j=0}^{d-1} \exp \omega_d^j x
$$

我们直接枚举拆括号的过程中计算了几个 $\exp \omega_d^0 x$，几个 $\exp \omega_d^1 x$……然后这一部分的贡献就是 $(c_0 + c_1 \omega_d^1 + c_2 \omega_d^2 + \dots)^n$。最后总和除以 $d^k$。

时间复杂度 $\Theta(k^{d-1}\log n)$，预计得分 $50\%$。

#### 算法三



主要思想还是围绕优化计算下式：


$$
[x^n]\left( \frac1d \sum_{j=0}^{d-1} \exp \omega_d^j x  \right)^k
$$


对于 $d=4$ 的情况，我们实际上是只需要统计每个 $\exp (a + b\mathrm{i})x$ 出现多少次。通过推导一些式子，或者直接将复平面旋转 $45^\circ$ 我们可以得到，方案数是 $\displaystyle\binom{k}{\frac{k + |a+b|}2} \binom{k}{\frac{k + |a-b|}2}$。因此答案可以在 $\Theta(k^2 \log n)$ 内计算出来。

预计得分 $70\%$。

#### 算法四




对于 $d=6$ 的情况，我们注意到 $\omega_6$ 的代数关系有 $\omega - 1 = \omega^2$，因此所有的根都可以用 $1, \omega$ 表示，即给每个数赋予了一个离散的二维坐标

$$ \begin{array}{clclc} \omega^0 & = & 1  &   &         \\\omega^1 & = &    &   & \omega\\\omega^2 & = & -1 & + & \omega\\\omega^3 & = & -1 &   &         \\\omega^4 & = &    &   &-\omega\\\omega^5 & = & 1  & + &-\omega\end{array} $$

因此我们只需要做一个二维的快速幂，倍增 FFT 可以做到 $\Theta(k^2 \log k)$。但是常数可能较大。

预计得分 $80\% \sim 100\%$。

#### 算法五

考虑计算一个二元母函数的高阶幂，$G(x, y) = F(x, y)^k$，可以得到 $F \frac{\partial G}{\partial_x} = kG \frac{\partial F}{\partial_x}$，由此可列得递推式子解出所有系数。计算高阶幂的复杂度是 $\Theta(k^2)$ 的。复杂度 $\Theta(k^2 \log n)$ 且常数较小。

事实上这也是可以直接用来做 $k=4$ 的情况的。

预计得分 $100\%$。

#### further

对于更大的 $d$，我们期望能得到一个怎样的做法？考虑 $d$ 次单位根的代数关系，我们希望能够基于一个它们的有理系数线性组合的基。由此则能将维度缩到基的维度，在其上进行快速幂。

我将说明维度可以达到 $\varphi(d)$，而数学迷告诉我说通过一些关于域的理论可以证明这也是下界，~~等我学了之后补一下证明~~。

考虑分圆多项式 $\Phi_d(x) = \prod_{0\le k < d, \gcd(d, k) = 1} (x - \omega_d^k)$，它的次数显然是 $\varphi(d)$。

显然分圆多项式也可以用容斥原理重写，即

$$\Phi_d(x) = \prod_{k|d} (x^{d/k}-1)^{\mu(k)} $$

显然该多项式的系数都是整数。由于 $\Phi_d(\omega_d) = 0$，不难得到 $\omega_d^k = \left.x^k \bmod \Phi_d\right \vert_{x=\omega}$。因此这个多项式的取模自然而然地导出了每个单位根到 $1, \omega_d, \dots, \omega_d^{\varphi(d) - 1}$ 的线性组合。


---

## 作者：Karry5307 (赞：8)

### 题意

略。

$\texttt{Data Range:}1\leq n\leq 10^9,1\leq k\leq 2\times 10^3,d\in\{1,2,3,4,6\}$。

### 题解

$d=6$ 有意思，其他的比较套路。

下面的 $n$ 代指题意中的 $nd$。

首先将答案的 EGF 表示出来：

$$\left(\sum\limits_{i}\frac{x^{id}}{(id)!}\right)^k$$

$d=1$ 很显然就不说了，否则可以将括号内的式子单位根反演（为了方便，下文用 $\omega$ 表示 $\omega_d$）：

$$\frac{1}{d^k}\left(\sum\limits_{i=0}^{d-1}e^{\omega^ix}\right)^k$$

当 $d=2$ 时有：

$$n![x^n](e^x+e^{-x})^k=n!\sum\limits_{i}\binom{k}{i}[x^n]e^{2i-k}=\sum\limits_{i=0}^{k}\binom{k}{i}(2i-k)^n$$

当 $d=3$ 时有：

$$n![x^n](e^x+e^{\omega x}+e^{\omega^2x})=\sum\limits_{i}\sum\limits_{j}\binom{k}{i}\binom{k-i}{j}(i+j\omega+(k-i-j)\omega^2)^n$$

由于 $3$ 和 $-1$ 在模意义下有二次剩余所以可以直接算。

当 $d=4$ 时有：

$$n![x^n](e^x+e^{\omega x}+e^{\omega^2 x}+e^{\omega^3 x})=\sum\limits_{i}\sum\limits_{j}\sum\limits_{l}\binom{k}{i}\binom{k-i}{j}\binom{k-i-j}{l}((i-l)+(i+2j+l-k)\omega)^k$$

这个时候直接枚举是 $O(k^3)$ 的，注意到如果设 $A=i+j,B=l+j$，则被求和部分的单位根那一部分可以表示成 $(A-B)+(A+B-k)\omega$。

通过打表可以大胆猜想前面的系数为 $\dbinom{k}{A}\dbinom{k}{B}$（只是因为我不会从代数意义上证明，但这个可以直接将复平面转 $45\degree$ 得到），则

$$\sum\limits_{i}\sum\limits_{j}\sum\limits_{l}\binom{k}{i}\binom{k-i}{j}\binom{k-i-j}{l}((i-l)+(i+2j+l-k)\omega)^n=\sum\limits_{A}\sum\limits_{B}\binom{k}{A}\binom{k}{B}((A-B)+(A+B-k)\omega)^n$$

即可 $O(k^2)$。

对于 $d=6$ 的时候，直接枚举是 $O(k^5)$ 的，即使猜测系数简化变量的个数也是 $O(k^3)$ 的，这启发我们想一个别的方法。

类似于 $d=4$ 的情况，不枚举六个变量，枚举一个复数 $a+b\mathrm{i}$ 之后算系数即可，但是怎么算系数呢？

直接考虑 $\omega$ 之间的代数关系有 $\omega-1=\omega^2$，所以有：

$$\omega^0=1,\omega^1=\omega,\omega^2=\omega-1,\omega^3=-1,\omega^4=-\omega,\omega^5=1-\omega$$

这个时候可以考虑给每一个 $\omega$ 对应一个离散的坐标，然后变成到达某一个值（对应 $a+b\mathrm{i}$）的方案数。

这个时候做二维的多项式快速幂即可，但是可能有些卡常。

考虑设 $G(x,y)=F^k(x,y)$，则对 $x$ 求偏导有：

$$\frac{\partial G}{\partial x}=k\frac{\partial F}{\partial x}F^{k-1}$$

然后两遍同时乘上 $F$ 得到：

$$F\frac{\partial G}{\partial x}=kG\frac{\partial F}{\partial x}$$

比较系数之后递推即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=4e3+51,MOD=1049874433,INV2=524937217,INV3=699916289;
const ll SQRT3=168679641,I=227660408;
ll kk,d,res;
li n;
ll fact[MAXN],finv[MAXN];
inline ll read()
{
	register ll num=0,neg=1;
	register char ch=getchar();
	while(!isdigit(ch)&&ch!='-')
	{
		ch=getchar();
	}
	if(ch=='-')
	{
		neg=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		num=(num<<3)+(num<<1)+(ch-'0');
		ch=getchar();
	}
	return num*neg;
}
inline ll qpow(ll base,li exponent)
{
	ll res=1;
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
inline void setup(ll cnt)
{
	fact[0]=fact[1]=finv[0]=1;
	for(register int i=2;i<=cnt;i++)
	{
		fact[i]=(li)fact[i-1]*i%MOD;
	}
	finv[cnt]=qpow(fact[cnt],MOD-2);
	for(register int i=cnt-1;i;i--)
	{
		finv[i]=(li)finv[i+1]*(i+1)%MOD;
	}
}
inline ll binom(ll m,ll n)
{
	return (li)fact[m]*finv[n]%MOD*finv[m-n]%MOD;
}
namespace Subtask2{
	inline void main()
	{
		for(register int i=0;i<=kk;i++)
		{
			res=(res+(li)binom(kk,i)*qpow(2*i-kk,n))%MOD;
		}
		printf("%d\n",(li)res*qpow(INV2,kk)%MOD);
	}
}
namespace Subtask3{
	ll w1=((li)SQRT3*I-1)%MOD*INV2%MOD,w2=MOD-((li)SQRT3*I+1)%MOD*INV2%MOD;
	ll cof,r;
	inline void main()
	{
		for(register int i=0;i<=kk;i++)
		{
			for(register int j=0;j<=kk-i;j++)
			{
				r=(i+(li)w1*j+(li)w2*(kk-i-j))%MOD;
				cof=(li)binom(kk,i)*binom(kk-i,j)%MOD;
				res=(res+(li)qpow(r,n)*cof)%MOD;
			}
		}
		printf("%d\n",(li)res*qpow(INV3,kk)%MOD);
	}
}
namespace Subtask4{
	ll cof,r;
	ll rr[MAXN];
	inline void main()
	{
		for(register int i=0;i<=kk;i++)
		{
			rr[i]=binom(kk,i);
		}
		for(register int i=0;i<=kk;i++)
		{
			for(register int j=0;j<=kk;j++)
			{
				cof=(li)rr[i]*rr[j]%MOD,r=((i-j+MOD)+(li)(i+j-kk+MOD)*I)%MOD;
				res=(res+(li)qpow(r,n)*cof)%MOD;
			}
		}
		printf("%d\n",(li)res*qpow((li)INV2*INV2%MOD,kk)%MOD);
	}
}
namespace Subtask5{
	ll cof,res,g=72193120;
	ll f[MAXN][MAXN];
	inline void main()
	{
		for(register int i=0;i<=kk;i++)
		{
			f[i][kk-i]=binom(kk,i);
		}
		for(register int i=kk+1;i<=2*kk;i++)
		{
			f[i][0]=f[0][i]=binom(kk,i-kk);
		}
		for(register int i=1;i<=2*kk;i++)
		{
			for(register int j=max(kk-i+1,1);j<=2*kk;j++)
			{
				f[i][j]=(li)(kk-i+1)*(f[i-1][j+1]+f[i-1][j-1])%MOD;
				if(i>1)
				{
					cof=(li)(kk*2+2-i)*(f[i-2][j+1]+f[i-2][j])%MOD;
					f[i][j]=(f[i][j]+cof)%MOD;
				}
				f[i][j]=(f[i][j]-(li)i*f[i][j-1]%MOD+MOD)%MOD;
				f[i][j]=(li)f[i][j]*finv[i]%MOD*fact[i-1]%MOD;
			}
		}
		for(register int i=0;i<=2*kk;i++)
		{
			for(register int j=0;j<=2*kk;j++)
			{
				if(f[i][j])
				{
					cof=qpow((i-kk+(li)(j-kk+MOD)*g%MOD+MOD)%MOD,n);
					res=(res+(li)f[i][j]*cof%MOD)%MOD;
				}
			}
		}
		printf("%d\n",(li)res*qpow((li)INV2*INV3%MOD,kk)%MOD);
	}
}
int main()
{
	n=read(),kk=read(),d=read(),setup(kk*2+10),n*=d;
	if(d==1)
	{
		return printf("%d\n",qpow(kk,n)),0;
	}
	if(d==2)
	{
		return Subtask2::main(),0;
	}
	if(d==3)
	{
		return Subtask3::main(),0;
	}
	if(d==4)
	{
		return Subtask4::main(),0;
	}
	if(d==6)
	{
		return Subtask5::main(),0;
	}
}
```

---

## 作者：iostream (赞：8)

简要讲一些细节部分，大体思路 EI 题解说的很清楚。

第一个是 $d=4$ 时组合数的推导。

首先问题模型是按顺序执行恰好 $k$ 个向量 $t\in \{(1,0),(-1,0),(0,1),(0,-1)\}$ ，求到达 $(a,b)$ 的方案数。

我们把坐标系选择 $45\degree$，并且放大 $\sqrt 2$ 倍，这样一来 $(a,b)\rightarrow (a+b,a-b)$，我们的移动向量变成了 $\{(1,1),(-1,-1),(-1,1),(1,-1)\}$ 于是就有两维独立，算出两维分别等于 $a$、$b$ 的方案相乘即可。

选 $k$ 个 $±1$ 和为 $a$ 的方案可以直接组合数。

第二个是 $d=6$ 时的递推方法。

问题模型是按顺序执行恰好 $k$ 个向量 $t\in \{(1,0),(-1,0),(-1,1),(0,1),(0,-1),(1,-1)\}$ ，求到达 $(a,b)$ 的方案数。

有负数不好进行生成函数操作，于是你把统一 +1 变成 $\{(2,1),(0,1),(0,2),(1,2),(1,0),(2,0)\}$。

现在相当于求 $F(x,y)=y+y^2+x+xy^2+x^2+xy,G(x,y)=F(x,y)^k$ 的所有系数。

对 $x$ 求导得 $G'(x,y)=kF'(x,y)F(x,y)^{k-1}$ 同乘以 $F(x,y)$ 得到 
$$F(x,y)G'(x,y)=kF'(x,y)G(x,y)$$
然后比较等式两边的 $[x^ny^m]$ 系数以列出方程如下：

$$n[x^n y^m ]+n[x^n y^{m-2} ]+(n-1)[x^{n-1} y^m ]+(n-1)[x^{n-1}y^{m-1}]+(n+1)[x^{n+1}y^{m-1}]+(n+1)[x^{n+1}y^{m-2}]=k[x^ny^m]+2k[x^{n-1}y^m]+2k[x^{n-1}y^{m-1}]+k[x^ny^{m-2}]$$

这个方程涉及的未知数位置关系大概长这样：

```
oo.
o.o
.oo
```

然后你要递推需要的边界有 $[i,0]=[0,i]={k\choose i-k} (i\ge k), [i,k-i]={k\choose i} (i\le k)$。

一开始我是想从最上面开始推，然后发现会出现分母等于 $0$。
然后一种可行的推法按 $n$ 递增、$m$ 递增的顺序推，用上面的方程每次解出 $[x^{n+1}y^{m-1}]$ 即可。

---

## 作者：DaiRuiChen007 (赞：4)

# P5548 题解

[Problem Link](https://www.luogu.com.cn/problem/P5548)

**题目大意**

> 给一个长度为 $n\times d$ 的序列，每个位置有 $k$ 种颜色可选，求有多少种染色方案使得每种颜色出现次数都是 $d$ 的倍数。
>
> 数据范围：$n\le 10^9,k\le 2000,d\in\{0,1,2,3,4,6\}$。

**思路分析**

以下题解中的 $n$ 均指原题中的 $n\times d$，$\omega$ 均指 $\omega _d$。

考虑指数型生成函数，容易写出：
$$
\mathrm{ans}=n![x^n]\left(\sum_{i=0}^\infty[d\mid i]\dfrac{x^i}{i!}\right)^k
$$
注意到 $[d\mid i]$ 这个条件很特殊，考虑单位根反演：$\sum_{i=0}^{d-1}\omega^{id}=d\times [d\mid i]$ 得到：
$$
\begin{aligned}
\mathrm{ans}
&=n![x^n]\left(\sum_{i=0}^\infty\dfrac{x^i}{i!}\dfrac 1d\sum_{j=0}^{d-1}\omega^{ij}\right)^k\\
&=\dfrac{n!}{d^k}[x^n]\left(\sum_{j=0}^{d-1}\sum_{i=0}^\infty\dfrac{x^i}{i!}\omega^{ij}\right)^k\\
&=\dfrac{n!}{d^k}[x^n]\left(\sum_{j=0}^{d-1}\exp(x\omega^j)\right)^k
\end{aligned}
$$
$d=1$ 的情况是显然的，答案为 $k^n$。

然后考虑 $d=2$ 的情况，那么相当于求：$[x^n](e^{-x}+e^x)^k$，暴力把后面的 $k$ 次幂二项式定理展开得到：
$$
\begin{aligned}
\mathrm{ans}
&=\dfrac{n!}{d^k}[x^n](e^{-x}+e^x)^k\\
&=\dfrac{n!}{d^k}\sum_{i=0}^n \binom ki [x^n]e^i\times e^{-(k-i)}\\
&=\dfrac{n!}{d^k}\sum_{i=0}^n \binom ki \dfrac{(2i-k)^n}{n!}\\
&=\dfrac 1{d^k}\sum_{i=0}^n \binom ki(2i-k)^n
\end{aligned}
$$
然后考虑 $d=3$ 的情况，同样暴力拆开得到：
$$
\mathrm{ans}=\dfrac{1}{d^k}\sum_{x+y+z=k}\binom k{x,y,z}(x+y\omega+z\omega^2)^n
$$
暴力计算复杂度是 $\mathcal O(k^{d-1}\log n)$ 的，对于 $d\ge 4$ 的情况就比较困难了。

对于 $d=4$ 的情况，我们要求的值是 $[x^n](e^x+e^{ix}+e^{-x}+e^{-ix})^k$，类似上面的推导，我们得到：
$$
\mathrm{ans}=\dfrac1{d^k}\sum_{x+y+z+w=k}\binom{k}{x,y,z,w}[(x-z)+(y-w)i]^n
$$
一个很自然的想法是枚举 $a=x-z,b=y-w$，然后算出前面的系数 $f_{a,b}$ 是多少。

考虑组合意义，相当于在二维平面上游走 $k$ 步后到达 $(a,b)$ 的方案数。

考虑二元 GF，设 $G(x,y)=x+y+x^{-1}+y^{-1}$，那么答案就是 $F(x,y)=G^k(x,y)$ 的 $x^ay^b$ 项系数。

注意到对于这种 $F=G^k$ 的形式，我们常用的一个办法是求导，这里改成求对 $x$ 的偏导，得到：
$$
\begin{aligned}
F&=G^k\\
\dfrac{\delta F}{\delta x}&=kG^{k-1}\times \dfrac{\delta G}{\delta x}\\
G\times \dfrac{\delta F}{\delta x}&=kF\times \dfrac{\delta G}{\delta x}
\end{aligned}
$$
其中第三步是两边同时 $\times G$ 然后用 $F$ 替换 $G^k$ 得到的。

注意到 $\dfrac{\delta G}{\delta x}=1-x^{-2}$，带入后比较两边 $x^ay^b$ 系数得到：
$$
af_{a,b}+(a+1)f_{a+1,b-1}+(a+2)f_{a+2,b}+(a+1)f_{a+1,b+1}=k(f_{a,b}-f_{a+2,b})
$$
用 $f(a+2,b)$ 作为主元，得到递推：
$$
(k+i)f_{i,j}=(k-i+2)f_{i-2,j}-(i-1)(f_{i-1,j-1}+f_{i-1,j+1})
$$
边界条件为 $f_{-k,0}=1$。

然后考虑 $d=6$ 的情况，类似上面的思路，用 $1,\omega$ 表示其他单位根得到 $(1,\omega,\omega-1,-1,-\omega,\omega-1)$。

然后观察 $[x^n](e^x+e^{\omega x}+e^{(\omega -1)x}+e^{-x}+e^{-\omega x}+e^{(\omega -1)x})$ 的展开式，枚举 $(a+b\omega)^n$ 的系数 $f_{a,b}$。

设 $G(x,y)=x+y+x^{-1}+y^{-1}+xy^{-1}+x^{-1}y$，然后依然求偏导得到 $\dfrac{\delta G}{\delta x}=1-x^{-2}+y^{-1}-x^{-2}y$。

根据 $G\times \dfrac{\delta F}{\delta x}=kF\times \dfrac{\delta G}{\delta x}$ 比较两侧系数得到：
$$
af_{a,b}+(a+1)f_{a+1,b-1}+(a+2)f_{a+2,b}+(a+1)f_{a+1,b+1}+(a+2)f_{a+2,b-1}+af_{a,b+1}=k(f_{a,b}-f_{a+2,b}-f_{a+2,b-1}+f_{a,b+1})
$$
然后以 $f_{i,j}=f_{a+2,b}$ 作为主元得到递推式：
$$
f_{i,j}=(k-i+2)(f_{i-2,j}+f_{i-2,j+1})-(i-1)(f_{i-1,j-1}+f_{i-1,j+1})-(k+i)f_{i,j-1}
$$
边界条件为 $f_{-k,j}=\binom kj$。

暴力计算出系数即可递推，由于题目保证了 $d\mid P-1$，因此所有单位根都可以直接计算。

时间复杂度 $\mathcal O(k^2\log n)$。

**代码呈现**

本题轻微卡常，实际代码用了 `atcoder::modint` 才通过，这里放出没有使用 `modint` 优化的版本。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2005,MOD=1049874433,G=7;
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1; a=(a%MOD+MOD)%MOD;
	for(;b;a=a*a%p,b>>=1) if(b&1) ret=ret*a%p;
	return ret;
}
ll n,k,d,fac[MAXN],ifac[MAXN],inv[MAXN<<1];
ll binom(ll a,ll b) { return fac[a]*ifac[b]%MOD*ifac[a-b]%MOD; }
namespace D1 { ll main() { return ksm(k,n); } }
namespace D2 {
ll main() {
	ll ans=0;
	for(int i=0;i<=k;++i) {
		ans=(ans+binom(k,i)*ksm(2*i-k,n))%MOD;
	}
	return ans*ksm(ksm(d),k)%MOD;
}
}
namespace D3 {
ll main() {
	ll ans=0,w=ksm(G,(MOD-1)/d);
	for(int x=0;x<=k;++x) for(int y=0;y<=k-x;++y) {
		int z=k-x-y;
		ans=(ans+binom(k,x)*binom(k-x,y)%MOD*ksm(x+y*w+z*w%MOD*w,n))%MOD;
	}
	return ans*ksm(ksm(d),k)%MOD;
}
}
namespace D4 {
ll rem[MAXN<<1][MAXN<<1];
ll& f(int i,int j) {
	if(i<-k||i>k||j<-k||j>k) return rem[0][0];
	return rem[i+MAXN][j+MAXN];
}
ll main() {
	ll ans=0,w=ksm(G,(MOD-1)/d); f(-k,0)=1;
	for(int i=-k+1;i<=k;++i) for(int j=abs(i)-k;j<=k-abs(i);++j) {
		f(i,j)=(f(i,j)+(k-i+2)*f(i-2,j))%MOD;
		f(i,j)=(f(i,j)+MOD-(i-1)*(f(i-1,j-1)+f(i-1,j+1))%MOD)%MOD;
		f(i,j)=f(i,j)*inv[k+i]%MOD;
	}
	for(int i=-k;i<=k;++i) for(int j=-k;j<=k;++j) if(f(i,j)) {
		ans=(ans+f(i,j)*ksm(i+j*w,n))%MOD;
	}
	return ans*ksm(ksm(d),k)%MOD;
}
}
namespace D6 {
ll rem[MAXN<<1][MAXN<<1];
ll& f(int i,int j) {
	if(i<-k||i>k||j<-k||j>k) return rem[0][0];
	return rem[i+MAXN][j+MAXN];
}
ll main() {
	ll ans=0,w=ksm(G,(MOD-1)/d);
	for(int i=0;i<=k;++i) f(-k,i)=binom(k,i);
	for(int i=-k+1;i<=k;++i) for(int j=-k;j<=k;++j) {
		f(i,j)=(f(i,j)+(k-i+2)*(f(i-2,j)+f(i-2,j+1)))%MOD;
		f(i,j)=(f(i,j)+MOD-(i-1)*(f(i-1,j-1)+f(i-1,j+1))%MOD)%MOD;
		f(i,j)=(f(i,j)+MOD-(k+i)*f(i,j-1)%MOD)%MOD;
		f(i,j)=f(i,j)*inv[k+i]%MOD;
	}
	for(int i=-k;i<=k;++i) for(int j=-k;j<=k;++j) if(f(i,j)) {
		ans=(ans+f(i,j)*ksm(i+j*w,n))%MOD;
	}
	return ans*ksm(ksm(d),k)%MOD;
}
}
signed main() {
	scanf("%lld%lld%lld",&n,&k,&d),n*=d;
	for(int i=fac[0]=ifac[0]=1;i<=k;++i) ifac[i]=ksm(fac[i]=fac[i-1]*i%MOD);
	for(int i=0;i<=2*k;++i) inv[i]=ksm(i);
	if(d==1) printf("%lld\n",D1::main());
	if(d==2) printf("%lld\n",D2::main());
	if(d==3) printf("%lld\n",D3::main());
	if(d==4) printf("%lld\n",D4::main());
	if(d==6) printf("%lld\n",D6::main());
	return 0;
}
```

---

## 作者：intemist (赞：0)

$k\in\{1,2,3\}$ 见[「集训队作业2018」复读机](https://uoj.ac/problem/450)，以下令新的 $n$ 为 $nd$。

对于 $d=4$，同 $d=3$，单位根反演完需要求 $\dfrac{1}{4^k}\left[\dfrac{x^n}{n!}\right]\left(\sum\limits_{i=0}^3e^{\omega_4^ix}\right)^k$。因为 $\omega_4^0=-\omega_4^2,\omega_4^1=-\omega_4^3$，所以可以简化成两个基。一种做法是看成坐标轴上行走，把 $x,y$ 搞独立了直接枚举终点。或者直接写出二元 GF：$F(x,y)=x+y+x^{-1}+y^{-1}$，需要求出 $G=F^k$ 的所有系数，类似短多项式求幂，两边对 $x$ 求偏导：
$$
\begin{aligned}
	G&=F^k\\
	\dfrac{\partial G}{\partial x}&=k\dfrac{\partial F}{\partial x}F^{k-1}\\
	\dfrac{\partial G}{\partial x}F&=k\dfrac{\partial F}{\partial x}G
\end{aligned}
$$
尝试列出两边 $x^ny^m$ 的系数（弃用了题目中的 $n$）：
$$
\begin{aligned}
	nG_{n,m}+(n+2)G_{n+2,m}+(n+1)(G_{n+1,m-1}+G_{n+1,m+1})=k(G_{n,m}-G_{n+2,m})\\
	(n+2+k)G_{n+2,m}=(k-n)G_{n,m}-(n+1)(G_{n+1,m-1}+G_{n+1,m+1})\\
	G_{n,m}=\dfrac{(k-n+2)G_{n-2,m}-(n-1)(G_{n-1,m-1}+G_{n-1,m+1})}{n+k}
\end{aligned}
$$
可以递推了，$d=6$ 也是类似的。

---

