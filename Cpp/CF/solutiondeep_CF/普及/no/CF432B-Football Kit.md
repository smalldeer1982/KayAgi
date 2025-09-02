# 题目信息

# Football Kit

## 题目描述

Consider a football tournament where $ n $ teams participate. Each team has two football kits: for home games, and for away games. The kit for home games of the $ i $ -th team has color $ x_{i} $ and the kit for away games of this team has color $ y_{i} $ $ (x_{i}≠y_{i}) $ .

In the tournament, each team plays exactly one home game and exactly one away game with each other team ( $ n(n-1) $ games in total). The team, that plays the home game, traditionally plays in its home kit. The team that plays an away game plays in its away kit. However, if two teams has the kits of the same color, they cannot be distinguished. In this case the away team plays in its home kit.

Calculate how many games in the described tournament each team plays in its home kit and how many games it plays in its away kit.

## 样例 #1

### 输入

```
2
1 2
2 1
```

### 输出

```
2 0
2 0
```

## 样例 #2

### 输入

```
3
1 2
2 1
1 3
```

### 输出

```
3 1
4 0
2 2
```

# AI分析结果



# Football Kit

## 题目描述

在一个有 $n$ 支球队参加的足球锦标赛中，每支球队有两套球衣：主场球衣和客场球衣。第 $i$ 支球队的主场球衣颜色为 $x_i$，客场球衣颜色为 $y_i$（保证 $x_i \neq y_i$）。

每支球队会与其他所有球队各进行两场比赛：一场主场一场客场（总场次为 $n(n-1)$）。主场球队固定穿主场球衣。客场球队若发现其客场球衣颜色与主场球队的主场球衣颜色相同，则会改穿自己的主场球衣。

请计算每支球队在锦标赛中穿主场球衣和客场球衣的总次数。

## 输入输出样例

### 样例 #1
输入：
```
2
1 2
2 1
```
输出：
```
2 0
2 0
```

### 样例 #2
输入：
```
3
1 2
2 1
1 3
```
输出：
```
3 1
4 0
2 2
```

---

**算法分类**  
枚举 + 桶统计

---

### 综合分析与结论

所有题解核心思路一致：  
1. 每个队作为主场时必穿主场球衣，共 $n-1$ 次  
2. 作为客场时，若其客场球衣 $y_i$ 与其他队主场球衣冲突，会改穿主场球衣  
3. 使用桶统计所有主场球衣颜色出现次数  
4. 最终主场总次数 = $n-1 + \text{其他队主场球衣为} y_i \text{的数量}$  
5. 客场总次数 = $n-1 - \text{冲突次数}$

---

### 优质题解推荐

#### 题解1：封禁用户（赞2） ⭐⭐⭐⭐⭐  
**亮点**  
- 代码极简（仅15行）  
- 直接使用数组桶统计，无冗余结构  
**关键代码**  
```cpp
int z[x]++; // 统计主场颜色
cout << n + z[y] - 1 << ' ' << n - z[y] - 1; 
// 主场次数 = n-1 + z[y]，客场次数 = n-1 - z[y]
```

#### 题解2：GCSG01（赞1） ⭐⭐⭐⭐  
**亮点**  
- 变量命名清晰（z表主场，c表客场）  
- 注释简明解释公式推导  
**核心思路**  
```cpp
t[z[i]]++; // 记录主场颜色
cout << n + t[c[i]] -1 << " " << n - t[c[i]] -1;
```

#### 题解3：Molina（赞2） ⭐⭐⭐⭐  
**亮点**  
- 分步骤说明数学推导过程  
- 完整注释主场/客场次数计算逻辑  
**关键实现**  
```cpp
ton[a[i].x]++; // 桶统计
b[i].x = n-1 + ton[a[i].y]; 
b[i].y = n-1 - ton[a[i].y];
```

---

### 关键思路总结  
**桶统计优化**：用数组直接记录主场颜色分布，将复杂度从 $O(n^2)$ 优化至 $O(n)$。  
**数学建模**：将问题分解为固定主场次数 + 动态冲突次数，避免逐场比赛模拟。

---

### 同类题目推荐  
1. [P1102 A-B数对](https://www.luogu.com.cn/problem/P1102) - 桶统计差值  
2. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406) - 前缀和与差分统计  
3. [P1997 小乔的难题](https://www.luogu.com.cn/problem/P1997) - 颜色覆盖与计数

---
处理用时：122.77秒