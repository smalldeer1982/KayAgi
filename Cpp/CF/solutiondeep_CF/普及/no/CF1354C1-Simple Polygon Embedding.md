# 题目信息

# Simple Polygon Embedding

## 题目描述

The statement of this problem is the same as the statement of problem C2. The only difference is that, in problem C1, $ n $ is always even, and in C2, $ n $ is always odd.

You are given a regular polygon with $ 2 \cdot n $ vertices (it's convex and has equal sides and equal angles) and all its sides have length $ 1 $ . Let's name it as $ 2n $ -gon.

Your task is to find the square of the minimum size such that you can embed $ 2n $ -gon in the square. Embedding $ 2n $ -gon in the square means that you need to place $ 2n $ -gon in the square in such way that each point which lies inside or on a border of $ 2n $ -gon should also lie inside or on a border of the square.

You can rotate $ 2n $ -gon and/or the square.

## 样例 #1

### 输入

```
3
2
4
200```

### 输出

```
1.000000000
2.414213562
127.321336469```

# AI分析结果

### 题目内容重写
# 简单多边形嵌入

## 题目描述

这道题的描述与问题C2相同。唯一的区别是，在问题C1中，$n$总是偶数，而在C2中，$n$总是奇数。

给定一个具有$2 \cdot n$个顶点的正多边形（它是凸的，且边长和角度都相等），所有边的长度均为$1$。我们将其命名为$2n$-边形。

你的任务是找到一个最小尺寸的正方形，使得可以将$2n$-边形嵌入到该正方形中。将$2n$-边形嵌入到正方形中意味着你需要将$2n$-边形放置在正方形中，使得$2n$-边形内部或边界上的每个点也位于正方形内部或边界上。

你可以旋转$2n$-边形和/或正方形。

## 样例 #1

### 输入

```
3
2
4
200```

### 输出

```
1.000000000
2.414213562
127.321336469```

### 算法分类
数学

### 题解分析与结论
这道题的核心在于通过数学推导找到正$2n$-边形的最小外接正方形的边长。所有题解都基于几何和三角函数的性质，通过不同的角度和公式推导出最终答案。

### 精选题解
1. **作者：皎月半洒花 (赞：18)**  
   - **星级：5**  
   - **关键亮点**：通过积化和差公式和三角函数的性质，推导出简洁的数学表达式，最终得到答案。思路清晰，数学推导严谨。  
   - **核心代码**：
     ```cpp
     double t = pi / n;
     printf("%.12lf\n", (double)1 / tan(t));
     ```

2. **作者：囧仙 (赞：2)**  
   - **星级：4**  
   - **关键亮点**：通过几何图形的分析，结合正多边形的性质，推导出最小外接正方形的边长。思路直观，易于理解。  
   - **核心代码**：
     ```cpp
     double t = pi / n;
     printf("%.12lf\n", (double)1 / tan(t));
     ```

3. **作者：To_Carpe_Diem (赞：1)**  
   - **星级：4**  
   - **关键亮点**：通过正多边形的外接圆半径推导出最小正方形的边长，思路简洁，代码实现清晰。  
   - **核心代码**：
     ```cpp
     double sh = 1.0 / tan(M_PI / (2.0 * n));
     cout << fixed;
     cout.precision(9);
     cout << sh << "\n";
     ```

### 最优关键思路
通过正多边形的几何性质和三角函数的推导，利用`cot`函数（即`1/tan`）直接计算出最小外接正方形的边长。这种方法简洁高效，避免了复杂的几何分析。

### 可拓展之处
类似的问题可以扩展到其他正多边形的外接矩形或圆的求解，或者扩展到三维空间中的正多面体的外接立方体等。

### 推荐题目
1. [P1354 正多边形外接圆](https://www.luogu.com.cn/problem/P1354)
2. [P1355 正多边形内切圆](https://www.luogu.com.cn/problem/P1355)
3. [P1356 正多边形面积](https://www.luogu.com.cn/problem/P1356)

---
处理用时：21.58秒