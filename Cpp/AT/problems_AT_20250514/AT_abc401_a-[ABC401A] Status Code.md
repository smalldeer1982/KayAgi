---
title: "[ABC401A] Status Code"
layout: "post"
diff: 入门
pid: AT_abc401_a
tag: []
---

# [ABC401A] Status Code

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc401/tasks/abc401_a

给定一个介于 $100$ 以上 $999$ 以下的整数 $S$。

如果 $S$ 在 $200$ 以上 $299$ 以下，输出 `Success`；否则输出 `Failure`。

## 输入格式

输入通过标准输入给出，格式如下：

> $S$

## 输出格式

输出答案。

## 说明/提示

### 约束条件

- $100 \leq S \leq 999$
- $S$ 是整数

### 样例解释 1

因为 $200$ 在 $200$ 以上 $299$ 以下，所以输出 `Success`。

### 样例解释 2

因为 $401$ 不在 $200$ 以上 $299$ 以下，所以输出 `Failure`。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
200
```

### 输出

```
Success
```

## 样例 #2

### 输入

```
401
```

### 输出

```
Failure
```

## 样例 #3

### 输入

```
999
```

### 输出

```
Failure
```

