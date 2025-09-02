---
title: "Covered Points Count"
layout: "post"
diff: 普及/提高-
pid: CF1000C
tag: ['枚举', '排序', '前缀和']
---

# Covered Points Count

## 题目描述

**题目大意：**

给你n个区间，求被这些区间覆盖层数为$k(k<=n)$的点的个数

## 输入格式

第一行一个整数，$n$，$n<=2*10^5$

以下$n$行，每行有两个整数，即这个区间的左右端点$l,r(0<=l<=r<=10^{18})$

## 输出格式

$n$个整数，即每个被覆盖层数对应的点的个数

感谢@守望 提供翻译

## 样例 #1

### 输入

```
3
0 3
1 3
3 8

```

### 输出

```
6 2 1 

```

## 样例 #2

### 输入

```
3
1 3
2 4
5 7

```

### 输出

```
5 2 0 

```



---

---
title: "Elections"
layout: "post"
diff: 普及/提高-
pid: CF1019A
tag: ['贪心', '枚举', '排序']
---

# Elections

## 题目描述

Berland地区的腐败现象非常常见。

马上有一场选举，你事先知道了选民和政党的数量，分别为  $n$  和  $m$  ，对于每一位选民，你知道他将要选举哪一个政党，不过，每一位选民都会在接受一定数额的金钱之后改变他的主意。如果你给第  $i$  位选民  $c_i$  数额的比特币，他就会选举任何你希望他选举的政党。

你的目的是让Berland的联合党赢得这场选举，联合党必须拥有比其它政党都多的选票，在此基础之上，你希望花费的比特币尽可能少。

## 输入格式

第一行包含两个整数  $n$  和  $m$ .

接下来  $n$  行每一行两个整数——  $p_i$  和  $c_i$  ，这一位选民将会选举政党的编号，和使他改变主意的最少比特币数额。

特别地，联合党的编号是1.


第一行包含两个整数  $n$  和  $m$ .

接下来  $n$  行每一行两个整数——  $p_i$  和  $c_i$  ，这一位选民将会选举政党的编号，和使他改变主意的最少比特币数额。

特别地，联合党的编号是1.

## 输出格式

一个整数，使联合党赢得选举所需花费的最少比特币数额。

```
Berland地区的腐败现象非常常见。

马上有一场选举，你事先知道了选民和政党的数量，分别为  $n$  和  $m$  ，对于每一位选民，你知道他将要选举哪一个政党，不过，每一位选民都会在接受一定数额的金钱之后改变他的主意。如果你给第  $i$  位选民  $c_i$  数额的比特币，他就会选举任何你希望他选举的政党。

你的目的是让Berland的联合党赢得这场选举，联合党必须拥有比其它政党都多的选票，在此基础之上，你希望花费的比特币尽可能少。


一个整数，使联合党赢得选举所需花费的最少比特币数额。
```

## 样例 #1

### 输入

```
1 2
1 100

```

### 输出

```
0

```

## 样例 #2

### 输入

```
5 5
2 100
3 200
4 300
5 400
5 900

```

### 输出

```
500

```

## 样例 #3

### 输入

```
5 5
2 100
3 200
4 300
5 800
5 900

```

### 输出

```
600

```



---

---
title: "Minimum Value Rectangle"
layout: "post"
diff: 普及/提高-
pid: CF1027C
tag: ['贪心', '排序']
---

# Minimum Value Rectangle

## 题目描述

You have $ n $ sticks of the given lengths.

Your task is to choose exactly four of them in such a way that they can form a rectangle. No sticks can be cut to pieces, each side of the rectangle must be formed by a single stick. No stick can be chosen multiple times. It is guaranteed that it is always possible to choose such sticks.

Let $ S $ be the area of the rectangle and $ P $ be the perimeter of the rectangle.

The chosen rectangle should have the value $ \frac{P^2}{S} $ minimal possible. The value is taken without any rounding.

If there are multiple answers, print any of them.

Each testcase contains several lists of sticks, for each of them you are required to solve the problem separately.

## 输入格式

The first line contains a single integer $ T $ ( $ T \ge 1 $ ) — the number of lists of sticks in the testcase.

Then $ 2T $ lines follow — lines $ (2i - 1) $ and $ 2i $ of them describe the $ i $ -th list. The first line of the pair contains a single integer $ n $ ( $ 4 \le n \le 10^6 $ ) — the number of sticks in the $ i $ -th list. The second line of the pair contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_j \le 10^4 $ ) — lengths of the sticks in the $ i $ -th list.

It is guaranteed that for each list there exists a way to choose four sticks so that they form a rectangle.

The total number of sticks in all $ T $ lists doesn't exceed $ 10^6 $ in each testcase.

## 输出格式

Print $ T $ lines. The $ i $ -th line should contain the answer to the $ i $ -th list of the input. That is the lengths of the four sticks you choose from the $ i $ -th list, so that they form a rectangle and the value $ \frac{P^2}{S} $ of this rectangle is minimal possible. You can print these four lengths in arbitrary order.

If there are multiple answers, print any of them.

## 说明/提示

There is only one way to choose four sticks in the first list, they form a rectangle with sides $ 2 $ and $ 7 $ , its area is $ 2 \cdot 7 = 14 $ , perimeter is $ 2(2 + 7) = 18 $ . $ \frac{18^2}{14} \approx 23.143 $ .

The second list contains subsets of four sticks that can form rectangles with sides $ (1, 2) $ , $ (2, 8) $ and $ (1, 8) $ . Their values are $ \frac{6^2}{2} = 18 $ , $ \frac{20^2}{16} = 25 $ and $ \frac{18^2}{8} = 40.5 $ , respectively. The minimal one of them is the rectangle $ (1, 2) $ .

You can choose any four of the $ 5 $ given sticks from the third list, they will form a square with side $ 5 $ , which is still a rectangle with sides $ (5, 5) $ .

## 样例 #1

### 输入

```
3
4
7 2 2 7
8
2 8 1 4 8 2 1 5
5
5 5 5 5 5

```

### 输出

```
2 7 7 2
2 2 1 1
5 5 5 5

```



---

---
title: "Valid BFS?"
layout: "post"
diff: 普及/提高-
pid: CF1037D
tag: ['排序', '广度优先搜索 BFS', '队列']
---

# Valid BFS?

## 题目描述

The [BFS](https://en.wikipedia.org/wiki/Breadth-first_search) algorithm is defined as follows.

1. Consider an undirected graph with vertices numbered from $ 1 $ to $ n $ . Initialize $ q $ as a new [queue](http://gg.gg/queue_en) containing only vertex $ 1 $ , mark the vertex $ 1 $ as used.
2. Extract a vertex $ v $ from the head of the queue $ q $ .
3. Print the index of vertex $ v $ .
4. Iterate in arbitrary order through all such vertices $ u $ that $ u $ is a neighbor of $ v $ and is not marked yet as used. Mark the vertex $ u $ as used and insert it into the tail of the queue $ q $ .
5. If the queue is not empty, continue from step 2.
6. Otherwise finish.

Since the order of choosing neighbors of each vertex can vary, it turns out that there may be multiple sequences which BFS can print.

In this problem you need to check whether a given sequence corresponds to some valid BFS traversal of the given tree starting from vertex $ 1 $ . The [tree](http://gg.gg/tree_en) is an undirected graph, such that there is exactly one simple path between any two vertices.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) which denotes the number of nodes in the tree.

The following $ n - 1 $ lines describe the edges of the tree. Each of them contains two integers $ x $ and $ y $ ( $ 1 \le x, y \le n $ ) — the endpoints of the corresponding edge of the tree. It is guaranteed that the given graph is a tree.

The last line contains $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the sequence to check.

## 输出格式

Print "Yes" (quotes for clarity) if the sequence corresponds to some valid BFS traversal of the given tree and "No" (quotes for clarity) otherwise.

You can print each letter in any case (upper or lower).

## 说明/提示

Both sample tests have the same tree in them.

In this tree, there are two valid BFS orderings:

- $ 1, 2, 3, 4 $ ,
- $ 1, 3, 2, 4 $ .

The ordering $ 1, 2, 4, 3 $ doesn't correspond to any valid BFS order.

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
1 2 3 4

```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
4
1 2
1 3
2 4
1 2 4 3

```

### 输出

```
No
```



---

---
title: "Social Circles"
layout: "post"
diff: 普及/提高-
pid: CF1060D
tag: ['贪心', '排序']
---

# Social Circles

## 题目描述

You invited $ n $ guests to dinner! You plan to arrange one or more circles of chairs. Each chair is going to be either occupied by one guest, or be empty. You can make any number of circles.

Your guests happen to be a little bit shy, so the $ i $ -th guest wants to have a least $ l_i $ free chairs to the left of his chair, and at least $ r_i $ free chairs to the right. The "left" and "right" directions are chosen assuming all guests are going to be seated towards the center of the circle. Note that when a guest is the only one in his circle, the $ l_i $ chairs to his left and $ r_i $ chairs to his right may overlap.

What is smallest total number of chairs you have to use?

## 输入格式

First line contains one integer $ n $ — number of guests, ( $ 1 \leqslant n \leqslant 10^5 $ ).

Next $ n $ lines contain $ n $ pairs of space-separated integers $ l_i $ and $ r_i $ ( $ 0 \leqslant l_i, r_i \leqslant 10^9 $ ).

## 输出格式

Output a single integer — the smallest number of chairs you have to use.

## 说明/提示

In the second sample the only optimal answer is to use two circles: a circle with $ 5 $ chairs accomodating guests $ 1 $ and $ 2 $ , and another one with $ 10 $ chairs accomodationg guests $ 3 $ and $ 4 $ .

In the third sample, you have only one circle with one person. The guest should have at least five free chairs to his left, and at least six free chairs to his right to the next person, which is in this case the guest herself. So, overall number of chairs should be at least 6+1=7.

## 样例 #1

### 输入

```
3
1 1
1 1
1 1

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
2 1
3 5
5 3

```

### 输出

```
15

```

## 样例 #3

### 输入

```
1
5 6

```

### 输出

```
7

```



---

---
title: "Equalize"
layout: "post"
diff: 普及/提高-
pid: CF1928B
tag: ['排序', '双指针 two-pointer']
---

# Equalize

## 题目描述

Vasya has two hobbies — adding permutations $ ^{\dagger} $ to arrays and finding the most frequently occurring element. Recently, he found an array $ a $ and decided to find out the maximum number of elements equal to the same number in the array $ a $ that he can obtain after adding some permutation to the array $ a $ .

More formally, Vasya must choose exactly one permutation $ p_1, p_2, p_3, \ldots, p_n $ of length $ n $ , and then change the elements of the array $ a $ according to the rule $ a_i := a_i + p_i $ . After that, Vasya counts how many times each number occurs in the array $ a $ and takes the maximum of these values. You need to determine the maximum value he can obtain.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 2 \cdot 10^4 $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single number — the maximum number of elements equal to the same number after the operation of adding a permutation.

## 说明/提示

In the first test case, it is optimal to choose $ p = [2, 1] $ . Then after applying the operation, the array $ a $ will be $ [3, 3] $ , in which the number $ 3 $ occurs twice, so the answer is $ 2 $ .

In the second test case, one of the optimal options is $ p = [2, 3, 1, 4] $ . After applying the operation, the array $ a $ will be $ [9, 4, 5, 5] $ . Since the number $ 5 $ occurs twice, the answer is $ 2 $ .

## 样例 #1

### 输入

```
7
2
1 2
4
7 1 4 1
3
103 102 104
5
1 101 1 100 1
5
1 10 100 1000 1
2
3 1
3
1000000000 999999997 999999999
```

### 输出

```
2
2
3
2
1
1
2
```



---

---
title: "Chat Screenshots"
layout: "post"
diff: 普及/提高-
pid: CF1931F
tag: ['拓扑排序']
---

# Chat Screenshots

## 题目描述

There are $ n $ people in the programming contest chat. Chat participants are ordered by activity, but each person sees himself at the top of the list.

For example, there are $ 4 $ participants in the chat, and their order is $ [2, 3, 1, 4] $ . Then

- $ 1 $ -st user sees the order $ [1, 2, 3, 4] $ .
- $ 2 $ -nd user sees the order $ [2, 3, 1, 4] $ .
- $ 3 $ -rd user sees the order $ [3, 2, 1, 4] $ .
- $ 4 $ -th user sees the order $ [4, 2, 3, 1] $ .

 $ k $ people posted screenshots in the chat, which show the order of participants shown to this user. The screenshots were taken within a short period of time, and the order of participants has not changed.

Your task is to determine whether there is a certain order that all screenshots correspond to.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of input test cases. The descriptions of test cases follow.

The first line of the description of each test case contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 2 \cdot 10^5, n \cdot k \le 2 \cdot 10^5 $ ) — the number of chat participants and the number of participants who posted screenshots.

The following $ k $ lines contain descriptions of screenshots posted by the participants.

The $ i $ -th row contains $ n $ integers $ a_{ij} $ each ( $ 1 \le a_{ij} \le n $ , all $ a_{ij} $ are different) — the order of participants shown to the participant $ a_{i0} $ , where $ a_{i0} $ — the author of the screenshot. You can show that in the screenshot description it will always be at the top of the list.

It is guaranteed that the sum of $ n \cdot k $ for all test cases does not exceed $ 2 \cdot 10^5 $ . It is also guaranteed that all the authors of the screenshots are different.

## 输出格式

Output $ t $ lines, each of which is the answer to the corresponding test case. As an answer, output "YES" if there exists at least one order of participants, under which all $ k $ screenshots could have been obtained. Otherwise, output "NO".

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 样例 #1

### 输入

```
10
5 1
1 2 3 4 5
4 4
1 2 3 4
2 3 1 4
3 2 1 4
4 2 3 1
6 2
1 3 5 2 4 6
6 3 5 2 1 4
3 3
1 2 3
2 3 1
3 2 1
10 2
1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1
1 1
1
5 2
1 2 3 5 4
2 1 3 5 4
3 3
3 1 2
2 3 1
1 3 2
5 4
3 5 1 4 2
2 5 1 4 3
1 5 4 3 2
5 1 4 3 2
3 3
1 3 2
2 1 3
3 2 1
```

### 输出

```
YES
YES
YES
YES
NO
YES
YES
YES
YES
NO
```



---

---
title: "World Football Cup"
layout: "post"
diff: 普及/提高-
pid: CF19A
tag: ['模拟', '排序']
---

# World Football Cup

## 题目描述

## 题意
众所周知，2010 年 FIFA 世界杯在南非举行。BFA 决定下一届世界杯将在伯兰德举行。BFA 决定改变世界杯的一些规定：  

- 最后的比赛涉及 $n$ 支球队（$n$ 总是偶数）；
- 前 $\frac{n}{2}$ 队（根据排名）进入淘汰赛阶段。

积分榜是按照以下原则制作的：胜利一个队得 $3$ 分，平分 $1$ 分，失败 $0$ 分。首先，球队按积分顺序排在积分榜上，分数相等比较净胜球，净胜球相等比较进球数。

你被要求写一个程序，通过给定的比赛名单和所有比赛的结果，找到设法进入淘汰赛阶段的球队名单。

## 输入格式

第一个输入行包含唯一的整数 $n(1 \le n \le 50)$表示参加世界杯决赛的球队数量。 

以下 $n$ 行，包含这些团队的名称，名称是一个包含小写和大写拉丁字母的字符串，其长度不超过 $30$ 个字符。

以下的 $\frac{n\times(n-1)}{2}$ 行描述格式为 $\text{name1-name2  num1:num2}$，其中 $\text{name1,name2}$ 为团队名称；$\text{num1,num2} (0 \le \text{num1,num2} \le 100) $ 为相应的队伍得分。 数据保证没有两支球队名字相同，没有比赛一个球队与自己打球，任意两个球队只会比赛一次。

## 输出格式

按照字典顺序输出 $\frac{n}{2}$ 行进入淘汰赛阶段的球队的名字，在一个单独的行中输出每支球队名称。数据保证结果唯一。
Translated by @Youngsc、@艾因斯坦

## 样例 #1

### 输入

```
4
A
B
C
D
A-B 1:1
A-C 2:2
A-D 1:0
B-C 1:0
B-D 0:3
C-D 0:3

```

### 输出

```
A
D

```

## 样例 #2

### 输入

```
2
a
A
a-A 2:1

```

### 输出

```
a

```



---

---
title: "Concatenation of Arrays"
layout: "post"
diff: 普及/提高-
pid: CF2023A
tag: ['贪心', '排序']
---

# Concatenation of Arrays

## 题目描述

You are given $ n $ arrays $ a_1 $ , $ \ldots $ , $ a_n $ . The length of each array is two. Thus, $ a_i = [a_{i, 1}, a_{i, 2}] $ . You need to concatenate the arrays into a single array of length $ 2n $ such that the number of inversions $ ^{\dagger} $ in the resulting array is minimized. Note that you do not need to count the actual number of inversions.

More formally, you need to choose a permutation $ ^{\ddagger} $ $ p $ of length $ n $ , so that the array $ b = [a_{p_1,1}, a_{p_1,2}, a_{p_2, 1}, a_{p_2, 2}, \ldots, a_{p_n,1}, a_{p_n,2}] $ contains as few inversions as possible.

 $ ^{\dagger} $ The number of inversions in an array $ c $ is the number of pairs of indices $ i $ and $ j $ such that $ i < j $ and $ c_i > c_j $ .

 $ ^{\ddagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of arrays.

Each of the following $ n $ lines contains two integers $ a_{i,1} $ and $ a_{i,2} $ ( $ 1 \le a_{i,j} \le 10^9 $ ) — the elements of the $ i $ -th array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ 2n $ integers — the elements of the array you obtained. If there are multiple solutions, output any of them.

## 说明/提示

In the first test case, we concatenated the arrays in the order $ 2, 1 $ . Let's consider the inversions in the resulting array $ b = [2, 3, 1, 4] $ :

- $ i = 1 $ , $ j = 3 $ , since $ b_1 = 2 > 1 = b_3 $ ;
- $ i = 2 $ , $ j = 3 $ , since $ b_2 = 3 > 1 = b_3 $ .

Thus, the number of inversions is $ 2 $ . It can be proven that this is the minimum possible number of inversions.

In the second test case, we concatenated the arrays in the order $ 3, 1, 2 $ . Let's consider the inversions in the resulting array $ b = [2, 1, 3, 2, 4, 3] $ :

- $ i = 1 $ , $ j = 2 $ , since $ b_1 = 2 > 1 = b_2 $ ;
- $ i = 3 $ , $ j = 4 $ , since $ b_3 = 3 > 2 = b_4 $ ;
- $ i = 5 $ , $ j = 6 $ , since $ b_5 = 4 > 3 = b_6 $ .

Thus, the number of inversions is $ 3 $ . It can be proven that this is the minimum possible number of inversions.

In the third test case, we concatenated the arrays in the order $ 4, 2, 1, 5, 3 $ .

## 样例 #1

### 输入

```
4
2
1 4
2 3
3
3 2
4 3
2 1
5
5 10
2 3
9 6
4 1
8 7
1
10 20
```

### 输出

```
2 3 1 4
2 1 3 2 4 3
4 1 2 3 5 10 8 7 9 6
10 20
```



---

---
title: "DIY"
layout: "post"
diff: 普及/提高-
pid: CF2038C
tag: ['贪心', '排序']
---

# DIY

## 题目描述

给定一个长度为 $n$ 的整数数列 $a$，下标从 $1$ 到 $n$。你需要从 $a$ 中选择 $8$ 个下标互不相同的数 $x1,y1,x2,y2,x3,y3,x4,y4$，并使 $(x_1,y_1),(x_2,y_2),(x_3,y_3),(x_4,y_4)$ 成为一个长方形的四个点的坐标。请构造一种方案使得此长方形面积最大，或报告无解。

## 输入格式

本题多测。

第一行一个整数 $t(1\le t\le 25000)$，代表测试样例组数。

对于每组测试样例：

第一行一个整数 $n(8\le n\le 2\times 10^5)$。

第二行 $n$ 个整数 $a_1,a_2,\dots,a_n(-10^9\le a_i\le 10^9)$。

保证 $\sum n\le 2\times 10^5$。

## 输出格式

对于每组测试样例：

若无解，输出一行 ```NO```（不区分大小写）。

否则，第一行输出 ```YES```（不区分大小写），第二行输出 $x1,y1,x2,y2,x3,y3,x4,y4$——长方形的四个点的坐标。你可以按任意顺序打印坐标对。

Translated by @[ARIS2_0](https://www.luogu.com.cn/user/1340759)

## 样例 #1

### 输入

```
3
16
-5 1 1 2 2 3 3 4 4 5 5 6 6 7 7 10
8
0 0 -1 2 2 1 1 3
8
0 0 0 0 0 5 0 5
```

### 输出

```
YES
1 2 1 7 6 2 6 7
NO
YES
0 0 0 5 0 0 0 5
```



---

---
title: "Medium Demon Problem (easy version)"
layout: "post"
diff: 普及/提高-
pid: CF2044G1
tag: ['拓扑排序']
---

# Medium Demon Problem (easy version)

## 题目描述

这是问题的简化版。两个版本之间的关键区别以粗体显著标出。

有一群 $n$ 只蜘蛛聚在一起交换他们的毛绒玩具。最初，每只蜘蛛都有 $1$ 个毛绒玩具。每年，如果第 $i$ 只蜘蛛拥有至少一个毛绒玩具，它就会给第 $r_i$ 只蜘蛛一个毛绒玩具。否则，它将不会进行任何操作。注意，所有的毛绒玩具转移是同时进行的。在这个版本中，如果一只蜘蛛在任意时刻拥有超过 $1$ 个毛绒玩具，它们会丢掉多余的，只保留一个。

如果在某年开始时，每只蜘蛛拥有的毛绒玩具数量与上一年相同，则这一年的过程是稳定的。请注意，第 $1$ 年永远不会是稳定的。

请找出该过程中首次出现稳定的年份。

## 输入格式

第一行输入一个整数 $t$（$1 \leq t \leq 10^4$），表示测试用例的数量。

每个测试用例的第一行输入一个整数 $n$（$2 \leq n \leq 2 \cdot 10^5$），表示蜘蛛的数量。

接下来的第二行输入 $n$ 个整数 $r_1, r_2, \ldots, r_n$（$1 \leq r_i \leq n, r_i \neq i$），表示每只蜘蛛的毛绒玩具接收者。

保证所有测试用例中的 $n$ 总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每一个测试用例，请在新的一行输出一个整数，表示过程首次达到稳定的年份。

## 说明/提示

对于第二个测试用例：

- 在第 $1$ 年，每只蜘蛛的毛绒玩具数量为 $[1, 1, 1, 1, 1]$。然后进行当年的交换。
- 到了第 $2$ 年，各蜘蛛的毛绒玩具数量仍然为 $[1, 1, 1, 1, 1]$。由于数量没有变化，因此这一年是稳定的。

对于第三个测试用例：

- 在第 $1$ 年，所有蜘蛛的毛绒玩具数量为 $[1, 1, 1, 1, 1]$。然后进行第 $1$ 年的交换。
- 在第 $2$ 年，这些数量变为 $[1, 1, 1, 1, 0]$ 。然后进行第 $2$ 年的交换。即便有两只蜘蛛给了第 $2$ 只蜘蛛毛绒玩具，第 $2$ 只蜘蛛也只能保留一个。
- 到第 $3$ 年，数量变为 $[1, 1, 0, 1, 0]$。然后进行交换。
- 第 $4$ 年，数量变为 $[1, 1, 0, 0, 0]$。然后进行交换。
- 第 $5$ 年，数量仍然为 $[1, 1, 0, 0, 0]$。由于数量保持不变，这一年是稳定的。

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
4
5
```



---

---
title: "Best Price"
layout: "post"
diff: 普及/提高-
pid: CF2051E
tag: ['二分', '排序']
---

# Best Price

## 题目描述

伯兰德最大的商店收到了一批圣诞树，并已有 $n$ 位顾客前来欲购这些树。在销售启动前，商店需要统一为每棵树定价。为了合理制定价格，商店掌握了关于每位顾客的一些信息。

对于第 $i$ 位顾客，有两个已知整数 $a_i$ 和 $b_i$，它们定义了顾客的购物行为：

- 如果价格不超过 $a_i$，顾客将购买一棵树并给出正面评价；
- 如果价格超过 $a_i$ 但不超过 $b_i$，顾客仍会购买，但会留下负面评价；
- 如果价格高于 $b_i$，则顾客将不会购买。

在负面评价不超过 $k$ 条的前提下，你的任务是帮助商店计算出最大的可能收益。

## 输入格式

第一行是一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的数量。

接下来的每个测试用例，第一行包含两个整数 $n$ 和 $k$（$1 \le n \le 2 \cdot 10^5$，$0 \le k \le n$），分别表示顾客数量和允许的最大负面评价数。

第二行是 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le 2 \cdot 10^9$），分别表示每位顾客给出正面评价的最高价格。

第三行是 $n$ 个整数 $b_1, b_2, \dots, b_n$（$1 \le b_i \le 2 \cdot 10^9$ 且 $a_i < b_i$），表示顾客购买的最高价格。

输入的附加限制是：所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每一个测试用例，输出一个整数，即在满足负面评价不超过 $k$ 条的情况下，商店可能获得的最大收益。

## 说明/提示

考虑以下例子：

- 在第一个测试用例中，如果价格设为 $1$，两位顾客都会各买一棵树且没有负面评价。
- 在第二个测试用例中，如果价格设为 $5$，顾客会购买一棵树且给出一条负面评价。
- 在第三个测试用例中，如果价格定为 $3$，所有顾客会购买且将收到两条负面评价。
- 在第四个测试用例中，价格定为 $7$ 时，有两位顾客购买，一条负面评价。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2 0
2 1
3 4
1 1
2
5
3 3
1 5 2
3 6 4
4 3
2 3 2 8
3 7 3 9
3 1
2 9 5
12 14 9
```

### 输出

```
2
5
9
14
15
```



---

---
title: "Skibidus and Sigma"
layout: "post"
diff: 普及/提高-
pid: CF2065D
tag: ['数学', '排序']
---

# Skibidus and Sigma

## 题目描述

定义一个 $k$ 个元素的数组 $b$ 的分数为
$\sum_{i=1}^{k}\left(\sum_{j=1}^{i}b_j\right)$，也就是说，设 $S_i$ 表示数组 $b$ 的前 $i$ 个元素之和，则分数可以写作
$S_1 + S_2 + \ldots + S_k$。

Skibidus 得到了 $n$ 个数组 $a_1, a_2, \ldots, a_n$，每个数组包含 $m$ 个元素。作为西格玛男人，他希望能将这 $n$ 个数组按任意顺序拼接成一个包含 $n \cdot m$ 个元素的数组，以使最终得到的拼接数组的分数达到最大。请你帮助他计算拼接后能够获得的最大分数！

形式上地说，在所有可能的长度为 $n$ 的排列 $p$ 中，
求出数组 $a_{p_1} + a_{p_2} + \dots + a_{p_n}$ 的最大分数，
其中符号 $+$ 表示数组拼接。

$ ^{\text{∗}} $ 一个排列指的是一个包含 $1$ 到 $n$ 的所有整数且每个整数恰好出现一次的序列。  
$ ^{\text{∗}} $ 两个数组 $c$ 和 $d$（长度分别为 $e$ 和 $f$）的拼接 $c+d$ 定义为 $c_1, c_2, \ldots, c_e, d_1, d_2, \ldots, d_f$。

## 输入格式

第一行包含一个整数 $t$ ($1 \leq t \leq 10^4$)，表示测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $m$ ($1 \leq n \cdot m \leq 2 \cdot 10^5$)，分别表示数组的个数和每个数组的长度。

接下来的 $n$ 行中，第 $i$ 行包含 $m$ 个整数 $a_{i,1}, a_{i,2}, \ldots, a_{i,m}$ ($1 \leq a_{i,j} \leq 10^6$)，表示第 $i$ 个数组的元素。

保证所有测试用例中，$n \cdot m$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一行一个整数，表示所有排列中拼接数组能够获得的最大分数。

## 说明/提示

在第一个测试用例中，有可能的两种排列：
- $p = [1, 2]$，拼接后的数组为 $a_{p_1} + a_{p_2} = [4, 4, 6, 1]$，分数为 $4 + (4+4) + (4+4+6) + (4+4+6+1) = 41$。
- $p = [2, 1]$，拼接后的数组为 $a_{p_1} + a_{p_2} = [6, 1, 4, 4]$，分数为 $6 + (6+1) + (6+1+4) + (6+1+4+4) = 39$。  

因此，最大可能分数为 $41$。

在第二个测试用例中，一个最优的拼接结果为 $[4,1,2,1,2,2,2,2,3,2,1,2]$，分数为 $162$。

## 样例 #1

### 输入

```
3
2 2
4 4
6 1
3 4
2 2 2 2
3 2 1 2
4 1 2 1
2 3
3 4 5
1 1 9
```

### 输出

```
41
162
72
```



---

---
title: "Sports Betting"
layout: "post"
diff: 普及/提高-
pid: CF2097A
tag: ['贪心', '排序']
---

# Sports Betting

## 题目描述

不同航班的登机过程可能以不同方式进行：要么通过巴士，要么通过伸缩式登机桥。每天，圣彼得堡到明斯克的航班恰好有一班，而 Vadim 决定向学生们证明他总能提前知道登机方式。

Vadim 与 $n$ 名学生打赌，与第 $i$ 名学生的赌约是在第 $a_i$ 天。若 Vadim 正确预测了第 $a_i+1$ 天和第 $a_i+2$ 天的登机方式，则他赢得赌约。

尽管 Vadim 并不知道登机方式会如何发生，但他非常希望至少赢得一名学生的赌约，以此说服对方相信他的预测能力。请判断是否存在一种策略，使得 Vadim 能够确保成功。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 10^5$）—— Vadim 打赌的学生人数。

每个测试用例的第二行包含 $n$ 个整数 $a_1, \ldots, a_n$（$1 \le a_i \le 10^9$）—— Vadim 与学生们打赌的日期。

保证所有测试用例的 $n$ 之和不超过 $10^5$。


## 输出格式

对于每个测试用例，若 Vadim 能确保至少说服一名学生，则输出 "Yes"（不带引号），否则输出 "No"。

答案大小写不敏感。例如，"yEs"、"yes"、"Yes" 和 "YES" 均会被视为肯定回答。

## 说明/提示

在第一个测试用例中，Vadim 需要至少正确预测第 2 天和第 3 天的登机方式之一。这两天共有 $4$ 种可能的登机场景，因此 Vadim 可以为所有 $4$ 名学生提供不同的预测组合，从而确保至少有一名学生会被说服。

在第二个测试用例中，Vadim 仅与三名学生打赌，无法保证能为其中至少一名提供正确的预测。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
4
1 1 1 1
3
2 2 2
5
2 4 3 2 4
8
6 3 1 1 5 1 2 6
1
1000000000
```

### 输出

```
Yes
No
Yes
No
No
```



---

---
title: "Sasha and the Apartment Purchase"
layout: "post"
diff: 普及/提高-
pid: CF2098B
tag: ['数学', '排序']
---

# Sasha and the Apartment Purchase

## 题目描述

Sasha 想在一条街道上购买一套公寓，这条街道上的房屋从左到右编号为 $1$ 到 $10^9$。

这条街道上有 $n$ 家酒吧，分别位于编号为 $a_1, a_2, \ldots, a_n$ 的房屋中。注意，可能有多个酒吧位于同一房屋中，这种情况下这些酒吧被视为不同的酒吧。

Sasha 担心在他购买公寓时，部分酒吧可能会关闭，但最多不超过 $k$ 家酒吧会关闭。

对于任意编号为 $x$ 的房屋，定义 $f(x)$ 为所有开放酒吧 $y$（即关闭部分酒吧后）的 $|x - y|$ 之和。

Sasha 可以购买编号为 $x$（$1 \le x \le 10^9$）的房屋中的公寓，当且仅当可以通过关闭最多 $k$ 家酒吧，使得 $f(x)$ 在所有房屋中达到最小值。

请确定 Sasha 可以购买公寓的不同房屋数量。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$1 \leq n \leq 10^5$，$0 \leq k < n$）——酒吧数量和最多可以关闭的酒吧数量。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \leq a_i \leq 10^9$）——酒吧所在的房屋编号。

保证所有测试用例的 $n$ 之和不超过 $10^5$。

## 输出格式

对于每个测试用例，输出一个整数——Sasha 可以购买公寓的房屋数量。


## 说明/提示

在第一个测试用例中，没有酒吧可以关闭，因此只有编号为 $2$ 和 $3$ 的房屋是合适的。对于编号为 $2$ 的房屋，距离之和为 $|2 - 1| + |2 - 2| + |2 - 3| + |2 - 4| = 4$；对于编号为 $3$ 的房屋，距离之和为 $|3 - 1| + |3 - 2| + |3 - 3| + |3 - 4| = 4$。然而，对于编号为 $1$ 的房屋，距离之和为 $|1 - 1| + |1 - 2| + |1 - 3| + |1 - 4| = 6$，因此编号为 $1$ 的房屋不合适。可以证明 Sasha 也无法在其他房屋购买公寓。

在第二个测试用例中，合适的房屋编号为 $6$ 和 $7$。如果 Sasha 选择编号为 $6$ 的房屋，只需不关闭任何酒吧。如果 Sasha 选择编号为 $7$ 的房屋，可以关闭编号为 $1$ 和 $6$ 的房屋中的酒吧。此时开放的酒吧将位于编号为 $6$、$7$ 和 $7$ 的房屋中。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
4 0
1 2 3 4
5 2
7 6 6 7 1
3 1
6 7 9
6 2
5 1 9 10 13 2
```

### 输出

```
2
2
4
9
```



---

---
title: "Median Splits"
layout: "post"
diff: 普及/提高-
pid: CF2103C
tag: ['贪心', '排序']
---

# Median Splits

## 题目描述

数组 $b_1, b_2, \ldots b_m$ 的中位数记作 $\operatorname{med}(b_1, b_2, \ldots, b_m)$，定义为数组 $b$ 中第 $\left\lceil \frac{m}{2} \right\rceil$ 小的元素。

给定一个整数数组 $a_1, a_2, \ldots, a_n$ 和一个整数 $k$。你需要判断是否存在一对下标 $1 \le l < r < n$ 满足：

$$
\operatorname{med}(\operatorname{med}(a_1, a_2 \dots a_l), \operatorname{med}(a_{l + 1}, a_{l + 2} \dots a_r), \operatorname{med}(a_{r + 1}, a_{r + 2} \dots a_n)) \leq k.
$$

换句话说，判断是否可以将数组分割为三个连续的子数组，使得这三个子数组中位数的中位数小于或等于 $k$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$3 \le n \le 2 \cdot 10^5$，$1 \le k \le 10^9$）——数组 $a$ 的长度和常数 $k$。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^9$）——数组 $a$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果存在满足条件的分割，输出 "YES"，否则输出 "NO"。

答案可以以任意大小写形式输出（例如 "yEs"、"yes"、"Yes" 和 "YES" 都会被识别为肯定回答）。


## 说明/提示

在第一个和第二个测试用例中，唯一可能的分割方式是将数组分为 $[3]$、$[2]$、$[1]$。它们的中位数分别是 $3$、$2$ 和 $1$。这三个中位数的中位数是 $\operatorname{med}(3, 2, 1) = 2$。因此，第一个测试用例的答案是 "YES"（因为 $2 \le 2$），而第二个测试用例的答案是 "NO"（因为 $2 > 1$）。

在第三个测试用例中，可以证明不存在满足条件的分割。

在第四个测试用例中，一个满足条件的分割是 $[10, 7]$、$[12, 16, 3, 15]$、$[6, 11]$。子数组的中位数分别是 $7$、$12$ 和 $6$。这三个中位数的中位数是 $\operatorname{med}(7, 12, 6) = 7 \le k$，因此该分割满足条件。

在第五个测试用例中，一个满足条件的分割是 $[7, 11]$、$[12, 4]$、$[9, 17]$。子数组的中位数分别是 $7$、$4$ 和 $9$。这三个中位数的中位数是 $\operatorname{med}(7, 4, 9) = 7 \le k$，因此该分割满足条件。

在第六个测试用例中，唯一可能的分割方式是将数组分为 $[1000]$、$[10^9]$、$[1000]$。子数组的中位数分别是 $1000$、$10^9$ 和 $1000$。这三个中位数的中位数是 $\operatorname{med}(1000, 10^9, 1000) = 1000 \le k$，因此该分割满足条件。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
3 2
3 2 1
3 1
3 2 1
6 3
8 5 3 1 6 4
8 7
10 7 12 16 3 15 6 11
6 8
7 11 12 4 9 17
3 500000000
1000 1000000000 1000
```

### 输出

```
YES
NO
NO
YES
YES
YES
```



---

---
title: "Champions' League"
layout: "post"
diff: 普及/提高-
pid: CF234E
tag: ['模拟', '排序']
---

# Champions' League

## 题目描述

In the autumn of this year, two Russian teams came into the group stage of the most prestigious football club competition in the world — the UEFA Champions League. Now, these teams have already started to play in the group stage and are fighting for advancing to the playoffs. In this problem we are interested in the draw stage, the process of sorting teams into groups.

The process of the draw goes as follows (the rules that are described in this problem, are somehow simplified compared to the real life). Suppose $ n $ teams will take part in the group stage ( $ n $ is divisible by four). The teams should be divided into groups of four. Let's denote the number of groups as $ m $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/65e4300bd0cdae46f7d260b1389d3b214f9ce521.png)). Each team has a rating — an integer characterizing the team's previous achievements. The teams are sorted by the rating's decreasing (no two teams have the same rating).

After that four "baskets" are formed, each of which will contain $ m $ teams: the first $ m $ teams with the highest rating go to the first basket, the following $ m $ teams go to the second one, and so on.

Then the following procedure repeats $ m-1 $ times. A team is randomly taken from each basket, first from the first basket, then from the second, then from the third, and at last, from the fourth. The taken teams form another group. After that, they are removed from their baskets.

The four teams remaining in the baskets after $ (m-1) $ such procedures are performed, form the last group.

In the real draw the random selection of teams from the basket is performed by people — as a rule, the well-known players of the past. As we have none, we will use a random number generator, which is constructed as follows. Its parameters are four positive integers $ x,a,b,c $ . Every time there is a call to the random number generator, it produces the following actions:

- calculates ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/2fe2894178b5b7478ae2269aae243e7c851b6173.png);
- replaces parameter $ x $ by value $ y $ (assigns ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/72e8070934423a6837039e7a1e2f312765ec26ab.png));
- returns $ x $ as another random number.

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) means taking the remainder after division: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/c19545677f47a50d181dd7b00e822282597427db.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/770f8dc8f9b95dc42d2401b09019f707ad7418fc.png).

A random number generator will be used in the draw as follows: each time we need to randomly choose a team from the basket, it will generate a random number $ k $ . The teams that yet remain in the basket are considered numbered with consecutive integers from $ 0 $ to $ s-1 $ , in the order of decreasing rating, where $ s $ is the current size of the basket. Then a team number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/65912cf5ed5c94787700c166a6eeb79e0114a14b.png) is taken from the basket.

Given a list of teams and the parameters of the random number generator, determine the result of the draw.

## 输入格式

The first input line contains integer $ n $ ( $ 4<=n<=64 $ , $ n $ is divisible by four) — the number of teams that take part in the sorting. The second line contains four space-separated integers $ x,a,b,c $ ( $ 1<=x,a,b,c<=1000 $ ) — the parameters of the random number generator. Each of the following $ n $ lines describes one team. The description consists of the name of the team and its rating, separated by a single space. The name of a team consists of uppercase and lowercase English letters and has length from 1 to 20 characters. A team's rating is an integer from 0 to 1000. All teams' names are distinct. All team's ratings are also distinct.

## 输出格式

Print the way the teams must be sorted into groups. Print the groups in the order, in which they are formed in the sorting. Number the groups by consecutive uppercase English letters, starting from letter 'A'. Inside each group print the teams' names one per line, in the order of decreasing of the teams' rating. See samples for a better understanding of the output format.

## 说明/提示

In the given sample the random number generator will be executed four times:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/fe99c797dbb307d601e0f59e424f6250c45a7d38.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/baa288fe7b8d960b815b5367ff1126e08e6c706b.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/81b191782fc61308d51cf88ac0aba6c561fc0212.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/549ef2ab2cbb05e99d689f6ca803b6fab657873d.png).

## 样例 #1

### 输入

```
8
1 3 1 7
Barcelona 158
Milan 90
Spartak 46
Anderlecht 48
Celtic 32
Benfica 87
Zenit 79
Malaga 16

```

### 输出

```
Group A:
Barcelona
Benfica
Spartak
Celtic
Group B:
Milan
Zenit
Anderlecht
Malaga

```



---

---
title: "New Year Ratings Change"
layout: "post"
diff: 普及/提高-
pid: CF379C
tag: ['递推', '排序', '期望']
---

# New Year Ratings Change

## 题目描述

One very well-known internet resource site (let's call it X) has come up with a New Year adventure. Specifically, they decided to give ratings to all visitors.

There are $ n $ users on the site, for each user we know the rating value he wants to get as a New Year Present. We know that user $ i $ wants to get at least $ a_{i} $ rating units as a present.

The X site is administered by very creative and thrifty people. On the one hand, they want to give distinct ratings and on the other hand, the total sum of the ratings in the present must be as small as possible.

Help site X cope with the challenging task of rating distribution. Find the optimal distribution.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=3·10^{5}) $ — the number of users on the site. The next line contains integer sequence $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ .

## 输出格式

Print a sequence of integers $ b_{1},b_{2},...,b_{n} $ . Number $ b_{i} $ means that user $ i $ gets $ b_{i} $ of rating as a present. The printed sequence must meet the problem conditions.

If there are multiple optimal solutions, print any of them.

## 样例 #1

### 输入

```
3
5 1 1

```

### 输出

```
5 1 2

```

## 样例 #2

### 输入

```
1
1000000000

```

### 输出

```
1000000000

```



---

---
title: "Jeopardy!"
layout: "post"
diff: 普及/提高-
pid: CF413C
tag: ['贪心', '排序']
---

# Jeopardy!

## 题目描述

题意简述

“Jeopardy！”的决赛将有n问题，每个问题都有对应的得分ai，其中有m个问题可以选择不得分，而将现有总得分翻倍。你可以安排关卡的通过顺序和策略，求最大得分。

## 输入格式

第一行包含两个整数。n和m(1<=n，m<=100；m<=min(n，30))分别代表问题总数和可翻倍问题总数。第二行包含n个整数a1,a2,...,an(1<=ai<=1e7)代表每个问题的价值；第三行包含m个整数b1,b2,...,bm(1<=bi<=n)代表可翻倍问题的编号。问题编号是从1到n。

## 输出格式

一行一个数字，表示通过所有关卡最大得分。保证该答案在64位带符号整型范围内。

感谢@Peter_Matthew 提供的翻译

## 样例 #1

### 输入

```
4 1
1 3 7 5
3

```

### 输出

```
18

```

## 样例 #2

### 输入

```
3 2
10 3 8
2 3

```

### 输出

```
40

```

## 样例 #3

### 输入

```
2 2
100 200
1 2

```

### 输出

```
400

```



---

---
title: "Physical Education"
layout: "post"
diff: 普及/提高-
pid: CF53D
tag: ['排序']
---

# Physical Education

## 题目描述

Vasya is a school PE teacher. Unlike other PE teachers, Vasya doesn't like it when the students stand in line according to their height. Instead, he demands that the children stand in the following order: $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ is the height of the $ i $ -th student in the line and $ n $ is the number of students in the line. The children find it hard to keep in mind this strange arrangement, and today they formed the line in the following order: $ b_{1},b_{2},...,b_{n} $ , which upset Vasya immensely. Now Vasya wants to rearrange the children so that the resulting order is like this: $ a_{1},a_{2},...,a_{n} $ . During each move Vasya can swap two people who stand next to each other in the line. Help Vasya, find the sequence of swaps leading to the arrangement Vasya needs. It is not required to minimize the number of moves.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=300 $ ) which is the number of students. The second line contains $ n $ space-separated integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ) which represent the height of the student occupying the $ i $ -th place must possess. The third line contains $ n $ space-separated integers $ b_{i} $ ( $ 1<=b_{i}<=10^{9} $ ) which represent the height of the student occupying the $ i $ -th place in the initial arrangement. It is possible that some students possess similar heights. It is guaranteed that it is possible to arrange the children in the required order, i.e. $ a $ and $ b $ coincide as multisets.

## 输出格式

In the first line print an integer $ k $ ( $ 0<=k<=10^{6} $ ) which is the number of moves. It is not required to minimize $ k $ but it must not exceed $ 10^{6} $ . Then print $ k $ lines each containing two space-separated integers. Line $ p_{i} $ , $ p_{i}+1 $ ( $ 1<=p_{i}<=n-1 $ ) means that Vasya should swap students occupying places $ p_{i} $ and $ p_{i+1} $ .

## 样例 #1

### 输入

```
4
1 2 3 2
3 2 1 2

```

### 输出

```
4
2 3
1 2
3 4
2 3

```

## 样例 #2

### 输入

```
2
1 100500
1 100500

```

### 输出

```
0

```



---

---
title: "Sorting Railway Cars"
layout: "post"
diff: 普及/提高-
pid: CF605A
tag: ['排序']
---

# Sorting Railway Cars

## 题目描述

An infinitely long railway has a train consisting of $ n $ cars, numbered from $ 1 $ to $ n $ (the numbers of all the cars are distinct) and positioned in arbitrary order. David Blaine wants to sort the railway cars in the order of increasing numbers. In one move he can make one of the cars disappear from its place and teleport it either to the beginning of the train, or to the end of the train, at his desire. What is the minimum number of actions David Blaine needs to perform in order to sort the train?

## 输入格式

The first line of the input contains integer $ n $ ( $ 1<=n<=100000 $ ) — the number of cars in the train.

The second line contains $ n $ integers $ p_{i} $ ( $ 1<=p_{i}<=n $ , $ p_{i}≠p_{j} $ if $ i≠j $ ) — the sequence of the numbers of the cars in the train.

## 输出格式

Print a single integer — the minimum number of actions needed to sort the railway cars.

## 说明/提示

In the first sample you need first to teleport the $ 4 $ -th car, and then the $ 5 $ -th car to the end of the train.

## 样例 #1

### 输入

```
5
4 1 2 5 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4
4 1 3 2

```

### 输出

```
2

```



---

---
title: "String Game"
layout: "post"
diff: 普及/提高-
pid: CF778A
tag: ['字符串', '排序']
---

# String Game

## 题目描述

Little Nastya has a hobby, she likes to remove some letters from word, to obtain another word. But it turns out to be pretty hard for her, because she is too young. Therefore, her brother Sergey always helps her.

Sergey gives Nastya the word $ t $ and wants to get the word $ p $ out of it. Nastya removes letters in a certain order (one after another, in this order strictly), which is specified by permutation of letters' indices of the word $ t $ : $ a_{1}...\ a_{|t|} $ . We denote the length of word $ x $ as $ |x| $ . Note that after removing one letter, the indices of other letters don't change. For example, if $ t= $ "nastya" and $ a=[4,1,5,3,2,6] $ then removals make the following sequence of words "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya".

Sergey knows this permutation. His goal is to stop his sister at some point and continue removing by himself to get the word $ p $ . Since Nastya likes this activity, Sergey wants to stop her as late as possible. Your task is to determine, how many letters Nastya can remove before she will be stopped by Sergey.

It is guaranteed that the word $ p $ can be obtained by removing the letters from word $ t $ .

## 输入格式

The first and second lines of the input contain the words $ t $ and $ p $ , respectively. Words are composed of lowercase letters of the Latin alphabet ( $ 1<=|p|&lt;|t|<=200000 $ ). It is guaranteed that the word $ p $ can be obtained by removing the letters from word $ t $ .

Next line contains a permutation $ a_{1},a_{2},...,a_{|t|} $ of letter indices that specifies the order in which Nastya removes letters of $ t $ ( $ 1<=a_{i}<=|t| $ , all $ a_{i} $ are distinct).

## 输出格式

Print a single integer number, the maximum number of letters that Nastya can remove.

## 说明/提示

In the first sample test sequence of removing made by Nastya looks like this:

"ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba"

Nastya can not continue, because it is impossible to get word "abb" from word "ababcba".

So, Nastya will remove only three letters.

## 样例 #1

### 输入

```
ababcba
abb
5 3 4 1 7 6 2

```

### 输出

```
3
```

## 样例 #2

### 输入

```
bbbabb
bb
1 6 3 4 2 5

```

### 输出

```
4
```



---

---
title: "The Monster"
layout: "post"
diff: 普及/提高-
pid: CF787A
tag: ['模拟', '排序', '中国剩余定理 CRT']
---

# The Monster

## 题目描述

A monster is chasing after Rick and Morty on another planet. They're so frightened that sometimes they scream. More accurately, Rick screams at times $ b,b+a,b+2a,b+3a,... $ and Morty screams at times $ d,d+c,d+2c,d+3c,... $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF787A/23c11249630f1c4252ef0b9cda8ec1bf9b317b5a.png)The Monster will catch them if at any point they scream at the same time, so it wants to know when it will catch them (the first time they scream at the same time) or that they will never scream at the same time.

## 输入格式

The first line of input contains two integers $ a $ and $ b $ ( $ 1<=a,b<=100 $ ).

The second line contains two integers $ c $ and $ d $ ( $ 1<=c,d<=100 $ ).

## 输出格式

Print the first time Rick and Morty will scream at the same time, or $ -1 $ if they will never scream at the same time.

## 说明/提示

In the first sample testcase, Rick's $ 5 $ th scream and Morty's $ 8 $ th time are at time $ 82 $ .

In the second sample testcase, all Rick's screams will be at odd times and Morty's will be at even times, so they will never scream at the same time.

## 样例 #1

### 输入

```
20 2
9 19

```

### 输出

```
82

```

## 样例 #2

### 输入

```
2 1
16 12

```

### 输出

```
-1

```



---

---
title: "Planning"
layout: "post"
diff: 普及/提高-
pid: CF853A
tag: ['贪心', '线段树', '排序']
---

# Planning

## 题目描述

Helen在大都会机场工作，她的任务是安排每天的航班起飞时刻。今天一共有n架飞机将要起飞，第i架飞机将在第i分钟起飞。

大都会机场是大都会最重要的交通枢纽，因此想要原封不动地按照起飞时刻表的时刻起飞是很困难的。今天的情况也是如此：由于技术原因，在今天一开始的k分钟内飞机不允许起飞，因此必须创建一个新的起飞时刻表。

所有的航班必须在第(k+1)分钟到第(k+n)分钟内(包括两端)起飞，而且每分钟仅能有一架飞机起飞。然而，航班起飞的先后顺序可以与最初的时刻表排好的顺序不同，重排的时刻表只有一个限制：飞机不能比它在初始时刻表中起飞的时刻还要早的时刻起飞(即：第i架飞机必须在第i分钟后或第i分钟时起飞)。

Helen知道第i架飞机起飞时刻每延误一分钟机场所需支付的额外花费ci是多少。帮助她找到额外花费最小的方案。

## 输入格式

输入数据的第一行包括两个整数n和k(1<=k<=n<=300000)。

第二行包括n个整数c1，c2，...，cn(1<=ci<=10^7).

## 输出格式

输出数据的第一行包括一个整数，表示最小额外花费。

第二行包括n个整数t1，t2，...，tn(k+1<=ti<=k+n)，ti表示第i架家航班起飞的时刻。如果同时存在多种方案，输出任意一种。

## 说明/提示

在样例中，如果Helen仅把每架飞机的起飞时刻都推迟2分钟，那么总额外花费是38。
但是，对于最佳结果来说，总额外花费为20。

感谢@radish布団  提供的翻译

## 样例 #1

### 输入

```
5 2
4 2 1 10 2

```

### 输出

```
20
3 6 7 4 5 

```



---

---
title: "Minimum Sum"
layout: "post"
diff: 普及/提高-
pid: CF910C
tag: ['贪心', '排序', '进制']
---

# Minimum Sum

## 题目描述

Petya 有一个长度为n的正整数序列 $a_{1},a_{2},...,a_{n}$。他的朋友Vasya 想要捉弄他，Vasya用一个字母替换了Petya 的号码中的所有数字。

他用小写字母‘a’到‘j’中的一个字母替换了所有数字 0，用另一个字母替换了所有 1，依次类推。对于不同的两个数字，Vasya 用‘a’到‘j’中不同的字母。

你的任务是还原 Petya 的序列。还原得到的数字应是没有前导零（数字开头没有零）的正整数。由于可能有多种方式实现，所以要求恢复后的序列总和最小。保证初始时序列中数字没有前导零。

## 输入格式

第一行包含一个数字n。

之后的每一行包含一个由小写字母‘a’到‘j’构成非空字符串，每个字符串长度不超过六个字符。

## 输出格式

恢复后的序列的和的最小值。保证有解。

Translated by Fowany

## 样例 #1

### 输入

```
3
ab
de
aj

```

### 输出

```
47

```

## 样例 #2

### 输入

```
5
abcdef
ghij
bdef
accbd
g

```

### 输出

```
136542

```

## 样例 #3

### 输入

```
3
aa
jj
aa

```

### 输出

```
44

```



---

---
title: "Substring"
layout: "post"
diff: 普及/提高-
pid: CF919D
tag: ['排序', '拓扑排序']
---

# Substring

## 题目描述

You are given a graph with $ n $ nodes and $ m $ directed edges. One lowercase letter is assigned to each node. We define a path's value as the number of the most frequently occurring letter. For example, if letters on a path are "abaca", then the value of that path is $ 3 $ . Your task is find a path whose value is the largest.

## 输入格式

The first line contains two positive integers $ n,m $ ( $ 1<=n,m<=300000 $ ), denoting that the graph has $ n $ nodes and $ m $ directed edges.

The second line contains a string $ s $ with only lowercase English letters. The $ i $ -th character is the letter assigned to the $ i $ -th node.

Then $ m $ lines follow. Each line contains two integers $ x,y $ ( $ 1<=x,y<=n $ ), describing a directed edge from $ x $ to $ y $ . Note that $ x $ can be equal to $ y $ and there can be multiple edges between $ x $ and $ y $ . Also the graph can be not connected.

## 输出格式

Output a single line with a single integer denoting the largest value. If the value can be arbitrarily large, output -1 instead.

## 说明/提示

In the first sample, the path with largest value is $ 1→3→4→5 $ . The value is $ 3 $ because the letter 'a' appears $ 3 $ times.

## 样例 #1

### 输入

```
5 4
abaca
1 2
1 3
3 4
4 5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
6 6
xzyabc
1 2
3 1
2 3
5 4
4 3
6 4

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
10 14
xzyzyzyzqx
1 2
2 4
3 5
4 5
2 6
6 8
6 5
2 10
3 9
10 9
4 6
1 10
2 8
3 7

```

### 输出

```
4

```



---

---
title: "Merge Equals"
layout: "post"
diff: 普及/提高-
pid: CF962D
tag: ['排序', '优先队列', '队列']
---

# Merge Equals

## 题目描述

You are given an array of positive integers. While there are at least two equal elements, we will perform the following operation. We choose the smallest value $ x $ that occurs in the array $ 2 $ or more times. Take the first two occurrences of $ x $ in this array (the two leftmost occurrences). Remove the left of these two occurrences, and the right one is replaced by the sum of this two values (that is, $ 2 \cdot x $ ).

Determine how the array will look after described operations are performed.

For example, consider the given array looks like $ [3, 4, 1, 2, 2, 1, 1] $ . It will be changed in the following way: $ [3, 4, 1, 2, 2, 1, 1]~\rightarrow~[3, 4, 2, 2, 2, 1]~\rightarrow~[3, 4, 4, 2, 1]~\rightarrow~[3, 8, 2, 1] $ .

If the given array is look like $ [1, 1, 3, 1, 1] $ it will be changed in the following way: $ [1, 1, 3, 1, 1]~\rightarrow~[2, 3, 1, 1]~\rightarrow~[2, 3, 2]~\rightarrow~[3, 4] $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 150\,000 $ ) — the number of elements in the array.

The second line contains a sequence from $ n $ elements $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^{9} $ ) — the elements of the array.

## 输出格式

In the first line print an integer $ k $ — the number of elements in the array after all the performed operations. In the second line print $ k $ integers — the elements of the array after all the performed operations.

## 说明/提示

The first two examples were considered in the statement.

In the third example all integers in the given array are distinct, so it will not change.

## 样例 #1

### 输入

```
7
3 4 1 2 2 1 1

```

### 输出

```
4
3 8 2 1 

```

## 样例 #2

### 输入

```
5
1 1 3 1 1

```

### 输出

```
2
3 4 

```

## 样例 #3

### 输入

```
5
10 40 20 50 30

```

### 输出

```
5
10 40 20 50 30 

```



---

---
title: "Nested Segments"
layout: "post"
diff: 普及/提高-
pid: CF976C
tag: ['树状数组', '排序']
---

# Nested Segments

## 题目描述

##### 【题目大意】：

你得到了一个序列$a_1,a_2,a_3...a_n$，表示$n$个区间。你的任务是求出一对$(i,j)$，表示区间$j$包含区间$i$（注意是区间$j$包含$i$）。

我们定义区间$[l_2,r_2]$包含区间$[l_1,r_1]$当且仅当$l_1 \geq l_2$且$r_1 \leq r_2$。比如区间$[2,5]$包含区间$[3,5]$，因为$3 \geq 2,5 \leq 5$。再比如区间$[2,5]$不包含区间$[1,4]$，因为$1<2$。

输出一对$(i,j)$表示答案。如果答案不唯一，则输出任意一组解即可（所以本题有`SPJ`）。如果无解，则输出`-1 -1`。

--------------------------------------

## 输入格式

第一行一个整数$n(1 \leq n \leq 3 \times 10^5)$，表示区间的个数。

以下$n$行，每行两个数$l,r$，表示一个区间的左右端点。$1 \leq l \leq r \leq 1 \times 10^9$。

----------------------------------

## 输出格式

一行两个数$(i,j)$，表示答案。如果有多解，输出任意一组解即可。如果无解，输出`-1 -1`。

--------------------------------------

翻译至`HPXXZYY`。

## 样例 #1

### 输入

```
5
1 10
2 9
3 9
2 3
2 9

```

### 输出

```
2 1

```

## 样例 #2

### 输入

```
3
1 5
2 6
6 20

```

### 输出

```
-1 -1

```



---

---
title: "Petya's Exams"
layout: "post"
diff: 普及/提高-
pid: CF978G
tag: ['模拟', '贪心', '排序']
---

# Petya's Exams

## 题目描述

Petya studies at university. The current academic year finishes with $ n $ special days. Petya needs to pass $ m $ exams in those special days. The special days in this problem are numbered from $ 1 $ to $ n $ .

There are three values about each exam:

- $ s_i $ — the day, when questions for the $ i $ -th exam will be published,
- $ d_i $ — the day of the $ i $ -th exam ( $ s_i < d_i $ ),
- $ c_i $ — number of days Petya needs to prepare for the $ i $ -th exam. For the $ i $ -th exam Petya should prepare in days between $ s_i $ and $ d_i-1 $ , inclusive.

There are three types of activities for Petya in each day: to spend a day doing nothing (taking a rest), to spend a day passing exactly one exam or to spend a day preparing for exactly one exam. So he can't pass/prepare for multiple exams in a day. He can't mix his activities in a day. If he is preparing for the $ i $ -th exam in day $ j $ , then $ s_i \le j < d_i $ .

It is allowed to have breaks in a preparation to an exam and to alternate preparations for different exams in consecutive days. So preparation for an exam is not required to be done in consecutive days.

Find the schedule for Petya to prepare for all exams and pass them, or report that it is impossible.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (2 \le n \le 100, 1 \le m \le n) $ — the number of days and the number of exams.

Each of the following $ m $ lines contains three integers $ s_i $ , $ d_i $ , $ c_i $ $ (1 \le s_i < d_i \le n, 1 \le c_i \le n) $ — the day, when questions for the $ i $ -th exam will be given, the day of the $ i $ -th exam, number of days Petya needs to prepare for the $ i $ -th exam.

Guaranteed, that all the exams will be in different days. Questions for different exams can be given in the same day. It is possible that, in the day of some exam, the questions for other exams are given.

## 输出格式

If Petya can not prepare and pass all the exams, print -1. In case of positive answer, print $ n $ integers, where the $ j $ -th number is:

- $ (m + 1) $ , if the $ j $ -th day is a day of some exam (recall that in each day no more than one exam is conducted),
- zero, if in the $ j $ -th day Petya will have a rest,
- $ i $ ( $ 1 \le i \le m $ ), if Petya will prepare for the $ i $ -th exam in the day $ j $ (the total number of days Petya prepares for each exam should be strictly equal to the number of days needed to prepare for it).Assume that the exams are numbered in order of appearing in the input, starting from $ 1 $ .
  
  If there are multiple schedules, print any of them.

## 说明/提示

In the first example Petya can, for example, prepare for exam $ 1 $ in the first day, prepare for exam $ 2 $ in the second day, pass exam $ 1 $ in the third day, relax in the fourth day, and pass exam $ 2 $ in the fifth day. So, he can prepare and pass all exams.

In the second example, there are three days and two exams. So, Petya can prepare in only one day (because in two other days he should pass exams). Then Petya can not prepare and pass all exams.

## 样例 #1

### 输入

```
5 2
1 3 1
1 5 1

```

### 输出

```
1 2 3 0 3 

```

## 样例 #2

### 输入

```
3 2
1 3 1
1 2 1

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
10 3
4 7 2
1 10 3
8 9 1

```

### 输出

```
2 2 2 1 1 0 4 3 4 4 

```



---

