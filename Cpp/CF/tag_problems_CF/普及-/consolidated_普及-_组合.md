---
title: "Secret Box"
layout: "post"
diff: 普及-
pid: CF1985E
tag: ['数学', '枚举', '排列组合']
---

# Secret Box

## 题目描述

Ntarsis has a box $ B $ with side lengths $ x $ , $ y $ , and $ z $ . It lies in the 3D coordinate plane, extending from $ (0,0,0) $ to $ (x,y,z) $ .

Ntarsis has a secret box $ S $ . He wants to choose its dimensions such that all side lengths are positive integers, and the volume of $ S $ is $ k $ . He can place $ S $ somewhere within $ B $ such that:

- $ S $ is parallel to all axes.
- every corner of $ S $ lies on an integer coordinate.

 $ S $ is magical, so when placed at an integer location inside $ B $ , it will not fall to the ground.

Among all possible ways to choose the dimensions of $ S $ , determine the maximum number of distinct locations he can choose to place his secret box $ S $ inside $ B $ . Ntarsis does not rotate $ S $ once its side lengths are selected.

## 输入格式

The first line consists of an integer $ t $ , the number of test cases ( $ 1 \leq t \leq 2000 $ ). The description of the test cases follows.

The first and only line of each test case contains four integers $ x, y, z $ and $ k $ ( $ 1 \leq x, y, z \leq 2000 $ , $ 1 \leq k \leq x \cdot y \cdot z $ ).

It is guaranteed the sum of all $ x $ , sum of all $ y $ , and sum of all $ z $ do not exceed $ 2000 $ over all test cases.

Note that $ k $ may not fit in a standard 32-bit integer data type.

## 输出格式

For each test case, output the answer as an integer on a new line. If there is no way to select the dimensions of $ S $ so it fits in $ B $ , output $ 0 $ .

## 说明/提示

For the first test case, it is optimal to choose $ S $ with side lengths $ 2 $ , $ 2 $ , and $ 2 $ , which has a volume of $ 2 \cdot 2 \cdot 2 = 8 $ . It can be shown there are $ 8 $ ways to put $ S $ inside $ B $ .

The coordinate with the least $ x $ , $ y $ , and $ z $ values for each possible arrangement of $ S $ are:

1. $ (0, 0, 0) $
2. $ (1, 0, 0) $
3. $ (0, 1, 0) $
4. $ (0, 0, 1) $
5. $ (1, 0, 1) $
6. $ (1, 1, 0) $
7. $ (0, 1, 1) $
8. $ (1, 1, 1) $

The arrangement of $ S $ with a coordinate of $ (0, 0, 0) $ is depicted below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1985E/47efaaa7005bda1e805807f94ece6c58f2ba3050.png)For the second test case, $ S $ with side lengths $ 2 $ , $ 3 $ , and $ 3 $ are optimal.

## 样例 #1

### 输入

```
7
3 3 3 8
3 3 3 18
5 1 1 1
2 2 2 7
3 4 2 12
4 3 1 6
1800 1800 1800 4913000000
```

### 输出

```
8
2
5
0
4
4
1030301
```



---

---
title: "All Pairs Segments"
layout: "post"
diff: 普及-
pid: CF2019B
tag: ['排列组合']
---

# All Pairs Segments

## 题目描述

你有 $ n $ 个点，这些点位于 $ x $ 轴上，坐标为递增的正整数，分别为 $ x_1 < x_2 < \ldots < x_n $。

对于每对点 $ (i, j) $，其中 $ 1 \leq i < j \leq n $，你将绘制线段 $ [x_i, x_j] $。这些线段是闭合的，即线段 $ [a, b] $ 包含点 $ a, a+1, \ldots, b $。

你有 $ q $ 个查询。在第 $ i $ 个查询中，给定一个正整数 $ k_i $，你需要确定恰好被 $ k_i $ 条线段包含的整点有多少个。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $ t $（ $ 1 \leq t \leq 10^4 $）。接下来是每个测试用例的描述。

每个测试用例的第一行包含两个整数 $ n $ 和 $ q $（ $ 2 \leq n \leq 10^5 $， $ 1 \leq q \leq 10^5 $）——点的数量和查询的数量。

每个测试用例的第二行包含 $ n $ 个整数 $ x_1, x_2, \ldots, x_n $（ $ 1 \leq x_1 < x_2 < \ldots < x_n \leq 10^9 $）——这些点的坐标。

每个测试用例的第三行包含 $ q $ 个整数 $ k_1, k_2, \ldots, k_q $（ $ 1 \leq k_i \leq 10^{18} $）——查询的参数。

保证所有测试用例中 $ n $ 的总和不超过 $ 10^5 $，所有测试用例中 $ q $ 的总和不超过 $ 10^5 $。

## 输出格式

对于每个测试用例，输出一行包含 $ q $ 个整数：第 $ i $ 个整数是第 $ i $ 个查询的答案。


### 样例解释

在第一个例子中，你只绘制了线段 $ [101, 200] $ 。没有点恰好被 $ 2 $ 条线段包含，而有 $ 100 $ 个点 $ 101, 102, \ldots, 200 $ 恰好被 $ 1 $ 条线段包含。

在第二个例子中，你绘制了 $ 15 $ 条线段：$ [1, 2], [1, 3], [1, 5], [1, 6], [1, 7], [2, 3], [2, 5], [2, 6], [2, 7], [3, 5], [3, 6], [3, 7], [5, 6], [5, 7], [6, 7] $。点 $ 1, 7 $ 恰好被 $ 5 $ 条线段包含；点 $ 2, 4, 6 $ 恰好被 $ 9 $ 条线段包含；点 $ 3, 5 $ 恰好被 $ 11 $ 条线段包含。

## 样例 #1

### 输入

```
3
2 2
101 200
2 1
6 15
1 2 3 5 6 7
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
5 8
254618033 265675151 461318786 557391198 848083778
6 9 15 10 6 9 4 4294967300
```

### 输出

```
0 100 
0 0 0 0 2 0 0 0 3 0 2 0 0 0 0 
291716045 0 0 0 291716045 0 301749698 0
```



---

---
title: "Replace Character"
layout: "post"
diff: 普及-
pid: CF2047B
tag: ['贪心', '排列组合']
---

# Replace Character

## 题目描述

给定一个长度为 $n$ 的字符串 $s$，只包含小写英文字母。

你只能进行一次如下操作：

- 选择任意两个下标 $i$ 和 $j$ ($1\le i,j\le n$)，允许选择 $i=j$。
- 将 $s_i$ 赋值为 $s_j$。

你需要最小化 $s$ 不同排列的个数。输出在一次操作后满足条件的任何一个字符串 $s$。

字符串的一个排列是打乱其字符顺序后形成的新字符串。比如 `bac` 是 `abc` 的一个排列，而 `bcc` 不是。

## 输入格式

本题有多组数据。第一行，一个整数 $t$ ($1\le t\le 500$)，表示数据组数。

对于每组数据：

第一行，一个整数 $n$ ($1\le n\le 10$)，表示 $s$ 的长度。

第二行，一个长度为 $n$ 的字符串 $s$，只包含小写英文字母。

## 输出格式

对于每组数据，输出一次操作后满足要求的 $s$。如果有多个答案，输出任意一个即可。

翻译：[HYdroKomide](https://www.luogu.com.cn/user/299883)

## 样例 #1

### 输入

```
6
3
abc
4
xyyx
8
alphabet
1
k
10
aabbccddee
6
ttbddq
```

### 输出

```
cbc
yyyx
alphaaet
k
eabbccddee
tttddq
```



---

---
title: "Having Been a Treasurer in the Past, I Help Goblins Deceive"
layout: "post"
diff: 普及-
pid: CF2072B
tag: ['排列组合']
---

# Having Been a Treasurer in the Past, I Help Goblins Deceive

## 题目描述

完成第一个任务后，章人（Akito）离开了初始洞穴。不久后，他偶然发现了一个哥布林村落。

由于章人无处可居，他想了解房屋的价格。众所周知，哥布林将数字写作由字符 '-' 和 '\_' 组成的字符串，字符串 $ s $ 所表示的数值等于其所有等于字符串 "-\_-" 的不同子序列 $ ^{\text{∗}} $ 的数量（这与哥布林的面部特征非常相似）。

例如，字符串 $ s = $ "-\_--\_-" 表示的数值为 $ 6$，因为它包含 $ 6 $ 个 "-\_-" 子序列：

1. $ s_1 + s_2 + s_3 $
2. $ s_1 + s_2 + s_4 $
3. $ s_1 + s_2 + s_6 $
4. $ s_1 + s_5 + s_6 $
5. $ s_3 + s_5 + s_6 $
6. $ s_4 + s_5 + s_6 $

最初，哥布林在回答章人的问题时随机写了一个字符串数值 $ s$，但随后他们意识到想要从旅行者身上获取尽可能多的黄金。为此，他们要求你重新排列字符串 $ s $ 中的字符，使得该字符串所表示的数值最大化。

$ ^{\text{∗}} $ 字符串 $ a $ 的子序列是指通过删除 $ a $ 中若干（可能为 $ 0 $）个字符后得到的字符串 $ b$。若两个子序列是通过删除不同位置的字符得到的，则它们被视为不同的子序列。

## 输入格式

第一行包含一个整数 $ t $（$ 1 \le t \le 10^4$）—— 测试用例的数量。

每个测试用例的第一行包含一个整数 $ n $（$ 1 \le n \le 2 \cdot 10^5$）—— 哥布林所写字符串的长度。

每个测试用例的第二行包含一个长度为 $ n $ 的字符串 $ s$，仅由字符 '-' 和 '\_' 组成——哥布林所写的字符串。

保证所有测试用例的 $ n $ 之和不超过 $ 2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——在最优重排字符串 $ s $ 后，等于字符串 "-\_-" 的子序列的最大数量。

## 说明/提示

第一个测试用例中，最优方案是将字符重排为 "-\_-"。这是唯一一个长度为 $ 3 $ 且至少包含一个 "-\_-" 子序列的字符串。

第二个测试用例中，只有一个字符 "-"，而构成子序列 "-\_-" 至少需要两个 "-"。这意味着无论如何重排，答案都是 $ 0$。

第七和第八个测试用例中，字符串长度 $ n < 3$，这意味着长度为 $ 3 $ 的子序列不存在。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
3
--_
5
__-__
9
--__-_---
4
_--_
10
_-_-_-_-_-
7
_------
1
-
2
_-
```

### 输出

```
1
0
27
2
30
9
0
0
```



---

---
title: "Parking Lot"
layout: "post"
diff: 普及-
pid: CF630I
tag: ['排列组合']
---

# Parking Lot

## 题目描述

停车场共有 $2n-2$ 个停车位。共有 $4$ 种品牌的汽车，每种汽车的数量都远大于停车位的数量。

该公司首席执行官认为，如果停车场有 **恰好** $n$ 个连续汽车的品牌相同，则停车场会更漂亮。

给定n的值，问有多少的方案使停车场满足条件。

## 输入格式

一行，包含一个整数 $n$（$3\leq n\leq 30$）。

## 输出格式

输出一个整数，即总方案数。

## 样例 #1

### 输入

```
3

```

### 输出

```
24
```



---

