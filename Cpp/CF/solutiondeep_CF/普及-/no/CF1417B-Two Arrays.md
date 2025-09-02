# 题目信息

# Two Arrays

## 题目描述

RedDreamer has an array $ a $ consisting of $ n $ non-negative integers, and an unlucky integer $ T $ .

Let's denote the misfortune of array $ b $ having length $ m $ as $ f(b) $ — the number of pairs of integers $ (i, j) $ such that $ 1 \le i < j \le m $ and $ b_i + b_j = T $ . RedDreamer has to paint each element of $ a $ into one of two colors, white and black (for each element, the color is chosen independently), and then create two arrays $ c $ and $ d $ so that all white elements belong to $ c $ , and all black elements belong to $ d $ (it is possible that one of these two arrays becomes empty). RedDreamer wants to paint the elements in such a way that $ f(c) + f(d) $ is minimum possible.

For example:

- if $ n = 6 $ , $ T = 7 $ and $ a = [1, 2, 3, 4, 5, 6] $ , it is possible to paint the $ 1 $ -st, the $ 4 $ -th and the $ 5 $ -th elements white, and all other elements black. So $ c = [1, 4, 5] $ , $ d = [2, 3, 6] $ , and $ f(c) + f(d) = 0 + 0 = 0 $ ;
- if $ n = 3 $ , $ T = 6 $ and $ a = [3, 3, 3] $ , it is possible to paint the $ 1 $ -st element white, and all other elements black. So $ c = [3] $ , $ d = [3, 3] $ , and $ f(c) + f(d) = 0 + 1 = 1 $ .

Help RedDreamer to paint the array optimally!

## 样例 #1

### 输入

```
2
6 7
1 2 3 4 5 6
3 6
3 3 3```

### 输出

```
1 0 0 1 1 0 
1 0 0```

# AI分析结果

### 题目内容
#### Two Arrays
1. **题目描述**：RedDreamer 有一个由 $n$ 个非负整数组成的数组 $a$ ，以及一个不吉利的整数 $T$ 。
    - 定义长度为 $m$ 的数组 $b$ 的不幸程度 $f(b)$ 为满足 $1 \leq i < j \leq m$ 且 $b_i + b_j = T$ 的整数对 $(i, j)$ 的数量。RedDreamer 必须将 $a$ 的每个元素涂成两种颜色之一，白色和黑色（对于每个元素，颜色是独立选择的），然后创建两个数组 $c$ 和 $d$ ，使得所有白色元素属于 $c$ ，所有黑色元素属于 $d$ （这两个数组中的一个可能为空）。RedDreamer 希望以这样一种方式给元素涂色，使得 $f(c) + f(d)$ 尽可能小。
    - 例如：
        - 如果 $n = 6$ ，$T = 7$ 且 $a = [1, 2, 3, 4, 5, 6]$ ，可以将第 $1$ 、第 $4$ 和第 $5$ 个元素涂成白色，所有其他元素涂成黑色。所以 $c = [1, 4, 5]$ ，$d = [2, 3, 6]$ ，并且 $f(c) + f(d) = 0 + 0 = 0$ ；
        - 如果 $n = 3$ ，$T = 6$ 且 $a = [3, 3, 3]$ ，可以将第 $1$ 个元素涂成白色，所有其他元素涂成黑色。所以 $c = [3]$ ，$d = [3, 3]$ ，并且 $f(c) + f(d) = 0 + 1 = 1$ 。
    - 帮助 RedDreamer 以最优方式给数组涂色！
2. **样例 #1**
    - **输入**：
```
2
6 7
1 2 3 4 5 6
3 6
3 3 3
```
    - **输出**：
```
1 0 0 1 1 0 
1 0 0
```

### 算法分类
构造

### 综合分析与结论
所有题解思路核心一致，均基于对满足 \(a_i + a_j = T\) 情况的分析来构造分组。要点为将小于 \(\frac{T}{2}\) 的数放入一个集合，大于 \(\frac{T}{2}\) 的数放入另一个集合，等于 \(\frac{T}{2}\) 的数平均分配到两个集合。难点在于理解为何这样分组能使 \(f(c) + f(d)\) 最小，以及如何实现等于 \(\frac{T}{2}\) 的数的平均分配。各题解在实现方式上略有不同，部分使用数组存储数据，部分直接输出结果，还有部分使用了 `map` 等数据结构。但整体思路和核心算法一致。

### 通用建议与扩展思路
对于此类构造类型题目，关键在于深入分析题目条件，找到符合要求的构造规律。在实现时，注意边界情况处理和代码的简洁性与可读性。同类型题可考虑其他基于条件构造分组或排列的问题，类似套路为从条件出发，分析满足目标的元素分布特点，进而构造出解决方案。

### 洛谷相似题目推荐
1. P1036 [选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合数并判断是否为质数，与本题分析条件构造方案有相似思考过程。
2. P1157 组合的输出：考查组合相关知识，与本题在构造满足条件的组合上思路类似。
3. P1433 吃奶酪：需要通过分析距离等条件构造出最优路径，和本题分析条件进行构造的思维方式相近。 

---
处理用时：28.40秒