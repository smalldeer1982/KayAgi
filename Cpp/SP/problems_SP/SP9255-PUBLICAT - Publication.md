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

