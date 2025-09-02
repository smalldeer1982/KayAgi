---
title: "AmShZ Wins a Bet"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1610G
tag: ['倍增', '哈希 hashing']
---

# AmShZ Wins a Bet

## 题目描述

Right before the UEFA Euro 2020, AmShZ and Safar placed bets on who'd be the champion, AmShZ betting on Italy, and Safar betting on France.

Of course, AmShZ won. Hence, Safar gave him a bracket sequence $ S $ . Note that a bracket sequence is a string made of '(' and ')' characters.

AmShZ can perform the following operation any number of times:

- First, he cuts his string $ S $ into three (possibly empty) contiguous substrings $ A, B $ and $ C $ . Then, he glues them back by using a '(' and a ')' characters, resulting in a new string $ S $ = $ A $ + "(" + $ B $ + ")" + $ C $ .For example, if $ S $ = "))((" and AmShZ cuts it into $ A $ = "", $ B $ = "))", and $ C $ = "((", He will obtain $ S $ = "()))((" as a new string.

After performing some (possibly none) operations, AmShZ gives his string to Keshi and asks him to find the initial string. Of course, Keshi might be able to come up with more than one possible initial string. Keshi is interested in finding the lexicographically smallest possible initial string.

Your task is to help Keshi in achieving his goal.

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

The only line of input contains a single string $ S $ — the string after the operations $ (1\le |S|\le 3 \cdot 10^5) $ .

It is guaranteed that the first character of $ S $ is ')'.

## 输出格式

Print the lexicographically smallest possible initial string before operations.

## 说明/提示

In the first sample, you can transform ")((())))" into ")(()(())))" by splitting it into ")(", empty string, and "(())))". It can be shown that this is the lexicographically smallest possible initial string

## 样例 #1

### 输入

```
)(()(())))
```

### 输出

```
)((())))
```

