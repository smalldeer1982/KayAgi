---
title: "The Supersonic Rocket"
layout: "post"
diff: 省选/NOI-
pid: CF1017E
tag: ['字符串', '凸包', 'KMP 算法']
---

# The Supersonic Rocket

## 题目描述

After the war, the supersonic rocket became the most common public transportation.

Each supersonic rocket consists of two "engines". Each engine is a set of "power sources". The first engine has $ n $ power sources, and the second one has $ m $ power sources. A power source can be described as a point $ (x_i, y_i) $ on a 2-D plane. All points in each engine are different.

You can manipulate each engine separately. There are two operations that you can do with each engine. You can do each operation as many times as you want.

1. For every power source as a whole in that engine: $ (x_i, y_i) $ becomes $ (x_i+a, y_i+b) $ , $ a $ and $ b $ can be any real numbers. In other words, all power sources will be shifted.
2. For every power source as a whole in that engine: $ (x_i, y_i) $ becomes $ (x_i \cos \theta - y_i \sin \theta, x_i \sin \theta + y_i \cos \theta) $ , $ \theta $ can be any real number. In other words, all power sources will be rotated.

The engines work as follows: after the two engines are powered, their power sources are being combined (here power sources of different engines may coincide). If two power sources $ A(x_a, y_a) $ and $ B(x_b, y_b) $ exist, then for all real number $ k $ that $ 0 \lt k \lt 1 $ , a new power source will be created $ C_k(kx_a+(1-k)x_b,ky_a+(1-k)y_b) $ . Then, this procedure will be repeated again with all new and old power sources. After that, the "power field" from all power sources will be generated (can be considered as an infinite set of all power sources occurred).

A supersonic rocket is "safe" if and only if after you manipulate the engines, destroying any power source and then power the engine, the power field generated won't be changed (comparing to the situation where no power source erased). Two power fields are considered the same if and only if any power source in one field belongs to the other one as well.

Given a supersonic rocket, check whether it is safe or not.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 3 \le n, m \le 10^5 $ ) — the number of power sources in each engine.

Each of the next $ n $ lines contains two integers $ x_i $ and $ y_i $ ( $ 0\leq x_i, y_i\leq 10^8 $ ) — the coordinates of the $ i $ -th power source in the first engine.

Each of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 0\leq x_i, y_i\leq 10^8 $ ) — the coordinates of the $ i $ -th power source in the second engine.

It is guaranteed that there are no two or more power sources that are located in the same point in each engine.

## 输出格式

Print "YES" if the supersonic rocket is safe, otherwise "NO".

You can print each letter in an arbitrary case (upper or lower).

## 说明/提示

The first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/1f54366cb2efd6f1fd1d0617b722b5e3979dfd89.png)Those near pairs of blue and orange points actually coincide.First, manipulate the first engine: use the second operation with $ \theta = \pi $ (to rotate all power sources $ 180 $ degrees).

The power sources in the first engine become $ (0, 0) $ , $ (0, -2) $ , and $ (-2, 0) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/d9732486b953667a46772450be0d244f2cb20626.png)Second, manipulate the second engine: use the first operation with $ a = b = -2 $ .

The power sources in the second engine become $ (-2, 0) $ , $ (0, 0) $ , $ (0, -2) $ , and $ (-1, -1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/f5d3a1ffc842f837240530d5f9c0ef57b3d408b7.png)You can examine that destroying any point, the power field formed by the two engines are always the solid triangle $ (0, 0) $ , $ (-2, 0) $ , $ (0, -2) $ .

In the second sample, no matter how you manipulate the engines, there always exists a power source in the second engine that power field will shrink if you destroy it.

## 样例 #1

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
1 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
0 0

```

### 输出

```
NO

```



---

---
title: "String Set Queries"
layout: "post"
diff: 省选/NOI-
pid: CF710F
tag: ['分治', '哈希 hashing', '分块', '字典树 Trie', 'AC 自动机', 'KMP 算法']
---

# String Set Queries

## 题目描述

You should process $ m $ queries over a set $ D $ of strings. Each query is one of three kinds:

1. Add a string $ s $ to the set $ D $ . It is guaranteed that the string $ s $ was not added before.
2. Delete a string $ s $ from the set $ D $ . It is guaranteed that the string $ s $ is in the set $ D $ .
3. For the given string $ s $ find the number of occurrences of the strings from the set $ D $ . If some string $ p $ from $ D $ has several occurrences in $ s $ you should count all of them.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query of the third type. Use functions fflush in C++ and BufferedWriter.flush in Java languages after each writing in your program.

## 输入格式

The first line contains integer $ m $ ( $ 1<=m<=3·10^{5} $ ) — the number of queries.

Each of the next $ m $ lines contains integer $ t $ ( $ 1<=t<=3 $ ) and nonempty string $ s $ — the kind of the query and the string to process. All strings consist of only lowercase English letters.

The sum of lengths of all strings in the input will not exceed $ 3·10^{5} $ .

## 输出格式

For each query of the third kind print the only integer $ c $ — the desired number of occurrences in the string $ s $ .

## 样例 #1

### 输入

```
5
1 abc
3 abcabc
2 abc
1 aba
3 abababc

```

### 输出

```
2
2

```

## 样例 #2

### 输入

```
10
1 abc
1 bcd
1 abcd
3 abcd
2 abcd
3 abcd
2 bcd
3 abcd
2 abc
3 abcd

```

### 输出

```
3
2
1
0

```



---

---
title: "Substrings in a String"
layout: "post"
diff: 省选/NOI-
pid: CF914F
tag: ['进制', 'KMP 算法']
---

# Substrings in a String

## 题目描述

Given a string $ s $ , process $ q $ queries, each having one of the following forms:

- $ 1ic $ — Change the $ i $ -th character in the string to $ c $ .
- $ 2lry $ — Consider the substring of $ s $ starting at position $ l $ and ending at position $ r $ . Output the number of times $ y $ occurs as a substring in it.

## 输入格式

The first line of the input contains the string $ s $ ( $ 1<=|s|<=10^{5} $ ) of lowercase English letters.

The second line contains an integer $ q $ ( $ 1<=q<=10^{5} $ ) — the number of queries to process.

The next $ q $ lines describe the queries and may have one of the following forms:

- $ 1ic $ ( $ 1<=i<=|s| $ )
- $ 2lry $ ( $ 1<=l<=r<=|s| $ )

 $ c $ is a lowercase English letter and $ y $ is a non-empty string consisting of only lowercase English letters.

The sum of $ |y| $ over all queries of second type is at most $ 10^{5} $ .

It is guaranteed that there is at least one query of second type.

All strings are $ 1 $ -indexed.

 $ |s| $ is the length of the string $ s $ .

## 输出格式

For each query of type $ 2 $ , output the required answer in a separate line.

## 说明/提示

Consider the first sample case. Initially, the string aba occurs $ 3 $ times in the range $ [1,7] $ . Note that two occurrences may overlap.

After the update, the string becomes ababcbaba and now aba occurs only once in the range $ [1,7] $ .

## 样例 #1

### 输入

```
ababababa
3
2 1 7 aba
1 5 c
2 1 7 aba

```

### 输出

```
3
1

```

## 样例 #2

### 输入

```
abcdcbc
5
2 1 7 bc
1 4 b
2 4 7 bc
1 2 a
2 1 4 aa

```

### 输出

```
2
2
1

```



---

