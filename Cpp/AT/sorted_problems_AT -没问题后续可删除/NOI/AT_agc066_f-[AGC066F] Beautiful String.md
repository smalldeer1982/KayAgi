---
title: "[AGC066F] Beautiful String"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_agc066_f
tag: ['贪心', '差分']
---

# [AGC066F] Beautiful String

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc066/tasks/agc066_f

次の条件を満たす文字列を，**美しい文字列**ということにします．

- どの文字も `A`, `B`, `C` のいずれかである．
- どの隣接する $ 2 $ 文字も相異なる．
 
例えば `AB`, `BCAC` は美しい文字列です．`BB`, `CBAAC` は美しい文字列ではありません．

- - - - - -

美しい文字列 $ S $ が与えられます．あなたはこの文字列に対して，次の操作を繰り返し行うことができます：

- 操作：$ S $ の隣接する $ 2 $ 文字をスワップする．ただしスワップ後の $ S $ も美しい文字列でなくてはならない．
 
最終的な文字列 $ S $ としてありうる辞書順最小の文字列を求めてください．

$ T $ 個のテストケースが与えられるので，それぞれについて答えを求めてください．

## 输入格式

入力は以下の形式で標準入力から与えられます．

> $ T $ $ \text{case}_1 $ $ \vdots $ $ \text{case}_T $

各テストケースは以下の形式で与えられます．

> $ S $

## 输出格式

$ T $ 行出力してください．$ i $ 行目には $ i $ 番目のテストケースについて，最終的な文字列 $ S $ としてありうる辞書順最小の文字列を出力してください．

## 说明/提示

### 制約

- $ 1\leq\ T\leq\ 10^5 $
- $ S $ は美しい文字列である．
- $ 1\leq\ |S|\leq\ 10^6 $
- $ 1 $ 個の入力に含まれるテストケースについて，それらの $ |S| $ の総和は $ 10^6 $ 以下である．
 
### Sample Explanation 1

$ 1 $ 番目，$ 2 $ 番目のテストケースについて，次が $ S $ を辞書順最小化する方法の一例となります． - `CAB` → `ACB` → `ABC` - `ACBCB` → `CABCB` → `CBACB` → `BCACB` → `BCABC` → `BACBC` → `ABCBC`

## 样例 #1

### 输入

```
8
CAB
ACBCB
B
AC
BACBA
BABABA
ABCBCAC
CBABACABCBABABC
```

### 输出

```
ABC
ABCBC
B
AC
ABABC
BABABA
ABCACBC
ABABACBCACBCBAB
```

