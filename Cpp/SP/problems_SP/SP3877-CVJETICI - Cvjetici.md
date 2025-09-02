---
title: "CVJETICI - Cvjetici"
layout: "post"
diff: 难度0
pid: SP3877
tag: []
---

# CVJETICI - Cvjetici

## 题目描述

在一个遥远的星球上，生长着一种神奇的植物，每株植物都有两根茎。这些植物可以用三个数值来描述：两根茎的 $x$ 坐标分别为 $L$ 和 $R$，以及它们相连的高度 $H$。下图展示了一个例子，这株植物的参数为 $L=2$、$R=5$、$H=4$。

![植物示意图](https://cdn.luogu.com.cn/upload/vjudge_pic/SP3877/e7f7f56b085f59388be16ad70b2ab7f63fb8948d.png)

每天，这个星球上都会有一株新的植物出现。第一天长出的植物高度为 1，之后每天新增的植物高度都比前一天的高 1。

当一株新生植物的茎与另一株植物的水平段有交叉时（前提是那个位置还没有花），便会开出一朵小花。如果只是接触到一个点，不会开花。下图为第一个示例的可视化过程：

![示例过程图](https://cdn.luogu.com.cn/upload/vjudge_pic/SP3877/4d9060378144e2bdb42a00f1772cd0dc7fde19ae.png)
![示例过程图](https://cdn.luogu.com.cn/upload/vjudge_pic/SP3877/4783144745f03f983238b0128aa46fd5eac25461.png)
![示例过程图](https://cdn.luogu.com.cn/upload/vjudge_pic/SP3877/ddbf87ff69ebcc48c5109dd710d0737269176c2d.png)
![示例过程图](https://cdn.luogu.com.cn/upload/vjudge_pic/SP3877/0a5f759830544402a08ae61bfe8a52c7fe42f1e8.png)

请设计一个程序，根据所有植物的坐标，计算出每天新增的花朵数。

## 输入格式

第一行包含一个整数 $N$（$1 \le N \le 10^5$），表示共有 $N$ 株植物。

接下来的 $N$ 行中，每行包含两个整数 $L$ 和 $R$（$1 \le L < R \le 10^5$），代表每株植物的左茎和右茎的 $x$ 坐标。

## 输出格式

输出 $N$ 行，每行一个整数，表示当天新长出的植物使得新增的花朵数量。

## 说明/提示

- $1 \le N \le 10^5$
- $1 \le L < R \le 10^5$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1 4
3 7
1 6
2 6
```

### 输出

```
0
1
1
2


Input
5
1 3
3 5
3 9
2 4
3 8

Output
0
0
0
3
2
```

