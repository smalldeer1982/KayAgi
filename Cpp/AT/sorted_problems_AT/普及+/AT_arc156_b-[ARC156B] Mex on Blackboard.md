---
title: "[ARC156B] Mex on Blackboard"
layout: "post"
diff: 普及+/提高
pid: AT_arc156_b
tag: ['组合数学', '排列组合']
---

# [ARC156B] Mex on Blackboard

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc156/tasks/arc156_b

有限個の非負整数からなる多重集合 $ S $ にたいして、$ \mathrm{mex}(S) $ を、$ S $ に含まれない最小の非負整数と定義します。例えば、$ \mathrm{mex}(\lbrace\ 0,0,\ 1,3\rbrace\ )\ =\ 2,\ \mathrm{mex}(\lbrace\ 1\ \rbrace)\ =\ 0,\ \mathrm{mex}(\lbrace\ \rbrace)\ =\ 0 $ です。

黒板に $ N $ 個の非負整数が書かれており、$ i $ 番目の非負整数は $ A_i $ です。

あなたは、以下の操作をちょうど $ K $ 回行います。

- 黒板に書かれている非負整数を $ 0 $ 個以上選ぶ。選んだ非負整数からなる多重集合を $ S $ として、$ \mathrm{mex}(S) $ を黒板に $ 1 $ 個書き込む。
 
最終的に黒板に書かれている非負整数の多重集合としてありうるものの個数を $ 998244353 $ で割ったあまりを求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ K $ $ A_1 $ $ A_2 $ $ \ldots $ $ A_N $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N,K\ \leq\ 2\times\ 10^5 $
- $ 0\leq\ A_i\leq\ 2\times\ 10^5 $
- 入力される数値は全て整数
 
### Sample Explanation 1

操作後に得られる多重集合は、以下の $ 3 $ 通りです。 - $ \lbrace\ 0,0,1,3\ \rbrace $ - $ \lbrace\ 0,1,1,3\rbrace $ - $ \lbrace\ 0,1,2,3\ \rbrace $ 例えば、$ \lbrace\ 0,1,1,3\rbrace $ は黒板に書かれている $ 0 $ を選び、$ S=\lbrace\ 0\rbrace $ として操作をすることで得られます。

### Sample Explanation 2

操作後に得られる多重集合は、以下の $ 2 $ 通りです。 - $ \lbrace\ 0,0,0\ \rbrace $ - $ \lbrace\ 0,0,1\rbrace $ 操作で選ぶ整数は $ 0 $ 個でも良いことに注意してください。

## 样例 #1

### 输入

```
3 1
0 1 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 1
0 0
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 10
3 1 4 1 5
```

### 输出

```
7109
```

