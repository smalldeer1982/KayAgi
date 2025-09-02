---
title: "The Bits"
layout: "post"
diff: 普及/提高-
pid: CF1017B
tag: ['数学', '概率论', '构造']
---

# The Bits

## 题目描述

手工翻译qwq，可能掺杂个人情感，但保证题目含义不变。

Rudolf正在去城堡的路上。在大门前，保安问了他一个问题：

已知两个长度为$n$的二进制数$a,b$。你可以任意选择$a$中的两个二进制位，然后把上面的数字调换位置。问题是，有多少中不同的操作，可以生成一个与原来不同的$a\;|\;b$？

换句话说，令$c=a\;|\;b$，你能找到多少种操作，使得更改后的$a$满足$a'\;|\;b \ne c$？

其中$|$表示“按位或”运算。如$(01010)_2\;|\;(10011)_2=(11011)_2$

## 输入格式

输入的第一行包含一个整数$n$。其中$2\leqslant n \leqslant 10^5$

后两行分别描述$a, b$。

## 输出格式

输出包含一个整数，表示交换的方案数。

## 样例 #1

### 输入

```
5
01011
11001

```

### 输出

```
4

```

## 样例 #2

### 输入

```
6
011000
010011

```

### 输出

```
6

```



---

---
title: "The Phone Number"
layout: "post"
diff: 普及/提高-
pid: CF1017C
tag: ['模拟', '数学', '构造']
---

# The Phone Number

## 题目描述

Mrs. Smith is trying to contact her husband, John Smith, but she forgot the secret phone number!

The only thing Mrs. Smith remembered was that any permutation of $ n $ can be a secret phone number. Only those permutations that minimize secret value might be the phone of her husband.

The sequence of $ n $ integers is called a permutation if it contains all integers from $ 1 $ to $ n $ exactly once.

The secret value of a phone number is defined as the sum of the length of the longest increasing subsequence (LIS) and length of the longest decreasing subsequence (LDS).

A subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ where $ 1\leq i_1 < i_2 < \ldots < i_k\leq n $ is called increasing if $ a_{i_1} < a_{i_2} < a_{i_3} < \ldots < a_{i_k} $ . If $ a_{i_1} > a_{i_2} > a_{i_3} > \ldots > a_{i_k} $ , a subsequence is called decreasing. An increasing/decreasing subsequence is called longest if it has maximum length among all increasing/decreasing subsequences.

For example, if there is a permutation $ [6, 4, 1, 7, 2, 3, 5] $ , LIS of this permutation will be $ [1, 2, 3, 5] $ , so the length of LIS is equal to $ 4 $ . LDS can be $ [6, 4, 1] $ , $ [6, 4, 2] $ , or $ [6, 4, 3] $ , so the length of LDS is $ 3 $ .

Note, the lengths of LIS and LDS can be different.

So please help Mrs. Smith to find a permutation that gives a minimum sum of lengths of LIS and LDS.

## 输入格式

The only line contains one integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of permutation that you need to build.

## 输出格式

Print a permutation that gives a minimum sum of lengths of LIS and LDS.

If there are multiple answers, print any.

## 说明/提示

In the first sample, you can build a permutation $ [3, 4, 1, 2] $ . LIS is $ [3, 4] $ (or $ [1, 2] $ ), so the length of LIS is equal to $ 2 $ . LDS can be ony of $ [3, 1] $ , $ [4, 2] $ , $ [3, 2] $ , or $ [4, 1] $ . The length of LDS is also equal to $ 2 $ . The sum is equal to $ 4 $ . Note that $ [3, 4, 1, 2] $ is not the only permutation that is valid.

In the second sample, you can build a permutation $ [2, 1] $ . LIS is $ [1] $ (or $ [2] $ ), so the length of LIS is equal to $ 1 $ . LDS is $ [2, 1] $ , so the length of LDS is equal to $ 2 $ . The sum is equal to $ 3 $ . Note that permutation $ [1, 2] $ is also valid.

## 样例 #1

### 输入

```
4

```

### 输出

```
3 4 1 2

```

## 样例 #2

### 输入

```
2

```

### 输出

```
2 1

```



---

---
title: "Cthulhu"
layout: "post"
diff: 普及/提高-
pid: CF103B
tag: ['模拟', '并查集', '构造']
---

# Cthulhu

## 题目描述

...Once upon a time a man came to the sea. The sea was stormy and dark. The man started to call for the little mermaid to appear but alas, he only woke up Cthulhu...

Whereas on the other end of the world Pentagon is actively collecting information trying to predict the monster's behavior and preparing the secret super weapon. Due to high seismic activity and poor weather conditions the satellites haven't yet been able to make clear shots of the monster. The analysis of the first shot resulted in an undirected graph with $ n $ vertices and $ m $ edges. Now the world's best minds are about to determine whether this graph can be regarded as Cthulhu or not.

To add simplicity, let's suppose that Cthulhu looks from the space like some spherical body with tentacles attached to it. Formally, we shall regard as Cthulhu such an undirected graph that can be represented as a set of three or more rooted trees, whose roots are connected by a simple cycle.

It is guaranteed that the graph contains no multiple edges and self-loops.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF103B/33dc55a8762ea9a08fee5a98be66bd3670ec0fbb.png)

## 输入格式

The first line contains two integers — the number of vertices $ n $ and the number of edges $ m $ of the graph ($1 \le n \le 100$, $0 \le m \le \frac{n(n-1)}{2}$).

Each of the following $ m $ lines contains a pair of integers $ x $ and $ y $, that show that an edge exists between vertices $ x $ and $ y $ ($1 \le x, y \le n, x \ne y$). For each pair of vertices there will be at most one edge between them, no edge connects a vertex to itself.

## 输出格式

Print "NO", if the graph is not Cthulhu and "FHTAGN!" if it is.

## 说明/提示

Let us denote as a simple cycle a set of $ v $ vertices that can be numbered so that the edges will only exist between vertices number $ 1 $ and $ 2 $ , $ 2 $ and $ 3 $ , ..., $ v-1 $ and $ v $ , $ v $ and $ 1 $ .

A tree is a connected undirected graph consisting of $ n $ vertices and $ n-1 $ edges ( $ n&gt;0 $ ).

A rooted tree is a tree where one vertex is selected to be the root.

## 样例 #1

### 输入

```
6 6
6 3
6 4
5 1
2 5
1 4
5 4

```

### 输出

```
FHTAGN!
```

## 样例 #2

### 输入

```
6 5
5 6
4 6
3 1
5 1
1 2

```

### 输出

```
NO
```



---

---
title: "Vasya and Isolated Vertices"
layout: "post"
diff: 普及/提高-
pid: CF1065B
tag: ['构造']
---

# Vasya and Isolated Vertices

## 题目描述

Vasya has got an undirected graph consisting of $ n $ vertices and $ m $ edges. This graph doesn't contain any self-loops or multiple edges. Self-loop is an edge connecting a vertex to itself. Multiple edges are a pair of edges such that they connect the same pair of vertices. Since the graph is undirected, the pair of edges $ (1, 2) $ and $ (2, 1) $ is considered to be multiple edges. Isolated vertex of the graph is a vertex such that there is no edge connecting this vertex to any other vertex.

Vasya wants to know the minimum and maximum possible number of isolated vertices in an undirected graph consisting of $ n $ vertices and $ m $ edges.

## 输入格式

The only line contains two integers $ n $ and $ m~(1 \le n \le 10^5, 0 \le m \le \frac{n (n - 1)}{2}) $ .

It is guaranteed that there exists a graph without any self-loops or multiple edges with such number of vertices and edges.

## 输出格式

In the only line print two numbers $ min $ and $ max $ — the minimum and maximum number of isolated vertices, respectively.

## 说明/提示

In the first example it is possible to construct a graph with $ 0 $ isolated vertices: for example, it should contain edges $ (1, 2) $ and $ (3, 4) $ . To get one isolated vertex, we may construct a graph with edges $ (1, 2) $ and $ (1, 3) $ .

In the second example the graph will always contain exactly one isolated vertex.

## 样例 #1

### 输入

```
4 2

```

### 输出

```
0 1

```

## 样例 #2

### 输入

```
3 1

```

### 输出

```
1 1

```



---

---
title: "Prime Permutation"
layout: "post"
diff: 普及/提高-
pid: CF123A
tag: ['字符串', '素数判断,质数,筛法', '构造']
---

# Prime Permutation

## 题目描述

You are given a string $ s $ , consisting of small Latin letters. Let's denote the length of the string as $ |s| $ . The characters in the string are numbered starting from $ 1 $ .

Your task is to find out if it is possible to rearrange characters in string $ s $ so that for any prime number $ p<=|s| $ and for any integer $ i $ ranging from $ 1 $ to $ |s|/p $ (inclusive) the following condition was fulfilled $ s_{p}=s_{p×i} $ . If the answer is positive, find one way to rearrange the characters.

## 输入格式

The only line contains the initial string $ s $ , consisting of small Latin letters ( $ 1<=|s|<=1000 $ ).

## 输出格式

If it is possible to rearrange the characters in the string so that the above-mentioned conditions were fulfilled, then print in the first line "YES" (without the quotes) and print on the second line one of the possible resulting strings. If such permutation is impossible to perform, then print the single string "NO".

## 说明/提示

In the first sample any of the six possible strings will do: "abc", "acb", "bac", "bca", "cab" or "cba".

In the second sample no letter permutation will satisfy the condition at $ p=2 $ ( $ s_{2}=s_{4} $ ).

In the third test any string where character "y" doesn't occupy positions 2, 3, 4, 6 will be valid.

## 样例 #1

### 输入

```
abc

```

### 输出

```
YES
abc

```

## 样例 #2

### 输入

```
abcd

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
xxxyxxx

```

### 输出

```
YES
xxxxxxy

```



---

---
title: "Binary Period"
layout: "post"
diff: 普及/提高-
pid: CF1342B
tag: ['贪心', '构造']
---

# Binary Period

## 题目描述

假设有一个字符串$s$，如果它的第$i$ 个字符和第$i+k$ 个字符相等$(1\le i\le|s|-k)$ ，那么这个字符串的周期为$k$ 。其中，$|s|$ 表示字符串$s$ 的长度。



现在给你一个字符串$t$ ，$t$ 内只包括```0```和```1```，请你找出这个$s$ ，使其满足如下条件：

1. 字符串$s$ 也只包括```0```和```1```。

2. $|s|\le 2\times|t|$（$s$ 的长度不能超过$t$ 的长度的两倍）。

3. $t$ 是$s$ 的子串。

4. 在满足上面3个条件的情况下，$s$ 需要有最小的周期$k$ 。



$t$ 是$s$ 的子串就是说当$s$ 删除$0$个或更多个字符后（不能改变顺序），$s$ 就变成了$t$ 。例如```011```就是```10101```的子串。

## 输入格式

第一行是一个正整数$T$，表示数据的组数。



接下来$T$行，每行有一个只包含```0```和```1```的字符串$t$ $(1\le|t|\le100)$。

## 输出格式

如果有多种解，输出一个符合条件的字符串$s$ 即可。

## 样例 #1

### 输入

```
4
00
01
111
110
```

### 输出

```
00
01
11111
1010
```



---

---
title: "Special Permutation"
layout: "post"
diff: 普及/提高-
pid: CF1352G
tag: ['构造']
---

# Special Permutation

## 题目描述

A permutation of length $ n $ is an array $ p=[p_1,p_2,\dots,p_n] $ , which contains every integer from $ 1 $ to $ n $ (inclusive) and, moreover, each number appears exactly once. For example, $ p=[3,1,4,2,5] $ is a permutation of length $ 5 $ .

For a given number $ n $ ( $ n \ge 2 $ ), find a permutation $ p $ in which absolute difference (that is, the absolute value of difference) of any two neighboring (adjacent) elements is between $ 2 $ and $ 4 $ , inclusive. Formally, find such permutation $ p $ that $ 2 \le |p_i - p_{i+1}| \le 4 $ for each $ i $ ( $ 1 \le i < n $ ).

Print any such permutation for the given integer $ n $ or determine that it does not exist.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le       100 $ ) — the number of test cases in the input. Then $ t $ test cases follow.

Each test case is described by a single line containing an integer $ n $ ( $ 2 \le n \le 1000 $ ).

## 输出格式

Print $ t $ lines. Print a permutation that meets the given requirements. If there are several such permutations, then print any of them. If no such permutation exists, print -1.

## 样例 #1

### 输入

```
6
10
2
4
6
7
13
```

### 输出

```
9 6 10 8 4 7 3 1 5 2 
-1
3 1 4 2 
5 3 6 2 4 1 
5 1 3 6 2 4 7 
13 9 7 11 8 4 1 3 5 2 6 10 12
```



---

---
title: "Prefix Flip (Easy Version)"
layout: "post"
diff: 普及/提高-
pid: CF1381A1
tag: ['构造']
---

# Prefix Flip (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the versions is the constraint on $ n $ and the required number of operations. You can make hacks only if all versions of the problem are solved.

There are two binary strings $ a $ and $ b $ of length $ n $ (a binary string is a string consisting of symbols $ 0 $ and $ 1 $ ). In an operation, you select a prefix of $ a $ , and simultaneously invert the bits in the prefix ( $ 0 $ changes to $ 1 $ and $ 1 $ changes to $ 0 $ ) and reverse the order of the bits in the prefix.

For example, if $ a=001011 $ and you select the prefix of length $ 3 $ , it becomes $ 011011 $ . Then if you select the entire string, it becomes $ 001001 $ .

Your task is to transform the string $ a $ into $ b $ in at most $ 3n $ operations. It can be proved that it is always possible.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le       1000 $ ) — the number of test cases. Next $ 3t $ lines contain descriptions of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le 1000 $ ) — the length of the binary strings.

The next two lines contain two binary strings $ a $ and $ b $ of length $ n $ .

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 1000 $ .

## 输出格式

For each test case, output an integer $ k $ ( $ 0\le k\le       3n $ ), followed by $ k $ integers $ p_1,\ldots,p_k $ ( $ 1\le       p_i\le n $ ). Here $ k $ is the number of operations you use and $ p_i $ is the length of the prefix you flip in the $ i $ -th operation.

## 说明/提示

In the first test case, we have $ 01\to 11\to 00\to 10 $ .

In the second test case, we have $ 01011\to 00101\to 11101\to       01000\to 10100\to 00100\to 11100 $ .

In the third test case, the strings are already the same. Another solution is to flip the prefix of length $ 2 $ , which will leave $ a $ unchanged.

## 样例 #1

### 输入

```
5
2
01
10
5
01011
11100
2
01
01
10
0110011011
1000110100
1
0
1
```

### 输出

```
3 1 2 1
6 5 2 5 3 1 2
0
9 4 1 2 10 4 1 2 1 5
1 1
```



---

---
title: "Lucky Number 2"
layout: "post"
diff: 普及/提高-
pid: CF145B
tag: ['构造']
---

# Lucky Number 2

## 题目描述

Petya loves lucky numbers very much. Everybody knows that lucky numbers are positive integers whose decimal record contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya loves long lucky numbers very much. He is interested in the minimum lucky number $ d $ that meets some condition. Let $ cnt(x) $ be the number of occurrences of number $ x $ in number $ d $ as a substring. For example, if $ d=747747 $ , then $ cnt(4)=2 $ , $ cnt(7)=4 $ , $ cnt(47)=2 $ , $ cnt(74)=2 $ . Petya wants the following condition to fulfil simultaneously: $ cnt(4)=a_{1} $ , $ cnt(7)=a_{2} $ , $ cnt(47)=a_{3} $ , $ cnt(74)=a_{4} $ . Petya is not interested in the occurrences of other numbers. Help him cope with this task.

## 输入格式

The single line contains four integers $ a_{1} $ , $ a_{2} $ , $ a_{3} $ and $ a_{4} $ ( $ 1<=a_{1},a_{2},a_{3},a_{4}<=10^{6} $ ).

## 输出格式

On the single line print without leading zeroes the answer to the problem — the minimum lucky number $ d $ such, that $ cnt(4)=a_{1} $ , $ cnt(7)=a_{2} $ , $ cnt(47)=a_{3} $ , $ cnt(74)=a_{4} $ . If such number does not exist, print the single number "-1" (without the quotes).

## 样例 #1

### 输入

```
2 2 1 1

```

### 输出

```
4774

```

## 样例 #2

### 输入

```
4 7 3 1

```

### 输出

```
-1

```



---

---
title: "Not Assigning"
layout: "post"
diff: 普及/提高-
pid: CF1627C
tag: ['构造']
---

# Not Assigning

## 题目描述

You are given a tree of $ n $ vertices numbered from $ 1 $ to $ n $ , with edges numbered from $ 1 $ to $ n-1 $ . A tree is a connected undirected graph without cycles. You have to assign integer weights to each edge of the tree, such that the resultant graph is a prime tree.

A prime tree is a tree where the weight of every path consisting of one or two edges is prime. A path should not visit any vertex twice. The weight of a path is the sum of edge weights on that path.

Consider the graph below. It is a prime tree as the weight of every path of two or less edges is prime. For example, the following path of two edges: $ 2 \to 1 \to 3 $ has a weight of $ 11 + 2 = 13 $ , which is prime. Similarly, the path of one edge: $ 4 \to 3 $ has a weight of $ 5 $ , which is also prime.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627C/3add991eaafca4c0491e3513c8ebd38f1627bca9.png)Print any valid assignment of weights such that the resultant tree is a prime tree. If there is no such assignment, then print $ -1 $ . It can be proven that if a valid assignment exists, one exists with weights between $ 1 $ and $ 10^5 $ as well.

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 2 \leq n \leq 10^5 $ ) — the number of vertices in the tree.

Then, $ n-1 $ lines follow. The $ i $ -th line contains two integers $ u $ and $ v $ ( $ 1 \leq u, v \leq n $ ) denoting that edge number $ i $ is between vertices $ u $ and $ v $ . It is guaranteed that the edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, if a valid assignment exists, then print a single line containing $ n-1 $ integers $ a_1, a_2, \dots, a_{n-1} $ ( $ 1 \leq a_i \le 10^5 $ ), where $ a_i $ denotes the weight assigned to the edge numbered $ i $ . Otherwise, print $ -1 $ .

If there are multiple solutions, you may print any.

## 说明/提示

For the first test case, there are only two paths having one edge each: $ 1 \to 2 $ and $ 2 \to 1 $ , both having a weight of $ 17 $ , which is prime.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627C/22666e3c2f70cbd5edc23fd608081fffda0715fc.png)The second test case is described in the statement.

It can be proven that no such assignment exists for the third test case.

## 样例 #1

### 输入

```
3
2
1 2
4
1 3
4 3
2 1
7
1 2
1 3
3 4
3 5
6 2
7 2
```

### 输出

```
17
2 5 11
-1
```



---

---
title: "Circular Local MiniMax"
layout: "post"
diff: 普及/提高-
pid: CF1685A
tag: ['构造']
---

# Circular Local MiniMax

## 题目描述

给你 $n$ 个整数 $ a_1, a_2, \ldots, a_n $ 。 问有没有可能将它们排列在一个圆上，使每个数字严格地大于其相邻的两个数字或严格地小于其相邻的两个数字？

换句话说，检查是否存在 $ b_1, b_2, \ldots, b_n $ 的整数 $ a_1, a_2, \ldots, a_n $ 的重新排列，使得 $ i $ 从 $ 1 $ 到 $ n $ 中至少有一个以下条件成立。

- $ b_{i-1} < b_i > b_{i+1} $
- $ b_{i-1} > b_i < b_{i+1} $

为了使前面的公式对 $ i=1 $ 和 $ i=n $ 有意义，我们应定义 $ b_0=b_n $ 和 $ b_{n+1}=b_1 $。

## 输入格式

输入的第一行包含一个整数 $ t $ ( $ 1 \le t \le 3\cdot 10^4 $ ) ，表示数据组数。

接下来 $T$ 行，第一行包含一个的整数 $ n $ ( $ 3 \le n \le 10^5 $ ) ，

第二行包含 $ n $ 整数 $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) 。（$\sum n \le 2 \cdot 10^5$）

## 输出格式

对于每组数据，如果不可能将数字排列在满足语句条件的圆圈上，则输出 $ \texttt{NO} $ 。

否则，输出 $ \texttt{YES} $ 。在第二行，输出 $ b_1, b_2, \ldots, b_n $ ，这是 $ a_1, a_2, \ldots, a_n $ 的重新排列，并且满足声明中的条件。如果有多种有效的数字排列方式，你可以输出其中任何一种。

## 样例解释
可以证明，对于第一个和第三个测试案例，没有有效的安排。

在第二个测试案例中，安排 $ [1, 8, 4, 9] $ 是有效的。在这个排列中，$1$ 和 $4$ 都比它们相邻的数小，而 $8、9$ 则较大。

在第四个测试案例中，排列方式 $[1，11，1，111，1，1111]$ 有效。在这个排列中，等于$1$的三个元素比它们相邻的数小，而所有其他元素都比它们相邻的数大。

## 样例 #1

### 输入

```
4
3
1 1 2
4
1 9 8 4
4
2 0 2 2
6
1 1 1 11 111 1111
```

### 输出

```
NO
YES
1 8 4 9 
NO
YES
1 11 1 111 1 1111
```



---

---
title: "Fishingprince Plays With Array"
layout: "post"
diff: 普及/提高-
pid: CF1696C
tag: ['模拟', '数学', '贪心', '构造']
---

# Fishingprince Plays With Array

## 题目描述

Fishingprince is playing with an array $ [a_1,a_2,\dots,a_n] $ . He also has a magic number $ m $ .

He can do the following two operations on it:

- Select $ 1\le i\le n $ such that $ a_i $ is divisible by $ m $ (that is, there exists an integer $ t $ such that $ m \cdot t = a_i $ ). Replace $ a_i $ with  $ m $ copies of $ \frac{a_i}{m} $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[2,3] $ and $ i=1 $ , $ a $ changes into $ [1,1,3] $ .
- Select $ 1\le i\le n-m+1 $ such that $ a_i=a_{i+1}=\dots=a_{i+m-1} $ . Replace these $ m $ elements with a single $ m \cdot a_i $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[3,2,2,3] $ and $ i=2 $ , $ a $ changes into $ [3,4,3] $ .

Note that the array length might change during the process. The value of $ n $ above is defined as the current length of the array (might differ from the $ n $ in the input).

Fishingprince has another array $ [b_1,b_2,\dots,b_k] $ . Please determine if he can turn $ a $ into $ b $ using any number (possibly zero) of operations.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1\le n\le 5\cdot 10^4 $ , $ 2\le m\le 10^9 $ ).

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1\le a_i\le 10^9 $ ).

The third line of each test case contains one integer $ k $ ( $ 1\le k\le 5\cdot 10^4 $ ).

The fourth line of each test case contains $ k $ integers $ b_1,b_2,\ldots,b_k $ ( $ 1\le b_i\le 10^9 $ ).

It is guaranteed that the sum of $ n+k $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each testcase, print Yes if it is possible to turn $ a $ into $ b $ , and No otherwise. You can print each letter in any case (upper or lower).

## 说明/提示

In the first test case of the sample, we can do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},4,2]\to [1,\color{red}{4},4,2] $ .

In the second testcase of the sample, we can:

- do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},8,2,2]\to [1,\color{red}{4},8,2,2] $ .
- do the second operation with $ i=4 $ : $ [1,4,8,\color{red}{2,2}]\to [1,4,8,\color{red}{4}] $ .
- do the first operation with $ i=3 $ : $ [1,4,\color{red}{8},4]\to [1,4,\color{red}{4,4},4] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{4,4},4,4]\to [1,\color{red}{8},4,4] $ .
- do the second operation with $ i=3 $ : $ [1,8,\color{red}{4,4}]\to [1,8,\color{red}{8}] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{8,8}]\to [1,\color{red}{16}] $ .

## 样例 #1

### 输入

```
5
5 2
1 2 2 4 2
4
1 4 4 2
6 2
1 2 2 8 2 2
2
1 16
8 3
3 3 3 3 3 3 3 3
4
6 6 6 6
8 3
3 9 6 3 12 12 36 12
16
9 3 2 2 2 3 4 12 4 12 4 12 4 12 4 4
8 3
3 9 6 3 12 12 36 12
7
12 2 4 3 4 12 56
```

### 输出

```
Yes
Yes
No
Yes
No
```



---

---
title: "Difference of GCDs"
layout: "post"
diff: 普及/提高-
pid: CF1708B
tag: ['数论', '构造']
---

# Difference of GCDs

## 题目描述

You are given three integers $ n $ , $ l $ , and $ r $ . You need to construct an array $ a_1,a_2,\dots,a_n $ ( $ l\le a_i\le r $ ) such that $ \gcd(i,a_i) $ are all distinct or report there's no solution.

Here $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line contains three integers $ n $ , $ l $ , $ r $ ( $ 1 \le n \le 10^5 $ , $ 1\le l\le r\le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, if there is no solution, print "NO" (without quotes). You can print letters in any case (upper or lower).

Otherwise, print "YES" (without quotes). In the next line, print $ n $ integers $ a_1,a_2,\ldots,a_n $ — the array you construct.

If there are multiple solutions, you may output any.

## 说明/提示

In the first test case, $ \gcd(1,a_1),\gcd(2,a_2),\ldots,\gcd(5,a_5) $ are equal to $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , respectively.

## 样例 #1

### 输入

```
4
5 1 5
9 1000 2000
10 30 35
1 1000000000 1000000000
```

### 输出

```
YES
1 2 3 4 5
YES
1145 1926 1440 1220 1230 1350 1001 1000 1233
NO
YES
1000000000
```



---

---
title: "Even-Odd XOR"
layout: "post"
diff: 普及/提高-
pid: CF1722G
tag: ['位运算', '构造']
---

# Even-Odd XOR

## 题目描述

给定一个正整数 $n$，请你找出一个长度为 $n$ 数组 $a$，满足数组是由互不相同的非负且小于 $2^{31}$ 的整数组成，并且该数组中奇数项上元素的[异或和](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)与偶数项上元素的异或和要相等。

## 输入格式

输入的第一行为一个整数 $t$ $(1 \leq t \leq 629)$，表示测试点的数量。

接下来 $t$ 行，每行一个整数 $n$ $(3 \leq n \leq 2 \times 10^5)$，表示数组的长度。

保证所有测试点中 $n$ 的总和不超过 $2 \times 10^5$。

## 输出格式

对于每个测试点，在一行中输出 $n$ 个不同的满足条件的整数。

如果有多种答案，你可以输出任意一种。

### 样例解释

在第一个测试点中，奇数项的异或和为 $4 \oplus 1 \oplus 0 \oplus 7 = 2$；偶数项的异或和为 $2 \oplus 5 \oplus 6 \oplus 3 = 2$。

## 样例 #1

### 输入

```
7
8
3
4
5
6
7
9
```

### 输出

```
4 2 1 5 0 6 7 3
2 1 3
2 1 3 0
2 0 4 5 3
4 1 2 12 3 8
1 2 3 4 5 6 7
8 2 3 7 4 0 5 6 9
```



---

---
title: "Gardener and the Array"
layout: "post"
diff: 普及/提高-
pid: CF1775B
tag: ['位运算', '构造']
---

# Gardener and the Array

## 题目描述

The gardener Kazimir Kazimirovich has an array of $ n $ integers $ c_1, c_2, \dots, c_n $ .

He wants to check if there are two different subsequences $ a $ and $ b $ of the original array, for which $ f(a) = f(b) $ , where $ f(x) $ is the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of all of the numbers in the sequence $ x $ .

A sequence $ q $ is a subsequence of $ p $ if $ q $ can be obtained from $ p $ by deleting several (possibly none or all) elements.

Two subsequences are considered different if the sets of indexes of their elements in the original sequence are different, that is, the values of the elements are not considered when comparing the subsequences.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775B/01e7b88f6704ebb4d7f093f81e886f156c238509.png)

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the size of the array $ c $ .

The description of the array $ c $ in this problem is given implicitly to speed up input.

The $ (i + 1) $ -st of the following $ n $ lines of the test case begins with an integer $ k_i $ ( $ 1 \le k_i \le 10^5 $ ) — the number of set bits in the number $ c_i $ . Next follow $ k_i $ distinct integers $ p_{i, 1}, p_{i, 2}, \dots, p_{i, k_i} $ ( $ 1 \le p_i \le 2 \cdot 10^5 $ ) —the numbers of bits that are set to one in number $ c_i $ . In other words, $ c_i = 2^{p_{i, 1}} + 2^{p_{i, 2}} + \ldots + 2^{p_{i, k_i}} $ .

It is guaranteed that the total sum of $ k_i $ in all tests does not exceed $ 10^5 $ .

## 输出格式

For each set of input, print "Yes" if there exist two different subsequences for which $ f(a) = f(b) $ , and "No" otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

It can be proven that in the first test case there are no two different subsequences $ a $ and $ b $ for which $ f(a) = f(b) $ .

In the second test case, one of the possible answers are following subsequences: the subsequence $ a $ formed by the element at position $ 1 $ , and the subsequence $ b $ formed by the elements at positions $ 1 $ and $ 2 $ .

In the third test case, one of the possible answers are following subsequences: the subsequence $ a $ formed by elements at positions $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , and the subsequence $ b $ formed by elements at positions $ 2 $ , $ 3 $ and $ 4 $ .

## 样例 #1

### 输入

```
5
3
2 1 5
2 2 4
2 2 3
2
2 1 2
1 2
4
3 1 2 4
2 2 4
4 1 2 5 6
2 2 5
5
3 3 1 2
3 2 5 3
5 7 2 3 1 4
5 1 2 6 3 5
3 2 6 3
2
1 1
1 2
```

### 输出

```
No
Yes
Yes
Yes
No
```



---

---
title: "Find B"
layout: "post"
diff: 普及/提高-
pid: CF1923C
tag: ['前缀和', '构造']
---

# Find B

## 题目描述

An array $ a $ of length $ m $ is considered good if there exists an integer array $ b $ of length $ m $ such that the following conditions hold:

1. $ \sum\limits_{i=1}^{m} a_i = \sum\limits_{i=1}^{m} b_i $ ;
2. $ a_i \neq b_i $ for every index $ i $ from $ 1 $ to $ m $ ;
3. $ b_i > 0 $ for every index $ i $ from $ 1 $ to $ m $ .

You are given an array $ c $ of length $ n $ . Each element of this array is greater than $ 0 $ .

You have to answer $ q $ queries. During the $ i $ -th query, you have to determine whether the subarray $ c_{l_{i}}, c_{l_{i}+1}, \dots, c_{r_{i}} $ is good.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 3 \cdot 10^5 $ ) — the length of the array $ c $ and the number of queries.

The second line of each test case contains $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le 10^9 $ ).

Then $ q $ lines follow. The $ i $ -th of them contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) — the borders of the $ i $ -th subarray.

Additional constraints on the input: the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ ; the sum of $ q $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each query, print YES if the subarray is good. Otherwise, print NO.

You can output each letter of the answer in any case (upper or lower). For example, the strings yEs, yes, Yes, and YES will all be recognized as positive responses.

## 样例 #1

### 输入

```
1
5 4
1 2 1 4 5
1 5
4 4
3 4
1 3
```

### 输出

```
YES
NO
YES
NO
```



---

---
title: "Klever Permutation"
layout: "post"
diff: 普及/提高-
pid: CF1927E
tag: ['构造']
---

# Klever Permutation

## 题目描述

You are given two integers $ n $ and $ k $ ( $ k \le n $ ), where $ k $ is even.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation (as $ 2 $ appears twice in the array) and $ [0,1,2] $ is also not a permutation (as $ n=3 $ , but $ 3 $ is not present in the array).

Your task is to construct a  $ k $ -level permutation of length $ n $ .

A permutation is called  $ k $ -level if, among all the sums of continuous segments of length $ k $ (of which there are exactly $ n - k + 1 $ ), any two sums differ by no more than $ 1 $ .

More formally, to determine if the permutation $ p $ is  $ k $ -level, first construct an array $ s $ of length $ n - k + 1 $ , where $ s_i=\sum_{j=i}^{i+k-1} p_j $ , i.e., the $ i $ -th element is equal to the sum of $ p_i, p_{i+1}, \dots, p_{i+k-1} $ .

A permutation is called  $ k $ -level if $ \max(s) - \min(s) \le 1 $ .

Find any  $ k $ -level permutation of length $ n $ .

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. This is followed by the description of the test cases.

The first and only line of each test case contains two integers $ n $ and $ k $ ( $ 2 \le k \le n \le 2 \cdot 10^5 $ , $ k $ is even), where $ n $ is the length of the desired permutation.

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output any  $ k $ -level permutation of length $ n $ .

It is guaranteed that such a permutation always exists given the constraints.

## 说明/提示

In the second test case of the example:

- $ p_1 + p_2 = 3 + 1 = 4 $ ;
- $ p_2 + p_3 = 1 + 2 = 3 $ .

 The maximum among the sums is $ 4 $ , and the minimum is $ 3 $ .

## 样例 #1

### 输入

```
5
2 2
3 2
10 4
13 4
7 4
```

### 输出

```
2 1
1 3 2
1 8 4 10 2 7 5 9 3 6
4 10 1 13 5 9 2 12 6 8 3 11 7
1 6 3 7 2 5 4
```



---

---
title: "Equal XOR"
layout: "post"
diff: 普及/提高-
pid: CF1944B
tag: ['位运算', '构造']
---

# Equal XOR

## 题目描述

You are given an array $ a $ of length $ 2n $ , consisting of each integer from $ 1 $ to $ n $ exactly twice.

You are also given an integer $ k $ ( $ 1 \leq k \leq \lfloor \frac{n}{2} \rfloor  $ ).

You need to find two arrays $ l $ and $ r $ each of length $ \mathbf{2k} $ such that:

- $ l $ is a subset $ ^\dagger $ of $ [a_1, a_2, \ldots a_n] $
- $ r $ is a subset of $ [a_{n+1}, a_{n+2}, \ldots a_{2n}] $
- [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of elements of $ l $ is equal to the bitwise XOR of elements of $ r $ ; in other words, $ l_1 \oplus l_2 \oplus \ldots \oplus l_{2k} = r_1 \oplus r_2 \oplus \ldots \oplus r_{2k} $

It can be proved that at least one pair of $ l $ and $ r $ always exists. If there are multiple solutions, you may output any one of them.

 $ ^\dagger $ A sequence $ x $ is a subset of a sequence $ y $ if $ x $ can be obtained by deleting several (possibly none or all) elements of $ y $ and rearranging the elements in any order. For example, $ [3,1,2,1] $ , $ [1, 2, 3] $ , $ [1, 1] $ and $ [3, 2] $ are subsets of $ [1, 1, 2, 3] $ but $ [4] $ and $ [2, 2] $ are not subsets of $ [1, 1, 2, 3] $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 5000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains $ 2 $ integers $ n $ and $ k $ ( $ 2 \le n \le 5 \cdot 10^4 $ , $ 1 \leq k \leq \lfloor \frac{n}{2} \rfloor  $ ).

The second line contains $ 2n $ integers $ a_1, a_2, \ldots, a_{2n} $ ( $ 1 \le a_i \le n $ ). It is guaranteed that every integer from $ 1 $ to $ n $ occurs exactly twice in $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^4 $ .

## 输出格式

For each test case, output two lines.

On the first line of output, output $ 2k $ integers $ l_1, l_2, \ldots, l_{2k} $ .

On the second line of output, output $ 2k $ integers $ r_1, r_2, \ldots r_{2k} $ .

If there are multiple solutions, you may output any one of them.

## 说明/提示

In the first test case, we choose $ l=[2,1] $ and $ r=[2,1] $ . $ [2, 1] $ is a subset of $ [a_1, a_2] $ and $ [2, 1] $ is a subset of $ [a_3, a_4] $ , and $ 2 \oplus 1 = 2 \oplus 1 = 3 $ .

In the second test case, $ 6 \oplus 4 = 1 \oplus 3 = 2 $ .

## 样例 #1

### 输入

```
4
2 1
1 2 2 1
6 1
6 4 2 1 2 3 1 6 3 5 5 4
4 1
1 2 3 4 1 2 3 4
6 2
5 1 3 3 5 1 2 6 4 6 4 2
```

### 输出

```
2 1
2 1
6 4
1 3
1 2
1 2
5 1 3 3
6 4 2 4
```



---

---
title: "Cells Arrangement"
layout: "post"
diff: 普及/提高-
pid: CF1968E
tag: ['数学', '构造']
---

# Cells Arrangement

## 题目描述

You are given an integer $ n $ . You choose $ n $ cells $ (x_1,y_1), (x_2,y_2),\dots,(x_n,y_n) $ in the grid $ n\times n $ where $ 1\le x_i\le n $ and $ 1\le y_i\le n $ .

Let $ \mathcal{H} $ be the set of distinct Manhattan distances between any pair of cells. Your task is to maximize the size of $ \mathcal{H} $ . Examples of sets and their construction are given in the notes.

If there exists more than one solution, you are allowed to output any.

Manhattan distance between cells $ (x_1,y_1) $ and $ (x_2,y_2) $ equals $ |x_1-x_2|+|y_1-y_2| $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 50 $ ) — the number of test cases.

Each of the following $ t $ lines contains a single integer $ n $ ( $ 2\le n\le 10^3 $ ).

## 输出格式

For each test case, output $ n $ points which maximize the size of $ \mathcal{H} $ . It is not necessary to output an empty line at the end of the answer for each test case.

## 说明/提示

In the first testcase we have $ n=2 $ . One of the possible arrangements is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/75dc943a7c64415a7537c95e5a0a8ab6f7bb8c40.png) The arrangement with cells located in $ (1,1) $ and $ (1,2) $ .  In this case $ \mathcal{H}=\{|1-1|+|1-1|,|1-1|+|2-2|,|1-1|+|1-2|\}=\{0,0,1\}=\{0,1\} $ . Hence, the size of $ \mathcal{H} $ is $ 2 $ . It can be shown that it is the greatest possible answer.In the second testcase we have $ n=3 $ . The optimal arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c33264fb4d38aae733c98659eb0f28334deed2c9.png) The arrangement with cells located in $ (2,1) $ , $ (2,3) $ and $ (3,1) $ . $ \mathcal{H} $ = $ \{|2-2|+|1-1|,|2-2|+|3-3|,|3-3|+|1-1|,|2-2|+|1-3|,|2-3|+|1-1|,|2-3|+|3-1|\} $ = $ \{0,0,0,2,1,3\} $ = $ \{0,1,2,3\} $ .

For $ n=4 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c8c88e231569a366e81dbe59dfe40f3bca88662e.png)For $ n=5 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/3a3f9b43e6fc8c9643d27a1bfc597d0efe1c8425.png)For $ n=6 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/b0bf5b17a4bc6da02c3ed5a2113cf7373a9e3ccc.png)

## 样例 #1

### 输入

```
5
2
3
4
5
6
```

### 输出

```
1 1
1 2

2 1
2 3
3 1

1 1
1 3
4 3
4 4

1 1
1 3
1 4
2 1
5 5

1 4
1 5
1 6
5 2
5 5
6 1
```



---

---
title: "Cat, Fox and Double Maximum"
layout: "post"
diff: 普及/提高-
pid: CF1973C
tag: ['构造']
---

# Cat, Fox and Double Maximum

## 题目描述

Fox loves permutations! She came up with the following problem and asked Cat to solve it:

You are given an even positive integer $ n $ and a permutation $ ^\dagger $ $ p $ of length $ n $ .

The score of another permutation $ q $ of length $ n $ is the number of local maximums in the array $ a $ of length $ n $ , where $ a_i = p_i + q_i $ for all $ i $ ( $ 1 \le i \le n $ ). In other words, the score of $ q $ is the number of $ i $ such that $ 1 < i < n $ (note the strict inequalities), $ a_{i-1} < a_i $ , and $ a_i > a_{i+1} $ (once again, note the strict inequalities).

Find the permutation $ q $ that achieves the maximum score for given $ n $ and $ p $ . If there exist multiple such permutations, you can pick any of them.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

The first line of input contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases in the input you will have to solve.

The first line of each test case contains one even integer $ n $ ( $ 4 \leq n \leq 10^5 $ , $ n $ is even) — the length of the permutation $ p $ .

The second line of each test case contains the $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \leq p_i \leq n $ ). It is guaranteed that $ p $ is a permutation of length $ n $ .

It is guaranteed that the sum of $ n $ across all test cases doesn't exceed $ 10^5 $ .

## 输出格式

For each test case, output one line containing any permutation of length $ n $ (the array $ q $ ), such that $ q $ maximizes the score under the given constraints.

## 说明/提示

In the first example, $ a = [3, 6, 4, 7] $ . The array has just one local maximum (on the second position), so the score of the chosen permutation $ q $ is $ 1 $ . It can be proven that this score is optimal under the constraints.

In the last example, the resulting array $ a = [6, 6, 12, 7, 14, 7, 14, 6] $ has $ 3 $ local maximums — on the third, fifth and seventh positions.

## 样例 #1

### 输入

```
4
4
1 2 3 4
4
4 3 1 2
6
6 5 1 4 2 3
8
1 2 4 5 7 6 8 3
```

### 输出

```
2 4 1 3
3 1 4 2
2 5 1 4 3 6
5 4 8 2 7 1 6 3
```



---

---
title: "Manhattan Permutations"
layout: "post"
diff: 普及/提高-
pid: CF1978C
tag: ['构造']
---

# Manhattan Permutations

## 题目描述

设排列 $p$ 的曼哈顿值为 $ |p_1 - 1| + |p_2 - 2| + \ldots + |p_n - n| $ 。

例如，对于排列 $ [1, 2, 3] $ , 它的曼哈顿值为 $ |1 - 1| + |2 - 2| + |3 - 3| = 0 $ ；
对于排列 $ [3, 1, 2] $ , 它的曼哈顿值为 $ |3 - 1| + |1 - 2| + |2 - 3| = 2 + 1 + 1 = 4 $ 。

给出 $ n $ 和 $ k $ . 询问是否存在一个长度为 $ n $ 的排列 $ p $ 的曼哈顿值为 $ k $ ，若存在，输出排列 $ p $ 。

## 输入格式

每个测试点包含多组数据。  
第一行包括一个整数 $ t $ ( $ 1 \leq t \leq 10^{4} $ )，表示测试数据的组数。  
接下来 $ t $ 行，每行包括两个整数 $ n $ 和 $ k $ ( $ 1 \le n \le 2 \cdot 10^{5}, 0 \le k \le 10^{12} $ ) ，分别表示你需要找到的排列的长度与曼哈顿值。

保证所有数据中的 $ n $ 的和不会超过 $ 2 \cdot 10^{5} $ 。

## 输出格式

对于每组数据，如果不存在合法的排列，输出"No"；否则先输出一行"Yes"，然后在第二行输出 $ n $ 个不同的整数 $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ) 表示一个合法的排列。

如果存在多个合法的排列，你可以输出任意一个。

"Yes"和"No"大小写不敏感（例如，"yEs", "yes", "Yes", "YES" 都会被视为正确的答案）。

## 样例 #1

### 输入

```
8
3 4
4 5
7 0
1 1000000000000
8 14
112 777
5 12
5 2
```

### 输出

```
Yes
3 1 2
No
Yes
1 2 3 4 5 6 7
No
Yes
8 2 3 4 5 6 1 7
No
Yes
5 4 3 1 2
Yes
2 1 3 4 5
```



---

---
title: "Minimize Equal Sum Subarrays"
layout: "post"
diff: 普及/提高-
pid: CF1998B
tag: ['贪心', '构造']
---

# Minimize Equal Sum Subarrays

## 题目描述

# 最小化相等和子数组


已知 [农夫约翰喜欢排列](https://usaco.org/index.php?page=viewproblem2&cpid=1421)，我也喜欢它们！

给定一个长度为 $ n $ 的排列 $ p $。

找到一个长度为 $ n $ 的排列 $ q $，使得以下条件下的对数最小化：对所有 $ 1 \leq i \leq j \leq n $，使得 $ p_i + p_{i+1} + \ldots + p_j = q_i + q_{i+1} + \ldots + q_j $。

**注**：一个长度为 $ n $ 的排列是一个包含 $ 1 $ 到 $ n $ 的 $ n $ 个不同整数的数组。例如，\[2, 3, 1, 5, 4\] 是一个排列，但 \[1, 2, 2\] 不是一个排列（数字 2 在数组中出现了两次），而 \[1, 3, 4\] 也不是一个排列（$ n=3 $，但数组中有 4）。

## 输入格式

第一行包含一个整数 $ t $ ($ 1 \leq t \leq 10^4 $) — 测试用例的数量。

每个测试用例的第一行包含一个整数 $ n $ ($ 1 \leq n \leq 2 \cdot 10^5 $)。

接下来一行包含 $ n $ 个空格分隔的整数 $ p_1, p_2, \ldots, p_n $ ($ 1 \leq p_i \leq n $) — 表示长度为 $ n $ 的排列 $ p $。

保证所有测试用例中 $ n $ 的总和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对于每个测试用例，输出一行包含任意长度为 $ n $ 的排列 $ q $，使得 $ q $ 最小化满足条件的对数。

## 说明/提示

对于第一个测试用例，存在唯一一对 $ (i, j) $ ($ 1 \leq i \leq j \leq n $) 使得 $ p_i + p_{i+1} + \ldots + p_j = q_i + q_{i+1} + \ldots + q_j $，即 $ (1, 2) $。可以证明，没有这样的 $ q $ 使得不存在满足条件的对。

## 样例 #1

### 输入

```
3
2
1 2
5
1 2 3 4 5
7
4 7 5 1 2 6 3
```

### 输出

```
2 1
3 5 4 2 1
6 2 1 4 7 3 5
```



---

---
title: "Penchick and BBQ Buns"
layout: "post"
diff: 普及/提高-
pid: CF2031C
tag: ['数学', '构造']
---

# Penchick and BBQ Buns

## 题目描述

有 $n$ 个空位，你要用一些正整数来填充这些空位。

你用来填充空位的正整数 $k$ 必须满足以下两个条件：

-	$k$ 至少出现两次。

填完空位之后，设第 $i$ 个空位上的数是 $a_i$。对于任意的 $i\le n$ 和 $j\le n$，如果 $i\ne j$ 且 $a_i=a_j$，那么 $|i-j|$ 是完全平方数。

你需要构造出一组合法的方案，或者报告无解。

## 输入格式

第一行输入一个整数 $t(1\le t\le 2\times 10^5)$，表示数据组数。

对于每一组数据，输入一行一个整数，表示 $n(1\le n\le 2\times 10^5)$。

保证 $\sum n\le 2\times 10^5$。

## 输出格式

对于每组测试数据，如果无解，输出一行一个整数 $-1$。

如果有解，输出一行 $n$ 个数，第 $i$ 个数表示 $a_i$。

### 样例解释

对于 $n=3$，可以证明无法找到合法解，因为不能构造出使用超过两种数且每种数出现次数大于等于 $2$ 的方案，而 $\{1,1,1\}$ 显然不是合法解，因为 $a_1=a_3$ 而 $3-1$ 不是完全平方数。

对于 $n=12$，显然样例输出是合法解：

$a_1=a_{10},10-1=9=3^2$

$a_2=a_{6},6-2=4=2^2$

$a_3=a_{12},12-3=9=3^2$

$a_4=a_{8},8-4=4=2^2$

$a_5=a_{9},9-5=4=2^2$

$a_7=a_{11},11-7=4=2^2$

## 样例 #1

### 输入

```
2
3
12
```

### 输出

```
-1
1 2 3 6 10 2 7 6 10 1 7 3
```



---

---
title: "Alya and Permutation"
layout: "post"
diff: 普及/提高-
pid: CF2035C
tag: ['数学', '构造']
---

# Alya and Permutation

## 题目描述

Alya has been given a hard problem. Unfortunately, she is too busy running for student council. Please solve this problem for her.

Given an integer $ n $ , construct a permutation $ p $ of integers $ 1, 2, \ldots, n $ that maximizes the value of $ k $ (which is initially $ 0 $ ) after the following process.

Perform $ n $ operations, on the $ i $ -th operation ( $ i=1, 2, \dots, n $ ),

- If $ i $ is odd, $ k=k\,\&\,p_i $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).
- If $ i $ is even, $ k=k\,|\,p_i $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 500 $ ) — the number of test cases.

The only line of each test case contains a single integer $ n $ ( $ 5\le n\le 2 \cdot 10^5 $ ) — the length of the permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum value of $ k $ in the first line and output the permutation $ p_1, p_2,\ldots, p_n $ in the second line.

If there are multiple such permutations, output any.

## 说明/提示

For the first test case, the value of $ k $ is determined as follows:

 $ k = 0 $ initially.

- On the $ 1 $ st operation, $ 1 $ is odd, so Alya sets $ k $ to be $ k\&p_1 = 0\&2 = 0 $ .
- On the $ 2 $ nd operation, $ 2 $ is even, so Alya sets $ k $ to be $ k|p_2 = 0|1 = 1 $ .
- On the $ 3 $ rd operation, $ 3 $ is odd, so Alya sets $ k $ to be $ k\&p_3 = 1\&3 = 1 $ .
- On the $ 4 $ th operation, $ 4 $ is even, so Alya sets $ k $ to be $ k|p_4 = 1|4 = 5 $ .
- On the $ 5 $ th operation, $ 5 $ is odd, so Alya sets $ k $ to be $ k\&p_5 = 5\&5 = 5 $ .

The final value of $ k $ is $ 5 $ . It can be shown that the final value of $ k $ is at most $ 5 $ for all permutations of length $ 5 $ . Another valid output is $ [2, 3, 1, 4, 5] $ .

For the second test case, the final value of $ k $ is $ 7 $ . It can be shown that the final value of $ k $ is at most $ 7 $ for all permutations of length $ 6 $ . Other valid outputs include $ [2, 4, 1, 6, 3, 5] $ and $ [5, 2, 6, 1, 3, 4] $ .

## 样例 #1

### 输入

```
6
5
6
7
8
9
10
```

### 输出

```
5
2 1 3 4 5 
7
1 2 4 6 5 3 
7
2 4 5 1 3 6 7 
15
2 4 5 1 3 6 7 8 
9
2 4 5 6 7 1 3 8 9 
15
1 2 3 4 5 6 8 10 9 7
```



---

---
title: "Harder Problem"
layout: "post"
diff: 普及/提高-
pid: CF2044D
tag: ['构造']
---

# Harder Problem

## 题目描述

给定一个正整数序列，若一个正整数在该序列中出现最多次，则称其为该序列的众数（ mode ）。例如，序列 $[2,2,3]$ 的众数为 $2$ 。 $9$ ， $8$ 或 $7$ 的任意一个都可以被认为是序列 $[9,9,8,8,7,7]$ 的众数。

你给了 UFO 一个长度为 $n$ 的数组 $a$ 。为了感谢你， UFO 决定构造一个长度也为 $n$ 的数组 $b$ ，使得对于所有 $1 \leq i \leq n$ ，$a_i$ 是序列 $[b_1, b_2, …, b_i]$ 的众数。

然而， UFO 不知道怎么构造数组 b ，因此你需要帮助她。注意：构造的数组 b 中的元素 $b_i$ 需满足 $1 \leq b_i \leq n$ 。

## 输入格式

第一行包含一个正整数 $t (1 \leq t \leq 10^4)$，代表测试样例数量。

每组测试样例包括两行：

第一行包含一个整数 $n (1 \leq n \leq 2 \cdot 10^5)$ ，代表 $a$ 的长度。

第二行包含 n 个整数 $a_1, a_2, \ldots, a_n (1 \leq a_i \leq n)$ 。

保证所有测试用例的 $n$ 总和不超过 $2 \cdot 10^5$ 。

## 输出格式

对于每组测试样例，在新的一行 n 个数字 $b_1, b_2, \ldots, b_n (1 \leq b_i \leq n )$ 。可以证明数组 $b$ 总是可以构造出来。如果有多个解，输出任意一个。

## 说明/提示

对第 2 组测试样例正确性的证明：

- 当 $i = 1$ 时， $1$ 是 $[1]$ 唯一的众数；
- 当 $i = 2$ 时， $1$ 是 $[1, 1]$ 唯一的众数；
- 当 $i = 3$ 时， $1$ 是 $[1, 1, 2]$ 唯一的众数；
- 当 $i = 4$ 时， $1$ 或 $2$ 均为 $[1, 1, 2, 2]$ 的众数。由于 $a_i = 2$ ，因此这个数组是有效的。

## 样例 #1

### 输入

```
4
2
1 2
4
1 1 1 2
8
4 5 5 5 1 1 2 1
10
1 1 2 2 1 1 3 3 1 1
```

### 输出

```
1 2
1 1 2 2
4 5 5 1 1 2 2 3
1 8 2 2 1 3 3 9 1 1
```



---

---
title: "MEX Cycle"
layout: "post"
diff: 普及/提高-
pid: CF2049C
tag: ['构造', '分类讨论']
---

# MEX Cycle

## 题目描述

Evirir 这只龙有很多朋友。它有 **3** 个朋友！这比普通龙多一个。

你得到了三个整数 $ n $ , $ x $ 和 $ y $ 。有 $ n $ 只龙围成一个圈坐着。龙从 $ 1 $ 到 $ n $ 编号。对于每个 $ i $ ( $ 1 \le i \le n $ )，龙 $ i $ 与龙 $ i - 1 $ 和 $ i + 1 $ 是朋友，其中龙 $ 0 $ 被定义为龙 $ n $ ，龙 $ n + 1 $ 被定义为龙 $ 1 $ 。此外，龙 $ x $ 和龙 $ y $ 也是朋友（如果它们已经是朋友了，这不会改变任何东西）。请注意，所有的友谊都是相互的。

你需要输出 $ n $ 个非负整数 $ a_1, a_2, \ldots, a_n $ ，使得对于每只龙 $ i $ ( $ 1 \le i \le n $ )，以下条件成立：

- 设 $ f_1, f_2, \ldots, f_k $ 是龙 $ i $ 的朋友。那么 $ a_i = \operatorname{mex}(a_{f_1}, a_{f_2}, \ldots, a_{f_k}) $ 。 $ ^{\text{∗}} $

 $ ^{\text{∗}} $ 集合 $ c_1, c_2, \ldots, c_m $ 的最小排除值 (MEX) 被定义为最小的非负整数 $ t $ ，它不在集合 $ c $ 中出现。

## 输入格式

每个测试用例包含多个测试用例。第一行包含测试用例的数量 $ t $ ( $ 1 \le t \le 10^4 $ )。测试用例的描述如下。

每个测试用例的第一行也是唯一的一行，包含三个整数 $ n $ , $ x $ , $ y $ ( $ 3 \le n \le 2 \cdot 10^5 $ , $ 1 \le x < y \le n $ )。

保证所有测试用例的 $ n $ 之和不超过 $ 2 \cdot 10^5 $ 。

## 输出格式

对于每个测试用例，输出一行包含 $ n $ 个空格分隔的非负整数 $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ )，满足题目中的条件。如果有多个解，输出任意一个。可以证明，在问题约束下，存在满足 $ 0 \le a_i \le 10^9 $ 的解。

## 说明/提示

对于第一个测试用例：

- $ i = 1 $ : 龙 $ 1 $ 的朋友是龙 $ 2, 3, 5 $  $ \operatorname{mex}(a_2, a_3, a_5) = \operatorname{mex}(2, 1, 1) = 0 = a_1 $ ，所以龙 $ 1 $ 的条件满足
- $ i = 2 $ : 龙 $ 2 $ 的朋友是龙 $ 1, 3 $  $ \operatorname{mex}(a_1, a_3) = \operatorname{mex}(0, 1) = 2 = a_2 $ 
- $ i = 3 $ : 龙 $ 3 $ 的朋友是龙 $ 1, 2, 4 $  $ \operatorname{mex}(a_1, a_2, a_4) = \operatorname{mex}(0, 2, 0) = 1 = a_3 $ 
- $ i = 4 $ : 龙 $ 4 $ 的朋友是龙 $ 3, 5 $  $ \operatorname{mex}(a_3, a_5) = \operatorname{mex}(1, 1) = 0 = a_4 $ 
- $ i = 5 $ : 龙 $ 5 $ 的朋友是龙 $ 1, 4 $  $ \operatorname{mex}(a_1, a_4) = \operatorname{mex}(0, 0) = 1 = a_5 $

## 样例 #1

### 输入

```
7
5 1 3
4 2 4
6 3 5
7 3 6
3 2 3
5 1 5
6 2 5
```

### 输出

```
0 2 1 0 1
1 2 1 0
1 2 0 1 2 0
0 1 2 0 1 0 1
2 0 1
1 0 2 1 0
0 1 2 0 2 1
```



---

---
title: "Skibidus and Rizz"
layout: "post"
diff: 普及/提高-
pid: CF2065E
tag: ['构造']
---

# Skibidus and Rizz

## 题目描述

情人节将至，Skibidus 拼命需要一种方法来吸引他的暗恋对象！幸运的是，他找到了正解：制造完美的二进制字符串！

给定一个二进制字符串$^{\text{∗}} $ $t$，令 $x$ 表示 $t$ 中 $\texttt{0}$ 的个数，$y$ 表示 $t$ 中 $\texttt{1}$ 的个数。我们定义字符串的平衡值为 $\max(x-y,\, y-x)$。

Skibidus 给你三个整数 $n$，$m$ 和 $k$。他希望你构造一个长度为 $n+m$ 的二进制字符串 $s$，其中恰好包含 $n$ 个 $\texttt{0}$ 和 $m$ 个 $\texttt{1}$，并且要求其所有子串$^{\text{†}} $的平衡值的最大值恰好为 $k$。如果不存在满足条件的字符串，请输出 -1。

$ ^{\text{∗}} $ 二进制字符串指仅由字符 $\texttt{0}$ 和 $\texttt{1}$ 组成的字符串。

$ ^{\text{†}} $ 字符串 $a$ 是字符串 $b$ 的子串，意味着 $a$ 可以通过删除 $b$ 开头和结尾的若干（可能为 0 或全部）字符得到。

## 输入格式

第一行包含一个整数 $t$ ($1 \leq t \leq 10^4$)，表示测试用例的数量。

每个测试用例的唯一一行包含三个整数 $n$，$m$ 和 $k$ ($0 \leq n, m \leq 2\cdot 10^5$，$1 \leq k \leq n+m$，$n+m \geq 1$)。

保证所有测试用例中，$n$ 的总和和 $m$ 的总和均不超过 $2\cdot 10^5$。

## 输出格式

对于每个测试用例，如果可以构造满足条件的 $s$，输出任意一个满足条件的字符串；否则，输出 -1。

## 说明/提示

在第一个测试用例中，我们必须构造一个字符串 $s$，包含 1 个 $\texttt{0}$ 和 2 个 $\texttt{1}$，且所有子串中的最大平衡值为 $1$。一个可能的满足条件的字符串是 $\texttt{101}$，原因如下：

- 考虑由索引 $[1,1]$ 界定的子串：平衡值为 $\max(0-1,\, 1-0) = 1$。
- 考虑由索引 $[1,2]$ 界定的子串：平衡值为 $\max(1-1,\, 1-1) = 0$。
- 考虑由索引 $[1,3]$ 界定的子串：平衡值为 $\max(1-2,\, 2-1) = 1$。
- 考虑由索引 $[2,2]$ 界定的子串：平衡值为 $\max(1-0,\, 0-1) = 1$。
- 考虑由索引 $[2,3]$ 界定的子串：平衡值为 $\max(1-1,\, 1-1) = 0$。
- 考虑由索引 $[3,3]$ 界定的子串：平衡值为 $\max(0-1,\, 1-0) = 1$。

在所有可能的子串中，最大的平衡值为 $1$。

在第二个测试用例中，具有最大平衡值的子串为 $\texttt{0100}$，其平衡值为 $\max(3-1,\, 1-3) = 2$。

## 样例 #1

### 输入

```
6
1 2 1
4 3 2
2 4 3
8 3 2
5 0 4
5 0 5
```

### 输出

```
101
0100101
011011
-1
-1
00000
```



---

---
title: "Creating Keys for StORages Has Become My Main Skill"
layout: "post"
diff: 普及/提高-
pid: CF2072C
tag: ['贪心', '位运算', '构造']
---

# Creating Keys for StORages Has Become My Main Skill

## 题目描述

Akito 仍然无处可住，而小房间的价格却居高不下。为此，Akito 决定在银行找一份为存储设备创建密钥的工作。

在这个魔法世界中，一切都与众不同。例如，代码为 $(n, x)$ 的存储设备的密钥是一个满足以下条件的长度为 $n$ 的数组 $a$：

- $a_1 \mid a_2 \mid a_3 \mid \ldots \mid a_n = x$，其中 $a \mid b$ 表示数 $a$ 和 $b$ 的[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。
- $\text{MEX}(\{ a_1, a_2, a_3, \ldots, a_n \})$ $^{\text{∗}}$ 在所有满足条件的数组中达到最大值。

Akito 勤奋地工作了几个小时，但突然头痛发作。请代替他工作一小时：对于给定的 $n$ 和 $x$，创建任意一个满足代码为 $(n, x)$ 的存储设备的密钥。

$^{\text{∗}}$ $\text{MEX}(S)$ 是满足以下条件的最小非负整数 $z$：$z$ 不在集合 $S$ 中，且所有满足 $0 \le y < z$ 的 $y$ 都在集合 $S$ 中。

## 输入格式

第一行包含一个数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的唯一一行包含两个数 $n$ 和 $x$（$1 \le n \le 2 \cdot 10^5$，$0 \le x < 2^{30}$）——数组的长度和按位或运算的目标值。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数 $a_i$（$0 \le a_i < 2^{30}$）——满足所有条件的密钥数组元素。

如果存在多个符合条件的数组，输出其中任意一个即可。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
9
1 69
7 7
5 7
7 3
8 7
3 52
9 11
6 15
2 3
```

### 输出

```
69
6 0 3 4 1 2 5
4 1 3 0 2
0 1 2 3 2 1 0
7 0 6 1 5 2 4 3
0 52 0
0 1 8 3 0 9 11 2 10
4 0 3 8 1 2
0 3
```



---

---
title: "Do You Love Your Hero and His Two-Hit Multi-Target Attacks?"
layout: "post"
diff: 普及/提高-
pid: CF2072E
tag: ['数学', '构造']
---

# Do You Love Your Hero and His Two-Hit Multi-Target Attacks?

## 题目描述

Akito 决定学习一个强大的新咒语。由于这个咒语拥有无可估量的力量，它必然需要大量空间和精心准备。为此，Akito 来到了一片空地。我们将这片空地表示为一个笛卡尔坐标系。

为了施展咒语，Akito 需要在空地的不同整数坐标处放置 $0 \le n \le 500$ 根法杖，使得恰好存在 $k$ 对 $(i, j)$ 满足 $1 \le i < j \le n$ 且 $\rho(i, j) = d(i, j)$。

这里，对于两个整数坐标点 $a = (x_a, y_a)$ 和 $b = (x_b, y_b)$，定义 $\rho(a, b) = \sqrt{(x_a - x_b)^2 + (y_a - y_b)^2}$ 且 $d(a, b) = |x_a - x_b| + |y_a - y_b|$。

## 输入格式

输入的第一行包含一个数 $t$（$1 \le t \le 1000$）——测试用例的数量。

每个测试用例的唯一一行包含一个数 $k$（$0 \le k \le 10^5$）——满足 $\rho(i, j) = d(i, j)$ 的法杖对数要求。

## 输出格式

对于每个测试用例，输出的第一行应包含一个数 $n$（$0 \le n \le 500$）——放置的法杖数量。

接下来的 $n$ 行中，每行应输出两个整数 $x_i, y_i$（$-10^9 \le x_i, y_i \le 10^9$）——第 $i$ 根法杖的坐标。所有法杖的坐标点必须互不相同。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
0
2
5
```

### 输出

```
6
69 52
4 20
789 9308706
1337 1337
-1234 -5678
23456178 707
10
-236 -346262358
273568 6435267
2365437 31441367
246574 -45642372
-236 56
4743623 -192892 
10408080 -8173135
-237415357 31441367
-78125638 278
56 143231
5
1 1
2 1
1 5
3 5
1 10
```



---

---
title: "XOR and Triangle"
layout: "post"
diff: 普及/提高-
pid: CF2074C
tag: ['位运算', '构造']
---

# XOR and Triangle

## 题目描述

这次，粉色士兵们给了你一个整数 $x$（$x \ge 2$）。

请判断是否存在一个正整数 $y$ 满足以下条件：

- $y$ 严格小于 $x$
- 存在一个非退化三角形$^{\text{∗}}$，其边长为 $x$、$y$ 和 $x \oplus y$。其中 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

若存在这样的整数 $y$，请输出任意一个满足条件的值。

$^{\text{∗}}$当边长为 $a$、$b$、$c$ 的三角形满足 $a + b > c$、$a + c > b$ 且 $b + c > a$ 时，该三角形是非退化的。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 2000$）。接下来是每个测试用例的描述。

每个测试用例的单独一行包含一个整数 $x$（$2 \le x \le 10^9$）。

## 输出格式

对于每个测试用例，在单独一行中输出一个整数：

- 若存在满足条件的整数 $y$，输出 $y$ 的值（$1 \le y < x$）
- 否则输出 $-1$

若存在多个满足条件的整数，可以输出任意一个。

## 说明/提示

在第一个测试用例中，存在边长为 $3$、$5$ 和 $3 \oplus 5 = 6$ 的非退化三角形。因此 $y=3$ 是有效答案。

在第二个测试用例中，$1$ 是 $y$ 的唯一可能候选值，但无法构成非退化三角形。因此答案为 $-1$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
7
5
2
6
3
69
4
420
```

### 输出

```
3
-1
5
-1
66
-1
320
```



---

---
title: "Trulimero Trulicina"
layout: "post"
diff: 普及/提高-
pid: CF2094F
tag: ['构造', '分类讨论']
---

# Trulimero Trulicina

## 题目描述

Trulicina 给你三个整数 $n$、$m$ 和 $k$。题目保证 $k \geq 2$ 且 $n \cdot m \equiv 0 \pmod{k}$。

请输出一个 $n \times m$ 的整数网格，满足以下所有条件：
- 网格中的每个整数都在 $1$ 到 $k$ 之间（包含 $1$ 和 $k$）。
- 从 $1$ 到 $k$ 的每个整数出现的次数相同。
- 共享一条边的两个单元格不能包含相同的整数。

可以证明这样的网格总是存在。如果存在多个解，输出任意一个即可。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——测试用例的数量。

每个测试用例的第一行包含三个整数 $n$、$m$ 和 $k$（$2 \leq n \cdot m \leq 2 \cdot 10^5$，$2 \leq k \leq n \cdot m$，$n \cdot m \equiv 0 \pmod{k}$）。

保证所有测试用例的 $n \cdot m$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出 $n$ 行，每行包含 $m$ 个满足条件的整数。如果存在多个解，输出任意一个即可。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
2 2 2
3 4 6
5 5 25
```

### 输出

```
1 2
2 1
1 6 1 6
2 5 2 5
3 4 3 4
17 2 12 25 14
3 1 6 19 11
8 20 23 24 4
9 10 5 13 21
22 7 15 18 16
```



---

---
title: "网格 mex"
layout: "post"
diff: 普及/提高-
pid: CF2101A
tag: ['构造']
---

# 网格 mex

## 题目描述

你有一个 $n\times n$ 的网格，初始全部为空。

你要把 $0$ 到 $n^2-1$ 这些数填入网格中，使得每个数出现恰好一次，并使这个网格的所有子网格的 mex 值之和最大。

一个网格是另一个网格的子网格，当且仅当在后者中存在一个矩形区域和前者完全相同。\
一个网格的 mex 最小的没有出现在此网格中的非负整数。

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 100)$，表示数据组数。

对于每组数据，输入一行一个整数 $n(1\le n\le 500)$。

保证在单个测试点中 $\sum n\le 1000$。

## 输出格式

对于每组数据，输出 $n$ 行，每行 $n$ 个数字，表示你填完数字后的网格。

如果有多解，输出任意一种均可。

## 说明/提示

**样例解释**

第一组数据中，一种可行解是：

|$0$|$1$|
|:-:|:-:|
|$2$|$3$|

这个矩形有 $9$ 个子网格，其中存在 $4$ 个子网格的 mex 大于零，如下所示：

|$0$|
|:-:|

mex 为 $1$。

|$0$|$1$|
|:-:|:-:|

mex 为 $2$。

|$0$|
|:-:|
|$2$|

mex 为 $1$。

|$0$|$1$|
|:-:|:-:|
|$2$|$3$|

mex 为 $4$。

总和为 $8$，可以证明这是可以达到的最大值。

## 样例 #1

### 输入

```
2
2
3
```

### 输出

```
0 1 
2 3 
8 4 5 
6 0 1 
7 2 3
```



---

---
title: "Maximum Subarray Sum"
layout: "post"
diff: 普及/提高-
pid: CF2107C
tag: ['贪心', '构造']
---

# Maximum Subarray Sum

## 题目描述

给你一个长为 $n$ 的序列 $a=(a_1,a_2,\cdots,a_n)$，$a$ 的一部分丢失了。你的任务是填补丢失的部分使得 $a$ 的最大子区间和为 $k$，或报告无解。

给你一个 01 串 $s$ 和 $a$：
- 如果 $a_i$ 没有被丢失，$s_i=1$，此时 $a_i$ 记录了它的真实值。
- 如果 $a_i$ 被丢失，$s_i=0$，此时给到你的序列 $a$ 中 $a_i=0$。

输入的 $a$ 满足 $\vert a_i\vert\le 10^6$，你填充后的 $a$ 需要满足 $\vert a_i\vert \le 10^{18}$。可以被证明如果存在解，那么一定存在一个满足 $\vert a_i\vert \le 10^{18}$ 的解。

一个长为 $n$ 的数列 $a$ 的最大子区间和是 $\max\limits_{1\le i\le j\le n}\sum\limits_{k=i}^j a_k$。

## 输入格式

多组数据，第一行一个整数为数据组数 $t(1\le t\le 10^4)$。

对于每组数据，第一行两个整数 $n,k(1\le n\le 2\times 10^5,1\le k\le 10^{12})$。\
第二行为一个长为 $n$ 的 01 字符串 $s$。\
第三行 $n$ 个整数 $a_1,a_2,\cdots,a_n(\vert a_i\vert\le 10^6)$。保证 $s_i=0$ 时 $a_i=0$。

保证一个测试点中 $\sum n\le 2\times 10^5$。

## 输出格式

对于每组数据，第一行一个字符串，如果有解输出 `Yes`，如果无解输出 `No`。大小写不敏感。

如果有解，第二行输出填充后的字符串 $a$。你需要保证 $\vert a_i\vert\le 10^{18}$。

如果有多种解法，输出任意一种均可。

## 说明/提示

第一组数据中，向唯一丢失的 $a_1$ 填充 $4$ 得到 $a=(4,0,1)$，它的最大子区间和为 $5$。

第二组数据中，向唯一丢失的 $a_3$ 填充 $5$ 得到 $a=(4,-3,5,-2,1)$，它的最大子区间和为 $6$。

第三组数据中 $a_1$ 和 $a_2$ 待填充，向它们填充 $2$ 得到 $a=(2,2,-4,-5)$，它的最大子区间和为 $4$。$a=(0,4,-4,-5)$ 也是一种解法。

对于第四组数据，没有合法的填充 $a$ 的方式。例如 $a=(1,2,0,5,-1,9)$，它的最大子区间和为 $16$ 而非 $12$。

By chenxi2009

## 样例 #1

### 输入

```
10
3 5
011
0 0 1
5 6
11011
4 -3 0 -2 1
4 4
0011
0 0 -4 -5
6 12
110111
1 2 0 5 -1 9
5 19
00000
0 0 0 0 0
5 19
11001
-8 6 0 0 -5
5 10
10101
10 0 10 0 10
1 1
1
0
3 5
111
3 -1 3
4 5
1011
-2 0 1 -5
```

### 输出

```
Yes
4 0 1
Yes
4 -3 5 -2 1
Yes
2 2 -4 -5
No
Yes
5 1 9 2 2
Yes
-8 6 6 7 -5
Yes
10 -20 10 -20 10
No
Yes
3 -1 3
Yes
-2 4 1 -5
```



---

---
title: "最大子区间和"
layout: "post"
diff: 普及/提高-
pid: CF2107C
tag: ['贪心', '构造']
---

# 最大子区间和

## 题目描述

给你一个长为 $n$ 的序列 $a=(a_1,a_2,\cdots,a_n)$，$a$ 的一部分丢失了。你的任务是填补丢失的部分使得 $a$ 的最大子区间和为 $k$，或报告无解。

给你一个 01 串 $s$ 和 $a$：
- 如果 $a_i$ 没有被丢失，$s_i=1$，此时 $a_i$ 记录了它的真实值。
- 如果 $a_i$ 被丢失，$s_i=0$，此时给到你的序列 $a$ 中 $a_i=0$。

输入的 $a$ 满足 $\vert a_i\vert\le 10^6$，你填充后的 $a$ 需要满足 $\vert a_i\vert \le 10^{18}$。可以被证明如果存在解，那么一定存在一个满足 $\vert a_i\vert \le 10^{18}$ 的解。

一个长为 $n$ 的数列 $a$ 的最大子区间和是 $\max\limits_{1\le i\le j\le n}\sum\limits_{k=i}^j a_k$。

## 输入格式

多组数据，第一行一个整数为数据组数 $t(1\le t\le 10^4)$。

对于每组数据，第一行两个整数 $n,k(1\le n\le 2\times 10^5,1\le k\le 10^{12})$。\
第二行为一个长为 $n$ 的 01 字符串 $s$。\
第三行 $n$ 个整数 $a_1,a_2,\cdots,a_n(\vert a_i\vert\le 10^6)$。保证 $s_i=0$ 时 $a_i=0$。

保证一个测试点中 $\sum n\le 2\times 10^5$。

## 输出格式

对于每组数据，第一行一个字符串，如果有解输出 `Yes`，如果无解输出 `No`。大小写不敏感。

如果有解，第二行输出填充后的字符串 $a$。你需要保证 $\vert a_i\vert\le 10^{18}$。

如果有多种解法，输出任意一种均可。

## 说明/提示

第一组数据中，向唯一丢失的 $a_1$ 填充 $4$ 得到 $a=(4,0,1)$，它的最大子区间和为 $5$。

第二组数据中，向唯一丢失的 $a_3$ 填充 $5$ 得到 $a=(4,-3,5,-2,1)$，它的最大子区间和为 $6$。

第三组数据中 $a_1$ 和 $a_2$ 待填充，向它们填充 $2$ 得到 $a=(2,2,-4,-5)$，它的最大子区间和为 $4$。$a=(0,4,-4,-5)$ 也是一种解法。

对于第四组数据，没有合法的填充 $a$ 的方式。例如 $a=(1,2,0,5,-1,9)$，它的最大子区间和为 $16$ 而非 $12$。

By chenxi2009

## 样例 #1

### 输入

```
10
3 5
011
0 0 1
5 6
11011
4 -3 0 -2 1
4 4
0011
0 0 -4 -5
6 12
110111
1 2 0 5 -1 9
5 19
00000
0 0 0 0 0
5 19
11001
-8 6 0 0 -5
5 10
10101
10 0 10 0 10
1 1
1
0
3 5
111
3 -1 3
4 5
1011
-2 0 1 -5
```

### 输出

```
Yes
4 0 1
Yes
4 -3 5 -2 1
Yes
2 2 -4 -5
No
Yes
5 1 9 2 2
Yes
-8 6 6 7 -5
Yes
10 -20 10 -20 10
No
Yes
3 -1 3
Yes
-2 4 1 -5
```



---

---
title: "Racing"
layout: "post"
diff: 普及/提高-
pid: CF2110C
tag: ['构造']
---

# Racing

## 题目描述

在 2077 年，一项名为"业余无人机竞速"的运动在机器人中越来越流行。

你已经拥有一架无人机，并且想要获胜。为此，你的无人机需要飞越一个包含 $n$ 个障碍物的赛道。

第 $i$ 个障碍物由两个数字 $l_i, r_i$ 定义。设你的无人机在第 $i$ 个障碍物处的高度为 $h_i$，那么当且仅当 $l_i \le h_i \le r_i$ 时，无人机才能通过该障碍物。初始时无人机位于地面，即 $h_0 = 0$。

无人机的飞行程序由一个数组 $d_1, d_2, \ldots, d_n$ 表示，其中 $h_{i} - h_{i-1} = d_i$，且 $0 \leq d_i \leq 1$。这意味着你的无人机在障碍物之间要么保持高度不变，要么上升 $1$ 个单位。你已经有一个飞行程序，但其中某些 $d_i$ 未知并被标记为 $-1$。你需要将这些未知的 $d_i$ 替换为 $0$ 或 $1$，以创建一个能完整通过所有障碍物的飞行程序，或者报告这是不可能的。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——数组 $d$ 的大小。

每个测试用例的第二行包含 $n$ 个整数 $d_1, d_2, \ldots, d_n$（$-1 \leq d_i \leq 1$）——数组 $d$ 的元素。$d_i = -1$ 表示该 $d_i$ 是未知的。

接下来 $n$ 行，每行包含 $2$ 个整数 $l_i, r_i$（$0 \leq l_i \leq r_i \leq n$）——障碍物的描述。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果能够正确恢复数组 $d$，则输出 $n$ 个整数 $d_1, d_2, \ldots, d_n$；如果不可能，则输出 $-1$。


## 说明/提示

在第一个测试用例中，一个可能的答案是 $d=[0,1,1,1]$。此时数组 $h$ 将为 $[0,0+1,0+1+1,0+1+1+1]=[0,1,2,3]$。这个数组满足题目条件。

在第二个测试用例中，可以证明不存在满足条件的数组 $d$，因此答案为 $-1$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
4
0 -1 -1 1
0 4
1 2
2 4
1 4
3
0 -1 -1
0 1
2 2
0 3
2
-1 -1
0 0
2 2
8
-1 -1 1 -1 -1 0 0 -1
0 0
0 1
0 2
0 2
1 3
0 4
2 5
4 5
1
0
1 1
```

### 输出

```
0 1 1 1 
-1
-1
0 1 1 0 1 0 0 1 
-1
```



---

---
title: "Make It Permutation"
layout: "post"
diff: 普及/提高-
pid: CF2118B
tag: ['构造']
---

# Make It Permutation

## 题目描述

有一个大小为 $ n \times n $ 的矩阵 $ A $，其中对于所有 $ 1 \le i,j \le n $，$ A_{i,j} = j $。

在一次操作中，你可以选择一行，并反转该行中的任意子数组$^{\text{∗}}$。

请找到最多 $ 2n $ 次操作的序列，使得每一列都包含一个长度为 $ n $ 的排列$^{\text{†}}$。

可以证明这样的构造总是可能的。如果有多个解，输出任意一个即可。

$^{\text{∗}}$ 数组 $ a $ 是数组 $ b $ 的子数组，如果 $ a $ 可以通过从 $ b $ 的开头删除零个或多个元素，以及从 $ b $ 的末尾删除零个或多个元素得到。

$^{\text{†}}$ 长度为 $ n $ 的排列是一个由 $ 1 $ 到 $ n $ 的 $ n $ 个不同整数按任意顺序组成的数组。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 不是排列（$ 2 $ 出现了两次），$ [1,3,4] $ 也不是排列（$ n=3 $ 但出现了 $ 4 $）。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $ t $（$ 1 \le t \le 100 $）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $ n $（$ 3 \le n \le 5000 $），表示矩阵的行数和列数。

保证所有测试用例的 $ n $ 之和不超过 $ 5000 $。

## 输出格式

对于每个测试用例，第一行输出一个整数 $ k $（$ 0 \le k \le 2n $），表示你希望执行的操作次数。接下来的行中，输出这些操作。

每个操作的输出格式为“$ i\;l\;r $”（$ 1 \leq l \leq r \leq n $ 且 $ 1 \leq i \leq n $），表示反转第 $ i $ 行的子数组 $ A_{i, l} $, $ A_{i, l+1} $, ..., $ A_{i, r} $。

## 说明/提示

在第一个测试用例中，以下操作是一个有效的解：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2118B/2e920475092c0a06b7e6444770e39ca0f6a17a41.png)

## 样例 #1

### 输入

```
2
3
4
```

### 输出

```
4
2 1 3
2 2 3
3 1 2
3 2 3
5
2 1 4
3 1 3
3 2 4
4 3 4
4 1 2
```



---

---
title: "k-String"
layout: "post"
diff: 普及/提高-
pid: CF219A
tag: ['字符串', '构造']
---

# k-String

## 题目描述

- **题面翻译如下**

如果一个字符串可以被划分为 $k$ 个相同的子串，则称这个字符串为 $k$-string。例如，字符串“aabaabaabaab”同时是 $1$-string, $2$-string和 $4$-string，但它不是 $3$-string, $5$-string 或 $6$-string 等。显然，任何字符串都是 $1$-string。

给你一个由小写英文字母组成的字符串 $s$ 和一个正整数 $k$。你需要将字符串 $s$ 重新排列成一个 $k$-string。

## 输入格式

第一行，一个正整数 $ k $ ($ 1\le k \le 1000 $)。  
第二行，一个由小写英文字母组成的字符串 $ s $，（$ 1<=|s|<=1000 $， $ |s| $ 表示字符串 $s$ 的长度）。

## 输出格式

- 共一行，一个经过重新排列后的字符串。如果存在多种排列方案，输出其中任意一种即可。  
- 如果不存在解决方案，则输出“-1”（不含双引号）。

## 样例 #1

### 输入

```
2
aazz

```

### 输出

```
azaz

```

## 样例 #2

### 输入

```
3
abcabcabz

```

### 输出

```
-1

```



---

---
title: "System Administrator"
layout: "post"
diff: 普及/提高-
pid: CF22C
tag: ['贪心', '连通块', '构造']
---

# System Administrator

## 题目描述

给定 $n$ 个顶点，可以在这些顶点之间连接 $m$ 条双向边，要求连接后整个图联通，并且去掉 $v$ 点后整个图不连通。

若有解，输出所连得的 $m$ 条边，随意输出一种方案即可；若无解，输出 ```-1```。

## 输入格式

一行三个整数表示 $n,m,v$。

## 输出格式

共 $m$ 行，每行两个整数 $u_i$ 和 $v_i$，表示 $u_i$ 向 $v_i$ 连一条边。

## 说明/提示

- $n, m \le {10}^5$

Translated by 稀神探女

## 样例 #1

### 输入

```
5 6 3

```

### 输出

```
1 2
2 3
3 4
4 5
1 3
3 5

```

## 样例 #2

### 输入

```
6 100 1

```

### 输出

```
-1

```



---

---
title: "Chess"
layout: "post"
diff: 普及/提高-
pid: CF38B
tag: ['构造']
---

# Chess

## 题目描述

在一个大小8×8的国际象棋的棋盘有车和马两个棋子，保证一个棋子无法吃掉另一个。
    请把另一个马放在棋盘上,使得三个棋子都无法吃掉另一个。棋子只能放在一个空的地方。

## 输入格式

输入第一行，有两个字符。第一个字符是小写字母a~h,第二个是1~8的一个数字，表示车的位置。第二行骑士的位置类似。保证他们的位置不一致。

## 输出格式

方案总数。

Translated by @少谷

## 样例 #1

### 输入

```
a1
b2

```

### 输出

```
44

```

## 样例 #2

### 输入

```
a8
d4

```

### 输出

```
38

```



---

---
title: "New Year Book Reading"
layout: "post"
diff: 普及/提高-
pid: CF500C
tag: ['模拟', '贪心', '构造']
---

# New Year Book Reading

## 题目描述

小明非常喜欢读书。他一共有 $n$ 本书，编号为 $1\sim n$，第 $i$本书重 $w_i$。

小明计划在暑假的 $m$ 天里每天读一本书，第 $i$ 天读第 $d_i$ 本书，可能会重复读到同一本书。

因为所有的书都是堆成一摞的，所以每次读某本书之前小明都需要先将这本书上面所有的书搬开，拿出这本书，再将搬开的书按原顺序放回去，消耗体力为搬开书的重量之和，读完这本书后将其放在这摞书的最上面。

小明想知道这 $n$ 本书以怎样的初始顺序放置，所搬书消耗总体力最小。

## 输入格式

第一行两个正整数 $n,m$，表示小明一共有 $n$ 本书，要读 $m$ 天。

第二行 $n$ 个正整数，第 $i$ 个数表示表示第 $i$本书的重量为 $w_i$。

第三行 $m$ 个正整数，第 $i$ 个数表示第 $i$ 天要读第 $d_i$ 本书。

## 输出格式

一行一个数，表示读完 $m$ 次书所搬书消耗的最小体力值。

## 样例 #1

### 输入

```
3 5
1 2 3
1 3 2 3 1

```

### 输出

```
12

```



---

---
title: "Chtholly's request"
layout: "post"
diff: 普及/提高-
pid: CF897B
tag: ['枚举', '构造']
---

# Chtholly's request

## 题目描述

 — Thanks a lot for today.— I experienced so many great things.

— You gave me memories like dreams... But I have to leave now...

— One last request, can you...

— Help me solve a Codeforces problem?

— ......

— What?





Chtholly has been thinking about a problem for days:

If a number is palindrome and length of its decimal representation without leading zeros is even, we call it a zcy number. A number is palindrome means when written in decimal representation, it contains no leading zeros and reads the same forwards and backwards. For example 12321 and 1221 are palindromes and 123 and 12451 are not. Moreover, 1221 is zcy number and 12321 is not.

Given integers $ k $ and $ p $ , calculate the sum of the $ k $ smallest zcy numbers and output this sum modulo $ p $ .

Unfortunately, Willem isn't good at solving this kind of problems, so he asks you for help!

## 输入格式

The first line contains two integers $ k $ and $ p $ $ (1<=k<=10^{5},1<=p<=10^{9}) $ .

## 输出格式

Output single integer — answer to the problem.

## 说明/提示

In the first example, the smallest zcy number is $ 11 $ , and the second smallest zcy number is $ 22 $ .

In the second example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF897B/8301f23cf6a6ac38a43acd044c106b422734f787.png).

## 样例 #1

### 输入

```
2 100

```

### 输出

```
33

```

## 样例 #2

### 输入

```
5 30

```

### 输出

```
15

```



---

---
title: "Permutation Cycle"
layout: "post"
diff: 普及/提高-
pid: CF932C
tag: ['构造']
---

# Permutation Cycle

## 题目描述

**【题意】：**



我们有一个序列$P$，对于任意整数$i(1 \leq i \leq N)$，满足$1 \leq P_i \leq N$。



我们定义一个函数$f$，其中$f_{i,j}$的值满足：



- 当$j=1$时，$f_{i,j}=P_i$。

- 当$j\neq 1$时，$f_{i,j}=f_{P_i,j-1}$。



我们记$G_i$表示令$f_{i,j}=i$成立的最小的$j$。我们可以证明$G_i$是一定存在的。



输入$N,A,B$。$A,B$表示$G_i$只能等于$A$或$B$。求一个可能的$P$，使得对于任意$i(1 \leq i \leq N)$，都有$f_{i,j}=i$。

## 样例 #1

### 输入

```
9 2 5

```

### 输出

```
6 5 8 3 4 1 9 2 7
```

## 样例 #2

### 输入

```
3 2 1

```

### 输出

```
1 2 3 
```



---

