---
title: "Did We Get Everything Covered?"
layout: "post"
diff: 普及/提高-
pid: CF1924A
tag: ['贪心']
---

# Did We Get Everything Covered?

## 题目描述

You are given two integers $ n $ and $ k $ along with a string $ s $ .

Your task is to check whether all possible strings of length $ n $ that can be formed using the first $ k $ lowercase English alphabets occur as a subsequence of $ s $ . If the answer is NO, you also need to print a string of length $ n $ that can be formed using the first $ k $ lowercase English alphabets which does not occur as a subsequence of $ s $ .

If there are multiple answers, you may print any of them.

Note: A string $ a $ is called a subsequence of another string $ b $ if $ a $ can be obtained by deleting some (possibly zero) characters from $ b $ without changing the order of the remaining characters.

## 输入格式

The first line of input contains a single integer $ t \, (1 \le t \le 10^5) $ , the number of test cases.

The first line of each test case contains $ 3 $ integers $ n \, (1 \le n \le 26), \: k \, (1 \le k \le 26), \: m \, (1 \le m \le 1000) $ , where $ n $ and $ k $ are the same as described in the input and $ m $ is the length of the string $ s $ .

The second line of each test case contains a single string $ s $ of length $ m $ , comprising only of the first $ k $ lowercase English alphabets.

It is guaranteed that the sum of $ m $ and the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print YES if all possible strings of length $ n $ that can be formed using the first $ k $ lowercase English alphabets occur as a subsequence of $ s $ , else print NO.

If your answer is NO, print a string of length $ n $ that can be formed using the first $ k $ lowercase English alphabets which does not occur as a subsequence of $ s $ in the next line.

You may print each letter of YES or NO in any case (for example, YES, yES, YeS will all be recognized as a positive answer).

## 说明/提示

For the first test case, all possible strings (aa, ab, ba, bb) of length $ 2 $ that can be formed using the first $ 2 $ English alphabets occur as a subsequence of abba.

For the second test case, the string aa is not a subsequence of abb.

## 样例 #1

### 输入

```
3
2 2 4
abba
2 2 3
abb
3 3 10
aabbccabab
```

### 输出

```
YES
NO
aa
NO
ccc
```

