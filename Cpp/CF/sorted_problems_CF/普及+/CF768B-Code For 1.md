---
title: "Code For 1"
layout: "post"
diff: 普及+/提高
pid: CF768B
tag: []
---

# Code For 1

## 题目描述

Jon fought bravely to rescue the wildlings who were attacked by the white-walkers at Hardhome. On his arrival, Sam tells him that he wants to go to Oldtown to train at the Citadel to become a maester, so he can return and take the deceased Aemon's place as maester of Castle Black. Jon agrees to Sam's proposal and Sam sets off his journey to the Citadel. However becoming a trainee at the Citadel is not a cakewalk and hence the maesters at the Citadel gave Sam a problem to test his eligibility.

Initially Sam has a list with a single element $ n $ . Then he has to perform certain operations on this list. In each operation Sam must remove any element $ x $ , such that $ x&gt;1 $ , from the list and insert at the same position ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768B/465cdad41298994952ff82579429cb3d1de6dea4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768B/42f87a6d55a7d4b8ea353aaf2fcb56c13744febb.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768B/465cdad41298994952ff82579429cb3d1de6dea4.png) sequentially. He must continue with these operations until all the elements in the list are either $ 0 $ or $ 1 $ .

Now the masters want the total number of $ 1 $ s in the range $ l $ to $ r $ ( $ 1 $ -indexed). Sam wants to become a maester but unfortunately he cannot solve this problem. Can you help Sam to pass the eligibility test?

## 输入格式

The first line contains three integers $ n $ , $ l $ , $ r $ ( $ 0<=n&lt;2^{50} $ , $ 0<=r-l<=10^{5} $ , $ r>=1 $ , $ l>=1 $ ) – initial element and the range $ l $ to $ r $ .

It is guaranteed that $ r $ is not greater than the length of the final list.

## 输出格式

Output the total number of $ 1 $ s in the range $ l $ to $ r $ in the final sequence.

## 说明/提示

Consider first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768B/e9c535e642142fa233499539a19c390315a69ecc.png)

Elements on positions from $ 2 $ -nd to $ 5 $ -th in list is $ [1,1,1,1] $ . The number of ones is $ 4 $ .

For the second example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768B/a34639e1edfe488c7c83f3ed3854d0edf4f7db1f.png)

Elements on positions from $ 3 $ -rd to $ 10 $ -th in list is $ [1,1,1,0,1,0,1,0] $ . The number of ones is $ 5 $ .

## 样例 #1

### 输入

```
7 2 5

```

### 输出

```
4

```

## 样例 #2

### 输入

```
10 3 10

```

### 输出

```
5

```

