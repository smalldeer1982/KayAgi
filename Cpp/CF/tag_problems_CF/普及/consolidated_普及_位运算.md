---
title: "Bit Flipping"
layout: "post"
diff: 普及/提高-
pid: CF1659B
tag: ['贪心', '位运算']
---

# Bit Flipping

## 题目描述

You are given a binary string of length $ n $ . You have exactly $ k $ moves. In one move, you must select a single bit. The state of all bits except that bit will get flipped ( $ 0 $ becomes $ 1 $ , $ 1 $ becomes $ 0 $ ). You need to output the lexicographically largest string that you can get after using all $ k $ moves. Also, output the number of times you will select each bit. If there are multiple ways to do this, you may output any of them.

A binary string $ a $ is lexicographically larger than a binary string $ b $ of the same length, if and only if the following holds:

- in the first position where $ a $ and $ b $ differ, the string $ a $ contains a $ 1 $ , and the string $ b $ contains a $ 0 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case has two lines. The first line has two integers $ n $ and $ k $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ; $ 0 \leq k \leq 10^9 $ ).

The second line has a binary string of length $ n $ , each character is either $ 0 $ or $ 1 $ .

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output two lines.

The first line should contain the lexicographically largest string you can obtain.

The second line should contain $ n $ integers $ f_1, f_2, \ldots, f_n $ , where $ f_i $ is the number of times the $ i $ -th bit is selected. The sum of all the integers must be equal to $ k $ .

## 说明/提示

Here is the explanation for the first testcase. Each step shows how the binary string changes in a move.

- Choose bit $ 1 $ : $ \color{red}{\underline{1}00001} \rightarrow \color{red}{\underline{1}}\color{blue}{11110} $ .
- Choose bit $ 4 $ : $ \color{red}{111\underline{1}10} \rightarrow \color{blue}{000}\color{red}{\underline{1}}\color{blue}{01} $ .
- Choose bit $ 4 $ : $ \color{red}{000\underline{1}01} \rightarrow \color{blue}{111}\color{red}{\underline{1}}\color{blue}{10} $ .

 The final string is $ 111110 $ and this is the lexicographically largest string we can get.

## 样例 #1

### 输入

```
6
6 3
100001
6 4
100011
6 0
000000
6 1
111001
6 11
101100
6 12
001110
```

### 输出

```
111110
1 0 0 2 0 0 
111110
0 1 1 1 0 1 
000000
0 0 0 0 0 0 
100110
1 0 0 0 0 0 
111111
1 2 1 3 0 4 
111110
1 1 4 2 0 4
```



---

---
title: "Even-Odd XOR"
layout: "post"
diff: 普及/提高-
pid: CF1722G
tag: ['位运算', '构造']
---

# Even-Odd XOR

## 题目描述

给定一个正整数 $n$，请你找出一个长度为 $n$ 数组 $a$，满足数组是由互不相同的非负且小于 $2^{31}$ 的整数组成，并且该数组中奇数项上元素的[异或和](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)与偶数项上元素的异或和要相等。

## 输入格式

输入的第一行为一个整数 $t$ $(1 \leq t \leq 629)$，表示测试点的数量。

接下来 $t$ 行，每行一个整数 $n$ $(3 \leq n \leq 2 \times 10^5)$，表示数组的长度。

保证所有测试点中 $n$ 的总和不超过 $2 \times 10^5$。

## 输出格式

对于每个测试点，在一行中输出 $n$ 个不同的满足条件的整数。

如果有多种答案，你可以输出任意一种。

### 样例解释

在第一个测试点中，奇数项的异或和为 $4 \oplus 1 \oplus 0 \oplus 7 = 2$；偶数项的异或和为 $2 \oplus 5 \oplus 6 \oplus 3 = 2$。

## 样例 #1

### 输入

```
7
8
3
4
5
6
7
9
```

### 输出

```
4 2 1 5 0 6 7 3
2 1 3
2 1 3 0
2 0 4 5 3
4 1 2 12 3 8
1 2 3 4 5 6 7
8 2 3 7 4 0 5 6 9
```



---

---
title: "Gardener and the Array"
layout: "post"
diff: 普及/提高-
pid: CF1775B
tag: ['位运算', '构造']
---

# Gardener and the Array

## 题目描述

The gardener Kazimir Kazimirovich has an array of $ n $ integers $ c_1, c_2, \dots, c_n $ .

He wants to check if there are two different subsequences $ a $ and $ b $ of the original array, for which $ f(a) = f(b) $ , where $ f(x) $ is the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of all of the numbers in the sequence $ x $ .

A sequence $ q $ is a subsequence of $ p $ if $ q $ can be obtained from $ p $ by deleting several (possibly none or all) elements.

Two subsequences are considered different if the sets of indexes of their elements in the original sequence are different, that is, the values of the elements are not considered when comparing the subsequences.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775B/01e7b88f6704ebb4d7f093f81e886f156c238509.png)

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the size of the array $ c $ .

The description of the array $ c $ in this problem is given implicitly to speed up input.

The $ (i + 1) $ -st of the following $ n $ lines of the test case begins with an integer $ k_i $ ( $ 1 \le k_i \le 10^5 $ ) — the number of set bits in the number $ c_i $ . Next follow $ k_i $ distinct integers $ p_{i, 1}, p_{i, 2}, \dots, p_{i, k_i} $ ( $ 1 \le p_i \le 2 \cdot 10^5 $ ) —the numbers of bits that are set to one in number $ c_i $ . In other words, $ c_i = 2^{p_{i, 1}} + 2^{p_{i, 2}} + \ldots + 2^{p_{i, k_i}} $ .

It is guaranteed that the total sum of $ k_i $ in all tests does not exceed $ 10^5 $ .

## 输出格式

For each set of input, print "Yes" if there exist two different subsequences for which $ f(a) = f(b) $ , and "No" otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

It can be proven that in the first test case there are no two different subsequences $ a $ and $ b $ for which $ f(a) = f(b) $ .

In the second test case, one of the possible answers are following subsequences: the subsequence $ a $ formed by the element at position $ 1 $ , and the subsequence $ b $ formed by the elements at positions $ 1 $ and $ 2 $ .

In the third test case, one of the possible answers are following subsequences: the subsequence $ a $ formed by elements at positions $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , and the subsequence $ b $ formed by elements at positions $ 2 $ , $ 3 $ and $ 4 $ .

## 样例 #1

### 输入

```
5
3
2 1 5
2 2 4
2 2 3
2
2 1 2
1 2
4
3 1 2 4
2 2 4
4 1 2 5 6
2 2 5
5
3 3 1 2
3 2 5 3
5 7 2 3 1 4
5 1 2 6 3 5
3 2 6 3
2
1 1
1 2
```

### 输出

```
No
Yes
Yes
Yes
No
```



---

---
title: "Equal XOR"
layout: "post"
diff: 普及/提高-
pid: CF1944B
tag: ['位运算', '构造']
---

# Equal XOR

## 题目描述

You are given an array $ a $ of length $ 2n $ , consisting of each integer from $ 1 $ to $ n $ exactly twice.

You are also given an integer $ k $ ( $ 1 \leq k \leq \lfloor \frac{n}{2} \rfloor  $ ).

You need to find two arrays $ l $ and $ r $ each of length $ \mathbf{2k} $ such that:

- $ l $ is a subset $ ^\dagger $ of $ [a_1, a_2, \ldots a_n] $
- $ r $ is a subset of $ [a_{n+1}, a_{n+2}, \ldots a_{2n}] $
- [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of elements of $ l $ is equal to the bitwise XOR of elements of $ r $ ; in other words, $ l_1 \oplus l_2 \oplus \ldots \oplus l_{2k} = r_1 \oplus r_2 \oplus \ldots \oplus r_{2k} $

It can be proved that at least one pair of $ l $ and $ r $ always exists. If there are multiple solutions, you may output any one of them.

 $ ^\dagger $ A sequence $ x $ is a subset of a sequence $ y $ if $ x $ can be obtained by deleting several (possibly none or all) elements of $ y $ and rearranging the elements in any order. For example, $ [3,1,2,1] $ , $ [1, 2, 3] $ , $ [1, 1] $ and $ [3, 2] $ are subsets of $ [1, 1, 2, 3] $ but $ [4] $ and $ [2, 2] $ are not subsets of $ [1, 1, 2, 3] $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 5000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains $ 2 $ integers $ n $ and $ k $ ( $ 2 \le n \le 5 \cdot 10^4 $ , $ 1 \leq k \leq \lfloor \frac{n}{2} \rfloor  $ ).

The second line contains $ 2n $ integers $ a_1, a_2, \ldots, a_{2n} $ ( $ 1 \le a_i \le n $ ). It is guaranteed that every integer from $ 1 $ to $ n $ occurs exactly twice in $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^4 $ .

## 输出格式

For each test case, output two lines.

On the first line of output, output $ 2k $ integers $ l_1, l_2, \ldots, l_{2k} $ .

On the second line of output, output $ 2k $ integers $ r_1, r_2, \ldots r_{2k} $ .

If there are multiple solutions, you may output any one of them.

## 说明/提示

In the first test case, we choose $ l=[2,1] $ and $ r=[2,1] $ . $ [2, 1] $ is a subset of $ [a_1, a_2] $ and $ [2, 1] $ is a subset of $ [a_3, a_4] $ , and $ 2 \oplus 1 = 2 \oplus 1 = 3 $ .

In the second test case, $ 6 \oplus 4 = 1 \oplus 3 = 2 $ .

## 样例 #1

### 输入

```
4
2 1
1 2 2 1
6 1
6 4 2 1 2 3 1 6 3 5 5 4
4 1
1 2 3 4 1 2 3 4
6 2
5 1 3 3 5 1 2 6 4 6 4 2
```

### 输出

```
2 1
2 1
6 4
1 3
1 2
1 2
5 1 3 3
6 4 2 4
```



---

---
title: "A BIT of a Construction"
layout: "post"
diff: 普及/提高-
pid: CF1957B
tag: ['贪心', '位运算']
---

# A BIT of a Construction

## 题目描述

给定 $n,k$，请构造序列 $a_n$，你需要保证 $a_i$ 为自然数，同时满足以下条件：

* $\sum\limits_{i=1}^{n} a_i=k$。

* $a_1|a_2|\dots|a_n$ 二进制下拆位后 $1$ 的数量最大，其中 $|$ 表示[按位或](https://baike.baidu.com/item/%E6%8C%89%E4%BD%8D%E6%88%96/548283?fr=ge_ala)。

## 输入格式

第一行一个整数 $t$，表示数据组数。

接下来对于每组数据，共一行两个整数 $n,k$。

## 输出格式

共 $t$ 行，每行 $n$ 个整数，表示构造的 $a_n$。

如果有多个解，输出任意解即可。

## 说明/提示

对于全部数据，满足 $1\le t\le10^4$，$1\le n\le2\times10^5$，$1\le k\le10^9$，$\sum n\le2\times10^5$。

## 样例 #1

### 输入

```
4
1 5
2 3
2 5
6 51
```

### 输出

```
5
1 2
5 0
3 1 1 32 2 12
```



---

---
title: "XOUR"
layout: "post"
diff: 普及/提高-
pid: CF1971G
tag: ['贪心', '堆', '位运算']
---

# XOUR

## 题目描述

You are given an array $ a $ consisting of $ n $ nonnegative integers.

You can swap the elements at positions $ i $ and $ j $ if $ a_i~\mathsf{XOR}~a_j < 4 $ , where $ \mathsf{XOR} $ is the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Find the lexicographically smallest array that can be made with any number of swaps.

An array $ x $ is lexicographically smaller than an array $ y $ if in the first position where $ x $ and $ y $ differ, $ x_i < y_i $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2\cdot10^5 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_i $ ( $ 0 \leq a_i \leq 10^9 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers — the lexicographically smallest array that can be made with any number of swaps.

## 说明/提示

For the first test case, you can swap any two elements, so we can produce the sorted array.

For the second test case, you can swap $ 2 $ and $ 1 $ (their $ \mathsf{XOR} $ is $ 3 $ ), $ 7 $ and $ 5 $ (their $ \mathsf{XOR} $ is $ 2 $ ), and $ 7 $ and $ 6 $ (their $ \mathsf{XOR} $ is $ 1 $ ) to get the lexicographically smallest array.

## 样例 #1

### 输入

```
4
4
1 0 3 2
5
2 7 1 5 6
8
1 2 1 2 1 2 1 2
4
16 4 1 64
```

### 输出

```
0 1 2 3 
1 5 2 6 7 
1 1 1 1 2 2 2 2 
16 4 1 64
```



---

---
title: "Cat, Fox and the Lonely Array"
layout: "post"
diff: 普及/提高-
pid: CF1973B
tag: ['二分', '位运算']
---

# Cat, Fox and the Lonely Array

## 题目描述

Today, Cat and Fox found an array $ a $ consisting of $ n $ non-negative integers.

Define the loneliness of $ a $ as the smallest positive integer $ k $ ( $ 1 \le k \le n $ ) such that for any two positive integers $ i $ and $ j $ ( $ 1 \leq i, j \leq n - k +1 $ ), the following holds: $ $$$a_i | a_{i+1} | \ldots | a_{i+k-1} = a_j | a_{j+1} | \ldots | a_{j+k-1}, $ $  where  $ x | y $  denotes the <a href="https://en.wikipedia.org/wiki/Bitwise_operation#OR">bitwise OR</a> of  $ x $  and  $ y $ . In other words, for every  $ k $  consecutive elements, their bitwise OR should be the same. Note that the loneliness of  $ a $  is well-defined, because for  $ k = n $  the condition is satisfied.</p><p>Cat and Fox want to know how lonely the array  $ a$$$ is. Help them calculate the loneliness of the found array.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4  $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < 2^{20} $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 10^5 $ .

## 输出格式

For each test case, print one integer — the loneliness of the given array.

## 说明/提示

In the first example, the loneliness of an array with a single element is always $ 1 $ , so the answer is $ 1 $ .

In the second example, the OR of each subarray of length $ k = 1 $ is $ 2 $ , so the loneliness of the whole array is $ 1 $ .

In the seventh example, it's true that $ (0 | 1 | 3) = (1 | 3 | 2) = (3 | 2 | 2) = (2 | 2 | 1) = (2 | 1 | 0) = (1 | 0 | 3) = 3 $ , so the condition is satisfied for $ k = 3 $ . We can verify that the condition is not true for any smaller $ k $ , so the answer is indeed $ 3 $ .

## 样例 #1

### 输入

```
7
1
0
3
2 2 2
3
1 0 2
5
3 0 1 4 2
5
2 0 4 0 2
7
0 0 0 0 1 2 4
8
0 1 3 2 2 1 0 3
```

### 输出

```
1
1
3
4
4
7
3
```



---

---
title: "Turtle and an Infinite Sequence"
layout: "post"
diff: 普及/提高-
pid: CF1981B
tag: ['位运算']
---

# Turtle and an Infinite Sequence

## 题目描述

There is a sequence $ a_0, a_1, a_2, \ldots $ of infinite length. Initially $ a_i = i $ for every non-negative integer $ i $ .

After every second, each element of the sequence will simultaneously change. $ a_i $ will change to $ a_{i - 1} \mid a_i \mid a_{i + 1} $ for every positive integer $ i $ . $ a_0 $ will change to $ a_0 \mid a_1 $ . Here, $ | $ denotes [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

Turtle is asked to find the value of $ a_n $ after $ m $ seconds. In particular, if $ m = 0 $ , then he needs to find the initial value of $ a_n $ . He is tired of calculating so many values, so please help him!

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n, m $ ( $ 0 \le n, m \le 10^9 $ ).

## 输出格式

For each test case, output a single integer — the value of $ a_n $ after $ m $ seconds.

## 说明/提示

After $ 1 $ second, $ [a_0, a_1, a_2, a_3, a_4, a_5] $ will become $ [1, 3, 3, 7, 7, 7] $ .

After $ 2 $ seconds, $ [a_0, a_1, a_2, a_3, a_4, a_5] $ will become $ [3, 3, 7, 7, 7, 7] $ .

## 样例 #1

### 输入

```
9
0 0
0 1
0 2
1 0
5 2
10 1
20 3
1145 14
19198 10
```

### 输出

```
0
1
3
1
7
11
23
1279
19455
```



---

---
title: "Increasing Sequence with Fixed OR"
layout: "post"
diff: 普及/提高-
pid: CF1988C
tag: ['贪心', '位运算']
---

# Increasing Sequence with Fixed OR

## 题目描述

You are given a positive integer $ n $ . Find the longest sequence of positive integers $ a=[a_1,a_2,\ldots,a_k] $ that satisfies the following conditions, and print the sequence:

- $ a_i\le n $ for all $ 1\le i\le k $ .
- $ a $ is strictly increasing. That is, $ a_i>a_{i-1} $ for all $ 2\le i\le k $ .
- $ a_i\,|\,a_{i-1}=n $ for all $ 2\le i\le k $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). Description of the test cases follows.

The only line of each test case contains one integer $ n $ ( $ 1\le n\le 10^{18} $ ).

It's guaranteed that the sum of lengths of the longest valid sequences does not exceed $ 5\cdot 10^5 $ .

## 输出格式

For each testcase, print two lines. In the first line, print the length of your constructed sequence, $ k $ . In the second line, print $ k $ positive integers, denoting the sequence. If there are multiple longest sequences, you can print any of them.

## 样例 #1

### 输入

```
4
1
3
14
23
```

### 输出

```
1
1
3
1 2 3
4
4 10 12 14
5
7 18 21 22 23
```



---

---
title: "Bitwise Balancing"
layout: "post"
diff: 普及/提高-
pid: CF2020C
tag: ['位运算']
---

# Bitwise Balancing

## 题目描述

# 位运算平衡


给定三个非负整数 $ b $ 、$ c $ 和 $ d $ 。

请找到一个非负整数 $ a \in [0, 2^{61}] $ 使得 $ (a\, |\, b)-(a\, \&\, c)=d $ ，其中 $ | $ 和 $ \& $ 分别表示[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)和[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)。

如果存在这样的 $ a $ ，请输出它的值。如果没有解，请输出整数 $ -1 $ 。如果存在多个解，输出其中任意一个。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $ t $ ( $ 1 \le t \le 10^5 $ )。每个测试用例的描述如下。

每个测试用例的唯一一行包含三个正整数 $ b $ 、$ c $ 和 $ d $ ( $ 0 \le b, c, d \le 10^{18} $ )。

## 输出格式

对于每个测试用例，输出 $ a $ 的值，或者如果没有解则输出 $ -1 $ 。请注意，$ a $ 必须是非负数，并且不能超过 $ 2^{61} $ 。

## 说明/提示

在第一个测试用例中，$ (0\,|\,2)-(0\,\&\,2)=2-0=2 $ 。因此，$ a = 0 $ 是一个正确答案。

在第二个测试用例中，没有任何值 $ a $ 满足方程。

在第三个测试用例中，$ (12\,|\,10)-(12\,\&\,2)=14-0=14 $ 。因此，$ a = 12 $ 是一个正确答案。

## 样例 #1

### 输入

```
3
2 2 2
4 2 6
10 2 14
```

### 输出

```
0
-1
12
```



---

---
title: "A TRUE Battle"
layout: "post"
diff: 普及/提高-
pid: CF2030C
tag: ['贪心', '位运算']
---

# A TRUE Battle

## 题目描述

Alice and Bob are playing a game. There is a list of $ n $ booleans, each of which is either true or false, given as a binary string $ ^{\text{∗}} $ of length $ n $ (where $ \texttt{1} $ represents true, and $ \texttt{0} $ represents false). Initially, there are no operators between the booleans.

Alice and Bob will take alternate turns placing and or or between the booleans, with Alice going first. Thus, the game will consist of $ n-1 $ turns since there are $ n $ booleans. Alice aims for the final statement to evaluate to true, while Bob aims for it to evaluate to false. Given the list of boolean values, determine whether Alice will win if both players play optimally.

To evaluate the final expression, repeatedly perform the following steps until the statement consists of a single true or false:

- If the statement contains an and operator, choose any one and replace the subexpression surrounding it with its evaluation.
- Otherwise, the statement contains an or operator. Choose any one and replace the subexpression surrounding the or with its evaluation.

 For example, the expression true or false and false is evaluated as true or (false and false) $ = $ true or false $ = $ true. It can be shown that the result of any compound statement is unique. $ ^{\text{∗}} $ A binary string is a string that only consists of characters $ \texttt{0} $ and $ \texttt{1} $

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the length of the string.

The second line contains a binary string of length $ n $ , consisting of characters $ \texttt{0} $ and $ \texttt{1} $ — the list of boolean values.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, output "YES" (without quotes) if Alice wins, and "NO" (without quotes) otherwise.

You can output "YES" and "NO" in any case (for example, strings "yES", "yes" and "Yes" will be recognized as a positive response).

## 说明/提示

In the first testcase, Alice can place and between the two booleans. The game ends as there are no other places to place operators, and Alice wins because true and true is true.

In the second testcase, Alice can place or between the middle true and the left false. Bob can place and between the middle true and the right false. The statement false or true and false is false.

Note that these examples may not be the best strategies for either Alice or Bob.

## 样例 #1

### 输入

```
5
2
11
3
010
12
101111111100
10
0111111011
8
01000010
```

### 输出

```
YES
NO
YES
YES
NO
```



---

---
title: "Kevin and Binary Strings"
layout: "post"
diff: 普及/提高-
pid: CF2048C
tag: ['贪心', '位运算']
---

# Kevin and Binary Strings

## 题目描述

Kevin 在月光河公园的河里发现了一个二进制字符串 $s$，它以 1 开头，并把它交给了你。你的任务是从 $s$ 中选择两个非空子串（允许重叠），以使得它们之间的异或值最大。

对于两个二进制字符串 $a$ 和 $b$，它们的异或结果是将 $a$ 和 $b$ 看作二进制数后，进行按位异或操作 $\oplus$ 所得到的结果，其中最左边的位即为最高位。可以参考[按位异或操作](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

你选择的字符串可以包含前导零。

## 输入格式

输入包含多个测试用例。第一行是测试用例的数量 $t$（$1 \le t \le 10^3$）。

接下来的每个测试用例有一行，包含一个以 1 开头的二进制字符串 $s$（$1 \le |s| \le 5000$）。

保证所有测试用例中 $|s|$ 的总长度不超过 $5000$。

## 输出格式

对于每个测试用例，输出四个整数 $l_1, r_1, l_2, r_2$（$1 \le l_1 \le r_1 \le |s|$, $1 \le l_2 \le r_2 \le |s|$）——表示你选择的两个子串分别是 $s_{l_1} s_{l_1 + 1} \ldots s_{r_1}$ 和 $s_{l_2} s_{l_2 + 1} \ldots s_{r_2}$。

如果存在多种可能的解，输出任意一种即可。

## 说明/提示

在第一个测试用例中，我们可以选择 $s_2 = \texttt{1}$ 和 $s_1 s_2 s_3 = \texttt{111}$，此时 $\texttt{1} \oplus \texttt{111} = \texttt{110}$。可以证明这是可能得到的最大值。此外，选择 $l_1 = 3$，$r_1 = 3$，$l_2 = 1$，$r_2 = 3$ 也是一个有效的解决方案。

在第二个测试用例中，选择 $s_1 s_2 s_3 = \texttt{100}$ 和 $s_1 s_2 s_3 s_4 = \texttt{1000}$，则异或结果为 $\texttt{100} \oplus \texttt{1000} = \texttt{1100}$，也是最大的结果。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
111
1000
10111
11101
1100010001101
```

### 输出

```
2 2 1 3
1 3 1 4
1 5 1 4
3 4 1 5
1 13 1 11
```



---

---
title: "Creating Keys for StORages Has Become My Main Skill"
layout: "post"
diff: 普及/提高-
pid: CF2072C
tag: ['贪心', '位运算', '构造']
---

# Creating Keys for StORages Has Become My Main Skill

## 题目描述

Akito 仍然无处可住，而小房间的价格却居高不下。为此，Akito 决定在银行找一份为存储设备创建密钥的工作。

在这个魔法世界中，一切都与众不同。例如，代码为 $(n, x)$ 的存储设备的密钥是一个满足以下条件的长度为 $n$ 的数组 $a$：

- $a_1 \mid a_2 \mid a_3 \mid \ldots \mid a_n = x$，其中 $a \mid b$ 表示数 $a$ 和 $b$ 的[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。
- $\text{MEX}(\{ a_1, a_2, a_3, \ldots, a_n \})$ $^{\text{∗}}$ 在所有满足条件的数组中达到最大值。

Akito 勤奋地工作了几个小时，但突然头痛发作。请代替他工作一小时：对于给定的 $n$ 和 $x$，创建任意一个满足代码为 $(n, x)$ 的存储设备的密钥。

$^{\text{∗}}$ $\text{MEX}(S)$ 是满足以下条件的最小非负整数 $z$：$z$ 不在集合 $S$ 中，且所有满足 $0 \le y < z$ 的 $y$ 都在集合 $S$ 中。

## 输入格式

第一行包含一个数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的唯一一行包含两个数 $n$ 和 $x$（$1 \le n \le 2 \cdot 10^5$，$0 \le x < 2^{30}$）——数组的长度和按位或运算的目标值。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数 $a_i$（$0 \le a_i < 2^{30}$）——满足所有条件的密钥数组元素。

如果存在多个符合条件的数组，输出其中任意一个即可。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
9
1 69
7 7
5 7
7 3
8 7
3 52
9 11
6 15
2 3
```

### 输出

```
69
6 0 3 4 1 2 5
4 1 3 0 2
0 1 2 3 2 1 0
7 0 6 1 5 2 4 3
0 52 0
0 1 8 3 0 9 11 2 10
4 0 3 8 1 2
0 3
```



---

---
title: "XOR and Triangle"
layout: "post"
diff: 普及/提高-
pid: CF2074C
tag: ['位运算', '构造']
---

# XOR and Triangle

## 题目描述

这次，粉色士兵们给了你一个整数 $x$（$x \ge 2$）。

请判断是否存在一个正整数 $y$ 满足以下条件：

- $y$ 严格小于 $x$
- 存在一个非退化三角形$^{\text{∗}}$，其边长为 $x$、$y$ 和 $x \oplus y$。其中 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

若存在这样的整数 $y$，请输出任意一个满足条件的值。

$^{\text{∗}}$当边长为 $a$、$b$、$c$ 的三角形满足 $a + b > c$、$a + c > b$ 且 $b + c > a$ 时，该三角形是非退化的。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 2000$）。接下来是每个测试用例的描述。

每个测试用例的单独一行包含一个整数 $x$（$2 \le x \le 10^9$）。

## 输出格式

对于每个测试用例，在单独一行中输出一个整数：

- 若存在满足条件的整数 $y$，输出 $y$ 的值（$1 \le y < x$）
- 否则输出 $-1$

若存在多个满足条件的整数，可以输出任意一个。

## 说明/提示

在第一个测试用例中，存在边长为 $3$、$5$ 和 $3 \oplus 5 = 6$ 的非退化三角形。因此 $y=3$ 是有效答案。

在第二个测试用例中，$1$ 是 $y$ 的唯一可能候选值，但无法构成非退化三角形。因此答案为 $-1$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
7
5
2
6
3
69
4
420
```

### 输出

```
3
-1
5
-1
66
-1
320
```



---

---
title: "Serval and The Formula"
layout: "post"
diff: 普及/提高-
pid: CF2085C
tag: ['贪心', '进制', '位运算']
---

# Serval and The Formula

## 题目描述

给定两个正整数 $x$ 和 $y$（$1 \le x, y \le 10^9$）。

请找到一个非负整数 $k \le 10^{18}$，使得等式 $(x + k) + (y + k) = (x + k) \oplus (y + k)$ 成立$^{\text{∗}}$，或判断这样的整数不存在。

$^{\text{∗}}$符号 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。


## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的唯一一行包含两个整数 $x$ 和 $y$（$1 \le x, y \le 10^9$）——给定的整数。


## 输出格式

对于每个测试用例，输出一个整数 $k$（$0 \le k \le 10^{18}$）——找到的符合条件的整数。若不存在这样的整数，输出 $-1$。

若存在多个答案，输出任意一个即可。

## 说明/提示

第一个测试案例中，由于 $(2 + 0) + (5 + 0) = (2 + 0) \oplus (5 + 0) = 7$，因此 $k = 0$ 是合法答案。注意 $k = 4$ 也是一个合法答案，因为 $(2 + 4) + (5 + 4) = (2 + 4) \oplus (5 + 4) = 15$。

第二个测试案例中，$(x + k) \oplus (y + k) = (6 + k) \oplus (6 + k) = 0$。然而对于所有 $k \ge 0$，$(x + k) + (y + k) > 0$ 恒成立，因此这样的整数 $k$ 不存在。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
2 5
6 6
19 10
1024 4096
1198372 599188
```

### 输出

```
0
-1
1
1024
28
```



---

---
title: "Boneca Ambalabu"
layout: "post"
diff: 普及/提高-
pid: CF2094E
tag: ['贪心', '位运算']
---

# Boneca Ambalabu

## 题目描述

Boneca Ambalabu 给你一个包含 $n$ 个整数的序列 $a_1,a_2,\ldots,a_n$。

在所有 $1 \leq k \leq n$ 中，输出 $(a_k \oplus a_1) + (a_k \oplus a_2) + \ldots + (a_k \oplus a_n)$ 的最大值。注意 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——独立测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 2 \cdot 10^5$）——数组的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1,a_2,\ldots,a_n$（$0 \leq a_i < 2^{30}$）。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，在新的一行输出最大值。

## 说明/提示

在第一个测试用例中，我们能得到的最大值是 $(18 \oplus 18) + (18 \oplus 18) + (18 \oplus 18) = 0$。

在第二个测试用例中，我们选择 $k=5$ 得到 $(16 \oplus 1) + (16 \oplus 2) + (16 \oplus 4) + (16 \oplus 8) + (16 \oplus 16) = 79$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
18 18 18
5
1 2 4 8 16
5
8 13 4 5 15
6
625 676 729 784 841 900
1
1
```

### 输出

```
0
79
37
1555
0
```



---

---
title: "SUMdamental Decomposition"
layout: "post"
diff: 普及/提高-
pid: CF2108B
tag: ['位运算', '分类讨论']
---

# SUMdamental Decomposition

## 题目描述

在最近的一次生日中，你最好的朋友 Maurice 给了你一对数字 $n$ 和 $x$，并要求你构造一个长度为 $n$ 的正数数组 $a$，使得 $a_1 \oplus a_2 \oplus \cdots \oplus a_n = x$ $^{\text{∗}}$。

这个任务对你来说太简单了，因此你决定给 Maurice 一个回礼：在所有满足条件的数组中，构造一个元素和最小的数组。你立刻想到了一个合适的数组；然而，由于把它写下来太费时间，Maurice 只能得到它的元素和。

$^{\text{∗}}$ $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例由一行组成，包含两个数字 $n$ 和 $x$（$1 \le n \le 10^9$，$0 \le x \le 10^9$）——Maurice 给你的数字。

## 输出格式

对于每个测试用例，输出你给 Maurice 的礼物——满足所有描述性质的数组的元素和。如果不存在这样的数组，输出 $-1$。

## 说明/提示

在第一个测试用例中，一个合适的数组是 $[2, 3]$。可以证明无法获得更小的数组元素和。

在第二个测试用例中，一个合适的数组是 $[1, 3, 4]$。同样可以证明这是最优的和。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
2 1
3 6
1 0
2 0
5 0
2 27
15 43
12345678 9101112
```

### 输出

```
5
8
-1
2
8
27
55
21446778
```



---

---
title: "Little Girl and Maximum XOR"
layout: "post"
diff: 普及/提高-
pid: CF276D
tag: ['位运算']
---

# Little Girl and Maximum XOR

## 题目描述

A little girl loves problems on bitwise operations very much. Here's one of them.

You are given two integers $ l $ and $ r $ . Let's consider the values of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF276D/e4d673f94fffa65030d2edd227a746e3a121dade.png) for all pairs of integers $ a $ and $ b $ $ (l<=a<=b<=r) $ . Your task is to find the maximum value among all considered ones.

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF276D/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying bitwise excluding or operation to integers $ x $ and $ y $ . The given operation exists in all modern programming languages, for example, in languages $ C $ ++ and $ Java $ it is represented as "^", in $ Pascal $ — as «xor».

## 输入格式

The single line contains space-separated integers $ l $ and $ r $ ( $ 1<=l<=r<=10^{18} $ ).

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 输出格式

In a single line print a single integer — the maximum value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF276D/e4d673f94fffa65030d2edd227a746e3a121dade.png) for all pairs of integers $ a $ , $ b $ $ (l<=a<=b<=r) $ .

## 样例 #1

### 输入

```
1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
8 16

```

### 输出

```
31

```

## 样例 #3

### 输入

```
1 1

```

### 输出

```
0

```



---

---
title: "New Year and Old Property"
layout: "post"
diff: 普及/提高-
pid: CF611B
tag: ['位运算']
---

# New Year and Old Property

## 题目描述

The year 2015 is almost over.

Limak is a little polar bear. He has recently learnt about the binary system. He noticed that the passing year has exactly one zero in its representation in the binary system — $ 2015_{10}=11111011111_{2} $ . Note that he doesn't care about the number of zeros in the decimal representation.

Limak chose some interval of years. He is going to count all years from this interval that have exactly one zero in the binary representation. Can you do it faster?

Assume that all positive integers are always written without leading zeros.

## 输入格式

The only line of the input contains two integers $ a $ and $ b $ ( $ 1<=a<=b<=10^{18} $ ) — the first year and the last year in Limak's interval respectively.

## 输出格式

Print one integer – the number of years Limak will count in his chosen interval.

## 说明/提示

In the first sample Limak's interval contains numbers $ 5_{10}=101_{2} $ , $ 6_{10}=110_{2} $ , $ 7_{10}=111_{2} $ , $ 8_{10}=1000_{2} $ , $ 9_{10}=1001_{2} $ and $ 10_{10}=1010_{2} $ . Two of them ( $ 101_{2} $ and $ 110_{2} $ ) have the described property.

## 样例 #1

### 输入

```
5 10

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2015 2015

```

### 输出

```
1

```

## 样例 #3

### 输入

```
100 105

```

### 输出

```
0

```

## 样例 #4

### 输入

```
72057594000000000 72057595000000000

```

### 输出

```
26

```



---

