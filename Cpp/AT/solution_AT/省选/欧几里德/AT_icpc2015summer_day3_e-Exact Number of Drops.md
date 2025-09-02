# Exact Number of Drops

## 题目描述

给定两个容量分别为 $a$ 滴水和 $b$ 滴水的杯子（开始时均为空），每步都做以下操作之一：

- 将某个杯子倒空；
- 将某个杯子装满；
- 将一个杯子的水倒到另一个杯子，直到第一个杯子倒空或者第二个杯子装满。   

求使得任意一个杯子装上恰好 $c$ 滴水的最少步数。

# 题解

## 作者：ZeroOf149 (赞：2)

# [AT_icpc2015summer_day3_e Exact Number of Drops](https://www.luogu.com.cn/problem/AT_icpc2015summer_day3_e)

## 题目描述

给定两个容量分别为 $a$ 滴水和 $b$ 滴水的杯子（开始时均为空），每步都做以下操作之一：

- 将某个杯子**倒空**；
- 将某个杯子**装满**；
- 将一个杯子的水倒到另一个杯子，直到第一个杯子**倒空**或者第二个杯子**装满**。   

求使得任意一个杯子装上恰好 $c$ 滴水的最少步数。

## 解法说明

显然 $c > \max(a,b)$ 的时候无解，$c=a \vee c=b$ 的时候只要倒一次即可。  
下面我们讨论剩余的情况，并假设题目中两个杯子分别为 A 和 B。

手动模拟样例，会发现步骤有以下特征： 
1. 是倒空杯子 A $\leftrightarrow$ 杯子 B 倒到杯子 A $\leftrightarrow$ 装满杯子 B 这一类操作的循环；  
2. 倒空某一个杯子前，这个杯子是满的；装满某一个杯子前，这个杯子是空的。  
  
事实上，如果我们不这么做，显然有更优的解法。

观察每个操作，容易发现：在任意时刻，一定有某一个杯子是空的或满的。
这启发我们通过两个杯子**装水的总量**来确定两个杯子**分别装的水**。不妨假设目标总容量为 $k (0 < k \leq a+b)$。  
接下来考虑每次操作对总量的影响：
1. 将一个杯子的水倒到另一个杯子：总量不变；  
2. 将某个杯子装满或倒空：由上面第二条，发现只会加上或减去杯子容量。

结合上面第一条：  
假设我们倒空杯子 A 有 $X$ 次，装满杯子 B 有 $Y$ 次，就有 $-aX+bY=k$。  
如果我们希望任意一个杯子装上恰好 $c$ 滴水，$k$ 就只能在 $\{c, a+c, b+c\}$ 里面取。  
这时我们又发现：在最优方案中，最后一步是杯子 B 倒到杯子 A（否则这个方案就是由其他 $k$ 值生成的方案再加几步得到的，或者是不合法的方案），于是这种操作的步数恰为 $(X+Y)$，总步数为 $2(X+Y)$。对每个 $k$ 分别求 $2(X+Y)$ 取最小值即可。  

剩下的问题是：对于一个 $k$，如何求出 $X$ 和 $Y$？  
根据裴蜀定理，当 $\gcd(a,b) \nmid k$ 的时候无解。注意上文 $k$ 的取值，这等价于 $\gcd(a,b) \nmid c$。  
对于剩下的情况，我们先通过 exgcd 求出 $ax+by=\gcd(a,b)$ 的一组解 $(x_{0}, y_{0})$ ，这样就有 $ax+by=k$ 的解集为
$\left\{ \begin{array}{}
x = -\dfrac{b}{\gcd(a,b)} \times t + \dfrac{k}{\gcd(a,b)} \times x_{0} \\
y = \dfrac{a}{\gcd(a,b)} \times t + \dfrac{k}{\gcd(a,b)} \times y_{0}
\end{array}\right. (t \in \mathbb{Z})$，  
而且 $X=|x|, Y=|y|$。  
此时 $X+Y=|x|+|y|$ 的最小值是容易求出的：考虑到 $x,y$ 异号，因此 $|x|+|y|=|x|+|-y|=|x-y|$。

## 代码实现
```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <numeric>
#include <tuple>

using ll = long long;

ll exgcd(ll a, ll &x, ll b, ll &y) {
  ll x1 = 1, x2 = 0, x3 = 0, x4 = 1;
  while (b) {
    ll q = a / b;
    std::tie(x1, x2, x3, x4, a, b) =
        std::tuple{x3, x4, x1 - q * x3, x2 - q * x4, b, a % b};
  }
  x = x1;
  y = x2;
  return a;
}

int T;
ll a, b, c, x, y, g;

ll f(ll k, ll b) {
  ll t = std::abs(b % k);
  return std::min(t, k - t);
}

ll work(ll k) { return f((a + b) / g, k / g * (y - x)); }

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%lld %lld %lld", &a, &b, &c);
    g = std::gcd(a, b);
    if (c > std::max(a, b) || c % g) {
      puts("-1");
      continue;
    }
    if (c == a || c == b) {
      puts("1");
      continue;
    }
    exgcd(a, x, b, y);
    ll mn = std::min(a, b);
    printf("%lld\n",
           std::min(work(c),
                    c <= mn ? std::min(work(a + c), work(b + c)) : work(mn + c))
               << 1);
  }
}
```

---

