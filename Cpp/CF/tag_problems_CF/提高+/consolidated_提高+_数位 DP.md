---
title: "Classy Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF1036C
tag: ['搜索', '记忆化搜索', '数位 DP']
---

# Classy Numbers

## 题目描述

Let's call some positive integer classy if its decimal representation contains no more than $ 3 $ non-zero digits. For example, numbers $ 4 $ , $ 200000 $ , $ 10203 $ are classy and numbers $ 4231 $ , $ 102306 $ , $ 7277420000 $ are not.

You are given a segment $ [L; R] $ . Count the number of classy integers $ x $ such that $ L \le x \le R $ .

Each testcase contains several segments, for each of them you are required to solve the problem separately.

## 输入格式

The first line contains a single integer $ T $ ( $ 1 \le T \le 10^4 $ ) — the number of segments in a testcase.

Each of the next $ T $ lines contains two integers $ L_i $ and $ R_i $ ( $ 1 \le L_i \le R_i \le 10^{18} $ ).

## 输出格式

Print $ T $ lines — the $ i $ -th line should contain the number of classy integers on a segment $ [L_i; R_i] $ .

## 样例 #1

### 输入

```
4
1 1000
1024 1024
65536 65536
999999 1000001

```

### 输出

```
1000
1
0
2

```



---

---
title: "XOR Triangle"
layout: "post"
diff: 提高+/省选-
pid: CF1710C
tag: ['数位 DP']
---

# XOR Triangle

## 题目描述

给你一个数 $n$，问：有多少对数 $0\leq a,b,c \leq n$ 满足 $a \oplus b,b \oplus c,a \oplus c$  。三个数字构成了一个非退化三角形，也就是两条短边之和大于第三边的长度。$\oplus$ 表示二进制下的异或操作。

## 输入格式

一个数字 $n$，表示给定的 n 在二进制下的表示。

## 输出格式

输出答案 mod 998244353。

## 样例 #1

### 输入

```
101
```

### 输出

```
12
```

## 样例 #2

### 输入

```
1110
```

### 输出

```
780
```

## 样例 #3

### 输入

```
11011111101010010
```

### 输出

```
141427753
```



---

---
title: "Zebra-like Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF2086E
tag: ['数学', '贪心', '记忆化搜索', '数位 DP']
---

# Zebra-like Numbers

## 题目描述

我们称一个正整数为斑马数（zebra-like），如果它的二进制表示从最高有效位开始是交替的比特位，并且最低有效位等于 $1$。例如，数字 $1$、$5$ 和 $21$ 都是斑马数，因为它们的二进制表示 $1$、$101$ 和 $10101$ 满足要求，而数字 $10$ 不是斑马数，因为它的二进制表示 $1010$ 的最低有效位是 $0$。

我们定义一个正整数 $e$ 的斑马值为最小的整数 $p$，使得 $e$ 可以表示为 $p$ 个斑马数（可以相同也可以不同）的和。

给定三个整数 $l$、$r$ 和 $k$，计算满足 $l \le x \le r$ 且 $x$ 的斑马值等于 $k$ 的整数 $x$ 的数量。

## 输入格式

每个测试包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 100$）——测试用例的数量。接下来是测试用例的描述。

每个测试用例的唯一一行包含三个整数 $l$、$r$（$1 \le l \le r \le 10^{18}$）和 $k$（$1 \le k \le 10^{18}$）。

## 输出格式

对于每个测试用例，输出一个整数——区间 $[l, r]$ 内斑马值为 $k$ 的整数的数量。

## 说明/提示

- 在第一个测试用例中，有 $13$ 个符合条件的数字：$3, 7, 11, 15, 23, 27, 31, 43, 47, 63, 87, 91, 95$。每个数字都可以表示为 $3$ 个斑马数的和。
- 在第二个测试用例中，数字 $1$ 的斑马值为 $1$，因此输出 $1$。
- 在第四个测试用例中，区间 $[2, 10]$ 内没有数字的斑马值为 $100$，因此输出 $0$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
1 100 3
1 1 1
15 77 2
2 10 100
1234567 123456789101112131 12
```

### 输出

```
13
1
3
0
4246658701
```



---

---
title: "The Maths Lecture"
layout: "post"
diff: 提高+/省选-
pid: CF507D
tag: ['动态规划 DP', '数位 DP']
---

# The Maths Lecture

## 题目描述

Amr doesn't like Maths as he finds it really boring, so he usually sleeps in Maths lectures. But one day the teacher suspected that Amr is sleeping and asked him a question to make sure he wasn't.

First he gave Amr two positive integers $ n $ and $ k $ . Then he asked Amr, how many integer numbers $ x&gt;0 $ exist such that:

- Decimal representation of $ x $ (without leading zeroes) consists of exactly $ n $ digits;
- There exists some integer $ y&gt;0 $ such that: 
  - ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF507D/a168a0f3214943d3090a4c18ee0075fe3a3849dd.png);
  - decimal representation of $ y $ is a suffix of decimal representation of $ x $ .

As the answer to this question may be pretty huge the teacher asked Amr to output only its remainder modulo a number $ m $ .

Can you help Amr escape this embarrassing situation?

## 输入格式

Input consists of three integers $ n,k,m $ ( $ 1<=n<=1000 $ , $ 1<=k<=100 $ , $ 1<=m<=10^{9} $ ).

## 输出格式

Print the required number modulo $ m $ .

## 说明/提示

A suffix of a string $ S $ is a non-empty string that can be obtained by removing some number (possibly, zero) of first characters from $ S $ .

## 样例 #1

### 输入

```
1 2 1000

```

### 输出

```
4
```

## 样例 #2

### 输入

```
2 2 1000

```

### 输出

```
45
```

## 样例 #3

### 输入

```
5 3 1103

```

### 输出

```
590
```



---

---
title: "Salazar Slytherin's Locket"
layout: "post"
diff: 提高+/省选-
pid: CF855E
tag: ['数位 DP', '状态合并', '进制']
---

# Salazar Slytherin's Locket

## 题目描述

Harry came to know from Dumbledore that Salazar Slytherin's locket is a horcrux. This locket was present earlier at 12 Grimmauld Place, the home of Sirius Black's mother. It was stolen from there and is now present in the Ministry of Magic in the office of Dolorous Umbridge, Harry's former Defense Against the Dark Arts teacher.

Harry, Ron and Hermione are infiltrating the Ministry. Upon reaching Umbridge's office, they observed a code lock with a puzzle asking them to calculate count of magic numbers between two integers $ l $ and $ r $ (both inclusive).

Harry remembered from his detention time with Umbridge that she defined a magic number as a number which when converted to a given base $ b $ , all the digits from $ 0 $ to $ b-1 $ appear even number of times in its representation without any leading zeros.

You have to answer $ q $ queries to unlock the office. Each query has three integers $ b_{i} $ , $ l_{i} $ and $ r_{i} $ , the base and the range for which you have to find the count of magic numbers.

## 输入格式

First line of input contains $ q $ ( $ 1<=q<=10^{5} $ ) — number of queries.

Each of the next $ q $ lines contain three space separated integers $ b_{i} $ , $ l_{i} $ , $ r_{i} $ ( $ 2<=b_{i}<=10 $ , $ 1<=l_{i}<=r_{i}<=10^{18} $ ).

## 输出格式

You have to output $ q $ lines, each containing a single integer, the answer to the corresponding query.

## 说明/提示

In sample test case $ 1 $ , for first query, when we convert numbers $ 4 $ to $ 9 $ into base $ 2 $ , we get:

- $ 4=100_{2} $ ,
- $ 5=101_{2} $ ,
- $ 6=110_{2} $ ,
- $ 7=111_{2} $ ,
- $ 8=1000_{2} $ ,
- $ 9=1001_{2} $ .

Out of these, only base $ 2 $ representation of $ 9 $ has even number of $ 1 $ and $ 0 $ . Thus, the answer is $ 1 $ .

## 样例 #1

### 输入

```
2
2 4 9
3 1 10

```

### 输出

```
1
2

```

## 样例 #2

### 输入

```
2
2 1 100
5 1 100

```

### 输出

```
21
4

```



---

