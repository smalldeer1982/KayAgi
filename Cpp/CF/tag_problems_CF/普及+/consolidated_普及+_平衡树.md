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
title: "Knights of a Polygonal Table"
layout: "post"
diff: 普及+/提高
pid: CF994B
tag: ['贪心', '平衡树', '向量']
---

# Knights of a Polygonal Table

## 题目描述

有  $n$  个骑士想决战。每个骑士都有能力值，且身上带有一些金币。如果骑士  $A$  的能力值大于骑士  $B$ ，那么骑士  $A$  就可以杀死骑士  $B$ ，并获得骑士  $B$  身上的所有金币。但就算是骑士也不会残忍过度，他们最多只会杀死  $k$  个骑士。对于每一位骑士，请你求出在决战后他身上金币的最大值。

## 输入格式

第  $1$  行，有  $2$  个整数，分别为骑士人数  $n$  和杀人数上限  $k$ 。

（数据范围： $1 \leqslant n \leqslant 10^{5}$ , $0 \leqslant k \leqslant min(n - 1,\ 10)$ ）

第  $2$  行，有  $n$  个整数，表示每个骑士的能力值  $p_i$ 。

第  $3$  行，有  $n$  个整数，表示每个骑士原有的金币  $c_i$ 。

（数据范围： $1 \leqslant p_i \leqslant 10^{9}$ , $0 \leqslant c_i \leqslant 10^{9}$ ）

## 输出格式

$1$  行内输出  $n$  个整数，决战后每个骑士身上金币的最大值，每两个数间以单个空格隔开。

## 说明/提示

- 第  $1$  组样例的解释：

第  $1$  个骑士是最蒻的，因此他谁也不能杀，只能保留自己原有的金币。

第  $2$  个骑士只能杀死第  $1$  个骑士，因此他最多拥有  $2 + 1 = 3$  个金币。

第  $3$  个骑士是最蔃的，但他只能选择杀  $k = 2$  个骑士。显然他会杀死第  $2$  个骑士和
第  $4$  个骑士，因为他们身上的金币更多。因此他最多拥有  $11 + 2 + 33 = 46$  个金币。

第  $4$  个骑士应该杀死第  $1$  个和第  $2$  个骑士，因此他最多拥有  $33 + 1 + 2 = 36$  个金币。 

- 第  $2$  组样例的解释：

除了最蒻的第  $1$  个骑士谁也不能杀，其他骑士都能杀死前一个骑士并获得他的金币。

- 第  $3$  组样例的解释：

由于只有一个骑士在决战中，他无法杀死任何人。

感谢@Sooke 提供翻译

## 样例 #1

### 输入

```
4 2
4 5 9 7
1 2 11 33

```

### 输出

```
1 3 46 36 
```

## 样例 #2

### 输入

```
5 1
1 2 3 4 5
1 2 3 4 5

```

### 输出

```
1 3 5 7 9 
```

## 样例 #3

### 输入

```
1 0
2
3

```

### 输出

```
3 
```



---

