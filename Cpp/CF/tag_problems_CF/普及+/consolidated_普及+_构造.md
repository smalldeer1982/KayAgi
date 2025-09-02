---
title: "Many Equal Substrings"
layout: "post"
diff: 普及+/提高
pid: CF1029A
tag: ['字符串', 'KMP 算法', '构造']
---

# Many Equal Substrings

## 题目描述

You are given a string $ t $ consisting of $ n $ lowercase Latin letters and an integer number $ k $ .

Let's define a substring of some string $ s $ with indices from $ l $ to $ r $ as $ s[l \dots r] $ .

Your task is to construct such string $ s $ of minimum possible length that there are exactly $ k $ positions $ i $ such that $ s[i \dots i + n - 1] = t $ . In other words, your task is to construct such string $ s $ of minimum possible length that there are exactly $ k $ substrings of $ s $ equal to $ t $ .

It is guaranteed that the answer is always unique.

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 50 $ ) — the length of the string $ t $ and the number of substrings.

The second line of the input contains the string $ t $ consisting of exactly $ n $ lowercase Latin letters.

## 输出格式

Print such string $ s $ of minimum possible length that there are exactly $ k $ substrings of $ s $ equal to $ t $ .

It is guaranteed that the answer is always unique.

## 样例 #1

### 输入

```
3 4
aba

```

### 输出

```
ababababa

```

## 样例 #2

### 输入

```
3 2
cat

```

### 输出

```
catcat

```



---

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
title: "Prefix Flip (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF1381A2
tag: ['构造']
---

# Prefix Flip (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is the constraint on $ n $ and the required number of operations. You can make hacks only if all versions of the problem are solved.

There are two binary strings $ a $ and $ b $ of length $ n $ (a binary string is a string consisting of symbols $ 0 $ and $ 1 $ ). In an operation, you select a prefix of $ a $ , and simultaneously invert the bits in the prefix ( $ 0 $ changes to $ 1 $ and $ 1 $ changes to $ 0 $ ) and reverse the order of the bits in the prefix.

For example, if $ a=001011 $ and you select the prefix of length $ 3 $ , it becomes $ 011011 $ . Then if you select the entire string, it becomes $ 001001 $ .

Your task is to transform the string $ a $ into $ b $ in at most $ 2n $ operations. It can be proved that it is always possible.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le       1000 $ ) — the number of test cases. Next $ 3t $ lines contain descriptions of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le 10^5 $ ) — the length of the binary strings.

The next two lines contain two binary strings $ a $ and $ b $ of length $ n $ .

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output an integer $ k $ ( $ 0\le k\le       2n $ ), followed by $ k $ integers $ p_1,\ldots,p_k $ ( $ 1\le       p_i\le n $ ). Here $ k $ is the number of operations you use and $ p_i $ is the length of the prefix you flip in the $ i $ -th operation.

## 说明/提示

In the first test case, we have $ 01\to 11\to 00\to 10 $ .

In the second test case, we have $ 01011\to 00101\to 11101\to       01000\to 10100\to 00100\to 11100 $ .

In the third test case, the strings are already the same. Another solution is to flip the prefix of length $ 2 $ , which will leave $ a $ unchanged.

## 样例 #1

### 输入

```
5
2
01
10
5
01011
11100
2
01
01
10
0110011011
1000110100
1
0
1
```

### 输出

```
3 1 2 1
6 5 2 5 3 1 2
0
9 4 1 2 10 4 1 2 1 5
1 1
```



---

---
title: "Help General"
layout: "post"
diff: 普及+/提高
pid: CF142B
tag: ['构造']
---

# Help General

## 题目描述

Once upon a time in the Kingdom of Far Far Away lived Sir Lancelot, the chief Royal General. He was very proud of his men and he liked to invite the King to come and watch drill exercises which demonstrated the fighting techniques and tactics of the squad he was in charge of. But time went by and one day Sir Lancelot had a major argument with the Fairy Godmother (there were rumors that the argument occurred after the general spoke badly of the Godmother's flying techniques. That seemed to hurt the Fairy Godmother very deeply).

As the result of the argument, the Godmother put a rather strange curse upon the general. It sounded all complicated and quite harmless: "If the squared distance between some two soldiers equals to $ 5 $ , then those soldiers will conflict with each other!"

The drill exercises are held on a rectangular $ n×m $ field, split into $ nm $ square $ 1×1 $ segments for each soldier. Thus, the square of the distance between the soldiers that stand on squares $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ equals exactly $ (x_{1}-x_{2})^{2}+(y_{1}-y_{2})^{2} $ . Now not all $ nm $ squad soldiers can participate in the drill exercises as it was before the Fairy Godmother's curse. Unless, of course, the general wants the soldiers to fight with each other or even worse... For example, if he puts a soldier in the square $ (2,2) $ , then he cannot put soldiers in the squares $ (1,4) $ , $ (3,4) $ , $ (4,1) $ and $ (4,3) $ — each of them will conflict with the soldier in the square $ (2,2) $ .

Your task is to help the general. You are given the size of the drill exercise field. You are asked to calculate the maximum number of soldiers that can be simultaneously positioned on this field, so that no two soldiers fall under the Fairy Godmother's curse.

## 输入格式

The single line contains space-separated integers $ n $ and $ m $ ( $ 1<=n,m<=1000 $ ) that represent the size of the drill exercise field.

## 输出格式

Print the desired maximum number of warriors.

## 说明/提示

In the first sample test Sir Lancelot can place his 4 soldiers on the $ 2×4 $ court as follows (the soldiers' locations are marked with gray circles on the scheme):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF142B/0d23ce3839b0ce156cddd9663617e134809111ae.png)In the second sample test he can place 6 soldiers on the $ 3×4 $ site in the following manner:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF142B/57bf2bd762016d87a2641e15975b3acd653786ad.png)

## 样例 #1

### 输入

```
2 4

```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 4

```

### 输出

```
6
```



---

---
title: "Repetitions Decoding"
layout: "post"
diff: 普及+/提高
pid: CF1641B
tag: ['排序', '构造']
---

# Repetitions Decoding

## 题目描述

Olya has an array of integers $ a_1, a_2, \ldots, a_n $ . She wants to split it into tandem repeats. Since it's rarely possible, before that she wants to perform the following operation several (possibly, zero) number of times: insert a pair of equal numbers into an arbitrary position. Help her!

More formally:

- A tandem repeat is a sequence $ x $ of even length $ 2k $ such that for each $ 1 \le i \le k $ the condition $ x_i = x_{i + k} $ is satisfied.
- An array $ a $ could be split into tandem repeats if you can split it into several parts, each being a subsegment of the array, such that each part is a tandem repeat.
- In one operation you can choose an arbitrary letter $ c $ and insert $ [c, c] $ to any position in the array (at the beginning, between any two integers, or at the end).
- You are to perform several operations and split the array into tandem repeats or determine that it is impossible. Please note that you do not have to minimize the number of operations.

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 30\,000 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 500 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the initial array.

It is guaranteed that the sum of $ n^2 $ over all test cases does not exceed $ 250\,000 $ .

## 输出格式

For each test case print answer in the following format.

If you cannot turn the array into a concatenation of tandem repeats, print a single integer $ -1 $ .

Otherwise print the number of operations $ q $ ( $ 0 \le q \le 2 \cdot n^2 $ ) that you want to do. Then print the descriptions of operations.

In each of the following $ q $ lines print two integers $ p $ and $ c $ ( $ 1 \le c \le 10^9 $ ), which mean that you insert the integer $ c $ twice after $ p $ elements of the array. If the length of the array is $ m $ before the operation, then the condition $ 0 \le p \le m $ should be satisfied.

Then you should print any way to split the resulting array into tandem repeats. First, print a single integer $ d $ , and then print a sequence $ t_1, t_2, \ldots, t_d $ of even integers of size $ d $ ( $ d, t_i \ge 1 $ ). These numbers are the lengths of the subsegments from left to right.

Note that the size of the resulting array $ a $ is $ m = n + 2 \cdot q $ . The following statements must hold:

- $ m = \sum\limits_{i = 1}^{d}{t_i} $ .
- For all integer $ i $ such that $ 1 \le i \le d $ , the sequence $ a_l, a_{l+1}, \ldots, a_r $ is a tandem repeat, where $ l = \sum\limits_{j = 1}^{i - 1}{t_j} + 1 $ , $ r = l + t_i - 1 $ .

It can be shown that if the array can be turned into a concatenation of tandem repeats, then there exists a solution satisfying all constraints. If there are multiple answers, you can print any.

## 说明/提示

In the first test case, you cannot apply operations to the array to make it possible to split it into tandem repeats.

In the second test case the array is already a tandem repeat $ [5, 5] = \underbrace{([5] + [5])}_{t_1 = 2} $ , thus we can do no operations at all.

In the third test case, initially, we have the following array: $ $$$[1, 3, 1, 2, 2, 3]. $ $  After the first insertion with  $ p = 1, c = 3 $ :  $ $ [1, \textbf{3, 3}, 3, 1, 2, 2, 3]. $ $  After the second insertion with  $ p = 5, c = 3 $ :  $ $ [1, 3, 3, 3, 1, \textbf{3, 3}, 2, 2, 3]. $ $  After the third insertion with  $ p = 5, c = 3 $ :  $ $ [1, 3, 3, 3, 1, \textbf{3, 3}, 3, 3, 2, 2, 3]. $ $  After the fourth insertion with  $ p = 10, c = 3 $ :  $ $ [1, 3, 3, 3, 1, 3, 3, 3, 3, 2, \textbf{3, 3}, 2, 3]. $ $  The resulting array can be represented as a concatenation of tandem repeats:  $ $ \underbrace{([1, 3, 3, 3] + [1, 3, 3, 3])}_{t_1 = 8} + \underbrace{([3, 2, 3] + [3, 2, 3])}_{t_2 = 6}. $ $ </p><p>In the fourth test case, initially, we have the following array:  $ $ [3, 2, 1, 1, 2, 3]. $ $  After the first insertion with  $ p = 0, c = 3 $ :  $ $ [\textbf{3, 3}, 3, 2, 1, 1, 2, 3]. $ $  After the second insertion with  $ p = 8, c = 3 $ :  $ $ [3, 3, 3, 2, 1, 1, 2, 3, \textbf{3, 3}]. $ $  After the third insertion with  $ p = 5, c = 3 $   $ $ [3, 3, 3, 2, 1, \textbf{3, 3}, 1, 2, 3, 3, 3]. $ $  After the fourth insertion with  $ p = 6, c = 2 $ :  $ $ [3, 3, 3, 2, 1, 3, \textbf{2, 2}, 3, 1, 2, 3, 3, 3]. $ $  After the fifth insertion with  $ p = 7, c = 1 $ :  $ $ [3, 3, 3, 2, 1, 3, 2, \textbf{1, 1}, 2, 3, 1, 2, 3, 3, 3]. $ $  The resulting array can be represented as a concatenation of tandem repeats:  $ $ \underbrace{([3] + [3])}_{t_1 = 2} + \underbrace{([3, 2, 1] + [3, 2, 1])}_{t_2 = 6} + \underbrace{([1, 2, 3] + [1, 2, 3])}_{t_3 = 6} + \underbrace{([3] + [3])}_{t_4 = 2}. $ $$$

## 样例 #1

### 输入

```
4
2
5 7
2
5 5
6
1 3 1 2 2 3
6
3 2 1 1 2 3
```

### 输出

```
-1
0
1
2
4
1 3
5 3
5 3
10 3
2
8 6 
5
0 3
8 3
5 3 
6 2 
7 1
4
2 6 6 2
```



---

---
title: "LIS or Reverse LIS?"
layout: "post"
diff: 普及+/提高
pid: CF1682C
tag: ['数学', '构造']
---

# LIS or Reverse LIS?

## 题目描述

You are given an array $ a $ of $ n $ positive integers.

Let $ \text{LIS}(a) $ denote the length of [longest strictly increasing subsequence](https://en.wikipedia.org/wiki/Longest_increasing_subsequence) of $ a $ . For example,

- $ \text{LIS}([2, \underline{1}, 1, \underline{3}]) $ = $ 2 $ .
- $ \text{LIS}([\underline{3}, \underline{5}, \underline{10}, \underline{20}]) $ = $ 4 $ .
- $ \text{LIS}([3, \underline{1}, \underline{2}, \underline{4}]) $ = $ 3 $ .

We define array $ a' $ as the array obtained after reversing the array $ a $ i.e. $ a' = [a_n, a_{n-1}, \ldots , a_1] $ .

The beauty of array $ a $ is defined as $ min(\text{LIS}(a),\text{LIS}(a')) $ .

Your task is to determine the maximum possible beauty of the array $ a $ if you can rearrange the array $ a $ arbitrarily.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ $ (1 \leq t \leq 10^4) $ — the number of test cases. Description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (1 \leq n \leq 2\cdot 10^5) $ — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2, \ldots ,a_n $ $ (1 \leq a_i \leq 10^9) $ — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum possible beauty of $ a $ after rearranging its elements arbitrarily.

## 说明/提示

In the first test case, $ a $ = $ [6, 6, 6] $ and $ a' $ = $ [6, 6, 6] $ . $ \text{LIS}(a) = \text{LIS}(a') $ = $ 1 $ . Hence the beauty is $ min(1, 1) = 1 $ .

In the second test case, $ a $ can be rearranged to $ [2, 5, 4, 5, 4, 2] $ . Then $ a' $ = $ [2, 4, 5, 4, 5, 2] $ . $ \text{LIS}(a) = \text{LIS}(a') = 3 $ . Hence the beauty is $ 3 $ and it can be shown that this is the maximum possible beauty.

In the third test case, $ a $ can be rearranged to $ [1, 2, 3, 2] $ . Then $ a' $ = $ [2, 3, 2, 1] $ . $ \text{LIS}(a) = 3 $ , $ \text{LIS}(a') = 2 $ . Hence the beauty is $ min(3, 2) = 2 $ and it can be shown that $ 2 $ is the maximum possible beauty.

## 样例 #1

### 输入

```
3
3
6 6 6
6
2 5 4 5 2 4
4
1 3 2 2
```

### 输出

```
1
3
2
```



---

---
title: "Circular Spanning Tree"
layout: "post"
diff: 普及+/提高
pid: CF1682D
tag: ['构造']
---

# Circular Spanning Tree

## 题目描述

There are $ n $ nodes arranged in a circle numbered from $ 1 $ to $ n $ in the clockwise order. You are also given a binary string $ s $ of length $ n $ .

Your task is to construct a tree on the given $ n $ nodes satisfying the two conditions below or report that there such tree does not exist:

- For each node $ i $ $ (1 \le i \le n) $ , the degree of node is even if $ s_i = 0 $ and odd if $ s_i = 1 $ .
- No two edges of the tree intersect internally in the circle. The edges are allowed to intersect on the circumference.

Note that all edges are drawn as straight line segments. For example, edge $ (u, v) $ in the tree is drawn as a line segment connecting $ u $ and $ v $ on the circle.

A tree on $ n $ nodes is a connected graph with $ n - 1 $ edges.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ $ (1 \leq t \leq 2\cdot 10^4) $ — the number of test cases. Description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (2 \leq n \leq 2\cdot 10^5) $ — the number of nodes.

The second line of each test case contains a binary string $ s $ of length $ n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, if there does not exist a tree that satisfies the given conditions, then output "NO" (without quotes), otherwise output "YES" followed by the description of tree.

You can output each letter in any case (for example, "YES", "Yes", "yes", "yEs", "yEs" will be recognized as a positive answer).

If there exists a tree, then output $ n - 1 $ lines, each containing two integers $ u $ and $ v $ $ (1 \leq u,v \leq n, u \neq v) $ denoting an edge between $ u $ and $ v $ in the tree. If there are multiple possible answers, output any.

## 说明/提示

In the first test case, the tree looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682D/a3c1924547a7a2cf2e2e161bdb11c580efe3e855.png)In the second test case, there is only one possible tree with an edge between $ 1 $ and $ 2 $ , and it does not satisfy the degree constraints.

In the third test case,

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682D/e5b3e28053fdc3d6ed84005d3e46d8276c4f8576.png) The tree on the left satisfies the degree constraints but the edges intersect internally, therefore it is not a valid tree, while the tree on the right is valid.

## 样例 #1

### 输入

```
3
4
0110
2
10
6
110110
```

### 输出

```
YES
2 1
3 4
1 4
NO
YES
2 3
1 2
5 6
6 2
3 4
```



---

---
title: "Guess The String"
layout: "post"
diff: 普及+/提高
pid: CF1697D
tag: ['二分', '构造']
---

# Guess The String

## 题目描述

This is an interactive problem. Remember to flush your output while communicating with the testing program. You may use fflush(stdout) in C++, system.out.flush() in Java, stdout.flush() in Python or flush(output) in Pascal to flush the output. If you use some other programming language, consult its documentation. You may also refer to the guide on interactive problems: <https://codeforces.com/blog/entry/45307>.

The jury has chosen a string $ s $ consisting of $ n $ characters; each character of $ s $ is a lowercase Latin letter. Your task is to guess this string; initially, you know only its length.

You may ask queries of two types:

- $ 1 $ $ i $ — the query of the first type, where $ i $ is an integer from $ 1 $ to $ n $ . In response to this query, the jury will tell you the character $ s_i $ ;
- $ 2 $ $ l $ $ r $ — the query of the second type, where $ l $ and $ r $ are integers such that $ 1 \le l \le r \le n $ . In response to this query, the jury will tell you the number of different characters among $ s_l, s_{l+1}, \dots, s_r $ .

You are allowed to ask no more than $ 26 $ queries of the first type, and no more than $ 6000 $ queries of the second type. Your task is to restore the string $ s $ .

For each test in this problem, the string $ s $ is fixed beforehand, and will be the same for every submission.

## 输入格式

Initially, the jury program sends one integer $ n $ on a separate line — the size of $ s $ ( $ 1 \le n \le 1000 $ ).

## 输出格式

To give the answer, print one line ! s with a line break in the end, where $ s $ should be the string picked by the jury. After that, your program should flush the output and terminate gracefully.

Interaction

To ask a query, you should send one line containing the query, in one of the following formats:

- ? 1 i — for a query of the first type ( $ 1 \le i \le n $ );
- ? 2 l r — for a query of the second type ( $ 1 \le l \le r \le n $ ).

Don't forget to flush the output after sending the query line.

The answer to your query will be given on a separate line. For a query of the first type, the answer will be the character $ s_i $ . For a query of the second type, the answer will be an integer equal to the number of different characters among $ s_l, s_{l+1}, \dots, s_r $ .

You are allowed to ask no more than $ 26 $ queries of the first type, and no more than $ 6000 $ queries of the second type.

In case you ask too many queries, or the jury program fails to recognize your query format, the answer to your query will be one integer $ 0 $ . After receiving $ 0 $ as the answer, your program should terminate immediately — otherwise you may receive verdict "Runtime error", "Time limit exceeded" or some other verdict instead of "Wrong answer".

## 说明/提示

Let's analyze the example of interaction.

The string chosen by the jury is guess, so initially the jury sends one integer $ 5 $ .

1. the first query is ? 2 1 5, which means "count the number of different characters among $ s_1, s_2, \dots, s_5 $ ". The answer to it is $ 4 $ .
2. the second query is ? 1 2, which means "tell which character is $ s_2 $ ". The answer to it is u.
3. the third query is ? 2 1 2, which means "count the number of different characters among $ s_1 $ and $ s_2 $ ". The answer to it is $ 2 $ .
4. the fourth query is ? 1 1, which means "tell which character is $ s_1 $ ". The answer to it is g.
5. the fifth query is ? 1 3, which means "tell which character is $ s_3 $ ". The answer to it is e.
6. the sixth query is ? 1 4, which means "tell which character is $ s_4 $ ". The answer to it is s.
7. the seventh query is ? 2 4 5, which means "count the number of different characters among $ s_4 $ and $ s_5 $ ". The answer to it is $ 1 $ , so it's possible to deduce that $ s_4 $ is the same as $ s_5 $ .

In the end, the answer is submitted as ! guess, and it is deduced correctly.

## 样例 #1

### 输入

```
5
4
u
2
g
e
s
1
```

### 输出

```
? 2 1 5
? 1 2
? 2 1 2
? 1 1
? 1 3
? 1 4
? 2 4 5
! guess
```



---

---
title: "Magical Array"
layout: "post"
diff: 普及+/提高
pid: CF1704D
tag: ['哈希 hashing', '构造']
---

# Magical Array

## 题目描述

Eric has an array $ b $ of length $ m $ , then he generates $ n $ additional arrays $ c_1, c_2, \dots, c_n $ , each of length $ m $ , from the array $ b $ , by the following way:

Initially, $ c_i = b $ for every $ 1 \le i \le n $ . Eric secretly chooses an integer $ k $ $ (1 \le k \le n) $ and chooses $ c_k $ to be the special array.

There are two operations that Eric can perform on an array $ c_t $ :

- Operation 1: Choose two integers $ i $ and $ j $ ( $ 2 \leq i < j \leq m-1 $ ), subtract $ 1 $ from both $ c_t[i] $ and $ c_t[j] $ , and add $ 1 $ to both $ c_t[i-1] $ and $ c_t[j+1] $ . That operation can only be used on a non-special array, that is when $ t \neq k $ .;
- Operation 2: Choose two integers $ i $ and $ j $ ( $ 2 \leq i < j \leq m-2 $ ), subtract $ 1 $ from both $ c_t[i] $ and $ c_t[j] $ , and add $ 1 $ to both $ c_t[i-1] $ and $ c_t[j+2] $ . That operation can only be used on a special array, that is when $ t = k $ .Note that Eric can't perform an operation if any element of the array will become less than $ 0 $ after that operation.

Now, Eric does the following:

- For every non-special array $ c_i $ ( $ i \neq k $ ), Eric uses only operation 1 on it at least once.
- For the special array $ c_k $ , Eric uses only operation 2 on it at least once.

Lastly, Eric discards the array $ b $ .

For given arrays $ c_1, c_2, \dots, c_n $ , your task is to find out the special array, i.e. the value $ k $ . Also, you need to find the number of times of operation $ 2 $ was used on it.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Description of test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 3 \leq n \leq 10^5 $ , $ 7 \leq m \leq 3 \cdot 10^5 $ ) — the number of arrays given to you, and the length of each array.

The next $ n $ lines contains $ m $ integers each, $ c_{i,1}, c_{i,2}, \dots , c_{i,m} $ .

It is guaranteed that each element of the discarded array $ b $ is in the range $ [0,10^6] $ , and therefore $ 0 \leq c_{i,j} \leq 3 \cdot 10^{11} $ for all possible pairs of $ (i,j) $ .

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 10^6 $ .

It is guaranteed that the input is generated according to the procedure above.

## 输出格式

For each test case, output one line containing two integers — the index of the special array, and the number of times that Operation 2 was performed on it. It can be shown that under the constraints given in the problem, this value is unique and won't exceed $ 10^{18} $ , so you can represent it as a $ 64 $ -bit integer. It can also be shown that the index of the special array is uniquely determined.

In this problem, hacks are disabled.

## 说明/提示

In the first test case, the secret array $ b $ is $ [0, 1, 1, 1, 1, 1, 1, 1, 0] $ . Array $ c_1 $ and array $ c_2 $ are generated by using operation 1. Array $ c_3 $ is generated by using operation 2.

For Array $ c_1 $ ,you can choose $ i=4 $ and $ j=5 $ perform Operation 1 one time to generate it. For Array $ c_2 $ , you can choose $ i=6 $ and $ j=7 $ perform Operation 1 one time to generate it. For Array $ c_3 $ ,you can choose $ i=4 $ and $ j=5 $ perform Operation 2 one time to generate it.

In the second test case, the secret array $ b $ is $ [20, 20, 20, 20, 20, 20, 20] $ . You can also find that array $ c_1 $ and array $ c_2 $ are generated by using Operation 1. Array $ c_3 $ is generated by using Operation 2.

In the third test case, the secret array $ b $ is $ [20, 20, 20, 20, 20, 20, 20, 20, 20] $ . You can also find that array $ c_1 $ and array $ c_2 $ are generated by using Operation 1. Array $ c_3 $ is generated by using Operation 2.

## 样例 #1

### 输入

```
7
3 9
0 1 2 0 0 2 1 1 0
0 1 1 1 2 0 0 2 0
0 1 2 0 0 1 2 1 0
3 7
25 15 20 15 25 20 20
26 14 20 14 26 20 20
25 15 20 15 20 20 25
3 9
25 15 20 15 25 20 20 20 20
26 14 20 14 26 20 20 20 20
25 15 20 15 25 15 20 20 25
3 11
25 15 20 15 25 20 20 20 20 20 20
26 14 20 14 26 20 20 20 20 20 20
25 15 20 15 25 20 15 20 20 20 25
3 13
25 15 20 15 25 20 20 20 20 20 20 20 20
26 14 20 14 26 20 20 20 20 20 20 20 20
25 15 20 15 25 20 20 15 20 20 20 20 25
3 15
25 15 20 15 25 20 20 20 20 20 20 20 20 20 20
26 14 20 14 26 20 20 20 20 20 20 20 20 20 20
25 15 20 15 25 20 20 20 15 20 20 20 20 20 25
3 9
909459 479492 676924 224197 162866 164495 193268 742456 728277
948845 455424 731850 327890 304150 237351 251763 225845 798316
975446 401170 792914 272263 300770 242037 236619 334316 725899
```

### 输出

```
3 1
3 10
3 15
3 20
3 25
3 30
1 1378716
```



---

---
title: "Range = √Sum"
layout: "post"
diff: 普及+/提高
pid: CF1758D
tag: ['前缀和', '构造']
---

# Range = √Sum

## 题目描述

You are given an integer $ n $ . Find a sequence of $ n $ distinct integers $ a_1, a_2, \dots, a_n $ such that $ 1 \leq a_i \leq 10^9 $ for all $ i $ and $ $$$\max(a_1, a_2, \dots, a_n) - \min(a_1, a_2, \dots, a_n)= \sqrt{a_1 + a_2 + \dots + a_n}. $ $$$

It can be proven that there exists a sequence of distinct integers that satisfies all the conditions above.

## 输入格式

The first line of input contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first and only line of each test case contains one integer $ n $ ( $ 2 \leq n \leq 3 \cdot 10^5 $ ) — the length of the sequence you have to find.

The sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ space-separated distinct integers $ a_1, a_2, \dots, a_n $ satisfying the conditions in the statement.

If there are several possible answers, you can output any of them. Please remember that your integers must be distinct!

## 说明/提示

In the first test case, the maximum is $ 3 $ , the minimum is $ 1 $ , the sum is $ 4 $ , and $ 3 - 1 = \sqrt{4} $ .

In the second test case, the maximum is $ 29 $ , the minimum is $ 18 $ , the sum is $ 121 $ , and $ 29-18 = \sqrt{121} $ .

For each test case, the integers are all distinct.

## 样例 #1

### 输入

```
3
2
5
4
```

### 输出

```
3 1
20 29 18 26 28
25 21 23 31
```



---

---
title: "Same Count One"
layout: "post"
diff: 普及+/提高
pid: CF1774D
tag: ['贪心', '构造', '双指针 two-pointer']
---

# Same Count One

## 题目描述

给定 $n$ 个长度为 $m$ 的，只包含 $0$ 和 $1$ 的数组，选择任意两个数组交换位置 $pos$ 上的数。在经过最少的操作后使得每个数组中的 $1$ 数量相等，并输出操作过程。

## 输入格式

第一行一个整数 $t$  $( 1 \leq t \leq 2\cdot 10^4 )$ 表示有 $t$ 组测试数据。

每组测试数据：第一行两个整数 $ n $ 和 $ m $ 。 $( 2 \leq n \leq 10^5 $ , $ 2 \leq m \leq 10^5 , \sum n\times m \le 10^6)$ 

接下来 $ n $ 行，每行 $ m $ 个整数（ $ 0 $ 或 $ 1 $ ）。

## 输出格式

对于每一组测试样例，若无法满足要求，输出 $ -1 $ .

否则, 第一行输出一个整数 $ k $ $ (0 \le k \le mn) $ ，即最小的操作数量。

接下来输出 $ k $ 行，每行 $ 3 $ 个整数, $ x, y, z $ $ (1 \le x, y \le n, 1 \le z \le m) $ , 表示交换 $ a_{x, z}, a_{y, z} $ : 即交换第 $ x $ 和第 $ y $ 行的第 $ z $ 个数。

## 样例 #1

### 输入

```
3
3 4
1 1 1 0
0 0 1 0
1 0 0 1
4 3
1 0 0
0 1 1
0 0 1
0 0 0
2 2
0 0
0 1
```

### 输出

```
1
2 1 1
1
4 2 2
-1
```



---

---
title: "Bit Guessing Game"
layout: "post"
diff: 普及+/提高
pid: CF1780D
tag: ['位运算', '构造']
---

# Bit Guessing Game

## 题目描述

这是一道交互题。

Kira 和 Hayato 正在玩一种猜数游戏，Kira 想，Hayato 猜。

对于每一轮游戏，设 Kira 想的数为 $n$。初始时，Kira 会给出 $cnt$，表示 $n$ 的二进制中 $1$ 的个数。Hayato 只能进行以下两种操作：

1. `- x`：修改操作。Kira 会将 $n$ 减去 $x$（注意此处 $n$ 会被修改），并给出此时的 $cnt$。特别地，若 $x > n$，则 Kira 直接获胜。
2. `! x`：查询操作。Kira 会将 $x$ 与最初的 $n$ 对比，若二者相同则 Hayato 获胜，反之 Kira 获胜，这轮游戏立即结束。

他们一共会进行 $t$ 轮游戏，你需要帮助 Hayato 在每一轮中获胜。同时，Kira 并不是一个很有耐心的人，因此你进行操作 1 的次数不能超过 $30$。

注意样例中的空行只是为了显示更清晰，不会出现在实际评测中。

## 输入格式

第一行包含一个整数 $t(1 \le t \le 500)$，表示有 $t$ 组测试用例。

对于每组测试用例，首行均为一个整数 $cnt$，表示 $n$ 的二进制中 $1$ 的个数。

保证 $1 \le n \le 10^9$。

## 输出格式

对于每个操作 1，输出单独的一行 `- x`；相应地，对于每个操作 2，输出单独的一行 `! n`。

每个操作 1 完成后，交互库会输出一行一个整数 $cnt$，表示修改后的 $n$ 的二进制中 $1$ 的个数。

再次强调，每一轮 Hayato 进行操作 1 的次数不能超过 $30$。

确定初始时 $n$ 的值后，可进行操作 2 验证答案。

注意：每次输出任意操作后需要刷新输出。这里给出部分语言刷新输出的代码：

|  语言  |                代码                |
| :----: | :--------------------------------: |
|  C++   | `fflush(stdout)` 或 `cout.flush()` |
|  Java  |        `System.out.flush()`        |
| Pascal |          `flush(output)`           |
| Python |          `stdout.flush()`          |

## 样例 #1

### 输入

```
3

1

0

1

1

0

2

1

0
```

### 输出

```
- 1

! 1

- 1

- 1

! 2

- 2

- 1

! 3
```



---

---
title: "The Very Beautiful Blanket"
layout: "post"
diff: 普及+/提高
pid: CF1801A
tag: ['构造']
---

# The Very Beautiful Blanket

## 题目描述

Kirill wants to weave the very beautiful blanket consisting of $ n \times m $ of the same size square patches of some colors. He matched some non-negative integer to each color. Thus, in our problem, the blanket can be considered a $ B $ matrix of size $ n \times m $ consisting of non-negative integers.

Kirill considers that the blanket is very beautiful, if for each submatrix $ A $ of size $ 4 \times 4 $ of the matrix $ B $ is true:

- $ A_{11} \oplus A_{12} \oplus A_{21} \oplus A_{22} = A_{33} \oplus A_{34} \oplus A_{43} \oplus A_{44}, $
- $ A_{13} \oplus A_{14} \oplus A_{23} \oplus A_{24} = A_{31} \oplus A_{32} \oplus A_{41} \oplus A_{42}, $

where $ \oplus $ means [bitwise exclusive OR](https://en.wikipedia.org/wiki/Exclusive_or)

Kirill asks you to help her weave a very beautiful blanket, and as colorful as possible!

He gives you two integers $ n $ and $ m $ .

Your task is to generate a matrix $ B $ of size $ n \times m $ , which corresponds to a very beautiful blanket and in which the number of different numbers maximized.

## 输入格式

The first line of input data contains one integer number $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The single line of each test case contains two integers $ n $ and $ m $ $ (4 \le n, \, m \le 200) $ — the size of matrix $ B $ .

It is guaranteed that the sum of $ n \cdot m $ does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, in first line output one integer $ cnt $ $ (1 \le cnt \le n \cdot m) $ — the maximum number of different numbers in the matrix.

Then output the matrix $ B $ $ (0 \le B_{ij} < 2^{63}) $ of size $ n \times m $ . If there are several correct matrices, it is allowed to output any one.

It can be shown that if there exists a matrix with an optimal number of distinct numbers, then there exists among suitable matrices such a $ B $ that $ (0 \le B_{ij} < 2^{63}) $ .

## 说明/提示

In the first test case, there is only 4 submatrix of size $ 4 \times 4 $ . Consider a submatrix whose upper-left corner coincides with the upper-left corner of the matrix $ B $ :

 $  \left[ {\begin{array}{cccc} 9740 & 1549 & 9744 & 1553 \\ 1550 & 1551 & 1554 & 1555 \\ 10252 & 2061 & 10256 & 2065 \\ 2062 & 2063 & 2066 & 2067 \\ \end{array} } \right]  $

 $ 9740 \oplus 1549 \oplus 1550 \oplus 1551 $ $ = $ $ 10256 \oplus 2065 \oplus 2066 \oplus 2067 $ $ = $ $ 8192 $ ;

 $ 10252 \oplus 2061 \oplus 2062 \oplus 2063 $ $ = $ $ 9744 \oplus 1553 \oplus 1554 \oplus 1555 $ $ = $ $ 8192 $ .

So, chosen submatrix fits the condition. Similarly, you can make sure that the other three submatrices also fit the condition.

## 样例 #1

### 输入

```
4
5 5
4 4
4 6
6 6
```

### 输出

```
25
9740 1549 9744 1553 9748
1550 1551 1554 1555 1558
10252 2061 10256 2065 10260
2062 2063 2066 2067 2070
10764 2573 10768 2577 10772
16
3108 3109 3112 3113
3110 3111 3114 3115
3620 3621 3624 3625
3622 3623 3626 3627
24
548 549 552 553 556 557
550 551 554 555 558 559
1060 1061 1064 1065 1068 1069
1062 1063 1066 1067 1070 1071
36
25800 25801 25804 25805 25808 25809
25802 4294993099 25806 4294993103 25810 4294993107
26312 26313 26316 26317 26320 26321
26314 4294993611 26318 4294993615 26322 4294993619
26824 26825 26828 26829 26832 26833
26826 4294994123 26830 4294994127 26834 4294994131
```



---

---
title: "Increasing Subsequences"
layout: "post"
diff: 普及+/提高
pid: CF1922E
tag: ['构造']
---

# Increasing Subsequences

## 题目描述

Let's recall that an increasing subsequence of the array $ a $ is a sequence that can be obtained from it by removing some elements without changing the order of the remaining elements, and the remaining elements are strictly increasing (i. e $ a_{b_1} < a_{b_2} < \dots < a_{b_k} $ and $ b_1 < b_2 < \dots < b_k $ ). Note that an empty subsequence is also increasing.

You are given a positive integer $ X $ . Your task is to find an array of integers of length at most $ 200 $ , such that it has exactly $ X $ increasing subsequences, or report that there is no such array. If there are several answers, you can print any of them.

If two subsequences consist of the same elements, but correspond to different positions in the array, they are considered different (for example, the array $ [2, 2] $ has two different subsequences equal to $ [2] $ ).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The only line of each test case contains a single integer $ X $ ( $ 2 \le X \le 10^{18} $ ).

## 输出格式

For each query, print the answer to it. If it is impossible to find the required array, print -1 on the first line. Otherwise, print a positive integer $ n $ on the first line — the length of the array. On the second line, print $ n $ integers — the required array itself. If there are several answers, you can print any of them. All elements of the array should be in the range $ [-10^9; 10^9] $ .

## 样例 #1

### 输入

```
4
2
5
13
37
```

### 输出

```
1
0
3
0 1 0
5
2 2 3 4 2
7
-1 -1 0 0 2 3 -1
```



---

---
title: "Binary Search"
layout: "post"
diff: 普及+/提高
pid: CF1945E
tag: ['二分', '构造']
---

# Binary Search

## 题目描述

Anton got bored during the hike and wanted to solve something. He asked Kirill if he had any new problems, and of course, Kirill had one.

You are given a permutation $ p $ of size $ n $ , and a number $ x $ that needs to be found. A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

You decided that you are a cool programmer, so you will use an advanced algorithm for the search — binary search. However, you forgot that for binary search, the array must be sorted.

You did not give up and decided to apply this algorithm anyway, and in order to get the correct answer, you can perform the following operation no more than $ 2 $ times before running the algorithm: choose the indices $ i $ , $ j $ ( $ 1\le i, j \le n $ ) and swap the elements at positions $ i $ and $ j $ .

After that, the binary search is performed. At the beginning of the algorithm, two variables $ l = 1 $ and $ r = n + 1 $ are declared. Then the following loop is executed:

1. If $ r - l = 1 $ , end the loop
2. $ m = \lfloor \frac{r + l}{2} \rfloor $
3. If $ p_m \le x $ , assign $ l = m $ , otherwise $ r = m $ .

The goal is to rearrange the numbers in the permutation before the algorithm so that after the algorithm is executed, $ p_l $ is equal to $ x $ . It can be shown that $ 2 $ operations are always sufficient.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 2\cdot 10^4 $ ) — the number of test cases. Then follow the descriptions of the test cases.

The first line of each test case contains two integers $ n $ and $ x $ ( $ 1 \le x \le n \le 2\cdot 10^5 $ ) — the length of the permutation and the number to be found.

The second line contains the permutation $ p $ separated by spaces ( $ 1 \le p_i \le n $ ).

It is guaranteed that the sum of the values of $ n $ for all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output an integer $ k $ ( $ 0 \le k \le 2 $ ) on the first line — the number of operations performed by you. In the next $ k $ lines, output $ 2 $ integers $ i $ , $ j $ ( $ 1 \le i, j \le n $ ) separated by a space, indicating that you are swapping the elements at positions $ i $ and $ j $ .

Note that you do not need to minimize the number of operations.

## 样例 #1

### 输入

```
5
6 3
1 2 3 4 5 6
6 5
3 1 6 5 2 4
5 1
3 5 4 2 1
6 3
4 3 1 5 2 6
3 2
3 2 1
```

### 输出

```
0
1
3 4
2
2 4
1 5
2
4 5
2 4
1
1 3
```



---

---
title: "Clique Partition"
layout: "post"
diff: 普及+/提高
pid: CF1948E
tag: ['贪心', '构造']
---

# Clique Partition

## 题目描述

You are given two integers, $ n $ and $ k $ . There is a graph on $ n $ vertices, numbered from $ 1 $ to $ n $ , which initially has no edges.

You have to assign each vertex an integer; let $ a_i $ be the integer on the vertex $ i $ . All $ a_i $ should be distinct integers from $ 1 $ to $ n $ .

After assigning integers, for every pair of vertices $ (i, j) $ , you add an edge between them if $ |i - j| + |a_i - a_j| \le k $ .

Your goal is to create a graph which can be partitioned into the minimum possible (for the given values of $ n $ and $ k $ ) number of cliques. Each vertex of the graph should belong to exactly one clique. Recall that a clique is a set of vertices such that every pair of vertices in it are connected with an edge.

Since BledDest hasn't really brushed his programming skills up, he can't solve the problem "given a graph, partition it into the minimum number of cliques". So we also ask you to print the partition itself.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1600 $ ) — the number of test cases.

Each test case consists of one line containing two integers $ n $ and $ k $ ( $ 2 \le n \le 40 $ ; $ 1 \le k \le 2n $ ).

## 输出格式

For each test case, print three lines:

- the first line should contain $ n $ distinct integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ) — the values you assign to the vertices;
- the second line should contain one integer $ q $ ( $ 1 \le q \le n $ ) — the number of cliques you partition the graph into;
- the third line should contain $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le q $ ) — the partition of the graph into cliques. Where two vertices $ u $ and $ v $ are in the same clique if $ c_u = c_v $ .

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3
2 3
5 4
8 16
```

### 输出

```
2 1
1
1 1
3 1 5 2 4
2
1 1 2 1 2
1 2 3 4 5 6 7 8
1
1 1 1 1 1 1 1 1
```



---

---
title: "Missing Subsequence Sum"
layout: "post"
diff: 普及+/提高
pid: CF1965B
tag: ['贪心', '构造']
---

# Missing Subsequence Sum

## 题目描述

给定两个整数 $n,k$，你需要构造出一个长度不超过 $25$ 的数组 $a$，并满足以下条件：

* $a$ 中任意子序列元素和不为 $k$。

* $a$ 中所有子序列和可以表示 $1\sim n$ 中除了 $k$ 以外的任意整数。

子序列表示一个序列中任意一些元素按顺序组成的序列，比如 $[5,2,3]$ 是 $[1,5,7,8,2,4,3]$ 的子序列。

可以证明一定存在这样的方案。

## 输入格式

第一行一个整数 $t$，表示数据组数。

接下来 $t$ 行，每行两个整数 $n,k$。

## 输出格式

共 $t$ 组数据，每组数据共两行。

第一行一个整数 $m$ 表示你构造的序列长度。

接下来一行 $m$ 个整数表示你构造的数列，其中第 $i$ 个数表示 $a_i$。

## 说明/提示

对于全部数据，满足 $1\le t\le1000$，$1\le k\le n\le10^6$，$1\le \sum n\le10^7$。

你构造的数列需要满足 $1\le m\le25$，$0\le a_i\le10^9$。

## 样例 #1

### 输入

```
5
2 2
6 1
8 8
9 3
10 7
```

### 输出

```
1
1
5
2 3 4 5 6
7
1 1 1 1 1 1 1
4
7 1 4 1
4
1 2 8 3
```



---

---
title: "Exact Neighbours (Medium)"
layout: "post"
diff: 普及+/提高
pid: CF1970B2
tag: ['构造']
---

# Exact Neighbours (Medium)

## 题目描述

The only difference between this and the hard version is that $ a_{1} = 0 $ .

After some recent attacks on Hogwarts Castle by the Death Eaters, the Order of the Phoenix has decided to station $ n $ members in Hogsmead Village. The houses will be situated on a picturesque $ n\times n $ square field. Each wizard will have their own house, and every house will belong to some wizard. Each house will take up the space of one square.

However, as you might know wizards are very superstitious. During the weekends, each wizard $ i $ will want to visit the house that is exactly $ a_{i} $ $ (0 \leq a_{i} \leq n) $ away from their own house. The roads in the village are built horizontally and vertically, so the distance between points $ (x_{i}, y_{i}) $ and $ (x_{j}, y_{j}) $ on the $ n\times n $ field is $  |x_{i} - x_{j}| + |y_{i} - y_{j}| $ . The wizards know and trust each other, so one wizard can visit another wizard's house when the second wizard is away. The houses to be built will be big enough for all $ n $ wizards to simultaneously visit any house.

Apart from that, each wizard is mandated to have a view of the Hogwarts Castle in the north and the Forbidden Forest in the south, so the house of no other wizard should block the view. In terms of the village, it means that in each column of the $ n\times n $ field, there can be at most one house, i.e. if the $ i $ -th house has coordinates $ (x_{i}, y_{i}) $ , then $ x_{i} \neq x_{j} $ for all $ i \neq j $ .

The Order of the Phoenix doesn't yet know if it is possible to place $ n $ houses in such a way that will satisfy the visit and view requirements of all $ n $ wizards, so they are asking for your help in designing such a plan.

If it is possible to have a correct placement, where for the $ i $ -th wizard there is a house that is $ a_{i} $ away from it and the house of the $ i $ -th wizard is the only house in their column, output YES, the position of houses for each wizard, and to the house of which wizard should each wizard go during the weekends.

If it is impossible to have a correct placement, output NO.

## 输入格式

The first line contains $ n $ ( $ 2 \leq n \leq 2\cdot 10^{5} $ ), the number of houses to be built.

The second line contains $ n $ integers $ a_{1}, \ldots, a_{n} $ $ (0 \leq a_{i} \leq n) $ , $ a_{1} = 0 $ .

## 输出格式

If there exists such a placement, output YES on the first line; otherwise, output NO.

If the answer is YES, output $ n + 1 $ more lines describing the placement.

The next $ n $ lines should contain the positions of the houses $ 1 \leq x_{i}, y_{i} \leq n $ for each wizard.

The $ i $ -th element of the last line should contain the index of the wizard, the house of which is exactly $ a_{i} $ away from the house of the $ i $ -th wizard. If there are multiple such wizards, you can output any.

If there are multiple house placement configurations, you can output any.

## 说明/提示

For the sample, the house of the 1st wizard is located at $ (4, 4) $ , of the 2nd at $ (1, 3) $ , of the 3rd at $ (2, 4) $ , of the 4th at $ (3, 1) $ .

The distance from the house of the 1st wizard to the house of the 1st wizard is $ |4 - 4| + |4 - 4| = 0 $ .

The distance from the house of the 2nd wizard to the house of the 1st wizard is $ |1 - 4| + |3 - 4| = 4 $ .

The distance from the house of the 3rd wizard to the house of the 1st wizard is $ |2 - 4| + |4 - 4| = 2 $ .

The distance from the house of the 4th wizard to the house of the 3rd wizard is $ |3 - 2| + |1 - 4| = 4 $ .

The view and the distance conditions are satisfied for all houses, so the placement is correct.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1970B2/9f9f415b711c20a1d43262d4b959c18fec467842.png)

## 样例 #1

### 输入

```
4
0 4 2 4
```

### 输出

```
YES
4 4
1 3
2 4
3 1
1 1 1 3
```

## 样例 #2

### 输入

```
4
0 1 3 1
```

### 输出

```
YES
1 1
2 1
4 1
3 1
1 1 1 3
```



---

---
title: "Sakurako's Task"
layout: "post"
diff: 普及+/提高
pid: CF2008G
tag: ['数论', '构造']
---

# Sakurako's Task

## 题目描述

Sakurako has prepared a task for you:

She gives you an array of $ n $ integers and allows you to choose $ i $ and $ j $ such that $ i \neq j $ and $ a_i \ge a_j $ , and then assign $ a_i = a_i - a_j $ or $ a_i = a_i + a_j $ . You can perform this operation any number of times for any $ i $ and $ j $ , as long as they satisfy the conditions.

Sakurako asks you what is the maximum possible value of $ mex_k $ $ ^{\text{∗}} $ of the array after any number of operations.

 $ ^{\text{∗}} $ $ mex_k $ is the $ k $ -th non-negative integer that is absent in the array. For example, $ mex_1(\{1,2,3 \})=0 $ , since $ 0 $ is the first element that is not in the array, and $ mex_2(\{0,2,4 \})=3 $ , since $ 3 $ is the second element that is not in the array.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1\le n\le 2\cdot 10^5,1\le k\le 10^9 $ ) — the number of elements in the array and the value $ k $ for $ mex_k $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots,a_n $ ( $ 1\le a_i\le 10^9 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output the maximum $ mex_k $ that can be achieved through the operations.

## 样例 #1

### 输入

```
6
1 3
3
2 10
1 1
3 1
1 2 3
3 2
1 2 4
4 5
2 2 2 16
4 5
2 2 2 3
```

### 输出

```
2
11
3
4
8
8
```



---

---
title: "Asesino (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF2022D1
tag: ['构造']
---

# Asesino (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, you can ask at most $ n+69 $ questions. You can make hacks only if both versions of the problem are solved.

This is an interactive problem.

It is a tradition in Mexico's national IOI trainings to play the game "Asesino", which is similar to "Among Us" or "Mafia".

Today, $ n $ players, numbered from $ 1 $ to $ n $ , will play "Asesino" with the following three roles:

- Knight: a Knight is someone who always tells the truth.
- Knave: a Knave is someone who always lies.
- Impostor: an Impostor is someone everybody thinks is a Knight, but is secretly a Knave.

Each player will be assigned a role in the game. There will be exactly one Impostor but there can be any (possible zero) number of Knights and Knaves.

As the game moderator, you have accidentally forgotten the roles of everyone, but you need to determine the player who is the Impostor.

To determine the Impostor, you will ask some questions. In each question, you will pick two players $ i $ and $ j $ ( $ 1 \leq i, j \leq n $ ; $ i \neq j $ ) and ask if player $ i $ thinks that player $ j $ is a Knight. The results of the question is shown in the table below.

 KnightKnaveImpostorKnightYesNoYesKnaveNoYesNoImpostorNoYes— The response of the cell in row $ a $ and column $ b $ is the result of asking a question when $ i $ has role $ a $ and $ j $ has row $ b $ . For example, the "Yes" in the top right cell belongs to row "Knight" and column "Impostor", so it is the response when $ i $ is a Knight and $ j $ is an Impostor.Find the Impostor in at most $ n + 69 $ questions.

Note: the grader is adaptive: the roles of the players are not fixed in the beginning and may change depending on your questions. However, it is guaranteed that there exists an assignment of roles that is consistent with all previously asked questions under the constraints of this problem.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \le n \le 10^5 $ ) — the number of people playing the game.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

To ask a question, output a line in the following format:

- "? i j" ( $ 1 \leq i,j \leq n $ ; $ i \neq j $ ) — to ask player $ i $ if they think player $ j $ is a Knight.

The jury will output a "1" if player $ i $ thinks player $ j $ is a Knight, and "0" otherwise.

When you have determined which player the Impostor is, output a line in the following format:

- "! i" ( $ 1 \leq i \leq n $ ) — the Impostor is player $ i $ .

Note that answering does not count to your limit of $ n+69 $ questions.

If you have made an invalid output, used more than $ n+69 $ questions or wrongly determined the Impostor, the jury will respond with "-1" and you will receive a Wrong Answer verdict. Upon receiving "-1", your program must terminate immediately. Otherwise, you may receive an arbitrary verdict because your solution might be reading from a closed stream.

After printing a query do not forget to output the end of the line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- sys.stdout.flush() in Python;
- std::io::stdout().flush() in Rust;
- see the documentation for other languages.

Hack format

For hacks, use the following format.

The first line should contain a single integer $ t $ — the number of test cases.

The first line of each test case should contain the integer $ n $ followed by the string "manual".

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -1 \le a_i \le 1 $ ) — the roles of each player. $ 1 $ denotes a Knight, $ 0 $ denotes a Knave, and $ -1 $ dentoes an Impostor. There must be exactly one Impostor, that is there must be exactly one index $ i $ such that $ a_i=-1 $ .

As an example, the hack format for the example input is:

```
<pre class="lstlisting">```
2<br></br>7 manual<br></br>0 1 0 -1 0 1 0<br></br>4 manual<br></br>0 1 -1 0<br></br>
```
```

## 说明/提示

Note that the example test cases do not represent an optimal strategy for asking questions and are only shown for the sake of demonstrating the interaction format. Specifically, we cannot determine which player is the Impostor from the questions asked in the examples.

In the first test case of the example, players at indices $ 2 $ and $ 6 $ are Knights, players at indices $ 1 $ , $ 3 $ , $ 5 $ , and $ 7 $ are Knaves, and the Impostor is at index $ 4 $ . The following is an explanation of the questions asked:

- In the first query, player $ i $ is a Knave and player $ j $ is a Knave. The answer is "yes" since Knaves always lie.
- In the second query, player $ i $ is a Knave and player $ j $ is a Knight. The answer is "no" since Knaves always lie.
- In the third query, player $ i $ is a Knight and player $ j $ is a Knave. The answer is "no" since Knights always tell the truth.
- In the fourth query, player $ i $ is a Knight and player $ j $ is a Knight. The answer is "yes" since Knights always tell the truth.
- In the fifth query, player $ i $ is a Impostor and player $ j $ is a Knave. The answer is "yes" since the Impostor always lies.
- In the sixth query, player $ i $ is a Impostor and player $ j $ is a Knight. The answer is "no" since the Impostor always lies.
- In the seventh query, player $ i $ is a Knave and player $ j $ is a Impostor. The answer is "no" since Knaves always lie and Knaves thinks that the Impostor is a Knight.
- In the eighth query, player $ i $ is a Knight and player $ j $ is a Impostor. The answer is "yes" since Knights always tell the truth and Knights think that the Impostor is a Knight.

## 样例 #1

### 输入

```
2
7

1

0

0

1

1

0

0

1

4

0

1

1

1
```

### 输出

```
? 1 3

? 7 6

? 2 5

? 6 2

? 4 5

? 4 6

? 1 4

? 2 4

! 4

? 1 2

? 2 3

? 3 4

? 4 1

! 3
```



---

---
title: "Cool Graph"
layout: "post"
diff: 普及+/提高
pid: CF2029D
tag: ['图论', '构造']
---

# Cool Graph

## 题目描述

You are given an undirected graph with $ n $ vertices and $ m $ edges.

You can perform the following operation at most $ 2\cdot \max(n,m) $ times:

- Choose three distinct vertices $ a $ , $ b $ , and $ c $ , then for each of the edges $ (a,b) $ , $ (b,c) $ , and $ (c,a) $ , do the following: 
  - If the edge does not exist, add it. On the contrary, if it exists, remove it.

A graph is called cool if and only if one of the following holds:

- The graph has no edges, or
- The graph is a tree.

You have to make the graph cool by performing the above operations. Note that you can use at most $ 2\cdot \max(n,m) $ operations.

It can be shown that there always exists at least one solution.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 3\le n\le 10^5 $ , $ 0\le m\le \min\left(\frac{n(n-1)}{2},2\cdot 10^5\right) $ ) — the number of vertices and the number of edges.

Then $ m $ lines follow, the $ i $ -th line contains two integers $ u_i $ and $ v_i $ ( $ 1\le u_i,v_i\le n $ ) — the two nodes that the $ i $ -th edge connects.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ , and the sum of $ m $ over all test cases does not exceed $ 2\cdot 10^5 $ .

It is guaranteed that there are no self-loops or multiple-edges in the given graph.

## 输出格式

For each test case, in the first line output an integer $ k $ ( $ 0\le k\le 2\cdot \max(n, m) $ ) — the number of operations.

Then output $ k $ lines, the $ i $ -th line containing three distinct integers $ a $ , $ b $ , and $ c $ ( $ 1\le a,b,c\le n $ ) — the three integers you choose in the $ i $ -th operation.

If there are multiple solutions, you can output any of them.

## 说明/提示

In the first test case, the graph is already cool because there are no edges.

In the second test case, after performing the only operation, the graph becomes a tree, so it is cool.

In the third test case, the graph is already cool because it is a tree.

In the fourth test case, after performing the only operation, the graph has no edges, so it is cool.

In the fifth test case:

 OperationGraph before the operationGraph after the operation $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/b0f7ac35f24bdd1ef25527e8445c75c07c81b1cd.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/967d0caf549d17edc01f85e8fd3b92d4a29c78a4.png) $ 2 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/8fc9b337d57d63328a0f768cb6979898a6acb589.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/e76a67a3a1dfd30fecae063029760f2fec760cd4.png) $ 3 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/cd4bbe994192de9db9336eff41b4aa05bb7c27af.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/278495e89dce856c8d1c4a31851cd95fdb2f1cd3.png)Note that after the first operation, the graph has already become cool, and there are two extra operations. As the graph is still cool after the two extra operations, this is a valid answer.

## 样例 #1

### 输入

```
5
3 0
3 1
1 2
3 2
1 2
2 3
3 3
1 2
2 3
3 1
6 6
1 2
1 6
4 5
3 4
4 6
3 6
```

### 输出

```
0
1
1 2 3
0
1
1 2 3
3
1 3 6
2 4 5
3 4 6
```



---

---
title: "Genokraken"
layout: "post"
diff: 普及+/提高
pid: CF2032D
tag: ['图论', '构造']
---

# Genokraken

## 题目描述

This is an interactive problem.

Upon clearing the Waterside Area, Gretel has found a monster named Genokraken, and she's keeping it contained for her scientific studies.

The monster's nerve system can be structured as a tree $ ^{\dagger} $ of $ n $ nodes (really, everything should stop resembling trees all the time $ \ldots $ ), numbered from $ 0 $ to $ n-1 $ , with node $ 0 $ as the root.

Gretel's objective is to learn the exact structure of the monster's nerve system — more specifically, she wants to know the values $ p_1, p_2, \ldots, p_{n-1} $ of the tree, where $ p_i $ ( $ 0 \le p_i < i $ ) is the direct parent node of node $ i $ ( $ 1 \le i \le n - 1 $ ).

She doesn't know exactly how the nodes are placed, but she knows a few convenient facts:

- If we remove root node $ 0 $ and all adjacent edges, this tree will turn into a forest consisting of only paths $ ^{\ddagger} $ . Each node that was initially adjacent to the node $ 0 $ will be the end of some path.
- The nodes are indexed in a way that if $ 1 \le x \le y \le n - 1 $ , then $ p_x \le p_y $ .
- Node $ 1 $ has exactly two adjacent nodes (including the node $ 0 $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/e8258012a39acd46c9074838efef9914b6897d4b.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/206bea28ad893e4b88d7080ccd68226695dddca4.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/62f37c6d61a34178ff5087ddf19cef6e4de6bb74.png)The tree in this picture does not satisfy the condition, because if we remove node $ 0 $ , then node $ 2 $ (which was initially adjacent to the node $ 0 $ ) will not be the end of the path $ 4-2-5 $ .The tree in this picture does not satisfy the condition, because $ p_3 \le p_4 $ must hold.The tree in this picture does not satisfy the condition, because node $ 1 $ has only one adjacent node.Gretel can make queries to the containment cell:

- "? a b" ( $ 1 \le a, b < n $ , $ a \ne b $ ) — the cell will check if the simple path between nodes $ a $ and $ b $ contains the node $ 0 $ .

However, to avoid unexpected consequences by overstimulating the creature, Gretel wants to query at most $ 2n - 6 $ times. Though Gretel is gifted, she can't do everything all at once, so can you give her a helping hand?

 $ ^{\dagger} $ A tree is a connected graph where every pair of distinct nodes has exactly one simple path connecting them.

 $ ^{\ddagger} $ A path is a tree whose vertices can be listed in the order $ v_1, v_2, \ldots, v_k $ such that the edges are $ (v_i, v_{i+1}) $ ( $ 1 \le i < k $ ).

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 4 \le n \le 10^4 $ ) — the number of nodes in Genokraken's nerve system.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^4 $ .

## 输出格式

For each test case, interaction starts by reading the integer $ n $ .

Then you can make queries of the following type:

- "? a b" (without quotes) ( $ 1 \le a, b < n $ , $ a \ne b $ ).

After the query, read an integer $ r $ — the answer to your query. You are allowed to use at most $ 2n - 6 $ queries of this type.

- If the simple path between nodes $ a $ and $ b $ does not contain node $ 0 $ , you will get $ r = 0 $ .
- If the simple path between nodes $ a $ and $ b $ contains node $ 0 $ , you will get $ r = 1 $ .
- In case you make more than $ 2n-6 $ queries or make an invalid query, you will get $ r = -1 $ . You will need to terminate after this to get the "Wrong answer" verdict. Otherwise, you can get an arbitrary verdict because your solution will continue to read from a closed stream.

When you find out the structure, output a line in the format "! $ p_1 \space p_2 \ldots p_{n-1} $ " (without quotes), where $ p_i $ ( $ 0 \le p_i < i $ ) denotes the index of the direct parent of node $ i $ . This query is not counted towards the $ 2n - 6 $ queries limit.

After solving one test case, the program should immediately move on to the next one. After solving all test cases, the program should be terminated immediately.

After printing any query do not forget to output an end of line and flush the output buffer. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

The interactor is non-adaptive. The tree does not change during the interaction.

Hacks

For hack, use the following format:

The first line contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 4 \le n \le 10^4 $ ) — the number of nodes in Genokraken's nerve system.

The second line of each test case contains $ n-1 $ integers $ p_1, p_2, \ldots, p_{n-1} $ ( $ 0 \le p_1 \le p_2 \le \ldots \le p_{n-1} \le n - 2 $ , $ 0 \le p_i < i $ ) — the direct parents of node $ 1 $ , $ 2 $ , ..., $ n-1 $ in the system, respectively.

In each test case, the values $ p_1, p_2, \ldots, p_{n-1} $ must ensure the following in the tree:

- If we remove root node $ 0 $ and all adjacent edges, this tree will turn into a forest consisting of only paths. Each node that was initially adjacent to the node $ 0 $ will be the end of some path.
- Node $ 1 $ has exactly two adjacent nodes (including the node $ 0 $ ).

The sum of $ n $ over all test cases must not exceed $ 10^4 $ .

## 说明/提示

In the first test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/f881123b596891d36ab778596441f15ad95a02ea.png)- The answer to "? 2 3" is $ 1 $ . This means that the simple path between nodes $ 2 $ and $ 3 $ contains node $ 0 $ .

In the second test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/33f1d468944f56ba6a97f7e156678062fb607fea.png)- The answer to "? 2 3" is $ 1 $ . This means that the simple path between nodes $ 2 $ and $ 3 $ contains node $ 0 $ .
- The answer to "? 2 4" is $ 0 $ . This means that the simple path between nodes $ 2 $ and $ 4 $ doesn't contain node $ 0 $ .

In the third test case, Genokraken's nerve system forms the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2032D/80e7fbd696eda68303e33490520aebb364943d67.png)

## 样例 #1

### 输入

```
3
4

1

5

1

0

9
```

### 输出

```
? 2 3

! 0 0 1

? 2 3

? 2 4

! 0 0 1 2

! 0 0 0 1 3 5 6 7
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
title: "Non Prime Tree"
layout: "post"
diff: 普及+/提高
pid: CF2040D
tag: ['数学', '构造']
---

# Non Prime Tree

## 题目描述

给你一棵拥有 $n$ 个顶点的树。

你的任务是构造一个包含 $n$ 个不同整数的数组，这些整数从 $1$ 到 $2 \cdot n$ 分别取值。同时要求对于树中的任意一条边 $u_i \leftrightarrow v_i$，对应的数组元素差值 $|a_{u_i} - a_{v_i}|$ 不是质数。

请你找出任意一个符合以上条件的数组，如果不存在这样的数组，请输出 $-1$。

## 输入格式

每组测试用例包含多个测试。首行给出测试用例数量 $t$（$1 \le t \le 10^4$）。每个测试用例的描述如下：

第一行一个整数 $n$（$2 \le n \le 2 \cdot 10^5$），表示树的顶点数量。

接下来的 $n-1$ 行，每行描述一条树的边。具体来说，第 $i$ 行给出两个整数 $u_i$ 和 $v_i$（$1 \le u_i, v_i \le n$；$u_i \neq v_i$），表示节点 $u_i$ 和 $v_i$ 之间有边相连。

可以保证给定的边组成一棵树。此外，所有测试用例中的 $n$ 总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果找到满足条件的数组，输出该数组的元素 $a_1, a_2, \ldots, a_n$。如果找不到，则输出 $-1$。

## 说明/提示

如下图所示的答案中，用对应数组 $a$ 的元素替代了顶点编号：

第一组数据的树结构 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040D/d6a56c20ebd42ea20ac170d596c01c0583a1b831.png)  
第二组数据的树结构 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040D/8328682bcf4d0da5fcbe8de4a0054b43d22d093e.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
5
1 2
2 3
2 4
3 5
7
1 2
1 3
2 4
3 5
3 6
3 7
```

### 输出

```
2 10 1 6 5 
8 7 12 1 4 6 3
```



---

---
title: "Kevin and Bipartite Graph"
layout: "post"
diff: 普及+/提高
pid: CF2048E
tag: ['二分图', '构造']
---

# Kevin and Bipartite Graph

## 题目描述

武器工厂需要一种海报设计模式，并向 Kevin 求助。

海报设计模式是一个二分图，左半部分有 $2n$ 个顶点，右半部分有 $m$ 个顶点。左半部分的每个顶点与右半部分的每个顶点之间都有一条边，总共形成 $2nm$ 条边。

Kevin 必须用范围在 $[1, n]$ 内的正整数为每条边着色。如果二分图中没有单色环（所有边颜色相同的简单环），则该海报设计模式是良好的。

Kevin 需要你的帮助来构造一个良好的二分图，或者在不可能的情况下通知他。

**单色环**：指所有边颜色都相同的简单环。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \leq t \leq 100$）。

每个测试用例的唯一一行包含两个整数 $n$ 和 $m$（$1 \leq n, m \leq 10^3$），表示二分图左半部分有 $2n$ 个顶点，右半部分有 $m$ 个顶点。

保证所有测试用例的 $n$ 之和以及 $m$ 之和都不超过 $10^3$。

## 输出格式

对于每个测试用例，如果没有解决方案，则输出 No。

否则，首先输出 Yes，然后输出 $2n$ 行，每行包含 $m$ 个正整数。第 $i$ 行的第 $j$ 个整数表示左半部分第 $i$ 个顶点和右半部分第 $j$ 个顶点之间的边的颜色。

如果有多个答案，可以输出其中任何一个。

你可以以任何大小写形式输出每个字母（例如，字符串 yEs、yes、Yes 和 YES 都将被识别为肯定回答）。

## 说明/提示

对于第一个测试用例，图形如下所示：

对于第二个测试用例，可以证明没有有效的解决方案。

## 样例 #1

### 输入

```
3
2 2
3 7
5 4
```

### 输出

```
YES
1 2
2 1
2 2
2 1
NO
YES
1 1 1 1
1 2 2 2
1 2 3 3
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
```



---

---
title: "Finding OR Sum"
layout: "post"
diff: 普及+/提高
pid: CF2077B
tag: ['位运算', '构造']
---

# Finding OR Sum

## 题目描述

[ALTER EGO - Yuta Imai vs Qlarabelle](https://www.youtube.com/watch?v=LJEqM7pvClA)

这是一道交互题。

存在两个隐藏的非负整数 $x$ 和 $y$（$0 \leq x, y < 2^{30}$）。你最多可以提出 2 次以下形式的询问：

- 选择一个非负整数 $n$（$0 \leq n < 2^{30}$）。评测系统将返回 $(n \mathbin{|} x) + (n \mathbin{|} y)$ 的值，其中 $|$ 表示[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。

此后，评测系统将给出另一个非负整数 $m$（$0 \leq m < 2^{30}$）。你必须正确回答 $(m \mathbin{|} x) + (m \mathbin{|} y)$ 的值。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

## 输出格式

已选择两个隐藏整数 $x$ 和 $y$（$0 \leq x, y < 2^{30}$）。注意 $x$ 和 $y$ 可能因不同测试用例而异。

本题的交互器是非自适应的。换句话说，整数 $x$ 和 $y$ 在交互过程中不会改变。

要提出询问，请选择一个整数 $n$（$0 \leq n < 2^{30}$）并在一行中仅输出该整数 $n$。

你将收到一个整数，即 $(n \mathbin{|} x) + (n \mathbin{|} y)$ 的值。

你最多只能提出 2 次此类询问。

完成询问后，在一行中输出 "!"。你将收到一个整数 $m$（$0 \leq m < 2^{30}$）。注意 $m$ 的值在交互开始前也已确定。

你必须在一行中仅输出 $(m \mathbin{|} x) + (m \mathbin{|} y)$ 的值。注意此行不被视为询问，不计入询问次数统计。

完成此操作后，继续处理下一个测试用例。

如果在交互过程中提出超过 2 次询问，你的程序必须立即终止，并得到 Wrong Answer 的判定结果。否则，由于你的解决方案将继续从已关闭的流中读取数据，可能会得到任意判定结果。

在输出询问后请勿忘记换行并刷新输出缓冲区。否则你将得到 Idleness limit exceeded。为此，请使用：

- C++ 中的 fflush(stdout) 或 cout.flush()；
- Java 中的 System.out.flush()；
- Pascal 中的 flush(output)；
- Python 中的 stdout.flush()；
- 其他语言请参考相关文档。

## 说明/提示

### 示例交互

在第一个测试中，交互过程如下：

| 解决方案输出 | 评测系统输出 | 说明 |
|--------------|--------------|------|
| `2`          |              | 共有 2 个测试用例 |
|              |              | 第一个测试用例中 $x=1$ 且 $y=2$ |
| `0`          |              | 解决方案询问 $(0 \mathbin{\|} 1) + (0 \mathbin{\|} 2)$ |
|              | `3`          | 评测系统返回 3 |
| `1`          |              | 解决方案询问 $(1 \mathbin{\|} 1) + (1 \mathbin{\|} 2)$ |
|              | `4`          | 评测系统返回 4 |
| `!`          |              | 解决方案请求 $m$ 的值 |
|              | `1`          | 评测系统返回 $m=1$ |
| `4`          |              | 解决方案根据先前询问得知 $(1 \mathbin{\|} x) + (1 \mathbin{\|} y)=4$ |
|              |              | 第二个测试用例中 $x=0$ 且 $y=0$ |
| `0`          |              | 解决方案询问 $(0 \mathbin{\|} 0) + (0 \mathbin{\|} 0)$ |
|              | `0`          | 评测系统返回 0 |
| `!`          |              | 解决方案请求 $m$ 的值 |
|              | `1`          | 评测系统返回 $m=1$ |
| `2`          |              | 解决方案推断出 $x=y=0$，因此返回 $(1 \mathbin{\|} 0) + (1 \mathbin{\|} 0)=2$ |

注意示例输入输出中的空行仅为清晰展示，实际交互中不会出现。

注意示例输入输出中的空行仅为清晰展示，实际交互中不会出现。

## Hacks

要发起 hack，请遵循以下测试格式：

第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的第一行且唯一一行包含三个整数 $x, y, m$（$0 \leq x, y, m < 2^{30}$）。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2

3

4

1

0

1
```

### 输出

```
0

1

!

4

0

!

2
```



---

---
title: "Arcology On Permafrost"
layout: "post"
diff: 普及+/提高
pid: CF2084D
tag: ['贪心', '构造']
---

# Arcology On Permafrost

## 题目描述

给定三个整数 $n$、$m$ 和 $k$，其中满足 $m \cdot k < n$。

对于一个由非负整数组成的序列 $b$，定义 $f(b)$ 如下：

- 你可以对 $b$ 进行如下操作：
  - 设 $l$ 表示当前 $b$ 的长度。选择一个正整数 $1 \leq i \leq l - k + 1$，删除从下标 $i$ 到 $i + k - 1$ 的子数组，并将剩余部分拼接。换句话说，将 $b$ 替换为：
    $$
    [b_1, b_2, \ldots, b_{i - 1}, b_{i + k}, b_{i + k + 1}, \ldots, b_l].
    $$
- $f(b)$ 定义为在进行最多 $m$ 次（可以是零次）上述操作后，$\operatorname{mex}(b)$ 的**最小**可能值 $^{\text{∗}}$。

你需要构造一个长度为 $n$ 的非负整数序列 $a$，满足以下条件：
- 对于所有 $1 \le i \le n$，$0 \le a_i \le 10^9$。
- 在所有满足条件的序列 $a$ 中，$f(a)$ 的值最大化。

$^{\text{∗}}$ 集合 $c = \{c_1, c_2, \ldots, c_k\}$ 的最小排除值（MEX）定义为不包含在 $c$ 中的最小非负整数 $x$。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含三个整数 $n$、$m$ 和 $k$（$2 \le n \le 2 \cdot 10^5$，$1 \le m < n$，$1 \le k < n$，$1 \le m \cdot k < n$）。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \le a_i \le 10^9$）。

如果有多个答案，输出任意一个即可。

## 说明/提示

- 在第一个测试用例中，可以证明 $f(a) = 1$ 是最大化的结果。
- 在第二个测试用例中，可以证明 $f(a) = 1$ 是最大化的结果。$f(a) = 1$ 是因为你可以进行以下操作：
  - 选择 $i = 3$，删除下标 $3$ 到 $4$ 的子数组，剩余部分拼接后 $a$ 变为 $[0, 1, 0]$。
  - 选择 $i = 1$，删除下标 $1$ 到 $2$ 的子数组，剩余部分拼接后 $a$ 变为 $[0]$。
- 在第三个测试用例中，可以证明 $f(a) = 2$ 是最大化的结果。$f(a) = 2$ 是因为你可以进行以下操作：
  - 选择 $i = 2$，删除下标 $2$ 到 $5$ 的子数组，剩余部分拼接后 $a$ 变为 $[0, 1]$。
- 在第四个测试用例中，可以证明 $f(a) = 2$ 是最大化的结果。
- 在第五个测试用例中，可以证明 $f(a) = 3$ 是最大化的结果。
- 在第六个测试用例中，可以证明 $f(a) = 2$ 是最大化的结果。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
2 1 1
5 2 2
6 1 4
8 2 2
8 1 5
11 3 3
22 6 3
17 2 2
```

### 输出

```
0 0
0 1 0 0 0
0 1 2 2 0 1
0 2 1 0 1 0 8 1
0 1 2 1000000000 1 0 1 2
1 0 0 1 0 2 1 0 2 1 0
0 2 1 0 2 1 0 3 2 1 0 2 1 0 2 1 0 2 1 0 2 1
4 0 2 1 3 4 0 2 1 0 3 4 0 1 2 1 3
```



---

---
title: "Simple Permutation"
layout: "post"
diff: 普及+/提高
pid: CF2089A
tag: ['数学', '构造']
---

# Simple Permutation

## 题目描述

给定一个整数 $n$。构造一个长度为 $n$ 的排列 $p_1, p_2, \ldots, p_n$，使其满足以下性质：

对于 $1 \le i \le n$，定义 $c_i = \lceil \frac{p_1 + p_2 + \ldots + p_i}{i} \rceil$，那么在 $c_1, c_2, \ldots, c_n$ 中必须至少有 $\lfloor \frac{n}{3} \rfloor - 1$ 个素数。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10$）——测试用例的数量。接下来描述每个测试用例。

每个测试用例的一行中包含一个整数 $n$（$2 \le n \le 10^5$）——排列的大小。

## 输出格式

对于每个测试用例，输出满足条件的排列 $p_1, p_2, \ldots, p_n$。题目保证这样的排列总是存在。

## 说明/提示

第一个测试案例中，$c_1 = \lceil \frac{2}{1} \rceil = 2$，$c_2 = \lceil \frac{2+1}{2} \rceil = 2$。这两个数都是素数。

第三个测试案例中，$c_1 = \lceil \frac{2}{1} \rceil = 2$，$c_2 = \lceil \frac{3}{2} \rceil = 2$，$c_3 = \lceil \frac{6}{3} \rceil = 2$，$c_4 = \lceil \frac{10}{4} \rceil = 3$，$c_5 = \lceil \frac{15}{5} \rceil = 3$。所有这些数都是素数。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
2
3
5
```

### 输出

```
2 1
2 1 3
2 1 3 4 5
```



---

---
title: "Local Construction"
layout: "post"
diff: 普及+/提高
pid: CF2103D
tag: ['构造', '双指针 two-pointer']
---

# Local Construction

## 题目描述

在数组 $b_1, b_2, \ldots, b_m$ 中，元素 $b_i$（$1 \le i \le m$）是局部最小值当且仅当满足以下至少一个条件：
- $2 \le i \le m - 1$ 且 $b_i < b_{i - 1}$ 且 $b_i < b_{i + 1}$，或
- $i = 1$ 且 $b_1 < b_2$，或
- $i = m$ 且 $b_m < b_{m - 1}$。

类似地，元素 $b_i$（$1 \le i \le m$）是局部最大值当且仅当满足以下至少一个条件：
- $2 \le i \le m - 1$ 且 $b_i > b_{i - 1}$ 且 $b_i > b_{i + 1}$，或
- $i = 1$ 且 $b_1 > b_2$，或
- $i = m$ 且 $b_m > b_{m - 1}$。

注意，对于只有一个元素的数组，局部最小值和局部最大值没有定义。

给定一个隐藏的排列 $^{\text{∗}}$ $p$，其长度为 $n$。对该排列交替执行以下两种操作，从操作 1 开始，直到 $p$ 中只剩一个元素：
- 操作 1 —— 删除 $p$ 中所有不是局部最小值的元素。
- 操作 2 —— 删除 $p$ 中所有不是局部最大值的元素。

具体来说，在每次奇数轮迭代时执行操作 1，在每次偶数轮迭代时执行操作 2，直到 $p$ 中只剩一个元素。

对于每个下标 $i$（$1 \le i \le n$），设 $a_i$ 为元素 $p_i$ 被删除的轮次编号，若未被删除则设为 $-1$。

可以证明，最多经过 $\lceil \log_2 n \rceil$ 轮迭代后 $p$ 中只剩一个元素（即 $a_i \le \lceil \log_2 n \rceil$）。

给定数组 $a_1, a_2, \ldots, a_n$，你的任务是构造任意一个满足数组 $a$ 的排列 $p$。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是（因为 $2$ 出现了两次），$[1,3,4]$ 也不是（因为 $n=3$ 但出现了 $4$）。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 2 \cdot 10^5$）——排列 $p$ 的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le \lceil \log_2 n \rceil$ 或 $a_i = -1$）——元素 $p_i$ 被删除的轮次编号。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

保证至少存在一个满足数组 $a$ 的排列 $p$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数，表示满足数组 $a$ 的排列。

如果有多个解，输出任意一个即可。

## 说明/提示

在第一个测试用例中，对排列 $[3, 2, 1]$ 执行的操作如下：
1. $[3, 2, 1]$ 的唯一局部最小值是 $1$，因此删除 $3$ 和 $2$。此时只剩一个元素，过程终止。
这满足数组 $a = [1, 1, -1]$，因为 $p_1$ 和 $p_2$ 在第 1 轮被删除，而 $p_3$ 未被删除。

在第二个测试用例中，对排列 $[4, 3, 5, 1, 2]$ 执行的操作如下：
1. $[4, 3, 5, 1, 2]$ 的局部最小值是 $3$ 和 $1$，因此删除 $4$、$5$ 和 $2$。
2. $[3, 1]$ 的唯一局部最大值是 $3$，因此删除 $1$。此时只剩一个元素，过程终止。
这满足数组 $a = [1, -1, 1, 2, 1]$，因为 $p_1$、$p_3$ 和 $p_5$ 在第 1 轮被删除，$p_4$ 在第 2 轮被删除，$p_2$ 未被删除。

在第三个测试用例中，对排列 $[6, 7, 2, 4, 3, 8, 5, 1]$ 执行的操作如下：
1. 局部最小值是 $6$、$2$、$3$ 和 $1$，因此删除 $7$、$4$、$8$ 和 $5$。
2. 局部最大值是 $6$ 和 $3$，因此删除 $2$ 和 $1$。
3. 局部最小值是 $3$，因此删除 $6$。此时只剩一个元素，过程终止。

在第四个测试用例中，一个满足条件的排列是 $[6, 5, 2, 1, 3, 4, 7]$。$1$ 是唯一的局部最小值，因此它会在第一轮后保留。注意，其他排列也可能满足条件，例如 $[6, 4, 3, 1, 2, 5, 7]$ 也是正确的解。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
3
1 1 -1
5
1 -1 1 2 1
8
3 1 2 1 -1 1 1 2
7
1 1 1 -1 1 1 1
5
1 1 1 1 -1
5
-1 1 1 1 1
5
-1 1 2 1 2
```

### 输出

```
3 2 1
4 3 5 1 2
6 7 2 4 3 8 5 1
6 5 2 1 3 4 7
5 4 3 2 1
1 2 3 4 5
4 5 2 3 1
```



---

---
title: "Reachability and Tree"
layout: "post"
diff: 普及+/提高
pid: CF2112D
tag: ['图论', '构造']
---

# Reachability and Tree

## 题目描述

考虑一个有向图，我们称有序数对 $(u,v)$ 是好的当且仅当 $u\ne v$ 且图中存在一条 $u$ 到 $v$ 的路径。

给你一棵 $n$ 个结点的树，问有没有一种把这棵树的所有 $n-1$ 条边确定方向的方案，使得形成的有向图中恰有 $n$ 个好的数对。如果存在，给出任意一种方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2112D/5e96780aa4a833603401ce38c95583d3dff310ba.png)

对于第一组数据，这是一种可能的定向方案。

## 输入格式

多组数据。第一行一个整数 $t(1\le t\le 10^4)$，表示数据组数。

对于每组数据，第一行输入一个正整数 $n(2\le n\le 2\times 10^5)$。

接下来 $n-1$ 行，每行输入两个整 $u_i,v_i(1\le u_i,v_i\le n,n_i\ne v_i)$，表示树上的一条边。

保证每组数据输入的图均构成一棵无向树。保证单个测试点内 $n$ 的和不超过 $2\times 10^5$。

## 输出格式

对于每组数据，如果不存在定向方案使得形成的有向图中恰有 $n$ 个好的数对，输出一行 `NO`（大小写不敏感）。

否则，输出一行 `YES`（大小写不敏感），接下来输出 $n-1$ 行，每行两个正整数 $u_i,v_i$，表示你给出的方案形成的有向图中一条结点 $u_i$ 指向结点 $v_i$ 的边。边的输出顺序不限。如果有多种解，输出任意一种均可。

## 说明/提示

**样例解释**

对于第一组数据，一种可能的定向方案如上图所示。在此方案中五个好的数对为 $(3,5),(3,1),(3,2),(1,2),(4,2)$。

对于第二组数据，一种可能的定向方案如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2112D/a9d7677ec7ba1046004aa29fc6e4a4dca863d6eb.png)

在此方案中五个好的数对为 $(2,1),(3,1),(4,1),(5,4),(5,1)$。

对于第三组数据，只有两个有序数对，无论这条唯一的边指向哪个方向，都只有一个数对会是好的。

## 样例 #1

### 输入

```
4
5
1 2
2 4
1 3
3 5
5
1 2
1 3
1 4
4 5
2
2 1
4
3 1
1 2
2 4
```

### 输出

```
YES
1 2
3 1
3 5
4 2
YES
2 1
3 1
4 1
5 4
NO
YES
1 3
2 1
2 4
```



---

---
title: "Little Victor and Set"
layout: "post"
diff: 普及+/提高
pid: CF460D
tag: ['贪心', '枚举', '构造']
---

# Little Victor and Set

## 题目描述

Little Victor adores the sets theory. Let us remind you that a set is a group of numbers where all numbers are pairwise distinct. Today Victor wants to find a set of integers $ S $ that has the following properties:

- for all $ x $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/26c8948a606517ebae5f50ff9b8fc7d91f76f3df.png) the following inequality holds $ l<=x<=r $ ;
- $ 1<=|S|<=k $ ;
- lets denote the $ i $ -th element of the set $ S $ as $ s_{i} $ ; value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/7523823a9f324064de1df35c0e0503740f7be786.png) must be as small as possible.

Help Victor find the described set.

## 输入格式

The first line contains three space-separated integers $ l,r,k $ $ (1<=l<=r<=10^{12}; 1<=k<=min(10^{6},r-l+1)) $ .

## 输出格式

Print the minimum possible value of $ f(S) $ . Then print the cardinality of set $ |S| $ . Then print the elements of the set in any order.

If there are multiple optimal sets, you can print any of them.

## 说明/提示

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) represents the operation of bitwise exclusive OR. In other words, it is the XOR operation.

## 样例 #1

### 输入

```
8 15 3

```

### 输出

```
1
2
10 11

```

## 样例 #2

### 输入

```
8 30 7

```

### 输出

```
0
5
14 9 28 11 16

```



---

---
title: "Sums of Digits"
layout: "post"
diff: 普及+/提高
pid: CF509C
tag: ['构造']
---

# Sums of Digits

## 题目描述

Vasya had a strictly increasing sequence of positive integers $ a_{1} $ , ..., $ a_{n} $ . Vasya used it to build a new sequence $ b_{1} $ , ..., $ b_{n} $ , where $ b_{i} $ is the sum of digits of $ a_{i} $ 's decimal representation. Then sequence $ a_{i} $ got lost and all that remained is sequence $ b_{i} $ .

Vasya wonders what the numbers $ a_{i} $ could be like. Of all the possible options he likes the one sequence with the minimum possible last number $ a_{n} $ . Help Vasya restore the initial sequence.

It is guaranteed that such a sequence always exists.

## 输入格式

The first line contains a single integer number $ n $ ( $ 1<=n<=300 $ ).

Next $ n $ lines contain integer numbers $ b_{1} $ , ..., $ b_{n} $ — the required sums of digits. All $ b_{i} $ belong to the range $ 1<=b_{i}<=300 $ .

## 输出格式

Print $ n $ integer numbers, one per line — the correct option for numbers $ a_{i} $ , in order of following in sequence. The sequence should be strictly increasing. The sum of digits of the $ i $ -th number should be equal to $ b_{i} $ .

If there are multiple sequences with least possible number $ a_{n} $ , print any of them. Print the numbers without leading zeroes.

## 样例 #1

### 输入

```
3
1
2
3

```

### 输出

```
1
2
3

```

## 样例 #2

### 输入

```
3
3
2
1

```

### 输出

```
3
11
100

```



---

---
title: "Clique Problem"
layout: "post"
diff: 普及+/提高
pid: CF527D
tag: ['贪心', '排序', '构造']
---

# Clique Problem

## 题目描述

数轴上有 $n$ 个点，第 $i$ 个点的坐标为 $x_i$，权值为  $w_i$。两个点 $i,j$ 之间存在一条边当且仅当 $abs(x_i-x_j)\geq w_i+w_j$ 。 你需要求出这张图的最大团的点数。

团的定义：两两之间有边的顶点集合。

## 输入格式

第一行一个整数 $n$，接下来 $n$ 行每行两个整数 $x_i,w_i$ 。

## 输出格式

一行一个整数表示答案。 

感谢@Asougi_Kazuma 提供的翻译。

感谢@皎月半洒花 将翻译改成了正常人能看明白的翻译。

## 样例 #1

### 输入

```
4
2 3
3 1
6 1
0 2

```

### 输出

```
3

```



---

---
title: "Peter and Snow Blower"
layout: "post"
diff: 普及+/提高
pid: CF613A
tag: ['模拟', '数学', '构造']
---

# Peter and Snow Blower

## 题目描述

Peter got a new snow blower as a New Year present. Of course, Peter decided to try it immediately. After reading the instructions he realized that it does not work like regular snow blowing machines. In order to make it work, you need to tie it to some point that it does not cover, and then switch it on. As a result it will go along a circle around this point and will remove all the snow from its path.

Formally, we assume that Peter's machine is a polygon on a plane. Then, after the machine is switched on, it will make a circle around the point to which Peter tied it (this point lies strictly outside the polygon). That is, each of the points lying within or on the border of the polygon will move along the circular trajectory, with the center of the circle at the point to which Peter tied his machine.

Peter decided to tie his car to point $ P $ and now he is wondering what is the area of ​​the region that will be cleared from snow. Help him.

## 输入格式

The first line of the input contains three integers — the number of vertices of the polygon $ n $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/e07eddcf01ea19e02be99447a5d31677c12c0459.png)), and coordinates of point $ P $ .

Each of the next $ n $ lines contains two integers — coordinates of the vertices of the polygon in the clockwise or counterclockwise order. It is guaranteed that no three consecutive vertices lie on a common straight line.

All the numbers in the input are integers that do not exceed $ 1000000 $ in their absolute value.

## 输出格式

Print a single real value number — the area of the region that will be cleared. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 说明/提示

In the first sample snow will be removed from that area:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/d58837ea7895097f43b3c725628f9a11757bb6b3.png)

## 样例 #1

### 输入

```
3 0 0
0 1
-1 2
1 2

```

### 输出

```
12.566370614359172464

```

## 样例 #2

### 输入

```
4 1 -1
0 0
1 2
2 0
1 1

```

### 输出

```
21.991148575128551812

```



---

---
title: "Palindrome Degree"
layout: "post"
diff: 普及+/提高
pid: CF7D
tag: ['字符串', '哈希 hashing', '构造']
---

# Palindrome Degree

## 题目描述

String $ s $ of length $ n $ is called $ k $ -palindrome, if it is a palindrome itself, and its prefix and suffix of length ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF7D/f337f976991ac53405b164907ebe1f51ebb0830e.png) are $ (k-1) $ -palindromes. By definition, any string (even empty) is 0-palindrome.

Let's call the palindrome degree of string $ s $ such a maximum number $ k $ , for which $ s $ is $ k $ -palindrome. For example, "abaaba" has degree equals to $ 3 $ .

You are given a string. Your task is to find the sum of the palindrome degrees of all its prefixes.

## 输入格式

The first line of the input data contains a non-empty string, consisting of Latin letters and digits. The length of the string does not exceed $ 5·10^{6} $ . The string is case-sensitive.

## 输出格式

Output the only number — the sum of the polindrome degrees of all the string's prefixes.

## 样例 #1

### 输入

```
a2A

```

### 输出

```
1
```

## 样例 #2

### 输入

```
abacaba

```

### 输出

```
6
```



---

