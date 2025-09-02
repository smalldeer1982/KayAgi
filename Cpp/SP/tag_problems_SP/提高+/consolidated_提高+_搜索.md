---
title: "SUBSET - Balanced Cow Subsets"
layout: "post"
diff: 提高+/省选-
pid: SP11469
tag: ['搜索', '折半搜索 meet in the middle']
---

# SUBSET - Balanced Cow Subsets

## 题目描述

Farmer John's owns N cows (2 <= N <= 20), where cow i produces M(i) units of milk each day (1 <= M(i) <= 100,000,000).

 FJ wants to streamline the process of milking his cows every day, so he installs a brand new milking machine in his barn.

Unfortunately, the machine turns out to be far too sensitive: it only works properly if the cows on the left side of the

barn have the exact same total milk output as the cows on the right side of the barn!

Let us call a subset of cows "balanced" if it can be partitioned into two groups having equal milk output.

 Since only a balanced subset of cows can make the milking machine work, FJ wonders how many subsets of his N cows are balanced.

 Please help him compute this quantity.

 `INPUT FORMAT:` `* Line 1: The integer N.` `* Lines 2..1+N: Line i+1 contains M(i).` `SAMPLE INPUT` `4 ` `1 ` `2 ` `3 ` `4` `INPUT DETAILS:` `There are 4 cows, with milk outputs 1, 2, 3, and 4.` `OUTPUT FORMAT: ` `* Line 1: The number of balanced subsets of cows. ` `SAMPLE OUTPUT:` `3` `OUTPUT DETAILS: ` `There are three balanced subsets: the subset {1,2,3}, which can be partitioned into {1,2} and {3}, the subset {1,3,4}, ` `which can be partitioned into {1,3} and {4}, and the subset {1,2,3,4} which can be partitioned into {1,4} and {2,3}.`



---

---
title: "SOLIT - Solitaire"
layout: "post"
diff: 提高+/省选-
pid: SP120
tag: ['广度优先搜索 BFS', '折半搜索 meet in the middle']
---

# SOLIT - Solitaire

## 题目描述

Solitaire是一款在8x8棋盘上玩的游戏。棋盘的行和列分别为1到8，从顶部到底部以及从左到右依次编号。

棋盘上有4个相同的棋子。在每一次移动中，一个棋子可以：

- 移动一格到一个相邻的空格（向上、向下、向左或向右）

- 跳过另一个相邻的棋子到与之相邻一个空格（向上、向下、向左或向右）

## 输入格式

输入数据以一个整数t开头，表示测试案例数。然后是t个案例。

对于每个案例，两行中每一行包含8个整数a1,a2,...,a8，每个数之间由一个空格分开，以描述每个棋盘上棋子的分布。整数a（2j-1）和a（2j）(1 <= j <= 4) 分别描述了一个棋子的行与列的位置。

## 输出格式

对于每个测试案例，输出数据应当包含一个单词——

如果由输入数据第一行所描述的棋盘分布可以在8次移动之内转变为第二行所描述的棋盘分布，则输出“YES”，否则输出“NO”。

## 样例 #1

### 输入

```
1

4 4 4 5 5 4 6 5

2 4 3 3 3 6 4 6
```

### 输出

```
YES
```



---

---
title: "BST - Binary Search Tree"
layout: "post"
diff: 提高+/省选-
pid: SP3544
tag: ['模拟', '搜索', '平衡树']
---

# BST - Binary Search Tree

## 题目描述

众所周知，二叉搜索树是一棵树，其中每个节点最多具有两个子节点（左子节点和右子节点）。

二叉搜索树的每个节点都有一个权值。对于每个节点如果存在一个权值$X$，则其左子树中的权值小于$X$，右子树中的权值大于$X$.

现在给你一个$1$~$N$（包括$N$）之间的整数序列，其中保证每个数字在序列中只出现一次。

请你将序列建成一颗二叉搜索树，我们规定将第一个数字的值存在根节点中，并按给定的序列顺序插入其他数字。

换句话说，你需要对每个插入的数字运行函数$insert(X$，$root)$：

该函数伪代码如下：

	插入（编号X，节点N）

 		将计数器C增加1      

    	 if X小于节点N中的权值        

        	if N没有左子节点           

            	创建一个权值为X的新节点，并将其设置为节点N的左子节点          
        	else insert（X，节点N的左子节点） 
    	 else if （X大于节点N中的权值） 

        	if N没有右子节点              

            	创建一个权值为X的新节点，并将其设置为节点N的右子节点      

        	else insert（X，节点N的右子节点） 

请你编写一个程序，计算在依次插入每个数字后计数器$C$的值并输出。计数器$C$最初为$0$。

## 输入格式

第一行包含一个正整数$N(1<=N<=300000)$

之后有$N$行，每行一个数字，代表给定的序列。

输入数据保证这些数都是区间$[1,N]$中的整数且不会出现重复

## 输出格式

一共$N$行，每行一个数字，表示按给定序列顺序插入每个数字之后计数器$C$的值

感谢@___new2zy___ 提供的翻译

## 样例 #1

### 输入

```
8
3
5
1
6
8
7
2
4
```

### 输出

```
0
1
2
4
7
11
13
15
```



---

---
title: "ZUMA - ZUMA"
layout: "post"
diff: 提高+/省选-
pid: SP6340
tag: ['动态规划 DP', '搜索', '区间 DP']
---

# ZUMA - ZUMA

## 题目描述

祖玛游戏是这样的：有一列$ N$ 个有颜色的珠子，如果触碰连续 $K$ 个或更多同色的珠子，那么它们就会消失，其余的珠子按照原来顺序接在一起。

现在你每次可以发射任意颜色的珠子，发射在任意位置（开头、结尾以及任意两个之间）。

注意，如果有连续 $K$ 个或更多同色的珠子，你可以不立即消去他们。

问最少需要几发可以消掉所有的珠子。

## 输入格式

第一行 $N,K$

第二行 $N$ 个数 $a_i$，不同的数表示不同的颜色

## 输出格式

一个答案。

【数据规模】
对于所有数据，$1≤N≤100,2≤K≤5,1≤a_i≤100$

## 样例 #1

### 输入

```
2 5
1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10 4
3 3 3 3 2 3 1 1 1 3
```

### 输出

```
4
```



---

---
title: "QTREE2 - Query on a tree II"
layout: "post"
diff: 提高+/省选-
pid: SP913
tag: ['倍增', '深度优先搜索 DFS', '最近公共祖先 LCA']
---

# QTREE2 - Query on a tree II

## 题目描述

 You are given a tree (an undirected acyclic connected graph) with **N** nodes, and edges numbered 1, 2, 3...**N**-1. Each edge has an integer value assigned to it, representing its length.

 We will ask you to perfrom some instructions of the following form:

- **DIST a b** : ask for the distance between node **a** and node **b**  
   or
- **KTH a b k** : ask for the **k**-th node on the path from node **a** to node **b**

 **Example:**  
**N** = 6   
 1 2 1 // edge connects node 1 and node 2 has cost 1   
 2 4 1   
 2 5 2   
 1 3 1   
 3 6 2   
  
 Path from node 4 to node 6 is 4 -> 2 -> 1 -> 3 -> 6   
**DIST 4 6** : answer is 5 (1 + 1 + 1 + 2 = 5)   
**KTH 4 6 4** : answer is 3 (the 4-th node on the path from node 4 to node 6 is 3)

## 输入格式

 The first line of input contains an integer **t**, the number of test cases (**t** <= 25). **t** test cases follow.

For each test case:

- In the first line there is an integer **N** (**N** <= 10000)
- In the next **N**-1 lines, the i-th line describes the i-th edge: a line with three integers **a b c** denotes an edge between **a**, **b** of cost **c** (**c** <= 100000)
- The next lines contain instructions **"DIST a b"** or **"KTH a b k"**
- The end of each test case is signified by the string "**DONE**".

There is one blank line between successive tests.

## 输出格式

For each **"DIST"** or **"KTH"** operation, write one integer representing its result.

Print one blank line after each test.

## 样例 #1

### 输入

```
1

6
1 2 1
2 4 1
2 5 2
1 3 1
3 6 2
DIST 4 6
KTH 4 6 4
DONE
```

### 输出

```
5
3
```



---

