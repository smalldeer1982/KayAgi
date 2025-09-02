---
title: "[ARC145D] Non Arithmetic Progression Set"
layout: "post"
diff: 提高+/省选-
pid: AT_arc145_d
tag: []
---

# [ARC145D] Non Arithmetic Progression Set

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc145/tasks/arc145_d

以下の条件を全て満たす整数集合 $ S $ を一つ構築してください。なお、この問題の制約下で条件を満たす $ S $ が少なくとも一つ存在することが証明できます。

- $ S $ の要素数は $ N $
- $ S $ の要素は $ -10^7 $ 以上 $ 10^7 $ 以下の相異なる整数
- $ \displaystyle\ \sum\ _{s\ \in\ S}\ s\ =\ M $
- $ S $ の任意の相異なる要素 $ x,y,z $ $ (x\ <\ y\ <\ z) $ について $ y-x\neq\ z-y $

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $

## 输出格式

$ S $ の要素を $ s_1,s_2,\ldots,s_N $ とする。条件を満たす $ S $ を $ 1 $ つ以下の形式で出力せよ。

> $ s_1 $ $ s_2 $ $ \ldots $ $ s_N $

条件を満たす解が複数存在する場合、どれを出力しても正解とみなされる。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^4 $
- $ |M|\ \leq\ N\times\ 10^6 $
- 入力は全て整数

### Sample Explanation 1

$ 2-1\ \neq\ 6-2 $ であり、 $ 1+2+6=9 $ なのでこの出力は条件を満たします。他にも様々な答えが考えられます。

### Sample Explanation 2

$ M $ が負のこともあります。

## 样例 #1

### 输入

```
3 9
```

### 输出

```
1 2 6
```

## 样例 #2

### 输入

```
5 -15
```

### 输出

```
-15 -5 0 2 3
```

