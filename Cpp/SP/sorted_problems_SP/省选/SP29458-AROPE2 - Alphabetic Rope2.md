---
title: "AROPE2 - Alphabetic Rope2"
layout: "post"
diff: 省选/NOI-
pid: SP29458
tag: ['平衡树', '可持久化']
---

# AROPE2 - Alphabetic Rope2

## 题目描述

The Alphabetic Rope is now available in the market.

The Alphabetic Rope consists of alphabeticcharacters in each stripe which looks like string.

You are given an Alphabetic rope consists of lowercase alphabetic characters only,you have to performsome operations on rope and answers some queries on it and Time is increases by 1.

Initial time is 0 and Queries are of 4 types:

1 X Y : Cut the rope segment from X to Y and join at the front of rope.  
2 X Y : Cut the rope segment from X to Y and join at the back of rope.  
3 Y: Print on a new line the Alphabet on Yth position of current rope.  
4 X Y: Print on a new line the Alphabet on Yth position of rope 
configuration at Xth time.

## 输入格式

There is only one input. Input begins with single line giving Alphabetic Rope as a string S.  
Next line containg Q, follows Q lines giving Queries as mentioned above. (Index used are 0-based)

## 输出格式

There is only one input. Input begins with single line giving Alphabetic Rope as a string S.  
Next line containg Q, follows Q lines giving Queries as mentioned above. (Index used are 0-based)

## 样例 #1

### 输入

```
gautambishal
5
3 0
2 0 5
3 1
4 0 0
4 3 0
```

### 输出

```
g
i
g
b
```

