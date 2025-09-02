---
title: "String Game"
layout: "post"
diff: 普及/提高-
pid: CF778A
tag: ['字符串', '排序']
---

# String Game

## 题目描述

Little Nastya has a hobby, she likes to remove some letters from word, to obtain another word. But it turns out to be pretty hard for her, because she is too young. Therefore, her brother Sergey always helps her.

Sergey gives Nastya the word $ t $ and wants to get the word $ p $ out of it. Nastya removes letters in a certain order (one after another, in this order strictly), which is specified by permutation of letters' indices of the word $ t $ : $ a_{1}...\ a_{|t|} $ . We denote the length of word $ x $ as $ |x| $ . Note that after removing one letter, the indices of other letters don't change. For example, if $ t= $ "nastya" and $ a=[4,1,5,3,2,6] $ then removals make the following sequence of words "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya".

Sergey knows this permutation. His goal is to stop his sister at some point and continue removing by himself to get the word $ p $ . Since Nastya likes this activity, Sergey wants to stop her as late as possible. Your task is to determine, how many letters Nastya can remove before she will be stopped by Sergey.

It is guaranteed that the word $ p $ can be obtained by removing the letters from word $ t $ .

## 输入格式

The first and second lines of the input contain the words $ t $ and $ p $ , respectively. Words are composed of lowercase letters of the Latin alphabet ( $ 1<=|p|&lt;|t|<=200000 $ ). It is guaranteed that the word $ p $ can be obtained by removing the letters from word $ t $ .

Next line contains a permutation $ a_{1},a_{2},...,a_{|t|} $ of letter indices that specifies the order in which Nastya removes letters of $ t $ ( $ 1<=a_{i}<=|t| $ , all $ a_{i} $ are distinct).

## 输出格式

Print a single integer number, the maximum number of letters that Nastya can remove.

## 说明/提示

In the first sample test sequence of removing made by Nastya looks like this:

"ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba"

Nastya can not continue, because it is impossible to get word "abb" from word "ababcba".

So, Nastya will remove only three letters.

## 样例 #1

### 输入

```
ababcba
abb
5 3 4 1 7 6 2

```

### 输出

```
3
```

## 样例 #2

### 输入

```
bbbabb
bb
1 6 3 4 2 5

```

### 输出

```
4
```

