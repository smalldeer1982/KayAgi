# Prairie Partition

## 题目描述

It can be shown that any positive integer $ x $ can be uniquely represented as $ x=1+2+4+...+2^{k-1}+r $ , where $ k $ and $ r $ are integers, $ k>=0 $ , $ 0&lt;r<=2^{k} $ . Let's call that representation prairie partition of $ x $ .

For example, the prairie partitions of $ 12 $ , $ 17 $ , $ 7 $ and $ 1 $ are:

 $ 12=1+2+4+5 $ , $ 17=1+2+4+8+2 $ ,

 $ 7=1+2+4 $ ,

 $ 1=1 $ .

Alice took a sequence of positive integers (possibly with repeating elements), replaced every element with the sequence of summands in its prairie partition, arranged the resulting numbers in non-decreasing order and gave them to Borys. Now Borys wonders how many elements Alice's original sequence could contain. Find all possible options!

## 说明/提示

In the first example, Alice could get the input sequence from $ [6,20] $ as the original sequence.

In the second example, Alice's original sequence could be either $ [4,5] $ or $ [3,3,3] $ .

## 样例 #1

### 输入

```
8
1 1 2 2 3 4 5 8
```

### 输出

```
2 
```

## 样例 #2

### 输入

```
6
1 1 1 2 2 2
```

### 输出

```
2 3 
```

## 样例 #3

### 输入

```
5
1 2 4 4 4
```

### 输出

```
-1
```

