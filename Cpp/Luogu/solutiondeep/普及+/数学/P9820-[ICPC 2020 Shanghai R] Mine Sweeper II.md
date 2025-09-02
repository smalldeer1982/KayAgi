# 题目信息

# [ICPC 2020 Shanghai R] Mine Sweeper II

## 题目描述

A mine-sweeper map $X$ can be expressed as an $n\times m$ grid. Each cell of the grid is either a mine cell or a non-mine cell. A mine cell has no number on it. Each non-mine cell has a number representing the number of mine cells around it. (A cell is around another cell if they share at least one common point. Thus, every cell that is not on the boundary has $8$ cells around it.) The following is a $16\times 30$ mine-sweeper map where a flagged cell denotes a mine cell and a blank cell denotes a non-mine cell with number 0.

![](https://cdn.luogu.com.cn/upload/image_hosting/5bykwzuy.png)

Given two mine-sweeper maps $A, B$ of size $n\times m$, you should modify at most $\left\lfloor\frac{nm}{2}\right\rfloor$ (i.e. the largest nonnegative integer that is less than or equal to $\frac{nm}{2}$) cells in $B$ (from a non-mine cell to a mine cell or vice versa) such that the sum of numbers in the non-mine cells in $A$ and the sum of numbers in the non-mine cells in $B$ are the same. (If a map has no non-mine cell, the sum is considered as $0$.)

If multiple solutions exist, print any of them. If no solution exists, print ``-1`` in one line.

## 说明/提示

We modify one cell in $B$. Then the sums of the numbers on non-mine cells in $A$ and $B$ both equal $10$.

## 样例 #1

### 输入

```
2 4
X..X
X.X.
X.X.
.X..```

### 输出

```
X.XX
.X..```

# AI分析结果



### 综合分析与结论

所有题解均基于以下核心观察：  
1. 扫雷图的数字和等于其反图的数字和（反图指所有格子状态取反）  
2. 修改次数要求满足：min(k, nm-k) ≤ floor(nm/2)，其中k是B与A的差异数  
3. 只需将B改为A或A的反图即可，必然存在解（无需处理-1情况）

### 精选题解（评分≥4星）

#### 1. Vct14（⭐⭐⭐⭐⭐）
**关键亮点**  
- 给出严格的数学证明，通过相邻格子贡献分析反图等价性  
- 代码简洁高效，使用布尔数组存储地图状态  
- 输入输出处理规范，无冗余逻辑  

**核心代码思想**  
```cpp
// 统计差异数k后选择输出A或A的反图
if(k <= n*m/2) 输出原图A;
else 输出反图（所有格子取反）;
```

#### 2. chen_zhe（⭐⭐⭐⭐）  
**关键亮点**  
- 引用官方题解，直接点明关键性质：数字和等于相邻（雷,非雷）二元组数量  
- 思路表述极简，适合快速理解问题本质  

#### 3. Nuyoah_awa（⭐⭐⭐⭐）  
**关键亮点**  
- 补充对反图数字和相同性质的详细推导  
- 通过"非雷贡献"与"雷贡献"的对称性解释等价性  
- 代码采用字符串处理，直观易懂  

### 最优技巧总结
1. **互补解思想**：当要求操作次数≤半数时，比较原解与互补解的差异，必有一解满足条件  
2. **贡献对称性分析**：将雷与非雷的贡献关系转化为双向边，从而证明反图等价性  
3. **构造题通解模式**：无需复杂计算，直接构造两种极端情况（原图/全反）即可覆盖所有可能

### 同类题目推荐
1. P2893 [USACO08FEB] Making the Grade G（构造差值最小化）  
2. CF1556D Take a Guess（位运算+互补性质）  
3. P8112 [Cnoi2021] 符文破译（字符串反转构造）

### 题解中的个人心得摘录
- "若一个图与B图的差异为x，其反图差异为nm-x" → 用于快速判断可行解  
- "-1是诈骗" → 题目必然有解，无需处理无解分支  
- "贡献值不变" → 通过重新定义贡献视角发现对称性，是解题的关键突破点

---
处理用时：55.26秒