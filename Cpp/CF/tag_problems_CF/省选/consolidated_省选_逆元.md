---
title: "Digit Tree"
layout: "post"
diff: 省选/NOI-
pid: CF715C
tag: ['最近公共祖先 LCA', '概率论', '逆元']
---

# Digit Tree

## 题目描述

ZS the Coder has a large tree. It can be represented as an undirected connected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ n-1 $ edges between them. There is a single nonzero digit written on each edge.

One day, ZS the Coder was bored and decided to investigate some properties of the tree. He chose a positive integer $ M $ , which is coprime to $ 10 $ , i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/9b5bdec4cb6231baa1f3fcb57eb25703ae0eed8f.png).

ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting when if he would follow the shortest path from vertex $ u $ to vertex $ v $ and write down all the digits he encounters on his path in the same order, he will get a decimal representaion of an integer divisible by $ M $ .

Formally, ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting if the following states true:

- Let $ a_{1}=u,a_{2},...,a_{k}=v $ be the sequence of vertices on the shortest path from $ u $ to $ v $ in the order of encountering them;
- Let $ d_{i} $ ( $ 1<=i&lt;k $ ) be the digit written on the edge between vertices $ a_{i} $ and $ a_{i+1} $ ;
- The integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/72be647436ef167ccaba4334e08ad71c22afc6b4.png) is divisible by $ M $ .

Help ZS the Coder find the number of interesting pairs!

## 输入格式

The first line of the input contains two integers, $ n $ and $ M $ ( $ 2<=n<=100000 $ , $ 1<=M<=10^{9} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/d9389e45dbbc083daab078bda82851582dd53c47.png)) — the number of vertices and the number ZS has chosen respectively.

The next $ n-1 $ lines contain three integers each. $ i $ -th of them contains $ u_{i},v_{i} $ and $ w_{i} $ , denoting an edge between vertices $ u_{i} $ and $ v_{i} $ with digit $ w_{i} $ written on it ( $ 0<=u_{i},v_{i}&lt;n,1<=w_{i}<=9 $ ).

## 输出格式

Print a single integer — the number of interesting (by ZS the Coder's consideration) pairs.

## 说明/提示

In the first sample case, the interesting pairs are $ (0,4),(1,2),(1,5),(3,2),(2,5),(5,2),(3,5) $ . The numbers that are formed by these pairs are $ 14,21,217,91,7,7,917 $ respectively, which are all multiples of $ 7 $ . Note that $ (2,5) $ and $ (5,2) $ are considered different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/08c05395fdf8f9a998abf43b020555e6b5471bd5.png)In the second sample case, the interesting pairs are $ (4,0),(0,4),(3,2),(2,3),(0,1),(1,0),(4,1),(1,4) $ , and $ 6 $ of these pairs give the number $ 33 $ while $ 2 $ of them give the number $ 3333 $ , which are all multiples of $ 11 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/8a71025758e81b9cf19889885872aec3ca3f5ffc.png)

## 样例 #1

### 输入

```
6 7
0 1 2
4 2 4
2 0 1
3 0 9
2 5 7

```

### 输出

```
7

```

## 样例 #2

### 输入

```
5 11
1 2 3
2 0 3
3 0 3
4 3 3

```

### 输出

```
8

```



---

---
title: "New Year and Arbitrary Arrangement"
layout: "post"
diff: 省选/NOI-
pid: CF908D
tag: ['动态规划 DP', '期望', '逆元']
---

# New Year and Arbitrary Arrangement

## 题目描述

You are given three integers $ k $ , $ p_{a} $ and $ p_{b} $ .

You will construct a sequence with the following algorithm: Initially, start with the empty sequence. Each second, you do the following. With probability $ p_{a}/(p_{a}+p_{b}) $ , add 'a' to the end of the sequence. Otherwise (with probability $ p_{b}/(p_{a}+p_{b}) $ ), add 'b' to the end of the sequence.

You stop once there are at least $ k $ subsequences that form 'ab'. Determine the expected number of times 'ab' is a subsequence in the resulting sequence. It can be shown that this can be represented by $ P/Q $ , where $ P $ and $ Q $ are coprime integers, and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908D/250bff4a0d2d6149565f6e795de0dbd59e6a92a3.png). Print the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908D/962b3e429ab173c8d460f96cc849d01fcd4a9d47.png).

## 输入格式

The first line will contain three integers integer $ k,p_{a},p_{b} $ ( $ 1<=k<=1000 $ , $ 1<=p_{a},p_{b}<=1000000 $ ).

## 输出格式

Print a single integer, the answer to the problem.

## 说明/提示

The first sample, we will keep appending to our sequence until we get the subsequence 'ab' at least once. For instance, we get the sequence 'ab' with probability 1/4, 'bbab' with probability 1/16, and 'aab' with probability 1/8. Note, it's impossible for us to end with a sequence like 'aabab', since we would have stopped our algorithm once we had the prefix 'aab'.

The expected amount of times that 'ab' will occur across all valid sequences is 2.

For the second sample, the answer is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908D/be8bc2d2b5b20d19237dcaabfc3c3ca4bcb22ac0.png).

## 样例 #1

### 输入

```
1 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 1 4

```

### 输出

```
370000006

```



---

