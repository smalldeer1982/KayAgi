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
title: "Split the Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1059E
tag: ['动态规划 DP', '倍增']
---

# Split the Tree

## 题目描述

You are given a rooted tree on $ n $ vertices, its root is the vertex number $ 1 $ . The $ i $ -th vertex contains a number $ w_i $ . Split it into the minimum possible number of vertical paths in such a way that each path contains no more than $ L $ vertices and the sum of integers $ w_i $ on each path does not exceed $ S $ . Each vertex should belong to exactly one path.

A vertical path is a sequence of vertices $ v_1, v_2, \ldots, v_k $ where $ v_i $ ( $ i \ge 2 $ ) is the parent of $ v_{i - 1} $ .

## 输入格式

The first line contains three integers $ n $ , $ L $ , $ S $ ( $ 1 \le n \le 10^5 $ , $ 1 \le L \le 10^5 $ , $ 1 \le S \le 10^{18} $ ) — the number of vertices, the maximum number of vertices in one path and the maximum sum in one path.

The second line contains $ n $ integers $ w_1, w_2, \ldots, w_n $ ( $ 1 \le w_i \le 10^9 $ ) — the numbers in the vertices of the tree.

The third line contains $ n - 1 $ integers $ p_2, \ldots, p_n $ ( $ 1 \le p_i < i $ ), where $ p_i $ is the parent of the $ i $ -th vertex in the tree.

## 输出格式

Output one number — the minimum number of vertical paths. If it is impossible to split the tree, output $ -1 $ .

## 说明/提示

In the first sample the tree is split into $ \{1\},\ \{2\},\ \{3\} $ .

In the second sample the tree is split into $ \{1,\ 2\},\ \{3\} $ or $ \{1,\ 3\},\ \{2\} $ .

In the third sample it is impossible to split the tree.

## 样例 #1

### 输入

```
3 1 3
1 2 3
1 1

```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 3 6
1 2 3
1 1

```

### 输出

```
2
```

## 样例 #3

### 输入

```
1 1 10000
10001

```

### 输出

```
-1
```



---

---
title: "Segment Sum"
layout: "post"
diff: 省选/NOI-
pid: CF1073E
tag: ['动态规划 DP', '数位 DP', '状态合并']
---

# Segment Sum

## 题目描述

You are given two integers $ l $ and $ r $ ( $ l \le r $ ). Your task is to calculate the sum of numbers from $ l $ to $ r $ (including $ l $ and $ r $ ) such that each number contains at most $ k $ different digits, and print this sum modulo $ 998244353 $ .

For example, if $ k = 1 $ then you have to calculate all numbers from $ l $ to $ r $ such that each number is formed using only one digit. For $ l = 10, r = 50 $ the answer is $ 11 + 22 + 33 + 44 = 110 $ .

## 输入格式

The only line of the input contains three integers $ l $ , $ r $ and $ k $ ( $ 1 \le l \le r < 10^{18}, 1 \le k \le 10 $ ) — the borders of the segment and the maximum number of different digits.

## 输出格式

Print one integer — the sum of numbers from $ l $ to $ r $ such that each number contains at most $ k $ different digits, modulo $ 998244353 $ .

## 说明/提示

For the first example the answer is just the sum of numbers from $ l $ to $ r $ which equals to $ \frac{50 \cdot 51}{2} - \frac{9 \cdot 10}{2} = 1230 $ . This example also explained in the problem statement but for $ k = 1 $ .

For the second example the answer is just the sum of numbers from $ l $ to $ r $ which equals to $ \frac{2345 \cdot 2346}{2} = 2750685 $ .

For the third example the answer is $ 101 + 110 + 111 + 112 + 113 + 114 + 115 + 116 + 117 + 118 + 119 + 121 + 122 + 131 + 133 + 141 + 144 + 151 = 2189 $ .

## 样例 #1

### 输入

```
10 50 2

```

### 输出

```
1230

```

## 样例 #2

### 输入

```
1 2345 10

```

### 输出

```
2750685

```

## 样例 #3

### 输入

```
101 154 2

```

### 输出

```
2189

```



---

---
title: "Satanic Panic"
layout: "post"
diff: 省选/NOI-
pid: CF1146H
tag: ['动态规划 DP', '计算几何', '区间 DP']
---

# Satanic Panic

## 题目描述

You are given a set of $ n $ points in a 2D plane. No three points are collinear.

A pentagram is a set of $ 5 $ points $ A,B,C,D,E $ that can be arranged as follows. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/f942ae06c7e29cb9bc6462315be09bb7d5b4c362.png) Note the length of the line segments don't matter, only that those particular intersections exist.

Count the number of ways to choose $ 5 $ points from the given set that form a pentagram.

## 输入格式

The first line contains an integer $ n $ ( $ 5 \leq n \leq 300 $ ) — the number of points.

Each of the next $ n $ lines contains two integers $ x_i, y_i $ ( $ -10^6 \leq x_i,y_i \leq 10^6 $ ) — the coordinates of the $ i $ -th point. It is guaranteed that no three points are collinear.

## 输出格式

Print a single integer, the number of sets of $ 5 $ points that form a pentagram.

## 说明/提示

A picture of the first sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/ecb5db206846ce3b41c177fcaeaebe0ee2b1bb2a.png) A picture of the second sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/4f7f38f01a0904403461b302f8dc7d443ccc0e93.png) A picture of the third sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/d922b8e812b7b67b3a0bbbb474a47be87ee53781.png)

## 样例 #1

### 输入

```
5
0 0
0 2
2 0
2 2
1 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
0 0
4 0
0 4
4 4
2 3

```

### 输出

```
0

```

## 样例 #3

### 输入

```
10
841746 527518
595261 331297
-946901 129987
670374 -140388
-684770 309555
-302589 415564
-387435 613331
-624940 -95922
945847 -199224
24636 -565799

```

### 输出

```
85

```



---

---
title: "GCD Groups 2"
layout: "post"
diff: 省选/NOI-
pid: CF1198F
tag: ['动态规划 DP', '状态合并', '随机化']
---

# GCD Groups 2

## 题目描述

You are given an array of $ n $ integers. You need to split all integers into two groups so that the GCD of all integers in the first group is equal to one and the GCD of all integers in the second group is equal to one.

The GCD of a group of integers is the largest non-negative integer that divides all the integers in the group.

Both groups have to be non-empty.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \leq n \leq 10^5 $ ).

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , $ \ldots $ , $ a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the elements of the array.

## 输出格式

In the first line print "YES" (without quotes), if it is possible to split the integers into two groups as required, and "NO" (without quotes) otherwise.

If it is possible to split the integers, in the second line print $ n $ integers, where the $ i $ -th integer is equal to $ 1 $ if the integer $ a_i $ should be in the first group, and $ 2 $ otherwise.

If there are multiple solutions, print any.

## 样例 #1

### 输入

```
4
2 3 6 7

```

### 输出

```
YES
2 2 1 1 

```

## 样例 #2

### 输入

```
5
6 15 35 77 22

```

### 输出

```
YES
2 1 2 1 1 

```

## 样例 #3

### 输入

```
5
6 10 15 1000 75

```

### 输出

```
NO

```



---

---
title: "You Are Given Some Strings..."
layout: "post"
diff: 省选/NOI-
pid: CF1202E
tag: ['字符串', '动态规划 DP', 'AC 自动机']
---

# You Are Given Some Strings...

## 题目描述

You are given a string $ t $ and $ n $ strings $ s_1, s_2, \dots, s_n $ . All strings consist of lowercase Latin letters.

Let $ f(t, s) $ be the number of occurences of string $ s $ in string $ t $ . For example, $ f('\text{aaabacaa}', '\text{aa}') = 3 $ , and $ f('\text{ababa}', '\text{aba}') = 2 $ .

Calculate the value of $ \sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} f(t, s_i + s_j) $ , where $ s + t $ is the concatenation of strings $ s $ and $ t $ . Note that if there are two pairs $ i_1 $ , $ j_1 $ and $ i_2 $ , $ j_2 $ such that $ s_{i_1} + s_{j_1} = s_{i_2} + s_{j_2} $ , you should include both $ f(t, s_{i_1} + s_{j_1}) $ and $ f(t, s_{i_2} + s_{j_2}) $ in answer.

## 输入格式

The first line contains string $ t $ ( $ 1 \le |t| \le 2 \cdot 10^5 $ ).

The second line contains integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ).

Each of next $ n $ lines contains string $ s_i $ ( $ 1 \le |s_i| \le 2 \cdot 10^5 $ ).

It is guaranteed that $ \sum\limits_{i=1}^{n} |s_i| \le 2 \cdot 10^5 $ . All strings consist of lowercase English letters.

## 输出格式

Print one integer — the value of $ \sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} f(t, s_i + s_j) $ .

## 样例 #1

### 输入

```
aaabacaa
2
a
aa

```

### 输出

```
5

```

## 样例 #2

### 输入

```
aaabacaa
4
a
a
a
b

```

### 输出

```
33

```



---

---
title: "Emotional Fishermen"
layout: "post"
diff: 省选/NOI-
pid: CF1437F
tag: ['动态规划 DP', '组合数学']
---

# Emotional Fishermen

## 题目描述

$ n $ fishermen have just returned from a fishing vacation. The $ i $ -th fisherman has caught a fish of weight $ a_i $ .

Fishermen are going to show off the fish they caught to each other. To do so, they firstly choose an order in which they show their fish (each fisherman shows his fish exactly once, so, formally, the order of showing fish is a permutation of integers from $ 1 $ to $ n $ ). Then they show the fish they caught according to the chosen order. When a fisherman shows his fish, he might either become happy, become sad, or stay content.

Suppose a fisherman shows a fish of weight $ x $ , and the maximum weight of a previously shown fish is $ y $ ( $ y = 0 $ if that fisherman is the first to show his fish). Then:

- if $ x \ge 2y $ , the fisherman becomes happy;
- if $ 2x \le y $ , the fisherman becomes sad;
- if none of these two conditions is met, the fisherman stays content.

Let's call an order in which the fishermen show their fish emotional if, after all fishermen show their fish according to this order, each fisherman becomes either happy or sad. Calculate the number of emotional orders modulo $ 998244353 $ .

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 5000 $ ).

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ ( $ 1 \le a_i \le 10^9 $ ).

## 输出格式

Print one integer — the number of emotional orders, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
1 1 4 9
```

### 输出

```
20
```

## 样例 #2

### 输入

```
4
4 3 2 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
4 2 1
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
42 1337 13 37 420 666 616 97
```

### 输出

```
19200
```



---

---
title: "Lanterns"
layout: "post"
diff: 省选/NOI-
pid: CF1476F
tag: ['动态规划优化']
---

# Lanterns

## 题目描述

有 $n$ 个灯笼拍成一排，第 $i$ 个灯笼具有 $p_i$ 的亮度。每个灯笼要么朝向左，照亮左边编号为 $[i - p_i,i - 1]$ 的灯笼，要么朝向右，照亮右边编号为 $[i + 1, i + p_i]$ 的灯笼。

寻找一种方案，为所有的灯笼确定朝向，使得每一个灯笼被至少一个其他灯笼照亮。

## 输入格式

第一行一个正整数表示数据组数 $t$。

每组数据包含两行。第一行为一个正整数 $n$，表示灯笼的个数。

第二行 $n$ 个整数 $p_i$，表示各个灯笼的亮度。

## 输出格式

对于每组数据，如果存在方案，在第一行输出字符串 $\texttt{YES}$，并在下一行给出一个长度为 $n$ 的仅由 $\texttt L$ 和 $\texttt R$ 组成的字符串，描述灯笼的方向。多解输出任意解。无解输出 $\texttt{NO}$。

## 说明/提示

$1\le t \le 1\times 10^4$。对于每组数据，有 $2\le n\le 3\times 10^5,0\le p_i\le n$。同一个测试点内保证 $\sum n\le 3\times 10^5$。

## 样例 #1

### 输入

```
4
8
0 0 3 1 1 1 1 2
2
1 1
2
2 2
2
0 1
```

### 输出

```
YES
RRLLLLRL
YES
RL
YES
RL
NO
```



---

---
title: "Keep XOR Low"
layout: "post"
diff: 省选/NOI-
pid: CF1616H
tag: ['动态规划 DP', '字典树 Trie']
---

# Keep XOR Low

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ and an integer $ x $ .

Find the number of non-empty subsets of indices of this array $ 1 \leq b_1 < b_2 < \ldots < b_k \leq n $ , such that for all pairs $ (i, j) $ where $ 1 \leq i < j \leq k $ , the inequality $ a_{b_i} \oplus a_{b_j} \leq x $ is held. Here, $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). As the answer may be very large, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ x $ ( $ 1 \leq n \leq 150\,000 $ , $ 0 \leq x < 2^{30} $ ). Here, $ n $ is the size of the array.

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < 2^{30} $ ): the array itself.

## 输出格式

Print one integer: the number of non-empty subsets such that the bitwise XOR of every pair of elements is at most $ x $ , modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
4 2
0 1 2 3
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3 6
4 2 2
```

### 输出

```
7
```

## 样例 #3

### 输入

```
4 0
1 1 2 2
```

### 输出

```
6
```



---

---
title: "A Random Code Problem"
layout: "post"
diff: 省选/NOI-
pid: CF1626F
tag: ['动态规划 DP', '状态合并', '组合数学']
---

# A Random Code Problem

## 题目描述

给你一个数组 $a$ 和一个整数 $k$ ，执行下面的代码：
```cpp
long long ans = 0; //定义一个初始值为 0 的长整型变量
for(int i = 1; i <= k; i++) {
	int idx = rnd.next(0, n - 1); //生成一个介于0到n-1的随机数（含 0 和 n-1）
  								 //每个数被选中的概率是相同的
	ans += a[idx];
	a[idx] -= (a[idx] % i);
}
```
您需要在执行此代码后计算变量 $ans$ 的期望。

数组 $a$ 是输入时根据特殊规则生成的。

## 输入格式

仅一行，六个整数 $n$ , $a_0$ , $x$ , $y$ , $k$ 和 $M$ 。

数组 $a$ 由以下规则生成：

* $a_0$ 由输入给出
* 对于 $a_1$ 至 $a_{n-1}$，$a_i=(a_{i-1}\times x+y)\bmod M$。

## 输出格式

令 $E$ 为 $ans$ 的期望，输出 $E\times n^k$，对 $998244353$ 取模。

## 说明/提示

$1\le n\le10^7$

$1\le a_0,x,y<M\le998244353$

$1\le k\le17$

## 样例 #1

### 输入

```
3 10 3 5 13 88
```

### 输出

```
382842030
```

## 样例 #2

### 输入

```
2 15363 270880 34698 17 2357023
```

### 输出

```
319392398
```



---

---
title: "Serious Business"
layout: "post"
diff: 省选/NOI-
pid: CF1648D
tag: ['动态规划 DP', '线段树', '动态规划优化']
---

# Serious Business

## 题目描述

Dima is taking part in a show organized by his friend Peter. In this show Dima is required to cross a $ 3 \times n $ rectangular field. Rows are numbered from $ 1 $ to $ 3 $ and columns are numbered from $ 1 $ to $ n $ .

The cell in the intersection of the $ i $ -th row and the $ j $ -th column of the field contains an integer $ a_{i,j} $ . Initially Dima's score equals zero, and whenever Dima reaches a cell in the row $ i $ and the column $ j $ , his score changes by $ a_{i,j} $ . Note that the score can become negative.

Initially all cells in the first and the third row are marked as available, and all cells in the second row are marked as unavailable. However, Peter offered Dima some help: there are $ q $ special offers in the show, the $ i $ -th special offer allows Dima to mark cells in the second row between $ l_i $ and $ r_i $ as available, though Dima's score reduces by $ k_i $ whenever he accepts a special offer. Dima is allowed to use as many special offers as he wants, and might mark the same cell as available multiple times.

Dima starts his journey in the cell $ (1, 1) $ and would like to reach the cell $ (3, n) $ . He can move either down to the next row or right to the next column (meaning he could increase the current row or column by 1), thus making $ n + 1 $ moves in total, out of which exactly $ n - 1 $ would be horizontal and $ 2 $ would be vertical.

Peter promised Dima to pay him based on his final score, so the sum of all numbers of all visited cells minus the cost of all special offers used. Please help Dima to maximize his final score.

## 输入格式

The first input line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 500\,000 $ ) — the number of columns in the field and the number of special offers.

The next three lines describe the field, $ i $ -th of them contains $ n $ integers $ a_{i1} $ , $ a_{i2} $ , ..., $ a_{in} $ ( $ -10^9 \le a_{ij} \le 10^9) $ — the values in the $ i $ -th row.

The next $ q $ lines describe special offers: the $ i $ -th offer is described by 3 integers $ l_i $ , $ r_i $ and $ k_i $ ( $ 1 \leq l_i \leq r_i \leq n $ , $ 1\leq k_i\leq 10^9 $ ) — the segment that becomes unblocked and the cost of this special offer.

## 输出格式

Output one integer — the maximum final score Dima can achieve.

## 说明/提示

In the first example, it is optimal to use Peter's second offer of $ 4 $ rubles and go through the cells $ (1, 1) $ , $ (1, 2) $ , $ (1, 3) $ , $ (2, 3) $ , $ (3, 3) $ , $ (3, 4) $ , earning $ 1 + 0 + 2 + 9 + 4 + 1 - 4 = 13 $ rubles in total.

In the second example, it is optimal to use Peter's second and third offers of $ 2 $ and $ 3 $ rubles, respectively, and go through the cells $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (2, 4) $ , $ (3, 4) $ , $ (3, 5) $ , earning $ -20 + 1 + 3 + 3 + 6 + 6 + 2 - 2 - 3= -4 $ rubles.

## 样例 #1

### 输入

```
4 3
1 0 2 -1
-3 1 9 2
3 2 4 1
1 2 5
2 3 4
1 4 14
```

### 输出

```
13
```

## 样例 #2

### 输入

```
5 4
-20 -10 -11 -10 1
1 3 3 6 3
14 -20 3 6 2
1 5 13
1 2 2
3 5 3
2 3 1
```

### 输出

```
-4
```



---

---
title: "Centroid Probabilities"
layout: "post"
diff: 省选/NOI-
pid: CF1667E
tag: ['动态规划 DP', '快速傅里叶变换 FFT']
---

# Centroid Probabilities

## 题目描述

Consider every tree (connected undirected acyclic graph) with $ n $ vertices ( $ n $ is odd, vertices numbered from $ 1 $ to $ n $ ), and for each $ 2 \le i \le n $ the $ i $ -th vertex is adjacent to exactly one vertex with a smaller index.

For each $ i $ ( $ 1 \le i \le n $ ) calculate the number of trees for which the $ i $ -th vertex will be the centroid. The answer can be huge, output it modulo $ 998\,244\,353 $ .

A vertex is called a centroid if its removal splits the tree into subtrees with at most $ (n-1)/2 $ vertices each.

## 输入格式

The first line contains an odd integer $ n $ ( $ 3 \le n < 2 \cdot 10^5 $ , $ n $ is odd) — the number of the vertices in the tree.

## 输出格式

Print $ n $ integers in a single line, the $ i $ -th integer is the answer for the $ i $ -th vertex (modulo $ 998\,244\,353 $ ).

## 说明/提示

Example $ 1 $ : there are two possible trees: with edges $ (1-2) $ , and $ (1-3) $ — here the centroid is $ 1 $ ; and with edges $ (1-2) $ , and $ (2-3) $ — here the centroid is $ 2 $ . So the answer is $ 1, 1, 0 $ .

Example $ 2 $ : there are $ 24 $ possible trees, for example with edges $ (1-2) $ , $ (2-3) $ , $ (3-4) $ , and $ (4-5) $ . Here the centroid is $ 3 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
1 1 0
```

## 样例 #2

### 输入

```
5
```

### 输出

```
10 10 4 0 0
```

## 样例 #3

### 输入

```
7
```

### 输出

```
276 276 132 36 0 0 0
```



---

---
title: "Typical Party in Dorm"
layout: "post"
diff: 省选/NOI-
pid: CF1679E
tag: ['动态规划 DP']
---

# Typical Party in Dorm

## 题目描述

Today is a holiday in the residence hall — Oleh arrived, in honor of which the girls gave him a string. Oleh liked the gift a lot, so he immediately thought up and offered you, his best friend, the following problem.

You are given a string $ s $ of length $ n $ , which consists of the first $ 17 $ lowercase Latin letters { $ a $ , $ b $ , $ c $ , $ \ldots $ , $ p $ , $ q $ } and question marks. And $ q $ queries. Each query is defined by a set of pairwise distinct lowercase first $ 17 $ letters of the Latin alphabet, which can be used to replace the question marks in the string $ s $ .

The answer to the query is the sum of the number of distinct substrings that are palindromes over all strings that can be obtained from the original string $ s $ by replacing question marks with available characters. The answer must be calculated modulo $ 998\,244\,353 $ .

Pay attention! Two substrings are different when their start and end positions in the string are different. So, the number of different substrings that are palindromes for the string aba will be $ 4 $ : a, b, a, aba.

Consider examples of replacing question marks with letters. For example, from the string aba??ee when querying { $ a $ , $ b $ } you can get the strings ababaee or abaaaee but you cannot get the strings pizza,  abaee, abacaba, aba?fee, aba47ee, or abatree.

Recall that a palindrome is a string that reads the same from left to right as from right to left.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 1\,000 $ ) — the length of the string $ s $ .

The second line contains the string $ s $ , which consists of $ n $ lowercase Latin letters and question marks. It is guaranteed that all letters in the string belong to the set { $ a $ , $ b $ , $ c $ , $ \ldots $ , $ p $ , $ q $ }.

The third line contains a single integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of queries.

This is followed by $ q $ lines, each containing a single line $ t $ — a set of characters that can replace question marks ( $ 1 \le |t| \le 17 $ ). It is guaranteed that all letters in the string belong to the set { $ a $ , $ b $ , $ c $ , $ \ldots $ , $ p $ , $ q $ } and occur at most once.

## 输出格式

For each query print one number — the total numbers of palindromic substrings in all strings that can be obtained from the string $ s $ , modulo $ 998\,244\,353 $ .

## 说明/提示

Consider the first example and the first query in it. We can get only one string as a result of replacing the question marks — abaaaba. It has the following palindrome substrings:

1. a — substring \[ $ 1 $ ; $ 1 $ \].
2. b — substring \[ $ 2 $ ; $ 2 $ \].
3. a — substring \[ $ 3 $ ; $ 3 $ \].
4. a — substring \[ $ 4 $ ; $ 4 $ \].
5. a — substring \[ $ 5 $ ; $ 5 $ \].
6. b — substring \[ $ 6 $ ; $ 6 $ \].
7. a — substring \[ $ 7 $ ; $ 7 $ \].
8. aa — substring \[ $ 3 $ ; $ 4 $ \].
9. aa — substring \[ $ 4 $ ; $ 5 $ \].
10. aba — substring \[ $ 1 $ ; $ 3 $ \].
11. aaa — substring \[ $ 3 $ ; $ 5 $ \].
12. aba — substring \[ $ 5 $ ; $ 7 $ \].
13. baaab — substring \[ $ 2 $ ; $ 6 $ \].
14. abaaaba — substring \[ $ 1 $ ; $ 7 $ \].

In the third request, we get 4 lines: abaaaba, abababa, abbaaba, abbbaba.

## 样例 #1

### 输入

```
7
ab??aba
8
a
b
ab
abc
abcd
abcde
abcdef
abcdefg
```

### 输出

```
14
13
55
105
171
253
351
465
```

## 样例 #2

### 输入

```
11
???????????
6
abcdefghijklmnopq
ecpnkhbmlidgfjao
olehfan
codef
glhf
q
```

### 输出

```
900057460
712815817
839861037
756843750
70840320
66
```



---

---
title: "Formalism for Formalism"
layout: "post"
diff: 省选/NOI-
pid: CF1679F
tag: ['动态规划 DP', '状态合并']
---

# Formalism for Formalism

## 题目描述

### 题意简述

给出正整数 $n$，所有不足 $n$ 位（十进制）的数用前导零补充。

给出 $m$ 组**无序**数对 $(u_i,v_i)$，若一个数字的相邻两位数 $x,y$ 满足 $(x,y)$ 存在于这 $m$ 组数对中，则可以交换 $x,y$ 的位置。若 $A$ 可以通过若干次（包含零次）交换得到 $B$，则认为 $A$ 和 $B$ 是等价的。

求出最大整数 $k$，使得存在一组非负整数 $x_1,x_2,\ldots,x_k(0\leq x_i<10^n)$ 满足对于任意 $1\leq i<j\leq k$，$x_i$ 与 $x_j$ 不等价。

## 输入格式

第一行一个整数 $n(1\leq n\leq 50000)$，含义如题面所述。

第二行一个整数 $m(0\leq m\leq 45)$，表示数对数。

接下来 $m$ 行，每行一个无序数对 $(u_i,v_i)(0\leq u_i,v_i\leq 9)$，保证任意两组数对不相同。

## 输出格式

输出一个整数 $k$，含义如题面所述。

由于答案可能会很大，你需要输出答案对 $998244353$ 取模的值。

## 样例 #1

### 输入

```
1
0
```

### 输出

```
10
```

## 样例 #2

### 输入

```
2
1
0 1
```

### 输出

```
99
```

## 样例 #3

### 输入

```
2
9
0 1
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
```

### 输出

```
91
```



---

---
title: "Labyrinth Adventures"
layout: "post"
diff: 省选/NOI-
pid: CF1681E
tag: ['动态规划 DP', '图论', '倍增', 'O2优化']
---

# Labyrinth Adventures

## 题目描述

有一个 $n\times n$ 的方格图，坐标编号类似平面直角坐标系，左下角为 $(1, 1)$。

这个方格图被分成了 $n$ 层，左下角 $(1, 1)$ 为第一层，随后每层都向外拓展一圈，如下图就是 $n=5$ 的时候的情况：

![](https://espresso.codeforces.com/003bbba1ff0347bde56714b878262c5fe414679d.png)

层与层之间有墙隔开，但每层都有两个门，分别分布在该层顶部和右侧，门是双向的。

现在给出这些门的坐标，有 $m$ 次询问，每次给定两个坐标 $(x_1, y_1)$ 和 $(x_2,y_2)$，请你回答两点之间的最短路。

## 输入格式

第一行一个 $n$。

接下来的 $n-1$ 行中，每行有四个整数 $d_{1,x}, d_{1,y}, d_{2,x}, d_{2,y}$，第 $i$ 行表示第 $i$ 层的两个门的坐标。前两个表示顶部门坐标，后两个表示右侧门坐标。

下一行输入 $m$。

## 输出格式

对每次询问，输出一行一个整数，表示两点之间的最短路长度。**长度的定义是移动的步数。**

#### 样例解释

下图是样例二的网格图，红色的是门。

![](https://espresso.codeforces.com/522ad0e61c0b740a60c9203c9178279992c8ab2e.png)

## 样例 #1

### 输入

```
2
1 1 1 1
10
1 1 1 1
1 1 1 2
1 1 2 1
1 1 2 2
1 2 1 2
1 2 2 1
1 2 2 2
2 1 2 1
2 1 2 2
2 2 2 2
```

### 输出

```
0
1
1
2
0
2
1
0
1
0
```

## 样例 #2

### 输入

```
4
1 1 1 1
2 1 2 2
3 2 1 3
5
2 4 4 3
4 4 3 3
1 2 3 3
2 2 4 4
1 4 2 3
```

### 输出

```
3
4
3
6
2
```



---

---
title: "Coloring"
layout: "post"
diff: 省选/NOI-
pid: CF1697E
tag: ['动态规划 DP', '图论', '组合数学']
---

# Coloring

## 题目描述

You are given $ n $ points on the plane, the coordinates of the $ i $ -th point are $ (x_i, y_i) $ . No two points have the same coordinates.

The distance between points $ i $ and $ j $ is defined as $ d(i,j) = |x_i - x_j| + |y_i - y_j| $ .

For each point, you have to choose a color, represented by an integer from $ 1 $ to $ n $ . For every ordered triple of different points $ (a,b,c) $ , the following constraints should be met:

- if $ a $ , $ b $ and $ c $ have the same color, then $ d(a,b) = d(a,c) = d(b,c) $ ;
- if $ a $ and $ b $ have the same color, and the color of $ c $ is different from the color of $ a $ , then $ d(a,b) < d(a,c) $ and $ d(a,b) < d(b,c) $ .

Calculate the number of different ways to choose the colors that meet these constraints.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 100 $ ) — the number of points.

Then $ n $ lines follow. The $ i $ -th of them contains two integers $ x_i $ and $ y_i $ ( $ 0 \le x_i, y_i \le 10^8 $ ).

No two points have the same coordinates (i. e. if $ i \ne j $ , then either $ x_i \ne x_j $ or $ y_i \ne y_j $ ).

## 输出格式

Print one integer — the number of ways to choose the colors for the points. Since it can be large, print it modulo $ 998244353 $ .

## 说明/提示

In the first test, the following ways to choose the colors are suitable:

- $ [1, 1, 1] $ ;
- $ [2, 2, 2] $ ;
- $ [3, 3, 3] $ ;
- $ [1, 2, 3] $ ;
- $ [1, 3, 2] $ ;
- $ [2, 1, 3] $ ;
- $ [2, 3, 1] $ ;
- $ [3, 1, 2] $ ;
- $ [3, 2, 1] $ .

## 样例 #1

### 输入

```
3
1 0
3 0
2 1
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5
1 2
2 4
3 4
4 4
1 3
```

### 输出

```
240
```

## 样例 #3

### 输入

```
4
1 0
3 0
2 1
2 0
```

### 输出

```
24
```



---

---
title: "Illumination"
layout: "post"
diff: 省选/NOI-
pid: CF1728G
tag: ['动态规划 DP', '状态合并', '组合数学', '容斥原理', '快速沃尔什变换 FWT']
---

# Illumination

## 题目描述

Consider a segment $ [0, d] $ of the coordinate line. There are $ n $ lanterns and $ m $ points of interest in this segment.

For each lantern, you can choose its power — an integer between $ 0 $ and $ d $ (inclusive). A lantern with coordinate $ x $ illuminates the point of interest with coordinate $ y $ if $ |x - y| $ is less than or equal to the power of the lantern.

A way to choose the power values for all lanterns is considered valid if every point of interest is illuminated by at least one lantern.

You have to process $ q $ queries. Each query is represented by one integer $ f_i $ . To answer the $ i $ -th query, you have to:

- add a lantern on coordinate $ f_i $ ;
- calculate the number of valid ways to assign power values to all lanterns, and print it modulo $ 998244353 $ ;
- remove the lantern you just added.

## 输入格式

The first line contains three integers $ d $ , $ n $ and $ m $ ( $ 4 \le d \le 3 \cdot 10^5 $ ; $ 1 \le n \le 2 \cdot 10^5 $ ; $ 1 \le m \le 16 $ ) — the size of the segment, the number of lanterns and the number of points of interest, respectively.

The second line contains $ n $ integers $ l_1, l_2, \dots, l_n $ ( $ 1 \le l_i \le d - 1 $ ), where $ l_i $ is the coordinate of the $ i $ -th lantern.

The third line contains $ m $ integers $ p_1, p_2, \dots, p_m $ ( $ 1 \le p_i \le d - 1 $ ), where $ p_i $ is the coordinate of the $ i $ -th point of interest.

The fourth line contains one integer $ q $ ( $ 1 \le q \le 5 \cdot 10^5 $ ) — the number of queries.

The fifth line contains $ q $ integers $ f_1, f_2, \dots, f_q $ ( $ 1 \le f_i \le d - 1 $ ), where $ f_i $ is the integer representing the $ i $ -th query.

Additional constraint on the input: during the processing of each query, no coordinate contains more than one object (i. e. there cannot be two or more lanterns with the same coordinate, two or more points of interest with the same coordinate, or a lantern and a point of interest with the same coordinate).

## 输出格式

For each query, print one integer — the answer to it, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
6 1 1
4
3
3
2 1 5
```

### 输出

```
48
47
47
```

## 样例 #2

### 输入

```
6 1 2
4
2 5
2
1 3
```

### 输出

```
44
46
```

## 样例 #3

### 输入

```
20 1 2
11
15 7
1
8
```

### 输出

```
413
```

## 样例 #4

### 输入

```
20 3 5
5 7 18
1 6 3 10 19
5
4 17 15 8 9
```

### 输出

```
190431
187503
188085
189903
189708
```



---

---
title: "Cleaning Robot"
layout: "post"
diff: 省选/NOI-
pid: CF1739E
tag: ['动态规划 DP', '状态合并']
---

# Cleaning Robot

## 题目描述

Consider a hallway, which can be represented as the matrix with $ 2 $ rows and $ n $ columns. Let's denote the cell on the intersection of the $ i $ -th row and the $ j $ -th column as $ (i, j) $ . The distance between the cells $ (i_1, j_1) $ and $ (i_2, j_2) $ is $ |i_1 - i_2| + |j_1 - j_2| $ .

There is a cleaning robot in the cell $ (1, 1) $ . Some cells of the hallway are clean, other cells are dirty (the cell with the robot is clean). You want to clean the hallway, so you are going to launch the robot to do this.

After the robot is launched, it works as follows. While at least one cell is dirty, the robot chooses the closest (to its current cell) cell among those which are dirty, moves there and cleans it (so the cell is no longer dirty). After cleaning a cell, the robot again finds the closest dirty cell to its current cell, and so on. This process repeats until the whole hallway is clean.

However, there is a critical bug in the robot's program. If at some moment, there are multiple closest (to the robot's current position) dirty cells, the robot malfunctions.

You want to clean the hallway in such a way that the robot doesn't malfunction. Before launching the robot, you can clean some (possibly zero) of the dirty cells yourself. However, you don't want to do too much dirty work yourself while you have this nice, smart (yet buggy) robot to do this. Note that you cannot make a clean cell dirty.

Calculate the maximum possible number of cells you can leave dirty before launching the robot, so that it doesn't malfunction.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of columns in the hallway.

Then two lines follow, denoting the $ 1 $ -st and the $ 2 $ -nd row of the hallway. These lines contain $ n $ characters each, where 0 denotes a clean cell and 1 denotes a dirty cell. The starting cell of the robot $ (1, 1) $ is clean.

## 输出格式

Print one integer — the maximum possible number of cells you can leave dirty before launching the robot, so that it doesn't malfunction.

## 说明/提示

In the first example, you can clean the cell $ (1, 2) $ , so the path of the robot is $ (1, 1) \rightarrow (2, 1) \rightarrow (2, 2) $ .

In the second example, you can leave the hallway as it is, so the path of the robot is $ (1, 1) \rightarrow (1, 2) \rightarrow (2, 2) $ .

In the third example, you can clean the cell $ (1, 2) $ , so the path of the robot is $ (1, 1) \rightarrow (2, 1) \rightarrow (2, 3) \rightarrow (2, 4) \rightarrow (1, 4) $ .

In the fourth example, the hallway is already clean. Maybe you have launched the robot earlier?

## 样例 #1

### 输入

```
2
01
11
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
01
01
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
0101
1011
```

### 输出

```
4
```

## 样例 #4

### 输入

```
4
0000
0000
```

### 输出

```
0
```

## 样例 #5

### 输入

```
5
00011
10101
```

### 输出

```
4
```

## 样例 #6

### 输入

```
6
011111
111111
```

### 输出

```
8
```

## 样例 #7

### 输入

```
10
0101001010
1010100110
```

### 输出

```
6
```



---

---
title: "Laboratory on Pluto"
layout: "post"
diff: 省选/NOI-
pid: CF1775F
tag: ['动态规划 DP', '组合数学', '构造']
---

# Laboratory on Pluto

## 题目描述

As you know, Martian scientists are actively engaged in space research. One of the highest priorities is Pluto. In order to study this planet in more detail, it was decided to build a laboratory on Pluto.

It is known that the lab will be built of $ n $ square blocks of equal size. For convenience, we will assume that Pluto's surface is a plane divided by vertical and horizontal lines into unit squares. Each square is either occupied by a lab block or not, and only $ n $ squares are occupied.

Since each block is square, it has four walls. If a wall is adjacent to another block, it is considered inside, otherwise — outside.

Pluto is famous for its extremely cold temperatures, so the outside walls of the lab must be insulated. One unit of insulation per exterior wall would be required. Thus, the greater the total length of the outside walls of the lab (i. e., its perimeter), the more insulation will be needed.

Consider the lab layout in the figure below. It shows that the lab consists of $ n = 33 $ blocks, and all the blocks have a total of $ 24 $ outside walls, i. e. $ 24 $ units of insulation will be needed.

You should build the lab optimally, i. e., minimize the amount of insulation. On the other hand, there may be many optimal options, so scientists may be interested in the number of ways to build the lab using the minimum amount of insulation, modulo a prime number $ m $ .

Two ways are considered the same if they are the same when overlapping without turning. Thus, if a lab plan is rotated by $ 90^{\circ} $ , such a new plan can be considered a separate way.

To help scientists explore Pluto, you need to write a program that solves these difficult problems.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775F/19a2731aaaa55a0f9a8048f01dd79ff768ce23d2.png)

## 输入格式

The first line contains two integers $ t $ and $ u $ ( $ 1 \le t \le 2\cdot 10^5 $ , $ 1 \le u \le 2 $ ) — the number of test cases and the test type. If $ u=1 $ , you need to find any way to build the lab in an optimal way, and if $ u=2 $ , you need to calculate the number of ways to do it.

If $ u=2 $ , then in the following line of input there is a prime integer $ m $ ( $ 10^8 \le m \le 10^9 + 9 $ ), modulo which you need to calculate the number of ways.

Each of the following $ t $ lines of input contains a description of a test case consisting of one integer $ n $ ( $ 1 \le n \le 4\cdot 10^5 $ ) — the number of blocks the lab should consist of.

It is guaranteed that if $ u=1 $ , then the sum of $ n $ on all test cases does not exceed $ 8\cdot10^5 $ .

## 输出格式

For each test case, output the answers in the format below, separating them with a newline. The output format depends on $ u $ in the input data.

If $ u=1 $ , in the first line you need to print two integers $ h $ and $ w $ —the height and width of the area in which the lab should be built. Then, in each of the following $ h $ lines, you must output a line $ s_i $ consisting of $ w $ characters "\#" and ".". If the $ j $ -th character of the row $ s_i $ is "\#", then the corresponding square must contain a block of laboratory, otherwise, it is considered empty. Thus, we get a matrix of symbols. The condition must also be met that the first and last rows of the matrix, as well as the first and last columns, must have at least one character "\#", otherwise we could output the same lab layout, but with smaller $ h $ and $ w $ . If there are many options to build an optimal lab, you can print any of them.

If $ u=2 $ , you need to print two integers $ p $ and $ c $ — the number of outside walls in an optimal lab, and the remainder of the number of ways by prime modulo $ m $ .

## 说明/提示

Consider the second example.

If $ n=1 $ , the only way to build a lab is to place a single block. In this case, the perimeter will be equal to four.

When $ n=2 $ , you must place two blocks side by side. This can be done either vertically or horizontally, so there are two ways. It is easy to see that the lab has six outside walls in this case.

For $ n=7 $ , all the $ 22 $ optimal plans are shown in the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775F/2d61b154960a5ef9890728641d5e6f811e5f6274.png)

## 样例 #1

### 输入

```
3 1
1
2
7
```

### 输出

```
1 1
#
1 2
##
2 4
.###
####
```

## 样例 #2

### 输入

```
3 2
1000000007
1
2
7
```

### 输出

```
4 1
6 2
12 22
```



---

---
title: "Bracket Insertion"
layout: "post"
diff: 省选/NOI-
pid: CF1781F
tag: ['动态规划 DP', '组合数学', '前缀和', '概率论']
---

# Bracket Insertion

## 题目描述

Vika likes playing with bracket sequences. Today she wants to create a new bracket sequence using the following algorithm. Initially, Vika's sequence is an empty string, and then she will repeat the following actions $ n $ times:

- Choose a place in the current bracket sequence to insert new brackets uniformly at random. If the length of the current sequence is $ k $ , then there are $ k+1 $ such places: before the first bracket, between the first and the second brackets, $ \ldots $ , after the $ k $ -th bracket. In particular, there is one such place in an empty bracket sequence.
- Choose string "()" with probability $ p $ or string ")(" with probability $ 1 - p $ and insert it into the chosen place. The length of the bracket sequence will increase by $ 2 $ .

A bracket sequence is called regular if it is possible to obtain a correct arithmetic expression by inserting characters '+' and '1' into it. For example, sequences "(())()", "()", and "(()(()))" are regular, while ")(", "(()", and "(()))(" are not.

Vika wants to know the probability that her bracket sequence will be a regular one at the end. Help her and find this probability modulo $ 998\,244\,353 $ (see Output section).

## 输入格式

The only line contains two integers $ n $ and $ q $ ( $ 1 \le n \le 500 $ ; $ 0 \le q \le 10^4 $ ). Here $ n $ is equal to the number of bracket insertion operations, and the probability that Vika chooses string "()" on every step of the algorithm is equal to $ p = q \cdot 10^{-4} $ .

## 输出格式

Print the probability that Vika's final bracket sequence will be regular, modulo $ 998\,244\,353 $ .

Formally, let $ M = 998\,244\,353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first example, Vika will get a regular bracket sequence () with probability $ p = \frac{3}{4} $ , and she will get an irregular bracket sequence )( with probability $ 1 - p = \frac{1}{4} $ . The sought probability is $ \frac{3}{4} $ , and $ 249\,561\,089 \cdot 4 \equiv 3 \pmod{998\,244\,353} $ .

In the second example, the sought probability is $ \frac{11}{25} $ .

## 样例 #1

### 输入

```
1 7500
```

### 输出

```
249561089
```

## 样例 #2

### 输入

```
2 6000
```

### 输出

```
519087064
```

## 样例 #3

### 输入

```
5 4000
```

### 输出

```
119387743
```



---

---
title: "Graph Coloring (easy version)"
layout: "post"
diff: 省选/NOI-
pid: CF1792F1
tag: ['动态规划 DP', '图论', '组合数学']
---

# Graph Coloring (easy version)

## 题目描述

The only difference between the easy and the hard version is the constraint on $ n $ .

You are given an undirected complete graph on $ n $ vertices. A complete graph is a graph where each pair of vertices is connected by an edge. You have to paint the edges of the graph into two colors, red and blue (each edge will have one color).

A set of vertices $ S $ is red-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through red edges and vertices from $ S $ . Similarly, a set of vertices $ S $ is blue-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through blue edges and vertices from $ S $ .

You have to paint the graph in such a way that:

- there is at least one red edge;
- there is at least one blue edge;
- for each set of vertices $ S $ such that $ |S| \ge 2 $ , $ S $ is either red-connected or blue-connected, but not both.

Calculate the number of ways to paint the graph, and print it modulo $ 998244353 $ .

## 输入格式

The first (and only) line contains one integer $ n $ ( $ 3 \le n \le 5 \cdot 10^3 $ ).

## 输出格式

Print one integer — the number of ways to paint the graph, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
```

### 输出

```
50
```

## 样例 #3

### 输入

```
100
```

### 输出

```
878752271
```

## 样例 #4

### 输入

```
1337
```

### 输出

```
520628749
```



---

---
title: "Count Voting"
layout: "post"
diff: 省选/NOI-
pid: CF1799G
tag: ['动态规划 DP', '组合数学', '容斥原理']
---

# Count Voting

## 题目描述

There are $ n $ people that will participate in voting. Each person has exactly one vote.

 $ i $ -th person has a team $ t_i $ ( $ 1 \leq t_i \leq n $ ) where $ t_i = t_j $ means $ i $ , $ j $ are in the same team. By the rules each person should vote for the person from the different team. Note that it automatically means that each person can't vote for himself.

Each person knows the number of votes $ c_i $ he wants to get. How many possible votings exists, such that each person will get the desired number of votes? Due to this number can be big, find it by modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 200 $ ) — the number of people.

The second line contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 0 \leq c_i \leq n $ ) — desired number of votes. It is guaranteed, that $ \sum\limits_{i=1}^{n} c_i = n $ .

The third line contains $ n $ integers $ t_1, t_2, \ldots, t_n $ ( $ 1 \leq t_i \leq n $ ) — team numbers.

## 输出格式

Print a single integer — the number of possible votings by modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test there are two possible votings: $ (2, 3, 1) $ , $ (3, 1, 2) $ .

In the third test there are five possible votings: $ (3, 3, 2, 2, 1) $ , $ (2, 3, 2, 3, 1) $ , $ (3, 3, 1, 2, 2) $ , $ (3, 1, 2, 3, 2) $ , $ (2, 3, 1, 3, 2) $ .

## 样例 #1

### 输入

```
3
1 1 1
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
2 0 1 0 2
1 2 3 4 5
```

### 输出

```
10
```

## 样例 #3

### 输入

```
5
1 2 2 0 0
3 5 4 3 4
```

### 输出

```
5
```



---

---
title: "Another n-dimensional chocolate bar"
layout: "post"
diff: 省选/NOI-
pid: CF1801F
tag: ['动态规划 DP', '数学']
---

# Another n-dimensional chocolate bar

## 题目描述

Mom bought the boy Vasya a $ n $ -dimensional chocolate bar, which is a $ n $ -dimensional cube with the length of each side equal to $ 1 $ . The chocolate is planned to be divided into slices. According to the $ i $ th dimension, it can be divided by hyperplanes into $ a_i $ equal parts. Thus, the chocolate is divided in total into $ a_1 \cdot a_2 \cdot a_3 \cdot \ldots \cdot a_n $ slices, each slice has a length of $ i $ -th dimension equal to $ \frac{1}{a_i} $ , respectively, the volume of each slice is $ \frac{1}{a_1 a_2 \cdots a_n} $ .Vasya and his friends want to cut a chocolate bar to get at least $ k $ pieces, while Vasya wants to maximize the volume of the smallest of them. It is possible to cut the chocolate bar only at the junction of the lobules, and each incision must pass through the entire chocolate bar along some hyperplane involved in the formation of lobules. Only after making all the cuts, Vasya disassembles the chocolate into pieces.

More formally, Vasya wants to choose the numbers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le a_i $ ) — the number of parts into which Vasya will cut the chocolate bar along each dimension. The condition $ b_1 \cdot b_2 \cdot \ldots \cdot b_n \ge k $ must be met to get at least $ k $ pieces after all cuts. It can be noted that with optimal cutting with such parameters, the minimum piece will contain $ \lfloor \frac{a_1}{b_1} \rfloor \dotsm \lfloor \frac{a_n}{b_n} \rfloor $ slices, and its volume will be equal to $ \lfloor \frac{a_1}{b_1} \rfloor \dotsm \lfloor \frac{a_n}{b_n} \rfloor \cdot \frac{1}{a_1 a_2 \cdots a_n} $ .

Vasya wants to get the maximum possible value of the volume of the minimum piece multiplied by $ k $ , that is, he wants to maximize the number of $ \lfloor \frac{a_1}{b_1} \rfloor \dotsm \lfloor \frac{a_n}{b_n} \rfloor \cdot \frac{1}{a_1 a_2 \cdots a_n} \cdot k $ . Help him with this.

## 输入格式

The first line contains two integers $ n $ and $ k $ $ (1 \le n \le 100 $ , $ 1 \le k \le 10^7) $ — the dimension of the chocolate bar, and how many parts it needs to be divided into.

The second line contains $ n $ integers $ a_1,\ a_2,\ \dots,\ a_n $ $ (1 \le a_i \le 10^7) $ — the number of pieces on which the chocolate is placed along each of the dimensions.

## 输出格式

Print one number — the maximum possible volume of the smallest of the obtained pieces, multiplied by $ k $ , with an absolute or relative error of no more than $ 10^{-9} $ .

If it is impossible to cut a chocolate bar into at least $ k $ pieces under the given restrictions, output $ 0 $ .

## 说明/提示

In the first example, a one – dimensional chocolate bar can be divided as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1801F/f5840bc9b6fba83080f4985e511bff8530afd934.png)

Then the answer will be $ \frac{2}{5} \cdot 2 = 0.8 $

In the second example, the chocolate bar can be cut as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1801F/627b4397ae726c6c50e5194d712fdc53a32a0b7f.png)

Then the answer will be $ \frac{2}{5} \cdot \frac{3}{10} \cdot 6 = 0.72 $

In the third example, the chocolate bar can be cut as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1801F/40196c672f43b7ab300ba0a5b9511f838e6ac4ad.png) Then the answer will be $ \frac{2}{4} \cdot \frac{1}{4} \cdot 7 = 0.875 $

## 样例 #1

### 输入

```
1 2
5
```

### 输出

```
0.8
```

## 样例 #2

### 输入

```
2 6
5 10
```

### 输出

```
0.72
```

## 样例 #3

### 输入

```
2 7
4 4
```

### 输出

```
0.875
```

## 样例 #4

### 输入

```
2 3
4 5
```

### 输出

```
0.75
```

## 样例 #5

### 输入

```
4 444
57 179 239 2
```

### 输出

```
0.97557326850704739751
```

## 样例 #6

### 输入

```
2 5
2 2
```

### 输出

```
0
```



---

---
title: "Small Permutation Problem (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1909F2
tag: ['动态规划 DP']
---

# Small Permutation Problem (Hard Version)

## 题目描述

[Andy Tunstall - MiniBoss](https://soundcloud.com/tunners/miniboss)

⠀



In the easy version, the $ a_i $ are in the range $ [0, n] $ ; in the hard version, the $ a_i $ are in the range $ [-1, n] $ and the definition of good permutation is slightly different. You can make hacks only if all versions of the problem are solved.

You are given an integer $ n $ and an array $ a_1, a_2, \dots, a_n $ of integers in the range $ [-1, n] $ .

A permutation $ p_1, p_2, \dots, p_n $ of $ [1, 2, \dots, n] $ is good if, for each $ i $ , the following condition is true:

- if $ a_i \neq -1 $ , the number of values $ \leq i $ in $ [p_1, p_2, \dots, p_i] $ is exactly $ a_i $ .

Count the good permutations of $ [1, 2, \dots, n] $ , modulo $ 998\,244\,353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -1 \le a_i \le n $ ), which describe the conditions for a good permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line containing the number of good permutations, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, all the permutations of length $ 5 $ are good, so there are $ 120 $ good permutations.

In the second test case, the only good permutation is $ [1, 2, 3, 4, 5] $ .

In the third test case, there are $ 4 $ good permutations: $ [2, 1, 5, 6, 3, 4] $ , $ [2, 1, 5, 6, 4, 3] $ , $ [2, 1, 6, 5, 3, 4] $ , $ [2, 1, 6, 5, 4, 3] $ . For example, $ [2, 1, 5, 6, 3, 4] $ is good because:

- $ a_1 = 0 $ , and there are $ 0 $ values $ \leq 1 $ in $ [p_1] = [2] $ ;
- $ a_2 = 2 $ , and there are $ 2 $ values $ \leq 2 $ in $ [p_1, p_2] = [2, 1] $ ;
- $ a_3 = 2 $ , and there are $ 2 $ values $ \leq 3 $ in $ [p_1, p_2, p_3] = [2, 1, 5] $ ;
- $ a_4 = 2 $ , and there are $ 2 $ values $ \leq 4 $ in $ [p_1, p_2, p_3, p_4] = [2, 1, 5, 6] $ ;
- $ a_5 = -1 $ , so there are no restrictions on $ [p_1, p_2, p_3, p_4, p_5] $ ;
- $ a_6 = -1 $ , so there are no restrictions on $ [p_1, p_2, p_3, p_4, p_5, p_6] $ .

## 样例 #1

### 输入

```
10
5
-1 -1 -1 -1 -1
5
1 2 3 4 5
6
0 2 2 2 -1 -1
6
-1 -1 -1 -1 -1 5
6
-1 -1 3 2 -1 -1
15
0 0 -1 -1 -1 2 2 -1 -1 -1 -1 9 11 13 15
6
0 2 2 2 4 6
6
0 1 3 4 5 5
6
1 2 3 2 4 6
15
0 0 1 1 1 2 3 4 5 6 7 9 11 13 15
```

### 输出

```
120
1
4
0
0
494403526
4
0
0
532305727
```



---

---
title: "Construct Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1917F
tag: ['动态规划 DP']
---

# Construct Tree

## 题目描述

You are given an array of integers $ l_1, l_2, \dots, l_n $ and an integer $ d $ . Is it possible to construct a tree satisfying the following three conditions?

- The tree contains $ n + 1 $ nodes.
- The length of the $ i $ -th edge is equal to $ l_i $ .
- The (weighted) diameter of the tree is equal to $ d $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 250 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ d $ ( $ 2 \leq n \leq 2000, 1 \leq d \leq 2000 $ ).

The second line of each test case contains $ n $ integers $ l_1, l_2, \dots, l_n $ ( $ 1 \leq l_i \leq d $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, output $ \texttt{Yes} $ if it is possible to construct a tree that satisfies all the conditions, and $ \texttt{No} $ otherwise.

You can print the letters in any case (upper or lower).

## 说明/提示

Below, you are given the illustrations of trees for the first and third test cases. One of the diameters is highlighted by coloring its edges in red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1917F/b0da55c56a8230f64464b5410b99445c4424c394.png)

## 样例 #1

### 输入

```
3
4 10
1 2 3 4
4 7
1 4 3 4
6 18
2 4 3 7 6 7
```

### 输出

```
Yes
No
Yes
```



---

---
title: "Counting Prefixes"
layout: "post"
diff: 省选/NOI-
pid: CF1919E
tag: ['动态规划 DP', '欧拉回路']
---

# Counting Prefixes

## 题目描述

There is a hidden array $ a $ of size $ n $ consisting of only $ 1 $ and $ -1 $ . Let $ p $ be the prefix sums of array $ a $ . More formally, $ p $ is an array of length $ n $ defined as $ p_i = a_1 + a_2 + \ldots + a_i $ . Afterwards, array $ p $ is sorted in non-decreasing order. For example, if $ a = [1, -1, -1, 1, 1] $ , then $ p = [1, 0, -1, 0, 1] $ before sorting and $ p = [-1, 0, 0, 1, 1] $ after sorting.

You are given the prefix sum array $ p $ after sorting, but you do not know what array $ a $ is. Your task is to count the number of initial arrays $ a $ such that the above process results in the given sorted prefix sum array $ p $ . As this number can be large, you are only required to find it modulo $ 998\,244\,353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the size of the hidden array $ a $ .

The second line of each test case contains $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ |p_i| \le n $ ) — the $ n $ prefix sums of $ a $ sorted in non-decreasing order.

It is guaranteed that $ p_1 \le p_2 \le \ldots \le p_n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5000 $ .

## 输出格式

For each test case, output the answer modulo $ 998\,244\,353 $ .

## 说明/提示

In the first two test cases, the only possible arrays $ a $ for $ n = 1 $ are $ a = [1] $ and $ a = [-1] $ . Their respective sorted prefix sum arrays $ p $ are $ p = [1] $ and $ p = [-1] $ . Hence, there is no array $ a $ that can result in the sorted prefix sum array $ p = [0] $ and there is exactly $ 1 $ array $ a $ that can result in the sorted prefix sum array $ p = [1] $ .

In the third test case, it can be proven that there is no array $ a $ that could result in the sorted prefix sum array $ p = [-1, 1, 2] $ .

In the fourth test case, the $ 3 $ possible arrays $ a $ that could result in the sorted prefix sum array $ p = [-1, 0, 0, 1, 1] $ are:

- $ a = [1, -1, 1, -1, -1] $ . The prefix sum array before sorting is $ p = [1, 0, 1, 0, -1] $ , which after sorting gives $ p = [-1, 0, 0, 1, 1] $ .
- $ a = [1, -1, -1, 1, 1] $ . The prefix sum array before sorting is $ p = [1, 0, -1, 0, 1] $ , which after sorting gives $ p = [-1, 0, 0, 1, 1] $ .
- $ a = [-1, 1, 1, -1, 1] $ . The prefix sum array before sorting is $ p = [-1, 0, 1, 0, 1] $ , which after sorting gives $ p = [-1, 0, 0, 1, 1] $ .

For the fifth test case, the only possible array $ a $ that could result in the sorted prefix sum array $ p = [-4, -3, -3, -2, -1] $ is $ a = [-1, -1, -1, -1, 1] $ .

## 样例 #1

### 输入

```
5
1
0
1
1
3
-1 1 2
5
-1 0 0 1 1
5
-4 -3 -3 -2 -1
```

### 输出

```
0
1
0
3
1
```



---

---
title: "Replace on Segment"
layout: "post"
diff: 省选/NOI-
pid: CF1922F
tag: ['动态规划 DP', '区间 DP']
---

# Replace on Segment

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , where each element is an integer from $ 1 $ to $ x $ .

You can perform the following operation with it any number of times:

- choose three integers $ l $ , $ r $ and $ k $ such that $ 1 \le l \le r \le n $ , $ 1 \le k \le x $ and each element $ a_i $ such that $ l \le i \le r $ is different from $ k $ . Then, for each $ i \in [l, r] $ , replace $ a_i $ with $ k $ .

In other words, you choose a subsegment of the array and an integer from $ 1 $ to $ x $ which does not appear in that subsegment, and replace every element in the subsegment with that chosen integer.

Your goal is to make all elements in the array equal. What is the minimum number of operations that you have to perform?

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

Each test case consists of two lines:

- the first line contains two integers $ n $ and $ x $ ( $ 1 \le x \le n \le 100 $ );
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le x $ ).

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, print one integer — the minimum number of operations you have to perform.

## 样例 #1

### 输入

```
3
3 2
1 2 1
6 3
1 2 3 1 2 3
12 3
3 1 3 1 2 1 1 2 3 1 1 3
```

### 输出

```
1
2
2
```



---

---
title: "Nobody is needed"
layout: "post"
diff: 省选/NOI-
pid: CF1946F
tag: ['动态规划 DP', '树状数组']
---

# Nobody is needed

## 题目描述

Oleg received a permutation $ a $ of length $ n $ as a birthday present.

Oleg's friend Nechipor asks Oleg $ q $ questions, each question is characterized by two numbers $ l $ and $ r $ , in response to the question Oleg must say the number of sets of indices $ (t_1, t_2, \ldots, t_k) $ of any length $ k \ge 1 $ such that:

- $ l \le t_i \le r $ for each $ i $ from $ 1 $ to $ k $ .
- $ t_i < t_{i+1} $ for each $ i $ from $ 1 $ to $ k-1 $ .
- $ a_{t_{i+1}} $ is divisible by $ a_{t_i} $ for each $ i $ from $ 1 $ to $ k-1 $ .

Help Oleg and answer all of Nechipor's questions.

## 输入格式

Each test consists of several sets of input data. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of sets of input data. The description of the sets of input data follows.

The first line of each set of input data contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 10^6 $ ) — the length of the permutation and the number of Nechipor's questions.

The second line of each set of input data contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the permutation $ a $ itself.

In each of the next $ q $ lines of each set of input data, there are two integers $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ) — the next question of Nechipor.

It is guaranteed that the sum of the values of $ n $ and the sum of the values of $ q $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each set of input data, output the answers to all of Nechipor's questions.

## 说明/提示

All suitable arrays in the first set of input data: ( $ 1 $ ), ( $ 2 $ ), ( $ 3 $ ), ( $ 4 $ ), ( $ 5 $ ), ( $ 6 $ ), ( $ 7 $ ), ( $ 8 $ ), ( $ 1, 3 $ ), ( $ 1, 6 $ ), ( $ 1, 7 $ ), ( $ 1, 6, 7 $ ), ( $ 2, 3 $ ), ( $ 2, 4 $ ), ( $ 2, 5 $ ), ( $ 2, 6 $ ), ( $ 2, 7 $ ), ( $ 2, 8 $ ), ( $ 2, 6, 7 $ ), ( $ 6, 7 $ ).

All suitable arrays in the fourth set of input data: ( $ 1 $ ), ( $ 2 $ ), ( $ 3 $ ), ( $ 4 $ ), ( $ 5 $ ), ( $ 6 $ ), ( $ 7 $ ), ( $ 8 $ ), ( $ 1, 2 $ ), ( $ 1, 3 $ ), ( $ 1, 4 $ ), ( $ 1, 5 $ ), ( $ 1, 6 $ ), ( $ 1, 7 $ ), ( $ 1, 8 $ ), ( $ 1, 2, 4 $ ), ( $ 1, 2, 6 $ ), ( $ 1, 2, 8 $ ), ( $ 1, 2, 4, 8 $ ), ( $ 1, 3, 6 $ ), ( $ 1, 4, 8 $ ), ( $ 2, 4 $ ), ( $ 2, 6 $ ), ( $ 2, 8 $ ), ( $ 2, 4, 8 $ ), ( $ 3, 6 $ ), ( $ 4, 8 $ ).

## 样例 #1

### 输入

```
4
8 8
2 1 6 3 5 4 8 7
1 8
2 8
1 7
1 6
1 3
5 8
4 4
2 3
1 1
1
1 1
3 3
3 2 1
1 2
1 3
2 3
8 1
1 2 3 4 5 6 7 8
1 8
```

### 输出

```
20 15 18 12 5 5 1 3
1
2 3 2
27
```



---

---
title: "Card Pairing"
layout: "post"
diff: 省选/NOI-
pid: CF1969F
tag: ['动态规划 DP']
---

# Card Pairing

## 题目描述

有一副包含 $n$ 张牌的牌组，每张牌都是 $k$ 种类型中的一种。你会得到序列 $a_1,a_2,\dots,a_n$，从左到右表示牌组中牌的类型。$n$ 和 $k$ 都是偶数。

你用这些牌玩游戏。首先，你从牌组中抽取最上面的 $k$ 张牌。然后，游戏每回合都会遵循以下步骤：

- 首先，你从手上选择两张牌并将它们扔出。如果这两张卡的类型相同，你将获得一枚硬币；
- 如果牌组不是空的，就从中抽出两张最上面的牌；
- 如果你的手和牌组都是空的，游戏结束。否则，开始下一回合。

请计算你在游戏中可以赚取的最大硬币数量。

## 输入格式

第一行包含两个整数 $n$ 和 $k$（$2\le k\le n\le 1000$，$n$ 与 $k$ 都是偶数）。

第二行包含 $n$ 个整数 $a_1,a_2,\dots,a_n$（$1\le a_i\le k$）。

## 输出格式

输出一个整数——你可以赚取的最大硬币数量。

## 样例 #1

### 输入

```
4 2
1 2 1 2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
8 2
2 1 2 2 1 2 1 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 4
1 2 1 2
```

### 输出

```
2
```

## 样例 #4

### 输入

```
6 4
3 2 3 1 2 1
```

### 输出

```
3
```

## 样例 #5

### 输入

```
6 4
3 2 3 3 2 1
```

### 输出

```
2
```

## 样例 #6

### 输入

```
18 6
5 6 1 1 6 5 4 1 5 1 1 6 2 6 2 2 6 3
```

### 输出

```
6
```

## 样例 #7

### 输入

```
8 4
1 2 3 4 4 3 1 2
```

### 输出

```
2
```

## 样例 #8

### 输入

```
8 4
1 2 3 4 4 3 3 2
```

### 输出

```
3
```



---

---
title: "Trails (Hard)"
layout: "post"
diff: 省选/NOI-
pid: CF1970E3
tag: ['动态规划 DP', '矩阵加速']
---

# Trails (Hard)

## 题目描述

Harry Potter is hiking in the Alps surrounding Lake Geneva. In this area there are $ m $ cabins, numbered 1 to $ m $ . Each cabin is connected, with one or more trails, to a central meeting point next to the lake. Each trail is either short or long. Cabin $ i $ is connected with $ s_i $ short trails and $ l_i $ long trails to the lake.

Each day, Harry walks a trail from the cabin where he currently is to Lake Geneva, and then from there he walks a trail to any of the $ m $ cabins (including the one he started in). However, as he has to finish the hike in a day, at least one of the two trails has to be short.

How many possible combinations of trails can Harry take if he starts in cabin 1 and walks for $ n $ days?

Give the answer modulo $ 10^9 + 7 $ .

## 输入格式

The first line contains the integers $ m $ and $ n $ .

The second line contains $ m $ integers, $ s_1, \dots, s_m $ , where $ s_i $ is the number of short trails between cabin $ i $ and Lake Geneva.

The third and last line contains $ m $ integers, $ l_1, \dots, l_m $ , where $ l_i $ is the number of long trails between cabin $ i $ and Lake Geneva.

We have the following constraints:

 $ 0 \le s_i, l_i \le 10^3 $ .

 $ 1 \le m \le 10^5 $ .

 $ 1 \le n \le 10^9 $ .

## 输出格式

The number of possible combinations of trails, modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
3 2
1 0 1
0 1 1
```

### 输出

```
18
```



---

---
title: "Xor-Grid Problem"
layout: "post"
diff: 省选/NOI-
pid: CF1993E
tag: ['动态规划 DP', '状态合并']
---

# Xor-Grid Problem

## 题目描述

Given a matrix $ a $ of size $ n \times m $ , each cell of which contains a non-negative integer. The integer lying at the intersection of the $ i $ -th row and the $ j $ -th column of the matrix is called $ a_{i,j} $ .

Let's define $ f(i) $ and $ g(j) $ as the [XOR](https://en.wikipedia.org/wiki/Exclusive_or) of all integers in the $ i $ -th row and the $ j $ -th column, respectively. In one operation, you can either:

- Select any row $ i $ , then assign $ a_{i,j} := g(j) $ for each $ 1 \le j \le m $ ; or
- Select any column $ j $ , then assign $ a_{i,j} := f(i) $ for each $ 1 \le i \le n $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993E/ab8c49518f9b338686e1980130aba0ac0a188a1e.png) An example of applying an operation on column $ 2 $ of the matrix.In this example, as we apply an operation on column $ 2 $ , all elements in this column are changed:

- $ a_{1,2} := f(1) = a_{1,1} \oplus a_{1,2} \oplus a_{1,3} \oplus a_{1,4} = 1 \oplus 1 \oplus 1 \oplus 1 = 0 $
- $ a_{2,2} := f(2) = a_{2,1} \oplus a_{2,2} \oplus a_{2,3} \oplus a_{2,4} = 2 \oplus 3 \oplus 5 \oplus 7 = 3 $
- $ a_{3,2} := f(3) = a_{3,1} \oplus a_{3,2} \oplus a_{3,3} \oplus a_{3,4} = 2 \oplus 0 \oplus 3 \oplus 0 = 1 $
- $ a_{4,2} := f(4) = a_{4,1} \oplus a_{4,2} \oplus a_{4,3} \oplus a_{4,4} = 10 \oplus 11 \oplus 12 \oplus 16 = 29 $

You can apply the operations any number of times. Then, we calculate the $ \textit{beauty} $ of the final matrix by summing the absolute differences between all pairs of its adjacent cells.

More formally, $ \textit{beauty}(a) = \sum|a_{x,y} - a_{r,c}| $ for all cells $ (x, y) $ and $ (r, c) $ if they are adjacent. Two cells are considered adjacent if they share a side.

Find the minimum $ \textit{beauty} $ among all obtainable matrices.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 250 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 15 $ ) — the number of rows and columns of $ a $ , respectively.

The next $ n $ lines, each containing $ m $ integers $ a_{i,1}, a_{i,2}, \ldots, a_{i,m} $ ( $ 0 \le a_{i,j} < 2^{20} $ ) — description of the matrix $ a $ .

It is guaranteed that the sum of $ (n^2 + m^2) $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, print a single integer $ b $ — the smallest possible $ \textit{beauty} $ of the matrix.

## 说明/提示

Let's denote $ r(i) $ as the first type operation applied on the $ i $ -th row, and $ c(j) $ as the second type operation applied on the $ j $ -th column.

In the first test case, you can apply an operation $ c(1) $ , which assigns $ a_{1,1} := 1 \oplus 3 = 2 $ . Then, we'll receive this matrix:

 23In the second test case, you can apply an operation $ r(1) $ , which assigns:

- $ a_{1,1} := g(1) = 0 \oplus 5 = 5 $
- $ a_{1,2} := g(2) = 1 \oplus 4 = 5 $
- $ a_{1,3} := g(3) = 0 \oplus 4 = 4 $

The resulting matrix after performing the operation is:

 554544In the third test case, the best way to achieve minimum $ \textit{beauty} $ is applying three operations: $ c(3) $ , $ r(2) $ , and $ c(2) $ . The resulting matrix is:

 046456

## 样例 #1

### 输入

```
4
1 2
1 3
2 3
0 1 0
5 4 4
2 3
0 2 4
4 5 1
3 3
1 2 3
4 5 6
7 8 9
```

### 输出

```
1
3
13
24
```



---

---
title: "Chips on a Line"
layout: "post"
diff: 省选/NOI-
pid: CF1997F
tag: ['动态规划 DP']
---

# Chips on a Line

## 题目描述

你有 $n$ 个芯片，并且要将它们放置在 $x$ 个点上，这些点编号为 $1$ 到 $x$ 。每个点可以放置多个芯片。

在放置芯片后，你可以执行以下四种操作（顺序任意，次数不限）：

- 选择在点 $i \geq 3$ 的一个芯片，将其移除，并在 $i - 1$ 和 $i - 2$ 各放置一个芯片；
- 选择在相邻点 $i$ 和 $i + 1$ 的两个芯片，将它们移除，并在 $i + 2$ 放置一个新芯片；
- 选择在点 $1$ 的一个芯片，并将其移到点 $2$；
- 选择在点 $2$ 的一个芯片，并将其移到点 $1$。

注意，放置操作中芯片的位置不能小于 $1$，但可以大于 $x$ 。

定义芯片放置的成本为：经过以上操作后剩余的最少芯片数。

例如，将两个芯片放在点 $3$ 和一个芯片放在点 $5$ 的成本为 $2$，因为可以通过以下步骤将芯片数减少到 $2$：

- 选择点 $3$ 的一个芯片，移除它，并在点 $1$ 和点 $2$ 各放置一个芯片；
- 选择点 $2$ 和点 $3$ 的芯片，移除它们，并在点 $4$ 放置一个芯片；
- 选择点 $4$ 和点 $5$ 的芯片，移除它们，并在点 $6$ 放置一个芯片。

给定三个整数 $n$、$x$ 和 $m$，计算在点 $1$ 到 $x$ 放置恰好 $n$ 个芯片且成本等于 $m$ 的放置方案数，并输出其模 $998244353$ 的结果。如果两个放置方案在某点的芯片数不同，则认为它们是不同的放置方案。

## 输入格式

一行包含三个整数 $n$、$x$ 和 $m (1 \le m \le n \le 1000 ; 2 \le x \le 10 )$

## 输出格式

输出一个整数，表示成本等于 $m$ 的放置方案数，并对 $998244353$ 取模。

## 样例 #1

### 输入

```
2 3 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
42 10 5
```

### 输出

```
902673363
```

## 样例 #3

### 输入

```
1000 10 8
```

### 输出

```
187821763
```



---

---
title: "Deterministic Heap (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2001E2
tag: ['动态规划 DP']
---

# Deterministic Heap (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the two versions is the definition of deterministic max-heap, time limit, and constraints on $ n $ and $ t $ . You can make hacks only if both versions of the problem are solved.

Consider a perfect binary tree with size $ 2^n - 1 $ , with nodes numbered from $ 1 $ to $ 2^n-1 $ and rooted at $ 1 $ . For each vertex $ v $ ( $ 1 \le v \le 2^{n - 1} - 1 $ ), vertex $ 2v $ is its left child and vertex $ 2v + 1 $ is its right child. Each node $ v $ also has a value $ a_v $ assigned to it.

Define the operation $ \mathrm{pop} $ as follows:

1. initialize variable $ v $ as $ 1 $ ;
2. repeat the following process until vertex $ v $ is a leaf (i.e. until $ 2^{n - 1} \le v \le 2^n - 1 $ ); 
  1. among the children of $ v $ , choose the one with the larger value on it and denote such vertex as $ x $ ; if the values on them are equal (i.e. $ a_{2v} = a_{2v + 1} $ ), you can choose any of them;
  2. assign $ a_x $ to $ a_v $ (i.e. $ a_v := a_x $ );
  3. assign $ x $ to $ v $ (i.e. $ v := x $ );
3. assign $ -1 $ to $ a_v $ (i.e. $ a_v := -1 $ ).

Then we say the $ \mathrm{pop} $ operation is deterministic if there is a unique way to do such operation. In other words, $ a_{2v} \neq a_{2v + 1} $ would hold whenever choosing between them.

A binary tree is called a max-heap if for every vertex $ v $ ( $ 1 \le v \le 2^{n - 1} - 1 $ ), both $ a_v \ge a_{2v} $ and $ a_v \ge a_{2v + 1} $ hold.

A max-heap is deterministic if the $ \mathrm{pop} $ operation is deterministic to the heap when we do it for the first and the second time.

Initially, $ a_v := 0 $ for every vertex $ v $ ( $ 1 \le v \le 2^n - 1 $ ), and your goal is to count the number of different deterministic max-heaps produced by applying the following operation $ \mathrm{add} $ exactly $ k $ times:

- Choose an integer $ v $ ( $ 1 \le v \le 2^n - 1 $ ) and, for every vertex $ x $ on the path between $ 1 $ and $ v $ , add $ 1 $ to $ a_x $ .

Two heaps are considered different if there is a node which has different values in the heaps.

Since the answer might be large, print it modulo $ p $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 50 $ ). The description of the test cases follows.

The first line of each test case contains three integers $ n, k, p $ ( $ 2 \le n \le 100 $ , $ 1 \le k \le 500 $ , $ 10^8 \le p \le 10^9 $ , $ p $ is a prime).

It is guaranteed that the sum of $ n $ does not exceed $ 100 $ and the sum of $ k $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, output a single line containing an integer: the number of different deterministic max-heaps produced by applying the aforementioned operation $ \mathrm{add} $ exactly $ k $ times, modulo $ p $ .

## 说明/提示

For the first testcase, if we choose $ v = 1 $ and do the operation, we would have $ a = [1, 0, 0] $ , and since $ a_2 = a_3 $ , we can choose either of them when doing the first $ \mathrm{pop} $ operation, so such heap is not a deterministic max-heap.

And if we choose $ v = 2 $ , we would have $ a = [1, 1, 0] $ , during the first $ \mathrm{pop} $ , the following would happen:

- initialize $ v $ as $ 1 $
- since $ a_{2v} > a_{2v + 1} $ , choose $ 2v $ as $ x $ , then $ x = 2 $
- assign $ a_x $ to $ a_v $ , then $ a = [1, 1, 0] $
- assign $ x $ to $ v $ , then $ v = 2 $
- since $ v $ is a leaf, assign $ -1 $ to $ a_v $ , then $ a = [1, -1, 0] $

And during the second $ \mathrm{pop} $ , the following would happen:

- initialize $ v $ as $ 1 $
- since $ a_{2v} < a_{2v + 1} $ , choose $ 2v + 1 $ as $ x $ , then $ x = 3 $
- assign $ a_x $ to $ a_v $ , then $ a = [0, -1, 0] $
- assign $ x $ to $ v $ , then $ v = 3 $
- since $ v $ is a leaf, assign $ -1 $ to $ a_v $ , then $ a = [0, -1, -1] $

Since both the first and the second $ \mathrm{pop} $ operation are deterministic, this is a deterministic max-heap. Also, if we choose $ v = 3 $ , $ a $ would be a deterministic max-heap, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
6
2 1 998244353
3 2 998244853
3 3 998244353
3 4 100000037
4 2 100000039
4 3 100000037
```

### 输出

```
2
12
40
100
32
224
```

## 样例 #2

### 输入

```
1
100 500 100000037
```

### 输出

```
66681128
```

## 样例 #3

### 输入

```
2
87 63 100000037
13 437 100000039
```

### 输出

```
83566569
54517140
```



---

---
title: "Speedbreaker Counting (Medium Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2018F2
tag: ['区间 DP', '动态规划优化', '容斥原理']
---

# Speedbreaker Counting (Medium Version)

## 题目描述

[DRG - Limbo](https://soundcloud.com/drg72711/limbo)

⠀



This is the medium version of the problem. In the three versions, the constraints on $ n $ and the time limit are different. You can make hacks only if all the versions of the problem are solved.

This is the statement of Problem D1B:

- There are $ n $ cities in a row, numbered $ 1, 2, \ldots, n $ left to right.
  - At time $ 1 $ , you conquer exactly one city, called the starting city.
  - At time $ 2, 3, \ldots, n $ , you can choose a city adjacent to the ones conquered so far and conquer it.
  
  You win if, for each $ i $ , you conquer city $ i $ at a time no later than $ a_i $ . A winning strategy may or may not exist, also depending on the starting city. How many starting cities allow you to win?

For each $ 0 \leq k \leq n $ , count the number of arrays of positive integers $ a_1, a_2, \ldots, a_n $ such that

- $ 1 \leq a_i \leq n $ for each $ 1 \leq i \leq n $ ;
- the answer to Problem D1B is $ k $ .

The answer can be very large, so you have to calculate it modulo a given prime $ p $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ). The description of the test cases follows.

The only line of each test case contains two integers $ n $ , $ p $ ( $ 1 \le n \le 500 $ , $ 10^8 \leq p \leq 10^9 $ , $ p $ is prime) — the number of cities and the modulo.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, output $ n+1 $ integers: the $ i $ -th integer should be the number of arrays that satisfy the conditions for $ k = i-1 $ .

## 说明/提示

In the first test case,

- arrays with $ 1 $ good starting city: $ [1] $ .

In the second test case,

- arrays with $ 0 $ good starting cities: $ [1, 1] $ ;
- arrays with $ 1 $ good starting city: $ [1, 2] $ , $ [2, 1] $ ;
- arrays with $ 2 $ good starting cities: $ [2, 2] $ .

In the third test case,

- arrays with $ 0 $ good starting cities: $ [1, 1, 1] $ , $ [1, 1, 2] $ , $ [1, 1, 3] $ , $ [1, 2, 1] $ , $ [1, 2, 2] $ , $ [1, 3, 1] $ , $ [1, 3, 2] $ , $ [2, 1, 1] $ , $ [2, 1, 2] $ , $ [2, 2, 1] $ , $ [2, 2, 2] $ , $ [2, 3, 1] $ , $ [2, 3, 2] $ , $ [3, 1, 1] $ ;
- arrays with $ 1 $ good starting city: $ [1, 2, 3] $ , $ [1, 3, 3] $ , $ [2, 1, 3] $ , $ [3, 1, 2] $ , $ [3, 1, 3] $ , $ [3, 2, 1] $ , $ [3, 3, 1] $ ;
- arrays with $ 2 $ good starting cities: $ [2, 2, 3] $ , $ [2, 3, 3] $ , $ [3, 2, 2] $ , $ [3, 3, 2] $ ;
- arrays with $ 3 $ good starting cities: $ [3, 2, 3] $ , $ [3, 3, 3] $ .

## 样例 #1

### 输入

```
11
1 998244353
2 998244353
3 998244353
4 998244353
5 998244353
6 998244353
7 998244353
8 998244353
9 998244353
10 102275857
10 999662017
```

### 输出

```
0 1 
1 2 1 
14 7 4 2 
183 34 19 16 4 
2624 209 112 120 48 12 
42605 1546 793 992 468 216 36 
785910 13327 6556 9190 4672 2880 864 144 
16382863 130922 61939 94992 50100 36960 14256 4608 576 
382823936 1441729 657784 1086596 583344 488700 216000 96480 23040 2880 
20300780 17572114 7751377 13641280 7376068 6810552 3269700 1785600 576000 144000 14400 
944100756 17572114 7751377 13641280 7376068 6810552 3269700 1785600 576000 144000 14400
```



---

---
title: "Speedbreaker Counting (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2018F3
tag: ['区间 DP', '动态规划优化', '容斥原理']
---

# Speedbreaker Counting (Hard Version)

## 题目描述

[DRG - Limbo](https://soundcloud.com/drg72711/limbo)

⠀



This is the hard version of the problem. In the three versions, the constraints on $ n $ and the time limit are different. You can make hacks only if all the versions of the problem are solved.

This is the statement of Problem D1B:

- There are $ n $ cities in a row, numbered $ 1, 2, \ldots, n $ left to right.
  - At time $ 1 $ , you conquer exactly one city, called the starting city.
  - At time $ 2, 3, \ldots, n $ , you can choose a city adjacent to the ones conquered so far and conquer it.
  
  You win if, for each $ i $ , you conquer city $ i $ at a time no later than $ a_i $ . A winning strategy may or may not exist, also depending on the starting city. How many starting cities allow you to win?

For each $ 0 \leq k \leq n $ , count the number of arrays of positive integers $ a_1, a_2, \ldots, a_n $ such that

- $ 1 \leq a_i \leq n $ for each $ 1 \leq i \leq n $ ;
- the answer to Problem D1B is $ k $ .

The answer can be very large, so you have to calculate it modulo a given prime $ p $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 3000 $ ). The description of the test cases follows.

The only line of each test case contains two integers $ n $ , $ p $ ( $ 1 \le n \le 3000 $ , $ 10^8 \leq p \leq 10^9 $ , $ p $ is prime) — the number of cities and the modulo.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3000 $ .

## 输出格式

For each test case, output $ n+1 $ integers: the $ i $ -th integer should be the number of arrays that satisfy the conditions for $ k = i-1 $ .

## 说明/提示

In the first test case,

- arrays with $ 1 $ good starting city: $ [1] $ .

In the second test case,

- arrays with $ 0 $ good starting cities: $ [1, 1] $ ;
- arrays with $ 1 $ good starting city: $ [1, 2] $ , $ [2, 1] $ ;
- arrays with $ 2 $ good starting cities: $ [2, 2] $ .

In the third test case,

- arrays with $ 0 $ good starting cities: $ [1, 1, 1] $ , $ [1, 1, 2] $ , $ [1, 1, 3] $ , $ [1, 2, 1] $ , $ [1, 2, 2] $ , $ [1, 3, 1] $ , $ [1, 3, 2] $ , $ [2, 1, 1] $ , $ [2, 1, 2] $ , $ [2, 2, 1] $ , $ [2, 2, 2] $ , $ [2, 3, 1] $ , $ [2, 3, 2] $ , $ [3, 1, 1] $ ;
- arrays with $ 1 $ good starting city: $ [1, 2, 3] $ , $ [1, 3, 3] $ , $ [2, 1, 3] $ , $ [3, 1, 2] $ , $ [3, 1, 3] $ , $ [3, 2, 1] $ , $ [3, 3, 1] $ ;
- arrays with $ 2 $ good starting cities: $ [2, 2, 3] $ , $ [2, 3, 3] $ , $ [3, 2, 2] $ , $ [3, 3, 2] $ ;
- arrays with $ 3 $ good starting cities: $ [3, 2, 3] $ , $ [3, 3, 3] $ .

## 样例 #1

### 输入

```
11
1 998244353
2 998244353
3 998244353
4 998244353
5 998244353
6 998244353
7 998244353
8 998244353
9 998244353
10 102275857
10 999662017
```

### 输出

```
0 1 
1 2 1 
14 7 4 2 
183 34 19 16 4 
2624 209 112 120 48 12 
42605 1546 793 992 468 216 36 
785910 13327 6556 9190 4672 2880 864 144 
16382863 130922 61939 94992 50100 36960 14256 4608 576 
382823936 1441729 657784 1086596 583344 488700 216000 96480 23040 2880 
20300780 17572114 7751377 13641280 7376068 6810552 3269700 1785600 576000 144000 14400 
944100756 17572114 7751377 13641280 7376068 6810552 3269700 1785600 576000 144000 14400
```



---

---
title: "Count Leaves"
layout: "post"
diff: 省选/NOI-
pid: CF2020F
tag: ['动态规划 DP', '素数判断,质数,筛法']
---

# Count Leaves

## 题目描述

有正整数 $n$ 和 $d$。我们按如下规则建一棵 $T_{n,d}$ 的约数树：

- 树的根节点上的数为 $n$。这是树的第 $0$ 层。
- 对于第 $i$ 层（$i=0,1,...,d-1$）的每个结点，执行如下操作：若当前节点上的数为 $x$，则 $x$ 的所有可能的不同约数为其儿子节点上的数。这些儿子节点位于第 $i+1$ 层。
- 第 $d$ 层上的点为叶子节点。

例如，$T_{6,2}$（$n=6,d=2$ 的约数树）如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2020F/fe3509981f0e7cfbf5fabd59d7e6e5b6182b6f65.png)

定义 $f(n,d)$ 为 $T(n,d)$ 的叶子节点数。

给定 $n,k,d$ ，计算 $\sum\limits_{i=1}^nf(i^k,d)$ 模 $10^9+7$ 后的答案。

注：在这个问题中，我们说 $y$ 为 $x$ 的约数当且仅当 $y\geq1$ 且存在整数 $z$ 使得 $x=y\cdot z$。

## 输入格式

每个测试有多组测试数据。第一行 $t\ (1\leq t\leq10^4)$ 为测试数据数。

每个测试数据包含一行三个数 $n,k,d\ (1\leq n\leq 10^9,1\leq k,d\leq 10^5)$。

保证所有测试数据中 $n$ 的和不超过 $10^9$。

## 输出格式

对于每个测试数据，输出一行一个整数，表示 $\sum\limits_{i=1}^nf(i^k,d)\ mod\ 10^9+7$ 后的结果。 
### 样例解释
在第一个测试样例中，$n=6,k=1,d=1$。因此，我们要算出 $T_{1,1},T_{2,1},T_{3,1},T_{4,1},T_{5,1},T_{6,1}$ 的叶子数的和。
- $T_{1,1}$ 只有一个叶子，该叶子上的数为 $1$。
- $T_{2,1}$ 有两个叶子，叶子上的数为 $1,2$。
- $T_{3,1}$ 有两个叶子，叶子上的数为 $1,3$。
- $T_{4,1}$ 有三个叶子，叶子上的数为 $1,2,4$。
- $T_{5,1}$ 有两个叶子，叶子上的数为 $1,5$。
- $T_{6,1}$ 有四个叶子，叶子上的数为 $1,2,3,6$。

叶子的总数为 $1+2+2+3+2+4=14$。

在第二个测试样例中，$n=1,k=3,d=3$，所以我们要求出 $T_{1^3,3}$ 的叶子数。因为 $1^3=1$，所以这棵树只有一片叶子，答案为 $1$。

## 样例 #1

### 输入

```
3
6 1 1
1 3 3
10 1 2
```

### 输出

```
14
1
53
```



---

---
title: "Boss, Thirsty"
layout: "post"
diff: 省选/NOI-
pid: CF2021D
tag: ['动态规划 DP']
---

# Boss, Thirsty

## 题目描述

Pak Chanek的一个朋友在食堂经营一个饮料摊位。他的朋友将在 $n$ 天内出售饮料，从第1天到第 $n$ 天。总共有 $m$ 种饮料，编号从1到 $m$。

在某一天出售某种饮料所能获得的利润会有所不同。在第 $i$ 天，出售第 $j$ 种饮料的预期利润是 $A_{i, j}$。请注意，$A_{i, j}$ 可能是负数，这意味着出售这种饮料实际上会造成亏损。

Pak Chanek想帮助他的朋友规划这 $n$ 天的销售。在第 $i$ 天，Pak Chanek必须选择至少出售一种类型的饮料。此外，在同一天出售的饮料类型必须形成一个子数组。换句话说，在每一天，Pak Chanek将选择 $i$ 和 $j$，满足 $1 \leq i \leq j \leq m$。然后，从第 $i$ 个到第 $j$ 个（包括两端）的所有类型的饮料都将被出售。

但是，为了确保前一天的顾客能继续光顾，第 $i$ 天（$i>1$）出售的饮料类型选择必须满足以下条件：

- 第 $i$ 天至少有一种饮料类型也必须在第$i-1$ 天出售。
- 第 $i$ 天至少有一种饮料类型不能在第 $i-1$ 天出售。

每日利润是当天出售的所有饮料类型利润的总和。销售计划的总利润是 $n$ 天内利润的总和。如果Pak Chanek能够优化销售计划，那么他能获得的最大总利润是多少？

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 1000$）。以下是测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$1 \leq n \leq 2 \cdot 10^5$；$3 \leq m \leq 2 \cdot 10^5$；$n \cdot m \leq 2 \cdot 10^5$），表示网格的行数和列数。

每个测试用例的接下来 $n$ 行每行包含 $m$ 个整数，其中第$i$行包含整数 $A_{i,1} A_{i,2}, \ldots, A_{i,m}$（$-10^9 \leq A_{i,j} \leq 10^9$），表示第$i$天每种饮料类型的预期利润。

保证所有测试用例中 $n \cdot m$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数：Pak Chanek能够获得的最大利润。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2021D/7f3c895e123ba63a87bc7e1148e98588d4bb8d72.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2021D/4913b558091cf536ad505f423605a117c6964776.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2021D/1e52a9ae8bab076a8dbab9525e40f8a26b2cd856.png)
以下是Pak Chanek的最优计划：

- 在第1天，Pak Chanek出售第1到3种饮料。获得利润 $79+20+49 = 148$。
- 在第2天，Pak Chanek出售第2到4种饮料。获得利润 $9+109+24 = 142$。
- 在第3天，Pak Chanek出售第1到6种饮料。获得利润 $185$。

因此，Pak Chanek计划的总利润是 $148 + 142 + 185 = 475$。

## 样例 #1

### 输入

```
1
3 6
79 20 49 5 -1000 500
-105 9 109 24 -98 -499
14 47 12 39 23 50
```

### 输出

```
475
```



---

---
title: "Digital Village (Extreme Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2021E3
tag: ['动态规划 DP', 'Kruskal 重构树', '凸包']
---

# Digital Village (Extreme Version)

## 题目描述

**这是问题的极端版本。在三个版本中，$n$ 和 $m$ 的约束条件不同。只有所有版本的问题都解决了，你才能进行 hack。**

Pak Chanek 正在为 Khuntien 村设置互联网连接。这个村庄可以表示为一个连通的简单图，其中有 $n$ 栋房屋和 $m$ 条互联网电缆，每条电缆连接房屋 $u_i$ 和房屋 $v_i$，并且具有延迟 $w_i$。

有 $p$ 栋房屋需要互联网。Pak Chanek 最多可以在 $k$ 栋房屋中安装服务器。需要互联网的房屋将连接到其中一个服务器。但是，由于每条电缆都有其延迟，对于需要互联网的房屋 $s_i$，其经历的延迟将是该房屋与其连接的服务器之间电缆的**最大**延迟。

对于每个 $k = 1,2,\ldots,n$，帮助 Pak Chanek 确定所有需要互联网的房屋所能达到的最小**总**延迟。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 2000$ )。对每个测试用例说明如下：

每个测试用例的第一行包含三个整数 $n$ , $m$ , $p$ ( $2 \le n \le 2\times 10^5$ ; $n-1 \le m \le 2\times 10^5$ ; $1 \le p \le n$ )，表示房屋数量、电缆数量和需要网络的房屋数量。

每个测试用例的第二行包含 $p$ 个整数 $s_1, s_2, \ldots, s_p$ ( $1 \le s_i \le n$ )，表示需要上网的房屋。保证 $s$ 中的所有元素都是不同的。

每个测试用例下 $m$ 行每行包含三个整数 $u_i$、$v_i$ 和 $w_i$（$1 \le u_i , v_i \le n$ ; $1 \le w_i \le 10^9$）表示一条连接房屋 $u_i$ 和房屋 $v_i$ 的网线，延迟为 $w_i$。保证给定的边构成一个连通的简单图。

保证 $n$ 和 $m$ 之和不超过 $2 \times 10^5$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数：对**每个**$k = 1,2,\ldots,n$，计算所有需要上网的房屋所能达到的最小总延迟。

**样例解释**

第一个测试用例中，$k=3$ 的一个的最佳解决方案是在顶点 $2$ 、 $6$ 和 $8$ 安装服务器，并获得以下延迟：

- $\text{latency}(2) = 0$
- $\text{latency}(5) = \max(3, 5) = 5$
- $\text{latency}(6) = 0$
- $\text{latency}(8) = 0$
- $\text{latency}(9) = \max(2, 4) = 4$

因此总延迟为 $0+5+0+0+4=9$ 。

## 样例 #1

### 输入

```
2
9 8 5
2 5 6 8 9
1 2 1
1 3 2
3 4 10
4 5 3
4 6 5
1 7 10
7 8 4
7 9 2
3 3 2
3 1
1 2 1
2 3 3
1 3 2
```

### 输出

```
34 19 9 4 0 0 0 0 0
2 0 0
```



---

---
title: "Many Games"
layout: "post"
diff: 省选/NOI-
pid: CF2023D
tag: ['动态规划 DP', '数学', '剪枝', '概率论']
---

# Many Games

## 题目描述

Recently, you received a rare ticket to the only casino in the world where you can actually earn something, and you want to take full advantage of this opportunity.

The conditions in this casino are as follows:

- There are a total of $ n $ games in the casino.
- You can play each game at most once.
- Each game is characterized by two parameters: $ p_i $ ( $ 1 \le p_i \le 100 $ ) and $ w_i $ — the probability of winning the game in percentage and the winnings for a win.
- If you lose in any game you decide to play, you will receive nothing at all (even for the games you won).

You need to choose a set of games in advance that you will play in such a way as to maximize the expected value of your winnings.

In this case, if you choose to play the games with indices $ i_1 < i_2 < \ldots < i_k $ , you will win in all of them with a probability of $ \prod\limits_{j=1}^k \frac{p_{i_j}}{100} $ , and in that case, your winnings will be equal to $ \sum\limits_{j=1}^k w_{i_j} $ .

That is, the expected value of your winnings will be $ \left(\prod\limits_{j=1}^k \frac{p_{i_j}}{100}\right) \cdot \left(\sum\limits_{j=1}^k w_{i_j}\right) $ .

To avoid going bankrupt, the casino owners have limited the expected value of winnings for each individual game. Thus, for all $ i $ ( $ 1 \le i \le n $ ), it holds that $ w_i \cdot p_i \le 2 \cdot 10^5 $ .

Your task is to find the maximum expected value of winnings that can be obtained by choosing some set of games in the casino.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of games offered to play.

The $ i $ -th of the following $ n $ lines contains two integers $ p_i $ and $ w_i $ ( $ 1 \leq p_i \leq 100 $ , $ 1 \leq w_i, p_i \cdot w_i \leq 2 \cdot 10^5 $ ) — the probability of winning and the size of the winnings in the $ i $ -th game.

## 输出格式

Output a single number — the maximum expected value of winnings in the casino that can be obtained by choosing some subset of games.

Your answer will be accepted if the relative or absolute error does not exceed $ 10^{-6} $ . Formally, if $ a $ is your answer and $ b $ is the jury's answer, it will be accepted if $ \frac{|a-b|}{\max(b, 1)} \le 10^{-6} $ .

## 说明/提示

In the first example, you can choose the first and third games. In this case, the expected value of winnings will be $ \left(\frac{p_1}{100}\cdot \frac{p_3}{100}\right) \cdot (w_1 + w_3) = \left(\frac{80}{100}\cdot \frac{50}{100}\right) \cdot (80 + 200) = 112 $ .

In the second example, you can choose the first and second games. In this case, the expected value of winnings will be $ \left(\frac{p_1}{100}\cdot \frac{p_2}{100}\right) \cdot (w_1 + w_2) = \left(\frac{100}{100}\cdot \frac{100}{100}\right) \cdot (1 + 1) = 2 $ .

In the third example, you can choose only the second game. In this case, the expected value of winnings will be $ \frac{p_2}{100} \cdot w_2 = \frac{2}{100} \cdot 1000 = 20 $ .

## 样例 #1

### 输入

```
3
80 80
70 100
50 200
```

### 输出

```
112.00000000
```

## 样例 #2

### 输入

```
2
100 1
100 1
```

### 输出

```
2.00000000
```

## 样例 #3

### 输入

```
4
1 100
2 1000
2 100
3 1
```

### 输出

```
20.00000000
```

## 样例 #4

### 输入

```
5
34 804
78 209
99 191
61 439
90 79
```

### 输出

```
395.20423800
```



---

---
title: "Bermart Ice Cream"
layout: "post"
diff: 省选/NOI-
pid: CF2026F
tag: ['动态规划 DP', '均摊分析']
---

# Bermart Ice Cream

## 题目描述

Bermart 连锁店出售各种冰淇淋，每种冰淇淋都有两个参数：价格和口味。

最初，有一家编号为 $1$ 的商店，不出售任何产品。

您必须处理以下类型的 $q$ 个查询：

- `1 x`：新店开张，编号为开张前的最大编号 $+1$，出售与 $x$ 店相同种类的冰淇淋，且顺序与 $x$ 店相同。
- `2 x p t`：一种价格为 $p$、口味为 $t$ 的冰淇淋在 $x$ 店上市。
- `3 x`：$x$ 店中供应时间最长（最早出现）的一种冰淇淋被移除。
- `4 x p`：求在 $x$ 店出售的所有种类的冰淇淋中花费不超过 $p$ 元能获得的最大总美味度，每种冰淇淋只能购买一次。

## 输入格式

第一行一个整数 $q$，表示查询数量。

## 输出格式

对于每个类型 $4$ 的询问，输出一行一个整数表示答案。

## 说明/提示

$1\le q\le 3\times 10^4$，$1\le p,t\le 2\times 10^3$，且保证：

- 每个查询中的 $x$ 不超过当前商店数量（即 $1$ 加上类型 $1$ 查询的数量)；
- 查询类型 $3$ 不会用于没有冰淇淋出售的商店；
- 至少有一个类型 $4$ 的查询。

## 样例 #1

### 输入

```
12
2 1 5 7
2 1 3 4
4 1 4
4 1 8
4 1 2
1 1
2 2 4 10
4 1 9
4 2 9
3 1
4 1 9
4 2 9
```

### 输出

```
4
11
0
11
17
4
17
```



---

---
title: "Balanced Problem"
layout: "post"
diff: 省选/NOI-
pid: CF2029G
tag: ['动态规划 DP', '树状数组']
---

# Balanced Problem

## 题目描述

There is an array $ a $ consisting of $ n $ integers. Initially, all elements of $ a $ are equal to $ 0 $ .

Kevin can perform several operations on the array. Each operation is one of the following two types:

- Prefix addition — Kevin first selects an index $ x $ ( $ 1\le x\le n $ ), and then for each $ 1\le j\le x $ , increases $ a_j $ by $ 1 $ ;
- Suffix addition — Kevin first selects an index $ x $ ( $ 1\le x\le n $ ), and then for each $ x\le j\le n $ , increases $ a_j $ by $ 1 $ .

In the country of KDOI, people think that the integer $ v $ is balanced. Thus, Iris gives Kevin an array $ c $ consisting of $ n $ integers and defines the beauty of the array $ a $ as follows:

- Initially, set $ b=0 $ ;
- For each $ 1\le i\le n $ , if $ a_i=v $ , add $ c_i $ to $ b $ ;
- The beauty of $ a $ is the final value of $ b $ .

Kevin wants to maximize the beauty of $ a $ after all the operations. However, he had already performed $ m $ operations when he was sleepy. Now, he can perform an arbitrary number (possibly zero) of new operations.

You have to help Kevin find the maximum possible beauty if he optimally performs the new operations.

However, to make sure that you are not just rolling the dice, Kevin gives you an integer $ V $ , and you need to solve the problem for each $ 1\le v\le V $ .

## 输入格式

Each test contains multiple test cases. The first line of the input contains a single integer $ t $ ( $ 1\le t\le 1000 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains three integers $ n $ , $ m $ , and $ V $ ( $ 1\le n, m\le 2\cdot 10^5 $ , $ 1\le V\le 2000 $ ) — the length of the array $ a $ , the number of initial operations, and the number that Kevin gives you.

The second line contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 1\le c_i\le 10^9 $ ) — the elements in the array $ c $ .

Then $ m $ lines follow, the $ i $ -th line containing a character $ op $ and an integer $ x $ ( $ op=\mathtt{L} $ or $ \mathtt{R} $ , $ 1\le x\le n $ ) — the type of the $ i $ -th operation and the selected index.

- If $ op=\mathtt{L} $ , this operation is a prefix addition on index $ x $ ;
- If $ op=\mathtt{R} $ , this operation is a suffix addition on index $ x $ .

It is guaranteed that:

- the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ ;
- the sum of $ m $ over all test cases does not exceed $ 2\cdot 10^5 $ ;
- the sum of $ V^2 $ over all test cases does not exceed $ 4\cdot 10^6 $ .

## 输出格式

For each test case, output $ V $ integers in a single line, the $ i $ -th integer denoting the maximum possible beauty after Kevin performs some new operations when $ v=i $ .

## 说明/提示

In the first test case, the array $ a $ changes as follows for the initial operations: $ [0, 0, 0] \xrightarrow{\mathtt{L}\ 3} [1, 1, 1] \xrightarrow{\mathtt{R}\ 3} [1, 1, 2] \xrightarrow{\mathtt{L}\ 1} [2, 1, 2] $ .

- For $ v=1 $ , it is optimal to not perform any new operations, and the beauty is $ b=c_2=2 $ ;
- For $ v=2 $ , it is optimal to perform a prefix addition operation on index $ 2 $ . After that, $ a $ becomes $ [3,2,2] $ , and the beauty is $ b=c_2+c_3=6 $ .

In the second test case, for both $ v=1 $ and $ v=2 $ , it is optimal to not perform any new operations.

## 样例 #1

### 输入

```
5
3 3 2
1 2 4
L 3
R 3
L 1
3 3 2
5 1 4
L 3
R 3
L 1
5 4 5
1 1 1 1 1
L 3
R 2
L 5
L 4
10 12 9
10 9 8 7 6 5 4 3 2 1
L 2
L 4
R 4
R 4
L 6
R 8
L 3
L 2
R 1
R 10
L 8
L 1
1 1 4
1000000000
L 1
```

### 输出

```
2 6
1 9
0 1 3 5 5
0 0 0 6 25 32 35 44 51
1000000000 1000000000 1000000000 1000000000
```



---

---
title: "Peanuts"
layout: "post"
diff: 省选/NOI-
pid: CF2032F
tag: ['动态规划 DP', '博弈论']
---

# Peanuts

## 题目描述

Having the magical beanstalk, Jack has been gathering a lot of peanuts lately. Eventually, he has obtained $ n $ pockets of peanuts, conveniently numbered $ 1 $ to $ n $ from left to right. The $ i $ -th pocket has $ a_i $ peanuts.

Jack and his childhood friend Alice decide to play a game around the peanuts. First, Alice divides the pockets into some boxes; each box will have a non-zero number of consecutive pockets, and each pocket will, obviously, belong to exactly one box. At the same time, Alice does not change the order of the boxes, that is, the boxes are numbered in ascending order of the indices of the pockets in them.

After that, Alice and Jack will take turns alternately, with Alice going first.

At each turn, the current player will remove a positive number of peanuts from exactly one pocket which belongs to the leftmost non-empty box (i.e., the leftmost box containing at least one non-empty pocket). In other words, if we number the boxes from left to right, then each player can only pick peanuts from the pocket in the $ j $ -th box ( $ j \ge 2 $ ) only if the $ (j - 1) $ -th box has no peanuts left. The player who cannot make a valid move loses.

Alice is sure she will win since she has the advantage of dividing the pockets into boxes herself. Thus, she wanted to know how many ways there are for her to divide the peanuts into boxes at the start of the game so that she will win, assuming both players play optimally. Can you help her with the calculation?

As the result can be very large, output it modulo $ 998\,244\,353 $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 10^6 $ ) — the number of pockets.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the number of peanuts in each pocket.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a single integer — the number of ways for Alice to divide the pockets into boxes at the start of the game to guarantee her win, assuming both players play optimally, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the only way for Alice to win is to divide the pockets into two boxes as follows: $ ([1, 2], [3]) $ (the first box contains the first two pockets and the second box contains the third pocket). Alice wins by taking both peanuts from the second pocket, leaving Jack with $ ([1], [3]) $ . Jack is forced to take the only peanut left in the first box, which allows Alice to take the remaining ones in the second box.

In the second test case, the winning divisions for Alice are $ ([1], [2, 3, 1]) $ , $ ([1, 2, 3, 1]) $ , $ ([1, 2], [3], [1]) $ , and $ ([1, 2], [3, 1]) $ .

In the third test case, Alice always wins no matter how she divides the pockets into boxes.

In the fourth test case, Alice always loses no matter how she divides the pockets into boxes.

## 样例 #1

### 输入

```
5
3
1 2 3
4
1 2 3 1
5
1 1 1 1 1
2
1 1
10
1 2 3 4 5 6 7 8 9 10
```

### 输出

```
1
4
16
0
205
```



---

---
title: "Khayyam's Royal Decree (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2034F2
tag: ['动态规划 DP', '概率论']
---

# Khayyam's Royal Decree (Hard Version)

## 题目描述

这是本题的困难版本。两个版本的唯一区别在于 $k$ 和 $\sum k$ 的限制。

Khayyam 有一个**宝箱**，**宝箱**里初始有 $n$ 个红宝石和 $m$ 个蓝宝石。一个红宝石的价值为 $2$，一个蓝宝石的价值为 $1$。他还有一个**背包**，初始为空。另外，他还有 $k$ 张卷轴，第 $i$ 张卷轴上有数对 $(r_i,b_i)$。

Khayyam 将进行一个游戏，游戏共 $n+m$ 轮，每轮流程如下：

1. Khayyam 从**宝箱**中等概率随机拿出一个宝石。
2. 他将这个宝石放入**背包**中。
3. 若存在一张卷轴 $i$，使得**宝箱**中恰有 $r_i$ 个红宝石和 $b_i$ 个蓝宝石，将所有**背包**里的宝石的价值翻倍。

一个宝石的价值可以被多次翻倍。

求游戏结束时 Khayyam **背包**里宝石的价值总和的期望值，对 $998244353$ 取模。

## 输入格式

多测，第一行一个整数 $T$ 表示数据组数。

每组数据的第一行三个整数 $n,m,k$。

接下来 $k$ 行，每行两个整数 $r_i,b_i$。

保证 $1\le T\le 500$，$1\le n,m,\sum n,\sum m\le 2\times 10^5$，$1\le k,\sum k\le 5000$。

保证 $0\le r_i\le n$，$0\le b_i\le m$，$1\le r_i+b_i\le n+m-1$，且 $(r_i,b_i)$ 两两不同。

## 输出格式

一行一个整数，表示答案对 $998244353$ 取模的值。

### 样例解释

对于第一组数据，最终背包里总会有 $3$ 个红宝石和 $4$ 个蓝宝石，不会有卷轴被触发。因此背包里宝石的总价值总是 $2\times 3+1\times 4=10$。

对于第二组数据：

+ 有 $\dfrac{1}{2}$ 概率，Khayyam 先拿出红宝石再拿出蓝宝石，不会有卷轴被触发，总价值为 $3$；
+ 有 $\dfrac{1}{2}$ 概率，Khayyam 先拿出蓝宝石再拿出红宝石，卷轴 $1$ 会被触发，蓝宝石的价值翻倍，总价值为 $4$。

因此总价值的期望是 $\dfrac{1}{2}\times 3+\dfrac{1}{2}\times 4=\dfrac{7}{2}\equiv 499122180\pmod {998244353}$。

## 样例 #1

### 输入

```
5
3 4 0
1 1 1
1 0
3 3 2
1 1
2 2
3 3 2
2 1
1 2
10 4 5
1 0
8 0
6 4
0 2
7 4
```

### 输出

```
10
499122180
798595498
149736666
414854846
```



---

---
title: "Divide OR Conquer"
layout: "post"
diff: 省选/NOI-
pid: CF2038D
tag: ['动态规划 DP', '树状数组', '动态规划优化']
---

# Divide OR Conquer

## 题目描述

You are given an array $ [a_1, a_2, \ldots a_n] $ consisting of integers between $ 0 $ and $ 10^9 $ . You have to split this array into several segments (possibly one) in such a way that each element belongs to exactly one segment.

Let the first segment be the array $ [a_{l_1}, a_{l_1 + 1}, \ldots, a_{r_1}] $ , the second segment be $ [a_{l_2}, a_{l_2+ 1}, \ldots, a_{r_2}] $ , ..., the last segment be $ [a_{l_k}, a_{l_k+ 1}, \ldots, a_{r_k}] $ . Since every element should belong to exactly one array, $ l_1 = 1 $ , $ r_k = n $ , and $ r_i + 1 = l_{i+1} $ for each $ i $ from $ 1 $ to $ k-1 $ . The split should meet the following condition: $ f([a_{l_1}, a_{l_1 + 1}, \ldots, a_{r_1}]) \le f([a_{l_2}, a_{l_2+ 1}, \ldots, a_{r_2}]) \le \dots \le f([a_{l_k}, a_{l_k+1}, \ldots, a_{r_k}]) $ , where $ f(a) $ is the bitwise OR of all elements of the array $ a $ .

Calculate the number of ways to split the array, and print it modulo $ 998\,244\,353 $ . Two ways are considered different if the sequences $ [l_1, r_1, l_2, r_2, \ldots, l_k, r_k] $ denoting the splits are different.

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10 ^9 $ ) — the elements of the given array.

## 输出格式

Print one integer — the number of ways to split the array, taken modulo $ 998\,244\,353 $ .

## 说明/提示

In the first two examples, every way to split the array is valid.

In the third example, there are three valid ways to split the array:

- $ k = 3 $ ; $ l_1 = 1, r_1 = 1, l_2 = 2, r_2 = 2, l_3 = 3, r_3 = 3 $ ; the resulting arrays are $ [3] $ , $ [4] $ , $ [6] $ , and $ 3 \le 4 \le 6 $ ;
- $ k = 2 $ ; $ l_1 = 1, r_1 = 1, l_2 = 2, r_2 = 3 $ ; the resulting arrays are $ [3] $ and $ [4, 6] $ , and $ 3 \le 6 $ ;
- $ k = 1 $ ; $ l_1 = 1, r_1 = 3 $ ; there will be only one array: $ [3, 4, 6] $ .

If you split the array into two arrays $ [3, 4] $ and $ [6] $ , the bitwise OR of the first array is $ 7 $ , and the bitwise OR of the second array is $ 6 $ ; $ 7 > 6 $ , so this way to split the array is invalid.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1000 1000 1000 1000 1000
```

### 输出

```
16
```

## 样例 #3

### 输入

```
3
3 4 6
```

### 输出

```
3
```



---

---
title: "Royal Flush"
layout: "post"
diff: 省选/NOI-
pid: CF2038M
tag: ['动态规划 DP', '标签464']
---

# Royal Flush

## 题目描述

Consider the following game. There is a deck, which consists of cards of $ n $ different suits. For each suit, there are $ 13 $ cards in the deck, all with different ranks (the ranks are $ 2 $ , $ 3 $ , $ 4 $ , ..., $ 10 $ , Jack, Queen, King and Ace).

Initially, the deck is shuffled randomly (all $ (13n)! $ possible orders of cards have the same probability). You draw $ 5 $ topmost cards from the deck. Then, every turn of the game, the following events happen, in the given order:

1. if the cards in your hand form a Royal Flush (a $ 10 $ , a Jack, a Queen, a King, and an Ace, all of the same suit), you win, and the game ends;
2. if you haven't won yet, and the deck is empty, you lose, and the game ends;
3. if the game hasn't ended yet, you may choose any cards from your hand (possibly, all of them) and discard them. When a card is discarded, it is removed from the game;
4. finally, you draw cards from the deck, until you have $ 5 $ cards or the deck becomes empty.

Your goal is to find a strategy that allows you to win in the minimum expected number of turns. Note that the turn when the game ends is not counted (for example, if the $ 5 $ cards you draw initially already form a Royal Flush, you win in $ 0 $ turns).

Calculate the minimum possible expected number of turns required to win the game.

## 输入格式

The only line contains one integer $ n $ ( $ 1 \le n \le 4 $ ) — the number of suits used in the game.

## 输出格式

Print the minimum expected number of turns.

Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ . Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer will be accepted if and only if $ \frac{|a - b|}{\max{(1, |b|)}} \le 10^{-6} $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
3.598290598
```

## 样例 #2

### 输入

```
2
```

### 输出

```
8.067171309
```



---

---
title: "Shohag Loves Counting (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2039F1
tag: ['动态规划 DP', '数论', '莫比乌斯反演', '容斥原理']
---

# Shohag Loves Counting (Easy Version)

## 题目描述

This is the easy version of the problem. The only differences between the two versions of this problem are the constraints on $ t $ , $ m $ , and the sum of $ m $ . You can only make hacks if both versions of the problem are solved.

For an integer array $ a $ of length $ n $ , define $ f(k) $ as the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the maximum values of all subarrays $ ^{\text{∗}} $ of length $ k $ . For example, if the array is $ [2, 1, 4, 6, 2] $ , then $ f(3) = \operatorname{gcd}(\operatorname{max}([2, 1, 4]), \operatorname{max}([1, 4, 6]), \operatorname{max}([4, 6, 2])) = \operatorname{gcd}(4, 6, 6) = 2 $ .

An array is good if $ f(i) \neq f(j) $ is satisfied over all pairs $ 1 \le i \lt j \le n $ .

Shohag has an integer $ m $ . Help him count the number, modulo $ 998\,244\,353 $ , of non-empty good arrays of arbitrary length such that each element of the array is an integer from $ 1 $ to $ m $ .

 $ ^{\text{∗}} $ An array $ d $ is a subarray of an array $ c $ if $ d $ can be obtained from $ c $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line of each test case contains an integer $ m $ ( $ 1 \le m \le 10^5 $ ).

It is guaranteed that the sum of $ m $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output an integer — the number of valid arrays modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the valid arrays are $ [1] $ , $ [1, 2] $ , $ [2] $ , and $ [2, 1] $ .

In the second test case, there are a total of $ 29 $ valid arrays. In particular, the array $ [2, 1, 4] $ with length $ n = 3 $ is valid because all elements are from $ 1 $ to $ m = 5 $ and $ f(1) $ , $ f(2) $ and $ f(n = 3) $ all are distinct:

- $ f(1) = \operatorname{gcd}(\operatorname{max}([2]), \operatorname{max}([1]), \operatorname{max}([4])) = \operatorname{gcd}(2, 1, 4) = 1. $
- $ f(2) = \operatorname{gcd}(\operatorname{max}([2, 1]), \operatorname{max}([1, 4])) = \operatorname{gcd}(2, 4) = 2. $
- $ f(3) = \operatorname{gcd}(\operatorname{max}([2, 1, 4])) = \operatorname{gcd}(4) = 4. $

## 样例 #1

### 输入

```
3
2
5
9
```

### 输出

```
4
29
165
```



---

---
title: "Bottle Arrangement"
layout: "post"
diff: 省选/NOI-
pid: CF2041J
tag: ['动态规划 DP', '分治', '扫描线', '差分']
---

# Bottle Arrangement

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041J/a93240ff9d94fb996cc13c493b1008f9c0801598.png) Image generated by ChatGPT 4o.Mayaw works in a renowned Epah (aboriginal Taiwanese millet wine; Epah is the Pangcah term for aboriginal Taiwanese millet wine, named in the language of the Pangcah people, the largest Indigenous group in Taiwan) bar in the Fata'an Village. To showcase the depth of its collections, the bar has a two-row wine rack where each row can fit exactly $ n $ bottles. There are already $ n $ bottles placed on the back row of the rack, where the $ i $ -th bottle from left has height $ a_i $ . The owner of the bar has another $ n $ bottles with distinct heights $ b_1, \ldots, b_n $ that he would like Mayaw to put on the first row. To ensure that all bottles on the rack are visible, the owner requires that each bottle on the back row should not be blocked by the one put in front of it. That is, if a bottle of height $ h $ is put on the $ i $ -th spot (from left) in the first row, then $ h $ must be less than $ a_i $ . However, not all such arrangements are good for the owner. To pay tributes to the Maxi Mountain nearby, he additionally demands that the bottles in the front row should display a mountain-like shape. In particular, the heights of the bottles, when listing from left to right, should form a sequence that is first (non-strictly) increasing and then (non-strictly) decreasing.

Unfortunately, sometimes it is impossible to achieve owner's requirements. That is why Mayaw is also allowed to slightly reduce a bottle's height by removing its cap that has a height of $ 1 $ . In other words, after the removal of the cap, the height of the bottle decreases by exactly $ 1 $ . Of course, exposing the Epah inside the bottle to the open air is detrimental to its quality, and therefore it is desirable to remove as few bottle caps as possible.

Can you help Mayaw determine the minimum number of caps needed to be removed so that he can arrange the bottles in a way that satisfies the owner's requirements? Note that the positions of the bottles in the back row are fixed and Mayaw is not allowed to modify them.

## 输入格式

The first line contains an integer $ n $ which represents the number of bottles in each row. The second line contains $ n $ integers $ a_1, \ldots, a_n $ , the height of the bottles in the back row. The third line contains $ n $ distinct integers $ b_1, \ldots, b_n $ , the height of the bottles in the front row.

- $ 1 \leq n \leq 5 \times 10^5 $
- $ 1 \leq a_i, b_i \leq 10^9 $
- All $ b_i $ 's are distinct.

## 输出格式

Output the minimum number of bottle caps needed to be removed so that Mayaw can arrange the bottles in the desired way. If it is impossible to achieve that (regardless of the number of caps removed), output -1 instead.

## 样例 #1

### 输入

```
5
2 4 6 5 4
1 2 3 4 5
```

### 输出

```
0
```

## 样例 #2

### 输入

```
5
2 3 6 5 4
1 2 3 4 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
6 2 6 6 6
1 2 3 4 5
```

### 输出

```
1
```

## 样例 #4

### 输入

```
5
7 2 7 7 7
1 3 4 5 6
```

### 输出

```
-1
```

## 样例 #5

### 输入

```
10
18 20 16 18 16 10 13 6 4 10
19 10 9 15 4 16 6 12 3 17
```

### 输出

```
4
```



---

---
title: "Affectionate Arrays (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2053I1
tag: ['动态规划 DP', '前缀和']
---

# Affectionate Arrays (Easy Version)

## 题目描述

你是信的开头，诗的内容，童话的结尾。

—— ilem，[《勾指起誓》](https://www.bilibili.com/video/BV1Jb411U7u2/)



本题是简单版问题。两个版本的区别在于，此版本中你需要计算数组的最小长度。只有当你解决了所有版本的问题时才能进行 hack 操作。

Iris 珍视一个整数数组 $a_1, a_2, \ldots, a_n$。她知道这个数组有一个有趣的性质：所有元素的最大绝对值不超过所有元素的和，即 $\max(\lvert a_i\rvert) \leq \sum a_i$。

Iris 定义数组的**无聊值**为其最大子数组$^{\text{∗}}$和。

Iris 的生日即将到来，Victor 打算送她另一个数组 $b_1, b_2, \ldots, b_m$ 作为礼物。出于某些看似明显的原因，他决定数组 $b_1, b_2, \ldots, b_m$ 应满足以下条件：

- $a_1, a_2, \ldots, a_n$ 必须是 $b_1, b_2, \ldots, b_m$ 的子序列$^{\text{†}}$。
- 两个数组的和相同，即 $\sum\limits_{i=1}^n a_i = \sum\limits_{i=1}^m b_i$。
- 数组 $b$ 的无聊值尽可能小。
- 在所有具有最小无聊值的数组中，数组 $b$ 的长度（即 $m$）尽可能小。此时，Iris 将立刻理解他的心意！

即使有上述约束，可能的礼物仍然太多。因此 Victor 请你计算满足所有条件的数组 $b_1, b_2, \ldots, b_m$ 的长度 $\boldsymbol{m}$。他承诺：如果你成功帮助他，他会与你分享 Iris 的生日蛋糕。

注意：由于输入规模较大，你可能需要针对此问题进行优化。

例如，在 C++ 中，只需在 main() 函数开头添加以下代码：

```cpp
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}
```

$^{\text{∗}}$ 若数组 $c$ 可通过删除数组 $d$ 开头和末尾的若干（可能为零或全部）元素得到，则称 $c$ 是 $d$ 的子数组。

$^{\text{†}}$ 若序列 $c$ 可通过删除序列 $d$ 中任意位置的若干（可能为零或全部）元素得到，则称 $c$ 是 $d$ 的子序列。

## 输入格式

每个测试包含多个测试用例。第一行输入一个整数 $t$（$1 \leq t \leq 10^5$）—— 测试用例的数量。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 3\cdot 10^6$）—— 数组 $a_1, a_2, \ldots, a_n$ 的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$-10^9 \leq a_i \leq 10^9$）—— 初始数组。保证 $\max(\lvert a_i\rvert) \leq \sum a_i$。

保证所有测试用例的 $n$ 之和不超过 $3\cdot 10^6$。

## 输出格式

对每个测试用例，输出一行一个整数：满足条件的数组 $b$ 的长度 $m$。

## 说明/提示

第一个测试用例中，$a=[1, 2, 3, 4]$。唯一满足所有条件的数组 $b$ 是 $[1, 2, 3, 4]$，因此输出 4。

第二个测试用例中，$a=[2, -3, 2, 2]$。可能的数组 $b$ 包括 $[1, 2, -3, 2, -1, 2]$ 和 $[2, 1, -3, 2, -1, 2]$，因此输出 6。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
4
1 2 3 4
4
2 -3 2 2
10
2 -7 6 3 -1 4 2 -5 8 -4
20
4 -2 4 3 -2 1 5 2 3 6 -5 -1 -4 -2 -3 5 -3 1 -4 1
```

### 输出

```
4
6
14
25
```



---

---
title: "Club of Young Aircraft Builders (hard version)"
layout: "post"
diff: 省选/NOI-
pid: CF2066D2
tag: ['动态规划 DP', '组合数学']
---

# Club of Young Aircraft Builders (hard version)

## 题目描述

这是该问题的困难版本。各版本间的区别在于此版本中不要求所有 $a_i = 0$。只有当您解决了该问题的所有版本时才能进行 hack。

有一栋 $n$ 层的建筑物，楼层从下到上编号为 $1$ 至 $n$。每层恰好住着一位居民。

今天全体居民有一个重要目标：共同发射至少 $c$ 架纸飞机。居民们将依次发射飞机。当第 $i$ 层的居民发射一架飞机时，从第 $1$ 层到第 $i$ 层的所有居民都能看到它降落到地面的过程。如果从第 $i$ 层居民的视角看，已有至少 $c$ 架飞机被发射，则该居民自己不会再发射更多飞机。已知到当天结束时，从每位居民的视角看至少发射了 $c$ 架飞机，且总共发射了 $m$ 架飞机。

您仔细记录了这次快闪活动，记录了每架飞机的发射者所在楼层。遗憾的是，关于部分飞机的具体发射者信息已经丢失。请找出填补空缺信息使其可信的方案数。由于答案可能很大，请输出其对 $10^9 + 7$ 取模的结果。

也可能您的记录存在错误，导致无法恢复任何有效信息。此时答案视为 $0$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。随后为各测试用例的描述。

每个测试用例的第一行包含三个整数 $n, c, m$（$1 \le n \le 100$，$1 \le c \le 100$，$c \le m \le n \cdot c$）——建筑物的层数、所需最小飞机数、实际发射的飞机数。

每个测试用例的第二行包含 $m$ 个整数 $a_1, a_2, \ldots, a_m$（$0 \le a_i \le n$）——$a_i$ 表示发射第 $i$ 架飞机的居民所在楼层；$a_i = 0$ 表示空缺。

保证所有测试用例的 $m$ 值之和不超过 $10^4$。

## 输出格式

对于每个测试用例，输出用 $1$ 至 $n$ 填补空缺信息使其可信的方案数对 $10^9 + 7$ 取模后的结果。

## 说明/提示

第一个测试样例中，所有六种可能的填补方案如下：
1. $[1, 1, 3, 3]$
2. $[1, 2, 3, 3]$
3. $[1, 3, 2, 3]$
4. $[2, 1, 3, 3]$
5. $[2, 2, 3, 3]$
6. $[3, 1, 2, 3]$

注意数组 $[2, 3, 1, 3]$ 不是有效方案，因为第三架飞机不可能由第 $1$ 层的居民发射——从他们的视角看，当时已有 $c = 2$ 架飞机被发射。

同样地，数组 $[1, 1, 2, 3]$ 也不是有效方案，因为从第 $3$ 层居民的视角看，仅发射了 $1$ 架飞机，而 $c = 2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
3 2 4
0 0 0 0
5 5 7
0 0 0 0 0 0 0
6 1 3
2 0 0
2 3 5
0 0 1 0 2
3 3 4
3 3 3 0
2 1 2
0 1
2 1 2
0 2
5 3 12
0 0 1 0 2 4 0 0 0 5 0 5
```

### 输出

```
6
190
3
2
0
0
1
14
```



---

---
title: "AND x OR"
layout: "post"
diff: 省选/NOI-
pid: CF2077F
tag: ['动态规划 DP']
---

# AND x OR

## 题目描述

假设你有两个长度均为 $k$ 的数组 $c$ 和 $d$。当且仅当 $c$ 可以通过以下操作任意次变换为 $d$ 时，称这对数组 $(c, d)$ 是好的：

- 选择两个不同的下标 $i$ 和 $j$（$1 \leq i, j \leq k$，$i \neq j$）以及一个非负整数 $x$（$0 \leq x < 2^{30}$）。然后执行以下变换：
  - $c_i := c_i \mathbin{\&} x$（其中 $\&$ 表示[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)）
  - $c_j := c_j \mathbin{|} x$（其中 $|$ 表示[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)）

给定两个长度为 $n$ 的数组 $a$ 和 $b$，其中元素均为不超过 $m$ 的非负整数。你可以对这两个数组进行任意次以下两种操作：

1. 选择一个下标 $i$（$1 \leq i \leq n$），令 $a_i := a_i + 1$
2. 选择一个下标 $i$（$1 \leq i \leq n$），令 $b_i := b_i + 1$

注意在执行操作过程中，$a$ 和 $b$ 的元素可能会超过 $m$。

求使得数组对 $(a, b)$ 成为好的数组对所需的最小操作次数。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的第一行输入两个整数 $n$ 和 $m$（$1 \leq n, m \leq 2 \times 10^6$）——分别表示数组 $a$ 和 $b$ 的长度，以及数组中元素的最大初始值。

第二行输入 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \leq a_i \leq m$）——表示数组 $a$。

第三行输入 $n$ 个整数 $b_1, b_2, \ldots, b_n$（$0 \leq b_i \leq m$）——表示数组 $b$。

保证所有测试用例的 $n$ 总和与 $m$ 总和均不超过 $2 \times 10^6$。

## 输出格式

对于每个测试用例，输出一个整数——使得数组对 $(a, b)$ 成为好的数组对所需的最小操作次数。

## 说明/提示

第一个测试用例中，已有 $a = b$。

第二个测试用例中，可以对下标 $i=2$ 执行两次操作 2。数组 $b$ 将变为 $[8, 8, 32]$，此时 $(a, b)$ 成为好的数组对。

第三个测试用例中，可以对下标 $i=1$ 执行一次操作 2，再对下标 $i=2$ 执行一次操作 1。可以证明无法用少于 2 次操作使 $(a, b)$ 成为好的数组对。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
4 3
0 1 2 3
0 1 2 3
3 32
8 9 32
8 6 32
5 64
5 7 16 32 64
4 8 16 32 64
4 11
9 1 4 3
8 11 6 2
5 10
7 9 5 4 2
3 10 6 5 9
```

### 输出

```
0
2
2
0
1
```



---

---
title: "Wish Upon a Satellite (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2084G1
tag: ['动态规划 DP', '数学']
---

# Wish Upon a Satellite (Easy Version)

## 题目描述

这是该问题的简单版本。与困难版本的区别在于，本版本中 $t \le 1000$、$n \le 5000$ 且所有测试用例的 $n$ 之和不超过 $5000$。只有当你解决了该问题的所有版本时才能进行 hack。

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

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 1000$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 5000$）。  
第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \le a_i \le n$）。保证 $a$ 中非 $0$ 的元素互不相同。  
保证所有测试用例的 $n$ 之和不超过 $5000$。

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
title: "Key of Like (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2089C2
tag: ['动态规划 DP', '概率论']
---

# Key of Like (Hard Version)

## 题目描述

这是该问题的困难版本。两个版本之间的区别在于，在这个版本中 $$$k$$$ 可以是非零值。只有当你解决了该问题的所有版本时才能进行 hack。

玩具盒如同装满童年欢愉的冰箱。像脆弱、挣扎、希望……当这样的沉睡者被重新唤醒时，会有什么样的惊喜等待？

M 从母亲那里收到了这个玩具盒作为生日礼物。一位珠宝设计师必定会不遗余力地装饰这件无价杰作：用精美造型的宝石点缀出星空般的天穹。此外，$$$l$$$ 把独特的锁守护着可爱女儿的微型宇宙：一枚花朵造型的发夹、一支磨损的羽毛笔、一个 M 字母形状的气球……每件物品都封存着珍贵的瞬间。

几天前，M 在整理卧室时重新发现了玩具盒，以及一个专为它设计的钥匙环。钥匙环上挂着 $$$(l + k)$$$ 把钥匙，其中 $$$l$$$ 把钥匙能对应地打开 $$$l$$$ 把锁中的一把，而另外 $$$k$$$ 把钥匙只是用于防止暴力破解的仿制品。为了提醒对应关系，M 的母亲为每把钥匙镶嵌了不同类型的宝石。然而，流逝的时光已让 M 的记忆逐渐模糊。

"……所以只能拜托大家了。"M 说着将钥匙环放在桌上。

K 拿起钥匙仔细端详。"这些钥匙的外观无法提供有用信息。恐怕我们必须逐一尝试。"

虽然大家都愿意帮助 M，但没有人有头绪。观察着众人的反应，T 提议："我们来玩个游戏吧。大家轮流尝试钥匙，最终打开最多锁的人最厉害。"

包括 M 在内的 $$$n$$$ 名成员将按固定顺序轮流尝试解锁，直到所有 $$$l$$$ 把锁都被打开。每轮操作中，当前成员只会选择一把钥匙并在恰好一把锁上进行测试。为了尽快打开玩具盒，每位成员都会选择能最大化成功匹配概率的钥匙与锁组合。若存在多个这样的组合，成员会以相等概率随机选择其中之一。显然，若某把锁已与某把钥匙匹配成功，则该锁和钥匙都不会在后续尝试中被再次选择。

假设在最开始时，任意钥匙能打开任意锁的概率均相等。若每个人始终基于所有历史尝试选择最优的钥匙与锁组合，每位成员成功匹配的期望次数分别是多少？

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数 $$$t$$$（$$$1 \le t \le 100$$$）。接下来是每个测试用例的描述。

输入仅一行包含三个整数 $$$n$$$、$$$l$$$、$$$k$$$（$$$1 \leq n \leq 100$$$，$$$1 \leq l \leq 5000$$$，$$$0 \leq k \leq 25$$$）——参与游戏的成员数、锁的数量和仿制钥匙的数量。

保证所有测试用例的 $$$l$$$ 之和不超过 $$$5000$$$。


## 输出格式

对于每个测试用例，输出一行包含 $$$n$$$ 个整数 $$$e_1, \ldots, e_n$$$，其中 $$$e_i$$$ 表示第 $$$i$$$ 位成员的期望成功匹配次数，结果对 $$$10^9 + 7$$$ 取模。

形式化地，令 $$$M = 10^9 + 7$$$。可以证明精确答案可以表示为不可约分数 $$$\frac{p}{q}$$$，其中 $$$p$$$ 和 $$$q$$$ 为整数且 $$$q \not \equiv 0 \pmod{M}$$$。输出整数 $$$p \cdot q^{-1} \bmod M$$$。换句话说，输出满足 $$$0 \le x < M$$$ 且 $$$e_i \cdot q \equiv p \pmod{M}$$$ 的整数 $$$e_i$$$。

## 说明/提示

对于第一个测试用例，只有 $$$1$$$ 把锁，因此策略永远是选择任何未被尝试过的钥匙。由于总共有 $$$1 + 4 = 5$$$ 把钥匙，每位成员成功打开锁的概率（即期望成功次数）分别为 $$$2/5$$$、$$$2/5$$$、$$$1/5$$$。

对于第二个测试用例，恰好有 $$$2$$$ 把锁和 $$$2$$$ 把钥匙，每把钥匙对应一把锁。在缺乏额外信息时，第一位成员会以相等概率随机选择钥匙与锁的组合，成功概率为 $$$1/2$$$。

- 若第一位成员成功，第二位成员将用另一把钥匙打开另一把锁。
- 若第一位成员失败，则她选择的钥匙能打开另一把锁，而另一把钥匙必定对应她选择的锁。这一信息将使得第二位和第三位成员都能打开一把锁。

综上，期望成功次数为：

$$ 
\begin{split}
e_1 &= \frac{1}{2} \times 1 + \frac{1}{2} \times 0 = \frac{1}{2} \equiv 500,000,004 \pmod{10^9+7}, \\
e_2 &= \frac{1}{2} \times 1 + \frac{1}{2} \times 1 = 1, \\
e_3 &= \frac{1}{2} \times 0 + \frac{1}{2} \times 1 = \frac{1}{2} \equiv 500,000,004 \pmod{10^9+7}.
\end{split}
$$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3 1 4
3 2 0
25 2 5
4 102 9
```

### 输出

```
800000006 800000006 400000003
500000004 1 500000004
142857144 166666668 615646263 639455787 234126986 257936510 195918369 502040820 478316330 81264173 190523433 471438023 23809524 0 0 0 0 0 0 0 0 0 0 0 0
568832210 85779764 969938175 375449967
```



---

---
title: "Cycling (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2107F2
tag: ['动态规划 DP', '贪心', '斜率优化']
---

# Cycling (Hard Version)

## 题目描述

> 这是此问题的困难版本，和其他版本的区别是此版本中 $1\le n\le 10^6$，且需要对每个前缀都求解。

Leo 骑车去见他的女朋友。在 Leo 的前面有 $n$ 名骑手，从前往后排在第 $i$ 名的骑手的灵活度为 $a_i$。

Leo 将要加速超过前面的所有骑手，他可以执行以下两种操作：
- 当他在骑手 $i$ 后面，骑手 $i+1$ 前面（或 $i=n$）时，付出 $a_i$ 的代价超过骑手 $i$，之后他将在骑手 $i$ 前面，骑手 $i-1$ 后面（如果 $i>1$）；
- 使用他的超级力量交换 $a_i$ 和 $a_j$，代价为 $\vert i-j\vert$。

请你找出超过所有 $n$ 名骑手的最小代价。

额外地，Leo 想知道对于每个 $i(1\le i\le n)$，当只有骑手 $1,2,\cdots,i$ 存在时，他超过所有 $i$ 名骑手的最小代价。

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 10^4)$，表示数据组数。

对于每组数据，第一行一个整数 $n(1\le n\le 10^6)$。\
第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n(1\le a_i\le 10^9)$。

保证单个测试点中 $\sum n\le 10^6$。

## 输出格式

对于每组数据，输出一行 $n$ 个整数，第 $i$ 个数表示只存在前 $i$ 个骑手时的答案。

## 说明/提示

**样例解释**

第一组数据中，当存在所有 $n$ 名骑手时，一组操作如下所示：
- 交换 $a_2$ 和 $a_3$，之后 $a=(1,4,2)$，代价为 $1$；
- 超过第 $3$ 名骑手，代价为 $2$；
- 交换 $a_1$ 和 $a_2$，$a=(4,1,2)$，代价为 $1$；
- 超过第 $2$ 名骑手，代价为 $1$；
- 交换 $a_1$ 和 $a_2$，$a=(1,4,2)$，代价为 $1$；
- 超过第 $1$ 名骑手，代价为 $1$。

总代价为 $7$。可以证明这是最小的代价。

第二组数据中，当存在所有 $n$ 名骑手时，如果一直执行“超过”操作，花费为 $4$。可以证明这是最小的代价。

By chenxi2009

## 样例 #1

### 输入

```
4
3
1 2 4
4
1 1 1 1
2
1 2
4
4 1 3 2
```

### 输出

```
1 3 7
1 2 3 4
1 3
4 3 6 8
```



---

---
title: "Piglet's Birthday"
layout: "post"
diff: 省选/NOI-
pid: CF248E
tag: ['动态规划 DP', '期望']
---

# Piglet's Birthday

## 题目描述

Piglet has got a birthday today. His friend Winnie the Pooh wants to make the best present for him — a honey pot. Of course Winnie realizes that he won't manage to get the full pot to Piglet. In fact, he is likely to eat all the honey from the pot. And as soon as Winnie planned a snack on is way, the pot should initially have as much honey as possible.

The day before Winnie the Pooh replenished his honey stocks. Winnie-the-Pooh has $ n $ shelves at home, each shelf contains some, perhaps zero number of honey pots. During the day Winnie came to the honey shelves $ q $ times; on the $ i $ -th time he came to some shelf $ u_{i} $ , took from it some pots $ k_{i} $ , tasted the honey from each pot and put all those pots on some shelf $ v_{i} $ . As Winnie chose the pots, he followed his intuition. And that means that among all sets of $ k_{i} $ pots on shelf $ u_{i} $ , he equiprobably chooses one.

Now Winnie remembers all actions he performed with the honey pots. He wants to take to the party the pot he didn't try the day before. For that he must know the mathematical expectation of the number $ m $ of shelves that don't have a single untasted pot. To evaluate his chances better, Winnie-the-Pooh wants to know the value $ m $ after each action he performs.

Your task is to write a program that will find those values for him.

## 输入格式

The first line of the input contains a single number $ n $ ( $ 1<=n<=10^{5} $ ) — the number of shelves at Winnie's place. The second line contains $ n $ integers $ a_{i} $ ( $ 1<=i<=n $ , $ 0<=a_{i}<=100 $ ) — the number of honey pots on a shelf number $ i $ .

The next line contains integer $ q $ ( $ 1<=q<=10^{5} $ ) — the number of actions Winnie did the day before. Then follow $ q $ lines, the $ i $ -th of them describes an event that follows chronologically; the line contains three integers $ u_{i} $ , $ v_{i} $ and $ k_{i} $ ( $ 1<=u_{i},v_{i}<=n $ , $ 1<=k_{i}<=5 $ ) — the number of the shelf from which Winnie took pots, the number of the shelf on which Winnie put the pots after he tasted each of them, and the number of the pots Winnie tasted, correspondingly.

Consider the shelves with pots numbered with integers from 1 to $ n $ . It is guaranteed that Winnie-the-Pooh Never tried taking more pots from the shelf than it has.

## 输出格式

For each Winnie's action print the value of the mathematical expectation $ m $ by the moment when this action is performed. The relative or absolute error of each value mustn't exceed $ 10^{-9} $ .

## 样例 #1

### 输入

```
3
2 2 3
5
1 2 1
2 1 2
1 2 2
3 1 1
3 2 2

```

### 输出

```
0.000000000000
0.333333333333
1.000000000000
1.000000000000
2.000000000000

```



---

---
title: "Broken robot"
layout: "post"
diff: 省选/NOI-
pid: CF24D
tag: ['动态规划 DP', '期望', '高斯消元']
---

# Broken robot

## 题目描述

## 题意翻译
$n$ 行 $m$ 列的矩阵，现在在 $(x,y)$，每次等概率向左，右，下走或原地不动，但不能走出去，问走到最后一行期望的步数。

注意，$(1,1)$ 是木板的左上角，$(n,m)$ 是木板的右下角。

## 输入格式

第一行为两个整数 $n,m$。

第二行为两个整数 $x,y$。

## 输出格式

一行，输出所需移动步数的数学期望值，至少保留 $4$ 位小数的值。

## 说明/提示

$1\le n,m\le 10^3$，$1\le x\le n$，$1\le y\le m$。

## 样例 #1

### 输入

```
10 10
10 4

```

### 输出

```
0.0000000000

```

## 样例 #2

### 输入

```
10 14
5 14

```

### 输出

```
18.0038068653

```



---

---
title: "Little Elephant and Broken Sorting"
layout: "post"
diff: 省选/NOI-
pid: CF258D
tag: ['动态规划 DP']
---

# Little Elephant and Broken Sorting

## 题目描述

The Little Elephant loves permutations of integers from $ 1 $ to $ n $ very much. But most of all he loves sorting them. To sort a permutation, the Little Elephant repeatedly swaps some elements. As a result, he must receive a permutation $ 1,2,3,...,n $ .

This time the Little Elephant has permutation $ p_{1},p_{2},...,p_{n} $ . Its sorting program needs to make exactly $ m $ moves, during the $ i $ -th move it swaps elements that are at that moment located at the $ a_{i} $ -th and the $ b_{i} $ -th positions. But the Little Elephant's sorting program happened to break down and now on every step it can equiprobably either do nothing or swap the required elements.

Now the Little Elephant doesn't even hope that the program will sort the permutation, but he still wonders: if he runs the program and gets some permutation, how much will the result of sorting resemble the sorted one? For that help the Little Elephant find the mathematical expectation of the number of permutation inversions after all moves of the program are completed.

We'll call a pair of integers $ i,j $ $ (1<=i<j<=n) $ an inversion in permutatuon $ p_{1},p_{2},...,p_{n} $ , if the following inequality holds: $ p_{i}>p_{j} $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n,m<=1000,n>1) $ — the permutation size and the number of moves. The second line contains $ n $ distinct integers, not exceeding $ n $ — the initial permutation. Next $ m $ lines each contain two integers: the $ i $ -th line contains integers $ a_{i} $ and $ b_{i} $ $ (1<=a_{i},b_{i}<=n,a_{i}≠b_{i}) $ — the positions of elements that were changed during the $ i $ -th move.

## 输出格式

In the only line print a single real number — the answer to the problem. The answer will be considered correct if its relative or absolute error does not exceed $ 10^{-6} $ .

## 样例 #1

### 输入

```
2 1
1 2
1 2

```

### 输出

```
0.500000000

```

## 样例 #2

### 输入

```
4 3
1 3 2 4
1 2
2 3
1 4

```

### 输出

```
3.000000000

```



---

---
title: "Positions in Permutations"
layout: "post"
diff: 省选/NOI-
pid: CF285E
tag: ['动态规划 DP', '容斥原理']
---

# Positions in Permutations

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

We'll call position $ i $ ( $ 1<=i<=n $ ) in permutation $ p_{1},p_{2},...,p_{n} $ good, if $ |p[i]-i|=1 $ . Count the number of permutations of size $ n $ with exactly $ k $ good positions. Print the answer modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The single line contains two space-separated integers $ n $ and $ k $ ( $ 1<=n<=1000,0<=k<=n $ ).

## 输出格式

Print the number of permutations of length $ n $ with exactly $ k $ good positions modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

The only permutation of size 1 has 0 good positions.

Permutation $ (1,2) $ has 0 good positions, and permutation $ (2,1) $ has 2 positions.

Permutations of size 3:

1. $ (1,2,3) $ — 0 positions
2. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/0be2e55cf7a19e2daea8429a422511a827d2e236.png) — 2 positions
3. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/581bad7452cc25f3e2dca31dac99a205bf6361ef.png) — 2 positions
4. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/aad15ec07c7621cca60c3be370547e4457323e38.png) — 2 positions
5. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285E/b2a9b87daae026f62e110bd34347625817635c68.png) — 2 positions
6. $ (3,2,1) $ — 0 positions

## 样例 #1

### 输入

```
1 0

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3 2

```

### 输出

```
4

```

## 样例 #4

### 输入

```
4 1

```

### 输出

```
6

```

## 样例 #5

### 输入

```
7 4

```

### 输出

```
328

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
title: "Ciel and Gondolas"
layout: "post"
diff: 省选/NOI-
pid: CF321E
tag: ['动态规划 DP', '单调队列', '凸完全单调性（wqs 二分）']
---

# Ciel and Gondolas

## 题目描述

Fox Ciel is in the Amusement Park. And now she is in a queue in front of the Ferris wheel. There are $ n $ people (or foxes more precisely) in the queue: we use first people to refer one at the head of the queue, and $ n $ -th people to refer the last one in the queue.

There will be $ k $ gondolas, and the way we allocate gondolas looks like this:

- When the first gondolas come, the $ q_{1} $ people in head of the queue go into the gondolas.
- Then when the second gondolas come, the $ q_{2} $ people in head of the remain queue go into the gondolas. ...
- The remain $ q_{k} $ people go into the last ( $ k $ -th) gondolas.

Note that $ q_{1} $ , $ q_{2} $ , ..., $ q_{k} $ must be positive. You can get from the statement that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF321E/5aa86331c628d3d47e29fa23648bea351737ffff.png) and $ q_{i}>0 $ .

You know, people don't want to stay with strangers in the gondolas, so your task is to find an optimal allocation way (that is find an optimal sequence $ q $ ) to make people happy. For every pair of people $ i $ and $ j $ , there exists a value $ u_{ij} $ denotes a level of unfamiliar. You can assume $ u_{ij}=u_{ji} $ for all $ i,j $ $ (1<=i,j<=n) $ and $ u_{ii}=0 $ for all $ i $ $ (1<=i<=n) $ . Then an unfamiliar value of a gondolas is the sum of the levels of unfamiliar between any pair of people that is into the gondolas.

A total unfamiliar value is the sum of unfamiliar values for all gondolas. Help Fox Ciel to find the minimal possible total unfamiliar value for some optimal allocation.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=4000 $ and $ 1<=k<=min(n,800) $ ) — the number of people in the queue and the number of gondolas. Each of the following $ n $ lines contains $ n $ integers — matrix $ u $ , ( $ 0<=u_{ij}<=9 $ , $ u_{ij}=u_{ji} $ and $ u_{ii}=0 $ ).

Please, use fast input methods (for example, please use BufferedReader instead of Scanner for Java).

## 输出格式

Print an integer — the minimal possible total unfamiliar value.

## 说明/提示

In the first example, we can allocate people like this: {1, 2} goes into a gondolas, {3, 4, 5} goes into another gondolas.

In the second example, an optimal solution is : {1, 2, 3} | {4, 5, 6} | {7, 8}.

## 样例 #1

### 输入

```
5 2
0 0 1 1 1
0 0 1 1 1
1 1 0 0 0
1 1 0 0 0
1 1 0 0 0

```

### 输出

```
0

```

## 样例 #2

### 输入

```
8 3
0 1 1 1 1 1 1 1
1 0 1 1 1 1 1 1
1 1 0 1 1 1 1 1
1 1 1 0 1 1 1 1
1 1 1 1 0 1 1 1
1 1 1 1 1 0 1 1
1 1 1 1 1 1 0 1
1 1 1 1 1 1 1 0

```

### 输出

```
7

```

## 样例 #3

### 输入

```
3 2
0 2 0
2 0 3
0 3 0

```

### 输出

```
2

```



---

---
title: "Jeff and Brackets"
layout: "post"
diff: 省选/NOI-
pid: CF351C
tag: ['动态规划 DP', '矩阵加速']
---

# Jeff and Brackets

## 题目描述

Jeff loves regular bracket sequences.

Today Jeff is going to take a piece of paper and write out the regular bracket sequence, consisting of $ nm $ brackets. Let's number all brackets of this sequence from $ 0 $ to $ nm $ - $ 1 $ from left to right. Jeff knows that he is going to spend $ a_{i\ mod\ n} $ liters of ink on the $ i $ -th bracket of the sequence if he paints it opened and $ b_{i\ mod\ n} $ liters if he paints it closed.

You've got sequences $ a $ , $ b $ and numbers $ n $ , $ m $ . What minimum amount of ink will Jeff need to paint a regular bracket sequence of length $ nm $ ?

Operation $ x\ mod\ y $ means taking the remainder after dividing number $ x $ by number $ y $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=20; 1<=m<=10^{7}; $ $ m $ is even). The next line contains $ n $ integers: $ a_{0} $ , $ a_{1} $ , $ ... $ , $ a_{n-1} $ $ (1<=a_{i}<=10) $ . The next line contains $ n $ integers: $ b_{0} $ , $ b_{1} $ , $ ... $ , $ b_{n-1} $ $ (1<=b_{i}<=10) $ . The numbers are separated by spaces.

## 输出格式

In a single line print the answer to the problem — the minimum required amount of ink in liters.

## 说明/提示

In the first test the optimal sequence is: $ ()()()()()() $ , the required number of ink liters is $ 12 $ .

## 样例 #1

### 输入

```
2 6
1 2
2 1

```

### 输出

```
12

```

## 样例 #2

### 输入

```
1 10000000
2
3

```

### 输出

```
25000000

```



---

---
title: "Dead Ends"
layout: "post"
diff: 省选/NOI-
pid: CF53E
tag: ['动态规划 DP', '状态合并', '容斥原理']
---

# Dead Ends

## 题目描述

Bertown的生活变得困难了起来。这个城市有太多的道路，而且政府花费了太多来维护这些道路。这里有$n$个节点和$m$条双向道路，且两两节点之间可以通过道路相互到达。现在市长想要关闭一些道路，使最后总共有$n-1$条道路留下，并且所以节点之间仍然联通。另外，市长很关心终点，也就是只有一条道路可以到达的点的数量。终点不能太多也不能太少。在讨论过这个问题之后，市长和他的助手们觉得在应该关闭的道路关闭后，应该总共有恰好$k$个终点。你的任务是求出满足以下三个条件的方案数：

1.有恰好$n-1$条道路保留下来；

2.整张道路图仍然联通；

3.最后有恰好$k$个终点在道路图上。

如果有一条道路在第一种方案中被关闭而在第二种方案中没有被关闭，那么我们认为这两种方案不同。

## 输入格式

第一行有三个整数$n$，$m$和$k$（$3\leq n\leq10 , n-1\leq m\leq \frac {n(n-1)} {2} , 2\leq k\leq n-1$），依次代表了节点、道路和终点的数量。随后$m$行，每行包含两个不同的整数$v_1$和$v_2$（$1\leq v_1 , v_2\leq n , v_1 \not= v_2$），代表一条道路连接的两个节点。每一对节点之间最多有一条道路。节点被编号为1到$n$。保证初始的图联通。

## 输出格式

一个整数：满足条件的方案数。

## 样例 #1

### 输入

```
3 3 2
1 2
2 3
1 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 6 2
1 2
2 3
3 4
4 1
1 3
2 4

```

### 输出

```
12

```

## 样例 #3

### 输入

```
4 6 3
1 2
2 3
3 4
4 1
1 3
2 4

```

### 输出

```
4

```



---

---
title: "Road Improvement"
layout: "post"
diff: 省选/NOI-
pid: CF543D
tag: ['动态规划 DP']
---

# Road Improvement

## 题目描述

这个国家有n座城市和n-1条双向道路，你可以沿道路从一个城市到任意一个其他城市。这些城市被编号为整数1到n。

所有的道路最初都是不良的，但是政府想要改善一些路的状况。我们认为如果从首都x城到其他城市的道路最多包含一条不良道路，市民会对此感到满意。
你的任务是——对于每一个可能的x，求出所有能够满足市民条件的改良道路的方式。因为结果可能很大，你需要输出mod 1000000007 ( 10^9+7 )后的结果。

## 输入格式

第一行有一个整数n ( 2<=n<=2⋅10^5 )——代表城市的数量。
第二行包括n-1个描述城市道路的整数p2,p3,p4,...,pn ( 1<=pi<=i−1 ) pi表示有一条连接城市pi和城市i 的道路。

## 输出格式

输出n个整数a1,a2,...,an ，ai表示在城市i为首都时，改良道路的方式mod 1000000007 ( 10^9+7 )后的结果。

## 样例 #1

### 输入

```
3
1 1

```

### 输出

```
4 3 3
```

## 样例 #2

### 输入

```
5
1 2 3 4

```

### 输出

```
5 8 9 8 5
```



---

---
title: "Beautiful numbers"
layout: "post"
diff: 省选/NOI-
pid: CF55D
tag: ['动态规划 DP', '数位 DP', '状态合并']
---

# Beautiful numbers

## 题目描述

Volodya is an odd boy and his taste is strange as well. It seems to him that a positive integer number is beautiful if and only if it is divisible by each of its nonzero digits. We will not argue with this and just count the quantity of beautiful numbers in given ranges.

## 输入格式

The first line of the input contains the number of cases $ t $ ( $ 1<=t<=10 $ ). Each of the next $ t $ lines contains two natural numbers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=9·10^{18} $ ).

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cin (also you may use %I64d).

## 输出格式

Output should contain $ t $ numbers — answers to the queries, one number per line — quantities of beautiful numbers in given intervals (from $ l_{i} $ to $ r_{i} $ , inclusively).

## 样例 #1

### 输入

```
1
1 9

```

### 输出

```
9

```

## 样例 #2

### 输入

```
1
12 15

```

### 输出

```
2

```



---

---
title: "Mausoleum"
layout: "post"
diff: 省选/NOI-
pid: CF567F
tag: ['动态规划 DP', '递推']
---

# Mausoleum

## 题目描述

King of Berland Berl IV has recently died. Hail Berl V! As a sign of the highest achievements of the deceased king the new king decided to build a mausoleum with Berl IV's body on the main square of the capital.

The mausoleum will be constructed from $ 2n $ blocks, each of them has the shape of a cuboid. Each block has the bottom base of a $ 1×1 $ meter square. Among the blocks, exactly two of them have the height of one meter, exactly two have the height of two meters, ..., exactly two have the height of $ n $ meters.

The blocks are arranged in a row without spacing one after the other. Of course, not every arrangement of blocks has the form of a mausoleum. In order to make the given arrangement in the form of the mausoleum, it is necessary that when you pass along the mausoleum, from one end to the other, the heights of the blocks first were non-decreasing (i.e., increasing or remained the same), and then — non-increasing (decrease or remained unchanged). It is possible that any of these two areas will be omitted. For example, the following sequences of block height meet this requirement:

- $ [1,2,2,3,4,4,3,1] $ ;
- $ [1,1] $ ;
- $ [2,2,1,1] $ ;
- $ [1,2,3,3,2,1] $ .

Suddenly, $ k $ more requirements appeared. Each of the requirements has the form: " $ h[x_{i}] $ sign $ _{i} $ $ h[y_{i}] $ ", where $ h[t] $ is the height of the $ t $ -th block, and a sign $ _{i} $ is one of the five possible signs: '=' (equals), '<' (less than), '>' (more than), '<=' (less than or equals), '>=' (more than or equals). Thus, each of the $ k $ additional requirements is given by a pair of indexes $ x_{i} $ , $ y_{i} $ ( $ 1<=x_{i},y_{i}<=2n $ ) and sign sign $ _{i} $ .

Find the number of possible ways to rearrange the blocks so that both the requirement about the shape of the mausoleum (see paragraph 3) and the $ k $ additional requirements were met.

## 输入格式

The first line of the input contains integers $ n $ and $ k $ ( $ 1<=n<=35 $ , $ 0<=k<=100 $ ) — the number of pairs of blocks and the number of additional requirements.

Next $ k $ lines contain listed additional requirements, one per line in the format " $ x_{i} $ sign $ _{i} $ $ y_{i} $ " ( $ 1<=x_{i},y_{i}<=2n $ ), and the sign is on of the list of the five possible signs.

## 输出格式

Print the sought number of ways.

## 样例 #1

### 输入

```
3 0

```

### 输出

```
9

```

## 样例 #2

### 输入

```
3 1
2 > 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
4 1
3 = 6

```

### 输出

```
3

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
title: "Kingdom and its Cities"
layout: "post"
diff: 省选/NOI-
pid: CF613D
tag: ['动态规划 DP', '虚树']
---

# Kingdom and its Cities

## 题目描述

Meanwhile, the kingdom of K is getting ready for the marriage of the King's daughter. However, in order not to lose face in front of the relatives, the King should first finish reforms in his kingdom. As the King can not wait for his daughter's marriage, reforms must be finished as soon as possible.

The kingdom currently consists of $ n $ cities. Cities are connected by $ n-1 $ bidirectional road, such that one can get from any city to any other city. As the King had to save a lot, there is only one path between any two cities.

What is the point of the reform? The key ministries of the state should be relocated to distinct cities (we call such cities important). However, due to the fact that there is a high risk of an attack by barbarians it must be done carefully. The King has made several plans, each of which is described by a set of important cities, and now wonders what is the best plan.

Barbarians can capture some of the cities that are not important (the important ones will have enough protection for sure), after that the captured city becomes impassable. In particular, an interesting feature of the plan is the minimum number of cities that the barbarians need to capture in order to make all the important cities isolated, that is, from all important cities it would be impossible to reach any other important city.

Help the King to calculate this characteristic for each of his plan.

## 输入格式

The first line of the input contains integer $ n $ ( $ 1<=n<=100000 $ ) — the number of cities in the kingdom.

Each of the next $ n-1 $ lines contains two distinct integers $ u_{i} $ , $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) — the indices of the cities connected by the $ i $ -th road. It is guaranteed that you can get from any city to any other one moving only along the existing roads.

The next line contains a single integer $ q $ ( $ 1<=q<=100000 $ ) — the number of King's plans.

Each of the next $ q $ lines looks as follows: first goes number $ k_{i} $ — the number of important cities in the King's plan, ( $ 1<=k_{i}<=n $ ), then follow exactly $ k_{i} $ space-separated pairwise distinct numbers from 1 to $ n $ — the numbers of important cities in this plan.

The sum of all $ k_{i} $ 's does't exceed $ 100000 $ .

## 输出格式

For each plan print a single integer — the minimum number of cities that the barbarians need to capture, or print $ -1 $ if all the barbarians' attempts to isolate important cities will not be effective.

## 说明/提示

In the first sample, in the first and the third King's plan barbarians can capture the city 3, and that will be enough. In the second and the fourth plans all their attempts will not be effective.

In the second sample the cities to capture are 3 and 5.

## 样例 #1

### 输入

```
4
1 3
2 3
4 3
4
2 1 2
3 2 3 4
3 1 2 4
4 1 2 3 4

```

### 输出

```
1
-1
1
-1

```

## 样例 #2

### 输入

```
7
1 2
2 3
3 4
1 5
5 6
5 7
1
4 2 4 6 7

```

### 输出

```
2

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
title: "Selling Souvenirs"
layout: "post"
diff: 省选/NOI-
pid: CF808E
tag: ['动态规划 DP', '二分']
---

# Selling Souvenirs

## 题目描述

## 题目背景
Berland经过了多次改革后，许多游客打算来这儿游玩。居民们知道这是一个改行旅游服务业来赚钱的好机会，Petya也离开了他以前工作的IT公司，改在市场买礼品了。

像平常一样，今早Petya回来到市场。他有 $n$ 个不同的礼品要卖；第 $i$ 个礼品有重量 $w_{i}$ 和价格 $c_{i}$ 两个属性。Petya知道他不能把所有礼品扛到市场，便想要选一部分总重量不超过 $m$ 的礼品，而总价格越高越好。

帮帮Petya确定最大的总价格吧。

## 输入格式

第一行包括两个整数 $n$ 和 $m$（$1<=n<=100000$ , $1<=m<=300000$）——Petya的礼品数量和他能带去市场的最大重量。

然后下面$n$行中第$i$行各有两个整数 $w_{i}$  
和 $c_{i}$（$1<=w_{i}<=3$ , $1<=c_{i}<=10^{9}$）——第 $i$ 个礼品的重量和价格。

## 输出格式

输出一个数字——Petya能带去的礼品的最大总价格。

## 样例 #1

### 输入

```
1 1
2 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
2 2
1 3
2 2

```

### 输出

```
3

```

## 样例 #3

### 输入

```
4 3
3 10
2 7
2 8
1 1

```

### 输出

```
10

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
title: "Two Subsequences"
layout: "post"
diff: 省选/NOI-
pid: CF83E
tag: ['动态规划 DP', '字典树 Trie']
---

# Two Subsequences

## 题目描述

# CF83E 两个子序列
在一堂IT课上，Valera 学习了数据压缩。我们现在将向你介绍老师所讲解的一种新的数据压缩方法。

定义压缩函数 $f()$：

- $f($空序列$)=$ 空字符串
- 对于任意一个字符串 $s$，$f(s)=s$。
- 对于任意两个字符串 $s_{1}$，$s_{2}$，$f(s1,s2)$ 为包含前缀 $s_{1}$ 且包含后缀 $s_{2}$ 的字符串中长度最小的一个。
- 对于任意 $n$ 个字符串，$f({s_{1},s_{2},\ldots,s_{n}})=f(f({s_{1},s_{2},\ldots,s_{n-1}}),s_{n})$

例如：
1. $ f(001,011)=0011 $ 
2. $ f(111,011)=111011 $ 
2. $f(000,000,111)=f(f(000,000),111)=f(000,111)=000111 $ .

现在 Valera 面临一个难题：他需要将给定的需要压缩的序列 ${a_{1},a_{2},\ldots,a_{n}}$ 分成两个新的序列 ${b_{1},b_{2},\ldots,b_{k}}$ 和 ${c_{1},c_{2},\ldots,c_{m}}$ $(k+m=n)$ ，使得$S=|f({b_{1},b_{2},\ldots,b_{k}})|+|f({c_{1},c_{2},\ldots,c_{m}})|$ 的值最小。这里 $|p|$ 表示字符串 $p$ 的长度。

**注意**：
1. 不允许在子序列中更改元素的相对顺序。
2. 可以使得 $mk=0$ 即可以使得序列 $b$ $c$ 中的一个为空。
3. 对于原序列 $a$ 中的任意一项 $a_{i}$，不得既不存在于 $b$ 中，亦不存在于 $c$ 中。也不得同时存在于 $b$ 和 $c$ 中。
4.  $b$  $c$ 中的元素在 $a$ 中不必连续，即 $b$ 和 $c$ 的元素可以在 $a$ 中交替出现(参见样例2、3)。

## 输入格式

第一行一个整数 $n$，表示序列 $a$ 的项数。

接下来 $n$ 行，每行一个字符串，第 $i+1$ 行输入的字符串表示序列 $a$ 的第 $i$ 项，即 $a_{i}$。

输入数据保证序列 $a$ 中的所有项长度相同，并且仅由数字 $0$ 或 $1$ 组成。

## 输出格式

一行一个整数，$S$ 的最小值。
### 样例解释
1. 样例解释1

最佳的方法为：一个子序列为空，另一个子序列等于原始序列 $a$。此时$S_{min}=|f(01,10,01)|=|f(f(01,00),01)|=| f(010,01)|=|0101|=4$。故输出 $4$。

2. 最好的选择是：$b={000,001}$，$c={111,110}$。此时$S_{min}=|f（000,001）|+|f（111,110）|=|0001|+|1110|=8$。故输出 $8$。

3. 最好的选择是：$b={10101,01010,01000}，c={11111,10010}$。此时$S_{min}=(|10101000 |+|111110010 |=17$。故输出 $16$。

Translated by: @xhz0311

## 样例 #1

### 输入

```
3
01
10
01

```

### 输出

```
4

```

## 样例 #2

### 输入

```
4
000
111
110
001

```

### 输出

```
8

```

## 样例 #3

### 输入

```
5
10101
01010
11111
01000
10010

```

### 输出

```
17

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
title: "Gotta Go Fast"
layout: "post"
diff: 省选/NOI-
pid: CF865C
tag: ['动态规划 DP', '二分', '期望']
---

# Gotta Go Fast

## 题目描述

You're trying to set the record on your favorite video game. The game consists of $ N $ levels, which must be completed sequentially in order to beat the game. You usually complete each level as fast as possible, but sometimes finish a level slower. Specifically, you will complete the $ i $ -th level in either $ F_{i} $ seconds or $ S_{i} $ seconds, where $ F_{i}&lt;S_{i} $ , and there's a $ P_{i} $ percent chance of completing it in $ F_{i} $ seconds. After completing a level, you may decide to either continue the game and play the next level, or reset the game and start again from the first level. Both the decision and the action are instant.

Your goal is to complete all the levels sequentially in at most $ R $ total seconds. You want to minimize the expected amount of time playing before achieving that goal. If you continue and reset optimally, how much total time can you expect to spend playing?

## 输入格式

The first line of input contains integers $ N $ and $ R $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF865C/2edb953537ce7c8db1b280cf3e041068762c4830.png), the number of levels and number of seconds you want to complete the game in, respectively. $ N $ lines follow. The $ i $ th such line contains integers $ F_{i},S_{i},P_{i} $ $ (1<=F_{i}&lt;S_{i}<=100,80<=P_{i}<=99) $ , the fast time for level $ i $ , the slow time for level $ i $ , and the probability (as a percentage) of completing level $ i $ with the fast time.

## 输出格式

Print the total expected time. Your answer must be correct within an absolute or relative error of $ 10^{-9} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer will be considered correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF865C/cde5c1e0715ef65086b3065853dd22ee5a37eede.png).

## 说明/提示

In the first example, you never need to reset. There's an $ 81% $ chance of completing the level in $ 2 $ seconds and a $ 19% $ chance of needing $ 8 $ seconds, both of which are within the goal time. The expected time is $ 0.81·2+0.19·8=3.14 $ .

In the second example, you should reset after the first level if you complete it slowly. On average it will take $ 0.25 $ slow attempts before your first fast attempt. Then it doesn't matter whether you complete the second level fast or slow. The expected time is $ 0.25·30+20+0.85·3+0.15·9=31.4 $ .

## 样例 #1

### 输入

```
1 8
2 8 81

```

### 输出

```
3.14

```

## 样例 #2

### 输入

```
2 30
20 30 80
3 9 85

```

### 输出

```
31.4

```

## 样例 #3

### 输入

```
4 319
63 79 89
79 97 91
75 87 88
75 90 83

```

### 输出

```
314.159265358

```



---

---
title: "Yet Another Minimization Problem"
layout: "post"
diff: 省选/NOI-
pid: CF868F
tag: ['动态规划 DP', '分治']
---

# Yet Another Minimization Problem

## 输出格式

$2 \leq n \leq 10^5$，$2 \leq k \leq \min(n,20)$，$1 \leq a_i \leq n$ 。

## 样例 #1

### 输入

```
7 3
1 1 3 3 3 2 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10 2
1 2 1 2 1 2 1 2 1 2

```

### 输出

```
8

```

## 样例 #3

### 输入

```
13 3
1 2 2 2 1 2 1 1 1 2 2 1 1

```

### 输出

```
9

```



---

---
title: "New Year and Arbitrary Arrangement"
layout: "post"
diff: 省选/NOI-
pid: CF908D
tag: ['动态规划 DP', '期望', '逆元']
---

# New Year and Arbitrary Arrangement

## 题目描述

You are given three integers $ k $ , $ p_{a} $ and $ p_{b} $ .

You will construct a sequence with the following algorithm: Initially, start with the empty sequence. Each second, you do the following. With probability $ p_{a}/(p_{a}+p_{b}) $ , add 'a' to the end of the sequence. Otherwise (with probability $ p_{b}/(p_{a}+p_{b}) $ ), add 'b' to the end of the sequence.

You stop once there are at least $ k $ subsequences that form 'ab'. Determine the expected number of times 'ab' is a subsequence in the resulting sequence. It can be shown that this can be represented by $ P/Q $ , where $ P $ and $ Q $ are coprime integers, and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908D/250bff4a0d2d6149565f6e795de0dbd59e6a92a3.png). Print the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908D/962b3e429ab173c8d460f96cc849d01fcd4a9d47.png).

## 输入格式

The first line will contain three integers integer $ k,p_{a},p_{b} $ ( $ 1<=k<=1000 $ , $ 1<=p_{a},p_{b}<=1000000 $ ).

## 输出格式

Print a single integer, the answer to the problem.

## 说明/提示

The first sample, we will keep appending to our sequence until we get the subsequence 'ab' at least once. For instance, we get the sequence 'ab' with probability 1/4, 'bbab' with probability 1/16, and 'aab' with probability 1/8. Note, it's impossible for us to end with a sequence like 'aabab', since we would have stopped our algorithm once we had the prefix 'aab'.

The expected amount of times that 'ab' will occur across all valid sequences is 2.

For the second sample, the answer is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908D/be8bc2d2b5b20d19237dcaabfc3c3ca4bcb22ac0.png).

## 样例 #1

### 输入

```
1 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 1 4

```

### 输出

```
370000006

```



---

---
title: "Coins Exhibition"
layout: "post"
diff: 省选/NOI-
pid: CF930E
tag: ['动态规划 DP', '离散化', '排序']
---

# Coins Exhibition

## 题目描述

Arkady and Kirill visited an exhibition of rare coins. The coins were located in a row and enumerated from left to right from $ 1 $ to $ k $ , each coin either was laid with its obverse (front) side up, or with its reverse (back) side up.

Arkady and Kirill made some photos of the coins, each photo contained a segment of neighboring coins. Akrady is interested in obverses, so on each photo made by him there is at least one coin with obverse side up. On the contrary, Kirill is interested in reverses, so on each photo made by him there is at least one coin with its reverse side up.

The photos are lost now, but Arkady and Kirill still remember the bounds of the segments of coins each photo contained. Given this information, compute the remainder of division by $ 10^{9}+7 $ of the number of ways to choose the upper side of each coin in such a way, that on each Arkady's photo there is at least one coin with obverse side up, and on each Kirill's photo there is at least one coin with reverse side up.

## 输入格式

The first line contains three integers $ k $ , $ n $ and $ m $ ( $ 1<=k<=10^{9} $ , $ 0<=n,m<=10^{5} $ ) — the total number of coins, the number of photos made by Arkady, and the number of photos made by Kirill, respectively.

The next $ n $ lines contain the descriptions of Arkady's photos, one per line. Each of these lines contains two integers $ l $ and $ r $ ( $ 1<=l<=r<=k $ ), meaning that among coins from the $ l $ -th to the $ r $ -th there should be at least one with obverse side up.

The next $ m $ lines contain the descriptions of Kirill's photos, one per line. Each of these lines contains two integers $ l $ and $ r $ ( $ 1<=l<=r<=k $ ), meaning that among coins from the $ l $ -th to the $ r $ -th there should be at least one with reverse side up.

## 输出格式

Print the only line — the number of ways to choose the side for each coin modulo $ 10^{9}+7=1000000007 $ .

## 说明/提示

In the first example the following ways are possible ('O' — obverse, 'R' — reverse side):

- OROOR,
- ORORO,
- ORORR,
- RROOR,
- RRORO,
- RRORR,
- ORROR,
- ORRRO.

In the second example the information is contradictory: the second coin should have obverse and reverse sides up at the same time, that is impossible. So, the answer is $ 0 $ .

## 样例 #1

### 输入

```
5 2 2
1 3
3 5
2 2
4 5

```

### 输出

```
8

```

## 样例 #2

### 输入

```
5 3 2
1 3
2 2
3 5
2 2
4 5

```

### 输出

```
0

```

## 样例 #3

### 输入

```
60 5 7
1 3
50 60
1 60
30 45
20 40
4 5
6 37
5 18
50 55
22 27
25 31
44 45

```

### 输出

```
732658600

```



---

