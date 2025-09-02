# 题目信息

# Squares

## 题目描述

You are given an infinite checkered field. You should get from a square ( $ x_{1} $ ; $ y_{1} $ ) to a square ( $ x_{2} $ ; $ y_{2} $ ). Using the shortest path is not necessary. You can move on the field squares in four directions. That is, when you are positioned in any square, you can move to any other side-neighboring one.

A square ( $ x $ ; $ y $ ) is considered bad, if at least one of the two conditions is fulfilled:

- $ |x+y|≡0 $ $ (mod 2a) $ ,
- $ |x-y|≡0 $ $ (mod 2b) $ .

Your task is to find the minimum number of bad cells one will have to visit on the way from ( $ x_{1} $ ; $ y_{1} $ ) to ( $ x_{2} $ ; $ y_{2} $ ).

## 说明/提示

In the third sample one of the possible paths in (3;-1)->(3;0)->(3;1)->(3;2)->(4;2)->(4;3)->(4;4)->(4;5)->(4;6)->(4;7)->(3;7). Squares (3;1) and (4;4) are bad.

## 样例 #1

### 输入

```
2 2 1 0 0 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 2 10 11 0 1
```

### 输出

```
5
```

## 样例 #3

### 输入

```
2 4 3 -1 3 7
```

### 输出

```
2
```

# AI分析结果



# Squares

## 题目描述

给定一个无限的方格棋盘，你需要从方格 $(x_1, y_1)$ 移动到 $(x_2, y_2)$。路径不一定是最短的，但要求经过的坏点最少。移动时可以上下左右走到相邻方格。

坏点的定义是满足以下任一条件：
1. $|x+y| \equiv 0 \pmod{2a}$
2. $|x-y| \equiv 0 \pmod{2b}$

求必须经过的坏点最小数量。

## 说明/提示

样例3中，路径可能经过 (3;1) 和 (4;4) 两个坏点。

## 样例 #1

### 输入
```
2 2 1 0 0 1
```

### 输出
```
1
```

---

**算法分类**：数学

---

### 题解分析与结论

所有题解均采用**坐标变换法**，将原坐标 $(x,y)$ 转换为旋转坐标系 $(u,v)=(x+y, x-y)$，将坏点条件转换为：
- $u \equiv 0 \pmod{2a}$
- $v \equiv 0 \pmod{2b}$

核心思路是计算起点和终点在变换后的坐标系中跨越网格线的次数，取横向和纵向跨越次数的最大值即为答案。关键在于：
1. 将路径问题转化为网格线跨越次数的数学问题
2. 通过整数除法计算区域编号差
3. 处理正负坐标对区域划分的影响

---

### 精选题解

#### 1. 清小秋ovo（⭐⭐⭐⭐⭐）
**关键亮点**：
- 简洁的坐标变换和整数除法处理
- 通过区域差计算跨越次数
- 代码仅需10行，时空复杂度O(1)

**核心代码**：
```cpp
int a,b,x1,x2,y1,y2;
cin>>a>>b>>x1>>y1>>x2>>y2;
// 坐标变换
int u1 = x1 + y1, v1 = y1 - x1;
int u2 = x2 + y2, v2 = y2 - x2;
// 计算区域编号
a *= 2; b *= 2;
int reg_u1 = u1/a + (u1>0), reg_u2 = u2/a + (u2>0);
int reg_v1 = v1/b + (v1>0), reg_v2 = v2/b + (v1>0);
cout << max(abs(reg_u2 - reg_u1), abs(reg_v2 - reg_v1));
```

#### 2. Mistybranch（⭐⭐⭐⭐）
**关键亮点**：
- 详细注释解释坐标旋转原理
- 明确处理正负坐标的区域划分
- 变量命名清晰易懂

**个人心得**：
> "旋转坐标系后，坏点形成网格线，最优路径必走交点" —— 揭示了问题本质是网格线跨越次数的几何问题

---

### 关键思路总结
1. **坐标变换**：将原坐标系旋转45度，转化为正交网格问题
2. **区域计数**：通过整数除法和符号处理计算区域编号
3. **取最大值**：答案是两个方向跨越次数的最大值，因为最优路径可同时跨越两个方向的网格线

---

### 拓展建议
类似问题可使用：
1. **镜像对称**：处理周期性障碍问题
2. **格点计数**：计算路径经过特定条件点的数量
3. **数学建模**：将路径问题转化为坐标系中的几何问题

---

### 推荐练习
1. [P1865 路径计数](https://www.luogu.com.cn/problem/P1865) - 网格路径中的障碍计数
2. [CF628B](https://codeforces.com/problemset/problem/628/B) - 模数性质与坐标变换
3. [P2735 电网](https://www.luogu.com.cn/problem/P2735) - 格点与区域划分的数学问题

---
处理用时：212.21秒