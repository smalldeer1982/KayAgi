# 题目信息

# [USACO11MAR] Bovine Bridge Battle S

## 题目背景

给定N（4 <= N <= 1,000）个整点的坐标 (-1,000,000,000 <= X\_i <= 1,000,000,000; -1,000,000,000 <= Y\_i <= 1,000,000,000，X\_i，Y\_i∈Z)，求card{{(X\_a,Y\_a),(X\_b,Y\_b),(X\_c,Y\_c),(X\_d,Y\_d)}|四点呈中心对称}


## 题目描述

Each of Farmer John's N (4 <= N <= 1,000) cows is patiently waiting in the main pasture with cow i at point with integer coordinates (X\_i, Y\_i) (-1,000,000,000 <= X\_i <= 1,000,000,000; -1,000,000,000 <= Y\_i <= 1,000,000,000).

The cows wish to form into groups of four in order to play Bridge, their new favorite card game. Each group must satisfy an important constraint: four cows are allowed to team up if and only if there exists some point X somewhere in the plane (and not coincident with any of the four points of the potential group of four) such that rotating any of the group's cows 180 degrees about that point X gives the position of some other cow in the group.

Please help the cows determine the number of sets of four cows that can form a Bridge group.

By way of example, suppose eight cows are standing at eight points:

|
f\*
```cpp
|             a = (-3, 1)    e = (-1, 1) 
b*     |             b = (-2, 2)    f = ( 0, 3) 
a      e  |             c = (-3, 0)    g = ( 2, 0) 
*     *  |             d = (-2, 0)    h = ( 3, 0) 
```
c  d     |     g  h
---------\*--\*-----+-----\*--\*---------

|
Then the three legal sets of four cows are {a, b, e, d} (they rotate around point (-2, 1)), {b, c, e, f} (around the point (-1.5, 1.5)), and {c, d, g, h} (around (0,0)).

The supplied locations of the cows given are all distinct, although they are supplied in no particular order. Furthermore, the answer will fit into a signed 32-bit integer.


## 样例 #1

### 输入

```
8 
-3 0 
-2 0 
-1 1 
0 3 
2 0 
-3 1 
3 0 
-2 2 
```

### 输出

```
3 
```

# AI分析结果



### 算法分类
**组合数学**

---

### 综合分析与结论
题目核心是统计四个点中心对称的组合数。所有题解均基于以下数学观察：四个点中心对称等价于存在两对点的坐标和相等。通过统计所有点对的坐标和，并计算相同和的组合数，最终用组合数公式求得答案。优化方向集中在哈希结构的选择（map vs unordered_map vs 手写哈希）及坐标编码技巧。

---

### 精选题解

#### 1. feecle6418 的题解（⭐⭐⭐⭐⭐）
**关键亮点**  
- 数学建模：将中心对称转化为坐标和相等的组合问题  
- 优化策略：提出用哈希表替代map、坐标压缩技巧（将坐标和转为long long存储）  
- 复杂度分析：明确时间复杂度从O(n² logn)优化到O(n²)  
- 代码实现：使用`gp_hash_table`提升效率，避免浮点运算  
**核心代码**  
```cpp
gp_hash_table<long long,int> p;
for(int i=1;i<n;i++) 
    for(int j=i+1;j<=n;j++) 
        p[((long long)x[i]+x[j])*2147400000ll+(y[i]+y[j])]++;
// 统计相同坐标和的组合数
```

#### 2. __Creeper__ 的题解（⭐⭐⭐⭐）  
**关键亮点**  
- 简洁的数学推导：直接通过坐标和相等推导平行四边形的性质  
- 代码简洁性：仅用20行代码实现核心逻辑，可读性强  
**核心代码**  
```cpp
map<pair<int,int>,int> mp;
for(int i=1;i<=n;i++) 
    for(int j=i+1;j<=n;j++) 
        mp[{x[i]+x[j], y[i]+y[j]}]++;
// 利用pair直接存储坐标和
```

#### 3. 4041nofoundGeoge 的题解（⭐⭐⭐）  
**关键亮点**  
- 几何图示辅助理解：通过平行四边形示意图增强直观性  
- 强调去重逻辑：明确说明最后除以2的必要性  
**个人心得**  
> "不去重爆0分，去重100分" —— 提醒注意重复计数问题

---

### 关键思路总结
1. **数学建模**：将中心对称问题转化为坐标和相等的组合计数问题（利用平行四边形性质）  
2. **哈希优化**：用哈希表统计每对点的坐标和，避免O(n⁴)暴力枚举  
3. **去重处理**：每对点会被统计两次，最终答案需除以2  
4. **编码技巧**：将坐标对编码为单一数值（如`x*BASE + y`）提升哈希效率  

---

### 拓展思考
- **同类问题**：统计线段中点重复数（如[CF988D](https://codeforces.com/problemset/problem/988/D)）、寻找对称轴等  
- **优化延伸**：当坐标范围更大时，可考虑双哈希或Bloom Filter避免冲突  
- **思维训练**：将几何问题转化为代数特征统计是常见套路（如斜率、距离、中点等）

---

### 推荐习题
1. [P1102 A-B数对](https://www.luogu.com.cn/problem/P1102)（哈希统计配对）  
2. [P1496 火烧赤壁](https://www.luogu.com.cn/problem/P1496)（离散化与区间统计）  
3. [CF988D Points](https://codeforces.com/problemset/problem/988/D)（寻找几何特征）

---
处理用时：49.27秒