---
title: "Polycarp and Div 3"
layout: "post"
diff: 普及/提高-
pid: CF1005D
tag: ['字符串', '贪心', '前缀和']
---

# Polycarp and Div 3

## 题目描述

Polycarp likes numbers that are divisible by 3.

He has a huge number $ s $ . Polycarp wants to cut from it the maximum number of numbers that are divisible by $ 3 $ . To do this, he makes an arbitrary number of vertical cuts between pairs of adjacent digits. As a result, after $ m $ such cuts, there will be $ m+1 $ parts in total. Polycarp analyzes each of the obtained numbers and finds the number of those that are divisible by $ 3 $ .

For example, if the original number is $ s=3121 $ , then Polycarp can cut it into three parts with two cuts: $ 3|1|21 $ . As a result, he will get two numbers that are divisible by $ 3 $ .

Polycarp can make an arbitrary number of vertical cuts, where each cut is made between a pair of adjacent digits. The resulting numbers cannot contain extra leading zeroes (that is, the number can begin with 0 if and only if this number is exactly one character '0'). For example, 007, 01 and 00099 are not valid numbers, but 90, 0 and 10001 are valid.

What is the maximum number of numbers divisible by $ 3 $ that Polycarp can obtain?

## 输入格式

The first line of the input contains a positive integer $ s $ . The number of digits of the number $ s $ is between $ 1 $ and $ 2\cdot10^5 $ , inclusive. The first (leftmost) digit is not equal to 0.

## 输出格式

Print the maximum number of numbers divisible by $ 3 $ that Polycarp can get by making vertical cuts in the given number $ s $ .

## 说明/提示

In the first example, an example set of optimal cuts on the number is 3|1|21.

In the second example, you do not need to make any cuts. The specified number 6 forms one number that is divisible by $ 3 $ .

In the third example, cuts must be made between each pair of digits. As a result, Polycarp gets one digit 1 and $ 33 $ digits 0. Each of the $ 33 $ digits 0 forms a number that is divisible by $ 3 $ .

In the fourth example, an example set of optimal cuts is 2|0|1|9|201|81. The numbers $ 0 $ , $ 9 $ , $ 201 $ and $ 81 $ are divisible by $ 3 $ .

## 样例 #1

### 输入

```
3121

```

### 输出

```
2

```

## 样例 #2

### 输入

```
6

```

### 输出

```
1

```

## 样例 #3

### 输入

```
1000000000000000000000000000000000

```

### 输出

```
33

```

## 样例 #4

### 输入

```
201920181

```

### 输出

```
4

```



---

---
title: "Minimum Ternary String"
layout: "post"
diff: 普及/提高-
pid: CF1009B
tag: ['字符串', '贪心', '概率论']
---

# Minimum Ternary String

## 题目描述

给定一个由 '0', '1', '2' 组成的字符串  $S$ 。可以交换相邻'0', '1'或'1', '2'的位置（例如：'12' - '21'  $\;$  '01' - '10'）请输出原字符串经过任意转换后字典序最小的字符串。原字符串长度不超过  $10^5$ 。

## 输入格式

字符串  $S$

## 输出格式

转化后字典序最小的字符串

Translated by @ZCDHJ

## 样例 #1

### 输入

```
100210

```

### 输出

```
001120

```

## 样例 #2

### 输入

```
11222121

```

### 输出

```
11112222

```

## 样例 #3

### 输入

```
20

```

### 输出

```
20

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
title: "Bracket Subsequence"
layout: "post"
diff: 普及/提高-
pid: CF1023C
tag: ['字符串', '贪心', '枚举']
---

# Bracket Subsequence

## 题目描述

A bracket sequence is a string containing only characters "(" and ")". A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example, bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)"), and ")(", "(" and ")" are not.

Subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

You are given a regular bracket sequence $ s $ and an integer number $ k $ . Your task is to find a regular bracket sequence of length exactly $ k $ such that it is also a subsequence of $ s $ .

It is guaranteed that such sequence always exists.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2 \le k \le n \le 2 \cdot 10^5 $ , both $ n $ and $ k $ are even) — the length of $ s $ and the length of the sequence you are asked to find.

The second line is a string $ s $ — regular bracket sequence of length $ n $ .

## 输出格式

Print a single string — a regular bracket sequence of length exactly $ k $ such that it is also a subsequence of $ s $ .

It is guaranteed that such sequence always exists.

## 样例 #1

### 输入

```
6 4
()(())

```

### 输出

```
()()

```

## 样例 #2

### 输入

```
8 8
(()(()))

```

### 输出

```
(()(()))

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
title: "Maximal Intersection"
layout: "post"
diff: 普及/提高-
pid: CF1029C
tag: ['贪心', '枚举', '优先队列']
---

# Maximal Intersection

## 题目描述

给定n个闭区间,现在要求从这些闭区间中删除一个区间，使得剩下的（n-1）个区间的交集的长度最大，求这个最大值。

（p.s.：若这个区间为空集或它的左端点与右端点重合，则长度为0；否则其长度为右端点在数轴上表示的数-左端点在数轴上表示的数）

## 输入格式

第一行输入一个正整数n（2<=n<=3e5）。

后面的n行中每行输入两个自然数l、r，表示一个闭区间[l,r]（0<=l<=r<=1e9）。

## 输出格式

输出一个数，表示这个最大值。

Translated by @lhy930

## 样例 #1

### 输入

```
4
1 3
2 6
0 4
3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
2 6
1 3
0 4
1 20
0 4

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3
4 5
1 2
9 20

```

### 输出

```
0

```

## 样例 #4

### 输入

```
2
3 10
1 5

```

### 输出

```
7

```



---

---
title: "Coffee Break"
layout: "post"
diff: 普及/提高-
pid: CF1041C
tag: ['搜索', '贪心', '二分']
---

# Coffee Break

## 题目描述

### 题目大意：
给定$n$个数和一个$k$，这$n$个数都不超过$m$

每次从没被去掉的数里面选一个数$a$，去掉$a$，然后可以任意一个$b(b>a+k)$，然后去掉任意一个$c(c>b+k)$，以此类推

问最少能选多少个$a$，然后输出每个数都是选第几个$a$的时候被去掉的

## 输入格式

一行三个整数$n,m,k$

再一行$n$个整数，表示给定的数

## 输出格式

第一行一个整数，表示最少选$a$的个数

第二行$n$个整数，表示每个数都是选第几个$a$时被去掉的

## 样例 #1

### 输入

```
4 5 3
3 5 1 2

```

### 输出

```
3
3 1 1 2 

```

## 样例 #2

### 输入

```
10 10 1
10 5 7 4 6 3 2 1 9 8

```

### 输出

```
2
2 1 1 2 2 1 2 1 1 2 

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
title: "Boxes Packing"
layout: "post"
diff: 普及/提高-
pid: CF1066D
tag: ['模拟', '贪心', '二分']
---

# Boxes Packing

## 题目描述

有 $n$ 个物品，$m$ 个盒子。其中第 $i$ 个物品的大小为 $a_i$，所有盒子的大小均为 $k$。Makmis 先生想要将这些物品放入盒子中。对于每个物品，如果可以放入当前盒子中则放入当前盒子，否则换一个新的盒子放入。如果物品数量太多使得盒子装不下，可以**将先放入的物品丢弃**。求出最多能够放入多少物品。

## 输入格式

第一行三个整数 $n,m,k$，含义见上文。

第二行共 $n$ 个数，第 $i$ 个为 $a_i$，表示物品的大小。

## 输出格式

一行一个数，表示最多可以放入多少个物品。

## 说明/提示

#### 样例解释
- 在第一组样例中，可以将后 $4$ 个放入盒子。
- 在第二组样例中仅有一个盒子，故只能放入最后一个。
- 在第三组样例中有 $3$ 个大小为 $3$ 的盒子，每个盒子正好装满。
#### 数据规模与约定
保证 $1\le n,m\le2\times 10^5$，$1\le k\le10^9$，$1\le a_i\le k$。

## 样例 #1

### 输入

```
5 2 6
5 2 1 4 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 1 4
4 2 3 4 1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
5 3 3
1 2 3 1 1

```

### 输出

```
5

```



---

---
title: "Vova and Trophies"
layout: "post"
diff: 普及/提高-
pid: CF1082B
tag: ['贪心']
---

# Vova and Trophies

## 题目描述

你现在有 $n$ 枚奖牌，每枚奖牌为金牌或银牌。这些奖牌现在按顺序排成一排。现在你可以调换任意一对奖牌的位置，求金牌最长连续段。

## 输入格式

第一行一个整数 $n$ $(2\le n\le 10^5)$ .

第二行一行字符串，表示你的奖牌。 ( $\texttt{G}$ 表示金牌，$\texttt{S}$ 表示银牌)

## 输出格式

输出一个整数表示答案。

## 样例 #1

### 输入

```
10
GGGSGGGSGG

```

### 输出

```
7

```

## 样例 #2

### 输入

```
4
GGGG

```

### 输出

```
4

```

## 样例 #3

### 输入

```
3
SSS

```

### 输出

```
0

```



---

---
title: "Lazyland"
layout: "post"
diff: 普及/提高-
pid: CF1089L
tag: ['贪心']
---

# Lazyland

## 题目描述

The kingdom of Lazyland is the home to $ n $ idlers. These idlers are incredibly lazy and create many problems to their ruler, the mighty King of Lazyland.

Today $ k $ important jobs for the kingdom ( $ k \le n $ ) should be performed. Every job should be done by one person and every person can do at most one job. The King allowed every idler to choose one job they wanted to do and the $ i $ -th idler has chosen the job $ a_i $ .

Unfortunately, some jobs may not be chosen by anyone, so the King has to persuade some idlers to choose another job. The King knows that it takes $ b_i $ minutes to persuade the $ i $ -th idler. He asked his minister of labour to calculate the minimum total time he needs to spend persuading the idlers to get all the jobs done. Can you help him?

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 10^5 $ ) — the number of idlers and the number of jobs.

The second line of the input contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le k $ ) — the jobs chosen by each idler.

The third line of the input contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le 10^9 $ ) — the time the King needs to spend to persuade the $ i $ -th idler.

## 输出格式

The only line of the output should contain one number — the minimum total time the King needs to spend persuading the idlers to get all the jobs done.

## 说明/提示

In the first example the optimal plan is to persuade idlers 1, 6, and 8 to do jobs 2, 4, and 6.

In the second example each job was chosen by some idler, so there is no need to persuade anyone.

## 样例 #1

### 输入

```
8 7
1 1 3 1 5 3 7 1
5 7 4 8 1 3 5 2

```

### 输出

```
10

```

## 样例 #2

### 输入

```
3 3
3 1 2
5 3 4

```

### 输出

```
0

```



---

---
title: "Binary Period"
layout: "post"
diff: 普及/提高-
pid: CF1342B
tag: ['贪心', '构造']
---

# Binary Period

## 题目描述

假设有一个字符串$s$，如果它的第$i$ 个字符和第$i+k$ 个字符相等$(1\le i\le|s|-k)$ ，那么这个字符串的周期为$k$ 。其中，$|s|$ 表示字符串$s$ 的长度。



现在给你一个字符串$t$ ，$t$ 内只包括```0```和```1```，请你找出这个$s$ ，使其满足如下条件：

1. 字符串$s$ 也只包括```0```和```1```。

2. $|s|\le 2\times|t|$（$s$ 的长度不能超过$t$ 的长度的两倍）。

3. $t$ 是$s$ 的子串。

4. 在满足上面3个条件的情况下，$s$ 需要有最小的周期$k$ 。



$t$ 是$s$ 的子串就是说当$s$ 删除$0$个或更多个字符后（不能改变顺序），$s$ 就变成了$t$ 。例如```011```就是```10101```的子串。

## 输入格式

第一行是一个正整数$T$，表示数据的组数。



接下来$T$行，每行有一个只包含```0```和```1```的字符串$t$ $(1\le|t|\le100)$。

## 输出格式

如果有多种解，输出一个符合条件的字符串$s$ 即可。

## 样例 #1

### 输入

```
4
00
01
111
110
```

### 输出

```
00
01
11111
1010
```



---

---
title: "Decrease the Sum of Digits"
layout: "post"
diff: 普及/提高-
pid: CF1409D
tag: ['贪心']
---

# Decrease the Sum of Digits

## 题目描述

You are given a positive integer $ n $ . In one move, you can increase $ n $ by one (i.e. make $ n := n + 1 $ ). Your task is to find the minimum number of moves you need to perform in order to make the sum of digits of $ n $ be less than or equal to $ s $ .

You have to answer $ t $ independent test cases.

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ) — the number of test cases. Then $ t $ test cases follow.

The only line of the test case contains two integers $ n $ and $ s $ ( $ 1 \le n \le 10^{18} $ ; $ 1 \le s \le 162 $ ).

## 输出格式

For each test case, print the answer: the minimum number of moves you need to perform in order to make the sum of digits of $ n $ be less than or equal to $ s $ .

## 样例 #1

### 输入

```
5
2 1
1 1
500 4
217871987498122 10
100000000000000001 1
```

### 输出

```
8
0
500
2128012501878
899999999999999999
```



---

---
title: "Arena of Greed"
layout: "post"
diff: 普及/提高-
pid: CF1425A
tag: ['贪心', '博弈论']
---

# Arena of Greed

## 题目描述

Lately, Mr. Chanek frequently plays the game Arena of Greed. As the name implies, the game's goal is to find the greediest of them all, who will then be crowned king of Compfestnesia.

The game is played by two people taking turns, where Mr. Chanek takes the first turn. Initially, there is a treasure chest containing $ N $ gold coins. The game ends if there are no more gold coins in the chest. In each turn, the players can make one of the following moves:

- Take one gold coin from the chest.
- Take half of the gold coins on the chest. This move is only available if the number of coins in the chest is even.

Both players will try to maximize the number of coins they have. Mr. Chanek asks your help to find the maximum number of coins he can get at the end of the game if both he and the opponent plays optimally.

## 输入格式

The first line contains a single integer $ T $ $ (1 \le T \le 10^5) $ denotes the number of test cases.

The next $ T $ lines each contain a single integer $ N $ $ (1 \le N \le 10^{18}) $ .

## 输出格式

$ T $ lines, each line is the answer requested by Mr. Chanek.

## 说明/提示

For the first case, the game is as follows:

1. Mr. Chanek takes one coin.
2. The opponent takes two coins.
3. Mr. Chanek takes one coin.
4. The opponent takes one coin.

For the second case, the game is as follows:

1. Mr. Chanek takes three coins.
2. The opponent takes one coin.
3. Mr. Chanek takes one coin.
4. The opponent takes one coin.

## 样例 #1

### 输入

```
2
5
6
```

### 输出

```
2
4
```



---

---
title: "Hills And Valleys"
layout: "post"
diff: 普及/提高-
pid: CF1467B
tag: ['贪心']
---

# Hills And Valleys

## 题目描述

You are given a sequence of $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ . Let us call an index $ j $ ( $ 2 \le j \le {{n-1}} $ ) a hill if $ a_j > a_{{j+1}} $ and $ a_j > a_{{j-1}} $ ; and let us call it a valley if $ a_j < a_{{j+1}} $ and $ a_j < a_{{j-1}} $ .

Let us define the intimidation value of a sequence as the sum of the number of hills and the number of valleys in the sequence. You can change exactly one integer in the sequence to any number that you want, or let the sequence remain unchanged. What is the minimum intimidation value that you can achieve?

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 3\cdot10^5 $ ).

The second line of each test case contains $ n $ space-separated integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ ( $ 1 \le a_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3\cdot10^5 $ .

## 输出格式

For each test case, print a single integer — the minimum intimidation value that you can achieve.

## 说明/提示

In the first test case, changing $ a_2 $ to $ 2 $ results in no hills and no valleys.

In the second test case, the best answer is just to leave the array as it is.

In the third test case, changing $ a_3 $ to $ 6 $ results in only one valley (at the index $ 5 $ ).

In the fourth test case, changing $ a_3 $ to $ 6 $ results in no hills and no valleys.

## 样例 #1

### 输入

```
4
3
1 5 3
5
2 2 2 2 2
6
1 6 2 5 2 10
5
1 6 2 5 1
```

### 输出

```
0
0
1
0
```



---

---
title: "Deep Down Below"
layout: "post"
diff: 普及/提高-
pid: CF1561C
tag: ['贪心']
---

# Deep Down Below

## 题目描述

In a certain video game, the player controls a hero characterized by a single integer value: power. The hero will have to beat monsters that are also characterized by a single integer value: armor.

On the current level, the hero is facing $ n $ caves. To pass the level, the hero must enter all the caves in some order, each cave exactly once, and exit every cave safe and sound. When the hero enters cave $ i $ , he will have to fight $ k_i $ monsters in a row: first a monster with armor $ a_{i, 1} $ , then a monster with armor $ a_{i, 2} $ and so on, finally, a monster with armor $ a_{i, k_i} $ .

The hero can beat a monster if and only if the hero's power is strictly greater than the monster's armor. If the hero can't beat the monster he's fighting, the game ends and the player loses. Note that once the hero enters a cave, he can't exit it before he fights all the monsters in it, strictly in the given order.

Each time the hero beats a monster, the hero's power increases by $ 1 $ .

Find the smallest possible power the hero must start the level with to be able to enter all the caves in some order and beat all the monsters.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of caves.

The $ i $ -th of the next $ n $ lines contains an integer $ k_i $ ( $ 1 \le k_i \le 10^5 $ ) — the number of monsters in the $ i $ -th cave, followed by $ k_i $ integers $ a_{i, 1}, a_{i, 2}, \ldots, a_{i, k_i} $ ( $ 1 \le a_{i, j} \le 10^9 $ ) — armor levels of the monsters in cave $ i $ in order the hero has to fight them.

It is guaranteed that the sum of $ k_i $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case print a single integer — the smallest possible power the hero must start the level with to be able to enter all the caves in some order and beat all the monsters.

## 说明/提示

In the first test case, the hero has to beat a single monster with armor $ 42 $ , it's enough to have power $ 43 $ to achieve that.

In the second test case, the hero can pass the level with initial power $ 13 $ as follows:

- enter cave $ 2 $ : 
  - beat a monster with armor $ 12 $ , power increases to $ 14 $ ;
  - beat a monster with armor $ 11 $ , power increases to $ 15 $ ;
- enter cave $ 1 $ : 
  - beat a monster with armor $ 10 $ , power increases to $ 16 $ ;
  - beat a monster with armor $ 15 $ , power increases to $ 17 $ ;
  - beat a monster with armor $ 8 $ , power increases to $ 18 $ .

## 样例 #1

### 输入

```
2
1
1 42
2
3 10 15 8
2 12 11
```

### 输出

```
43
13
```



---

---
title: "Save More Mice"
layout: "post"
diff: 普及/提高-
pid: CF1593C
tag: ['贪心']
---

# Save More Mice

## 题目描述

坐标轴上有一只猫，$k$ 只老鼠和一个洞口。其中猫在坐标为 $0$ 的位置，洞口在坐标为 $n$ 的位置，所有的老鼠都在猫和洞口之间，其中第 $i$ 只老鼠在 $x_i$ 的位置。可能有多只老鼠在同一个位置上。

在每一秒钟，将会**依次**执行以下行动：

- **其中一只**老鼠会向右移动 $1$ 的位置，如果一个老鼠到达洞口，它会隐藏起来（这只老鼠将不会再移动到任何位置，也不会被猫吃掉）。
- 猫会向右移动 $1$ 的位置，并会吃掉它到达的位置上的老鼠（被吃掉的老鼠将不能再移动）。

直到所有的老鼠都已经隐藏起来或已经被吃掉。

每一秒钟，你都可以选择移动的老鼠，请你求出最多可以保护多少只老鼠安全到达洞口并隐藏起来。

## 输入格式

本题包含多组数据。

输入的第一行包含一个正整数 $t$，表示数据组数。

每组数据包含两行，其中第一行包含两个整数 $n$ 和 $k$；

第二行包含 $k$ 个整数 $x_1,x_2,\ldots,x_k$，表示老鼠的初始位置。

## 输出格式

对于每组数据，输出一行一个非负整数 $m$，表示能保护的老鼠的最大数量。

## 说明/提示

- $1 \le t \le 10^4$；
- $2 \le n \le 10^9$；
- $1 \le k \le 4 \times 10^5$；
- $1 \le x_i <n$。

Translated by @BurningEnderDragon, 2021.10.14

## 样例 #1

### 输入

```
3
10 6
8 7 5 4 9 4
2 8
1 1 1 1 1 1 1 1
12 11
1 2 3 4 5 6 7 8 9 10 11
```

### 输出

```
3
1
4
```



---

---
title: "Dominant Character"
layout: "post"
diff: 普及/提高-
pid: CF1605C
tag: ['贪心']
---

# Dominant Character

## 题目描述

Ashish has a string $ s $ of length $ n $ containing only characters 'a', 'b' and 'c'.

He wants to find the length of the smallest substring, which satisfies the following conditions:

- Length of the substring is at least $ 2 $
- 'a' occurs strictly more times in this substring than 'b'
- 'a' occurs strictly more times in this substring than 'c'

Ashish is busy planning his next Codeforces round. Help him solve the problem.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## 输入格式

The first line contains a single integer $ t $ $ (1 \le t \le 10^{5}) $ — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ $ (2 \le n \le 10^{6}) $ — the length of the string $ s $ .

The second line of each test case contains a string $ s $ consisting only of characters 'a', 'b' and 'c'.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^{6} $ .

## 输出格式

For each test case, output the length of the smallest substring which satisfies the given conditions or print $ -1 $ if there is no such substring.

## 说明/提示

Consider the first test case. In the substring "aa", 'a' occurs twice, while 'b' and 'c' occur zero times. Since 'a' occurs strictly more times than 'b' and 'c', the substring "aa" satisfies the condition and the answer is $ 2 $ . The substring "a" also satisfies this condition, however its length is not at least $ 2 $ .

In the second test case, it can be shown that in none of the substrings of "cbabb" does 'a' occur strictly more times than 'b' and 'c' each.

In the third test case, "cacabccc", the length of the smallest substring that satisfies the conditions is $ 3 $ .

## 样例 #1

### 输入

```
3
2
aa
5
cbabb
8
cacabccc
```

### 输出

```
2
-1
3
```



---

---
title: "Paprika and Permutation"
layout: "post"
diff: 普及/提高-
pid: CF1617C
tag: ['贪心']
---

# Paprika and Permutation

## 题目描述

Paprika loves permutations. She has an array $ a_1, a_2, \dots, a_n $ . She wants to make the array a permutation of integers $ 1 $ to $ n $ .

In order to achieve this goal, she can perform operations on the array. In each operation she can choose two integers $ i $ ( $ 1 \le i \le n $ ) and $ x $ ( $ x > 0 $ ), then perform $ a_i := a_i \bmod x $ (that is, replace $ a_i $ by the remainder of $ a_i $ divided by $ x $ ). In different operations, the chosen $ i $ and $ x $ can be different.

Determine the minimum number of operations needed to make the array a permutation of integers $ 1 $ to $ n $ . If it is impossible, output $ -1 $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 10^5 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ . ( $ 1 \le a_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the minimum number of operations needed to make the array a permutation of integers $ 1 $ to $ n $ , or $ -1 $ if it is impossible.

## 说明/提示

For the first test, the only possible sequence of operations which minimizes the number of operations is:

- Choose $ i=2 $ , $ x=5 $ . Perform $ a_2 := a_2 \bmod 5 = 2 $ .

For the second test, it is impossible to obtain a permutation of integers from $ 1 $ to $ n $ .

## 样例 #1

### 输入

```
4
2
1 7
3
1 5 4
4
12345678 87654321 20211218 23571113
9
1 2 3 4 18 19 5 6 7
```

### 输出

```
1
-1
4
2
```



---

---
title: "Not Sitting"
layout: "post"
diff: 普及/提高-
pid: CF1627B
tag: ['贪心']
---

# Not Sitting

## 题目描述

Rahul and Tina are looking forward to starting their new year at college. As they enter their new classroom, they observe the seats of students are arranged in a $ n \times m $ grid. The seat in row $ r $ and column $ c $ is denoted by $ (r, c) $ , and the distance between two seats $ (a,b) $ and $ (c,d) $ is $ |a-c| + |b-d| $ .

As the class president, Tina has access to exactly $ k $ buckets of pink paint. The following process occurs.

- First, Tina chooses exactly $ k $ seats in the classroom to paint with pink paint. One bucket of paint can paint exactly one seat.
- After Tina has painted $ k $ seats in the previous step, Rahul chooses where he sits. He will not choose a seat that has been painted pink due to his hatred of the colour pink.
- After Rahul has chosen his seat, Tina chooses a seat for herself. She can choose any of the seats, painted or not, other than the one chosen by Rahul.

Rahul wants to choose a seat such that he sits as close to Tina as possible. However, Tina wants to sit as far away from Rahul as possible due to some complicated relationship history that we couldn't fit into the statement!

Now, Rahul wonders for $ k = 0, 1, \dots, n \cdot m - 1 $ , if Tina has $ k $ buckets of paint, how close can Rahul sit to Tina, if both Rahul and Tina are aware of each other's intentions and they both act as strategically as possible? Please help satisfy Rahul's curiosity!

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 5 \cdot 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ m $ ( $ 2 \leq n \cdot m \leq 10^5 $ ) — the number of rows and columns of seats in the classroom.

The sum of $ n \cdot m $ across all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ n \cdot m $ ordered integers — the distance between Rahul and Tina if both of them act optimally for every $ k \in [0, n \cdot m - 1] $ .

## 说明/提示

One possible sequence of choices for the first testcase where Tina has $ k=3 $ buckets of paints is as follows.

Tina paints the seats at positions $ (1, 2) $ , $ (2, 2) $ , $ (3, 2) $ with pink paint. Rahul chooses the seat at $ (3, 1) $ after which Tina chooses to sit at $ (1, 3) $ .

Therefore, the distance between Tina and Rahul is $ |3-1| + |1-3| = 4 $ , and we can prove that this is indeed the minimum possible distance under the given constraints. There may be other choices of seats which lead to the same answer as well.

For $ k=0 $ in the first test case, Rahul can decide to sit at $ (2, 2) $ and Tina can decide to sit at $ (4, 3) $ so the distance between them would be $ |2 - 4| + |2 - 3| = 3 $ .

Below are pictorial representations of the $ k=3 $ and $ k=0 $ cases for the first test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627B/135a6759a6ba23b198694ead1674597ee527f081.png) A possible seating arrangement for $ k=3 $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627B/f8d6f4f57279fb43f8c4bcfe0a1490483d3f4037.png) A possible seating arrangement for $ k=0 $ .

## 样例 #1

### 输入

```
2
4 3
1 2
```

### 输出

```
3 3 4 4 4 4 4 4 5 5 5 5 
1 1
```



---

---
title: "Bit Flipping"
layout: "post"
diff: 普及/提高-
pid: CF1659B
tag: ['贪心', '位运算']
---

# Bit Flipping

## 题目描述

You are given a binary string of length $ n $ . You have exactly $ k $ moves. In one move, you must select a single bit. The state of all bits except that bit will get flipped ( $ 0 $ becomes $ 1 $ , $ 1 $ becomes $ 0 $ ). You need to output the lexicographically largest string that you can get after using all $ k $ moves. Also, output the number of times you will select each bit. If there are multiple ways to do this, you may output any of them.

A binary string $ a $ is lexicographically larger than a binary string $ b $ of the same length, if and only if the following holds:

- in the first position where $ a $ and $ b $ differ, the string $ a $ contains a $ 1 $ , and the string $ b $ contains a $ 0 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case has two lines. The first line has two integers $ n $ and $ k $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ; $ 0 \leq k \leq 10^9 $ ).

The second line has a binary string of length $ n $ , each character is either $ 0 $ or $ 1 $ .

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output two lines.

The first line should contain the lexicographically largest string you can obtain.

The second line should contain $ n $ integers $ f_1, f_2, \ldots, f_n $ , where $ f_i $ is the number of times the $ i $ -th bit is selected. The sum of all the integers must be equal to $ k $ .

## 说明/提示

Here is the explanation for the first testcase. Each step shows how the binary string changes in a move.

- Choose bit $ 1 $ : $ \color{red}{\underline{1}00001} \rightarrow \color{red}{\underline{1}}\color{blue}{11110} $ .
- Choose bit $ 4 $ : $ \color{red}{111\underline{1}10} \rightarrow \color{blue}{000}\color{red}{\underline{1}}\color{blue}{01} $ .
- Choose bit $ 4 $ : $ \color{red}{000\underline{1}01} \rightarrow \color{blue}{111}\color{red}{\underline{1}}\color{blue}{10} $ .

 The final string is $ 111110 $ and this is the lexicographically largest string we can get.

## 样例 #1

### 输入

```
6
6 3
100001
6 4
100011
6 0
000000
6 1
111001
6 11
101100
6 12
001110
```

### 输出

```
111110
1 0 0 2 0 0 
111110
0 1 1 1 0 1 
000000
0 0 0 0 0 0 
100110
1 0 0 0 0 0 
111111
1 2 1 3 0 4 
111110
1 1 4 2 0 4
```



---

---
title: "Line Empire"
layout: "post"
diff: 普及/提高-
pid: CF1659C
tag: ['贪心']
---

# Line Empire

## 题目描述

You are an ambitious king who wants to be the Emperor of The Reals. But to do that, you must first become Emperor of The Integers.

Consider a number axis. The capital of your empire is initially at $ 0 $ . There are $ n $ unconquered kingdoms at positions $ 0<x_1<x_2<\ldots<x_n $ . You want to conquer all other kingdoms.

There are two actions available to you:

- You can change the location of your capital (let its current position be $ c_1 $ ) to any other conquered kingdom (let its position be $ c_2 $ ) at a cost of $ a\cdot |c_1-c_2| $ .
- From the current capital (let its current position be $ c_1 $ ) you can conquer an unconquered kingdom (let its position be $ c_2 $ ) at a cost of $ b\cdot |c_1-c_2| $ . You cannot conquer a kingdom if there is an unconquered kingdom between the target and your capital.

Note that you cannot place the capital at a point without a kingdom. In other words, at any point, your capital can only be at $ 0 $ or one of $ x_1,x_2,\ldots,x_n $ . Also note that conquering a kingdom does not change the position of your capital.

Find the minimum total cost to conquer all kingdoms. Your capital can be anywhere at the end.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of each test case follows.

The first line of each test case contains $ 3 $ integers $ n $ , $ a $ , and $ b $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ; $ 1 \leq a,b \leq 10^5 $ ).

The second line of each test case contains $ n $ integers $ x_1, x_2, \ldots, x_n $ ( $ 1 \leq x_1 < x_2 < \ldots < x_n \leq 10^8 $ ).

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum cost to conquer all kingdoms.

## 说明/提示

Here is an optimal sequence of moves for the second test case:

1. Conquer the kingdom at position $ 1 $ with cost $ 3\cdot(1-0)=3 $ .
2. Move the capital to the kingdom at position $ 1 $ with cost $ 6\cdot(1-0)=6 $ .
3. Conquer the kingdom at position $ 5 $ with cost $ 3\cdot(5-1)=12 $ .
4. Move the capital to the kingdom at position $ 5 $ with cost $ 6\cdot(5-1)=24 $ .
5. Conquer the kingdom at position $ 6 $ with cost $ 3\cdot(6-5)=3 $ .
6. Conquer the kingdom at position $ 21 $ with cost $ 3\cdot(21-5)=48 $ .
7. Conquer the kingdom at position $ 30 $ with cost $ 3\cdot(30-5)=75 $ .

The total cost is $ 3+6+12+24+3+48+75=171 $ . You cannot get a lower cost than this.

## 样例 #1

### 输入

```
4
5 2 7
3 5 12 13 21
5 6 3
1 5 6 21 30
2 9 3
10 15
11 27182 31415
16 18 33 98 874 989 4848 20458 34365 38117 72030
```

### 输出

```
173
171
75
3298918744
```



---

---
title: "Array Cloning Technique"
layout: "post"
diff: 普及/提高-
pid: CF1665B
tag: ['贪心', '倍增']
---

# Array Cloning Technique

## 题目描述

You are given an array $ a $ of $ n $ integers. Initially there is only one copy of the given array.

You can do operations of two types:

1. Choose any array and clone it. After that there is one more copy of the chosen array.
2. Swap two elements from any two copies (maybe in the same copy) on any positions.

You need to find the minimal number of operations needed to obtain a copy where all elements are equal.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case output a single integer — the minimal number of operations needed to create at least one copy where all elements are equal.

## 说明/提示

In the first test case all elements in the array are already equal, that's why the answer is $ 0 $ .

In the second test case it is possible to create a copy of the given array. After that there will be two identical arrays:

 $ [ \ 0 \ 1 \ 3 \ 3 \ 7 \ 0 \ ] $ and $ [ \ 0 \ 1 \ 3 \ 3 \ 7 \ 0 \ ] $

After that we can swap elements in a way so all zeroes are in one array:

 $ [ \ 0 \ \underline{0} \ \underline{0} \ 3 \ 7 \ 0 \ ] $ and $ [ \ \underline{1} \ 1 \ 3 \ 3 \ 7 \ \underline{3} \ ] $

Now let's create a copy of the first array:

 $ [ \ 0 \ 0 \ 0 \ 3 \ 7 \ 0 \ ] $ , $ [ \ 0 \ 0 \ 0 \ 3 \ 7 \ 0 \ ] $ and $ [ \ 1 \ 1 \ 3 \ 3 \ 7 \ 3 \ ] $

Let's swap elements in the first two copies:

 $ [ \ 0 \ 0 \ 0 \ \underline{0} \ \underline{0} \ 0 \ ] $ , $ [ \ \underline{3} \ \underline{7} \ 0 \ 3 \ 7 \ 0 \ ] $ and $ [ \ 1 \ 1 \ 3 \ 3 \ 7 \ 3 \ ] $ .

Finally, we made a copy where all elements are equal and made $ 6 $ operations.

It can be proven that no fewer operations are enough.

## 样例 #1

### 输入

```
6
1
1789
6
0 1 3 3 7 0
2
-1000000000 1000000000
4
4 3 2 1
5
2 5 7 6 3
7
1 1 1 1 1 1 1
```

### 输出

```
0
6
2
5
7
0
```



---

---
title: "Replace With the Previous, Minimize"
layout: "post"
diff: 普及/提高-
pid: CF1675E
tag: ['贪心']
---

# Replace With the Previous, Minimize

## 题目描述

### 题意简述

有一个长度为 $n$ 的，只含小写字母的字符串 $s$，每次操作可以选择 $26$ 个字母之一，将字符串中所有该字母替换为上一个字母（如 $\texttt{c}\to\texttt{b},\texttt{b}\to\texttt{a}$，特殊地，$\texttt{a}\to\texttt{z}$）。在 $k$ 次操作**之内**，使得到的字符串的字典序最小。

## 输入格式

第一行一个正整数 $t$ 表示数据组数。

对于每组数据，第一行两个正整数 $n,k$，第二行一个字符串 $s$。

## 输出格式

对于每组数据，输出一行一个字符串表示答案。

### 数据规模

$n\le 2\times 10^5,k\le 10^9,\sum n\le 2\times 10^5$

## 样例 #1

### 输入

```
4
3 2
cba
4 5
fgde
7 5
gndcafb
4 19
ekyv
```

### 输出

```
aaa
agaa
bnbbabb
aapp
```



---

---
title: "Binary String"
layout: "post"
diff: 普及/提高-
pid: CF1680C
tag: ['贪心', '二分']
---

# Binary String

## 题目描述

你有一个由 $1$ 和 $0$ 构成的字符串 $s$。

你需要先从 $s$ 的开头移除若干字符，然后从 $s$ 的结尾移除若干字符。（当然，你可以不移除任何字符，也可以将整个 $s$ 移除掉）

这样做的代价是从 $s$ 中移除的 $1$ 的个数和 $s$ 中剩余的 $0$ 的个数的最大值。

求代价的最小值。

## 输入格式

第一行一个整数 $t$ 表示数据组数。$(1\le t\le 10^4)$

接下来 $t$ 行，每行一个字符串 $s$ 表示这组数据的 $s$。$(1\le |s|\le 2⋅10^5)$

$s$ 的总和不超过 $2⋅10^5$。

## 输出格式

对于每组数据，输出一个整数表示最小代价。

## 说明/提示

样例解释：

`101110110` -> `(10) 111011 (0)`

`1001001001001` -> `(100100) 1001 (001)`

`0000111111` -> `(0000) 111111 ()`

`00000` -> `(00000)()`

`1111` -> `()1111()`

## 样例 #1

### 输入

```
5
101110110
1001001001001
0000111111
00000
1111
```

### 输出

```
1
3
0
0
0
```



---

---
title: "Fishingprince Plays With Array"
layout: "post"
diff: 普及/提高-
pid: CF1696C
tag: ['模拟', '数学', '贪心', '构造']
---

# Fishingprince Plays With Array

## 题目描述

Fishingprince is playing with an array $ [a_1,a_2,\dots,a_n] $ . He also has a magic number $ m $ .

He can do the following two operations on it:

- Select $ 1\le i\le n $ such that $ a_i $ is divisible by $ m $ (that is, there exists an integer $ t $ such that $ m \cdot t = a_i $ ). Replace $ a_i $ with  $ m $ copies of $ \frac{a_i}{m} $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[2,3] $ and $ i=1 $ , $ a $ changes into $ [1,1,3] $ .
- Select $ 1\le i\le n-m+1 $ such that $ a_i=a_{i+1}=\dots=a_{i+m-1} $ . Replace these $ m $ elements with a single $ m \cdot a_i $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[3,2,2,3] $ and $ i=2 $ , $ a $ changes into $ [3,4,3] $ .

Note that the array length might change during the process. The value of $ n $ above is defined as the current length of the array (might differ from the $ n $ in the input).

Fishingprince has another array $ [b_1,b_2,\dots,b_k] $ . Please determine if he can turn $ a $ into $ b $ using any number (possibly zero) of operations.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1\le n\le 5\cdot 10^4 $ , $ 2\le m\le 10^9 $ ).

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1\le a_i\le 10^9 $ ).

The third line of each test case contains one integer $ k $ ( $ 1\le k\le 5\cdot 10^4 $ ).

The fourth line of each test case contains $ k $ integers $ b_1,b_2,\ldots,b_k $ ( $ 1\le b_i\le 10^9 $ ).

It is guaranteed that the sum of $ n+k $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each testcase, print Yes if it is possible to turn $ a $ into $ b $ , and No otherwise. You can print each letter in any case (upper or lower).

## 说明/提示

In the first test case of the sample, we can do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},4,2]\to [1,\color{red}{4},4,2] $ .

In the second testcase of the sample, we can:

- do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},8,2,2]\to [1,\color{red}{4},8,2,2] $ .
- do the second operation with $ i=4 $ : $ [1,4,8,\color{red}{2,2}]\to [1,4,8,\color{red}{4}] $ .
- do the first operation with $ i=3 $ : $ [1,4,\color{red}{8},4]\to [1,4,\color{red}{4,4},4] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{4,4},4,4]\to [1,\color{red}{8},4,4] $ .
- do the second operation with $ i=3 $ : $ [1,8,\color{red}{4,4}]\to [1,8,\color{red}{8}] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{8,8}]\to [1,\color{red}{16}] $ .

## 样例 #1

### 输入

```
5
5 2
1 2 2 4 2
4
1 4 4 2
6 2
1 2 2 8 2 2
2
1 16
8 3
3 3 3 3 3 3 3 3
4
6 6 6 6
8 3
3 9 6 3 12 12 36 12
16
9 3 2 2 2 3 4 12 4 12 4 12 4 12 4 4
8 3
3 9 6 3 12 12 36 12
7
12 2 4 3 4 12 56
```

### 输出

```
Yes
Yes
No
Yes
No
```



---

---
title: "Virus"
layout: "post"
diff: 普及/提高-
pid: CF1704C
tag: ['贪心']
---

# Virus

## 题目描述

There are $ n $ houses numbered from $ 1 $ to $ n $ on a circle. For each $ 1 \leq i \leq n - 1 $ , house $ i $ and house $ i + 1 $ are neighbours; additionally, house $ n $ and house $ 1 $ are also neighbours.

Initially, $ m $ of these $ n $ houses are infected by a deadly virus. Each morning, Cirno can choose a house which is uninfected and protect the house from being infected permanently.

Every day, the following things happen in order:

- Cirno chooses an uninfected house, and protect it permanently.
- All uninfected, unprotected houses which have at least one infected neighbor become infected.

Cirno wants to stop the virus from spreading. Find the minimum number of houses that will be infected in the end, if she optimally choose the houses to protect.

Note that every day Cirno always chooses a house to protect before the virus spreads. Also, a protected house will not be infected forever.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Description of test cases follows.

The first line of each test case consists of two positive integers $ n, m $ ( $ 5 \leq n \leq 10^9 $ , $ 1 \leq m \leq \min(n, 10^5) $ ) — the number of houses on the circle, and the number of houses that are initially infected.

The second line of each test case consists of $ m $ distinct positive integers $ a_1, a_2, \cdots , a_m $ ( $ 1 \leq a_i \leq n $ ) — the indices of the houses infected initially.

It is guaranteed that the sum of $ m $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output an integer on a separate line, which is the minimum number of infected houses in the end.

## 说明/提示

In the first test case:

At the start of the first day, house $ 3 $ , $ 6 $ , $ 8 $ are infected. Choose house $ 2 $ to protect.

At the start of the second day, house $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ , $ 7 $ , $ 8 $ , $ 9 $ are infected. Choose house $ 10 $ to protect.

At the start of the third day, no more houses are infected.

In the second test case:

At the start of the first day, house $ 2 $ , $ 5 $ are infected. Choose house $ 1 $ to protect.

At the start of the second day, house $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ are infected. No more available houses can be protected.

## 样例 #1

### 输入

```
8
10 3
3 6 8
6 2
2 5
20 3
3 7 12
41 5
1 11 21 31 41
10 5
2 4 6 8 10
5 5
3 2 5 4 1
1000000000 1
1
1000000000 4
1 1000000000 10 16
```

### 输出

```
7
5
11
28
9
5
2
15
```



---

---
title: "Qpwoeirut And The City"
layout: "post"
diff: 普及/提高-
pid: CF1706C
tag: ['动态规划 DP', '贪心']
---

# Qpwoeirut And The City

## 题目描述

Qpwoeirut has taken up architecture and ambitiously decided to remodel his city.

Qpwoeirut's city can be described as a row of $ n $ buildings, the $ i $ -th ( $ 1 \le i \le n $ ) of which is $ h_i $ floors high. You can assume that the height of every floor in this problem is equal. Therefore, building $ i $ is taller than the building $ j $ if and only if the number of floors $ h_i $ in building $ i $ is larger than the number of floors $ h_j $ in building $ j $ .

Building $ i $ is cool if it is taller than both building $ i-1 $ and building $ i+1 $ (and both of them exist). Note that neither the $ 1 $ -st nor the $ n $ -th building can be cool.

To remodel the city, Qpwoeirut needs to maximize the number of cool buildings. To do this, Qpwoeirut can build additional floors on top of any of the buildings to make them taller. Note that he cannot remove already existing floors.

Since building new floors is expensive, Qpwoeirut wants to minimize the number of floors he builds. Find the minimum number of floors Qpwoeirut needs to build in order to maximize the number of cool buildings.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains the single integer $ n $ ( $ 3 \le n \le 10^5 $ ) — the number of buildings in Qpwoeirut's city.

The second line of each test case contains $ n $ integers $ h_1, h_2, \ldots, h_n $ ( $ 1 \le h_i \le 10^9 $ ) — the number of floors in each of the buildings of the city.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the minimum number of additional floors Qpwoeirut needs to build in order to maximize the number of cool buildings.

## 说明/提示

In the first test case, it is optimal for Qpwoeirut to make the second building cool by building $ 2 $ additional floors on top of it, making it taller than both of its adjacent buildings. The final heights of buildings will be $ [2, \underline{3}, 2] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/5b747d1e682e5f282bdd90fc1247bc9f2859b4d3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/c25e1e8b92772ee4d6c001b5263ad32fc0bed1d3.png)In the second test case, the number of cool buildings is already maximized, so Qpwoeirut does not need to do anything.

In the third test case, it is optimal for Qpwoeirut to make the third and fifth buildings cool by building $ 2 $ additional floors onto the third building and $ 1 $ additional floor onto the fifth building. The final heights of buildings will be $ [3, 1, \underline{6}, 5, \underline{6}, 2] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/d8dd96553e5aa6fe2bbad7a9bf1dc528da32254c.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/6d7185baf1e5e2a187bb01c943d100104f7de6bc.png)It can be shown that it is impossible to make more than $ 2 $ of the buildings cool, or to make $ 2 $ buildings cool using fewer than $ 3 $ additional floors.

In the fourth test case, Qpwoeirut can either make the second building cool, or he can make the third building cool. Either way, he will be building $ 3 $ additional floors and maximizing the number of cool buildings. The final heights of buildings will be $ [4, 2, \underline{4}, 3, 5, 3, 6, 1] $ or $ [4, \underline{5}, 1, 3, 5, 3, 6, 1] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/27f107a434b26468932a928c7c16fd0abda918f0.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/4e2e7951e438027228057e8a21e8bea81f160a32.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/8e41aee337358c3f261ed9626c0e19808d3f7d2c.png)

## 样例 #1

### 输入

```
6
3
2 1 2
5
1 2 1 4 3
6
3 1 4 5 5 2
8
4 2 1 3 5 3 6 1
6
1 10 1 1 10 1
8
1 10 11 1 10 11 10 1
```

### 输出

```
2
0
3
3
0
4
```



---

---
title: "Color the Picture"
layout: "post"
diff: 普及/提高-
pid: CF1710A
tag: ['贪心']
---

# Color the Picture

## 题目描述

A picture can be represented as an $ n\times m $ grid ( $ n $ rows and $ m $ columns) so that each of the $ n \cdot m $ cells is colored with one color. You have $ k $ pigments of different colors. You have a limited amount of each pigment, more precisely you can color at most $ a_i $ cells with the $ i $ -th pigment.

A picture is considered beautiful if each cell has at least $ 3 $ toroidal neighbors with the same color as itself.

Two cells are considered toroidal neighbors if they toroidally share an edge. In other words, for some integers $ 1 \leq x_1,x_2 \leq n $ and $ 1 \leq y_1,y_2 \leq m $ , the cell in the $ x_1 $ -th row and $ y_1 $ -th column is a toroidal neighbor of the cell in the $ x_2 $ -th row and $ y_2 $ -th column if one of following two conditions holds:

- $ x_1-x_2 \equiv \pm1 \pmod{n} $ and $ y_1=y_2 $ , or
- $ y_1-y_2 \equiv \pm1 \pmod{m} $ and $ x_1=x_2 $ .

Notice that each cell has exactly $ 4 $ toroidal neighbors. For example, if $ n=3 $ and $ m=4 $ , the toroidal neighbors of the cell $ (1, 2) $ (the cell on the first row and second column) are: $ (3, 2) $ , $ (2, 2) $ , $ (1, 3) $ , $ (1, 1) $ . They are shown in gray on the image below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710A/e3c8d205b2238ddbd1672ed2006ec3bad526c6bc.png)The gray cells show toroidal neighbors of $ (1, 2) $ .Is it possible to color all cells with the pigments provided and create a beautiful picture?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 10^4 $ ). The description of the test cases follows.

The first line of each test case contains three integers $ n $ , $ m $ , and $ k $ ( $ 3 \leq n,m \leq 10^9 $ , $ 1 \leq k \leq 10^5 $ ) — the number of rows and columns of the picture and the number of pigments.

The next line contains $ k $ integers $ a_1,a_2,\dots, a_k $ ( $ 1 \leq a_i \leq 10^9 $ ) — $ a_i $ is the maximum number of cells that can be colored with the $ i $ -th pigment.

It is guaranteed that the sum of $ k $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print "Yes" (without quotes) if it is possible to color a beautiful picture. Otherwise, print "No" (without quotes).

## 说明/提示

In the first test case, one possible solution is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710A/3537b81501ae3eaf0154251b0f27e35d8e63b1ec.png)In the third test case, we can color all cells with pigment $ 1 $ .

## 样例 #1

### 输入

```
6
4 6 3
12 9 8
3 3 2
8 8
3 3 2
9 5
4 5 2
10 11
5 4 2
9 11
10 10 3
11 45 14
```

### 输出

```
Yes
No
Yes
Yes
No
No
```



---

---
title: "Sort Zero"
layout: "post"
diff: 普及/提高-
pid: CF1712C
tag: ['贪心']
---

# Sort Zero

## 题目描述

An array is sorted if it has no inversions

A Young Boy



You are given an array of $ n $ positive integers $ a_1,a_2,\ldots,a_n $ .

In one operation you do the following:

1. Choose any integer $ x $ .
2. For all $ i $ such that $ a_i = x $ , do $ a_i := 0 $ (assign $ 0 $ to $ a_i $ ).

Find the minimum number of operations required to sort the array in non-decreasing order.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ).

The second line of each test case contains $ n $ positive integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le n $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case print one integer — the minimum number of operations required to sort the array in non-decreasing order.

## 说明/提示

In the first test case, you can choose $ x = 3 $ for the operation, the resulting array is $ [0, 0, 2] $ .

In the second test case, you can choose $ x = 1 $ for the first operation and $ x = 3 $ for the second operation, the resulting array is $ [0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
5
3
3 3 2
4
1 3 1 3
5
4 1 5 3 2
4
2 4 1 2
1
1
```

### 输出

```
1
2
4
3
0
```



---

---
title: "Madoka and Formal Statement"
layout: "post"
diff: 普及/提高-
pid: CF1717C
tag: ['贪心']
---

# Madoka and Formal Statement

## 题目描述

给定一个数列 $a_{1…n}$, 如果满足下面条件, 你可以使 $a_i = a_i + 1$:

- $i < n$ 且 $a_i \leq a_{i+1}$
- $i = n$ 且 $a_i \leq a_{1}$

再给定一个数列 $b_{1…n}$, 问 $a$ 是否可以通过上述操作变为 $b$.

## 输入格式

本题多测.

第一行为 $t$, 表示 $t$ 组数据.

接下来 $t$ 组数据，每组第一行为一个正整数 $n$, 

第二行为 $n$ 个整数, 代表数列 $a$;

第三行为 $n$ 个整数, 代表数列 $b$.

保证 $\Sigma n \le 2×10^5$.

## 输出格式

对于每组数据,输出 `"YES"` 或 `"NO"`.

## 样例 #1

### 输入

```
5
3
1 2 5
1 2 5
2
2 2
1 3
4
3 4 1 2
6 4 2 5
3
2 4 1
4 5 3
5
1 2 3 4 5
6 5 6 7 6
```

### 输出

```
YES
NO
NO
NO
YES
```



---

---
title: "Line"
layout: "post"
diff: 普及/提高-
pid: CF1722D
tag: ['贪心']
---

# Line

## 题目描述

There are $ n $ people in a horizontal line, each looking either to the left or the right. Each person counts the number of people in the direction they are looking. The value of the line is the sum of each person's count.

For example, in the arrangement LRRLL, where L stands for a person looking left and R stands for a person looking right, the counts for each person are $ [0, 3, 2, 3, 4] $ , and the value is $ 0+3+2+3+4=12 $ .

You are given the initial arrangement of people in the line. For each $ k $ from $ 1 $ to $ n $ , determine the maximum value of the line if you can change the direction of at most $ k $ people.

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2\cdot10^5 $ ) — the length of the line.

The following line contains a string consisting of $ n $ characters, each of which is either L or R, representing a person facing left or right, respectively — the description of the line.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot10^5 $ .

Please note that the answer for some test cases won't fit into 32-bit integer type, so you should use at least 64-bit integer type in your programming language (like long long for C++).

## 输出格式

For each test case, output $ n $ space-separated non-negative integers — the maximum value of the line if you can change the direction of at most $ k $ people for each $ k $ from $ 1 $ to $ n $ , inclusive.

## 说明/提示

In the first test case:

- $ k=1 $ : change the direction of $ 1 $ person to make the line RLR. The total value is $ 2+1+0=3 $ .
- $ k=2 $ : change the direction of $ 2 $ people to make the line RLL. The total value is $ 2+1+2=5 $ .
- $ k=3 $ : change the direction of $ 2 $ people to make the line RLL. The total value is $ 2+1+2=5 $ . Note that you have to change the direction of at most $ k $ people.

In the second test case, it is optimal to only change the direction of the first person for all $ k $ from $ 1 $ to $ 5 $ (that is, make the line RRRLL).

## 样例 #1

### 输入

```
6
3
LLR
5
LRRLL
1
L
12
LRRRLLLRLLRL
10
LLLLLRRRRR
9
LRLRLRLRL
```

### 输出

```
3 5 5 
16 16 16 16 16 
0 
86 95 98 101 102 102 102 102 102 102 102 102 
29 38 45 52 57 62 65 68 69 70 
44 50 54 56 56 56 56 56 56
```



---

---
title: "Complementary XOR"
layout: "post"
diff: 普及/提高-
pid: CF1750C
tag: ['贪心']
---

# Complementary XOR

## 题目描述

You have two binary strings $ a $ and $ b $ of length $ n $ . You would like to make all the elements of both strings equal to $ 0 $ . Unfortunately, you can modify the contents of these strings using only the following operation:

- You choose two indices $ l $ and $ r $ ( $ 1 \le l \le r \le n $ );
- For every $ i $ that respects $ l \le i \le r $ , change $ a_i $ to the opposite. That is, $ a_i := 1 - a_i $ ;
- For every $ i $ that respects either $ 1 \le i < l $ or $ r < i \le n $ , change $ b_i $ to the opposite. That is, $ b_i := 1 - b_i $ .

Your task is to determine if this is possible, and if it is, to find such an appropriate chain of operations. The number of operations should not exceed $ n + 5 $ . It can be proven that if such chain of operations exists, one exists with at most $ n + 5 $ operations.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the length of the strings.

The second line of each test case contains a binary string $ a $ , consisting only of characters 0 and 1, of length $ n $ .

The third line of each test case contains a binary string $ b $ , consisting only of characters 0 and 1, of length $ n $ .

It is guaranteed that sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, print first "YES" if it's possible to make all the elements of both strings equal to $ 0 $ . Otherwise, print "NO". If the answer is "YES", on the next line print a single integer $ k $ ( $ 0 \le k \le n + 5 $ ) — the number of operations. Then $ k $ lines follows, each contains two integers $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ) — the description of the operation.

If there are several correct answers, print any of them.

## 说明/提示

In the first test case, we can perform one operation with $ l = 2 $ and $ r = 2 $ . So $ a_2 := 1 - 1 = 0 $ and string $ a $ became equal to 000. $ b_1 := 1 - 1 = 0 $ , $ b_3 := 1 - 1 = 0 $ and string $ b $ became equal to 000.

In the second and in the third test cases, it can be proven that it's impossible to make all elements of both strings equal to $ 0 $ .

In the fourth test case, we can perform an operation with $ l = 1 $ and $ r = 2 $ , then string $ a $ became equal to 01, and string $ b $ doesn't change. Then we perform an operation with $ l = 2 $ and $ r = 2 $ , then $ a_2 := 1 - 1 = 0 $ and $ b_1 = 1 - 1 = 0 $ . So both of string $ a $ and $ b $ became equal to 00.

In the fifth test case, we can perform an operation with $ l = 1 $ and $ r = 1 $ . Then string $ a $ became equal to 011 and string $ b $ became equal to 100. Then we can perform an operation with $ l = 2 $ and $ r = 3 $ , so both of string $ a $ and $ b $ became equal to 000.

## 样例 #1

### 输入

```
5
3
010
101
2
11
10
4
1000
0011
2
10
10
3
111
111
```

### 输出

```
YES
1
2 2
NO
NO
YES
2
1 2
2 2
YES
2
1 1
2 3
```



---

---
title: "Doremy's City Construction"
layout: "post"
diff: 普及/提高-
pid: CF1764C
tag: ['贪心']
---

# Doremy's City Construction

## 题目描述

Doremy's new city is under construction! The city can be regarded as a simple undirected graph with $ n $ vertices. The $ i $ -th vertex has altitude $ a_i $ . Now Doremy is deciding which pairs of vertices should be connected with edges.

Due to economic reasons, there should be no self-loops or multiple edges in the graph.

Due to safety reasons, there should not be pairwise distinct vertices $ u $ , $ v $ , and $ w $ such that $ a_u \leq a_v \leq a_w $ and the edges $ (u,v) $ and $ (v,w) $ exist.

Under these constraints, Doremy would like to know the maximum possible number of edges in the graph. Can you help her?

Note that the constructed graph is allowed to be disconnected.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2\cdot 10^5 $ ) — the number of vertices.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1\le a_i\le 10^6 $ ) — the altitudes of each vertex.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum possible number of edges in the graph.

## 说明/提示

In the first test case, there can only be at most $ 3 $ edges in the graph. A possible construction is to connect $ (1,3) $ , $ (2,3) $ , $ (3,4) $ . In the picture below the red number above node $ i $ is $ a_i $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/664da7a7b39c78efe9a85191f05318cb0a9df4d9.png)

The following list shows all such $ u $ , $ v $ , $ w $ that the edges $ (u,v) $ and $ (v,w) $ exist.

- $ u=1 $ , $ v=3 $ , $ w=2 $ ;
- $ u=1 $ , $ v=3 $ , $ w=4 $ ;
- $ u=2 $ , $ v=3 $ , $ w=1 $ ;
- $ u=2 $ , $ v=3 $ , $ w=4 $ ;
- $ u=4 $ , $ v=3 $ , $ w=1 $ ;
- $ u=4 $ , $ v=3 $ , $ w=2 $ .

Another possible construction is to connect $ (1,4) $ , $ (2,4) $ , $ (3,4) $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/7d1fc03a74b1366633e41dc227acef23827c0f69.png)

An unacceptable construction is to connect $ (1,3) $ , $ (2,3) $ , $ (2,4) $ , $ (3,4) $ . Because when $ u=4 $ , $ v=2 $ , $ w=3 $ , $ a_u\le a_v \le a_w $ holds, and the respective edges exist.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/02cccee9e8ea3921ef7338c4d1dd72e83e933cbc.png)

## 样例 #1

### 输入

```
4
4
2 2 3 1
6
5 2 3 1 5 2
12
7 2 4 9 1 4 6 3 7 4 2 3
4
1000000 1000000 1000000 1000000
```

### 输出

```
3
9
35
2
```



---

---
title: "Playoff"
layout: "post"
diff: 普及/提高-
pid: CF1767D
tag: ['贪心']
---

# Playoff

## 题目描述

$ 2^n $ teams participate in a playoff tournament. The tournament consists of $ 2^n - 1 $ games. They are held as follows: in the first phase of the tournament, the teams are split into pairs: team $ 1 $ plays against team $ 2 $ , team $ 3 $ plays against team $ 4 $ , and so on (so, $ 2^{n-1} $ games are played in that phase). When a team loses a game, it is eliminated, and each game results in elimination of one team (there are no ties). After that, only $ 2^{n-1} $ teams remain. If only one team remains, it is declared the champion; otherwise, the second phase begins, where $ 2^{n-2} $ games are played: in the first one of them, the winner of the game " $ 1 $ vs $ 2 $ " plays against the winner of the game " $ 3 $ vs $ 4 $ ", then the winner of the game " $ 5 $ vs $ 6 $ " plays against the winner of the game " $ 7 $ vs $ 8 $ ", and so on. This process repeats until only one team remains.

The skill level of the $ i $ -th team is $ p_i $ , where $ p $ is a permutation of integers $ 1 $ , $ 2 $ , ..., $ 2^n $ (a permutation is an array where each element from $ 1 $ to $ 2^n $ occurs exactly once).

You are given a string $ s $ which consists of $ n $ characters. These characters denote the results of games in each phase of the tournament as follows:

- if $ s_i $ is equal to 0, then during the $ i $ -th phase (the phase with $ 2^{n-i} $ games), in each match, the team with the lower skill level wins;
- if $ s_i $ is equal to 1, then during the $ i $ -th phase (the phase with $ 2^{n-i} $ games), in each match, the team with the higher skill level wins.

Let's say that an integer $ x $ is winning if it is possible to find a permutation $ p $ such that the team with skill $ x $ wins the tournament. Find all winning integers.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 18 $ ).

The second line contains the string $ s $ of length $ n $ consisting of the characters 0 and/or 1.

## 输出格式

Print all the winning integers $ x $ in ascending order.

## 样例 #1

### 输入

```
3
101
```

### 输出

```
4 5 6 7
```

## 样例 #2

### 输入

```
1
1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2
01
```

### 输出

```
2 3
```



---

---
title: "Подкрутка II"
layout: "post"
diff: 普及/提高-
pid: CF1769C2
tag: ['动态规划 DP', '贪心']
---

# Подкрутка II

## 题目描述

В этой версии задачи $ n \le 2 \cdot 10^5 $ и $ a_i \le 10^6 $ (а также есть ограничение на сумму $ n $ по наборам входных данных внутри одного теста).

Вика за время работы в компании VK уже сделала $ n $ коммитов в системе контроля версий. $ i $ -й коммит был сделан в $ a_i $ -й день работы Вики в компании. В некоторые дни Вика могла сделать несколько коммитов, а в другие — не сделать ни одного.

Вику интересуют такие отрезки подряд идущих дней, что в каждый из этих дней у неё есть хотя бы один коммит. Чем длиннее будет самый длинный такой отрезок, тем более продуктивным сотрудником она будет себя ощущать.

Недавно Вика нашла способ подкрутить время любого коммита вперёд, но не более чем на сутки. Таким образом, $ i $ -й коммит теперь может быть «сделан» либо в $ a_i $ -й, либо в $ (a_i + 1) $ -й день. Время каждого коммита можно подкрутить независимо от других — в частности, можно как оставить всем коммитам исходное время, так и перенести все коммиты ровно на день вперёд.

Найдите длину самого длинного возможного отрезка подряд идущих дней, в каждый из которых у Вики в профиле будет отображаться хотя бы один коммит, после возможной подкрутки времени некоторых коммитов.

## 输入格式

Каждый тест состоит из нескольких наборов входных данных. В первой строке находится одно целое число $ t $ ( $ 1 \le t \le 100 $ ) — количество наборов входных данных. Далее следует описание наборов входных данных.

Первая строка каждого набора входных данных содержит одно целое число $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — число коммитов.

Вторая строка содержит $ n $ целых чисел $ a_1, a_2, \ldots, a_n $ в неубывающем порядке ( $ 1 \le a_1 \le a_2 \le \ldots \le a_n \le 10^6 $ ) — номера дней, в которые были сделаны коммиты.

Гарантируется, что сумма $ n $ по всем наборам входных данных не превосходит $ 2 \cdot 10^5 $ .

## 输出格式

Для каждого набора входных данных выведите одно целое число — максимальную возможную длину отрезка дней, в каждый из которых у Вики в профиле будет отображаться хотя бы один коммит, после возможной подкрутки времени некоторых коммитов вперёд не более чем на сутки.

## 样例 #1

### 输入

```
3
9
1 1 3 4 6 6 6 8 10
6
1 2 3 4 5 6
5
10 10 10 10 10
```

### 输出

```
5
6
2
```



---

---
title: "Coloring"
layout: "post"
diff: 普及/提高-
pid: CF1774B
tag: ['贪心']
---

# Coloring

## 题目描述

Cirno_9baka 的纸条上有 $n$ 个格子，他觉得空白的纸条看着有点无趣，于是想在纸条的格子上涂上 $m$ 种颜色。同时，他认为第 $i$ 种颜色必须要用 $a_i$ 次，且每连续 $k$ 个格子里涂的颜色必须互不相同。

Cirno_9baka 想知道有没有这样的一种涂色方案能符合他的要求。

## 输入格式

第一行，一个整数 $t$ ( $1 \leq t \leq 10\,000$ ) 表示测试用例的个数。

**对于每组测试用例：**

第一行，输入三个整数 $n$ , $m$ , $k$ ( $1 \leq k \leq n \leq 10^9$ , $1 \leq m \leq 10^5$ , $m \leq n$ )$\\$

第二行，$m$ 个整数 $a_1,a_2,\cdots,a_m$ ( $1\leq a_i\leq n$ ) 并且保证 $ a_1 + a_2 + \ldots + a_m = n $

保证每组测试用例中的 $m$ 的和不超过 $10^5$。

## 输出格式

对于每组测试用例，如果有至少一种涂色的方案，输出"YES"；否则输出"NO"。

输出不区分大小写。

## 说明/提示

第一个测试用例中，没有任何涂色的方案满足所有要求。

第二个测试用例中，可以将纸条涂成$(1,2,1,2,3,4,3,4,5,6,5,6)$，对于每两个连续的格子，颜色都是互不相同的。

## 样例 #1

### 输入

```
2
12 6 2
1 1 1 1 1 7
12 6 2
2 2 2 2 2 2
```

### 输出

```
NO
YES
```



---

---
title: "Dora and Search"
layout: "post"
diff: 普及/提高-
pid: CF1793C
tag: ['贪心', '双指针 two-pointer']
---

# Dora and Search

## 题目描述

As you know, the girl Dora is always looking for something. This time she was given a permutation, and she wants to find such a subsegment of it that none of the elements at its ends is either the minimum or the maximum of the entire subsegment. More formally, you are asked to find the numbers $ l $ and $ r $ $ (1 \leq l \leq r \leq n) $ such that $ a_l \neq \min(a_l, a_{l + 1}, \ldots, a_r) $ , $ a_l \neq \max(a_l, a_{l + 1}, \ldots, a_r) $ and $ a_r \neq \min(a_l, a_{l + 1}, \ldots, a_r) $ , $ a_r \neq \max(a_l, a_{l + 1}, \ldots, a_r) $ .

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

Help Dora find such a subsegment, or tell her that such a subsegment does not exist.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Description of the test cases follows.

For each test case, the first line contains one integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of permutation.

The second line contains $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq n $ ) — the elements of permutation.

It is guarented that the sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ -1 $ if the desired subsegment does not exist.

Otherwise, output two indexes $ l, r $ such that $ [a_{l}, a_{l + 1}, \ldots, a_{r}] $ satisfies all conditions.

If there are several solutions, then output any of them.

## 说明/提示

In the first and fourth test cases, it can be shown that there are no desired subsegments.

In the second test case, the subsegment $ [1, 4] $ satisfies all the conditions, because $ \max(a_1, a_2, a_3, a_4) = 4, \min(a_1, a_2, a_3, a_4) = 1 $ , as we see, all the conditions are met.

In the third test case, the subsegment $ [2, 6] $ also satisfies all the conditions described.

## 样例 #1

### 输入

```
4
3
1 2 3
4
2 1 4 3
7
1 3 2 4 6 5 7
6
2 3 6 5 4 1
```

### 输出

```
-1
1 4
2 6
-1
```



---

---
title: "Set To Max (Easy Version)"
layout: "post"
diff: 普及/提高-
pid: CF1904D1
tag: ['贪心']
---

# Set To Max (Easy Version)

## 题目描述

This is the easy version of the problem. The only differences between the two versions of this problem are the constraints on $ n $ and the time limit. You can make hacks only if all versions of the problem are solved.

You are given two arrays $ a $ and $ b $ of length $ n $ .

You can perform the following operation some (possibly zero) times:

1. choose $ l $ and $ r $ such that $ 1 \leq l \leq r \leq n $ .
2. let $ x=\max(a_l,a_{l+1},\ldots,a_r) $ .
3. for all $ l \leq i \leq r $ , set $ a_i := x $ .

Determine if you can make array $ a $ equal to array $ b $ .

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 1000 $ ) — the length of the arrays.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the elements of array $ a $ .

The third line contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le n $ ) — the elements of array $ b $ .

It is guaranteed that the sum of $ n^2 $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output "YES" (without quotes) if you can make $ a $ into $ b $ using any number of operations, and "NO" (without quotes) otherwise.

You can output "YES" and "NO" in any case (for example, strings "yES", "yes" and "Yes" will be recognized as a positive response).

## 说明/提示

In the first test case, we can achieve array $ b $ by applying a single operation: $ (l,r)=(2,3) $ .

In the second test case, it can be shown we cannot achieve array $ b $ in any amount of operations.

In the third test case, we can achieve array $ b $ by applying two operations: $ (l,r)=(2,5) $ . followed by $ (l,r)=(1,3) $ .

In the fourth and fifth test cases, it can be shown we cannot achieve array $ b $ in any amount of operations.

## 样例 #1

### 输入

```
5
5
1 2 3 2 4
1 3 3 2 4
5
3 4 2 2 4
3 4 3 4 4
5
3 2 1 1 1
3 3 3 2 2
2
1 1
1 2
3
1 1 2
2 1 2
```

### 输出

```
YES
NO
YES
NO
NO
```



---

---
title: "Heavy Intervals"
layout: "post"
diff: 普及/提高-
pid: CF1909C
tag: ['贪心']
---

# Heavy Intervals

## 题目描述

[Shiki - Pure Ruby](https://soundcloud.com/shiki-8/pure-rubyversoundcloud)

⠀



You have $ n $ intervals $ [l_1, r_1], [l_2, r_2], \dots, [l_n, r_n] $ , such that $ l_i < r_i $ for each $ i $ , and all the endpoints of the intervals are distinct.

The $ i $ -th interval has weight $ c_i $ per unit length. Therefore, the weight of the $ i $ -th interval is $ c_i \cdot (r_i - l_i) $ .

You don't like large weights, so you want to make the sum of weights of the intervals as small as possible. It turns out you can perform all the following three operations:

- rearrange the elements in the array $ l $ in any order;
- rearrange the elements in the array $ r $ in any order;
- rearrange the elements in the array $ c $ in any order.

However, after performing all of the operations, the intervals must still be valid (i.e., for each $ i $ , $ l_i < r_i $ must hold).

What's the minimum possible sum of weights of the intervals after performing the operations?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of intervals.

The second line of each test case contains $ n $ integers $ l_1, l_2, \ldots, l_n $ ( $ 1 \le l_i \le 2 \cdot 10^5 $ ) — the left endpoints of the initial intervals.

The third line of each test case contains $ n $ integers $ r_1, r_2, \ldots, r_n $ ( $ l_i < r_i \le 2 \cdot 10^5 $ ) — the right endpoints of the initial intervals.

It is guaranteed that $ \{l_1, l_2, \dots, l_n, r_1, r_2, \dots, r_n\} $ are all distinct.

The fourth line of each test case contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 1 \le c_i \le 10^7 $ ) — the initial weights of the intervals per unit length.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer: the minimum possible sum of weights of the intervals after your operations.

## 说明/提示

In the first test case, you can make

- $ l = [8, 3] $ ;
- $ r = [23, 12] $ ;
- $ c = [100, 100] $ .

In that case, there are two intervals:

- interval $ [8, 23] $ with weight $ 100 $ per unit length, and $ 100 \cdot (23-8) = 1500 $ in total;
- interval $ [3, 12] $ with weight $ 100 $ per unit length, and $ 100 \cdot (12-3) = 900 $ in total.

The sum of the weights is $ 2400 $ . It can be shown that there is no configuration of final intervals whose sum of weights is less than $ 2400 $ .

In the second test case, you can make

- $ l = [1, 2, 5, 20] $ ;
- $ r = [3, 4, 10, 30] $ ;
- $ c = [3, 3, 2, 2] $ .

In that case, there are four intervals:

- interval $ [1, 3] $ with weight $ 3 $ per unit length, and $ 3 \cdot (3-1) = 6 $ in total;
- interval $ [2, 4] $ with weight $ 3 $ per unit length, and $ 3 \cdot (4-2) = 6 $ in total;
- interval $ [5, 10] $ with weight $ 2 $ per unit length, and $ 2 \cdot (10-5) = 10 $ in total;
- interval $ [20, 30] $ with weight $ 2 $ per unit length, and $ 2 \cdot (30-20) = 20 $ in total.

The sum of the weights is $ 42 $ . It can be shown that there is no configuration of final intervals whose sum of weights is less than $ 42 $ .

## 样例 #1

### 输入

```
2
2
8 3
12 23
100 100
4
20 1 2 5
30 4 3 10
2 3 2 3
```

### 输出

```
2400
42
```



---

---
title: "Game with Marbles (Easy Version)"
layout: "post"
diff: 普及/提高-
pid: CF1914E1
tag: ['贪心', '博弈论']
---

# Game with Marbles (Easy Version)

## 题目描述

The easy and hard versions of this problem differ only in the constraints on the number of test cases and $ n $ . In the easy version, the number of test cases does not exceed $ 10^3 $ , and $ n $ does not exceed $ 6 $ .

Recently, Alice and Bob were given marbles of $ n $ different colors by their parents. Alice has received $ a_1 $ marbles of color $ 1 $ , $ a_2 $ marbles of color $ 2 $ ,..., $ a_n $ marbles of color $ n $ . Bob has received $ b_1 $ marbles of color $ 1 $ , $ b_2 $ marbles of color $ 2 $ , ..., $ b_n $ marbles of color $ n $ . All $ a_i $ and $ b_i $ are between $ 1 $ and $ 10^9 $ .

After some discussion, Alice and Bob came up with the following game: players take turns, starting with Alice. On their turn, a player chooses a color $ i $ such that both players have at least one marble of that color. The player then discards one marble of color $ i $ , and their opponent discards all marbles of color $ i $ . The game ends when there is no color $ i $ such that both players have at least one marble of that color.

The score in the game is the difference between the number of remaining marbles that Alice has and the number of remaining marbles that Bob has at the end of the game. In other words, the score in the game is equal to $ (A-B) $ , where $ A $ is the number of marbles Alice has and $ B $ is the number of marbles Bob has at the end of the game. Alice wants to maximize the score, while Bob wants to minimize it.

Calculate the score at the end of the game if both players play optimally.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^3 $ ) — the number of test cases.

Each test case consists of three lines:

- the first line contains a single integer $ n $ ( $ 2 \le n \le 6 $ ) — the number of colors;
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ), where $ a_i $ is the number of marbles of the $ i $ -th color that Alice has;
- the third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le 10^9 $ ), where $ b_i $ is the number of marbles of the $ i $ -th color that Bob has.

## 输出格式

For each test case, output a single integer — the score at the end of the game if both Alice and Bob act optimally.

## 说明/提示

In the first example, one way to achieve a score of $ 1 $ is as follows:

1. Alice chooses color $ 1 $ , discards $ 1 $ marble. Bob also discards $ 1 $ marble;
2. Bob chooses color $ 3 $ , discards $ 1 $ marble. Alice also discards $ 1 $ marble;
3. Alice chooses color $ 2 $ , discards $ 1 $ marble, and Bob discards $ 2 $ marble.

As a result, Alice has $ a = [3, 1, 0] $ remaining, and Bob has $ b = [0, 0, 3] $ remaining. The score is $ 3 + 1 - 3 = 1 $ .

It can be shown that neither Alice nor Bob can achieve a better score if both play optimally.

In the second example, Alice can first choose color $ 1 $ , then Bob will choose color $ 4 $ , after which Alice will choose color $ 2 $ , and Bob will choose color $ 3 $ . It can be shown that this is the optimal game.

## 样例 #1

### 输入

```
5
3
4 2 1
1 2 4
4
1 20 1 20
100 15 10 20
5
1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1
3
5 6 5
2 1 7
6
3 2 4 2 5 5
9 4 7 9 2 5
```

### 输出

```
1
-9
2999999997
8
-6
```



---

---
title: "Game with Marbles (Hard Version)"
layout: "post"
diff: 普及/提高-
pid: CF1914E2
tag: ['贪心', '博弈论']
---

# Game with Marbles (Hard Version)

## 题目描述

The easy and hard versions of this problem differ only in the constraints on the number of test cases and $ n $ . In the hard version, the number of test cases does not exceed $ 10^4 $ , and the sum of values of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Furthermore, there are no additional constraints on $ n $ in a single test case.

Recently, Alice and Bob were given marbles of $ n $ different colors by their parents. Alice has received $ a_1 $ marbles of color $ 1 $ , $ a_2 $ marbles of color $ 2 $ ,..., $ a_n $ marbles of color $ n $ . Bob has received $ b_1 $ marbles of color $ 1 $ , $ b_2 $ marbles of color $ 2 $ , ..., $ b_n $ marbles of color $ n $ . All $ a_i $ and $ b_i $ are between $ 1 $ and $ 10^9 $ .

After some discussion, Alice and Bob came up with the following game: players take turns, starting with Alice. On their turn, a player chooses a color $ i $ such that both players have at least one marble of that color. The player then discards one marble of color $ i $ , and their opponent discards all marbles of color $ i $ . The game ends when there is no color $ i $ such that both players have at least one marble of that color.

The score in the game is the difference between the number of remaining marbles that Alice has and the number of remaining marbles that Bob has at the end of the game. In other words, the score in the game is equal to $ (A-B) $ , where $ A $ is the number of marbles Alice has and $ B $ is the number of marbles Bob has at the end of the game. Alice wants to maximize the score, while Bob wants to minimize it.

Calculate the score at the end of the game if both players play optimally.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of three lines:

- the first line contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of colors;
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ), where $ a_i $ is the number of marbles of the $ i $ -th color that Alice has;
- the third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le 10^9 $ ), where $ b_i $ is the number of marbles of the $ i $ -th color that Bob has.

Additional constraint on the input: the sum of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the score at the end of the game if both Alice and Bob act optimally.

## 说明/提示

In the first example, one way to achieve a score of $ 1 $ is as follows:

1. Alice chooses color $ 1 $ , discards $ 1 $ marble. Bob also discards $ 1 $ marble;
2. Bob chooses color $ 3 $ , discards $ 1 $ marble. Alice also discards $ 1 $ marble;
3. Alice chooses color $ 2 $ , discards $ 1 $ marble, and Bob discards $ 2 $ marble.

As a result, Alice has $ a = [3, 1, 0] $ remaining, and Bob has $ b = [0, 0, 3] $ remaining. The score is $ 3 + 1 - 3 = 1 $ .

It can be shown that neither Alice nor Bob can achieve a better score if both play optimally.

In the second example, Alice can first choose color $ 1 $ , then Bob will choose color $ 4 $ , after which Alice will choose color $ 2 $ , and Bob will choose color $ 3 $ . It can be shown that this is the optimal game.

## 样例 #1

### 输入

```
5
3
4 2 1
1 2 4
4
1 20 1 20
100 15 10 20
5
1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1
3
5 6 5
2 1 7
6
3 2 4 2 5 5
9 4 7 9 2 5
```

### 输出

```
1
-9
2999999997
8
-6
```



---

---
title: "Watering an Array"
layout: "post"
diff: 普及/提高-
pid: CF1917C
tag: ['贪心']
---

# Watering an Array

## 题目描述

You have an array of integers $ a_1, a_2, \ldots, a_n $ of length $ n $ . On the $ i $ -th of the next $ d $ days you are going to do exactly one of the following two actions:

- Add $ 1 $ to each of the first $ b_i $ elements of the array $ a $ (i.e., set $ a_j := a_j + 1 $ for each $ 1 \le j \le b_i $ ).
- Count the elements which are equal to their position (i.e., the $ a_j = j $ ). Denote the number of such elements as $ c $ . Then, you add $ c $ to your score, and reset the entire array $ a $ to a $ 0 $ -array of length $ n $ (i.e., set $ [a_1, a_2, \ldots, a_n] := [0, 0, \ldots, 0] $ ).

Your score is equal to $ 0 $ in the beginning. Note that on each day you should perform exactly one of the actions above: you cannot skip a day or perform both actions on the same day.

What is the maximum score you can achieve at the end?

Since $ d $ can be quite large, the sequence $ b $ is given to you in the compressed format:

- You are given a sequence of integers $ v_1, v_2, \ldots, v_k $ . The sequence $ b $ is a concatenation of infinitely many copies of $ v $ : $ b = [v_1, v_2, \ldots, v_k, v_1, v_2, \ldots, v_k, \ldots] $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^3 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ k $ and $ d $ ( $ 1 \le n \le 2000 $ , $ 1 \le k \le 10^5 $ , $ k \le d \le 10^9 $ ) — the length of the array $ a $ , the length of the sequence $ v $ and the number of days you are going to perform operations on.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le n $ ) — the array $ a $ .

The third line of each test case contains $ k $ integers $ v_1, v_2, \ldots, v_k $ ( $ 1 \le v_i \le n $ ) — the sequence $ v $ .

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 2000 $ and the sum of $ k $ over all test cases doesn't exceed $ 10^5 $ .

## 输出格式

For each test case, output one integer: the maximum score you can achieve at the end of the $ d $ -th day.

## 说明/提示

In the first test case, the sequence $ b $ is equal to $ [1, 3, 2, 3, 1, 3, 2, 3, \ldots] $ and one of the optimal solutions for this case is as follows:

- Perform the operation of the second type on the $ 1 $ -st day: your score increases by $ 3 $ and array $ a $ becomes equal to $ [0, 0, 0] $ .
- Perform the operation of the first type on the $ 2 $ -nd day: array $ a $ becomes equal to $ [1, 1, 1] $ .
- Perform the operation of the first type on the $ 3 $ -rd day: array $ a $ becomes equal to $ [2, 2, 1] $ .
- Perform the operation of the second type on the $ 4 $ -th day: your score increases by $ 1 $ and array $ a $ becomes equal to $ [0, 0, 0] $ .

It can be shown that it is impossible to score more than $ 4 $ , so the answer is $ 4 $ .

In the second test case, the sequence $ b $ is equal to $ [6, 6, 6, 6, \ldots] $ . One of the ways to score $ 3 $ is to perform operations of the first type on the $ 1 $ -st and the $ 3 $ -rd days and to perform an operation of the second type on the $ 2 $ -nd day.

## 样例 #1

### 输入

```
5
3 4 4
1 2 3
1 3 2 3
6 2 3
6 1 2 4 1 5
6 6
5 1 1
0 5 0 5 0
5
1 1 1
1
1
3 4 6
1 2 3
1 3 2 3
```

### 输出

```
4
3
0
1
5
```



---

---
title: "Grouping Increases"
layout: "post"
diff: 普及/提高-
pid: CF1919C
tag: ['贪心']
---

# Grouping Increases

## 题目描述

You are given an array $ a $ of size $ n $ . You will do the following process to calculate your penalty:

1. Split array $ a $ into two (possibly empty) subsequences $ ^\dagger $ $ s $ and $ t $ such that every element of $ a $ is either in $ s $ or $ t^\ddagger $ .
2. For an array $ b $ of size $ m $ , define the penalty $ p(b) $ of an array $ b $ as the number of indices $ i $ between $ 1 $ and $ m - 1 $ where $ b_i < b_{i + 1} $ .
3. The total penalty you will receive is $ p(s) + p(t) $ .

If you perform the above process optimally, find the minimum possible penalty you will receive.

 $ ^\dagger $ A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by the deletion of several (possibly, zero or all) elements.

 $ ^\ddagger $ Some valid ways to split array $ a=[3,1,4,1,5] $ into $ (s,t) $ are $ ([3,4,1,5],[1]) $ , $ ([1,1],[3,4,5]) $ and $ ([\,],[3,1,4,1,5]) $ while some invalid ways to split $ a $ are $ ([3,4,5],[1]) $ , $ ([3,1,4,1],[1,5]) $ and $ ([1,3,4],[5,1]) $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le 2\cdot 10^5 $ ) — the size of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output a single integer representing the minimum possible penalty you will receive.

## 说明/提示

In the first test case, a possible way to split $ a $ is $ s=[2,4,5] $ and $ t=[1,3] $ . The penalty is $ p(s)+p(t)=2 + 1 =3 $ .

In the second test case, a possible way to split $ a $ is $ s=[8,3,1] $ and $ t=[2,1,7,4,3] $ . The penalty is $ p(s)+p(t)=0 + 1 =1 $ .

In the third test case, a possible way to split $ a $ is $ s=[\,] $ and $ t=[3,3,3,3,3] $ . The penalty is $ p(s)+p(t)=0 + 0 =0 $ .

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
8
8 2 3 1 1 7 4 3
5
3 3 3 3 3
1
1
2
2 1
```

### 输出

```
3
1
0
0
0
```



---

---
title: "Closest Cities"
layout: "post"
diff: 普及/提高-
pid: CF1922C
tag: ['贪心', '前缀和']
---

# Closest Cities

## 题目描述

There are $ n $ cities located on the number line, the $ i $ -th city is in the point $ a_i $ . The coordinates of the cities are given in ascending order, so $ a_1 < a_2 < \dots < a_n $ .

The distance between two cities $ x $ and $ y $ is equal to $ |a_x - a_y| $ .

For each city $ i $ , let's define the closest city $ j $ as the city such that the distance between $ i $ and $ j $ is not greater than the distance between $ i $ and each other city $ k $ . For example, if the cities are located in points $ [0, 8, 12, 15, 20] $ , then:

- the closest city to the city $ 1 $ is the city $ 2 $ ;
- the closest city to the city $ 2 $ is the city $ 3 $ ;
- the closest city to the city $ 3 $ is the city $ 4 $ ;
- the closest city to the city $ 4 $ is the city $ 3 $ ;
- the closest city to the city $ 5 $ is the city $ 4 $ .

The cities are located in such a way that for every city, the closest city is unique. For example, it is impossible for the cities to be situated in points $ [1, 2, 3] $ , since this would mean that the city $ 2 $ has two closest cities ( $ 1 $ and $ 3 $ , both having distance $ 1 $ ).

You can travel between cities. Suppose you are currently in the city $ x $ . Then you can perform one of the following actions:

- travel to any other city $ y $ , paying $ |a_x - a_y| $ coins;
- travel to the city which is the closest to $ x $ , paying $ 1 $ coin.

You are given $ m $ queries. In each query, you will be given two cities, and you have to calculate the minimum number of coins you have to spend to travel from one city to the other city.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case is given in the following format:

- the first line contains one integer $ n $ ( $ 2 \le n \le 10^5 $ );
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_1 < a_2 < \dots < a_n \le 10^9 $ );
- the third line contains one integer $ m $ ( $ 1 \le m \le 10^5 $ );
- then $ m $ lines follow; the $ i $ -th of them contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le n $ ; $ x_i \ne y_i $ ), denoting that in the $ i $ -th query, you have to calculate the minimum number of coins you have to spend to travel from the city $ x_i $ to the city $ y_i $ .

Additional constraints on the input:

- in every test case, for each city, the closest city is determined uniquely;
- the sum of $ n $ over all test cases does not exceed $ 10^5 $ ;
- the sum of $ m $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each query, print one integer — the minimum number of coins you have to spend.

## 说明/提示

Let's consider the first two queries in the example from the statement:

- in the first query, you are initially in the city $ 1 $ . You can travel to the closest city (which is the city $ 2 $ ), paying $ 1 $ coin. Then you travel to the closest city (which is the city $ 3 $ ) again, paying $ 1 $ coin. Then you travel to the closest city (which is the city $ 4 $ ) again, paying $ 1 $ coin. In total, you spend $ 3 $ coins to get from the city $ 1 $ to the city $ 4 $ ;
- in the second query, you can use the same way to get from the city $ 1 $ to the city $ 4 $ , and then spend $ 5 $ coins to travel from the city $ 4 $ to the city $ 5 $ .

## 样例 #1

### 输入

```
1
5
0 8 12 15 20
5
1 4
1 5
3 4
3 2
5 1
```

### 输出

```
3
8
1
4
14
```



---

---
title: "Did We Get Everything Covered?"
layout: "post"
diff: 普及/提高-
pid: CF1924A
tag: ['贪心']
---

# Did We Get Everything Covered?

## 题目描述

You are given two integers $ n $ and $ k $ along with a string $ s $ .

Your task is to check whether all possible strings of length $ n $ that can be formed using the first $ k $ lowercase English alphabets occur as a subsequence of $ s $ . If the answer is NO, you also need to print a string of length $ n $ that can be formed using the first $ k $ lowercase English alphabets which does not occur as a subsequence of $ s $ .

If there are multiple answers, you may print any of them.

Note: A string $ a $ is called a subsequence of another string $ b $ if $ a $ can be obtained by deleting some (possibly zero) characters from $ b $ without changing the order of the remaining characters.

## 输入格式

The first line of input contains a single integer $ t \, (1 \le t \le 10^5) $ , the number of test cases.

The first line of each test case contains $ 3 $ integers $ n \, (1 \le n \le 26), \: k \, (1 \le k \le 26), \: m \, (1 \le m \le 1000) $ , where $ n $ and $ k $ are the same as described in the input and $ m $ is the length of the string $ s $ .

The second line of each test case contains a single string $ s $ of length $ m $ , comprising only of the first $ k $ lowercase English alphabets.

It is guaranteed that the sum of $ m $ and the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print YES if all possible strings of length $ n $ that can be formed using the first $ k $ lowercase English alphabets occur as a subsequence of $ s $ , else print NO.

If your answer is NO, print a string of length $ n $ that can be formed using the first $ k $ lowercase English alphabets which does not occur as a subsequence of $ s $ in the next line.

You may print each letter of YES or NO in any case (for example, YES, yES, YeS will all be recognized as a positive answer).

## 说明/提示

For the first test case, all possible strings (aa, ab, ba, bb) of length $ 2 $ that can be formed using the first $ 2 $ English alphabets occur as a subsequence of abba.

For the second test case, the string aa is not a subsequence of abb.

## 样例 #1

### 输入

```
3
2 2 4
abba
2 2 3
abb
3 3 10
aabbccabab
```

### 输出

```
YES
NO
aa
NO
ccc
```



---

---
title: "Lexicographically Largest"
layout: "post"
diff: 普及/提高-
pid: CF1930C
tag: ['贪心']
---

# Lexicographically Largest

## 题目描述

Stack has an array $ a $ of length $ n $ . He also has an empty set $ S $ . Note that $ S $ is not a multiset.

He will do the following three-step operation exactly $ n $ times:

1. Select an index $ i $ such that $ 1 \leq i \leq |a| $ .
2. Insert $ ^\dagger $ $ a_i + i $ into $ S $ .
3. Delete $ a_i $ from $ a $ . Note that the indices of all elements to the right of $ a_i $ will decrease by $ 1 $ .

Note that after $ n $ operations, $ a $ will be empty.

Stack will now construct a new array $ b $ which is $ S $ sorted in decreasing order. Formally, $ b $ is an array of size $ |S| $ where $ b_i $ is the $ i $ -th largest element of $ S $ for all $ 1 \leq i \leq |S| $ .

Find the lexicographically largest $ ^\ddagger $ $ b $ that Stack can make.

 $ ^\dagger $ A set can only contain unique elements. Inserting an element that is already present in a set will not change the elements of the set.

 $ ^\ddagger $ An array $ p $ is lexicographically larger than a sequence $ q $ if and only if one of the following holds:

- $ q $ is a prefix of $ p $ , but $ p \ne q $ ; or
- in the first position where $ p $ and $ q $ differ, the array $ p $ has a larger element than the corresponding element in $ q $ .

Note that $ [3,1,4,1,5] $ is lexicographically larger than $ [3,1,3] $ , $ [\,] $ , and $ [3,1,4,1] $ but not $ [3,1,4,1,5,9] $ , $ [3,1,4,1,5] $ , and $ [4] $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 3 \cdot 10^5 $ ) — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_{n} $ ( $ 1 \leq a_i \leq 10^9 $ ) — the elements of array $ a $ .

The sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output the lexicographically largest $ b $ .

## 说明/提示

In the first test case, select $ i=1 $ in the first operation, insert $ a_1 + 1 = 3 $ in $ S $ , and delete $ a_1 $ from $ a $ . After the first operation, $ a $ becomes $ a=[1] $ . In the second operation, we select $ i=1 $ again and insert $ a_1 + 1 = 2 $ in $ S $ . Thus $ S=\{2, 3\} $ , and $ b = [3, 2] $ .

Note that if you select $ i=2 $ in the first operation, and $ i=1 $ in the second operation, $ S=\{3\} $ as $ 3 $ will be inserted twice, resulting in $ b=[3] $ .

As $ [3,2] $ is lexicographically larger than $ [3] $ , we should select $ i=1 $ in the first operation.

In the second test case, in each operation, select the last element.

## 样例 #1

### 输入

```
3
2
2 1
5
1 100 1000 1000000 1000000000
3
6 4 8
```

### 输出

```
3 2 
1000000005 1000004 1003 102 2 
11 7 6
```



---

---
title: "Anna and the Valentine's Day Gift"
layout: "post"
diff: 普及/提高-
pid: CF1931E
tag: ['贪心']
---

# Anna and the Valentine's Day Gift

## 题目描述

Sasha gave Anna a list $ a $ of $ n $ integers for Valentine's Day. Anna doesn't need this list, so she suggests destroying it by playing a game.

Players take turns. Sasha is a gentleman, so he gives Anna the right to make the first move.

- On her turn, Anna must choose an element $ a_i $ from the list and reverse the sequence of its digits. For example, if Anna chose the element with a value of $ 42 $ , it would become $ 24 $ ; if Anna chose the element with a value of $ 1580 $ , it would become $ 851 $ . Note that leading zeros are removed. After such a turn, the number of elements in the list does not change.
- On his turn, Sasha must extract two elements $ a_i $ and $ a_j $ ( $ i \ne j $ ) from the list, concatenate them in any order and insert the result back into the list. For example, if Sasha chose the elements equal to $ 2007 $ and $ 19 $ , he would remove these two elements from the list and add the integer $ 200719 $ or $ 192007 $ . After such a turn, the number of elements in the list decreases by $ 1 $ .

Players can't skip turns. The game ends when Sasha can't make a move, i.e. after Anna's move there is exactly one number left in the list. If this integer is not less than $ 10^m $ (i.e., $ \ge 10^m $ ), Sasha wins. Otherwise, Anna wins.

It can be shown that the game will always end. Determine who will win if both players play optimally.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Then follows the description of the test cases.

The first line of each test case contains integers $ n $ , $ m $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le m \le 2 \cdot 10^6 $ ) — the number of integers in the list and the parameter determining when Sasha wins.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the list that Sasha gave to Anna.

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output:

- "Sasha", if Sasha wins with optimal play;
- "Anna", if Anna wins with optimal play.

## 说明/提示

Consider the first test case.

Anna can reverse the integer $ 2 $ , then Sasha can concatenate the integers $ 2 $ and $ 14 $ , obtaining the integer $ 214 $ , which is greater than $ 10^2 = 100 $ . If Anna had reversed the integer $ 14 $ , Sasha would have concatenated the integers $ 41 $ and $ 2 $ , obtaining the integer $ 412 $ , which is greater than $ 10^2 = 100 $ . Anna has no other possible moves, so she loses.

## 样例 #1

### 输入

```
9
2 2
14 2
3 5
9 56 1
4 10
1 2007 800 1580
4 5
5000 123 30 4
10 10
6 4 6 2 3 1 10 9 10 7
1 1
6
1 1
10
8 9
1 2 9 10 10 2 10 2
4 5
10 10 10 10
```

### 输出

```
Sasha
Anna
Anna
Sasha
Sasha
Anna
Anna
Anna
Sasha
```



---

---
title: "Card Game"
layout: "post"
diff: 普及/提高-
pid: CF1932D
tag: ['模拟', '贪心']
---

# Card Game

## 题目描述

两名玩家正在玩在线纸牌游戏。游戏使用一副  $32$ 张牌进行。每张牌都有花色和数字。有四种花色：梅花、方块、红心和黑桃。用字符 `C`、`D`、`H` 和 `S` 分别表示它们。共有 8 种数字，按递增顺序为 `2`、`3`、`4`、`5`、`6`、`7`、`8`、`9`。

每张牌由两个字母表示：其等级和花色。例如，红心 8 可以表示为 `8H`。

在游戏开始时，会选择一种花色作为王牌花色。

在每一轮中，玩家的操作如下：第一个玩家在桌子上放一张牌，第二个玩家必须用自己的一张牌打败这张牌。之后，两张牌都被移动到弃牌堆中。

一张牌可以打败另一张牌，如果两张牌都具有相同的花色，并且第一张牌的等级比第二张牌高。例如，方块 8 可以打败方块 4。此外，王牌可以打败任何非王牌牌，无论牌的等级如何，例如，如果王牌花色是梅花 (`C`)，那么梅花 3 可以打败方块 9。请注意，王牌只能被等级更高的王牌打败。

游戏中进行了 $n$ 轮，因此弃牌堆现在包含 $2n$ 张牌。你想要重建游戏中进行的轮次，但是弃牌堆中的牌已经洗牌。找到可能在游戏中玩过的 $n$ 轮的任何可能顺序。

## 输入格式

第一行包含整数 $t$（$1\le t\le100$），表示测试数据数量。接下来是 $t$ 个测试数据。

每个测试数据的第一行包含整数 $n$（$1\le n\le16$）。

每个测试数据的第二行包含一个字符，即王牌花色。它是 `CDHS` 中的一个。

每个测试数据的第三行包含 $2n$ 张牌的描述。每张牌由一个两个字符的字符串描述，第一个字符是牌的等级，是 `23456789` 中的一个，第二个字符是牌的花色，是 `CDHS` 中的一个。所有牌都是不同的。

## 输出格式

对于每个测试用例，输出答案：

打印 $n$ 行。在每一行中，以与输入相同的格式打印两张牌的描述：第一张牌是第一个玩家打出的牌，然后是第二个玩家用来打败它的牌。
如果没有解决方案，则打印一行 `IMPOSSIBLE`。
如果有多个解决方案，则打印其中任何一个。

## 样例 #1

### 输入

```
8
3
S
3C 9S 4C 6D 3S 7S
2
C
3S 5D 9S 6H
1
H
6C 5D
1
S
7S 3S
1
H
9S 9H
1
S
9S 9H
1
C
9D 8H
2
C
9C 9S 6H 8C
```

### 输出

```
3C 4C
6D 9S
3S 7S
IMPOSSIBLE
IMPOSSIBLE
3S 7S
9S 9H
9H 9S
IMPOSSIBLE
6H 9C
9S 8C
```



---

---
title: "Binary Path"
layout: "post"
diff: 普及/提高-
pid: CF1937B
tag: ['动态规划 DP', '贪心']
---

# Binary Path

## 题目描述

You are given a $ 2 \times n $ grid filled with zeros and ones. Let the number at the intersection of the $ i $ -th row and the $ j $ -th column be $ a_{ij} $ .

There is a grasshopper at the top-left cell $ (1, 1) $ that can only jump one cell right or downwards. It wants to reach the bottom-right cell $ (2, n) $ . Consider the binary string of length $ n+1 $ consisting of numbers written in cells of the path without changing their order.

Your goal is to:

1. Find the lexicographically smallest $ ^\dagger $ string you can attain by choosing any available path;
2. Find the number of paths that yield this lexicographically smallest string.

 $ ^\dagger $ If two strings $ s $ and $ t $ have the same length, then $ s $ is lexicographically smaller than $ t $ if and only if in the first position where $ s $ and $ t $ differ, the string $ s $ has a smaller element than the corresponding element in $ t $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ).

The second line of each test case contains a binary string $ a_{11} a_{12} \ldots a_{1n} $ ( $ a_{1i} $ is either $ 0 $ or $ 1 $ ).

The third line of each test case contains a binary string $ a_{21} a_{22} \ldots a_{2n} $ ( $ a_{2i} $ is either $ 0 $ or $ 1 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output two lines:

1. The lexicographically smallest string you can attain by choosing any available path;
2. The number of paths that yield this string.

## 说明/提示

In the first test case, the lexicographically smallest string is $ \mathtt{000} $ . There are two paths that yield this string:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1937B/28bc26c21acb39dafc863512440b57a82f70d617.png)In the second test case, the lexicographically smallest string is $ \mathtt{11000} $ . There is only one path that yields this string:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1937B/f024d427300a33d2f71c9946e45249754a59348c.png)

## 样例 #1

### 输入

```
3
2
00
00
4
1101
1100
8
00100111
11101101
```

### 输出

```
000
2
11000
1
001001101
4
```



---

---
title: "Maximum Sum"
layout: "post"
diff: 普及/提高-
pid: CF1946B
tag: ['动态规划 DP', '贪心']
---

# Maximum Sum

## 题目描述

You have an array $ a $ of $ n $ integers.

You perform exactly $ k $ operations on it. In one operation, you select any contiguous subarray of the array $ a $ (possibly empty) and insert the sum of this subarray anywhere in the array.

Your task is to find the maximum possible sum of the array after $ k $ such operations.

As this number can be very large, output the answer modulo $ 10^9 + 7 $ .

Reminder: the remainder of a number $ x $ modulo $ p $ is the smallest non-negative $ y $ such that there exists an integer $ q $ and $ x = p \cdot q + y $ .

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 2 \cdot 10^5 $ ) — the length of the array $ a $ and the number of operations, respectively.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — the array $ a $ itself.

It is guaranteed that the sum of the values of $ n $ and $ k $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test, output a single integer — the maximum sum of the array that can be obtained after $ k $ operations modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case, it is advantageous to take an empty subarray of the array twice and insert the sum of the empty subarray (zero) anywhere, then the sum of the resulting array will be $ (-4) + (-7) + 0 + 0 = -11 $ , modulo $ 10^9 + 7 $ this is $ 999\,999\,996 $ .

In the second test case, it is advantageous to take the sum of the entire array three times and place it anywhere in the array, then one of the possible sequences of actions: \[ $ 2, 2, 8 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12, 24 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12, 24, 48 $ \], the sum of the final array is $ 2 + 2 + 8 + 12 + 24 + 48 = 96 $ .

In the fourth test case, it is advantageous to take a subarray of the array consisting of the first three numbers (i.e. consisting of the numbers $ 4, -2 $ and $ 8 $ ) and insert its sum at the beginning of the array, thereby obtaining the array \[ $ 10, 4, -2, 8, -12, 9 $ \], the sum of this array is $ 17 $ .

In the seventh test case, it will always be advantageous for us to take an empty subarray of the array. In this case, the sum of the resulting array will not differ from the sum of the original. The answer will be the sum of the original array, taken modulo — $ 42 $ , because $ (-6 \cdot (10^9 + 7) + 42 = -6\,000\,000\,000) $ .

## 样例 #1

### 输入

```
12
2 2
-4 -7
3 3
2 2 8
1 7
7
5 1
4 -2 8 -12 9
7 4
8 14 -9 6 0 -1 3
7 100
5 3 -8 12 -5 -9 3
6 1000
-1000000000 -1000000000 -1000000000 -1000000000 -1000000000 -1000000000
2 1
1000000000 8
5 4
0 0 0 0 0
6 10
48973 757292 58277 -38574 27475 999984
7 1
-1000 1000 -1000 1000 -1000 1000 -1000
10 10050
408293874 -3498597 7374783 295774930 -48574034 26623784 498754833 -294875830 283045804 85938045
```

### 输出

```
999999996
96
896
17
351
716455332
42
2
0
897909241
0
416571966
```



---

---
title: "Ticket Hoarding"
layout: "post"
diff: 普及/提高-
pid: CF1951C
tag: ['贪心']
---

# Ticket Hoarding

## 题目描述

[Maître Gims - Est-ce que tu m'aimes ?](https://youtu.be/6TpyRE_juyA)

ඞ



As the CEO of a startup company, you want to reward each of your $ k $ employees with a ticket to the upcoming concert. The tickets will be on sale for $ n $ days, and by some time travelling, you have predicted that the price per ticket at day $ i $ will be $ a_i $ . However, to prevent ticket hoarding, the concert organizers have implemented the following measures:

- A person may purchase no more than $ m $ tickets per day.
- If a person purchases $ x $ tickets on day $ i $ , all subsequent days (i.e. from day $ i+1 $ onwards) will have their prices per ticket increased by $ x $ .

For example, if $ a = [1, 3, 8, 4, 5] $ and you purchase $ 2 $ tickets on day $ 1 $ , they will cost $ 2 $ in total, and the prices from day $ 2 $ onwards will become $ [5, 10, 6, 7] $ . If you then purchase $ 3 $ more tickets on day $ 2 $ , they will cost in total an additional $ 15 $ , and the prices from day $ 3 $ onwards will become $ [13, 9, 10] $ .

Find the minimum spending to purchase $ k $ tickets.

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains three integers $ n $ , $ m $ , and $ k $ ( $ 1 \le n \le 3 \cdot 10^5, 1 \le m \le 10^9, 1 \le k \le \min(nm, 10^9) $ ) — the number of sale days, the maximum amount of ticket purchasable each day, and the number of tickets to be bought at the end.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the price per ticket for each of the upcoming $ n $ days.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print one integer: the minimum amount of money needed to purchase exactly $ k $ tickets.

## 说明/提示

In the first test case, one optimal way to buy $ 3 $ tickets is as follows:

- Buy $ 0 $ tickets on the first day. The prices per ticket for the remaining days are $ [6, 4, 2] $ .
- Buy $ 0 $ tickets on the second day. The prices per ticket for the remaining days are $ [4, 2] $ .
- Buy $ 1 $ ticket on the third day with cost $ 4 $ . The price per ticket for the remaining day is $ [3] $ .
- Buy $ 2 $ tickets on the fourth day with cost $ 6 $ .

In the second test case, there is only one way to buy $ 8 $ tickets:

- Buy $ 2 $ tickets on the first day with cost $ 16 $ . The prices per ticket for the remaining days are $ [8, 6, 4] $ .
- Buy $ 2 $ tickets on the second day with cost $ 16 $ . The prices per ticket for the remaining days are $ [8, 6] $ .
- Buy $ 2 $ tickets on the third day with cost $ 16 $ . The price per ticket for the remaining day is $ [8] $ .
- Buy $ 2 $ tickets on the fourth day with cost $ 16 $ .

## 样例 #1

### 输入

```
4
4 2 3
8 6 4 2
4 2 8
8 6 4 2
5 100 1
10000 1 100 10 1000
6 3 9
5 5 5 5 5 5
```

### 输出

```
10
64
1
72
```



---

---
title: "Nene's Magical Matrix"
layout: "post"
diff: 普及/提高-
pid: CF1956C
tag: ['数学', '贪心']
---

# Nene's Magical Matrix

## 题目描述

The magical girl Nene has an $ n\times n $ matrix $ a $ filled with zeroes. The $ j $ -th element of the $ i $ -th row of matrix $ a $ is denoted as $ a_{i, j} $ .

She can perform operations of the following two types with this matrix:

- Type $ 1 $ operation: choose an integer $ i $ between $ 1 $ and $ n $ and a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ . Assign $ a_{i, j}:=p_j $ for all $ 1 \le j \le n $ simultaneously.
- Type $ 2 $ operation: choose an integer $ i $ between $ 1 $ and $ n $ and a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ . Assign $ a_{j, i}:=p_j $ for all $ 1 \le j \le n $ simultaneously.

Nene wants to maximize the sum of all the numbers in the matrix $ \sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}a_{i,j} $ . She asks you to find the way to perform the operations so that this sum is maximized. As she doesn't want to make too many operations, you should provide a solution with no more than $ 2n $ operations.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ). The description of test cases follows.

The only line of each test case contains a single integer $ n $ ( $ 1 \le n \le 500 $ ) — the size of the matrix $ a $ .

It is guaranteed that the sum of $ n^2 $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, in the first line output two integers $ s $ and $ m $ ( $ 0\leq m\leq 2n $ ) — the maximum sum of the numbers in the matrix and the number of operations in your solution.

In the $ k $ -th of the next $ m $ lines output the description of the $ k $ -th operation:

- an integer $ c $ ( $ c \in \{1, 2\} $ ) — the type of the $ k $ -th operation;
- an integer $ i $ ( $ 1 \le i \le n $ ) — the row or the column the $ k $ -th operation is applied to;
- a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ — the permutation used in the $ k $ -th operation.

Note that you don't need to minimize the number of operations used, you only should use no more than $ 2n $ operations. It can be shown that the maximum possible sum can always be obtained in no more than $ 2n $ operations.

## 说明/提示

In the first test case, the maximum sum $ s=1 $ can be obtained in $ 1 $ operation by setting $ a_{1, 1}:=1 $ .

In the second test case, the maximum sum $ s=7 $ can be obtained in $ 3 $ operations as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1956C/3b20fbb55df6b6d6328669ffd917221602db721d.png)It can be shown that it is impossible to make the sum of the numbers in the matrix larger than $ 7 $ .

## 样例 #1

### 输入

```
2
1
2
```

### 输出

```
1 1
1 1 1
7 3
1 1 1 2
1 2 1 2
2 1 1 2
```



---

---
title: "A BIT of a Construction"
layout: "post"
diff: 普及/提高-
pid: CF1957B
tag: ['贪心', '位运算']
---

# A BIT of a Construction

## 题目描述

给定 $n,k$，请构造序列 $a_n$，你需要保证 $a_i$ 为自然数，同时满足以下条件：

* $\sum\limits_{i=1}^{n} a_i=k$。

* $a_1|a_2|\dots|a_n$ 二进制下拆位后 $1$ 的数量最大，其中 $|$ 表示[按位或](https://baike.baidu.com/item/%E6%8C%89%E4%BD%8D%E6%88%96/548283?fr=ge_ala)。

## 输入格式

第一行一个整数 $t$，表示数据组数。

接下来对于每组数据，共一行两个整数 $n,k$。

## 输出格式

共 $t$ 行，每行 $n$ 个整数，表示构造的 $a_n$。

如果有多个解，输出任意解即可。

## 说明/提示

对于全部数据，满足 $1\le t\le10^4$，$1\le n\le2\times10^5$，$1\le k\le10^9$，$\sum n\le2\times10^5$。

## 样例 #1

### 输入

```
4
1 5
2 3
2 5
6 51
```

### 输出

```
5
1 2
5 0
3 1 1 32 2 12
```



---

---
title: "Everything Nim"
layout: "post"
diff: 普及/提高-
pid: CF1965A
tag: ['贪心', '博弈论']
---

# Everything Nim

## 题目描述

Alice 和 Bob 在用 $n\ (n\le2\times10^5 ) $ 堆石子做游戏。在其中一位玩家的回合里，他可以选择一个不超过当前所有**非空**堆中石子数量**最小值**的**正整数** $ k$，并从目前所有非空堆中移除 $k$ 颗石子。当一名玩家在他的回合中无法进行操作时（此时所有石子堆都是空的），即判为负。

现在给出 $n$ 堆石子的初始石子数，已知 Alice 先手且两人都足够聪明，请你判断最后谁会获胜。

---

## 输入格式

输入包含多组数据。

第一行一个整数 $T\ (T\le10^4 ) $，表示输入数据组数。

对于每组数据，第一行包含一个整数 $n\ (n\le2\times10^5 ) $，表示石子堆数；第二行包含 $n$ 个整数 $a_{1\sim n}\ (a_i\le10^9 ) $，表示第 $i$ 堆石子的数量。

题目保证对于单个测试点的所有数据，满足 $\sum n\le2\times10^5$。

---

## 输出格式

对于每组测试数据，输出一行一个字符串，表示胜者的名字。如 Alice 获胜则输出 `Alice`，否则输出 `Bob`。

## 样例 #1

### 输入

```
7
5
3 3 3 3 3
2
1 7
7
1 3 9 7 4 2 100
3
1 2 3
6
2 1 3 4 2 4
8
5 7 2 9 6 3 3 2
1
1000000000
```

### 输出

```
Alice
Bob
Alice
Alice
Bob
Alice
Alice
```



---

---
title: "Permutation Game"
layout: "post"
diff: 普及/提高-
pid: CF1968D
tag: ['搜索', '贪心']
---

# Permutation Game

## 题目描述

Bodya and Sasha found a permutation $ p_1,\dots,p_n $ and an array $ a_1,\dots,a_n $ . They decided to play a well-known "Permutation game".

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

Both of them chose a starting position in the permutation.

The game lasts $ k $ turns. The players make moves simultaneously. On each turn, two things happen to each player:

- If the current position of the player is $ x $ , his score increases by $ a_x $ .
- Then the player either stays at his current position $ x $ or moves from $ x $ to $ p_x $ .

 The winner of the game is the player with the higher score after exactly $ k $ turns.Knowing Bodya's starting position $ P_B $ and Sasha's starting position $ P_S $ , determine who wins the game if both players are trying to win.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of testcases.

The first line of each testcase contains integers $ n $ , $ k $ , $ P_B $ , $ P_S $ ( $ 1\le P_B,P_S\le n\le 2\cdot 10^5 $ , $ 1\le k\le 10^9 $ ) — length of the permutation, duration of the game, starting positions respectively.

The next line contains $ n $ integers $ p_1,\dots,p_n $ ( $ 1 \le p_i \le n $ ) — elements of the permutation $ p $ .

The next line contains $ n $ integers $ a_1,\dots,a_n $ ( $ 1\le a_i\le 10^9 $ ) — elements of array $ a $ .

It is guaranteed that the sum of values of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase output:

- "Bodya" if Bodya wins the game.
- "Sasha" if Sasha wins the game.
- "Draw" if the players have the same score.

## 说明/提示

Below you can find the explanation for the first testcase, where the game consists of $ k=2 $ turns.

 TurnBodya's positionBodya's scoreBodya's moveSasha's positionSasha's scoreSasha's movefirst $ 3 $  $ 0 + a_3 = 0 + 5 = 5 $ stays on the same position $ 2 $  $ 0 + a_2 = 0 + 2 = 2 $ moves to $ p_2=1 $ second $ 3 $  $ 5 + a_3 = 5 + 5 = 10 $ stays on the same position $ 1 $  $ 2 + a_1 = 2 + 7 = 9 $ stays on the same positionfinal results $ 3 $  $ 10 $  $ 1 $  $ 9 $ As we may see, Bodya's score is greater, so he wins the game. It can be shown that Bodya always can win this game.

## 样例 #1

### 输入

```
10
4 2 3 2
4 1 2 3
7 2 5 6
10 8 2 10
3 1 4 5 2 7 8 10 6 9
5 10 5 1 3 7 10 15 4 3
2 1000000000 1 2
1 2
4 4
8 10 4 1
5 1 4 3 2 8 6 7
1 1 2 1 2 100 101 102
5 1 2 5
1 2 4 5 3
4 6 9 4 2
4 2 3 1
4 1 3 2
6 8 5 3
6 9 5 4
6 1 3 5 2 4
6 9 8 9 5 10
4 8 4 2
2 3 4 1
5 2 8 7
4 2 3 1
4 1 3 2
6 8 5 3
2 1000000000 1 2
1 2
1000000000 2
```

### 输出

```
Bodya
Sasha
Draw
Draw
Bodya
Sasha
Sasha
Sasha
Sasha
Bodya
```



---

---
title: "XOUR"
layout: "post"
diff: 普及/提高-
pid: CF1971G
tag: ['贪心', '堆', '位运算']
---

# XOUR

## 题目描述

You are given an array $ a $ consisting of $ n $ nonnegative integers.

You can swap the elements at positions $ i $ and $ j $ if $ a_i~\mathsf{XOR}~a_j < 4 $ , where $ \mathsf{XOR} $ is the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Find the lexicographically smallest array that can be made with any number of swaps.

An array $ x $ is lexicographically smaller than an array $ y $ if in the first position where $ x $ and $ y $ differ, $ x_i < y_i $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2\cdot10^5 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_i $ ( $ 0 \leq a_i \leq 10^9 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers — the lexicographically smallest array that can be made with any number of swaps.

## 说明/提示

For the first test case, you can swap any two elements, so we can produce the sorted array.

For the second test case, you can swap $ 2 $ and $ 1 $ (their $ \mathsf{XOR} $ is $ 3 $ ), $ 7 $ and $ 5 $ (their $ \mathsf{XOR} $ is $ 2 $ ), and $ 7 $ and $ 6 $ (their $ \mathsf{XOR} $ is $ 1 $ ) to get the lexicographically smallest array.

## 样例 #1

### 输入

```
4
4
1 0 3 2
5
2 7 1 5 6
8
1 2 1 2 1 2 1 2
4
16 4 1 64
```

### 输出

```
0 1 2 3 
1 5 2 6 7 
1 1 1 1 2 2 2 2 
16 4 1 64
```



---

---
title: "Ingenuity-2"
layout: "post"
diff: 普及/提高-
pid: CF1974D
tag: ['模拟', '贪心']
---

# Ingenuity-2

## 题目描述

Let's imagine the surface of Mars as an infinite coordinate plane. Initially, the rover Perseverance-2 and the helicopter Ingenuity-2 are located at the point with coordinates $ (0, 0) $ . A set of instructions $ s $ consisting of $ n $ instructions of the following types was specially developed for them:

- N: move one meter north (from point $ (x, y) $ to $ (x, y + 1) $ );
- S: move one meter south (from point $ (x, y) $ to $ (x, y - 1) $ );
- E: move one meter east (from point $ (x, y) $ to $ (x + 1, y) $ );
- W: move one meter west (from point $ (x, y) $ to $ (x - 1, y) $ ).

Each instruction must be executed either by the rover or by the helicopter. Moreover, each device must execute at least one instruction. Your task is to distribute the instructions in such a way that after executing all $ n $ instructions, the helicopter and the rover end up at the same point, or determine that this is impossible.

## 输入格式

The first line of input contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of instructions.

The second line of each test case contains a string $ s $ of length $ n $ consisting of the characters 'N', 'S', 'E', 'W' — the sequence of instructions.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10 ^ 5 $ .

## 输出格式

For each test case, if the required distribution of instructions exists, output a string $ p $ of length $ n $ consisting of the characters 'R', 'H'. If the $ i $ -th operation should be executed by the rover, then $ p_i=\text{R} $ , if the $ i $ -th operation should be executed by the helicopter, then $ p_i=\text{H} $ . If there are multiple solutions, output any of them.

Otherwise, output NO.

## 说明/提示

Let's consider the first example: the string $ S = \texttt{NENSNE} $ . One of the possible solutions, shown in the figure below, is $ p = \texttt{RRHRRH} $ , using which both the rover and the helicopter will end up one meter north and one meter east.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974D/6e8d0f788b954d2ceff54878d55afda06efd52c8.png)For WWW, the solution is impossible.

## 样例 #1

### 输入

```
10
6
NENSNE
3
WWW
6
NESSWS
2
SN
2
WE
4
SSNN
4
WESN
2
SS
4
EWNN
4
WEWE
```

### 输出

```
RRHRRH
NO
HRRHRH
NO
NO
RHRH
RRHH
RH
RRRH
RRHH
```



---

---
title: "Elections"
layout: "post"
diff: 普及/提高-
pid: CF1978D
tag: ['贪心', '前缀和']
---

# Elections

## 题目描述

Elections are taking place in Berland. There are $ n $ candidates participating in the elections, numbered from $ 1 $ to $ n $ . The $ i $ -th candidate has $ a_i $ fans who will vote for him. Additionally, there are $ c $ people who are undecided about their favorite candidate, let's call them undecided. Undecided people will vote for the candidate with the lowest number.

The candidate who receives the maximum number of votes wins the elections, and if multiple candidates receive the same maximum number of votes, the candidate with the lowest number among them wins.

You found these elections too boring and predictable, so you decided to exclude some candidates from them. If you do not allow candidate number $ i $ to participate in the elections, all $ a_i $ of his fans will become undecided, and will vote for the candidate with the lowest number.

You are curious to find, for each $ i $ from $ 1 $ to $ n $ , the minimum number of candidates that need to be excluded from the elections for candidate number $ i $ to win the elections.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 2 \cdot 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ c $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le c \le 10^9 $ ) — the number of candidates in the elections and the number of undecided people.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the number of fans for each candidate.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers, the $ i $ -th of which should be equal to the minimum number of candidates that need to be excluded from the elections for candidate number $ i $ to win.

## 说明/提示

In the first test case:

- If all candidates are allowed, candidate number $ 1 $ will receive $ 3 $ votes ( $ 1 $ undecided person will vote for him), candidate number $ 2 $ will receive $ 0 $ votes, and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 1 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 0 $ .
- If candidate number $ 1 $ is not allowed, his $ 2 $ fans will become undecided. Then candidate number $ 2 $ will receive $ 3 $ votes ( $ 3 $ undecided people will vote for him) and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 2 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 1 $ .
- If candidates with numbers $ 1 $ and $ 2 $ are not allowed, candidate number $ 3 $ wins, so the answer for him is $ 2 $ .

In the second test case, candidate number $ 1 $ will win if candidate number $ 2 $ is not allowed to participate.

## 样例 #1

### 输入

```
5
3 1
2 0 3
2 3
0 10
5 3
5 4 3 2 1
4 5
3 10 7 1
6 0
2 2 2 3 3 3
```

### 输出

```
0 1 2
1 0
0 1 2 3 4
1 0 2 3
1 1 2 0 4 5
```



---

---
title: "Sofia and the Lost Operations"
layout: "post"
diff: 普及/提高-
pid: CF1980C
tag: ['贪心']
---

# Sofia and the Lost Operations

## 题目描述

Sofia had an array of $ n $ integers $ a_1, a_2, \ldots, a_n $ . One day she got bored with it, so she decided to sequentially apply $ m $ modification operations to it.

Each modification operation is described by a pair of numbers $ \langle c_j, d_j \rangle $ and means that the element of the array with index $ c_j $ should be assigned the value $ d_j $ , i.e., perform the assignment $ a_{c_j} = d_j $ . After applying all modification operations sequentially, Sofia discarded the resulting array.

Recently, you found an array of $ n $ integers $ b_1, b_2, \ldots, b_n $ . You are interested in whether this array is Sofia's array. You know the values of the original array, as well as the values $ d_1, d_2, \ldots, d_m $ . The values $ c_1, c_2, \ldots, c_m $ turned out to be lost.

Is there a sequence $ c_1, c_2, \ldots, c_m $ such that the sequential application of modification operations $ \langle c_1, d_1, \rangle, \langle c_2, d_2, \rangle, \ldots, \langle c_m, d_m \rangle $ to the array $ a_1, a_2, \ldots, a_n $ transforms it into the array $ b_1, b_2, \ldots, b_n $ ?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Then follow the descriptions of the test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the size of the array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the original array.

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le 10^9 $ ) — the elements of the found array.

The fourth line contains an integer $ m $ ( $ 1 \le m \le 2 \cdot 10^5 $ ) — the number of modification operations.

The fifth line contains $ m $ integers $ d_1, d_2, \ldots, d_m $ ( $ 1 \le d_j \le 10^9 $ ) — the preserved value for each modification operation.

It is guaranteed that the sum of the values of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ , similarly the sum of the values of $ m $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

Output $ t $ lines, each of which is the answer to the corresponding test case. As an answer, output "YES" if there exists a suitable sequence $ c_1, c_2, \ldots, c_m $ , and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 样例 #1

### 输入

```
7
3
1 2 1
1 3 2
4
1 3 1 2
4
1 2 3 5
2 1 3 5
2
2 3
5
7 6 1 10 10
3 6 1 11 11
3
4 3 11
4
3 1 7 8
2 2 7 10
5
10 3 2 2 1
5
5 7 1 7 9
4 10 1 2 9
8
1 1 9 8 7 2 10 4
4
1000000000 203 203 203
203 1000000000 203 1000000000
2
203 1000000000
1
1
1
5
1 3 4 5 1
```

### 输出

```
YES
NO
NO
NO
YES
NO
YES
```



---

---
title: "Mathematical Problem"
layout: "post"
diff: 普及/提高-
pid: CF1986D
tag: ['动态规划 DP', '贪心']
---

# Mathematical Problem

## 题目描述

你有一个长度 $n > 1$ 的字符串 $s$，由数字 $0$ 到 $9$ 组成，你要将 $n - 2$ 个运算符（$+$ 或 $\times$）插入至 $s$ 中，形成一个合法的表达式。

很明显，任何一个运算符都不应插入在 $s_0$ 前或 $s_{n - 1}$ 后，因为这样构不成一个合法的表达式。还有一点：字符串中数字的位置不能变。

假设 $s = \tt 987009$，可以获得以下几种表达式：

- $ 9 \times 8 + 70 \times 0 + 9 = 81 $ 
- $ 98 \times 7 \times 0 + 0 \times 9 = 0 $
- $ 9 + 8 + 7 + 0 + 09 = 33 $  
表达式里的数被允许含有前导零，例子中的 $09$ 可以被转换为 $9$。

从该字符串中，无法获得以下几种表达式：
- $+ 9 \times 8 \times 70 + 09$（符号只能放在数字之间）
- $98 \times 70 + 0 + 9$（因为有 $6$ 个数字，所以必须正好有 $4$ 个符号）

## 输入格式

每个测试由多个测试数据组成。第一行包含一个整数 $t$（$1 \leq t \leq 10^4$），表示测试数据的数量。

每个测试用例的第一行包含一个整数 $n(2 \leq n \leq 20)$，表示字符串 $s$ 的长度。

每个测试用例的第二行包含一个字符串 $s$，长度为 $n$，由 $0$ 到 $9$ 的数字组成。

## 输出格式

对于每个测试数据，输出每个合法表达式的最小结果。

## 样例 #1

### 输入

```
18
2
10
2
74
2
00
2
01
3
901
3
101
5
23311
6
987009
7
1111111
20
99999999999999999999
20
00000000000000000000
4
0212
18
057235283621345395
4
1112
20
19811678487321784121
4
1121
4
2221
3
011
```

### 输出

```
10
74
0
1
9
1
19
0
11
261
0
0
0
12
93
12
24
0
```



---

---
title: "Increasing Sequence with Fixed OR"
layout: "post"
diff: 普及/提高-
pid: CF1988C
tag: ['贪心', '位运算']
---

# Increasing Sequence with Fixed OR

## 题目描述

You are given a positive integer $ n $ . Find the longest sequence of positive integers $ a=[a_1,a_2,\ldots,a_k] $ that satisfies the following conditions, and print the sequence:

- $ a_i\le n $ for all $ 1\le i\le k $ .
- $ a $ is strictly increasing. That is, $ a_i>a_{i-1} $ for all $ 2\le i\le k $ .
- $ a_i\,|\,a_{i-1}=n $ for all $ 2\le i\le k $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). Description of the test cases follows.

The only line of each test case contains one integer $ n $ ( $ 1\le n\le 10^{18} $ ).

It's guaranteed that the sum of lengths of the longest valid sequences does not exceed $ 5\cdot 10^5 $ .

## 输出格式

For each testcase, print two lines. In the first line, print the length of your constructed sequence, $ k $ . In the second line, print $ k $ positive integers, denoting the sequence. If there are multiple longest sequences, you can print any of them.

## 样例 #1

### 输入

```
4
1
3
14
23
```

### 输出

```
1
1
3
1 2 3
4
4 10 12 14
5
7 18 21 22 23
```



---

---
title: "Absolute Zero"
layout: "post"
diff: 普及/提高-
pid: CF1991C
tag: ['贪心']
---

# Absolute Zero

## 题目描述

你会得到一个$n$整数的数组$a$。
在一个操作中，您将执行以下两步移动：
1.选择一个整数$x$（$0\le x\le 10^{9}$）。
2.将每个$a_i$替换为$|a_i-x|$，其中$|v|$表示[绝对值](https://en.wikipedia.org/wiki/Absolute_value)$v$。
例如，通过选择$x=8$，数组$[5,7,10]$将变为$[|5-8|，|7-8|，|10-8|]=[3,1,2]$。
构造一个操作序列，使$a$的所有元素在最多$40$的操作中等于$0$，或者确定这是不可能的。您不需要减少操作次数

## 输入格式

每个测试包含多个测试用例。第一行包含一个整数$t$（$1\le t\le 10^4$）——测试用例的数量。测试用例的描述如下。
每个测试用例的第一行包含一个整数$n$（$1\le n\le 2\cdot 10^5$）——数组的长度$a$。
每个测试用例的第二行包含$n$整数$a_1，a_2，\ldots，a_n$（$0\le a_i\le 10^9$）——数组$a$的元素。
保证所有测试用例中$n$的总和不超过$2⋅10^5$。

## 输出格式

对于每个测试用例，如果不可能在最多$40$的操作中使所有数组元素都等于$0$，则输出一个整数$-1$。
否则，输出两行。输出的第一行应包含一个整数$k$（$0\le k\le 40$）——操作数。第二行输出应包含$k$个整数$x_1，x_2，\ldots，x_k$（$0\le x_i\le 10^{9}$）——操作序列，表示在第$i$次操作中，您选择了$x=x_i$。
如果有多个解决方案，请输出其中任何一个。
您不需要减少操作次数。

## 说明/提示

在第一个测试用例中，我们只能通过选择$x=5$执行一个操作，将数组从$[5]$更改为$[0]$。
在第二个测试用例中，不需要任何操作，因为数组的所有元素都已经是$0$了。
在第三个测试用例中，我们可以选择$x=6$将数组从$[4,6,8]$更改为$[2,0,2]$，然后选择$x=1$将其更改为$[1,1,1]$，最后再次选择$x=1.$将数组更改为$[0,0,0]$。
在第四个测试用例中，我们可以按照操作序列$（60,40,20,10,30,25,5）$使所有元素都为$0$。
在第五个测试用例中，可以证明，在最多$40$的操作中，不可能使所有元素都为$0$。因此，输出为$-1$。

## 样例 #1

### 输入

```
5
1
5
2
0 0
3
4 6 8
4
80 40 20 10
5
1 2 3 4 5
```

### 输出

```
1
5
0

3
6 1 1
7
60 40 20 10 30 25 5
-1
```



---

---
title: "Light Switches"
layout: "post"
diff: 普及/提高-
pid: CF1993C
tag: ['数学', '贪心']
---

# Light Switches

## 题目描述

一栋公寓楼里面有 $n$ 个房间，初始时每个房间的灯都是关的。为了更好地对房间里的灯进行控制，房东计划在不同时间给每个房间安装芯片。具体地，房东给每个房间安装芯片的时刻可以用包含 $n$ 个整数的数组 $a$ 来表示，其中第 $i$ 个元素 $a_i$ 表示房东给第 $i$ 个房间安装芯片的时刻。

一旦某个房间被安装上了芯片，这个房间里面的灯的状态每隔 $k$ 分钟就会发生一次变化，也就是说，安装商芯片的这一时刻起，这个房间里面的灯会先被点亮，$k$ 分钟后被熄灭，$k$ 分钟后再被点亮，如此循环往复。形式化的来讲，对于第 $i$ 个房间的灯，它的状态会在第 $a_i,a_i+k,a_i+2k,\dots$ 分钟发生变化。

现在请你求出所有房间的灯都被点亮的最小时刻，或者报告不存在所有房间的灯都被点亮的时刻。

## 输入格式

**本题包含多组数据**。

第一行输入一个整数 $T$，表示数据组数。

对于每组数据，第一行输入两个整数 $n,k$，分别表示房间个数和灯的状态发生变化的时间间隔。第二行输入 $n$ 个整数，第 $i$ 个整数表示房东给第 $i$ 个房间安装芯片的时刻 $a_i$。

## 输出格式

对于每组数据，如果不存在所有房间的灯都被点亮的时刻，输出一行 $-1$，否则输出一行一个整数，表示所有房间的灯都被点亮的最小时刻（单位为**分钟**）。

### 输入输出样例

见下文 _输入 #1_ 和 _输出 #1_。

### 样例 #1 解释

对于第一组数据，可以发现在第 $5$ 分钟所有的灯都是开着的。

对于第二组数据，第一个房间的灯被点亮的时刻为 $2,3,4,8,9,10,14\dots$，而第四个房间的灯被点亮的时刻为 $5,6,7,11,12,13,17,\dots$，可以发现这两个房间的灯无论什么时刻都不可能同时被点亮。

对于第三组数据，各个房间的灯在前 $10$ 分钟的状态如下表所示：

| 时刻（分钟）   | $1$  | $2$  | $3$  | $4$  | $5$  | $6$  | $7$  | $8$  | $9$  | $10$ |
| -------------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| $1$ 号房间的灯 | 关   | 关   | 开   | 开   | 开   | 关   | 关   | 关   | 开   | 开   |
| $2$ 号房间的灯 | 关   | 关   | 关   | 开   | 开   | 开   | 关   | 关   | 关   | 开   |
| $3$ 号房间的灯 | 关   | 关   | 关   | 关   | 关   | 关   | 关   | 开   | 开   | 开   |
| $4$ 号房间的灯 | 关   | 关   | 关   | 关   | 关   | 关   | 关   | 关   | 开   | 开   |

因此，所有房间的灯都被点亮的最小时刻为 $10$。

## 说明/提示

对于所有数据：

- $1\leqslant T\leqslant 10^4$。
- $1\leqslant k\leqslant n\leqslant 2\times 10^5$，$\sum n\leqslant 2\times 10^5$。
- $1\leqslant a_n\leqslant 10^9$。

Translated by [Eason_AC](/user/112917)。

## 样例 #1

### 输入

```
9
4 4
2 3 4 5
4 3
2 3 4 5
4 3
3 4 8 9
3 3
6 2 1
1 1
1
7 5
14 34 6 25 46 7 17
6 5
40 80 99 60 90 50
6 5
64 40 50 68 70 10
2 1
1 1000000000
```

### 输出

```
5
-1
10
8
1
47
100
-1
-1
```



---

---
title: "Maximize the Root"
layout: "post"
diff: 普及/提高-
pid: CF1997D
tag: ['贪心', '二分']
---

# Maximize the Root

## 题目描述

给你一棵有根的树，由 $n$ 个顶点组成。树上的顶点从 $1$到 $n$ 编号，根是顶点 $1$ 。第 $i$ 个顶点上的值为 $a_i$。

你可以执行以下操作任意次(可以为零次):选择一个至少有一个子顶点的顶点 $v$; 将 $a_v$ 增加 $1$ 并且对于 $v$ 的子树中的所有顶点 $u$ 将 $a_u$ 减少 $1$ (除了 $v$ 本身)。但是，在每次操作之后，所有顶点上的值都应该是非负的。

你的任务是使用前面提到的运算来计算写在根上的最大可能值。

## 输入格式

第一行包含一个整数 $t(1 \le t \le 10^4)$  表示测试用例的数量。

每个测试用例的第一行为一个整数 $n (2 \le n \le 2 \times 10^5)$ 表示树中顶点的数量。

第二行包含 $n$ 整数 $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) 表示每个点的初始值。
 
第三行包含 $n - 1$ 整数 $ p_2，p_3，\dots，p_n  (1 \le p_i \le n)$，其中 $p_i$ 是树中第 $i$ 个顶点的父顶点。顶点 $1$ 是根。

对输入的附加约束:所有测试用例的 $n$ 之和不超过 $ 2 \times 10^5 $。

## 输出格式

对于每个测试用例，输出一个整数——使用前面提到的操作在根上写出的最大可能值。

## 样例 #1

### 输入

```
3
4
0 1 0 2
1 1 3
2
3 0
1
5
2 5 3 9 6
3 1 5 2
```

### 输出

```
1
3
6
```



---

---
title: "Minimize Equal Sum Subarrays"
layout: "post"
diff: 普及/提高-
pid: CF1998B
tag: ['贪心', '构造']
---

# Minimize Equal Sum Subarrays

## 题目描述

# 最小化相等和子数组


已知 [农夫约翰喜欢排列](https://usaco.org/index.php?page=viewproblem2&cpid=1421)，我也喜欢它们！

给定一个长度为 $ n $ 的排列 $ p $。

找到一个长度为 $ n $ 的排列 $ q $，使得以下条件下的对数最小化：对所有 $ 1 \leq i \leq j \leq n $，使得 $ p_i + p_{i+1} + \ldots + p_j = q_i + q_{i+1} + \ldots + q_j $。

**注**：一个长度为 $ n $ 的排列是一个包含 $ 1 $ 到 $ n $ 的 $ n $ 个不同整数的数组。例如，\[2, 3, 1, 5, 4\] 是一个排列，但 \[1, 2, 2\] 不是一个排列（数字 2 在数组中出现了两次），而 \[1, 3, 4\] 也不是一个排列（$ n=3 $，但数组中有 4）。

## 输入格式

第一行包含一个整数 $ t $ ($ 1 \leq t \leq 10^4 $) — 测试用例的数量。

每个测试用例的第一行包含一个整数 $ n $ ($ 1 \leq n \leq 2 \cdot 10^5 $)。

接下来一行包含 $ n $ 个空格分隔的整数 $ p_1, p_2, \ldots, p_n $ ($ 1 \leq p_i \leq n $) — 表示长度为 $ n $ 的排列 $ p $。

保证所有测试用例中 $ n $ 的总和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对于每个测试用例，输出一行包含任意长度为 $ n $ 的排列 $ q $，使得 $ q $ 最小化满足条件的对数。

## 说明/提示

对于第一个测试用例，存在唯一一对 $ (i, j) $ ($ 1 \leq i \leq j \leq n $) 使得 $ p_i + p_{i+1} + \ldots + p_j = q_i + q_{i+1} + \ldots + q_j $，即 $ (1, 2) $。可以证明，没有这样的 $ q $ 使得不存在满足条件的对。

## 样例 #1

### 输入

```
3
2
1 2
5
1 2 3 4 5
7
4 7 5 1 2 6 3
```

### 输出

```
2 1
3 5 4 2 1
6 2 1 4 7 3 5
```



---

---
title: "Right Left Wrong"
layout: "post"
diff: 普及/提高-
pid: CF2000D
tag: ['贪心']
---

# Right Left Wrong

## 题目描述

Vlad发现了一个由 $n$ 细胞组成的条带，从左到右从 $1$ 到 $n$ 编号。在 $i$ 中，有一个正整数 $a_i$ 和一个字母 $s_i$ ，其中所有 $s_i$ 都是'L'或'R'。

Vlad邀请您尝试通过执行任意(可能为零)操作来获得最大可能的分数。

在一次操作中，您可以选择两个索引 $l$ 和 $r$ ( $1 \le l < r \le n$ )，使 $s_l$ = `L` 和 $s_r$ = `R`，并执行以下操作:

- 在当前分数基础上增加 $a_l + a_{l + 1} + \dots + a_{r - 1} + a_r$ 分;

- 将 $s_i$ 替换为`.`

- 对于所有 $l \le i \le r$ ，这意味着您不能再选择这些索引。

例如，考虑下面的strip:

| $3$ | $5$ | $1$ | $4$ | $3$ | $2$
|  --- | --- | --- | --- | --- | ---  |
| l | r | l | l | l | r |

您可以先选择 $l = 1$ ， $r = 2$ ，并将 $3 + 5 = 8$ 添加到您的分数中。

| $3$ | $5$ | $1$ | $4$ | $3$ | $2$
|  --- | --- | --- | --- | --- | ---  |
|。|。| l | l | l | r |

然后选择 $l = 3$ ， $r = 6$ 并将 $1 + 4 + 3 + 2 = 10$ 添加到您的分数中。

| $3$ | $5$ | $1$ | $4$ | $3$ | $2$
|  --- | --- | --- | --- | --- | ---  |
|。|。|。|。|。|。|

因此无法再进行其他操作，最终得分为 $18$ 。

能达到的最高分数是多少?

## 输入格式

输入* * * *

第一行包含一个整数 $t$ ( $1 \le t \le 10^4$ )—测试用例的数量。

每个测试用例的第一行包含一个整数 $n$ ( $2 \le n \le 2 \cdot 10^5$ )—条带的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$ ( $1 \le a_i \le 10^5$ )——写在试纸上的数字。

每个测试用例的第三行包含一个由 $n$ 字符 `L` 和 `R` 组成的字符串 $s$ 。

可以保证所有测试用例中 $n$ 的值之和不超过 $2 \cdot 10^5$ 。

## 输出格式

对于每个测试用例，输出一个整数—可以得分的最大可能点数。

## 样例 #1

### 输入

```
4
6
3 5 1 4 3 2
LRLLLR
2
2 8
LR
2
3 9
RL
5
1 2 3 4 5
LRLRR
```

### 输出

```
18
10
0
22
```



---

---
title: "Photoshoot for Gorillas"
layout: "post"
diff: 普及/提高-
pid: CF2000E
tag: ['贪心', '前缀和']
---

# Photoshoot for Gorillas

## 题目描述

你非常喜欢大猩猩，于是你决定为它们组织一次拍摄活动。大猩猩生活在丛林中，丛林被表示为一个有 $n$ 行 $m$ 列的网格，有 $w$ 个大猩猩同意参与拍摄，第 $i$ 个大猩猩的身高为 $a_i$ .你希望将所有大猩猩放置在网格的单元格中，并且确保每个单元格中最多只有一只大猩猩。

每种方案的壮观程度等于网格中所有以 $k$ 为边长的子正方形的壮观程度的总和。

子正方形的壮观程度等于其中所有大猩猩的身高的总和。

从所有合适的方案中选出最壮观的方案。

## 输入格式

第一行包含一个整数 $t$ ，表示共有 $t$ 组测试样例。

测试用例的描述如下。

第一行包含三个整数 $n，m，k$，表示网格的尺寸和子正方形的边长。

第二行包含一个整数 $w$，表示大猩猩的数量。

第三行包含 $w$ 个整数 $a_1，a_2，...，a_w$，表示每个大猩猩的身高。

保证所有测试样例中 $n·m$ 的总和不超过 $2·10^5$，$w$ 的总和也不超过 $2·10^5$。

## 输出格式

对于每个测试用例，输出一个整数表示最壮观的方案的壮观程度。

## 样例 #1

### 输入

```
5
3 4 2
9
1 1 1 1 1 1 1 1 1
2 1 1
2
5 7
20 15 7
9
4 1 4 5 6 1 1000000000 898 777
1984 1 1
4
5 4 1499 2004
9 5 5
6
6 7 14 16 16 6
```

### 输出

```
21
12
49000083104
3512
319
```



---

---
title: "Turtle and Good Pairs"
layout: "post"
diff: 普及/提高-
pid: CF2003C
tag: ['贪心']
---

# Turtle and Good Pairs

## 题目描述

海龟给你一个由小写字母组成的字符串 $s$。

他认为，如果一对整数 $(i, j)$（其中 $1 \le i < j \le n$）满足以下条件，则称其为「愉快对」：

1. 存在一个整数 $k$，满足 $i \le k < j$，而且：
   - $s_k \ne s_{k + 1}$；
   - $s_k \ne s_i$ 或 $s_{k + 1} \ne s_j$。

同时，如果一对整数 $(i, j)$（其中 $1 \le i < j \le n$）是「愉快对」或者 $s_i = s_j$，那么它就是「好对」。

海龟想重新排列字符串 $s$，以使「好对」的数量最大化。请帮他实现这一目标。

## 输入格式

输入包括多个测试用例。第一行给出测试用例的数量 $t$（$1 \le t \le 10^4$）。随后是每个测试用例的具体内容。

对于每个测试用例，第一行是一个整数 $n$（$2 \le n \le 2 \cdot 10^5$），表示字符串的长度。

接下来的一行是一个由小写字母组成的字符串 $s$，长度为 $n$。

保证所有测试用例中的字符串长度之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个重新排列后的字符串 $s$，使得「好对」的数量最大化。如果存在多个解，可以输出其中任意一个。

## 数据范围与示例

对于第一个测试用例，例如，重新排列后的字符串中 $(1, 3)$ 是「好对」。你可以发现无法进一步增加「好对」的数量。`bac` 和 `cab` 也是有效答案。

在第二个测试用例中，重新排列后的字符串中有多个「好对」，例如 $(1, 2)$、$(1, 4)$、$(1, 5)$、$(2, 4)$、$(2, 5)$ 和 $(3, 5)$。`efddd` 也是一个符合条件的答案。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
3
abc
5
edddf
6
turtle
8
pppppppp
10
codeforces
```

### 输出

```
acb
ddedf
urtlet
pppppppp
codeforces
```



---

---
title: "Turtle and a MEX Problem (Easy Version)"
layout: "post"
diff: 普及/提高-
pid: CF2003D1
tag: ['数学', '贪心']
---

# Turtle and a MEX Problem (Easy Version)

## 题目描述

The two versions are different problems. In this version of the problem, you can choose the same integer twice or more. You can make hacks only if both versions are solved.

One day, Turtle was playing with $ n $ sequences. Let the length of the $ i $ -th sequence be $ l_i $ . Then the $ i $ -th sequence was $ a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i} $ .

Piggy gave Turtle a problem to solve when Turtle was playing. The statement of the problem was:

- There was a non-negative integer $ x $ at first. Turtle would perform an arbitrary number (possibly zero) of operations on the integer.
- In each operation, Turtle could choose an integer $ i $ such that $ 1 \le i \le n $ , and set $ x $ to $ \text{mex}^{\dagger}(x, a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}) $ .
- Turtle was asked to find the answer, which was the maximum value of $ x $ after performing an arbitrary number of operations.

Turtle solved the above problem without difficulty. He defined $ f(k) $ as the answer to the above problem when the initial value of $ x $ was $ k $ .

Then Piggy gave Turtle a non-negative integer $ m $ and asked Turtle to find the value of $ \sum\limits_{i = 0}^m f(i) $ (i.e., the value of $ f(0) + f(1) + \ldots + f(m) $ ). Unfortunately, he couldn't solve this problem. Please help him!

 $ ^{\dagger}\text{mex}(c_1, c_2, \ldots, c_k) $ is defined as the smallest non-negative integer $ x $ which does not occur in the sequence $ c $ . For example, $ \text{mex}(2, 2, 0, 3) $ is $ 1 $ , $ \text{mex}(1, 2) $ is $ 0 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n, m $ ( $ 1 \le n \le 2 \cdot 10^5, 0 \le m \le 10^9 $ ).

Each of the following $ n $ lines contains several integers. The first integer $ l_i $ ( $ 1 \le l_i \le 2 \cdot 10^5 $ ) represents the length of the $ i $ -th sequence, and the following $ l_i $ integers $ a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i} $ ( $ 0 \le a_{i, j} \le 10^9 $ ) represent the elements of the $ i $ -th sequence.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ , and the sum of $ \sum l_i $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the value of $ \sum\limits_{i = 0}^m f(i) $ .

## 说明/提示

In the first test case, when $ x $ is initially $ 2 $ , Turtle can choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}) = \text{mex}(2, 7, 0, 1, 5) = 3 $ . It can be proved that Turtle can't make the value of $ x $ greater than $ 3 $ , so $ f(2) = 3 $ .

It can be seen that $ f(0) = 3 $ , $ f(1) = 3 $ , $ f(2) = 3 $ , $ f(3) = 3 $ , and $ f(4) = 4 $ . So $ f(0) + f(1) + f(2) + f(3) + f(4) = 3 + 3 + 3 + 3 + 4 = 16 $ .

In the second test case, when $ x $ is initially $ 1 $ , Turtle can choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(1, 1, 3, 0, 3, 3) = 2 $ , and choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(2, 1, 3, 0, 3, 3) = 4 $ . It can be proved that Turtle can't make the value of $ x $ greater than $ 4 $ , so $ f(1) = 4 $ .

It can be seen that $ f(0) = 4 $ , $ f(1) = 4 $ , $ f(2) = 4 $ , $ f(3) = 4 $ , and $ f(4) = 4 $ . So $ f(0) + f(1) + f(2) + f(3) + f(4) = 4 + 4 + 4 + 4 + 4 = 20 $ .

In the fourth test case, it can be seen that $ f(0) = 3 $ and $ f(1) = 3 $ . So $ f(0) + f(1) = 3 + 3 = 6 $ .

## 样例 #1

### 输入

```
6
3 4
2 0 2
3 2 3 3
4 7 0 1 5
3 4
5 0 2 0 4 11
1 1
5 1 3 0 3 3
2 50
2 1 2
2 1 2
1 1
7 1 2 4 1 4 9 5
4 114514
2 2 2
5 7 3 6 0 3
3 0 1 1
5 0 9 2 1 5
5 1919810
1 2
2 324003 0
3 1416324 2 1460728
4 1312631 2 0 1415195
5 1223554 192248 2 1492515 725556
```

### 输出

```
16
20
1281
6
6556785365
1842836177961
```



---

---
title: "Colored Portals"
layout: "post"
diff: 普及/提高-
pid: CF2004D
tag: ['模拟', '图论', '贪心']
---

# Colored Portals

## 题目描述

一条直线上有 $n$ 个城市，这些城市的编号为 $1$ 到 $n$。

传送门被用于在城市间移动，传送门有四种颜色：蓝色，绿色，红色和黄色。每一个城市都有两种颜色的传送门。你可以从城市 $i$ 到城市 $j$，当且仅当这两个城市存在同色的传送门（例如，你可以从有红色和蓝色的传送门的城市到有蓝色和绿色传送门的城市），花费 $|i - j|$ 个硬币。

你的任务是回答 $q$ 个询问：计算城市 $x$ 到城市 $y$ 的最小花费。

## 输入格式

第一行输入 $t$（$1\le t \le 10^4$），代表测试数据的组数。

对于每个测试数据，第一行输入 $n,q$（$1\le n,q \le2 \times 10^5$），表示城市数和询问数。

第二行输入 $n$ 个只能为 `BG`，`BR`，`BY`，`GR`，`GY`，`RY` 之一的字符串，第 $i$ 个表示城市 $i$ 有的传送门颜色，`B` 表示蓝色，`G` 表示绿色，`R` 表示红色，`Y` 表示黄色。

接下来 $q$ 行第 $j$ 行输入 $x_j,y_j$（$1 \le x_j,y_j \le n$），表示第 $j$ 个询问的 $x,y$。

输入保证所有测试数据中 $n$ 的和不超过 $2 \times 10^5$，$q$ 的和不超过 $2 \times 10 ^ 5$。

## 输出格式

对每个询问，输出一个整数，即从城市 $x$ 到城市 $y$ 的最小花费（若无解输出 $-1$）。

## 样例 #1

### 输入

```
2
4 5
BR BR GY GR
1 2
3 1
4 4
1 4
4 2
2 1
BG RY
1 2
```

### 输出

```
1
4
0
3
2
-1
```



---

---
title: "Alternating String"
layout: "post"
diff: 普及/提高-
pid: CF2008E
tag: ['贪心', '前缀和']
---

# Alternating String

## 题目描述

# 交替字符串


Sakurako 非常喜欢交替字符串。她把一个由小写拉丁字母组成的字符串 $s$ 称为"交替字符串"，如果字符串中偶数位置的字符都相同，奇数位置的字符都相同，且字符串的长度是偶数。

例如，字符串 `abab` 和 `gg` 是交替的，而字符串 `aba` 和 `ggwp` 则不是。

作为她的好朋友，你决定送她这样一个字符串，但你没能找到一个。幸运的是，你可以对字符串执行两种操作：

1. 选择一个索引 $i$ 并删除字符串中的第  $i$ 个字符，这将使字符串的长度减少 $1$ 。这种操作最多可以执行 $1$ 次；

2. 选择一个索引 $i$ 并将 $s_i$ 替换为任意其他字母。

由于你很着急，你需要确定将字符串变成交替字符串所需的最少操作次数。

## 输入格式

第一行包含一个整数 $t$ $(1 \le t \le 10^4)$。

每个测试用例的第一行包含一个整数$n$ $(1 \le n \le 2\cdot 10^5)$。

每个测试用例的第二行包含一个字符串$s$，由小写拉丁字母组成。

保证所有测试用例中$n$的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——将字符串 $s$ 变成交替字符串所需的最少操作次数。

## 说明/提示

对于字符串 `ababa`，你可以删除第一个字符得到 `baba`，这是一个交替字符串。

对于字符串 `acdada`，你可以将前两个字符改为 `d` 和 `a` 得到 `dadada`，这是一个交替字符串。

## 样例 #1

### 输入

```
10
1
a
2
ca
3
aab
5
ababa
6
acdada
9
ejibmyyju
6
bbccbc
6
abacba
5
bcbca
5
dcbdb
```

### 输出

```
1
0
1
1
2
6
2
3
1
1
```



---

---
title: "Password Cracking"
layout: "post"
diff: 普及/提高-
pid: CF2013C
tag: ['贪心']
---

# Password Cracking

## 题目描述

迪马什得知曼苏尔向朋友泄露了一些关于他的不愉快言论，于是他决心揭开曼苏尔的密码，看看具体内容是什么。

曼苏尔对自己的密码充满信心，他表示自己的密码是一个长度为 $ n $ 的二进制字符串。同时，他愿意回答迪马什的问题：

迪马什可以给出一个二进制字符串 $ t $ ，曼苏尔则回答 $ t $ 是否是他的密码的一个子串（即一段连续的字符序列）。

请帮助迪马什在不超过 $ 2n $ 次询问内猜出密码；否则，曼苏尔将识破伎俩并停止与他交流。

## 输入格式

输入包含多个测试用例。第一行包含一个整数 $ t $ ，表示测试用例的数量（$ 1 \le t \le 100 $）。接下来描述每个测试用例。

## 输出格式

每个测试用例一开始，读取一个整数 $ n $ ，表示二进制字符串的长度（$ 1 \le n \le 100 $）。然后开始猜测这个字符串。

在猜测字符串 $ s $ 的过程中，你可以进行不超过 $ 2n $ 次以下类型的查询：

- "? $ t $"，其中 $ t $ 是满足 $ 1 \le |t| \le n $ 的二进制字符串。

对于每次查询，你将收到一个结果：如果 $ t $ 是 $ s $ 的子串，返回 $ 1 $；否则返回 $ 0 $。

一旦确认了密码字符串 $ s $，输出格式如下：

- "! $ s $"，其中 $ s $ 是长度为 $ n $ 的二进制字符串。

完成一个测试用例后，继续下一个测试用例的解答。

如果在过程中发生错误尝试或超过 $ 2n $ 次查询限制，将收到 $ -1 $ 作为回应，并被判定为“错误答案”。此时程序应立即终止，以避免未定义的结果。

记得在输出查询结果之后，添加一个换行并刷新输出缓冲区，否则程序会被判定为“程序挂起”。常用的刷新缓冲方法如下：

- C++ 中使用 `fflush(stdout)` 或 `cout.flush()`
- Java 中使用 `System.out.flush()`
- Pascal 中使用 `flush(output)`
- Python 中使用 `sys.stdout.flush()`
- 其他语言请参考相关文档进行操作。

### 数据范围与提示

举例说明：对于字符串 $ 010 $ ，查询的结果是：

- "? 00"——因为 $ 00 $ 不是 $ 010 $ 的子串，所以结果是 $ 0 $。
- "? 000"——因为 $ 000 $ 不是子串，结果是 $ 0 $。
- "? 010"——因为 $ 010 $ 是子串，结果是 $ 1 $。

在以下示例中，字符串分别为 $ 1100 $ 、 $ 0110 $ 和 $ 10 $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
3

0

0

1

4

4

2
```

### 输出

```
? 00

? 000

? 010

! 010

! 1100

! 0110

! 10
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
title: "Action Figures"
layout: "post"
diff: 普及/提高-
pid: CF2026C
tag: ['贪心', '队列']
---

# Action Figures

## 题目描述

在 Monocarp 家附近有一家商店，专门售卖手办。近期，这家店将推出一套新的手办系列，总共包含 $n$ 个手办。其中，第 $i$ 个手办的价格为 $i$ 枚金币。在第 $i$ 天到第 $n$ 天之间，这个手办都是可以购买的。

Monocarp 知道他在这 $n$ 天中的哪几天可以去商店。

每次去商店的时候，他可以购买多件手办（当然，不能买尚未发售的手办）。如果他在同一天购买了至少两个手办，他可以享受一个折扣：他所购买的最贵手办是免费的，也就是说他无需为该手办支付费用。

Monocarp 的目标是从这个手办系列中，分别购买一个第 $1$ 个手办、一个第 $2$ 个手办……一直到一个第 $n$ 个手办。注意，每个手办只能购买一次。请你帮他计算，他最少需要花费多少金币？

## 输入格式

第一行输入一个整数 $t$，表示有多少个测试用例（$1 \le t \le 10^4$）。

每个测试用例包含两行：

- 第一行是一个整数 $n$，表示手办的数量（也是销售天数）（$1 \le n \le 4 \cdot 10^5$）；
- 第二行是一个长度为 $n$ 的字符串 $s$。如果在第 $i$ 天 Monocarp 可以去商店，$s_i$ 就为 1；否则为 0。

额外的限制条件有：

- 在每个测试用例中，字符串 $s$ 的最后一个字符 $s_n$ 一定是 1，所以 Monocarp 无论如何都能在最后一天买到所有手办。
- 所有测试用例中 $n$ 的总和不超过 $4 \cdot 10^5$。

## 输出格式

对每个测试用例，输出一个整数，表示 Monocarp 最少需要花费的金币数。

## 说明/提示

在第一个测试用例中，Monocarp 可以在第一天购买第一个手办，花费 1 枚金币。

在第二个测试用例中，他可以在第三天购买第 1 和第 3 个手办，在第四天购买第 2 和第 4 个手办，在第六天购买第 5 和第 6 个手办。这样总费用为 $1+2+5=8$ 枚金币。

在第三个测试用例中，他可以在第三天购买第 2 和第 3 个手办，其余手办在第七天购买，最终花费 $1+2+4+5+6 = 18$ 枚金币。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1
1
6
101101
7
1110001
5
11111
```

### 输出

```
1
8
18
6
```



---

---
title: "A TRUE Battle"
layout: "post"
diff: 普及/提高-
pid: CF2030C
tag: ['贪心', '位运算']
---

# A TRUE Battle

## 题目描述

Alice and Bob are playing a game. There is a list of $ n $ booleans, each of which is either true or false, given as a binary string $ ^{\text{∗}} $ of length $ n $ (where $ \texttt{1} $ represents true, and $ \texttt{0} $ represents false). Initially, there are no operators between the booleans.

Alice and Bob will take alternate turns placing and or or between the booleans, with Alice going first. Thus, the game will consist of $ n-1 $ turns since there are $ n $ booleans. Alice aims for the final statement to evaluate to true, while Bob aims for it to evaluate to false. Given the list of boolean values, determine whether Alice will win if both players play optimally.

To evaluate the final expression, repeatedly perform the following steps until the statement consists of a single true or false:

- If the statement contains an and operator, choose any one and replace the subexpression surrounding it with its evaluation.
- Otherwise, the statement contains an or operator. Choose any one and replace the subexpression surrounding the or with its evaluation.

 For example, the expression true or false and false is evaluated as true or (false and false) $ = $ true or false $ = $ true. It can be shown that the result of any compound statement is unique. $ ^{\text{∗}} $ A binary string is a string that only consists of characters $ \texttt{0} $ and $ \texttt{1} $

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the length of the string.

The second line contains a binary string of length $ n $ , consisting of characters $ \texttt{0} $ and $ \texttt{1} $ — the list of boolean values.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, output "YES" (without quotes) if Alice wins, and "NO" (without quotes) otherwise.

You can output "YES" and "NO" in any case (for example, strings "yES", "yes" and "Yes" will be recognized as a positive response).

## 说明/提示

In the first testcase, Alice can place and between the two booleans. The game ends as there are no other places to place operators, and Alice wins because true and true is true.

In the second testcase, Alice can place or between the middle true and the left false. Bob can place and between the middle true and the right false. The statement false or true and false is false.

Note that these examples may not be the best strategies for either Alice or Bob.

## 样例 #1

### 输入

```
5
2
11
3
010
12
101111111100
10
0111111011
8
01000010
```

### 输出

```
YES
NO
YES
YES
NO
```



---

---
title: "Sakurako, Kosuke, and the Permutation"
layout: "post"
diff: 普及/提高-
pid: CF2033E
tag: ['贪心']
---

# Sakurako, Kosuke, and the Permutation

## 题目描述

Sakurako's exams are over, and she did excellently. As a reward, she received a permutation $ p $ . Kosuke was not entirely satisfied because he failed one exam and did not receive a gift. He decided to sneak into her room (thanks to the code for her lock) and spoil the permutation so that it becomes simple.

A permutation $ p $ is considered simple if for every $ i $ $ (1\le i \le n) $ one of the following conditions holds:

- $ p_i=i $
- $ p_{p_i}=i $

For example, the permutations $ [1, 2, 3, 4] $ , $ [5, 2, 4, 3, 1] $ , and $ [2, 1] $ are simple, while $ [2, 3, 1] $ and $ [5, 2, 1, 4, 3] $ are not.

In one operation, Kosuke can choose indices $ i,j $ $ (1\le i,j\le n) $ and swap the elements $ p_i $ and $ p_j $ .

Sakurako is about to return home. Your task is to calculate the minimum number of operations that Kosuke needs to perform to make the permutation simple.

## 输入格式

The first line contains one integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

Each test case is described by two lines.

- The first line contains one integer $ n $ ( $ 1\le n \le 10^6 $ ) — the length of the permutation $ p $ .
- The second line contains $ n $ integers $ p_i $ ( $ 1\le p_i\le n $ ) — the elements of the permutation $ p $ .

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 10^6 $ .

It is guaranteed that $ p $ is a permutation.

## 输出格式

For each test case, output the minimum number of operations that Kosuke needs to perform to make the permutation simple.

## 说明/提示

In the first and second examples, the permutations are already simple.

In the fourth example, it is sufficient to swap $ p_2 $ and $ p_4 $ . Thus, the permutation will become $ [2, 1, 4, 3] $ in $ 1 $ operation.

## 样例 #1

### 输入

```
6
5
1 2 3 4 5
5
5 4 3 2 1
5
2 3 4 5 1
4
2 3 4 1
3
1 3 2
7
2 3 1 5 6 7 4
```

### 输出

```
0
0
2
1
0
2
```



---

---
title: "Sharky Surfing"
layout: "post"
diff: 普及/提高-
pid: CF2037D
tag: ['贪心', '堆', '优先队列']
---

# Sharky Surfing

## 题目描述

Mualani 喜欢在她的大鲨鱼冲浪板上冲浪！

Mualani 的冲浪路径可以用一个数轴来表示。她从位置 $1$ 开始，路径的终点是位置 $L$。当她处于位置 $x$ 且跳跃能力为 $k$ 时，她可以跳到区间 $[x, x+k]$ 内的任意整数位置。最初，她的跳跃能力为 $1$。

然而，她的冲浪路径并不完全平坦。她的路径上有 $n$ 个障碍物。每个障碍物由一个区间 $[l, r]$ 表示，意味着她不能跳到区间 $[l, r]$ 内的任何位置。

在路径上还有 $m$ 个能量提升点。第 $i$ 个能量提升点位于位置 $x_i$，其值为 $v_i$。当 Mualani 处于位置 $x_i$ 时，她可以选择收集该能量提升点，将她的跳跃能力增加 $v_i$。在同一个位置可能有多个能量提升点。当她处于有多个能量提升点的位置时，她可以选择收集或忽略每个单独的能量提升点。没有能量提升点位于任何障碍物的区间内。

Mualani 必须收集最少的能量提升点数才能到达位置 $L$ 完成冲浪路径。如果无法完成冲浪路径，则输出 $-1$。

## 输入格式

第一行包含一个整数 $t$ ($1 \leq t \leq 10^4$) — 测试用例的数量。

每个测试用例的第一行包含三个整数 $n$, $m$, 和 $L$ ($1 \leq n, m \leq 2 \cdot 10^5, 3 \leq L \leq 10^9$) — 障碍物的数量，能量提升点的数量，以及终点的位置。

接下来的 $n$ 行每行包含两个整数 $l_i$ 和 $r_i$ ($2 \leq l_i \leq r_i \leq L-1$) — 第 $i$ 个障碍物的区间边界。保证对于所有 $1 \leq i < n$，有 $r_i + 1 < l_{i+1}$（即所有障碍物都是非重叠的，按递增位置排序，并且前一个障碍物的终点与下一个障碍物的起点不连续）。

接下来的 $m$ 行每行包含两个整数 $x_i$ 和 $v_i$ ($1 \leq x_i, v_i \leq L$) — 第 $i$ 个能量提升点的位置和值。在所有测试用例中，能量提升点的数量总和不超过 $2 \cdot 10^5$。保证对于所有 $1 \leq i < m$，有 $x_i \leq x_{i+1}$（即能量提升点按非递减位置排序），并且没有能量提升点位于任何障碍物的区间内。

## 输出格式

对于每个测试用例，输出她必须收集的最少能量提升点数才能到达位置 $L$。如果无法完成，则输出 $-1$。

## 样例 #1

### 输入

```
4
2 5 50
7 14
30 40
2 2
3 1
3 5
18 2
22 32
4 3 50
4 6
15 18
20 26
34 38
1 2
8 2
10 2
1 4 17
10 14
1 6
1 2
1 2
16 9
1 2 10
5 9
2 3
2 2
```

### 输出

```
4
-1
1
2
```



---

---
title: "Bonus Project"
layout: "post"
diff: 普及/提高-
pid: CF2038A
tag: ['贪心']
---

# Bonus Project

## 题目描述

有 $n$ 名编号为 $1$ 到 $n$ 的软件工程师。他们的老板承诺，如果他们完成一个额外项目，将给他们发放奖金。完成这个项目总共需要 $k$ 个单位的工作。给第 $i$ 名工程师的奖金是 $a_i$ 。第 $i$ 名工程师估计他们的一个单位的工作价值为 $b_i$ 。如果奖金发放了，那么第 $i$ 名工程师完成 $c$ 个单位的工作的收益 $s_i$ 定义为 $s_i = a_i - c \cdot b_i$。如果奖金不发放，工程师将不会自愿做任何工作。工程师们已经一起工作了很多年，所以他们知道奖金将如何分配，以及他们的同事对劳动的估值是多少。也就是说，团队中的每个工程师都知道所有的 $a_i$ 和 $b_i$。工程师们渴望得到奖金，所以他们同意按照以下过程在他们之间分配工作：
- 第一名工程师说：“我将完成 $c_1$ 个单位的工作”，其中 $c_1$ 是一个非负整数；
- 然后，第二名工程师说：“我将完成 $c_2$ 个单位的工作”，其中 $c_2$ 是一个非负整数；
-... 以此类推；
- 最后，第 $n$ 名工程师说：“我将完成 $c_n$ 个单位的工作”，其中 $c_n$ 是一个非负整数。


每个工程师都会说出一个 $c_i$ 来最大化他们自己的收益 $s_i$。如果预期的收益为零，工程师仍然会同意工作以获得经验并帮助他们的同事获得奖金。然而，如果出于某种原因预期的收益为负（工程师需要进行过量的工作，或者项目无法完成），那么该工程师将不会进行任何工作（完成0个单位的工作）。假设每个工程师的行为都是完美的，你的任务是找出每个工程师所说的数字 $c_i$。

## 输入格式

第一行包含两个整数 $n$ 和 $k$（$1 \leq n \leq 1000$；$1 \leq k \leq 10^6$），分别表示公司中的工程师人数和项目所需的工作单位数。第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \leq a_i \leq 10^9$），其中 $a_i$ 表示如果项目完成，将支付给第 $i$ 位工程师的奖金。第三行包含 $n$ 个整数 $b_1, b_2, \ldots, b_n$（$1 \leq b_i \leq 1000$），其中 $b_i$ 表示第 $i$ 位工程师的工作单位成本。

## 输出格式

第一行包含两个整数 $n$ 和 $k$（$1 \leq n \leq 1000$；$1 \leq k \leq 10^6$），分别表示公司中的工程师人数和项目所需的工作单位数。第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \leq a_i \leq 10^9$），其中 $a_i$ 表示如果项目完成，将支付给第 $i$ 位工程师的奖金。第三行包含 $n$ 个整数 $b_1, b_2, \ldots, b_n$（$1 \leq b_i \leq 1000$），其中 $b_i$ 表示第 $i$ 位工程师的工作单位成本。

## 说明/提示

在这两个例子中，工程师们分配了工作并获得了奖金，即使第三个工程师的收益为零。在第二个例子中，奖金项目需要太多工作量才能完成，所以工程师们根本不工作反而更有益。

## 样例 #1

### 输入

```
3 6
4 7 6
1 2 3
```

### 输出

```
1 3 2
```

## 样例 #2

### 输入

```
3 12
4 7 6
1 2 3
```

### 输出

```
0 0 0
```

## 样例 #3

### 输入

```
3 11
6 7 8
1 2 3
```

### 输出

```
6 3 2
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
title: "Competitive Fishing"
layout: "post"
diff: 普及/提高-
pid: CF2042C
tag: ['贪心']
---

# Competitive Fishing

## 题目描述

Alice 和 Bob 参加了一个钓鱼比赛，他们一共钓到了 $n$ 条鱼，鱼的大小从 $1$ 到 $n$ 升序排序。

两人的总分计算如下：首先，选择一个整数 $m$，所有鱼都被依次分到 $m$ 个非空连续区间，一条鱼只能被分到一个区间，并且区间从小到大排列。比如：第二个区间的鱼必须全部大于第一个区间的鱼。

接着，每条鱼都按照区间编号被分配了分数，第 $1$ 个区间的鱼分数全部为 $0$，第 $1$ 个区间鱼的分数全部为 $1$……第 $i$ 个区间鱼的分数全部为 $(i-1)$。

两人的分数即为他们各自钓到鱼的分数之和。

你想要让 Bob 的分数比 Alice 高至少 $k$ 分。求划分的区间个数 $m$ 的最小值。

## 输入格式

第一行，一个整数 $t$ ($1\le t \le 10^4$)，表示数据组数。

对于每组数据：

第一行，两个整数 $n,k$ ($1\le n\le 2\times 10^5$；$1\le k\le 10^9$)。

第二行，一个长度为 $n$ 的 0-1 字符串，第 $i$ 个位置为 $1$，代表第 $i$ 条鱼属于 Alice。第 $i$ 个位置为 $0$，代表第 $i$ 条鱼属于 Bob。

## 输出格式

对于每组数据，输出一行，一个整数，表示将鱼分成组数的最小值。如果无解，输出 -1。

翻译：[HYdroKomide](https://www.luogu.com.cn/user/299883)

## 样例 #1

### 输入

```
7
4 1
1001
4 1
1010
4 1
0110
4 2
0110
6 3
001110
10 20
1111111111
5 11
11111
```

### 输出

```
2
-1
2
-1
3
4
-1
```



---

---
title: "Kevin and Binary Strings"
layout: "post"
diff: 普及/提高-
pid: CF2048C
tag: ['贪心', '位运算']
---

# Kevin and Binary Strings

## 题目描述

Kevin 在月光河公园的河里发现了一个二进制字符串 $s$，它以 1 开头，并把它交给了你。你的任务是从 $s$ 中选择两个非空子串（允许重叠），以使得它们之间的异或值最大。

对于两个二进制字符串 $a$ 和 $b$，它们的异或结果是将 $a$ 和 $b$ 看作二进制数后，进行按位异或操作 $\oplus$ 所得到的结果，其中最左边的位即为最高位。可以参考[按位异或操作](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

你选择的字符串可以包含前导零。

## 输入格式

输入包含多个测试用例。第一行是测试用例的数量 $t$（$1 \le t \le 10^3$）。

接下来的每个测试用例有一行，包含一个以 1 开头的二进制字符串 $s$（$1 \le |s| \le 5000$）。

保证所有测试用例中 $|s|$ 的总长度不超过 $5000$。

## 输出格式

对于每个测试用例，输出四个整数 $l_1, r_1, l_2, r_2$（$1 \le l_1 \le r_1 \le |s|$, $1 \le l_2 \le r_2 \le |s|$）——表示你选择的两个子串分别是 $s_{l_1} s_{l_1 + 1} \ldots s_{r_1}$ 和 $s_{l_2} s_{l_2 + 1} \ldots s_{r_2}$。

如果存在多种可能的解，输出任意一种即可。

## 说明/提示

在第一个测试用例中，我们可以选择 $s_2 = \texttt{1}$ 和 $s_1 s_2 s_3 = \texttt{111}$，此时 $\texttt{1} \oplus \texttt{111} = \texttt{110}$。可以证明这是可能得到的最大值。此外，选择 $l_1 = 3$，$r_1 = 3$，$l_2 = 1$，$r_2 = 3$ 也是一个有效的解决方案。

在第二个测试用例中，选择 $s_1 s_2 s_3 = \texttt{100}$ 和 $s_1 s_2 s_3 s_4 = \texttt{1000}$，则异或结果为 $\texttt{100} \oplus \texttt{1000} = \texttt{1100}$，也是最大的结果。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
111
1000
10111
11101
1100010001101
```

### 输出

```
2 2 1 3
1 3 1 4
1 5 1 4
3 4 1 5
1 13 1 11
```



---

---
title: "pspspsps"
layout: "post"
diff: 普及/提高-
pid: CF2049B
tag: ['贪心', '鸽笼原理']
---

# pspspsps

## 题目描述

# pspspsps


猫会被 $ pspspsps $ 所吸引，但 $ Evirir $ 作为一条有尊严的龙，只被具有奇怪特定要求的 $ pspspsps $ 所吸引......

给定一个长度为 $ n $ 的字符串 $ s = s_1s_2 \dots s_n $  ，由字符 $ p、s $ 和 $.$（点）组成，确定长度为 $ n $ 的排列 $ ^{∗} $ $ p $ 是否存在，使得对于所有整数 $ i $ （ $ 1 \le i \le n $ ）：

- 如果 $ s_i $ 是 $ p $，那么 $ [p_1， p_2， \dots， p_i] $ 形成一个排列（长度为 $ i $ ）;
- 如果 $ s_i $ 是 $ s $，那么 $ [p_i， p_{i+1}， \dots， p_{n}] $ 形成一个排列（长度为 $ n-i+1 $ ）;
- 如果 $ s_i $ 为 $ . $（点），则没有其他限制。

$ ^{∗} $ 长度为 $ n $ 的排列是一个数组，由 $ n $ 个从 $ 1 $ 到 $ n $ 的任意顺序的不同的整数组成。例如，$ [2,3,1,5,4] $ 是排列，但 $ [1,2,2] $ 不是排列（ $ 2 $ 在数组中出现两次），$ [1,3,4] $ 也不是排列（ $ n=3 $ 但数组中有 $ 4 $）。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $ t $ （ $ 1 \le t \le 10^4 $ ）。测试用例的描述如下。

每个测试用例的第一行包含一个整数 $ n $ （ $ 1 \le n \le 500 $ ），长度为 $ s $ 。

每个测试用例的第二行包含一个长度为 $ n $ 的字符串 $ s $，该字符串由字符 $ p、s $ 和 $ . $ （点） 组成。

保证所有测试用例的 $ n $ 之和不超过 $ 5000 $ 。

## 输出格式

对于每个测试用例，在一行上输出 YES 或 NO。如果存在这样的排列，则输出 YES，否则输出 NO。

答案忽视字母大小写。例如，字符串 “yEs”、“yes”、“Yes” 和 “YES” 将会被判定正确。

## 样例 #1

### 样例输入 #1

```
9
4
s.sp
6
pss..s
5
ppppp
2
sp
4
.sp.
8
psss....
1
.
8
pspspsps
20
....................
```

### 样例输出 #1

```
YES
NO
YES
YES
NO
NO
YES
NO
YES
```

## 说明/提示

对于第一个测试用例，一个有效的排列是 $ p = [3， 4， 1， 2] $ 。要求如下：

- $ s_1 = s $： $ [p_1， p_2， p_3， p_4] = [3， 4， 1， 2] $ 形成排列。
- $ s_2 = . $（点）：无其它要求。
- $ s_3 = s $： $ [p_3， p_4] = [1， 2] $ 形成排列。
- $ s_4 = p $： $ [p_1， p_2， p_3， p_4] = [3， 4， 1， 2] $ 形成排列。

对于第二个测试用例，可以证明没有满足所有要求的排列。

对于第三个测试用例，满足要求的一个排列是 $ p = [1， 2， 3， 4， 5] $ 。

## 样例 #1

### 输入

```
9
4
s.sp
6
pss..s
5
ppppp
2
sp
4
.sp.
8
psss....
1
.
8
pspspsps
20
....................
```

### 输出

```
YES
NO
YES
YES
NO
NO
YES
NO
YES
```



---

---
title: "Digital string maximization"
layout: "post"
diff: 普及/提高-
pid: CF2050D
tag: ['贪心']
---

# Digital string maximization

## 题目描述

给你一个由 $0$ 至 $9$ 的数字组成的字符串 $s$ 。在一次运算中，您可以选取该字符串中除 $0$ 或最左边数字之外的任意数字，将其减少 $1$ ，然后将其与左边的数字对调。

例如，从字符串 $1023$ 中进行一次运算，可以得到 $1103$ 或 $1022$ 。

找出任意多次运算后所能得到的字典序最大的字符串。

## 输入格式

输入的第一行是一个整数 $t$ ( $1 \le t \le 10^4$ ) - 测试用例的数量。

每个测试用例由一行数字字符串 $s$ ( $1 \le |s| \le 2\cdot 10^5$ ) 组成，其中 $|s|$ 表示 $s$ 的长度。字符串不包含前导零。

保证所有测试用例的 $|s|$ 之和不超过 $2\cdot 10^5$ 。

## 输出格式

对于每个测试用例，在单独一行中打印其对应的答案。

## 样例 #1

### 样例输入 #1

```
6
19
1709
11555
51476
9876543210
5891917899
```

### 样例输出 #1

```
81
6710
33311
55431
9876543210
7875567711
```

### 样例解释


在第一个样例中，以下操作顺序是合适的： $19 \rightarrow 81$ .

在第二个样例中，适合使用以下操作序列： $1709 \rightarrow 1780 \rightarrow 6180 \rightarrow 6710$ .

在第四个样例中，以下操作序列是合适的： $51476 \rightarrow 53176 \rightarrow 53616 \rightarrow 53651 \rightarrow 55351 \rightarrow 55431$ .

## 样例 #1

### 输入

```
6
19
1709
11555
51476
9876543210
5891917899
```

### 输出

```
81
6710
33311
55431
9876543210
7875567711
```



---

---
title: "Skibidus and Fanum Tax (hard version)"
layout: "post"
diff: 普及/提高-
pid: CF2065C2
tag: ['贪心', '二分']
---

# Skibidus and Fanum Tax (hard version)

## 题目描述

这是这道题的困难版本。在该版本中，$m \leq 2\cdot 10^5$。

Skibidus 有两个数组 $a$ 和 $b$，分别包含 $n$ 个和 $m$ 个元素。对于 $1$ 到 $n$ 的每个整数 $i$，他**最多**可以执行一次以下操作：

- 选择一个整数 $j$（$1 \leq j \leq m$），将 $a_i$ 赋值为 $b_j - a_i$。注意，经过此操作后，$a_i$ 可能变为非正数。

Skibidus 需要你的帮助，判断是否可以通过若干次上述操作，使得数组 $a$ 为非递减序列。

$^{\text{∗}}$ 若 $a_1 \leq a_2 \leq \dots \leq a_n$，则数组 $a$ 为非递减序列。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$），表示表示测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$1 \leq n \leq 2 \cdot 10^5$，$1 \leq m \leq 2 \cdot 10^5$）。

接下来一行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \leq a_i \leq 10^9$）。

接下来一行包含 $m$ 个整数 $b_1, b_2, \dots, b_m$（$1 \leq b_i \leq 10^9$）。

保证所有测试用例中，$n$ 的总和以及 $m$ 的总和都不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果可以使 $a$ 按非递减顺序排列，则在新的一行输出 `YES`，否则输出 `NO`。

## 说明/提示

- 在第一个测试用例中， $[5]$ 已经是非递减序列。
- 在第二个测试用例中，可以证明无法使其非递减。
- 在第三个测试用例中，我们可以将 $a_2$ 更新为 $b_1 - a_2 = 6 - 4 = 2$，将 $a_3$ 更新为 $b_3 - a_3 = 8 - 6 = 2$。此时数组变为 $[2,2,2,5]$，为非递减序列。
- 在最后一个测试用例中，我们可以对每个位置均执行操作，数组变为 $[-1,0,1]$，是非递减序列。

## 样例 #1

### 输入

```
5
1 3
5
9 1 1000000000
3 2
1 4 3
3 4
4 3
2 4 6 5
6 1 8
5 2
6 4 5 4 5
4 1000
3 1
9 8 7
8
```

### 输出

```
YES
NO
YES
NO
YES
```



---

---
title: "Limited Repainting"
layout: "post"
diff: 普及/提高-
pid: CF2070C
tag: ['贪心', '二分']
---

# Limited Repainting

## 题目描述

给定一个由 $n$ 个单元格组成的条带，所有单元格初始均为红色。

在一次操作中，你可以选择一个连续的单元格段并将其涂成蓝色。涂色前，所选单元格可以是红色或蓝色（注意不能将其涂成红色）。你最多可以进行 $k$ 次操作（可以是零次）。

对于每个单元格，指定了所有操作完成后期望的颜色：红色或蓝色。

显然，有时无法在 $k$ 次操作内满足所有要求。因此，对于每个单元格，还指定了一个惩罚值，当该单元格在所有操作后呈现错误颜色时应用此惩罚。对于第 $i$ 个单元格，其惩罚值为 $a_i$。

最终涂色的总惩罚值定义为所有错误颜色单元格的惩罚值的最大值。如果没有错误颜色的单元格，总惩罚值为 $0$。

求可以达到的最小总惩罚值是多少？

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$1 \le n \le 3 \cdot 10^5$；$0 \le k \le n$）——条带长度和最大操作次数。

第二行包含一个由 $n$ 个字符 'R' 和/或 'B' 组成的字符串 $s$。'R' 表示该单元格应保持红色，'B' 表示该单元格应被涂成蓝色。

第三行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le 10^9$）——每个单元格的惩罚值。

所有测试用例的 $n$ 之和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——可达的最小总惩罚值。

## 说明/提示

第一个测试用例中，你可以将 $1$ 到 $3$ 号的单元格涂色。最终涂色为 BBBR。只有第 $2$ 号单元格颜色错误，因此总惩罚值为 $3$。

第二个测试用例中，若涂色为 BBBR 则总惩罚值为 $5$。但如果仅涂色 $1$ 号单元格得到 BRRR，则只有第 $3$ 号单元格颜色错误，总惩罚值为 $3$。

第三个测试用例中，可以分别涂色 $1$ 号单元格和 $3$ 号单元格。所有单元格颜色均正确，总惩罚值为 $0$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
4 1
BRBR
9 3 5 4
4 1
BRBR
9 5 3 4
4 2
BRBR
9 3 5 4
10 2
BRBRBBRRBR
5 1 2 4 5 3 6 1 5 4
5 5
RRRRR
5 3 1 2 4
```

### 输出

```
3
3
0
4
0
```



---

---
title: "Creating Keys for StORages Has Become My Main Skill"
layout: "post"
diff: 普及/提高-
pid: CF2072C
tag: ['贪心', '位运算', '构造']
---

# Creating Keys for StORages Has Become My Main Skill

## 题目描述

Akito 仍然无处可住，而小房间的价格却居高不下。为此，Akito 决定在银行找一份为存储设备创建密钥的工作。

在这个魔法世界中，一切都与众不同。例如，代码为 $(n, x)$ 的存储设备的密钥是一个满足以下条件的长度为 $n$ 的数组 $a$：

- $a_1 \mid a_2 \mid a_3 \mid \ldots \mid a_n = x$，其中 $a \mid b$ 表示数 $a$ 和 $b$ 的[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。
- $\text{MEX}(\{ a_1, a_2, a_3, \ldots, a_n \})$ $^{\text{∗}}$ 在所有满足条件的数组中达到最大值。

Akito 勤奋地工作了几个小时，但突然头痛发作。请代替他工作一小时：对于给定的 $n$ 和 $x$，创建任意一个满足代码为 $(n, x)$ 的存储设备的密钥。

$^{\text{∗}}$ $\text{MEX}(S)$ 是满足以下条件的最小非负整数 $z$：$z$ 不在集合 $S$ 中，且所有满足 $0 \le y < z$ 的 $y$ 都在集合 $S$ 中。

## 输入格式

第一行包含一个数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的唯一一行包含两个数 $n$ 和 $x$（$1 \le n \le 2 \cdot 10^5$，$0 \le x < 2^{30}$）——数组的长度和按位或运算的目标值。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数 $a_i$（$0 \le a_i < 2^{30}$）——满足所有条件的密钥数组元素。

如果存在多个符合条件的数组，输出其中任意一个即可。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
9
1 69
7 7
5 7
7 3
8 7
3 52
9 11
6 15
2 3
```

### 输出

```
69
6 0 3 4 1 2 5
4 1 3 0 2
0 1 2 3 2 1 0
7 0 6 1 5 2 4 3
0 52 0
0 1 8 3 0 9 11 2 10
4 0 3 8 1 2
0 3
```



---

---
title: "For Wizards, the Exam Is Easy, but I Couldn't Handle It"
layout: "post"
diff: 普及/提高-
pid: CF2072D
tag: ['数学', '贪心', '枚举']
---

# For Wizards, the Exam Is Easy, but I Couldn't Handle It

## 题目描述

Akito 厌倦了在银行当普通锁匠的工作，因此他决定进入魔法学院并成为世界上最强的巫师！然而，为了入学，他需要解决考试中的唯一一道题目，而这位雄心勃勃的英雄却未能成功。

题目给出一个长度为 $n$ 的数组 $a$。Akito 需要在使用恰好一次咒语后，使数组中的逆序对数量 $^{\text{∗}}$ 最小化。咒语的使用方式很简单：Akito 必须选择两个数 $l$ 和 $r$（满足 $1 \le l \le r \le n$），并对子数组 $[l, r]$ 进行一次向左循环移位。

更正式地说，Akito 选择子数组 $[l, r]$ 并按以下方式修改数组：

- 原始数组为 $[a_1, a_2, \ldots, a_{l - 1}, \mathbf{ a_l }, \mathbf{ a_{l + 1} }, \mathbf{ \ldots }, \mathbf{ a_{r - 1} }, \mathbf{ a_r }, a_{r + 1}, \ldots, a_{n - 1}, a_n]$，修改后的数组变为 $[a_1, a_2, \ldots, a_{l - 1}, \mathbf{ a_{l + 1} }, \mathbf{ a_{l + 2} }, \mathbf{ \ldots }, \mathbf{ a_{r - 1} }, \mathbf{ a_{r} }, \mathbf{ a_{l} }, a_{r + 1}, \ldots, a_{n - 1}, a_{n}]$。

Akito 渴望开始他的学习，但他仍未通过考试。请帮助他入学并解决这道题目！

$^{\text{∗}}$ 在长度为 $m$ 的数组 $b$ 中，逆序对被定义为满足 $1 \le i < j \le m$ 且 $b_i > b_j$ 的索引对 $(i, j)$。例如，在数组 $b = [3, 1, 4, 1, 5]$ 中，逆序对为索引对 $(1, 2)$、$(1, 4)$ 和 $(3, 4)$。

## 输入格式

输入的第一行包含一个数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含一个数 $n$（$1 \le n \le 2000$）——数组 $a$ 的长度。

每个测试用例的第二行包含 $n$ 个数 $a_i$（$1 \le a_i \le 2000$）——数组 $a$ 的元素。

保证所有测试用例的 $n^2$ 之和不超过 $4 \cdot 10^6$。

## 输出格式

对于每个测试用例，输出两个数 $l$ 和 $r$（$1 \le l \le r \le n$）——选择的子数组边界，使得应用咒语后数组的逆序对数量最小。

如果存在多个符合条件的边界对，可以输出其中任意一个。

## 说明/提示

在第一个示例中，数组 $[1, 4, 3, 2, 5, 3, 3]$ 将变为 $[1, 3, 2, 5, 3, 3, 4]$。其中的逆序对为 $(2, 3)$、$(4, 5)$、$(4, 6)$ 和 $(4, 7)$。可以证明无法获得少于 $4$ 个逆序对。

在第二个示例中，数组 $[1, 4, 3, 2, 5, 3]$ 将变为 $[1, 3, 2, 4, 5, 3]$。其中的逆序对为 $(2, 3)$、$(4, 6)$ 和 $(5, 6)$。选择 $l = 2$ 和 $r = 6$ 同样有效，此时数组变为 $[1, 3, 2, 5, 3, 4]$，其中也有 $3$ 个逆序对：$(2, 3)$、$(4, 5)$ 和 $(4, 6)$。可以证明无法获得少于 $3$ 个逆序对。

在第四个示例中，选择 $l = 4$ 和 $r = 6$ 将数组变为 $[1, 1, 1, 1, 1, 5, 5, 6, 7, 8]$。该数组已排序，因此没有逆序对。

在最后一个示例中，数组初始时已排序，因此对长度至少为 $2$ 的段进行任何操作只会增加逆序对的数量。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
9
7
1 4 3 2 5 3 3
6
1 4 3 2 5 3
8
7 6 5 8 4 3 2 1
10
1 1 1 5 1 1 5 6 7 8
2
1337 69
4
2 1 2 1
3
998 244 353
3
1 2 1
9
1 1 2 3 5 8 13 21 34
```

### 输出

```
2 7
2 4
1 8
4 6
1 2
1 4
1 3
2 3
5 5
```



---

---
title: "Breach of Faith"
layout: "post"
diff: 普及/提高-
pid: CF2077A
tag: ['数学', '贪心']
---

# Breach of Faith

## 题目描述

[Breach of Faith - Supire feat.eili](https://www.youtube.com/watch?v=nVTiCKIIQSM)

你和你的团队不懈努力，最终得到了一个满足以下性质的正整数序列 $a_1, a_2, \ldots, a_{2n+1}$：

- 对于所有 $1 \le i \le 2n + 1$，有 $1 \le a_i \le 10^{18}$。
- $a_1, a_2, \ldots, a_{2n+1}$ 两两互不相同。
- $a_1 = a_2 - a_3 + a_4 - a_5 + \ldots + a_{2n} - a_{2n+1}$。

然而，与你合作的人为了抢先发表这个序列而背叛了你。他们从序列中删除了一个数并将其余数打乱，留下了一个序列 $b_1, b_2, \ldots, b_{2n}$。你已经忘记了原序列 $a$，现在需要找到一种方法恢复它。

如果有多个可能的序列，你可以输出其中任意一个。根据题目约束条件可以证明至少存在一个满足条件的序列 $a$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 2 \cdot 10^5$）。

每个测试用例的第二行包含 $2n$ 个互不相同的整数 $b_1, b_2, \ldots, b_{2n}$（$1 \leq b_i \leq 10^9$），表示序列 $b$。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出 $2n+1$ 个互不相同的整数，表示序列 $a$（$1 \leq a_i \leq 10^{18}$）。

如果有多个可能的序列，可以输出其中任意一个。输出的序列 $a$ 必须满足给定条件，并且删除其中一个元素并打乱后可以得到序列 $b$。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
1
9 2
2
8 6 1 4
3
99 2 86 33 14 77
2
1 6 3 2
```

### 输出

```
7 9 2
1 8 4 6 9
86 99 2 77 69 14 33
4 6 1 2 3
```



---

---
title: "You Soared Afar With Grace"
layout: "post"
diff: 普及/提高-
pid: CF2084C
tag: ['数学', '贪心']
---

# You Soared Afar With Grace

## 题目描述

给定两个长度为 $n$ 的排列 $a$ 和 $b$ $^{\text{∗}}$。你最多可以进行 $n$ 次如下操作：

- 选择两个下标 $i$ 和 $j$（$1 \le i, j \le n$，$i \ne j$），交换 $a_i$ 和 $a_j$，同时交换 $b_i$ 和 $b_j$。

判断是否可以通过这些操作使得 $a$ 和 $b$ 互为逆序排列。换句话说，对于每个 $i = 1, 2, \ldots, n$，满足 $a_i = b_{n + 1 - i}$。

如果可能，输出任意一个有效的操作序列；否则输出 $-1$。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（因为 $n=3$ 但数组中包含 $4$）。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 2 \cdot 10^5$）——排列的长度。  
第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le n$）。  
第三行包含 $n$ 个整数 $b_1, b_2, \ldots, b_n$（$1 \le b_i \le n$）。  

保证 $a$ 和 $b$ 都是长度为 $n$ 的排列。  
保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例：  
- 如果不可能满足条件，输出一行 $-1$。  
- 否则，第一行输出一个整数 $m$（$0 \le m \le n$）表示操作次数。接下来的 $m$ 行，每行输出两个整数 $i$ 和 $j$（$1 \le i, j \le n$，$i \ne j$），表示每次操作交换的下标。如果有多个解，输出任意一个即可。

## 说明/提示

- 在第二个测试用例中，$b$ 已经是 $a$ 的逆序排列，因此不需要操作。  
- 在第三个测试用例中，执行以下操作后，$b$ 将成为 $a$ 的逆序排列：  
  - 交换 $a_1, a_2$ 和 $b_1, b_2$。此时 $a = [3, 1, 2, 4]$，$b = [4, 2, 1, 3]$。  
- 在第四个测试用例中，按顺序执行以下操作后，$b$ 将成为 $a$ 的逆序排列：  
  - 交换 $a_1, a_2$ 和 $b_1, b_2$。此时 $a = [5, 2, 1, 3, 4]$，$b = [5, 3, 4, 2, 1]$。  
  - 交换 $a_1, a_3$ 和 $b_1, b_3$。此时 $a = [1, 2, 5, 3, 4]$，$b = [4, 3, 5, 2, 1]$。  

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2
1 2
1 2
2
1 2
2 1
4
1 3 2 4
2 4 1 3
5
2 5 1 3 4
3 5 4 2 1
5
3 1 2 4 5
1 2 3 4 5
```

### 输出

```
-1
0
1
1 2
2
1 2
1 3
-1
```



---

---
title: "Serval and The Formula"
layout: "post"
diff: 普及/提高-
pid: CF2085C
tag: ['贪心', '进制', '位运算']
---

# Serval and The Formula

## 题目描述

给定两个正整数 $x$ 和 $y$（$1 \le x, y \le 10^9$）。

请找到一个非负整数 $k \le 10^{18}$，使得等式 $(x + k) + (y + k) = (x + k) \oplus (y + k)$ 成立$^{\text{∗}}$，或判断这样的整数不存在。

$^{\text{∗}}$符号 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。


## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的唯一一行包含两个整数 $x$ 和 $y$（$1 \le x, y \le 10^9$）——给定的整数。


## 输出格式

对于每个测试用例，输出一个整数 $k$（$0 \le k \le 10^{18}$）——找到的符合条件的整数。若不存在这样的整数，输出 $-1$。

若存在多个答案，输出任意一个即可。

## 说明/提示

第一个测试案例中，由于 $(2 + 0) + (5 + 0) = (2 + 0) \oplus (5 + 0) = 7$，因此 $k = 0$ 是合法答案。注意 $k = 4$ 也是一个合法答案，因为 $(2 + 4) + (5 + 4) = (2 + 4) \oplus (5 + 4) = 15$。

第二个测试案例中，$(x + k) \oplus (y + k) = (6 + k) \oplus (6 + k) = 0$。然而对于所有 $k \ge 0$，$(x + k) + (y + k) > 0$ 恒成立，因此这样的整数 $k$ 不存在。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
2 5
6 6
19 10
1024 4096
1198372 599188
```

### 输出

```
0
-1
1
1024
28
```



---

---
title: "Place of the Olympiad"
layout: "post"
diff: 普及/提高-
pid: CF2091D
tag: ['数学', '贪心', '二分']
---

# Place of the Olympiad

## 题目描述

首届 IT Campus "NEIMARK" 奥林匹克的决赛场地被布置为一个矩形区域。你可以认为该场地被划分为 $n$ 行，每行包含 $m$ 个参赛者座位的点位。共有 $k$ 名参赛者注册了决赛，每位参赛者将坐在单独的座位上。现在，组委会需要为这些座位选择具体位置。

每个座位占据某一行中的 $m$ 个点位之一。此外，若同一行中多个连续的座位被占据，我们称这样的座位组为一个长凳，组内座位的数量称为长凳的长度。例如，在 $3 \times 4$ 的场地（$n = 3$, $m = 4$）中安排 $7$ 名参赛者的座位可能如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091D/f5385f1942a12d0af05982f4772fe392160619db.png)  
上图中，第一行有一个长度为 $3$ 的长凳，第二行有一个长度为 $2$ 的长凳，第三行有两个长度为 $1$ 的长凳。

组委会希望选择座位位置使得最长长凳的长度尽可能小。例如，同样的 $7$ 个座位可以被更优地安排，使得所有长凳的长度都不超过 $2$：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091D/cb2856101ccbe650ed0a0bdeca813ffe1ec02c80.png)  
给定整数 $n$、$m$ 和 $k$，请确定最长长凳的最小可能长度。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ($1 \leq t \leq 10^4$)。接下来是每个测试用例的描述。

每个测试用例单独一行，包含三个正整数 $n$、$m$、$k$ ($1 \leq n, m, k \leq 10^9$, $k \leq n \cdot m$)。


## 输出格式

对于每个测试用例，输出一个数字 —— 最长长凳的最小可能长度。


## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3 4 7
5 5 5
1 13 2
2 4 7
1 5 4
```

### 输出

```
2
1
1
4
2
```



---

---
title: "Boneca Ambalabu"
layout: "post"
diff: 普及/提高-
pid: CF2094E
tag: ['贪心', '位运算']
---

# Boneca Ambalabu

## 题目描述

Boneca Ambalabu 给你一个包含 $n$ 个整数的序列 $a_1,a_2,\ldots,a_n$。

在所有 $1 \leq k \leq n$ 中，输出 $(a_k \oplus a_1) + (a_k \oplus a_2) + \ldots + (a_k \oplus a_n)$ 的最大值。注意 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——独立测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 2 \cdot 10^5$）——数组的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1,a_2,\ldots,a_n$（$0 \leq a_i < 2^{30}$）。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，在新的一行输出最大值。

## 说明/提示

在第一个测试用例中，我们能得到的最大值是 $(18 \oplus 18) + (18 \oplus 18) + (18 \oplus 18) = 0$。

在第二个测试用例中，我们选择 $k=5$ 得到 $(16 \oplus 1) + (16 \oplus 2) + (16 \oplus 4) + (16 \oplus 8) + (16 \oplus 16) = 79$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
18 18 18
5
1 2 4 8 16
5
8 13 4 5 15
6
625 676 729 784 841 900
1
1
```

### 输出

```
0
79
37
1555
0
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
title: "Array and GCD"
layout: "post"
diff: 普及/提高-
pid: CF2104D
tag: ['贪心', '素数判断,质数,筛法', '前缀和']
---

# Array and GCD

## 题目描述

给定一个大小为 $n$ 的整数数组 $a$。

你可以执行以下操作任意次数（包括零次）：
- 支付 1 枚硬币并将数组中的任意一个元素增加 $1$（执行此操作时你至少需要有 1 枚硬币）；
- 获得 1 枚硬币并将数组中的任意一个元素减少 $1$。

我们称一个数组是理想的，当且仅当满足以下两个条件：
1. 数组中的每个元素都至少为 $2$；
2. 对于任意两个不同的下标 $i$ 和 $j$（$1 \le i, j \le n$；$i \ne j$），$a_i$ 和 $a_j$ 的最大公约数（GCD）等于 $1$。如果数组元素少于 2 个，则此条件自动满足。

我们称一个数组是美丽的，如果可以通过上述操作将其转换为理想数组，且初始时你没有硬币。如果数组已经是理想的，那么它也是美丽的。

给定的数组不一定是美丽或理想的。你可以从中删除任意数量的元素（包括删除整个数组或不删除任何元素）。你的任务是计算为了使数组变得美丽，最少需要删除多少个元素（可以是零个）。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 4 \cdot 10^5$）。

第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$2 \le a_i \le 10^9$）。

输入数据的额外约束：所有测试用例的 $n$ 之和不超过 $4 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——为了使数组变得美丽，最少需要删除的元素数量（可以是零个）。


## 说明/提示

在第一个样例中，你不需要删除任何元素，因为数组已经是美丽的。可以通过以下操作将其转换为理想数组：$[5, 5, 5] \rightarrow [4, 5, 5] \rightarrow [4, 4, 5] \rightarrow [4, 3, 5]$（最终你会拥有 3 枚硬币）。

在第二个样例中，你需要删除 2 个元素才能使数组变得美丽。如果保留元素 $[2, 3]$ 并删除其他元素，那么给定的数组已经是理想的（因此也是美丽的）。

在第三个样例中，你不需要删除任何元素，因为数组已经是理想的（因此也是美丽的）。

在第四个样例中，数组是美丽的。可以通过以下操作将其转换为理想数组：$[2, 100, 2] \rightarrow [2, 99, 2] \rightarrow [2, 99, 3] \rightarrow [2, 98, 3] \rightarrow [2, 97, 3]$（最终你会拥有 2 枚硬币）。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
5 5 5
4
2 3 2 4
1
3
3
2 100 2
5
2 4 2 11 2
```

### 输出

```
0
2
0
0
1
```



---

---
title: "Unpleasant Strings"
layout: "post"
diff: 普及/提高-
pid: CF2104E
tag: ['动态规划 DP', '贪心']
---

# Unpleasant Strings

## 题目描述

我们称一个字母是允许的，当且仅当它是小写字母且属于拉丁字母表的前 $k$ 个字母。

给定一个长度为 $n$ 的字符串 $s$，它仅由允许的字母组成。

我们称一个字符串 $t$ 是愉快的，当且仅当 $t$ 是 $s$ 的子序列。

给定 $q$ 个字符串 $t_1, t_2, \dots, t_q$，它们都仅由允许的字母组成。对于每个字符串 $t_i$，计算最少需要在它的右侧追加多少个允许的字母，才能使其不再愉快。

序列 $t$ 是序列 $s$ 的子序列，当且仅当 $t$ 可以通过从 $s$ 中删除若干个（可以是零个或全部）任意位置的元素得到。

## 输入格式

第一行包含两个整数 $n$ 和 $k$（$1 \le n \le 10^6$；$1 \le k \le 26$）——字符串 $s$ 的长度和允许的字母数量。

第二行包含字符串 $s$，由 $n$ 个小写拉丁字母组成。字符串的每个字符都是拉丁字母表的前 $k$ 个字母之一。

第三行包含一个整数 $q$（$1 \le q \le 2 \cdot 10^5$）——查询的数量。

接下来的 $q$ 行包含查询：每行一个查询。第 $i$ 行包含字符串 $t_i$，仅由允许的字母组成。

输入数据的额外约束：所有 $t_i$ 的总长度不超过 $10^6$。


## 输出格式

对于每个查询，输出一个整数——最少需要在字符串右侧追加的允许字母数量，使其不再愉快。


## 说明/提示

在第一个样例中：

1. 字符串 cc 已经是不愉快的，因此不需要追加任何字母；
2. bcb 是愉快的，因此至少需要在右侧追加一个字母：bcba 仍然会保持愉快，但 bcbb 和 bcbc 是不愉快的；
3. 对于 b，至少需要追加两个字母，因为 ba、bb 和 bc 都是愉快的。例如，我们可以得到一个不愉快的字符串 bbb。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7 3
abacaba
3
cc
bcb
b
```

### 输出

```
0
1
2
```

## 样例 #2

### 输入

```
5 1
aaaaa
6
a
aa
aaa
aaaa
aaaaa
aaaaaa
```

### 输出

```
5
4
3
2
1
0
```



---

---
title: "Flower Boy"
layout: "post"
diff: 普及/提高-
pid: CF2106D
tag: ['模拟', '贪心']
---

# Flower Boy

## 题目描述

花之少年有一个由 $n$ 朵花组成的花园，这些花可以表示为一个整数序列 $a_1, a_2, \dots, a_n$，其中 $a_i$ 表示从左数第 $i$ 朵花的美丽值。

伊戈尔想要收集恰好 $m$ 朵花。为此，他将从左到右遍历花园，并决定是否收集当前位置的花。他收集的第 $i$ 朵花的美丽值必须至少为 $b_i$。

伊戈尔发现，有时可能无法收集满足美丽值要求的 $m$ 朵花。因此，在开始收集之前，他可以选择任意一个整数 $k$，使用魔法棒培育一朵美丽值为 $k$ 的新花，并将其放置在花园中的任意位置（两朵花之间、第一朵花之前或最后一朵花之后）。由于魔法能力有限，他最多只能执行一次这个操作。

请输出伊戈尔执行上述操作时需要选择的最小整数 $k$，以确保他能收集到 $m$ 朵花。如果不需要操作就能收集 $m$ 朵花，则输出 $0$。如果即使执行操作也无法收集 $m$ 朵花，则输出 $-1$。

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$1 \le m \le n \le 2 \cdot 10^5$）——分别表示花园中的花朵数量和伊戈尔想要收集的花朵数量。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, ..., a_n$（$1 \le a_i \le 10^9$）——表示从左数第 $i$ 朵花的美丽值。

每个测试用例的第三行包含 $m$ 个整数 $b_1, b_2, ..., b_m$（$1 \le b_i \le 10^9$）——表示伊戈尔收集的第 $i$ 朵花必须满足的最小美丽值。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一行，表示伊戈尔执行操作时需要选择的最小整数 $k$。如果不需要操作，则输出 $0$；如果即使执行操作也无法满足条件，则输出 $-1$。


## 说明/提示

在第一个测试用例中，假设伊戈尔培育了一朵美丽值为 $6$ 的花，并将其放置在第三朵和第四朵花之间。此时花园变为 $[3, 5, 2, 6, 3, 3, 5, 8, 1, 2]$。然后，他可以选择第二、第四、第六、第七和第八朵花，其美丽值分别为 $[5, 6, 3, 5, 8]$。

在第三个测试用例中，他可以培育一朵美丽值为 $7$ 的花，并将其放在第一朵花之前。此时花园变为 $[7, 4, 3, 5, 4, 3]$。现在，他可以选择第一、第二和第四朵花。

在第四个测试用例中，伊戈尔不需要执行操作，因此答案为 $0$。

在第六个测试用例中，无论伊戈尔如何操作，都无法收集到 $3$ 朵满足美丽值要求的花，因此答案为 $-1$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
9 5
3 5 2 3 3 5 8 1 2
4 6 2 4 6
6 3
1 2 6 8 2 1
5 4 3
5 3
4 3 5 4 3
7 4 5
6 3
8 4 2 1 2 5
6 1 4
5 5
1 2 3 4 5
5 4 3 2 1
6 3
1 2 3 4 5 6
9 8 7
5 5
7 7 6 7 7
7 7 7 7 7
```

### 输出

```
6
3
7
0
-1
-1
7
```



---

---
title: "Maximum Subarray Sum"
layout: "post"
diff: 普及/提高-
pid: CF2107C
tag: ['贪心', '构造']
---

# Maximum Subarray Sum

## 题目描述

给你一个长为 $n$ 的序列 $a=(a_1,a_2,\cdots,a_n)$，$a$ 的一部分丢失了。你的任务是填补丢失的部分使得 $a$ 的最大子区间和为 $k$，或报告无解。

给你一个 01 串 $s$ 和 $a$：
- 如果 $a_i$ 没有被丢失，$s_i=1$，此时 $a_i$ 记录了它的真实值。
- 如果 $a_i$ 被丢失，$s_i=0$，此时给到你的序列 $a$ 中 $a_i=0$。

输入的 $a$ 满足 $\vert a_i\vert\le 10^6$，你填充后的 $a$ 需要满足 $\vert a_i\vert \le 10^{18}$。可以被证明如果存在解，那么一定存在一个满足 $\vert a_i\vert \le 10^{18}$ 的解。

一个长为 $n$ 的数列 $a$ 的最大子区间和是 $\max\limits_{1\le i\le j\le n}\sum\limits_{k=i}^j a_k$。

## 输入格式

多组数据，第一行一个整数为数据组数 $t(1\le t\le 10^4)$。

对于每组数据，第一行两个整数 $n,k(1\le n\le 2\times 10^5,1\le k\le 10^{12})$。\
第二行为一个长为 $n$ 的 01 字符串 $s$。\
第三行 $n$ 个整数 $a_1,a_2,\cdots,a_n(\vert a_i\vert\le 10^6)$。保证 $s_i=0$ 时 $a_i=0$。

保证一个测试点中 $\sum n\le 2\times 10^5$。

## 输出格式

对于每组数据，第一行一个字符串，如果有解输出 `Yes`，如果无解输出 `No`。大小写不敏感。

如果有解，第二行输出填充后的字符串 $a$。你需要保证 $\vert a_i\vert\le 10^{18}$。

如果有多种解法，输出任意一种均可。

## 说明/提示

第一组数据中，向唯一丢失的 $a_1$ 填充 $4$ 得到 $a=(4,0,1)$，它的最大子区间和为 $5$。

第二组数据中，向唯一丢失的 $a_3$ 填充 $5$ 得到 $a=(4,-3,5,-2,1)$，它的最大子区间和为 $6$。

第三组数据中 $a_1$ 和 $a_2$ 待填充，向它们填充 $2$ 得到 $a=(2,2,-4,-5)$，它的最大子区间和为 $4$。$a=(0,4,-4,-5)$ 也是一种解法。

对于第四组数据，没有合法的填充 $a$ 的方式。例如 $a=(1,2,0,5,-1,9)$，它的最大子区间和为 $16$ 而非 $12$。

By chenxi2009

## 样例 #1

### 输入

```
10
3 5
011
0 0 1
5 6
11011
4 -3 0 -2 1
4 4
0011
0 0 -4 -5
6 12
110111
1 2 0 5 -1 9
5 19
00000
0 0 0 0 0
5 19
11001
-8 6 0 0 -5
5 10
10101
10 0 10 0 10
1 1
1
0
3 5
111
3 -1 3
4 5
1011
-2 0 1 -5
```

### 输出

```
Yes
4 0 1
Yes
4 -3 5 -2 1
Yes
2 2 -4 -5
No
Yes
5 1 9 2 2
Yes
-8 6 6 7 -5
Yes
10 -20 10 -20 10
No
Yes
3 -1 3
Yes
-2 4 1 -5
```



---

---
title: "最大子区间和"
layout: "post"
diff: 普及/提高-
pid: CF2107C
tag: ['贪心', '构造']
---

# 最大子区间和

## 题目描述

给你一个长为 $n$ 的序列 $a=(a_1,a_2,\cdots,a_n)$，$a$ 的一部分丢失了。你的任务是填补丢失的部分使得 $a$ 的最大子区间和为 $k$，或报告无解。

给你一个 01 串 $s$ 和 $a$：
- 如果 $a_i$ 没有被丢失，$s_i=1$，此时 $a_i$ 记录了它的真实值。
- 如果 $a_i$ 被丢失，$s_i=0$，此时给到你的序列 $a$ 中 $a_i=0$。

输入的 $a$ 满足 $\vert a_i\vert\le 10^6$，你填充后的 $a$ 需要满足 $\vert a_i\vert \le 10^{18}$。可以被证明如果存在解，那么一定存在一个满足 $\vert a_i\vert \le 10^{18}$ 的解。

一个长为 $n$ 的数列 $a$ 的最大子区间和是 $\max\limits_{1\le i\le j\le n}\sum\limits_{k=i}^j a_k$。

## 输入格式

多组数据，第一行一个整数为数据组数 $t(1\le t\le 10^4)$。

对于每组数据，第一行两个整数 $n,k(1\le n\le 2\times 10^5,1\le k\le 10^{12})$。\
第二行为一个长为 $n$ 的 01 字符串 $s$。\
第三行 $n$ 个整数 $a_1,a_2,\cdots,a_n(\vert a_i\vert\le 10^6)$。保证 $s_i=0$ 时 $a_i=0$。

保证一个测试点中 $\sum n\le 2\times 10^5$。

## 输出格式

对于每组数据，第一行一个字符串，如果有解输出 `Yes`，如果无解输出 `No`。大小写不敏感。

如果有解，第二行输出填充后的字符串 $a$。你需要保证 $\vert a_i\vert\le 10^{18}$。

如果有多种解法，输出任意一种均可。

## 说明/提示

第一组数据中，向唯一丢失的 $a_1$ 填充 $4$ 得到 $a=(4,0,1)$，它的最大子区间和为 $5$。

第二组数据中，向唯一丢失的 $a_3$ 填充 $5$ 得到 $a=(4,-3,5,-2,1)$，它的最大子区间和为 $6$。

第三组数据中 $a_1$ 和 $a_2$ 待填充，向它们填充 $2$ 得到 $a=(2,2,-4,-5)$，它的最大子区间和为 $4$。$a=(0,4,-4,-5)$ 也是一种解法。

对于第四组数据，没有合法的填充 $a$ 的方式。例如 $a=(1,2,0,5,-1,9)$，它的最大子区间和为 $16$ 而非 $12$。

By chenxi2009

## 样例 #1

### 输入

```
10
3 5
011
0 0 1
5 6
11011
4 -3 0 -2 1
4 4
0011
0 0 -4 -5
6 12
110111
1 2 0 5 -1 9
5 19
00000
0 0 0 0 0
5 19
11001
-8 6 0 0 -5
5 10
10101
10 0 10 0 10
1 1
1
0
3 5
111
3 -1 3
4 5
1011
-2 0 1 -5
```

### 输出

```
Yes
4 0 1
Yes
4 -3 5 -2 1
Yes
2 2 -4 -5
No
Yes
5 1 9 2 2
Yes
-8 6 6 7 -5
Yes
10 -20 10 -20 10
No
Yes
3 -1 3
Yes
-2 4 1 -5
```



---

---
title: "Neo's Escape"
layout: "post"
diff: 普及/提高-
pid: CF2108C
tag: ['贪心', '枚举']
---

# Neo's Escape

## 题目描述

Neo 想要逃离矩阵世界。在他面前有一排 $n$ 个按钮，每个按钮都有一个整数权重：$a_1, a_2, \ldots, a_n$。

Neo 被固定住了，但他可以创建和移动克隆体。这意味着他可以按任意顺序执行以下两种操作，次数不限：

1. 在特定按钮前创建一个克隆体。
2. 将现有的克隆体向左或向右移动一个位置。

当一个克隆体位于尚未被按下的按钮前时（无论他是被创建还是被移动的），他会立即按下该按钮。如果按钮已经被按下过，克隆体不会做任何操作——每个按钮只能被按下一次。

为了成功逃脱，Neo 需要以特定的顺序按下所有按钮：按钮权重的序列必须是非递增的。也就是说，如果 $b_1, b_2, \ldots, b_n$ 是按按钮的顺序对应的权重，那么必须满足 $b_1 \geq b_2 \geq \cdots \geq b_n$。

你的任务是确定 Neo 需要创建的最少克隆体数量，以便能够以有效顺序按下所有按钮。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 2 \cdot 10^5$）——按钮的数量。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \leq a_i \leq 10^9$）——按钮的权重。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。


## 输出格式

对于每个测试用例，输出一个整数——为了以有效顺序按下所有按钮需要创建的最少克隆体数量。


## 说明/提示

在第一个测试用例中，Neo 可以按以下方式操作：

1. 在第五个按钮（权重为 $5$）前创建一个克隆体。
2. 在第一个按钮（权重为 $4$）前创建第二个克隆体。
3. 将第二个克隆体从第一个按钮移动到第二个按钮（权重为 $3$）。
4. 将第二个克隆体从第二个按钮移动到第三个按钮（权重为 $2$）。
5. 将第一个克隆体从第五个按钮移动到第四个按钮（权重为 $1$）。

这样，按钮按下的顺序将是 $5 \rightarrow 4 \rightarrow 3 \rightarrow 2 \rightarrow 1$，满足要求。可以证明，创建的克隆体数量是最小的。

在第二个测试用例中，Neo 可以按以下方式操作：

1. 在第二个按钮（权重为 $1$）前创建一个克隆体。
2. 将该克隆体从第二个按钮移动到第三个按钮（权重为 $1$）。
3. 将该克隆体从第三个按钮移回第二个按钮（已被按下）。
4. 将该克隆体从第二个按钮移动到第一个按钮（权重为 $1$）。

这样，按钮按下的顺序将是 $1 \rightarrow 1 \rightarrow 1$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
5
4 3 2 1 5
3
1 1 1
6
7 8 1 5 9 2
10
1 7 9 7 1 10 2 10 10 7
```

### 输出

```
2
1
2
3
```



---

---
title: "Smilo and Minecraft"
layout: "post"
diff: 普及/提高-
pid: CF2113C
tag: ['贪心', '枚举', '前缀和']
---

# Smilo and Minecraft

## 题目描述

Smilo 在玩 Minecraft！为了准备去打龙，他需要大量的金苹果，所以他需要大量的金子。因此，Smilo 准备下矿。

矿洞是一个 $n\times m$ 的矩形网格，每个格子可能是金矿、石头或空地。Smilo 可以在一个空地点燃炸药，这会将以此空地为中心的边长为 $2k+1$ 的正方形区域夷为平地。如果一个金矿在正方形的内部并且没有和边框相接触，那么它会直接消失；如果金矿在正方形的边框上（在内部并且和正方形的边相接触），Smilo 将会获得这个金子。

求出 Smilo 最多可以获得多少金子。

## 输入格式

多组数据。第一行一个整数 $t(1\le t\le 10^4)$ 表示数据组数。

对于每组数据，第一行三个整数 $n,m,k(1\le n,m,k\le 500)$。\
接下来 $n$ 行，每行一个由 `g`，`#` 和 `.` 构成的长度为 $m$ 的字符串，表示矿洞。`g` 表示金矿，`#` 表示石头，`.` 表示空格。

保证单个测试点中 $\sum nm\le 2.5\times 10^5$。

## 输出格式

对于每组数据，输出一行一个整数表示答案。

## 说明/提示

**样例解释**

对于第一组数据，Smilo 可以在任意空地中引爆炸药获得 $2$ 个金子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113C/31cdfd6d4d5bc2d30d1aa78bd3d2c6d2b0fc3eda.png)

对于第二组数据，Smilo 怎么做都不能获得任何金子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113C/a0691441b6e186314d109f809a1563824ebb170d.png)

对于第三组数据，Smilo 可以先在左下角的空地中引爆炸药获得 $2$ 个金子，再在左边一个格子引爆炸药获得 $2$ 个金子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113C/83af7f606c31f060510f0f11993f3494ca718e49.png)

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
3
2 3 1
#.#
g.g
2 3 2
#.#
g.g
3 4 2
.gg.
g..#
g##.
```

### 输出

```
2
0
4
```



---

---
title: "Kirei Attacks the Estate"
layout: "post"
diff: 普及/提高-
pid: CF2114E
tag: ['动态规划 DP', '贪心']
---

# Kirei Attacks the Estate

## 题目描述

Once, Kirei stealthily infiltrated the trap-filled estate of the Ainzbern family but was discovered by Kiritugu's familiar. Assessing his strength, Kirei decided to retreat. The estate is represented as a tree with $ n $ vertices, with the root at vertex $ 1 $ . Each vertex of the tree has a number $ a_i $ recorded, which represents the danger of vertex $ i $ . Recall that a tree is a connected undirected graph without cycles.

For a successful retreat, Kirei must compute the threat value for each vertex. The threat of a vertex is equal to the maximum alternating sum along the vertical path starting from that vertex. The alternating sum along the vertical path starting from vertex $ i $ is defined as $ a_i - a_{p_i} + a_{p_{p_i}} - \ldots $ , where $ p_i $ is the parent of vertex $ i $ on the path to the root (to vertex $ 1 $ ).

For example, in the tree below, vertex $ 4 $ has the following vertical paths:

- $ [4] $ with an alternating sum of $ a_4 = 6 $ ;
- $ [4, 3] $ with an alternating sum of $ a_4 - a_3 = 6 - 2 = 4 $ ;
- $ [4, 3, 2] $ with an alternating sum of $ a_4 - a_3 + a_2 = 6 - 2 + 5 = 9 $ ;
- $ [4, 3, 2, 1] $ with an alternating sum of $ a_4 - a_3 + a_2 - a_1 = 6 - 2 + 5 - 4 = 5 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2114E/041b3ada5bf12f77aa5a5a5b9431f1b90937ec72.png) The dangers of the vertices are indicated in red.Help Kirei compute the threat values for all vertices and escape the estate.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The following describes the test cases.

The first line contains an integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the dangers of the vertices.

The next $ n - 1 $ lines contain the numbers $ v, u $ ( $ 1 \le v, u \le n $ , $ v \neq u $ ) — the description of the edges of the tree.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ . It is also guaranteed that the given set of edges forms a tree.

## 输出格式

For each test case, output $ n $ integers — the threat of each vertex.

## 说明/提示

The tree from the first test case is depicted in the statement, and the maximum variable-sign sums are achieved as follows:

1. $ a_1 = 4 $ ;
2. $ a_2 = 5 $ ;
3. $ a_3 = 2 $ ;
4. $ a_4 - a_3 + a_2 = 6 - 2 + 5 = 9 $ ;
5. $ a_5 = 7 $ .

## 样例 #1

### 输入

```
2
5
4 5 2 6 7
1 2
3 2
4 3
5 1
6
1000000000 500500500 900900900 9 404 800800800
3 4
5 1
2 5
1 6
6 4
```

### 输出

```
4 5 2 9 7 
1000000000 1500500096 1701701691 199199209 404 800800800
```



---

---
title: "Lost Soul"
layout: "post"
diff: 普及/提高-
pid: CF2117E
tag: ['贪心']
---

# Lost Soul

## 题目描述

给定两个长度均为 $n$ 的数组 $a$ 和 $b$。

你可以进行任意次如下操作：

- 选择一个下标 $i$（$1 \le i \le n-1$），然后赋值 $a_i:=b_{i+1}$，或者 $b_i:=a_{i+1}$。

在进行这些操作之前，你可以选择一个下标 $i$（$1 \le i \le n$），然后将 $a_i$ 和 $b_i$ 从两个数组中删去。这个删除操作至多可以进行一次。

我们称两个长度为 $m$ 的数组 $c$ 和 $d$ 之间的匹配数量为满足 $c_j=d_j$ 的下标 $j$（$1 \le j \le m$）的数量。

你的任务是计算通过上述操作可以得到的 $a$ 和 $b$ 的最大匹配数量。

## 输入格式

输入数据包含多个测试用例。输入数据的第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的个数。

对于每个测试用例：

- 第一行包含一个整数 $n$（$2 \le n \le 2 \cdot 10^5$），表示数组 $a$ 和 $b$ 的长度。
- 第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le n$），表示 $a$ 中的元素。
- 第三行包含 $n$ 个整数 $b_1, b_2, \dots, b_n$（$1 \le b_i \le n$），表示 $b$ 中的元素。

输入数据保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一行一个整数，表示当前测试用例的答案。

## 说明/提示

对于第一个测试用例，我们可以进行如下操作：

- 不进行删除操作。
- 选择下标 $3$，然后赋值 $a_3:=b_4$。数组变为 $a=[1,3,2,4]$，$b=[4,3,2,2]$。
- 选择下标 $1$，然后赋值 $a_1:=b_2$。数组变为 $a=[3,3,2,4]$，$b=[4,3,2,2]$。
- 选择下标 $1$，然后赋值 $a_2:=b_1$。数组变为 $a=[3,3,2,4]$，$b=[3,3,2,2]$。

匹配数量为 $3$。可以证明这是我们可以得到匹配数量的最大值。

对于第二个测试用例，我们可以进行如下操作：

- 删去下标 $5$ 对应的元素。数组变为 $a=[2,1,5,3,4]$，$b=[3,2,4,5,6]$。
- 选择下标 $4$，然后赋值 $b_4:=a_5$。数组变为 $a=[2,1,5,3,4]$，$b=[3,2,4,4,6]$。
- 选择下标 $3$，然后赋值 $a_3:=b_4$。数组变为 $a=[2,1,4,3,4]$，$b=[3,2,4,4,6]$。
- 选择下标 $2$，然后赋值 $a_2:=b_3$。数组变为 $a=[2,4,4,3,4]$，$b=[3,2,4,4,6]$。
- 选择下标 $1$，然后赋值 $b_1:=a_2$。数组变为 $a=[2,4,4,3,4]$，$b=[4,2,4,4,6]$。
- 选择下标 $2$，然后赋值 $b_2:=a_3$。数组变为 $a=[2,4,4,3,4]$，$b=[4,4,4,4,6]$。
- 选择下标 $1$，然后赋值 $a_1:=b_2$。数组变为 $a=[4,4,4,3,4]$，$b=[4,4,4,4,6]$。

对于第三个测试用例，可以证明我们无法得到任何匹配，因此答案为 $0$。

## 样例 #1

### 输入

```
10
4
1 3 1 4
4 3 2 2
6
2 1 5 3 6 4
3 2 4 5 1 6
2
1 2
2 1
6
2 5 1 3 6 4
3 5 2 3 4 6
4
1 3 2 2
2 1 3 4
8
3 1 4 6 2 2 5 7
4 2 3 7 1 1 6 5
10
5 1 2 7 3 9 4 10 6 8
6 2 3 6 4 10 5 1 7 9
5
3 2 4 1 5
2 4 5 1 3
7
2 2 6 4 1 3 5
3 1 6 5 1 4 2
5
4 1 3 2 5
3 2 1 5 4
```

### 输出

```
3
3
0
4
3
5
6
4
5
2
```



---

---
title: "Make It Beautiful"
layout: "post"
diff: 普及/提高-
pid: CF2118C
tag: ['数学', '贪心']
---

# Make It Beautiful

## 题目描述

给定一个包含 $ n $ 个整数的数组 $ a $。我们定义一个数字 $ x $ 的**美丽值**为其二进制表示中 $ 1 $ 的个数。我们定义一个数组的美丽值为其所有数字美丽值的总和。

在一次操作中，你可以选择一个下标 $ i $（$ 1 \le i \le n $）并将 $ a_i $ 增加 $ 1 $。

在最多进行 $ k $ 次操作后，求数组可能达到的最大美丽值。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $ t $（$ 1 \le t \le 5000 $）。接下来是每个测试用例的描述。

每个测试用例的第一行包含两个整数 $ n $ 和 $ k $（$ 1 \le n \le 5000 $，$ 0 \le k \le 10^{18} $）——数组的长度和最大操作次数。

每个测试用例的第二行包含 $ n $ 个整数 $ a_1, a_2, \ldots, a_n $（$ 0 \le a_i \le 10^9 $）——表示数组 $ a $。

保证所有测试用例的 $ n $ 之和不超过 $ 5000 $。

## 输出格式

对于每个测试用例，输出一个整数，表示最多进行 $ k $ 次操作后数组的最大美丽值。

## 说明/提示

在第一个测试用例中，$ a = [0, 1, 7, 2, 4] $。

- 第一次操作选择 $ i = 1 $，新数组为 $ a = [1, 1, 7, 2, 4] $。
- 第二次操作选择 $ i = 4 $，新数组为 $ a = [1, 1, 7, 3, 4] $。

该数组的美丽值为 $ 1 + 1 + 3 + 2 + 1 = 8 $。另一个具有相同美丽值的有效解是 $ [0, 1, 7, 3, 5] $。在第三个测试用例中，$ a = [3] $。由于不要求必须使用恰好 $ k $ 次操作，最优解是不进行任何操作。

## 样例 #1

### 输入

```
5
5 2
0 1 7 2 4
5 3
0 1 7 2 4
1 1
3
3 0
2 0 3
1 100000000000
0
```

### 输出

```
8
9
2
3
36
```



---

---
title: "System Administrator"
layout: "post"
diff: 普及/提高-
pid: CF22C
tag: ['贪心', '连通块', '构造']
---

# System Administrator

## 题目描述

给定 $n$ 个顶点，可以在这些顶点之间连接 $m$ 条双向边，要求连接后整个图联通，并且去掉 $v$ 点后整个图不连通。

若有解，输出所连得的 $m$ 条边，随意输出一种方案即可；若无解，输出 ```-1```。

## 输入格式

一行三个整数表示 $n,m,v$。

## 输出格式

共 $m$ 行，每行两个整数 $u_i$ 和 $v_i$，表示 $u_i$ 向 $v_i$ 连一条边。

## 说明/提示

- $n, m \le {10}^5$

Translated by 稀神探女

## 样例 #1

### 输入

```
5 6 3

```

### 输出

```
1 2
2 3
3 4
4 5
1 3
3 5

```

## 样例 #2

### 输入

```
6 100 1

```

### 输出

```
-1

```



---

---
title: "Find Maximum"
layout: "post"
diff: 普及/提高-
pid: CF353C
tag: ['动态规划 DP', '贪心']
---

# Find Maximum

## 题目描述

Valera 有一个 $n$ 个数的 **非负整数** 数组 $a$ ，其元素分别为 $a_0,a_1,\cdots,a_{n-1}$。同时有一个函数 $f(x)=\sum_{i=0}^{n-1}a_i\cdot bit(i)$，$bit(i)$ 指的是数字 $x$ 在二进制中第 $i$ 位的值是否为 1。

举个例子，当 $n=4,x=11(11=2^0+2^1+2^3)$ 时，$f(x)=a_0+a_1+a_3$。

对于所有 $0\le x \le m$ 的整数 $x$ ，请求出 $f(x)$ 的最大值。

## 输入格式

第一行，输入 $n$ 。

接下来一行，输入数组 $a$ 。

最后一行输入一个由 $n$ 个数组成的数字序列 $s$ ，$s$ 即为 $m$ 的二进制翻转后的数字序列。（ 也就是 $m=\sum_{i=0}^{n-1}2^i\cdot s_i$ ）数字与数字之间没有空格。

## 输出格式

一行一个整数，表示 $f(x)$ 的最大值。

## 说明/提示

- $1 \le n \le 10^5$

- $0 \le a_i \le 10^4$

- $0\le s_i \le 1$

## 样例 #1

### 输入

```
2
3 8
10

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5
17 0 10 2 1
11010

```

### 输出

```
27

```



---

---
title: "Milking cows"
layout: "post"
diff: 普及/提高-
pid: CF383A
tag: ['贪心', '前缀和', '概率论']
---

# Milking cows

## 题目描述

Iahub在农场帮助他的祖父，今天他必须挤牛奶。农场里有$n$只牛左成一排，从左到右编号$1$到$n$。每只牛不是面向左边就是面向右边。当Iahub挤某一只牛的牛奶时，所有看得到这当前只牛的牛都会因为受到惊吓而损失一单位量的牛奶。面向左边的牛可以看到它左边的所有牛（不包括自己），面向右边的牛可以看到它右边的所有牛（不包括自己）。被惊吓过的牛可以再次被惊吓。被挤过奶的牛不会再被惊吓。我们假定每一头牛可以生产无限量的牛奶。

Iahub可以决定挤牛奶的顺序，但他必须每头牛都要挤。Iahub想损失尽可能少的牛奶。请输出最少的牛奶损失量。

## 输入格式

第一行包括一个整数$n(1<=n<=200000)$. 第二行包括n个整数$a_1,a_2...,a_n$。$a_i$是$0$表示牛面向左边，$1$则表示面向右边。

## 输出格式

输出一个整数，即最少的牛奶损失量

在C++中，请不要用%lld分类符来读入或输出64位整型。最好用输出输出流或者%I64D分类符

## 说明/提示

在第一个样例中,Iahub按照下面的顺序可以使得牛奶损失最少：$3,4,2,1$。当他挤牛$3$时，牛$4$会损失$1$单位牛奶。在此之后，没有牛奶损失。

Translated by @Imakf

## 样例 #1

### 输入

```
4
0 0 1 0

```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 0 1 0 1

```

### 输出

```
3
```



---

---
title: "Cards"
layout: "post"
diff: 普及/提高-
pid: CF398A
tag: ['数学', '贪心', '枚举']
---

# Cards

## 题目描述

User ainta loves to play with cards. He has $ a $ cards containing letter "o" and $ b $ cards containing letter "x". He arranges the cards in a row, and calculates the score of the deck by the formula below.

1. At first, the score is $ 0 $ .
2. For each block of contiguous "o"s with length $ x $ the score increases by $ x^{2} $ .
3. For each block of contiguous "x"s with length $ y $ the score decreases by $ y^{2} $ .

For example, if $ a=6,b=3 $ and ainta have arranged the cards in the order, that is described by string "ooxoooxxo", the score of the deck equals $ 2^{2}-1^{2}+3^{2}-2^{2}+1^{2}=9 $ . That is because the deck has 5 blocks in total: "oo", "x", "ooo", "xx", "o".

User ainta likes big numbers, so he wants to maximize the score with the given cards. Help ainta make the score as big as possible. Note, that he has to arrange all his cards.

## 输入格式

The first line contains two space-separated integers $ a $ and $ b $ ( $ 0<=a,b<=10^{5}; a+b>=1 $ ) — the number of "o" cards and the number of "x" cards.

## 输出格式

In the first line print a single integer $ v $ — the maximum score that ainta can obtain.

In the second line print $ a+b $ characters describing the deck. If the $ k $ -th card of the deck contains "o", the $ k $ -th character must be "o". If the $ k $ -th card of the deck contains "x", the $ k $ -th character must be "x". The number of "o" characters must be equal to $ a $ , and the number of "x " characters must be equal to $ b $ . If there are many ways to maximize $ v $ , print any.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
2 3

```

### 输出

```
-1
xoxox

```

## 样例 #2

### 输入

```
4 0

```

### 输出

```
16
oooo
```

## 样例 #3

### 输入

```
0 4

```

### 输出

```
-16
xxxx
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
title: "Sereja and Swaps"
layout: "post"
diff: 普及/提高-
pid: CF425A
tag: ['贪心', '枚举']
---

# Sereja and Swaps

## 题目描述

As usual, Sereja has array $ a $ , its elements are integers: $ a[1],a[2],...,a[n] $ . Let's introduce notation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF425A/32568eeb8040eb1aa136af55c788f7e656cb44a9.png)A swap operation is the following sequence of actions:

- choose two indexes $ i,j $ $ (i≠j) $ ;
- perform assignments $ tmp=a[i],a[i]=a[j],a[j]=tmp $ .

What maximum value of function $ m(a) $ can Sereja get if he is allowed to perform at most $ k $ swap operations?

## 输入格式

The first line contains two integers $ n $ and $ k $ $ (1<=n<=200; 1<=k<=10) $ . The next line contains $ n $ integers $ a[1] $ , $ a[2] $ , $ ... $ , $ a[n] $ $ (-1000<=a[i]<=1000) $ .

## 输出格式

In a single line print the maximum value of $ m(a) $ that Sereja can get if he is allowed to perform at most $ k $ swap operations.

## 样例 #1

### 输入

```
10 2
10 -1 2 2 2 2 2 2 -1 10

```

### 输出

```
32

```

## 样例 #2

### 输入

```
5 10
-1 -1 -1 -1 -1

```

### 输出

```
-1

```



---

---
title: "New Year Book Reading"
layout: "post"
diff: 普及/提高-
pid: CF500C
tag: ['模拟', '贪心', '构造']
---

# New Year Book Reading

## 题目描述

小明非常喜欢读书。他一共有 $n$ 本书，编号为 $1\sim n$，第 $i$本书重 $w_i$。

小明计划在暑假的 $m$ 天里每天读一本书，第 $i$ 天读第 $d_i$ 本书，可能会重复读到同一本书。

因为所有的书都是堆成一摞的，所以每次读某本书之前小明都需要先将这本书上面所有的书搬开，拿出这本书，再将搬开的书按原顺序放回去，消耗体力为搬开书的重量之和，读完这本书后将其放在这摞书的最上面。

小明想知道这 $n$ 本书以怎样的初始顺序放置，所搬书消耗总体力最小。

## 输入格式

第一行两个正整数 $n,m$，表示小明一共有 $n$ 本书，要读 $m$ 天。

第二行 $n$ 个正整数，第 $i$ 个数表示表示第 $i$本书的重量为 $w_i$。

第三行 $m$ 个正整数，第 $i$ 个数表示第 $i$ 天要读第 $d_i$ 本书。

## 输出格式

一行一个数，表示读完 $m$ 次书所搬书消耗的最小体力值。

## 样例 #1

### 输入

```
3 5
1 2 3
1 3 2 3 1

```

### 输出

```
12

```



---

---
title: "Woodcutters"
layout: "post"
diff: 普及/提高-
pid: CF545C
tag: ['动态规划 DP', '贪心']
---

# Woodcutters

## 题目描述

Little Susie listens to fairy tales before bed every day. Today's fairy tale was about wood cutters and the little girl immediately started imagining the choppers cutting wood. She imagined the situation that is described below.

There are $ n $ trees located along the road at points with coordinates $ x_{1},x_{2},...,x_{n} $ . Each tree has its height $ h_{i} $ . Woodcutters can cut down a tree and fell it to the left or to the right. After that it occupies one of the segments $ [x_{i}-h_{i},x_{i}] $ or $ [x_{i};x_{i}+h_{i}] $ . The tree that is not cut down occupies a single point with coordinate $ x_{i} $ . Woodcutters can fell a tree if the segment to be occupied by the fallen tree doesn't contain any occupied point. The woodcutters want to process as many trees as possible, so Susie wonders, what is the maximum number of trees to fell.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of trees.

Next $ n $ lines contain pairs of integers $ x_{i},h_{i} $ ( $ 1<=x_{i},h_{i}<=10^{9} $ ) — the coordinate and the height of the $ і $ -th tree.

The pairs are given in the order of ascending $ x_{i} $ . No two trees are located at the point with the same coordinate.

## 输出格式

Print a single number — the maximum number of trees that you can cut down by the given rules.

## 说明/提示

In the first sample you can fell the trees like that:

- fell the $ 1 $ -st tree to the left — now it occupies segment $ [-1;1] $
- fell the $ 2 $ -nd tree to the right — now it occupies segment $ [2;3] $
- leave the $ 3 $ -rd tree — it occupies point $ 5 $
- leave the $ 4 $ -th tree — it occupies point $ 10 $
- fell the $ 5 $ -th tree to the right — now it occupies segment $ [19;20] $

In the second sample you can also fell $ 4 $ -th tree to the right, after that it will occupy segment $ [10;19] $ .

## 样例 #1

### 输入

```
5
1 2
2 1
5 10
10 9
19 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5
1 2
2 1
5 10
10 9
20 1

```

### 输出

```
4

```



---

---
title: "Efim and Strange Grade"
layout: "post"
diff: 普及/提高-
pid: CF718A
tag: ['贪心']
---

# Efim and Strange Grade

## 题目描述

Efim just received his grade for the last test. He studies in a special school and his grade can be equal to any positive decimal fraction. First he got disappointed, as he expected a way more pleasant result. Then, he developed a tricky plan. Each second, he can ask his teacher to round the grade at any place after the decimal point (also, he can ask to round to the nearest integer).

There are $ t $ seconds left till the end of the break, so Efim has to act fast. Help him find what is the maximum grade he can get in no more than $ t $ seconds. Note, that he can choose to not use all $ t $ seconds. Moreover, he can even choose to not round the grade at all.

In this problem, classic rounding rules are used: while rounding number to the $ n $ -th digit one has to take a look at the digit $ n+1 $ . If it is less than $ 5 $ than the $ n $ -th digit remain unchanged while all subsequent digits are replaced with $ 0 $ . Otherwise, if the $ n+1 $ digit is greater or equal to $ 5 $ , the digit at the position $ n $ is increased by $ 1 $ (this might also change some other digits, if this one was equal to $ 9 $ ) and all subsequent digits are replaced with $ 0 $ . At the end, all trailing zeroes are thrown away.

For example, if the number $ 1.14 $ is rounded to the first decimal place, the result is $ 1.1 $ , while if we round $ 1.5 $ to the nearest integer, the result is $ 2 $ . Rounding number $ 1.299996121 $ in the fifth decimal place will result in number $ 1.3 $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ t $ ( $ 1<=n<=200000 $ , $ 1<=t<=10^{9} $ ) — the length of Efim's grade and the number of seconds till the end of the break respectively.

The second line contains the grade itself. It's guaranteed that the grade is a positive number, containing at least one digit after the decimal points, and it's representation doesn't finish with $ 0 $ .

## 输出格式

Print the maximum grade that Efim can get in $ t $ seconds. Do not print trailing zeroes.

## 说明/提示

In the first two samples Efim initially has grade $ 10.245 $ .

During the first second Efim can obtain grade $ 10.25 $ , and then $ 10.3 $ during the next second. Note, that the answer $ 10.30 $ will be considered incorrect.

In the third sample the optimal strategy is to not perform any rounding at all.

## 样例 #1

### 输入

```
6 1
10.245

```

### 输出

```
10.25

```

## 样例 #2

### 输入

```
6 2
10.245

```

### 输出

```
10.3

```

## 样例 #3

### 输入

```
3 100
9.2

```

### 输出

```
9.2

```



---

---
title: "Tennis Championship"
layout: "post"
diff: 普及/提高-
pid: CF735C
tag: ['贪心', '递推']
---

# Tennis Championship

## 题目描述

Famous Brazil city Rio de Janeiro holds a tennis tournament and Ostap Bender doesn't want to miss this event. There will be $ n $ players participating, and the tournament will follow knockout rules from the very first game. That means, that if someone loses a game he leaves the tournament immediately.

Organizers are still arranging tournament grid (i.e. the order games will happen and who is going to play with whom) but they have already fixed one rule: two players can play against each other only if the number of games one of them has already played differs by no more than one from the number of games the other one has already played. Of course, both players had to win all their games in order to continue participating in the tournament.

Tournament hasn't started yet so the audience is a bit bored. Ostap decided to find out what is the maximum number of games the winner of the tournament can take part in (assuming the rule above is used). However, it is unlikely he can deal with this problem without your help.

## 输入格式

The only line of the input contains a single integer $ n $ ( $ 2<=n<=10^{18} $ ) — the number of players to participate in the tournament.

## 输出格式

Print the maximum number of games in which the winner of the tournament can take part.

## 说明/提示

In all samples we consider that player number $ 1 $ is the winner.

In the first sample, there would be only one game so the answer is $ 1 $ .

In the second sample, player $ 1 $ can consequently beat players $ 2 $ and $ 3 $ .

In the third sample, player $ 1 $ can't play with each other player as after he plays with players $ 2 $ and $ 3 $ he can't play against player $ 4 $ , as he has $ 0 $ games played, while player $ 1 $ already played $ 2 $ . Thus, the answer is $ 2 $ and to achieve we make pairs $ (1,2) $ and $ (3,4) $ and then clash the winners.

## 样例 #1

### 输入

```
2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3

```

### 输出

```
2

```

## 样例 #3

### 输入

```
4

```

### 输出

```
2

```

## 样例 #4

### 输入

```
10

```

### 输出

```
4

```



---

---
title: "Maximal Binary Matrix"
layout: "post"
diff: 普及/提高-
pid: CF803A
tag: ['贪心', '递归']
---

# Maximal Binary Matrix

## 题目描述

You are given matrix with $ n $ rows and $ n $ columns filled with zeroes. You should put $ k $ ones in it in such a way that the resulting matrix is symmetrical with respect to the main diagonal (the diagonal that goes from the top left to the bottom right corner) and is lexicographically maximal.

One matrix is lexicographically greater than the other if the first different number in the first different row from the top in the first matrix is greater than the corresponding number in the second one.

If there exists no such matrix then output -1.

## 输入格式

The first line consists of two numbers $ n $ and $ k $ ( $ 1<=n<=100 $ , $ 0<=k<=10^{6} $ ).

## 输出格式

If the answer exists then output resulting matrix. Otherwise output -1.

## 样例 #1

### 输入

```
2 1

```

### 输出

```
1 0 
0 0 

```

## 样例 #2

### 输入

```
3 2

```

### 输出

```
1 0 0 
0 1 0 
0 0 0 

```

## 样例 #3

### 输入

```
2 5

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
title: "Party Lemonade"
layout: "post"
diff: 普及/提高-
pid: CF913C
tag: ['贪心', '递归', '进制']
---

# Party Lemonade

## 题目描述

题意

没有柠檬水的新年派对不是新年派对。像往常一样，你期待着客人，而柠檬水已经成为一种令人愉快的必需品。
你最喜欢的商店卖 n 种不同价格的装在不同瓶子里的柠檬水。一瓶第 i 种柠檬水，体积为2^{i-1}，价格为c_{i}卢布。商店里的每种柠檬水可以被认为有无限瓶。
你想要买至少 L 升的柠檬水，你需要花费多少卢布？

## 输入格式

第一行包含两个整数 n 和 L（1<=n<=30;1<=L<=10^{9}）。
第二行包含 n 个整数c_{1},c_{2},...,c_{n}（1<=c_{i}<=10^{9}）。

## 输出格式

输出一个正整数---买至少 L 升的柠檬水，你需要支付的最少卢布。



Translated by Fowany

## 样例 #1

### 输入

```
4 12
20 30 70 90

```

### 输出

```
150

```

## 样例 #2

### 输入

```
4 3
10000 1000 100 10

```

### 输出

```
10

```

## 样例 #3

### 输入

```
4 3
10 100 1000 10000

```

### 输出

```
30

```

## 样例 #4

### 输入

```
5 787787787
123456789 234567890 345678901 456789012 987654321

```

### 输出

```
44981600785557577

```



---

---
title: "Our Tanya is Crying Out Loud"
layout: "post"
diff: 普及/提高-
pid: CF940B
tag: ['模拟', '贪心', '枚举']
---

# Our Tanya is Crying Out Loud

## 题目描述

Right now she actually isn't. But she will be, if you don't solve this problem.

You are given integers $ n $ , $ k $ , $ A $ and $ B $ . There is a number $ x $ , which is initially equal to $ n $ . You are allowed to perform two types of operations:

1. Subtract 1 from $ x $ . This operation costs you $ A $ coins.
2. Divide $ x $ by $ k $ . Can be performed only if $ x $ is divisible by $ k $ . This operation costs you $ B $ coins.

 What is the minimum amount of coins you have to pay to make $ x $ equal to $ 1 $ ?

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=2·10^{9} $ ).

The second line contains a single integer $ k $ ( $ 1<=k<=2·10^{9} $ ).

The third line contains a single integer $ A $ ( $ 1<=A<=2·10^{9} $ ).

The fourth line contains a single integer $ B $ ( $ 1<=B<=2·10^{9} $ ).

## 输出格式

Output a single integer — the minimum amount of coins you have to pay to make $ x $ equal to $ 1 $ .

## 说明/提示

In the first testcase, the optimal strategy is as follows:

- Subtract 1 from $ x $ ( $ 9→8 $ ) paying 3 coins.
- Divide $ x $ by 2 ( $ 8→4 $ ) paying 1 coin.
- Divide $ x $ by 2 ( $ 4→2 $ ) paying 1 coin.
- Divide $ x $ by 2 ( $ 2→1 $ ) paying 1 coin.

The total cost is $ 6 $ coins.

In the second test case the optimal strategy is to subtract 1 from $ x $ $ 4 $ times paying $ 8 $ coins in total.

## 样例 #1

### 输入

```
9
2
3
1

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5
5
2
20

```

### 输出

```
8

```

## 样例 #3

### 输入

```
19
3
4
2

```

### 输出

```
12

```



---

---
title: "Minimize the error"
layout: "post"
diff: 普及/提高-
pid: CF960B
tag: ['模拟', '贪心']
---

# Minimize the error

## 题目描述

You are given two arrays $ A $ and $ B $ , each of size $ n $ . The error, $ E $ , between these two arrays is defined ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960B/e950d33ee993b9f2e2ad61182c68b371192cc68e.png). You have to perform exactly $ k_{1} $ operations on array $ A $ and exactly $ k_{2} $ operations on array $ B $ . In one operation, you have to choose one element of the array and increase or decrease it by $ 1 $ .

Output the minimum possible value of error after $ k_{1} $ operations on array $ A $ and $ k_{2} $ operations on array $ B $ have been performed.

## 输入格式

The first line contains three space-separated integers $ n $ ( $ 1<=n<=10^{3} $ ), $ k_{1} $ and $ k_{2} $ ( $ 0<=k_{1}+k_{2}<=10^{3} $ , $ k_{1} $ and $ k_{2} $ are non-negative) — size of arrays and number of operations to perform on $ A $ and $ B $ respectively.

Second line contains $ n $ space separated integers $ a_{1},a_{2},...,a_{n} $ ( $ -10^{6}<=a_{i}<=10^{6} $ ) — array $ A $ .

Third line contains $ n $ space separated integers $ b_{1},b_{2},...,b_{n} $ ( $ -10^{6}<=b_{i}<=10^{6} $ )— array $ B $ .

## 输出格式

Output a single integer — the minimum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960B/52c5522faff1ae1553e7476d3c27b93932998da8.png) after doing exactly $ k_{1} $ operations on array $ A $ and exactly $ k_{2} $ operations on array $ B $ .

## 说明/提示

In the first sample case, we cannot perform any operations on $ A $ or $ B $ . Therefore the minimum possible error $ E=(1-2)^{2}+(2-3)^{2}=2 $ .

In the second sample case, we are required to perform exactly one operation on $ A $ . In order to minimize error, we increment the first element of $ A $ by $ 1 $ . Now, $ A=[2,2] $ . The error is now $ E=(2-2)^{2}+(2-2)^{2}=0 $ . This is the minimum possible error obtainable.

In the third sample case, we can increase the first element of $ A $ to $ 8 $ , using the all of the $ 5 $ moves available to us. Also, the first element of $ B $ can be reduced to $ 8 $ using the $ 6 $ of the $ 7 $ available moves. Now $ A=[8,4] $ and $ B=[8,4] $ . The error is now $ E=(8-8)^{2}+(4-4)^{2}=0 $ , but we are still left with $ 1 $ move for array $ B $ . Increasing the second element of $ B $ to $ 5 $ using the left move, we get $ B=[8,5] $ and $ E=(8-8)^{2}+(4-5)^{2}=1 $ .

## 样例 #1

### 输入

```
2 0 0
1 2
2 3

```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 1 0
1 2
2 2

```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 5 7
3 4
14 4

```

### 输出

```
1
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

---
title: "Liebig's Barrels"
layout: "post"
diff: 普及/提高-
pid: CF985C
tag: ['贪心']
---

# Liebig's Barrels

## 题目描述

你有一共m=n*k个木板。第i个木板的长度为ai。你必须用其中的每k条木板组成n个木桶。每条木板只能且必须属于一个木桶。我们把第j个木桶的最短的木板长度作为这个木桶的容积vj

你想要让这组合起来的n个木桶总容积最大。但是你需要让他们的容积尽量差不多，使得无论那两个木桶的容积差不超过l，即|vx-vy|<=l(1<=vx,vy<=n)。

输出这n个尽量相等的木桶的最大容积。如果无法组成满足要求的n个木桶，输出“0”

## 输入格式

第一行包括三个分开的整数n,k,l(1<=n,k<=10^5, 1<=n·k<=10^5, 0<=l<=10^9)

第二行包括m=n*k个整数，表示木板长度a1,a2,...,am ( 1<=ai<=10^9)

## 输出格式

输出一个整数，即n个满足要求的木桶的容积最大值

感谢@hicc0305 提供的翻译

## 样例 #1

### 输入

```
4 2 1
2 2 1 2 3 2 2 3

```

### 输出

```
7

```

## 样例 #2

### 输入

```
2 1 0
10 10

```

### 输出

```
20

```

## 样例 #3

### 输入

```
1 2 1
5 2

```

### 输出

```
2

```

## 样例 #4

### 输入

```
3 2 1
1 2 3 4 5 6

```

### 输出

```
0

```



---

---
title: "Petr and Permutations"
layout: "post"
diff: 普及/提高-
pid: CF986B
tag: ['模拟', '贪心', '树状数组']
---

# Petr and Permutations

## 题目描述

Petr likes to come up with problems about randomly generated data. This time problem is about random permutation. He decided to generate a random permutation this way: he takes identity permutation of numbers from $ 1 $ to $ n $ and then $ 3n $ times takes a random pair of different elements and swaps them. Alex envies Petr and tries to imitate him in all kind of things. Alex has also come up with a problem about random permutation. He generates a random permutation just like Petr but swaps elements $ 7n+1 $ times instead of $ 3n $ times. Because it is more random, OK?!

You somehow get a test from one of these problems and now you want to know from which one.

## 输入格式

In the first line of input there is one integer $ n $ ( $ 10^{3} \le n \le 10^{6} $ ).

In the second line there are $ n $ distinct integers between $ 1 $ and $ n $ — the permutation of size $ n $ from the test.

It is guaranteed that all tests except for sample are generated this way: First we choose $ n $ — the size of the permutation. Then we randomly choose a method to generate a permutation — the one of Petr or the one of Alex. Then we generate a permutation using chosen method.

## 输出格式

If the test is generated via Petr's method print "Petr" (without quotes). If the test is generated via Alex's method print "Um\_nik" (without quotes).

## 说明/提示

Please note that the sample is not a valid test (because of limitations for $ n $ ) and is given only to illustrate input/output format. Your program still has to print correct answer to this test to get AC.

Due to randomness of input hacks in this problem are forbidden.

## 样例 #1

### 输入

```
5
2 4 5 1 3

```

### 输出

```
Petr

```



---

---
title: "Bishwock"
layout: "post"
diff: 普及/提高-
pid: CF991D
tag: ['模拟', '贪心']
---

# Bishwock

## 题目描述

Bishwock is a chess figure that consists of three squares resembling an "L-bar". This figure can be rotated by 90, 180 and 270 degrees so it can have four possible states:

```
XX   XX   .X   X.
X.   .X   XX   XX
```

Bishwocks don't attack any squares and can even occupy on the adjacent squares as long as they don't occupy the same square.

Vasya has a board with $ 2\times n $ squares onto which he wants to put some bishwocks. To his dismay, several squares on this board are already occupied by pawns and Vasya can't put bishwocks there. However, pawns also don't attack bishwocks and they can occupy adjacent squares peacefully.

Knowing the positions of pawns on the board, help Vasya to determine the maximum amount of bishwocks he can put onto the board so that they wouldn't occupy the same squares and wouldn't occupy squares with pawns.

## 输入格式

The input contains two nonempty strings that describe Vasya's board. Those strings contain only symbols "0" (zero) that denote the empty squares and symbols "X" (uppercase English letter) that denote the squares occupied by pawns. Strings are nonempty and are of the same length that does not exceed $ 100 $ .

## 输出格式

Output a single integer — the maximum amount of bishwocks that can be placed onto the given board.

## 样例 #1

### 输入

```
00
00

```

### 输出

```
1
```

## 样例 #2

### 输入

```
00X00X0XXX0
0XXX0X00X00

```

### 输出

```
4
```

## 样例 #3

### 输入

```
0X0X0
0X0X0

```

### 输出

```
0
```

## 样例 #4

### 输入

```
0XXX0
00000

```

### 输出

```
2
```



---

---
title: "Suit and Tie"
layout: "post"
diff: 普及/提高-
pid: CF995B
tag: ['贪心']
---

# Suit and Tie

## 题目描述

Allen is hosting a formal dinner party. $ 2n $ people come to the event in $ n $ pairs (couples). After a night of fun, Allen wants to line everyone up for a final picture. The $ 2n $ people line up, but Allen doesn't like the ordering. Allen prefers if each pair occupies adjacent positions in the line, as this makes the picture more aesthetic.

Help Allen find the minimum number of swaps of adjacent positions he must perform to make it so that each couple occupies adjacent positions in the line.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 100 $ ), the number of pairs of people.

The second line contains $ 2n $ integers $ a_1, a_2, \dots, a_{2n} $ . For each $ i $ with $ 1 \le i \le n $ , $ i $ appears exactly twice. If $ a_j = a_k = i $ , that means that the $ j $ -th and $ k $ -th people in the line form a couple.

## 输出格式

Output a single integer, representing the minimum number of adjacent swaps needed to line the people up so that each pair occupies adjacent positions.

## 说明/提示

In the first sample case, we can transform $ 1 1 2 3 3 2 4 4 \rightarrow 1 1 2 3 2 3 4 4 \rightarrow 1 1 2 2 3 3 4 4 $ in two steps. Note that the sequence $ 1 1 2 3 3 2 4 4 \rightarrow 1 1 3 2 3 2 4 4 \rightarrow 1 1 3 3 2 2 4 4 $ also works in the same number of steps.

The second sample case already satisfies the constraints; therefore we need $ 0 $ swaps.

## 样例 #1

### 输入

```
4
1 1 2 3 3 2 4 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
1 1 2 2 3 3

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3
3 1 2 3 1 2

```

### 输出

```
3

```



---

