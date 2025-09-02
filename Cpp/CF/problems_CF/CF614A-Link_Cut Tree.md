---
title: "Link/Cut Tree"
layout: "post"
diff: 普及-
pid: CF614A
tag: []
---

# Link/Cut Tree

## 题目描述

Programmer Rostislav got seriously interested in the Link/Cut Tree data structure, which is based on Splay trees. Specifically, he is now studying the $ expose $ procedure.

Unfortunately, Rostislav is unable to understand the definition of this procedure, so he decided to ask programmer Serezha to help him. Serezha agreed to help if Rostislav solves a simple task (and if he doesn't, then why would he need Splay trees anyway?)

Given integers $ l $ , $ r $ and $ k $ , you need to print all powers of number $ k $ within range from $ l $ to $ r $ inclusive. However, Rostislav doesn't want to spent time doing this, as he got interested in playing a network game called Agar with Gleb. Help him!

## 输入格式

The first line of the input contains three space-separated integers $ l $ , $ r $ and $ k $ ( $ 1<=l<=r<=10^{18} $ , $ 2<=k<=10^{9} $ ).

## 输出格式

Print all powers of number $ k $ , that lie within range from $ l $ to $ r $ in the increasing order. If there are no such numbers, print "-1" (without the quotes).

## 说明/提示

Note to the first sample: numbers $ 2^{0}=1 $ , $ 2^{1}=2 $ , $ 2^{2}=4 $ , $ 2^{3}=8 $ lie within the specified range. The number $ 2^{4}=16 $ is greater then $ 10 $ , thus it shouldn't be printed.

## 样例 #1

### 输入

```
1 10 2

```

### 输出

```
1 2 4 8 
```

## 样例 #2

### 输入

```
2 4 5

```

### 输出

```
-1
```

