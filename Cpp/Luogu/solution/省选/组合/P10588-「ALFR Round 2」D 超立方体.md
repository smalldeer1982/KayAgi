# 「ALFR Round 2」D 超立方体

## 题目背景

>  映入眼帘的是一棵硕大的樱花树。   
>
> 树下站着一个少女，她正抬头仰望着那棵樱花树。  
> 我想：她是位新生吧，大概和我一样也是溜出来的。  
> 我也抬着头望了望那棵樱花树。模模糊糊的花色遮住了天空。  
> 刮起一阵风，飘舞着的樱花花瓣将少女裹住。  
> 少女也看到了我……

## 题目描述

那是你与米尔嘉最初的邂逅。  

一如既往，米尔嘉又给你出了一道数列题。  
洁白的信封上留着柑橘的芳香，  
你小心翼翼地拆开信封阅读。

------------

在三维中，我们有三维立方体。  
它的 $2^3$ 个点的坐标都可以写成 $(x,y,z)$ 的形式。  

同理在 $n$ 维中，我们有 $n$ 维超立方体，它有 $2^n$ 个点。  
其棱长为 $1$，且所有顶点的各维坐标都是非负整数。

我们从点 $(0,0,\dots,0)$ 出发，走过 $m$ 条棱，求到达点 $(1,1,\dots,0)$ 的方案总数。

其中要到达的点的坐标中有 $l$ 个数字 $1$。

由于答案可能很大，你只需要输出方案数对 $998244353$ 取模后的结果就可以了。

## 说明/提示

### 样例解释

第一个例子中的 $7$ 种方案分别是：

- $(0,0,0) \to (1,0,0) \to (0,0,0) \to (1,0,0)$
- $(0,0,0) \to (0,1,0) \to (0,0,0) \to (1,0,0)$
- $(0,0,0) \to (0,0,1) \to (0,0,0) \to (1,0,0)$
- $(0,0,0) \to (1,0,0) \to (1,1,0) \to (1,0,0)$
- $(0,0,0) \to (1,0,0) \to (1,0,1) \to (1,0,0)$
- $(0,0,0) \to (0,1,0) \to (1,1,0) \to (1,0,0)$
- $(0,0,0) \to (0,0,1) \to (1,0,1) \to (1,0,0)$

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $10$ | $\sum nm\le2^{26}$，$n\le2^{13}$ |
| $1$ | $20$ | $l=0$ |
| $2$ | $30$ | $\sum n^2\le2^{26}$ |
| $3$ | $40$ | - |

对于 $100\%$ 数据，$1\le T\le600$，$\sum n\log_2 n\le2^{25}$，$n\in[1,2^{21}]$，$m\in[0,2^{64}-1]$，$l\in[0,n]$。

---

你翻到背面，发现一行小字：

请不要忘记考虑特殊情形。

## 样例 #1

### 输入

```
5
3 3 1
3 4 0
114 514 86
19198 10101 7211
604800 4089470473293004800 443520 ```

### 输出

```
7
21
191637399
939162608
305624040```

# 题解

## 作者：NaCly_Fish (赞：20)

在任意位置上时，都有 $n$ 条棱可以选择走，对应了改变 $n$ 维坐标中任意一个的状态。

所以稍微转化一下问题：有 $n$ 个硬币，初始全是反面。每次选一个硬币翻面，$m$ 次后要让恰好前 $l$ 个正面朝上，问方案数。

那么前 $l$ 个硬币要翻奇数次，剩下的翻偶数次，答案也就是：

$$m![x^m]\left(\frac{\text e^x -\text e^{-x}}{2} \right)^{l}\left(\frac{\text e^x +\text e^{-x}}{2} \right)^{n-l}$$
我们可以设
$$G(x)=(x+1)^{n-l}(x-1)^l$$
显然 $G(x)$ 是微分有限的，具有整式递推式。具体而言：
$$(x^2-1)G'(x)=((2l-n)+nx)G(x)$$
$$(i-1)g_{i-1}-(i+1)g_{i+1}=(2l-n)g_i+ng_{i-1}$$
那么答案就是
$$2^{-n}m! [x^m] \text e^{-nx} G(\text e^{2x})=2^{-n}\sum_{i=0}^n g_i(2i-n)^m$$
线性筛出自然数幂即可计算，时间复杂度 $\Theta(n + n \log_n m)$。

---

## 作者：Naszt (赞：9)

# 超立方体
[> Problem Link <](https://www.luogu.com.cn/problem/P10588)  

## 设计说明

样例点是按照以下梯度设计的：
| 算法 | 期望得分 |
| :----------: | :----------: |
| 递推 | Subtask 0 |
| 部分公式 | Subtask 1 |
| 普通公式 | Subtask 1+2 |
| NTT / 整式递推 | $100$ 分 |

## 算法

### 递推 | Subtask 0

我们可以使用 $\Theta(nm)$ 的递推：

从点 $(0,0,0,\dots,0)$ 出发。  
称 $a^{[x_1,x_2,x_3,\dots,x_n]}_m$ 为走过 $m$ 条棱后到达点 $(x_1,x_2,x_3,\dots,x_n)$ 的方案总数。  

容易得到递推关系式（记 $\neg$ 为非运算）：  
$$a^{[x_1,x_2,\dots,x_n]}_m=a^{[\neg x_1,x_2,\dots,x_n]}_{m-1}+a^{[x_1,\neg x_2,\dots,x_n]}_{m-1}+\dots+a^{[x_1,x_2,\dots,\neg x_n]}_{m-1}$$

可以发现当 $x_1+x_2+\dots+x_n=y_1+y_2+\dots+y_n$ 时：  
$$a^{[x_1,x_2,\dots,x_n]}_m=a^{[y_1,y_2,\dots,y_n]}_m$$

于是记 $\lambda=x_1+x_2+\dots+x_n$ 可得递推式：  
$$a^{[\lambda]}_m=(n-\lambda)a^{[\lambda+1]}_{m-1}+\lambda a^{[\lambda-1]}_{m-1}$$

### 普通公式 | Subtask 1+2

构造循环群 $Z_2^n$，其生成元分别为 $x_1,x_2,\dots,x_n$。  

有生成函数：
$$f(x_1,x_2,\dots,x_n)=(x_1+x_2+\dots+x_n)^m=\sum_{\lambda_1,\lambda_2,\dots,\lambda_n\in N} a_{\lambda_1,\lambda_2,\dots,\lambda_n}x_1^{\lambda_1}x_2^{\lambda_2}\dots x_n^{\lambda_n}$$

方案数可以这么计算：
$$\sum_{x_1,x_2,\dots,x_n\in N}a_{x_1,x_2,\dots,x_n}[2\mid x_1+1][2\mid x_2+1]\dots[2\mid x_n]$$

用单位根反演得到：
$$\frac{1}{2^n}\sum_{x_1,x_2,\dots,x_n\in N}a_{x_1,x_2,\dots,x_n}(1-(-1)^{x_1})(1-(-1)^{x_2})\dots(1+(-1)^{x_1})$$

展开连乘，带入函数：
$$\frac{1}{2^n}\sum_{x_1,x_2,\dots,x_n\in\{-1,1\}}(-1)^{\frac{x_1+x_2+\dots+x_l-1}{2}}f(x_1,x_2,\dots,x_n)$$  

排列组合： 
$$\frac{1}{2^n}\sum_{k_1=0}^n\sum_{k_2=0}^{n-l}(-1)^{k_1}\binom{l}{k_1}\binom{n-l}{k_2}(n-2k_1-2k_2)^m$$

### NTT / 整式递推 | $100$ 分

在普通公式做法的基础上，设：
$$F(x)=(-1)^x\binom{l}{x},G(x)=\binom{n-l}{x},H(x)=(n-2x)^m$$

可以化简成：
$$\frac{1}{2^n}\sum_{t=0}^nH(t)\sum_{k_1+k_2=t}F(k_1)G(k_2)$$

利用 NTT 可以 $\Theta(\sum n\log n)$ 计算后半部分的卷积。

UPD:  
感谢 NaCly\_Fish 提供了一种整式递推的方法，  
可以 $\Theta(\sum n)$ 的计算，orz。  

_tips: 时间复杂度的计算忽略了一些可以当成常数的东西_

## 代码实现

注意一个细节：  
我们知道同余意义下 $(n-2x)^m=(n-2x)^{m \bmod p-1}$，  
所以该数列是循环的。  
但是当 $m=0$ 和 $m=p-1$ 时的结果可能不一样，  
因为 $0^0=1,0^{p-1}=0$ <这里可以这么定义 $0^0$ >  
所以需要特判。

这里给个我的核心代码吧：
```cpp
for(ans=t=0;t<=n;++t)(ans+=fpow(P+n-(t<<1),m)*F[t])%=P;
std::cout<<ans*fpow(2,P-1-n)%P<<"\n";
```
其中 `F[t]` 是卷积的函数。

## 致谢

以下排名不分先后：  
感谢 NaCly\_Fish 对这题的关注与 hack（上方提到的细节），  
感谢 szh_AK_all 积极联系验题人，  
感谢 2023gdgz01 及时的沟通联系，  
以及感谢所有团队成员和大家的支持。

---

## 作者：qzmoot (赞：7)

## 题解：P10588 「ALFR Round 2」D 超立方体
### 前言
先膜拜神鱼的思路，但是神鱼的题解实在是太抽象了……感觉很难看懂（反正我和同机房的大佬看了一下午）。于是我在得到神鱼被搬运的允许后，写下了这篇题解。
### 题目描述
给你 $n$ 个数，要求你进行 $m$ 个操作，每次操作可以选择一个数异或 $1$。求最后前 $l$ 个数是 $1$ 其余全是 $0$ 的操作方案数量。
### 题目分析
构造出生成函数 $F(x)=\sum_i^{\infty}f_i x^i$。其中系数 $f_i$ 表示 $i=m$ 时的答案。

接着来求 $f_m$。若考虑每个操作的顺序，则方案数为 $m!$。那么再把每个操作不考虑顺序，则将这些操作的阶乘从答案里除掉。

又因为前 $l$ 项全部变成了 $1$ 说明操作次数为奇数，否则为偶数。注意**此时注意操作次数都为奇数与都为偶数的两个集合是分开来看的，所以最后要用乘法原理乘起来。**

即为 $m!x^m(\sum_{i=0}\frac{x^{2i +1}}{(2i+1)!})^l(\sum_{i=0}\frac{x^{2i}}{2i!})^{n-l}$。

后面两个式子化成 $\sinh^lx\times\cosh^{n-l}x$ 后进一步化简成限制式。

即 $m!x^m(\frac{e^x-e^{-x}}{2})^l(\frac{e^x+e^{-x}}{2})^{n-l}$。

最后得到 $(2e)^{-n}m!x^m(e^{2x}-1)^l(e^{2x}+1)^{n-l}$。

然后考虑如何进一步化简式子，令函数 $G(x)=(x-1)^l(x+1)^{n-l}$。

因为这个函数是微分有限的，所以我们可以构造出微分方程。

于是我便选择解出导数来构造方程。

$G'(x)=l(x-1)^{l-1}(x+1)^{n-l}+(x-1)^l(n-l)(x+1)^{n-l-1}$

$G'(x)=(x-1)^{l-1}(x+1)^{n-l-1}(lx+l+nx-lx-n+l)$

$G'(x)=(x-1)^{l-1}(x+1)^{n-l-1}(nx+2l-n)$

接下来就不难列出式子：$(x+1)(x-1)G'(x)=(nx+2l-n)G(x)$。

令序列 $g$ 表示 $G(x)$ 函数中的系数，则我们可以从微分方程中得到递推式：$(i-1)g_{i-1}-(i+1)g_{i+1}=(2l-n)g_i+ng_{i-1}$。那么为什么其中可以和 $g$ 联系上呢？因为系数中多带一个 $x$ 所以原本与 $x_i$ 对应的 $g_i$ 就向后移位，系数就变成了 $g_{i-1}$。因为两式子相等，自然说明每一项的系数都相等。

那么答案式可以进一步化简：$(2e)^{-n}x^mm!G(e^{2x})$。

展开 $G(x)$：$(2e)^{-n}x^mm!\sum_{i=0}^ng_ie^{2ix}$。

将 $e^{-n}$ 移入求和：$2^{-n}x^mm!\sum_{i=0}^ng_ie^{(2i-n)x}$。

由于 $e^{ax}=\sum_{i=0}^\infty \frac{(ax)^i}{i!}$。

又因为我们要求的式子是第 $m$ 项，所以式子为：$2^{-n}\sum_{i=0}^ng_i(2i-n)^m$。接着只用递推来求每个系数来求就行。
### CODE
我发现整个题解区没有一个代码是可以运行的，于是我便贴上我丑陋的代码。
```cpp
#include <bits/stdc++.h>
#define int unsigned long long 
using namespace std;
template<typename T>
inline void rd(T& x)
{
	x=0;
	int f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-48,ch=getchar();
	x*=f;
}
template<typename T,typename ...Args>
inline void rd(T& x,Args& ...args)
{
	rd(x),rd(args...);
}
template<typename T>
void wr(T x)
{
	if(x<0)
		putchar('-'),x=-x;
	if(x<=9)
		putchar(x+48);
	else
		wr(x/10),putchar(x%10+48); 
}
template<typename T>
void wrln(T x)
{
	wr(x),putchar('\n');
}
template<typename T>
void wrts(T x)
{
	wr(x),putchar(' ');
}
constexpr int inv2=499122177,mod=998244353;
int T;
int n,m,l;
int ans;
int qpow(int a,int b)
{
	if(a<0)
	{
		cout<<"1111111111111111111";
		exit(0);
	}
	int res=1;
	while(b)
	{
		if(b&1)
			res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
/*
1
3 3 1

*/
signed main()
{
	rd(T);
	while(T--)
	{
		rd(n,m,l);
		int gi2=0,gi1=l&1?mod-1:1,gi;
		ans=gi1*qpow(mod-n,m)%mod;
		for(int i=1;i<=n;i++)
		{
			gi=((i-2+mod-n)*gi2%mod+(n+mod-l*2)*gi1%mod)%mod*qpow(i,mod-2)%mod;
			//wrts(gi2),wrts(gi1),wrln(gi);
			ans=(ans+gi%mod*qpow(2*i+mod-n,m)%mod)%mod;
			gi2=gi1,gi1=gi;
		}
		ans=ans*qpow(inv2,n)%mod;
		wrln(ans);
	}
	return 0;
}
```

---

## 作者：Argon_Cube (赞：7)

将坐标视为长为 $n$ 的二进制串，则每走一条边相当于将串的某一位反转。显然当 $m$ 和 $l$ 奇偶性不同或 $m<l$ 时答案为 $0$。以下我们忽略这两种情况。

枚举每一位被反转了几次得到：

$$\sum_{|a|=n,\sum a=m,a_i\bmod 2=[i\le l]}\binom{m}{a_1,a_2,\cdots,a_n}=m!\sum_{|a|=n,\sum a=\frac{m-a}2}\frac{1}{(2a_i+[i\leq l])!}$$

令 $m'=0.5(m-l)$，显然我们需要将奇偶性不同的位置分开：

$$
\begin{aligned}
&m!\sum_{i=0}^{m'}\left(\sum_{|a|=l,\sum a=i}\frac{1}{(2a_i+1)!}\right)\left(\sum_{|a|=n-l,\sum a=m'-i}\frac{1}{(2a_i)!}\right)
\\=&m!\sum_{i}[x^{2i+l}]\sinh^l[x^{2m'-2i}]\cosh^{n-l}
\\=&\left[\frac{x^m}{m!}\right]\sinh^l\cosh^{n-l}
\\=&2^{-n}\sum_{i=0}^n(2i-n)^m\sum_j(-1)^{l+i-j}\binom l{i-j}\binom {n-l}{j}
\end{aligned}
$$

以上省略了大量简单的中间过程，最后一步是将 $\sinh$ 展开为 $0.5(e^x-e^{-x})$。

后面关于 $j$ 的和式显然是卷积，于是本题可以做到 $\Omicron(n\log n)$。

~~怎么会有人因为快速幂被卡了一页啊？？？~~

```cpp
constexpr int maxn=1<<21,moder=998244353;
array<long long,maxn+1> facts,ifacts;
polynomial<maxn+1> polya,polyb,polyans;

inline long long binom(int n,int m)
{
    return facts[n]*ifacts[m]%moder*ifacts[n-m]%moder;
}

int main(int argc,char* argv[],char* envp[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    facts[0]=1;
    for(int i=1;i<=maxn;i++)
        facts[i]=facts[i-1]*i%moder;
    ifacts[maxn]=inverse(facts[maxn],moder);
    for(int i=maxn;i;i--)
        ifacts[i-1]=ifacts[i]*i%moder;
    int testcnt;
    cin>>testcnt;
    while(testcnt--)
    {
        int n,a;
        unsigned long long m;
        cin>>n>>m>>a;
        if((m-a&1)||m<a)
        {
            cout<<"0\n";
            continue;
        }
        long long answer=0;
        for(int i=0;i<=a;i++)
            polya[i]=binom(a,i)*(a-i&1?moder-1:1)%moder;
        for(int i=0;i<=n-a;i++)
            polyb[i]=binom(n-a,i);
        mult(a+1,n-a+1,polya,polyb,polyans,n);
        polyans[0]=polya[0],polyans[n]=1;
        for(int i=0;i<=n;i++)
            polya[i]=polyb[i]=0;
        for(int i=0;i<=n;i++)
            answer+=polyans[i]*fast_pow((i+i-n+moder)%moder,m%(moder-1)+(m>=moder-1)*(moder-1),moder)%moder;
        cout<<answer%moder*fast_pow(moder+1>>1,n,moder)%moder<<'\n';
    }
    return 0;
}
```

---

## 作者：Starrykiller (赞：6)

答案显然为

$$\left[\prod_{1\le i\le n} x_i^{[i\le l]}\right]\left(\sum_{1\le i\le n}  x_i\right)^m \bmod (x_1^2-1)\bmod \cdots \bmod (x_ n^2-1)$$


考虑手动做 FWT：

初始时，序列 $f_i=[i=2^k]$。然后做长度为 $2^n$ 的 FWT 之后得到

$$
\begin{aligned}
\hat f_i&=\sum_{0\le j\lt 2^n} (-1)^{\operatorname{popcount}(i\operatorname{and}j)} f_j \\
&=\sum_{0\le j\lt n} (-1)^{[j\in i]} \\
&=n-2\operatorname{popcount}(i)
\end{aligned}
$$


然后令 $\hat f_i\gets {\hat f_i}^m$，再 IFWT 回去：

$$
\begin{aligned}
f'_i&=\frac{1}{2^n}\sum_{0\le j\lt 2^n} (-1)^{\operatorname{popcount}(i\operatorname{and}j)} \hat f_j \\
\end{aligned}
$$

我们关心的实际上是 $f_{2^l-1}$，也就是，低 $l$ 位是 $1$。注意到只和 $\operatorname{popcount}$ 有关系，不妨枚举低 $l$ 位的 $\operatorname{popcount}$ 和后 $(n-l)$ 位的 $\operatorname{popcount}$：

$$
\begin{aligned}
\mathrm{answer}&=\frac{1}{2^n}\sum_{0\le p\le l}(-1)^p{l\choose p}\sum_{0\le q\le n-l}{n-l\choose q} (n-2(p+q))^m 
\end{aligned}
$$

枚举 $p+q$ 的值，得到

$$
\begin{aligned}
\mathrm{answer}&=\frac{1}{2^n}\sum_{0\le i\le n}(n-2i)^m\sum_{p+q=i}(-1)^p{l\choose p}{n-l\choose q}
\end{aligned}
$$

使用 DFT，时间复杂度 $\Theta(n\log n)$。

Madoka 酱亲亲！鱼鱼姐姐亲亲！/mm

---

## 作者：qczrz6v4nhp6u (赞：1)

怎么都是 FWT 大神。

### Solution

显然每一维是独立的，那么限制就只有前 $l$ 维走的步数是奇数，后 $n-l$ 维走的步数是偶数。根据 EGF 的组合意义直接列出答案的 EGF：

$$m![z^m]\Big(\frac{{\rm e}^z-{\rm e}^{-z}}{2}\Big)^l\Big(\frac{{\rm e}^z+{\rm e}^{-z}}{2}\Big)^{n-l}$$

然后看起来不太会优化啊，先试试看 $l=0$ 怎么做。此时的答案就是

$$\frac{m!}{2^n}[z^m]({\rm e}^z+{\rm e}^{-z})^n$$

拆一下二项式

$$\begin{aligned}
&\frac{m!}{2^n}[z^m]\sum_{i=0}^n{n\choose i}{\rm e}^{iz-(n-i)z}\\
=&\frac{m!}{2^n}[z^m]\sum_{i=0}^n{n\choose i}{\rm e}^{(2i-n)z}\\
=&\frac{m!}{2^n}[z^m]\sum_{i=0}^n{n\choose i}\sum_{j\ge 0}\frac{(2i-n)^jz^j}{j!}\\
=&\frac{1}{2^n}\sum_{i=0}^n{n\choose i}(2i-n)^m\\
\end{aligned}$$

这样 $l=0$ 的部分可以直接 $O(n\log m)$ 搞定。

然后尝试推广到 $l>0$。故技重施：

$$\begin{aligned}
&m![z^m]\Big(\frac{{\rm e}^z-{\rm e}^{-z}}{2}\Big)^l\Big(\frac{{\rm e}^z+{\rm e}^{-z}}{2}\Big)^{n-l}\\
=&\frac{m!}{2^n}[z^m]({\rm e}^z-{\rm e}^{-z})^l({\rm e}^z+{\rm e}^{-z})^{n-l}\\
=&\frac{m!}{2^n}[z^m]\Big(\sum_{i=0}^l{l\choose i}\sum_{j\ge 0}\frac{(2i-l)^jz^j}{j!}\Big)\Big(\sum_{i=0}^{n-l}{n-l\choose i}\sum_{j\ge 0}\frac{(2i-n+l)^jz^j}{j!}\Big)\\
=&\frac{1}{2^n}\sum_{k=0}^m{m\choose k}\Big(\sum_{i=0}^l{l\choose i}(-1)^{l-i}(2i-l)^k\Big)\Big(\sum_{i=0}^{n-l}{n-l\choose i}(2i-n+l)^{m-k}\Big)\\
=&\frac{1}{2^n}\sum_{i=0}^l\sum_{j=0}^{n-l}{l\choose i}{n-l\choose j}(-1)^{l-i}\sum_{k=0}^m{m\choose k}(2i-l)^k(2j-n+l)^{m-k}\\
=&\frac{1}{2^n}\sum_{i=0}^l\sum_{j=0}^{n-l}{l\choose i}{n-l\choose j}(-1)^{l-i}(2i+2j-n)^m
\end{aligned}$$

设 $a_k=\sum_{i=0}^l\sum_{j=0}^{n-l}{l\choose i}{n-l\choose j}(-1)^{l-i}$，则答案即为

$$\sum_{k=0}^na_k(2k-n)^m$$

于是一个 NTT 就 $O(n\log n)$ 做完了。可以使用经典的微分解递推式做到线性。

### Code

```cpp
bool Mst;
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=(1<<21)+5,mod=998244353;
inline ll add(ll x,ll y){return (x+=y)>=mod&&(x-=mod),x;}
inline ll Add(ll &x,ll y){return x=add(x,y);}
inline ll sub(ll x,ll y){return (x-=y)<0&&(x+=mod),x;}
inline ll Sub(ll &x,ll y){return x=sub(x,y);}
inline ll qpow(ll a,ull b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
int lim,rev[N];ll ilim,w[N];
inline void initNTT(int n){
	lim=1;
	while(lim<=n)lim<<=1;
	ilim=qpow(lim,mod-2);
	rev[0]=0;
	for(int i=1;i<lim;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)*(lim>>1));
	for(int i=1;i<lim;i<<=1){
		ll cur=1,wn=qpow(3,(mod-1)/(i<<1));
		for(int j=0;j<i;j++,cur=cur*wn%mod)
			w[i|j]=cur;
	}
}
inline void NTT(ll *F,int type){
	for(int i=0;i<lim;i++)
		if(i<rev[i])
			swap(F[i],F[rev[i]]);
	for(int i=1;i<lim;i<<=1)
		for(int j=0;j<lim;j+=i<<1)
			for(int k=0;k<i;k++){
				ll x=F[j|k],y=w[i|k]*F[i|j|k]%mod;
				F[j|k]=add(x,y),F[i|j|k]=sub(x,y);
			}
	if(type==1)return;
	reverse(F+1,F+lim);
	for(int i=0;i<lim;i++)F[i]=F[i]*ilim%mod;
}
ll fac[N],ifac[N];
inline ll binom(int n,int m){
	if(m<0||m>n)return 0;
	return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
void init(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	ifac[n]=qpow(fac[n],mod-2);
	for(int i=n;i>=1;i--)ifac[i-1]=ifac[i]*i%mod;
}
int n,l;ull m;
ll F[N],G[N];
bool Med;
int main(){
	cerr<<abs(&Mst-&Med)/1048576.0<<endl;
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	init(1<<21);
	int _Test;cin>>_Test;
	while(_Test--){
		cin>>n>>m>>l;
		initNTT(n);
		for(int i=0;i<lim;i++)F[i]=G[i]=0;
		for(int i=0;i<=l;i++)F[i]=(l-i)&1?mod-binom(l,i):binom(l,i);
		for(int i=0;i<=n-l;i++)G[i]=binom(n-l,i);
		NTT(F,1),NTT(G,1);
		for(int i=0;i<lim;i++)F[i]=F[i]*G[i]%mod;
		NTT(F,-1);
		ll ans=0;
		for(int i=0;i<=n;i++)ans=(ans+F[i]*qpow(sub(i<<1,n),m))%mod;
		cout<<ans*qpow(2,mod-n-1)%mod<<'\n';
	}
	return 0;
}
```

---

