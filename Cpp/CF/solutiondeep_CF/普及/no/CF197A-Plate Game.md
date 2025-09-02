# 题目信息

# Plate Game

## 题目描述

You've got a rectangular table with length $ a $ and width $ b $ and the infinite number of plates of radius $ r $ . Two players play the following game: they take turns to put the plates on the table so that the plates don't lie on each other (but they can touch each other), and so that any point on any plate is located within the table's border. During the game one cannot move the plates that already lie on the table. The player who cannot make another move loses. Determine which player wins, the one who moves first or the one who moves second, provided that both players play optimally well.

## 说明/提示

In the first sample the table has place for only one plate. The first player puts a plate on the table, the second player can't do that and loses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197A/616ddb445b80df1d3e6e847cff2f0e32d4fd3dd4.png)In the second sample the table is so small that it doesn't have enough place even for one plate. So the first player loses without making a single move.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197A/c6393d7d89b7426c75efde7ce23de7dae72901f3.png)

## 样例 #1

### 输入

```
5 5 2
```

### 输出

```
First
```

## 样例 #2

### 输入

```
6 7 4
```

### 输出

```
Second
```

# AI分析结果



# 盘子游戏

## 题目描述

你有一个长 $a$ 宽 $b$ 的矩形桌子和无限多个半径 $r$ 的盘子。两个玩家轮流放置盘子，要求盘子不能重叠（但可以接触），且所有盘子必须完全位于桌面内。无法操作的玩家判负。假设双方都采取最优策略，判断先手还是后手获胜。

## 说明/提示

当桌子只能放一个盘子时（样例1），先手放置后后手无法操作。当桌子太小无法放置任何盘子时（样例2），先手直接失败。

## 样例 #1

### 输入
```
5 5 2
```

### 输出
```
First
```

## 样例 #2

### 输入
```
6 7 4
```

### 输出
```
Second
```

---

**算法分类**：组合数学

---

## 题解综合分析

所有题解均基于博弈论中的对称策略思想，核心思路可概括为：
1. 若桌子的长宽均无法容纳至少一个盘子（直径 2r > a 或 2r > b），则先手直接失败
2. 否则先手必胜，通过中心对称策略每次镜像后手操作

---

## 精选题解

### 1. 梨衣（⭐⭐⭐⭐⭐）
**关键亮点**：
- 从博弈论维度拆解问题，提出将二维平面简化为线性模型分析
- 论证先手通过中心对称策略的必胜性
- 代码简洁，逻辑清晰

**核心代码**：
```cpp
scanf("%d%d%d",&a,&b,&r);
if(a<r*2||b<r*2)printf("Second");
else printf("First");
```

### 2. Anyonion（⭐⭐⭐⭐）
**关键亮点**：
- 明确强调特判第一次放置的边界条件
- 通过注释说明直径转换的逻辑
- 包含变量命名规范化的示范

**代码亮点**：
```cpp
c *= 2; // 半径转直径
if(a>=c && b>=c) cout << "First";
```

### 3. 恨穹不是妹（⭐⭐⭐⭐）
**个人心得**：
- 通过多组图形示例解释对称策略
- 指出该策略在各类尺寸下的通用性
- 强调问题本质是空间分割博弈

---

## 关键思路
**对称策略核心**：
1. **初始条件判定**：检查 2r ≤ min(a,b)
2. **必胜策略**：首步放置中心点，后续镜像对手操作
3. **空间分割**：每个操作将剩余空间划分为对称区域

---

## 拓展练习
1. [P1290 欧几里德的游戏](https://www.luogu.com.cn/problem/P1290)  
   （博弈论中的取石子变体）
   
2. [P2197 【模板】nim游戏](https://www.luogu.com.cn/problem/P2197)  
   （经典NIM博弈问题）

3. [P1247 取火柴游戏](https://www.luogu.com.cn/problem/P1247)  
   （异或运算在博弈论中的应用）

---

**总结**：本题的核心在于识别必胜策略的存在性，通过空间对称性将复杂博弈简化为初始条件判断，体现了博弈论问题中寻找不变量的典型思路。

---
处理用时：60.27秒