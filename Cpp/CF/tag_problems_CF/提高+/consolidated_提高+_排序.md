---
title: "MST Company"
layout: "post"
diff: 提高+/省选-
pid: CF125E
tag: ['贪心', '排序', '生成树']
---

# MST Company

## 题目描述

The MST (Meaningless State Team) company won another tender for an important state reform in Berland.

There are $ n $ cities in Berland, some pairs of the cities are connected by roads. Each road has its price. One can move along any road in any direction. The MST team should carry out the repair works on some set of roads such that one can get from any city to any other one moving only along the repaired roads. Moreover, this set should contain exactly $ k $ capital roads (that is, the roads that start or finish in the capital). The number of the capital is 1.

As the budget has already been approved, the MST Company will profit by finding the set with minimum lengths of roads.

## 输入格式

The first input line contains three integers $ n,m,k $ ( $ 1<=n<=5000;0<=m<=10^{5};0<=k&lt;5000 $ ), where $ n $ is the number of cities in the country, $ m $ is the number of roads in the country, $ k $ is the number of capital roads in the required set. Then $ m $ lines enumerate the roads in question. Each road is specified by three numbers $ a_{i},b_{i},w_{i} $ ( $ 1<=a_{i},b_{i}<=n $ ; $ 1<=w<=10^{5} $ ), where $ a_{i},b_{i} $ are the numbers of cities linked by a road and $ w_{i} $ is its length.

Between each pair of cities no more than one road exists. There are no roads that start and finish in one city. The capital's number is 1.

## 输出格式

In the first line print the number of roads in the required set. The second line should contain the numbers of roads included in the sought set. If the sought set does not exist, print -1.

## 样例 #1

### 输入

```
4 5 2
1 2 1
2 3 1
3 4 1
1 3 3
1 4 2

```

### 输出

```
3
1 5 2 
```



---

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
title: "Boring Segments"
layout: "post"
diff: 提高+/省选-
pid: CF1555E
tag: ['线段树', '排序', '双指针 two-pointer']
---

# Boring Segments

## 题目描述

You are given $ n $ segments on a number line, numbered from $ 1 $ to $ n $ . The $ i $ -th segments covers all integer points from $ l_i $ to $ r_i $ and has a value $ w_i $ .

You are asked to select a subset of these segments (possibly, all of them). Once the subset is selected, it's possible to travel between two integer points if there exists a selected segment that covers both of them. A subset is good if it's possible to reach point $ m $ starting from point $ 1 $ in arbitrary number of moves.

The cost of the subset is the difference between the maximum and the minimum values of segments in it. Find the minimum cost of a good subset.

In every test there exists at least one good subset.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 3 \cdot 10^5 $ ; $ 2 \le m \le 10^6 $ ) — the number of segments and the number of integer points.

Each of the next $ n $ lines contains three integers $ l_i $ , $ r_i $ and $ w_i $ ( $ 1 \le l_i < r_i \le m $ ; $ 1 \le w_i \le 10^6 $ ) — the description of the $ i $ -th segment.

In every test there exists at least one good subset.

## 输出格式

Print a single integer — the minimum cost of a good subset.

## 样例 #1

### 输入

```
5 12
1 5 5
3 4 10
4 10 6
11 12 5
10 12 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 10
1 10 23
```

### 输出

```
0
```



---

---
title: "Count Seconds"
layout: "post"
diff: 提高+/省选-
pid: CF1704E
tag: ['拓扑排序']
---

# Count Seconds

## 题目描述

Cirno has a DAG (Directed Acyclic Graph) with $ n $ nodes and $ m $ edges. The graph has exactly one node that has no out edges. The $ i $ -th node has an integer $ a_i $ on it.

Every second the following happens:

- Let $ S $ be the set of nodes $ x $ that have $ a_x > 0 $ .
- For all $ x \in S $ , $ 1 $ is subtracted from $ a_x $ , and then for each node $ y $ , such that there is an edge from $ x $ to $ y $ , $ 1 $ is added to $ a_y $ .

Find the first moment of time when all $ a_i $ become $ 0 $ . Since the answer can be very large, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases. Description of test cases follows.

The first line of each test case contains two integers $ n, m $ ( $ 1 \leq n, m \leq 1000 $ ) — the number of vertices and edges in the graph.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq 10^9 $ ) — the integer on vertices.

Each line of the following $ m $ lines contains two integers $ x, y $ ( $ 1 \leq x, y \leq n $ ), represent a directed edge from $ x $ to $ y $ . It is guaranteed that the graph is a DAG with no multi-edges, and there is exactly one node that has no out edges.

It is guaranteed that both sum of $ n $ and sum of $ m $ over all test cases are less than or equal to $ 10\,000 $ .

## 输出格式

For each test case, print an integer in a separate line — the first moment of time when all $ a_i $ become $ 0 $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case:

- At time $ 0 $ , the values of the nodes are $ [1, 1, 1] $ .
- At time $ 1 $ , the values of the nodes are $ [0, 1, 1] $ .
- At time $ 2 $ , the values of the nodes are $ [0, 0, 1] $ .
- At time $ 3 $ , the values of the nodes are $ [0, 0, 0] $ .

So the answer is $ 3 $ .

 In the second test case: - At time $ 0 $ , the values of the nodes are $ [1, 0, 0, 0, 0] $ .
- At time $ 1 $ , the values of the nodes are $ [0, 1, 0, 0, 1] $ .
- At time $ 2 $ , the values of the nodes are $ [0, 0, 1, 0, 0] $ .
- At time $ 3 $ , the values of the nodes are $ [0, 0, 0, 1, 0] $ .
- At time $ 4 $ , the values of the nodes are $ [0, 0, 0, 0, 1] $ .
- At time $ 5 $ , the values of the nodes are $ [0, 0, 0, 0, 0] $ .

 So the answer is $ 5 $ .In the third test case:

The first moment of time when all $ a_i $ become $ 0 $ is $ 6\cdot 998244353 + 4 $ .

## 样例 #1

### 输入

```
5
3 2
1 1 1
1 2
2 3
5 5
1 0 0 0 0
1 2
2 3
3 4
4 5
1 5
10 11
998244353 0 0 0 998244353 0 0 0 0 0
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
1 3
7 9
5 6
1293 1145 9961 9961 1919
1 2
2 3
3 4
5 4
1 4
2 4
6 9
10 10 10 10 10 10
1 2
1 3
2 3
4 3
6 3
3 5
6 5
6 1
6 2
```

### 输出

```
3
5
4
28010
110
```



---

---
title: "Imbalanced Arrays"
layout: "post"
diff: 提高+/省选-
pid: CF1852B
tag: ['贪心', '拓扑排序', '构造']
---

# Imbalanced Arrays

## 题目描述

Ntarsis has come up with an array $ a $ of $ n $ non-negative integers.

Call an array $ b $ of $ n $ integers imbalanced if it satisfies the following:

- $ -n\le b_i\le n $ , $ b_i \ne 0 $ ,
- there are no two indices $ (i, j) $ ( $ 1 \le i, j \le n $ ) such that $ b_i + b_j = 0 $ ,
- for each $ 1 \leq i \leq n $ , there are exactly $ a_i $ indices $ j $ ( $ 1 \le j \le n $ ) such that $ b_i+b_j>0 $ , where $ i $ and $ j $ are not necessarily distinct.

Given the array $ a $ , Ntarsis wants you to construct some imbalanced array. Help him solve this task, or determine it is impossible.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case has a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ).

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq n $ ).

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output "NO" if there exists no imbalanced array.

Otherwise, output "YES". Then, on the next line, output $ n $ integers $ b_1, b_2, \ldots, b_n $ where $ b_i \neq 0 $ for all $ 1 \leq i \leq n $ — an imbalanced array.

## 说明/提示

For the first test case, $ b = [1] $ is an imbalanced array. This is because for $ i = 1 $ , there is exactly one $ j $ ( $ j = 1 $ ) where $ b_1 + b_j > 0 $ .

For the second test case, it can be shown that there exists no imbalanced array.

For the third test case, $ a = [0, 1, 0] $ . The array $ b = [-3, 1, -2] $ is an imbalanced array.

- For $ i = 1 $ and $ i = 3 $ , there exists no index $ j $ such that $ b_i + b_j > 0 $ .
- For $ i = 2 $ , there is only one index $ j = 2 $ such that $ b_i + b_j > 0 $ ( $ b_2 + b_2 = 1 + 1 = 2 $ ).

 Another possible output for the third test case could be $ b = [-2, 1, -3] $ .

## 样例 #1

### 输入

```
5
1
1
4
1 4 3 4
3
0 1 0
4
4 3 2 1
3
1 3 1
```

### 输出

```
YES
1 
NO
YES
-3 1 -2 
YES
4 2 -1 -3 
YES
-1 3 -1
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
title: "Gellyfish and Camellia Japonica"
layout: "post"
diff: 提高+/省选-
pid: CF2115B
tag: ['图论', '拓扑排序']
---

# Gellyfish and Camellia Japonica

## 题目描述

Gellyfish 有一个长度为 $n$ 的整数数组 $c$，初始状态为 $c = [a_1, a_2, \ldots, a_n]$。接下来，Gellyfish 对数组进行 $q$ 次修改。每次修改由三个整数 $x_i, y_i, z_i$ 描述，表示将 $c_{z_i}$ 的值设置为 $\min(c_{x_i}, c_{y_i})$。经过 $q$ 次修改后，数组变为 $c = [b_1, b_2, \ldots, b_n]$。  
Flower 知道最终数组 $b$ 和所有修改操作 $(x_i, y_i, z_i)$，但不知道初始数组 $a$。她希望找到任意一个满足条件的初始数组 $a$，或者判断不存在这样的 $a$。如果存在多个解，输出任意一个即可。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的数量。  
对于每个测试用例:  
第一行包含两个整数 $n$ 和 $q$（$1 \leq n, q \leq 3 \cdot 10^5$），分别表示数组大小和修改次数。  
第二行包含 $n$ 个整数 $b_1, b_2, \ldots, b_n$（$1 \leq b_i \leq 10^9$），表示修改后的数组。  
接下来的 $q$ 行，每行包含三个整数 $x_i, y_i, z_i$（$1 \leq x_i, y_i, z_i \leq n$），描述一次修改操作。  
所有测试用例的 $n$ 之和与 $q$ 之和均不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例：  
如果存在初始数组 $a$，输出一行 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \leq a_i \leq 10^9$）。  
否则，输出一行 `-1` 。

## 说明/提示

**第一个测试用例：** 修改操作要求 $b_2 = \min(a_1, a_2)$，且 $b_1 = a_1$。但 $b_1 = 1 < b_2 = 2$，矛盾，无解。  
**第二个测试用例：** 初始数组 $a = [1, 2, 3]$ 经过两次修改后得到 $b = [1, 2, 3]$。  
**第三个测试用例：** 输出 $a = [1, 2, 3, 4, 5, 5]$ 是一个可行解。  

---  

由 DeepSeek 翻译

## 样例 #1

### 输入

```
3
2 1
1 2
2 1 2
3 2
1 2 3
2 3 2
1 2 1
6 4
1 2 2 3 4 5
5 6 6
4 5 5
3 4 4
2 3 3
```

### 输出

```
-1
1 2 3 
1 2 3 4 5 5
```



---

---
title: "A Simple Task"
layout: "post"
diff: 提高+/省选-
pid: CF558E
tag: ['字符串', '线段树', '排序']
---

# A Simple Task

## 题目描述

This task is very simple. Given a string $ S $ of length $ n $ and $ q $ queries each query is on the format $ i $ $ j $ $ k $ which means sort the substring consisting of the characters from $ i $ to $ j $ in non-decreasing order if $ k=1 $ or in non-increasing order if $ k=0 $ .

Output the final string after applying the queries.

## 输入格式

The first line will contain two integers $ n,q $ ( $ 1<=n<=10^{5} $ , $ 0<=q<=50000 $ ), the length of the string and the number of queries respectively.

Next line contains a string $ S $ itself. It contains only lowercase English letters.

Next $ q $ lines will contain three integers each $ i,j,k $ ( $ 1<=i<=j<=n $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/7c3e064c95015e1bd5569e78df83991726b5fb24.png)).

## 输出格式

Output one line, the string $ S $ after applying the queries.

## 说明/提示

First sample test explanation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/39812d297b72578842edac4711612bcaf8f08f55.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/6cf00260e704a305c81e1f57b87405efa2610fa7.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/8d72452272093b12cc5f5081cf07220bba9298d5.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/51ddb7e0620c1f3452d956f281c3537d11d07fb3.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/47cfdfe8b8cb10e651ce3dbdd53d8f068aca3e79.png)

## 样例 #1

### 输入

```
10 5
abacdabcda
7 10 0
5 8 1
1 4 0
3 6 0
7 10 1

```

### 输出

```
cbcaaaabdd
```

## 样例 #2

### 输入

```
10 1
agjucbvdfk
1 10 1

```

### 输出

```
abcdfgjkuv
```



---

---
title: "Cartons of milk"
layout: "post"
diff: 提高+/省选-
pid: CF767D
tag: ['贪心', '枚举', '排序']
---

# Cartons of milk

## 题目描述

Olya likes milk very much. She drinks $ k $ cartons of milk each day if she has at least $ k $ and drinks all of them if she doesn't. But there's an issue — expiration dates. Each carton has a date after which you can't drink it (you still can drink it exactly at the date written on the carton). Due to this, if Olya's fridge contains a carton past its expiry date, she throws it away.

Olya hates throwing out cartons, so when she drinks a carton, she chooses the one which expires the fastest. It's easy to understand that this strategy minimizes the amount of cartons thrown out and lets her avoid it if it's even possible.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767D/609b94e7f0b8a5d407df0e97345c78713f56ad66.png)Milk. Best before: 20.02.2017.The main issue Olya has is the one of buying new cartons. Currently, there are $ n $ cartons of milk in Olya's fridge, for each one an expiration date is known (how soon does it expire, measured in days). In the shop that Olya visited there are $ m $ cartons, and the expiration date is known for each of those cartons as well.

Find the maximum number of cartons Olya can buy so that she wouldn't have to throw away any cartons. Assume that Olya drank no cartons today.

## 输入格式

In the first line there are three integers $ n $ , $ m $ , $ k $ ( $ 1<=n,m<=10^{6} $ , $ 1<=k<=n+m $ ) — the amount of cartons in Olya's fridge, the amount of cartons in the shop and the number of cartons Olya drinks each day.

In the second line there are $ n $ integers $ f_{1},f_{2},...,f_{n} $ ( $ 0<=f_{i}<=10^{7} $ ) — expiration dates of the cartons in Olya's fridge. The expiration date is expressed by the number of days the drinking of this carton can be delayed. For example, a $ 0 $ expiration date means it must be drunk today, $ 1 $ — no later than tomorrow, etc.

In the third line there are $ m $ integers $ s_{1},s_{2},...,s_{m} $ ( $ 0<=s_{i}<=10^{7} $ ) — expiration dates of the cartons in the shop in a similar format.

## 输出格式

If there's no way for Olya to drink the cartons she already has in her fridge, print -1.

Otherwise, in the first line print the maximum number $ x $ of cartons which Olya can buy so that she wouldn't have to throw a carton away. The next line should contain exactly $ x $ integers — the numbers of the cartons that should be bought (cartons are numbered in an order in which they are written in the input, starting with $ 1 $ ). Numbers should not repeat, but can be in arbitrary order. If there are multiple correct answers, print any of them.

## 说明/提示

In the first example $ k=2 $ and Olya has three cartons with expiry dates $ 0 $ , $ 1 $ and $ 1 $ (they expire today, tomorrow and tomorrow), and the shop has $ 3 $ cartons with expiry date $ 0 $ and $ 3 $ cartons with expiry date $ 2 $ . Olya can buy three cartons, for example, one with the expiry date $ 0 $ and two with expiry date $ 2 $ .

In the second example all three cartons Olya owns expire today and it means she would have to throw packets away regardless of whether she buys an extra one or not.

In the third example Olya would drink $ k=2 $ cartons today (one she alreay has in her fridge and one from the shop) and the remaining one tomorrow.

## 样例 #1

### 输入

```
3 6 2
1 0 1
2 0 2 0 0 2

```

### 输出

```
3
1 2 3
```

## 样例 #2

### 输入

```
3 1 2
0 0 0
1

```

### 输出

```
-1
```

## 样例 #3

### 输入

```
2 1 2
0 1
0

```

### 输出

```
1
1 
```



---

---
title: "Hanoi Factory"
layout: "post"
diff: 提高+/省选-
pid: CF777E
tag: ['枚举', '排序']
---

# Hanoi Factory

## 题目描述

你肯定听说过著名的游戏汉诺塔吧，但是你知道有一个神奇的工厂专门制造这种游戏塔上的环吗？很久之前，古埃及的裁定者命令“汉诺工厂”（上文提到的工厂）的工人制造一座尽可能高的汉诺塔，而他们没有做好准备去执行这样一个奇怪的命令，所以他们不得不用已经造好的环。
工厂储备有$n$个环，其内径为$a_i$，外径为$b_i$，高度为$h_i$。要求环的放置条件如下：
-    塔的外半径从下至上为非递增序列，即越下面的环外径不能小于上面的环
-    环不能掉下来，即相邻两环上方的环的外径必须大于下面的环的内径
-    塔的高度必须最大

## 输入格式

第$1$行一个数$n$，代表环的数量
第$2$~$n-1$行，每行3个数$a_i,b_i,h_i$代表环的内径，外径，高度

## 输出格式

一个整数，代表塔的最大高度

## 说明/提示

Translated by Venus

## 样例 #1

### 输入

```
3
1 5 1
2 6 2
3 7 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4
1 2 1
1 3 3
4 6 2
5 7 1

```

### 输出

```
4

```



---

---
title: "Sum of Medians"
layout: "post"
diff: 提高+/省选-
pid: CF85D
tag: ['线段树', '枚举', '排序', '分块']
---

# Sum of Medians

## 题目描述

In one well-known algorithm of finding the $ k $ -th order statistics we should divide all elements into groups of five consecutive elements and find the median of each five. A median is called the middle element of a sorted array (it's the third largest element for a group of five). To increase the algorithm's performance speed on a modern video card, you should be able to find a sum of medians in each five of the array.

A sum of medians of a sorted $ k $ -element set $ S={a_{1},a_{2},...,a_{k}} $ , where $ a_{1}&lt;a_{2}&lt;a_{3}&lt;...&lt;a_{k} $ , will be understood by as

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/ade3397df6e8978ddadfc100b4ccb88beefd1e3f.png)The ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) operator stands for taking the remainder, that is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) stands for the remainder of dividing $ x $ by $ y $ .

To organize exercise testing quickly calculating the sum of medians for a changing set was needed.

## 输入格式

The first line contains number $ n $ ( $ 1<=n<=10^{5} $ ), the number of operations performed.

Then each of $ n $ lines contains the description of one of the three operations:

- add $ x $  — add the element $ x $ to the set;
- del $ x $  — delete the element $ x $ from the set;
- sum — find the sum of medians of the set.

For any add $ x $  operation it is true that the element $ x $ is not included in the set directly before the operation.

For any del $ x $  operation it is true that the element $ x $ is included in the set directly before the operation.

All the numbers in the input are positive integers, not exceeding $ 10^{9} $ .

## 输出格式

For each operation sum print on the single line the sum of medians of the current set. If the set is empty, print 0.

Please, do not use the %lld specificator to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams (also you may use the %I64d specificator).

## 样例 #1

### 输入

```
6
add 4
add 5
add 1
add 2
add 3
sum

```

### 输出

```
3

```

## 样例 #2

### 输入

```
14
add 1
add 7
add 2
add 5
sum
add 6
add 8
add 9
add 3
add 4
add 10
sum
del 1
sum

```

### 输出

```
5
11
13

```



---

---
title: "Too Easy Problems"
layout: "post"
diff: 提高+/省选-
pid: CF913D
tag: ['贪心', '排序', '优先队列']
---

# Too Easy Problems

## 题目描述

你正在准备一场关于调度理论的考试。

这场考试会持续正好 $T$ 毫秒，由 $n$ 道题目组成。

你可以用 $t_i$ 毫秒解决第 $i$ 个问题，或者忽略它并不消耗时间。你也不需要用来在做完一道题之后休息的时间。

不幸的是，你的老师认为一些题目对你来说太简单了。因此，他对于每道题 $i$ 规定了一个整数 $a_i$，表示题目 $i$ 只在你总共解决了不超过 $a_i$ 个问题（包括问题 $i$ ）的情况下为你的最终成绩加上一分。

正式地，假设你在考试中解决了问题 $p_1,p_2,\cdots,p_k$。那么，你的最终成绩 $s$ 会等于在 $1$ 到 $k$ 之间的满足 $k\le a_{p_j}$ 的 $j$ 的个数。

你已经意识到这场考试真正的第一道题目已经放在了你面前。因此，你想要选择一组题目来解决，从而最大化你的最终成绩。不要忘记这场考试有时间限制，而你必须有足够的时间来解决所有你选择的题目。如果存在多个最优解，任意输出一组即可。

## 输入格式

第一行包含 $2$ 个整数，$n$ 和 $T$，分别是考试中题目的数量和考试时长的毫秒数。

接下来的 $n$ 行每行包括两个整数 $a_i$ 和 $t_i$。题目编号从 $1$ 到 $n$。

## 输出格式

在第一行，输出一个单独的整数 $s$，表示你的可能得到的最终成绩的最大值。

在第二行，输出一个单独的整数 $k$ 表示你应该解决的问题数量。

在第三行，以任意顺序输出 $k$ 个不同整数 $p_1,p_2,\cdots,p_k$，即你应当解决的题目编号。

如果有多个最优解，你可以输出其中任意一个。

## 样例解释

在第一个样例中，你应该解决题目 $3$、$1$ 和 $4$。在这种解下你会花费 $80+100+90=270$ 毫秒，在考试的长度 $300$ms 以内（甚至给自己留出了 $30$ms 休息时间）。题目 $3$ 和题目 $1$ 会分别为你带来 $1$ 分，然而题目 $4$ 不会。你会得到 $2$ 分。

在第二个样例中，这场灾难性的考试的长度甚至不足以解决一道题目（所以你显然一分都得不到）。

在第三个样例中，你刚好有足够的时间 $(42+58=100)$ 来解决这两道题并且微笑着把答卷交给老师。

## 说明/提示

$1\le n\le 2\times10^5$

$1\le T\le10^9$

$0\le k\le n$

## 样例 #1

### 输入

```
5 300
3 100
4 150
4 80
2 90
2 300

```

### 输出

```
2
3
3 1 4

```

## 样例 #2

### 输入

```
2 100
1 787
2 788

```

### 输出

```
0
0


```

## 样例 #3

### 输入

```
2 100
2 42
2 58

```

### 输出

```
2
2
1 2

```



---

---
title: "Robot Vacuum Cleaner"
layout: "post"
diff: 提高+/省选-
pid: CF922D
tag: ['字符串', '排序', '概率论']
---

# Robot Vacuum Cleaner

## 题目描述

Pushok the dog has been chasing Imp for a few hours already.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/829d42ff73514382387680ad82853edceea77a87.png)Fortunately, Imp knows that Pushok is afraid of a robot vacuum cleaner.

While moving, the robot generates a string $ t $ consisting of letters 's' and 'h', that produces a lot of noise. We define noise of string $ t $ as the number of occurrences of string "sh" as a subsequence in it, in other words, the number of such pairs $ (i,j) $ , that $ i<j $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/f1a56c1d084d739e6652be99271753eea487f10e.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/1c020fe0ca945d3f2fc54f71a604c6ab2188fcee.png).

The robot is off at the moment. Imp knows that it has a sequence of strings $ t_{i} $ in its memory, and he can arbitrary change their order. When the robot is started, it generates the string $ t $ as a concatenation of these strings in the given order. The noise of the resulting string equals the noise of this concatenation.

Help Imp to find the maximum noise he can achieve by changing the order of the strings.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of strings in robot's memory.

Next $ n $ lines contain the strings $ t_{1},t_{2},...,t_{n} $ , one per line. It is guaranteed that the strings are non-empty, contain only English letters 's' and 'h' and their total length does not exceed $ 10^{5} $ .

## 输出格式

Print a single integer — the maxumum possible noise Imp can achieve by changing the order of the strings.

## 说明/提示

The optimal concatenation in the first sample is $ ssshhshhhs $ .

## 样例 #1

### 输入

```
4
ssh
hs
s
hhhs

```

### 输出

```
18

```

## 样例 #2

### 输入

```
2
h
s

```

### 输出

```
1

```



---

---
title: "Water Taps"
layout: "post"
diff: 提高+/省选-
pid: CF954E
tag: ['贪心', '排序']
---

# Water Taps

## 题目描述

Consider a system of $ n $ water taps all pouring water into the same container. The $ i $ -th water tap can be set to deliver any amount of water from $ 0 $ to $ a_{i} $ ml per second (this amount may be a real number). The water delivered by $ i $ -th tap has temperature $ t_{i} $ .

If for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/035d166bda223ecd5c31eb614a76bdcc9b8fe8c4.png) you set $ i $ -th tap to deliver exactly $ x_{i} $ ml of water per second, then the resulting temperature of water will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/4d0f711b0c4dc1450cd61a20f118d34a644e0d79.png) (if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/dbce41b29215315b290a54646261b5eaa9727507.png), then to avoid division by zero we state that the resulting water temperature is $ 0 $ ).

You have to set all the water taps in such a way that the resulting temperature is exactly $ T $ . What is the maximum amount of water you may get per second if its temperature has to be $ T $ ?

## 输入格式

The first line contains two integers $ n $ and $ T $ ( $ 1<=n<=200000 $ , $ 1<=T<=10^{6} $ ) — the number of water taps and the desired temperature of water, respectively.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{6} $ ) where $ a_{i} $ is the maximum amount of water $ i $ -th tap can deliver per second.

The third line contains $ n $ integers $ t_{1} $ , $ t_{2} $ , ..., $ t_{n} $ ( $ 1<=t_{i}<=10^{6} $ ) — the temperature of water each tap delivers.

## 输出格式

Print the maximum possible amount of water with temperature exactly $ T $ you can get per second (if it is impossible to obtain water with such temperature, then the answer is considered to be $ 0 $ ).

Your answer is considered correct if its absolute or relative error doesn't exceed $ 10^{-6} $ .

## 样例 #1

### 输入

```
2 100
3 10
50 150

```

### 输出

```
6.000000000000000

```

## 样例 #2

### 输入

```
3 9
5 5 30
6 6 10

```

### 输出

```
40.000000000000000

```

## 样例 #3

### 输入

```
2 12
1 3
10 15

```

### 输出

```
1.666666666666667

```



---

---
title: "Mahmoud and Ehab and yet another xor task"
layout: "post"
diff: 提高+/省选-
pid: CF959F
tag: ['排序', '线性基']
---

# Mahmoud and Ehab and yet another xor task

## 题目描述

Ehab has an array $ a $ of $ n $ integers. He likes the [bitwise-xor operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) and he likes to bother Mahmoud so he came up with a problem. He gave Mahmoud $ q $ queries. In each of them, he gave Mahmoud 2 integers $ l $ and $ x $ , and asked him to find the number of subsequences of the first $ l $ elements of the array such that their bitwise-xor sum is $ x $ . Can you help Mahmoud answer the queries?

A subsequence can contain elements that are not neighboring.

## 输入格式

The first line contains integers $ n $ and $ q $ $ (1<=n,q<=10^{5}) $ , the number of elements in the array and the number of queries.

The next line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ $ (0<=a_{i}<2^{20}) $ , the elements of the array.

The next $ q $ lines, each contains integers $ l $ and $ x $ $ (1<=l<=n $ , $ 0<=x<2^{20}) $ , representing the queries.

## 输出格式

For each query, output its answer modulo $ 10^{9}+7 $ in a newline.

## 说明/提示

The bitwise-xor sum of the empty set is 0 and the bitwise-xor sum of a set containing one element is that element itself.

## 样例 #1

### 输入

```
5 5
0 1 2 3 4
4 3
2 0
3 7
5 7
5 8

```

### 输出

```
4
2
0
4
0

```

## 样例 #2

### 输入

```
3 2
1 1 1
3 1
2 0

```

### 输出

```
4
2

```



---

