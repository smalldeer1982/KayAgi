---
title: "ace5 and Task Order"
layout: "post"
diff: 提高+/省选-
pid: CF1918E
tag: []
---

# ace5 and Task Order

## 题目描述

This is an interactive problem!

In the new round, there were $ n $ tasks with difficulties from $ 1 $ to $ n $ . The coordinator, who decided to have the first round with tasks in unsorted order of difficulty, rearranged the tasks, resulting in a permutation of difficulties from $ 1 $ to $ n $ . After that, the coordinator challenged ace5 to guess the permutation in the following way.

Initially, the coordinator chooses a number $ x $ from $ 1 $ to $ n $ .

ace5 can make queries of the form: $ ?\ i $ . The answer will be:

- $ > $ , if $ a_i > x $ , after which $ x $ increases by $ 1 $ .
- $ < $ , if $ a_i < x $ , after which $ x $ decreases by $ 1 $ .
- $ = $ , if $ a_i = x $ , after which $ x $ remains unchanged.

The task for ace5 is to guess the permutation in no more than $ 40n $ queries. Since ace5 is too busy writing the announcement, he has entrusted this task to you.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

## 输出格式

The interaction between your program and the jury's program begins with reading a positive integer $ n $ ( $ 1 \leq n \leq 2000 $ ) — the length of the hidden permutation.

To make a query, output a line in the format "? i", where $ 1 \leq i \leq n $ .

As an answer, you will receive:

- "&gt;", if $ a_i $ &gt; $ x $ , after which $ x $ will increase by $ 1 $ .
- "&lt;", if $ a_i $ &lt; $ x $ , after which $ x $ will decrease by $ 1 $ .
- "=", if $ a_i $ = $ x $ , after which $ x $ will remain unchanged.

You can make no more than $ 40n $ queries. To output the answer, you need to print "! a\_1 a\_2 ... a\_n", where $ 1 \leq a_i \leq n $ , and all of them are distinct. Outputting the answer does not count as a query.

If your program makes more than $ 40n $ queries for one test case, or makes an invalid query, then the response to the query will be -1. After receiving such a response, your program should immediately terminate to receive the verdict Wrong Answer. Otherwise, it may receive any other verdict.

After outputting a query, do not forget to print a newline and flush the output buffer. Otherwise, you will receive the verdict Presentation Error. To flush the buffer, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see the documentation for other languages.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

The interactor in this problem is not adaptive.

Hacks:

To make a hack, use the following format:

The first line contains a single integer $ t $ — the number of test cases.

The description of each test case should consist of two lines. The first line contains the numbers $ n $ and $ x $ ( $ 1 \leq x \leq n \leq 2000 $ ) — the length of the hidden permutation and the initial value of the number $ x $ . The second line contains $ n $ distinct numbers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq n $ ) — the permutation that the jury should choose in this test case.

Sum of $ n $ over all test cases should not exceed $ 2000 $ .

## 说明/提示

In the first test, the hidden permutation is $ a $ = \[ $ 2,4,1,5,3 $ \], and the initial value of $ x $ is $ 3 $ .

In the second test, the hidden permutation is $ a $ = \[ $ 2,1 $ \], and the initial value of $ x $ is $ 1 $ .

## 样例 #1

### 输入

```
2
5

>

=

<

=

<

<

2

>
```

### 输出

```
? 4

? 2

? 1

? 5

? 1

? 3

! 2 4 1 5 3

? 1

! 2 1
```

