---
title: "[ABC295A] Probably English"
layout: "post"
diff: 入门
pid: AT_abc295_a
tag: []
---

# [ABC295A] Probably English

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc295/tasks/abc295_a

英小文字からなる $ N $ 個の文字列 $ W_1,W_2,\dots,W_N $ が与えられます。  
 これらのうち一つ以上が `and`, `not`, `that`, `the`, `you` のいずれかと一致するなら `Yes` 、そうでないなら `No` と出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ W_1 $ $ W_2 $ $ \dots $ $ W_N $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ N $ は $ 1 $ 以上 $ 100 $ 以下の整数
- $ 1\ \le\ |W_i|\ \le\ 50 $ ( $ |W_i| $ は文字列 $ W_i $ の長さ )
- $ W_i $ は英小文字からなる
 
### Sample Explanation 1

例えば $ W_4= $ `you` なので、 `Yes` と出力します。

### Sample Explanation 2

文字列 $ W_i $ はいずれも、 `and`, `not`, `that`, `the`, `you` のいずれとも一致しません。

## 样例 #1

### 输入

```
10
in that case you should print yes and not no
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
10
in diesem fall sollten sie no und nicht yes ausgeben
```

### 输出

```
No
```

