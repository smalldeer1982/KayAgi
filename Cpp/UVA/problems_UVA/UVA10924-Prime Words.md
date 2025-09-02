---
title: "Prime Words"
layout: "post"
diff: 普及-
pid: UVA10924
tag: []
---

# Prime Words

## 题目描述

质数是指只有两个除数的数：它本身和数字 $1$。例如 $1$、$2$、$3$、$5$、$17$、$101$ 和 $10007$。

在这个问题中，你需要读取一组单词，每个单词仅由范围 $\texttt{a-z}$ 和 $\texttt{A-Z}$ 之间的字母组成。每个字母都有特定的值，字母 $\tt a$ 的值是 $1$，字母 $\tt b$ 的值是 $2$，依此类推，直到字母 $\tt z$ 的值是 $26$。同样，字母 $\tt A$ 的值是 $27$，字母 $\tt B$ 的值是 $28$，直到字母 $\tt Z$ 的值是 $52$。

你需要编写一个程序来确定一个单词是否为质数单词。如果一个单词的字母总和值是一个质数，那么这个单词就是一个质数单词。

## 输入格式

输入由一组单词组成。每个单词独占一行，且长度为 $L$ 个字母，其中 $1 \le L \le 20$。输入以文件结束标记（EOF）终止。

## 输出格式

对于每个单词，如果单词的字母总和值是一个质数，你应输出：$\texttt{It is a prime word.}$；否则输出：$\texttt{It is not a prime word.}$。

---

Translated by User 735713.

## 样例 #1

### 输入

```
UFRN
contest
AcM
```

### 输出

```
It is a prime word.
It is not a prime word.
It is not a prime word.
```

