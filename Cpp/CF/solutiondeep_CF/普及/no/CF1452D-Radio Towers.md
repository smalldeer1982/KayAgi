# 题目信息

# Radio Towers

## 题目描述

There are $ n + 2 $ towns located on a coordinate line, numbered from $ 0 $ to $ n + 1 $ . The $ i $ -th town is located at the point $ i $ .

You build a radio tower in each of the towns $ 1, 2, \dots, n $ with probability $ \frac{1}{2} $ (these events are independent). After that, you want to set the signal power on each tower to some integer from $ 1 $ to $ n $ (signal powers are not necessarily the same, but also not necessarily different). The signal from a tower located in a town $ i $ with signal power $ p $ reaches every city $ c $ such that $ |c - i| < p $ .

After building the towers, you want to choose signal powers in such a way that:

- towns $ 0 $ and $ n + 1 $ don't get any signal from the radio towers;
- towns $ 1, 2, \dots, n $ get signal from exactly one radio tower each.

For example, if $ n = 5 $ , and you have built the towers in towns $ 2 $ , $ 4 $ and $ 5 $ , you may set the signal power of the tower in town $ 2 $ to $ 2 $ , and the signal power of the towers in towns $ 4 $ and $ 5 $ to $ 1 $ . That way, towns $ 0 $ and $ n + 1 $ don't get the signal from any tower, towns $ 1 $ , $ 2 $ and $ 3 $ get the signal from the tower in town $ 2 $ , town $ 4 $ gets the signal from the tower in town $ 4 $ , and town $ 5 $ gets the signal from the tower in town $ 5 $ .

Calculate the probability that, after building the towers, you will have a way to set signal powers to meet all constraints.

## 说明/提示

The real answer for the first example is $ \frac{1}{4} $ :

- with probability $ \frac{1}{4} $ , the towers are built in both towns $ 1 $ and $ 2 $ , so we can set their signal powers to $ 1 $ .

The real answer for the second example is $ \frac{1}{4} $ :

- with probability $ \frac{1}{8} $ , the towers are built in towns $ 1 $ , $ 2 $ and $ 3 $ , so we can set their signal powers to $ 1 $ ;
- with probability $ \frac{1}{8} $ , only one tower in town $ 2 $ is built, and we can set its signal power to $ 2 $ .

The real answer for the third example is $ \frac{5}{32} $ . Note that even though the previous explanations used equal signal powers for all towers, it is not necessarily so. For example, if $ n = 5 $ and the towers are built in towns $ 2 $ , $ 4 $ and $ 5 $ , you may set the signal power of the tower in town $ 2 $ to $ 2 $ , and the signal power of the towers in towns $ 4 $ and $ 5 $ to $ 1 $ .

## 样例 #1

### 输入

```
2```

### 输出

```
748683265```

## 样例 #2

### 输入

```
3```

### 输出

```
748683265```

## 样例 #3

### 输入

```
5```

### 输出

```
842268673```

## 样例 #4

### 输入

```
200000```

### 输出

```
202370013```

# AI分析结果

### 题目内容重写
#### 题目描述
在一条坐标线上有 $n + 2$ 个小镇，编号从 $0$ 到 $n + 1$。第 $i$ 个小镇位于坐标点 $i$。

你在每个小镇 $1, 2, \dots, n$ 上以概率 $\frac{1}{2}$ 建造一个无线电塔（这些事件是独立的）。之后，你需要为每个塔设置一个信号功率，信号功率为 $1$ 到 $n$ 之间的整数（信号功率不必相同，也不必不同）。位于小镇 $i$ 的塔的信号功率为 $p$ 时，信号将覆盖所有满足 $|c - i| < p$ 的小镇 $c$。

在建造塔之后，你需要选择信号功率，使得：
- 小镇 $0$ 和 $n + 1$ 不接收到任何信号；
- 小镇 $1, 2, \dots, n$ 每个小镇恰好接收到一个塔的信号。

例如，如果 $n = 5$，并且你在小镇 $2$、$4$ 和 $5$ 上建造了塔，你可以将小镇 $2$ 的塔的信号功率设置为 $2$，小镇 $4$ 和 $5$ 的塔的信号功率设置为 $1$。这样，小镇 $0$ 和 $n + 1$ 不会接收到任何信号，小镇 $1$、$2$ 和 $3$ 接收到来自小镇 $2$ 的塔的信号，小镇 $4$ 接收到来自小镇 $4$ 的塔的信号，小镇 $5$ 接收到来自小镇 $5$ 的塔的信号。

计算在建造塔之后，能够通过设置信号功率满足所有约束条件的概率。

#### 说明/提示
第一个样例的正确答案是 $\frac{1}{4}$：
- 以概率 $\frac{1}{4}$，塔被建造在小镇 $1$ 和 $2$ 上，因此我们可以将它们的信号功率设置为 $1$。

第二个样例的正确答案是 $\frac{1}{4}$：
- 以概率 $\frac{1}{8}$，塔被建造在小镇 $1$、$2$ 和 $3$ 上，因此我们可以将它们的信号功率设置为 $1$；
- 以概率 $\frac{1}{8}$，只有小镇 $2$ 上建造了塔，我们可以将其信号功率设置为 $2$。

第三个样例的正确答案是 $\frac{5}{32}$。注意，尽管之前的解释中所有塔的信号功率相同，但这并不一定是必须的。例如，如果 $n = 5$ 并且塔被建造在小镇 $2$、$4$ 和 $5$ 上，你可以将小镇 $2$ 的塔的信号功率设置为 $2$，小镇 $4$ 和 $5$ 的塔的信号功率设置为 $1$。

### 算法分类
动态规划、概率论

### 题解分析与结论
本题的核心在于计算满足条件的信号塔分布方案数，并将其除以总方案数 $2^n$。大多数题解都采用了动态规划的思路，通过递推或前缀和优化来计算方案数。部分题解还利用了斐波那契数列的性质来简化计算。

### 所选高分题解
#### 题解1：作者：ql12345 (评分：5星)
**关键亮点**：
- 使用动态规划递推计算方案数，并通过前缀和优化将时间复杂度降低到 $O(n)$。
- 代码简洁明了，逻辑清晰。

**核心代码**：
```cpp
for (int i = 3; i <= n; ++i) {
    if (i & 1) {
        a[i] = f[i - 1];
        s[i] = (s[i - 2] + a[i]) % P;
    } else {
        a[i] = s[i - 1];
        f[i] = (f[i - 2] + a[i]) % P;
    }
}
```
**实现思想**：通过奇偶性分开统计前缀和，优化动态规划的递推过程。

#### 题解2：作者：Oxide (评分：4星)
**关键亮点**：
- 利用斐波那契数列的性质简化了动态规划的递推公式，进一步优化了计算。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
for (int i = 3; i <= n; i++) {
    a = (a + b) % mod;
    swap(a, b);
}
```
**实现思想**：通过斐波那契数列的性质，直接递推计算方案数。

#### 题解3：作者：jiangtaizhe001 (评分：4星)
**关键亮点**：
- 使用动态规划递推计算方案数，并通过前缀和优化将时间复杂度降低到 $O(n)$。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
for (int i = 2; i <= n; i++) {
    f[i] = s[(i & 1) ^ 1];
    f[i] %= mod;
    s[i & 1] += f[i];
    s[i & 1] %= mod;
}
```
**实现思想**：通过奇偶性分开统计前缀和，优化动态规划的递推过程。

### 最优关键思路
- **动态规划递推**：通过递推公式计算方案数，利用前缀和优化降低时间复杂度。
- **斐波那契数列性质**：利用斐波那契数列的性质简化递推公式，进一步优化计算。

### 扩展思路
- 类似的问题可以通过动态规划和前缀和优化来解决，特别是在需要计算方案数或概率的情况下。
- 斐波那契数列的性质在递推问题中经常被用来简化计算。

### 推荐题目
1. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)

### 个人心得
- **调试经历**：在动态规划递推过程中，注意边界条件的处理，避免数组越界或初始值错误。
- **顿悟感想**：利用斐波那契数列的性质可以大大简化递推问题的计算，特别是在方案数计算中。

---
处理用时：49.28秒