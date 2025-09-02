---
title: "ABSURD - Absurd prices"
layout: "post"
diff: 普及/提高-
pid: SP6803
tag: []
---

# ABSURD - Absurd prices

## 题目描述

Surely you know that supermarkets, shopping centres, and indeed all kind of vendors seem to have fallen in love with the digit _9_, for that digit occurs most often in the price of a product, preferably at the least significant positions. Your favourite chocolate bar might cost _99_ cents, just right to be able to advertise that it costs less than _1_ euro. Your new bicycle might cost _499.98_ euros, which, of course, is less than _500_ euros.

While such comparisons are mathematically sound, they seem to impose a certain amount of stupidity on the customer. Moreover, who wants to carry home those annoying small coins you get back as change?

Fortunately, the FIFA has not adopted this weird pricing scheme: a ticket for the final in the first category for example costs _900_ dollar, in the second category _600_ dollar and in the third category _400_ dollar. These prices may only be regarded weird for other reasons.

We want to distinguish between **absurd** prices like _99_ cents, _499.98_ euros, etc. and normal prices. To measure the absurdity of a positive integer, do the following:

- Eliminate all trailing zeros, i.e., those in the least significant positions, from the number. You now have a positive integer, say _x_, with a non-zero digit _d_ at its end.
- Count the number of digits, say _a_, of the number _x_.
- if _d=5_ the absurdity of the number is _2 \* a - 1_
- otherwise, the absurdity of the number is _2 \* a_

For example, the absurdity of _350_ is _3_ and the absurdity of _900900_ is _8_. Using the measure of absurdity, we can define what we call an absurd price: A price _c_ is absurd if and only if the closed interval \[_0.95 \* c,1.05 \* c_\] contains an integer _e_ such that the absurdity of _e_ is less than the absurdity of _c_. Given a price in cents, go ahead and tell whether it is absurd!

## 输入格式

The first line of the input consists of the number _t_ of test cases to follow. Each test case is specified by one line containing an integer _c_. You may assume that _1 ._

## 输出格式

For each test case output if _c_ is absurd or not. Adhere to the format shown in the sample output.

## 样例 #1

### 输入

```
4
99
49998
90000
970000000
```

### 输出

```
absurd
absurd
not absurd
absurd
```

