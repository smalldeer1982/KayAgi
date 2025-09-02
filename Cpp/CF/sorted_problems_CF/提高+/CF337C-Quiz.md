---
title: "Quiz"
layout: "post"
diff: 提高+/省选-
pid: CF337C
tag: []
---

# Quiz

## 题目描述

Manao is taking part in a quiz. The quiz consists of $ n $ consecutive questions. A correct answer gives one point to the player. The game also has a counter of consecutive correct answers. When the player answers a question correctly, the number on this counter increases by 1. If the player answers a question incorrectly, the counter is reset, that is, the number on it reduces to 0. If after an answer the counter reaches the number $ k $ , then it is reset, and the player's score is doubled. Note that in this case, first 1 point is added to the player's score, and then the total score is doubled. At the beginning of the game, both the player's score and the counter of consecutive correct answers are set to zero.

Manao remembers that he has answered exactly $ m $ questions correctly. But he does not remember the order in which the questions came. He's trying to figure out what his minimum score may be. Help him and compute the remainder of the corresponding number after division by $ 1000000009 $ $ (10^{9}+9) $ .

## 输入格式

The single line contains three space-separated integers $ n $ , $ m $ and $ k $ ( $ 2<=k<=n<=10^{9}; 0<=m<=n $ ).

## 输出格式

Print a single integer — the remainder from division of Manao's minimum possible score in the quiz by $ 1000000009 $ $ (10^{9}+9) $ .

## 说明/提示

Sample 1. Manao answered 3 questions out of 5, and his score would double for each two consecutive correct answers. If Manao had answered the first, third and fifth questions, he would have scored as much as 3 points.

Sample 2. Now Manao answered 4 questions. The minimum possible score is obtained when the only wrong answer is to the question 4.

Also note that you are asked to minimize the score and not the remainder of the score modulo $ 1000000009 $ . For example, if Manao could obtain either $ 2000000000 $ or $ 2000000020 $ points, the answer is $ 2000000000 mod 1000000009 $ , even though $ 2000000020 mod 1000000009 $ is a smaller number.

## 样例 #1

### 输入

```
5 3 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 4 2

```

### 输出

```
6

```

