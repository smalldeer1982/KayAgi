---
title: "[ABC377G] Edit to Match"
layout: "post"
diff: 普及+/提高
pid: AT_abc377_g
tag: ['动态规划 DP', '字典树 Trie']
---

# [ABC377G] Edit to Match

## 题目描述

给你 $N$ 个字符串 $S_1,S_2,\ldots,S_N$ 。每个字符串都由小写英文字母组成。

对于每一个 $k=1,2,\ldots,N$，解决下列问题：

一开始将一个字符串 $T$ 赋为 $S_k$。

接下来，你可以在下列操作中二选一，并可以操作无限次。但每一次操作都会花费 $1$ 的代价。

- 当 $T$ 不为空时，删除 $T$ 的最后一个字符。
- 在 $T$ 后面加上一个任意的小写字母。

求使 $T$ 要么为空，要么与 $S_1,S_2,\ldots,S_{k-1}$ 中的一个匹配所需的最小代价。

## 输入格式

第一行一个正整数 $N$。

第 $2$ 至 $N+1$ 行，每行一个字符串 $S_i$。

## 输出格式

共 $N$ 行。第 $i$ 行输出当 $k=i$ 时的最小代价。

## 说明/提示

- $1\le N\le 2\times10^5$
- $\sum\limits_{i=1}^N|S_i|\le2\times10^5$

## 样例 #1

### 输入

```
3
snuke
snuki
snuuk
```

### 输出

```
5
2
4
```

## 样例 #2

### 输入

```
3
abc
arc
agc
```

### 输出

```
3
3
3
```

## 样例 #3

### 输入

```
8
at
atatat
attat
aatatatt
attattat
ttatta
tta
tt
```

### 输出

```
2
4
3
8
3
6
3
1
```



---

---
title: "[ABC384F] Double Sum 2"
layout: "post"
diff: 普及+/提高
pid: AT_abc384_f
tag: ['数学', '字典树 Trie', '位运算']
---

# [ABC384F] Double Sum 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc384/tasks/abc384_f

正整数 $ x $ に対して $ f(x) $ を「 $ x $ が偶数である間 $ x $ を $ 2 $ で割り続けたときの、最終的な $ x $ の値」として定義します。例えば $ f(4)=f(2)=f(1)=1 $ 、 $ f(12)=f(6)=f(3)=3 $ です。

長さ $ N $ の整数列 $ A=(A_1,A_2,\ldots,\ A_N) $ が与えられるので、 $ \displaystyle\ \sum_{i=1}^N\ \sum_{j=i}^N\ f(A_i+A_j) $ を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ \ldots $ $ A_N $

## 输出格式

答えを出力せよ。

## 说明/提示

### 制約

- $ 1\le\ N\le\ 2\times\ 10^5 $
- $ 1\le\ A_i\le\ 10^7 $
- 入力は全て整数
 
### Sample Explanation 1

$ f(A_1+A_1)=f(8)=1 $ 、 $ f(A_1+A_2)=f(12)=3 $ 、 $ f(A_2+A_2)=f(16)=1 $ です。したがって、 $ 1+3+1=5 $ を出力してください。

## 样例 #1

### 输入

```
2

4 8
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3

51 44 63
```

### 输出

```
384
```

## 样例 #3

### 输入

```
8

577752 258461 183221 889769 278633 577212 392309 326001
```

### 输出

```
20241214
```



---

---
title: "[ABC403E] Forbidden Prefix"
layout: "post"
diff: 普及+/提高
pid: AT_abc403_e
tag: ['字符串', '哈希 hashing', '字典树 Trie']
---

# [ABC403E] Forbidden Prefix

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc403/tasks/abc403_e

现有两个字符串多重集合 $X$ 和 $Y$，初始时均为空集合。

需要依次处理 $Q$ 个查询。第 $i$ 个查询给出整数 $T_i$ 和字符串 $S_i$：
- 若 $T_i=1$，则将 $S_i$ 加入 $X$；
- 若 $T_i=2$，则将 $S_i$ 加入 $Y$。

在每个查询处理完成后，请输出以下值：
- $Y$ 中满足"不以 $X$ 中任何字符串作为前缀"的字符串数量。

## 输入格式

输入通过标准输入给出，格式如下：

> $Q$  
> $T_1$ $S_1$  
> $T_2$ $S_2$  
> $\vdots$  
> $T_Q$ $S_Q$

## 输出格式

输出 $Q$ 行。第 $i$ 行 $(1 \leq i \leq Q)$ 应输出第 $i$ 个查询处理后的答案。


## 说明/提示

### 约束条件

- $Q$ 是 $1$ 到 $2 \times 10^5$ 之间的整数
- $T_i \in \{1,2\}$
- $S_i$ 是长度在 $1$ 到 $5 \times 10^5$ 之间的小写字母字符串
- $\displaystyle \sum_{i=1}^Q |S_i| \leq 5 \times 10^5$

### 样例解释 #1

各查询处理后的结果如下：
- $i=1$：$Y$ 为空集，答案为 $0$
- $i=2$：`watcoder` 不以 $X$ 中的 `at` 为前缀，答案为 $1$
- $i=3$：`watcoder` 仍满足条件，而 `atcoder` 以 `at` 为前缀，答案为 $1$
- $i=4$：`watcoder` 以新增的 `wa` 为前缀，`atcoder` 以 `at` 为前缀，答案为 $0$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
1 at
2 watcoder
2 atcoder
1 wa
```

### 输出

```
0
1
1
0
```

## 样例 #2

### 输入

```
10
1 w
1 avko
2 atcoder
1 bzginn
2 beginner
1 atco
2 contest
1 ntxcdg
1 atc
1 contest
```

### 输出

```
0
0
1
1
2
1
2
2
2
1
```



---

---
title: "[AGC047B] First Second"
layout: "post"
diff: 普及+/提高
pid: AT_agc047_b
tag: ['字典树 Trie']
---

# [AGC047B] First Second

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc047/tasks/agc047_b

リマクは、文字列の先頭 $ 2 $ 文字のうち片方を取り除くことを繰り返し行えます。例えば、$ abcxyx\ \rightarrow\ acxyx\ \rightarrow\ cxyx\ \rightarrow\ cyx $ とすることができます。

$ N $ 個の相異なる文字列 $ S_1,\ S_2,\ \ldots,\ S_N $ が与えられます。$ N\ \cdot\ (N-1)\ /\ 2 $ 個のペア $ (S_i,\ S_j) $ のうち何個において、リマクは一方からもう一方を得ることができるでしょうか。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S_1 $ $ S_2 $ $ \vdots $ $ S_N $

## 输出格式

リマクが一方の文字列からもう一方を得られるような非順序対 $ (S_i,\ S_j) $ ($ i\ \neq\ j $) の個数を出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 200\,000 $
- $ S_i $ は英小文字 `a` - `z` からなる。
- $ S_i\ \neq\ S_j $
- $ 1\ \leq\ |S_i| $
- $ |S_1|\ +\ |S_2|\ +\ \ldots\ +\ |S_N|\ \leq\ 10^6 $

### Sample Explanation 1

条件を満たすペアは $ (abcxyx,\ cyx) $ のみです。

### Sample Explanation 2

条件を満たすペアは $ (b,\ abc) $, $ (a,\ abc) $, $ (abc,\ c) $, $ (b,\ ab) $, $ (a,\ ab) $ の $ 5 $ 個です。

## 样例 #1

### 输入

```
3

abcxyx

cyx

abc
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6

b

a

abc

c

d

ab
```

### 输出

```
5
```



---

