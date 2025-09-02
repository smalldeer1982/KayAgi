---
title: "じゃんけん式 (Rock-Scissors-Paper Expression)"
layout: "post"
diff: 难度0
pid: AT_joi2020_yo2_e
tag: []
---

# じゃんけん式 (Rock-Scissors-Paper Expression)

## 题目描述

在这个问题中，我们将"石头"、"剪刀"、"布"分别用符号 $\mathrm{R},\ \mathrm{S},\ \mathrm{P}$ 表示。其中，$\mathrm{R}$ 胜 $\mathrm{S}$，$\mathrm{S}$ 胜 $\mathrm{P}$，而 $\mathrm{P}$ 胜 $\mathrm{R}$。

对于两个手势 $x$ 和 $y$，定义三种特别的运算 $x + y$，$x - y$，$x * y$（注意这并不是我们熟悉的加法、减法和乘法，意义如下）：

- $x + y$：当 $x \ne y$ 时，取两个中获胜的一项；如果 $x = y$，则取 $x$。
- $x - y$：当 $x \ne y$ 时，取两个中失败的一项；如果 $x = y$，则取 $x$。
- $x * y$：当 $x \ne y$ 时，取 $\mathrm{R},\ \mathrm{S},\ \mathrm{P}$ 中既非 $x$ 也非 $y$ 的符号；如果 $x = y$，则取 $x$。

表达式由手势符号以及 $+,\ -, *$ 和括号组成，并遵循如下计算规则：

- 括号里的内容最优先计算。例如，$\mathrm{R} * (\mathrm{P} + \mathrm{S}) = \mathrm{R} * \mathrm{S} = \mathrm{P}$。
- 在括号深度相同的情况下：
  - 优先计算 $*$，再计算 $+$ 和 $-$。例如，$\mathrm{R} - \mathrm{P} * \mathrm{S} = \mathrm{R} - (\mathrm{P} * \mathrm{S}) = \mathrm{R} - \mathrm{R} = \mathrm{R}$。
  - 对于相同优先级的运算符，例如 $+$ 与 $+$、$-$ 与 $-$、$+$ 与 $-$、$*$ 与 $*$，依照从左到右的顺序计算。例如，$\mathrm{R} - \mathrm{P} + \mathrm{S} = (\mathrm{R} - \mathrm{P}) + \mathrm{S} = \mathrm{R} + \mathrm{S} = \mathrm{R}$。

JOI 遭遇了一个问题，他的手势表达式中有部分 $\mathrm{R},\ \mathrm{S},\ \mathrm{P}$ 被遮住了，用 `?` 代替。现在给定一个长度为 $N$ 的表达式字符串 $E$，包含若干 `?` 和可见的符号，JOI 想知道，如何替换这些 `?` 使得整个表达式的运算结果为 $A$ 的方法有多少种。由于方法数可能极大，要求对 $1\,000\,000\,007$ 取模。

表达式由 BNF (巴科斯-诺尔范式) 定义如下：

```
<expression> ::= <term> | <expression> "+" <term> | <expression> "-" <term>
<term> ::= <factor> | <term> "*" <factor>
<factor> ::= "R" | "S" | "P" | "?" | "(" <expression> ")"
```

这意味着，一个字符串是 &lt;expression&gt;，如果它是 &lt;term&gt;；或者是一个 &lt;expression&gt;，后跟 `+` 和一个 &lt;term&gt; 的组合；或是一个 &lt;expression&gt;，后跟 `-` 和一个 &lt;term&gt; 的组合。

现在给你一个 &lt;expression&gt; 类型的字符串 $E$ 和一个结果 $A$，请编写程序计算以不同方式替换 '?' 所形成的表达式 $E$ 的结果为 $A$ 的方案数，并输出该方案数对 $1\,000\,000\,007$ 取模的结果。

## 输入格式

输入以如下形式给出：

> $ N $ $ E $ $ A $

## 输出格式

输出一个整数，该整数表示将 `?` 替换为 $\mathrm{R},\ \mathrm{S},\ \mathrm{P}$ 中任意一个，使得表达式计算结果为 $A$ 的方案数量，最后需要对 $1\,000\,000\,007$ 取模。

## 说明/提示

- $1 \leq N \leq 200\,000$。
- $E$ 是长度为 $N$ 的字符串。
- $E$ 是描述中的 &lt;expression&gt;。
- $A$ 是 $\mathrm{R},\ \mathrm{S},\ \mathrm{P}$ 中的一个字符。

### 子任务

1. （20 分）$N \leq 15$。
2. （20 分）$N \leq 200$。
3. （60 分）无额外限制。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
11
S+?-(R+?)*P
S
```

### 输出

```
6
```

## 样例 #2

### 输入

```
15
?+?-?*?+?-?*?+?
R
```

### 输出

```
2187
```

## 样例 #3

### 输入

```
13
(((((R)))))+?
P
```

### 输出

```
1
```

## 样例 #4

### 输入

```
1
P
S
```

### 输出

```
0
```

## 样例 #5

### 输入

```
27
R+((?+S-?*P+?)-P*?+S-?)*R+?
P
```

### 输出

```
381
```

## 样例 #6

### 输入

```
83
((R+?)*(?+?))*((?+?)*(?+?))*((?+?)*(?+?))-((S+?)*(?+?))*((?+?)*(?+?))*((?+?)*(?+?))
P
```

### 输出

```
460353133
```

