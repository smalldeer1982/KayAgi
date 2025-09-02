---
title: "Guess One Character"
layout: "post"
diff: 普及+/提高
pid: CF2038G
tag: ['数学']
---

# Guess One Character

## 题目描述

This is an interactive problem. You have to use flush operation right after printing each line. For example, in C++ you should use the function fflush(stdout) or cout.flush(), in Java or Kotlin — System.out.flush(), and in Python — sys.stdout.flush().

The jury has a string $ s $ consisting of characters 0 and/or 1. The length of this string is $ n $ .

You can ask the following queries:

- $ 1 $ $ t $ — "how many times does $ t $ appear in $ s $ as a contiguous substring?" Here, $ t $ should be a string consisting of characters 0 and/or 1; its length should be at least $ 1 $ and at most $ n $ . For example, if the string $ s $ is 111011 and the string $ t $ is 11, the response to the query is $ 3 $ .

You have to guess at least one character in the string $ s $ by asking no more than $ 3 $ queries. Note that giving the answer does not count as a query.

In every test and in every test case, the string $ s $ is fixed beforehand.

## 输出格式

Initially, the jury program sends one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

At the start of each test case, the jury program sends one integer $ n $ ( $ 2 \le n \le 50 $ ) — the length of the string.

After that, your program can submit queries to the jury program by printing the following line (do not forget to flush the output after printing a line!):

- $ 1 $ $ t $ means asking a query "how many times does $ t $ appear in $ s $ as a contiguous substring?"

For every query, the jury prints one integer on a separate line. It is either:

- the answer to your query, if the query is correct, and you haven't exceeded the query limit;
- or the integer $ -1 $ , if your query is incorrect (for example, the constraint $ 1 \le |t| \le n $ is not met or the string $ t $ contains characters other than 0 and 1) or if you have asked too many queries while processing the current test case.

To submit the answer, your program should send a line in the following format (do not forget to flush the output after printing a line!):

- $ 0 $ $ i $ $ c $ , where $ 1 \le i \le n $ and $ c $ is either 0 or 1, meaning that $ s_i = c $ .

If your guess is correct, the jury program will print one integer $ 1 $ on a separate line, indicating that you may proceed to the next test case (or terminate the program, if it was the last test case) and that the number of queries you have asked is reset. If it is not correct, the jury program will print one integer $ -1 $ on a separate line.

After your program receives $ -1 $ as the response, it should immediately terminate. This will lead to your submission receiving the verdict "Wrong Answer". If your program does not terminate, the verdict of your submission is undefined.

## 说明/提示

In the example, there are $ 3 $ test cases: 101, 11 and 10. Note that everything after the // sign is a comment that explains which line means what in the interaction. The jury program won't print these comments in the actual problem, and you shouldn't print them. The empty lines are also added for your convenience, the jury program won't print them, and your solution should not print any empty lines.

## 样例 #1

### 输入

```
3     // 3 test cases
3     // the length of the string is 3

1     // 101 occurs once

1     // guessed correctly
2     // the length of the string is 2

0     // 00 occurs zero times

0     // 0 occurs zero times

1     // guessed correctly
2     // the length of the string is 2

1     // 1 occurs once

0     // 01 occurs zero times

1     // guessed correctly
```

### 输出

```
1 101 // how many times 101 occurs

0 2 0 // guess: s[2] is 0


1 00  // how many times 00 occurs

1 0   // how many times 0 occurs

0 1 1 // guess: s[1] is 1


1 1   // how many times 1 occurs

1 01  // how many times 01 occurs

0 2 0 // guess: s[2] is 0
```

