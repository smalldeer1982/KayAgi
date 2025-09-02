# New Year and Original Order

## 题目描述

Let $ S(n) $ denote the number that represents the digits of $ n $ in sorted order. For example, $ S(1)=1,S(5)=5,S(50394)=3459,S(353535)=333555 $ .

Given a number $ X $ , compute ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908G/86189a2fc1d31a8560e966bada6dfd32afab65e2.png) modulo $ 10^{9}+7 $ .

## 说明/提示

The first few values of $ S $ are $ 1,2,3,4,5,6,7,8,9,1,11,12,13,14,15,16,17,18,19,2,12 $ . The sum of these values is $ 195 $ .

## 样例 #1

### 输入

```
21
```

### 输出

```
195
```

## 样例 #2

### 输入

```
345342
```

### 输出

```
390548434
```

# 题解

## 作者：C20203030 (赞：36)

__题目背景__

在某一场省选模拟赛之后，$\tt zxy$ 凝视着无比简洁的做法，轻轻叹息了一句：

**朝算贡献，夕死可矣。**

__题目描述__

[点此看题](https://www.luogu.com.cn/problem/CF908G)

设 $f(x)$ 表示将 $x$ 的所有数码从小到大排序所得的数（忽略前导 $0$ ），求 $\sum_{i=1}^X f(i)$

$n\leq 700$，表示 $X$ 的位数

__解法__

讲一个 $O(10^2n)$ 吊打全场的做法，我用这个做法跑到了洛谷 $\tt rank1$

$n$ 这么大就考虑数位 $dp$ 吧，但你发现直接算根本不行，因为加入一个数之后会影响到很多数字的贡献。

那么我们就不要跑一次算贡献，我们跑 $9$ 次算出每种数字 $d$ 的贡献，**每次只考虑一种数字的贡献是及其简单的**

设 $f(i,0/1)$ 表示算到了第 $i$ 位，是否顶到了上界，对于数位 $d$ 的总贡献，$g(i,0/1)$ 表示算到了第 $i$ 位，是否顶到了上界，假设在此基础上加入数字 $d$ 的贡献应该是多少，转移枚举填入的数字。

$f$ 的转移：

- 填的数字小于 $d$ ：$f(i)\leftarrow f(i-1)$，表示排在前面不会对贡献有影响

- 填的数字就是 $d$ ：$f(i)\leftarrow g(i-1)+10\cdot f(i-1)$，表示可以让以前的 $d$ 右移，并且这个 $d$ 的贡献是 $g(i-1)$
- 填的数字大于 $d$ ：$f(i)\leftarrow 10\cdot f(i-1)$，表示可以让以前的 $d$ 右移

$g$ 的转移：

- 填的数字小于等于 $d$ ：$g(i)\leftarrow g(i-1)$，表示不会对前面的贡献有影响
- 填的数字大于 $d$ ：$g(i)\leftarrow 10\cdot g(i-1)$，表示会让填入的 $d$ 右移

那么递推一下就可以做到 $O(10^2n)$

----

再讲一下考试时候的想法吧，如果觉得没什么价值可以跳过。

因为考试时候我是不会数位 $dp$ 做法的，我想的是看 $f(x)$ 什么样子再去算对应的 $x$ 有多少个。

如果 $n=999....999$ 这种情况可以直接做背包（用可重集的排列），然后我们枚举 $x$ 的前几位（和上界 $n$ 相同），就可以套 $n=999...999$ 的做法，直接做时间复杂度 $O(10^2n^3)$，某位巨佬用生成函数优化转移可以做到 $O(10^2n\log n)$

下面给出的是 $O(10^2n)$ 的好做法

```c++
#include <cstdio>
#include <cstring>
const int MOD = 1e9+7;
const int M = 1005;
#define int long long
int read()
{
	int x=0,f=1;char c;
	while((c=getchar())<'0' || c>'9') {if(c=='-') f=-1;}
	while(c>='0' && c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int n,d,ans,g[M][2],f[M][2];char s[M];
void dp()
{
	memset(f,0,sizeof f);
	memset(g,0,sizeof g);
	g[0][1]=d;
	for(int i=0;i<n;i++)
		for(int j=0;j<=1;j++)
		{
			int t=s[i+1]-'0';
			for(int k=0;k<=9;k++)//枚举填的数
			{
				if(j && k>t) break;
				int op=(j&&k==t);
				if(k<d)
				{
					f[i+1][op]=(f[i+1][op]+f[i][j])%MOD;
					g[i+1][op]=(g[i+1][op]+g[i][j])%MOD;
				}
				if(k==d)
				{
					f[i+1][op]=(f[i+1][op]+g[i][j]+10*f[i][j])%MOD;
					g[i+1][op]=(g[i+1][op]+g[i][j])%MOD;
				}
				if(k>d)
				{
					f[i+1][op]=(f[i+1][op]+10*f[i][j])%MOD;
					g[i+1][op]=(g[i+1][op]+10*g[i][j])%MOD;
				}
			}
		}
	ans=(ans+f[n][0]+f[n][1])%MOD;
}
signed main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	for(d=1;d<=9;d++)//算贡献
		dp();
	printf("%lld\n",ans);
}
```





---

## 作者：天才byt (赞：15)

### CF 908G

令 $S(n)$ 表示将 $n$ 的各位数字升序排序并去掉前导零之后形成的数。给出 $X$，求：
$$
\sum_{i = 1}^X S(i)
$$
$X \leq 10^{700}$。

-----------

很显然的思路是按每一个数字在每一位上拆开考虑。如果我们能求出 $f(i, j)$ 表示有多少个数的 $S()$ 满足第 $j$ 位（从右向左，个位为第 $1$ 位）是 $i$，那么答案就是
$$
\sum_{k = 1}^9 k \times \sum_{i = 1}^{\text{len}} 10^{i - 1} \times f(k, i)
$$
dp 是没什么方法直接求出第 $j$ 位恰好是 $i$ 的（需要 $O(700^39)$ 的复杂度）。

不过这道题既然是“每一位排序之后”，我们不妨可以把每个数表示为若干个 $111\cdots 1$ 的和，例如 $3459$ 就是：
$$
\begin{aligned}
1111\\
1111\\
1111\\
111\\
11\\
1\\
1\\
1\\
1\\
\end{aligned}
$$
事实上，对于每第 $i$ 行，其 $1$ 的个数，正是原数中大于等于 $i$ 的数位的个数。

所以如果我们能计算出，对于 $d \in [1, 9]$，有多少个数满足在第 $i$ 位以及 $i$ 位右边，都大于等于 $d$，并且第 $i$ 位左边是小于 $d$ 的，那么其贡献就是 $\underbrace{11\cdots1}_{i}$。

即若一个数恰好有 $i$ 位数大于等于 $d$，那么贡献就是 $\underbrace{11\cdots1}_{i}$。

dp，$f(i, j, 0/1)$ 表示放了 $i$ 个数，有恰好 $j$ 位大于等于 $d$，是否压上界。

```cpp
void work(int x) {
	memset(f, 0, sizeof f);
	rep(i, 0, digit[1]) f[1][(i >= x)][i == digit[1]]++;
	rep(i, 1, len - 1) {
		rep(j, 0, len - 1) {
			rep(flg, 0, 1) {
				int& slf = f[i][j][flg];
				if (!slf) continue;
				rep(nxt_digit, 0, flg ? digit[i + 1] : 9) {
					add(f[i + 1][j + (nxt_digit >= x)][flg && nxt_digit == digit[i + 1]], slf);
				}
			}
		}
	}
	int pow_10 = 0;
	rep(i, 0, len) {
		add(ans, 1ll * pow_10 * (f[len][i][0] + f[len][i][1]) % P);
		pow_10 = (1ll * pow_10 * 10 + 1 )% P;
	}
}

```



---

## 作者：Rainybunny (赞：12)

# $\mathcal{Description}$

&emsp;&emsp;[Link](https://www.luogu.com.cn/problem/CF908G).

&emsp;&emsp;对于 $x\in\mathbb N^*$，令 $s(x)$ 表示将 $x$ 十进制下的各位数码排序后得到的十进制数的值。求 $\sum_{i=1}^X s(i)$ 对 $(10^9+7)$ 取模的结果。

&emsp;&emsp;$X\le10^{700}$。

# $\mathcal{Solution}$

&emsp;&emsp;下记 $m=10$（进制），$n=\lceil\log_mX\rceil$。

## $\mathcal{Case~1}$

&emsp;&emsp;市面上的题解做法。

&emsp;&emsp;考虑到“数码有序”的特性：$\forall x,~s(x)$ 可以表示为若干个 $11\dots1$ 之和。对于 $d\in[1,9]$，$d$ 显然在 $s(x)$ 中占有连续的一段，那么 $s(x)$ 有形如 $\sum_d \underbrace{dd\dots d}_a\underbrace{00\dots0}_b$ 的形式，其中 $a$ 表示 $d$ 的个数，$b$ 表示大于 $d$ 的数码个数。根据上述特性，它可以转化为 $\sum_d\underbrace{11\dots1}_a\underbrace{11\dots1}_b$，就能直接 DP 计算啦。

&emsp;&emsp;令 $f_d(i,j,0/1)$ 表示当前的 $x$ 填到了从高到低第 $i$ 位，且有 $j$ 个数码大于等于 $d$，是否被 $X$ 限制的方案数，转移枚举第 $i+1$ 位所填的数码即可。最终答案为
$$
\sum_{d=1}^{m-1}\sum_{l=1}^n(\underbrace{11\dots1}_l)f_d(n,l,0)+f_d(n,l,1)
$$
&emsp;&emsp;复杂度 $\mathcal O(m^2n^2)$。

## $\mathcal{Case~2}$

&emsp;&emsp;一种粗暴但是实用的 GF 做法。

&emsp;&emsp;本节记 $v_i=\underbrace{11\dots1}_i$。

&emsp;&emsp;对于上界 $X$，不管什么做法都很难带着这种限制算。考虑枚举 $x$ 中从高到低第一个严格小于 $X$ 的数码位置 $p$ —— 即 $x$ 的第 $1\sim p-1$ 位与 $X$ 相同，第 $p$ 位小于 $X$。同时，记 $c_i$ 示 $X$ 的 $1\sim p-1$ 位中数码 $i$ 的出现次数，它们在 $x$ 中亦出现，且位置已经固定。当然，还需要枚举第 $p$ 位的值。

&emsp;&emsp;注意到 $x$ 的第 $p+1\sim n$ 位已经不必担心限制，可以用单纯的计数 DP 而非数位 DP 进行求解。我们以 $1\sim 9$ 的顺序将数码填入这 $n-p$ 个位置中，没填的位置视为 $0$（不影响 $s(x)$ 的值），设 DP 状态：

-   $g_{i,j}$ 表示用 $1\sim i$ 的数码填 $j$ 个位置的方案数；
-   $f_{i,j}$ 表示用 $1\sim i$ 的数码填 $j$ 个位置，得到的所有 $x$ 的 $s(x)$ 之和。（再次强调，没填的位置视为 $0$）。 

&emsp;&emsp;对于 $g_{i,j}$ 的转移，枚举数码 $i$ 的个数，得到
$$
g_{i,j}=\sum_{k=0}^j\binom{j}{k}g_{i-1,j-k}
$$
&emsp;&emsp;对于 $f_{i,j}$ 的转移，数码 $i$ 会把 $s(x)$ 本来的值整体向高位位移（因为 $s(x)$ 当时只有 $1\sim i-1$ 的数码，都小于 $i$），然后低位补上 $dd\dots d$。具体有
$$
f_{i,j}=\sum_{k=0}^j\binom{j}{k}\left(f_{i-1,j-k}\cdot m^{k+c_i}+g_{i-1,j-k}\cdot iv_{k+c_i}\right)
$$
&emsp;&emsp;我们可以用它们表示出当前 $p$ 对答案的贡献 $\text{ans}_p$ 为：
$$
\text{ans}_p=\sum_{k=0}^{n-p}\binom{n-p}{k}f_{m-1,k}
$$
注意 $f_{m-1,k}$ 中的 $k$ 只考虑了内部选位置的方案，所以外面还得带一个组合数。

&emsp;&emsp;DP 在此告一段落，如此暴力求答案的复杂度是枚举前缀的 $\mathcal O(nm)$ 套 DP 的 $\mathcal O(n^2m)$ 即 $\mathcal O(m^2n^3)$ 的。

---

&emsp;&emsp;接下来引入 EGF，令
$$
G_i(x)=\sum_{j=0}^{n-p-1}g_{i,j}x^j\\
F_i(x)=\sum_{j=0}^{n-p-1}f_{i,j}x^j
$$
尝试化简它们，从递推式入手：
$$
g_{i,j}=\sum_{k=0}^j\binom{j}{k}g_{i-1,j-k}
$$
$$
\Rightarrow~~~~\frac{g_{i,j}}{j!}=\sum_{k=0}^j\frac{g_{i-1,j-k}}{(j-k)!}\cdot\frac{1}{k!}
$$
后者很显然是一个卷积形式，套入 EGF 就有：
$$
\Rightarrow~~~~[x^j]G_i(x)=\sum_{k=0}^j[x^{j-k}]G_{i-1}(x)\cdot[x^k]e^x
$$
$$
\Rightarrow~~~~G_i(x)=e^xG_{i-1}(x)
$$
$$
\Rightarrow~~~~G_i(x)=e^{ix}
$$
&emsp;&emsp;类似的，对于 $F$ 有
$$
f_{i,j}=\sum_{k=0}^j\binom{j}{k}(m^{k+c_i}f_{i-1,j-k}+g_{i-1,j-k}\cdot iv_{k+c_i})
$$
$$
\Rightarrow~~~~\frac{f_{i,j}}{j!}=\sum_{k=0}^j\left(\frac{m^{c_i}m^k}{k!}\cdot\frac{f_{i-1,j-k}}{(j-k)!}+i\cdot\frac{g_{i-1,j-k}}{(j-k)!}\cdot\frac{m^{c_i}v_k+v_{c_i}}{k!}\right)
$$
$$
\Rightarrow~~~~F_i(x)=m^{c_i}e^{mx}F_{i-1}(x)+iG_{i-1}(x)\left(m^{c_i}V(x)+v_{c_i}e^x\right),~~~~\text{let }V(x)=\sum_{i=0}^{+\infty}v_ix^i
$$
$$
\Rightarrow~~~~F_i(x)=m^{c_i}e^{mx}F_{i-1}(x)+ie^{(i-1)x}(m^{c_i}V(x)+v_{c_i}e^x)
$$
发现这是关于 $F_i(x)$ 的常系数线性递推，令
$$
p_i=m^{c_i}e^{mx}\\
q_i=ie^{(i-1)x}(m^{c_i}V(x)+v_{c_i}e^x)
$$
则
$$
F_i(x)=p_iF_{i-1}(x)+q_i
$$
美观多啦，手代一下就能展开成通项：
$$
F_i(x)=\sum_{k=1}^iq_k\prod_{j=k+1}^ip_j
$$
&emsp;&emsp;进一步，代入 $\text{ans}_p$ 的式子：
$$
\begin{aligned}
\frac{\text{ans}_p}{(n-p)!}&=[x^{n-p}]e^xF_{m-1}(x)\\
&=[x^{n-p}]e^x\sum_{k=1}^{m-1}q_k\prod_{j=k+1}^{m-1}p_j\\
&=[x^{n-p}]\sum_{k=1}^{m-1}\left(ke^{kx}(m^{c_k}V(x)+v_{c_k}e^x)\right)\left(\prod_{j=k+1}^{m-1}m^{c_j}e^{mx}\right)\\
&=[x^{n-p}]\sum_{k=1}^{m-1}k\left(\prod_{j=k+1}^{m-1}m^{c_j}\right)(m^{c_k}e^{(m(m-1-k)+k)x}V(x)+v_{c_k}e^{(m(m-1-k)+k+1)x})\\
\end{aligned}
$$
卡住啦，瓶颈在于求 $e^{(m(m-1-k)+k)x}V(x)$。来看看 $V(x)$ 是什么……
$$
\begin{aligned}
V(x)&=\sum_{i=0}^{+\infty}\frac{m^i-1}{m-1}\cdot\frac{x^i}{i!}\\
&=\frac{1}{m-1}(e^{mx}-e^x)\\
&=\frac{e^x}{m-1}(e^{(m-1)x}-1)
\end{aligned}
$$
大力丢进去，有
$$
\begin{aligned}
e^{(m(m-1-k)+k)x}V(x)&=\frac{1}{m-1}e^{(m(m-1-k)+k+1)x}(e^{(m-1)x}-1)

\end{aligned}
$$
天呐它果然封闭，可以 $\mathcal O(1)$ 算系数。那么整个算法就是 $\mathcal O(nm)$ 枚举 $p$ 套 $\mathcal O(m)$ 求 $\text{ans}_p$，即 $\mathcal O(m^2n)$ 的。

## $\mathcal{Case~3}$

&emsp;&emsp;来冷静并反复刺激一下大脑叭~

&emsp;&emsp;研究某个 $x$ 及其 $s(x)$，设 $x$ 中数码出现次数为 $c_{0..9}$，则
$$
s(x)=\sum_{i=1}^{m-1}\frac{m^{\sum_{j=i}^{m-1}c_j}-1}{m-1}
$$
实质上就是 $\mathcal{Case~1}$ 中 $11\dots 1$ 的转化。然后类似 $\mathcal{Case~2}$ 地，枚举 $x$ 与 $X$ 的相同前缀及下一位严格小于 $X$ 的数码。还是记枚举的位置 $p$，前缀中数码出现次数为 $c_{0..9}$。把上式 $\sum_{j=i}^{m-1}c_j$ 处理为后缀和 $s_i$，那么 $\text{ans}_p$ 有
$$
\text{ans}_p=\frac{1}{m-1}\sum_{i=1}^{m-1}\sum_{j=0}^{n-p}\binom{n-p}{j}(i-1)^{n-p-j}(m-i)^p(m^{s_i+j}-1)
$$
注意其中 $j$ 枚举的是“大于等于 $i$ 的数码个数”。瞪一下和式里面，显然可以把形如二项式展开的这一坨拍回去。记 $l=n-p$，推一推：
$$
\begin{aligned}
\sum_{j=0}^{l}\cdots&=m^{s_i}\sum_{j=0}^l\binom{l}{j}(i-1)^{l-j}(m-i)^jm^j-(m-1)^l\\
&=m^{s_i}(m(m-i)+i-1)^l-(m-1)^l
\end{aligned}
$$
扫前缀的过程中顺带维护一下这个式子，~~Tiw：~~可以做到 $\mathcal O(mn)$。

---

## 作者：Kelin (赞：9)

题意:定义函数$S(x)$是把$x$各数位排序后得到的数,求$\sum_{i=1}^nS(i)$

$S(2018)=128,S(998244353)=233445899$

$n\le10^{700}$

------
看着$n$这么大显然是[数位$DP$](http://blog.csdn.net/wust_zzwh/article/details/52100392)了

扒一下官方题解

---

This is a digit $dp$ problem. Let's try to solve the subproblem "How many ways can the$i-th$ digit be at least $j$?". Let's fix $j$, and solve this with $dp$. We have a dp state $dp[a][b][c]$=number of ways given we've considered the first a digits of $X$, we need $b$ more occurrences of digits at least $j$, and $c$ is a boolean saying whether or not we are strictly less than $X$ or not yet.

For a fixed digit, we can compute this dp table in $O(n^2)$ time, and then compute the answers to our subproblem for each $i$ ($i.e.^1$ by varying $b$ in our table).

1.$i.e.$ $\Rightarrow$in other words/this is

----
考虑到原问题很难做,我们转换一下问题

举个例子:假设第$i$位填$3$,那么他的贡献的$3*10^i$,考虑把这个贡献拆开

$3\ge3,3\ge2,3\ge1$我们在这一位填$1,2,3$时都记上$10^i$的贡献

那么我们就只要记这一位填大于等于某个数的方案数就好了

考虑~~按照套路~~设$dp[i][j][k][l]$表示前$i$位有$j$位的数字大小大于等于$k$,是否严格小于$n$的方案数

枚举第$i+1$位填$p$

$f[i+1][j+(p>=k)][k][l|(p<a_{i+1})]=\sum f[i][j][k][l]$

然后实际上假设前$n$位我们$j$位数字大于等于$k$的方案数是$sum=f[n][j][k][0]+f[n][j][k][1]$

这个对答案的贡献的是$sum*\underbrace{111\ldots11}_{j\text{个}1}$

```
 #include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
using namespace std;
const int N=705,P=1e9+7;
int n,ans,a[N],f[N][N][10][2];char s[N];
inline void add(int&a,int b){a+=b,a>=P?a-=P:0;}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    scanf("%s",s+1);n=strlen(s+1);
    fp(i,1,n)a[i]=s[i]-48;
    fp(i,0,9)f[0][0][i][0]=1;
    fp(i,0,n-1)fp(j,0,i)fp(k,1,9)fp(l,0,1)fp(p,0,(l?9:a[i+1]))
         add(f[i+1][j+(p>=k)][k][l|(p<a[i+1])],f[i][j][k][l]);
    fp(k,1,9){
        int tp=1;
        fp(i,1,n)add(ans,1ll*tp*(f[n][i][k][0]+f[n][i][k][1])%P),tp=(10ll*tp+1)%P;
    }printf("%d",ans);
return 0;
}
```
发现这个转移是可以滚动的,而且每一个$k$还可以分开考虑贡献

~~所以泥萌可以自己再卡一卡常数~~

---

## 作者：tommy0221 (赞：7)

[CF908G New Year and Original Order](https://www.luogu.com.cn/problem/CF908G)

题意：给 $n<=10^{700}$ ，问 $1$ 到 $n$ 中每个数在各数位排序后得到的数的和，答案对 $10^9+7$ 取模。 

太久没写数位dp了，调到自闭。感谢 $\color{black}{\texttt{z}}\color{red}{\texttt{houakngyang}}$ 耐心的指导

每一个数排序以后可以拆成 $9$ 个形如 $111\cdots1$ 数的和（比如 $223=111+111+1+0+0+\cdots+0$）

对于每一个 $1\le i \le 9$ ，当这一位的值不小于 $i$ 的时候，$i$ 所对应的 $1$ 串长度会增加 $1$

考虑数位dp出 “对于某一个 $i$ 恰有 $j$ 个 $1$”的数量

状态开 $4$ 维，分别表示：在第几位，是否顶到上界，还需要几个不小于 $i$ 的值，$i$ 

就可以转移了

状态总数是 $n^2*10$ 的，可以通过

考虑枚举 $i,j$ 计算答案

$ans=\sum\limits_{j=1}^{9}\sum\limits_{i=1}^{n}dp[i][j]*f[j]$

$f[j]$ 表示有 $j$ 个 $1$ 的串的值

~~我忘记开-Wall导致一个变量没用调了一下午~~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 705
#define mod 1000000007
char s[N];
int d[N],dp[N][N][10];
void fmod(int&x){x-=mod,x+=x>>31&mod;}
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
int dfs(int pos,int limit,int sum,int low){
	if(!pos)return !sum;
	if(!limit&&~dp[pos][sum][low])return dp[pos][sum][low];
	int res=0,up=limit?d[pos]:9;
	for(int i=0;i<=up;++i)fmod(res+=dfs(pos-1,limit&&i==up,sum-(i>=low),low));
	if(!limit)dp[pos][sum][low]=res;
	return res;
}
int solve(char*s){
	int res=0;
	d[0]=0;int n=strlen(s+1);
	for(int i=1,j=n;i<=n;++i,--j)d[j]=s[i]-'0';
	for(int i=1;i<=9;++i)
		for(int j=1,now=1;j<=n;++j,now=(10ll*now+1)%mod)
			fmod(res+=1ll*dfs(n,1,j,i)*now%mod);
	return res;
}
signed main(){
	memset(dp,-1,sizeof(dp));
	scanf("%s",s+1);
	printf("%d\n",solve(s));
}
```

---

## 作者：GavinZheng (赞：5)

我们首先考虑对于任意一个数，数字$k$对答案的贡献：$c(k)=\sum_{digit[i]=k}10^i$

那么任意一个数对答案的贡献就是：

$ans=\sum_{k=1}^9 k\cdot c(k)$

因为后面这个“限制数字固定为多少”，数位DP不太好求。所以我们考虑把他化成“限制数字大于多少”的形式。

$ans=\sum_{k=1}^9  \sum_{i=k} ^9c(i)$

然后我们发现现在后面这一部分变成了“数字大于等于$k$的贡献”。于是我们可以对于每一个$k$，利用数位DP单独计算一次贡献。

令$dp[i][j][0/1]$代表枚举到第$i$位，大于等于$k$的数字有$j$个，当前枚举的数字前缀是不是和上界重合时，小于等于X的数有多少个。

转移方程：$dp[i][j][0]=(k-1)*dp[i-1][j][0]+(11-k)*dp[i-1][j-1][0]$

贴近上界的情况类似，特殊处理一下即可。

然后我们知道，所有“大于等于K”的数，都是被排列在新生成数的最后几位。所以通过这种方法求的$\sum_{i=k} ^9c(i)$一定是一串前导0+一串1。这样答案就很好计算了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int mod=1e9+7;
typedef long long ll;
ll dp[730][730][2];//前i位 符合条件的多少位 有没有贴到边界
char s[730];
ll ans=0;
int main() {
    scanf("%s",s+1);int len=strlen(s+1);
    for(int k=1;k<=9;k++){//限制大于等于k
        memset(dp,0,sizeof(dp));
        for(int i=0;i<=s[1]-'0';i++) {
            bool ty2=(i>=k),ty3=(i==(s[1]-'0'));
            dp[1][ty2][ty3]+=1;
        }
        for(int i=1;i<len;i++) {
            for(int j=0;j<len;j++) {//符合条件多少位
                for(int st=0;st<=1;st++) {
                    if(!dp[i][j][st])continue;
                    for(int add=0;add<=(st?(s[i+1]-'0'):9);add++) {
                        dp[i+1][j+(add>=k)][st&&(add==(s[i+1]-'0'))]+=dp[i][j][st];
                        dp[i+1][j+(add>=k)][st&&(add==(s[i+1]-'0'))]%=mod;
                    }
                }
            }
        }
        ll tmp=0;
        for(int j=0;j<=len;j++) {
            ans+=(dp[len][j][0]+dp[len][j][1])%mod*tmp%mod;
            ans%=mod;tmp=(tmp*10)+1;tmp%=mod;
        }

    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：4)

差分算贡献。

枚举整数 $w\in[1,9]$，将排序后的数每一位值 $x$ 改为 $[x\ge w]$（如 $w=3$，$54321\mapsto 11100$），将所有数加起来就是答案。

考虑数位 DP，设当前在高位已经确定了 $lst$ 个 $\ge w$ 的数，接下来 $len$ 个低位随便填，则贡献为：

$$
\sum_{i=0}^{len}\binom{len}{i}(10-w)^iw^{len-i}\frac{10^{i+lst}-1}{9}
$$

通过一些套路的恒等变形，化简为：

$$
\frac{10^{lst}}{9}(100-9w)^{len}-\frac{10^{len}}{9}
$$

可以预处理后 $O(1)$ 计算。

复杂度为 $O(|\Sigma|^2n)$，$|\Sigma|$ 为进制 $=10$，$n$ 为位数 $\le 700$。

---

## 作者：platelett (赞：4)

> [题目链接](https://codeforces.com/problemset/problem/908/G)
[可能更好的体验](http://coding-pages-bucket-3532178-8430896-13917-522304-1305159063.cos-website.ap-hongkong.myqcloud.com/CF908G/)
>
> 定义 $S(x)$ 表示把 $x$ 各数位上的数排序后得到的新数，$S(353594)=334559$。
>
> 给定 $n$，求 $\sum\limits_{i=1}^nS(i) \bmod 10^9+7$。
>
> $n \le 10^{700}$

设 $n$ 总共 $m$ 位，$h_{x,i}$ 表示 $x$ 有多少个数位上的数大于等于 $i$。  

然后发现 $S(x) = \sum\limits_{i=1}^9 \underbrace{111\cdots 1}=\frac 19\sum\limits_{i=1}^910^{h_{x,i}}-1=\frac 19\sum\limits_{i=1}^9\sum\limits_{j=0}^{m}(10^j-1)\sum\limits_{k=1}^n[h_{k,i}=j]$  
...................................$h_{x,i}$ 个 $1$

因此对每个 $i,j$ 求出 $\sum\limits_{k=1}^n[h_{k,i}=j]$ 即可求得答案。

数位 ```DP``` 即可，复杂度 $O(100m^2)$。

也可以组合计数：

先让 ```n++```，问题变成求 $\sum_{x < n}S(x)$。

定义第 $i$ 位是从最高位开始的第 $i$ 位，$a_i$ 表示 $n$ 的第 $i$ 位。

先枚举数 $x$ 和 $n$ 的 ```LCP``` $i \in [0,m)$，再枚举 $x$ 在第 $i+1$ 位上的值 $j \in [0,a_{i+1})$，则所有 $x$ 的贡献为：

这里 $k$ 表示低 $m-i-1$ 位中有多少位大于等于 $d$。
$$
\frac 19\sum_{d=1}^9\sum_{k=0}^{m-i-1}\binom {m-i-1}k(10-d)^kd^{m-i-1-k}(10^{\sum_{s=1}^i[a_s \ge d]+[j \ge d]+k}-1)
$$
故答案为：
$$
\begin{aligned}
&\frac 19\sum_{i=0}^{m-1}\sum_{j=0}^{a_{i+1}-1}\sum_{d=1}^9\sum_{k=0}^{m-i-1}\binom {m-i-1}k(10-d)^kd^{m-i-1-k}(10^{\sum_{s=1}^i[a_s \ge d]+[j \ge d]+k}-1)\\
&=\frac 19\sum_{i=0}^{m-1}\sum_{j=0}^{a_{i+1}-1}\sum_{d=1}^9\left(\left(10^{\sum_{s=1}^i[a_s \ge d]+[j \ge d]}\sum_{k=0}^{m-i-1}\binom {m-i-1}k(100-10d)^kd^{m-i-1-k}\right)-10^{m-i-1}\right)\\
&=\frac 19\sum_{i=0}^{m-1}\sum_{j=0}^{a_{i+1}-1}\sum_{d=1}^9\left(10^{\sum_{s=1}^i[a_s \ge d]+[j \ge d]}(100-9d)^{m-i-1}-10^{m-i-1}\right)\\
&=\frac 19\sum_{i=0}^{m-1}\sum_{d=1}^9\left(10^{\sum_{s=1}^i[a_s \ge d]}(10\max\{a_{i+1}-d,0\}+\min\{a_{i+1},d\})(100-9d)^{m-i-1}-a_{i+1}10^{m-i-1}\right)\\
&=\frac 19\sum_{i=1}^m\sum_{j=1}^9\left(10^{\sum_{s=1}^{i-1}[a_s \ge j]}(100-9j)^{m-i}(10\max\{a_i-j,0\}+\min\{a_i,j\})-a_i10^{m-i}\right)
\end{aligned}
$$
$\sum_{s=1}^i[a_s \ge d],(100-9d)^{m-i-1},10^{m-i-1}$ 可以枚举 $i$ 时顺便维护。

复杂度 $O(10m)$。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define per(i, r, l) for(int i = (r); i >= (l); i--)
#define mem(a, b) memset(a, b, sizeof a)
#define For(i, l, r) for(int i = (l), i##e = (r); i < i##e; i++)

using namespace std;
typedef long long ll;
const ll P = 1e9 + 7;
int n, a[705]; char s[705];
ll Pow[705][11];
int main() {
	cin >> s, n = strlen(s);
	rep(i, 1, n) a[i] = s[n - i] - 48;
	int i = 1;
	while(a[i] == 9) a[i++] = 0;
	a[i]++;
	if(i > n) n++;
	reverse(a + 1, a + n + 1);
	rep(i, 1, 10) Pow[0][i] = 1;
	rep(i, 1, n) rep(j, 1, 10) Pow[i][j] = Pow[i - 1][j] * (100 - 9 * j) % P;
	int idx[11] = {};
	ll as = 0;
	rep(i, 1, n) rep(j, 1, 9) {
		(as += Pow[idx[j]][10] * Pow[n - i][j] % P * (10 * max(a[i] - j, 0) + min(a[i], j)) - a[i] * Pow[n - i][10]) %= P;
		idx[j] += a[i] >= j;
	}
	cout << (as * 111111112 % P + P) % P;
	return 0;
}
```

---

## 作者：丛雨 (赞：4)

### [CF908G New Year and Original Order](https://www.luogu.com.cn/problem/CF908G)

开始看到题时一头雾水：什么鬼东西，还带排序的

后来才从$\tt tly$大佬那里学到了正解

首先我们可以先将S函数的值拆分

$S(353535)=333555=111111+111111+111111+111+111$

于是我们可以发现,令$s_i$表示每一位中等于i的个数和的后缀和,

例如$s_5=s_4=3,s_3=s_2=s_1=s_0=6$

则$S(x)=\frac{1}{9}\sum_{i=1}^910^{s_i}-1$

所以我们可以对每一位分开来算贡献

但是我们考虑到X的限制，所以我们先枚举后m位不等于X的后m位，前面的位相等，再枚举第m位上的数字

但是在这里，我们只知道前面位和第m位上的数字，所以我们重新定义$s_i$为已知的位中等于$i$的后缀和

于是数字i对于当前情况的贡献为$\frac{1}{9}\sum_{p=0}^m{m\choose p}i^{m-p}(10-i)^p(10^{s_i+p}-1)$

意义为枚举大于等于i的个数p，$\frac{10^{s_i+p}-1}{9}$则表示那一段1

这样我们就可以得到一个时间复杂度为$O(k^2N^2)(N=\text{len(n)}\leq 700)$的算法

```cpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;char k;bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
# define mod 1000000007
# define inv9 111111112ll
char str[705];
int s,h[10];
ll P[705][12],C[705][705];
int main(){
	scanf("%s",str+1);
	s=strlen(str+1);reverse(str+1,str+s+1);
	for(int i=0;i<12;++i)P[0][i]=1;
	for(int i=1;i<=s;++i)
		for(int j=1;j<12;++j)
			P[i][j]=P[i-1][j]*j%mod;
	for(int i=0;i<=s;++i){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;++j)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	ll ans=0;
	for(int i=s;i;--i){
		str[i]-='0';ll k=0;
		if(i!=s)++h[str[i+1]];
		for(int j=0;j<str[i];++j){
			++h[j];int o=0;
			for(int l=10;--l;){
				o+=h[l];//m=i-1;
				for(int p=0;p<i;++p)
					k=(k+C[i-1][p]*P[i-p-1][l]%mod*P[p][10-l]%mod*(P[o+p][10]-1))%mod;
				ans=(ans+inv9*k)%mod;k=0;
			}
			--h[j];
		}
	}
	sort(str+1,str+s+1);
	ll sum=0;
	for(int i=1;i<=s;++i)sum=(10ll*sum+str[i])%mod;
	cout<<(ans+sum)%mod;
	return 0;
}

```



虽然可以过，但我们可以进行优化。

对贡献进行二项式展开逆变换

则贡献为$\frac{1}{9}(10^{s_i}(100-9i)^m-10^m)$

则得到了一个$O(k^2N)$的算法

```cpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;char k;bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
# define mod 1000000007
# define inv9 111111112ll
char str[705];
int s,h[10];
ll P[705][12],C[705][10];
int main(){
	scanf("%s",str+1);
	s=strlen(str+1);reverse(str+1,str+s+1);
	for(int i=0;i<12;++i)P[0][i]=1;
	for(int i=0;i<10;++i)C[0][i]=1;
	for(int i=1;i<=s;++i)
		for(int j=1;j<12;++j)
			P[i][j]=P[i-1][j]*j%mod;
	for(int i=1;i<=s;++i)
		for(int j=0;j<10;++j)
			C[i][j]=C[i-1][j]*(100-9*j)%mod;
	ll ans=0;
	for(int i=s;i;--i){
		str[i]-='0';ll k=0;
		if(i!=s)++h[str[i+1]];
		for(int j=0;j<str[i];++j){
			++h[j];int o=0;
			for(int l=10;--l;){
				o+=h[l];
				ans=(ans+P[o][10]*C[i-1][l]-P[i-1][10])%mod;
			}
			--h[j];
		}
	}ans=ans*inv9%mod;
	sort(str+1,str+s+1);
	ll sum=0;
	for(int i=1;i<=s;++i)sum=(10ll*sum+str[i])%mod;
	cout<<(ans+sum+mod)%mod;
	return 0;
}

```

其实哪怕到了这里，依然可以进行优化。

我们发现每次枚举第$m$位时$s$的变换都不会影响小于当前枚举的数位，所以可以$O(1)$更新

$\mathfrak{Talk\ is\ cheap,show\ you\ the\ code.}$

```cpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;char k;bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
# define mod 1000000007
# define inv9 111111112ll
char str[705];
int s,h[10];
ll P[11][705],C[10][705];
int main(){
	scanf("%s",str+1);
	s=strlen(str+1);reverse(str+1,str+s+1);
	for(int i=0;i<11;++i)P[i][0]=1;
	for(int i=0;i<10;++i)C[i][0]=1;
	for(int j=1;j<11;++j)
		for(int i=1;i<=s;++i)
			P[j][i]=P[j][i-1]*j%mod;
	for(int j=0;j<10;++j)
		for(int i=1;i<=s;++i)
			C[j][i]=C[j][i-1]*(100-9*j)%mod;
	ll ans=0;
	for(int i=s;i;--i){
		str[i]-='0';ll k=0;int o=0;
		if(i!=s)++h[str[i+1]];
		ll t=0;
		for(int l=10;--l;){
			o+=h[l];
			t=(t+P[10][o]*C[l][i-1]-P[10][i-1])%mod;
		}if(str[i])ans=(ans+t)%mod;
		for(int j=1;j<str[i];++j){
			t=(t+C[j][i-1]*P[10][o]*9ll)%mod;
			o-=h[j];ans=(ans+t)%mod;
		}
	}ans=ans*inv9%mod;
	sort(str+1,str+s+1);
	ll sum=0;
	for(int i=1;i<=s;++i)sum=(10ll*sum+str[i])%mod;
	cout<<(ans+sum+mod)%mod;
	return 0;
}
```

时间复杂度$O(kN)$,目前全洛谷$rk1$



---

## 作者：s_r_f (赞：3)

  [我的数位DP总结blog](https://www.luogu.com.cn/blog/s-r-f/oi-bi-ji-shuo-wei-dp-ge-ji-dui-shuo-wei-dp-di-yi-dian-li-xie)

这题也有两种思路$,$不过交错和那道题两种思路不管优劣都能过$,$但是在这个题目里较劣复杂度的做法就过不去了$.$
  
  一种思路是对于$O(700*10)$个查询直接整体$DP$求答案$,$
  
  记$dp[i][j]$表示目前已经安排到了数字$i,$已经放了$j$个数位的方案数和答案$($ 可以用一个$struct$来存 $)$
  
  $.$每次$DP$的复杂度都是$O(700^2*10)$的$,$总复杂度$O(700^3*10^2)$过不去$,$并且不能在只$dp$一次的情况下处理多组询问$.$
  
  另一种思路是$,$我们考虑贡献$.$
  
  记$sum(n) = \sum\limits_{i=0}^{n-1}10^i$
  
  那么对于一个数字答案显然为 $\sum\limits_{i=0}^{9}$ $sum($ 满足 $k\leq i$ 的数字的个数 $).$
  
  所以对这个 $($ 满足 $k\leq i$ 的数字的个数 $)$ $dp,$就可以降低复杂度$.$
  
  记$dp(n,m,k)$表示目前还有$n$位还没确定$,$目前已经确定下来的前缀中有$m$位数字$\geq$ $k$ $,$直接$dp$即可$.$
  
  处理一组询问的复杂度是$O(10*700),$可以只通过一次$dp$来处理多组询问$.$
  
  这种做法的复杂度是 $O(700^2*10),$ 可以通过本题$.$
  
  两种做法的代码$:($ 第一种$TLE,$第二种$AC$ $)$
  
  $upd:$这篇题解里面的**查询**和**询问**不是同一个意思$.$
  
  一组**询问**里面会包含$O($ 进制 $\times$ 最大位数 $)$ 次**查询**$.$ 结合数位$dp$的本质不难想清楚这是为什么$.$

```cpp
/*
方法一O(700^3*10^2) 
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 705,P = 1e9 + 7;
int fac[10005],nfac[10005],inv[10005],pw[10005],prepw[10005];
inline int getval(int l,int r){ if (l>r) return 0; if (l <= 0) return prepw[r]; return (prepw[r] - prepw[l-1] + P) % P; }
inline int C(int n,int m){ return (n<0||m<0||n<m) ? 0 : (LL)fac[n] * nfac[m] % P * nfac[n-m] % P; }
inline void init(){
	int i;
	fac[0] = nfac[0] = inv[0] = fac[1] = nfac[1] = inv[1] = 1;
	for (i = 2; i < 10005; ++i) fac[i] = (LL)fac[i-1] * i % P,inv[i] = (LL)(P-P/i) * inv[P%i] % P,nfac[i] = (LL)nfac[i-1] * inv[i] % P;
	pw[0] = prepw[0] = 1;
	for (i = 1; i < 10005; ++i) pw[i] = 10ll * pw[i-1] % P,prepw[i] = (prepw[i-1] + pw[i]) % P;
}
int cnt[10],suf[11];
struct data{
	int f0,f1;
	inline void mul(int v){ f0 = (LL)f0*v%P,f1 = (LL)f1*v%P; }
	inline void add(int v){ f1 = (f1 + (LL)f0 * v) % P; }
	inline void init(){ f0 = f1 = 0; }
	inline void upd(data x){ f0 = (f0+x.f0) % P,f1 = (f1+x.f1) % P; }
};
data dp[N],f[N];
int n;
inline void work(int v){
	register int i,j,r; int l; data vv;
	for (i = 0; i <= n; ++i) f[i] = dp[i],dp[i].init();
	if (!v){
		for (i = 0; i <= n; ++i){
			if (!f[i].f0) continue;
			l = suf[v+1] + i,r = suf[v] + n - 1;
			vv = f[i],vv.mul(nfac[n-i]),dp[n].upd(vv);
		}
		return;
	}
	for (i = 0; i <= n; ++i){
		if (!f[i].f0) continue;
		l = suf[v+1] + i,r = suf[v] + i - 1;
		for (j = 0; j <= n-i; ++j,++r)
			vv = f[i],vv.add((LL)getval(l,r) * v % P),vv.mul(nfac[j]),dp[i+j].upd(vv);
	}
}
inline void upd(int &x,int y){ x = (x+y>=P)?(x+y-P):(x+y); }
inline int DP(int nn){
	int i; data ans;
	for (ans.init(),n = nn,suf[9] = cnt[9],i = 8; i >= 0; --i) suf[i] = suf[i+1] + cnt[i]; suf[10] = 0;
	for (i = 0; i <= n; ++i) dp[i].init(); dp[0].f0 = fac[n];
	for (i = 9; i >= 0; --i) work(i);
	return dp[n].f1;
}
inline int calc(string X){
	int i,j,x,ans = 0; bool flag = 0;
	for (i = X.size()-1; i >= 0; --i) if ((x=X[i]-'0')||flag){
		for (j = 0; j < x; ++j) ++cnt[j],ans = (ans+DP(i)) % P,--cnt[j];
		flag = 1,++cnt[x];
	}
	return ans;
}
string addone(string X){
	cerr<<X.size()<<'\n';
	int i,n = X.size(),pos = 0; bool flag = 1;
	for (i = 0; i < n; ++i) if (X[i] != '9'){ flag = 0; break; }
	if (flag){ X.resize(n+1); X[n] = '1'; for (i = n-1; i >= 0; --i) X[i] = '0'; return X; }
	while (X[pos] == '9') X[pos] = '0',++pos; X[pos]++; return X;
}
int main(){ init(); string N; cin >> N; reverse(N.begin(),N.end()); N = addone(N); cout << calc(N) << '\n'; }
*/

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 705,P = 1e9 + 7;
inline void upd(int &x,int y){ x = (x+y>=P)?(x+y-P):(x+y); }
int pw[701];
inline void init(){
	int i;
	for (pw[0] = 0,pw[1] = 1,i = 2; i <= 700; ++i) pw[i] = 10ll * pw[i-1] % P;
	for (i = 1; i <= 700; ++i) upd(pw[i],pw[i-1]); 
}
int dp[10][701][701]; bool vis[10][701][701];
inline int DP(int k,int n,int m){
	if (!n) return pw[m]; if (vis[k][n][m]) return dp[k][n][m]; vis[k][n][m] = 1;
	return dp[k][n][m] = ((LL)DP(k,n-1,m+1)*(10-k)+(LL)DP(k,n-1,m)*k) % P;
}
int cnt[10];
inline int calc(string X){
	int i,j,k,now,x,ans = 0; bool flag = 0;
	for (i = X.size()-1; i >= 0; --i) if ((x=X[i]-'0')||flag){
		for (j = 0; j < x; ++j){
			for (++cnt[j],now = 0,k = 9; k ; --k) now += cnt[k],upd(ans,DP(k,i,now));
			--cnt[j];
		}
		flag = 1,++cnt[x];
	}
	return ans;
}

string addone(string X){
	int i,n = X.size(),pos = 0; bool flag = 1;
	for (i = 0; i < n; ++i) if (X[i] != '9'){ flag = 0; break; }
	if (flag){ X.resize(n+1); X[n] = '1'; for (i = n-1; i >= 0; --i) X[i] = '0'; return X; }
	while (X[pos] == '9') X[pos] = '0',++pos; X[pos]++; return X;
}
int main(){
	init(); string N; cin >> N; reverse(N.begin(),N.end()); N = addone(N);
	cout << calc(N) << '\n';
}
```


---

## 作者：ql12345 (赞：3)

%%%kelin大佬

补充一下kelin大佬题解的几个细节

1. 为什么有“个大于等于k的数字”的情况对答案的贡献要乘上11111...：

```
1 1 1 2 3 3 ..... k   k   k   k+2  k+2 ...
先考虑1，将1以及以后的位对答案的贡献都减去1，再将这些数都减去1，即：
ans +=
1 1 1 1 1 1 ..... 1   1   1   1    1 ...
原数列对答案的贡献变为：
0 0 0 1 2 2 ..... k-1 k-1 k-1 k+1  k+1 ...
因为我们不在原数列中修改，所以接下来对2计算贡献的时候，
现数列对答案的贡献中大于0的位会再减去1，依次类推...

如果对原数列中k+1计算贡献，但k+1不在原数列中呢？
也不难：我们找到的大于等于k+1的数的个数就是k+2 k+2 ...的所有数，
这些数减去1同时记录答案，就变为了：
0 0 0 0 0 0 ..... 0   0   0   1    1 ...
正常了

其实可以按照另一个思路理解：一个数k，会对1~k每一个数“大于等于其的数的个数”作1的贡献，
所以它做出的总贡献为k，即它会被算k次贡献，即k*他的位的权值
```

2. 对于转移时p的取值，根据数位dp的传统做法不难理解：

	如果之前位不严格小于，就让最高位为该位置上的最大值，这样，最后的“不严格小于”实际上表示的是“严格等于”，所以统计答案的时候直接统计上这种情况

---

## 作者：OrangeEye (赞：1)

用柱状图描述一个数624491456：
![](https://cdn.luogu.com.cn/upload/image_hosting/aw15v104.png)
下面是他排序之后的数（即124445669）：
![](https://cdn.luogu.com.cn/upload/image_hosting/est7qhai.png)
由于竖向统计不好做，所以考虑横向统计贡献。在上述数中，$1$ 到 $9$ 每一位贡献为：
| 位 | 贡献 |
| :----------: | :----------: |
| $1$ | $111111111$ |
| $2$ | $11111111$ |
| $3$ | $1111111$ |
| $4$ | $1111111$ |
| $5$ | $1111$ |
| $6$ | $111$ |
| $7$ | $1$ |
| $8$ | $1$ |
| $9$ | $1$ |


容易发现，对于一个数 $k(0<k<10)$，如果有 $p$ 位大于等于 $k$，则贡献为 $11\dots11$（$p$ 个 $1$）。

由此可以设计数位 DP 状态：$dp_{c,i,j,lim}$ 表示第 $i$ 位到第 $n$ 位有 $j$ 个数大于等 $c$，且 $lim$ 表示是否封顶的方案数。最后统计答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define endl '\n'
const int mod=1000000007;
int n;
char s[777];
int dp[10][777][777];
int dfs(int op,int x,int up,int lim){
	if(x>n)return !up;
	if(!lim&&dp[op][x][up]!=-1)return dp[op][x][up];
	int res=0;
	for(int i=0;i<op;i++)if(!lim||i<=s[x]-'0')
		(res+=dfs(op,x+1,up,lim&&(i==s[x]-'0')))%=mod;
	for(int i=op;i<10;i++)if(!lim||i<=s[x]-'0')
		(res+=dfs(op,x+1,up-1,lim&&(i==s[x]-'0')))%=mod;
	if(!lim)return dp[op][x][up]=res;
	else return res;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	memset(dp,-1,sizeof(dp));
	cin>>(s+1);
	n=strlen(s+1);
	int ans=0;
	for(int c=1;c<10;c++){
		for(int i=1,p=1;i<=n;i++,p=(p*10+1)%mod)
			(ans+=p*dfs(c,1,i,1))%=mod;
	}cout<<ans<<endl;
	return 0;
}
```

---

## 作者：LastKismet (赞：0)

# Sol
本题是有生成函数和卷积做法的，但那实在是太复杂了，所以还是写一种简单写法吧。

考虑数位 DP，逐位枚举加入的数，这样的话加入一个数会对九种数（显然可以忽略 $0$ 的贡献）造成繁琐影响，虽然说也不是不能实现吧，但相较而言太繁琐了。

考虑拆贡献，每次只考虑一种数的贡献，这样就只需要看加入的数与当前判断的数的大小关系即可，虽然复杂度并没有优化，但好写多了。

使用 $f$ 存储当前位当前数产生的贡献，发现加入一个新数时，我们需要知道比它大的数有多少才能计算新的贡献，于是再开一个数组 $g$ 储存当前加入一个数后将会产生的贡献值，每次更新贡献就加上 $g$ 即可。倘若插入大于当前数的数需要将前面的贡献乘 $10$，具体细节详见代码部分。

# Code
```cpp
const int N=705;

string s;int n;
mint f[N][2],g[N][2],ans;

void solve(int dg){
    rep(i,0,n)f[i][0]=f[i][1]=g[i][0]=g[i][1]=0;
    g[0][1]=dg;
    rep(i,1,n){
        rep(j,0,s[i]-'0'-1){
            if(j<dg)f[i][0]+=f[i-1][0]+f[i-1][1],g[i][0]+=g[i-1][0]+g[i-1][1];
            else if(j==dg)f[i][0]+=(f[i-1][0]+f[i-1][1])*10+g[i-1][0]+g[i-1][1],g[i][0]+=g[i-1][0]+g[i-1][1];
            else f[i][0]+=(f[i-1][0]+f[i-1][1])*10,g[i][0]+=(g[i-1][0]+g[i-1][1])*10;
        }
        rep(j,s[i]-'0',s[i]-'0'){
            if(j<dg)f[i][1]+=f[i-1][1],g[i][1]+=g[i-1][1];
            else if(j==dg)f[i][1]+=f[i-1][1]*10+g[i-1][1],g[i][1]+=g[i-1][1];
            else f[i][1]+=f[i-1][1]*10,g[i][1]+=g[i-1][1]*10;
        }
        rep(j,s[i]-'0',9){
            if(j<dg)f[i][0]+=f[i-1][0],g[i][0]+=g[i-1][0];
            else if(j==dg)f[i][0]+=f[i-1][0]*10+g[i-1][0],g[i][0]+=g[i-1][0];
            else f[i][0]+=f[i-1][0]*10,g[i][0]+=g[i-1][0]*10;
        }
    }
    ans+=f[n][0]+f[n][1];
}

inline void Main(){
    read(s);n=s.size();s=" "+s;
    rep(i,1,9)solve(i);
    put(ans);
}
```

---

## 作者：Priestess_SLG (赞：0)

补的 NOIP 集训的题。这种题肯定就只能数位 dp。对于一个数字 $S$，将其所有数位从小到大排序之后 $0$ 会全部变为前导零并消失，还剩下 $1\sim 9$ 这 $9$ 个数字。

可以发现这些数字之间对答案的贡献是互相独立的，因此可以对这 $9$ 个数字中每一个数字分别计算她们单独贡献。那么考虑设一个简单的 dp：设 $f_i$ 表示前 $i$ 位对当前枚举数位的值 $x$ 对答案的贡献。那么考虑分三类讨论：

+ 若当前枚举填写的位置的值 $<x$，那么对当前数的所有 $x$ 没有产生贡献。即 $f_i\leftarrow f_{i-1}$。
+ 若当前枚举填写的位置的值 $>x$，那么就会把所有值为 $x$ 的位整体左移一位，答案 $\times 10$。即 $f_i\leftarrow 10f_{i-1}$。
+ 若当前枚举填写的位置的值 $=x$，那么之前所有填写的值为 $x$ 的位整体左移，对答案的贡献 $\times 10$。然后还需要计算当前数的贡献。考虑用另一个 dp 来优化当前 dp 的转移：设 $g_i$ 表示前 $i$ 个位若在最后一位加入当前填写的字符 $x$，那么当前位会额外给答案贡献多少。此时可以继续分类讨论：
  + 若当前枚举填的数字 $\le x$，那么不会给之前所有填写的 $x$ 添加新的贡献，即 $g_i\leftarrow g_{i-1}$。
  + 若当前枚举填的数字 $>x$。那么会让之前所有填写的 $x$ 整体左移一位，即 $g_i\leftarrow 10g_{i-1}$。
+ 因此该部分整体的 dp 转移式为：$f_\leftarrow 10f_{i-1}+g_{i-1}$。

因为这是数位 dp 所以还需要额外设一个 $j$ 维度表示当前的数值是否顶了上界，转移的时候就随便带着转移即可。因此本题做完了，时间复杂度为 $O(|n|\omega^2)$，其中 $|n|$ 为 $n$ 在 $10$ 进制下的位数，$\omega$ 为字符集大小，本题中取 $9$。

代码，这是某人少有的清纯少女 style 代码。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 710;
const int mod = 1e9 + 7;
int f[N][2], g[N][2];
char s[N];
inline void add(int &x, int y) {
    x = (x + y) % mod;
}
signed main() {
    // cin.tie(0)->sync_with_stdio(false);
    scanf("%s", s + 1);
    int n = strlen(s + 1), sum = 0;
    for (int x = 1; x < 10; ++x) {
        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);
        f[0][1] = 0, g[0][1] = x;
        for (int i = 0; i < n; ++i)
            for (int o = 0; o < 2; ++o) {
                int liim = o ? (s[i + 1] & 15) : 9;
                for (int j = 0; j <= liim; ++j) {
                    int lim = o && j == (s[i + 1] & 15);
                    if (j < x) add(f[i + 1][lim], f[i][o]);
                    else if (j > x) add(f[i + 1][lim], f[i][o] * 10 % mod);
                    else add(f[i + 1][lim], (f[i][o] * 10 % mod + g[i][o]) % mod);
                    if (j <= x) add(g[i + 1][lim], g[i][o]);
                    else add(g[i + 1][lim], g[i][o] * 10 % mod);
                }
            }
        add(sum, (f[n][0] + f[n][1]) % mod);
    }
    cout << sum << '\n';
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

写 OI 题目，过赛博新年。

在题单里面随便翻了一道带有 New Year 的题目，算是过个赛博新年了 /tiao 感觉这题完全没有 `*2800` 的难度啊 /yun

如果这个数的数位中，有 $a_9$ 个 $\ge 9$ 的数，$a_8$ 个 $\ge 8$ 的数，以此类推，那么 $f$ 值就是：

$$
\sum_{i=1}^9 \dfrac{10^{a_i}-1}{9}
$$

这个东西，显然可以对每个 $i$ 拆开的——因此我们只需要计算出，**如果钦定了一段开头，剩下的 $10^{\alpha}$ 种情况中，$a_i=t$ 的有多少个**。

使用 DP 预处理出长度为 $len$ 的数，只允许 $\ge t$ 的数位出现的方案数即可。

复杂度为 $O(n^2 |\Sigma|^2)$，足以通过本题。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=700+10,MOD=1e9+7;
int n,ans,cnt[MAXN],C[MAXN][MAXN],dp[15][MAXN],pw[15][MAXN],sum[MAXN];
string S;
int solve(int len) {
	int pre=0,ans=0;
	ffor(i,0,8) {
		pre+=cnt[i];
		ffor(j,0,len) ans=(ans+sum[n-j-pre]*dp[i][j]%MOD*C[len][j]%MOD*pw[9-i][len-j])%MOD;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>S,n=S.size(),S="&"+S;
	ffor(i,0,n) {C[i][0]=1;ffor(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;}
	ffor(i,1,n) sum[i]=(sum[i-1]*10+1)%MOD;
	ffor(i,1,10) {
		pw[i][0]=1;
		ffor(j,1,n) pw[i][j]=pw[i][j-1]*i%MOD;
	}
	ffor(i,0,n) dp[0][i]=1;
	ffor(i,0,9) ffor(j,0,n) ffor(w,0,n-j) dp[i+1][j+w]=(dp[i+1][j+w]+dp[i][j]*C[j+w][j])%MOD;
	ffor(i,1,n) {ffor(j,0,S[i]-'0'-1) cnt[j]++,ans=(ans+solve(n-i))%MOD,cnt[j]--;cnt[S[i]-'0']++;}
	ans=(ans+solve(0))%MOD;
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

好牛的题目。

考虑最后的贡献形式是数位排序后的结果，注意到这种数一定能拆解为不超过 $9$ 个 $0000...111111$ 之和。

所以考虑令 $s_{i,j}$ 表示 $1 \sim n$ 中大于等于 $i$ 的数位有 $j$ 个的方案，有答案就是 $\sum_{i=1}^9 \sum_{j=0}^n  s_{i,j} \times f_j$，其中 $f_j = 10 \times f_{j-1} + 1$。

考虑枚举 $i$ 然后算贡献，考虑去数位 dp，注意可以把 $f_{j}$ 放到 dp 过程里面算，也就是当数位 dp 时假若加入了一个大于等于 $i$ 的数，前面所有方案贡献会乘 $10$ 并加上 $1$，否则直接继承所有方案贡献，因此 dp 过程中记录下方案之和与方案数即可转移。

时间复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;
const int maxn = 800; 
string S;
int dp[maxn][2],g[maxn][2];//0 达到上界 1 没达到上界 
int n;
int ans;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>S;
	n=S.size();
	for(int w=1;w<=9;w++){
		memset(dp,0,sizeof(dp));
		memset(g,0,sizeof(g));
		g[0][0]=1;
		for(int i=1;i<=n;i++){
			for(int d=0;d<=9;d++){
				//0 \to 0
				if(d==S[i-1]-'0'){
					g[i][0]=(g[i][0]+g[i-1][0])%mod;
					dp[i][0]=(dp[i][0]+(d>=w?(dp[i-1][0]*10%mod+g[i-1][0])%mod:dp[i-1][0]))%mod;
				}
				//0 \to 1
				if(d<S[i-1]-'0'){
					g[i][1]=(g[i][1]+g[i-1][0])%mod;
					dp[i][1]=(dp[i][1]+(d>=w?(dp[i-1][0]*10%mod+g[i-1][0])%mod:dp[i-1][0]))%mod;
				}
				//1 \to 1
				g[i][1]=(g[i][1]+g[i-1][1])%mod;
				dp[i][1]=(dp[i][1]+(d>=w?(dp[i-1][1]*10%mod+g[i-1][1])%mod:dp[i-1][1]))%mod;
			}
		}
		ans=(ans+dp[n][0]+dp[n][1])%mod;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：xfrvq (赞：0)

考虑按数位算贡献，一个数种数字 $x$ 产生 $x\times10^y$ 的条件是：$\gt x$ 的位置有 $\lt y$ 个，$\ge x$ 的位置有 $\le y$ 个。但这个两维条件不好弄，数位 dp 起码是立方的。

转思路，将一个数的贡献差分。把一个排好序的数拆成 **不多于 $9$ 个由若干 $1$ 组成的数的和**，例如 $1239=1111+111+11+1\times6$，观察到第 $i$ 个是 $x_i$ 个 $1$ 构成，其中 $x_i$ 是原数中 $\ge i$ 的位数。

于是对于每个数分 $9$ 次计算其贡献，对于一个数字 $i$，我们要算的就是：**设一个数 $\ge i$ 位数为 $f(x,i)$，求 $\displaystyle\sum_{x=1}^nf(x,i)$ 个 $1$ 构成的数。** 这个数位 dp 就是平方的了。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 7e2 + 5;
const ll mod = 1e9 + 7;

char a[N];
int n,k;
ll v[N],f[N][N],sum;

ll dfs(int p,int c,bool lim,ll tot = 0){
	if(p == n + 1) return v[c];
	if(!lim && ~f[p][c]) return f[p][c];
	for(int i = 0;i <= (lim ? a[p] - '0' : 9);++i)
		(tot += dfs(p + 1,c + (i >= k),lim && (i == a[p] - '0'))) %= mod;
	return lim ? tot : (f[p][c] = tot);
}

int main(){
	scanf("%s",a + 1),n = strlen(a + 1);
	for(int i = 1;i <= n;++i) v[i] = (v[i - 1] * 10 + 1) % mod;
	for(k = 1;k <= 9;++k){
		memset(f,-1,sizeof f);
		(sum += dfs(1,0,1)) %= mod;
	}
	printf("%lld\n",sum);
	return 0;
}
```

---

## 作者：Drind (赞：0)

我们发现按照普通的数位 dp 来解决这个问题比较困难，因为有一个排序的操作导致前面的位会影响后面的位。

我们发现一个没什么用的性质是一个已经排序好的数，他的每一位都大于等于他的下一位。然后我们就能得到一个真正有用的性质就是每个排序好的数都能被不超过九个连续的一相加得到。

例如 345342 排序好之后就是 233445，即 $111111
+111111+11111+111+1$.

于是我们把每个连续的一分开来算，设 $f_{i,j,k}$ 代表前 $i$ 位中恰好有 $j$ 个数大于 $k$ 的情况数。我们设$g_j$ 为长度为 $j$ 的连续1的值，这样我们的答案就是 $\sum_{i=1}^{9}\sum_{j=1}^{n}f_{n,j,i}\times g_j$，其中 $n$ 代表题目给定数字的长度。

为什么是这样呢？我们发现 $\sum_{i=1}^{9} f_{n,j,i}\times g_j$ 就是长度为 $j$ 的所有连续 1 串的和，那么 $f_{n,j,i}$ 就是出现了 $i$ 个长度为 $j$ 的所有连续 1 串的情况数， $i=1$ 的时候统计了第一个串，$i=2$ 的时候统计了第二个串，以此类推。

然后记忆化搜索一下就解决啦。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int p=1e9+7;

int a[N],cnt;
int dp[701][702][10];

int dfs(int len,int tot,int low,bool lim){
	if(!len) return tot==1;//注意这里的tot要全部加上1否则会数组越界，访问-1
	if(tot==0) return 0;
	if(!lim&&dp[len][tot+1][low]!=-1) return dp[len][tot+1][low];
	int limit=lim?a[len]:9; int ans=0;
	for(int i=0;i<=limit;i++) ans=(ans+dfs(len-1,tot-(i>=low),low,lim&&(i==a[len])))%p;
	if(!lim) dp[len][tot+1][low]=ans;
	return ans;
}

int work(string x){
	for(int i=x.size()-1;i>=0;i--) a[++cnt]=x[i]-'0';
	int res=0;
	for(int i=1;i<=9;i++){
		int f=1;//f计算全部是1的串的值
		for(int j=1;j<=cnt;j++){
			res=(res+dfs(cnt,j+1,i,1)*f%p)%p;
			f=(f*10+1)%p;
		}
	}
	return res;
}

void fake_main(){
	memset(dp,-1,sizeof dp);
	string n; cin>>n;
	cout<<work(n)<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：crashed (赞：0)

# 题目

[点这里](https://www.luogu.com.cn/problem/CF908G)看题目。

# 分析

~~看见大家都写数位 DP ，可是我就是不会数位 DP 。~~

为了方便描述，不妨设 $m$ 为进制，在这个问题中 $m=10$ 。

类似于数位 DP ，我们可以限制当前的数在前 $i$ 位与 $X$ 相同，且在第 $i+1$ 位比 $X$ 小，那么在更低的位就没有限制了，我们可以方便地统计。

此时的问题就相当于是，我们仍然选 $n$ 个数码，但在确定的前缀中，对于数码 $k$ ，它至少会被选择 $l_k$ 次，并且这 $l_k$ 个的位置已经确定的。

那么不难想到如下 DP ：

设 $g_{i,j}$ 表示考虑了前 $i$ 个**非零**数码后，已有的数字的总长度为 $j$ 的**方案数**。

设 $f_{i,j}$ 表示考虑了前 $i$ 个**非零**数码后，已有的数字的总长度为 $j$ 的**所有 $f(X)$ 的和**。

另设 $V_k$ 表示长度为 $k$ 的全是 1 的数的值，即 $\frac{m^k-1}{m-1}$ 。

假设现在未被确定的有 $L$ 个数码，转移也比较简单：
$$
\begin{aligned}
g_{i,j}&=\sum_{k=0}^{j}\binom{j}{k}g_{i-1,j-k}\\
f_{i,j}&=\sum_{k=0}^{j}\binom{j}{k}\left(m^{k+l_i}f_{i-1,j-k}+g_{i-1,j-k}\times iV_{k+l_i}\right)
\end{aligned}
$$
最后我们不需要考虑 0 的贡献，位置也不重要，所以：
$$
ans=\sum_{k=0}^{L}\binom{L}{k}f_{m-1,k}
$$
现在我们就得到了 $O(m^2n^3)$ 的算法。

考虑优化这个过程。由于 $f,g$ 的转移比较简单，我们考虑推导生成函数。

设如下几个生成函数：
$$
\begin{aligned}
G_j(x)&=\sum_{0\le k}\frac{g_{j,k}x^k}{k!}\\
F_j(x)&=\sum_{0\le k}\frac{f_{j,k}x^k}{k!}\\
V(x)&=\sum_{0\le k}\frac{V_kx^k}{k!}
\end{aligned}
$$
根据 $G$ 的转移有：
$$
G_k(x)=e^x\cdot G_{k-1}(x)\Rightarrow G_{k}(x)=e^{kx}
$$
根据 $F$ 的转移有：
$$
\begin{aligned}
f_{i,j}&=\sum_{k=0}^j\binom{j}{k}(m^{k+l_i}f_{i-1,j-k}+g_{i-1,j-k}\times iV_{k+l_i})\\
\Rightarrow \frac{f_{i,j}x^j}{j!}&=\sum_{k=0}^j\frac{m^kx^k}{k!}\cdot \frac{f_{i-1,j-k}x^{j-k}}{(j-k)!}\cdot m^{l_i}+i\cdot \frac{g_{i-1,j-k}x^{j-k}}{(j-k)!}\cdot\frac{(m^{l_i}V_k+V_{l_i})x^k}{k!}\\
\Rightarrow F_i(x)&=m^{l_i}\cdot e^{mx}F_{i-1}(x)+iG_{i-1}(x)(m^{l_i}V(x)+e^xV_{l_i})\\
\Rightarrow F_i(x)&=m^{l_i}\cdot e^{mx}F_{i-1}(x)+ie^{(i-1)x}(m^{l_{i}}V(x)+e^xV_{l_i})
\end{aligned}
$$
令 $p_i=m^{l_i}e^{mx},q_i=ie^{(i-1)x}(m^{l_i}V(x)+e^xV_{l_i})$ ，则有：
$$
F_i(x)=\sum_{k=1}^iq_k\prod_{j=k+1}^i p_j
$$
考虑答案：
$$
\begin{aligned}
\frac{ans}{L!}
&=[x^L]e^xF_{m-1}(x)\\
&=[x^L]e^x\sum_{k=1}^{m-1}q_k\prod_{j=k+1}^{m-1}p_j\\
&=[x^L]e^x\sum_{k=1}^{m-1}ke^{(k-1)x}(m^{l_k}V(x)+e^xV_{l_k})\prod_{j=k+1}^{m-1}m^{l_j}e^{mx}\\
&=[x^L]\sum_{k=1}^{m-1}\left(\prod_{j=k+1}^{m-1}m^{l_j}\right)e^{m(m-1-k)x}\cdot ke^{kx}(m^{l_k}V(x)+e^xV_{l_k})\\
&=[x^L]\sum_{k=1}^{m-1}k\left(\prod_{j=k+1}^{m-1}m^{l_j}\right)e^{(m(m-1-k)+k)x}(m^{l_k}V(x)+e^xV_{l_k})\\
&=[x^L]\sum_{k=1}^{m-1}k\left(\prod_{j=k+1}^{m-1}m^{l_j}\right)(m^{l_k}e^{(m(m-1-k)+k)x}V(x)+e^{(m(m-1-k)+k+1)x}V_{l_k})\\
\end{aligned}
$$
看到特殊的情况，即带入 $m=10$ ：
$$
ans=L![x^L]\sum_{k=1}^{9}k\left(\prod_{j=k+1}^{9}10^{l_j}\right)(10^{l_k}e^{(90-9k)x}V(x)+e^{(91-9k)x}V_{l_i})
$$
考虑计算这个式子，可以发现唯一的问题就在于 $e^{(90-9k)x}V(x)$ 比较复杂。不过，由于 $k$ 的值很少，我们可以直接枚举 $k$ ，预处理 $e^{(90-9k)x}V(x)$ 的结果。这样我们就可以 $O(m)$ 计算一次 $ans$ 。

> 这里 $V(x)$ 可以得到一个闭形式： $V(x)=\frac{1}{m-1}(e^{mx}-e^x)=\frac{1}{m-1}e^x(e^{(m-1)x}-1)$ ，那么可以得到闭形式为 $\frac{1}{m-1}e^{(m(m-1-k)+k)x}e^x(e^{(m-1)x}-1)$ ，这个东西就可以 $O(1)$ 计算了。 

时间复杂度是 $O(mn^2)$ ，如果你喜欢，也可以变成 $O(mn\log_2n)$ ，甚至 $O(m^2n)$ 。

# 代码

```cpp
#include <cstdio>
#include <cstring>

#define rep( i, a, b ) for( int i = (a) ; i <= (b) ; i ++ )
#define per( i, a, b ) for( int i = (a) ; i >= (b) ; i -- )

const int mod = 1e9 + 7;
const int MAXN = 700 + 5, MAXK = 10;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

int low[MAXK];

int fac[MAXN], ifac[MAXN];

int V[MAXN], pw[MAXN], spw[MAXN];

int X[MAXN];
char str[MAXN];
int N, ans = 0, inv9;

inline int Qkpow( int, int );
inline int Mul( int x, int v ) { return 1ll * x * v % mod; }
inline int Inv( const int a ) { return Qkpow( a, mod - 2 ); }
inline int Sub( int x, int v ) { return ( x -= v ) < 0 ? x + mod : x; }
inline int Add( int x, int v ) { return ( x += v ) >= mod ? x - mod : x; }

int Qkpow( int base, int indx )
{
	int ret = 1;
	while( indx )
	{
		if( indx & 1 ) ret = Mul( ret, base );
		base = Mul( base, base ), indx >>= 1;
	}
	return ret;
}

void Init()
{
	spw[0] = pw[0] = 1, V[0] = 0;
	rep( i, 1, N ) pw[i] = Mul( pw[i - 1], 10 ), V[i] = Add( V[i - 1], pw[i - 1] );
	inv9 = Inv( 9 );	
	fac[0] = 1; rep( i, 1, N ) fac[i] = Mul( fac[i - 1], i );
	ifac[N] = Inv( fac[N] ); per( i, N - 1, 0 ) ifac[i] = Mul( ifac[i + 1], i + 1 );
}

int Calc( const int L )
{
	int ret = 0, prod = 1;
	per( k, 9, 1 )
	{
		int coe = Mul( inv9, Sub( Mul( Qkpow( 100 - 9 * k, L ), ifac[L] ), Mul( Qkpow( 91 - 9 * k, L ), ifac[L] ) ) );
		ret = Add( ret, Mul( Mul( prod, k ), Add( Mul( coe, pw[low[k]] ), Mul( V[low[k]], Mul( Qkpow( 91 - 9 * k, L ), ifac[L] ) ) ) ) );
		prod = Mul( prod, pw[low[k]] );
	}
	return Mul( ret, fac[L] );
}

int main()
{
	scanf( "%s", str + 1 ), N = strlen( str + 1 );
	rep( i, 1, N ) X[N - i + 1] = str[i] - '0';
	Init();
	per( i, N, 1 )
	{
		rep( j, 0, X[i] - 1 )
		{
			low[j] ++; 
			ans = Add( ans, Calc( i - 1 ) ); 
			low[j] --;
		}
		low[X[i]] ++;
	}
	ans = Add( ans, Calc( 0 ) );
	write( ans ), putchar( '\n' );
	return 0;
}
```

---

