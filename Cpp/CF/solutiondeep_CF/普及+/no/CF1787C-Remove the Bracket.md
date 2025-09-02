# 题目信息

# Remove the Bracket

## 题目描述

RSJ 得到了一个长为 $n$ 的序列 $a_1,a_2, \ldots, a_n$ 和一个正整数 $s$，他想要计算 $\prod\limits_{i=1}^n a_i$。对于 $a_2,a_3, \ldots, a_{n-1}$ 中的每一个，他都选取了一对**非负整数** $x_i,y_i$ 使得 $x_i + y_i = a_i$ 且 $(x_i-s) \cdot (y_i-s) \geq 0$。他使用如下的方法计算：

$$
\begin{aligned}
\text{Product} &= a_1 \cdot a_2 \cdot a_3 \cdot \ldots \cdot a_n \\
&= a_1 \cdot (x_2+y_2) \cdot (x_3+y_3) \cdot (x_4 + y_4) \cdot \ldots \cdot (x_{n-1}+y_{n-1}) \cdot a_n \\
&\overset{\text{?}}{=} a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + y_4 \cdot \ldots \cdot x_{n-1}+y_{n-1} \cdot a_n
\end{aligned}
$$

但是他在计算时出现了错误，不小心把括号弄丢了（式子第 $3$ 行）。于是，他想要知道写错了的式子（$F = a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + y_4 \cdot \ldots \cdot x_{n-1}+y_{n-1} \cdot a_n$）的最小值是多少。

~~这是原本的题面，审核改成了现在的样子（真就 remove the bracket 了，导致赛时式子有歧义，在此向大家道歉~~


第二行 $n$ 个正整数 $a_1,a_2,\ldots,a_n$（$0 \le a_i \le 2 \cdot 10^5$）表示序列 $a$。

保证所有测试数据的 $n$ 之和不超过 $2\cdot 10^5$。

## 样例 #1

### 输入

```
10
5 0
2 0 1 3 4
5 1
5 3 4 3 5
7 2
7 6 5 4 3 2 1
5 1
1 2 3 4 5
5 2
1 2 3 4 5
4 0
0 1 1 1
5 5
4 3 5 6 4
4 1
0 2 1 0
3 99999
200000 200000 200000
6 8139
7976 129785 12984 78561 173685 15480```

### 输出

```
0
18
32
11
14
0
16
0
40000000000
2700826806```

# AI分析结果

### 题目内容重写

#### 题目描述

RSJ 得到了一个长度为 $n$ 的序列 $a_1,a_2, \ldots, a_n$ 和一个正整数 $s$，他想要计算 $\prod\limits_{i=1}^n a_i$。对于 $a_2,a_3, \ldots, a_{n-1}$ 中的每一个，他都选取了一对**非负整数** $x_i,y_i$ 使得 $x_i + y_i = a_i$ 且 $(x_i-s) \cdot (y_i-s) \geq 0$。他使用如下的方法计算：

$$
\begin{aligned}
\text{Product} &= a_1 \cdot a_2 \cdot a_3 \cdot \ldots \cdot a_n \\
&= a_1 \cdot (x_2+y_2) \cdot (x_3+y_3) \cdot (x_4 + y_4) \cdot \ldots \cdot (x_{n-1}+y_{n-1}) \cdot a_n \\
&\overset{\text{?}}{=} a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + y_4 \cdot \ldots \cdot x_{n-1}+y_{n-1} \cdot a_n
\end{aligned}
$$

但是他在计算时出现了错误，不小心把括号弄丢了（式子第 $3$ 行）。于是，他想要知道写错了的式子（$F = a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + y_4 \cdot \ldots \cdot x_{n-1}+y_{n-1} \cdot a_n$）的最小值是多少。

### 算法分类

动态规划

### 题解分析与结论

这道题的核心在于如何将序列中的每个元素 $a_i$ 拆分成 $x_i$ 和 $y_i$，并满足 $(x_i-s)(y_i-s) \geq 0$，同时使得最终的错误表达式 $F$ 最小。通过分析，可以发现 $x_i$ 和 $y_i$ 的取值只能在特定的范围内，且可以通过动态规划来优化求解过程。

### 精选题解

#### 题解1：yimuhua (赞：16)

**星级：5星**

**关键亮点：**
- 通过分析 $(x_i-s)(y_i-s) \geq 0$ 的条件，得出了 $x_i$ 和 $y_i$ 的上下界。
- 使用动态规划 $dp_{i,0/1}$ 来表示处理到第 $i$ 组时，$x_i$ 取上界或下界的最小 $F$ 值。
- 代码简洁明了，逻辑清晰。

**核心代码：**
```cpp
dp[2][0] = a[1] * mini[2], dp[2][1] = a[1] * maxi[2];
for(int i = 3; i < n; i++)
    dp[i][0] = min(dp[i - 1][0] + maxi[i - 1] * mini[i], dp[i - 1][1] + mini[i - 1] * mini[i]), 
    dp[i][1] = min(dp[i - 1][0] + maxi[i - 1] * maxi[i], dp[i - 1][1] + mini[i - 1] * maxi[i]);
cout << min(dp[n - 1][0] + a[n] * maxi[n - 1], dp[n - 1][1] + a[n] * mini[n - 1]) << '\n';
```

#### 题解2：KingPowers (赞：5)

**星级：4星**

**关键亮点：**
- 通过猜测和验证，得出了 $x_i$ 和 $y_i$ 的取值策略。
- 使用动态规划 $f[i][0/1]$ 来表示前 $i$ 组的最小 $F$ 值。
- 代码实现较为详细，逻辑清晰。

**核心代码：**
```cpp
f[i][0] = min({f[i-1][0]+xy[i-1][1]*xy[i][0], f[i-1][1]+xy[i-1][0]*xy[i][0]});
f[i][1] = min({f[i-1][0]+xy[i-1][1]*xy[i][1], f[i-1][1]+xy[i-1][0]*xy[i][1]});
```

#### 题解3：hcywoi (赞：2)

**星级：4星**

**关键亮点：**
- 通过分析 $(x_i-s)(y_i-s) \geq 0$ 的条件，得出了 $x_i$ 和 $y_i$ 的取值策略。
- 使用动态规划 $f_{i,0/1}$ 来表示前 $i$ 组的最小 $F$ 值。
- 代码实现简洁，逻辑清晰。

**核心代码：**
```cpp
f[i][0] = min(f[i-1][0] + maxi[i-1] * mini[i], f[i-1][1] + mini[i-1] * mini[i]);
f[i][1] = min(f[i-1][0] + maxi[i-1] * maxi[i], f[i-1][1] + mini[i-1] * maxi[i]);
```

### 最优关键思路

1. **确定上下界**：通过分析 $(x_i-s)(y_i-s) \geq 0$ 的条件，确定 $x_i$ 和 $y_i$ 的取值上下界。
2. **动态规划**：使用 $dp_{i,0/1}$ 来表示处理到第 $i$ 组时，$x_i$ 取上界或下界的最小 $F$ 值，通过状态转移方程进行优化求解。

### 可拓展之处

类似的问题可以通过动态规划来解决，尤其是在需要优化某种表达式或函数的最小值或最大值时。动态规划的状态设计和转移方程是关键，通常需要根据问题的具体条件来确定。

### 推荐题目

1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)

---
处理用时：52.75秒