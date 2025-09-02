---
title: "FASHION - Fashion Shows"
layout: "post"
diff: 普及-
pid: SP1025
tag: ['数学', '排序']
---

# FASHION - Fashion Shows

## 题目描述

A fashion show rates participants according to their level of hotness. Two different fashion shows were organized, one for men and the other for women. A date for the third is yet to be decided ;) .

Now the results of both fashion shows are out. The participants of both the fashion shows have decided to date each other, but as usual they have difficuly in choosing their partners. The Maximum Match dating serive (MMDS) comes to their rescue and matches them in such a way that that maximizes the hotness bonds for all couples.

If a man has been rated at hotness level x and a women at hotness level y, the value of their hotness bond is x\*y.

Both fashion shows contain **N** participants each. MMDS has done its job and your job is to find the sum of hotness bonds for all the couples that MMDS has proposed.

## 输入格式

The first line of the input contains an integer **t**, the number of test cases. **t** test cases follow.

Each test case consists of 3 lines:

- The first line contains a single integer **N** (1 <= **N** <= 1000).
- The second line contains **N** integers separated by single spaces denoting the hotness levels of the men.
- The third line contains **N** integers separated by single spaces denoting the hotness levels of the women.

All hotness ratings are on a scale of 0 to 10.

## 输出格式

For each test case output a single line containing a single integer denoting the sum of the hotness bonds for all pairs that MMDS has proposed.

## 样例 #1

### 输入

```
2

2

1 1

3 2

3

2 3 2

1 3 2
```

### 输出

```
5

15
```



---

---
title: "SBANK - Sorting Bank Accounts"
layout: "post"
diff: 普及-
pid: SP27
tag: ['模拟', '字符串', '排序']
---

# SBANK - Sorting Bank Accounts

## 题目描述

 In one of the internet banks thousands of operations are being performed every day. Since certain customers do business more actively than others, some of the bank accounts occur many times in the list of operations. Your task is to sort the bank account numbers in ascending order. If an account appears twice or more in the list, write the number of repetitions just after the account number. The format of accounts is as follows: **2** control digits, an **8**-digit code of the bank, **16** digits identifying the owner (written in groups of four digits), for example (at the end of each line there is exactly one space):

**30 10103538 2222 1233 6160 0142**  **Banks are real-time institutions and they need FAST solutions. If you feel you can meet the challenge within a very stringent time limit, go ahead!** A well designed sorting algorithm in a fast language is likely to succeed.

## 输入格式

   
_t_ \[the number of tests <= **5**\]   
_n_ \[the number of accounts<= **100 000**\]   
\[list of accounts\]   
\[empty line\]   
\[next test cases\]

## 输出格式

   
\[sorted list of accounts with the number of repeated accounts\]   
\[empty line\]   
\[other results\]

## 样例 #1

### 输入

```
2
6
03 10103538 2222 1233 6160 0142 
03 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0142 
30 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0142 

5
30 10103538 2222 1233 6160 0144 
30 10103538 2222 1233 6160 0142 
30 10103538 2222 1233 6160 0145 
30 10103538 2222 1233 6160 0146 
30 10103538 2222 1233 6160 0143
```

### 输出

```
03 10103538 2222 1233 6160 0141 1
03 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0141 2
30 10103538 2222 1233 6160 0142 2

30 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0143 1
30 10103538 2222 1233 6160 0144 1
30 10103538 2222 1233 6160 0145 1
30 10103538 2222 1233 6160 0146 1
```



---

---
title: "MDOLLS - Nested Dolls"
layout: "post"
diff: 普及-
pid: SP3943
tag: ['贪心', '二分', '排序']
---

# MDOLLS - Nested Dolls

## 题目描述

[English](/problems/MDOLLS/en/) [Vietnamese](/problems/MDOLLS/vn/) ```

Dilworth is the world's most prominent collector of Russian nested dolls:
he literally has thousands of them! You know, the wooden hollow dolls of 
different sizes of which the smallest doll is contained in the second smallest,
and this doll is in turn contained in the next one and so forth. One day he
wonders if there is another way of nesting them so he will end up with
fewer nested dolls? After all, that would make his collection even 
more magnificent! He unpacks each nested doll and measures the width 
and height of each contained doll. A doll with width w1 and height h1 will
fit in another doll of width w2 and height h= if and only if w1 < w2 and 
h1 < h2. Can you help him calculate the smallest number of nested dolls 
possible to assemble from his massive list of measurements? 
```

## 输入格式

```

On the first line of input is a single positive integer 1 ≤ t ≤ 20 specifying
the number of test cases to follow. Each test case begins with a positive 
integer 1 ≤ m ≤ 20000 on a line of itself telling the number of dolls 
in the test case. Next follow 2m positive integers w1, h1,w2, h2, ... ,wm, 
hm, where wi is the width and hi is the height of doll number i. 
1 ≤ wi, hi ≤ 10000 for all i.

SAMPLE INPUT
4
3
20 30 40 50 30 40
4
20 30 10 10 30 20 40 50
3
10 30 20 20 30 10
4
10 10 20 30 40 50 39 51
```

## 输出格式

```
 
For each test case there should be one line of output containing the minimum
number of nested dolls possible.

SAMPLE OUTPUT
1
2
3
2
```



---

