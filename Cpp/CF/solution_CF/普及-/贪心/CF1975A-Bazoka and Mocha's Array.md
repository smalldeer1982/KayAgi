# Bazoka and Mocha's Array

## 题目描述

Mocha likes arrays, so before her departure, Bazoka gave her an array $ a $ consisting of $ n $ positive integers as a gift.

Now Mocha wants to know whether array $ a $ could become sorted in non-decreasing order after performing the following operation some (possibly, zero) times:

- Split the array into two parts — a prefix and a suffix, then swap these two parts. In other words, let $ a=x+y $ . Then, we can set $ a:= y+x $ . Here $ + $ denotes the array concatenation operation.

For example, if $ a=[3,1,4,1,5] $ , we can choose $ x=[3,1] $ and $ y=[4,1,5] $ , satisfying $ a=x+y $ . Then, we can set $ a:= y + x = [4,1,5,3,1] $ . We can also choose $ x=[3,1,4,1,5] $ and $ y=[\,] $ , satisfying $ a=x+y $ . Then, we can set $ a := y+x = [3,1,4,1,5] $ . Note that we are not allowed to choose $ x=[3,1,1] $ and $ y=[4,5] $ , neither are we allowed to choose $ x=[1,3] $ and $ y=[5,1,4] $ , as both these choices do not satisfy $ a=x+y $ .

## 说明/提示

In the first test case, it can be proven that $ a $ cannot become non-decreasing after performing the operation any number of times.

In the second test case, we can perform the following operations to make $ a $ sorted in non-decreasing order:

- Split the array into two parts: $ x=[7] $ and $ y=[9,2,2,3] $ , then swap these two parts. The array will become $ y+x = [9,2,2,3,7] $ .
- Split the array into two parts: $ x=[9] $ and $ y=[2,2,3,7] $ , then swap these two parts. The array will become $ y+x=[2,2,3,7,9] $ , which is non-decreasing.

## 样例 #1

### 输入

```
3
6
1 1 4 5 1 4
5
7 9 2 2 3
3
1 2 3```

### 输出

```
No
Yes
Yes```

