---
title: "[ICPC 2024 Xi'an I] Triangle"
layout: "post"
diff: 普及/提高-
pid: P10562
tag: ['2024', 'O2优化', 'ICPC']
---
# [ICPC 2024 Xi'an I] Triangle
## 题目描述

There are three points $A(a, 0)$, $B(0, b)$, $C(0, 0)$ in the plane rectangular coordinate system. Define the size of triangle $ABC$ as the number of squares that belong to it.
    
    
    
For integers $x,y$, one square is defined by four points $(x, y)$, $(x + 1, y)$, $(x, y + 1)$, $(x + 1, y + 1)$. We consider a square to belong to a triangle if half or more of it is inside the triangle.
    
    
    
For example, when $a = 8, b = 6$, the size of triangle $ABC$ will be $24$. The image below shows which squares are counted in the triangle.

![](https://cdn.luogu.com.cn/upload/image_hosting/3fnqi74y.png)
## 输入格式


    
The first and only line contains two integers $a\ (1\le a\le 10^6)$ and $b\ (1\le b\le 10^6)$.
## 输出格式


Print an integer: the size of triangle $ABC$.
    
## 样例

### 样例输入 #1
```
6 8
```
### 样例输出 #1
```
24
```
### 样例输入 #2
```
5 5

```
### 样例输出 #2
```
15
```
### 样例输入 #3
```
1 999999
```
### 样例输出 #3
```
500000
```


---

---
title: "[SEERC 2020] Divisible by 3"
layout: "post"
diff: 普及/提高-
pid: P10740
tag: ['2020', 'ICPC']
---
# [SEERC 2020] Divisible by 3
## 题目描述

定义一个序列 $b$ 的权重为 $\sum_{i=1}^n \sum_{j=1}^{i-1} b_i \times b_j$。

现在你有一个长度为 $n$ 的数组 $a$，求一共存在多少种 $(l,r)$ 使得 $1 \leq l \leq r \leq n$ 且 $[a_l, a_{l+1},\ldots,a_r]$ 的权重能被 $3$ 整除。
## 输入格式

第一行一个整数 $n\ (1 \leq n \leq 5 \times 10^5)$。

然后 $n$ 个整数 $a_i\ (0 \leq a_i \leq 10^9)$。
## 输出格式

输出方案总数。
## 样例

### 样例输入 #1
```
3
5 23 2021

```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
5
0 0 1 3 3
```
### 样例输出 #2
```
15
```
### 样例输入 #3
```
10
0 1 2 3 4 5 6 7 8 9
```
### 样例输出 #3
```
20
```
## 提示

对于第一个样例，存在 $[1,1]$、$[2,2]$、$[3,3]$、$[1,3]$ 共 $4$ 种方案。


---

---
title: "[SEERC 2020] Mistake"
layout: "post"
diff: 普及/提高-
pid: P10748
tag: ['2020', 'Special Judge', 'ICPC']
---
# [SEERC 2020] Mistake
## 题目描述

你有 $k$ 个机器，每个机器都**未按序**存储了 $1 \sim n$ 共 $n$ 个数，当你启动某个机器时，该机器会将其存储的数最前面的数打印出来，然后删除它。

但是很幸运，你知道 $m$ 对 $(a_i,b_i)$，表示每个存储的 $a_i$ 都在 $b_i$ 前面。

你还知道你依次启动的机器输出了哪些，请对于每个打印的数，确定一种方案表示它是由哪个机器启动得来，保证每个数出现的次数 $=n$。

存在多种可行解，输出任何都可以得分。
## 输入格式

第一行三个整数 $n,k,m\ (1 \leq n,k\leq 5 \times 10^5, 0 \leq m \leq 2.5 \times 10^5, 1 \leq n \times k \leq 5 \times 10^5)$。

然后 $m$ 行每行两个 $a_i,b_i\ (1 \leq a_i,b_i \leq n)$，保证不存在环。

然后一行 $n \times k$ 的数，表示依次启动的机器输出的序列。
## 输出格式

输出一种合法的启动方案。
## 样例

### 样例输入 #1
```
3 3 2
1 2
1 3
1 1 2 3 3 2 1 2 3
```
### 样例输出 #1
```
1 2 2 1 2 1 3 3 3
```


---

---
title: "[EC Final 2020] Rooks"
layout: "post"
diff: 普及/提高-
pid: P10821
tag: ['模拟', '2020', 'O2优化', '排序', 'ICPC']
---
# [EC Final 2020] Rooks
## 题目描述

Prof. Pang plays chess against his rival Prof. Shou. They are the only two players in the game. The chessboard is very large and can be viewed as a 2D plane. Prof. Pang placed $n_1$ rooks and Prof. Shou placed $n_2$ rooks. Each rook is a point with integer coordinates on the chessboard. One rook is $\textit{attacked}$ by another rook if they satisfy all of the following conditions:

- They are placed by different players.
- They have the same $x$-coordinate or $y$-coordinate.
- There is no other rook on the line segment between them.

Help Prof. Pang and Prof. Shou to decide which rooks are attacked.
## 输入格式

The first line contains two integers $n_1, n_2$ ($1\le n_1, n_2\le 200000$) separated by a single space denoting the number of rooks placed by Prof. Pang and the number of rooks placed by Prof. Shou.

The $i$-th ($1\le i\le n_1$) line of the next $n_1$ lines contains two integers $x, y$ ($-10^9\le x, y\le 10^9$) separated by a single space denoting the location $(x, y)$ of the $i$-th rook placed by Prof. Pang.

The $i$-th ($1\le i\le n_2$) line of the next $n_2$ lines contains two integers $x, y$ ($-10^9\le x, y\le 10^9$) separated by a single space denoting the location $(x, y)$ of the $i$-th rook placed by Prof. Shou.

It is guaranteed that the $n_1+n_2$ rooks placed by the players are distinct (i.e., no two rooks can have the same location).
## 输出格式

Output a string with length $n_1$ on the first line. The $i$-th ($1\le i\le n_1$) character should be $1$ if the $i$-th rook placed by Prof. Pang is attacked and $0$ otherwise.

Output a string with length $n_2$ on the second line. The $i$-th ($1\le i\le n_2$) character should be $1$ if the $i$-th rook placed by Prof. Shou is attacked and $0$ otherwise.

## 样例

### 样例输入 #1
```
3 2
0 0
0 1
1 0
0 -1
-1 0
```
### 样例输出 #1
```
100
11
```


---

---
title: "[NERC2024] Adrenaline Rush"
layout: "post"
diff: 普及/提高-
pid: P12092
tag: ['2024', 'Special Judge', 'ICPC', '北欧亚大陆']
---
# [NERC2024] Adrenaline Rush
## 题目描述

Alice's friend is a big fan of the Adrenaline Rush racing competition and always strives to attend every race. However, this time, Alice is the one watching the race. To ensure her friend does not miss any important details, Alice decides to take notes on everything that happens on the track.

The first thing Alice notices before the race begins is the numbering of the cars. All the cars line up in front of the starting line in a specific order. The car closest to the line is numbered $1$, the second car is numbered $2$, and so on, up to the last car, which is numbered $n$. How convenient! --- Alice thought.

The race begins with the countdown: ``Three! Two! One! Go!``. Alice observes that the cars start in their original order. However, as the race progresses, their order changes. She records whenever one car overtakes another, essentially swapping places with it on the track.

During the race, Alice notices something curious: no car overtakes another more than once. In other words, for any two cars $x$ and $y$, there are at most two overtakes between them during the race: $x$ overtakes $y$ and/or $y$ overtakes $x$.

At the end of the race, Alice carefully writes down the final order of the cars $c_1, c_2, \ldots, c_n$, where $c_1$ represents the winner of the race.

Alice's friend, however, is only interested in the final ranking and discards all of Alice's notes except for the final ordering. As Alice is quite curious, she wonders: $\textit{What is the longest possible sequence of overtakes she could have observed during the race?}$ Your task is to help Alice answer this question.
## 输入格式

The first line of the input contains a single integer $n\;(1 \le n \le 1000)$ --- the number of cars in the race.

The second line contains a permutation $c_1, c_2, \ldots, c_n\;(1 \le c_i \le n, c_i \ne c_j)$ --- the final order of the cars.
## 输出格式

The first line of the output should contain a single integer $m$ --- the maximum possible number of overtakes that can occur during the race.

Each of the next $m$ lines should contain two integers $x$ and $y$ ($1 \le x, y \le n$, $x \ne y$) representing an overtake event, where car $x$ overtakes car $y$. This means that car $x$ was directly behind car $y$ and overtakes it. The overtakes must be listed in the order they occurred during the race.

After all $m$ overtakes have occurred, the cars must arrive at the finish line in the order $c_1, c_2, \ldots, c_n$. Note that any car $x$ should not overtake another car $y$ more than once.

If there are multiple possible longest sequences of overtakes, output any of them.
## 样例

### 样例输入 #1
```
3
2 3 1
```
### 样例输出 #1
```
4
2 1
3 1
3 2
2 3
```
### 样例输入 #2
```
1
1
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
2
1 2
```
### 样例输出 #3
```
2
2 1
1 2
```


---

---
title: "[ICPC 2022/2023 WF] Riddle of the Sphinx"
layout: "post"
diff: 普及/提高-
pid: P12295
tag: ['2022', '2023', '交互题', 'Special Judge', 'ICPC']
---
# [ICPC 2022/2023 WF] Riddle of the Sphinx


---

---
title: "[NERC 2022] Easy Assembly"
layout: "post"
diff: 普及/提高-
pid: P12794
tag: ['2022', 'ICPC', 'NERC/NEERC']
---
# [NERC 2022] Easy Assembly
## 题目描述

Emma loves playing with blocks. She has several cubic blocks of the same size that are numbered with $\textbf{distinct}$ integers written on them. She assembles towers from those blocks by stacking them vertically. 

A configuration of her game is a set of towers that she has assembled from the blocks. Emma can perform two kinds of operations on a configuration of towers:

- $\textbf{Split}$ any tower with more than one block in it by taking any number of blocks from the top of the tower and moving them to a new tower keeping their order, so that the top block of the old tower becomes the top block of the new tower. As a result of this operation, the number of towers increases by one.

- $\textbf{Combine}$ any two towers by moving blocks from one tower on top of the other tower in the same order. As a result of this operation, the number of towers decreases by one.

Emma wants to stack all the blocks into a single tower so that all blocks come in order sorted by the numbers --- from the block with the minimal number at the top to the block with the maximal number at the bottom. Emma wants to do as little of splitting and combining operations as possible. Your task is to find the minimal number of operations she has to make and output how many splits and combines are needed.
 
## 输入格式

The first line of the input file contains an integer $n$ ($1 \le n \le 10\,000$) --- the number of towers in the initial configuration. Next $n$ lines describe towers. Each tower $i$ is described by a line that starts with the number $k_i$ ($k_i \ge 1$; $\sum_1^n{k_i} \le 10\,000$) --- the number of blocks in the tower, followed by $k_i$ numbers $b_{i,j}$ ($1 \le b_{i,j} \le 10^9$) --- numbers written on the blocks in the $i$-th tower, listed from top to bottom. All block numbers listed in the input are different. 
## 输出格式

Output a line with two integers $s$ and $c$ --- the number of split and combine operations Emma should make to get a single tower with blocks sorted by their numbers, so that the total number of operations is minimized.
## 样例

### 样例输入 #1
```
2
3 3 5 8
2 9 2
```
### 样例输出 #1
```
1 2
```
## 提示

The example needs the following operations (1 split and 2 combines).

![](https://cdn.luogu.com.cn/upload/image_hosting/vcr3xth0.png)


---

---
title: "[NERC 2021] Connect the Points"
layout: "post"
diff: 普及/提高-
pid: P12816
tag: ['2021', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2021] Connect the Points
## 题目描述

You are given three points on a plane. You should choose some segments on the plane that are parallel to coordinate axes, so that all three points become connected. The total length of the chosen segments should be the minimal possible.

Two points $a$ and $b$ are considered connected if there is a sequence of points $p_0 = a, p_1, \ldots, p_k = b$ such that points $p_i$ and $p_{i+1}$ lie on the same segment.
## 输入格式

The input consists of three lines describing three points. Each line contains two integers $x$ and $y$ separated by a space --- the coordinates of the point ($-10^9 \le x, y \le 10^9$). The points are pairwise distinct.

## 输出格式

On the first line output $n$ --- the number of segments, at most 100.

The next $n$ lines should contain descriptions of segments. Output four integers $x_1$, $y_1$, $x_2$, $y_2$ on a line --- the coordinates of the endpoints of the corresponding segment ($-10^9 \le x_1, y_1, x_2, y_2 \le 10^9$). Each segment should be either horizontal or vertical.

It is guaranteed that the solution with the given constraints exists.
## 样例

### 样例输入 #1
```
1 1
3 5
8 6
```
### 样例输出 #1
```
3
1 1 1 5
1 5 8 5
8 5 8 6
```
## 提示

The points and the segments from the example are shown below.

![](https://cdn.luogu.com.cn/upload/image_hosting/3ln8aeda.png)


---

---
title: "[NERC 2021] Labyrinth"
layout: "post"
diff: 普及/提高-
pid: P12825
tag: ['2021', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2021] Labyrinth
## 题目描述

Leslie and Leon entered a labyrinth. The labyrinth consists of $n$ halls and $m$ one-way passages between them. The halls are numbered from $1$ to $n$.

Leslie and Leon start their journey in the hall $s$. Right away, they quarrel and decide to explore the~labyrinth separately. However, they want to meet again at the end of their journey.

To help Leslie and Leon, your task is to find two different paths from the given hall $s$ to some other hall $t$, such that these two paths do not share halls other than the staring hall $s$ and the ending hall $t$. The hall $t$ has not been determined yet, so you can choose any of the labyrinth's halls as $t$ except $s$.

Leslie's and Leon's paths do not have to be the shortest ones, but their paths must be simple, visiting any hall at most once. Also, they cannot visit any common halls except $s$ and $t$ during their journey, even at different times.
## 输入格式

The first line contains three integers $n$, $m$, and $s$, where $n$ ($2 \le n \le 2 \cdot 10^5$) is the number of vertices, $m$ ($0 \le m \le 2 \cdot 10^5$) is the number of edges in the labyrinth, and $s$ ($1 \le s \le n$) is the starting hall.

Then $m$ lines with descriptions of passages follow. Each description contains two integers $u_i$, $v_i$ ($1 \le u_i, v_i \le n$; $u_i \neq v_i$), denoting a passage from the hall $u_i$ to the hall $v_i$. The passages are one-way. Each tuple $(u_i, v_i)$ is present in the input at most once. The labyrinth can contain cycles and is not necessarily connected in any way.
## 输出格式

If it is possible to find the desired two paths, output $\tt{Possible}$, otherwise output $\tt{Impossible}$.

If the answer exists, output two path descriptions. Each description occupies two lines. The first line of the description contains an integer $h$ ($2 \le h \le n$) --- the number of halls in a path, and the second line contains distinct integers $w_1, w_2, \dots, w_h$ ($w_1 = s$; $1 \le w_j \le n$; $w_h = t$) --- the halls in the path in the order of passing.
Both paths must end at the same vertex $t$. The paths must be different, and all intermediate halls in these paths must be distinct.
## 样例

### 样例输入 #1
```
5 5 1
1 2
2 3
1 4
4 3
3 5
```
### 样例输出 #1
```
Possible
3
1 2 3
3
1 4 3
```
### 样例输入 #2
```
5 5 1
1 2
2 3
3 4
2 5
5 4
```
### 样例输出 #2
```
Impossible
```
### 样例输入 #3
```
3 3 2
1 2
2 3
3 1
```
### 样例输出 #3
```
Impossible
```


---

---
title: "[NERC 2020 Online] Miser"
layout: "post"
diff: 普及/提高-
pid: P12862
tag: ['2020', '二分', '拓扑排序', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020 Online] Miser
## 题目描述

In some non-classical University, there is going to be an opening ceremony of the cafeteria in $n$ days. In front of the closed cafeteria, there is a sign with a number --- how many days are left before the opening.

For each day out of these $n$, the director of the cafeteria knows all the people who are coming to the University and are going to see the sign. The director has to choose a sign with a number each day, such that each person who is coming to the University sees that the number on the sign is decreasing. The director is a typical $\emph{miser}$ who spends as little money as possible and wants to order the minimum possible number of different signs. Your task is to help the director find this number.

Consider the first test case: person $1$ comes on days $1$, $2$ and $5$, and person $2$ comes on days $2$, $3$ and $4$. The director can order just four signs with numbers $1$, $2$, $3$ and $4$, to put a sign with $1$ on days $5$ and $4$, a sign with $2$ on day $3$, a sign with $3$ on day $2$, and a sign with $4$ on day $1$. Thus, person $1$ will see the signs $4$, $2$, and $1$ and person $2$ will see the signs $3$, $2$, and $1$.
## 输入格式

The first line of the input contains an integer $n$ --- the total number of days before the opening of the~cafeteria. The next $n$ lines contain the description of each day. The description starts with the positive integer $k$ --- the number of people that come to the University this day. This integer is followed by $k$ distinct integers --- the identifiers of the people that come.

The sum of all $k$ over all days does not exceed $10^5$. Identifiers of people are positive and do not exceed $10^5$.
## 输出格式

Output one integer --- the minimum possible number of different signs that have to be ordered.
## 样例

### 样例输入 #1
```
5
1 1
2 1 2
1 2
1 2
1 1
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
5
1 1
1 1
1 1
1 1
1 1
```
### 样例输出 #2
```
5
```


---

---
title: "[NERC 2020] King's Task"
layout: "post"
diff: 普及/提高-
pid: P12910
tag: ['2020', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020] King's Task
## 题目描述

The brave Knight came to the King and asked permission to marry the princess.
The King knew that the Knight was brave, but he also wanted to know if he was smart enough. So he asked him to solve the following task.

There is a permutation $p_i$ of numbers from $1$ to $2n$. You can make two types of operations.

- Swap $p_1$ and $p_2$, $p_3$ and $p_4$, ..., $p_{2n-1}$ and $p_{2n}$. 
- Swap $p_1$ and $p_{n+1}$, $p_2$ and $p_{n+2}$, ..., $p_{n}$ and $p_{2n}$.

The task is to find the minimal number of operations required to sort the given permutation.

The Knight was not that smart actually, but quite charming, so the princess asks you to help him to solve the King's task.
## 输入格式

The first line contains the integer $n$ ($1\le n\le 1000$). The second line contains $2n$ integers $p_i$ --- the permutation of numbers from 1 to $2n$.
## 输出格式

Print one integer --- the minimal number of operations required to sort the permutation. If it is impossible to sort the permutation using these operations, print $-1$.
## 样例

### 样例输入 #1
```
3
6 3 2 5 4 1
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
2
3 4 2 1
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
4
1 2 3 4 5 6 7 8
```
### 样例输出 #3
```
0
```
## 提示

In the first example, you can sort the permutation in three operations:
- Make operation 1: $3, 6, 5, 2, 1, 4$.
- Make operation 2: $2, 1, 4, 3, 6, 5$.
- Make operation 1: $1, 2, 3, 4, 5, 6$.


---

---
title: "[NERC 2019] Balls of Buma"
layout: "post"
diff: 普及/提高-
pid: P12935
tag: ['2019', 'ICPC', 'NERC/NEERC']
---
# [NERC 2019] Balls of Buma
## 题目描述

Balph is learning to play a game called Buma. In this game, he is given a row of colored balls. He has to choose the color of one new ball and the place to insert it (between two balls, or to the left of all the balls, or to the right of all the balls).

When the ball is inserted the following happens repeatedly: if some segment of balls of the same color became longer as a result of a previous action and its length became at least $3$, then all the balls of this segment are eliminated. 

Consider, for example, a row of balls $\tt{AAABBBWWBB}$. Suppose Balph chooses a ball of color $\tt{W}$ and the place to insert it after the sixth ball, i.e. to the left of the two $\tt{W}$ s. After Balph inserts this ball, the balls of color $\tt{W}$ are eliminated, since this segment was made longer and has length $3$ now, so the row becomes $\texttt{AAABBBBB}$. The balls of color $\tt{B}$ are eliminated now, because the segment of balls of color $\tt{B}$ became longer and has length $5$ now. Thus, the row becomes $\texttt{AAA}$. However, none of the balls are eliminated now, because there is no elongated segment.

Help Balph count the number of possible ways to choose a color of a new ball and a place to insert it that leads to the elimination of all the balls.
## 输入格式

The only line contains a non-empty string of uppercase English letters of length at most $3 \cdot 10^5$. Each letter represents a ball with the corresponding color.
## 输出格式

Output the number of ways to choose a color and a position of a new ball in order to eliminate all the balls.
## 样例

### 样例输入 #1
```
BBWWBB
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
BWWB
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
BBWBB
```
### 样例输出 #3
```
0
```
### 样例输入 #4
```
OOOWWW
```
### 样例输出 #4
```
0
```
### 样例输入 #5
```
WWWOOOOOOWWW
```
### 样例输出 #5
```
7
```


---

---
title: "[NWRRC 2023] Divisibility Trick"
layout: "post"
diff: 普及/提高-
pid: P13584
tag: ['2023', 'Special Judge', '鸽笼原理', 'ICPC', 'NWRRC']
---
# [NWRRC 2023] Divisibility Trick
## 题目描述

Dmitry has recently learned a simple rule to check if an integer is divisible by 3. An integer is divisible by 3 if the sum of its digits is divisible by 3.

Later he also learned that the same rule can be used to check if an integer is divisible by 9. An integer is divisible by 9 if the sum of its digits is divisible by 9.

Dmitry's elder sister Daria wants to trick him by showing that the same rule can be applied to any divisor~$d$. To do this, she wants to show Dmitry an example of a positive integer $n$ such that $n$ is divisible by $d$, and the sum of the digits of $n$ is also divisible by $d$. Help her to find such a number.
## 输入格式

The only line contains a single integer $d$ ($1\le d\le 1000$).
## 输出格式

Print a positive integer $n$ divisible by $d$ such that the sum of its digits is also divisible by $d$.

The value of $n$ must consist of at most $10^6$ digits and must not have leading zeroes. It can be shown that such an integer always exists. If there are multiple answers, print any of them.
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
13
```
### 样例输出 #2
```
1898
```
### 样例输入 #3
```
1
```
### 样例输出 #3
```
239
```
## 提示

In the first example, $3$ is divisible by $3$, and its sum of digits, $3$, is also divisible by $3$.

In the second example, $1898$ is divisible by $13$, and its sum of digits, $1 + 8 + 9 + 8 = 26$, is also divisible by $13$.

In the third example, any positive integer satisfies the conditions.


---

---
title: "[NWRRC 2023] Every Queen"
layout: "post"
diff: 普及/提高-
pid: P13585
tag: ['2023', 'Special Judge', 'ICPC', '分类讨论', 'NWRRC']
---
# [NWRRC 2023] Every Queen
## 题目描述

There are $n$ chess queens on an infinite grid. They are placed in squares with coordinates $(x_1, y_1), (x_2, y_2), \ldots, (x_n, y_n)$. Your task is to find a square that all queens attack, or report that no such square exists.

A queen in square $(x_i, y_i)$ attacks square $(x, y)$ if at least one of the following conditions is satisfied:

- $x_i = x$;
- $y_i = y$;
- $|x_i - x| = |y_i - y|$.

Note that in this problem, the queens do not block each other. For example, if there are queens in squares $(1, 1)$ and $(2, 2)$, both of them attack square $(3, 3)$. Moreover, you can choose a square that already contains a queen. For example, square $(1, 1)$ would be a valid answer in this case.
## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^5$). The description of the test cases follows.

The first line of each test case contains a single integer $n$, denoting the number of queens ($1 \le n \le 10^5$).

The $i$-th of the following $n$ lines contains two integers $x_i$ and $y_i$, denoting the coordinates of the square containing the $i$-th queen ($-10^8 \le x_i, y_i \le 10^8$). No two queens share the same square.

It is guaranteed that the sum of $n$ over all test cases does not exceed $10^5$.
## 输出格式

For each test case, if an answer exists, print $\tt{YES}$ in the first line. Then, in the second line, print two integers $x$ and $y$, denoting the coordinates of a square attacked by every queen ($-10^9 \le x, y \le 10^9$). 

If no such square exists, print a single line containing $\tt{NO}$ instead.

It can be shown that if an answer exists, there also exists an answer that satisfies $-10^9 \le x, y \le 10^9$. If there are multiple answers, print any of them.
## 样例

### 样例输入 #1
```
3
2
1 1
2 2
4
0 1
1 0
3 1
4 0
5
0 1
1 0
1 2
2 2
4 2
```
### 样例输出 #1
```
YES
1 1
NO
YES
-1 2
```


---

---
title: "[NWRRC 2023] Jumping Frogs"
layout: "post"
diff: 普及/提高-
pid: P13590
tag: ['贪心', '2023', '排序', 'ICPC', 'NWRRC']
---
# [NWRRC 2023] Jumping Frogs
## 题目描述

Julia is a fan of wild nature photos. Yesterday, she took two photos of a beautiful river with water lilies and some frogs sitting on them. 

There are many water lilies on the river, numbered with consecutive positive integers from left to right, starting from $1$. Both photos were taken from exactly the same spot, and both photos have the same $n$ frogs sitting on water lilies. Each water lily can hold at most one frog.

After comparing the photos, Julia found out that all the frogs moved between the photos, since no water lily had a frog sitting on it in both photos. However, Julia couldn't understand which frog from the first photo moved to which water lily in the second photo, as all frogs looked exactly the same!

One thing is for sure: each frog jumped to a different water lily. Some frogs moved $\textit{to the left}$, to a water lily with a smaller number, while the other frogs moved $\textit{to the right}$, to a water lily with a larger number.

To investigate the movement of frogs, Julia wants to answer the following question: how many frogs moved to the left between the photos? As it may not be possible to find a unique answer to this question, you need to help Julia to find all possible answers.
## 输入格式

The first line contains a single integer $n$, denoting the number of frogs ($1 \le n \le 200\,000$).

The second line contains $n$ integers $a_1, a_2, \ldots, a_n$, denoting the water lilies with frogs on them in the first photo, in increasing order ($1 \le a_1 < a_2 < \cdots < a_n \le 10^9$).

The third line contains $n$ integers $b_1, b_2, \ldots, b_n$, denoting the water lilies with frogs on them in the second photo, in increasing order ($1 \le b_1 < b_2 < \cdots < b_n \le 10^9$).

All $2n$ given integers are distinct: no water lily has a frog sitting on it in both photos.
## 输出格式

In the first line, print a single integer $k$, denoting the number of possible answers to Julia's question.

In the second line, print $k$ integers $c_1, c_2, \ldots, c_k$, denoting all possible answers in increasing order ($0 \le c_1 < c_2 < \cdots < c_k \le n$).
## 样例

### 样例输入 #1
```
4
10 20 30 40
1 2 51 52
```
### 样例输出 #1
```
1
2
```
### 样例输入 #2
```
4
10 20 30 40
5 15 25 35

```
### 样例输出 #2
```
4
1 2 3 4
```
### 样例输入 #3
```
1
100
200
```
### 样例输出 #3
```
1
0
```
## 提示

In the first example, frogs that ended up on water lilies $1$ and $2$ must have moved to the left, while frogs that ended up on water lilies $51$ and $52$ must have moved to the right. Thus, we know for sure that exactly $2$ frogs moved to the left between the photos.


---

---
title: "[NWRRC 2023] Kitchen Timer"
layout: "post"
diff: 普及/提高-
pid: P13591
tag: ['2023', '枚举', '位运算', 'ICPC', 'NWRRC']
---
# [NWRRC 2023] Kitchen Timer
## 题目描述

Kenny has a microwave in his kitchen. The microwave has a pretty weird one-button timer interface. 

When you have put some food into the microwave and want it to start heating, you should press the button one or multiple times. When you press the button for the first time, the timer is set for $1$ minute. If you immediately press the button again, $2$ minutes are added to the timer, for a total of $3$ minutes. If you immediately press the button yet again, $4$ more minutes are added to the timer, and so on. If you press the button for the $k$-th time without a pause, it adds $2^k$ minutes to the timer.

It seems impossible to set the timer for some periods of time by using the button: for example, how to set the timer for $2$ minutes? Fortunately, you can reset the button counter by making a pause for one second. So, for example, if you press the button, make a pause for one second, and then press the button again, the timer is set for $2$ minutes. Another example: if you press, press, pause, press, press, press, the total time on the timer is $1+2+1+2+4=10$ minutes.

Kenny needs to heat his food for exactly $x$ minutes. Help him to find the minimum number of one-second pauses he needs to set the timer. Let us assume that only pauses take time, while time to press the button is ignored.
## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.

The only line of each test case contains a single integer $x$, denoting the number of minutes Kenny needs to heat the food for ($1 \le x \le 10^{18}$).
## 输出格式

For each test case, print a single integer, denoting the minimum number of one-second pauses Kenny needs to make when setting the microwave timer for $x$ minutes.
## 样例

### 样例输入 #1
```
7
1
2
3
4
10
239
123456789012
```
### 样例输出 #1
```
0
1
0
1
1
4
19
```
## 提示

In the first example test case, no pauses are needed: Kenny can just press the button once.

In the second example test case, Kenny can press, pause, press to set the timer for $2$ minutes.

In the third example test case, Kenny can just press the button twice to set the timer for $3$ minutes.

In the fourth example test case, Kenny can press, press, pause, press to set the timer for $1 + 2 + 1 = 4$ minutes.


---

---
title: "[NWRRC 2023] Missing Vowels"
layout: "post"
diff: 普及/提高-
pid: P13593
tag: ['贪心', '2023', 'ICPC', 'NWRRC']
---
# [NWRRC 2023] Missing Vowels
## 题目描述

There are many ways to write a word on paper. For example, some writing systems, like Arabic and Hebrew, omit most vowels, although they write some of them.

In this problem, we will only consider strings consisting of English letters and hyphens. Letters $\tt{a}$, $\tt{e}$, $\tt{i}$, $\tt{o}$, $\tt{u}$, and $\tt{y}$ are considered to be vowels, while hyphens and all other letters are considered to be consonants. All comparisons are case-insensitive: uppercase and lowercase versions of the same letter are considered equal.

You are given two strings $s$ and $f$, called the $\textit{short}$ name and the $\textit{full}$ name, respectively. Your task is to check whether the short name $s$ can be obtained from the full name $f$ by omitting some vowels (possibly none).
## 输入格式

The first line contains a single string $s$, denoting the short name.

The second line contains a single string $f$, denoting the full name.

Each string is non-empty and consists of at most $1000$ English letters and hyphens.
## 输出格式

Print $\tt{Same}$ if the short name $s$ can be obtained from the long name $f$ by omitting some vowels, and $\tt{Different}$ otherwise.
## 样例

### 样例输入 #1
```
Shrm-el-Shikh
Sharm-el-Sheikh
```
### 样例输出 #1
```
Same
```
### 样例输入 #2
```
Eilot
Eilat
```
### 样例输出 #2
```
Different
```
### 样例输入 #3
```
Saint-Petersburg
Saint-Petersburg
```
### 样例输出 #3
```
Same
```
### 样例输入 #4
```
Bcdfghjklmnpqrstvwxz
Abcdefghijklmnopqrstuvwxzyy
```
### 样例输出 #4
```
Same
```
### 样例输入 #5
```
Aa
aaaA
```
### 样例输出 #5
```
Same
```
### 样例输入 #6
```
Etis-Atis-Amatis
Etis-Atis-Animatis
```
### 样例输出 #6
```
Different
```
### 样例输入 #7
```
will-the-wisp
will-o-the-wisp
```
### 样例输出 #7
```
Different
```
### 样例输入 #8
```
--a-very-short-name--
long-name
```
### 样例输出 #8
```
Different
```


---

---
title: "[GCPC 2023] Cosmic Commute"
layout: "post"
diff: 普及/提高-
pid: P13668
tag: ['2023', 'ICPC']
---
# [GCPC 2023] Cosmic Commute
## 题目描述

A long time ago, in a galaxy far, far away, the InterCosmic Passage Company (ICPC) operates a complex railway system using *light trains*.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/8bjjmufd.png)

A wormhole above Gallifrey, [mau\_king](https://pixabay.com/de/photos/milchstra\%c3\%9fe-wurmloch-5904640/)
:::

Each planet has exactly one train station and each light train connects two distinct planets of the galaxy, going back and forth between them. 
Just recently, the InterCosmic Passage Company established a teleportation system, which is now in its testing phase. 
Some train stations are now extended by a *wormhole*. 
All wormholes are connected to each other, and it is possible to teleport from one wormhole to another instantaneously. 
To not overload the new system, each citizen of the galaxy is only allowed to teleport at most once a day.   

Charlie lives on planet Gallifrey and works on planet Sontar. 
It is her first day of work, and she is already terribly late because her stupid alarm clock did not go off. 
On top of that, the new teleportation system is malfunctioning today of all days, and the destination wormhole cannot be chosen.
Instead, after entering a wormhole, one is teleported to a wormhole that is chosen uniformly at random among all other wormholes.
(It is impossible to be at the same train station after teleportation.)

Despite all her bad luck, Charlie is dead set on getting to work on time. 
Since all light trains are very slow, she wants to take as few light trains as possible. 
What is the expected minimum number of light trains she has to take to get to work if she can use the (malfunctioning) teleportation system at most once?  


## 输入格式

The input consists of:

- One line with integers $n, m, k$ ($2 \leq n \leq 2\cdot10^5,$ $n - 1 \leq m \leq 10^6, 2\leq k\leq n$), the number of planets in the galaxy, light trains and wormholes. Planet $1$ is Charlie's home planet Gallifrey, and planet $n$ is Sontar, where Charlie works.
- One line containing $k$ distinct integers, the planets whose train stations each have a wormhole (in addition to the light trains).
- $m$ lines, each containing two integers $a$ and $b$ ($1 \leq a,b \leq n$ and $a \neq b$), describing a light train between the planets $a$ and $b$. It is guaranteed that all light trains are pairwise disjoint.

It is guaranteed that it is possible to travel from any planet to any other planet of the galaxy using only light trains.
## 输出格式

Output a single reduced fraction, the expected minimum number of light trains Charlie has to take to get to work if she can use the (malfunctioning) teleportation system at most once.

Output the fraction as "$\texttt{a/b}$", where $a$ is the numerator and $b$ is the denominator.
## 样例

### 样例输入 #1
```
5 5 3
2 3 4
1 2
1 3
2 4
3 4
4 5
```
### 样例输出 #1
```
5/2
```
### 样例输入 #2
```
5 6 3
2 3 4
1 2
1 3
2 4
3 4
4 5
1 4
```
### 样例输出 #2
```
2/1
```


---

---
title: "[GCPC 2023] DnD Dice"
layout: "post"
diff: 普及/提高-
pid: P13669
tag: ['2023', 'Special Judge', 'ICPC']
---
# [GCPC 2023] DnD Dice
## 题目描述

In *Dungeons \& Dragons* (DnD) and many other role playing games, many
actions are determined by dice rolls, and it is also quite common to use dice
with different numbers of sides. The most common dice are those based on the
five Platonic solids, the tetrahedron, cube, octahedron, dodecahedron and
icosahedron, with $4$, $6$, $8$, $12$ and $20$ sides, respectively. In DnD
terminology, these dice are usually called d4, d6, d8, d12 and d20.

![](https://cdn.luogu.com.cn/upload/image_hosting/flvm7fum.png)

:::align{center}
The five standard dice, [Ramona Trusheim](https://commons.wikimedia.org/wiki/File:Spielw%C3%BCrfel_(als_Modelle_Platonischer_K%C3%B6rper_und_Trapezoeder).jpg)
:::

As a dungeon master, you are currently designing a campaign for your group of
players. In the final battle of this campaign, the players need to roll a
combination of multiple dice with varying numbers of sides, and the action of
the enemy is determined by the sum of the numbers on the dice that were rolled.
For balancing purposes, you want to sort these sums based on how likely they
are to occur, so that you can assign appropriate events to each of them.

Given the number of dice of each type, and assuming the sides of each die are
numbered from $1$ to the number of sides, find all possible sums of dice rolls
and output them sorted by non-increasing probability.


## 输入格式

The input consists of:
- One line with five integers $t$, $c$, $o$, $d$ and $i$, ($0 \le t, c, o, d, i \le 10$), giving the number of tetrahedra, cubes, octahedra, dodecahedra and icosahedra among the dice that are rolled. There is always at least one die, that is $t+c+o+d+i \ge 1$.

## 输出格式

Output all possible sums, ordered from most likely to least likely. If two sums occur with the same probability, then those sums may be printed in any relative order.
## 样例

### 样例输入 #1
```
1 1 1 0 0
```
### 样例输出 #1
```
11 10 9 12 8 13 14 7 15 6 5 16 17 4 18 3
```
### 样例输入 #2
```
2 0 0 1 0
```
### 样例输出 #2
```
9 14 12 11 10 13 15 8 16 7 6 17 5 18 4 19 3 20
```
### 样例输入 #3
```
0 0 0 0 1
```
### 样例输出 #3
```
10 3 9 8 14 13 11 7 6 12 20 4 15 5 16 1 2 19 17 18
```


---

---
title: "[NWERC 2023] Arranging Adapters"
layout: "post"
diff: 普及/提高-
pid: P13700
tag: ['2023', 'ICPC']
---
# [NWERC 2023] Arranging Adapters
## 题目背景

It is the day before the NWERC and you and your team are on the train towards Delft.
The journey is long and boring but you came up with a good idea: "Let's do some *train*ing".

$\quad$ *-- silence --*
## 题目描述

You take your laptop out and try to plug it in when you notice that the only socket is already in use.
Your friends smirk and reply: "No socket for you, no *train*ing for us".
Their smirks quickly fade as you pull out a power strip, unplug the charger from the socket, and plug it back into the power strip.
Now, there is enough space for your charger as well.

However, as soon as more sockets are available, your friends suddenly take out more devices that need to be charged.
You realize that you will not get them to train like this, so you decide to trick them into solving a problem instead.

![](https://cdn.luogu.com.cn/upload/image_hosting/jhlld6he.png)

:::align{center}
Illustration of Sample Input 2. The first six chargers can be plugged in as shown. Note that this is not the only possible solution. However, it can be shown that it is impossible to plug in all seven chargers.
:::

Your power strip comprises a row of $s$ sockets, and each socket is $3\,\rm{cm}$ in diameter.
Furthermore, as you examine the chargers, you notice that they all have integer lengths.
The plug of each charger is always on one of the two ends, and each charger can
only be used in two orientations. Chargers cannot overlap, but can touch,
and can extend beyond the end of the power strip as long as they are plugged in
to a socket.
This is visualized in Figure A.1.
Hoping that this allows them to avoid the *train*ing, your friends agree to write a program to solve this.
## 输入格式

The input consists of:

- One line with two integers $n$ and $s$ $(1\leq n\leq2\cdot 10^5$,  $1\leq s\leq10^9)$, the number of chargers you have and the number of sockets on the power strip.
- One line with $n$ integers $w$ ($3\leq w\leq10^9$),
the width of each charger in centimetres.


Note that you are allowed to rotate chargers by $180^\circ$ before plugging them in.

## 输出格式

Output the maximum number of chargers you can plug into the power strip at the same time.
## 样例

### 样例输入 #1
```
5 7
7 4 4 5 8
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
8 9
7 4 3 6 4 8 5 6
```
### 样例输出 #2
```
6
```


---

---
title: "[NWERC 2023] Date Picker"
layout: "post"
diff: 普及/提高-
pid: P13703
tag: ['2023', 'Special Judge', 'ICPC']
---
# [NWERC 2023] Date Picker
## 题目描述

The NWERC is coming up and your agenda is filling up with meetings.
One of your teammates wants to plan a meeting, and asks for your input.
However, instead of asking you for your exact agenda, you have to fill out two separate polls:
one for indicating which days you are available, and one for the hours!

![](https://cdn.luogu.com.cn/upload/image_hosting/6a7bghv1.png)
:::align{center}
Afilled agenda.
:::

As a computer scientist, you plan your meetings only on whole hours and each meeting takes an integer number of hours.
Therefore, your agenda can be modelled as a matrix of $7$ rows (days), and $24$ columns (hours).
Each cell in this matrix is either '$\texttt{.}$' or '$\texttt{x}$',
meaning that hour of that day you are either free or have a meeting, respectively.

You have to pick at least $d$ days in the first poll and $h$ hours in the second poll,
and we assume the meeting will take place on any of your picked hour/day combinations with equal probability.
What is the probability that you can attend the meeting if you fill in the polls optimally?
## 输入格式

The input consists of:
- $7$ lines with $24$ characters, each character being either '$\texttt{.}$' or '$\texttt{x}$', with '$\texttt{.}$' indicating the time slots you are available.
- One line with two integers $d$ and $h$ ($1 \leq d \leq 7$, $1 \leq h \leq 24$), the minimum number of days and hours you have to fill in.

## 输出格式

Output the probability that you are available at the chosen meeting time. Your answer should have an absolute or relative error of at most $10^{-6}$.
## 样例

### 样例输入 #1
```
xxxxxx..xx..xxxxxxxxxxxx
xxxxxxxxxxxxx....xxxxxxx
xxxxxxxxxxxxxxxxxxxxxxxx
xxxxxx..xx..xxxxxxxxxxxx
xxxxxxxxxxxxx...x..xxxxx
xxxxxxxxxxxxxxxxxxxxxxxx
xxxxxxxxxxxxxxxxxxxxxxxx
2 5
```
### 样例输出 #1
```
0.8

```
### 样例输入 #2
```
xxxxxxxxx.....x...xxxxxx
xxxxxxxx..x...x...xxxxxx
xxxxxxxx......x...x.xxxx
xxxxxxxx...xxxxxxxxxxxxx
xxxxxxxx...xxxxxxxxxxxxx
xxxxxxxx...xxxxxxxx.xxxx
......xxxxxxxxxxxxxxxxxx
3 8
```
### 样例输出 #2
```
0.958333333333333
```


---

---
title: "[GCPC 2024] Alien Attack 2"
layout: "post"
diff: 普及/提高-
pid: P13716
tag: ['并查集', '2024', '连通块', 'ICPC']
---
# [GCPC 2024] Alien Attack 2
## 题目描述

Aliens are visiting Earth and, as usual, they plan to abduct humans for their experiments.
In the past, alien abductions have caused a lot of press coverage and wild speculation on Earth.
Luckily for them, most people do not believe these stories and think that aliens are not real.

:::align{center}
![](https://upload.wikimedia.org/wikipedia/commons/0/0d/Rocket_USA_Battery_Operated_Tin_UFO_Mars_Explorer_Close_Up.jpg)

A representative of the Galactic Committee for Person Captures.

By D J Shin on [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Rocket_USA_Battery_Operated_Tin_UFO_Mars_Explorer_Close_Up.jpg)

:::

In order to keep a low profile in the future, the Galactic Committee for Person Captures (GCPC) has established rules for abductions.
Besides a lot of boring paperwork, the aliens have to prepare the abduction carefully.
While they can make multiple trips (in fact, alien travel is so fast in practice that this is not a limitation at all),
they must be smart about it so that their secret is not revealed to humans. If aliens want to abduct a person,
they are required to abduct all of their friends at the same time, so that no one notices that their friend is missing when they want to hang out.
Of course, friendships on planet Earth are bidirectional, that is if Alice is a friend of Bob, then Bob is also a friend of Alice.

In preparation for the trip, the aliens have observed their targets and started taking note of all their friendships.
In total, they must abduct $n$ people, including their friends.
Now, they want to book a starship at their local dealership and wonder how much space they need to abduct all $n$ people.
A starship's storage space is measured in terms of the number of people that can be transported simultaneously.
What is the minimum storage space required to abduct all $n$ people?

## 输入格式

The input consists of:
- One line with two integers $n$ and $m$ ($1\leq n\leq 2 \cdot 10^5$, $0\leq m\leq 2 \cdot 10^5$), the number of people and the total number of friendships between them.
- $m$ lines, each with two integers $i$ and $j$ ($1\leq i < j\leq n$), denoting a friendship between persons $i$ and $j$.


The people are numbered from $1$ to $n$. It is guaranteed that no friendship is listed multiple times.

## 输出格式

Output the minimum storage space needed to abduct all people.
## 样例

### 样例输入 #1
```
5 3
1 2
2 3
4 5
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3 0
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
8 8
1 2
2 3
3 4
1 4
1 5
2 6
3 7
4 8
```
### 样例输出 #3
```
8
```


---

---
title: "[GCPC 2024] Musical Mending"
layout: "post"
diff: 普及/提高-
pid: P13728
tag: ['数学', '2024', 'ICPC']
---
# [GCPC 2024] Musical Mending
## 题目描述

Shortly before the concert starts, you notice that your piano is completely out
of tune! Having the ability of relative pitch, you are able to discern the
difference between the pitch of any piano key to the first piano key. While this
does not help you find the absolute pitch, you decide to at least tune the keys relative
to each other. To do this, you need to make sure that the pitch of each key is exactly one 
higher than the key before it and one lower than the key after it.
As the concert will start shortly, you need to minimize the total tuning effort,
which is the sum of the absolute changes in pitch you apply to each key.
For example, Figure M.1 illustrates a solution for Sample Input 3, resulting in a total tuning effort of 23.

:::align{center}

![](https://cdn.luogu.com.cn/upload/image_hosting/4shk0pix.png)

Figure M.1: Visualization of Sample Input 3.
:::
## 输入格式

The input consists of:
- One line with an integer $n$ ($2 \leq n \leq 10^5$), the number of keys on the piano. 
- One line with $n$ integers $t_1,\dots,t_n$ ($-2 \cdot 10^5 \leq t_i \leq 2 \cdot 10^5$), where $t_i$ describes the difference in pitch between the $i$th key and the first key. The first integer $t_1$ is always $0$.    
## 输出格式

Output the minimal total tuning effort.
## 样例

### 样例输入 #1
```
7
0 1 2 3 4 5 6
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
5
0 1 4 3 6
```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
6
0 -2 10 6 7 -1
```
### 样例输出 #3
```
23
```
### 样例输入 #4
```
4
0 -4 -2 1
```
### 样例输出 #4
```
7
```
### 样例输入 #5
```
9
0 23452 145043 -3423 -20 9845 435 -3 4453
```
### 样例输出 #5
```
186237
```


---

---
title: "[CERC 2021] Letters"
layout: "post"
diff: 普及/提高-
pid: P13768
tag: ['模拟', '2021', 'ICPC', 'CERC']
---
# [CERC 2021] Letters
## 题目描述

Martin is attending a lecture on linear algebra. It is needless to say that the professor who is giving the lecture is the most boring person in the entire universe. There is a $N \times M$ matrix written on the blackboard. Some of the entries in the matrix are letters (of the English alphabet) while some other entries are blank. Here is an example of such a matrix of size $6 \times 8$:

$\begin{bmatrix} k & l & & n & d & i & \\ & & & & c \\  & & & & & i & h \\ j & & a \\ & c & b \\ & c & & & & e & f \end{bmatrix}.$

Martin has absolutely no idea what this matrix represents. He is so bored that he has not been following the lecture anymore for the last 30 minutes. However, Martin has an extremely vivid imagination. He is imagining that the matrix is suddenly influenced by gravity and all the letters in it are sliding downwards until each letter either 'reaches the bottom' or 'hits the letter that is below it'. In the first phase, the above matrix becomes:

$\begin{bmatrix} \\ \\ \\ & & l & & & i \\ k & & c & a & & d & i & h \\ j & & c & b & n & c & e & f \end{bmatrix}.$

After that, gravity changes direction and is now pulling the letters to the left. We are now in the second phase. Again, all the letters are sliding to the left until each letter either 'reaches the left bracket' or 'hits the letter on its left'. The previous matrix thus becomes:

$\begin{bmatrix} l & i \\ k & c & a & d & i & h \\ j & c & b & n & c & e & f \end{bmatrix}.$

Martin is carrying out this procedure in his head until the very end of the boring lecture. Of course, after each phase, i.e. after all the letters land at their respective destinations, gravity may change its direction (there are four possibilities for the direction: left, right, up and down).

### Task

Write a program that determines the final positions of all letters in the matrix given the precise sequence of the gravity direction changes.

## 输入格式

The first line contains three integers $N$, $M$ and $K$ where $N \times M$ is the size of the matrix and $K$ is the number of phases.

The second line contains a string of length $K$ that consists of letters L, R, U and D that represent the direction of gravity in each phase (left, right, up and down, respectively).

The final $N$ lines represent the matrix. Each of the lines contains $M$ characters. The characters are lowercase letters of the English alphabet and `.` (dot) which represents a blank entry.

## 输出格式

Output the matrix which Martin obtained at the end of the lecture. The format of the matrix is identical to the one in the input data.
## 样例

### 样例输入 #1
```
6 8 5
DLURD
k.l.ndi.
.....c..
......ih
j..a....
..cb....
..c...ef
```
### 样例输出 #1
```
........
........
........
......hf
..iadice
.lkcbnjc
```
### 样例输入 #2
```
3 3 0
a..
.b.
..x
```
### 样例输出 #2
```
a..
.b.
..x
```
## 提示

### Input limits

* $1 \leq N, M \leq 100$
* $0 \leq K \leq 100$


---

---
title: "[SWERC 2023] Card game"
layout: "post"
diff: 普及/提高-
pid: P13792
tag: ['2023', 'ICPC']
---
# [SWERC 2023] Card game
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/81d3c64f9dd7fdfb3f4c9a4e9e503c0ca089ccbb.png)

:::

The Olympic Games in Paris are almost here, and you are thrilled! You and four of your friends
managed to get five of the rare tickets for sports climbing even though all tickets were sold out in less
than two hours! While waiting for the games to start, you decide to do something fun to keep your
mind off the wait: play your favourite card game.


The card deck contains four standard suits of different colours: silver (S), white (W), emerald (E),
and red (R), as well as one trump suit coloured cyan (C). That is, the Cyan cards outrank all other
cards. There are $N$ cards of each suit, numbered from $1$ to $N$. This means that, in total, the deck
comprises $5N$ cards. At the beginning of the game, the deck is randomly distributed between the five
players, such that each player gets $N$ cards.


Before you start playing, you want to organise your cards such that all cards of the same suit are
next to each other in increasing order, and the trump cards appear at the end (also in increasing order).
When you receive your cards, they appear in your hand as a sequence. To organise them, you perform
a sequence of actions, where in each action you take one card out of your hand and put it back in your
hand at another position (between two cards, before the first card, or after the last card).


You cannot help but wonder: what is the minimum number of actions you need to take in order to organise your hand?
## 输入格式

The input consists of two lines. The first line contains the number $N$. The second line contains $N$ space-separated values describing the sequence of cards in your hand. Each value is composed of one letter of the set $\left\{ \texttt{S, W, E, R, C} \right\}$ (describing the card suit), followed by an integer V such that $1 \leq V \leq N$ (describing the card number).

**Limits**

- $1 \leq N \leq 100\,000$


## 输出格式

The output should contain a single line, consisting of a single number: the minimum number of actions required to organise your hand.
## 样例

### 样例输入 #1
```
4
C1 R2 E4 R1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
5
S2 W4 E1 R5 C1
```
### 样例输出 #2
```
0
```


---

---
title: "[SWERC 2023] Nicest view"
layout: "post"
diff: 普及/提高-
pid: P13796
tag: ['2023', 'ICPC', '单调栈']
---
# [SWERC 2023] Nicest view
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/93613cfd23ca0223b6f9aa573bf5381a7646cd95.png)

:::

Paris is so crowded with tourists during the Olympic games! You want to escape the city and go on a hike on a linear trail path, going from left to right. Every kilometre on that trail, including at start and end, is a milestone, on which is written the stone's altitude. The slope between two consecutive stones is constant, and no two stones have the same altitude.


Planning to come back with your friends, you try to identify the point of the hike at which you had the nicest view. The beauty of a point of view is defined as the distance (measured in kilometres) between your position and the leftmost position that you can see on your hike and that is at the same altitude as you are. If such a previous position fails to exist, it means that you can see the city and its smog, and the beauty of that view is zero.


You have listed the altitudes of the milestones. What is the maximal beauty on your hike?
## 输入格式

The input consists of two lines. The first line contains a single integer $N$, which is the number of milestones on the trail path. The second line contains $N$ space-separated integers $H_1, H_2, \dots, H_N$; each integer $H_k$ is the altitude (measured in metres) of the $k^\text{th}$ milestone on the path.


**Limits**

- $1 \leq N \leq 100~000$;
- $0 \leq H_k \leq 1~000~000$ for all $k \leq N$;
- the integers $H_k$ are pairwise distinct.

## 输出格式

The output should contain a single line, consisting of a single number $S$: the best beauty score on your hike. This number is written either as an integer or as an irreducible fraction $N/D$ for which $D \geq 2$; we recall that a fraction $N/D$ is irreducible when the greatest common divisor of $N$ and $D$ is $1$.
## 样例

### 样例输入 #1
```
7
0 5 3 1 4 8 2
```
### 样例输出 #1
```
13/4
```
### 样例输入 #2
```
5
3 5 8 7 1
```
### 样例输出 #2
```
0
```


---

---
title: "[SWERC 2023] Throwing dice"
layout: "post"
diff: 普及/提高-
pid: P13800
tag: ['2023', '期望', 'ICPC']
---
# [SWERC 2023] Throwing dice
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/a11e720cc14242ff598268192fbaaa26b9332c02.png)

:::

Alice and Bob are discussing penalty shoot-outs and their randomness: "We might as well be throwing dice to determine the winner!", Alice said. And so they started simulating penalty shoot-outs by each throwing dice, summing the points indicated on their dice, and comparing these sums. The player with the largest sum wins; in case both sums are equal, there is a tie.


But even in such situations, some player might have an edge over their opponent, depending on which dice they throw. Thus, just by looking at the dice they are about to throw, Alice and Bob want to determine who has the better edge.


Alice has $M$ fair dice, with $A_1, A_2, \dots, A_M$ sides. For all integers $k$ and $l$ such that $1 \leq k \leq M$ and $1 \leq l \leq A_k$, the $k^\text{th}$ die of Alice has a probability $1/A_k$ of showing its face numbered $l$. Then, Alice's score is the sum of the numbers displayed by her $M$ dice. Similarly, Bob has $N$ fair dice, with $B_1, B_2, \dots, B_N$ sides.


Given these dice, Alice has a probability $\mathbb{P}_A$ of having a strictly larger score than Bob, and Bob has a probability $\mathbb{P}_B$ of having a strictly larger score than Alice. Which probability is the largest one?

## 输入格式

The input consists of three lines, each one containing space-separated integers. The first line contains the numbers $M$ and $N$. The second line contains the numbers $A_1, A_2, \dots, A_M$. The third line contains the numbers $B_1, B_2, \dots, B_N$.

**Limits**
	
- $1 \leq M \leq 100~000$;
- $1 \leq N \leq 100~000$;
- $4 \leq A_k \leq 1~000~000~000$ for all $k \leq M$;
- $4 \leq B_k \leq 1~000~000~000$ for all $k \leq N$;

## 输出格式

The output should contain a single line, consisting of a single uppercase word: $\texttt{ALICE}$ if $\mathbb{P}_A > \mathbb{P}_B$, $\texttt{TIED}$ if $\mathbb{P}_A = \mathbb{P}_B$, and $\texttt{BOB}$ if $\mathbb{P}_A < \mathbb{P}_B$.
## 样例

### 样例输入 #1
```
8 1
4 4 4 4 4 4 4 4
6
```
### 样例输出 #1
```
ALICE
```
### 样例输入 #2
```
2 2
6 4
4 6
```
### 样例输出 #2
```
TIED
```
## 提示

**Sample Explanation 1**

Since Alice has 8 dice, her score is always 8 or more; Bob's score is always 6 or less. Hence, Alice has a probability $\mathbb{P}_A = 100\%$ of beating Bob, and he has a probability $\mathbb{P}_B = 0\%$ of beating her. Consequently, $\mathbb{P}_A > \mathbb{P}_B$.

**Sample Explanation 2**

Alice has a probability $\mathbb{P}_A = 125/288$ of beating Bob; he also has a probability $\mathbb{P}_B = 125/288$ of beating her.


---

---
title: "[CERC 2022] Deforestation"
layout: "post"
diff: 普及/提高-
pid: P13808
tag: ['2022', 'ICPC', 'CERC']
---
# [CERC 2022] Deforestation
## 题目描述

You want to remove a big tree from your property, but it's too big for you to carry all at once. How many pieces do you have to cut it into if the maximum weight you can carry is $W$?

The tree has a single trunk connected to the ground and can split out into multiple branches. All of those branches can branch out further etc. So each segment of the tree is a continuous mass of wood, which may or may not split out into multiple branches.

You can make cuts at any point on the tree; start, end, or anywhere in the middle of any segment. You can consider branching as an arbitrarily small part of the tree, i.e. you can cut immediately before or after a branch splits off without increasing the weight of the base branch, but it will affect whether the child branches are cut off as a single piece or just one branch is cut off separately.
## 输入格式

The first line of the input will contain $W$, your carrying capacity. The next line will continue with the description of the first tree segment; its trunk.

A tree segment description is defined recursively. The first line contains two numbers $M$, weight of the segment, and $N$, number of branches coming out of the segment at its end. This is followed by $N$ tree segment descriptions, describing each one of the branches.
## 输出格式

Output one number, the number of pieces you have to cut the tree into.
## 样例

### 样例输入 #1
```
1
10 0
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
7
5 2
7 0
2 0
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
5
2 3
2 2
1 0
1 0
6 0
4 2
3 0
2 0
```
### 样例输出 #3
```
5
```
## 提示

### Comment

Image shows some possible solutions of sample test cases.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/ovr7c4zx.png)
:::

### Input limits

* $1 \leq W, M \leq 10^9$
* $0 \leq N \leq 10^5$
* Total weight of all tree segments will not exceed $10^9$.
* Total number of segments will not exceed $10^5$.


---

---
title: "[CERC 2022] Denormalization"
layout: "post"
diff: 普及/提高-
pid: P13809
tag: ['2022', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2022] Denormalization
## 题目描述

Dr. Brodnik prepared a list $A = [a_1, a_2, \ldots, a_N]$ that contained $N$ integers. No one knows what exactly these numbers represented, but it is well known that:

* $1 \leq a_i \leq 10\,000$ for all $1 \leq i \leq N$ and
* their greatest common divisor was 1.

Dr. Hočevar decided to do his colleague a favor and normalized the list, as he thought that it represents a vector in the $n$-dimensional real vector space. Namely, he calculated the number

$$d = \sqrt{\sum_{i=1}^{N} a_i^2} = \sqrt{a_1^2 + a_2^2 + \cdots + a_N^2}$$

and replaced Dr. Brodnik's list by $[a_1/d, a_2/d, \ldots, a_N/d]$. The numbers in this normalized list were also rounded to 12 decimal places for storage. We will refer to the elements of the stored normalized list as $X = [x_1, x_2, \ldots, x_N]$. After some time, he realized that it was a mistake and he now wishes to recover the original list $A$. Of course, no backup of the original has been made. Since Dr. Hočevar is too busy at the moment doing more important tasks, your help will be much appreciated.

As some data was lost due to rounding, he will be happy with any reconstructed list $R = [r_1, r_2, \ldots, r_N]$, such that after normalization it would differ from $X$ by at most $10^{-6}$ in each corresponding element.
## 输入格式

The first line of the input contains an integer $N$, i.e. the length of the list $X$. The $i$-th of the following $N$ lines contains a floating-point number $x_i$ with exactly 12 decimal places. It is guaranteed that the input is valid, i.e. it was really obtained in the described manner from a list of integers with the properties described above.
## 输出格式

The output should contain $N$ lines containing the reconstructed integers $r_1, r_2, \ldots, r_N$ in this order. You can output any acceptable solution as described above.

## 样例

### 样例输入 #1
```
6
0.137516331034
0.165019597241
0.275032662068
0.412548993102
0.825097986204
0.165019597241
```
### 样例输出 #1
```
5
6
10
15
30
6
```
## 提示

### Input limits

* $2 \leq N \leq 10\,000$
* $0 < x_i < 1$ for all $1 \leq i \leq N$

### Output limits

* $1 \leq r_i \leq 10\,000$ for all $1 \leq i \leq N$
* $\gcd(r_1, \ldots, r_N) = 1$


---

---
title: "[CERC 2023] Ball Passing"
layout: "post"
diff: 普及/提高-
pid: P13846
tag: ['2023', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2023] Ball Passing
## 题目描述

A group of students has just finished their math lesson and they’re heading out for physical education. Their teacher has asked them to arrange themselves in a circle. After several minutes of busy moving around the court they have finally managed to position themselves so that they form a strictly convex polygon. They might not lie on the circle, but the teacher is happy to at least get some structure.

There is an even number of boys and an even number of girls in this group of $N$ students. They will practice ball passing in pairs, therefore the teacher has to pair them up. The teacher will pair boys among themselves and the same for girls.

The school administration has decided to address the decline in physical performance of their students. Therefore, they have implemented a quality measure for ball passing practice, which is the total distance traveled by the balls in a single round of ball passes between each pair. Help the teacher pair up the students in a way that will maximize this measure.
## 输入格式

The first line contains the number of students $N$. The second line contains a string $S$ of length $N$, which describes the students along the perimeter of the polygon with a character "B" for a boy and "G" for a girl. The following $N$ lines provide the locations of students with space-separated integer coordinates $X_i$ and $Y_i$ in the same order as they are described in the string $S$.

## 输出格式

Output the maximum ball passing distance that can be obtained by pairing up the students appropriately. The solution will be considered correct if the relative or absolute error compared to the official solution is within $10^{-6}$.
## 样例

### 样例输入 #1
```
4
BGBG
0 0
0 1
1 1
1 0
```
### 样例输出 #1
```
2.828427125
```
### 样例输入 #2
```
4
GGBB
0 0
0 1
1 1
1 0
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
12
GBGBBGBBBBGB
0 -15
6 -14
19 -5
17 7
11 12
1 15
-9 13
-15 10
-17 8
-19 4
-16 -9
-13 -11
```
### 样例输出 #3
```
186.529031603
```
## 提示

### Input limits

- $2 \leq N \leq 50$
- The number of boys and girls will both be even. Note that one of them can be zero.
- The coordinates $X_i$ and $Y_i$ won’t exceed 10 000 by absolute value.


---

---
title: "[SEERC 2019] Absolute Game"
layout: "post"
diff: 普及/提高-
pid: P5804
tag: ['2019', 'ICPC']
---
# [SEERC 2019] Absolute Game
## 题目描述

Alice 和 Bob 在玩一个游戏。Alice 有一个包含 $n$ 个整数的数列 $a$，Bob 有一个包含 $n$ 个整数的数列 $b$。每一回合中，玩家需要从他的数列中删去一个数字。玩家轮流进行回合，Alice 先手。

当两个数列中都只剩下一个数字的时候，游戏结束。令 Alice 的数列剩下的数字为 $x$，Bob 的数列剩下的数字为 $y$。Alice 想要最大化 $x$ 与 $y$ 之差的绝对值，而 Bob 想最小化这个值。两个玩家都以最优策略游戏。

请算出游戏结束时的结果。
## 输入格式

第一行包含一个整数 $n \ (1 \leq n \leq 1 \ 000)$，代表每个数列中的数字个数。

第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n \ (1 \leq a_i \leq 10^9)$，代表 Alice 的数列中的数字。

第三行包含 $n$ 个整数 $b_1, b_2, \dots, b_n \ (1 \leq b_i \leq 10^9)$，代表 Bob 的数列中的数字。
## 输出格式

输出当两个玩家都以最优策略游戏时，$x$ 与 $y$ 之差的绝对值。
## 样例

### 样例输入 #1
```
4
2 14 7 14
5 10 9 22
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
1
14
42
```
### 样例输出 #2
```
28
```
## 提示

第一个样例中，$x=14, y=10$，因此两个数之差为 $4$。

第二个样例中，两个数列都只剩下一个数字了，因此 $x=14, y=42$。


---

---
title: "[SEERC 2019] Graph and Cycles"
layout: "post"
diff: 普及/提高-
pid: P5805
tag: ['2019', 'ICPC']
---
# [SEERC 2019] Graph and Cycles
## 题目描述

有一个 $n$ 个点的无向有边权的完全图，其中 $n$ 是奇数。

定义一个大小为 $k$ 的*环边组*为一个边构成的数组 $[e_1, e_2, \dots, e_k]$，且具有以下性质：

- $k$ 大于 $1$。
- 对于任意 $[1, k]$ 中的整数 $i$，边 $e_i$ 与 $e_{i-1}$ 和 $e_{i+1}$ 都恰好有一个相同的端点（规定 $e_0=e_k, e_{k+1}=e_1$）。

显然一个环边组中的边构成了图上的一个环。

定义一个参数为两条边 $e_1, e_2$ 的函数 $f(e_1, e_2)$，其函数值为两条边中边权的较大值。

定义一个环边组 $C=[e_1, e_2, \dots, e_k]$ 的*价值*为对于任意 $[1, k]$ 中的整数 $i$，$f(e_i, e_{i+1})$ 的值之和（规定 $e_{k+1}=e_1$）。

定义一个图的*环分割*为一组无交集的环边组，且这些环边组的并包含了图上所有的边。定义一个图的环分割的*价值*为其中所有环边组的价值之和。

一个图可能存在多组环分割。给定一个图，你的任务是找到价值最小的环分割并输出该最小价值。
## 输入格式

第一行包含一个整数 $n \ (3 \leq n \leq 999, n \bmod 2 = 1)$，代表图的点数。

接下来的 $\frac{n\cdot (n-1)}{2}$ 行每行包含三个整数 $u, v$ 和 $w \ (1 \leq u, v \leq n, u \neq v, 1 \leq w \leq 10^9)$，代表点 $u$ 和点 $v$ 间有一条边权为 $w$ 的边。
## 输出格式

输出一个整数，代表给定图的最小价值环分割的价值。
## 样例

### 样例输入 #1
```
3
1 2 1
2 3 1
3 1 1
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
5
4 5 4
1 3 4
1 2 4
3 2 3
3 5 2
1 4 3
4 2 2
1 5 4
5 2 4
3 4 2
```
### 样例输出 #2
```
35
```
## 提示

以下样例解释中，边以输入顺序编号，$e_i$ 代表输入顺序中的第 $i$ 条边。

第一个样例中，唯一的环分割为 $S=\{ [e_1, e_2, e_3] \}$。$f(e_1, e_2)+f(e_2,e_3)+f(e_3,e_1)=1+1+1=3$。

第二个样例中，最优的环分割为 $S=\{ [e_3, e_8, e_9], [e_2,e_4,e_7,e_{10},e_5,e_1,e_6] \}$。环边组 $[e_3,e_8,e_9]$ 的价值为 $12$，$[e_2,e_4,e_7,e_{10},e_5,e_1,e_6]$ 的价值为 $23$，因此环分割的价值为 $35$。


---

---
title: "[NEERC 2016] Hard Refactoring"
layout: "post"
diff: 普及/提高-
pid: P6123
tag: ['字符串', '2016', 'ICPC']
---
# [NEERC 2016] Hard Refactoring
## 题目描述

对于一个变量 $x$，给出一些约束条件，形如 $x \geq a$，$x \le a$ 
这些约束条件之间用```||```连接，然后你需要将这些约束条件简化，最后输出简化后的约束条件。
## 输入格式

输入不超过 $10^3$ 行，每行要么是两个用 ```&&``` 连接的约束条件，要么就是单个的约束条件。

如果一行有两个约束条件，第一个约束条件总是 $x \geq a$ 的形式，第二个约束总是 $x \leq a$ 的形式。

除了输入的最后一行，每一行末尾都有一个 ```||```。

并且所有的字符（除了`>=`，`<=`，`&&`，`||`）之间均由空格隔开，且没有多余的前置、后置空格。
## 输出格式

输出若干行，表示最简的约束条件的形式（也就是使输出的行数尽量少），其余格式与输入格式保持一致。

输出的若干行可以不按照特定的顺序输出。

特别地，如果对于任意的 $x∈[-32768,32767]$，$x$均能满足约束条件，仅输出一行```true```，反之，若对于任意的 $x∈[-32768,32767]$，$x$均不能满足约束条件，仅输出一行```false```。
## 样例

### 样例输入 #1
```
x >= 5 && x <= 10 ||
x >= 7 && x <= 20 ||
x <= 2 ||
x >= 21 && x <= 25 ||
x >= 8 && x <= 10 ||
x >= 100
```
### 样例输出 #1
```
x <= 2 ||
x >= 5 && x <= 25 ||
x >= 100
```
## 提示

对于所有在这一题中出现的数字（包括 $x$），都$\ge -32768$（$-2^{15}$） 且 $\le 32767 $（$2^{15}-1$）。


---

---
title: "[ICPC 2017 WF] Need for Speed"
layout: "post"
diff: 普及/提高-
pid: P6933
tag: ['2017', 'Special Judge', 'ICPC']
---
# [ICPC 2017 WF] Need for Speed
## 题目描述

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14637/1.png)

Sheila is a student and she drives at ypical student car: it is old, slow, rusty, and falling apart. Recently,the needle on the speedometer fell off. She glued it back on, but she might have placed it at the wrong angle. Thus, when the speedometer reads $s$,her true speed is $s+c$, where $c$ is an unknown constant(possibly negative).

Sheila made a careful record of a recent journey and wants to use this to compute $c$ . The journey consisted of $n$ segments. In the $i^{th}$ segment she traveled a distance of $d_{i}$ and the speedometer read $s_{i}$ for the entire segment. This whole journey took time $t$ . Help Sheila by computing $c$ .

Note that while Sheila's speedometer might have negative readings, her true speed was greater than zero for each segment of the journey.


## 输入格式



The first line of input contains two integers $n (1 \le n \le 1 000)$ , the number of sections in Sheila's journey, and $t (1 \le t \le 10^{6}),$ the total time. This is followed by $n$ lines, each describing one segment of Sheila's journey. The $i^{th}$ of these lines contains two integers $d_{i} (1 \le d_{i} \le 1 000)$ and $s_{i} (|s_{i}| \le 1 000)$ , the distance and speedometer reading for the $i^{th}$ segment of the journey. Time is specified in hours, distance in miles, and speed in miles per hour.


## 输出格式



Display the constant $c$ in miles per hour. Your answer should have an absolute or relative error of less than $10^{−6}.$


## 样例

### 样例输入 #1
```
3 5
4 -1
4 0
10 3

```
### 样例输出 #1
```
3.000000000

```
### 样例输入 #2
```
4 10
5 3
2 2
3 6
3 1

```
### 样例输出 #2
```
-0.508653377

```
## 提示

Time limit: 1 s, Memory limit: 512 MB. 

spj provider:@[shenyouran](/user/137367).
## 题目翻译

在你面前的是一个坏掉的速度表，当显示速度为 $s$ km/h 时，实际速度为 $s+c$ km/h，$c$ 为固定的常数，为任意实数。你打算计算这个 $c$，于是准备用这个速度表记录速度。现在你要走 $n$ 段路程，第 $i$ 段路程距离为 $d_i$ 米，显示的指数为 $s_i$ km/h，总共路程用了 $t$ 小时。求 $c$ 的值。

你的答案应该与正确答案的差在 $10^{-6}$ 以内。

$1 \le n \le 1000$，$1 \le t \le 10^6$，$1 \le d_i \le 1000$，$|s_i| \le 1000$。

翻译者：一只书虫仔


---

---
title: "[ICPC 2017 WF] Secret Chamber at Mount Rushmore"
layout: "post"
diff: 普及/提高-
pid: P6937
tag: ['2017', 'ICPC']
---
# [ICPC 2017 WF] Secret Chamber at Mount Rushmore
## 题目描述



![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14641/1.png)

By now you have probably heard that there is a spectacular stone sculp-ture featuring four famous U.S. presidents at Mount Rushmore.  How-ever, very few people know that this monument contains a secret cham-ber. This sounds like something out of a plot of a Hollywood movie, butthe chamber really exists.  It can be found behind the head of AbrahamLincoln and was designed to serve as a Hall of Records to store impor-tant historical U.S. documents and artifacts.  Historians claim that theconstruction of the hall was halted in 1939 and the uncompleted cham-ber was left untouched until the late 1990s,  but this is not the wholetruth.

In $1982$ , the famous archaeologist $S$ . Dakota Jones secretly visited the monument and found that the chamber actually was completed, but it was kept confidential. This seemed suspicious and after some poking around, she found a hidden vault and some documents inside. Unfortunately, these documents did not make any sense and were all gibberish. She suspected that they had been written in a code, but she could not decipher them despite all her efforts.

Earlier this week when she was in the area to follow the ACM-ICPC World Finals, Dr. Jones finally discovered the key to deciphering the documents, in Connolly Hall of $SDSM&T$ . She found a document that contains a list of translations of letters. Some letters may have more than one translation, and others may have no translation. By repeatedly applying some of these translations to individual letters in the gibberish documents, she might be able to decipher them to yield historical U.S . documents such as the Declaration of Independence and the Constitution. She needs your help.

You are given the possible translations of letters and a list of pairs of original and deciphered words. Your task is to verify whether the words in each pair match. Two words match if they have the same length and if each letter of the first word can be turned into the corresponding letter of the second word by using the available translations zero or more times.


## 输入格式



The first line of input contains two integers $m (1 \le m \le 500)$ and $n (1 \le n \le 50)$ , where $m$ is the number of translations of letters and $n$ is the number of word pairs. Each of the next $m$ lines contains two distinct space-separated letters a and $b$ , indicating that the letter a can be translated to the letter $b$ . Each ordered pair of letters $(a , b)$ appears at most once. Following this are $n$ lines, each containing a word pair to check. Translations and words use only lowercase letters $‘a'-‘z',$ and each word contains at least $1$ and at most $50$ letters.


## 输出格式



For each pair of words, display yes if the two words match, and no otherwise.


## 样例

### 样例输入 #1
```
9 5
c t
i r
k p
o c
r o
t e
t f
u h
w p
we we
can the
work people
it of
out the

```
### 样例输出 #1
```
yes
no
no
yes
yes

```
### 样例输入 #2
```
3 3
a c
b a
a b
aaa abc
abc aaa
acm bcm

```
### 样例输出 #2
```
yes
no
yes

```
## 提示

Time limit: 1 s, Memory limit: 512 MB. 


## 题目翻译

一共有 $m$ 种字母的转换关系，每一种转换关系表示为，可以从小写字母 $a$ 转化为小写字母 $b$，转换关系单向且不重复。现在给定 $n$ 组询问，每一组询问字符串 $s$ 是否能通过转换关系变为 $t$。

$1 \le m \le 500$，$1 \le n \le 50$，$a,b$ 只为小写字母，$s,t$ 只包含小写字母，长度在 $[1,50]$ 内。

翻译者：一只书虫仔


---

---
title: "[ICPC 2018 WF] Comma Sprinkler"
layout: "post"
diff: 普及/提高-
pid: P6942
tag: ['2018', 'ICPC']
---
# [ICPC 2018 WF] Comma Sprinkler
## 题目描述

As practice will tell you, the English rules for comma placement are complex, frustrating, and often ambiguous. Many people, even the English, will, in practice, ignore them, and, apply custom rules, or, no rules, at all.

Doctor Comma Sprinkler solved this issue by developing a set of rules that sprinkles commas in a sentence with no ambiguity and little simplicity. In this problem you will help Dr. Sprinkler by producing an algorithm to automatically apply her rules.

Dr. Sprinkler's rules for adding commas to an existing piece of text are as follows:

If a word anywhere in the text is preceded by a comma, find all occurrences of that word in the text, and put a comma before each of those occurrences, except in the case where such an occurrence is the first word of a sentence or already preceded by a comma.

If a word anywhere in the text is succeeded by a comma, find all occurrences of that word in the text, and put a comma after each of those occurrences, except in the case where such an occurrence is the last word of a sentence or already succeeded by a comma.

Apply rules $1$ and $2$ repeatedly until no new commas can be added using either of them.

As an example, consider the text

please sit spot. sit spot, sit. spot here now here.

Because there is a comma after spot in the second sentence, a comma should be added after spot in the third sentence as well (but not the first sentence, since it is the last word of that sentence). Also, because there is a comma before the word sit in the second sentence, one should be added before that word in the first sentence (but no comma is added before the word sit beginning the second sentence because it is the first word of that sentence). Finally, notice that once a comma is added after spot in the third sentence, there exists a comma before the first occurrence of the word here. Therefore, a comma is also added before the other occurrence of the word here. There are no more commas to be added so the final result is

please, sit spot. sit spot, sit. spot, here now, here.


## 输入格式



The input contains one line of text, containing at least $2$ characters and at most $1 000 000$ characters. Each character is either a lowercase letter, a comma, a period, or a space. We define a word to be a maximal sequence of letters within the text. The text adheres to the following constraints:

The text begins with a word.

Between every two words in the text, there is either a single space, a comma followed by a space, or a period followed by a space (denoting the end of a sentence and the beginning of a new one).

The last word of the text is followed by a period with no trailing space.


## 输出格式



Display the result after applying Dr. Sprinkler's algorithm to the original text.


## 样例

### 样例输入 #1
```
please sit spot. sit spot, sit. spot here now here.

```
### 样例输出 #1
```
please, sit spot. sit spot, sit. spot, here now, here.

```
### 样例输入 #2
```
one, two. one tree. four tree. four four. five four. six five.

```
### 样例输出 #2
```
one, two. one, tree. four, tree. four, four. five, four. six five.

```
## 提示

Time limit: 8 s, Memory limit: 1024 MB. 


## 题目翻译

给定一些文本，对他添加逗号。

添加的规则为：

1. 找到一个单词前面有逗号，就在文本中的其他这个单词前添加一个逗号，除非这个单词是句子的第一个单词，或单词前已经有逗号了。
2. 找到一个单词后面有逗号，就在文本中的其他这个单词后添加一个逗号，除非这个单词是句子的最后一个单词，或单词后已经有逗号了。
3. 重复 1 和 2 直到不能填加逗号。

$2 \le $ 文本长度 $ \le 10^6$。

文本满足以下特征：

- 文本开头为一个单词；
- 两个单词之间为一个空格，或者一个逗号一个空格，或者一个句号一个空格；
- 文本末尾为一个句号。

翻译者：一只书虫仔


---

---
title: "[NEERC 2017] Easy Quest"
layout: "post"
diff: 普及/提高-
pid: P6956
tag: ['2017', 'Special Judge', 'ICPC']
---
# [NEERC 2017] Easy Quest
## 题目描述



A young hero is starting his heroic life. The wise wizard suggested him an easy first quest. During this quest our young hero meets $n$ magical creatures, in specific order. In order to help the young hero, the wizard gave him a clue -- a list of $n$ integers $a_{i}.$

If $a_{i}$ is positive, then the i-th magical creature is benevolent and gives to our hero one magical item of type $a_{i}.$ The hero can keep several items of the same type.

If $a_i$ is negative, then the i-th magical creature is evil and in order to defeat it the young hero needs one magical item of type $−a_{i}.$ All magical items are fragile and can be used only once.

If $a_{i}$ is zero, then the i-th creature is a unicorn. It gives the hero any magical item he asks for, but only one.

Your task is to help the young hero to finish the first quest, defeating all enemies on the way, or say that it is impossible.


## 输入格式



The first line of input contains one integer $n (1 \le n \le 1000)$ . The second line contains $n$ integers $a_{i} (−1000 \le a_{i} \le 1000)$ .


## 输出格式



If it is impossible to defeat all enemies, then output one string `No`. If it is possible, then output string `Yes`, and in the next line output the types of items the hero should ask the unicorns for, in order they meet during the quest. Types must be integers in range from $1$ to $1000$ inclusive. If there are several solutions, output any of them.


## 样例

### 样例输入 #1
```
10
1 0 -4 0 0 -1 -3 0 -1 -2

```
### 样例输出 #1
```
Yes
4 1 3 2

```
### 样例输入 #2
```
5
5 8 0 -6 -3

```
### 样例输出 #2
```
No

```
### 样例输入 #3
```
3
2 -2 -2

```
### 样例输出 #3
```
No

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 

spj provider:@[shenyouran](/user/137367).
## 题目翻译

一个英雄进行了一次探索。在这次探索中，英雄按特定顺序遇到了 $n$ 个魔法生物，第 $i$ 个魔法生物对应 $a_i$。

当 $a_i$ 为正数时，第 $i$ 个魔法生物会给英雄提供一个为 $a_i$ 的魔法物品。

当 $a_i$ 为负数时，第 $i$ 个魔法生物需要英雄消耗一个为 $-a_i$ 的魔法物品。

当 $a_i$ 为 $0$ 时，第 $i$ 个魔法生物可以给英雄提供一个任意的魔法物品。

你需要回答英雄是否可以完成这次探索（经过所有魔法生物），如果可以，请回答 $a_i$ 为 $0$ 魔法生物应该为英雄提供哪种魔法物品。


---

---
title: "[NEERC 2015] Generators"
layout: "post"
diff: 普及/提高-
pid: P6979
tag: ['2015', 'Special Judge', 'ICPC']
---
# [NEERC 2015] Generators
## 题目描述



Little Roman is studying linear congruential generators -- one of the oldest and best known pseudorandom number generator algorithms. Linear congruential generator (LCG) starts with a non-negative integer number $x_{0}$ also known as seed and produces an infinite sequence of non-negative integer numbers $x_{i} (0 \le x_{i} < c)$ which are given by the following recurrence relation:

$x_{i+1} = (ax_{i} + b)$ mod $c$

here a , $b$ , and $c$ are non-negative integer numbers and $0 \le x_{0} < c$ .

Roman is curious about relations between sequences generated by different LCGs. In particular, he has $n$ different LCGs with parameters $a^{(j)}, b^{(j)},$ and $c^{(j)}$ for $1 \le j \le n$ , where the j-th LCG is generating a sequence $x_{i}^{(j)}.$ He wants to pick one number from each of the sequences generated by each LCG so that the sum of the numbers is the maximum one, but is not divisible by the given integer number $k$ .

Formally, Roman wants to find integer numbers $t_{j} \ge 0$ for $1 \le j \le n$ to maximize $s = Σ^{n}_{j=1} x_{t_{j}}^{(j)}  subject$ to constraint that $s$ mod $k ≠ 0$ .


## 输入格式



The first line of the input file contains two integer numbers $n$ and $k (1 \le n \le 10 000 , 1 \le k \le 10^{9}).$ The following $n$ lines describe LCGs. Each line contains four integer numbers $x_{0}^{(j)}, a^{(j)}, b^{(j)},$ and $c^{(j)} (0 \le a^{(j)}, b^{(j)} \le 1000 , 0 \le x_{0}^{(j)} < c^{(j)} \le 1000)$ .


## 输出格式



If Roman's problem has a solution, then write on the first line of the output file a single integer $s$ -- the maximum sum not divisible by $k$ , followed on the next line by $n$ integer numbers $t_{j} (0 \le t_{j} \le 10^{9})$ specifying some solution with this sum.

Otherwise, write to the output file a single line with the number $−1$ .


## 样例

### 样例输入 #1
```
2 3
1 1 1 6
2 4 0 5

```
### 样例输出 #1
```
8
4 1

```
### 样例输入 #2
```
2 2
0 7 2 8
2 5 0 6

```
### 样例输出 #2
```
-1

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 


## 题目翻译

### 题目描述

罗曼在学习线性同余发生器——最古老，也是最广为人知的伪随机数生成算法之一。线性同余发生器（LCG）以 $x_0$ 为随机种子，生成很多非负整数 $x_i$ ,它遵循以下规则：

给定非负整数 $a,b,c\space(0≤x_0<c)$ ，
$x_{i+1} = (ax_i+b)\space mod \space c$

罗曼很好奇由不同LCG产生的序列之间的关系。特别地，他有 $n$ 个不同的LCG，含有参数 $a^{(j)}, b^{(j)}, c^{(j)}\space(1≤j≤n)$。第 $j$ 个LCG会生成一个序列 $x_i^{(j)}$ 。

他希望能从每个LCG产生的序列中挑出一个数，使他们的和最大，且不被给定的 $k$ 整除。

**格式化一点来说**，他希望找到整数 $t_j \space(t_j>0,1≤j≤n)$ ，使$s=\sum\limits_{j=1}^nx_{t_j}^{(j)}$最大，且$s\not\equiv0(mod\space k)$。

### 输入格式 

第 $1$ 行包括两个整数$n,k$。

$(1≤n≤10000,1≤k≤10^9)$


接下来 $n$ 行描述LCG，每行包括4个整数：$x_0^{(j)},a^{(j)}, b^{(j)}, c^{(j)}$ 。

$(0≤a^{(j)}, b^{(j)}≤1000,0≤x_0^{(j)}<c^{(j)}≤1000)$

### 输出格式 

如果有解，第 $1$ 行输出 $s$，第 $2$ 行输出 $n$ 个 $t_j$ 。

$(0≤t_j≤10^9)$ 。

如果无解，输出 $-1$ 。

### 说明/提示
时间限制：1秒

空间限制：256MB


---

---
title: "[NEERC 2014] Alter Board"
layout: "post"
diff: 普及/提高-
pid: P6985
tag: ['2014', 'Special Judge', 'ICPC']
---
# [NEERC 2014] Alter Board
## 题目描述

Little Dima gave his little brother Petya interactive chess board of size $n \times m$ as a present. There are many awesome features of this board but one is Petya's favorite. He can choose any rectangle formed by board squares and perform an inversion. Every white cell in the inverted rectangle becomes black and every black one becomes white.

In the initial state the board is colored in chess style, namely every cell is either black or white and every two cells that share a side have different colors. Little Petya wants to perform several inversions described above to turn all cells into the same color. He is impatient, so he asks you to provide him with instructions to do it with the minimal number of inversions.
## 输入格式

Contains two integers $n$ and $m (1 \le n , m \le 50) -$ the number of rows and columns on the board, respectively.
## 输出格式


The first line must contain the number of inversions $k$ required to transform the board.

The following $k$ lines must describe inversions, one per line. Each line must contains $4$ integers $-$ row and column of one of the corners of the corresponding rectangle and row and column of the opposite corner. Any two opposite corners can be used to specify a rectangle.

Rows of the board are numbered from $1$ to $n$ . Columns of the board are numbered from $1$ to $m$ . 
## 样例

### 样例输入 #1
```
2 2

```
### 样例输出 #1
```
2
1 1 1 1
2 2 2 2

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 

spj provider:@[shenyouran](/user/137367).
## 题目翻译

给出了一个 $n$ 行 $m$ 列的国际象棋棋盘。每次可以选择一个矩形区域，将里面的所有格子的颜色翻转。问最少需要多少次才能让所有格子变成同色？请输出一组合法的翻转方案。



---

---
title: "[NEERC 2014] Joke with permutation"
layout: "post"
diff: 普及/提高-
pid: P6994
tag: ['2014', 'Special Judge', 'ICPC']
---
# [NEERC 2014] Joke with permutation
## 题目描述

Joey had saved a permutation of integers from $1$ to $n$ in a text file. All the numbers were written as decimal numbers without leading spaces.

Then Joe made a practical joke on her: he removed all the spaces in the file.

Help Joey to restore the original permutation after the Joe's joke! 
## 输入格式

The input file contains a single line with a single string -- the Joey's permutation without spaces.

The Joey's permutation had at least $1$ and at most $50$ numbers. 
## 输出格式

Write a line to the output file with the restored permutation. Don’t forget the spaces!

If there are several possible original permutations, write any one of them.
## 样例

### 样例输入 #1
```
4111109876532

```
### 样例输出 #1
```
4 1 11 10 9 8 7 6 5 3 2

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 

Thanks to checker provider:@[Arcturus1350
](/user/57699).
## 题目翻译

给出数字之间无分隔符的 $1\dots n$ 的排列构成的字符串，将其还原为合法的排列。

保证 $n\leq 50$，输入数据均保证有解。如有多解输出任一即可。

样例可能有助于你更好理解题意。


---

---
title: "[NWRRC 2017] Boolean Satisfiability"
layout: "post"
diff: 普及/提高-
pid: P7020
tag: ['2017', 'ICPC']
---
# [NWRRC 2017] Boolean Satisfiability
## 题目描述



Boolean satisfiability problem (SAT) is known to be a very hard problem in computer science. In this problem you are given a Boolean formula, and you need to find out if the variables of a given formula can be consistently replaced by the values true or false in such a way that the formula evaluates to true. SAT is known to be NP-complete problem. Moreover, it is NP-complete even in case of $3-CNF$ formula $(3-SAT).$ However, for example, SAT problem for $2-CNF$ formulae $(2-SAT)$ is in $P$ .

$#SAT$ is the extension of SAT problem. In this problem you need to check if it is possible, and count the number of ways to assign values to variables. This problem is known to be $#P-complete$ even for $2-CNF$ formulae. We ask you to solve $#1-DNF-SAT,$ which is $#SAT$ problem for $1-DNF$ formulae.

You are given a Boolean formula in $1-DNF$ form. It means that it is a disjunction (logical or) of one or more clauses, each clause is exactly one literal, each literal is either variable or its negation (logical not).

Formally:

$〈formula〉 ::= 〈clause〉 | 〈formula〉 ∨ 〈clause〉$

$〈clause〉 ::= 〈literal〉$

$〈literal〉 ::= 〈variable〉 | ¬ 〈variable〉$

$〈variable〉 ::=$ A . . . $Z |$ a . . . $z$

Your task is to find the number of ways to replace all variables with values true and false (all occurrences of the same variable should be replaced with same value), such that the formula evaluates to true.


## 输入格式



The only line of the input file contains a logical formula in $1-DNF$ form (not longer than $1000$ symbols). Logical operations are represented by $‘|'$ (disjunction) and $‘ \sim ' (negatio_n).$ The variables are $‘A'$ . . . $‘Z'$ and $‘a'$ . . . $‘z'$ (uppercase and lowercase letters are different variables). The formula contains neither spaces nor other characters not mentioned in the grammar.


## 输出格式



Output a single integer -- the answer for $#SAT$ problem for the given formula.


## 样例

### 样例输入 #1
```
a

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
B|~B

```
### 样例输出 #2
```
2

```
### 样例输入 #3
```
c|~C

```
### 样例输出 #3
```
3

```
### 样例输入 #4
```
i|c|p|c

```
### 样例输出 #4
```
7

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

给定一个由大小写字母（变量），``|`` 和 ``~`` 组成的布尔代数式，求对于给定的变量，有多少种方案使得给定的代数式值为 ``True`` 。

注：

``a|b`` 表示 $a\vee b$ , 也就是 C++ 中的 ``a || b`` 。

``~a`` 表示 $\neg a$，也就是 C++ 中的 ``(!a)`` 。

变量只有可能由单个字母构成。


---

---
title: "[NWRRC 2015] Distribution in Metagonia"
layout: "post"
diff: 普及/提高-
pid: P7051
tag: ['2015', 'Special Judge', 'ICPC']
---
# [NWRRC 2015] Distribution in Metagonia
## 题目描述



There are one hundred noble families in the country of Metagonia, and each year some of these families receive several ritual cubes from the Seer of the One. The One has several rules about cube distribution: if a family receives at least one cube, every prime divisor of the number of cubes received should be either $2$ or $3$ , moreover if one family receives a $> 0$ cubes and another family in the same year receives $b > 0$ cubes then a should not be divisible by $b$ and vice versa.

You are the Seer of the One. You know in advance how many cubes would be available for distribution for the next $t$ years. You want to find any valid distribution of cubes for each of these years. Each year you have to distribute all cubes available for that year.


## 输入格式



The first line of input file contains a single integer $t$ -- the number of years to come $(1 \le t \le 1000)$ . Each of the following $t$ lines contains a single integer $n_{i}$ -- the number of cubes to distribute in i-th year $(1 \le n_{i} \le 10^{18}).$


## 输出格式



For each year $i$ output two lines. The first line should contain $m_{i}$ -- the number of families that would receive at least one cube in i-th year $(1 \le m_{i} \le 100)$ . The second line should contain $m_{i}$ integers -- the number of cubes received by each family. The sum of these numbers should be equal to $n_{i}.$


## 样例

### 样例输入 #1
```
4
1
2
3
10

```
### 样例输出 #1
```
1
1
1
2
1
3
2
4 6

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

在一个叫做 镁铊铬铌氩$ (Metagonia)$ 的国度中，有$100$个贵族家庭。

每年，这些贵族家庭都要收到来自先知之首的若干个典礼用的小方块。先知有一些分配小方块的规则：

1. 如果某年有一个家庭收到了小方块，那么这个家庭所收到的小方块的个数的质因数只能是$2$和$3$。

2. 如果某年有一个家庭收到了$a>0$个小方块，同年另一个家庭收到了$b>0$个小方块，那么$a$不整除$b$，$b$也不整除$a$。

现在，你作为先知之首，你知道你接下来的$t$年中，你每年有多少个小方块。你现在想要找到任意一个可行的方案，以便在接下来$t$年中能够进行按规则分配。

--------

第一行，包含一个正整数$t(1≤t≤1000)$。

接下来有$t$行，每行有一个正整数$n_i(1≤n_i≤10^{18})$，表示在第$i$年中，你可以用于支配的小方块个数。

--------

对于每年输出两行。第一行应包含一个数$m_i$,表示能够收到小方块的家庭的数目。

第二行有$m_i$个整数，代表每个家庭应该收到的小方块的个数。这些整数之和应该等于$n_i$。

---------

时间限制：$2s$

空间限制：$256MB$

翻译提供：@Trexmao


---

---
title: "[NWRRC 2013] Flight Boarding Optimization"
layout: "post"
diff: 普及/提高-
pid: P7084
tag: ['2013', 'ICPC']
---
# [NWRRC 2013] Flight Boarding Optimization
## 题目描述



Peter is an executive boarding manager in Byteland airport. His job is to optimize the boarding process. The planes in Byteland have $s$ rows, numbered from $1$ to $s$ . Every row has six seats, labeled A to $F$ .

![](/upload/images2/flgithseat.png)

There are $n$ passengers, they form a queue and board the plane one by one. If the i-th passenger sits in a row $r_{i}$ then the difficulty of boarding for him is equal to the number of passengers boarded before him and sit in rows $1$ . . . $r_{i}−1$ . The total difficulty of the boarding is the sum of difficulties for all passengers. For example, if there are ten passengers, and their seats are $6A, 4B, 2E, 5F, 2A, 3F, 1C, 10E, 8B, 5A,$ in the queue order, then the difficulties of their boarding are $0 , 0 , 0 , 2 , 0 , 2 , 0 , 7 , 7 , 5$ , and the total difficulty is $23$ .

To optimize the boarding, Peter wants to divide the plane into $k$ zones. Every zone must be a continuous range of rows. Than the boarding process is performed in $k$ phases. On every phase, one zone is selected and passengers whose seats are in this zone are boarding in the order they were in the initial queue. $ $

In the example above, if we divide the plane into two zones: rows $5-10$ and rows $1-4$ , then during the first phase the passengers will take seats $6A, 5F, 10E, 8B, 5A,$ and during the second phase the passengers will take seats $4B, 2E, 2A, 3F, 1C,$ in this order. The total difficulty of the boarding will be $6$ .

Help Peter to find the division of the plane into $k$ zones which minimizes the total difficulty of the boarding, given a specific queue of passengers.


## 输入格式



The first line contains three integers $n (1 \le n \le 1000) , s (1 \le s \le 1000)$ , and $k (1 \le k \le 50$ ; $k \le s)$ . The next line contains $n$ integers $r_{i} (1 \le r_{i} \le s)$ .

Each row is occupied by at most $6$ passengers.


## 输出格式



Output one number, the minimal possible difficulty of the boarding.


## 样例

### 样例输入 #1
```
10 12 2
6 4 2 5 2 3 1 11 8 5

```
### 样例输出 #1
```
6

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

## 题目描述

Peter是 Byteland 机场的高级登机管理人员。他的工作是优化登机流程。Byteland 中的飞机有$s$行，编号从1到$s$。每排有六个座位，标有$A$到$F$。

有$n$名乘客，他们排成一队，一个接一个地登上飞机。如果第$i$位乘客坐在第$r_i$排，那么，他登机的难度等于在他前面登机的并且坐在第1......$r_i$ $-$1排的乘客人数之和。



登机的总难度是所有乘客的登机难度之和。例如，如果有十名乘客，他们的座位分别是$6A、4B、2E、5F、2A、3F、1C、10E、8B、5A$，按照排队顺序排列，那么他们登机的难度分别是$0、0、0、2、0、2、0、7、7、5$，总难度是$23$。

为了优化登机，Peter希望将飞机划分成$k$个区域。每个分区都必须是连续的行数。然后分成$k$段执行登机流程。在每个阶段，选择一个区域，座位在该区域的乘客将按照他们在初始队列中的顺序登机。

在上面的示例中，如果我们将平面划分为两个区域：第 $5-10$ 行和第$1-4$ 行，则在第一阶段，乘客将依次就座$6A、5F、10E、8B、5A$。在第二阶段，乘客将依次就座$4B、2E、2A、3F、1C$。登机的总难度为$6$。

帮助Peter找到将飞机划分为$k$个区域的方法，在给定特定乘客队列的情况下，将登机的总难度降至最低。

## 输入格式

第一行包括三个整数$n(1≤n≤1000)$,$s(1≤s≤1000)$和$k(1≤k≤1000)$

第二行包括$n$个整数$r_i(1≤r_i≤s)$ 



## 输出格式

输出一行一个数，最小的登机总难度


---

---
title: "[CERC2018] The Silence of the Lamps"
layout: "post"
diff: 普及/提高-
pid: P7464
tag: ['2018', 'ICPC']
---
# [CERC2018] The Silence of the Lamps
## 题目描述

**译自[ [CERC2018]](https://contest.felk.cvut.cz/18cerc/) [The Silence of the Lamps](https://contest.felk.cvut.cz/18cerc/solved/lamps.pdf)**

在开始之前，如果之前没有见过台灯，那么现在我们把它看做一个用玻璃做的长方体（一个矩形表面的箱子），里面都是煤气。灯的所有边长度都是整数。

曾经，我们的一位讲师曾因破坏路灯而被判刑。他肯定疯了，因为他认为一些路灯向他高声尖叫。

在他的想法里，他遵从一个奇怪的行为模式。他只会认出并且破坏表面不是正方形，并且体积不超过一个给定数值的路灯。后来，在与医生 Clarice 的一次会谈中，他说他非常害怕大型物体和形状过于规则的物体。

你的任务是数出所有满足讲师条件的可能长方体。
## 输入格式

第一行一个整数 $T$，表示数据组数。

接下来 $T$ 行，每行一个整数 $N$，表示最大可识别的路灯体积。
## 输出格式

对于每组数据，输出会被破坏的不同路灯个数。
## 样例

### 样例输入 #1
```
5
5
6
10
30
666
```
### 样例输出 #1
```
0
1
3
26
2406
```
## 提示

$1≤T≤10^5$，$1≤N≤10^6$。


---

---
title: "[ICPC 2022 Xi'an R] Hotel"
layout: "post"
diff: 普及/提高-
pid: P9363
tag: ['2022', 'O2优化', 'ICPC']
---
# [ICPC 2022 Xi'an R] Hotel
## 题目描述

You are doing volunteer work for a programming competition in an ancient hotel. Unfortunately, the hotel provides no phone signal or tap water since it can be dated back to the Qin Dynasty, and you have to assign the contestants to the hotel rooms manually instead of using the internet apps. Fortunately, the hotel has sufficient rooms, and you have taken a computer that lets you do some computation locally.

There are $n$ teams, each with exactly $3$ contestants. There are $2$ types of rooms in the hotel, the single room and double room, which can receive at most $1$ and $2$ contestants, respectively. To avoid embarrassing contestants, if two contestants are assigned to a double room, they must come from the same team and have the same gender.

The cost of each room of the same type is the same, but different types may have different costs. Your program needs to calculate the minimum price the host has to pay. The teams are waiting in the registration hall now, and the competition finance officer relies on you to save costs and make a fortune by the residual value. Be quick, or the finance officer will sue you for violating his reputation!
## 输入格式

The first line of input contains three integers $n$, $c_1$ and $c_2$ ($1 \leq n, c_1, c_2 \leq 1\,000$), denoting the number of teams, the cost of a single room and a double room respectively.

In the following $n$ lines, each line contains a string $S$ with exactly $3$ uppercase English letters. The letters in a string denote the genders of the contestants in one team and will be represented by $\texttt{A}$ to $\texttt{Z}$, respecting the diversity of human beings.
## 输出格式

The output should contain a single integer, denoting the minimum cost of hotel allocation for contestants.
## 样例

### 样例输入 #1
```
3 1 3
MMM
MMM
FFF

```
### 样例输出 #1
```
9

```
### 样例输入 #2
```
3 3 1
ABC
DEF
GHI

```
### 样例输出 #2
```
9

```
### 样例输入 #3
```
10 438 438
WWW
SOU
PUN
ETC
OME
CFI
NAL
GOO
DHO
TEL

```
### 样例输出 #3
```
12264

```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem F.

**Author**: fstqwq.
## 题目翻译

### 题目描述

你正在一个古代的酒店里为一场编程竞赛做志愿工作。酒店的历史可以追溯到秦朝，所以酒店不提供手机信号和自来水。你无法使用网络软件，不得不手动为参赛者分配房间。幸运的是，酒店拥有充足的房间，并且你有一台电脑帮你做一些计算。

共有 $n$ 个队伍，每个队伍恰有 $3$ 名选手。酒店有两种房间，单人间和双人间，分别可以容纳 $1$ 和 $2$ 名选手。为了避免使选手尴尬，如果两名选手分配到了同一个双人间，他们必须来自同一个队伍，并拥有相同的性别。

相同种类的房间的花费相同，但不同种类的房间花费可能不同。你需要计算主办方最少需要花多少钱。选手们已经在登记厅等候多时，而竞赛财务经理依靠你来节省开支，私吞剩下来的钱发大财。你需要尽快完成任务，否则财务经理将起诉你侵犯了他的名誉权！

$1\leq n, c_1, c_2\leq 1000$。

### 输入格式

第一行三个整数 $n, c_1, c_2$，分别表示队伍数量，单人间单价和双人间单价。

接下来的 $n$ 行，每行一个长度为 $3$ 的字符串 $S$ 表示一个队伍的参赛队员的性别。为了尊重人类的多样性，$S$ 可能包含从 $\texttt A$ 到 $\texttt Z$ 的所有大写字母。

### 输出格式

输出一行一个整数表示分配房间的最小代价。


---

---
title: "[CERC2019] Zeldain Garden"
layout: "post"
diff: 普及/提高-
pid: P9611
tag: ['数学', '2019', 'ICPC']
---
# [CERC2019] Zeldain Garden
## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[Zeldain Garden](https://contest.felk.cvut.cz/19cerc/solved/garden.pdf)」**
## 题目描述

Boris 是 Rock Anywhere Transport（RAT）公司的首席执行官，该公司专门支持音乐产业。特别是，他们为许多流行的摇滚乐队提供折扣运输。这一次，Boris 不得不将大量优质的墨西哥音乐会扬声器从北海港口转移到遥远的内陆首都。由于预计收货量很大，Boris 不得不组织多辆卡车以确保运输顺畅。运送货物通过该国的众多卡车被称为车队。

Boris 希望通过一个车队一次性运输所有货物，一个扬声器都不留下。欧盟的严格规定要求，在大规模运输音频技术设备的情况下，车队中的所有卡车必须携带完全相同数量的设备。

为了满足所有规定，Boris 希望提前做一些计划，尽管他还不知道扬声器的确切数量，这对车队中卡车的数量和容量的选择有很大影响。为了检查各种情况，对于每个可能的容货量，Boris 计算出所谓的“可变性”，即在不违反规定的情况下，可以为该容货量创建的不同车队的数量。如果两个车队由不同数量的卡车组成，那么它们就不同了。

例如，$6$ 个扬声器货物的可变性为 $4$，因为它们可以均匀地分为 $1$、$2$、$3$ 或 $6$ 辆卡车。

### 简要题意

给定 $l,r$，求 $l\sim r$ 中所有数的因数个数之和。
## 输入格式

输入包含一个文本行，包含两个整数 $N, M\ (1\le N\le M\le 10^{12})$，代表扬声器货物的最小和最大数量。
## 输出格式

输出一个整数，代表对于 $N$ 和 $M$ 之间（含）的所有货物量的可变性之和。
## 样例

### 样例输入 #1
```
2 5

```
### 样例输出 #1
```
9

```
### 样例输入 #2
```
12 12

```
### 样例输出 #2
```
6

```
### 样例输入 #3
```
555 666

```
### 样例输出 #3
```
852
```


---

---
title: "[CERC2019] Light Emitting Hindenburg"
layout: "post"
diff: 普及/提高-
pid: P9612
tag: ['贪心', '2019', '位运算', 'ICPC']
---
# [CERC2019] Light Emitting Hindenburg
## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[Light Emitting Hindenburg](https://contest.felk.cvut.cz/19cerc/solved/hindenburg.pdf)」**
## 题目描述

Lothar 正在组织他朋友的摇滚乐队的音乐会巡演。巡演将于 11 月举行，每天最多有一场音乐会。这次巡演将非常具有代表性，许多音乐家都愿意参加。巡演中的音乐家人数是严格规定的，不能改变。巡演中的每一场音乐会都必须有所有参加巡演的音乐家参加。

对 Lothar 来说，好消息是，候选音乐家的数量至少与巡演中规定的音乐家数量一样多。坏消息是，一个典型的音乐家整个月都没有空，而且各种音乐家的日程安排也大不相同。

很久以前，Lothar 编写了一个计算机调度系统的核心，现在他正在利用它来组织这次巡演。他反复地、有点随机地选择一组指定数量的音乐家，并让系统计算出一个可接受的巡演时间表。该系统取决于一种非常具体的数据格式。音乐家的时间表和巡演时间表用数字编码表示。11 月的日子是按月份的数字标记的：$1, 2, \dots, 30$。

对于一个给定的音乐家来说，每年 11 月的一天都会被分配一个特定的数字编码。如果音乐家当天空闲，则标签为 $L$ 的一天由整数 $2^{30-L}$ 编码。否则，日期将由 $0$ 编码。音乐家的时间表编码是他或她的所有日期编码的总和。

对于一组给定的音乐家来说，每年 11 月的一天都会被分配一个特定的数字编码。如果该组中的所有音乐家当天都空闲，标签为 $L$ 的一天由整数 $2^{30-L}$ 编码。否则，日期将由 $0$ 编码。组的空闲编码是该组所有日期编码的总和。

出于许多其他微妙的原因，Lothar 认为最好的巡演应该是任意一组音乐家，这组的空闲编码是可能的最大值。
## 输入格式

第一行包含两个整数 $N, K\ (1\le K\le N\le 2\times 10^5)$。$N$ 是可用音乐家的数量，$K$ 是参加巡演的音乐家的规定数量。

第二行包含一个由 $N$ 个正整数组成的序列。序列中的每个整数表示一个音乐家的时间表编码。编码按任意顺序列出。
## 输出格式

输出一个整数，代表 $K$ 个音乐家的空闲编码值总和的最大值。
## 样例

### 样例输入 #1
```
5 2
6 15 9 666 1

```
### 样例输出 #1
```
10

```
### 样例输入 #2
```
8 4
13 30 27 20 11 30 19 10

```
### 样例输出 #2
```
18

```


---

---
title: "[ICPC 2020 Nanjing R] Evil Coordinate"
layout: "post"
diff: 普及/提高-
pid: P9626
tag: ['2020', 'Special Judge', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] Evil Coordinate
## 题目描述

A robot is standing on an infinite 2-dimensional plane. Programmed with a string $s_1s_2\cdots s_n$ of length $n$, where $s_i \in \{\text{`U'}, \text{`D'}, \text{`L'}, \text{`R'}\}$, the robot will start moving from $(0, 0)$ and will follow the instructions represented by the characters in the string.

More formally, let $(x, y)$ be the current coordinate of the robot. Starting from $(0, 0)$, the robot repeats the following procedure $n$ times. During the $i$-th time:

- If $s_i = \text{`U'}$ the robot moves from $(x, y)$ to $(x, y+1)$;
- If $s_i = \text{`D'}$ the robot moves from $(x, y)$ to $(x, y-1)$;
- If $s_i = \text{`L'}$ the robot moves from $(x, y)$ to $(x-1, y)$;
- If $s_i = \text{`R'}$ the robot moves from $(x, y)$ to $(x+1, y)$.-

However, there is a mine buried under the coordinate $(m_x, m_y)$. If the robot steps onto $(m_x, m_y)$ during its movement, it will be blown up into pieces. Poor robot!

Your task is to rearrange the characters in the string in any order, so that the robot will not step onto $(m_x, m_y)$.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains two integers $m_x$ and $m_y$ ($-10^9 \le m_x, m_y \le 10^9$) indicating the coordinate of the mine.

The second line contains a string $s_1s_2\cdots s_n$ of length $n$ ($1 \le n \le 10^5$, $s_i \in \{\text{`U'}, \text{`D'}, \text{`L'}, \text{`R'}\}$) indicating the string programmed into the robot.

It's guaranteed that the sum of $n$ of all test cases will not exceed $10^6$.
## 输出格式

For each test case output one line. If a valid answer exists print the rearranged string, otherwise print ``Impossible`` instead. If there are multiple valid answers you can print any of them.
## 样例

### 样例输入 #1
```
5
1 1
RURULLD
0 5
UUU
0 3
UUU
0 2
UUU
0 0
UUU

```
### 样例输出 #1
```
LDLRUUR
UUU
Impossible
Impossible
Impossible

```
## 题目翻译

一个机器人位于平面直角坐标系的原点处。给定一串指令，由 `UDLR` 四个字符构成，分别表示向上下左右移动 $1$ 单位长度。

$(m_x, m_y)$ 处埋有地雷，你需要任意重排指令使得机器人不会经过该坐标，判定是否有解并构造方案。

多组数据。指令长度不超过 $10 ^ 5$，长度总和不超过 $10 ^ 6$。


---

---
title: "[ICPC 2020 Nanjing R] Let's Play Curling"
layout: "post"
diff: 普及/提高-
pid: P9633
tag: ['2020', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] Let's Play Curling
## 题目描述

Curling is a sport in which players slide stones on a sheet of ice toward a target area. The team with the nearest stone to the center of the target area wins the game.

Two teams, Red and Blue, are competing on the number axis. After the game there are $(n+m)$ stones remaining on the axis, $n$ of them for the Red team and the other $m$ of them for the Blue. The $i$-th stone of the Red team is positioned at $a_i$ and the $i$-th stone of the Blue team is positioned at $b_i$.

Let $c$ be the position of the center of the target area. From the description above we know that if there exists some $i$ such that $1 \le i \le n$ and for all $1 \le j \le m$ we have $|c - a_i| < |c - b_j|$ then Red wins the game. What's more, Red is declared to win $p$ points if the number of $i$ satisfying the constraint is exactly $p$.

Given the positions of the stones for team Red and Blue, your task is to determine the position $c$ of the center of the target area so that Red wins the game and scores as much as possible. Note that $c$ can be any real number, not necessarily an integer.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($1 \le n, m \le 10^5$) indicating the number of stones for Red and the number of stones for Blue.

The second line contains $n$ integers $a_1, a_2, \cdots, a_n$ ($1 \le a_i \le 10^9$) indicating the positions of the stones for Red.

The third line contains $m$ integers $b_1, b_2, \cdots, b_m$ ($1 \le b_i \le 10^9$) indicating the positions of the stones for Blue.

It's guaranteed that neither the sum of $n$ nor the sum of $m$ will exceed $5 \times 10^5$.
## 输出格式

For each test case output one line. If there exists some $c$ so that Red wins and scores as much as possible, output one integer indicating the maximum possible $\textbf{score}$ of Red (NOT $c$). Otherwise output ``Impossible`` (without quotes) instead.
## 样例

### 样例输入 #1
```
3
2 2
2 3
1 4
6 5
2 5 3 7 1 7
3 4 3 1 10
1 1
7
7
```
### 样例输出 #1
```
2
3
Impossible
```
## 提示

For the first sample test case we can assign $c = 2.5$ so that the stones at position 2 and 3 for Red will score.

For the second sample test case we can assign $c = 7$ so that the stones at position 5 and 7 for Red will score.
## 题目翻译

# [ICPC2020 Nanjing R] Let's Play Curling

## 题目描述

红队和蓝队在冰面上向目标区域滑动冰壶，距离目标区域中心最近的队伍获胜。

两支队伍在一条直线上竞争。比赛结束后，有   $(n+m)$ 个冰壶在直线上, $n$ 个是红队的，剩下 $m$ 个是蓝队的。 红队的第 $i$ 个冰壶被放在 $a_i$ ，蓝队的第 $i$ 个冰壶被放在 $b_i$ 。

设 $c$ 是中心。如果存在一些 $i$ 使得 $1 \le i \le n$ 并且对于所有 $1 \le j \le m$ 都有 $|c - a_i| < |c - b_j|$ 红队就赢得比赛。另外，如果满足条件的 $i$ 的数目是 $p$ ，则认为红队赢得 $p$ 分。

给你红蓝两队的冰壶的位置，请你确定中心 $c$ 的值，使红队得分最多。注意， $c$ 是任意实数，不一定是整数。

## 输入格式

有很多测试样例。第一行输入一个整数 $T$ ，表示样例数量。对于每个测试样列：

第一行包括两个整数 $n$ 和 $m$ ($1 \le n, m \le 10^5$) 分别表示红队和蓝队的冰壶数量。

第二行包括 $n$ 个整数 $a_1, a_2, \cdots, a_n$ ($1 \le a_i \le 10^9$) 表示红队的冰壶的位置。

第三行包括 $m$ 个整数 $b_1, b_2, \cdots, b_m$ ($1 \le b_i \le 10^9$)表示蓝队的冰壶的位置。

数据保证 $n$ 的总和以及 $m$ 的总和都不会超过 $5 \times 10^5$ 。

## 输出格式

每一个测试样列输出一行。如果存在 $c$ 使得红队获胜且得分最多, 输出一个整数表示红队最大 $\textbf{ 得分 }$ (不是 $c$) 。否则输出 ``Impossible`` ( 不带等号 ) 。

## 样例 #1

### 样例输入 #1

```
3
2 2
2 3
1 4
6 5
2 5 3 7 1 7
3 4 3 1 10
1 1
7
7
```

### 样例输出 #1

```
2
3
Impossible
```

## 提示

对于第一个样例，当 $c = 2.5$ 时，红队的位于 2 和 3 的冰壶可以得分。

对于第二个样例，当 $c = 7$ 时，红队的位于 5 和 7 的冰壶可以得分。


---

---
title: "[ICPC 2021 Macao R] Link-Cut Tree"
layout: "post"
diff: 普及/提高-
pid: P9666
tag: ['2021', 'O2优化', '生成树', 'ICPC', '澳门']
---
# [ICPC 2021 Macao R] Link-Cut Tree
## 题目描述

BaoBao just learned how to use a data structure called link-cut tree to find cycles in a graph and decided to give it a try. BaoBao is given an undirected graph with $n$ vertices and $m$ edges, where the length of the $i$-th edge equals $2^i$. She needs to find a simple cycle with the smallest length.

A simple cycle is a subgraph of the original graph containing $k$ ($3 \le k \le n$) vertices $a_1, a_2, \cdots, a_k$ and $k$ edges such that for all $1 \le i \le k$ there is an edge connecting vertices $a_i$ and $a_{(i \mod k) + 1}$ in the subgraph. The length of a simple cycle is the total length of the edges in the cycle.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($3 \le n \le 10^5$, $1 \le m \le 10^5$) indicating the number of vertices and edges in the original graph.

For the following $m$ lines, the $i$-th line contains two integers $u_i$ and $v_i$ ($1 \le u_i, v_i \le n$) indicating an edge connecting vertices $u_i$ and $v_i$ with length $2^i$. There are no self loops nor multiple edges. Note that the graph is not necessarily connected.

It's guaranteed that neither the sum of $n$ nor the sum of $m$ of all test cases will exceed $10^6$.
## 输出格式

For each test case output one line. If there are no simple cycles in the graph output ``-1`` (without quotes); Otherwise output $k$ integers separated by a space in increasing order indicating the indices of the edges in the simple cycle with the smallest length. It can be shown that there is at most one answer.

Please, DO NOT output extra spaces at the end of each line, or your solution may be considered incorrect!
## 样例

### 样例输入 #1
```
2
6 8
1 2
2 3
5 6
3 4
2 5
5 4
5 1
4 2
4 2
1 2
4 3
```
### 样例输出 #1
```
2 4 5 6
-1
```
## 提示

The first sample test case is shown below. The integers beside the edges are their indices (outside the parentheses) and lengths (inside the parentheses). The simple cycle with the smallest length consists of edges $2$, $4$, $5$ and $6$ with a length of $2^2 + 2^4 + 2^5 + 2^6 = 116$.
## 题目翻译


BaoBao刚学会如何用一种叫做 LCT 的数据结构去找图中的环，因此决定试一试。BaoBao 得到一个有 $n$ 个点，$m$    条边的无向图，其中第 $i$ 条边的权值为 $2^i$。她需要找到一个权值最小的环。

环是原图的子图，包含 $k$ ($3 \le k \le n$) 个点 $a_1, a_2, \cdots, a_k$ 和 $k$ 条边，使得对于所有的 $1 \le i \le k$ ，子图中存在边连接点 $a_i$ 和 $a_{(i \mod k) + 1}$ 。环的权值为环上所有边的权值之和。

每一个测试点有多组测试数据。 第一行有一个整数 $T$ 表示数据组数。

第二行有两个整数 $n$ 和 $m$ ($3 \le n \le 10^5$, $1 \le m \le 10^5$)，分别为点数和边数。

接下来 $m$ 行， 第 $i$ 行包括两个整数 $u_i$ 和 $v_i$ ($1 \le u_i, v_i \le n$) 表示有一条边连接 $u_i$ 和 $v_i$ ，权值为 $2^i$。 请注意，图 **不一定** 连通。

保证所有测试样例 $n$ 之和， $m$ 之和均不超过 $10^6$.

对每一组测试数据输出一行。如果图中没有环，输出 ``-1`` 。 否则 **升序** 输出边的编号，共 $k$ 个整数 ， 显然答案唯一。

第一个测试样例如图，图中标注出的为边的编号，环 $2$, $4$, $5$, $6$ 边权为 $2^2 + 2^4 + 2^5 + 2^6 = 116$，为最小环。

![](https://cdn.luogu.com.cn/upload/image_hosting/vqpea23u.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


---

---
title: "[ICPC 2022 Jinan R] Identical Parity"
layout: "post"
diff: 普及/提高-
pid: P9671
tag: ['2022', 'Special Judge', 'O2优化', 'ICPC', '济南']
---
# [ICPC 2022 Jinan R] Identical Parity
## 题目描述

Let the value of a sequence be the sum of all numbers in it.

Determine whether there exists a permutation of length $n$ such that the values of all subsegments of length $k$ of the permutation share the same parity. The values share the same parity means that they are all odd numbers or they are all even numbers.

A subsegment of a permutation is a contiguous subsequence of that permutation. A permutation of length $n$ is a sequence in which each integer from $1$ to $n$ appears exactly once.
## 输入格式

The first line contains one integer $T~(1\le T \le 10^5)$, the number of test cases.

For each test case, the only line contains two integers $n,k~(1 \le k \le n \le 10^9)$.
## 输出格式

For each test case, output $\texttt{Yes}$ (without quotes) if there exists a valid permutation, or $\texttt{No}$ (without quotes) otherwise.

You can output $\texttt{Yes}$ and $\texttt{No}$ in any case (for example, strings $\texttt{YES}$, $\texttt{yEs}$ and $\texttt{yes}$ will be recognized as positive responses).
## 样例

### 样例输入 #1
```
3
3 1
4 2
5 3
```
### 样例输出 #1
```
No
Yes
Yes
```
## 提示

In the first test case, it can be shown that there does not exist any valid permutation.

In the second test case, $[1,2,3,4]$ is one of the valid permutations. Its subsegments of length $2$ are $[1,2],[2,3],[3,4]$. Their values are $3,5,7$, respectively. They share the same parity.

In the third test case, $[1,2,3,5,4]$ is one of the valid permutations. Its subsegments of length $3$ are $[1,2,3],[2,3,5],[3,5,4]$. Their values are $6,10,12$, respectively. They share the same parity.
## 题目翻译

### 题目描述

定义一个序列的 **权值** 等于这个序列所有的元素之和。

试判断：是否存在一个长度为 $n$ 的 **排列**，满足以下约束条件？

- 其所有长度为 $k$ 的 **子区间** 的权值具有相同的奇偶性。

### 输入格式

第一行一个整数 $T$ $(1\leqslant T\leqslant 10^5)$，表示测试数据组数。

对于每组测试数据，仅有一行两个整数 $n,k$ $(1\leqslant k\leqslant n\leqslant 10^9)$，含义见“题目描述”。

### 输出格式

对于每组测试数据，输出一行一个字符串。若存在符合题意的排列，输出 $\texttt{Yes}$；否则，输出 $\texttt{No}$。

你可以以任意的大小写输出 $\texttt{Yes}$ 和 $\texttt{No}$（例如，$\texttt{YES}$，$\texttt{yEs}$ 和 $\texttt{yes}$ 都会被视作合法的输出）。

### 样例解释

对于第一组测试数据，能够证明不存在任何符合题意的排列。

对于第二组测试数据，$[1,2,3,4]$ 是一个符合题意的排列。其所有长度为 $2$ 的子区间分别为 $[1,2],[2,3],[3,4]$，它们的权值分别为 $3,5,7$，具有相同的奇偶性。

对于第三组测试数据，$[1,2,3,5,4]$ 是一个符合题意的排列。其所有长度为 $3$ 的子区间分别为 $[1,2,3],[2,3,5],[3,5,4]$，它们的权值分别为 $6,10,12$，具有相同的奇偶性。


---

---
title: "[ICPC 2022 Jinan R] Best Carry Player"
layout: "post"
diff: 普及/提高-
pid: P9679
tag: ['2022', 'O2优化', 'ICPC', '济南']
---
# [ICPC 2022 Jinan R] Best Carry Player
## 题目描述

Prof. Pang is given $n$ numbers $a_1,\ldots, a_n$. It is easy to add the numbers up using a computer. But Prof. Pang treasures his computer so much and wants to reduce its workload. He decides to simulate the following program by hand. 

![](https://cdn.luogu.com.cn/upload/image_hosting/ajtj92in.png)


Unlike a computer, the time needed for Prof. Pang to simulate the program is proportional to the total number of **carries**(which means “进位” in Chinese) when calculating $s+a[i]$ for each $i$ from $1$ to $n$. Prof. Pang adds numbers **by column addition in base-ten**, just like what we normally do in primary school. For example, there are two carries in the following addition.

![](https://cdn.luogu.com.cn/upload/image_hosting/c779jeox.png)

Please permute the array $a_1,\ldots, a_n$ so that the total number of carries when Prof. Pang simulates the program is as small as possible. (By ''permute an array'', we mean that you can change the order of the elements arbitrarily.)

## 输入格式

The first line contains one integer $T~(1\le T \le 10^5)$, the number of test cases.

For each test case, the first line contains one positive integer $n~(1\le n \le 10^5)$. The next line contains $n$ integers $a_1,\ldots, a_n~(1 \le a_i\le 10^9)$ denoting the numbers Prof. Pang is given. 

It is guaranteed that the sum of $n$ over all test cases is no more than $10^5$.
## 输出格式

For each test case, output one line containing the minimum amount of carries.
## 样例

### 样例输入 #1
```
2
3
9 99 999
1
12345
```
### 样例输出 #1
```
5
0
```
## 题目翻译

### 简要题面

这里我们定义一个电脑运行 $a+b$ 的速度是 $a+b$ 中出现的进位的次数。

给定一个数组 $a_1,a_2,...,a_n$，请找出正确的排序使得计算这个数组的和时运行的速度最短，请找出最少的进位次数。

### 输入格式

**本题有多组数据**。

第一行一个整数 $T$，表示数据组数。

对于每组数据：

第一行一个整数 $n$。  

接下来一行 $n$ 个整数，表示输入的数组 $a$。

### 输出格式

对于每组数据，输出最小的进位次数。

### 数据范围

对于 $100 \%$ 的数据： $1 \leq \sum n \leq 10^5$， $1 \leq a_i \leq 10^9$


---

---
title: "[EC Final 2022] Dining Professors"
layout: "post"
diff: 普及/提高-
pid: P9728
tag: ['贪心', '2022', 'O2优化', 'ICPC']
---
# [EC Final 2022] Dining Professors
## 题目描述

Prof. Pang invited $n$ professors to his banquet. The professors sit at a round table. For all $i$ from $1$ to $n$, professor $i$ sits adjacent to professor $(i \bmod n) + 1$ and $((i + n - 2)\bmod n) + 1$.

Prof. Pang prepared $n$ dishes. There are $n$ positions on the table. Position $i$ is in front of professor $i$. Professor $i$ can access only the dishes placed at positions $i$, $(i \bmod n) + 1$, and $((i + n - 2)\bmod n) + 1$. Prof. Pang will place exactly one dish at each position.

Among the dishes, $a$ of them are spicy and $n-a$ of them are not spicy. Some (possibly $0$) professors are unable to have spicy food. If a professor can have spicy food, his/her **satisfaction level** is the number of dishes (no matter spicy or not) he/she can access. If a professor cannot have spicy food, his/her satisfaction level is the number of not spicy dishes he/she can access.

Prof. Pang knows whether each professor can have spicy food or not. Please help him to arrange the dishes on the table so that the sum of satisfaction levels over all the professors is maximized. Output the maximum sum.
## 输入格式

The first line contains two integers $n, a$ ($3\le n\le 10^5, 0\le a\le n$). 

The second line contains $n$ integers $b_1, \ldots, b_n$. $b_i$ is $0$ or $1$. $b_i=1$ means professor $i$ can have spicy food. $b_i=0$ means professor $i$ cannot have spicy food.
## 输出格式

Output one integer representing the answer in one line.
## 样例

### 样例输入 #1
```
5 2
1 0 1 0 1

```
### 样例输出 #1
```
13

```
## 题目翻译

**【题目描述】**

庞教授邀请了 $n$ 位教授参加他的宴会。教授们坐在一个圆桌周围。对于所有 $i$，从 $1$ 到 $n$，教授 $i$ 坐在教授 $(i \bmod n) + 1$ 和 $((i + n - 2)\bmod n) + 1$ 旁边。

庞教授准备了 $n$ 道菜。桌子上有 $n$ 个位置。位置 $i$ 在教授 $i$ 的前面。教授 $i$ 只能接触到放在位置 $i$、$(i \bmod n) + 1$ 和 $((i + n - 2)\bmod n) + 1$ 处的菜。庞教授将在每个位置上放置一道菜。

在这些菜中，有 $a$ 道是辣的，$n-a$ 道是不辣的。有些（可能为 $0$）教授不能吃辣的食物。如果一位教授可以吃辣的食物，他/她的**满意度水平**是他/她可以接触到的菜的数量（无论是辣的还是不辣的）。如果一位教授不能吃辣的食物，他/她的满意度水平是他/她可以接触到的不辣的菜的数量。

庞教授知道每位教授是否可以吃辣的食物。请帮助他安排桌子上的菜，使得所有教授的满意度水平之和最大化。输出最大的总和。

**【输入格式】**

第一行包含两个整数 $n, a$ ($3\le n\le 10^5, 0\le a\le n$)。

第二行包含 $n$ 个整数 $b_1, \ldots, b_n$。$b_i$ 是 $0$ 或 $1$。$b_i=1$ 表示教授 $i$ 可以吃辣的食物。$b_i=0$ 表示教授 $i$ 不能吃辣的食物。

**【输出格式】**

输出一行一个整数，表示答案。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "[NERC 2018] Lazyland"
layout: "post"
diff: 普及/提高-
pid: P9802
tag: ['2018', 'ICPC']
---
# [NERC 2018] Lazyland
## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) L 题。
## 题目描述

一个城市里有 $n$ 个人，和 $k$ 种职业，其中，每个人都有一个现在正在从事的职业 $a_i$，但是很遗憾，由于某些职业的空缺，使得这个城市根本无法继续正常生存下去。

你作为一城之主，自然不希望看到自己的城市这样子下去，你决定说服其中的某些人，使得每种职业都有人在做，对于每个人 $i$，你需要耗费 $b_i$ 的时间去说服。

你需要求出你去说服的时间的最小值。
## 输入格式

第一行两个整数 $n$ 和 $k (1 \leq k \leq n \leq 10^5)$，分别表示 $n$ 个人和 $k$ 种职业。

第二行 $n$ 个整数 $a_i (1 \leq a_i \leq k)$，表示第 $i$ 个人正在从事的职业 。

第三行 $n$ 个整数 $b_i (1 \leq b_i \leq 10^9)$，表示第 $i$ 个人被说服去做别的职业的时间。
## 输出格式

输出去说服市民的最小时间。
## 样例

### 样例输入 #1
```
8 7
1 1 3 1 5 3 7 1
5 7 4 8 1 3 5 2
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
3 3
3 1 2
5 3 4
```
### 样例输出 #2
```
0
```
## 提示

对于所有的数据，保证 $1 \leq k \leq n \leq 10^5$，$1 \leq a_i \leq k$，$1 \leq b_i \leq 10^9$。

对于样例一，分别令 $1$，$6$，$8$ 号市民去从事 $2$，$4$，$6$ 号职业。


---

---
title: "[ICPC 2020 Shanghai R] Walker"
layout: "post"
diff: 普及/提高-
pid: P9822
tag: ['数学', '2020', '二分', '上海', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2020 Shanghai R] Walker
## 题目描述

As a world-famous traveler, Prof. Pang's research interest is to travel as many places as possible in his life.

We have a segment $[0, n]$. There are two travelers on it. The first one is on position $p_1$ with velocity $v_1$ (which means s/he can walk $v_1$ unit on the segment per second). The second one is on position $p_2$ with velocity $v_2$.

From their respective beginning points, travelers can walk on the segment. They cannot walk outside the segment. Whenever they want to change their direction, they can turn around immediately.

Please help Prof. Pang to calculate the minimum  possible time by which every position of the segment is passed by at least one traveler.
## 输入格式

The first line contains one integer $test~(1\le test\le 10000)$ -- the number of test cases.

The $i$-th of the next $test$ lines contains five numbers $n, p_{1, i}, v_{1, i}, p_{2, i}, v_{2, i}$ ($0 < n \le 10000$, $0\le p_{1, i},p_{2, i} \le n$, $0.001 \le v_{1, i},v_{2, i} \le 1000$). All numbers have at most $3$ digits after the decimal point.
## 输出格式

For each test case, we should output one number -- the minimum time that every position of the segment is passed by at least one traveler.

Your answer is considered correct if its absolute or relative error does not exceed $10^{-6}$.
## 样例

### 样例输入 #1
```
2
10000.0 1.0 0.001 9999.0 0.001
4306.063 4079.874 0.607 1033.423 0.847
```
### 样例输出 #1
```
5001000.0000000000
3827.8370013755
```
## 题目翻译

作为著名的旅行者，Prof. Pang 的研究兴趣是在一生中到尽可能多的地方旅游。

在一条 $[0,n]$ 的线段上有两名旅行者，第一名在位置 $p_1$ 以 $v_1$ （每秒钟可以走 $v_1$ 单位的距离）的速度开始运动，第二名在位置 $p_2$ 以 $v_2$ 的速度开始运动。

从他们分别的起始点出发，旅行者可以在线段上移动，但不可以走出线段。他们可以随时改变自己的方向。

请帮助 Prof. Pang 计算至少需要多少时间，线段上的每个位置都至少被一名旅行者经过。


---

---
title: "[ICPC 2020 Shanghai R] Gitignore"
layout: "post"
diff: 普及/提高-
pid: P9831
tag: ['2020', '上海', 'O2优化', 'ICPC']
---
# [ICPC 2020 Shanghai R] Gitignore
## 题目描述

Your git project (you don't need to be familiar with git to solve this problem) has some files that should be ignored from synchronizing. You need to calculate the minimum number of lines needed for gitignore.

Formally, your project is a folder. A folder can have files and sub folders. There are no empty folders (i.e. folders without any files or sub folders inside). Initially, the git software will synchronize all the files in your project. However, you can specify some files and folders in the settings (which is called gitignore) to exclude them from synchronizing. For each line in gitignore, you can specify either a file or all the files in a folder. You can $\textbf{not}$  ignore the whole project folder (i.e. an empty line in gitignore).

You are given paths for all the files in the project and whether they should be ignored or shouldn't. Your task is to calculate the minimum number of lines for gitignore.
## 输入格式

The input contains several test cases. The first line contains a single positive integer $T$ which is the number of test cases. For each test case, you are first given two non-negative numbers $n$ and $m$. And then $n$ non-empty lines of file paths that should be $\textbf{ignored}$, and $m$ non-empty lines of file paths that should $\textbf{not}$ be ignored.

The paths are strings containing lower-cased English alphabets and slashes (`/`) only. Slashes are used to separate folders, sub folders and file name. For exapmle, ``a/b/c/d`` indicates folder ``a`` in the project folder, folder ``b`` in folder ``a``, folder ``c`` in ``b`` and file ``d`` in folder ``c``. All the paths are valid, specifically:

- The path is non-empty and it always indicates a file (i.e. the path does not end with a slash).
- The path does not start with a slash.
- Folder names and file names are non-empty (i.e. there are no consecutive slashes).
- File paths are always unique (i.e. all the paths in a test case are different).
- In a folder, no sub folders and files share the same names. For example, there won't be two files ``a/b/a`` and ``a/b/a/d`` in one test case. However, files ``a/b/a`` and ``a/b/b`` are allowed.

$1\leq n+m\leq 100$ holds and in the whole input there are no more than $1,000$ characters in file paths (i.e. the sum of lengths of file path strings in the whole input file is no more than $1,000$).
## 输出格式

$T$ lines of non-negative integers, the minimum number of gitignore lines for each test case.
## 样例

### 样例输入 #1
```
2
3 0
data/train
data/test
model
3 1
data/train
data/test
model
data/sample
```
### 样例输出 #1
```
2
3
```
## 提示

In the first sample test case, the corresponding gitignore file contains $2$ lines: a folder line ``data/`` and a file name ``model``.

In the second sample test case, the corresponding gitignore file contains $3$ file lines: ``data/train``, ``data/test`` and ``model``.
## 题目翻译

你使用 git 管理的一个项目有一些需要被忽略的文件。你需要计算 .gitignore 文件中至少写入多少行。

详细来说，你的项目是一个文件夹，文件夹可以含有文件或子文件夹。在本题中，不会出现空文件夹（不含文件或子文件夹的文件夹）。git 软件会同步你项目中所有的文件，但是，你可以在 .gitignore 中写入一些信息，使某些文件或文件夹不被同步。在 .gitignore 文件中的一行，你可以指定一个文件或者一个文件夹，使得这个文件或这个文件夹中的所有文件不被同步。**你不可以忽略整个项目文件夹。**

你会得到项目中所有文件的路径，以及他们是否应该被同步，你的任务是计算 .gitignore 文件中最少的行数。


---

---
title: "[ICPC 2021 Nanjing R] Klee in Solitary Confinement"
layout: "post"
diff: 普及/提高-
pid: P9842
tag: ['2021', 'Special Judge', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Klee in Solitary Confinement
## 题目描述

Since the traveler comes, People in Monstadt suddenly raise great interest in computer programming and algorithms, including Klee, the Spark Knight of the Knights of Favonius.

![](https://cdn.luogu.com.cn/upload/image_hosting/xcnn0v4q.png)

Being sent to solitary confinement by Jean again, Klee decides to spend time learning the famous Mo's algorithm, which can compute with a time complexity of $\mathcal{O}(n^{1.5})$ for some range query problem without modifications.

To check whether Klee has truly mastered the algorithm (or in fact making another bombs secretly), Jean gives her a problem of an integer sequence $a_1, a_2, \cdots, a_n$ along with some queries $[l_i, r_i]$ requiring her to find the mode number in the contiguous subsequence $a_{l_i}, a_{l_i + 1}, \cdots, a_{r_i}$. The mode number is the most common number (that is to say, the number which appears the maximum number of times) in the subsequence.

With the help of Mo's algorithm, Klee solves that problem without effort, but another problem comes into her mind. Given an integer sequence $a_1, a_2, \cdots, a_n$ of length $n$ and an integer $k$, you can perform the following operation at most once: Choose two integers $l$ and $r$ such that $1 \le l \le r \le n$ and add $k$ to every $a_i$ where $l \le i \le r$. Note that it is OK not to perform this operation. Compute the maximum occurrence of the mode number of the whole sequence if you choose to perform (or not perform) the operation optimally.
## 输入格式

There is only one test case in each test file.

The first line of the input contains two integers $n$ and $k$ ($1 \le n \le 10^6$, $-10^6 \le k \le 10^6$) indicating the length of the sequence and the additive number.

The second line of the input contains $n$ integers $a_1, a_2, \cdots, a_n$ ($-10^6 \le a_i \le 10^6$) indicating the original sequence.
## 输出格式

Output one line containing one integer indicating the maximum occurrence of the mode number of the whole sequence after performing (or not performing) the operation.
## 样例

### 样例输入 #1
```
5 2
2 2 4 4 4

```
### 样例输出 #1
```
5

```
### 样例输入 #2
```
7 1
3 2 3 2 2 2 3

```
### 样例输出 #2
```
6

```
### 样例输入 #3
```
7 1
2 3 2 3 2 3 3

```
### 样例输出 #3
```
5

```
### 样例输入 #4
```
9 -100
-1 -2 1 2 -1 -2 1 -2 1

```
### 样例输出 #4
```
3

```
## 提示

For the first sample test case, choose $l = 1$ and $r = 2$ and we'll result in the sequence $\{4, 4, 4, 4, 4\}$. The mode number is obviously $4$ which appears $5$ times.

For the second sample test case, choose $l = 4$ and $r = 6$ and we'll result in the sequence $\{3, 2, 3, 3, 3, 3, 3\}$. The mode number is $3$ which appears $6$ times.

For the fourth sample test case, choose not to perform the operation. The mode number is $1$ and $-2$ which both appear $3$ times.
## 题目翻译

给定 $n,k$ 和一个长为 $n$ 的序列，你可以选择对区间 $[l, r]$ 的数整体加上 $k$，也可以不加。最大化众数出现次数并输出。


---

---
title: "[ICPC 2021 Nanjing R] Windblume Festival"
layout: "post"
diff: 普及/提高-
pid: P9852
tag: ['2021', 'Special Judge', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Windblume Festival
## 题目描述

The Windblume Festival in Mondstadt is coming! People are preparing windblumes for Barbatos and for those they love and adore. The Windblume Festival is also an opportunity to improve the relationships people have.

![](https://cdn.luogu.com.cn/upload/image_hosting/nbhhi3bg.png)

During the festival, a famous game will be played every year, invented by Jean, the Acting Grand Master of the Knights of Favonius. In the game, $n$ players numbered from $1$ to $n$ stand in a circle, each holding an integer with them. Each turn, one player will be removed. The game will end when there is only one player left.

For each turn, let $k$ be the number of players remaining and $a_i$ be the integer player $i$ holds. Two adjacent players, $x$ and $(x \bmod k + 1)$ are selected and player $(x \bmod k + 1)$ is removed from the game. Player $x$'s integer will then change from $a_x$ to $(a_x - a_{x \bmod k + 1})$. Player $y$ in this turn will become player $(y - 1)$ in the next turn for all $x < y \le k$, though the integer they hold will not change.

Jean wants to know the maximum possible integer held by the last remaining player in the game by selecting the players in each round optimally.
## 输入格式

There are multiple test cases. The first line of the input contains one integer $T$ indicating the number of test cases. For each test case:

The first line contains one integer $n$ ($1 \le n \le 10^6$) indicating the initial number of players.

The next line contains $n$ integers $a_i$ ($-10^9 \le a_i \le 10^9$) where $a_i$ is the integer held by player $i$ at the beginning.

It is guaranteed that the sum of $n$ of all test cases will not exceed $10^6$.
## 输出格式

For each test case output one line containing one integer indicating the maximum possible integer.
## 样例

### 样例输入 #1
```
5
4
1 -3 2 -4
11
91 66 73 71 32 83 72 79 84 33 93
12
91 66 73 71 32 83 72 79 84 33 33 93
13
91 66 73 71 32 83 72 79 84 33 33 33 93
1
0

```
### 样例输出 #1
```
10
713
746
779
0

```
## 提示

For the first sample test case follow the strategy shown below, where the underlined integers are the integers held by the players selected in each turn.

$\{\underline{1}, -3, 2, \underline{-4}\}$ (select $x = 4$) $\to$ $\{-3, \underline{2, -5}\}$ (select $x = 2$) $\to$ $\{\underline{-3, 7}\}$ (select $x = 2$) $\to$ $\{10\}$.
## 题目翻译

给一个长度为 $n$ 环形整数序列 $a$, 每次操作可以任意选择一个下标 $x$，令 $ a_x = a_x - a_{(x\bmod n)+1}$，之后移除 $a_{(x\bmod n)+1}$。
  
最后会剩下一个元素，要求最大化这个元素。

数据范围 $1\le n\le10^6,-10^9\le a_i\le 10^9$。


---

---
title: "[ICPC 2018 Qingdao R] Flippy Sequence"
layout: "post"
diff: 普及/提高-
pid: P9887
tag: ['2018', 'O2优化', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Flippy Sequence
## 题目描述

DreamGrid has just found two binary sequences $s_1, s_2, \dots, s_n$ and $t_1, t_2, \dots, t_n$ ($s_i, t_i \in \{0, 1\}$ for all $1 \le i \le n$) from his virtual machine! He would like to perform the operation described below exactly twice, so that $s_i = t_i$ holds for all $1 \le i \le n$ after the two operations.

The operation is: Select two integers $l$ and $r$ ($1 \le l \le r \le n$), change $s_i$ to $(1 - s_i)$ for all $l \le i \le r$.

DreamGrid would like to know the number of ways to do so.

We use the following rules to determine whether two ways are different:

- Let $A = (a_1, a_2, a_3, a_4)$, where $1 \le a_1 \le a_2 \le n, 1 \le a_3 \le a_4 \le n$, be a valid operation pair denoting that DreamGrid selects integers $a_1$ and $a_2$ for the first operation and integers $a_3$ and $a_4$ for the second operation;
- Let $B = (b_1, b_2, b_3, b_4)$, where $1 \le b_1 \le b_2 \le n, 1 \le b_3 \le b_4 \le n$, be another valid operation pair denoting that DreamGrid selects integers $b_1$ and $b_2$ for the first operation and integers $b_3$ and $b_4$ for the second operation.
- $A$ and $B$ are considered different, if there exists an integer $k$ ($1 \le k \le 4$) such that $a_k \ne b_k$.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 10^6$), indicating the length of two binary sequences.

The second line contains a string $s_1s_2\dots s_n$ ($s_i \in \{\text{`0'}, \text{`1'}\}$) of length $n$, indicating the first binary sequence.

The third line contains a string $t_1t_2\dots t_n$ ($t_i \in \{\text{`0'}, \text{`1'}\}$) of length $n$, indicating the second binary sequence.

It's guaranteed that the sum of $n$ in all test cases will not exceed $10^7$.
## 输出格式

For each test case, output an integer denoting the answer.
## 样例

### 样例输入 #1
```
3
1
1
0
2
00
11
5
01010
00111
```
### 样例输出 #1
```
0
2
6
```
## 提示

For the second sample test case, there are two valid operation pairs: $(1, 1, 2, 2)$ and $(2, 2, 1, 1)$.

For the third sample test case, there are six valid operation pairs: $(2, 3, 5, 5)$, $(5, 5, 2, 3)$, $(2, 5, 4, 4)$, $(4, 4, 2, 5)$, $(2, 4, 4, 5)$ and $(4, 5, 2, 4)$.
## 题目翻译

给定两个长度为 $n$ 的 **01** 字符串 $s,\,t$。你需要求出有多少个 $1 \le l_1 \le r_1 \le n,\, 1 \le l_2 \le r_2 \le n$，使得分别**取反** $s$ 串的区间 $[l_1,\,r_1]$ 和区间 $[l_2,\,r_2]$ 内的字符串后，$s$ 和 $t$ 相等。取反的定义是对于 01 字符串 $a$，若 $a_i = 0$ 则令 $a_i \leftarrow 1$，否则令 $a_i \leftarrow 0$。

$1\leq n\leq 10 ^ 6$，$\sum n\leq 10 ^ 7$。


---

---
title: "[ICPC 2018 Qingdao R] Books"
layout: "post"
diff: 普及/提高-
pid: P9894
tag: ['2018', 'O2优化', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Books
## 题目描述

DreamGrid went to the bookshop yesterday. There are $n$ books in the bookshop in total. Because DreamGrid is very rich, he bought the books according to the strategy below:

- Check the $n$ books from the 1st one to the $n$-th one **in order**.
- For each book being checked now, if DreamGrid has enough money (not less than the book price), he'll buy the book and his money will be reduced by the price of the book.
- In case that his money is less than the price of the book being checked now, he will skip that book.


BaoBao is curious about how rich DreamGrid is. You are asked to tell him the maximum possible amount of money DreamGrid took before buying the books, which is a non-negative integer. All he knows are the prices of the $n$ books and the number of books DreamGrid bought in total,  indicated  by $m$. 

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($1 \le n \le 10^5$, $0 \le m \le n$), indicating the number of books in the bookshop and the number of books DreamGrid bought in total.

The second line contains $n$ non-negative integers $a_1, a_2, ... , a_n$ ($0 \le a_i \le 10^9$), where $a_i$ indicates the price of the $i$-th book checked by DreamGrid.

It's guaranteed that the sum of $n$ in all test cases will not exceed $10^6$.
## 输出格式

For each test case output one line.

If it's impossible to buy $m$ books for any initial number of money, output ``Impossible'' (without quotes).

If DreamGrid may take an infinite amount of money, output ``Richman'' (without quotes).

In other cases, output a non-negative integer, indicating the maximum number of money he may take.

## 样例

### 样例输入 #1
```
4
4 2
1 2 4 8
4 0
100 99 98 97
2 2
10000 10000
5 3
0 0 0 0 1
```
### 样例输出 #1
```
6
96
Richman
Impossible
```
## 题目翻译

共有 $n$ 本书，第 $i$ 本书的价格为 $a_i$。买书的策略为：按编号顺序从小到大遍历每本书，若书的价格不超过剩余钱数，则购买，否则跳过。

问初始最多有多少钱能恰好买 $m$ 本书。若初始可以有无穷多的钱，则输出 `Richman`。若不能恰好买 $m$ 本数，则输出 `Impossible`。

多组测试数据。

$1\leq n\leq 10 ^ 5$，$0\leq m\leq n$，$0\leq a_i\leq 10 ^ 9$，$\sum n\leq 10 ^ 6$。


---

