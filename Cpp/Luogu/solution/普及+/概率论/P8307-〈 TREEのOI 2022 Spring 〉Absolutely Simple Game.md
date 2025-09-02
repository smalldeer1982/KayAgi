# 〈 TREEのOI 2022 Spring 〉Absolutely Simple Game

## 题目背景

rin 和 len 在玩一个绝对简单的游戏，pcq 为裁判。

## 题目描述

初始时给定范围 $[l,r]=[1,n]$，pcq 从中均匀随机选出一个自然数 $t$，之后 rin 和 len 两人轮流进行操作，rin 先行。

每次操作方猜测一个整数 $x\in[l,r]$，若 $x=t$，则游戏结束，该方负；若 $x<t$，则调整范围 $[l,r]$ 为 $[x+1,r]$；若 $x>t$，则调整范围 $[l,r]$ 为 $[l,x-1]$。

rin 和 len 两人均充分了解规则且无比可爱聪明（都会最大化自己的胜率），过程中谁都知道场上除了 $t$ 以外的一切信息，求 rin 的胜率。

## 说明/提示

**样例解释1：**  

rin 的胜率为 $\dfrac 23$（一开始猜 $2$），$\bmod~998244353$ 后输出为 $665496236$。

***

**本题采用 SubTask 捆绑测试。**

| SubTask 编号 | 分值 | 特殊限制 |
| :-----------: | :-----------: | :-----------: |
| $0$ | $10$ | $n\equiv 0\ \pmod 2$ |
| $1$ | $20$ | $n\le 100$ |
| $2$ | $30$ | $n\le 10^9$ |
|$3$|$40$|$n\le 10^{18}$|

对于 $100\%$ 的数据，$1 \le n\le 10^{18}$。

---
**如何对有理数取模？**  

$\dfrac {x}{y} \bmod m$ 定义为 $xy^{m-2}\bmod~m$。

$m$ 必须为质数。  

保证答案约分后分母不为 $998244353$ 的倍数。

## 样例 #1

### 输入

```
3```

### 输出

```
665496236```

# 题解

## 作者：Remake_ (赞：4)

很多人想要一个证明，那我就直接借用[这篇题解](https://ternarytree.blog.luogu.org/absolutely-simple-game-ti-xie)通过打表获得的式子了。

考虑**归纳法**

$$ a_n=\left\{
\begin{aligned}

\frac{n-1}{2}(n\operatorname{mod} 4=1) \\

\frac{n}{2}(n\operatorname{mod}2=0) \\

\frac{n+1}{2}(n\operatorname{mod}4=3)

\end{aligned}

\right.

$$

不妨假设此条件对于 $a_1\sim a_{n-1}$ 均成立。

很显然我们可以将其改写成 $a_n=\frac{n-[n\operatorname{mod}4=1]+[n\operatorname{mod}4=3]}{2}$。

$a_n$ 的计算式是 $n-1-\min\limits_{i=1}^na_{i-1}+a_{n-i}$。

我们将我们所改写的代回到 $a_n$ 的计算式得到 $a_n=n-1-\min\limits_{i=1}^n\frac{n-1+[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]}{2}$。

里面的 $\frac{n-1}{2}$ 可以提出来，变成了 $a_n=\frac{n-1}{2}-\min\limits_{i=1}^n\frac{[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]}{2}$。

那么现在我们所需要求的就变成了对于给定 $n$，求 $\min\limits_{i=1}^n[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]$。

分类讨论即可。

$n\operatorname{mod}4=0$:

1.$(i-1)\operatorname{mod}4=0$，则 $(n-i)\operatorname{mod}4=3$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=1$。

2.$(i-1)\operatorname{mod}4=1$，则 $(n-i)\operatorname{mod}4=2$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=-1$。

3.$(i-1)\operatorname{mod}4=2$，则 $(n-i)\operatorname{mod}4=1$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=-1$。

4.$(i-1)\operatorname{mod}4=3$，则 $(n-i)\operatorname{mod}4=0$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=1$。

不难发现此时 $\min\limits_{i=1}^n[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=-1$。

回代之后可得，若 $n\operatorname{mod}4=0$，则 $a_n=\frac{n}{2}$。

$n\operatorname{mod}4=1$:

1.$(i-1)\operatorname{mod}4=0$，则 $(n-i)\operatorname{mod}4=0$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=0$。

2.$(i-1)\operatorname{mod}4=1$，则 $(n-i)\operatorname{mod}4=3$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=0$。

3.$(i-1)\operatorname{mod}4=2$，则 $(n-i)\operatorname{mod}4=2$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=0$。

4.$(i-1)\operatorname{mod}4=3$，则 $(n-i)\operatorname{mod}4=1$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=0$。

不难发现此时 $\min\limits_{i=1}^n[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=0$。

回代之后可得，若 $n\operatorname{mod}4=1$，则 $a_n=\frac{n-1}{2}$。

$n\operatorname{mod}4=2$:

1.$(i-1)\operatorname{mod}4=0$，则 $(n-i)\operatorname{mod}4=1$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=-1$。

2.$(i-1)\operatorname{mod}4=1$，则 $(n-i)\operatorname{mod}4=0$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=-1$。

3.$(i-1)\operatorname{mod}4=2$，则 $(n-i)\operatorname{mod}4=3$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=1$。

4.$(i-1)\operatorname{mod}4=3$，则 $(n-i)\operatorname{mod}4=2$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=1$。

不难发现此时 $\min\limits_{i=1}^n[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=-1$。

回代之后可得，若 $n\operatorname{mod}4=2$，则 $a_n=\frac{n}{2}$。

$n\operatorname{mod}4=3$:

1.$(i-1)\operatorname{mod}4=0$，则 $(n-i)\operatorname{mod}4=2$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=0$。

2.$(i-1)\operatorname{mod}4=1$，则 $(n-i)\operatorname{mod}4=1$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=-2$。

3.$(i-1)\operatorname{mod}4=2$，则 $(n-i)\operatorname{mod}4=0$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=0$。

4.$(i-1)\operatorname{mod}4=3$，则 $(n-i)\operatorname{mod}4=3$，此时 $[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=2$。

不难发现此时 $\min\limits_{i=1}^n[(i-1)\operatorname{mod}4=3]-[(i-1)\operatorname{mod}4=1]-[(n-i)\operatorname{mod}4=1]+[(n-i)\operatorname{mod}4=3]=-2$

回代之后可得，若 $n\operatorname{mod}4=3$，则 $a_n=\frac{n+1}{2}$。

完了。

当然这个东西有一个前提，就是 $(i-1)\operatorname{mod}4=0,1,2,3$ 均能取到。

所以说这个东西对 $n<4$ 是不适用的。

但是我们发现 $n<4$ 的情况显然符合给出的式子，所以是没有影响的。

---

## 作者：retep (赞：2)

## 题目简述

rin 和 len 两个人，轮流从初始为 $[1,n]$ 的区间中选整数，ren 先选。其中某个整数 $t$ 是炸弹，谁先选中谁输。如果没选中，区间会被选出的数分为两半，只保留包含 $t$ 的那一半。两人都要将自己的胜率最大化，求 rin 的胜率。

## 题目分析
题解里已经有详细的归纳法证明了，本蒟蒻就不写了 ~~我不会~~。
说说比赛时的思考历程吧，每步都很简单，保证你能读懂。

刚读完题，看一眼数据范围，哇 $10^{18}$，大概率是数学题。
先来手算数据，$p(x)$ 表示 $n$ 为 $x$ 时 rin 的胜率：

| $x$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $p(x)$ | $0$ | $\frac{1}2$ | $\frac{2}3$ | $\frac{1}2$ | $\frac{2}5$ | $\frac{1}2$ |

通过观察，我们大胆猜测 $x$ 为偶数时，$p(x)$ 都是 $\frac{1}2$，并且 **subtask 里有个分值为 $10$ 分的 $n$ 为偶数的数据点**。赌一波，直接输出 $\frac{1}2$ 交上去，真的得了 $10$ 分！说明我们猜对了。

除了骗分，$\frac{1}2$ 还能告诉我们更重要的事，**那就是 $p(x)$ 一定是个有规律的函数**，只要找到了规律，正解就出来了。

手算的过程中我们发现每次**最大的胜率都是选择区间中第二个数**。也就是说无论是 rin 还是 len，上去都会直接选第二个数。

选第二个数胜率的计算为：

$p(x)=\frac{x-1}{x}\times(\frac{1}{x-1}+\frac{x-2}{x-1}\times(1-p(x-2)))$

$\frac{x-1}{x}$ 的意思是，去掉第二个数就是 $t$然后直接输掉的概率，也就是 $1-\frac{1}{x}$ 。

括号内的 $\frac{1}{x-1}$ 的意思是 $t$ 在第二个数左边，也就是第一个数，直接赢了。

$\frac{x-2}{x-1}\times(1-p(x-2))$ 的意思是 $t$ 在第二个数右边的概率，乘以这个区间中rin赢的概率，因为下次轮到len了，所以要用len赢的概率的补集来算，也就是 $1-p(x-2)$。

用这个公式我们就能快速递推 $p(x)$ 的值了，因为 $x$ 为偶数时 $p(x)$ 一直都是 $\frac{1}{2}$，所以我们只看 $x$ 为奇数时的值，试图找到规律：

| $x$ | $3$ | $5$ | $7$ | $9$ | $11$ | $13$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $p(x)$ |$\frac{2}3$ | $\frac{2}5$ | $\frac{4}7$ | $\frac{4}9$ | $\frac{6}{11}$ | $\frac{6}{13}$ |


规律显而易见，$p(x)$ 分母为 $x$，分子每次加 $2$。
用公式表示出来就是从 $1$ 开始 $\frac{n-1}{2n}$, $\frac{1}2$, $\frac{n+1}{2n}$,  $\frac{1}2$ 这样一直循环。

题目中告诉了我们如何对有理数取模，其实就是求逆元，具体可以看[这里](https://www.luogu.com.cn/problem/solution/P3811)。

计算逆元的过程中用到了快速幂，恐怖的是**直接乘会爆long long，所以还得写个快速乘法**，用加法替代乘法，原理和快速幂是一样的。

## code:
```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define ll unsigned long long
using namespace std;

ll n;

ll mult(ll a,ll b){ //快速乘法
    if(!b)return 0;
    if(b==1)return a;
    if(b&1)return (mult(a,b-1)+a)%mod;
    return 2*mult(a,b/2)%mod;
}

ll power(ll a,ll b){ //快速幂
    if(b==1)return a;
    if(!b)return 1;
    if(b&1)return mult(power(a,b-1),a)%mod;
    ll buf=power(a,b/2);
    return mult(buf,buf)%mod;
}

int main(){
    cin>>n;
    ll m=power(n,mod-2); //n的逆元
    if(n%2==0)cout<<499122177<<endl;  //这玩意儿就是0.5取模
    else if(n%4==1)cout<<mult((n-1),499122177)%mod*m%mod<<endl;
    else if(n%4==3)cout<<mult(n+1,499122177)%mod*m%mod<<endl;
    return 0;
}
```



---

## 作者：TernaryTree (赞：1)

## 题目大意

给定范围 $[l,r]=[1,n]$，pcq 从中均匀随机选出一个自然数 $t$，之后 rin 和 len 两人轮流进行操作，rin 先行。

每次操作方猜测一个整数 $x\in[l,r]$，若 $x=t$，则游戏结束，该方负；若 $x<t$，则调整范围 $[l,r]$ 为 $[x+1,r]$；若 $x>t$，则调整范围 $[l,r]$ 为 $[l,x-1]$。

rin 和 len 两人均充分了解规则且无比可爱聪明，过程中谁都知道场上除了 $t$ 以外的一切信息，求 rin 的胜率。

## 思路分析

我们对前几个 $n$ 进行打表，将 $s_n$ 表示 $n$ 的 rin 胜率，$a_n$ 表示 $n$ 的 rin 胜率 $\times n$。

$n=1$：

| $t=$ | $1$ |
| :----------: | :----------: |
| rin 第一次选 $1$ 的胜率 | $0$ |
| rin 的总胜率 $\times n$ | $0$ |

有 $a_1=0, s_1=\dfrac01=0$。

***

$n=2$：

| $t=$ | $1$ | $2$ |
| :----------: | :----------: | :----------: |
| rin 第一次选 $1$ 的胜率 | $0$ | $1-s_1=1$ （因为 rin 选择 $2$ 后范围由 $[1,2]$ 变为 $[1,1]$，len 面临的是 $s_1$ 情况，胜率为 $0$，故 rin 胜率为 $1-0$。） |
| rin 第一次选 $2$ 的胜率 | $1-s_1=1$ | $0$ |
| rin 的总胜率 $\times n$ | $1$ | $1$ |

所以 $a_2=1, s_2=\dfrac12$。

***

$n=3$：

| $t=$ | $1$ | $2$ | $3$ |
| :----------: | :----------: | :----------: | :----------: |
| rin 第一次选 $1$ 的胜率 | $0$ | $1-s_1=1$ | $1-s_2=\dfrac12$ |
| rin 第一次选 $2$ 的胜率 | $1-s_2=\dfrac12$ | $0$ | $1-s_2=\dfrac12$ |
| rin 第一次选 $3$ 的胜率 | $1-s_2=\dfrac12$ | $1-s_1=1$ | $0$ |
| rin 的总胜率 $\times n$ | $1$ | $2$ | $1$ |

所以 $a_3=2, s_3=\dfrac23$。

***

$n=4$：

| $t=$ | $1$ | $2$ | $3$ |  |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| rin 第一次选 $1$ 的胜率 | $0$ | $1-s_1=1$ | $1-s_2=\dfrac12$ | $1-s_3=\dfrac13$ |
| rin 第一次选 $2$ 的胜率 | $1-s_3=\dfrac13$ | $0$ | $1-s_2=\dfrac12$ | $1-s_3=\dfrac13$ |
| rin 第一次选 $3$ 的胜率 | $1-s_3=\dfrac13$ | $1-s_2=\dfrac12$ | $0$ | $1-s_3=\dfrac13$ |
| rin 第一次选 $4$ 的胜率 | $1-s_3=\dfrac13$ | $1-s_2=\dfrac12$ | $1-s_1=1$ | $0$ |
| rin 的总胜率 $\times n$ | $1$ | $2$ | $2$ | $1$ |

所以 $a_4=2, s_4=\dfrac24=\dfrac12$。

***

由上可见，对于第 $n$ 个表格的第 $t=i$ 列，rin 的总胜率为

$$
\begin{aligned}
a_n'&=(1-s_{i-1})(i-1)+(1-s_{n-i})(n-i) \\ 
&=(1-\dfrac{a_{i-1}}{i-1})(i-1)+(1-\dfrac{a_{n-i}}{n-i})(n-i) \\
&=i-1-a_{i-1}+n-i-a_{n-i} \\
&=n-1-(a_{i-1}+a_{n-i}) \\
\end{aligned}
$$

因为

$$a_n=\max a_n'$$

所以我们只要求

$$n-i-(\min_{i=1}^{n}a_{i-1}+a_{n-i})$$

对前几个表格进行分析，不难发现 $i=2$ 时可以使其取到最小值。

打出相应的表格：

| $n=$ | $1$ | $2$ | $3$  | $4$  |$5$   |  $6$ |  $7$ | $8$  |$9$   | $10$ | $\dots$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $a_n=$ | $0$ | $1$ | $2$ | $2$ | $2$ | $3$ | $4$ | $4$ | $4$ |$5$ | $\dots$|

可以发现，

$$
a_n=
\begin{cases}
  \begin{aligned}
    &\dfrac{n-1}{2}\  &(n\bmod 4=1) \\ 
    &\dfrac{n+1}{2}\  &(n\bmod 4=3) \\
    &\ \ \ \dfrac n2\  &(n\bmod 2=0) \\
  \end{aligned}
\end{cases}
$$

且有 $s_n=\dfrac{a_n}{n}$。故可以进行有理数取余运算。

完结撒花。

---

## 作者：ylch (赞：0)

其实前面一些大佬的题解写得已经很清楚了，但看起来都有些唬人，免不了一顿数学推导。如果只是想看看题解启发一下思路，接着自己思考，可以考虑本篇题解。


---


古人云：“数学题，先打表。”先手算一下 $n$ 较小时的规律：

|$n$|1|2|3|4|5|6|7|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$p$（赢的概率）|$1$|$\dfrac{1}{2}$|$\dfrac{2}{3}$|$\dfrac{1}{2}$|$\dfrac{2}{5}$|$\dfrac{1}{2}$|$\dfrac{4}{7}$|

发现如果 $n$ 是偶数，胜率一定是 $\dfrac{1}{2}$；

如果 $n$ 是奇数，分母是 $n$ ，分子是每隔两个加一次 $2$，相邻两个奇数可以表示为 $\dfrac{n-1}{2n},\dfrac{n+1}{2n}$。

所以，得到以四个为一组的规律：$\dfrac{n-1}{2n},\dfrac{1}{2},\dfrac{n+1}{2n},\dfrac{1}{2}$。

根据取模 $4$ 的余数分类讨论即可。


---


计算胜率的方法：

设 $s[n]$ 表示长度为 $n$ 时先手的胜率。

然后，对于每个 $n$ ，分情况讨论 $t$ 的取值（有 $n$ 个），对于每个 $t$ 都分类讨论先手第一次选每个数的胜率。

把所有胜率相加，除以总方案数 $n^2$，得到总胜率

计算胜率可以用一个类似记忆化搜索的方法：
假设 $n=3,t=2$，分类讨论：
1. 先手第一次选 $1$：胜率为 $1-s[2]=\dfrac{1}{2}$（先手选之后，后手选择区间为 $[2,3]$，是 $s[2]$的表示范围。用 $1$ 减去后手在当前局面下的胜率，就是先手胜率）；

2. 先手第一次选 $2$：直接失败，胜率为 $0$；

3. 先手第一次选 $3$：胜率为 $1-s[2]=\dfrac{1}{2}$。（原理同情况 $1$）

综上，这个部分能贡献的胜率为 $ \dfrac{\dfrac{1}{2}+0+\dfrac{1}{2}}{3}=\dfrac{1}{3}$。


---


最后，还有一个坑点：$10^{18}$ 很大，可能 long long 都过不了，要用 int128 存储数据进行运算。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
typedef __int128_t ll; // 注意开 int128

ll Pow(ll a, ll b){
	if(b == 1) return a;
	if(b == 0) return 1;
	ll temp = Pow(a, b / 2);
	if(b & 1){
		return temp * temp % mod * a % mod;
	}
	return temp * temp % mod;
}

namespace fastio{
	struct reader{
		template<typename T>reader&operator>>(T&x){
			char c=getchar();short f=1;
			while(c<'0'||c>'9'){if(c=='-')f*=-1;c=getchar();}
			x=0;while(c>='0'&&c<='9'){
				x=(x<<1)+(x<<3)+(c^48);
				c=getchar();
			}x*=f;return *this;
		}
	}cin;
	struct writer{
		template<typename T>writer&operator<<(T x){
			if(x==0)return putchar('0'),*this;
			if(x<0)putchar('-'),x=-x;
			static int sta[45];int top=0;
			while(x)sta[++top]=x%10,x/=10;
			while(top)putchar(sta[top]+'0'),--top;
			return*this;
		}
	}cout;
};
#define cin fastio::cin
#define cout fastio::cout

signed main()
{
	ll n; cin >> n;
	if(n % 2 == 0){
		cout << 1 * Pow(2, mod - 2) % mod;
	}
	else if(n % 4 == 1){
		cout << (n - 1) * Pow(2 * n, mod - 2) % mod;
	}
	else if(n % 4 == 3){
		cout << (n + 1) * Pow(2 * n, mod - 2) % mod;
	}
	return 0;
}
```

---

