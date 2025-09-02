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
title: "NUMOFPAL - Number of Palindromes"
layout: "post"
diff: 普及-
pid: SP7586
tag: ['字符串', '概率论']
---

# NUMOFPAL - Number of Palindromes

## 题目描述

Each palindrome can be always created from the other palindromes, if a single character is also a palindrome. For example, the string "malayalam" can be created by some ways:

  
\* malayalam = m + ala + y + ala + m  
\* malayalam = m + a + l + aya + l + a + m  
  
We want to take the value of function NumPal(s) which is the number of different palindromes that can be created using the string S by the above method. If the same palindrome occurs more than once then all of them should be counted separately.

## 输入格式

The string S.

## 输出格式

The value of function NumPal(s).

## 说明/提示

**Limitations**

0 < |s| <= 1000

## 样例 #1

### 输入

```
malayalam
```

### 输出

```
15
```



---

---
title: "NY10A - Penney Game"
layout: "post"
diff: 普及-
pid: SP8612
tag: ['模拟', '字符串']
---

# NY10A - Penney Game

## 题目描述

Penney’s game is a simple game typically played by two players. One version of the game calls for each player to choose a unique three-coin sequence such as **HEADS TAILS HEADS (HTH)**. A fair coin is tossed sequentially some number of times until one of the two sequences appears. The player who chose the first sequence to appear wins the game.

For this problem, you will write a program that implements a variation on the Penney Game. You willread a sequence of 40 coin tosses and determine how many times each three-coin sequence appears. Obviously there are eight such three-coin sequences: **TTT**, **TTH**, **THT**, **THH**, **HTT**, **HTH**, **HHT** and **HHH**. Sequences may overlap. For example, if all 40 coin tosses are heads, then the sequence HHH appears 38 times.

## 输入格式

The first line of input contains a single integer P, (1

## 输出格式

For each data set there is one line of output. It contains the data set number followed by a single space, followed by the number of occurrences of each three-coin sequence, in the order shown above, with a space between each one. There should be a total of 9 space separated decimal integers on each output line.

## 样例 #1

### 输入

```
\n4\n1\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n2\nTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n3\nHHTTTHHTTTHTHHTHHTTHTTTHHHTHTTHTTHTTTHTH\n4\nHTHTHHHTHHHTHTHHHHTTTHTTTTTHHTTTTHTHHHHT\n\n
```

### 输出

```
\n1 0 0 0 0 0 0 0 38\n2 38 0 0 0 0 0 0 0\n3 4 7 6 4 7 4 5 1\n4 6 3 4 5 3 6 5 6
```



---

