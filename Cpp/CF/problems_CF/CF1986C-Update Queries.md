---
title: "Update Queries"
layout: "post"
diff: 普及-
pid: CF1986C
tag: ['贪心']
---

# Update Queries

## 题目描述

Let's consider the following simple problem. You are given a string $ s $ of length $ n $ , consisting of lowercase Latin letters, as well as an array of indices $ ind $ of length $ m $ ( $ 1 \leq ind_i \leq n $ ) and a string $ c $ of length $ m $ , consisting of lowercase Latin letters. Then, in order, you perform the update operations, namely, during the $ i $ -th operation, you set $ s_{ind_i} = c_i $ . Note that you perform all $ m $ operations from the first to the last.

Of course, if you change the order of indices in the array $ ind $ and/or the order of letters in the string $ c $ , you can get different results. Find the lexicographically smallest string $ s $ that can be obtained after $ m $ update operations, if you can rearrange the indices in the array $ ind $ and the letters in the string $ c $ as you like.

A string $ a $ is lexicographically less than a string $ b $ if and only if one of the following conditions is met:

- $ a $ is a prefix of $ b $ , but $ a \neq b $ ;
- in the first position where $ a $ and $ b $ differ, the symbol in string $ a $ is earlier in the alphabet than the corresponding symbol in string $ b $ .

## 输入格式

Each test consists of several sets of input data. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of sets of input data. Then follows their description.

The first line of each set of input data contains two integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 10^5 $ ) — the length of the string $ s $ and the number of updates.

The second line of each set of input data contains a string $ s $ of length $ n $ , consisting of lowercase Latin letters.

The third line of each set of input data contains $ m $ integers $ ind_1, ind_2, \ldots, ind_m $ ( $ 1 \leq ind_i \leq n $ ) — the array of indices $ ind $ .

The fourth line of each set of input data contains a string $ c $ of length $ m $ , consisting of lowercase Latin letters.

It is guaranteed that the sum of $ n $ over all sets of input data does not exceed $ 2 \cdot 10^5 $ . Similarly, the sum of $ m $ over all sets of input data does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each set of input data, output the lexicographically smallest string $ s $ that can be obtained by rearranging the indices in the array $ ind $ and the letters in the string $ c $ as you like.

## 说明/提示

In the first set of input data, you can leave the array $ ind $ and the string $ c $ unchanged and simply perform all operations in that order.

In the second set of input data, you can set the array $ ind = [1, 1, 4, 2] $ and $ c = $ "zczw". Then the string $ s $ will change as follows: $ meow \rightarrow zeow \rightarrow ceow \rightarrow ceoz \rightarrow cwoz $ .

In the third set of input data, you can leave the array $ ind $ unchanged and set $ c =  $ "admn". Then the string $ s $ will change as follows: $ abacaba \rightarrow abacaba \rightarrow abdcaba \rightarrow abdcmba \rightarrow abdcmbn $ .

## 样例 #1

### 输入

```
4
1 2
a
1 1
cb
4 4
meow
1 2 1 4
zcwz
7 4
abacaba
1 3 5 7
damn
7 10
traktor
7 6 5 4 3 2 1 6 4 2
codeforces
```

### 输出

```
b
cwoz
abdcmbn
ccdeefo
```

