---
title: "Floor or Ceil"
layout: "post"
diff: 普及+/提高
pid: CF2082B
tag: ['贪心']
---

# Floor or Ceil

## 题目描述

Ecrade 有一个整数 $x$。存在两种操作：

1. 将 $x$ 替换为 $\left\lfloor \dfrac{x}{2}\right\rfloor$，其中 $\left\lfloor \dfrac{x}{2}\right\rfloor$ 表示不大于 $\dfrac{x}{2}$ 的最大整数。
2. 将 $x$ 替换为 $\left\lceil \dfrac{x}{2}\right\rceil$，其中 $\left\lceil \dfrac{x}{2}\right\rceil$ 表示不小于 $\dfrac{x}{2}$ 的最小整数。

Ecrade 将**恰好执行** $n$ 次操作 1 和 $m$ 次操作 2，且操作顺序任意。他想知道在 $n + m$ 次操作后 $x$ 的**最小可能值**和**最大可能值**。这个问题似乎有些困难，请帮助他！

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来每个测试用例的描述如下：

每个测试用例的唯一一行包含三个整数 $x$，$n$，$m$（$0 \le x, n, m \le 10^9$）。

## 输出格式

对于每个测试用例，在一行中输出两个整数，分别表示操作后 $x$ 的最小可能值和最大可能值。

## 说明/提示

为简化描述，我们将操作 1 称为 $\text{OPER 1}$，操作 2 称为 $\text{OPER 2}$。

在第一个测试用例中：

- 若执行 $12 \xrightarrow{\text{OPER 2}} 6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 1}} 1$，可得到最小值 $1$。
- 若执行 $12 \xrightarrow{\text{OPER 2}} 6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 2}} 2$，可得到最大值 $2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
12 1 2
12 1 1
12 0 0
12 1000000000 1000000000
706636307 0 3
```

### 输出

```
1 2
3 3
12 12
0 0
88329539 88329539
```

