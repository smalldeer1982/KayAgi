---
title: "Appropriate Team"
layout: "post"
diff: 省选/NOI-
pid: CF1016G
tag: ['状态合并', '素数判断,质数,筛法', '概率论']
---

# Appropriate Team

## 题目描述

Since next season are coming, you'd like to form a team from two or three participants. There are $ n $ candidates, the $ i $ -th candidate has rank $ a_i $ . But you have weird requirements for your teammates: if you have rank $ v $ and have chosen the $ i $ -th and $ j $ -th candidate, then $ GCD(v, a_i) = X $ and $ LCM(v, a_j) = Y $ must be met.

You are very experienced, so you can change your rank to any non-negative integer but $ X $ and $ Y $ are tied with your birthdate, so they are fixed.

Now you want to know, how many are there pairs $ (i, j) $ such that there exists an integer $ v $ meeting the following constraints: $ GCD(v, a_i) = X $ and $ LCM(v, a_j) = Y $ . It's possible that $ i = j $ and you form a team of two.

 $ GCD $ is the greatest common divisor of two number, $ LCM $ — the least common multiple.

## 输入格式

First line contains three integers $ n $ , $ X $ and $ Y $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le X \le Y \le 10^{18} $ ) — the number of candidates and corresponding constants.

Second line contains $ n $ space separated integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^{18} $ ) — ranks of candidates.

## 输出格式

Print the only integer — the number of pairs $ (i, j) $ such that there exists an integer $ v $ meeting the following constraints: $ GCD(v, a_i) = X $ and $ LCM(v, a_j) = Y $ . It's possible that $ i = j $ .

## 说明/提示

In the first example next pairs are valid: $ a_j = 1 $ and $ a_i = [2, 4, 6, 8, 10, 12] $ or $ a_j = 2 $ and $ a_i = [2, 4, 6, 8, 10, 12] $ . The $ v $ in both cases can be equal to $ 2 $ .

In the second example next pairs are valid:

- $ a_j = 1 $ and $ a_i = [1, 5, 7, 11] $ ;
- $ a_j = 2 $ and $ a_i = [1, 5, 7, 11, 10, 8, 4, 2] $ ;
- $ a_j = 3 $ and $ a_i = [1, 3, 5, 7, 9, 11] $ ;
- $ a_j = 6 $ and $ a_i = [1, 3, 5, 7, 9, 11, 12, 10, 8, 6, 4, 2] $ .

## 样例 #1

### 输入

```
12 2 2
1 2 3 4 5 6 7 8 9 10 11 12

```

### 输出

```
12

```

## 样例 #2

### 输入

```
12 1 6
1 3 5 7 9 11 12 10 8 6 4 2

```

### 输出

```
30

```



---

---
title: "Covered Points"
layout: "post"
diff: 省选/NOI-
pid: CF1036E
tag: ['概率论']
---

# Covered Points

## 题目描述

You are given $ n $ segments on a Cartesian plane. Each segment's endpoints have integer coordinates. Segments can intersect with each other. No two segments lie on the same line.

Count the number of distinct points with integer coordinates, which are covered by at least one segment.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 1000 $ ) — the number of segments.

Each of the next $ n $ lines contains four integers $ Ax_i, Ay_i, Bx_i, By_i $ ( $ -10^6 \le Ax_i, Ay_i, Bx_i, By_i \le 10^6 $ ) — the coordinates of the endpoints $ A $ , $ B $ ( $ A \ne B $ ) of the $ i $ -th segment.

It is guaranteed that no two segments lie on the same line.

## 输出格式

Print a single integer — the number of distinct points with integer coordinates, which are covered by at least one segment.

## 说明/提示

The image for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1036E/328bc786470ca0c6c881c66bf4ab063a98d10f53.png)Several key points are marked blue, the answer contains some non-marked points as well.

The image for the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1036E/eec87126bd479256c1ebc7932fb835380371e1c1.png)

## 样例 #1

### 输入

```
9
0 0 4 4
-1 5 4 0
4 0 4 4
5 2 11 2
6 1 6 7
5 6 11 6
10 1 10 7
7 0 9 8
10 -1 11 -1

```

### 输出

```
42

```

## 样例 #2

### 输入

```
4
-1 2 1 2
-1 0 1 0
-1 0 0 3
0 3 1 0

```

### 输出

```
7

```



---

---
title: "Network Safety"
layout: "post"
diff: 省选/NOI-
pid: CF1039C
tag: ['并查集', '枚举', '概率论']
---

# Network Safety

## 题目描述

题意：

给你一个有$n$点个和$m$条边的图，第$i$个点的权值为$c_i$。

定义图为安全的条件对于所有的边都保证$c_l≠c_r$

请你求出对于任意的$x$，集合$s$中所有点的点权$xor\quad x$后图仍然安全，这样的$x$和$s$的组合的数量。

答案对于$1e9+7$取模

保证一开始给出的图是安全的。

## 输入格式

第一行一共三个整数$n(n<=500000),m(m<=min(\frac{n*(n-1)}{2},500000)),k(k<=60)$

第二行一共$n$个整数$c_i(c_i<=2^k-1)$

接下来的$m$行每行两个整数$l,r$，表示$l$和$r$之间有边

## 输出格式

一共一个整数，表示答案

## 样例 #1

### 输入

```
4 4 2
0 1 0 1
1 2
2 3
3 4
4 1

```

### 输出

```
50

```

## 样例 #2

### 输入

```
4 5 3
7 1 7 2
1 2
2 3
3 4
4 1
2 4

```

### 输出

```
96

```



---

---
title: "AI robots"
layout: "post"
diff: 省选/NOI-
pid: CF1045G
tag: ['线段树', '树套树', '概率论']
---

# AI robots

## 题目描述

In the last mission, MDCS has successfully shipped $ N $ AI robots to Mars. Before they start exploring, system initialization is required so they are arranged in a line. Every robot can be described with three numbers: position ( $ x_i $ ), radius of sight ( $ r_i $ ) and IQ ( $ q_i $ ).

Since they are intelligent robots, some of them will talk if they see each other. Radius of sight is inclusive, so robot can see other all robots in range $ [x_i - r_i, x_i + r_i] $ . But they don't walk to talk with anybody, but only with robots who have similar IQ. By similar IQ we mean that their absolute difference isn't more than $ K $ .

 Help us and calculate how many pairs of robots are going to talk with each other, so we can timely update their software and avoid any potential quarrel.

## 输入格式

The first line contains two integers, numbers $ N (1 \leq N \leq 10^5)  $ and $ K (0 \leq K \leq 20) $ .

Next $ N $ lines contain three numbers each $ x_i, r_i, q_i (0 \leq x_i,r_i,q_i \leq 10^9) $ — position, radius of sight and IQ of every robot respectively.

## 输出格式

Output contains only one number — solution to the problem.

## 说明/提示

The first robot can see the second, but not vice versa. The first robot can't even see the third. The second and the third robot can see each other and their IQs don't differ more than 2 so only one conversation will happen.

## 样例 #1

### 输入

```
3 2
3 6 1
7 3 10
10 5 8

```

### 输出

```
1
```



---

---
title: "Crime Management"
layout: "post"
diff: 省选/NOI-
pid: CF107D
tag: ['字符串', '深度优先搜索 DFS', '概率论']
---

# Crime Management

## 题目描述

Zeyad 想要在埃及犯下 $n$ 起罪行，并且不受惩罚。罪行有几种类型。例如，贿赂是一种罪行，但如果重复两次，它就不被视为犯罪。因此，贿赂在重复偶数次时不被视为犯罪。超速也是一种罪行，但如果其重复的次数是 5 的倍数，它也不被视为犯罪。

更具体地说，已知有 $c$ 条关于罪行重复的条件。每个条件描述了罪行的类型 $t_{i}$ 及其重复的次数限制 $m_{i}$ 。如果 Zeyad 犯下的罪行 $t_{i}$ 的次数是 $m_{i}$ 的倍数，则 Zeyad 不会因为该罪行而受到惩罚。如果某种罪行出现多次，满足其中任意一个条件即可不受惩罚。当然，如果某罪行的次数为零，Zeyad 对该罪行无罪。

现在，Zeyad 想知道有多少种方式可以精确犯下 $n$ 起罪行且不受惩罚。

罪行的顺序是重要的。更正式地说，犯下 $n$ 起罪行的两种方式（序列 $w1$ 和 $w2$ ）如果对所有 $1 \leq i \leq n$ ，$w1_{i} = w2_{i}$ ，那么它们是相同的方式。

## 输入格式

第一行包含两个整数 $n$ 和 $c$ ($0 \leq n \leq 10^{18}, 0 \leq c \leq 1000$) —— Zeyad 想要犯下的罪行数量和他知道的条件数量。

接下来是 $c$ 条条件的定义。有 $26$ 种类型的罪行。每个罪行的定义由罪行类型（一个大写拉丁字母）和其重复次数的限制组成。

每个罪行的重复次数限制是一个正整数，并且所有限制的乘积不超过 $123$ 。输入中可能有重复的条件。

若某罪行的重复次数限制为 $1$ ，无论犯多少次都不会受到惩罚。法律的严格性由其非强制性来弥补。

显然，如果某罪行未在条件集中列出，那么 Zeyad 不会考虑它，因为犯下它不可避免地会受到惩罚。

请不要在 C++ 中使用 %lld 格式符来读写 64 位整数，建议使用 cin 流（你也可以使用 %I64d 格式符）。

## 输出格式

输出精确犯下 $n$ 起罪行且不受惩罚的不同方式数量，结果对 $12345$ 取模。

## 说明/提示

在第一个测试用例中，16 种方式是：AAAAA，AAABB，AABAB，AABBA，ABAAB，ABABA，ABBAA，BAAAB，BAABA，BABAA，BBAAA，ABBBB，BABBB，BBABB，BBBAB，BBBBA。

## 样例 #1

### 输入

```
5 2
A 1
B 2

```

### 输出

```
16

```

## 样例 #2

### 输入

```
6 3
A 1
B 2
C 3

```

### 输出

```
113

```

## 样例 #3

### 输入

```
8 3
A 2
A 3
B 2

```

### 输出

```
128

```



---

---
title: "Maze"
layout: "post"
diff: 省选/NOI-
pid: CF123E
tag: ['概率论', '期望']
---

# Maze

## 题目描述

A maze is represented by a tree (an undirected graph, where exactly one way exists between each pair of vertices). In the maze the entrance vertex and the exit vertex are chosen with some probability. The exit from the maze is sought by Deep First Search. If there are several possible ways to move, the move is chosen equiprobably. Consider the following pseudo-code:

```plain
DFS(x)
    if x == exit vertex then
        finish search
    flag[x] <- TRUE
    random shuffle the vertices' order in V(x) // here all permutations have equal probability to be chosen
    for i <- 1 to length[V] do
        if flag[V[i]] = FALSE then
            count++;
            DFS(y);
    count++;
```

$ V(x) $ is the list vertices adjacent to $ x $ . The $ flag $ array is initially filled as FALSE. $ DFS $ initially starts with a parameter of an entrance vertex. When the search is finished, variable $ count $ will contain the number of moves.

Your task is to count the mathematical expectation of the number of moves one has to do to exit the maze.

## 输入格式

The first line determines the number of vertices in the graph $ n $ ( $ 1<=n<=10^{5} $ ). The next $ n-1 $ lines contain pairs of integers $ a_{i} $ and $ b_{i} $ , which show the existence of an edge between $ a_{i} $ and $ b_{i} $ vertices ( $ 1<=a_{i},b_{i}<=n $ ). It is guaranteed that the given graph is a tree.

Next $ n $ lines contain pairs of non-negative numbers $ x_{i} $ and $ y_{i} $ , which represent the probability of choosing the $ i $ -th vertex as an entrance and exit correspondingly. The probabilities to choose vertex $ i $ as an entrance and an exit equal ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF123E/0240d8f3c959727649615a9c4b8bbbdbc401999b.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF123E/4e43637d1b15e1f62f6536d616a94de5b4b829ea.png) correspondingly. The sum of all $ x_{i} $ and the sum of all $ y_{i} $ are positive and do not exceed $ 10^{6} $ .

## 输出格式

Print the expectation of the number of moves. The absolute or relative error should not exceed $ 10^{-9} $ .

## 说明/提示

In the first sample the entrance vertex is always 1 and the exit vertex is always 2.

In the second sample the entrance vertex is always 1 and the exit vertex with the probability of 2/5 will be 2 of with the probability if 3/5 will be 3. The mathematical expectations for the exit vertices 2 and 3 will be equal (symmetrical cases). During the first move one can go to the exit vertex with the probability of 0.5 or to go to a vertex that's not the exit vertex with the probability of 0.5. In the first case the number of moves equals 1, in the second one it equals 3. The total mathematical expectation is counted as $ 2/5×(1×0.5+3×0.5)+3/5×(1×0.5+3×0.5) $

## 样例 #1

### 输入

```
2
1 2
0 1
1 0

```

### 输出

```
1.00000000000000000000

```

## 样例 #2

### 输入

```
3
1 2
1 3
1 0
0 2
0 3

```

### 输出

```
2.00000000000000000000

```

## 样例 #3

### 输入

```
7
1 2
1 3
2 4
2 5
3 6
3 7
1 1
1 1
1 1
1 1
1 1
1 1
1 1

```

### 输出

```
4.04081632653
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
title: "Balance"
layout: "post"
diff: 省选/NOI-
pid: CF17C
tag: ['字符串', '枚举', '概率论']
---

# Balance

## 题目描述

1. 选择两个相邻字符，将第一个字符替换成第二个。 
2. 选择两个相邻字符，将第二个字符替换成第一个。 这样，通过任意多次的操作，可以得到许多不同的串，为了追求字符的平衡， 我们要求a,b,c三种字符在字符串中出现的次数两两之差都不能大于1。

你的任 务是，统计给定字符串通过任意多次的操作，能够得到的不同的平衡串的个数。

## 输入格式

输入文件包含2行。 第一行包含1个正整数n，表示字符串长度。 第二行包含1个长度为n的字符串。

## 输出格式

输出共1行，包含1个正整数，表示能够得到的平衡串的数量。由于答案可 能很大，因此输出时要对51123987取模。

## 样例 #1

### 输入

```
4
abca

```

### 输出

```
7

```

## 样例 #2

### 输入

```
4
abbc

```

### 输出

```
3

```

## 样例 #3

### 输入

```
2
ab

```

### 输出

```
1

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
title: "Number Challenge"
layout: "post"
diff: 省选/NOI-
pid: CF235E
tag: ['数学', '枚举', '概率论']
---

# Number Challenge

## 题目描述

Let's denote $ d(n) $ as the number of divisors of a positive integer $ n $ . You are given three integers $ a $ , $ b $ and $ c $ . Your task is to calculate the following sum:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF235E/6b4d9893ce96bd0459ff1289a8bf3491052ac12a.png)Find the sum modulo $ 1073741824 $ $ (2^{30}) $ .

## 输入格式

The first line contains three space-separated integers $ a $ , $ b $ and $ c $ ( $ 1<=a,b,c<=2000 $ ).

## 输出格式

Print a single integer — the required sum modulo $ 1073741824 $ $ (2^{30}) $ .

## 说明/提示

For the first example.

- $ d(1·1·1)=d(1)=1 $ ;
- $ d(1·1·2)=d(2)=2 $ ;
- $ d(1·2·1)=d(2)=2 $ ;
- $ d(1·2·2)=d(4)=3 $ ;
- $ d(2·1·1)=d(2)=2 $ ;
- $ d(2·1·2)=d(4)=3 $ ;
- $ d(2·2·1)=d(4)=3 $ ;
- $ d(2·2·2)=d(8)=4 $ .

So the result is $ 1+2+2+3+2+3+3+4=20 $ .

## 样例 #1

### 输入

```
2 2 2

```

### 输出

```
20

```

## 样例 #2

### 输入

```
4 4 4

```

### 输出

```
328

```

## 样例 #3

### 输入

```
10 10 10

```

### 输出

```
11536

```



---

---
title: "Close Vertices"
layout: "post"
diff: 省选/NOI-
pid: CF293E
tag: ['点分治', '树状数组', '概率论']
---

# Close Vertices

## 题目描述

You've got a weighted tree, consisting of $ n $ vertices. Each edge has a non-negative weight. The length of the path between any two vertices of the tree is the number of edges in the path. The weight of the path is the total weight of all edges it contains.

Two vertices are close if there exists a path of length at most $ l $ between them and a path of weight at most $ w $ between them. Count the number of pairs of vertices $ v,u $ $ (v&lt;u) $ , such that vertices $ v $ and $ u $ are close.

## 输入格式

The first line contains three integers $ n $ , $ l $ and $ w $ $ (1<=n<=10^{5},1<=l<=n,0<=w<=10^{9}) $ . The next $ n-1 $ lines contain the descriptions of the tree edges. The $ i $ -th line contains two integers $ p_{i},w_{i} $ $ (1<=p_{i}&lt;(i+1),0<=w_{i}<=10^{4}) $ , that mean that the $ i $ -th edge connects vertex $ (i+1) $ and $ p_{i} $ and has weight $ w_{i} $ .

Consider the tree vertices indexed from 1 to $ n $ in some way.

## 输出格式

Print a single integer — the number of close pairs.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
4 4 6
1 3
1 4
1 3

```

### 输出

```
4

```

## 样例 #2

### 输入

```
6 2 17
1 3
2 5
2 13
1 6
5 9

```

### 输出

```
9

```



---

---
title: "Painting The Wall"
layout: "post"
diff: 省选/NOI-
pid: CF398B
tag: ['数学', '概率论', '期望']
---

# Painting The Wall

## 题目描述

User ainta decided to paint a wall. The wall consists of $ n^{2} $ tiles, that are arranged in an $ n×n $ table. Some tiles are painted, and the others are not. As he wants to paint it beautifully, he will follow the rules below.

1. Firstly user ainta looks at the wall. If there is at least one painted cell on each row and at least one painted cell on each column, he stops coloring. Otherwise, he goes to step 2.
2. User ainta choose any tile on the wall with uniform probability.
3. If the tile he has chosen is not painted, he paints the tile. Otherwise, he ignores it.
4. Then he takes a rest for one minute even if he doesn't paint the tile. And then ainta goes to step 1.

However ainta is worried if it would take too much time to finish this work. So he wants to calculate the expected time needed to paint the wall by the method above. Help him find the expected time. You can assume that choosing and painting any tile consumes no time at all.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=2·10^{3} $ ; $ 0<=m<=min(n^{2},2·10^{4}) $ ) — the size of the wall and the number of painted cells.

Next $ m $ lines goes, each contains two integers $ r_{i} $ and $ c_{i} $ ( $ 1<=r_{i},c_{i}<=n $ ) — the position of the painted cell. It is guaranteed that the positions are all distinct. Consider the rows of the table are numbered from $ 1 $ to $ n $ . Consider the columns of the table are numbered from $ 1 $ to $ n $ .

## 输出格式

In a single line print the expected time to paint the wall in minutes. Your answer will be considered correct if it has at most $ 10^{-4} $ absolute or relative error.

## 样例 #1

### 输入

```
5 2
2 3
4 1

```

### 输出

```
11.7669491886

```

## 样例 #2

### 输入

```
2 2
1 1
1 2

```

### 输出

```
2.0000000000

```

## 样例 #3

### 输入

```
1 1
1 1

```

### 输出

```
0.0000000000

```



---

---
title: "Digit Tree"
layout: "post"
diff: 省选/NOI-
pid: CF715C
tag: ['最近公共祖先 LCA', '概率论', '逆元']
---

# Digit Tree

## 题目描述

ZS the Coder has a large tree. It can be represented as an undirected connected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ n-1 $ edges between them. There is a single nonzero digit written on each edge.

One day, ZS the Coder was bored and decided to investigate some properties of the tree. He chose a positive integer $ M $ , which is coprime to $ 10 $ , i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/9b5bdec4cb6231baa1f3fcb57eb25703ae0eed8f.png).

ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting when if he would follow the shortest path from vertex $ u $ to vertex $ v $ and write down all the digits he encounters on his path in the same order, he will get a decimal representaion of an integer divisible by $ M $ .

Formally, ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting if the following states true:

- Let $ a_{1}=u,a_{2},...,a_{k}=v $ be the sequence of vertices on the shortest path from $ u $ to $ v $ in the order of encountering them;
- Let $ d_{i} $ ( $ 1<=i&lt;k $ ) be the digit written on the edge between vertices $ a_{i} $ and $ a_{i+1} $ ;
- The integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/72be647436ef167ccaba4334e08ad71c22afc6b4.png) is divisible by $ M $ .

Help ZS the Coder find the number of interesting pairs!

## 输入格式

The first line of the input contains two integers, $ n $ and $ M $ ( $ 2<=n<=100000 $ , $ 1<=M<=10^{9} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/d9389e45dbbc083daab078bda82851582dd53c47.png)) — the number of vertices and the number ZS has chosen respectively.

The next $ n-1 $ lines contain three integers each. $ i $ -th of them contains $ u_{i},v_{i} $ and $ w_{i} $ , denoting an edge between vertices $ u_{i} $ and $ v_{i} $ with digit $ w_{i} $ written on it ( $ 0<=u_{i},v_{i}&lt;n,1<=w_{i}<=9 $ ).

## 输出格式

Print a single integer — the number of interesting (by ZS the Coder's consideration) pairs.

## 说明/提示

In the first sample case, the interesting pairs are $ (0,4),(1,2),(1,5),(3,2),(2,5),(5,2),(3,5) $ . The numbers that are formed by these pairs are $ 14,21,217,91,7,7,917 $ respectively, which are all multiples of $ 7 $ . Note that $ (2,5) $ and $ (5,2) $ are considered different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/08c05395fdf8f9a998abf43b020555e6b5471bd5.png)In the second sample case, the interesting pairs are $ (4,0),(0,4),(3,2),(2,3),(0,1),(1,0),(4,1),(1,4) $ , and $ 6 $ of these pairs give the number $ 33 $ while $ 2 $ of them give the number $ 3333 $ , which are all multiples of $ 11 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/8a71025758e81b9cf19889885872aec3ca3f5ffc.png)

## 样例 #1

### 输入

```
6 7
0 1 2
4 2 4
2 0 1
3 0 9
2 5 7

```

### 输出

```
7

```

## 样例 #2

### 输入

```
5 11
1 2 3
2 0 3
3 0 3
4 3 3

```

### 输出

```
8

```



---

---
title: "Xor-matic Number of the Graph"
layout: "post"
diff: 省选/NOI-
pid: CF724G
tag: ['进制', '概率论', '线性基']
---

# Xor-matic Number of the Graph

## 题目描述

给你一个无向图，有n个顶点和m条边，每条边上都有一个非负权值。

我们称一个三元组  $(u,v,s)$ 是有趣的，当且仅当对于 $1 \le u < v \le n$ 且有一条从 $u$ 到 $v$ 的路径(可以经过相同的点和边多次)，其路径上的权值异或和为  $s$。对于一条路径，如果一条边经过了多次，则计算异或和时也应计算多次。不难证明，这样的三元组是有限的。

计算所有有趣的三元组中 $s$ 的和对于 $10^9+7$ 的模数

## 输入格式

第一行包括两个整数  $n,m,(n\in [1,10^5],m\in[0,2*10^5]$  ——图中点数与边数

接下来的  $m$  行每行包括3个整数  $u_i,v_i,t_i(u_i,v_i\in [1,n],t_i\in [0,10^{18}],u_i\not = v_i)$  ——边的两端点序号与边的权值

图中无自环与重边

## 输出格式

输出一个整数，即题目中的答案对于  $10^9+7$  的mod值

感谢@Dimitry_L 提供的翻译

## 样例 #1

### 输入

```
4 4
1 2 1
1 3 2
2 3 3
3 4 1

```

### 输出

```
12

```

## 样例 #2

### 输入

```
4 4
1 2 1
2 3 2
3 4 4
4 1 8

```

### 输出

```
90

```

## 样例 #3

### 输入

```
8 6
1 2 2
2 3 1
2 4 4
4 5 5
4 6 3
7 8 5

```

### 输出

```
62

```



---

---
title: "Karen and Cards"
layout: "post"
diff: 省选/NOI-
pid: CF815D
tag: ['枚举', '前缀和', '概率论']
---

# Karen and Cards

## 题目描述

Karen just got home from the supermarket, and is getting ready to go to sleep.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815D/d6b07c74db93ed793c45ff910937379fe578d8dc.png)After taking a shower and changing into her pajamas, she looked at her shelf and saw an album. Curious, she opened it and saw a trading card collection.

She recalled that she used to play with those cards as a child, and, although she is now grown-up, she still wonders a few things about it.

Each card has three characteristics: strength, defense and speed. The values of all characteristics of all cards are positive integers. The maximum possible strength any card can have is $ p $ , the maximum possible defense is $ q $ and the maximum possible speed is $ r $ .

There are $ n $ cards in her collection. The $ i $ -th card has a strength $ a_{i} $ , defense $ b_{i} $ and speed $ c_{i} $ , respectively.

A card beats another card if at least two of its characteristics are strictly greater than the corresponding characteristics of the other card.

She now wonders how many different cards can beat all the cards in her collection. Two cards are considered different if at least one of their characteristics have different values.

## 输入格式

The first line of input contains four integers, $ n $ , $ p $ , $ q $ and $ r $ ( $ 1<=n,p,q,r<=500000 $ ), the number of cards in the collection, the maximum possible strength, the maximum possible defense, and the maximum possible speed, respectively.

The next $ n $ lines each contain three integers. In particular, the $ i $ -th line contains $ a_{i} $ , $ b_{i} $ and $ c_{i} $ ( $ 1<=a_{i}<=p $ , $ 1<=b_{i}<=q $ , $ 1<=c_{i}<=r $ ), the strength, defense and speed of the $ i $ -th collection card, respectively.

## 输出格式

Output a single integer on a line by itself, the number of different cards that can beat all the cards in her collection.

## 说明/提示

In the first test case, the maximum possible strength is $ 4 $ , the maximum possible defense is $ 4 $ and the maximum possible speed is $ 5 $ . Karen has three cards:

- The first card has strength $ 2 $ , defense $ 2 $ and speed $ 5 $ .
- The second card has strength $ 1 $ , defense $ 3 $ and speed $ 4 $ .
- The third card has strength $ 4 $ , defense $ 1 $ and speed $ 1 $ .

There are $ 10 $ cards that beat all the cards here:

1. The card with strength $ 3 $ , defense $ 3 $ and speed $ 5 $ .
2. The card with strength $ 3 $ , defense $ 4 $ and speed $ 2 $ .
3. The card with strength $ 3 $ , defense $ 4 $ and speed $ 3 $ .
4. The card with strength $ 3 $ , defense $ 4 $ and speed $ 4 $ .
5. The card with strength $ 3 $ , defense $ 4 $ and speed $ 5 $ .
6. The card with strength $ 4 $ , defense $ 3 $ and speed $ 5 $ .
7. The card with strength $ 4 $ , defense $ 4 $ and speed $ 2 $ .
8. The card with strength $ 4 $ , defense $ 4 $ and speed $ 3 $ .
9. The card with strength $ 4 $ , defense $ 4 $ and speed $ 4 $ .
10. The card with strength $ 4 $ , defense $ 4 $ and speed $ 5 $ .

In the second test case, the maximum possible strength is $ 10 $ , the maximum possible defense is $ 10 $ and the maximum possible speed is $ 10 $ . Karen has five cards, all with strength $ 1 $ , defense $ 1 $ and speed $ 1 $ .

Any of the $ 972 $ cards which have at least two characteristics greater than $ 1 $ can beat all of the cards in her collection.

## 样例 #1

### 输入

```
3 4 4 5
2 2 5
1 3 4
4 1 1

```

### 输出

```
10

```

## 样例 #2

### 输入

```
5 10 10 10
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1

```

### 输出

```
972

```



---

---
title: "Desk Disorder"
layout: "post"
diff: 省选/NOI-
pid: CF859E
tag: ['二分图', '概率论']
---

# Desk Disorder

## 题目描述

A new set of desks just arrived, and it's about time! Things were getting quite cramped in the office. You've been put in charge of creating a new seating chart for the engineers. The desks are numbered, and you sent out a survey to the engineering team asking each engineer the number of the desk they currently sit at, and the number of the desk they would like to sit at (which may be the same as their current desk). Each engineer must either remain where they sit, or move to the desired seat they indicated in the survey. No two engineers currently sit at the same desk, nor may any two engineers sit at the same desk in the new seating arrangement.

How many seating arrangements can you create that meet the specified requirements? The answer may be very large, so compute it modulo $ 1000000007=10^{9}+7 $ .

## 输入格式

Input will begin with a line containing $ N $ ( $ 1<=N<=100000 $ ), the number of engineers.

 $ N $ lines follow, each containing exactly two integers. The $ i $ -th line contains the number of the current desk of the $ i $ -th engineer and the number of the desk the $ i $ -th engineer wants to move to. Desks are numbered from $ 1 $ to $ 2·N $ . It is guaranteed that no two engineers sit at the same desk.

## 输出格式

Print the number of possible assignments, modulo $ 1000000007=10^{9}+7 $ .

## 说明/提示

These are the possible assignments for the first example:

- 1 5 3 7
- 1 2 3 7
- 5 2 3 7
- 1 5 7 3
- 1 2 7 3
- 5 2 7 3

## 样例 #1

### 输入

```
4
1 5
5 2
3 7
7 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5
1 10
2 10
3 10
4 10
5 5

```

### 输出

```
5

```



---

