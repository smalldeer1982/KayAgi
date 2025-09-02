---
title: "Packets"
layout: "post"
diff: 普及-
pid: CF1037A
tag: ['数学', '枚举', '进制']
---

# Packets

## 题目描述

你有$n$个硬币，每个硬币价值都为$1$。

你要把它们分成若干个小包裹，使得在$1$与$n$之间的所有面额都能用这其中某几个小包裹凑出。

每个小包裹只能作为一个整体使用。

请求出最少要分几个包裹。

## 输入格式

一个数$n$($1\le n\le 10^9$)。

## 输出格式

输出最少要分几个包裹。

### 样例解释1：

分成$3$个包裹：$[1,2,3]$，可以凑出$1$到$6$中所有的面额。

## 样例 #1

### 输入

```
6

```

### 输出

```
3
```

## 样例 #2

### 输入

```
2

```

### 输出

```
2
```



---

---
title: "Numbers"
layout: "post"
diff: 普及-
pid: CF13A
tag: ['模拟', '最大公约数 gcd', '进制']
---

# Numbers

## 题目描述

Little Petya likes numbers a lot. He found that number 123 in base 16 consists of two digits: the first is 7 and the second is 11. So the sum of digits of 123 in base 16 is equal to 18.

Now he wonders what is an average value of sum of digits of the number $ A $ written in all bases from $ 2 $ to $ A-1 $ .

Note that all computations should be done in base 10. You should find the result as an irreducible fraction, written in base 10.

## 输入格式

Input contains one integer number $ A $ ( $ 3<=A<=1000 $ ).

## 输出格式

Output should contain required average value in format «X/Y», where X is the numerator and Y is the denominator.

## 说明/提示

In the first sample number 5 written in all bases from 2 to 4 looks so: 101, 12, 11. Sums of digits are 2, 3 and 2, respectively.

## 样例 #1

### 输入

```
5

```

### 输出

```
7/3

```

## 样例 #2

### 输入

```
3

```

### 输出

```
2/1

```



---

---
title: "Binary Colouring"
layout: "post"
diff: 普及-
pid: CF1977B
tag: ['进制']
---

# Binary Colouring

## 题目描述

You are given a positive integer $ x $ . Find any array of integers $ a_0, a_1, \ldots, a_{n-1} $ for which the following holds:

- $ 1 \le n \le 32 $ ,
- $ a_i $ is $ 1 $ , $ 0 $ , or $ -1 $ for all $ 0 \le i \le n - 1 $ ,
- $ x = \displaystyle{\sum_{i=0}^{n - 1}{a_i \cdot 2^i}} $ ,
- There does not exist an index $ 0 \le i \le n - 2 $ such that both $ a_{i} \neq 0 $ and $ a_{i + 1} \neq 0 $ .

It can be proven that under the constraints of the problem, a valid array always exists.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The only line of each test case contains a single positive integer $ x $ ( $ 1 \le x < 2^{30} $ ).

## 输出格式

For each test case, output two lines.

On the first line, output an integer $ n $ ( $ 1 \le n \le 32 $ ) — the length of the array $ a_0, a_1, \ldots, a_{n-1} $ .

On the second line, output the array $ a_0, a_1, \ldots, a_{n-1} $ .

If there are multiple valid arrays, you can output any of them.

## 说明/提示

In the first test case, one valid array is $ [1] $ , since $ (1) \cdot 2^0 = 1 $ .

In the second test case, one possible valid array is $ [0,-1,0,0,1] $ , since $ (0) \cdot 2^0 + (-1) \cdot 2^1 + (0) \cdot 2^2 + (0) \cdot 2^3 + (1) \cdot 2^4 = -2 + 16 = 14 $ .

## 样例 #1

### 输入

```
7
1
14
24
15
27
11
19
```

### 输出

```
1
1
5
0 -1 0 0 1
6
0 0 0 -1 0 1
5
-1 0 0 0 1
6
-1 0 -1 0 0 1
5
-1 0 -1 0 1
5
-1 0 1 0 1
```



---

---
title: "Spreadsheets"
layout: "post"
diff: 普及-
pid: CF1B
tag: ['模拟', '字符串', '进制']
---

# Spreadsheets

## 题目描述

In the popular spreadsheets systems (for example, in Excel) the following numeration of columns is used. The first column has number A, the second — number B, etc. till column 26 that is marked by Z. Then there are two-letter numbers: column 27 has number AA, 28 — AB, column 52 is marked by AZ. After ZZ there follow three-letter numbers, etc.

The rows are marked by integer numbers starting with 1. The cell name is the concatenation of the column and the row numbers. For example, BC23 is the name for the cell that is in column 55, row 23.

Sometimes another numeration system is used: RXCY, where X and Y are integer numbers, showing the column and the row numbers respectfully. For instance, R23C55 is the cell from the previous example.

Your task is to write a program that reads the given sequence of cell coordinates and produce each item written according to the rules of another numeration system.


## 输入格式

The first line of the input contains integer number $ n $ ( $ 1<=n<=10^{5} $ ), the number of coordinates in the test. Then there follow $ n $ lines, each of them contains coordinates. All the coordinates are correct, there are no cells with the column and/or the row numbers larger than $ 10^{6} $ .


## 输出格式

Write $ n $ lines, each line should contain a cell coordinates in the other numeration system.


## 样例 #1

### 输入

```
2
R23C55
BC23

```

### 输出

```
BC23
R23C55

```



---

---
title: "Sum"
layout: "post"
diff: 普及-
pid: CF49B
tag: ['字符串', '进制', '位运算']
---

# Sum

## 题目描述

Vasya终于学会了进位制，但他经常忘记写算式的基数。有一次，他看到他的笔记本上写着a+b=？，但是没有写明基数。现在Vasya认为算式的基数为p。他知道算式在不同的基数下，会有不同的结果，甚至在有些基数下是没有意义的。算式78+87的值在十六进制下为FF，在十五进制下为110，十进制下为165，九进制下为176，更小的基数下就没有意义了。现在，Vasya想要知道算式结果的最大长度。
我们定义数字的长度为数字的字符个数，在不同的进制下，同一个数字有不同的数字长度。

## 输入格式

共一行，包含两个数a，b。

## 输出格式

共一行，输出算式的最大长度。

Translated by @handahao

## 样例 #1

### 输入

```
78 87

```

### 输出

```
3

```

## 样例 #2

### 输入

```
1 1

```

### 输出

```
2

```



---

---
title: "New Year's Eve"
layout: "post"
diff: 普及-
pid: CF912B
tag: ['贪心', '进制', '位运算']
---

# New Year's Eve

## 题目描述

Since Grisha behaved well last year, at New Year's Eve he was visited by Ded Moroz who brought an enormous bag of gifts with him! The bag contains $ n $ sweet candies from the good ol' bakery, each labeled from $ 1 $ to $ n $ corresponding to its tastiness. No two candies have the same tastiness.

The choice of candies has a direct effect on Grisha's happiness. One can assume that he should take the tastiest ones — but no, the holiday magic turns things upside down. It is the xor-sum of tastinesses that matters, not the ordinary sum!

A xor-sum of a sequence of integers $ a_{1},a_{2},...,a_{m} $ is defined as the bitwise XOR of all its elements: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/475d3a054d8c211f23a68d652dd85385e5ab9fc9.png), here ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/4298d47c0191af3c0a3103f431751061bc7e2362.png) denotes the bitwise XOR operation; more about bitwise XOR can be found [here.](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

Ded Moroz warned Grisha he has more houses to visit, so Grisha can take no more than $ k $  candies from the bag. Help Grisha determine the largest xor-sum (largest xor-sum means maximum happiness!) he can obtain.

## 输入格式

The sole string contains two integers $ n $ and $ k $ ( $ 1<=k<=n<=10^{18} $ ).

## 输出格式

Output one number — the largest possible xor-sum.

## 说明/提示

In the first sample case, one optimal answer is $ 1 $ , $ 2 $ and $ 4 $ , giving the xor-sum of $ 7 $ .

In the second sample case, one can, for example, take all six candies and obtain the xor-sum of $ 7 $ .

## 样例 #1

### 输入

```
4 3

```

### 输出

```
7

```

## 样例 #2

### 输入

```
6 6

```

### 输出

```
7

```



---

---
title: "Jamie and Alarm Snooze"
layout: "post"
diff: 普及-
pid: CF916A
tag: ['进制', '概率论']
---

# Jamie and Alarm Snooze

## 题目描述

Jamie loves sleeping. One day, he decides that he needs to wake up at exactly $ hh:mm $ . However, he hates waking up, so he wants to make waking up less painful by setting the alarm at a lucky time. He will then press the snooze button every $ x $ minutes until $ hh:mm $ is reached, and only then he will wake up. He wants to know what is the smallest number of times he needs to press the snooze button.

A time is considered lucky if it contains a digit ' $ 7 $ '. For example, $ 13:07 $ and $ 17:27 $ are lucky, while $ 00:48 $ and $ 21:34 $ are not lucky.

Note that it is not necessary that the time set for the alarm and the wake-up time are on the same day. It is guaranteed that there is a lucky time Jamie can set so that he can wake at $ hh:mm $ .

Formally, find the smallest possible non-negative integer $ y $ such that the time representation of the time $ x·y $ minutes before $ hh:mm $ contains the digit ' $ 7 $ '.

Jamie uses 24-hours clock, so after $ 23:59 $ comes $ 00:00 $ .

## 输入格式

The first line contains a single integer $ x $ ( $ 1<=x<=60 $ ).

The second line contains two two-digit integers, $ hh $ and $ mm $ ( $ 00<=hh<=23,00<=mm<=59 $ ).

## 输出格式

Print the minimum number of times he needs to press the button.

## 说明/提示

In the first sample, Jamie needs to wake up at 11:23. So, he can set his alarm at 11:17. He would press the snooze button when the alarm rings at 11:17 and at 11:20.

In the second sample, Jamie can set his alarm at exactly at 01:07 which is lucky.

## 样例 #1

### 输入

```
3
11 23

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
01 07

```

### 输出

```
0

```



---

---
title: "Hexadecimal's Numbers"
layout: "post"
diff: 普及-
pid: CF9C
tag: ['递归', '枚举', '进制', '队列']
---

# Hexadecimal's Numbers

## 题目描述

One beautiful July morning a terrible thing happened in Mainframe: a mean virus Megabyte somehow got access to the memory of his not less mean sister Hexadecimal. He loaded there a huge amount of $ n $ different natural numbers from 1 to $ n $ to obtain total control over her energy.

But his plan failed. The reason for this was very simple: Hexadecimal didn't perceive any information, apart from numbers written in binary format. This means that if a number in a decimal representation contained characters apart from 0 and 1, it was not stored in the memory. Now Megabyte wants to know, how many numbers were loaded successfully.

## 输入格式

Input data contains the only number $ n $ ( $ 1<=n<=10^{9} $ ).

## 输出格式

Output the only number — answer to the problem.

## 说明/提示

For $ n $ = 10 the answer includes numbers 1 and 10.

## 样例 #1

### 输入

```
10

```

### 输出

```
2
```



---

