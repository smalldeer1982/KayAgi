---
title: "DNPALIN - Double Near Palindromes"
layout: "post"
diff: 难度0
pid: SP3388
tag: []
---

# DNPALIN - Double Near Palindromes

## 题目描述

### 题意简述

回文是一个单词或一个或多个字母的序列，前后读法相同。近回文是一个单词或序列，可以通过将一个字母改为另一个字母来更改为或保持回文。例如 `BAT` 是一个近回文的词，因为将 `T` 改为 `B` 会使这个词变成回文：`BAB`。而 `PEEP` 不是近回文：虽然 `PEEP` 是回文，但更改任何字母都会使其不回文。双近回文是由两个连接在一起的近回文组成的单词或序列。例如，`BATMAN` 是双近回文，因为 `BAT` 和 `MAN` 都是近回文。现给定一个单词列表，你要确定哪些单词是双近回文，哪些不是。

## 输入格式

输入由一个或多个单词组成。所有单词（最后一个除外）的长度在 1 到 25 个字母之间，全部由大写字母组成。最后一个单词将是 `*END*`，并且不会被处理；它只是指示输入的结束。

## 输出格式

对于输入的单词，您需要回答其是或不是一个双近回文。

## 样例 #1

### 输入

```
BATMAN
CONSTANTINOPLE
*END*
```

### 输出

```
BATMAN is a double near palindrome.
CONSTANTINOPLE is not a double near palindrome.
```

