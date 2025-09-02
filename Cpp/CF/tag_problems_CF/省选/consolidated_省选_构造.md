---
title: "Recovering BST"
layout: "post"
diff: 省选/NOI-
pid: CF1025D
tag: ['搜索', '构造']
---

# Recovering BST

## 题目描述

Dima the hamster enjoys nibbling different things: cages, sticks, bad problemsetters and even trees!

Recently he found a binary search tree and instinctively nibbled all of its edges, hence messing up the vertices. Dima knows that if Andrew, who has been thoroughly assembling the tree for a long time, comes home and sees his creation demolished, he'll get extremely upset.

To not let that happen, Dima has to recover the binary search tree. Luckily, he noticed that any two vertices connected by a direct edge had their greatest common divisor value exceed $ 1 $ .

Help Dima construct such a binary search tree or determine that it's impossible. The definition and properties of a binary search tree can be found [here.](https://en.wikipedia.org/wiki/Binary_search_tree)

## 输入格式

The first line contains the number of vertices $ n $ ( $ 2 \le n \le 700 $ ).

The second line features $ n $ distinct integers $ a_i $ ( $ 2 \le a_i \le 10^9 $ ) — the values of vertices in ascending order.

## 输出格式

If it is possible to reassemble the binary search tree, such that the greatest common divisor of any two vertices connected by the edge is greater than $ 1 $ , print "Yes" (quotes for clarity).

Otherwise, print "No" (quotes for clarity).

## 说明/提示

The picture below illustrates one of the possible trees for the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1025D/a6281ebfc3addc046e3a216e978640a7d00d938f.png)The picture below illustrates one of the possible trees for the third example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1025D/422d22e6560dde35033dafdd73125c60e4d294d8.png)

## 样例 #1

### 输入

```
6
3 6 9 18 36 108

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
2
7 17

```

### 输出

```
No

```

## 样例 #3

### 输入

```
9
4 8 10 12 15 18 33 44 81

```

### 输出

```
Yes

```



---

---
title: "Relatively Prime Powers"
layout: "post"
diff: 省选/NOI-
pid: CF1036F
tag: ['排序', '构造']
---

# Relatively Prime Powers

## 题目描述

Consider some positive integer $ x $ . Its prime factorization will be of form $ x = 2^{k_1} \cdot 3^{k_2} \cdot 5^{k_3} \cdot \dots $

Let's call $ x $ elegant if the greatest common divisor of the sequence $ k_1, k_2, \dots $ is equal to $ 1 $ . For example, numbers $ 5 = 5^1 $ , $ 12 = 2^2 \cdot 3 $ , $ 72 = 2^3 \cdot 3^2 $ are elegant and numbers $ 8 = 2^3 $ ( $ GCD = 3 $ ), $ 2500 = 2^2 \cdot 5^4 $ ( $ GCD = 2 $ ) are not.

Count the number of elegant integers from $ 2 $ to $ n $ .

Each testcase contains several values of $ n $ , for each of them you are required to solve the problem separately.

## 输入格式

The first line contains a single integer $ T $ ( $ 1 \le T \le 10^5 $ ) — the number of values of $ n $ in the testcase.

Each of the next $ T $ lines contains a single integer $ n_i $ ( $ 2 \le n_i \le 10^{18} $ ).

## 输出格式

Print $ T $ lines — the $ i $ -th line should contain the number of elegant numbers from $ 2 $ to $ n_i $ .

## 说明/提示

Here is the list of non-elegant numbers up to $ 10 $ :

- $ 4 = 2^2, GCD = 2 $ ;
- $ 8 = 2^3, GCD = 3 $ ;
- $ 9 = 3^2, GCD = 2 $ .

The rest have $ GCD = 1 $ .

## 样例 #1

### 输入

```
4
4
2
72
10

```

### 输出

```
2
1
61
6

```



---

---
title: "Nature Reserve"
layout: "post"
diff: 省选/NOI-
pid: CF1059D
tag: ['构造']
---

# Nature Reserve

## 题目描述

There is a forest that we model as a plane and live $ n $ rare animals. Animal number $ i $ has its lair in the point $ (x_{i}, y_{i}) $ . In order to protect them, a decision to build a nature reserve has been made.

The reserve must have a form of a circle containing all lairs. There is also a straight river flowing through the forest. All animals drink from this river, therefore it must have at least one common point with the reserve. On the other hand, ships constantly sail along the river, so the reserve must not have more than one common point with the river.

For convenience, scientists have made a transformation of coordinates so that the river is defined by $ y = 0 $ . Check whether it is possible to build a reserve, and if possible, find the minimum possible radius of such a reserve.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of animals.

Each of the next $ n $ lines contains two integers $ x_{i} $ , $ y_{i} $ ( $ -10^7 \le x_{i}, y_{i} \le 10^7 $ ) — the coordinates of the $ i $ -th animal's lair. It is guaranteed that $ y_{i} \neq 0 $ . No two lairs coincide.

## 输出格式

If the reserve cannot be built, print $ -1 $ . Otherwise print the minimum radius. Your answer will be accepted if absolute or relative error does not exceed $ 10^{-6} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer is considered correct if $ \frac{|a - b|}{\max{(1, |b|)}} \le 10^{-6} $ .

## 说明/提示

In the first sample it is optimal to build the reserve with the radius equal to $ 0.5 $ and the center in $ (0,\ 0.5) $ .

In the second sample it is impossible to build a reserve.

In the third sample it is optimal to build the reserve with the radius equal to $ \frac{5}{8} $ and the center in $ (\frac{1}{2},\ \frac{5}{8}) $ .

## 样例 #1

### 输入

```
1
0 1

```

### 输出

```
0.5
```

## 样例 #2

### 输入

```
3
0 1
0 2
0 -3

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
2
0 1
1 1

```

### 输出

```
0.625
```



---

---
title: "Odd Federalization"
layout: "post"
diff: 省选/NOI-
pid: CF1070L
tag: ['高斯消元', '构造']
---

# Odd Federalization

## 题目描述

Berland has $ n $ cities, some of which are connected by roads. Each road is bidirectional, connects two distinct cities and for each two cities there's at most one road connecting them.

The president of Berland decided to split country into $ r $ states in such a way that each city will belong to exactly one of these $ r $ states.

After this split each road will connect either cities of the same state or cities of the different states. Let's call roads that connect two cities of the same state "inner" roads.

The president doesn't like odd people, odd cities and odd numbers, so he wants this split to be done in such a way that each city would have even number of "inner" roads connected to it.

Please help president to find smallest possible $ r $ for which such a split exists.

## 输入格式

The input contains one or several test cases. The first input line contains a single integer number $ t $ — number of test cases. Then, $ t $ test cases follow. Solve test cases separately, test cases are completely independent and do not affect each other.

Then $ t $ blocks of input data follow. Each block starts from empty line which separates it from the remaining input data. The second line of each block contains two space-separated integers $ n $ , $ m $ ( $ 1 \le n \le 2000 $ , $ 0 \le m \le 10000 $ ) — the number of cities and number of roads in the Berland. Each of the next $ m $ lines contains two space-separated integers — $ x_i $ , $ y_i $ ( $ 1 \le x_i, y_i \le n $ ; $ x_i \ne y_i $ ), which denotes that the $ i $ -th road connects cities $ x_i $ and $ y_i $ . Each pair of cities are connected by at most one road.

Sum of values $ n $ across all test cases doesn't exceed $ 2000 $ . Sum of values $ m $ across all test cases doesn't exceed $ 10000 $ .

## 输出格式

For each test case first print a line containing a single integer $ r $ — smallest possible number of states for which required split is possible. In the next line print $ n $ space-separated integers in range from $ 1 $ to $ r $ , inclusive, where the $ j $ -th number denotes number of state for the $ j $ -th city. If there are multiple solutions, print any.

## 样例 #1

### 输入

```
2
 
5 3
1 2
2 5
1 5
 
6 5
1 2
2 3
3 4
4 2
4 1

```

### 输出

```
1
1 1 1 1 1 
2
2 1 1 1 1 1

```



---

---
title: "Construct the Binary Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1311E
tag: ['贪心', '构造']
---

# Construct the Binary Tree

## 题目描述

You are given two integers $ n $ and $ d $ . You need to construct a rooted binary tree consisting of $ n $ vertices with a root at the vertex $ 1 $ and the sum of depths of all vertices equals to $ d $ .

A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. A parent of a vertex $ v $ is the last different from $ v $ vertex on the path from the root to the vertex $ v $ . The depth of the vertex $ v $ is the length of the path from the root to the vertex $ v $ . Children of vertex $ v $ are all vertices for which $ v $ is the parent. The binary tree is such a tree that no vertex has more than $ 2 $ children.

You have to answer $ t $ independent test cases.

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The only line of each test case contains two integers $ n $ and $ d $ ( $ 2 \le n, d \le 5000 $ ) — the number of vertices in the tree and the required sum of depths of all vertices.

It is guaranteed that the sum of $ n $ and the sum of $ d $ both does not exceed $ 5000 $ ( $ \sum n \le 5000, \sum d \le 5000 $ ).

## 输出格式

For each test case, print the answer.

If it is impossible to construct such a tree, print "NO" (without quotes) in the first line. Otherwise, print "{YES}" in the first line. Then print $ n-1 $ integers $ p_2, p_3, \dots, p_n $ in the second line, where $ p_i $ is the parent of the vertex $ i $ . Note that the sequence of parents you print should describe some binary tree.

## 说明/提示

Pictures corresponding to the first and the second test cases of the example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1311E/514e626aa001052fb71d69f413a53a8e6f0cb5f0.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1311E/6407c12a699d89084b087667ed6f21f3aeed074d.png)

## 样例 #1

### 输入

```
3
5 7
10 19
10 18
```

### 输出

```
YES
1 2 1 3 
YES
1 2 3 3 9 9 2 1 6 
NO
```



---

---
title: "Mastermind"
layout: "post"
diff: 省选/NOI-
pid: CF1381C
tag: ['构造']
---

# Mastermind

## 题目描述

In the game of Mastermind, there are two players — Alice and Bob. Alice has a secret code, which Bob tries to guess. Here, a code is defined as a sequence of $ n $ colors. There are exactly $ n+1 $ colors in the entire universe, numbered from $ 1 $ to $ n+1 $ inclusive.

When Bob guesses a code, Alice tells him some information about how good of a guess it is, in the form of two integers $ x $ and $ y $ .

The first integer $ x $ is the number of indices where Bob's guess correctly matches Alice's code. The second integer $ y $ is the size of the intersection of the two codes as multisets. That is, if Bob were to change the order of the colors in his guess, $ y $ is the maximum number of indices he could get correct.

For example, suppose $ n=5 $ , Alice's code is $ [3,1,6,1,2] $ , and Bob's guess is $ [3,1,1,2,5] $ . At indices $ 1 $ and $ 2 $ colors are equal, while in the other indices they are not equal. So $ x=2 $ . And the two codes have the four colors $ 1,1,2,3 $ in common, so $ y=4 $ .

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1381C/0a0bf21772b2a037969dab6b2775ca2f40f3672c.png) Solid lines denote a matched color for the same index. Dashed lines denote a matched color at a different index. $ x $ is the number of solid lines, and $ y $ is the total number of lines. You are given Bob's guess and two values $ x $ and $ y $ . Can you find one possibility of Alice's code so that the values of $ x $ and $ y $ are correct?

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le       1000 $ ) — the number of test cases. Next $ 2t $ lines contain descriptions of test cases.

The first line of each test case contains three integers $ n,x,y $ ( $ 1\le n\le 10^5, 0\le x\le y\le n $ ) — the length of the codes, and two values Alice responds with.

The second line of each test case contains $ n $ integers $ b_1,\ldots,b_n $ ( $ 1\le b_i\le n+1 $ ) — Bob's guess, where $ b_i $ is the $ i $ -th color of the guess.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, on the first line, output "YES" if there is a solution, or "NO" if there is no possible secret code consistent with the described situation. You can print each character in any case (upper or lower).

If the answer is "YES", on the next line output $ n $ integers $ a_1,\ldots,a_n $ ( $ 1\le a_i\le       n+1 $ ) — Alice's secret code, where $ a_i $ is the $ i $ -th color of the code.

If there are multiple solutions, output any.

## 说明/提示

The first test case is described in the statement.

In the second test case, $ x=3 $ because the colors are equal at indices $ 2,4,5 $ . And $ y=4 $ because they share the colors $ 1,1,1,2 $ .

In the third test case, $ x=0 $ because there is no index where the colors are the same. But $ y=4 $ because they share the colors $ 3,3,5,5 $ .

In the fourth test case, it can be proved that no solution exists.

## 样例 #1

### 输入

```
7
5 2 4
3 1 1 2 5
5 3 4
1 1 2 1 2
4 0 4
5 5 3 3
4 1 4
2 3 2 3
6 1 2
3 2 1 1 1 1
6 2 4
3 3 2 1 1 1
6 2 6
1 1 3 2 1 1
```

### 输出

```
YES
3 1 6 1 2
YES
3 1 1 1 2
YES
3 3 5 5
NO
YES
4 4 4 4 3 1
YES
3 1 3 1 7 7
YES
2 3 1 1 1 1
```



---

---
title: "Magnets"
layout: "post"
diff: 省选/NOI-
pid: CF1491F
tag: ['二分', '构造']
---

# Magnets

## 题目描述

This is an interactive problem.

Kochiya Sanae is playing with magnets. Realizing that some of those magnets are demagnetized, she is curious to find them out.

There are $ n $ magnets, which can be of the following $ 3 $ types:

- N
- S
- - — these magnets are demagnetized.

Note that you don't know the types of these magnets beforehand.

You have a machine which can measure the force between the magnets, and you can use it at most $ n+\lfloor \log_2n\rfloor $ times.

You can put some magnets to the left part of the machine and some to the right part of the machine, and launch the machine. Obviously, you can put one magnet to at most one side (you don't have to put all magnets). You can put the same magnet in different queries.

Then the machine will tell the force these magnets produce. Formally, let $ n_1,s_1 $ be the number of N and S magnets correspondently on the left and $ n_2,s_2 $ — on the right. Then the force between them would be $ n_1n_2+s_1s_2-n_1s_2-n_2s_1 $ . Please note that the force is a signed value.

However, when the absolute value of the force is strictly larger than $ n $ , the machine will crash into pieces.

You need to find all magnets of type - (all demagnetized ones), without breaking the machine.

Note that the interactor is not adaptive. The types of the magnets are fixed before the start of the interaction and do not change with queries.

It is guaranteed that there are at least $ 2 $ magnets whose type is not -, and at least $ 1 $ magnet of type -.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

## 输出格式

For each test case you should start by reading an integer $ n $ ( $ 3 \leq n \leq 2000 $ ) — the number of the magnets.

It is guaranteed that the total sum of all $ n $ over all test cases doesn't exceed $ 2000 $ .

After that you can put some magnets into the machine and make a query from the statement.

You have to print each query in three lines:

- In the first line print "? l r" (without quotes) where $ l $ and $ r $ ( $ 1 \leq l,r < n $ , $ l+r \leq n $ ) respectively denote the number of the magnets you put to left and right.
- In the second line print $ l $ integers $ a_1, \dots, a_l $ ( $ 1 \leq a_i \leq n $ , $ a_i \neq a_j $ if $ i \neq j $ ) — the indices of the magnets you put to left.
- In the third line print $ r $ integers $ b_1, \dots, b_r $ ( $ 1 \leq b_i \leq n $ , $ b_i \neq b_j $ if $ i \neq j $ ) — the indices of the magnets you put to right.
- The same magnet can't be put to both sides in the same query. Formally, you should guarantee that $ a_i \neq b_j $ for any $ i $ and $ j $ . However, you may leave some magnets unused.

After printing a query do not forget to output end of line and flush the output. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

After this, you should read an integer $ F $ — the force these magnets produce.

Note that if your query is invalid(either the query limit exceeds, the machine crashes or the arguments are invalid), the interactor will terminate immediately. In this case terminate your program to receive verdict Wrong Answer instead of arbitrary verdicts.

If you are confident about your answer, use the following format to report it:

- "! k A", where $ k $ is the number of magnets you found, and $ A $ is an array consisting of $ k $ different integers from $ 1 $ to $ n $ denoting the indices of the magnets of type - that you found. You may print elements of $ A $ in arbitrary order.
- After that, if this is the last test case, you have to terminate your program; otherwise you should immediately continue to deal with the next test case.

Note that the interactor is not adaptive. The types of the magnets are fixed before the start of interaction and do not change with queries.

Hacks

To hack a solution, use the following format:

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases in your hack.

Then follow the descriptions of the $ t $ test cases, each printed in two lines:

- The first line contains a single integer $ n $ ( $ 3 \leq n \leq 2000 $ ) — the number of magnets.
- The second line contains a string $ S $ of length $ n $ consisting of only N, S and -, denoting the magnets' types.
- Each of your test case should guarantee that there are at least $ 2 $ magnets whose type is not -, and at least $ 1 $ magnet of type -. Meanwhile, the total sum of $ n $ in all test cases should not exceed $ 2000 $ .

## 说明/提示

The empty lines in the sample are just for you to better understand the interaction process. You're not required to print them.

In the sample, the types of the magnets are NN--.

At first, you put the third magnet on the left and the fourth one on the right. Both of them have type -, thus no force is produced.

Then you put the first magnet on the left and the second and third one on the right. The third magnet has type -, while the other two magnets are of type N, so the force produced is $ 1 $ .

In the following two queries, the force is $ 0 $ since there is only a magnet with property - on the right.

Then we can determine that the magnets of type - are the third and the fourth one, so we should print ! 2 3 4 and exit.

## 样例 #1

### 输入

```
1
4



0



1



0



0
```

### 输出

```
? 1 1
3
4

? 1 2
1
2 3

? 1 1
1
4

? 1 1
1
3

! 2 3 4
```



---

---
title: "Switch and Flip"
layout: "post"
diff: 省选/NOI-
pid: CF1491G
tag: ['构造']
---

# Switch and Flip

## 题目描述

There are $ n $ coins labeled from $ 1 $ to $ n $ . Initially, coin $ c_i $ is on position $ i $ and is facing upwards (( $ c_1, c_2, \dots, c_n) $ is a permutation of numbers from $ 1 $ to $ n $ ). You can do some operations on these coins.

In one operation, you can do the following:

- Choose $ 2 $ distinct indices $ i $ and $ j $ .
- Then, swap the coins on positions $ i $ and $ j $ .
- Then, flip both coins on positions $ i $ and $ j $ . (If they are initially faced up, they will be faced down after the operation and vice versa)

Construct a sequence of at most $ n+1 $ operations such that after performing all these operations the coin $ i $ will be on position $ i $ at the end, facing up.

Note that you do not need to minimize the number of operations.

## 输入格式

The first line contains an integer $ n $ ( $ 3 \leq n \leq 2 \cdot 10^5 $ ) — the number of coins.

The second line contains $ n $ integers $ c_1,c_2,\dots,c_n $ ( $ 1 \le c_i \le n $ , $ c_i \neq c_j $ for $ i\neq j $ ).

## 输出格式

In the first line, output an integer $ q $ $ (0 \leq q \leq n+1) $ — the number of operations you used.

In the following $ q $ lines, output two integers $ i $ and $ j $ $ (1 \leq i, j \leq n, i \ne j) $ — the positions you chose for the current operation.

## 说明/提示

Let coin $ i $ facing upwards be denoted as $ i $ and coin $ i $ facing downwards be denoted as $ -i $ .

The series of moves performed in the first sample changes the coins as such:

- $ [~~~2,~~~1,~~~3] $
- $ [-3,~~~1,-2] $
- $ [-3,~~~2,-1] $
- $ [~~~1,~~~2,~~~3] $

In the second sample, the coins are already in their correct positions so there is no need to swap.

## 样例 #1

### 输入

```
3
2 1 3
```

### 输出

```
3
1 3
3 2
3 1
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
0
```



---

---
title: "Half Queen Cover"
layout: "post"
diff: 省选/NOI-
pid: CF1667C
tag: ['构造']
---

# Half Queen Cover

## 题目描述

You are given a board with $ n $ rows and $ n $ columns, numbered from $ 1 $ to $ n $ . The intersection of the $ a $ -th row and $ b $ -th column is denoted by $ (a, b) $ .

A half-queen attacks cells in the same row, same column, and on one diagonal. More formally, a half-queen on $ (a, b) $ attacks the cell $ (c, d) $ if $ a=c $ or $ b=d $ or $ a-b=c-d $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1667C/7bd42db06039264b9144129e45c89b4a8730a512.png)The blue cells are under attack.  What is the minimum number of half-queens that can be placed on that board so as to ensure that each square is attacked by at least one half-queen?Construct an optimal solution.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the size of the board.

## 输出格式

In the first line print a single integer $ k $ — the minimum number of half-queens.

In each of the next $ k $ lines print two integers $ a_i $ , $ b_i $ ( $ 1 \le a_i, b_i \le n $ ) — the position of the $ i $ -th half-queen.

If there are multiple solutions, print any.

## 说明/提示

Example $ 1 $ : one half-queen is enough. Note: a half-queen on $ (1, 1) $ attacks $ (1, 1) $ .

Example $ 2 $ : one half-queen is enough too. $ (1, 2) $ or $ (2, 1) $ would be wrong solutions, because a half-queen on $ (1, 2) $ does not attack the cell $ (2, 1) $ and vice versa. $ (2, 2) $ is also a valid solution.

Example $ 3 $ : it is impossible to cover the board with one half queen. There are multiple solutions for $ 2 $ half-queens; you can print any of them.

## 样例 #1

### 输入

```
1
```

### 输出

```
1
1 1
```

## 样例 #2

### 输入

```
2
```

### 输出

```
1
1 1
```

## 样例 #3

### 输入

```
3
```

### 输出

```
2
1 1
1 2
```



---

---
title: "Tree Recovery"
layout: "post"
diff: 省选/NOI-
pid: CF1696F
tag: ['构造']
---

# Tree Recovery

## 题目描述

给定一棵 $n$ 个节点的树，节点编号为 $1\sim n$。

树的形态是未知的，但我们知道：
* 所有边的边权都为 $1$。
* $n-1$ 行信息：
	* 第 $i$ 行信息由 $n-i$ 个以空格隔开的 $01$ 字符串组成。
	* 定义 $d(x,y)$ 为树上 $x,y$ 两点之间的距离。我们约定字符串下标从 $1$开始。
   * 对于第 $i$ 行的 第 $j$ 个字符串 $s$，$s_k=0$ 表示 $d(i,k)\neq d(i+j,k)$，$s_k=1$ 表示 $d(i,k)=d(i+j,k)$。

## 输入格式

**本题有多组数据**。
* 第一行是一个整数 $t$，表示数据组数。

对于每组数据：
* 第一行是一个整数 $n$，表示树的节点数量。

## 输出格式

对于每组数据：
* 如果不存在符合要求的树，输出一行，内容为一个字符串 `No`。
* 如果存在符合要求的树，输出 $n$ 行：
	* 第一行输出一个字符串 `Yes`。
   * 接下来 $n-1$ 行，每行输出两个用空格隔开的整数 $x,y$，表示 $x$ 和 $y$ 之间有一条边。
   * 如果符合要求的树的形态不唯一，你可以输出任何一种（原文没有提及边的输出顺序，但样例中是以 $x$ 为第一关键字，$y$ 为第二关键字的字典序升序）。
* 对 `Yes` 和 `No` 大小写不敏感，每个字母都可以以大写或小写输出。

## 说明/提示

对于所有测试点，$t\leqslant 200$，$n\leqslant 100$。

对于每个测试点的多组数据，至多有 $2$ 组数据的 $n>50$，至多有 $5$ 组数据的 $n>20$。

## 样例 #1

### 输入

```
5
2
00
2
10
3
001 000
000
3
001 010
000
5
00000 01001 00000 01100
00000 10000 00000
00000 11010
00000
```

### 输出

```
Yes
1 2
No
Yes
1 3
2 3
No
Yes
1 2
1 4
2 3
2 5
```



---

---
title: "Crop Squares"
layout: "post"
diff: 省选/NOI-
pid: CF1715F
tag: ['构造']
---

# Crop Squares

## 题目描述

This is an interactive problem.

Farmer Stanley grows corn on a rectangular field of size $  n \times m  $ meters with corners in points $ (0, 0) $ , $ (0, m) $ , $ (n, 0) $ , $ (n, m) $ . This year the harvest was plentiful and corn covered the whole field.

The night before harvest aliens arrived and poisoned the corn in a single $ 1 \times 1 $ square with sides parallel to field borders. The corn inside the square must not be eaten, but you cannot distinguish it from ordinary corn by sight. Stanley can only collect a sample of corn from an arbitrary polygon and bring it to the laboratory, where it will be analyzed and Stanley will be told the amount of corn in the sample that was poisoned. Since the harvest will soon deteriorate, such a study can be carried out no more than $ 5 $ times.

More formally, it is allowed to make no more than $ 5 $ queries, each of them calculates the area of intersection of a chosen polygon with a square of poisoned corn. It is necessary to find out the coordinates of the lower-left corner of the drawn square (the vertex of the square with the smallest $ x $ and $ y $ coordinates).

## 输入格式

First line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 100 $ ) — field sizes.

## 输出格式

In order to query the area of intersection of a polygon with $ k $ ( $ 3 \le k \le 1000 $ ) vertices at points with coordinates $ (x_1, y_1),\; \dots ,\;(x_k, y_k) $ with a square of poisoned corn print $ k+1 $ lines. In the first of these lines print "? k". In the $ i $ -th of the next $ k $ lines print two real numbers $ x_i $ and $ y_i $ ( $ |x_i|, |y_i| \le 10^4 $ ) with at most $ 15 $ digits after decimal place.

The polygon must have strictly positive area and contain no self-intersections.

In response to this query you will receive a real number $ s $ ( $ 0 \le s \le 1 $ ) with $ 15 $ digits after decimal place — the area of intersection of the square with the given polygon. If the polygon is invalid, there is no guarantee on the valid response.

When you have identified the drawn square, print on a separate line "! x y", where $ x $ and $ y $ are real numbers with at most $ 15 $ digits after decimal place representing the coordinates of its lower-left corner ( $ 0 \le x \le n - 1 $ , $ 0 \le y \le m - 1 $ ), and then you have to terminate your program.

Your answer will be considered correct if its absolute or relative error on both coordinates does not exceed $ 10^{-6} $ . Formally let your answer be $ a $ , jury answer be $ b $ . Your answer will be considered correct if $ \frac{|a-b|}{max(1,|b|)} \le 10^{-6} $ .

After printing a query do not forget to output end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

Hacks

To make a hack, use the following test format.

The first line of the input should contain two integers $ n $ and $ m $ ( $ 1 \le n,m \le 100 $ ) — field sizes.

The second line should contain two real numbers $ x $ ( $ 0 \le x \le n - 1 $ ) and $ y $ ( $ 0 \le y \le m - 1 $ ) — coordinates of the lower-left corner of the square of poisoned corn.

## 说明/提示

In the first test from the statement, the aliens poisoned a square of corn with vertices at points with coordinates $ (1.5, 0.5) $ , $ (1.5, 1.5) $ , $ (2.5, 1.5) $ , $ (2.5, 0.5) $ . In the picture, it is red, the polygon selected in the query is blue, and their intersection is green.

Picture for the first query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1715F/5905e23dc243a04aad10e5bcbe0e2cd6bb70131e.png)Picture for the second query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1715F/55886132a04f6c81b89194c1c281874f100d6c79.png)

## 样例 #1

### 输入

```
3 3





0.5





0.5
```

### 输出

```
? 4
0 0
2 0
2 3
0 3

? 4
0 0
0 1
3 1
3 0

! 1.5 0.5
```



---

---
title: "Connectivity Addicts"
layout: "post"
diff: 省选/NOI-
pid: CF1738F
tag: ['贪心', '构造']
---

# Connectivity Addicts

## 题目描述

This is an interactive problem.

Given a simple undirected graph with $ n $ vertices numbered from $ 1 $ to $ n $ , your task is to color all the vertices such that for every color $ c $ , the following conditions hold:

1. The set of vertices with color $ c $ is connected;
2. $ s_c \leq n_c^2 $ , where $ n_c $ is the number of vertices with color $ c $ , and $ s_c $ is the sum of degrees of vertices with color $ c $ .

 It can be shown that there always exists a way to color all the vertices such that the above conditions hold. Initially, you are only given the number $ n $ of vertices and the degree of each vertex.

In each query, you can choose a vertex $ u $ . As a response, you will be given the $ k $ -th edge incident to $ u $ , if this is the $ k $ -th query on vertex $ u $ .

You are allowed to make at most $ n $ queries.

An undirected graph is simple if it does not contain multiple edges or self-loops.

The degree of a vertex is the number of edges incident to it.

A set $ S $ of vertices is connected if for every two different vertices $ u, v \in S $ , there is a path, which only passes through vertices in $ S $ , that connects $ u $ and $ v $ . That is, there is a sequence of edges $ (u_1, v_1), (u_2, v_2), \dots, (u_k, v_k) $ with $ k \geq 1 $ such that

1. $ u_1 = u $ , $ v_k = v $ , and $ v_i = u_{i+1} $ for every $ 1 \leq i < k $ ; and
2. $ u_k \in S $ and $ v_k \in S $ for every $ 1 \leq i \leq k $ .

 Especially, a set containing only one vertex is connected.

## 输出格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases. The following lines contain the description and the interactive section of each test case.

For each test case, you begin the interaction by reading an integer $ n $ ( $ 1\le n \le 1000 $ ) in the first line, indicating the number of vertices in the graph.

The second line contains $ n $ integers $ d_1, d_2, \dots, d_n $ ( $ 0 \leq d_i \leq n - 1 $ ), where $ d_i $ is the degree of vertex $ i $ .

To make a query on vertex $ u $ ( $ 1 \leq u \leq n $ ), you should output

- "? $ u $ "

 in a separate line. If this is the $ k $ -th query on vertex $ u $ , vertex $ e_{u, k} $ will be given in the next separate line, where $ \left(u, e_{u, k}\right) $ is the $ k $ -th edge incident to vertex $ u $ . In case of $ k > d_u $ , define $ e_{u, k} = -1 $ . You should make no more than $ n $  "?" queries.To give the answer, you should output

- "! $ c_1 $ $ c_2 $ $ \dots $ $ c_n $ "

 in a separate line, where $ c_i $ ( $ 1 \leq c_i \leq n $ ) is the color of vertex $ i $ . After that, your program should continue to the next test case, or terminate if this is the last test case. It is guaranteed that the graph is a simple undirected graph.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 1000 $ .

In case your query format is invalid, or you have made more than $ n $ "?" queries, you will receive Wrong Answer verdict.

After printing a query, do not forget to output end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

Hack Format

The first line of the hack contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ), indicating the number of test cases. The following lines contain the description of each test case.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 1000 $ ), indicating the number of vertices in the graph.

Then $ n $ lines follow. The $ i $ -th line contains an integer $ d_i $ ( $ 0 \leq d_i \leq n - 1 $ ), indicating the degree of vertex $ i $ , and then $ d_i $ distinct integers $ e_{i,1}, e_{i,2}, \dots, e_{i,d_i} $ ( $ 1 \leq e_{i, j} \leq n $ and $ e_{i,j} \neq i $ ), where $ \left(i, e_{i,j}\right) $ is the $ j $ -th edge incident to vertex $ i $ .

It should be guaranteed that the graph is a simple undirected graph.

It should be guaranteed that the sum of $ n $ over all test cases does not exceed $ 1000 $ .

## 说明/提示

In the example, there is only one test case.

In the test case, there are $ n = 5 $ vertices with vertices $ 1, 2, 3, 4 $ of degree $ 2 $ and vertex $ 5 $ of degree $ 0 $ . It is obvious that vertex $ 5 $ is isolated, i.e., it does not connect to any other vertices.

A possible interaction is shown in the sample input and output, where $ 4 $ "?" queries are made on vertex $ 1 $ twice and vertex $ 3 $ twice. According to the responses to these queries, we know that each of vertex $ 1 $ and vertex $ 3 $ connects to two vertices $ 2 $ and $ 4 $ .

A possible solution is shown in the sample output, where vertex $ 1 $ and vertex $ 2 $ are colored by $ 1 $ , vertex $ 3 $ and vertex $ 4 $ are colored by $ 2 $ , and vertex $ 5 $ is colored by $ 3 $ . It can be seen that this solution satisfies the required conditions as follows.

- For color $ c = 1 $ , vertex $ 1 $ and vertex $ 2 $ are connected. Moreover, $ n_1 = 2 $ and $ s_1 = d_1 + d_2 = 2 + 2 = 4 \leq n_1^2 = 2^2 = 4 $ ;
- For color $ c = 2 $ , vertex $ 3 $ and vertex $ 4 $ are connected. Moreover, $ n_2 = 2 $ and $ s_2 = d_3 + d_4 = 2 + 2 = 4 \leq n_2^2 = 2^2 = 4 $ ;
- For color $ c = 3 $ , there is only one vertex (vertex $ 5 $ ) colored by $ 3 $ . Moreover, $ n_3 = 1 $ and $ s_3 = d_5 = 0 \leq n_3^2 = 1^2 = 1 $ .

## 样例 #1

### 输入

```
1
5
2 2 2 2 0

2

4

2

4
```

### 输出

```
? 1

? 1

? 3

? 3

! 1 1 2 2 3
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
title: "Flower-like Pseudotree"
layout: "post"
diff: 省选/NOI-
pid: CF1868D
tag: ['构造', '分类讨论']
---

# Flower-like Pseudotree

## 题目描述

A pseudotree is a connected graph which has exactly one cycle and no self-loops. Note that a pseudotree may contain multiple-edges. It can be shown that a pseudotree with $ n $ vertices always contains $ n $ edges.

After deleting all edges on the cycle in the pseudotree, a forest $ ^{\dagger} $ will be formed. It can be shown that each tree in the forest will contain exactly one vertex which is on cycle before removing the edges. If all trees in the forest have the same depth $ ^{\ddagger} $ when picking the vertex on cycle as root, we call the original pseudotree flower-like.

Our friend sszcdjr, had a flower-like pseudotree with $ n $ vertices and $ n $ edges. However, he forgot all the edges in the pseudotree. Fortunately, he still remembers the degrees of vertices. Specifically, the degree of the $ i $ -th vertex is $ d_i $ .

You have to help sszcdjr construct a possible flower-like pseudotree with $ n $ vertices, where the degree of the $ i $ -th vertex is exactly $ d_i $ , or tell him that it is impossible.

 $ ^{\dagger} $ A forest is a graph in which all connectivity components are trees. A connected graph without cycles and self-loops is called a tree.

 $ ^{\ddagger} $ The depth of a tree with a root is the maximum distance from the root to the vertex of this tree.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1\leq t\leq 10^5 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2\leq n\leq 10^6 $ ) — the number of vertices.

The second line of each test case contains $ n $ integers $ d_1,d_2,\ldots,d_n $ ( $ 1\leq d_i\leq n $ ) — the degree of each vertex.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, if there exist a possible flower-like pseudotree:

- Print "Yes" (without quotes) in the first line.
- Then, output $ n $ lines, in each line print two integers $ u_i $ and $ v_i $ — the two vertices that the $ i $ -th edge connects.

If there are multiple answers, you may output any of them.

Otherwise, print "No" (without quotes) in the only line of output.

You can output the first line of each test case in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, the only possible flower-like psuedotree is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1868D/cef326e6c38f8a7ed31108a0dd8a82ca77066a75.png)After deleting all edges on the cycle in the pseudotree, each tree has depth $ 0 $ .

In the second test case, it can be proven that there's no such flower-like psuedotree.

In the third test case, one of the possible flower-like psuedotrees is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1868D/48e01c1853662d07718526eb1ce31700d09724f0.png)

## 样例 #1

### 输入

```
6
3
2 2 2
4
1 2 3 4
7
4 3 3 1 1 1 1
6
1 1 2 2 3 3
10
1 1 5 2 1 1 1 1 1 6
9
1 1 3 1 1 4 1 1 5
```

### 输出

```
Yes
1 2
2 3
3 1
No
Yes
1 2
2 3
3 1
1 4
1 5
2 6
3 7
Yes
5 6
6 5
1 3
2 4
3 5
4 6
No
Yes
3 6
6 9
9 3
1 3
2 6
4 6
5 9
7 9
8 9
```



---

---
title: "Bracket Xoring"
layout: "post"
diff: 省选/NOI-
pid: CF1896F
tag: ['构造']
---

# Bracket Xoring

## 题目描述

You are given a binary string $ s $ of length $ 2n $ where each element is $ \mathtt{0} $ or $ \mathtt{1} $ . You can do the following operation:

1. Choose a balanced bracket sequence $ ^\dagger $ $ b $ of length $ 2n $ .
2. For every index $ i $ from $ 1 $ to $ 2n $ in order, where $ b_i $ is an open bracket, let $ p_i $ denote the minimum index such that $ b[i,p_i] $ is a balanced bracket sequence. Then, we perform a range toggle operation $ ^\ddagger $ from $ i $ to $ p_i $ on $ s $ . Note that since a balanced bracket sequence of length $ 2n $ will have $ n $ open brackets, we will do $ n $ range toggle operations on $ s $ .

Your task is to find a sequence of no more than $ 10 $ operations that changes all elements of $ s $ to $ \mathtt{0} $ , or determine that it is impossible to do so. Note that you do not have to minimize the number of operations.

Under the given constraints, it can be proven that if it is possible to change all elements of $ s $ to $ \mathtt{0} $ , there exists a way that requires no more than $ 10 $ operations.

 $ ^\dagger $ A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters $ + $ and $ 1 $ . For example, sequences "(())()", "()", and "(()(()))" are balanced, while ")(", "(()", and "(()))(" are not.

 $ ^\ddagger $ If we perform a range toggle operation from $ l $ to $ r $ on a binary string $ s $ , then we toggle all values of $ s_i $ such that $ l \leq i \leq r $ . If $ s_i $ is toggled, we will set $ s_i := \mathtt{0} $ if $ s_i = \mathtt{1} $ or vice versa. For example, if $ s=\mathtt{1000101} $ and we perform a range toggle operation from $ 3 $ to $ 5 $ , $ s $ will be changed to $ s=\mathtt{1011001} $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2\cdot 10^5 $ ) — where $ 2n $ is the length of string $ s $ .

The second line of each test case contains a binary string $ s $ of length $ 2n $ ( $ s_i = \mathtt{0} $ or $ s_i = \mathtt{1} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output $ -1 $ in a single line if it is impossible to change all elements of $ s $ to $ \mathtt{0} $ .

Otherwise, output a single integer $ k $ ( $ 0 \le k \le 10 $ ) representing the number of operations needed to change all elements of $ s $ to $ \mathtt{0} $ . Then, on each of the next $ k $ lines, output a balanced bracket sequence of length $ 2n $ representing the operations needed to change all elements of $ s $ to $ 0 $ s.

If there are multiple ways to change all elements of $ s $ to $ \mathtt{0} $ that require not more than $ 10 $ operations, you can output any of them.

## 说明/提示

In the first test case, it can be proven that it is impossible to change all elements of $ s $ to $ \mathtt{0} $ .

In the second test case, the first operation using the bracket sequence $ b = \mathtt{()()} $ will convert the binary string $ s=\mathtt{0000} $ to $ s=\mathtt{1111} $ . Then, the second operation using the same bracket sequence $ b = \mathtt{()()} $ will convert the binary string $ s=\mathtt{1111} $ back to $ s=\mathtt{0000} $ . Note that since all elements of $ s $ is already $ \mathtt{0} $ initially, using $ 0 $ operations is also a valid answer.

In the third test case, a single operation using the bracket sequence $ b = \mathtt{(())()} $ will change all elements of $ s $ to $ \mathtt{0} $ . The operation will happen as follows.

1. $ b_1 $ is an open bracket and $ p_1 = 4 $ since $ b[1,4]=\mathtt{(())} $ is a balanced bracket sequence. Hence, we do a range toggle operation from $ 1 $ to $ 4 $ on the binary string $ s = \mathtt{100111} $ to obtain $ s = \mathtt{011011} $ .
2. $ b_2 $ is an open bracket and $ p_2 = 3 $ since $ b[2,3]=\mathtt{()} $ is a balanced bracket sequence. Hence, we do a range toggle operation from $ 2 $ to $ 3 $ on the binary string $ s = \mathtt{011011} $ to obtain $ s = \mathtt{000011} $ .
3. $ b_3 $ is not an open bracket, so no range toggle operation is done at this step.
4. $ b_4 $ is not an open bracket, so no range toggle operation is done at this step.
5. $ b_5 $ is an open bracket and $ p_5 = 6 $ since $ b[5,6]=\mathtt{()} $ is a balanced bracket sequence. Hence, we do a range toggle operation from $ 5 $ to $ 6 $ on the binary string $ s = \mathtt{000011} $ to obtain $ s = \mathtt{000000} $ .
6. $ b_6 $ is not an open bracket, so no range toggle operation is done at this step.

In the fourth test case, the first operation using the bracket sequence $ b = \mathtt{(((())))} $ will convert the binary string $ s = \mathtt{01011100} $ to $ s = \mathtt{11111001} $ . Then, the second operation using the bracket sequence $ b = \mathtt{()()(())} $ will convert the binary string $ s = \mathtt{11111001} $ to $ s=\mathtt{00000000} $ .

## 样例 #1

### 输入

```
4
1
01
2
0000
3
100111
4
01011100
```

### 输出

```
-1
2
()()
()()
1
(())()
2
(((())))
()()(())
```



---

---
title: "Palindromic Parentheses"
layout: "post"
diff: 省选/NOI-
pid: CF1906L
tag: ['构造']
---

# Palindromic Parentheses

## 题目描述

Construct a parentheses sequence consisting of $ N $ characters such that it is balanced and the length of its longest palindromic subsequence (LPS) is exactly $ K $ . Determine whether such a construction is possible. If there are several possible sequences, construct any of them.

A parentheses sequence consists of only character ( and ). A parentheses sequence is balanced if each character ( has a corresponding character ) and the pairs of parentheses are properly nested. For example, (), (()), (())(), and ((())()) are balanced. However, )(, ((), and ()) are not balanced.

A sequence is palindromic if it reads the same backwards as forwards. For example, ((, ), ())(, and (()(( are palindromic. However, (), )(, and (()) are not palindromic.

A subsequence can be derived from another sequence by removing zero or more characters without changing the order of the remaining characters. For example, (, ))), ())(, and (())() are subsequence of (())(). However, )(( and ((())) are not subsequence of (())().

The longest palindromic subsequence (LPS) of a sequence is a subsequence with the maximum number of characters, derived from that sequence and it is palindromic. For example, the LPS of sequence (())() is ())(, which can be obtained by removing the second and sixth characters. Therefore, the length of the LPS of (())() is $ 4 $ .

## 输入格式

Input consists of two integers $ N $ $ K $ ( $ 2 \leq N \leq 2000; 1 \leq K \leq N $ ). $ N $ is an even number.

## 输出格式

If there is no such parentheses sequence such that it is balanced and the length of its LPS is exactly $ K $ , then output -1.

Otherwise, output a string of $ N $ characters, representing the parentheses sequence. If there are several possible answers, output any of them.

## 说明/提示

Explanation for the sample input/output #2

The LPS of (()()) is either ((( by removing all ) characters, or ))) by removing all ( characters.

The output ((())) also satisfies the requirements.

Explanation for the sample input/output #3

The only possible balanced parentheses sequences are (()) and ()(). The length of the LPS of (()) and ()() are $ 2 $ and $ 3 $ , respectively.

Explanation for the sample input/output #4

The LPS of ()((())()())() is )())()())(), which can be obtained by removing the first, fourth, and fifth characters.

## 样例 #1

### 输入

```
6 4
```

### 输出

```
(())()
```

## 样例 #2

### 输入

```
6 3
```

### 输出

```
(()())
```

## 样例 #3

### 输入

```
4 1
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
14 11
```

### 输出

```
()((())()())()
```



---

---
title: "Construct Matrix"
layout: "post"
diff: 省选/NOI-
pid: CF1917E
tag: ['构造']
---

# Construct Matrix

## 题目描述

You are given an even integer $ n $ and an integer $ k $ . Your task is to construct a matrix of size $ n \times n $ consisting of numbers $ 0 $ and $ 1 $ in such a way that the following conditions are true, or report that it is impossible:

- the sum of all the numbers in the matrix is exactly $ k $ ;
- the bitwise $ \texttt{XOR} $ of all the numbers in the row $ i $ is the same for each $ i $ ;
- the bitwise $ \texttt{XOR} $ of all the numbers in the column $ j $ is the same for each $ j $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 130 $ ) — the number of test cases. The description of the test cases follows.

Each test case is described by a single line, which contains two integers $ n $ and $ k $ ( $ 2 \leq n \leq 1000 $ , $ n $ is even, $ 0 \leq k \leq n^2 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, output $ \texttt{Yes} $ if it's possible to construct a matrix that satisfies all of the problem's conditions, and $ \texttt{No} $ otherwise.

If it is possible to construct a matrix, the $ i $ -th of the next $ n $ lines should contain $ n $ integers representing the elements in the $ i $ -th row of the matrix.

## 说明/提示

In the first example, all conditions are satisfied:

- the sum of all the numbers in the matrix is exactly $ 0 $ ;
- the bitwise $ \texttt{XOR} $ of all the numbers in the row $ i $ is $ 0 $ for each $ i $ ;
- the bitwise $ \texttt{XOR} $ of all the numbers in the column $ j $ is $ 0 $ for each $ j $ .

In the third example, it can be shown that it's impossible to find a matrix satisfying all the problem's conditions.

## 样例 #1

### 输入

```
5
4 0
6 6
6 5
4 2
6 36
```

### 输出

```
Yes
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
Yes
1 0 0 0 0 0
0 1 0 0 0 0
0 0 1 0 0 0
0 0 0 1 0 0
0 0 0 0 1 0
0 0 0 0 0 1
No
No
Yes
1 1 1 1 1 1
1 1 1 1 1 1
1 1 1 1 1 1
1 1 1 1 1 1
1 1 1 1 1 1
1 1 1 1 1 1
```



---

---
title: "Kostyanych's Theorem"
layout: "post"
diff: 省选/NOI-
pid: CF1979F
tag: ['构造']
---

# Kostyanych's Theorem

## 题目描述

This is an interactive problem.

Kostyanych has chosen a complete undirected graph $ ^{\dagger} $ with $ n $ vertices, and then removed exactly $ (n - 2) $ edges from it. You can ask queries of the following type:

- "? $ d $ " — Kostyanych tells you the number of vertex $ v $ with a degree at least $ d $ . Among all possible such vertices, he selects the vertex with the minimum degree, and if there are several such vertices, he selects the one with the minimum number. He also tells you the number of another vertex in the graph, with which $ v $ is not connected by an edge (if none is found, then $ 0 $ is reported). Among all possible such vertices, he selects the one with the minimum number. Then he removes the vertex $ v $ and all edges coming out of it. If the required vertex $ v $ is not found, then " $ 0\ 0 $ " is reported.

Find a Hamiltonian path $ ^{\ddagger} $ in the original graph in at most $ n $ queries. It can be proven that under these constraints, a Hamiltonian path always exists.

 $ ^{\dagger} $ A complete undirected graph is a graph in which there is exactly one undirected edge between any pair of distinct vertices. Thus, a complete undirected graph with $ n $ vertices contains $ \frac{n(n-1)}{2} $ edges.

 $ ^{\ddagger} $ A Hamiltonian path in a graph is a path that passes through each vertex exactly once.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of the test cases follows.

The only line of each test case contains a single integer $ n $ ( $ 2 \le n \le 10^5 $ ) — the number of vertices in the graph.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

Interaction for each test case begins with reading the integer $ n $ .

Then you can make no more than $ n $ queries.

To make a query, output a line in the format "? $ d $ " (without quotes) ( $ 0 \le d \le n - 1 $ ). After each query, read two integers — the answer to your query.

When you are ready to report the answer, output a line in the format "! $ v_1\ v_2 \ldots v_n $ " (without quotes) — the vertices in the order of their occurrence in the Hamiltonian path. Outputting the answer does not count as one of the $ n $ queries. After solving one test case, the program should immediately move on to the next one. After solving all test cases, the program should be terminated immediately.

If your program makes more than $ n $ queries for one test case or makes an incorrect query, then the response to the query will be $ -1 $ , and after receiving such a response, your program should immediately terminate to receive the verdict Wrong answer. Otherwise, it may receive any other verdict.

After outputting a query, do not forget to output an end of line and flush the output buffer. Otherwise, you will receive the verdict Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

The interactor is non-adaptive. The graph does not change during the interaction.

Hacks

To hack, use the following format:

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The only line of each test case contains a single integer $ n $ ( $ 2 \le n \le 10^5 $ ) — the number of vertices in the graph.

Each of the following $ (n - 2) $ lines should contains two integers $ u $ and $ v $ ( $ 1 \le u, v \le n $ , $ u \ne v $ ) — ends of the edge that was removed from the graph. Each edge must not occur more than once.

The sum of $ n $ over all test cases should not exceed $ 10^5 $ .

## 说明/提示

In the first test case, the original graph looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1979F/42089518245c2488c2bfecf2fe23dadea3c789e8.png)Consider the queries:

- There are no vertices with a degree of at least $ 3 $ in the graph, so " $ 0\ 0 $ " is reported.
- There are four vertices with a degree of at least $ 2 $ , and all of them have a degree of exactly $ 2 $ : $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ . Vertex $ 1 $ is reported, because it has the minimum number, and vertex $ 4 $ is reported, because it is the only one not connected to vertex $ 1 $ . After this, vertex $ 1 $ is removed from the graph.
- There are three vertices with a degree of at least $ 1 $ , among them vertices $ 2 $ and $ 3 $ have a minimum degree of $ 1 $ (vertex $ 4 $ has a degree of $ 2 $ ). Vertex $ 2 $ is reported, because it has the minimum number, and vertex $ 3 $ is reported, because it is the only one not connected to vertex $ 2 $ . After this, vertex $ 2 $ is removed from the graph.

The path $ 4 - 3 - 1 - 2 $ is a Hamiltonian path.

In the second test case, the original graph looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1979F/8d69c71de95e98946d0d15367d0511bf08d2ba0a.png)Consider the queries:

- Vertex $ 1 $ has a degree of at least $ 3 $ , but it is connected to all vertices, so " $ 1\ 0 $ " is reported. After this, vertex $ 1 $ is removed from the graph.
- The remaining vertices $ 2 $ , $ 3 $ , and $ 4 $ have a degree of at least $ 0 $ , but among them vertex $ 4 $ has the minimum degree of $ 0 $ (vertices $ 2 $ and $ 3 $ have a degree of $ 1 $ ). Vertex $ 4 $ is not connected to both vertices $ 2 $ and $ 3 $ , so vertex $ 2 $ is reported (as it has the minimum number). After this, vertex $ 4 $ is removed from the graph.

The path $ 4 - 1 - 2 - 3 $ is a Hamiltonian path.

In the third test case, the graph consists of $ 2 $ vertices connected by an edge.

## 样例 #1

### 输入

```
3
4

0 0

1 4

2 3

4

1 0

4 2

2

1 0
```

### 输出

```
? 3

? 2

? 1

! 4 3 1 2

? 3

? 0

! 4 1 2 3

? 0

! 2 1
```



---

---
title: "Grid Reset"
layout: "post"
diff: 省选/NOI-
pid: CF1991G
tag: ['贪心', '构造']
---

# Grid Reset

## 题目描述

给定一个 $n$ 行 $m$ 列的格子矩阵，初始所有格子都是白色。另外给定一个整数 $k$。

你将执行如下两类操作共 $q$ 次：

- $\texttt H$（水平操作）：在格子矩阵中选择一个 $1$ 行 $k$ 列，且所有格子均为白色的格子矩阵，并将其中的所有格子涂黑。
- $\texttt V$（纵向操作）：在格子矩阵中选择一个 $k$ 行 $1$ 列，且所有格子均为白色的格子矩阵，并将其中的所有格子涂黑。

每次操作之后，如果任意一行或一列所有格子都被涂成了黑色，则这一行或一列的所有格子自动被重置成白色。特别的，如果某一个格子所在的行和列都被涂成了黑色，则该格子所处的行和列的所有格子也将自动被重置成白色。

现在，对于 $q$ 次操作中的每次操作，请指定一个矩阵，使得所有 $q$ 次操作都能够进行，或者报告无论如何指定矩阵都不能使得所有 $q$ 次操作都能够进行。

## 输入格式

**本题包含多组数据。**

第一行输入一个整数 $t$，表示数据组数。

对于每组数据，第一行输入四个整数 $n,m,k,q$，分别代表格子矩阵的行数、列数、每次操作选定的矩阵的大小和操作次数。  
第二行输入一个长度为 $q$ 的字符串 $s$，表示操作序列。

## 输出格式

对于每组数据，如果无论如何指定矩阵都不能使得所有 $q$ 次操作都能够进行，输出一行 $-1$。否则，输出 $q$ 行，第 $x$ 行两个整数 $i,j$，表示第 $x$ 次操作所指定的矩阵的左上角的格子所在的行和列。

## 说明/提示

对于所有数据：

- $1\leqslant t\leqslant 1000$。
- $1\leqslant n,m\leqslant 100,\color{Red}1\leqslant k\leqslant \min\{n,m\}$。
- $1\leqslant q\leqslant 1000,\sum q\leqslant 1000$。

输入输出样例参见下文。

Translated by [Eason_AC](/user/112917)。

## 样例 #1

### 输入

```
1
4 5 3 6
HVVHHV
```

### 输出

```
1 1
2 1
1 1
2 3
3 3
2 2
```



---

---
title: "Asesino (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2022D2
tag: ['鸽笼原理', '构造']
---

# Asesino (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, you must use the minimum number of queries possible. You can make hacks only if both versions of the problem are solved.

This is an interactive problem.

It is a tradition in Mexico's national IOI trainings to play the game "Asesino", which is similar to "Among Us" or "Mafia".

Today, $ n $ players, numbered from $ 1 $ to $ n $ , will play "Asesino" with the following three roles:

- Knight: a Knight is someone who always tells the truth.
- Knave: a Knave is someone who always lies.
- Impostor: an Impostor is someone everybody thinks is a Knight, but is secretly a Knave.

Each player will be assigned a role in the game. There will be exactly one Impostor but there can be any (possible zero) number of Knights and Knaves.

As the game moderator, you have accidentally forgotten the roles of everyone, but you need to determine the player who is the Impostor.

To determine the Impostor, you will ask some questions. In each question, you will pick two players $ i $ and $ j $ ( $ 1 \leq i, j \leq n $ ; $ i \neq j $ ) and ask if player $ i $ thinks that player $ j $ is a Knight. The results of the question is shown in the table below.

 KnightKnaveImpostorKnightYesNoYesKnaveNoYesNoImpostorNoYes— The response of the cell in row $ a $ and column $ b $ is the result of asking a question when $ i $ has role $ a $ and $ j $ has row $ b $ . For example, the "Yes" in the top right cell belongs to row "Knight" and column "Impostor", so it is the response when $ i $ is a Knight and $ j $ is an Impostor.Find the Impostor in the minimum number of queries possible. That is, let $ f(n) $ be the minimum integer such that for $ n $ players, there exists a strategy that can determine the Impostor using at most $ f(n) $ questions. Then, you should use at most $ f(n) $ questions to determine the Impostor.

Note: the grader is adaptive: the roles of the players are not fixed in the beginning and may change depending on your questions. However, it is guaranteed that there exists an assignment of roles that is consistent with all previously asked questions under the constraints of this problem.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \le n \le 10^5 $ ) — the number of people playing the game.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

To ask a question, output a line in the following format:

- "? i j" ( $ 1 \leq i,j \leq n $ ; $ i \neq j $ ) — to ask player $ i $ if they think player $ j $ is a Knight.

The jury will output a "1" if player $ i $ thinks player $ j $ is a Knight, and "0" otherwise.

When you have determined which player the Impostor is, output a line in the following format:

- "! i" ( $ 1 \leq i \leq n $ ) — the Impostor is player $ i $ .

Note that answering does not count to your limit of $ f(n) $ questions.

If you have made an invalid output, used more than $ f(n) $ questions or wrongly determined the Impostor, the jury will respond with "-1" and you will receive a Wrong Answer verdict. Upon receiving "-1", your program must terminate immediately. Otherwise, you may receive an arbitrary verdict because your solution might be reading from a closed stream.

After printing a query do not forget to output the end of the line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- sys.stdout.flush() in Python;
- std::io::stdout().flush() in Rust;
- see the documentation for other languages.

Hack format

For hacks, use the following format.

The first line should contain a single integer $ t $ — the number of test cases.

The first line of each test case should contain the integer $ n $ followed by the string "manual".

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -1 \le a_i \le 1 $ ) — the roles of each player. $ 1 $ denotes a Knight, $ 0 $ denotes a Knave, and $ -1 $ dentoes an Impostor. There must be exactly one Impostor, that is there must be exactly one index $ i $ such that $ a_i=-1 $ .

As an example, the hack format for the example input is:

```
<pre class="lstlisting">```
2<br></br>7 manual<br></br>0 1 0 -1 0 1 0<br></br>4 manual<br></br>0 1 -1 0<br></br>
```
```

## 说明/提示

Note that the example test cases do not represent an optimal strategy for asking questions and are only shown for the sake of demonstrating the interaction format. Specifically, we cannot determine which player is the Impostor from the questions asked in the examples.

In the first test case of the example, players at indices $ 2 $ and $ 6 $ are Knights, players at indices $ 1 $ , $ 3 $ , $ 5 $ , and $ 7 $ are Knaves, and the Impostor is at index $ 4 $ . The following is an explanation of the questions asked:

- In the first query, player $ i $ is a Knave and player $ j $ is a Knave. The answer is "yes" since Knaves always lie.
- In the second query, player $ i $ is a Knave and player $ j $ is a Knight. The answer is "no" since Knaves always lie.
- In the third query, player $ i $ is a Knight and player $ j $ is a Knave. The answer is "no" since Knights always tell the truth.
- In the fourth query, player $ i $ is a Knight and player $ j $ is a Knight. The answer is "yes" since Knights always tell the truth.
- In the fifth query, player $ i $ is a Impostor and player $ j $ is a Knave. The answer is "yes" since the Impostor always lies.
- In the sixth query, player $ i $ is a Impostor and player $ j $ is a Knight. The answer is "no" since the Impostor always lies.
- In the seventh query, player $ i $ is a Knave and player $ j $ is a Impostor. The answer is "no" since Knaves always lie and Knaves thinks that the Impostor is a Knight.

## 样例 #1

### 输入

```
2
7

1

0

0

1

1

0

0

4

0

1

1

1
```

### 输出

```
? 1 3

? 7 6

? 2 5

? 6 2

? 4 5

? 4 6

? 1 4

! 4

? 1 2

? 2 3

? 3 4

? 4 1

! 3
```



---

---
title: "Palindrome Everywhere"
layout: "post"
diff: 省选/NOI-
pid: CF2029F
tag: ['构造']
---

# Palindrome Everywhere

## 题目描述

给定一个 $n$ 个点的环，编号为 $0$ 到 $n-1$，第 $i(0 \leq i \leq n-1)$ 个点向第 $((i+1) \bmod n)$ 个点连一条颜色为 $c_i$（$c_i$ 为 `R` 或 `B`）的无向边。问任意两点是否都满足它们之间有一条“回文路径”。

两点 $(i,j)$ 间的回文路径定义：（假设该回文路径包含的点集为 $p=[p_0,p_1,\dots,p_m]$）

- 回文路径必须是两点之间的一条路径，但 **可以不是简单路径**。

- 对于满足 $x+y=m-1$ 且 $0 \leq x \leq y \leq m-1$ 的两点 $p_x,p_y$，若连接 $p_x,p_x+1$ 的边的颜色和连接 $p_y,p_y+1$ 的边的颜色相同。

## 输入格式

多测，第一行输入数据组数 $t(1 \leq t \leq 10^5)$。

对于每组数据，第一行一个整数 $n(3 \le n \le 10^6,\sum n \le 10^6)$，表示环长。

第二行有一个长度为 $n$ 的字符串 $c$，表示环上边的颜色。

## 输出格式

对于每组测试数据，如果满足任意两个节点都有回文路径，输出 `YES`，否则输出 `NO`。

输出大小写不敏感，即输出 `yEs`，`yes`，`Yes` 或 `YES` 都表示 `YES`。

## 样例 #1

### 输入

```
7
5
RRRRR
5
RRRRB
5
RBBRB
6
RBRBRB
6
RRBBRB
5
RBRBR
12
RRBRRBRRBRRB
```

### 输出

```
YES
YES
YES
NO
NO
YES
NO
```



---

---
title: "Penchick and Even Medians"
layout: "post"
diff: 省选/NOI-
pid: CF2031F
tag: ['随机化', '构造']
---

# Penchick and Even Medians

## 题目描述

这是一个交互式的问题。

Penchick 刚从澳大利亚的黄金海岸度假回家，却遗忘给他的宠物鸭 Duong Canh 带礼物！或许经过海滩上的深思熟虑设计出的一道有趣题目，是最好的纪念品。

你面临的任务是找出一个长度为 $n$ 的隐藏排列 $p$，其中 $n$ 是偶数。你可以通过以下方式进行查询：

- 选择排列 $p$ 的一个长度为 $4 \le k \le n$ 的子序列（子序列中的元素不必连续）。交互系统会返回该子序列中的两个中位数。

你的任务是在不超过 80 次查询的条件下，找出排列 $p$ 中这两个中位数的索引。

注意：交互系统是固定的，即排列 $p$ 在开始时就已经确定，并不会根据你的查询而改变。

## 输入格式

每个测例包含多个测试用例。第一行包含测例数量 $t$ （$1 \le t \le 1000$）。接下来是每个测试用例的描述。

在每个测试用例中，首先是一个整数 $n$ （$6 \le n \le 100$，且为偶数），即隐藏排列 $p$ 的长度。

读取整数 $n$ 后，你应开始与系统进行交互，直到猜出答案，然后再处理下一个测试用例。

保证所有测试用例中 $n$ 的总和不超过 $10^4$。

## 输出格式

要进行一次查询，按以下格式输出：

- `? k x_1 x_2 ... x_{k-1} x_k` （$4 \le k \le n$，$k$ 是偶数，$1 \le x_i \le n$，所有 $x_i$ 互不相同），其中 $k$ 是选择的子序列长度，后面跟随子序列元素的索引。

每次查询后，你会收到一个包含两个整数 $m_1$ 和 $m_2$ 的响应（$1 \le m_1 < m_2 \le n$），表示这个子序列的两个中位数的值。

每个测试用例中可以进行的查询次数最多为 80。

输出最终答案时，请按以下格式：

- `! i_1 i_2` （$1 \le i_1, i_2 \le n$）——这两个数表示两个中位数的索引。

注意，输出的顺序不重要，即满足 $p_{i_1} = \frac{n}{2}$ 和 $p_{i_2} = \frac{n}{2}+1$，或反之亦可。

在每次查询后，记得输出换行符并刷新输出，否则程序可能由于“空闲限制”而失败。

如果在任何交互步骤中读取到 $-1$ 而不是有效数据，说明出现了无效查询或其他错误，你的程序必须立即退出继续执行会导致程序异常。

### 示例

在第一个测试用例中，隐藏的排列是 $p = [6, 2, 3, 5, 1, 4]$。

1. 第一次查询选择了整个排列，此时的两个中位数是 $3$ 和 $4$。
2. 第二次查询选择了子序列 $3, 6, 1, 5$，返回的中位数是 $3$ 和 $4$。
3. 第三次查询选择了子序列 $3, 6, 2, 5$，返回的中位数是 $2$ 和 $3$。

答案“! 3 6”是有效的，因为 $p_3 = 3$ 且 $p_6 = 4$。

在第二个测试用例中，隐藏的排列是 $p = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]$。

1. 第一次查询选择了子序列 $1, 3, 7, 8, 9, 10$，返回的中位数是 $3$ 和 $4$。
2. 第二次查询选择了子序列 $1, 2, 3, 4, 5, 6, 7, 8$，返回的中位数是 $6$ 和 $7$。

答案“! 5 6”是有效的，因为 $p_5 = 6$ 和 $p_6 = 5$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
6

3 4

3 4

2 3

10

3 4

6 7
```

### 输出

```
? 6 1 2 3 4 5 6

? 4 3 6 1 5

? 4 3 6 2 5

! 3 6

? 6 1 3 7 8 9 10

? 8 1 2 3 4 5 6 7 8

! 6 5
```



---

---
title: "Cheops and a Contest (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2046E1
tag: ['贪心', '构造']
---

# Cheops and a Contest (Easy Version)

## 题目描述

这是问题的简单版本。在这个版本中，$m$ 固定为 $2$。只有解决了问题的所有版本后，你才能进行 hack。

在古埃及有一场问题解决比赛，参赛者有 $n$ 名，编号从 $1$ 到 $n$。每位参赛者来自一个特定的城市，城市的编号从 $1$ 到 $m$。保证每个城市至少有一名参赛者。

每位参赛者拥有力量 $a_i$，专长 $s_i$，以及智慧 $b_i$，并且 $b_i \ge a_i$。比赛中的每个问题都有一个难度 $d$ 和一个独特的主题 $t$。如果满足以下条件之一，第 $i$ 位参赛者可以解决这个问题：

- $a_i \ge d$，即参赛者的力量大于或等于问题的难度；
- $s_i = t$ 并且 $b_i \ge d$，即参赛者的专长等于问题的主题，同时智慧不低于问题的难度。

Cheops 的愿望是设计一组问题，使得来自城市 $i$ 的每位参赛者比来自城市 $j$ 的每位参赛者解决更多的问题，且 $i < j$。

请找到一个不超过 $5n$ 个问题的集合，其中所有问题的主题各不相同，能够满足 Cheops 的愿望，或者说明这个愿望无法实现。

## 输入格式

输入包含多个测试用例。第一行为测试用例的数量 $T$，满足 $1 \le T \le 10^4$。接下来的部分描述每个测试用例。

对于每个测试用例，第一行包含两个整数 $n$ 和 $m$，其中 $2 = m \le n \le 3 \cdot 10^5$，分别表示参赛者数量和城市数量。

接下来的 $n$ 行描述了每位参赛者。第 $i$ 行包含三个整数 $a_i$，$b_i$ 和 $s_i$，其中 $0 \le a_i, b_i, s_i \le 10^9$ 且 $a_i \le b_i$，依次表示第 $i$ 位参赛者的力量、智慧和专长。

接下来的 $m$ 行描述每个城市的参赛者情况。第 $i$ 行首先是一个整数 $k_i$，表示来自于第 $i$ 个城市的参赛者数量，满足 $1 \le k_i \le n$。接着是该城市参赛者的编号序列 $q_{i, 1}, q_{i, 2}, \ldots, q_{i, k_i}$，其中 $1 \le q_{i, j} \le n$ 且 $1 \le j \le k_i$。保证每位参赛者的编号恰好被提及一次。

保证所有测试用例中 $n$ 的总和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果存在一组问题满足 Cheops 的条件，则输出一个整数 $p$，表示问题数量，满足 $1 \le p \le 5n$。

接下来输出 $p$ 行，每行包含两个整数 $d$ 和 $t$，分别表示问题的难度和主题。不同问题的主题必须各不相同。

如果无法找到符合条件的问题集合，请输出 $-1$。

 **本翻译由 AI 自动生成**

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
title: "Secret Message"
layout: "post"
diff: 省选/NOI-
pid: CF2057G
tag: ['鸽笼原理', '构造']
---

# Secret Message

## 题目描述

每个周六晚上，平行班的老师亚历山大 B，总会把一封密码信息写在交互式在线白板上，发送给另一位老师亚历山大 G。这封信相当重要，而亚历山大 G 正在授课，因此在线白板就成了一个理想的秘密传递工具。

这个白板是一个由 $n$ 行 $m$ 列构成的网格。网格中每个单元格大小是 $1 \times 1$。部分单元格已经填满，用符号 "." 表示，不能在其中书写；剩下的未填满的单元格称为自由单元格，用符号 "#" 代表。

我们需要关注白板的两个特性：

- $s$：自由单元格的数量。
- $p$：由这些自由单元格构成的图形的边界周长。

设 $A$ 为当前所有自由单元格的集合。你的任务是从中找到一个子集 $S \subseteq A$，满足以下条件：

- $|S| \le \frac{1}{5} \cdot (s+p)$，即集合 $S$ 的大小不超过 $s$ 和 $p$ 的加和的五分之一。
- 每一个自由单元格，要么已经在 $S$ 中，要么与 $S$ 中的某个单元格相邻（共用一条边）。

可以证明，总有这样的集合 $S$ 存在，你只需找到任意符合条件的一个即可。

## 输入格式

首先输入一个整数 $t$ 表示测试用例的数量（$1 \le t \le 80\,000$）。

每个测试用例的第一行包含两个整数 $n$ 和 $m$ （$1 \le n, m \le 2 \cdot 10^6$），分别表示网格的行数和列数。

接下来的 $n$ 行给出网格的具体描述。

所有测试用例中，所有 $n \cdot m$ 的总和不超过 $2 \cdot 10^6$。

## 输出格式

对于每个测试用例，输出 $n$ 行，每行有 $m$ 个字符，表示网格中的单元状态：

- "#" 表示该单元格在 $A$ 中但不在 $S$ 中；
- "S" 表示该单元格同时在 $A$ 和 $S$ 中；
- "." 表示该单元格既不在 $A$ 中也不在 $S$ 中。

## 说明/提示

例如：

- 在第一个例子中，$s=5$ 和 $p=12$，所以 $S$ 的单元格数量不能超过 $\frac{1}{5} \cdot (5+12) = 3.4$，即 $|S| \le 3$。给出的 $S$ 集合包含 1 个单元格，符合条件。

- 在第二个例子中，$s=12$ 和 $p=16$，所以 $S$ 的单元格数量不能超过 $\frac{1}{5} \cdot (12+16)= 5.6$，即 $|S| \le 5$。给出的 $S$ 集合包含 4 个单元格，符合条件。

- 在第三个例子中说明了周长的概念。任何网格图形都有一个由线段组成的边界，边界线段的长度总和即为周长。在示例中，黑色粗线标示的是自由单元格形成图形的边界，其总长度为 $p=24$。同时，$s=11$，故上限为 $|S| \le 7$，给出的 $S$ 集合大小为 6，符合条件。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2057G/7a81d6643999264740192ed7581cb70b4cce9f3c.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3 3
.#.
###
.#.
2 6
######
######
3 7
###....
#.#.###
###....
```

### 输出

```
.#.
#S#
.#.
#S##S#
#S##S#
S#S....
#.#.S#S
S#S....
```



---

---
title: "Quaternary Matrix"
layout: "post"
diff: 省选/NOI-
pid: CF2081C
tag: ['贪心', '构造']
---

# Quaternary Matrix

## 题目描述

若矩阵中所有元素均为 $0$、$1$、$2$ 或 $3$，则称该矩阵为四元矩阵。

当四元矩阵 $A$ 满足以下两个性质时，Ecrade 称其为好矩阵：
1. 矩阵 $A$ 的每一行中所有数字的按位异或（bitwise XOR）结果等于 $0$。
2. 矩阵 $A$ 的每一列中所有数字的按位异或（bitwise XOR）结果等于 $0$。

Ecrade 有一个 $n \times m$ 的四元矩阵。他想知道将该矩阵变为好矩阵所需修改的最少元素数量，并希望得到其中一个可能的修改后矩阵。

由于问题有一定难度，请你帮助他！

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 2 \cdot 10^5$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 10^3$）。

接下来输入 $n$ 行，每行包含恰好 $m$ 个字符，且每个字符均为 $0$、$1$、$2$ 或 $3$，描述 Ecrade 的矩阵。

保证所有测试用例的 $n \cdot m$ 总和不超过 $10^6$。

## 输出格式

对于每个测试用例：
1. 第一行输出使矩阵变为好矩阵所需修改的最少元素数量。
2. 随后输出 $n$ 行，每行包含恰好 $m$ 个字符（均为 $0$、$1$、$2$ 或 $3$），描述其中一个可能的修改后矩阵。

若存在多个可行的修改后矩阵，可输出任意一个。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3 3
313
121
313
3 3
000
000
000
4 4
0123
1230
2301
3012
4 4
1232
2110
3122
1311
4 4
1232
2110
3122
1312
```

### 输出

```
3
213
101
312
0
000
000
000
0
0123
1230
2301
3012
6
0132
2310
3131
1313
5
0132
2310
3120
1302
```



---

---
title: "Conditional Operators"
layout: "post"
diff: 省选/NOI-
pid: CF2089D
tag: ['构造']
---

# Conditional Operators

## 题目描述

在 C++ 中，条件运算符 `?:` 的使用规则为：表达式 `x?y:z` 的值为 $$$y$$$（若 $$$x$$$ 为真）或 $$$z$$$（若 $$$x$$$ 为假）。其中 $$$x$$$、$$$y$$$ 和 $$$z$$$ 可以是任意表达式。该运算符具有右结合性，即 `a?b:c?d:e` 等价于 `a?b:(c?d:e)`。数值 $$$0$$$ 表示假，$$$1$$$ 表示真。

给定一个长度为 $$$2n+1$$$ 的二进制字符串，请判断在插入 $$$n$$$ 个条件运算符后，该表达式能否计算结果为 $$$1$$$。允许使用括号。例如，字符串 `10101` 可被转换为 `(1?0:1)?0:1`，其计算结果为 $$$1$$$。

## 输入格式

第一行包含一个整数 $$$t$$$（$$$1 \le t \le 10\,000$$$），表示测试用例数量。

每个测试用例的第一行包含一个整数 $$$n$$$（$$$1 \le n \le 1.5 \cdot 10^5$$$）。

每个测试用例的第二行包含一个长度为 $$$2n + 1$$$ 的二进制字符串。

保证所有测试用例的 $$$n$$$ 之和不超过 $$$1.5 \cdot 10^5$$$。

## 输出格式

对于每个测试用例：
- 若该字符串可被转换为结果为 $$$1$$$ 的表达式，则在第一行输出 `Yes`，并在第二行输出该表达式。允许使用括号，但必须保持原字符串字符顺序，且表达式长度不超过 $$$10n + 1000$$$。
- 否则，在第一行输出 `No`。

## 说明/提示

第一个测试用例对应题目描述中的示例。

第二个测试用例中，无论如何插入条件运算符，结果始终为 $$$0$$$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
2
10101
2
00000
```

### 输出

```
Yes
(1?0:1)?(0):1
No
```



---

---
title: "Keep the Sum"
layout: "post"
diff: 省选/NOI-
pid: CF2103E
tag: ['构造']
---

# Keep the Sum

## 题目描述

You are given an integer $ k $ and an array $ a $ of length $ n $ , where each element satisfies $ 0 \le a_i \le k $ for all $ 1 \le i \le n $ . You can perform the following operation on the array:

- Choose two distinct indices $ i $ and $ j $ ( $ 1 \le i,j \le n $ and $ i \neq j $ ) such that $ a_i + a_j = k $ .
- Select an integer $ x $ satisfying $ -a_j \le x \le a_i $ .
- Decrease $ a_i $ by $ x $ and increase $ a_j $ by $ x $ . In other words, update $ a_i := a_i - x $ and $ a_j := a_j + x $ .

Note that the constraints on $ x $ ensure that all elements of array $ a $ remain between $ 0 $ and $ k $ throughout the operations.

Your task is to determine whether it is possible to make the array $ a $ non-decreasing $ ^{\text{∗}} $ using the above operation. If it is possible, find a sequence of at most $ 3n $ operations that transforms the array into a non-decreasing one.

It can be proven that if it is possible to make the array non-decreasing using the above operation, there exists a solution that uses at most $ 3n $ operations.

 $ ^{\text{∗}} $ An array $ a_1, a_2, \ldots, a_n $ is said to be non-decreasing if for all $ 1 \le i \le n - 1 $ , it holds that $ a_i \le a_{i+1} $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers, $ n $ and $ k $ ( $ 4 \le n \le 2 \cdot 10^5 $ , $ 1 \le k \le 10^9 $ ) — the length of the array $ a $ and the required sum for the operation.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le k $ ) — the elements of array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ -1 $ if it is not possible to make the array non-decreasing using the operation.

Otherwise, output the number of operations $ m $ ( $ 0 \le m \le 3n $ ). On each of the next $ m $ lines, output three integers $ i $ , $ j $ , and $ x $ representing an operation where $ a_i $ is decreased by $ x $ and $ a_j $ is increased by $ x $ .

Note that you are not required to minimize the number of operations. If there are multiple solutions requiring at most $ 3n $ operations, you may output any.

## 说明/提示

In the first test case, the array is already non-decreasing, so we do not need to perform any operations.

In the second test case, we can perform an operation with $ i=4 $ , $ j=1 $ , and $ x=1 $ . $ a_4 $ decreases by $ 1 $ to become $ 5 - 1 = 4 $ while $ a_1 $ increases by $ 1 $ to become $ 1 + 1 = 2 $ . After the operation, the array becomes $ [2, 2, 3, 4, 4] $ , which is non-decreasing.

Note that there are other ways to make the array non-decreasing, all of which would be considered correct as long as they do not use more than $ 3 \cdot n = 15 $ operations.

In the third test case, it is not possible to make the array non-decreasing. This is because there are no distinct pairs of indices $ i $ and $ j $ where $ a_i + a_j = 7 $ , so no operation can be done on the array.

In the fourth test case, the array is transformed as follows:

1. $ [\textbf{0}, 5, 3, 2, 7, 3, 1, \textbf{10}, 4, 0] $
2. $ [0, 5, \textbf{1}, 2, \textbf{9}, 3, 1, 10, 4, 0] $
3. $ [0, 5, 1, 2, \textbf{6}, 3, \textbf{4}, 10, 4, 0] $
4. $ [0, 5, 1, 2, \textbf{3}, 3, 4, 10, \textbf{7}, 0] $
5. $ [0, 5, 1, 2, 3, 3, 4, \textbf{5}, 7, \textbf{5}] $
6. $ [0, \textbf{1}, 1, 2, 3, 3, 4, 5, 7, \textbf{9}] $

## 样例 #1

### 输入

```
4
5 100
1 2 3 4 5
5 6
1 2 3 5 4
5 7
7 1 5 3 1
10 10
2 5 3 2 7 3 1 8 4 0
```

### 输出

```
0
1
4 1 1
-1
6
1 8 2
3 5 2
5 7 3
5 9 3
8 10 5
2 10 4
```



---

---
title: "Spruce Dispute"
layout: "post"
diff: 省选/NOI-
pid: CF2108E
tag: ['构造', '标签483']
---

# Spruce Dispute

## 题目描述

四月的天气已经相当炎热，Polycarp 决定这是拆除他几年前搭建的云杉树的绝佳时机。当他绕着树走了几个小时，积蓄力量时，他注意到一个有趣的现象：这棵云杉实际上是一棵树$^{\text{∗}}$——而且不是普通的树，它由奇数个顶点 $n$ 组成。更特别的是，$n-1$ 个顶点上挂着圣诞装饰品，这些装饰品恰好涂有 $\frac{n-1}{2}$ 种不同的颜色，每种颜色恰好有两个装饰品。剩下的顶点按照传统，挂着树顶的星星。

经过几天的心理准备，Polycarp 终于开始拆除云杉。他先取下了树顶的星星，并开始拆卸一些树枝，这时他突然想到一个自然的问题：如何移除树的一条边，并重新排列装饰品，使得同色装饰品之间的简单路径长度之和尽可能大？

在这个问题中，移除树的一条边的定义如下：选择一对相邻顶点 $a$ 和 $b$（$a < b$），然后从树中移除顶点 $b$，并将 $b$ 的所有相邻顶点（除了 $a$）直接重新连接到 $a$ 上。

Polycarp 在得到这个问题的答案之前无法继续拆除云杉。然而，检查所有可能的选项会花费他数年时间。鉴于你在竞赛编程方面的经验，他向你求助。但你能解决这个争议吗？

$^{\text{∗}}$ 树是指一个无环的连通图。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例的第一行包含一个奇数 $n$（$3 \le n < 2 \cdot 10^5$）——树中顶点的数量。

接下来的 $n-1$ 行描述了树的边，每行给出两个相邻顶点 $u$ 和 $v$（$1 \le u, v \le n$，$u \neq v$）。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，你需要输出两行。

第一行输出一对顶点 $u$ 和 $v$，表示 Polycarp 将要移除的边。

第二行输出一个长度为 $n$ 的数组 $c$，其中 $c[i]$ 表示顶点 $i$ 被分配的正颜色编号（从 $0$ 到 $\frac{n-1}{2}$）。注意，$c[\text{max}(u, v)]$ 必须为 $0$，因为该顶点已被移除。


## 说明/提示

考虑第一个测试用例。

移除连接顶点 $1$ 和 $2$ 的边。之后，顶点 $2$ 将从树中移除，顶点 $3$ 和 $4$ 将被连接到顶点 $1$。

将顶点 $3$ 和 $4$ 涂为第一种颜色，顶点 $1$ 和 $5$ 涂为第二种颜色。同色装饰品之间的简单路径长度之和为 $2 + 2 = 4$。可以证明，这是可能的最大值。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2108E/60feb47fab29e7103e114ad3b20f5966a35c1290.png)

在第二个和第三个例子中，路径长度之和的最大值分别为 $3$ 和 $9$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
5
1 2
2 3
2 4
4 5
5
1 2
1 3
1 4
1 5
7
1 5
5 4
4 3
3 2
2 6
6 7
```

### 输出

```
1 2
2 0 1 1 2
1 5
1 1 2 2 0
4 3
1 3 3 0 2 2 1
```



---

---
title: "Shift It!"
layout: "post"
diff: 省选/NOI-
pid: CF74E
tag: ['构造']
---

# Shift It!

## 题目描述

There is a square box $ 6×6 $ in size. It contains $ 36 $ chips $ 1×1 $ in size. Those chips contain 36 different characters — "0"-"9" and "A"-"Z". There is exactly one chip with each character.

You are allowed to make the following operations: you may choose one of $ 6 $ rows or one of $ 6 $ columns and cyclically shift the chips there to one position to the left or to the right (for the row) or upwards or downwards (for the column). Those operations are allowed to perform several times.

To solve the puzzle is to shift the chips using the above described operations so that they were written in the increasing order (exactly equal to the right picture). An example of solving the puzzle is shown on a picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF74E/0a3a314e2a091acebeaa1e063e0064f39d2f8755.png)Write a program that finds the sequence of operations that solves the puzzle. That sequence should not necessarily be shortest, but you should not exceed the limit of $ 10000 $ operations. It is guaranteed that the solution always exists.

## 输入格式

The input data are represented by 6 lines containing 6 characters each. They are the puzzle's initial position. Those lines contain each character from the string "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" exactly once.

## 输出格式

On the first line print number $ n $ , which is the number of operations. On the next $ n $ lines print the sequence of operations one per line. An operation is described by a word consisting of two characters. The first character shows the direction where the row or the column will be shifted. The possible directions are "L", "R" (to the left, to the right correspondingly, we shift a row), "U", "D" (upwards, downwards correspondingly, we shift a column). The second character is the number of the row (or the column), it is an integer from "1" to "6". The rows are numbered from the top to the bottom, the columns are numbered from the left to the right.

The number of operations should not exceed $ 10^{4} $ . If there are several solutions, print any of them.

## 样例 #1

### 输入

```
01W345
729AB6
CD8FGH
IJELMN
OPKRST
UVQXYZ

```

### 输出

```
2
R2
U3

```



---

---
title: "An unavoidable detour for home"
layout: "post"
diff: 省选/NOI-
pid: CF814E
tag: ['最短路', '构造']
---

# An unavoidable detour for home

## 题目描述

Those unwilling to return home from a long journey, will be affected by the oddity of the snail and lose their way. Mayoi, the oddity's carrier, wouldn't like this to happen, but there's nothing to do with this before a cure is figured out. For now, she would only like to know the enormous number of possibilities to be faced with if someone gets lost.

There are $ n $ towns in the region, numbered from $ 1 $ to $ n $ . The town numbered $ 1 $ is called the capital. The traffic network is formed by bidirectional roads connecting pairs of towns. No two roads connect the same pair of towns, and no road connects a town with itself. The time needed to travel through each of the roads is the same. Lost travelers will not be able to find out how the towns are connected, but the residents can help them by providing the following facts:

- Starting from each town other than the capital, the shortest path (i.e. the path passing through the minimum number of roads) to the capital exists, and is unique;
- Let $ l_{i} $ be the number of roads on the shortest path from town $ i $ to the capital, then $ l_{i}>=l_{i-1} $ holds for all $ 2<=i<=n $ ;
- For town $ i $ , the number of roads connected to it is denoted by $ d_{i} $ , which equals either $ 2 $ or $ 3 $ .

You are to count the number of different ways in which the towns are connected, and give the answer modulo $ 10^{9}+7 $ . Two ways of connecting towns are considered different if a pair $ (u,v) $ ( $ 1<=u,v<=n $ ) exists such there is a road between towns $ u $ and $ v $ in one of them but not in the other.

## 输入格式

The first line of input contains a positive integer $ n $ ( $ 3<=n<=50 $ ) — the number of towns.

The second line contains $ n $ space-separated integers $ d_{1},d_{2},...,d_{n} $ ( $ 2<=d_{i}<=3 $ ) — the number of roads connected to towns $ 1,2,...,n $ , respectively. It is guaranteed that the sum of $ d_{i} $ over all $ i $ is even.

## 输出格式

Output one integer — the total number of different possible ways in which the towns are connected, modulo $ 10^{9}+7 $ .

## 说明/提示

In the first example, the following structure is the only one to satisfy the constraints, the distances from towns $ 2,3,4 $ to the capital are all $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814E/41aec6960c240a1fb09480a0a613ecf71bad9b6b.png)In the second example, the following two structures satisfy the constraints.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814E/5dfe5b5d19d9938739604a89ad14ef6620891ff1.png)

## 样例 #1

### 输入

```
4
3 2 3 2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
2 3 3 2 2

```

### 输出

```
2

```

## 样例 #3

### 输入

```
5
2 2 2 2 2

```

### 输出

```
2

```

## 样例 #4

### 输入

```
20
2 2 2 2 3 2 3 2 2 2 2 2 2 2 2 2 2 3 3 2

```

### 输出

```
82944

```



---

---
title: "Rusty String"
layout: "post"
diff: 省选/NOI-
pid: CF827E
tag: ['字符串', '枚举', '构造']
---

# Rusty String

## 题目描述

Grigory loves strings. Recently he found a metal strip on a loft. The strip had length $ n $ and consisted of letters "V" and "K". Unfortunately, rust has eaten some of the letters so that it's now impossible to understand which letter was written.

Grigory couldn't understand for a long time what these letters remind him of, so he became interested in the following question: if we put a letter "V" or "K" on each unreadable position, which values can the period of the resulting string be equal to?

A period of a string is such an integer $ d $ from $ 1 $ to the length of the string that if we put the string shifted by $ d $ positions to the right on itself, then all overlapping letters coincide. For example, $ 3 $ and $ 5 $ are periods of "VKKVK".

## 输入格式

There are several (at least one) test cases in the input. The first line contains single integer — the number of test cases.

There is an empty line before each test case. Each test case is described in two lines: the first line contains single integer $ n $ ( $ 1<=n<=5·10^{5} $ ) — the length of the string, the second line contains the string of length $ n $ , consisting of letters "V", "K" and characters "?". The latter means the letter on its position is unreadable.

It is guaranteed that the sum of lengths among all test cases doesn't exceed $ 5·10^{5} $ .

For hacks you can only use tests with one test case.

## 输出格式

For each test case print two lines. In the first line print the number of possible periods after we replace each unreadable letter with "V" or "K". In the next line print all these values in increasing order.

## 说明/提示

In the first test case from example we can obtain, for example, "VKKVK", which has periods $ 3 $ and $ 5 $ .

In the second test case we can obtain "VVVVVV" which has all periods from $ 1 $ to $ 6 $ .

In the third test case string "KVKV" has periods $ 2 $ and $ 4 $ , and string "KVKK" has periods $ 3 $ and $ 4 $ .

## 样例 #1

### 输入

```
3
 
5
V??VK
 
6
??????
 
4
?VK?

```

### 输出

```
2
3 5
6
1 2 3 4 5 6
3
2 3 4

```



---

---
title: "Restore the Tree"
layout: "post"
diff: 省选/NOI-
pid: CF871E
tag: ['构造']
---

# Restore the Tree

## 题目描述

Petya had a tree consisting of $ n $ vertices numbered with integers from $ 1 $ to $ n $ . Accidentally he lost his tree.

Petya remembers information about $ k $ vertices: distances from each of them to each of the $ n $ tree vertices.

Your task is to restore any tree that satisfies the information that Petya remembers or report that such tree doesn't exist.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2<=n<=30000 $ , $ 1<=k<=min(200,n) $ ) — the number of vertices in the tree and the number of vertices about which Petya remembers distance information.

The following $ k $ lines contain remembered information. The $ i $ -th line contains $ n $ integers $ d_{i,1},d_{i,2},...,d_{i,n} $ ( $ 0<=d_{i,j}<=n-1 $ ), where $ d_{i,j} $ — the distance to $ j $ -th vertex from the $ i $ -th vertex that Petya remembers.

## 输出格式

If there are no suitable trees, print -1.

In the other case, print $ n-1 $ lines: each line should contain two vertices connected by edge in the required tree. You can print edges and vertices in an edge in any order. The tree vertices are enumerated from $ 1 $ to $ n $ .

If there are many solutions print any of them.

## 说明/提示

Picture for the first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF871E/6f212029526e4d77c3a6bc5fe4ad25b3afc1824a.png)

## 样例 #1

### 输入

```
5 2
0 1 2 3 2
2 1 0 1 2

```

### 输出

```
2 1
3 2
4 3
5 2

```

## 样例 #2

### 输入

```
3 1
1 2 1

```

### 输出

```
-1

```



---

---
title: "Willem, Chtholly and Seniorious"
layout: "post"
diff: 省选/NOI-
pid: CF896C
tag: ['暴力数据结构', '颜色段均摊（珂朵莉树 ODT）', '枚举', '排序', '构造']
---

# Willem, Chtholly and Seniorious

## 题目描述

【题面】
请你写一种奇怪的数据结构，支持：
- $1$  $l$  $r$  $x$ ：将$[l,r]$ 区间所有数加上$x$ 
- $2$  $l$  $r$  $x$ ：将$[l,r]$ 区间所有数改成$x$ 
- $3$  $l$  $r$  $x$ ：输出将$[l,r]$ 区间从小到大排序后的第$x$ 个数是的多少(即区间第$x$ 小，数字大小相同算多次，保证 $1\leq$  $x$  $\leq$  $r-l+1$  )
- $4$  $l$  $r$  $x$  $y$ ：输出$[l,r]$ 区间每个数字的$x$ 次方的和模$y$ 的值(即($\sum^r_{i=l}a_i^x$ ) $\mod y$ )

## 输入格式

输入一行四个整数$n,m,seed,v_{max}$ （$1\leq $  $n,m\leq 10^{5}$  ,$0\leq seed \leq 10^{9}+7$  $,1\leq vmax \leq 10^{9} $ ）
其中$n$ 表示数列长度，$m$ 表示操作次数，后面两个用于生成输入数据。
数据生成的伪代码如下
![](https://cdn.luogu.org/upload/pic/13887.png )

其中上面的op指题面中提到的四个操作。

## 输出格式

对于每个操作3和4，输出一行仅一个数。

## 样例 #1

### 输入

```
10 10 7 9

```

### 输出

```
2
1
0
3

```

## 样例 #2

### 输入

```
10 10 9 9

```

### 输出

```
1
1
3
3

```



---

---
title: "Weighting a Tree"
layout: "post"
diff: 省选/NOI-
pid: CF901D
tag: ['生成树', '最近公共祖先 LCA', '构造']
---

# Weighting a Tree

## 题目描述

给你一个有 $n$ 个顶点与 $m$ 条边的无向图，那些顶点的编号依次为 $1$ 到 $n$。

再给你 $n$ 个整数 $C[1],c[2],…,C[n]$，每一个数都在区间 $[-n,n]$ 之间。保证 $C[v]$ 的奇偶性与顶点 $v$ 的度的奇偶性相同。一个顶点的的度是指连接到它的边数。

你需要按照下列的要求为所有边写上一个在 $-2\cdot n^2$ 与 $2\cdot n^2$ 之间的一个重量：对于任何一个顶点 $v$，所有连接到这个顶点的边的重量和等于 $C[v]$。或者，确定这是不可能达到的。

## 输入格式

第一行是两个整数 $n$ 和 $m$ $\ (2\le n\le 10^5$,$n-1\le m\le 10^5)$，为边与顶点的个数。

第二行有 $n$ 个整数 $C[1],C[2]……C[n]\ (-n\le C[i]\le n$)，$C[i]$ 是连接到 $i$ 的边的权值之和。保证 $C[v]$ 的奇偶性与顶点 $v$ 的度的奇偶性相同。

之后的 $m$ 行是用来描述无向图的边的。对于第 $i$ 行，有 $a[i]$ 和 $b[i]$ 两个整数$\ (1\le a[i],b[i]\le n,a[i]≠b[i])$，表示第 $i$ 条边连接点 $a[i]$ 和 $b[i]$ 。

保证给出的无向图是联通的且不含有重边与自环。

## 输出格式

如果无解，输出"NO"。

否则输出"YES"和$m$行，每一行表示对应编号的边的权值。

Translated by @Microelectronics

## 样例 #1

### 输入

```
3 3
2 2 2
1 2
2 3
1 3

```

### 输出

```
YES
1
1
1

```

## 样例 #2

### 输入

```
4 3
-1 0 2 1
1 2
2 3
3 4

```

### 输出

```
YES
-1
1
1

```

## 样例 #3

### 输入

```
6 6
3 5 5 5 1 5
1 4
3 2
4 3
4 5
3 5
5 6

```

### 输出

```
YES
3
5
3
-1
-3
5

```

## 样例 #4

### 输入

```
4 4
4 4 2 4
1 2
2 3
3 4
4 1

```

### 输出

```
NO
```



---

---
title: "Round Marriage"
layout: "post"
diff: 省选/NOI-
pid: CF981F
tag: ['二分', '枚举', '构造']
---

# Round Marriage

## 题目描述

It's marriage season in Ringland!

Ringland has a form of a circle's boundary of length $ L $ . There are $ n $ bridegrooms and $ n $ brides, and bridegrooms decided to marry brides.

Of course, each bridegroom should choose exactly one bride, and each bride should be chosen by exactly one bridegroom.

All objects in Ringland are located on the boundary of the circle, including the capital, bridegrooms' castles and brides' palaces. The castle of the $ i $ -th bridegroom is located at the distance $ a_i $ from the capital in clockwise direction, and the palace of the $ i $ -th bride is located at the distance $ b_i $ from the capital in clockwise direction.

Let's define the inconvenience of a marriage the maximum distance that some bride should walk along the circle from her palace to her bridegroom's castle in the shortest direction (in clockwise or counter-clockwise direction).

Help the bridegrooms of Ringland to choose brides in such a way that the inconvenience of the marriage is the smallest possible.

## 输入格式

The first line contains two integers $ n $ and $ L $ ( $ 1 \leq n \leq 2 \cdot 10^{5} $ , $ 1 \leq L \leq 10^{9} $ ) — the number of bridegrooms and brides and the length of Ringland.

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < L $ ) — the distances from the capital to the castles of bridegrooms in clockwise direction.

The next line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 0 \leq b_i < L $ ) — the distances from the capital to the palaces of brides in clockwise direction.

## 输出格式

In the only line print the smallest possible inconvenience of the wedding, where the inconvenience is the largest distance traveled by a bride.

## 说明/提示

In the first example the first bridegroom should marry the second bride, the second bridegroom should marry the first bride. This way, the second bride should walk the distance of $ 1 $ , and the first bride should also walk the same distance. Thus, the inconvenience is equal to $ 1 $ .

In the second example let $ p_i $ be the bride the $ i $ -th bridegroom will marry. One of optimal $ p $ is the following: $ (6,8,1,4,5,10,3,2,7,9) $ .

## 样例 #1

### 输入

```
2 4
0 1
2 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10 100
3 14 15 92 65 35 89 79 32 38
2 71 82 81 82 84 5 90 45 23

```

### 输出

```
27

```



---

---
title: "A Trance of Nightfall"
layout: "post"
diff: 省选/NOI-
pid: CF989E
tag: ['进制', '矩阵乘法', '构造']
---

# A Trance of Nightfall

## 题目描述

 The cool breeze blows gently, the flowing water ripples steadily."Flowing and passing like this, the water isn't gone ultimately; Waxing and waning like that, the moon doesn't shrink or grow eventually."

"Everything is transient in a way and perennial in another."

Kanno doesn't seem to make much sense out of Mino's isolated words, but maybe it's time that they enjoy the gentle breeze and the night sky — the inexhaustible gifts from nature.

Gazing into the sky of stars, Kanno indulges in a night's tranquil dreams.





There is a set $ S $ of $ n $ points on a coordinate plane.

Kanno starts from a point $ P $ that can be chosen on the plane. $ P $ is not added to $ S $ if it doesn't belong to $ S $ . Then the following sequence of operations (altogether called a move) is repeated several times, in the given order:

1. Choose a line $ l $ such that it passes through at least two elements in $ S $ and passes through Kanno's current position. If there are multiple such lines, one is chosen equiprobably.
2. Move to one of the points that belong to $ S $ and lie on $ l $ . The destination is chosen equiprobably among all possible ones, including Kanno's current position (if it does belong to $ S $ ).

There are $ q $ queries each consisting of two integers $ (t_i, m_i) $ . For each query, you're to help Kanno maximize the probability of the stopping position being the $ t_i $ -th element in $ S $ after $ m_i $ moves with a proper selection of $ P $ , and output this maximum probability. Note that according to rule 1, $ P $ should belong to at least one line that passes through at least two points from $ S $ .

## 输入格式

The first line contains a positive integer $ n $ ( $ 2 \leq n \leq 200 $ ) — the number of points in $ S $ .

The $ i $ -th of the following $ n $ lines contains two space-separated integers $ x_i $ and $ y_i $ ( $ -10^4 \leq x_i, y_i \leq 10^4 $ ) — the coordinates of the $ i $ -th point in $ S $ . The input guarantees that for all $ 1 \leq i \lt j \leq n $ , $ (x_i, y_i) \neq (x_j, y_j) $ holds.

The next line contains a positive integer $ q $ ( $ 1 \leq q \leq 200 $ ) — the number of queries.

Each of the following $ q $ lines contains two space-separated integers $ t $ and $ m $ ( $ 1 \leq t_i \leq n $ , $ 1 \leq m_i \leq 10^4 $ ) — the index of the target point and the number of moves, respectively.

## 输出格式

Output $ q $ lines each containing a decimal number — the $ i $ -th among them denotes the maximum probability of staying on the $ t_i $ -th point after $ m_i $ steps, with a proper choice of starting position $ P $ .

Your answer will be considered correct if each number in your output differs from the corresponding one in jury's answer by at most $ 10^{-6} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer is considered correct if $ |a - b| \le 10^{-6} $ .

## 说明/提示

The points in $ S $ and possible candidates for line $ l $ are depicted in the following figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF989E/9dc6a2e53d51df32abc295e2febe0114d0e3d73f.png)For the first query, when $ P = (-1, -3) $ , $ l $ is uniquely determined to be $ 3x = y $ , and thus Kanno will move to $ (0, 0) $ with a probability of $ \frac 1 2 $ .

For the third query, when $ P = (2, 2) $ , $ l $ is chosen equiprobably between $ x + y = 4 $ and $ x = y $ . Kanno will then move to the other four points with a probability of $ \frac 1 2 \cdot \frac 1 3 = \frac 1 6 $ each, or stay at $ (2, 2) $ with a probability of $ \frac 1 3 $ .

## 样例 #1

### 输入

```
5
0 0
1 3
2 2
3 1
4 4
10
1 1
2 1
3 1
4 1
5 1
3 2
3 3
3 4
3 5
3 6

```

### 输出

```
0.50000000000000000000
0.50000000000000000000
0.33333333333333331483
0.50000000000000000000
0.50000000000000000000
0.18518518518518517491
0.15226337448559670862
0.14494741655235482414
0.14332164812274550414
0.14296036624949901017

```



---

---
title: "Nikita and Order Statistics"
layout: "post"
diff: 省选/NOI-
pid: CF993E
tag: ['快速傅里叶变换 FFT', '构造']
---

# Nikita and Order Statistics

## 题目描述

Nikita likes tasks on order statistics, for example, he can easily find the $ k $ -th number in increasing order on a segment of an array. But now Nikita wonders how many segments of an array there are such that a given number $ x $ is the $ k $ -th number in increasing order on this segment. In other words, you should find the number of segments of a given array such that there are exactly $ k $ numbers of this segment which are less than $ x $ .

Nikita wants to get answer for this question for each $ k $ from $ 0 $ to $ n $ , where $ n $ is the size of the array.

## 输入格式

The first line contains two integers $ n $ and $ x $ $ (1 \le n \le 2 \cdot 10^5, -10^9 \le x \le 10^9) $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ $ (-10^9 \le a_i \le 10^9) $ — the given array.

## 输出格式

Print $ n+1 $ integers, where the $ i $ -th number is the answer for Nikita's question for $ k=i-1 $ .

## 样例 #1

### 输入

```
5 3
1 2 3 4 5

```

### 输出

```
6 5 4 0 0 0 
```

## 样例 #2

### 输入

```
2 6
-5 9

```

### 输出

```
1 2 0 
```

## 样例 #3

### 输入

```
6 99
-1 -1 -1 -1 -1 -1

```

### 输出

```
0 6 5 4 3 2 1 
```



---

