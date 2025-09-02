---
title: "BLINNET - Bytelandian Blingors Network"
layout: "post"
diff: 难度0
pid: SP30
tag: []
---

# BLINNET - Bytelandian Blingors Network

## 题目描述

 _We have discovered the fastest communication medium_  Bytelandian scientists announced, and they called it _blingors_. The blingors are incomparably better than other media known before. Many companies in Byteland started to build blingors networks, so the information society in the kingdom of Bytes is fact! The priority is to build the core of the blingors network, joinig main cities in the country. Assume there is some number of cities that will be connected at the beginning. The cost of building blingors connection between two cities depends on many elements, but it has been successfully estimated. Your task is to design the blingors network connections between some cities in this way that between any pair of cities is a communication route. The cost of this network should be as small as possible.

Remarks

- The name of the city is a string of at most 10 letters from _a,...,z_.
- The cost of the connection between two cities is a positive integer.
- The sum of all connections is not greater than 2 $ ^{32} $ -1.
- The number of cities is not greater than 10 000.

## 输入格式

```



s [number of test cases <= 10]
n [number of cities <= 10 000]
NAME [city name]
p [number of neigbouring cities to the city NAME]
neigh cost 
     [neigh - the unique number of  city from the main list
      cost - the cost of building the blingors connection from NAME to neigh]
[empty line between test cases]

```

## 输出格式

 \[separate lines\] _cost_ \[the minimum cost of building the blingors network\]

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages**

## 样例 #1

### 输入

```
2

4
gdansk
2
2 1
3 3
bydgoszcz
3
1 1
3 1
4 4
torun
3
1 3
2 1
4 1
warszawa
2
2 4
3 1

3
ixowo
2
2 1
3 3
iyekowo
2
1 1
3 7
zetowo
2
1 3 
2 7
```

### 输出

```
3
4
```

