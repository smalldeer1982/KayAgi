---
title: "Reverse Grid"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_codefestival_2016_final_i
tag: ['线性基']
---

# Reverse Grid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/cf16-final/tasks/codefestival_2016_final_i

縦 $ H $ 行、横 $ W $ 列のマス目があり、$ i $ 行目の $ j $ 列目のマスには文字 $ S_{i,j} $ が書かれています。

すぬけくんはこのマス目に対して以下の $ 2 $ 種類の操作を行うことが出来ます。

- 行リバース：行を $ 1 $ つ選び、その行をリバースする。
- 列リバース：列を $ 1 $ つ選び、その列をリバースする。

例えば、$ 2 $ 行目をリバースした後に $ 4 $ 列目をリバースすると以下のように変化します。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_codefestival_2016_final_i/2c78e6cf67ba2ff8a353121894255544acf43c84.png)

上記の操作を好きな順番で何回か行うことによって作ることの出来る文字の配置は何通り考えられるでしょうか？

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ H $ $ W $ $ S_{1,1} $$ S_{1,2} $$ ... $$ S_{1,W} $ $ S_{2,1} $$ S_{2,2} $$ ... $$ S_{2,W} $ $ : $ $ S_{H,1} $$ S_{H,2} $$ ... $$ S_{H,W} $

## 输出格式

答えを $ 1000000007\ (=10^9+7) $ で割ったあまりを出力せよ。

## 说明/提示

### 制約

- $ 1≦H,W≦200 $
- $ S_{i,j} $ は小文字アルファベット（`a`-`z`）である。

### Sample Explanation 1

以下の $ 6 $ 通りの配置が考えられます。 !\[\](https://atcoder.jp/img/code-festival-2016-final/ddf2925467af2c9734194a886f819a2b.png)

## 样例 #1

### 输入

```
2 2
cf
cf
```

### 输出

```
6
```

## 样例 #2

### 输入

```
1 12
codefestival
```

### 输出

```
2
```

