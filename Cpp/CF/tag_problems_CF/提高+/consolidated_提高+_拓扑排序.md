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

