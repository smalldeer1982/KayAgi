# 题目信息

# [ICPC 2021 Nanjing R] Windblume Festival

## 题目描述

The Windblume Festival in Mondstadt is coming! People are preparing windblumes for Barbatos and for those they love and adore. The Windblume Festival is also an opportunity to improve the relationships people have.

![](https://cdn.luogu.com.cn/upload/image_hosting/nbhhi3bg.png)

During the festival, a famous game will be played every year, invented by Jean, the Acting Grand Master of the Knights of Favonius. In the game, $n$ players numbered from $1$ to $n$ stand in a circle, each holding an integer with them. Each turn, one player will be removed. The game will end when there is only one player left.

For each turn, let $k$ be the number of players remaining and $a_i$ be the integer player $i$ holds. Two adjacent players, $x$ and $(x \bmod k + 1)$ are selected and player $(x \bmod k + 1)$ is removed from the game. Player $x$'s integer will then change from $a_x$ to $(a_x - a_{x \bmod k + 1})$. Player $y$ in this turn will become player $(y - 1)$ in the next turn for all $x < y \le k$, though the integer they hold will not change.

Jean wants to know the maximum possible integer held by the last remaining player in the game by selecting the players in each round optimally.

## 说明/提示

For the first sample test case follow the strategy shown below, where the underlined integers are the integers held by the players selected in each turn.

$\{\underline{1}, -3, 2, \underline{-4}\}$ (select $x = 4$) $\to$ $\{-3, \underline{2, -5}\}$ (select $x = 2$) $\to$ $\{\underline{-3, 7}\}$ (select $x = 2$) $\to$ $\{10\}$.

## 样例 #1

### 输入

```
5
4
1 -3 2 -4
11
91 66 73 71 32 83 72 79 84 33 93
12
91 66 73 71 32 83 72 79 84 33 33 93
13
91 66 73 71 32 83 72 79 84 33 33 33 93
1
0
```

### 输出

```
10
713
746
779
0
```

# AI分析结果



**算法分类**: 数学

---

### 题解综合分析结论
题目本质是构造符号组合求最大值的数学问题。核心思路分三种情况处理：
1. 既有正数又有负数 → 答案=绝对值之和
2. 全正或全负 → 答案=绝对值之和-2×最小绝对值
3. n=1 → 直接输出

所有题解均围绕该数学结论展开，差异仅在于分类讨论的实现方式。

---

### 精选题解列表

1. **题解作者: RAND_MAX**  
   ⭐⭐⭐⭐⭐  
   **关键亮点**:  
   - 使用布尔标记正负存在性，逻辑简明  
   - 代码仅需一次遍历，时间复杂度O(n)  
   **核心代码**:  
   ```cpp
   for(int i=1;i<=n;i++){
       sum += abs(a[i]);
       minn = min(minn,abs(a[i]));
       if(a[i]>0) has_pos=true;
       if(a[i]<0) has_neg=true;
   }
   cout << (has_pos&&has_neg ? sum : sum-2*minn);
   ```

2. **题解作者: zyn_**  
   ⭐⭐⭐⭐  
   **关键亮点**:  
   - 数学归纳法证明结论严谨  
   - 符号系统分析透彻  
   **实现思想**:  
   统计绝对值和、最小绝对值，标记正负存在性，按分类输出。

3. **题解作者: wangbinfeng**  
   ⭐⭐⭐⭐  
   **个人心得**:  
   - 通过代数推导发现绝对值规律  
   - 将零值处理融入分类讨论  
   **代码特点**:  
   采用快读处理输入，使用位运算标记状态。

---

### 核心实现思想
1. 遍历数组同时记录三个值：  
   - 绝对值总和 `sum`  
   - 最小绝对值 `minn`  
   - 正负存在标记 `has_pos`/`has_neg`  
2. 根据标记选择输出模式：  
   ```cpp
   if(has_pos && has_neg) 
       ans = sum;
   else 
       ans = sum - 2*minn;
   ```

---

### 拓展应用
类似符号构造问题：
1. [CF1592B Hemose Shopping](https://www.luogu.com.cn/problem/CF1592B)  
   → 利用绝对值性质推导操作可行性
2. [P2513 逆序对数列](https://www.luogu.com.cn/problem/P2513)  
   → 数学规律与递推结合
3. [P2118 比例简化](https://www.luogu.com.cn/problem/P2118)  
   → 分数运算中的极值问题

---

### 题解心得摘录
1. **紊莫**:  
   > "零的存在相当于可以忽视符号限制，使得可以自由构造符号组合"  
   → 揭示零在问题中的特殊作用

2. **Lvlinxi2010**:  
   > "舍去绝对值最小的数相当于损失最小"  
   → 指明全正/全负情况的最优策略本质

3. **RyanCh**:  
   > "将全是负数转为正数处理，保持逻辑统一"  
   → 体现问题转换的简化思想

---
处理用时：40.57秒