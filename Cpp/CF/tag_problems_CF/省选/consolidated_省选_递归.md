---
title: "Points"
layout: "post"
diff: 省选/NOI-
pid: CF19D
tag: ['线段树', '递归', '离散化']
---

# Points

## 题目描述

Pete and Bob invented a new interesting game. Bob takes a sheet of paper and locates a Cartesian coordinate system on it as follows: point $ (0,0) $ is located in the bottom-left corner, $ Ox $ axis is directed right, $ Oy $ axis is directed up. Pete gives Bob requests of three types:

- add x y — on the sheet of paper Bob marks a point with coordinates $ (x,y) $ . For each request of this type it's guaranteed that point $ (x,y) $ is not yet marked on Bob's sheet at the time of the request.
- remove x y — on the sheet of paper Bob erases the previously marked point with coordinates $ (x,y) $ . For each request of this type it's guaranteed that point $ (x,y) $ is already marked on Bob's sheet at the time of the request.
- find x y — on the sheet of paper Bob finds all the marked points, lying strictly above and strictly to the right of point $ (x,y) $ . Among these points Bob chooses the leftmost one, if it is not unique, he chooses the bottommost one, and gives its coordinates to Pete.

Bob managed to answer the requests, when they were 10, 100 or 1000, but when their amount grew up to $ 2·10^{5} $ , Bob failed to cope. Now he needs a program that will answer all Pete's requests. Help Bob, please!

## 输入格式

The first input line contains number $ n $ ( $ 1<=n<=2·10^{5} $ ) — amount of requests. Then there follow $ n $ lines — descriptions of the requests. add x y describes the request to add a point, remove x y — the request to erase a point, find x y — the request to find the bottom-left point. All the coordinates in the input file are non-negative and don't exceed $ 10^{9} $ .

## 输出格式

For each request of type find x y output in a separate line the answer to it — coordinates of the bottommost among the leftmost marked points, lying strictly above and to the right of point $ (x,y) $ . If there are no points strictly above and to the right of point $ (x,y) $ , output -1.

## 样例 #1

### 输入

```
7
add 1 1
add 3 4
find 0 0
remove 1 1
find 0 0
add 1 1
find 0 0

```

### 输出

```
1 1
3 4
1 1

```

## 样例 #2

### 输入

```
13
add 5 5
add 5 6
add 5 7
add 6 5
add 6 6
add 6 7
add 7 5
add 7 6
add 7 7
find 6 6
remove 7 7
find 6 6
find 4 4

```

### 输出

```
7 7
-1
5 5

```



---

---
title: "Alien DNA"
layout: "post"
diff: 省选/NOI-
pid: CF217E
tag: ['字符串', '并查集', '递归']
---

# Alien DNA

## 题目描述

Professor Bajtocy is conducting experiments on alien DNA. He has discovered that it is subject to repetitive mutations — each mutation happens in the same way: some continuous subsequence of the alien DNA becomes active, copies itself, the copy gets mangled and inserts itself right after the original subsequence. The mangled copy of the activated continuous subsequence is formed by first joining all the elements at the even positions in that subsequence, and then joining all the elements at the odd ones at the end. That is, if the activated subsequence consists of 11 elements and represented as $ s_{1}s_{2}...\ s_{11} $ , its mangled copy is $ s_{2}s_{4}s_{6}s_{8}s_{10}s_{1}s_{3}s_{5}s_{7}s_{9}s_{11} $ .

For example, if the original sequence was "ACTGG" and the mutation happened on the segment $ [2,4] $ (that is the activated subsequence is "CTG"), the mutated DNA is: "ACTGTCGG". The mangled copy of the activated subsequence is marked with bold font.

Professor Bajtocy has written down the original DNA sequence and the mutations that sequentially happened to it, and he now asks you to recover the first $ k $ elements of the DNA sequence after all the mutations.

## 输入格式

The first line of input contains the original DNA sequence, consisting only of letters "A", "C", "T" and "G" and not exceeding $ 3·10^{6} $ in length.

The second line contains a single integer $ k $ ( $ 1<=k<=3·10^{6} $ ).

The third line contains a single integer $ n $ ( $ 0<=n<=5000 $ ) — the number of mutations. The next $ n $ lines describe the mutations in chronological order — each mutation is described by two numbers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=10^{9} $ ), meaning that the continuous subsequence $ [l_{i},r_{i}] $ has become active and cloned itself, joining itself with the mangled copy.

It is guaranteed that the input data is correct, that is, no mutation acts on non-existing elements of the DNA sequence, and the resulting DNA sequence has at least $ k $ elements.

Assume that the DNA elements are indexed starting from 1 and that the notation $ [l,r] $ meaning the continuous subsequence of DNA sequence that consists of $ r-l+1 $ elements starting at the $ l $ -th DNA sequence element and ending at the $ r $ -th DNA sequence element.

## 输出格式

Output a single line, containing the first $ k $ letters of the mutated DNA sequence.

## 说明/提示

In the second example, after the first mutation the sequence is "ACCAGTACGT". After the second mutation it's "ACCAGTACCGACATCGT".

## 样例 #1

### 输入

```
GAGA
4
0

```

### 输出

```
GAGA

```

## 样例 #2

### 输入

```
ACGTACGT
16
2
1 2
2 8

```

### 输出

```
ACCAGTACCGACATCG

```



---

---
title: "Power Tower"
layout: "post"
diff: 省选/NOI-
pid: CF906D
tag: ['递归', '标签462']
---

# Power Tower

## 题目描述

Priests of the Quetzalcoatl cult want to build a tower to represent a power of their god. Tower is usually made of power-charged rocks. It is built with the help of rare magic by levitating the current top of tower and adding rocks at its bottom. If top, which is built from $ k-1 $ rocks, possesses power $ p $ and we want to add the rock charged with power $ w_{k} $ then value of power of a new tower will be $ {w_{k}}^{p} $ .

Rocks are added from the last to the first. That is for sequence $ w_{1},...,w_{m} $ value of power will be

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF906D/a7b9adfbee151f2e3ef09f9dbad2cf6b657882ca.png)After tower is built, its power may be extremely large. But still priests want to get some information about it, namely they want to know a number called cumulative power which is the true value of power taken modulo $ m $ . Priests have $ n $ rocks numbered from $ 1 $ to $ n $ . They ask you to calculate which value of cumulative power will the tower possess if they will build it from rocks numbered $ l,l+1,...,r $ .

## 输入格式

First line of input contains two integers $ n $ ( $ 1<=n<=10^{5} $ ) and $ m $ ( $ 1<=m<=10^{9} $ ).

Second line of input contains $ n $ integers $ w_{k} $ ( $ 1<=w_{k}<=10^{9} $ ) which is the power of rocks that priests have.

Third line of input contains single integer $ q $ ( $ 1<=q<=10^{5} $ ) which is amount of queries from priests to you.

 $ k^{th} $ of next $ q $ lines contains two integers $ l_{k} $ and $ r_{k} $ ( $ 1<=l_{k}<=r_{k}<=n $ ).

## 输出格式

Output $ q $ integers. $ k $ -th of them must be the amount of cumulative power the tower will have if is built from rocks $ l_{k},l_{k}+1,...,r_{k} $ .

## 说明/提示

 $ 3^{27}=7625597484987 $

## 样例 #1

### 输入

```
6 1000000000
1 2 2 3 3 3
8
1 1
1 6
2 2
2 3
2 4
4 4
4 5
4 6

```

### 输出

```
1
1
2
4
256
3
27
597484987

```



---

---
title: "Short Code"
layout: "post"
diff: 省选/NOI-
pid: CF965E
tag: ['字符串', '贪心', '递归']
---

# Short Code

## 题目描述

Arkady's code contains $ n $ variables. Each variable has a unique name consisting of lowercase English letters only. One day Arkady decided to shorten his code.

He wants to replace each variable name with its non-empty prefix so that these new names are still unique (however, a new name of some variable can coincide with some old name of another or same variable). Among such possibilities he wants to find the way with the smallest possible total length of the new names.

A string $ a $ is a prefix of a string $ b $ if you can delete some (possibly none) characters from the end of $ b $ and obtain $ a $ .

Please find this minimum possible total length of new names.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of variables.

The next $ n $ lines contain variable names, one per line. Each name is non-empty and contains only lowercase English letters. The total length of these strings is not greater than $ 10^5 $ . The variable names are distinct.

## 输出格式

Print a single integer — the minimum possible total length of new variable names.

## 说明/提示

In the first example one of the best options is to shorten the names in the given order as "cod", "co", "c".

In the second example we can shorten the last name to "aac" and the first name to "a" without changing the other names.

## 样例 #1

### 输入

```
3
codeforces
codehorses
code

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5
abba
abb
ab
aa
aacada

```

### 输出

```
11

```

## 样例 #3

### 输入

```
3
telegram
digital
resistance

```

### 输出

```
3

```



---

