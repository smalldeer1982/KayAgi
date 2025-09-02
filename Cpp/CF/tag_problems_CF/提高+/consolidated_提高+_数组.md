---
title: "Ball"
layout: "post"
diff: 提高+/省选-
pid: CF12D
tag: ['树状数组', '排序']
---

# Ball

## 题目描述

 $ N $ ladies attend the ball in the King's palace. Every lady can be described with three values: beauty, intellect and richness. King's Master of Ceremonies knows that ladies are very special creatures. If some lady understands that there is other lady at the ball which is more beautiful, smarter and more rich, she can jump out of the window. He knows values of all ladies and wants to find out how many probable self-murderers will be on the ball. Lets denote beauty of the $ i $ -th lady by $ B_{i} $ , her intellect by $ I_{i} $ and her richness by $ R_{i} $ . Then $ i $ -th lady is a probable self-murderer if there is some $ j $ -th lady that $ B_{i}<B_{j},I_{i}<I_{j},R_{i}<R_{j} $ . Find the number of probable self-murderers.

## 输入格式

The first line contains one integer $ N $ ( $ 1<=N<=500000 $ ). The second line contains $ N $ integer numbers $ B_{i} $ , separated by single spaces. The third and the fourth lines contain sequences $ I_{i} $ and $ R_{i} $ in the same format. It is guaranteed that $ 0<=B_{i},I_{i},R_{i}<=10^{9} $ .

## 输出格式

Output the answer to the problem.

## 样例 #1

### 输入

```
3
1 4 2
4 3 2
2 5 3

```

### 输出

```
1

```



---

---
title: "Optimal Partition"
layout: "post"
diff: 提高+/省选-
pid: CF1667B
tag: ['动态规划 DP', '树状数组']
---

# Optimal Partition

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You should divide $ a $ into continuous non-empty subarrays (there are $ 2^{n-1} $ ways to do that).

Let $ s=a_l+a_{l+1}+\ldots+a_r $ . The value of a subarray $ a_l, a_{l+1}, \ldots, a_r $ is:

- $ (r-l+1) $ if $ s>0 $ ,
- $ 0 $ if $ s=0 $ ,
- $ -(r-l+1) $ if $ s<0 $ .

 What is the maximum sum of values you can get with a partition?

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 5 \cdot 10^5 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5 \cdot 10^5 $ ).

The second line of each test case contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ ( $ -10^9 \le a_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case print a single integer — the maximum sum of values you can get with an optimal parition.

## 说明/提示

Test case $ 1 $ : one optimal partition is $ [1, 2] $ , $ [-3] $ . $ 1+2>0 $ so the value of $ [1, 2] $ is $ 2 $ . $ -3<0 $ , so the value of $ [-3] $ is $ -1 $ . $ 2+(-1)=1 $ .

Test case $ 2 $ : the optimal partition is $ [0, -2, 3] $ , $ [-4] $ , and the sum of values is $ 3+(-1)=2 $ .

## 样例 #1

### 输入

```
5
3
1 2 -3
4
0 -2 3 -4
5
-1 -2 3 -1 -1
6
-1 2 -3 4 -5 6
7
1 -1 -1 1 -1 -1 1
```

### 输出

```
1
2
1
6
-1
```



---

---
title: "Bracket Cost"
layout: "post"
diff: 提高+/省选-
pid: CF1750E
tag: ['线段树', '树状数组']
---

# Bracket Cost

## 题目描述

Daemon Targaryen decided to stop looking like a Metin2 character. He turned himself into the most beautiful thing, a bracket sequence.

For a bracket sequence, we can do two kind of operations:

- Select one of its substrings $ ^\dagger $ and cyclic shift it to the right. For example, after a cyclic shift to the right, "(())" will become ")(()";
- Insert any bracket, opening '(' or closing ')', wherever you want in the sequence.

We define the cost of a bracket sequence as the minimum number of such operations to make it balanced $ ^\ddagger $ .

Given a bracket sequence $ s $ of length $ n $ , find the sum of costs across all its $ \frac{n(n+1)}{2} $ non-empty substrings. Note that for each substring we calculate the cost independently.

 $ ^\dagger $ A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

 $ ^\ddagger $ A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters $ + $ and $ 1 $ . For example, sequences "(())()", "()", and "(()(()))" are balanced, while ")(", "(()", and "(()))(" are not.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the bracket sequence.

The second line of each test case contains a string $ s $ , consisting only of characters '(' and ')', of length $ n $ — the bracket sequence.

It is guaranteed that sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the sum of costs of all substrings of $ s $ .

## 说明/提示

In the first test case, there is the only substring ")". Its cost is $ 1 $ because we can insert '(' to the beginning of this substring and get a string "()", that is a balanced string.

In the second test case, the cost of each substring of length one is $ 1 $ . The cost of a substring ")(" is $ 1 $ because we can cyclically shift it to right and get a string "()". The cost of strings ")()" and "()(" is $ 1 $ because its enough to insert one bracket to each of them. The cost of substring ")()(" is $ 1 $ because we can cyclically shift it to right and get a string "()()". So there are $ 4 + 2 + 2 + 1 = 9 $ substring of cost $ 1 $ and $ 1 $ substring of cost $ 0 $ . So the sum of the costs is $ 9 $ .

In the third test case,

- "(", the cost is $ 1 $ ;
- "()", the cost is $ 0 $ ;
- "())", the cost is $ 1 $ ;
- ")", the cost is $ 1 $ ;
- "))", the cost is $ 2 $ ;
- ")", the cost is $ 1 $ .

So the sum of the costs is $ 6 $ .

## 样例 #1

### 输入

```
5
1
)
4
)()(
3
())
5
(((((
10
)(())))())
```

### 输出

```
1
9
6
35
112
```



---

---
title: "Game of the Year"
layout: "post"
diff: 提高+/省选-
pid: CF1783E
tag: ['数学', '贪心', '树状数组', '数论', '前缀和', 'ST 表']
---

# Game of the Year

## 题目描述

Monocarp 和 Polycarp 正在玩电脑游戏。游戏特点：$ n $ 个编号从 $ 1 $ 到 $ n $ 的BOSS。

他俩将用以下方式与BOSS战斗

- Monocarp 进行 $ k $ 次尝试撒掉boss;
- Polycarp 进行 $ k $ 次尝试撒掉boss;
- Monocarp 进行 $ k $ 次尝试撒掉boss;
- Polycarp 进行 $ k $ 次尝试撒掉boss;
- ...

Monocarp 在第 $ a_i $ 次尝试中撒掉了第 $ i $ 只BOSS。Polycarp 在第 $ b_i $ 次尝试中撒掉了第 $ i $ 只BOSS。其中一个人撒掉第 $ i $ 只BOSS后，他们就会尝试撒第 $ (i+1) $ 只BOSS。并且他们的尝试计数器都会清空。撒掉第 $ n $ 只BOSS后，游戏结束。

找到从$ 1 $ 到 $ n $所有的 $ k $ 值， 使得 Monocarp 可以杀死所有的BOSS。

## 输入格式

第一行输入一个整数 $ t $ ( $ 1 \le t \le 10^4 $ ) — 样例数。

每个样例第一行输入一个整数 $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — BOSS的数量。

每个样例第二行输入 $ n $ 个整数： $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ) — Monocarp 撒死每只BOSS的尝试次数。

每个样例第三行输入 $ n $ 个整数： $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le n $ ) — Polycarp 撒死每只BOSS的尝试次数。

所有测试样例的 $ n $ 之和不超过 $ 2 \cdot 10^5 $ .

## 输出格式

对于每个样例输出两行。第一行应该包含一个正整数 $ \mathit{cnt} $ — 从 $ 1 $ 到 $ n $ 使得 Monocarp 可以撒死所有BOSS的 $ k $ 的总数。第二行应该包含 $ \mathit{cnt} $ 个正整数 — 所有 $ k $ 的值。

## 说明/提示

考虑最后一组测试样例

使 $ k = 1 $。首先，Monocarp经过1次尝试撒死第一只BOSS。成功，因为 $ a_1 = 1 $。 然后，Monocarp进行一次尝试撒死第二只BOSS。不成功，因为 $ a_2 > 1 $。于是，Polycarp尝试了一下。也不成功，因为 $ b_2 > 1 $。然后Monocarp进行了另一次尝试。仍然不成功，因为 $ a_2 > 2 $。直到Polycarp 在第三次尝试撒掉了BOSS。Monocarp没能撒掉BOSS。因此，$ k = 1 $ 不是答案。

使 $ k = 2 $ . Monocarp仍然在他的第一次尝试中撒死了BOSS。然后，他进行了两次不成功的尝试未能撒死BOSS。然后，Polycarp进行了两次不成功的尝试。然后，Monocarp进行了两次尝试，并且在第四次尝试中撒掉了BOSS。撒掉第三只BOSS的方法也类似。首先，Monocarp进行两次不成功的尝试。然后，Polycarp进行两次不成功的尝试。然后，Monocarp还有两次尝试机会，但在这两次机会中第一次就撒死了BOSS，因为 $ a_3 = 3 $。 第四只BOSS也被Monocarp撒死。因此，$ k = 2 $ 是答案。

## 样例 #1

### 输入

```
3
3
1 1 1
2 3 1
1
1
1
4
1 4 3 2
3 3 4 1
```

### 输出

```
3
1 2 3 
1
1 
2
2 4
```



---

---
title: "Music Festival"
layout: "post"
diff: 提高+/省选-
pid: CF1801C
tag: ['动态规划 DP', '树状数组']
---

# Music Festival

## 题目描述

The boy Vitya loves to listen to music very much. He knows that $ n $ albums are due to be released this Friday, $ i $ -th of which contains $ k_i $ tracks. Of course, Vitya has already listened to all the tracks, and knows that in the $ i $ -th album, the coolness of the $ j $ -th track is equal to $ a_{i,j} $ .Vitya has a friend Masha, whom he really wants to invite to the festival, where his favorite bands perform. However, in order for a friend to agree, she must first evaluate the released novelties. Vitya knows that if Masha listens to a track that was cooler than all the previous ones, she will get 1 unit of impression. Unfortunately, albums can only be listened to in their entirety, without changing the songs in them in places.

Help Vitya find such an order of albums so that Masha's impression turns out to be as much as possible, and she definitely went to the festival with him.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer t ( $ 1 \le t \le 200\,000 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 200\,000 $ ) — number of albums.

The album descriptions follow. Each album description consists of two lines:

The first line contains a single integer $ k_i $ ( $ 1 \le k_i \le 200\,000 $ ) — the number of tracks in the $ i $ th album.

The following line contains $ k_i $ integers $ a_{i, 1},\ a_{i, 2},\ a_{i, 3},\ \ldots,\ a_{i, k_i} $ ( $ 1 \le a_{i,j} \le 200\,000 $ ) — the coolness of the tracks in the $ i $ album.

Denote for $ \sum k_i $ the sum of all $ k_i $ . It is guaranteed that $ \sum k_i \le 200\,000 $ .

## 输出格式

For each test case print the singular number — the maximum impression that Masha can get.

## 说明/提示

In the first test example, the optimal order is listening to the 4th, 2nd, 3rd and 1st albums.

In this case, Masha will listen to the tracks in the following order: 1; 7; 8, 6; 4, 9, 4, 6, 8 and will receive 4 units of impression.

In the second test example, you must first listen to the 1st, then the 4th, and in any order the 2nd and 3rd. In this case, Masha will get the maximum impression, and for every song in the 1st and 4th albums and nothing for the 2nd and 3rd.

## 样例 #1

### 输入

```
2
4
5
4 9 4 6 8
1
7
2
8 6
1
1
4
2
3 4
2
1 8
2
2 8
2
7 9
```

### 输出

```
4
4
```



---

---
title: "Permutation Sorting"
layout: "post"
diff: 提高+/省选-
pid: CF1896E
tag: ['树状数组', '排序']
---

# Permutation Sorting

## 题目描述

You are given a permutation $ ^\dagger $ $ a $ of size $ n $ . We call an index $ i $ good if $ a_i=i $ is satisfied. After each second, we rotate all indices that are not good to the right by one position. Formally,

- Let $ s_1,s_2,\ldots,s_k $ be the indices of $ a $ that are not good in increasing order. That is, $ s_j < s_{j+1} $ and if index $ i $ is not good, then there exists $ j $ such that $ s_j=i $ .
- For each $ i $ from $ 1 $ to $ k $ , we assign $ a_{s_{(i \% k+1)}} := a_{s_i} $ all at once.

For each $ i $ from $ 1 $ to $ n $ , find the first time that index $ i $ becomes good.

 $ ^\dagger $ A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the size of permutation $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the elements of permutation $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a single line containing $ n $ integers where the $ i $ -th integer represents the first time that index $ i $ becomes good.

## 说明/提示

In the first test case, $ 2 $ and $ 5 $ are already in the correct position so indices $ 2 $ and $ 5 $ become good at $ 0 $ second. After $ 1 $ second, a cyclic shift will be done with $ s=[1, 3, 4] $ , resulting in array $ a=[1, 2, 3, 4, 5] $ . Notice that indices $ 1 $ , $ 3 $ and $ 4 $ become good at $ 1 $ second.

In the second test case, $ 5 $ is already in the correct position, so index $ 5 $ becomes good at $ 0 $ second. After $ 1 $ second, a cyclic shift will be done with $ s=[1, 2, 3, 4, 6] $ , resulting in array $ a=[3, 2, 1, 4, 5, 6] $ . Notice that indices $ 2 $ , $ 4 $ and $ 6 $ become good at $ 1 $ second. After $ 2 $ seconds, a cyclic shift will be done with $ s=[1, 3] $ , resulting in array $ a=[1, 2, 3, 4, 5, 6] $ . Notice that indices $ 1 $ and $ 3 $ become good at $ 2 $ second.

## 样例 #1

### 输入

```
2
5
3 2 4 1 5
6
2 1 4 6 5 3
```

### 输出

```
1 0 1 1 0 
2 1 2 1 0 1
```



---

---
title: "Yet Another Inversions Problem"
layout: "post"
diff: 提高+/省选-
pid: CF1917D
tag: ['树状数组']
---

# Yet Another Inversions Problem

## 题目描述

You are given a permutation $ p_0, p_1, \ldots, p_{n-1} $ of odd integers from $ 1 $ to $ 2n-1 $ and a permutation $ q_0, q_1, \ldots, q_{k-1} $ of integers from $ 0 $ to $ k-1 $ .

An array $ a_0, a_1, \ldots, a_{nk-1} $ of length $ nk $ is defined as follows:

 $ a_{i \cdot k+j}=p_i \cdot 2^{q_j} $ for all $ 0 \le i < n $ and all $ 0 \le j < k $ For example, if $ p = [3, 5, 1] $ and $ q = [0, 1] $ , then $ a = [3, 6, 5, 10, 1, 2] $ .

Note that all arrays in the statement are zero-indexed. Note that each element of the array $ a $ is uniquely determined.

Find the number of inversions in the array $ a $ . Since this number can be very large, you should find only its remainder modulo $ 998\,244\,353 $ .

An inversion in array $ a $ is a pair $ (i, j) $ ( $ 0 \le i < j < nk $ ) such that $ a_i > a_j $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 2 \cdot 10^5 $ ) — the lengths of arrays $ p $ and $ q $ .

The second line of each test case contains $ n $ distinct integers $ p_0, p_1, \ldots, p_{n-1} $ ( $ 1 \le p_i \le 2n-1 $ , $ p_i $ is odd) — the array $ p $ .

The third line of each test case contains $ k $ distinct integers $ q_0, q_1, \ldots, q_{k-1} $ ( $ 0 \le q_i < k $ ) — the array $ q $ .

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ and the sum of $ k $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output one integer: the number of inversions in array $ a $ modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, array $ a $ is equal to $ [3, 6, 5, 10, 1, 2] $ . There are $ 9 $ inversions in it: $ (0, 4) $ , $ (0, 5) $ , $ (1, 2) $ , $ (1, 4) $ , $ (1, 5) $ , $ (2, 4) $ , $ (2, 5) $ , $ (3, 4) $ , $ (3, 5) $ . Note that these are pairs $ (i, j) $ such that $ i < j $ and $ a_i > a_j $ .

In the second test case, array $ a $ is equal to $ [8, 4, 1, 2, 24, 12, 3, 6, 40, 20, 5, 10] $ . There are $ 25 $ inversions in it.

In the third test case, array $ a $ is equal to $ [1, 2, 4, 8, 16] $ . There are no inversions in it.

## 样例 #1

### 输入

```
4
3 2
3 5 1
0 1
3 4
1 3 5
3 2 0 1
1 5
1
0 1 2 3 4
8 3
5 1 7 11 15 3 9 13
2 0 1
```

### 输出

```
9
25
0
104
```



---

---
title: "Space Harbour"
layout: "post"
diff: 提高+/省选-
pid: CF1924B
tag: ['线段树', '树状数组']
---

# Space Harbour

## 题目描述

There are $ n $ points numbered $ 1 $ to $ n $ on a straight line. Initially, there are $ m $ harbours. The $ i $ -th harbour is at point $ X_i $ and has a value $ V_i $ . It is guaranteed that there are harbours at the points $ 1 $ and $ n $ . There is exactly one ship on each of the $ n $ points. The cost of moving a ship from its current location to the next harbour is the product of the value of the nearest harbour to its left and the distance from the nearest harbour to its right. Specifically, if a ship is already at a harbour, the cost of moving it to the next harbour is $ 0 $ .

Additionally, there are $ q $ queries, each of which is either of the following $ 2 $ types:

- $ 1 $ $ x $ $ v $ — Add a harbour at point $ x $ with value $ v $ . It is guaranteed that before adding the harbour, there is no harbour at point $ x $ .
- $ 2 $ $ l $ $ r $ — Print the sum of the cost of moving all ships at points from $ l $ to $ r $ to their next harbours. Note that you just need to calculate the cost of moving the ships but not actually move them.

## 输入格式

The first line contains three integers $ n $ , $ m $ , and $ q $ ( $ 2 \le m \le n \le 3 \cdot 10^5 $ , $ 1 \le q \le 3 \cdot 10^5 $ ) — the number of points, harbours, and queries, respectively.

The second line contains $ m $ distinct integers $ X_1, X_2, \ldots, X_m(1 \le X_i \le n) $ — the position at which the $ i $ -th harbour is located.

The third line contains $ m $ integers $ V_1, V_2, \ldots, V_m(1 \le V_i \le 10^7) $ — the value of the $ i $ -th harbour.

Each of the next $ q $ lines contains three integers. The first integer is $ t $ ( $ 1\le t \le 2 $ ) — type of query. If $ t=1 $ , then the next two integers are $ x $ and $ v $ ( $ 2 \le x \le n - 1 $ , $ 1 \le v \le 10^7 $ ) — first-type query. If $ t=2 $ , then the next two integers are $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ) — second-type query.

It is guaranteed that there is at least one second-type query.

## 输出格式

For every second-type query, print one integer in a new line — answer to this query.

## 说明/提示

For the first type $ 2 $ query, the cost for ships at positions $ 2 $ , $ 3 $ , $ 4 $ and $ 5 $ are $ 3(3 \times 1) $ , $ 0 $ , $ 96(24 \times 4) $ and $ 72(24 \times 3) $ respectively.

For the second type $ 2 $ query, since the ship at position $ 5 $ is already at a harbour, so the cost is $ 0 $ .

For the third type $ 2 $ query, the cost for ships at position $ 7 $ and $ 8 $ are $ 15(15 \times 1) $ and $ 0 $ respectively.

## 样例 #1

### 输入

```
8 3 4
1 3 8
3 24 10
2 2 5
1 5 15
2 5 5
2 7 8
```

### 输出

```
171
0
15
```



---

---
title: "Division + LCP (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF1968G2
tag: ['后缀数组 SA']
---

# Division + LCP (hard version)

## 题目描述

This is the hard version of the problem. In this version $ l\le r $ .

You are given a string $ s $ . For a fixed $ k $ , consider a division of $ s $ into exactly $ k $ continuous substrings $ w_1,\dots,w_k $ . Let $ f_k $ be the maximal possible $ LCP(w_1,\dots,w_k) $ among all divisions.

 $ LCP(w_1,\dots,w_m) $ is the length of the Longest Common Prefix of the strings $ w_1,\dots,w_m $ .

For example, if $ s=abababcab $ and $ k=4 $ , a possible division is $ \color{red}{ab}\color{blue}{ab}\color{orange}{abc}\color{green}{ab} $ . The $ LCP(\color{red}{ab},\color{blue}{ab},\color{orange}{abc},\color{green}{ab}) $ is $ 2 $ , since $ ab $ is the Longest Common Prefix of those four strings. Note that each substring consists of a continuous segment of characters and each character belongs to exactly one substring.

Your task is to find $ f_l,f_{l+1},\dots,f_r $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ , $ l $ , $ r $ ( $ 1 \le l \le r \le n \le 2 \cdot 10^5 $ ) — the length of the string and the given range.

The second line of each test case contains string $ s $ of length $ n $ , all characters are lowercase English letters.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output $ r-l+1 $ values: $ f_l,\dots,f_r $ .

## 样例 #1

### 输入

```
7
3 1 3
aba
3 2 3
aaa
7 1 5
abacaba
9 1 6
abababcab
10 1 10
aaaaaaawac
9 1 9
abafababa
7 2 7
vvzvvvv
```

### 输出

```
3 1 0 
1 1 
7 3 1 1 0 
9 2 2 2 0 0 
10 3 2 1 1 1 1 1 0 0 
9 3 2 1 1 0 0 0 0 
2 2 1 1 1 0
```



---

---
title: "Level Up"
layout: "post"
diff: 提高+/省选-
pid: CF1997E
tag: ['线段树', '二分', '树状数组']
---

# Level Up

## 题目描述

Monocarp正在玩一款电脑游戏。他从等级 $ 1 $ 开始。他将依次与 $ n $ 只怪物战斗，这些怪物的等级从 $ 1 $ 到 $ n $ 不等。

对于按顺序给出的每个怪物，Monocarp的遭遇如下：

- 如果Monocarp的等级高于怪物的等级，则怪物会逃跑；
- 否则，Monocarp会与怪物战斗。

在每与第 $ k $ 个怪物战斗（逃跑的怪物不计算在内）后，Monocarp的等级会增加 $ 1 $ 。因此，他在与 $ k $ 个怪物战斗后等级变为 $ 2 $ ，在与 $ 2k $ 个怪物战斗后等级变为 $ 3 $ ，以此类推。

你需要处理 $ q $ 个查询，每个查询的格式如下：

- $ i~x $ ：如果参数 $ k $ 等于 $ x $ ，Monocarp是否会与第 $ i $ 个怪物战斗？

## 输入格式

第一行包含两个整数 $ n $ 和 $ q $ （ $ 1 \le n, q \le 2 \cdot 10^5 $ ） — 怪物的数量和查询的数量。

第二行包含 $ n $ 个整数 $ a_1, a_2, \dots, a_n $ （ $ 1 \le a_i \le 2 \cdot 10^5 $ ） — 每个怪物的等级。

接下来的 $ q $ 行，每行包含两个整数 $ i $ 和 $ x $ （ $ 1 \le i, x \le n $ ） — 查询中指定的怪物索引和需要升级的战斗次数。

## 输出格式

对于每个查询，如果Monocarp会与第 $ i $ 个怪物战斗，则输出 "YES" ，否则输出 "NO" 。

## 样例 #1

### 输入

```
4 16
2 1 2 1
1 1
2 1
3 1
4 1
1 2
2 2
3 2
4 2
1 3
2 3
3 3
4 3
1 4
2 4
3 4
4 4
```

### 输出

```
YES
NO
YES
NO
YES
YES
YES
NO
YES
YES
YES
NO
YES
YES
YES
YES
```

## 样例 #2

### 输入

```
7 15
1 1 2 1 1 1 1
5 3
2 2
2 2
1 6
5 1
5 5
7 7
3 5
7 4
4 3
2 5
1 2
5 6
4 1
6 1
```

### 输出

```
NO
YES
YES
YES
NO
YES
YES
YES
NO
NO
YES
YES
YES
NO
NO
```



---

---
title: "Microwavable Subsequence"
layout: "post"
diff: 提高+/省选-
pid: CF2045I
tag: ['树状数组', '扫描线']
---

# Microwavable Subsequence

## 题目描述

给定一个整数数组 $[A_1, A_2, \dots, A_N]$，数组长度为 $N$。

从数组中移除零个或多个元素，并保持剩余元素的顺序不变，就可以得到一个子序列。例如，$[2, 1, 2]$、$[3, 3]$、$[1]$ 和 $[3, 2, 1, 3, 2]$ 都是数组 $[3, 2, 1, 3, 2]$ 的子序列，而 $[1, 2, 3]$ 不是。

如果某个子序列最多只包含两种不同的数，并且相邻元素不相同，则称为“微波炉”子序列。例如，$[2, 1, 2]$、$[3, 2, 3, 2]$ 以及 $[1]$ 是微波炉子序列，而 $[3, 3]$ 和 $[3, 2, 1, 3, 2]$ 则不是。

函数 $f(x, y)$ 表示数组 $A$ 中元素仅为 $x$ 或 $y$ 的最长微波炉子序列的长度。请计算所有满足 $1 \leq x < y \leq M$ 的 $f(x, y)$ 之和。

## 输入格式

第一行输入两个整数 $N$ 和 $M$，满足 $1 \leq N, M \leq 300,000$。

第二行包含 $N$ 个整数 $A_i$，其中 $1 \leq A_i \leq M$。

## 输出格式

输出一个整数，即所有满足 $1 \leq x < y \leq M$ 的 $f(x, y)$ 的总和。

## 说明/提示

### 样例解释 1

$f(1, 2)$ 的值为 $3$，可以从序列中去掉 $A_1$ 和 $A_4$，得到子序列 $[2, 1, 2]$。$f(1, 3)$ 的值为 $3$，通过去除 $A_2$ 和 $A_5$，得到子序列 $[3, 1, 3]$。$f(2, 3)$ 的值为 $4$，从序列中去除 $A_3$，得到子序列 $[3, 2, 3, 2]$。而 $f(1, 4)$、$f(2, 4)$ 和 $f(3, 4)$ 的值均为 $1$。

### 样例解释 2

$f(1, 2)$ 和 $f(1, 3)$ 的值均为 $1$，而 $f(2, 3)$ 的值是 $0$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5 4
3 2 1 3 2
```

### 输出

```
13
```

## 样例 #2

### 输入

```
3 3
1 1 1
```

### 输出

```
2
```



---

---
title: "Adventurers"
layout: "post"
diff: 提高+/省选-
pid: CF2046C
tag: ['线段树', '二分', '树状数组', '扫描线']
---

# Adventurers

## 题目描述

Once, four Roman merchants met in a Roman mansion to discuss their trading plans. They faced the following problem: they traded the same type of goods, and if they traded in the same city, they would inevitably incur losses. They decided to divide up the cities between them where they would trade.

The map of Rome can be represented in this problem as a plane with certain points marked — the cities of the Roman Empire.

The merchants decided to choose a certain dividing point $ (x_0, y_0) $ . Then, in a city with coordinates $ (x_i, y_i) $ ,

- the first merchant sells goods if $ x_0 \le x_i $ and $ y_0 \le y_i $ ;
- the second merchant sells goods if $ x_0 > x_i $ and $ y_0 \le y_i $ ;
- the third merchant sells goods if $ x_0 \le x_i $ and $ y_0 > y_i $ ;
- the fourth merchant sells goods if $ x_0 > x_i $ and $ y_0 > y_i $ .

The merchants want to choose $ (x_0, y_0) $ in such a way as to maximize the smallest number of cities that any of them gets (i. e., as fair as possible). Please find such a point for them.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 4 \le n \le 10^5 $ ) — the number of cities on the map.

Each of the next $ n $ lines contains two integers $ x_i, y_i $ ( $ -10^9 \le x_i, y_i \le 10^9 $ ) — the coordinates of the cities.

Note that some points may coincide. This is because some cities may be so close that they cannot be distinguished on the map at the given scale.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, in the first line, print a single integer $ k $ ( $ 0 \le k \le \frac{n}{4} $ ) — the maximum possible number of cities that each merchant can get at a minimum.

In the second line, print two integers $ x_0 $ and $ y_0 $ ( $ |x_0|, |y_0| \le 10^9 $ ) — the coordinates of the dividing point. If there are multiple suitable points, print any of them.

## 样例 #1

### 输入

```
4
4
1 1
1 2
2 1
2 2
4
0 0
0 0
0 0
0 0
8
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1
-2 1
-1 2
7
1 1
1 2
1 3
1 4
2 1
3 1
4 1
```

### 输出

```
1
2 2
0
0 0
2
1 0
0
0 0
```



---

---
title: "Bro Thinks He's Him"
layout: "post"
diff: 提高+/省选-
pid: CF2065H
tag: ['动态规划 DP', '线段树', '树状数组', '矩阵加速', '前缀和']
---

# Bro Thinks He's Him

## 题目描述

Skibidus 自认为是"天选之人"！他通过解决这个难题证明了这一点。你也能证明自己吗？

给定一个二进制字符串 $^{\text{∗}}$ $t$，定义 $f(t)$ 为将 $t$ 分割成由相同字符组成的连续子串的最小数量。例如，$f(\texttt{00110001}) = 4$，因为 $t$ 可以被分割为 $\texttt{[00][11][000][1]}$，每个括号内的子串均由相同字符组成。

Skibidus 给你一个二进制字符串 $s$ 和 $q$ 次查询。每次查询会翻转字符串中的一个字符（即 $\texttt{0}$ 变为 $\texttt{1}$，$\texttt{1}$ 变为 $\texttt{0}$），且修改会保留到后续查询。每次查询后，你需要输出所有非空子序列 $^{\text{†}}$ $b$ 的 $f(b)$ 之和模 $998\,244\,353$ 的结果。

 $^{\text{∗}}$ 二进制字符串仅包含字符 $\texttt{0}$ 和 $\texttt{1}$。

 $^{\text{†}}$ 字符串的子序列是指通过删除原字符串中若干（可能为零）个字符得到的新字符串。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——测试用例数量。

每个测试用例的第一行包含一个二进制字符串 $s$（$1 \leq |s| \leq 2 \cdot 10^5$）。

每个测试用例的第二行包含一个整数 $q$（$1 \leq q \leq 2 \cdot 10^5$）——查询次数。

每个测试用例的第三行包含 $q$ 个整数 $v_1, v_2, \ldots, v_q$（$1 \leq v_i \leq |s|$），表示第 $i$ 次查询翻转 $s_{v_i}$ 处的字符。

保证所有测试用例的 $|s|$ 之和与 $q$ 之和均不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，在一行中输出 $q$ 个整数——每次查询后的答案模 $998\,244\,353$。

## 说明/提示

第一个测试用例在第一次查询后，$s$ 变为 $\texttt{001}$。计算所有子序列的 $f$ 值：
- $f(s_1) = f(\texttt{0}) = 1$
- $f(s_2) = f(\texttt{0}) = 1$
- $f(s_3) = f(\texttt{1}) = 1$
- $f(s_1 s_2) = f(\texttt{00}) = 1$
- $f(s_1 s_3) = f(\texttt{01}) = 2$
- $f(s_2 s_3) = f(\texttt{01}) = 2$
- $f(s_1 s_2 s_3) = f(\texttt{001}) = 2$

这些值的总和为 $10$，模 $998\,244\,353$ 后结果为 $10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
101
2
1 3
10110
3
1 2 3
101110101
5
7 2 4 4 1
```

### 输出

```
10 7 
61 59 67 
1495 1169 1417 1169 1396
```



---

---
title: "Yaroslav and Divisors"
layout: "post"
diff: 提高+/省选-
pid: CF301D
tag: ['树状数组']
---

# Yaroslav and Divisors

## 题目描述

### 题意：
+ 给定一个由$n$个数组成的排列，每个数互不相同且数字不会超过$n$，你需要回答$m$个询问。
+ 询问包含两个整数$l$和$r$$(1<=l,r<=n)$。
+ 对于每个询问，查询有多少数对$i,j(l<=i,j<=r)$。使得$pi$与$pj$是倍数关系。

## 输入格式

+ 第一行输入两个数n,m$(1<=n,m<=2*10^{5})$,表示序列长度和询问个数
+ 第$2$行输入$n$个数代表这个排列。
+ 接下来输入$m$个数对$l, r$代表每一次询问

## 输出格式

+ 输出一个整数代表答案
### hint：
+ 建议阅读样例加深理解

## 样例 #1

### 输入

```
1 1
1
1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10 9
1 2 3 4 5 6 7 8 9 10
1 10
2 9
3 8
4 7
5 6
2 2
9 10
5 10
4 10

```

### 输出

```
27
14
8
4
2
1
2
7
9

```



---

---
title: "Mishka and Interesting sum"
layout: "post"
diff: 提高+/省选-
pid: CF703D
tag: ['线段树', '树状数组', '离散化']
---

# Mishka and Interesting sum

## 题目描述

Little Mishka enjoys programming. Since her birthday has just passed, her friends decided to present her with array of non-negative integers $ a_{1},a_{2},...,a_{n} $ of $ n $ elements!

Mishka loved the array and she instantly decided to determine its beauty value, but she is too little and can't process large arrays. Right because of that she invited you to visit her and asked you to process $ m $ queries.

Each query is processed in the following way:

1. Two integers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ) are specified — bounds of query segment.
2. Integers, presented in array segment $ [l,r] $ (in sequence of integers $ a_{l},a_{l+1},...,a_{r} $ ) even number of times, are written down.
3. XOR-sum of written down integers is calculated, and this value is the answer for a query. Formally, if integers written down in point 2 are $ x_{1},x_{2},...,x_{k} $ , then Mishka wants to know the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7210428d91e1c7505cfe57a2df3abdc28a7ac76c.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/4298d47c0191af3c0a3103f431751061bc7e2362.png) — operator of exclusive bitwise OR.

Since only the little bears know the definition of array beauty, all you are to do is to answer each of queries presented.

## 输入格式

The first line of the input contains single integer $ n $ ( $ 1<=n<=1000000 $ ) — the number of elements in the array.

The second line of the input contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — array elements.

The third line of the input contains single integer $ m $ ( $ 1<=m<=1000000 $ ) — the number of queries.

Each of the next $ m $ lines describes corresponding query by a pair of integers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ) — the bounds of query segment.

## 输出格式

Print $ m $ non-negative integers — the answers for the queries in the order they appear in the input.

## 说明/提示

In the second sample:

There is no integers in the segment of the first query, presented even number of times in the segment — the answer is $ 0 $ .

In the second query there is only integer $ 3 $ is presented even number of times — the answer is $ 3 $ .

In the third query only integer $ 1 $ is written down — the answer is $ 1 $ .

In the fourth query all array elements are considered. Only $ 1 $ and $ 2 $ are presented there even number of times. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/1f43581f72fc5ce3c0b862a8034cb76a29952125.png).

In the fifth query $ 1 $ and $ 3 $ are written down. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7a7518e2f6c019be104f1f3114e7d17043192b15.png).

## 样例 #1

### 输入

```
3
3 7 8
1
1 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
7
1 2 1 3 3 2 3
5
4 7
4 5
1 3
1 7
1 5

```

### 输出

```
0
3
1
3
2

```



---

---
title: "PolandBall and Polygon"
layout: "post"
diff: 提高+/省选-
pid: CF755D
tag: ['数学', '线段树', '树状数组']
---

# PolandBall and Polygon

## 题目描述

PolandBall has such a convex polygon with $ n $ veritces that no three of its diagonals intersect at the same point. PolandBall decided to improve it and draw some red segments.

He chose a number $ k $ such that $ gcd(n,k)=1 $ . Vertices of the polygon are numbered from $ 1 $ to $ n $ in a clockwise way. PolandBall repeats the following process $ n $ times, starting from the vertex $ 1 $ :

Assume you've ended last operation in vertex $ x $ (consider $ x=1 $ if it is the first operation). Draw a new segment from vertex $ x $ to $ k $ -th next vertex in clockwise direction. This is a vertex $ x+k $ or $ x+k-n $ depending on which of these is a valid index of polygon's vertex.

Your task is to calculate number of polygon's sections after each drawing. A section is a clear area inside the polygon bounded with drawn diagonals or the polygon's sides.

## 输入格式

There are only two numbers in the input: $ n $ and $ k $ ( $ 5<=n<=10^{6} $ , $ 2<=k<=n-2 $ , $ gcd(n,k)=1 $ ).

## 输出格式

You should print $ n $ values separated by spaces. The $ i $ -th value should represent number of polygon's sections after drawing first $ i $ lines.

## 说明/提示

The greatest common divisor (gcd) of two integers $ a $ and $ b $ is the largest positive integer that divides both $ a $ and $ b $ without a remainder.

For the first sample testcase, you should output "2 3 5 8 11". Pictures below correspond to situations after drawing lines.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/4990bd3c0c7dd5836fdcc579f970dcdca8dbd872.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/6451ef95db9646f275ba3ec79da2a8d5b0b028d0.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/da900464c60a214ba6c5242ba8fc65122871a490.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/a8b3c0780f20737fed12f744f83c0f1eab3d538f.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/c214010a205eb51e891b2376aacedcb09475410e.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF755D/ac2e2680dc9611afb331663a01c918e0c001e832.png)

## 样例 #1

### 输入

```
5 2

```

### 输出

```
2 3 5 8 11 
```

## 样例 #2

### 输入

```
10 3

```

### 输出

```
2 3 4 6 9 12 16 21 26 31 
```



---

---
title: "The Untended Antiquity"
layout: "post"
diff: 提高+/省选-
pid: CF869E
tag: ['树状数组', '进制', '差分']
---

# The Untended Antiquity

## 题目描述

Adieu l'ami.

Koyomi is helping Oshino, an acquaintance of his, to take care of an open space around the abandoned Eikou Cram School building, Oshino's makeshift residence.

The space is represented by a rectangular grid of $ n×m $ cells, arranged into $ n $ rows and $ m $ columns. The $ c $ -th cell in the $ r $ -th row is denoted by $ (r,c) $ .

Oshino places and removes barriers around rectangular areas of cells. Specifically, an action denoted by " $ 1\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means Oshino's placing barriers around a rectangle with two corners being $ (r_{1},c_{1}) $ and $ (r_{2},c_{2}) $ and sides parallel to squares sides. Similarly, " $ 2\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means Oshino's removing barriers around the rectangle. Oshino ensures that no barriers staying on the ground share any common points, nor do they intersect with boundaries of the $ n×m $ area.

Sometimes Koyomi tries to walk from one cell to another carefully without striding over barriers, in order to avoid damaging various items on the ground. " $ 3\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means that Koyomi tries to walk from $ (r_{1},c_{1}) $ to $ (r_{2},c_{2}) $ without crossing barriers.

And you're here to tell Koyomi the feasibility of each of his attempts.

## 输入格式

The first line of input contains three space-separated integers $ n $ , $ m $ and $ q $ ( $ 1<=n,m<=2500 $ , $ 1<=q<=100000 $ ) — the number of rows and columns in the grid, and the total number of Oshino and Koyomi's actions, respectively.

The following $ q $ lines each describes an action, containing five space-separated integers $ t $ , $ r_{1} $ , $ c_{1} $ , $ r_{2} $ , $ c_{2} $ ( $ 1<=t<=3 $ , $ 1<=r_{1},r_{2}<=n $ , $ 1<=c_{1},c_{2}<=m $ ) — the type and two coordinates of an action. Additionally, the following holds depending on the value of $ t $ :

- If $ t=1 $ : $ 2<=r_{1}<=r_{2}<=n-1 $ , $ 2<=c_{1}<=c_{2}<=m-1 $ ;
- If $ t=2 $ : $ 2<=r_{1}<=r_{2}<=n-1 $ , $ 2<=c_{1}<=c_{2}<=m-1 $ , the specified group of barriers exist on the ground before the removal.
- If $ t=3 $ : no extra restrictions.

## 输出格式

For each of Koyomi's attempts (actions with $ t=3 $ ), output one line — containing "Yes" (without quotes) if it's feasible, and "No" (without quotes) otherwise.

## 说明/提示

For the first example, the situations of Koyomi's actions are illustrated below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869E/5930e5689d91726564d05581955bbc9acf5a8c98.png)

## 样例 #1

### 输入

```
5 6 5
1 2 2 4 5
1 3 3 3 3
3 4 4 1 1
2 2 2 4 5
3 1 1 4 4

```

### 输出

```
No
Yes

```

## 样例 #2

### 输入

```
2500 2500 8
1 549 1279 1263 2189
1 303 795 1888 2432
1 2227 622 2418 1161
3 771 2492 1335 1433
1 2017 2100 2408 2160
3 48 60 798 729
1 347 708 1868 792
3 1940 2080 377 1546

```

### 输出

```
No
Yes
No

```



---

