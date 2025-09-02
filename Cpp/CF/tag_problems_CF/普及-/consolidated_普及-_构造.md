---
title: "Binary String Constructing"
layout: "post"
diff: 普及-
pid: CF1003B
tag: ['模拟', '构造']
---

# Binary String Constructing

## 题目描述

给你 $3$ 个整数 $a$ ,$b$ ,$x$ ，让你求出一个包含了 $a$ 个 $0$，$b$ 个 $1$ 的二进制串 $s$。要求其中 $s_i\not =s_{i+1}$ 的对数正好等于 $x$。

## 输入格式

一行 $3$ 个整数 $a$ ,$b$ ,$x$。

## 输出格式

一行一个字符串 $s$ ,表示**任意**一符合要求的答案。

### 输入输出样例
无。

感谢 @win10 提供的翻译。

## 样例 #1

### 输入

```
2 2 1

```

### 输出

```
1100

```

## 样例 #2

### 输入

```
3 3 3

```

### 输出

```
101100

```

## 样例 #3

### 输入

```
5 3 6

```

### 输出

```
01010100

```



---

---
title: "Oh Those Palindromes"
layout: "post"
diff: 普及-
pid: CF1063A
tag: ['字符串', '概率论', '构造']
---

# Oh Those Palindromes

## 题目描述

一个非空字符串叫做回文串。如果它从左到右，从右到左读相同，那么它就是回文串。
例如，“ABCBA”,“A”和“ABBA”都是回文串，而“ABAB”和“XY”则不是。




如果可以通过从字符串的开头和结尾删除一些（可能为零）字符来从该字符串获得新字符串，
则新字符串叫做另一个字符串的子字符串。
例如，“ABC”、“AB”和“C”是字符串“ABC”的子串，而“AC”和“D”不是。


我们把字符串的“回文计数”定义为回文的子串个数。
例如，字符串“aaa”的回文计数是6，因为它的所有子字符串都是回文，
而字符串“abc”的回文计数是3，因为只有长度为1的子字符串是回文。


给你一个字符串S。你可以任意地重新排列它的字符，求它的回文计数最大值。

## 输入格式

第一行包含整数n（1≤n≤100000）表示字符串s的长度。




第二行包含字符串S，它由n个小写字母组成。

## 输出格式

输出字符串t，（它是字符串s的一种排列）
此外，t应该具有最大回文计数的可能值。




如果有多个这样的字符串，输出它们中的任何一个。

## 输入输出样例：
#### 输入样例#1：
```
5
oolol
```
#### 输出样例#1：
```
ololo
```

#### 输入样例#2：
```
16
gagadbcgghhchbdf
```
#### 输出样例#2：
```
16
gagadbcgghhchbdf
```

## 说明/提示

在第一个例子中，字符串“ololo”有9个9回文子串：
"o","l","o","l","o","olo","lol","olo","oloo"

注意，即使某些子串重合，它们也会在生成的字符串中计入多次。




在第二个例子中，字符串“abccbaghghghgdfd”的回文计数为29。

## 样例 #1

### 输入

```
5
oolol

```

### 输出

```
ololo

```

## 样例 #2

### 输入

```
16
gagadbcgghhchbdf

```

### 输出

```
abccbaghghghgdfd

```



---

---
title: "Make Even"
layout: "post"
diff: 普及-
pid: CF1611A
tag: ['字符串', '数学', '构造']
---

# Make Even

## 题目描述

Polycarp 有一个不包含数字 $0$ 的整数 $n$。他可以使用他的数字执行以下操作数次（可能为零）：

将 $n$ 的长度 $l\ (1 \leq l \leq |n|$，这里 $|n|$ 指 $n$ 的十进制长度 $)$ 的前缀反转，即反转 $n$ 的 前 $l$ 位数字。那么，第 $1$ 个数位（默认从左向右数，下文同理）将与第 $l$ 个数位交换，第 $2$ 个数位与第 $(l-1)$ 个交换......以此类推。

例如，如果 $n=123456789$ 且 $l=5$，则 $n$ 变换后的值将为 $543216789$。

对于不同的操作，$l$ 的值可能不同。

Polycarp 喜欢偶数，并且非常不耐烦。因此，他想用最少的操作次数使他的数字 $n$ 变成偶数。

**本题有多组数据。**

## 输入格式

第一行，一个整数 $t\ (1 \leq t \leq 10^4)$，表示数据的组数。

接下来 $t$ 行，每行一个数 $n\ (1 \leq n \leq 10^9)$。可以保证该数中各数位没有 $0$。

## 输出格式

共 $t$ 行，每行一个整数，表示将该数字变成偶数的最小操作次数。如果无论如何操作，都无法变为偶数，则输出 `-1`。

## 样例 #1

### 输入

```
4
3876
387
4489
3
```

### 输出

```
0
2
1
-1
```



---

---
title: "Special Permutation"
layout: "post"
diff: 普及-
pid: CF1612B
tag: ['构造']
---

# Special Permutation

## 题目描述

A permutation of length $ n $ is an array $ p=[p_1,p_2,\dots, p_n] $ which contains every integer from $ 1 $ to $ n $ (inclusive) exactly once. For example, $ p=[4, 2, 6, 5, 3, 1] $ is a permutation of length $ 6 $ .

You are given three integers $ n $ , $ a $ and $ b $ , where $ n $ is an even number. Print any permutation of length $ n $ that the minimum among all its elements of the left half equals $ a $ and the maximum among all its elements of the right half equals $ b $ . Print -1 if no such permutation exists.

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1 \le t \le 1000 $ ), the number of test cases in the test. The following $ t $ lines contain test case descriptions.

Each test case description contains three integers $ n $ , $ a $ , $ b $ ( $ 2 \le n \le 100 $ ; $ 1 \le a,b \le n $ ; $ a \ne b $ ), where $ n $ is an even number (i.e. $ n \bmod 2 = 0 $ ).

## 输出格式

For each test case, print a single line containing any suitable permutation. Print -1 no such permutation exists. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
7
6 2 5
6 1 3
6 4 3
4 2 4
10 5 3
2 1 2
2 2 1
```

### 输出

```
4 2 6 5 3 1
-1
6 4 5 1 3 2 
3 2 4 1 
-1
1 2 
2 1
```



---

---
title: "OKEA"
layout: "post"
diff: 普及-
pid: CF1634C
tag: ['构造']
---

# OKEA

## 题目描述

People worry that computers will get too smart and take over the world, but the real problem is that they're too stupid and they've already taken over the world.

— Pedro Domingos



You work for a well-known department store that uses leading technologies and employs mechanistic work — that is, robots!

The department you work in sells $ n \cdot k $ items. The first item costs $ 1 $ dollar, the second item costs $ 2 $ dollars, and so on: $ i $ -th item costs $ i $ dollars. The items are situated on shelves. The items form a rectangular grid: there are $ n $ shelves in total, and each shelf contains exactly $ k $ items. We will denote by $ a_{i,j} $ the price of $ j $ -th item (counting from the left) on the $ i $ -th shelf, $ 1 \le i \le n, 1 \le j \le k $ .

Occasionally robots get curious and ponder on the following question: what is the mean price (arithmetic average) of items $ a_{i,l}, a_{i,l+1}, \ldots, a_{i,r} $ for some shelf $ i $ and indices $ l \le r $ ? Unfortunately, the old robots can only work with whole numbers. If the mean price turns out not to be an integer, they break down.

You care about robots' welfare. You want to arrange the items in such a way that the robots cannot theoretically break. Formally, you want to choose such a two-dimensional array $ a $ that:

- Every number from $ 1 $ to $ n \cdot k $ (inclusively) occurs exactly once.
- For each $ i, l, r $ , the mean price of items from $ l $ to $ r $ on $ i $ -th shelf is an integer.

Find out if such an arrangement is possible, and if it is, give any example of such arrangement.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases.

The first and only line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 500 $ ) — the number of shelves and length of each shelf, respectively.

It is guaranteed that the sum $ n $ over all test cases does not exceed $ 500 $ and the sum $ k $ over all test cases does not exceed $ 500 $ .

## 输出格式

Print the answer for each test case.

If such an arrangement exists, print "YES" on a single line. After that, print any example on $ n $ lines of $ k $ numbers each, one line per shelf. Each number from $ 1 $ to $ n \cdot k $ must occur exactly once in the output.

If no good arrangement exists, print a single word "NO" on its own line.

## 样例 #1

### 输入

```
4
1 1
2 2
3 3
3 1
```

### 输出

```
YES
1 
YES
1 3 
2 4 
NO
YES
1 
2 
3
```



---

---
title: "GCD vs LCM"
layout: "post"
diff: 普及-
pid: CF1665A
tag: ['构造']
---

# GCD vs LCM

## 题目描述

本题有多测。  
给定一个正整数 $n$，求一组正整数 $a$, $b$, $c$, $d$，使得 $a+b+c+d=n$，并且 $\gcd(a,b) = \operatorname{lcm}(c,d)$。本题有 SPJ，求出任意一组即可。

## 输入格式

第一行一个正整数 $t$，表示测试数据组数，接下来 $t$ 行，每行一个正整数 $n$。

## 输出格式

对于每组数据，输出任意一组 $a$, $b$, $c$, $d$。数据保证一定有解。

## 说明/提示

$4\le n\le 10^9$  
$1\le t\le 10^4$

## 样例 #1

### 输入

```
5
4
7
8
9
10
```

### 输出

```
1 1 1 1
2 2 2 1
2 2 2 2
2 4 2 1
3 5 1 1
```



---

---
title: "Z mod X = C"
layout: "post"
diff: 普及-
pid: CF1684B
tag: ['数论', '构造']
---

# Z mod X = C

## 题目描述

给定三个整数 $a,b,c$，求三个整数 $x,y,z$，满足

$$x \bmod{y} =a$$
$$y \bmod{z} =b$$
$$z \bmod{x} =c$$

对于给定数据，保证答案存在。

## 输入格式

**本题有多组数据。**

第一行：一个整数 $t$，表示测试数据的组数。

第 $2$ 行至第 $t+1$ 行：每行三个整数 $a,b,c$，含义如上文所述。

## 输出格式

对于每组数据，输出三个整数 $x,y,z$ ($1 \le x, y, z \le 10^{18}$)，含义为上文所述。

如果有多组答案，输出任意一组即可。

## 说明/提示

$1 \le t \le 10^4$

$1 \le a < b < c \le 10^8$

## 样例 #1

### 输入

```
4
1 3 4
127 234 421
2 7 8
59 94 388
```

### 输出

```
12 11 4
1063 234 1484
25 23 8
2221 94 2609
```



---

---
title: "Perfect Permutation"
layout: "post"
diff: 普及-
pid: CF1711A
tag: ['构造']
---

# Perfect Permutation

## 题目描述

You are given a positive integer $ n $ .

The weight of a permutation $ p_1, p_2, \ldots, p_n $ is the number of indices $ 1\le i\le n $ such that $ i $ divides $ p_i $ . Find a permutation $ p_1,p_2,\dots, p_n $ with the minimum possible weight (among all permutations of length $ n $ ).

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 10^4 $ ). The description of the test cases follows.

The only line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the length of permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print a line containing $ n $ integers $ p_1, p_2,\dots, p_n $ so that the permutation $ p $ has the minimum possible weight.

If there are several possible answers, you can print any of them.

## 说明/提示

In the first test case, the only valid permutation is $ p=[1] $ . Its weight is $ 1 $ .

In the second test case, one possible answer is the permutation $ p=[2,1,4,3] $ . One can check that $ 1 $ divides $ p_1 $ and $ i $ does not divide $ p_i $ for $ i=2,3,4 $ , so the weight of this permutation is $ 1 $ . It is impossible to find a permutation of length $ 4 $ with a strictly smaller weight.

## 样例 #1

### 输入

```
2
1
4
```

### 输出

```
1
2 1 4 3
```



---

---
title: "Beautiful Array"
layout: "post"
diff: 普及-
pid: CF1715B
tag: ['构造']
---

# Beautiful Array

## 题目描述

Stanley defines the beauty of an array $ a $ of length $ n $ , which contains non-negative integers, as follows: $ $$$\sum\limits_{i = 1}^{n} \left \lfloor \frac{a_{i}}{k} \right \rfloor, $ $  which means that we divide each element by  $ k $ , round it down, and sum up the resulting values.</p><p>Stanley told Sam the integer  $ k $  and asked him to find an array  $ a $  of  $ n $  non-negative integers, such that the beauty is equal to  $ b $  and the sum of elements is equal to  $ s$$$. Help Sam — find any of the arrays satisfying the conditions above.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). Description of the test cases follows.

The first line of each test case contains integers $ n $ , $ k $ , $ b $ , $ s $ ( $ 1 \leq n \leq 10^{5} $ , $ 1 \leq k \leq 10^{9} $ , $ 0 \leq b \leq 10^{9} $ , $ 0 \leq s \leq 10^{18} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case print $ -1 $ if such array $ a $ does not exist. Otherwise print $ n $ non-negative integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_{i} \leq 10^{18} $ ) — the answer.

## 说明/提示

In the first, the second, the fifth and the sixth test cases of the example it is possible to show that such array does not exist.

In the third testcase of the example $ a = [0, 0, 19] $ . The sum of elements in it is equal to 19, the beauty of it is equal to $ \left ( \left \lfloor \frac{0}{6} \right \rfloor + \left \lfloor \frac{0}{6} \right \rfloor + \left \lfloor \frac{19}{6} \right \rfloor \right ) = (0 + 0 + 3) = 3 $ .

In the fourth testcase of the example $ a = [0, 3, 3, 3, 29] $ . The sum of elements in it is equal to $ 38 $ , the beauty of it is equal to $ (0 + 0 + 0 + 0 + 7) = 7 $ .

## 样例 #1

### 输入

```
8
1 6 3 100
3 6 3 12
3 6 3 19
5 4 7 38
5 4 7 80
99978 1000000000 100000000 1000000000000000000
1 1 0 0
4 1000000000 1000000000 1000000000000000000
```

### 输出

```
-1
-1
0 0 19
0 3 3 3 29
-1
-1
0
0 0 0 1000000000000000000
```



---

---
title: "Madoka and Underground Competitions"
layout: "post"
diff: 普及-
pid: CF1717B
tag: ['模拟', '构造']
---

# Madoka and Underground Competitions

## 题目描述

Madoka decided to participate in an underground sports programming competition. And there was exactly one task in it:

A square table of size $ n \times n $ , where  $ n $ is a multiple of $ k $ , is called good if only the characters '.' and 'X' are written in it, as well as in any subtable of size $ 1 \times k $ or $ k \times 1 $ , there is at least one character 'X'. In other words, among any $ k $ consecutive vertical or horizontal cells, there must be at least one containing the character 'X'.

Output any good table that has the minimum possible number of characters 'X', and also the symbol 'X' is written in the cell $ (r, c) $ . Rows are numbered from $ 1 $ to $ n $ from top to bottom, columns are numbered from $ 1 $ to $ n $ from left to right.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. Description of the test cases follows.

The first and the only line of each test case contains four integers $ n $ , $ k $ , $ r $ , $ c $ ( $ 1 \le n \le 500, 1 \le k \le n, 1 \le r, c \le n $ ) — the size of the table, the integer $ k $ and the coordinates of the cell, which must contain the character 'X'. It is guaranteed that $ n $ is a multiple of $ k $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, output $ n $ lines, each consisting of $ n $ characters '.' and 'X', — the desired table. If there are several answers, then you can output anyone.

## 说明/提示

Let's analyze the first test case.

The following tables can be printed as the correct answer:

 X....X.X. or ..XX...X. It can be proved that there cannot be less than $ 3 $ characters 'X' in the answer.Note that the following table is invalid because cell $ (3, 2) $ does not contain the character 'X':

 X...X...XIn the second test case, the only correct table is:

 XXXX Each subtable of size $ 1 \times 1 $ must contain a 'X' character, so all characters in the table must be equal to 'X'.

## 样例 #1

### 输入

```
3
3 3 3 2
2 1 1 2
6 3 4 2
```

### 输出

```
X..
..X
.X.
XX
XX
.X..X.
X..X..
..X..X
.X..X.
X..X..
..X..X
```



---

---
title: "Mathematical Circus"
layout: "post"
diff: 普及-
pid: CF1719B
tag: ['数论', '构造']
---

# Mathematical Circus

## 题目描述

A new entertainment has appeared in Buryatia — a mathematical circus! The magician shows two numbers to the audience — $ n $ and $ k $ , where $ n $ is even. Next, he takes all the integers from $ 1 $ to $ n $ , and splits them all into pairs $ (a, b) $ (each integer must be in exactly one pair) so that for each pair the integer $ (a + k) \cdot b $ is divisible by $ 4 $ (note that the order of the numbers in the pair matters), or reports that, unfortunately for viewers, such a split is impossible.

Burenka really likes such performances, so she asked her friend Tonya to be a magician, and also gave him the numbers $ n $ and $ k $ .

Tonya is a wolf, and as you know, wolves do not perform in the circus, even in a mathematical one. Therefore, he asks you to help him. Let him know if a suitable splitting into pairs is possible, and if possible, then tell it.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The following is a description of the input data sets.

The single line of each test case contains two integers $ n $ and $ k $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ , $ 0 \leq k \leq 10^9 $ , $ n $ is even) — the number of integers and the number being added $ k $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, first output the string "YES" if there is a split into pairs, and "NO" if there is none.

If there is a split, then in the following $ \frac{n}{2} $ lines output pairs of the split, in each line print $ 2 $ numbers — first the integer $ a $ , then the integer $ b $ .

## 说明/提示

In the first test case, splitting into pairs $ (1, 2) $ and $ (3, 4) $ is suitable, same as splitting into $ (1, 4) $ and $ (3, 2) $ .

In the second test case, $ (1 + 0) \cdot 2 = 1 \cdot (2 + 0) = 2 $ is not divisible by $ 4 $ , so there is no partition.

## 样例 #1

### 输入

```
4
4 1
2 0
12 10
14 11
```

### 输出

```
YES
1 2
3 4
NO
YES
3 4
7 8
11 12
2 1
6 5
10 9
YES
1 2
3 4
5 6
7 8
9 10
11 12
13 14
```



---

---
title: "Immobile Knight"
layout: "post"
diff: 普及-
pid: CF1739A
tag: ['构造']
---

# Immobile Knight

## 题目描述

There is a chess board of size $ n \times m $ . The rows are numbered from $ 1 $ to $ n $ , the columns are numbered from $ 1 $ to $ m $ .

Let's call a cell isolated if a knight placed in that cell can't move to any other cell on the board. Recall that a chess knight moves two cells in one direction and one cell in a perpendicular direction:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1739A/a0d7d8c62ba0d8d73d58490b8d2222f35ced96b2.png)Find any isolated cell on the board. If there are no such cells, print any cell on the board.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 64 $ ) — the number of testcases.

The only line of each testcase contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 8 $ ) — the number of rows and columns of the board.

## 输出格式

For each testcase, print two integers — the row and the column of any isolated cell on the board. If there are no such cells, print any cell on the board.

## 说明/提示

In the first testcase, all cells are isolated. A knight can't move from any cell of the board to any other one. Thus, any cell on board is a correct answer.

In the second testcase, there are no isolated cells. On a normal chess board, a knight has at least two moves from any cell. Thus, again, any cell is a correct answer.

In the third testcase, only the middle cell of the board is isolated. The knight can move freely around the border of the board, but can't escape the middle.

## 样例 #1

### 输入

```
3
1 7
8 8
3 3
```

### 输出

```
1 7
7 2
2 2
```



---

---
title: "Fedya and Array"
layout: "post"
diff: 普及-
pid: CF1793B
tag: ['构造']
---

# Fedya and Array

## 题目描述

For his birthday recently Fedya was given an array $ a $ of $ n $ integers arranged in a circle, For each pair of neighboring numbers ( $ a_1 $ and $ a_2 $ , $ a_2 $ and $ a_3 $ , $ \ldots $ , $ a_{n - 1} $ and $ a_n $ , $ a_n $ and $ a_1 $ ) the absolute difference between them is equal to $ 1 $ .

Let's call a local maximum an element, which is greater than both of its neighboring elements. Also call a local minimum an element, which is less than both of its neighboring elements. Note, that elements $ a_1 $ and $ a_n $ are neighboring elements.

Unfortunately, Fedya lost an array, but he remembered in it the sum of local maximums $ x $ and the sum of local minimums $ y $ .

Given $ x $ and $ y $ , help Fedya find any matching array of minimum length.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). Description of the test cases follows.

Each line of each test case contain two integers $ x $ and $ y $ ( $ -10^{9} \le y < x \le 10^{9} $ ) — the sum of local maximums and the sum of local minimums, respectively.

## 输出格式

For each test case, in the first line print one integer $ n $ — the minimum length of matching arrays.

In the second line print $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^{9} \leqslant a_i \leqslant 10^{9} $ ) — the array elements such that the the absolute difference between each pair of neighboring is equal to $ 1 $ .

If there are multiple solutions, print any of them.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^{5} $ .

## 说明/提示

In the first test case, the local maximums are the numbers at $ 3, 7 $ and $ 10 $ positions, and the local minimums are the numbers at $ 1, 6 $ and $ 8 $ positions. $ x = a_3 + a_7 + a_{10} = 2 + 0 + 1 = 3 $ , $ y = a_1 + a_6 + a_8 = 0 + (-1) + (-1) = -2 $ .

In the second test case, the local maximums are the numbers at $ 2 $ and $ 10 $ positions, and the local minimums are the numbers at $ 1 $ and $ 3 $ positions. $ x = a_2 + a_{10} = -1 + 5 = 4 $ , $ y = a_1 + a_3 = -2 + (-2) = -4 $ .

In the third test case, the local maximums are the numbers at $ 1 $ and $ 5 $ positions, and the local minimums are the numbers at $ 3 $ and $ 6 $ positions.

## 样例 #1

### 输入

```
4
3 -2
4 -4
2 -1
5 -3
```

### 输出

```
10
0 1 2 1 0 -1 0 -1 0 1
16
-2 -1 -2 -1 0 1 2 3 4 5 4 3 2 1 0 -1 
6
1 0 -1 0 1 0
16
2 3 2 1 0 -1 0 -1 0 -1 0 1 2 1 0 1
```



---

---
title: "Permutation Printing"
layout: "post"
diff: 普及-
pid: CF1930B
tag: ['数学', '构造']
---

# Permutation Printing

## 题目描述

You are given a positive integer $ n $ .

Find a permutation $ ^\dagger $ $ p $ of length $ n $ such that there do not exist two distinct indices $ i $ and $ j $ ( $ 1 \leq i, j < n $ ; $ i \neq j $ ) such that $ p_i $ divides $ p_j $ and $ p_{i+1} $ divides $ p_{j+1} $ .

Refer to the Notes section for some examples.

Under the constraints of this problem, it can be proven that at least one $ p $ exists.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \leq n \leq 10^5 $ ) — the length of the permutation $ p $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ p_1, p_2, \ldots, p_n $ .

If there are multiple solutions, you may output any one of them.

## 说明/提示

In the first test case, $ p=[4,1,2,3] $ is a valid permutation. However, the permutation $ p=[1,2,3,4] $ is not a valid permutation as we can choose $ i=1 $ and $ j=3 $ . Then $ p_1=1 $ divides $ p_3=3 $ and $ p_2=2 $ divides $ p_4=4 $ . Note that the permutation $ p=[3, 4, 2, 1] $ is also not a valid permutation as we can choose $ i=3 $ and $ j=2 $ . Then $ p_3=2 $ divides $ p_2=4 $ and $ p_4=1 $ divides $ p_3=2 $ .

In the second test case, $ p=[1,2,3] $ is a valid permutation. In fact, all $ 6 $ permutations of length $ 3 $ are valid.

## 样例 #1

### 输入

```
2
4
3
```

### 输出

```
4 1 2 3
1 2 3
```



---

---
title: "Exact Neighbours (Easy)"
layout: "post"
diff: 普及-
pid: CF1970B1
tag: ['构造']
---

# Exact Neighbours (Easy)

## 题目描述

The only difference between this and the hard version is that all $ a_{i} $ are even.

After some recent attacks on Hogwarts Castle by the Death Eaters, the Order of the Phoenix has decided to station $ n $ members in Hogsmead Village. The houses will be situated on a picturesque $ n\times n $ square field. Each wizard will have their own house, and every house will belong to some wizard. Each house will take up the space of one square.

However, as you might know wizards are very superstitious. During the weekends, each wizard $ i $ will want to visit the house that is exactly $ a_{i} $ $ (0 \leq a_{i} \leq n) $ away from their own house. The roads in the village are built horizontally and vertically, so the distance between points $ (x_{i}, y_{i}) $ and $ (x_{j}, y_{j}) $ on the $ n\times n $ field is $  |x_{i} - x_{j}| + |y_{i} - y_{j}| $ . The wizards know and trust each other, so one wizard can visit another wizard's house when the second wizard is away. The houses to be built will be big enough for all $ n $ wizards to simultaneously visit any house.

Apart from that, each wizard is mandated to have a view of the Hogwarts Castle in the north and the Forbidden Forest in the south, so the house of no other wizard should block the view. In terms of the village, it means that in each column of the $ n\times n $ field, there can be at most one house, i.e. if the $ i $ -th house has coordinates $ (x_{i}, y_{i}) $ , then $ x_{i} \neq x_{j} $ for all $ i \neq j $ .

The Order of the Phoenix doesn't yet know if it is possible to place $ n $ houses in such a way that will satisfy the visit and view requirements of all $ n $ wizards, so they are asking for your help in designing such a plan.

If it is possible to have a correct placement, where for the $ i $ -th wizard there is a house that is $ a_{i} $ away from it and the house of the $ i $ -th wizard is the only house in their column, output YES, the position of houses for each wizard, and to the house of which wizard should each wizard go during the weekends.

If it is impossible to have a correct placement, output NO.

## 输入格式

The first line contains $ n $ ( $ 2 \leq n \leq 2\cdot 10^{5} $ ), the number of houses to be built.

The second line contains $ n $ integers $ a_{1}, \ldots, a_{n} $ $ (0 \leq a_{i} \leq n) $ . All $ a_{i} $ are even.

## 输出格式

If there exists such a placement, output YES on the first line; otherwise, output NO.

If the answer is YES, output $ n + 1 $ more lines describing the placement.

The next $ n $ lines should contain the positions of the houses $ 1 \leq x_{i}, y_{i} \leq n $ for each wizard.

The $ i $ -th element of the last line should contain the index of the wizard, the house of which is exactly $ a_{i} $ away from the house of the $ i $ -th wizard. If there are multiple such wizards, you can output any.

If there are multiple house placement configurations, you can output any.

## 说明/提示

For the sample, the house of the 1st wizard is located at $ (4, 4) $ , of the 2nd at $ (1, 3) $ , of the 3rd at $ (2, 4) $ , of the 4th at $ (3, 1) $ .

The distance from the house of the 1st wizard to the house of the 1st wizard is $ |4 - 4| + |4 - 4| = 0 $ .

The distance from the house of the 2nd wizard to the house of the 1st wizard is $ |1 - 4| + |3 - 4| = 4 $ .

The distance from the house of the 3rd wizard to the house of the 1st wizard is $ |2 - 4| + |4 - 4| = 2 $ .

The distance from the house of the 4th wizard to the house of the 3rd wizard is $ |3 - 2| + |1 - 4| = 4 $ .

The view and the distance conditions are satisfied for all houses, so the placement is correct.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1970B1/9f9f415b711c20a1d43262d4b959c18fec467842.png)

## 样例 #1

### 输入

```
4
0 4 2 4
```

### 输出

```
YES
4 4
1 3
2 4
3 1
1 1 1 3
```



---

---
title: "Strange Splitting"
layout: "post"
diff: 普及-
pid: CF1984A
tag: ['构造']
---

# Strange Splitting

## 题目描述

给你一个非空序列$a$，这个序列的范围是这个序列的最大值减去最小值（这里的范围有特殊含义，不是“数据范围”的“范围”）。  
举个例子：$[1,4,2]$的“范围”就是$4-1=3$。  
介于这个之上,$a$长度为$n$（$n>=3$）。  
你可以给这个序列中的一个元素标记为：红色$red$蓝色$blue$中的任意一种。  
要求：  

- 将这个序列$a$分为两个序列，一个序列的元素为$a$序列中所有背涂成红色$red$的元素，另一个序列为$a$序列中所有被涂成蓝色$blue$的元素，要保证**这两个序列的“范围”不相等**。  
- 每个元素都要被涂上颜色。  

如果没有能满足上面要求的涂色方法，输出```NO```。  
如果有多种涂色方法，你可以输出其中的任意一种。  
**注：如果有符合要求的涂色方法，先输出```YES```然后换行!!!**

具体见样例......

## 输入格式

本题有$t$组数据。  
第一行一个整数$t$($1<=t<=100$)。  
每组数据包含一个整数$n$($3<=n<=50$)，和$n$个元素$a_i$（$1<=a_i<=10^9$）。

## 输出格式

如果没有符合要求的涂色方法，只用输出```NO```。  
如果有多种方案（或$1$种）：  
需要用到 $Special Judge$  

先输出一个```YES```（换行），接着输出一种，或多种方案。  
如果这个方案的$a_i$被涂成了红色$red$，则输出```R```，如果是蓝色$blue$，输出```B```(不带空格）。

翻译提供：feizhu0130

## 样例 #1

### 输入

```
7
4
1 1 2 2
5
1 2 3 4 5
3
3 3 3
4
1 2 2 2
3
1 2 2
3
1 1 2
3
1 9 84
```

### 输出

```
YES
RBRR
YES
BBRBB
NO
YES
RBBR
YES
RRB
YES
BRR
YES
BRB
```



---

---
title: "Generate Permutation"
layout: "post"
diff: 普及-
pid: CF2001B
tag: ['构造']
---

# Generate Permutation

## 题目描述

There is an integer sequence $ a $ of length $ n $ , where each element is initially $ -1 $ .

Misuki has two typewriters where the first one writes letters from left to right, with a pointer initially pointing to $ 1 $ , and another writes letters from right to left with a pointer initially pointing to $ n $ .

Misuki would choose one of the typewriters and use it to perform the following operations until $ a $ becomes a permutation of $ [1, 2, \ldots, n] $

- write number: write the minimum positive integer that isn't present in the array $ a $ to the element $ a_i $ , $ i $ is the position where the pointer points at. Such operation can be performed only when $ a_i = -1 $ .
- carriage return: return the pointer to its initial position (i.e. $ 1 $ for the first typewriter, $ n $ for the second)
- move pointer: move the pointer to the next position, let $ i $ be the position the pointer points at before this operation, if Misuki is using the first typewriter, $ i := i + 1 $ would happen, and $ i := i - 1 $ otherwise. Such operation can be performed only if after the operation, $ 1 \le i \le n $ holds.

Your task is to construct any permutation $ p $ of length $ n $ , such that the minimum number of carriage return operations needed to make $ a = p $ is the same no matter which typewriter Misuki is using.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a line of $ n $ integers, representing the permutation $ p $ of length $ n $ such that the minimum number of carriage return operations needed to make $ a = p $ is the same no matter which typewriter Misuki is using, or $ -1 $ if it is impossible to do so.

If there are multiple valid permutations, you can output any of them.

## 说明/提示

In the first testcase, it's possible to make $ a = p = [1] $ using $ 0 $ carriage return operations.

In the second testcase, it is possible to make $ a = p = [1, 2] $ with the minimal number of carriage returns as follows:

If Misuki is using the first typewriter:

- Write number: write $ 1 $ to $ a_1 $ , $ a $ becomes $ [1, -1] $
- Move pointer: move the pointer to the next position. (i.e. $ 2 $ )
- Write number: write $ 2 $ to $ a_2 $ , $ a $ becomes $ [1, 2] $

If Misuki is using the second typewriter:

- Move pointer: move the pointer to the next position. (i.e. $ 1 $ )
- Write number: write $ 1 $ to $ a_1 $ , $ a $ becomes $ [1, -1] $
- Carriage return: return the pointer to $ 2 $ .
- Write number: write $ 2 $ to $ a_2 $ , $ a $ becomes $ [1, 2] $

It can be proven that the minimum number of carriage returns needed to transform $ a $ into $ p $ when using the first typewriter is $ 0 $ and it is $ 1 $ when using the second one, so this permutation is not valid.

Similarly, $ p = [2, 1] $ is also not valid, so there is no solution for $ n = 2 $ .

In the third testcase, it is possibile to make $ a = p = [3, 1, 2] $ with $ 1 $ carriage return with both the first and the second typewriter. It can be proven that, for both typewriters, it is impossible to write $ p $ with $ 0 $ carriage returns.

With the first typewriter it is possible to:

- Move pointer: move the pointer to the next position. (i.e. $ 2 $ )
- Write number: write $ 1 $ to $ a_2 $ , $ a $ becomes $ [-1, 1, -1] $
- Move pointer: move the pointer to the next position. (i.e. $ 3 $ )
- Write number: write $ 2 $ to $ a_3 $ , $ a $ becomes $ [-1, 1, 2] $
- Carriage return: return the pointer to $ 1 $ .
- Write number: write $ 3 $ to $ a_1 $ , $ a $ becomes $ [3,1,2] $

With the second typewriter it is possible to:

- Move pointer: move the pointer to the next position. (i.e. $ 2 $ )
- Write number: write $ 1 $ to $ a_2 $ , $ a $ becomes $ [-1, 1, -1] $
- Carriage return: return the pointer to $ 3 $ .
- Write number: write $ 2 $ to $ a_3 $ , $ a $ becomes $ [-1, 1, 2] $
- Move pointer: move the pointer to the next position. (i.e. $ 2 $ )
- Move pointer: move the pointer to the next position. (i.e. $ 1 $ )
- Write number: write $ 3 $ to $ a_1 $ , $ a $ becomes $ [3, 1, 2] $

## 样例 #1

### 输入

```
3
1
2
3
```

### 输出

```
1
-1
3 1 2
```



---

---
title: "Medians"
layout: "post"
diff: 普及-
pid: CF2032B
tag: ['构造']
---

# Medians

## 题目描述

You are given an array $ a = [1, 2, \ldots, n] $ , where $ n $ is odd, and an integer $ k $ .

Your task is to choose an odd positive integer $ m $ and to split $ a $ into $ m $ subarrays $ ^{\dagger} $ $ b_1, b_2, \ldots, b_m $ such that:

- Each element of the array $ a $ belongs to exactly one subarray.
- For all $ 1 \le i \le m $ , $ |b_i| $ is odd, i.e., the length of each subarray is odd.
- $ \operatorname{median}([\operatorname{median}(b_1), \operatorname{median}(b_2), \ldots, \operatorname{median}(b_m)]) = k $ , i.e., the median $ ^{\ddagger} $ of the array of medians of all subarrays must equal $ k $ . $ \operatorname{median}(c) $ denotes the median of the array $ c $ .

 $ ^{\dagger} $ A subarray of the array $ a $ of length $ n $ is the array $ [a_l, a_{l + 1}, \ldots, a_r] $ for some integers $ 1 \le l \le r \le n $ .

 $ ^{\ddagger} $ A median of the array of odd length is the middle element after the array is sorted in non-decreasing order. For example: $ \operatorname{median}([1,2,5,4,3]) = 3 $ , $ \operatorname{median}([3,2,1]) = 2 $ , $ \operatorname{median}([2,1,2,1,2,2,2]) = 2 $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 5000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le k \le n < 2 \cdot 10^5 $ , $ n $ is odd) — the length of array $ a $ and the desired median of the array of medians of all subarrays.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case:

- If there is no suitable partition, output $ -1 $ in a single line.
- Otherwise, in the first line, output an odd integer $ m $ ( $ 1 \le m \le n $ ), and in the second line, output $ m $ distinct integers $ p_1, p_2 , p_3 , \ldots, p_m $ ( $ 1 = p_1 < p_2 < p_3 < \ldots < p_m \le n $ ) — denoting the left borders of each subarray.

In detail, for a valid answer $ [p_1, p_2, \ldots, p_m] $ :

- $ b_1 = \left[ a_{p_1}, a_{p_1 + 1}, \ldots, a_{p_2 - 1} \right] $
- $ b_2 = \left[ a_{p_2}, a_{p_2 + 1}, \ldots, a_{p_3 - 1} \right] $
- $ \ldots $
- $ b_m = \left[ a_{p_m}, a_{p_m + 1}, \ldots, a_n \right] $ .

If there are multiple solutions, you can output any of them.

## 说明/提示

In the first test case, the given partition has $ m = 1 $ and $ b_1 = [1] $ . It is obvious that $ \operatorname{median}([\operatorname{median}([1])]) = \operatorname{median}([1]) = 1 $ .

In the second test case, the given partition has $ m = 3 $ and:

- $ b_1 = [1] $
- $ b_2 = [2] $
- $ b_3 = [3] $

Therefore, $ \operatorname{median}([\operatorname{median}([1]), \operatorname{median}([2]), \operatorname{median}([3])]) = \operatorname{median}([1, 2, 3]) = 2 $ .

In the third test case, there is no valid partition for $ k = 3 $ .

In the fourth test case, the given partition has $ m = 5 $ and:

- $ b_1 = [1, 2, 3] $
- $ b_2 = [4, 5, 6] $
- $ b_3 = [7, 8, 9] $
- $ b_4 = [10, 11, 12] $
- $ b_5 = [13, 14, 15] $

Therefore, $ \operatorname{median}([\operatorname{median}([1, 2, 3]), \operatorname{median}([4, 5, 6]), \operatorname{median}([7, 8, 9]), \operatorname{median}([10, 11, 12]), \operatorname{median}([13, 14, 15])]) = \operatorname{median}([2, 5, 8, 11, 14]) = 8 $ .

## 样例 #1

### 输入

```
4
1 1
3 2
3 3
15 8
```

### 输出

```
1
1
3
1 2 3
-1
5
1 4 7 10 13
```



---

---
title: "Everyone Loves Tres"
layout: "post"
diff: 普及-
pid: CF2035B
tag: ['数论', '构造']
---

# Everyone Loves Tres

## 题目描述

There are 3 heroes and 3 villains, so 6 people in total.



Given a positive integer $ n $ . Find the smallest integer whose decimal representation has length $ n $ and consists only of $ 3 $ s and $ 6 $ s such that it is divisible by both $ 33 $ and $ 66 $ . If no such integer exists, print $ -1 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 500 $ ) — the number of test cases.

The only line of each test case contains a single integer $ n $ ( $ 1\le n\le 500 $ ) — the length of the decimal representation.

## 输出格式

For each test case, output the smallest required integer if such an integer exists and $ -1 $ otherwise.

## 说明/提示

For $ n=1 $ , no such integer exists as neither $ 3 $ nor $ 6 $ is divisible by $ 33 $ .

For $ n=2 $ , $ 66 $ consists only of $ 6 $ s and it is divisible by both $ 33 $ and $ 66 $ .

For $ n=3 $ , no such integer exists. Only $ 363 $ is divisible by $ 33 $ , but it is not divisible by $ 66 $ .

For $ n=4 $ , $ 3366 $ and $ 6666 $ are divisible by both $ 33 $ and $ 66 $ , and $ 3366 $ is the smallest.

## 样例 #1

### 输入

```
6
1
2
3
4
5
7
```

### 输出

```
-1
66
-1
3366
36366
3336366
```



---

---
title: "Shohag Loves Mod"
layout: "post"
diff: 普及-
pid: CF2039A
tag: ['数论', '构造']
---

# Shohag Loves Mod

## 题目描述

Shohag 有一个整数 $n$，请帮助他找到一个升序序列 $1\le a_1< a_2<\cdots<a_n\le100$，使得对于所有满足 $1\le i < j \le n$ 的数对 $(i,j)$，都满足 $a_i \bmod i\neq a_j \bmod j$。

可以证明，在给定限制下，一定存在合法的序列。

$a\bmod b$ 表示 $a$ 除以 $b$ 的余数。比如，$7\bmod 3=1, 8\bmod 4=0, 69\bmod 10=9$。

## 输入格式

第一行，一个整数 $t$（$1\le t\le 50$） 表示数据组数。

对于每组数据，输入一行，一个整数 $n$（$2\le n\le 50$）。

## 输出格式

对于每组数据，输出 $n$ 个整数，表示符合题目条件的一个序列。如果有多个符合条件的序列，输出任意一个即可。

翻译：[HYdroKomide](https://www.luogu.com.cn/user/299883)

## 样例 #1

### 输入

```
2
3
6
```

### 输出

```
2 7 8
2 3 32 35 69 95
```



---

---
title: "Beautiful Array"
layout: "post"
diff: 普及-
pid: CF2041E
tag: ['数学', '构造']
---

# Beautiful Array

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041E/123e9f2378be455eca9fba5ff4bfa308ab2b1a77.png) Image generated by ChatGPT 4o.A-Ming's birthday is coming and his friend A-May decided to give him an integer array as a present. A-Ming has two favorite numbers $ a $ and $ b $ , and he thinks an array is beautiful if its mean is exactly $ a $ and its median is exactly $ b $ . Please help A-May find a beautiful array so her gift can impress A-Ming.

The mean of an array is its sum divided by its length. For example, the mean of array $ [3, -1, 5, 5] $ is $ 12 \div 4 = 3 $ .

The median of an array is its middle element after sorting if its length is odd, or the mean of two middle elements after sorting if its length is even. For example, the median of $ [1, 1, 2, 4, 8] $ is $ 2 $ and the median of $ [3, -1, 5, 5] $ is $ (3 + 5) \div 2 = 4 $ .

Note that the mean and median are not rounded to an integer. For example, the mean of array $ [1, 2] $ is $ 1.5 $ .

## 输入格式

The only line contains two integers $ a $ and $ b $ .

- $ -100 \leq a, b \leq 100 $ .
- The length of the array must be between $ 1 $ and $ 1000 $ .
- The elements of the array must be integers and their absolute values must not exceed $ 10^6 $ .

## 输出格式

In the first line, print the length of the array.

In the second line, print the elements of the array.

If there are multiple solutions, you can print any. It can be proved that, under the constraints of the problem, a solution always exists.

## 样例 #1

### 输入

```
3 4
```

### 输出

```
4
3 -1 5 5
```

## 样例 #2

### 输入

```
-100 -100
```

### 输出

```
1
-100
```



---

---
title: "Kevin and Permutation"
layout: "post"
diff: 普及-
pid: CF2048B
tag: ['构造']
---

# Kevin and Permutation

## 题目描述

### 题意
给定 $n,k$，构造一个长度为 $n$ 序列 $a$ 使得
$$\sum^{n-k+1}_{i=1}\left(\min^{i+k-1}_{j=i}a_j\right)$$
的值尽量小。其中，$a$ 满足各项均不相等。

请注意，共有 $t$ 次询问。

## 输入格式

每组数据包含 $t$ 次询问。

第 $1$ 行，一个正整数 $t$。

第 $2\sim t+1$ 行，每行两个正整数 $n,k$。

## 输出格式

输出共 $t$ 行。

每行输出 $n$ 个整数表示满足题目条件的序列。如果有多个答案，可以输出其中任何一个。
### 样例解释
在样例的第一组数据中，$n=4,k=2$。考虑所有长度为 $2$ 的子数组：$p_1,p_2$ 的最小值为 $1$，$p_2,p_3$ 的最小值为 $1$，$p_3,p_4$ 的最小值为 $k=2$。在所有可能的排列组合中，和 $1+1+2=4$ 是最小的。

在第二组数据中，所有长度为 $1$ 的子数组的最小值为 $5,2,1,6,4,3$。总和 $5+2+1+6+4+3=21$ 最小。

## 说明/提示

$1\le t\le10^3,1\le k\le n\le10^5$。

保证所有数据中 $\sum n\le 10^5$。

## 样例 #1

### 输入

```
3
4 2
6 1
8 3
```

### 输出

```
3 1 2 4
5 2 1 6 4 3
4 6 2 8 3 1 5 7
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
title: "Perfecto"
layout: "post"
diff: 普及-
pid: CF2071B
tag: ['数学', '构造']
---

# Perfecto

## 题目描述

若一个长度为 $n$ 的排列 $p$ $^{\text{∗}}$ 满足：对于每个下标 $i$（$1 \le i \le n$），前 $i$ 个元素的和 $p_1 + p_2 + \ldots + p_i$ 不是完全平方数 $^{\text{†}}$，则称该排列为完美排列。

你需要构造完美排列。给定正整数 $n$，找出一个长度为 $n$ 的完美排列，若不存在则输出 $-1$。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是排列，但 $[1,2,2]$ 不是排列（数字 $2$ 重复出现），$[1,3,4]$ 也不是排列（当 $n=3$ 时出现数字 $4$）。

$^{\text{†}}$ 完全平方数是指某个整数的平方，例如 $9=3^2$ 是完全平方数，但 $8$ 和 $14$ 不是。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各个测试用例的描述。

每个测试用例仅包含一行，包含一个整数 $n$（$1 \le n \le 5 \cdot 10^5$）。

保证所有测试用例的 $n$ 之和不超过 $10^6$。

## 输出格式

对于每个测试用例：

- 若无解，输出单个整数 $-1$；
- 否则，输出 $n$ 个整数 $p_1,p_2,\ldots,p_n$ —— 你找到的完美排列。

若存在多个解，输出任意一个即可。

## 说明/提示

第一个测试用例中，当 $n = 1$ 时唯一可能的排列是 $p = [1]$，但它不满足完美条件：
- $p_1 = 1 = x^2$（当 $x = 1$ 时成立）。

第二个测试用例中，当 $n = 4$ 时一个可能的完美排列是 $p = [2, 4, 1, 3]$：
- $p_1 = 2 \neq x^2$；
- $p_1 + p_2 = 2 + 4 = 6 \neq x^2$；
- $p_1 + p_2 + p_3 = 2 + 4 + 1 = 7 \neq x^2$；
- $p_1 + p_2 + p_3 + p_4 = 2 + 4 + 1 + 3 = 10 \neq x^2$。

第三个测试用例中，当 $n = 5$ 时一个可能的完美排列是 $p = [5, 1, 4, 3, 2]$：
- $p_1 = 5 \neq x^2$；
- $p_1 + p_2 = 5 + 1 = 6 \neq x^2$；
- $p_1 + p_2 + p_3 = 5 + 1 + 4 = 10 \neq x^2$；
- $p_1 + p_2 + p_3 + p_4 = 5 + 1 + 4 + 3 = 13 \neq x^2$；
- $p_1 + p_2 + p_3 + p_4 + p_5 = 5 + 1 + 4 + 3 + 2 = 15 \neq x^2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
1
4
5
```

### 输出

```
-1
2 4 1 3
5 1 4 3 2
```



---

---
title: "Combination Lock"
layout: "post"
diff: 普及-
pid: CF2091C
tag: ['数学', '构造']
---

# Combination Lock

## 题目描述

在 IT Campus "NEIMARK" 中，有几个开发重大编程竞赛题目的绝密房间。要进入其中一个房间，必须通过选择正确的密码来解锁一个圆形锁。该密码每天更新一次。

今天的密码是一个从 $1$ 到 $n$ 的排列$$$^{\text{∗}}$$$，且满足其每个循环位移$$$^{\text{†}}$$$中恰好有一个固定点。也就是说，在每一个循环位移中，存在且仅存在一个元素，其值等于它在排列中的位置。

请输出任意一个满足此条件的有效排列。请注意，有效的排列可能不存在，此时请输出 $-1$。

$$$^{\text{∗}}$$$排列的定义是一个长度为 $n$ 的序列，包含从 $1$ 到 $n$ 的整数，且每个数字恰好出现一次。例如，$(2\ 1\ 3)$、$(1)$、$(4\ 3\ 1\ 2)$ 是排列；而 $(1\ 2\ 2)$、$(3)$、$(1\ 3\ 2\ 5)$ 不是排列。

$$$^{\text{†}}$$$数组的循环位移是指将最后一个元素移动到数组开头得到的数组。一个长度为 $n$ 的排列恰好有 $n$ 个循环位移。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ($1 \leq t \leq 500$)。接下来是每个测试用例的描述。

每个测试用例单独一行，包含一个整数 $n$ ($1 \leq n \leq 2 \cdot 10^5$)。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。


## 输出格式

对于每个测试用例，输出满足条件的排列。如果存在多个解，输出任意一个即可。如果不存在符合条件的排列，输出 $-1$。


## 说明/提示

在第二个样例中，存在一个排列使得每个循环位移中都有一个固定点（用深红色标出）：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091C/97f07d8865b709e2ac05cf6cf0c154be7dc52ee5.png)  
第一行表示元素的位置编号，第二行展示了目标排列的所有循环位移。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4
5
3
```

### 输出

```
-1
4 1 3 5 2
1 3 2
```



---

---
title: "Lady Bug"
layout: "post"
diff: 普及-
pid: CF2092B
tag: ['贪心', '构造']
---

# Lady Bug

## 题目描述

当 Dasha Purova 刚越过法国边境时，反派 Markaron 绑架了她并将她关押在其城堡下的监狱中。幸运的是，神奇的 Lady Bug 得知 Dasha 的消息后立即赶往 Markaron 的城堡营救她。然而，她需要破解一个复杂密码才能进入。

该密码由两个长度为 $n$ 的比特字符串 $a$ 和 $b$ 组成。Lady Bug 在一次操作中可以选择任意索引 $2 \leq i \leq n$ 并执行以下两种操作之一：

1. 交换($a_i$, $b_{i-1}$)（交换 $a_i$ 和 $b_{i-1}$ 的值），或  
2. 交换($b_i$, $a_{i-1}$)（交换 $b_i$ 和 $a_{i-1}$ 的值）。

Lady Bug 可以进行任意次数的操作。若她能使第一个字符串 $a$ 仅由 0 组成，则视为密码破解成功。请帮助她判断是否能成功营救 Dasha。

## 输入格式

每个测试包含多个测试用例。输入数据第一行包含一个整数 $t$ ($1 \leq t \leq 10^4$) —— 测试用例数量。接下来是测试用例描述。

每个测试用例的第一行包含一个整数 $n$ ($2 \leq n \leq 2 \cdot 10^5$) —— 密码比特字符串的长度。

接下来两行各包含一个长度为 $n$ 的比特字符串 $a$ 和 $b$，表示密码。每个字符串仅包含字符 0 和 1。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，若 Lady Bug 能通过任意次操作破解密码，则输出 "YES"；否则输出 "NO"。

可以以任意大小写形式输出每个字母。例如，"yEs"、"yes"、"Yes" 和 "YES" 均会被接受为肯定答案。

## 说明/提示

第一个测试用例中，字符串 $a$ 本身已全为 0。

第二个测试用例中，一种可能的操作序列为：

1. 交换$(a_2, b_{1})$  
  $$$\mathtt{0{\color{red}{1}}0001}$$$  
  $$$\mathtt{{\color{red}{0}}10111}$$$
2. 交换$(b_5, a_{4})$  
  $$$\mathtt{000{\color{red}{0}}01}$$$  
  $$$\mathtt{1101{\color{red}{1}}1}$$$
3. 交换$(a_4, b_{3})$  
  $$$\mathtt{000{\color{red}{1}}01}$$$  
  $$$\mathtt{11{\color{red}{0}}101}$$$
4. 交换$(a_5, b_{4})$  
  $$$\mathtt{00000{\color{red}{1}}}$$$  
  $$$\mathtt{1111{\color{red}{0}}1}$$$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3
000
000
6
010001
010111
5
10000
01010
2
11
00
```

### 输出

```
YES
YES
NO
YES
```



---

---
title: "St. Chroma"
layout: "post"
diff: 普及-
pid: CF2106B
tag: ['贪心', '构造']
---

# St. Chroma

## 题目描述

给定一个长度为 $n$ 的排列$^{\text{∗}}$ $p$，其中包含从 $0$ 到 $n-1$ 的所有整数，以及一条包含 $n$ 个单元格的彩带。圣·克罗玛会将彩带的第 $i$ 个单元格涂成颜色 $\operatorname{MEX}(p_1, p_2, ..., p_i)$ $^{\text{†}}$。

例如，假设 $p = [1, 0, 3, 2]$。那么，圣·克罗玛会按照以下方式为彩带的单元格上色：$[0, 2, 2, 4]$。

现在给定两个整数 $n$ 和 $x$。由于圣·克罗玛特别喜爱颜色 $x$，请构造一个排列 $p$，使得彩带中被涂成颜色 $x$ 的单元格数量最大化。

$^{\text{∗}}$ 长度为 $n$ 的排列是指包含从 $0$ 到 $n-1$ 所有整数且每个整数恰好出现一次的序列。例如，$[0, 3, 1, 2]$ 是一个排列，但 $[1, 2, 0, 1]$ 不是（因为 $1$ 出现了两次），$[1, 3, 2]$ 也不是（因为缺少 $0$）。

$^{\text{†}}$ 序列的 $\operatorname{MEX}$ 定义为该序列中缺失的最小非负整数。例如，$\operatorname{MEX}(1, 3, 0, 2) = 4$，而 $\operatorname{MEX}(3, 1, 2) = 0$。

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 4000$）——测试用例的数量。

每个测试用例的唯一一行包含两个整数 $n$ 和 $x$（$1 \le n \le 2 \cdot 10^5$，$0 \le x \le n$）——分别表示单元格数量和需要最大化的颜色编号。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

输出一个长度为 $n$ 的排列 $p$，使得彩带中被涂成颜色 $x$ 的单元格数量最大化。如果存在多个满足条件的排列，输出其中任意一个即可。


## 说明/提示

第一个样例已在题目描述中解释。可以证明，$2$ 是被涂成颜色 $2$ 的单元格的最大可能数量。注意，另一个正确的答案可以是排列 $[0, 1, 3, 2]$。

在第二个样例中，排列给出的涂色结果为 $[0, 0, 0, 4]$，因此有 $3$ 个单元格被涂成颜色 $0$，这可以被证明是最大值。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
4 2
4 0
5 0
1 1
3 3
1 0
4 3
```

### 输出

```
1 0 3 2
2 3 1 0
3 2 4 1 0
0
0 2 1
0
1 2 0 3
```



---

---
title: "Permutation Warm-Up"
layout: "post"
diff: 普及-
pid: CF2108A
tag: ['构造']
---

# Permutation Warm-Up

## 题目描述

对于一个长度为 $n ^{\text{∗}}$ 的排列 $p$，我们定义函数：

$$ f(p) = \sum_{i=1}^{n} \lvert p_i - i \rvert $$

给定一个数字 $n$。你需要计算当考虑从 $1$ 到 $n$ 的所有可能排列时，函数 $f(p)$ 可以取到多少个不同的值。

$ ^{\text{∗}}$ 一个长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（$2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（$n=3$ 但数组中出现了 $4$）。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 100$）。接下来是测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 500$）——排列中数字的个数。


## 输出格式

对于每个测试用例，输出一个整数——给定排列长度下函数 $f(p)$ 的不同值的数量。


## 说明/提示

考虑输入的前两个例子。

对于 $n = 2$，只有 $2$ 个排列——$[1, 2]$ 和 $[2, 1]$。$f([1, 2]) = \lvert 1 - 1 \rvert + \lvert 2 - 2 \rvert = 0$，$f([2, 1]) = \lvert 2 - 1 \rvert + \lvert 1 - 2 \rvert = 1 + 1 = 2$。因此，函数有 $2$ 个不同的取值。

对于 $n=3$，已经有 $6$ 个排列：$[1, 2, 3]$、$[1, 3, 2]$、$[2, 1, 3]$、$[2, 3, 1]$、$[3, 1, 2]$、$[3, 2, 1]$，对应的函数值分别为 $0$、$2$、$2$、$4$、$4$ 和 $4$，总共有 $3$ 个不同的取值。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2
3
8
15
43
```

### 输出

```
2
3
17
57
463
```



---

---
title: "Good Start"
layout: "post"
diff: 普及-
pid: CF2113B
tag: ['数学', '构造']
---

# Good Start

## 题目描述

The roof is a rectangle of size $ w \times h $ with the bottom left corner at the point $ (0, 0) $ on the plane. Your team needs to completely cover this roof with identical roofing sheets of size $ a \times b $ , with the following conditions:

- The sheets cannot be rotated (not even by $ 90^\circ $ ).
- The sheets must not overlap (but they can touch at the edges).
- The sheets can extend beyond the boundaries of the rectangular roof.

A novice from your team has already placed two such sheets on the roof in such a way that the sheets do not overlap and each of them partially covers the roof.

Your task is to determine whether it is possible to completely tile the roof without removing either of the two already placed sheets.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains four integers $ w $ , $ h $ , $ a $ , and $ b $ ( $ 1 \le w, h, a, b \le 10^9 $ ) — the dimensions of the roof and the dimensions of the roofing sheets, respectively.

The second line of each test case contains four integers $ x_1 $ , $ y_1 $ , $ x_2 $ , and $ y_2 $ ( $ -a + 1 \le x_1, x_2 \le w - 1, -b + 1 \le y_1, y_2 \le h - 1 $ ) — the coordinates of the bottom left corners of the already placed roofing sheets. It is guaranteed that these sheets do not overlap.

## 输出格式

For each test case, output "Yes" (without quotes) if it is possible to completely tile the roof without removing either of the two already placed tiles, and "No" (without quotes) otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, it is possible to add $ 8 $ roofing sheets as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113B/93f36282728350193810dfbfa6e6dfdf291648d2.png)In the second test case, it is impossible to completely tile the roof:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113B/cebcd94b71d8b7130f37fb6e9fd22f74c727960b.png)

## 样例 #1

### 输入

```
7
6 5 2 3
-1 -2 5 4
4 4 2 2
0 0 3 1
10 9 3 2
0 0 4 3
10 9 3 2
0 0 6 3
5 5 2 2
-1 -1 4 -1
5 5 2 2
-1 -1 2 3
7 8 2 4
0 0 0 5
```

### 输出

```
Yes
No
No
Yes
No
Yes
No
```



---

---
title: "Game"
layout: "post"
diff: 普及-
pid: CF49D
tag: ['模拟', '构造']
---

# Game

## 题目描述

Vasya and Petya have invented a new game. Vasya takes a stripe consisting of $ 1×n $ square and paints the squares black and white. After that Petya can start moves — during a move he may choose any two neighboring squares of one color and repaint these two squares any way he wants, perhaps in different colors. Petya can only repaint the squares in white and black colors. Petya’s aim is to repaint the stripe so that no two neighboring squares were of one color. Help Petya, using the given initial coloring, find the minimum number of moves Petya needs to win.

## 输入格式

The first line contains number $ n $ ( $ 1<=n<=1000 $ ) which represents the stripe’s length. The second line contains exactly $ n $ symbols — the line’s initial coloring. 0 corresponds to a white square, 1 corresponds to a black one.

## 输出格式

If Petya cannot win with such an initial coloring, print -1. Otherwise print the minimum number of moves Petya needs to win.

## 说明/提示

In the first sample Petya can take squares 1 and 2. He repaints square 1 to black and square 2 to white.

In the second sample Petya can take squares 2 and 3. He repaints square 2 to white and square 3 to black.

## 样例 #1

### 输入

```
6
111010

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
10001

```

### 输出

```
1

```

## 样例 #3

### 输入

```
7
1100010

```

### 输出

```
2

```

## 样例 #4

### 输入

```
5
00100

```

### 输出

```
2

```



---

---
title: "3-palindrome"
layout: "post"
diff: 普及-
pid: CF805B
tag: ['字符串', '构造']
---

# 3-palindrome

## 题目描述

题意
给定n，求长度为n的以'a','b'或'c'构成的字符串，使得其中不存在长为3的回文子串（如"abc","abca"均符合，但"aba"不符），并使'c'的个数尽可能少

## 输入格式

第一行输入一个整数n（1<=n<=2*10^5）为字符串长度

## 输出格式

输出一个满足要求的字符串，若有多个任选一个输出
翻译提供者：mxy1

## 样例 #1

### 输入

```
2

```

### 输出

```
aa

```

## 样例 #2

### 输入

```
3

```

### 输出

```
bba

```



---

---
title: "A Prosperous Lot"
layout: "post"
diff: 普及-
pid: CF934B
tag: ['贪心', '构造']
---

# A Prosperous Lot

## 题目描述

Apart from Nian, there is a daemon named Sui, which terrifies children and causes them to become sick. Parents give their children money wrapped in red packets and put them under the pillow, so that when Sui tries to approach them, it will be driven away by the fairies inside.

Big Banban is hesitating over the amount of money to give out. He considers loops to be lucky since it symbolizes unity and harmony.

He would like to find a positive integer $ n $ not greater than $ 10^{18} $ , such that there are exactly $ k $ loops in the decimal representation of $ n $ , or determine that such $ n $ does not exist.

A loop is a planar area enclosed by lines in the digits' decimal representation written in Arabic numerals. For example, there is one loop in digit $ 4 $ , two loops in $ 8 $ and no loops in $ 5 $ . Refer to the figure below for all exact forms.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF934B/ef09358ad2ff9bd7af31e67d589f7cc1105bcc74.png)

## 输入格式

The first and only line contains an integer $ k $ ( $ 1<=k<=10^{6} $ ) — the desired number of loops.

## 输出格式

Output an integer — if no such $ n $ exists, output -1; otherwise output any such $ n $ . In the latter case, your output should be a positive decimal integer not exceeding $ 10^{18} $ .

## 样例 #1

### 输入

```
2

```

### 输出

```
462
```

## 样例 #2

### 输入

```
6

```

### 输出

```
8080
```



---

