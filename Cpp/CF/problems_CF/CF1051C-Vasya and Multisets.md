---
title: "Vasya and Multisets"
layout: "post"
diff: 普及+/提高
pid: CF1051C
tag: []
---

# Vasya and Multisets

## 题目描述

Vasya has a multiset $ s $ consisting of $ n $ integer numbers. Vasya calls some number $ x $ nice if it appears in the multiset exactly once. For example, multiset $ \{1, 1, 2, 3, 3, 3, 4\} $ contains nice numbers $ 2 $ and $ 4 $ .

Vasya wants to split multiset $ s $ into two multisets $ a $ and $ b $ (one of which may be empty) in such a way that the quantity of nice numbers in multiset $ a $ would be the same as the quantity of nice numbers in multiset $ b $ .

## 输入格式

The first line contains a single integer $ n~(2 \le n \le 100) $ .

The second line contains $ n $ integers $ s_1, s_2, \dots s_n~(1 \le s_i \le 100) $ — the multiset $ s $ .

## 输出格式

If there exists no split of $ s $ to satisfy the given requirements, then print "NO" in the first line.

Otherwise print "YES" in the first line.

The second line should contain a string, consisting of $ n $ characters. $ i $ -th character should be equal to 'A' if the $ i $ -th element of multiset $ s $ goes to multiset $ a $ and 'B' if if the $ i $ -th element of multiset $ s $ goes to multiset $ b $ . Elements are numbered from $ 1 $ to $ n $ in the order they are given in the input.

If there exist multiple solutions, then print any of them.

## 样例 #1

### 输入

```
4
3 5 7 1

```

### 输出

```
YES
BABA

```

## 样例 #2

### 输入

```
3
3 5 1

```

### 输出

```
NO

```

