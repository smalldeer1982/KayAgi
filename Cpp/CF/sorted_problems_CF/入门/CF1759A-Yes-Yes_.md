---
title: "Yes-Yes?"
layout: "post"
diff: 入门
pid: CF1759A
tag: ['字符串']
---

# Yes-Yes?

## 题目描述

You talked to Polycarp and asked him a question. You know that when he wants to answer "yes", he repeats Yes many times in a row.

Because of the noise, you only heard part of the answer — some substring of it. That is, if he answered YesYes, then you could hear esY, YesYes, sYes, e, but you couldn't Yess, YES or se.

Determine if it is true that the given string $ s $ is a substring of YesYesYes... (Yes repeated many times in a row).

## 输入格式

The first line of input data contains the singular $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases in the test.

Each test case is described by a single string of Latin letters $ s $ ( $ 1 \le |s| \le 50 $ ) — the part of Polycarp's answer that you heard, where $ |s| $ — is the length of the string $ s $ .

## 输出格式

Output $ t $ lines, each of which is the answer to the corresponding test case. As an answer, output "YES" if the specified string $ s $ is a substring of the string YesYesYes...Yes (the number of words Yes is arbitrary), and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 样例 #1

### 输入

```
12
YES
esYes
codeforces
es
se
YesY
esYesYesYesYesYesYe
seY
Yess
sY
o
Yes
```

### 输出

```
NO
YES
NO
YES
NO
YES
YES
NO
NO
YES
NO
YES
```

