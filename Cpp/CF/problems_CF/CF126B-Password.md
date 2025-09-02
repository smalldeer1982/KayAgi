---
title: "Password"
layout: "post"
diff: 普及+/提高
pid: CF126B
tag: ['字符串', '枚举', 'KMP 算法', '标签474']
---

# Password

## 题目描述

Asterix，Obelix 和他们的临时伙伴 Suffix、Prefix 已经最终找到了和谐寺。然而和谐寺大门紧闭，就连 Obelix 的运气也没好到能打开它。

不久他们发现了一个字符串 $S\ (1\leqslant\vert S\vert\leqslant1000000)$，刻在和谐寺大门下面的岩石上。Asterix 猜想那一定是打开寺庙大门的密码，于是就大声将字符串朗读了出来，然而并没有什么事发生。于是 Asterix 又猜想密码一定是字符串 $S$ 的子串 $T$。

Prefix 认为 $T$ 是 $S$ 的前缀，Suffix 认为 $T$ 是 $S$ 的后缀，Obelix 却认为 $T$ 应该是 $S$ 中的某一部分，也就是说，$T$ 既不是 $S$ 的前缀，也不是 $S$ 的后缀。

Asterix 选择子串 $T$ 来满足所有伙伴们的想法。同时，在所有可以被接受的子串变形中，Asterix 选择了最长的一个。当 Asterix 大声读出子串 $T$ 时，寺庙的大门开了。（也就是说，你需要找到既是 $S$ 的前缀又是 $S$ 的后缀同时又在 $S$ 中间出现过的最长子串）

现在给你字符串 $S$，你需要找到满足上述要求的子串 $T$。

## 输入格式

一行一个只包含小写字母的字符串 $S$。

## 输出格式

输出子串 $T$，如果 $T$ 不存在，输出 `Just a legend`。

## 样例 #1

### 输入

```
fixprefixsuffix

```

### 输出

```
fix
```

## 样例 #2

### 输入

```
abcdabc

```

### 输出

```
Just a legend
```

