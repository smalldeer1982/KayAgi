# 题目信息

# Ciel and Robot

## 题目描述

Fox Ciel has a robot on a 2D plane. Initially it is located in (0, 0). Fox Ciel code a command to it. The command was represented by string $ s $ . Each character of $ s $ is one move operation. There are four move operations at all:

- 'U': go up, (x, y) $ → $ (x, y+1);
- 'D': go down, (x, y) $ → $ (x, y-1);
- 'L': go left, (x, y) $ → $ (x-1, y);
- 'R': go right, (x, y) $ → $ (x+1, y).

The robot will do the operations in $ s $ from left to right, and repeat it infinite times. Help Fox Ciel to determine if after some steps the robot will located in $ (a,b) $ .

## 说明/提示

In the first and second test case, command string is "RU", so the robot will go right, then go up, then right, and then up and so on.

The locations of its moves are (0, 0) $ → $ (1, 0) $ → $ (1, 1) $ → $ (2, 1) $ → $ (2, 2) $ → $ $ ... $

So it can reach (2, 2) but not (1, 2).

## 样例 #1

### 输入

```
2 2
RU
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
1 2
RU
```

### 输出

```
No
```

## 样例 #3

### 输入

```
-1 1000000000
LRRLU
```

### 输出

```
Yes
```

## 样例 #4

### 输入

```
0 0
D
```

### 输出

```
Yes
```

# AI分析结果

### 题目内容
# Ciel和机器人

## 题目描述
Fox Ciel有一个在二维平面上的机器人。最初它位于(0, 0)。Fox Ciel为它编写了一条指令。该指令由字符串 $ s $ 表示。$ s $ 的每个字符都是一个移动操作。总共有四种移动操作：
- 'U'：向上移动，(x, y) $ → $ (x, y + 1)；
- 'D'：向下移动，(x, y) $ → $ (x, y - 1)；
- 'L'：向左移动，(x, y) $ → $ (x - 1, y)；
- 'R'：向右移动，(x, y) $ → $ (x + 1, y)。

机器人将从左到右执行字符串 $ s $ 中的操作，并无限重复。帮助Fox Ciel确定经过若干步后机器人是否会位于(a, b)。

## 说明/提示
在第一个和第二个测试用例中，指令字符串是“RU”，所以机器人会先向右移动，然后向上移动，接着再向右移动，然后再向上移动，依此类推。
它移动的位置是(0, 0) $ → $ (1, 0) $ → $ (1, 1) $ → $ (2, 1) $ → $ (2, 2) $ → $ $... $
所以它可以到达(2, 2)但不能到达(1, 2)。

## 样例 #1
### 输入
```
2 2
RU
```
### 输出
```
Yes
```

## 样例 #2
### 输入
```
1 2
RU
```
### 输出
```
No
```

## 样例 #3
### 输入
```
-1 1000000000
LRRLU
```
### 输出
```
Yes
```

## 样例 #4
### 输入
```
0 0
D
```
### 输出
```
Yes
```

### 算法分类
数学

### 题解综合分析与结论
- **辛丑九月题解思路**：先计算字符串 $ s $ 长度为 $ n $ 时，一次完整执行后在 $ x $、$ y $ 方向的坐标变化量 $ (dx, dy) $。然后枚举零头步数，算出对应坐标变化量 $ (nx, ny) $，通过判断 $ dx \mid (tx - nx) $ 且 $ dy \mid (ty - ny) $ 且 $ \frac {tx - nx} {dx} = \frac {ty - ny}{dy} $ 来确定是否能到达目标点，同时处理 $ dx = 0 $ 或 $ dy = 0 $ 等特殊情况。
- **_rbq题解思路**：先求出操作 $ s $ 的任意前缀之后位置的变化，记录为 $ a_{i,1} $（$ x $ 值）和 $ a_{i,2} $（$ y $ 值）。然后枚举 $ s $ 前缀长度 $ i $，判断是否满足 $ a_{|s|,1}|a - a_{i,1},a_{|s|,2}|b - a_{i,2} $ 来确定能否到达目标点。
- **难点对比**：两者都需要处理字符串操作与坐标变化关系，辛丑九月题解难点在于对特殊情况（$ dx = 0 $ 或 $ dy = 0 $ 等）的处理；_rbq题解难点在于理解通过枚举前缀长度来判断能否到达目标点的逻辑。
- **结论**：两题解思路相似，均通过分析字符串操作对坐标的影响来解题，辛丑九月题解更注重数学关系推导和特殊情况处理，_rbq题解更侧重于前缀模拟和整除判断。但两题解整体质量未达到4星。

### 通用建议与扩展思路
通用建议：对于此类坐标移动与字符串指令结合的题目，关键在于清晰梳理字符串操作对坐标的影响，建立数学关系。可以先从简单情况入手，分析一次操作、多次操作后坐标变化规律。
扩展思路：同类型题可拓展到在不同形状地图（如矩形、圆形边界等）上按特定指令移动判断能否到达目标点；类似算法套路是先分析单次操作影响，再考虑重复操作规律，结合数学关系（如整除、余数等）来解决问题。

### 洛谷相似题目
- [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)：涉及坐标移动与数值获取，可类比本题分析移动规律。
- [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)：字符串处理与规则判断，和本题处理字符串指令有相似处。
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过数学分析来解决问题，与本题运用数学关系解题思路相符。 

---
处理用时：40.23秒