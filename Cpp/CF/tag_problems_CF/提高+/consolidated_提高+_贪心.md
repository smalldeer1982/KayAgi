---
title: "MST Company"
layout: "post"
diff: 提高+/省选-
pid: CF125E
tag: ['贪心', '排序', '生成树']
---

# MST Company

## 题目描述

The MST (Meaningless State Team) company won another tender for an important state reform in Berland.

There are $ n $ cities in Berland, some pairs of the cities are connected by roads. Each road has its price. One can move along any road in any direction. The MST team should carry out the repair works on some set of roads such that one can get from any city to any other one moving only along the repaired roads. Moreover, this set should contain exactly $ k $ capital roads (that is, the roads that start or finish in the capital). The number of the capital is 1.

As the budget has already been approved, the MST Company will profit by finding the set with minimum lengths of roads.

## 输入格式

The first input line contains three integers $ n,m,k $ ( $ 1<=n<=5000;0<=m<=10^{5};0<=k&lt;5000 $ ), where $ n $ is the number of cities in the country, $ m $ is the number of roads in the country, $ k $ is the number of capital roads in the required set. Then $ m $ lines enumerate the roads in question. Each road is specified by three numbers $ a_{i},b_{i},w_{i} $ ( $ 1<=a_{i},b_{i}<=n $ ; $ 1<=w<=10^{5} $ ), where $ a_{i},b_{i} $ are the numbers of cities linked by a road and $ w_{i} $ is its length.

Between each pair of cities no more than one road exists. There are no roads that start and finish in one city. The capital's number is 1.

## 输出格式

In the first line print the number of roads in the required set. The second line should contain the numbers of roads included in the sought set. If the sought set does not exist, print -1.

## 样例 #1

### 输入

```
4 5 2
1 2 1
2 3 1
3 4 1
1 3 3
1 4 2

```

### 输出

```
3
1 5 2 
```



---

---
title: "Math Test"
layout: "post"
diff: 提高+/省选-
pid: CF1622E
tag: ['贪心', '状态合并']
---

# Math Test

## 题目描述

Petya is a math teacher. $ n $ of his students has written a test consisting of $ m $ questions. For each student, it is known which questions he has answered correctly and which he has not.

If the student answers the $ j $ -th question correctly, he gets $ p_j $ points (otherwise, he gets $ 0 $ points). Moreover, the points for the questions are distributed in such a way that the array $ p $ is a permutation of numbers from $ 1 $ to $ m $ .

For the $ i $ -th student, Petya knows that he expects to get $ x_i $ points for the test. Petya wonders how unexpected the results could be. Petya believes that the surprise value of the results for students is equal to $ \sum\limits_{i=1}^{n} |x_i - r_i| $ , where $ r_i $ is the number of points that the $ i $ -th student has got for the test.

Your task is to help Petya find such a permutation $ p $ for which the surprise value of the results is maximum possible. If there are multiple answers, print any of them.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n \le 10 $ ; $ 1 \le m \le 10^4 $ ) — the number of students and the number of questions, respectively.

The second line contains $ n $ integers $ x_1, x_2, \dots, x_n $ ( $ 0 \le x_i \le \frac{m(m+1)}{2} $ ), where $ x_i $ is the number of points that the $ i $ -th student expects to get.

This is followed by $ n $ lines, the $ i $ -th line contains the string $ s_i $ ( $ |s_i| = m; s_{i, j} \in \{0, 1\} $ ), where $ s_{i, j} $ is $ 1 $ if the $ i $ -th student has answered the $ j $ -th question correctly, and $ 0 $ otherwise.

The sum of $ m $ for all test cases does not exceed $ 10^4 $ .

## 输出格式

For each test case, print $ m $ integers — a permutation $ p $ for which the surprise value of the results is maximum possible. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3
4 3
5 1 2 2
110
100
101
100
4 4
6 2 0 10
1001
0010
0110
0101
3 6
20 3 15
010110
000101
111111
```

### 输出

```
3 1 2 
2 3 4 1 
3 1 4 5 2 6
```



---

---
title: "Towers"
layout: "post"
diff: 提高+/省选-
pid: CF1637F
tag: ['贪心', '构造']
---

# Towers

## 题目描述

You are given a tree with $ n $ vertices numbered from $ 1 $ to $ n $ . The height of the $ i $ -th vertex is $ h_i $ . You can place any number of towers into vertices, for each tower you can choose which vertex to put it in, as well as choose its efficiency. Setting up a tower with efficiency $ e $ costs $ e $ coins, where $ e > 0 $ .

It is considered that a vertex $ x $ gets a signal if for some pair of towers at the vertices $ u $ and $ v $ ( $ u \neq v $ , but it is allowed that $ x = u $ or $ x = v $ ) with efficiencies $ e_u $ and $ e_v $ , respectively, it is satisfied that $ \min(e_u, e_v) \geq h_x $ and $ x $ lies on the path between $ u $ and $ v $ .

Find the minimum number of coins required to set up towers so that you can get a signal at all vertices.

## 输入格式

The first line contains an integer $ n $ ( $ 2 \le n \le 200\,000 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ h_i $ ( $ 1 \le h_i \le 10^9 $ ) — the heights of the vertices.

Each of the next $ n - 1 $ lines contain a pair of numbers $ v_i, u_i $ ( $ 1 \le v_i, u_i \le n $ ) — an edge of the tree. It is guaranteed that the given edges form a tree.

## 输出格式

Print one integer — the minimum required number of coins.

## 说明/提示

In the first test case it's optimal to install two towers with efficiencies $ 2 $ at vertices $ 1 $ and $ 3 $ .

In the second test case it's optimal to install a tower with efficiency $ 1 $ at vertex $ 1 $ and two towers with efficiencies $ 3 $ at vertices $ 2 $ and $ 5 $ .

In the third test case it's optimal to install two towers with efficiencies $ 6 $ at vertices $ 1 $ and $ 2 $ .

## 样例 #1

### 输入

```
3
1 2 1
1 2
2 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1 3 3 1 3
1 3
5 4
4 3
2 3
```

### 输出

```
7
```

## 样例 #3

### 输入

```
2
6 1
1 2
```

### 输出

```
12
```



---

---
title: "Equal Tree Sums"
layout: "post"
diff: 提高+/省选-
pid: CF1656E
tag: ['贪心', '构造']
---

# Equal Tree Sums

## 题目描述

You are given an undirected unrooted tree, i.e. a connected undirected graph without cycles.

You must assign a nonzero integer weight to each vertex so that the following is satisfied: if any vertex of the tree is removed, then each of the remaining connected components has the same sum of weights in its vertices.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 3 \leq n \leq 10^5 $ ) — the number of vertices of the tree.

The next $ n-1 $ lines of each case contain each two integers $ u, v $ ( $ 1 \leq u,v \leq n $ ) denoting that there is an edge between vertices $ u $ and $ v $ . It is guaranteed that the given edges form a tree.

The sum of $ n $ for all test cases is at most $ 10^5 $ .

## 输出格式

For each test case, you must output one line with $ n $ space separated integers $ a_1, a_2, \ldots, a_n $ , where $ a_i $ is the weight assigned to vertex $ i $ . The weights must satisfy $ -10^5 \leq a_i \leq 10^5 $ and $ a_i \neq 0 $ .

It can be shown that there always exists a solution satisfying these constraints. If there are multiple possible solutions, output any of them.

## 说明/提示

In the first case, when removing vertex $ 1 $ all remaining connected components have sum $ 5 $ and when removing vertex $ 3 $ all remaining connected components have sum $ 2 $ . When removing other vertices, there is only one remaining connected component so all remaining connected components have the same sum.

## 样例 #1

### 输入

```
2
5
1 2
1 3
3 4
3 5
3
1 2
1 3
```

### 输出

```
-3 5 1 2 2
1 1 1
```



---

---
title: "Dog Walking"
layout: "post"
diff: 提高+/省选-
pid: CF1680D
tag: ['贪心']
---

# Dog Walking

## 题目描述

You are walking with your dog, and now you are at the promenade. The promenade can be represented as an infinite line. Initially, you are in the point $ 0 $ with your dog.

You decided to give some freedom to your dog, so you untied her and let her run for a while. Also, you watched what your dog is doing, so you have some writings about how she ran. During the $ i $ -th minute, the dog position changed from her previous position by the value $ a_i $ (it means, that the dog ran for $ a_i $ meters during the $ i $ -th minute). If $ a_i $ is positive, the dog ran $ a_i $ meters to the right, otherwise (if $ a_i $ is negative) she ran $ a_i $ meters to the left.

During some minutes, you were chatting with your friend, so you don't have writings about your dog movement during these minutes. These values $ a_i $ equal zero.

You want your dog to return to you after the end of the walk, so the destination point of the dog after $ n $ minutes should be $ 0 $ .

Now you are wondering: what is the maximum possible number of different integer points of the line your dog could visit on her way, if you replace every $ 0 $ with some integer from $ -k $ to $ k $ (and your dog should return to $ 0 $ after the walk)? The dog visits an integer point if she runs through that point or reaches in it at the end of any minute. Point $ 0 $ is always visited by the dog, since she is initially there.

If the dog cannot return to the point $ 0 $ after $ n $ minutes regardless of the integers you place, print -1.

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1 \le n \le 3000; 1 \le k \le 10^9 $ ) — the number of minutes and the maximum possible speed of your dog during the minutes without records.

The second line of the input contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ), where $ a_i $ is the number of meters your dog ran during the $ i $ -th minutes (to the left if $ a_i $ is negative, to the right otherwise). If $ a_i = 0 $ then this value is unknown and can be replaced with any integer from the range $ [-k; k] $ .

## 输出格式

If the dog cannot return to the point $ 0 $ after $ n $ minutes regardless of the set of integers you place, print -1. Otherwise, print one integer — the maximum number of different integer points your dog could visit if you fill all the unknown values optimally and the dog will return to the point $ 0 $ at the end of the walk.

## 样例 #1

### 输入

```
3 2
5 0 -4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
6 4
1 -2 0 3 -4 5
```

### 输出

```
7
```

## 样例 #3

### 输入

```
3 1000000000
0 0 0
```

### 输出

```
1000000001
```

## 样例 #4

### 输入

```
5 9
-7 -3 8 12 0
```

### 输出

```
-1
```

## 样例 #5

### 输入

```
5 3
-1 0 3 3 0
```

### 输出

```
7
```

## 样例 #6

### 输入

```
5 4
0 2 0 3 0
```

### 输出

```
9
```



---

---
title: "MEX vs DIFF"
layout: "post"
diff: 提高+/省选-
pid: CF1684E
tag: ['贪心', '构造']
---

# MEX vs DIFF

## 题目描述

给你一个大小为n的数组a，保证数组内元素非负，你可以执行以下操作k次：

在一次操作中将数组内任意一个数字改为任何一个非负整数。

现在定义这个数组的成本为DIFF(a)−MEX(a)，其中 DIFF(a) 为a数组内元素去重后的数量，  MEX(a) 为数组中未出现的元素中最小的元素，
举个例子，MEX( { 1 , 2 , 3 } )=0 , MEX( { 0 , 1 , 2 , 4 , 5 } ) = 3。

现在给你数组a，求能实现的最小成本。

## 输入格式

输入包含多个测试用例，第一行输入t表示数据组数，测试用例描述如下：

每个用例的第一行包含两个整数n和k，n表示数组长度，k表示最多的操作次数，第二行有n个整数，为数组n的元素。

## 输出格式

对于每个测试用例输出一行一个整数，表示该用例能实现的最小整数。

## 说明/提示

在第一个测试用例中，不需要任何操作来最小化 DIFF-MEX 的值。

在第二个测试用例中，可以将 5 替换为 1 。 数组 a 变为[ 0 , 2 , 4 , 1 ] , DIFF = 4，MEX=MEX( { 0 , 1 , 2 , 4 } )=3 ，所以答案是 1.

在第三个测试用例中，一个可能的数组 a 的变形是[ 4 , 13 , 0 , 0 , 13 , 1 , 2 ]，其中 DIFF = 5，MEX = 3。

在第四个测试用例中，一个可能的数组 a 的变形是 [ 1 , 2 , 3 , 0 , 0 , 0 ] 。

## 样例 #1

### 输入

```
4
4 1
3 0 1 2
4 1
0 2 4 5
7 2
4 13 0 0 13 1337 1000000000
6 2
1 2 8 0 0 0
```

### 输出

```
0
1
2
0
```



---

---
title: "Linguistics"
layout: "post"
diff: 提高+/省选-
pid: CF1685B
tag: ['贪心']
---

# Linguistics

## 题目描述

Alina 发现了一种只由 $\text{A, B, AB, BA}$ 四种单词组成的语言，这种语言不含有空格，书写句子时只需要将单词直接连接起来即可。

她很好奇是否可以用 $a$ 个 $\text{A}$，$b$ 个 $\text{B}$，$c$ 个 $\text{AB}$，$d$ 个 $\text{BA}$ 拼接形成句子 $s$。

换句话说，是否可以用 $a+b+c+d$ 个单词以某种顺序拼接出句子 $s$，这 $a+b+c+d$ 个单词都得被用到，他们的顺序可以由你决定。

## 输入格式

第一行是一个数字 $t$，表示数据的组数。每一组的格式如下：

每组的第一行是四个数字 $a, b, c, d$（$0\leq a,b,c,d\leq2\cdot10^5$），它们分别代表本组单词 $\text{A, B, AB, BA}$ 需要使用的次数。
每组的第二行是一个字符串 $s$（$|s|\leq 2\cdot 10^5$），并且保证 $s$ 的总长和 $a$ 个 $\text{A}$，$b$ 个 $\text{B}$，$c$ 个 $\text{AB}$，$d$ 个 $\text{BA}$ 拼接形成的长度相同（$|s|=a+b+2c+2d$）。其中 $|s|$ 表示字符串 $s$ 的长度。

所有 $s$ 的总长度之和不会超过 $2\cdot 10^5$。

## 输出格式

对于每组数据，如果该组数据的 $s$ 可以被 $a$ 个 $\text{A}$，$b$ 个 $\text{B}$，$c$ 个 $\text{AB}$，$d$ 个 $\text{BA}$ 不限顺序地拼接形成，那么输出一个字符串 `YES`，否则输出 `NO`。

## 样例 #1

### 输入

```
8
1 0 0 0
B
0 0 1 0
AB
1 1 0 1
ABAB
1 0 1 1
ABAAB
1 1 2 2
BAABBABBAA
1 1 2 3
ABABABBAABAB
2 3 5 4
AABAABBABAAABABBABBBABB
1 3 3 10
BBABABABABBBABABABABABABAABABA
```

### 输出

```
NO
YES
YES
YES
YES
YES
NO
YES
```



---

---
title: "Permutation Graph"
layout: "post"
diff: 提高+/省选-
pid: CF1696D
tag: ['贪心', '线段树', '分治']
---

# Permutation Graph

## 题目描述

给出一个 $1$ 到 $n$ 的排列 $ [a_1,a_2,\dots,a_n] $ 。对于 $1\le i < j\le n$ ，记 $ \operatorname{mn}(i,j) $ 为 $\min\limits_{k=i}^j a_k$ ，记  $ \operatorname{mx}(i,j) $ 为 $ \max\limits_{k=i}^j a_k $ 。

有一张 $n$ 个点的无向图，点的编号为 $1$ 到 $n$ 。对于每一对整数 $ 1\le i<j\le n $ ，如果同时满足 $ \operatorname{mn}(i,j)=a_i $ 且 $ \operatorname{mx}(i,j)=a_j $ ，或同时满足 $ \operatorname{mn}(i,j)=a_j $ 和 $ \operatorname{mx}(i,j)=a_i $ ，那么就在 $i$ 和 $j$ 之间连一条长度为 $1$ 的边。

询问这张图中从 $1$ 到 $n$ 的最短路的长度。可以证明 $1$ 和 $n$ 总是连通，所以最短路总是存在。

## 输入格式

每个数据点包含多组数据。第一行一个整数 $t$ ( $ 1 \le t \le 5\cdot 10^4 $ ) 表示测试组数

对于每组数据，第一行一个整数 $n$ ( $ 1\le n\le 2.5\cdot 10^5 $ ) 。

第二行包含 $n$ 个整数 $ a_1 $ , $ a_2 $ , $ \ldots $ , $ a_n $ ( $ 1\le a_i\le n $ ) 。保证 $a$ 是 $ 1 $ , $ 2 $ , $ \dots $ , $ n $ 的一个排列。

保证所有数据的 $n$ 之和不超过 $ 5\cdot 10^5 $

## 输出格式

对于每组数据，输出一个整数表示从 $1$ 到 $n$ 的最短路长度

## 样例 #1

### 输入

```
5
1
1
2
1 2
5
1 4 2 3 5
5
2 1 5 3 4
10
7 4 8 1 6 10 3 5 2 9
```

### 输出

```
0
1
1
4
6
```



---

---
title: "Almost Triple Deletions"
layout: "post"
diff: 提高+/省选-
pid: CF1699D
tag: ['贪心', '区间 DP']
---

# Almost Triple Deletions

## 题目描述

You are given an integer $ n $ and an array $ a_1,a_2,\ldots,a_n $ .

In one operation, you can choose an index $ i $ ( $ 1 \le i \lt n $ ) for which $ a_i \neq a_{i+1} $ and delete both $ a_i $ and $ a_{i+1} $ from the array. After deleting $ a_i $ and $ a_{i+1} $ , the remaining parts of the array are concatenated.

For example, if $ a=[1,4,3,3,6,2] $ , then after performing an operation with $ i=2 $ , the resulting array will be $ [1,3,6,2] $ .

What is the maximum possible length of an array of equal elements obtainable from $ a $ by performing several (perhaps none) of the aforementioned operations?

## 输入格式

Each test contains multiple test cases. The first line of input contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The following lines contain the descriptions of the test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le n $ ) — the elements of array $ a $ .

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 10\,000 $ .

## 输出格式

For each testcase, print a single integer, the maximum possible length of an array of equal elements obtainable from $ a $ by performing a sequence of operations.

## 说明/提示

For the first testcase, an optimal sequence of operations would be: $ [1,2,3,2,1,3,3] \rightarrow [3,2,1,3,3] \rightarrow [3,3,3] $ .

For the second testcase, all elements in the array are already equal.

For the third testcase, the only possible sequence of operations is: $ [1,1,1,2,2,2] \rightarrow [1,1,2,2] \rightarrow [1,2] \rightarrow [] $ . Note that, according to the statement, the elements deleted at each step must be different.

For the fourth testcase, the optimal sequence of operations is: $ [1,1,2,2,3,3,1,1] \rightarrow [1,1,2,3,1,1] \rightarrow [1,1,1,1] $ .

For the fifth testcase, one possible reachable array of two equal elements is $ [4,4] $ .

## 样例 #1

### 输入

```
5
7
1 2 3 2 1 3 3
1
1
6
1 1 1 2 2 2
8
1 1 2 2 3 3 1 1
12
1 5 2 3 3 3 4 4 4 4 3 3
```

### 输出

```
3
1
0
4
2
```



---

---
title: "Burenka and Traditions (easy version)"
layout: "post"
diff: 提高+/省选-
pid: CF1718A1
tag: ['动态规划 DP', '贪心']
---

# Burenka and Traditions (easy version)

## 题目描述

This is the easy version of this problem. The difference between easy and hard versions is only the constraints on $ a_i $ and on $ n $ . You can make hacks only if both versions of the problem are solved.

Burenka is the crown princess of Buryatia, and soon she will become the $ n $ -th queen of the country. There is an ancient tradition in Buryatia — before the coronation, the ruler must show their strength to the inhabitants. To determine the strength of the $ n $ -th ruler, the inhabitants of the country give them an array of $ a $ of exactly $ n $ numbers, after which the ruler must turn all the elements of the array into zeros in the shortest time. The ruler can do the following two-step operation any number of times:

- select two indices $ l $ and $ r $ , so that $ 1 \le l \le r \le n $ and a non-negative integer $ x $ , then
- for all $ l \leq i \leq r $ assign $ a_i := a_i \oplus x $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). It takes $ \left\lceil \frac{r-l+1}{2} \right\rceil $ seconds to do this operation, where $ \lceil y \rceil $ denotes $ y $ rounded up to the nearest integer.

Help Burenka calculate how much time she will need.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the size of the array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 5000 $ ) — elements of the array.

It is guaranteed that the sum of $ n $ in all tests does not exceed $ 5000 $ .

## 输出格式

For each test case, output a single number — the minimum time that Burenka will need.

## 说明/提示

In the first test case, Burenka can choose segment $ l = 1 $ , $ r = 4 $ , and $ x=5 $ . so it will fill the array with zeros in $ 2 $ seconds.

In the second test case, Burenka first selects segment $ l = 1 $ , $ r = 2 $ , and $ x = 1 $ , after which $ a = [0, 2, 2] $ , and then the segment $ l = 2 $ , $ r = 3 $ , and $ x=2 $ , which fills the array with zeros. In total, Burenka will spend $ 2 $ seconds.

## 样例 #1

### 输入

```
7
4
5 5 5 5
3
1 3 2
2
0 0
3
2 5 7
6
1 2 3 3 2 1
10
27 27 34 32 2 31 23 56 52 4
5
1822 1799 57 23 55
```

### 输出

```
2
2
0
2
4
7
4
```



---

---
title: "Burenka and Traditions (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF1718A2
tag: ['动态规划 DP', '贪心']
---

# Burenka and Traditions (hard version)

## 题目描述

This is the hard version of this problem. The difference between easy and hard versions is only the constraints on $ a_i $ and on $ n $ . You can make hacks only if both versions of the problem are solved.

Burenka is the crown princess of Buryatia, and soon she will become the $ n $ -th queen of the country. There is an ancient tradition in Buryatia — before the coronation, the ruler must show their strength to the inhabitants. To determine the strength of the $ n $ -th ruler, the inhabitants of the country give them an array of $ a $ of exactly $ n $ numbers, after which the ruler must turn all the elements of the array into zeros in the shortest time. The ruler can do the following two-step operation any number of times:

- select two indices $ l $ and $ r $ , so that $ 1 \le l \le r \le n $ and a non-negative integer $ x $ , then
- for all $ l \leq i \leq r $ assign $ a_i := a_i \oplus x $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). It takes $ \left\lceil \frac{r-l+1}{2} \right\rceil $ seconds to do this operation, where $ \lceil y \rceil $ denotes $ y $ rounded up to the nearest integer.

Help Burenka calculate how much time she will need.

## 输入格式

The first line contains a single integer $ t $ $ (1 \le t \le 500) $ — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (1 \le n \le 10^5) $ - the size of the array

The second line of each test case contains $ n $ integers $ a_1, a_2, \cdots , a_n $ $ (0 \le a_i < 2^{30}) $ — elements of the array.

It is guaranteed that the sum of $ n $ in all tests does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single number — the minimum time that Burenka will need.

## 说明/提示

In the first test case, Burenka can choose segment $ l = 1 $ , $ r = 4 $ , and $ x=5 $ . so it will fill the array with zeros in $ 2 $ seconds.

In the second test case, Burenka first selects segment $ l = 1 $ , $ r = 2 $ , and $ x = 1 $ , after which $ a = [0, 2, 2] $ , and then the segment $ l = 2 $ , $ r = 3 $ , and $ x=2 $ , which fills the array with zeros. In total, Burenka will spend $ 2 $ seconds.

## 样例 #1

### 输入

```
7
4
5 5 5 5
3
1 3 2
2
0 0
3
2 5 7
6
1 2 3 3 2 1
10
27 27 34 32 2 31 23 56 52 4
5
1822 1799 57 23 55
```

### 输出

```
2
2
0
2
4
7
4
```



---

---
title: "Graph Cost"
layout: "post"
diff: 提高+/省选-
pid: CF1731E
tag: ['贪心', '容斥原理']
---

# Graph Cost

## 题目描述

You are given an initially empty undirected graph with $ n $ nodes, numbered from $ 1 $ to $ n $ (i. e. $ n $ nodes and $ 0 $ edges). You want to add $ m $ edges to the graph, so the graph won't contain any self-loop or multiple edges.

If an edge connecting two nodes $ u $ and $ v $ is added, its weight must be equal to the greatest common divisor of $ u $ and $ v $ , i. e. $ \gcd(u, v) $ .

In order to add edges to the graph, you can repeat the following process any number of times (possibly zero):

- choose an integer $ k \ge 1 $ ;
- add exactly $ k $ edges to the graph, each having a weight equal to $ k + 1 $ . Adding these $ k $ edges costs $ k + 1 $ in total.

 Note that you can't create self-loops or multiple edges. Also, if you can't add $ k $ edges of weight $ k + 1 $ , you can't choose such $ k $ .For example, if you can add $ 5 $ more edges to the graph of weight $ 6 $ , you may add them, and it will cost $ 6 $ for the whole pack of $ 5 $ edges. But if you can only add $ 4 $ edges of weight $ 6 $ to the graph, you can't perform this operation for $ k = 5 $ .

Given two integers $ n $ and $ m $ , find the minimum total cost to form a graph of $ n $ vertices and exactly $ m $ edges using the operation above. If such a graph can't be constructed, output $ -1 $ .

Note that the final graph may consist of several connected components.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 10^4 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \leq n \leq 10^6 $ ; $ 1 \leq m \leq \frac{n(n-1)}{2} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print the minimum cost to build the graph, or $ -1 $ if you can't build such a graph.

## 说明/提示

In the first test case, we can add an edge between the vertices $ 2 $ and $ 4 $ with $ \gcd = 2 $ . This is the only possible way to add $ 1 $ edge that will cost $ 2 $ .

In the second test case, there is no way to add $ 10 $ edges, so the answer is $ -1 $ .

In the third test case, we can add the following edges:

- $ k = 1 $ : edge of weight $ 2 $ between vertices $ 2 $ and $ 4 $ ( $ \gcd(2, 4) = 2 $ ). Cost: $ 2 $ ;
- $ k = 1 $ : edge of weight $ 2 $ between vertices $ 4 $ and $ 6 $ ( $ \gcd(4, 6) = 2 $ ). Cost: $ 2 $ ;
- $ k = 2 $ : edges of weight $ 3 $ : $ (3, 6) $ and $ (3, 9) $ ( $ \gcd(3, 6) = \gcd(3, 9) = 3 $ ). Cost: $ 3 $ .

 As a result, we added $ 1 + 1 + 2 = 4 $ edges with total cost $ 2 + 2 + 3 = 7 $ , which is the minimal possible cost.

## 样例 #1

### 输入

```
4
4 1
6 10
9 4
10 11
```

### 输出

```
2
-1
7
21
```



---

---
title: "Paths on the Tree"
layout: "post"
diff: 提高+/省选-
pid: CF1746D
tag: ['动态规划 DP', '贪心', '树形数据结构']
---

# Paths on the Tree

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ , and the root is the vertex $ 1 $ . You are also given a score array $ s_1, s_2, \ldots, s_n $ .

A multiset of $ k $ simple paths is called valid if the following two conditions are both true.

- Each path starts from $ 1 $ .
- Let $ c_i $ be the number of paths covering vertex $ i $ . For each pair of vertices $ (u,v) $ ( $ 2\le u,v\le n $ ) that have the same parent, $ |c_u-c_v|\le 1 $ holds.

 The value of the path multiset is defined as $ \sum\limits_{i=1}^n c_i s_i $ .It can be shown that it is always possible to find at least one valid multiset. Find the maximum value among all valid multisets.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two space-separated integers $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) and $ k $ ( $ 1 \le k \le 10^9 $ ) — the size of the tree and the required number of paths.

The second line contains $ n - 1 $ space-separated integers $ p_2,p_3,\ldots,p_n $ ( $ 1\le p_i\le n $ ), where $ p_i $ is the parent of the $ i $ -th vertex. It is guaranteed that this value describe a valid tree with root $ 1 $ .

The third line contains $ n $ space-separated integers $ s_1,s_2,\ldots,s_n $ ( $ 0 \le s_i \le 10^4 $ ) — the scores of the vertices.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10 ^ 5 $ .

## 输出格式

For each test case, print a single integer — the maximum value of a path multiset.

## 说明/提示

In the first test case, one of optimal solutions is four paths $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 4 $ , $ 1 \to 4 $ , here $ c=[4,2,2,2,2] $ . The value equals to $ 4\cdot 6+ 2\cdot 2+2\cdot 1+2\cdot 5+2\cdot 7=54 $ .

In the second test case, one of optimal solution is three paths $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 4 $ , here $ c=[3,2,2,1,2] $ . The value equals to $ 3\cdot 6+ 2\cdot 6+2\cdot 1+1\cdot 4+2\cdot 10=56 $ .

## 样例 #1

### 输入

```
2
5 4
1 2 1 3
6 2 1 5 7
5 3
1 2 1 3
6 6 1 4 10
```

### 输出

```
54
56
```



---

---
title: "Yet Another Problem"
layout: "post"
diff: 提高+/省选-
pid: CF1747D
tag: ['数学', '贪心', '前缀和']
---

# Yet Another Problem

## 题目描述

You are given an array $ a $ of $ n $ integers $ a_1, a_2, a_3, \ldots, a_n $ .

You have to answer $ q $ independent queries, each consisting of two integers $ l $ and $ r $ .

- Consider the subarray $ a[l:r] $ $ = $ $ [a_l, a_{l+1}, \ldots, a_r] $ . You can apply the following operation to the subarray any number of times (possibly zero)- 
  1. Choose two integers $ L $ , $ R $ such that $ l \le L \le R \le r $ and $ R - L + 1 $ is odd.
  2. Replace each element in the subarray from $ L $ to $ R $ with the XOR of the elements in the subarray $ [L, R] $ .
- The answer to the query is the minimum number of operations required to make all elements of the subarray $ a[l:r] $ equal to $ 0 $ or $ -1 $ if it is impossible to make all of them equal to $ 0 $ .

You can find more details about XOR operation [here](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 输入格式

The first line contains two integers $ n $ and $ q $ $ (1 \le n, q \le 2 \cdot 10^5) $ — the length of the array $ a $ and the number of queries.

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ $ (0 \le a_i \lt 2^{30}) $ — the elements of the array $ a $ .

The $ i $ -th of the next $ q $ lines contains two integers $ l_i $ and $ r_i $ $ (1 \le l_i \le r_i \le n) $ — the description of the $ i $ -th query.

## 输出格式

For each query, output a single integer — the answer to that query.

## 说明/提示

In the first query, $ l = 3, r = 4 $ , subarray = $ [3, 3] $ . We can apply operation only to the subarrays of length $ 1 $ , which won't change the array; hence it is impossible to make all elements equal to $ 0 $ .

In the second query, $ l = 4, r = 6 $ , subarray = $ [3, 1, 2] $ . We can choose the whole subarray $ (L = 4, R = 6) $ and replace all elements by their XOR $ (3 \oplus 1 \oplus 2) = 0 $ , making the subarray $ [0, 0, 0] $ .

In the fifth query, $ l = 1, r = 6 $ , subarray = $ [3, 0, 3, 3, 1, 2] $ . We can make the operations as follows:

1. Choose $ L = 4, R = 6 $ , making the subarray $ [3, 0, 3, 0, 0, 0] $ .
2. Choose $ L = 1, R = 5 $ , making the subarray $ [0, 0, 0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
7 6
3 0 3 3 1 2 3
3 4
4 6
3 7
5 6
1 6
2 2
```

### 输出

```
-1
1
1
-1
2
0
```



---

---
title: "ConstructOR"
layout: "post"
diff: 提高+/省选-
pid: CF1748D
tag: ['贪心', '中国剩余定理 CRT', '位运算', '构造']
---

# ConstructOR

## 题目描述

You are given three integers $ a $ , $ b $ , and $ d $ . Your task is to find any integer $ x $ which satisfies all of the following conditions, or determine that no such integers exist:

- $ 0 \le x \lt 2^{60} $ ;
- $ a|x $ is divisible by $ d $ ;
- $ b|x $ is divisible by $ d $ .

Here, $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 输入格式

Each test contains multiple test cases. The first line of input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of one line, containing three integers $ a $ , $ b $ , and $ d $ ( $ 1 \le a,b,d \lt 2^{30} $ ).

## 输出格式

For each test case print one integer. If there exists an integer $ x $ which satisfies all of the conditions from the statement, print $ x $ . Otherwise, print $ -1 $ .

If there are multiple solutions, you may print any of them.

## 说明/提示

In the first test case, $ x=18 $ is one of the possible solutions, since $ 39|18=55 $ and $ 12|18=30 $ , both of which are multiples of $ d=5 $ .

In the second test case, $ x=14 $ is one of the possible solutions, since $ 8|14=6|14=14 $ , which is a multiple of $ d=14 $ .

In the third and fourth test cases, we can show that there are no solutions.

## 样例 #1

### 输入

```
8
12 39 5
6 8 14
100 200 200
3 4 6
2 2 2
18 27 3
420 666 69
987654321 123456789 999999999
```

### 输出

```
18
14
-1
-1
0
11
25599
184470016815529983
```



---

---
title: "Doremy's Number Line"
layout: "post"
diff: 提高+/省选-
pid: CF1764E
tag: ['模拟', '贪心']
---

# Doremy's Number Line

## 题目描述

Doremy has two arrays $ a $ and $ b $ of $ n $ integers each, and an integer $ k $ .

Initially, she has a number line where no integers are colored. She chooses a permutation $ p $ of $ [1,2,\ldots,n] $ then performs $ n $ moves. On the $ i $ -th move she does the following:

- Pick an uncolored integer $ x $ on the number line such that either: 
  - $ x \leq a_{p_i} $ ; or
  - there exists a colored integer $ y $ such that $ y \leq a_{p_i} $ and $ x \leq y+b_{p_i} $ .
- Color integer $ x $ with color $ p_i $ .

Determine if the integer $ k $ can be colored with color $ 1 $ .

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 10^5 $ , $ 1 \le k \le 10^9 $ ).

Each of the following $ n $ lines contains two integers $ a_i $ and $ b_i $ ( $ 1 \le a_i,b_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output "YES" (without quotes) if the point $ k $ can be colored with color $ 1 $ . Otherwise, output "NO" (without quotes).

You can output "YES" and "NO" in any case (for example, strings "yEs", "yes" and "Yes" will be recognized as a positive response).

## 说明/提示

For the first test case, it is impossible to color point $ 16 $ with color $ 1 $ .

For the second test case, $ p=[2,1,3,4] $ is one possible choice, the detail is shown below.

- On the first move, pick $ x=8 $ and color it with color $ 2 $ since $ x=8 $ is uncolored and $ x \le a_2 $ .
- On the second move, pick $ x=16 $ and color it with color $ 1 $ since there exists a colored point $ y=8 $ such that $ y\le a_1 $ and $ x \le y + b_1 $ .
- On the third move, pick $ x=0 $ and color it with color $ 3 $ since $ x=0 $ is uncolored and $ x \le a_3 $ .
- On the forth move, pick $ x=-2 $ and color it with color $ 4 $ since $ x=-2 $ is uncolored and $ x \le a_4 $ .
- In the end, point $ -2,0,8,16 $ are colored with color $ 4,3,2,1 $ , respectively.

For the third test case, $ p=[2,1,4,3] $ is one possible choice.

For the fourth test case, $ p=[2,3,4,1] $ is one possible choice.

## 样例 #1

### 输入

```
6
4 16
5 3
8 12
10 7
15 1
4 16
8 12
10 7
15 1
5 3
4 16
10 7
15 1
5 3
8 12
4 16
15 1
5 3
8 12
10 7
1 1000000000
500000000 500000000
2 1000000000
1 999999999
1 1
```

### 输出

```
NO
YES
YES
YES
NO
YES
```



---

---
title: "Rectangle Shrinking"
layout: "post"
diff: 提高+/省选-
pid: CF1781E
tag: ['贪心', '构造']
---

# Rectangle Shrinking

## 题目描述

你有一个长为 $10^9$，宽为 $2$ 的矩形网格。

起初，网格上有 $n$ 个矩形，这些矩形的边沿着单元格的边。对于第 $i$ 个矩形，左上角为 $(u_i,l_i)$，右下角为 $(d_i,r_i)$。这些矩形两两之间可能相交、重合或包含。

对于每个矩形，你可以进行以下操作一种或者不操作：

- 删除这个矩形。

- 用一个非空的子矩形来替换它。

要求：在完成所有操作后，剩下的所有矩形中不允许任意两个矩形有交。

求剩余矩形覆盖的总面积最大为多少，以及达到最大的任意一种方案。

$1 \le u_i \le d_i \le 2$，$1 \le l_i \le r_i \le 10^9$，$\sum n \le 2 \times 10^5$。

## 输入格式

多测。

第一行一个正整数 $t$ ($1 \le t \le 10^4$) 表示测试用例的数量。

对于每个测试用例，
第一行一个正整数 $n$ ($1 \le n \le 2 \times 10^5$) 表示初始矩形的个数。

接下来一共 $n$ 行，第 $i$ 行包含四个整数 $u_i,l_i,d_i,r_i$ ($1 \le u_i \le d_i \le 2$，$1 \le l_i \le r_i \le 10^9$) 表示矩形左上角和右下角的坐标。

## 输出格式

对于每个测试用例，第一行一个整数 $s$ 表示剩余矩形覆盖的最大总面积。

在之后 $n$ 行中，第 $i$ 行输出四个整数表示方案：

如果第 $i$ 个矩形被删除，输出 `0 0 0 0`。

否则，输出第 $i$ 个矩形被替换后的左上角和右下角的新坐标，满足 $u_i \le u'_i \le d'_i \le d_i$，$l_i \le l'_i \le r'_i \le r_i$ 。

如果有多个解，输出任意一种。

### 样例解释
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1781E/2361ff07797a1f95e7735ebc4fd257e63a865b14.png)

上图为第一个测试用例的图片。上方为初始矩形，下方为剩余矩形。

翻译来自 [jianhe](https://www.luogu.com.cn/user/613794)。

## 样例 #1

### 输入

```
8
5
1 2 2 4
2 4 2 8
1 4 2 7
1 2 1 2
1 9 1 10
2
1 1 1 10
1 5 1 15
2
1 1 1 10
1 1 1 10
5
1 3 1 7
1 3 1 8
1 1 1 4
1 2 1 7
1 10 1 11
2
1 1 2 10
1 5 1 8
2
1 5 2 10
1 2 1 7
2
1 5 2 10
2 2 2 15
5
2 6 2 7
1 4 2 5
1 5 1 9
1 7 2 10
1 2 1 6
```

### 输出

```
15
1 2 2 4
2 5 2 8
1 5 1 7
0 0 0 0
1 9 1 10
15
1 1 1 10
1 11 1 15
10
1 1 1 10
0 0 0 0
10
0 0 0 0
1 8 1 8
1 1 1 4
1 5 1 7
1 10 1 11
20
1 1 2 10
0 0 0 0
15
1 5 2 10
1 2 1 4
20
1 5 1 10
2 2 2 15
16
2 6 2 6
2 4 2 5
0 0 0 0
1 7 2 10
1 2 1 6
```



---

---
title: "Game of the Year"
layout: "post"
diff: 提高+/省选-
pid: CF1783E
tag: ['数学', '贪心', '树状数组', '数论', '前缀和', 'ST 表']
---

# Game of the Year

## 题目描述

Monocarp 和 Polycarp 正在玩电脑游戏。游戏特点：$ n $ 个编号从 $ 1 $ 到 $ n $ 的BOSS。

他俩将用以下方式与BOSS战斗

- Monocarp 进行 $ k $ 次尝试撒掉boss;
- Polycarp 进行 $ k $ 次尝试撒掉boss;
- Monocarp 进行 $ k $ 次尝试撒掉boss;
- Polycarp 进行 $ k $ 次尝试撒掉boss;
- ...

Monocarp 在第 $ a_i $ 次尝试中撒掉了第 $ i $ 只BOSS。Polycarp 在第 $ b_i $ 次尝试中撒掉了第 $ i $ 只BOSS。其中一个人撒掉第 $ i $ 只BOSS后，他们就会尝试撒第 $ (i+1) $ 只BOSS。并且他们的尝试计数器都会清空。撒掉第 $ n $ 只BOSS后，游戏结束。

找到从$ 1 $ 到 $ n $所有的 $ k $ 值， 使得 Monocarp 可以杀死所有的BOSS。

## 输入格式

第一行输入一个整数 $ t $ ( $ 1 \le t \le 10^4 $ ) — 样例数。

每个样例第一行输入一个整数 $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — BOSS的数量。

每个样例第二行输入 $ n $ 个整数： $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ) — Monocarp 撒死每只BOSS的尝试次数。

每个样例第三行输入 $ n $ 个整数： $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le n $ ) — Polycarp 撒死每只BOSS的尝试次数。

所有测试样例的 $ n $ 之和不超过 $ 2 \cdot 10^5 $ .

## 输出格式

对于每个样例输出两行。第一行应该包含一个正整数 $ \mathit{cnt} $ — 从 $ 1 $ 到 $ n $ 使得 Monocarp 可以撒死所有BOSS的 $ k $ 的总数。第二行应该包含 $ \mathit{cnt} $ 个正整数 — 所有 $ k $ 的值。

## 说明/提示

考虑最后一组测试样例

使 $ k = 1 $。首先，Monocarp经过1次尝试撒死第一只BOSS。成功，因为 $ a_1 = 1 $。 然后，Monocarp进行一次尝试撒死第二只BOSS。不成功，因为 $ a_2 > 1 $。于是，Polycarp尝试了一下。也不成功，因为 $ b_2 > 1 $。然后Monocarp进行了另一次尝试。仍然不成功，因为 $ a_2 > 2 $。直到Polycarp 在第三次尝试撒掉了BOSS。Monocarp没能撒掉BOSS。因此，$ k = 1 $ 不是答案。

使 $ k = 2 $ . Monocarp仍然在他的第一次尝试中撒死了BOSS。然后，他进行了两次不成功的尝试未能撒死BOSS。然后，Polycarp进行了两次不成功的尝试。然后，Monocarp进行了两次尝试，并且在第四次尝试中撒掉了BOSS。撒掉第三只BOSS的方法也类似。首先，Monocarp进行两次不成功的尝试。然后，Polycarp进行两次不成功的尝试。然后，Monocarp还有两次尝试机会，但在这两次机会中第一次就撒死了BOSS，因为 $ a_3 = 3 $。 第四只BOSS也被Monocarp撒死。因此，$ k = 2 $ 是答案。

## 样例 #1

### 输入

```
3
3
1 1 1
2 3 1
1
1
1
4
1 4 3 2
3 3 4 1
```

### 输出

```
3
1 2 3 
1
1 
2
2 4
```



---

---
title: "Monsters (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF1784C
tag: ['贪心', '线段树']
---

# Monsters (hard version)

## 题目描述

This is the hard version of the problem. In this version, you need to find the answer for every prefix of the monster array.

In a computer game, you are fighting against $ n $ monsters. Monster number $ i $ has $ a_i $ health points, all $ a_i $ are integers. A monster is alive while it has at least $ 1 $ health point.

You can cast spells of two types:

1. Deal $ 1 $ damage to any single alive monster of your choice.
2. Deal $ 1 $ damage to all alive monsters. If at least one monster dies (ends up with $ 0 $ health points) as a result of this action, then repeat it (and keep repeating while at least one monster dies every time).

Dealing $ 1 $ damage to a monster reduces its health by $ 1 $ .

Spells of type 1 can be cast any number of times, while a spell of type 2 can be cast at most once during the game.

For every $ k = 1, 2, \ldots, n $ , answer the following question. Suppose that only the first $ k $ monsters, with numbers $ 1, 2, \ldots, k $ , are present in the game. What is the smallest number of times you need to cast spells of type 1 to kill all $ k $ monsters?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

Each test case consists of two lines. The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of monsters.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — monsters' health points.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print $ n $ integers. The $ k $ -th of these integers must be equal to the smallest number of times you need to cast spells of type 1 to kill all $ k $ monsters, if only monsters with numbers $ 1, 2, \ldots, k $ are present in the game.

## 说明/提示

In the first test case, for $ k = n $ , the initial health points of the monsters are $ [3, 1, 2] $ . It is enough to cast a spell of type 2:

- Monsters' health points change to $ [2, 0, 1] $ . Since monster number $ 2 $ dies, the spell is repeated.
- Monsters' health points change to $ [1, 0, 0] $ . Since monster number $ 3 $ dies, the spell is repeated.
- Monsters' health points change to $ [0, 0, 0] $ . Since monster number $ 1 $ dies, the spell is repeated.
- Monsters' health points change to $ [0, 0, 0] $ .

Since it is possible to use no spells of type 1 at all, the answer is $ 0 $ .

In the second test case, for $ k = n $ , the initial health points of the monsters are $ [4, 1, 5, 4, 1, 1] $ . Here is one of the optimal action sequences:

- Using a spell of type 1, deal $ 1 $ damage to monster number $ 1 $ . Monsters' health points change to $ [3, 1, 5, 4, 1, 1] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 4 $ . Monsters' health points change to $ [3, 1, 5, 3, 1, 1] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 4 $ again. Monsters' health points change to $ [3, 1, 5, 2, 1, 1] $ .
- Use a spell of type 2:
  - Monsters' health points change to $ [2, 0, 4, 1, 0, 0] $ . Since monsters number $ 2 $ , $ 5 $ , and $ 6 $ die, the spell is repeated.
  - Monsters' health points change to $ [1, 0, 3, 0, 0, 0] $ . Since monster number $ 4 $ dies, the spell is repeated.
  - Monsters' health points change to $ [0, 0, 2, 0, 0, 0] $ . Since monster number $ 1 $ dies, the spell is repeated.
  - Monsters' health points change to $ [0, 0, 1, 0, 0, 0] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 3 $ . Monsters' health points change to $ [0, 0, 0, 0, 0, 0] $ .

Spells of type 1 are cast $ 4 $ times in total. It can be shown that this is the smallest possible number.

## 样例 #1

### 输入

```
2
3
3 1 2
6
4 1 5 4 1 1
```

### 输出

```
2 1 0
3 2 4 4 4 4
```



---

---
title: "City Union"
layout: "post"
diff: 提高+/省选-
pid: CF1799E
tag: ['贪心', '并查集', '构造']
---

# City Union

## 题目描述

You are given $ n \times m $ grid. Some cells are filled and some are empty.

A city is a maximal (by inclusion) set of filled cells such that it is possible to get from any cell in the set to any other cell in the set by moving to adjacent (by side) cells, without moving into any cells not in the set. In other words, a city is a connected component of filled cells with edges between adjacent (by side) cells.

Initially, there are two cities on the grid. You want to change some empty cells into filled cells so that both of the following are satisfied:

- There is one city on the resulting grid.
- The shortest path between any two filled cells, achievable only by moving onto filled cells, is equal to the Manhattan distance between them.

The Manhattan distance between two cells $ (a, b) $ and $ (c, d) $ is equal to $ |a - c| + |b - d| $ .

Find a way to add filled cells that satisfies these conditions and minimizes the total number of filled cells.

## 输入格式

Input consists of multiple test cases. The first line contains a single integer $ t $ , the number of test cases ( $ 1 \le t \le 5000 $ ).

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 50 $ , $ nm \geq 3 $ ).

The next $ n $ lines describe the grid. The $ i $ -th line contains a string $ s_i $ of length $ m $ . $ s_{i,j} $ is '\#' if the cell in position $ (i, j) $ is filled, and '.' if it is empty.

It is guaranteed that there are exactly two cities in the initial grid.

It is guaranteed that the sum of $ n\cdot m $ over all test cases does not exceed $ 25\,000 $ .

## 输出格式

For each test case, output $ n $ lines, each containing a string of length $ m $ , describing the grid you create in the same format as the input.

If there are multiple possible answers with the minimum number of filled cells print any.

## 说明/提示

In the first test case, we can add a single filled cell between the two cities to connect them. We can verify that the second condition is satisfied.

In the second test case, we can also connect the cities with a single filled cell, while satisfying the second condition.

In the third test case, note that if we filled the 3 cells in the top left, the cities would be connected, but the second condition would not be satisfied for cells $ (4, 2) $ and $ (2, 4) $ .

## 样例 #1

### 输入

```
11
1 3
#.#
2 2
.#
#.
4 4
..##
...#
#...
##..
6 6
.##...
##....
......
....##
.....#
...###
6 5
.#..#
.#..#
.#..#
.#.##
.#...
##...
5 5
#####
#...#
#.#.#
#...#
#####
4 4
.##.
##.#
#.##
.##.
5 5
..###
....#
.....
#....
#....
5 6
.##...
##....
#....#
....##
...##.
6 5
..##.
...##
....#
#....
##...
.##..
5 4
..##
..#.
..#.
#...
#...
```

### 输出

```
###

.#
##

..##
..##
###.
##..

.##...
###...
..#...
..####
...###
...###

.####
.####
.####
.####
.#...
##...

#####
#####
#####
#####
#####

.##.
####
####
.##.

..###
..###
..#..
###..
#....

.##...
###...
######
...###
...##.

..##.
..###
..###
###..
###..
.##..

..##
..#.
..#.
###.
#...
```



---

---
title: "Imbalanced Arrays"
layout: "post"
diff: 提高+/省选-
pid: CF1852B
tag: ['贪心', '拓扑排序', '构造']
---

# Imbalanced Arrays

## 题目描述

Ntarsis has come up with an array $ a $ of $ n $ non-negative integers.

Call an array $ b $ of $ n $ integers imbalanced if it satisfies the following:

- $ -n\le b_i\le n $ , $ b_i \ne 0 $ ,
- there are no two indices $ (i, j) $ ( $ 1 \le i, j \le n $ ) such that $ b_i + b_j = 0 $ ,
- for each $ 1 \leq i \leq n $ , there are exactly $ a_i $ indices $ j $ ( $ 1 \le j \le n $ ) such that $ b_i+b_j>0 $ , where $ i $ and $ j $ are not necessarily distinct.

Given the array $ a $ , Ntarsis wants you to construct some imbalanced array. Help him solve this task, or determine it is impossible.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case has a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ).

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq n $ ).

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output "NO" if there exists no imbalanced array.

Otherwise, output "YES". Then, on the next line, output $ n $ integers $ b_1, b_2, \ldots, b_n $ where $ b_i \neq 0 $ for all $ 1 \leq i \leq n $ — an imbalanced array.

## 说明/提示

For the first test case, $ b = [1] $ is an imbalanced array. This is because for $ i = 1 $ , there is exactly one $ j $ ( $ j = 1 $ ) where $ b_1 + b_j > 0 $ .

For the second test case, it can be shown that there exists no imbalanced array.

For the third test case, $ a = [0, 1, 0] $ . The array $ b = [-3, 1, -2] $ is an imbalanced array.

- For $ i = 1 $ and $ i = 3 $ , there exists no index $ j $ such that $ b_i + b_j > 0 $ .
- For $ i = 2 $ , there is only one index $ j = 2 $ such that $ b_i + b_j > 0 $ ( $ b_2 + b_2 = 1 + 1 = 2 $ ).

 Another possible output for the third test case could be $ b = [-2, 1, -3] $ .

## 样例 #1

### 输入

```
5
1
1
4
1 4 3 4
3
0 1 0
4
4 3 2 1
3
1 3 1
```

### 输出

```
YES
1 
NO
YES
-3 1 -2 
YES
4 2 -1 -3 
YES
-1 3 -1
```



---

---
title: "Set To Max (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1904D2
tag: ['贪心', '单调栈']
---

# Set To Max (Hard Version)

## 题目描述

This is the hard version of the problem. The only differences between the two versions of this problem are the constraints on $ n $ and the time limit. You can make hacks only if all versions of the problem are solved.

You are given two arrays $ a $ and $ b $ of length $ n $ .

You can perform the following operation some (possibly zero) times:

1. choose $ l $ and $ r $ such that $ 1 \leq l \leq r \leq n $ .
2. let $ x=\max(a_l,a_{l+1},\ldots,a_r) $ .
3. for all $ l \leq i \leq r $ , set $ a_i := x $ .

Determine if you can make array $ a $ equal to array $ b $ .

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the arrays.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the elements of array $ a $ .

The third line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le n $ ) — the elements of array $ b $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output "YES" (without quotes) if you can make $ a $ into $ b $ using any number of operations, and "NO" (without quotes) otherwise.

You can output "YES" and "NO" in any case (for example, strings "yES", "yes" and "Yes" will be recognized as a positive response).

## 说明/提示

In the first test case, we can achieve array $ b $ by applying a single operation: $ (l,r)=(2,3) $ .

In the second test case, it can be shown we cannot achieve array $ b $ in any amount of operations.

In the third test case, we can achieve array $ b $ by applying two operations: $ (l,r)=(2,5) $ . followed by $ (l,r)=(1,3) $ .

In the fourth and fifth test cases, it can be shown we cannot achieve array $ b $ in any amount of operations.

## 样例 #1

### 输入

```
5
5
1 2 3 2 4
1 3 3 2 4
5
3 4 2 2 4
3 4 3 4 4
5
3 2 1 1 1
3 3 3 2 2
2
1 1
1 2
3
1 1 2
2 1 2
```

### 输出

```
YES
NO
YES
NO
NO
```



---

---
title: "Modular Sequence"
layout: "post"
diff: 提高+/省选-
pid: CF1928E
tag: ['动态规划 DP', '贪心']
---

# Modular Sequence

## 题目描述

You are given two integers $ x $ and $ y $ . A sequence $ a $ of length $ n $ is called modular if $ a_1=x $ , and for all $ 1 < i \le n $ the value of $ a_{i} $ is either $ a_{i-1} + y $ or $ a_{i-1} \bmod y $ . Here $ x \bmod y $ denotes the remainder from dividing $ x $ by $ y $ .

Determine if there exists a modular sequence of length $ n $ with the sum of its elements equal to $ S $ , and if it exists, find any such sequence.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ). The description of the test cases follows.

The first and only line of each test case contains four integers $ n $ , $ x $ , $ y $ , and $ s $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le x \le 2 \cdot 10^5 $ , $ 1 \le y \le 2 \cdot 10^5 $ , $ 0 \le s \le 2 \cdot 10^5 $ ) — the length of the sequence, the parameters $ x $ and $ y $ , and the required sum of the sequence elements.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ , and also the sum of $ s $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, if the desired sequence exists, output "Yes" on the first line (without quotes). Then, on the second line, output $ n $ integers $ a_1, a_2, \ldots, a_n $ separated by a space — the elements of the sequence $ a $ . If there are multiple suitable sequences, output any of them.

If the sequence does not exist, output "No" on a single line.

You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes", and "YES" will be accepted as a positive answer.

## 说明/提示

In the first example, the sequence $ [8, 11, 2, 5, 2] $ satisfies the conditions. Thus, $ a_1 = 8 = x $ , $ a_2 = 11 = a_1 + 3 $ , $ a_3 = 2 = a_2 \bmod 3 $ , $ a_4 = 5 = a_3 + 3 $ , $ a_5 = 2 = a_4 \bmod 3 $ .

In the second example, the first element of the sequence should be equal to $ 5 $ , so the sequence $ [2, 2, 2] $ is not suitable.

## 样例 #1

### 输入

```
3
5 8 3 28
3 5 3 6
9 1 5 79
```

### 输出

```
YES
8 11 2 2 5 
NO
NO
```



---

---
title: "Chain Reaction"
layout: "post"
diff: 提高+/省选-
pid: CF1954E
tag: ['贪心']
---

# Chain Reaction

## 题目描述

There are $ n $ monsters standing in a row. The $ i $ -th monster has $ a_i $ health points.

Every second, you can choose one alive monster and launch a chain lightning at it. The lightning deals $ k $ damage to it, and also spreads to the left (towards decreasing $ i $ ) and to the right (towards increasing $ i $ ) to alive monsters, dealing $ k $ damage to each. When the lightning reaches a dead monster or the beginning/end of the row, it stops. A monster is considered alive if its health points are strictly greater than $ 0 $ .

For example, consider the following scenario: there are three monsters with health equal to $ [5, 2, 7] $ , and $ k = 3 $ . You can kill them all in $ 4 $ seconds:

- launch a chain lightning at the $ 3 $ -rd monster, then their health values are $ [2, -1, 4] $ ;
- launch a chain lightning at the $ 1 $ -st monster, then their health values are $ [-1, -1, 4] $ ;
- launch a chain lightning at the $ 3 $ -rd monster, then their health values are $ [-1, -1, 1] $ ;
- launch a chain lightning at the $ 3 $ -th monster, then their health values are $ [-1, -1, -2] $ .

For each $ k $ from $ 1 $ to $ \max(a_1, a_2, \dots, a_n) $ , calculate the minimum number of seconds it takes to kill all the monsters.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of monsters.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^5 $ ) — the health points of the $ i $ -th monster.

## 输出格式

For each $ k $ from $ 1 $ to $ \max(a_1, a_2, \dots, a_n) $ , output the minimum number of seconds it takes to kill all the monsters.

## 样例 #1

### 输入

```
3
5 2 7
```

### 输出

```
10 6 4 3 2 2 1
```

## 样例 #2

### 输入

```
4
7 7 7 7
```

### 输出

```
7 4 3 2 2 2 1
```

## 样例 #3

### 输入

```
10
1 9 7 6 2 4 7 8 1 3
```

### 输出

```
17 9 5 4 3 3 3 2 1
```



---

---
title: "Unique Array"
layout: "post"
diff: 提高+/省选-
pid: CF1969E
tag: ['贪心', '线段树']
---

# Unique Array

## 题目描述

You are given an integer array $ a $ of length $ n $ . A subarray of $ a $ is one of its contiguous subsequences (i. e. an array $ [a_l, a_{l+1}, \dots, a_r] $ for some integers $ l $ and $ r $ such that $ 1 \le l < r \le n $ ). Let's call a subarray unique if there is an integer that occurs exactly once in the subarray.

You can perform the following operation any number of times (possibly zero): choose an element of the array and replace it with any integer.

Your task is to calculate the minimum number of aforementioned operation in order for all the subarrays of the array $ a $ to be unique.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

Additional constraint on the input: the sum of $ n $ over all test cases doesn't exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the minimum number of aforementioned operation in order for all the subarrays of the array $ a $ to be unique.

## 说明/提示

In the second test case, you can replace the $ 1 $ -st and the $ 3 $ -rd element, for example, like this: $ [3, 4, 1, 4] $ .

In the third test case, you can replace the $ 4 $ -th element, for example, like this: $ [3, 1, 2, 3, 2] $ .

## 样例 #1

### 输入

```
4
3
2 1 2
4
4 4 4 4
5
3 1 2 1 2
5
1 3 2 1 2
```

### 输出

```
0
2
1
0
```



---

---
title: "Cat, Fox and Swaps"
layout: "post"
diff: 提高+/省选-
pid: CF1973E
tag: ['贪心']
---

# Cat, Fox and Swaps

## 题目描述

Fox has found an array $ p_1, p_2, \ldots, p_n $ , that is a permutation of length $ n^\dagger $ of the numbers $ 1, 2, \ldots, n $ . She wants to sort the elements in increasing order. Cat wants to help her — he is able to swap any two numbers $ x $ and $ y $ in the array, but only if $ l \leq x + y \leq r $ (note that the constraint is imposed on the values of the elements, not their positions). He can make such swaps any number of times.

They don't know the numbers $ l $ , $ r $ yet, they only know that it's true that $ 1 \leq l \leq r \leq 2 \cdot n $ .

You are given the number $ n $ and the array $ p_1, p_2, \ldots, p_n $ . Determine how many pairs $ (l, r) $ satisfying the conditions are there such that you can sort the permutation if you can only swap two number $ (x, y) $ such that $ l \leq x + y \leq r $ (arbitrary number of times, possibly $ 0 $ ).

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

Description of each test case consists of two lines. The first line contains one integer $ n $ ( $ 1 \leq n \leq 10^5 $ ).

The second line contains $ n $ integers: the array $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ). It is guaranteed that this array is a permutation of length $ n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print the number of pairs of integers $ (l, r) $ such that $ 1 \leq l \leq r \leq 2 \cdot n $ , and you can sort the array under the constraints.

## 说明/提示

In the first example, we need to be able to swap $ 1 $ and $ 2 $ , so we must be able to swap numbers with sum $ 3 $ . There are exactly $ 6 $ pairs satisfying the condition: $ (1, 3), (2, 3), (3, 3), (1, 4), (2, 4) $ and $ (3, 4) $ , so the answer is $ 6 $ .

In the second example, the $ 11 $ pairs satisfying the condition are $ (1, 4), (1, 5), (1, 6), (2, 4), (2, 5), (2, 6), (3, 4), (3, 5), (3, 6), (4, 5) $ and $ (4, 6) $ . For example, if we pick the pair $ (3, 4) $ we can first swap the numbers $ 1 $ and $ 2 $ and then the numbers $ 1 $ and $ 3 $ , after this, the permutation is sorted.

## 样例 #1

### 输入

```
7
2
2 1
3
3 1 2
4
3 2 1 4
5
5 3 1 2 4
5
1 2 3 4 5
6
3 2 1 5 4 6
6
1 3 2 4 5 6
```

### 输出

```
6
11
23
29
55
46
58
```



---

---
title: "Wonderful Tree!"
layout: "post"
diff: 提高+/省选-
pid: CF1987E
tag: ['贪心']
---

# Wonderful Tree!

## 题目描述

God's Blessing on This ArrayForces!

A Random Pebble



You are given a tree with $ n $ vertices, rooted at vertex $ 1 $ . The $ i $ -th vertex has an integer $ a_i $ written on it.

Let $ L $ be the set of all direct children $ ^{\text{∗}} $ of $ v $ . A tree is called wonderful, if for all vertices $ v $ where $ L $ is not empty, $ $$$a_v \le \sum_{u \in L}{a_u}. $ $  In one operation, you choose any vertex  $ v $  and increase  $ a\_v $  by  $ 1 $ .</p><p>Find the minimum number of operations needed to make the given tree <span class="tex-font-style-it">wonderful</span>!</p><div><p> $ ^{\\text{∗}} $  Vertex  $ u $  is called a direct child of vertex  $ v $  if: </p><ul> <li>  $ u $  and  $ v $  are connected by an edge, and </li><li>  $ v $  is on the (unique) path from  $ u$$$ to the root of the tree.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 5000 $ ) — the number of vertices in the tree.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the values initially written on the vertices.

The third line of each test case contains $ n - 1 $ integers $ p_2, p_3 , \ldots, p_n $ ( $ 1 \le p_i < i $ ), indicating that there is an edge from vertex $ p_i $ to vertex $ i $ . It is guaranteed that the given edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5000 $ .

## 输出格式

For each test case, output a single integer — the minimum number of operations needed to make the tree wonderful.

## 说明/提示

The tree in the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1987E/2f38988a6330d33a37c9c3428488c52df188849b.png)You can apply the operation once on vertex $ 5 $ and twice on vertex $ 2 $ to get a wonderful tree.

In the second test case, you can apply the operation twice on vertex $ 2 $ to get a wonderful tree.

In the third and fourth test cases, the tree is already wonderful, so you don't need to apply any operations.

## 样例 #1

### 输入

```
4
5
9 3 4 1 2
1 1 3 3
2
5 3
1
2
36 54
1
3
0 0 0
1 2
```

### 输出

```
3
2
0
0
```



---

---
title: "Triangle Formation"
layout: "post"
diff: 提高+/省选-
pid: CF1991F
tag: ['数学', '贪心']
---

# Triangle Formation

## 题目描述

### 题面描述
你有 $n$ 根棍子，从 $1$ 到 $n$ 编号。第 $i$ 根棍子的长度是 $a_i$。

你需要回答 $q$ 个问题。在每个查询中，你会得到两个整数 $l$ 和 $r$（$1 \le l < r \le n，r − l + 1 \le 6$）。确定是否可以从编号为l到r的棒中选择6个不同的棒，形成2个非退化三角形。

边长为 $a$、$b$ 和 $c$ 的三角形称为非退化三角形，当且仅当：

$a<b+c\text{，}b<a+c，c<a+b$。

## 输入格式

第一行包含两个整数 $n$ 和 $q$（ $6 \le n  \le 10^5，1 \le q \le 10^6$）——分别是条数和查询数。
第二行包含 $n$ 个整数 $a_1、a_2、\cdots、a_n$（$1 \le a_i \le 10^9$）—— $a_i$ 表示第 $i$ 根棒的长度。（$1 \le l < r \le n，r − l + 1 \le 6$）——每个查询的参数。

## 输出格式

对于每个查询，如果可以形成 $2$ 个三角形，则输出“YES”（不带引号），否则为“NO”（不带引号）。

在任何情况下都可以输出答案（大小写均可）。例如，字符串“yEs”、“yes”、“YeS”和“YEs”都将被识别为正确答案。

## 样例 #1

### 输入

```
10 5
5 2 2 10 4 10 6 1 5 3
1 6
2 7
2 8
5 10
4 10
```

### 输出

```
YES
NO
YES
NO
YES
```



---

---
title: "Prefix GCD"
layout: "post"
diff: 提高+/省选-
pid: CF2013E
tag: ['贪心', '数论']
---

# Prefix GCD

## 题目描述

Since Mansur is tired of making legends, there will be no legends for this task.

You are given an array of positive integer numbers $ a_1, a_2, \ldots, a_n $ . The elements of the array can be rearranged in any order. You need to find the smallest possible value of the expression $ $$$\gcd(a_1) + \gcd(a_1, a_2) + \ldots + \gcd(a_1, a_2, \ldots, a_n), $ $  where  $ \\gcd(a\_1, a\_2, \\ldots, a\_n) $  denotes the <a href="https://en.wikipedia.org/wiki/Greatest_common_divisor">greatest common divisor (GCD)</a> of  $ a\_1, a\_2, \\ldots, a\_n$$$.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single number $ n $ ( $ 1 \le n \le 10^5 $ ) — the size of the array.

The second line of each test case contains $ n $ numbers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^5 $ ) — the initial array.

The sum of $ n $ over all test cases does not exceed $ 10^5 $ .

The sum of $ \max(a_1, a_2, \ldots, a_n) $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single number on a separate line — the answer to the problem.

## 说明/提示

In the first test case, the elements can be rearranged as follows: $ [2, 4, 2] $ . Then the answer will be $ \gcd(2) + \gcd(2, 4) + \gcd(2, 4, 2) = 2 + 2 + 2 = 6 $ .

In the third test case, the elements can be rearranged as follows: $ [6, 10, 15] $ . Then the answer will be $ \gcd(6) + \gcd(6, 10) + \gcd(6, 10, 15) = 6 + 2 + 1 = 9 $ .

## 样例 #1

### 输入

```
5
3
4 2 2
2
6 3
3
10 15 6
5
6 42 12 52 20
4
42 154 231 66
```

### 输出

```
6
6
9
14
51
```



---

---
title: "Speedbreaker"
layout: "post"
diff: 提高+/省选-
pid: CF2018B
tag: ['贪心', '线段树']
---

# Speedbreaker

## 题目描述

[Djjaner - Speedbreaker](https://soundcloud.com/luciano-ferrari-151560131/speedbreaker)

⠀



There are $ n $ cities in a row, numbered $ 1, 2, \ldots, n $ left to right.

- At time $ 1 $ , you conquer exactly one city, called the starting city.
- At time $ 2, 3, \ldots, n $ , you can choose a city adjacent to the ones conquered so far and conquer it.

You win if, for each $ i $ , you conquer city $ i $ at a time no later than $ a_i $ . A winning strategy may or may not exist, also depending on the starting city. How many starting cities allow you to win?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of cities.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the deadlines for conquering the cities.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the number of starting cities that allow you to win.

## 说明/提示

In the first test case, cities $ 2 $ , $ 3 $ , and $ 4 $ are good starting cities.

In the second test case, there are no good starting cities.

In the third test case, the only good starting city is city $ 5 $ .

## 样例 #1

### 输入

```
3
6
6 3 3 3 5 5
6
5 6 4 1 4 5
9
8 6 4 2 1 3 5 7 9
```

### 输出

```
3
0
1
```



---

---
title: "Permutations Harmony"
layout: "post"
diff: 提高+/省选-
pid: CF2034E
tag: ['贪心', '分类讨论']
---

# Permutations Harmony

## 题目描述

Rayan wants to present a gift to Reyhaneh to win her heart. However, Reyhaneh is particular and will only accept a k-harmonic set of permutations.

We define a k-harmonic set of permutations as a set of $ k $ pairwise distinct permutations $ p_1, p_2, \ldots, p_k $ of size $ n $ such that for every pair of indices $ i $ and $ j $ (where $ 1 \leq i, j \leq n $ ), the following condition holds:

 $ $$$ p_1[i] + p_2[i] + \ldots + p_k[i] = p_1[j] + p_2[j] + \ldots + p_k[j]  $ $ </p><p>Your task is to help Rayan by either providing a valid <span class="tex-font-style-it">k-harmonic set of permutations</span> for given values of  $ n $  and  $ k $  or by determining that such a set does not exist.</p><p>We call a sequence of length  $ n $  a permutation if it contains every integer from  $ 1 $  to  $ n$$$ exactly once.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ), the number of test cases.

Each test case consists of two integers $ n $ and $ k $ ( $ 1 \leq n, k \leq 10^5 $ ). The sum of $ n \cdot k $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, if a k-harmonic set of permutations exists, print YES on the first line. Then, print $ k $ lines, each containing a distinct permutation of the integers from $ 1 $ to $ n $ .

If no such set exists, print NO on the first line.

You can output "YES" and "NO" in any case (for example, strings "yEs", "yes", and "Yes" will be recognized as a positive response).

If multiple answers are possible, you can output any of them.

## 说明/提示

In example 1, we have $ p_1 = [1, 2, 3] $ , $ p_2 = [2, 3, 1] $ , and $ p_3 = [3, 1, 2] $ . It's easy to see that $ p_1[1] + p_2[1] + p_3[1] = p_1[2] + p_2[2] + p_3[2] = p_1[3] + p_2[3] + p_3[3] = 6 $ .

In example 2, we have $ p_1 = [1, 2, 3, 4] $ and $ p_2 = [4, 3, 2, 1] $ . It's easy to see that $ p_1[1] + p_2[1] = p_1[2] + p_2[2] = p_1[3] + p_2[3] = p_1[4] + p_2[4] = 5 $ .

In example 3, as there are five distinct elements in $ p_1 $ , it's obvious that the answer is "No".

## 样例 #1

### 输入

```
4
3 3
4 2
5 1
3 2
```

### 输出

```
YES
1 2 3
2 3 1
3 1 2
YES
1 2 3 4
4 3 2 1
NO
YES
1 2 3
3 2 1
```



---

---
title: "Matrix Transformation"
layout: "post"
diff: 提高+/省选-
pid: CF2043E
tag: ['图论', '贪心', '位运算']
---

# Matrix Transformation

## 题目描述

给定两个大小为 $n \times m$ 的矩阵 $A$ 和 $B$，其中元素是 $0$ 到 $10^9$ 之间的整数。你可以对矩阵 $A$ 执行以下任意次数的操作，且操作顺序不受限制：

- **按位与操作**：选择某一行 $i$ 和一个非负整数 $x$，将这一行的每个元素用 $x$ 进行按位与运算。具体来说，对于行 $i$ 的每个元素 $A_{i,j}$，都替换为 $A_{i,j} \text{ & } x$。
- **按位或操作**：选择某一列 $j$ 和一个非负整数 $x$，将这一列的每个元素用 $x$ 进行按位或运算。具体来说，对于列 $j$ 的每个元素 $A_{i,j}$，都替换为 $A_{i,j} \text{ | } x$。

可以在每次操作中选择不同的 $x$ 值。

你的任务是判断是否可以通过上述操作，将矩阵 $A$ 转变为矩阵 $B$。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 100$），表示测试用例的数量。接下来是 $t$ 组测试用例。

每个测试用例如下：

- 第一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 10^3$ 且 $n \cdot m \le 10^3$），表示矩阵 $A$ 和 $B$ 的行数和列数。
- 接下来的 $n$ 行描述矩阵 $A$，每行包含 $m$ 个整数 $A_{i,1}, A_{i,2}, \dots, A_{i,m}$，表示该行的所有元素（$0 \le A_{i,j} \le 10^9$）。
- 再接下来的 $n$ 行描述矩阵 $B$，每行包含 $m$ 个整数 $B_{i,1}, B_{i,2}, \dots, B_{i,m}$，表示该行的所有元素（$0 \le B_{i,j} \le 10^9$）。

## 输出格式

对于每个测试用例，如果可以将矩阵 $A$ 转换为矩阵 $B$，请输出 `Yes`；否则输出 `No`。输出中的字母大小写不作要求。

## 说明/提示

以第二组输入数据为例，展示如何通过操作将矩阵 $A$ 转换为矩阵 $B$：

初始状态下，矩阵 $A$ 如下：

$$
\begin{bmatrix}
10 & 10 \\
42 & 42 \\
\end{bmatrix}
$$

1. 对第一行：应用按位与操作，选择 $x = 0$，矩阵变为：

$$
\begin{bmatrix}
0 & 0 \\
42 & 42 \\
\end{bmatrix}
$$

2. 对第二行：再次应用按位与操作，选择 $x = 0$，矩阵变为：

$$
\begin{bmatrix}
0 & 0 \\
0 & 0 \\
\end{bmatrix}
$$

3. 对第一列：应用按位或操作，选择 $x = 21$，矩阵变为：

$$
\begin{bmatrix}
21 & 0 \\
21 & 0 \\
\end{bmatrix}
$$

4. 对第二列：再次应用按位或操作，选择 $x = 21$，最终矩阵为：

$$
\begin{bmatrix}
21 & 21 \\
21 & 21 \\
\end{bmatrix}
$$

通过这一系列操作，我们成功将矩阵 $A$ 转换为矩阵 $B$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1 1
12
13
2 2
10 10
42 42
21 21
21 21
2 2
74 10
42 106
21 85
85 21
2 4
1 2 3 4
5 6 7 8
3 2 3 4
1 0 1 0
```

### 输出

```
Yes
Yes
No
Yes
```



---

---
title: "A, B, AB and BA"
layout: "post"
diff: 提高+/省选-
pid: CF2069E
tag: ['字符串', '贪心']
---

# A, B, AB and BA

## 题目描述

给定一个由字符 A 和 B 组成的字符串 $s$。

你的任务是将它分割成长度为 $1$ 或 $2$ 的块，使得：
- "A" 类型的块数量不超过 $a$；
- "B" 类型的块数量不超过 $b$；
- "AB" 类型的块数量不超过 $ab$；
- "BA" 类型的块数量不超过 $ba$；

其中 "AA" 和 "BB" 类型的块是被禁止的。原始字符串 $s$ 的每个字符必须恰好属于一个块。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。接下来输入 $t$ 个独立测试用例。

每个测试用例的第一行包含一个仅由字符 A 和/或 B 组成的字符串 $s$（$1 \le |s| \le 5 \cdot 10^5$）。

每个测试用例的第二行包含四个整数 $a$、$b$、$ab$ 和 $ba$（$0 \le a, b, ab, ba \le 5 \cdot 10^5$）——分别表示允许的 "A"、"B"、"AB" 和 "BA" 类型块的最大数量。

保证所有测试用例的 $s$ 总长度不超过 $5 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果能够分割字符串 $s$ 则输出 YES，否则输出 NO。

## 说明/提示

第三个测试用例中，所有可能的分割方式为：A|B|A、AB|A 或 A|BA。所有这些方式都至少包含一个 "A"。

第四个测试用例中，一种可能的分割方式是：A|B|B|A|B|A|A|B。

第五个测试用例中，一种可能的分割方式是：A|BA|B|BA|AB|BA|AB。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
7
A
0 0 10 10
B
0 1 0 0
ABA
0 0 1 1
ABBABAAB
5 5 0 0
ABABBAABBAAB
1 1 2 3
ABBBBAB
0 3 2 0
BAABBA
1 3 2 0
```

### 输出

```
NO
YES
NO
YES
YES
YES
NO
```



---

---
title: "Balancing"
layout: "post"
diff: 提高+/省选-
pid: CF2081B
tag: ['贪心']
---

# Balancing

## 题目描述

Ecrade 有一个整数数组 $a_1, a_2, \ldots, a_n$。保证对于每个 $1 \le i < n$，$a_i \neq a_{i+1}$。

Ecrade 可以通过若干次操作将数组变为严格递增的数组。

每次操作中，他可以选择两个整数 $l$ 和 $r$（$1 \le l \le r \le n$），并将 $a_l, a_{l+1}, \ldots, a_r$ 替换为任意 $r-l+1$ 个整数 $a'_l, a'_{l+1}, \ldots, a'_r$。替换后的数组需要满足以下约束：
- 对于每个 $l \le i < r$，$a'_i$ 和 $a'_{i+1}$ 之间的比较关系必须与原数组中 $a_i$ 和 $a_{i+1}$ 的比较关系相同。即，若原数组中 $a_i < a_{i+1}$，则替换后必须有 $a'_i < a'_{i+1}$；若原数组中 $a_i > a_{i+1}$，则替换后必须有 $a'_i > a'_{i+1}$；若原数组中 $a_i = a_{i+1}$，则替换后必须有 $a'_i = a'_{i+1}$。

Ecrade 想知道使数组严格递增所需的最少操作次数。由于问题有一定难度，请你帮助他！

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的第一行输入一个整数 $n$（$2 \le n \le 2 \cdot 10^5$）。

每个测试用例的第二行输入 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$-10^9 \le a_i \le 10^9$）。

保证对于每个 $1 \le i < n$，$a_i \neq a_{i+1}$。

保证所有测试用例的 $n$ 总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数表示使数组严格递增所需的最少操作次数。

## 说明/提示

第一个测试用例中，一种获得最少操作次数的方式为：
1. 第一次操作选择 $l = 2, r = 2$，将 $a'_2 = 4$，此时数组变为 $[3, 4, 1]$；
2. 第二次操作选择 $l = 1, r = 2$，将 $a'_1 = -1, a'_2 = 0$，此时数组变为 $[-1, 0, 1]$。

第二个测试用例中，一种获得最少操作次数的方式为：
1. 第一次操作选择 $l = 2, r = 3$，将 $a'_2 = 4, a'_3 = 5$，此时数组变为 $[3, 4, 5]$。

第三个测试用例中，一种获得最少操作次数的方式为：
1. 第一次操作选择 $l = 2, r = 3$，将 $a'_2 = -1, a'_3 = 1$，此时数组变为 $[-2, -1, 1, 2]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3
3 2 1
3
3 1 2
4
-2 -5 5 2
7
1 9 1 9 8 1 0
```

### 输出

```
2
1
1
3
```



---

---
title: "Serval and Colorful Array (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2085F1
tag: ['贪心', '枚举', '差分']
---

# Serval and Colorful Array (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本的区别在于此版本中 $n \leq 3000$。仅当您解决了该问题的所有版本时才能进行 hack。

Serval 有一个魔法数 $k$（$k \geq 2$）。我们称数组 $r$ 为 colorful 当且仅当：
- $r$ 的长度为 $k$，且
- $1$ 到 $k$ 之间的每个整数在 $r$ 中恰好出现一次。

给定一个由 $n$ 个介于 $1$ 到 $k$ 的整数组成的数组 $a$。保证 $1$ 到 $k$ 之间的每个整数在 $a$ 中至少出现一次。您可以对 $a$ 执行以下操作：
- 选择一个下标 $i$（$1 \leq i < n$），然后交换 $a_i$ 和 $a_{i+1}$。

求使得 $a$ 中至少存在一个 colorful 子数组$^{\text{∗}}$所需的最小操作次数。可以证明在题目约束下这总是可行的。

$^{\text{∗}}$数组 $b$ 是数组 $a$ 的子数组，当且仅当 $b$ 可以通过从 $a$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 1000$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$2 \leq k \leq n \leq 3000$）——数组 $a$ 的长度和 Serval 的魔法数。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \leq a_i \leq k$）——数组 $a$ 的元素。保证 $1$ 到 $k$ 之间的每个整数在 $a$ 中至少出现一次。

保证所有测试用例的 $n$ 之和不超过 $3000$。

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
title: "Zebra-like Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF2086E
tag: ['数学', '贪心', '记忆化搜索', '数位 DP']
---

# Zebra-like Numbers

## 题目描述

我们称一个正整数为斑马数（zebra-like），如果它的二进制表示从最高有效位开始是交替的比特位，并且最低有效位等于 $1$。例如，数字 $1$、$5$ 和 $21$ 都是斑马数，因为它们的二进制表示 $1$、$101$ 和 $10101$ 满足要求，而数字 $10$ 不是斑马数，因为它的二进制表示 $1010$ 的最低有效位是 $0$。

我们定义一个正整数 $e$ 的斑马值为最小的整数 $p$，使得 $e$ 可以表示为 $p$ 个斑马数（可以相同也可以不同）的和。

给定三个整数 $l$、$r$ 和 $k$，计算满足 $l \le x \le r$ 且 $x$ 的斑马值等于 $k$ 的整数 $x$ 的数量。

## 输入格式

每个测试包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 100$）——测试用例的数量。接下来是测试用例的描述。

每个测试用例的唯一一行包含三个整数 $l$、$r$（$1 \le l \le r \le 10^{18}$）和 $k$（$1 \le k \le 10^{18}$）。

## 输出格式

对于每个测试用例，输出一个整数——区间 $[l, r]$ 内斑马值为 $k$ 的整数的数量。

## 说明/提示

- 在第一个测试用例中，有 $13$ 个符合条件的数字：$3, 7, 11, 15, 23, 27, 31, 43, 47, 63, 87, 91, 95$。每个数字都可以表示为 $3$ 个斑马数的和。
- 在第二个测试用例中，数字 $1$ 的斑马值为 $1$，因此输出 $1$。
- 在第四个测试用例中，区间 $[2, 10]$ 内没有数字的斑马值为 $100$，因此输出 $0$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
1 100 3
1 1 1
15 77 2
2 10 100
1234567 123456789101112131 12
```

### 输出

```
13
1
3
0
4246658701
```



---

---
title: "Canteen (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2089B2
tag: ['贪心', '二分', '单调队列']
---

# Canteen (Hard Version)

## 题目描述

这是该问题的困难版本。两个版本的区别在于此版本中，对 $$$k$$$ 没有额外限制。只有当你解决了该问题的所有版本时才能进行 hack。

Ecrade 有两个由整数构成的序列 $$$a_0, a_1, \ldots, a_{n - 1}$$$ 和 $$$b_0, b_1, \ldots, b_{n - 1}$$$。保证 $$$a$$$ 中所有元素的总和不超过 $$$b$$$ 中所有元素的总和。

初始时，Ecrade 可以对序列 $$$a$$$ 进行恰好 $$$k$$$ 次修改。保证 $$$k$$$ 不超过 $$$a$$$ 的总和。每次修改操作如下：
- 选择一个整数 $$$i$$$（$$0 \le i < n$$）满足 $$$a_i > 0$$$，并执行 $$$a_i := a_i - 1$$$。

然后，Ecrade 将对 $$$a$$$ 和 $$$b$$$ 依次执行以下三个操作，这三个操作构成一轮操作：
1. 对每个 $$$0 \le i < n$$$：$$t := \min(a_i, b_i)$$，$$a_i := a_i - t$$，$$b_i := b_i - t$$；
2. 对每个 $$$0 \le i < n$$$：$$c_i := a_{(i - 1) \bmod n}$$；
3. 对每个 $$$0 \le i < n$$$：$$a_i := c_i$$。

Ecrade 想知道，在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$$0$$$ 所需的最小轮数。

然而，这似乎有些复杂，因此请帮助他！

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $$$t$$$（$$1 \le t \le 2 \cdot 10^4$$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $$$n$$$、$$k$$（$$1 \le n \le 2 \cdot 10^5$$，$$0 \le k \le 2 \cdot 10^{14}$$）。

每个测试用例的第二行包含 $$$n$$$ 个整数 $$$a_0, a_1, \ldots, a_{n - 1}$$$（$$1 \le a_i \le 10^9$$）。

每个测试用例的第三行包含 $$$n$$$ 个整数 $$$b_0, b_1, \ldots, b_{n - 1}$$$（$$1 \le b_i \le 10^9$$）。

保证所有测试用例的 $$$n$$$ 之和不超过 $$$2 \cdot 10^5$$$。同时保证每个测试用例中 $$$a$$$ 的总和不超过 $$$b$$$ 的总和，且 $$$k$$$ 不超过 $$$a$$$ 的总和。

## 输出格式

对于每个测试用例，输出在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$$0$$$ 所需的最小轮数。


## 说明/提示

在第五个测试用例中，$$$a$$$ 的所有元素在恰好 $$$6$$$ 次修改后变为 $$$0$$$。

在第六个测试用例中，Ecrade 可以对 $$$a_3$$$ 进行一次修改，之后 $$$a$$$ 将变为 $$$[1,2,2,4]$$$：
- 第一轮操作后，$$a=[3,0,0,0]$$，$$b=[3,1,0,0]$$；
- 第二轮操作后，$$a=[0,0,0,0]$$，$$b=[0,1,0,0]$$。

在第七个测试用例中，Ecrade 可以对 $$$a_4$$$ 进行一次修改，之后 $$$a$$$ 将变为 $$$[2,1,1,1]$$$：
- 第一轮操作后，$$a=[0,1,0,0]$$，$$b=[0,1,1,0]$$；
- 第二轮操作后，$$a=[0,0,0,0]$$，$$b=[0,0,1,0]$$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
3 0
1 1 4
5 1 4
4 0
1 2 3 4
4 3 2 1
4 0
2 1 1 2
1 2 2 1
8 0
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
3 6
1 1 4
5 1 4
4 1
1 2 3 4
4 3 2 1
4 1
2 1 1 2
1 2 2 1
4 2
2 1 1 2
1 2 2 1
```

### 输出

```
1
4
4
8
0
2
2
1
```



---

---
title: "Wonderful Teddy Bears"
layout: "post"
diff: 提高+/省选-
pid: CF2096E
tag: ['贪心']
---

# Wonderful Teddy Bears

## 题目描述

你是 $n$ 只泰迪熊的骄傲主人，它们被排成一列放在架子上。每只泰迪熊的颜色是黑色或粉色。

如果所有黑色泰迪熊都位于所有粉色泰迪熊的左侧，则称这种排列是美丽的。换句话说，不存在一对索引 $(i, j)$（$1 \leq i < j \leq n$）使得第 $i$ 只泰迪熊是粉色且第 $j$ 只泰迪熊是黑色。

你希望将这些泰迪熊重新排列成美丽的顺序。由于你够不到架子，但幸运的是，你可以向机器人发送指令来移动泰迪熊。在单条指令中，机器人可以：

- 选择一个索引 $i$（$1 \le i \le n - 2$），并将位置 $i$、$i + 1$ 和 $i + 2$ 的泰迪熊重新排列，使得所有黑色泰迪熊位于所有粉色泰迪熊的左侧。

最少需要多少条指令才能完成重新排列？

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$3 \le n \le 2 \cdot 10^5$）——泰迪熊的数量。

每个测试用例的第二行包含一个长度为 $n$ 的字符串 $s$，由字符 `B` 和 `P` 组成——表示泰迪熊的颜色。对于从 $1$ 到 $n$ 的每个 $i$，如果 $s_i = \texttt{B}$，则第 $i$ 只泰迪熊是黑色；如果 $s_i = \texttt{P}$，则是粉色。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——完成重新排列所需的最少指令数。


## 说明/提示

对于第一个测试用例，所有泰迪熊都是粉色。因此，排列已经是美丽的，答案为 $0$。

对于第二个测试用例，所有黑色泰迪熊已经位于所有粉色泰迪熊的左侧。因此，答案为 $0$。

对于第三个测试用例，我们可以执行 $1$ 条指令，选择 $i = 1$。

执行指令后，颜色序列从 $\texttt{PPB}$ 变为 $\texttt{BPP}$，任务完成。

对于第四个测试用例，我们可以执行 $5$ 条指令如下：

- $i = 1$：$\texttt{}\color{magenta}{\texttt{PPB}}\texttt{PPBB} \rightarrow \texttt{}\color{magenta}{\texttt{BPP}}\texttt{PPBB}$
- $i = 5$：$\texttt{BPPP}\color{magenta}{\texttt{PBB}}\texttt{} \rightarrow \texttt{BPPP}\color{magenta}{\texttt{BBP}}\texttt{}$
- $i = 4$：$\texttt{BPP}\color{magenta}{\texttt{PBB}}\texttt{P} \rightarrow \texttt{BPP}\color{magenta}{\texttt{BBP}}\texttt{P}$
- $i = 3$：$\texttt{BP}\color{magenta}{\texttt{PBB}}\texttt{PP} \rightarrow \texttt{BP}\color{magenta}{\texttt{BBP}}\texttt{PP}$
- $i = 2$：$\texttt{B}\color{magenta}{\texttt{PBB}}\texttt{PPP} \rightarrow \texttt{B}\color{magenta}{\texttt{BBP}}\texttt{PPP}$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
PPP
3
BPP
3
PPB
7
PPBPPBB
15
BPBPBBBBBPBBBBB
```

### 输出

```
0
0
1
5
14
```



---

---
title: "23 Kingdom"
layout: "post"
diff: 提高+/省选-
pid: CF2101C
tag: ['贪心', '标签477']
---

# 23 Kingdom

## 题目描述

我们定义 $d_x(c)$ 为整数 $x$ 在数列 $c$ 中的距离，也就是 $c$ 中出现的两个 $x$ 之间的最长间隔。若 $x$ 出现的次数不足两次则为零。

形式化地，$d_x(c)=\max\limits_{1\le i<j\le\vert c\vert\wedge c_i=c_j=x}(j-i)$。

定义一个数列 $c$ 的美丽度为 $\sum\limits_{i=1}^n d_i(c)$。

给你一个长为 $n$ 的数列 $a$，你将构造一个长为 $n$ 的数列 $b$，要求每一项均满足 $1\le b_i\le a_i$。求这样的 $b$ 的最大美丽度。你需要求出这个值。

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 10^4)$ 表示数据组数。

对于每组数据：\
第一行一个整数 $n(1\le n\le 2\times 10^5)$。\
第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n(1\le a_i\le n)$。

保证单个测试点中 $\sum n\le 2\times 10^5$。

## 输出格式

每组数据输出一行一个整数，表示答案。

## 说明/提示

**样例解释**

第一组数据中，令 $b=(1,2,1,2)$，$d_1(b)=3-1=2,d_2(b)=4-2=2$，美丽度为 $4$。可以证明这个可能的最大的美丽值。

第二组数据中，令 $b=(1,1)$ 或 $b=(2,2)$ 均可得到 $1$ 的美丽值。

第三组数据中，令 $b=(1,2,1,4,1,2,1,1,1,2)$，则有 $d_1(b)=9-1=8,d_2(b)=10-2=8,d_4(b)=0$，可以获得 $16$ 的美丽值。

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
4
4
1 2 1 2
2
2 2
10
1 2 1 5 1 2 2 1 1 2
8
1 5 2 8 4 1 4 2
```

### 输出

```
4
1
16
16
```



---

---
title: "Ain and Apple Tree"
layout: "post"
diff: 提高+/省选-
pid: CF2107E
tag: ['数学', '贪心', '最近公共祖先 LCA']
---

# Ain and Apple Tree

## 题目描述

如果我也被从苹果树上掉下的苹果砸中，我能变得像牛顿一样擅长物理吗？

为了更擅长物理，Ain 想建造一棵苹果树，这样她就能被树上的苹果砸中。她的苹果树有 $n$ 个节点，根节点为 $1$。她将苹果树的权重定义为 $\sum \limits_{i=1}^n \sum \limits_{j=i+1}^n \text{dep}(\operatorname{lca}(i,j))$。

这里，$\text{dep}(x)$ 定义为从节点 $1$ 到节点 $x$ 的唯一最短路径上的边数。$\operatorname{lca}(i, j)$ 定义为在路径 $(1, i)$ 和 $(1, j)$ 上同时出现且 $\text{dep}(x)$ 值最大的唯一节点 $x$。

Ain 从一些旧书中得知，牛顿的苹果树的权重大约是 $k$，但具体的值已经丢失了。

作为 Ain 的朋友，你想为她建造一棵有 $n$ 个节点的苹果树，且树的权重与 $k$ 的绝对差不超过 $1$，即 $|\text{权重} - k| \le 1$。如果无法满足这一条件，请报告这一情况。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例的第一行包含两个数字 $n, k$（$2 \le n \le 10^5$，$0 \le k \le 10^{15}$）。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果存在解，首先输出 `Yes`，否则输出 `No`。你可以使用任意大小写，例如 `YES` 和 `yEs` 也会被接受。

如果至少存在一个解，则输出 $n-1$ 行，每行包含两个数字 $u, v$（$1 \le u, v \le n$），表示苹果树的边。


## 说明/提示

在第一个测试用例中，我们可以验证权重为 $0$。这满足条件，因为 $k = 1$，所以绝对差仅为 $1$。

在第二个测试用例中，不存在解，因为没有 $2$ 个节点的树的权重为 $1$、$2$ 或 $3$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2 1
2 2
4 0
5 7
5 5
```

### 输出

```
Yes
1 2
No
Yes
1 2
1 3
1 4
Yes
1 3
3 5
4 5
3 2
Yes
1 2
2 3
2 4
2 5
```



---

---
title: "Cycling (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2107F1
tag: ['动态规划 DP', '贪心']
---

# Cycling (Easy Version)

## 题目描述

> 这是此问题的简单版本，和其他版本的区别是此版本中 $n\le 5000$，且你不需要对每个前缀都求解。

Leo 骑车去见他的女朋友。在 Leo 的前面有 $n$ 名骑手，从前往后排在第 $i$ 名的骑手的灵活度为 $a_i$。

Leo 将要加速超过前面的所有骑手，他可以执行以下两种操作：
- 当他在骑手 $i$ 后面，骑手 $i+1$ 前面（或 $i=n$）时，付出 $a_i$ 的代价超过骑手 $i$，之后他将在骑手 $i$ 前面，骑手 $i-1$ 后面（如果 $i>1$）；
- 使用他的超级力量交换 $a_i$ 和 $a_j$，代价为 $\vert i-j\vert$。

请你找出超过所有 $n$ 名骑手的最小代价。

## 输入格式

多组数据，第一行一个整数 $t(1\le t\le 1000)$，表示数据组数。

对于每组数据，第一行一个整数 $n(1\le n\le 5000)$。\
第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n(1\le a_i\le 10^9)$。

保证单个测试点中 $\sum n\le 5000$。

## 输出格式

对于每组数据，输出一行一个整数，表示答案。

## 说明/提示

**样例解释**

第一组数据中，一组操作如下所示：
- 交换 $a_2$ 和 $a_3$，之后 $a=(1,4,2)$，代价为 $1$；
- 超过第 $3$ 名骑手，代价为 $2$；
- 交换 $a_1$ 和 $a_2$，$a=(4,1,2)$，代价为 $1$；
- 超过第 $2$ 名骑手，代价为 $1$；
- 交换 $a_1$ 和 $a_2$，$a=(1,4,2)$，代价为 $1$；
- 超过第 $1$ 名骑手，代价为 $1$。

总代价为 $7$。可以证明这是最小的代价。

第二组数据中如果一直执行“超过”操作，花费为 $4$。可以证明这是最小的代价。

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
7
4
3
8
```



---

---
title: "Cheater"
layout: "post"
diff: 提高+/省选-
pid: CF2113D
tag: ['贪心', '二分']
---

# Cheater

## 题目描述

你正在赌场玩一种新的纸牌游戏，规则如下：

1. 游戏使用一副共 $2n$ 张不同点数的牌。
2. 牌堆被均匀分给玩家和庄家：每人获得 $n$ 张牌。
3. 在 $n$ 轮比赛中，玩家和庄家同时打出手中最上面的一张牌。比较两张牌的点数，点数较大的一方获得 $1$ 分。获胜的牌会被移出游戏，而失败的牌会返回持有者的手牌，并放在该玩家手牌堆的最上面。

注意游戏总是会进行恰好 $n$ 轮。

你已经追踪了洗牌过程，知道庄家手牌的从上到下的顺序。为了最大化你的得分，你可以在游戏开始前交换手中任意两张牌的位置（最多交换一次以避免引起怀疑）。

请确定你能获得的最大分数。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 5 \cdot 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 2 \cdot 10^{5}$）——玩家手牌的数量。

第二行包含 $n$ 个整数 $a_{1}, a_{2}, \ldots, a_{n}$（$1 \leq a_{i} \leq 2n$）——玩家手牌从上到下的点数。

第三行包含 $n$ 个整数 $b_{1}, b_{2}, \ldots, b_{n}$（$1 \leq b_{i} \leq 2n$）——庄家手牌从上到下的点数。

保证所有牌的点数都是唯一的。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——你能获得的最大分数。

## 说明/提示

在第一个测试用例中，可以不交换任何牌。游戏过程如下：

1. 比较点数为 $13$ 和 $6$ 的牌。玩家获胜，得 $1$ 分。
2. 比较点数为 $7$ 和 $6$ 的牌。玩家获胜，得 $1$ 分。
3. 比较点数为 $4$ 和 $6$ 的牌。庄家获胜。
4. 比较点数为 $4$ 和 $1$ 的牌。玩家获胜，得 $1$ 分。
5. 比较点数为 $9$ 和 $1$ 的牌。玩家获胜，得 $1$ 分。
6. 比较点数为 $12$ 和 $1$ 的牌。玩家获胜，得 $1$ 分。
7. 比较点数为 $10$ 和 $1$ 的牌。玩家获胜，得 $1$ 分。

因此玩家总共获得 $6$ 分。

在第二个测试用例中，可以交换点数为 $1$ 和 $5$ 的牌，交换后玩家手牌变为 $[5, 6, 1]$。游戏过程如下：

1. 比较点数为 $5$ 和 $2$ 的牌。玩家获胜，得 $1$ 分。
2. 比较点数为 $6$ 和 $2$ 的牌。玩家获胜，得 $1$ 分。
3. 比较点数为 $1$ 和 $2$ 的牌。庄家获胜。

因此玩家总共获得 $2$ 分。

在第三个测试用例中，可以交换点数为 $3$ 和 $10$ 的牌，交换后玩家手牌变为 $[8, 6, 10, 3, 1]$。游戏过程如下：

1. 比较点数为 $8$ 和 $7$ 的牌。玩家获胜，得$1$分。
2. 比较点数为 $6$ 和 $7$ 的牌。庄家获胜。
3. 比较点数为 $6$ 和 $9$ 的牌。庄家获胜。
4. 比较点数为 $6$ 和 $5$ 的牌。玩家获胜，得 $1$ 分。
5. 比较点数为 $10$ 和 $5 $的牌。玩家获胜，得 $1$ 分。

因此玩家总共获得 $3$ 分。

## 样例 #1

### 输入

```
3
7
13 7 4 9 12 10 2
6 1 14 3 8 5 11
3
1 6 5
2 3 4
5
8 6 3 10 1
7 9 5 2 4
```

### 输出

```
6
2
3
```



---

---
title: "George and Cards"
layout: "post"
diff: 提高+/省选-
pid: CF387E
tag: ['贪心', '线段树', '二分']
---

# George and Cards

## 题目描述

George is a cat, so he loves playing very much.

Vitaly put $ n $ cards in a row in front of George. Each card has one integer written on it. All cards had distinct numbers written on them. Let's number the cards from the left to the right with integers from $ 1 $ to $ n $ . Then the $ i $ -th card from the left contains number $ p_{i} $ ( $ 1<=p_{i}<=n $ ).

Vitaly wants the row to have exactly $ k $ cards left. He also wants the $ i $ -th card from left to have number $ b_{i} $ written on it. Vitaly gave a task to George, to get the required sequence of cards using the remove operation $ n-k $ times.

In one remove operation George can choose $ w $ ( $ 1<=w $ ; $ w $ is not greater than the current number of cards in the row) contiguous cards (contiguous subsegment of cards). Let's denote the numbers written on these card as $ x_{1},x_{2},...,x_{w} $ (from the left to the right). After that, George can remove the card $ x_{i} $ , such that $ x_{i}<=x_{j} $ for each $ j $ $ (1<=j<=w) $ . After the described operation George gets $ w $ pieces of sausage.

George wondered: what maximum number of pieces of sausage will he get in total if he reaches his goal and acts optimally well? Help George, find an answer to his question!

## 输入格式

The first line contains integers $ n $ and $ k $ ( $ 1<=k<=n<=10^{6} $ ) — the initial and the final number of cards.

The second line contains $ n $ distinct space-separated integers $ p_{1},p_{2},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — the initial row of cards.

The third line contains $ k $ space-separated integers $ b_{1},b_{2},...,b_{k} $ — the row of cards that you need to get. It is guaranteed that it's possible to obtain the given row by using the remove operation for $ n-k $ times.

## 输出格式

Print a single integer — the maximum number of pieces of sausage that George can get if he acts optimally well.

## 样例 #1

### 输入

```
3 2
2 1 3
1 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10 5
1 2 3 4 5 6 7 8 9 10
2 4 6 8 10

```

### 输出

```
30

```



---

---
title: "Fox and Card Game"
layout: "post"
diff: 提高+/省选-
pid: CF388C
tag: ['贪心', '博弈论']
---

# Fox and Card Game

## 题目描述

Fox Ciel is playing a card game with her friend Fox Jiro. There are $ n $ piles of cards on the table. And there is a positive integer on each card.

The players take turns and Ciel takes the first turn. In Ciel's turn she takes a card from the top of any non-empty pile, and in Jiro's turn he takes a card from the bottom of any non-empty pile. Each player wants to maximize the total sum of the cards he took. The game ends when all piles become empty.

Suppose Ciel and Jiro play optimally, what is the score of the game?

## 输入格式

The first line contain an integer $ n $ ( $ 1<=n<=100 $ ). Each of the next $ n $ lines contains a description of the pile: the first integer in the line is $ s_{i} $ ( $ 1<=s_{i}<=100 $ ) — the number of cards in the $ i $ -th pile; then follow $ s_{i} $ positive integers $ c_{1} $ , $ c_{2} $ , ..., $ c_{k} $ , ..., $ c_{si} $ ( $ 1<=c_{k}<=1000 $ ) — the sequence of the numbers on the cards listed from top of the current pile to bottom of the pile.

## 输出格式

Print two integers: the sum of Ciel's cards and the sum of Jiro's cards if they play optimally.

## 说明/提示

In the first example, Ciel will take the cards with number 100 and 1, Jiro will take the card with number 10.

In the second example, Ciel will take cards with numbers 2, 8, 6, 5, 9 and Jiro will take cards with numbers 4, 7, 1, 3.

## 样例 #1

### 输入

```
2
1 100
2 1 10

```

### 输出

```
101 10

```

## 样例 #2

### 输入

```
1
9 2 8 6 5 9 4 7 1 3

```

### 输出

```
30 15

```

## 样例 #3

### 输入

```
3
3 1 3 2
3 5 4 6
2 8 7

```

### 输出

```
18 18

```

## 样例 #4

### 输入

```
3
3 1000 1000 1000
6 1000 1000 1000 1000 1000 1000
5 1000 1000 1000 1000 1000

```

### 输出

```
7000 7000

```



---

---
title: "Painting Fence"
layout: "post"
diff: 提高+/省选-
pid: CF448C
tag: ['贪心', '递归', '分治']
---

# Painting Fence

## 题目描述

Bizon the Champion isn't just attentive, he also is very hardworking.

Bizon the Champion decided to paint his old fence his favorite color, orange. The fence is represented as $ n $ vertical planks, put in a row. Adjacent planks have no gap between them. The planks are numbered from the left to the right starting from one, the $ i $ -th plank has the width of $ 1 $ meter and the height of $ a_{i} $ meters.

Bizon the Champion bought a brush in the shop, the brush's width is $ 1 $ meter. He can make vertical and horizontal strokes with the brush. During a stroke the brush's full surface must touch the fence at all the time (see the samples for the better understanding). What minimum number of strokes should Bizon the Champion do to fully paint the fence? Note that you are allowed to paint the same area of the fence multiple times.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=5000) $ — the number of fence planks. The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ .

## 输出格式

Print a single integer — the minimum number of strokes needed to paint the whole fence.

## 说明/提示

In the first sample you need to paint the fence in three strokes with the brush: the first stroke goes on height 1 horizontally along all the planks. The second stroke goes on height 2 horizontally and paints the first and second planks and the third stroke (it can be horizontal and vertical) finishes painting the fourth plank.

In the second sample you can paint the fence with two strokes, either two horizontal or two vertical strokes.

In the third sample there is only one plank that can be painted using a single vertical stroke.

## 样例 #1

### 输入

```
5
2 2 1 2 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2
2 2

```

### 输出

```
2

```

## 样例 #3

### 输入

```
1
5

```

### 输出

```
1

```



---

---
title: "Kindergarten"
layout: "post"
diff: 提高+/省选-
pid: CF484D
tag: ['动态规划 DP', '贪心']
---

# Kindergarten

## 题目描述

In a kindergarten, the children are being divided into groups. The teacher put the children in a line and associated each child with his or her integer charisma value. Each child should go to exactly one group. Each group should be a nonempty segment of consecutive children of a line. A group's sociability is the maximum difference of charisma of two children in the group (in particular, if the group consists of one child, its sociability equals a zero).

The teacher wants to divide the children into some number of groups in such way that the total sociability of the groups is maximum. Help him find this value.

## 输入格式

The first line contains integer $n$ — the number of children in the line ($1\le n\le 10^6$).

The second line contains $n$ integers $a_i$ — the charisma of the $i$-th child ($-10^9\le a_i\le 10^9$).

## 输出格式

Print the maximum possible total sociability of all groups.

## 说明/提示

In the first test sample one of the possible variants of an division is following: the first three children form a group with sociability 2, and the two remaining children form a group with sociability 1.

In the second test sample any division leads to the same result, the sociability will be equal to 0 in each group.

## 样例 #1

### 输入

```
5
1 2 3 1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
3 3 3

```

### 输出

```
0

```



---

---
title: "Gadgets for dollars and pounds"
layout: "post"
diff: 提高+/省选-
pid: CF609D
tag: ['贪心', '二分', '前缀和']
---

# Gadgets for dollars and pounds

## 题目描述

一个人手上有 $s$ 卢布，他要在 $n$ 天内买 $m$ 样东西中的 $k$ 样。

每个物品有两种支付方式，要么用美元，要么用英镑。

每天有不同的支付方式代价，即换取一美元或英镑，需要付出 $x_i$ 卢布的代价。

求最早完成买 $k$ 样东西的天数。如果无法完成任务，输出 `-1`。

一种商品只能购买一次，但是一天可以买多种商品。

## 输入格式

第一行包含四个整数，$n, m, k, s$。

第二行 $n$ 个整数，表示每天多少卢布换一美元。

第三行 $n$ 个整数，表示多少卢布换一英镑。

接下来是 $m$ 行，每行 $2$ 个整数，表示每样东西用什么货币结账（ $1$ 是美元，$2$ 是英镑），以及要多少那种外币。

## 输出格式

输出最短到第几天买完 $k$ 样商品。

以及输出 $q_i$ 与 $d_i$ 表示在第 $d_i$ 天购买第 $q_i$ 样东西。

## 样例 #1

### 输入

```
5 4 2 2
1 2 3 2 1
3 2 1 2 3
1 1
2 1
1 2
2 2

```

### 输出

```
3
1 1
2 3

```

## 样例 #2

### 输入

```
4 3 2 200
69 70 71 72
104 105 106 107
1 1
2 2
1 2

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
4 3 1 1000000000
900000 910000 940000 990000
990000 999000 999900 999990
1 87654
2 76543
1 65432

```

### 输出

```
-1

```



---

---
title: "Hamiltonian Spanning Tree"
layout: "post"
diff: 提高+/省选-
pid: CF618D
tag: ['贪心']
---

# Hamiltonian Spanning Tree

## 题目描述

n 个城市之间形成了一个有n*(n-1)/2条边的完全无向图。走每条边需要y秒。  

给定该图的一个n-1条边的生成树，走树上的每一条边只需要x秒（不过注意x不一定小于y）。

你希望从任意一个点开始，经过每个点恰好一次，在任意一个点结束的路径的长度所花时间最少。求最少时间。

## 输入格式

第一行包含三个整数 n,x,y  
接下来 n−1行每行包含两个整数a和b，表示生成树上a与 b之间有一条边。保证这些边形成一棵生成树。

## 输出格式

输出一个整数，表示环游城市最小时间。

## 样例 #1

### 输入

```
5 2 3
1 2
1 3
3 4
5 3

```

### 输出

```
9

```

## 样例 #2

### 输入

```
5 3 2
1 2
1 3
3 4
5 3

```

### 输出

```
8

```



---

---
title: "Contest Balloons"
layout: "post"
diff: 提高+/省选-
pid: CF725D
tag: ['模拟', '贪心', '优先队列', '队列']
---

# Contest Balloons

## 题目描述

ACM比赛，大家都知道。AC一题会有一个气球。
现在有$n(2<=n<=300000)$ 支队伍，每支队伍的重量是$w_i$ ，拥有$t_i$ 个气球$(w_i,t_i<=10^{18})$ ，当一支队伍的气球个数比它的重量都要大时，这个队伍就会飘起来，从而被取消比赛资格。
现在你带领的是1号队，你希望你队伍的名次尽可能靠前，你是个有原则的人，不会偷气球，但你可以把气球送给别的队伍，让他们飞起来。
求最终你的队伍所获得的最好名次

## 输入格式

第一行：一个正整数$n(2<=n<=300000)$ ，队伍的总数
第二行到第$n+1$ 行：每行两个整数$t_i,w_i(0<=t_i<=w_i<=10^{18})$ ，分别表示第$i$ 个队伍气球的个数以及它的重量。你的队伍是1号队。

## 输出格式

仅有一行，输出你带领的队伍能够达到的最好名次

感谢@2016wudi 提供的翻译

## 样例 #1

### 输入

```
8
20 1000
32 37
40 1000
45 50
16 16
16 16
14 1000
2 1000

```

### 输出

```
3

```

## 样例 #2

### 输入

```
7
4 4
4 4
4 4
4 4
4 4
4 4
5 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
7
14000000003 1000000000000000000
81000000000 88000000000
5000000000 7000000000
15000000000 39000000000
46000000000 51000000000
0 1000000000
0 0

```

### 输出

```
2

```



---

---
title: "Bottles"
layout: "post"
diff: 提高+/省选-
pid: CF730J
tag: ['贪心', '枚举', '背包 DP']
---

# Bottles

## 题目描述

有 $n$ 瓶水，第 $i$ 瓶水的水量为 $a_i$，容量为 $b_i$。将 $1$ 单位水从一个瓶子转移到另一个瓶子所消耗时间为 $1$ 秒，且可以进行无限次转移。求储存所有水所需最小瓶子数 $k$ 以及该情况下所用最小时间 $t$。

## 输入格式

第一行输入一个正整数 $n$（$1\le n\le 100$）。

第二行输入 $n$ 个正整数，第 $i$ 个正整数表示 $a_i$（$1\le a_i \le 100$）。

第三行输入 $n$ 个正整数，第 $i$ 个正整数表示 $b_i$（$1\le b_i \le100$）。

对于每一个 $i$，满足$a_i\le b_i$。

## 输出格式

输出一行两个整数：$k$ 和 $t$。

## 样例 #1

### 输入

```
4
3 3 4 3
4 7 6 5

```

### 输出

```
2 6

```

## 样例 #2

### 输入

```
2
1 1
100 100

```

### 输出

```
1 1

```

## 样例 #3

### 输入

```
5
10 30 5 6 24
10 41 7 8 24

```

### 输出

```
3 11

```



---

---
title: "Sockets"
layout: "post"
diff: 提高+/省选-
pid: CF732E
tag: ['贪心', '优先队列', '队列']
---

# Sockets

## 题目描述

ICM ACPC 世界决赛就要来临了！不幸的是，赛事组织者因为在准备赛题时太忙碌了，他们几乎忘了一个关键点——为参赛者的工作站准备电力资源。  
  
赛场有 $n$ 台为参赛者准备的电脑，第 $i$ 台电脑拥有与正整数 $p_i$ 相等大小的电源。同时，有 $m$ 个可用的插座，第 $j$ 个插座拥有与正整数 $s_j$ 相等的电源。只有当 $p_i = s_j$ 时才可以将第 $i$ 台电脑和第 $j$ 个插座连接。一台电脑只可以接一个插座。不仅如此，如果所有的电脑与插座的电源都不同，那么没有任何电脑可以接通至插座。  
  
为了解决问题，Puch Williams 教授紧急订购了一车适配器（电源分离器）。每个适配器都有一个插头与一个插座，在它们之间还有一个分压器。在将适配器插入一个带有 $x$ 的电源后，适配器上的插座将会拥有一个 $\left \lceil \frac{x}{2} \right \rceil $ 的电源，这代表着将被插入的插座的电源除以 $2$，再取顶。例如：$\left \lceil \frac{10}{2} \right \rceil =5$，$\left \lceil \frac{15}{2} \right \rceil =8$。  
  
每个适配器只能使用一次。它可以被多次串联。例如，在将一个适配器插入一个插入带有 $10$ 电源的插座的适配器时，可以将一个带有 $3$ 电源的电脑插入这个适配器。  
  
组织者们会安装这些适配器，以确保它会同时输送给最多 $c$ 台电脑。如果有多种连接方案，组织者们想要在连接最多 $c$ 台电脑的前提下，使用最少 $u$ 个适配器的方案。  
  
你的任务是帮助组织者们计算完成这个任务最大的 $c$ 和最小的 $u$。  
  
这一车适配器是足够这个任务使用的，同时数据保证至少可以连接一台电脑。

## 输入格式

第一行包含两个整数 $n$ 和 $m$（$1 \le n,m \le 200000$），分别为电脑的数量和插座的数量。  
第二行包含 $n$ 个整数，$p_1,p_2,\ldots,p_n$（$1 \le p_i \le 10^9$），为电脑的电源。  
第三行包含 $m$ 个整数，$s_1,s_2,\ldots,s_m$（$1 \le s_i \le 10^9$），为插座的电源。

## 输出格式

第一行输出两个数字 $c$ 和 $u$，分别为最多可以连接的电脑数量与最少可以使用的适配器数量。  
第二行输出 $m$ 个数字，$a_1,a_2,\ldots,a_m$（$0 \le a_i \le 10^9$），为插在第 $i$ 个插座上的适配器数量。$a_i$ 的和应等于 $u$。  
第三行输出 $n$ 个数字，$b_1,b_2,\ldots,b_m$（$0 \le b_i \le m$），为第 $j$ 台电脑插入的插座序号。若 $b_j=0$，代表第 $j$ 台电脑不应插入任何插座。当 $b_j\ne 0$ 时，任何 $b_j$ 应不相等。在插入了 $a_{bj}$ 个适配器后，第 $j$ 台电脑的电源应与第 $b_j$ 个插座的电源相等。非 $0$ 的 $b_j$ 的数量应等于 $c$。  
如果有多组答案，请输出任意一组。

## 样例 #1

### 输入

```
2 2
1 1
2 2

```

### 输出

```
2 2
1 1
1 2

```

## 样例 #2

### 输入

```
2 1
2 100
99

```

### 输出

```
1 6
6
1 0

```



---

---
title: "Cartons of milk"
layout: "post"
diff: 提高+/省选-
pid: CF767D
tag: ['贪心', '枚举', '排序']
---

# Cartons of milk

## 题目描述

Olya likes milk very much. She drinks $ k $ cartons of milk each day if she has at least $ k $ and drinks all of them if she doesn't. But there's an issue — expiration dates. Each carton has a date after which you can't drink it (you still can drink it exactly at the date written on the carton). Due to this, if Olya's fridge contains a carton past its expiry date, she throws it away.

Olya hates throwing out cartons, so when she drinks a carton, she chooses the one which expires the fastest. It's easy to understand that this strategy minimizes the amount of cartons thrown out and lets her avoid it if it's even possible.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767D/609b94e7f0b8a5d407df0e97345c78713f56ad66.png)Milk. Best before: 20.02.2017.The main issue Olya has is the one of buying new cartons. Currently, there are $ n $ cartons of milk in Olya's fridge, for each one an expiration date is known (how soon does it expire, measured in days). In the shop that Olya visited there are $ m $ cartons, and the expiration date is known for each of those cartons as well.

Find the maximum number of cartons Olya can buy so that she wouldn't have to throw away any cartons. Assume that Olya drank no cartons today.

## 输入格式

In the first line there are three integers $ n $ , $ m $ , $ k $ ( $ 1<=n,m<=10^{6} $ , $ 1<=k<=n+m $ ) — the amount of cartons in Olya's fridge, the amount of cartons in the shop and the number of cartons Olya drinks each day.

In the second line there are $ n $ integers $ f_{1},f_{2},...,f_{n} $ ( $ 0<=f_{i}<=10^{7} $ ) — expiration dates of the cartons in Olya's fridge. The expiration date is expressed by the number of days the drinking of this carton can be delayed. For example, a $ 0 $ expiration date means it must be drunk today, $ 1 $ — no later than tomorrow, etc.

In the third line there are $ m $ integers $ s_{1},s_{2},...,s_{m} $ ( $ 0<=s_{i}<=10^{7} $ ) — expiration dates of the cartons in the shop in a similar format.

## 输出格式

If there's no way for Olya to drink the cartons she already has in her fridge, print -1.

Otherwise, in the first line print the maximum number $ x $ of cartons which Olya can buy so that she wouldn't have to throw a carton away. The next line should contain exactly $ x $ integers — the numbers of the cartons that should be bought (cartons are numbered in an order in which they are written in the input, starting with $ 1 $ ). Numbers should not repeat, but can be in arbitrary order. If there are multiple correct answers, print any of them.

## 说明/提示

In the first example $ k=2 $ and Olya has three cartons with expiry dates $ 0 $ , $ 1 $ and $ 1 $ (they expire today, tomorrow and tomorrow), and the shop has $ 3 $ cartons with expiry date $ 0 $ and $ 3 $ cartons with expiry date $ 2 $ . Olya can buy three cartons, for example, one with the expiry date $ 0 $ and two with expiry date $ 2 $ .

In the second example all three cartons Olya owns expire today and it means she would have to throw packets away regardless of whether she buys an extra one or not.

In the third example Olya would drink $ k=2 $ cartons today (one she alreay has in her fridge and one from the shop) and the remaining one tomorrow.

## 样例 #1

### 输入

```
3 6 2
1 0 1
2 0 2 0 0 2

```

### 输出

```
3
1 2 3
```

## 样例 #2

### 输入

```
3 1 2
0 0 0
1

```

### 输出

```
-1
```

## 样例 #3

### 输入

```
2 1 2
0 1
0

```

### 输出

```
1
1 
```



---

---
title: "Innokenty and a Football League"
layout: "post"
diff: 提高+/省选-
pid: CF780D
tag: ['字符串', '贪心', '构造']
---

# Innokenty and a Football League

## 题目描述

Innokenty is a president of a new football league in Byteland. The first task he should do is to assign short names to all clubs to be shown on TV next to the score. Of course, the short names should be distinct, and Innokenty wants that all short names consist of three letters.

Each club's full name consist of two words: the team's name and the hometown's name, for example, "DINAMO BYTECITY". Innokenty doesn't want to assign strange short names, so he wants to choose such short names for each club that:

1. the short name is the same as three first letters of the team's name, for example, for the mentioned club it is "DIN",
2. or, the first two letters of the short name should be the same as the first two letters of the team's name, while the third letter is the same as the first letter in the hometown's name. For the mentioned club it is "DIB".

Apart from this, there is a rule that if for some club $ x $ the second option of short name is chosen, then there should be no club, for which the first option is chosen which is the same as the first option for the club $ x $ . For example, if the above mentioned club has short name "DIB", then no club for which the first option is chosen can have short name equal to "DIN". However, it is possible that some club have short name "DIN", where "DI" are the first two letters of the team's name, and "N" is the first letter of hometown's name. Of course, no two teams can have the same short name.

Help Innokenty to choose a short name for each of the teams. If this is impossible, report that. If there are multiple answer, any of them will suit Innokenty. If for some team the two options of short name are equal, then Innokenty will formally think that only one of these options is chosen.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=1000 $ ) — the number of clubs in the league.

Each of the next $ n $ lines contains two words — the team's name and the hometown's name for some club. Both team's name and hometown's name consist of uppercase English letters and have length at least $ 3 $ and at most $ 20 $ .

## 输出格式

It it is not possible to choose short names and satisfy all constraints, print a single line "NO".

Otherwise, in the first line print "YES". Then print $ n $ lines, in each line print the chosen short name for the corresponding club. Print the clubs in the same order as they appeared in input.

If there are multiple answers, print any of them.

## 说明/提示

In the first sample Innokenty can choose first option for both clubs.

In the second example it is not possible to choose short names, because it is not possible that one club has first option, and the other has second option if the first options are equal for both clubs.

In the third example Innokenty can choose the second options for the first two clubs, and the first option for the third club.

In the fourth example note that it is possible that the chosen short name for some club $ x $ is the same as the first option of another club $ y $ if the first options of $ x $ and $ y $ are different.

## 样例 #1

### 输入

```
2
DINAMO BYTECITY
FOOTBALL MOSCOW

```

### 输出

```
YES
DIN
FOO

```

## 样例 #2

### 输入

```
2
DINAMO BYTECITY
DINAMO BITECITY

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
3
PLAYFOOTBALL MOSCOW
PLAYVOLLEYBALL SPB
GOGO TECHNOCUP

```

### 输出

```
YES
PLM
PLS
GOG

```

## 样例 #4

### 输入

```
3
ABC DEF
ABC EFG
ABD OOO

```

### 输出

```
YES
ABD
ABE
ABO

```



---

---
title: "Buy Low Sell High"
layout: "post"
diff: 提高+/省选-
pid: CF865D
tag: ['贪心', '优先队列', '队列']
---

# Buy Low Sell High

## 题目描述

你可以完美地预测某只股票接下来 $N$ 天的价格，你想利用这一知识盈利，但你每天只想买卖一股，这表明你每天要么什么都不干，要么买入一股，要么卖出一股。起初你没有股票，你也不能在没有股票时卖出股票。你希望在第 $N$ 天结束时不持有股票，并最大化盈利。

## 输入格式

第一行一个整数 $N$（$2 \le N \le 3 \times 10^5$），表示天数。

接下来一行 $N$ 个整数 $p_1,p_2,\dots p_N$（$1 \le p_i \le 10^6$），表示第 $i$ 天的股价。

## 输出格式

输出你第 $N$ 天结束时的最大盈利。

### 样例解释

在股价为 $5,4$ 时各买入一股，在股价为 $9,12$ 时各卖出一股，接着在股价为 $2$ 时买入一股，股价为 $10$ 时卖出一股，总收益为 $20$。

Translated by uid $408071$。

## 样例 #1

### 输入

```
9
10 5 4 7 9 12 6 2 10

```

### 输出

```
20

```

## 样例 #2

### 输入

```
20
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3 2 3 8 4

```

### 输出

```
41

```



---

---
title: "Too Easy Problems"
layout: "post"
diff: 提高+/省选-
pid: CF913D
tag: ['贪心', '排序', '优先队列']
---

# Too Easy Problems

## 题目描述

你正在准备一场关于调度理论的考试。

这场考试会持续正好 $T$ 毫秒，由 $n$ 道题目组成。

你可以用 $t_i$ 毫秒解决第 $i$ 个问题，或者忽略它并不消耗时间。你也不需要用来在做完一道题之后休息的时间。

不幸的是，你的老师认为一些题目对你来说太简单了。因此，他对于每道题 $i$ 规定了一个整数 $a_i$，表示题目 $i$ 只在你总共解决了不超过 $a_i$ 个问题（包括问题 $i$ ）的情况下为你的最终成绩加上一分。

正式地，假设你在考试中解决了问题 $p_1,p_2,\cdots,p_k$。那么，你的最终成绩 $s$ 会等于在 $1$ 到 $k$ 之间的满足 $k\le a_{p_j}$ 的 $j$ 的个数。

你已经意识到这场考试真正的第一道题目已经放在了你面前。因此，你想要选择一组题目来解决，从而最大化你的最终成绩。不要忘记这场考试有时间限制，而你必须有足够的时间来解决所有你选择的题目。如果存在多个最优解，任意输出一组即可。

## 输入格式

第一行包含 $2$ 个整数，$n$ 和 $T$，分别是考试中题目的数量和考试时长的毫秒数。

接下来的 $n$ 行每行包括两个整数 $a_i$ 和 $t_i$。题目编号从 $1$ 到 $n$。

## 输出格式

在第一行，输出一个单独的整数 $s$，表示你的可能得到的最终成绩的最大值。

在第二行，输出一个单独的整数 $k$ 表示你应该解决的问题数量。

在第三行，以任意顺序输出 $k$ 个不同整数 $p_1,p_2,\cdots,p_k$，即你应当解决的题目编号。

如果有多个最优解，你可以输出其中任意一个。

## 样例解释

在第一个样例中，你应该解决题目 $3$、$1$ 和 $4$。在这种解下你会花费 $80+100+90=270$ 毫秒，在考试的长度 $300$ms 以内（甚至给自己留出了 $30$ms 休息时间）。题目 $3$ 和题目 $1$ 会分别为你带来 $1$ 分，然而题目 $4$ 不会。你会得到 $2$ 分。

在第二个样例中，这场灾难性的考试的长度甚至不足以解决一道题目（所以你显然一分都得不到）。

在第三个样例中，你刚好有足够的时间 $(42+58=100)$ 来解决这两道题并且微笑着把答卷交给老师。

## 说明/提示

$1\le n\le 2\times10^5$

$1\le T\le10^9$

$0\le k\le n$

## 样例 #1

### 输入

```
5 300
3 100
4 150
4 80
2 90
2 300

```

### 输出

```
2
3
3 1 4

```

## 样例 #2

### 输入

```
2 100
1 787
2 788

```

### 输出

```
0
0


```

## 样例 #3

### 输入

```
2 100
2 42
2 58

```

### 输出

```
2
2
1 2

```



---

---
title: "Water Taps"
layout: "post"
diff: 提高+/省选-
pid: CF954E
tag: ['贪心', '排序']
---

# Water Taps

## 题目描述

Consider a system of $ n $ water taps all pouring water into the same container. The $ i $ -th water tap can be set to deliver any amount of water from $ 0 $ to $ a_{i} $ ml per second (this amount may be a real number). The water delivered by $ i $ -th tap has temperature $ t_{i} $ .

If for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/035d166bda223ecd5c31eb614a76bdcc9b8fe8c4.png) you set $ i $ -th tap to deliver exactly $ x_{i} $ ml of water per second, then the resulting temperature of water will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/4d0f711b0c4dc1450cd61a20f118d34a644e0d79.png) (if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/dbce41b29215315b290a54646261b5eaa9727507.png), then to avoid division by zero we state that the resulting water temperature is $ 0 $ ).

You have to set all the water taps in such a way that the resulting temperature is exactly $ T $ . What is the maximum amount of water you may get per second if its temperature has to be $ T $ ?

## 输入格式

The first line contains two integers $ n $ and $ T $ ( $ 1<=n<=200000 $ , $ 1<=T<=10^{6} $ ) — the number of water taps and the desired temperature of water, respectively.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{6} $ ) where $ a_{i} $ is the maximum amount of water $ i $ -th tap can deliver per second.

The third line contains $ n $ integers $ t_{1} $ , $ t_{2} $ , ..., $ t_{n} $ ( $ 1<=t_{i}<=10^{6} $ ) — the temperature of water each tap delivers.

## 输出格式

Print the maximum possible amount of water with temperature exactly $ T $ you can get per second (if it is impossible to obtain water with such temperature, then the answer is considered to be $ 0 $ ).

Your answer is considered correct if its absolute or relative error doesn't exceed $ 10^{-6} $ .

## 样例 #1

### 输入

```
2 100
3 10
50 150

```

### 输出

```
6.000000000000000

```

## 样例 #2

### 输入

```
3 9
5 5 30
6 6 10

```

### 输出

```
40.000000000000000

```

## 样例 #3

### 输入

```
2 12
1 3
10 15

```

### 输出

```
1.666666666666667

```



---

