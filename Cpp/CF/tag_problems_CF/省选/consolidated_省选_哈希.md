---
title: "Quadratic Set"
layout: "post"
diff: 省选/NOI-
pid: CF1622F
tag: ['图论', '哈希 hashing']
---

# Quadratic Set

## 题目描述

Let's call a set of positive integers $ a_1, a_2, \dots, a_k $ quadratic if the product of the factorials of its elements is a square of an integer, i. e. $ \prod\limits_{i=1}^{k} a_i! = m^2 $ , for some integer $ m $ .

You are given a positive integer $ n $ .

Your task is to find a quadratic subset of a set $ 1, 2, \dots, n $ of maximum size. If there are multiple answers, print any of them.

## 输入格式

A single line contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ).

## 输出格式

In the first line, print a single integer — the size of the maximum subset. In the second line, print the subset itself in an arbitrary order.

## 样例 #1

### 输入

```
1
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
4
```

### 输出

```
3
1 3 4
```

## 样例 #3

### 输入

```
7
```

### 输出

```
4
1 4 5 6
```

## 样例 #4

### 输入

```
9
```

### 输出

```
7
1 2 4 5 6 7 9
```



---

---
title: "Kazaee"
layout: "post"
diff: 省选/NOI-
pid: CF1746F
tag: ['树状数组', '哈希 hashing']
---

# Kazaee

## 题目描述

给出一个长度为 $n$ 的数组 $a$ 和以下两种操作：

- $1\ i\ x$：将 $a_i$ 修改为 $x$。
- $2\ l\ r\ k$：询问在数组区间 $[l, r]$ 内是否每个出现过的正整数的出现次数都是 $k$ 的倍数。（建议参照样例理解）若是则输出 `YES`，若否则输出 `NO`。

## 输入格式

第一行两个整数 $n$、$q$，表示数组长度和操作数。

第二行 $n$ 个整数，为数组 $a$ 中的元素。（下标从1开始）

之后 $q$ 行，每行一个询问。

## 输出格式

对于每个操作2，给出相应答案（YES 或 NO）。

## 样例 #1

### 输入

```
10 8
1234 2 3 3 2 1 1 2 3 4
2 1 6 2
1 1 1
2 1 6 2
2 1 9 2
1 10 5
2 1 9 3
1 3 5
2 3 10 2
```

### 输出

```
NO
YES
NO
YES
YES
```



---

---
title: "Frequency Mismatch (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1957F1
tag: ['线段树', '哈希 hashing']
---

# Frequency Mismatch (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the two versions of this problem is the constraint on $ k $ . You can make hacks only if all versions of the problem are solved.

You are given an undirected tree of $ n $ nodes. Each node $ v $ has a value $ a_v $ written on it. You have to answer queries related to the tree.

You are given $ q $ queries. In each query, you are given $ 5 $ integers, $ u_1, v_1, u_2, v_2, k $ . Denote the count of nodes with value $ c $ on path $ u_1 \rightarrow v_1 $ with $ x_c $ , and the count of nodes with value $ c $ on path $ u_2 \rightarrow v_2 $ with $ y_c $ . If there are $ z $ such values of $ c $ such that $ x_c \neq y_c $ , output any $ \min(z, k) $ such values in any order.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the number of nodes in the tree.

The next line contains $ n $ integers, $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^5 $ ) — the value written on each node of the tree.

Then $ n - 1 $ lines follow. Each line contains two integers $ u $ and $ v $ ( $ 1 \leq u, v \leq n, u \neq v $ ) denoting an edge of the tree. It is guaranteed that the given edges form a tree.

The next line contains one integer $ q $ ( $ 1 \leq q \leq 10^5 $ ) — the number of queries.

Then $ q $ lines follow. Each line contains five integers $ u_1, v_1, u_2, v_2, k $ ( $ 1 \leq u_1, v_1, u_2, v_2 \leq n $ , $ k = 1 $ ).

## 输出格式

For each query, output on a separate line. For a query, first output $ \min(z, k) $ and then on the same line, output any $ \min(z, k) $ values in any order which occur a different number of times in each path.

## 说明/提示

For query $ 1 $ , the first path is $ 1 \rightarrow 2 \rightarrow 4 $ , coming across the multiset of values $ \{5, 2, 4\} $ . On the second path $ 4 \rightarrow 2 \rightarrow 5 $ , we have the multiset $ \{4, 2, 3\} $ . Two numbers — $ 3 $ and $ 5 $ occur a different number of times, hence we print one of them.

In query $ 2 $ , there is no difference between the paths, hence we output $ 0 $ .

In query $ 3 $ , the first path is just the node $ 5 $ , resulting in the multiset $ \{3\} $ , and the second path $ 4 \rightarrow 2 \rightarrow 1 \rightarrow 3 $ gives $ \{4, 2, 5, 3\} $ . The numbers $ 5 $ , $ 2 $ and $ 4 $ occur a different number of times.

## 样例 #1

### 输入

```
5
5 2 3 4 3
1 2
1 3
2 4
2 5
3
1 4 4 5 1
2 3 2 3 1
5 5 4 3 1
```

### 输出

```
1 5
0
1 2
```



---

---
title: "Frequency Mismatch (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1957F2
tag: ['线段树', '哈希 hashing']
---

# Frequency Mismatch (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the two versions of this problem is the constraint on $ k $ . You can make hacks only if all versions of the problem are solved.

You are given an undirected tree of $ n $ nodes. Each node $ v $ has a value $ a_v $ written on it. You have to answer queries related to the tree.

You are given $ q $ queries. In each query, you are given $ 5 $ integers, $ u_1, v_1, u_2, v_2, k $ . Denote the count of nodes with value $ c $ on path $ u_1 \rightarrow v_1 $ with $ x_c $ , and the count of nodes with value $ c $ on path $ u_2 \rightarrow v_2 $ with $ y_c $ . If there are $ z $ such values of $ c $ such that $ x_c \neq y_c $ , output any $ \min(z, k) $ such values in any order.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the number of nodes in the tree.

The next line contains $ n $ integers, $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^5 $ ) — the value written on each node of the tree.

Then $ n - 1 $ lines follow. Each line contains two integers $ u $ and $ v $ ( $ 1 \leq u, v \leq n, u \neq v $ ) denoting an edge of the tree. It is guaranteed that the given edges form a tree.

The next line contains one integer $ q $ ( $ 1 \leq q \leq 10^5 $ ) — the number of queries.

Then $ q $ lines follow. Each line contains five integers $ u_1, v_1, u_2, v_2, k $ ( $ 1 \leq u_1, v_1, u_2, v_2 \leq n $ , $ 1 \leq k \leq 10 $ ).

## 输出格式

For each query, output on a separate line. For a query, first output $ \min(z, k) $ and then on the same line, output any $ \min(z, k) $ values in any order which occur a different number of times in each path.

## 说明/提示

For query $ 1 $ , the first path is $ 1 \rightarrow 2 \rightarrow 4 $ , coming across the multiset of values $ \{5, 2, 4\} $ . On the second path $ 4 \rightarrow 2 \rightarrow 5 $ , we have the multiset $ \{4, 2, 3\} $ . Two numbers — $ 3 $ and $ 5 $ occur a different number of times, hence we print them both.

In query $ 2 $ , there is no difference between the paths, hence we output $ 0 $ .

In query $ 3 $ , we have the same paths as query $ 1 $ , but we need to output only $ 1 $ value, hence we output $ 5 $ .

In query $ 4 $ , the first path is just the node $ 5 $ , resulting in the multiset $ \{3\} $ , and the second path $ 4 \rightarrow 2 \rightarrow 1 \rightarrow 3 $ gives $ \{4, 2, 5, 3\} $ . The numbers $ 5 $ , $ 2 $ and $ 4 $ occur a different number of times.

## 样例 #1

### 输入

```
5
5 2 3 4 3
1 2
1 3
2 4
2 5
4
1 4 4 5 3
2 3 2 3 1
1 4 4 5 1
5 5 4 3 10
```

### 输出

```
2 3 5
0
1 5
3 5 2 4
```



---

---
title: "The Next Good String"
layout: "post"
diff: 省选/NOI-
pid: CF196D
tag: ['字符串', '枚举', '哈希 hashing']
---

# The Next Good String

## 题目描述

In problems on strings one often has to find a string with some particular properties. The problem authors were reluctant to waste time on thinking of a name for some string so they called it good. A string is good if it doesn't have palindrome substrings longer than or equal to $ d $ .

You are given string $ s $ , consisting only of lowercase English letters. Find a good string $ t $ with length $ |s| $ , consisting of lowercase English letters, which is lexicographically larger than $ s $ . Of all such strings string $ t $ must be lexicographically minimum.

We will call a non-empty string $ s[a ... b]=s_{a}s_{a+1}...\ s_{b} $ $ (1<=a<=b<=|s|) $ a substring of string $ s=s_{1}s_{2}...\ s_{|s|} $ .

A non-empty string $ s=s_{1}s_{2}...\ s_{n} $ is called a palindrome if for all $ i $ from $ 1 $ to $ n $ the following fulfills: $ s_{i}=s_{n-i+1} $ . In other words, palindrome read the same in both directions.

String $ x=x_{1}x_{2}...\ x_{|x|} $ is lexicographically larger than string $ y=y_{1}y_{2}...\ y_{|y|} $ , if either $ |x|&gt;|y| $ and $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{|y|}=y_{|y|} $ , or there exists such number $ r $ $ (r&lt;|x|,r&lt;|y|) $ , that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&gt;y_{r+1} $ . Characters in such strings are compared like their ASCII codes.

## 输入格式

The first line contains integer $ d $ ( $ 1<=d<=|s| $ ).

The second line contains a non-empty string $ s $ , its length is no more than $ 4·10^{5} $ characters. The string consists of lowercase English letters.

## 输出格式

Print the good string that lexicographically follows $ s $ , has the same length and consists of only lowercase English letters. If such string does not exist, print "Impossible" (without the quotes).

## 样例 #1

### 输入

```
3
aaaaaaa

```

### 输出

```
aabbcaa

```

## 样例 #2

### 输入

```
3
zzyzzzz

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
4
abbabbbabbb

```

### 输出

```
abbbcaaabab

```



---

---
title: "Game with Two Trees"
layout: "post"
diff: 省选/NOI-
pid: CF207C3
tag: ['哈希 hashing', '后缀数组 SA']
---

# Game with Two Trees

## 题目描述

The Smart Beaver from ABBYY has come up with a new developing game for children. The Beaver thinks that this game will help children to understand programming better.

The main object of the game is finite rooted trees, each of their edges contains some lowercase English letter. Vertices on any tree are always numbered sequentially from $ 1 $ to $ m $ , where $ m $ is the number of vertices in the tree. Before describing the actual game, let's introduce some definitions.

We'll assume that the sequence of vertices with numbers $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ ( $ k>=1 $ ) is a forward path, if for any integer $ i $ from $ 1 $ to $ k-1 $ vertex $ v_{i} $ is a direct ancestor of vertex $ v_{i+1} $ . If we sequentially write out all letters from the the edges of the given path from $ v_{1} $ to $ v_{k} $ , we get some string ( $ k=1 $ gives us an empty string). We'll say that such string corresponds to forward path $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ .

We'll assume that the sequence of tree vertices with numbers $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ ( $ k>=1 $ ) is a backward path if for any integer $ i $ from $ 1 $ to $ k-1 $ vertex $ v_{i} $ is the direct descendant of vertex $ v_{i+1} $ . If we sequentially write out all the letters from the edges of the given path from $ v_{1} $ to $ v_{k} $ , we get some string ( $ k=1 $ gives us an empty string). We'll say that such string corresponds to backward path $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ .

Now let's describe the game that the Smart Beaver from ABBYY has come up with. The game uses two rooted trees, each of which initially consists of one vertex with number $ 1 $ . The player is given some sequence of operations. Each operation is characterized by three values ( $ t $ , $ v $ , $ c $ ) where:

- $ t $ is the number of the tree on which the operation is executed ( $ 1 $ or $ 2 $ );
- $ v $ is the vertex index in this tree (it is guaranteed that the tree contains a vertex with this index);
- $ c $ is a lowercase English letter.

The actual operation is as follows: vertex $ v $ of tree $ t $ gets a new descendant with number $ m+1 $ (where $ m $ is the current number of vertices in tree $ t $ ), and there should be letter $ c $ put on the new edge from vertex $ v $ to vertex $ m+1 $ .

We'll say that an ordered group of three integers ( $ i $ , $ j $ , $ q $ ) is a good combination if:

- $ 1<=i<=m_{1} $ , where $ m_{1} $ is the number of vertices in the first tree;
- $ 1<=j,q<=m_{2} $ , where $ m_{2} $ is the number of vertices in the second tree;
- there exists a forward path $ v_{1} $ , $ v_{2} $ , $ ... $ , $ v_{k} $ such that $ v_{1}=j $ and $ v_{k}=q $ in the second tree;
- the string that corresponds to the forward path in the second tree from vertex $ j $ to vertex $ q $ equals the string that corresponds to the backward path in the first tree from vertex $ i $ to vertex $ 1 $ (note that both paths are determined uniquely).

Your task is to calculate the number of existing good combinations after each operation on the trees.

## 输入格式

The first line contains integer $ n $ — the number of operations on the trees. Next $ n $ lines specify the operations in the order of their execution. Each line has form " $ t $ $ v $ $ c $ ", where $ t $ is the number of the tree, $ v $ is the vertex index in this tree, and $ c $ is a lowercase English letter.

To get the full points for the first group of tests it is sufficient to solve the problem with $ 1<=n<=700 $ .

To get the full points for the second group of tests it is sufficient to solve the problem with $ 1<=n<=7000 $ .

To get the full points for the third group of tests it is sufficient to solve the problem with $ 1<=n<=100000 $ .

## 输出格式

Print exactly $ n $ lines, each containing one integer — the number of existing good combinations after the corresponding operation from the input.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

After the first operation the only good combination was $ (1,1,1) $ . After the second operation new good combinations appeared, $ (2,1,2) $ and $ (1,2,2) $ . The third operation didn't bring any good combinations. The fourth operation added good combination $ (1,3,3) $ . Finally, the fifth operation resulted in as much as three new good combinations — $ (1,4,4) $ , $ (2,3,4) $ and $ (3,1,4) $ .

## 样例 #1

### 输入

```
5
1 1 a
2 1 a
1 2 b
2 1 b
2 3 a

```

### 输出

```
1
3
3
4
7

```



---

---
title: "Two Permutations"
layout: "post"
diff: 省选/NOI-
pid: CF213E
tag: ['线段树', '平衡树', '枚举', '哈希 hashing']
---

# Two Permutations

## 题目描述

Rubik is very keen on number permutations.

A permutation $ a $ with length $ n $ is a sequence, consisting of $ n $ different numbers from 1 to $ n $ . Element number $ i $ $ (1<=i<=n) $ of this permutation will be denoted as $ a_{i} $ .

Furik decided to make a present to Rubik and came up with a new problem on permutations. Furik tells Rubik two number permutations: permutation $ a $ with length $ n $ and permutation $ b $ with length $ m $ . Rubik must give an answer to the problem: how many distinct integers $ d $ exist, such that sequence $ c $ $ (c_{1}=a_{1}+d,c_{2}=a_{2}+d,...,c_{n}=a_{n}+d) $ of length $ n $ is a subsequence of $ b $ .

Sequence $ a $ is a subsequence of sequence $ b $ , if there are such indices $ i_{1},i_{2},...,i_{n} $ $ (1<=i_{1}&lt;i_{2}&lt;...&lt;i_{n}<=m) $ , that $ a_{1}=b_{i1} $ , $ a_{2}=b_{i2} $ , $ ... $ , $ a_{n}=b_{in} $ , where $ n $ is the length of sequence $ a $ , and $ m $ is the length of sequence $ b $ .

You are given permutations $ a $ and $ b $ , help Rubik solve the given problem.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n<=m<=200000) $ — the sizes of the given permutations. The second line contains $ n $ distinct integers — permutation $ a $ , the third line contains $ m $ distinct integers — permutation $ b $ . Numbers on the lines are separated by spaces.

## 输出格式

On a single line print the answer to the problem.

## 样例 #1

### 输入

```
1 1
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
1 2
1
2 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 3
2 3 1
1 2 3

```

### 输出

```
0

```



---

---
title: "Kefa and Watch"
layout: "post"
diff: 省选/NOI-
pid: CF580E
tag: ['字符串', '线段树', '哈希 hashing']
---

# Kefa and Watch

## 题目描述

One day Kefa the parrot was walking down the street as he was on the way home from the restaurant when he saw something glittering by the road. As he came nearer he understood that it was a watch. He decided to take it to the pawnbroker to earn some money.

The pawnbroker said that each watch contains a serial number represented by a string of digits from $ 0 $ to $ 9 $ , and the more quality checks this number passes, the higher is the value of the watch. The check is defined by three positive integers $ l $ , $ r $ and $ d $ . The watches pass a check if a substring of the serial number from $ l $ to $ r $ has period $ d $ . Sometimes the pawnbroker gets distracted and Kefa changes in some substring of the serial number all digits to $ c $ in order to increase profit from the watch.

The seller has a lot of things to do to begin with and with Kefa messing about, he gave you a task: to write a program that determines the value of the watch.

Let us remind you that number $ x $ is called a period of string $ s $ ( $ 1<=x<=|s| $ ), if $ s_{i}=s_{i+x} $ for all $ i $ from 1 to $ |s|-x $ .

## 输入格式

The first line of the input contains three positive integers $ n $ , $ m $ and $ k $ ( $ 1<=n<=10^{5} $ , $ 1<=m+k<=10^{5} $ ) — the length of the serial number, the number of change made by Kefa and the number of quality checks.

The second line contains a serial number consisting of $ n $ digits.

Then $ m+k $ lines follow, containing either checks or changes.

The changes are given as 1 $ l $ $ r $ $ c $ ( $ 1<=l<=r<=n $ , $ 0<=c<=9 $ ). That means that Kefa changed all the digits from the $ l $ -th to the $ r $ -th to be $ c $ .

The checks are given as 2 $ l $ $ r $ $ d $ ( $ 1<=l<=r<=n $ , $ 1<=d<=r-l+1 $ ).

## 输出格式

For each check on a single line print "YES" if the watch passed it, otherwise print "NO".

## 说明/提示

In the first sample test two checks will be made. In the first one substring "12" is checked on whether or not it has period 1, so the answer is "NO". In the second one substring "88", is checked on whether or not it has period 1, and it has this period, so the answer is "YES".

In the second statement test three checks will be made. The first check processes substring "3493", which doesn't have period 2. Before the second check the string looks as "334334", so the answer to it is "YES". And finally, the third check processes substring "8334", which does not have period 1.

## 样例 #1

### 输入

```
3 1 2
112
2 2 3 1
1 1 3 8
2 1 2 1

```

### 输出

```
NO
YES

```

## 样例 #2

### 输入

```
6 2 3
334934
2 2 5 2
1 4 4 3
2 1 6 3
1 2 3 8
2 3 6 1

```

### 输出

```
NO
YES
NO

```



---

---
title: "String Set Queries"
layout: "post"
diff: 省选/NOI-
pid: CF710F
tag: ['分治', '哈希 hashing', '分块', '字典树 Trie', 'AC 自动机', 'KMP 算法']
---

# String Set Queries

## 题目描述

You should process $ m $ queries over a set $ D $ of strings. Each query is one of three kinds:

1. Add a string $ s $ to the set $ D $ . It is guaranteed that the string $ s $ was not added before.
2. Delete a string $ s $ from the set $ D $ . It is guaranteed that the string $ s $ is in the set $ D $ .
3. For the given string $ s $ find the number of occurrences of the strings from the set $ D $ . If some string $ p $ from $ D $ has several occurrences in $ s $ you should count all of them.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query of the third type. Use functions fflush in C++ and BufferedWriter.flush in Java languages after each writing in your program.

## 输入格式

The first line contains integer $ m $ ( $ 1<=m<=3·10^{5} $ ) — the number of queries.

Each of the next $ m $ lines contains integer $ t $ ( $ 1<=t<=3 $ ) and nonempty string $ s $ — the kind of the query and the string to process. All strings consist of only lowercase English letters.

The sum of lengths of all strings in the input will not exceed $ 3·10^{5} $ .

## 输出格式

For each query of the third kind print the only integer $ c $ — the desired number of occurrences in the string $ s $ .

## 样例 #1

### 输入

```
5
1 abc
3 abcabc
2 abc
1 aba
3 abababc

```

### 输出

```
2
2

```

## 样例 #2

### 输入

```
10
1 abc
1 bcd
1 abcd
3 abcd
2 abcd
3 abcd
2 bcd
3 abcd
2 abc
3 abcd

```

### 输出

```
3
2
1
0

```



---

