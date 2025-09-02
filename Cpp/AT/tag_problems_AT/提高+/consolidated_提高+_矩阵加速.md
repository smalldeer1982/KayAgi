---
title: "[ABC271G] Access Counter"
layout: "post"
diff: 提高+/省选-
pid: AT_abc271_g
tag: ['矩阵加速', '概率论']
---

# [ABC271G] Access Counter

## 题目描述

【题目翻译】

给定 $24$ 个时间点，每个时间点有可能有两种指令

如果指令是 `T`，则高桥有 $x\%$ 的概率登录洛谷。

如果指令是 `A`，则青木有 $y\%$ 的概率登录洛谷。

操作是依次进行的。求洛谷第 $n$ 次被登录是由青木操作的概率。

答案对 $998244353$ 取模。

## 输入格式

第一行三个数 $n,x,y$。

接下来有 24 个操作，每个操作只会有 `T` 或 `A`。

## 输出格式

求洛谷第 $n$ 次被登录是由青木操作的概率。

Translated by @cc0000

## 样例 #1

### 输入

```
1 50 50

ATATATATATATATATATATATAT
```

### 输出

```
665496236
```

## 样例 #2

### 输入

```
271 95 1

TTTTTTTTTTTTTTTTTTTTTTTT
```

### 输出

```
0
```

## 样例 #3

### 输入

```
10000000000000000 62 20

ATAATTATATTTAAAATATTATAT
```

### 输出

```
744124544
```



---

---
title: "[ABC305G] Banned Substrings"
layout: "post"
diff: 提高+/省选-
pid: AT_abc305_g
tag: ['动态规划 DP', '矩阵加速', 'AC 自动机']
---

# [ABC305G] Banned Substrings

## 题目描述

给定一个由 $M$ 个长度不超过 $6$ 的仅由字母 $\texttt a$ 和 $\texttt b$ 组成的非空字符串集合 $S=\{s_1, s_2, ..., s_M\}$。

求有多少个字符串 $T$ 满足以下条件：

- 长度为 $N$ 且仅由字母 $\texttt a$ 和 $\texttt b$ 组成。
- 对于任意 $s_i\in S$，$T$ 中不包含 $s_i$ 作为连续的子串。

由于答案可能很大，所以对 $998244353$ 取模。

## 输入格式

输入共 $M+1$ 行，第一行包括两个整数 $N$ 和 $M$，表示字符串长度和非空字符串集合大小。接下来 $M$ 行，每行一个字符串 $s_i$。

## 输出格式

输出仅包含一个整数，表示满足条件的字符串 $T$ 的个数对 $998244353$ 取模后的结果。

## 说明/提示

$1\leq N\leq 10^{18}$

$1\leq M\leq 126$

$N$ 和 $M$ 是整数。

$s_i$ 是由字母 $a$ 和 $b$ 组成的长度不超过 $6$ 的非空字符串。

$s_i \neq s_j$（$1\leq i<j\leq M$）。

## 样例 #1

### 输入

```
4 3

aab

bbab

abab
```

### 输出

```
10
```

## 样例 #2

### 输入

```
20 1

aa
```

### 输出

```
17711
```

## 样例 #3

### 输入

```
1000000007 28

bbabba

bbbbaa

aabbab

bbbaba

baaabb

babaab

bbaaba

aabaaa

aaaaaa

aabbaa

bbaaaa

bbaabb

bbabab

aababa

baaaba

ababab

abbaba

aabaab

ababaa

abbbba

baabaa

aabbbb

abbbab

baaaab

baabbb

ababbb

baabba

abaaaa
```

### 输出

```
566756841
```



---

---
title: "[ABC388F] Dangerous Sugoroku"
layout: "post"
diff: 提高+/省选-
pid: AT_abc388_f
tag: ['动态规划 DP', '矩阵加速']
---

# [ABC388F] Dangerous Sugoroku

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc388/tasks/abc388_f

$ N $ 個のマスが $ 1 $ 列に並んでおり、順に $ 1,\ 2,\ \ldots,\ N $ の番号が付けられています。

$ M $ 個の整数組 $ (L_1,\ R_1),\ \ldots,\ (L_M,\ R_M) $ が与えられます。

マス $ j $ はある $ i $ に対して $ L_i\ \leq\ j\ \leq\ R_i $ を満たすとき、またそのときに限り **悪いマス** であると定めます。

マス $ 1 $ から以下の行動を繰り返すことでマス $ N $ に移動できるか判定してください。

- 現在位置しているマスをマス $ x $ とする。以下の条件をすべて満たすような整数 $ i $ を選び、マス $ x\ +\ i $ に移動する。
  - $ A\ \leq\ i\ \leq\ B $
  - $ x\ +\ i\ \leq\ N $
  - マス $ x\ +\ i $ は悪いマスでない

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $ $ A $ $ B $ $ L_1 $ $ R_1 $ $ L_2 $ $ R_2 $ $ \vdots $ $ L_M $ $ R_M $

## 输出格式

問題文中の行動を繰り返すことでマス $ N $ に移動できる場合は `Yes` を、そうでない場合は `No` を出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^{12} $
- $ 0\ \leq\ M\ \leq\ 2\ \times\ 10^4 $
- $ 1\ \leq\ A\ \leq\ B\ \leq\ 20 $
- $ 1\ <\ L_i\ \leq\ R_i\ <\ N\ (1\ \leq\ i\ \leq\ M) $
- $ R_i\ <\ L_{i\ +\ 1}\ (1\ \leq\ i\ \leq\ M\ -\ 1) $
- 入力される値はすべて整数
 
### Sample Explanation 1

マス $ 1\ \to\ 6\ \to\ 9\ \to\ 12\ \to\ 16\ \to\ 21\ \to\ 24 $ のように移動することでマス $ N $ に移動することができます。

## 样例 #1

### 输入

```
24 2 3 5

7 8

17 20
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
30 1 5 8

4 24
```

### 输出

```
No
```

## 样例 #3

### 输入

```
100 4 10 11

16 18

39 42

50 55

93 99
```

### 输出

```
Yes
```



---

