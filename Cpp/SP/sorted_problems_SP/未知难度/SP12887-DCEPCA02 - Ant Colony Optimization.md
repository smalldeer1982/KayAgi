---
title: "DCEPCA02 - Ant Colony Optimization"
layout: "post"
diff: 难度0
pid: SP12887
tag: []
---

# DCEPCA02 - Ant Colony Optimization

## 题目描述

蚂蚁通常群体行动，秩序井然。然而，在本题中，蚂蚁只能朝左（L）、右（R）、上（U）和下（D）四个方向移动。整个活动场地是一个矩形网格，网格上生活着两种蚂蚁：A型蚂蚁和B型蚂蚁。每种蚂蚁都有一只女王蚂蚁，她决定了蚂蚁繁殖时可以移动的两个方向。

题目开始时，网格上有一个初始位置，上面分别有一只A型和B型蚂蚁。繁殖过程开始时，每种蚂蚁会根据女王的指示繁殖出4只新蚂蚁。其中两个新蚂蚁是本类型蚂蚁，向指定的两个方向（每个方向一只）生成，另外两个是另一类型的蚂蚁，向剩余两个方向生成。例如，如果A型蚂蚁的女王指定向左和右 (LR) 繁殖，而B型蚂蚁的女王指定向上和下 (UD) 繁殖，则A型蚂蚁会在左侧和右侧各繁殖一只A型蚂蚁，同时在上方和下方各繁殖一只B型蚂蚁。相应地，B型蚂蚁会同样进行繁殖。新生的蚂蚁会继续在它们所在的相邻单元格，按照女王的指示继续繁殖。

每次在相邻单元格繁殖新蚂蚁需要耗费1个时间单位。你的任务是计算出A型蚂蚁和B型蚂蚁到达终点所需的最短时间之和。如果某种类型的蚂蚁无法到达终点，则结果为-1。

## 输入格式

第一行输入 $T$，表示需要处理的测试用例数。  
每个测试用例包含四行数据：  
- 第一行输入两个整数 $M, N$，代表网格的大小。  
- 第二行输入两个整数 $SX, SY$，表示起始单元格的坐标。  
- 第三行输入两个整数 $EX, EY$，表示终点单元格的坐标。  
- 第四行输入一个包含LRUD的排列组合，表示女王蚂蚁提供的繁殖方向指令。字符串的前两个字符表示A型蚂蚁女王的指令，后两个字符表示B型蚂蚁女王的指令。

## 输出格式

对于每个测试用例，输出一行，表示两种类型的蚂蚁到达终点的最短时间之和（A型蚂蚁到达终点的最短时间 + B型蚂蚁到达终点的最短时间）。如果不能到达，输出-1。

## 说明/提示

- $1 \le T \le 100,000$
- $1 \le M, N \le 1,000$
- $1 \le SX, SY, EX, EY \le \min(M, N)$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n3\n5 5\n1 1 \n3 4\nLRUD\n2 4\n0 2\n0 3\nRULD\n2 4\n0 2\n1 1 \nURDL\n\n
```

### 输出

```
\n10\n-1\n6\n\nExplanation:\n\nTestCase 1 : Minimum time at which A type ant reaches end point = 5 \nMinimum time at which B type ant reaches endpoint = 5\nTestCase 2 : B cannot reach endpoint. Hence answer is -1.\nTestCase 3 : Minimum time at which A type ant reaches end point = 4\nMinimum time at which B type ant reaches endpoint = 2
```

