---
title: "Multicolored Markers"
layout: "post"
diff: 普及+/提高
pid: CF1029F
tag: ['数学', '枚举']
---

# Multicolored Markers

## 题目描述

There is an infinite board of square tiles. Initially all tiles are white.

Vova has a red marker and a blue marker. Red marker can color $ a $ tiles. Blue marker can color $ b $ tiles. If some tile isn't white then you can't use marker of any color on it. Each marker must be drained completely, so at the end there should be exactly $ a $ red tiles and exactly $ b $ blue tiles across the board.

Vova wants to color such a set of tiles that:

- they would form a rectangle, consisting of exactly $ a+b $ colored tiles;
- all tiles of at least one color would also form a rectangle.

Here are some examples of correct colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/4e60c629e360885141e5179d3d4cdaf35671b392.png)Here are some examples of incorrect colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/8bb11d3a5c5094b0326713ae6edbddbecf3531f0.png)Among all correct colorings Vova wants to choose the one with the minimal perimeter. What is the minimal perimeter Vova can obtain?

It is guaranteed that there exists at least one correct coloring.

## 输入格式

A single line contains two integers $ a $ and $ b $ ( $ 1 \le a, b \le 10^{14} $ ) — the number of tiles red marker should color and the number of tiles blue marker should color, respectively.

## 输出格式

Print a single integer — the minimal perimeter of a colored rectangle Vova can obtain by coloring exactly $ a $ tiles red and exactly $ b $ tiles blue.

It is guaranteed that there exists at least one correct coloring.

## 说明/提示

The first four examples correspond to the first picture of the statement.

Note that for there exist multiple correct colorings for all of the examples.

In the first example you can also make a rectangle with sides $ 1 $ and $ 8 $ , though its perimeter will be $ 18 $ which is greater than $ 8 $ .

In the second example you can make the same resulting rectangle with sides $ 3 $ and $ 4 $ , but red tiles will form the rectangle with sides $ 1 $ and $ 3 $ and blue tiles will form the rectangle with sides $ 3 $ and $ 3 $ .

## 样例 #1

### 输入

```
4 4

```

### 输出

```
12

```

## 样例 #2

### 输入

```
3 9

```

### 输出

```
14

```

## 样例 #3

### 输入

```
9 3

```

### 输出

```
14

```

## 样例 #4

### 输入

```
3 6

```

### 输出

```
12

```

## 样例 #5

### 输入

```
506 2708

```

### 输出

```
3218

```



---

---
title: "Divisors"
layout: "post"
diff: 普及+/提高
pid: CF1033D
tag: ['数学', '枚举', '素数判断,质数,筛法']
---

# Divisors

## 题目描述

You are given $ n $ integers $ a_1, a_2, \ldots, a_n $ . Each of $ a_i $ has between $ 3 $ and $ 5 $ divisors. Consider $ a = \prod a_i $ — the product of all input integers. Find the number of divisors of $ a $ . As this number may be very large, print it modulo prime number $ 998244353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 500 $ ) — the number of numbers.

Each of the next $ n $ lines contains an integer $ a_i $ ( $ 1 \leq a_i \leq 2\cdot 10^{18} $ ). It is guaranteed that the number of divisors of each $ a_i $ is between $ 3 $ and $ 5 $ .

## 输出格式

Print a single integer $ d $ — the number of divisors of the product $ a_1 \cdot a_2 \cdot \dots \cdot a_n $ modulo $ 998244353 $ .

Hacks input

For hacks, the input needs to be provided in a special format.

The first line contains an integer $ n $ ( $ 1 \leq n \leq 500 $ ) — the number of numbers.

Each of the next $ n $ lines contains a prime factorization of $ a_i $ . The line contains an integer $ k_i $ ( $ 2 \leq k_i \leq 4 $ ) — the number of prime factors of $ a_i $ and $ k_i $ integers $ p_{i,j} $ ( $ 2 \leq p_{i,j} \leq 2 \cdot 10^{18} $ ) where $ p_{i,j} $ is the $ j $ -th prime factor of $ a_i $ .

Before supplying the input to the contestant, $ a_i = \prod p_{i,j} $ are calculated. Note that each $ p_{i,j} $ must be prime, each computed $ a_i $ must satisfy $ a_i \leq 2\cdot10^{18} $ and must have between $ 3 $ and $ 5 $ divisors. The contestant will be given only $ a_i $ , and not its prime factorization.

For example, you need to use this test to get the first sample:

`<br></br>3<br></br>2 3 3<br></br>2 3 5<br></br>2 11 13<br></br>`Interaction

From the technical side, this problem is interactive. Therefore, do not forget to output end of line and flush the output. Also, do not read more than you need. To flush the output, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

## 说明/提示

In the first case, $ a = 19305 $ . Its divisors are $ 1, 3, 5, 9, 11, 13, 15, 27, 33, 39, 45, 55, 65, 99, 117, 135, 143, 165, 195, 297, 351, 429, 495, 585, 715, 1287, 1485, 1755, 2145, 3861, 6435, 19305 $ — a total of $ 32 $ .

In the second case, $ a $ has four divisors: $ 1 $ , $ 86028121 $ , $ 86028157 $ , and $ 7400840699802997  $ .

In the third case $ a = 202600445671925364698739061629083877981962069703140268516570564888699 375209477214045102253766023072401557491054453690213483547 $ .

In the fourth case, $ a=512=2^9 $ , so answer equals to $ 10 $ .

## 样例 #1

### 输入

```
3
9
15
143
```

### 输出

```
32
```

## 样例 #2

### 输入

```
1
7400840699802997

```

### 输出

```
4
```

## 样例 #3

### 输入

```
8 
4606061759128693
4606066102679989
4606069767552943
4606063116488033
4606063930903637
4606064745319241
4606063930904021
4606065559735517
```

### 输出

```
1920
```

## 样例 #4

### 输入

```
3
4
8
16

```

### 输出

```
10

```



---

---
title: "Palindrome-less Arrays"
layout: "post"
diff: 普及+/提高
pid: CF1140E
tag: ['组合数学']
---

# Palindrome-less Arrays

## 题目描述

Let's denote that some array $ b $ is bad if it contains a subarray $ b_l, b_{l+1}, \dots, b_{r} $ of odd length more than $ 1 $ ( $ l < r $ and $ r - l + 1 $ is odd) such that $ \forall i \in \{0, 1, \dots, r - l\} $ $ b_{l + i} = b_{r - i} $ .

If an array is not bad, it is good.

Now you are given an array $ a_1, a_2, \dots, a_n $ . Some elements are replaced by $ -1 $ . Calculate the number of good arrays you can obtain by replacing each $ -1 $ with some integer from $ 1 $ to $ k $ .

Since the answer can be large, print it modulo $ 998244353 $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2 \le n, k \le 2 \cdot 10^5 $ ) — the length of array $ a $ and the size of "alphabet", i. e., the upper bound on the numbers you may use to replace $ -1 $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ a_i = -1 $ or $ 1 \le a_i \le k $ ) — the array $ a $ .

## 输出格式

Print one integer — the number of good arrays you can get, modulo $ 998244353 $ .

## 样例 #1

### 输入

```
2 3
-1 -1

```

### 输出

```
9

```

## 样例 #2

### 输入

```
5 2
1 -1 -1 1 2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
5 3
1 -1 -1 1 2

```

### 输出

```
2

```

## 样例 #4

### 输入

```
4 200000
-1 -1 12345 -1

```

### 输出

```
735945883

```



---

---
title: "Electrification"
layout: "post"
diff: 普及+/提高
pid: CF1175C
tag: ['数学', '二分']
---

# Electrification

## 题目描述

At first, there was a legend related to the name of the problem, but now it's just a formal statement.

You are given $ n $ points $ a_1, a_2, \dots, a_n $ on the $ OX $ axis. Now you are asked to find such an integer point $ x $ on $ OX $ axis that $ f_k(x) $ is minimal possible.

The function $ f_k(x) $ can be described in the following way:

- form a list of distances $ d_1, d_2, \dots, d_n $ where $ d_i = |a_i - x| $ (distance between $ a_i $ and $ x $ );
- sort list $ d $ in non-descending order;
- take $ d_{k + 1} $ as a result.

If there are multiple optimal answers you can print any of them.

## 输入格式

The first line contains single integer $ T $ ( $  1 \le T \le 2 \cdot 10^5 $ ) — number of queries. Next $ 2 \cdot T $ lines contain descriptions of queries. All queries are independent.

The first line of each query contains two integers $ n $ , $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le k < n $ ) — the number of points and constant $ k $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_1 < a_2 < \dots < a_n \le 10^9 $ ) — points in ascending order.

It's guaranteed that $ \sum{n} $ doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

Print $ T $ integers — corresponding points $ x $ which have minimal possible value of $ f_k(x) $ . If there are multiple answers you can print any of them.

## 样例 #1

### 输入

```
3
3 2
1 2 5
2 1
1 1000000000
1 0
4

```

### 输出

```
3
500000000
4

```



---

---
title: "Nick and Array"
layout: "post"
diff: 普及+/提高
pid: CF1180B
tag: ['数学', '贪心']
---

# Nick and Array

## 题目描述

Nick had received an awesome array of integers $ a=[a_1, a_2, \dots, a_n] $ as a gift for his $ 5 $ birthday from his mother. He was already going to explore its various properties but after unpacking he was disappointed a lot because the product $ a_1 \cdot a_2 \cdot \dots a_n $ of its elements seemed to him not large enough.

He was ready to throw out the array, but his mother reassured him. She told him, that array would not be spoiled after the following operation: choose any index $ i $ ( $ 1 \le i \le n $ ) and do $ a_i := -a_i - 1 $ .

For example, he can change array $ [3, -1, -4, 1] $ to an array $ [-4, -1, 3, 1] $ after applying this operation to elements with indices $ i=1 $ and $ i=3 $ .

Kolya had immediately understood that sometimes it's possible to increase the product of integers of the array a lot. Now he has decided that he wants to get an array with the maximal possible product of integers using only this operation with its elements (possibly zero, one or more times, as many as he wants), it is not forbidden to do this operation several times for the same index.

Help Kolya and print the array with the maximal possible product of elements $ a_1 \cdot a_2 \cdot \dots a_n $ which can be received using only this operation in some order.

If there are multiple answers, print any of them.

## 输入格式

The first line contains integer $ n $ ( $ 1 \leq n \leq 10^{5} $ ) — number of integers in the array.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^{6} \leq a_i \leq 10^{6} $ ) — elements of the array

## 输出格式

Print $ n $ numbers — elements of the array with the maximal possible product of elements which can be received using only this operation in some order from the given array.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
4
2 2 2 2

```

### 输出

```
-3 -3 -3 -3 
```

## 样例 #2

### 输入

```
1
0

```

### 输出

```
0 
```

## 样例 #3

### 输入

```
3
-3 -3 2

```

### 输出

```
-3 -3 2 
```



---

---
title: "Deleting Divisors"
layout: "post"
diff: 普及+/提高
pid: CF1537D
tag: ['数学']
---

# Deleting Divisors

## 题目描述

Alice and Bob are playing a game.

They start with a positive integer $ n $ and take alternating turns doing operations on it. Each turn a player can subtract from $ n $ one of its divisors that isn't $ 1 $ or $ n $ . The player who cannot make a move on his/her turn loses. Alice always moves first.

Note that they subtract a divisor of the current number in each turn.

You are asked to find out who will win the game if both players play optimally.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Then $ t $ test cases follow.

Each test case contains a single integer $ n $ ( $ 1 \leq n \leq 10^9 $ ) — the initial number.

## 输出格式

For each test case output "Alice" if Alice will win the game or "Bob" if Bob will win, if both players play optimally.

## 说明/提示

In the first test case, the game ends immediately because Alice cannot make a move.

In the second test case, Alice can subtract $ 2 $ making $ n = 2 $ , then Bob cannot make a move so Alice wins.

In the third test case, Alice can subtract $ 3 $ so that $ n = 9 $ . Bob's only move is to subtract $ 3 $ and make $ n = 6 $ . Now, Alice can subtract $ 3 $ again and $ n = 3 $ . Then Bob cannot make a move, so Alice wins.

## 样例 #1

### 输入

```
4
1
4
12
69
```

### 输出

```
Bob
Alice
Alice
Bob
```



---

---
title: "Up the Strip (simplified version)"
layout: "post"
diff: 普及+/提高
pid: CF1561D1
tag: ['数学', '递推']
---

# Up the Strip (simplified version)

## 题目描述

This version of the problem differs from the next one only in the constraint on $ n $ .

Note that the memory limit in this problem is lower than in others.

You have a vertical strip with $ n $ cells, numbered consecutively from $ 1 $ to $ n $ from top to bottom.

You also have a token that is initially placed in cell $ n $ . You will move the token up until it arrives at cell $ 1 $ .

Let the token be in cell $ x > 1 $ at some moment. One shift of the token can have either of the following kinds:

- Subtraction: you choose an integer $ y $ between $ 1 $ and $ x-1 $ , inclusive, and move the token from cell $ x $ to cell $ x - y $ .
- Floored division: you choose an integer $ z $ between $ 2 $ and $ x $ , inclusive, and move the token from cell $ x $ to cell $ \lfloor \frac{x}{z} \rfloor $ ( $ x $ divided by $ z $ rounded down).

Find the number of ways to move the token from cell $ n $ to cell $ 1 $ using one or more shifts, and print it modulo $ m $ . Note that if there are several ways to move the token from one cell to another in one shift, all these ways are considered distinct (check example explanation for a better understanding).

## 输入格式

The only line contains two integers $ n $ and $ m $ ( $ 2 \le n \le 2 \cdot 10^5 $ ; $ 10^8 < m < 10^9 $ ; $ m $ is a prime number) — the length of the strip and the modulo.

## 输出格式

Print the number of ways to move the token from cell $ n $ to cell $ 1 $ , modulo $ m $ .

## 说明/提示

In the first test, there are three ways to move the token from cell $ 3 $ to cell $ 1 $ in one shift: using subtraction of $ y = 2 $ , or using division by $ z = 2 $ or $ z = 3 $ .

There are also two ways to move the token from cell $ 3 $ to cell $ 1 $ via cell $ 2 $ : first subtract $ y = 1 $ , and then either subtract $ y = 1 $ again or divide by $ z = 2 $ .

Therefore, there are five ways in total.

## 样例 #1

### 输入

```
3 998244353
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5 998244353
```

### 输出

```
25
```

## 样例 #3

### 输入

```
42 998244353
```

### 输出

```
793019428
```



---

---
title: "Tyler and Strings"
layout: "post"
diff: 普及+/提高
pid: CF1648C
tag: ['树状数组', '组合数学']
---

# Tyler and Strings

## 题目描述

While looking at the kitchen fridge, the little boy Tyler noticed magnets with symbols, that can be aligned into a string $ s $ .

Tyler likes strings, and especially those that are lexicographically smaller than another string, $ t $ . After playing with magnets on the fridge, he is wondering, how many distinct strings can be composed out of letters of string $ s $ by rearranging them, so that the resulting string is lexicographically smaller than the string $ t $ ? Tyler is too young, so he can't answer this question. The alphabet Tyler uses is very large, so for your convenience he has already replaced the same letters in $ s $ and $ t $ to the same integers, keeping that different letters have been replaced to different integers.

We call a string $ x $ lexicographically smaller than a string $ y $ if one of the followings conditions is fulfilled:

- There exists such position of symbol $ m $ that is presented in both strings, so that before $ m $ -th symbol the strings are equal, and the $ m $ -th symbol of string $ x $ is smaller than $ m $ -th symbol of string $ y $ .
- String $ x $ is the prefix of string $ y $ and $ x \neq y $ .

Because the answer can be too large, print it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 200\,000 $ ) — the lengths of strings $ s $ and $ t $ respectively.

The second line contains $ n $ integers $ s_1, s_2, s_3, \ldots, s_n $ ( $ 1 \le s_i \le 200\,000 $ ) — letters of the string $ s $ .

The third line contains $ m $ integers $ t_1, t_2, t_3, \ldots, t_m $ ( $ 1 \le t_i \le 200\,000 $ ) — letters of the string $ t $ .

## 输出格式

Print a single number — the number of strings lexicographically smaller than $ t $ that can be obtained by rearranging the letters in $ s $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the strings we are interested in are $ [1\, 2\, 2] $ and $ [2\, 1\, 2] $ . The string $ [2\, 2\, 1] $ is lexicographically larger than the string $ [2\, 1\, 2\, 1] $ , so we don't count it.

In the second example, all strings count except $ [4\, 3\, 2\, 1] $ , so the answer is $ 4! - 1 = 23 $ .

In the third example, only the string $ [1\, 1\, 1\, 2] $ counts.

## 样例 #1

### 输入

```
3 4
1 2 2
2 1 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 4
1 2 3 4
4 3 2 1
```

### 输出

```
23
```

## 样例 #3

### 输入

```
4 3
1 1 1 2
1 1 2
```

### 输出

```
1
```



---

---
title: "Very Suspicious"
layout: "post"
diff: 普及+/提高
pid: CF1670D
tag: ['数学']
---

# Very Suspicious

## 题目描述

Sehr Sus is an infinite hexagonal grid as pictured below, controlled by MennaFadali, ZerooCool and Hosssam.

They love equilateral triangles and want to create $ n $ equilateral triangles on the grid by adding some straight lines. The triangles must all be empty from the inside (in other words, no straight line or hexagon edge should pass through any of the triangles).

You are allowed to add straight lines parallel to the edges of the hexagons. Given $ n $ , what is the minimum number of lines you need to add to create at least $ n $ equilateral triangles as described?

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1670D/5491a1c977b08c3202f038f487f2a32d813abedc.png)Adding two red lines results in two new yellow equilateral triangles.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases. Then $ t $ test cases follow.

Each test case contains a single integer $ n $ ( $ 1 \le n \le 10^{9} $ ) — the required number of equilateral triangles.

## 输出格式

For each test case, print the minimum number of lines needed to have $ n $ or more equilateral triangles.

## 说明/提示

In the first and second test cases only 2 lines are needed. After adding the first line, no equilateral triangles will be created no matter where it is added. But after adding the second line, two more triangles will be created at once.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1670D/22d6faf1616d600d29aaaff5a040ccd6f3af5678.png)In the third test case, the minimum needed is 3 lines as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1670D/2b991947c4bc515f58f281666fad74ef0d33ed67.png)

## 样例 #1

### 输入

```
4
1
2
3
4567
```

### 输出

```
2
2
3
83
```



---

---
title: "Lost Arithmetic Progression"
layout: "post"
diff: 普及+/提高
pid: CF1673D
tag: ['数学']
---

# Lost Arithmetic Progression

## 题目描述

很久以前，你想到了两个有限的[等差级数](https://baike.baidu.com/item/%E7%AD%89%E5%B7%AE%E7%BA%A7%E6%95%B0) $A$ 和 $B$。然后你发现另一个序列 $C$ 包含了 $A$ 和 $B$ 的所有公有元素。不难看出， $C$ 也是一个有限等差数列。

许多年后，你忘记了 $A$ 是什么，但还记得 $B$ 数列和 $C$ 数列。出于某种原因，你决心找到这个丢失的等差数列。在你开始这个永恒搜索之前，你想知道有多少个不同的有限等差数列可以作为你丢失的数列 $A$。

如果两个等差数列的第一项、公差数或项数不同，则认为它们不同。

有可能有无限多这样的数列，在这种情况下，你不需要尝试找到它们！你只要直接输出 $-1$。

即使它们的数量有限，答案也可能非常大。你只需要求对 $10^9+7$ 取模的答案。

## 输入格式

第一行包含一个整数 $t$ $(1\leq t\leq 100)$，表示测试用例的数量。

每个测试用例的第一行包含三个整数 $b$、$q$ 和 $y$ $(-10^9 \leq b \leq 10^9$、$1 \leq q \leq 10^9$、$2 \leq y \leq 10^9)$，分别表示 $b$ 的第一项、公约数和项数。

每个测试用例的第二行包含三个整数 $c$、$r$ 和 $z$ $(-10^9 \leq c \leq 10^9$、$1 \leq r \leq 10^9$、$2 \leq z \leq 10^9)$，分别表示 $c$ 的第一项、公差和项数。

## 输出格式

对于每个测试用例，打印包含单个整数的一行。

如果有无限多个有限等差数列可能是你忘记的数列 $A$，打印 $-1$。

否则，打印有限等差数列的数量，这可能是你忘记的数列 $A$ $%$ $10^9+7$。特别地，如果没有这样的有限等差数列，则输出 $0$。

## 说明/提示

对于第一个测试用例，$B=\{-3,-2,-1,0,1,2,3\}$、$C=\{-1,1,3,5\}$，不存在等差数列 $A$，因为 $5$ 不存在于 $B$ 中，所以 $5$ 也不应该存在于 $C$ 中。

对于第二个测试用例，$B=\{-9,-6,-3,0,3,6,9,12,15,18,21\}$、$C=\{0,6,12\}$，有 $10$ 个可能的等差数列 $A$：

- $\{0,6,12\}$
- $\{0,2,4,6,8,10,12\}$
- $\{0,2,4,6,8,10,12,14\}$
- $\{0,2,4,6,8,10,12,14,16\}$
- $\{-2,0,2,4,6,8,10,12\}$
- $\{-2,0,2,4,6,8,10,12,14\}$
- $\{-2,0,2,4,6,8,10,12,14,16\}$
- $\{-4,-2,0,2,4,6,8,10,12\}$
- $\{-4,-2,0,2,4,6,8,10,12,14\}$
- $\{-4,-2,0,2,4,6,8,10,12,14,16\}$

对于第三个测试用例，$B=\{2,7,12,17,22\}$、$C=\{7,12,17,22\}$，有无限多个可能的等差数列 $A$：

- $ \{7,12,17,22\} $
- $ \{7,12,17,22,27\} $
- $ \{7,12,17,22,27,32\} $
- $ \{7,12,17,22,27,32,37\} $
- $ \{7,12,17,22,27,32,37,42\} $
- $ \ldots $

## 样例 #1

### 输入

```
8
-3 1 7
-1 2 4
-9 3 11
0 6 3
2 5 5
7 5 4
2 2 11
10 5 3
0 2 9
2 4 3
-11 4 12
1 12 2
-27 4 7
-17 8 2
-8400 420 1000000000
0 4620 10
```

### 输出

```
0
10
-1
0
-1
21
0
273000
```



---

---
title: "LIS or Reverse LIS?"
layout: "post"
diff: 普及+/提高
pid: CF1682C
tag: ['数学', '构造']
---

# LIS or Reverse LIS?

## 题目描述

You are given an array $ a $ of $ n $ positive integers.

Let $ \text{LIS}(a) $ denote the length of [longest strictly increasing subsequence](https://en.wikipedia.org/wiki/Longest_increasing_subsequence) of $ a $ . For example,

- $ \text{LIS}([2, \underline{1}, 1, \underline{3}]) $ = $ 2 $ .
- $ \text{LIS}([\underline{3}, \underline{5}, \underline{10}, \underline{20}]) $ = $ 4 $ .
- $ \text{LIS}([3, \underline{1}, \underline{2}, \underline{4}]) $ = $ 3 $ .

We define array $ a' $ as the array obtained after reversing the array $ a $ i.e. $ a' = [a_n, a_{n-1}, \ldots , a_1] $ .

The beauty of array $ a $ is defined as $ min(\text{LIS}(a),\text{LIS}(a')) $ .

Your task is to determine the maximum possible beauty of the array $ a $ if you can rearrange the array $ a $ arbitrarily.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ $ (1 \leq t \leq 10^4) $ — the number of test cases. Description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (1 \leq n \leq 2\cdot 10^5) $ — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2, \ldots ,a_n $ $ (1 \leq a_i \leq 10^9) $ — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum possible beauty of $ a $ after rearranging its elements arbitrarily.

## 说明/提示

In the first test case, $ a $ = $ [6, 6, 6] $ and $ a' $ = $ [6, 6, 6] $ . $ \text{LIS}(a) = \text{LIS}(a') $ = $ 1 $ . Hence the beauty is $ min(1, 1) = 1 $ .

In the second test case, $ a $ can be rearranged to $ [2, 5, 4, 5, 4, 2] $ . Then $ a' $ = $ [2, 4, 5, 4, 5, 2] $ . $ \text{LIS}(a) = \text{LIS}(a') = 3 $ . Hence the beauty is $ 3 $ and it can be shown that this is the maximum possible beauty.

In the third test case, $ a $ can be rearranged to $ [1, 2, 3, 2] $ . Then $ a' $ = $ [2, 3, 2, 1] $ . $ \text{LIS}(a) = 3 $ , $ \text{LIS}(a') = 2 $ . Hence the beauty is $ min(3, 2) = 2 $ and it can be shown that $ 2 $ is the maximum possible beauty.

## 样例 #1

### 输入

```
3
3
6 6 6
6
2 5 4 5 2 4
4
1 3 2 2
```

### 输出

```
1
3
2
```



---

---
title: "The Enchanted Forest"
layout: "post"
diff: 普及+/提高
pid: CF1687A
tag: ['数学', '贪心']
---

# The Enchanted Forest

## 题目描述

> 其实这里被称为魔法森林，基本上就是因为这些有幻觉效果的蘑菇。光是接近这些蘑菇，就好像被施了魔法而产生幻觉。——《东方求闻史纪》

魔理沙来到了魔法森林采摘蘑菇。    
魔法森林可以被抽象成一条有着 $n$ 个节点，从 $1$ 到 $n$ 标号的数轴。在魔理沙出发之前，她的好友帕秋莉运用魔法去侦测了每个节点上的蘑菇数量，分别为 $a_1,a_2,\dots,a_n$。    
在第 $0$ 分钟的时候，魔理沙可以从任意一个节点出发。在每一分钟的时候，她将会做以下事情：

- 她将从节点 $x$ 移动到节点 $y$（$|x-y| \leq 1$，即 $y$ 可能等于 $x$）
- 她将会收集节点 $y$ 上的所有蘑菇。
- 魔法森林中每个节点会再生长出一个蘑菇。

注意，她不能在第 $0$ 分钟的时候收集蘑菇。    
现在魔理沙希望知道她在前 $k$ 分钟的时候，最多能收集到多少个蘑菇。请你帮帮她。

## 输入格式

第一行输入一个正整数 $t(1 \leq t \leq 10^4)$，表示输入数据组数。   
对于每一组测试数据，第一行输入两个正整数 $n,k(1 \leq n \leq 2\times 10^5, 1\leq k \leq 10^9)$，含义如题目所述。    
第二行输入 $n$ 个正整数 $a_i$，表示每个节点上起初有的蘑菇数量。

## 输出格式

对于每组测试数据输出一行，表示魔理沙最多能收集到多少个蘑菇。

## 样例 #1

### 输入

```
4
5 2
5 6 1 2 3
5 7
5 6 1 2 3
1 2
999999
5 70000
1000000000 1000000000 1000000000 1000000000 1000000000
```

### 输出

```
12
37
1000000
5000349985
```



---

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
title: "The Third Problem"
layout: "post"
diff: 普及+/提高
pid: CF1699C
tag: ['数学']
---

# The Third Problem

## 题目描述

You are given a permutation $ a_1,a_2,\ldots,a_n $ of integers from $ 0 $ to $ n - 1 $ . Your task is to find how many permutations $ b_1,b_2,\ldots,b_n $ are similar to permutation $ a $ .

Two permutations $ a $ and $ b $ of size $ n $ are considered similar if for all intervals $ [l,r] $ ( $ 1 \le l \le r \le n $ ), the following condition is satisfied: $ $$$\operatorname{MEX}([a_l,a_{l+1},\ldots,a_r])=\operatorname{MEX}([b_l,b_{l+1},\ldots,b_r]), $ $  where the  $ \\operatorname{MEX} $  of a collection of integers  $ c\_1,c\_2,\\ldots,c\_k $  is defined as the smallest non-negative integer  $ x $  which does not occur in collection  $ c $ . For example,  $ \\operatorname{MEX}(\[1,2,3,4,5\])=0 $ , and  $ \\operatorname{MEX}(\[0,1,2,4,5\])=3 $ .</p><p>Since the total number of such permutations can be very large, you will have to print its remainder modulo  $ 10^9+7 $ .</p><p>In this problem, a permutation of size  $ n $  is an array consisting of  $ n $  distinct integers from  $ 0 $  to  $ n-1 $  in arbitrary order. For example,  $ \[1,0,2,4,3\] $  is a permutation, while  $ \[0,1,1\] $  is not, since  $ 1 $  appears twice in the array.  $ \[0,1,3\] $  is also not a permutation, since  $ n=3 $  and there is a  $ 3$$$ in the array.

## 输入格式

Each test contains multiple test cases. The first line of input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The following lines contain the descriptions of the test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the size of permutation $ a $ .

The second line of each test case contains $ n $ distinct integers $ a_1,a_2,\ldots,a_n $ ( $ 0 \le a_i \lt n $ ) — the elements of permutation $ a $ .

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print a single integer, the number of permutations similar to permutation $ a $ , taken modulo $ 10^9+7 $ .

## 说明/提示

For the first test case, the only permutations similar to $ a=[4,0,3,2,1] $ are $ [4,0,3,2,1] $ and $ [4,0,2,3,1] $ .

For the second and third test cases, the given permutations are only similar to themselves.

For the fourth test case, there are $ 4 $ permutations similar to $ a=[1,2,4,0,5,3] $ :

- $ [1,2,4,0,5,3] $ ;
- $ [1,2,5,0,4,3] $ ;
- $ [1,4,2,0,5,3] $ ;
- $ [1,5,2,0,4,3] $ .

## 样例 #1

### 输入

```
5
5
4 0 3 2 1
1
0
4
0 1 2 3
6
1 2 4 0 5 3
8
1 3 7 2 5 0 6 4
```

### 输出

```
2
1
1
4
72
```



---

---
title: "Tournament Countdown"
layout: "post"
diff: 普及+/提高
pid: CF1713D
tag: ['数学']
---

# Tournament Countdown

## 题目描述

这是一道交互题。

有一场由 $2^n$ 位选手组成的锦标赛。

这个锦标赛的规则如下：第 $1$ 位选手与第 $2$ 位选手竞争，第 $3$ 位选手与第 $4$ 位选手竞争……以此类推，比赛结束时会只剩下一位参赛选手，这位参赛选手就是胜利者。

你不知道比赛的结果，但你想通过询问评审团来得知最后谁赢了。

每次询问评审团，你需要给定两个正整数 $a$ 和 $b$，$a$ 和 $b$ 分别代指两位选手的编号。

若 $a$ 选手 比 $b$ 选手 赢的回合更多，评委团将报出数字 $1$；如果 $b$ 选手 比 $a$ 选手 赢的回合更多，评审团将报出数字 $2$；如果这两位选手赢的回合一样多，评审团会报出数字 $0$。

你要做的是在不超过 $\lceil \frac{1}{3} \cdot 2^{n+1} \rceil$ 的次数内找到最后胜利的选手。此处 $\lceil x \rceil$ 表示四舍五入 $x$ 到最近的整数。

这场锦标赛已经过去很久了。所以保证有唯一解。

## 输入格式

输入第一行是一个正整数 $t\ (1\leq t\leq 2^{14})$，表示测试组数。

第二行是一个正整数 $n\ (1\leq n\leq 17)$，作用如题目所述。

接下来若干行都是一个正整数，表示询问的结果。

保证所有测试用例之和不超过 $2^{17}$。

## 输出格式

读取到 $n$ 后即开始询问。

要进行查询，请输出 " $?\ a\ b$ " $ (1\leq a, b\leq 2^n)$ 不包括引号。

若读入到了 $-1$ 或非有效值，这意味着程序在之前或现在**给出了无效的询问，或者是给出了错误的答案，或者是超出了查询的限制**。此时应停止程序。

若已经确定答案，且要给出答案，请输出 " $!\ x$ " $(1\leq x\leq 2^n)$ 不包括引号，且 $x$ 表示当前判断的最后的赢家。给出答案的次数无限制，即，给出答案不会计入到已询问的次数中。

注意，在每次**回答完成当前数据组或回答完成全部数据组**，程序都应该立即跳出，并刷新缓存区（~~不然呢？ILE大礼包警告~~），你可以：

- 在 `C++`，使用 `fflush(stdout)` 或 `cout.flush()` 或 `cout<<endl`；
- 在 `Java` 使用 `System.out.flush()`；
- 在 `Pascal` 使用 `flush(output)`；
- 在 `Python` 使用 `stdout.flush()`；
- 其他语言自行查阅对应文档。



要调试你的程序，可以参考以下说明：

1. 第一行输入一个整数 $t$ $(1 \leq t \leq 2^{14})$，表示测试组数；
2. 对于每组测试数据：

   1. 第一行输入一个整数 $n$ $(1 \leq n \leq 17)$；
   2. 接下来若干行，对于程序提出的询问，依照情况作出回答；
   3. 应该保证有唯一解，且给出的数据没有错误。

## 样例 #1

### 输入

```
1
3

2

0

2
```

### 输出

```
? 1 4

? 1 6

? 5 7

! 7
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
title: "Even Subarrays"
layout: "post"
diff: 普及+/提高
pid: CF1731C
tag: ['动态规划 DP', '数学', '前缀和']
---

# Even Subarrays

## 题目描述

You are given an integer array $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

Find the number of subarrays of $ a $ whose $ \operatorname{XOR} $ has an even number of divisors. In other words, find all pairs of indices $ (i, j) $ ( $ i \le j $ ) such that $ a_i \oplus a_{i + 1} \oplus \dots \oplus a_j $ has an even number of divisors.

For example, numbers $ 2 $ , $ 3 $ , $ 5 $ or $ 6 $ have an even number of divisors, while $ 1 $ and $ 4 $ — odd. Consider that $ 0 $ has an odd number of divisors in this task.

Here $ \operatorname{XOR} $ (or $ \oplus $ ) denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Print the number of subarrays but multiplied by 2022... Okay, let's stop. Just print the actual answer.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 10^4 $ ). Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq n $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the number of subarrays, whose $ \operatorname{XOR} $ has an even number of divisors.

## 说明/提示

In the first test case, there are $ 4 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [3] $ , $ [3,1] $ , $ [1,2] $ , $ [2] $ .

In the second test case, there are $ 11 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [4,2] $ , $ [4,2,1] $ , $ [4,2,1,5] $ , $ [2] $ , $ [2,1] $ , $ [2,1,5] $ , $ [2,1,5,3] $ , $ [1,5,3] $ , $ [5] $ , $ [5,3] $ , $ [3] $ .

In the third test case, there is no subarray whose $ \operatorname{XOR} $ has an even number of divisors since $ \operatorname{XOR} $ of any subarray is either $ 4 $ or $ 0 $ .

## 样例 #1

### 输入

```
4
3
3 1 2
5
4 2 1 5 3
4
4 4 4 4
7
5 7 3 7 1 7 3
```

### 输出

```
4
11
0
20
```



---

---
title: "Meta-set"
layout: "post"
diff: 普及+/提高
pid: CF1735D
tag: ['枚举', '组合数学']
---

# Meta-set

## 题目描述

### 题目翻译
你有一副牌，每张牌包含$k$个特征，每个特征等于集合 $\{0，1，2\}$ 中的一个值。显然，共有$3^k$
不同的情况。
 
定义一个三张牌为好的，当且仅当：对于同一位上的特征，要么**相同**，要么**两两不同**。如果**三张牌**所有$k$对特征都是好的，则称为一个集合。

如果一组**五张牌**中有严格意义上的**一个以上**的集合，则称为元组。在给定的$n$个不同的牌中，有多少个元组？

## 输入格式

输入的第一行包含两个整数 $n$ 和 $k$ $( 1\le n\le 10^3)$ $( 1 \le k \le 20）$,表示桌子上的牌的数量和牌的特征的数量。在接下来的$n$行中，将对牌进行描述。

描述卡片的每一行包含$k$个整数，表示卡片特征$\{0，1，2\}$。所有卡片都是**不同的**。

## 输出格式

输出一个整数表示元组的数量。

## 样例 #1

### 输入

```
8 4
0 0 0 0
0 0 0 1
0 0 0 2
0 0 1 0
0 0 2 0
0 1 0 0
1 0 0 0
2 2 0 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7 4
0 0 0 0
0 0 0 1
0 0 0 2
0 0 1 0
0 0 2 0
0 1 0 0
0 2 0 0
```

### 输出

```
3
```

## 样例 #3

### 输入

```
9 2
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2
```

### 输出

```
54
```

## 样例 #4

### 输入

```
20 4
0 2 0 0
0 2 2 2
0 2 2 1
0 2 0 1
1 2 2 0
1 2 1 0
1 2 2 1
1 2 0 1
1 1 2 2
1 1 0 2
1 1 2 1
1 1 1 1
2 1 2 0
2 1 1 2
2 1 2 1
2 1 1 1
0 1 1 2
0 0 1 0
2 2 0 0
2 0 0 2
```

### 输出

```
0
```



---

---
title: "Count GCD"
layout: "post"
diff: 普及+/提高
pid: CF1750D
tag: ['数学', '枚举', '容斥原理']
---

# Count GCD

## 题目描述

You are given two integers $ n $ and $ m $ and an array $ a $ of $ n $ integers. For each $ 1 \le i \le n $ it holds that $ 1 \le a_i \le m $ .

Your task is to count the number of different arrays $ b $ of length $ n $ such that:

- $ 1 \le b_i \le m $ for each $ 1 \le i \le n $ , and
- $ \gcd(b_1,b_2,b_3,...,b_i) = a_i $ for each $ 1 \le i \le n $ .

Here $ \gcd(a_1,a_2,\dots,a_i) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ a_1,a_2,\ldots,a_i $ .

Since this number can be too large, print it modulo $ 998\,244\,353 $ .

## 输入格式

Each test consist of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le m \le 10^9 $ ) — the length of the array $ a $ and the maximum possible value of the element.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le m $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ across all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the number of different arrays satisfying the conditions above. Since this number can be large, print it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the possible arrays $ b $ are:

- $ [4,2,1] $ ;
- $ [4,2,3] $ ;
- $ [4,2,5] $ .

In the second test case, the only array satisfying the demands is $ [1,1] $ .

In the third test case, it can be proven no such array exists.

## 样例 #1

### 输入

```
5
3 5
4 2 1
2 1
1 1
5 50
2 3 5 2 3
4 1000000000
60 30 1 1
2 1000000000
1000000000 2
```

### 输出

```
3
1
0
595458194
200000000
```



---

---
title: "Doremy's Pegging Game"
layout: "post"
diff: 普及+/提高
pid: CF1764D
tag: ['数学', '组合数学']
---

# Doremy's Pegging Game

## 题目描述

Doremy has $ n+1 $ pegs. There are $ n $ red pegs arranged as vertices of a regular $ n $ -sided polygon, numbered from $ 1 $ to $ n $ in anti-clockwise order. There is also a blue peg of slightly smaller diameter in the middle of the polygon. A rubber band is stretched around the red pegs.

Doremy is very bored today and has decided to play a game. Initially, she has an empty array $ a $ . While the rubber band does not touch the blue peg, she will:

1. choose $ i $ ( $ 1 \leq i \leq n $ ) such that the red peg $ i $ has not been removed;
2. remove the red peg $ i $ ;
3. append $ i $ to the back of $ a $ .

Doremy wonders how many possible different arrays $ a $ can be produced by the following process. Since the answer can be big, you are only required to output it modulo $ p $ . $ p $ is guaranteed to be a prime number.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764D/39b25225514736b577fbcbcd5d0b5bf29ecc4db4.png) game with $ n=9 $ and $ a=[7,5,2,8,3,9,4] $ and another game with $ n=8 $ and $ a=[3,4,7,1,8,5,2] $

## 输入格式

The first line contains two integers $ n $ and $ p $ ( $ 3 \leq n \leq 5000 $ , $ 10^8 \le p \le 10^9 $ ) — the number of red pegs and the modulo respectively.

 $ p $ is guaranteed to be a prime number.

## 输出格式

Output a single integer, the number of different arrays $ a $ that can be produced by the process described above modulo $ p $ .

## 说明/提示

In the first test case, $ n=4 $ , some possible arrays $ a $ that can be produced are $ [4,2,3] $ and $ [1,4] $ . However, it is not possible for $ a $ to be $ [1] $ or $ [1,4,3] $ .

## 样例 #1

### 输入

```
4 100000007
```

### 输出

```
16
```

## 样例 #2

### 输入

```
1145 141919831
```

### 输出

```
105242108
```



---

---
title: "Moscow Gorillas"
layout: "post"
diff: 普及+/提高
pid: CF1793D
tag: ['数学', '组合数学']
---

# Moscow Gorillas

## 题目描述

In winter, the inhabitants of the Moscow Zoo are very bored, in particular, it concerns gorillas. You decided to entertain them and brought a permutation $ p $ of length $ n $ to the zoo.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

The gorillas had their own permutation $ q $ of length $ n $ . They suggested that you count the number of pairs of integers $ l, r $ ( $ 1 \le l \le r \le n $ ) such that $ \operatorname{MEX}([p_l, p_{l+1}, \ldots, p_r])=\operatorname{MEX}([q_l, q_{l+1}, \ldots, q_r]) $ .

The $ \operatorname{MEX} $ of the sequence is the minimum integer positive number missing from this sequence. For example, $ \operatorname{MEX}([1, 3]) = 2 $ , $ \operatorname{MEX}([5]) = 1 $ , $ \operatorname{MEX}([3, 1, 2, 6]) = 4 $ .

You do not want to risk your health, so you will not dare to refuse the gorillas.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the permutations length.

The second line contains $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ) — the elements of the permutation $ p $ .

The third line contains $ n $ integers $ q_1, q_2, \ldots, q_n $ ( $ 1 \le q_i \le n $ ) — the elements of the permutation $ q $ .

## 输出格式

Print a single integer — the number of suitable pairs $ l $ and $ r $ .

## 说明/提示

In the first example, two segments are correct – $ [1, 3] $ with $ \operatorname{MEX} $ equal to $ 4 $ in both arrays and $ [3, 3] $ with $ \operatorname{MEX} $ equal to $ 1 $ in both of arrays.

In the second example, for example, the segment $ [1, 4] $ is correct, and the segment $ [6, 7] $ isn't correct, because $ \operatorname{MEX}(5, 4) \neq \operatorname{MEX}(1, 4) $ .

## 样例 #1

### 输入

```
3
1 3 2
2 1 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
7 3 6 2 1 5 4
6 7 2 5 3 1 4
```

### 输出

```
16
```

## 样例 #3

### 输入

```
6
1 2 3 4 5 6
6 5 4 3 2 1
```

### 输出

```
11
```



---

---
title: "Climbing the Tree"
layout: "post"
diff: 普及+/提高
pid: CF1810D
tag: ['数学']
---

# Climbing the Tree

## 题目描述

蜗牛在爬树。树高为 $ h $ 米，每只蜗牛从 $ 0 $ 米高处开始爬。

每只蜗牛有两个属性 $ a $ 与 $ b \text{ } ( a > b ) $。从第 $ 1 $ 天开始，每只蜗牛会以以下方式爬树：在白天，蜗牛向上爬 $ a $ 米； 在晚上，蜗牛会休息，而它每晚会向下滑 $ b $ 米。如果在第 $ n $ 天，蜗牛首次到达第 $ h $ 米的高度（也就是树顶），它就会结束爬行，此时我们称此蜗牛花了 $ n $ 天来爬树。注意，在最后一天，只要蜗牛离树顶的高度小于 $ a $ 米，它就不需要正好再向上爬 $ a $ 米。

起初，你并不知道树高 $ h $，你只知道 $ h $ 是一个正整数。接下来会发生以下两种类型的事件，事件件数总和为 $ q $。

- 事件 $ 1 $：有一只属性为 $ a $， $ b $ 的蜗牛声称它花了 $ n $ 天来爬树。如果这条信息与之前的已知信息有冲突（即根据之前信息确定的树高范围与当前信息所确定的树高范围有冲突），则忽略该信息，否则采纳该信息。

- 事件 $ 2 $：有一只属性为 $ a $， $ b $ 的蜗牛前来询问你它需要花几天来爬树。你只能根据当前你已采纳的信息来推测答案。如果仅根据已有信息无法给出精确的答案，则回答 $ -1 $。

你需要按顺序处理所有事件。




保证单个测试点内 $ q $ 的总和不超过 $ 2 \times 10 ^ 5 $。

## 输入格式

每个测试点包含多组测试数据。每组测试数据的第一行包含一个整数 $ t \text{ } ( 1 \le t \le 10 ^ 4 ) $，代表测试数据组数。

每组测试数据的第一行包含一个正整数 $ q \text{ } ( 1 \le q \le 2 \times 10 ^ 5 ) $，代表事件的件数。

对于接下来的 $ q $ 行，每行的第一个整数为 $ 1 $ 或 $ 2 $，代表事件的种类。

## 输出格式

对于每组测试数据，在同一行内输出 $ q $ 个由空格隔开的整数。整数的含义如下：

- 对于每个事件 $ 1 $，如果你接纳该信息，则输出 $ 1 $；如果你忽略该信息，则输出 $ 0 $；

- 对于每个事件 $ 2 $，输出一个整数，代表该蜗牛爬树所花费的天数。如果无法确定具体的答案，则输出 $ -1 $。

## 说明/提示

在第一个测试样例中，我们可以从第一条信息确定 $ h = 7 $，所有我们可以知道第二条蜗牛和第三条蜗牛各自需要 $ 2 $ 天和 $ 5 $ 天来爬树。

对于第一个样例中的第二只蜗牛，有：

- 在第 $ 1 $ 天的白天：这只蜗牛向上爬了 $ 4 $ 米，现在它在 $ 4 $ 米高处。
- 在第 $ 1 $ 天的晚上：这只蜗牛向下滑了 $ 1 $ 米，现在它在 $ 3 $ 米高处。
- 在第 $ 2 $ 天的白天：这只蜗牛向上爬了 $ 4 $ 米，现在它在 $ 7 $ 米高处（即爬到树顶）。

在第三个测试样例中，第二只蜗牛的信息与第一只蜗牛的信息有冲突，因为第二支蜗牛说它花了 $ 3 $ 天爬树，而它在前 $ 3 $ 天最多可以爬 $ 1 + 1 + 2 = 4 $ 米，而第一只蜗牛只需要花 $ 1 $ 天就能爬 $ 4 $ 米。

## 样例 #1

### 输入

```
5
3
1 3 2 5
2 4 1
2 3 2
3
1 6 5 1
2 3 1
2 6 2
3
1 4 2 2
1 2 1 3
2 10 2
9
1 7 3 6
1 2 1 8
2 5 1
1 10 9 7
1 8 1 2
1 10 5 8
1 10 7 7
2 7 4
1 9 4 2
9
1 2 1 6
1 8 5 6
1 4 2 7
2 9 1
1 5 1 4
1 5 2 7
1 7 1 9
1 9 1 4
2 10 8
```

### 输出

```
1 2 5
1 -1 1
1 0 1
1 0 -1 0 0 0 1 8 0
1 0 0 1 0 0 0 0 1
```



---

---
title: "One-Dimensional Puzzle"
layout: "post"
diff: 普及+/提高
pid: CF1931G
tag: ['组合数学', '分类讨论']
---

# One-Dimensional Puzzle

## 题目描述

You have a one-dimensional puzzle, all the elements of which need to be put in one row, connecting with each other. All the puzzle elements are completely white and distinguishable from each other only if they have different shapes.

Each element has straight borders at the top and bottom, and on the left and right it has connections, each of which can be a protrusion or a recess. You cannot rotate the elements.

You can see that there are exactly $ 4 $ types of elements. Two elements can be connected if the right connection of the left element is opposite to the left connection of the right element.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1931G/ab3dee044a8e18206fe7c695b7a089bda5931d43.png) All possible types of elements. The puzzle contains $ c_1, c_2, c_3, c_4 $ elements of each type. The puzzle is considered complete if you have managed to combine all elements into one long chain. You want to know how many ways this can be done.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^5 $ ) — the number of input test cases. The descriptions of the test cases follow.

The description of each test case contains $ 4 $ integers $ c_i $ ( $ 0 \le c_i \le 10^6 $ ) — the number of elements of each type, respectively.

It is guaranteed that the sum of $ c_i $ for all test cases does not exceed $ 4 \cdot 10^6 $ .

## 输出格式

For each test case, print one integer — the number of possible ways to solve the puzzle.

Two methods are considered different if there is $ i $ , such that the types of elements at the $ i $ position in these methods differ.

Since the answer can be very large, output it modulo $ 998244353 $ .

If it is impossible to solve the puzzle, print $ 0 $ .

## 样例 #1

### 输入

```
11
1 1 1 1
1 2 5 10
4 6 100 200
900000 900000 900000 900000
0 0 0 0
0 0 566 239
1 0 0 0
100 0 100 0
0 0 0 4
5 5 0 2
5 4 0 5
```

### 输出

```
4
66
0
794100779
1
0
1
0
1
36
126
```



---

---
title: "Find a Mine"
layout: "post"
diff: 普及+/提高
pid: CF1934C
tag: ['数学']
---

# Find a Mine

## 题目描述

This is an interactive problem.

You are given a grid with $ n $ rows and $ m $ columns. The coordinates $ (x, y) $ represent the cell on the grid, where $ x $ ( $ 1 \leq x \leq n $ ) is the row number counting from the top and $ y $ ( $ 1 \leq y \leq m $ ) is the column number counting from the left. It is guaranteed that there are exactly $ 2 $ mines in the grid at distinct cells, denoted as $ (x_1, y_1) $ and $ (x_2, y_2) $ . You are allowed to make no more than $ 4 $ queries to the interactor, and after these queries, you need to provide the location of one of the mines.

In each query, you can choose any grid cell $ (x, y) $ , and in return, you will receive the minimum Manhattan distance from both the mines to the chosen cell, i.e., you will receive the value $ \min(|x-x_1|+|y-y_1|, |x-x_2|+|y-y_2|) $ .

Your task is to determine the location of one of the mines after making the queries.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 3 \cdot 10^{3} $ ) — the number of test cases.

The only line of each test case contains two integers $ n $ and $ m $ ( $ 2 \leq n \leq 10^{8} $ , $ 2 \leq m \leq 10^{8} $ ) — the number of rows and columns.

## 输出格式

For each test case, the interaction starts with reading $ n $ and $ m $ .

Then you are allowed to make at most $ 4 $ queries in the following way:

"? x y" ( $ 1 \leq x \leq n $ and $ 1 \leq y \leq m $ )

After each one, you should read an integer $ d $ which is equal to $ \min(|x-x_1|+|y-y_1|, |x-x_2|+|y-y_2|) $ .

When you have found the location of any one of the mines, print a single line "! x y" (without quotes), representing the row and the column of one of the mines. Outputting the answer does not count as a query.

After printing the answer, your program must then continue to solve the remaining test cases, or exit if all test cases have been solved.

The interactor for this problem is not adaptive: cells of mines are fixed before any queries are made.

After printing a query, do not forget to output the end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see the documentation for other languages.

Hacks:

To make a hack, use the following format:

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 3 \cdot 10^{3} $ ) — the number of test cases.

The description of each test case should consist of three lines.

The first line contains two integers $ n $ and $ m $ ( $ 2 \leq n \leq 10^{8} $ , $ 2 \leq m \leq 10^{8} $ ) — the number of rows and columns.

The second line contains the coordinates of the first mine $ x_1 $ and $ y_1 $ ( $ 1 \leq x_1 \leq n $ , $ 1 \leq y_1 \leq m $ ).

The third line contains the coordinates of the second mine $ x_2 $ and $ y_2 $ ( $ 1 \leq x_2 \leq n $ , $ 1 \leq y_2 \leq m $ ).

The mines should be located at different positions.

## 说明/提示

In the first test case, we start by querying the upper-left corner $ (1, 1) $ and get the result $ 3 $ , which means that there is a mine on the counter diagonal, and there is no mine above it.

In the image below, each cell contains a number indicating the distance to the blue cell. The green cells are candidates to contain the nearest mine.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/9f8890c987cfc62ebf33297af68261e59cb82050.png)Then we ask three cells on that diagonal, and at the last query, we get the result $ 0 $ , which means that a mine is found at the position $ (2, 3) $ .

The second mine was located at the position $ (3, 2) $ .

In the second test case, we start by asking the lower-right corner $ (5, 5) $ , and get the result $ 1 $ , which means that one of the two neighbours contains a mine, let's call it mine $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/529c76a59b6e1128854ef8942281235840d099a4.png)Then we ask cell $ (2, 2) $ . We can see that these green cells don't intersect with the green cells from the first query, so they contain the other mine, let's call it mine $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/759e71e2b3a5d456c063d438414900b4ab40b3f1.png)Query $ 3 $ is cell $ (3, 3) $ . These cells contain mine $ 1 $ , but we still don't know where exactly. Nevertheless, we can determine that the only possible cell for mine $ 2 $ is $ (1, 1) $ , because all other candidates are at a distance closer than $ 3 $ for this query.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1934C/9b91f7f88f4e4ce648a34002d2c4a2f09feeedee.png)

## 样例 #1

### 输入

```
2
4 4

3

2

2

0

5 5

1

2

3
```

### 输出

```
? 1 1

? 1 4

? 4 1

? 2 3

! 2 3

? 5 5

? 2 2

? 3 3

! 1 1
```



---

---
title: "Bessie's Birthday Cake (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF1942C2
tag: ['数学', '贪心']
---

# Bessie's Birthday Cake (Hard Version)

## 题目描述

[Proof Geometric Construction Can Solve All Love Affairs - manbo-p](https://soundcloud.com/alice-law-314125270/manbo-p-proof-geometric-construction-can-solve-all-love-affairs)

⠀



This is the hard version of the problem. The only difference between the two versions is the constraint on $ y $ . In this version $ 0 \leq y \leq n - x $ . You can make hacks only if both versions are solved.

Bessie has received a birthday cake from her best friend Elsie, and it came in the form of a regular polygon with $ n $ sides. The vertices of the cake are numbered from $ 1 $ to $ n $ clockwise. You and Bessie are going to choose some of those vertices to cut non-intersecting diagonals into the cake. In other words, the endpoints of the diagonals must be part of the chosen vertices.

Bessie would only like to give out pieces of cake which result in a triangle to keep consistency. The size of the pieces doesn't matter, and the whole cake does not have to be separated into all triangles (other shapes are allowed in the cake, but those will not be counted).

Bessie has already chosen $ x $ of those vertices that can be used to form diagonals. She wants you to choose no more than $ y $ other vertices such that the number of triangular pieces of cake she can give out is maximized.

What is the maximum number of triangular pieces of cake Bessie can give out?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case consists of three integers, $ n $ , $ x $ , and $ y $ ( $ 4 \leq n \leq 10^9 $ , $ 2 \leq x \leq \min(n, 2 \cdot 10^5) $ , $ 0 \leq y \leq n - x $ ) — the number of sides of the polygon, number of vertices Bessie has chosen, and the maximum number of other vertices you can choose.

The second line consists of $ x $ distinct integers from $ 1 $ to $ n $ , representing the vertices Bessie has chosen.

It is guaranteed the sum of $ x $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the maximum number of non-intersecting triangular pieces of cake she can give out.

## 说明/提示

In test cases $ 1 $ , $ 2 $ and $ 3 $ , you can get $ 6 $ , $ 5 $ and $ 2 $ non-intersecting triangular pieces of cake, respectively. A possible construction is shown in the following pictures:

The green dots represent vertices that Bessie chose, the yellow dots represent vertices that you chose, the blue lines represent diagonals that are drawn, and the red numbers represent triangles that are counted.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942C2/1d0397b12ffc5a0058affa34960ac433601c6be3.png)

## 样例 #1

### 输入

```
3
8 4 2
1 6 2 5
7 3 1
6 4 3
4 2 2
1 3
```

### 输出

```
6
5
2
```



---

---
title: "Unfair Game"
layout: "post"
diff: 普及+/提高
pid: CF1955F
tag: ['动态规划 DP', '数学']
---

# Unfair Game

## 题目描述

Alice and Bob gathered in the evening to play an exciting game on a sequence of $ n $ integers, each integer of the sequence doesn't exceed $ 4 $ . The rules of the game are too complex to describe, so let's just describe the winning condition — Alice wins if the [bitwise XOR](http://tiny.cc/xor_wiki_eng) of all the numbers in the sequence is non-zero; otherwise, Bob wins.

The guys invited Eve to act as a judge. Initially, Alice and Bob play with $ n $ numbers. After one game, Eve removes one of the numbers from the sequence, then Alice and Bob play with $ n-1 $ numbers. Eve removes one number again, after which Alice and Bob play with $ n - 2 $ numbers. This continues until the sequence of numbers is empty.

Eve seems to think that in such a game, Alice almost always wins, so she wants Bob to win as many times as possible. Determine the maximum number of times Bob can win against Alice if Eve removes the numbers optimally.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line of each test case contains four integers $ p_i $ ( $ 0 \le p_i \le 200 $ ) — the number of ones, twos, threes, and fours in the sequence at the beginning of the game.

## 输出格式

For each test case, print the maximum number of times Bob will win in a separate line, if Eve removes the numbers optimally.

## 说明/提示

In the first example, Bob wins when Eve has not removed any numbers yet.

In the second example, Bob wins if Eve removes one one and one three.

## 样例 #1

### 输入

```
5
1 1 1 0
1 0 1 2
2 2 2 0
3 3 2 0
0 9 9 9
```

### 输出

```
1
1
3
3
12
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
title: "Novice's Mistake"
layout: "post"
diff: 普及+/提高
pid: CF1992E
tag: ['数学', '枚举']
---

# Novice's Mistake

## 题目描述

One of the first programming problems by K1o0n looked like this: "Noobish\_Monk has $ n $ $ (1 \le n \le 100) $ friends. Each of them gave him $ a $ $ (1 \le a \le 10000) $ apples for his birthday. Delighted with such a gift, Noobish\_Monk returned $ b $ $ (1 \le b \le \min(10000, a \cdot n)) $ apples to his friends. How many apples are left with Noobish\_Monk?"

K1o0n wrote a solution, but accidentally considered the value of $ n $ as a string, so the value of $ n \cdot a - b $ was calculated differently. Specifically:

- when multiplying the string $ n $ by the integer $ a $ , he will get the string $ s=\underbrace{n + n + \dots + n + n}_{a\ \text{times}} $
- when subtracting the integer $ b $ from the string $ s $ , the last $ b $ characters will be removed from it. If $ b $ is greater than or equal to the length of the string $ s $ , it will become empty.

Learning about this, ErnKor became interested in how many pairs $ (a, b) $ exist for a given $ n $ , satisfying the constraints of the problem, on which K1o0n's solution gives the correct answer.

"The solution gives the correct answer" means that it outputs a non-empty string, and this string, when converted to an integer, equals the correct answer, i.e., the value of $ n \cdot a - b $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

For each test case, a single line of input contains an integer $ n $ ( $ 1 \le n \le 100 $ ).

It is guaranteed that in all test cases, $ n $ is distinct.

## 输出格式

For each test case, output the answer in the following format:

In the first line, output the integer $ x $ — the number of bad tests for the given $ n $ .

In the next $ x $ lines, output two integers $ a_i $ and $ b_i $ — such integers that K1o0n's solution on the test " $ n $ $ a_i $ $ b_i $ " gives the correct answer.

## 说明/提示

In the first example, $ a = 20 $ , $ b = 18 $ are suitable, as " $ \text{2} $ " $ \cdot 20 - 18 = $ " $ \text{22222222222222222222} $ " $ - 18 = 22 = 2 \cdot 20 - 18 $

## 样例 #1

### 输入

```
3
2
3
10
```

### 输出

```
3
20 18 
219 216 
2218 2214 
1
165 162 
1
1262 2519
```



---

---
title: "Bouquet (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF1995B2
tag: ['数学', '贪心']
---

# Bouquet (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version, instead of listing the number of petals for each flower, the number of petals and the quantity of flowers in the store is set for all types of flowers.

A girl is preparing for her birthday and wants to buy the most beautiful bouquet. There are a total of $ n $ different types of flowers in the store, each of which is characterized by the number of petals and the quantity of this type of flower. A flower with $ k $ petals costs $ k $ coins. The girl has decided that the difference in the number of petals between any two flowers she will use to decorate her cake should not exceed one. At the same time, the girl wants to assemble a bouquet with the maximum possible number of petals. Unfortunately, she only has $ m $ coins, and she cannot spend more. What is the maximum total number of petals she can assemble in the bouquet?

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10\,000 $ ) — the number of test cases. This is followed by descriptions of the test cases.

The first line of each test case contains two integers $ n $ , $ m $ ( $ 1 \le n \le 2 \cdot 10^5, 1 \le m \le 10^{18} $ ) — the number of types of flowers in the store and the number of coins the girl possesses, respectively. The second line of each test case contains $ n $ different integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ), where $ a_i $ is the number of petals of the $ i $ -th flower type in the store (for different indexes $ i \neq j $ , it must be $ a_i \neq a_j $ ). The third line of each test case contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 1 \le c_i \le 10^9 $ ), where $ c_i $ is the quantity of the $ i $ -th flower type in the store.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot {10}^5 $ .

## 输出格式

For each test case, print one integer — the maximum possible number of petals in a bouquet that a girl can collect, observing all the conditions listed above.

## 说明/提示

In the first test case, some valid bouquets are $ (1, 1, 2, 2), (2, 2, 3), (1, 1), (2, 2) $ . The maximum over all valid bouquets not greater than $ 10 $ is $ 7 $ for $ (2, 2, 3) $ . In the second test case, you can assemble a valid bouquet with $ (206, 206, 207, 207, 207) $ with a sum of $ 1033 $ , which is the maximum number of petals the girl can buy. In the third test case, you can assemble a valid bouquet with $ (5, 5, 5, 4) $ with a sum of $ 19 $ . It can be seen that no valid bouquet can have $ 20 $ petals.

## 样例 #1

### 输入

```
7
3 10
1 2 3
2 2 1
3 1033
206 207 1000
3 4 1
6 20
4 2 7 5 6 1
1 2 1 3 1 7
8 100000
239 30 610 122 24 40 8 2
12 13123 112 1456 124 100 123 10982
6 13
2 4 11 1 3 5
2 2 1 2 2 1
8 10330
206 210 200 201 198 199 222 1000
9 10 11 12 13 14 15 16
2 10000000000
11 12
87312315 753297050
```

### 输出

```
7
1033
19
99990
13
10000
9999999999
```



---

---
title: "Squaring"
layout: "post"
diff: 普及+/提高
pid: CF1995C
tag: ['数学']
---

# Squaring

## 题目描述

ikrpprpp found an array $ a $ consisting of integers. He likes justice, so he wants to make $ a $ fair — that is, make it non-decreasing. To do that, he can perform an act of justice on an index $ 1 \le i \le n $ of the array, which will replace $ a_i $ with $ a_i ^ 2 $ (the element at position $ i $ with its square). For example, if $ a = [2,4,3,3,5,3] $ and ikrpprpp chooses to perform an act of justice on $ i = 4 $ , $ a $ becomes $ [2,4,3,9,5,3] $ .

What is the minimum number of acts of justice needed to make the array non-decreasing?

## 输入格式

First line contains an integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. It is followed by the description of test cases.

For each test case, the first line contains an integer $ n $ — size of the array $ a $ . The second line contains $ n $ ( $ 1 \le n \le 2 \cdot 10 ^5 $ ) integers $ a_1, a_2,\ldots, a_n $ ( $ 1 \le a_i \le 10 ^ 6 $ ).

The sum of $ n $ over all test cases does not exceed $ 2 \cdot {10}^5 $ .

## 输出格式

For each testcase, print an integer — minimum number of acts of justice required to make the array $ a $ non-decreasing. If it is impossible to do that, print $ -1 $ .

## 说明/提示

In the first test case, there's no need to perform acts of justice. The array is fair on its own!

In the third test case, it can be proven that the array cannot become non-decreasing.

In the fifth test case, ikrpprppp can perform an act of justice on index 3, then an act of justice on index 2, and finally yet another act of justice on index 3. After that, $ a $ will become $ [4, 9, 16] $ .

## 样例 #1

### 输入

```
7
3
1 2 3
2
3 2
3
3 1 5
4
1 1 2 3
3
4 3 2
9
16 2 4 2 256 2 4 2 8
11
10010 10009 10008 10007 10006 10005 10004 10003 10002 10001 10000
```

### 输出

```
0
1
-1
0
3
15
55
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
title: "Sakurako's Box"
layout: "post"
diff: 普及+/提高
pid: CF2008F
tag: ['数学', '逆元']
---

# Sakurako's Box

## 题目描述

Sakurako 有一个装满 $n$ 个球的盒子。每个球都有自己的数值。她想和朋友打个赌，朋友如果从盒子中随机选出两个球（可以是不同的两球，即使它们有相同的数值），这两个球数值的乘积能够等于 Sakurako 事先猜测到的一个数。

因为 Sakurako 是概率学方面的专家，她知道最明智的猜测应该是[期望值](http://tiny.cc/matozh_en)，但她忘了如何去计算。请帮助她计算出这个数组中任意两个元素乘积的期望值。

可以证明，该期望值的形式为 $\frac{P}{Q}$，其中 $P$ 和 $Q$ 是非负整数，且 $Q \ne 0$。你需要计算并输出 $P \cdot Q^{-1} \bmod (10^9+7)$ 的结果。

## 输入格式

输入的第一行是一个整数 $t$，表示测试用例的数量（$1 \le t \le 10^4$）。

接下来的每一个测试用例的第一行是一个整数 $n$，表示数组中元素的数量（$2 \le n \le 2 \cdot 10^5$）。

接下来的第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$0 \le a_i \le 10^9$），表示数组中的元素值。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对每个测试用例，输出 $P \cdot Q^{-1} \bmod (10^9+7)$ 的结果。

## 说明/提示

举个例子：
- 在第一个测试用例中，Sakurako 的朋友可以选择这些球对：$(a_1, a_2)$、$(a_1, a_3)$ 和 $(a_2, a_3)$。它们的乘积分别是 $3 \times 2 = 6$、$3 \times 3 = 9$ 和 $3 \times 2 = 6$，所以期望值计算结果为 $\frac{6 + 9 + 6}{3} = 7$。

- 在第二个测试用例中，朋友可以选择的球对有：$(a_1, a_2)$、$(a_1, a_3)$、$(a_1, a_4)$、$(a_2, a_3)$、$(a_2, a_4)$ 和 $(a_3, a_4)$。它们的乘积分别为 $2 \times 2 = 4$、$2 \times 2 = 4$、$2 \times 4 = 8$、$2 \times 2 = 4$、$2 \times 4 = 8$ 和 $2 \times 4 = 8$，所以期望值为 $\frac{4 + 4 + 8 + 4 + 8 + 8}{6} = \frac{36}{6} = 6$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3
3 2 3
4
2 2 2 4
5
1 2 3 4 5
```

### 输出

```
7
6
500000012
```



---

---
title: "Sakurako's Test"
layout: "post"
diff: 普及+/提高
pid: CF2008H
tag: ['数学', '二分', '前缀和']
---

# Sakurako's Test

## 题目描述

Sakurako 即将参加一场考试，这场考试可用一个整数数组 $n$ 和一个相关任务来描述：

对于给定的整数 $x$，Sakurako 可以多次执行以下操作：

- 选择一个整数 $i$，其中 $1 \le i \le n$，且满足 $a_i \ge x$；
- 将 $a_i$ 的值减少 $x$，即改为 $a_i - x$。

通过这样的操作，她需要找到数组 $a$ 的最小可能中位数 $^{\text{∗}}$。

Sakurako 已知数组的内容，但不清楚整数 $x$ 的值。不过，有人透露在接下来的考试中，$x$ 的值会是给定的 $q$ 个值之一，因此她希望你能帮忙找出每一个可能的 $x$ 所对应的最小中位数。

$^{\text{∗}}$ 对于一个长度为 $n$ 的数组，若 $n$ 是偶数，则中位数是排序后数组中第 $\frac{n+2}{2}$ 个位置的元素；若 $n$ 是奇数，则为第 $\frac{n+1}{2}$ 个位置的元素。

## 输入格式

第一行包含一个整数 $t$，表示测试用例的数量（$1 \le t \le 10^4$）。

接下来，每个测试用例的第一行包括两个整数 $n$ 和 $q$，分别表示数组的元素数量和查询数量（$1 \le n, q \le 10^5$）。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$，表示数组的内容（$1 \le a_i \le n$）。

接下来的 $q$ 行每行给出一个整数 $x$，表示一个查询（$1 \le x \le n$）。

保证所有测试用例中 $n$ 和 $q$ 的总和均不超过 $10^5$。

## 输出格式

对于每个测试用例，输出 $q$ 个整数，代表每个查询下计算出的答案。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
5 5
1 2 3 4 5
1
2
3
4
5
6 3
1 2 6 4 1 3
2
1
5
```

### 输出

```
0 1 1 1 2 
1 0 2
```



---

---
title: "Cards Partition"
layout: "post"
diff: 普及+/提高
pid: CF2018A
tag: ['数学', '贪心']
---

# Cards Partition

## 题目描述

[DJ Genki vs Gram - Einherjar Joker](https://soundcloud.com/leon-hwang-368077289/einherjar-joker-dj-genki-vs-gram)

⠀



You have some cards. An integer between $ 1 $ and $ n $ is written on each card: specifically, for each $ i $ from $ 1 $ to $ n $ , you have $ a_i $ cards which have the number $ i $ written on them.

There is also a shop which contains unlimited cards of each type. You have $ k $ coins, so you can buy at most $ k $ new cards in total, and the cards you buy can contain any integer between $ \mathbf{1} $ and $ \mathbf{n} $ , inclusive.

After buying the new cards, you must partition all your cards into decks, according to the following rules:

- all the decks must have the same size;
- there are no pairs of cards with the same value in the same deck.

Find the maximum possible size of a deck after buying cards and partitioning them optimally.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ k $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ , $ 0 \leq k \leq 10^{16} $ ) — the number of distinct types of cards and the number of coins.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq 10^{10} $ , $ \sum a_i \geq 1 $ ) — the number of cards of type $ i $ you have at the beginning, for each $ 1 \leq i \leq n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the maximum possible size of a deck if you operate optimally.

## 说明/提示

In the first test case, you can buy one card with the number $ 1 $ , and your cards become $ [1, 1, 1, 1, 2, 2, 3, 3] $ . You can partition them into the decks $ [1, 2], [1, 2], [1, 3], [1, 3] $ : they all have size $ 2 $ , and they all contain distinct values. You can show that you cannot get a partition with decks of size greater than $ 2 $ , so the answer is $ 2 $ .

In the second test case, you can buy two cards with the number $ 1 $ and one card with the number $ 3 $ , and your cards become $ [1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 5, 5, 5, 5] $ , which can be partitioned into $ [1, 2, 3], [1, 2, 4], [1, 2, 5], [1, 2, 5], [2, 3, 5], [2, 4, 5] $ . You can show that you cannot get a partition with decks of size greater than $ 3 $ , so the answer is $ 3 $ .

## 样例 #1

### 输入

```
9
3 1
3 2 2
5 4
2 6 1 2 4
2 100
1410065408 10000000000
10 8
7 4 6 6 9 3 10 2 8 7
2 12
2 2
2 70
0 1
1 0
1
3 0
2 1 2
3 1
0 3 3
```

### 输出

```
2
3
1
7
2
2
1
1
2
```



---

---
title: "Kosuke's Sloth"
layout: "post"
diff: 普及+/提高
pid: CF2033F
tag: ['数学']
---

# Kosuke's Sloth

## 题目描述

Kosuke is too lazy. He will not give you any legend, just the task:

Fibonacci numbers are defined as follows:

- $ f(1)=f(2)=1 $ .
- $ f(n)=f(n-1)+f(n-2) $ $ (3\le n) $

 We denote $ G(n,k) $ as an index of the $ n $ -th Fibonacci number that is divisible by $ k $ . For given $ n $ and $ k $ , compute $ G(n,k) $ .As this number can be too big, output it by modulo $ 10^9+7 $ .

For example: $ G(3,2)=9 $ because the $ 3 $ -rd Fibonacci number that is divisible by $ 2 $ is $ 34 $ . $ [1,1,\textbf{2},3,5,\textbf{8},13,21,\textbf{34}] $ .

## 输入格式

The first line of the input data contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 10^{18} $ , $ 1 \le k \le 10^5 $ ).

It is guaranteed that the sum of $ k $ across all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output the only number: the value $ G(n,k) $ taken by modulo $ 10^9+7 $ .

## 样例 #1

### 输入

```
3
3 2
100 1
1000000000000 1377
```

### 输出

```
9
100
999244007
```



---

---
title: "Guess One Character"
layout: "post"
diff: 普及+/提高
pid: CF2038G
tag: ['数学']
---

# Guess One Character

## 题目描述

This is an interactive problem. You have to use flush operation right after printing each line. For example, in C++ you should use the function fflush(stdout) or cout.flush(), in Java or Kotlin — System.out.flush(), and in Python — sys.stdout.flush().

The jury has a string $ s $ consisting of characters 0 and/or 1. The length of this string is $ n $ .

You can ask the following queries:

- $ 1 $ $ t $ — "how many times does $ t $ appear in $ s $ as a contiguous substring?" Here, $ t $ should be a string consisting of characters 0 and/or 1; its length should be at least $ 1 $ and at most $ n $ . For example, if the string $ s $ is 111011 and the string $ t $ is 11, the response to the query is $ 3 $ .

You have to guess at least one character in the string $ s $ by asking no more than $ 3 $ queries. Note that giving the answer does not count as a query.

In every test and in every test case, the string $ s $ is fixed beforehand.

## 输出格式

Initially, the jury program sends one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

At the start of each test case, the jury program sends one integer $ n $ ( $ 2 \le n \le 50 $ ) — the length of the string.

After that, your program can submit queries to the jury program by printing the following line (do not forget to flush the output after printing a line!):

- $ 1 $ $ t $ means asking a query "how many times does $ t $ appear in $ s $ as a contiguous substring?"

For every query, the jury prints one integer on a separate line. It is either:

- the answer to your query, if the query is correct, and you haven't exceeded the query limit;
- or the integer $ -1 $ , if your query is incorrect (for example, the constraint $ 1 \le |t| \le n $ is not met or the string $ t $ contains characters other than 0 and 1) or if you have asked too many queries while processing the current test case.

To submit the answer, your program should send a line in the following format (do not forget to flush the output after printing a line!):

- $ 0 $ $ i $ $ c $ , where $ 1 \le i \le n $ and $ c $ is either 0 or 1, meaning that $ s_i = c $ .

If your guess is correct, the jury program will print one integer $ 1 $ on a separate line, indicating that you may proceed to the next test case (or terminate the program, if it was the last test case) and that the number of queries you have asked is reset. If it is not correct, the jury program will print one integer $ -1 $ on a separate line.

After your program receives $ -1 $ as the response, it should immediately terminate. This will lead to your submission receiving the verdict "Wrong Answer". If your program does not terminate, the verdict of your submission is undefined.

## 说明/提示

In the example, there are $ 3 $ test cases: 101, 11 and 10. Note that everything after the // sign is a comment that explains which line means what in the interaction. The jury program won't print these comments in the actual problem, and you shouldn't print them. The empty lines are also added for your convenience, the jury program won't print them, and your solution should not print any empty lines.

## 样例 #1

### 输入

```
3     // 3 test cases
3     // the length of the string is 3

1     // 101 occurs once

1     // guessed correctly
2     // the length of the string is 2

0     // 00 occurs zero times

0     // 0 occurs zero times

1     // guessed correctly
2     // the length of the string is 2

1     // 1 occurs once

0     // 01 occurs zero times

1     // guessed correctly
```

### 输出

```
1 101 // how many times 101 occurs

0 2 0 // guess: s[2] is 0


1 00  // how many times 00 occurs

1 0   // how many times 0 occurs

0 1 1 // guess: s[1] is 1


1 1   // how many times 1 occurs

1 01  // how many times 01 occurs

0 2 0 // guess: s[2] is 0
```



---

---
title: "Shohag Loves XOR (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF2039C2
tag: ['数学', '数论', '枚举', '位运算']
---

# Shohag Loves XOR (Hard Version)

## 题目描述

This is the hard version of the problem. The differences between the two versions are highlighted in bold. You can only make hacks if both versions of the problem are solved.

Shohag has two integers $ x $ and $ m $ . Help him count the number of integers $ 1 \le y \le m $ such that $ x \oplus y $ is divisible $ ^{\text{∗}} $ by either $ x $ , $ y $ , or both. Here $ \oplus $ is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operator.

 $ ^{\text{∗}} $ The number $ a $ is divisible by the number $ b $ if there exists an integer $ c $ such that $ a = b \cdot c $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line of each test case contains two space-separated integers $ x $ and $ m $ ( $ 1 \le x \le 10^6 $ , $ 1 \le m \le 10^{18} $ ).

It is guaranteed that the sum of $ x $ over all test cases does not exceed $ 10^7 $ .

## 输出格式

For each test case, print a single integer — the number of suitable $ y $ .

## 说明/提示

In the first test case, for $ x = 7 $ , there are $ 3 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 10 $ , and they are $ 1 $ , $ 7 $ , and $ 9 $ .

- $ y = 1 $ is valid because $ x \oplus y = 7 \oplus 1 = 6 $ and $ 6 $ is divisible by $ y = 1 $ .
- $ y = 7 $ is valid because $ x \oplus y = 7 \oplus 7 = 0 $ and $ 0 $ is divisible by both $ x = 7 $ and $ y = 7 $ .
- $ y = 9 $ is valid because $ x \oplus y = 7 \oplus 9 = 14 $ and $ 14 $ is divisible by $ x = 7 $ .

## 样例 #1

### 输入

```
5
7 10
2 3
6 4
1 6
4 1
```

### 输出

```
3
2
2
6
1
```



---

---
title: "Ordered Permutations"
layout: "post"
diff: 普及+/提高
pid: CF2040C
tag: ['数学', '贪心', '位运算']
---

# Ordered Permutations

## 题目描述

给定一个长度为 $n$ 的整数排列 $p_1, p_2, \ldots, p_n$，其中包含从 $1$ 到 $n$ 的所有整数。我们定义一个如下的和式：

$$S(p) = \sum_{1 \le l \le r \le n} \min(p_l, p_{l+1}, \ldots, p_r)$$

我们希望找出所有能使 $S(p)$ 最大的排列，并从中按字典序选择第 $k$ 个。如果这样的排列数量少于 $k$，则输出 -1。

**解释说明：**
- 长度为 $n$ 的排列是一个由 $n$ 个不同的整数组成的序列，这些整数来源于 $1$ 到 $n$ 的一组数字。例如，$[2, 3, 1, 5, 4]$ 是一个符合要求的排列，而 $[1, 2, 2]$ 因为有重复数字 $2$ 而不符合，$[1, 3, 4]$ 也不符合要求，因为它包含了不在 $1$ 到 $n$ 范围内的数 $4$（$n = 3$）。
- 示例计算： 
  - 对于排列 $[1, 2, 3]$，$S(p)$ 计算为 $\min(1) + \min(1, 2) + \min(1, 2, 3) + \min(2) + \min(2, 3) + \min(3) = 1 + 1 + 1 + 2 + 2 + 3 = 10$。
  - 对于排列 $[2, 4, 1, 3]$，$S(p)$ 计算为 $\min(2) + \min(2, 4) + \min(2, 4, 1) + \min(2, 4, 1, 3) + \min(4) + \min(4, 1) + \min(4, 1, 3) + \min(1) + \min(1, 3) + \min(3) = 2 + 2 + 1 + 1 + 4 + 1 + 1 + 1 + 1 + 3 = 17$。
- 字典序小于：数组 $a$ 比数组 $b$ 在字典序上小的条件是：
  1. $a$ 是 $b$ 的一个前缀，且 $a \ne b$；
  2. 或者在第一个不同的位置上，$a$ 的元素小于 $b$ 的对应元素。

## 输入格式

第一行输入一个整数 $t$，表示测试用例的数量 ($1 \le t \le 10^4$)。之后的每一个测试用例由一行组成，包含两个整数 $n$ 和 $k$，分别表示排列的长度和需要找出的第 $k$ 个排列的索引 ($1 \le n \le 2 \cdot 10^5$; $1 \le k \le 10^{12}$)。

保证所有测试用例中的 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每一个测试用例：
- 如果符合条件的排列少于 $k$ 个，则输出 `-1`。
- 否则，输出第 $k$ 个符合条件的排列。

## 说明/提示

以下是所有长度为 3 的排列及其对应的 $S(p)$ 值（按字典序排序）：

| 排列 | $S(p)$ 的值 |
|------|-------------|
| $[1, 2, 3]$ | $10$ |
| $[1, 3, 2]$ | $10$ |
| $[2, 1, 3]$ | $9$ |
| $[2, 3, 1]$ | $10$ |
| $[3, 1, 2]$ | $9$ |
| $[3, 2, 1]$ | $10$ |

在第一个测试用例中，需输出长度为 3 的第 2 个符合条件的排列，看表格可以知道是 $[1, 3, 2]$。

在第二个测试用例中，需输出长度为 3 的第 3 个符合条件的排列，对应的是 $[2, 3, 1]$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6
3 2
3 3
4 11
4 6
6 39
7 34
```

### 输出

```
1 3 2 
2 3 1 
-1
2 4 3 1 
-1
2 3 4 5 7 6 1
```



---

---
title: "Non Prime Tree"
layout: "post"
diff: 普及+/提高
pid: CF2040D
tag: ['数学', '构造']
---

# Non Prime Tree

## 题目描述

给你一棵拥有 $n$ 个顶点的树。

你的任务是构造一个包含 $n$ 个不同整数的数组，这些整数从 $1$ 到 $2 \cdot n$ 分别取值。同时要求对于树中的任意一条边 $u_i \leftrightarrow v_i$，对应的数组元素差值 $|a_{u_i} - a_{v_i}|$ 不是质数。

请你找出任意一个符合以上条件的数组，如果不存在这样的数组，请输出 $-1$。

## 输入格式

每组测试用例包含多个测试。首行给出测试用例数量 $t$（$1 \le t \le 10^4$）。每个测试用例的描述如下：

第一行一个整数 $n$（$2 \le n \le 2 \cdot 10^5$），表示树的顶点数量。

接下来的 $n-1$ 行，每行描述一条树的边。具体来说，第 $i$ 行给出两个整数 $u_i$ 和 $v_i$（$1 \le u_i, v_i \le n$；$u_i \neq v_i$），表示节点 $u_i$ 和 $v_i$ 之间有边相连。

可以保证给定的边组成一棵树。此外，所有测试用例中的 $n$ 总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果找到满足条件的数组，输出该数组的元素 $a_1, a_2, \ldots, a_n$。如果找不到，则输出 $-1$。

## 说明/提示

如下图所示的答案中，用对应数组 $a$ 的元素替代了顶点编号：

第一组数据的树结构 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040D/d6a56c20ebd42ea20ac170d596c01c0583a1b831.png)  
第二组数据的树结构 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040D/8328682bcf4d0da5fcbe8de4a0054b43d22d093e.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
5
1 2
2 3
2 4
3 5
7
1 2
1 3
2 4
3 5
3 6
3 7
```

### 输出

```
2 10 1 6 5 
8 7 12 1 4 6 3
```



---

---
title: "Easy Demon Problem"
layout: "post"
diff: 普及+/提高
pid: CF2044F
tag: ['数学']
---

# Easy Demon Problem

## 题目描述

机器人定义了一个网格的美丽值，就是其中所有元素的总和。现在他给了你两个数组：一个长度为 $n$ 的数组 $a$ 和一个长度为 $m$ 的数组 $b$。你的任务是利用这两个数组建立一个 $n \times m$ 的网格 $M$，其中 $M_{i,j} = a_i \cdot b_j$ 对于所有的 $1 \leq i \leq n$ 和 $1 \leq j \leq m$ 均成立。

接下来，机器人会提供 $q$ 个查询。对于每个查询，会给出一个整数 $x$。你的目标是判断是否可以通过以下操作，使得网格 $M$ 的美丽值恰好为 $x$：

1. 选择一行 $r$ 和一列 $c$，满足 $1 \leq r \leq n$ 和 $1 \leq c \leq m$。
2. 将所有在第 $r$ 行或第 $c$ 列，或者同时位于这两者交叉处的元素设为 $0$。

需要注意的是，各个查询之间是相互独立的，这意味着你不必实际修改网格的元素为零——你只需判断是否存在这样的一对 $r$ 和 $c$，如果进行上述操作能使网格的美丽值为 $x$。即便网格的初始美丽值已经是 $x$，你仍然需要选择行和列并执行这个操作。

## 输入格式

第一行包含三个整数 $n$、$m$ 和 $q$，分别表示数组 $a$ 的长度、数组 $b$ 的长度，以及要处理的查询数量（$1 \leq n, m \leq 2 \times 10^5$，$1 \leq q \leq 5 \times 10^4$）。

第二行是 $n$ 个整数，表示数组 $a$ 中的元素：$a_1, a_2, \ldots, a_n$（$0 \leq |a_i| \leq n$）。

第三行是 $m$ 个整数，表示数组 $b$ 中的元素：$b_1, b_2, \ldots, b_m$（$0 \leq |b_i| \leq m$）。

接下来的 $q$ 行中，每行包含一个整数 $x$，表示希望网格经过设零操作后的美丽值（$1 \leq |x| \leq 2 \times 10^5$）。

## 输出格式

对于每个查询，如果存在一种操作能使网格的美丽值变为 $x$，输出「YES」（不带引号）；否则输出「NO」（不带引号）。无论「YES」或「NO」的大小写如何（例如，「yES」、「yes」或「Yes」），系统都会识别为正确答案。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3 3 6
-2 3 -3
-2 2 -1
-1
1
-2
2
-3
3
```

### 输出

```
NO
YES
NO
NO
YES
NO
```

## 样例 #2

### 输入

```
5 5 6
1 -2 3 0 0
0 -2 5 0 -3
4
-3
5
2
-1
2
```

### 输出

```
YES
YES
YES
YES
NO
YES
```



---

---
title: "ICPC Square"
layout: "post"
diff: 普及+/提高
pid: CF2045B
tag: ['数学']
---

# ICPC Square

## 题目描述

ICPC Square 是由 ICPC 委员会为参赛者安排住宿的酒店，共有 $N$ 层（编号从 $1$ 到 $N$）。酒店内的电梯非常独特：如果你目前在第 $x$ 层，你可以通过乘坐电梯到达第 $y$ 层，但要求 $y$ 是 $x$ 的倍数且 $y - x \leq D$。

你最初在第 $S$ 层。你想通过乘坐电梯零次或多次，尽量到达高的一层。请找出你能够到达的最高楼层。

## 输入格式

输入一行，包含三个整数：$N$、$D$、$S$。满足条件：$2 \leq N \leq 10^{12}$，$1 \leq D \leq N - 1$，$1 \leq S \leq N$。

## 输出格式

输出一个整数，表示你可以通过乘坐电梯零次或多次到达的最高楼层。

## 说明/提示

样例解释：

1. 首先，从第 3 层乘电梯到第 15 层，因为 15 是 3 的倍数且 $15 - 3 \leq 35$。
2. 然后，从第 15 层乘电梯到第 30 层，因为 30 是 15 的倍数且 $30 - 15 \leq 35$。
3. 最后，从第 30 层乘电梯到第 60 层，因为 60 是 30 的倍数且 $60 - 30 \leq 35$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
64 35 3
```

### 输出

```
60
```

## 样例 #2

### 输入

```
2024 2023 1273
```

### 输出

```
1273
```



---

---
title: "Kevin and Competition Memories"
layout: "post"
diff: 普及+/提高
pid: CF2048D
tag: ['贪心', '二分', '数学']
---

# Kevin and Competition Memories

## 题目描述

Kevin 曾经进入过 Rio 的记忆。在那段记忆中，曾举办过一系列的比赛。Kevin 还记得所有参赛者和比赛的问题，但具体的比赛轮次、问题分布和排名已经模糊不清。

有 $m$ 个比赛问题，第 $i$ 个问题的难度为 $b_i$。每场比赛选择 $k$ 个问题，因此总共会有 $\lfloor \frac{m}{k} \rfloor$ 场比赛。这意味着你可以任意组合选择这些比赛问题，并挑出总共 $\lfloor \frac{m}{k} \rfloor \cdot k$ 个问题参赛，每个问题最多只能被选一次，剩余 $m \bmod k$ 个问题将未被使用。例如，如果 $m = 17$ 且 $k = 3$，你将组织 $5$ 场比赛，每场 $3$ 个问题，会剩下 $2$ 个问题没有用上。

比赛有 $n$ 位参赛者，其中 Kevin 是第 1 位。第 $i$ 位参赛者的评分是 $a_i$。在比赛中，每个参赛者能解决难度不超过其评分的问题，具体来说，第 $i$ 位参赛者能解决第 $j$ 个问题，当且仅当 $a_i \geq b_j$。在每场比赛中，Kevin 的排名定义为那些比他解掉更多题目的参赛者数量加一。

对于每个 $k = 1, 2, \ldots, m$，Kevin 想知道在所有 $\lfloor \frac{m}{k} \rfloor$ 场比赛中的排名之和的最小可能值。也就是说，对于某个 $k$，你需要优化问题的选择和分配，使得 Kevin 的排名之和最小化。

不同的 $k$ 值代表的比赛是相互独立的。换言之，你可以对每个不同的 $k$ 值分别规划问题分配。

## 输入格式

输入包含多组测试数据。第一行为测试数据的组数 $t$（$1 \le t \le 5 \cdot 10^4$）。

每组测试数据的第一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 3 \cdot 10^5$），分别表示参赛者数量和问题数量。

接下来的行中，第二行列出 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \le a_i \le 10^9$）代表每个参赛者的评分。

第三行列出 $m$ 个整数 $b_1, b_2, \ldots, b_m$（$0 \le b_i \le 10^9$）代表每个问题的难度。

保证所有测试数据中的 $n$ 与 $m$ 的总和不超过 $3 \cdot 10^5$。

## 输出格式

对于每组测试数据，输出 $m$ 个整数，分别代表对于每个 $k = 1, 2, \ldots, m$，Kevin 的排名之和的最小可能值。

## 说明/提示

考虑第一个测试数据：

- 当 $k=1$ 时，每场比赛只包含一个问题，分配方式是唯一的。例如，在包含难度为 $4$ 的第三个问题的比赛中，除了第 2 位参赛者外，所有人都能解决。因为没有人比 Kevin 解出更多的问题，他在这场比赛中排名第 1。同理，在所有 $4$ 场比赛中，Kevin 的排名分别是 $1, 3, 1, 2$，总和为 $7$。

- 当 $k=2$ 时，最佳选择是将第 1 和第 3 个问题组成一场比赛，第 2 和第 4 个问题组成另一场。在前一场比赛中，4 名选手分别解决 $2, 1, 2, 2$ 个问题，Kevin 排名第 1；在后一场比赛中，选手分别解决 $0, 0, 2, 1$ 个问题，因有 2 位选手多解题，Kevin 排名第 $3$。所以总和是 $1 + 3 = 4$。这是最优解。

- 当 $k=3$ 时，可以选择第 1、3、4 个问题组成一场比赛，Kevin 的排名是 2，为最优。

- 当 $k=4$ 时，只有一场比赛，分配方式唯一，Kevin 的排名是 3。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
4 4
4 3 7 5
2 5 4 6
5 5
5 0 4 8 6
1 3 9 2 7
6 7
1 1 4 5 1 4
1 9 1 9 8 1 0
7 6
1 9 1 9 8 1 0
1 1 4 5 1 4
```

### 输出

```
7 4 2 3
6 2 1 1 2
7 3 2 1 1 1 1
15 9 5 4 4 4
```



---

---
title: "Refined Product Optimality"
layout: "post"
diff: 普及+/提高
pid: CF2053D
tag: ['数学', '贪心', '排序', '逆元']
---

# Refined Product Optimality

## 题目描述

As a tester, when my solution has a different output from the example during testing, I suspect the author first.

— Chris, [a comment](https://codeforces.com/blog/entry/133116?#comment-1190579)



Although Iris occasionally sets a problem where the solution is possibly wrong, she still insists on creating problems with her imagination; after all, everyone has always been on the road with their stubbornness... And like ever before, Iris has set a problem to which she gave a wrong solution, but Chris is always supposed to save it! You are going to play the role of Chris now:

- Chris is given two arrays $ a $ and $ b $ , both consisting of $ n $ integers.
- Iris is interested in the largest possible value of $ P = \prod\limits_{i=1}^n \min(a_i, b_i) $ after an arbitrary rearrangement of $ b $ . Note that she only wants to know the maximum value of $ P $ , and no actual rearrangement is performed on $ b $ .
- There will be $ q $ modifications. Each modification can be denoted by two integers $ o $ and $ x $ ( $ o $ is either $ 1 $ or $ 2 $ , $ 1 \leq x \leq n $ ). If $ o = 1 $ , then Iris will increase $ a_x $ by $ 1 $ ; otherwise, she will increase $ b_x $ by $ 1 $ .
- Iris asks Chris the maximum value of $ P $ for $ q + 1 $ times: once before any modification, then after every modification.
- Since $ P $ might be huge, Chris only needs to calculate it modulo $ 998\,244\,353 $ .

Chris soon worked out this problem, but he was so tired that he fell asleep. Besides saying thanks to Chris, now it is your turn to write a program to calculate the answers for given input data.

Note: since the input and output are large, you may need to optimize them for this problem.

For example, in C++, it is enough to use the following lines at the start of the main() function:

```
<pre class="lstlisting">```
int main() {<br></br>    std::ios::sync_with_stdio(false);<br></br>    std::cin.tie(nullptr); std::cout.tie(nullptr);<br></br>}<br></br>
```
```

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \leq n \leq 2\cdot 10^5 $ , $ 1 \leq q \leq 2\cdot 10^5 $ ) — the length of the array and the number of operations.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 5\cdot 10^8 $ ) — the array $ a $ .

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq 5\cdot 10^8 $ ) — the array $ b $ .

Then $ q $ lines follow, each line contains two integers $ o $ and $ x $ ( $ o \in \{1, 2\} $ , $ 1 \leq x \leq n $ ), representing an operation.

It's guaranteed that the sum of $ n $ and the sum of $ q $ over all test cases does not exceed $ 4\cdot 10^5 $ , respectively.

## 输出格式

For each test case, output $ q + 1 $ integers in a line, representing the answers that Chris will calculate, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case:

- Before the modifications, Chris can rearrange $ b $ to $ [1, 2, 3] $ so that $ P = \prod\limits_{i=1}^n \min(a_i, b_i) = 1 \cdot 1 \cdot 2 = 2 $ . We can prove that this is the maximum possible value. For example, if Chris rearranges $ b = [2, 3, 1] $ , $ P $ will be equal $ 1 \cdot 1 \cdot 1 = 1 < 2 $ , which is not optimal.
- After the first modification, Chris can rearrange $ b $ to $ [1, 2, 3] $ so that $ P = 1 \cdot 1 \cdot 3 = 3 $ , which is maximized.
- After the second modification, Chris can rearrange $ b $ to $ [2, 2, 3] $ so that $ P = 1 \cdot 1 \cdot 3 = 3 $ , which is maximized.
- After the third modification, Chris can rearrange $ b $ to $ [2, 2, 3] $ so that $ P = 6 $ , which is maximized.
- After the fourth modification, Chris can rearrange $ b $ to $ [2, 2, 4] $ so that $ P = 6 $ , which is maximized.

## 样例 #1

### 输入

```
4
3 4
1 1 2
3 2 1
1 3
2 3
1 1
2 1
6 8
1 4 2 7 3 5
7 6 5 6 3 3
2 5
1 6
1 5
1 5
1 5
2 3
2 3
1 6
13 8
7 7 6 6 5 5 5 2 2 3 4 5 1
1 4 1 9 6 6 9 1 5 1 3 8 4
2 2
2 11
2 4
2 4
1 7
1 1
2 12
1 5
5 3
10000000 20000000 30000000 40000000 50000000
10000000 20000000 30000000 40000000 50000000
1 1
2 2
2 1
```

### 输出

```
2 3 3 6 6
840 840 1008 1344 1680 2016 2016 2016 2352
2116800 2646000 3528000 3528000 3528000 4233600 4838400 4838400 4838400
205272023 205272023 205272023 264129429
```



---

---
title: "Even String"
layout: "post"
diff: 普及+/提高
pid: CF2086D
tag: ['背包 DP', '组合数学']
---

# Even String

## 题目描述

你需要构造一个由小写拉丁字母组成的字符串 $s$，满足以下条件：
- 对于任意两个满足 $s_{i} = s_{j}$ 的下标 $i$ 和 $j$，这两个下标之差的绝对值为偶数，即 $|i - j| \bmod 2 = 0$。

构造任意字符串太简单了，因此你会被给定一个包含 $26$ 个数字的数组 $c$ —— 表示字符串 $s$ 中每个字母必须出现的次数。也就是说，对于每个 $i \in [1, 26]$，拉丁字母表中的第 $i$ 个字母必须恰好出现 $c_i$ 次。

你的任务是计算满足所有这些条件的不同字符串 $s$ 的数量。由于答案可能非常大，请输出其对 $998\,244\,353$ 取模后的结果。

## 输入格式

每个测试包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 10^{4}$）—— 测试用例的数量。接下来是测试用例的描述。

每个测试用例包含 $26$ 个整数 $c_{i}$（$0 \le c_{i} \le 5 \cdot 10^{5}$）—— 数组 $c$ 的元素。

输入数据的额外限制：
- 每个测试用例的 $c_{i}$ 之和为正；
- 所有测试用例的 $c_{i}$ 之和不超过 $5 \cdot 10^{5}$。

## 输出格式

对于每个测试用例，输出一个整数 —— 满足条件的字符串 $s$ 的数量，对 $998\,244\,353$ 取模后的结果。


## 说明/提示

- 在第一个测试用例中，有 $4$ 个满足条件的字符串："abak"、"akab"、"baka" 和 "kaba"。


翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2 1 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
3 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 0 0 0 0 1 0 3 0 0 0 0 0 0 0 0 0 0 0
1 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 233527 233827
```

### 输出

```
4
960
0
1
789493841
```



---

---
title: "Simple Permutation"
layout: "post"
diff: 普及+/提高
pid: CF2089A
tag: ['数学', '构造']
---

# Simple Permutation

## 题目描述

给定一个整数 $n$。构造一个长度为 $n$ 的排列 $p_1, p_2, \ldots, p_n$，使其满足以下性质：

对于 $1 \le i \le n$，定义 $c_i = \lceil \frac{p_1 + p_2 + \ldots + p_i}{i} \rceil$，那么在 $c_1, c_2, \ldots, c_n$ 中必须至少有 $\lfloor \frac{n}{3} \rfloor - 1$ 个素数。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10$）——测试用例的数量。接下来描述每个测试用例。

每个测试用例的一行中包含一个整数 $n$（$2 \le n \le 10^5$）——排列的大小。

## 输出格式

对于每个测试用例，输出满足条件的排列 $p_1, p_2, \ldots, p_n$。题目保证这样的排列总是存在。

## 说明/提示

第一个测试案例中，$c_1 = \lceil \frac{2}{1} \rceil = 2$，$c_2 = \lceil \frac{2+1}{2} \rceil = 2$。这两个数都是素数。

第三个测试案例中，$c_1 = \lceil \frac{2}{1} \rceil = 2$，$c_2 = \lceil \frac{3}{2} \rceil = 2$，$c_3 = \lceil \frac{6}{3} \rceil = 2$，$c_4 = \lceil \frac{10}{4} \rceil = 3$，$c_5 = \lceil \frac{15}{5} \rceil = 3$。所有这些数都是素数。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
2
3
5
```

### 输出

```
2 1
2 1 3
2 1 3 4 5
```



---

---
title: "She knows..."
layout: "post"
diff: 普及+/提高
pid: CF2092E
tag: ['数学', '组合数学']
---

# She knows...

## 题目描述

D. Pippy 正在为家中的"黑白派对"做准备。他只需要重新粉刷地下室的 floor，该 floor 可表示为 $n \times m$ 的棋盘。

在上次派对后，整个棋盘除 $k$ 个单元格 $(x_1, y_1), (x_2, y_2), \ldots, (x_k, y_k)$ 外均被涂成绿色，这些单元格已被涂成白色或黑色。为了即将到来的派对，D. Pippy 想要将剩余的绿色单元格涂成黑色或白色。同时，他要求重新粉刷后棋盘上相邻颜色不同的单元格对数量为偶数。

形式化地，若定义集合：
$$A = \left\{((i_1, j_1), (i_2, j_2)) \ | \ 1 \le i_1, i_2 \le n, 1 \le j_1, j_2 \le m, i_1+j_1 < i_2+j_2, |i_1-i_2|+|j_1-j_2| = 1, \operatorname{color}(i_1, j_1) \neq \operatorname{color}(i_2, j_2) \right\},$$
其中 $\operatorname{color}(x, y)$ 表示单元格 $(x, y)$ 的颜色，则要求 $|A|$ 为偶数。

请帮助 D. Pippy 计算满足条件的粉刷方案数。由于答案可能很大，请输出其对 $10^9 + 7$ 取模的结果。

## 输入格式

每个测试包含多个测试用例。输入数据第一行包含一个整数 $t$ ($1 \le t \le 10^4$) —— 测试用例数量。接下来是测试用例描述。

每个测试用例的第一行包含三个整数 $n, m, k$ ($3 \le n, m \le 10^9$; $1 \le k \le 2 \cdot 10^5$) —— 棋盘的尺寸和初始非绿色单元格的数量。

接下来每个测试用例的 $k$ 行中，第 $i$ 行包含三个整数 $x_i, y_i$ 和 $c_i$ ($1 \le x_i \le n$; $1 \le y_i \le m$; $c_i \in \{0, 1\}$) —— 单元格的坐标及其颜色（白色对应 $c_i = 0$，黑色对应 $c_i = 1$）。保证所有单元格坐标互不相同。

保证所有测试用例的 $k$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数 —— 答案对 $10^9 + 7$ 取模的结果。


## 说明/提示

第一个测试案例中，绿色单元格 $(2, 1), (2, 2), (2, 3)$ 共有 $4$ 种合法涂色方案，分别为：$(1, 1, 0)$，$(0, 0, 1)$，$(1, 0, 0)$，$(0, 1, 1)$（颜色按单元格顺序排列），如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2092E/0ff35e90f545116ecc7d2fbe2de16f35bcaedb89.png)  
第二个测试案例中，棋盘已全部涂色且相邻异色对数量为奇数，因此答案为 $0$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
3 3 6
1 1 0
1 2 1
1 3 0
3 1 1
3 2 0
3 3 1
3 4 12
1 1 0
1 2 1
1 3 0
1 4 1
2 1 1
2 2 0
2 3 1
2 4 0
3 1 0
3 2 1
3 3 0
3 4 1
```

### 输出

```
4
0
```



---

---
title: "Small Operations"
layout: "post"
diff: 普及+/提高
pid: CF2114F
tag: ['动态规划 DP', '搜索', '数学', '记忆化搜索', '最大公约数 gcd']
---

# Small Operations

## 题目描述

给你两个正整数 $x,k$。进行以下两种变换之一称为一次操作：
- 选择一个满足 $1 \le a \le k$ 的正整数 $a$，使 $x$ 变为 $x\cdot a$；
- 选择一个满足 $1 \le a \le k$ 的正整数 $a$，使 $x$ 变为 $\frac{x}{a}$，要求操作完后 $x$ 值是整数。

你需要找出使 $x$ 变为给定正整数 $y$ 的最小操作次数，或判断无解。

## 输入格式

第一行，一个正整数 $t\ (1 \le t \le {10}^4)$，表示测试数据组数。

对于每组测试数据，一行三个正整数 $x,y,k\ (1 \le x,y,k \le {10}^6)$。

保证所有测试数据中 $x$ 的总和与 $y$ 的总和均不超过 ${10}^8$。

## 输出格式

对于每组测试数据，如果无解输出 $-1$，否则输出使 $x$ 变为 $y$ 的最小操作次数。

## 说明/提示

对于第一组测试数据，我们可以选择 $a=2$，将 $x$ 除以 $2$，然后选择 $a=3$，将 $x$ 乘上 $3$，此时 $x$ 将变为 $6$，等于 $y$。

对于第二组测试数据，可以证明其不可能。

对于第七组测试数据，我们可以分别选择 $a=7,9,10,10,12,13$，连续做 $6$ 次乘法。可以证明没有比这更少的操作次数了。

## 样例 #1

### 输入

```
8
4 6 3
4 5 3
4 6 2
10 45 3
780 23 42
11 270 23
1 982800 13
1 6 2
```

### 输出

```
2
-1
-1
3
3
3
6
-1
```



---

---
title: "Wildflower"
layout: "post"
diff: 普及+/提高
pid: CF2117F
tag: ['数学', 'Ad-hoc']
---

# Wildflower

## 题目描述

Yousef 有一棵包含 $n$ 个结点，以结点 $1$ 为根的树 $^*$。你打算给 Yousef 一个长度为 $n$ 的数组 $a$，其中每个元素 $a_i$（$1 \le i \le n$）可以是 $1$ 或者 $2$。

我们记结点 $u$ 的子树中所有结点 $v$ 对应的 $a_v$ 之和为 $s_u$。如果这些 $s_u$ 两两不同，即所有的子树权值之和不同，那么 Yousef 会认为这棵树是特别的。

你的任务是帮助 Yousef 统计数组 $a$ 的数目，要求它能使得树是特别的。若存在一个下标 $i$ 使得两个数组 $b$ 和 $c$ 满足 $b_i \neq c_i$，则称 $b$ 和 $c$ 是不同的。

由于答案可能非常大，你需要输出答案模 $10^9+7$ 的结果。

$^*$ 一棵树是一个包含 $n-1$ 条边的无向连通图。

$^\dagger$ 结点 $v$ 的子树是指所有在通往根结点的简单路径上必须经过结点 $v$ 的结点构成的集合。

## 输入格式

输入数据包含多个测试用例。输入数据的第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的个数。

对于每个测试用例：

- 第一行包含一个整数 $n$（$2 \le n \le 2 \cdot 10^5$），表示树中结点的个数。
- 接下来 $n-1$ 行中每行包含两个整数 $u$ 和 $v$（$1 \le u,v \le n$），表示一条连接结点 $u$ 和 $v$ 的边。输入数据保证这些边组成了一棵树，且树中没有自环或重边。

输入数据保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一行一个整数 $x$，表示能够使得树变得特别的数组 $a$ 的个数，模 $10^9+7$ 之后的结果。

## 说明/提示

如图是第五个测试用例所对应的树。

## 样例 #1

### 输入

```
7
2
1 2
8
1 2
2 3
3 8
2 4
4 5
5 6
6 7
10
1 2
2 3
3 4
4 5
5 6
4 7
7 8
4 9
9 10
7
1 4
4 2
3 2
3 5
2 6
6 7
7
1 2
2 3
3 4
3 5
4 6
6 7
7
5 7
4 6
1 6
1 3
2 6
6 7
5
3 4
1 2
1 3
2 5
```

### 输出

```
4
24
0
16
48
0
4
```



---

---
title: "Matrix game"
layout: "post"
diff: 普及+/提高
pid: CF2120D
tag: ['组合数学', '鸽笼原理']
---

# Matrix game

## 题目描述

Aryan and Harshith play a game. They both start with three integers $ a $ , $ b $ , and $ k $ . Aryan then gives Harshith two integers $ n $ and $ m $ . Harshith then gives Aryan a matrix $ X $ with $ n $ rows and $ m $ columns, such that each of the elements of $ X $ is between $ 1 $ and $ k $ (inclusive). After that, Aryan wins if he can find a submatrix $ ^{\text{∗}} $ $ Y $ of $ X $ with $ a $ rows and $ b $ columns such that all elements of $ Y $ are equal.

For example, when $ a=2, b=2, k=6, n=3 $ and $ m=3 $ , if Harshith gives Aryan the matrix below, it is a win for Aryan as it has a submatrix of size $ 2\times 2 $ with all elements equal to $ 1 $ as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120D/ff9ee31dfc04aa73a7daca458dede1d4462758ef.png) Example of a matrix where Aryan wins Aryan gives you the values of $ a $ , $ b $ , and $ k $ . He asks you to find the lexicographically minimum tuple $ (n,m) $ that he should give to Harshith such that Aryan always wins. Help Aryan win the game. Assume that Harshith plays optimally. The values of $ n $ and $ m $ can be large, so output them modulo $ 10^9+7 $ . A tuple $ (n_1, m_1) $ is said to be lexicographically smaller than $ (n_2, m_2) $ if either $ n_1<n_2 $ or $ n_1=n_2 $ and $ m_1<m_2 $ .

 $ ^{\text{∗}} $ A submatrix of a matrix is obtained by removing some rows and/or columns from the original matrix.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

Each test case contains a single line with three space-separated integers $ a, b $ and $ k $ ( $ 1\leq a,b,k\leq 10^5 $ ).

It is guaranteed that the sum of $ \max(a, b, k) $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single line containing two space-separated integers $ n $ and $ m $ , denoting the answer to the problem. The values of $ n $ and $ m $ can be large, so output them modulo $ 10^9+7 $ .

## 说明/提示

For the first test case, every $ n\times m $ matrix contains a $ 1\times 1 $ submatrix with all elements equal. $ (1,1) $ is the lexicographically minimum tuple among all of them.

For the second test case, it can be verified that whatever $ 3\times 7 $ matrix Harshith gives to Aryan, Aryan can always win by finding a $ 2\times 2 $ submatrix with all elements equal. $ (3,7) $ is also the lexicographically minimum tuple among all possible tuples where Aryan always wins.

## 样例 #1

### 输入

```
3
1 1 5
2 2 2
90000 80000 70000
```

### 输出

```
1 1
3 7
299929959 603196135
```



---

---
title: "Numbers"
layout: "post"
diff: 普及+/提高
pid: CF213B
tag: ['动态规划 DP', '枚举', '组合数学']
---

# Numbers

## 题目描述

Furik loves writing all sorts of problems, especially such that he can't solve himself. You've got one of his problems, the one Furik gave to Rubik. And Rubik asks you to solve it.

There is integer $ n $ and array $ a $ , consisting of ten integers, indexed by numbers from 0 to 9. Your task is to count the number of positive integers with the following properties:

- the number's length does not exceed $ n $ ;
- the number doesn't have leading zeroes;
- digit $ i $ $ (0<=i<=9) $ occurs in the number at least $ a[i] $ times.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=100) $ . The next line contains 10 integers $ a[0] $ , $ a[1] $ , $ ... $ , $ a[9] $ $ (0<=a[i]<=100) $ — elements of array $ a $ . The numbers are separated by spaces.

## 输出格式

On a single line print the remainder of dividing the answer to the problem by $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample number 9 meets the requirements.

In the second sample number 10 meets the requirements.

In the third sample numbers 10, 110, 210, 120, 103 meet the requirements. There are other suitable numbers, 36 in total.

## 样例 #1

### 输入

```
1
0 0 0 0 0 0 0 0 0 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
1 1 0 0 0 0 0 0 0 0

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3
1 1 0 0 0 0 0 0 0 0

```

### 输出

```
36

```



---

---
title: "The least round way"
layout: "post"
diff: 普及+/提高
pid: CF2B
tag: ['动态规划 DP', '数学']
---

# The least round way

## 题目描述

给定由非负整数组成的 $n\times n$ 的正方形矩阵，你需要寻找一条路径：

+ 以左上角为起点。
+ 每次只能向右或向下走。
+ 以右下角为终点。
+ 如果我们把沿路遇到的数进行相乘，积应当以尽可能少的 $0$ 结尾。

## 输入格式

第一行包含一个整数 $n (2 \leq n \leq 1000)$，$n$ 为矩阵的规模，接下来的 $n$ 行包含矩阵的元素（不超过 $10^9$ 的非负整数）。

## 输出格式

第一行应包含结尾最少的 $0$ 的个数，第二行打印出相应的路径（译注：`D` 为下，`R`  为右）。

## 样例 #1

### 输入

```
3
1 2 3
4 5 6
7 8 9

```

### 输出

```
0
DDRR

```



---

---
title: "Wonderful Randomized Sum"
layout: "post"
diff: 普及+/提高
pid: CF33C
tag: ['数学', '贪心', '前缀和']
---

# Wonderful Randomized Sum

## 题目描述

Learn, learn and learn again — Valera has to do this every day. He is studying at mathematical school, where math is the main discipline. The mathematics teacher loves her discipline very much and tries to cultivate this love in children. That's why she always gives her students large and difficult homework. Despite that Valera is one of the best students, he failed to manage with the new homework. That's why he asks for your help. He has the following task. A sequence of $ n $ numbers is given. A prefix of a sequence is the part of the sequence (possibly empty), taken from the start of the sequence. A suffix of a sequence is the part of the sequence (possibly empty), taken from the end of the sequence. It is allowed to sequentially make two operations with the sequence. The first operation is to take some prefix of the sequence and multiply all numbers in this prefix by $ -1 $ . The second operation is to take some suffix and multiply all numbers in it by $ -1 $ . The chosen prefix and suffix may intersect. What is the maximum total sum of the sequence that can be obtained by applying the described operations?

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — amount of elements in the sequence. The second line contains $ n $ integers $ a_{i} $ ( $ -10^{4}<=a_{i}<=10^{4} $ ) — the sequence itself.

## 输出格式

The first and the only line of the output should contain the answer to the problem.

## 样例 #1

### 输入

```
3
-1 -2 -3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5
-4 2 0 5 0

```

### 输出

```
11

```

## 样例 #3

### 输入

```
5
-1 10 -5 10 -2

```

### 输出

```
18

```



---

---
title: "Pluses everywhere"
layout: "post"
diff: 普及+/提高
pid: CF520E
tag: ['组合数学']
---

# Pluses everywhere

## 题目描述

Vasya is sitting on an extremely boring math class. To have fun, he took a piece of paper and wrote out $ n $ numbers on a single line. After that, Vasya began to write out different ways to put pluses ("+") in the line between certain digits in the line so that the result was a correct arithmetic expression; formally, no two pluses in such a partition can stand together (between any two adjacent pluses there must be at least one digit), and no plus can stand at the beginning or the end of a line. For example, in the string 100500, ways 100500 (add no pluses), 1+00+500 or 10050+0 are correct, and ways 100++500, +1+0+0+5+0+0 or 100500+ are incorrect.

The lesson was long, and Vasya has written all the correct ways to place exactly $ k $ pluses in a string of digits. At this point, he got caught having fun by a teacher and he was given the task to calculate the sum of all the resulting arithmetic expressions by the end of the lesson (when calculating the value of an expression the leading zeros should be ignored). As the answer can be large, Vasya is allowed to get only its remainder modulo $ 10^{9}+7 $ . Help him!

## 输入格式

The first line contains two integers, $ n $ and $ k $ ( $ 0<=k&lt;n<=10^{5} $ ).

The second line contains a string consisting of $ n $ digits.

## 输出格式

Print the answer to the problem modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample the result equals $ (1+08)+(10+8)=27 $ .

In the second sample the result equals $ 1+0+8=9 $ .

## 样例 #1

### 输入

```
3 1
108

```

### 输出

```
27
```

## 样例 #2

### 输入

```
3 2
108

```

### 输出

```
9
```



---

---
title: "Om Nom and Candies"
layout: "post"
diff: 普及+/提高
pid: CF526C
tag: ['数学', '数论']
---

# Om Nom and Candies

## 题目描述

桌子上有无限多的红糖果与蓝糖果，每个红糖果重 $ W_{r} $ 克，而每个蓝糖果重 $ W_{b} $ 克。吃一颗红糖果可以获得 $ H_{r} $ 的快乐值，吃一颗蓝糖果可以获得 $ H_{b} $ 的快乐值。

在只能吃 $ C $ 克糖果的前提下，请求出能获得的最大快乐值。

## 输入格式

五个整数：$ C,H_{r},H_{b},W_{r},W_{b} $（$1 \leq C,H_{r},H_{b},W_{r},W_{b}  \leq 10^9$）

## 输出格式

出输出一个整数：能达到的最大快乐值。

## 样例 #1

### 输入

```
10 3 5 2 3

```

### 输出

```
16

```



---

---
title: "Array"
layout: "post"
diff: 普及+/提高
pid: CF57C
tag: ['数学', '组合数学', '逆元']
---

# Array

## 题目描述

Chris the Rabbit has been interested in arrays ever since he was a child. At the moment he is researching arrays with the length of $ n $ , containing only integers from $ 1 $ to $ n $ . He is not good at math, that's why some simple things drive him crazy. For example, yesterday he grew keen on counting how many different beautiful arrays there are. Chris thinks that an array is beautiful if it meets one of the two conditions:

- each elements, starting from the second one, is no more than the preceding one
- each element, starting from the second one, is no less than the preceding one

Having got absolutely mad at himself and at math, Chris came to Stewie and Brian to ask them for help. However, they only laughed at him and said that the answer is too simple and not interesting. Help Chris the Rabbit to find the answer at last.

## 输入格式

The single line contains an integer $ n $ which is the size of the array ( $ 1<=n<=10^{5} $ ).

## 输出格式

You must print the answer on a single line. As it can be rather long, you should print it modulo $ 1000000007 $ .

## 样例 #1

### 输入

```
2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3

```

### 输出

```
17

```



---

---
title: "Peter and Snow Blower"
layout: "post"
diff: 普及+/提高
pid: CF613A
tag: ['模拟', '数学', '构造']
---

# Peter and Snow Blower

## 题目描述

Peter got a new snow blower as a New Year present. Of course, Peter decided to try it immediately. After reading the instructions he realized that it does not work like regular snow blowing machines. In order to make it work, you need to tie it to some point that it does not cover, and then switch it on. As a result it will go along a circle around this point and will remove all the snow from its path.

Formally, we assume that Peter's machine is a polygon on a plane. Then, after the machine is switched on, it will make a circle around the point to which Peter tied it (this point lies strictly outside the polygon). That is, each of the points lying within or on the border of the polygon will move along the circular trajectory, with the center of the circle at the point to which Peter tied his machine.

Peter decided to tie his car to point $ P $ and now he is wondering what is the area of ​​the region that will be cleared from snow. Help him.

## 输入格式

The first line of the input contains three integers — the number of vertices of the polygon $ n $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/e07eddcf01ea19e02be99447a5d31677c12c0459.png)), and coordinates of point $ P $ .

Each of the next $ n $ lines contains two integers — coordinates of the vertices of the polygon in the clockwise or counterclockwise order. It is guaranteed that no three consecutive vertices lie on a common straight line.

All the numbers in the input are integers that do not exceed $ 1000000 $ in their absolute value.

## 输出格式

Print a single real value number — the area of the region that will be cleared. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 说明/提示

In the first sample snow will be removed from that area:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/d58837ea7895097f43b3c725628f9a11757bb6b3.png)

## 样例 #1

### 输入

```
3 0 0
0 1
-1 2
1 2

```

### 输出

```
12.566370614359172464

```

## 样例 #2

### 输入

```
4 1 -1
0 0
1 2
2 0
1 1

```

### 输出

```
21.991148575128551812

```



---

---
title: "Remove Extra One"
layout: "post"
diff: 普及+/提高
pid: CF900C
tag: ['数学', '树状数组']
---

# Remove Extra One

## 题目描述

You are given a permutation $ p $ of length $ n $ . Remove one element from permutation to make the number of records the maximum possible.

We remind that in a sequence of numbers $ a_{1},a_{2},...,a_{k} $ the element $ a_{i} $ is a record if for every integer $ j $ ( $ 1<=j&lt;i $ ) the following holds: $ a_{j}&lt;a_{i} $ .

## 输入格式

The first line contains the only integer $ n $ ( $ 1<=n<=10^{5} $ ) — the length of the permutation.

The second line contains $ n $ integers $ p_{1},p_{2},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — the permutation. All the integers are distinct.

## 输出格式

Print the only integer — the element that should be removed to make the number of records the maximum possible. If there are multiple such elements, print the smallest one.

## 说明/提示

In the first example the only element can be removed.

## 样例 #1

### 输入

```
1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
5 1 2 3 4

```

### 输出

```
5

```



---

---
title: "Inversion Counting"
layout: "post"
diff: 普及+/提高
pid: CF911D
tag: ['数学', '平衡树', '树状数组']
---

# Inversion Counting

## 题目描述

A permutation of size $ n $ is an array of size $ n $ such that each integer from $ 1 $ to $ n $ occurs exactly once in this array. An inversion in a permutation $ p $ is a pair of indices $ (i,j) $ such that $ i>j $ and $ a_{i}<a_{j} $ . For example, a permutation $ [4,1,3,2] $ contains $ 4 $ inversions: $ (2,1) $ , $ (3,1) $ , $ (4,1) $ , $ (4,3) $ .

You are given a permutation $ a $ of size $ n $ and $ m $ queries to it. Each query is represented by two indices $ l $ and $ r $ denoting that you have to reverse the segment $ [l,r] $ of the permutation. For example, if $ a=[1,2,3,4] $ and a query $ l=2 $ , $ r=4 $ is applied, then the resulting permutation is $ [1,4,3,2] $ .

After each query you have to determine whether the number of inversions is odd or even.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=1500 $ ) — the size of the permutation.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=n $ ) — the elements of the permutation. These integers are pairwise distinct.

The third line contains one integer $ m $ ( $ 1<=m<=2·10^{5} $ ) — the number of queries to process.

Then $ m $ lines follow, $ i $ -th line containing two integers $ l_{i} $ , $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) denoting that $ i $ -th query is to reverse a segment $ [l_{i},r_{i}] $ of the permutation. All queries are performed one after another.

## 输出格式

Print $ m $ lines. $ i $ -th of them must be equal to odd if the number of inversions in the permutation after $ i $ -th query is odd, and even otherwise.

## 说明/提示

The first example:

1. after the first query $ a=[2,1,3] $ , inversion: $ (2,1) $ ;
2. after the second query $ a=[2,3,1] $ , inversions: $ (3,1) $ , $ (3,2) $ .

The second example:

1. $ a=[1,2,4,3] $ , inversion: $ (4,3) $ ;
2. $ a=[3,4,2,1] $ , inversions: $ (3,1) $ , $ (4,1) $ , $ (3,2) $ , $ (4,2) $ , $ (4,3) $ ;
3. $ a=[1,2,4,3] $ , inversion: $ (4,3) $ ;
4. $ a=[1,4,2,3] $ , inversions: $ (3,2) $ , $ (4,2) $ .

## 样例 #1

### 输入

```
3
1 2 3
2
1 2
2 3

```

### 输出

```
odd
even

```

## 样例 #2

### 输入

```
4
1 2 4 3
4
1 1
1 4
1 4
2 3

```

### 输出

```
odd
odd
odd
even

```



---

---
title: "A Leapfrog in the Array"
layout: "post"
diff: 普及+/提高
pid: CF949B
tag: ['数学', '树状数组', '进制']
---

# A Leapfrog in the Array

## 题目描述

## 题意:
Dima是一名初级程序员。 在他的工作中，他经常不断地重复以下操作：从数组中删除每个第二个元素。 有一天，他对这个问题的解决方案感到厌倦，他提出了以下华丽的算法。

假设有一长度为2n的数组，最初的数组包含从1到n的n个数字，数字i位于序号为2i - 1的单元格中（序号从1开始编号），并且数组的其他单元格为空。每个步骤你需要选择一个最大序号的非空单元格，并将其中的数字移动到它左边最近的空单元格。一直循环该过程，直到所有n个数字出现在数组的前n个单元格中。例如，如果n = 4，则数组更改如下：
![这里写图片描述](http://codeforces.com/predownloaded/1e/83/1e838f4fb99d933b7259fbfe5b8722990c08d718.png)
您必须编写一个程序，输出在该算法完成后，序号为x（1≤x≤n）的单元格中的数字。

## 输入格式

第一行包含两个整数n和q（1≤n≤1e18，1≤q≤200 000），数组中元素的数量以及查询数量。

接下来的q行包含一个整数xi（1≤xi≤n），xi为算法完成后，第xi个单元格。

## 输出格式

对于q个查询中的每一个，输出一个整数，即相应数组单元格中的值。

## 样例:
```
inputCopy
4 3
2
3
4
outputCopy
3
2
4
```
```
inputCopy
13 4
10
5
4
8
outputCopy
13
3
8
9
```
翻译提供者：xjdx

## 样例 #1

### 输入

```
4 3
2
3
4

```

### 输出

```
3
2
4

```

## 样例 #2

### 输入

```
13 4
10
5
4
8

```

### 输出

```
13
3
8
9

```



---

---
title: "Tufurama"
layout: "post"
diff: 普及+/提高
pid: CF961E
tag: ['数学', '可持久化线段树', '级数']
---

# Tufurama

## 题目描述

One day Polycarp decided to rewatch his absolute favourite episode of well-known TV series "Tufurama". He was pretty surprised when he got results only for season 7 episode 3 with his search query of "Watch Tufurama season 3 episode 7 online full hd free". This got Polycarp confused — what if he decides to rewatch the entire series someday and won't be able to find the right episodes to watch? Polycarp now wants to count the number of times he will be forced to search for an episode using some different method.

TV series have $ n $ seasons (numbered $ 1 $ through $ n $ ), the $ i $ -th season has $ a_{i} $ episodes (numbered $ 1 $ through $ a_{i} $ ). Polycarp thinks that if for some pair of integers $ x $ and $ y $ ( $ x<y $ ) exist both season $ x $ episode $ y $ and season $ y $ episode $ x $ then one of these search queries will include the wrong results. Help Polycarp to calculate the number of such pairs!

## 输入格式

The first line contains one integer $ n $ $ (1<=n<=2·10^{5}) $ — the number of seasons.

The second line contains $ n $ integers separated by space $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ — number of episodes in each season.

## 输出格式

Print one integer — the number of pairs $ x $ and $ y $ ( $ x<y $ ) such that there exist both season $ x $ episode $ y $ and season $ y $ episode $ x $ .

## 说明/提示

Possible pairs in the second example:

1. $ x=1 $ , $ y=2 $ (season 1 episode 2 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 2 episode 1);
2. $ x=2 $ , $ y=3 $ (season 2 episode 3 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 3 episode 2);
3. $ x=1 $ , $ y=3 $ (season 1 episode 3 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 3 episode 1).

In the third example:

1. $ x=1 $ , $ y=2 $ (season 1 episode 2 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 2 episode 1);
2. $ x=1 $ , $ y=3 $ (season 1 episode 3 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 3 episode 1).

## 样例 #1

### 输入

```
5
1 2 3 4 5

```

### 输出

```
0

```

## 样例 #2

### 输入

```
3
8 12 7

```

### 输出

```
3

```

## 样例 #3

### 输入

```
3
3 2 1

```

### 输出

```
2

```



---

