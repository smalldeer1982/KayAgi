---
title: "AND Segments"
layout: "post"
diff: 提高+/省选-
pid: CF1327F
tag: ['动态规划 DP', '差分']
---

# AND Segments

## 题目描述

你有三个整数 $n, k, m$ 以及 $m$ 个限制 $(l_1, r_1, x_1), (l_2, r_2, x_2), \ldots, (l_m, r_m, x_m)$。

计算满足下列条件的，长度为 $n$ 的序列 $a$ 的个数：

- 对于每个 $1 \le i \le n$，$0 \le a_i \lt 2 ^ k$。
- 对于每个 $1 \le i \le m$，数字的按位与 $a[l_i] \text{ and } a_[l_i + 1] \text{ and } \ldots \text{ and } a[r_i] = x_i$。

两个序列 $a, b$ 被认为是不同的，当且仅当存在一个位置 $i$ 满足 $a_i \neq b_i$。

由于答案可能过大，请输出其对 $998\ 244\ 353$ 取模的结果。

## 输入格式

第一行输入三个整数 $n, k, m ~(1 \le n \le 5 \cdot 10 ^ 5; 1 \le k \le 30; 0 \le m \le 5 \cdot 10 ^ 5)~$，分别表示数组 $a$ 的长度，$a$ 中元素的值域，以及限制的个数。

接下来 $m$ 行，每行描述一个限制 $l_i, r_i, x_i ~ (1 \le l_i \le r_i \le n; 0 \le x_i \lt 2 ^ k)$，分别表示限制的线段区间以及按位与值。

## 输出格式

输出一行一个整数，表示满足条件的序列 $a$ 的个数，对 $998\ 244\ 353$ 取模的结果。

## 说明/提示

你可以在 [这里](https://en.wikipedia.org/wiki/Bitwise_operation#AND) 获得有关按位与的信息。

在一个样例中，合法的序列 $a$ 有：$[3, 3, 7, 6]$，$[3, 7, 7, 6]$ 以及 $[7, 3, 7, 6]$。

## 样例 #1

### 输入

```
4 3 2
1 3 3
3 4 6
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 2 3
1 3 2
2 5 0
3 3 3
```

### 输出

```
33
```



---

---
title: "Shuffle"
layout: "post"
diff: 提高+/省选-
pid: CF1622D
tag: ['组合数学', '差分']
---

# Shuffle

## 题目描述

You are given a binary string (i. e. a string consisting of characters 0 and/or 1) $ s $ of length $ n $ . You can perform the following operation with the string $ s $ at most once: choose a substring (a contiguous subsequence) of $ s $ having exactly $ k $ characters 1 in it, and shuffle it (reorder the characters in the substring as you wish).

Calculate the number of different strings which can be obtained from $ s $ by performing this operation at most once.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2 \le n \le 5000 $ ; $ 0 \le k \le n $ ).

The second line contains the string $ s $ of length $ n $ , consisting of characters 0 and/or 1.

## 输出格式

Print one integer — the number of different strings which can be obtained from $ s $ by performing the described operation at most once. Since the answer can be large, output it modulo $ 998244353 $ .

## 说明/提示

Some strings you can obtain in the first example:

- to obtain 0110110, you can take the substring from the $ 1 $ -st character to the $ 4 $ -th character, which is 1100, and reorder its characters to get 0110;
- to obtain 1111000, you can take the substring from the $ 3 $ -rd character to the $ 7 $ -th character, which is 00110, and reorder its characters to get 11000;
- to obtain 1100101, you can take the substring from the $ 5 $ -th character to the $ 7 $ -th character, which is 110, and reorder its characters to get 101.

In the second example, $ k = 0 $ so you can only choose the substrings consisting only of 0 characters. Reordering them doesn't change the string at all, so the only string you can obtain is 10010.

## 样例 #1

### 输入

```
7 2
1100110
```

### 输出

```
16
```

## 样例 #2

### 输入

```
5 0
10010
```

### 输出

```
1
```

## 样例 #3

### 输入

```
8 1
10001000
```

### 输出

```
10
```

## 样例 #4

### 输入

```
10 8
0010011000
```

### 输出

```
1
```



---

---
title: "DFS Trees"
layout: "post"
diff: 提高+/省选-
pid: CF1707C
tag: ['生成树', '最近公共祖先 LCA', '差分']
---

# DFS Trees

## 题目描述

You are given a connected undirected graph consisting of $ n $ vertices and $ m $ edges. The weight of the $ i $ -th edge is $ i $ .

Here is a wrong algorithm of finding a [minimum spanning tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree) (MST) of a graph:

```
<pre class="verbatim"><br></br>vis := an array of length n<br></br>s := a set of edges<br></br><br></br>function dfs(u):<br></br>    vis[u] := true<br></br>    iterate through each edge (u, v) in the order from smallest to largest edge weight<br></br>        if vis[v] = false<br></br>            add edge (u, v) into the set (s)<br></br>            dfs(v)<br></br><br></br>function findMST(u):<br></br>    reset all elements of (vis) to false<br></br>    reset the edge set (s) to empty<br></br>    dfs(u)<br></br>    return the edge set (s)<br></br>
```

Each of the calls findMST(1), findMST(2), ..., findMST(n) gives you a spanning tree of the graph. Determine which of these trees are minimum spanning trees.

## 输入格式

The first line of the input contains two integers $ n $ , $ m $ ( $ 2\le n\le 10^5 $ , $ n-1\le m\le 2\cdot 10^5 $ ) — the number of vertices and the number of edges in the graph.

Each of the following $ m $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1\le u_i, v_i\le n $ , $ u_i\ne v_i $ ), describing an undirected edge $ (u_i,v_i) $ in the graph. The $ i $ -th edge in the input has weight $ i $ .

It is guaranteed that the graph is connected and there is at most one edge between any pair of vertices.

## 输出格式

You need to output a binary string $ s $ , where $ s_i=1 $ if findMST(i) creates an MST, and $ s_i = 0 $ otherwise.

## 说明/提示

Here is the graph given in the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1707C/6866eea697370f9ef4baf895c7023c2ffb357c36.png)There is only one minimum spanning tree in this graph. A minimum spanning tree is $ (1,2),(3,5),(1,3),(2,4) $ which has weight $ 1+2+3+5=11 $ .

Here is a part of the process of calling findMST(1):

- reset the array vis and the edge set s;
- calling dfs(1);
- vis\[1\] := true;
- iterate through each edge $ (1,2),(1,3) $ ;
- add edge $ (1,2) $ into the edge set s, calling dfs(2): 
  - vis\[2\] := true
  - iterate through each edge $ (2,1),(2,3),(2,4) $ ;
  - because vis\[1\] = true, ignore the edge $ (2,1) $ ;
  - add edge $ (2,3) $ into the edge set s, calling dfs(3): 
      - ...

In the end, it will select edges $ (1,2),(2,3),(3,5),(2,4) $ with total weight $ 1+4+2+5=12>11 $ , so findMST(1) does not find a minimum spanning tree.

It can be shown that the other trees are all MSTs, so the answer is 01111.

## 样例 #1

### 输入

```
5 5
1 2
3 5
1 3
3 2
4 2
```

### 输出

```
01111
```

## 样例 #2

### 输入

```
10 11
1 2
2 5
3 4
4 2
8 1
4 5
10 5
9 5
8 2
5 7
4 6
```

### 输出

```
0011111011
```



---

---
title: "Rain"
layout: "post"
diff: 提高+/省选-
pid: CF1710B
tag: ['二分', '差分']
---

# Rain

## 题目描述

You are the owner of a harvesting field which can be modeled as an infinite line, whose positions are identified by integers.

It will rain for the next $ n $ days. On the $ i $ -th day, the rain will be centered at position $ x_i $ and it will have intensity $ p_i $ . Due to these rains, some rainfall will accumulate; let $ a_j $ be the amount of rainfall accumulated at integer position $ j $ . Initially $ a_j $ is $ 0 $ , and it will increase by $ \max(0,p_i-|x_i-j|) $ after the $ i $ -th day's rain.

A flood will hit your field if, at any moment, there is a position $ j $ with accumulated rainfall $ a_j>m $ .

You can use a magical spell to erase exactly one day's rain, i.e., setting $ p_i=0 $ . For each $ i $ from $ 1 $ to $ n $ , check whether in case of erasing the $ i $ -th day's rain there is no flood.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ , $ 1 \leq m \leq 10^9 $ ) — the number of rainy days and the maximal accumulated rainfall with no flood occurring.

Then $ n $ lines follow. The $ i $ -th of these lines contains two integers $ x_i $ and $ p_i $ ( $ 1 \leq x_i,p_i \leq 10^9 $ ) — the position and intensity of the $ i $ -th day's rain.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a binary string $ s $ length of $ n $ . The $ i $ -th character of $ s $ is 1 if after erasing the $ i $ -th day's rain there is no flood, while it is 0, if after erasing the $ i $ -th day's rain the flood still happens.

## 说明/提示

In the first test case, if we do not use the spell, the accumulated rainfall distribution will be like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710B/40bd9aae46d3e796ba1ad418de0578aa41ab0c1c.png)If we erase the third day's rain, the flood is avoided and the accumulated rainfall distribution looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710B/d422db8867ffc7f0ea195742c50ffb3752e7d523.png)In the second test case, since initially the flood will not happen, we can erase any day's rain.

In the third test case, there is no way to avoid the flood.

## 样例 #1

### 输入

```
4
3 6
1 5
5 5
3 4
2 3
1 3
5 2
2 5
1 6
10 6
6 12
4 5
1 6
12 5
5 5
9 7
8 3
```

### 输出

```
001
11
00
100110
```



---

---
title: "Maximize the Largest Component (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1985H2
tag: ['深度优先搜索 DFS', '差分']
---

# Maximize the Largest Component (Hard Version)

## 题目描述

简单版本和困难版本实际上是不同的问题，因此请完整仔细地阅读两个问题的陈述。两个版本之间的唯一区别是操作。
Alex有一个由 $ n $ 行和 $ m $ 列组成的网格，由“.”和“#”字符组成。如果从该组中的任何单元格开始，通过仅移动到该组中共享一个共同边的另一个单元格，就可以到达该组中的任何其他单元格，则一组“#”单元格形成一个连通分量。连通分量的尺寸是该组中的单元格数量。
在一次操作中，Alex选择任意行$ r $（$ 1 \le r \le n $）和任意列$ c $（$ 1 \le c \le m $），然后将行$ r $和列$ c $中的每个单元格设置为“＃”。帮助Alex找到他在最多执行一次操作后，可以实现的“＃”个单元格的最大连通分量的最大可能大小。

## 输入格式

输入的第一行包含一个整数 $ t $（$ 1 \leq t \leq 10^4 $）——测试用例的数量。
每个测试用例的第一行包含两个整数$n$和$m$（$1 \le n \cdot m \le 10^6$）——网格的行数和列数。
接下来的 $n$ 行每行包含 $m$ 个字符。每个字符要么是 '.'或
保证所有测试用例中的 $ n \cdot m $ 的总和不超过 $ 10^6 $。

## 输出格式

对于每个测试用例，输出一个整数——Alex可以实现的“#”单元的连通分量的最大可能大小。

## 说明/提示

在第四个测试用例中，Alex将第4行和第2列的所有单元格设置为“#”是最优的。这样做将导致“#”的最大连通分量大小为16。
在第五个测试用例中，Alex将第2行和第4列的所有单元格设置为“#”是最优的。这样做将导致“#”的最大连通分量大小为22。

## 样例 #1

### 输入

```
6
1 1
.
4 2
..
#.
#.
.#
3 5
.#.#.
..#..
.#.#.
5 5
#...#
....#
#...#
.....
...##
6 6
.#..#.
#..#..
.#...#
#.#.#.
.#.##.
###..#
6 8
..#....#
.####.#.
###.#..#
.##.#.##
.#.##.##
#..##.#.
```

### 输出

```
1
7
11
16
22
36
```



---

---
title: "Fairy"
layout: "post"
diff: 提高+/省选-
pid: CF19E
tag: ['二分图', '最近公共祖先 LCA', '差分']
---

# Fairy

## 题目描述

Once upon a time there lived a good fairy A. One day a fine young man B came to her and asked to predict his future. The fairy looked into her magic ball and said that soon the fine young man will meet the most beautiful princess ever and will marry her. Then she drew on a sheet of paper $ n $ points and joined some of them with segments, each of the segments starts in some point and ends in some other point. Having drawn that picture, she asked the young man to erase one of the segments from the sheet. Then she tries to colour each point red or blue so, that there is no segment having points of the same colour as its ends. If she manages to do so, the prediction will come true. B wants to meet the most beautiful princess, that's why he asks you to help him. Find all the segments that will help him to meet the princess.

## 输入格式

The first input line contains two integer numbers: $ n $ — amount of the drawn points and $ m $ — amount of the drawn segments ( $ 1<=n<=10^{4},0<=m<=10^{4} $ ). The following $ m $ lines contain the descriptions of the segments. Each description contains two different space-separated integer numbers $ v $ , $ u $ ( $ 1<=v<=n,1<=u<=n $ ) — indexes of the points, joined by this segment. No segment is met in the description twice.

## 输出格式

In the first line output number $ k $ — amount of the segments in the answer. In the second line output $ k $ space-separated numbers — indexes of these segments in ascending order. Each index should be output only once. Segments are numbered from 1 in the input order.

## 样例 #1

### 输入

```
4 4
1 2
1 3
2 4
3 4

```

### 输出

```
4
1 2 3 4 
```

## 样例 #2

### 输入

```
4 5
1 2
2 3
3 4
4 1
1 3

```

### 输出

```
1
5 
```



---

---
title: "Balanced"
layout: "post"
diff: 提高+/省选-
pid: CF2032E
tag: ['差分']
---

# Balanced

## 题目描述

You are given a cyclic array $ a $ with $ n $ elements, where $ n $ is odd. In each operation, you can do the following:

- Choose an index $ 1 \le i \le n $ and increase $ a_{i - 1} $ by $ 1 $ , $ a_i $ by $ 2 $ , and $ a_{i + 1} $ by $ 1 $ . The element before the first element is the last element because this is a cyclic array.

A cyclic array is called balanced if all its elements are equal to each other.

Find any sequence of operations to make this cyclic array balanced or determine that it is impossible. Please note that you do not have to minimize the number of operations.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^5 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n < 2 \cdot 10^5 $ , $ n $ is odd) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^{6} $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case:

- If it is impossible to make the cyclic array balanced, output $ -1 $ .
- Otherwise, output $ n $ integers $ v_1, v_2, \ldots, v_n $ ( $ 0 \leq v_i \leq 10^{18} $ ) — where $ v_i $ denotes the number of operations applied to index $ i $ . It can be proved that if any solution exists, then there exists a solution under the given constraints. If there are several solutions under the given constraints, output any of them.

## 说明/提示

In the first test case:

- After $ 1 $ operation applied to index $ i = 2 $ , the array $ a = [3, 3, 3] $ .

In the second test case:

- After $ 2 $ operations applied to index $ i = 1 $ , the array $ a = [5, 4, 5] $ .
- After $ 1 $ operation applied to index $ i = 2 $ , the array $ a = [6, 6, 6] $ .

In the third test case:

- After $ 2 $ operations applied to index $ i = 1 $ , the array $ a = [5, 4, 1, 2, 3] $ .
- After $ 3 $ operations applied to index $ i = 3 $ , the array $ a = [5, 7, 7, 5, 3] $ .
- After $ 2 $ operations applied to index $ i = 5 $ , the array $ a = [7, 7, 7, 7, 7] $ .

## 样例 #1

### 输入

```
6
3
2 1 2
3
1 2 3
5
1 2 1 2 1
7
1 2 1 2 1 3 1
9
10000 10000 10000 10000 10000 10001 10002 10001 10000
1
10
```

### 输出

```
0 1 0 
2 1 0 
2 0 3 0 2 
4 2 7 0 8 0 6 
1 1 1 1 1 1 0 1 1 
0
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
title: "Alyona and a tree"
layout: "post"
diff: 提高+/省选-
pid: CF739B
tag: ['深度优先搜索 DFS', '前缀和', '差分']
---

# Alyona and a tree

## 题目描述

Alyona有一棵有 $n$ 个节点的树。这棵树的根节点是 $1$。在每个节点里，Alyona写了一个正整数，在节点 $i$ 她写了正整数 $a_i$ 。另外，她在这棵树上的每条边上写了一个正整数（不同边上可能有不同的数）。

让我们定义 $dist(v,u)$ 作为从 $v$ 到 $u$ 的简单路径上的边权和。

当且仅当 $u$ 在 $v$ 的子树中并且 $dist(v,u)\leq a_u$，顶点 $v$ 控制顶点 $u(v\neq u)$ 。

Alyona想在某些顶点定居。为了做到这件事，她想知道在每个节点 $v$ 能控制几个节点。

## 输入格式

第一行包含一个整数 $n (1\leq n\leq 2\times 10^5)$

第二行有 $n$ 个整数 $a_1,a_2,\ldots,a_n(1\leq a_i\leq 10^9)$ ,作为节点 $i$ 的数。

下面的 $n-1$ 行，每行有两个整数。第 $i$ 行包含整数 $p_i,w_i(1\leq p_i\leq n,1\leq w_i\leq 10^9)$ ,分别为节点 $i+1$ 的在树上的父节点和 $p_i$ 和 $(i+1)$ 的边上的数字。

数据保证是个树。

## 输出格式

输出 $n$ 个整数，第 $i$ 个数为节点 $i$ 能控制的点数。

## 说明/提示

在样例中，节点 $1$ 控制了节点 $3$ ，节点 $3$ 控制节点 $5$ （注意，这并不代表节点 $1$ 控制了节点 $5$ ）

Translated by @lolte

## 样例 #1

### 输入

```
5
2 5 1 4 6
1 7
1 1
3 5
3 6

```

### 输出

```
1 0 1 0 0

```

## 样例 #2

### 输入

```
5
9 7 8 6 5
1 1
2 1
3 1
4 1

```

### 输出

```
4 3 2 1 0

```



---

---
title: "The Untended Antiquity"
layout: "post"
diff: 提高+/省选-
pid: CF869E
tag: ['树状数组', '进制', '差分']
---

# The Untended Antiquity

## 题目描述

Adieu l'ami.

Koyomi is helping Oshino, an acquaintance of his, to take care of an open space around the abandoned Eikou Cram School building, Oshino's makeshift residence.

The space is represented by a rectangular grid of $ n×m $ cells, arranged into $ n $ rows and $ m $ columns. The $ c $ -th cell in the $ r $ -th row is denoted by $ (r,c) $ .

Oshino places and removes barriers around rectangular areas of cells. Specifically, an action denoted by " $ 1\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means Oshino's placing barriers around a rectangle with two corners being $ (r_{1},c_{1}) $ and $ (r_{2},c_{2}) $ and sides parallel to squares sides. Similarly, " $ 2\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means Oshino's removing barriers around the rectangle. Oshino ensures that no barriers staying on the ground share any common points, nor do they intersect with boundaries of the $ n×m $ area.

Sometimes Koyomi tries to walk from one cell to another carefully without striding over barriers, in order to avoid damaging various items on the ground. " $ 3\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means that Koyomi tries to walk from $ (r_{1},c_{1}) $ to $ (r_{2},c_{2}) $ without crossing barriers.

And you're here to tell Koyomi the feasibility of each of his attempts.

## 输入格式

The first line of input contains three space-separated integers $ n $ , $ m $ and $ q $ ( $ 1<=n,m<=2500 $ , $ 1<=q<=100000 $ ) — the number of rows and columns in the grid, and the total number of Oshino and Koyomi's actions, respectively.

The following $ q $ lines each describes an action, containing five space-separated integers $ t $ , $ r_{1} $ , $ c_{1} $ , $ r_{2} $ , $ c_{2} $ ( $ 1<=t<=3 $ , $ 1<=r_{1},r_{2}<=n $ , $ 1<=c_{1},c_{2}<=m $ ) — the type and two coordinates of an action. Additionally, the following holds depending on the value of $ t $ :

- If $ t=1 $ : $ 2<=r_{1}<=r_{2}<=n-1 $ , $ 2<=c_{1}<=c_{2}<=m-1 $ ;
- If $ t=2 $ : $ 2<=r_{1}<=r_{2}<=n-1 $ , $ 2<=c_{1}<=c_{2}<=m-1 $ , the specified group of barriers exist on the ground before the removal.
- If $ t=3 $ : no extra restrictions.

## 输出格式

For each of Koyomi's attempts (actions with $ t=3 $ ), output one line — containing "Yes" (without quotes) if it's feasible, and "No" (without quotes) otherwise.

## 说明/提示

For the first example, the situations of Koyomi's actions are illustrated below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869E/5930e5689d91726564d05581955bbc9acf5a8c98.png)

## 样例 #1

### 输入

```
5 6 5
1 2 2 4 5
1 3 3 3 3
3 4 4 1 1
2 2 2 4 5
3 1 1 4 4

```

### 输出

```
No
Yes

```

## 样例 #2

### 输入

```
2500 2500 8
1 549 1279 1263 2189
1 303 795 1888 2432
1 2227 622 2418 1161
3 771 2492 1335 1433
1 2017 2100 2408 2160
3 48 60 798 729
1 347 708 1868 792
3 1940 2080 377 1546

```

### 输出

```
No
Yes
No

```



---

