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
title: "Planning The Expedition"
layout: "post"
diff: 普及/提高-
pid: CF1011B
tag: ['模拟', '枚举', '概率论']
---

# Planning The Expedition

## 题目描述

Natasha is planning an expedition to Mars for $ n $ people. One of the important tasks is to provide food for each participant.

The warehouse has $ m $ daily food packages. Each package has some food type $ a_i $ .

Each participant must eat exactly one food package each day. Due to extreme loads, each participant must eat the same food type throughout the expedition. Different participants may eat different (or the same) types of food.

Formally, for each participant $ j $ Natasha should select his food type $ b_j $ and each day $ j $ -th participant will eat one food package of type $ b_j $ . The values $ b_j $ for different participants may be different.

What is the maximum possible number of days the expedition can last, following the requirements above?

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 100 $ , $ 1 \le m \le 100 $ ) — the number of the expedition participants and the number of the daily food packages available.

The second line contains sequence of integers $ a_1, a_2, \dots, a_m $ ( $ 1 \le a_i \le 100 $ ), where $ a_i $ is the type of $ i $ -th food package.

## 输出格式

Print the single integer — the number of days the expedition can last. If it is not possible to plan the expedition for even one day, print 0.

## 说明/提示

In the first example, Natasha can assign type $ 1 $ food to the first participant, the same type $ 1 $ to the second, type $ 5 $ to the third and type $ 2 $ to the fourth. In this case, the expedition can last for $ 2 $ days, since each participant can get two food packages of his food type (there will be used $ 4 $ packages of type $ 1 $ , two packages of type $ 2 $ and two packages of type $ 5 $ ).

In the second example, there are $ 100 $ participants and only $ 1 $ food package. In this case, the expedition can't last even $ 1 $ day.

## 样例 #1

### 输入

```
4 10
1 5 2 1 1 1 2 5 7 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
100 1
1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
2 5
5 4 3 2 1

```

### 输出

```
1

```

## 样例 #4

### 输入

```
3 9
42 42 42 42 42 42 42 42 42

```

### 输出

```
3

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
title: "Vasya and Golden Ticket"
layout: "post"
diff: 普及/提高-
pid: CF1030C
tag: ['搜索', '枚举', '前缀和']
---

# Vasya and Golden Ticket

## 题目描述

Recently Vasya found a golden ticket — a sequence which consists of $ n $ digits $ a_1a_2\dots a_n $ . Vasya considers a ticket to be lucky if it can be divided into two or more non-intersecting segments with equal sums. For example, ticket $ 350178 $ is lucky since it can be divided into three segments $ 350 $ , $ 17 $ and $ 8 $ : $ 3+5+0=1+7=8 $ . Note that each digit of sequence should belong to exactly one segment.

Help Vasya! Tell him if the golden ticket he found is lucky or not.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 100 $ ) — the number of digits in the ticket.

The second line contains $ n $ digits $ a_1 a_2 \dots a_n $ ( $ 0 \le a_i \le 9 $ ) — the golden ticket. Digits are printed without spaces.

## 输出格式

If the golden ticket is lucky then print "YES", otherwise print "NO" (both case insensitive).

## 说明/提示

In the first example the ticket can be divided into $ 7 $ , $ 34 $ and $ 52 $ : $ 7=3+4=5+2 $ .

In the second example it is impossible to divide ticket into segments with equal sum.

## 样例 #1

### 输入

```
5
73452

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4
1248

```

### 输出

```
NO

```



---

---
title: "Curiosity Has No Limits"
layout: "post"
diff: 普及/提高-
pid: CF1031B
tag: ['枚举']
---

# Curiosity Has No Limits

## 题目描述

When Masha came to math classes today, she saw two integer sequences of length $ n - 1 $ on the blackboard. Let's denote the elements of the first sequence as $ a_i $ ( $ 0 \le a_i \le 3 $ ), and the elements of the second sequence as $ b_i $ ( $ 0 \le b_i \le 3 $ ).

Masha became interested if or not there is an integer sequence of length $ n $ , which elements we will denote as $ t_i $ ( $ 0 \le t_i \le 3 $ ), so that for every $ i $ ( $ 1 \le i \le n - 1 $ ) the following is true:

- $ a_i = t_i | t_{i + 1} $ (where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR)) and
- $ b_i = t_i \& t_{i + 1} $ (where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND)).

The question appeared to be too difficult for Masha, so now she asked you to check whether such a sequence $ t_i $ of length $ n $ exists. If it exists, find such a sequence. If there are multiple such sequences, find any of them.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 10^5 $ ) — the length of the sequence $ t_i $ .

The second line contains $ n - 1 $ integers $ a_1, a_2, \ldots, a_{n-1} $ ( $ 0 \le a_i \le 3 $ ) — the first sequence on the blackboard.

The third line contains $ n - 1 $ integers $ b_1, b_2, \ldots, b_{n-1} $ ( $ 0 \le b_i \le 3 $ ) — the second sequence on the blackboard.

## 输出格式

In the first line print "YES" (without quotes), if there is a sequence $ t_i $ that satisfies the conditions from the statements, and "NO" (without quotes), if there is no such sequence.

If there is such a sequence, on the second line print $ n $ integers $ t_1, t_2, \ldots, t_n $ ( $ 0 \le t_i \le 3 $ ) — the sequence that satisfies the statements conditions.

If there are multiple answers, print any of them.

## 说明/提示

In the first example it's easy to see that the sequence from output satisfies the given conditions:

- $ t_1 | t_2 = (01_2) | (11_2) = (11_2) = 3 = a_1 $ and $ t_1 \& t_2 = (01_2) \& (11_2) = (01_2) = 1 = b_1 $ ;
- $ t_2 | t_3 = (11_2) | (10_2) = (11_2) = 3 = a_2 $ and $ t_2 \& t_3 = (11_2) \& (10_2) = (10_2) = 2 = b_2 $ ;
- $ t_3 | t_4 = (10_2) | (00_2) = (10_2) = 2 = a_3 $ and $ t_3 \& t_4 = (10_2) \& (00_2) = (00_2) = 0 = b_3 $ .

In the second example there is no such sequence.

## 样例 #1

### 输入

```
4
3 3 2
1 2 0

```

### 输出

```
YES
1 3 2 0 
```

## 样例 #2

### 输入

```
3
1 3
3 2

```

### 输出

```
NO
```



---

---
title: "Buying a TV Set"
layout: "post"
diff: 普及/提高-
pid: CF1041B
tag: ['枚举']
---

# Buying a TV Set

## 题目描述

### 题目大意：
给你$a,b,c,d$，求满足$\frac{x}{y}=\frac{c}{d},x\leq a,y\leq b$的$x,y$的对数

## 输入格式

一行$4$个整数$a,b,c,d$

## 输出格式

一个整数，表示满足条件的对数

## 样例 #1

### 输入

```
17 15 5 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
14 16 7 22

```

### 输出

```
0

```

## 样例 #3

### 输入

```
4 2 6 4

```

### 输出

```
1

```

## 样例 #4

### 输入

```
1000000000000000000 1000000000000000000 999999866000004473 999999822000007597

```

### 输出

```
1000000063

```



---

---
title: "Berland Fair"
layout: "post"
diff: 普及/提高-
pid: CF1073D
tag: ['模拟', '枚举']
---

# Berland Fair

## 题目描述

XXI Berland Annual Fair is coming really soon! Traditionally fair consists of $ n $ booths, arranged in a circle. The booths are numbered $ 1 $ through $ n $ clockwise with $ n $ being adjacent to $ 1 $ . The $ i $ -th booths sells some candies for the price of $ a_i $ burles per item. Each booth has an unlimited supply of candies.

Polycarp has decided to spend at most $ T $ burles at the fair. However, he has some plan in mind for his path across the booths:

- at first, he visits booth number $ 1 $ ;
- if he has enough burles to buy exactly one candy from the current booth, then he buys it immediately;
- then he proceeds to the next booth in the clockwise order (regardless of if he bought a candy or not).

Polycarp's money is finite, thus the process will end once he can no longer buy candy at any booth.

Calculate the number of candies Polycarp will buy.

## 输入格式

The first line contains two integers $ n $ and $ T $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le T \le 10^{18} $ ) — the number of booths at the fair and the initial amount of burles Polycarp has.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the price of the single candy at booth number $ i $ .

## 输出格式

Print a single integer — the total number of candies Polycarp will buy.

## 说明/提示

Let's consider the first example. Here are Polycarp's moves until he runs out of money:

1. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 33 $ ;
2. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 31 $ ;
3. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 26 $ ;
4. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 21 $ ;
5. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 19 $ ;
6. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 14 $ ;
7. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 9 $ ;
8. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 7 $ ;
9. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 2 $ ;
10. Booth $ 1 $ , buys no candy, not enough money;
11. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 0 $ .

No candy can be bought later. The total number of candies bought is $ 10 $ .

In the second example he has $ 1 $ burle left at the end of his path, no candy can be bought with this amount.

## 样例 #1

### 输入

```
3 38
5 2 5

```

### 输出

```
10

```

## 样例 #2

### 输入

```
5 21
2 4 100 2 6

```

### 输出

```
6

```



---

---
title: "Lost Numbers"
layout: "post"
diff: 普及/提高-
pid: CF1167B
tag: ['枚举']
---

# Lost Numbers

## 题目描述

This is an interactive problem. Remember to flush your output while communicating with the testing program. You may use fflush(stdout) in C++, system.out.flush() in Java, stdout.flush() in Python or flush(output) in Pascal to flush the output. If you use some other programming language, consult its documentation. You may also refer to the guide on interactive problems: <https://codeforces.com/blog/entry/45307>.

The jury guessed some array $ a $ consisting of $ 6 $ integers. There are $ 6 $ special numbers — $ 4 $ , $ 8 $ , $ 15 $ , $ 16 $ , $ 23 $ , $ 42 $ — and each of these numbers occurs in $ a $ exactly once (so, $ a $ is some permutation of these numbers).

You don't know anything about their order, but you are allowed to ask up to $ 4 $ queries. In each query, you may choose two indices $ i $ and $ j $ ( $ 1 \le i, j \le 6 $ , $ i $ and $ j $ are not necessarily distinct), and you will get the value of $ a_i \cdot a_j $ in return.

Can you guess the array $ a $ ?

The array $ a $ is fixed beforehand in each test, the interaction program doesn't try to adapt to your queries.

## 输出格式

Before submitting the answer, you may ask up to $ 4 $ queries. To ask a query, print one line in the following format: $ ? $ $ i $ $ j $ , where $ i $ and $ j $ should be two integers such that $ 1 \le i, j \le 6 $ . The line should be ended with a line break character. After submitting a query, flush the output and read the answer to your query — one line containing one integer $ a_i \cdot a_j $ . If you submit an incorrect query (or ask more than $ 4 $ queries), the answer to it will be one string 0. After receiving such an answer, your program should terminate immediately — otherwise you may receive verdict "Runtime error", "Time limit exceeded" or some other verdict instead of "Wrong answer".

To give the answer, your program should print one line $ ! $ $ a_1 $ $ a_2 $ $ a_3 $ $ a_4 $ $ a_5 $ $ a_6 $ with a line break in the end. After that, it should flush the output and terminate gracefully.

## 说明/提示

If you want to submit a hack for this problem, your test should contain exactly six space-separated integers $ a_1 $ , $ a_2 $ , ..., $ a_6 $ . Each of $ 6 $ special numbers should occur exactly once in the test. The test should be ended with a line break character.

## 样例 #1

### 输入

```
16
64
345
672
```

### 输出

```
? 1 1
? 2 2
? 3 5
? 4 6
! 4 8 15 16 23 42
```



---

---
title: "Required Length"
layout: "post"
diff: 普及/提高-
pid: CF1681D
tag: ['动态规划 DP', '枚举', '广度优先搜索 BFS']
---

# Required Length

## 题目描述

You are given two integer numbers, $ n $ and $ x $ . You may perform several operations with the integer $ x $ .

Each operation you perform is the following one: choose any digit $ y $ that occurs in the decimal representation of $ x $ at least once, and replace $ x $ by $ x \cdot y $ .

You want to make the length of decimal representation of $ x $ (without leading zeroes) equal to $ n $ . What is the minimum number of operations required to do that?

## 输入格式

The only line of the input contains two integers $ n $ and $ x $ ( $ 2 \le n \le 19 $ ; $ 1 \le x < 10^{n-1} $ ).

## 输出格式

Print one integer — the minimum number of operations required to make the length of decimal representation of $ x $ (without leading zeroes) equal to $ n $ , or $ -1 $ if it is impossible.

## 说明/提示

In the second example, the following sequence of operations achieves the goal:

1. multiply $ x $ by $ 2 $ , so $ x = 2 \cdot 2 = 4 $ ;
2. multiply $ x $ by $ 4 $ , so $ x = 4 \cdot 4 = 16 $ ;
3. multiply $ x $ by $ 6 $ , so $ x = 16 \cdot 6 = 96 $ ;
4. multiply $ x $ by $ 9 $ , so $ x = 96 \cdot 9 = 864 $ .

## 样例 #1

### 输入

```
2 1
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
4
```

## 样例 #3

### 输入

```
13 42
```

### 输出

```
12
```



---

---
title: "Diverse Substrings"
layout: "post"
diff: 普及/提高-
pid: CF1748B
tag: ['枚举']
---

# Diverse Substrings

## 题目描述

A non-empty digit string is diverse if the number of occurrences of each character in it doesn't exceed the number of distinct characters in it.

For example:

- string "7" is diverse because 7 appears in it $ 1 $ time and the number of distinct characters in it is $ 1 $ ;
- string "77" is not diverse because 7 appears in it $ 2 $ times and the number of distinct characters in it is $ 1 $ ;
- string "1010" is diverse because both 0 and 1 appear in it $ 2 $ times and the number of distinct characters in it is $ 2 $ ;
- string "6668" is not diverse because 6 appears in it $ 3 $ times and the number of distinct characters in it is $ 2 $ .

You are given a string $ s $ of length $ n $ , consisting of only digits $ 0 $ to $ 9 $ . Find how many of its $ \frac{n(n+1)}{2} $ substrings are diverse.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

Note that if the same diverse string appears in $ s $ multiple times, each occurrence should be counted independently. For example, there are two diverse substrings in "77" both equal to "7", so the answer for the string "77" is $ 2 $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the string $ s $ .

The second line of each test case contains a string $ s $ of length $ n $ . It is guaranteed that all characters of $ s $ are digits from $ 0 $ to $ 9 $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case print one integer — the number of diverse substrings of the given string $ s $ .

## 说明/提示

In the first test case, the diverse substring is "7".

In the second test case, the only diverse substring is "7", which appears twice, so the answer is $ 2 $ .

In the third test case, the diverse substrings are "0" ( $ 2 $ times), "01", "010", "1" ( $ 2 $ times), "10" ( $ 2 $ times), "101" and "1010".

In the fourth test case, the diverse substrings are "0" ( $ 3 $ times), "01", "011", "0110", "1" ( $ 2 $ times), "10", "100", "110" and "1100".

In the fifth test case, the diverse substrings are "3", "39", "399", "6", "9" ( $ 4 $ times), "96" and "996".

In the sixth test case, all $ 15 $ non-empty substrings of "23456" are diverse.

## 样例 #1

### 输入

```
7
1
7
2
77
4
1010
5
01100
6
399996
5
23456
18
789987887987998798
```

### 输出

```
1
2
10
12
10
15
106
```



---

---
title: "Stripe"
layout: "post"
diff: 普及/提高-
pid: CF18C
tag: ['模拟', '枚举', '前缀和']
---

# Stripe

## 题目描述

Once Bob took a paper stripe of $ n $ squares (the height of the stripe is 1 square). In each square he wrote an integer number, possibly negative. He became interested in how many ways exist to cut this stripe into two pieces so that the sum of numbers from one piece is equal to the sum of numbers from the other piece, and each piece contains positive integer amount of squares. Would you help Bob solve this problem?

## 输入格式

The first input line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — amount of squares in the stripe. The second line contains $ n $ space-separated numbers — they are the numbers written in the squares of the stripe. These numbers are integer and do not exceed 10000 in absolute value.

## 输出格式

Output the amount of ways to cut the stripe into two non-empty pieces so that the sum of numbers from one piece is equal to the sum of numbers from the other piece. Don't forget that it's allowed to cut the stripe along the squares' borders only.

## 样例 #1

### 输入

```
9
1 5 -6 7 9 -16 0 -2 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
1 1 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
2
0 0

```

### 输出

```
1

```



---

---
title: "Three Activities"
layout: "post"
diff: 普及/提高-
pid: CF1914D
tag: ['枚举']
---

# Three Activities

## 题目描述

Winter holidays are coming up. They are going to last for $ n $ days.

During the holidays, Monocarp wants to try all of these activities exactly once with his friends:

- go skiing;
- watch a movie in a cinema;
- play board games.

Monocarp knows that, on the $ i $ -th day, exactly $ a_i $ friends will join him for skiing, $ b_i $ friends will join him for a movie and $ c_i $ friends will join him for board games.

Monocarp also knows that he can't try more than one activity in a single day.

Thus, he asks you to help him choose three distinct days $ x, y, z $ in such a way that the total number of friends to join him for the activities ( $ a_x + b_y + c_z $ ) is maximized.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains a single integer $ n $ ( $ 3 \le n \le 10^5 $ ) — the duration of the winter holidays in days.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^8 $ ) — the number of friends that will join Monocarp for skiing on the $ i $ -th day.

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le 10^8 $ ) — the number of friends that will join Monocarp for a movie on the $ i $ -th day.

The fourth line contains $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le 10^8 $ ) — the number of friends that will join Monocarp for board games on the $ i $ -th day.

The sum of $ n $ over all testcases doesn't exceed $ 10^5 $ .

## 输出格式

For each testcase, print a single integer — the maximum total number of friends that can join Monocarp for the activities on three distinct days.

## 说明/提示

In the first testcase, Monocarp can choose day $ 2 $ for skiing, day $ 1 $ for a movie and day $ 3 $ for board games. This way, $ a_2 = 10 $ friends will join him for skiing, $ b_1 = 10 $ friends will join him for a movie and $ c_3 = 10 $ friends will join him for board games. The total number of friends is $ 30 $ .

In the second testcase, Monocarp can choose day $ 1 $ for skiing, day $ 4 $ for a movie and day $ 2 $ for board games. $ 30 + 20 + 25 = 75 $ friends in total. Note that Monocarp can't choose day $ 1 $ for all activities, because he can't try more than one activity in a single day.

In the third testcase, Monocarp can choose day $ 2 $ for skiing, day $ 3 $ for a movie and day $ 7 $ for board games. $ 19 + 19 + 17 = 55 $ friends in total.

In the fourth testcase, Monocarp can choose day $ 1 $ for skiing, day $ 4 $ for a movie and day $ 9 $ for board games. $ 17 + 19 + 20 = 56 $ friends in total.

## 样例 #1

### 输入

```
4
3
1 10 1
10 1 1
1 1 10
4
30 20 10 1
30 5 15 20
30 25 10 10
10
5 19 12 3 18 18 6 17 10 13
15 17 19 11 16 3 11 17 17 17
1 17 18 10 15 8 17 3 13 12
10
17 5 4 18 12 4 11 2 16 16
8 4 14 19 3 12 6 7 5 16
3 4 8 11 10 8 10 2 20 3
```

### 输出

```
30
75
55
56
```



---

---
title: "Partitioning the Array"
layout: "post"
diff: 普及/提高-
pid: CF1920C
tag: ['枚举', '最大公约数 gcd']
---

# Partitioning the Array

## 题目描述

Allen has an array $ a_1, a_2,\ldots,a_n $ . For every positive integer $ k $ that is a divisor of $ n $ , Allen does the following:

- He partitions the array into $ \frac{n}{k} $ disjoint subarrays of length $ k $ . In other words, he partitions the array into the following subarrays: $ $$$[a_1,a_2,\ldots,a_k],[a_{k+1}, a_{k+2},\ldots,a_{2k}],\ldots,[a_{n-k+1},a_{n-k+2},\ldots,a_{n}] $ $  </li><li> Allen earns one point if there exists some positive integer  $ m $  ( $ m \\geq 2 $ ) such that if he replaces every element in the array with its remainder when divided by  $ m$$$, then all subarrays will be identical.

Help Allen find the number of points he will earn.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2\cdot10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2,\ldots, a_n $ ( $ 1 \leq a_i \leq n $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of points Allen will earn.

## 说明/提示

In the first test case, $ k=2 $ earns a point since Allen can pick $ m = 2 $ and both subarrays will be equal to $ [1, 0] $ . $ k=4 $ also earns a point, since no matter what $ m $ Allen chooses, there will be only one subarray and thus all subarrays are equal.

In the second test case, Allen earns $ 1 $ point for $ k=3 $ , where his choice for $ m $ does not matter.

## 样例 #1

### 输入

```
8
4
1 2 1 4
3
1 2 3
5
1 1 1 1 1
6
1 3 1 1 3 1
6
6 2 6 2 2 2
6
2 6 3 6 6 6
10
1 7 5 1 4 3 1 3 1 4
1
1
```

### 输出

```
2
1
2
4
4
1
2
1
```



---

---
title: "Fun"
layout: "post"
diff: 普及/提高-
pid: CF1996D
tag: ['枚举']
---

# Fun

## 题目描述

Counting is Fun!

— satyam343



Given two integers $ n $ and $ x $ , find the number of triplets ( $ a,b,c $ ) of positive integers such that $ ab + ac + bc \le n $ and $ a + b + c \le x $ .

Note that order matters (e.g. ( $ 1, 1, 2 $ ) and ( $ 1, 2, 1 $ ) are treated as different) and $ a $ , $ b $ , $ c $ must be strictly greater than $ 0 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

Each test case contains two integers $ n $ and $ x $ ( $ 1 \leq n,x \leq 10^6 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ and that the sum of $ x $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

Output a single integer — the number of triplets ( $ a,b,c $ ) of positive integers such that $ ab + ac + bc \le n $ and $ a + b + c \le x $ .

## 说明/提示

In the first test case, the triplets are ( $ 1, 1, 1 $ ), ( $ 1, 1, 2 $ ), ( $ 1, 2, 1 $ ), and ( $ 2, 1, 1 $ ).

In the second test case, the triplets are ( $ 1, 1, 1 $ ), ( $ 1, 1, 2 $ ), ( $ 1, 1, 3 $ ), ( $ 1, 2, 1 $ ), ( $ 1, 2, 2 $ ), ( $ 1, 3, 1 $ ), ( $ 2, 1, 1 $ ), ( $ 2, 1, 2 $ ), ( $ 2, 2, 1 $ ), and ( $ 3, 1, 1 $ ).

## 样例 #1

### 输入

```
4
7 4
10 5
7 1000
900000 400000
```

### 输出

```
4
10
7
1768016938
```



---

---
title: "Devyatkino"
layout: "post"
diff: 普及/提高-
pid: CF2067C
tag: ['数学', '枚举']
---

# Devyatkino

## 题目描述

You are given a positive integer $ n $ . In one operation, you can add to $ n $ any positive integer whose decimal representation contains only the digit $ 9 $ , possibly repeated several times.

What is the minimum number of operations needed to make the number $ n $ contain at least one digit $ 7 $ in its decimal representation?

For example, if $ n = 80 $ , it is sufficient to perform one operation: you can add $ 99 $ to $ n $ , after the operation $ n = 179 $ , which contains the digit $ 7 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The only line of each test case contains an integer $ n $ ( $ 10 \leq n \leq 10^9 $ ).

## 输出格式

For each test case, output the minimum number of operations required for the number $ n $ to contain the digit $ 7 $ .

## 说明/提示

In the first test case, three operations are sufficient: $ 51 + 9 + 9 + 9 = 78 $ , which contains the digit $ 7 $ . It can be shown that it is impossible to achieve the goal in one or two operations.

In the second test case, two operations are sufficient: $ 60 + 9 + 9 = 78 $ .

In the third test case, one operation is sufficient: $ 61 + 9 = 70 $ .

In the fourth test case, $ n $ already contains the digit $ 7 $ , so no operations are required.

In the fifth test case, you can add $ 99 $ to $ n $ to obtain a number containing the digit $ 7 $ .

## 样例 #1

### 输入

```
16
51
60
61
777
12345689
1000000000
2002
3001
977
989898986
80
800001
96
70
15
90
```

### 输出

```
3
2
1
0
1
3
5
4
0
7
1
2
7
0
7
3
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
title: "Counting Points"
layout: "post"
diff: 普及/提高-
pid: CF2074D
tag: ['数学', '枚举']
---

# Counting Points

## 题目描述

粉色士兵们在平面上绘制了 $n$ 个圆心位于 $x$ 轴上的圆。此外，他们告知这些圆的半径之和恰好为 $m$ $^{\text{∗}}$。

请计算至少位于一个圆内或边界上的整数点数量。形式化地说，问题定义如下：

给定一个整数序列 $x_1, x_2, \ldots, x_n$ 和一个正整数序列 $r_1, r_2, \ldots, r_n$，已知 $\sum_{i=1}^n r_i = m$。

你需要统计满足以下条件的整数对 $(x, y)$ 的数量：

- 存在一个下标 $i$ 使得 $(x - x_i)^2 + y^2 \le r_i^2$（$1 \le i \le n$）。

$^{\text{∗}}$ 这个信息真的有用吗？别问我，其实我也不知道。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$1 \le n \le m \le 2 \cdot 10^5$）。

每个测试用例的第二行包含 $x_1, x_2, \ldots, x_n$ —— 圆的圆心坐标（$-10^9 \le x_i \le 10^9$）。

每个测试用例的第三行包含 $r_1, r_2, \ldots, r_n$ —— 圆的半径（$1 \le r_i$，$\sum_{i=1}^n r_i = m$）。

保证所有测试用例的 $m$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，在单独一行中输出满足条件的整数点数量。

## 说明/提示

在第一个测试用例中，半径为 $r_1=1$ 的圆完全包含在半径为 $r_2=2$ 的圆内部。因此只需统计后者内部的整数点数量。满足 $x^2 + y^2 \le 2^2$ 的整数点共有 $13$ 个，因此答案为 $13$。

在第二个测试用例中，半径为 $r_1=1$ 的圆未完全包含在半径为 $r_2=2$ 的圆内部。存在 $3$ 个额外整数点位于第一个圆内但不在第二个圆内，因此答案为 $3+13=16$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
2 3
0 0
1 2
2 3
0 2
1 2
3 3
0 2 5
1 1 1
4 8
0 5 10 15
2 2 2 2
```

### 输出

```
13
16
14
52
```



---

---
title: "Dubstep"
layout: "post"
diff: 普及/提高-
pid: CF208A
tag: ['模拟', '字符串', '枚举']
---

# Dubstep

## 题目描述

## 题目翻译
Vasya有一句歌词(可能含有空格)，他在第一个单词之前和最后一个单词之后加上若干(可以为0)个"WUB",再每个单词之间加上若干(至少为1)个"WUB"，转变成一个新的字符串(无空格)
如"I AM X" 可以变成 "WUBWUBIWUBAMWUBWUBX" 而不能变成 "WUBWUBIAMWUBX"
现在给出转变后的字符串，求出原来的字符串

## 输入格式

输入包括一个非空字符串SSS，其中SSS仅由大写字母组成并且的长度不超过200
保证原来的字符串不含有"WUB"并且至少有一个单词

## 输出格式

输出转变前的字符串，每个单词用空格分隔

## 样例 #1

### 输入

```
WUBWUBABCWUB

```

### 输出

```
ABC 
```

## 样例 #2

### 输入

```
WUBWEWUBAREWUBWUBTHEWUBCHAMPIONSWUBMYWUBFRIENDWUB

```

### 输出

```
WE ARE THE CHAMPIONS MY FRIEND 
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
title: "T-primes"
layout: "post"
diff: 普及/提高-
pid: CF230B
tag: ['数学', '枚举', '素数判断,质数,筛法']
---

# T-primes

## 题目描述

我们知道质数是只有两个不同的正数因数的正整数。相似的，我们把一个正整数 _t_ 叫做 T质数，如果 _t_ 恰好有三个不同的正整数因数。 

你被给了一个含有 _n_ 个正整数的数组。你要给其中所有的数判断它是否是 T质数。

## 输入格式

第一行只有一个正整数， _n_ （1<= _n_ <=10⁵）,代表数组里有几个数字。下一行包含了 _n_ 个被空格分开了的整数 _Xᵢ_ （1<=Xᵢ<=10¹²)。

请勿在C++中使用 %lld 用来读写64位整数。建议使用cin、cout流或 %I64d。

## 输出格式

输出 _n_ 行：如果第 _i_ 行的数 _Xᵢ_ 是T质数，则输出YES，否则输出NO。

## 说明/提示

给定样例有三个数。第一个数4恰好有三个因数--1、2和4，因此对这个数字输出YES。第二个数5有两个因数（1和5），第三个数6有四个因数（1、2、3和6），因此这两个数的答案是NO。

## 样例 #1

### 输入

```
3
4 5 6

```

### 输出

```
YES
NO
NO

```



---

---
title: "Flipping Game"
layout: "post"
diff: 普及/提高-
pid: CF327A
tag: ['模拟', '枚举']
---

# Flipping Game

## 题目描述

Iahub got bored, so he invented a game to be played on paper.

He writes $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Each of those integers can be either 0 or 1. He's allowed to do exactly one move: he chooses two indices $ i $ and $ j $ ( $ 1<=i<=j<=n $ ) and flips all values $ a_{k} $ for which their positions are in range $ [i,j] $ (that is $ i<=k<=j $ ). Flip the value of $ x $ means to apply operation $ x=1 $ - $ x $ .

The goal of the game is that after exactly one move to obtain the maximum number of ones. Write a program to solve the little game of Iahub.

## 输入格式

The first line of the input contains an integer $ n $ ( $ 1<=n<=100 $ ). In the second line of the input there are $ n $ integers: $ a_{1},a_{2},...,a_{n} $ . It is guaranteed that each of those $ n $ values is either 0 or 1.

## 输出格式

Print an integer — the maximal number of 1s that can be obtained after exactly one move.

## 说明/提示

In the first case, flip the segment from 2 to 5 $ (i=2,j=5) $ . That flip changes the sequence, it becomes: \[1 1 1 0 1\]. So, it contains four ones. There is no way to make the whole sequence equal to \[1 1 1 1 1\].

In the second case, flipping only the second and the third element $ (i=2,j=3) $ will turn all numbers into 1.

## 样例 #1

### 输入

```
5
1 0 0 1 0

```

### 输出

```
4

```

## 样例 #2

### 输入

```
4
1 0 0 1

```

### 输出

```
4

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
title: "Tic-tac-toe"
layout: "post"
diff: 普及/提高-
pid: CF3C
tag: ['模拟', '枚举', '概率论']
---

# Tic-tac-toe

## 题目描述

Certainly, everyone is familiar with tic-tac-toe game. The rules are very simple indeed. Two players take turns marking the cells in a $ 3×3 $ grid (one player always draws crosses, the other — noughts). The player who succeeds first in placing three of his marks in a horizontal, vertical or diagonal line wins, and the game is finished. The player who draws crosses goes first. If the grid is filled, but neither Xs, nor 0s form the required line, a draw is announced.

You are given a $ 3×3 $ grid, each grid cell is empty, or occupied by a cross or a nought. You have to find the player (first or second), whose turn is next, or print one of the verdicts below:

- illegal — if the given board layout can't appear during a valid game;
- the first player won — if in the given board layout the first player has just won;
- the second player won — if in the given board layout the second player has just won;
- draw — if the given board layout has just let to a draw.

## 输入格式

The input consists of three lines, each of the lines contains characters ".", "X" or "0" (a period, a capital letter X, or a digit zero).

## 输出格式

Print one of the six verdicts: first, second, illegal, the first player won, the second player won or draw.

## 样例 #1

### 输入

```
X0X
.0.
.X.

```

### 输出

```
second

```



---

---
title: "Elimination"
layout: "post"
diff: 普及/提高-
pid: CF417A
tag: ['枚举', '背包 DP']
---

# Elimination

## 题目描述

The finalists of the "Russian Code Cup" competition in 2214 will be the participants who win in one of the elimination rounds.

The elimination rounds are divided into main and additional. Each of the main elimination rounds consists of $ c $ problems, the winners of the round are the first $ n $ people in the rating list. Each of the additional elimination rounds consists of $ d $ problems. The winner of the additional round is one person. Besides, $ k $ winners of the past finals are invited to the finals without elimination.

As a result of all elimination rounds at least $ n·m $ people should go to the finals. You need to organize elimination rounds in such a way, that at least $ n·m $ people go to the finals, and the total amount of used problems in all rounds is as small as possible.

## 输入格式

The first line contains two integers $ c $ and $ d $ ( $ 1<=c,d<=100 $ ) — the number of problems in the main and additional rounds, correspondingly. The second line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=100 $ ). Finally, the third line contains an integer $ k $ ( $ 1<=k<=100 $ ) — the number of the pre-chosen winners.

## 输出格式

In the first line, print a single integer — the minimum number of problems the jury needs to prepare.

## 样例 #1

### 输入

```
1 10
7 2
1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 2
2 1
2

```

### 输出

```
0

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
title: "Guilty — to the kitchen!"
layout: "post"
diff: 普及/提高-
pid: CF42A
tag: ['枚举']
---

# Guilty — to the kitchen!

## 题目描述

今天对Volodya来说是十分不幸的一天。他的代数考试挂掉了，并且不得不在厨房里干活，即做罗宋汤（一种传统的俄罗斯汤）。通过这样也能提高他的代数水平。

根据罗宋汤的配方,罗宋汤由$n$部分组成，并且它们必须按比例（$a_1:a_2:\ldots:a_n$）混合（因此，对于一个非负的$x$，它们为$a_1*x,a_2*x,\ldots,a_n*x$升），在厨房里 Volodya发现每种配料他相应的有$b_1,b_2,\ldots,b_n$升供他使用。为了纠正他在代数上的错误，他决定用一个容量为$V$升的锅尽可能的多做汤（这意味着这它能够做$0$到$V$升的汤）。Volodya最多能做多少汤？

## 输入格式

第一行包含两个用空格分开的整数$n$和$V$（$1\leq n\leq20,1\leq V\leq10000$）。下一行包含$n$个用空格分开的整数$a_i$（$1\leq a_i\leq100$）。
最后一行包含$n$个空格分开的整数$b_i$（$0\leq b_i\leq100$）

## 输出格式

你的程序应当仅仅输出一个实数 — Volodya最多能做的汤的体积。你的答案必须和标准答案相差不超过$10^{-4}$
Translated by @Khassar

## 样例 #1

### 输入

```
1 100
1
40

```

### 输出

```
40.0

```

## 样例 #2

### 输入

```
2 100
1 1
25 30

```

### 输出

```
50.0

```

## 样例 #3

### 输入

```
2 100
1 1
60 60

```

### 输出

```
100.0

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
title: "Number of Ways"
layout: "post"
diff: 普及/提高-
pid: CF466C
tag: ['枚举', '前缀和']
---

# Number of Ways

## 题目描述

You've got array $ a[1],a[2],...,a[n] $ , consisting of $ n $ integers. Count the number of ways to split all the elements of the array into three contiguous parts so that the sum of elements in each part is the same.

More formally, you need to find the number of such pairs of indices $ i,j $ $ (2<=i<=j<=n-1) $ , that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF466C/6d268bd0e5773093a8b59275245964aa2b1c55f9.png).

## 输入格式

The first line contains integer $ n $ $ (1<=n<=5·10^{5}) $ , showing how many numbers are in the array. The second line contains $ n $ integers $ a[1] $ , $ a[2] $ , ..., $ a[n] $ $ (|a[i]|<=10^{9}) $ — the elements of array $ a $ .

## 输出格式

Print a single integer — the number of ways to split the array into three parts with the same sum.

## 样例 #1

### 输入

```
5
1 2 3 0 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4
0 1 -1 0

```

### 输出

```
1

```

## 样例 #3

### 输入

```
2
4 1

```

### 输出

```
0

```



---

---
title: "Smallest number"
layout: "post"
diff: 普及/提高-
pid: CF55B
tag: ['搜索', '枚举', '深度优先搜索 DFS']
---

# Smallest number

## 题目描述

Recently, Vladimir got bad mark in algebra again. To avoid such unpleasant events in future he decided to train his arithmetic skills. He wrote four integer numbers $ a $ , $ b $ , $ c $ , $ d $ on the blackboard. During each of the next three minutes he took two numbers from the blackboard (not necessarily adjacent) and replaced them with their sum or their product. In the end he got one number. Unfortunately, due to the awful memory he forgot that number, but he remembers four original numbers, sequence of the operations and his surprise because of the very small result. Help Vladimir remember the forgotten number: find the smallest number that can be obtained from the original numbers by the given sequence of operations.

## 输入格式

First line contains four integers separated by space: $ 0<=a,b,c,d<=1000 $ — the original numbers. Second line contains three signs ('+' or '\*' each) separated by space — the sequence of the operations in the order of performing. ('+' stands for addition, '\*' — multiplication)

## 输出格式

Output one integer number — the minimal result which can be obtained.

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cin (also you may use %I64d).

## 样例 #1

### 输入

```
1 1 1 1
+ + *

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2 2 2 2
* * +

```

### 输出

```
8

```

## 样例 #3

### 输入

```
1 2 3 4
* + +

```

### 输出

```
9

```



---

---
title: "Rebranding"
layout: "post"
diff: 普及/提高-
pid: CF591B
tag: ['模拟', '枚举']
---

# Rebranding

## 题目描述

The name of one small but proud corporation consists of $ n $ lowercase English letters. The Corporation has decided to try rebranding — an active marketing strategy, that includes a set of measures to change either the brand (both for the company and the goods it produces) or its components: the name, the logo, the slogan. They decided to start with the name.

For this purpose the corporation has consecutively hired $ m $ designers. Once a company hires the $ i $ -th designer, he immediately contributes to the creation of a new corporation name as follows: he takes the newest version of the name and replaces all the letters $ x_{i} $ by $ y_{i} $ , and all the letters $ y_{i} $ by $ x_{i} $ . This results in the new version. It is possible that some of these letters do no occur in the string. It may also happen that $ x_{i} $ coincides with $ y_{i} $ . The version of the name received after the work of the last designer becomes the new name of the corporation.

Manager Arkady has recently got a job in this company, but is already soaked in the spirit of teamwork and is very worried about the success of the rebranding. Naturally, he can't wait to find out what is the new name the Corporation will receive.

Satisfy Arkady's curiosity and tell him the final version of the name.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=200000 $ ) — the length of the initial name and the number of designers hired, respectively.

The second line consists of $ n $ lowercase English letters and represents the original name of the corporation.

Next $ m $ lines contain the descriptions of the designers' actions: the $ i $ -th of them contains two space-separated lowercase English letters $ x_{i} $ and $ y_{i} $ .

## 输出格式

Print the new name of the corporation.

## 说明/提示

In the second sample the name of the corporation consecutively changes as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b0c9599f7e4282de011e545b3b2138ce054cf709.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b503b89dff83c09912a9706615e9f382f03f5909.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e277cc6136141b35244d23f5857e2b4088822639.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/cfe2461ca78ee24244102008b38c52289020e201.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/c06bdcdcec7417c4f543399c6c3d126f67ecf0a6.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e46b37134536ad3b6c864840e66c2932fc25c838.png)

## 样例 #1

### 输入

```
6 1
police
p m

```

### 输出

```
molice

```

## 样例 #2

### 输入

```
11 6
abacabadaba
a b
b c
a d
e g
f a
b b

```

### 输出

```
cdcbcdcfcdc

```



---

---
title: "Bash's Big Day"
layout: "post"
diff: 普及/提高-
pid: CF757B
tag: ['枚举', '素数判断,质数,筛法', '概率论']
---

# Bash's Big Day

## 题目描述

Bash 已经踏上了成为最伟大的口袋妖怪大师的旅程。为了得到他的第一个口袋妖怪，他去了 Zulu 教授的实验室。由于 Bash 是 Zulu 教授最喜欢的学生，Zulu 允许他从实验室里取出任意数量的口袋妖怪。

但是 Zulu 警告他，每个小精灵都有一个力量值，例如 $k(k>1)$ 个小精灵在一起，它们的力量值为 $s_1,s_2,\dots,s_k$，如果 $\gcd(s_1,s_2,\dots s_k)=1$（见 $\gcd$ 的定义注释），它们之间就会互相打架。

Bash 作为一个聪明的人，不希望他的口袋妖怪互相斗争。然而，他也想最大化他从实验室里带走的神奇宝贝的数量。你能帮 Bash 找出他能带走的最大数量的口袋妖怪吗？

**注意：口袋妖怪不能与自己战斗。**

## 输入格式

输入包含两行。

第一行一个整数 $n(1\le n \le 10^5)$，表示实验室中的小精灵总数。

第二行 $n$ 个用空格隔开的整数，第 $i$ 个整数代表第 $i$ 个小精灵的力量值 $s_i(1 \le s_i \le 10^5)$。

## 输出格式

一行包含一个整数，表示能拿走的小精灵数量最大值。

## 样例 #1

### 输入

```
3
2 3 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
2 3 4 6 7

```

### 输出

```
3

```



---

---
title: "Modified GCD"
layout: "post"
diff: 普及/提高-
pid: CF75C
tag: ['数学', '枚举', '最大公约数 gcd']
---

# Modified GCD

## 题目描述

Well, here is another math class task. In mathematics, GCD is the greatest common divisor, and it's an easy task to calculate the GCD between two positive integers.

A common divisor for two positive numbers is a number which both numbers are divisible by.

But your teacher wants to give you a harder task, in this task you have to find the greatest common divisor $ d $ between two integers $ a $ and $ b $ that is in a given range from $ low $ to $ high $ (inclusive), i.e. $ low<=d<=high $ . It is possible that there is no common divisor in the given range.

You will be given the two integers $ a $ and $ b $ , then $ n $ queries. Each query is a range from $ low $ to $ high $ and you have to answer each query.

## 输入格式

The first line contains two integers $ a $ and $ b $ , the two integers as described above ( $ 1<=a,b<=10^{9} $ ). The second line contains one integer $ n $ , the number of queries ( $ 1<=n<=10^{4} $ ). Then $ n $ lines follow, each line contains one query consisting of two integers, $ low $ and $ high $ ( $ 1<=low<=high<=10^{9} $ ).

## 输出格式

Print $ n $ lines. The $ i $ -th of them should contain the result of the $ i $ -th query in the input. If there is no common divisor in the given range for any query, you should print -1 as a result for this query.

## 样例 #1

### 输入

```
9 27
3
1 5
10 11
9 11

```

### 输出

```
3
-1
9

```



---

---
title: "Dasha and friends"
layout: "post"
diff: 普及/提高-
pid: CF761B
tag: ['字符串', '枚举']
---

# Dasha and friends

## 题目描述

小A和小B参加障碍跑，跑道可能有多个，所有跑道是环形的，按逆时针方向跑，长度都是是L，都有n个障碍。 小A从起点A开始跑，沿途记录下经过的障碍物离开起点A的距离，如2,4,6；小B从起点B开始跑，沿途记录下经过的障碍物离开起点B的距离，如1,5,7。距离均为整数。 现在请你判断，小A和小B的使用的是否是同一个跑道。

## 输入格式

第一行，两个整数n和L (1 ≤ n ≤ 50, n ≤ L ≤ 100)，分别表示障碍物的数量和跑道的长度。 第二行，n个升序的整数，表示小A记录的障碍物离起点的距离，范围为0到L-1。 第三行，n个升序的整数，表示小B记录的障碍物离起点的距离，范围为0到L-1。

## 输出格式

输出一个字符串，“YES”表示跑道相同，“NO”表示跑道不同。

## 输入输出样例

### 输入 #1

```

3 8

2 4 6

1 5 7

```

### 输出 #1

```

YES

```

### 输入 #2

```

4 9

2 3 5 8

0 1 3 6

```

### 输出 #2

```

YES

```

### 输入 #3

```

2 4

1 3

1 2

```

### 输出 #3

```

NO

```

## 样例 #1

### 输入

```
3 8
2 4 6
1 5 7

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4 9
2 3 5 8
0 1 3 6

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
2 4
1 3
1 2

```

### 输出

```
NO

```



---

---
title: "k-th divisor"
layout: "post"
diff: 普及/提高-
pid: CF762A
tag: ['枚举']
---

# k-th divisor

## 题目描述

你被给了两个整数$n$ 和$k$ 。找到$n$ 的第$k$ 小因子，或者告知其不存在。

任意一个可以除$n$ 而没有余数的自然数都是$n$ 的因子。

## 输入格式

第一行包含两个整数$n$ 和$k$ （$1\leq n\leq 10^{15}$ ，$1\leq k\leq 10^9$ ）

## 输出格式

如果$n$ 不足$k$ 个因子输出-1。

否则输出$n$ 的第$k$ 小的因子。

## 说明/提示

在第一个样例中，数字$4$ 有三个因子：$1$ ，$2$ 和$4$ 。第二小的为$2$ 。

在第二个样例中，数字$5$ 仅有两个因子$1$ 和$5$ 。第三个因子是不存在的，因此答案是-1。

感谢@Khassar 提供的翻译

## 样例 #1

### 输入

```
4 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 3

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
12 5

```

### 输出

```
6

```



---

---
title: "Sherlock and his girlfriend"
layout: "post"
diff: 普及/提高-
pid: CF776B
tag: ['枚举', '素数判断,质数,筛法']
---

# Sherlock and his girlfriend

## 题目描述

Sherlock 有一个新女朋友。现在情人节就要到了，他想送给她一些珠宝。 

他买了几件首饰。第 $i$ 件的价格等于 $i+ 1$，也就是说，珠宝的价格分别为 $2,3,4,n + 1$ 。

现在需要给这些珠宝首饰上色。**当一件珠宝的价格是另一件珠宝的价格的素因子时，这两件的颜色就不允许相同。** 此外，要最少化使用的颜色数量。

## 输入格式

一行，包含单个整数 $n(1\le n\leq 100000)$ 指珠宝的数量。

## 输出格式

第一行的输出包含一个整数 $K$，指最少颜色的颜色种类数。

第二行由 $n$ 个整数（$1$ 到 $k$）组成，按价格从小到大来表示每件珠宝的颜色。

如果有多种方法，则可以输出它们中的任何一种。

## 说明/提示

在第一个样例中，第一、第二和第三件首饰的价格分别为 $2$、$3$、$4$,它们的颜色分别为 $1$ 、$1$ 和 $2$。

在这种情况下，由于 $2$ 是 $4$ 的因子，所以具有因数 $2$ 和 $4$ 的珠宝的颜色必须是不同的。

Translated by @皎月半洒花。

## 样例 #1

### 输入

```
3

```

### 输出

```
2
1 1 2 
```

## 样例 #2

### 输入

```
4

```

### 输出

```
2
2 1 1 2

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

---
title: "Chtholly's request"
layout: "post"
diff: 普及/提高-
pid: CF897B
tag: ['枚举', '构造']
---

# Chtholly's request

## 题目描述

 — Thanks a lot for today.— I experienced so many great things.

— You gave me memories like dreams... But I have to leave now...

— One last request, can you...

— Help me solve a Codeforces problem?

— ......

— What?





Chtholly has been thinking about a problem for days:

If a number is palindrome and length of its decimal representation without leading zeros is even, we call it a zcy number. A number is palindrome means when written in decimal representation, it contains no leading zeros and reads the same forwards and backwards. For example 12321 and 1221 are palindromes and 123 and 12451 are not. Moreover, 1221 is zcy number and 12321 is not.

Given integers $ k $ and $ p $ , calculate the sum of the $ k $ smallest zcy numbers and output this sum modulo $ p $ .

Unfortunately, Willem isn't good at solving this kind of problems, so he asks you for help!

## 输入格式

The first line contains two integers $ k $ and $ p $ $ (1<=k<=10^{5},1<=p<=10^{9}) $ .

## 输出格式

Output single integer — answer to the problem.

## 说明/提示

In the first example, the smallest zcy number is $ 11 $ , and the second smallest zcy number is $ 22 $ .

In the second example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF897B/8301f23cf6a6ac38a43acd044c106b422734f787.png).

## 样例 #1

### 输入

```
2 100

```

### 输出

```
33

```

## 样例 #2

### 输入

```
5 30

```

### 输出

```
15

```



---

---
title: "The Monster"
layout: "post"
diff: 普及/提高-
pid: CF917A
tag: ['枚举']
---

# The Monster

## 题目描述

As Will is stuck in the Upside Down, he can still communicate with his mom, Joyce, through the Christmas lights (he can turn them on and off with his mind). He can't directly tell his mom where he is, because the monster that took him to the Upside Down will know and relocate him.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917A/4c119b489e29bab2fd3dc778221019b04c8209ba.png)Thus, he came up with a puzzle to tell his mom his coordinates. His coordinates are the answer to the following problem.

A string consisting only of parentheses ('(' and ')') is called a bracket sequence. Some bracket sequence are called correct bracket sequences. More formally:

- Empty string is a correct bracket sequence.
- if $ s $ is a correct bracket sequence, then $ (s) $ is also a correct bracket sequence.
- if $ s $ and $ t $ are correct bracket sequences, then $ st $ (concatenation of $ s $ and $ t $ ) is also a correct bracket sequence.

A string consisting of parentheses and question marks ('?') is called pretty if and only if there's a way to replace each question mark with either '(' or ')' such that the resulting string is a non-empty correct bracket sequence.

Will gave his mom a string $ s $ consisting of parentheses and question marks (using Morse code through the lights) and his coordinates are the number of pairs of integers $ (l,r) $ such that $ 1<=l<=r<=|s| $ and the string $ s_{l}s_{l+1}...\ s_{r} $ is pretty, where $ s_{i} $ is $ i $ -th character of $ s $ .

Joyce doesn't know anything about bracket sequences, so she asked for your help.

## 输入格式

The first and only line of input contains string $ s $ , consisting only of characters '(', ')' and '?' ( $ 2<=|s|<=5000 $ ).

## 输出格式

Print the answer to Will's puzzle in the first and only line of output.

## 说明/提示

For the first sample testcase, the pretty substrings of $ s $ are:

1. "(?" which can be transformed to "()".
2. "?)" which can be transformed to "()".
3. "((?)" which can be transformed to "(())".
4. "(?))" which can be transformed to "(())".

For the second sample testcase, the pretty substrings of $ s $ are:

1. "??" which can be transformed to "()".
2. "()".
3. "??()" which can be transformed to "()()".
4. "?()?" which can be transformed to "(())".
5. "??" which can be transformed to "()".
6. "()??" which can be transformed to "()()".
7. "??()??" which can be transformed to "()()()".

## 样例 #1

### 输入

```
((?))

```

### 输出

```
4

```

## 样例 #2

### 输入

```
??()??

```

### 输出

```
7

```



---

---
title: "Magic Forest"
layout: "post"
diff: 普及/提高-
pid: CF922B
tag: ['枚举']
---

# Magic Forest

## 题目描述

### 题目大意

给定一个正整数$n$ ，求满足如下条件的三元组$(a,b,c)$ 的个数：

- $1 \le a \le b \le c \le n$ 
- $a \space xor \space b \space xor \space c=0$ 
- 存在一个边长分别为$a,b,c$ 的三角形。

## 输入格式

一行一个正整数$n(1 \le n \le 2500)$

## 输出格式

输出满足题意的三元组个数。

感谢U3144 浮尘ii 提供的翻译

## 样例 #1

### 输入

```
6

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10

```

### 输出

```
2

```



---

---
title: "A Twisty Movement"
layout: "post"
diff: 普及/提高-
pid: CF933A
tag: ['动态规划 DP', '线段树', '枚举', '前缀和']
---

# A Twisty Movement

## 题目描述

A dragon symbolizes wisdom, power and wealth. On Lunar New Year's Day, people model a dragon with bamboo strips and clothes, raise them with rods, and hold the rods high and low to resemble a flying dragon.

A performer holding the rod low is represented by a $ 1 $ , while one holding it high is represented by a $ 2 $ . Thus, the line of performers can be represented by a sequence $ a_{1},a_{2},...,a_{n} $ .

Little Tommy is among them. He would like to choose an interval $ [l,r] $ ( $ 1<=l<=r<=n $ ), then reverse $ a_{l},a_{l+1},...,a_{r} $ so that the length of the longest non-decreasing subsequence of the new sequence is maximum.

A non-decreasing subsequence is a sequence of indices $ p_{1},p_{2},...,p_{k} $ , such that $ p_{1}<p_{2}<...<p_{k} $ and $ a_{p1}<=a_{p2}<=...<=a_{pk} $ . The length of the subsequence is $ k $ .

## 输入格式

The first line contains an integer $ n $ $ (1<=n<=2000) $ , denoting the length of the original sequence.

The second line contains $ n $ space-separated integers, describing the original sequence $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=2,i=1,2,...,n) $ .

## 输出格式

Print a single integer, which means the maximum possible length of the longest non-decreasing subsequence of the new sequence.

## 说明/提示

In the first example, after reversing $ [2,3] $ , the array will become $ [1,1,2,2] $ , where the length of the longest non-decreasing subsequence is $ 4 $ .

In the second example, after reversing $ [3,7] $ , the array will become $ [1,1,1,1,2,2,2,2,2,1] $ , where the length of the longest non-decreasing subsequence is $ 9 $ .

## 样例 #1

### 输入

```
4
1 2 1 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
10
1 1 2 2 2 1 1 2 2 1

```

### 输出

```
9

```



---

---
title: "Vile Grasshoppers"
layout: "post"
diff: 普及/提高-
pid: CF937B
tag: ['枚举', '素数判断,质数,筛法']
---

# Vile Grasshoppers

## 题目描述

The weather is fine today and hence it's high time to climb the nearby pine and enjoy the landscape.

The pine's trunk includes several branches, located one above another and numbered from $ 2 $ to $ y $ . Some of them (more precise, from $ 2 $ to $ p $ ) are occupied by tiny vile grasshoppers which you're at war with. These grasshoppers are known for their awesome jumping skills: the grasshopper at branch $ x $ can jump to branches ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF937B/e256171e16de0ce2bc4667496d6c5befd611ffc8.png).

Keeping this in mind, you wisely decided to choose such a branch that none of the grasshoppers could interrupt you. At the same time you wanna settle as high as possible since the view from up there is simply breathtaking.

In other words, your goal is to find the highest branch that cannot be reached by any of the grasshoppers or report that it's impossible.

## 输入格式

The only line contains two integers $ p $ and $ y $ $ (2<=p<=y<=10^{9}) $ .

## 输出格式

Output the number of the highest suitable branch. If there are none, print -1 instead.

## 说明/提示

In the first sample case grasshopper from branch $ 2 $ reaches branches $ 2 $ , $ 4 $ and $ 6 $ while branch $ 3 $ is initially settled by another grasshopper. Therefore the answer is $ 5 $ .

It immediately follows that there are no valid branches in second sample case.

## 样例 #1

### 输入

```
3 6

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3 4

```

### 输出

```
-1

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
title: "Friends"
layout: "post"
diff: 普及/提高-
pid: CF94B
tag: ['图论', '枚举']
---

# Friends

## 题目描述

有一天，一个叫做伊戈尔-凯的人放弃编程，转攻数学题。一个深秋的夜晚，他坐在桌旁读书，想着数学问题。
书上有着一段话吸引了他的注意：“在任六人中有三个人互相认识或互相不认识。”
伊戈尔完全无法理解为什么至少有六个人。“那对不起，我觉得五个人也一样，”他脑子里开始胡思乱想“让我试试...马克思，利亚，瓦娃--他们互相认识，额..再加一个迪玛和欧莱格，对瓦娃来说他们三个互不认识！哈哈哈哈哈，这个定理就是一个渣渣。”
伊戈尔带着他的5个朋友，让他们记下来，他们中谁互为朋友。现在他想看看这五个人是否真的认识三对或三对不认识的人。

## 输入格式

第一行包括了一个整数m(0<=m<=10)这是伊戈尔的五个朋友之间的互相认识的关系的个数。
接下来m行每行有两个数aibi（1<=ai,bi<=5;ai!=bi）,表示ai与bi是互相认识。每个关系是准确的也是对称的，即若x认识y，y也认识x。

## 输出格式

如果这五个人中既没有三个不认识的也没有三个互相认识的，输出：“FAIL”。其他情况输出“WIN“

## 样例 #1

### 输入

```
4
1 3
2 3
1 4
5 3

```

### 输出

```
WIN

```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
4 5
5 1

```

### 输出

```
FAIL

```



---

---
title: "Make a Square"
layout: "post"
diff: 普及/提高-
pid: CF962C
tag: ['递归', '枚举', '概率论']
---

# Make a Square

## 题目描述

You are given a positive integer $ n $ , written without leading zeroes (for example, the number 04 is incorrect).

In one operation you can delete any digit of the given integer so that the result remains a positive integer without leading zeros.

Determine the minimum number of operations that you need to consistently apply to the given integer $ n $ to make from it the square of some positive integer or report that it is impossible.

An integer $ x $ is the square of some positive integer if and only if $ x=y^2 $ for some positive integer $ y $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^{9} $ ). The number is given without leading zeroes.

## 输出格式

If it is impossible to make the square of some positive integer from $ n $ , print -1. In the other case, print the minimal number of operations required to do it.

## 说明/提示

In the first example we should delete from $ 8314 $ the digits $ 3 $ and $ 4 $ . After that $ 8314 $ become equals to $ 81 $ , which is the square of the integer $ 9 $ .

In the second example the given $ 625 $ is the square of the integer $ 25 $ , so you should not delete anything.

In the third example it is impossible to make the square from $ 333 $ , so the answer is -1.

## 样例 #1

### 输入

```
8314

```

### 输出

```
2

```

## 样例 #2

### 输入

```
625

```

### 输出

```
0

```

## 样例 #3

### 输入

```
333

```

### 输出

```
-1

```



---

---
title: "Almost Arithmetic Progression"
layout: "post"
diff: 普及/提高-
pid: CF978D
tag: ['搜索', '枚举', '剪枝']
---

# Almost Arithmetic Progression

## 题目描述

Polycarp 喜欢等差数列，对于一个数列 $ [a_1,a_2,a_3,\dots,a_n] $，如果对于每个 $ i\,(1\le i < n) $，$ a_{i+1}-a_i $ 的值均相同，那么这个数列就是一个等差数列。例如，$ [42] $ ，$ [5,5,5] $ ，$ [2,11,20,29] $ 和 $ [3,2,1,0] $ 是等差数列，但是 $ [1,0,1] $，$ [1,3,9] $ 和 $ [2,3,1] $ 不是。

根据定义，任何长度为 $ 1 $ 或 $ 2 $ 的数列都是等差数列。

Polycarp 找到了一个只包含正整数的数列 $ [b_1,b_2,b_3,\dots,b_n] $ 。他只想最多将每个元素改变一次。换句话说，对于每个元素，有三种选项：自增 $ 1 $，自减 $ 1 $ 或者不变。

你需要找到对 $ b $ 中元素操作（每个只能操作一次）的最小次数，使 $ b $ 变成一个等差数列。

操作完成后的数列可以含有 $ 0 $ 。

## 输入格式

第 $ 1 $ 行有 $ 1 $ 个整数 $ n\,(1\le n\le 100\,000) $ ，表示 $ b $ 中元素的个数。

第 $ 2 $ 行包含一个数列 $ b_1,b_2,b_3,\dots,b_n \,(1\le b_i \le 10^9)$。

## 输出格式

如果无法使用上述的操作将数列变为等差数列，输出 $ -1 $ 。在另一种情况下，输出一个非负整数，表示要将 $ b $ 变为等差数列所需要改变的元素的个数。唯一允许的操作是元素的自增 $/$ 减（不能够对一个元素操作两次）。

## 说明/提示

在样例 $ 1 $ 中，Polycarp 应该将第 $ 1 $ 个元素加 $ 1 $ ，将第 $ 2 $ 个元素加 $ 1 $ ，将第 $ 3 $ 个元素加 $ 1 $ ，并且不改变第 $ 4 $ 个元素。所以，Polycarp 操作之后的数列为 $ [25,20,15,10] $ 。

在样例 $ 2 $ 中，Polycarp 不应进行操作，因为他的数列已经是等差数列了。

在样例 $ 3 $ 中，不可能通过上述的操作将数列变为等差数列。

在样例 $ 4 $ 中，Polycarp 应该只将第 $ 1 $ 个元素加 $ 1 $ 。操作之后的数列为 $ [0,3,6,9,12] $ 。

## 样例 #1

### 输入

```
4
24 21 14 10

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2
500 500

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3
14 5 1

```

### 输出

```
-1

```

## 样例 #4

### 输入

```
5
1 3 6 9 12

```

### 输出

```
1

```



---

---
title: "Three displays"
layout: "post"
diff: 普及/提高-
pid: CF987C
tag: ['动态规划 DP', '线段树', '枚举']
---

# Three displays

## 题目描述

### 形式化题面

给定一个有两个性质 $s_i$ 和 $c_i$ 的数组，要求在其中选出三个数，满足：

 - $i<j<k$.
 - $s_i<s_j<s_k$.
 - $c_i+c_j+c_k$ 最小.

## 输入格式

第一行一个整数 $n$ 表示数组长度.

接下来一行 $n$ 个整数，表示 $s_i$.

接下来一行 $n$ 个整数，表示 $c_i$.

## 输出格式

一行一个整数，表示最小的 $c_i+c_j+c_k$

翻译 @[zymooll](/user/289296)

## 样例 #1

### 输入

```
5
2 4 5 4 10
40 30 20 10 40

```

### 输出

```
90

```

## 样例 #2

### 输入

```
3
100 101 100
2 4 5

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
10
1 2 3 4 5 6 7 8 9 10
10 13 11 14 15 12 13 13 18 13

```

### 输出

```
33

```



---

