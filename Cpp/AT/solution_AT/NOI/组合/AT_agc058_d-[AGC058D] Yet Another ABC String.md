# [AGC058D] Yet Another ABC String

## 题目描述

给定整数 $A$、$B$、$C$。请计算由 $A$ 个 `A`、$B$ 个 `B`、$C$ 个 `C` 组成的字符串 $S$，满足以下所有条件的字符串个数，并将结果对 $998244353$ 取模。

- $S$ 中包含的 `A`、`B`、`C` 的数量分别为 $A$、$B$、$C$。
- $S$ 作为（连续的）子串，不包含 `ABC`、`BCA`、`CAB` 中的任意一个。

## 说明/提示

### 限制条件

- $1 \leq A,B,C \leq 10^6$
- 输入的值均为整数。

### 样例解释 1

满足条件的字符串有 `ACB`、`CBA`、`BAC` 共 $3$ 个。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
2 2 2```

### 输出

```
42```

## 样例 #3

### 输入

```
96 11 46```

### 输出

```
818015722```

## 样例 #4

### 输入

```
125132 102271 152064```

### 输出

```
128086069```

# 题解

## 作者：EuphoricStar (赞：25)

Orz H6_6Q，感谢他给我们带来了这道容斥好题。

这个东西看起来很不好搞。可以尝试容斥。

但是我们要容斥啥？钦定 `ABC` 不出现，其他任意？感觉还是很难算。

观察不合法子串，发现它们很有特点。如果我们钦定 $\texttt{A}$ 为 $0$，$\texttt{B}$ 为 $1$，$\texttt{C}$ 为 $2$，那么不合法串相当于 $S_i + 1 \equiv S_{i + 1} \pmod 3$。

并且我们还发现一个性质，如果 $S_{i \sim i + 2}$ 不合法，即 $S_{i \sim i + 2}$ 为 $\texttt{ABC}, \texttt{BCA}, \texttt{CAB}$ 中的其中一个，并且 $S_{i + 1 \sim i + 3}$ 也不合法，那么 **$S_{i \sim i + 3}$ 也不合法**。因为由上面不合法子串的特点我们得到了这个东西具有**传递性**。

现在我们尝试考虑每个**极长**不合法子串。发现它们既有起点又有终点。我们尝试**容斥起点**。即我们钦定有 $i$ 个极长不合法子串的起点。

极长不合法子串的长度还不确定，但是我们发现只要钦定它们的长度 $\ge 3$，即每个字母至少出现一次即可。

于是我们现在相当于有 $a - i$ 个 $\texttt{A}$，$b - i$ 个 $\texttt{B}$，$c - i$ 个 $\texttt{C}$ 是自由的。我们需要把它排成一个**初始串**。这部分的方案数由多重组合数易得为 $\frac{(a + b + c - 3i)!}{(a - i)! (b - i)! (c - i)!}$。

然后，我们需要把 $i$ 个串，每个都是 $\texttt{ABC}, \texttt{BCA}, \texttt{CAB}$ 中**之一**的串插入一开始排成的那个初始串。如果插入的位置在开头，那么 $3$ 个串都可以被选择插入；如果在中间，因为我们**容斥的是极长不合法子串的起点，也就是说它们必须是起点，其他的可以是也可以不是**，所以我们不能接在字母序上一个字母后面，导致这个字母成为了起点。具体一点就是，$\texttt{ABC}$ 不能接在 $\texttt{C}$ 后面，$\texttt{BCA}$ 不能接在 $\texttt{A}$ 后面，$\texttt{CAB}$ 不能接在 $\texttt{B}$ 后面。我们发现无论插入位置前一个字母是什么，插入的串都有 $2$ 种选择。

现在考虑统计**插入初始串并选择是 $\texttt{ABC}, \texttt{BCA}$ 还是 $\texttt{CAB}$** 的方案数。分类讨论。

- 如果没有串被放到开头，那么初始串有 $a + b + c - 3i$ 个空隙。我们需要把 $i$ 个起点分配成 $a + b + c - 3i$ 份，每份可以为空，然后再按份对应地插入到这么多空隙中，再乘上选择插入的是哪个串的方案数。于是这部分的方案数就是 $\binom{i + a + b + c - 3i - 1}{a + b + c - 3i - 1} \times 2^i$。
- 如果有 $1$ 个串被放到开头，那么我们先放一个起点到开头，那么现在的串有 $a + b + c + 3i + 1$ 个空隙，并且我们还剩 $i - 1$ 个起点。由上面的推法可得这部分的方案数为 $\binom{i - 1 + a + b + c - 3i}{a + b + c - 3i} \times 2^{i - 1} \times 3$。

然后，我们把排成初始串的方案数，和上面统计的插入并选择的方案数相乘，再乘上容斥系数 $(-1)^i$。对于每个 $i \in [0, \min(a, b, c)]$ 求和，即是答案。

**启发：容斥的东西可以是非常规的，不一定是题目直接给出的东西。**

[code](https://atcoder.jp/contests/agc058/submissions/43324511)

---

## 作者：NaCly_Fish (赞：20)

没活整了，怎么办！
****
[题目链接](https://www.luogu.com.cn/problem/AT_agc058_d)

我不会容斥，也不会分析性质，我只会暴力递推！

设 $f_0$ 表示以 `AA` 结尾的合法串数量的三元生成函数（用 $x,y,z$ 分别计量 $A,B,C$ 出现的次数），$f_1$ 表示 `AB` 结尾的 ... $f_8$ 表示 `CC` 结尾的。于是就能得到一个 9 元线性方程组：

$$\begin{cases}f_0=x(f_0+f_3+f_6)+x^2 \\ f_1 = y(f_0+f_3) + xy \\ f_2 = z(f_0+f_3+f_6) + xz \\ f_3 = x(f_1+f_4+f_7) + xy
\\f_4 = y(f_1+f_4+f_7) + y^2
\\f_5 = z(f_4+f_7) + yz
\\f_6 = x(f_2+f_8) + xz
\\f_7 = y(f_2+f_5+f_8) + yz
\\f_8 = z(f_2+f_5+f_8) + z^2 \end{cases}$$
理解起来很简单，比如 $f_5$，它表示 `BC` 结尾的情况。这可以由 `BB`、`CB` 结尾的情况接一个 `C` 组成（注意不能由 `AB` 拼接 `C`，因为 `ABC` 是不能出现的），同时补上缺掉的只有 `BC` 两项的情况（即那个单项 $yz$）。

这个方程组中是蕴涵着某种对称性的，我们就可以~~容易地使用mma~~算出
$$\sum_{i=0}^8f_i=\frac{(3-x-y-z)/2}{1-x-y-z+2xyz}-\frac 32-x-y-z$$
由于 $A,B,C \geq 1$，我们要算的答案就只是
$$\frac 12[x^Ay^Bz^C] \frac{3-x-y-z}{1-x-y-z+2xyz}$$
$$=\frac 12[x^Ay^Bz^C]\sum_{i\geq 0}(-1)^i(2xyz)^i(3-x-y-z)(1-x-y-z)^{-1-i}$$
$$=\frac 12 \sum_{i\geq 0}(-2)^i [x^{A-i}y^{B-i}z^{C-i}]\left( \frac{2}{(1-x-y-z)^{i+1}}+\frac{1}{(1-x-y-z)^i}\right)$$
两项有类似的形式，只用考虑其中一部分：
$$[x^ay^bz^c]\frac{1}{(1-x-y-z)^k}=[x^ay^bz^c]\sum_{i\geq 0}\binom{k+i-1}{k-1}(x+y+z)^i$$
提取系数后，显然和式中仅有 $i=a+b+c$ 的那一项非零，结果就是
$$\binom{k+a+b+c-1}{k-1}\binom{a+b+c}{a,b,c}$$
带回原式，答案即为
$$\frac 12 \sum_{i \geq 0}(-2)^i \left( 2\binom{A+B+C-2i}{i}+\binom{A+B+C-2i-1}{i-1}\right)\binom{A+B+C-3i}{A-i,B-i,C-i}$$

---

## 作者：Eaoci (赞：14)

感谢 gyh 神仙的思路。

我们首先发现不合法区间是可以合并的。具体来说，若 $[i,i+2]$ 不合法，$[i+2,i+4]$ 不合法，那么 $[i+1,i+3]$ 也不合法。

于是我们考虑容斥，我们可以求出钦定出现了 $k$ 个连续不合法段的方案数，即钦定存在 $k$ 个位置满足 $[i,i+2]$ 非法且 $[i+1,i+3]$ 合法或 $i+2$ 是序列结尾，这样钦定的每个位置要保证和下一个位置合法有两种填法，在算上钦定到了结尾的方案数即可，具体式子可见代码，复杂度 $O(n)$ 。

```cpp
#include<iostream>
#include<cstdio>
#define int long long 
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=3000030,mod=998244353;
int n,a,b,c,jc[N],inv[N],mi[N];
int ksm(int p,int k){
	int x=1;
	while(k){
		if(k&1)x=x*p%mod;
		p=p*p%mod;
		k>>=1;
	}
	return x;
}
int C(int n,int m){
	if(n<m)return 0;
	return jc[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	a=read(),b=read(),c=read();
	n=a+b+c,jc[0]=mi[0]=1;
	for(int i=1;i<=n;i++){
		jc[i]=jc[i-1]*i%mod;
		mi[i]=mi[i-1]*2%mod;
	}
	inv[n]=ksm(jc[n],mod-2);
	for(int i=n;i;i--){
		inv[i-1]=inv[i]*i%mod;
	}
	int ans=C(n,a)*C(n-a,b)%mod,nw=1;
	for(int i=1;i<=min(min(a,b),c);i++){
		int m=n-3*i,x=C(m,a-i)*C(m-(a-i),b-i)%mod;nw=-nw;
		//m为去掉钦定位置的序列长度，x为此时任意填的方案数。 
		ans=(ans+nw*(x*C(m+i,i)%mod*mi[i]+x*C(m+i-1,i-1)%mod*mi[i-1])%mod+mod)%mod;
		//注意如果钦定到结尾那么结尾有三种填法，把少算的一种加上。 
	}
	cout<<ans;
	return 0;
}


```


---

## 作者：lingfunny (赞：14)

# D - Yet Another ABC String
首先基础的容斥是考虑**不合法位置起点集合** $\{p_1, p_2, \dots, p_k\}$，表示 $s_{p_i}s_{p_i + 1}s_{p_i + 2}\in\{\texttt{ABC},\texttt{BCA},\texttt{CAB}\}$。容斥系数就是 $-1^{k}$。

但这并不好算，因为不合法位置可能重合，这时候是比较难计数的（还要枚举重叠情况进行拼接）。

于是转而考虑直接容斥**不合法线段**：用序列 $L=(L_1, L_2, \dots, L_k)$ 表示有长度为 $L_1, L_2, \dots, L_k$ 的**不合法线段**，这时候是比较好计数的，但是容斥系数需要搓一下。

对于一个长度为 $L_i$ 的**不合法线段**，用上面的**不合法位置起点集合**的容斥系数计算，可以得到：
$$
\begin{aligned}
F_3 &= -1 & \{\{1\}\}\\
F_4 &= 1 & \{\{1, 2\}\}\\
F_5 &= 0 & \{\{1,2,3\},\{1,3\}\}\\
F_6 &= -1 & \{\{1,2,3,4\},\{1,2,4\},\{1,3,4\}\}
\end{aligned}
$$
再往下就不列举了，其实可以得到递推式，$F_k=-F_{k-1} - F_{k - 2}$，从在末尾添加点的角度考虑不难理解该式。

通过上述式子，可以找规律并归纳证明：
$$
F_i=
\begin{cases}
-1&i\equiv0\pmod 3\\
1&i\equiv1\pmod3\\
0&i\equiv2\pmod3
\end{cases}
$$
得到容斥系数之后，考虑怎么算出所有序列 $L$ 的贡献。

首先只需要考虑 $L_i=3m$ 和 $L_i=3m+1$ 的情况，前者是直接填 `ABC` 各一个上去，后者是还要多填一个单独字符。

那么可以设计一个 dp，记 $f_{i, j}$ 表示已经构造了长度为 $i$ 的字符串，多填了 $j$ 个单独字符的容斥系数。
$$
f_{i, j}=f_{i-1, j-1}+\sum_{k = 3}^{i}[k\equiv1\pmod3]f_{i-k, j - 1}-3[k\equiv0\pmod3]f_{i-k,j}
$$
前面的 $f_{i-1,j -1}$ 是指随便填一个字符，不组成**不合法线段**。

最后把计数一并加上去：
$$
\mathrm{Ans}=\sum_{i=0}^{\min(a,b,c)}\binom{n-3i}{a-i,b-i,c-i}f_{n,n-3i}
$$
得到了一个 $O(n^3)$ 的做法，瓶颈在于 dp 太慢了。

注意起点是 $f_{0, 0}=1$，转移系数固定，生成函数非常适合。

设 $G(x,y)$ 为 $f_{x, y}$ 的生成函数，可以得到：
$$
\begin{aligned}
F& = xy+\sum_{i\ge1}x^{3i+1}y-3\sum_{i\ge1}x^{3i}=\sum_{i\ge0}x^{3i+1}y-3\sum_{i\ge1}x^{3i}\\
G& = \sum_{i\ge0}F^i
\end{aligned}
$$
经典错项减一减就可以搞出来辣：
$$
\begin{aligned}
&x^3F=\sum_{i\ge1}x^{3i+1}y-3\sum_{i\ge2}x^{3i}\\
&(1-x^3)F=xy-3x^3\\
&F=\frac{xy-3x^3}{1-x^3}\\
&G=\frac{1}{1-F}=\frac{1-x^3}{1-xy+2x^3}
\end{aligned}
$$
想搞 $[x^ny^m]G$，先拆成 $G'=\frac{1}{1-xy+2x^3}$，则 $[x^ny^m]G=[x^ny^m]G'-[x^{n-3}y^m]G'$。

问题变成怎么计算 $[x^ny^m]G'$：这东西可以拆成 $G'=\displaystyle\sum_{i\ge0}(xy-2x^3)^i$，好消息是可以直接解方程。

设左边贡献 $p$ 次，右边贡献 $q$ 次，有 $\begin{cases}p+3q=n\\q=m\end{cases}$，解出 $p, q$ 后不难得到 $[x^ny^m]G'=\binom{p+q}{p}(-2)^{q}$。

直接枚举 $[x^ny^{n-3i}]G$ 即可，时间复杂度 $\Theta(n)$。


---

## 作者：Graphcity (赞：9)

显然要考虑容斥。一般的容斥是枚举不合法的字符串位置，但这题不合法的字符串可能会重叠，比较难以计算。一种好的容斥方式是容斥形如 `ABCABCABCA...` 这样的连续段，只要每个极长连续段长度都不超过 2 就行了。

这样会产生一个新的问题：我们并不能保证连续段是极长的。我们需要找到一个容斥系数，使得长度 $\le 2$ 的连续段的所有划分方式容斥系数之和为 1，否则为 0。设 $F(x)$ 为容斥系数的生成函数，应该有：
$$
\begin{aligned}
\sum_{i\ge 0}F(x)^i&=1+x+x^2\\
\frac{1}{1-F(x)}&=1+x+x^2\\
F(x)&=1-\frac{1}{1+x+x^2}
\end{aligned}
$$
通过暴力多项式求逆或者手算，可以得到：
$$
[x^k]F(x)=\begin{cases}
0 & k=0 \operatorname{or} k\equiv 2\pmod 3\\
1 & k\equiv 1\pmod 3\\
-1 & k\equiv 0\pmod 3
\end{cases}
$$
我们只关心 $\not= 0$ 的项。计算答案可以利用三元生成函数：
$$
\begin{aligned}
G&=(-3\sum_{i\ge 1}(abc)^i)+(\sum_{i\ge 0}(abc)^i(a+b+c))\\
ans&=[a^{A}b^{B}c^{C}]\sum_{i\ge 0}G^i=[a^{A}b^{B}c^{C}]\frac{1}{1-G}
\end{aligned}
$$
其中 -3 的系数是因为连续段长度为 3 的倍数时，有三种方案。整理一下：
$$
\begin{aligned}
G&= a+b+c+\sum_{i\ge 1}(abc)^i(a+b+c-3)\\
&= a+b+c+(a+b+c-3)\frac{abc}{1-abc}\\
&=\frac{(1-abc)(a+b+c)+abc(a+b+c-3)}{1-abc}\\
&=\frac{a+b+c-3abc}{1-abc}\\
\frac{1}{1-G}&=\frac{1-abc}{1-a-b-c+2abc}=(1-abc)(\sum_{i\ge 0}(a+b+c-2abc)^i)
\end{aligned}
$$
那么我们只需要枚举右边选了几个 $-2abc$ 就可以 $O(1)$ 求出答案。时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=3e6,Mod=998244353;

inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}

int A,B,C,n,fac[Maxn+5],inv[Maxn+5],pw[Maxn+5];
inline int F(int a,int b,int c)
{
    int m=min(a,min(b,c)),res=0; if(m<0) return 0;
    For(i,0,m)
    {
        int k=1ll*pw[i]*(i&1?Mod-1:1)%Mod;
        res=(res+1ll*k*fac[a+b+c-i-i]%Mod*inv[i]%Mod*
             inv[a-i]%Mod*inv[b-i]%Mod*inv[c-i])%Mod;
    } return res;
}

int main()
{
    cin>>A>>B>>C; n=A+B+C,fac[0]=inv[0]=pw[0]=1;
    For(i,1,n) pw[i]=2*pw[i-1]%Mod;
    For(i,1,n) fac[i]=1ll*fac[i-1]*i%Mod;
    inv[n]=Pow(fac[n],Mod-2);
    Rof(i,n-1,1) inv[i]=1ll*inv[i+1]*(i+1)%Mod;
    cout<<(F(A,B,C)-F(A-1,B-1,C-1)+Mod)%Mod<<endl;
    return 0;
}
```



---

## 作者：analysis (赞：8)

将字符串看作若干个 abcabc 的有序段组成，我们希望序列中的所有极长有序段的长度小于等于 $2$。

我们给长度为 $n$ 的有序段配上 $p_n$ 的容斥系数，由于不关心位置，我们设出系数的 OGF P。

显然一个极长的有序段会被钦定的操作划成若干个段，于是有 $SEQ(P)=1+x+x^2$，解出 $P=1-\frac{1}{1+x+x^2}$。求系数，分式下面是 $\{1,1,1,0,\cdots\}$，施差分可以得到 $P=1-\frac{1-x}{1-x^3}$，得到：

$$
P=1-\sum_{i \geq 0}x^{3i}(1-x)\\p_n=\begin{cases}-1 &&&&& n\equiv 0\\1 &&&&& n \equiv 1\\0 &&&&& n \equiv 2 or n=0\end{cases}
$$

挂上三元 GF，设 $u=xyz$，有：

$$
G=x+y+z+\sum_{i\geq 1}(xyz)^i(x+y+z-3)=\frac{x+y+z-3u}{1-u}\\\frac{1}{1-G}=\frac{1-u}{1-x-y-z+2u}=(1-u)\sum(x+y+z-2u)^i\\
$$

枚举有多少个 $u$ 即可。

---

## 作者：psoet (赞：8)

> 给出 $a,b,c$，求由 $a$ 个 A，$b$ 个 B，$c$ 个 C 构成的字符串数量，使得不存在子串 `ABC`，`BCA` 和 `CAB`。$1 \leq a,b,c \leq 10^6$

场上的想法：肯定是容斥，钦定一些位置是这三类串后钦定的部分构成了一些连通子段，容斥系数是 $(-1)$ 的钦定总长次方，但是因为限制了 ABC 的数量方案数不好计算。

考虑从串的整体出发的容斥方法。

注意到这三种串都是 $\mathtt{ABCABC\cdots}$ 的一部分。考虑把 `AB`，`BC`，`CA` 合起来后的隔板，一个串合法当且仅当相邻隔板距离不超过2。

钦定隔板的子集然后容斥。如果我们要计算隔板恰好是 $S$ 的方案数 $f_S$，令钦定是 $T$ 的方案数是 $g_T$，那么 $f_S = \sum_{T \subseteq S} g_T(-1)^{|S| - |T|}$。

我们要求合法的 $S$ 的 $f$ 之和。交换求和号，对于一种钦定的 $T$，求相应合法 $S$ 的容斥系数之和，然后乘上 $g_T$。

设钦定的 $T$ 中一段长度为 $i$ 的连续段各种选 $S$ 的方式容斥系数之和为 $c_i$，则 $c_1 = 1, c_2 = 0, c_i(i \geq 3) = -c_{i-1} - c_{i-2}$，得到

$$
c_i = \begin{cases}1\quad (i \equiv 1 \pmod 3) \\0\quad (i \equiv 2 \pmod 3)\\-1\quad (i \equiv 0 \pmod 3)\end{cases}
$$

然后需要求 $g_T$。枚举 $T$ 中有多少个模3余1的段（记为 $x(3|(n-x))$），剩下的段长度都是3的倍数（因为模3余2没有贡献），设有 $y$ 个。根据 $a,b,c$ 可以求出每个字母是多少个模3余1的段的开头，记为 $c_A,c_B,c_C$。先确定开头（长度为1或3）的位置，再把剩余的长度为3的段插进去。那么只需计算 ${x \choose c_A \; c_B \; c_C}$ 乘上

$$
\sum_y (-3)^y{x+y\choose x}{{n-x\over 3}+x-1 \choose x+y-1}  \\
=\sum_y(-3)^y[{x+y-1 \choose x} +{x+y-1 \choose x-1}]{{n-x\over 3}+x-1 \choose x+y-1} \\
=\sum_y(-3)^y[{{n-x\over 3}+x-1 \choose x}{{n-x\over 3} - 1\choose y-1}+{{n-x\over 3}+x-1 \choose x-1}{{n-x\over 3} - 1\choose y}] \\
=-3\cdot{{n-x\over 3}+x-1 \choose x}(-2)^{{n-x\over 3}-1}[x<n]+{{n-x\over 3}+x-1 \choose x-1}(-2)^{n-x\over 3}[x>0]
$$

即可。（注意组合数的规范定义，上述推导不需要对变量的范围有额外限制）

---

## 作者：win114514 (赞：4)

非常棒的容斥题。

### 思路

由于我们要求的是不存在子串 `ABC`，`BCA` 和 `CAB` 的字符串。

我们可以对这个进行容斥。

如何容斥？

假如我们容斥有多少个不合法的子串，这样是非常不好计算的。

但是我们可以观察这道题的一些性质。

其实你从上一个容斥就可以看出，对于一个类似 `ABCA` 的串，它的长度只有 $4$，但是却包含了 $2$ 个不合法的子串。

可以发现我们可以提出来一个极长的不合法子串。

这是由于他给的字符串的特殊性质。

那么就容易想到我们可以容斥它有多少个极长的不合法子串。

这个是比较好容斥的。

在容斥的时候，由于我们不需要关心他的长度，我们只需要限定他一定是一个不合法子串，并且是极长的即可。

那么可以通过钦定起点来计数。

首先假设有 $i$ 个极长的不合法子串。

那么我们其它的字符可以随意排列：

$$
\binom{a-i+b-i+c-i}{a-i,b-i,c-i}
=\frac{(a+b+c-3\times i)!}{(a-i)!(b-i)!(c-i)!}
$$

由于我们钦定的是起点，那么假如钦定的起点是 $s$，那么 $s-1,s,s+1$ 必定不是一个不合法子串。

所以 `A` 后面可以接 `ABC` 和 `CAB`。

`B` 后面可以接 `ABC` 和 `BCA`。

`C` 后面可以接 `BCA` 和 `CAB`。

每个点都是两种情况。

所以方案数可以用插板法算：

$$
\binom{a+b+c-i-i-1}{a+b+c-i-i-i-1}\times 2^i
$$

当然，这个答案还少了一种情况，我们的不合法串还可以在开头。

所以还有：

$$
\binom{a+b+c-i-i-1}{a+b+c-i-i-i}\times 2^{i-1}\times 3
$$

最后不要忘记容斥系数。

预处理组合数就可以了。

时间复杂度：$O(n)$。

### Code

```cpp
/*
  ! 如果没有天赋，那就一直重复
  ! Created: 2024/06/28 15:24:35
*/
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
// #define int long long
#define mp(x, y) make_pair(x, y)
#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)
inline void JYFILE19();

using i64 = long long;
using PII = pair<int, int>;

bool ST;
const int N = 3e6 + 10;
const int mod = 998244353;

int n, m, k, ans, all, f[N];

namespace Math {
const int I = N; i64 fac[I], inv[I], pw2[I];
template<typename T> inline void add(T &x, i64 y) { x = (x + y >= mod ? x + y - mod : x + y); }
template<typename T> inline void mul(T &x, i64 y) { x = (x * y >= mod ? x * y % mod : x * y); }
inline i64 Add(i64 x, i64 y) { return (x + y >= mod ? x + y - mod : x + y); }
inline i64 Mul(i64 x, i64 y) { return (x * y >= mod ? x * y % mod : x * y); }
inline i64 power(i64 x, i64 y) {
  i64 res = 1; while(y) {
    if(y & 1) res = res * x % mod;
    x = x * x % mod, y /= 2;
  }
  return res;
}
inline void init(int n = I - 10) {
  fac[0] = pw2[0] = 1;
  fro(i, 1, n) fac[i] = Mul(fac[i - 1], i);
  fro(i, 1, n) pw2[i] = pw2[i - 1] * 2 % mod;
  inv[n] = power(fac[n], mod - 2);
  pre(i, n, 1) inv[i - 1] = Mul(inv[i], i);
}
inline i64 C(i64 x, i64 y) {
  if (x < 0 || y < 0 || x - y < 0) return 0;
  return Mul(fac[x], Mul(inv[y], inv[x - y]));
}
} using namespace Math;

inline i64 C(i64 a, i64 b, i64 c) {
  return fac[a + b + c] * inv[a] % mod * inv[b] % mod * inv[c] % mod;
}

signed main() {
  JYFILE19();
  cin >> n >> m >> k, init(all = n + m + k);
  fro(i, 0, min({n, m, k})) {
    i64 res = C(n - i, m - i, k - i);
    if (i) {
      int x = Mul(C(all - i - i - 1, all - i - i - i - 1), pw2[i]);
      int y = Mul(C(all - i - i - 1, all - i - i - i), pw2[i - 1]) * 3 % mod;
      res = res * (x + y) % mod;
    }
    add(ans, (i & 1 ? mod - res : res));
  }
  cout << ans << "\n";
  return 0;
}

bool ED;
inline void JYFILE19() {
  // freopen("", "r", stdin);
  // freopen("", "w", stdout);
  srand(random_device{}());
  ios::sync_with_stdio(0), cin.tie(0);
  double MIB = fabs((&ED - &ST) / 1048576.), LIM = 1024;
  cerr << "MEMORY: " << MIB << endl, assert(MIB <= LIM);
}
```

---

## 作者：ty_mxzhn (赞：3)

容斥。

题意说你不能出现 $\texttt{ABC,BCA,CAB}$ 这样的东西。那么考虑把 $\texttt{A,B,C}$ 看成 $0,1,2$。此时做对 $3$ 同余意义下的差分可以发现，不合法的条件是两个连续的 $1$。

考虑形如 $\texttt{ABCABCAB}$ 的连续段，钦定他的起点并容斥。我们只需要确定前三位，后面都不用管了。

假设一共有 $i$ 段不合法段，每段起点处只能有 $2$ 种填法（特别地，第一个数是 $3$ 种）而中间的位置已经确定。

还是推一下式子吧。第一部分显然是随机排列没被钦定的连续段，这一部分是 $\displaystyle\binom{a+b+c-3i}{a-i,b-i,c-i}$，起点的权值贡献刚才已经说了，选择起点的方案数是 $\displaystyle \binom{a+b+c-2i-1}{i}$。还有容斥系数是 $(-1)^i$。

时间复杂度 $O(n)$。

---

## 作者：JWRuixi (赞：2)

~~/bx H6_6Q~~

### 题意

求有多少长度为 $a+b+c$ 的只包含 `A`、`B`、`C` 的字符串，满足：

- 恰好有 $a$ 个 `A`，$b$ 个 `B`，$c$ 个 `C`。
- 不包含形如 `ABC`、`BCA`、`CAB` 的子串。

### 分析

> 不包含是困难的，但是包含看上去就是容易的，所以考虑容斥。—— H6_6Q

发现这种连续字串是循环的，也就是说，它可以一直往下固定的延展。那么只需要知道起始字母、起点和长度就能确定这样一个不合法的子串，于是我们容斥起点。

设 $p$ 是一个非法子串的起点，$s$ 是这个字符串。那么我们容斥的子串显然要极大，所以会满足 $s_{p-1}\not =s_p$。且且长度大于等于 $3$，于是我们将 `ABC` 绑定，令长度等于 $3$，于是就不用关心它的后继。

若枚举当前有 $i$ 个起点，那么可以先将剩下的 $a+b+c-3i$ 个字符先排序，方案数 $\dbinom{a+b+c-3i}{a-i,b-i,c-i}$；接下来考虑将这 $i$ 个绑定的子串扔进去，因为前驱已经固定，所以 $s_p$ 显然有 $2$ 种取值（注意字符串开头有 $3$ 种，要分类讨论），方案数 $2^i$；容斥系数显然是 $(-1)^i$。

那就做完了！

### Code

提交记录：<https://atcoder.jp/contests/agc058/submissions/43331554>。

---

## 作者：Unnamed114514 (赞：1)

总的方案数是非常好求的，所以容斥。

发现不合法串是可重合的，直接容斥不是很好算，所以可以钦定长度为 $3$ 的不合法串的数量。

若 $[i,i+2]$ 为长度为 $3$ 的不合法串，$i+3$ 有两种方法，但是如果 $[i,i+2]$ 为原串后缀就有 $3$ 种方法。

对是否存在后缀进行分讨：

- 存在后缀，此时相当于 $m+1$ 个盒子放 $i-1$ 个球，盒子可以为空，就是 $C_{m+i-1}^{m}\times 2^{i-1}\times 3$。

- 不存在后缀，此时相当于 $m$ 个盒子放 $i$ 个球，盒子可以为空，就是 $C_{m+i-1}^{m-1}\times 2^i$。

还要乘上其它位置随便放的方案数，计算方法同总方案数一致。

---

## 作者：SudoXue (赞：0)

[更好的阅读体验](https://www.cnblogs.com/xueruhao/p/18994510)

题目要求在总长度 $n=A+B+C$ 的排列中统计既定字母数且完全不出现子串 `ABC`、`BCA`、`CAB` 的方案数，结果对 $998244353$ 取模。核心做法是把三个禁止的视作一个循环串 $A\to B\to C\to A$ 上长度为 $3$ 的滑动窗口，用容斥原理把**出现至少一段非法三连**转化为**精确出现 $i$ 段非法三连的加减和**。若钦定了 $i$ 段非法块，就先把每块末尾的三个固定字母拿掉，剩余 $m=n-3i$ 个位置用插板法在整体中穿插；此时需要放 $A-i$ 个 `A`、$B-i$ 个 `B`、$C-i$ 个 `C`，排列数为 $\binom{m}{A-i}\binom{m-(A-i)}{B-i}$。随后把被抽出的三元锚点插回串中：锚点之间共有 $m+i$ 个隔板，一次性选出 $i$ 个隔板可用 $\binom{m+i-1}{i}$；每段末尾的三个字母里前两位已经确定，第 $3$ 位只能在两种合法字母里选，所以有额外 $2^i$；若最左侧锚点左边没有字符则多出一种选法，需要补上一项 $\binom{m+i-1}{i-1}2^{i-1}3$。整理后第 $i$ 项贡献为

$$
(-1)^i\bigl[\binom{m}{A-i}\binom{m-(A-i)}{B-i}\bigr]\bigl[\binom{m+i-1}{i}2^{i}+\mathbf 1_{i\ge1}\binom{m+i-1}{i-1}2^{i-1}3\bigr]
$$

枚举 $i=0\ldots\min\{A,B,C\}$ 累加即可。

时间复杂度 $O(n)$。

[link](https://atcoder.jp/contests/agc058/submissions/67784152)

---

## 作者：_Cheems (赞：0)

题意：用 $a,b,c$ 个 $A,B,C$ 组成字符串，问有多少个串满足不存在 $ABC,BCA,CAB$ 子串。$a,b,c\le 10^6$。

数数好题捏。

需要有以下的观察：

1. 三种不同的不合法串就是 $ABC$ 分别以 $A,B,C$ 开头循环得到的串。
2. 非法串存在传递性。这里的非法串 $[l,r]$ 指满足 $i\in [l,r-2]$ 均为不合法串的起点。由前者易知若两个非法串相交，则会得到合并一个更大的非法串。

直接对非法串容斥并不是很好做。然后本题很巧的一步来了：对**极大**非法串的**起点**容斥。

好处有两点：

1. 无需枚举非法串的长度，只需保证其 $\ge 3$，也就是只填 $3$ 位即可。
2. “极大非法串的起点”很好维护，先确定非法串位置而不填，那么每个串恰有 $2$ 种填法，只需起点与它前面的字母不同即可。假如前面没有字母就随便填。

现在是容易计数了。具体来说，枚举有 $i$ 个非法串，先让 $a+b+c-3i$ 个字母任意排列。然后插入非法串起始部分，先确定位置再确定字母，只需分讨一下是否有非法串在开头部分即可。

$O(n)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ADD(a, b) a = (a + b) % mod
const int N = 4e6 + 5, mod = 998244353, inv2 = 499122177;
int a, b, c, ans, jc[N], jcinv[N];

inline int qstp(int a, int k) {int res = 1; for(; k; a = a * a % mod, k >>= 1) if(k & 1) res = res * a % mod; return res;}
inline int C(int n, int m){
	if(n < 0 || m < 0 || n < m) return 0;
	return jc[n] * jcinv[m] % mod * jcinv[n - m] % mod;
}
inline int CC(int n, int m){
	if(m == 0 && n == 0) return 1;
	return C(n + m - 1, m - 1);
}
signed main(){
	jc[0] = jcinv[0] = 1;
	for(int i = 1; i < N; ++i) jc[i] = jc[i - 1] * i % mod;
	jcinv[N - 1] = qstp(jc[N - 1], mod - 2);
	for(int i = N - 2; i; --i) jcinv[i] = jcinv[i + 1] * (i + 1) % mod;
	
	cin >> a >> b >> c;
	for(int i = 0, pw = 1, pw2 = 1; i <= min(a, min(b, c)); ++i){
		int res, res2;
		res = jc[a + b + c - 3 * i] * jcinv[a - i] % mod * jcinv[b - i] % mod * jcinv[c - i] % mod;
		res2 = CC(i, a + b + c - 3 * i) * pw2 % mod;
		ADD(res2, CC(i - 1, a + b + c - 3 * i + 1) * pw2 % mod * inv2 % mod * 3ll % mod); 
		ADD(ans, res * res2 % mod * pw % mod) % mod;
		pw = (pw == 1 ? (mod - 1) : 1);
		pw2 = pw2 * 2ll % mod;
	}
	cout << ans;
	return 0;
}

```

---

## 作者：larsr (赞：0)

评分虚高，感觉只有紫。十几分钟就秒了。

首先一眼容斥，至于怎么容就是关键了。

如果以 $x$ 和 $x+2$ 为起点的子串不满足条件，那么 $x+1$ 为起点的子串也不满足条件。容斥只考虑不合法子串连续段的最后一段子串。即只考虑 $S_{x\ldots x+2}$ 不满足条件且 $S_{x+1\ldots x+3}$ 满足条件。这样子容斥不重不漏，并且考虑的每个子串都占用 $A,B,C$ 各一个，复杂度线性。

考虑枚举 $0\le k\le \min(a,b,c)$，有 $k$ 个需要考虑的子串时的贡献。

- 若 $k=0$。

$$\frac{(a+b+c)!}{a!b!c!}$$

- 有一个需要考虑的子串在末尾，若 $0<3k < a+b+c$，先用组合数计算这些子串位置的方案数，在末尾的子串 $3$ 个情况都可以，其它的子串根据它后面的那个字符决定它只有 $2$ 个情况，然后再计算除去考虑的子串其它字符位置情况。

$$3(-1)^kC_{a+b+c-3k-1}^{k-1}2^{k-1}\frac{(a+b+c-3k)!}{(a-k)!(b-k)!(c-k)!}$$

- 没有需要考虑的子串在末尾，若 $0<3k$。与上面的情况类似，不讲了。

$$(-1)^kC_{a+b+c-3k-1}^{k}2^k\frac{(a+b+c-3k)!}{(a-k)!(b-k)!(c-k)!}$$

[sub](https://atcoder.jp/contests/agc058/submissions/63110534)

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/solution/AT_agc058_d)

**题目大意**

> 求有多少 $a$ 个 $\texttt A$，$b$ 个 $\texttt B$，$c$ 个 $\texttt C$ 构成的字符串使得不存在子串 $\texttt{ABC},\texttt{BCA},\texttt{CAB}$。
>
> 数据范围：$a,b,c\le 10^6$。

**思路分析**

记 $n=a+b+c$。

考虑容斥，钦定若干个 $i$ 使得 $s[i,i+2]$ 不合法，但是此时可能会同时钦定到 $i,i+1$ 从而导致两个不合法段拼起来了。

因此我们不妨枚举极长的被钦定不合法的段，先求容斥系数，设 $p_i$ 表示段长为 $i$ 时的容斥系数，那么考虑上一个被钦定的位置有 $p_i=-p_{i-1}-p_{i-2}$。

边界条件是 $p_2=0,p_3=-1$，从而得到 $p_{3k}=-1,p_{3k+1}=1,p_{3k+2}=0$（$k>0$）。

枚举每一段的长度，会发现此时的序列形如：若干个被钦定的 $\texttt{ABC}$ 循环串和一些没限制的字符。

- 长度为 $3k$ 的串相当于 $k$ 个 $\texttt{ABC}$，但有 $3$ 种方法选颜色。
- 长度为 $3k+1$ 的串相当于 $k$ 个 $\texttt{ABC}$ 和一个自由字符。
- 自由字符可以看成 $k=0$ 的长度为 $3k+1$ 的串。

因此设 $f_{i,j}$ 表示当前字符串长度为 $i$，钦定 $j$ 个 $\texttt{ABC}$ 循环串的容斥系数，有转移：
$$
f_{i,j}=\sum_{k\ge 0} f_{i-3k-1,j-1}-3\sum_{k\ge 1}f_{i-3k,j}
$$

答案为 $\sum \binom{n-3i}{a-i,b-i,c-i}f_{n,n-3i}$。

考虑如何求 $f$，用二元生成函数，设 $F(x,y)=\sum f_{i,j}x^iy^j$，转移系数为 $G(x,y)$，那么 $F(x,y)=\sum_{k\ge 0} G^k=\dfrac{1}{1-G}$。

其中 $G(x,y)=\sum_{k\ge 0}x^{3k+1}y-3\sum_{k\ge 1} x^{3k}=\dfrac{xy-3x^3}{1-x^3}$，因此 $F(x,y)=\dfrac{1-x^3}{1-xy+2x^3}$。

我们只要求 $[x^uy^v]\dfrac{1}{1-xy+2x^3}$ 即可，即 $[x^uy^v]\sum_{i\ge 0}(xy-2x^3)^i$，那么最终对答案有贡献的项就是 $(xy)^v(-2x^3)^{(u-v)/3}$，直接计算二项式系数即可 $\mathcal O(1)$ 计算。

最终答案需要 $\mathcal O(n)$ 项系数，预处理组合数后直接计算即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD=998244353,MAXN=3e6+5;
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b=b>>1) if(b&1) ret=ret*a%p;
	return ret;
}
ll fac[MAXN],ifac[MAXN];
ll C(int n,int m) { return fac[n]*ifac[m]%MOD*ifac[n-m]%MOD;}
ll F(int n,int m) {
	if(n<m) return 0;
	n=(n-m)/3;
	return ksm(MOD-2,n)*C(n+m,m)%MOD;
}
signed main() {
	int x,y,z,n;
	scanf("%d%d%d",&x,&y,&z),n=x+y+z;
	for(int i=fac[0]=1;i<=n;++i) fac[i]=fac[i-1]*i%MOD;
	ifac[n]=ksm(fac[n]);
	for(int i=n;i;--i) ifac[i-1]=ifac[i]*i%MOD;
	ll ans=0;
	for(int i=0;i<=min({x,y,z});++i) {
		ans=(ans+C(n-3*i,x-i)%MOD*C(n-x-2*i,y-i)%MOD*(F(n,n-3*i)-F(n-3,n-3*i)))%MOD;
	}
	printf("%lld\n",(ans+MOD)%MOD);
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：0)

不合法的子串很有意思，尝试对其进行刻画。

发现若 $s_{i,i+2}$ 和 $s_{i+1,i+3}$ 均不合法可推出 $s_{i,i+3}$ 不合法。即不合法关系具有传递性。

那么思路就很清晰了，考虑容斥每个极长不合法连续串的起点。

考虑一个点是起点的条件，首先是其往前不可再拓展，其次是其往后需能拓展至少两次。

将长度为 $3$ 的不合法串捆起来做隔板法即可（要特判是否有串被放在了开头），注意 $\texttt{ABC,BCA,CAB}$ 是不等价的，所以还要乘一个 $2$ 的幂次，此外，剩下的字符是随便排的，这个是一个多重集排列，也是容易的。

记得乘上容斥系数 $-1$ 的幂次。

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/agc058/submissions/53068039)

---

## 作者：xcyyyyyy (赞：0)

做过的题目，应该比较经典了。

首先一般的想法是容斥不合法的连续三个的第一个的位置数量，但是容斥后我们并不好做。

我们考虑容斥连续一段不合法的起点个数 $i$，此时还剩下 $a-i$ 个 $A$，$b-i$ 个 $B$，$c-i$ 个 $C$，另外 $A，B，C$ 三个组合在一起。

我们先将 $a-i$ 个 $A$，$b-i$ 个 $B$，$c-i$ 个 $C$ 排列一下 $\tbinom{a+b+c-3i}{a-i,b-i,c-i}$。

考虑插入 $i$ 个组合，因为这些必须为起点，定了插入位置后，若前面有一个字符，那么该组合只能选择两种，具体的说，若前面是 $A$，那么跟着他的组合只能是 $ABC,CAB$。其他同理。

我们只需要先讨论是否有一个组合在开头即可，剩下的就是小球放盒子的问题了。

这道题的重点就是：容斥的是不合法的段起点个数。

[code](https://atcoder.jp/contests/agc058/submissions/52263808)

---

