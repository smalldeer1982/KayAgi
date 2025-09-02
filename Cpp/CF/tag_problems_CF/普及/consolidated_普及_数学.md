---
title: "The Bits"
layout: "post"
diff: 普及/提高-
pid: CF1017B
tag: ['数学', '概率论', '构造']
---

# The Bits

## 题目描述

手工翻译qwq，可能掺杂个人情感，但保证题目含义不变。

Rudolf正在去城堡的路上。在大门前，保安问了他一个问题：

已知两个长度为$n$的二进制数$a,b$。你可以任意选择$a$中的两个二进制位，然后把上面的数字调换位置。问题是，有多少中不同的操作，可以生成一个与原来不同的$a\;|\;b$？

换句话说，令$c=a\;|\;b$，你能找到多少种操作，使得更改后的$a$满足$a'\;|\;b \ne c$？

其中$|$表示“按位或”运算。如$(01010)_2\;|\;(10011)_2=(11011)_2$

## 输入格式

输入的第一行包含一个整数$n$。其中$2\leqslant n \leqslant 10^5$

后两行分别描述$a, b$。

## 输出格式

输出包含一个整数，表示交换的方案数。

## 样例 #1

### 输入

```
5
01011
11001

```

### 输出

```
4

```

## 样例 #2

### 输入

```
6
011000
010011

```

### 输出

```
6

```



---

---
title: "The Phone Number"
layout: "post"
diff: 普及/提高-
pid: CF1017C
tag: ['模拟', '数学', '构造']
---

# The Phone Number

## 题目描述

Mrs. Smith is trying to contact her husband, John Smith, but she forgot the secret phone number!

The only thing Mrs. Smith remembered was that any permutation of $ n $ can be a secret phone number. Only those permutations that minimize secret value might be the phone of her husband.

The sequence of $ n $ integers is called a permutation if it contains all integers from $ 1 $ to $ n $ exactly once.

The secret value of a phone number is defined as the sum of the length of the longest increasing subsequence (LIS) and length of the longest decreasing subsequence (LDS).

A subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ where $ 1\leq i_1 < i_2 < \ldots < i_k\leq n $ is called increasing if $ a_{i_1} < a_{i_2} < a_{i_3} < \ldots < a_{i_k} $ . If $ a_{i_1} > a_{i_2} > a_{i_3} > \ldots > a_{i_k} $ , a subsequence is called decreasing. An increasing/decreasing subsequence is called longest if it has maximum length among all increasing/decreasing subsequences.

For example, if there is a permutation $ [6, 4, 1, 7, 2, 3, 5] $ , LIS of this permutation will be $ [1, 2, 3, 5] $ , so the length of LIS is equal to $ 4 $ . LDS can be $ [6, 4, 1] $ , $ [6, 4, 2] $ , or $ [6, 4, 3] $ , so the length of LDS is $ 3 $ .

Note, the lengths of LIS and LDS can be different.

So please help Mrs. Smith to find a permutation that gives a minimum sum of lengths of LIS and LDS.

## 输入格式

The only line contains one integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of permutation that you need to build.

## 输出格式

Print a permutation that gives a minimum sum of lengths of LIS and LDS.

If there are multiple answers, print any.

## 说明/提示

In the first sample, you can build a permutation $ [3, 4, 1, 2] $ . LIS is $ [3, 4] $ (or $ [1, 2] $ ), so the length of LIS is equal to $ 2 $ . LDS can be ony of $ [3, 1] $ , $ [4, 2] $ , $ [3, 2] $ , or $ [4, 1] $ . The length of LDS is also equal to $ 2 $ . The sum is equal to $ 4 $ . Note that $ [3, 4, 1, 2] $ is not the only permutation that is valid.

In the second sample, you can build a permutation $ [2, 1] $ . LIS is $ [1] $ (or $ [2] $ ), so the length of LIS is equal to $ 1 $ . LDS is $ [2, 1] $ , so the length of LDS is equal to $ 2 $ . The sum is equal to $ 3 $ . Note that permutation $ [1, 2] $ is also valid.

## 样例 #1

### 输入

```
4

```

### 输出

```
3 4 1 2

```

## 样例 #2

### 输入

```
2

```

### 输出

```
2 1

```



---

---
title: "All are Same"
layout: "post"
diff: 普及/提高-
pid: CF1593D1
tag: ['数学']
---

# All are Same

## 题目描述

给定一个包含 $n$（$n$ 是偶数）个整数的数列 $a_1,a_2,\ldots,a_n$。

考虑一个可能的**正整数** $k$，在每次操作中，你可以选定一个 $i$，并将 $a_i$ 减少 $k$。

你可以执行任意多次（也可能是零次）操作，使这个数列中的**每一个数**都相等。

请找出最大的符合条件的 $k$，如果 $k$ 可以是任意的大小，输出 $-1$。

## 输入格式

本题包含多组数据。

输入的第一行包含一个正整数 $t$，表示数据组数。

每组数据包含两行，其中第一行包含一个偶数 $n$，第二行包含 $n$ 个整数 $a_i,a_2,\ldots,a_n$。

## 输出格式

对于每组数据，输出一个正整数 $k$ 或 $-1$，表示答案。

## 说明/提示

- $1 \le t \le 10$；
- $4 \le n \le 40$；
- $-10^6 \le a_i \le 10^6$。

保证 $\sum\limits{n} \le 100$。

Translated by @BurningEnderDragon, 2021.10.14

## 样例 #1

### 输入

```
3
6
1 5 3 1 1 5
8
-1 0 1 -1 0 1 -1 0
4
100 -1000 -1000 -1000
```

### 输出

```
2
1
1100
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
title: "Fortune Telling"
layout: "post"
diff: 普及/提高-
pid: CF1634B
tag: ['数学']
---

# Fortune Telling

## 题目描述

Haha, try to solve this, SelectorUnlimited!

— antontrygubO_o



Your friends Alice and Bob practice fortune telling.

Fortune telling is performed as follows. There is a well-known array $ a $ of $ n $ non-negative integers indexed from $ 1 $ to $ n $ . The tellee starts with some non-negative number $ d $ and performs one of the two operations for each $ i = 1, 2, \ldots, n $ , in the increasing order of $ i $ . The possible operations are:

- replace their current number $ d $ with $ d + a_i $
- replace their current number $ d $ with $ d \oplus a_i $ (hereinafter $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Exclusive_or))

Notice that the chosen operation may be different for different $ i $ and for different tellees.

One time, Alice decided to start with $ d = x $ and Bob started with $ d = x + 3 $ . Each of them performed fortune telling and got a particular number in the end. Notice that the friends chose operations independently of each other, that is, they could apply different operations for the same $ i $ .

You learnt that either Alice or Bob ended up with number $ y $ in the end, but you don't know whose of the two it was. Given the numbers Alice and Bob started with and $ y $ , find out who (Alice or Bob) could get the number $ y $ after performing the operations. It is guaranteed that on the jury tests, exactly one of your friends could have actually gotten that number.

Hacks

You cannot make hacks in this problem.

## 输入格式

On the first line of the input, you are given one number $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The following $ 2 \cdot t $ lines contain test cases.

The first line of each test case contains three numbers $ n $ , $ x $ , $ y $ ( $ 1 \le n \le 10^5 $ , $ 0 \le x \le 10^9 $ , $ 0 \le y \le 10^{15} $ ) — the length of array $ a $ , Alice's initial number (Bob's initial number is therefore $ x+3 $ ), and the number that one of the two friends got in the end.

The second line of each test case contains $ n $ numbers — the array $ a $ ( $ 0 \le a_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print the name of the friend who could get the number $ y $ : "Alice" or "Bob".

## 说明/提示

In the first test case, Alice could get $ 9 $ using the following operations: $ 7 + 2 = 9 $ .

In the second test case, Alice could get $ 2 $ using this operations: $ (0 + 1) \oplus 3 = 2 $ .

In the third test case, Bob started with $ x+3 = 0+3=3 $ and could get $ 1 $ this way: $ (((3 + 1) + 2) \oplus 3) \oplus 4 = 1 $ .

## 样例 #1

### 输入

```
4
1 7 9
2
2 0 2
1 3
4 0 1
1 2 3 4
2 1000000000 3000000000
1000000000 1000000000
```

### 输出

```
Alice
Alice
Bob
Alice
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
title: "Chopping Carrots (Easy Version)"
layout: "post"
diff: 普及/提高-
pid: CF1706D1
tag: ['数学']
---

# Chopping Carrots (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本间的区别仅为 $n$、$k$、$a_i$ 和 $\sum n$ 的上界。

注意不正常的空间限制。

给出长度为 $n$ 的整数数组 $ a_1, a_2, \ldots, a_n $，以及一个整数 $k$。

一个长度为 $n$ 的整数数组 $ p_1, p_2, \ldots, p_n $ 的花费为 $\max\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right) - \min\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right)$。
此处，$ \lfloor \frac{x}{y} \rfloor $ 表示 $x$ 除以 $y$ 的整数部分。
请找到花费最小的数组 $p$，且满足对任意 $ 1 \le i \le n$ 都有 $ 1 \le p_i \le k $。

## 输入格式

第一行包括一个整数 $t$（$ 1 \le t \le 100 $），表示接下来测试组的数量。

对于每一个测试组，第一行包括两个整数 $n$ 和 $k$（$ 1 \le n, k \le 3000 $）。

对于每一个测试组，第二行包括 $n$ 个整数 $ a_1, a_2, \ldots, a_n $（$ 1 \le a_1 \le a_2 \le \ldots \le a_n \le 3000 $）。

保证 $\sum n \le 3000$。

## 输出格式

对于每一个测试组，输出一个整数，表示满足上述条件的数组 $p$ 的花费的最小值。

## 样例 #1

### 样例输入 #1

```
7
5 2
4 5 6 8 11
5 12
4 5 6 8 11
3 1
2 9 15
7 3
2 3 5 5 6 9 10
6 56
54 286 527 1436 2450 2681
3 95
16 340 2241
2 2
1 3
```

### 样例输出 #1

```
2
0
13
1
4
7
0
```

## 说明/提示

在第一个测试组中，最优的数组是 $ p = [1, 1, 1, 2, 2] $。
$ \lfloor \frac{a_i}{p_i} \rfloor $ 得到的结果数组为 $ [4, 5, 6, 4, 5] $。
数组 $p$ 的花费为 $ \max\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) - \min\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) = 6 - 4 = 2 $。
可以证明，没有（满足题目条件的）数组的花费更小。

在第二个测试组中，最优的数组之一为 $ p = [12, 12, 12, 12, 12] $，它使得所有的 $ \lfloor \frac{a_i}{p_i} \rfloor $ 的值都为 $0$。

在第三个测试组中，唯一可能的数组为 $ p = [1, 1, 1] $。

## 样例 #1

### 输入

```
7
5 2
4 5 6 8 11
5 12
4 5 6 8 11
3 1
2 9 15
7 3
2 3 5 5 6 9 10
6 56
54 286 527 1436 2450 2681
3 95
16 340 2241
2 2
1 3
```

### 输出

```
2
0
13
1
4
7
0
```



---

---
title: "Vlad and a Pair of Numbers"
layout: "post"
diff: 普及/提高-
pid: CF1790E
tag: ['数学']
---

# Vlad and a Pair of Numbers

## 题目描述

Vlad found two positive numbers $ a $ and $ b $ ( $ a,b>0 $ ). He discovered that $ a \oplus b = \frac{a + b}{2} $ , where $ \oplus $ means the [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng) , and division is performed without rounding..

Since it is easier to remember one number than two, Vlad remembered only $ a\oplus b $ , let's denote this number as $ x $ . Help him find any suitable $ a $ and $ b $ or tell him that they do not exist.

## 输入格式

The first line of the input data contains the single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases in the test.

Each test case is described by a single integer $ x $ ( $ 1 \le x \le 2^{29} $ ) — the number that Vlad remembered.

## 输出格式

Output $ t $ lines, each of which is the answer to the corresponding test case. As the answer, output $ a $ and $ b $ ( $ 0 < a,b \le 2^{32} $ ), such that $ x = a \oplus b = \frac{a + b}{2} $ . If there are several answers, output any of them. If there are no matching pairs, output -1.

## 样例 #1

### 输入

```
6
2
5
10
6
18
36
```

### 输出

```
3 1
-1
13 7
-1
25 11
50 22
```



---

---
title: "Physical Education Lesson"
layout: "post"
diff: 普及/提高-
pid: CF1928C
tag: ['数学']
---

# Physical Education Lesson

## 题目描述

In a well-known school, a physical education lesson took place. As usual, everyone was lined up and asked to settle in "the first– $ k $ -th" position.

As is known, settling in "the first– $ k $ -th" position occurs as follows: the first $ k $ people have numbers $ 1, 2, 3, \ldots, k $ , the next $ k - 2 $ people have numbers $ k - 1, k - 2, \ldots, 2 $ , the next $ k $ people have numbers $ 1, 2, 3, \ldots, k $ , and so on. Thus, the settling repeats every $ 2k - 2 $ positions. Examples of settling are given in the "Note" section.

The boy Vasya constantly forgets everything. For example, he forgot the number $ k $ described above. But he remembers the position he occupied in the line, as well as the number he received during the settling. Help Vasya understand how many natural numbers $ k $ fit under the given constraints.

Note that the settling exists if and only if $ k > 1 $ . In particular, this means that the settling does not exist for $ k = 1 $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases. This is followed by the description of the test cases.

The only line of each test case contains two integers $ n $ and $ x $ ( $ 1 \le x < n \le 10^9 $ ) — Vasya's position in the line and the number Vasya received during the settling.

## 输出格式

For each test case, output a single integer — the number of different $ k $ that fit under the given constraints.

It can be proven that under the given constraints, the answer is finite.

## 说明/提示

In the first test case, $ k $ equals $ 2, 3, 5, 6 $ are suitable.

An example of settling for these $ k $ :

  $ k $ / № $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 6 $  $ 7 $  $ 8 $  $ 9 $  $ 10 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 1 $  $ 2 $  $ 3 $  $ 1 $  $ 2 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 5 $  $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 4 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 6 $  $ 1 $  $ 2 $  $ 3 $  $ 4 $  $ 5 $  $ 6 $  $ 5 $  $ 4 $  $ 3 $  $ 2 $  In the second test case, $ k = 2 $ is suitable.

## 样例 #1

### 输入

```
5
10 2
3 1
76 4
100 99
1000000000 500000000
```

### 输出

```
4
1
9
0
1
```



---

---
title: "Final Countdown"
layout: "post"
diff: 普及/提高-
pid: CF1932E
tag: ['数学', '高精度']
---

# Final Countdown

## 题目描述

You are in a nuclear laboratory that is about to explode and destroy the Earth. You must save the Earth before the final countdown reaches zero.

The countdown consists of $ n $ ( $ 1 \le n \le 4 \cdot 10^5 $ ) mechanical indicators, each showing one decimal digit. You noticed that when the countdown changes its state from $ x $ to $ x-1 $ , it doesn't happen in one move. Instead, each change of a single digit takes one second.

So, for example, if the countdown shows 42, then it will change to 41 in one second, because only one digit is changed, but if the countdown shows 2300, then it will change to 2299 in three seconds, because the three last digits are changed.

Find out how much time is left before the countdown reaches zero.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then the descriptions of the test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le 4\cdot 10^5 $ ).

The second line contains a string of $ n $ digits, the current state of the countdown. It is guaranteed that at least one digit is not zero.

The sum of $ n $ for all tests does not exceed $ 4\cdot 10^5 $ .

## 输出格式

For each test case, print a single integer without leading zeroes, the number of seconds left before the countdown reaches zero. Note that this number may be huge.

## 说明/提示

In the first example, there are four changes that take 2 seconds: 40 to 39, 30 to 29, 20 to 19, and 10 to 09, other changes take 1 second each. So the total time is $ 2\cdot 4 + 1\cdot(42-4) = 46 $ .

## 样例 #1

### 输入

```
5
2
42
5
12345
2
99
4
0005
27
456480697259671309012631002
```

### 输出

```
46
13715
108
5
507200774732968121125145546
```



---

---
title: "Turtle Tenacity: Continual Mods"
layout: "post"
diff: 普及/提高-
pid: CF1933D
tag: ['数学']
---

# Turtle Tenacity: Continual Mods

## 题目描述

Given an array $ a_1, a_2, \ldots, a_n $ , determine whether it is possible to rearrange its elements into $ b_1, b_2, \ldots, b_n $ , such that $ b_1 \bmod b_2 \bmod \ldots \bmod b_n \neq 0 $ .

Here $ x \bmod y $ denotes the remainder from dividing $ x $ by $ y $ . Also, the modulo operations are calculated from left to right. That is, $ x \bmod y \bmod z = (x \bmod y) \bmod z $ . For example, $ 2024 \bmod 1000 \bmod 8 = (2024 \bmod 1000) \bmod 8 = 24 \bmod 8 = 0 $ .

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 10^5 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output "YES" if it is possible, "NO" otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, rearranging the array into $ b = [1, 2, 3, 4, 5, 6] $ (doing nothing) would result in $ 1 \bmod 2 \bmod 3 \bmod 4 \bmod 5 \bmod 6 = 1 $ . Hence it is possible to achieve the goal.

In the second test case, the array $ b $ must be equal to $ [3, 3, 3, 3, 3] $ , which would result in $ 3 \bmod 3 \bmod 3 \bmod 3 \bmod 3 = 0 $ . Hence it is impossible to achieve the goal.

In the third test case, rearranging the array into $ b = [3, 2, 2] $ would result in $ 3 \bmod 2 \bmod 2 = 1 $ . Hence it is possible to achieve the goal.

## 样例 #1

### 输入

```
8
6
1 2 3 4 5 6
5
3 3 3 3 3
3
2 2 3
5
1 1 2 3 7
3
1 2 2
3
1 1 2
6
5 2 10 10 10 2
4
3 6 9 3
```

### 输出

```
YES
NO
YES
NO
YES
NO
YES
NO
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
title: "Cells Arrangement"
layout: "post"
diff: 普及/提高-
pid: CF1968E
tag: ['数学', '构造']
---

# Cells Arrangement

## 题目描述

You are given an integer $ n $ . You choose $ n $ cells $ (x_1,y_1), (x_2,y_2),\dots,(x_n,y_n) $ in the grid $ n\times n $ where $ 1\le x_i\le n $ and $ 1\le y_i\le n $ .

Let $ \mathcal{H} $ be the set of distinct Manhattan distances between any pair of cells. Your task is to maximize the size of $ \mathcal{H} $ . Examples of sets and their construction are given in the notes.

If there exists more than one solution, you are allowed to output any.

Manhattan distance between cells $ (x_1,y_1) $ and $ (x_2,y_2) $ equals $ |x_1-x_2|+|y_1-y_2| $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 50 $ ) — the number of test cases.

Each of the following $ t $ lines contains a single integer $ n $ ( $ 2\le n\le 10^3 $ ).

## 输出格式

For each test case, output $ n $ points which maximize the size of $ \mathcal{H} $ . It is not necessary to output an empty line at the end of the answer for each test case.

## 说明/提示

In the first testcase we have $ n=2 $ . One of the possible arrangements is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/75dc943a7c64415a7537c95e5a0a8ab6f7bb8c40.png) The arrangement with cells located in $ (1,1) $ and $ (1,2) $ .  In this case $ \mathcal{H}=\{|1-1|+|1-1|,|1-1|+|2-2|,|1-1|+|1-2|\}=\{0,0,1\}=\{0,1\} $ . Hence, the size of $ \mathcal{H} $ is $ 2 $ . It can be shown that it is the greatest possible answer.In the second testcase we have $ n=3 $ . The optimal arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c33264fb4d38aae733c98659eb0f28334deed2c9.png) The arrangement with cells located in $ (2,1) $ , $ (2,3) $ and $ (3,1) $ . $ \mathcal{H} $ = $ \{|2-2|+|1-1|,|2-2|+|3-3|,|3-3|+|1-1|,|2-2|+|1-3|,|2-3|+|1-1|,|2-3|+|3-1|\} $ = $ \{0,0,0,2,1,3\} $ = $ \{0,1,2,3\} $ .

For $ n=4 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c8c88e231569a366e81dbe59dfe40f3bca88662e.png)For $ n=5 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/3a3f9b43e6fc8c9643d27a1bfc597d0efe1c8425.png)For $ n=6 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/b0bf5b17a4bc6da02c3ed5a2113cf7373a9e3ccc.png)

## 样例 #1

### 输入

```
5
2
3
4
5
6
```

### 输出

```
1 1
1 2

2 1
2 3
3 1

1 1
1 3
4 3
4 4

1 1
1 3
1 4
2 1
5 5

1 4
1 5
1 6
5 2
5 5
6 1
```



---

---
title: "Circle Perimeter"
layout: "post"
diff: 普及/提高-
pid: CF1971F
tag: ['数学']
---

# Circle Perimeter

## 题目描述

Given an integer $ r $ , find the number of lattice points that have a Euclidean distance from $ (0, 0) $ greater than or equal to $ r $ but strictly less than $ r+1 $ .

A lattice point is a point with integer coordinates. The Euclidean distance from $ (0, 0) $ to the point $ (x,y) $ is $ \sqrt{x^2 + y^2} $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The only line of each test case contains a single integer $ r $ ( $ 1 \leq r \leq 10^5 $ ).

The sum of $ r $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of lattice points that have an Euclidean distance $ d $ from $ (0, 0) $ such that $ r \leq d < r+1 $ .

## 说明/提示

The points for the first three test cases are shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971F/aff456cddb623f0decb8386de3943888d72800f7.png)

## 样例 #1

### 输入

```
6
1
2
3
4
5
1984
```

### 输出

```
8
16
20
24
40
12504
```



---

---
title: "GCD-sequence"
layout: "post"
diff: 普及/提高-
pid: CF1980D
tag: ['数学', '数论']
---

# GCD-sequence

## 题目描述

最大公约数（GCD）是两个整数 $x$ 和 $y$ 可以整除的最大整数 $z$。例如，$\text{GCD}(36, 48) = 12$，$\text{GCD}(5, 10) = 5$，以及 $\text{GCD}(7,11) = 1$。

Kristina 有一个由正整数组成的数组 $a$，其中有 $n$ 个数。她想要计算相邻两个数的最大公约数，得到一个新数组 $b$，称为最大公约数序列。

因此，最大公约数序列的元素 $b$ 将使用公式 $b_i = \text{GCD}(a_i, a_{i + 1})$ 计算得到 $1 \le i \le n - 1$。

确定是否可以从数组 $a$ 中移除恰好一个数字，使得最大公约数序列 $b$ 是非递减的（即，$b_i \le b_{i+1}$ 始终为真）。

例如，如果 Khristina 有一个数组 $a = [20, 6, 12, 3, 48, 36]$。如果她从中移除 $a_4 = 3$ 并计算 $b$ 的最大公约数序列，她会得到：

+ $b_1 = \text{GCD}(20, 6) = 2$
+ $b_2 = \text{GCD}(6, 12) = 6$ 
+ $b_3 = \text{GCD}(12, 48) = 12$ 
+ $b_4 = \text{GCD}(48, 36) = 12$  

结果得到的最大公约数序列 $b = [2,6,12,12]$ 是非递减的，因为 $b_1 \le b_2 \le b_3 \le b_4$。

## 输入格式

输入数据的第一行包含一个数字 $t$（$1 \le t \le 10^4$）— 测试中的测试用例数量。

接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$3 \le n \le 2 \cdot 10^5$）— 数组 $a$ 中元素的数量。

每个测试用例的第二行包含恰好 $n$ 个整数 $a_i$（$1 \le a_i \le 10^9$）— 数组 $a$ 的元素。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一行：

+ 如果可以移除数组 $a$ 中的恰好一个数字，使得 $b$ 的最大公约数序列是非递减的，则输出 `YES`;
否则输出 `NO`。

你可以以任何形式输出答案（例如，字符串 `yEs`，`yes`，`Yes`，和 `YES` 都将被视为肯定答案）。

## 样例 #1

### 输入

```
12
6
20 6 12 3 48 36
4
12 6 3 4
3
10 12 3
5
32 16 8 4 2
5
100 50 2 10 20
4
2 4 8 1
10
7 4 6 2 4 5 1 4 2 8
7
5 9 6 8 5 9 2
6
11 14 8 12 9 3
9
5 7 3 10 6 3 12 6 3
3
4 2 4
8
1 6 11 12 6 12 3 6
```

### 输出

```
YES
NO
YES
NO
YES
YES
NO
YES
YES
YES
YES
YES
```



---

---
title: "D-Function"
layout: "post"
diff: 普及/提高-
pid: CF1985G
tag: ['数学']
---

# D-Function

## 题目描述

Let $ D(n) $ represent the sum of digits of $ n $ . For how many integers $ n $ where $ 10^{l} \leq n < 10^{r} $ satisfy $ D(k \cdot n) = k \cdot D(n) $ ? Output the answer modulo $ 10^9+7 $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) – the number of test cases.

Each test case contains three integers $ l $ , $ r $ , and $ k $ ( $ 0 \leq l < r \leq 10^9 $ , $ 1 \leq k \leq 10^9 $ ).

## 输出格式

For each test case, output an integer, the answer, modulo $ 10^9 + 7 $ .

## 说明/提示

For the first test case, the only values of $ n $ that satisfy the condition are $ 1 $ and $ 2 $ .

For the second test case, the only values of $ n $ that satisfy the condition are $ 1 $ , $ 10 $ , and $ 11 $ .

For the third test case, all values of $ n $ between $ 10 $ inclusive and $ 100 $ exclusive satisfy the condition.

## 样例 #1

### 输入

```
6
0 1 4
0 2 7
1 2 1
1 2 3
582 74663 3
0 3 1
```

### 输出

```
2
3
90
12
974995667
999
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
title: "Triple Operations"
layout: "post"
diff: 普及/提高-
pid: CF1999E
tag: ['数学', '前缀和']
---

# Triple Operations

## 题目描述

**题面描述**

Ivy 在黑板上写下了在 $l$ 到 $r$ 之间的所有整数。

在一次运算中，她做了以下操作：

- 在黑板上选出任意两个数字 $x$ 和 $y$ ，将它们擦掉，然后在它们的位置上写下数字 $3x$ 和 $\lfloor \frac{y}{3} \rfloor$ 。(这里的 $\lfloor x\rfloor$ 表示取整，即四舍五入到最接近的整数）。

要使黑板上的所有数字都等于 $0$ ，Ivy 最少需要进行多少次运算？可以证明一定有解。

## 输入格式

第一行包含一个正整数 $t$ ( $1 \leq t \leq 10^4$ )，表示测试用例的数量。

对于每个测试用例，仅一行包含两个正整数 $l$ 和 $r$ ( $1 \leq l <  r \leq 2 \cdot 10^5$ )。

## 输出格式

对于每个测试用例，输出一个整数，即使黑板上的所有数字等于 $0$ 所需的最少操作次数。

**样例解释**

在第一个测试用例中，我们可以执行 $5$ 次操作，如下：

$$
1,2,3 \xrightarrow[x=1,\\,y=2]{} 3,0,3 \xrightarrow[x=0,\\,y=3]{} 1,0,3 \xrightarrow[x=0,\\,y=3]{} 1,0,1 \xrightarrow[x=0,\\,y=1]{} 0,0,1 \xrightarrow[x=0,\\,y=1]{} 0,0,0 .
$$

## 样例 #1

### 输入

```
4
1 3
2 4
199999 200000
19 84
```

### 输出

```
5
6
36
263
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
title: "Ruler (hard version)"
layout: "post"
diff: 普及/提高-
pid: CF1999G2
tag: ['数学', '三分']
---

# Ruler (hard version)

## 题目描述

本题是问题的困难版本。该版本与简单版之间的唯一区别是在这个版本中，你最多可以进行 $7$ 次查询。

这是一道交互题。

有一把有 $1001$ 个刻度的尺子，刻度分别为 $1 \sim 1001$。不幸的是，尺子丢失了一个刻度 $x$（$2 \le x \le 999$）。当你用尺子量一个长度为 $y$ 的物体时，尺子量出的结果为：
- 若 $y < x$，尺子将会量出正确的结果 $y$。
- 否则，尺子将会量出错误的结果 $y + 1$。

你需要找出丢失的刻度 $x$。你可以每次提供两个 $1$ 至 $1000$ 内的整数 $a,b$，你将会收到尺子量出的 $a$ 的长度与尺子量出的 $b$ 的长度之积。

你可以进行最多 $7$ 次询问。

## 输入格式

输入共一行一个整数 $T$，代表数据组数。

## 输出格式

你可以输出 `? a b` 以进行一次询问。`a` 和 `b` 的含义见上。随后，你将收到一个整数，表示尺子量出的 $a$ 的长度与尺子量出的 $b$ 的长度之积。

当你猜出 $x$ 后，你需要输出一行 `! x`，`x` 为你猜出的 $x$ 值。

如果你的询问大于 $7$ 次或猜出的 $x$ 值不对，你将收到一行一个 `-1`。请立刻终止程序。

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
title: "Binomial Coefficients, Kind Of"
layout: "post"
diff: 普及/提高-
pid: CF2025B
tag: ['数学']
---

# Binomial Coefficients, Kind Of

## 题目描述

Recently, akshiM met a task that needed binomial coefficients to solve. He wrote a code he usually does that looked like this:

```
<pre class="verbatim">    for (int n = 0; n < N; n++) { // loop over n from 0 to N-1 (inclusive)<br></br>        C[n][0] = 1;<br></br>        C[n][n] = 1;<br></br>        for (int k = 1; k < n; k++) // loop over k from 1 to n-1 (inclusive)<br></br>            C[n][k] = C[n][k - 1] + C[n - 1][k - 1];<br></br>    }<br></br>
```

Unfortunately, he made an error, since the right formula is the following:

```
<pre class="verbatim">            C[n][k] = C[n - 1][k] + C[n - 1][k - 1]<br></br>
```

But his team member keblidA is interested in values that were produced using the wrong formula. Please help him to calculate these coefficients for $ t $ various pairs $ (n_i, k_i) $ . Note that they should be calculated according to the first (wrong) formula.

Since values $ C[n_i][k_i] $ may be too large, print them modulo $ 10^9 + 7 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of pairs. Next, $ t $ pairs are written in two lines.

The second line contains $ t $ integers $ n_1, n_2, \dots, n_t $ ( $ 2 \le n_i \le 10^5 $ ).

The third line contains $ t $ integers $ k_1, k_2, \dots, k_t $ ( $ 1 \le k_i < n_i $ ).

## 输出格式

Print $ t $ integers $ C[n_i][k_i] $ modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
7
2 5 5 100000 100000 100000 100000
1 2 3 1 33333 66666 99999
```

### 输出

```
2
4
8
2
326186014
984426998
303861760
```



---

---
title: "Add Zeros"
layout: "post"
diff: 普及/提高-
pid: CF2027C
tag: ['动态规划 DP', '数学', '记忆化搜索']
---

# Add Zeros

## 题目描述

You're given an array $ a $ initially containing $ n $ integers. In one operation, you must do the following:

- Choose a position $ i $ such that $ 1 < i \le |a| $ and $ a_i = |a| + 1 - i $ , where $ |a| $ is the current size of the array.
- Append $ i - 1 $ zeros onto the end of $ a $ .

After performing this operation as many times as you want, what is the maximum possible length of the array $ a $ ?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

The first line of each test case contains $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^{12} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum possible length of $ a $ after performing some sequence of operations.

## 说明/提示

In the first test case, we can first choose $ i = 4 $ , since $ a_4 = 5 + 1 - 4 = 2 $ . After this, the array becomes $ [2, 4, 6, 2, 5, 0, 0, 0] $ . We can then choose $ i = 3 $ since $ a_3 = 8 + 1 - 3 = 6 $ . After this, the array becomes $ [2, 4, 6, 2, 5, 0, 0, 0, 0, 0] $ , which has a length of $ 10 $ . It can be shown that no sequence of operations will make the final array longer.

In the second test case, we can choose $ i=2 $ , then $ i=3 $ , then $ i=4 $ . The final array will be $ [5, 4, 4, 5, 1, 0, 0, 0, 0, 0, 0] $ , with a length of $ 11 $ .

## 样例 #1

### 输入

```
4
5
2 4 6 2 5
5
5 4 4 5 1
4
6 8 2 3
1
1
```

### 输出

```
10
11
10
1
```



---

---
title: "Alice's Adventures in Permuting"
layout: "post"
diff: 普及/提高-
pid: CF2028B
tag: ['数学', '分类讨论']
---

# Alice's Adventures in Permuting

## 题目描述

Alice mixed up the words transmutation and permutation! She has an array $ a $ specified via three integers $ n $ , $ b $ , $ c $ : the array $ a $ has length $ n $ and is given via $ a_i = b\cdot (i - 1) + c $ for $ 1\le i\le n $ . For example, if $ n=3 $ , $ b=2 $ , and $ c=1 $ , then $ a=[2 \cdot 0 + 1, 2 \cdot 1 + 1, 2 \cdot 2 + 1] = [1, 3, 5] $ .

Now, Alice really enjoys permutations of $ [0, \ldots, n-1] $ $ ^{\text{∗}} $ and would like to transform $ a $ into a permutation. In one operation, Alice replaces the maximum element of $ a $ with the $ \operatorname{MEX} $ $ ^{\text{†}} $ of $ a $ . If there are multiple maximum elements in $ a $ , Alice chooses the leftmost one to replace.

Can you help Alice figure out how many operations she has to do for $ a $ to become a permutation for the first time? If it is impossible, you should report it.

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 0 $ to $ n-1 $ in arbitrary order. Please note, this is slightly different from the usual definition of a permutation. For example, $ [1,2,0,4,3] $ is a permutation, but $ [0,1,1] $ is not a permutation ( $ 1 $ appears twice in the array), and $ [0,2,3] $ is also not a permutation ( $ n=3 $ but there is $ 3 $ in the array).

 $ ^{\text{†}} $ The $ \operatorname{MEX} $ of an array is the smallest non-negative integer that does not belong to the array. For example, the $ \operatorname{MEX} $ of $ [0, 3, 1, 3] $ is $ 2 $ and the $ \operatorname{MEX} $ of $ [5] $ is $ 0 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The only line of each test case contains three integers $ n $ , $ b $ , $ c $ ( $ 1\le n\le 10^{18} $ ; $ 0\le b $ , $ c\le 10^{18} $ ) — the parameters of the array.

## 输出格式

For each test case, if the array can never become a permutation, output $ -1 $ . Otherwise, output the minimum number of operations for the array to become a permutation.

## 说明/提示

In the first test case, the array is already $ [0, 1, \ldots, 9] $ , so no operations are required.

In the third test case, the starting array is $ [1, 3, 5, \ldots, 199] $ . After the first operation, the $ 199 $ gets transformed into a $ 0 $ . In the second operation, the $ 197 $ gets transformed into a $ 2 $ . If we continue this, it will take exactly $ 50 $ operations to get the array $ [0, 1, 2, 3, \ldots, 99] $ .

In the fourth test case, two operations are needed: $ [1,1,1] \to [0,1,1] \to [0,2,1] $ .

In the fifth test case, the process is $ [0,0,0] \to [1,0,0] \to [2,0,0] \to [1,0,0] \to [2,0,0] $ . This process repeats forever, so the array is never a permutation and the answer is $ -1 $ .

## 样例 #1

### 输入

```
7
10 1 0
1 2 3
100 2 1
3 0 1
3 0 0
1000000000000000000 0 0
1000000000000000000 1000000000000000000 1000000000000000000
```

### 输出

```
0
1
50
2
-1
-1
1000000000000000000
```



---

---
title: "Penchick and BBQ Buns"
layout: "post"
diff: 普及/提高-
pid: CF2031C
tag: ['数学', '构造']
---

# Penchick and BBQ Buns

## 题目描述

有 $n$ 个空位，你要用一些正整数来填充这些空位。

你用来填充空位的正整数 $k$ 必须满足以下两个条件：

-	$k$ 至少出现两次。

填完空位之后，设第 $i$ 个空位上的数是 $a_i$。对于任意的 $i\le n$ 和 $j\le n$，如果 $i\ne j$ 且 $a_i=a_j$，那么 $|i-j|$ 是完全平方数。

你需要构造出一组合法的方案，或者报告无解。

## 输入格式

第一行输入一个整数 $t(1\le t\le 2\times 10^5)$，表示数据组数。

对于每一组数据，输入一行一个整数，表示 $n(1\le n\le 2\times 10^5)$。

保证 $\sum n\le 2\times 10^5$。

## 输出格式

对于每组测试数据，如果无解，输出一行一个整数 $-1$。

如果有解，输出一行 $n$ 个数，第 $i$ 个数表示 $a_i$。

### 样例解释

对于 $n=3$，可以证明无法找到合法解，因为不能构造出使用超过两种数且每种数出现次数大于等于 $2$ 的方案，而 $\{1,1,1\}$ 显然不是合法解，因为 $a_1=a_3$ 而 $3-1$ 不是完全平方数。

对于 $n=12$，显然样例输出是合法解：

$a_1=a_{10},10-1=9=3^2$

$a_2=a_{6},6-2=4=2^2$

$a_3=a_{12},12-3=9=3^2$

$a_4=a_{8},8-4=4=2^2$

$a_5=a_{9},9-5=4=2^2$

$a_7=a_{11},11-7=4=2^2$

## 样例 #1

### 输入

```
2
3
12
```

### 输出

```
-1
1 2 3 6 10 2 7 6 10 1 7 3
```



---

---
title: "Alya and Permutation"
layout: "post"
diff: 普及/提高-
pid: CF2035C
tag: ['数学', '构造']
---

# Alya and Permutation

## 题目描述

Alya has been given a hard problem. Unfortunately, she is too busy running for student council. Please solve this problem for her.

Given an integer $ n $ , construct a permutation $ p $ of integers $ 1, 2, \ldots, n $ that maximizes the value of $ k $ (which is initially $ 0 $ ) after the following process.

Perform $ n $ operations, on the $ i $ -th operation ( $ i=1, 2, \dots, n $ ),

- If $ i $ is odd, $ k=k\,\&\,p_i $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).
- If $ i $ is even, $ k=k\,|\,p_i $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 500 $ ) — the number of test cases.

The only line of each test case contains a single integer $ n $ ( $ 5\le n\le 2 \cdot 10^5 $ ) — the length of the permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum value of $ k $ in the first line and output the permutation $ p_1, p_2,\ldots, p_n $ in the second line.

If there are multiple such permutations, output any.

## 说明/提示

For the first test case, the value of $ k $ is determined as follows:

 $ k = 0 $ initially.

- On the $ 1 $ st operation, $ 1 $ is odd, so Alya sets $ k $ to be $ k\&p_1 = 0\&2 = 0 $ .
- On the $ 2 $ nd operation, $ 2 $ is even, so Alya sets $ k $ to be $ k|p_2 = 0|1 = 1 $ .
- On the $ 3 $ rd operation, $ 3 $ is odd, so Alya sets $ k $ to be $ k\&p_3 = 1\&3 = 1 $ .
- On the $ 4 $ th operation, $ 4 $ is even, so Alya sets $ k $ to be $ k|p_4 = 1|4 = 5 $ .
- On the $ 5 $ th operation, $ 5 $ is odd, so Alya sets $ k $ to be $ k\&p_5 = 5\&5 = 5 $ .

The final value of $ k $ is $ 5 $ . It can be shown that the final value of $ k $ is at most $ 5 $ for all permutations of length $ 5 $ . Another valid output is $ [2, 3, 1, 4, 5] $ .

For the second test case, the final value of $ k $ is $ 7 $ . It can be shown that the final value of $ k $ is at most $ 7 $ for all permutations of length $ 6 $ . Other valid outputs include $ [2, 4, 1, 6, 3, 5] $ and $ [5, 2, 6, 1, 3, 4] $ .

## 样例 #1

### 输入

```
6
5
6
7
8
9
10
```

### 输出

```
5
2 1 3 4 5 
7
1 2 4 6 5 3 
7
2 4 5 1 3 6 7 
15
2 4 5 1 3 6 7 8 
9
2 4 5 6 7 1 3 8 9 
15
1 2 3 4 5 6 8 10 9 7
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
title: "Insane Problem"
layout: "post"
diff: 普及/提高-
pid: CF2044E
tag: ['数学']
---

# Insane Problem

## 题目描述

Wave 有五个整数 $k$ 、 $l_1$ 、 $r_1$ 、 $l_2$ 和 $r_2$ ，她想要你帮她数出有多少对有序数对 $(x, y)$ 满足以下条件：

- $l_1 \leq x \leq r_1$ .
- $l_2 \leq y \leq r_2$ .
- 存在一个非负整数 $n$ ，使得 $\frac{y}{x} = k^n$ 。

## 输入格式

第一行包含一个正整数 $t (1 \leq t \leq 10^4)$，代表测试样例数量。

接下来的 $t-1$ 行，每行代表一组测试样例，包括五个整数 $k$ 、 $l_1$ 、 $r_1$ 、 $l_2$ 和 $r_2$  （ $2 \leq k \leq 10^9, 1 \leq l_1 \leq r_1 \leq 10^9, 1 \leq l_2 \leq r_2 \leq 10^9$ ）。

## 输出格式

对于每组测试样例，在新的一行输出符合条件的有序数对 $(x,y)$ 的组数。

## 说明/提示

对于第三组测试样例，以下有序数对是符合条件的：

- $(5,15)$
- $(5,45)$
- $(6,18)$
- $(6,54)$
- $(7,21)$
- $(7,63)$

对于第四组测试样例，唯一有效的有序数对是 $(1,1\,000\,000\,000)$

## 样例 #1

### 输入

```
5
2 2 6 2 12
2 1 1000000000 1 1000000000
3 5 7 15 63
1000000000 1 5 6 1000000000
15 17 78 2596 20914861
```

### 输出

```
12
1999999987
6
1
197
```



---

---
title: "Skibidus and Sigma"
layout: "post"
diff: 普及/提高-
pid: CF2065D
tag: ['数学', '排序']
---

# Skibidus and Sigma

## 题目描述

定义一个 $k$ 个元素的数组 $b$ 的分数为
$\sum_{i=1}^{k}\left(\sum_{j=1}^{i}b_j\right)$，也就是说，设 $S_i$ 表示数组 $b$ 的前 $i$ 个元素之和，则分数可以写作
$S_1 + S_2 + \ldots + S_k$。

Skibidus 得到了 $n$ 个数组 $a_1, a_2, \ldots, a_n$，每个数组包含 $m$ 个元素。作为西格玛男人，他希望能将这 $n$ 个数组按任意顺序拼接成一个包含 $n \cdot m$ 个元素的数组，以使最终得到的拼接数组的分数达到最大。请你帮助他计算拼接后能够获得的最大分数！

形式上地说，在所有可能的长度为 $n$ 的排列 $p$ 中，
求出数组 $a_{p_1} + a_{p_2} + \dots + a_{p_n}$ 的最大分数，
其中符号 $+$ 表示数组拼接。

$ ^{\text{∗}} $ 一个排列指的是一个包含 $1$ 到 $n$ 的所有整数且每个整数恰好出现一次的序列。  
$ ^{\text{∗}} $ 两个数组 $c$ 和 $d$（长度分别为 $e$ 和 $f$）的拼接 $c+d$ 定义为 $c_1, c_2, \ldots, c_e, d_1, d_2, \ldots, d_f$。

## 输入格式

第一行包含一个整数 $t$ ($1 \leq t \leq 10^4$)，表示测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $m$ ($1 \leq n \cdot m \leq 2 \cdot 10^5$)，分别表示数组的个数和每个数组的长度。

接下来的 $n$ 行中，第 $i$ 行包含 $m$ 个整数 $a_{i,1}, a_{i,2}, \ldots, a_{i,m}$ ($1 \leq a_{i,j} \leq 10^6$)，表示第 $i$ 个数组的元素。

保证所有测试用例中，$n \cdot m$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一行一个整数，表示所有排列中拼接数组能够获得的最大分数。

## 说明/提示

在第一个测试用例中，有可能的两种排列：
- $p = [1, 2]$，拼接后的数组为 $a_{p_1} + a_{p_2} = [4, 4, 6, 1]$，分数为 $4 + (4+4) + (4+4+6) + (4+4+6+1) = 41$。
- $p = [2, 1]$，拼接后的数组为 $a_{p_1} + a_{p_2} = [6, 1, 4, 4]$，分数为 $6 + (6+1) + (6+1+4) + (6+1+4+4) = 39$。  

因此，最大可能分数为 $41$。

在第二个测试用例中，一个最优的拼接结果为 $[4,1,2,1,2,2,2,2,3,2,1,2]$，分数为 $162$。

## 样例 #1

### 输入

```
3
2 2
4 4
6 1
3 4
2 2 2 2
3 2 1 2
4 1 2 1
2 3
3 4 5
1 1 9
```

### 输出

```
41
162
72
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
title: "Beautiful Sequence"
layout: "post"
diff: 普及/提高-
pid: CF2069C
tag: ['数学', '组合数学', '前缀和']
---

# Beautiful Sequence

## 题目描述

我们称一个整数序列为美丽的（beautiful），当且仅当满足以下条件：
- 序列长度至少为 $3$；
- 对于除第一个元素外的每个元素，其左侧存在一个比它小的元素；
- 对于除最后一个元素外的每个元素，其右侧存在一个比它大的元素；

例如，$[1, 4, 2, 4, 7]$ 和 $[1, 2, 4, 8]$ 是美丽的，但 $[1, 2]$、$[2, 2, 4]$ 和 $[1, 3, 5, 3]$ 不是。

注意：子序列是指通过删除原序列中某些元素（不改变剩余元素的顺序）得到的新序列。

给定一个大小为 $n$ 的整数数组 $a$，其中每个元素均为 $1$ 到 $3$ 之间的整数。你的任务是计算数组 $a$ 中美丽子序列的数量。由于答案可能很大，请将其对 $998244353$ 取模后输出。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$3 \le n \le 2 \cdot 10^5$）。

第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le 3$）。

输入额外约束：所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——数组 $a$ 中美丽子序列的数量对 $998244353$ 取模后的结果。

## 说明/提示

在示例的第一个测试用例中，以下子序列是美丽的：
- $[a_3, a_4, a_7]$；
- $[a_3, a_5, a_7]$；
- $[a_3, a_4, a_5, a_7]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
7
3 2 1 2 2 1 3
4
3 1 2 2
3
1 2 3
9
1 2 3 2 1 3 2 2 3
```

### 输出

```
3
0
1
22
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
title: "Do You Love Your Hero and His Two-Hit Multi-Target Attacks?"
layout: "post"
diff: 普及/提高-
pid: CF2072E
tag: ['数学', '构造']
---

# Do You Love Your Hero and His Two-Hit Multi-Target Attacks?

## 题目描述

Akito 决定学习一个强大的新咒语。由于这个咒语拥有无可估量的力量，它必然需要大量空间和精心准备。为此，Akito 来到了一片空地。我们将这片空地表示为一个笛卡尔坐标系。

为了施展咒语，Akito 需要在空地的不同整数坐标处放置 $0 \le n \le 500$ 根法杖，使得恰好存在 $k$ 对 $(i, j)$ 满足 $1 \le i < j \le n$ 且 $\rho(i, j) = d(i, j)$。

这里，对于两个整数坐标点 $a = (x_a, y_a)$ 和 $b = (x_b, y_b)$，定义 $\rho(a, b) = \sqrt{(x_a - x_b)^2 + (y_a - y_b)^2}$ 且 $d(a, b) = |x_a - x_b| + |y_a - y_b|$。

## 输入格式

输入的第一行包含一个数 $t$（$1 \le t \le 1000$）——测试用例的数量。

每个测试用例的唯一一行包含一个数 $k$（$0 \le k \le 10^5$）——满足 $\rho(i, j) = d(i, j)$ 的法杖对数要求。

## 输出格式

对于每个测试用例，输出的第一行应包含一个数 $n$（$0 \le n \le 500$）——放置的法杖数量。

接下来的 $n$ 行中，每行应输出两个整数 $x_i, y_i$（$-10^9 \le x_i, y_i \le 10^9$）——第 $i$ 根法杖的坐标。所有法杖的坐标点必须互不相同。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
0
2
5
```

### 输出

```
6
69 52
4 20
789 9308706
1337 1337
-1234 -5678
23456178 707
10
-236 -346262358
273568 6435267
2365437 31441367
246574 -45642372
-236 56
4743623 -192892 
10408080 -8173135
-237415357 31441367
-78125638 278
56 143231
5
1 1
2 1
1 5
3 5
1 10
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
title: "Sasha and the Apartment Purchase"
layout: "post"
diff: 普及/提高-
pid: CF2098B
tag: ['数学', '排序']
---

# Sasha and the Apartment Purchase

## 题目描述

Sasha 想在一条街道上购买一套公寓，这条街道上的房屋从左到右编号为 $1$ 到 $10^9$。

这条街道上有 $n$ 家酒吧，分别位于编号为 $a_1, a_2, \ldots, a_n$ 的房屋中。注意，可能有多个酒吧位于同一房屋中，这种情况下这些酒吧被视为不同的酒吧。

Sasha 担心在他购买公寓时，部分酒吧可能会关闭，但最多不超过 $k$ 家酒吧会关闭。

对于任意编号为 $x$ 的房屋，定义 $f(x)$ 为所有开放酒吧 $y$（即关闭部分酒吧后）的 $|x - y|$ 之和。

Sasha 可以购买编号为 $x$（$1 \le x \le 10^9$）的房屋中的公寓，当且仅当可以通过关闭最多 $k$ 家酒吧，使得 $f(x)$ 在所有房屋中达到最小值。

请确定 Sasha 可以购买公寓的不同房屋数量。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$1 \leq n \leq 10^5$，$0 \leq k < n$）——酒吧数量和最多可以关闭的酒吧数量。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \leq a_i \leq 10^9$）——酒吧所在的房屋编号。

保证所有测试用例的 $n$ 之和不超过 $10^5$。

## 输出格式

对于每个测试用例，输出一个整数——Sasha 可以购买公寓的房屋数量。


## 说明/提示

在第一个测试用例中，没有酒吧可以关闭，因此只有编号为 $2$ 和 $3$ 的房屋是合适的。对于编号为 $2$ 的房屋，距离之和为 $|2 - 1| + |2 - 2| + |2 - 3| + |2 - 4| = 4$；对于编号为 $3$ 的房屋，距离之和为 $|3 - 1| + |3 - 2| + |3 - 3| + |3 - 4| = 4$。然而，对于编号为 $1$ 的房屋，距离之和为 $|1 - 1| + |1 - 2| + |1 - 3| + |1 - 4| = 6$，因此编号为 $1$ 的房屋不合适。可以证明 Sasha 也无法在其他房屋购买公寓。

在第二个测试用例中，合适的房屋编号为 $6$ 和 $7$。如果 Sasha 选择编号为 $6$ 的房屋，只需不关闭任何酒吧。如果 Sasha 选择编号为 $7$ 的房屋，可以关闭编号为 $1$ 和 $6$ 的房屋中的酒吧。此时开放的酒吧将位于编号为 $6$、$7$ 和 $7$ 的房屋中。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
4 0
1 2 3 4
5 2
7 6 6 7 1
3 1
6 7 9
6 2
5 1 9 10 13 2
```

### 输出

```
2
2
4
9
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
title: "Red Light, Green Light (Easy version)"
layout: "post"
diff: 普及/提高-
pid: CF2118D1
tag: ['模拟', '数学', '图论']
---

# Red Light, Green Light (Easy version)

## 题目描述

**这是问题的简单版本。不同版本的区别在于对 $k$ 和单个测试点中的 $n,q$ 总和的限制不同。**

给你一个长度为 $10^{15}$ 的长条和一个常数 $k$。在长条上有 $n$ 个格子上有一个信号灯，第 $i$ 个信号灯在格子 $p_i$ 处，同时具有一个初相 $d_i<k$。第 $i$ 个信号灯将在时刻 $z\times k+d_i,z$ 为整数时亮红灯，其他时刻亮绿灯。

时刻 $0$ 时你在某个格子处，面向正方向。每个时刻你将执行如下操作：
- 如果你所在的格子上有一个红色的信号灯，转向；
- 向你所面向的方向走一格。

你要处理 $q$ 个询问，询问给出时刻 $0$ 时你在格子 $a_i$，问时刻 $10^{100}$ 你是否已经走出长条的范围。

## 输入格式

多组数据。第一行一个整数 $t(1\le t\le 500)$，表示数据组数。

对于每组数据：第一行两个整数 $n,k(1\le n,k\le 500)$。\
第二行 $n$ 个整数 $p_1,p_2,\cdots,p_n(1\le p_1<p_2\cdots<p_n\le 10^{15})$。\
第三行 $n$ 个整数 $d_1,d_2,\cdots,d_n(0\le d_i<k)$。\
第四行一个整数 $q(1\le q\le 500)$。\
第五行 $q$ 个整数 $a_1,a_2,\cdots,a_q(1\le a_i\le 10
^{15})$。

保证单个测试点中 $\sum n,\sum q\le 500$。

## 输出格式

对于每组数据，输出 $q$ 行，第 $i$ 个询问结果为是则在第 $i$ 行输出 `YES`，否则输出 `NO`。你可以以任意形式输出答案（大写或小写）。例如，`yEs`，`yes`，`Yes` 和 `YES` 均是符合条件的输出。

## 说明/提示

对于第一组数据，从 $1,2,3$ 出发的情况如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2118D2/ce9b61d8441ec2687644e4fcb1ecf9c698d0d9de.png)

对于第二组数据，从 $2$ 出发的情况如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2118D2/b6fc75687c6b2b664c445b1824b01121fde0aaa1.png)

## 样例 #1

### 输入

```
4
2 2
1 4
1 0
3
1 2 3
9 4
1 2 3 4 5 6 7 8 9
3 2 1 0 1 3 3 1 1
5
2 5 6 7 8
4 2
1 2 3 4
0 0 0 0
4
1 2 3 4
3 4
1 2 3
3 1 1
3
1 2 3
```

### 输出

```
YES
NO
YES
YES
YES
YES
NO
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
title: "A Problem about Polyline"
layout: "post"
diff: 普及/提高-
pid: CF578A
tag: ['数学']
---

# A Problem about Polyline

## 题目描述

There is a polyline going through points $ (0,0)–(x,x)–(2x,0)–(3x,x)–(4x,0)–...-(2kx,0)–(2kx+x,x)–... $ .

We know that the polyline passes through the point $ (a,b) $ . Find minimum positive value $ x $ such that it is true or determine that there is no such $ x $ .

## 输入格式

Only one line containing two positive integers $ a $ and $ b $ ( $ 1<=a,b<=10^{9} $ ).

## 输出格式

Output the only line containing the answer. Your answer will be considered correct if its relative or absolute error doesn't exceed $ 10^{-9} $ . If there is no such $ x $ then output $ -1 $ as the answer.

## 说明/提示

You can see following graphs for sample 1 and sample 3.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF578A/abf33c2e979ad11f626e45babf5d2a8a224a3964.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF578A/567201d8db120e4f8136d5be265b91eca027e0d4.png)

## 样例 #1

### 输入

```
3 1

```

### 输出

```
1.000000000000

```

## 样例 #2

### 输入

```
1 3

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
4 1

```

### 输出

```
1.250000000000

```



---

---
title: "Taxes"
layout: "post"
diff: 普及/提高-
pid: CF735D
tag: ['数学', '素数判断,质数,筛法']
---

# Taxes

## 题目描述

Mr. Funt now lives in a country with a very specific tax laws. The total income of mr. Funt during this year is equal to $ n $ ( $ n>=2 $ ) burles and the amount of tax he has to pay is calculated as the maximum divisor of $ n $ (not equal to $ n $ , of course). For example, if $ n=6 $ then Funt has to pay $ 3 $ burles, while for $ n=25 $ he needs to pay $ 5 $ and if $ n=2 $ he pays only $ 1 $ burle.

As mr. Funt is a very opportunistic person he wants to cheat a bit. In particular, he wants to split the initial $ n $ in several parts $ n_{1}+n_{2}+...+n_{k}=n $ (here $ k $ is arbitrary, even $ k=1 $ is allowed) and pay the taxes for each part separately. He can't make some part equal to $ 1 $ because it will reveal him. So, the condition $ n_{i}>=2 $ should hold for all $ i $ from $ 1 $ to $ k $ .

Ostap Bender wonders, how many money Funt has to pay (i.e. minimal) if he chooses and optimal way to split $ n $ in parts.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=2·10^{9} $ ) — the total year income of mr. Funt.

## 输出格式

Print one integer — minimum possible number of burles that mr. Funt has to pay as a tax.

## 样例 #1

### 输入

```
4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
27

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
title: "Journey"
layout: "post"
diff: 普及/提高-
pid: CF839C
tag: ['数学', '概率论', '期望']
---

# Journey

## 题目描述

## 问题描述

在七大王国里有 $n$ 个城市和 $n-1$ 条道路，每条道路连接两个城市，并且通过这些道路我们可以从任何一个城市到达任何一个城市。

席恩和阿莎在第一个城市骑上马，他们要通过这些路开始一次旅行。但是有雾，所以他们看不见他们的马带他们去了哪里。当马抵达一个城市的时候（包括第一个城市），它会去跟当前这个城市相连的城市。但是这是一匹奇怪的马，它只去他们以前没有去过的城市。在每个城市，马以相同的概率移动去上述符合要求的城市，并且当没有这样的城市（可走）时，马就停下了。

每条路的长度都是 $1$，旅行从城市 $1$ 开始，问这次旅行的期望长度（旅行长度的期望值）是多少？你可以通过[这个链接](https://en.wikipedia.org/wiki/Expected\_value)来阅读一些关于期望（平均）值的文字。

## 输入格式

第一行包含一个整数 $n$（$1 \leq n \leq 100000$）——城市的数量。

下来是 $n-1$ 行，这些行中的第 $i$ 行包含两个整数 $u_i$ 和 $v_i$（$1 \leq u_i, v_i \leq n$，$u_i \not = v_i$）——第 $i$ 条边连接的城市。

保证通过这些道路可以从任何一个城市到达任何一个城市。

## 输出格式

输出一个数——这次旅行长度的期望值。旅行从城市 $1$ 开始。

当你的答案的绝对或相对误差不超过 $10^{-6}$ 时你的答案将会被接受。

换句话说，假定你的答案是 $a$，标准答案是 $b$，当 $\frac{|a-b|}{max(1,b)} \leq 10^{-6}$ 时你的答案将会被接受。

## 说明/提示

在第一个例子中，他们的旅行可能以同等的概率停止于城市 $3$ 或城市 $4$。去城市 $3$ 的距离是 $1$，去城市 $4$ 的距离是 $2$，所以期望是 $1.5$。

在第二个例子中，他们的旅行可能停止于城市 $4$ 或城市 $5$。去这些城市的距离都是 $2$，所以期望是 $2$。

## 样例 #1

### 输入

```
4
1 2
1 3
2 4

```

### 输出

```
1.500000000000000

```

## 样例 #2

### 输入

```
5
1 2
1 3
3 4
2 5

```

### 输出

```
2.000000000000000

```



---

---
title: "Reflection"
layout: "post"
diff: 普及/提高-
pid: CF86A
tag: ['数学']
---

# Reflection

## 题目描述

For each positive integer $ n $ consider the integer $ ψ(n) $ which is obtained from $ n $ by replacing every digit $ a $ in the decimal notation of $ n $ with the digit $ (9-a) $ . We say that $ ψ(n) $ is the reflection of $ n $ . For example, reflection of $ 192 $ equals $ 807 $ . Note that leading zeros (if any) should be omitted. So reflection of $ 9 $ equals $ 0 $ , reflection of $ 91 $ equals $ 8 $ .

Let us call the weight of the number the product of the number and its reflection. Thus, the weight of the number $ 10 $ is equal to $ 10·89=890 $ .

Your task is to find the maximum weight of the numbers in the given range $ [l,r] $ (boundaries are included).

## 输入格式

Input contains two space-separated integers $ l $ and $ r $ ( $ 1<=l<=r<=10^{9} $ ) — bounds of the range.

## 输出格式

Output should contain single integer number: maximum value of the product $ n·ψ(n) $ , where $ l<=n<=r $ .

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preferred to use cout (also you may use %I64d).

## 说明/提示

In the third sample weight of $ 8 $ equals $ 8·1=8 $ , weight of $ 9 $ equals $ 9·0=0 $ , weight of $ 10 $ equals $ 890 $ .

Thus, maximum value of the product is equal to $ 890 $ .

## 样例 #1

### 输入

```
3 7

```

### 输出

```
20
```

## 样例 #2

### 输入

```
1 1

```

### 输出

```
8
```

## 样例 #3

### 输入

```
8 10

```

### 输出

```
890
```



---

---
title: "Finite or not?"
layout: "post"
diff: 普及/提高-
pid: CF983A
tag: ['数学', '最大公约数 gcd', '进制']
---

# Finite or not?

## 题目描述

有 $n$ 组数据，每一组数据读入一个分数的分子 $p$、分母 $q$ 和进制 $b$（分子、分母均以十进制读入）求在 $b$ 进制下 $\frac{p}{q}$ 是否为有限小数。如果是，输出 `Finite`，否则输出 `Infinite`

## 输入格式

第一行输入 $n$

接下来 $n$ 行输入 $p$, $q$ 和 $b$。

## 输出格式

对于每一组数据，输出 `Finite` 或 `Infinite`

1 <= n <= 10^5, 1 <= b, p, q <= 10^18

由 @Medoric 提供翻译

## 样例 #1

### 输入

```
2
6 12 10
4 3 10

```

### 输出

```
Finite
Infinite

```

## 样例 #2

### 输入

```
4
1 1 2
9 36 2
4 12 3
3 5 4

```

### 输出

```
Finite
Finite
Finite
Infinite

```



---

---
title: "High School: Become Human"
layout: "post"
diff: 普及/提高-
pid: CF987B
tag: ['数学', '导数']
---

# High School: Become Human

## 题目描述

### 题目大意
输入一个 $x$ ,一个 $y$ ，求是  $x^y$  大还是  $y^x$  大。 $(1≤x,y≤10^9)$

## 输入格式

一行，两个整数 $x,y$ 。

## 输出格式

若 $x^y$ > $y^x$ ,输出">",若 $x^y$ < $y^x$ ,输出"<",相等则输出"="。

感谢@二元长天笑 提供的翻译

## 样例 #1

### 输入

```
5 8

```

### 输出

```
>

```

## 样例 #2

### 输入

```
10 3

```

### 输出

```
<

```

## 样例 #3

### 输入

```
6 6

```

### 输出

```
=

```



---

