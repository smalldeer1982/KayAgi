---
title: "George and Number"
layout: "post"
diff: 普及+/提高
pid: CF387C
tag: []
---

# George and Number

## 题目描述

George is a cat, so he really likes to play. Most of all he likes to play with his array of positive integers $ b $ . During the game, George modifies the array by using special changes. Let's mark George's current array as $ b_{1},b_{2},...,b_{|b|} $ (record $ |b| $ denotes the current length of the array). Then one change is a sequence of actions:

- Choose two distinct indexes $ i $ and $ j $ $ (1<=i,j<=|b|; i≠j) $ , such that $ b_{i}>=b_{j} $ .
- Get number $ v=concat(b_{i},b_{j}) $ , where $ concat(x,y) $ is a number obtained by adding number $ y $ to the end of the decimal record of number $ x $ . For example, $ concat(500,10)=50010 $ , $ concat(2,2)=22 $ .
- Add number $ v $ to the end of the array. The length of the array will increase by one.
- Remove from the array numbers with indexes $ i $ and $ j $ . The length of the array will decrease by two, and elements of the array will become re-numbered from $ 1 $ to current length of the array.

George played for a long time with his array $ b $ and received from array $ b $ an array consisting of exactly one number $ p $ . Now George wants to know: what is the maximum number of elements array $ b $ could contain originally? Help him find this number. Note that originally the array could contain only positive integers.

## 输入格式

The first line of the input contains a single integer $ p $ ( $ 1<=p&lt;10^{100000} $ ). It is guaranteed that number $ p $ doesn't contain any leading zeroes.

## 输出格式

Print an integer — the maximum number of elements array $ b $ could contain originally.

## 说明/提示

Let's consider the test examples:

- Originally array $ b $ can be equal to $ {5,9,5,5} $ . The sequence of George's changes could have been: $ {5,9,5,5}→{5,5,95}→{95,55}→{9555} $ .
- Originally array $ b $ could be equal to $ {1000000000,5} $ . Please note that the array $ b $ cannot contain zeros.
- Originally array $ b $ could be equal to $ {800,10,1} $ .
- Originally array $ b $ could be equal to $ {45} $ . It cannot be equal to $ {4,5} $ , because George can get only array $ {54} $ from this array in one operation.

Note that the numbers can be very large.

## 样例 #1

### 输入

```
9555

```

### 输出

```
4
```

## 样例 #2

### 输入

```
10000000005

```

### 输出

```
2
```

## 样例 #3

### 输入

```
800101

```

### 输出

```
3
```

## 样例 #4

### 输入

```
45

```

### 输出

```
1
```

## 样例 #5

### 输入

```
1000000000000001223300003342220044555

```

### 输出

```
17
```

## 样例 #6

### 输入

```
19992000

```

### 输出

```
1
```

## 样例 #7

### 输入

```
310200

```

### 输出

```
2
```

