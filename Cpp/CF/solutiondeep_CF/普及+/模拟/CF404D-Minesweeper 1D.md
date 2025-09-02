# 题目信息

# Minesweeper 1D

## 题目描述

Game "Minesweeper 1D" is played on a line of squares, the line's height is 1 square, the line's width is $ n $ squares. Some of the squares contain bombs. If a square doesn't contain a bomb, then it contains a number from 0 to 2 — the total number of bombs in adjacent squares.

For example, the correct field to play looks like that: 001\*2\*\*\*101\*. The cells that are marked with "\*" contain bombs. Note that on the correct field the numbers represent the number of bombs in adjacent cells. For example, field 2\* is not correct, because cell with value 2 must have two adjacent cells with bombs.

Valera wants to make a correct field to play "Minesweeper 1D". He has already painted a squared field with width of $ n $ cells, put several bombs on the field and wrote numbers into some cells. Now he wonders how many ways to fill the remaining cells with bombs and numbers are there if we should get a correct field in the end.

## 说明/提示

In the first test sample you can get the following correct fields: 001\*\*1, 001\*\*\*, 001\*2\*, 001\*10.

## 样例 #1

### 输入

```
?01???
```

### 输出

```
4
```

## 样例 #2

### 输入

```
?
```

### 输出

```
2
```

## 样例 #3

### 输入

```
**12
```

### 输出

```
0
```

## 样例 #4

### 输入

```
1
```

### 输出

```
0
```

# AI分析结果



### 中文重写题目

#### 题目描述
**一维扫雷**

游戏"一维扫雷"在一个由 $n$ 个方格组成的直线上进行。某些方格包含地雷，未埋雷的方格会显示数字 0-2，表示相邻方格中的地雷总数。

例如合法局面：001*2***101*。带*的格子是雷。注意数字必须准确反映相邻雷数（如"2*"不合法，因为数字2需要两侧有两个雷）。

Valera 想构造一个合法局面。他已经绘制了部分格子（包含雷和数字），求填充剩余'?'格子的合法方案数。

#### 输入格式
一行字符串，包含'0','1','2','*','?'。

#### 输出格式
合法方案数模 $10^9+7$。

#### 样例
**样例1输入**  
?01???  
**样例1输出**  
4  
**样例解释**  
可能方案：001**1, 001***, 001*2*, 001*10  

---

### 题解分析与结论

#### 关键思路总结
1. **动态规划核心**：以位置 $i$ 为中心，定义状态表示后续格子的约束条件
2. **状态压缩技巧**：多数题解采用 3 种核心状态：
   - 当前格子不是雷且下一格不是雷
   - 当前格子不是雷且下一格是雷 
   - 当前格子是雷
3. **滚动数组优化**：处理 1e6 数据规模时，使用奇偶滚动将空间复杂度降至 $O(1)$
4. **问号处理**：同时考虑所有可能情况（0/1/2/*）进行转移

#### 推荐题解
1. **Star_Cried（5星）**
   - 亮点：状态定义简洁，滚动数组优化到位，代码可读性强
   - 关键代码：
```cpp
int f[2][3]; // 滚动数组
// 状态转移核心逻辑
case '?':{
    qm(f[i][0],f[i^1][0]);
    qm(f[i][0],f[i^1][2]);
    qm(f[i][1],f[i^1][0]);
    qm(f[i][1],f[i^1][2]);
    qm(f[i][2],f[i^1][1]);
    qm(f[i][2],f[i^1][2]);
    break;
}
```

2. **Austin0116（4星）**
   - 亮点：五状态定义更直观，适合理解数字约束关系
   - 状态定义：
     - 0: 无雷且两边无雷
     - 1: 无雷且两边有雷
     - 2: 左边有雷右边无
     - 3: 右边有雷左边无 
     - 4: 自身是雷

3. **Rolling_star（4星）**
   - 亮点：三状态定义兼顾效率和可读性
   - 状态转移方程：
```cpp
// 当前字符为'?'时的转移
f[i][0] = (前状态0 + 前状态2) // 填0
f[i][1] = (前状态0 + 前状态2) // 填1 
f[i][2] = (前状态1 + 前状态2) // 填*
```

---

### 拓展练习
1. [P2327 扫雷](https://www.luogu.com.cn/problem/P2327)  
   （二维扫雷问题，强化状态分析能力）

2. [P2583 地图](https://www.luogu.com.cn/problem/P2583)  
   （动态规划处理网格状态转移）

3. [P1273 有线电视网](https://www.luogu.com.cn/problem/P1273)  
   （树形DP与状态设计训练）

---
处理用时：50.64秒