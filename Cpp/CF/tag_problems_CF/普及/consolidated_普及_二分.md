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
title: "Glider"
layout: "post"
diff: 普及/提高-
pid: CF1041D
tag: ['二分', '前缀和']
---

# Glider

## 题目描述

```
你在玩一个吃鸡游戏，你现在要跳伞。你的飞机现在在高度为$h$的空中飞行，你每飞一个单位长度的距离，你就会下落一个单位长度的高度，当然，有些地方是上升气流，你不会下落，你会往前直飞，由于你想在空中就被人打死，求你最远的飞行距离

## 输入格式

第一行两个正整数$n$，$h$，代表有$n$段上升气流，飞机的高度为$h$。

接下来$n$行，每行两个数$x_{i1}$，$x_{i2}$。代表$x_{i1}$至$x_{i2}$这段区间为上升气流。

## 输出格式

一个整数，代表你最远的飞行距离
```

## 样例 #1

### 输入

```
3 4
2 5
7 9
10 11

```

### 输出

```
10

```

## 样例 #2

### 输入

```
5 10
5 7
11 12
16 20
25 26
30 33

```

### 输出

```
18

```

## 样例 #3

### 输入

```
1 1000000000
1 1000000000

```

### 输出

```
1999999999

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
title: "Chat Ban"
layout: "post"
diff: 普及/提高-
pid: CF1612C
tag: ['数学', '二分']
---

# Chat Ban

## 题目描述

You are a usual chat user on the most famous streaming platform. Of course, there are some moments when you just want to chill and spam something.

More precisely, you want to spam the emote triangle of size $ k $ . It consists of $ 2k-1 $ messages. The first message consists of one emote, the second one — of two emotes, ..., the $ k $ -th one — of $ k $ emotes, the $ k+1 $ -th one — of $ k-1 $ emotes, ..., and the last one — of one emote.

For example, the emote triangle for $ k=3 $ consists of $ 5 $ messages:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1612C/2949e1c874315434d0b3c1f5e20dee7c9097dc7a.png)Of course, most of the channels have auto moderation. Auto moderator of the current chat will ban you right after you spam at least $ x $ emotes in succession (you can assume you are the only user in the chat). Now you are interested — how many messages will you write before getting banned? Or maybe you will not get banned at all (i.e. will write all $ 2k-1 $ messages and complete your emote triangle successfully)? Note that if you get banned as a result of writing a message, this message is also counted.

You have to answer $ t $ independent test cases.

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The next $ t $ lines describe test cases.

The only line of the test case contains integers $ k $ and $ x $ ( $ 1 \le k \le 10^9; 1 \le x \le 10^{18} $ ).

## 输出格式

For each test case, print the number of messages you will write before getting banned for the corresponding values $ k $ and $ x $ .

## 说明/提示

Let's analyze the test cases of the example.

1. In the first test case, you write three messages containing $ 1 $ , $ 2 $ and $ 3 $ emotes respectively, and since $ 1 + 2 + 3 \ge 6 $ , you get banned after that.
2. In the second test case, you write four messages containing $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ emotes respectively, and since $ 1 + 2 + 3 + 4 \ge 7 $ , you get banned after that.
3. In the third test case, you write one message containing exactly $ 1 $ emote. It doesn't get you banned, since $ 1 < 2 $ , but you have already finished posting your emote triangle. So you wrote one message successfully.
4. In the fourth test case, you write four messages containing $ 1 $ , $ 2 $ , $ 3 $ and $ 2 $ emotes respectively, and since $ 1 + 2 + 3 + 2 \ge 7 $ , you get banned after that.
5. In the fifth test case, you write three messages containing $ 1 $ , $ 2 $ and $ 1 $ emote respectively. It doesn't get you banned, since $ 1 + 2 + 1 < 5 $ , but you have already finished posting your emote triangle. So you wrote three messages successfully.
6. In the sixth test case, since $ x = 1 $ , you get banned as soon as you send your first message.
7. The seventh test case is too large to analyze, so we'll skip it.

## 样例 #1

### 输入

```
7
4 6
4 7
1 2
3 7
2 5
100 1
1000000000 923456789987654321
```

### 输出

```
3
4
1
4
3
1
1608737403
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
title: "Mark and His Unfinished Essay"
layout: "post"
diff: 普及/提高-
pid: CF1705C
tag: ['二分']
---

# Mark and His Unfinished Essay

## 题目描述

One night, Mark realized that there is an essay due tomorrow. He hasn't written anything yet, so Mark decided to randomly copy-paste substrings from the prompt to make the essay.

More formally, the prompt is a string $ s $ of initial length $ n $ . Mark will perform the copy-pasting operation $ c $ times. Each operation is described by two integers $ l $ and $ r $ , which means that Mark will append letters $ s_l s_{l+1} \ldots s_r $ to the end of string $ s $ . Note that the length of $ s $ increases after this operation.

Of course, Mark needs to be able to see what has been written. After copying, Mark will ask $ q $ queries: given an integer $ k $ , determine the $ k $ -th letter of the final string $ s $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1\leq t\leq 1000 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ c $ , and $ q $ ( $ 1\leq n\leq 2\cdot 10^5 $ , $ 1\leq c\leq 40 $ , and $ 1\leq q\leq 10^4 $ ) — the length of the initial string $ s $ , the number of copy-pasting operations, and the number of queries, respectively.

The second line of each test case contains a single string $ s $ of length $ n $ . It is guaranteed that $ s $ only contains lowercase English letters.

The following $ c $ lines describe the copy-pasting operation. Each line contains two integers $ l $ and $ r $ ( $ 1\leq l\leq r\leq 10^{18} $ ). It is also guaranteed that $ r $ does not exceed the current length of $ s $ .

The last $ q $ lines of each test case describe the queries. Each line contains a single integer $ k $ ( $ 1\leq k\leq 10^{18} $ ). It is also guaranteed that $ k $ does not exceed the final length of $ s $ .

It is guaranteed that the sum of $ n $ and $ q $ across all test cases does not exceed $ 2\cdot 10^5 $ and $ 10^4 $ , respectively.

## 输出格式

For each query, print the $ k $ -th letter of the final string $ s $ .

## 说明/提示

In the first test case, the copy-paste process is as follows.

- The first step is pasting string $ \texttt{mark} $ at the end, yielding the string $ \texttt{mark}\color{red}{\texttt{mark}} $ .
- The second step is pasting string $ \texttt{mar} $ at the end, yielding the string $ \texttt{markmark}\color{red}{\texttt{mar}} $ .
- The third step is pasting string $ \texttt{rkmark} $ at the end, yielding the string $ \texttt{markmarkmar}\color{red}{\texttt{rkmark}} $ .

In the second test case, the copy-paste process is as follows.

- The first step is pasting string $ \texttt{re} $ at the end, yielding the string $ \texttt{creamii}\color{red}{\texttt{re}} $ .
- The second step is pasting string $ \texttt{ea} $ at the end, yielding the string $ \texttt{creamiire}\color{red}{\texttt{ea}} $ .
- The third step is pasting string $ \texttt{reamiire} $ at the end, yielding the string $ \texttt{creamiireea}\color{red}{\texttt{reamiire}} $ .

## 样例 #1

### 输入

```
2
4 3 3
mark
1 4
5 7
3 8
1
10
12
7 3 3
creamii
2 3
3 4
2 9
9
11
12
```

### 输出

```
m
a
r
e
a
r
```



---

---
title: "Min-Max Array Transformation"
layout: "post"
diff: 普及/提高-
pid: CF1721C
tag: ['二分']
---

# Min-Max Array Transformation

## 题目描述

给你一个升序数组 $a_1,a_2,...,a_n$。你要通过以下步骤去得到数组 $b_1,b_2,...,b_n$ ：

1. 生成数组 $d$，由$n$个非负整数组成。
2. 通过 $b_i=a_i+d_i$ 计算每一个 $b_i$。
3. 给 $b$ 进行升序排序。

你现在又知道了结果 $b$，你要算出每一个 $d_i$ 可能的最小值和最大值（每个 $d_i$ 的最值可以是由不同的数组 $d$ 满足的）。

## 输入格式

第一行一个整数 $t (1\le t \le 10^4)$，样例数。

每个样例的第一行一个整数 $n (1 \le n \le 2 * 10^5)$ 。

下一行 $n$ 个整数，$a_1,a_2,...,a_n (1 \le a_1 \le a_2 \le ... \le a_n \le 10^9)$。

下一行 $n$ 个整数，$b_1,b_2,...,b_n (1 \le b_1 \le b_2 \le ... \le b_n \le 10^9)$。

输入数据满足至少有一个满足题意的 $d$。
所有的 $n$ 和不超 $2 * 10^5$。

## 输出格式

每个样例两行：

第一行 $d_1^{min}, d_2^{min},..., d_n^{min}$。
第二行 $d_1^{max}, d_2^{max},..., d_3^{max}$。

## 说明/提示

第一个样例中，$d=[5,10,6]$ 满足 $d_1^{min}=5,b=[2+5,3+10,5+6]=[7,13,11]=[7,11,13]$。

第一个样例中，$d=[9,4,8]$ 满足 $d_2^{min}=4,b=[2+9,3+4,5+8]=[11,7,13]=[7,11,13]$。

## 样例 #1

### 输入

```
4
3
2 3 5
7 11 13
1
1000
5000
4
1 2 3 4
1 2 3 4
4
10 20 30 40
22 33 33 55
```

### 输出

```
5 4 2
11 10 8
4000
4000
0 0 0 0
0 0 0 0
12 2 3 15
23 13 3 15
```



---

---
title: "Iva & Pav"
layout: "post"
diff: 普及/提高-
pid: CF1878E
tag: ['线段树', '二分', 'ST 表']
---

# Iva & Pav

## 题目描述

Iva and Pav are a famous Serbian competitive programming couple. In Serbia, they call Pav "papuca" and that's why he will make all of Iva's wishes come true.

Iva gave Pav an array $ a $ of $ n $ elements.

Let's define $ f(l, r) = a_l \ \& \ a_{l+1} \ \& \dots \& \ a_r $ (here $ \& $ denotes the [bitwise AND operation](http://tiny.cc/bitwise_and)).

Note that $ f(l, r) $ is not defined when $ l>r $ .

Iva also gave Pav $ q $ queries.

Each query consists of 2 numbers, $ k $ and $ l $ , and she wants Pav to find the largest index $ r $ ( $ l \le r \le n $ ), such that $ f(l, r) \ge k $ .

Pav wants to solve this problem fast because he doesn't want to upset Iva. He needs your help.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of array $ a $ .

The third line of each test case contains a single integer $ q $ ( $ 1 \le q \le 10^5 $ ) — the number of queries Iva gave Pav.

The next $ q $ lines of each test case contains two numbers, $ l $ and $ k $ ( $ 1 \le l \le n $ , $ 1 \le k \le 10^9 $ ) — the left bound for the subsegment, and the integer $ k $ described in statement.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Also, it is guaranteed that the sum of $ q $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query output maximal index $ r $ ( $ l \le r \le n $ ) such that $ a_l \ \& \ a_{l+1} \ \& \dots \& \ a_r \ \ge \ k $ .

If such $ r $ doesn't exist, output $ -1 $ .

## 说明/提示

In the first test case $ n=5 $ , and the array $ a = [15, 14, 17, 42, 34] $

The first query asks for the biggest index $ r $ such that the $ f(1, r) \ge 7 $ .

 $ f(1,1) = 15, \ f(1, 2) = 14, \ f(1,3)=0 \ f(1, 4)=0 \ f(1, 5)=0 $ , so $ r=2 $ is the answer.

The second query asks for $ f(2, r) \ge 15 $ . Since such $ r $ doesn't exist, the answer is $ -1 $ .

The third query asks for $ f(4, r) \ge 5 $ . $ f(4, 4) = 42, \ f(4, 5) = 34 $ , so $ r=5 $ is the answer.

In the second test case $ n=5 $ , and the array $ a= [7, 5, 3, 1, 7] $ .

For the first query, $ f(1, r) \ge 7 $ .

 $ f(1, 1)=7, \ f(1, 2)=5, \ f(1, 3) = 1, \ f(1,4) = 1, \ f(1, 5)=1 $ , so the answer to this query is $ 1 $ .

For the second query, $ f(5, r) \ge 7 $ .

 $ f(5, 5) = 7 $ , so the answer is $ 5 $ .

For the third query, $ f(2, r) \ge 3 $ .

 $ f(2, 2) = 5, \ f(2, 3) = 1, \ f(2, 4) = 1, \ f(2, 5) = 1 $ , so the answer is $ 2 $ .

## 样例 #1

### 输入

```
3
5
15 14 17 42 34
3
1 7
2 15
4 5
5
7 5 3 1 7
4
1 7
5 7
2 3
2 2
7
19 20 15 12 21 7 11
4
1 15
4 4
7 12
5 7
```

### 输出

```
2 -1 5 
1 5 2 2 
2 6 -1 5
```



---

---
title: "Jumping Through Segments"
layout: "post"
diff: 普及/提高-
pid: CF1907D
tag: ['二分']
---

# Jumping Through Segments

## 题目描述

Polycarp is designing a level for a game. The level consists of $ n $ segments on the number line, where the $ i $ -th segment starts at the point with coordinate $ l_i $ and ends at the point with coordinate $ r_i $ .

The player starts the level at the point with coordinate $ 0 $ . In one move, they can move to any point that is within a distance of no more than $ k $ . After their $ i $ -th move, the player must land within the $ i $ -th segment, that is, at a coordinate $ x $ such that $ l_i \le x \le r_i $ . This means:

- After the first move, they must be inside the first segment (from $ l_1 $ to $ r_1 $ );
- After the second move, they must be inside the second segment (from $ l_2 $ to $ r_2 $ );
- ...
- After the $ n $ -th move, they must be inside the $ n $ -th segment (from $ l_n $ to $ r_n $ ).

The level is considered completed if the player reaches the $ n $ -th segment, following the rules described above. After some thought, Polycarp realized that it is impossible to complete the level with some values of $ k $ .

Polycarp does not want the level to be too easy, so he asks you to determine the minimum integer $ k $ with which it is possible to complete the level.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ )—the number of test cases. Descriptions of the test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ )—the number of segments in the level.

The following $ n $ lines.

The $ i $ -th line contain two integers $ l_i $ and $ r_i $ ( $ 0 \le l_i \le r_i \le 10^9 $ )—the boundaries of the $ i $ -th segment. Segments may intersect.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer—the minimum value of $ k $ with which it is possible to complete the level.

## 说明/提示

In the third example, the player can make the following moves:

- Move from point $ 0 $ to point $ 5 $ ( $ 3 \le 5 \le 8 $ );
- Move from point $ 5 $ to point $ 10 $ ( $ 10 \le 10 \le 18 $ );
- Move from point $ 10 $ to point $ 7 $ ( $ 6 \le 7 \le 11 $ ).

Note that for the last move, the player could have chosen not to move and still complete the level.

## 样例 #1

### 输入

```
4
5
1 5
3 4
5 6
8 10
0 1
3
0 2
0 1
0 3
3
3 8
10 18
6 11
4
10 20
0 5
15 17
2 2
```

### 输出

```
7
0
5
13
```



---

---
title: "Find the Different Ones!"
layout: "post"
diff: 普及/提高-
pid: CF1927D
tag: ['二分']
---

# Find the Different Ones!

## 题目描述

给定一个长度为 $n$ 的序列 $\{a\}$ 和 $q$ 次询问。每次询问给定 $l,r$，求在区间 $[l,r]$ 里是否存在满足 $l \le i,j \le r~,~a_i \ne a_j$ 的 $i,j$，如果存在则求出任意一种可能的情况。

## 输入格式

第一行一个整数 $T$ 表示数据组数。

在每组测试数据中，第一行一个整数 $n$，表示序列长度。

第二行 $n$ 个整数，表示序列 $\{a\}$。

第三行一个整数 $q$，表示询问个数。

## 输出格式

对于每次询问，输出用空格分隔的两个整数 $i,j$，满足 $l \le i,j \le r~,~a_i \ne a_j$，如果不存在这样的 $i,j$，则输出 $i=-1$ 和 $j=-1$。

每组测试数据之间可以用空行分隔，但这不是强制性要求。

## 说明/提示

对于所有测试点，满足 $1\le t\le10^4$，$2\le n\le2\times10^5$，$1 \le a_i \le 10^6$，$1 \le q \le 2\times10^5$，$1 \le l < r \le n$，单测试点所有测试数据中 $n$ 的和不超过 $2\times10^5$，所有 $q$ 的和也不超过 $2\times10^5$。

## 样例 #1

### 输入

```
5
5
1 1 2 1 1
3
1 5
1 2
1 3
6
30 20 20 10 10 20
5
1 2
2 3
2 4
2 6
3 5
4
5 2 3 4
4
1 2
1 4
2 3
2 4
5
1 4 3 2 4
5
1 5
2 4
3 4
3 5
4 5
5
2 3 1 4 2
7
1 2
1 4
1 5
2 4
2 5
3 5
4 5
```

### 输出

```
2 3
-1 -1
1 3

2 1
-1 -1
4 2
4 6
5 3

1 2
1 2
2 3
3 2

1 3
2 4
3 4
5 3
5 4

1 2
4 2
1 3
2 3
3 2
5 4
5 4
```



---

---
title: "Turtle vs. Rabbit Race: Optimal Trainings"
layout: "post"
diff: 普及/提高-
pid: CF1933E
tag: ['二分']
---

# Turtle vs. Rabbit Race: Optimal Trainings

## 题目描述

Isaac begins his training. There are $ n $ running tracks available, and the $ i $ -th track ( $ 1 \le i \le n $ ) consists of $ a_i $ equal-length sections.

Given an integer $ u $ ( $ 1 \le u \le 10^9 $ ), finishing each section can increase Isaac's ability by a certain value, described as follows:

- Finishing the $ 1 $ -st section increases Isaac's performance by $ u $ .
- Finishing the $ 2 $ -nd section increases Isaac's performance by $ u-1 $ .
- Finishing the $ 3 $ -rd section increases Isaac's performance by $ u-2 $ .
- $ \ldots $
- Finishing the $ k $ -th section ( $ k \ge 1 $ ) increases Isaac's performance by $ u+1-k $ . (The value $ u+1-k $ can be negative, which means finishing an extra section decreases Isaac's performance.)

You are also given an integer $ l $ . You must choose an integer $ r $ such that $ l \le r \le n $ and Isaac will finish each section of each track $ l, l + 1, \dots, r $ (that is, a total of $ \sum_{i=l}^r a_i = a_l + a_{l+1} + \ldots + a_r $ sections).

Answer the following question: what is the optimal $ r $ you can choose that the increase in Isaac's performance is maximum possible?

If there are multiple $ r $ that maximize the increase in Isaac's performance, output the smallest $ r $ .

To increase the difficulty, you need to answer the question for $ q $ different values of $ l $ and $ u $ .

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The descriptions of the test cases follow.

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^4 $ ).

The third line contains a single integer $ q $ ( $ 1 \le q \le 10^5 $ ).

The next $ q $ lines each contain two integers $ l $ and $ u $ ( $ 1 \le l \le n, 1 \le u \le 10^9 $ ) — the descriptions to each query.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . The sum of $ q $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ q $ integers: the $ i $ -th integer contains the optimal $ r $ for the $ i $ -th query. If there are multiple solutions, output the smallest one.

## 说明/提示

For the $ 1 $ -st query in the first test case:

- By choosing $ r = 3 $ , Isaac finishes $ a_1 + a_2 + a_3 = 3 + 1 + 4 = 8 $ sections in total, hence his increase in performance is $ u+(u-1)+\ldots+(u-7)=8+7+6+5+4+3+2+1 = 36 $ .
- By choosing $ r = 4 $ , Isaac finishes $ a_1 + a_2 + a_3 + a_4 = 3 + 1 + 4 + 1 = 9 $ sections in total, hence his increase in performance is $ u+(u-1)+\ldots+(u-8)=8+7+6+5+4+3+2+1+0 = 36 $ .

Both choices yield the optimal increase in performance, however we want to choose the smallest $ r $ . So we choose $ r = 3 $ .

For the $ 2 $ -nd query in the first test case, by choosing $ r = 4 $ , Isaac finishes $ a_2 + a_3 + a_4 = 1 + 4 + 1 = 6 $ sections in total, hence his increase in performance is $ u+(u-1)+\ldots+(u-5)=7+6+5+4+3+2 = 27 $ . This is the optimal increase in performance.

For the $ 3 $ -rd query in the first test case:

- By choosing $ r = 5 $ , Isaac finishes $ a_5 = 5 $ sections in total, hence his increase in performance is $ u+(u-1)+\ldots+(u-4)=9+8+7+6+5 = 35 $ .
- By choosing $ r = 6 $ , Isaac finishes $ a_5 + a_6 = 5 + 9 = 14 $ sections in total, hence his increase in performance is $ u+(u-1)+\ldots+(u-13)=9+8+7+6+5+4+3+2+1+0+(-1)+(-2)+(-3)+(-4) = 35 $ .

Both choices yield the optimal increase in performance, however we want to choose the smallest $ r $ . So we choose $ r = 5 $ .

Hence the output for the first test case is $ [3, 4, 5] $ .

## 样例 #1

### 输入

```
5
6
3 1 4 1 5 9
3
1 8
2 7
5 9
1
10
1
1 1
9
5 10 9 6 8 3 10 7 3
5
8 56
1 12
9 3
1 27
5 45
5
7 9 2 5 2
10
1 37
2 9
3 33
4 32
4 15
2 2
4 2
2 19
3 7
2 7
10
9 1 6 7 6 3 10 7 3 10
5
10 43
3 23
9 3
6 8
5 14
```

### 输出

```
3 4 5 
1 
9 2 9 4 9 
5 2 5 5 5 2 4 5 4 2 
10 6 9 7 7
```



---

---
title: "Tree Cutting"
layout: "post"
diff: 普及/提高-
pid: CF1946C
tag: ['图论', '二分']
---

# Tree Cutting

## 题目描述

You are given a tree with $ n $ vertices.

Your task is to find the maximum number $ x $ such that it is possible to remove exactly $ k $ edges from this tree in such a way that the size of each remaining connected component $ ^{\dagger} $ is at least $ x $ .

 $ ^{\dagger} $ Two vertices $ v $ and $ u $ are in the same connected component if there exists a sequence of numbers $ t_1, t_2, \ldots, t_k $ of arbitrary length $ k $ , such that $ t_1 = v $ , $ t_k = u $ , and for each $ i $ from $ 1 $ to $ k - 1 $ , vertices $ t_i $ and $ t_{i+1} $ are connected by an edge.

## 输入格式

Each test consists of several sets of input data. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of sets of input data. This is followed by a description of the sets of input data.

The first line of each set of input data contains two integers $ n $ and $ k $ ( $ 1 \le k < n \le 10^5 $ ) — the number of vertices in the tree and the number of edges to be removed.

Each of the next $ n - 1 $ lines of each set of input data contains two integers $ v $ and $ u $ ( $ 1 \le v, u \le n $ ) — the next edge of the tree.

It is guaranteed that the sum of the values of $ n $ for all sets of input data does not exceed $ 10^5 $ .

## 输出格式

For each set of input data, output a single line containing the maximum number $ x $ such that it is possible to remove exactly $ k $ edges from the tree in such a way that the size of each remaining connected component is at least $ x $ .

## 说明/提示

The tree in the first set of input data:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/832ffb4f88c37ab14f5b7a9eaac2d6382d506053.png)After removing the edge $ 1 $ — $ 3 $ , the tree will look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/fbcdbb17592694a687d8cacf2d552a9f2e19b5fc.png)The tree has split into two connected components. The first component consists of two vertices: $ 1 $ and $ 2 $ . The second connected component consists of three vertices: $ 3, 4 $ and $ 5 $ . In both connected components, there are at least two vertices. It can be shown that the answer $ 3 $ is not achievable, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
6
5 1
1 2
1 3
3 4
3 5
2 1
1 2
6 1
1 2
2 3
3 4
4 5
5 6
3 1
1 2
1 3
8 2
1 2
1 3
2 4
2 5
3 6
3 7
3 8
6 2
1 2
2 3
1 4
4 5
5 6
```

### 输出

```
2
1
3
1
1
2
```



---

---
title: "Cat, Fox and the Lonely Array"
layout: "post"
diff: 普及/提高-
pid: CF1973B
tag: ['二分', '位运算']
---

# Cat, Fox and the Lonely Array

## 题目描述

Today, Cat and Fox found an array $ a $ consisting of $ n $ non-negative integers.

Define the loneliness of $ a $ as the smallest positive integer $ k $ ( $ 1 \le k \le n $ ) such that for any two positive integers $ i $ and $ j $ ( $ 1 \leq i, j \leq n - k +1 $ ), the following holds: $ $$$a_i | a_{i+1} | \ldots | a_{i+k-1} = a_j | a_{j+1} | \ldots | a_{j+k-1}, $ $  where  $ x | y $  denotes the <a href="https://en.wikipedia.org/wiki/Bitwise_operation#OR">bitwise OR</a> of  $ x $  and  $ y $ . In other words, for every  $ k $  consecutive elements, their bitwise OR should be the same. Note that the loneliness of  $ a $  is well-defined, because for  $ k = n $  the condition is satisfied.</p><p>Cat and Fox want to know how lonely the array  $ a$$$ is. Help them calculate the loneliness of the found array.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4  $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < 2^{20} $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 10^5 $ .

## 输出格式

For each test case, print one integer — the loneliness of the given array.

## 说明/提示

In the first example, the loneliness of an array with a single element is always $ 1 $ , so the answer is $ 1 $ .

In the second example, the OR of each subarray of length $ k = 1 $ is $ 2 $ , so the loneliness of the whole array is $ 1 $ .

In the seventh example, it's true that $ (0 | 1 | 3) = (1 | 3 | 2) = (3 | 2 | 2) = (2 | 2 | 1) = (2 | 1 | 0) = (1 | 0 | 3) = 3 $ , so the condition is satisfied for $ k = 3 $ . We can verify that the condition is not true for any smaller $ k $ , so the answer is indeed $ 3 $ .

## 样例 #1

### 输入

```
7
1
0
3
2 2 2
3
1 0 2
5
3 0 1 4 2
5
2 0 4 0 2
7
0 0 0 0 1 2 4
8
0 1 3 2 2 1 0 3
```

### 输出

```
1
1
3
4
4
7
3
```



---

---
title: "Chamo and Mocha's Array"
layout: "post"
diff: 普及/提高-
pid: CF1975C
tag: ['二分']
---

# Chamo and Mocha's Array

## 题目描述

Mocha likes arrays, so before her departure, Chamo gave her an array $ a $ consisting of $ n $ positive integers as a gift.

Mocha doesn't like arrays containing different numbers, so Mocha decides to use magic to change the array. Mocha can perform the following three-step operation some (possibly, zero) times:

1. Choose indices $ l $ and $ r $ ( $ 1 \leq l < r \leq n $ )
2. Let $ x $ be the median $ ^\dagger $ of the subarray $ [a_l, a_{l+1},\ldots, a_r] $
3. Set all values $ a_l, a_{l+1},\ldots, a_r $ to $ x $

Suppose $ a=[1,2,3,4,5] $ initially:

- If Mocha chooses $ (l,r)=(3,4) $ in the first operation, then $ x=3 $ , the array will be changed into $ a=[1,2,3,3,5] $ .
- If Mocha chooses $ (l,r)=(1,3) $ in the first operation, then $ x=2 $ , the array will be changed into $ a=[2,2,2,4,5] $ .

Mocha will perform the operation until the array contains only the same number. Mocha wants to know what is the maximum possible value of this number.

 $ ^\dagger $ The median in an array $ b $ of length $ m $ is an element that occupies position number $ \lfloor \frac{m+1}{2} \rfloor $ after we sort the elements in non-decreasing order. For example, the median of $ [3,1,4,1,5] $ is $ 3 $ and the median of $ [5,25,20,24] $ is $ 20 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\leq t\leq 500 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2\leq n\leq 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1\leq a_i \leq 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output the maximum value of the number.

## 说明/提示

In the first test case, $ a=[1,2] $ . Mocha can only choose the interval $ (l,r)=(1,2) $ . The array will be changed to $ a=[1,1] $ . Therefore, the answer is $ 1 $ .

In the second test case, Mocha can perform the following operations:

- Choose the interval $ (l,r)=(4,5) $ , then $ a=[1,2,3,4,4] $ .
- Choose the interval $ (l,r)=(3,5) $ , then $ a=[1,2,4,4,4] $ .
- Choose the interval $ (l,r)=(1,5) $ , then $ a=[4,4,4,4,4] $ .

The array contains only the same number, which is $ 4 $ . It can be proven that the maximum value of the final number cannot be greater than $ 4 $ .

## 样例 #1

### 输入

```
2
2
1 2
5
1 2 3 4 5
```

### 输出

```
1
4
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
title: "Ruler (easy version)"
layout: "post"
diff: 普及/提高-
pid: CF1999G1
tag: ['数学', '二分']
---

# Ruler (easy version)

## 题目描述

本题是问题的简单版本。该版本与困难版之间的唯一区别是在这个版本中，你最多可以进行 $10$ 次查询。

这是一道交互题。

有一把有 $1001$ 个刻度的尺子，刻度分别为 $1 \sim 1001$。不幸的是，尺子丢失了一个刻度 $x$（$2 \le x \le 999$）。当你用尺子量一个长度为 $y$ 的物体时，尺子量出的结果为：
- 若 $y < x$，尺子将会量出正确的结果 $y$。
- 否则，尺子将会量出错误的结果 $y + 1$。

你需要找出丢失的刻度 $x$。你可以每次提供两个 $1$ 至 $1000$ 内的整数 $a,b$，你将会收到尺子量出的 $a$ 的长度与尺子量出的 $b$ 的长度之积。

你可以进行最多 $10$ 次询问。

## 输入格式

输入共一行一个整数 $T$，代表数据组数。

## 输出格式

你可以输出 `? a b` 以进行一次询问。`a` 和 `b` 的含义见上。随后，你将收到一个整数，表示尺子量出的 $a$ 的长度与尺子量出的 $b$ 的长度之积。

当你猜出 $x$ 后，你需要输出一行 `! x`，`x` 为你猜出的 $x$ 值。

如果你的询问大于 $10$ 次或猜出的 $x$ 值不对，你将收到一行一个 `-1`。请立刻终止程序。

在进行一次询问后，你需要刷新缓冲区。否则，你可能会获得 ILE（Idleness Limit Exceeded）。刷新缓冲区方法如下：
- 对于 C++：`fflush(stdout)` 或 `cout.flush()`；
- 对于 Java：`System.out.flush()`；
- 对于 Pascal：`flush(output)`；
- 对于 Python：`stdout.flush()`。

Translated by liuli688

## 样例 #1

### 输入

```
2

18

25


9999
```

### 输出

```
? 3 5

? 4 4

! 4
? 99 100

! 100
```



---

---
title: "Guess The Tree"
layout: "post"
diff: 普及/提高-
pid: CF2001C
tag: ['树形数据结构', '二分']
---

# Guess The Tree

## 题目描述

这是一道交互题。

Misuki 有一棵结构未知，具有 $n$ 个节点的树，节点编号从 $ 1 $ 到 $ n $ ，并要求你写一份代码来猜测它。

你可以询问以下问题：

`? a b`

其中 $a,b$ 为两个节点的编号。

对于一次询问，Misuki 会告诉你哪个节点 $x$ 能最小化 $|d(a,x)-d(b,x)|$ 的值，其中 $d(x,y)$ 是节点 $x$ 和 $y$ 之间的距离。如果存在多个这样的节点，Misuki 会告诉你最小化 $d(a,x)$ 的节点。

现要求你使用不超过 $15n$ 次的询问，来确定这棵树的结构。

## 输入格式

**本题有多组测试数据。** 第一行一个正整数 $t$ ，代表测试样例的个数，$1 \le t \le 200 $。

对于每组测试数据，一行一个正整数 $n$（$2 \le n \le 1000$），代表树中的节点数。

保证所有测试数据中 $n$ 的总和不超过 $1000$。

## 输出格式

交互从读取整数 $n$ 开始，
然后你最多可以进行 $15n$ 次查询。在每个查询后，读取一个整数作为查询的答案。

要输出答案，请按如下格式输出：

！$a_1$ $b_1$ $a_2$ $b_2$ ... $a_{n-1}$ $b_{n-1}$ 

这意味着对于 $1 \le i \le n-1$，节点 $ a_i $ 和 $ b_i $ 之间有一条边。你可以按任意顺序输出边。

在进行 $15n$ 次查询后，若再进行查询，将读取到 $-1$ 。收到 $-1$ 后，请终止程序以接收 Wrong Answer 判定。

## 说明/提示

打印每一行后（即进行一次询问或输出一次答案后），请输出回车并刷新输出缓冲区。可刷新输出缓冲区的有：

- C++ 中的 `fflush(stdout)` 或 `cout.flush()`;
- Java 中的 `System.out.flush()`;
- Pascal 中的 `flush(output)`;
- Python 中的 `stdout.flush()`;
- 对于其他语言，请参阅其他语言的文档。

Translated by @[ARIS2_0](https://www.luogu.com.cn/user/1340759)

## 样例 #1

### 输入

```
1
4
1
1
3
```

### 输出

```
? 1 2

? 1 3

? 1 4

! 1 2 1 3 3 4
```



---

---
title: "The Strict Teacher (Hard Version)"
layout: "post"
diff: 普及/提高-
pid: CF2005B2
tag: ['数学', '二分', '分类讨论']
---

# The Strict Teacher (Hard Version)

## 题目描述

**这是本题的困难版，它和本题的简单版的唯一差距是 $m$ 和 $q$ 的数据范围**。在此版本中，$m,q\le10^5$。你在解决两个版本之后才可以去提交 hack 数据。

Narek 和 Tsovak 正在热火朝天地准备这场比赛，所以他们没时间去做作业了，因此，他们决定去偷 David 的作业。

严厉的老师发现 David 的作业没了非常生气，打算狠狠地惩罚他，于是她雇佣了别的老师帮她一起抓捕 David。

现在有 $m$ 个老师正在一起追 David。幸运的是，教室非常的大，所以 David 有充足的躲藏空间。

教室可以被表示为一条一维直线，上面有 $n$ 个单元格编号从 $1$ 到 $n$，**包含边界。**

最初，David 和这 $m$ 个老师**在不同的单元格中**。然后他们将会进行若干次行动。每次行动中：
- 首先，David 可以移动到一个**相邻的**单元格中，**也可以不动。**
- 然后，每位老师也进行这样的一次移动。

行动将一直持续知道 David 被抓住，即有任何一个老师和 David 位于同一个单元格中。**所有人都看得见其它人的行动。**

你的任务是计算**在所有人按照最优方案行动的前提下，多少次行动后 David 会被抓住。**

> 按照最优方案行动，是指：
> - David 采取一种方案，使得老师抓住他所需的行动次数最大。
> - 老师之间相互配合并采用一种方案，使得他们能够用最少的行动次数抓住 David。

Narek 和 Tsovak 认为这个任务太简单了，于是他们决定给你 $q$ 次询问。

## 输入格式

**每个测试点有多组数据。**

第一行有一个正整数 $t(1\le t\le10^5)$，表示数据的组数。

每组数据的第一行有三个正整数 $n,m,q(3\le n\le10^9,1\le m,q\le10^5)$，分别表示单元格个数，老师个数，和询问次数。

每组数据的第二行有 $m$ 个**不同的**正整数 $b_1,b_2,\dots,b_m(1\le b_i\le n)$，代表每个老师初始的位置。

每组数据的第三行有 $q$ 个正整数 $a_1,a_2,\dots,a_q(1\le a_i\le n)$，代表每次询问中 David 的初始位置。

保证 $\forall i\in[1,m],j\in[1,q],b_i\ne a_j$。

保证 $\sum m,\sum q\le2\cdot10^5$。

## 输出格式

对于每组数据，输出 $q$ 行，第 $i$ 行是这组数据中的第 $i$ 次询问的答案。

### 样例解释翻译

在样例 $1$ 的唯一一次询问中，David 可以跑到 $1$ 号单元格。老师需要 $5$ 步来从 $6$ 号单元格跑到 $1$ 号单元格，所以答案为 $5$。

在样例 $2$ 的第二次讯问中，David 可以一直呆在 $3$ 号单元格。初始位于 $4$ 号单元格的老师一步就可以走到 $3$ 号单元格。因此答案为 $1$。

## 样例 #1

### 输入

```
2
8 1 1
6
3
10 3 3
1 4 8
2 3 10
```

### 输出

```
5
1
1
2
```



---

---
title: "Klee's SUPER DUPER LARGE Array!!!"
layout: "post"
diff: 普及/提高-
pid: CF2009E
tag: ['数学', '二分', '三分']
---

# Klee's SUPER DUPER LARGE Array!!!

## 题目描述

### 题目大意

你将得到一个长度为 $n$ 的序列 $a=[k,k+1,k+2,\dots, k+n-1]$，请求出 $S$ 的值，其中

$$S=\min\limits_{1\le x\le n}|(\sum\limits_{i=1}^x a_i)-(\sum\limits_{i=x+1}^n a_i)|$$

## 输入格式

**本题存在多组测试数据**。第一行为一个正整数 $T$（$1\le T\le 10^4$），表示数据组数。对于每组数据分别给出用空格隔开的两个整数 $n$ 与 $k$（$2\le n,k\le 10^9$）。

## 输出格式

对于每组数据，输出一行一个整数 $S$。

## 样例 #1

### 输入

```
4
2 2
7 2
5 3
1000000000 1000000000
```

### 输出

```
1
5
1
347369930
```



---

---
title: "Alice's Adventures in Cutting Cake"
layout: "post"
diff: 普及/提高-
pid: CF2028C
tag: ['二分', '双指针 two-pointer']
---

# Alice's Adventures in Cutting Cake

## 题目描述

爱丽丝参加了疯帽子的茶话会！有一块长长的蛋糕，由 $n$ 个部分组成，每个部分的美味度值为 $a_1, a_2, \ldots, a_n$ 。茶话会上共有 $m$ 个生物，但不包括爱丽丝。

爱丽丝将把蛋糕切成 $m + 1$ 块。正式地说，她将把蛋糕分成 $m + 1$ 个子串，每个子串由一定数量的相邻部分组成。一块蛋糕的美味度是其各部分美味度的总和。之后，她会将这些 $m + 1$ 块蛋糕分给 $m$ 个生物和她自己（她的那块蛋糕可以是空的）。但是，只有当每个 $m$ 个生物的蛋糕美味度达到或超过 $v$ 时，它们才会感到高兴。

Alice 想要确保每个生物都快乐。受此条件限制，她还想最大化自己的那块食物的美味程度。你能帮助 Alice 找到她的那块食物可以达到的最大美味程度吗？如果没有办法确保每个生物都快乐，则输出 $-1$ 。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 10^4$ )。测试用例的描述如下。

每个测试用例的第一行包含三个整数 $n, m, v$ ( $1\le m\le n\le 2\cdot 10^5$ ; $1\le v\le 10^9$ ) — 分别表示部分数量、生物数量和生物对美味的最低要求。

下一行包含 $n$ 个空格分隔的整数 $a_1, a_2, \ldots, a_n$ ( $1 \le a_i \le 10^9$ ) — 部分美味程度。

所有测试用例的总和 $n$ 不超过 $2\cdot 10^5$ 。

## 输出格式

对于每个测试用例，输出 Alice 可以达到的最大美味程度，或者如果没有办法确保每个生物都开心，则输出 $-1$ 。
### 样例解释

对于第一个测试案例，爱丽丝可以将第一和第二部分作为自己的部分，然后将剩余的 $10 + 1 + 1 + 10 = 22$ 美味度留给自己。我们可以证明她不能做得更好。

对于第二个测试案例，爱丽丝可以将第一和第二部分作为一个部分，将第六部分作为一个部分。然后她可以为自己拿走剩余的 $10 + 1 + 1 = 12$ 美味度。我们可以证明她不能做得更好。

对于第七个测试案例，爱丽丝不能给每个生物至少 $12$ 美味度的部分。

## 样例 #1

### 输入

```
7
6 2 1
1 1 10 1 1 10
6 2 2
1 1 10 1 1 10
6 2 3
1 1 10 1 1 10
6 2 10
1 1 10 1 1 10
6 2 11
1 1 10 1 1 10
6 2 12
1 1 10 1 1 10
6 2 12
1 1 1 1 10 10
```

### 输出

```
22
12
2
2
2
0
-1
```



---

---
title: "Trinity"
layout: "post"
diff: 普及/提高-
pid: CF2032C
tag: ['二分', '双指针 two-pointer']
---

# Trinity

## 题目描述

给定 $n$ 个元素的数组 $a_1, a_2, \ldots, a_n$。 

你可以进行如下操作任意次（包括 0 次）：

- 选择两个下标 $i, j\ (1 \le i, j \le n)$，令 $a_i := a_j$。

现请你求出使数组 $a$ 满足下列条件所需的最少操作次数。

- 对每个下标三元组 $(x, y, z)\ (1 \le x, y, z \le n, x \neq y, y \neq z, z \neq x)$ ，都有以 $a_x, a_y, a_z$ 为长度的三条线段可以构成一个非退化三角形。

## 输入格式

**题目有多组数据**。

第一行有一个整数 $T\ (1 \le T \le 10^4)$ ，表示测试数据组数。

对每一组数据，

第一行包括一个整数 $n \ (3 \le n \le 2 \times 10^5)$ 表示数组 $a$ 的元素个数。

第二行有 $n$ 个整数 $a_1, a_2, \ldots, a_n \ (1 \le a_i \le 10^9)$ 表示数组 $a$ 的元素。

保证所有 $n$ 的和不超过 $2 \times 10^5$。

## 输出格式

对每一组数据，输出一个整数表示最少操作次数。

## 说明/提示

对第一组样例，一种可能的操作方式如下：

- 令 $a_1 := a_4 = 4$，数组变为 $[4, 2, 3, 4, 5, 6, 7]$。
- 令 $a_2 := a_5 = 5$，数组变为 $[4, 5, 3, 4, 5, 6, 7]$。
- 令 $a_7 := a_4 = 4$，数组变为 $[4, 5, 3, 4, 5, 6, 4]$。

可以证明最终的数组符合条件，并且 3 次操作是最少的。

对第二组样例，我们令 $a_1 := a_2 = 3$ 使数组变为 $a = [3, 3, 2]$ 即可。

对第三组样例，既然 $3, 4, 5$ 已经可以构成三角形的三条边，我们并不需要进行任何操作。

## 样例 #1

### 输入

```
4
7
1 2 3 4 5 6 7
3
1 3 2
3
4 5 3
15
9 3 8 1 6 5 3 8 2 1 4 2 9 4 7
```

### 输出

```
3
1
0
8
```



---

---
title: "Bowling Frame"
layout: "post"
diff: 普及/提高-
pid: CF2041B
tag: ['数学', '二分']
---

# Bowling Frame

## 题目描述

题面涉及到政治敏感内容，请在 Codeforces 查阅。

## 输入格式

The first line of the input contains a single integer $ t $ , the number of test cases. Each of the following $ t $ lines contains two integers $ w $ and $ b $ , the number of white and black pins, respectively.

- $ 1 \leq t \leq 100 $
- $ 0 \leq w, b \leq 10^9 $

## 输出格式

For each test case, output in a single line the side length $ k $ of the largest pin satisfying Maw-Shang's requirement you can build with the given pins.

## 样例 #1

### 输入

```
4
1 2
3 2
3 3
12 0
```

### 输出

```
2
2
3
4
```



---

---
title: "Counting Pairs"
layout: "post"
diff: 普及/提高-
pid: CF2051D
tag: ['二分']
---

# Counting Pairs

## 题目描述

给定一个整数序列 $ a $，长度为 $ n $，其中第 $ i $ 个元素为 $ a_i $。此外，还有两个整数 $ x $ 和 $ y $，且满足 $ x \le y $。

如果一对整数 $ (i, j) $ 满足以下条件，则称其为有趣的：

- $ 1 \le i < j \le n $；
- 从序列 $ a $ 中同时移除位置 $ i $ 和 $ j $ 的元素后，剩余元素的和在 $ x $ 和 $ y $ 之间。

你的任务是找出给定序列 $ a $ 中有多少对这样的有趣整数组合。

## 输入格式

第一行输入一个整数 $ t $（$ 1 \le t \le 10^4 $），表示测试用例的数量。

每个测试用例包含两行：

- 第一行输入三个整数 $ n, x, y $（$ 3 \le n \le 2 \cdot 10^5 $，$ 1 \le x \le y \le 2 \cdot 10^{14} $）；
- 第二行输入包含 $ n $ 个整数 $ a_1, a_2, \dots, a_n $（$ 1 \le a_i \le 10^9 $）。

输入附加条件为：所有测试用例中的 $ n $ 之和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对于每个测试用例，输出一个整数，表示序列 $ a $ 中有趣的整数对的数量。

## 说明/提示

例如，在第一个示例中，有 $ 4 $ 个有趣的整数组合：

1. $ (1, 2) $；
2. $ (1, 4) $；
3. $ (2, 3) $；
4. $ (3, 4) $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
7
4 8 10
4 6 3 6
6 22 27
4 9 6 3 4 5
3 8 10
3 2 1
3 1 1
2 3 4
3 3 6
3 2 1
4 4 12
3 3 2 1
6 8 8
1 1 2 2 2 3
```

### 输出

```
4
7
0
0
1
5
6
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
title: "Two Colors"
layout: "post"
diff: 普及/提高-
pid: CF2075C
tag: ['二分']
---

# Two Colors

## 题目描述

Monocarp 决定按照以下规则粉刷围栏：
- 每块木板必须被涂上恰好一种颜色；
- 使用的不同颜色总数必须恰好为两种；
- 相同颜色的木板必须形成连续序列，即对于所有被涂成同一颜色的木板对，它们之间不存在被涂成其他颜色的木板。

Monocarp 有 $m$ 种不同的颜料，其中第 $i$ 种颜色的颜料最多可以涂 $a_i$ 块木板。Monocarp 不会购买额外颜料。

你的任务是计算满足 Monocarp 所有描述的愿望的围栏涂色方式数目。两种涂色方式被认为是不同的，当且仅当存在至少一块木板在这两种方式中被涂成不同颜色。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$2 \le n, m \le 2 \cdot 10^5$）——围栏的木板数量以及 Monocarp 拥有的不同颜色数量。

第二行包含 $m$ 个整数 $a_1, a_2, \dots, a_m$（$1 \le a_i \le n$），其中 $a_i$ 表示第 $i$ 种颜色最多可涂的木板数量。

所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。所有测试用例的 $m$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出满足条件的不同涂色方式数目。

## 说明/提示

第一个测试案例中，存在 $4$ 种不同的涂色方式（木板从左到右的颜色编号序列如下）：
1. $[1, 2, 2, 2, 2]$；
2. $[1, 1, 2, 2, 2]$；
3. $[2, 2, 2, 1, 1]$；
4. $[2, 2, 2, 2, 1]$。

第二个测试案例中，存在 $6$ 种不同的涂色方式（木板从左到右的颜色编号序列如下）：
1. $[1, 2, 2, 2, 2]$；
2. $[1, 1, 2, 2, 2]$；
3. $[1, 1, 1, 2, 2]$；
4. $[2, 2, 1, 1, 1]$；
5. $[2, 2, 2, 1, 1]$；
6. $[2, 2, 2, 2, 1]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
5 2
2 4
5 2
3 4
12 3
5 9 8
```

### 输出

```
4
6
22
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
title: "Min Max MEX"
layout: "post"
diff: 普及/提高-
pid: CF2093E
tag: ['二分']
---

# Min Max MEX

## 题目描述

给定一个长度为 $n$ 的数组 $a$ 和一个数字 $k$。

子数组被定义为数组中一个或多个连续元素组成的序列。你需要将数组 $a$ 分割成 $k$ 个互不重叠的子数组 $b_1, b_2, \dots, b_k$，使得这些子数组的并集等于整个数组。此外，你需要最大化 $x$ 的值，其中 $x$ 等于所有子数组 $b_i$（$i \in [1..k]$）的 MEX 的最小值。

MEX $(v)$ 表示数组 $v$ 中未出现的最小非负整数。

## 输入格式

第一行包含一个整数 $t$（$1\leq t\leq 10^4$）——测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$1\leq k \leq n \leq 2 \cdot 10^5$）——数组的长度和需要分割成的子数组数量。

每个测试用例的第二行包含 $n$ 个整数 $a_i$（$0\leq a_i\leq 10^9$）——数组的元素。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个查询，输出一个数字——最大的 $x$ 值，使得存在一种将数组 $a$ 分割成 $k$ 个子数组的方式，其中所有子数组的 MEX 的最小值等于 $x$。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
1 1
0
5 1
0 1 3 2 4
6 2
2 1 0 0 1 2
5 5
0 0 0 0 0
5 2
2 3 4 5 6
6 2
0 0 1 1 2 2
4 4
1 0 0 0
```

### 输出

```
1
5
3
1
0
1
0
```



---

---
title: "Wolf"
layout: "post"
diff: 普及/提高-
pid: CF2106E
tag: ['二分']
---

# Wolf

## 题目描述

狼发现了 $n$ 只羊，它们的可口度分别为 $p_1, p_2, ..., p_n$，其中 $p$ 是一个排列$^{\text{∗}}$。狼想在 $p$ 上使用二分查找来寻找可口度为 $k$ 的羊，但 $p$ 可能并未排序。对于区间 $[l, r]$ 上寻找 $k$ 的二分查找是否成功，用 $f(l, r, k)$ 表示，其定义如下：

如果 $l > r$，则 $f(l, r, k)$ 失败。否则，令 $m = \lfloor\frac{l + r}{2}\rfloor$，然后：

- 如果 $p_m = k$，则 $f(l, r, k)$ 成功；
- 如果 $p_m < k$，则 $f(l, r, k) = f(m+1, r, k)$；
- 如果 $p_m > k$，则 $f(l, r, k) = f(l, m-1, k)$。

书呆子牛决定帮助狼。书呆子牛会收到 $q$ 个查询，每个查询包含三个整数 $l$、$r$ 和 $k$。在开始查找之前，书呆子牛可以选择一个非负整数 $d$ 和 $d$ 个下标 $1 \le i_1 < i_2 < \ldots < i_d \le n$，其中对于所有 $1 \leq j \leq d$ 都有 $p_{i_j} \neq k$。然后，他可以随意重新排列元素 $p_{i_1}, p_{i_2}, ..., p_{i_d}$。

对于每个查询，输出书呆子牛需要选择的最小整数 $d$，使得 $f(l, r, k)$ 能够成功，或者报告这是不可能的。注意，查询是独立的，且实际的重新排列不会被执行。

$^{\text{∗}}$ 长度为 $n$ 的排列是指包含从 $1$ 到 $n$ 的所有整数且每个整数恰好出现一次的数组。

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $q$（$1 \le n, q \le 2 \cdot 10^5$）——分别表示 $p$ 的长度和查询的数量。

第二行包含 $n$ 个整数 $p_1, p_2, ..., p_n$——表示第 $i$ 只羊的可口度。保证 $p$ 中每个从 $1$ 到 $n$ 的整数恰好出现一次。

接下来的 $q$ 行每行包含三个整数 $l$、$r$ 和 $k$（$1 \le l \le r \le n$，$1 \le k \le n$）——分别表示二分查找的区间范围和要查找的整数。

保证所有测试用例的 $n$ 之和和 $q$ 之和均不超过 $2 \cdot 10^5$。

## 输出格式

对于每个查询，输出一行，表示书呆子牛需要选择的最小整数 $d$，使得 $f(l, r, k)$ 能够成功。如果不可能，则输出 $-1$。


## 说明/提示

在第一个样例的第二个查询中：由于 $4$ 不存在于前三个元素中，因此在该范围内查找 $4$ 是不可能的。

在第二个样例的第一个查询中，可以选择下标 $2$ 和 $3$，并交换它们，使得 $p = [3, 5, 1, 2, 7, 6, 4]$。然后，$f(3, 4, 2)$ 的执行过程如下：

1. 令 $m = \lfloor \frac{3 + 4}{2} \rfloor = 3$。因为 $p_3 = 1 < 2$，所以 $f(3, 4, 2) = f(4, 4, 2)$。
2. 令 $m = \lfloor \frac{4 + 4}{2} \rfloor = 4$。因为 $p_4 = 2 = k$，所以 $f(4, 4, 2)$ 成功，因此 $f(3, 4, 2)$ 也成功。

总共选择了 $2$ 个下标，因此最终的成本是 $2$，可以证明这是最小的。注意，对于这个查询，不能选择下标 $4$，因为 $p_4 = k = 2$。

在第二个样例的最后一个查询中，可以选择下标 $2, 3, 4, 5$ 并重新排列它们，使得 $p = [3, 5, 2, 7, 1, 6, 4]$。然后，$f(1, 7, 3)$ 成功。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
5 3
1 2 3 4 5
1 5 4
1 3 4
3 4 4
7 4
3 1 5 2 7 6 4
3 4 2
2 3 5
1 5 6
1 7 3
2 1
2 1
1 2 1
1 1
1
1 1 1
7 1
3 4 2 5 7 1 6
1 7 1
16 1
16 10 12 6 13 9 14 3 8 11 15 2 7 1 5 4
1 16 4
16 1
14 1 3 15 4 5 6 16 7 8 9 10 11 12 13 2
1 16 14
13 1
12 13 10 9 8 4 11 5 7 6 2 1 3
1 13 2
```

### 输出

```
0 -1 0 
2 0 -1 4 
-1 
0 
-1 
-1 
-1 
-1
```



---

---
title: "Baudelaire (easy version)"
layout: "post"
diff: 普及/提高-
pid: CF2106G1
tag: ['二分', '交互题']
---

# Baudelaire (easy version)

## 题目描述

这是该问题的简单版本。两个版本之间的唯一区别在于，在这个版本中，保证每个节点都与节点 $1$ 相邻。

本题是交互题。

波德莱尔非常富有，所以他购买了一棵大小为 $n$ 的树，这棵树以某个任意节点为根。此外，每个节点的值为 $1$ 或 $-1$。在这个版本中，每个节点都与节点 $1$ 相邻。但请注意，节点 $1$ 不一定是根节点。

书呆子牛看到了这棵树并爱上了它。然而，计算机科学的收入不足以让他买下这棵树。波德莱尔决定和书呆子牛玩一个游戏，如果他赢了，就把这棵树送给他。

书呆子牛不知道哪个节点是根，也不知道节点的值。但他可以向波德莱尔提出两种类型的查询：

1. `1 k u₁ u₂ ... uₖ`：设 $f(u)$ 为从树的根到节点 $u$ 的路径上所有节点的值之和。书呆子牛可以选择一个整数 $k$（$1 \le k \le n$）和 $k$ 个节点 $u_1, u_2, ..., u_k$，然后他会收到值 $f(u_1) + f(u_2) + ... + f(u_k)$。
2. `2 u`：波德莱尔将切换节点 $u$ 的值。具体来说，如果 $u$ 的值为 $1$，则变为 $-1$，反之亦然。

如果书呆子牛在总共 $n + 200$ 次查询内正确猜出每个节点的值（即执行查询后树的最终值），他就获胜。你能帮助他获胜吗？

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 100$），表示测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 10^3$），表示树的大小。

接下来的 $n-1$ 行每行包含两个整数 $u$ 和 $v$（$1 \le u, v \le n$，$u \neq v$），表示树中节点 $u$ 和 $v$ 之间有一条边。在这个版本中，保证 $u = 1$ 或 $v = 1$。

保证所有测试用例的 $n$ 之和不超过 $10^3$，并且每个输入的图都是合法的树。

## 输出格式

要提出类型 $1$ 的查询，请按以下格式输出一行（不带引号）：
- `? 1 k u₁ u₂ ... uₖ`（$1 \le k, u_i \le n$）

评测机将返回一个整数，即 $f(u_1) + f(u_2) + ... + f(u_k)$。

要提出类型 $2$ 的查询，请按以下格式输出一行：
- `? 2 u`（$1 \le u \le n$）

评测机会切换节点 $u$ 的值：如果其值为 $1$，则变为 $-1$，反之亦然。

当你找到答案时，请按以下格式输出一行：
- `! v₁ v₂ ... vₙ`（$v_i = 1$ 或 $v_i = -1$，$v_i$ 是执行查询后节点 $i$ 的值）

之后，继续处理下一个测试用例，或者如果是最后一个测试用例则终止程序。输出答案不计入查询次数。

交互器不是自适应的，这意味着树的值在参与者提出查询之前就已经确定。

如果你的程序进行了超过 $n + 200$ 次查询，它应立即终止并收到 Wrong Answer 的判定。否则，你可能会得到任意判定，因为你的解决方案将继续从已关闭的流中读取数据。

在打印查询后，不要忘记输出换行符并刷新输出缓冲区。否则，你可能会得到 Idleness Limit Exceeded 的判定。可以使用以下方法刷新输出：
- C++：`fflush(stdout)` 或 `cout.flush()`
- Java：`System.out.flush()`
- Pascal：`flush(output)`
- Python：`stdout.flush()`
- 其他语言请参考相关文档。

## Hack 格式

对于 Hack 攻击，请使用以下格式：

第一行应包含一个整数 $t$（$1 \le t \le 100$）——测试用例的数量。

每个测试用例的第一行必须包含两个整数 $n$ 和 $root$（$2 \le n \le 10^3$，$1 \le root \le n$）——树的大小和树的根节点。

每个测试用例的第二行必须包含 $n$ 个整数 $a_1, a_2, ..., a_n$（$|a_i| = 1$）——其中 $a_i$ 是节点 $i$ 的值。

接下来的 $n-1$ 行每行必须包含两个整数 $u$ 和 $v$（$1 \le u, v \le n$）——表示节点 $u$ 和 $v$ 之间有一条边。

所有测试用例的 $n$ 之和不得超过 $10^3$，并且每个输入的图必须是合法的树。对于此版本，每个节点必须与节点 $1$ 相邻。

## 说明/提示

在示例中，树的根是节点 $2$，节点的初始值为 $[-1, 1, -1, 1]$。因此，$f(1) = 0$，$f(2) = 1$，$f(3) = -1$，$f(4) = 1$。

首先，我们查询 $f(1) + f(2) + f(3)$ 的和，得到 $0$。然后，我们切换节点 $2$ 的值，此时节点的值变为 $[-1, -1, -1, 1]$。因此，$f(1) = -2$，$f(2) = -1$，$f(3) = -3$，$f(4) = -1$，$f(1) + f(2) + f(3) = -6$。

最终，我们推断出节点的值为 $[-1, -1, -1, 1]$，并输出该结果。

注意，这只是一个解释查询如何工作的示例，并不涉及具体的解题策略。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
1
4
1 2
3 1
1 4

0


-6
```

### 输出

```
? 1 3 1 2 3

? 2 2
? 1 3 1 2 3

! -1 -1 -1 1
```



---

---
title: "Coloring Game"
layout: "post"
diff: 普及/提高-
pid: CF2112C
tag: ['二分', '枚举', '双指针 two-pointer']
---

# Coloring Game

## 题目描述

Alice 和 Bob 使用一个长度为 $n$ 的数列 $a$ 进行游戏。

初始时，任何数列中的数字都没有被染色。首先，Alice 选择 $3$ 个 $a$ 中的元素并将它们染为红色。然后 Bob 将选择一个任意元素并将它染为蓝色（如果这个元素原本是红色的，那么蓝色将覆盖掉红色）。Alice 获胜当且仅当剩余的红色的数字之和严格大于蓝色的数字。

你需要计算 Alice 有多少种选择 $3$ 个元素染色的方案使得无论 Bob 如何操作 Alive 都将获胜。

## 输入格式

多组数据。第一行一个整数 $t$ ($1\le t\le 1000$) 表示数据组数。

对于每组数据，第一行一个整数 $n$ ($3\le n\le 5000$)。\
第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n$ ($1\le a_1\le a_2\le \cdots\le a_n\le 10^5$)。

保证单个测试点内 $\sum n\le 5000$。

## 输出格式

对于每组数据，输出一行一个整数表示答案。

## 说明/提示

**样例解释**

对于前两组数据，无论 Alice 怎么选择元素，Bob 总有办法选择元素使得 Alice 不能获胜。

对于第三组数据，Alice 可以选择任意的三个元素。如果 Bob 选择对红色的某个元素染色，红色数字的和将为 $14$，蓝色数字的和将为 $7$；如果 Bob 选择对某个未染色的元素染色，红色数字的和将为 $21$，蓝色数字的和将为 $7$。

对于第四组数据，Alice 可以选择 $a_1,a_3,a_4$ 或 $a_2,a_3,a_4$。

## 样例 #1

### 输入

```
6
3
1 2 3
4
1 1 2 4
5
7 7 7 7 7
5
1 1 2 2 4
6
2 3 3 4 5 5
5
1 1 1 1 3
```

### 输出

```
0
0
10
2
16
0
```



---

---
title: "Multiplication Table"
layout: "post"
diff: 普及/提高-
pid: CF448D
tag: ['模拟', '二分', '枚举']
---

# Multiplication Table

## 题目描述

Bizon the Champion isn't just charming, he also is very smart.

While some of us were learning the multiplication table, Bizon the Champion had fun in his own manner. Bizon the Champion painted an $ n×m $ multiplication table, where the element on the intersection of the $ i $ -th row and $ j $ -th column equals $ i·j $ (the rows and columns of the table are numbered starting from 1). Then he was asked: what number in the table is the $ k $ -th largest number? Bizon the Champion always answered correctly and immediately. Can you repeat his success?

Consider the given multiplication table. If you write out all $ n·m $ numbers from the table in the non-decreasing order, then the $ k $ -th number you write out is called the $ k $ -th largest number.

## 输入格式

The single line contains integers $ n $ , $ m $ and $ k $ $ (1<=n,m<=5·10^{5}; 1<=k<=n·m) $ .

## 输出格式

Print the $ k $ -th largest number in a $ n×m $ multiplication table.

## 说明/提示

A $ 2×3 $ multiplication table looks like this:

`<br></br>1 2 3<br></br>2 4 6<br></br><br></br>`

## 样例 #1

### 输入

```
2 2 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 3 4

```

### 输出

```
3

```

## 样例 #3

### 输入

```
1 10 5

```

### 输出

```
5

```



---

---
title: "An impassioned circulation of affection"
layout: "post"
diff: 普及/提高-
pid: CF814C
tag: ['二分', '枚举', '前缀和']
---

# An impassioned circulation of affection

## 题目描述

Nadeko's birthday is approaching! As she decorated the room for the party, a long garland of Dianthus-shaped paper pieces was placed on a prominent part of the wall. Brother Koyomi will like it!

Still unsatisfied with the garland, Nadeko decided to polish it again. The garland has $ n $ pieces numbered from $ 1 $ to $ n $ from left to right, and the $ i $ -th piece has a colour $ s_{i} $ , denoted by a lowercase English letter. Nadeko will repaint at most $ m $ of the pieces to give each of them an arbitrary new colour (still denoted by a lowercase English letter). After this work, she finds out all subsegments of the garland containing pieces of only colour $ c $ — Brother Koyomi's favourite one, and takes the length of the longest among them to be the Koyomity of the garland.

For instance, let's say the garland is represented by "kooomo", and Brother Koyomi's favourite colour is "o". Among all subsegments containing pieces of "o" only, "ooo" is the longest, with a length of $ 3 $ . Thus the Koyomity of this garland equals $ 3 $ .

But problem arises as Nadeko is unsure about Brother Koyomi's favourite colour, and has swaying ideas on the amount of work to do. She has $ q $ plans on this, each of which can be expressed as a pair of an integer $ m_{i} $ and a lowercase letter $ c_{i} $ , meanings of which are explained above. You are to find out the maximum Koyomity achievable after repainting the garland according to each plan.

## 输入格式

The first line of input contains a positive integer $ n $ ( $ 1<=n<=1500 $ ) — the length of the garland.

The second line contains $ n $ lowercase English letters $ s_{1}s_{2}...\ s_{n} $ as a string — the initial colours of paper pieces on the garland.

The third line contains a positive integer $ q $ ( $ 1<=q<=200000 $ ) — the number of plans Nadeko has.

The next $ q $ lines describe one plan each: the $ i $ -th among them contains an integer $ m_{i} $ ( $ 1<=m_{i}<=n $ ) — the maximum amount of pieces to repaint, followed by a space, then by a lowercase English letter $ c_{i} $ — Koyomi's possible favourite colour.

## 输出格式

Output $ q $ lines: for each work plan, output one line containing an integer — the largest Koyomity achievable after repainting the garland according to it.

## 说明/提示

In the first sample, there are three plans:

- In the first plan, at most $ 1 $ piece can be repainted. Repainting the "y" piece to become "o" results in "kooomi", whose Koyomity of $ 3 $ is the best achievable;
- In the second plan, at most $ 4 $ pieces can be repainted, and "oooooo" results in a Koyomity of $ 6 $ ;
- In the third plan, at most $ 4 $ pieces can be repainted, and "mmmmmi" and "kmmmmm" both result in a Koyomity of $ 5 $ .

## 样例 #1

### 输入

```
6
koyomi
3
1 o
4 o
4 m

```

### 输出

```
3
6
5

```

## 样例 #2

### 输入

```
15
yamatonadeshiko
10
1 a
2 a
3 a
4 a
5 a
1 b
2 b
3 b
4 b
5 b

```

### 输出

```
3
4
5
7
8
1
2
3
4
5

```

## 样例 #3

### 输入

```
10
aaaaaaaaaa
2
10 b
10 z

```

### 输出

```
10
10

```



---

