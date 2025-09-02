---
title: "Uppercase or Lowercase?"
layout: "post"
diff: 难度0
pid: CF2087D
tag: []
---

# Uppercase or Lowercase?

## 题目描述

This is an interactive problem.

In a certain database, there are $ n $ handles stored in the form of a numbered list. You are interested in one specific handle $ h $ , or more precisely, in its position in this list.

You can ask the database for the position $ i $ from the list, and it will return the handle at the $ i $ -th position.

All handles are non-empty strings consisting of at most $ 20 $ lowercase Latin letters, except the first one that can be either a lowercase or an uppercase Latin letter.

You know that all handles are sorted in lexicographical order, but the problem is that it is unknown whether uppercase letters are considered less than lowercase ones. In other words, you do not know if it is true that all handles starting with uppercase letters come first, followed by those starting with lowercase letters — or vice versa, that all handles starting with lowercase letters come first, followed by those starting with uppercase letters.

Lexicographical order is the order of standard string comparison, formally defined as follows:

- if strings $ s $ and $ t $ differ in some positions, the earliest of which is position $ i $ , then string $ s $ comes before string $ t $ in lexicographical order if and only if $ s_i < t_i $ (for example, for the strings cats and current, the first position with different characters is $ 2 $ , and the character a is less than the character u, so cats is lexicographically less than current);
- if strings $ s $ and $ t $ have no positions with different characters, then the shorter one comes first. For example, the string cat comes before the string cats.

Due to restricted access to the database, you can make no more than $ 10 $ queries to it. Determine the position of the handle you are interested in, knowing that it is definitely in the list.

## 输入格式

The first line contains the number $ n $ and the string $ h $ ( $ 1 \le n \le 500 $ ) — the total number of handles in the list and the handle you are searching for.

It is guaranteed that all handles are non-empty strings of no more than $ 20 $ characters, consisting only of lowercase Latin letters, except the first letter that may be an uppercase letter.

It is also guaranteed that all handles are sorted, unique, and the given handle is in the list.

## 输出格式

To ask a question, output a string in the following format (without quotes):

- "? i" ( $ 1 \le i \le n $ )

The jury will return a string $ s $ — the handle at the $ i $ -th position in the list.

When you are ready to print the answer, output a single string in the following format (without quotes):

- "! i" ( $ 1 \le i \le n $ )

 and terminate the program. Printing the answer does not count as a query.The interactor is not adaptive, which means that the list of handles in each test is fixed beforehand.

If your program asks more than $ 10 $ queries (excluding printing the answer) or violates the format of the queries, the jury will respond with the string "-1". In this case, your program should terminate immediately to receive a verdict of Wrong Answer. Otherwise, you may receive an arbitrary verdict because your solution will continue to read from a closed stream.

After printing a query, do not forget to output a newline and flush the output. Otherwise, you may receive a verdict of Idleness limit exceeded. To do this, use System.out.flush().

## 说明/提示

Note that spaces in examples are added only for improved readability. When checking solutions, the interactor will not output any empty lines.

## 样例 #1

### 输入

```
4 adedalic

Bleddest

Neon

adedalic

awoo
```

### 输出

```
? 1

? 2

? 3

? 4

! 3
```

## 样例 #2

### 输入

```
6 tourist

jiangly

tourist

Radewoosh
```

### 输出

```
? 1

? 3

? 6

! 3
```

