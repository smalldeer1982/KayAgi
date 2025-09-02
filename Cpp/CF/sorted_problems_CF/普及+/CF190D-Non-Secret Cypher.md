---
title: "Non-Secret Cypher"
layout: "post"
diff: 普及+/提高
pid: CF190D
tag: []
---

# Non-Secret Cypher

## 题目描述

Berland starts to seize the initiative on the war with Flatland. To drive the enemy from their native land, the berlanders need to know exactly how many more flatland soldiers are left in the enemy's reserve. Fortunately, the scouts captured an enemy in the morning, who had a secret encrypted message with the information the berlanders needed so much.

The captured enemy had an array of positive integers. Berland intelligence have long been aware of the flatland code: to convey the message, which contained a number $ m $ , the enemies use an array of integers $ a $ . The number of its subarrays, in which there are at least $ k $ equal numbers, equals $ m $ . The number $ k $ has long been known in the Berland army so General Touristov has once again asked Corporal Vasya to perform a simple task: to decipher the flatlanders' message.

Help Vasya, given an array of integers $ a $ and number $ k $ , find the number of subarrays of the array of numbers $ a $ , which has at least $ k $ equal numbers.

Subarray $ a[i...\ j] (1<=i<=j<=n) $ of array $ a=(a_{1},a_{2},...,a_{n}) $ is an array, made from its consecutive elements, starting from the $ i $ -th one and ending with the $ j $ -th one: $ a[i...\ j]=(a_{i},a_{i+1},...,a_{j}) $ .

## 输入格式

The first line contains two space-separated integers $ n $ , $ k $ $ (1<=k<=n<=4·10^{5}) $ , showing how many numbers an array has and how many equal numbers the subarrays are required to have, correspondingly.

The second line contains $ n $ space-separated integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ) — elements of the array.

## 输出格式

Print the single number — the number of such subarrays of array $ a $ , that they have at least $ k $ equal integers.

Please do not use the %lld specifier to read or write 64-bit integers in С++. In is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first sample are three subarrays, containing at least two equal numbers: (1,2,1), (2,1,2) and (1,2,1,2).

In the second sample are two subarrays, containing three equal numbers: (1,2,1,1,3) and (1,2,1,1).

In the third sample any subarray contains at least one 1 number. Overall they are 6: (1), (1), (1), (1,1), (1,1) and (1,1,1).

## 样例 #1

### 输入

```
4 2
1 2 1 2

```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 3
1 2 1 1 3

```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 1
1 1 1

```

### 输出

```
6
```

