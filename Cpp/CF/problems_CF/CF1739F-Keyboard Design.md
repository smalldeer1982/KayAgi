---
title: "Keyboard Design"
layout: "post"
diff: 省选/NOI-
pid: CF1739F
tag: []
---

# Keyboard Design

## 题目描述

Monocarp has a dictionary of $ n $ words, consisting of $ 12 $ first letters of the Latin alphabet. The words are numbered from $ 1 $ to $ n $ . In every pair of adjacent characters in each word, the characters are different. For every word $ i $ , Monocarp also has an integer $ c_i $ denoting how often he uses this word.

Monocarp wants to design a keyboard that would allow him to type some of the words easily. A keyboard can be denoted as a sequence of $ 12 $ first letters of the Latin alphabet, where each letter from a to l appears exactly once.

A word can be typed with the keyboard easily if, for every pair of adjacent characters in the word, these characters are adjacent in the keyboard as well. The optimality of the keyboard is the sum of $ c_i $ over all words $ i $ that can be typed easily with it.

Help Monocarp to design a keyboard with the maximum possible optimality.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 1000 $ ) — the number of words.

Then, $ n $ lines follow. The $ i $ -th of them contains an integer $ c_i $ ( $ 1 \le c_i \le 10^5 $ ) and a string $ s_i $ ( $ 2 \le |s_i| \le 2000 $ ) denoting the $ i $ -th word. Each character of $ s_i $ is one of $ 12 $ first letters of Latin alphabet, in lowercase. For every $ j \in [1, |s_i| - 1] $ , the $ j $ -th character of $ s_i $ is different from the $ (j+1) $ -th one.

Additional constraint on the input: $ \sum \limits_{i=1}^{n} |s_i| \le 2000 $ .

## 输出格式

Print a sequence of $ 12 $ first letters of the Latin alphabet, where each letter from a to l appears exactly once, denoting the optimal keyboard. If there are multiple answers, you may print any of them.

## 样例 #1

### 输入

```
3
7 abacaba
10 cba
4 db
```

### 输出

```
hjkildbacefg
```

## 样例 #2

### 输入

```
1
100 abca
```

### 输出

```
abcdefghijkl
```

