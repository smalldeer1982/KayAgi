---
title: "Palindrome-less Arrays"
layout: "post"
diff: 普及+/提高
pid: CF1140E
tag: ['组合数学']
---

# Palindrome-less Arrays

## 题目描述

Let's denote that some array $ b $ is bad if it contains a subarray $ b_l, b_{l+1}, \dots, b_{r} $ of odd length more than $ 1 $ ( $ l < r $ and $ r - l + 1 $ is odd) such that $ \forall i \in \{0, 1, \dots, r - l\} $ $ b_{l + i} = b_{r - i} $ .

If an array is not bad, it is good.

Now you are given an array $ a_1, a_2, \dots, a_n $ . Some elements are replaced by $ -1 $ . Calculate the number of good arrays you can obtain by replacing each $ -1 $ with some integer from $ 1 $ to $ k $ .

Since the answer can be large, print it modulo $ 998244353 $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2 \le n, k \le 2 \cdot 10^5 $ ) — the length of array $ a $ and the size of "alphabet", i. e., the upper bound on the numbers you may use to replace $ -1 $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ a_i = -1 $ or $ 1 \le a_i \le k $ ) — the array $ a $ .

## 输出格式

Print one integer — the number of good arrays you can get, modulo $ 998244353 $ .

## 样例 #1

### 输入

```
2 3
-1 -1

```

### 输出

```
9

```

## 样例 #2

### 输入

```
5 2
1 -1 -1 1 2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
5 3
1 -1 -1 1 2

```

### 输出

```
2

```

## 样例 #4

### 输入

```
4 200000
-1 -1 12345 -1

```

### 输出

```
735945883

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
title: "Placing Jinas"
layout: "post"
diff: 普及+/提高
pid: CF1696E
tag: ['数学', '排列组合']
---

# Placing Jinas

## 题目描述

We say an infinite sequence $ a_{0}, a_{1}, a_2, \ldots $ is non-increasing if and only if for all $ i\ge 0 $ , $ a_i \ge a_{i+1} $ .

There is an infinite right and down grid. The upper-left cell has coordinates $ (0,0) $ . Rows are numbered $ 0 $ to infinity from top to bottom, columns are numbered from $ 0 $ to infinity from left to right.

There is also a non-increasing infinite sequence $ a_{0}, a_{1}, a_2, \ldots $ . You are given $ a_0 $ , $ a_1 $ , $ \ldots $ , $ a_n $ ; for all $ i>n $ , $ a_i=0 $ . For every pair of $ x $ , $ y $ , the cell with coordinates $ (x,y) $ (which is located at the intersection of $ x $ -th row and $ y $ -th column) is white if $ y<a_x $ and black otherwise.

Initially there is one doll named Jina on $ (0,0) $ . You can do the following operation.

- Select one doll on $ (x,y) $ . Remove it and place a doll on $ (x,y+1) $ and place a doll on $ (x+1,y) $ .

Note that multiple dolls can be present at a cell at the same time; in one operation, you remove only one. Your goal is to make all white cells contain $ 0 $ dolls.

What's the minimum number of operations needed to achieve the goal? Print the answer modulo $ 10^9+7 $ .

## 输入格式

The first line of input contains one integer $ n $ ( $ 1\le n\le 2\cdot 10^5 $ ).

The second line of input contains $ n+1 $ integers $ a_0,a_1,\ldots,a_n $ ( $ 0\le a_i\le 2\cdot 10^5 $ ).

It is guaranteed that the sequence $ a $ is non-increasing.

## 输出格式

Print one integer — the answer to the problem, modulo $ 10^9+7 $ .

## 说明/提示

Consider the first example. In the given grid, cells $ (0,0),(0,1),(1,0),(1,1) $ are white, and all other cells are black. Let us use triples to describe the grid: triple $ (x,y,z) $ means that there are $ z $ dolls placed on cell $ (x,y) $ . Initially the state of the grid is $ (0,0,1) $ .

One of the optimal sequence of operations is as follows:

- Do the operation with $ (0,0) $ . Now the state of the grid is $ (1,0,1),(0,1,1) $ .
- Do the operation with $ (0,1) $ . Now the state of the grid is $ (1,0,1),(1,1,1),(0,2,1) $ .
- Do the operation with $ (1,0) $ . Now the state of the grid is $ (1,1,2),(0,2,1),(2,0,1) $ .
- Do the operation with $ (1,1) $ . Now the state of the grid is $ (1,1,1),(0,2,1),(2,0,1),(1,2,1),(2,1,1) $ .
- Do the operation with $ (1,1) $ . Now the state of the grid is $ (0,2,1),(2,0,1),(1,2,2),(2,1,2) $ .

Now all white cells contain $ 0 $ dolls, so we have achieved the goal with $ 5 $ operations.

## 样例 #1

### 输入

```
2
2 2 0
```

### 输出

```
5
```

## 样例 #2

### 输入

```
10
12 11 8 8 6 6 6 5 3 2 1
```

### 输出

```
2596
```



---

---
title: "Madoka and The Corruption Scheme"
layout: "post"
diff: 普及+/提高
pid: CF1717D
tag: ['组合数学', '排列组合']
---

# Madoka and The Corruption Scheme

## 题目描述

Madoka decided to entrust the organization of a major computer game tournament "OSU"!

In this tournament, matches are held according to the "Olympic system". In other words, there are $ 2^n $ participants in the tournament, numbered with integers from $ 1 $ to $ 2^n $ . There are $ n $ rounds in total in the tournament. In the $ i $ -th round there are $ 2^{n - i} $ matches between two players (one of whom is right, the other is left), after which the winners go further along the tournament grid, and the losing participants are eliminated from the tournament. Herewith, the relative order in the next round does not change. And the winner of the tournament — is the last remaining participant.

But the smaller the participant's number, the more he will pay Madoka if he wins, so Madoka wants the participant with the lowest number to win. To do this, she can arrange the participants in the first round as she likes, and also determine for each match who will win — the participant on the left or right.

But Madoka knows that tournament sponsors can change the winner in matches no more than $ k $ times. (That is, if the participant on the left won before the change, then the participant on the right will win after the change, and if the participant on the right won, then the participant on the left will win after the change).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1717D/f3b4c42531ac8b0aab0fa40e7e46069a137caf77.png)So, the first image shows the tournament grid that Madoka made, where the red lines denote who should win the match. And the second one shows the tournament grid, after one change in the outcome of the match by sponsors (a match between $ 1 $ and $ 3 $ players).Print the minimum possible number of the winner in the tournament, which Madoka can get regardless of changes in sponsors. But since the answer can be very large, output it modulo $ 10^9 + 7 $ . Note that we need to minimize the answer, and only then take it modulo.

## 输入格式

The first and the only line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 10^5, 1 \le k \le \min(2^n - 1, 10^9) $ ) — the number of rounds in the tournament and the number of outcomes that sponsors can change.

## 输出格式

Print exactly one integer — the minimum number of the winner modulo $ 10^9 + 7 $

## 说明/提示

In the first example, there is only one match between players $ 1 $ and $ 2 $ , so the sponsors can always make player $ 2 $ wins.

The tournament grid from the second example is shown in the picture in the statement.

## 样例 #1

### 输入

```
1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 2
```

### 输出

```
7
```



---

---
title: "Circular Mirror"
layout: "post"
diff: 普及+/提高
pid: CF1725C
tag: ['组合数学', '排列组合']
---

# Circular Mirror

## 题目描述

Pak Chanek has a mirror in the shape of a circle. There are $ N $ lamps on the circumference numbered from $ 1 $ to $ N $ in clockwise order. The length of the arc from lamp $ i $ to lamp $ i+1 $ is $ D_i $ for $ 1 \leq i \leq N-1 $ . Meanwhile, the length of the arc between lamp $ N $ and lamp $ 1 $ is $ D_N $ .

Pak Chanek wants to colour the lamps with $ M $ different colours. Each lamp can be coloured with one of the $ M $ colours. However, there cannot be three different lamps such that the colours of the three lamps are the same and the triangle made by considering the three lamps as vertices is a right triangle (triangle with one of its angles being exactly $ 90 $ degrees).

The following are examples of lamp colouring configurations on the circular mirror.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/f662b018d5c25548ad3c12ebf7297c4fe9cddb27.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/d15118feff1296e48df6066dea2761fdbf3bbba3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/904b8c54d18751fcd9444e012c7c141ddaf812b7.png)Figure 1. an example of an incorrect colouring because lamps $ 1 $ , $ 2 $ , and $ 3 $ form a right triangleFigure 2. an example of a correct colouringFigure 3. an example of a correct colouringBefore colouring the lamps, Pak Chanek wants to know the number of distinct colouring configurations he can make. Count the number of distinct possible lamp colouring configurations, modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains two integers $ N $ and $ M $ ( $ 1 \le N \le 3 \cdot 10^5 $ , $ 2 \le M \le 3 \cdot 10^5 $ ) — the number of lamps in the mirror and the number of different colours used.

The second line contains $ N $ integers $ D_1, D_2, \ldots, D_N $ ( $ 1 \le D_i \le 10^9 $ ) — the lengths of the arcs between the lamps in the mirror.

## 输出格式

An integer representing the number of possible lamp colouring configurations, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, all correct lamp colouring configurations are $ [1, 1, 2, 1] $ , $ [1, 1, 2, 2] $ , $ [1, 2, 1, 2] $ , $ [1, 2, 2, 1] $ , $ [1, 2, 2, 2] $ , $ [2, 1, 1, 1] $ , $ [2, 1, 1, 2] $ , $ [2, 1, 2, 1] $ , $ [2, 2, 1, 1] $ , and $ [2, 2, 1, 2] $ .

## 样例 #1

### 输入

```
4 2
10 10 6 14
```

### 输出

```
10
```

## 样例 #2

### 输入

```
1 2
10
```

### 输出

```
2
```



---

---
title: "Meta-set"
layout: "post"
diff: 普及+/提高
pid: CF1735D
tag: ['枚举', '组合数学']
---

# Meta-set

## 题目描述

### 题目翻译
你有一副牌，每张牌包含$k$个特征，每个特征等于集合 $\{0，1，2\}$ 中的一个值。显然，共有$3^k$
不同的情况。
 
定义一个三张牌为好的，当且仅当：对于同一位上的特征，要么**相同**，要么**两两不同**。如果**三张牌**所有$k$对特征都是好的，则称为一个集合。

如果一组**五张牌**中有严格意义上的**一个以上**的集合，则称为元组。在给定的$n$个不同的牌中，有多少个元组？

## 输入格式

输入的第一行包含两个整数 $n$ 和 $k$ $( 1\le n\le 10^3)$ $( 1 \le k \le 20）$,表示桌子上的牌的数量和牌的特征的数量。在接下来的$n$行中，将对牌进行描述。

描述卡片的每一行包含$k$个整数，表示卡片特征$\{0，1，2\}$。所有卡片都是**不同的**。

## 输出格式

输出一个整数表示元组的数量。

## 样例 #1

### 输入

```
8 4
0 0 0 0
0 0 0 1
0 0 0 2
0 0 1 0
0 0 2 0
0 1 0 0
1 0 0 0
2 2 0 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7 4
0 0 0 0
0 0 0 1
0 0 0 2
0 0 1 0
0 0 2 0
0 1 0 0
0 2 0 0
```

### 输出

```
3
```

## 样例 #3

### 输入

```
9 2
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2
```

### 输出

```
54
```

## 样例 #4

### 输入

```
20 4
0 2 0 0
0 2 2 2
0 2 2 1
0 2 0 1
1 2 2 0
1 2 1 0
1 2 2 1
1 2 0 1
1 1 2 2
1 1 0 2
1 1 2 1
1 1 1 1
2 1 2 0
2 1 1 2
2 1 2 1
2 1 1 1
0 1 1 2
0 0 1 0
2 2 0 0
2 0 0 2
```

### 输出

```
0
```



---

---
title: "Doremy's Pegging Game"
layout: "post"
diff: 普及+/提高
pid: CF1764D
tag: ['数学', '组合数学']
---

# Doremy's Pegging Game

## 题目描述

Doremy has $ n+1 $ pegs. There are $ n $ red pegs arranged as vertices of a regular $ n $ -sided polygon, numbered from $ 1 $ to $ n $ in anti-clockwise order. There is also a blue peg of slightly smaller diameter in the middle of the polygon. A rubber band is stretched around the red pegs.

Doremy is very bored today and has decided to play a game. Initially, she has an empty array $ a $ . While the rubber band does not touch the blue peg, she will:

1. choose $ i $ ( $ 1 \leq i \leq n $ ) such that the red peg $ i $ has not been removed;
2. remove the red peg $ i $ ;
3. append $ i $ to the back of $ a $ .

Doremy wonders how many possible different arrays $ a $ can be produced by the following process. Since the answer can be big, you are only required to output it modulo $ p $ . $ p $ is guaranteed to be a prime number.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764D/39b25225514736b577fbcbcd5d0b5bf29ecc4db4.png) game with $ n=9 $ and $ a=[7,5,2,8,3,9,4] $ and another game with $ n=8 $ and $ a=[3,4,7,1,8,5,2] $

## 输入格式

The first line contains two integers $ n $ and $ p $ ( $ 3 \leq n \leq 5000 $ , $ 10^8 \le p \le 10^9 $ ) — the number of red pegs and the modulo respectively.

 $ p $ is guaranteed to be a prime number.

## 输出格式

Output a single integer, the number of different arrays $ a $ that can be produced by the process described above modulo $ p $ .

## 说明/提示

In the first test case, $ n=4 $ , some possible arrays $ a $ that can be produced are $ [4,2,3] $ and $ [1,4] $ . However, it is not possible for $ a $ to be $ [1] $ or $ [1,4,3] $ .

## 样例 #1

### 输入

```
4 100000007
```

### 输出

```
16
```

## 样例 #2

### 输入

```
1145 141919831
```

### 输出

```
105242108
```



---

---
title: "Moscow Gorillas"
layout: "post"
diff: 普及+/提高
pid: CF1793D
tag: ['数学', '组合数学']
---

# Moscow Gorillas

## 题目描述

In winter, the inhabitants of the Moscow Zoo are very bored, in particular, it concerns gorillas. You decided to entertain them and brought a permutation $ p $ of length $ n $ to the zoo.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

The gorillas had their own permutation $ q $ of length $ n $ . They suggested that you count the number of pairs of integers $ l, r $ ( $ 1 \le l \le r \le n $ ) such that $ \operatorname{MEX}([p_l, p_{l+1}, \ldots, p_r])=\operatorname{MEX}([q_l, q_{l+1}, \ldots, q_r]) $ .

The $ \operatorname{MEX} $ of the sequence is the minimum integer positive number missing from this sequence. For example, $ \operatorname{MEX}([1, 3]) = 2 $ , $ \operatorname{MEX}([5]) = 1 $ , $ \operatorname{MEX}([3, 1, 2, 6]) = 4 $ .

You do not want to risk your health, so you will not dare to refuse the gorillas.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the permutations length.

The second line contains $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ) — the elements of the permutation $ p $ .

The third line contains $ n $ integers $ q_1, q_2, \ldots, q_n $ ( $ 1 \le q_i \le n $ ) — the elements of the permutation $ q $ .

## 输出格式

Print a single integer — the number of suitable pairs $ l $ and $ r $ .

## 说明/提示

In the first example, two segments are correct – $ [1, 3] $ with $ \operatorname{MEX} $ equal to $ 4 $ in both arrays and $ [3, 3] $ with $ \operatorname{MEX} $ equal to $ 1 $ in both of arrays.

In the second example, for example, the segment $ [1, 4] $ is correct, and the segment $ [6, 7] $ isn't correct, because $ \operatorname{MEX}(5, 4) \neq \operatorname{MEX}(1, 4) $ .

## 样例 #1

### 输入

```
3
1 3 2
2 1 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
7 3 6 2 1 5 4
6 7 2 5 3 1 4
```

### 输出

```
16
```

## 样例 #3

### 输入

```
6
1 2 3 4 5 6
6 5 4 3 2 1
```

### 输出

```
11
```



---

---
title: "One-Dimensional Puzzle"
layout: "post"
diff: 普及+/提高
pid: CF1931G
tag: ['组合数学', '分类讨论']
---

# One-Dimensional Puzzle

## 题目描述

You have a one-dimensional puzzle, all the elements of which need to be put in one row, connecting with each other. All the puzzle elements are completely white and distinguishable from each other only if they have different shapes.

Each element has straight borders at the top and bottom, and on the left and right it has connections, each of which can be a protrusion or a recess. You cannot rotate the elements.

You can see that there are exactly $ 4 $ types of elements. Two elements can be connected if the right connection of the left element is opposite to the left connection of the right element.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1931G/ab3dee044a8e18206fe7c695b7a089bda5931d43.png) All possible types of elements. The puzzle contains $ c_1, c_2, c_3, c_4 $ elements of each type. The puzzle is considered complete if you have managed to combine all elements into one long chain. You want to know how many ways this can be done.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^5 $ ) — the number of input test cases. The descriptions of the test cases follow.

The description of each test case contains $ 4 $ integers $ c_i $ ( $ 0 \le c_i \le 10^6 $ ) — the number of elements of each type, respectively.

It is guaranteed that the sum of $ c_i $ for all test cases does not exceed $ 4 \cdot 10^6 $ .

## 输出格式

For each test case, print one integer — the number of possible ways to solve the puzzle.

Two methods are considered different if there is $ i $ , such that the types of elements at the $ i $ position in these methods differ.

Since the answer can be very large, output it modulo $ 998244353 $ .

If it is impossible to solve the puzzle, print $ 0 $ .

## 样例 #1

### 输入

```
11
1 1 1 1
1 2 5 10
4 6 100 200
900000 900000 900000 900000
0 0 0 0
0 0 566 239
1 0 0 0
100 0 100 0
0 0 0 4
5 5 0 2
5 4 0 5
```

### 输出

```
4
66
0
794100779
1
0
1
0
1
36
126
```



---

---
title: "How Does the Rook Move?"
layout: "post"
diff: 普及+/提高
pid: CF1957C
tag: ['动态规划 DP', '组合数学', '排列组合']
---

# How Does the Rook Move?

## 题目描述

你在一个 $n\times n$ 的棋盘上玩一个游戏。

你每次可以选择在 $(r,c)$ 的位置放置一个**白色的车**，使得放置后所有车无法通过水平或垂直的方向攻击到其它车（无论颜色）。如果 $r\not=c$ 则电脑在 $(c,r)$ 处放一个**黑色的车**，可以证明，如果你的操作合法，电脑操作必定合法。

现在你已经放置了 $k$ 个白色的车（显然电脑也已经进行了对应操作），如果你继续放车直到没有合法的位置放车，则游戏结束。

你希望知道游戏结束时形成的局面的可能性。

答案对 $10^9+7$ 取模。

两个局面不同当且仅当某个位置上的车颜色不同或其中一个局面放了车而另一个没有。

## 输入格式

第一行一个整数 $t$，表示数据组数。

接下来对于每组数据，第一行两个整数 $n,k$。

接下来 $k$ 行，每行两个整数 $r_i,c_i$，表示已经放置的白车的位置。

## 输出格式

共 $t$ 行，每行一个整数，表示答案。

## 说明/提示

对于全部数据，满足 $ 1 \leq t \leq 10^4 $，$ 1 \leq n \leq 3 \times 10^5 $ , $ 0 \leq k \leq n $，$\sum n\le3\times10^5$。

## 样例 #1

### 输入

```
3
4 1
1 2
8 1
7 6
1000 4
4 4
952 343
222 333
90 91
```

### 输出

```
3
331
671968183
```



---

---
title: "Expected Median"
layout: "post"
diff: 普及+/提高
pid: CF1999F
tag: ['组合数学', '排列组合']
---

# Expected Median

## 题目描述

Arul has a binary array $ ^{\text{∗}} $ $ a $ of length $ n $ .

He will take all subsequences $ ^{\text{†}} $ of length $ k $ ( $ k $ is odd) of this array and find their median. $ ^{\text{‡}} $

What is the sum of all these values?

As this sum can be very large, output it modulo $ 10^9 + 7 $ . In other words, print the remainder of this sum when divided by $ 10^9 + 7 $ .

 $ ^{\text{∗}} $ A binary array is an array consisting only of zeros and ones.

 $ ^{\text{†}} $ An array $ b $ is a subsequence of an array $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements. Subsequences don't have to be contiguous.

 $ ^{\text{‡}} $ The median of an array of odd length $ k $ is the $ \frac{k+1}{2} $ -th element when sorted.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \leq k \leq n \leq 2 \cdot 10^5 $ ,  $ k $ is odd) — the length of the array and the length of the subsequence, respectively.

The second line of each test case contains $ n $ integers $ a_i $ ( $ 0 \leq a_i \leq 1 $ ) — the elements of the array.

It is guaranteed that sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the sum modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case, there are four subsequences of $ [1,0,0,1] $ with length $ k=3 $ :

- $ [1,0,0] $ : median $ = 0 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [0,0,1] $ : median $ = 0 $ .

 The sum of the results is $ 0+1+1+0=2 $ .In the second test case, all subsequences of length $ 1 $ have median $ 1 $ , so the answer is $ 5 $ .

## 样例 #1

### 输入

```
8
4 3
1 0 0 1
5 1
1 1 1 1 1
5 5
0 1 0 1 0
6 3
1 0 1 0 1 1
4 3
1 0 1 1
5 3
1 0 1 1 0
2 1
0 0
34 17
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
```

### 输出

```
2
5
0
16
4
7
0
333606206
```



---

---
title: "Goodbye, Banker Life"
layout: "post"
diff: 普及+/提高
pid: CF2072F
tag: ['排列组合', '位运算']
---

# Goodbye, Banker Life

## 题目描述

怪物正在逼近城市，为了保护它，Akito 必须在城市周围创建一个防护场。众所周知，防护场有不同的等级。Akito 选择了等级为 $n$ 的防护场。为了构建这个防护场，需要一个特殊咒语，即伟大魔法三角（表示为二维数组 $T$）的第 $n$ 行。我们将这个数组称为 $T$。

魔法三角的定义如下：

- 第 $i$ 行包含 $i$ 个整数。
- 第一行唯一的整数是 $k$。
- 设第 $i$ 行第 $j$ 个元素为 $T_{i,j}$，则：

$$
T_{i,j} = \begin{cases} 
T_{i-1,j-1} \oplus T_{i-1,j}, & \text{if } 1 < j < i \\ 
T_{i-1,j}, & \text{if } j = 1 \\ 
T_{i-1,j-1}, & \text{if } j = i 
\end{cases}
$$

其中 $a \oplus b$ 表示整数 $a$ 和 $b$ 的按位异或运算。

请帮助 Akito 在怪物抵达城市前找到这个无限魔法三角的第 $n$ 行整数。

## 输入格式

第一行包含整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的唯一一行包含两个整数 $n$ 和 $k$（$1 \le n \le 10^6$，$1 \le k < 2^{31}$）——分别表示 Akito 需要的行索引和伟大魔法三角第一行的整数。

保证所有测试用例的 $n$ 之和不超过 $10^6$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数——伟大魔法三角第 $n$ 行的元素。

## 说明/提示

在第一个示例中，根据定义，伟大魔法三角的第一行为 $[5]$。

在第二个示例中，$T_{2,1} = T_{1,1} = 10$ 且 $T_{2,2} = T_{1,1} = 10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
1 5
2 10
3 16
9 1
1 52
```

### 输出

```
5
10 10
16 0 16
1 0 0 0 0 0 0 0 1
52
```



---

---
title: "Even String"
layout: "post"
diff: 普及+/提高
pid: CF2086D
tag: ['背包 DP', '组合数学']
---

# Even String

## 题目描述

你需要构造一个由小写拉丁字母组成的字符串 $s$，满足以下条件：
- 对于任意两个满足 $s_{i} = s_{j}$ 的下标 $i$ 和 $j$，这两个下标之差的绝对值为偶数，即 $|i - j| \bmod 2 = 0$。

构造任意字符串太简单了，因此你会被给定一个包含 $26$ 个数字的数组 $c$ —— 表示字符串 $s$ 中每个字母必须出现的次数。也就是说，对于每个 $i \in [1, 26]$，拉丁字母表中的第 $i$ 个字母必须恰好出现 $c_i$ 次。

你的任务是计算满足所有这些条件的不同字符串 $s$ 的数量。由于答案可能非常大，请输出其对 $998\,244\,353$ 取模后的结果。

## 输入格式

每个测试包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 10^{4}$）—— 测试用例的数量。接下来是测试用例的描述。

每个测试用例包含 $26$ 个整数 $c_{i}$（$0 \le c_{i} \le 5 \cdot 10^{5}$）—— 数组 $c$ 的元素。

输入数据的额外限制：
- 每个测试用例的 $c_{i}$ 之和为正；
- 所有测试用例的 $c_{i}$ 之和不超过 $5 \cdot 10^{5}$。

## 输出格式

对于每个测试用例，输出一个整数 —— 满足条件的字符串 $s$ 的数量，对 $998\,244\,353$ 取模后的结果。


## 说明/提示

- 在第一个测试用例中，有 $4$ 个满足条件的字符串："abak"、"akab"、"baka" 和 "kaba"。


翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2 1 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
3 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 0 0 0 0 1 0 3 0 0 0 0 0 0 0 0 0 0 0
1 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 233527 233827
```

### 输出

```
4
960
0
1
789493841
```



---

---
title: "She knows..."
layout: "post"
diff: 普及+/提高
pid: CF2092E
tag: ['数学', '组合数学']
---

# She knows...

## 题目描述

D. Pippy 正在为家中的"黑白派对"做准备。他只需要重新粉刷地下室的 floor，该 floor 可表示为 $n \times m$ 的棋盘。

在上次派对后，整个棋盘除 $k$ 个单元格 $(x_1, y_1), (x_2, y_2), \ldots, (x_k, y_k)$ 外均被涂成绿色，这些单元格已被涂成白色或黑色。为了即将到来的派对，D. Pippy 想要将剩余的绿色单元格涂成黑色或白色。同时，他要求重新粉刷后棋盘上相邻颜色不同的单元格对数量为偶数。

形式化地，若定义集合：
$$A = \left\{((i_1, j_1), (i_2, j_2)) \ | \ 1 \le i_1, i_2 \le n, 1 \le j_1, j_2 \le m, i_1+j_1 < i_2+j_2, |i_1-i_2|+|j_1-j_2| = 1, \operatorname{color}(i_1, j_1) \neq \operatorname{color}(i_2, j_2) \right\},$$
其中 $\operatorname{color}(x, y)$ 表示单元格 $(x, y)$ 的颜色，则要求 $|A|$ 为偶数。

请帮助 D. Pippy 计算满足条件的粉刷方案数。由于答案可能很大，请输出其对 $10^9 + 7$ 取模的结果。

## 输入格式

每个测试包含多个测试用例。输入数据第一行包含一个整数 $t$ ($1 \le t \le 10^4$) —— 测试用例数量。接下来是测试用例描述。

每个测试用例的第一行包含三个整数 $n, m, k$ ($3 \le n, m \le 10^9$; $1 \le k \le 2 \cdot 10^5$) —— 棋盘的尺寸和初始非绿色单元格的数量。

接下来每个测试用例的 $k$ 行中，第 $i$ 行包含三个整数 $x_i, y_i$ 和 $c_i$ ($1 \le x_i \le n$; $1 \le y_i \le m$; $c_i \in \{0, 1\}$) —— 单元格的坐标及其颜色（白色对应 $c_i = 0$，黑色对应 $c_i = 1$）。保证所有单元格坐标互不相同。

保证所有测试用例的 $k$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数 —— 答案对 $10^9 + 7$ 取模的结果。


## 说明/提示

第一个测试案例中，绿色单元格 $(2, 1), (2, 2), (2, 3)$ 共有 $4$ 种合法涂色方案，分别为：$(1, 1, 0)$，$(0, 0, 1)$，$(1, 0, 0)$，$(0, 1, 1)$（颜色按单元格顺序排列），如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2092E/0ff35e90f545116ecc7d2fbe2de16f35bcaedb89.png)  
第二个测试案例中，棋盘已全部涂色且相邻异色对数量为奇数，因此答案为 $0$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
3 3 6
1 1 0
1 2 1
1 3 0
3 1 1
3 2 0
3 3 1
3 4 12
1 1 0
1 2 1
1 3 0
1 4 1
2 1 1
2 2 0
2 3 1
2 4 0
3 1 0
3 2 1
3 3 0
3 4 1
```

### 输出

```
4
0
```



---

---
title: "Matrix game"
layout: "post"
diff: 普及+/提高
pid: CF2120D
tag: ['组合数学', '鸽笼原理']
---

# Matrix game

## 题目描述

Aryan and Harshith play a game. They both start with three integers $ a $ , $ b $ , and $ k $ . Aryan then gives Harshith two integers $ n $ and $ m $ . Harshith then gives Aryan a matrix $ X $ with $ n $ rows and $ m $ columns, such that each of the elements of $ X $ is between $ 1 $ and $ k $ (inclusive). After that, Aryan wins if he can find a submatrix $ ^{\text{∗}} $ $ Y $ of $ X $ with $ a $ rows and $ b $ columns such that all elements of $ Y $ are equal.

For example, when $ a=2, b=2, k=6, n=3 $ and $ m=3 $ , if Harshith gives Aryan the matrix below, it is a win for Aryan as it has a submatrix of size $ 2\times 2 $ with all elements equal to $ 1 $ as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120D/ff9ee31dfc04aa73a7daca458dede1d4462758ef.png) Example of a matrix where Aryan wins Aryan gives you the values of $ a $ , $ b $ , and $ k $ . He asks you to find the lexicographically minimum tuple $ (n,m) $ that he should give to Harshith such that Aryan always wins. Help Aryan win the game. Assume that Harshith plays optimally. The values of $ n $ and $ m $ can be large, so output them modulo $ 10^9+7 $ . A tuple $ (n_1, m_1) $ is said to be lexicographically smaller than $ (n_2, m_2) $ if either $ n_1<n_2 $ or $ n_1=n_2 $ and $ m_1<m_2 $ .

 $ ^{\text{∗}} $ A submatrix of a matrix is obtained by removing some rows and/or columns from the original matrix.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

Each test case contains a single line with three space-separated integers $ a, b $ and $ k $ ( $ 1\leq a,b,k\leq 10^5 $ ).

It is guaranteed that the sum of $ \max(a, b, k) $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single line containing two space-separated integers $ n $ and $ m $ , denoting the answer to the problem. The values of $ n $ and $ m $ can be large, so output them modulo $ 10^9+7 $ .

## 说明/提示

For the first test case, every $ n\times m $ matrix contains a $ 1\times 1 $ submatrix with all elements equal. $ (1,1) $ is the lexicographically minimum tuple among all of them.

For the second test case, it can be verified that whatever $ 3\times 7 $ matrix Harshith gives to Aryan, Aryan can always win by finding a $ 2\times 2 $ submatrix with all elements equal. $ (3,7) $ is also the lexicographically minimum tuple among all possible tuples where Aryan always wins.

## 样例 #1

### 输入

```
3
1 1 5
2 2 2
90000 80000 70000
```

### 输出

```
1 1
3 7
299929959 603196135
```



---

---
title: "Numbers"
layout: "post"
diff: 普及+/提高
pid: CF213B
tag: ['动态规划 DP', '枚举', '组合数学']
---

# Numbers

## 题目描述

Furik loves writing all sorts of problems, especially such that he can't solve himself. You've got one of his problems, the one Furik gave to Rubik. And Rubik asks you to solve it.

There is integer $ n $ and array $ a $ , consisting of ten integers, indexed by numbers from 0 to 9. Your task is to count the number of positive integers with the following properties:

- the number's length does not exceed $ n $ ;
- the number doesn't have leading zeroes;
- digit $ i $ $ (0<=i<=9) $ occurs in the number at least $ a[i] $ times.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=100) $ . The next line contains 10 integers $ a[0] $ , $ a[1] $ , $ ... $ , $ a[9] $ $ (0<=a[i]<=100) $ — elements of array $ a $ . The numbers are separated by spaces.

## 输出格式

On a single line print the remainder of dividing the answer to the problem by $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample number 9 meets the requirements.

In the second sample number 10 meets the requirements.

In the third sample numbers 10, 110, 210, 120, 103 meet the requirements. There are other suitable numbers, 36 in total.

## 样例 #1

### 输入

```
1
0 0 0 0 0 0 0 0 0 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
1 1 0 0 0 0 0 0 0 0

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3
1 1 0 0 0 0 0 0 0 0

```

### 输出

```
36

```



---

---
title: "Pluses everywhere"
layout: "post"
diff: 普及+/提高
pid: CF520E
tag: ['组合数学']
---

# Pluses everywhere

## 题目描述

Vasya is sitting on an extremely boring math class. To have fun, he took a piece of paper and wrote out $ n $ numbers on a single line. After that, Vasya began to write out different ways to put pluses ("+") in the line between certain digits in the line so that the result was a correct arithmetic expression; formally, no two pluses in such a partition can stand together (between any two adjacent pluses there must be at least one digit), and no plus can stand at the beginning or the end of a line. For example, in the string 100500, ways 100500 (add no pluses), 1+00+500 or 10050+0 are correct, and ways 100++500, +1+0+0+5+0+0 or 100500+ are incorrect.

The lesson was long, and Vasya has written all the correct ways to place exactly $ k $ pluses in a string of digits. At this point, he got caught having fun by a teacher and he was given the task to calculate the sum of all the resulting arithmetic expressions by the end of the lesson (when calculating the value of an expression the leading zeros should be ignored). As the answer can be large, Vasya is allowed to get only its remainder modulo $ 10^{9}+7 $ . Help him!

## 输入格式

The first line contains two integers, $ n $ and $ k $ ( $ 0<=k&lt;n<=10^{5} $ ).

The second line contains a string consisting of $ n $ digits.

## 输出格式

Print the answer to the problem modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample the result equals $ (1+08)+(10+8)=27 $ .

In the second sample the result equals $ 1+0+8=9 $ .

## 样例 #1

### 输入

```
3 1
108

```

### 输出

```
27
```

## 样例 #2

### 输入

```
3 2
108

```

### 输出

```
9
```



---

---
title: "Array"
layout: "post"
diff: 普及+/提高
pid: CF57C
tag: ['数学', '组合数学', '逆元']
---

# Array

## 题目描述

Chris the Rabbit has been interested in arrays ever since he was a child. At the moment he is researching arrays with the length of $ n $ , containing only integers from $ 1 $ to $ n $ . He is not good at math, that's why some simple things drive him crazy. For example, yesterday he grew keen on counting how many different beautiful arrays there are. Chris thinks that an array is beautiful if it meets one of the two conditions:

- each elements, starting from the second one, is no more than the preceding one
- each element, starting from the second one, is no less than the preceding one

Having got absolutely mad at himself and at math, Chris came to Stewie and Brian to ask them for help. However, they only laughed at him and said that the answer is too simple and not interesting. Help Chris the Rabbit to find the answer at last.

## 输入格式

The single line contains an integer $ n $ which is the size of the array ( $ 1<=n<=10^{5} $ ).

## 输出格式

You must print the answer on a single line. As it can be rather long, you should print it modulo $ 1000000007 $ .

## 样例 #1

### 输入

```
2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3

```

### 输出

```
17

```



---

