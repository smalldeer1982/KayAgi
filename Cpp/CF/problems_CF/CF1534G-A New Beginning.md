---
title: "A New Beginning"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1534G
tag: []
---

# A New Beginning

## 题目描述

Annie has gotten bored of winning every coding contest and farming unlimited rating. Today, she is going to farm potatoes instead.

Annie's garden is an infinite 2D plane. She has $ n $ potatoes to plant, and the $ i $ -th potato must be planted at $ (x_i,y_i) $ . Starting at the point $ (0, 0) $ , Annie begins walking, in one step she can travel one unit right or up (increasing her $ x $ or $ y $ coordinate by $ 1 $ respectively). At any point $ (X,Y) $ during her walk she can plant some potatoes at arbitrary points using her potato gun, consuming $ \max(|X-x|,|Y-y|) $ units of energy in order to plant a potato at $ (x,y) $ . Find the minimum total energy required to plant every potato.

Note that Annie may plant any number of potatoes from any point.

## 输入格式

The first line contains the integer $ n $ ( $ 1 \le n \le 800\,000 $ ).

The next $ n $ lines contain two integers $ x_i $ and $ y_i $ ( $ 0 \le x_i,y_i \le 10^9 $ ), representing the location of the $ i $ -th potato. It is possible that some potatoes should be planted in the same location.

## 输出格式

Print the minimum total energy to plant all potatoes.

## 说明/提示

In example $ 1 $ , Annie can travel to each spot directly and plant a potato with no energy required.

In example $ 2 $ , moving to $ (1,0) $ , Annie plants the second potato using $ 1 $ energy. Next, she travels to $ (1,1) $ and plants the first potato with $ 0 $ energy.

## 样例 #1

### 输入

```
2
1 1
2 2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2
1 1
2 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
5 5
7 7
4 9
```

### 输出

```
2
```

## 样例 #4

### 输入

```
10
5 1
4 0
9 6
0 2
10 1
9 10
3 10
0 10
8 9
1 5
```

### 输出

```
19
```

## 样例 #5

### 输入

```
10
1 1
2 2
2 0
4 2
4 0
2 0
0 2
4 0
4 2
5 1
```

### 输出

```
6
```

