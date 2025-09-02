# [ARC174C] Catastrophic Roulette

## 题目描述

有一个能等概率转出整数 $1,2,\dots,N$ 的轮盘。  
两个人用它进行如下游戏：

- 先手和后手轮流转动轮盘。
  - 如果转出的整数之前没有出现过，则什么都不会发生。
  - 否则，转动轮盘的玩家需要支付 $1$ 日元的罚金。
- 当 $N$ 个整数都至少出现过一次时，游戏立即结束。

请分别求出先手和后手在游戏结束前需要支付的罚金的期望值，并对 $998244353$ 取模后输出。

  期望值 $\bmod\ 998244353$ 的定义：本题中要求的期望值一定是有理数。并且，在本题的约束下，设期望值为既约分数 $\frac{y}{x}$，保证 $x$ 不会被 $998244353$ 整除。

此时，存在唯一的整数 $z$，满足 $0 \leq z \leq 998244352$ 且 $xz \equiv y \pmod{998244353}$。请输出这个 $z$。

## 说明/提示

## 限制

- $N$ 是满足 $1 \leq N \leq 10^6$ 的整数。

## 样例解释 1

本样例中 $N=1$。先手转动轮盘必定转出 $1$，游戏立即结束。因此，先手和后手支付的罚金期望值均为 $0$。

## 样例解释 2

本样例中 $N=2$。游戏的一种可能流程如下：
- 先手转动轮盘，转出 $2$，什么都不会发生。
- 后手转动轮盘，转出 $2$，后手支付 $1$ 日元罚金。
- 先手转动轮盘，转出 $2$，先手支付 $1$ 日元罚金。
- 后手转动轮盘，转出 $1$，什么都不会发生。
- 此时 $1,2$ 都至少出现过一次，游戏立即结束。
- 在这种情况下，先手支付 $1$ 日元罚金，后手支付 $1$ 日元罚金。
可以证明，先手支付的罚金期望值为 $\frac{1}{3}$ 日元，后手支付的罚金期望值为 $\frac{2}{3}$ 日元。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1```

### 输出

```
0 0```

## 样例 #2

### 输入

```
2```

### 输出

```
332748118 665496236```

## 样例 #3

### 输入

```
3```

### 输出

```
174692763 324429416```

# 题解

## 作者：STUDENT00 (赞：9)

传送门：[Luogu](https://www.luogu.com.cn/problem/AT_arc174_c) / [AtCoder](https://atcoder.jp/contests/arc174/tasks/arc174_c)。

首次参赛 ARC，1100 分，749 名（菜就多练，越练越菜）。C 题是 ABCD 四题里我唯一不会的，ABD 共计 1h 全 AC，C 题 10min 无思路，就被赶进房间、被逼迫睡觉了，wuwu……

emem，咱们切入正题。

求期望值？DP，启动！显然，数据范围 $1\le n\le 10^6$ 只允许我们使用 $O(n)$ DP。你根本不知道这个游戏要玩几轮（如果双方“默契”地一直抽 $1$，轮数就 $=\infty$），所以不能把轮数作为状态维度。

显然，抽到过的卡牌数量相同，则期望值相同，否则不同，具体抽到哪些卡牌无需理会。尝试用“**抽到过的卡牌数量**”作 DP 维度。

用 $f1_i$ 表示“**抽到过的卡牌数量变成 $i$ 的那刻，先手的罚款期望值**”。

用 $f2_i$ 表示“**抽到过的卡牌数量变成 $i$ 的那刻，后手的罚款期望值**”。

边界：$f1_1=f2_1=0$。

转移方程：$f1_{i+1}=f1_i+A$。

$A$ 表示“抽到过的卡牌数量变成 $i$ 的那刻”到“抽到过的卡牌数量变成 $i+1$ 的那刻”这段时间里，先手的罚款期望值。

那怎么求 $A$ 呢？

显然，$A$ 是一条级数式，而常数项相同的级数式较易求和。设 $h1=$ 抽到过的卡牌数量变成 $i$ 后轮到先手的概率，$h2=$ 抽到过的卡牌数量变成 $i$ 后轮到后手的概率，则有：

$A=(h1\times \frac{i}{n}+h1\times\frac{i}{n}\times\frac{i}{n}\times\frac{i}{n}+...)+(h2\times\frac{i}{n}\times\frac{i}{n}+h2\times\frac{i}{n}\times\frac{i}{n}\times \frac{i}{n}\times\frac{i}{n})$

$\>\>\>\>=h1\times\frac{i}{n}\times(1+(\frac{i}{n})^2+(\frac{i}{n})^4+...)+h2\times(\frac{i}{n})^2\times(1+(\frac{i}{n})^2+(\frac{i}{n})^4+...)$

设 $p=\frac{i}{n}$，则 $1+(\frac{i}{n})^2+(\frac{i}{n})^4+...=\frac{1}{1-p^2}$。

$A=h1\times\frac{p}{1-p^2}+h2\times\frac{p^2}{1-p^2}$。

代入原式，$f1_{i+1}=f1_i+h1\times\frac{p}{1-p^2}+h2\times\frac{p^2}{1-p^2}$。

同理，$f2_{i+1}=f2_i+h2\times\frac{p}{1-p^2}+h1\times\frac{p^2}{1-p^2}$。

问题：怎么求 $h1$，$h2$ 呢？

简单，DP，启动！

用 $h1_i$ 表示“**抽到过的卡牌数量变成 $i$ 后轮到先手的概率**”。

用 $h2_i$ 表示“**抽到过的卡牌数量变成 $i$ 后轮到后手的概率**”。

边界：$h1_1=0,h2_1=1$。

转移方程推导：

$h1_{i+1}=(h1_i\times p\times (1-p)+h1_i\times p\times p\times p\times (1-p)+...)+(h2_i\times (1-p)+h2_i\times p\times p\times (1-p)+...)$

$\>\>\>\>\>\>\>\>\>\>\>=h1\times p\times (1-p)\times \frac{1}{1-p^2}+h2\times (1-p)\times \frac{1}{1-p^2}$

$\>\>\>\>\>\>\>\>\>\>\>=\frac{1}{1+p}\times (h1\times p+h2)$。

同理，$h2_{i+1}=\frac{1}{1+p}\times (h2\times p+h1)$。

最终答案为 $(f1_n,f2_n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
const int mod=998244353;
typedef long long ll;
int n;
int h1[N],h2[N],f1[N],f2[N];
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=(ll)res*a%mod;
		a=(ll)a*a%mod;
		b>>=1;
	}
	return res;
}
int inv(int x){
	return qpow(x,mod-2);
}
int main(){
	scanf("%d",&n);
	h2[1]=1;
	for(int i=1;i<n;i++){
		int p=(ll)i*inv(n)%mod;
		h1[i+1]=(h2[i]+(ll)h1[i]*p)%mod*inv(1+p)%mod;
		h2[i+1]=(h1[i]+(ll)h2[i]*p)%mod*inv(1+p)%mod;
		f1[i+1]=(f1[i]+(h1[i]+(ll)h2[i]*p)%mod*p%mod*inv((1-(ll)p*p%mod+mod)%mod)%mod)%mod;
		f2[i+1]=(f2[i]+(h2[i]+(ll)h1[i]*p)%mod*p%mod*inv((1-(ll)p*p%mod+mod)%mod)%mod)%mod;
	}
	printf("%d %d",f1[n],f2[n]);
	return 0;
}
```

---

## 作者：liangbowen (赞：7)

[blog](https://www.cnblogs.com/liangbowen/p/18082512)。官解似乎很难想到，这里是容易想到的方法。

---

显然是 DP。介于轮数可能趋近于无穷，所以类似 P4550 做即可。

设 $f_i,g_i$ 表示已经抽了 $i$ 个数，当前是 Alice 或 Bob 抽的，期望罚款。

倒推处理，$f_n=g_n=0$。下文中 $p=\dfrac in$ 表示抽到已经有的概率。

$$\large\begin{cases}f_i=(1-p)\cdot g_{i+1} + p\cdot g_i\\g_i=(1-p)\cdot f_{i+1} + p\cdot(f_i+1)\end{cases}$$

含义：Alice 要么是 Bob 抽完后轮到他，直接抽中新的；要么是没抽中，轮给 Bob。

将 $f_i$ 代入 $g_i$，得：

$$\large\begin{aligned}f_i & =(1-p)\cdot g_{i+1} + p\cdot\Big(f_{i+1} \cdot (1 - p) + (f_i + 1) \cdot p)\Big)\\& = (1-p)\cdot g_{i+1}+p(1-p)\cdot f_{i+1}+p^2+p^2\cdot f_i\end{aligned}$$

移项即有：

$$\large f_i=\dfrac{(1-p)\cdot g_{i+1}+p(1-p)\cdot f_{i+1}+p^2}{1-p^2}$$

$g_i$ 代入即可，答案即 $f_1$ 与 $g_1$。

[code](https://atcoder.jp/contests/arc174/submissions/51435593)，除去快速幂即 $O(n)$。实现时小心爆 long long。

---

## 作者：Starrykiller (赞：6)

记 $g_i$ 为长度为 $i$ 的序列变成长度为 $n$ 的序列的期望代价。我们有

$$g_i=\frac{(n-i)g_{i+1}+i\cdot (g_i+1)}{n}$$

解释：当前长度为 $i$ 的序列随一个数有 $n$ 种可能。有 $(n-i)$ 种是随到一个不在序列中的数；有 $i$ 种是随到一个在序列中的数，代价为 $1$。

初值是 $g_n=0$，不难直接解出 

$$g_i=\frac{(n-i)g_{i+1}+i}{n-i}$$

记 $f_{i,0/1}$ 为当前序列长度为 $i$，且当前是先/后手操作，变成长度为 $n$ 的序列的**先手的**期望代价。于是有

$$f_{i,0}=\frac{(n-i)f_{i+1,1}+i\cdot (f_{i,1}+1)}{n}$$

$$f_{i,1}=\frac{(n-i)f_{i+1,0}+i\cdot f_{i,0}}{n}$$

转移成环，但是从中可以解出 $f_{i,0}$，直接转移即可。

答案为 $f_{0,0}$ 和 $f_{0,1}$。时间复杂度 $\Theta(n)\sim \Theta(n\log n)$。

提请思考：为什么 $f_{0,1}$ 就是后手的期望代价？为什么 $h_0=f_{0,0}+f_{0,1}$？

（赛时把一处 $i^2$ 写成 $i\times 2$ 调了 1h。生气。）

[My Submission](https://atcoder.jp/contests/arc174/submissions/51397135)。

Update on 3.18：感谢 @Nicrobot 指出一处笔误。

---

## 作者：__ryp__ (赞：4)

和机房 dalao 在机房黑板上推了式子，但是不如队爷 cxm 的简洁，~~替他~~ 写个题解。

这题和百事世界杯那道很像，区别就是这题是有两个人的。
但是状态是一样的。

我们设 $f(x)$ 表示作为先手，当前有 $x$ 个物品已经被摸到的期望代价，同理设 $g(x)$ 代表后手的相应情况。（用 $i$ 做变量的话推式子老觉得跟复分析一样qwq）

对于每一次摸球，我们只有摸到新的和摸到旧的两种可能。

+ 摸到新的，概率是 $\dfrac {n - x} n$，此时有

$$\begin{cases}
f(x) = g(x + 1), \\
g(x) = f(x + 1)
\end{cases}$$

+ 摸到旧的，概率是 $\dfrac x n$，此时

$$\begin{cases}
f(x) = g(x) + 1, \\
g(x) = f(x)
\end{cases}$$

这个先后手的转移有一点抽象。当前的先手，转移之后自然是后手，反之亦然。这里玩家并没有改变，仍然是 A 和 B，只是先后手的顺序改变了。我们用状态，用的就是它的语义。

联立这个方程，得到解：

$$\begin{cases}
f(x) = \bigg(\dfrac {n - x} n \cdot g(x + 1) + \dfrac{x\cdot (n - x)}n \cdot f(x + 1) + \dfrac x n\bigg) \bigg/ \bigg(1 - \dfrac {x^2}{n^2}\bigg) \\
g(x) = \dfrac x n \cdot f(x) + \dfrac{n - x}n \cdot f(x + 1)
\end{cases}$$

倒着递推就行了。

---

## 作者：spire001 (赞：2)

## AT_arc174_c 题解

算麻了，所以写一篇题解。

假定你已经读懂题目了，直接说解法。

### 解法

这种概率题常常是需要让你倒推列出递推式的。

就要求的答案出发。

记 $f_i$ 表示在场上还剩 $i$ 张牌时，某个人先手（注意没说是先手的玩家）距离结束还需要罚多少钱。

记 $g_i$ 表示在场上还剩 $i$ 张牌时，某个人让对面先拿一张牌然后距离结束还需要罚多少钱。

然后模拟拿到牌的情况就可以了。

首先说获取 $f$ 的递推式的方法：

假如拿到了一个拿过的，概率为 $\frac{i}{n}$，那么此时你在罚完钱后，只需要等着对面拿一张牌，就是 $g_i$。

你可以理解为玩轮盘赌的时候你按下扳机结果枪没响，现在你成为等待对面操作的后手了。

假如拿到了一个没拿过的，概率为 $\frac{n-i}{n}$。

那么你不需要罚钱，同时只需等待对面在已经拿过 $i+1$ 张牌的情况下拿牌，也就是 $g_{i+1}$。

具体的的式子：
$$
f_i=\frac{i}{n} \times\left( g_i+1 \right)+\frac{n-i}{n}\times (g_{i+1})
$$
然后说获取 $g$ 的递推式的方法：

你只需要看对方怎么操作，但不用管对方是否罚钱。

比如说对面拿到了已经拿过的。概率为 $\frac{i}{n}$，那么此时你成为了先手，即 $f_{i}$。

如果对面拿到的是新的，概率为 $\frac{n-i}{n}$，此时你作为先手，期望是 $f_{i+1}$。

具体的的式子：
$$
g_i=\frac{i}{n} \times f_i + \frac{n-i}{n}\times f_{i+1}
$$
然后你非常恼火的发现这玩意不能直接递推。

所以你将下面的式子带回上面。

然后你需要较为复杂的化简。。。



感兴趣的同学可以去算一下，带进去算，结果是：
$$
f_i=\frac{n\times i+(n-i)(2i+1)f_{i+1}+(n-i)(n-i-1)f_{i+2}}{n^2-i^2}
$$


根据我们的定义，答案即为 $f_0,g_0$。

时间复杂度 $\mathcal O(n\log_2n)$，空间复杂度线性。

实现倒是简单，只需照着式子套即可，本题解给出的代码中变量与以上分析一致。



### 代码

```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

typedef long long LL;
constexpr int N = 2000010;
constexpr int mod = 998244353;
template <typename Tp1, typename Tp2>
inline void cmax(Tp1& A, const Tp2& B)
{
  if (A < B)
    A = B;
  return;
}
template <typename Tp1, typename Tp2>
inline void cmin(Tp1& A, const Tp2& B)
{
  if (A > B)
    A = B;
  return;
}
template <typename Tp1, typename Tp2, int mod = ::mod>
inline void ad(Tp1& A, const Tp2& B)
{
  A = (A + B) % mod;
  return;
}
template <typename Tp1, typename Tp2, int mod = ::mod>
inline void sb(Tp1& A, const Tp2& B)
{
  A = (A + mod - B) % mod;
  return;
}

LL jc[N];

inline LL quick_pow(LL base, LL ind)
{
  LL res = 1;
  base %= mod;
  for (; ind; ind >>= 1)
  {
    if (ind & 1ll)
    {
      res = res * base % mod;
    }
    base = base * base % mod;
  }
  return res;
}
inline LL _div(LL x, LL y)
{
  return x * quick_pow(y, mod - 2) % mod;
}
inline LL C(const int x, const int y)
{
  return _div(jc[x], jc[y] * jc[x - y] % mod);
}

void pre() // 预处理阶乘
{
  jc[0] = 1;
  for (int i = 1; i != N; i++)
    jc[i] = jc[i - 1] * i % mod;
  return;
}
LL f[N], g[N];
void solve()
{
  int n;
  cin >> n;

  for (int i = n - 1; i >= 0; i--) // 倒序递推
  {
    LL tmp = ((LL)n * i % mod
                 + (LL)(n - i) * (i * 2 + 1) % mod * f[i + 1] % mod
                 + (LL)(n - i) * (n - i - 1) % mod * f[i + 2] % mod)
        % mod;
    f[i] = _div(tmp, (LL)n * n - (LL)i * i);
    g[i] = (_div(i, n) * f[i] % mod
               + _div(n - i, n) * f[i + 1] % mod)
        % mod;
  }

  cout << f[0] << ' ' << g[0] << endl;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T = 1;

  while (T--)
    solve();

  return 0;
}

/*

在 Fira Code 字体下查看代码观感更佳!

f_i 表示先手已经拿 i 张牌时还需罚的钱数
g_i 表示让对方已经拿 i 张牌拿一张后再让自己拿还需罚的钱数

f[i] = (i / n) * (1 + g[i]) + ((n - i) / n) * g[i + 1]
g[i] = ((i / n) * f[i] + ((n - i) / n) * f[i + 1])

==>

f[i] = (i / n) * (1 + ((i / n) * f[i] + ((n - i) / n) * f[i + 1])) + 
       ((n - i) / n) * ((i + 1) / n) * f[i + 1] + 
       ((n - i) / n) * ((n - i - 1) / n) * f[i + 2]

==>

f[i] = (i / n) * (1 + ((i / n) * f[i] + ((n - i) / n) * f[i + 1])) + 
       ((n - i) / n) * ((i + 1) / n) * f[i + 1] + 
       ((n - i) / n) * ((n - i - 1) / n) * f[i + 2]

==>

f[i] = (i / n) + 
       ((i * i) / (n * n)) * f[i] + 
       (i * (n - i) / (n * n)) * f[i + 1] + 
       ((n - i) / n) * ((i + 1) / n) * f[i + 1] + 
       ((n - i) / n) * ((n - i - 1) / n) * f[i + 2]

(n^2 - i^2)f[i] = 
(i * n) + 
(n - i) * (2i + 1) * f[i + 1] + 
(n - i) * (n - i - 1) * f[i + 2]

*/
```

---

## 作者：Jsxts_ (赞：1)

### ARC173 C 

题意：两个人玩游戏，每次一个人等概率选取一个 $[1,n]$ 内的数，若之前被选过，则将分数 $+1$，问所有数都被选过时先手和后手的得分期望。

法一：

设 $dp_{i,0/1}$ 表示已经有 $i$ 个数被选过时，先/后手之后的期望分数。

那么发现只需考虑先手的选取情况：

- 若先手选到一个之前选过的，则转移到 $dp_{i,1}+1$，而后手变为了先手。

- 若先手选到一个之前未选的，则转移到 $dp_{i+1,1}$，后手也转移到 $dp_{i+1,0}$。

所以转移方程为：

$$dp_{i,0}=\frac i n (dp_{i,1}+1)+\frac {n - i}{n}dp_{i+1,1}$$
$$dp_{i,1}=\frac i n dp_{i,0}+\frac {n - i}{n}dp_{i+1,0}$$

解二元一次方程即可。

法二：

上面的转移需要及其明确状态以及转移，而且会在先后手间转移，容易造成思绪混乱。考虑一次解决从选过 $i$ 个到 $i+1$ 个的所有贡献。

那么发现若在由 $i-1\to i$ 时是由先手选取的，那么 $i\to i+1$ 由先手选取的概率为 $p(1-p)+p^3(1-p)+\dots$，否则为 $(1-p)+p^2(1-p)+\dots$，其中 $p=\frac i n$（即选到重复的概率）。那么上述的式子都可以简单地写成封闭形式，而对后手的分析是相同的。

也即，我们设 $d_{i,0/1}$ 表示从 $i\to i+1$ 时，是先/后手操作的概率，可以如上转移。

那么对于答案，我们设 $dp_{i,0/1}$ 表示从 $i\to i+1$ 时，先/后手在这步前期望得分的和。转移类似，分讨 $i-1\to i$ 的情况即可。

---

## 作者：wosile (赞：1)

Atcoder 很喜欢出的等比数列求和概率题。

考虑从“出现了 $i$ 种数”转移到“出现了 $i+1$ 种数”的过程。**以下所有转移都在这两个状态之间进行。** 每个人转转盘都有 $p=\frac{i}{n}$ 的概率抽到已经出现过的数并交一块钱，有 $1-p$ 的概率进入下一个状态。

由于第一个人先手，所以这个问题对于两个人是不对称的。我们考虑记录 $p_1$ 为在刚转移到“出现了 $i$ 种数”的时候下一次转盘是由第一个人转动的概率。同理记 $p_2=1-p_1$。

很明显，一个状态由某个人开始转动，到下一个状态是另一个人开始转动，对应空转偶数次的情况。这样的概率是 $(1-p)+p^2(1-p)+p^4(1-p)+\dots=\frac{1-p}{1-p^2}=\frac{1}{1+p}$。相应的，空转奇数次的概率就是 $\frac{p}{1+p}$。

也就是说，我们可以推出 $p_1$ 如何转移：

$p_1 \leftarrow \frac{pp_1+p_2}{1+p}$

答案也可以通过类似的方式进行统计。由某个人开始转动，这个人期望缴纳的罚款是 $p+p^3+p^5+\dots=\frac{p}{1-p^2}$，另一个人缴纳的罚款是 $\frac{p^2}{1-p^2}$。

也就是说，设 $a_1,a_2$ 分别为两个人的罚款，很明显有：

$a_1\leftarrow a_1+\frac{p_1p+p_2p^2}{1-p^2},a_2\leftarrow a_2+\frac{p_2p+p_1p^2}{1-p^2}$

直接写就完事了，因为有逆元所以时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
typedef long long ll;
ll qp(ll x,int y){
	ll ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
inline ll inv(ll x){return qp(x,mod-2);}
int main(){
	int n; 
	scanf("%d",&n);
	ll p1=1,ans1=0,ans2=0;
	ll invn=qp(n,mod-2);
	for(int i=0;i<n;i++){
		ll p=invn*i%mod;
		ll np1,p2=mod+1-p1;
		ll _p=inv(1+p);
		np1=(p1*p%mod*_p%mod+p2*_p%mod)%mod;
		ll v=p%mod*inv(mod+1-p*p%mod)%mod; 
		ans1=(ans1+p1*v+p2*v%mod*p)%mod;
		ans2=(ans2+p2*v+p1*v%mod*p)%mod;
		p1=np1;
	}
	printf("%lld %lld",ans1,ans2);
	return 0;
	//quod erat demonstrandum
}
```

---

## 作者：鲤鱼江 (赞：0)

记选中之前没选过的数位有效操作，否则为无效操作。

用 $f_i$ 表示当前已有 $i$ 个数选了，先手的人期望花费，倒着 DP 出来。

那么先手期望花费为 $f_0$，后手为 $f_1$。

式子有点烦，不过还算好推。

具体地，可以枚举下两步的状况，分四种（注意此时 $i\neq n-1$）：
+ A 有效 B 无效，概率为 $\frac{(n-i)(i+1)}{n^2}$。
+ A 无效 B 有效，概率为 $\frac{i(n-i)}{n^2}$。
+ A 有效 B 有效，概率为 $\frac{(n-i)(n-i-1)}{n^2}$。
+ 都无效，概率为 $\frac{i^2}{n^2}$。

$i=n-1$ 时有三种情况，直接把式子写出来就行了。

其实没必要分讨 $i=n-1$，但是求稳。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=1e6+10;
const int mod=998244353;
struct modint {
    int val;
    static int norm(const int& x) { return x < 0 ? x + mod : x; }
    modint inv() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) t = a / b, swap(a -= t * b, b), swap(u -= t * v, v);
        return modint(u);
    }
    modint() : val(0) {}
    modint(const int& m) : val(norm(m)) {}
    modint(const long long& m) : val(norm(m % mod)) {}
    modint operator-() const { return modint(norm(-val)); }
    modint& operator+=(const modint& o) { return val = (1ll * val + o.val) % mod, *this; }
    modint& operator-=(const modint& o) { return val = norm(1ll * val - o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint operator-(const modint& o) const { return modint(*this) -= o; }
    modint operator+(const modint& o) const { return modint(*this) += o; }
    modint operator*(const modint& o) const { return modint(*this) *= o; }
	friend std::ostream& operator<<(std::ostream& os, const modint a) { return os << a.val; }
}f[N];
int n;

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;f[n]=0;
	for(int i=n-1;~i;--i){
		modint p=(-modint(1ll*n*n).inv()*(i)*(i)+1).inv();
		modint p2=modint(n).inv(),p3=p2*p2;
		if(i==n-1){
			f[i]=p2*p*(n-1);
		}else {
			f[i]=p*(f[i+2]*(n-i)*(n-i-1)*p3+f[i+1]*(n-i)*(2*i+1)*p3+p2*i);
		}
	}
	cout<<f[0]<<' '<<f[1]<<endl;
	return 0;
}
```

---

## 作者：JackMerryYoung (赞：0)

# 前言

简单期望题。

# 正文

我们来考虑一个 $\mathcal{O}(N)$ 的朴素做法。

令 $K$ 为这个随机数生成器已经产生的不同的数的个数。

设 $p_1, p_2$ 为先手 / 后手“使用随机数生成器后，使得这个随机数生成器已经产生的不同的数的个数从 $K - 1$ 变为 $K$ 后”的概率。

又可以设 $e_1, e_2$ 为先手 / 后手“使用随机数生成器后，使得这个随机数生成器已经产生的不同的数的个数从 $K - 1$ 变为 $K$ 后”付的金额的期望。

我们考虑通过 $K - 1$ 的情况算出 $K$ 的情况。因此我们先考虑 $K = 1$。

不难发现，这位老哥不中枪的概率是（要保证之前他和对手一直中枪）：

$$
\sum_{i = 0}^{\infty}{(1 - \dfrac{q}{N}) \cdot (\dfrac{q}{N})^{2i}}
$$

这位先手老哥要付的钱期望（还是一直中枪）：

$$
\sum_{i = 0}^{\infty}{(\dfrac{q}{N})^{2i+1}}
$$

后手老哥就是先手老哥的柿子里指数减个 $1$。

~~这些无穷级数相信大家都会算，不再赘述。这样就基本做完了。~~

这里再放出一个结论：

$$
\sum_{i = 0}^{\infty}{p^{2i}} = \dfrac{1}{1 - p^2} \quad (0 < p < 1)
$$

~~具体为啥嘛，请读者自证（可以手敲计算器）~~。

证明（使用等比数列求和公式）：

$$
\begin{aligned}
\sum_{i = 0}^{\infty}{p^{2i}} &= \lim_{n \to \infty}{\dfrac{(1 - p^{2n})}{1 - p^2}} \\
&= \dfrac{1}{1 - p^2}
\end{aligned}
$$

显然有了这个结论之后，我们就可以算出上述所有的级数了。

---

