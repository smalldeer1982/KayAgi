---
title: "Relatively Prime Graph"
layout: "post"
diff: 普及+/提高
pid: CF1009D
tag: ['枚举']
---

# Relatively Prime Graph

## 题目描述

我们将一个无向图称作互质图，当且仅当对于其中每一条边$(v, u)$有$v$和$u$互质（也即$GCD(v,u)=1$）。当两个顶点之间没有边时不需要考虑。顶点从1开始标号。

现在给你$n$个顶点和$m$条边，要求你建立一个无重边和自环并且连通的互质图，如果无法构造输出"Impossible"，对于多种可能的答案输出任意一种即可。

## 输入格式

顶点数$n$，边数$m$。($1≤n,m≤10^5$)

## 输出格式

如果不存在答案输出"Impossible"。否则第一行输出"Possible"，接下来m行每行输出$v_i, u_i$（$1≤v_i,u_i≤n,v_i≠u_i$）。

## 样例 #1

### 输入

```
5 6

```

### 输出

```
Possible
2 5
3 2
5 1
3 4
4 1
5 4

```

## 样例 #2

### 输入

```
6 12

```

### 输出

```
Impossible

```



---

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
title: "Vasya and Triangle"
layout: "post"
diff: 普及+/提高
pid: CF1030D
tag: ['枚举', '素数判断,质数,筛法', '构造']
---

# Vasya and Triangle

## 题目描述

Vasya has got three integers $ n $ , $ m $ and $ k $ . He'd like to find three integer points $ (x_1, y_1) $ , $ (x_2, y_2) $ , $ (x_3, y_3) $ , such that $ 0 \le x_1, x_2, x_3 \le n $ , $ 0 \le y_1, y_2, y_3 \le m $ and the area of the triangle formed by these points is equal to $ \frac{nm}{k} $ .

Help Vasya! Find such points (if it's possible). If there are multiple solutions, print any of them.

## 输入格式

The single line contains three integers $ n $ , $ m $ , $ k $ ( $ 1\le n, m \le 10^9 $ , $ 2 \le k \le 10^9 $ ).

## 输出格式

If there are no such points, print "NO".

Otherwise print "YES" in the first line. The next three lines should contain integers $ x_i, y_i $ — coordinates of the points, one point per line. If there are multiple solutions, print any of them.

You can print each letter in any case (upper or lower).

## 说明/提示

In the first example area of the triangle should be equal to $ \frac{nm}{k} = 4 $ . The triangle mentioned in the output is pictured below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030D/7ee3f0a3ce75449bbc8ed199a32a394763a46df2.png)In the second example there is no triangle with area $ \frac{nm}{k} = \frac{16}{7} $ .

## 样例 #1

### 输入

```
4 3 3

```

### 输出

```
YES
1 0
2 3
4 1

```

## 样例 #2

### 输入

```
4 4 7

```

### 输出

```
NO

```



---

---
title: "Vasya and Good Sequences"
layout: "post"
diff: 普及+/提高
pid: CF1030E
tag: ['动态规划 DP', '枚举', '进制']
---

# Vasya and Good Sequences

## 题目描述

Vasya has a sequence $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . Vasya may pefrom the following operation: choose some number from the sequence and swap any pair of bits in its binary representation. For example, Vasya can transform number $ 6 $ $ (\dots 00000000110_2) $ into $ 3 $ $ (\dots 00000000011_2) $ , $ 12 $ $ (\dots 000000001100_2) $ , $ 1026 $ $ (\dots 10000000010_2) $ and many others. Vasya can use this operation any (possibly zero) number of times on any number from the sequence.

Vasya names a sequence as good one, if, using operation mentioned above, he can obtain the sequence with [bitwise exclusive or](https://en.wikipedia.org/wiki/Exclusive_or) of all elements equal to $ 0 $ .

For the given sequence $ a_1, a_2, \ldots, a_n $ Vasya'd like to calculate number of integer pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ and sequence $ a_l, a_{l + 1}, \dots, a_r $ is good.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — length of the sequence.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^{18} $ ) — the sequence $ a $ .

## 输出格式

Print one integer — the number of pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ and the sequence $ a_l, a_{l + 1}, \dots, a_r $ is good.

## 说明/提示

In the first example pairs $ (2, 3) $ and $ (1, 3) $ are valid. Pair $ (2, 3) $ is valid since $ a_2 = 7 \rightarrow 11 $ , $ a_3 = 14 \rightarrow 11 $ and $ 11 \oplus 11 = 0 $ , where $ \oplus $ — bitwise exclusive or. Pair $ (1, 3) $ is valid since $ a_1 = 6 \rightarrow 3 $ , $ a_2 = 7 \rightarrow 13 $ , $ a_3 = 14 \rightarrow 14 $ and $ 3 \oplus 13 \oplus 14 = 0 $ .

In the second example pairs $ (1, 2) $ , $ (2, 3) $ , $ (3, 4) $ and $ (1, 4) $ are valid.

## 样例 #1

### 输入

```
3
6 7 14

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4
1 2 1 16

```

### 输出

```
4

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
title: "Palindrome Pairs"
layout: "post"
diff: 普及+/提高
pid: CF1045I
tag: ['字符串', '枚举', '进制']
---

# Palindrome Pairs

## 题目描述

After learning a lot about space exploration, a little girl named Ana wants to change the subject.

Ana is a girl who loves palindromes (string that can be read the same backwards as forward). She has learned how to check for a given string whether it's a palindrome or not, but soon she grew tired of this problem, so she came up with a more interesting one and she needs your help to solve it:

You are given an array of strings which consist of only small letters of the alphabet. Your task is to find how many palindrome pairs are there in the array. A palindrome pair is a pair of strings such that the following condition holds: at least one permutation of the concatenation of the two strings is a palindrome. In other words, if you have two strings, let's say "aab" and "abcac", and you concatenate them into "aababcac", we have to check if there exists a permutation of this new string such that it is a palindrome (in this case there exists the permutation "aabccbaa").

Two pairs are considered different if the strings are located on different indices. The pair of strings with indices $ (i,j) $ is considered the same as the pair $ (j,i) $ .

## 输入格式

The first line contains a positive integer $ N $ ( $ 1 \le N \le 100\,000 $ ), representing the length of the input array.

Eacg of the next $ N $ lines contains a string (consisting of lowercase English letters from 'a' to 'z') — an element of the input array.

The total number of characters in the input array will be less than $ 1\,000\,000 $ .

## 输出格式

Output one number, representing how many palindrome pairs there are in the array.

## 说明/提示

The first example:

1. aa $ + $ bb $ \to $ abba.

The second example:

1. aab $ + $ abcac $ = $ aababcac $ \to $ aabccbaa
2. aab $ + $ aa $ = $ aabaa
3. abcac $ + $ aa $ = $ abcacaa $ \to $ aacbcaa
4. dffe $ + $ ed $ = $ dffeed $ \to $ fdeedf
5. dffe $ + $ aade $ = $ dffeaade $ \to $ adfaafde
6. ed $ + $ aade $ = $ edaade $ \to $ aeddea

## 样例 #1

### 输入

```
3
aa
bb
cd

```

### 输出

```
1

```

## 样例 #2

### 输入

```
6
aab
abcac
dffe
ed
aa
aade

```

### 输出

```
6

```



---

---
title: "Maximum Subrectangle"
layout: "post"
diff: 普及+/提高
pid: CF1060C
tag: ['枚举', '前缀和']
---

# Maximum Subrectangle

## 题目描述

You are given two arrays $ a $ and $ b $ of positive integers, with length $ n $ and $ m $ respectively.

Let $ c $ be an $ n \times m $ matrix, where $ c_{i,j} = a_i \cdot b_j $ .

You need to find a subrectangle of the matrix $ c $ such that the sum of its elements is at most $ x $ , and its area (the total number of elements) is the largest possible.

Formally, you need to find the largest number $ s $ such that it is possible to choose integers $ x_1, x_2, y_1, y_2 $ subject to $ 1 \leq x_1 \leq x_2 \leq n $ , $ 1 \leq y_1 \leq y_2 \leq m $ , $ (x_2 - x_1 + 1) \times (y_2 - y_1 + 1) = s $ , and $ $$ \sum_{i=x_1}^{x_2}{\sum_{j=y_1}^{y_2}{c_{i,j}}} \leq x. $ $$

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 2000 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 2000 $ ).

The third line contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ 1 \leq b_i \leq 2000 $ ).

The fourth line contains a single integer $ x $ ( $ 1 \leq x \leq 2 \cdot 10^{9} $ ).

## 输出格式

If it is possible to choose four integers $ x_1, x_2, y_1, y_2 $ such that $ 1 \leq x_1 \leq x_2 \leq n $ , $ 1 \leq y_1 \leq y_2 \leq m $ , and $ \sum_{i=x_1}^{x_2}{\sum_{j=y_1}^{y_2}{c_{i,j}}} \leq x $ , output the largest value of $ (x_2 - x_1 + 1) \times (y_2 - y_1 + 1) $ among all such quadruplets, otherwise output $ 0 $ .

## 说明/提示

Matrix from the first sample and the chosen subrectangle (of blue color):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1060C/ea340f2e4123e359048067db39cb97e3a56962fb.png)Matrix from the second sample and the chosen subrectangle (of blue color):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1060C/29ed72ba75c43c8c56e95a795caca1696bad260c.png)

## 样例 #1

### 输入

```
3 3
1 2 3
1 2 3
9

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 1
5 4 2 4 5
2
5

```

### 输出

```
1

```



---

---
title: "Vasya and Robot"
layout: "post"
diff: 普及+/提高
pid: CF1073C
tag: ['二分', '枚举', '前缀和']
---

# Vasya and Robot

## 题目描述

Vasya has got a robot which is situated on an infinite Cartesian plane, initially in the cell $ (0, 0) $ . Robot can perform the following four kinds of operations:

- U — move from $ (x, y) $ to $ (x, y + 1) $ ;
- D — move from $ (x, y) $ to $ (x, y - 1) $ ;
- L — move from $ (x, y) $ to $ (x - 1, y) $ ;
- R — move from $ (x, y) $ to $ (x + 1, y) $ .

Vasya also has got a sequence of $ n $ operations. Vasya wants to modify this sequence so after performing it the robot will end up in $ (x, y) $ .

Vasya wants to change the sequence so the length of changed subsegment is minimum possible. This length can be calculated as follows: $ maxID - minID + 1 $ , where $ maxID $ is the maximum index of a changed operation, and $ minID $ is the minimum index of a changed operation. For example, if Vasya changes RRRRRRR to RLRRLRL, then the operations with indices $ 2 $ , $ 5 $ and $ 7 $ are changed, so the length of changed subsegment is $ 7 - 2 + 1 = 6 $ . Another example: if Vasya changes DDDD to DDRD, then the length of changed subsegment is $ 1 $ .

If there are no changes, then the length of changed subsegment is $ 0 $ . Changing an operation means replacing it with some operation (possibly the same); Vasya can't insert new operations into the sequence or remove them.

Help Vasya! Tell him the minimum length of subsegment that he needs to change so that the robot will go from $ (0, 0) $ to $ (x, y) $ , or tell him that it's impossible.

## 输入格式

The first line contains one integer number $ n~(1 \le n \le 2 \cdot 10^5) $ — the number of operations.

The second line contains the sequence of operations — a string of $ n $ characters. Each character is either U, D, L or R.

The third line contains two integers $ x, y~(-10^9 \le x, y \le 10^9) $ — the coordinates of the cell where the robot should end its path.

## 输出格式

Print one integer — the minimum possible length of subsegment that can be changed so the resulting sequence of operations moves the robot from $ (0, 0) $ to $ (x, y) $ . If this change is impossible, print $ -1 $ .

## 说明/提示

In the first example the sequence can be changed to LULUU. So the length of the changed subsegment is $ 3 - 1 + 1 = 3 $ .

In the second example the given sequence already leads the robot to $ (x, y) $ , so the length of the changed subsegment is $ 0 $ .

In the third example the robot can't end his path in the cell $ (x, y) $ .

## 样例 #1

### 输入

```
5
RURUU
-2 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
RULR
1 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3
UUU
100 100

```

### 输出

```
-1

```



---

---
title: "Password"
layout: "post"
diff: 普及+/提高
pid: CF126B
tag: ['字符串', '枚举', 'KMP 算法', '标签474']
---

# Password

## 题目描述

Asterix，Obelix 和他们的临时伙伴 Suffix、Prefix 已经最终找到了和谐寺。然而和谐寺大门紧闭，就连 Obelix 的运气也没好到能打开它。

不久他们发现了一个字符串 $S\ (1\leqslant\vert S\vert\leqslant1000000)$，刻在和谐寺大门下面的岩石上。Asterix 猜想那一定是打开寺庙大门的密码，于是就大声将字符串朗读了出来，然而并没有什么事发生。于是 Asterix 又猜想密码一定是字符串 $S$ 的子串 $T$。

Prefix 认为 $T$ 是 $S$ 的前缀，Suffix 认为 $T$ 是 $S$ 的后缀，Obelix 却认为 $T$ 应该是 $S$ 中的某一部分，也就是说，$T$ 既不是 $S$ 的前缀，也不是 $S$ 的后缀。

Asterix 选择子串 $T$ 来满足所有伙伴们的想法。同时，在所有可以被接受的子串变形中，Asterix 选择了最长的一个。当 Asterix 大声读出子串 $T$ 时，寺庙的大门开了。（也就是说，你需要找到既是 $S$ 的前缀又是 $S$ 的后缀同时又在 $S$ 中间出现过的最长子串）

现在给你字符串 $S$，你需要找到满足上述要求的子串 $T$。

## 输入格式

一行一个只包含小写字母的字符串 $S$。

## 输出格式

输出子串 $T$，如果 $T$ 不存在，输出 `Just a legend`。

## 样例 #1

### 输入

```
fixprefixsuffix

```

### 输出

```
fix
```

## 样例 #2

### 输入

```
abcdabc

```

### 输出

```
Just a legend
```



---

---
title: "Help Farmer"
layout: "post"
diff: 普及+/提高
pid: CF142A
tag: ['枚举']
---

# Help Farmer

## 题目描述

原本有A×B×C块干草，被偷走若干块后，剩下N块，刚好等于(A−1)×(B−2)×(C−2)。现在已知N的值，不知道ABC的值，求被偷走的干草的最小值和最大值。

## 输入格式

第一行，一个整数n。

## 输出格式

第一行，两个整数，分别表示最小值和最大值。

感谢@xukuan 提供的翻译

## 样例 #1

### 输入

```
4

```

### 输出

```
28 41

```

## 样例 #2

### 输入

```
7

```

### 输出

```
47 65

```

## 样例 #3

### 输入

```
12

```

### 输出

```
48 105

```



---

---
title: "Porcelain"
layout: "post"
diff: 普及+/提高
pid: CF148E
tag: ['枚举', '背包 DP', '前缀和']
---

# Porcelain

## 题目描述

During her tantrums the princess usually smashes some collectable porcelain. Every furious shriek is accompanied with one item smashed.

The collection of porcelain is arranged neatly on $ n $ shelves. Within each shelf the items are placed in one row, so that one can access only the outermost items — the leftmost or the rightmost item, not the ones in the middle of the shelf. Once an item is taken, the next item on that side of the shelf can be accessed (see example). Once an item is taken, it can't be returned to the shelves.

You are given the values of all items. Your task is to find the maximal damage the princess' tantrum of $ m $ shrieks can inflict on the collection of porcelain.

## 输入格式

The first line of input data contains two integers $ n $ ( $ 1<=n<=100 $ ) and $ m $ ( $ 1<=m<=10000 $ ). The next $ n $ lines contain the values of the items on the shelves: the first number gives the number of items on this shelf (an integer between $ 1 $ and $ 100 $ , inclusive), followed by the values of the items (integers between $ 1 $ and $ 100 $ , inclusive), in the order in which they appear on the shelf (the first number corresponds to the leftmost item, the last one — to the rightmost one). The total number of items is guaranteed to be at least $ m $ .

## 输出格式

Output the maximal total value of a tantrum of $ m $ shrieks.

## 说明/提示

In the first case there are two shelves, each with three items. To maximize the total value of the items chosen, one can take two items from the left side of the first shelf and one item from the right side of the second shelf.

In the second case there is only one shelf, so all three items are taken from it — two from the left side and one from the right side.

## 样例 #1

### 输入

```
2 3
3 3 7 2
3 4 1 5

```

### 输出

```
15

```

## 样例 #2

### 输入

```
1 3
4 4 3 1 2

```

### 输出

```
9

```



---

---
title: "Rescheduling the Exam"
layout: "post"
diff: 普及+/提高
pid: CF1650E
tag: ['枚举', '背包 DP']
---

# Rescheduling the Exam

## 题目描述

Now Dmitry has a session, and he has to pass $ n $ exams. The session starts on day $ 1 $ and lasts $ d $ days. The $ i $ th exam will take place on the day of $ a_i $ ( $ 1 \le a_i \le d $ ), all $ a_i $ — are different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/80b5043cb96246fb12fe0316b7ae224994f04da5.png)Sample, where $ n=3 $ , $ d=12 $ , $ a=[3,5,9] $ . Orange — exam days. Before the first exam Dmitry will rest $ 2 $ days, before the second he will rest $ 1 $ day and before the third he will rest $ 3 $ days.For the session schedule, Dmitry considers a special value $ \mu $ — the smallest of the rest times before the exam for all exams. For example, for the image above, $ \mu=1 $ . In other words, for the schedule, he counts exactly $ n $ numbers — how many days he rests between the exam $ i-1 $ and $ i $ (for $ i=0 $ between the start of the session and the exam $ i $ ). Then it finds $ \mu $ — the minimum among these $ n $ numbers.

Dmitry believes that he can improve the schedule of the session. He may ask to change the date of one exam (change one arbitrary value of $ a_i $ ). Help him change the date so that all $ a_i $ remain different, and the value of $ \mu $ is as large as possible.

For example, for the schedule above, it is most advantageous for Dmitry to move the second exam to the very end of the session. The new schedule will take the form:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/ea72ffbaa1a469cfa577e07f4a541e64f273ed21.png)Now the rest periods before exams are equal to $ [2,2,5] $ . So, $ \mu=2 $ .Dmitry can leave the proposed schedule unchanged (if there is no way to move one exam so that it will lead to an improvement in the situation).

## 输入格式

The first line of input data contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of input test cases. The descriptions of test cases follow.

An empty line is written in the test before each case.

The first line of each test case contains two integers $ n $ and $ d $ ( $ 2 \le n \le 2 \cdot 10^5, 1 \le d \le 10^9 $ ) — the number of exams and the length of the session, respectively.

The second line of each test case contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le d, a_i < a_{i+1} $ ), where the $ i $ -th number means the date of the $ i $ -th exam.

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum possible value of $ \mu $ if Dmitry can move any one exam to an arbitrary day. All values of $ a_i $ should remain distinct.

## 说明/提示

The first sample is parsed in statement.

One of the optimal schedule changes for the second sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/a8127e465b7998df08b0c9dd6be925e73333852b.png)Initial schedule.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/c109ce56a74359821f30b8b4de03ca418349d132.png)New schedule.

In the third sample, we need to move the exam from day $ 1 $ to any day from $ 4 $ to $ 100 $ .

In the fourth sample, any change in the schedule will only reduce $ \mu $ , so the schedule should be left as it is.

In the fifth sample, we need to move the exam from day $ 1 $ to any day from $ 100000000 $ to $ 300000000 $ .

One of the optimal schedule changes for the sixth sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/c42982828b6b783bfe2b7287e37a4f2be5dfff0a.png)Initial schedule.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/40bee0dd841380562f7e8f2d4a71c924f5f6fe41.png)New schedule.

In the seventh sample, every day is exam day, and it is impossible to rearrange the schedule.

## 样例 #1

### 输入

```
9

3 12
3 5 9

2 5
1 5

2 100
1 2

5 15
3 6 9 12 15

3 1000000000
1 400000000 500000000

2 10
3 4

2 2
1 2

4 15
6 11 12 13

2 20
17 20
```

### 输出

```
2
1
1
2
99999999
3
0
1
9
```



---

---
title: "Progressions Covering"
layout: "post"
diff: 普及+/提高
pid: CF1661D
tag: ['贪心', '枚举']
---

# Progressions Covering

## 题目描述

You are given two arrays: an array $ a $ consisting of $ n $ zeros and an array $ b $ consisting of $ n $ integers.

You can apply the following operation to the array $ a $ an arbitrary number of times: choose some subsegment of $ a $ of length $ k $ and add the arithmetic progression $ 1, 2, \ldots, k $ to this subsegment — i. e. add $ 1 $ to the first element of the subsegment, $ 2 $ to the second element, and so on. The chosen subsegment should be inside the borders of the array $ a $ (i.e., if the left border of the chosen subsegment is $ l $ , then the condition $ 1 \le l \le l + k - 1 \le n $ should be satisfied). Note that the progression added is always $ 1, 2, \ldots, k $ but not the $ k, k - 1, \ldots, 1 $ or anything else (i.e., the leftmost element of the subsegment always increases by $ 1 $ , the second element always increases by $ 2 $ and so on).

Your task is to find the minimum possible number of operations required to satisfy the condition $ a_i \ge b_i $ for each $ i $ from $ 1 $ to $ n $ . Note that the condition $ a_i \ge b_i $ should be satisfied for all elements at once.

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 3 \cdot 10^5 $ ) — the number of elements in both arrays and the length of the subsegment, respectively.

The second line of the input contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le 10^{12} $ ), where $ b_i $ is the $ i $ -th element of the array $ b $ .

## 输出格式

Print one integer — the minimum possible number of operations required to satisfy the condition $ a_i \ge b_i $ for each $ i $ from $ 1 $ to $ n $ .

## 说明/提示

Consider the first example. In this test, we don't really have any choice, so we need to add at least five progressions to make the first element equals $ 5 $ . The array $ a $ becomes $ [5, 10, 15] $ .

Consider the second example. In this test, let's add one progression on the segment $ [1; 3] $ and two progressions on the segment $ [4; 6] $ . Then, the array $ a $ becomes $ [1, 2, 3, 2, 4, 6] $ .

## 样例 #1

### 输入

```
3 3
5 4 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
6 3
1 2 3 2 2 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
6 3
1 2 4 1 2 3
```

### 输出

```
3
```

## 样例 #4

### 输入

```
7 3
50 17 81 25 42 39 96
```

### 输出

```
92
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
title: "Flag 2"
layout: "post"
diff: 普及+/提高
pid: CF18E
tag: ['动态规划 DP', '枚举']
---

# Flag 2

## 题目描述

According to a new ISO standard, a flag of every country should have, strangely enough, a chequered field $ n×m $ , each square should be wholly painted one of 26 colours. The following restrictions are set:

- In each row at most two different colours can be used.
- No two adjacent squares can be painted the same colour.

Pay attention, please, that in one column more than two different colours can be used.

Berland's government took a decision to introduce changes into their country's flag in accordance with the new standard, at the same time they want these changes to be minimal. By the given description of Berland's flag you should find out the minimum amount of squares that need to be painted different colour to make the flag meet the new ISO standard. You are as well to build one of the possible variants of the new Berland's flag.

## 输入格式

The first input line contains 2 integers $ n $ and $ m $ ( $ 1<=n,m<=500 $ ) — amount of rows and columns in Berland's flag respectively. Then there follows the flag's description: each of the following $ n $ lines contains $ m $ characters. Each character is a letter from a to z, and it stands for the colour of the corresponding square.

## 输出格式

In the first line output the minimum amount of squares that need to be repainted to make the flag meet the new ISO standard. The following $ n $ lines should contain one of the possible variants of the new flag. Don't forget that the variant of the flag, proposed by you, should be derived from the old flag with the minimum amount of repainted squares. If the answer isn't unique, output any.

## 样例 #1

### 输入

```
3 4
aaaa
bbbb
cccc

```

### 输出

```
6
abab
baba
acac

```

## 样例 #2

### 输入

```
3 3
aba
aba
zzz

```

### 输出

```
4
aba
bab
zbz

```



---

---
title: "Mathematical Problem"
layout: "post"
diff: 普及+/提高
pid: CF1916D
tag: ['枚举']
---

# Mathematical Problem

## 题目描述

The mathematicians of the 31st lyceum were given the following task:

You are given an odd number $ n $ , and you need to find $ n $ different numbers that are squares of integers. But it's not that simple. Each number should have a length of $ n $ (and should not have leading zeros), and the multiset of digits of all the numbers should be the same. For example, for $ \mathtt{234} $ and $ \mathtt{432} $ , and $ \mathtt{11223} $ and $ \mathtt{32211} $ , the multisets of digits are the same, but for $ \mathtt{123} $ and $ \mathtt{112233} $ , they are not.

The mathematicians couldn't solve this problem. Can you?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

The following $ t $ lines contain one odd integer $ n $ ( $ 1 \leq n \leq 99 $ ) — the number of numbers to be found and their length.

It is guaranteed that the solution exists within the given constraints.

It is guaranteed that the sum of $ n^2 $ does not exceed $ 10^5 $ .

The numbers can be output in any order.

## 输出格式

For each test case, you need to output $ n $ numbers of length $ n $ — the answer to the problem.

If there are several answers, print any of them.

## 说明/提示

Below are the squares of the numbers that are the answers for the second test case:

 $ \mathtt{169} $ = $ \mathtt{13}^2 $

 $ \mathtt{196} $ = $ \mathtt{14}^2 $

 $ \mathtt{961} $ = $ \mathtt{31}^2 $

Below are the squares of the numbers that are the answers for the third test case:

 $ \mathtt{16384} $ = $ \mathtt{128}^2 $

 $ \mathtt{31684} $ = $ \mathtt{178}^2 $

 $ \mathtt{36481} $ = $ \mathtt{191}^2 $

 $ \mathtt{38416} $ = $ \mathtt{196}^2 $

 $ \mathtt{43681} $ = $ \mathtt{209}^2 $

## 样例 #1

### 输入

```
3
1
3
5
```

### 输出

```
1
169
196
961
16384
31684
36481
38416
43681
```



---

---
title: "Mischievous Shooter"
layout: "post"
diff: 普及+/提高
pid: CF1921G
tag: ['枚举', '前缀和', '差分']
---

# Mischievous Shooter

## 题目描述

Once the mischievous and wayward shooter named Shel found himself on a rectangular field of size $ n \times m $ , divided into unit squares. Each cell either contains a target or not.

Shel only had a lucky shotgun with him, with which he can shoot in one of the four directions: right-down, left-down, left-up, or right-up. When fired, the shotgun hits all targets in the chosen direction, the Manhattan distance to which does not exceed a fixed constant $ k $ . The Manhattan distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is equal to $ |x_1 - x_2| + |y_1 - y_2| $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/07ae9ceed185244b94a445086f5cae84fbf84168.png) Possible hit areas for $ k = 3 $ .Shel's goal is to hit as many targets as possible. Please help him find this value.

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains field dimensions $ n $ , $ m $ , and the constant for the shotgun's power $ k $ ( $ 1 \le n, m, k \le 10^5, 1 \le n \cdot m \le 10^5 $ ).

Each of the next $ n $ lines contains $ m $ characters — the description of the next field row, where the character '.' means the cell is empty, and the character '\#' indicates the presence of a target.

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer on a separate line, which is equal to the maximum possible number of hit targets with one shot.

## 说明/提示

Possible optimal shots for the examples in the statement:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/027b9a5a762b96357d7642f8eac1d4cf8d7ae93a.png)

## 样例 #1

### 输入

```
4
3 3 1
.#.
###
.#.
2 5 3
###..
...##
4 4 2
..##
###.
#..#
####
2 1 3
#
#
```

### 输出

```
3
4
5
2
```



---

---
title: "Tandem Repeats?"
layout: "post"
diff: 普及+/提高
pid: CF1948D
tag: ['动态规划 DP', '枚举']
---

# Tandem Repeats?

## 题目描述

给定一个由**小写字母**和**问号** `?` 组成的字符串 $s$，你可以将问号 `?` 替换为任何小写字母。

替换后，你需要找到 $s$ 中最长的**重复**子串。

一个长度为 $2n$ 的字符串 $t$ 是**重复**串，当且仅当对于所有 $1 \leq i \leq n$，有 $t_i = t_{i+n}$。

## 输入格式

**本题目含多组数据。**

第一行，一个正整数 $t$，表示数据组数。

接下来每组数据仅包含一行，一个字符串 $s$。

## 输出格式

对于每组数据，输出一行一个非负整数，表示你得到的最长重复子串的长度。

如果这样的子串不存在，输出 `0`。

## 说明/提示

对于 $100 \%$ 的数据，保证 $1 \leq t \leq 10^3, 1 \leq |s| \leq 5 \times 10^3$​。

保证 $\sum |s| \leq 5 \times 10^3$。

Translated by ShiRoZeTsu.

## 样例 #1

### 输入

```
4
zaabaabz
?????
code?????s
codeforces
```

### 输出

```
6
4
10
0
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
title: "Fragile Bridges"
layout: "post"
diff: 普及+/提高
pid: CF201C
tag: ['动态规划 DP', '枚举', '前缀和']
---

# Fragile Bridges

## 题目描述

You are playing a video game and you have just reached the bonus level, where the only possible goal is to score as many points as possible. Being a perfectionist, you've decided that you won't leave this level until you've gained the maximum possible number of points there.

The bonus level consists of $ n $ small platforms placed in a line and numbered from $ 1 $ to $ n $ from left to right and ( $ n-1 $ ) bridges connecting adjacent platforms. The bridges between the platforms are very fragile, and for each bridge the number of times one can pass this bridge from one of its ends to the other before it collapses forever is known in advance.

The player's actions are as follows. First, he selects one of the platforms to be the starting position for his hero. After that the player can freely move the hero across the platforms moving by the undestroyed bridges. As soon as the hero finds himself on a platform with no undestroyed bridge attached to it, the level is automatically ended. The number of points scored by the player at the end of the level is calculated as the number of transitions made by the hero between the platforms. Note that if the hero started moving by a certain bridge, he has to continue moving in the same direction until he is on a platform.

Find how many points you need to score to be sure that nobody will beat your record, and move to the next level with a quiet heart.

## 输入格式

The first line contains a single integer $ n $ ( $ 2<=n<=10^{5} $ ) — the number of platforms on the bonus level. The second line contains ( $ n-1 $ ) integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ , $ 1<=i&lt;n $ ) — the number of transitions from one end to the other that the bridge between platforms $ i $ and $ i+1 $ can bear.

## 输出格式

Print a single integer — the maximum number of points a player can get on the bonus level.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

One possibility of getting $ 5 $ points in the sample is starting from platform $ 3 $ and consequently moving to platforms $ 4 $ , $ 3 $ , $ 2 $ , $ 1 $ and $ 2 $ . After that the only undestroyed bridge is the bridge between platforms $ 4 $ and $ 5 $ , but this bridge is too far from platform $ 2 $ where the hero is located now.

## 样例 #1

### 输入

```
5
2 1 2 1

```

### 输出

```
5

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
title: "Hackers and Neural Networks"
layout: "post"
diff: 普及+/提高
pid: CF2093F
tag: ['字符串', '贪心', '枚举']
---

# Hackers and Neural Networks

## 题目描述

黑客们再次尝试利用神经网络的输出来创造有趣的短语。这次，他们希望获得一个长度为 $n$ 的字符串数组 $a$。

最初，他们有一个长度为 $n$ 的数组 $c$，其中所有位置都是空白，用符号 $*$ 表示。例如，如果 $n=4$，那么初始时 $c=[*,*,*,*]$。

黑客们可以访问 $m$ 个神经网络，每个神经网络都有自己对请求的答案版本——一个长度为 $n$ 的字符串数组 $b_i$。

黑客们试图通过以下操作从数组 $c$ 得到数组 $a$：

1. 选择一个神经网络 $i$，它将执行对数组 $c$ 的下一个操作：随机选择一个空白位置（例如位置 $j$），并将 $c_j$ 替换为 $b_{i, j}$。例如，如果选择第一个神经网络且 $c = [*, \text{«like»}, *]$，而 $b_1 = [\text{«I»}, \text{«love»}, \text{«apples»}]$，那么经过第一个神经网络的操作后，$c$ 可能变为 $[\text{«I»}, \text{«like»}, *]$ 或 $[*, \text{«like»}, \text{«apples»}]$。
2. 选择一个位置 $j$，并将 $c_j$ 替换为空白。

不幸的是，由于黑客访问神经网络的方式，他们只能在所有操作完成后看到修改后的数组 $c$，因此他们必须提前指定完整的操作序列。

然而，神经网络的随机行为可能导致无法获得目标数组 $a$，或者需要过多的操作才能获得它。

因此，黑客们希望你能帮助他们选择一个操作序列，确保以最少的操作次数获得数组 $a$。

更正式地说，如果存在一个操作序列可以确保从数组 $c$ 得到数组 $a$，那么在所有这样的序列中，找出操作次数最少的序列，并输出其中的操作次数。

如果不存在将数组 $c$ 转换为数组 $a$ 的操作序列，则输出 $-1$。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 1000$）——测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 500$）——原始数组 $a$ 的长度和神经网络的数量。

每个测试用例的第二行包含数组 $a$，由 $n$ 个字符串 $a_i$（$1 \le |a_i| \le 10$）组成，用空格分隔。

接下来的 $m$ 行，每行包含一个数组 $b_i$，由 $n$ 个字符串 $b_{i, j}$（$1 \le |b_{i,j}| \le 10$）组成，用空格分隔。

保证所有测试用例的 $|a_i|$ 和 $|b_{i, j}|$ 的总和不超过 $2 \cdot 10^5$，且所有测试用例的 $n \cdot m$ 总和也不超过 $2 \cdot 10^5$。

保证输入字符串仅由大小写拉丁字母组成。

注意，每个输入字符串的长度不超过 $10$。

## 输出格式

输出 $t$ 个数字——每个测试用例一个数字，每个数字单独占一行。

如果存在确保从第 $i$ 个测试用例的数组 $c$ 得到数组 $a$ 的操作序列，则第 $i$ 个数字是该序列的最小操作次数。

否则，对于第 $i$ 个数字，输出 $-1$。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3 3
I love apples
He likes apples
I love cats
They love dogs
3 2
Icy wake up
wake Icy up
wake up Icy
4 3
c o D E
c o D s
c O l S
c o m E
4 5
a s k A
d s D t
O R i A
a X b Y
b a k A
u s k J
```

### 输出

```
5
-1
6
8
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
title: "LCM Challenge"
layout: "post"
diff: 普及+/提高
pid: CF235A
tag: ['贪心', '枚举']
---

# LCM Challenge

## 题目描述

Some days ago, I learned the concept of LCM (least common multiple). I've played with it for several times and I want to make a big number with it.

But I also don't want to use many numbers, so I'll choose three positive integers (they don't have to be distinct) which are not greater than $ n $ . Can you help me to find the maximum possible least common multiple of these three integers?

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{6} $ ) — the $ n $ mentioned in the statement.

## 输出格式

Print a single integer — the maximum possible LCM of three not necessarily distinct positive integers that are not greater than $ n $ .

## 说明/提示

The least common multiple of some positive integers is the least positive integer which is multiple for each of them.

The result may become very large, 32-bit integer won't be enough. So using 64-bit integers is recommended.

For the last example, we can chose numbers $ 7 $ , $ 6 $ , $ 5 $ and the LCM of them is $ 7·6·5=210 $ . It is the maximum value we can get.

## 样例 #1

### 输入

```
9

```

### 输出

```
504

```

## 样例 #2

### 输入

```
7

```

### 输出

```
210

```



---

---
title: "Good Sequences"
layout: "post"
diff: 普及+/提高
pid: CF264B
tag: ['动态规划 DP', '枚举', '最大公约数 gcd']
---

# Good Sequences

## 题目描述

Squirrel Liss is interested in sequences. She also has preferences of integers. She thinks $ n $ integers $ a_{1},a_{2},...,a_{n} $ are good.

Now she is interested in good sequences. A sequence $ x_{1},x_{2},...,x_{k} $ is called good if it satisfies the following three conditions:

- The sequence is strictly increasing, i.e. $ x_{i}&lt;x_{i+1} $ for each $ i $ $ (1<=i<=k-1) $ .
- No two adjacent elements are coprime, i.e. $ gcd(x_{i},x_{i+1})&gt;1 $ for each $ i $ $ (1<=i<=k-1) $ (where $ gcd(p,q) $ denotes the greatest common divisor of the integers $ p $ and $ q $ ).
- All elements of the sequence are good integers.

Find the length of the longest good sequence.

## 输入格式

The input consists of two lines. The first line contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of good integers. The second line contains a single-space separated list of good integers $ a_{1},a_{2},...,a_{n} $ in strictly increasing order ( $ 1<=a_{i}<=10^{5}; a_{i}&lt;a_{i+1} $ ).

## 输出格式

Print a single integer — the length of the longest good sequence.

## 说明/提示

In the first example, the following sequences are examples of good sequences: \[2; 4; 6; 9\], \[2; 4; 6\], \[3; 9\], \[6\]. The length of the longest good sequence is 4.

## 样例 #1

### 输入

```
5
2 3 4 6 9

```

### 输出

```
4

```

## 样例 #2

### 输入

```
9
1 2 3 5 6 7 8 9 10

```

### 输出

```
4

```



---

---
title: "Greg and Graph"
layout: "post"
diff: 普及+/提高
pid: CF295B
tag: ['枚举', '最短路', '概率论']
---

# Greg and Graph

## 题目描述

Greg 有一个有边权的有向图，包含 $n$ 个点。这个图的每两个点之间都有两个方向的边。Greg 喜欢用他的图玩游戏，现在他发明了一种新游戏：

- 游戏包含 $n$ 步。
- 第 $i$ 步 Greg 从图中删掉编号为 $x_i$ 的点。当删除一个点时，这个点的出边和入边都会被删除。
- 在执行每一步之前，Greg 想知道所有点对间最短路长度的和。最短路可以经过任何没删掉的点。换句话说，如果我们假设 $d(i, v, u)$ 是在删掉 $x_i$ 前 $v$ 和 $u$ 间的最短路长度，那么Greg想知道下面这个求和的值：$\sum_{v, u, v \neq u} d(i, v, u)$ 。

帮帮 Greg，输出每一步之前要求的值。

## 输入格式

第一行包含一个整数 $n \ (1 \leq n \leq 500)$ ，代表图中的点数。

下面 $n$ 行每行包含 $n$ 个整数，代表边权：第 $i$ 行的第 $j$ 个数 $a_{ij} \ (1 \leq a_{ij} \leq 10^5, a_{ii} = 0)$ 代表从 $i$ 到 $j$ 的边权。

最后一行包含 $n$ 个整数：$x_1, x_2, \dots, x_n \ (1 \leq x_i \leq n)$ ，分别为Greg每一步删掉的点的编号。

## 输出格式

输出 $n$ 个整数，第 $i$ 个数等于游戏的第 $i$ 步之前统计的求和值。

请不要在 C++ 中使用 `%lld` 标志来输出 64 位整数 `long long`，推荐使用 `cin, cout` 流或者用 `%I64d` 标志。

Translated by @KSkun

## 样例 #1

### 输入

```
1
0
1

```

### 输出

```
0 
```

## 样例 #2

### 输入

```
2
0 5
4 0
1 2

```

### 输出

```
9 0 
```

## 样例 #3

### 输入

```
4
0 3 1 1
6 0 400 1
2 4 0 1
1 1 1 0
4 1 2 3

```

### 输出

```
17 23 404 0 
```



---

---
title: "Greg and Friends"
layout: "post"
diff: 普及+/提高
pid: CF295C
tag: ['模拟', '动态规划 DP', '枚举']
---

# Greg and Friends

## 题目描述

One day Greg and his friends were walking in the forest. Overall there were $ n $ people walking, including Greg. Soon he found himself in front of a river. The guys immediately decided to get across the river. Luckily, there was a boat by the river bank, just where the guys were standing. We know that the boat can hold people with the total weight of at most $ k $ kilograms.

Greg immediately took a piece of paper and listed there the weights of all people in his group (including himself). It turned out that each person weights either 50 or 100 kilograms. Now Greg wants to know what minimum number of times the boat needs to cross the river to transport the whole group to the other bank. The boat needs at least one person to navigate it from one bank to the other. As the boat crosses the river, it can have any non-zero number of passengers as long as their total weight doesn't exceed $ k $ .

Also Greg is wondering, how many ways there are to transport everybody to the other side in the minimum number of boat rides. Two ways are considered distinct if during some ride they have distinct sets of people on the boat.

Help Greg with this problem.

## 输入格式

The first line contains two integers $ n $ , $ k $ $ (1<=n<=50,1<=k<=5000) $ — the number of people, including Greg, and the boat's weight limit. The next line contains $ n $ integers — the people's weights. A person's weight is either $ 50 $ kilos or $ 100 $ kilos.

You can consider Greg and his friends indexed in some way.

## 输出格式

In the first line print an integer — the minimum number of rides. If transporting everyone to the other bank is impossible, print an integer -1.

In the second line print the remainder after dividing the number of ways to transport the people in the minimum number of rides by number $ 1000000007 $ $ (10^{9}+7) $ . If transporting everyone to the other bank is impossible, print integer $ 0 $ .

## 说明/提示

In the first test Greg walks alone and consequently, he needs only one ride across the river.

In the second test you should follow the plan:

1. transport two $ 50 $ kg. people;
2. transport one $ 50 $ kg. person back;
3. transport one $ 100 $ kg. person;
4. transport one $ 50 $ kg. person back;
5. transport two $ 50 $ kg. people.

That totals to $ 5 $ rides. Depending on which person to choose at step 2, we can get two distinct ways.

## 样例 #1

### 输入

```
1 50
50

```

### 输出

```
1
1

```

## 样例 #2

### 输入

```
3 100
50 50 100

```

### 输出

```
5
2

```

## 样例 #3

### 输入

```
2 50
50 50

```

### 输出

```
-1
0

```



---

---
title: "Vasily the Bear and Sequence"
layout: "post"
diff: 普及+/提高
pid: CF336C
tag: ['贪心', '枚举', '进制']
---

# Vasily the Bear and Sequence

## 题目描述

Vasily the bear has got a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Vasily the Bear wants to write out several numbers on a piece of paper so that the beauty of the numbers he wrote out was maximum.

The beauty of the written out numbers $ b_{1},b_{2},...,b_{k} $ is such maximum non-negative integer $ v $ , that number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by number $ 2^{v} $ without a remainder. If such number $ v $ doesn't exist (that is, for any non-negative integer $ v $ , number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by $ 2^{v} $ without a remainder), the beauty of the written out numbers equals -1.

Tell the bear which numbers he should write out so that the beauty of the written out numbers is maximum. If there are multiple ways to write out the numbers, you need to choose the one where the bear writes out as many numbers as possible.

Here expression $ x $ $ and $ $ y $ means applying the bitwise AND operation to numbers $ x $ and $ y $ . In programming languages C++ and Java this operation is represented by "&", in Pascal — by "and".

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ). The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{1}&lt;a_{2}&lt;...&lt;a_{n}<=10^{9}) $ .

## 输出格式

In the first line print a single integer $ k $ $ (k&gt;0) $ , showing how many numbers to write out. In the second line print $ k $ integers $ b_{1},b_{2},...,b_{k} $ — the numbers to write out. You are allowed to print numbers $ b_{1},b_{2},...,b_{k} $ in any order, but all of them must be distinct. If there are multiple ways to write out the numbers, choose the one with the maximum number of numbers to write out. If there still are multiple ways, you are allowed to print any of them.

## 样例 #1

### 输入

```
5
1 2 3 4 5

```

### 输出

```
2
4 5

```

## 样例 #2

### 输入

```
3
1 2 4

```

### 输出

```
1
4

```



---

---
title: "Knights"
layout: "post"
diff: 普及+/提高
pid: CF33D
tag: ['枚举', '最近公共祖先 LCA']
---

# Knights

## 题目描述

伯兰国不得不又一次面对黑♂暗势力的降临。邪恶领主~~Van♂De♂Mart~~范·德·马特正在计划征服整个王国。王国成立了由伯兰国王瓦莱丽领导的理事会。理事会由$n$个骑士组成。经过一番激烈的讨论，他们把整个国家分成了$n$个战略目标点，（如果黑暗势力控制了至少一个战略目标点，战争就失败了）

伯兰国可以被认为是由$m+1$个区域和$m$个栅栏组成的。同时，从一个区域到达另一个区域的唯一方法就是翻过栅栏。每个栅栏都是同一个平面上的圆，并且任意两个栅栏之间都没有交叉点，同时保证所有战略目标点都`不在`栅栏上。我们会给你$k$对整数$ai, bi$，对于每对整数，你都要解决：如果一个骑士想从战略控制点$ai$赶到$bi$，（为了防止范·德·马特突袭控制点bi），而每个骑士都骑着一匹马（把马从栅栏上扔过去太难了），那么，他最少爬过多少栅栏？

## 输入格式

第一行是两个正整数$n,m$（$1 ≤ n,m ≤ 1000$， $0 ≤ k ≤ 10000$）接下来$n$行， 两个数，$Kx_i, Ky_i$，（$-1 * 10^9 ≤ Kx_i, Ky_i ≤ 1 * 10^9$）描述第$i$个控制点的坐标。

接下来$m$行，每行描述一个栅栏，一个栅栏有三个参数，$r_i, Cx_i, Cy_i$分别表示这个栅栏的直径和坐标。（$-1 * 10^9 ≤ Cx_i, Cy_i ≤ 1 * 10^9$， $1 ≤ r_i ≤ 1 * 10^9$）

在接下来$k$行，每行两个整数，第$n+m+j$行表示$a_i$，$b_i$，（意义前面已经说了）

## 输出格式

正好k行，每行一个整数，对这$k$次询问的答案

_翻译 By 的卢_

## 样例 #1

### 输入

```
2 1 1
0 0
3 3
2 0 0
1 2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2 3 1
0 0
4 4
1 0 0
2 0 0
3 0 0
1 2

```

### 输出

```
3

```



---

---
title: "Knight Tournament"
layout: "post"
diff: 普及+/提高
pid: CF356A
tag: ['搜索', '并查集', '枚举']
---

# Knight Tournament

## 题目描述

（题目大意）：有n个骑士，他们每个人都被从1-n进行编号，他们现在需要进行一次比赛，且总共会进行m场比赛。每场比赛会在编号在Li-Ri这段区间内的骑士之间举行，对于每场比赛，它的胜利者的编号为Xi，其他的骑士会出局，之后无法进行比赛。最后留下的骑士就是这次比赛的最终胜利者。比赛结束后，每个骑士都想知道他被哪一个骑士击败了，请你告诉他们。

## 输入格式

第一行为两个整数n，m。代表有n个骑士参加m场比赛；

之后的m行，每行3个整数Li，Ri，Xi，代表第i场比赛在编号在Li-Ri之间的骑士举行，胜利者的编号为Xi。

保证输入数据正确，保证至少有两名骑士参加每一场战斗；

## 输出格式

输出只有一行，包括n个整数，第i个数代表第i个骑士被编号为第i个数的骑士打败，特别的，如果第i个骑士是最后的胜者，输出0；

## 样例 #1

### 输入

```
4 3
1 2 1
1 3 3
1 4 4

```

### 输出

```
3 1 4 0 
```

## 样例 #2

### 输入

```
8 4
3 5 4
3 7 6
2 8 8
1 8 1

```

### 输出

```
0 8 4 6 4 8 6 1 
```



---

---
title: "Diverse Substrings"
layout: "post"
diff: 普及+/提高
pid: CF386C
tag: ['枚举', '双指针 two-pointer']
---

# Diverse Substrings

## 题目描述

给定一个字符串 $s$，定义 $d(x)$ 为字符串 $x$ 内不同的字符个数。

求有多少个 $s$ 的子串 $s1$，使得 $d(s1)$ 为给定的 $t_{i}$。

## 输入格式

第一行包含一个字符串 $s$。

## 输出格式

第一行输出 $d(s)$。

然后输出 $t_1,t_2,\cdots,t_{d(s)}$ 对应的子串数量。

$1 \le |s| \le 3 \times 10^5$。

## 样例 #1

### 输入

```
abca

```

### 输出

```
3
4
3
3

```

## 样例 #2

### 输入

```
aabacaabbad

```

### 输出

```
4
14
19
28
5

```



---

---
title: "Little Victor and Set"
layout: "post"
diff: 普及+/提高
pid: CF460D
tag: ['贪心', '枚举', '构造']
---

# Little Victor and Set

## 题目描述

Little Victor adores the sets theory. Let us remind you that a set is a group of numbers where all numbers are pairwise distinct. Today Victor wants to find a set of integers $ S $ that has the following properties:

- for all $ x $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/26c8948a606517ebae5f50ff9b8fc7d91f76f3df.png) the following inequality holds $ l<=x<=r $ ;
- $ 1<=|S|<=k $ ;
- lets denote the $ i $ -th element of the set $ S $ as $ s_{i} $ ; value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/7523823a9f324064de1df35c0e0503740f7be786.png) must be as small as possible.

Help Victor find the described set.

## 输入格式

The first line contains three space-separated integers $ l,r,k $ $ (1<=l<=r<=10^{12}; 1<=k<=min(10^{6},r-l+1)) $ .

## 输出格式

Print the minimum possible value of $ f(S) $ . Then print the cardinality of set $ |S| $ . Then print the elements of the set in any order.

If there are multiple optimal sets, you can print any of them.

## 说明/提示

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) represents the operation of bitwise exclusive OR. In other words, it is the XOR operation.

## 样例 #1

### 输入

```
8 15 3

```

### 输出

```
1
2
10 11

```

## 样例 #2

### 输入

```
8 30 7

```

### 输出

```
0
5
14 9 28 11 16

```



---

---
title: "Mr. Kitayuta, the Treasure Hunter"
layout: "post"
diff: 普及+/提高
pid: CF505C
tag: ['动态规划 DP', '枚举']
---

# Mr. Kitayuta, the Treasure Hunter

## 题目描述

The Shuseki Islands are an archipelago of $ 30001 $ small islands in the Yutampo Sea. The islands are evenly spaced along a line, numbered from $ 0 $ to $ 30000 $ from the west to the east. These islands are known to contain many treasures. There are $ n $ gems in the Shuseki Islands in total, and the $ i $ -th gem is located on island $ p_{i} $ .

Mr. Kitayuta has just arrived at island $ 0 $ . With his great jumping ability, he will repeatedly perform jumps between islands to the east according to the following process:

- First, he will jump from island $ 0 $ to island $ d $ .
- After that, he will continue jumping according to the following rule. Let $ l $ be the length of the previous jump, that is, if his previous jump was from island $ prev $ to island $ cur $ , let $ l=cur-prev $ . He will perform a jump of length $ l-1 $ , $ l $ or $ l+1 $ to the east. That is, he will jump to island $ (cur+l-1) $ , $ (cur+l) $ or $ (cur+l+1) $ (if they exist). The length of a jump must be positive, that is, he cannot perform a jump of length $ 0 $ when $ l=1 $ . If there is no valid destination, he will stop jumping.

Mr. Kitayuta will collect the gems on the islands visited during the process. Find the maximum number of gems that he can collect.

## 输入格式

The first line of the input contains two space-separated integers $ n $ and $ d $ ( $ 1<=n,d<=30000 $ ), denoting the number of the gems in the Shuseki Islands and the length of the Mr. Kitayuta's first jump, respectively.

The next $ n $ lines describe the location of the gems. The $ i $ -th of them ( $ 1<=i<=n $ ) contains a integer $ p_{i} $ ( $ d<=p_{1}<=p_{2}<=...<=p_{n}<=30000 $ ), denoting the number of the island that contains the $ i $ -th gem.

## 输出格式

Print the maximum number of gems that Mr. Kitayuta can collect.

## 说明/提示

In the first sample, the optimal route is 0 $ → $ 10 (+1 gem) $ → $ 19 $ → $ 27 (+2 gems) $ →...&#x1; $

In the second sample, the optimal route is 0 $ → $ 8 $ → $ 15 $ → $ 21 $ → $ 28 (+1 gem) $ → $ 36 (+1 gem) $ → $ 45 (+1 gem) $ → $ 55 (+1 gem) $ → $ 66 (+1 gem) $ → $ 78 (+1 gem) $ →... $

In the third sample, the optimal route is 0 $ → $ 7 $ → $ 13 $ → $ 18 (+1 gem) $ → $ 24 (+2 gems) $ → $ 30 (+1 gem) $ →... $

## 样例 #1

### 输入

```
4 10
10
21
27
27

```

### 输出

```
3

```

## 样例 #2

### 输入

```
8 8
9
19
28
36
45
55
66
78

```

### 输出

```
6

```

## 样例 #3

### 输入

```
13 7
8
8
9
16
17
17
18
21
23
24
24
26
30

```

### 输出

```
4

```



---

---
title: "Fox And Jumping"
layout: "post"
diff: 普及+/提高
pid: CF510D
tag: ['动态规划 DP', '枚举', '背包 DP', '最大公约数 gcd']
---

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=300 $ ), number of cards.

The second line contains $ n $ numbers $ l_{i} $ ( $ 1<=l_{i}<=10^{9} $ ), the jump lengths of cards.

The third line contains $ n $ numbers $ c_{i} $ ( $ 1<=c_{i}<=10^{5} $ ), the costs of cards.

## 输出格式

If it is impossible to buy some cards and become able to jump to any cell, output -1. Otherwise output the minimal cost of buying such set of cards.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10

```

### 输出

```
6

```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026

```

### 输出

```
7237

```



---

---
title: "Group Photo 2 (online mirror version)"
layout: "post"
diff: 普及+/提高
pid: CF529B
tag: ['贪心', '枚举', '排序']
---

# Group Photo 2 (online mirror version)

## 题目描述

Many years have passed, and $ n $ friends met at a party again. Technologies have leaped forward since the last meeting, cameras with timer appeared and now it is not obligatory for one of the friends to stand with a camera, and, thus, being absent on the photo.

Simply speaking, the process of photographing can be described as follows. Each friend occupies a rectangle of pixels on the photo: the $ i $ -th of them in a standing state occupies a $ w_{i} $ pixels wide and a $ h_{i} $ pixels high rectangle. But also, each person can lie down for the photo, and then he will occupy a $ h_{i} $ pixels wide and a $ w_{i} $ pixels high rectangle.

The total photo will have size $ W×H $ , where $ W $ is the total width of all the people rectangles, and $ H $ is the maximum of the heights. The friends want to determine what minimum area the group photo can they obtain if no more than $ n/2 $ of them can lie on the ground (it would be strange if more than $ n/2 $ gentlemen lie on the ground together, isn't it?..)

Help them to achieve this goal.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=1000 $ ) — the number of friends.

The next $ n $ lines have two integers $ w_{i},h_{i} $ ( $ 1<=w_{i},h_{i}<=1000 $ ) each, representing the size of the rectangle, corresponding to the $ i $ -th friend.

## 输出格式

Print a single integer equal to the minimum possible area of the photo containing all friends if no more than $ n/2 $ of them can lie on the ground.

## 样例 #1

### 输入

```
3
10 1
20 2
30 3

```

### 输出

```
180

```

## 样例 #2

### 输入

```
3
3 1
2 2
4 3

```

### 输出

```
21

```

## 样例 #3

### 输入

```
1
5 10

```

### 输出

```
50

```



---

---
title: "Amr and Chemistry"
layout: "post"
diff: 普及+/提高
pid: CF558C
tag: ['动态规划 DP', '贪心', '枚举', '进制', '字典树 Trie']
---

# Amr and Chemistry

## 题目描述

Amr loves Chemistry, and specially doing experiments. He is preparing for a new interesting experiment.

Amr has $ n $ different types of chemicals. Each chemical $ i $ has an initial volume of $ a_{i} $ liters. For this experiment, Amr has to mix all the chemicals together, but all the chemicals volumes must be equal first. So his task is to make all the chemicals volumes equal.

To do this, Amr can do two different kind of operations.

- Choose some chemical $ i $ and double its current volume so the new volume will be $ 2a_{i} $
- Choose some chemical $ i $ and divide its volume by two (integer division) so the new volume will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558C/2af906789c62f9845274f856d2f941f2357aa169.png)

Suppose that each chemical is contained in a vessel of infinite volume. Now Amr wonders what is the minimum number of operations required to make all the chemicals volumes equal?

## 输入格式

The first line contains one number $ n $ ( $ 1<=n<=10^{5} $ ), the number of chemicals.

The second line contains $ n $ space separated integers $ a_{i} $ ( $ 1<=a_{i}<=10^{5} $ ), representing the initial volume of the $ i $ -th chemical in liters.

## 输出格式

Output one integer the minimum number of operations required to make all the chemicals volumes equal.

## 说明/提示

In the first sample test, the optimal solution is to divide the second chemical volume by two, and multiply the third chemical volume by two to make all the volumes equal $ 4 $ .

In the second sample test, the optimal solution is to divide the first chemical volume by two, and divide the second and the third chemical volumes by two twice to make all the volumes equal $ 1 $ .

## 样例 #1

### 输入

```
3
4 8 2

```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
3 5 6

```

### 输出

```
5
```



---

---
title: "Kefa and Dishes"
layout: "post"
diff: 普及+/提高
pid: CF580D
tag: ['动态规划 DP', '枚举', '状态合并']
---

# Kefa and Dishes

## 题目描述

$\texttt{songshe}$ 进入了一家餐厅，这家餐厅中有 $n\ (1\leqslant n\leqslant18)$ 个菜。$\texttt{songshe}$ 对第 $i$ 个菜的满意度为 $a_i\ (0\leqslant a_i\leqslant10^9)$。

对于这 $n$ 个菜，有 $k\ (0\leqslant k\leqslant n^2-n)$ 条规则：如果 $\texttt{songshe}$ 在吃完第 $x_i$ 个菜之后立刻吃了第 $y_i\ (x_i\neq y_i)$ 个菜，那么会额外获得 $c_i\ (0\leqslant c_i\leqslant10^9)$ 的满意度。

$\texttt{songshe}$ 要吃 $m\ (1\leqslant m\leqslant n)$ 道任意的菜，但是他希望自己吃菜的顺序得到的满意度最大，请你帮 $\texttt{songshe}$ 解决这个问题。

## 输入格式

第 $1$ 行包含三个整数 $n,m,k$。

第 $2$ 行 $n$ 个非负整数，第 $i$ 个数表示 $\texttt{songshe}$ 对第 $i$ 道菜的满意度为 $a_i$。

若 $k\neq0$，第 $3$ 行到第 $k+2$ 行每行 $3$ 个整数 $x_i,y_i,c_i$，含义见上文。

## 输出格式

一行一个整数，表示最大满意度。

## 样例 #1

### 输入

```
2 2 1
1 1
2 1 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 3 2
1 2 3 4
2 1 5
3 4 2

```

### 输出

```
12

```



---

---
title: "World Tour"
layout: "post"
diff: 普及+/提高
pid: CF666B
tag: ['枚举', '最短路']
---

# World Tour

## 题目描述

A famous sculptor Cicasso goes to a world tour!

Well, it is not actually a world-wide. But not everyone should have the opportunity to see works of sculptor, shouldn't he? Otherwise there will be no any exclusivity. So Cicasso will entirely hold the world tour in his native country — Berland.

Cicasso is very devoted to his work and he wants to be distracted as little as possible. Therefore he will visit only four cities. These cities will be different, so no one could think that he has "favourites". Of course, to save money, he will chose the shortest paths between these cities. But as you have probably guessed, Cicasso is a weird person. Although he doesn't like to organize exhibitions, he likes to travel around the country and enjoy its scenery. So he wants the total distance which he will travel to be as large as possible. However, the sculptor is bad in planning, so he asks you for help.

There are $ n $ cities and $ m $ one-way roads in Berland. You have to choose four different cities, which Cicasso will visit and also determine the order in which he will visit them. So that the total distance he will travel, if he visits cities in your order, starting from the first city in your list, and ending in the last, choosing each time the shortest route between a pair of cities — will be the largest.

Note that intermediate routes may pass through the cities, which are assigned to the tour, as well as pass twice through the same city. For example, the tour can look like that: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF666B/a1ec5df39eab48a433cbfa38b3e24c1e861f8538.png). Four cities in the order of visiting marked as overlines: $ [1,5,2,4] $ .

Note that Berland is a high-tech country. So using nanotechnologies all roads were altered so that they have the same length. For the same reason moving using regular cars is not very popular in the country, and it can happen that there are such pairs of cities, one of which generally can not be reached by car from the other one. However, Cicasso is very conservative and cannot travel without the car. Choose cities so that the sculptor can make the tour using only the automobile. It is guaranteed that it is always possible to do.

## 输入格式

In the first line there is a pair of integers $ n $ and $ m $ ( $ 4<=n<=3000,3<=m<=5000 $ ) — a number of cities and one-way roads in Berland.

Each of the next $ m $ lines contains a pair of integers $ u_{i},v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) — a one-way road from the city $ u_{i} $ to the city $ v_{i} $ . Note that $ u_{i} $ and $ v_{i} $ are not required to be distinct. Moreover, it can be several one-way roads between the same pair of cities.

## 输出格式

Print four integers — numbers of cities which Cicasso will visit according to optimal choice of the route. Numbers of cities should be printed in the order that Cicasso will visit them. If there are multiple solutions, print any of them.

## 说明/提示

Let $ d(x,y) $ be the shortest distance between cities $ x $ and $ y $ . Then in the example $ d(2,1)=3,d(1,8)=7,d(8,7)=3 $ . The total distance equals $ 13 $ .

## 样例 #1

### 输入

```
8 9
1 2
2 3
3 4
4 1
4 5
5 6
6 7
7 8
8 5

```

### 输出

```
2 1 8 7

```



---

---
title: "Petya and Post"
layout: "post"
diff: 普及+/提高
pid: CF66E
tag: ['动态规划 DP', '线段树', '枚举']
---

# Petya and Post

## 题目描述

### 题意翻译

有 $n$ 个邮局，在每个邮局都有一个加油站。（邮局编号从 $1$ 开始）

对于第 $i$ 个邮局，$a_i$ 表示位于这个邮局加油站最多能加多少油，$b_i$ 表示它到第 $i+1$ 个邮局会耗费多少油。特殊的，对于第 $n$ 个邮局，$b_n$ 表示它到第 $1$ 个邮局会耗费多少油。

现在可以任意选择一个邮局出发，开始的油量为 $0$。可以选择顺时针或者逆时针走动，一旦决定方向就不可以回头。 要求路途上任一时刻油量$\ge 0$。

## 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个正整数表示 $a$。

第三行 $n$ 个正整数表示 $b$。

## 输出格式

第一行一个正整数 $res$，表示有多少个邮局出发可以回到自己。

第二行 $res$ 个正整数，从小到大的输出这些可以回到自己的邮局的编号。

### 数据规模

$1 \le n \le 10^5$。

$\sum\limits_{i=1}^n a_i$ 不超过 $10^9$。

$\sum\limits_{i=1}^n b_i$ 不超过 $10^9$。

## 样例 #1

### 输入

```
4
1 7 2 3
8 1 1 3

```

### 输出

```
2
2 4

```

## 样例 #2

### 输入

```
8
1 2 1 2 1 2 1 2
2 1 2 1 2 1 2 1

```

### 输出

```
8
1 2 3 4 5 6 7 8

```



---

---
title: "Kay and Snowflake"
layout: "post"
diff: 普及+/提高
pid: CF685B
tag: ['枚举', '深度优先搜索 DFS', '位运算']
---

# Kay and Snowflake

## 题目描述

After the piece of a devilish mirror hit the Kay's eye, he is no longer interested in the beauty of the roses. Now he likes to watch snowflakes.

Once upon a time, he found a huge snowflake that has a form of the tree (connected acyclic graph) consisting of $ n $ nodes. The root of tree has index $ 1 $ . Kay is very interested in the structure of this tree.

After doing some research he formed $ q $ queries he is interested in. The $ i $ -th query asks to find a centroid of the subtree of the node $ v_{i} $ . Your goal is to answer all queries.

Subtree of a node is a part of tree consisting of this node and all it's descendants (direct or not). In other words, subtree of node $ v $ is formed by nodes $ u $ , such that node $ v $ is present on the path from $ u $ to root.

Centroid of a tree (or a subtree) is a node, such that if we erase it from the tree, the maximum size of the connected component will be at least two times smaller than the size of the initial tree (or a subtree).

## 输入格式

The first line of the input contains two integers $ n $ and $ q $ ( $ 2<=n<=300000 $ , $ 1<=q<=300000 $ ) — the size of the initial tree and the number of queries respectively.

The second line contains $ n-1 $ integer $ p_{2},p_{3},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — the indices of the parents of the nodes from $ 2 $ to $ n $ . Node $ 1 $ is a root of the tree. It's guaranteed that $ p_{i} $ define a correct tree.

Each of the following $ q $ lines contain a single integer $ v_{i} $ ( $ 1<=v_{i}<=n $ ) — the index of the node, that define the subtree, for which we want to find a centroid.

## 输出格式

For each query print the index of a centroid of the corresponding subtree. If there are many suitable nodes, print any of them. It's guaranteed, that each subtree has at least one centroid.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF685B/821209b858c843715556bbbb66f001612969fa03.png)The first query asks for a centroid of the whole tree — this is node $ 3 $ . If we delete node $ 3 $ the tree will split in four components, two of size $ 1 $ and two of size $ 2 $ .

The subtree of the second node consists of this node only, so the answer is $ 2 $ .

Node $ 3 $ is centroid of its own subtree.

The centroids of the subtree of the node $ 5 $ are nodes $ 5 $ and $ 6 $ — both answers are considered correct.

## 样例 #1

### 输入

```
7 4
1 1 3 3 5 3
1
2
3
5

```

### 输出

```
3
2
3
6

```



---

---
title: "Lizards and Basements 2"
layout: "post"
diff: 普及+/提高
pid: CF6D
tag: ['枚举', '深度优先搜索 DFS', '剪枝']
---

# Lizards and Basements 2

## 题目描述

有一队人，第 $i$ 个人的血量为 $h_{i}$，你可以用火球点某个人，会对当前的人造成 $a$ 点伤害，对旁边的人造成 $b$ 点伤害。

火球不能打 $1$ 号和 $n$ 号，求最少多少发火球烧死所有人。血量为负数才算死。

## 输入格式

第一行输入三个整数 $n$, $a$, $b$；

第二行输入 $n$ 个 $h_{i}$，表示每个人的血量。

## 输出格式

第一行输出 $ t $，表示需要使用的火球总数。

第二行输出 $ t $ 个数，分别表示第 $i$ 个火球打在了哪个人身上。

## 样例 #1

### 输入

```
3 2 1
2 2 2

```

### 输出

```
3
2 2 2 
```

## 样例 #2

### 输入

```
4 3 1
1 4 1 1

```

### 输出

```
4
2 2 3 3 
```



---

---
title: "Memory and De-Evolution"
layout: "post"
diff: 普及+/提高
pid: CF712C
tag: ['贪心', '枚举']
---

# Memory and De-Evolution

## 题目描述

Memory 对物体，尤其是三角形的变化感兴趣。 他有一个边长为 $x$ 的等边三角形，他希望通过一些操作获得一个边长为 $y$ 的等边三角形。

他一次可以修改当前三角形一边的长度，修改后也应为合法的三角形。每次修改后，每一边的长度都应该是整数。

Memory 要获得边长 $y$ 的等边三角形，所需的最小修改次数是多少？

## 输入格式

第一行包含两个整数 $x$ 和 $y$（$3\le y < x \le 100000$），分别为最开始的三角形边长与想要获得的三角形边长。

## 输出格式

输出一个整数，即为最小的修改次数。

## 样例 #1

### 输入

```
6 3

```

### 输出

```
4

```

## 样例 #2

### 输入

```
8 5

```

### 输出

```
3

```

## 样例 #3

### 输入

```
22 4

```

### 输出

```
6

```



---

---
title: "Five Dimensional Points"
layout: "post"
diff: 普及+/提高
pid: CF850A
tag: ['枚举', '向量']
---

# Five Dimensional Points

## 题目描述

You are given set of $ n $ points in 5-dimensional space. The points are labeled from $ 1 $ to $ n $ . No two points coincide.

We will call point $ a $ bad if there are different points $ b $ and $ c $ , not equal to $ a $ , from the given set such that angle between vectors ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/0653dbc57091409c95cbdb75a14170af617d0442.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/bde2e95036e34134c1ea6bd6b9709d7dd49d1b09.png) is acute (i.e. strictly less than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/fe3c8011bb9ee15abb5ac0ee9f2f980eef59656c.png)). Otherwise, the point is called good.

The angle between vectors ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/5a3a683029365387cf086e592ebfccb0e126e88a.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/2c10c8fe0b4dfc279c1514830bc9fce0b1aa6b49.png) in 5-dimensional space is defined as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/d27dbfc0849680d0f326c5cde0af47140b2f6df3.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/0fea22328d6b3b4c1d11529ba4c9764cafce84d3.png) is the scalar product and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/f06b81b731bd497af38154f7447638a84ce787f2.png) is length of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/5a3a683029365387cf086e592ebfccb0e126e88a.png).

Given the list of points, print the indices of the good points in ascending order.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1<=n<=10^{3} $ ) — the number of points.

The next $ n $ lines of input contain five integers $ a_{i},b_{i},c_{i},d_{i},e_{i} $ ( $ |a_{i}|,|b_{i}|,|c_{i}|,|d_{i}|,|e_{i}|<=10^{3} $ ) — the coordinates of the i-th point. All points are distinct.

## 输出格式

First, print a single integer $ k $ — the number of good points.

Then, print $ k $ integers, each on their own line — the indices of the good points in ascending order.

## 说明/提示

In the first sample, the first point forms exactly a ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/fe3c8011bb9ee15abb5ac0ee9f2f980eef59656c.png) angle with all other pairs of points, so it is good.

In the second sample, along the cd plane, we can see the points look as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/dc25f4e169ea69409034b12812dd7f4f82002152.png)

We can see that all angles here are acute, so no points are good.

## 样例 #1

### 输入

```
6
0 0 0 0 0
1 0 0 0 0
0 1 0 0 0
0 0 1 0 0
0 0 0 1 0
0 0 0 0 1

```

### 输出

```
1
1

```

## 样例 #2

### 输入

```
3
0 0 1 2 0
0 0 9 2 0
0 0 5 9 0

```

### 输出

```
0

```



---

---
title: "Maximum Subsequence"
layout: "post"
diff: 普及+/提高
pid: CF888E
tag: ['搜索', '贪心', '枚举']
---

# Maximum Subsequence

## 题目描述

You are given an array $ a $ consisting of $ n $ integers, and additionally an integer $ m $ . You have to choose some sequence of indices $ b_{1},b_{2},...,b_{k} $ ( $ 1<=b_{1}&lt;b_{2}&lt;...&lt;b_{k}<=n $ ) in such a way that the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png) is maximized. Chosen sequence can be empty.

Print the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png).

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=35 $ , $ 1<=m<=10^{9} $ ).

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png).

## 说明/提示

In the first example you can choose a sequence $ b={1,2} $ , so the sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/08d6750b1b23699a8b513ddd01c316f10e6a789c.png) is equal to $ 7 $ (and that's $ 3 $ after taking it modulo $ 4 $ ).

In the second example you can choose a sequence $ b={3} $ .

## 样例 #1

### 输入

```
4 4
5 2 4 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 20
199 41 299

```

### 输出

```
19

```



---

---
title: "Almost Acyclic Graph"
layout: "post"
diff: 普及+/提高
pid: CF915D
tag: ['枚举', '排序', '拓扑排序']
---

# Almost Acyclic Graph

## 题目描述

You are given a [directed graph](https://en.wikipedia.org/wiki/Directed_graph) consisting of $ n $ vertices and $ m $ edges (each edge is directed, so it can be traversed in only one direction). You are allowed to remove at most one edge from it.

Can you make this graph [acyclic](https://en.wikipedia.org/wiki/Directed_acyclic_graph) by removing at most one edge from it? A directed graph is called acyclic iff it doesn't contain any cycle (a non-empty path that starts and ends in the same vertex).

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=500 $ , $ 1<=m<=min(n(n-1),100000) $ ) — the number of vertices and the number of edges, respectively.

Then $ m $ lines follow. Each line contains two integers $ u $ and $ v $ denoting a directed edge going from vertex $ u $ to vertex $ v $ ( $ 1<=u,v<=n $ , $ u≠v $ ). Each ordered pair $ (u,v) $ is listed at most once (there is at most one directed edge from $ u $ to $ v $ ).

## 输出格式

If it is possible to make this graph acyclic by removing at most one edge, print YES. Otherwise, print NO.

## 说明/提示

In the first example you can remove edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png), and the graph becomes acyclic.

In the second example you have to remove at least two edges (for example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/7480c546ca7ee72615c3ded7d769355b1c864f93.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png)) in order to make the graph acyclic.

## 样例 #1

### 输入

```
3 4
1 2
2 3
3 2
3 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
5 6
1 2
2 3
3 2
3 1
2 1
4 5

```

### 输出

```
NO

```



---

---
title: "Primal Sport"
layout: "post"
diff: 普及+/提高
pid: CF923A
tag: ['贪心', '枚举', '素数判断,质数,筛法']
---

# Primal Sport

## 题目描述

Alice and Bob begin their day with a quick game. They first choose a starting number $ X_{0}>=3 $ and try to reach one million by the process described below.

Alice goes first and then they take alternating turns. In the $ i $ -th turn, the player whose turn it is selects a prime number smaller than the current number, and announces the smallest multiple of this prime number that is not smaller than the current number.

Formally, he or she selects a prime $ p&lt;X_{i-1} $ and then finds the minimum $ X_{i}>=X_{i-1} $ such that $ p $ divides $ X_{i} $ . Note that if the selected prime $ p $ already divides $ X_{i-1} $ , then the number does not change.

Eve has witnessed the state of the game after two turns. Given $ X_{2} $ , help her determine what is the smallest possible starting number $ X_{0} $ . Note that the players don't necessarily play optimally. You should consider all possible game evolutions.

## 输入格式

The input contains a single integer $ X_{2} $ ( $ 4<=X_{2}<=10^{6} $ ). It is guaranteed that the integer $ X_{2} $ is composite, that is, is not prime.

## 输出格式

Output a single integer — the minimum possible $ X_{0} $ .

## 说明/提示

In the first test, the smallest possible starting number is $ X_{0}=6 $ . One possible course of the game is as follows:

- Alice picks prime 5 and announces $ X_{1}=10 $
- Bob picks prime 7 and announces $ X_{2}=14 $ .

In the second case, let $ X_{0}=15 $ .

- Alice picks prime 2 and announces $ X_{1}=16 $
- Bob picks prime 5 and announces $ X_{2}=20 $ .

## 样例 #1

### 输入

```
14

```

### 输出

```
6

```

## 样例 #2

### 输入

```
20

```

### 输出

```
15

```

## 样例 #3

### 输入

```
8192

```

### 输出

```
8191

```



---

---
title: "Chessboard"
layout: "post"
diff: 普及+/提高
pid: CF961C
tag: ['枚举']
---

# Chessboard

## 题目描述

Magnus decided to play a classic chess game. Though what he saw in his locker shocked him! His favourite chessboard got broken into $ 4 $ pieces, each of size $ n $ by $ n $ , $ n $ is always odd. And what's even worse, some squares were of wrong color. $ j $ -th square of the $ i $ -th row of $ k $ -th piece of the board has color $ a_{k,i,j} $ ; $ 1 $ being black and $ 0 $ being white.

Now Magnus wants to change color of some squares in such a way that he recolors minimum number of squares and obtained pieces form a valid chessboard. Every square has its color different to each of the neightbouring by side squares in a valid board. Its size should be $ 2n $ by $ 2n $ . You are allowed to move pieces but not allowed to rotate or flip them.

## 输入格式

The first line contains odd integer $ n $ $ (1<=n<=100) $ — the size of all pieces of the board.

Then $ 4 $ segments follow, each describes one piece of the board. Each consists of $ n $ lines of $ n $ characters; $ j $ -th one of $ i $ -th line is equal to 1 if the square is black initially and 0 otherwise. Segments are separated by an empty line.

## 输出格式

Print one number — minimum number of squares Magnus should recolor to be able to obtain a valid chessboard.

## 样例 #1

### 输入

```
1
0

0

1

0

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
101
010
101

101
000
101

010
101
011

010
101
010

```

### 输出

```
2

```



---

---
title: "Well played!"
layout: "post"
diff: 普及+/提高
pid: CF976E
tag: ['贪心', '枚举']
---

# Well played!

## 题目描述

Max 最近沉迷于一款打怪游戏《赛某号》。现在，他正在参加赛某号的春季联赛。

他有 $n$ 只精灵。每只精灵都有对应的生命值 $hp_i$ 和攻击值 $dmg_i$。在比赛过程中，Max 可以借助巴拉拉小魔仙之力，说出这两种咒语：

1. “乌卡拉！血量！加倍！“意即将当前精灵的生命值加倍。（使得 $hp_i \gets 2\times hp_i$）

2. “乌卡拉！生命之力！”意即将当前精灵的生命值赋给当前精灵的攻击值。（使得 $dmg_i\gets hp_i$）

Max 当然不能无限使用这两种咒语。在一局游戏中，他可以使用第一种咒语 $a$ 次，第二次咒语 $b$ 次。由于Max 购买了超级 Nono，所以这两种咒语都可以被多次用在同一精灵身上，且咒语的使用顺序没有限制。Max 可以不用完所有的咒语。

Max 非常希望通过使用这些咒语使得自己的精灵战斗群的攻击值达到最大。现在，Max 想知道这个最大值。


输入第 $2$ 行到第 $n+1$ 行，每行两个整数 $hp$，$dmg$。第 $i$ 行表示第 $i-1$ 个精灵的生命值和攻击值。

## 输出格式

输出一行一个整数，代表 Max 的精灵战斗群能达到的最大攻击值。

**样例 1 解释**

Max 在第二只精灵上先使用第一种魔咒将其生命值加倍，此时的生命值为 $12$。此时，再用第二种魔咒将它的攻击值赋为当前的生命值，则第二只精灵的攻击值为 $12$。可以证明，不存在其它的方案使得这两只精灵的攻击值总和更大。

## 样例 #1

### 输入

```
2 1 1
10 15
6 1

```

### 输出

```
27

```

## 样例 #2

### 输入

```
3 0 3
10 8
7 11
5 2

```

### 输出

```
26

```



---

---
title: "How many trees?"
layout: "post"
diff: 普及+/提高
pid: CF9D
tag: ['动态规划 DP', '枚举']
---

# How many trees?

## 题目描述

In one very old text file there was written Great Wisdom. This Wisdom was so Great that nobody could decipher it, even Phong — the oldest among the inhabitants of Mainframe. But still he managed to get some information from there. For example, he managed to learn that User launches games for pleasure — and then terrible Game Cubes fall down on the city, bringing death to those modules, who cannot win the game...

For sure, as guard Bob appeared in Mainframe many modules stopped fearing Game Cubes. Because Bob (as he is alive yet) has never been defeated by User, and he always meddles with Game Cubes, because he is programmed to this.

However, unpleasant situations can happen, when a Game Cube falls down on Lost Angles. Because there lives a nasty virus — Hexadecimal, who is... mmm... very strange. And she likes to play very much. So, willy-nilly, Bob has to play with her first, and then with User.

This time Hexadecimal invented the following entertainment: Bob has to leap over binary search trees with $ n $ nodes. We should remind you that a binary search tree is a binary tree, each node has a distinct key, for each node the following is true: the left sub-tree of a node contains only nodes with keys less than the node's key, the right sub-tree of a node contains only nodes with keys greater than the node's key. All the keys are different positive integer numbers from $ 1 $ to $ n $ . Each node of such a tree can have up to two children, or have no children at all (in the case when a node is a leaf).

In Hexadecimal's game all the trees are different, but the height of each is not lower than $ h $ . In this problem «height» stands for the maximum amount of nodes on the way from the root to the remotest leaf, the root node and the leaf itself included. When Bob leaps over a tree, it disappears. Bob gets the access to a Cube, when there are no trees left. He knows how many trees he will have to leap over in the worst case. And you?

## 输入格式

The input data contains two space-separated positive integer numbers $ n $ and $ h $ ( $ n<=35 $ , $ h<=n $ ).

## 输出格式

Output one number — the answer to the problem. It is guaranteed that it does not exceed $ 9·10^{18} $ .

## 样例 #1

### 输入

```
3 2

```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 3

```

### 输出

```
4
```



---

