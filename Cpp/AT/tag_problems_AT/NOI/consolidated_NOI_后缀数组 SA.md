---
title: "[ARC175F] Append Same Characters"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_arc175_f
tag: ['后缀数组 SA']
---

# [ARC175F] Append Same Characters

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc175/tasks/arc175_f

英小文字からなる $ N $ 個の文字列 $ S_1,\ \dots,\ S_N $ が与えられます．以下の $ 2 $ 種類の操作を好きな順番で $ 0 $ 回以上好きな回数行うことを考えます．

- 英小文字 $ c $ を $ 1 $ つ選ぶ．全ての $ 1\ \leq\ i\leq\ N $ について，$ S_i $ の末尾に $ c $ を追加する．
- $ 1\ \leq\ i\ \leq\ N-1 $ を満たす整数 $ i $ を $ 1 $ つ選ぶ．$ S_i $ と $ S_{i+1} $ を入れ替える．
 
全ての操作の終了後に，辞書順で $ S_i\ \leq\ S_{i+1} $ が各 $ 1\ \leq\ i\ \leq\ N-1 $ について成り立つようにするとき，操作の合計回数の最小値を求めてください．

  辞書順とは文字列 $ S\ =\ S_1S_2\ldots\ S_{|S|} $ が文字列 $ T\ =\ T_1T_2\ldots\ T_{|T|} $ より**辞書順で小さい**とは，下記の 1. と 2. のどちらかが成り立つことを言います． ここで，$ |S|,\ |T| $ はそれぞれ $ S,\ T $ の長さを表します．

1. $ |S|\ \lt\ |T| $ かつ $ S_1S_2\ldots\ S_{|S|}\ =\ T_1T_2\ldots\ T_{|S|} $．
2. ある整数 $ 1\ \leq\ i\ \leq\ \min\lbrace\ |S|,\ |T|\ \rbrace $ が存在して，下記の $ 2 $ つがともに成り立つ． 
  - $ S_1S_2\ldots\ S_{i-1}\ =\ T_1T_2\ldots\ T_{i-1} $．
  - $ S_i $ が $ T_i $ よりアルファベット順で小さい文字である．

## 输入格式

入力は以下の形式で標準入力から与えられる．

> $ N $ $ S_1 $ $ S_2 $ $ \vdots $ $ S_N $

## 输出格式

答えを $ 1 $ 行に出力せよ．

## 说明/提示

### 制約

- 入力される数値は全て整数
- $ 2\ \le\ N\ \le\ 3\ \times\ 10^5 $
- $ S_i $ は英小文字からなる文字列
- $ 1\ \le\ |S_i| $
- $ |S_1|\ +\ |S_2|\ +\ \dots\ +\ |S_N|\ \le\ 3\ \times\ 10^5 $
 
### Sample Explanation 1

操作の一例を示します． - $ S_2 $ と $ S_3 $ を入れ替える．$ (S_1,\ \ldots,\ S_5)\ =\ ( $`ab`, `a`, `rac`, `dab`, `ra`$ ) $ となる． - 各文字列の末尾に `z` を追加する．$ (S_1,\ \ldots,\ S_5)\ =\ ( $`abz`, `az`, `racz`, `dabz`, `raz`$ ) $ となる． - $ S_3 $ と $ S_4 $ を入れ替える．$ (S_1,\ \ldots,\ S_5)\ =\ ( $`abz`, `az`, `dabz`, `racz`, `raz`$ ) $ となる．このとき全ての $ i\ =\ 1,\ \ldots,\ N-1 $ について $ S_i\ \leq\ S_{i+1} $ が満たされている． $ 3 $ 回未満の操作により，全ての $ i\ =\ 1,\ \ldots,\ N-1 $ について $ S_i\ \leq\ S_{i+1} $ が満たされている状態にすることはできないので，$ 3 $ を出力します．

### Sample Explanation 2

操作を行う前の時点で，全ての $ i\ =\ 1,\ \ldots,\ N-1 $ について $ S_i\ \leq\ S_{i+1} $ が満たされています．

### Sample Explanation 3

$ i\ \neq\ j $ に対して $ S_i\ =\ S_j $ となりうることに注意してください．

## 样例 #1

### 输入

```
5

ab

rac

a

dab

ra
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3

kitekuma

nok

zkou
```

### 输出

```
0
```

## 样例 #3

### 输入

```
31

arc

arrc

rc

rac

a

rc

aara

ra

caac

cr

carr

rrra

ac

r

ccr

a

c

aa

acc

rar

r

c

r

a

r

rc

a

r

rc

cr

c
```

### 输出

```
175
```



---

