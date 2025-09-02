---
title: "New Year and North Pole"
layout: "post"
diff: 普及-
pid: CF750B
tag: []
---

# New Year and North Pole

## 题目描述

In this problem we assume the Earth to be a completely round ball and its surface a perfect sphere. The length of the equator and any meridian is considered to be exactly $ 40000 $ kilometers. Thus, travelling from North Pole to South Pole or vice versa takes exactly $ 20000 $ kilometers.

Limak, a polar bear, lives on the North Pole. Close to the New Year, he helps somebody with delivering packages all around the world. Instead of coordinates of places to visit, Limak got a description how he should move, assuming that he starts from the North Pole. The description consists of $ n $ parts. In the $ i $ -th part of his journey, Limak should move $ t_{i} $ kilometers in the direction represented by a string $ dir_{i} $ that is one of: "North", "South", "West", "East".

Limak isn’t sure whether the description is valid. You must help him to check the following conditions:

- If at any moment of time (before any of the instructions or while performing one of them) Limak is on the North Pole, he can move only to the South.
- If at any moment of time (before any of the instructions or while performing one of them) Limak is on the South Pole, he can move only to the North.
- The journey must end on the North Pole.

Check if the above conditions are satisfied and print "YES" or "NO" on a single line.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=50 $ ).

The $ i $ -th of next $ n $ lines contains an integer $ t_{i} $ and a string $ dir_{i} $ ( $ 1<=t_{i}<=10^{6} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750B/bad8e6778e4440b96077dcc3eab91b8cb46271e1.png)) — the length and the direction of the $ i $ -th part of the journey, according to the description Limak got.

## 输出格式

Print "YES" if the description satisfies the three conditions, otherwise print "NO", both without the quotes.

## 说明/提示

Drawings below show how Limak's journey would look like in first two samples. In the second sample the answer is "NO" because he doesn't end on the North Pole.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750B/9bb594fe352848bbba36035935a49c02ad65109a.png)

## 样例 #1

### 输入

```
5
7500 South
10000 East
3500 North
4444 West
4000 North

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
2
15000 South
4000 East

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5
20000 South
1000 North
1000000 West
9000 North
10000 North

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
3
20000 South
10 East
20000 North

```

### 输出

```
NO

```

## 样例 #5

### 输入

```
2
1000 North
1000 South

```

### 输出

```
NO

```

## 样例 #6

### 输入

```
4
50 South
50 North
15000 South
15000 North

```

### 输出

```
YES

```

