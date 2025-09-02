---
title: "Red-White Fence"
layout: "post"
diff: 省选/NOI-
pid: CF1251F
tag: ['数学', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---

# Red-White Fence

## 题目描述

Polycarp想在他家附近建一道栅栏。他有$n$个白板和$k$个红板去建造它。每一块板都有一个整数长度。

一个好的栅栏应由一块红板和几块（可能是零块）白板组成。红色的板应该在这道栅栏中是**最长的**，而且红板前的板子长度应为递增，而红板之后的板子长度为递减。如果用了$m$块板子，它们的长度从左到右依次是$l_1,l_2,…,l_m$，那么应该符合以下条件

①栅栏上应**有且只有一块**红板，设其序号为$j$

②对于所有的$i∈[1,j-1]$有$l_i<l_{i+1}$

③对于所有的$i∈[j,m-1]$有$l_i>l_{i+1}$

在Polycarp建造他的栅栏时，他会从左向右在$0$高度上放置所有板，没有间隙，所以这些板将会组成一个多边形

例图：一个栅栏的板长数组为$[1,2,3,4,5]$，第二个板是红板。栅栏的周长是$20$。Polycrp对一些特殊周长的栅栏感兴趣。他有喜欢的$q$个偶整数$[Q_1,Q_2,…,Q_q]$，对于每个这样的整数$Q_i$，他想计算有几种不同的周长是$Q_i$的篱笆可以被造出来（如果两个篱笆的板长排列不同，那么就认为这两个篱笆是不同的）你可以帮他计算这些数值吗？

## 输入格式

输入第一行是两个正整数$n,k(1≤n≤3*10^5,1≤k≤5)$，表示Polycarp拥有的白板和红板的数量

第二行有$n$个正整数$[a_1,a_2,...,a_n](1≤a_i≤3*10^5)$，表示Polycarp拥有的$n$块白板的长度

第三行有$k$个正整数$[b_1,b_2,...,b_k](1≤b_i≤3*10^5)$，表示Polycarp拥有的$k$块红板的长度，所有$b_i$都是不相同的

第四行是一个正整数$q(1≤q≤3*10^5)$，表示特殊周长的数量

第五行有$q$个正整数$[Q_1,Q_2,...,Q_q](4≤Q_i≤12*10^5)$，每个$Q_i$都是偶数，表示Polycarp喜欢的特殊整数（即特殊周长）

## 输出格式

对于每个$Q_i$，输出一个整数，表示有多少种符合约束条件的周长为$Q_i$的栅栏，由于数量可能很大，结果请对$998244353$取模，每个输出占一行

## 说明/提示

对于第一个样例，可能的长度序列有（红板加粗）

·周长为$6$：$[$**2**$]$

·周长为$8$：$[1,$ **2**$]$,$[$**2**$,1]$

·周长为$10$：$[1,$ **2**$,1]$,$[$**4**$]$

·周长为$12$：$[1,$ **4**$]$,$[3,$ **4**$]$,$[$**4**$,1]$,$[$**4**$,3]$

·周长为$14$：$[1,$ **4**$,1]$,$[1,$ **4**$,3]$,$[3,$ **4**$,1]$,$[3,$ **4**$,3]$,$[1,3,$ **4**$]$,$[$**4**$,3,1]$

·周长为$16$：$[1,$ **4**$,3,1]$,$[3,$ **4**$,3,1]$,$[1,3,$ **4**$,1]$,$[1,3,$ **4**$,3]$

·周长为$18$：$[1,3,$ **4**$,3,1]$

## 样例 #1

### 输入

```
5 2
3 3 1 1 1
2 4
7
6 8 10 12 14 16 18

```

### 输出

```
1
2
2
4
6
4
1

```

## 样例 #2

### 输入

```
5 5
1 2 3 4 5
1 2 3 4 5
4
4 8 10 14

```

### 输出

```
1
3
5
20

```



---

---
title: "Centroid Probabilities"
layout: "post"
diff: 省选/NOI-
pid: CF1667E
tag: ['动态规划 DP', '快速傅里叶变换 FFT']
---

# Centroid Probabilities

## 题目描述

Consider every tree (connected undirected acyclic graph) with $ n $ vertices ( $ n $ is odd, vertices numbered from $ 1 $ to $ n $ ), and for each $ 2 \le i \le n $ the $ i $ -th vertex is adjacent to exactly one vertex with a smaller index.

For each $ i $ ( $ 1 \le i \le n $ ) calculate the number of trees for which the $ i $ -th vertex will be the centroid. The answer can be huge, output it modulo $ 998\,244\,353 $ .

A vertex is called a centroid if its removal splits the tree into subtrees with at most $ (n-1)/2 $ vertices each.

## 输入格式

The first line contains an odd integer $ n $ ( $ 3 \le n < 2 \cdot 10^5 $ , $ n $ is odd) — the number of the vertices in the tree.

## 输出格式

Print $ n $ integers in a single line, the $ i $ -th integer is the answer for the $ i $ -th vertex (modulo $ 998\,244\,353 $ ).

## 说明/提示

Example $ 1 $ : there are two possible trees: with edges $ (1-2) $ , and $ (1-3) $ — here the centroid is $ 1 $ ; and with edges $ (1-2) $ , and $ (2-3) $ — here the centroid is $ 2 $ . So the answer is $ 1, 1, 0 $ .

Example $ 2 $ : there are $ 24 $ possible trees, for example with edges $ (1-2) $ , $ (2-3) $ , $ (3-4) $ , and $ (4-5) $ . Here the centroid is $ 3 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
1 1 0
```

## 样例 #2

### 输入

```
5
```

### 输出

```
10 10 4 0 0
```

## 样例 #3

### 输入

```
7
```

### 输出

```
276 276 132 36 0 0 0
```



---

---
title: "Multiset of Strings"
layout: "post"
diff: 省选/NOI-
pid: CF1709F
tag: ['树形 DP', '快速傅里叶变换 FFT']
---

# Multiset of Strings

## 题目描述

You are given three integers $ n $ , $ k $ and $ f $ .

Consider all binary strings (i. e. all strings consisting of characters $ 0 $ and/or $ 1 $ ) of length from $ 1 $ to $ n $ . For every such string $ s $ , you need to choose an integer $ c_s $ from $ 0 $ to $ k $ .

A multiset of binary strings of length exactly $ n $ is considered beautiful if for every binary string $ s $ with length from $ 1 $ to $ n $ , the number of strings in the multiset such that $ s $ is their prefix is not exceeding $ c_s $ .

For example, let $ n = 2 $ , $ c_{0} = 3 $ , $ c_{00} = 1 $ , $ c_{01} = 2 $ , $ c_{1} = 1 $ , $ c_{10} = 2 $ , and $ c_{11} = 3 $ . The multiset of strings $ \{11, 01, 00, 01\} $ is beautiful, since:

- for the string $ 0 $ , there are $ 3 $ strings in the multiset such that $ 0 $ is their prefix, and $ 3 \le c_0 $ ;
- for the string $ 00 $ , there is one string in the multiset such that $ 00 $ is its prefix, and $ 1 \le c_{00} $ ;
- for the string $ 01 $ , there are $ 2 $ strings in the multiset such that $ 01 $ is their prefix, and $ 2 \le c_{01} $ ;
- for the string $ 1 $ , there is one string in the multiset such that $ 1 $ is its prefix, and $ 1 \le c_1 $ ;
- for the string $ 10 $ , there are $ 0 $ strings in the multiset such that $ 10 $ is their prefix, and $ 0 \le c_{10} $ ;
- for the string $ 11 $ , there is one string in the multiset such that $ 11 $ is its prefix, and $ 1 \le c_{11} $ .

Now, for the problem itself. You have to calculate the number of ways to choose the integer $ c_s $ for every binary string $ s $ of length from $ 1 $ to $ n $ in such a way that the maximum possible size of a beautiful multiset is exactly $ f $ .

## 输入格式

The only line of input contains three integers $ n $ , $ k $ and $ f $ ( $ 1 \le n \le 15 $ ; $ 1 \le k, f \le 2 \cdot 10^5 $ ).

## 输出格式

Print one integer — the number of ways to choose the integer $ c_s $ for every binary string $ s $ of length from $ 1 $ to $ n $ in such a way that the maximum possible size of a beautiful multiset is exactly $ f $ . Since it can be huge, print it modulo $ 998244353 $ .

## 说明/提示

In the first example, the three ways to choose the integers $ c_s $ are:

- $ c_0 = 0 $ , $ c_1 = 2 $ , then the maximum beautiful multiset is $ \{1, 1\} $ ;
- $ c_0 = 1 $ , $ c_1 = 1 $ , then the maximum beautiful multiset is $ \{0, 1\} $ ;
- $ c_0 = 2 $ , $ c_1 = 0 $ , then the maximum beautiful multiset is $ \{0, 0\} $ .

## 样例 #1

### 输入

```
1 42 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 37 13
```

### 输出

```
36871576
```

## 样例 #3

### 输入

```
4 1252 325
```

### 输出

```
861735572
```

## 样例 #4

### 输入

```
6 153 23699
```

### 输出

```
0
```

## 样例 #5

### 输入

```
15 200000 198756
```

### 输出

```
612404746
```



---

---
title: "Wooden Spoon"
layout: "post"
diff: 省选/NOI-
pid: CF1784D
tag: ['数学', '组合数学', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---

# Wooden Spoon

## 题目描述

$ 2^n $ people, numbered with distinct integers from $ 1 $ to $ 2^n $ , are playing in a single elimination tournament. The bracket of the tournament is a full binary tree of height $ n $ with $ 2^n $ leaves.

When two players meet each other in a match, a player with the smaller number always wins. The winner of the tournament is the player who wins all $ n $ their matches.

A virtual consolation prize "Wooden Spoon" is awarded to a player who satisfies the following $ n $ conditions:

- they lost their first match;
- the player who beat them lost their second match;
- the player who beat that player lost their third match;
- $ \ldots $ ;
- the player who beat the player from the previous condition lost the final match of the tournament.

It can be shown that there is always exactly one player who satisfies these conditions.

Consider all possible $ (2^n)! $ arrangements of players into the tournament bracket. For each player, find the number of these arrangements in which they will be awarded the "Wooden Spoon", and print these numbers modulo $ 998\,244\,353 $ .

## 输入格式

The only line contains a single integer $ n $ ( $ 1 \le n \le 20 $ ) — the size of the tournament.

There are $ 20 $ tests in the problem: in the first test, $ n = 1 $ ; in the second test, $ n = 2 $ ; $ \ldots $ ; in the $ 20 $ -th test, $ n = 20 $ .

## 输出格式

Print $ 2^n $ integers — the number of arrangements in which the "Wooden Spoon" is awarded to players $ 1, 2, \ldots, 2^n $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the "Wooden Spoon" is always awarded to player $ 2 $ .

In the second example, there are $ 8 $ arrangements where players $ 1 $ and $ 4 $ meet each other in the first match, and in these cases, the "Wooden Spoon" is awarded to player $ 3 $ . In the remaining $ 16 $ arrangements, the "Wooden Spoon" is awarded to player $ 4 $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
0
2
```

## 样例 #2

### 输入

```
2
```

### 输出

```
0
0
8
16
```

## 样例 #3

### 输入

```
3
```

### 输出

```
0
0
0
1536
4224
7680
11520
15360
```



---

---
title: "Fuzzy Search"
layout: "post"
diff: 省选/NOI-
pid: CF528D
tag: ['快速傅里叶变换 FFT']
---

# Fuzzy Search

## 题目描述

给出一个门限值 $k$ 和两个只包含 $\texttt{AGCT}$ 四种字符的基因串 $S$ 和 $T$。现在你要找出在下列规则中 $T$ 在 $S$ 中出现了几次。 

$T$ 在 $S$ 的第 $i$ 个位置中出现，当且仅当把 $T$ 的首字符和 $S$ 的第 $i$ 个字符对齐后，$T$ 中的每一个字符能够在 $S$ 中找到一个位置偏差不超过 $k$ 的相同字符。

即对于所有的 $j \in[1,|T|]$，都存在一个 $p \in [1,|S|]$ 使得 $|(i+j-1)-p| \leq k$ 且 $S_p=T_j$ 。 

例如 $k=1$ 时，$\texttt{ACAT}$ 出现在 $\texttt{AGCAATTCAT}$ 的 $2$ 号， $3$ 号和 $6$ 号位置。 (编号从 $1$ 开始。)

## 输入格式

第一行有三个整数 $n$ , $m$ , $k$ ，表示 $S$ 的长度， $T$ 的长度和"门限值"。 

第二行给出基因串$S$，第三行给出基因串$T$，且两个串都只包含大写字母$\texttt{ATGC}$ 。

 $1≤n≤m≤2*10^5\ ,\ 0≤k≤2*10^5$

## 输出格式

输出一个整数，表示 $T$ 在 $S$ 中出现的次数。

## 样例 #1

### 输入

```
10 4 1
AGCAATTCAT
ACAT

```

### 输出

```
3

```



---

---
title: "Nikita and Order Statistics"
layout: "post"
diff: 省选/NOI-
pid: CF993E
tag: ['快速傅里叶变换 FFT', '构造']
---

# Nikita and Order Statistics

## 题目描述

Nikita likes tasks on order statistics, for example, he can easily find the $ k $ -th number in increasing order on a segment of an array. But now Nikita wonders how many segments of an array there are such that a given number $ x $ is the $ k $ -th number in increasing order on this segment. In other words, you should find the number of segments of a given array such that there are exactly $ k $ numbers of this segment which are less than $ x $ .

Nikita wants to get answer for this question for each $ k $ from $ 0 $ to $ n $ , where $ n $ is the size of the array.

## 输入格式

The first line contains two integers $ n $ and $ x $ $ (1 \le n \le 2 \cdot 10^5, -10^9 \le x \le 10^9) $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ $ (-10^9 \le a_i \le 10^9) $ — the given array.

## 输出格式

Print $ n+1 $ integers, where the $ i $ -th number is the answer for Nikita's question for $ k=i-1 $ .

## 样例 #1

### 输入

```
5 3
1 2 3 4 5

```

### 输出

```
6 5 4 0 0 0 
```

## 样例 #2

### 输入

```
2 6
-5 9

```

### 输出

```
1 2 0 
```

## 样例 #3

### 输入

```
6 99
-1 -1 -1 -1 -1 -1

```

### 输出

```
0 6 5 4 3 2 1 
```



---

