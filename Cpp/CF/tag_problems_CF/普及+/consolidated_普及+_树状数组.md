---
title: "Petya and Array"
layout: "post"
diff: 普及+/提高
pid: CF1042D
tag: ['线段树', '树状数组', '前缀和']
---

# Petya and Array

## 题目描述

Petya has an array $ a $ consisting of $ n $ integers. He has learned partial sums recently, and now he can calculate the sum of elements on any segment of the array really fast. The segment is a non-empty sequence of elements standing one next to another in the array.

Now he wonders what is the number of segments in his array with the sum less than $ t $ . Help Petya to calculate this number.

More formally, you are required to calculate the number of pairs $ l, r $ ( $ l \le r $ ) such that $ a_l + a_{l+1} + \dots + a_{r-1} + a_r < t $ .

## 输入格式

The first line contains two integers $ n $ and $ t $ ( $ 1 \le n \le 200\,000, |t| \le 2\cdot10^{14} $ ).

The second line contains a sequence of integers $ a_1, a_2, \dots, a_n $ ( $ |a_{i}| \le 10^{9} $ ) — the description of Petya's array. Note that there might be negative, zero and positive elements.

## 输出格式

Print the number of segments in Petya's array with the sum of elements less than $ t $ .

## 说明/提示

In the first example the following segments have sum less than $ 4 $ :

- $ [2, 2] $ , sum of elements is $ -1 $
- $ [2, 3] $ , sum of elements is $ 2 $
- $ [3, 3] $ , sum of elements is $ 3 $
- $ [4, 5] $ , sum of elements is $ 3 $
- $ [5, 5] $ , sum of elements is $ -1 $

## 样例 #1

### 输入

```
5 4
5 -1 3 4 -1

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3 0
-1 2 -3

```

### 输出

```
4

```

## 样例 #3

### 输入

```
4 -1
-2 1 -2 3

```

### 输出

```
3

```



---

---
title: "Make It Equal"
layout: "post"
diff: 普及+/提高
pid: CF1065C
tag: ['模拟', '贪心', '树状数组']
---

# Make It Equal

## 题目描述

There is a toy building consisting of $ n $ towers. Each tower consists of several cubes standing on each other. The $ i $ -th tower consists of $ h_i $ cubes, so it has height $ h_i $ .

Let's define operation slice on some height $ H $ as following: for each tower $ i $ , if its height is greater than $ H $ , then remove some top cubes to make tower's height equal to $ H $ . Cost of one "slice" equals to the total number of removed cubes from all towers.

Let's name slice as good one if its cost is lower or equal to $ k $ ( $ k \ge n $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1065C/658a593f32bf5073d4f1a1a7bd7987feaeb4f838.png)Calculate the minimum number of good slices you have to do to make all towers have the same height. Of course, it is always possible to make it so.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ n \le k \le 10^9 $ ) — the number of towers and the restriction on slices, respectively.

The second line contains $ n $ space separated integers $ h_1, h_2, \dots, h_n $ ( $ 1 \le h_i \le 2 \cdot 10^5 $ ) — the initial heights of towers.

## 输出格式

Print one integer — the minimum number of good slices you have to do to make all towers have the same heigth.

## 说明/提示

In the first example it's optimal to make $ 2 $ slices. The first slice is on height $ 2 $ (its cost is $ 3 $ ), and the second one is on height $ 1 $ (its cost is $ 4 $ ).

## 样例 #1

### 输入

```
5 5
3 1 2 2 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 5
2 3 4 5

```

### 输出

```
2

```



---

---
title: "LCIS"
layout: "post"
diff: 普及+/提高
pid: CF10D
tag: ['动态规划 DP', '树状数组', '前缀和']
---

# LCIS

## 题目描述

This problem differs from one which was on the online contest.

The sequence $ a_{1},a_{2},...,a_{n} $ is called increasing, if $ a_{i}<a_{i+1} $ for $ i<n $ .

The sequence $ s_{1},s_{2},...,s_{k} $ is called the subsequence of the sequence $ a_{1},a_{2},...,a_{n} $ , if there exist such a set of indexes $ 1<=i_{1}<i_{2}<...<i_{k}<=n $ that $ a_{ij}=s_{j} $ . In other words, the sequence $ s $ can be derived from the sequence $ a $ by crossing out some elements.

You are given two sequences of integer numbers. You are to find their longest common increasing subsequence, i.e. an increasing sequence of maximum length that is the subsequence of both sequences.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=500 $ ) — the length of the first sequence. The second line contains $ n $ space-separated integers from the range $ [0,10^{9}] $ — elements of the first sequence. The third line contains an integer $ m $ ( $ 1<=m<=500 $ ) — the length of the second sequence. The fourth line contains $ m $ space-separated integers from the range $ [0,10^{9}] $ — elements of the second sequence.

## 输出格式

In the first line output $ k $ — the length of the longest common increasing subsequence. In the second line output the subsequence itself. Separate the elements with a space. If there are several solutions, output any.

## 样例 #1

### 输入

```
7
2 3 1 6 5 4 6
4
1 3 5 6

```

### 输出

```
3
3 5 6 

```

## 样例 #2

### 输入

```
5
1 2 0 2 1
3
1 0 1

```

### 输出

```
2
0 1 

```



---

---
title: "Tyler and Strings"
layout: "post"
diff: 普及+/提高
pid: CF1648C
tag: ['树状数组', '组合数学']
---

# Tyler and Strings

## 题目描述

While looking at the kitchen fridge, the little boy Tyler noticed magnets with symbols, that can be aligned into a string $ s $ .

Tyler likes strings, and especially those that are lexicographically smaller than another string, $ t $ . After playing with magnets on the fridge, he is wondering, how many distinct strings can be composed out of letters of string $ s $ by rearranging them, so that the resulting string is lexicographically smaller than the string $ t $ ? Tyler is too young, so he can't answer this question. The alphabet Tyler uses is very large, so for your convenience he has already replaced the same letters in $ s $ and $ t $ to the same integers, keeping that different letters have been replaced to different integers.

We call a string $ x $ lexicographically smaller than a string $ y $ if one of the followings conditions is fulfilled:

- There exists such position of symbol $ m $ that is presented in both strings, so that before $ m $ -th symbol the strings are equal, and the $ m $ -th symbol of string $ x $ is smaller than $ m $ -th symbol of string $ y $ .
- String $ x $ is the prefix of string $ y $ and $ x \neq y $ .

Because the answer can be too large, print it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 200\,000 $ ) — the lengths of strings $ s $ and $ t $ respectively.

The second line contains $ n $ integers $ s_1, s_2, s_3, \ldots, s_n $ ( $ 1 \le s_i \le 200\,000 $ ) — letters of the string $ s $ .

The third line contains $ m $ integers $ t_1, t_2, t_3, \ldots, t_m $ ( $ 1 \le t_i \le 200\,000 $ ) — letters of the string $ t $ .

## 输出格式

Print a single number — the number of strings lexicographically smaller than $ t $ that can be obtained by rearranging the letters in $ s $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the strings we are interested in are $ [1\, 2\, 2] $ and $ [2\, 1\, 2] $ . The string $ [2\, 2\, 1] $ is lexicographically larger than the string $ [2\, 1\, 2\, 1] $ , so we don't count it.

In the second example, all strings count except $ [4\, 3\, 2\, 1] $ , so the answer is $ 4! - 1 = 23 $ .

In the third example, only the string $ [1\, 1\, 1\, 2] $ counts.

## 样例 #1

### 输入

```
3 4
1 2 2
2 1 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 4
1 2 3 4
4 3 2 1
```

### 输出

```
23
```

## 样例 #3

### 输入

```
4 3
1 1 1 2
1 1 2
```

### 输出

```
1
```



---

---
title: "Reverse Sort Sum"
layout: "post"
diff: 普及+/提高
pid: CF1659D
tag: ['树状数组']
---

# Reverse Sort Sum

## 题目描述

Suppose you had an array $ A $ of $ n $ elements, each of which is $ 0 $ or $ 1 $ .

Let us define a function $ f(k,A) $ which returns another array $ B $ , the result of sorting the first $ k $ elements of $ A $ in non-decreasing order. For example, $ f(4,[0,1,1,0,0,1,0]) = [0,0,1,1,0,1,0] $ . Note that the first $ 4 $ elements were sorted.

Now consider the arrays $ B_1, B_2,\ldots, B_n $ generated by $ f(1,A), f(2,A),\ldots,f(n,A) $ . Let $ C $ be the array obtained by taking the element-wise sum of $ B_1, B_2,\ldots, B_n $ .

For example, let $ A=[0,1,0,1] $ . Then we have $ B_1=[0,1,0,1] $ , $ B_2=[0,1,0,1] $ , $ B_3=[0,0,1,1] $ , $ B_4=[0,0,1,1] $ . Then $ C=B_1+B_2+B_3+B_4=[0,1,0,1]+[0,1,0,1]+[0,0,1,1]+[0,0,1,1]=[0,2,2,4] $ .

You are given $ C $ . Determine a binary array $ A $ that would give $ C $ when processed as above. It is guaranteed that an array $ A $ exists for given $ C $ in the input.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

Each test case has two lines. The first line contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 0 \leq c_i \leq n $ ). It is guaranteed that a valid array $ A $ exists for the given $ C $ .

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line containing $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ a_i $ is $ 0 $ or $ 1 $ ). If there are multiple answers, you may output any of them.

## 说明/提示

Here's the explanation for the first test case. Given that $ A=[1,1,0,1] $ , we can construct each $ B_i $ :

- $ B_1=[\color{blue}{1},1,0,1] $ ;
- $ B_2=[\color{blue}{1},\color{blue}{1},0,1] $ ;
- $ B_3=[\color{blue}{0},\color{blue}{1},\color{blue}{1},1] $ ;
- $ B_4=[\color{blue}{0},\color{blue}{1},\color{blue}{1},\color{blue}{1}] $

 And then, we can sum up each column above to get $ C=[1+1+0+0,1+1+1+1,0+0+1+1,1+1+1+1]=[2,4,2,4] $ .

## 样例 #1

### 输入

```
5
4
2 4 2 4
7
0 3 4 2 3 2 7
3
0 0 0
4
0 0 0 4
3
1 2 3
```

### 输出

```
1 1 0 1 
0 1 1 0 0 0 1 
0 0 0 
0 0 0 1 
1 0 1
```



---

---
title: "Rooks Defenders"
layout: "post"
diff: 普及+/提高
pid: CF1679C
tag: ['线段树', '树状数组']
---

# Rooks Defenders

## 题目描述

You have a square chessboard of size $ n \times n $ . Rows are numbered from top to bottom with numbers from $ 1 $ to $ n $ , and columns — from left to right with numbers from $ 1 $ to $ n $ . So, each cell is denoted with pair of integers $ (x, y) $ ( $ 1 \le x, y \le n $ ), where $ x $ is a row number and $ y $ is a column number.

You have to perform $ q $ queries of three types:

- Put a new rook in cell $ (x, y) $ .
- Remove a rook from cell $ (x, y) $ . It's guaranteed that the rook was put in this cell before.
- Check if each cell of subrectangle $ (x_1, y_1) - (x_2, y_2) $ of the board is attacked by at least one rook.

Subrectangle is a set of cells $ (x, y) $ such that for each cell two conditions are satisfied: $ x_1 \le x \le x_2 $ and $ y_1 \le y \le y_2 $ .

Recall that cell $ (a, b) $ is attacked by a rook placed in cell $ (c, d) $ if either $ a = c $ or $ b = d $ . In particular, the cell containing a rook is attacked by this rook.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n \le 10^5 $ , $ 1 \le q \le 2 \cdot 10^5 $ ) — the size of the chessboard and the number of queries, respectively.

Each of the following $ q $ lines contains description of a query. Description begins with integer $ t $ ( $ t \in \{1, 2, 3\} $ ) which denotes type of a query:

- If $ t = 1 $ , two integers $ x $ and $ y $ follows ( $ 1 \le x, y \le n $ ) — coordinated of the cell where the new rook should be put in. It's guaranteed that there is no rook in the cell $ (x, y) $ at the moment of the given query.
- If $ t = 2 $ , two integers $ x $ and $ y $ follows ( $ 1 \le x, y \le n $ ) — coordinates of the cell to remove a rook from. It's guaranteed that there is a rook in the cell $ (x, y) $ at the moment of the given query.
- If $ t = 3 $ , four integers $ x_1, y_1, x_2 $ and $ y_2 $ follows ( $ 1 \le x_1 \le x_2 \le n $ , $ 1 \le y_1 \le y_2 \le n $ ) — subrectangle to check if each cell of it is attacked by at least one rook.

It's guaranteed that among $ q $ queries there is at least one query of the third type.

## 输出格式

Print the answer for each query of the third type in a separate line. Print "Yes" (without quotes) if each cell of the subrectangle is attacked by at least one rook.

Otherwise print "No" (without quotes).

## 说明/提示

Consider example. After the first two queries the board will look like the following picture (the letter $ R $ denotes cells in which rooks are located, the subrectangle of the query of the third type is highlighted in green):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/ed156665629e711ee2ed4626477b94d3794c1b66.png)Chessboard after performing the third and the fourth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/287c91194903b3f438014966a1c3ab50aa3053b1.png)Chessboard after performing the fifth and the sixth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/2450d8ada954d98a57be494097290cacc9d47393.png)Chessboard after performing the seventh and the eighth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/860ee139e8d85a9e953e6218af254f9a2b04a395.png)Chessboard after performing the last two queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/fa48f4457088559fa8b50c796cacdd0ae0609075.png)

## 样例 #1

### 输入

```
8 10
1 2 4
3 6 2 7 2
1 3 2
3 6 2 7 2
1 4 3
3 2 6 4 8
2 4 3
3 2 6 4 8
1 4 8
3 2 6 4 8
```

### 输出

```
No
Yes
Yes
No
Yes
```



---

---
title: "Alice's Adventures in Cards"
layout: "post"
diff: 普及+/提高
pid: CF2028D
tag: ['动态规划 DP', '树状数组', '最短路']
---

# Alice's Adventures in Cards

## 题目描述

Alice 正在和红心皇后、红心国王以及红心杰克玩纸牌游戏。这个游戏中有 $ n $ 种不同的纸牌类型。Alice 手上现在有一张类型为 $ 1 $ 的纸牌，她需要通过一系列的交换，得到类型为 $ n $ 的纸牌，才能逃出仙境。而其他三名玩家手上各自持有每种类型的纸牌一张。

在这个游戏中，Alice 可以与这些玩家进行纸牌交换。每位玩家对不同类型纸牌的偏好用排列 $ q $、$ k $ 和 $ j $ 来表示，分别对应红心皇后、红心国王和红心杰克。

对于任意玩家，如果在他们的排列 $ p $ 中，满足 $ p_a > p_b $ ，那么该玩家就认为类型为 $ a $ 的纸牌比类型为 $ b $ 的更有价值。于是，他们愿意用类型为 $ b $ 的纸牌换取类型为 $ a $ 的纸牌。而 Alice 的偏好简单直观：纸牌类型 $ a $ 比类型 $ b $ 更有价值，当且仅当 $ a > b $ ，并且她只会按照这种偏好进行交换。

请判断 Alice 能否通过与其他玩家的交换，从类型为 $ 1 $ 的纸牌升级到类型为 $ n $ 的纸牌。如果可以，请给出可能的交换方案。

$ ^{\text{∗}} $ 长度为 $ n $ 的排列是一个包含 $ n $ 个不同整数（从 $ 1 $ 到 $ n $）的数组。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 和 $ [1,3,4] $ 则不是。

## 输入格式

输入包含多个测试用例。第一行给出测试用例的数量 $ t $ （$ 1 \le t \le 10^4 $）。随后是每个测试用例的详细描述。

对于每个测试用例，首先提供一个整数 $ n $ （$ 2 \le n \le 2 \cdot 10^5 $），代表纸牌类型的数量。

接下来的三行分别是红心皇后、红心国王和红心杰克对纸牌的偏好排列。每行包括 $ n $ 个整数 $ p_1, p_2, \ldots, p_n $ （$ 1 \le p_i \le n $），表示每个玩家对纸牌的偏好顺序。

所有测试用例中 $ n $ 的总和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对于每个测试用例，输出一行，写上 "YES" 或 "NO" 来表示 Alice 是否能通过交换得到类型为 $ n $ 的纸牌。

如果可以输出 "YES"，接下来一行输出一个整数 $ k $ ，表示 Alice 将进行的交换次数。随后的 $ k $ 行，每行描述一次交换，以一个字符 $ c \in \{\texttt{q}, \texttt{k}, \texttt{j}\} $ 和一个整数 $ x $ 的形式出现，表示 Alice 与玩家 $ c $ 进行交换，以获得类型为 $ x $ 的纸牌。最终必须确保在第 $ k $ 次交换后，得到的纸牌为类型 $ n $。如果存在多种解决方案，输出任意一个即可。

输出中的字母大小写不固定。例如，"yEs"、"yes"、"Yes" 和 "YES" 都被视为肯定回答。同样，代表玩家的字符 $ c $ 也可以使用大写形式（$\texttt{Q}$、$\texttt{K}$、$\texttt{J}$）。

## 说明/提示

在第一个测试用例中，Alice 可以与红心国王交换以获得类型为 $ 2 $ 的纸牌，接着再与红心皇后交换以得到类型为 $ 3 $ 的纸牌。

在第二个测试用例中，尽管 Alice 能与红心皇后交换得到类型为 $ 3 $ 的纸牌，再接着与红心国王交换得到类型为 $ 2 $，最后与红心杰克交换得到类型为 $ 4 $ 的纸牌，但这种方案不符合 Alice 的偏好原则，因此无效。我们可以证明在这种情况下 Alice 无法获得类型为 $ 4 $ 的纸牌。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
3
1 3 2
2 1 3
1 2 3
4
2 3 1 4
1 2 3 4
1 4 2 3
```

### 输出

```
YES
2
k 2
q 3
NO
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
title: "Misha and Permutations Summation"
layout: "post"
diff: 普及+/提高
pid: CF501D
tag: ['树状数组', '康托展开']
---

# Misha and Permutations Summation

## 题目描述

现在有两个$n$的排列$n$的排列是由0 1 2 ... n − 1
这$n$的数字组成的。对于一个排列$p$，$Order(p)$表示$p$是字典序第$Order(p)$小的排列（从0开始计数）。对于小于 $n!$ 的非负数$x$,$P erm(x)$表示字典序第$x$小的排列。
现在，求两个排列的和。两个排列$p$和$q$的和为$sum =Perm((Order(p) + Order(q))$$%$n!)$

## 输入格式

输入文件第一行一个数字 n，含义如题。

接下来两行，每行 n 个用空格隔开的数字，表示两个排列。

## 输出格式

输出一行 n 个数字，用空格隔开，表示两个排列的和。

## 样例 #1

### 输入

```
2
0 1
0 1

```

### 输出

```
0 1

```

## 样例 #2

### 输入

```
2
0 1
1 0

```

### 输出

```
1 0

```

## 样例 #3

### 输入

```
3
1 2 0
2 1 0

```

### 输出

```
1 0 2

```



---

---
title: "Factory Repairs"
layout: "post"
diff: 普及+/提高
pid: CF627B
tag: ['线段树', '树状数组']
---

# Factory Repairs

## 题目描述

A factory produces thimbles in bulk. Typically, it can produce up to $ a $ thimbles a day. However, some of the machinery is defective, so it can currently only produce $ b $ thimbles each day. The factory intends to choose a $ k $ -day period to do maintenance and construction; it cannot produce any thimbles during this time, but will be restored to its full production of $ a $ thimbles per day after the $ k $ days are complete.

Initially, no orders are pending. The factory receives updates of the form $ d_{i} $ , $ a_{i} $ , indicating that $ a_{i} $ new orders have been placed for the $ d_{i} $ -th day. Each order requires a single thimble to be produced on precisely the specified day. The factory may opt to fill as many or as few of the orders in a single batch as it likes.

As orders come in, the factory owner would like to know the maximum number of orders he will be able to fill if he starts repairs on a given day $ p_{i} $ . Help the owner answer his questions.

## 输入格式

The first line contains five integers $ n $ , $ k $ , $ a $ , $ b $ , and $ q $ ( $ 1<=k<=n<=200000 $ , $ 1<=b&lt;a<=10\ 000 $ , $ 1<=q<=200000 $ ) — the number of days, the length of the repair time, the production rates of the factory, and the number of updates, respectively.

The next $ q $ lines contain the descriptions of the queries. Each query is of one of the following two forms:

- $ 1\ d_{i}\ a_{i} $ ( $ 1<=d_{i}<=n $ , $ 1<=a_{i}<=10\ 000 $ ), representing an update of $ a_{i} $ orders on day $ d_{i} $ , or
- $ 2\ p_{i} $ ( $ 1<=p_{i}<=n-k+1 $ ), representing a question: at the moment, how many orders could be filled if the factory decided to commence repairs on day $ p_{i} $ ?

It's guaranteed that the input will contain at least one query of the second type.

## 输出格式

For each query of the second type, print a line containing a single integer — the maximum number of orders that the factory can fill over all $ n $ days.

## 说明/提示

Consider the first sample.

We produce up to $ 1 $ thimble a day currently and will produce up to $ 2 $ thimbles a day after repairs. Repairs take $ 2 $ days.

For the first question, we are able to fill $ 1 $ order on day $ 1 $ , no orders on days $ 2 $ and $ 3 $ since we are repairing, no orders on day $ 4 $ since no thimbles have been ordered for that day, and $ 2 $ orders for day $ 5 $ since we are limited to our production capacity, for a total of $ 3 $ orders filled.

For the third question, we are able to fill $ 1 $ order on day $ 1 $ , $ 1 $ order on day $ 2 $ , and $ 2 $ orders on day $ 5 $ , for a total of $ 4 $ orders.

## 样例 #1

### 输入

```
5 2 2 1 8
1 1 2
1 5 3
1 2 1
2 2
1 4 2
1 3 2
2 1
2 3

```

### 输出

```
3
6
4

```

## 样例 #2

### 输入

```
5 4 10 1 6
1 1 5
1 5 5
1 3 2
1 5 2
2 1
2 2

```

### 输出

```
7
1

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
title: "Remove Extra One"
layout: "post"
diff: 普及+/提高
pid: CF900C
tag: ['数学', '树状数组']
---

# Remove Extra One

## 题目描述

You are given a permutation $ p $ of length $ n $ . Remove one element from permutation to make the number of records the maximum possible.

We remind that in a sequence of numbers $ a_{1},a_{2},...,a_{k} $ the element $ a_{i} $ is a record if for every integer $ j $ ( $ 1<=j&lt;i $ ) the following holds: $ a_{j}&lt;a_{i} $ .

## 输入格式

The first line contains the only integer $ n $ ( $ 1<=n<=10^{5} $ ) — the length of the permutation.

The second line contains $ n $ integers $ p_{1},p_{2},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — the permutation. All the integers are distinct.

## 输出格式

Print the only integer — the element that should be removed to make the number of records the maximum possible. If there are multiple such elements, print the smallest one.

## 说明/提示

In the first example the only element can be removed.

## 样例 #1

### 输入

```
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
5
5 1 2 3 4

```

### 输出

```
5

```



---

---
title: "Inversion Counting"
layout: "post"
diff: 普及+/提高
pid: CF911D
tag: ['数学', '平衡树', '树状数组']
---

# Inversion Counting

## 题目描述

A permutation of size $ n $ is an array of size $ n $ such that each integer from $ 1 $ to $ n $ occurs exactly once in this array. An inversion in a permutation $ p $ is a pair of indices $ (i,j) $ such that $ i>j $ and $ a_{i}<a_{j} $ . For example, a permutation $ [4,1,3,2] $ contains $ 4 $ inversions: $ (2,1) $ , $ (3,1) $ , $ (4,1) $ , $ (4,3) $ .

You are given a permutation $ a $ of size $ n $ and $ m $ queries to it. Each query is represented by two indices $ l $ and $ r $ denoting that you have to reverse the segment $ [l,r] $ of the permutation. For example, if $ a=[1,2,3,4] $ and a query $ l=2 $ , $ r=4 $ is applied, then the resulting permutation is $ [1,4,3,2] $ .

After each query you have to determine whether the number of inversions is odd or even.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=1500 $ ) — the size of the permutation.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=n $ ) — the elements of the permutation. These integers are pairwise distinct.

The third line contains one integer $ m $ ( $ 1<=m<=2·10^{5} $ ) — the number of queries to process.

Then $ m $ lines follow, $ i $ -th line containing two integers $ l_{i} $ , $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) denoting that $ i $ -th query is to reverse a segment $ [l_{i},r_{i}] $ of the permutation. All queries are performed one after another.

## 输出格式

Print $ m $ lines. $ i $ -th of them must be equal to odd if the number of inversions in the permutation after $ i $ -th query is odd, and even otherwise.

## 说明/提示

The first example:

1. after the first query $ a=[2,1,3] $ , inversion: $ (2,1) $ ;
2. after the second query $ a=[2,3,1] $ , inversions: $ (3,1) $ , $ (3,2) $ .

The second example:

1. $ a=[1,2,4,3] $ , inversion: $ (4,3) $ ;
2. $ a=[3,4,2,1] $ , inversions: $ (3,1) $ , $ (4,1) $ , $ (3,2) $ , $ (4,2) $ , $ (4,3) $ ;
3. $ a=[1,2,4,3] $ , inversion: $ (4,3) $ ;
4. $ a=[1,4,2,3] $ , inversions: $ (3,2) $ , $ (4,2) $ .

## 样例 #1

### 输入

```
3
1 2 3
2
1 2
2 3

```

### 输出

```
odd
even

```

## 样例 #2

### 输入

```
4
1 2 4 3
4
1 1
1 4
1 4
2 3

```

### 输出

```
odd
odd
odd
even

```



---

---
title: "A Leapfrog in the Array"
layout: "post"
diff: 普及+/提高
pid: CF949B
tag: ['数学', '树状数组', '进制']
---

# A Leapfrog in the Array

## 题目描述

## 题意:
Dima是一名初级程序员。 在他的工作中，他经常不断地重复以下操作：从数组中删除每个第二个元素。 有一天，他对这个问题的解决方案感到厌倦，他提出了以下华丽的算法。

假设有一长度为2n的数组，最初的数组包含从1到n的n个数字，数字i位于序号为2i - 1的单元格中（序号从1开始编号），并且数组的其他单元格为空。每个步骤你需要选择一个最大序号的非空单元格，并将其中的数字移动到它左边最近的空单元格。一直循环该过程，直到所有n个数字出现在数组的前n个单元格中。例如，如果n = 4，则数组更改如下：
![这里写图片描述](http://codeforces.com/predownloaded/1e/83/1e838f4fb99d933b7259fbfe5b8722990c08d718.png)
您必须编写一个程序，输出在该算法完成后，序号为x（1≤x≤n）的单元格中的数字。

## 输入格式

第一行包含两个整数n和q（1≤n≤1e18，1≤q≤200 000），数组中元素的数量以及查询数量。

接下来的q行包含一个整数xi（1≤xi≤n），xi为算法完成后，第xi个单元格。

## 输出格式

对于q个查询中的每一个，输出一个整数，即相应数组单元格中的值。

## 样例:
```
inputCopy
4 3
2
3
4
outputCopy
3
2
4
```
```
inputCopy
13 4
10
5
4
8
outputCopy
13
3
8
9
```
翻译提供者：xjdx

## 样例 #1

### 输入

```
4 3
2
3
4

```

### 输出

```
3
2
4

```

## 样例 #2

### 输入

```
13 4
10
5
4
8

```

### 输出

```
13
3
8
9

```



---

