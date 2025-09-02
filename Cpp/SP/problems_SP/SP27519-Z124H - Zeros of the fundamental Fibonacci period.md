---
title: "Z124H - Zeros of the fundamental Fibonacci period"
layout: "post"
diff: 难度0
pid: SP27519
tag: []
---

# Z124H - Zeros of the fundamental Fibonacci period

## 题目描述

我们知道，斐波那契数列在模 $p$ 取余后经常会呈现出周期性的特征。

例如：
- 对 2 取模：$F \mod 2 = \textbf{0 1 1} \ 0 1 1 \ 0 1 \ldots$
- 对 3 取模：$F \mod 3 = \textbf{0 1 1 2 0 2 2 1} \ 0 1 1 2 \ldots$
- 对 5 取模：$F \mod 5 = \textbf{0 1 1 2 3 0 3 3 1 4 0 4 4 3 2 0 2 2 4 1} \ 0 1 1 2 3 \ldots$

在这里，我们用 $Z(p)$ 表示斐波那契数列在模 $p$ 下的基本周期内零出现的次数（假设它具有周期性）。从上面的例子中可以看出，$Z(2) = 1$，$Z(3) = 2$，$Z(5) = 4$。

## 输入格式

第一行为整数 $T$，表示测试用例的数量。接下来的 $T$ 行中，每行包含一个质数 $p$。

## 输出格式

对于每个测试用例，输出 $Z(p)$。如果斐波那契数列在模 $p$ 下没有周期性，输出 `Not periodic.`（不带引号）。

## 说明/提示

- $1 \le T \le 10^5$
- $2 \le p \le 10^9$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
2
3
5
```

### 输出

```
1
2
4
```

