---
title: "VIDEO - Video game combos"
layout: "post"
diff: 省选/NOI-
pid: SP10502
tag: ['字符串', '动态规划 DP']
---

# VIDEO - Video game combos

## 题目描述

 Bessie is playing a video game! In the game, the three letters 'A', 'B', and 'C' are the only valid buttons. Bessie may press the buttons in any order she likes. However, there are only N distinct combos possible (1 <= N <= 20). Combo i is represented as a string S\_i which has a length between 1 and 15 and contains only the letters 'A', 'B', and 'C'.

 Whenever Bessie presses a combination of letters that matches with a combo, she gets one point for the combo. Combos may overlap with each other or even finish at the same time! For example if N = 3 and the three possible combos are "ABA", "CB", and "ABACB", and Bessie presses "ABACB", she will end with 3 points. Bessie may score points for a single combo more than once.

 Bessie of course wants to earn points as quickly as possible. If she presses exactly K buttons (1 <= K <= 1,000), what is the maximum number of points she can earn?

## 样例 #1

### 输入

```
3 7
ABA
CB
ABACB
```

### 输出

```
4
```



---

---
title: "SEQPAR2 - Sequence Partitioning II"
layout: "post"
diff: 省选/NOI-
pid: SP1748
tag: ['动态规划 DP', '线段树']
---

# SEQPAR2 - Sequence Partitioning II

## 题目描述

Given a sequence of _N_ ordered pairs of positive integers (_A $ _{i} $_ , _B $ _{i} $_ ), you have to partition it into several contiguous parts. Let _p_ be the number of these parts, whose boundaries are (_l_ $ _{1} $ , _r_ $ _{1} $ ), (_l_ $ _{2} $ , _r_ $ _{2} $ ), ... ,(_l $ _{p} $_ , _r $ _{p} $_ ), which satisfy _l $ _{i} $_ = _r $ _{i-} $_  $ _{1} $ + 1, _l $ _{i} $_ <= _r $ _{i} $_ , _l_ $ _{1} $ = 1, _r $ _{p} $_ = _n_. The parts themselves also satisfy the following restrictions:

1. For any two pairs (_A $ _{p} $_ , _B $ _{p} $_ ), (_A $ _{q} $_ , _B $ _{q} $_ ), where (_A $ _{p} $_ , _B $ _{p} $_ ) is belongs to the _T $ _{p} $_ th part and (_A $ _{q} $_ , _B $ _{q} $_ ) the _T $ _{q} $_ th part. If _T $ _{p} $_ < _T $ _{q} $_ , then _B $ _{p} $_ > _A $ _{q} $_ .
2. Let _M $ _{i} $_  be the maximum _A_-component of elements in the _i_th part, say
  
  _M $ _{i} $_  = max {_A $ _{li} $_ , _A $ _{li+} $_  $ _{1} $ , ..., _A $ _{ri} $_ }, 1 <= _i_ <= _p_
  
  it is provided that
  
  ![](../../content/crazyb0y:SEQPAR2_1.bmp)  
   where Limit is a given integer.

Let _S $ _{i} $_  be the sum of _B_-components of elements in the _i_th part.

Now I want to minimize the value

max{_S $ _{i} $_ :1 <= _i_ <= p}

Could you tell me the minimum?

## 输入格式

The input contains exactly one test case. The first line of input contains two positive integers N (N <= 50000), Limit (Limit <= 2 $ ^{31} $ -1). Then follow N lines each contains a positive integers pair (_A_, _B_). It's always guaranteed that

 max{_A_ $ _{1} $ , _A_ $ _{2} $ , ..., _A $ _{n} $_ } <= Limit  
![](../../content/crazyb0y:SEQPAR2_2.bmp)

## 输出格式

Output the minimum target value.

## 样例 #1

### 输入

```
4 6
4 3
3 5
2 5
2 4
```

### 输出

```
9
```



---

---
title: "PERIODNI - Periodni"
layout: "post"
diff: 省选/NOI-
pid: SP3734
tag: ['动态规划 DP']
---

# PERIODNI - Periodni

## 题目描述

 [English](/problems/PERIODNI/en/) [Vietnamese](/problems/PERIODNI/vn/)Luka is bored in chemistry class so he is staring at a large periodic table of chemical elements hanging from a wall above the blackboard. To kill time, Luka decided to make his own table completely different from the one in the classroom.

His table consists of N columns, each with some height, aligned at the bottom (see example below). After he draws the table he needs to fill it with elements. He first decided to enter the noble gases of which there are K. Luka must put them in the table so that no two noble gases are close to each other.

Two squares in the table are close to each other if they are in the same column or row, and all squares between them exist. In the example below, the 'a' squares are not close, but the 'b' squares are.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP3734/87f0da7d42d32cf3ae36c86030240397dce7472a.png)

Write a program that, given N, K and the heights of the N columns, calculates the total number of ways for Luka to place the noble gases into the table. This number can be large, so output it modulo 1 000 000 007.

## 输入格式

The first line contains the integers N and K separated by a space (1

The next line contains N positive integers, separated by spaces. These are heights of the columns from left to right. The heights will be at most 1 000 000.

## 输出格式

Output the number of ways for Luka to fill his table with noble gases, modulo 1 000 000 007.

## 样例 #1

### 输入

```
5 2
2 3 1 2 4
```

### 输出

```
43
```



---

---
title: "PSTRING - Remove The String"
layout: "post"
diff: 省选/NOI-
pid: SP704
tag: ['动态规划 DP', 'KMP 算法']
---

# PSTRING - Remove The String

## 题目描述

给你两个字符串$X$和$Y$。在$X$中删除最少的字符，使得$Y$不为$X$的子串。

## 输入格式

输入包含多组测试数据。



每个测试数据的第一行为$X$,而第二行为$Y$。（保证$X$的长度小于等于10000,$Y$的长度小于等于1000）

## 输出格式

对于每一组数据，输出一个整数，也就是最少删除字符的数量。

## 样例 #1

### 输入

```
ababaa

aba
```

### 输出

```
1
```



---

---
title: "AMR10B - Regex Edit Distance"
layout: "post"
diff: 省选/NOI-
pid: SP8056
tag: ['动态规划 DP', '有限状态自动机']
---

# AMR10B - Regex Edit Distance

## 题目描述

在这道题目中，我们使用正则表达式来描述一组字符串。题目限定的字母表是 'a' 和 'b'。一个正则表达式 $R$ 满足以下任一条件时即为合法：

1. $R$ 为 "a" 或 "b"
2. $R$ 可以写成 "(R1R2)" 形式，其中 R1 和 R2 都是正则表达式
3. $R$ 可以写成 "(R1|R2)" 形式，其中 R1 和 R2 都是正则表达式
4. $R$ 可以写成 "(R1*)" 形式，其中 R1 是正则表达式

识别的字符串集合由 $R$ 描述如下：

1. 当 $R$ 为 "a" 时，识别的字符串集合为 {a}
2. 当 $R$ 为 "b" 时，识别的字符串集合为 {b}
3. 若 $R$ 的形式是 "(R1R2)"，识别的字符串集合是所有能由 R1 识别的字符串 s1 和由 R2 识别的字符串 s2 连同起来得到的字符串
4. 若 $R$ 的形式是 "(R1|R2)"，识别的字符串集合是 R1 和 R2 识别集合的并集
5. 若 $R$ 的形式是 "(R1\*)" ，识别的字符串集合包括空字符串以及任意多个 R1 识别的字符串连接起来得到的字符串

字符串 s1 和 s2 之间的编辑距离是指将 s1 通过最少的字符插入、删除或替换操作变成 s2 所需的步数。

给定两个正则表达式 $R1$ 和 $R2$，求在所有由 $R1$ 识别的字符串 s1 和由 $R2$ 识别的字符串 s2 之间的最小编辑距离。

## 输入格式

第一行输入一个整数 $T$，表示测试用例的数量。接下来是 $T$ 个测试用例。
每个测试用例由两行组成，分别包含一个正则表达式 $R1$ 和 $R2$。每个测试用例之间用一个空行分隔。

## 输出格式

输出 $T$ 行，每行对应一个测试用例的最小编辑距离。

## 说明/提示

- $T \leq 100$
- $1 \leq \text{length}(R1), \text{length}(R2) \leq 50$
- 保证 $R1$ 和 $R2$ 完全符合题目给出的定义。

**样例输入**
```
2
((a|b)*)
(a(b(aa)))

(a((ab)*))
(a(b(((ab)b)b)))
```

**样例输出**
```
0
2
```

**解释**
- 对于第一个测试用例，$R1$ 能识别所有由 'a' 和 'b' 组成的字符串，因此它也识别字符串 "abaa"，这个字符串同样被 $R2$ 识别。
- 对于第二个测试用例，字符串 "aababab" 和 "ababbb" 分别被 $R1$ 和 $R2$ 识别，而它们之间的编辑距离为 2。

 **本翻译由 AI 自动生成**



---

