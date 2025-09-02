---
title: "Yet Another LCP Problem"
layout: "post"
diff: 省选/NOI-
pid: CF1073G
tag: ['字符串', '图论', '后缀自动机 SAM', '虚树', '后缀数组 SA', '后缀树']
---

# Yet Another LCP Problem

## 题目描述

Let $ \text{LCP}(s, t) $ be the length of the longest common prefix of strings $ s $ and $ t $ . Also let $ s[x \dots y] $ be the substring of $ s $ from index $ x $ to index $ y $ (inclusive). For example, if $ s =  $ "abcde", then $ s[1 \dots 3] = $ "abc", $ s[2 \dots 5] = $ "bcde".

You are given a string $ s $ of length $ n $ and $ q $ queries. Each query is a pair of integer sets $ a_1, a_2, \dots, a_k $ and $ b_1, b_2, \dots, b_l $ . Calculate $ \sum\limits_{i = 1}^{i = k} \sum\limits_{j = 1}^{j = l}{\text{LCP}(s[a_i \dots n], s[b_j \dots n])} $ for each query.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the length of string $ s $ and the number of queries, respectively.

The second line contains a string $ s $ consisting of lowercase Latin letters ( $ |s| = n $ ).

Next $ 3q $ lines contains descriptions of queries — three lines per query. The first line of each query contains two integers $ k_i $ and $ l_i $ ( $ 1 \le k_i, l_i \le n $ ) — sizes of sets $ a $ and $ b $ respectively.

The second line of each query contains $ k_i $ integers $ a_1, a_2, \dots a_{k_i} $ ( $ 1 \le a_1 < a_2 < \dots < a_{k_i} \le n $ ) — set $ a $ .

The third line of each query contains $ l_i $ integers $ b_1, b_2, \dots b_{l_i} $ ( $ 1 \le b_1 < b_2 < \dots < b_{l_i} \le n $ ) — set $ b $ .

It is guaranteed that $ \sum\limits_{i = 1}^{i = q}{k_i} \le 2 \cdot 10^5 $ and $ \sum\limits_{i = 1}^{i = q}{l_i} \le 2 \cdot 10^5 $ .

## 输出格式

Print $ q $ integers — answers for the queries in the same order queries are given in the input.

## 说明/提示

Description of queries:

1. In the first query $ s[1 \dots 7] = \text{abacaba} $ and $ s[2 \dots 7] = \text{bacaba} $ are considered. The answer for the query is $ \text{LCP}(\text{abacaba}, \text{abacaba}) + \text{LCP}(\text{abacaba}, \text{bacaba}) + \text{LCP}(\text{bacaba}, \text{abacaba}) + \text{LCP}(\text{bacaba}, \text{bacaba}) = 7 + 0 + 0 + 6 = 13 $ .
2. In the second query $ s[1 \dots 7] = \text{abacaba} $ , $ s[2 \dots 7] = \text{bacaba} $ , $ s[3 \dots 7] = \text{acaba} $ and $ s[7 \dots 7] = \text{a} $ are considered. The answer for the query is $ \text{LCP}(\text{abacaba}, \text{a}) + \text{LCP}(\text{bacaba}, \text{a}) + \text{LCP}(\text{acaba}, \text{a}) = 1 + 0 + 1 = 2 $ .
3. In the third query $ s[1 \dots 7] = \text{abacaba} $ are compared with all suffixes. The answer is the sum of non-zero values: $ \text{LCP}(\text{abacaba}, \text{abacaba}) + \text{LCP}(\text{abacaba}, \text{acaba}) + \text{LCP}(\text{abacaba}, \text{aba}) + \text{LCP}(\text{abacaba}, \text{a}) = 7 + 1 + 3 + 1 = 12 $ .
4. In the fourth query $ s[1 \dots 7] = \text{abacaba} $ and $ s[5 \dots 7] = \text{aba} $ are considered. The answer for the query is $ \text{LCP}(\text{abacaba}, \text{abacaba}) + \text{LCP}(\text{abacaba}, \text{aba}) + \text{LCP}(\text{aba}, \text{abacaba}) + \text{LCP}(\text{aba}, \text{aba}) = 7 + 3 + 3 + 3 = 16 $ .

## 样例 #1

### 输入

```
7 4
abacaba
2 2
1 2
1 2
3 1
1 2 3
7
1 7
1
1 2 3 4 5 6 7
2 2
1 5
1 5

```

### 输出

```
13
2
12
16

```



---

---
title: "String"
layout: "post"
diff: 省选/NOI-
pid: CF123D
tag: ['线段树', '排序', '后缀数组 SA']
---

# String

## 题目描述

You are given a string $ s $ . Each pair of numbers $ l $ and $ r $ that fulfill the condition $ 1<=l<=r<=|s| $ , correspond to a substring of the string $ s $ , starting in the position $ l $ and ending in the position $ r $ (inclusive).

Let's define the function of two strings $ F(x,y) $ like this. We'll find a list of such pairs of numbers for which the corresponding substrings of string $ x $ are equal to string $ y $ . Let's sort this list of pairs according to the pair's first number's increasing. The value of function $ F(x,y) $ equals the number of non-empty continuous sequences in the list.

For example: $ F(babbabbababbab,babb)=6 $ . The list of pairs is as follows:

 $ (1,4),(4,7),(9,12) $

Its continuous sequences are:

- $ (1,4) $
- $ (4,7) $
- $ (9,12) $
- $ (1,4),(4,7) $
- $ (4,7),(9,12) $
- $ (1,4),(4,7),(9,12) $

Your task is to calculate for the given string $ s $ the sum $ F(s,x) $ for all $ x $ , that $ x $ belongs to the set of all substrings of a string $ s $ .

## 输入格式

The only line contains the given string $ s $ , consisting only of small Latin letters ( $ 1<=|s|<=10^{5} $ ).

## 输出格式

Print the single number — the sought sum.

Please do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specificator.

## 说明/提示

In the first sample the function values at $ x $ equal to "a", "aa", "aaa" and "aaaa" equal 10, 6, 3 and 1 correspondingly.

In the second sample for any satisfying $ x $ the function value is 1.

## 样例 #1

### 输入

```
aaaa

```

### 输出

```
20

```

## 样例 #2

### 输入

```
abcdef

```

### 输出

```
21

```

## 样例 #3

### 输入

```
abacabadabacaba

```

### 输出

```
188

```



---

---
title: "Shrink-Reverse"
layout: "post"
diff: 省选/NOI-
pid: CF1923F
tag: ['后缀自动机 SAM', '后缀数组 SA']
---

# Shrink-Reverse

## 题目描述

You are given a binary string $ s $ of length $ n $ (a string consisting of $ n $ characters, and each character is either 0 or 1).

Let's look at $ s $ as at a binary representation of some integer, and name that integer as the value of string $ s $ . For example, the value of 000 is $ 0 $ , the value of 01101 is $ 13 $ , "100000" is $ 32 $ and so on.

You can perform at most $ k $ operations on $ s $ . Each operation should have one of the two following types:

- SWAP: choose two indices $ i < j $ in $ s $ and swap $ s_i $ with $ s_j $ ;
- SHRINK-REVERSE: delete all leading zeroes from $ s $ and reverse $ s $ .

 For example, after you perform SHRINK-REVERSE on 000101100, you'll get 001101.What is the minimum value of $ s $ you can achieve by performing at most $ k $ operations on $ s $ ?

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2 \le n \le 5 \cdot 10^5 $ ; $ 1 \le k \le n $ ) — the length of the string $ s $ and the maximum number of operations.

The second line contains the string $ s $ of length $ n $ consisting of characters 0 and/or 1.

Additional constraint on the input: $ s $ contains at least one 1.

## 输出格式

Print a single integer — the minimum value of $ s $ you can achieve using no more than $ k $ operations. Since the answer may be too large, print it modulo $ 10^{9} + 7 $ .

Note that you need to minimize the original value, not the remainder.

## 说明/提示

In the first example, one of the optimal strategies is the following:

1. 10010010 $ \xrightarrow{\texttt{SWAP}} $ 00010110;
2. 00010110 $ \xrightarrow{\texttt{SWAP}} $ 00000111.

 The value of 00000111 is $ 7 $ .In the second example, one of the optimal strategies is the following:

1. 01101000 $ \xrightarrow{\texttt{SHRINK}} $ 1101000 $ \xrightarrow{\texttt{REVERSE}} $ 0001011;
2. 0001011 $ \xrightarrow{\texttt{SWAP}} $ 0000111.

 The value of 0000111 is $ 7 $ .

## 样例 #1

### 输入

```
8 2
10010010
```

### 输出

```
7
```

## 样例 #2

### 输入

```
8 2
01101000
```

### 输出

```
7
```

## 样例 #3

### 输入

```
30 30
111111111111111111111111111111
```

### 输出

```
73741816
```

## 样例 #4

### 输入

```
14 1
10110001111100
```

### 输出

```
3197
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
title: "Fence"
layout: "post"
diff: 省选/NOI-
pid: CF232D
tag: ['线段树', '后缀数组 SA']
---

# Fence

## 题目描述

John Doe has a crooked fence, consisting of $ n $ rectangular planks, lined up from the left to the right: the plank that goes $ i $ -th $ (1<=i<=n) $ (from left to right) has width 1 and height $ h_{i} $ . We will assume that the plank that goes $ i $ -th $ (1<=i<=n) $ (from left to right) has index $ i $ .

A piece of the fence from $ l $ to $ r $ $ (1<=l<=r<=n) $ is a sequence of planks of wood with indices from $ l $ to $ r $ inclusive, that is, planks with indices $ l,l+1,...,r $ . The width of the piece of the fence from $ l $ to $ r $ is value $ r-l+1 $ .

Two pieces of the fence from $ l_{1} $ to $ r_{1} $ and from $ l_{2} $ to $ r_{2} $ are called matching, if the following conditions hold:

- the pieces do not intersect, that is, there isn't a single plank, such that it occurs in both pieces of the fence;
- the pieces are of the same width;
- for all $ i $ $ (0<=i<=r_{1}-l_{1}) $ the following condition holds: $ h_{l1+i}+h_{l2+i}=h_{l1}+h_{l2} $ .

John chose a few pieces of the fence and now wants to know how many distinct matching pieces are for each of them. Two pieces of the fence are distinct if there is a plank, which belongs to one of them and does not belong to the other one.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of wood planks in the fence. The second line contains $ n $ space-separated integers $ h_{1},h_{2},...,h_{n} $ ( $ 1<=h_{i}<=10^{9} $ ) — the heights of fence planks.

The third line contains integer $ q $ ( $ 1<=q<=10^{5} $ ) — the number of queries. Next $ q $ lines contain two space-separated integers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) — the boundaries of the $ i $ -th piece of the fence.

## 输出格式

For each query on a single line print a single integer — the number of pieces of the fence that match the given one. Print the answers to the queries in the order, in which the queries are given in the input.

## 样例 #1

### 输入

```
10
1 2 2 1 100 99 99 100 100 100
6
1 4
1 2
3 4
1 5
9 10
10 10

```

### 输出

```
1
2
2
0
2
9

```



---

