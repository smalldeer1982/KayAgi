---
title: "IITWPC4H - Maggu and Cuteness of Strings"
layout: "post"
diff: 难度0
pid: SP18283
tag: []
---

# IITWPC4H - Maggu and Cuteness of Strings

## 题目描述

给定两个字符串 $s$ 和 $t$，它们的长度分别为 $n$ 和 $m$。你需要构造一个新字符串 $w$，它的长度为 $n+m$，要求 $w$ 同时包含 $s$ 和 $t$ 作为其子序列。$w$ 必须满足以下条件：对于每个从 'a' 到 'z' 的字母，在字符串 $w$ 中，这个字母出现的次数必须等于它在 $s$ 中和 $t$ 中出现次数的总和。此外，$w$ 中的每个字符必须存在于 $s$ 或 $t$ 的子序列中。

例如，如果 $s = \text{ab}$ 且 $t = \text{cd}$，那么 $w$ 可以是 $\text{abcd}$、$\text{acbd}$、$\text{cdab}$、$\text{cabd}$、$\text{acdb}$、$\text{cadb}$。注意，$\text{adcb}$ 是不合适的，因为 $t$ 不是它的子序列。

字符串的“可爱值”被定义为该字符串中最长连续相同字符出现的次数。

对于所有可能构造的字符串 $w$，求出“可爱值”的最大值。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1\nab ab
```

### 输出

```
2
```

