# Flip Flop Sum

## 题目描述

You are given an array of $ n $ integers $ a_1, a_2, \ldots, a_n $ . The integers are either $ 1 $ or $ -1 $ . You have to perform the following operation exactly once on the array $ a $ :

- Choose an index $ i $ ( $ 1 \leq i < n $ ) and flip the signs of $ a_i $ and $ a_{i+1} $ . Here, flipping the sign means $ -1 $ will be $ 1 $ and $ 1 $ will be $ -1 $ .

What is the maximum possible value of $ a_1 + a_2 + \ldots + a_n $ after applying the above operation?

## 说明/提示

In the first case, we can choose index $ 4 $ and flip the signs of $ a_4 $ and $ a_5 $ . After this operation, the sum will be $ -1+1+1+1+1 = 3 $ . We can't make the sum larger than this.

In the third case, the only option is to choose the index $ 1 $ .

## 样例 #1

### 输入

```
4
5
-1 1 1 -1 -1
5
1 1 -1 -1 -1
2
1 1
4
1 -1 -1 1```

### 输出

```
3
3
-2
4```

