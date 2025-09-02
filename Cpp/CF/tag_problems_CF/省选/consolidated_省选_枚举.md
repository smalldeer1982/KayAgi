---
title: "Dominant Indices"
layout: "post"
diff: 省选/NOI-
pid: CF1009F
tag: ['动态规划 DP', '树上启发式合并', '枚举']
---

# Dominant Indices

## 题目描述

You are given a rooted undirected tree consisting of $ n $ vertices. Vertex $ 1 $ is the root.

Let's denote a depth array of vertex $ x $ as an infinite sequence $ [d_{x, 0}, d_{x, 1}, d_{x, 2}, \dots] $ , where $ d_{x, i} $ is the number of vertices $ y $ such that both conditions hold:

- $ x $ is an ancestor of $ y $ ;
- the simple path from $ x $ to $ y $ traverses exactly $ i $ edges.

The dominant index of a depth array of vertex $ x $ (or, shortly, the dominant index of vertex $ x $ ) is an index $ j $ such that:

- for every $ k < j $ , $ d_{x, k} < d_{x, j} $ ;
- for every $ k > j $ , $ d_{x, k} \le d_{x, j} $ .

For every vertex in the tree calculate its dominant index.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the number of vertices in a tree.

Then $ n - 1 $ lines follow, each containing two integers $ x $ and $ y $ ( $ 1 \le x, y \le n $ , $ x \ne y $ ). This line denotes an edge of the tree.

It is guaranteed that these edges form a tree.

## 输出格式

Output $ n $ numbers. $ i $ -th number should be equal to the dominant index of vertex $ i $ .

## 样例 #1

### 输入

```
4
1 2
2 3
3 4

```

### 输出

```
0
0
0
0

```

## 样例 #2

### 输入

```
4
1 2
1 3
1 4

```

### 输出

```
1
0
0
0

```

## 样例 #3

### 输入

```
4
1 2
2 3
2 4

```

### 输出

```
2
1
0
0

```



---

---
title: "Bracket Substring"
layout: "post"
diff: 省选/NOI-
pid: CF1015F
tag: ['字符串', '递推', '枚举']
---

# Bracket Substring

## 题目描述

You are given a bracket sequence $ s $ (not necessarily a regular one). A bracket sequence is a string containing only characters '(' and ')'.

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters '1' and '+' between the original characters of the sequence. For example, bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)"), and ")(", "(" and ")" are not.

Your problem is to calculate the number of regular bracket sequences of length $ 2n $ containing the given bracket sequence $ s $ as a substring (consecutive sequence of characters) modulo $ 10^9+7 $ ( $ 1000000007 $ ).

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1 \le n \le 100 $ ) — the half-length of the resulting regular bracket sequences (the resulting sequences must have length equal to $ 2n $ ).

The second line of the input contains one string $ s $ ( $ 1 \le |s| \le 200 $ ) — the string $ s $ that should be a substring in each of the resulting regular bracket sequences ( $ |s| $ is the length of $ s $ ).

## 输出格式

Print only one integer — the number of regular bracket sequences containing the given bracket sequence $ s $ as a substring. Since this number can be huge, print it modulo $ 10^9+7 $ ( $ 1000000007 $ ).

## 说明/提示

All regular bracket sequences satisfying the conditions above for the first example:

- "(((()))())";
- "((()()))()";
- "((()))()()";
- "(()(()))()";
- "()((()))()".

All regular bracket sequences satisfying the conditions above for the second example:

- "((()))";
- "(()())";
- "(())()";
- "()(())".

And there is no regular bracket sequences of length $ 4 $ containing "(((" as a substring in the third example.

## 样例 #1

### 输入

```
5
()))()

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3
(()

```

### 输出

```
4

```

## 样例 #3

### 输入

```
2
(((

```

### 输出

```
0

```



---

---
title: "Triple Flips"
layout: "post"
diff: 省选/NOI-
pid: CF1031E
tag: ['枚举']
---

# Triple Flips

## 题目描述

You are given an array $ a $ of length $ n $ that consists of zeros and ones.

You can perform the following operation multiple times. The operation consists of two steps:

1. Choose three integers $ 1 \le x < y < z \le n $ , that form an arithmetic progression ( $ y - x = z - y $ ).
2. Flip the values $ a_x, a_y, a_z $ (i.e. change $ 1 $ to $ 0 $ , change $ 0 $ to $ 1 $ ).

Determine if it is possible to make all elements of the array equal to zero. If yes, print the operations that lead the the all-zero state. Your solution should not contain more than $ (\lfloor \frac{n}{3} \rfloor + 12) $ operations. Here $ \lfloor q \rfloor $ denotes the number $ q $ rounded down. We can show that it is possible to make all elements equal to zero in no more than this number of operations whenever it is possible to do so at all.

## 输入格式

The first line contains a single integer $ n $ ( $ 3 \le n \le 10^5 $ ) — the length of the array.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 1 $ ) — the elements of the array.

## 输出格式

Print "YES" (without quotes) if the answer exists, otherwise print "NO" (without quotes). You can print each letter in any case (upper or lower).

If there is an answer, in the second line print an integer $ m $ ( $ 0 \le m \le (\lfloor \frac{n}{3} \rfloor + 12) $ ) — the number of operations in your answer.

After that in ( $ i + 2 $ )-th line print the $ i $ -th operations — the integers $ x_i, y_i, z_i $ . You can print them in arbitrary order.

## 说明/提示

In the first sample the shown output corresponds to the following solution:

- 1 1 0 1 1 (initial state);
- 0 1 1 1 0 (the flipped positions are the first, the third and the fifth elements);
- 0 0 0 0 0 (the flipped positions are the second, the third and the fourth elements).

Other answers are also possible. In this test the number of operations should not exceed $ \lfloor \frac{5}{3} \rfloor + 12 = 1 + 12 = 13 $ .

In the second sample the only available operation is to flip all the elements. This way it is only possible to obtain the arrays 0 1 0 and 1 0 1, but it is impossible to make all elements equal to zero.

## 样例 #1

### 输入

```
5
1 1 0 1 1

```

### 输出

```
YES
2
1 3 5
2 3 4

```

## 样例 #2

### 输入

```
3
0 1 0

```

### 输出

```
NO

```



---

---
title: "Maximum Matching"
layout: "post"
diff: 省选/NOI-
pid: CF1038E
tag: ['枚举']
---

# Maximum Matching

## 题目描述

给定 $n$ 个方块，每个方块的格式为 $color_1\mid value \mid color_2$，方块也可以翻转得到 $color_2 \mid value \mid color_1$。

如果一个方块序列中相邻方块的接触端颜色相同，则称该序列为有效序列。例如，由三个方块 A、B 和 C 组成的序列是有效的，当且仅当 B 的左侧颜色与 A 的右侧颜色相同，且 B 的右侧颜色与 C 的左侧颜色相同。

序列的值定义为该序列中所有方块的值之和。

请从给定的方块子集中构造一个有效序列，并找到该序列的最大可能值。子集中的方块可以重新排序和翻转。每个方块在序列中最多只能使用一次。


## 输入格式

输入的第一行包含一个整数 $n$（$1 \le n \le 100$）—— 给定方块的数量。

接下来的 $n$ 行描述每个方块，每行包含 $\mathrm{color}_{1,i}$、$\mathrm{value}_i$ 和 $\mathrm{color}_{2,i}$（$1 \le \mathrm{color}_{1,i}, \mathrm{color}_{2,i} \le 4$，$1 \le \mathrm{value}_i \le 100\,000$）。


## 输出格式

输出一个整数 —— 能够构成有效序列的方块子集的最大总值。

## 说明/提示

第一个样例中，可以使用所有方块构造有效序列。

一种有效序列如下：

$4|2|1$，$1|32|2$，$2|8|3$，$3|16|3$，$3|4|4$，$4|1|2$

输入的第一个方块（$2|1|4$ $\to$ $4|1|2$）和第二个方块（$1|2|4$ $\to$ $4|2|1$）被翻转。

第二个样例中，最优解可由前三个方块构造（输入的第二个或第三个方块被翻转）：

$2|100000|1$，$1|100000|1$，$1|100000|2$

第三个样例中，无法构造包含两个或更多方块的有效序列，因此答案是仅包含第一个方块的序列（因为它是数值最大的方块）。

翻译由 DeepSeek V3+R1 完成

## 样例 #1

### 输入

```
6
2 1 4
1 2 4
3 4 4
2 8 3
3 16 3
1 32 2

```

### 输出

```
63
```

## 样例 #2

### 输入

```
7
1 100000 1
1 100000 2
1 100000 2
4 50000 3
3 50000 4
4 50000 4
3 50000 3

```

### 输出

```
300000
```

## 样例 #3

### 输入

```
4
1 1000 1
2 500 2
3 250 3
4 125 4

```

### 输出

```
1000
```



---

---
title: "Network Safety"
layout: "post"
diff: 省选/NOI-
pid: CF1039C
tag: ['并查集', '枚举', '概率论']
---

# Network Safety

## 题目描述

题意：

给你一个有$n$点个和$m$条边的图，第$i$个点的权值为$c_i$。

定义图为安全的条件对于所有的边都保证$c_l≠c_r$

请你求出对于任意的$x$，集合$s$中所有点的点权$xor\quad x$后图仍然安全，这样的$x$和$s$的组合的数量。

答案对于$1e9+7$取模

保证一开始给出的图是安全的。

## 输入格式

第一行一共三个整数$n(n<=500000),m(m<=min(\frac{n*(n-1)}{2},500000)),k(k<=60)$

第二行一共$n$个整数$c_i(c_i<=2^k-1)$

接下来的$m$行每行两个整数$l,r$，表示$l$和$r$之间有边

## 输出格式

一共一个整数，表示答案

## 样例 #1

### 输入

```
4 4 2
0 1 0 1
1 2
2 3
3 4
4 1

```

### 输出

```
50

```

## 样例 #2

### 输入

```
4 5 3
7 1 7 2
1 2
2 3
3 4
4 1
2 4

```

### 输出

```
96

```



---

---
title: "Ray in the tube"
layout: "post"
diff: 省选/NOI-
pid: CF1041F
tag: ['模拟', '枚举']
---

# Ray in the tube

## 题目描述

### 题目大意：
下边界有$n$个给定点，上边界有$m$个给定点，可以从任意一个点发出一条激光，激光碰到边界会反射

激光到达边界必须打到整数点，问最多可以打到几个给定点

## 输入格式

第一行两个整数$n,y_1$，表示下边界给定点的个数和下边界的纵坐标

第二行$n$个整数，表示给定点的横坐标

第三行两个整数$m,y_2$，表示上边界给定点的个数和上边界的纵坐标

第四行$m$个整数，表示给定点的横坐标

## 输出格式

一个整数，表示最多能打到多少点

## 样例 #1

### 输入

```
3 1
1 5 6
1 3
3

```

### 输出

```
3

```



---

---
title: "Greedy Change"
layout: "post"
diff: 省选/NOI-
pid: CF10E
tag: ['贪心', '枚举', '向量']
---

# Greedy Change

## 题目描述

给定 $n$ 种货币，每种货币数量无限。 现在要求以最少的货币数目表示一个数 $S$。 一种方法当然是 DP 求一个最优解了， 当然正常人的做法是贪心：每次取最大的不超过当前待表示数的货币。 现在，你的任务是证明正常人的表示法不一定最优：找到最小的 $S$，使得正常人的表示法比理论最优解差，或说明这样的 $S$ 不存在。

## 输入格式

第一行包含一个整数 $n$（$1\leq n\leq 400$）。第二行包含 $n$ 个整数 $a_i$（$1\leq a_i\leq 10^9$）为每个硬币面值。保证 $a$ 数组严格降序排列且 $a_n=1$。

## 输出格式

如果贪心能以最优的方式求出所以和，输出 `-1`。否则以非最优方式输出贪婪算法收集的最小和。

## 样例 #1

### 输入

```
5
25 10 5 2 1

```

### 输出

```
-1

```

## 样例 #2

### 输入

```
3
4 3 1

```

### 输出

```
6

```



---

---
title: "Lucky Array"
layout: "post"
diff: 省选/NOI-
pid: CF121E
tag: ['树状数组', '枚举', '进制']
---

# Lucky Array

## 题目描述

Petya 喜欢幸运数，幸运数只包含 $4$ 和 $7$ 这两个数字。例如 $47$，$744$，$4$ 都是幸运数字，但 $5,16,467$ 不是。

Petya 有一个 $N$ 个数的数组，他想给这个数组执行 $M$ 个操作，可以分为两种操作：

1. `add l r d` 把第 $l$ 到第 $r$ 个数都加上 $d$；
2. `count l r` 统计第 $l$ 到第 $r$ 个数有多少个幸运数字。

保证所有数操作前后都不超过 $10^4$。

请你编一个程序来执行这些操作。

$1\leq N,M\leq 10^5$，$1\leq l\leq r\leq N$，$1\leq d \leq 10^4$。

## 输入格式

第一行，两个数 $N$ 和 $M$；

第二行，$N$ 个数，表示原数组；

## 输出格式

对于每个询问幸运数个数的问题，输出答案，每个占一行。

_输入输出样例在下面_

## 说明/提示

对于第一个样例：

1. 执行了 `add 1 3 2` 操作之后变成：$[4, 5, 6]$；
2. 执行了 `add 2 3 3` 操作之后变成：$[4, 8, 9]$。

对于第二个样例：

1. 执行了 `add 1 4 3` 之后变成：$[7,7,7,7]$；
2. 执行了 `add 2 3 40` 之后变成：$[7,47,47,7]$。

## 样例 #1

### 输入

```
3 6
2 3 4
count 1 3
count 1 2
add 1 3 2
count 1 3
add 2 3 3
count 1 3

```

### 输出

```
1
0
1
1

```

## 样例 #2

### 输入

```
4 5
4 4 4 4
count 1 4
add 1 4 3
count 1 4
add 2 3 40
count 1 4

```

### 输出

```
4
4
4

```



---

---
title: "Smile House"
layout: "post"
diff: 省选/NOI-
pid: CF147B
tag: ['倍增', '枚举']
---

# Smile House

## 题目描述

n个点，m条边，无向图但一条无向边的两个方向的边权不同，求图上最小正环的大小（定义正环为从一个点出发再回到这个点经过所有边边权之和为正）（定义最小正环的含义为这个正环经过的点数最少）

## 输入格式

第一行两个整数n，m，表示点数和边数



接下来m行，一行四个整数x,y,z,w，表示x到y有一条边，x到y的边权为z，y到x的边权为w

## 输出格式

一行一个整数，表示最小正环的大小（即这个正环上点的个数），如果没有正环输出0

## 样例 #1

### 输入

```
4 4
1 2 -10 3
1 3 1 -10
2 4 -10 -1
3 4 0 -3

```

### 输出

```
4

```



---

---
title: "Balance"
layout: "post"
diff: 省选/NOI-
pid: CF17C
tag: ['字符串', '枚举', '概率论']
---

# Balance

## 题目描述

1. 选择两个相邻字符，将第一个字符替换成第二个。 
2. 选择两个相邻字符，将第二个字符替换成第一个。 这样，通过任意多次的操作，可以得到许多不同的串，为了追求字符的平衡， 我们要求a,b,c三种字符在字符串中出现的次数两两之差都不能大于1。

你的任 务是，统计给定字符串通过任意多次的操作，能够得到的不同的平衡串的个数。

## 输入格式

输入文件包含2行。 第一行包含1个正整数n，表示字符串长度。 第二行包含1个长度为n的字符串。

## 输出格式

输出共1行，包含1个正整数，表示能够得到的平衡串的数量。由于答案可 能很大，因此输出时要对51123987取模。

## 样例 #1

### 输入

```
4
abca

```

### 输出

```
7

```

## 样例 #2

### 输入

```
4
abbc

```

### 输出

```
3

```

## 样例 #3

### 输入

```
2
ab

```

### 输出

```
1

```



---

---
title: "Field Should Not Be Empty"
layout: "post"
diff: 省选/NOI-
pid: CF1905F
tag: ['枚举']
---

# Field Should Not Be Empty

## 题目描述

You are given a permutation $ ^{\dagger} $ $ p $ of length $ n $ .

We call index $ x $ good if for all $ y < x $ it holds that $ p_y < p_x $ and for all $ y > x $ it holds that $ p_y > p_x $ . We call $ f(p) $ the number of good indices in $ p $ .

You can perform the following operation: pick $ 2 $ distinct indices $ i $ and $ j $ and swap elements $ p_i $ and $ p_j $ .

Find the maximum value of $ f(p) $ after applying the aforementioned operation exactly once.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test consists of multiple test cases. The first line of contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the length of the permutation $ p $ .

The second line of each test case contain $ n $ distinct integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ) — the elements of the permutation $ p $ .

It is guaranteed that sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum value of $ f(p) $ after performing the operation exactly once.

## 说明/提示

In the first test case, $ p = [1,2,3,4,5] $ and $ f(p)=5 $ which is already maximum possible. But must perform the operation anyway. We can get $ f(p)=3 $ by choosing $ i=1 $ and $ j=2 $ which makes $ p = [2,1,3,4,5] $ .

In the second test case, we can transform $ p $ into $ [1,2,3,4,5] $ by choosing $ i=1 $ and $ j=2 $ . Thus $ f(p)=5 $ .

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
5
2 1 3 4 5
7
2 1 5 3 7 6 4
6
2 3 5 4 1 6
7
7 6 5 4 3 2 1
```

### 输出

```
3
5
2
3
2
```



---

---
title: "Palindromic Problem"
layout: "post"
diff: 省选/NOI-
pid: CF1913F
tag: ['字符串', '枚举']
---

# Palindromic Problem

## 题目描述

You are given a string $ s $ of length $ n $ , consisting of lowercase Latin letters.

You are allowed to replace at most one character in the string with an arbitrary lowercase Latin letter.

Print the lexicographically minimal string that can be obtained from the original string and contains the maximum number of palindromes as substrings. Note that if a palindrome appears more than once as a substring, it is counted the same number of times it appears.

The string $ a $ is lexicographically smaller than the string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ are different, the string $ a $ contains a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \leq n \leq 3 \cdot 10^5 $ ) — the number of characters in the string.

The second line contains the string $ s $ itself, consisting of exactly $ n $ lowercase Latin letters.

## 输出格式

In the first line, print one integer — the maximum number of palindromic substrings that can be obtained using the operation described in the statement at most once.

In the second line, print the string that can be obtained from $ s $ and has the maximum possible number of palindromic substrings. If there are multiple answers, print the lexicographically smallest one.

## 样例 #1

### 输入

```
5
aabaa
```

### 输出

```
15
aaaaa
```

## 样例 #2

### 输入

```
5
aaaaa
```

### 输出

```
15
aaaaa
```

## 样例 #3

### 输入

```
4
awoo
```

### 输出

```
7
aooo
```



---

---
title: "The Next Good String"
layout: "post"
diff: 省选/NOI-
pid: CF196D
tag: ['字符串', '枚举', '哈希 hashing']
---

# The Next Good String

## 题目描述

In problems on strings one often has to find a string with some particular properties. The problem authors were reluctant to waste time on thinking of a name for some string so they called it good. A string is good if it doesn't have palindrome substrings longer than or equal to $ d $ .

You are given string $ s $ , consisting only of lowercase English letters. Find a good string $ t $ with length $ |s| $ , consisting of lowercase English letters, which is lexicographically larger than $ s $ . Of all such strings string $ t $ must be lexicographically minimum.

We will call a non-empty string $ s[a ... b]=s_{a}s_{a+1}...\ s_{b} $ $ (1<=a<=b<=|s|) $ a substring of string $ s=s_{1}s_{2}...\ s_{|s|} $ .

A non-empty string $ s=s_{1}s_{2}...\ s_{n} $ is called a palindrome if for all $ i $ from $ 1 $ to $ n $ the following fulfills: $ s_{i}=s_{n-i+1} $ . In other words, palindrome read the same in both directions.

String $ x=x_{1}x_{2}...\ x_{|x|} $ is lexicographically larger than string $ y=y_{1}y_{2}...\ y_{|y|} $ , if either $ |x|&gt;|y| $ and $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{|y|}=y_{|y|} $ , or there exists such number $ r $ $ (r&lt;|x|,r&lt;|y|) $ , that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&gt;y_{r+1} $ . Characters in such strings are compared like their ASCII codes.

## 输入格式

The first line contains integer $ d $ ( $ 1<=d<=|s| $ ).

The second line contains a non-empty string $ s $ , its length is no more than $ 4·10^{5} $ characters. The string consists of lowercase English letters.

## 输出格式

Print the good string that lexicographically follows $ s $ , has the same length and consists of only lowercase English letters. If such string does not exist, print "Impossible" (without the quotes).

## 样例 #1

### 输入

```
3
aaaaaaa

```

### 输出

```
aabbcaa

```

## 样例 #2

### 输入

```
3
zzyzzzz

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
4
abbabbbabbb

```

### 输出

```
abbbcaaabab

```



---

---
title: "Serval and Colorful Array (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2085F2
tag: ['贪心', '枚举', '差分']
---

# Serval and Colorful Array (Hard Version)

## 题目描述

这是该问题的困难版本。两个版本的区别在于此版本中 $n \leq 4 \cdot 10^5$。仅当您解决了该问题的所有版本时才能进行 hack。

Serval 有一个魔法数 $k$（$k \geq 2$）。我们称数组 $r$ 为 colorful 当且仅当：
- $r$ 的长度为 $k$，且
- $1$ 到 $k$ 之间的每个整数在 $r$ 中恰好出现一次。

给定一个由 $n$ 个介于 $1$ 到 $k$ 的整数组成的数组 $a$。保证 $1$ 到 $k$ 之间的每个整数在 $a$ 中至少出现一次。您可以对 $a$ 执行以下操作：
- 选择一个下标 $i$（$1 \leq i < n$），然后交换 $a_i$ 和 $a_{i+1}$。

求使得 $a$ 中至少存在一个 colorful 子数组$^{\text{∗}}$所需的最小操作次数。可以证明在题目约束下这总是可行的。

$^{\text{∗}}$数组 $b$ 是数组 $a$ 的子数组，当且仅当 $b$ 可以通过从 $a$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 1000$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$2 \leq k \leq n \leq 4 \cdot 10^5$）——数组 $a$ 的长度和 Serval 的魔法数。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \leq a_i \leq k$）——数组 $a$ 的元素。保证 $1$ 到 $k$ 之间的每个整数在 $a$ 中至少出现一次。

保证所有测试用例的 $n$ 之和不超过 $4 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数 —— 使得 $a$ 中至少存在一个 colorful 子数组所需的最小操作次数。

## 说明/提示

第一个测试案例中，由于子数组 $[a_1, a_2] = [1, 2]$ 和 $[a_2, a_3] = [2, 1]$ 已经是 colorful 的，因此无需执行任何操作。答案为 $0$。

第二个测试案例中，我们可以交换 $a_1$ 和 $a_2$ 得到 $[1, \underline{2, 1, 3}, 1, 1, 2]$，其中包含一个 colorful 子数组 $[a_2, a_3, a_4] = [2, 1, 3]$。由于原数组初始时没有 colorful 子数组，因此答案为 $1$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
3 2
1 2 1
7 3
2 1 1 3 1 1 2
6 3
1 1 2 2 2 3
6 3
1 2 2 2 2 3
10 5
5 1 3 1 1 2 2 4 1 3
9 4
1 2 3 3 3 3 3 2 4
```

### 输出

```
0
1
2
3
4
5
```



---

---
title: "Two Permutations"
layout: "post"
diff: 省选/NOI-
pid: CF213E
tag: ['线段树', '平衡树', '枚举', '哈希 hashing']
---

# Two Permutations

## 题目描述

Rubik is very keen on number permutations.

A permutation $ a $ with length $ n $ is a sequence, consisting of $ n $ different numbers from 1 to $ n $ . Element number $ i $ $ (1<=i<=n) $ of this permutation will be denoted as $ a_{i} $ .

Furik decided to make a present to Rubik and came up with a new problem on permutations. Furik tells Rubik two number permutations: permutation $ a $ with length $ n $ and permutation $ b $ with length $ m $ . Rubik must give an answer to the problem: how many distinct integers $ d $ exist, such that sequence $ c $ $ (c_{1}=a_{1}+d,c_{2}=a_{2}+d,...,c_{n}=a_{n}+d) $ of length $ n $ is a subsequence of $ b $ .

Sequence $ a $ is a subsequence of sequence $ b $ , if there are such indices $ i_{1},i_{2},...,i_{n} $ $ (1<=i_{1}&lt;i_{2}&lt;...&lt;i_{n}<=m) $ , that $ a_{1}=b_{i1} $ , $ a_{2}=b_{i2} $ , $ ... $ , $ a_{n}=b_{in} $ , where $ n $ is the length of sequence $ a $ , and $ m $ is the length of sequence $ b $ .

You are given permutations $ a $ and $ b $ , help Rubik solve the given problem.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n<=m<=200000) $ — the sizes of the given permutations. The second line contains $ n $ distinct integers — permutation $ a $ , the third line contains $ m $ distinct integers — permutation $ b $ . Numbers on the lines are separated by spaces.

## 输出格式

On a single line print the answer to the problem.

## 样例 #1

### 输入

```
1 1
1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1 2
1
2 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 3
2 3 1
1 2 3

```

### 输出

```
0

```



---

---
title: "Number Challenge"
layout: "post"
diff: 省选/NOI-
pid: CF235E
tag: ['数学', '枚举', '概率论']
---

# Number Challenge

## 题目描述

Let's denote $ d(n) $ as the number of divisors of a positive integer $ n $ . You are given three integers $ a $ , $ b $ and $ c $ . Your task is to calculate the following sum:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF235E/6b4d9893ce96bd0459ff1289a8bf3491052ac12a.png)Find the sum modulo $ 1073741824 $ $ (2^{30}) $ .

## 输入格式

The first line contains three space-separated integers $ a $ , $ b $ and $ c $ ( $ 1<=a,b,c<=2000 $ ).

## 输出格式

Print a single integer — the required sum modulo $ 1073741824 $ $ (2^{30}) $ .

## 说明/提示

For the first example.

- $ d(1·1·1)=d(1)=1 $ ;
- $ d(1·1·2)=d(2)=2 $ ;
- $ d(1·2·1)=d(2)=2 $ ;
- $ d(1·2·2)=d(4)=3 $ ;
- $ d(2·1·1)=d(2)=2 $ ;
- $ d(2·1·2)=d(4)=3 $ ;
- $ d(2·2·1)=d(4)=3 $ ;
- $ d(2·2·2)=d(8)=4 $ .

So the result is $ 1+2+2+3+2+3+3+4=20 $ .

## 样例 #1

### 输入

```
2 2 2

```

### 输出

```
20

```

## 样例 #2

### 输入

```
4 4 4

```

### 输出

```
328

```

## 样例 #3

### 输入

```
10 10 10

```

### 输出

```
11536

```



---

---
title: "Maxim and Increasing Subsequence"
layout: "post"
diff: 省选/NOI-
pid: CF261D
tag: ['线段树', '树状数组', '枚举']
---

# Maxim and Increasing Subsequence

## 题目描述

Maxim loves sequences, especially those that strictly increase. He is wondering, what is the length of the longest increasing subsequence of the given sequence $ a $ ?

Sequence $ a $ is given as follows:

- the length of the sequence equals $ n×t $ ;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261D/62550b81a494c59fe3493af08329ebf8f9d7bb9b.png) $ (1<=i<=n×t) $ , where operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261D/946bcc44e053027f1f6b5dfc3143583e661988f5.png) means taking the remainder after dividing number $ x $ by number $ y $ .

Sequence $ s_{1},s_{2},...,s_{r} $ of length $ r $ is a subsequence of sequence $ a_{1},a_{2},...,a_{n} $ , if there is such increasing sequence of indexes $ i_{1},i_{2},...,i_{r} $ $ (1<=i_{1}&lt;i_{2}&lt;...\ &lt;i_{r}<=n) $ , that $ a_{ij}=s_{j} $ . In other words, the subsequence can be obtained from the sequence by crossing out some elements.

Sequence $ s_{1},s_{2},...,s_{r} $ is increasing, if the following inequality holds: $ s_{1}&lt;s_{2}&lt;...&lt;s_{r} $ .

Maxim have $ k $ variants of the sequence $ a $ . Help Maxim to determine for each sequence the length of the longest increasing subsequence.

## 输入格式

The first line contains four integers $ k $ , $ n $ , $ maxb $ and $ t $ $ (1<=k<=10; 1<=n,maxb<=10^{5}; 1<=t<=10^{9}; n×maxb<=2·10^{7}) $ . Each of the next $ k $ lines contain $ n $ integers $ b_{1},b_{2},...,b_{n} $ $ (1<=b_{i}<=maxb) $ .

Note that for each variant of the sequence $ a $ the values $ n $ , $ maxb $ and $ t $ coincide, the only arrays $ b $ s differ.

The numbers in the lines are separated by single spaces.

## 输出格式

Print $ k $ integers — the answers for the variants of the sequence $ a $ . Print the answers in the order the variants follow in the input.

## 样例 #1

### 输入

```
3 3 5 2
3 2 1
1 2 3
2 3 1

```

### 输出

```
2
3
3

```



---

---
title: "Greg and Caves"
layout: "post"
diff: 省选/NOI-
pid: CF295D
tag: ['动态规划 DP', '枚举', '前缀和']
---

# Greg and Caves

## 题目描述

Greg有一个8868，其屏幕为一$n \times m$的矩形，每个像素可以是黑色或白色。我们考虑将8868的行从上到下编号为1到$n$。类似地，8868的列从左到右编号为1到$m$



Greg认为8868显示一个洞时，当且仅当以下情况：



- $\exist$区间$[l,r](1 \leq l \leq r \leq n)$，使得每一行恰有两个黑色像素，而所有其他行只有白色像素

- $\exist$行$t(l \leq t \leq r)$，使得对于$\forall(i,j)(l \leq i \leq j \leq t)$，第$i$行中黑色单元格之间列的集合$S_1$，与第$j$行中黑色单元格之间列的集合$S_2$，满足$S_1 \subseteq S_2$，同样对于$\forall (i,j)(t \leq i \leq j \leq r)$，第$i$行中黑色单元格之间列的集合$S_1$，与第$j$行中黑色单元格之间列的集合$S_2$，满足$S_2 \subseteq S_1$，



Greg想知道，有多少种方案能让他的8868显示一个洞。当且仅当两个屏幕存在一个位置像素颜色不同，两种方案不同



帮帮Greg吧

## 输入格式

第一行两个整数$n$，$m$表示8868的分辨率$(1 \leq n,m \leq 2000)$

## 输出格式

一行，答案在模$1e9+7$意义下的数值

## 样例 #1

### 输入

```
1 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
4 4

```

### 输出

```
485

```

## 样例 #3

### 输入

```
3 5

```

### 输出

```
451

```



---

---
title: "Cats Transport"
layout: "post"
diff: 省选/NOI-
pid: CF311B
tag: ['枚举', '斜率优化', '前缀和']
---

# Cats Transport

## 题目描述

Zxr960115 is owner of a large farm. He feeds $ m $ cute cats and employs $ p $ feeders. There's a straight road across the farm and $ n $ hills along the road, numbered from 1 to $ n $ from left to right. The distance between hill $ i $ and $ (i-1) $ is $ d_{i} $ meters. The feeders live in hill 1.

One day, the cats went out to play. Cat $ i $ went on a trip to hill $ h_{i} $ , finished its trip at time $ t_{i} $ , and then waited at hill $ h_{i} $ for a feeder. The feeders must take all the cats. Each feeder goes straightly from hill 1 to $ n $ without waiting at a hill and takes all the waiting cats at each hill away. Feeders walk at a speed of 1 meter per unit time and are strong enough to take as many cats as they want.

For example, suppose we have two hills $ (d_{2}=1) $ and one cat that finished its trip at time 3 at hill 2 $ (h_{1}=2) $ . Then if the feeder leaves hill 1 at time 2 or at time 3, he can take this cat, but if he leaves hill 1 at time 1 he can't take it. If the feeder leaves hill 1 at time 2, the cat waits him for 0 time units, if the feeder leaves hill 1 at time 3, the cat waits him for 1 time units.

Your task is to schedule the time leaving from hill 1 for each feeder so that the sum of the waiting time of all cats is minimized.

## 输入格式

The first line of the input contains three integers $n,m,p$ $(2 \le n\le 10^5,1 \le m \le 10^5, 1\le p \le 100)$.

The second line contains $n-1$ positive integers $d_{2},d_{3},...,d_{n}$  $(1 \le d_{i} < 10^{4}) .$

Each of the next $m$ lines contains two integers $h_i$ and $t_i$ $(1 \le h_i \le n,0 \le t_i \le 10^9)$.

## 输出格式

Output an integer, the minimum sum of waiting time of all cats.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
4 6 2
1 3 5
1 0
2 1
4 9
1 10
2 10
3 12

```

### 输出

```
3

```



---

---
title: "Tricky Function"
layout: "post"
diff: 省选/NOI-
pid: CF429D
tag: ['枚举', '分治', '未知标签296']
---

# Tricky Function

## 题目描述

Iahub and Sorin are the best competitive programmers in their town. However, they can't both qualify to an important contest. The selection will be made with the help of a single problem. Blatnatalag, a friend of Iahub, managed to get hold of the problem before the contest. Because he wants to make sure Iahub will be the one qualified, he tells Iahub the following task.

You're given an (1-based) array $ a $ with $ n $ elements. Let's define function $ f(i,j) $ $ (1<=i,j<=n) $ as $ (i-j)^{2}+g(i,j)^{2} $ . Function g is calculated by the following pseudo-code:

```
int g(int i, int j) {
    int sum = 0;
    for (int k = min(i, j) + 1; k <= max(i, j); k = k + 1)
        sum = sum + a[k];
    return sum;
}
```
Find a value $ min_{i≠j}  f(i,j) $ .

Probably by now Iahub already figured out the solution to this problem. Can you?

## 输入格式

The first line of input contains a single integer $ n $ ( $ 2<=n<=100000 $ ). Next line contains $ n $ integers $ a[1] $ , $ a[2] $ , ..., $ a[n] $ ( $ -10^{4}<=a[i]<=10^{4} $ ).

## 输出格式

Output a single integer — the value of $ min_{i≠j}  f(i,j) $ .

## 样例 #1

### 输入

```
4
1 0 0 -1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
1 -1

```

### 输出

```
2

```



---

---
title: "Jzzhu and Apples"
layout: "post"
diff: 省选/NOI-
pid: CF449C
tag: ['枚举', '素数判断,质数,筛法', '栈']
---

# Jzzhu and Apples

## 题目描述

Jzzhu has picked $ n $ apples from his big apple tree. All the apples are numbered from $ 1 $ to $ n $ . Now he wants to sell them to an apple store.

Jzzhu will pack his apples into groups and then sell them. Each group must contain two apples, and the greatest common divisor of numbers of the apples in each group must be greater than 1. Of course, each apple can be part of at most one group.

Jzzhu wonders how to get the maximum possible number of groups. Can you help him?

## 输入格式

A single integer $ n $ $ (1<=n<=10^{5}) $ , the number of the apples.

## 输出格式

The first line must contain a single integer $ m $ , representing the maximum number of groups he can get. Each of the next $ m $ lines must contain two integers — the numbers of apples in the current group.

If there are several optimal answers you can print any of them.

## 样例 #1

### 输入

```
6

```

### 输出

```
2
6 3
2 4

```

## 样例 #2

### 输入

```
9

```

### 输出

```
3
9 3
2 4
6 8

```

## 样例 #3

### 输入

```
2

```

### 输出

```
0

```



---

---
title: "Chess"
layout: "post"
diff: 省选/NOI-
pid: CF57E
tag: ['模拟', '搜索', '枚举']
---

# Chess

## 题目描述

Brian the Rabbit adores chess. Not long ago he argued with Stewie the Rabbit that a knight is better than a king. To prove his point he tries to show that the knight is very fast but Stewie doesn't accept statements without evidence. He constructed an infinite chessboard for Brian, where he deleted several squares to add some more interest to the game. Brian only needs to count how many different board squares a knight standing on a square with coordinates of $ (0,0) $ can reach in no more than $ k $ moves. Naturally, it is forbidden to move to the deleted squares.

Brian doesn't very much like exact sciences himself and is not acquainted with programming, that's why he will hardly be able to get ahead of Stewie who has already started solving the problem. Help Brian to solve the problem faster than Stewie.

## 输入格式

The first line contains two integers $ k $ and $ n $ ( $ 0<=k<=10^{18},0<=n<=440 $ ) which are correspondingly the maximal number of moves a knight can make and the number of deleted cells. Then follow $ n $ lines, each giving the coordinates of a deleted square in the form $ (x_{i},y_{i}) $ ( $ |x_{i}|<=10,|y_{i}|<=10 $ ). All the numbers are integer, the deleted squares are different and it is guaranteed that the square $ (0,0) $ is not deleted.

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cin (also you may use %I64d).

## 输出格式

You must print the answer on a single line. As it can be rather long, you should print it modulo $ 1000000007 $ .

## 样例 #1

### 输入

```
1 0

```

### 输出

```
9

```

## 样例 #2

### 输入

```
2 7
-1 2
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1

```

### 输出

```
9

```



---

---
title: "Three States"
layout: "post"
diff: 省选/NOI-
pid: CF590C
tag: ['枚举']
---

# Three States

## 题目描述

The famous global economic crisis is approaching rapidly, so the states of Berman, Berance and Bertaly formed an alliance and allowed the residents of all member states to freely pass through the territory of any of them. In addition, it was decided that a road between the states should be built to guarantee so that one could any point of any country can be reached from any point of any other State.

Since roads are always expensive, the governments of the states of the newly formed alliance asked you to help them assess the costs. To do this, you have been issued a map that can be represented as a rectangle table consisting of $ n $ rows and $ m $ columns. Any cell of the map either belongs to one of three states, or is an area where it is allowed to build a road, or is an area where the construction of the road is not allowed. A cell is called passable, if it belongs to one of the states, or the road was built in this cell. From any passable cells you can move up, down, right and left, if the cell that corresponds to the movement exists and is passable.

Your task is to construct a road inside a minimum number of cells, so that it would be possible to get from any cell of any state to any cell of any other state using only passable cells.

It is guaranteed that initially it is possible to reach any cell of any state from any cell of this state, moving only along its cells. It is also guaranteed that for any state there is at least one cell that belongs to it.

## 输入格式

The first line of the input contains the dimensions of the map $ n $ and $ m $ ( $ 1<=n,m<=1000 $ ) — the number of rows and columns respectively.

Each of the next $ n $ lines contain $ m $ characters, describing the rows of the map. Digits from $ 1 $ to $ 3 $ represent the accessory to the corresponding state. The character '.' corresponds to the cell where it is allowed to build a road and the character '\#' means no construction is allowed in this cell.

## 输出格式

Print a single integer — the minimum number of cells you need to build a road inside in order to connect all the cells of all states. If such a goal is unachievable, print -1.

## 样例 #1

### 输入

```
4 5
11..2
#..22
#.323
.#333
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 5
1#2#3

```

### 输出

```
-1

```



---

---
title: "Sandy and Nuts"
layout: "post"
diff: 省选/NOI-
pid: CF599E
tag: ['动态规划 DP', '枚举', '最近公共祖先 LCA']
---

# Sandy and Nuts

## 题目描述

Rooted tree is a connected graph without any simple cycles with one vertex selected as a root. In this problem the vertex number $ 1 $ will always serve as a root.

Lowest common ancestor of two vertices $ u $ and $ v $ is the farthest from the root vertex that lies on both the path from $ u $ to the root and on path from $ v $ to the root. We will denote it as $ LCA(u,v) $ .

Sandy had a rooted tree consisting of $ n $ vertices that she used to store her nuts. Unfortunately, the underwater storm broke her tree and she doesn't remember all it's edges. She only managed to restore $ m $ edges of the initial tree and $ q $ triples $ a_{i} $ , $ b_{i} $ and $ c_{i} $ , for which she supposes $ LCA(a_{i},b_{i})=c_{i} $ .

Help Sandy count the number of trees of size $ n $ with vertex $ 1 $ as a root, that match all the information she remembered. If she made a mess and there are no such trees then print $ 0 $ . Two rooted trees are considered to be distinct if there exists an edge that occur in one of them and doesn't occur in the other one.

## 输入格式

The first line of the input contains three integers $ n $ , $ m $ and $ q $ ( $ 1<=n<=13,0<=m<n,0<=q<=100 $ ) — the number of vertices, the number of edges and $ LCA $ triples remembered by Sandy respectively.

Each of the next $ m $ lines contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n,u_{i}≠v_{i} $ ) — the numbers of vertices connected by the $ i $ -th edge. It's guaranteed that this set of edges is a subset of edges of some tree.

The last $ q $ lines contain the triplets of numbers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ ( $ 1<=a_{i},b_{i},c_{i}<=n) $ . Each of these triples define $ LCA(a_{i},b_{i})=c_{i} $ . It's not guaranteed that there exists a tree that satisfy all the given $ LCA $ conditions.

## 输出格式

Print a single integer — the number of trees of size $ n $ that satisfy all the conditions.

## 说明/提示

In the second sample correct answer looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599E/3a06f49f1bab15c25fa9029dff674e9bd2958cf5.png)In the third sample there are two possible trees:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599E/5bc65707292dd568a0ac7a018a2f94f9303bf3c4.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599E/bacea40f00b7ff26956d9e8aa34e3c4499c85dc6.png)In the fourth sample the answer is $ 0 $ because the information about $ LCA $ is inconsistent.

## 样例 #1

### 输入

```
4 0 0

```

### 输出

```
16

```

## 样例 #2

### 输入

```
4 0 1
3 4 2

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 1 0
1 2

```

### 输出

```
2

```

## 样例 #4

### 输入

```
3 0 2
2 3 2
2 3 1

```

### 输出

```
0

```

## 样例 #5

### 输入

```
4 1 2
1 2
2 2 2
3 4 2

```

### 输出

```
1

```



---

---
title: "Group Projects"
layout: "post"
diff: 省选/NOI-
pid: CF626F
tag: ['动态规划 DP', '枚举']
---

# Group Projects

## 题目描述

There are $ n $ students in a class working on group projects. The students will divide into groups (some students may be in groups alone), work on their independent pieces, and then discuss the results together. It takes the $ i $ -th student $ a_{i} $ minutes to finish his/her independent piece.

If students work at different paces, it can be frustrating for the faster students and stressful for the slower ones. In particular, the imbalance of a group is defined as the maximum $ a_{i} $ in the group minus the minimum $ a_{i} $ in the group. Note that a group containing a single student has an imbalance of $ 0 $ . How many ways are there for the students to divide into groups so that the total imbalance of all groups is at most $ k $ ?

Two divisions are considered distinct if there exists a pair of students who work in the same group in one division but different groups in the other.

## 输入格式

The first line contains two space-separated integers $ n $ and $ k $ ( $ 1<=n<=200 $ , $ 0<=k<=1000 $ ) — the number of students and the maximum total imbalance allowed, respectively.

The second line contains $ n $ space-separated integers $ a_{i} $ ( $ 1<=a_{i}<=500 $ ) — the time it takes the $ i $ -th student to complete his/her independent piece of work.

## 输出格式

Print a single integer, the number of ways the students can form groups. As the answer may be large, print its value modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, we have three options:

- The first and second students form a group, and the third student forms a group. Total imbalance is $ 2+0=2 $ .
- The first student forms a group, and the second and third students form a group. Total imbalance is $ 0+1=1 $ .
- All three students form their own groups. Total imbalance is $ 0 $ .

In the third sample, the total imbalance must be $ 0 $ , so each student must work individually.

## 样例 #1

### 输入

```
3 2
2 4 5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 3
7 8 9 10

```

### 输出

```
13

```

## 样例 #3

### 输入

```
4 0
5 10 20 21

```

### 输出

```
1

```



---

---
title: "Thief in a Shop"
layout: "post"
diff: 省选/NOI-
pid: CF632E
tag: ['枚举', '排序', '背包 DP']
---

# Thief in a Shop

## 题目描述

A thief made his way to a shop.

As usual he has his lucky knapsack with him. The knapsack can contain $ k $ objects. There are $ n $ kinds of products in the shop and an infinite number of products of each kind. The cost of one product of kind $ i $ is $ a_{i} $ .

The thief is greedy, so he will take exactly $ k $ products (it's possible for some kinds to take several products of that kind).

Find all the possible total costs of products the thief can nick into his knapsack.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n,k<=1000 $ ) — the number of kinds of products and the number of products the thief will take.

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=1000 $ ) — the costs of products for kinds from $ 1 $ to $ n $ .

## 输出格式

Print the only line with all the possible total costs of stolen products, separated by a space. The numbers should be printed in the ascending order.

## 样例 #1

### 输入

```
3 2
1 2 3

```

### 输出

```
2 3 4 5 6

```

## 样例 #2

### 输入

```
5 5
1 1 1 1 1

```

### 输出

```
5

```

## 样例 #3

### 输入

```
3 3
3 5 11

```

### 输出

```
9 11 13 15 17 19 21 25 27 33

```



---

---
title: "The Chocolate Spree"
layout: "post"
diff: 省选/NOI-
pid: CF633F
tag: ['动态规划 DP', '枚举', '深度优先搜索 DFS']
---

# The Chocolate Spree

## 题目描述

Alice and Bob have a tree (undirected acyclic connected graph). There are $ a_{i} $ chocolates waiting to be picked up in the $ i $ -th vertex of the tree. First, they choose two different vertices as their starting positions (Alice chooses first) and take all the chocolates contained in them.

Then, they alternate their moves, selecting one vertex at a time and collecting all chocolates from this node. To make things more interesting, they decided that one can select a vertex only if he/she selected a vertex adjacent to that one at his/her previous turn and this vertex has not been already chosen by any of them during other move.

If at any moment one of them is not able to select the node that satisfy all the rules, he/she will skip his turns and let the other person pick chocolates as long as he/she can. This goes on until both of them cannot pick chocolates any further.

Due to their greed for chocolates, they want to collect as many chocolates as possible. However, as they are friends they only care about the total number of chocolates they obtain together. What is the maximum total number of chocolates they may pick?

## 输入格式

The first line of the input contains the single integer $ n $ ( $ 2<= $ n $ <=100000 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ), $ i $ -th of these numbers stands for the number of chocolates stored at the node $ i $ .

Then follow $ n-1 $ lines that describe the tree. Each of them contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) — indices of vertices connected by the $ i $ -th edge.

## 输出格式

Print the number of chocolates Alice and Bob can collect together if they behave optimally.

## 说明/提示

In the first sample, Alice may start at the vertex $ 9 $ and Bob at vertex $ 8 $ . Alice will select vertex $ 1 $ and Bob has no options now. Alice selects the vertex $ 7 $ and they both stop.

In the second sample, both of them will pick either of the nodes alternately.

## 样例 #1

### 输入

```
9
1 2 3 4 5 6 7 8 9
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9

```

### 输出

```
25

```

## 样例 #2

### 输入

```
2
20 10
1 2

```

### 输出

```
30

```



---

---
title: "Inversions After Shuffle"
layout: "post"
diff: 省选/NOI-
pid: CF749E
tag: ['树状数组', '枚举', '期望']
---

# Inversions After Shuffle

## 题目描述

You are given a permutation of integers from $ 1 $ to $ n $ . Exactly once you apply the following operation to this permutation: pick a random segment and shuffle its elements. Formally:

1. Pick a random segment (continuous subsequence) from $ l $ to $ r $ . All ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF749E/150441d31156a32e0b2da63844d600138a543898.png) segments are equiprobable.
2. Let $ k=r-l+1 $ , i.e. the length of the chosen segment. Pick a random permutation of integers from $ 1 $ to $ k $ , $ p_{1},p_{2},...,p_{k} $ . All $ k! $ permutation are equiprobable.
3. This permutation is applied to elements of the chosen segment, i.e. permutation $ a_{1},a_{2},...,a_{l-1},a_{l},a_{l+1},...,a_{r-1},a_{r},a_{r+1},...,a_{n} $ is transformed to $ a_{1},a_{2},...,a_{l-1},a_{l-1+p1},a_{l-1+p2},...,a_{l-1+pk-1},a_{l-1+pk},a_{r+1},...,a_{n} $ .

Inversion if a pair of elements (not necessary neighbouring) with the wrong relative order. In other words, the number of inversion is equal to the number of pairs $ (i,j) $ such that $ i&lt;j $ and $ a_{i}&gt;a_{j} $ . Find the expected number of inversions after we apply exactly one operation mentioned above.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the length of the permutation.

The second line contains $ n $ distinct integers from $ 1 $ to $ n $ — elements of the permutation.

## 输出格式

Print one real value — the expected number of inversions. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-9} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF749E/d8d110e69d298146d951837cc2710d1c4cc74a7d.png).

## 样例 #1

### 输入

```
3
2 3 1

```

### 输出

```
1.916666666666666666666666666667

```



---

---
title: "Hitchhiking in the Baltic States"
layout: "post"
diff: 省选/NOI-
pid: CF809D
tag: ['动态规划 DP', '平衡树', '枚举']
---

# Hitchhiking in the Baltic States

## 题目描述

Leha and Noora decided to go on a trip in the Baltic States. As you know from the previous problem, Leha has lost his car on the parking of the restaurant. Unfortunately, requests to the watchman didn't helped hacker find the car, so friends decided to go hitchhiking.

In total, they intended to visit $ n $ towns. However it turned out that sights in $ i $ -th town are open for visitors only on days from $ l_{i} $ to $ r_{i} $ .

What to do? Leha proposed to choose for each town $ i $ a day, when they will visit this town, i.e any integer $ x_{i} $ in interval $ [l_{i},r_{i}] $ . After that Noora choses some subsequence of towns $ id_{1},id_{2},...,id_{k} $ , which friends are going to visit, that at first they are strictly increasing, i.e $ id_{i}<id_{i+1} $ is for all integers $ i $ from $ 1 $ to $ k-1 $ , but also the dates of the friends visits are strictly increasing, i.e $ x_{idi}<x_{idi+1} $ is true for all integers $ i $ from $ 1 $ to $ k-1 $ .

Please help Leha and Noora in choosing such $ x_{i} $ for each town $ i $ , and such subsequence of towns $ id_{1},id_{2},...,id_{k} $ , so that friends can visit maximal number of towns.

You may assume, that Leha and Noora can start the trip any day.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=3·10^{5} $ ) denoting the number of towns Leha and Noora intended to visit.

Each line $ i $ of the $ n $ subsequent lines contains two integers $ l_{i} $ , $ r_{i} $ $ (1<=l_{i}<=r_{i}<=10^{9}) $ , denoting that sights in $ i $ -th town are open for visitors on any day ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809D/67e7c15a830b4bf2b41222394fc99591b0cfcff8.png).

## 输出格式

Print a single integer denoting the maximal number of towns, that Leha and Noora can visit.

## 说明/提示

Consider the first example.

Let's take this plan: let's visit the sight in the second town on the first day, in the third town on the third day and in the fifth town on the fourth. That's would be the optimal answer.

## 样例 #1

### 输入

```
5
6 6
1 2
3 4
2 2
1 4

```

### 输出

```
3

```



---

---
title: "Karen and Cards"
layout: "post"
diff: 省选/NOI-
pid: CF815D
tag: ['枚举', '前缀和', '概率论']
---

# Karen and Cards

## 题目描述

Karen just got home from the supermarket, and is getting ready to go to sleep.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815D/d6b07c74db93ed793c45ff910937379fe578d8dc.png)After taking a shower and changing into her pajamas, she looked at her shelf and saw an album. Curious, she opened it and saw a trading card collection.

She recalled that she used to play with those cards as a child, and, although she is now grown-up, she still wonders a few things about it.

Each card has three characteristics: strength, defense and speed. The values of all characteristics of all cards are positive integers. The maximum possible strength any card can have is $ p $ , the maximum possible defense is $ q $ and the maximum possible speed is $ r $ .

There are $ n $ cards in her collection. The $ i $ -th card has a strength $ a_{i} $ , defense $ b_{i} $ and speed $ c_{i} $ , respectively.

A card beats another card if at least two of its characteristics are strictly greater than the corresponding characteristics of the other card.

She now wonders how many different cards can beat all the cards in her collection. Two cards are considered different if at least one of their characteristics have different values.

## 输入格式

The first line of input contains four integers, $ n $ , $ p $ , $ q $ and $ r $ ( $ 1<=n,p,q,r<=500000 $ ), the number of cards in the collection, the maximum possible strength, the maximum possible defense, and the maximum possible speed, respectively.

The next $ n $ lines each contain three integers. In particular, the $ i $ -th line contains $ a_{i} $ , $ b_{i} $ and $ c_{i} $ ( $ 1<=a_{i}<=p $ , $ 1<=b_{i}<=q $ , $ 1<=c_{i}<=r $ ), the strength, defense and speed of the $ i $ -th collection card, respectively.

## 输出格式

Output a single integer on a line by itself, the number of different cards that can beat all the cards in her collection.

## 说明/提示

In the first test case, the maximum possible strength is $ 4 $ , the maximum possible defense is $ 4 $ and the maximum possible speed is $ 5 $ . Karen has three cards:

- The first card has strength $ 2 $ , defense $ 2 $ and speed $ 5 $ .
- The second card has strength $ 1 $ , defense $ 3 $ and speed $ 4 $ .
- The third card has strength $ 4 $ , defense $ 1 $ and speed $ 1 $ .

There are $ 10 $ cards that beat all the cards here:

1. The card with strength $ 3 $ , defense $ 3 $ and speed $ 5 $ .
2. The card with strength $ 3 $ , defense $ 4 $ and speed $ 2 $ .
3. The card with strength $ 3 $ , defense $ 4 $ and speed $ 3 $ .
4. The card with strength $ 3 $ , defense $ 4 $ and speed $ 4 $ .
5. The card with strength $ 3 $ , defense $ 4 $ and speed $ 5 $ .
6. The card with strength $ 4 $ , defense $ 3 $ and speed $ 5 $ .
7. The card with strength $ 4 $ , defense $ 4 $ and speed $ 2 $ .
8. The card with strength $ 4 $ , defense $ 4 $ and speed $ 3 $ .
9. The card with strength $ 4 $ , defense $ 4 $ and speed $ 4 $ .
10. The card with strength $ 4 $ , defense $ 4 $ and speed $ 5 $ .

In the second test case, the maximum possible strength is $ 10 $ , the maximum possible defense is $ 10 $ and the maximum possible speed is $ 10 $ . Karen has five cards, all with strength $ 1 $ , defense $ 1 $ and speed $ 1 $ .

Any of the $ 972 $ cards which have at least two characteristics greater than $ 1 $ can beat all of the cards in her collection.

## 样例 #1

### 输入

```
3 4 4 5
2 2 5
1 3 4
4 1 1

```

### 输出

```
10

```

## 样例 #2

### 输入

```
5 10 10 10
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1

```

### 输出

```
972

```



---

---
title: "Rusty String"
layout: "post"
diff: 省选/NOI-
pid: CF827E
tag: ['字符串', '枚举', '构造']
---

# Rusty String

## 题目描述

Grigory loves strings. Recently he found a metal strip on a loft. The strip had length $ n $ and consisted of letters "V" and "K". Unfortunately, rust has eaten some of the letters so that it's now impossible to understand which letter was written.

Grigory couldn't understand for a long time what these letters remind him of, so he became interested in the following question: if we put a letter "V" or "K" on each unreadable position, which values can the period of the resulting string be equal to?

A period of a string is such an integer $ d $ from $ 1 $ to the length of the string that if we put the string shifted by $ d $ positions to the right on itself, then all overlapping letters coincide. For example, $ 3 $ and $ 5 $ are periods of "VKKVK".

## 输入格式

There are several (at least one) test cases in the input. The first line contains single integer — the number of test cases.

There is an empty line before each test case. Each test case is described in two lines: the first line contains single integer $ n $ ( $ 1<=n<=5·10^{5} $ ) — the length of the string, the second line contains the string of length $ n $ , consisting of letters "V", "K" and characters "?". The latter means the letter on its position is unreadable.

It is guaranteed that the sum of lengths among all test cases doesn't exceed $ 5·10^{5} $ .

For hacks you can only use tests with one test case.

## 输出格式

For each test case print two lines. In the first line print the number of possible periods after we replace each unreadable letter with "V" or "K". In the next line print all these values in increasing order.

## 说明/提示

In the first test case from example we can obtain, for example, "VKKVK", which has periods $ 3 $ and $ 5 $ .

In the second test case we can obtain "VVVVVV" which has all periods from $ 1 $ to $ 6 $ .

In the third test case string "KVKV" has periods $ 2 $ and $ 4 $ , and string "KVKK" has periods $ 3 $ and $ 4 $ .

## 样例 #1

### 输入

```
3
 
5
V??VK
 
6
??????
 
4
?VK?

```

### 输出

```
2
3 5
6
1 2 3 4 5 6
3
2 3 4

```



---

---
title: "On the Bench"
layout: "post"
diff: 省选/NOI-
pid: CF840C
tag: ['动态规划 DP', '枚举']
---

# On the Bench

## 题目描述

A year ago on the bench in public park Leha found an array of $ n $ numbers. Leha believes that permutation $ p $ is right if for all $ 1<=i&lt;n $ condition, that $ a_{pi}·a_{pi+1} $ is not perfect square, holds. Leha wants to find number of right permutations modulo $ 10^{9}+7 $ .

## 输入格式

First line of input data contains single integer $ n $ ( $ 1<=n<=300 $ ) — length of the array.

Next line contains $ n $ integers $ a_{1},a_{2},...\ ,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — found array.

## 输出格式

Output single integer — number of right permutations modulo $ 10^{9}+7 $ .

## 说明/提示

For first example:

 $ [1,2,4] $ — right permutation, because $ 2 $ and $ 8 $ are not perfect squares.

 $ [1,4,2] $ — wrong permutation, because $ 4 $ is square of $ 2 $ .

 $ [2,1,4] $ — wrong permutation, because $ 4 $ is square of $ 2 $ .

 $ [2,4,1] $ — wrong permutation, because $ 4 $ is square of $ 2 $ .

 $ [4,1,2] $ — wrong permutation, because $ 4 $ is square of $ 2 $ .

 $ [4,2,1] $ — right permutation, because $ 8 $ and $ 2 $ are not perfect squares.

## 样例 #1

### 输入

```
3
1 2 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7
5 2 4 2 4 1 1

```

### 输出

```
144

```



---

---
title: "Shortest Path Problem?"
layout: "post"
diff: 省选/NOI-
pid: CF845G
tag: ['枚举', '线性基']
---

# Shortest Path Problem?

## 题目描述

You are given an undirected graph with weighted edges. The length of some path between two vertices is the bitwise xor of weights of all edges belonging to this path (if some edge is traversed more than once, then it is included in bitwise xor the same number of times). You have to find the minimum length of path between vertex $ 1 $ and vertex $ n $ .

Note that graph can contain multiple edges and loops. It is guaranteed that the graph is connected.

## 输入格式

The first line contains two numbers $ n $ and $ m $ ( $ 1<=n<=100000 $ , $ n-1<=m<=100000 $ ) — the number of vertices and the number of edges, respectively.

Then $ m $ lines follow, each line containing three integer numbers $ x $ , $ y $ and $ w $ ( $ 1<=x,y<=n $ , $ 0<=w<=10^{8} $ ). These numbers denote an edge that connects vertices $ x $ and $ y $ and has weight $ w $ .

## 输出格式

Print one number — the minimum length of path between vertices $ 1 $ and $ n $ .

## 样例 #1

### 输入

```
3 3
1 2 3
1 3 2
3 2 0

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 2
1 1 3
1 2 3

```

### 输出

```
0

```



---

---
title: "Willem, Chtholly and Seniorious"
layout: "post"
diff: 省选/NOI-
pid: CF896C
tag: ['暴力数据结构', '颜色段均摊（珂朵莉树 ODT）', '枚举', '排序', '构造']
---

# Willem, Chtholly and Seniorious

## 题目描述

【题面】
请你写一种奇怪的数据结构，支持：
- $1$  $l$  $r$  $x$ ：将$[l,r]$ 区间所有数加上$x$ 
- $2$  $l$  $r$  $x$ ：将$[l,r]$ 区间所有数改成$x$ 
- $3$  $l$  $r$  $x$ ：输出将$[l,r]$ 区间从小到大排序后的第$x$ 个数是的多少(即区间第$x$ 小，数字大小相同算多次，保证 $1\leq$  $x$  $\leq$  $r-l+1$  )
- $4$  $l$  $r$  $x$  $y$ ：输出$[l,r]$ 区间每个数字的$x$ 次方的和模$y$ 的值(即($\sum^r_{i=l}a_i^x$ ) $\mod y$ )

## 输入格式

输入一行四个整数$n,m,seed,v_{max}$ （$1\leq $  $n,m\leq 10^{5}$  ,$0\leq seed \leq 10^{9}+7$  $,1\leq vmax \leq 10^{9} $ ）
其中$n$ 表示数列长度，$m$ 表示操作次数，后面两个用于生成输入数据。
数据生成的伪代码如下
![](https://cdn.luogu.org/upload/pic/13887.png )

其中上面的op指题面中提到的四个操作。

## 输出格式

对于每个操作3和4，输出一行仅一个数。

## 样例 #1

### 输入

```
10 10 7 9

```

### 输出

```
2
1
0
3

```

## 样例 #2

### 输入

```
10 10 9 9

```

### 输出

```
1
1
3
3

```



---

---
title: "List Of Integers"
layout: "post"
diff: 省选/NOI-
pid: CF920G
tag: ['二分', '枚举', '容斥原理']
---

# List Of Integers

## 题目描述

Let's denote as $ L(x,p) $ an infinite sequence of integers $ y $ such that $ gcd(p,y)=1 $ and $ y>x $ (where $ gcd $ is the greatest common divisor of two integer numbers), sorted in ascending order. The elements of $ L(x,p) $ are $ 1 $ -indexed; for example, $ 9 $ , $ 13 $ and $ 15 $ are the first, the second and the third elements of $ L(7,22) $ , respectively.

You have to process $ t $ queries. Each query is denoted by three integers $ x $ , $ p $ and $ k $ , and the answer to this query is $ k $ -th element of $ L(x,p) $ .

## 输入格式

The first line contains one integer $ t $ ( $ 1<=t<=30000 $ ) — the number of queries to process.

Then $ t $ lines follow. $ i $ -th line contains three integers $ x $ , $ p $ and $ k $ for $ i $ -th query ( $ 1<=x,p,k<=10^{6} $ ).

## 输出格式

Print $ t $ integers, where $ i $ -th integer is the answer to $ i $ -th query.

## 样例 #1

### 输入

```
3
7 22 1
7 22 2
7 22 3

```

### 输出

```
9
13
15

```

## 样例 #2

### 输入

```
5
42 42 42
43 43 43
44 44 44
45 45 45
46 46 46

```

### 输出

```
187
87
139
128
141

```



---

---
title: "Machine Learning"
layout: "post"
diff: 省选/NOI-
pid: CF940F
tag: ['莫队', '枚举', '分块']
---

# Machine Learning

## 题目描述

You come home and fell some unpleasant smell. Where is it coming from?

You are given an array $ a $ . You have to answer the following queries:

1. You are given two integers $ l $ and $ r $ . Let $ c_{i} $ be the number of occurrences of $ i $ in $ a_{l:r} $ , where $ a_{l:r} $ is the subarray of $ a $ from $ l $ -th element to $ r $ -th inclusive. Find the Mex of $ {c_{0},c_{1},...,c_{10^{9}}} $
2. You are given two integers $ p $ to $ x $ . Change $ a_{p} $ to $ x $ .

The Mex of a multiset of numbers is the smallest non-negative integer not in the set.

Note that in this problem all elements of $ a $ are positive, which means that $ c_{0} $ = 0 and $ 0 $ is never the answer for the query of the second type.

## 输入格式

The first line of input contains two integers $ n $ and $ q $ ( $ 1<=n,q<=100000 $ ) — the length of the array and the number of queries respectively.

The second line of input contains $ n $ integers — $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

Each of the next $ q $ lines describes a single query.

The first type of query is described by three integers $ t_{i}=1 $ , $ l_{i} $ , $ r_{i} $ , where $ 1<=l_{i}<=r_{i}<=n $ — the bounds of the subarray.

The second type of query is described by three integers $ t_{i}=2 $ , $ p_{i} $ , $ x_{i} $ , where $ 1<=p_{i}<=n $ is the index of the element, which must be changed and $ 1<=x_{i}<=10^{9} $ is the new value.

## 输出格式

For each query of the first type output a single integer — the Mex of $ {c_{0},c_{1},...,c_{10^{9}}} $ .

## 说明/提示

The subarray of the first query consists of the single element — $ 1 $ .

The subarray of the second query consists of four $ 2 $ s, one $ 3 $ and two $ 1 $ s.

The subarray of the fourth query consists of three $ 1 $ s, three $ 2 $ s and one $ 3 $ .

## 样例 #1

### 输入

```
10 4
1 2 3 1 1 2 2 2 9 9
1 1 1
1 2 8
2 7 1
1 2 8

```

### 输出

```
2
3
2

```



---

---
title: "Simple Cycles Edges"
layout: "post"
diff: 省选/NOI-
pid: CF962F
tag: ['搜索', '枚举', '差分']
---

# Simple Cycles Edges

## 题目描述

You are given an undirected graph, consisting of $ n $ vertices and $ m $ edges. The graph does not necessarily connected. Guaranteed, that the graph does not contain multiple edges (more than one edges between a pair of vertices) or loops (edges from a vertex to itself).

A cycle in a graph is called a simple, if it contains each own vertex exactly once. So simple cycle doesn't allow to visit a vertex more than once in a cycle.

Determine the edges, which belong to exactly on one simple cycle.

## 输入格式

The first line contain two integers $ n $ and $ m $ $ (1 \le n \le 100\,000 $ , $ 0 \le m \le \min(n \cdot (n - 1) / 2, 100\,000)) $ — the number of vertices and the number of edges.

Each of the following $ m $ lines contain two integers $ u $ and $ v $ ( $ 1 \le u, v \le n $ , $ u \neq v $ ) — the description of the edges.

## 输出格式

In the first line print the number of edges, which belong to exactly one simple cycle.

In the second line print the indices of edges, which belong to exactly one simple cycle, in increasing order. The edges are numbered from one in the same order as they are given in the input.

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1

```

### 输出

```
3
1 2 3 

```

## 样例 #2

### 输入

```
6 7
2 3
3 4
4 2
1 2
1 5
5 6
6 1

```

### 输出

```
6
1 2 3 5 6 7 

```

## 样例 #3

### 输入

```
5 6
1 2
2 3
2 4
4 3
2 5
5 3

```

### 输出

```
0


```



---

---
title: "Round Marriage"
layout: "post"
diff: 省选/NOI-
pid: CF981F
tag: ['二分', '枚举', '构造']
---

# Round Marriage

## 题目描述

It's marriage season in Ringland!

Ringland has a form of a circle's boundary of length $ L $ . There are $ n $ bridegrooms and $ n $ brides, and bridegrooms decided to marry brides.

Of course, each bridegroom should choose exactly one bride, and each bride should be chosen by exactly one bridegroom.

All objects in Ringland are located on the boundary of the circle, including the capital, bridegrooms' castles and brides' palaces. The castle of the $ i $ -th bridegroom is located at the distance $ a_i $ from the capital in clockwise direction, and the palace of the $ i $ -th bride is located at the distance $ b_i $ from the capital in clockwise direction.

Let's define the inconvenience of a marriage the maximum distance that some bride should walk along the circle from her palace to her bridegroom's castle in the shortest direction (in clockwise or counter-clockwise direction).

Help the bridegrooms of Ringland to choose brides in such a way that the inconvenience of the marriage is the smallest possible.

## 输入格式

The first line contains two integers $ n $ and $ L $ ( $ 1 \leq n \leq 2 \cdot 10^{5} $ , $ 1 \leq L \leq 10^{9} $ ) — the number of bridegrooms and brides and the length of Ringland.

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < L $ ) — the distances from the capital to the castles of bridegrooms in clockwise direction.

The next line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 0 \leq b_i < L $ ) — the distances from the capital to the palaces of brides in clockwise direction.

## 输出格式

In the only line print the smallest possible inconvenience of the wedding, where the inconvenience is the largest distance traveled by a bride.

## 说明/提示

In the first example the first bridegroom should marry the second bride, the second bridegroom should marry the first bride. This way, the second bride should walk the distance of $ 1 $ , and the first bride should also walk the same distance. Thus, the inconvenience is equal to $ 1 $ .

In the second example let $ p_i $ be the bride the $ i $ -th bridegroom will marry. One of optimal $ p $ is the following: $ (6,8,1,4,5,10,3,2,7,9) $ .

## 样例 #1

### 输入

```
2 4
0 1
2 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10 100
3 14 15 92 65 35 89 79 32 38
2 71 82 81 82 84 5 90 45 23

```

### 输出

```
27

```



---

