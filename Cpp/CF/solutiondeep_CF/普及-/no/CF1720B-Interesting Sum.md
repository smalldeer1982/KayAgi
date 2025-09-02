# 题目信息

# Interesting Sum

## 题目描述

You are given an array $ a $ that contains $ n $ integers. You can choose any proper subsegment $ a_l, a_{l + 1}, \ldots, a_r $ of this array, meaning you can choose any two integers $ 1 \le l \le r \le n $ , where $ r - l + 1 < n $ . We define the beauty of a given subsegment as the value of the following expression:

$$\max(a_{1}, a_{2}, \ldots, a_{l-1}, a_{r+1}, a_{r+2}, \ldots, a_{n}) - \min(a_{1}, a_{2}, \ldots, a_{l-1}, a_{r+1}, a_{r+2}, \ldots, a_{n}) + \max(a_{l}, \ldots, a_{r}) - \min(a_{l}, \ldots, a_{r}). $$

Please find the maximum beauty among all proper subsegments.

## 说明/提示

In the first test case, the optimal segment is $ l = 7 $ , $ r = 8 $ . The beauty of this segment equals to $ (6 - 1) + (5 - 1) = 9 $ .

In the second test case, the optimal segment is $ l = 2 $ , $ r = 4 $ . The beauty of this segment equals $ (100 - 2) + (200 - 1) = 297 $ .

## 样例 #1

### 输入

```
4
8
1 2 2 3 1 5 6 1
5
1 2 3 100 200
4
3 3 3 3
6
7 8 3 1 1 8```

### 输出

```
9
297
0
14```

# AI分析结果

### 题目内容
# 有趣的和

## 题目描述
给定一个包含 $n$ 个整数的数组 $a$ 。你可以选择该数组的任意一个真子段 $a_l, a_{l + 1}, \ldots, a_r$ ，即可以选择任意两个整数 $1 \le l \le r \le n$ ，其中 $r - l + 1 < n$ 。我们将给定子段的「美丽值」定义为以下表达式的值：

$$\max(a_{1}, a_{2}, \ldots, a_{l - 1}, a_{r + 1}, a_{r + 2}, \ldots, a_{n}) - \min(a_{1}, a_{2}, \ldots, a_{l - 1}, a_{r + 1}, a_{r + 2}, \ldots, a_{n}) + \max(a_{l}, \ldots, a_{r}) - \min(a_{l}, \ldots, a_{r})$$

请找出所有真子段中的最大美丽值。

## 说明/提示
在第一个测试用例中，最优子段为 $l = 7$ ，$r = 8$ 。该子段的美丽值等于 $(6 - 1) + (5 - 1) = 9$ 。

在第二个测试用例中，最优子段为 $l = 2$ ，$r = 4$ 。该子段的美丽值等于 $(100 - 2) + (200 - 1) = 297$ 。

## 样例 #1
### 输入
```
4
8
1 2 2 3 1 5 6 1
5
1 2 3 100 200
4
3 3 3 3
6
7 8 3 1 1 8
```
### 输出
```
9
297
0
14
```
### 算法分类
数学

### 题解综合分析与结论
所有题解核心思路均为通过分析发现最大美丽值等于数组中的最大值与次大值之和减去最小值与次小值之和。各题解通过不同方式证明该结论，如枚举各种排列情况、分类讨论等。实现上，部分题解采用排序获取最值，部分通过打擂法在线性时间内找出最值。解决难点在于证明为何最大美丽值是这四个值的特定运算结果。

### 所选的题解
- **作者：Hisaishi_Kanade (5星)**
  - **关键亮点**：思路清晰，先指出暴力做法的时间复杂度不可行，再通过枚举最大、次大、最小、次小这四个数的排列情况，证明一定能将这四个值分成符合条件的两组，得出最优的 $O(n)$ 做法。
  - **重点代码**：无具体代码，核心思路为找出最大、次大、最小、次小值，输出 $a + b - c - d$。
- **作者：wzmzmhk (4星)**
  - **关键亮点**：简洁阐述思路，通过观察发现四个数无论如何排列都能找到满足条件的 $[l, r]$ 区间，进而得出答案为 $a + b - c - d$，并给出打擂法找最值的代码。
  - **重点代码**：
```cpp
for (int i = 1; i <= n; i++) {
    if (a[i] >= Max) Max = a[i], I = i;
    if (a[i] <= Min) Min = a[i], J = i;
}
int nMax = -INF, nMin = INF;
for (int i = 1; i <= n; i++) {
    if (i!= I && a[i] >= nMax) nMax = a[i];
    if (i!= J && a[i] <= nMin) nMin = a[i];
}
cout << Max + nMax - Min - nMin << endl;
```
核心实现思想：通过两轮遍历，第一轮找出最大值及其下标、最小值及其下标，第二轮在排除最大值和最小值的位置后找出次大值和次小值，最后输出计算结果。
- **作者：CSP_Sept (4星)**
  - **关键亮点**：详细证明答案必定为 $\mathscr A+\mathscr S - s - t$，分三种情况讨论并证明，逻辑严谨。
  - **重点代码**：无具体代码，核心思路为排序后输出 $a_n + a_{n - 1} - a_1 - a_2$。

### 最优关键思路或技巧
通过对问题深入分析，发现答案只与数组中的最大、次大、最小、次小值有关，避免了复杂的数据结构和暴力枚举区间的方法，大大降低时间复杂度。

### 拓展
同类型题常围绕数组元素的最值组合与区间运算展开，类似套路是通过分析题目所求表达式，找出对结果起关键作用的特殊值（如最值、次最值等），从而简化计算。

### 洛谷相似题目推荐
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：涉及对数列的分段处理与最值分析。
- [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)：通过二分答案结合对数组元素的分析解决问题，与本题分析关键值思路类似。
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：在处理数组元素关系时，通过特定算法（归并排序）统计逆序对，与本题分析数组元素间关系有相似之处。

### 个人心得摘录与总结
部分作者提到乍看题目可能会想用线段树等复杂数据结构，但分析后发现有更简单的数学规律。这表明面对问题不能仅从常规思路出发，要深入分析问题本质，挖掘隐藏的数学关系来简化问题。 

---
处理用时：41.31秒