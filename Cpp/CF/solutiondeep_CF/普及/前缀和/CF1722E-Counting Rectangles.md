# 题目信息

# Counting Rectangles

## 题目描述

You have $ n $ rectangles, the $ i $ -th rectangle has height $ h_i $ and width $ w_i $ .

You are asked $ q $ queries of the form $ h_s \ w_s \ h_b \ w_b $ .

For each query output, the total area of rectangles you own that can fit a rectangle of height $ h_s $ and width $ w_s $ while also fitting in a rectangle of height $ h_b $ and width $ w_b $ . In other words, print $ \sum h_i \cdot w_i $ for $ i $ such that $ h_s < h_i < h_b $ and $ w_s < w_i < w_b $ .

Please note, that if two rectangles have the same height or the same width, then they cannot fit inside each other. Also note that you cannot rotate rectangles.

Please note that the answer for some test cases won't fit into 32-bit integer type, so you should use at least 64-bit integer type in your programming language (like long long for C++).

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1722E/eea41631a59a3be709b240003a8697e693220564.png)In the first test case, there is only one query. We need to find the sum of areas of all rectangles that can fit a $ 1 \times 1 $ rectangle inside of it and fit into a $ 3 \times 4 $ rectangle.

Only the $ 2 \times 3 $ rectangle works, because $ 1 < 2 $ (comparing heights) and $ 1 < 3 $ (comparing widths), so the $ 1 \times 1 $ rectangle fits inside, and $ 2 < 3 $ (comparing heights) and $ 3 < 4 $ (comparing widths), so it fits inside the $ 3 \times 4 $ rectangle. The $ 3 \times 2 $ rectangle is too tall to fit in a $ 3 \times 4 $ rectangle. The total area is $ 2 \cdot 3 = 6 $ .

## 样例 #1

### 输入

```
3
2 1
2 3
3 2
1 1 3 4
5 5
1 1
2 2
3 3
4 4
5 5
3 3 6 6
2 1 4 5
1 1 2 10
1 1 100 100
1 1 3 3
3 1
999 999
999 999
999 998
1 1 1000 1000```

### 输出

```
6
41
9
0
54
4
2993004```

# AI分析结果

### 题目内容重写

你有 $n$ 个矩形，第 $i$ 个矩形的高度为 $h_i$，宽度为 $w_i$。你需要回答 $q$ 个查询，每个查询给出四个整数 $h_s, w_s, h_b, w_b$。对于每个查询，输出满足 $h_s < h_i < h_b$ 且 $w_s < w_i < w_b$ 的所有矩形的面积之和。注意，如果两个矩形的高度或宽度相同，则它们不能相互嵌套。同时，矩形不能旋转。

### 题解分析与结论

#### 综合分析与结论
本题的核心在于如何高效地处理多个查询，要求统计满足特定条件的矩形面积之和。由于矩形的尺寸范围较小（$h_i, w_i \leq 1000$），因此可以通过预处理二维前缀和或使用树状数组等数据结构来优化查询效率。大多数题解采用了二维前缀和的思路，能够在 $O(1)$ 时间内回答每个查询，整体时间复杂度为 $O(n + q)$。

#### 精选题解

1. **题解作者：ScottSuperb (赞：17)**
   - **星级：5星**
   - **关键亮点**：使用二维前缀和，代码简洁高效，预处理和查询的时间复杂度均为 $O(1)$，适合大规模数据。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= 1000; ++i)
         for (int j = 1; j <= 1000; ++j)
             s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
     ```
     **实现思想**：通过二维前缀和预处理，查询时直接通过差分公式计算矩形区域内的面积和。

2. **题解作者：Lantrol (赞：5)**
   - **星级：4星**
   - **关键亮点**：同样使用二维前缀和，代码清晰，处理多组数据时手动清零，避免了 `memset` 的性能问题。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= 1000; i++)
         for (int j = 1; j <= 1000; j++)
             d[i][j] = d[i][j] + d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1];
     ```
     **实现思想**：通过二维前缀和预处理，查询时直接通过差分公式计算矩形区域内的面积和。

3. **题解作者：zsseg (赞：0)**
   - **星级：4星**
   - **关键亮点**：使用一维前缀和优化，将复杂度从 $O(qhw)$ 降低到 $O(nw + qh)$，适合中等规模数据。
   - **核心代码**：
     ```cpp
     f(i,1,n){
         h[i]=read(),w[i]=read();
         f(j,w[i],1000)a[h[i]][j]+=h[i]*w[i];
     }
     ```
     **实现思想**：通过一维前缀和预处理，查询时通过累加每行的前缀和来得到矩形区域内的面积和。

#### 最优关键思路或技巧
- **二维前缀和**：通过预处理二维前缀和，能够在 $O(1)$ 时间内回答每个查询，适用于大规模数据。
- **一维前缀和优化**：通过一维前缀和优化，将复杂度从 $O(qhw)$ 降低到 $O(nw + qh)$，适合中等规模数据。

#### 可拓展之处
- **类似算法套路**：二维前缀和和树状数组等数据结构在处理二维区间查询问题时非常有用，可以拓展到其他类似问题，如矩阵求和、区间统计等。
- **同类型题推荐**：
  1. [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)
  2. [P2004 领地选择](https://www.luogu.com.cn/problem/P2004)
  3. [P3397 地毯](https://www.luogu.com.cn/problem/P3397)

#### 个人心得摘录
- **调试经历**：部分题解提到在调试过程中发现数组开小导致的问题，提醒我们在处理大规模数据时要注意数组大小。
- **踩坑教训**：使用 `memset` 清零时可能会影响性能，手动清零是更好的选择。
- **顿悟感想**：通过二维前缀和的预处理，能够将复杂的区间查询问题简化为简单的差分计算，大大提高了效率。

---
处理用时：36.61秒