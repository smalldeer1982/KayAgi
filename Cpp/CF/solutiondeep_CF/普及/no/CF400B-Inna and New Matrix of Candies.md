# 题目信息

# Inna and New Matrix of Candies

## 题目描述

Inna likes sweets and a game called the "Candy Matrix". Today, she came up with the new game "Candy Matrix 2: Reload".

The field for the new game is a rectangle table of size $ n×m $ . Each line of the table contains one cell with a dwarf figurine, one cell with a candy, the other cells of the line are empty. The game lasts for several moves. During each move the player should choose all lines of the matrix where dwarf is not on the cell with candy and shout "Let's go!". After that, all the dwarves from the chosen lines start to simultaneously move to the right. During each second, each dwarf goes to the adjacent cell that is located to the right of its current cell. The movement continues until one of the following events occurs:

- some dwarf in one of the chosen lines is located in the rightmost cell of his row;
- some dwarf in the chosen lines is located in the cell with the candy.

The point of the game is to transport all the dwarves to the candy cells.

Inna is fabulous, as she came up with such an interesting game. But what about you? Your task is to play this game optimally well. Specifically, you should say by the given game field what minimum number of moves the player needs to reach the goal of the game.

## 样例 #1

### 输入

```
3 4
*G*S
G**S
*G*S
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 3
S*G
```

### 输出

```
-1
```

# AI分析结果



# Inna and New Matrix of Candies

## 题目描述

Inna 喜欢糖果和一个叫"糖果矩阵"的游戏。今天她发明了新游戏"糖果矩阵2：重装上阵"。

游戏场地是一个 $n×m$ 的矩形表格。每行包含一个矮人玩偶单元格、一个糖果单元格，其余单元格为空。游戏分为若干回合，每回合玩家需选择所有矮人未到达糖果的行，并让这些行的矮人同时向右移动。每秒每个矮人移动到右侧相邻单元格，直到以下情况之一发生：
1. 某矮人移动到行末
2.某矮人到达糖果单元格

你的任务是计算将所有矮人移动到糖果位置所需的最少回合数，若不可能则输出 -1。

---

**算法分类**：模拟

---

## 题解分析与结论

题目核心在于统计每行矮人与糖果的水平距离，当存在糖果在左侧时无解，否则不同距离的数量即为最少回合数。关键点：
1. **即时判断非法情况**：发现任一行的糖果在左侧立即返回-1
2. **去重统计**：使用集合或排序去重统计不同合法距离

---

## 精选题解

### 题解作者：L_shadow（⭐⭐⭐⭐⭐）
**亮点**：
- 使用 STL set 自动去重，代码简洁高效
- 直接利用集合特性统计不同距离数量
```cpp
set<int> se;
// 核心逻辑
for (每行) {
    if (S在G左侧) return -1;
    se.insert(距离);
}
cout << se.size();
```

### 题解作者：rain_dew（⭐⭐⭐⭐）
**亮点**：
- 排序后线性扫描去重，无需额外空间
- 显式处理输入边界
```cpp
sort(s+1, s+n+1);
ans = n;
for (int i=1; i<=n; i++) 
    if (s[i] == s[i-1]) ans--;
```

---

## 关键思路
1. **集合去重**：利用 STL set 的自动去重特性，简洁高效
2. **即时剪枝**：在输入处理阶段直接判断非法情况，避免无效计算
3. **问题转化**：将移动次数转化为不同距离的统计问题

---

## 同类题目推荐
1. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059) - 排序与去重
2. [CF1175A From Hero to Zero](https://www.luogu.com.cn/problem/CF1175A) - 数学步骤优化
3. [CF389B Fox and Cross](https://www.luogu.com.cn/problem/CF389B) - 模拟与条件判断

---
处理用时：204.22秒