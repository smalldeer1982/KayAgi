---
title: "Half Palindromes"
layout: "post"
diff: 难度0
pid: AT1202Contest_e
tag: []
---

# Half Palindromes

## 题目描述

给定一个由小写英文字母组成的字符串 $ S $。对于 $ S $ 的所有连续子串，共有 $ \lceil \lvert S \rvert \div 2 \rceil$ 个，针对每个子串解决以下问题，并求解所有解的总和。

问题：给定一个由小写英文字母组成的字符串 $ T $。请找出 $ T $ 可以通过以下操作任意多次得到的最小长度。
- 操作：从 $ T $ 的前缀中选择一个奇数长度的回文串（假设长度为 $ 2k+1 $），删除 $ T $ 的前 $ k $ 个字符。

## 输入格式

从标准输入中给出输入，具有以下格式：
> $ S $

## 输出格式

输出答案。
### 约束
- $ 1 \leq \lvert S \rvert \leq 10^6 $
- $ S $ 由小写英文字母组成

Translate by [@XYQ_102](https://www.luogu.com.cn/user/712337)

## 样例 #1

### 输入

```
abab
```

### 输出

```
16
```

## 样例 #2

### 输入

```
abacaba
```

### 输出

```
67
```

## 样例 #3

### 输入

```
tabatadebatabata
```

### 输出

```
739
```

