# Make It Zero

## 题目描述

During Zhongkao examination, Reycloer met an interesting problem, but he cannot come up with a solution immediately. Time is running out! Please help him.

Initially, you are given an array $ a $ consisting of $ n \ge 2 $ integers, and you want to change all elements in it to $ 0 $ .

In one operation, you select two indices $ l $ and $ r $ ( $ 1\le l\le r\le n $ ) and do the following:

- Let $ s=a_l\oplus a_{l+1}\oplus \ldots \oplus a_r $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR);
- Then, for all $ l\le i\le r $ , replace $ a_i $ with $ s $ .

You can use the operation above in any order at most $ 8 $ times in total.

Find a sequence of operations, such that after performing the operations in order, all elements in $ a $ are equal to $ 0 $ . It can be proven that the solution always exists.

## 说明/提示

In the first test case, since $ 1\oplus2\oplus3\oplus0=0 $ , after performing the operation on segment $ [1,4] $ , all the elements in the array are equal to $ 0 $ .

In the second test case, after the first operation, the array becomes equal to $ [3,1,4,15,15,15,15,6] $ , after the second operation, the array becomes equal to $ [0,0,0,0,0,0,0,0] $ .

In the third test case:

 Operation $ a $ before $ a $ after $ 1 $  $ [\underline{1,5},4,1,4,7] $  $ \rightarrow $  $ [4,4,4,1,4,7] $  $ 2 $  $ [4,4,\underline{4,1},4,7] $  $ \rightarrow $  $ [4,4,5,5,4,7] $  $ 3 $  $ [4,4,5,5,\underline{4,7}] $  $ \rightarrow $  $ [4,4,5,5,3,3] $  $ 4 $  $ [\underline{4,4,5},5,3,3] $  $ \rightarrow $  $ [5,5,5,5,3,3] $  $ 5 $  $ [5,5,5,\underline{5,3,3}] $  $ \rightarrow $  $ [5,5,5,5,5,5] $  $ 6 $  $ [\underline{5,5,5,5,5,5}] $  $ \rightarrow $  $ [0,0,0,0,0,0] $ In the fourth test case, the initial array contains only $ 0 $ , so we do not need to perform any operations with it.

## 样例 #1

### 输入

```
6
4
1 2 3 0
8
3 1 4 1 5 9 2 6
6
1 5 4 1 4 7
5
0 0 0 0 0
7
1 1 9 9 0 1 8
3
100 100 0```

### 输出

```
1
1 4
2
4 7
1 8
6
1 2
3 4
5 6
1 3
4 6
1 6
0
4
1 2
6 7
3 4
6 7
1
1 2```

