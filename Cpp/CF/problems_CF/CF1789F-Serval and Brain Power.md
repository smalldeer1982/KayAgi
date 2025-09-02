---
title: "Serval and Brain Power"
layout: "post"
diff: 省选/NOI-
pid: CF1789F
tag: []
---

# Serval and Brain Power

## 题目描述

定义一个字符串 $T$ 是好的，当且仅当存在字符串 $T'$ 和整数 $k(k\geq2)$，使得 $T$ 可以由 $k$ 个 $T'$ 首尾相接得到。  
例如，字符串 $\texttt{gogogo}$ 就是好的，因为它可以由 $3$ 个字符串 $\texttt{go}$ 首尾相接得到；而 $\texttt{power}$ 就不是好的。  
给定仅包含小写英文字母的字符串 $S$。  
你需要求出 $S$ 最长的好的子序列（不一定连续）的长度，特别的如果 $S$ 没有好的子序列，答案为 $0$。

## 输入格式

输入一行一个小写英文字母字符串表示 $S(|S|\leq80)$。

## 输出格式

输出一行一个整数表示 $S$ 中最长的好的子序列的长度。  
如果 $S$ 没有好的子序列，输出 $0$。

## 样例 #1

### 输入

```
buaa
```

### 输出

```
2
```

## 样例 #2

### 输入

```
codeforcesround
```

### 输出

```
6
```

## 样例 #3

### 输入

```
oooooooooooaaaaeaaiaujooooooooooooo
```

### 输出

```
24
```

## 样例 #4

### 输入

```
zero
```

### 输出

```
0
```

