---
title: "Tokitsukaze and Powers"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1190F
tag: []
---

# Tokitsukaze and Powers

## 题目描述

Tokitsukaze is playing a room escape game designed by SkywalkerT. In this game, she needs to find out hidden clues in the room to reveal a way to escape.

After a while, she realizes that the only way to run away is to open the digital door lock since she accidentally went into a secret compartment and found some clues, which can be interpreted as:

- Only when you enter $ n $ possible different passwords can you open the door;
- Passwords must be integers ranged from $ 0 $ to $ (m - 1) $ ;
- A password cannot be $ x $ ( $ 0 \leq x < m $ ) if $ x $ and $ m $ are not coprime (i.e. $ x $ and $ m $ have some common divisor greater than $ 1 $ );
- A password cannot be $ x $ ( $ 0 \leq x < m $ ) if there exist non-negative integers $ e $ and $ k $ such that $ p^e = k m + x $ , where $ p $ is a secret integer;
- Any integer that doesn't break the above rules can be a password;
- Several integers are hidden in the room, but only one of them can be $ p $ .

Fortunately, she finds that $ n $ and $ m $ are recorded in the lock. However, what makes Tokitsukaze frustrated is that she doesn't do well in math. Now that she has found an integer that is suspected to be $ p $ , she wants you to help her find out $ n $ possible passwords, or determine the integer cannot be $ p $ .

## 输入格式

The only line contains three integers $ n $ , $ m $ and $ p $ ( $ 1 \leq n \leq 5 \times 10^5 $ , $ 1 \leq p < m \leq 10^{18} $ ).

It is guaranteed that $ m $ is a positive integer power of a single prime number.

## 输出格式

If the number of possible different passwords is less than $ n $ , print a single integer $ -1 $ .

Otherwise, print $ n $ distinct integers ranged from $ 0 $ to $ (m - 1) $ as passwords. You can print these integers in any order. Besides, if there are multiple solutions, print any.

## 说明/提示

In the first example, there is no possible password.

In each of the last three examples, the given integer $ n $ equals to the number of possible different passwords for the given integers $ m $ and $ p $ , so if the order of numbers in the output is ignored, the solution is unique as shown above.

## 样例 #1

### 输入

```
1 2 1

```

### 输出

```
-1

```

## 样例 #2

### 输入

```
3 5 1

```

### 输出

```
2 4 3

```

## 样例 #3

### 输入

```
2 5 4

```

### 输出

```
2 3

```

## 样例 #4

### 输入

```
4 9 8

```

### 输出

```
2 4 7 5

```

