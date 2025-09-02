---
title: "Sale"
layout: "post"
diff: 普及-
pid: CF34B
tag: ['贪心', '排序']
---

# Sale

## 题目描述

Once Bob got to a sale of old TV sets. There were $ n $ TV sets at that sale. TV set with index $ i $ costs $ a_{i} $ bellars. Some TV sets have a negative price — their owners are ready to pay Bob if he buys their useless apparatus. Bob can «buy» any TV sets he wants. Though he's very strong, Bob can carry at most $ m $ TV sets, and he has no desire to go to the sale for the second time. Please, help Bob find out the maximum sum of money that he can earn.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ( $ 1<=m<=n<=100 $ ) — amount of TV sets at the sale, and amount of TV sets that Bob can carry. The following line contains $ n $ space-separated integers $ a_{i} $ ( $ -1000<=a_{i}<=1000 $ ) — prices of the TV sets.

## 输出格式

Output the only number — the maximum sum of money that Bob can earn, given that he can carry at most $ m $ TV sets.

## 样例 #1

### 输入

```
5 3
-6 0 35 -2 4

```

### 输出

```
8

```

## 样例 #2

### 输入

```
4 2
7 0 0 -7

```

### 输出

```
7

```

