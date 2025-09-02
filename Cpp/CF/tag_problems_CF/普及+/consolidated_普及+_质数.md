---
title: "Vasya and Triangle"
layout: "post"
diff: 普及+/提高
pid: CF1030D
tag: ['枚举', '素数判断,质数,筛法', '构造']
---

# Vasya and Triangle

## 题目描述

Vasya has got three integers $ n $ , $ m $ and $ k $ . He'd like to find three integer points $ (x_1, y_1) $ , $ (x_2, y_2) $ , $ (x_3, y_3) $ , such that $ 0 \le x_1, x_2, x_3 \le n $ , $ 0 \le y_1, y_2, y_3 \le m $ and the area of the triangle formed by these points is equal to $ \frac{nm}{k} $ .

Help Vasya! Find such points (if it's possible). If there are multiple solutions, print any of them.

## 输入格式

The single line contains three integers $ n $ , $ m $ , $ k $ ( $ 1\le n, m \le 10^9 $ , $ 2 \le k \le 10^9 $ ).

## 输出格式

If there are no such points, print "NO".

Otherwise print "YES" in the first line. The next three lines should contain integers $ x_i, y_i $ — coordinates of the points, one point per line. If there are multiple solutions, print any of them.

You can print each letter in any case (upper or lower).

## 说明/提示

In the first example area of the triangle should be equal to $ \frac{nm}{k} = 4 $ . The triangle mentioned in the output is pictured below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030D/7ee3f0a3ce75449bbc8ed199a32a394763a46df2.png)In the second example there is no triangle with area $ \frac{nm}{k} = \frac{16}{7} $ .

## 样例 #1

### 输入

```
4 3 3

```

### 输出

```
YES
1 0
2 3
4 1

```

## 样例 #2

### 输入

```
4 4 7

```

### 输出

```
NO

```



---

---
title: "Divisors"
layout: "post"
diff: 普及+/提高
pid: CF1033D
tag: ['数学', '枚举', '素数判断,质数,筛法']
---

# Divisors

## 题目描述

You are given $ n $ integers $ a_1, a_2, \ldots, a_n $ . Each of $ a_i $ has between $ 3 $ and $ 5 $ divisors. Consider $ a = \prod a_i $ — the product of all input integers. Find the number of divisors of $ a $ . As this number may be very large, print it modulo prime number $ 998244353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \leq n \leq 500 $ ) — the number of numbers.

Each of the next $ n $ lines contains an integer $ a_i $ ( $ 1 \leq a_i \leq 2\cdot 10^{18} $ ). It is guaranteed that the number of divisors of each $ a_i $ is between $ 3 $ and $ 5 $ .

## 输出格式

Print a single integer $ d $ — the number of divisors of the product $ a_1 \cdot a_2 \cdot \dots \cdot a_n $ modulo $ 998244353 $ .

Hacks input

For hacks, the input needs to be provided in a special format.

The first line contains an integer $ n $ ( $ 1 \leq n \leq 500 $ ) — the number of numbers.

Each of the next $ n $ lines contains a prime factorization of $ a_i $ . The line contains an integer $ k_i $ ( $ 2 \leq k_i \leq 4 $ ) — the number of prime factors of $ a_i $ and $ k_i $ integers $ p_{i,j} $ ( $ 2 \leq p_{i,j} \leq 2 \cdot 10^{18} $ ) where $ p_{i,j} $ is the $ j $ -th prime factor of $ a_i $ .

Before supplying the input to the contestant, $ a_i = \prod p_{i,j} $ are calculated. Note that each $ p_{i,j} $ must be prime, each computed $ a_i $ must satisfy $ a_i \leq 2\cdot10^{18} $ and must have between $ 3 $ and $ 5 $ divisors. The contestant will be given only $ a_i $ , and not its prime factorization.

For example, you need to use this test to get the first sample:

`<br></br>3<br></br>2 3 3<br></br>2 3 5<br></br>2 11 13<br></br>`Interaction

From the technical side, this problem is interactive. Therefore, do not forget to output end of line and flush the output. Also, do not read more than you need. To flush the output, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

## 说明/提示

In the first case, $ a = 19305 $ . Its divisors are $ 1, 3, 5, 9, 11, 13, 15, 27, 33, 39, 45, 55, 65, 99, 117, 135, 143, 165, 195, 297, 351, 429, 495, 585, 715, 1287, 1485, 1755, 2145, 3861, 6435, 19305 $ — a total of $ 32 $ .

In the second case, $ a $ has four divisors: $ 1 $ , $ 86028121 $ , $ 86028157 $ , and $ 7400840699802997  $ .

In the third case $ a = 202600445671925364698739061629083877981962069703140268516570564888699 375209477214045102253766023072401557491054453690213483547 $ .

In the fourth case, $ a=512=2^9 $ , so answer equals to $ 10 $ .

## 样例 #1

### 输入

```
3
9
15
143
```

### 输出

```
32
```

## 样例 #2

### 输入

```
1
7400840699802997

```

### 输出

```
4
```

## 样例 #3

### 输入

```
8 
4606061759128693
4606066102679989
4606069767552943
4606063116488033
4606063930903637
4606064745319241
4606063930904021
4606065559735517
```

### 输出

```
1920
```

## 样例 #4

### 输入

```
3
4
8
16

```

### 输出

```
10

```



---

---
title: "Shohag Loves GCD"
layout: "post"
diff: 普及+/提高
pid: CF2039D
tag: ['贪心', '数论', '素数判断,质数,筛法', '构造', '标签475']
---

# Shohag Loves GCD

## 题目描述

Shohag 拥有一个整数 $n$ 和一个包含 $m$ 个不同整数的集合 $S$。请帮助他找到字典序最大*的整数数组 $a_1, a_2, \ldots, a_n$，使得对于每个 $1 \le i \le n$ 有 $a_i \in S$ ，并且满足对所有 $1 \le i < j \le n$ 有 $a_{\gcd(i, j)} \neq \gcd(a_i, a_j)$†，或者说明不存在这样的数组。

*一个数组 $a$ 如果在第一个不同的位置上比数组 $b$ 有更大的元素，则称其为字典序大于数组 $b$（假设两个数组长度相同）。

†$\gcd(x, y)$ 表示整数 $x$ 和 $y$ 的[最大公约数（GCD）](https://en.wikipedia.org/wiki/Greatest_common_divisor)。

## 输入格式

第一行包含一个整数 $t$ ($1 \le t \le 10^4$) — 测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $m$ ($1 \le m \le n \le 10^5$)。

每个测试用例的第二行包含 $m$ 个按递增顺序排列的不同整数，表示集合 $S$ 的元素 ($1 \le x \le n$ 对于每个 $x \in S$)。

保证所有测试用例中 $n$ 的总和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果无解则输出 $-1$，否则输出 $n$ 个整数 —— 满足条件的字典序最大的整数数组。

## 说明/提示

在第一个测试用例中，数组中的每个元素都属于给定的集合 $S = \{3, 4, 6\}$，并且数组的所有索引对都满足必要的条件。特别是对于对 $(2, 3)$，有 $a_{\gcd(2, 3)} = a_1 = 6$ 而 $\gcd(a_2, a_3) = \gcd(4, 4) = 4$，因此它们不相等。尽管存在其他满足条件的数组，但这个是其中字典序最大的。

在第三个测试用例中，由于我们只能使用数组 $a = [2, 2]$，但对于该数组，对于对 $(1, 2)$，有 $a_{\gcd(1, 2)} = a_1 = 2$ 而 $\gcd(a_1, a_2) = \gcd(2, 2) = 2$，因此它们相等，这是不允许的！所以没有解决方案。

## 样例 #1

### 输入

```
3
6 3
3 4 6
1 1
1
2 1
2
```

### 输出

```
6 4 4 3 4 3 
1 
-1
```



---

---
title: "Skibidus and Capping"
layout: "post"
diff: 普及+/提高
pid: CF2065G
tag: ['数论', '素数判断,质数,筛法']
---

# Skibidus and Capping

## 题目描述

Skibidus 被 Amog 外星人绑架了！Skibidus 试图以言辞自辩脱身，但 Amog 外星人不相信他。为了证明自己不是在撒谎(capping)，Amog 外星人要求他解决以下问题：

一个整数 $x$ 如果可以写成 $p \cdot q$ 的形式（$p$ 和 $q$ 均为质数，可以相同），则称其为半质数。例如，$9$ 是半质数，因为它可以写成 $3 \cdot 3$，而 $3$ 是质数。

Skibidus 得到了一个包含 $n$ 个整数的数组 $a$。他需要统计所有满足 $i \leq j$ 且 $\operatorname{lcm}(a_i, a_j)$ $ ^{\text{∗}} $ 为半质数的索引对 $(i, j)$ 的数量。

$ ^{\text{∗}} $ 给定两个整数 $x$ 和 $y$，$\operatorname{lcm}(x, y)$ 表示 $x$ 与 $y$ 的 [最小公倍数](https://zh.wikipedia.org/wiki/%E6%9C%80%E5%B0%8F%E5%85%AC%E5%80%8D%E6%95%B8)。

## 输入格式

第一行包含一个整数 $t$ ($1 \leq t \leq 10^4$)，表示测试用例的数量。

每个测试用例的第一行包含一个整数 $n$ ($2 \leq n \leq 2 \cdot 10^5$)。

接下来一行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ ($2 \leq a_i \leq n$)。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一行一个整数，表示满足条件的有序索引对 $(i, j)$ 的数量。

## 说明/提示

在第一个测试用例中，满足条件的 $5$ 个索引对分别为 $(1, 3)$、$(1, 4)$、$(2, 3)$、$(2, 4)$ 和 $(4, 4)$。

## 样例 #1

### 输入

```
3
4
2 2 3 4
6
2 2 3 4 5 6
9
2 2 4 5 7 8 9 3 5
```

### 输出

```
5
12
18
```



---

---
title: "Primal Sport"
layout: "post"
diff: 普及+/提高
pid: CF923A
tag: ['贪心', '枚举', '素数判断,质数,筛法']
---

# Primal Sport

## 题目描述

Alice and Bob begin their day with a quick game. They first choose a starting number $ X_{0}>=3 $ and try to reach one million by the process described below.

Alice goes first and then they take alternating turns. In the $ i $ -th turn, the player whose turn it is selects a prime number smaller than the current number, and announces the smallest multiple of this prime number that is not smaller than the current number.

Formally, he or she selects a prime $ p&lt;X_{i-1} $ and then finds the minimum $ X_{i}>=X_{i-1} $ such that $ p $ divides $ X_{i} $ . Note that if the selected prime $ p $ already divides $ X_{i-1} $ , then the number does not change.

Eve has witnessed the state of the game after two turns. Given $ X_{2} $ , help her determine what is the smallest possible starting number $ X_{0} $ . Note that the players don't necessarily play optimally. You should consider all possible game evolutions.

## 输入格式

The input contains a single integer $ X_{2} $ ( $ 4<=X_{2}<=10^{6} $ ). It is guaranteed that the integer $ X_{2} $ is composite, that is, is not prime.

## 输出格式

Output a single integer — the minimum possible $ X_{0} $ .

## 说明/提示

In the first test, the smallest possible starting number is $ X_{0}=6 $ . One possible course of the game is as follows:

- Alice picks prime 5 and announces $ X_{1}=10 $
- Bob picks prime 7 and announces $ X_{2}=14 $ .

In the second case, let $ X_{0}=15 $ .

- Alice picks prime 2 and announces $ X_{1}=16 $
- Bob picks prime 5 and announces $ X_{2}=20 $ .

## 样例 #1

### 输入

```
14

```

### 输出

```
6

```

## 样例 #2

### 输入

```
20

```

### 输出

```
15

```

## 样例 #3

### 输入

```
8192

```

### 输出

```
8191

```



---

