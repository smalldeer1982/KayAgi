# 题目信息

# Cherry

## 题目描述

You are given $ n $ integers $ a_1, a_2, \ldots, a_n $ . Find the maximum value of $ max(a_l, a_{l + 1}, \ldots, a_r) \cdot min(a_l, a_{l + 1}, \ldots, a_r) $ over all pairs $ (l, r) $ of integers for which $ 1 \le l < r \le n $ .

## 说明/提示

Let $ f(l, r) = max(a_l, a_{l + 1}, \ldots, a_r) \cdot min(a_l, a_{l + 1}, \ldots, a_r) $ .

In the first test case,

- $ f(1, 2) = max(a_1, a_2) \cdot min(a_1, a_2) = max(2, 4) \cdot min(2, 4) = 4 \cdot 2 = 8 $ .
- $ f(1, 3) = max(a_1, a_2, a_3) \cdot min(a_1, a_2, a_3) = max(2, 4, 3) \cdot min(2, 4, 3) = 4 \cdot 2 = 8 $ .
- $ f(2, 3) = max(a_2, a_3) \cdot min(a_2, a_3) = max(4, 3) \cdot min(4, 3) = 4 \cdot 3 = 12 $ .

So the maximum is $ f(2, 3) = 12 $ .

In the second test case, the maximum is $ f(1, 2) = f(1, 3) = f(2, 3) = 6 $ .

## 样例 #1

### 输入

```
4
3
2 4 3
4
3 2 3 1
2
69 69
6
719313 273225 402638 473783 804745 323328```

### 输出

```
12
6
4761
381274500335```

# AI分析结果

### 题目内容
# Cherry

## 题目描述
给定$n$个整数$a_1, a_2, \ldots, a_n$ 。在所有满足$1 \le l < r \le n$的整数对$(l, r)$中，找出$ \max(a_l, a_{l + 1}, \ldots, a_r) \cdot \min(a_l, a_{l + 1}, \ldots, a_r)$的最大值。

## 说明/提示
设$f(l, r) = \max(a_l, a_{l + 1}, \ldots, a_r) \cdot \min(a_l, a_{l + 1}, \ldots, a_r)$ 。

在第一个测试用例中：
 - $f(1, 2) = \max(a_1, a_2) \cdot \min(a_1, a_2) = \max(2, 4) \cdot \min(2, 4) = 4 \cdot 2 = 8$ 。
 - $f(1, 3) = \max(a_1, a_2, a_3) \cdot \min(a_1, a_2, a_3) = \max(2, 4, 3) \cdot \min(2, 4, 3) = 4 \cdot 2 = 8$ 。
 - $f(2, 3) = \max(a_2, a_3) \cdot \min(a_2, a_3) = \max(4, 3) \cdot \min(4, 3) = 4 \cdot 3 = 12$ 。

所以最大值是$f(2, 3) = 12$ 。

在第二个测试用例中，最大值是$f(1, 2) = f(1, 3) = f(2, 3) = 6$ 。

## 样例 #1
### 输入
```
4
3
2 4 3
4
3 2 3 1
2
69 69
6
719313 273225 402638 473783 804745 323328
```
### 输出
```
12
6
4761
381274500335
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是通过贪心策略，证明只需考虑相邻两个数的乘积就能得到最大值。难点在于证明为什么只考虑相邻两个数的乘积即可，不同题解从不同角度进行了论证。例如，有的题解从添加新元素对最值乘积影响的角度分析，有的通过分类讨论三个数的情况来推导。算法要点是遍历相邻数对并计算其乘积，找出最大值。

### 通用建议与扩展思路
对于此类问题，关键在于理解贪心策略的正确性，即为什么扩大区间不会使结果更优。可以进一步思考如果题目条件改变，如求最小值、改变区间限制等，解法会如何变化。同类型题通常围绕区间最值的某种运算结果的最值问题，解题思路往往是通过分析区间变化对结果的影响，找到最优子结构或贪心策略。

### 相似知识点洛谷题目
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过分析相邻元素交换对结果的影响，运用贪心策略解题。
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据接水时间的长短进行贪心排序，以得到最优的总等待时间。
3. [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过比较不同包装铅笔的单价，采用贪心策略选择最优购买方案。 

---
处理用时：25.23秒