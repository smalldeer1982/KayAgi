---
title: "Help Far Away Kingdom"
layout: "post"
diff: 普及-
pid: CF99A
tag: []
---

# Help Far Away Kingdom

## 题目描述

In a far away kingdom lived the King, the Prince, the Shoemaker, the Dressmaker and many other citizens. They lived happily until great trouble came into the Kingdom. The ACMers settled there.

Most damage those strange creatures inflicted upon the kingdom was that they loved high precision numbers. As a result, the Kingdom healers had already had three appointments with the merchants who were asked to sell, say, exactly $ 0.273549107 $ beer barrels. To deal with the problem somehow, the King issued an order obliging rounding up all numbers to the closest integer to simplify calculations. Specifically, the order went like this:

- If a number's integer part does not end with digit $ 9 $ and its fractional part is strictly less than $ 0.5 $ , then the rounded up number coincides with the number’s integer part.
- If a number's integer part does not end with digit $ 9 $ and its fractional part is not less than $ 0.5 $ , the rounded up number is obtained if we add $ 1 $ to the last digit of the number’s integer part.
- If the number’s integer part ends with digit $ 9 $ , to round up the numbers one should go to Vasilisa the Wise. In the whole Kingdom she is the only one who can perform the tricky operation of carrying into the next position.

Merchants found the algorithm very sophisticated and they asked you (the ACMers) to help them. Can you write a program that would perform the rounding according to the King’s order?

## 输入格式

The first line contains a single number to round up — the integer part (a non-empty set of decimal digits that do not start with $ 0 $ — with the exception of a case when the set consists of a single digit — in this case 0 can go first), then follows character «.» (a dot), and then follows the fractional part (any non-empty set of decimal digits). The number's length does not exceed $ 1000 $ characters, including the dot. There are no other characters in the input data.

## 输出格式

If the last number of the integer part is not equal to $ 9 $ , print the rounded-up number without leading zeroes. Otherwise, print the message "GOTO Vasilisa." (without the quotes).

## 样例 #1

### 输入

```
0.0

```

### 输出

```
0
```

## 样例 #2

### 输入

```
1.49

```

### 输出

```
1
```

## 样例 #3

### 输入

```
1.50

```

### 输出

```
2
```

## 样例 #4

### 输入

```
2.71828182845904523536

```

### 输出

```
3
```

## 样例 #5

### 输入

```
3.14159265358979323846

```

### 输出

```
3
```

## 样例 #6

### 输入

```
12345678901234567890.1

```

### 输出

```
12345678901234567890
```

## 样例 #7

### 输入

```
123456789123456789.999

```

### 输出

```
GOTO Vasilisa.
```

