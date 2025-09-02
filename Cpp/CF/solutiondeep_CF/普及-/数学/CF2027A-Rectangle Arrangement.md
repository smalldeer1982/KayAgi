# 题目信息

# Rectangle Arrangement

## 题目描述

You are coloring an infinite square grid, in which all cells are initially white. To do this, you are given $ n $ stamps. Each stamp is a rectangle of width $ w_i $ and height $ h_i $ .

You will use each stamp exactly once to color a rectangle of the same size as the stamp on the grid in black. You cannot rotate the stamp, and for each cell, the stamp must either cover it fully or not cover it at all. You can use the stamp at any position on the grid, even if some or all of the cells covered by the stamping area are already black.

What is the minimum sum of the perimeters of the connected regions of black squares you can obtain after all the stamps have been used?

## 说明/提示

In the first test case, the stamps can be used as shown on the left. Each stamp is highlighted in its own color for clarity.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2027A/eb6eb9753bb0b7d5590d43612099263639e3e940.png)After all these stamps are used, there is one black region (as shown on the right), and its perimeter is $ 20 $ . It can be shown that there is no way of using the stamps that yields a lower total perimeter.

In the second test case, the second and third stamps can be used entirely inside the first one, so the minimum perimeter is equal to $ 8 $ .

## 样例 #1

### 输入

```
5
5
1 5
2 4
3 3
4 2
5 1
3
2 2
1 1
1 2
1
3 2
3
100 100
100 100
100 100
4
1 4
2 3
1 5
3 2```

### 输出

```
20
8
10
400
16```

# AI分析结果

### 题目内容翻译

#### 矩形排列

##### 题目描述

你正在为一个无限大的正方形网格着色，所有单元格最初都是白色的。为此，你得到了 $ n $ 个印章。每个印章是一个宽度为 $ w_i $、高度为 $ h_i $ 的矩形。

你将使用每个印章一次，在网格上以与印章相同大小的矩形区域涂黑。你不能旋转印章，并且对于每个单元格，印章必须完全覆盖它或不覆盖它。你可以在网格上的任何位置使用印章，即使印章覆盖的区域中的一些或所有单元格已经被涂黑。

在所有印章使用完毕后，你能得到的所有黑色区域的连通区域的最小周长总和是多少？

##### 说明/提示

在第一个测试用例中，印章可以按照左边的方式使用。每个印章用不同的颜色高亮显示以便清晰。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2027A/eb6eb9753bb0b7d5590d43612099263639e3e940.png) 在使用完所有这些印章后，有一个黑色区域（如右边所示），其周长为 $ 20 $。可以证明，没有其他使用印章的方式可以得到更小的总周长。

在第二个测试用例中，第二个和第三个印章可以完全在第一个印章内部使用，因此最小周长等于 $ 8 $。

##### 样例 #1

###### 输入

```
5
5
1 5
2 4
3 3
4 2
5 1
3
2 2
1 1
1 2
1
3 2
3
100 100
100 100
100 100
4
1 4
2 3
1 5
3 2
```

###### 输出

```
20
8
10
400
16
```

### 题解分析与结论

由于目前没有提供具体的题解，我将根据题目描述和常见算法思路进行分析。

#### 关键思路与技巧

1. **问题转化**：题目要求最小化所有黑色连通区域的周长总和。这可以转化为如何将多个矩形尽可能重叠，以减少总的周长。
2. **贪心策略**：一种可能的策略是尽可能将较小的矩形放在较大的矩形内部，以减少新增的周长。
3. **动态规划**：可以考虑使用动态规划来计算不同排列方式下的最小周长，但由于矩形的排列组合较多，这种方法可能不够高效。
4. **几何优化**：利用几何性质，如矩形的重叠面积最大化，可以进一步优化周长的计算。

#### 通用建议与扩展思路

- **模拟与验证**：可以通过模拟不同排列方式，计算每种情况下的总周长，选择最小的一个。
- **数学建模**：尝试将问题转化为数学优化问题，寻找最优解。
- **分治策略**：将大问题分解为小问题，逐步求解。

#### 推荐题目

1. **洛谷 P1880 [NOI1995]石子合并** - 考察动态规划与区间合并。
2. **洛谷 P1048 采药** - 考察背包问题与动态规划。
3. **洛谷 P1064 金明的预算方案** - 考察依赖背包问题与动态规划。

### 结论

由于目前没有具体的题解，建议尝试上述关键思路与技巧，结合模拟与验证的方法，逐步优化解决方案。

---
处理用时：28.69秒