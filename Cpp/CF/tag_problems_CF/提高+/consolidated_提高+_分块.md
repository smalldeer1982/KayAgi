---
title: "Tree Master"
layout: "post"
diff: 提高+/省选-
pid: CF1806E
tag: ['剪枝', '分块', '根号分治']
---

# Tree Master

## 题目描述

You are given a tree with $ n $ weighted vertices labeled from $ 1 $ to $ n $ rooted at vertex $ 1 $ . The parent of vertex $ i $ is $ p_i $ and the weight of vertex $ i $ is $ a_i $ . For convenience, define $ p_1=0 $ .

For two vertices $ x $ and $ y $ of the same depth $ ^\dagger $ , define $ f(x,y) $ as follows:

- Initialize $ \mathrm{ans}=0 $ .
- While both $ x $ and $ y $ are not $ 0 $ : 
  - $ \mathrm{ans}\leftarrow \mathrm{ans}+a_x\cdot a_y $ ;
  - $ x\leftarrow p_x $ ;
  - $ y\leftarrow p_y $ .
- $ f(x,y) $ is the value of $ \mathrm{ans} $ .

You will process $ q $ queries. In the $ i $ -th query, you are given two integers $ x_i $ and $ y_i $ and you need to calculate $ f(x_i,y_i) $ .

 $ ^\dagger $ The depth of vertex $ v $ is the number of edges on the unique simple path from the root of the tree to vertex $ v $ .

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2 \le n \le 10^5 $ ; $ 1 \le q \le 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^5 $ ).

The third line contains $ n-1 $ integers $ p_2, \ldots, p_n $ ( $ 1 \le p_i < i $ ).

Each of the next $ q $ lines contains two integers $ x_i $ and $ y_i $ ( $ 1\le x_i,y_i\le n $ ). It is guaranteed that $ x_i $ and $ y_i $ are of the same depth.

## 输出格式

Output $ q $ lines, the $ i $ -th line contains a single integer, the value of $ f(x_i,y_i) $ .

## 说明/提示

Consider the first example:

In the first query, the answer is $ a_4\cdot a_5+a_3\cdot a_3+a_2\cdot a_2+a_1\cdot a_1=3+4+25+1=33 $ .

In the second query, the answer is $ a_6\cdot a_6+a_2\cdot a_2+a_1\cdot a_1=1+25+1=27 $ .

## 样例 #1

### 输入

```
6 2
1 5 2 3 1 1
1 2 3 3 2
4 5
6 6
```

### 输出

```
33
27
```

## 样例 #2

### 输入

```
14 8
3 2 5 3 1 4 2 2 2 5 5 5 2 4
1 2 3 1 1 4 7 3 3 1 5 3 8
4 4
4 10
13 10
3 12
13 9
3 12
9 10
11 5
```

### 输出

```
47
53
48
36
42
36
48
14
```



---

---
title: "Mr. Kitayuta's Colorful Graph"
layout: "post"
diff: 提高+/省选-
pid: CF506D
tag: ['图论', '并查集', '分块']
---

# Mr. Kitayuta's Colorful Graph

## 题目描述

给出一个 $n$ 个点，$m$ 条边的无向图，每条边上是有颜色的。有 $q$ 组询问

对于第 $i$ 组询问，给出点对 $u_i,v_i$， 求有多少种颜色 $c$，满足存在至少一条从 $u_i$ 到 $v_i$ 的路径，使得该路径上的所有边的颜色均为 $c$。

## 输入格式

第一行两个整数 $n,m$ 分别表示点的个数和边的个数  
接下来 $m$ 行，每行三个整数 $x_i,y_i,c_i$，表示有一条连接点 $x_i,y_i$ 的边，且该边的颜色为 $c_i$

接下来一行一个整数 $q$，表示询问的个数

接下来 $q$ 行，每行两个整数 $u_i,v_i$，表示一组询问

## 输出格式

对于每一组询问，在单独的一行输出对应的答案

## 说明/提示

$2 \le n \le 10^5$  
$1 \le m,q \le 10^5$  
$1\le x_i,y_i,u_i,v_i \le n$  
$1 \le c_i \le m$

## 样例 #1

### 输入

```
4 5
1 2 1
1 2 2
2 3 1
2 3 3
2 4 3
3
1 2
3 4
1 4

```

### 输出

```
2
1
0

```

## 样例 #2

### 输入

```
5 7
1 5 1
2 5 1
3 5 1
4 5 1
1 2 2
2 3 2
3 4 2
5
1 5
5 1
2 5
1 5
1 4

```

### 输出

```
1
1
1
1
2

```



---

---
title: "Sum of Medians"
layout: "post"
diff: 提高+/省选-
pid: CF85D
tag: ['线段树', '枚举', '排序', '分块']
---

# Sum of Medians

## 题目描述

In one well-known algorithm of finding the $ k $ -th order statistics we should divide all elements into groups of five consecutive elements and find the median of each five. A median is called the middle element of a sorted array (it's the third largest element for a group of five). To increase the algorithm's performance speed on a modern video card, you should be able to find a sum of medians in each five of the array.

A sum of medians of a sorted $ k $ -element set $ S={a_{1},a_{2},...,a_{k}} $ , where $ a_{1}&lt;a_{2}&lt;a_{3}&lt;...&lt;a_{k} $ , will be understood by as

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/ade3397df6e8978ddadfc100b4ccb88beefd1e3f.png)The ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) operator stands for taking the remainder, that is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) stands for the remainder of dividing $ x $ by $ y $ .

To organize exercise testing quickly calculating the sum of medians for a changing set was needed.

## 输入格式

The first line contains number $ n $ ( $ 1<=n<=10^{5} $ ), the number of operations performed.

Then each of $ n $ lines contains the description of one of the three operations:

- add $ x $  — add the element $ x $ to the set;
- del $ x $  — delete the element $ x $ from the set;
- sum — find the sum of medians of the set.

For any add $ x $  operation it is true that the element $ x $ is not included in the set directly before the operation.

For any del $ x $  operation it is true that the element $ x $ is included in the set directly before the operation.

All the numbers in the input are positive integers, not exceeding $ 10^{9} $ .

## 输出格式

For each operation sum print on the single line the sum of medians of the current set. If the set is empty, print 0.

Please, do not use the %lld specificator to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams (also you may use the %I64d specificator).

## 样例 #1

### 输入

```
6
add 4
add 5
add 1
add 2
add 3
sum

```

### 输出

```
3

```

## 样例 #2

### 输入

```
14
add 1
add 7
add 2
add 5
sum
add 6
add 8
add 9
add 3
add 4
add 10
sum
del 1
sum

```

### 输出

```
5
11
13

```



---

---
title: "SUM and REPLACE"
layout: "post"
diff: 提高+/省选-
pid: CF920F
tag: ['线段树', '递归', '分块']
---

# SUM and REPLACE

## 题目描述

Let $ D(x) $ be the number of positive divisors of a positive integer $ x $ . For example, $ D(2)=2 $ ( $ 2 $ is divisible by $ 1 $ and $ 2 $ ), $ D(6)=4 $ ( $ 6 $ is divisible by $ 1 $ , $ 2 $ , $ 3 $ and $ 6 $ ).

You are given an array $ a $ of $ n $ integers. You have to process two types of queries:

1. REPLACE $ l $ $ r $ — for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920F/8c67e39bbb4a436ecb9bbf84b28c1b332f05ca94.png) replace $ a_{i} $ with $ D(a_{i}) $ ;
2. SUM $ l $ $ r $ — calculate ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920F/1deabb69ce88e0c9a5b8e5232e5782460ccfe87b.png).

Print the answer for each SUM query.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=3·10^{5} $ ) — the number of elements in the array and the number of queries to process, respectively.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{6} $ ) — the elements of the array.

Then $ m $ lines follow, each containing $ 3 $ integers $ t_{i} $ , $ l_{i} $ , $ r_{i} $ denoting $ i $ -th query. If $ t_{i}=1 $ , then $ i $ -th query is REPLACE $ l_{i} $ $ r_{i} $ , otherwise it's SUM $ l_{i} $ $ r_{i} $ ( $ 1<=t_{i}<=2 $ , $ 1<=l_{i}<=r_{i}<=n $ ).

There is at least one SUM query.

## 输出格式

For each SUM query print the answer to it.

## 样例 #1

### 输入

```
7 6
6 4 1 10 3 2 4
2 1 7
2 4 5
1 3 5
2 4 4
1 5 7
2 1 7

```

### 输出

```
30
13
4
22

```



---

