# 题目信息

# Minimum Triangulation

## 题目描述

You are given a regular polygon with $ n $ vertices labeled from $ 1 $ to $ n $ in counter-clockwise order. The triangulation of a given polygon is a set of triangles such that each vertex of each triangle is a vertex of the initial polygon, there is no pair of triangles such that their intersection has non-zero area, and the total area of all triangles is equal to the area of the given polygon. The weight of a triangulation is the sum of weigths of triangles it consists of, where the weight of a triagle is denoted as the product of labels of its vertices.

Calculate the minimum weight among all triangulations of the polygon.

## 说明/提示

According to Wiki: polygon triangulation is the decomposition of a polygonal area (simple polygon) $ P $ into a set of triangles, i. e., finding a set of triangles with pairwise non-intersecting interiors whose union is $ P $ .

In the first example the polygon is a triangle, so we don't need to cut it further, so the answer is $ 1 \cdot 2 \cdot 3 = 6 $ .

In the second example the polygon is a rectangle, so it should be divided into two triangles. It's optimal to cut it using diagonal $ 1-3 $ so answer is $ 1 \cdot 2 \cdot 3 + 1 \cdot 3 \cdot 4 = 6 + 12 = 18 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
```

### 输出

```
18
```

# AI分析结果

### 题目内容翻译
# 最小三角剖分

## 题目描述
给定一个有 $n$ 个顶点的正多边形，顶点按逆时针顺序从 $1$ 到 $n$ 编号。该多边形的三角剖分是一组三角形，使得每个三角形的每个顶点都是初始多边形的顶点，不存在一对三角形其交集的面积非零，且所有三角形的总面积等于给定多边形的面积。三角剖分的权重是其包含的三角形的权重之和，其中三角形的权重定义为其顶点编号的乘积。

计算该多边形所有三角剖分中的最小权重。

## 说明/提示
根据维基百科：多边形三角剖分是将多边形区域（简单多边形）$P$ 分解为一组三角形，即找到一组内部两两不相交且并集为 $P$ 的三角形。

在第一个样例中，多边形是一个三角形，所以不需要进一步分割，答案是 $1 \cdot 2 \cdot 3 = 6$。

在第二个样例中，多边形是一个矩形，所以应该将其分成两个三角形。最优的分割方式是使用对角线 $1 - 3$，所以答案是 $1 \cdot 2 \cdot 3 + 1 \cdot 3 \cdot 4 = 6 + 12 = 18$。

## 样例 #1
### 输入
```
3
```
### 输出
```
6
```

## 样例 #2
### 输入
```
4
```
### 输出
```
18
```

### 算法分类
动态规划、贪心、数学

### 综合分析与结论
本题主要是求正多边形三角剖分的最小权重，不同题解提供了多种思路和方法。
- **动态规划思路**：通过定义状态 $f_{i,j}$ 或 $dp_{i,j}$ 表示从 $i$ 逆时针到 $j$ 所需的最小权值，然后枚举割点 $k$ 进行状态转移，时间复杂度为 $O(n^3)$。这种方法具有一定的通用性，能处理输入权值的更复杂问题。
- **贪心思路**：观察发现让每条边的两个顶点都和 $1$ 连接能使权值最小，得到答案为 $\sum_{i=2}^{n - 1}i(i + 1)$，时间复杂度为 $O(n)$。
- **数学思路**：对贪心思路得到的式子进行变形，推导出 $\frac{(n - 1)n(n + 1)}{3}-2$，时间复杂度降为 $O(1)$。

### 所选题解
- **seanlsy（5星）**：
    - **关键亮点**：提供了动态规划、贪心和数学三种方法，思路清晰，代码规范，对每种方法的复杂度和适用性都有分析。
    - **重点代码**：
```cpp
// 动态规划
for(int i=n-2;i;i--)
    for(int j=i+2;j<=n;j++)
        for(int k=i+1;k<j;k++)
            f[i][j]=min(f[i][k]+f[k][j]+i*j*k,f[i][j]);
// 贪心
for(int i=2;i<=n-1;i++) 
    ans+=i*(i+1);
// 数学
printf("%lld\n",(n-1)*n*(n+1)/3-2);
```
- **da32s1da（4星）**：
    - **关键亮点**：通过比较不同连接方式的权值，推导出数学公式 $\frac{n^3 - n}{3}-2$，思路简洁明了。
    - **重点代码**：
```cpp
// 直接输出结果
cout<<(n*n*n-n)/3-2;
```
- **jbc392（4星）**：
    - **关键亮点**：思路与 da32s1da 类似，代码简洁，直接利用推导的公式求解。
    - **重点代码**：
```cpp
// 直接输出结果
cout<<(n*n*n-n)/3-2;
```

### 最优关键思路或技巧
- **动态规划**：定义合适的状态，通过枚举中间点进行状态转移，适用于更复杂的情况。
- **贪心**：通过观察和分析，找到使权值最小的连接方式，简化问题。
- **数学推导**：对贪心得到的式子进行数学变形，降低时间复杂度。

### 可拓展之处
同类型题可能会改变多边形的性质（如非正多边形）、顶点权值的计算方式等。类似算法套路包括在其他几何问题中运用动态规划、贪心和数学推导来优化求解过程。

### 推荐洛谷题目
1. [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)：区间动态规划问题，与本题的动态规划思路有相似之处。
2. [P2124 贪婪大陆](https://www.luogu.com.cn/problem/P2124)：涉及贪心算法的应用。
3. [P1044 栈](https://www.luogu.com.cn/problem/P1044)：可以通过数学推导得到递推公式，与本题的数学思路类似。

### 个人心得摘录与总结
- **Supor__Shoep**：在使用区间 DP 时发现运行速度较慢，于是采用打表的策略。总结：当算法复杂度较高时，打表可能是一种可行的优化方法，但适用范围有限。

---
处理用时：39.08秒