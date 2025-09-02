---
title: "JGTLE - Jalil Got TLE"
layout: "post"
diff: 普及/提高-
pid: SP34011
tag: ['数学', '枚举']
---

# JGTLE - Jalil Got TLE

## 题目描述

Ananta Jalil 是一个多才多艺的人。他可以完成任何对别人来说不可能的任务。最近，他学会了编程基础。在一个问题中，他提交了以下解决方案：

```cpp
#include <stdio.h>

int main()
{
   int t;
   scanf("%d", &t);
   for(int tc = 1; tc <= t; ++tc) {
       int a, b, c;
       scanf("%d %d %d", &a, &b, &c);
       long long result = 0;
       for(int i = 1; i <= a; ++i) {
           for(int j = 1; j <= b; ++j) {
               for(int k = 1; k <= c; ++k) {
                   result += j * k;
               }
           }
       }
       printf("Case %d: %lld\n", tc, result);
   }
   return 0;
}
```

但由于他是编程新手，他得到了 TLE（Time Limit Exceeded，超出时间限制）。因此他的解决方案效率不高。所以，你需要为 Jalil 编写一个优化的解决方案，以获得相同的输出。

## 输入格式

输入的第一行将包含一个正整数 $T$，表示测试用例的数量。

在每个测试用例中，将有 $3$ 个正整数 $a$、$b$ 和 $c$。

## 输出格式

对于每个测试用例，打印与上述程序相同的输出。


---

Translated by User 735713.

## 样例 #1

### 输入

```
3
1 4 3
3 4 2
143 342 777
```

### 输出

```
Case 1: 60
Case 2: 90
Case 3: 2535110464887
```



---

---
title: "ABCDEF - ABCDEF"
layout: "post"
diff: 普及/提高-
pid: SP4580
tag: ['搜索', '枚举']
---

# ABCDEF - ABCDEF

## 题目描述

You are given a set S of integers between -30000 and 30000 (inclusive).

Find the total number of sextuples ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP4580/60da4a6ec7452a0168508bec756f9c6a0109d346.png) that satisfy:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP4580/5ae23b14079f628cec1090fc74b452939c2ffbe4.png)

### Input

The first line contains integer N (1

Elements of S are given in the next N lines, one integer per line. Given numbers will be distinct.

## 输出格式

Output the total number of plausible sextuples.

## 样例 #1

### 输入

```
1
1

```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
2
3

```

### 输出

```
4
```

## 样例 #3

### 输入

```
2
-1
1

```

### 输出

```
24
```

## 样例 #4

### 输入

```
3
5
7
10

```

### 输出

```
10
```



---

---
title: "PALIN - The Next Palindrome"
layout: "post"
diff: 普及/提高-
pid: SP5
tag: ['字符串', '数学', '枚举']
---

# PALIN - The Next Palindrome

## 题目描述

A positive integer is called a _palindrome_ if its representation in the decimal system is the same when read from left to right and from right to left. For a given positive integer _K_ of not more than 1000000 digits, write the value of the smallest palindrome larger than _K_ to output. Numbers are always displayed without leading zeros.

## 输入格式

The first line contains integer _t_, the number of test cases. Integers _K_ are given in the next _t_ lines.

## 输出格式

For each _K_, output the smallest palindrome larger than _K_.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages**

## 样例 #1

### 输入

```
2

808

2133
```

### 输出

```
818

2222
```



---

---
title: "NOSQ - No Squares Numbers"
layout: "post"
diff: 普及/提高-
pid: SP8496
tag: ['枚举', '素数判断,质数,筛法']
---

# NOSQ - No Squares Numbers

## 题目描述

A square free number is defined as a number which is not divisible by any square number.

For example, 13, 15, 210 are square free numbers, where as 25 (divisible by 5\*5), 108 (divisible by 6\*6), 18 (divisible by 3\*3) are not square free numbers. However number 1 is not considered to be a square and is a squarefree number.

Now you must find how many numbers from number a to b, are square free and also have a digit d inside it.

For example for in the range 10 to 40 te squarefree numbers having digit 3 are 13, 23, 30, 31, 33, 34, 35, 37, 38, 39

## 输入格式

The first line contains an integer T, which is the number of test-cases

Then follow T lines, each containing 3 integers a, b and d.

1 <= T <= 20,000

1 <= a <= b <= 100,000

0 <= d <= 9

## 输出格式

Print one integer which is the required number as described in the problem statement.

## 样例 #1

### 输入

```
3
10 40 3
1 100 4
1 100000 7
```

### 输出

```
10
9
26318
```



---

