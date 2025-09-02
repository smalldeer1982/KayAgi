---
title: "[ARC172C] Election"
layout: "post"
diff: 普及+/提高
pid: AT_arc172_c
tag: ['数学']
---

# [ARC172C] Election

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc172/tasks/arc172_c

今年の AtCoder 市長選挙には A 候補と B 候補の $ 2 $ 人が立候補し、$ N $ 人の有権者が投票しました。 投票者にはそれぞれ $ 1 $ から $ N $ までの番号が付けられており、投票者 $ i $ $ (1\ \leq\ i\ \leq\ N) $ は $ c_i $ 候補に投票しました。

さて、これから開票作業が行われます。 開票作業では $ 1 $ 票ずつ票が開けられていき、票が開けられるたびに、現時点での開票結果が以下の $ 3 $ つのうちどれであるかが発表されます。

- **結果 A:** 現時点で、A 候補の方が獲得票数が多い。
- **結果 B:** 現時点で、B 候補の方が獲得票数が多い。
- **結果 C:** 現時点で、A 候補と B 候補の獲得票数が同数である。
 
ここで開票の順番にはルールがあり、投票者 $ 1 $ 以外の票は、投票者の番号の小さい順に開票されなければなりません。 (投票者 $ 1 $ の票は好きなタイミングで開票してかまいません)

発表される開票結果の列としてあり得るものが何通りあるかを答えてください。

 開票結果の列とは$ i $ 票目 $ (1\ \leq\ i\ \leq\ N) $ が開けられたタイミングで報告された結果を $ s_i $ (`A`, `B`, `C` のいずれか) とするとき，文字列 $ s_1\ s_2\ \dots\ s_N $ のことを指します。

## 输入格式

入力は以下の形式で標準入力から与えられます。

> $ N $ $ c_1\ c_2\ \cdots\ c_N $

## 输出格式

答えを出力してください。

## 说明/提示

### 制約

- $ N $ は $ 2\ \leq\ N\ \leq\ 1000000 $ を満たす整数
- $ c_1,\ c_2,\ \dots,\ c_N $ は `A` または `B`
 
### Sample Explanation 1

この入力例では、開票が行われる順番として以下の $ 4 $ 通りが考えられます。 - 投票者 $ 1\ \to\ 2\ \to\ 3\ \to\ 4 $ の順に開票が行われる。 - 投票者 $ 2\ \to\ 1\ \to\ 3\ \to\ 4 $ の順に開票が行われる。 - 投票者 $ 2\ \to\ 3\ \to\ 1\ \to\ 4 $ の順に開票が行われる。 - 投票者 $ 2\ \to\ 3\ \to\ 4\ \to\ 1 $ の順に開票が行われる。 開票結果の列は上から順に `AAAC`、`AAAC`、`ACAC`、`ACBC` となるため、開票結果の列としてあり得るものは $ 3 $ 通りです。

### Sample Explanation 2

どのような順序で開票を行っても、開票結果の列は `AAAA` となります。

## 样例 #1

### 输入

```
4
AABB
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
AAAA
```

### 输出

```
1
```

## 样例 #3

### 输入

```
10
BBBAAABBAA
```

### 输出

```
5
```

## 样例 #4

### 输入

```
172
AABAAAAAABBABAABBBBAABBAAABBABBABABABBAAABAAABAABAABBBBABBBABBABBBBBBBBAAABAAABAAABABBBAABAAAABABBABBABBBBBABAABAABBBABABBAAAABAABABBBABAAAABBBBABBBABBBABAABBBAAAABAAABAAAB
```

### 输出

```
24
```

