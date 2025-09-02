---
title: "Cifera"
layout: "post"
diff: 入门
pid: CF114A
tag: ['模拟', '枚举', '进制']
---

# Cifera

## 题目描述

When Petya went to school, he got interested in large numbers and what they were called in ancient times. For instance, he learned that the Russian word "tma" (which now means "too much to be counted") used to stand for a thousand and "tma tmyschaya" (which literally means "the tma of tmas") used to stand for a million.

Petya wanted to modernize the words we use for numbers and invented a word petricium that represents number $ k $ . Moreover, petricium la petricium stands for number $ k^{2} $ , petricium la petricium la petricium stands for $ k^{3} $ and so on. All numbers of this form are called petriciumus cifera, and the number's importance is the number of articles la in its title.

Petya's invention brought on a challenge that needed to be solved quickly: does some number $ l $ belong to the set petriciumus cifera? As Petya is a very busy schoolboy he needs to automate the process, he asked you to solve it.

## 输入格式

The first input line contains integer number $ k $ , the second line contains integer number $ l $ ( $ 2<=k,l<=2^{31}-1 $ ).

## 输出格式

You should print in the first line of the output "YES", if the number belongs to the set petriciumus cifera and otherwise print "NO". If the number belongs to the set, then print on the seconds line the only number — the importance of number $ l $ .

## 样例 #1

### 输入

```
5
25

```

### 输出

```
YES
1

```

## 样例 #2

### 输入

```
3
8

```

### 输出

```
NO

```



---

---
title: "Find Minimum Operations"
layout: "post"
diff: 入门
pid: CF2020A
tag: ['数学', '进制']
---

# Find Minimum Operations

## 题目描述

You are given two integers $ n $ and $ k $ .

In one operation, you can subtract any power of $ k $ from $ n $ . Formally, in one operation, you can replace $ n $ by $ (n-k^x) $ for any non-negative integer $ x $ .

Find the minimum number of operations required to make $ n $ equal to $ 0 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The only line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 10^9 $ ).

## 输出格式

For each test case, output the minimum number of operations on a new line.

## 说明/提示

In the first test case, $ n = 5 $ and $ k = 2 $ . We can perform the following sequence of operations:

1. Subtract $ 2^0 = 1 $ from $ 5 $ . The current value of $ n $ becomes $ 5 - 1 = 4 $ .
2. Subtract $ 2^2 = 4 $ from $ 4 $ . The current value of $ n $ becomes $ 4 - 4 = 0 $ .

It can be shown that there is no way to make $ n $ equal to $ 0 $ in less than $ 2 $ operations. Thus, $ 2 $ is the answer.

In the second test case, $ n = 3 $ and $ k = 5 $ . We can perform the following sequence of operations:

1. Subtract $ 5^0 = 1 $ from $ 3 $ . The current value of $ n $ becomes $ 3 - 1 = 2 $ .
2. Subtract $ 5^0 = 1 $ from $ 2 $ . The current value of $ n $ becomes $ 2 - 1 = 1 $ .
3. Subtract $ 5^0 = 1 $ from $ 1 $ . The current value of $ n $ becomes $ 1 - 1 = 0 $ .

It can be shown that there is no way to make $ n $ equal to $ 0 $ in less than $ 3 $ operations. Thus, $ 3 $ is the answer.

## 样例 #1

### 输入

```
6
5 2
3 5
16 4
100 3
6492 10
10 1
```

### 输出

```
2
3
1
4
21
10
```



---

---
title: "Even Odds"
layout: "post"
diff: 入门
pid: CF318A
tag: ['模拟', '进制', '位运算']
---

# Even Odds

## 题目描述

## 题目大意

作为一个不顺从的人， $Volodya$  不喜欢当前的事物状态，特别是自然数的顺序（自然数是正整数）。他决心重新安排他们。但是自然数太多，所以 $Volodya$ 决定从 $n$ 开始。他写出下面的数列：首先是从1到 $n$ 的所有奇数整数（以升序排列），然后从1到 $n$ 的所有偶数整数（也按升序排列）。帮助我们的英雄找出：第 $k$ 个数字是多少

## 输入格式

输入一行包含整数n和k（1 <＝k<＝n<＝10^12）

请不要使用%lld说明符来读取或写入C++中的64位整数。最好使用cin、cut流或%I64d说明符。

翻译提供者：蒟蒻烟雨平生

## 样例 #1

### 输入

```
10 3

```

### 输出

```
5
```

## 样例 #2

### 输入

```
7 7

```

### 输出

```
6
```



---

---
title: "Div. 64"
layout: "post"
diff: 入门
pid: CF887A
tag: ['字符串', '数学', '进制']
---

# Div. 64

## 题目描述

超模$Izabella$ 参加了比赛。她想要给评委留下深刻的印象并且展示她的数学技能。

她的问题如下：对于一个只由$0$ 和$1$ 组成的字符串，判断是否能删掉一些数字，使得得到的二进制数能被$64$ 整除。

## 输入格式

一行，为一个长度不超过$100$ 的$01$ 字符串。

## 输出格式

如果可以，输出$yes$ ，否则输出$no$ 。

感谢@M_sea 提供的翻译

## 样例 #1

### 输入

```
100010001

```

### 输出

```
yes
```

## 样例 #2

### 输入

```
100

```

### 输出

```
no
```



---

