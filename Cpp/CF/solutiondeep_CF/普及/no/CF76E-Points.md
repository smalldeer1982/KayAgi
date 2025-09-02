# 题目信息

# Points

## 题目描述

You are given $ N $ points on a plane. Write a program which will find the sum of squares of distances between all pairs of points.

## 样例 #1

### 输入

```
4
1 1
-1 -1
1 -1
-1 1
```

### 输出

```
32
```

# AI分析结果



# Points

## 题目描述

给定平面上的 $N$ 个点，编写程序计算所有点对之间距离的平方和。

## 样例 #1

### 输入

```
4
1 1
-1 -1
1 -1
-1 1
```

### 输出

```
32
```

---

**算法分类**：数学

---

### 题解综合分析

本题核心在于将平方和公式展开，通过数学变形将 $O(n^2)$ 复杂度优化为 $O(n)$。各题解均采用以下核心思路：

1. **公式展开**：将 $\sum (x_i-x_j)^2$ 分解为 $(n-1)\sum x_i^2 - 2\sum x_i x_j$（y 同理）
2. **前缀和优化**：利用累加值实时计算交叉项 $\sum x_i x_j$，避免双重循环

---

### 精选题解（评分≥4星）

#### 1. 作者：Wenoide（5星）
**关键亮点**：
- 代码简洁高效，单次遍历同时维护累加值
- 直接在输入时计算贡献，无需存储坐标数组
- 正确处理数据类型溢出问题

**核心代码**：
```cpp
long long ans=0, sx=0, sy=0;
scanf("%d",&n);
for(int i=0;i<n;++i){
    int x,y;
    scanf("%d%d",&x,&y);
    ans += (n-1LL)*(x*x + y*y) - ((x*sx + y*sy)<<1);
    sx += x, sy += y;
}
printf("%lld\n",ans);
```
**实现思想**：实时维护坐标累加和 `sx`, `sy`，每个点的贡献由 `(n-1)*当前点平方值` 减去 `2*当前点与前缀和的乘积`。

#### 2. 作者：Buried_Dream（4星）
**关键亮点**：
- 预处理后缀和数组，直观展示交叉项计算
- 通过反向遍历构建后缀和，实现清晰的分项计算

**核心代码**：
```cpp
for(int i = n; i >= 1; i--) 
    hzx[i] = hzx[i+1] + x[i], hzy[i] = hzy[i+1] + y[i];
for(int i = 1; i <= n; i++)
    ans -= 2*(x[i]*hzx[i+1] + y[i]*hzy[i+1]);
```
**实现思想**：预处理后缀和数组 `hzx`, `hzy`，每个点与后续所有点的乘积和可通过后缀和快速计算。

---

### 最优关键技巧
- **数学展开式变形**：将平方距离转换为独立项与交叉项的组合
- **前缀和/后缀和优化**：将 $O(n^2)$ 的交叉项计算转化为 $O(n)$ 的线性计算
- **实时累加策略**：在输入时同步计算各项贡献，减少空间占用

---

### 拓展应用
同类问题可使用类似数学优化方法：
1. 方差计算：$\sum (x_i-\mu)^2 = \sum x_i^2 - n\mu^2$
2. 向量点积求和：$\sum_{i<j} \vec{v_i} \cdot \vec{v_j}$
3. 多维空间距离计算（扩展至三维或更高维度）

---

### 推荐题目
1. [CF1721C - Min-Max Array Transformation](https://www.luogu.com.cn/problem/CF1721C)（数学推导优化）
2. [P2181 对角线](https://www.luogu.com.cn/problem/P2181)（组合数学）
3. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)（前缀和与数学变形）

---
处理用时：71.99秒