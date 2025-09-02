---
title: "KATHTHI - KATHTHI"
layout: "post"
diff: 普及+/提高
pid: SP22393
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# KATHTHI - KATHTHI

## 题目描述

```
         Kathiresan is initially locked at cell (0,0) in a highly guarded rectangular prison of order RxC. He must reach the gate at (R-1,C-1) in order to escape from the prison. Kathiresan can move from any cell, to any of it's 4 adjacent cells (North, East, West and South). If Kathiresan is currently at (x1,y1), then he can move to (x2,y2) if and only if abs(x2-x1)+abs(y2-y1) == 1 and 0<=x2<R and 0<=y2<CKathiresan somehow manages to get the map of the prison.
If map[x1][y1] == map[x2][y2] then Kathiresan can move from (x1,y1) to (x2,y2) without killing any guards.
If map[x1][y1] != map[x2][y2], then Kathiresan can move from (x1,y1) to (x2,y2) by killing a guard.

Given the map of the prison, find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input:
The first line consists of an integer t, the number of test cases. For each test case, the first line consists of two integers R and C representing the order of the rectangular prison followed by R strings representing the map of the rectangular prison.
 
Output:
For each test case find the minimum number of guards Kathiresan must kill in order to escape from the prison.
 
Input Constraints:
1 <= t <= 10
2 <= R <= 1000
2 <= C <= 1000
'a' <= map[i][j] <= 'z'
Sample Input:
4
2 2
aa
aa
2 3
abc
def6 6akacccaaacfcamdfccaokhddzyxwdpzyxwdd5 5abbbcabaccaaaccaefcicdgdd Sample Output:
0
322
```

## 样例 #1

### 输入

```
4
2 2
aa
aa
2 3
abc
def
6 6
akaccc
aaacfc
amdfcc
aokhdd
zyxwdp
zyxwdd
5 5
abbbc
abacc
aaacc
aefci
cdgdd

```

### 输出

```
0
3
2
2
```



---

---
title: "PUBLICAT - Publication"
layout: "post"
diff: 普及+/提高
pid: SP9255
tag: ['广度优先搜索 BFS']
---

# PUBLICAT - Publication

## 题目描述

Orizondo 数用于衡量某个科学家与 Rodrigo Orizondo 在学术论文合著中的“合作距离”。Rodrigo Orizondo 的 Orizondo 数是零。要获得有限的 Orizondo 数，科学家必须与至少一个已有有限 Orizondo 数的科学家共同发表论文。一个科学家的 Orizondo 数是他所有合作者中最低的 Orizondo 数加一。论文发表的顺序和编号分配顺序无关，因为每次发表后，系统会自动更新所有作者的 Orizondo 数。

你将得到一组 **论文** 数据，每篇论文包含一组作者，格式为 “AUTHOR\_1 AUTHOR\_2 ... AUTHOR\_N”（引号仅为明确表示）。其中，Rodrigo Orizondo 用 “ORIZONDO” 表示。

请输出所有作者的 Orizondo 数。输出格式为 “AUTHOR NUMBER”，若无法为某作者赋予有限的 Orizondo 数，仅输出 “AUTHOR”。作者的输出顺序应按字典序排列。

## 输入格式

第一行输入一个整数 \( C \)，表示测试用例的数量（\( 0 < C \)）。

每个测试用例首先包含一个整数 \( N \)，表示论文的数量，接着是 \( N \) 行，每行包含一组用空格分隔的作者姓名。

## 输出格式

对于每个测试用例，输出一行，包含每个作者及其 Orizondo 数，信息之间用空格分隔。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
1
ORIZONDO
2
KLEITMAN LANDER
ORIZONDO KLEITMAN
4
ORIZONDO B
A B C
B A E
D F
```

### 输出

```
ORIZONDO 0
KLEITMAN 1 LANDER 2 ORIZONDO 0
A 2 B 1 C 2 D E 2 F ORIZONDO 0
```



---

