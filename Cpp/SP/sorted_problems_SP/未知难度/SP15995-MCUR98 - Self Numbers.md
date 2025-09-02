---
title: "MCUR98 - Self Numbers"
layout: "post"
diff: 难度0
pid: SP15995
tag: []
---

# MCUR98 - Self Numbers

## 题目描述

**Background**

In 1949 the Indian mathematician D.R. Kaprekar discovered a class of numbers called _self-numbers_. For any positive integer _n_, define _d(n)_ to be_n_ plus the sum of the digits of _n_. (The _d_ stands for _digitadition_, a term coined by Kaprekar.) For example:

d(75) = 75 + 7 + 5 = 87

Given any positive integer n as a starting point, you can construct the infinite increasing sequence of integers _n, d(n), d(d(n)), d(d(d(n))), ..._ For example, if you start with 33, the next number is 33 + 3 + 3 = 39, the next is 39 + 3 + 9 = 51, the next is 51 + 5 + 1 = 57, and so you generate the sequence

33, 39, 51, 57, 69, 84, 96, 111, 114, 120, 123, 129, 141, ...

The number _n_ is called a _generator_ of _d(n)_. In the sequence above, 33 is a generator of 39, 39 is a generator of 51, 51 is a generator of 57, and so on.

Some numbers have more than one generator: For example, 101 has two generators, 91 and 100. A number with no generators is a _self-number_. There are thirteen self-numbers less than 100: 1, 3, 5, 7, 9, 20, 31, 42, 53, 64, 75, 86, and 97.

**Problem**

Write a program to output all positive self-numbers less than 1000000 in increasing order, one per line.

**Input**

There is no input.

**Output**

All positive self-numbers less than 1000000 in increasing order, one per line.

