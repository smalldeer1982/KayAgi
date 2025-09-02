# 「FAOI-R2」A trip to Macao

## 题目背景

## 本题目背景仅供引出题意，无任何不良诱导。
## 出题人特别提醒：请勿在赌博非法地区模仿题目中的行为

这天，xhabc66 来到澳门旅游。一下飞机，他直奔赌场。

可是，今天的赌场格外热闹，不知发生了什么。

xhabc66 打开手机一看：啊，原来今天是 $12$ 月 $20$ 日！

因此，赌场在做活动！一年一度！机不可失！

xhabc66 径直走进了赌场。

## 题目描述

赌场贴出了如下规则（**你可以忽略没有加粗的内容**）：

1. 所有玩家在注册后方可进行游戏。
2. 活动期间，**新注册的玩家可从抽奖盒内拿走一枚筹码。抽奖盒内共 $m$ 种筹码，面值分别为 $a_1,a_2,\ldots,a_m$ 澳元（均为正整数）**，每种一个，保证公平。
3. 本赌场仅提供一种游戏：猜拳。游戏开始时，双方各下注相同数量（以 $1$ 澳元为单位）的筹码；若猜拳分出胜负，则胜者拿走所有下注。
4. 根据上一条可知，**玩家一次游戏中赢得的筹码（正整数）不得超过自身所携带的筹码**。
5. 公平游戏，严禁作弊，违者严惩。

xhabc66 注册后，**连赢数局（可以是 $0$ 局，但没有输过，也没有平局过）**，最终带着 $n$ 澳元走出了赌场。

出赌场后，xhabc66 突然好奇他是怎么赢到这么多钱的。然而，他不记得他每局下了多少注，不记得他一共玩了多少局，甚至不记得他开始时拿走的筹码是什么面值。

**他想知道：他有多少种不同的赢钱方法。**

**答案对 $10^9+7$ 取模。**

> 两种赢钱方法在满足以下任何一个条件时，xhabc66 都会认为它们不同：
>
> - 他某一局的下注金额不同；
> - 他玩的局数不同；
> - 他开始时拿走的筹码的面值不同。

### 形式化题意

求有多少个数列 $\{b_k\}$ 满足：

1. $\forall i \in [1,k],b_i \in \mathbb{N^*}$；
2. $\forall i \in [2,k],b_i \in [b_{i-1}+1,b_{i-1} \times 2]$；
3. $b_1 \in\{a_m\}$；
4. $b_k=n$。

数列的长度 $k$ 可以是任何**正整数**。

答案对 $10^9+7$ 取模。

## 说明/提示

样例 $1$ 解释：

```plain
1 2 3 4
1 2 4
2 3 4
2 4
3 4
4
```

样例 $2$ 解释：

```plain
1 2 3 4 5
1 2 3 5
1 2 4 5
```

----------

**本题采用捆绑测试。**

| Subtask 编号 | $m \le$ | $n \le$ | 分值 |
| :-: | :-: | :-: | :-: |
| $0$ | $3$ | $3$ | $20$ |
| $1$ | $10^5$ | $10^5$ | $40$ |
| $2$ | $10^6$ | $10^8$ | $40$ |

对于 $100\%$ 的数据，$1 \le m \le 10^6$，$1 \le a_1<a_2<\ldots<a_m \le n \le 10^8$，$m \le n$。

> **提示：** 请注意本题不同寻常的内存限制！

## 样例 #1

### 输入

```
4 4
1 2 3 4```

### 输出

```
6```

## 样例 #2

### 输入

```
5 1
1```

### 输出

```
3```

## 样例 #3

### 输入

```
12345678 9
1 2 3 45 67 89 123 456 789```

### 输出

```
998899106```

# 题解

## 作者：xhabc66 (赞：10)

## $\texttt{Subtask 0}$

爆搜。或者直接输出 $m$。

## $\texttt{Subtask 0.5}$

设 $a_i$ 为最终赢到 $i$ 澳元的方案数，$c_i$ 表示是否有面值为 $i$ 的筹码（有为 $1$，没有为 $0$），则 $a_n$ 为答案。

递推式：

$$a_1=c_1$$
$$a_{i+1}=(a_{\lceil\frac{i+1}{2}\rceil}+\ldots+a_{i-1}+a_i)+c_{i+1}$$

时间 / 空间复杂度为 $O(n^2+m)/O(n+m)$。


## $\texttt{Subtask 1}$

设 $b_i$ 为 $a_i$ 的前缀和（$b_1=a_1$，$b_i=b_{i-1}+a_i$），注意到 $\lceil\dfrac{i+1}{2}\rceil=\lfloor\dfrac{i}{2}\rfloor+1$，则 $b_n-b_{n-1}$ 为答案。
$$b_1=c_1$$
$$b_{i+1}=(b_i+b_i-b_{\lfloor\frac{i}{2}\rfloor})+c_{i+1}$$

时间 / 空间复杂度为 $O(n+m)/O(n+m)$。

## $\texttt{Subtask 2}$

不难发现，求 $b_{i+1}$ 时只需要 $b_i$ 及 $b_{\lfloor\frac{i}{2}\rfloor}$ 的值。**于是，我们可以每次只存 $b_i,b_{\lfloor\frac{i}{2}\rfloor},b_{\lfloor\frac{i}{4}\rfloor},b_{\lfloor\frac{i}{8}\rfloor},\ldots,b_1$ 的值**。例如：

| $i$ | 存储的下标 |
| -----------: | -----------: |
| $1$ | $1$ |
| $2$ | $2,1$ |
| $3$ | $3,1$ |
| $4$ | $4,2,1$ |
| $5$ | $5,2,1$ |
| $6$ | $6,3,1$ |
| $7$ | $7,3,1$ |
| $8$ | $8,4,2,1$ |
| $\ldots$ | $\ldots$ |

不难发现，每次从右往前更新即可。时间 / 空间复杂度为 $O(n+m)/O(m+ \log n)$。

## 参考代码（std）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int B = 32, P = 1e9 + 7, M = 1e6 + 5;
int b[B], p[B], a[M];
int main()
{
    int n, m, s = 0;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
    {
        int t = i & (-i);
        for (int j = 1, k = 1, l = i; k <= t; j++, k <<= 1, l >>= 1)
        {
            b[j] <<= 1;
            b[j] -= b[j + 1];
            if (p[j] != m && a[p[j] + 1] == l) b[j]++, p[j]++;
            b[j] %= P;
            if (b[j] < 0) b[j] += P;
        }
        if (i == n - 1) s -= b[1];
        if (i == n) s += b[1];
    }
    cout << (s % P + P) % P;
    return 0;
}
```

---

## 作者：VTloBong (赞：8)

## 主要思路
一个 $O(\min(m\log{n},\log^3{n}))$ 的做法。  
首先令 $g_i$ 是从 $b_1=i$ 时 $b$ 序列的数目，$f_i$ 为 $g_i$ 的后缀和，特别的，$f_{n+1}=0$。  
那么有 $f_n=1$,$f_i =2 \times f_{i+1}-f_{\min\{ 2i, n + 1\}} (i<n)$，直接递推便是 $60$ 分的做法。  
为降低复杂度，考虑如何快速计算 $f_i$。  
将 $[1,n]$ 分为 $O(\log n)$ 个不相交区间：$[\lceil \frac{n}{2} \rceil,n]$，$[\lceil \frac{n}{4} \rceil,\lceil \frac{n}{2} \rceil)$，$[\lceil \frac{n}{8} \rceil,\lceil \frac{n}{4} \rceil)\cdots$
记第 $0$ 个区间是 $[\lceil \frac{n}{2} \rceil,n]$，第 $l(l>0)$ 个区间是 $[\lceil \frac{n}{2^{l+1}} \rceil,\lceil \frac{n}{2^l} \rceil)$，可以发现若 $i$ 在第 $l(l>0)$ 个区间中，则 $2i+1$ 在第 $l-1$ 个区间中。  
可以通过归纳法证明 $f_i$ 在第 $l$ 个区间内的通项公式具有 $\sum\limits_{k=0}^{l}c_{l,k}\times 2^{-i\times 2^k}$ 的形式。  
第 $0$ 个区间内通项公式为 $f_i = 2^{n-i}$，相应地，$c_{0,0}=2^n$。  
如果已知第 $l-1$ 个区间的通项公式为 $\sum\limits_{k=0}^{l-1}c_{l-1,k}\times 2^{-i\times 2^k}$，那么根据第 $l(l>0)$ 个区间 $[\lceil \frac{n}{2^{l+1}} \rceil,\lceil \frac{n}{2^l} \rceil)$ 内的递推公式：
$$f_i=2f_{i+1}-f_{2i+1}$$
其中 $2i+1 \in [\lceil \frac{n}{2^{l}} \rceil,\lceil \frac{n}{2^{l-1}} \rceil)$，可以得到：
$$f_i=2f_{i+1}-\sum\limits_{k=0}^{l-1}c_{l-1,k}\times 2^{-(2i+1)\times 2^k}$$
$$2^if_i=2^{i+1}f_{i+1}-\sum\limits_{k=0}^{l-1}\frac{c_{l-1,k}}{2^{2^k}}\times 2^{(1-2^{k+1})\times i}$$
递推并对等比数列求和得到：
$$\begin{aligned}2^if_i &=2^{\lceil \frac{n}{2^l} \rceil}f_{\lceil \frac{n}{2^l} \rceil}-\sum\limits_{k=0}^{l-1}\frac{c_{l-1,k}}{2^{2^k}}(\sum_{j=i}^{\lceil \frac{n}{2^l} \rceil-1} 2^{(1-2^{k+1})\times j}) \\&=\sum\limits_{k=0}^{l-1}c_{l-1,k}\ 2^{-\lceil \frac{n}{2^{l}} \rceil\times 2^k}-\sum\limits_{k=0}^{l-1}\frac{c_{l-1,k}(2^{(1-2^{k+1})\lceil \frac{n}{2^l} \rceil}- 2^{(1-2^{k+1})\times i})}{2^{1-2^{k}}-2^{2^k}}\end{aligned}$$  
整理得到：
$$f_i=2^{-i}\sum\limits_{k=0}^{l-1}c_{l-1,k}(2^{-\lceil \frac{n}{2^{l}} \rceil\times 2^k}-\frac{2^{(1-2^{k+1})\lceil \frac{n}{2^l} \rceil}}{2^{1-2^{k}}-2^{2^k}})+\sum\limits_{k=0}^{l-1}\frac{c_{l-1,k}2^{-i\times 2^{k+1}}}{2^{1-2^{k}}-2^{2^k}}$$
又因为：
$$f_i=\sum\limits_{k=0}^{l}c_{l,k}\times 2^{-i\times 2^k}$$
对照系数得到 $l>0$ 时的递推式：
$$c_{l,0}=\sum\limits_{k=0}^{l-1}c_{l-1,k}(2^{-\lceil \frac{n}{2^{l}} \rceil\times 2^k}-\frac{2^{(1-2^{k+1})\lceil \frac{n}{2^l} \rceil}}{2^{1-2^{k}}-2^{2^k}})$$
$$c_{l,k+1}=\frac{c_{l-1,k}}{2^{1-2^{k}}-2^{2^k}}$$

$O(\log^3n)$ 递推得到所有 $c_{l,k}$ 后，就能 $O(\log{n})$ 计算一次 $f_i$，因为需要计算每个 $g_{a_i}$，总复杂度为 $O(m\log{n})$。
## 参考代码：
```cpp
void solve()
{
    int n, m;
    cin >> m >> n;
    vector c(28, vector<int>(28));
    int i2 = (mod + 1) / 2;
    c[0][0] = qpow(2, m);
    for (int i = 1, j = (m + 1) / 2; j > 1; i++, j = (j + 1) / 2)
    {
        for (int k = 0; k < i; k++)
        {
            c[i][0] = (c[i][0] + (qpow(2, ((1 - (1LL << k)) * j)) + mod - qpow(2, (1 - (1LL << k + 1)) * j) * qpow(qpow(2, 1 - (1LL << k)) - qpow(2, (1LL << k)), mod - 2) % mod) % mod * c[i - 1][k] % mod) % mod;
            c[i][k + 1] = qpow(qpow(2, 1 - (1LL << k)) - qpow(2, (1LL << k)), mod - 2) * c[i - 1][k] % mod;
        }
    }
    auto f = [&](int x) -> i64
    {
        if (x > m)
            return 0;
        for (int i = 0, j = m; j > 1; i++, j = (j + 1) / 2)
        {
            if (x < (j + 1) / 2)
                continue;
            int res = 0, m2 = qpow(2, -x);
            for (int k = 0; k <= i; k++)
                res += c[i][k] * m2 % mod, 
                m2 = m2 * m2 % mod, res %= mod;
        
            return res;
        }
    };
    i64 ans = 0;
    for (int i = 1, x; i <= n; i++)
        cin >> x, ans = (ans + f(x) - f(x + 1) + mod) % mod;
    cout << ans << "\n";
}
```

---

## 作者：Disjoint_cat (赞：4)

# [P10036 A trip to Macao](https://www.luogu.com.cn/problem/P10036)

## 前言

赛时空间限制开了 $16\;\texttt{MB}$ 然后让我的 `bitset` 草过去了还拿了个首杀。

于是~~毒瘤~~出题人赛后把空间限制改成了 $8\;\texttt{MB}$……

然后想了一想优化，过了。~~但是还是被别人的优秀做法暴打了……~~

## 题解

~~不会有人题面都没看懂就来翻题解吧……~~

### 20 分

首先注意到 $b$ 数列是严格递增的，所以可以以当前的筹码数为状态 dp。

设 $dp_{i}$ 为最后一个数为 $i$ 时的方案数。另外，令 $init_i$ 为初始筹码中有无 $i$（有为 $1$，无为 $0$）。

则初始时令 $dp_i\gets init_i$，之后 $dp_i$ 转移时，可以转移到 $dp_{i+1},\ldots,dp_{2i}$，答案即为 $dp_n$。时间复杂度 $\Theta(n^2+m)$，空间复杂度 $\Theta(n)$。期望得分 20。

### 60 分

可以发现这个 dp 是一次更新一段区间的 $dp$ 值。考虑前缀和优化。

令 $f_i=dp_{i}-dp_{i-1}$（这里的变量指的是最终的答案），即 $dp$ 的差分。 那么这个 dp 就转化成了：

> 初始时，令所有的 $f_i=init_i-init_{i-1}$，并令 $cur\gets0$。
>
> 依次枚举 $i=1,2,\ldots,n$，执行：
>
> - 令 $cur\gets cur+f_i$，此时 $cur$ 即为 $dp_i$ 的值。
> - 要对 $j\in[i+1,2i]$ 的 $dp_j$ 都加上 $cur$，所以令 $f_{i+1}\gets f_{i+1}+cur,f_{2i+1}\gets f_{2i+1}-cur$。 
>
> 最后 $cur$ 的值为 $dp_n$，即答案。

时间复杂度为 $\Theta(n+m)$，空间复杂度为 $\Theta(n)$（到目前为止还是需要存下 $f$ 和 $init$ 的值）。期望得分 60。

### 100 分

现在的算法用的是刷表法，不好优化空间。考虑改成填表法。**注意执行完 $i$ 后时的 $cur$ 值就是 $dp_i$。**

> 考虑 $f_i$ 能被什么东西影响到。
>
> 首先是 $init$ 里面的值。
>
> 然后就是枚举到 $i-1$ 时的 $cur$，即 $dp_{i-1}$。
>
> 最后是 $dp_x$ 对 $f_{2x+1}$ 造成的影响。可以发现当且仅当 $i$ 为奇数时，$f_i$ 要减去 $dp_{\frac{i-1}2}$。

那么就有：

$$f_i=\begin{cases}init_i-init_{i-1}+dp_{i-1},&2\mid i\\init_i-init_{i-1}+dp_{i-1}-dp_{\frac{i-1}2},&2\nmid i\end{cases}$$

即

$$dp_i=dp_{i-1}+f_i=\begin{cases}init_i-init_{i-1}+2dp_{i-1},&2\mid i\\init_i-init_{i-1}+2dp_{i-1}-dp_{\frac{i-1}2},&2\nmid i\end{cases}$$

来看这个式子。$dp_{i-1}$ 就是转移前的值，它是简单的。

先暂时不管 $init$，只看 $dp_{\frac{i-1}2}$。这个东西怎么维护呢？

注意到 $\dfrac{i-1}2=\dfrac{(i-2)-1}2+1$，所以当枚举到 $i-2$ 时，就已经知道了 $dp_{\frac{i-3}2}$ 的值。所以其实可以直接把这东西向后转移一位，就得到了 $dp_{\frac{i-1}2}$ 的值。

这启发我们使用递归。具体的，可以存储并维护下列值：

$$dp_i,dp_{\lfloor\frac{i-1}2\rfloor},dp_{\lfloor\frac{i-3}4\rfloor},\ldots,dp_1$$

这样，每次转移某个位置时，如果它的新位置是**不小于 $3$ 的**奇数（注意 $i=1$ 时 $\frac{i-1}2=0$，也就是从 $dp_3$ 开始才会减掉东西），则把其后面的一个 $dp$ 值也转移一位，然后减去后面位置的值；如果新位置是偶数，则可以直接转移。

注意到第 $t$ 个位置只会被转移 $\Theta\left(\left\lfloor\dfrac n{2^t}\right\rfloor\right)$ 次，所以转移次数仍然为 $\Theta(n)$，同时这部分的空间复杂度变成了 $\Theta(\log n)$。

最后一个问题：怎么维护 $init$ 数组的查询？

可以想到开 `std::bitset`。但空间为 $\dfrac{10^8}8\;\texttt B\approx12\;\texttt{MB}$，不能卡进 $8\;\texttt{MB}$。

注意到把原筹码数组存下来只需要 $4\;\texttt{MB}$，可以开下，而且题目保证了原数列递增。而每次的 $dp$ 转移都只会移动一位，所以对于存储的每一个 $dp$ 值双指针维护即可。

时间复杂度 $\Theta(n+m)$，空间复杂度 $\Theta(m+\log n)$。

## 代码片段

下面 `f` 数组是存下的 $dp$ 值，`pos` 是存储的 $dp$ 位置，`ptr` 是维护的指针。短短的，~~很可爱~~。

```cpp
const int N=1000005,L=28,MOD=1000000007;
int n,m;
int val[N];
int pos[L],f[L],ptr[L];
void inc(int p)
{
	++pos[p];
	f[p]<<=1;
	if(val[ptr[p]-1]==pos[p]-1)f[p]--;
	if(val[ptr[p]]==pos[p])++ptr[p],f[p]++;
	if((pos[p]&1)&&(pos[p]>1))inc(p+1),f[p]-=f[p+1];
	f[p]%=MOD;if(f[p]<0)f[p]+=MOD;
}
void Solve()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>val[i];val[m+1]=INT_MAX,val[0]=INT_MIN;
	fill(ptr+1,ptr+28,1);
	for(int i=1;i<=n;i++)inc(1);
	cout<<f[1];
}
```

---

完结撒花！

---

## 作者：JURUOzhao (赞：3)

## P10036题解
这道题确实是一道非常有趣
~~恶心~~的题目，对于时间与空间复杂度的严格要求十分考验代码水平（~~欺负我这个蒟蒻~~），下面让我们一起来分析一下这道题目：
#### 1. 初步思路
通过对题目的审读，我们可以考虑 $dp$ 来解决这道题。\
通过这句话“ $$b_{k}=n$$ "设计状态 $$f_{i}$$ 为以自然数为 $i$ 结尾的方案数量$$。 mp_{i}$$ 表示 $i$ 这个数是否出现过。\
通过这句话“ $$\forall b_{i}\in\left[{2},{k}\right],b_{i}\in\ [b_{i-1}+1,b_{i-1}/2]$$ ”
得到状态的转移
$$f_{i+1}=(\sum_{j=\lceil\tfrac{i+1}{2} \rceil }^nf_j)+mp_{i+1}$$。\
（相信大家一定做过类似于跳楼梯这样的题，每次只能往上走一个或两个台阶，问总方案数，这道题的转移跟跳楼梯类似，都是需要去找该状态能从哪些状态直接转移到）。

#### 2. 时间优化
观察式子，这是一个非常明显的前缀和优化，设 $$g_{i}$$ 为 $$f_{i}$$ 的前缀和，因为 $$\left\lceil\dfrac{i+1}{2}\right\rceil=\left\lfloor\dfrac{i}{2}\right\rfloor+1$$ ，我们不难得到：
$$g_{i+1}=g_{i}+a_{i}+mp_{i+1}$$
  $$a_{i}=g_{i}-g_{i/2}$$
整理上面两个式子我们可以得到
$$g_{i+1}=g_{i}+g_{i}-g_{i/2}+mp_{i+1}$$
此时递推求解，最后答案为 $$g_{n}-g_{n-1} 。$$时间复杂度 $$O(n+m)$$ , 空间复杂度 $$O(n+m)$$ 。

#### 3. 空间优化
最恶心的点来了，这道题的空间限制为8MB,也就说直接开一个长度为$n$的数组根本不可行接下来让我们来看这幅图（手画版比较丑，还请见谅）
![](https://cdn.luogu.com.cn/upload/image_hosting/1dp6ny1t.png)\
我们可以画出来这个式子的递推（也可以说是搜索过程）我们发现可以将上图的上方结构优化改变成为下方结构。
![](https://cdn.luogu.com.cn/upload/image_hosting/cle048sq.png)
对优化后的结构进行观察，我们能够发现每次更新只需要 $$log_{2}n$$ 的空间（图中画方框的部分），第 $i$ 次修改只需要对 $i$ 的二进制数中从右往左数第一个1出现时此时数的大小再对2取 $log$ 再加1即可，即每次修改只需修改前 $$log_2(i\&(-i))+1$$ 个空间即可，同时维护pos指针与当前空间对应的自然数id即可。空间复杂度 $$O(m+log_2n)$$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int md=1e9+7;
int n,m;
int mp[1000500],pos[35];
struct nd{
	int sum,id;
}g[35];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>mp[i];
	}
	int ans=0;	
	for(int i=1;i<=n;i++){
		int k=i&(-i),j=1,q=i;
		while(k){
			k>>=1;
			g[j].id=i/(1<<(j-1));
			g[j].sum<<=1;
			g[j].sum-=g[j+1].sum;
			if(mp[pos[j]+1]==g[j].id)g[j].sum++,pos[j]++;
			g[j].sum%=md;
			g[j].sum=(g[j].sum+md)%md;
			j++;
		}
		if(i==n-1)ans-=g[1].sum;
		if(i==n)ans+=g[1].sum;
	}
	cout<<(ans+md)%md;
   return 0;
}
```
至于为什么用指针维护，是因为经过测试如果用STL的 $map$ 来维护的话也会爆空间（~~本蒟蒻太菜了，不知道其他大佬有没有更优秀或者编码更简便的维护方式）~~。
（第一篇题解，希望通过）

---

## 作者：irris (赞：3)

## Preface

> ？

## Solution

$f_i = \displaystyle\sum_{j=\lceil i/2\rceil}^{i-1} f_j + \displaystyle \sum_{j=1}^m [a_j = i]$。

考虑前缀和，$f_i = 2f_{i-1} - f_{\lfloor (i-1)/2 \rfloor} + cur_i$，$cur$ 表示是否出现过。

发现转移只需要用到 $-1$ 和 $/2$，后者是不好处理的。于是我们每次存储 $f_i, f_{i/2}, f_{i/4}, \dots ,f_{i/2^k}$，其中 $k = \mathcal O(\log n)$。

考虑转移，直接从 $i/2^0$ 到 $i/2^{\text{ctz}(i)}$ 枚举一遍。这样依赖关系就对了，也能正确找到转移了。

复杂度均摊 $(n + n/2 + n/4 + \dots ) \times \frac 1n = \mathcal O(1)$。

但是 $cur$ 不能直接二分有没有出现，这是 $n\log m$，注意到 $a$ 已经有序，所以对每个 $2^k$ 跑个双指针状物即可。

## Code

```cpp
int main() {
    int N = read<int>(), M = read<int>(), ans = 0;
    for (int i = 0; i < M; ++i) a[i] = read<int>();
    for (int i = 1, t, k; i <= N; ++i) {
        t = __builtin_ctz(i), k = i;
        for (int j = 0; j <= t; ++j, k >>= 1) {
            add(dp[j], dp[j]), del(dp[j], dp[j + 1]);
            if (a[cur[j]] == k) add(dp[j], 1), ++cur[j];
        }
        if (i == N - 1) ans = MOD - dp[0];
    }
	return print<int>(sum(ans, dp[0])), 0;
}
```

---

