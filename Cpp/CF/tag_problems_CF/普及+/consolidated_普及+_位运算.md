---
title: "Changing Array"
layout: "post"
diff: 普及+/提高
pid: CF1054D
tag: ['贪心', '前缀和', '位运算']
---

# Changing Array

## 题目描述

At a break Vanya came to the class and saw an array of $ n $ $ k $ -bit integers $ a_1, a_2, \ldots, a_n $ on the board. An integer $ x $ is called a $ k $ -bit integer if $ 0 \leq x \leq 2^k - 1 $ .

Of course, Vanya was not able to resist and started changing the numbers written on the board. To ensure that no one will note anything, Vanya allowed himself to make only one type of changes: choose an index of the array $ i $ ( $ 1 \leq i \leq n $ ) and replace the number $ a_i $ with the number $ \overline{a_i} $ . We define $ \overline{x} $ for a $ k $ -bit integer $ x $ as the $ k $ -bit integer such that all its $ k $ bits differ from the corresponding bits of $ x $ .

Vanya does not like the number $ 0 $ . Therefore, he likes such segments $ [l, r] $ ( $ 1 \leq l \leq r \leq n $ ) such that $ a_l \oplus a_{l+1} \oplus \ldots \oplus a_r \neq 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). Determine the maximum number of segments he likes Vanya can get applying zero or more operations described above.

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1 \leq n \leq 200\,000 $ , $ 1 \leq k \leq 30 $ ).

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq 2^k - 1 $ ), separated by spaces — the array of $ k $ -bit integers.

## 输出格式

Print one integer — the maximum possible number of segments with XOR not equal to $ 0 $ that can be obtained by making several (possibly $ 0 $ ) operations described in the statement.

## 说明/提示

In the first example if Vasya does not perform any operations, he gets an array that has $ 5 $ segments that Vanya likes. If he performs the operation with $ i = 2 $ , he gets an array $ [1, 0, 0] $ , because $ \overline{3} = 0 $ when $ k = 2 $ . This array has $ 3 $ segments that Vanya likes. Also, to get an array with $ 5 $ segments that Vanya likes, he can perform two operations with $ i = 3 $ and with $ i = 2 $ . He then gets an array $ [1, 0, 3] $ . It can be proven that he can't obtain $ 6 $ or more segments that he likes.

In the second example, to get $ 19 $ segments that Vanya likes, he can perform $ 4 $ operations with $ i = 3 $ , $ i = 4 $ , $ i = 5 $ , $ i = 6 $ and get an array $ [1, 4, 3, 0, 4, 3] $ .

## 样例 #1

### 输入

```
3 2
1 3 0

```

### 输出

```
5
```

## 样例 #2

### 输入

```
6 3
1 4 4 7 3 4

```

### 输出

```
19
```



---

---
title: "Manipulating History"
layout: "post"
diff: 普及+/提高
pid: CF1688C
tag: ['位运算']
---

# Manipulating History

## 题目描述

> 身为人类时，她的能力是将已有的历史全盘抹消；变身为白泽时，则能创造历史。——《东方求闻史纪》

上白泽慧音具有操作历史程度的能力。      
幻想乡的历史，一开始是一个长度为 $1$ 的字符串 $s$。为了修复由于八云紫造成的历史错乱，她需要完成 $n$ 次操作。对于第 $i$ 次操作：

- 她会选择字符串 $s$ 中的一个非空子串 $t_{2i-1}$；
- 她会将 $t_{2i-1}$ 替换为 $t_{2i}$，注意这两者的长度可能是不一样的。

注意，如果 $t_{2i-1}$ 在字符串 $s$ 中出现多次，也仅仅只替换其中恰好一个。    
例如，如果有一个字符串 $s=\texttt{marisa}$，$t_{2i-1}=\texttt a$，$t_{2i}=\texttt z$，那么在一次操作后，字符串 $s$ 将会变成 $\texttt{marisz}$ 或者 $\texttt{mzrisa}$。    
在经过 $n$ 次这样的操作之后，慧音得到了最后的字符串以及 $2n$ 个 $t_i$。正当慧音觉得她完成了这项任务的时候，八云紫又一次出现并且打乱了所有的 $t_i$。更糟糕的是，慧音忘记了幻想乡最一开始的历史。     
请你帮助慧音求出幻想乡最一开始的历史。

## 输入格式

第一行输入一个正整数 $t(1 \leq t \leq 10^3)$，表示输入数据组数。   
对于每一组数据，第一行输入一个正整数 $n(1 \leq n \leq 10^5)$，表示慧音的操作次数。    
接下来 $2n$ 行，每一行输入一个非空字符串 $t_i$，表示被打乱后的字符串序列 $t$。    
接下来输入一个字符串 $s$，表示最后的字符串。     
数据保证 $|s|+\sum |t_i| \leq 2 \times 10^5$。输入的字符串仅由小写英语字母组成。保证初始的字符串存在且唯一。

## 输出格式

对于每组数据，输出幻想乡最一开始的历史。

## 样例 #1

### 输入

```
2
2
a
ab
b
cd
acd
3
z
a
a
aa
yakumo
ran
yakumoran
```

### 输出

```
a
z
```



---

---
title: "Maximum AND"
layout: "post"
diff: 普及+/提高
pid: CF1721D
tag: ['贪心', '位运算']
---

# Maximum AND

## 题目描述

给出两个长度为 $n$ 的数组 $a,b$ ，规定 $f(a,b)$ 表示以下操作：

1. 创建一个长度为 $n$ 的 $c$ 数组，满足 $c_i=a_i \oplus b_i$ （此处的 $\oplus$ 表示[按位异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fr=aladdin)）。
2. 则 $f(a, b) = c_1\space\& c_2\space\& \cdots \& c_n$。

你可以将 $b$ 数组进行任意的排列（包括保留原始情况），试求出最大的 $f(a,b)$ 。

## 输入格式

第一行一个 $t\ (1\le t \le 10^4)$ ，表示数据组数。

对于每组数据：
	
第一行一个 $n\ (1 \le n \le 10^5)$ ，表示 $a,b$ 数组的长度。

第二行 $n$ 个自然数 $a_1,a_2......a_n(1 \le a_i \lt 2^{30})$

第三行 $n$ 个自然数 $b_1,b_2......b_n(1 \le b_i \lt 2^{30})$

数据保证单个数据测试点内，所有 $n$ 之和不超过 $10^5$.

## 输出格式

对于每一个测试点，一行一个正整数表示     $f(a,b)$ 的最大值。

## 样例 #1

### 输入

```
3
5
1 0 0 3 3
2 3 2 1 0
3
1 1 1
0 0 3
8
0 1 2 3 4 5 6 7
7 6 5 4 3 2 1 0
```

### 输出

```
2
0
7
```



---

---
title: "Bit Guessing Game"
layout: "post"
diff: 普及+/提高
pid: CF1780D
tag: ['位运算', '构造']
---

# Bit Guessing Game

## 题目描述

这是一道交互题。

Kira 和 Hayato 正在玩一种猜数游戏，Kira 想，Hayato 猜。

对于每一轮游戏，设 Kira 想的数为 $n$。初始时，Kira 会给出 $cnt$，表示 $n$ 的二进制中 $1$ 的个数。Hayato 只能进行以下两种操作：

1. `- x`：修改操作。Kira 会将 $n$ 减去 $x$（注意此处 $n$ 会被修改），并给出此时的 $cnt$。特别地，若 $x > n$，则 Kira 直接获胜。
2. `! x`：查询操作。Kira 会将 $x$ 与最初的 $n$ 对比，若二者相同则 Hayato 获胜，反之 Kira 获胜，这轮游戏立即结束。

他们一共会进行 $t$ 轮游戏，你需要帮助 Hayato 在每一轮中获胜。同时，Kira 并不是一个很有耐心的人，因此你进行操作 1 的次数不能超过 $30$。

注意样例中的空行只是为了显示更清晰，不会出现在实际评测中。

## 输入格式

第一行包含一个整数 $t(1 \le t \le 500)$，表示有 $t$ 组测试用例。

对于每组测试用例，首行均为一个整数 $cnt$，表示 $n$ 的二进制中 $1$ 的个数。

保证 $1 \le n \le 10^9$。

## 输出格式

对于每个操作 1，输出单独的一行 `- x`；相应地，对于每个操作 2，输出单独的一行 `! n`。

每个操作 1 完成后，交互库会输出一行一个整数 $cnt$，表示修改后的 $n$ 的二进制中 $1$ 的个数。

再次强调，每一轮 Hayato 进行操作 1 的次数不能超过 $30$。

确定初始时 $n$ 的值后，可进行操作 2 验证答案。

注意：每次输出任意操作后需要刷新输出。这里给出部分语言刷新输出的代码：

|  语言  |                代码                |
| :----: | :--------------------------------: |
|  C++   | `fflush(stdout)` 或 `cout.flush()` |
|  Java  |        `System.out.flush()`        |
| Pascal |          `flush(output)`           |
| Python |          `stdout.flush()`          |

## 样例 #1

### 输入

```
3

1

0

1

1

0

2

1

0
```

### 输出

```
- 1

! 1

- 1

- 1

! 2

- 2

- 1

! 3
```



---

---
title: "Tree XOR"
layout: "post"
diff: 普及+/提高
pid: CF1882D
tag: ['贪心', '树形 DP', '位运算']
---

# Tree XOR

## 题目描述

You are given a tree with $ n $ vertices labeled from $ 1 $ to $ n $ . An integer $ a_{i} $ is written on vertex $ i $ for $ i = 1, 2, \ldots, n $ . You want to make all $ a_{i} $ equal by performing some (possibly, zero) spells.

Suppose you root the tree at some vertex. On each spell, you can select any vertex $ v $ and any non-negative integer $ c $ . Then for all vertices $ i $ in the subtree $ ^{\dagger} $ of $ v $ , replace $ a_{i} $ with $ a_{i} \oplus c $ . The cost of this spell is $ s \cdot c $ , where $ s $ is the number of vertices in the subtree. Here $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Let $ m_r $ be the minimum possible total cost required to make all $ a_i $ equal, if vertex $ r $ is chosen as the root of the tree. Find $ m_{1}, m_{2}, \ldots, m_{n} $ .

 $ ^{\dagger} $ Suppose vertex $ r $ is chosen as the root of the tree. Then vertex $ i $ belongs to the subtree of $ v $ if the simple path from $ i $ to $ r $ contains $ v $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^{4} $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^{5} $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i < 2^{20} $ ).

Each of the next $ n-1 $ lines contains two integers $ u $ and $ v $ ( $ 1 \le u, v \le n $ ), denoting that there is an edge connecting two vertices $ u $ and $ v $ .

It is guaranteed that the given edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^{5} $ .

## 输出格式

For each test case, print $ m_1, m_2, \ldots, m_n $ on a new line.

## 说明/提示

In the first test case, to find $ m_1 $ we root the tree at vertex $ 1 $ .

1. In the first spell, choose $ v=2 $ and $ c=1 $ . After performing the spell, $ a $ will become $ [3, 3, 0, 1] $ . The cost of this spell is $ 3 $ .
2. In the second spell, choose $ v=3 $ and $ c=3 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 1] $ . The cost of this spell is $ 3 $ .
3. In the third spell, choose $ v=4 $ and $ c=2 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 3] $ . The cost of this spell is $ 2 $ .

Now all the values in array $ a $ are equal, and the total cost is $ 3 + 3 + 2 = 8 $ .

The values $ m_2 $ , $ m_3 $ , $ m_4 $ can be found analogously.

In the second test case, the goal is already achieved because there is only one vertex.

## 样例 #1

### 输入

```
2
4
3 2 1 0
1 2
2 3
2 4
1
100
```

### 输出

```
8 6 12 10 
0
```



---

---
title: "Birthday Gift"
layout: "post"
diff: 普及+/提高
pid: CF1946D
tag: ['位运算']
---

# Birthday Gift

## 题目描述

Yarik's birthday is coming soon, and Mark decided to give him an array $ a $ of length $ n $ .

Mark knows that Yarik loves bitwise operations very much, and he also has a favorite number $ x $ , so Mark wants to find the maximum number $ k $ such that it is possible to select pairs of numbers \[ $ l_1, r_1 $ \], \[ $ l_2, r_2 $ \], $ \ldots $ \[ $ l_k, r_k $ \], such that:

- $ l_1 = 1 $ .
- $ r_k = n $ .
- $ l_i \le r_i $ for all $ i $ from $ 1 $ to $ k $ .
- $ r_i + 1 = l_{i + 1} $ for all $ i $ from $ 1 $ to $ k - 1 $ .
- $ (a_{l_1} \oplus a_{l_1 + 1} \oplus \ldots \oplus a_{r_1}) | (a_{l_2} \oplus a_{l_2 + 1} \oplus \ldots \oplus a_{r_2}) | \ldots | (a_{l_k} \oplus a_{l_k + 1} \oplus \ldots \oplus a_{r_k}) \le x $ , where $ \oplus $ denotes the operation of [bitwise XOR](https://en.wikipedia.org/wiki/Exclusive_or), and $ | $ denotes the operation of [bitwise OR](https://en.wikipedia.org/wiki/Logical_disjunction).

If such $ k $ does not exist, then output $ -1 $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The following lines contain the descriptions of the test cases.

The first line of each test case contains two integers $ n $ and $ x $ ( $ 1 \le n \le 10^5, 0 \le x < 2^{30} $ ) — the length of the array $ a $ and the number $ x $ respectively.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i < 2^{30} $ ) — the array $ a $ itself.

It is guaranteed that the sum of the values of $ n $ across all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer on a separate line — the maximum suitable number $ k $ , and $ -1 $ if such $ k $ does not exist.

## 说明/提示

In the first test case, you can take $ k $ equal to $ 2 $ and choose two segments \[ $ 1, 1 $ \] and \[ $ 2, 3 $ \], $ (1) | (2 \oplus 3) = 1 $ . It can be shown that $ 2 $ is the maximum possible answer.

In the second test case, the segments \[ $ 1, 1 $ \] and \[ $ 2, 2 $ \] are suitable, $ (1) | (1) = 1 $ . It is not possible to make more segments.

In the third test case, it is not possible to choose $ 2 $ segments, as $ (1) | (3) = 3 > 2 $ , so the optimal answer is $ 1 $ .

## 样例 #1

### 输入

```
8
3 1
1 2 3
2 2
1 1
2 2
1 3
2 3
0 0
3 2
0 0 1
4 2
1 3 3 7
2 2
2 3
5 0
0 1 2 2 1
```

### 输出

```
2
2
1
2
3
-1
1
2
```



---

---
title: "A BIT of an Inequality"
layout: "post"
diff: 普及+/提高
pid: CF1957D
tag: ['前缀和', '位运算']
---

# A BIT of an Inequality

## 题目描述

给定序列 $a_n$，求满足以下条件的三元组 $(x,y,z)$ 的数量：

* $1\le x\le y\le z\le n$.

* $f(x,y)\oplus f(y,z)>f(x,z)$.

我们规定 $f(l,r)$ 表示 $a_l\oplus a_{l+1}\oplus\dots\oplus a_{r-1}\oplus a_{r}$，$\oplus$ 表示[异或和](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fr=ge_ala)。

## 输入格式

第一行一个整数 $t$，表示数据组数。

接下来对于每组数据，第一行一个整数 $n$。

接下来 $n$ 个整数，表示 $a_i$。

## 输出格式

共 $t$ 行，每行一个整数，表示答案。

## 说明/提示

对于全部数据，满足 $1\le t\le10^4$，$1\le n\le10^5$，$1\le a_i\le10^9$，$\sum n\le10^5$。

## 样例 #1

### 输入

```
3
3
6 2 4
1
3
5
7 3 7 2 1
```

### 输出

```
4
0
16
```



---

---
title: "Equal XOR Segments"
layout: "post"
diff: 普及+/提高
pid: CF1968F
tag: ['贪心', '位运算']
---

# Equal XOR Segments

## 题目描述

Let us call an array $ x_1,\dots,x_m $ interesting if it is possible to divide the array into $ k>1 $ parts so that [bitwise XOR](http://tiny.cc/xor_wiki_eng) of values from each part are equal.

More formally, you must split array $ x $ into $ k $ consecutive segments, each element of $ x $ must belong to exactly $ 1 $ segment. Let $ y_1,\dots,y_k $ be the XOR of elements from each part respectively. Then $ y_1=y_2=\dots=y_k $ must be fulfilled.

For example, if $ x = [1, 1, 2, 3, 0] $ , you can split it as follows: $ [\color{blue}1], [\color{green}1], [\color{red}2, \color{red}3, \color{red}0] $ . Indeed $ \color{blue}1=\color{green}1=\color{red}2 \oplus \color{red}3\oplus \color{red}0 $ .

You are given an array $ a_1,\dots,a_n $ . Your task is to answer $ q $ queries:

- For fixed $ l $ , $ r $ , determine whether the subarray $ a_l,a_{l+1},\dots,a_r $ is interesting.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of elements in the array and the number of queries respectively.

The next line contains $ n $ integers $ a_1,\dots,a_n $ ( $ 0 \le a_i < 2^{30} $ ) — elements of the array.

Each of the next $ q $ lines contains two integers $ l $ and $ r $ ( $ 1 \le l < r \le n $ ) describing the query.

It is guaranteed that the sum of $ n $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

It is guaranteed that the sum of $ q $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query, output "YES" if the subarray is interesting and "NO" otherwise.

You can output "Yes" and "No" in any case (for example, the strings "yES", "yes", and "Yes" will be recognized as correct answers).

## 说明/提示

Explanation for the first test case:

The first query is described in the statement.

In the second query, we should divide $ [1,2,3] $ . A possible division is $ [1,2],[3] $ , since $ 1\oplus 2=3 $ .

It can be shown that for queries $ 3,4,5 $ , the subarrays are not interesting.

## 样例 #1

### 输入

```
4
5 5
1 1 2 3 0
1 5
2 4
3 5
1 3
3 4
5 5
1 2 3 4 5
1 5
2 4
3 5
1 3
2 3
7 4
12 9 10 9 10 11 9
1 5
1 7
2 6
2 7
11 4
0 0 1 0 0 1 0 1 1 0 1
1 2
2 5
6 9
7 11
```

### 输出

```
YES
YES
NO
NO
NO

YES
NO
NO
YES
NO

NO
NO
NO
NO

YES
NO
YES
YES
```



---

---
title: "Prime XOR Coloring"
layout: "post"
diff: 普及+/提高
pid: CF1991D
tag: ['数论', '位运算', 'Ad-hoc']
---

# Prime XOR Coloring

## 题目描述

You are given an undirected graph with $ n $ vertices, numbered from $ 1 $ to $ n $ . There is an edge between vertices $ u $ and $ v $ if and only if $ u \oplus v $ is a [prime number](https://en.wikipedia.org/wiki/Prime_number), where $ \oplus $ denotes the [bitwise XOR operator](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Color all vertices of the graph using the minimum number of colors, such that no two vertices directly connected by an edge have the same color.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ). The description of test cases follows.

The only line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the graph.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output two lines.

The first line should contain a single integer $ k $ ( $ 1 \le k \le n $ ) — the minimum number of colors required.

The second line should contain $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 1 \le c_i \le k $ ) — the color of each vertex.

If there are multiple solutions, output any of them.

## 说明/提示

In the first test case, the minimum number of colors is $ 1 $ , because there is only one vertex.

In the second test case, the minimum number of colors is $ 2 $ , because there is an edge connecting $ 1 $ and $ 2 $ ( $ 1 \oplus 2 = 3 $ , which is a prime number).

In the third test case, the minimum number of colors is still $ 2 $ , because $ 2 $ and $ 3 $ can be colored the same since there is no edge between $ 2 $ and $ 3 $ ( $ 2 \oplus 3 = 1 $ , which is not a prime number).

In the fourth test case, it can be shown that the minimum number of colors is $ 3 $ .

In the fifth test case, it can be shown that the minimum number of colors is $ 3 $ .

In the sixth test case, it can be shown that the minimum number of colors is $ 4 $ .

## 样例 #1

### 输入

```
6
1
2
3
4
5
6
```

### 输出

```
1
1
2
1 2
2
1 2 2
3
1 2 2 3
3
1 2 2 3 3
4
1 2 2 3 3 4
```



---

---
title: "Wooden Game"
layout: "post"
diff: 普及+/提高
pid: CF1994E
tag: ['贪心', '位运算']
---

# Wooden Game

## 题目描述

### 题目大意

给定一个有根树森林 $K=\left\{T_1,T_2,\dots,T_k\right\}$。Timofey 可以移除森林中任意树的子树，然后将其加入森林。

求 Timofey 通过任意次操作，所能得到的 
$$
\bigvee_{i=1}^{|K|}\left|T_i\right|
$$
的最大值，其中 $\bigvee$ 表示按位或。

## 输入格式

输入数据的第一行包括一个整数 $t\left(1\le t\le10^4\right)$，表示测试用例的组数。

对于每个测试用例：

第一行包括一个整数$k\left(1\le k\le10^6\right)$，表示初始状态下森林中树的数目。

接下来 $2k$ 行依次描述了 $k$ 颗树。对于每颗树：

- 第一行包括一个整数 $n\left(1\le n\le10^6\right)$，表示树中结点的数目。
- 第二行包括 $n-1$ 个整数 $p_2,p_3,\dots,p_n$ $\left(1\le p_i<i\right)$。其中，$p_i$ 表示结点 $i$ 的父亲。
- 特别地，当  $n=1$ 时，第二行为空行。

输入数据保证 $\sum n,\sum k\le10^6$

## 输出格式

对于每个测试用例，输出一行一个整数，表示能得到的最大值。

## 样例 #1

### 输入

```
3
1
1


2
4
1 2 2
6
1 1 3 1 3
1
10
1 2 2 1 1 5 7 6 4
```

### 输出

```
1
7
10
```



---

---
title: "XORificator 3000"
layout: "post"
diff: 普及+/提高
pid: CF2036F
tag: ['位运算']
---

# XORificator 3000

## 题目描述

### 题面描述

多次询问，每次给定 $l,r,i,k$，求 $[l,r]$ 内所有满足 $x \not\equiv  k\pmod{2^i}$ 的 $x$ 的异或和。

## 输入格式

第一行一个整数 $t$，表示数据组数。

接下来 $t$ 组数据，每组数据一行四个整数表示 $l,r,i,k$。

## 输出格式

对于每组数据输出一行一个整数表示答案。

## 说明/提示

保证 $1\le t\le 10^4$，$1\le l\le r\le 10^{18}$，$0\le i\le 30$，$0\le k < 2^i$。

## 样例 #1

### 输入

```
6
1 3 1 0
2 28 3 7
15 43 1 0
57 2007 1 0
1010 1993 2 2
1 1000000000 30 1543
```

### 输出

```
2
2
13
0
4
1000000519
```



---

---
title: "Library of Magic"
layout: "post"
diff: 普及+/提高
pid: CF2036G
tag: ['二分', '位运算']
---

# Library of Magic

## 题目描述

This is an interactive problem.

The Department of Supernatural Phenomena at the Oxenfurt Academy has opened the Library of Magic, which contains the works of the greatest sorcerers of Redania — $ n $ ( $ 3 \leq n \leq 10^{18} $ ) types of books, numbered from $ 1 $ to $ n $ . Each book's type number is indicated on its spine. Moreover, each type of book is stored in the library in exactly two copies! And you have been appointed as the librarian.

One night, you wake up to a strange noise and see a creature leaving the building through a window. Three thick tomes of different colors were sticking out of the mysterious thief's backpack. Before you start searching for them, you decide to compute the numbers $ a $ , $ b $ , and $ c $ written on the spines of these books. All three numbers are distinct.

So, you have an unordered set of tomes, which includes one tome with each of the pairwise distinct numbers $ a $ , $ b $ , and $ c $ , and two tomes for all numbers from $ 1 $ to $ n $ , except for $ a $ , $ b $ , and $ c $ . You want to find these values $ a $ , $ b $ , and $ c $ .

Since you are not working in a simple library, but in the Library of Magic, you can only use one spell in the form of a query to check the presence of books in their place:

- "xor l r" — Bitwise XOR query with parameters $ l $ and $ r $ . Let $ k $ be the number of such tomes in the library whose numbers are greater than or equal to $ l $ and less than or equal to $ r $ . You will receive the result of the computation $ v_1 \oplus v_2 \oplus ... \oplus v_k $ , where $ v_1 ... v_k $ are the numbers on the spines of these tomes, and $ \oplus $ denotes the operation of [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng).

Since your magical abilities as a librarian are severely limited, you can make no more than $ 150 $ queries.

## 输入格式

The first line of input contains an integer $ t $ ( $ 1 \le t \le 300 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 3 \leq n \leq 10^{18} $ ) — the number of types of tomes.

## 输出格式

The interaction for each test case begins with reading the integer $ n $ .

Then you can make up to $ 150 $ queries.

To make a query, output a string in the format "xor l r" (without quotes) ( $ 1 \leq l \leq r \leq n $ ). After each query, read an integer — the answer to your query.

To report the answer, output a string in the format "ans a b c" (without quotes), where $ a $ , $ b $ , and $ c $ are the numbers you found as the answer to the problem. You can output them in any order.

The interactor is not adaptive, which means that the answer is known before the participant makes queries and does not depend on the queries made by the participant.

After making $ 150 $ queries, the answer to any other query will be $ -1 $ . Upon receiving such an answer, terminate the program to receive a verdict of "WA" (Wrong answer).

After outputting a query, do not forget to output a newline and flush the output buffer. Otherwise, you will receive a verdict of "IL" (Idleness limit exceeded). To flush the buffer, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- refer to the documentation for other languages.

Hacks

To make a hack, use the following format.

The first line should contain a single integer $ t $ ( $ 1 \leq t \leq 300 $ ) — the number of test cases.

The only line of each test case should contain four integers $ n $ , $ a $ , $ b $ , and $ c $ ( $ 3 \leq n \leq 10^{18} $ , $ 1 \le a, b, c \le n $ ) — the number of books in the library and the numbers of the stolen tomes. The numbers $ a $ , $ b $ , and $ c $ must be distinct.

## 说明/提示

In the first test case, the books in the library after the theft look like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2036G/fa5245a6b21b822e029654d6d78459d7dcab42ae.png)

Now consider the answers to the queries:

- For the query "xor 1 1", you receive the result $ 1 \oplus 1 = 0 $ . Two tomes satisfy the condition specified in the query — both with the number $ 1 $ .
- For the query "xor 2 2", you receive the result $ 2 $ , as only one tome satisfies the specified condition.
- For the query "xor 3 3", you receive the result $ 3 $ .
- For the query "xor 4 6", you receive the result $ 4 \oplus 6 \oplus 4 \oplus 5 \oplus 6 = 5 $ .

In the second test case, there are only $ 3 $ types of books, and it is easy to guess that the missing ones have the numbers $ 1 $ , $ 2 $ , and $ 3 $ .

## 样例 #1

### 输入

```
2
6

0

2

3

5

3
```

### 输出

```
xor 1 1

xor 2 2

xor 3 3

xor 4 6

ans 2 3 5

ans 1 2 3
```



---

---
title: "Shohag Loves XOR (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF2039C2
tag: ['数学', '数论', '枚举', '位运算']
---

# Shohag Loves XOR (Hard Version)

## 题目描述

This is the hard version of the problem. The differences between the two versions are highlighted in bold. You can only make hacks if both versions of the problem are solved.

Shohag has two integers $ x $ and $ m $ . Help him count the number of integers $ 1 \le y \le m $ such that $ x \oplus y $ is divisible $ ^{\text{∗}} $ by either $ x $ , $ y $ , or both. Here $ \oplus $ is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operator.

 $ ^{\text{∗}} $ The number $ a $ is divisible by the number $ b $ if there exists an integer $ c $ such that $ a = b \cdot c $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line of each test case contains two space-separated integers $ x $ and $ m $ ( $ 1 \le x \le 10^6 $ , $ 1 \le m \le 10^{18} $ ).

It is guaranteed that the sum of $ x $ over all test cases does not exceed $ 10^7 $ .

## 输出格式

For each test case, print a single integer — the number of suitable $ y $ .

## 说明/提示

In the first test case, for $ x = 7 $ , there are $ 3 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 10 $ , and they are $ 1 $ , $ 7 $ , and $ 9 $ .

- $ y = 1 $ is valid because $ x \oplus y = 7 \oplus 1 = 6 $ and $ 6 $ is divisible by $ y = 1 $ .
- $ y = 7 $ is valid because $ x \oplus y = 7 \oplus 7 = 0 $ and $ 0 $ is divisible by both $ x = 7 $ and $ y = 7 $ .
- $ y = 9 $ is valid because $ x \oplus y = 7 \oplus 9 = 14 $ and $ 14 $ is divisible by $ x = 7 $ .

## 样例 #1

### 输入

```
5
7 10
2 3
6 4
1 6
4 1
```

### 输出

```
3
2
2
6
1
```



---

---
title: "Ordered Permutations"
layout: "post"
diff: 普及+/提高
pid: CF2040C
tag: ['数学', '贪心', '位运算']
---

# Ordered Permutations

## 题目描述

给定一个长度为 $n$ 的整数排列 $p_1, p_2, \ldots, p_n$，其中包含从 $1$ 到 $n$ 的所有整数。我们定义一个如下的和式：

$$S(p) = \sum_{1 \le l \le r \le n} \min(p_l, p_{l+1}, \ldots, p_r)$$

我们希望找出所有能使 $S(p)$ 最大的排列，并从中按字典序选择第 $k$ 个。如果这样的排列数量少于 $k$，则输出 -1。

**解释说明：**
- 长度为 $n$ 的排列是一个由 $n$ 个不同的整数组成的序列，这些整数来源于 $1$ 到 $n$ 的一组数字。例如，$[2, 3, 1, 5, 4]$ 是一个符合要求的排列，而 $[1, 2, 2]$ 因为有重复数字 $2$ 而不符合，$[1, 3, 4]$ 也不符合要求，因为它包含了不在 $1$ 到 $n$ 范围内的数 $4$（$n = 3$）。
- 示例计算： 
  - 对于排列 $[1, 2, 3]$，$S(p)$ 计算为 $\min(1) + \min(1, 2) + \min(1, 2, 3) + \min(2) + \min(2, 3) + \min(3) = 1 + 1 + 1 + 2 + 2 + 3 = 10$。
  - 对于排列 $[2, 4, 1, 3]$，$S(p)$ 计算为 $\min(2) + \min(2, 4) + \min(2, 4, 1) + \min(2, 4, 1, 3) + \min(4) + \min(4, 1) + \min(4, 1, 3) + \min(1) + \min(1, 3) + \min(3) = 2 + 2 + 1 + 1 + 4 + 1 + 1 + 1 + 1 + 3 = 17$。
- 字典序小于：数组 $a$ 比数组 $b$ 在字典序上小的条件是：
  1. $a$ 是 $b$ 的一个前缀，且 $a \ne b$；
  2. 或者在第一个不同的位置上，$a$ 的元素小于 $b$ 的对应元素。

## 输入格式

第一行输入一个整数 $t$，表示测试用例的数量 ($1 \le t \le 10^4$)。之后的每一个测试用例由一行组成，包含两个整数 $n$ 和 $k$，分别表示排列的长度和需要找出的第 $k$ 个排列的索引 ($1 \le n \le 2 \cdot 10^5$; $1 \le k \le 10^{12}$)。

保证所有测试用例中的 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每一个测试用例：
- 如果符合条件的排列少于 $k$ 个，则输出 `-1`。
- 否则，输出第 $k$ 个符合条件的排列。

## 说明/提示

以下是所有长度为 3 的排列及其对应的 $S(p)$ 值（按字典序排序）：

| 排列 | $S(p)$ 的值 |
|------|-------------|
| $[1, 2, 3]$ | $10$ |
| $[1, 3, 2]$ | $10$ |
| $[2, 1, 3]$ | $9$ |
| $[2, 3, 1]$ | $10$ |
| $[3, 1, 2]$ | $9$ |
| $[3, 2, 1]$ | $10$ |

在第一个测试用例中，需输出长度为 3 的第 2 个符合条件的排列，看表格可以知道是 $[1, 3, 2]$。

在第二个测试用例中，需输出长度为 3 的第 3 个符合条件的排列，对应的是 $[2, 3, 1]$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6
3 2
3 3
4 11
4 6
6 39
7 34
```

### 输出

```
1 3 2 
2 3 1 
-1
2 4 3 1 
-1
2 3 4 5 7 6 1
```



---

---
title: "Trip to the Olympiad"
layout: "post"
diff: 普及+/提高
pid: CF2057C
tag: ['贪心', '位运算']
---

# Trip to the Olympiad

## 题目描述

在新的一年中，将会有很多团队奥林匹克竞赛，因此「T-generation」的老师们需要选择三名学生组成一个团队来参加这些比赛。无论是哪三名学生，他们都能在任何团体竞赛中表现出色。然而，赢得比赛仅仅是成功的一部分；首先，他们需要获得参赛资格……

每位学生都有一个用整数表示的独立性等级。「T-generation」中，每个独立性等级从 $l$ 到 $r$（包含 $l$ 和 $r$）的数值都有且只有一名学生。对于一个由独立性等级为 $a$、$b$ 和 $c$ 的学生组成的三人团队，他们的团队独立性值定义为 $(a \oplus b) + (b \oplus c) + (a \oplus c)$，其中 $\oplus$ 表示按位异或运算。

你的任务是选择一个三人团队，使得他们的团队独立性值最大化。

## 输入格式

输入包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的数量。接下来的每行描述一个测试用例。

每个测试用例的首行包含两个整数 $l$ 和 $r$（$0 \le l, r < 2^{30}$，$r - l > 1$），表示学生独立性等级的最小值和最大值。

## 输出格式

对于每个测试用例，输出三个不同的整数 $a, b, c$，满足 $l \le a, b, c \le r$，且使表达式 $(a \oplus b) + (b \oplus c) + (a \oplus c)$ 的值最大。在存在多个解的情况下，可以输出任意一个满足条件的三元组。

## 说明/提示

在第一个测试用例中，可以选择的唯一个合适的三元组（忽略顺序）是 $(0, 1, 2)$。

在第二个测试用例中，其中一个合适的三元组是 $(8, 7, 1)$，因为 $(8 \oplus 7) + (7 \oplus 1) + (8 \oplus 1) = 15 + 6 + 9 = 30$。经过证明，$30$ 是在 $0 \le a, b, c \le 8$ 时，$(a \oplus b) + (b \oplus c) + (a \oplus c)$ 的最大可能值。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
8
0 2
0 8
1 3
6 22
128 137
69 98
115 127
0 1073741823
```

### 输出

```
1 2 0
8 7 1
2 1 3
7 16 11
134 132 137
98 85 76
123 121 118
965321865 375544086 12551794
```



---

---
title: "Infinite Sequence (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF2071D1
tag: ['位运算']
---

# Infinite Sequence (Easy Version)

## 题目描述

这是该问题的简单版本。不同版本的区别在于此版本中 $l = r$。仅当您解决了该问题的所有版本时才能进行 hack。

给定一个正整数 $n$ 和一个无限二进制序列 $a$ 的前 $n$ 项，该序列定义如下：

- 对于 $m > n$，$a_m = a_1 \oplus a_2 \oplus \ldots \oplus a_{\lfloor \frac{m}{2} \rfloor}$ $^{\text{∗}}$。

你的任务是计算给定区间 $[l, r]$ 内元素的和：$a_l + a_{l + 1} + \ldots + a_r$。

$^{\text{∗}}$ $\oplus$ 表示[按位异或操作](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各个测试用例的描述。

每个测试用例的第一行包含三个整数 $n$、$l$ 和 $r$（$1 \le n \le 2 \cdot 10^5$，$1 \le l = r \le 10^{18}$）。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$\color{red}{a_i \in \{0, 1\}}$）——序列 $a$ 的前 $n$ 项。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——给定区间内元素的和。

## 说明/提示

第一个测试用例中，序列 $a$ 为：

$$[\underline{\color{red}{1}}, 1, 1, 0, 0, 1, 1, 1, 1, 1, \ldots]$$ 

其中 $l = 1$，$r = 1$。区间 $[1, 1]$ 的元素和为 $a_1 = 1$。

第二个测试用例中，序列 $a$ 为：

$$ [\text{\color{red}{1}}, \text{\color{red}{0}}, \underline{1}, 1, 1, 0, 0, 1, 1, 0, \ldots] $$

其中 $l = 3$，$r = 3$。区间 $[3, 3]$ 的元素和为 $a_3 = 1$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
9
1 1 1
1
2 3 3
1 0
3 5 5
1 1 1
1 234 234
0
5 1111 1111
1 0 1 0 1
1 1000000000000000000 1000000000000000000
1
10 87 87
0 1 1 1 1 1 1 1 0 0
12 69 69
1 0 0 0 0 1 0 1 0 1 1 0
13 46 46
0 1 0 1 1 1 1 1 1 0 1 1 1
```

### 输出

```
1
1
0
0
1
0
1
0
0
```



---

---
title: "Goodbye, Banker Life"
layout: "post"
diff: 普及+/提高
pid: CF2072F
tag: ['排列组合', '位运算']
---

# Goodbye, Banker Life

## 题目描述

怪物正在逼近城市，为了保护它，Akito 必须在城市周围创建一个防护场。众所周知，防护场有不同的等级。Akito 选择了等级为 $n$ 的防护场。为了构建这个防护场，需要一个特殊咒语，即伟大魔法三角（表示为二维数组 $T$）的第 $n$ 行。我们将这个数组称为 $T$。

魔法三角的定义如下：

- 第 $i$ 行包含 $i$ 个整数。
- 第一行唯一的整数是 $k$。
- 设第 $i$ 行第 $j$ 个元素为 $T_{i,j}$，则：

$$
T_{i,j} = \begin{cases} 
T_{i-1,j-1} \oplus T_{i-1,j}, & \text{if } 1 < j < i \\ 
T_{i-1,j}, & \text{if } j = 1 \\ 
T_{i-1,j-1}, & \text{if } j = i 
\end{cases}
$$

其中 $a \oplus b$ 表示整数 $a$ 和 $b$ 的按位异或运算。

请帮助 Akito 在怪物抵达城市前找到这个无限魔法三角的第 $n$ 行整数。

## 输入格式

第一行包含整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的唯一一行包含两个整数 $n$ 和 $k$（$1 \le n \le 10^6$，$1 \le k < 2^{31}$）——分别表示 Akito 需要的行索引和伟大魔法三角第一行的整数。

保证所有测试用例的 $n$ 之和不超过 $10^6$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数——伟大魔法三角第 $n$ 行的元素。

## 说明/提示

在第一个示例中，根据定义，伟大魔法三角的第一行为 $[5]$。

在第二个示例中，$T_{2,1} = T_{1,1} = 10$ 且 $T_{2,2} = T_{1,1} = 10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
1 5
2 10
3 16
9 1
1 52
```

### 输出

```
5
10 10
16 0 16
1 0 0 0 0 0 0 0 1
52
```



---

---
title: "Finding OR Sum"
layout: "post"
diff: 普及+/提高
pid: CF2077B
tag: ['位运算', '构造']
---

# Finding OR Sum

## 题目描述

[ALTER EGO - Yuta Imai vs Qlarabelle](https://www.youtube.com/watch?v=LJEqM7pvClA)

这是一道交互题。

存在两个隐藏的非负整数 $x$ 和 $y$（$0 \leq x, y < 2^{30}$）。你最多可以提出 2 次以下形式的询问：

- 选择一个非负整数 $n$（$0 \leq n < 2^{30}$）。评测系统将返回 $(n \mathbin{|} x) + (n \mathbin{|} y)$ 的值，其中 $|$ 表示[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。

此后，评测系统将给出另一个非负整数 $m$（$0 \leq m < 2^{30}$）。你必须正确回答 $(m \mathbin{|} x) + (m \mathbin{|} y)$ 的值。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

## 输出格式

已选择两个隐藏整数 $x$ 和 $y$（$0 \leq x, y < 2^{30}$）。注意 $x$ 和 $y$ 可能因不同测试用例而异。

本题的交互器是非自适应的。换句话说，整数 $x$ 和 $y$ 在交互过程中不会改变。

要提出询问，请选择一个整数 $n$（$0 \leq n < 2^{30}$）并在一行中仅输出该整数 $n$。

你将收到一个整数，即 $(n \mathbin{|} x) + (n \mathbin{|} y)$ 的值。

你最多只能提出 2 次此类询问。

完成询问后，在一行中输出 "!"。你将收到一个整数 $m$（$0 \leq m < 2^{30}$）。注意 $m$ 的值在交互开始前也已确定。

你必须在一行中仅输出 $(m \mathbin{|} x) + (m \mathbin{|} y)$ 的值。注意此行不被视为询问，不计入询问次数统计。

完成此操作后，继续处理下一个测试用例。

如果在交互过程中提出超过 2 次询问，你的程序必须立即终止，并得到 Wrong Answer 的判定结果。否则，由于你的解决方案将继续从已关闭的流中读取数据，可能会得到任意判定结果。

在输出询问后请勿忘记换行并刷新输出缓冲区。否则你将得到 Idleness limit exceeded。为此，请使用：

- C++ 中的 fflush(stdout) 或 cout.flush()；
- Java 中的 System.out.flush()；
- Pascal 中的 flush(output)；
- Python 中的 stdout.flush()；
- 其他语言请参考相关文档。

## 说明/提示

### 示例交互

在第一个测试中，交互过程如下：

| 解决方案输出 | 评测系统输出 | 说明 |
|--------------|--------------|------|
| `2`          |              | 共有 2 个测试用例 |
|              |              | 第一个测试用例中 $x=1$ 且 $y=2$ |
| `0`          |              | 解决方案询问 $(0 \mathbin{\|} 1) + (0 \mathbin{\|} 2)$ |
|              | `3`          | 评测系统返回 3 |
| `1`          |              | 解决方案询问 $(1 \mathbin{\|} 1) + (1 \mathbin{\|} 2)$ |
|              | `4`          | 评测系统返回 4 |
| `!`          |              | 解决方案请求 $m$ 的值 |
|              | `1`          | 评测系统返回 $m=1$ |
| `4`          |              | 解决方案根据先前询问得知 $(1 \mathbin{\|} x) + (1 \mathbin{\|} y)=4$ |
|              |              | 第二个测试用例中 $x=0$ 且 $y=0$ |
| `0`          |              | 解决方案询问 $(0 \mathbin{\|} 0) + (0 \mathbin{\|} 0)$ |
|              | `0`          | 评测系统返回 0 |
| `!`          |              | 解决方案请求 $m$ 的值 |
|              | `1`          | 评测系统返回 $m=1$ |
| `2`          |              | 解决方案推断出 $x=y=0$，因此返回 $(1 \mathbin{\|} 0) + (1 \mathbin{\|} 0)=2$ |

注意示例输入输出中的空行仅为清晰展示，实际交互中不会出现。

注意示例输入输出中的空行仅为清晰展示，实际交互中不会出现。

## Hacks

要发起 hack，请遵循以下测试格式：

第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的第一行且唯一一行包含三个整数 $x, y, m$（$0 \leq x, y, m < 2^{30}$）。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2

3

4

1

0

1
```

### 输出

```
0

1

!

4

0

!

2
```



---

---
title: "XOR on Segment"
layout: "post"
diff: 普及+/提高
pid: CF242E
tag: ['线段树', '进制', '位运算']
---

# XOR on Segment

## 题目描述

You've got an array $ a $ , consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . You are allowed to perform two operations on this array:

1. Calculate the sum of current array elements on the segment $ [l,r] $ , that is, count value $ a_{l}+a_{l+1}+...+a_{r} $ .
2. Apply the xor operation with a given number $ x $ to each array element on the segment $ [l,r] $ , that is, execute ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a6ed6800239445c652bf1618450a09b2fce8b86d.png). This operation changes exactly $ r-l+1 $ array elements.

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying bitwise xor operation to numbers $ x $ and $ y $ . The given operation exists in all modern programming languages, for example in language C++ and Java it is marked as "^", in Pascal — as "xor".

You've got a list of $ m $ operations of the indicated type. Your task is to perform all given operations, for each sum query you should print the result you get.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the size of the array. The second line contains space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=10^{6} $ ) — the original array.

The third line contains integer $ m $ ( $ 1<=m<=5·10^{4} $ ) — the number of operations with the array. The $ i $ -th of the following $ m $ lines first contains an integer $ t_{i} $ ( $ 1<=t_{i}<=2 $ ) — the type of the $ i $ -th query. If $ t_{i}=1 $ , then this is the query of the sum, if $ t_{i}=2 $ , then this is the query to change array elements. If the $ i $ -th operation is of type $ 1 $ , then next follow two integers $ l_{i},r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ). If the $ i $ -th operation is of type $ 2 $ , then next follow three integers $ l_{i},r_{i},x_{i} $ ( $ 1<=l_{i}<=r_{i}<=n,1<=x_{i}<=10^{6} $ ). The numbers on the lines are separated by single spaces.

## 输出格式

For each query of type $ 1 $ print in a single line the sum of numbers on the given segment. Print the answers to the queries in the order in which the queries go in the input.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams, or the %I64d specifier.

## 样例 #1

### 输入

```
5
4 10 3 13 7
8
1 2 4
2 1 3 3
1 2 4
1 3 3
2 2 5 5
1 1 5
2 1 2 10
1 2 3

```

### 输出

```
26
22
0
34
11

```

## 样例 #2

### 输入

```
6
4 7 4 0 7 3
5
2 2 3 8
1 1 5
2 3 5 1
2 4 5 6
1 2 3

```

### 输出

```
38
28

```



---

---
title: "Bits"
layout: "post"
diff: 普及+/提高
pid: CF484A
tag: ['贪心', '进制', '位运算']
---

# Bits

## 题目描述

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 输入格式

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 输出格式

For each query print the answer in a separate line.

## 说明/提示

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 样例 #1

### 输入

```
3
1 2
2 4
1 10

```

### 输出

```
1
3
7

```



---

---
title: "Kay and Snowflake"
layout: "post"
diff: 普及+/提高
pid: CF685B
tag: ['枚举', '深度优先搜索 DFS', '位运算']
---

# Kay and Snowflake

## 题目描述

After the piece of a devilish mirror hit the Kay's eye, he is no longer interested in the beauty of the roses. Now he likes to watch snowflakes.

Once upon a time, he found a huge snowflake that has a form of the tree (connected acyclic graph) consisting of $ n $ nodes. The root of tree has index $ 1 $ . Kay is very interested in the structure of this tree.

After doing some research he formed $ q $ queries he is interested in. The $ i $ -th query asks to find a centroid of the subtree of the node $ v_{i} $ . Your goal is to answer all queries.

Subtree of a node is a part of tree consisting of this node and all it's descendants (direct or not). In other words, subtree of node $ v $ is formed by nodes $ u $ , such that node $ v $ is present on the path from $ u $ to root.

Centroid of a tree (or a subtree) is a node, such that if we erase it from the tree, the maximum size of the connected component will be at least two times smaller than the size of the initial tree (or a subtree).

## 输入格式

The first line of the input contains two integers $ n $ and $ q $ ( $ 2<=n<=300000 $ , $ 1<=q<=300000 $ ) — the size of the initial tree and the number of queries respectively.

The second line contains $ n-1 $ integer $ p_{2},p_{3},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — the indices of the parents of the nodes from $ 2 $ to $ n $ . Node $ 1 $ is a root of the tree. It's guaranteed that $ p_{i} $ define a correct tree.

Each of the following $ q $ lines contain a single integer $ v_{i} $ ( $ 1<=v_{i}<=n $ ) — the index of the node, that define the subtree, for which we want to find a centroid.

## 输出格式

For each query print the index of a centroid of the corresponding subtree. If there are many suitable nodes, print any of them. It's guaranteed, that each subtree has at least one centroid.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF685B/821209b858c843715556bbbb66f001612969fa03.png)The first query asks for a centroid of the whole tree — this is node $ 3 $ . If we delete node $ 3 $ the tree will split in four components, two of size $ 1 $ and two of size $ 2 $ .

The subtree of the second node consists of this node only, so the answer is $ 2 $ .

Node $ 3 $ is centroid of its own subtree.

The centroids of the subtree of the node $ 5 $ are nodes $ 5 $ and $ 6 $ — both answers are considered correct.

## 样例 #1

### 输入

```
7 4
1 1 3 3 5 3
1
2
3
5

```

### 输出

```
3
2
3
6

```



---

---
title: "Twisted Circuit"
layout: "post"
diff: 普及+/提高
pid: CF784E
tag: ['模拟', '位运算']
---

# Twisted Circuit

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF784E/03bc9ecd826bed4c1045a0a976af29d4edaea871.png)

## 输入格式

The input consists of four lines, each line containing a single digit 0 or 1.

## 输出格式

Output a single digit, 0 or 1.

## 样例 #1

### 输入

```
0
1
1
0

```

### 输出

```
0

```



---

---
title: "Bookshelves"
layout: "post"
diff: 普及+/提高
pid: CF981D
tag: ['贪心', '概率论', '位运算']
---

# Bookshelves

## 题目描述

## 题意：

$Keks$ 先生是 $Byteland$ 大陆的典型的白领。

他办公室里有一个书架，上面有几本书，每本书都有一个值为正整数的价格。

$Keks$ 先生把书架的价值定义为书价的总和。         

出乎意料地是， $Keks$ 先生升职了，现在他要去一个新的办公室。

他知道，在新的办公室里，他将有不止一个书架，而恰恰是 $K$ 个书架。

他认为 $K$ 个书架的美丽程度在于所有书架的价值的“按位与”和。 

他还决定不花时间重新整理书籍，所以他会先把几本书放在第一个书架上，下几本书放在下一个书架上，以此类推。当然，他会在每一个架子上放置至少一本书。这样，他会把所有的书放在 $K$ 个书架上，尽量使书架的美观程度越大越好。计算这个最大可能的美丽程度。

## 输入格式

两行，

第一行两个数：$n,k$ 书本数，书架数。

第二行 $n$ 个整数，每本书的价值。

## 输出格式

一个数，最大可能的美丽程度

## 样例 #1

### 输入

```
10 4
9 14 28 1 7 13 15 29 2 31

```

### 输出

```
24

```

## 样例 #2

### 输入

```
7 3
3 14 15 92 65 35 89

```

### 输出

```
64

```



---

