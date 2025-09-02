---
title: "IITWPC4L - Maggu and Mystery"
layout: "post"
diff: 难度0
pid: SP18289
tag: []
---

# IITWPC4L - Maggu and Mystery

## 题目描述

Maggu 前往神秘之地探索，这片土地充满了谜团。进入神秘之地共有 $n$ 扇门，而Maggu必须至少开启其中的 $d$ 扇门才能进去。每扇门只能用特定的神秘钥匙打开，每个门上都有一个编号锁，只有编号与之匹配的钥匙才能开启。

由于 Maggu 还是个小男孩，他获得了一项神秘的能力：可以对每扇门的锁编号进行调整，将它增加或减少最多 $v[i]$。神秘之地的钥匙非常特别，它们可以是任何整数（无需是正数）。不过有个限制，不允许两扇门使用相同的钥匙编号。如果有两扇或更多的门使用相同的钥匙编号，则只有第一扇门能打开。因此，Maggu 需要利用神秘力量尽可能少地调整钥匙编号，以至少打开 $d$ 扇门。

由于 Maggu 急着去冒险，他希望在使用最少次数的神秘力量操作下实现目标。请计算 Maggu 至少需要多少次使用神秘力量，才能顺利进入神秘之地，开始他的旅程。

## 输入格式

第一行输入一个整数 $T$，表示测试用例的数量（$1 \le T \le 20$）。

对于每个测试用例，输入包括三行：
- 第一行是两个空格分隔的整数 $n$ 和 $d$，表示共有 $n$ 扇门，其中至少要打开 $d$ 扇（$1 \le n \le 50$，$1 \le d \le n$）。
- 第二行包含 $n$ 个整数，表示每扇门的锁编号（每个数字范围为 $1$ 到 $1000$）。
- 第三行包含 $n$ 个空格分隔的整数，表示每扇门对应的调整限额 $v[i]$（$1 \le v[i] \le 5$）。

## 输出格式

对于每个测试用例，输出一行表示问题的答案，即最少需要使用多少次神秘力量才能满足条件。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4\n3 2
5 1 3
1 1 1\n3 3\n1 1 1\n2 1 1\n4 4\n1 1 1 2\n1 2 1 1\n4 3\n1 1 1 2\n1 2 1 1
```

### 输出

```
\n 0\n 2\n 2\n 1\n\nExplanation of the test case. For the second test case, the configuation of keys according to doors can be as follows -1, 1, 2.\nHe only needs 2 Mystery powers for doing this.\nExplanation of last test case: For opening two doors, You can use key configutation of 0, 1, 1, 2 (reducing the first door \nnumber by 1). Then use 0, 1, 2 keys to open 3 doors. \nYou can also use key configutation of 1 -1 1 2  (reducing the second door number by 2), Then use -1, 1, 2 for \nopening 3 doors.
```

