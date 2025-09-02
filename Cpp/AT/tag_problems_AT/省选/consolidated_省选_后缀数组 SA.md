---
title: "Smaller-Suffix-Free Sequences"
layout: "post"
diff: 省选/NOI-
pid: AT_ddcc2020_final_c
tag: ['后缀数组 SA']
---

# Smaller-Suffix-Free Sequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ddcc2020-final/tasks/ddcc2020_final_c

数列 $ T\ =\ (T_1,\ \ldots,\ T_L) $ が smaller-suffix-free であるとは、 $ i\ =\ 2,\ 3,\ \ldots,\ L $ 全てについて、 数列 $ (T_i,\ T_{i+1},\ \ldots,\ T_L) $ が 辞書順で $ T $ よりも大きいことを指します。 たとえば $ (5) $ や $ (1,\ 1,\ 2,\ 3) $ はsmaller-suffix-freeであり、$ (3,\ 2,\ 1) $ や $ (2,\ 2) $ は smaller-suffix-free ではありません。

長さ $ N $ の数列 $ A\ =\ (A_1,\ \ldots,\ A_N) $ が与えられます。 各 $ i\ =\ 1,\ \ldots,\ N $ について、$ (A_i,\ A_{i+1},\ \ldots,\ A_j) $ が smaller-suffix-free であるような最大の $ j $ を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ \ldots $ $ A_N $

## 输出格式

出力は $ N $ 行からなる。

$ i $ 行目には $ (A_i,\ A_{i+1},\ \ldots,\ A_j) $ が smaller-suffix-free であるような最大の $ j $ を出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 2\ \times\ 10^5\ (1\ \leq\ i\ \leq\ N) $

### Sample Explanation 1

$ A_1 $ から始まる smaller-suffix-free である 最長の連続する部分列は $ (A_1)\ =\ (3) $ です。したがって $ 1 $ 行目には $ 1 $ を出力します。 同様に、$ (A_2),\ (A_3,\ A_4,\ A_5,\ A_6),\ (A_4,\ A_5,\ A_6),\ (A_5,\ A_6),\ (A_6) $ がそれぞれ $ A_i\ (2\ \leq\ i\ \leq\ 6) $ から始まる smaller-suffix-free である最長の連続する部分列です。

## 样例 #1

### 输入

```
6

3 2 1 1 2 3
```

### 输出

```
1

2

6

6

6

6
```

## 样例 #2

### 输入

```
3

10 10 10
```

### 输出

```
1

2

3
```



---

---
title: "Analyzing Bit (Yet Special) Strings"
layout: "post"
diff: 省选/NOI-
pid: AT_icpc2015summer_day3_a
tag: ['并查集', '后缀自动机 SAM', '后缀数组 SA']
---

# Analyzing Bit (Yet Special) Strings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2015summer-day3/tasks/icpc2015summer_day3_a





---

---
title: "Golf"
layout: "post"
diff: 省选/NOI-
pid: AT_pakencamp_2021_day2_o
tag: ['线段树', '后缀数组 SA']
---

# Golf

## 题目描述

给定一个字符串 $S$。定义子串 $S[i:j]$ 表示从字符串 $S$ 的第 $i$ 个字符到第 $j$ 个字符组成的子串。

如果子串 $T$ 满足以下条件，则称其为一个「好字符串」：

- 长度在 1 到 $|S|$ 之间，即 $1 \leq |T| \leq |S|$
- 恰好存在唯一一个整数 $i$，使得 $S[i:i+|T|-1]$ 与 $T$ 相等

例如，若字符串 $S$ 为 `abcbabc`，那么 `cb`、`abcb` 和 `abcbabc` 都是「好字符串」，但 `abc` 和 `zyx` 不是。

接下来有 $Q$ 个查询。对于第 $i$ 个查询，给出两个整数 $L_i$ 和 $R_i$，满足 $1 \leq L_i \leq R_i \leq |S|$，然后解决以下问题：

- 寻找两个整数 $l$ 和 $r$，使得 $1 \leq l \leq L_i$ 且 $R_i \leq r \leq |S|$，并使得子串 $S[l:r]$ 是一个「好字符串」。然后计算 $r-l+1$ 的最小可能值。

## 输入格式

输入通过标准输入提供，格式如下：

> $ S $ $ Q $ $ L_1 $ $ R_1 $ $ L_2 $ $ R_2 $ $ \vdots $ $ L_Q $ $ R_Q $

## 输出格式

输出 $Q$ 行。对于每个查询，第 $i$ 行输出对应查询的结果。

## 说明/提示

- 字符串 $S$ 仅由小写英文字母组成。
- $1 \leq |S| \leq 200,000$
- $1 \leq Q \leq 200,000$
- 对于每个 $i$，满足 $1 \leq L_i \leq R_i \leq |S|$

### 样例解释

对于第一个查询，我们可以取 $l=2, r=4$，此时 $r-l+1=3$，这是最小值。注意 `bc` 不是「好字符串」，所以不能取 $l=2, r=3$。在第二个查询中，取 $l=2, r=5$，得到 $r-l+1=4$，是最小值。在第三个查询中，我们取 $l=1, r=7$，则 $r-l+1=7$，这是最小值。值得注意的是，字符串 $S$ 本身是一个「好字符串」。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
abcbabc

5

2 3

2 5

1 7

4 4

6 6
```

### 输出

```
3

4

7

2

3
```

## 样例 #2

### 输入

```
yyxxzzyyxx

5

3 3

1 1

10 10

5 5

7 7
```

### 输出

```
3

5

5

2

2
```

## 样例 #3

### 输入

```
qprrrrrpprqrrppq

20

7 8

6 8

4 7

7 12

6 7

5 5

6 8

4 6

4 4

2 3

7 11

8 9

6 7

11 12

11 15

5 6

4 5

13 13

9 13

5 7
```

### 输出

```
4

4

5

6

4

4

4

5

3

3

5

3

4

2

5

4

4

3

5

4
```



---

