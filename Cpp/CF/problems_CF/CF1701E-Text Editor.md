---
title: "Text Editor"
layout: "post"
diff: 提高+/省选-
pid: CF1701E
tag: ['动态规划 DP']
---

# Text Editor

## 题目描述

You wanted to write a text $ t $ consisting of $ m $ lowercase Latin letters. But instead, you have written a text $ s $ consisting of $ n $ lowercase Latin letters, and now you want to fix it by obtaining the text $ t $ from the text $ s $ .

Initially, the cursor of your text editor is at the end of the text $ s $ (after its last character). In one move, you can do one of the following actions:

- press the "left" button, so the cursor is moved to the left by one position (or does nothing if it is pointing at the beginning of the text, i. e. before its first character);
- press the "right" button, so the cursor is moved to the right by one position (or does nothing if it is pointing at the end of the text, i. e. after its last character);
- press the "home" button, so the cursor is moved to the beginning of the text (before the first character of the text);
- press the "end" button, so the cursor is moved to the end of the text (after the last character of the text);
- press the "backspace" button, so the character before the cursor is removed from the text (if there is no such character, nothing happens).

Your task is to calculate the minimum number of moves required to obtain the text $ t $ from the text $ s $ using the given set of actions, or determine it is impossible to obtain the text $ t $ from the text $ s $ .

You have to answer $ T $ independent test cases.

## 输入格式

The first line of the input contains one integer $ T $ ( $ 1 \le T \le 5000 $ ) — the number of test cases. Then $ T $ test cases follow.

The first line of the test case contains two integers $ n $ and $ m $ ( $ 1 \le m \le n \le 5000 $ ) — the length of $ s $ and the length of $ t $ , respectively.

The second line of the test case contains the string $ s $ consisting of $ n $ lowercase Latin letters.

The third line of the test case contains the string $ t $ consisting of $ m $ lowercase Latin letters.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5000 $ ( $ \sum n \le 5000 $ ).

## 输出格式

For each test case, print one integer — the minimum number of moves required to obtain the text $ t $ from the text $ s $ using the given set of actions, or -1 if it is impossible to obtain the text $ t $ from the text $ s $ in the given test case.

## 样例 #1

### 输入

```
6
9 4
aaaaaaaaa
aaaa
7 3
abacaba
aaa
5 4
aabcd
abcd
4 2
abba
bb
6 4
baraka
baka
8 7
question
problem
```

### 输出

```
5
6
3
4
4
-1
```

