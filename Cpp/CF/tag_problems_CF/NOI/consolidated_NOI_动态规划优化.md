---
title: "Counting 101"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2002H
tag: ['动态规划 DP', '动态规划优化', 'DP 套 DP']
---

# Counting 101

## 题目描述

### 题目背景

夏日漫长，蝉鸣不断，酷暑难耐。终于，它落下了帷幕。决战已过，大门敞开，只留下一阵轻风。

你的前辈们已经完成了最后的鞠躬，轮到你上场了。


在整理留下的一些笔记时，你发现了一份名为 **问题 101** 的奇怪声明：

- 给定一个正整数序列 $a_1,a_2,\ldots,a_n$，你可以对它进行任意次操作。在一次操作中，你可以选择连续的三个元素 $a_i,a_{i+1},a_{i+2}$，并将它们合并为一个元素 $\max(a_i+1,a_{i+1},a_{i+2}+1)$。请计算在不产生大于 $m$ 的元素的前提下，最多可以进行多少次操作。

经过思考，你决定提出下面这个问题，命名为 **计算 101**：

- 给定 $n$ 和 $m$。对于每一个 $k=0,1,\ldots,\left\lfloor\frac{n-1}{2}\right\rfloor$，求元素在 $[1, m]$ 中的整数序列 $a_1,a_2,\ldots,a_n$ 的个数，使得作为 **问题 101** 的输入时，答案是 $k$。由于答案可能非常大，只需要输出对 $10^9+7$ 的结果即可。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1\le t\le10^3$ ) 。测试用例说明如下。

每个测试用例的唯一一行包含两个整数 $n$ , $m$ ( $1\le n\le 130$ , $1\le m\le 30$ )。

## 输出格式

对于每个测试用例，输出 $\left\lfloor\frac{n+1}{2}\right\rfloor$ 个数字。第 $i$ 个数字是有效序列的个数，满足这些序列作为 **问题 101** 的输入时，答案为 $i-1$，对 $10^9+7$ 取模。

### 样例解释

对于第一组数据，共有 $2^3=8$ 种合法数组。其中 $[1,2,1]$ 与 $[1,1,1]$ 可操作一次，余下 $6$ 个数组无法操作。

## 样例 #1

### 输入

```
2
3 2
10 10
```

### 输出

```
6 2 
1590121 23399118 382293180 213020758 379696760
```



---

---
title: "Go Learn! (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2035G2
tag: ['动态规划 DP', '二分', '动态规划优化']
---

# Go Learn! (Hard Version)

## 题目描述

The differences between the easy and hard versions are the constraints on $ n $ and the sum of $ n $ . In this version, $ n \leq 3\cdot 10^5 $ and the sum of $ n $ does not exceed $ 10^6 $ . You can only make hacks if both versions are solved.

Well, well, well, let's see how Bessie is managing her finances. She seems to be in the trenches! Fortunately, she is applying for a job at Moogle to resolve this issue. Moogle interviews require intensive knowledge of obscure algorithms and complex data structures, but Bessie received a tip-off from an LGM on exactly what she has to go learn.

Bessie wrote the following code to binary search for a certain element $ k $ in a possibly unsorted array $ [a_1, a_2,\ldots,a_n] $ with $ n $ elements.

```
<pre class="lstlisting">```
let l = 1<br></br>let h = n<br></br><br></br>while l < h:<br></br>  let m = floor((l + h) / 2)<br></br><br></br>  if a[m] < k:<br></br>    l = m + 1<br></br>  else:<br></br>    h = m<br></br><br></br>return l<br></br>
```
```

Bessie submitted her code to Farmer John's problem with $ m $ ( $ 1 \leq m \leq n $ ) tests. The $ i $ -th test is of the form $ (x_i, k_i) $ ( $ 1 \leq x, k \leq n $ ). It is guaranteed all the $ x_i $ are distinct and all the $ k_i $ are distinct.

Test $ i $ is correct if the following hold:

1. The $ x_i $ -th element in the array is $ k_i $ .
2. If Bessie calls the binary search as shown in the above code for $ k_i $ , it will return $ x_i $ .

It might not be possible for all $ m $ tests to be correct on the same array, so Farmer John will remove some of them so Bessie can AC. Let $ r $ be the minimum of tests removed so that there exists an array $ [a_1, a_2,\ldots,a_n] $ with $ 1 \leq a_i \leq n $ so that all remaining tests are correct.

In addition to finding $ r $ , Farmer John wants you to count the number of arrays $ [a_1, a_2,\ldots,a_n] $ with $ 1 \leq a_i \leq n $ such that there exists a way to remove exactly $ r $ tests so that all the remaining tests are correct. Since this number may be very large, please find it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \leq m \leq n \leq 3 \cdot 10^5 $ ) denoting the number of the array and the number of tests.

The following $ m $ lines each contain two integers, describing the tests. The $ i $ -th line contains two integers $ x_i $ and $ k_i $ ( $ 1 \leq x_i, k_i \leq n $ ) denoting the index and value of the test. It is guaranteed all $ x_i $ are distinct and all $ k_i $ are distinct.

It is guaranteed the sum of $ n $ across all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output two integers, $ r $ — the minimum of tests removed so that there exists an array so that all remaining tests are correct, and the number of arrays such that it is possible to remove $ r $ tests to make all remaining tests correct modulo $ 998\,244\,353 $ .

## 说明/提示

Consider the first example.

In the first test case, the array $ [1,2,2,3,4] $ satisfies all $ m $ tests, so the minimum number of tests Bessie has to remove is $ 0 $ . Note that this is also the only array that satisfies all $ m $ tests.

In the second test case, the minimum number of tests Bessie has to remove is $ 1 $ . The only test Bessie can remove is $ (2,5) $ . If Bessie removes test $ (2,5) $ , then the arrays satisfying the remaining $ m-1 $ tests are $ [2,2,3,1,4] $ , $ [2,2,3,2,4] $ , $ [2,2,3,3,4] $ .

## 样例 #1

### 输入

```
2
5 4
1 1
2 2
4 3
5 4
5 4
5 4
2 5
1 2
3 3
```

### 输出

```
0 1
1 3
```

## 样例 #2

### 输入

```
3
6 6
1 3
2 5
3 1
4 2
5 4
6 6
30 8
19 22
6 12
12 1
28 27
3 4
14 25
29 14
11 15
300000 1
5 10
```

### 输出

```
3 78
3 839271911
0 702730519
```



---

---
title: "Yandex Cuneiform (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2046F2
tag: ['动态规划 DP', '动态规划优化', '凸包']
---

# Yandex Cuneiform (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in this version, there is no restriction on the number of question marks. You can hack only if you solved all versions of this problem.

For a long time, no one could decipher Sumerian cuneiform. However, it has finally succumbed to pressure! Today, you have the chance to decipher Yandex cuneiform.

Yandex cuneiform is defined by the following rules:

1. An empty string is a Yandex cuneiform.
2. If you insert exactly one copy of each of the three letters 'Y', 'D', and 'X' into a Yandex cuneiform in such a way that no two adjacent letters become equal after the operation, you obtain a Yandex cuneiform.
3. If a string can't be obtained using the above rules, it is not a Yandex cuneiform.

You are given a template. A template is a string consisting of the characters 'Y', 'D', 'X', and '?'.

You need to check whether there exists a way to replace each question mark with 'Y', 'D', or 'X' to obtain a Yandex cuneiform, and if it exists, output any of the matching options, as well as a sequence of insertion operations to obtain the resulting cuneiform.

In this version of the problem, the number of question marks in the template can be arbitrary.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5 \cdot 10^4 $ ). The description of the test cases follows.

Each test case consists of a single line containing a template of length $ n $ ( $ 3 \leq n < 2 \cdot 10^5 $ , $ n \bmod 3 = 0 $ ), consisting only of characters 'Y', 'D', 'X', and '?'.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line containing 'NO' if it is not possible to obtain a cuneiform from the given template.

Otherwise, output 'YES' on the first line, and on the second line, any obtainable cuneiform. After that, you need to output the sequence of operations that leads to the cuneiform you printed.

A sequence of operations is described by $ \frac{n}{3} $ triples of pairs. A pair has the form c p, where $ c $ is one of the letters 'Y', 'D', or 'X', and $ p $ is the position at which the letter $ c $ should be inserted. The insertion position is the number of letters to skip from the beginning of the string for the insertion. For example, after inserting the character 'D' into the string "YDX" with $ p=3 $ , the result is "YDXD", and with $ p=0 $ , it is "DYDX". Note that the index cannot exceed the current length of the string.

The operations are applied from top to bottom, left to right. After inserting each triple to the string, there should be no two adjacent identical characters.

## 说明/提示

In the second example, the string is transformed like this: $ "" \to \mathtt{YDX} \to \mathtt{YDXDYX} $ .

## 样例 #1

### 输入

```
4
???
Y??D?X
???
D??DXYXYX
```

### 输出

```
YES
YDX
X 0 D 0 Y 0 
YES
YDXDYX
X 0 Y 0 D 1
X 2 D 3 Y 4
YES
YDX
Y 0 D 1 X 2
NO
```



---

---
title: "Wish Upon a Satellite (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2084G2
tag: ['动态规划 DP', '平衡树', '动态规划优化']
---

# Wish Upon a Satellite (Hard Version)

## 题目描述

这是该问题的简单版本。与困难版本的区别在于，本版本中 $t \le 10^4$、$n \le 5 \times 10^5$ 且所有测试用例的 $n$ 之和不超过 $5\times 10^5$。只有当你解决了该问题的所有版本时才能进行 hack。

对于一个长度为 $k$ 的非空序列 $c$，定义 $f(c)$ 如下：

- Turtle 和 Piggy 正在一个序列上玩游戏。他们被给定序列 $c_1, c_2, \ldots, c_k$，由 Turtle 先手。Turtle 和 Piggy 轮流进行操作（Turtle 第一步，Piggy 第二步，Turtle 第三步，依此类推）。
- 游戏规则如下：
  - 设当前序列长度为 $m$。如果 $m = 1$，游戏结束。
  - 如果游戏未结束且轮到 Turtle，Turtle 必须选择一个整数 $i$（$1 \le i \le m - 1$），将 $c_i$ 设为 $\min(c_i, c_{i + 1})$，并删除 $c_{i + 1}$。
  - 如果游戏未结束且轮到 Piggy，Piggy 必须选择一个整数 $i$（$1 \le i \le m - 1$），将 $c_i$ 设为 $\max(c_i, c_{i + 1})$，并删除 $c_{i + 1}$。
- Turtle 希望最终 $c_1$ 的值最大化，而 Piggy 希望最终 $c_1$ 的值最小化。
- $f(c)$ 表示双方都采取最优策略时，最终 $c_1$ 的值。

对于一个长度为 $n$ 的排列 $p$ $^{\text{∗}}$，Turtle 定义该排列的美观度为 $\sum\limits_{i = 1}^n \sum\limits_{j = i}^n f([p_i, p_{i + 1}, \ldots, p_j])$（即所有 $p$ 的非空子段 $^{\text{†}}$ $c$ 的 $f(c)$ 之和）。

Piggy 给 Turtle 一个长度为 $n$ 的排列 $a$，其中部分元素缺失（用 $0$ 表示）。

Turtle 请你确定一个排列 $b$，满足以下条件：

- $b$ 可以通过填充 $a$ 中缺失的元素得到（即对于所有 $1 \le i \le n$，如果 $a_i \ne 0$，则 $b_i = a_i$）。
- 排列 $b$ 的美观度最大化。

为了方便，你只需要找到这样的排列 $b$ 的最大美观度。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（因为 $n=3$ 但数组中包含 $4$）。

$^{\text{†}}$ 序列 $a$ 是序列 $b$ 的子段，当且仅当 $a$ 可以通过从 $b$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 5\times 10^5$）。  
第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \le a_i \le n$）。保证 $a$ 中非 $0$ 的元素互不相同。  
保证所有测试用例的 $n$ 之和不超过 $5\times 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——排列 $b$ 的最大美观度。


## 说明/提示

- 在第一个测试用例中，美观度最大的排列 $b$ 是 $[1, 2]$。$[1, 2]$ 的美观度为 $4$，因为 $f([1]) + f([2]) + f([1, 2]) = 1 + 2 + 1 = 4$。如果 $c = [1, 2]$，则 $f(c) = 1$，因为 Turtle 只能选择 $i = 1$，并将 $c_1$ 设为 $\min(c_1, c_2) = 1$。

- 在第二个测试用例中，美观度最大的排列之一是 $[3, 2, 1]$。$[3, 2, 1]$ 的美观度为 $12$，因为 $f([3]) + f([2]) + f([1]) + f([3, 2]) + f([2, 1]) + f([3, 2, 1]) = 3 + 2 + 1 + 2 + 1 + 3 = 12$。

- 在第三个测试用例中，美观度最大的排列之一是 $[2, 1, 3]$。

- 在第四个测试用例中，如果 $c = [3, 2, 4, 5, 1]$，则 $f(c) = 3$。一种可能的游戏过程如下：
  - Turtle 选择 $i = 3$，将 $c_3$ 设为 $\min(c_3, c_4) = 4$ 并删除 $c_4$。序列变为 $[3, 2, 4, 1]$。
  - Piggy 选择 $i = 1$，将 $c_1$ 设为 $\max(c_1, c_2) = 3$ 并删除 $c_2$。序列变为 $[3, 4, 1]$。
  - Turtle 选择 $i = 2$，将 $c_2$ 设为 $\min(c_2, c_3) = 1$ 并删除 $c_3$。序列变为 $[3, 1]$。
  - Piggy 选择 $i = 1$，将 $c_1$ 设为 $\max(c_1, c_2) = 3$ 并删除 $c_2$。序列变为 $[3]$。
  - 序列长度为 $1$，游戏结束。最终 $c_1$ 的值为 $3$。

- 在第五个测试用例中，美观度最大的排列之一是 $[1, 3, 2, 5, 6, 4, 7]$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
2
1 0
3
0 0 0
3
0 1 0
5
3 2 4 5 1
7
0 3 2 5 0 0 0
10
1 2 6 5 8 9 0 0 0 0
5
0 4 1 0 0
5
0 1 5 2 3
```

### 输出

```
4
12
11
44
110
300
45
40
```



---

---
title: "Turtle and Nediam 2"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2084H
tag: ['动态规划 DP', '动态规划优化']
---

# Turtle and Nediam 2

## 题目描述

[LGR-205-Div.1 C Turtle and Nediam](https://www.luogu.com.cn/problem/P11283)

给定一个长度为 $n$ 的二进制序列 $s$，仅由 $0$ 和 $1$ 组成。

你可以进行最多 $n - 2$ 次（可以是零次）以下操作：

- 设当前序列 $s$ 的长度为 $m$。选择一个整数 $i$ 满足 $1 \le i \le m - 2$。
- 设子数组 $[s_i, s_{i + 1}, s_{i + 2}]$ 的中位数 $^{\text{∗}}$ 为 $x$，并令 $j$ 为满足 $j \ge i$ 且 $s_j = x$ 的最小整数。
- 从序列中移除 $s_j$ 并将剩余部分拼接。换句话说，将 $s$ 替换为 $[s_1, s_2, \ldots, s_{j - 1}, s_{j + 1}, s_{j + 2}, \ldots, s_m]$。

注意每次操作后，序列 $s$ 的长度会减少 $1$。

求经过若干次操作后，可以得到的不同二进制序列的数量，结果对 $10^9 + 7$ 取模。

$^{\text{∗}}$ 长度为奇数 $k$ 的数组的中位数是指排序后的第 $\frac{k + 1}{2}$ 个元素。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$3 \le n \le 2 \cdot 10^6$）——二进制序列的长度。  
第二行包含一个长度为 $n$ 的字符串 $s$，仅由 $0$ 和 $1$ 组成。  

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^6$。

## 输出格式

对于每个测试用例，输出一个整数——可以得到的二进制序列的数量，对 $10^9 + 7$ 取模。


## 说明/提示

- 在第一个测试用例中，可以得到以下二进制序列：$[1, 1]$、$[1, 1, 1]$、$[1, 1, 1, 1]$、$[1, 1, 1, 1, 1]$。

- 在第二个测试用例中，可以得到以下二进制序列：$[0, 1]$、$[0, 1, 1]$、$[1, 0, 1]$、$[1, 0, 0, 1]$、$[1, 0, 1, 1]$、$[1, 0, 0, 0, 1]$、$[1, 0, 0, 1, 1]$、$[1, 0, 0, 0, 1, 1]$。例如，要得到 $[0, 1, 1]$，可以：
  - 选择 $i = 2$。子数组 $[0, 0, 0]$ 的中位数为 $0$。移除 $s_2$，序列变为 $[1, 0, 0, 1, 1]$。
  - 选择 $i = 1$。子数组 $[1, 0, 0]$ 的中位数为 $0$。移除 $s_2$，序列变为 $[1, 0, 1, 1]$。
  - 选择 $i = 1$。子数组 $[1, 0, 1]$ 的中位数为 $1$。移除 $s_1$，序列变为 $[0, 1, 1]$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
5
11111
6
100011
9
000111000
14
11001111111000
16
0010000110100011
```

### 输出

```
4
8
30
114
514
```



---

