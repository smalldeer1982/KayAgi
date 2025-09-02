---
title: "Functions On The Segments"
layout: "post"
diff: 省选/NOI-
pid: CF837G
tag: []
---

# Functions On The Segments

## 题目描述

You have an array $ f $ of $ n $ functions.The function $ f_{i}(x) $ ( $ 1<=i<=n $ ) is characterized by parameters: $ x_{1},x_{2},y_{1},a,b,y_{2} $ and take values:

- $ y_{1} $ , if $ x<=x_{1} $ .
- $ a·x+b $ , if $ x_{1}&lt;x<=x_{2} $ .
- $ y_{2} $ , if $ x&gt;x_{2} $ .

There are $ m $ queries. Each query is determined by numbers $ l $ , $ r $ and $ x $ . For a query with number $ i $ ( $ 1<=i<=m $ ), you need to calculate the sum of all $ f_{j}(x_{i}) $ where $ l<=j<=r $ . The value of $ x_{i} $ is calculated as follows: $ x_{i}=(x+last) $ mod $ 10^{9} $ , where $ last $ is the answer to the query with number $ i-1 $ . The value of $ last $ equals $ 0 $ if $ i=1 $ .

## 输入格式

First line contains one integer number $ n $ ( $ 1<=n<=75000 $ ).

Each of the next $ n $ lines contains six integer numbers: $ x_{1},x_{2},y_{1},a,b,y_{2} $ ( $ 0<=x_{1}&lt;x_{2}<=2·10^{5} $ , $ 0<=y_{1},y_{2}<=10^{9} $ , $ 0<=a,b<=10^{4} $ ).

Next line contains one integer number $ m $ ( $ 1<=m<=500000 $ ).

Each of the next $ m $ lines contains three integer numbers: $ l $ , $ r $ and $ x $ ( $ 1<=l<=r<=n $ , $ 0<=x<=10^{9} $ ).

## 样例 #1

### 输入

```
1
1 2 1 4 5 10
1
1 1 2

```

### 输出

```
13

```

## 样例 #2

### 输入

```
3
2 5 1 1 1 4
3 6 8 2 5 7
1 3 5 1 4 10
3
1 3 3
2 3 2
1 2 5

```

### 输出

```
19
17
11

```

