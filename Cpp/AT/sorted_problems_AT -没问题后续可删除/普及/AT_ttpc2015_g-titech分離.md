---
title: "titech分離"
layout: "post"
diff: 普及/提高-
pid: AT_ttpc2015_g
tag: []
---

# titech分離

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ttpc2015/tasks/ttpc2015_g

英小文字(a-z)からなる文字列$ S $が与えられる。

$ S $をいくつかの(連続とは限らない)部分文字列に分解する。 つまり、$ S $の各文字がちょうど1つの部分文字列に含まれるように、$ S $から複数の部分文字列を選ぶ。

分解した結果の部分文字列が全て`titech`になるような分解方法があるかどうか判定せよ。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

- $ 1 $ 行目に文字列$ S(1\ ≦\ |\ S\ |\ ≦\ 100) $が与えられる。

## 输出格式

分解が可能なら`Yes`、不可能なら`No`を出力せよ。 出力の末尾に改行を入れること。

## 说明/提示

### Sample Explanation 1

1つの`titech`に分解できる。

### Sample Explanation 2

例えば、1,2,5,6,7,8文字目と3,4,9,10,11,12文字目に分解すれば2つの`titech`に分解できる。

### Sample Explanation 4

3つの`titech`に分解できる。

## 样例 #1

### 输入

```
titech
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
tititechtech
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
titecg
```

### 输出

```
No
```

## 样例 #4

### 输入

```
tttiiittteeeccchhh
```

### 输出

```
Yes
```

