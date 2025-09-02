---
title: "Making Towers"
layout: "post"
diff: 普及-
pid: CF1706B
tag: ['动态规划 DP']
---

# Making Towers

## 题目描述

You have a sequence of $ n $ colored blocks. The color of the $ i $ -th block is $ c_i $ , an integer between $ 1 $ and $ n $ .

You will place the blocks down in sequence on an infinite coordinate grid in the following way.

1. Initially, you place block $ 1 $ at $ (0, 0) $ .
2. For $ 2 \le i \le n $ , if the $ (i - 1) $ -th block is placed at position $ (x, y) $ , then the $ i $ -th block can be placed at one of positions $ (x + 1, y) $ , $ (x - 1, y) $ , $ (x, y + 1) $ (but not at position $ (x, y - 1) $ ), as long no previous block was placed at that position.

A tower is formed by $ s $ blocks such that they are placed at positions $ (x, y), (x, y + 1), \ldots, (x, y + s - 1) $ for some position $ (x, y) $ and integer $ s $ . The size of the tower is $ s $ , the number of blocks in it. A tower of color $ r $  is a tower such that all blocks in it have the color $ r $ .

For each color $ r $ from $ 1 $ to $ n $ , solve the following problem independently:

- Find the maximum size of a tower of color $ r $ that you can form by placing down the blocks according to the rules.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ).

The second line of each test case contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 1 \le c_i \le n $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers. The $ r $ -th of them should be the maximum size of an tower of color $ r $ you can form by following the given rules. If you cannot form any tower of color $ r $ , the $ r $ -th integer should be $ 0 $ .

## 说明/提示

In the first test case, one of the possible ways to form a tower of color $ 1 $ and size $ 3 $ is:

- place block $ 1 $ at position $ (0, 0) $ ;
- place block $ 2 $ to the right of block $ 1 $ , at position $ (1, 0) $ ;
- place block $ 3 $ above block $ 2 $ , at position $ (1, 1) $ ;
- place block $ 4 $ to the left of block $ 3 $ , at position $ (0, 1) $ ;
- place block $ 5 $ to the left of block $ 4 $ , at position $ (-1, 1) $ ;
- place block $ 6 $ above block $ 5 $ , at position $ (-1, 2) $ ;
- place block $ 7 $ to the right of block $ 6 $ , at position $ (0, 2) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706B/ec98c0f164311a4ec7c2c7d82fee7c9f6eae74e7.png)The blocks at positions $ (0, 0) $ , $ (0, 1) $ , and $ (0, 2) $ all have color $ 1 $ , forming an tower of size $ 3 $ .

In the second test case, note that the following placement is not valid, since you are not allowed to place block $ 6 $ under block $ 5 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706B/39b20d638e1634a0778efb064f52a1e1cffbd150.png)It can be shown that it is impossible to form a tower of color $ 4 $ and size $ 3 $ .

## 样例 #1

### 输入

```
6
7
1 2 3 1 2 3 1
6
4 2 2 2 4 4
1
1
5
5 4 5 3 5
6
3 3 3 1 3 3
8
1 2 3 4 4 3 2 1
```

### 输出

```
3 2 2 0 0 0 0 
0 3 0 2 0 0 
1 
0 0 1 1 1 
1 0 4 0 0 0 
2 2 2 2 0 0 0 0
```



---

---
title: "Magnitude (Easy Version)"
layout: "post"
diff: 普及-
pid: CF1984C1
tag: ['动态规划 DP', '贪心']
---

# Magnitude (Easy Version)

## 题目描述

### **题目翻译描述**

这个问题的两个版本是不同的。你可能想阅读这两个版本。这样，只有两个版本都解决了，你才能成为黑客。

您将获得一个长度n的数组。C=0.然后，对于从i到n（按升序排列）执行以下操作之一：

选项1：将c设置为c+$a_{i} $。
 
选项2：放c到∣c+$a_{i}$∣，其中∣x∣表示x的绝对值。

你要使运行上述过程之后的c的最大最终值等于k，并且找到输出k。

## 输入格式

第一行包含一个整数t（$1 \le t \le $$10^4 $)—测试询问的数量。

每个测试询问的第一行包含一个整数n（$2 \le t \le 2 \cdot$$10^5 $)。

每个测试询问的第二行包含n整数 $a_{1} $,$a_{2} $,$a_{3} $, … ,$a_n$（ $-10^9$  $ \le $$a_i$ $ \le $$10^9$)。

所有测试询问的n之和不超过3 $\cdot$$10^9$。

## 输出格式

对于每个测试询问，输出一个整数——k的值。

### 说明/提示 翻译

在第一个测试询问中，如果我们每次添加c时都将其设置为绝对值，那么最终得到6。可以看出，这是最大的结果。

在第二个测试询问中，取绝对值永远不会改变任何结果，所以我们可以不做任何选项，直接对数组求和，得到24。

在第三个测试询问中，等到最后将c设置为其绝对值，得到6。

## 样例 #1

### 输入

```
5
4
10 -9 -3 4
8
1 4 3 4 1 4 3 4
3
-1 -2 -3
4
-1000000000 1000000000 1000000000 1000000000
4
1 9 8 4
```

### 输出

```
6
24
6
4000000000
22
```



---

---
title: "Stripe 2"
layout: "post"
diff: 普及-
pid: CF21C
tag: ['动态规划 DP', '枚举']
---

# Stripe 2

## 题目描述

给出一个长度为 $n$ 的序列 $a$，问有多少种方案将序列 $a$ 划分为恰好连续的三段（每个元素都属于某一段），使得每一段的和都相等。

## 输入格式

第一行一个整数 $n$，表示序列长度。

第二行 $n$ 个整数用空格隔开，第 $i$ 个整数表示 $a_i$。

## 输出格式

一行一个整数表示方案数。

## 样例 #1

### 输入

```
4
1 2 3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
1 2 3 4 5

```

### 输出

```
0

```



---

---
title: "Divisibility by Eight"
layout: "post"
diff: 普及-
pid: CF550C
tag: ['动态规划 DP', '枚举']
---

# Divisibility by Eight

## 题目描述

You are given a non-negative integer $ n $ , its decimal representation consists of at most $ 100 $ digits and doesn't contain leading zeroes.

Your task is to determine if it is possible in this case to remove some of the digits (possibly not remove any digit at all) so that the result contains at least one digit, forms a non-negative integer, doesn't have leading zeroes and is divisible by 8. After the removing, it is forbidden to rearrange the digits.

If a solution exists, you should print it.

## 输入格式

The single line of the input contains a non-negative integer $ n $ . The representation of number $ n $ doesn't contain any leading zeroes and its length doesn't exceed $ 100 $ digits.

## 输出格式

Print "NO" (without quotes), if there is no such way to remove some digits from number $ n $ .

Otherwise, print "YES" in the first line and the resulting number after removing digits from number $ n $ in the second line. The printed number must be divisible by $ 8 $ .

If there are multiple possible answers, you may print any of them.

## 样例 #1

### 输入

```
3454

```

### 输出

```
YES
344

```

## 样例 #2

### 输入

```
10

```

### 输出

```
YES
0

```

## 样例 #3

### 输入

```
111111

```

### 输出

```
NO

```



---

