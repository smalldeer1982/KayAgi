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

