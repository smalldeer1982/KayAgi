---
title: "TAP2012D - Designing T-Shirts"
layout: "post"
diff: 难度0
pid: SP12367
tag: []
---

# TAP2012D - Designing T-Shirts

## 题目描述

阿根廷的橄榄球运动正经历着辉煌时期。

## 输入格式

每个测试用例由三行组成：

- 第一行是一个整数 **N**，表示每支队伍的球员人数（$1 \le N \le 5000$）。
- 第二行列出18岁以下队伍中 **N** 名球员的姓氏。
- 第三行列出21岁以下队伍中 **N** 名球员的姓氏。

每个姓氏由最多 100 个大写字母组成，是非空的字符串。在每个测试用例中，所有 $2N$ 个姓氏的字符总数不超过 $10^5$。可能会出现同一名或不同队伍的多名球员拥有相同的姓氏。

输入以一行包含数字 **-1** 结束。

## 输出格式

对于每个测试用例，输出一行包含一个整数，表示根据题目描述的规则，可以印在一组 **N** 件 T 恤上的最大字母数。这些 T 恤将同时为两支队伍所使用。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
PEREZ GONZALEZ LOPEZ
GARCIA PERALTA RODRIGUEZ
2
RODRIGO GONZALEZ
GONZALO RODRIGUEZ
3
LOPEZ PEREZ LOPEZ
PEREZ LOPEZ LOPEZ
1
GIMENEZ
JIMENEZ
6
HEIDEGGER GAUSS GROTHENDIECK ERDOS CHURCH TURING
HEISENBERG GALOIS EULER ALLEN GODEL CHURCHILL
-1
```

### 输出

```
4
12
15
0
13
```

