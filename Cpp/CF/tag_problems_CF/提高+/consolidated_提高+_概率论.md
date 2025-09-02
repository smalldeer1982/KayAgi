---
title: "Xor-Paths"
layout: "post"
diff: 提高+/省选-
pid: CF1006F
tag: ['搜索', '概率论']
---

# Xor-Paths

## 题目描述

There is a rectangular grid of size $ n \times m $ . Each cell has a number written on it; the number on the cell ( $ i, j $ ) is $ a_{i, j} $ . Your task is to calculate the number of paths from the upper-left cell ( $ 1, 1 $ ) to the bottom-right cell ( $ n, m $ ) meeting the following constraints:

- You can move to the right or to the bottom only. Formally, from the cell ( $ i, j $ ) you may move to the cell ( $ i, j + 1 $ ) or to the cell ( $ i + 1, j $ ). The target cell can't be outside of the grid.
- The xor of all the numbers on the path from the cell ( $ 1, 1 $ ) to the cell ( $ n, m $ ) must be equal to $ k $ (xor operation is the bitwise exclusive OR, it is represented as '^' in Java or C++ and "xor" in Pascal).

Find the number of such paths in the given grid.

## 输入格式

The first line of the input contains three integers $ n $ , $ m $ and $ k $ ( $ 1 \le n, m \le 20 $ , $ 0 \le k \le 10^{18} $ ) — the height and the width of the grid, and the number $ k $ .

The next $ n $ lines contain $ m $ integers each, the $ j $ -th element in the $ i $ -th line is $ a_{i, j} $ ( $ 0 \le a_{i, j} \le 10^{18} $ ).

## 输出格式

Print one integer — the number of paths from ( $ 1, 1 $ ) to ( $ n, m $ ) with xor sum equal to $ k $ .

## 说明/提示

All the paths from the first example:

- $ (1, 1) \rightarrow (2, 1) \rightarrow (3, 1) \rightarrow (3, 2) \rightarrow (3, 3) $ ;
- $ (1, 1) \rightarrow (2, 1) \rightarrow (2, 2) \rightarrow (2, 3) \rightarrow (3, 3) $ ;
- $ (1, 1) \rightarrow (1, 2) \rightarrow (2, 2) \rightarrow (3, 2) \rightarrow (3, 3) $ .

All the paths from the second example:

- $ (1, 1) \rightarrow (2, 1) \rightarrow (3, 1) \rightarrow (3, 2) \rightarrow (3, 3) \rightarrow (3, 4) $ ;
- $ (1, 1) \rightarrow (2, 1) \rightarrow (2, 2) \rightarrow (3, 2) \rightarrow (3, 3) \rightarrow (3, 4) $ ;
- $ (1, 1) \rightarrow (2, 1) \rightarrow (2, 2) \rightarrow (2, 3) \rightarrow (2, 4) \rightarrow (3, 4) $ ;
- $ (1, 1) \rightarrow (1, 2) \rightarrow (2, 2) \rightarrow (2, 3) \rightarrow (3, 3) \rightarrow (3, 4) $ ;
- $ (1, 1) \rightarrow (1, 2) \rightarrow (1, 3) \rightarrow (2, 3) \rightarrow (3, 3) \rightarrow (3, 4) $ .

## 样例 #1

### 输入

```
3 3 11
2 1 5
7 10 0
12 6 4

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 4 2
1 3 3 3
0 3 3 2
3 0 1 1

```

### 输出

```
5

```

## 样例 #3

### 输入

```
3 4 1000000000000000000
1 3 3 3
0 3 3 2
3 0 1 1

```

### 输出

```
0

```



---

---
title: "Chemical table"
layout: "post"
diff: 提高+/省选-
pid: CF1012B
tag: ['并查集', '概率论', '构造']
---

# Chemical table

## 题目描述

Innopolis University scientists continue to investigate the periodic table. There are $ n·m $ known elements and they form a periodic table: a rectangle with $ n $ rows and $ m $ columns. Each element can be described by its coordinates $ (r,c) $ ( $ 1<=r<=n $ , $ 1<=c<=m $ ) in the table.

Recently scientists discovered that for every four different elements in this table that form a rectangle with sides parallel to the sides of the table, if they have samples of three of the four elements, they can produce a sample of the fourth element using nuclear fusion. So if we have elements in positions $ (r_{1},c_{1}) $ , $ (r_{1},c_{2}) $ , $ (r_{2},c_{1}) $ , where $ r_{1}≠r_{2} $ and $ c_{1}≠c_{2} $ , then we can produce element $ (r_{2},c_{2}) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/a1ec2b34980f17dea8ef9d5c32f5d591ae712bba.png)Samples used in fusion are not wasted and can be used again in future fusions. Newly crafted elements also can be used in future fusions.

Innopolis University scientists already have samples of $ q $ elements. They want to obtain samples of all $ n·m $ elements. To achieve that, they will purchase some samples from other laboratories and then produce all remaining elements using an arbitrary number of nuclear fusions in some order. Help them to find the minimal number of elements they need to purchase.

## 输入格式

The first line contains three integers $ n $ , $ m $ , $ q $ ( $ 1<=n,m<=200000 $ ; $ 0<=q<=min(n·m,200000) $ ), the chemical table dimensions and the number of elements scientists already have.

The following $ q $ lines contain two integers $ r_{i} $ , $ c_{i} $ ( $ 1<=r_{i}<=n $ , $ 1<=c_{i}<=m $ ), each describes an element that scientists already have. All elements in the input are different.

## 输出格式

Print the minimal number of elements to be purchased.

## 说明/提示

For each example you have a picture which illustrates it.

The first picture for each example describes the initial set of element samples available. Black crosses represent elements available in the lab initially.

The second picture describes how remaining samples can be obtained. Red dashed circles denote elements that should be purchased from other labs (the optimal solution should minimize the number of red circles). Blue dashed circles are elements that can be produced with nuclear fusion. They are numbered in order in which they can be produced.

Test 1

We can use nuclear fusion and get the element from three other samples, so we don't need to purchase anything.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/d0188b7b484eed4ec50dd63bc64a04ce06b65611.png)Test 2

We cannot use any nuclear fusion at all as there is only one row, so we have to purchase all missing elements.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/ba8b5c94cc17a4604dd0e58fb6a66f6e2487526e.png)Test 3

There are several possible solutions. One of them is illustrated below.

Note that after purchasing one element marked as red it's still not possible to immidiately produce the middle element in the bottom row (marked as 4). So we produce the element in the left-top corner first (marked as 1), and then use it in future fusions.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/5273513fe4bf0485a76591391c8b08a7edf8e9af.png)

## 样例 #1

### 输入

```
2 2 3
1 2
2 2
2 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
1 5 3
1 3
1 1
1 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
4 3 6
1 2
1 3
2 2
2 3
3 1
3 3

```

### 输出

```
1

```



---

---
title: "Mouse Hunt"
layout: "post"
diff: 提高+/省选-
pid: CF1027D
tag: ['模拟', '强连通分量', '概率论']
---

# Mouse Hunt

## 题目描述

伯兰州立大学的医学部刚刚结束了招生活动。和以往一样，约80%的申请人都是女生并且她们中的大多数人将在未来4年（真希望如此）住在大学宿舍里。

宿舍楼里有$n$个房间和**一只老鼠**！女孩们决定在一些房间里设置捕鼠器来除掉这只可怕的怪物。在$i$号房间设置陷阱要花费$c_i$伯兰币。房间编号从$1$到$n$。

要知道老鼠不是一直原地不动的，它不停地跑来跑去。如果$t$秒时它在$i$号房间，那么它将在$t+1$秒时跑到$a_i$号房间，但这期间不会跑到别的任何房间里($i=a_i$表示老鼠没有离开原来的房间)。时间从$0$秒开始，一旦老鼠窜到了有捕鼠器的房间里，这只老鼠就会被抓住。

如果女孩们知道老鼠一开始在哪里不就很容易吗？不幸的是，情况不是这样，老鼠在第$0$秒时可能会在从$1$到$n$的任何一个房间内。

那么女孩们最少要花多少钱设置捕鼠器，才能保证老鼠无论从哪个房间开始流窜最终都会被抓到？

## 输入格式

第1行一个整数n($1\le n \le 2*10^5$)，表示宿舍楼里的房间数。

第2行有$n$个整数，$c_1, c_2, \dots, c_n(1\le c_i \le 10^4)$，$c_i$表示在$i$号房间设置捕鼠器的花费。

第3行有$n$个整数，$a_1, a_2, \dots, a_n(1\le a_i \le n)$，$a_i$是老鼠在$i$号房间时，下一秒会窜到的房间号。

## 输出格式

输出一个整数，表示设置捕鼠器的最小花费（保证无论老鼠一开始在什么位置最终都能被抓住！）。

## 样例 #1

### 输入

```
5
1 2 3 2 10
1 3 4 3 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
1 10 2 10
2 4 2 2

```

### 输出

```
10

```

## 样例 #3

### 输入

```
7
1 1 1 1 1 1 1
2 2 2 3 6 7 6

```

### 输出

```
2

```



---

---
title: "Enlarge GCD"
layout: "post"
diff: 提高+/省选-
pid: CF1034A
tag: ['枚举', '素数判断,质数,筛法', '概率论']
---

# Enlarge GCD

## 题目描述

Mr. F has $ n $ positive integers, $ a_1, a_2, \ldots, a_n $ .

He thinks the greatest common divisor of these integers is too small. So he wants to enlarge it by removing some of the integers.

But this problem is too simple for him, so he does not want to do it by himself. If you help him, he will give you some scores in reward.

Your task is to calculate the minimum number of integers you need to remove so that the greatest common divisor of the remaining integers is bigger than that of all integers.

## 输入格式

The first line contains an integer $ n $ ( $ 2 \leq n \leq 3 \cdot 10^5 $ ) — the number of integers Mr. F has.

The second line contains $ n $ integers, $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 1.5 \cdot 10^7 $ ).

## 输出格式

Print an integer — the minimum number of integers you need to remove so that the greatest common divisor of the remaining integers is bigger than that of all integers.

You should not remove all of the integers.

If there is no solution, print «-1» (without quotes).

## 说明/提示

In the first example, the greatest common divisor is $ 1 $ in the beginning. You can remove $ 1 $ so that the greatest common divisor is enlarged to $ 2 $ . The answer is $ 1 $ .

In the second example, the greatest common divisor is $ 3 $ in the beginning. You can remove $ 6 $ and $ 9 $ so that the greatest common divisor is enlarged to $ 15 $ . There is no solution which removes only one integer. So the answer is $ 2 $ .

In the third example, there is no solution to enlarge the greatest common divisor. So the answer is $ -1 $ .

## 样例 #1

### 输入

```
3
1 2 4

```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
6 9 15 30

```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
1 1 1

```

### 输出

```
-1
```



---

---
title: "Sergey and Subway"
layout: "post"
diff: 提高+/省选-
pid: CF1060E
tag: ['分治', '深度优先搜索 DFS', '概率论']
---

# Sergey and Subway

## 题目描述

Sergey Semyonovich is a mayor of a county city N and he used to spend his days and nights in thoughts of further improvements of Nkers' lives. Unfortunately for him, anything and everything has been done already, and there are no more possible improvements he can think of during the day (he now prefers to sleep at night). However, his assistants have found a solution and they now draw an imaginary city on a paper sheet and suggest the mayor can propose its improvements.

Right now he has a map of some imaginary city with $ n $ subway stations. Some stations are directly connected with tunnels in such a way that the whole map is a tree (assistants were short on time and enthusiasm). It means that there exists exactly one simple path between each pair of station. We call a path simple if it uses each tunnel no more than once.

One of Sergey Semyonovich's favorite quality objectives is the sum of all pairwise distances between every pair of stations. The distance between two stations is the minimum possible number of tunnels on a path between them.

Sergey Semyonovich decided to add new tunnels to the subway map. In particular, he connected any two stations $ u $ and $ v $ that were not connected with a direct tunnel but share a common neighbor, i.e. there exists such a station $ w $ that the original map has a tunnel between $ u $ and $ w $ and a tunnel between $ w $ and $ v $ . You are given a task to compute the sum of pairwise distances between all pairs of stations in the new map.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2 \leq n \leq 200\,000 $ ) — the number of subway stations in the imaginary city drawn by mayor's assistants. Each of the following $ n - 1 $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ , $ u_i \ne v_i $ ), meaning the station with these indices are connected with a direct tunnel.

It is guaranteed that these $ n $ stations and $ n - 1 $ tunnels form a tree.

## 输出格式

Print one integer that is equal to the sum of distances between all pairs of stations after Sergey Semyonovich draws new tunnels between all pairs of stations that share a common neighbor in the original map.

## 说明/提示

In the first sample, in the new map all pairs of stations share a direct connection, so the sum of distances is $ 6 $ .

In the second sample, the new map has a direct tunnel between all pairs of stations except for the pair $ (1, 4) $ . For these two stations the distance is $ 2 $ .

## 样例 #1

### 输入

```
4
1 2
1 3
1 4

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4

```

### 输出

```
7

```



---

---
title: "Tree Array"
layout: "post"
diff: 提高+/省选-
pid: CF1540B
tag: ['树形 DP', '组合数学', '概率论']
---

# Tree Array

## 题目描述

You are given a tree consisting of $ n $ nodes. You generate an array from the tree by marking nodes one by one.

Initially, when no nodes are marked, a node is equiprobably chosen and marked from the entire tree.

After that, until all nodes are marked, a node is equiprobably chosen and marked from the set of unmarked nodes with at least one edge to a marked node.

It can be shown that the process marks all nodes in the tree.

The final array $ a $ is the list of the nodes' labels in order of the time each node was marked.

Find the expected number of inversions in the array that is generated by the tree and the aforementioned process.

The number of inversions in an array $ a $ is the number of pairs of indices $ (i, j) $ such that $ i < j $ and $ a_i > a_j $ . For example, the array $ [4, 1, 3, 2] $ contains $ 4 $ inversions: $ (1, 2) $ , $ (1, 3) $ , $ (1, 4) $ , $ (3, 4) $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 200 $ ) — the number of nodes in the tree.

The next $ n - 1 $ lines each contains two integers $ x $ and $ y $ ( $ 1 \le x, y \le n $ ; $ x \neq y $ ), denoting an edge between node $ x $ and $ y $ .

It's guaranteed that the given edges form a tree.

## 输出格式

Output the expected number of inversions in the generated array modulo $ 10^9+7 $ .

Formally, let $ M = 10^9+7 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

This is the tree from the first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1540B/3833e6cdc8f432e8774aa8c02d9352118566a812.png)For the first sample, the arrays are almost fixed. If node $ 2 $ is chosen initially, then the only possible array is $ [2, 1, 3] $ ( $ 1 $ inversion). If node $ 3 $ is chosen initially, then the only possible array is $ [3, 1, 2] $ ( $ 2 $ inversions). If node $ 1 $ is chosen initially, the arrays $ [1, 2, 3] $ ( $ 0 $ inversions) and $ [1, 3, 2] $ ( $ 1 $ inversion) are the only possibilities and equiprobable. In total, the expected number of inversions is $ \frac{1}{3}\cdot 1 + \frac{1}{3} \cdot 2 + \frac{1}{3} \cdot (\frac{1}{2} \cdot 0 + \frac{1}{2} \cdot 1) = \frac{7}{6} $ .

 $ 166666669 \cdot 6 = 7 \pmod {10^9 + 7} $ , so the answer is $ 166666669 $ .

This is the tree from the second sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1540B/7f613b365926417ec34142a093ccc13b3b572f4f.png)This is the tree from the third sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1540B/4cf8ac5fc765cc7cdc6657a332a13e66dcba8fef.png)

## 样例 #1

### 输入

```
3
1 2
1 3
```

### 输出

```
166666669
```

## 样例 #2

### 输入

```
6
2 1
2 3
6 1
1 4
2 5
```

### 输出

```
500000009
```

## 样例 #3

### 输入

```
5
1 2
1 3
1 4
2 5
```

### 输出

```
500000007
```



---

---
title: "Wish I Knew How to Sort"
layout: "post"
diff: 提高+/省选-
pid: CF1753C
tag: ['动态规划 DP', '组合数学', '概率论']
---

# Wish I Knew How to Sort

## 题目描述

You are given a binary array $ a $ (all elements of the array are $ 0 $ or $ 1 $ ) of length $ n $ . You wish to sort this array, but unfortunately, your algorithms teacher forgot to teach you sorting algorithms. You perform the following operations until $ a $ is sorted:

1. Choose two random indices $ i $ and $ j $ such that $ i < j $ . Indices are chosen equally probable among all pairs of indices $ (i, j) $ such that $ 1 \le i < j \le n $ .
2. If $ a_i > a_j $ , then swap elements $ a_i $ and $ a_j $ .

What is the [expected number](https://en.wikipedia.org/wiki/Expected_value) of such operations you will perform before the array becomes sorted?

It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{998\,244\,353} $ . Output the integer equal to $ p \cdot q^{-1} \bmod 998\,244\,353 $ . In other words, output such an integer $ x $ that $ 0 \le x < 998\,244\,353 $ and $ x \cdot q \equiv p \pmod{998\,244\,353} $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). Description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 200\,000 $ ) — the number of elements in the binary array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ a_i \in \{0, 1\} $ ) — elements of the array.

It's guaranteed that sum of $ n $ over all test cases does not exceed $ 200\,000 $ .

## 输出格式

For each test case print one integer — the value $ p \cdot q^{-1} \bmod 998\,244\,353 $ .

## 说明/提示

Consider the first test case. If the pair of indices $ (2, 3) $ will be chosen, these elements will be swapped and array will become sorted. Otherwise, if one of pairs $ (1, 2) $ or $ (1, 3) $ will be selected, nothing will happen. So, the probability that the array will become sorted after one operation is $ \frac{1}{3} $ , the probability that the array will become sorted after two operations is $ \frac{2}{3} \cdot \frac{1}{3} $ , the probability that the array will become sorted after three operations is $ \frac{2}{3} \cdot \frac{2}{3} \cdot \frac{1}{3} $ and so on. The expected number of operations is $ \sum \limits_{i=1}^{\infty} \left(\frac{2}{3} \right)^{i - 1} \cdot \frac{1}{3} \cdot i = 3 $ .

In the second test case the array is already sorted so the expected number of operations is zero.

In the third test case the expected number of operations equals to $ \frac{75}{4} $ so the answer is $ 75 \cdot 4^{-1} \equiv 249\,561\,107 \pmod {998\,244\,353} $ .

## 样例 #1

### 输入

```
3
3
0 1 0
5
0 0 1 1 1
6
1 1 1 0 0 1
```

### 输出

```
3
0
249561107
```



---

---
title: "Alice's Adventures in the Rabbit Hole"
layout: "post"
diff: 提高+/省选-
pid: CF2028E
tag: ['数学', '树形 DP', '概率论']
---

# Alice's Adventures in the Rabbit Hole

## 题目描述

爱丽丝在兔子洞的底部！兔子洞可以建模为一棵树 $^{\text{∗}}$  ，在顶点 $1$ 有一个出口，而爱丽丝从某个顶点 $v$ 开始。她想要逃出这个洞，但不幸的是，红心女王下令处决她。

每分钟都会抛一次公平的硬币。如果硬币正面朝上，爱丽丝可以移动到她当前位置的一个相邻顶点，否则，红心女王可以将爱丽丝拉到女王选择的一个相邻顶点。如果爱丽丝最终出现在树的任何非根叶子 $^{\text{†}}$ 上，爱丽丝就输了。

假设他们都以最佳方式移动，计算爱丽丝从每个起始顶点 $1\le v\le n$ 成功逃脱的概率。由于这些概率可能非常小，因此输出它们对 $998\,244\,353$ 的取模。

形式上，设 $M = 998\,244\,353$ 。可以证明，确切的答案可以表示为一个不可约分的分数 $\frac{p}{q}$ ，其中 $p$ 和 $q$ 是整数且 $q \not \equiv 0 \pmod{M}$。输出等于 $p \cdot q^{-1} \bmod M$ 的整数。换句话说，输出这样一个整数 $x$，使得 $0 \le x < M$ 和 $x \cdot q \equiv p \pmod{M}$ 

---
$^{\text{∗}}$
 一棵树是一个连通的简单图，具有 $n$ 个顶点和 $n-1$ 条边。

$^{\text{†}} $
 一个叶子是一个仅与一条边相连的顶点。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。测试用例的描述如下。

每个测试用例的第一行包含一个整数 $n$（$2\le n\le 2\cdot 10^5$）——树中的顶点数量。

接下来的 $i$ 行中的第 $n - 1$ 行包含两个整数 $x_i$ 和 $y_i$ （$1 \le x_i, y_i \le n$ 和 $x_i \neq y_i$）——树的边。可以保证给定的边形成一棵树。

可以保证所有测试用例的 $n$ 之和不超过 $2\cdot 10^5$ 。

## 输出格式

对于每个测试用例，输出 $n$ 个整数在一行上——爱丽丝从顶点 $1, 2, \ldots, n$ 开始逃脱的概率。由于这些概率可能非常小，因此输出它们对$998\,244\,353$ 的取模。

## 说明/提示

对于第一个测试用例：

1.根据定义，爱丽丝从根节点（顶点 $1$）逃脱的概率为 $1$。\
2.爱丽丝从顶点 $4$ 和 $5$ 立即输掉，因为它们是叶子。\
3.从另外两个顶点，爱丽丝以概率 $\frac 12$ 逃脱，因为女王会将她拉到叶子。

## 样例 #1

### 输入

```
2
5
1 2
1 3
2 4
3 5
9
1 2
2 3
4 5
5 6
7 8
8 9
2 4
5 7
```

### 输出

```
1 499122177 499122177 0 0 
1 499122177 0 332748118 166374059 0 443664157 720954255 0
```



---

---
title: "Control of Randomness"
layout: "post"
diff: 提高+/省选-
pid: CF2040E
tag: ['树形 DP', '概率论']
---

# Control of Randomness

## 题目描述

给定一棵树，树上有 $ n $ 个顶点。

我们在某个顶点 $ v \ne 1 $ 放置一个机器人，最初拥有 $ p $ 枚硬币。以下是机器人的移动规则：

- 当 $ i $ 为奇数时，机器人会向顶点 $ 1 $ 的方向移动到相邻的节点。
- 当 $ i $ 为偶数时，如果你愿意支付一枚硬币并且还有剩余的硬币，则机器人会向顶点 $ 1 $ 的方向移动到相邻的节点；否则，机器人将随机选择一个相邻的节点移动。

当机器人到达顶点 $ 1 $ 时，过程终止。记 $ f(v, p) $ 为通过最佳策略使用硬币时，使得上述过程的期望步数最小值。

你的任务是解决 $ q $ 个查询。每个查询包含一对 $(v_i, p_i)$，你需要计算 $ f(v_i, p_i) $ 模 $ 998\,244\,353 $ 的值。

具体来说，令 $ M = 998\,244\,353 $。结果可以表示为一个不可约分数 $ \frac{p}{q} $，其中 $ p $ 和 $ q $ 是整数且 $ q \not\equiv 0 \pmod{M} $。你需要输出 $ p \cdot q^{-1} \bmod M $。换句话说，输出满足 $ 0 \le x < M $ 且 $ x \cdot q \equiv p \pmod{M} $ 的整数 $ x $。

## 输入格式

输入包含多个测试用例。第一行为测试用例的数量 $ t $ （$ 1 \le t \le 10^3 $）。

对于每个测试用例，第一行包含两个整数 $ n $ 和 $ q $（$ 2 \le n \le 2000 $，$ 1 \le q \le 2000 $），分别表示树的顶点数和查询数量。

接下来的 $ n - 1 $ 行每行描述一条树的边，包含两个整数 $ u_i $ 和 $ v_i $ （$ 1 \le u_i, v_i \le n $，$ u_i \neq v_i $），表示节点 $ u_i $ 和 $ v_i $ 之间有一条边。

接下来的 $ q $ 行中每行包含两个整数 $ v_i $ 和 $ p_i $（$ 2 \le v_i \le n $，$ 0 \le p_i \le n $），表示每个查询的节点和初始硬币数。

保证输入的边构成一棵树，并且所有测试用例的 $ n $ 之和不超过 $ 2000 $，$ q $ 之和不超过 $ 2000 $。

## 输出格式

对于每个测试用例，输出 $ q $ 个整数，表示每个查询 $ f(v_i, p_i) $ 模 $ 998\,244\,353 $ 的结果。

形式上，令 $ M = 998\,244\,353 $。可以证明答案可以表示为不可约分数 $ \frac{p}{q} $，其中 $ p $ 和 $ q $ 是整数且 $ q \not\equiv 0 \pmod{M} $。输出满足 $ 0 \le x < M $ 且 $ x \cdot q \equiv p \pmod{M} $ 的整数 $ x $。

## 说明/提示

在第一个测试用例中，树的结构如下：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040E/6e37a094615504d3867ace023f49408cee6e1144.png)

第一个查询中，期望值为 $ 1 $，因为机器人从顶点 $ 2 $ 出发，一步就到达了顶点 $ 1 $，过程结束。

第二个查询中的期望步数计算如下（$ x $ 为步数）：

- $ P(x < 2) = 0 $，因为距离顶点 $ 1 $ 是 $ 2 $，机器人无法在更少的步数内到达。
- $ P(x = 2) = \frac{1}{3} $，因为只有一种步骤序列使 $ x = 2 $。即 $ 3 \rightarrow_{1} 2 \rightarrow_{0.33} 1 $，概率为 $ 1 \cdot \frac{1}{3} $。
- $ P(x \bmod 2 = 1) = 0 $，因为机器人只能通过偶数步数到达顶点 $ 1 $。
- $ P(x = 4) = \frac{2}{9} $：可能路径为 $ 3 \rightarrow_{1} 2 \rightarrow_{0.67} [3, 4] \rightarrow_{1} 2 \rightarrow_{0.33} 1 $。
- $ P(x = 6) = \frac{4}{27} $：可能路径为 $ 3 \rightarrow_{1} 2 \rightarrow_{0.67} [3, 4] \rightarrow_{1} 2 \rightarrow_{0.67} [3, 4] \rightarrow_{1} 2 \rightarrow_{0.33} 1 $。
- 一般情况下，$ P(x = i \cdot 2) = \frac{2^{i - 1}}{3^i} $。

因此，$ f(v, p) = \sum_{i=1}^{\infty}{i \cdot 2 \cdot \frac{2^{i - 1}}{3^i}} = 6 $。

第二个测试用例中，树的结构如下：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040E/817926230fce12f251ecac195b4fa36da450f14f.png)


 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
4 4
1 2
2 3
2 4
2 0
3 0
4 0
3 1
12 10
1 2
2 3
2 4
1 5
5 6
6 7
6 8
6 9
8 10
10 11
10 12
6 0
9 0
10 0
11 0
3 1
7 1
10 1
12 1
12 2
11 12
```

### 输出

```
1
6
6
2
4
9
8
15
2
3
6
9
5
5
```



---

---
title: "Key of Like (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2089C1
tag: ['动态规划 DP', '概率论']
---

# Key of Like (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本之间的区别在于，在这个版本中保证 $$$k = 0$$$。只有当你解决了该问题的所有版本时才能进行 hack。

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

输入仅一行包含三个整数 $$$n$$$、$$$l$$$、$$$k$$$（$$$1 \leq n \leq 100$$$，$$$1 \leq l \leq 5000$$$，$$$k = 0$$$）——参与游戏的成员数、锁的数量和仿制钥匙的数量。

保证所有测试用例的 $$$l$$$ 之和不超过 $$$5000$$$。

## 输出格式

对于每个测试用例，输出一行包含 $$$n$$$ 个整数 $$$e_1, \ldots, e_n$$$，其中 $$$e_i$$$ 表示第 $$$i$$$ 位成员的期望成功匹配次数，结果对 $$$10^9 + 7$$$ 取模。

形式化地，令 $$$M = 10^9 + 7$$$。可以证明精确答案可以表示为不可约分数 $$$\frac{p}{q}$$$，其中 $$$p$$$ 和 $$$q$$$ 为整数且 $$$q \not \equiv 0 \pmod{M}$$$。输出整数 $$$p \cdot q^{-1} \bmod M$$$。换句话说，输出满足 $$$0 \le x < M$$$ 且 $$$e_i \cdot q \equiv p \pmod{M}$$$ 的整数 $$$e_i$$$。

## 说明/提示

对于第一个测试用例，只有 $$$1$$$ 把锁，因此第一位成员必定用唯一的钥匙打开唯一的锁。

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
3 1 0
3 2 0
2 5 0
9 104 0
```

### 输出

```
1 0 0
500000004 1 500000004
200000004 800000008
869203933 991076635 39374313 496894434 9358446 51822059 979588764 523836809 38844739
```



---

---
title: "Trails and Glades"
layout: "post"
diff: 提高+/省选-
pid: CF209C
tag: ['连通块', '欧拉回路', '概率论']
---

# Trails and Glades

## 题目描述

Vasya went for a walk in the park. The park has $ n $ glades, numbered from 1 to $ n $ . There are $ m $ trails between the glades. The trails are numbered from 1 to $ m $ , where the $ i $ -th trail connects glades $ x_{i} $ and $ y_{i} $ . The numbers of the connected glades may be the same $ (x_{i}=y_{i}) $ , which means that a trail connects a glade to itself. Also, two glades may have several non-intersecting trails between them.

Vasya is on glade 1, he wants to walk on all trails of the park exactly once, so that he can eventually return to glade 1. Unfortunately, Vasya does not know whether this walk is possible or not. Help Vasya, determine whether the walk is possible or not. If such walk is impossible, find the minimum number of trails the authorities need to add to the park in order to make the described walk possible.

Vasya can shift from one trail to another one only on glades. He can move on the trails in both directions. If Vasya started going on the trail that connects glades $ a $ and $ b $ , from glade $ a $ , then he must finish this trail on glade $ b $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n<=10^{6}; 0<=m<=10^{6}) $ — the number of glades in the park and the number of trails in the park, respectively. Next $ m $ lines specify the trails. The $ i $ -th line specifies the $ i $ -th trail as two space-separated numbers, $ x_{i} $ , $ y_{i} $ $ (1<=x_{i},y_{i}<=n) $ — the numbers of the glades connected by this trail.

## 输出格式

Print the single integer — the answer to the problem. If Vasya's walk is possible without adding extra trails, print 0, otherwise print the minimum number of trails the authorities need to add to the park in order to make Vasya's walk possible.

## 说明/提示

In the first test case the described walk is possible without building extra trails. For example, let's first go on the first trail, then on the second one, and finally on the third one.

In the second test case the described walk is impossible without adding extra trails. To make the walk possible, it is enough to add one trail, for example, between glades number one and two.

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
0

```

## 样例 #2

### 输入

```
2 5
1 1
1 2
1 2
2 2
1 2

```

### 输出

```
1

```



---

---
title: "Longest Subsequence"
layout: "post"
diff: 提高+/省选-
pid: CF632D
tag: ['最大公约数 gcd', '概率论']
---

# Longest Subsequence

## 题目描述

You are given array $ a $ with $ n $ elements and the number $ m $ . Consider some subsequence of $ a $ and the value of least common multiple (LCM) of its elements. Denote LCM as $ l $ . Find any longest subsequence of $ a $ with the value $ l<=m $ .

A subsequence of $ a $ is an array we can get by erasing some elements of $ a $ . It is allowed to erase zero or all elements.

The LCM of an empty array equals $ 1 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{6} $ ) — the size of the array $ a $ and the parameter from the problem statement.

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ) — the elements of $ a $ .

## 输出格式

In the first line print two integers $ l $ and $ k_{max} $ ( $ 1<=l<=m,0<=k_{max}<=n $ ) — the value of LCM and the number of elements in optimal subsequence.

In the second line print $ k_{max} $ integers — the positions of the elements from the optimal subsequence in the ascending order.

Note that you can find and print any subsequence with the maximum length.

## 样例 #1

### 输入

```
7 8
6 2 9 2 7 2 3

```

### 输出

```
6 5
1 2 4 6 7

```

## 样例 #2

### 输入

```
6 4
2 2 2 3 3 3

```

### 输出

```
2 3
1 2 3

```



---

---
title: "Fibonacci-ish"
layout: "post"
diff: 提高+/省选-
pid: CF633D
tag: ['枚举', '剪枝', '概率论']
---

# Fibonacci-ish

## 题目描述

Yash has recently learnt about the Fibonacci sequence and is very excited about it. He calls a sequence Fibonacci-ish if

1. the sequence consists of at least two elements
2. $ f_{0} $ and $ f_{1} $ are arbitrary
3. $ f_{n+2}=f_{n+1}+f_{n} $ for all $ n>=0 $ .

You are given some sequence of integers $ a_{1},a_{2},...,a_{n} $ . Your task is rearrange elements of this sequence in such a way that its longest possible prefix is Fibonacci-ish sequence.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=1000 $ ) — the length of the sequence $ a_{i} $ .

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ |a_{i}|<=10^{9} $ ).

## 输出格式

Print the length of the longest possible Fibonacci-ish prefix of the given sequence after rearrangement.

## 说明/提示

In the first sample, if we rearrange elements of the sequence as $ -1 $ , $ 2 $ , $ 1 $ , the whole sequence $ a_{i} $ would be Fibonacci-ish.

In the second sample, the optimal way to rearrange elements is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/d3ff4ea2c12e52c9ca4c15e14139f2b01f478bed.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/67db7509088e9e5340d450cc0af986d1466ce169.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/7be78903e0b1130fefbb3533b84d31cf4efaa940.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/0d98505f3f5d3d9cd5c06747ea4bb30d03a8d1e8.png), $ 28 $ .

## 样例 #1

### 输入

```
3
1 2 -1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5
28 35 7 14 21

```

### 输出

```
4

```



---

---
title: "High Cry"
layout: "post"
diff: 提高+/省选-
pid: CF875D
tag: ['线段树', '概率论', '栈']
---

# High Cry

## 题目描述

Disclaimer: there are lots of untranslateable puns in the Russian version of the statement, so there is one more reason for you to learn Russian :)

Rick and Morty like to go to the ridge High Cry for crying loudly — there is an extraordinary echo. Recently they discovered an interesting acoustic characteristic of this ridge: if Rick and Morty begin crying simultaneously from different mountains, their cry would be heard between these mountains up to the height equal the bitwise OR of mountains they've climbed and all the mountains between them.

Bitwise OR is a binary operation which is determined the following way. Consider representation of numbers $ x $ and $ y $ in binary numeric system (probably with leading zeroes) $ x=x_{k}...\ x_{1}x_{0} $ and $ y=y_{k}...\ y_{1}y_{0} $ . Then $ z=x | y $ is defined following way: $ z=z_{k}...\ z_{1}z_{0} $ , where $ z_{i}=1 $ , if $ x_{i}=1 $ or $ y_{i}=1 $ , and $ z_{i}=0 $ otherwise. In the other words, digit of bitwise OR of two numbers equals zero if and only if digits at corresponding positions is both numbers equals zero. For example bitwise OR of numbers $ 10=1010_{2} $ and $ 9=1001_{2} $ equals $ 11=1011_{2} $ . In programming languages C/C++/Java/Python this operation is defined as «|», and in Pascal as «or».

Help Rick and Morty calculate the number of ways they can select two mountains in such a way that if they start crying from these mountains their cry will be heard above these mountains and all mountains between them. More formally you should find number of pairs $ l $ and $ r $ ( $ 1<=l&lt;r<=n $ ) such that bitwise OR of heights of all mountains between $ l $ and $ r $ (inclusive) is larger than the height of any mountain at this interval.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=200000 $ ), the number of mountains in the ridge.

Second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=10^{9} $ ), the heights of mountains in order they are located in the ridge.

## 输出格式

Print the only integer, the number of ways to choose two different mountains.

## 说明/提示

In the first test case all the ways are pairs of mountains with the numbers (numbering from one):

 $ (1,4),(1,5),(2,3),(2,4),(2,5),(3,4),(3,5),(4,5) $ In the second test case there are no such pairs because for any pair of mountains the height of cry from them is $ 3 $ , and this height is equal to the height of any mountain.

## 样例 #1

### 输入

```
5
3 2 1 6 5

```

### 输出

```
8

```

## 样例 #2

### 输入

```
4
3 3 3 3

```

### 输出

```
0

```



---

---
title: "Beads"
layout: "post"
diff: 提高+/省选-
pid: CF8E
tag: ['枚举', '进制', '概率论']
---

# Beads

## 题目描述

One Martian boy called Zorg wants to present a string of beads to his friend from the Earth — Masha. He knows that Masha likes two colours: blue and red, — and right in the shop where he has come, there is a variety of adornments with beads of these two colours. All the strings of beads have a small fastener, and if one unfastens it, one might notice that all the strings of beads in the shop are of the same length. Because of the peculiarities of the Martian eyesight, if Zorg sees one blue-and-red string of beads first, and then the other with red beads instead of blue ones, and blue — instead of red, he regards these two strings of beads as identical. In other words, Zorg regards as identical not only those strings of beads that can be derived from each other by the string turnover, but as well those that can be derived from each other by a mutual replacement of colours and/or by the string turnover.

It is known that all Martians are very orderly, and if a Martian sees some amount of objects, he tries to put them in good order. Zorg thinks that a red bead is smaller than a blue one. Let's put 0 for a red bead, and 1 — for a blue one. From two strings the Martian puts earlier the string with a red bead in the $ i $ -th position, providing that the second string has a blue bead in the $ i $ -th position, and the first two beads $ i-1 $ are identical.

At first Zorg unfastens all the strings of beads, and puts them into small heaps so, that in each heap strings are identical, in his opinion. Then he sorts out the heaps and chooses the minimum string in each heap, in his opinion. He gives the unnecassary strings back to the shop assistant and says he doesn't need them any more. Then Zorg sorts out the remaining strings of beads and buys the string with index $ k $ .

All these manupulations will take Zorg a lot of time, that's why he asks you to help and find the string of beads for Masha.

## 输入格式

The input file contains two integers $ n $ and $ k $ ( $ 2<=n<=50;1<=k<=10^{16} $ ) —the length of a string of beads, and the index of the string, chosen by Zorg.

## 输出格式

Output the $ k $ -th string of beads, putting 0 for a red bead, and 1 — for a blue one. If it s impossible to find the required string, output the only number -1.

## 说明/提示

Let's consider the example of strings of length 4 — 0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001, 1010, 1011, 1100, 1101, 1110. Zorg will divide them into heaps: {0001, 0111, 1000, 1110}, {0010, 0100, 1011, 1101}, {0011, 1100}, {0101, 1010}, {0110, 1001}. Then he will choose the minimum strings of beads in each heap: 0001, 0010, 0011, 0101, 0110. The forth string — 0101.

## 样例 #1

### 输入

```
4 4

```

### 输出

```
0101

```



---

---
title: "Congruence Equation"
layout: "post"
diff: 提高+/省选-
pid: CF919E
tag: ['素数判断,质数,筛法', '概率论', '逆元']
---

# Congruence Equation

## 题目描述

Given an integer $ x $ . Your task is to find out how many positive integers $ n $ ( $ 1<=n<=x $ ) satisfy

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF919E/02717f82c41ef4ed609db5d967f659c9784212e1.png) where $ a,b,p $ are all known constants.

## 输入格式

The only line contains four integers $ a,b,p,x $ ( $ 2<=p<=10^{6}+3 $ , $ 1<=a,b<p $ , $ 1<=x<=10^{12} $ ). It is guaranteed that $ p $ is a prime.

## 输出格式

Print a single integer: the number of possible answers $ n $ .

## 说明/提示

In the first sample, we can see that $ n=2 $ and $ n=8 $ are possible answers.

## 样例 #1

### 输入

```
2 3 5 8

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 6 7 13

```

### 输出

```
1

```

## 样例 #3

### 输入

```
233 233 10007 1

```

### 输出

```
1

```



---

---
title: "Robot Vacuum Cleaner"
layout: "post"
diff: 提高+/省选-
pid: CF922D
tag: ['字符串', '排序', '概率论']
---

# Robot Vacuum Cleaner

## 题目描述

Pushok the dog has been chasing Imp for a few hours already.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/829d42ff73514382387680ad82853edceea77a87.png)Fortunately, Imp knows that Pushok is afraid of a robot vacuum cleaner.

While moving, the robot generates a string $ t $ consisting of letters 's' and 'h', that produces a lot of noise. We define noise of string $ t $ as the number of occurrences of string "sh" as a subsequence in it, in other words, the number of such pairs $ (i,j) $ , that $ i<j $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/f1a56c1d084d739e6652be99271753eea487f10e.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/1c020fe0ca945d3f2fc54f71a604c6ab2188fcee.png).

The robot is off at the moment. Imp knows that it has a sequence of strings $ t_{i} $ in its memory, and he can arbitrary change their order. When the robot is started, it generates the string $ t $ as a concatenation of these strings in the given order. The noise of the resulting string equals the noise of this concatenation.

Help Imp to find the maximum noise he can achieve by changing the order of the strings.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of strings in robot's memory.

Next $ n $ lines contain the strings $ t_{1},t_{2},...,t_{n} $ , one per line. It is guaranteed that the strings are non-empty, contain only English letters 's' and 'h' and their total length does not exceed $ 10^{5} $ .

## 输出格式

Print a single integer — the maxumum possible noise Imp can achieve by changing the order of the strings.

## 说明/提示

The optimal concatenation in the first sample is $ ssshhshhhs $ .

## 样例 #1

### 输入

```
4
ssh
hs
s
hhhs

```

### 输出

```
18

```

## 样例 #2

### 输入

```
2
h
s

```

### 输出

```
1

```



---

---
title: "Perfect Groups"
layout: "post"
diff: 提高+/省选-
pid: CF980D
tag: ['数学', '素数判断,质数,筛法', '概率论']
---

# Perfect Groups

## 题目描述

SaMer has written the greatest test case of all time for one of his problems. For a given array of integers, the problem asks to find the minimum number of groups the array can be divided into, such that the product of any pair of integers in the same group is a perfect square.

Each integer must be in exactly one group. However, integers in a group do not necessarily have to be contiguous in the array.

SaMer wishes to create more cases from the test case he already has. His test case has an array $ A $ of $ n $ integers, and he needs to find the number of contiguous subarrays of $ A $ that have an answer to the problem equal to $ k $ for each integer $ k $ between $ 1 $ and $ n $ (inclusive).

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1 \leq n \leq 5000 $ ), the size of the array.

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , $ \dots $ , $ a_n $ ( $ -10^8 \leq a_i \leq 10^8 $ ), the values of the array.

## 输出格式

Output $ n $ space-separated integers, the $ k $ -th integer should be the number of contiguous subarrays of $ A $ that have an answer to the problem equal to $ k $ .

## 样例 #1

### 输入

```
2
5 5

```

### 输出

```
3 0

```

## 样例 #2

### 输入

```
5
5 -4 2 1 8

```

### 输出

```
5 5 3 2 0

```

## 样例 #3

### 输入

```
1
0

```

### 输出

```
1

```



---

---
title: "Nastya and a Game"
layout: "post"
diff: 提高+/省选-
pid: CF992D
tag: ['枚举', '概率论']
---

# Nastya and a Game

## 题目描述

$Nastya$  在生日那天收到了一个大小为  $n$  的数组，她想知道数组存放的序列中，有多少的子串满足其中所有的数的乘积是数的总和的  $k$  倍。请帮她得到答案。

## 输入格式

第  $1$  行，有  $2$  个整数，分别表示数组的大小  $n$  和倍数  $k$ 。

（数据范围： $1 \leqslant n \leqslant 2 \times 10^{5}$ ， $1 \leqslant k \leqslant 10^5$ ）

第  $2$  行，有  $n$  个整数，表示数组的元素  $a_i$ 。

（数据范围： $1 \leqslant a_i \leqslant 10^8$ ）

## 输出格式

仅  $1$  个整数，表示符合条件的子串数量。

## 说明/提示

- 第  $1$  组样例的解释：

只有  $1$  子串  $\{1\}$ ，因为  $\frac{1}{1}=k=1$ ，所以它恰好是符合条件的。

- 第  $2$  组样例的解释：

 $\{6,\ 3\}$  中所有数的乘积是  $18$ ，总和是  $9$ ，因为  $\frac{18}{9}=k=2$ ，所以它符合条件。

 $\{3,\ 8,\ 1\}$ 中所有数的乘积是  $24$ ，总和是  $12$ ，因为  $\frac{24}{12} = k = 2$ ，所以它也符合条件。

综上所述，共有  $2$  个子串符合条件。

感谢@Sooke 提供翻译以及@ZqlwMatt 修正

## 样例 #1

### 输入

```
1 1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4 2
6 3 8 1

```

### 输出

```
2

```



---

---
title: "Reachability from the Capital"
layout: "post"
diff: 提高+/省选-
pid: CF999E
tag: ['深度优先搜索 DFS', '强连通分量', '概率论']
---

# Reachability from the Capital

## 题目描述

在 Berland 有 $n$ 座城市和 $m$ 条道路，每条道路连接着一对城市。

Berland 的道路都是**单向**的

为了能让首都能够到达所有的城市，最少需要新修建多少新道路？

新道路也是单向的

## 输入格式

输入的第一行包含三个整数 $n,m$ 和 $s$ $(1\le n \le 5000,0\le m \le 5000 , 1\le s \le n)$ ——城市数，道路数和首都所在城市的标号。 城市的标号为 $1$ \~ $n$
接下来 $m$ 行每行包含一条道路连接着一对城市 $u_i,v_i$ $(1\le u_i,v_i\le n,u_i\ne v_i)$

 对于每对城市 $u,v$，从 $u$ 到 $v$ 最多只能有一条道路。 允许在一对城市之间建造相反方向的道路（即从 $u$ 到 $v$ 和从 $v$ 到 $u$ ）。

## 输出格式

输出一个整数——使从首都可以到达所有城市所需的最少新修建道路数。如果从 $s$ 已经可以到达所有城市，则输出 $0$。

## 说明/提示

样例 1：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF999E/cfa72c5c5f72e8ccb5babda1e509efae921c1e73.png)

例如，您可以添加道路 ( 6, 4 ) , ( 7 , 9 ) , ( 1 , 7 )，以使从 $s = 1$ 可到达所有城市。
样例 2：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF999E/62d78c6df2be4fcc0d6c17ba856e4ad627c47d5f.png)

在此样例中，您可以添加道路（5 , 1），（5 , 2），（5 , 3），（5 , 4）中的任何一条，以使可从 $s = 5$ 到达所有城市。

## 样例 #1

### 输入

```
9 9 1
1 2
1 3
2 3
1 5
5 6
6 1
1 8
9 8
7 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 4 5
1 2
2 3
3 4
4 1

```

### 输出

```
1

```



---

