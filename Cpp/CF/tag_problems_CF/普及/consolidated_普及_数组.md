---
title: "Cinema Cashier"
layout: "post"
diff: 普及/提高-
pid: CF10B
tag: ['模拟', '树状数组', '队列']
---

# Cinema Cashier

## 题目描述

All cinema halls in Berland are rectangles with $ K $ rows of $ K $ seats each, and $ K $ is an odd number. Rows and seats are numbered from $ 1 $ to $ K $ . For safety reasons people, who come to the box office to buy tickets, are not allowed to choose seats themselves. Formerly the choice was made by a cashier, but now this is the responsibility of a special seating program. It was found out that the large majority of Berland's inhabitants go to the cinema in order to watch a movie, that's why they want to sit as close to the hall center as possible. Moreover, a company of $ M $ people, who come to watch a movie, want necessarily to occupy $ M $ successive seats in one row. Let's formulate the algorithm, according to which the program chooses seats and sells tickets. As the request for $ M $ seats comes, the program should determine the row number $ x $ and the segment $ [y_{l},y_{r}] $ of the seats numbers in this row, where $ y_{r}-y_{l}+1=M $ . From all such possible variants as a final result the program should choose the one with the minimum function value of total seats remoteness from the center. Say, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF10B/c9748a84837b67ee9aa2cbea2b55fdd9ec523940.png) — the row and the seat numbers of the most "central" seat. Then the function value of seats remoteness from the hall center is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF10B/9bc644baca5d1a575e01b85fce16d96f8e180ca4.png). If the amount of minimum function values is more than one, the program should choose the one that is closer to the screen (i.e. the row number $ x $ is lower). If the variants are still multiple, it should choose the one with the minimum $ y_{l} $ . If you did not get yet, your task is to simulate the work of this program.


## 输入格式

The first line contains two integers $ N $ and $ K $ ( $ 1<=N<=1000,1<=K<=99 $ ) — the amount of requests and the hall size respectively. The second line contains $ N $ space-separated integers $ M_{i} $ from the range $ [1,K] $ — requests to the program.

## 输出格式

Output $ N $ lines. In the $ i $ -th line output «-1» (without quotes), if it is impossible to find $ M_{i} $ successive seats in one row, otherwise output three numbers $ x,y_{l},y_{r} $ . Separate the numbers with a space.

## 样例 #1

### 输入

```
2 1
1 1

```

### 输出

```
1 1 1
-1

```

## 样例 #2

### 输入

```
4 3
1 2 3 1

```

### 输出

```
2 2 2
1 1 2
3 1 3
2 1 1

```



---

---
title: "Maximum Crossings (Hard Version)"
layout: "post"
diff: 普及/提高-
pid: CF1676H2
tag: ['树状数组']
---

# Maximum Crossings (Hard Version)

## 题目描述

The only difference between the two versions is that in this version $ n \leq 2 \cdot 10^5 $ and the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

A terminal is a row of $ n $ equal segments numbered $ 1 $ to $ n $ in order. There are two terminals, one above the other.

You are given an array $ a $ of length $ n $ . For all $ i = 1, 2, \dots, n $ , there should be a straight wire from some point on segment $ i $ of the top terminal to some point on segment $ a_i $ of the bottom terminal. For example, the following pictures show two possible wirings if $ n=7 $ and $ a=[4,1,4,6,7,7,5] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676H2/71a1fe41f3cad0f3cbda88716457eefb4e46b4ca.png)A crossing occurs when two wires share a point in common. In the picture above, crossings are circled in red.

What is the maximum number of crossings there can be if you place the wires optimally?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq n $ ) — the elements of the array.

The sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum number of crossings there can be if you place the wires optimally.

## 说明/提示

The first test case is shown in the second picture in the statement.

In the second test case, the only wiring possible has the two wires cross, so the answer is $ 1 $ .

In the third test case, the only wiring possible has one wire, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
4
7
4 1 4 6 7 7 5
2
2 1
1
1
3
2 2 2
```

### 输出

```
6
1
0
3
```



---

---
title: "Tokitsukaze and Strange Inequality"
layout: "post"
diff: 普及/提高-
pid: CF1677A
tag: ['树状数组']
---

# Tokitsukaze and Strange Inequality

## 题目描述

Tokitsukaze has a permutation $ p $ of length $ n $ . Recall that a permutation $ p $ of length $ n $ is a sequence $ p_1, p_2, \ldots, p_n $ consisting of $ n $ distinct integers, each of which from $ 1 $ to $ n $ ( $ 1 \leq p_i \leq n $ ).

She wants to know how many different indices tuples $ [a,b,c,d] $ ( $ 1 \leq a < b < c < d \leq n $ ) in this permutation satisfy the following two inequalities:

 $ p_a < p_c $ and $ p_b > p_d $ . Note that two tuples $ [a_1,b_1,c_1,d_1] $ and $ [a_2,b_2,c_2,d_2] $ are considered to be different if $ a_1 \ne a_2 $ or $ b_1 \ne b_2 $ or $ c_1 \ne c_2 $ or $ d_1 \ne d_2 $ .

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases. Each test case consists of two lines.

The first line contains a single integer $ n $ ( $ 4 \leq n \leq 5000 $ ) — the length of permutation $ p $ .

The second line contains $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \leq p_i \leq n $ ) — the permutation $ p $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5000 $ .

## 输出格式

For each test case, print a single integer — the number of different $ [a,b,c,d] $ tuples.

## 说明/提示

In the first test case, there are $ 3 $ different $ [a,b,c,d] $ tuples.

 $ p_1 = 5 $ , $ p_2 = 3 $ , $ p_3 = 6 $ , $ p_4 = 1 $ , where $ p_1 < p_3 $ and $ p_2 > p_4 $ satisfies the inequality, so one of $ [a,b,c,d] $ tuples is $ [1,2,3,4] $ .

Similarly, other two tuples are $ [1,2,3,6] $ , $ [2,3,5,6] $ .

## 样例 #1

### 输入

```
3
6
5 3 6 1 4 2
4
1 2 3 4
10
5 1 6 2 8 3 4 10 9 7
```

### 输出

```
3
0
28
```



---

---
title: "Greetings"
layout: "post"
diff: 普及/提高-
pid: CF1915F
tag: ['树状数组']
---

# Greetings

## 题目描述

There are $ n $ people on the number line; the $ i $ -th person is at point $ a_i $ and wants to go to point $ b_i $ . For each person, $ a_i < b_i $ , and the starting and ending points of all people are distinct. (That is, all of the $ 2n $ numbers $ a_1, a_2, \dots, a_n, b_1, b_2, \dots, b_n $ are distinct.)

All the people will start moving simultaneously at a speed of $ 1 $ unit per second until they reach their final point $ b_i $ . When two people meet at the same point, they will greet each other once. How many greetings will there be?

Note that a person can still greet other people even if they have reached their final point.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of people.

Then $ n $ lines follow, the $ i $ -th of which contains two integers $ a_i $ and $ b_i $ ( $ -10^9 \leq a_i < b_i \leq 10^9 $ ) — the starting and ending positions of each person.

For each test case, all of the $ 2n $ numbers $ a_1, a_2, \dots, a_n, b_1, b_2, \dots, b_n $ are distinct.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer denoting the number of greetings that will happen.

## 说明/提示

In the first test case, the two people will meet at point $ 3 $ and greet each other.

## 样例 #1

### 输入

```
5
2
2 3
1 4
6
2 6
3 9
4 5
1 8
7 10
-2 100
4
-10 10
-5 5
-12 12
-13 13
5
-4 9
-2 5
3 4
6 7
8 10
4
1 2
3 4
5 6
7 8
```

### 输出

```
1
9
6
4
0
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

