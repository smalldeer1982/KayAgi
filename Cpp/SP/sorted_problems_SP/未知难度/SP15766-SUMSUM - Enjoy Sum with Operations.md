---
title: "SUMSUM - Enjoy Sum with Operations"
layout: "post"
diff: 难度0
pid: SP15766
tag: []
---

# SUMSUM - Enjoy Sum with Operations

## 题目描述

 You are given N numbers of the array (N <= 100000), all less than 10^8 and greater than 0.

 Now, you are given 2 queries:

1. "1 x i" : Change the i-th number to x. (0 <= x <= 10^8)
2. "2 Op i1 i2": Compute the sum of all two elements taken at a time within index i1 to i2(both inclusive) under the operation Op. Op could be XOR,OR or AND.

For example, let N=4, Query=3 and "10 20 30 40" be the Initial array.

Query:

 ```

2 OR 1 3
1 0 1
2 OR 1 3
```
Answer:

 ```

2 OR 1 3--> (10 OR 20) + (20 OR 30) + (10 OR 30)
1 0 1   --> Now array becomes 0 20 30 40
2 OR 1 3--> (0 OR 20) + (20 OR 30) + (0 OR 30)
```

## 样例 #1

### 输入

```
4 3
10 20 30 40
2 OR 1 3
1 0 1
2 OR 1 3
```

### 输出

```
90
80
```

