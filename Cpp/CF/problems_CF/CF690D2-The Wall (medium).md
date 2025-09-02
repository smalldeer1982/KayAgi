---
title: "The Wall (medium)"
layout: "post"
diff: 普及+/提高
pid: CF690D2
tag: []
---

# The Wall (medium)

## 题目描述

Heidi the Cow is aghast: cracks in the northern Wall? Zombies gathering outside, forming groups, preparing their assault? This must not happen! Quickly, she fetches her HC $ ^{2} $ (Handbook of Crazy Constructions) and looks for the right chapter:

How to build a wall:

1. Take a set of bricks.
2. Select one of the possible wall designs. Computing the number of possible designs is left as an exercise to the reader.
3. Place bricks on top of each other, according to the chosen design.

This seems easy enough. But Heidi is a Coding Cow, not a Constructing Cow. Her mind keeps coming back to point 2b. Despite the imminent danger of a zombie onslaught, she wonders just how many possible walls she could build with up to $ n $ bricks.

A wall is a set of wall segments as defined in the easy version. How many different walls can be constructed such that the wall consists of at least $ 1 $ and at most $ n $ bricks? Two walls are different if there exist a column $ c $ and a row $ r $ such that one wall has a brick in this spot, and the other does not.

Along with $ n $ , you will be given $ C $ , the width of the wall (as defined in the easy version). Return the number of different walls modulo $ 10^{6}+3 $ .

## 输入格式

The first line contains two space-separated integers $ n $ and $ C $ , $ 1<=n<=500000 $ , $ 1<=C<=200000 $ .

## 输出格式

Print the number of different walls that Heidi could build, modulo $ 10^{6}+3 $ .

## 说明/提示

The number $ 10^{6}+3 $ is prime.

In the second sample case, the five walls are:

```
<pre class="verbatim"><br></br>            B        B<br></br>B., .B, BB, B., and .B<br></br>
```

In the third sample case, the nine walls are the five as in the second sample case and in addition the following four:

```
<pre class="verbatim"><br></br>B    B<br></br>B    B  B        B<br></br>B., .B, BB, and BB<br></br>
```

## 样例 #1

### 输入

```
5 1

```

### 输出

```
5

```

## 样例 #2

### 输入

```
2 2

```

### 输出

```
5

```

## 样例 #3

### 输入

```
3 2

```

### 输出

```
9

```

## 样例 #4

### 输入

```
11 5

```

### 输出

```
4367

```

## 样例 #5

### 输入

```
37 63

```

### 输出

```
230574

```

