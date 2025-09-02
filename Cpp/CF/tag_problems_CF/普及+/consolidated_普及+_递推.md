---
title: "Vasya And The Mushrooms"
layout: "post"
diff: 普及+/提高
pid: CF1016C
tag: ['模拟', '递推', '前缀和']
---

# Vasya And The Mushrooms

## 题目描述

Vasya 住在森林里，附近有一个会长蘑菇的空地。这个空地被分成两行，每行分为 $n$ 个连续的格子。Vasya 知道每分钟每个格子里能长多少个蘑菇。他要花一分钟从一个格子走到相邻的格子上，并且他不能离开空地。（我们称两个格子相邻，当且仅当它们有公共边。）当 Vasya 进入一个格子时，他会马上收集那个格子里的所有蘑菇。

Vasya 从左上角的格子开始收集蘑菇。因为他等不及蘑菇生长了，所以每分钟内他必须移动到一个相邻格子。他想每个格子都恰好走一遍并且最大化他所收集的蘑菇数量。一开始所有格子都没有蘑菇。Vasya也不一定要回到开始的格子。
帮帮 Vasya！计算出他能收集到的最大蘑菇数量。

## 输入格式

第一行包含数字 $n(1 \le n \le 3 \cdot 10 ^ {5})$ —— 空地的长度。

第二行包含 $n$ 个数字 $a_ {1}, a_ {2}, \ldots, a_{n}$（$1 \le a_{i} \le 10^{6}$） —— 在空地第一行的蘑菇的生长速度。

第三行包含 $n$ 个数字 $b_ {1}, b_ {2}, \ldots, b_{n}$（$1 \le b_ {i} \le 10 ^ {6}$） —— 在空地第二行的蘑菇的生长速度。

## 输出格式

输出一个数字—— Vasya 通过选择最佳路线可以收集的最大蘑菇总重量。 

请注意，Vasya 必须将空地中的每个单元都访问一次。

## 说明/提示

#### 样例1:

在第一个测试用例中，最佳路径如下：

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1016C/fbb0db02f46ac40c8f18dc6a212852df14543f5e.png) 

这样，蘑菇的收集重量将为 $0·1 + 1·2 + 2·3 + 3·4 + 4·5 + 5·6 =70$。

#### 样例2:

在第二个测试用例中，最佳路径如下：

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1016C/0853812a60511dc1127814cc7d3f93535736820f.png) 

这样，蘑菇的收集重量将为 $0·1 + 1·10 + 2·100 + 3·1000 + 4·10000 + 5·100000 =543210$

## 样例 #1

### 输入

```
3
1 2 3
6 5 4

```

### 输出

```
70

```

## 样例 #2

### 输入

```
3
1 1000 10000
10 100 100000

```

### 输出

```
543210

```



---

---
title: "Up the Strip (simplified version)"
layout: "post"
diff: 普及+/提高
pid: CF1561D1
tag: ['数学', '递推']
---

# Up the Strip (simplified version)

## 题目描述

This version of the problem differs from the next one only in the constraint on $ n $ .

Note that the memory limit in this problem is lower than in others.

You have a vertical strip with $ n $ cells, numbered consecutively from $ 1 $ to $ n $ from top to bottom.

You also have a token that is initially placed in cell $ n $ . You will move the token up until it arrives at cell $ 1 $ .

Let the token be in cell $ x > 1 $ at some moment. One shift of the token can have either of the following kinds:

- Subtraction: you choose an integer $ y $ between $ 1 $ and $ x-1 $ , inclusive, and move the token from cell $ x $ to cell $ x - y $ .
- Floored division: you choose an integer $ z $ between $ 2 $ and $ x $ , inclusive, and move the token from cell $ x $ to cell $ \lfloor \frac{x}{z} \rfloor $ ( $ x $ divided by $ z $ rounded down).

Find the number of ways to move the token from cell $ n $ to cell $ 1 $ using one or more shifts, and print it modulo $ m $ . Note that if there are several ways to move the token from one cell to another in one shift, all these ways are considered distinct (check example explanation for a better understanding).

## 输入格式

The only line contains two integers $ n $ and $ m $ ( $ 2 \le n \le 2 \cdot 10^5 $ ; $ 10^8 < m < 10^9 $ ; $ m $ is a prime number) — the length of the strip and the modulo.

## 输出格式

Print the number of ways to move the token from cell $ n $ to cell $ 1 $ , modulo $ m $ .

## 说明/提示

In the first test, there are three ways to move the token from cell $ 3 $ to cell $ 1 $ in one shift: using subtraction of $ y = 2 $ , or using division by $ z = 2 $ or $ z = 3 $ .

There are also two ways to move the token from cell $ 3 $ to cell $ 1 $ via cell $ 2 $ : first subtract $ y = 1 $ , and then either subtract $ y = 1 $ again or divide by $ z = 2 $ .

Therefore, there are five ways in total.

## 样例 #1

### 输入

```
3 998244353
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5 998244353
```

### 输出

```
25
```

## 样例 #3

### 输入

```
42 998244353
```

### 输出

```
793019428
```



---

---
title: "Tetrahedron"
layout: "post"
diff: 普及+/提高
pid: CF166E
tag: ['递推', '线性递推', '逆元']
---

# Tetrahedron

## 题目描述

You are given a tetrahedron. Let's mark its vertices with letters $ A $ , $ B $ , $ C $ and $ D $ correspondingly.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166E/40dcfda00eddce9e7e8701e13b2759e732ca40f3.png)An ant is standing in the vertex $ D $ of the tetrahedron. The ant is quite active and he wouldn't stay idle. At each moment of time he makes a step from one vertex to another one along some edge of the tetrahedron. The ant just can't stand on one place.

You do not have to do much to solve the problem: your task is to count the number of ways in which the ant can go from the initial vertex $ D $ to itself in exactly $ n $ steps. In other words, you are asked to find out the number of different cyclic paths with the length of $ n $ from vertex $ D $ to itself. As the number can be quite large, you should print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains the only integer $ n $ ( $ 1<=n<=10^{7} $ ) — the required length of the cyclic path.

## 输出格式

Print the only integer — the required number of ways modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

The required paths in the first sample are:

- $ D-A-D $
- $ D-B-D $
- $ D-C-D $

## 样例 #1

### 输入

```
2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4

```

### 输出

```
21

```



---

---
title: "Word Cut"
layout: "post"
diff: 普及+/提高
pid: CF176B
tag: ['字符串', '递推', 'KMP 算法']
---

# Word Cut

## 题目描述

Let's consider one interesting word game. In this game you should transform one word into another through special operations.

Let's say we have word $ w $ , let's split this word into two non-empty parts $ x $ and $ y $ so, that $ w=xy $ . A split operation is transforming word $ w=xy $ into word $ u=yx $ . For example, a split operation can transform word "wordcut" into word "cutword".

You are given two words $ start $ and $ end $ . Count in how many ways we can transform word $ start $ into word $ end $ , if we apply exactly $ k $ split operations consecutively to word $ start $ .

Two ways are considered different if the sequences of applied operations differ. Two operation sequences are different if exists such number $ i $ ( $ 1<=i<=k $ ), that in the $ i $ -th operation of the first sequence the word splits into parts $ x $ and $ y $ , in the $ i $ -th operation of the second sequence the word splits into parts $ a $ and $ b $ , and additionally $ x≠a $ holds.

## 输入格式

The first line contains a non-empty word $ start $ , the second line contains a non-empty word $ end $ . The words consist of lowercase Latin letters. The number of letters in word $ start $ equals the number of letters in word $ end $ and is at least $ 2 $ and doesn't exceed $ 1000 $ letters.

The third line contains integer $ k $ ( $ 0<=k<=10^{5} $ ) — the required number of operations.

## 输出格式

Print a single number — the answer to the problem. As this number can be rather large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

The sought way in the first sample is:

ab $ → $ a|b $ → $ ba $ → $ b|a $ → $ ab

In the second sample the two sought ways are:

- ababab $ → $ abab|ab $ → $ ababab
- ababab $ → $ ab|abab $ → $ ababab

## 样例 #1

### 输入

```
ab
ab
2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
ababab
ababab
1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
ab
ba
2

```

### 输出

```
0

```



---

---
title: "Travelling Salesman and Special Numbers"
layout: "post"
diff: 普及+/提高
pid: CF914C
tag: ['递推', '数位 DP', '进制']
---

# Travelling Salesman and Special Numbers

## 题目描述

The Travelling Salesman spends a lot of time travelling so he tends to get bored. To pass time, he likes to perform operations on numbers. One such operation is to take a positive integer $ x $ and reduce it to the number of bits set to $ 1 $ in the binary representation of $ x $ . For example for number $ 13 $ it's true that $ 13_{10}=1101_{2} $ , so it has $ 3 $ bits set and $ 13 $ will be reduced to $ 3 $ in one operation.

He calls a number special if the minimum number of operations to reduce it to $ 1 $ is $ k $ .

He wants to find out how many special numbers exist which are not greater than $ n $ . Please help the Travelling Salesman, as he is about to reach his destination!

Since the answer can be large, output it modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<2^{1000} $ ).

The second line contains integer $ k $ ( $ 0<=k<=1000 $ ).

Note that $ n $ is given in its binary representation without any leading zeros.

## 输出格式

Output a single integer — the number of special numbers not greater than $ n $ , modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, the three special numbers are $ 3 $ , $ 5 $ and $ 6 $ . They get reduced to $ 2 $ in one operation (since there are two set bits in each of $ 3 $ , $ 5 $ and $ 6 $ ) and then to $ 1 $ in one more operation (since there is only one set bit in $ 2 $ ).

## 样例 #1

### 输入

```
110
2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
111111011
2

```

### 输出

```
169

```



---

