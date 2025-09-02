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



### 综合分析与结论
题目核心是统计中心对称四点组，关键发现是两对点必须有相同的中点（即坐标和相等）。所有题解均基于以下核心思路：
- 遍历所有点对，计算坐标和（即中点的2倍坐标）
- 用哈希结构统计相同坐标和出现的次数
- 每个坐标和出现k次时，贡献C(k,2)组四点，但需处理重复计数

### 高分题解推荐（≥4星）

#### 1. feecle6418（⭐⭐⭐⭐⭐）
**关键亮点**：
- 同时给出基础解法和多种优化方案（哈希压缩、数据结构替换）
- 通过实验对比不同优化策略的时间效率
- 代码结构清晰，包含防抄袭提示
**核心思路**：
```cpp
// 预处理所有点对的坐标和
for(i=1~n) for(j=i+1~n) 
    hash[x[i]+x[j], y[i]+y[j]]++
// 统计答案时每个点对贡献对应哈希值-1
ans = sum(hash[key]-1) / 2
```

#### 2. Hog_Dawa_IOI（⭐⭐⭐⭐）
**关键亮点**：
- 用数学证明强化思路可信度
- 代码极简但完整呈现核心逻辑
**个人心得**：
> "每一组点会被计算两次，所以要除以二" —— 点明重复计数的处理关键

#### 3. xiaoyuchenp（⭐⭐⭐⭐）
**关键亮点**：
- 明确点出广义平行四边形的几何特性
- 强调必须开O2优化的实践细节
**代码亮点**：
```cpp
// 使用C++11特性初始化pair
mp[{g[i].x+g[j].x, g[i].y+g[j].y}]++ 
```

### 最优关键思路
1. **坐标和哈希法**：将点对的坐标和作为哈希键，统计出现次数
2. **重复计数处理**：最终答案除以2（每四元组被两对点计算）
3. **优化技巧**：
   - 用长整数(如`x_sum*BASE + y_sum`)代替pair提升哈希效率
   - 使用`gp_hash_table`等高效哈希结构

### 拓展应用
- **类似问题**：寻找矩形（两对点坐标和相等且距离相等）、对称点统计等问题
- **算法套路**：坐标特征哈希化，将几何问题转化为计数问题

### 推荐习题
1. [P3183 HAOI2016找相同字符](https://www.luogu.com.cn/problem/P3183)（哈希统计）
2. [CF755C PolandBall and Forest](https://codeforces.com/problemset/problem/755/C)（坐标特征处理）
3. [P2906 USACO08 Cow Neighborhoods](https://www.luogu.com.cn/problem/P2906)（坐标变换+哈希）

---
处理用时：45.50秒