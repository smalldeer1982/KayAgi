---
title: "Anton and Digits"
layout: "post"
diff: 入门
pid: CF734B
tag: []
---

# Anton and Digits

## 题目描述

Recently Anton found a box with digits in his room. There are $ k_{2} $ digits $ 2 $ , $ k_{3} $ digits $ 3 $ , $ k_{5} $ digits $ 5 $ and $ k_{6} $ digits $ 6 $ .

Anton's favorite integers are $ 32 $ and $ 256 $ . He decided to compose this integers from digits he has. He wants to make the sum of these integers as large as possible. Help him solve this task!

Each digit can be used no more than once, i.e. the composed integers should contain no more than $ k_{2} $ digits $ 2 $ , $ k_{3} $ digits $ 3 $ and so on. Of course, unused digits are not counted in the sum.

## 输入格式

The only line of the input contains four integers $ k_{2} $ , $ k_{3} $ , $ k_{5} $ and $ k_{6} $ — the number of digits $ 2 $ , $ 3 $ , $ 5 $ and $ 6 $ respectively ( $ 0<=k_{2},k_{3},k_{5},k_{6}<=5·10^{6} $ ).

## 输出格式

Print one integer — maximum possible sum of Anton's favorite integers that can be composed using digits from the box.

## 说明/提示

In the first sample, there are five digits $ 2 $ , one digit $ 3 $ , three digits $ 5 $ and four digits $ 6 $ . Anton can compose three integers $ 256 $ and one integer $ 32 $ to achieve the value $ 256+256+256+32=800 $ . Note, that there is one unused integer $ 2 $ and one unused integer $ 6 $ . They are not counted in the answer.

In the second sample, the optimal answer is to create on integer $ 256 $ , thus the answer is $ 256 $ .

## 样例 #1

### 输入

```
5 1 3 4

```

### 输出

```
800

```

## 样例 #2

### 输入

```
1 1 1 1

```

### 输出

```
256

```

