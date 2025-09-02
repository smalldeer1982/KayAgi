---
title: "Datatypes"
layout: "post"
diff: 普及/提高-
pid: CF108B
tag: []
---

# Datatypes

## 题目描述

Tattah's youngest brother, Tuftuf, is new to programming.

Since his older brother is such a good programmer, his biggest dream is to outshine him. Tuftuf is a student at the German University in Cairo (GUC) where he learns to write programs in Gava.

Today, Tuftuf was introduced to Gava's unsigned integer datatypes. Gava has $ n $ unsigned integer datatypes of sizes (in bits) $ a_{1},a_{2},...\ a_{n} $ . The $ i $ -th datatype have size $ a_{i} $ bits, so it can represent every integer between $ 0 $ and $ 2^{a_{i}}-1 $ inclusive.

Tuftuf is thinking of learning a better programming language. If there exists an integer $ x $ , such that $ x $ fits in some type $ i $ (in $ a_{i} $ bits) and $ x·x $ does not fit in some other type $ j $ (in $ a_{j} $ bits) where $ a_{i}&lt;a_{j} $ , then Tuftuf will stop using Gava.

Your task is to determine Tuftuf's destiny.

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=10^{5} $ ) — the number of Gava's unsigned integer datatypes' sizes. The second line contains a single-space-separated list of $ n $ integers ( $ 1<=a_{i}<=10^{9} $ ) — sizes of datatypes in bits. Some datatypes may have equal sizes.

## 输出格式

Print "YES" if Tuftuf will stop using Gava, and "NO" otherwise.

## 说明/提示

In the second example, $ x=7 $ $ (111_{2}) $ fits in $ 3 $ bits, but $ x^{2}=49 $ $ (110001_{2}) $ does not fit in $ 4 $ bits.

## 样例 #1

### 输入

```
3
64 16 32

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
4
4 2 1 3

```

### 输出

```
YES

```

