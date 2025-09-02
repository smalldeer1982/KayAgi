# Koxia and Whiteboards

## 题目描述

Kiyora has $ n $ whiteboards numbered from $ 1 $ to $ n $ . Initially, the $ i $ -th whiteboard has the integer $ a_i $ written on it.

Koxia performs $ m $ operations. The $ j $ -th operation is to choose one of the whiteboards and change the integer written on it to $ b_j $ .

Find the maximum possible sum of integers written on the whiteboards after performing all $ m $ operations.

## 说明/提示

In the first test case, Koxia can perform the operations as follows:

1. Choose the $ 1 $ -st whiteboard and rewrite the integer written on it to $ b_1=4 $ .
2. Choose the $ 2 $ -nd whiteboard and rewrite to $ b_2=5 $ .

After performing all operations, the numbers on the three whiteboards are $ 4 $ , $ 5 $ and $ 3 $ respectively, and their sum is $ 12 $ . It can be proven that this is the maximum possible sum achievable.

In the second test case, Koxia can perform the operations as follows:

1. Choose the $ 2 $ -nd whiteboard and rewrite to $ b_1=3 $ .
2. Choose the $ 1 $ -st whiteboard and rewrite to $ b_2=4 $ .
3. Choose the $ 2 $ -nd whiteboard and rewrite to $ b_3=5 $ .

The sum is $ 4 + 5 = 9 $ . It can be proven that this is the maximum possible sum achievable.

## 样例 #1

### 输入

```
4
3 2
1 2 3
4 5
2 3
1 2
3 4 5
1 1
100
1
5 3
1 1 1 1 1
1000000000 1000000000 1000000000```

### 输出

```
12
9
1
3000000002```

