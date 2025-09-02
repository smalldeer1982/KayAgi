# 题目信息

# Beautiful Sets of Points

## 题目描述

Manao has invented a new mathematical term — a beautiful set of points. He calls a set of points on a plane beautiful if it meets the following conditions:

1. The coordinates of each point in the set are integers.
2. For any two points from the set, the distance between them is a non-integer.

Consider all points $ (x,y) $ which satisfy the inequations: $ 0<=x<=n $ ; $ 0<=y<=m $ ; $ x+y&gt;0 $ . Choose their subset of maximum size such that it is also a beautiful set of points.

## 说明/提示

Consider the first sample. The distance between points (0, 1) and (1, 2) equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF268C/2826342a15affce70e459206e8466cd2b66552a3.png), between (0, 1) and (2, 0) — ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF268C/29e9747d937919d5f8da56e63d91085e91605151.png), between (1, 2) and (2, 0) — ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF268C/29e9747d937919d5f8da56e63d91085e91605151.png). Thus, these points form a beautiful set. You cannot form a beautiful set with more than three points out of the given points. Note that this is not the only solution.

## 样例 #1

### 输入

```
2 2
```

### 输出

```
3
0 1
1 2
2 0
```

## 样例 #2

### 输入

```
4 3
```

### 输出

```
4
0 3
2 1
3 0
4 2
```

# AI分析结果



### 中文题目重写

# 美丽点集

## 题目描述

Manao 定义了一个新的数学术语——美丽点集。平面上的点集满足以下条件时被称为美丽点集：

1. 集合中每个点的坐标都是整数
2. 集合中任意两点之间的距离都不是整数

给定范围 $0 \leq x \leq n$ 和 $0 \leq y \leq m$，且 $x+y>0$，请找出满足条件的最大美丽点集。

## 样例 #1

### 输入
```
2 2
```

### 输出
```
3
0 1
1 2
2 0
```

## 样例 #2

### 输入
```
4 3
```

### 输出
```
4
0 3
2 1
3 0
4 2
```

---

**算法分类**：构造

---

### 题解综合分析

各题解核心思路均为构造对角线上满足 $x+y=k$ 的点集（$k=\min(n,m)$），通过两点间距离为 $\sqrt{2}$ 的整数倍确保非整距离。所有解法均得出最大点数为 $\min(n,m)+1$。

---

### 精选题解

#### 1. LRL65（⭐⭐⭐⭐⭐）
**关键亮点**：  
- 通过反证法说明同行/列必然存在整距离  
- 给出数学证明 $\sqrt{2} \cdot |i-j|$ 必为非整数  
- 代码简洁直观（直接输出对角点）

**核心代码**：
```cpp
int main() {
    cin>>n>>m;
    n=min(n,m);
    cout<<n+1<<endl;
    for(int i=0;i<=n;i++) cout<<i<<" "<<n-i<<endl;
}
```

#### 2. songtaoran（⭐⭐⭐⭐）
**关键亮点**：  
- 通过手玩样例快速定位对角线构造法  
- 强调距离公式的数学验证过程  

**个人心得**：  
> "恭喜你，这道题你AC了！" —— 提示通过构造法快速解题的思路  

**核心代码**：  
```cpp
for(ll i = 0; i <= t; i++) printf("%lld %lld\n", i, t - i);
```

#### 3. da32s1da（⭐⭐⭐⭐）
**构造技巧**：  
- 解释原对角线 $(0,0)$ 被排除的原因  
- 采用逆序输出对角线点增强可读性  

**核心代码**：  
```cpp
for(int i=qwq;i>=0;i--)printf("%d %d\n",i,qwq-i);
```

---

### 关键思路总结
选择斜率为-1的对角线进行点集构造，每个点的坐标满足 $x+y = \min(n,m)$，此时：  
1. 不同行且不同列避免整行/列距离  
2. 任意两点间距为 $\sqrt{2} \cdot p$（$p$为整数），确保非整数距离  
3. 最大点数由较小维度决定：$\min(n,m)+1$

---

### 拓展应用
类似构造题可考虑：  
1. 利用特殊数学性质（如质数、平方数等）  
2. 几何对称性（如棋盘染色、螺旋排列）  
3. 离散点集的极值构造  

---

### 推荐练习题
1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)（逆向构造）  
2. [P2119 魔法阵](https://www.luogu.com.cn/problem/P2119)（数学规律构造）  
3. [CF1111C Creative Snap](https://www.luogu.com.cn/problem/CF1111C)（分治+构造策略）

---
处理用时：56.22秒