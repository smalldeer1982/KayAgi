---
title: "Propagating Edges"
layout: "post"
diff: 提高+/省选-
pid: AT_soundhound2018_summer_final_d
tag: ['并查集', 'Kruskal 重构树']
---

# Propagating Edges

## 题目描述

[problemUrl]: https://atcoder.jp/contests/soundhound2018-summer-final/tasks/soundhound2018_summer_final_d

$ N $ 頂点 $ 0 $ 辺の無向グラフが与えられます。以下のクエリを $ Q $ 個処理して下さい。

- addクエリ($ type\ =\ 1,\ u,\ v $): $ u $ と $ v $ の間に辺が無ければ辺を貼る。
- completeクエリ($ type\ =\ 2,\ u,\ v\ =\ 0 $): 全ての頂点対 $ a,\ b $ について以下を行う, $ u,\ a,\ b $ がすべて連結で，かつ $ a,\ b $ 間に辺がない場合，$ a,\ b $ の間に辺を貼る。
- checkクエリ($ type\ =\ 3,\ u,\ v $): $ u,\ v $ が与えられる。$ u $ と $ v $ を直接結ぶ辺がある場合`Yes`、そうでない場合`No`を出力する。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ Q $ $ type_1 $ $ u_1 $ $ v_1 $ $ type_2 $ $ u_2 $ $ v_2 $ $ : $ $ type_Q $ $ u_Q $ $ v_Q $

## 输出格式

各checkクエリに対し、`Yes`か`No`を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100,000 $
- $ 1\ \leq\ Q\ \leq\ 200,000 $
- $ type_i\ =\ 1,\ 2,\ 3 $
- $ 1\ \leq\ u_i\ \leq\ N $
- add, checkクエリにおいて $ 1\ \leq\ v_i\ \leq\ N $ かつ $ u_i\ \neq\ v_i $
- completeクエリにおいて $ v_i\ =\ 0 $
- 入力される値は全て整数である

### Sample Explanation 1

$ 1,\ 2 $ つ目のクエリで$ (1,\ 2) $, $ (2,\ 3) $に辺が張られます。 そして、$ 5 $ つ目のクエリで$ (1,\ 3) $ 間に辺が張られます。

## 样例 #1

### 输入

```
3 6
1 1 2
1 2 3
3 1 2
3 1 3
2 1 0
3 1 3
```

### 输出

```
Yes
No
Yes
```

## 样例 #2

### 输入

```
3 6
2 3 0
3 1 3
1 3 1
2 3 0
1 1 2
3 2 1
```

### 输出

```
No
Yes
```

## 样例 #3

### 输入

```
8 20
1 3 6
2 6 0
2 2 0
2 7 0
1 7 3
3 2 6
1 4 2
3 3 7
1 2 6
2 4 0
2 2 0
3 3 1
2 8 0
2 8 0
1 8 2
2 7 0
3 5 4
1 4 2
3 5 7
3 2 3
```

### 输出

```
No
Yes
No
No
No
Yes
```

