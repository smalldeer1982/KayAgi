---
title: "Bob Laptop Woolmer and Eddie Desktop Barlow"
layout: "post"
diff: 提高+/省选-
pid: UVA10072
tag: []
---

# Bob Laptop Woolmer and Eddie Desktop Barlow

## 题目描述

为了参加下一届世界杯，Barlow 将给每个球员在击球、投球和接球这三个方面打三个分值，他将从中选择分值最大的组合。

Barlow 计划在球队中有四名击球手，三名投球手和三名多面手。分数计算规则如下：

对于任意球员 P
- 如果P被选为击球手，他的有效分数 $= 0.8 \times$ 击球分数 $+ 0.2 \times$ 接球分数
- 如果P被选为投球手，他的有效分数 $= 0.7 \times$ 投球分数 $+ 0.1 \times$ 击球分数 $+ 0.2 \times$ 接球分数
- 如果P被选为多面手，他的有效分数 $= 0.4 \times$ 击球分数 $+ 0.4 \times$ 投球分数 $+ 0.2 \times$ 接球分数

所有的有效分数都应四舍五入到最近的整数，以便进一步计算。  

请根据 Barlow 打出的分数，编写选择最佳球队的程序。

**本题多测**。

## 输入格式

对于每组数据：  

第一行 $1$ 个整数 $n\,(10 \leq n \leq 100)$，表示运动员总数。  

第 $2\sim (n-1)$ 行，每行 $3$ 个整数 $bt_i, bl_i$ 和 $fl_i\,(0 \leq bt_i, bl_i, fl_i \leq 100)$，分别表示第 $i$ 名运动员的击球、投球与接球分值。  

最后一行三个整数 $BT\,(1 \leq BT \leq 7), BL\,(0 \leq BL \leq 5)$ 和 $AR\,(0 \leq AR \leq 4)$，分别表示最终的队伍中需要的击球手、投球手和多面手的人数。$BT, BL$ 和 $AR$ 之和总是 $10$。  

当 $n=0$ 时，输入结束。

## 输出格式

对于每组数据，请按照如下格式输出：
```
Team #x Maximum Effective Score = ans1 Batsmen : {ans2} Bowlers : {ans3} All-rounders : {ans4}
```


$\texttt{x}$ 表示数据（队伍）编号（从 $1$ 开始）。

$\texttt{ans1}$ 表示分值最大的队伍分数总和。

$\texttt{ans2, ans3, ans4}$ 分别表示被选为击球手的运动员编号、被选为投球手的运动员的编号和被选为多面手的运动员编号。

如果有多组解，输出任意一种即可。

感谢 @[159号程序员](/user/334586) 提供的翻译。

## 样例 #1

### 输入

```
15
43 17 97
10 75 15
53 33 62
85 12 19
44 77 85
19 10 76
58 26 84
33 32 80
88 29 83
30 4 7
66 15 18
20 93 1
11 74 98
20 89 40
58 24 35
6 3 1
20
96 1 38
82 53 66
42 22 29
47 57 41
41 70 19
50 21 19
72 57 54
3 71 99
42 8 10
20 81 67
82 2 91
72 48 66
45 8 76
5 38 68
69 27 88
30 43 67
37 92 46
56 22 7
57 54 18
69 71 64
5 3 2
0
```

### 输出

```
Team #1
Maximum Effective Score = 664
Batsmen : 1 3 4 7 9 11
Bowlers : 12 13 14
All-rounders : 5
Team #2
Maximum Effective Score = 741
Batsmen : 1 2 11 12 15
Bowlers : 8 10 17
All-rounders : 7 20
```

