---
title: "Reorder the Array"
layout: "post"
diff: 普及+/提高
pid: CF1008C
tag: ['排序']
---

# Reorder the Array

## 题目描述

**题目大意：**

给定一个序列，序列里的元素可以以任意顺序重新排好

序列里某位置排序后的数可能会大于原数，问这样的位置最多能有多少个

## 输入格式

第一行一个整数$n$，表示序列长度

第二行$n$个整数，表示初始序列

## 输出格式

一个整数，表示满足条件的位置最多能有多少个

## 样例 #1

### 输入

```
7
10 1 1 1 5 5 3

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5
1 1 1 1 1

```

### 输出

```
0

```



---

---
title: "Repetitions Decoding"
layout: "post"
diff: 普及+/提高
pid: CF1641B
tag: ['排序', '构造']
---

# Repetitions Decoding

## 题目描述

Olya has an array of integers $ a_1, a_2, \ldots, a_n $ . She wants to split it into tandem repeats. Since it's rarely possible, before that she wants to perform the following operation several (possibly, zero) number of times: insert a pair of equal numbers into an arbitrary position. Help her!

More formally:

- A tandem repeat is a sequence $ x $ of even length $ 2k $ such that for each $ 1 \le i \le k $ the condition $ x_i = x_{i + k} $ is satisfied.
- An array $ a $ could be split into tandem repeats if you can split it into several parts, each being a subsegment of the array, such that each part is a tandem repeat.
- In one operation you can choose an arbitrary letter $ c $ and insert $ [c, c] $ to any position in the array (at the beginning, between any two integers, or at the end).
- You are to perform several operations and split the array into tandem repeats or determine that it is impossible. Please note that you do not have to minimize the number of operations.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 30\,000 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 500 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the initial array.

It is guaranteed that the sum of $ n^2 $ over all test cases does not exceed $ 250\,000 $ .

## 输出格式

For each test case print answer in the following format.

If you cannot turn the array into a concatenation of tandem repeats, print a single integer $ -1 $ .

Otherwise print the number of operations $ q $ ( $ 0 \le q \le 2 \cdot n^2 $ ) that you want to do. Then print the descriptions of operations.

In each of the following $ q $ lines print two integers $ p $ and $ c $ ( $ 1 \le c \le 10^9 $ ), which mean that you insert the integer $ c $ twice after $ p $ elements of the array. If the length of the array is $ m $ before the operation, then the condition $ 0 \le p \le m $ should be satisfied.

Then you should print any way to split the resulting array into tandem repeats. First, print a single integer $ d $ , and then print a sequence $ t_1, t_2, \ldots, t_d $ of even integers of size $ d $ ( $ d, t_i \ge 1 $ ). These numbers are the lengths of the subsegments from left to right.

Note that the size of the resulting array $ a $ is $ m = n + 2 \cdot q $ . The following statements must hold:

- $ m = \sum\limits_{i = 1}^{d}{t_i} $ .
- For all integer $ i $ such that $ 1 \le i \le d $ , the sequence $ a_l, a_{l+1}, \ldots, a_r $ is a tandem repeat, where $ l = \sum\limits_{j = 1}^{i - 1}{t_j} + 1 $ , $ r = l + t_i - 1 $ .

It can be shown that if the array can be turned into a concatenation of tandem repeats, then there exists a solution satisfying all constraints. If there are multiple answers, you can print any.

## 说明/提示

In the first test case, you cannot apply operations to the array to make it possible to split it into tandem repeats.

In the second test case the array is already a tandem repeat $ [5, 5] = \underbrace{([5] + [5])}_{t_1 = 2} $ , thus we can do no operations at all.

In the third test case, initially, we have the following array: $ $$$[1, 3, 1, 2, 2, 3]. $ $  After the first insertion with  $ p = 1, c = 3 $ :  $ $ [1, \textbf{3, 3}, 3, 1, 2, 2, 3]. $ $  After the second insertion with  $ p = 5, c = 3 $ :  $ $ [1, 3, 3, 3, 1, \textbf{3, 3}, 2, 2, 3]. $ $  After the third insertion with  $ p = 5, c = 3 $ :  $ $ [1, 3, 3, 3, 1, \textbf{3, 3}, 3, 3, 2, 2, 3]. $ $  After the fourth insertion with  $ p = 10, c = 3 $ :  $ $ [1, 3, 3, 3, 1, 3, 3, 3, 3, 2, \textbf{3, 3}, 2, 3]. $ $  The resulting array can be represented as a concatenation of tandem repeats:  $ $ \underbrace{([1, 3, 3, 3] + [1, 3, 3, 3])}_{t_1 = 8} + \underbrace{([3, 2, 3] + [3, 2, 3])}_{t_2 = 6}. $ $ </p><p>In the fourth test case, initially, we have the following array:  $ $ [3, 2, 1, 1, 2, 3]. $ $  After the first insertion with  $ p = 0, c = 3 $ :  $ $ [\textbf{3, 3}, 3, 2, 1, 1, 2, 3]. $ $  After the second insertion with  $ p = 8, c = 3 $ :  $ $ [3, 3, 3, 2, 1, 1, 2, 3, \textbf{3, 3}]. $ $  After the third insertion with  $ p = 5, c = 3 $   $ $ [3, 3, 3, 2, 1, \textbf{3, 3}, 1, 2, 3, 3, 3]. $ $  After the fourth insertion with  $ p = 6, c = 2 $ :  $ $ [3, 3, 3, 2, 1, 3, \textbf{2, 2}, 3, 1, 2, 3, 3, 3]. $ $  After the fifth insertion with  $ p = 7, c = 1 $ :  $ $ [3, 3, 3, 2, 1, 3, 2, \textbf{1, 1}, 2, 3, 1, 2, 3, 3, 3]. $ $  The resulting array can be represented as a concatenation of tandem repeats:  $ $ \underbrace{([3] + [3])}_{t_1 = 2} + \underbrace{([3, 2, 1] + [3, 2, 1])}_{t_2 = 6} + \underbrace{([1, 2, 3] + [1, 2, 3])}_{t_3 = 6} + \underbrace{([3] + [3])}_{t_4 = 2}. $ $$$

## 样例 #1

### 输入

```
4
2
5 7
2
5 5
6
1 3 1 2 2 3
6
3 2 1 1 2 3
```

### 输出

```
-1
0
1
2
4
1 3
5 3
5 3
10 3
2
8 6 
5
0 3
8 3
5 3 
6 2 
7 1
4
2 6 6 2
```



---

---
title: "Toss a Coin to Your Graph..."
layout: "post"
diff: 普及+/提高
pid: CF1679D
tag: ['二分', '拓扑排序']
---

# Toss a Coin to Your Graph...

## 题目描述

One day Masha was walking in the park and found a graph under a tree... Surprised? Did you think that this problem would have some logical and reasoned story? No way! So, the problem...

Masha has an oriented graph which $ i $ -th vertex contains some positive integer $ a_i $ . Initially Masha can put a coin at some vertex. In one operation she can move a coin placed in some vertex $ u $ to any other vertex $ v $ such that there is an oriented edge $ u \to v $ in the graph. Each time when the coin is placed in some vertex $ i $ , Masha write down an integer $ a_i $ in her notebook (in particular, when Masha initially puts a coin at some vertex, she writes an integer written at this vertex in her notebook). Masha wants to make exactly $ k - 1 $ operations in such way that the maximum number written in her notebook is as small as possible.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le m \le 2 \cdot 10^5 $ , $ 1 \le k \le 10^{18} $ ) — the number of vertices and edges in the graph, and the number of operation that Masha should make.

The second line contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le 10^9 $ ) — the numbers written in graph vertices.

Each of the following $ m $ lines contains two integers $ u $ and $ v $ ( $ 1 \le u \ne v \le n $ ) — it means that there is an edge $ u \to v $ in the graph.

It's guaranteed that graph doesn't contain loops and multi-edges.

## 输出格式

Print one integer — the minimum value of the maximum number that Masha wrote in her notebook during optimal coin movements.

If Masha won't be able to perform $ k - 1 $ operations, print $ -1 $ .

## 说明/提示

Graph described in the first and the second examples is illustrated below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679D/f21a10b2a32ca5315b6d3233f4e3f1d967d3f865.png)In the first example Masha can initially put a coin at vertex $ 1 $ . After that she can perform three operations: $ 1 \to 3 $ , $ 3 \to 4 $ and $ 4 \to 5 $ . Integers $ 1, 2, 3 $ and $ 4 $ will be written in the notepad.

In the second example Masha can initially put a coin at vertex $ 2 $ . After that she can perform $ 99 $ operations: $ 2 \to 5 $ , $ 5 \to 6 $ , $ 6 \to 2 $ , $ 2 \to 5 $ , and so on. Integers $ 10, 4, 5, 10, 4, 5, \ldots, 10, 4, 5, 10 $ will be written in the notepad.

In the third example Masha won't be able to perform $ 4 $ operations.

## 样例 #1

### 输入

```
6 7 4
1 10 2 3 4 5
1 2
1 3
3 4
4 5
5 6
6 2
2 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6 7 100
1 10 2 3 4 5
1 2
1 3
3 4
4 5
5 6
6 2
2 5
```

### 输出

```
10
```

## 样例 #3

### 输入

```
2 1 5
1 1
1 2
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
1 0 1
1000000000
```

### 输出

```
1000000000
```



---

---
title: "Matching Arrays"
layout: "post"
diff: 普及+/提高
pid: CF1896C
tag: ['贪心', '排序']
---

# Matching Arrays

## 题目描述

You are given two arrays $ a $ and $ b $ of size $ n $ . The beauty of the arrays $ a $ and $ b $ is the number of indices $ i $ such that $ a_i > b_i $ .

You are also given an integer $ x $ . Determine whether it is possible to rearrange the elements of $ b $ such that the beauty of the arrays becomes $ x $ . If it is possible, output one valid rearrangement of $ b $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ x $ ( $ 1 \le n \le 2\cdot 10^5 $ , $ 0 \le x \le n $ ) — the size of arrays $ a $ and $ b $ and the desired beauty of the arrays.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 2n $ ) — the elements of array $ a $ .

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le 2n $ ) — the elements of array $ b $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output "NO" if it is not possible to rearrange $ b $ to make the beauty of the arrays equal to $ x $ .

Otherwise, output "YES". Then, on the next line, output $ n $ integers which represent the rearrangement of $ b $ .

If there are multiple solutions, you may output any of them.

You can output "YES" and "NO" in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In test cases 1 and 2, the beauty of the arrays has to be $ 0 $ since $ a_1 = 1 \le 2 = b_1 $ .

In test cases 3, 4, 5 and 6, the only possible beauty of the arrays is $ x = 1 $ and $ x = 2 $ . In particular, if $ b $ is rearranged to $ [2, 4, 1] $ , then $ a_3 = 3 > 1 = b_3 $ , so the beauty of the arrays is $ 1 $ . If $ b $ is kept in the same order as given the input, then $ a_2 = 4 > b_2 = 1 $ and $ a_3 = 3 > 2 = b_3 $ , so the beauty of the arrays is $ 2 $ .

## 样例 #1

### 输入

```
7
1 0
1
2
1 1
1
2
3 0
2 4 3
4 1 2
3 1
2 4 3
4 1 2
3 2
2 4 3
4 1 2
3 3
2 4 3
4 1 2
5 2
6 4 5 6 2
9 7 9 1 1
```

### 输出

```
YES
2
NO
NO
YES
2 4 1
YES
4 1 2
NO
YES
1 9 9 7 1
```



---

---
title: "Polyathlon"
layout: "post"
diff: 普及+/提高
pid: CF2038I
tag: ['排序']
---

# Polyathlon

## 题目描述

伯兰（Berland）是今年国际大学生多项全能比赛的主办国！与双项全能是两个项目的比赛类似，多项全能是多个项目的比赛。今年有 $m$ 个项目。此外，还有 $n$ 名参赛者。项目编号从 $1$ 到 $m$ ，参赛者编号从 $1$ 到 $n$ 。

有些参赛者擅长多项运动。我们还知道，对于每一对参与者来说，至少存在一种运动，即其中一人擅长该运动，而另一人不擅长。

比赛项目的顺序在开幕式上决定。从历史上看，它是由万能的随机数生成器决定的。掷出一个从 $1$ 到 $m$ 的随机数 $x$ 。比赛从 $x$ 开始，然后是 $(x \bmod m + 1)$ ，接着是 $((x + 1) \bmod m + 1)$ ，以此类推。

每个项目的比赛规则如下。如果剩下的所有参赛者（所有尚未被淘汰的参赛者）都不擅长该项目，则所有人都进入下一个项目。否则，所有熟练的参赛者都进入下一个项目，所有不熟练的参赛者都被淘汰出局。一旦比赛只剩下一名参赛者，比赛即告结束，该参赛者即为获胜者。

作为比赛的组织者，您事先对比赛可能出现的结果很好奇。对于每个运动项目 $x$ ，如果比赛从运动项目 $x$ 开始，请打印获胜者的编号。

## 输入格式

第一行包含两个整数 $n$ 和 $m$ ( $2 \le n, m \le 10^6,n \le 2^m,nm \le 2 \times 10^6$ )，它们分别是参赛人数和运动项目数。

接下来 $n$ 行的每行中包含一个二进制字符串，该字符串正好由 $m$ 个字符 0 或 1 组成--即第 $i$ 个参赛者的技能组合。如果第 $j$ 个字符为1，则 $i$ 个参赛者熟练掌握了 $j$ 运动。如果为0，则第 $i$ 个参与者不擅长 $j$ 运动。

输入的附加限制：对于每一对参与者来说，至少存在一种运动，即其中一人擅长该运动，而另一人不擅长。换句话说，所有 $n$ 二进制字符串都是成对不同的。

## 输出格式

输出 $m$ 个整数。对于从 $1$ 到 $m$ 的每个 $x$ ，如果比赛从运动 $x$ 开始，则打印获胜者的编号。

## 样例 #1

### 输入

```
3 5
10010
01100
10101
```

### 输出

```
3 2 3 1 3
```



---

---
title: "Recommendations"
layout: "post"
diff: 普及+/提高
pid: CF2042D
tag: ['树状数组', '排序', '扫描线']
---

# Recommendations

## 题目描述

有 $n$ 个区间 $S_i=[l_i,r_i]$，对于每个区间求出 $|\bigcap\limits_{j} S_j|-|S_i|$，其中 $j\neq i$，且 $S_i\subseteq S_j$。即对于每个区间求出其包区间交集的大小，并减去自己的大小。

## 输入格式

$T(1\le t\le 10^4)$ 组测试数据。

每组数据第一行输入 $n(1\le n\le 2\times 10^5)$ 表示区间个数，$\sum\limits n\le 2\times 10^5$。

接下来 $n$ 行，每行两个整数 $l_i,r_i(1\le l_i,r_i\le 10^9)$ 表示区间范围。

## 输出格式

对于每组测试数据，输出 $n$ 行表示第 $i$ 个答案。如果第 $i$ 个区间没有包区间，则直接输出 $0$。

translated by xyin

## 样例 #1

### 输入

```
4
3
3 8
2 5
4 5
2
42 42
1 1000000000
3
42 42
1 1000000000
42 42
6
1 10
3 10
3 7
5 7
4 4
1 2
```

### 输出

```
0
0
1
999999999
0
0
0
0
0
2
3
2
4
8
```



---

---
title: "Medium Demon Problem (hard version)"
layout: "post"
diff: 普及+/提高
pid: CF2044G2
tag: ['贪心', '拓扑排序']
---

# Medium Demon Problem (hard version)

## 题目描述

这是该问题的困难版本。两个版本之间的关键区别已用粗体强调。

有一群 $n$ 只蜘蛛聚在一起交换毛绒玩具。一开始，每只蜘蛛手里都有一个毛绒玩具。每年，如果第 $i$ 只蜘蛛至少有一个毛绒玩具，它会把自己的一个毛绒玩具送给第 $r_i$ 只蜘蛛。否则，它会选择不做任何事情。注意，所有毛绒玩具的转移同时进行。在这个版本中，每只蜘蛛在任何时候都可以拥有多个毛绒玩具。

如果今年（在进行交换之前）每只蜘蛛拥有的毛绒玩具数量与去年（交换之前）相同，那么这一年就是稳定的。需要注意的是，第一年不可能是稳定的。

请找出施行直到稳定的第一个年份。

## 输入格式

第一行输入一个整数 $t$（$1 \leq t \leq 10^4$），表示测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$2 \leq n \leq 2 \cdot 10^5$），表示蜘蛛的数量。

接下来的一行包含 $n$ 个整数 $r_1, r_2, \ldots, r_n$（$1 \leq r_i \leq n, r_i \neq i$），表示每只蜘蛛所指定的收件蜘蛛编号。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数代表过程第一次变得稳定的年份。

## 说明/提示

对于第二个测试用例：

- 第一年，每只蜘蛛拥有的毛绒玩具数量为：$[1, 1, 1, 1, 1]$。接下来进行第一次交换。
- 第二年，每只蜘蛛拥有的毛绒玩具数量仍为：$[1, 1, 1, 1, 1]$。由于这个数组与去年相同，所以第二年是稳定的。

对于第三个测试用例：

- 第一年，每只蜘蛛拥有的毛绒玩具数量为：$[1, 1, 1, 1, 1]$。接下来进行第一次交换。
- 第二年，每只蜘蛛拥有的毛绒玩具数量变为：$[1, 2, 1, 1, 0]$。随后进行第二次交换。
- 第三年，每只蜘蛛拥有的毛绒玩具数量变为：$[1, 3, 0, 1, 0]$。随后进行第三次交换。
- 第四年，每只蜘蛛拥有的毛绒玩具数量变为：$[1, 4, 0, 0, 0]$。随后进行第四次交换。
- 第五年，每只蜘蛛拥有的毛绒玩具数量仍为：$[1, 4, 0, 0, 0]$。由于这个阵列与上一年相同，第五年是稳定的。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
2 1
5
2 3 4 5 1
5
2 1 4 2 3
5
4 1 1 5 4
10
4 3 9 1 6 7 9 10 10 3
```

### 输出

```
2
2
5
5
5
```



---

---
title: "Refined Product Optimality"
layout: "post"
diff: 普及+/提高
pid: CF2053D
tag: ['数学', '贪心', '排序', '逆元']
---

# Refined Product Optimality

## 题目描述

As a tester, when my solution has a different output from the example during testing, I suspect the author first.

— Chris, [a comment](https://codeforces.com/blog/entry/133116?#comment-1190579)



Although Iris occasionally sets a problem where the solution is possibly wrong, she still insists on creating problems with her imagination; after all, everyone has always been on the road with their stubbornness... And like ever before, Iris has set a problem to which she gave a wrong solution, but Chris is always supposed to save it! You are going to play the role of Chris now:

- Chris is given two arrays $ a $ and $ b $ , both consisting of $ n $ integers.
- Iris is interested in the largest possible value of $ P = \prod\limits_{i=1}^n \min(a_i, b_i) $ after an arbitrary rearrangement of $ b $ . Note that she only wants to know the maximum value of $ P $ , and no actual rearrangement is performed on $ b $ .
- There will be $ q $ modifications. Each modification can be denoted by two integers $ o $ and $ x $ ( $ o $ is either $ 1 $ or $ 2 $ , $ 1 \leq x \leq n $ ). If $ o = 1 $ , then Iris will increase $ a_x $ by $ 1 $ ; otherwise, she will increase $ b_x $ by $ 1 $ .
- Iris asks Chris the maximum value of $ P $ for $ q + 1 $ times: once before any modification, then after every modification.
- Since $ P $ might be huge, Chris only needs to calculate it modulo $ 998\,244\,353 $ .

Chris soon worked out this problem, but he was so tired that he fell asleep. Besides saying thanks to Chris, now it is your turn to write a program to calculate the answers for given input data.

Note: since the input and output are large, you may need to optimize them for this problem.

For example, in C++, it is enough to use the following lines at the start of the main() function:

```
<pre class="lstlisting">```
int main() {<br></br>    std::ios::sync_with_stdio(false);<br></br>    std::cin.tie(nullptr); std::cout.tie(nullptr);<br></br>}<br></br>
```
```

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \leq n \leq 2\cdot 10^5 $ , $ 1 \leq q \leq 2\cdot 10^5 $ ) — the length of the array and the number of operations.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 5\cdot 10^8 $ ) — the array $ a $ .

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq 5\cdot 10^8 $ ) — the array $ b $ .

Then $ q $ lines follow, each line contains two integers $ o $ and $ x $ ( $ o \in \{1, 2\} $ , $ 1 \leq x \leq n $ ), representing an operation.

It's guaranteed that the sum of $ n $ and the sum of $ q $ over all test cases does not exceed $ 4\cdot 10^5 $ , respectively.

## 输出格式

For each test case, output $ q + 1 $ integers in a line, representing the answers that Chris will calculate, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case:

- Before the modifications, Chris can rearrange $ b $ to $ [1, 2, 3] $ so that $ P = \prod\limits_{i=1}^n \min(a_i, b_i) = 1 \cdot 1 \cdot 2 = 2 $ . We can prove that this is the maximum possible value. For example, if Chris rearranges $ b = [2, 3, 1] $ , $ P $ will be equal $ 1 \cdot 1 \cdot 1 = 1 < 2 $ , which is not optimal.
- After the first modification, Chris can rearrange $ b $ to $ [1, 2, 3] $ so that $ P = 1 \cdot 1 \cdot 3 = 3 $ , which is maximized.
- After the second modification, Chris can rearrange $ b $ to $ [2, 2, 3] $ so that $ P = 1 \cdot 1 \cdot 3 = 3 $ , which is maximized.
- After the third modification, Chris can rearrange $ b $ to $ [2, 2, 3] $ so that $ P = 6 $ , which is maximized.
- After the fourth modification, Chris can rearrange $ b $ to $ [2, 2, 4] $ so that $ P = 6 $ , which is maximized.

## 样例 #1

### 输入

```
4
3 4
1 1 2
3 2 1
1 3
2 3
1 1
2 1
6 8
1 4 2 7 3 5
7 6 5 6 3 3
2 5
1 6
1 5
1 5
1 5
2 3
2 3
1 6
13 8
7 7 6 6 5 5 5 2 2 3 4 5 1
1 4 1 9 6 6 9 1 5 1 3 8 4
2 2
2 11
2 4
2 4
1 7
1 1
2 12
1 5
5 3
10000000 20000000 30000000 40000000 50000000
10000000 20000000 30000000 40000000 50000000
1 1
2 2
2 1
```

### 输出

```
2 3 3 6 6
840 840 1008 1344 1680 2016 2016 2016 2352
2116800 2646000 3528000 3528000 3528000 4233600 4838400 4838400 4838400
205272023 205272023 205272023 264129429
```



---

---
title: "Chocolate"
layout: "post"
diff: 普及+/提高
pid: CF31D
tag: ['模拟', '排序']
---

# Chocolate

## 题目描述

Bob has a rectangular chocolate bar of the size $ W×H $ . He introduced a cartesian coordinate system so that the point $ (0,0) $ corresponds to the lower-left corner of the bar, and the point $ (W,H) $ corresponds to the upper-right corner. Bob decided to split the bar into pieces by breaking it. Each break is a segment parallel to one of the coordinate axes, which connects the edges of the bar. More formally, each break goes along the line $ x=x_{c} $ or $ y=y_{c} $ , where $ x_{c} $ and $ y_{c} $ are integers. It should divide one part of the bar into two non-empty parts. After Bob breaks some part into two parts, he breaks the resulting parts separately and independently from each other. Also he doesn't move the parts of the bar. Bob made $ n $ breaks and wrote them down in his notebook in arbitrary order. At the end he got $ n+1 $ parts. Now he wants to calculate their areas. Bob is lazy, so he asks you to do this task.

## 输入格式

The first line contains 3 integers $ W $ , $ H $ and $ n $ ( $ 1<=W,H,n<=100 $ ) — width of the bar, height of the bar and amount of breaks. Each of the following $ n $ lines contains four integers $ x_{i,1},y_{i,1},x_{i,2},y_{i,2} $ — coordinates of the endpoints of the $ i $ -th break ( $ 0<=x_{i,1}<=x_{i,2}<=W,0<=y_{i,1}<=y_{i,2}<=H $ , or $ x_{i,1}=x_{i,2} $ , or $ y_{i,1}=y_{i,2} $ ). Breaks are given in arbitrary order.

It is guaranteed that the set of breaks is correct, i.e. there is some order of the given breaks that each next break divides exactly one part of the bar into two non-empty parts.

## 输出格式

Output $ n+1 $ numbers — areas of the resulting parts in the increasing order.

## 样例 #1

### 输入

```
2 2 2
1 0 1 2
0 1 1 1

```

### 输出

```
1 1 2 
```

## 样例 #2

### 输入

```
2 2 3
1 0 1 2
0 1 1 1
1 1 2 1

```

### 输出

```
1 1 1 1 
```

## 样例 #3

### 输入

```
2 4 2
0 1 2 1
0 3 2 3

```

### 输出

```
2 2 4 
```



---

---
title: "Fox And Names"
layout: "post"
diff: 普及+/提高
pid: CF510C
tag: ['字符串', '图论建模', '拓扑排序']
---

# Fox And Names

## 题目描述

Fox Ciel is going to publish a paper on FOCS (Foxes Operated Computer Systems, pronounce: "Fox"). She heard a rumor: the authors list on the paper is always sorted in the lexicographical order.

After checking some examples, she found out that sometimes it wasn't true. On some papers authors' names weren't sorted in lexicographical order in normal sense. But it was always true that after some modification of the order of letters in alphabet, the order of authors becomes lexicographical!

She wants to know, if there exists an order of letters in Latin alphabet such that the names on the paper she is submitting are following in the lexicographical order. If so, you should find out any such order.

Lexicographical order is defined in following way. When we compare $ s $ and $ t $ , first we find the leftmost position with differing characters: $ s_{i}≠t_{i} $ . If there is no such position (i. e. $ s $ is a prefix of $ t $ or vice versa) the shortest string is less. Otherwise, we compare characters $ s_{i} $ and $ t_{i} $ according to their order in alphabet.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=100 $ ): number of names.

Each of the following $ n $ lines contain one string $ name_{i} $ ( $ 1<=|name_{i}|<=100 $ ), the $ i $ -th name. Each name contains only lowercase Latin letters. All names are different.

## 输出格式

If there exists such order of letters that the given names are sorted lexicographically, output any such order as a permutation of characters 'a'–'z' (i. e. first output the first letter of the modified alphabet, then the second, and so on).

Otherwise output a single word "Impossible" (without quotes).

## 样例 #1

### 输入

```
3
rivest
shamir
adleman

```

### 输出

```
bcdefghijklmnopqrsatuvwxyz

```

## 样例 #2

### 输入

```
10
tourist
petr
wjmzbmr
yeputons
vepifanov
scottwu
oooooooooooooooo
subscriber
rowdark
tankengineer

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
10
petr
egor
endagorion
feferivan
ilovetanyaromanova
kostka
dmitriyh
maratsnowbear
bredorjaguarturnik
cgyforever

```

### 输出

```
aghjlnopefikdmbcqrstuvwxyz

```

## 样例 #4

### 输入

```
7
car
care
careful
carefully
becarefuldontforgetsomething
otherwiseyouwillbehacked
goodluck

```

### 输出

```
acbdefhijklmnogpqrstuvwxyz

```



---

---
title: "Glass Carving"
layout: "post"
diff: 普及+/提高
pid: CF527C
tag: ['线段树', '排序']
---

# Glass Carving

## 题目描述

Leonid wants to become a glass carver (the person who creates beautiful artworks by cutting the glass). He already has a rectangular $ w $ mm $ × $ $ h $ mm sheet of glass, a diamond glass cutter and lots of enthusiasm. What he lacks is understanding of what to carve and how.

In order not to waste time, he decided to practice the technique of carving. To do this, he makes vertical and horizontal cuts through the entire sheet. This process results in making smaller rectangular fragments of glass. Leonid does not move the newly made glass fragments. In particular, a cut divides each fragment of glass that it goes through into smaller fragments.

After each cut Leonid tries to determine what area the largest of the currently available glass fragments has. Since there appear more and more fragments, this question takes him more and more time and distracts him from the fascinating process.

Leonid offers to divide the labor — he will cut glass, and you will calculate the area of the maximum fragment after each cut. Do you agree?

## 输入格式

The first line contains three integers $ w,h,n $ ( $ 2<=w,h<=200000 $ , $ 1<=n<=200000 $ ).

Next $ n $ lines contain the descriptions of the cuts. Each description has the form $ H y $ or $ V x $ . In the first case Leonid makes the horizontal cut at the distance $ y $ millimeters ( $ 1<=y<=h-1 $ ) from the lower edge of the original sheet of glass. In the second case Leonid makes a vertical cut at distance $ x $ ( $ 1<=x<=w-1 $ ) millimeters from the left edge of the original sheet of glass. It is guaranteed that Leonid won't make two identical cuts.

## 输出格式

After each cut print on a single line the area of the maximum available glass fragment in mm $ ^{2} $ .

## 说明/提示

Picture for the first sample test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527C/6468d2fd0321178fa316ccb774411f002769e9ee.png) Picture for the second sample test:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527C/40ba2772b27431a21bc874ab308dc348ec8365fd.png)

## 样例 #1

### 输入

```
4 3 4
H 2
V 2
V 3
V 1

```

### 输出

```
8
4
4
2

```

## 样例 #2

### 输入

```
7 6 5
H 4
V 3
V 5
H 2
V 1

```

### 输出

```
28
16
12
6
4

```



---

---
title: "Clique Problem"
layout: "post"
diff: 普及+/提高
pid: CF527D
tag: ['贪心', '排序', '构造']
---

# Clique Problem

## 题目描述

数轴上有 $n$ 个点，第 $i$ 个点的坐标为 $x_i$，权值为  $w_i$。两个点 $i,j$ 之间存在一条边当且仅当 $abs(x_i-x_j)\geq w_i+w_j$ 。 你需要求出这张图的最大团的点数。

团的定义：两两之间有边的顶点集合。

## 输入格式

第一行一个整数 $n$，接下来 $n$ 行每行两个整数 $x_i,w_i$ 。

## 输出格式

一行一个整数表示答案。 

感谢@Asougi_Kazuma 提供的翻译。

感谢@皎月半洒花 将翻译改成了正常人能看明白的翻译。

## 样例 #1

### 输入

```
4
2 3
3 1
6 1
0 2

```

### 输出

```
3

```



---

---
title: "Group Photo 2 (online mirror version)"
layout: "post"
diff: 普及+/提高
pid: CF529B
tag: ['贪心', '枚举', '排序']
---

# Group Photo 2 (online mirror version)

## 题目描述

Many years have passed, and $ n $ friends met at a party again. Technologies have leaped forward since the last meeting, cameras with timer appeared and now it is not obligatory for one of the friends to stand with a camera, and, thus, being absent on the photo.

Simply speaking, the process of photographing can be described as follows. Each friend occupies a rectangle of pixels on the photo: the $ i $ -th of them in a standing state occupies a $ w_{i} $ pixels wide and a $ h_{i} $ pixels high rectangle. But also, each person can lie down for the photo, and then he will occupy a $ h_{i} $ pixels wide and a $ w_{i} $ pixels high rectangle.

The total photo will have size $ W×H $ , where $ W $ is the total width of all the people rectangles, and $ H $ is the maximum of the heights. The friends want to determine what minimum area the group photo can they obtain if no more than $ n/2 $ of them can lie on the ground (it would be strange if more than $ n/2 $ gentlemen lie on the ground together, isn't it?..)

Help them to achieve this goal.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=1000 $ ) — the number of friends.

The next $ n $ lines have two integers $ w_{i},h_{i} $ ( $ 1<=w_{i},h_{i}<=1000 $ ) each, representing the size of the rectangle, corresponding to the $ i $ -th friend.

## 输出格式

Print a single integer equal to the minimum possible area of the photo containing all friends if no more than $ n/2 $ of them can lie on the ground.

## 样例 #1

### 输入

```
3
10 1
20 2
30 3

```

### 输出

```
180

```

## 样例 #2

### 输入

```
3
3 1
2 2
4 3

```

### 输出

```
21

```

## 样例 #3

### 输入

```
1
5 10

```

### 输出

```
50

```



---

---
title: "Points on Plane"
layout: "post"
diff: 普及+/提高
pid: CF576C
tag: ['莫队', '排序', '分块']
---

# Points on Plane

## 题目描述

给出 $N$ 个整点 $(x_i,y_i)$，求一个排列 $p$，使得 $\sum\limits_{i=2}^N (|x_{p_i} - x_{p_{i-1}}| + |y_{p_i} - y_{p_{i-1}}|) \leq 2.5 \times 10^9$。

## 输入格式

输入的第一行一个正整数 $N(1 \leq N \leq 10^6)$ 表示点的数量，接下来 $N$ 行每行两个非负整数 $x_i,y_i(0 \leq x_i,y_i \leq 10^6)$ 描述一个点。

## 输出格式

一行 $N$ 个数表示你给出的排列，每两个数之间用一个空格隔开。

## 样例 #1

### 输入

```
5
0 7
8 10
3 4
5 0
9 12

```

### 输出

```
4 3 1 2 5 

```



---

---
title: "Babaei and Birthday Cake"
layout: "post"
diff: 普及+/提高
pid: CF629D
tag: ['树状数组', '排序']
---

# Babaei and Birthday Cake

## 题目描述

Babaei 打算制作一个特殊的蛋糕。蛋糕由一些已知半径和高度的圆柱体组成，蛋糕的体积等于相应圆柱体的体积之和。

但是，还有一些额外的烹饪限制。编号为 $i$ 的蛋糕只能放在桌子上或编号为 $j$ 的蛋糕上，其中 $j\lt i$。 此外，为了给朋友们留下深刻印象，只有当蛋糕 $i$ 的体积超过蛋糕 $j$ 的体积时，Babaei 才会把蛋糕 $i$ 放在蛋糕 $j$ 上面。

Babaei 想要准备一个总体积最大的生日蛋糕，请你帮助他找到这个最大体积。

## 输入格式

输入的第一行包含一个整数 $n$（$1\le n\le10^5$），代表 Babaei 的蛋糕数量。

接下来 $n$ 行，每行两个整数 $r_i,h_i$（$1\le r_i,h_i\le10^4$），代表第 $i$ 个蛋糕的半径和高度。

## 输出格式

输出 Babaei 可以制作的蛋糕的最大体积。如果误差不超过 $10^{-6}$，则该答案将被视为正确。即：输出为 $a$，标准答案为 $b$，若 $\dfrac{\vert a-b\vert}{\max\left(1,b\right)}\le10^{-6}$，判为答案正确。

## 样例 #1

### 输入

```
2
100 30
40 10

```

### 输出

```
942477.796077000

```

## 样例 #2

### 输入

```
4
1 1
9 7
1 4
10 7

```

### 输出

```
3983.539484752

```



---

---
title: "Closing ceremony"
layout: "post"
diff: 普及+/提高
pid: CF720A
tag: ['排序', '队列']
---

# Closing ceremony

## 题目描述

The closing ceremony of Squanch Code Cup is held in the big hall with $ n×m $ seats, arranged in $ n $ rows, $ m $ seats in a row. Each seat has two coordinates $ (x,y) $ ( $ 1<=x<=n $ , $ 1<=y<=m $ ).

There are two queues of people waiting to enter the hall: $ k $ people are standing at $ (0,0) $ and $ n·m-k $ people are standing at $ (0,m+1) $ . Each person should have a ticket for a specific seat. If person $ p $ at $ (x,y) $ has ticket for seat $ (x_{p},y_{p}) $ then he should walk $ |x-x_{p}|+|y-y_{p}| $ to get to his seat.

Each person has a stamina — the maximum distance, that the person agrees to walk. You should find out if this is possible to distribute all $ n·m $ tickets in such a way that each person has enough stamina to get to their seat.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 1<=n·m<=10^{4} $ ) — the size of the hall.

The second line contains several integers. The first integer $ k $ ( $ 0<=k<=n·m $ ) — the number of people at $ (0,0) $ . The following $ k $ integers indicate stamina of each person there.

The third line also contains several integers. The first integer $ l $ ( $ l=n·m-k $ ) — the number of people at $ (0,m+1) $ . The following $ l $ integers indicate stamina of each person there.

The stamina of the person is a positive integer less that or equal to $ n+m $ .

## 输出格式

If it is possible to distribute tickets between people in the described manner print "YES", otherwise print "NO".

## 样例 #1

### 输入

```
2 2
3 3 3 2
1 3

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
2 2
3 2 3 3
1 2

```

### 输出

```
NO

```



---

---
title: "Crunching Numbers Just for You"
layout: "post"
diff: 普及+/提高
pid: CF784F
tag: ['排序', '优先队列', '队列']
---

# Crunching Numbers Just for You

## 题目描述

你正在为销售机票的网站开发一项新功能：按能够对价格进行票分类照片你已经提取了票价，所以只有最后一步要做...

## 输出格式

记住，这是一个非常重要的功能，你必须确保顾客欣赏它！

Translated by @zhrzhrzhr

## 样例 #1

### 输入

```
3 3 1 2

```

### 输出

```
1 2 3 

```



---

---
title: "Fire"
layout: "post"
diff: 普及+/提高
pid: CF864E
tag: ['贪心', '排序', '背包 DP']
---

# Fire

## 题目描述

某人的房子着火了，他想从大火中带走价值总和尽量多的物品，每次他只能带走一个，分别给出挽救某物品需要的时间 $t$，该物品开始燃烧的时间 $d$（从 $d$ 时间开始就不能再挽救该物品了），该物品的价值 $p$。

## 输入格式

第一行为物品总数 $n$（$1\leqslant n\leqslant100$）；

接下来 $n$ 行，每行有三个整数 $t_i$（$1\leqslant t_i\leqslant20$），$di$（$1\leqslant d_i\leqslant2000$），$pi$（$1\leqslant p_i\leqslant20$）。

## 输出格式

第一行为能带走的最大的价值总和；

第二行为能带走的物品的数量；

第三行为能带走的物品的编号（按带走顺序排序）。

Translated by 凌幽

## 样例 #1

### 输入

```
3
3 7 4
2 6 5
3 7 6

```

### 输出

```
11
2
2 3 

```

## 样例 #2

### 输入

```
2
5 6 1
3 3 5

```

### 输出

```
1
1
1 

```



---

---
title: "Coprocessor"
layout: "post"
diff: 普及+/提高
pid: CF909E
tag: ['排序', '拓扑排序', '队列']
---

# Coprocessor

## 题目描述

给你 $N$ 个任务，任务从 $0$ 开始标号，有些只能用主处理器处理，另外的任务只能用副处理器处理。其中存在 $M$ 个依赖关系，如果任务 $i$ 依赖于任务 $j$，那么称 $j$ 是 $i$ 的前继任务。

主处理器和副处理器都可以一次处理很多个任务。一个任务能被处理的条件为其所有的前继任务已经被执行过了，或者前继任务和自己同时被放进同一个处理器处理。


现在给出这些依赖关系和每个任务处理要用的处理器，求副处理器最少运行了几次。保证依赖关系是一张有向无环图。

## 输入格式

第一行输入两个非负整数 $N, M\ (1 \le N \le 10 ^ 5,\ 0 \le M \le 10 ^ 5)$。

接下来输入一行 $N$ 个整数 $E _ i\ (E _ i \in \{0, 1\})$，若 $E _ i = 0$ 则表示任务 $i$ 只能在主处理器上运行，否则其只能在副处理器上运行。

接下来 $M$ 行，每行两个非负整数 $T _ 1, T _ 2\ (0 \le T _ i < n,\ T _ 1 \ne T _ 2)$，表示任务 $T _ 1$ 依赖于任务 $T _ 2$。

## 输出格式

一行一个整数表示答案。

感谢 @Styx  提供的翻译。

## 样例 #1

### 输入

```
4 3
0 1 0 1
0 1
1 2
2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 3
1 1 1 0
0 1
0 2
3 0

```

### 输出

```
1

```



---

---
title: "Almost Acyclic Graph"
layout: "post"
diff: 普及+/提高
pid: CF915D
tag: ['枚举', '排序', '拓扑排序']
---

# Almost Acyclic Graph

## 题目描述

You are given a [directed graph](https://en.wikipedia.org/wiki/Directed_graph) consisting of $ n $ vertices and $ m $ edges (each edge is directed, so it can be traversed in only one direction). You are allowed to remove at most one edge from it.

Can you make this graph [acyclic](https://en.wikipedia.org/wiki/Directed_acyclic_graph) by removing at most one edge from it? A directed graph is called acyclic iff it doesn't contain any cycle (a non-empty path that starts and ends in the same vertex).

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=500 $ , $ 1<=m<=min(n(n-1),100000) $ ) — the number of vertices and the number of edges, respectively.

Then $ m $ lines follow. Each line contains two integers $ u $ and $ v $ denoting a directed edge going from vertex $ u $ to vertex $ v $ ( $ 1<=u,v<=n $ , $ u≠v $ ). Each ordered pair $ (u,v) $ is listed at most once (there is at most one directed edge from $ u $ to $ v $ ).

## 输出格式

If it is possible to make this graph acyclic by removing at most one edge, print YES. Otherwise, print NO.

## 说明/提示

In the first example you can remove edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png), and the graph becomes acyclic.

In the second example you have to remove at least two edges (for example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/7480c546ca7ee72615c3ded7d769355b1c864f93.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png)) in order to make the graph acyclic.

## 样例 #1

### 输入

```
3 4
1 2
2 3
3 2
3 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
5 6
1 2
2 3
3 2
3 1
2 1
4 5

```

### 输出

```
NO

```



---

---
title: "Divide by three, multiply by two"
layout: "post"
diff: 普及+/提高
pid: CF977D
tag: ['搜索', '拓扑排序', '哈希 hashing']
---

# Divide by three, multiply by two

## 题目描述

有一个长度为 $n$ 的数列 $a_i$，要求你将这个数列重排成一个排列 $p_i$，使得对于任意的 $p_i(1 \le i < n)$：



- $p_i \times 2 = p_{i+1}$，或者

- 当 $p_i$ 可以被 $3$ 整除时，$p_i \div 3 = p_{i+1}$。



保证答案存在。

## 输入格式

输入包含两行。



第一行一个整数 $n(2 \le n \le 100)$，表示数列中的元素个数。  

第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n (1 \le a_i \le 10^{18})$，描述这个数列。

## 输出格式

输出应包含 $n$ 个整数 $p_1, p_2, \dots, p_n$，表示你的答案。

## 说明/提示

在第一个样例中，一种可能的合法排列为 $[9,3,6,12,4,8]$。

## 样例 #1

### 输入

```
6
4 8 6 3 12 9

```

### 输出

```
9 3 6 12 4 8 

```

## 样例 #2

### 输入

```
4
42 28 84 126

```

### 输出

```
126 42 84 28 

```

## 样例 #3

### 输入

```
2
1000000000000000000 3000000000000000000

```

### 输出

```
3000000000000000000 1000000000000000000 

```



---

