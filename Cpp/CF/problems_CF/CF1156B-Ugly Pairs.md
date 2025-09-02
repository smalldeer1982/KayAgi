---
title: "Ugly Pairs"
layout: "post"
diff: 提高+/省选-
pid: CF1156B
tag: []
---

# Ugly Pairs

## 题目描述

You are given a string, consisting of lowercase Latin letters.

A pair of neighbouring letters in a string is considered ugly if these letters are also neighbouring in a alphabet. For example, string "abaca" contains ugly pairs at positions $ (1, 2) $ — "ab" and $ (2, 3) $ — "ba". Letters 'a' and 'z' aren't considered neighbouring in a alphabet.

Can you rearrange the letters of a given string so that there are no ugly pairs? You can choose any order of the letters of the given string but you can't add any new letters or remove the existing ones. You can also leave the order the same.

If there are multiple answers, print any of them.

You also have to answer $ T $ separate queries.

## 输入格式

The first line contains a single integer $ T $ ( $ 1 \le T \le 100 $ ) — the number of queries.

Each of the next $ T $ lines contains string $ s $ $ (1 \le |s| \le 100) $ — the string for the next query. It is guaranteed that it contains only lowercase Latin letters.

Note that in hacks you have to set $ T = 1 $ .

## 输出格式

Print $ T $ lines. The $ i $ -th line should contain the answer to the $ i $ -th query.

If the answer for the $ i $ -th query exists, then print such a rearrangment of letters of the given string that it contains no ugly pairs. You can choose any order of the letters of the given string but you can't add any new letters or remove the existing ones. You can also leave the order the same.

If there are multiple answers, print any of them.

Otherwise print "No answer" for that query.

## 说明/提示

In the first example answer "bdac" is also correct.

The second example showcases the fact that only neighbouring in alphabet letters are not allowed. The same letter is ok.

There are lots of valid answers for the third example.

## 样例 #1

### 输入

```
4
abcd
gg
codeforces
abaca

```

### 输出

```
cadb
gg
codfoerces
No answer

```

