# [语言月赛202303] M Function G

## 题目描述

对于一个长度为 $n$ 的正整数数列 $a$，Farmer John 定义 M 函数 $M(l, r)$ 如下：

$$
M(l, r) = \begin{cases}
\left(M(l, \left \lfloor \dfrac{l + r}{2} \right \rfloor) \bmod \max(M(\left \lfloor \dfrac{l + r}{2} \right \rfloor + 1, r), 7)\right ) + \left(a _ {\left \lfloor \frac{l + r}{2} \right \rfloor} - 1 \right ) & |r - l| > 5 \\
\max \limits _ {l \leq i \leq r}{a _ i} & |r - l| \leq 5
\end{cases}
$$

$\max \limits _ {l \leq i \leq r}{a _ i}$ 代表 $a _ l, a _ {l + 1}, \cdots, a _ {r - 1}, a _ r$ 中的最大值。

$\left \lfloor x \right \rfloor$ 代表 $\leq x$ 的最大整数。比如 $\left \lfloor 4.2 \right \rfloor = 4$，$\left \lfloor 5 \right \rfloor = 5$。

$\max(x, y)$ 代表 $x, y$ 中的最大值。

现在给定 $n$ 和 $a$，请你求出 $M(1, n)$。

## 说明/提示

### 样例 1 解释

我们这里暂时使用 $\max \{a _ l, a _ {l + 1}, \cdots, a _ r\}$ 来表示 $a _ l, a _ {l + 1}, \cdots, a _ r$ 中的最大值。

$$\begin{aligned} 
M(1, 10) &= M(1, 5) \bmod \max(M(6, 10), 7) + (a _ 5 - 1) \\ 
&= \max \{a _ 1, a _ 2 \cdots, a _ 5\} \bmod \max(\max \{a _ 6, a _ 7 \cdots, a _ {10}\}, 7) + (a _ 5 - 1) \\
&= \max \{a _ 1, a _ 2 \cdots, a _ 5\} \bmod \max(84, 7) + (a _ 5 - 1) \\
&= \max \{a _ 1, a _ 2 \cdots, a _ 5\} \bmod 84 + (a _ 5 - 1) \\
&= 91 \bmod 84 + (a _ 5 - 1) \\
&= 7 +  (a _ 5 - 1) \\
&= 11
\end{aligned}$$

### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n \leq 5 \times 10 ^ 5$，$1 \leq a _ i \leq 10 ^ 9$。

| 测试点编号 | $n$ | $a _ i$ |  特殊性质 |
| :----------: | :----------: | :----------: | :----------: |
| $1 \sim 2$ | $\leq 10$ | $\leq 100$ | 无 |
| $3 \sim 5$ | $\leq 10 ^ 3$ | $\leq 10 ^ 4$ | 无 |
| $6$ | $\leq 5 \times 10 ^ 5$ | $\leq 10 ^ 9$ | $a _ i = 1$ |
| $7$ | $= 5$ | $\leq 10 ^ 9$ | 无 |
| $8 \sim 10$ | $\leq 5 \times 10 ^ 5$ | $\leq 10 ^ 9$ | 无 |

## 样例 #1

### 输入

```
10
3 72 26 91 5 84 18 29 50 23```

### 输出

```
11```

# 题解

## 作者：一扶苏一 (赞：10)

# [语言月赛202303] Carrot Harvest G 题解

## Source & Knowledge

2023 年 3 月语言月赛，由洛谷网校入门计划/基础计划提供。

本题考察函数与递归。

## 文字题解

### 题目大意

给定函数


$$
M(l, r) = \begin{cases}
\left(M(l, \left \lfloor \dfrac{l + r}{2} \right \rfloor) \bmod \max(M(\left \lfloor \dfrac{l + r}{2} \right \rfloor + 1, r), 7)\right ) + \left(a _ {\left \lfloor \frac{l + r}{2} \right \rfloor} - 1 \right ) & |r - l| > 5 \\
\max \limits _ {l \leq i \leq r}{a _ i} & |r - l| \leq 5
\end{cases}
$$

和数组 $a$，求 $M(1, n)$。

### 解析

本题需要依照题意定义出所需的函数。定义函数的语法是 `返回类型 函数名(参数列表) {函数体}`。

本函数应该返回一个整数，经过简单的计算可以发现它可能超过 $2 \times 10^9$，于是返回类型应该设计为 `long long`。函数名为 `M`，需要两个参数 $l, r$。于是按如下格式定义这个函数：

```cpp
long long M(int l, int r) {
  // to do
}
```

我们来尝试填写函数体部分：题目给出的式子共分两种情况，第一种是 $|r - l | \leq 5$。此时返回的是区间最大值。我们遍历一遍这段区间就能找到：

```cpp
if (abs(r - l) <= 5) {
  int ret = 0;
  for (int i = l; i <= r; ++i) ret = max(ret, a[i]);
  return ret;
}
```

第二种情况依据题设进行递归处理即可。设 `mid = (l + r) / 2` 可以更方便的完成，$mid$ 的值就是 $\left \lfloor \dfrac{l + r}{2} \right \rfloor$。

```cpp
else {
  int mid = (l + r) / 2;
  return M(l, mid) % max(M(mid + 1, r), 7ll) + a[mid] - 1;
}
```

这里有一个细节是，在 `max` 函数里，因为 M 函数的返回值是 long long，而 STL 提供的 max 函数不能把两个不同类型的变量作比较，所以需要把常数 $7$ 也改为 long long 类型的，即写作 `7ll`。注意后面两个 `l` 是 `L` 的小写形式，不是数字。

把 `if` 和 `else` 的代码填充到前面定义的函数 `M` 的大括号内，在主函数中调用 `M(1, n)` 即可。

## 视频题解

**完整代码请在视频中观看**。

![](bilibili:BV1Vv4y1L7Vc?page=7)

---

