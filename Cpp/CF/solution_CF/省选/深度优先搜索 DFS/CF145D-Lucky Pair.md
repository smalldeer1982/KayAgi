# Lucky Pair

## 题目描述

Petya loves lucky numbers very much. Everybody knows that lucky numbers are positive integers whose decimal record contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya has an array $ a $ of $ n $ integers. The numbers in the array are numbered starting from $ 1 $ . Unfortunately, Petya has been misbehaving and so, his parents don't allow him play with arrays that have many lucky numbers. It is guaranteed that no more than $ 1000 $ elements in the array $ a $ are lucky numbers.

Petya needs to find the number of pairs of non-intersecting segments $ [l_{1};r_{1}] $ and $ [l_{2};r_{2}] $ ( $ 1<=l_{1}<=r_{1}&lt;l_{2}<=r_{2}<=n $ , all four numbers are integers) such that there's no such lucky number that occurs simultaneously in the subarray $ a[l_{1}..r_{1}] $ and in the subarray $ a[l_{2}..r_{2}] $ . Help Petya count the number of such pairs.

## 说明/提示

The subarray $ a[l..r] $ is an array that consists of elements $ a_{l} $ , $ a_{l+1} $ , ..., $ a_{r} $ .

In the first sample there are $ 9 $ possible pairs that satisfy the condition: $ [1,1] $ and $ [2,2] $ , $ [1,1] $ and $ [2,3] $ , $ [1,1] $ and $ [2,4] $ , $ [1,1] $ and $ [3,3] $ , $ [1,1] $ and $ [3,4] $ , $ [1,1] $ and $ [4,4] $ , $ [1,2] $ and $ [3,3] $ , $ [2,2] $ and $ [3,3] $ , $ [3,3] $ and $ [4,4] $ .

In the second sample there is only one pair of segments — $ [1;1] $ and $ [2;2] $ and it satisfies the condition.

## 样例 #1

### 输入

```
4
1 4 2 4
```

### 输出

```
9
```

## 样例 #2

### 输入

```
2
4 7
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4
4 4 7 7
```

### 输出

```
9
```

