---
title: "BOOKS1 - Copying Books"
layout: "post"
diff: 普及/提高-
pid: SP43
tag: ['动态规划 DP', '贪心', '进制']
---

# BOOKS1 - Copying Books

## 样例 #1

### 输入

```
2

9 3

100 200 300 400 500 600 700 800 900

5 4

100 100 100 100 100
```

### 输出

```
100 200 300 400 500 / 600 700 / 800 900

100 / 100 / 100 / 100 100
```



---

---
title: "NEG2 - The Moronic Cowmpouter"
layout: "post"
diff: 普及/提高-
pid: SP739
tag: ['进制']
---

# NEG2 - The Moronic Cowmpouter

## 题目描述

Inexperienced in the digital arts, the cows tried to build a calculating engine (yes, it's a cowmpouter) using binary numbers (base 2) but instead built one based on base negative 2! They were quite pleased since numbers expressed in base -2 do not have a sign bit.

 You know number bases have place values that start at 1 (base to the 0 power) and proceed right-to-left to base^1, base^2, and so on. In base -2, the place values are 1, -2, 4, -8, 16, -32, ... (reading from right to left). Thus, counting from 1 goes like this: 1, 110, 111, 100, 101, 11010, 11011, 11000, 11001, and so on.

 Eerily, negative numbers are also represented with 1's and 0's but no sign. Consider counting from -1 downward: 11, 10, 1101, 1100, 1111, and so on.

 Please help the cows convert ordinary decimal integers (range -2,000,000,000 .. 2,000,000,000) to their counterpart representation in base -2.

## 输入格式

A single integer to be converted to base -2

## 输出格式

A single integer with no leading zeroes that is the input integer converted to base -2. The value 0 is expressed as 0, with exactly one 0.

## 样例 #1

### 输入

```
-13
```

### 输出

```
110111
```



---

