---
title: "The penguin's game"
layout: "post"
diff: 省选/NOI-
pid: CF835E
tag: []
---

# The penguin's game

## 题目描述

Pay attention: this problem is interactive.

Penguin Xoriy came up with a new game recently. He has $ n $ icicles numbered from $ 1 $ to $ n $ . Each icicle has a temperature — an integer from $ 1 $ to $ 10^{9} $ . Exactly two of these icicles are special: their temperature is $ y $ , while a temperature of all the others is $ x≠y $ . You have to find those special icicles. You can choose a non-empty subset of icicles and ask the penguin what is the bitwise exclusive OR (XOR) of the temperatures of the icicles in this subset. Note that you can't ask more than 19 questions.

You are to find the special icicles.

## 输入格式

The first line contains three integers $ n $ , $ x $ , $ y $ ( $ 2<=n<=1000 $ , $ 1<=x,y<=10^{9} $ , $ x≠y $ ) — the number of icicles, the temperature of non-special icicles and the temperature of the special icicles.

## 输出格式

To give your answer to the penguin you have to print character "!" (without quotes), then print two integers $ p_{1} $ , $ p_{2} $ ( $ p_{1}&lt;p_{2} $ ) — the indexes of the special icicles in ascending order. Note that "!" and $ p_{1} $ should be separated by a space; the indexes should be separated by a space too. After you gave the answer your program should terminate immediately.

Interaction

To ask a question print character "?" (without quotes), an integer $ c $ ( $ 1<=c<=n $ ), and $ c $ distinct integers $ p_{1} $ , $ p_{2} $ , ..., $ p_{c} $ ( $ 1<=p_{i}<=n $ ) — the indexes of icicles that you want to know about. Note that "?" and $ c $ should be separated by a space; the indexes should be separated by a space too.

After you asked the question, read a single integer — the answer.

Note that you can't ask more than 19 questions. If you ask more than 19 questions or at least one incorrect question, your solution will get "Wrong answer".

If at some moment your program reads $ -1 $ as an answer, it should immediately exit (for example, by calling exit(0)). You will get "Wrong answer" in this case, it means that you asked more than 19 questions, or asked an invalid question. If you ignore this, you can get other verdicts since your program will continue to read from a closed stream.

Your solution will get "Idleness Limit Exceeded", if you don't print anything or forget to flush the output, including for the final answer .

To flush you can use (just after printing):

- fflush(stdout) in C++;
- System.out.flush() in Java;
- stdout.flush() in Python;
- flush(output) in Pascal;
- For other languages see the documentation.

Hacking

For hacking use the following format:

 $ n $ $ x $ $ y $ $ p_{1} $ $ p_{2} $

Here $ 1<=p_{1}&lt;p_{2}<=n $ are the indexes of the special icicles.

Contestant programs will not be able to see this input.

## 说明/提示

The answer for the first question is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF835E/3579feff85b3a33a65d7529a532f9fbb51cc40c4.png).

The answer for the second and the third questions is 1, therefore, special icicles are indexes 1 and 3.

You can read more about bitwise XOR operation here: [https://en.wikipedia.org/wiki/Bitwise\_operation#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 样例 #1

### 输入

```
4 2 1
2
1
1
```

### 输出

```
? 3 1 2 3
? 1 1
? 1 3
! 1 3
```

