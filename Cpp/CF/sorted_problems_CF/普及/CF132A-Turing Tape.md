---
title: "Turing Tape"
layout: "post"
diff: 普及/提高-
pid: CF132A
tag: []
---

# Turing Tape

## 题目描述

INTERCAL is the oldest of esoteric programming languages. One of its many weird features is the method of character-based output, known as Turing Tape method. It converts an array of unsigned 8-bit integers into a sequence of characters to print, using the following method.

The integers of the array are processed one by one, starting from the first. Processing $ i $ -th element of the array is done in three steps:

1\. The 8-bit binary notation of the ASCII-code of the previous printed character is reversed. When the first element of the array is processed, the result of this step is considered to be 0.

2\. The $ i $ -th element of the array is subtracted from the result of the previous step modulo 256.

3\. The binary notation of the result of the previous step is reversed again to produce ASCII-code of the $ i $ -th character to be printed.

You are given the text printed using this method. Restore the array used to produce this text.

## 输入格式

The input will consist of a single line $ text $ which contains the message printed using the described method. String $ text $ will contain between 1 and 100 characters, inclusive. ASCII-code of each character of $ text $ will be between 32 (space) and 126 (tilde), inclusive.

## 输出格式

Output the initial array, which was used to produce $ text $ , one integer per line.

## 说明/提示

Let's have a closer look at the beginning of the example. The first character is "H" with ASCII-code $ 72=01001000_{2} $ . Its reverse is $ 00010010_{2}=18 $ , and this number should become the result of the second step of processing. The result of the first step is considered to be 0, so the first element of the array has to be $ (0-18) $ mod $ 256=238 $ , where $ a $ mod $ b $ is the remainder of division of $ a $ by $ b $ .

## 样例 #1

### 输入

```
Hello, World!

```

### 输出

```
238
108
112
0
64
194
48
26
244
168
24
16
162

```

