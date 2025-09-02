---
title: "Nastya and King-Shamans"
layout: "post"
diff: 省选/NOI-
pid: CF992E
tag: []
---

# Nastya and King-Shamans

## 题目描述

Nastya likes reading and even spends whole days in a library sometimes. Today she found a chronicle of Byteland in the library, and it stated that there lived shamans long time ago. It is known that at every moment there was exactly one shaman in Byteland, and there were $ n $ shamans in total enumerated with integers from $ 1 $ to $ n $ in the order they lived. Also, each shaman had a magic power which can now be expressed as an integer.

The chronicle includes a list of powers of the $ n $ shamans. Also, some shamans can be king-shamans, if they gathered all the power of their predecessors, i.e. their power is exactly the sum of powers of all previous shamans. Nastya is interested in whether there was at least one king-shaman in Byteland.

Unfortunately many of the powers are unreadable in the list, so Nastya is doing the following:

- Initially she supposes some power for each shaman.
- After that she changes the power of some shaman $ q $ times (the shamans can differ) and after that wants to check if there is at least one king-shaman in the list. If yes, she wants to know the index of any king-shaman.

Unfortunately the list is too large and Nastya wants you to help her.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1<=n,q<=2·10^{5} $ ).

The second line contains $ n $ integers $ a_{1},...,a_{n} $ ( $ 0<=a_{i}<=10^{9} $ ), where $ a_{i} $ is the magic power of the $ i $ -th shaman.

After that $ q $ lines follow, the $ i $ -th of them contains two integers $ p_{i} $ and $ x_{i} $ ( $ 1<=p_{i}<=n $ , $ 0<=x_{i}<=10^{9} $ ) that mean that the new power of the $ p_{i} $ -th shaman is $ x_{i} $ .

## 输出格式

Print $ q $ lines, the $ i $ -th of them should contain $ -1 $ , if after the $ i $ -th change there are no shaman-kings, and otherwise a single integer $ j $ , where $ j $ is an index of some king-shaman after the $ i $ -th change.

If there are multiple king-shamans after each change, print the index of any of them.

## 说明/提示

In the first example powers of shamans after the first change are equal to $ (2,3) $ . The answer equals $ -1 $ , because the sum of powers of shamans before the first shaman is equal to $ 0 $ , and before the second is equal to $ 2 $ .

In the second example after the first change the powers are equal to $ (1,2,3) $ . The answer is equal to $ 3 $ , because the power of the third shaman is equal to $ 3 $ , and the sum of powers of the first and the second shaman is also $ 1+2=3 $ . After the second change the powers become equal to $ (2,2,3) $ , where the answer equals $ 2 $ . After the third change the powers become equal to $ (2,4,3) $ , where the answer equals $ -1 $ . After the fourth change the powers become equal to $ (2,4,6) $ , where the answer equals $ 3 $ .

## 样例 #1

### 输入

```
2 1
1 3
1 2

```

### 输出

```
-1

```

## 样例 #2

### 输入

```
3 4
2 2 3
1 1
1 2
2 4
3 6

```

### 输出

```
3
2
-1
3

```

## 样例 #3

### 输入

```
10 7
0 3 1 4 6 2 7 8 10 1
2 5
1 3
9 36
4 10
4 9
1 2
1 0

```

### 输出

```
1
-1
9
-1
4
-1
1

```

