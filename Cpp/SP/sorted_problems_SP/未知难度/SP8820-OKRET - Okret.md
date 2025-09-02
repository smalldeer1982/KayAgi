---
title: "OKRET - Okret"
layout: "post"
diff: 难度0
pid: SP8820
tag: []
---

# OKRET - Okret

## 题目描述

给定一段由 $N$ 个字符组成的文本，Mirko 可以每次选择两个位置 $A$ 和 $B$，将这两个位置之间的子序列（包含 $A$ 和 $B$）进行反转。这里的位置从 $1$ 开始计数。

请编写一个程序，在所有操作完成后，输出最终得到的文本。

## 输入格式

第一行是一个长度为 $N$ 的初始文本。

第二行是整数 $M$，表示操作的次数。

接下来的 $M$ 行中，每行包含两个整数 $A$ 和 $B$，表示每次操作的起始和结束位置。

## 输出格式

输出最终的文本，只有一行。

## 说明/提示

1 < N ≤ 10^5,   
1 ≤ M ≤ 10^5,   
1 ≤ A ≤ B ≤ N.

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\nlukakuka\n3\n1 4\n5 8\n1 8\n\n
```

### 输出

```
\nkukaluka\n\n\nInput:\nkukulelebodumepcele\n5\n3 7\n10 12\n2 10\n5 18\n5 15\n\nOutput:\nkubeeludomepcelluke\n
```

