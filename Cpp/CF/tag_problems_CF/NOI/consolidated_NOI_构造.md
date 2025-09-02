---
title: "Ancient civilizations"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1045E
tag: ['计算几何', '构造']
---

# Ancient civilizations

## 题目描述

On the surface of a newly discovered planet, which we model by a plane, explorers found remains of two different civilizations in various locations. They would like to learn more about those civilizations and to explore the area they need to build roads between some of locations. But as always, there are some restrictions:

1. Every two locations of the same civilization are connected by a unique path of roads
2. No two locations from different civilizations may have road between them (explorers don't want to accidentally mix civilizations they are currently exploring)
3. Roads must be straight line segments
4. Since intersections are expensive to build, they don't want any two roads to intersect (that is, only common point for any two roads may be at some of locations)

Obviously all locations are different points in the plane, but explorers found out one more interesting information that may help you – no three locations lie on the same line!

Help explorers and find a solution for their problem, or report it is impossible.

## 输入格式

In the first line, integer $ n $ $ (1 \leq n \leq 10^3) $ - the number of locations discovered.

In next $ n $ lines, three integers $ x, y, c $ $ (0 \leq x, y \leq 10^4, c \in \{0, 1\}) $ - coordinates of the location and number of civilization it belongs to.

## 输出格式

In first line print number of roads that should be built.

In the following lines print all pairs of locations (their $ 0 $ -based indices) that should be connected with a road.

If it is not possible to build roads such that all restrictions are met, print "Impossible". You should not print the quotation marks.

## 样例 #1

### 输入

```
5
0 0 1
1 0 0
0 1 0
1 1 1
3 2 0

```

### 输出

```
3
1 4
4 2
3 0

```



---

---
title: "Median Queries"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1526F
tag: ['随机化', '构造']
---

# Median Queries

## 题目描述

This is an interactive problem.

There is a secret permutation $ p $ ( $ 1 $ -indexed) of numbers from $ 1 $ to $ n $ . More formally, for $ 1 \leq i \leq n $ , $ 1 \leq p[i] \leq n $ and for $ 1 \leq i < j \leq n $ , $ p[i] \neq p[j] $ . It is known that $ p[1]<p[2] $ .

In $ 1 $ query, you give $ 3 $ distinct integers $ a,b,c $ ( $ 1 \leq a,b,c \leq n $ ), and receive the median of $ \{|p[a]-p[b]|,|p[b]-p[c]|,|p[a]-p[c]|\} $ .

In this case, the median is the $ 2 $ -nd element ( $ 1 $ -indexed) of the sequence when sorted in non-decreasing order. The median of $ \{4,6,2\} $ is $ 4 $ and the median of $ \{0,123,33\} $ is $ 33 $ .

Can you find the secret permutation in not more than $ 2n+420 $ queries?

Note: the grader is not adaptive: the permutation is fixed before any queries are made.

## 输入格式

The first line of input contains a single integer $ t $ $ (1 \leq t \leq 1000) $ — the number of testcases.

The first line of each testcase consists of a single integer $ n $ $ (20 \leq n \leq 100000) $ — the length of the secret permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 100000 $ .

## 输出格式

For each testcase, you begin the interaction by reading $ n $ .

To perform a query, output "? a b c" where $ a,b,c $ is the $ 3 $ indices you want to use for the query.

Numbers have to satisfy $ 1 \leq a,b,c \leq n $ and $ a \neq b $ , $ b \neq c $ , $ a \neq c $ .

For each query, you will receive a single integer $ x $ : the median of $ \{|p[a]-p[b]|,|p[b]-p[c]|,|p[a]-p[c]|\} $ .

In case your query is invalid or you asked more than $ 2n+420 $ queries, the interactor will print "−1" and will finish interaction. You will receive Wrong answer verdict. Make sure to exit immediately to avoid getting other verdicts.

When you have determined the secret permutation, output "! p\[1\] p\[2\] ... p\[n\]". If the secret permutation is correct, the interactor will print "1". Otherwise, the interactor will print "-1" and will finish interaction. You will receive Wrong answer verdict. Make sure to exit immediately to avoid getting other verdicts.

After printing a query do not forget to output the end of line and flush the output. Otherwise, you will get Idleness limit exceeded verdict.

To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

Hacks:

To hack, use the following format of test:

 The first line should contain a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of testcases.

The first line of each testcase should contain a single integer $ n $ ( $ 20 \leq n \leq 100000 $ ) — the length of the secret permutation.

The following line of should contain $ n $ integers $ p[1],p[2],p[3],\ldots,p[n] $ . $ p[1]<p[2] $ and $ p $ must be a permutation of integers from $ 1 $ to $ n $ .

You must ensure that the sum of $ n $ over all testcases does not exceed $ 100000 $ .

## 说明/提示

The secret permutation is $ \{9,10,19,7,16,18,11,14,15,6,20,8,17,4,5,3,12,2,13,1\} $ .

For the first query, the values of $ (a,b,c) $ is $ (1,5,2) $ . Since $ p[1]=9 $ , $ p[5]=16 $ and $ p[2]=10 $ . The return value is the median of $ \{|9-16|,|16-10|,|9-10|\} $ which is $ 6 $ .

For the second query, the values of $ (a,b,c) $ is $ (20,19,2) $ . Since $ p[20]=1 $ , $ p[19]=13 $ and $ p[2]=10 $ . The return value is the median of $ \{|1-13|,|13-10|,|1-10|\} $ which is $ 9 $ .

By some miracle, we have figured out that the secret permutation is $ \{9,10,19,7,16,18,11,14,15,6,20,8,17,4,5,3,12,2,13,1\} $ . We output it and receive $ 1 $ from the interactor, meaning that we have guessed the secret permutation correctly.

## 样例 #1

### 输入

```
1
20

6

9

1
```

### 输出

```
? 1 5 2

? 20 19 2

! 9 10 19 7 16 18 11 14 15 6 20 8 17 4 5 3 12 2 13 1
```



---

---
title: "Birthday"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1637G
tag: ['构造']
---

# Birthday

## 题目描述

Vitaly gave Maxim $ n $ numbers $ 1, 2, \ldots, n $ for his $ 16 $ -th birthday. Maxim was tired of playing board games during the celebration, so he decided to play with these numbers. In one step Maxim can choose two numbers $ x $ and $ y $ from the numbers he has, throw them away, and add two numbers $ x + y $ and $ |x - y| $ instead. He wants all his numbers to be equal after several steps and the sum of the numbers to be minimal.

Help Maxim to find a solution. Maxim's friends don't want to wait long, so the number of steps in the solution should not exceed $ 20n $ . It is guaranteed that under the given constraints, if a solution exists, then there exists a solution that makes all numbers equal, minimizes their sum, and spends no more than $ 20n $ moves.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 25\,000 $ ) — the number of test cases.

Each test case contains a single integer $ n $ ( $ 2 \le n \le 5 \cdot 10^4 $ ) — the number of integers given to Maxim.

It is guaranteed that the total sum of $ n $ doesn't exceed $ 5 \cdot 10^4 $ .

## 输出格式

For each test case print $ -1 $ if it's impossible to make all numbers equal.

Otherwise print a single integer $ s $ ( $ 0 \le s \le 20n $ ) — the number of steps. Then print $ s $ lines. The $ i $ -th line must contain two integers $ x_i $ and $ y_i $ — numbers that Maxim chooses on the $ i $ -th step. The numbers must become equal after all operations.

Don't forget that you not only need to make all numbers equal, but also minimize their sum. It is guaranteed that under the given constraints, if a solution exists, then there exists a solution that makes all numbers equal, minimizes their sum, and spends no more than $ 20n $ moves.

## 样例 #1

### 输入

```
2
2
3
```

### 输出

```
-1
3
1 3
2 2
4 0
```



---

---
title: "Yin Yang"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1667F
tag: ['构造']
---

# Yin Yang

## 题目描述

You are given a rectangular grid with $ n $ rows and $ m $ columns. $ n $ and $ m $ are divisible by $ 4 $ . Some of the cells are already colored black or white. It is guaranteed that no two colored cells share a corner or an edge.

Color the remaining cells in a way that both the black and the white cells becomes orthogonally connected or determine that it is impossible.

Consider a graph, where the black cells are the nodes. Two nodes are adjacent if the corresponding cells share an edge. If the described graph is connected, the black cells are orthogonally connected. Same for white cells.

## 输入格式

The input consists of multiple test cases. The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 4000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ m $ ( $ 8 \le n, m \le 500 $ , $ n $ and $ m $ are divisible by $ 4 $ ) — the number of rows and columns.

Each of the next $ n $ lines contains $ m $ characters. Each character is either 'B', 'W' or '.', representing black, white or empty cell respectively. Two colored (black or white) cell does not share a corner or an edge.

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 250\,000 $ .

## 输出格式

For each testcase print "NO" if there is no solution, otherwise print "YES" and a grid with the same format. If there are multiple solutions, you can print any.

## 说明/提示

Solution for test case 1:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1667F/3dc9d1049e5e9d683890dfa8ead1eafd76cdf4e9.png)Test case 2: one can see that the black and the white part can't be connected in the same time. So the answer is "NO".

## 样例 #1

### 输入

```
4
8 8
.W.W....
.....B.W
.W.W....
.....W.W
B.B.....
....B.B.
B.W.....
....B.B.
8 8
B.W..B.W
........
W.B..W.B
........
........
B.W..B.W
........
W.B..W.B
8 12
W.B.........
....B...B.W.
B.B.........
....B...B.B.
.B..........
........B...
.W..B.B...W.
............
16 16
.W............W.
...W..W..W.W....
.B...........B.W
....W....W......
W......B....W.W.
..W.......B.....
....W...W....B.W
.W....W....W....
...B...........W
W.....W...W..B..
..W.W...W......B
............W...
.W.B...B.B....B.
.....W.....W....
..W......W...W..
W...W..W...W...W
```

### 输出

```
YES
BWWWWWWW
BWBBBBBW
BWBWWWBW
BWBWBWBW
BWBWBWBW
BWBBBWBW
BWWWWWBW
BBBBBBBW
NO
YES
WWBBBBBBBBBB
BWWWBBBBBBWB
BBBWBBBWWWWB
BBBWBBBWBBBB
BBBWBBBWBBBB
BBBWWWWWBBBB
BWWWBBBWWWWB
BBBBBBBBBBBB
YES
WWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWW
WBBBBBBBBBBBBBWW
WBBBWBWWWWBWWBWW
WBBWWBBBWWBWWBWW
WBWWWBWWWWBWWBWW
WBBWWBBBWWBWWBWW
WWBWWWWWWWWWWWWW
WWBBBBBBBBBBBBWW
WBBBWWWBWWWBWBWW
WWWBWBBBWBBBWBBB
WWWBWBWWWWWBWWBW
WWWBWBBBWBBBWWBW
WWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWW
```



---

---
title: "Become Big For Me"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1687E
tag: ['数论', '容斥原理', '构造']
---

# Become Big For Me

## 题目描述

> 『来吧，让我们构筑起一个不会遗弃弱者的乐园吧！』——少名针妙丸&鬼人正邪，《东方辉针城》

针妙丸有一个万宝槌，可以将物体变大或者变小。她现在在对一个序列 $a$ 测试这一功能。具体而言，她有一个实数 $v=1$，她希望在不超过 $10^5$ 次操作后，将 $v$ 变为 $\gcd \limits_{i \neq j} \{a_i \times a_j\}$。其中，$\gcd \limits_{i \neq j} \{a_i \times a_j\}$ 指的是，序列 $a$ 中两个不同元素相乘得到的所有乘积的最大公约数。

在每一次操作中，针妙丸可以选择序列 $a$ 中的一个子序列 $b$，并且对其做如下两种操作中的一个：

- 放大：令 $v \leftarrow v \times \operatorname{lcm(b)}$；
- 缩小：令 $v \leftarrow \dfrac{v}{\operatorname{lcm(b)}}$。

其中，$\operatorname{lcm(b)}$ 指的是序列 $b$ 中所有元素的最小公倍数。此外，她不要求 $v$ 一定是个整数，也就是说执行缩小操作的时候，$v$ 可以不是 $\operatorname{lcm(b)}$ 的倍数。

更进一步地说，针妙丸希望她选取的所有子序列 $b$ 的长度不超过 $10^6$，即 $\sum |b| \leq 10^6$。请你为她找到一种操作方案。注意，您无需最小化任何东西。

## 输入格式

第一行输入一个正整数 $n(2 \leq n \leq 10^5)$，表示序列 $a$ 的长度。

第二行输入 $n$ 个正整数 $a_1,a_2,\dots a_n(1 \leq a_i \leq 10^6)$。

保证最后的答案一定存在。

## 输出格式

第一行输出一个正整数 $k$，表示操作次数。

第二行开始往下输出 $k$ 行，每行包含若干个整数。对于每一行，首先输出两个整数 $f \in \{0,1\}$ 和 $p$，其中 $f=0$ 表示执行放大操作，而 $f=1$ 表示执行缩小操作。$p$ 表示所截取的子序列 $b$ 的长度。接下来是 $p$ 个正整数 $i_1,i_2,\dots,i_p(1 \leq i_1<i_2<\dots<i_p \leq n)$，表示所截取的子序列 $b$ 对应原序列 $a$ 的下标。形式化地说，$b_j=a_{i_j}$。

## 样例 #1

### 输入

```
3
6 10 15
```

### 输出

```
1
0 3 1 2 3
```

## 样例 #2

### 输入

```
4
2 4 8 16
```

### 输出

```
2
0 1 4
1 1 1
```



---

---
title: "Recover the Tree"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1710D
tag: ['构造']
---

# Recover the Tree

## 题目描述

Rhodoks has a tree with $ n $ vertices, but he doesn't remember its structure. The vertices are indexed from $ 1 $ to $ n $ .

A segment $ [l,r] $ ( $ 1 \leq l \leq r \leq n $ ) is good if the vertices with indices $ l $ , $ l + 1 $ , ..., $ r $ form a connected component in Rhodoks' tree. Otherwise, it is bad.

For example, if the tree is the one in the picture, then only the segment $ [3,4] $ is bad while all the other segments are good.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710D/4fd7c832e9131d61a7e54d528e57f32ae63951c2.png)For each of the $ \frac{n(n+1)}{2} $ segments, Rhodoks remembers whether it is good or bad. Can you help him recover the tree? If there are multiple solutions, print any.

It is guaranteed that the there is at least one tree satisfying Rhodoks' description.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 1000 $ ). The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2000 $ ) — the number of vertices in the tree.

Then $ n $ lines follow. The $ i $ -th of these lines contains a string $ good_i $ of length $ n+1-i $ consisting of 0 and 1. If the segment $ [i,i+j-1] $ is good then the $ j $ -th character of $ good_i $ is 1, otherwise $ j $ -th character of $ good_i $ is 0.

It is guaranteed that the there is at least one tree consistent with the given data.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, print $ n-1 $ lines describing the tree you recover.

The $ i $ -th line should contain two integers $ u_i $ and $ v_i $ ( $ 1 \leq u_i,v_i \leq n $ ), denoting an edge between vertices $ u_i $ and $ v_i $ .

If there are multiple solutions, print any.

## 说明/提示

The first test case is explained in the statement.

In the second test case, one possible tree is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710D/5e8ee8c45791f0ab519d49ee3373b652d0c902bd.png)In the third test case, one possible tree is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710D/e951e91b803c38b61a8bd56acc10554d42a981b3.png)

## 样例 #1

### 输入

```
3
4
1111
111
10
1
6
111111
11111
1111
111
11
1
12
100100000001
11100000001
1000000000
100000000
10010001
1110000
100000
10000
1001
111
10
1
```

### 输出

```
1 2
2 3
2 4
1 2
2 3
3 4
4 5
5 6
2 3
6 7
10 11
2 4
6 8
10 12
1 4
5 8
9 12
5 12
2 12
```



---

---
title: "Circular Xor Reversal"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1748F
tag: ['位运算', '构造']
---

# Circular Xor Reversal

## 题目描述

给定整数 $n$。  
初始，有一个编号从 $0$ 开始的长度为 $n$ 的环形序列 $a$，满足 $a_i=2^i$ 对任意整数 $i(0\leq i<n)$ 成立。  
你的任务是将 $a$ 翻转，即使序列 $a$ 满足 $a_i=2^{n-i-1}$ 对任意整数 $i(0\leq i<n)$ 成立。  
为此，你可以进行下列操作至多 $2.5\times10^5$ 次：

- 选定整数 $i$，将 $a_i$ 的值改为 $a_i\text{ xor }a_{(i+1)\bmod n}$。  
其中 $\text{xor}$ 表示按位异或运算。

可以证明在题目限制下，本题一定有解。你需要找出任意一组满足要求的解。

## 输入格式

输入一行一个整数 $n(2\leq n\leq 400)$。

## 输出格式

首先输出一行一个整数 $k(0\leq k\leq2.5\times10^5)$ 表示你所构造的操作方案的操作次数。  
接下来输出一行 $k$ 个整数表示你每次操作所选择的 $i(1\leq i\leq n)$。  
你并不需要最小化操作次数，只需构造任意一组满足要求的操作方案即可。

### 样例解释

- 对于样例一：
	- 初始 $a$ 为 $[1,2]$。
	- 第一次操作选择 $i=1$，操作后 $a$ 为 $[1,3]$。
    - 第二次操作选择 $i=0$，操作后 $a$ 为 $[2,3]$。
    - 第三次操作选择 $i=1$，操作后 $a$ 为 $[2,1]$，此时目标达成。
- 对于样例二：
	- 下面展示了样例输出对应的流程：  
    $[1,2,4]\rightarrow[1,6,4]\rightarrow[7,6,4]\rightarrow[7,2,4]\rightarrow[5,2,4]\rightarrow[5,2,1]\rightarrow[5,3,1]\rightarrow[6,3,1]\rightarrow[6,2,1]\rightarrow[4,2,1]$。

## 样例 #1

### 输入

```
2
```

### 输出

```
3
1 0 1
```

## 样例 #2

### 输入

```
3
```

### 输出

```
9
1 0 1 0 2 1 0 1 0
```



---

---
title: "Maximum Permutation"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1774H
tag: ['构造']
---

# Maximum Permutation

## 题目描述

Ecrade bought a deck of cards numbered from $ 1 $ to $ n $ . Let the value of a permutation $ a $ of length $ n $ be $ \min\limits_{i = 1}^{n - k + 1}\ \sum\limits_{j = i}^{i + k - 1}a_j $ .

Ecrade wants to find the most valuable one among all permutations of the cards. However, it seems a little difficult, so please help him!

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 2 \cdot 10^4 $ ) — the number of test cases. The description of test cases follows.

The only line of each test case contains two integers $ n,k $ ( $ 4 \leq k < n \leq 10^5 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^6 $ .

## 输出格式

For each test case, output the largest possible value in the first line. Then in the second line, print $ n $ integers $ a_1,a_2,\dots,a_n $ ( $ 1 \le a_i \le n $ , all $ a_i $ are distinct) — the elements of the permutation that has the largest value.

If there are multiple such permutations, output any of them.

## 说明/提示

In the first test case, $ [1,4,5,3,2] $ has a value of $ 13 $ . It can be shown that no permutations of length $ 5 $ have a value greater than $ 13 $ when $ k = 4 $ .

In the second test case, $ [4,2,5,7,8,3,1,6] $ has a value of $ 18 $ . It can be shown that no permutations of length $ 8 $ have a value greater than $ 18 $ when $ k = 4 $ .

## 样例 #1

### 输入

```
2
5 4
8 4
```

### 输出

```
13
1 3 4 5 2 
18
1 8 2 7 3 6 4 5
```



---

---
title: "Arithmancy (Hard)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1970D3
tag: ['构造']
---

# Arithmancy (Hard)

## 题目描述

在这道问题中，不同版本的唯一区别是 $ n $ 的最大值。

Vector 教授正忙着为她的算术课准备材料。她需要准备 $ n $ 个不同的魔法词。这些魔法词是由 X 和 O 组成的字符串。一个咒语是由两个魔法词组合而成的字符串，其威力由这个咒语中所有不同非空子串的数量决定。例如，XOXO 这个咒语的威力是 7，因为它有 7 种不同的子串：X、O、XO、OX、XOX、OXO 和 XOXO。

每位学生将从这些魔法词中挑选两个，拼接在一起形成自己的咒语。由于学生们对魔法尚不熟练，这两个词是从 Vector 教授准备的 $ n $ 个词中独立随机选择的，因此有可能选择的是同一个词。然后，学生会计算他们咒语的威力，并告诉 Vector 教授。为了更出色地评价学生的工作，Vector 教授希望能够精确地辨别出学生使用了哪两个魔法词，并且知道它们的顺序。

你的任务是扮演 Vector 教授的角色：首先，生成 $ n $ 个不同的魔法词，然后根据学生给出的咒语威力，确定他们使用了哪两个魔法词及其顺序。

## 输入格式

这是一个交互式问题。

首先，你会读取一个整数 $ n $（$ 1 \le n \le 1000 $），表示需要准备的魔法词的数量。接着，你需要输出 $ n $ 个不同的魔法词，每行一个。每个魔法词的长度至少是 1，最多为 $ 30 \cdot n $ 个字符，而字符只能是 X 或 O。我们用 $ w_i $ 来表示你输出的第 $ i $ 个魔法词（$ 1 \le i \le n $）。

接下来，你会读取一个整数 $ q $（$ 1 \le q \le 1000 $），表示班级里有多少个学生。然后，对于每个学生，重复以下过程 $ q $ 次：

对于第 $ j $ 个学生，程序会读取一个整数 $ p_j $，代表他们咒语的威力。这一咒语的威力是随机选取两个 1 到 $ n $ 之间的索引 $ u_j $ 和 $ v_j $，然后组合 $ w_{u_j} $ 和 $ w_{v_j} $ 计算而得。接着，你需要输出 $ u_j $ 和 $ v_j $（必须按这个顺序），这两个数代表他们所使用的魔法词的索引（$ 1 \le u_j, v_j \le n $）。

需要特别注意的是，必须准确找出学生真正使用的两个魔法词和它们的顺序，而不是其他可能产生相同威力的任意组合。

记得在打印出所有魔法词后，以及每次输出 $ u_j $ 和 $ v_j $ 后，刷新输出流。

## 说明/提示

- $ 1 \le n \le 1000 $
- $ 1 \le q \le 1000 $
- 每个魔法词的长度在 1 到 $ 30 \cdot n $ 之间。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2


2
15

11
```

### 输出

```
XOXO
X


1 1

2 1
```



---

---
title: "Magic Trick II"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1984G
tag: ['构造']
---

# Magic Trick II

## 题目描述

The secret behind Oscar's first magic trick has been revealed! Because he still wants to impress Lura, he comes up with a new idea: he still wants to sort a permutation $ p_1, p_2, \ldots, p_n $ of $ [1, 2, \ldots, n] $ .

This time, he chooses an integer $ k $ . He wants to sort the permutation in non-decreasing order using the following operation several times:

1. Pick a continuous subarray of length $ k $ and remove it from $ p $ .
2. Insert the continuous subarray back into $ p $ at any position (perhaps, in the very front or the very back).

To be as impressive as possible, Oscar would like to choose the maximal value of $ k $ such that he can sort his permutation. Please help him find the maximal $ k $ as well as a sequence of operations that will sort the permutation. You don't need to minimize the number of operations, but you are allowed to use at most $ 5n^2 $ operations.

We have a proof that, for the maximal $ k $ such that you can sort the permutation in any number of operations, you can also sort it in at most $ 5n^2 $ operations.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 5 \leq n \leq 10^3 $ ) — the length of the permutation.

The second line of each test case contains a permutation $ p_1, p_2, \ldots, p_n $ of $ [1, 2, \ldots, n] $ .

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^3 $ .

## 输出格式

For each test case, first output the chosen value of $ k $ on a new line ( $ 1 \leq k \leq n $ ).

Then, output a single integer $ m $ — the number of operations used ( $ 0 \leq m \leq 5n^2 $ ).

Then, on each of the next $ m $ lines, output the operations denoted by two integers $ i $ and $ j $ ( $ 1 \leq i, j \leq n - k + 1 $ ), representing an operation where you remove the subarray starting from index $ i $ and replace it back into $ p $ at index $ j $ .

## 说明/提示

In the first test case, it is enough to move the last four numbers to the front.

In the second test case, it can be shown that we cannot have $ k = 4 $ or $ k = 5 $ . With $ k = 3 $ , we can move the first three numbers to the end, and then the middle three to the front to sort the permutation.

In the third test case, the permutation is already sorted. We can have $ k = 6 $ and use no operations.

## 样例 #1

### 输入

```
3
5
5 1 2 3 4
5
2 3 5 4 1
6
1 2 3 4 5 6
```

### 输出

```
4
1
2 1
3
2
1 3
2 1
6
0
```



---

---
title: "Grid Game"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1991I
tag: ['构造']
---

# Grid Game

## 题目描述

This is an interactive problem.

You are given a grid with $ n $ rows and $ m $ columns. You need to fill each cell with a unique integer from $ 1 $ to $ n \cdot m $ .

After filling the grid, you will play a game on this grid against the interactor. Players take turns selecting one of the previously unselected cells from the grid, with the interactor going first.

On the first turn, the interactor can choose any cell from the grid. After that, any chosen cell must be orthogonally adjacent to at least one previously selected cell. Two cells are considered orthogonally adjacent if they share an edge. The game continues until all cells have been selected.

Your goal is to let the sum of numbers in the cells selected by you be strictly less than the sum of numbers in the cells selected by the interactor.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of test cases follows.

The only line of each test case contains two integers $ n $ and $ m $ ( $ 4 \le n, m \le 10 $ ) — the number of rows and columns in the grid.

## 输出格式

First, output $ n $ lines, each containing $ m $ integers, representing the integers that you filled in the grid. Each integer from $ 1 $ to $ n \cdot m $ should appear exactly once.

Then, the game begins. The interactor and you take turns outputting coordinates to select a cell for $ n \times m $ turns, with the interactor starting first.

On each player's (either you or the interactor) turn, the player will output two integers $ i $ and $ j $ ( $ 1 \le i \le n $ , $ 1 \le j \le m $ ), denoting that the player has selected the cell on the $ i $ -th row and $ j $ -th column. This cell should not have been selected in a previous round. Additionally, if it is not the first turn, the cell must be orthogonally adjacent to at least one previously selected cell.

If any of your outputs are invalid, the jury will output "-1" and you will receive a Wrong Answer verdict.

At the end of all $ n \cdot m $ turns, if the sum of numbers in the cells selected by you is not strictly less than the sum of numbers in the cells selected by the interactor, the jury will output "-1" and you will receive a Wrong Answer verdict.

If your program has received a Wrong Answer verdict, it must terminate immediately. Otherwise, you may receive an arbitrary verdict because your solution might be reading from a closed stream.

After outputting, do not forget to output end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

In this problem, hacks are disabled.

## 说明/提示

Note that this is an example game and does not necessarily represent the optimal strategy for both players.

First, we fill a $ 4 \times 4 $ grid with unique integers from $ 1 $ to $ 16 $ in the following way:

  $ 2 $  $ 3 $  $ 4 $  $ 10 $  $ 12 $  $ 6 $  $ 11 $  $ 15 $  $ 5 $  $ 13 $  $ 16 $  $ 8 $  $ 9 $  $ 7 $  $ 1 $  $ 14 $ Next, the game begins.

1. The interactor first selects $ (3, 4) $ , which is the number $ 8 $ . For this selection, the interactor could choose any number. From the next selection onwards, each chosen number has to be adjacent to any previously selected number.
2. We select $ (2, 4) $ , which is the number $ 15 $ , adjacent to $ (3, 4) $ .
3. The interactor selects $ (4, 4) $ , which is the number $ 14 $ , adjacent to $ (3, 4) $ .
4. We select $ (4, 3) $ , which is the number $ 1 $ , adjacent to $ (4, 4) $ .
5. $ \ldots $
6. This is continued until all numbers are selected.

In the end, the numbers we selected were $ [15, 1, 16, 5, 4, 2, 11, 13] $ , and the numbers selected by the interactor were $ [8, 14, 7, 9, 10, 3, 6, 12] $ . The sum of the numbers we selected is $ 67 $ , which is less than the sum of the numbers selected by the interactor $ 69 $ . Therefore, we have won this game.

## 样例 #1

### 输入

```
1
4 4




3 4

4 4

4 2

4 1

1 4

1 2

2 2

2 1
```

### 输出

```
2 3 4 10
12 6 11 15
5 13 16 8
9 7 1 14

2 4

4 3

3 3

3 1

1 3

1 1

2 3

3 2
```



---

---
title: "Simurgh's Watch (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2034G1
tag: ['动态规划 DP', '贪心', '构造']
---

# Simurgh's Watch (Easy Version)

## 题目描述

传说中，神鸟 [Simurgh](https://www.eavartravel.com/blog/2023/11/3/140727/simurgh/) 需要监管大片土地，她召集了 $ n $ 名警惕的战士帮忙。每个战士在特定的时间段内保持警戒，这个时间段用 $ [l_i, r_i] $ 表示，其中 $ l_i $ 和 $ r_i $ 分别为开始和结束时间，都是包含在内的正整数。

![](https://espresso.codeforces.com/e448e919c3f03a9c212cd45c8dcd8e2bb0be579c.webp)然而，Simurgh 的顾问 [Zal](https://asia-archive.si.edu/learn/shahnama/zal-and-the-simurgh/) 担心，如果多个战士在同一时间值守且都穿着相同颜色的衣服，会造成混淆。因此，为了防止这种情况发生，在任何时刻（可以是非整数时间）的战士中，至少要有一种颜色是由恰好一个战士穿着的。

我们的任务是：确定需要的最少颜色数，并为每个战士的时间段 $ [l_i, r_i] $ 分配一种颜色 $ c_i $，使得无论在哪一个时间 $ t $（被某个时间段包含在内），至少有一种颜色只出现在一个战士上。

## 输入格式

第一行包含一个整数 $ t $ （$ 1 \leq t \leq 10^4 $）——表示测试用例的数目。

每个测试用例包含以下内容：

- 第一行是一个整数 $ n $ （$ 1 \leq n \leq 2 \cdot 10^5 $）——表示 Simurgh 派出的战士数量。
- 接下来的 $ n $ 行中，每行包含两个整数 $ l_i $ 和 $ r_i $ （$ 1 \leq l_i \leq r_i \leq 10^9 $）——分别表示第 $ i $ 个战士的值班开始和结束时间。

所有测试用例中 $ n $ 的总和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对于每个测试用例：

- 首先输出要使用的最少的颜色数量 $ k $。
- 接下来输出一行 $ n $ 个整数 $ c_i $（$ 1 \leq c_i \leq k $），代表为第 $ i $ 位战士分配的颜色。

## 说明/提示

可以将每个战士的值班时间段视作 X 轴上的一个区间：

- 在测试用例 1 中，有两个彼此不重叠的区间，因此可用相同颜色。
- 在测试用例 2 中，时间点 2 是公共的，因此不能使用相同颜色。
- 在测试用例 3 中，区间可以按下图所示进行着色：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G1/dd56c79752790418adde70ef7aa40c52b2f8834f.png)

- 在测试用例 4 中，区间的着色方式如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G1/7c7aad3a3ba91ddaff1d673e62791383c4f77dec.png)

- 在测试用例 5 中，区间着色如下图所示。右侧图是错误的着色示例；在时间点 $ 5.5 $ 时，没有唯一颜色：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G1/b8f2a4852b6af3f78d2729a80e0ad7497e55682a.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
1 2
3 4
2
1 2
2 3
3
1 4
2 5
3 6
5
1 4
2 8
3 7
5 10
6 9
5
1 5
2 6
3 7
4 7
6 7
```

### 输出

```
1
1 1
2
1 2
2
1 2 1
3
2 3 1 2 1
3
2 1 3 1 1
```



---

---
title: "Simurgh's Watch (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2034G2
tag: ['动态规划 DP', '贪心', '构造']
---

# Simurgh's Watch (Hard Version)

## 题目描述

传说中的神鸟 Simurgh 负责守护一片辽阔的土地，她为此招募了 $n$ 名机敏的战士。每位战士都需要在特定的时间段 $[l_i, r_i]$ 内保持警戒，其中 $l_i$ 代表起始时间（包含），$r_i$ 代表结束时间（包含），两者均为正整数。

Simurgh 信任的顾问 Zal 担心，如果多个战士同时在岗且都穿着相同的颜色，那么他们之间可能会难以区分，从而导致混乱。为解决这一问题，在每个整数时刻 $t$，如果有多个战士在岗，必须确保至少有一种颜色仅被其中一个战士穿着。

任务是找出所需的最少颜色数量，并为每个战士的时间段 $[l_i, r_i]$ 分配一种颜色 $c_i$，使得对于包含在至少一个时间段内的每个整数时间点 $t$，总有一种颜色只被一个时间段在$t$时刻使用。

## 输入格式

第一行输入一个整数 $t$（$1 \leq t \leq 10^4$），表示测试用例的数量。

对于每个测试用例：

- 第一行包含一个整数 $n$（$1 \leq n \leq 2 \cdot 10^5$），表示 Simurgh 招募的战士数量。
- 随后的 $n$ 行中，每行包含两个整数 $l_i$ 和 $r_i$（$1 \leq l_i \leq r_i \leq 10^9$），表示第 $i$ 位战士的警戒时间段。

所有测试用例中的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例：

- 输出所需的最少颜色数量 $k$。
- 接下来输出一行，包括 $n$ 个整数 $c_i$（$1 \leq c_i \leq k$），每个 $c_i$ 表示分配给第 $i$ 位战士的颜色。

## 说明/提示

我们可以将每位战士的警戒时间段看作 X 轴上的一个区间。

以下示例展示了如何为各个测试用例的区间着色（区域只有在某时间点，仅某种颜色出现时该区域才被染色）：

- 测试用例 1：

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G2/a8ca04e863ed852cb4b11c3982c1d5442199b24b.png)

- 测试用例 2：

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G2/36f2a5d9878f69668f835178da7df8642bec8342.png)

- 测试用例 3：

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G2/75559577acf19732a5a59981d3806145e52c5ed5.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
5
1 4
2 8
3 7
5 10
6 9
5
1 5
2 6
3 7
4 7
6 7
5
4 9
8 17
2 15
12 19
6 13
```

### 输出

```
2
1 2 2 1 2
2
1 2 2 2 1
3
1 1 2 3 1
```



---

---
title: "Peak Productivity Forces"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2035H
tag: ['构造']
---

# Peak Productivity Forces

## 题目描述

我们处在巅峰状态，来解决一个复杂的难题。

现有两组长度为 $n$ 的排列 $a$ 和 $b$。

你可以对排列 $a$ 进行如下操作：

1. 选择一个索引 $i$（$1 \le i \le n$）。
2. 将 $a_1, a_2, \ldots, a_{i-1}$ 按循环右移一位。如果选择了 $i = 1$，则这一部分不存在，因此无需移动。
3. 将 $a_{i + 1}, a_{i + 2}, \ldots, a_n$ 按循环右移一位。如果选择了 $i = n$，则这一部分不存在，因此也无需移动。

执行操作后，排列会从 $a_1, a_2, \ldots, a_{i-1}, a_i, a_{i+1}, \ldots, a_n$ 变成 $a_{i-1}, a_1, \ldots, a_{i-2}, a_i, a_n, a_{i+1}, \ldots, a_{n-1}$。

以下是长度为 $7$ 的单位排列 $[1, 2, 3, 4, 5, 6, 7]$ 的一些操作示例：

- 选择 $i = 3$，排列变为 $[2, 1, 3, 7, 4, 5, 6]$。
- 选择 $i = 1$，排列变为 $[1, 7, 2, 3, 4, 5, 6]$。
- 选择 $i = 7$，排列变为 $[6, 1, 2, 3, 4, 5, 7]$。

注意，第 $i$ 个位置的元素不发生位置变化。请尝试在最多 $2n$ 次操作中，使排列 $a$ 转换为排列 $b$。如果无法实现转换，请输出 $-1$。不需要最小化操作次数。已知如果可以转换，则在不超过 $2n$ 次操作内即可实现。

$^{\text{∗}}$ 长度为 $n$ 的排列是指包含 $1$ 到 $n$ 的任意顺序且互不重复的 $n$ 个整数组成的数组。例如，$[2, 3, 1, 5, 4]$ 是一个排列，但 $[1, 2, 2]$ 不是（因为 $2$ 重复出现），$[1, 3, 4]$ 也不是（因为缺少 $2$ 且多了 $4$）。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 5 \cdot 10^4$）——测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 5 \cdot 10^5$）——排列 $a$ 和 $b$ 的长度。

接下来的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le n$）——排列 $a$ 的元素。

第三行包含 $n$ 个整数 $b_1, b_2, \ldots, b_n$（$1 \le b_i \le n$）——排列 $b$ 的元素。

保证所有测试用例中 $n$ 的总和不超过 $5 \cdot 10^5$。

## 输出格式

对于每个测试用例：

如果可以通过一系列操作将 $a$ 转换为 $b$，请在第一行输出一个整数 $q$（$0 \le q \le 2n$）——操作次数，第二行输出 $q$ 个整数，第 $i$ 个整数表示第 $i$ 次操作选择的索引。

如果无法完成转换，输出 $-1$。

## 说明/提示

在第一个测试用例中，$a$ 已经等于 $b$，因此不需要操作。

在第二个测试用例中，可以证明 $a$ 无法变为 $b$。

在第三个测试用例中，经过两次操作后，$a$ 变成了与 $b$ 相同的排列。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1
1
1
2
1 2
2 1
3
2 1 3
3 2 1
8
7 8 3 5 4 6 1 2
2 1 6 4 5 3 8 7
```

### 输出

```
0

-1
2
1 3
7
3 4 5 1 2 1 1
```



---

---
title: "Cool Swap Walk (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2039H1
tag: ['构造']
---

# Cool Swap Walk (Easy Version)

## 题目描述

# Cool Swap Walk (Easy Version)


给你一个大小为 $ n $ 的数组 $ a $ 。

下面是一个很酷的交换行走过程：

- 你需要从 $(1,1) $ 走到 $(n,n) $ ，只需向右或向下走一步。
- 从形式上看，如果当前位于 $ (x,y) $，则可以走到 $ (x+1,y) $ 或 $ (x,y+1) $，但不能越过网格边界。
- 当你步进 $ (i,j) $ 时，必须在 $ i\neq j $ 时交换 $ a_i $ 和 $ a_j $。

你最多可以进行 $ 2n+4 $ 次酷交换行走。将数组 $ a_1, a_2, \ldots, a_n $ 按非递减顺序排序。数据保证成立。

## 输入格式

第一行包含一个整数 $ t $（$ 1 \le t \le 10^4 $）表示测试用例的数量。

每个测试用例的第一行包含一个整数 $ n $ ( $ 2 \leq n \leq 500 $ ) 表示数组的大小。

每个测试用例的第二行包含 n 个整数 $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le n $ ) 为数组中的元素。

保证所有测试用例的 $ n^2 $ 之和不超过 $ 2.5 \cdot 10^5 $ 。

## 输出格式

- 第一行包含一个整数 $ k $ ( $ 0 \leq k \leq 2n+4 $ )，代表你执行的酷交换行走次数。
- 接下来的每一行 $ k $ 包含一个长度为 $ 2n-2 $ 的字符串 $ s $，仅由 R 和 D 组成，代表路径（字母区分大小写）。对于所有 $ 1 \le i \le 2n-2 $ , 如果 $ s_i= $ R, 你在第 $ i $ 步向右走, 否则你在第 $ i $ 步向下走.

## 样例 #1

### 样例输入 #1

```
3
2
1 2
3
2 1 3
4
3 2 3 4
```

### 样例输出 #1

```
0
2
RRDD
DRDR
3
RRDRDD
DRDDRR
DDRRRD
```

## 说明/提示

样例一中，数组 $ a $ 已经是非递减的，所以不需要再走一遍。

样例二中，$ a=[2,1,3] $ 最初是递减的。

在第一次行走中

- 然后，$ a=[1,2,3] $ 注意，虽然数组 $ a $ 已经是非递减的，但在到达 $ (n,n) $ 之前不能停止。
- 在第 $ 2 $ 步中，你向右走到 $ (1,3) $ . 然后，$ a=[3,2,1] $ .
- 在第 $ 3 $ 步中，向下移动到 $ (2,3) $ . 然后，$ a=[3,1,2] $ .
- 在第 $ 4 $ 步中，你下到 $ (3,3) $ . 然后，$ a=[3,1,2] $ .

在第二次行走中

- 在第 $ 1 $ 步中，你下到 $ (2,1) $ . 然后，$ a=[1,3,2] $ .
- 在第 $ 2 $ 步中，向右走到 $ (2,2) $ . 然后，$ a=[1,3,2] $ .
- 在第 $ 4 $ 步中，向下移动到 $ (3,2) $ . 然后，$ a=[1,2,3] $ .
- 在第 $ 4 $ 步中，你下到 $ (3,3) $ . 然后，$ a=[1,2,3] $ .

经过上述两次酷交换行走，我们得到 $ a=[1,2,3] $ ，它是不递减的。

## 样例 #1

### 输入

```
3
2
1 2
3
2 1 3
4
3 2 3 4
```

### 输出

```
0
2
RRDD
DRDR
3
RRDRDD
DRDDRR
DDRRRD
```



---

---
title: "Cool Swap Walk (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2039H2
tag: ['构造']
---

# Cool Swap Walk (Hard Version)

## 题目描述

# Cool Swap Walk (Easy Version)


给你一个大小为 $ n $ 的数组 $ a $ 。

下面是一个很酷的交换行走过程：

- 你需要从 $(1,1) $ 走到 $(n,n) $ ，只需向右或向下走一步。
- 从形式上看，如果当前位于 $ (x,y) $，则可以走到 $ (x+1,y) $ 或 $ (x,y+1) $，但不能越过网格边界。
- 当你步进 $ (i,j) $ 时，必须在 $ i\neq j $ 时交换 $ a_i $ 和 $ a_j $。

你最多可以进行 $ n+4 $ 次酷交换行走。将数组 $ a_1, a_2, \ldots, a_n $ 按非递减顺序排序。数据保证成立。

## 输入格式

第一行包含一个整数 $ t $（$ 1 \le t \le 10^4 $）表示测试用例的数量。

每个测试用例的第一行包含一个整数 $ n $ ( $ 2 \leq n \leq 500 $ ) 表示数组的大小。

每个测试用例的第二行包含 n 个整数 $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le n $ ) 为数组中的元素。

保证所有测试用例的 $ n^2 $ 之和不超过 $ 2.5 \cdot 10^5 $ 。

## 输出格式

- 第一行包含一个整数 $ k $ ( $ 0 \leq k \leq n+4 $ )，代表你执行的酷交换行走次数。
- 接下来的每一行 $ k $ 包含一个长度为 $ 2n-2 $ 的字符串 $ s $，仅由 R 和 D 组成，代表路径（字母区分大小写）。对于所有 $ 1 \le i \le 2n-2 $ , 如果 $ s_i= $ R, 你在第 $ i $ 步向右走, 否则你在第 $ i $ 步向下走.

## 样例 #1

### 样例输入 #1

```
3
2
1 2
3
2 1 3
4
3 2 3 4
```

### 样例输出 #1

```
0
2
RRDD
DRDR
3
RRDRDD
DRDDRR
DDRRRD
```

## 说明/提示

样例一中，数组 $ a $ 已经是非递减的，所以不需要再走一遍。

样例二中，$ a=[2,1,3] $ 最初是递减的。

在第一次行走中

- 然后，$ a=[1,2,3] $ 注意，虽然数组 $ a $ 已经是非递减的，但在到达 $ (n,n) $ 之前不能停止。
- 在第 $ 2 $ 步中，你向右走到 $ (1,3) $ . 然后，$ a=[3,2,1] $ .
- 在第 $ 3 $ 步中，向下移动到 $ (2,3) $ . 然后，$ a=[3,1,2] $ .
- 在第 $ 4 $ 步中，你下到 $ (3,3) $ . 然后，$ a=[3,1,2] $ .

在第二次行走中

- 在第 $ 1 $ 步中，你下到 $ (2,1) $ . 然后，$ a=[1,3,2] $ .
- 在第 $ 2 $ 步中，向右走到 $ (2,2) $ . 然后，$ a=[1,3,2] $ .
- 在第 $ 4 $ 步中，向下移动到 $ (3,2) $ . 然后，$ a=[1,2,3] $ .
- 在第 $ 4 $ 步中，你下到 $ (3,3) $ . 然后，$ a=[1,2,3] $ .

经过上述两次酷交换行走，我们得到 $ a=[1,2,3] $ ，它是不递减的。

## 样例 #1

### 输入

```
3
2
1 2
3
2 1 3
4
3 2 3 4
```

### 输出

```
0
2
RRDD
DRDR
3
RRDRDD
DRDDRR
DDRRRD
```



---

---
title: "Buggy DFS"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2045L
tag: ['构造', 'Ad-hoc']
---

# Buggy DFS

## 题目描述

你正在学习一种名为深度优先搜索（DFS）的图遍历算法。然而，由于一个小错误，你的算法与标准版本略有区别。以下是你实现的有误深度优先搜索（BDFS）算法，假设图中有 $N$ 个节点（编号从 $1$ 到 $N$）。

```
BDFS():
  令 S 为一个空栈
  令 FLAG 为大小为 N 的布尔数组，初始值均为 false
  令 counter 为一个整数，初始化为 0

  将 1 压入栈 S

  当 S 不为空时：
    弹出 S 的栈顶元素到 u
    FLAG[u] = true

    对于 u 的每个邻居 v（按升序访问）：
      counter = counter + 1
      如果 FLAG[v] 为 false：
        将 v 压入栈 S

  返回 counter
```

你发现这个错误让算法比标准的 DFS 慢。通过查看函数 BDFS() 的返回值可以探究这个问题。为了更好地研究算法的行为，你打算构造一些无向简单图，让函数 BDFS() 的返回值等于 $K$，或者确定这样的图是否存在。

## 输入格式

输入只包含一个整数 $K$ （$1 \leq K \leq 10^9$）。

## 输出格式

如果无法构造一个无向简单图使得 BDFS() 返回 $K$，则输出 -1 -1。

否则，按照以下格式输出图的描述。第一行包含两个整数 $N$ 和 $M$，分别表示图中的节点数和无向边数。接下来的 $M$ 行，每行包含两个整数 $u$ 和 $v$，表示连接节点 $u$ 和节点 $v$ 的一条无向边。边的顺序可以随意，图需满足以下条件：

- $1 \leq N \leq 32\,768$
- $1 \leq M \leq 65\,536$
- 对于所有的边，$1 \leq u, v \leq N$
- 图为无向简单图，即没有重边和自环

注意，你不需要尽量减少节点或边的数量。可以证明，如果可以构造一个图使得 BDFS() 返回值为 $K$，则必然存在一个满足所有上述限制条件的图解。若有多个解，任选其一即可。

## 例子与提示

样例输入/输出 #1 的解析：

左图为该样例的输出。右图是该例子的另一个合理解。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045L/f1ba627a6dee4a42828d91349340ced7a2cb28cd.png)

样例输入/输出 #3 的解析：

下图为该例的输出。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045L/e5b77af5c2622d444d81c6aab8c41cda5b753182.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
8
```

### 输出

```
3 3
1 2
1 3
2 3
```

## 样例 #2

### 输入

```
1
```

### 输出

```
-1 -1
```

## 样例 #3

### 输入

```
23
```

### 输出

```
5 7
4 5
2 3
3 1
2 4
4 3
2 1
1 5
```



---

---
title: "Cheops and a Contest (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2046E2
tag: ['贪心', '构造']
---

# Cheops and a Contest (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in this version, $ m $ is arbitrary. You can hack only if you solved all versions of this problem.

There is a problem-solving competition in Ancient Egypt with $ n $ participants, numbered from $ 1 $ to $ n $ . Each participant comes from a certain city; the cities are numbered from $ 1 $ to $ m $ . There is at least one participant from each city.

The $ i $ -th participant has strength $ a_i $ , specialization $ s_i $ , and wisdom $ b_i $ , so that $ b_i \ge a_i $ . Each problem in the competition will have a difficulty $ d $ and a unique topic $ t $ . The $ i $ -th participant will solve the problem if

- $ a_i \ge d $ , i.e., their strength is not less than the problem's difficulty, or
- $ s_i = t $ , and $ b_i \ge d $ , i.e., their specialization matches the problem's topic, and their wisdom is not less than the problem's difficulty.

Cheops wants to choose the problems in such a way that each participant from city $ i $ will solve strictly more problems than each participant from city $ j $ , for all $ i < j $ .

Please find a set of at most $ 5n $ problems, where the topics of all problems are distinct, so that Cheops' will is satisfied, or state that it is impossible.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ T $ ( $ 1 \le T \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ m $ ( $ 2 \le m \le n \le 3 \cdot {10}^5 $ ) — the number of participants and the number of cities.

The following $ n $ lines describe the participants. The $ i $ -th line contains three integers — $ a_i $ , $ b_i $ , $ s_i $ ( $ 0 \le a_i, b_i, s_i \le {10}^9 $ , $ a_i \le b_i $ ) — strength, wisdom, and specialization of the $ i $ -th participant, respectively.

The next $ m $ lines describe the cities. In the $ i $ -th line, the first number is an integer $ k_i $ ( $ 1 \le k_i \le n $ ) — the number of participants from the $ i $ -th city. It is followed by $ k_i $ integers $ q_{i, 1}, q_{i, 2}, \ldots, q_{i, k_i} $ — ( $ 1 \le q_{i, j} \le n $ , $ 1 \le j \le k_i $ ) — the indices of the participants from this city. It is guaranteed that each participant is mentioned exactly once.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, if there exists a set of problems that satisfies Cheops' conditions, then in the first line output a single integer $ p $ ( $ 1 \le p \le 5n $ ) — the number of problems in your solution.

Then output $ p $ lines, each containing two integers $ d $ and $ t $ ( $ 0 \le d, t \le {10}^9 $ ) — the difficulty and topic of the respective problem. The topics must be distinct.

If there is no set of problems that meets Cheops' wishes, print $ -1 $ instead.

## 样例 #1

### 输入

```
2
5 2
5 7 1
6 7 2
3 9 2
5 10 3
4 4 1
2 1 2
3 3 4 5
2 2
1 2 1
1 2 1
1 2
1 1
```

### 输出

```
7
6 4
6 5
5 6
5 7
4 8
4 9
7 1
-1
```



---

---
title: "Kevin and Puzzle (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2048I1
tag: ['递归', '构造']
---

# Kevin and Puzzle (Easy Version)

## 题目描述

这是问题的简单版本。在这个版本中，你需要找到任意一个符合条件的数组。只有在解决了所有版本的问题后，你才可以进行 hack。

Kevin 在红教堂参观时，墙上发现一个谜题。

对于一个数组 $a$，定义 $c(l, r)$ 表示在 $a_l, a_{l+1}, \ldots, a_r$ 之间不同数字的数量。特别地，当 $l > r$ 时，定义 $c(l, r) = 0$。

给定一个长度为 $n$ 的字符串 $s$，字符串中仅包含字母 $\texttt{L}$ 和 $\texttt{R}$。若一个非负整数数组 $a$ 满足以下条件，则称其为“好”数组：

- 如果 $s_i=\verb!L!$，则 $c(1, i-1)=a_i$；
- 如果 $s_i=\verb!R!$，则 $c(i+1, n)=a_i$。

如果存在这样的“好”数组 $a$，请输出任意一个符合要求的数组。否则，输出 -1 表示不存在。

## 输入格式

输入包含多个测试用例。第一行是一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的数量。

每个测试用例的第一行是一个整数 $n$（$2 \le n \le 2 \cdot 10^5$），表示字符串 $s$ 的长度。

接下来一行是长度为 $n$ 的字符串 $s$，仅包含字母 $\verb!L!$ 和 $\verb!R!$。

保证所有测试用例的总长度之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果存在一个“好”数组，输出 $n$ 个非负整数，即该“好”数组。否则，输出 -1 表示不存在这样的数组。

如果存在多个符合条件的数组，任选其一输出即可。

## 说明/提示

在第一个测试用例中，数组 $[0, 1, 0]$ 满足条件，因为：

- 当 $i=1$ 时，$s_i=\verb!L!$，此时 $c(1, 0)=0$；
- 当 $i=2$ 时，$s_i=\verb!L!$，此时 $c(1, 1)=1$，因为 $a_1$ 中只有一个不同的数字；
- 当 $i=3$ 时，$s_i=\verb!R!$，此时 $c(4, 3)=0$。

在第二个测试用例中，数组 $[1, 1, 1]$ 也是一个有效答案。

在第三个测试用例中，可以证明不存在满足条件的数组。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
3
LLR
3
RRL
4
RRLR
5
LLRLR
```

### 输出

```
0 1 0
2 1 2
-1
0 1 2 3 0
```



---

---
title: "Kevin and Puzzle (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2048I2
tag: ['构造', '标签465']
---

# Kevin and Puzzle (Hard Version)

## 题目描述

这是此题目的困难版本，两个版本的区别在于在这个版本中，你需要计算出所有“好数组”的数量。只有在解决了所有版本的问题后，才可以进行 hack。

Kevin 在参观红教堂时发现了一道墙上的谜题。

对于一个数组 $a$，令 $c(l, r)$ 表示数组 $a$ 从位置 $l$ 到 $r$ 的所有元素中，不同数字的个数。特别地，当 $l > r$ 时，定义 $c(l, r) = 0$。

现给定一个长度为 $n$ 的字符串 $s$，该字符串仅由字母 $\texttt{L}$ 和 $\texttt{R}$ 组成。将一个非负整数数组 $a$ 称为“好数组”，如果对于每个 $1 \leq i \leq n$ 满足以下条件：

- 若 $s_i = \verb!L!$，则 $c(1, i-1) = a_i$；
- 若 $s_i = \verb!R!$，则 $c(i+1, n) = a_i$。

你的任务是计算这样的“好数组” $a$ 的数量。由于结果可能会非常大，输出结果时只需对 $998\,244\,353$ 取模。

## 输入格式

输入包含多组测试用例。 

第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的数量。

每个测试用例中：
- 第一行包含一个整数 $n$（$2 \leq n \leq 2 \cdot 10^5$），表示字符串 $s$ 的长度。
- 第二行是一个长度为 $n$ 的字符串 $s$，由字母 $\verb!L!$ 和 $\verb!R!$ 组成。

并且，所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出“好数组”的数量，并对 $998\,244\,353$ 取模。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
3
LLR
3
RRL
4
RRLR
5
LLRLR
```

### 输出

```
1
2
0
1
```



---

---
title: "Hot Matrix"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2081F
tag: ['构造']
---

# Hot Matrix

## 题目描述

Piggy Zhou 热爱矩阵，尤其是能让他感到兴奋的"热矩阵"。

一个大小为 $n \times n$ 的热矩阵定义如下。令 $a_{i, j}$ 表示第 $i$ 行第 $j$ 列的元素（$1 \le i, j \le n$）：

1. 矩阵的每一行和每一列都是 $0$ 到 $n-1$ 所有数字的一个排列。
2. 对于所有满足 $1 \le i, j \le n$ 的索引对 $(i, j)$，有 $a_{i, j} + a_{i, n - j + 1} = n - 1$。
3. 对于所有满足 $1 \le i, j \le n$ 的索引对 $(i, j)$，有 $a_{i, j} + a_{n - i + 1, j} = n - 1$。
4. 所有有序对 $\left(a_{i, j}, a_{i, j + 1}\right)$（其中 $1 \le i \le n$，$1 \le j < n$）必须互不相同。
5. 所有有序对 $\left(a_{i, j}, a_{i + 1, j}\right)$（其中 $1 \le i < n$，$1 \le j \le n$）必须互不相同。

现在，Piggy Zhou 给定你一个数字 $n$，你需要判断是否存在对应的热矩阵。若存在则构造一个符合要求的热矩阵，否则告知他无法构造。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 1000$）。接下来描述每个测试用例。

每个测试用例的输入仅包含一个整数 $n$（$1 \le n \le 3000$）。

保证所有测试用例的 $n$ 总和不超过 $3000$。

## 输出格式

对于每个测试用例：
- 若不存在热矩阵，输出"NO"（不含引号）。
- 否则，在第一行输出"YES"（不含引号），随后输出 $n$ 行，每行包含 $n$ 个数字，表示符合要求的热矩阵。

若存在多个解，输出任意一个即可。

## 说明/提示

第一个、第二个和第四个测试用例中，可以验证示例提供的矩阵满足题目所有条件。

第三个测试用例中，通过枚举所有可能的矩阵，可以证明不存在满足条件的热矩阵。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
1
2
3
4
```

### 输出

```
YES
0
YES
0 1
1 0
NO
YES
0 1 2 3
1 3 0 2
2 0 3 1
3 2 1 0
```



---

---
title: "Online Palindrome"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2086F
tag: ['构造', '分类讨论']
---

# Online Palindrome

## 题目描述

这是一个交互题。

裁判有一个由小写拉丁字母组成的字符串 $s$。该字符串满足以下约束条件：
- 字符串长度为不超过 $99$ 的奇数；
- 字符串仅由字符 "a" 和 "b" 组成。

另外有一个初始为空的字符串 $t$。接下来会进行 $|s|$ 个步骤。在第 $i$ 个步骤中，会发生以下事件：
- 首先，裁判会告诉你字符 $s_i$ 并将其追加到字符串 $t$ 的末尾；
- 然后，你可以交换 $t$ 中的任意两个字符，或者什么都不做。

你的任务是确保在第 $|s|$ 个步骤之后，字符串 $t$ 是一个回文串。

## 输出格式

交互过程立即开始。

在每个步骤中，你的程序将接收一个字符——字符串 $s$ 的下一个字符，或者如果字符串已经结束则接收 "0"（零）。如果接收到字符 "0"，你的程序必须立即终止。

在接收到 $s_{i}$ 后，你必须输出要交换的字符的位置，即两个整数 $l$ 和 $r$（$1 \le l,r \le i$），或者如果你不想交换字符，则输出 "0 0"。

如果你的程序执行了无效操作，例如尝试交换不存在的字符位置，或者最终字符串 $t$ 不是回文串，裁判程序将在单独的一行打印一个字符 "X"。如果你的程序接收到 "X" 作为响应，它应该立即终止；否则，你的提交的判题结果将是未定义的。

本题的交互器不是自适应的，这意味着字符串 $s$ 在交互过程中不会改变。

在每次输出请求后，不要忘记输出换行符并刷新输出缓冲区。否则，你将收到 "Idleness limit exceeded" 的判题结果。为此，请使用：
- C++ 中的 `fflush(stdout)` 或 `cout.flush()`；
- Java 中的 `System.out.flush()`；
- Python 中的 `sys.stdout.flush()`；
- 其他语言请参考相关文档。

Hack 格式

对于 Hack，请使用以下格式。

第一行应包含一个整数 $|s|$ —— 字符串 $s$ 的长度。

第二行应包含字符串 $s$ 本身（$1 \le |s| \le 99$，$|s| \bmod 2 = 1$），由小写拉丁字母 "a" 和 "b" 组成。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
a

a

b

0
```

### 输出

```
0 0

1 2

2 3
```

## 样例 #2

### 输入

```
a

a

b

a

b

0
```

### 输出

```
0 0

2 1

3 2

4 4

4 5
```



---

---
title: "Wonderful Guessing Game"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2096G
tag: ['位运算', '构造']
---

# Wonderful Guessing Game

## 题目描述

这是一道交互题。

你是千年科学学校的一名自豪的教师。今天，一名叫 Alice 的学生向你发起了一个猜数游戏的挑战。

Alice 心中想着一个 $1$ 到 $n$ 之间的整数，你必须通过向她提出一些查询来猜出这个数。

为了增加难度，她要求你必须先提出所有查询，而她将忽略其中的恰好 $1$ 个查询。

对于每个查询，你需要选择一个由 $1$ 到 $n$ 之间的 $k$ 个不同整数组成的数组，其中 $k$ 是偶数。然后，Alice 会给出以下回应之一：

- $\texttt{L}$：这个数位于数组的前 $\frac{k}{2}$ 个元素中；
- $\texttt{R}$：这个数位于数组的后 $\frac{k}{2}$ 个元素中；
- $\texttt{N}$：这个数不在数组中；
- $\texttt{?}$：这个查询被忽略。

Alice 很没耐心，因此你必须找到一种策略，使得查询次数最少。你能做到吗？

形式化地说，设 $f(n)$ 为确定 Alice 的数字所需的最小查询次数。你需要找到一种恰好使用 $f(n)$ 次查询的策略。

注意，交互器是自适应的，这意味着 Alice 的数字并非一开始就固定，可能会根据你的查询而变化。然而，保证至少存在一个数字与 Alice 的回应一致。

我们可以证明，对于所有满足 $2 \le n \le 2 \cdot 10^5$ 的 $n$，$f(n) \leq 20$。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的唯一一行包含一个整数 $n$（$2 \le n \le 2 \cdot 10^5$）——Alice 的数字的最大可能值。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

交互开始时，先读取整数 $n$。

然后，输出一个整数 $q$（$1 \leq q \leq 20$）——查询的次数。

要提出一个查询，请按以下格式输出一行：

- $k\,a_1\,a_2 \ldots a_k$（$2 \leq k \leq n$，$k$ 是偶数，$1 \leq a_i \leq n$，$a_i$ 互不相同）——数组的长度和数组本身。

在提出所有 $q$ 次查询后，读取一个字符串 $s$（$|s| = q$）——Alice 对查询的回应，如上所述。

当你确定 Alice 的数字时，输出一个整数 $x$（$1 \leq x \leq n$）——这个数字的值。

然后，继续处理下一个测试用例，如果没有更多测试用例，则终止程序。

在输出所有 $q$ 次查询后，不要忘记输出换行并刷新输出。否则，你将得到 Idleness limit exceeded。为此，请使用：

- C++ 中的 `fflush(stdout)` 或 `cout.flush()`；
- Java 中的 `System.out.flush()`；
- Pascal 中的 `flush(output)`；
- Python 中的 `stdout.flush()`；
- 其他语言的类似方法。

注意，即使你正确猜出了 Alice 的数字，但如果使用的查询次数超过了 $f(n)$，你也会得到 Wrong answer。

本题禁用 hack。

## 说明/提示

在第一个测试用例中，$n = 3$。我们提出了 $2$ 次查询：$[1, 2]$ 和再次的 $[1, 2]$。

- 对于第一次查询，Alice 的回应是 $\texttt{?}$，表示这次查询被忽略。
- 对于第二次查询，Alice 的回应是 $\texttt{N}$，表示她的数字不在数组 $[1, 2]$ 中。

根据以上信息，我们可以确定 Alice 的数字是 $3$。

可以证明，对于 $n = 3$，所有有效策略至少需要 $2$ 次查询。

在第二个测试用例中，$n = 5$。我们提出了 $3$ 次查询：$[3, 2, 4, 1]$、$[5, 4, 3, 1]$ 和 $[1, 5, 3, 4]$。

- 对于第一次查询，Alice 的回应是 $\texttt{R}$，表示她的数字在数组 $[4, 1]$ 中。
- 对于第二次查询，Alice 的回应是 $\texttt{?}$，表示这次查询被忽略。
- 对于第三次查询，Alice 的回应是 $\texttt{L}$，表示她的数字在数组 $[1, 5]$ 中。

根据以上信息，我们可以确定 Alice 的数字是 $1$。

可以证明，对于 $n = 5$，所有有效策略至少需要 $3$ 次查询。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
3



?N

5




R?L
```

### 输出

```
2
2 1 2
2 1 2

3

3
4 3 2 4 1
4 5 4 3 1
4 1 5 3 4

1
```



---

---
title: "Summer Dichotomy"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF538H
tag: ['深度优先搜索 DFS', '二分图', '构造']
---

# Summer Dichotomy

## 题目描述

 $ T $ students applied into the ZPP class of Summer Irrelevant School. The organizing committee of the school may enroll any number of them, but at least $ t $ students must be enrolled. The enrolled students should be divided into two groups in any manner (it is possible that one of the groups will be empty!)

During a shift the students from the ZPP grade are tutored by $ n $ teachers. Due to the nature of the educational process, each of the teachers should be assigned to exactly one of two groups (it is possible that no teacher will be assigned to some of the groups!). The $ i $ -th teacher is willing to work in a group as long as the group will have at least $ l_{i} $ and at most $ r_{i} $ students (otherwise it would be either too boring or too hard). Besides, some pairs of the teachers don't like each other other and therefore can not work in the same group; in total there are $ m $ pairs of conflicting teachers.

You, as the head teacher of Summer Irrelevant School, have got a difficult task: to determine how many students to enroll in each of the groups and in which group each teacher will teach.

## 输入格式

The first line contains two space-separated integers, $ t $ and $ T $ ( $ 1<=t<=T<=10^{9} $ ).

The second line contains two space-separated integers $ n $ and $ m $ ( $ 1<=n<=10^{5} $ , $ 0<=m<=10^{5} $ ).

The $ i $ -th of the next $ n $ lines contain integers $ l_{i} $ and $ r_{i} $ ( $ 0<=l_{i}<=r_{i}<=10^{9} $ ).

The next $ m $ lines describe the pairs of conflicting teachers. Each of these lines contain two space-separated integers — the indices of teachers in the pair. The teachers are indexed starting from one. It is guaranteed that no teacher has a conflict with himself and no pair of conflicting teachers occurs in the list more than once.

## 输出格式

If the distribution is possible, print in the first line a single word 'POSSIBLE' (without the quotes). In the second line print two space-separated integers $ n_{1} $ and $ n_{2} $ — the number of students in the first and second group, correspondingly, the contstraint $ t<=n_{1}+n_{2}<=T $ should be met. In the third line print $ n $ characters, the $ i $ -th of which should be 1 or 2, if the $ i $ -th teacher should be assigned to the first or second group, correspondingly. If there are multiple possible distributions of students and teachers in groups, you can print any of them.

If the sought distribution doesn't exist, print a single word 'IMPOSSIBLE' (without the quotes).

## 样例 #1

### 输入

```
10 20
3 0
3 6
4 9
16 25

```

### 输出

```
POSSIBLE
4 16
112

```

## 样例 #2

### 输入

```
1 10
3 3
0 10
0 10
0 10
1 2
1 3
2 3

```

### 输出

```
IMPOSSIBLE

```



---

