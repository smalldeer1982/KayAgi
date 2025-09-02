---
title: "Cut"
layout: "post"
diff: 普及+/提高
pid: CF1516D
tag: ['倍增']
---

# Cut

## 题目描述

This time Baby Ehab will only cut and not stick. He starts with a piece of paper with an array $ a $ of length $ n $ written on it, and then he does the following:

- he picks a range $ (l, r) $ and cuts the subsegment $ a_l, a_{l + 1}, \ldots, a_r $ out, removing the rest of the array.
- he then cuts this range into multiple subranges.
- to add a number theory spice to it, he requires that the elements of every subrange must have their product equal to their [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple).

Formally, he partitions the elements of $ a_l, a_{l + 1}, \ldots, a_r $ into contiguous subarrays such that the product of every subarray is equal to its LCM. Now, for $ q $ independent ranges $ (l, r) $ , tell Baby Ehab the minimum number of subarrays he needs.

## 输入格式

The first line contains $ 2 $ integers $ n $ and $ q $ ( $ 1 \le n,q \le 10^5 $ ) — the length of the array $ a $ and the number of queries.

The next line contains $ n $ integers $ a_1 $ , $ a_2 $ , $ \ldots $ , $ a_n $ ( $ 1 \le a_i \le 10^5 $ ) — the elements of the array $ a $ .

Each of the next $ q $ lines contains $ 2 $ integers $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ) — the endpoints of this query's interval.

## 输出格式

For each query, print its answer on a new line.

## 说明/提示

The first query asks about the whole array. You can partition it into $ [2] $ , $ [3,10,7] $ , and $ [5,14] $ . The first subrange has product and LCM equal to $ 2 $ . The second has product and LCM equal to $ 210 $ . And the third has product and LCM equal to $ 70 $ . Another possible partitioning is $ [2,3] $ , $ [10,7] $ , and $ [5,14] $ .

The second query asks about the range $ (2,4) $ . Its product is equal to its LCM, so you don't need to partition it further.

The last query asks about the range $ (3,5) $ . You can partition it into $ [10,7] $ and $ [5] $ .

## 样例 #1

### 输入

```
6 3
2 3 10 7 5 14
1 6
2 4
3 5
```

### 输出

```
3
1
2
```



---

---
title: "Path Prefixes"
layout: "post"
diff: 普及+/提高
pid: CF1714G
tag: ['倍增', '二分']
---

# Path Prefixes

## 题目描述

# Path Prefixes


现有一颗以 $1$ 为根的树，节点编号从 $1$ 到 $n$ .

每条边有两个权值，分别为 $a_j$ 和 $b_j$ .

输出 $n-1$ 个数 $r_2,r_3 \cdots ,r_n$ ，其中 $r_i$ 定义如下:

考虑从根节点( $1$ 号节点 ) 到第 $i$ 号节点 $(2 \le i \le n)$ 的路径，令沿该路径 $a_j$ 的花费为 $A_i$ ， $r_i$ 为该路径的最长前缀，使该前缀的 $b_j$ 之和不大于 $A_i$ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1714G/fb21910eda699947633b658de9a5b141ee71688b.png)

以 $n=9$ 时为例，如上图，蓝色数字表示 $a_j$ 的花费，红色数字表示 $b_j$ 的花费.

在这种情况下：

- $ r_2=0 $ ， 因为到节点 $ 2 $ 的路径中有 $ a_j=5 $  ， 只有前缀为 $ 0 $ 时才可能有较小（或相等）的 $ b_j $ ；
- $ r_3=3 $ ， 因为到节点 $ 3 $ 的路径中 $ a_j $ 为 $ 5+9+5=19 $ ， 长为 $ 3 $ 的前缀使 $ b_j $ 为 $ 6+10+1=17 $ ( $ 17 \le 19 $ 符合题意 )；
- $ r_4=1 $ ， 因为到节点 $ 4 $ 的路径中 $ a_j $ 为 $ 5+9=14 $ ， 长为 $ 1 $ 的前缀使 $ b_j $ 为 $ 6 $ (这是最长的符合题意的前缀， 因为长为 $ 2 $ 的前缀的 $ b_j $ 为 $ 6+10=16 $ ， 大于 $ 14 $ )；
- $ r_5=2 $ ， 因为到节点 $ 5 $ 的路径中 $ a_j $ 为 $ 5+9+2=16 $ ， 长为 $ 2 $ 的前缀使 $ b_j $ 为 $ 6+10=16 $ (这是最长的符合题意的前缀， 因为长为 $ 3 $ 的前缀的 $ b_j $ 为 $ 6+10+1=17 $ ， 比 $ 16 $ 大 )；
- $ r_6=1 $ ， 因为到节点 $ 6 $ 的路径中 $ a_j $ 为 $ 2 $ ， 长为 $ 1 $ 的前缀使 $ b_j $ 等于 $ 1 $ ；
- $ r_7=1 $ ， 因为到节点 $ 7 $ 的路径中 $ a_j $ 为 $ 5+3=8 $ ， 长为 $ 1 $ 的前缀使 $ b_j $ 等于 $ 6 $ (这是最长的符合题意的前缀， 因为长为 $ 2 $ 的前缀的 $ b_j $ 为 $ 6+3=9 $ ， 超出了期望的 $ 8 $ )；
- $ r_8=2 $ ， 因为到节点 $ 8 $ 的路径中 $ a_j $ 为 $ 2+4=6 $ ， 长为 $ 2 $ 的前缀使 $ b_j $ 为 $ 1+3=4 $ ；
- $ r_9=3 $ ， 因为到节点 $ 9 $ 的路径中 $ a_j $ 为 $ 2+4+1=7 $ ， 长为 $ 3 $ 的前缀使 $ b_j $ 为 $ 1+3+3=7 $ .


在第二组样例中

- $ r_2=0 $ ，因为到节点 $ 2 $ 的路径中 $ a_j $ 等于 $ 1 $ ， 只有前缀为 $ 0 $ 时才可能有较小（或相等）的 $ b_j $
- $ r_3=0 $ ， 因为到节点 $ 3 $ 的路径中 $ a_j $ 为 $ 1+1=2 $ ， 长为  $ 1 $ 的前缀使 $ b_j $ 等于 $ 100 $ ( $ 100 > 2 $ )；
- $ r_4=3 $ ， 因为到节点 $ 4 $ 的路径中 of $ a_j $ 为 $ 1+1+101=103 $ ， 长为 $ 3 $ 的前缀使 $ b_j $ 为 $ 102 $  .

## 输入格式

第一行有一个整数 $ t $ ( $ 1 \le t \le 10^4 $ ) 表示测试组数.

每组样例以一个整数 $ n $ ( $ 2 \le n \le 2\cdot10^5 $ ) 开始，表示这棵树的节点数.

接下来 $ n-1 $ 行，每行有三个整数  $ p_j， a_j， b_j $ ( $ 1 \le p_j \le n $ ; $ 1 \le a_j,b_j \le 10^9 $ ) 分别表示节点 $ j $ 的祖先和从 $ p_j $ 到 $ j $  的两个边权. 

 $ j $ 的值从 $ 2 $ 到 $ n $ . 输入数据保证生成的是一颗以 $ 1 $ 根的树，且 $ n $ 不超过 $ 2\cdot10^5 $ .

## 输出格式

对于每一组输入，输出一行 $ n-1 $ 个数: $ r_2, r_3, \dots , r_n $ .

## 样例 #1

### 样例输入 #1

```
4
9
1 5 6
4 5 1
2 9 10
4 2 1
1 2 1
2 3 3
6 4 3
8 1 3
4
1 1 100
2 1 1
3 101 1
4
1 100 1
2 1 1
3 1 101
10
1 1 4
2 3 5
2 5 1
3 4 3
3 1 5
5 3 5
5 2 1
1 3 2
6 2 1
```

### 样例输出 #1

```
0 3 1 2 1 1 2 3 
0 0 3 
1 2 2 
0 1 2 1 1 2 2 1 1
```

## 样例 #1

### 输入

```
4
9
1 5 6
4 5 1
2 9 10
4 2 1
1 2 1
2 3 3
6 4 3
8 1 3
4
1 1 100
2 1 1
3 101 1
4
1 100 1
2 1 1
3 1 101
10
1 1 4
2 3 5
2 5 1
3 4 3
3 1 5
5 3 5
5 2 1
1 3 2
6 2 1
```

### 输出

```
0 3 1 2 1 1 2 3 
0 0 3 
1 2 2 
0 1 2 1 1 2 2 1 1
```



---

