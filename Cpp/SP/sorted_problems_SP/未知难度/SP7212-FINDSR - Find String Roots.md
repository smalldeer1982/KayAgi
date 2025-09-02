---
title: "FINDSR - Find String Roots"
layout: "post"
diff: 难度0
pid: SP7212
tag: []
---

# FINDSR - Find String Roots

## 题目描述

#### 题意翻译
在数学中，$\sqrt[n]{M}=K$，使得 $K^n= M$。即 $KKK...K = M$，$K$共乘$N$次。

我们可以把它转换成字符串。但在字符串表示法中，并置是串联而不是乘法。因此，如果有字符串$S$，$\sqrt[n]{S}$是另一个字符串$T$，使得 $T^n= S$，那么其中 $T^n = TTT…T$ 就是字符串$T$连接$N$次。例如，如果 $S =$ "$abcabcabcabc$"，对于 $N = 2$，字符串 $T =\sqrt[n]{S}=$ "$abcabc$"，而对于 $N = 4$，$T=\sqrt[n]{S}=$ "$abc$"。注意，对于 $N = 1$，任何字符串$S$的 $\sqrt[n]{S}=S$。

给定一个字符串$S$，你必须找到最大的$N$,使得 $\sqrt[n]{S}$ 存在。在上面的例子中，答案是$4$，因为当 $N>4$ 时，没有 $S =$ "$abcabcabc$" 情况下的 $\sqrt[n]{S}$。

## 输入格式

**本题有多组数据**。

对于每组数据：一个不超过 $10^5$ 字符的非空字符串$S$，完全由数字和小写字母组成。

最后一行包含一个星号 $(“*”)$，代表输入结束。

## 输出格式

对于每个$S$，输出一行一个最大整数$N$，使得存在字符串$T$连接$N$次后等于$S$。

## 样例 #1

### 输入

```
\nabcabcabcabc\nabcdefgh012\naaaaaaaaaa\n*\n\n
```

### 输出

```
4\n1\n10
```

