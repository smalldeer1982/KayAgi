---
title: "Bag of mice"
layout: "post"
diff: 普及+/提高
pid: CF148D
tag: ['搜索', '记忆化搜索', '期望']
---

# Bag of mice

## 题目描述

The dragon and the princess are arguing about what to do on the New Year's Eve. The dragon suggests flying to the mountains to watch fairies dancing in the moonlight, while the princess thinks they should just go to bed early. They are desperate to come to an amicable agreement, so they decide to leave this up to chance.

They take turns drawing a mouse from a bag which initially contains $ w $ white and $ b $ black mice. The person who is the first to draw a white mouse wins. After each mouse drawn by the dragon the rest of mice in the bag panic, and one of them jumps out of the bag itself (the princess draws her mice carefully and doesn't scare other mice). Princess draws first. What is the probability of the princess winning?

If there are no more mice in the bag and nobody has drawn a white mouse, the dragon wins. Mice which jump out of the bag themselves are not considered to be drawn (do not define the winner). Once a mouse has left the bag, it never returns to it. Every mouse is drawn from the bag with the same probability as every other one, and every mouse jumps out of the bag with the same probability as every other one.

## 输入格式

The only line of input data contains two integers $ w $ and $ b $ ( $ 0<=w,b<=1000 $ ).

## 输出格式

Output the probability of the princess winning. The answer is considered to be correct if its absolute or relative error does not exceed $ 10^{-9} $ .

## 说明/提示

Let's go through the first sample. The probability of the princess drawing a white mouse on her first turn and winning right away is 1/4. The probability of the dragon drawing a black mouse and not winning on his first turn is 3/4 \* 2/3 = 1/2. After this there are two mice left in the bag — one black and one white; one of them jumps out, and the other is drawn by the princess on her second turn. If the princess' mouse is white, she wins (probability is 1/2 \* 1/2 = 1/4), otherwise nobody gets the white mouse, so according to the rule the dragon wins.

## 样例 #1

### 输入

```
1 3

```

### 输出

```
0.500000000

```

## 样例 #2

### 输入

```
5 5

```

### 输出

```
0.658730159

```



---

---
title: "Expected Power"
layout: "post"
diff: 普及+/提高
pid: CF2020E
tag: ['动态规划 DP', '期望']
---

# Expected Power

## 题目描述

You are given an array of $ n $ integers $ a_1,a_2,\ldots,a_n $ . You are also given an array $ p_1, p_2, \ldots, p_n $ .

Let $ S $ denote the random multiset (i. e., it may contain equal elements) constructed as follows:

- Initially, $ S $ is empty.
- For each $ i $ from $ 1 $ to $ n $ , insert $ a_i $ into $ S $ with probability $ \frac{p_i}{10^4} $ . Note that each element is inserted independently.

Denote $ f(S) $ as the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all elements of $ S $ . Please calculate the expected value of $ (f(S))^2 $ . Output the answer modulo $ 10^9 + 7 $ .

Formally, let $ M = 10^9 + 7 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ).

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le 1023 $ ).

The third line of each test case contains $ n $ integers $ p_1,p_2,\ldots,p_n $ ( $ 1 \le p_i \le 10^4 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the expected value of $ (f(S))^2 $ , modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case, $ a = [1, 2] $ and each element is inserted into $ S $ with probability $ \frac{1}{2} $ , since $ p_1 = p_2 = 5000 $ and $ \frac{p_i}{10^4} = \frac{1}{2} $ . Thus, there are $ 4 $ outcomes for $ S $ , each happening with the same probability of $ \frac{1}{4} $ :

- $ S = \varnothing $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ .
- $ S = \{1\} $ . In this case, $ f(S) = 1 $ , $ (f(S))^2 = 1 $ .
- $ S = \{2\} $ . In this case, $ f(S) = 2 $ , $ (f(S))^2 = 4 $ .
- $ S = \{1,2\} $ . In this case, $ f(S) = 1 \oplus 2 = 3 $ , $ (f(S))^2 = 9 $ .

Hence, the answer is $ 0 \cdot \frac{1}{4} + 1 \cdot \frac{1}{4} + 4\cdot \frac{1}{4} + 9 \cdot \frac{1}{4} = \frac{14}{4} = \frac{7}{2} \equiv 500\,000\,007 \pmod{10^9 + 7} $ .

In the second test case, $ a = [1, 1] $ , $ a_1 $ is inserted into $ S $ with probability $ 0.1 $ , while $ a_2 $ is inserted into $ S $ with probability $ 0.2 $ . There are $ 3 $ outcomes for $ S $ :

- $ S = \varnothing $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ . This happens with probability $ (1-0.1) \cdot (1-0.2) = 0.72 $ .
- $ S = \{1\} $ . In this case, $ f(S) = 1 $ , $ (f(S))^2 = 1 $ . This happens with probability $ (1-0.1) \cdot 0.2 + 0.1 \cdot (1-0.2) = 0.26 $ .
- $ S = \{1, 1\} $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ . This happens with probability $ 0.1 \cdot 0.2 = 0.02 $ .

Hence, the answer is $ 0 \cdot 0.72 + 1 \cdot 0.26 + 0 \cdot 0.02 = 0.26 = \frac{26}{100} \equiv 820\,000\,006 \pmod{10^9 + 7} $ .

## 样例 #1

### 输入

```
4
2
1 2
5000 5000
2
1 1
1000 2000
6
343 624 675 451 902 820
6536 5326 7648 2165 9430 5428
1
1
10000
```

### 输出

```
500000007
820000006
280120536
1
```



---

