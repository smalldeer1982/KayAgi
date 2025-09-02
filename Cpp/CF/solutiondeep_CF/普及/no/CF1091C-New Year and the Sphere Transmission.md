# 题目信息

# New Year and the Sphere Transmission

## 题目描述

There are $ n $ people sitting in a circle, numbered from $ 1 $ to $ n $ in the order in which they are seated. That is, for all $ i $ from $ 1 $ to $ n-1 $ , the people with id $ i $ and $ i+1 $ are adjacent. People with id $ n $ and $ 1 $ are adjacent as well.

The person with id $ 1 $ initially has a ball. He picks a positive integer $ k $ at most $ n $ , and passes the ball to his $ k $ -th neighbour in the direction of increasing ids, that person passes the ball to his $ k $ -th neighbour in the same direction, and so on until the person with the id $ 1 $ gets the ball back. When he gets it back, people do not pass the ball any more.

For instance, if $ n = 6 $ and $ k = 4 $ , the ball is passed in order $ [1, 5, 3, 1] $ .

Consider the set of all people that touched the ball. The fun value of the game is the sum of the ids of people that touched it. In the above example, the fun value would be $ 1 + 5 + 3 = 9 $ .

Find and report the set of possible fun values for all choices of positive integer $ k $ . It can be shown that under the constraints of the problem, the ball always gets back to the $ 1 $ -st player after finitely many steps, and there are no more than $ 10^5 $ possible fun values for given $ n $ .

## 说明/提示

In the first sample, we've already shown that picking $ k = 4 $ yields fun value $ 9 $ , as does $ k = 2 $ . Picking $ k = 6 $ results in fun value of $ 1 $ . For $ k = 3 $ we get fun value $ 5 $ and with $ k = 1 $ or $ k = 5 $ we get $ 21 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1091C/d99b7ec9698661c180178c4296e69ed6a8f083c5.png)In the second sample, the values $ 1 $ , $ 10 $ , $ 28 $ , $ 64 $ and $ 136 $ are achieved for instance for $ k = 16 $ , $ 8 $ , $ 4 $ , $ 10 $ and $ 11 $ , respectively.

## 样例 #1

### 输入

```
6
```

### 输出

```
1 5 9 21
```

## 样例 #2

### 输入

```
16
```

### 输出

```
1 10 28 64 136
```

# AI分析结果

【题目翻译】
# 新年和球的传递

## 题目描述

有 $n$ 个人围成一个圈，编号从 $1$ 到 $n$，按顺时针方向依次排列。也就是说，对于所有 $i$ 从 $1$ 到 $n-1$，编号为 $i$ 和 $i+1$ 的人是相邻的。编号为 $n$ 和 $1$ 的人也是相邻的。

编号为 $1$ 的人最初有一个球。他选择一个不超过 $n$ 的正整数 $k$，并将球传给他顺时针方向的第 $k$ 个邻居，那个人再将球传给他顺时针方向的第 $k$ 个邻居，依此类推，直到球回到编号为 $1$ 的人手中。当球回到 $1$ 时，游戏结束。

例如，如果 $n = 6$ 且 $k = 4$，则球的传递顺序为 $[1, 5, 3, 1]$。

考虑所有接触过球的人的集合。游戏的“乐趣值”是所有接触过球的人的编号之和。在上面的例子中，乐趣值为 $1 + 5 + 3 = 9$。

找到并报告所有可能的 $k$ 值对应的乐趣值集合。可以证明，在问题的约束下，球总是会在有限步数内回到第 $1$ 个人手中，且对于给定的 $n$，乐趣值的数量不超过 $10^5$。

## 说明/提示

在第一个样例中，我们已经展示了选择 $k = 4$ 和 $k = 2$ 时，乐趣值为 $9$。选择 $k = 6$ 时，乐趣值为 $1$。对于 $k = 3$，乐趣值为 $5$，而选择 $k = 1$ 或 $k = 5$ 时，乐趣值为 $21$。

在第二个样例中，$k = 16$、$8$、$4$、$10$ 和 $11$ 分别对应的乐趣值为 $1$、$10$、$28$、$64$ 和 $136$。

## 样例 #1

### 输入

```
6
```

### 输出

```
1 5 9 21
```

## 样例 #2

### 输入

```
16
```

### 输出

```
1 10 28 64 136
```

【算法分类】数学

【题解分析与结论】
该题的核心是通过枚举 $n$ 的因数，利用等差数列求和公式快速计算每个因数对应的乐趣值。所有题解都基于这一思路，但实现细节和代码风格有所不同。以下是几条评分较高的题解及其亮点。

【精选题解】
1. **作者：一扶苏一 (5星)**
   - **关键亮点**：通过裴蜀定理和同余方程推导出乐趣值的计算方式，代码简洁且高效，时间复杂度为 $O(\sqrt{n})$。
   - **代码核心**：
     ```cpp
     void work(cl s) {
         ll y = n / s;
         ll ans = (((s + y * s) * y) >> 1) + y - n;
         ss.insert(ans);
     }
     ```
   - **个人心得**：通过数学推导简化了问题，避免了复杂的模拟过程。

2. **作者：woshishei (4星)**
   - **关键亮点**：直接枚举 $n$ 的约数，并通过等差数列求和公式计算乐趣值，代码清晰易懂。
   - **代码核心**：
     ```cpp
     ans[++cnt] = (ll)(1 + n - i + 1) * (n / i) / 2;
     ```
   - **个人心得**：通过观察样例发现 $k$ 和 $n-k$ 的乐趣值相同，从而优化了枚举范围。

3. **作者：lahlah (4星)**
   - **关键亮点**：通过观察发现 $k$ 和 $gcd(k,n)$ 的关系，简化了问题，代码简洁且高效。
   - **代码核心**：
     ```cpp
     ans[++ sz] = (1 + n - x + 1) * n / x / 2;
     ```
   - **个人心得**：通过数学推导发现问题的本质，避免了不必要的计算。

【最优关键思路】
- **数学推导**：通过裴蜀定理和等差数列求和公式，快速计算每个因数对应的乐趣值，避免了复杂的模拟过程。
- **枚举优化**：只需枚举 $n$ 的因数，减少了计算量，时间复杂度为 $O(\sqrt{n})$。

【拓展思路】
- **类似问题**：可以扩展到其他与数论相关的传递问题，如模运算、循环节等。
- **算法套路**：在涉及循环和传递的问题中，考虑数学推导和因数分解，往往能简化问题。

【推荐题目】
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)
3. [P1069 细胞分裂](https://www.luogu.com.cn/problem/P1069)

---
处理用时：38.10秒