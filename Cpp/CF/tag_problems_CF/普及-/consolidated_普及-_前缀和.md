---
title: "Love Song"
layout: "post"
diff: 普及-
pid: CF1539B
tag: ['前缀和']
---

# Love Song

## 题目描述

Petya once wrote a sad love song and shared it to Vasya. The song is a string consisting of lowercase English letters. Vasya made up $ q $ questions about this song. Each question is about a subsegment of the song starting from the $ l $ -th letter to the $ r $ -th letter. Vasya considers a substring made up from characters on this segment and repeats each letter in the subsegment $ k $ times, where $ k $ is the index of the corresponding letter in the alphabet. For example, if the question is about the substring "abbcb", then Vasya repeats letter 'a' once, each of the letters 'b' twice, letter 'c" three times, so that the resulting string is "abbbbcccbb", its length is $ 10 $ . Vasya is interested about the length of the resulting string.

Help Petya find the length of each string obtained by Vasya.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1\leq n\leq 100\,000 $ , $ 1\leq q \leq 100\,000 $ ) — the length of the song and the number of questions.

The second line contains one string $ s $ — the song, consisting of $ n $ lowercase letters of English letters.

Vasya's questions are contained in the next $ q $ lines. Each line contains two integers $ l $ and $ r $ ( $ 1 \leq l \leq r \leq n $ ) — the bounds of the question.

## 输出格式

Print $ q $ lines: for each question print the length of the string obtained by Vasya.

## 说明/提示

In the first example Vasya is interested in three questions. In the first question Vasya considers the substring "aba", that transforms to "abba", so the answer is equal to $ 4 $ . In the second question Vasya considers "baca", that transforms to "bbaccca", so the answer is $ 7 $ . In the third question Vasya considers the string "abacaba",that transforms to "abbacccabba" of length $ 11 $ .

## 样例 #1

### 输入

```
7 3
abacaba
1 3
2 5
1 7
```

### 输出

```
4
7
11
```

## 样例 #2

### 输入

```
7 4
abbabaa
1 3
5 7
6 6
2 4
```

### 输出

```
5
4
1
5
```

## 样例 #3

### 输入

```
13 7
sonoshikumiwo
1 5
2 10
7 7
1 13
4 8
2 5
3 9
```

### 输出

```
82
125
9
191
62
63
97
```



---

---
title: "Also Try Minecraft"
layout: "post"
diff: 普及-
pid: CF1709B
tag: ['前缀和']
---

# Also Try Minecraft

## 题目描述

You are beta testing the new secret Terraria update. This update will add quests to the game!

Simply, the world map can be represented as an array of length $ n $ , where the $ i $ -th column of the world has height $ a_i $ .

There are $ m $ quests you have to test. The $ j $ -th of them is represented by two integers $ s_j $ and $ t_j $ . In this quest, you have to go from the column $ s_j $ to the column $ t_j $ . At the start of the quest, you are appearing at the column $ s_j $ .

In one move, you can go from the column $ x $ to the column $ x-1 $ or to the column $ x+1 $ . In this version, you have Spectre Boots, which allow you to fly. Since it is a beta version, they are bugged, so they only allow you to fly when you are going up and have infinite fly duration. When you are moving from the column with the height $ p $ to the column with the height $ q $ , then you get some amount of fall damage. If the height $ p $ is greater than the height $ q $ , you get $ p - q $ fall damage, otherwise you fly up and get $ 0 $ damage.

For each of the given quests, determine the minimum amount of fall damage you can get during this quest.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 2 \le n \le 10^5; 1 \le m \le 10^5 $ ) — the number of columns in the world and the number of quests you have to test, respectively.

The second line of the input contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ), where $ a_i $ is the height of the $ i $ -th column of the world.

The next $ m $ lines describe quests. The $ j $ -th of them contains two integers $ s_j $ and $ t_j $ ( $ 1 \le s_j, t_j \le n; s_j \ne t_j $ ), which means you have to move from the column $ s_j $ to the column $ t_j $ during the $ j $ -th quest.

Note that $ s_j $ can be greater than $ t_j $ .

## 输出格式

Print $ m $ integers. The $ j $ -th of them should be the minimum amount of fall damage you can get during the $ j $ -th quest completion.

## 样例 #1

### 输入

```
7 6
10 8 9 6 8 12 7
1 2
1 7
4 6
7 1
3 5
4 2
```

### 输出

```
2
10
0
7
3
1
```



---

---
title: "GCD Partition"
layout: "post"
diff: 普及-
pid: CF1780B
tag: ['最大公约数 gcd', '前缀和']
---

# GCD Partition

## 题目描述

While at Kira's house, Josuke saw a piece of paper on the table with a task written on it.

The task sounded as follows. There is an array $ a $ of length $ n $ . On this array, do the following:

- select an integer $ k > 1 $ ;
- split the array into $ k $ subsegments $ ^\dagger $ ;
- calculate the sum in each of $ k $ subsegments and write these sums to another array $ b $ (where the sum of the subsegment $ (l, r) $ is $ {\sum_{j = l}^{r}a_j} $ );
- the final score of such a split will be $ \gcd(b_1, b_2, \ldots, b_k)^\ddagger $ .

The task is to find such a partition that the score is maximum possible. Josuke is interested in this task but is not strong in computer science. Help him to find the maximum possible score.

 $ ^\dagger $ A division of an array into $ k $ subsegments is $ k $ pairs of numbers $ (l_1, r_1), (l_2, r_2), \ldots, (l_k, r_k) $ such that $ l_i \le r_i $ and for every $ 1 \le j \le k - 1 $ $ l_{j + 1} = r_j + 1 $ , also $ l_1 = 1 $ and $ r_k = n $ . These pairs represent the subsegments.

 $ ^\ddagger $ $ \gcd(b_1, b_2, \ldots, b_k) $ stands for the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the array $ b $ .

## 输入格式

The first line contains a single number $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

For each test case, the first line contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, a_3, \ldots, a_n $ ( $ 1 \le a_i \le 10^9  $ ) — the array $ a $ itself.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case print a single integer — the maximum score for the optimal partition.

## 说明/提示

In the first test case, you can choose $ k = 2 $ and split the array into subsegments $ (1, 2) $ and $ (3, 4) $ .

Then the score of such a partition will be equal to $ \gcd(a_1 + a_2, a_3 + a_4) = \gcd(2 + 2, 1 + 3) = \gcd(4, 4) = 4 $ .

In the fourth test case, you can choose $ k = 3 $ and split the array into subsegments $ (1, 2), (3, 5), (6, 6) $ .

The split score is $ \gcd(1 + 2, 1 + 1 + 1, 3) = 3 $ .

## 样例 #1

### 输入

```
6
4
2 2 1 3
2
1 2
3
1 4 5
6
1 2 1 1 1 3
10
12 30 37 88 12 78 89 17 2 12
6
7 7 7 7 7 7
```

### 输出

```
4
1
5
3
1
21
```



---

---
title: "Romantic Glasses"
layout: "post"
diff: 普及-
pid: CF1915E
tag: ['前缀和']
---

# Romantic Glasses

## 题目描述

Iulia has $ n $ glasses arranged in a line. The $ i $ -th glass has $ a_i $ units of juice in it. Iulia drinks only from odd-numbered glasses, while her date drinks only from even-numbered glasses.

To impress her date, Iulia wants to find a contiguous subarray of these glasses such that both Iulia and her date will have the same amount of juice in total if only the glasses in this subarray are considered. Please help her to do that.

More formally, find out if there exists two indices $ l $ , $ r $ such that $ 1 \leq l \leq r \leq n $ , and $ a_l + a_{l + 2} + a_{l + 4} + \dots + a_{r} = a_{l + 1} + a_{l + 3} + \dots + a_{r-1} $ if $ l $ and $ r $ have the same parity and $ a_l + a_{l + 2} + a_{l + 4} + \dots + a_{r - 1} = a_{l + 1} + a_{l + 3} + \dots + a_{r} $ otherwise.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the total number of glasses.

The second line of each test case contains $ n $ integers $ a_1, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the amount of juice in each glass.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output "YES" if there exists a subarray satisfying the condition, and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 说明/提示

In the first test case, Iulia can pick $ l=1 $ and $ r=3 $ . Then she drinks $ a_1+a_3=1+2=3 $ units and her date drinks $ a_2=3 $ units of juice.

In the second test case, Iulia can pick $ l=2 $ and $ r=5 $ . Then she drinks $ a_3+a_5=1+1=2 $ units and her date drinks $ a_2+a_4=1+1=2 $ units of juice.

In the third test case no such contiguous subarray works.

In the fourth test case, Iulia can pick $ l=2 $ and $ r=8 $ . Then she drinks $ a_3+a_5+a_7=11+1+1=13 $ units and her date drinks $ a_2+a_4+a_6+a_8=2+4+5+2=13 $ units of juice.

## 样例 #1

### 输入

```
6
3
1 3 2
6
1 1 1 1 1 1
10
1 6 9 8 55 3 14 2 7 2
8
1 2 11 4 1 5 1 2
6
2 6 1 5 7 8
9
2 5 10 4 4 9 6 7 8
```

### 输出

```
YES
YES
NO
YES
NO
YES
```



---

---
title: "Make Equal"
layout: "post"
diff: 普及-
pid: CF1931B
tag: ['前缀和']
---

# Make Equal

## 题目描述

There are $ n $ containers of water lined up, numbered from left to right from $ 1 $ to $ n $ . Each container can hold any amount of water; initially, the $ i $ -th container contains $ a_i $ units of water. The sum of $ a_i $ is divisible by $ n $ .

You can apply the following operation any (possibly zero) number of times: pour any amount of water from the $ i $ -th container to the $ j $ -th container, where $ i $ must be less than $ j $ (i.e. $ i<j $ ). Any index can be chosen as $ i $ or $ j $ any number of times.

Determine whether it is possible to make the amount of water in all containers the same using this operation.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then the descriptions of the test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of containers with water.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the amounts of water in the containers. It is guaranteed that the sum of $ a_i $ in each test case does not exceed $ 2 \cdot 10^9 $ . Also, the sum of $ a_i $ is divisible by $ n $ .

It is guaranteed that the sum of $ n $ over all test cases in the input does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

Output $ t $ lines, each of which is the answer to the corresponding test case. As the answer, output "YES" if it is possible to make the amount of water in all containers the same using the described operation. Otherwise, output "NO".

You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes", and "YES" will be accepted as a positive answer.

## 说明/提示

In the third test case of the example ( $ a=[4, 5, 2, 1, 3] $ ), you can proceed as follows:

- pour $ 1 $ unit of water from the first vessel to the fourth, then $ a=[3, 5, 2, 2, 3] $ ;
- pour $ 1 $ unit of water from the second vessel to the third, then $ a=[3, 4, 3, 2, 3] $ ;
- pour $ 1 $ unit of water from the second vessel to the fourth, then $ a=[3, 3, 3, 3, 3] $ .

## 样例 #1

### 输入

```
6
1
43
2
1 3
5
4 5 2 1 3
3
1 2 3
7
4 5 5 0 6 4 4
7
6 5 5 1 3 4 4
```

### 输出

```
YES
NO
YES
NO
NO
YES
```



---

---
title: "Left and Right Houses"
layout: "post"
diff: 普及-
pid: CF1945C
tag: ['前缀和']
---

# Left and Right Houses

## 题目描述

在 Letovo 村，有 $ n $ 坐房屋。村民们决定修一条大路，把村子分成左右两部分。每个居民都想住在街道的右边或左边，这被描述为一个顺序 $ a_1, a_2, \dots, a_n $，其中 $ a_j = 0 $ 表示编号为 $ j $ 房子的居民想住在街道的左边；否则，$ a_j = 1 $。

这条路将穿过两座房子之间。它左边的房子将被宣布为左边，右边的房子将被宣布为右边。更正式的说法是，**若道路在房屋 $ i $ 和 $ i+1 $ 之间通行。那么，位于 $ 1 $ 和 $ i $ 之间的房屋将位于街道的左侧，位于 $ i+1 $ 和 $ n $ 之间的房屋将位于街道的右侧**。这条路也**可以在第一所房子前面经过，在最后一所房子后面经过**。在这种情况下，整个村庄分别被声明为右侧或左侧。

为了使设计公平，决定铺设道路，使村庄两边至少有一半的居民对选择感到满意。也就是说，在每一边的 $ x $ 个居民中，至少 $ \lceil\frac{x}{2}\rceil $ 应该想住在另一边，其中 $ \lceil x \rceil $ 表示四舍五入的实数 $ x $。

 [](https://cdn.luogu.com.cn/upload/vjudge＿pic/CF1945C/2ed555a735574721378598482dfea8442c0609da.png)
 
路的左边会有 $ i $ 栋房子，对应的 $ a_j $ 中至少有 $ \lceil\frac{i}{2}\rceil $ 个 $0$。在道路的右侧，将会有 $ n-i $ 房屋，在相应的 $ a_j $ 中必须至少有 $ \lceil\frac{n-i}{2}\rceil $ 房屋。确定道路应该铺设在哪座房子 $ i $ 之后，以满足所描述的条件，并尽可能靠近村庄的中心。正式地说，在所有合适的位置 $ i $ 中，最小化 $ \left|\frac{n}{2} - i\right| $（**注意：这里的 $\frac{n}{2}$ 不做取整操作**）。

如果有多个适合的位置 $ i $ 和最小的 $ \left|\frac{n}{2} - i\right| $，输出较小的位置（即更靠左的位置）。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $ t $ ($ 1 \le t \le 2\cdot 10^4 $)。下面是测试用例的描述。

每个测试用例的第一行包含一个整数 $ n $ ($ 3 \le n \le 3\cdot 10^5 $)。每个测试用例的下一行包含一个长度为 $ n $ 的字符串 $ a $，仅由 $ 0 $ 和 $ 1 $ 组成。

可以保证所有测试用例 $ n $ 的总和不超过 $ 3\cdot 10^5 $。

## 输出格式

对于每个测试用例，输出一个数字 $ i $ ——应该在房子之后铺设道路的位置（如果应该在第一个房子之前铺设道路，则输出 $ 0 $）。我们可以证明答案总是存在的。

## 说明/提示

让我们考虑输入数据的第一个示例。

如果我们在第一所房子之后铺设道路，将会有一所房子 $ a_1 = 1 $ 在街道的左侧，其中的居民愿意住在街道的右侧。然后 $ 0 $ 出 $ 1 $ 居民在均匀的一边会满意的选择，这意味着道路不能在房子 $ 1 $ 后铺设。

如果我们在第二所房子之后铺设道路，左侧的 $ 2 $ 个居民中的 $ 1 $ 位（$ a_1 = 1 $, $ a_2 = 0 $）和右侧 $ 1 $ 位居民中的 $ 1 $ 位（$ a_3 = 1 $）将对选择感到满意。两边一半以上的居民都对这个选择感到满意，这意味着这条路可以能在房子 $ 2 $ 后铺设。我们可以证明这是最优答案。

翻译者：[SCAR_L](https://www.luogu.com.cn/user/608703)

## 样例 #1

### 输入

```
7
3
101
6
010111
6
011001
3
000
3
110
3
001
4
1100
```

### 输出

```
2
3
2
3
0
1
0
```



---

---
title: "Balanced Shuffle (Easy)"
layout: "post"
diff: 普及-
pid: CF1970A1
tag: ['模拟', '前缀和']
---

# Balanced Shuffle (Easy)

## 题目描述

A parentheses sequence is a string consisting of characters "(" and ")", for example "(()((".

A balanced parentheses sequence is a parentheses sequence which can become a valid mathematical expression after inserting numbers and operations into it, for example "(()(()))".

The balance of a parentheses sequence is defined as the number of opening parentheses "(" minus the number of closing parentheses ")". For example, the balance of the sequence "(()((" is 3.

A balanced parentheses sequence can also be defined as a parentheses sequence with balance 0 such that each of its prefixes has a non-negative balance.

We define the balanced shuffle operation that takes a parentheses sequence and returns a parentheses sequence as follows: first, for every character of the input sequence, we compute the balance of the prefix of the sequence before that character and write those down in a table together with the positions of the characters in the input sequence, for example:

Prefix balance01212321Position12345678Character(()(()))Then, we sort the columns of this table in increasing order of prefix balance, breaking ties in decreasing order of position. In the above example, we get:

Prefix balance01112223Position18427536Character()(()())The last row of this table forms another parentheses sequence, in this case "()(()())". This sequence is called the result of applying the balanced shuffle operation to the input sequence, or in short just the balanced shuffle of the input sequence.

You are given a balanced parentheses sequence. Print its balanced shuffle.

## 输入格式

The only line of input contains a string $ s $ consisting only of characters "(" and ")". This string is guaranteed to be a non-empty balanced parentheses sequence with its length not exceeding $ 500\,000 $ .

## 输出格式

Print the parentheses sequence $ t $ — the balanced shuffle of $ s $ .

## 样例 #1

### 输入

```
(()(()))
```

### 输出

```
()(()())
```



---

---
title: "Sort"
layout: "post"
diff: 普及-
pid: CF1996C
tag: ['贪心', '前缀和']
---

# Sort

## 题目描述

You are given two strings $ a $ and $ b $ of length $ n $ . Then, you are (forced against your will) to answer $ q $ queries.

For each query, you are given a range bounded by $ l $ and $ r $ . In one operation, you can choose an integer $ i $ ( $ l \leq i \leq r $ ) and set $ a_i = x $ where $ x $ is any character you desire. Output the minimum number of operations you must perform such that $ \texttt{sorted(a[l..r])} = \texttt{sorted(b[l..r])} $ . The operations you perform on one query does not affect other queries.

For an arbitrary string $ c $ , $ \texttt{sorted(c[l..r])} $ denotes the substring consisting of characters $ c_l, c_{l+1}, ... , c_r $ sorted in lexicographical order.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 1000 $ ) – the number of test cases.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \leq n, q \leq 2 \cdot 10^5 $ ) – the length of both strings and the number of queries.

The following line contains $ a $ of length $ n $ . It is guaranteed $ a $ only contains lowercase latin letters.

The following line contains $ b $ of length $ n $ . It is guaranteed $ b $ only contains lowercase latin letters.

The following $ q $ lines contain two integers $ l $ and $ r $ ( $ 1 \leq l \leq r \leq n $ ) – the range of the query.

It is guaranteed the sum of $ n $ and $ q $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query, output an integer, the minimum number of operations you need to perform in a new line.

## 说明/提示

For the first query, $ \texttt{sorted(a[1..5])} = $ abcde and $ \texttt{sorted(b[1..5])} = $ abcde, so no operations are necessary.

For the second query, you need to set $ a_1 =  $ e. Then, $ \texttt{sorted(a[1..4])} = \texttt{sorted(b[1..4])} =  $ bcde.

## 样例 #1

### 输入

```
3
5 3
abcde
edcba
1 5
1 4
3 3
4 2
zzde
azbe
1 3
1 4
6 3
uwuwuw
wuwuwu
2 4
1 3
1 6
```

### 输出

```
0
1
0
2
2
1
1
0
```



---

---
title: "Outstanding Impressionist"
layout: "post"
diff: 普及-
pid: CF2053B
tag: ['前缀和', '构造']
---

# Outstanding Impressionist

## 题目描述

Eric 仍然记得整数数组形式的 $n$ 个印象。他将它们记录为 $w_1,w_2,\ldots,w_n$ 。然而，他对印象的记忆力很差。对于每个 $1\leq i\leq n$ ，他只能记住 $ l_i \leq w_i \leq r_i $ 。

Eric 认为，印象 $i$ 是唯一的，当且仅当存在一个可能的数组 $w_1,w_2,\ldots,w_n$ ，使得 $w_i\neq w_j$ 对所有具有 $j\neq i$ 的 $1\leq j\leq n$ 都成立。

请帮助 Eric 确定印象 $i$ 是否对每个 $1\leq i\leq n$ 是唯一的，对每个 $i$ 是独立的。也许你的判断可以帮助改写最后的故事。

## 输入格式

每个测试包含多个测试用例。输入的第一行包含一个整数 $t$（$1\leq t\leq 10^4$），表示测试用例的数量。测试用例的描述如下。

每个测试用例的第一行包含一个整数 $n$（$1\leq n\leq 2\cdot 10^5$），表示展示次数。

然后是 $n$ 行，第 $i$ 行包含两个整数 $l_i$和$r_i$（$1\leq l_i\leq r_i\leq2\cdot n$），表示$w_i$的最小可能值和最大可能值。

保证所有测试用例中 $n$ 的总和不超过$ 2\cdot 10^5 $。

## 输出格式

对于每个测试用例，输出一个长度为 $n$ 的二进制字符串 $s$：对于每个 $1\leq i\leq n$，印象 $i$ 是唯一的，则 $s_i=\texttt{1}$；否则，$s_i=\texttt{0}$。不要输出空格。

### 样例解释
在第一个测试用例中，唯一可能的数组 $w$ 是 $[1,1]$，这使得印象 $1$ 和 $2$ 都不是唯一的（因为 $w_1=w_2$）。

在第二个测试用例中，所有印象都可以是唯一的：

- 对于 $i=1$，我们可以将 $w$ 设置为 $[1,3,2,3]$，其中 $w_1\neq w_2$、$w_1\neq w_3$ 和 $w_1\neq w_4$；
- 对于 $i=2$，我们可以将 $w$ 设置为 $[2,3,1,2]$，其中 $w_2\neq w_1$、$w_2\neq w_3$ 和 $w_2\neq w_4$；
- 对于 $i=3$，我们可以将 $w$ 设置为 $[1,1,3,1]$；
- 对于 $i=4$，我们可以将 $w$ 设置为 $[2,3,1]$。

在第三个测试用例中，对于 $i=4$，我们可以将 $w$ 设置为 $[3,2,2,1,3,2]$。因此，印象 $4$ 是独一无二的。

by [sunny12888](https://www.luogu.com.cn/user/790275)

## 样例 #1

### 输入

```
5
2
1 1
1 1
4
1 3
1 3
1 3
1 3
6
3 6
2 2
1 2
1 1
3 4
2 2
7
3 4
4 4
4 4
1 3
2 5
1 4
2 2
3
4 5
4 4
5 5
```

### 输出

```
00
1111
100110
1001111
011
```



---

---
title: "Move to the End"
layout: "post"
diff: 普及-
pid: CF2104B
tag: ['前缀和']
---

# Move to the End

## 题目描述

给定一个由 $n$ 个整数组成的数组 $a$。

对于从 $1$ 到 $n$ 的每个整数 $k$，你需要执行以下操作：
1. 选择数组 $a$ 中的任意一个元素并将其移动到数组的最右端（可以选择最后一个元素，此时数组不会改变）；
2. 输出数组 $a$ 最后 $k$ 个元素的和；
3. 将第一步选择的元素移回其原始位置（恢复原始数组 $a$）。

对于每个 $k$，你需要选择移动的元素，使得输出的值尽可能大。

请计算每个 $k$ 对应的输出值。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例包含两行：
- 第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）；
- 第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le 10^9$）。

输入数据的额外约束：所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。


## 输出格式

对于每个测试用例，输出 $n$ 个整数。其中第 $i$ 个整数表示当 $k=i$ 时能够输出的最大值。


## 说明/提示

以题目描述中的第一个测试用例为例：
- 当 $k=1$ 时，可以选择将第 $6$ 个元素移动到末尾，数组变为 $[13, 5, 10, 14, 8, 13, 15]$，输出值为 $15$；
- 当 $k=2$ 时，可以选择将第 $6$ 个元素移动到末尾，数组变为 $[13, 5, 10, 14, 8, 13, 15]$，输出值为 $13 + 15 = 28$；
- 当 $k=3$ 时，可以选择将第 $4$ 个元素移动到末尾，数组变为 $[13, 5, 10, 8, 15, 13, 14]$，输出值为 $15 + 13 + 14 = 42$；
- 当 $k=4$ 时，可以选择将第 $5$ 个元素移动到末尾，数组变为 $[13, 5, 10, 14, 15, 13, 8]$，输出值为 $14 + 15 + 13 + 8 = 50$；
- 当 $k=5$ 时，可以选择将第 $1$ 个元素移动到末尾，数组变为 $[5, 10, 14, 8, 15, 13, 13]$，输出值为 $14 + 8 + 15 + 13 + 13 = 63$；
- 当 $k=6$ 时，可以选择将第 $1$ 个元素移动到末尾，数组变为 $[5, 10, 14, 8, 15, 13, 13]$，输出值为 $10 + 14 + 8 + 15 + 13 + 13 = 73$；
- 当 $k=7$ 时，可以选择将第 $6$ 个元素移动到末尾，数组变为 $[13, 5, 10, 14, 8, 13, 15]$，输出值为 $13 + 5 + 10 + 14 + 8 + 13 + 15 = 78$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
7
13 5 10 14 8 15 13
6
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
1
42
2
7 5
```

### 输出

```
15 28 42 50 63 73 78 
1000000000 2000000000 3000000000 4000000000 5000000000 6000000000 
42 
7 12
```



---

---
title: "Little Xor"
layout: "post"
diff: 普及-
pid: CF252A
tag: ['博弈论', '枚举', '前缀和']
---

# Little Xor

## 题目描述

Little Petya likes arrays that consist of non-negative integers a lot. Recently his mom has presented him one such array consisting of $ n $ elements. Petya immediately decided to find there a segment of consecutive elements, such that the $ xor $ of all numbers from this segment was maximal possible. Help him with that.

The $ xor $ operation is the bitwise exclusive "OR", that is denoted as "xor" in Pascal and "^" in C/C++/Java.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=100 $ ) — the number of elements in the array. The second line contains the space-separated integers from the array. All numbers are non-negative integers strictly less than $ 2^{30} $ .

## 输出格式

Print a single integer — the required maximal $ xor $ of a segment of consecutive elements.

## 说明/提示

In the first sample one of the optimal segments is the segment that consists of the first and the second array elements, if we consider the array elements indexed starting from one.

The second sample contains only one optimal segment, which contains exactly one array element (element with index three).

## 样例 #1

### 输入

```
5
1 2 1 1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
1 2 7

```

### 输出

```
7

```

## 样例 #3

### 输入

```
4
4 2 4 8

```

### 输出

```
14

```



---

---
title: "Before an Exam"
layout: "post"
diff: 普及-
pid: CF4B
tag: ['贪心', '优先队列', '前缀和']
---

# Before an Exam

## 题目描述

Tomorrow Peter has a Biology exam. He does not like this subject much, but $ d $ days ago he learnt that he would have to take this exam. Peter's strict parents made him prepare for the exam immediately, for this purpose he has to study not less than $ minTime_{i} $ and not more than $ maxTime_{i} $ hours per each $ i $ -th day. Moreover, they warned Peter that a day before the exam they would check how he has followed their instructions.

So, today is the day when Peter's parents ask him to show the timetable of his preparatory studies. But the boy has counted only the sum of hours $ sumTime $ spent him on preparation, and now he wants to know if he can show his parents a timetable $ sсhedule $ with $ d $ numbers, where each number $ sсhedule_{i} $ stands for the time in hours spent by Peter each $ i $ -th day on biology studies, and satisfying the limitations imposed by his parents, and at the same time the sum total of all $ schedule_{i} $ should equal to $ sumTime $ .

## 输入格式

The first input line contains two integer numbers $ d,sumTime $ ( $ 1<=d<=30,0<=sumTime<=240 $ ) — the amount of days, during which Peter studied, and the total amount of hours, spent on preparation. Each of the following $ d $ lines contains two integer numbers $ minTime_{i},maxTime_{i} $ ( $ 0<=minTime_{i}<=maxTime_{i}<=8 $ ), separated by a space — minimum and maximum amount of hours that Peter could spent in the $ i $ -th day.

## 输出格式

In the first line print YES, and in the second line print $ d $ numbers (separated by a space), each of the numbers — amount of hours, spent by Peter on preparation in the corresponding day, if he followed his parents' instructions; or print NO in the unique line. If there are many solutions, print any of them.

## 样例 #1

### 输入

```
1 48
5 7

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
2 5
0 1
3 5

```

### 输出

```
YES
1 4 
```



---

---
title: "Orchestra"
layout: "post"
diff: 普及-
pid: CF635A
tag: ['模拟', '枚举', '前缀和']
---

# Orchestra

## 题目描述

Paul is at the orchestra. The string section is arranged in an $ r×c $ rectangular grid and is filled with violinists with the exception of $ n $ violists. Paul really likes violas, so he would like to take a picture including at least $ k $ of them. Paul can take a picture of any axis-parallel rectangle in the orchestra. Count the number of possible pictures that Paul can take.

Two pictures are considered to be different if the coordinates of corresponding rectangles are different.

## 输入格式

The first line of input contains four space-separated integers $ r $ , $ c $ , $ n $ , $ k $ ( $ 1<=r,c,n<=10 $ , $ 1<=k<=n $ ) — the number of rows and columns of the string section, the total number of violas, and the minimum number of violas Paul would like in his photograph, respectively.

The next $ n $ lines each contain two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i}<=r $ , $ 1<=y_{i}<=c $ ): the position of the $ i $ -th viola. It is guaranteed that no location appears more than once in the input.

## 输出格式

Print a single integer — the number of photographs Paul can take which include at least $ k $ violas.

## 说明/提示

We will use '\*' to denote violinists and '\#' to denote violists.

In the first sample, the orchestra looks as follows

`<br></br>*#<br></br>**<br></br>` Paul can take a photograph of just the viola, the $ 1×2 $ column containing the viola, the $ 2×1 $ row containing the viola, or the entire string section, for $ 4 $ pictures total.In the second sample, the orchestra looks as follows

`<br></br>#*<br></br>*#<br></br>#*<br></br>` Paul must take a photograph of the entire section.In the third sample, the orchestra looks the same as in the second sample.

## 样例 #1

### 输入

```
2 2 1 1
1 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3 2 3 3
1 1
3 1
2 2

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 2 3 2
1 1
3 1
2 2

```

### 输出

```
4

```



---

---
title: "Intercepted Message"
layout: "post"
diff: 普及-
pid: CF950B
tag: ['贪心', '前缀和']
---

# Intercepted Message

## 题目描述

Hacker Zhorik wants to decipher two secret messages he intercepted yesterday. Yeah message is a sequence of encrypted blocks, each of them consists of several bytes of information.

Zhorik knows that each of the messages is an archive containing one or more files. Zhorik knows how each of these archives was transferred through the network: if an archive consists of $ k $ files of sizes $ l_{1},l_{2},...,l_{k} $ bytes, then the $ i $ -th file is split to one or more blocks $ b_{i,1},b_{i,2},...,b_{i,mi} $ (here the total length of the blocks $ b_{i,1}+b_{i,2}+...+b_{i,mi} $ is equal to the length of the file $ l_{i} $ ), and after that all blocks are transferred through the network, maintaining the order of files in the archive.

Zhorik thinks that the two messages contain the same archive, because their total lengths are equal. However, each file can be split in blocks in different ways in the two messages.

You are given the lengths of blocks in each of the two messages. Help Zhorik to determine what is the maximum number of files could be in the archive, if the Zhorik's assumption is correct.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 1<=n,m<=10^{5} $ ) — the number of blocks in the first and in the second messages.

The second line contains $ n $ integers $ x_{1},x_{2},...,x_{n} $ ( $ 1<=x_{i}<=10^{6} $ ) — the length of the blocks that form the first message.

The third line contains $ m $ integers $ y_{1},y_{2},...,y_{m} $ ( $ 1<=y_{i}<=10^{6} $ ) — the length of the blocks that form the second message.

It is guaranteed that $ x_{1}+...+x_{n}=y_{1}+...+y_{m} $ . Also, it is guaranteed that $ x_{1}+...+x_{n}<=10^{6} $ .

## 输出格式

Print the maximum number of files the intercepted array could consist of.

## 说明/提示

In the first example the maximum number of files in the archive is 3. For example, it is possible that in the archive are three files of sizes $ 2+5=7 $ , $ 15=3+1+11=8+2+4+1 $ and $ 4+4=8 $ .

In the second example it is possible that the archive contains two files of sizes $ 1 $ and $ 110=10+100=100+10 $ . Note that the order of files is kept while transferring archives through the network, so we can't say that there are three files of sizes $ 1 $ , $ 10 $ and $ 100 $ .

In the third example the only possibility is that the archive contains a single file of size $ 4 $ .

## 样例 #1

### 输入

```
7 6
2 5 3 1 11 4 4
7 8 2 4 1 8

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 3
1 10 100
1 100 10

```

### 输出

```
2

```

## 样例 #3

### 输入

```
1 4
4
1 1 1 1

```

### 输出

```
1

```



---

---
title: "Encryption (easy)"
layout: "post"
diff: 普及-
pid: CF958C1
tag: ['枚举', '前缀和']
---

# Encryption (easy)

## 题目描述

Rebel spy Heidi has just obtained the plans for the Death Star from the Empire and, now on her way to safety, she is trying to break the encryption of the plans (of course they are encrypted – the Empire may be evil, but it is not stupid!). The encryption has several levels of security, and here is how the first one looks.

Heidi is presented with a screen that shows her a sequence of integers $ A $ and a positive integer $ p $ . She knows that the encryption code is a single number $ S $ , which is defined as follows:

Define the score of $ X $ to be the sum of the elements of $ X $ modulo $ p $ .

Heidi is given a sequence $ A $ that consists of $ N $ integers, and also given an integer $ p $ . She needs to split $ A $ into $ 2 $ parts such that:

- Each part contains at least $ 1 $ element of $ A $ , and each part consists of contiguous elements of $ A $ .
- The two parts do not overlap.
- The total sum $ S $ of the scores of those two parts is maximized. This is the encryption code.

Output the sum $ S $ , which is the encryption code.

## 输入格式

The first line of the input contains two space-separated integer $ N $ and $ p $ ( $ 2<=N<=100000 $ , $ 2<=p<=10000 $ ) – the number of elements in $ A $ , and the modulo for computing scores, respectively.

The second line contains $ N $ space-separated integers which are the elements of $ A $ . Each integer is from the interval $ [1,1000000] $ .

## 输出格式

Output the number $ S $ as described in the problem statement.

## 说明/提示

In the first example, the score is maximized if the input sequence is split into two parts as $ (3,4) $ , $ (7,2) $ . It gives the total score of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/39bbc2e047bed6ad62ef40401430a139534974d3.png).

In the second example, the score is maximized if the first part consists of the first three elements, and the second part consists of the rest. Then, the score is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/d991bcec92c9c10d8e1b00b096112e99ba9e2d35.png).

## 样例 #1

### 输入

```
4 10
3 4 7 2

```

### 输出

```
16

```

## 样例 #2

### 输入

```
10 12
16 3 24 13 9 8 7 5 12 12

```

### 输出

```
13

```



---

