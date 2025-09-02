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
title: "Sakurako's Box"
layout: "post"
diff: 普及+/提高
pid: CF2008F
tag: ['数学', '逆元']
---

# Sakurako's Box

## 题目描述

Sakurako 有一个装满 $n$ 个球的盒子。每个球都有自己的数值。她想和朋友打个赌，朋友如果从盒子中随机选出两个球（可以是不同的两球，即使它们有相同的数值），这两个球数值的乘积能够等于 Sakurako 事先猜测到的一个数。

因为 Sakurako 是概率学方面的专家，她知道最明智的猜测应该是[期望值](http://tiny.cc/matozh_en)，但她忘了如何去计算。请帮助她计算出这个数组中任意两个元素乘积的期望值。

可以证明，该期望值的形式为 $\frac{P}{Q}$，其中 $P$ 和 $Q$ 是非负整数，且 $Q \ne 0$。你需要计算并输出 $P \cdot Q^{-1} \bmod (10^9+7)$ 的结果。

## 输入格式

输入的第一行是一个整数 $t$，表示测试用例的数量（$1 \le t \le 10^4$）。

接下来的每一个测试用例的第一行是一个整数 $n$，表示数组中元素的数量（$2 \le n \le 2 \cdot 10^5$）。

接下来的第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$0 \le a_i \le 10^9$），表示数组中的元素值。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对每个测试用例，输出 $P \cdot Q^{-1} \bmod (10^9+7)$ 的结果。

## 说明/提示

举个例子：
- 在第一个测试用例中，Sakurako 的朋友可以选择这些球对：$(a_1, a_2)$、$(a_1, a_3)$ 和 $(a_2, a_3)$。它们的乘积分别是 $3 \times 2 = 6$、$3 \times 3 = 9$ 和 $3 \times 2 = 6$，所以期望值计算结果为 $\frac{6 + 9 + 6}{3} = 7$。

- 在第二个测试用例中，朋友可以选择的球对有：$(a_1, a_2)$、$(a_1, a_3)$、$(a_1, a_4)$、$(a_2, a_3)$、$(a_2, a_4)$ 和 $(a_3, a_4)$。它们的乘积分别为 $2 \times 2 = 4$、$2 \times 2 = 4$、$2 \times 4 = 8$、$2 \times 2 = 4$、$2 \times 4 = 8$ 和 $2 \times 4 = 8$，所以期望值为 $\frac{4 + 4 + 8 + 4 + 8 + 8}{6} = \frac{36}{6} = 6$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3
3 2 3
4
2 2 2 4
5
1 2 3 4 5
```

### 输出

```
7
6
500000012
```



---

---
title: "Refined Product Optimality"
layout: "post"
diff: 普及+/提高
pid: CF2053D
tag: ['数学', '贪心', '排序', '逆元']
---

# Refined Product Optimality

## 题目描述

As a tester, when my solution has a different output from the example during testing, I suspect the author first.

— Chris, [a comment](https://codeforces.com/blog/entry/133116?#comment-1190579)



Although Iris occasionally sets a problem where the solution is possibly wrong, she still insists on creating problems with her imagination; after all, everyone has always been on the road with their stubbornness... And like ever before, Iris has set a problem to which she gave a wrong solution, but Chris is always supposed to save it! You are going to play the role of Chris now:

- Chris is given two arrays $ a $ and $ b $ , both consisting of $ n $ integers.
- Iris is interested in the largest possible value of $ P = \prod\limits_{i=1}^n \min(a_i, b_i) $ after an arbitrary rearrangement of $ b $ . Note that she only wants to know the maximum value of $ P $ , and no actual rearrangement is performed on $ b $ .
- There will be $ q $ modifications. Each modification can be denoted by two integers $ o $ and $ x $ ( $ o $ is either $ 1 $ or $ 2 $ , $ 1 \leq x \leq n $ ). If $ o = 1 $ , then Iris will increase $ a_x $ by $ 1 $ ; otherwise, she will increase $ b_x $ by $ 1 $ .
- Iris asks Chris the maximum value of $ P $ for $ q + 1 $ times: once before any modification, then after every modification.
- Since $ P $ might be huge, Chris only needs to calculate it modulo $ 998\,244\,353 $ .

Chris soon worked out this problem, but he was so tired that he fell asleep. Besides saying thanks to Chris, now it is your turn to write a program to calculate the answers for given input data.

Note: since the input and output are large, you may need to optimize them for this problem.

For example, in C++, it is enough to use the following lines at the start of the main() function:

```
<pre class="lstlisting">```
int main() {<br></br>    std::ios::sync_with_stdio(false);<br></br>    std::cin.tie(nullptr); std::cout.tie(nullptr);<br></br>}<br></br>
```
```

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \leq n \leq 2\cdot 10^5 $ , $ 1 \leq q \leq 2\cdot 10^5 $ ) — the length of the array and the number of operations.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 5\cdot 10^8 $ ) — the array $ a $ .

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq 5\cdot 10^8 $ ) — the array $ b $ .

Then $ q $ lines follow, each line contains two integers $ o $ and $ x $ ( $ o \in \{1, 2\} $ , $ 1 \leq x \leq n $ ), representing an operation.

It's guaranteed that the sum of $ n $ and the sum of $ q $ over all test cases does not exceed $ 4\cdot 10^5 $ , respectively.

## 输出格式

For each test case, output $ q + 1 $ integers in a line, representing the answers that Chris will calculate, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case:

- Before the modifications, Chris can rearrange $ b $ to $ [1, 2, 3] $ so that $ P = \prod\limits_{i=1}^n \min(a_i, b_i) = 1 \cdot 1 \cdot 2 = 2 $ . We can prove that this is the maximum possible value. For example, if Chris rearranges $ b = [2, 3, 1] $ , $ P $ will be equal $ 1 \cdot 1 \cdot 1 = 1 < 2 $ , which is not optimal.
- After the first modification, Chris can rearrange $ b $ to $ [1, 2, 3] $ so that $ P = 1 \cdot 1 \cdot 3 = 3 $ , which is maximized.
- After the second modification, Chris can rearrange $ b $ to $ [2, 2, 3] $ so that $ P = 1 \cdot 1 \cdot 3 = 3 $ , which is maximized.
- After the third modification, Chris can rearrange $ b $ to $ [2, 2, 3] $ so that $ P = 6 $ , which is maximized.
- After the fourth modification, Chris can rearrange $ b $ to $ [2, 2, 4] $ so that $ P = 6 $ , which is maximized.

## 样例 #1

### 输入

```
4
3 4
1 1 2
3 2 1
1 3
2 3
1 1
2 1
6 8
1 4 2 7 3 5
7 6 5 6 3 3
2 5
1 6
1 5
1 5
1 5
2 3
2 3
1 6
13 8
7 7 6 6 5 5 5 2 2 3 4 5 1
1 4 1 9 6 6 9 1 5 1 3 8 4
2 2
2 11
2 4
2 4
1 7
1 1
2 12
1 5
5 3
10000000 20000000 30000000 40000000 50000000
10000000 20000000 30000000 40000000 50000000
1 1
2 2
2 1
```

### 输出

```
2 3 3 6 6
840 840 1008 1344 1680 2016 2016 2016 2352
2116800 2646000 3528000 3528000 3528000 4233600 4838400 4838400 4838400
205272023 205272023 205272023 264129429
```



---

---
title: "Array"
layout: "post"
diff: 普及+/提高
pid: CF57C
tag: ['数学', '组合数学', '逆元']
---

# Array

## 题目描述

Chris the Rabbit has been interested in arrays ever since he was a child. At the moment he is researching arrays with the length of $ n $ , containing only integers from $ 1 $ to $ n $ . He is not good at math, that's why some simple things drive him crazy. For example, yesterday he grew keen on counting how many different beautiful arrays there are. Chris thinks that an array is beautiful if it meets one of the two conditions:

- each elements, starting from the second one, is no more than the preceding one
- each element, starting from the second one, is no less than the preceding one

Having got absolutely mad at himself and at math, Chris came to Stewie and Brian to ask them for help. However, they only laughed at him and said that the answer is too simple and not interesting. Help Chris the Rabbit to find the answer at last.

## 输入格式

The single line contains an integer $ n $ which is the size of the array ( $ 1<=n<=10^{5} $ ).

## 输出格式

You must print the answer on a single line. As it can be rather long, you should print it modulo $ 1000000007 $ .

## 样例 #1

### 输入

```
2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3

```

### 输出

```
17

```



---

---
title: "Line"
layout: "post"
diff: 普及+/提高
pid: CF7C
tag: ['最大公约数 gcd', '扩展欧几里德算法', '逆元']
---

# Line

## 题目描述

A line on the plane is described by an equation $ Ax+By+C=0 $ . You are to find any point on this line, whose coordinates are integer numbers from $ -5·10^{18} $ to $ 5·10^{18} $ inclusive, or to find out that such points do not exist.

## 输入格式

The first line contains three integers $ A $ , $ B $ and $ C $ ( $ -2·10^{9}<=A,B,C<=2·10^{9} $ ) — corresponding coefficients of the line equation. It is guaranteed that $ A^{2}+B^{2}>0 $ .

## 输出格式

If the required point exists, output its coordinates, otherwise output -1.

## 样例 #1

### 输入

```
2 5 3

```

### 输出

```
6 -3

```



---

