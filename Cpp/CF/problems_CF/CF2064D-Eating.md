---
title: "Eating"
layout: "post"
diff: 普及+/提高
pid: CF2064D
tag: []
---

# Eating

## 题目描述

There are $ n $ slimes on a line, the $ i $ -th of which has weight $ w_i $ . Slime $ i $ is able to eat another slime $ j $ if $ w_i \geq w_j $ ; afterwards, slime $ j $ disappears and the weight of slime $ i $ becomes $ w_i \oplus w_j $ $ ^{\text{∗}} $ .

The King of Slimes wants to run an experiment with parameter $ x $ as follows:

- Add a new slime with weight $ x $ to the right end of the line (after the $ n $ -th slime).
- This new slime eats the slime to its left if it is able to, and then takes its place (moves one place to the left). It will continue to do this until there is either no slime to its left or the weight of the slime to its left is greater than its own weight. (No other slimes are eaten during this process.)
- The score of this experiment is the total number of slimes eaten.

The King of Slimes is going to ask you $ q $ queries. In each query, you will be given an integer $ x $ , and you need to determine the score of the experiment with parameter $ x $ .

Note that the King does not want you to actually perform each experiment; his slimes would die, which is not ideal. He is only asking what the hypothetical score is; in other words, the queries are not persistent.

 $ ^{\text{∗}} $ Here $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the number of slimes and the number of queries, respectively.

The following line contains $ n $ integers $ w_1,w_2,\ldots,w_n $ ( $ 1 \le w_i < 2^{30} $ ) — the weights of the slimes.

The following $ q $ lines contain a single integer $ x $ ( $  1 \le x < 2^{30} $ ) — the parameter for the experiment.

The sum of $ n $ does not exceed $ 2 \cdot 10^5 $ and the sum of $ q $ does not exceed $ 2 \cdot 10^5 $ across all test cases.

## 输出格式

For each query, output a single integer — the score of the experiment.

## 说明/提示

For the first query of the second testcase:

- A slime of weight $ 8 $ would be added to the end, so $ w = [1, 5, 4, 11, \color{red}8] $ .
- The added slime has smaller weight than the slime to its left so it cannot eat it, and thus ends the process after eating no slimes with score $ 0 $ .

 For the second query of the second testcase: - A slime of weight $ 13 $ would be added to the end, so $ w = [1, 5, 4, 11, \color{red}{13}] $ .
- The added slime has bigger weight than the slime to its left, and so it will eat it. Its weight will become $ 13 \oplus 11 = 6 $ . Now $ w = [1, 5, 4, \color{red}{6}] $ .
- The added slime will now eat the slime to its left, and its weight becomes $ 6 \oplus 4 = 2 $ . Now $ w = [1, 5, \color{red}{2}] $ .
- The added slime is no longer able to eat the slime to its left, so it ends the process with a score of $ 2 $ .

## 样例 #1

### 输入

```
3
1 1
5
6
4 4
1 5 4 11
8
13
16
15
10 9
10 4 3 9 7 4 6 1 9 4
2
6
5
6
9
8
6
2
7
```

### 输出

```
1
0 2 4 2
0 1 1 1 3 3 1 0 1
```

