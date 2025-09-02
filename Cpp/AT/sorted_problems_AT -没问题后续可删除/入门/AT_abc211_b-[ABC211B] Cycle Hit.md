---
title: "[ABC211B] Cycle Hit"
layout: "post"
diff: 入门
pid: AT_abc211_b
tag: []
---

# [ABC211B] Cycle Hit

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc211/tasks/abc211_b

$ 4 $ つの文字列 $ S_1,\ S_2,\ S_3,\ S_4 $ が与えられます。  
 この中に、`H` , `2B` , `3B` , `HR` がそれぞれ $ 1 $ つずつあるか判定してください。   
 ただし、全ての $ S_i $ は `H` , `2B` , `3B` , `HR` のいずれかと一致します。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S_1 $ $ S_2 $ $ S_3 $ $ S_4 $

## 输出格式

`H` , `2B` , `3B` , `HR` がそれぞれ $ 1 $ つずつあるならば `Yes` と出力せよ。  
 そうでないならば `No` と出力せよ。

## 说明/提示

### 制約

- $ S_i $ は `H` , `2B` , `3B` , `HR` のいずれかと一致する

### Sample Explanation 1

`H` , `2B` , `3B` , `HR` がそれぞれ $ 1 $ つずつあります。

### Sample Explanation 2

`H` がありません。

## 样例 #1

### 输入

```
3B
HR
2B
H
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2B
3B
HR
3B
```

### 输出

```
No
```

