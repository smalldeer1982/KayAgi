---
title: "Chests and Keys"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1519F
tag: ['动态规划 DP', '二分图']
---

# Chests and Keys

## 题目描述

Alice and Bob play a game. Alice has got $ n $ treasure chests (the $ i $ -th of which contains $ a_i $ coins) and $ m $ keys (the $ j $ -th of which she can sell Bob for $ b_j $ coins).

Firstly, Alice puts some locks on the chests. There are $ m $ types of locks, the locks of the $ j $ -th type can only be opened with the $ j $ -th key. To put a lock of type $ j $ on the $ i $ -th chest, Alice has to pay $ c_{i,j} $ dollars. Alice can put any number of different types of locks on each chest (possibly, zero).

Then, Bob buys some of the keys from Alice (possibly none, possibly all of them) and opens each chest he can (he can open a chest if he has the keys for all of the locks on this chest). Bob's profit is the difference between the total number of coins in the opened chests and the total number of coins he spends buying keys from Alice. If Bob's profit is strictly positive (greater than zero), he wins the game. Otherwise, Alice wins the game.

Alice wants to put some locks on some chests so no matter which keys Bob buys, she always wins (Bob cannot get positive profit). Of course, she wants to spend the minimum possible number of dollars on buying the locks. Help her to determine whether she can win the game at all, and if she can, how many dollars she has to spend on the locks.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 6 $ ) — the number of chests and the number of keys, respectively.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 4 $ ), where $ a_i $ is the number of coins in the $ i $ -th chest.

The third line contains $ m $ integers $ b_1, b_2, \dots, b_m $ ( $ 1 \le b_j \le 4 $ ), where $ b_j $ is the number of coins Bob has to spend to buy the $ j $ -th key from Alice.

Then $ n $ lines follow. The $ i $ -th of them contains $ m $ integers $ c_{i,1}, c_{i,2}, \dots, c_{i,m} $ ( $ 1 \le c_{i,j} \le 10^7 $ ), where $ c_{i,j} $ is the number of dollars Alice has to spend to put a lock of the $ j $ -th type on the $ i $ -th chest.

## 输出格式

If Alice cannot ensure her victory (no matter which locks she puts on which chests, Bob always has a way to gain positive profit), print $ -1 $ .

Otherwise, print one integer — the minimum number of dollars Alice has to spend to win the game regardless of Bob's actions.

## 说明/提示

In the first example, Alice should put locks of types $ 1 $ and $ 3 $ on the first chest, and locks of type $ 2 $ and $ 3 $ on the second chest.

In the second example, Alice should put locks of types $ 1 $ and $ 2 $ on the first chest, and a lock of type $ 3 $ on the second chest.

## 样例 #1

### 输入

```
2 3
3 3
1 1 4
10 20 100
20 15 80
```

### 输出

```
205
```

## 样例 #2

### 输入

```
2 3
3 3
2 1 4
10 20 100
20 15 80
```

### 输出

```
110
```

## 样例 #3

### 输入

```
2 3
3 4
1 1 4
10 20 100
20 15 80
```

### 输出

```
-1
```



---

---
title: "Turing's Award"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1530H
tag: ['动态规划 DP']
---

# Turing's Award

## 题目描述

Alan Turing is standing on a tape divided into cells that is infinite in both directions.

Cells are numbered with consecutive integers from left to right. Alan is initially standing in cell $ 0 $ . Every cell $ x $ has cell $ x - 1 $ on the left and cell $ x + 1 $ on the right.

Each cell can either contain an integer or be empty. Initially all cells are empty.

Alan is given a permutation $ a_1, a_2, \ldots, a_n $ of integers from $ 1 $ to $ n $ that was chosen uniformly at random among all permutations of length $ n $ .

At time $ 1 $ , integer $ a_1 $ is written down into cell $ 0 $ where Alan is located.

At each time $ i $ from $ 2 $ to $ n $ inclusive, the following happens. First, Alan decides whether to stay in the same cell he's currently in, move to the neighboring cell on the left, or move to the neighboring cell on the right. After that, integer $ a_i $ is written down into the cell where Alan is located. If that cell already contained some integer, the old integer is overwritten and irrelevant from that moment on.

Once $ a_n $ is written down into some cell at time $ n $ , sequence $ b $ of all integers contained in the cells from left to right is formed. Empty cells are ignored.

Turing's award is equal to the length of the longest increasing subsequence of sequence $ b $ .

Help Alan and determine the largest possible value of his award if he acts optimally.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). Description of the test cases follows.

Each test case is given in two lines. The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 15\,000 $ ) — the length of the permutation given to Alan.

The second line contains $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the elements of the permutation.

It is guaranteed that the permutation was chosen uniformly at random among all permutations of the corresponding length.

The sum of $ n $ over all test cases does not exceed $ 15\,000 $ .

## 输出格式

For each test case output a single integer — the largest possible value of Turing's award.

Hacks are not allowed for this problem.

## 说明/提示

Longest increasing subsequence of sequence $ b $ is the longest increasing sequence that can be obtained from $ b $ by deletion of several (possibly, zero or all) elements.

In the first test case, Alan can make a decision only at time $ 2 $ . If Alan stays in cell $ 0 $ , sequence $ b $ will be equal to $ [2] $ . If Alan moves to the left, to cell $ -1 $ , sequence $ b $ will be equal to $ [2, 1] $ . If Alan moves to the right, to cell $ 1 $ , sequence $ b $ will be equal to $ [1, 2] $ . Only in the last case the length of the longest increasing subsequence of $ b $ is $ 2 $ , therefore, the answer is equal to $ 2 $ .

In the second test case, one of the optimal sequences of actions looks as follows: move to the left at times $ 2 $ and $ 3 $ , and move to the right at time $ 4 $ . Then sequence $ b $ will be equal to $ [2, 3, 4] $ , and the length of its longest increasing subsequence is $ 3 $ .

In the third test case, one of the best ways is to always move to the left. Then sequence $ b $ will be equal to $ [2, 1, 4, 7, 5, 6, 3] $ , and the length of its longest increasing subsequence is $ 4 $ .

In the fourth test case, one of the best ways is to move to the right four times, then move to the left once, and stay in the same cell once. Sequence $ b $ will be equal to $ [5, 2, 3, 4, 6] $ .

## 样例 #1

### 输入

```
4
2
1 2
4
4 1 2 3
7
3 6 5 7 4 1 2
7
5 2 3 7 6 1 4
```

### 输出

```
2
3
4
4
```



---

---
title: "PalindORme"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1605F
tag: ['动态规划 DP', '组合数学']
---

# PalindORme

## 题目描述

An integer array $ a $ of length $ n $ is said to be a PalindORme if ( $ a_{1} $ $ | $ $ a_{2}  $ $ | $ $  \ldots  $ $ | $ $  a_{i}) = (a_{{n - i + 1}}  $ $ | $ $  \ldots  $ $ | $ $  a_{{n - 1}}  $ $ | $ $  a_{n})  $ for all $  1 \leq i \leq n $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

An integer array $ a $ of length $ n $ is considered to be good if its elements can be rearranged to form a PalindORme. Formally, array $ a $ is good if there exists a permutation $ p_1, p_2, \ldots p_n $ (an array where each integer from $ 1 $ to $ n $ appears exactly once) for which $ a_{p_1}, a_{p_2}, \ldots a_{p_n} $ is a PalindORme.

Find the number of good arrays of length $ n $ , consisting only of integers in the range $ [0, 2^{k} - 1] $ , and print it modulo some prime $ m $ .

Two arrays $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ are considered to be different if there exists any $ i $ $ (1 \leq i \leq n) $ such that $ a_i \ne b_i $ .

## 输入格式

The first and only line of the input contains three integers $ n $ , $ k $ and $ m $ ( $ 1 \leq n,k \leq 80 $ , $ 10^8 \lt m \lt 10^9 $ ). It is guaranteed that $ m $ is prime.

## 输出格式

Print a single integer — the number of good arrays modulo $ m $ .

## 说明/提示

In the first sample, both the possible arrays $ [0] $ and $ [1] $ are good.

In the second sample, some examples of good arrays are:

- $ [2, 1, 2] $ because it is already PalindORme.
- $ [1, 1, 0] $ because it can rearranged to $ [1, 0, 1] $ which is PalindORme

Note that $ [1, 1, 0] $ , $ [1, 0, 1] $ and $ [0, 1, 1] $ are all good arrays and are considered to be different according to the definition in the statement.

In the third sample, an example of a good array is $ [1, 0, 1, 4, 2, 5, 4] $ . It can be rearranged to an array $ b = [1, 5, 0, 2, 4, 4, 1] $ which is a PalindORme because:

- $ \mathrm{OR}(1, 1) $ = $ \mathrm{OR}(7, 7) $ = $ 1 $
- $ \mathrm{OR}(1, 2) $ = $ \mathrm{OR}(6, 7) $ = $ 5 $
- $ \mathrm{OR}(1, 3) $ = $ \mathrm{OR}(5, 7) $ = $ 5 $
- $ \mathrm{OR}(1, 4) $ = $ \mathrm{OR}(4, 7) $ = $ 7 $
- $ \mathrm{OR}(1, 5) $ = $ \mathrm{OR}(3, 7) $ = $ 7 $
- $ \mathrm{OR}(1, 6) $ = $ \mathrm{OR}(2, 7) $ = $ 7 $
- $ \mathrm{OR}(1, 7) $ = $ \mathrm{OR}(1, 7) $ = $ 7 $

Here $ \mathrm{OR}(l, r) $ denotes $ b_{l} $ $ | $ $ b_{l+1}  $ $ | $ $  \ldots  $ $ | $ $  b_{r} $

## 样例 #1

### 输入

```
1 1 998244353
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 2 999999733
```

### 输出

```
40
```

## 样例 #3

### 输入

```
7 3 796735397
```

### 输出

```
1871528
```

## 样例 #4

### 输入

```
2 46 606559127
```

### 输出

```
177013
```



---

---
title: "Weighted Increasing Subsequences"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1621G
tag: ['动态规划 DP', '树状数组']
---

# Weighted Increasing Subsequences

## 题目描述

You are given the sequence of integers $ a_1, a_2, \ldots, a_n $ of length $ n $ .

The sequence of indices $ i_1 < i_2 < \ldots < i_k $ of length $ k $ denotes the subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ of length $ k $ of sequence $ a $ .

The subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ of length $ k $ of sequence $ a $ is called increasing subsequence if $ a_{i_j} < a_{i_{j+1}} $ for each $ 1 \leq j < k $ .

The weight of the increasing subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ of length $ k $ of sequence $ a $ is the number of $ 1 \leq j \leq k $ , such that exists index $ i_k < x \leq n $ and $ a_x > a_{i_j} $ .

For example, if $ a = [6, 4, 8, 6, 5] $ , then the sequence of indices $ i = [2, 4] $ denotes increasing subsequence $ [4, 6] $ of sequence $ a $ . The weight of this increasing subsequence is $ 1 $ , because for $ j = 1 $ exists $ x = 5 $ and $ a_5 = 5 > a_{i_1} = 4 $ , but for $ j = 2 $ such $ x $ doesn't exist.

Find the sum of weights of all increasing subsequences of $ a $ modulo $ 10^9+7 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains the single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the sequence $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the sequence $ a $ .

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the sum of weights of all increasing subsequences $ a $ modulo $ 10^9+7 $ .

## 说明/提示

In the first test case the following increasing subsequences of $ a $ have not zero weight:

- The weight of $ [a_1] = [6] $ is $ 1 $ .
- The weight of $ [a_2] = [4] $ is $ 1 $ .
- The weight of $ [a_2, a_3] = [4, 8] $ is $ 1 $ .
- The weight of $ [a_2, a_4] = [4, 6] $ is $ 1 $ .

 The sum of weights of increasing subsequences is $ 4 $ .In the second test case there are $ 7 $ increasing subsequences of $ a $ with not zero weight: $ 3 $ with weight $ 1 $ , $ 3 $ with weight $ 2 $ and $ 1 $ with weight $ 3 $ . The sum of weights is $ 12 $ .

## 样例 #1

### 输入

```
4
5
6 4 8 6 5
4
1 2 3 4
3
3 2 2
4
4 5 6 5
```

### 输出

```
4
12
0
6
```



---

---
title: "Fishingprince Plays With Array Again"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1696G
tag: ['动态规划 DP', '线段树', '线性规划']
---

# Fishingprince Plays With Array Again

## 题目描述

Suppose you are given a 1-indexed sequence $ a $ of non-negative integers, whose length is $ n $ , and two integers $ x $ , $ y $ . In consecutive $ t $ seconds ( $ t $ can be any positive real number), you can do one of the following operations:

- Select $ 1\le i<n $ , decrease $ a_i $ by $ x\cdot t $ , and decrease $ a_{i+1} $ by $ y\cdot t $ .
- Select $ 1\le i<n $ , decrease $ a_i $ by $ y\cdot t $ , and decrease $ a_{i+1} $ by $ x\cdot t $ .

Define the minimum amount of time (it might be a real number) required to make all elements in the sequence less than or equal to $ 0 $ as $ f(a) $ .

For example, when $ x=1 $ , $ y=2 $ , it takes $ 3 $ seconds to deal with the array $ [3,1,1,3] $ . We can:

- In the first $ 1.5 $ seconds do the second operation with $ i=1 $ .
- In the next $ 1.5 $ seconds do the first operation with $ i=3 $ .

We can prove that it's not possible to make all elements less than or equal to $ 0 $ in less than $ 3 $ seconds, so $ f([3,1,1,3])=3 $ .

Now you are given a 1-indexed sequence $ b $ of positive integers, whose length is $ n $ . You are also given positive integers $ x $ , $ y $ . Process $ q $ queries of the following two types:

- 1 k v: change $ b_k $ to $ v $ .
- 2 l r: print $ f([b_l,b_{l+1},\dots,b_r]) $ .

## 输入格式

The first line of input contains two integers $ n $ and $ q $ ( $ 2\le n\le 2\cdot 10^5 $ , $ 1\le q\le 2\cdot 10^5 $ ).

The second line of input contains two integers $ x $ and $ y $ ( $ 1\le x,y\le 10^6 $ ).

The third line of input contains $ n $ integers $ b_1,b_2,\ldots,b_n $ ( $ 1\le b_i\le 10^6 $ ).

This is followed by $ q $ lines. Each of these $ q $ lines contains three integers. The first integer $ op $ is either $ 1 $ or $ 2 $ .

- If it is $ 1 $ , it is followed by two integers $ k $ , $ v $ ( $ 1\le k\le n $ , $ 1\le v\le 10^6 $ ). It means that you should change $ b_k $ to $ v $ .
- If it is $ 2 $ , it is followed by two integers $ l $ , $ r $ ( $ 1\le l<r\le n $ ). It means that you should print $ f([b_l,b_{l+1},\dots,b_r]) $ .

## 输出格式

For each query of type $ 2 $ , print one real number — the answer to the query. Your answer is considered correct if its absolute error or relative error does not exceed $ 10^{-9} $ .

## 说明/提示

Let's analyse the sample.

In the first query, we are asked to compute $ f([3,1,1,4]) $ . The answer is $ 3.5 $ . One optimal sequence of operations is:

- In the first $ 1.5 $ seconds do the second operation with $ i=1 $ .
- In the next $ 2 $ seconds do the first operation with $ i=3 $ .

In the third query, we are asked to compute $ f([1,1,1]) $ . The answer is $ 1 $ . One optimal sequence of operations is:

- In the first $ 0.5 $ seconds do the second operation with $ i=1 $ .
- In the next $ 0.5 $ seconds do the first operation with $ i=2 $ .

## 样例 #1

### 输入

```
4 3
1 2
3 1 1 4
2 1 4
1 1 1
2 1 3
```

### 输出

```
3.500000000000000
1.000000000000000
```



---

---
title: "Maximum Product?"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1696H
tag: ['动态规划 DP']
---

# Maximum Product?

## 题目描述

You are given a positive integer $ k $ . For a multiset of integers $ S $ , define $ f(S) $ as the following.

- If the number of elements in $ S $ is less than $ k $ , $ f(S)=0 $ .
- Otherwise, define $ f(S) $ as the maximum product you can get by choosing exactly $ k $ integers from $ S $ .

More formally, let $ |S| $ denote the number of elements in $ S $ . Then,

- If $ |S|<k $ , $ f(S)=0 $ .
- Otherwise, $ f(S)=\max\limits_{T\subseteq S,|T|=k}\left(\prod\limits_{i\in T}i\right) $ .

You are given a multiset of integers, $ A $ . Compute $ \sum\limits_{B\subseteq A} f(B) $ modulo $ 10^9+7 $ .

Note that in this problem, we distinguish the elements by indices instead of values. That is, a multiset consisting of $ n $ elements always has $ 2^n $ distinct subsets regardless of whether some of its elements are equal.

## 输入格式

The first line of input contains two integers $ n $ and $ k $ , where $ n $ is the number of elements in $ A $ ( $ 1\le k\le n\le 600 $ ).

The second line of input contains $ n $ integers $ a_1,a_2,\dots,a_n $ , describing the elements in $ A $ ( $ -10^9\le a_i\le 10^9 $ ).

## 输出格式

Output $ \sum\limits_{B\subseteq A} f(B) $ modulo $ 10^9+7 $ .

## 说明/提示

Consider the first sample. From the definitions we know that

- $ f(\varnothing)=0 $
- $ f(\{-1\})=0 $
- $ f(\{2\})=0 $
- $ f(\{4\})=0 $
- $ f(\{-1,2\})=-2 $
- $ f(\{-1,4\})=-4 $
- $ f(\{2,4\})=8 $
- $ f(\{-1,2,4\})=8 $

So we should print $ (0+0+0+0-2-4+8+8)\bmod (10^9+7)=10 $ .

In the second example, note that although the multiset consists of three same values, it still has $ 8 $ distinct subsets: $ \varnothing,\{1\},\{1\},\{1\},\{1,1\},\{1,1\},\{1,1\},\{1,1,1\} $ .

## 样例 #1

### 输入

```
3 2
-1 2 4
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 1
1 1 1
```

### 输出

```
7
```

## 样例 #3

### 输入

```
10 4
-24 -41 9 -154 -56 14 18 53 -7 120
```

### 输出

```
225905161
```

## 样例 #4

### 输入

```
15 5
0 0 2 -2 2 -2 3 -3 -3 4 5 -4 -4 4 5
```

### 输出

```
18119684
```



---

---
title: "Bugaboo"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1707F
tag: ['动态规划 DP', '线段树']
---

# Bugaboo

## 题目描述

A transformation of an array of positive integers $ a_1,a_2,\dots,a_n $ is defined by replacing $ a $ with the array $ b_1,b_2,\dots,b_n $ given by $ b_i=a_i\oplus a_{(i\bmod n)+1} $ , where $ \oplus $ denotes the bitwise XOR operation.

You are given integers $ n $ , $ t $ , and $ w $ . We consider an array $ c_1,c_2,\dots,c_n $ ( $ 0 \le c_i \le 2^w-1 $ ) to be bugaboo if and only if there exists an array $ a_1,a_2,\dots,a_n $ such that after transforming $ a $ for $ t $ times, $ a $ becomes $ c $ .

For example, when $ n=6 $ , $ t=2 $ , $ w=2 $ , then the array $ [3,2,1,0,2,2] $ is bugaboo because it can be given by transforming the array $ [2,3,1,1,0,1] $ for $ 2 $ times:

 $ $$$ [2,3,1,1,0,1]\to [2\oplus 3,3\oplus 1,1\oplus 1,1\oplus 0,0\oplus 1,1\oplus 2]=[1,2,0,1,1,3]; \\ [1,2,0,1,1,3]\to [1\oplus 2,2\oplus 0,0\oplus 1,1\oplus 1,1\oplus 3,3\oplus 1]=[3,2,1,0,2,2].  $ $ </p><p>And the array  $ \[4,4,4,4,0,0\] $  is not bugaboo because  $ 4 &gt; 2^2 - 1 $ . The array  $ \[2,3,3,3,3,3\] $  is also not bugaboo because it can't be given by transforming one array for  $ 2 $  times.</p><p>You are given an array  $ c $  with some positions lost (only  $ m $  positions are known at first and the remaining positions are lost). And there are  $ q $  modifications, where each modification is changing a position of  $ c $ . A modification can possibly change whether the position is lost or known, and it can possibly redefine a position that is already given.</p><p>You need to calculate how many possible arrays  $ c $  (with arbitrary elements on the lost positions) are bugaboos after each modification. Output the  $ i $ -th answer modulo  $ p\_i $  ( $ p\_i $  is a given array consisting of  $ q$$$ elements).

## 输入格式

The first line contains four integers $ n $ , $ m $ , $ t $ and $ w $ ( $ 2\le n\le 10^7 $ , $ 0\le m\le \min(n, 10^5) $ , $ 1\le t\le 10^9 $ , $ 1\le w\le 30 $ ).

The $ i $ -th line of the following $ m $ lines contains two integers $ d_i $ and $ e_i $ ( $ 1\le d_i\le n $ , $ 0\le e_i< 2^w $ ). It means the position $ d_i $ of the array $ c $ is given and $ c_{d_i}=e_i $ . It is guaranteed that $ 1\le d_1<d_2<\ldots<d_m\le n $ .

The next line contains only one number $ q $ ( $ 1\le q\le 10^5 $ ) — the number of modifications.

The $ i $ -th line of the following $ q $ lines contains three integers $ f_i $ , $ g_i $ , $ p_i $ ( $ 1\le f_i\le n $ , $ -1\le g_i< 2^w $ , $ 11\le p_i\le 10^9+7 $ ). The value $ g_i=-1 $ means changing the position $ f_i $ of the array $ c $ to a lost position, otherwise it means changing the position $ f_i $ of the array $ c $ to a known position, and $ c_{f_i}=g_i $ . The value $ p_i $ means you need to output the $ i $ -th answer modulo $ p_i $ .

## 输出格式

The output contains $ q $ lines, denoting your answers.

## 说明/提示

In the first example, $ n=3 $ , $ t=1 $ , and $ w=1 $ . Let $ ? $ denote a lost position of $ c $ .

In the first query, $ c=[1,0,1] $ . The only possible array $ [1,0,1] $ is bugaboo because it can be given by transforming $ [0,1,1] $ once. So the answer is $ 1\bmod 123\,456\,789 = 1 $ .

In the second query, $ c=[1,1,1] $ . The only possible array $ [1,1,1] $ is not bugaboo. So the answer is $ 0\bmod 111\,111\,111 = 0 $ .

In the third query, $ c=[?,1,1] $ . There are two possible arrays $ [1,1,1] $ and $ [0,1,1] $ . Only $ [0,1,1] $ is bugaboo because it can be given by transforming $ [1,1,0] $ once. So the answer is $ 1\bmod 987\,654\,321=1 $ .

In the fourth query, $ c=[?,1,?] $ . There are four possible arrays. $ [0,1,1] $ and $ [1,1,0] $ are bugaboos. $ [1,1,0] $ can be given by performing $ [1,0,1] $ once. So the answer is $ 2\bmod 555\,555\,555=2 $ .

## 样例 #1

### 输入

```
3 2 1 1
1 1
3 1
4
2 0 123456789
2 1 111111111
1 -1 987654321
3 -1 555555555
```

### 输出

```
1
0
1
2
```

## 样例 #2

### 输入

```
24 8 5 4
4 4
6 12
8 12
15 11
16 7
20 2
21 9
22 12
13
2 13 11
3 15 12
5 7 13
9 3 14
10 5 15
11 15 16
13 14 17
14 1 18
18 9 19
19 6 20
23 10 21
24 8 22
21 13 23
```

### 输出

```
1
4
9
2
1
0
1
10
11
16
16
0
16
```



---

---
title: "Infinite Game"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1784E
tag: ['动态规划 DP', 'DP 套 DP']
---

# Infinite Game

## 题目描述

Alice and Bob are playing an infinite game consisting of sets. Each set consists of rounds. In each round, one of the players wins. The first player to win two rounds in a set wins this set. Thus, a set always ends with the score of $ 2:0 $ or $ 2:1 $ in favor of one of the players.

Let's call a game scenario a finite string $ s $ consisting of characters 'a' and 'b'. Consider an infinite string formed with repetitions of string $ s $ : $ sss \ldots $ Suppose that Alice and Bob play rounds according to this infinite string, left to right. If a character of the string $ sss \ldots $ is 'a', then Alice wins the round; if it's 'b', Bob wins the round. As soon as one of the players wins two rounds, the set ends in their favor, and a new set starts from the next round.

Let's define $ a_i $ as the number of sets won by Alice among the first $ i $ sets while playing according to the given scenario. Let's also define $ r $ as the limit of ratio $ \frac{a_i}{i} $ as $ i \rightarrow \infty $ . If $ r > \frac{1}{2} $ , we'll say that scenario $ s $ is winning for Alice. If $ r = \frac{1}{2} $ , we'll say that scenario $ s $ is tied. If $ r < \frac{1}{2} $ , we'll say that scenario $ s $ is winning for Bob.

You are given a string $ s $ consisting of characters 'a', 'b', and '?'. Consider all possible ways of replacing every '?' with 'a' or 'b' to obtain a string consisting only of characters 'a' and 'b'. Count how many of them result in a scenario winning for Alice, how many result in a tied scenario, and how many result in a scenario winning for Bob. Print these three numbers modulo $ 998\,244\,353 $ .

## 输入格式

The only line contains a single string $ s $ ( $ 1 \le |s| \le 200 $ ), consisting of characters 'a', 'b', and '?'.

## 输出格式

Print three integers: how many ways result in a scenario winning for Alice, how many result in a tied scenario, and how many result in a scenario winning for Bob, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, there are four ways to replace the question marks:

- $ s = \mathtt{aa} $ : Alice wins every set $ 2:0 $ — the scenario is winning for Alice;
- $ s = \mathtt{ab} $ : Alice and Bob win sets in turns, with the score of $ 2:1 $ each — the scenario is tied;
- $ s = \mathtt{ba} $ : Bob and Alice win sets in turns, with the score of $ 2:1 $ each — the scenario is tied;
- $ s = \mathtt{bb} $ : Bob wins every set $ 2:0 $ — the scenario is winning for Bob.

## 样例 #1

### 输入

```
??
```

### 输出

```
1
2
1
```

## 样例 #2

### 输入

```
?aa?b
```

### 输出

```
1
3
0
```

## 样例 #3

### 输入

```
a???ba
```

### 输出

```
4
3
1
```

## 样例 #4

### 输入

```
????????
```

### 输出

```
121
14
121
```

## 样例 #5

### 输入

```
ba????a?a???abbb?
```

### 输出

```
216
57
239
```

## 样例 #6

### 输入

```
a????a??????b??abbababbbb?a?aaa????bb
```

### 输出

```
97833
28387
135924
```

## 样例 #7

### 输入

```
??????????????a????????????????b?????
```

### 输出

```
484121060
448940322
484613337
```



---

---
title: "Graph Coloring (hard version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1792F2
tag: ['动态规划 DP', '图论', '组合数学', '快速数论变换 NTT']
---

# Graph Coloring (hard version)

## 题目描述

The only difference between the easy and the hard version is the constraint on $ n $ .

You are given an undirected complete graph on $ n $ vertices. A complete graph is a graph where each pair of vertices is connected by an edge. You have to paint the edges of the graph into two colors, red and blue (each edge will have one color).

A set of vertices $ S $ is red-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through red edges and vertices from $ S $ . Similarly, a set of vertices $ S $ is blue-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through blue edges and vertices from $ S $ .

You have to paint the graph in such a way that:

- there is at least one red edge;
- there is at least one blue edge;
- for each set of vertices $ S $ such that $ |S| \ge 2 $ , $ S $ is either red-connected or blue-connected, but not both.

Calculate the number of ways to paint the graph, and print it modulo $ 998244353 $ .

## 输入格式

The first (and only) line contains one integer $ n $ ( $ 3 \le n \le 5 \cdot 10^4 $ ).

## 输出格式

Print one integer — the number of ways to paint the graph, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
```

### 输出

```
50
```

## 样例 #3

### 输入

```
100
```

### 输出

```
878752271
```

## 样例 #4

### 输入

```
1337
```

### 输出

```
520628749
```

## 样例 #5

### 输入

```
42013
```

### 输出

```
906821221
```



---

---
title: "Maximum GCD Sum Queries"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1973F
tag: ['动态规划 DP', '数论']
---

# Maximum GCD Sum Queries

## 题目描述

For $ k $ positive integers $ x_1, x_2, \ldots, x_k $ , the value $ \gcd(x_1, x_2, \ldots, x_k) $ is the greatest common divisor of the integers $ x_1, x_2, \ldots, x_k $ — the largest integer $ z $ such that all the integers $ x_1, x_2, \ldots, x_k $ are divisible by $ z $ .

You are given three arrays $ a_1, a_2, \ldots, a_n $ , $ b_1, b_2, \ldots, b_n $ and $ c_1, c_2, \ldots, c_n $ of length $ n $ , containing positive integers.

You also have a machine that allows you to swap $ a_i $ and $ b_i $ for any $ i $ ( $ 1 \le i \le n $ ). Each swap costs you $ c_i $ coins.

Find the maximum possible value of $ $$$\gcd(a_1, a_2, \ldots, a_n) + \gcd(b_1, b_2, \ldots, b_n) $ $  that you can get by paying in total at most  $ d $  coins for swapping some elements. The amount of coins you have changes a lot, so find the answer to this question for each of the  $ q $  possible values  $ d\_1, d\_2, \\ldots, d\_q$$$.

## 输入格式

There are two integers on the first line — the numbers $ n $ and $ q $ ( $ 1 \leq n \leq 5 \cdot 10^5 $ , $ 1 \leq q \leq 5 \cdot 10^5 $ ).

On the second line, there are $ n $ integers — the numbers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^8 $ ).

On the third line, there are $ n $ integers — the numbers $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq 10^8 $ ).

On the fourth line, there are $ n $ integers — the numbers $ c_1, c_2, \ldots, c_n $ ( $ 1 \leq c_i \leq 10^9 $ ).

On the fifth line, there are $ q $ integers — the numbers $ d_1, d_2, \ldots, d_q $ ( $ 0 \leq d_i \leq 10^{15} $ ).

## 输出格式

Print $ q $ integers — the maximum value you can get for each of the $ q $ possible values $ d $ .

## 说明/提示

In the first query of the first example, we are not allowed to do any swaps at all, so the answer is $ \gcd(1, 2, 3) + \gcd(4, 5, 6) = 2 $ . In the second query, one of the ways to achieve the optimal value is to swap $ a_2 $ and $ b_2 $ , then the answer is $ \gcd(1, 5, 3) + \gcd(4, 2, 6) = 3 $ .

In the second query of the second example, it's optimal to perform swaps on positions $ 1 $ and $ 3 $ , then the answer is $ \gcd(3, 3, 6, 9, 3) + \gcd(8, 4, 4, 8, 4) = 7 $ and we have to pay $ 40 $ coins in total.

## 样例 #1

### 输入

```
3 4
1 2 3
4 5 6
1 1 1
0 1 2 3
```

### 输出

```
2 3 3 3
```

## 样例 #2

### 输入

```
5 5
3 4 6 8 4
8 3 4 9 3
10 20 30 40 50
5 55 13 1000 113
```

### 输出

```
2 7 3 7 7
```

## 样例 #3

### 输入

```
1 1
3
4
5
0
```

### 输出

```
7
```



---

---
title: "Mind Bloom"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1975I
tag: ['动态规划 DP']
---

# Mind Bloom

## 题目描述

This is the way it always was.



This is the way it always will be.



All will be forgotten again soon...



Jellyfish is playing a one-player card game called "Slay the Spire". There are $ n $ cards in total numbered from $ 1 $ to $ n $ . The $ i $ -th card has power $ c_i $ .

There is a binary string $ s $ of length $ n $ . If $ s_i = \texttt{0} $ , the $ i $ -th card is initially in the draw pile. If $ s_i = \texttt{1} $ , the $ i $ -th card is initially in Jellyfish's hand.

Jellyfish will repeat the following process until either her hand or the draw pile is empty.

1. Let $ x $ be the power of the card with the largest power in her hand.
2. Place a single card with power $ x $ back into the draw pile.
3. Randomly draw $ x $ cards from the draw pile. All subsets of $ x $ cards from the draw pile have an equal chance of being drawn. If there are fewer than $ x $ cards in the draw pile, Jellyfish will draw all cards.

At the end of this process, find the probability that Jellyfish can empty the draw pile, modulo $ 1\,000\,000\,007 $ .

Formally, let $ M=1\,000\,000\,007 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\leq t\leq 100 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 120 $ ) — the number of cards.

The second line of each test case contains $ n $ integers $ c_1,c_2,\ldots,c_n $ ( $ 0 \leq c_i \leq n $ ) — the powers of the cards. It is guaranteed that $ c_1 \leq c_2 \leq \ldots \leq c_n $ .

The third line of each test case contains a binary string $ s $ of length $ n $ . If $ s_i = \texttt{0} $ , the $ i $ -th card is initially in the draw pile. If $ s_i = \texttt{1} $ , the $ i $ -th card is initially in Jellyfish's hand.

It is guaranteed that the sum of $ n^2 $ over all test cases does not exceed $ 120^2 $ .

## 输出格式

For each test case, output the probability that Jellyfish can empty the draw pile modulo $ 1\,000\,000\,007 $ .

## 说明/提示

In the first test case, Jellyfish will keep playing cards with power $ 1 $ until Jellyfish draws a card with power $ 0 $ or power $ 2 $ . If Jellyfish draws a card with power $ 0 $ , she will eventually empty her hand. If Jellyfish draws a card with power $ 2 $ , she will eventually empty the draw pile. Since there is an equal chance of drawing $ 0 $ or $ 2 $ , the answer is $ \frac{1}{2} $ , and $ 2 \cdot 500\,000\,004 \equiv 1 \pmod {10^9+7} $

## 样例 #1

### 输入

```
4
5
0 1 1 1 2
00100
3
2 3 3
000
10
0 0 0 0 0 0 0 1 1 1
1111011111
20
0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 2 3 3 4
00000000001000101010
```

### 输出

```
500000004
0
0
675898154
```



---

---
title: "Tower Capturing"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1984H
tag: ['动态规划 DP']
---

# Tower Capturing

## 题目描述

There are $ n $ towers at $ n $ distinct points $ (x_1, y_1), (x_2, y_2), \ldots, (x_n, y_n) $ , such that no three are collinear and no four are concyclic. Initially, you own towers $ (x_1, y_1) $ and $ (x_2, y_2) $ , and you want to capture all of them. To do this, you can do the following operation any number of times:

- Pick two towers $ P $ and $ Q $ you own and one tower $ R $ you don't own, such that the circle through $ P $ , $ Q $ , and $ R $ contains all $ n $ towers inside of it.
- Afterwards, capture all towers in or on triangle $ \triangle PQR $ , including $ R $ itself.

 An attack plan is a series of choices of $ R $ ( $ R_1, R_2, \ldots, R_k $ ) using the above operations after which you capture all towers. Note that two attack plans are considered different only if they differ in their choice of $ R $ in some operation; in particular, two attack plans using the same choices of $ R $ but different choices of $ P $ and $ Q $ are considered the same.Count the number of attack plans of minimal length. Note that it might not be possible to capture all towers, in which case the answer is $ 0 $ .

Since the answer may be large, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 250 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 4 \leq n \leq 100 $ ) — the number of towers.

The $ i $ -th of the next $ n $ lines contains two integers $ x_i $ and $ y_i $ ( $ -10^4 \leq x_i, y_i \leq 10^4 $ ) — the location of the $ i $ -th tower. Initially, you own towers $ (x_1, y_1) $ and $ (x_2, y_2) $ .

All towers are at distinct locations, no three towers are collinear, and no four towers are concyclic.

The sum of $ n $ over all test cases does not exceed $ 1000 $ .

## 输出格式

For each test case, output a single integer — the number of attack plans of minimal length after which you capture all towers, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, there is only one possible attack plan of shortest length, shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1984H/4db430879d9ca247997fc2913e9569a1772c78ba.png)- Use the operation with $ P = $ tower $ 1 $ , $ Q = $ tower $ 2 $ , and $ R = $ tower $ 5 $ . The circle through these three towers contains all towers inside of it, and as a result towers $ 3 $ and $ 5 $ are captured.
- Use the operation with $ P = $ tower $ 5 $ , $ Q = $ tower $ 1 $ , and $ R = $ tower $ 4 $ . The circle through these three towers contains all towers inside of it, and as a result tower $ 4 $ is captured.

In the second case, for example, you can never capture the tower at $ (3, 10\,000) $ .

## 样例 #1

### 输入

```
3
5
1 1
2 5
3 3
4 2
5 4
6
1 1
3 3
1 2
2 1
3 10000
19 84
7
2 7
-4 -3
-3 6
3 1
-5 2
1 -4
-1 7
```

### 输出

```
1
0
10
```



---

---
title: "Spinning Round (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1987G2
tag: ['动态规划 DP', '笛卡尔树']
---

# Spinning Round (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions are the allowed characters in $ s $ . You can make hacks only if both versions of the problem are solved.

You are given a permutation $ p $ of length $ n $ . You are also given a string $ s $ of length $ n $ , where each character is either L, R, or ?.

For each $ i $ from $ 1 $ to $ n $ :

- Define $ l_i $ as the largest index $ j < i $ such that $ p_j > p_i $ . If there is no such index, $ l_i := i $ .
- Define $ r_i $ as the smallest index $ j > i $ such that $ p_j > p_i $ . If there is no such index, $ r_i := i $ .

Initially, you have an undirected graph with $ n $ vertices (numbered from $ 1 $ to $ n $ ) and no edges. Then, for each $ i $ from $ 1 $ to $ n $ , add one edge to the graph:

- If $ s_i = $ L, add the edge $ (i, l_i) $ to the graph.
- If $ s_i = $ R, add the edge $ (i, r_i) $ to the graph.
- If $ s_i = $ ?, either add the edge $ (i, l_i) $ or the edge $ (i, r_i) $ to the graph at your choice.

Find the maximum possible diameter over all connected $ ^{\text{∗}} $ graphs that you can form. Output $ -1 $ if it is not possible to form any connected graphs.

 $ ^{\text{∗}} $ Let $ d(s, t) $ denote the smallest number of edges on any path between $ s $ and $ t $ .

The diameter of the graph is defined as the maximum value of $ d(s, t) $ over all pairs of vertices $ s $ and $ t $ .

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 4 \cdot 10^5 $ ) — the length of the permutation $ p $ .

The second line of each test case contains $ n $ integers $ p_1,p_2,\ldots, p_n $ ( $ 1 \le p_i \le n $ ) — the elements of $ p $ , which are guaranteed to form a permutation.

The third line of each test case contains a string $ s $ of length $ n $ . It is guaranteed that it consists only of the characters L, R, and ?.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 4 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum possible diameter over all connected graphs that you form, or $ -1 $ if it is not possible to form any connected graphs.

## 说明/提示

In the first test case, there are two connected graphs (the labels are indices):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1987G2/b9e604b93005a6fc948b7a3b538eda48ad94326a.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1987G2/1015454202f1913e51db8d5cb7f5b2c4acb62524.png)The graph on the left has a diameter of $ 2 $ , while the graph on the right has a diameter of $ 3 $ , so the answer is $ 3 $ .

In the second test case, there are no connected graphs, so the answer is $ -1 $ .

## 样例 #1

### 输入

```
8
5
2 1 4 3 5
R?RL?
2
1 2
LR
3
3 1 2
L?R
7
5 3 1 6 4 2 7
?R?R?R?
5
5 2 1 3 4
?????
6
6 2 3 4 5 1
?LLRLL
8
1 7 5 6 2 8 4 3
?R??????
12
6 10 7 1 8 5 12 2 11 3 4 9
????????????
```

### 输出

```
3
-1
-1
4
4
3
5
8
```



---

---
title: "Counting 101"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2002H
tag: ['动态规划 DP', '动态规划优化', 'DP 套 DP']
---

# Counting 101

## 题目描述

### 题目背景

夏日漫长，蝉鸣不断，酷暑难耐。终于，它落下了帷幕。决战已过，大门敞开，只留下一阵轻风。

你的前辈们已经完成了最后的鞠躬，轮到你上场了。


在整理留下的一些笔记时，你发现了一份名为 **问题 101** 的奇怪声明：

- 给定一个正整数序列 $a_1,a_2,\ldots,a_n$，你可以对它进行任意次操作。在一次操作中，你可以选择连续的三个元素 $a_i,a_{i+1},a_{i+2}$，并将它们合并为一个元素 $\max(a_i+1,a_{i+1},a_{i+2}+1)$。请计算在不产生大于 $m$ 的元素的前提下，最多可以进行多少次操作。

经过思考，你决定提出下面这个问题，命名为 **计算 101**：

- 给定 $n$ 和 $m$。对于每一个 $k=0,1,\ldots,\left\lfloor\frac{n-1}{2}\right\rfloor$，求元素在 $[1, m]$ 中的整数序列 $a_1,a_2,\ldots,a_n$ 的个数，使得作为 **问题 101** 的输入时，答案是 $k$。由于答案可能非常大，只需要输出对 $10^9+7$ 的结果即可。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1\le t\le10^3$ ) 。测试用例说明如下。

每个测试用例的唯一一行包含两个整数 $n$ , $m$ ( $1\le n\le 130$ , $1\le m\le 30$ )。

## 输出格式

对于每个测试用例，输出 $\left\lfloor\frac{n+1}{2}\right\rfloor$ 个数字。第 $i$ 个数字是有效序列的个数，满足这些序列作为 **问题 101** 的输入时，答案为 $i-1$，对 $10^9+7$ 取模。

### 样例解释

对于第一组数据，共有 $2^3=8$ 种合法数组。其中 $[1,2,1]$ 与 $[1,1,1]$ 可操作一次，余下 $6$ 个数组无法操作。

## 样例 #1

### 输入

```
2
3 2
10 10
```

### 输出

```
6 2 
1590121 23399118 382293180 213020758 379696760
```



---

---
title: "Substring Compression"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2004G
tag: ['动态规划 DP', '矩阵乘法', '双指针 two-pointer']
---

# Substring Compression

## 题目描述

Let's define the operation of compressing a string $ t $ , consisting of at least $ 2 $ digits from $ 1 $ to $ 9 $ , as follows:

- split it into an even number of non-empty substrings — let these substrings be $ t_1, t_2, \dots, t_m $ (so, $ t = t_1 + t_2 + \dots + t_m $ , where $ + $ is the concatenation operation);
- write the string $ t_2 $ $ t_1 $ times, then the string $ t_4 $ $ t_3 $ times, and so on.

For example, for a string "12345", one could do the following: split it into ("1", "23", "4", "5"), and write "235555".

Let the function $ f(t) $ for a string $ t $ return the minimum length of the string that can be obtained as a result of that process.

You are given a string $ s $ , consisting of $ n $ digits from $ 1 $ to $ 9 $ , and an integer $ k $ . Calculate the value of the function $ f $ for all contiguous substrings of $ s $ of length exactly $ k $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2 \le k \le n \le 2 \cdot 10^5 $ ).

The second line contains the string $ s $ ( $ |s| = n $ ), consisting only of digits from $ 1 $ to $ 9 $ .

## 输出格式

Output $ n - k + 1 $ integers — $ f(s_{1,k}), f(s_{2,k+1}), \dots, f(s_{n - k + 1, n}) $ .

## 样例 #1

### 输入

```
4 4
5999
```

### 输出

```
14
```

## 样例 #2

### 输入

```
10 3
1111111111
```

### 输出

```
2 2 2 2 2 2 2 2
```

## 样例 #3

### 输入

```
11 4
49998641312
```

### 输出

```
12 18 17 15 12 7 7 2
```



---

---
title: "Simurgh's Watch (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2034G1
tag: ['动态规划 DP', '贪心', '构造']
---

# Simurgh's Watch (Easy Version)

## 题目描述

传说中，神鸟 [Simurgh](https://www.eavartravel.com/blog/2023/11/3/140727/simurgh/) 需要监管大片土地，她召集了 $ n $ 名警惕的战士帮忙。每个战士在特定的时间段内保持警戒，这个时间段用 $ [l_i, r_i] $ 表示，其中 $ l_i $ 和 $ r_i $ 分别为开始和结束时间，都是包含在内的正整数。

![](https://espresso.codeforces.com/e448e919c3f03a9c212cd45c8dcd8e2bb0be579c.webp)然而，Simurgh 的顾问 [Zal](https://asia-archive.si.edu/learn/shahnama/zal-and-the-simurgh/) 担心，如果多个战士在同一时间值守且都穿着相同颜色的衣服，会造成混淆。因此，为了防止这种情况发生，在任何时刻（可以是非整数时间）的战士中，至少要有一种颜色是由恰好一个战士穿着的。

我们的任务是：确定需要的最少颜色数，并为每个战士的时间段 $ [l_i, r_i] $ 分配一种颜色 $ c_i $，使得无论在哪一个时间 $ t $（被某个时间段包含在内），至少有一种颜色只出现在一个战士上。

## 输入格式

第一行包含一个整数 $ t $ （$ 1 \leq t \leq 10^4 $）——表示测试用例的数目。

每个测试用例包含以下内容：

- 第一行是一个整数 $ n $ （$ 1 \leq n \leq 2 \cdot 10^5 $）——表示 Simurgh 派出的战士数量。
- 接下来的 $ n $ 行中，每行包含两个整数 $ l_i $ 和 $ r_i $ （$ 1 \leq l_i \leq r_i \leq 10^9 $）——分别表示第 $ i $ 个战士的值班开始和结束时间。

所有测试用例中 $ n $ 的总和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对于每个测试用例：

- 首先输出要使用的最少的颜色数量 $ k $。
- 接下来输出一行 $ n $ 个整数 $ c_i $（$ 1 \leq c_i \leq k $），代表为第 $ i $ 位战士分配的颜色。

## 说明/提示

可以将每个战士的值班时间段视作 X 轴上的一个区间：

- 在测试用例 1 中，有两个彼此不重叠的区间，因此可用相同颜色。
- 在测试用例 2 中，时间点 2 是公共的，因此不能使用相同颜色。
- 在测试用例 3 中，区间可以按下图所示进行着色：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G1/dd56c79752790418adde70ef7aa40c52b2f8834f.png)

- 在测试用例 4 中，区间的着色方式如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G1/7c7aad3a3ba91ddaff1d673e62791383c4f77dec.png)

- 在测试用例 5 中，区间着色如下图所示。右侧图是错误的着色示例；在时间点 $ 5.5 $ 时，没有唯一颜色：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G1/b8f2a4852b6af3f78d2729a80e0ad7497e55682a.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
1 2
3 4
2
1 2
2 3
3
1 4
2 5
3 6
5
1 4
2 8
3 7
5 10
6 9
5
1 5
2 6
3 7
4 7
6 7
```

### 输出

```
1
1 1
2
1 2
2
1 2 1
3
2 3 1 2 1
3
2 1 3 1 1
```



---

---
title: "Simurgh's Watch (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2034G2
tag: ['动态规划 DP', '贪心', '构造']
---

# Simurgh's Watch (Hard Version)

## 题目描述

传说中的神鸟 Simurgh 负责守护一片辽阔的土地，她为此招募了 $n$ 名机敏的战士。每位战士都需要在特定的时间段 $[l_i, r_i]$ 内保持警戒，其中 $l_i$ 代表起始时间（包含），$r_i$ 代表结束时间（包含），两者均为正整数。

Simurgh 信任的顾问 Zal 担心，如果多个战士同时在岗且都穿着相同的颜色，那么他们之间可能会难以区分，从而导致混乱。为解决这一问题，在每个整数时刻 $t$，如果有多个战士在岗，必须确保至少有一种颜色仅被其中一个战士穿着。

任务是找出所需的最少颜色数量，并为每个战士的时间段 $[l_i, r_i]$ 分配一种颜色 $c_i$，使得对于包含在至少一个时间段内的每个整数时间点 $t$，总有一种颜色只被一个时间段在$t$时刻使用。

## 输入格式

第一行输入一个整数 $t$（$1 \leq t \leq 10^4$），表示测试用例的数量。

对于每个测试用例：

- 第一行包含一个整数 $n$（$1 \leq n \leq 2 \cdot 10^5$），表示 Simurgh 招募的战士数量。
- 随后的 $n$ 行中，每行包含两个整数 $l_i$ 和 $r_i$（$1 \leq l_i \leq r_i \leq 10^9$），表示第 $i$ 位战士的警戒时间段。

所有测试用例中的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例：

- 输出所需的最少颜色数量 $k$。
- 接下来输出一行，包括 $n$ 个整数 $c_i$（$1 \leq c_i \leq k$），每个 $c_i$ 表示分配给第 $i$ 位战士的颜色。

## 说明/提示

我们可以将每位战士的警戒时间段看作 X 轴上的一个区间。

以下示例展示了如何为各个测试用例的区间着色（区域只有在某时间点，仅某种颜色出现时该区域才被染色）：

- 测试用例 1：

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G2/a8ca04e863ed852cb4b11c3982c1d5442199b24b.png)

- 测试用例 2：

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G2/36f2a5d9878f69668f835178da7df8642bec8342.png)

- 测试用例 3：

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G2/75559577acf19732a5a59981d3806145e52c5ed5.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
5
1 4
2 8
3 7
5 10
6 9
5
1 5
2 6
3 7
4 7
6 7
5
4 9
8 17
2 15
12 19
6 13
```

### 输出

```
2
1 2 2 1 2
2
1 2 2 2 1
3
1 1 2 3 1
```



---

---
title: "Go Learn! (Easy Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2035G1
tag: ['动态规划 DP', '二分']
---

# Go Learn! (Easy Version)

## 题目描述

The differences between the easy and hard versions are the constraints on $ n $ and the sum of $ n $ . In this version, $ n \leq 3000 $ and the sum of $ n $ does not exceed $ 10^4 $ . You can only make hacks if both versions are solved.

Well, well, well, let's see how Bessie is managing her finances. She seems to be in the trenches! Fortunately, she is applying for a job at Moogle to resolve this issue. Moogle interviews require intensive knowledge of obscure algorithms and complex data structures, but Bessie received a tip-off from an LGM on exactly what she has to go learn.

Bessie wrote the following code to binary search for a certain element $ k $ in a possibly unsorted array $ [a_1, a_2,\ldots,a_n] $ with $ n $ elements.

```
<pre class="lstlisting">```
let l = 1<br></br>let h = n<br></br><br></br>while l < h:<br></br>  let m = floor((l + h) / 2)<br></br><br></br>  if a[m] < k:<br></br>    l = m + 1<br></br>  else:<br></br>    h = m<br></br><br></br>return l<br></br>
```
```

Bessie submitted her code to Farmer John's problem with $ m $ ( $ 1 \leq m \leq n $ ) tests. The $ i $ -th test is of the form $ (x_i, k_i) $ ( $ 1 \leq x, k \leq n $ ). It is guaranteed all the $ x_i $ are distinct and all the $ k_i $ are distinct.

Test $ i $ is correct if the following hold:

1. The $ x_i $ -th element in the array is $ k_i $ .
2. If Bessie calls the binary search as shown in the above code for $ k_i $ , it will return $ x_i $ .

It might not be possible for all $ m $ tests to be correct on the same array, so Farmer John will remove some of them so Bessie can AC. Let $ r $ be the minimum of tests removed so that there exists an array $ [a_1, a_2,\ldots,a_n] $ with $ 1 \leq a_i \leq n $ so that all remaining tests are correct.

In addition to finding $ r $ , Farmer John wants you to count the number of arrays $ [a_1, a_2,\ldots,a_n] $ with $ 1 \leq a_i \leq n $ such that there exists a way to remove exactly $ r $ tests so that all the remaining tests are correct. Since this number may be very large, please find it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \leq m \leq n \leq 3000 $ ) denoting the number of the array and the number of tests.

The following $ m $ lines each contain two integers, describing the tests. The $ i $ -th line contains two integers $ x_i $ and $ k_i $ ( $ 1 \leq x_i, k_i \leq n $ ) denoting the index and value of the test. It is guaranteed all $ x_i $ are distinct and all $ k_i $ are distinct.

It is guaranteed the sum of $ n $ across all test cases does not exceed $ 10^4 $ .

## 输出格式

For each test case, output two integers, $ r $ — the minimum of tests removed so that there exists an array so that all remaining tests are correct, and the number of arrays such that it is possible to remove $ r $ tests to make all remaining tests correct modulo $ 998\,244\,353 $ .

## 说明/提示

Consider the first example.

In the first test case, the array $ [1,2,2,3,4] $ satisfies all $ m $ tests, so the minimum number of tests Bessie has to remove is $ 0 $ . Note that this is also the only array that satisfies all $ m $ tests.

In the second test case, the minimum number of tests Bessie has to remove is $ 1 $ . The only test Bessie can remove is $ (2,5) $ . If Bessie removes test $ (2,5) $ , then the arrays satisfying the remaining $ m-1 $ tests are $ [2,2,3,1,4] $ , $ [2,2,3,2,4] $ , $ [2,2,3,3,4] $ .

## 样例 #1

### 输入

```
2
5 4
1 1
2 2
4 3
5 4
5 4
5 4
2 5
1 2
3 3
```

### 输出

```
0 1
1 3
```

## 样例 #2

### 输入

```
2
6 6
1 3
2 5
3 1
4 2
5 4
6 6
30 8
19 22
6 12
12 1
28 27
3 4
14 25
29 14
11 15
```

### 输出

```
3 78
3 839271911
```



---

---
title: "Go Learn! (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2035G2
tag: ['动态规划 DP', '二分', '动态规划优化']
---

# Go Learn! (Hard Version)

## 题目描述

The differences between the easy and hard versions are the constraints on $ n $ and the sum of $ n $ . In this version, $ n \leq 3\cdot 10^5 $ and the sum of $ n $ does not exceed $ 10^6 $ . You can only make hacks if both versions are solved.

Well, well, well, let's see how Bessie is managing her finances. She seems to be in the trenches! Fortunately, she is applying for a job at Moogle to resolve this issue. Moogle interviews require intensive knowledge of obscure algorithms and complex data structures, but Bessie received a tip-off from an LGM on exactly what she has to go learn.

Bessie wrote the following code to binary search for a certain element $ k $ in a possibly unsorted array $ [a_1, a_2,\ldots,a_n] $ with $ n $ elements.

```
<pre class="lstlisting">```
let l = 1<br></br>let h = n<br></br><br></br>while l < h:<br></br>  let m = floor((l + h) / 2)<br></br><br></br>  if a[m] < k:<br></br>    l = m + 1<br></br>  else:<br></br>    h = m<br></br><br></br>return l<br></br>
```
```

Bessie submitted her code to Farmer John's problem with $ m $ ( $ 1 \leq m \leq n $ ) tests. The $ i $ -th test is of the form $ (x_i, k_i) $ ( $ 1 \leq x, k \leq n $ ). It is guaranteed all the $ x_i $ are distinct and all the $ k_i $ are distinct.

Test $ i $ is correct if the following hold:

1. The $ x_i $ -th element in the array is $ k_i $ .
2. If Bessie calls the binary search as shown in the above code for $ k_i $ , it will return $ x_i $ .

It might not be possible for all $ m $ tests to be correct on the same array, so Farmer John will remove some of them so Bessie can AC. Let $ r $ be the minimum of tests removed so that there exists an array $ [a_1, a_2,\ldots,a_n] $ with $ 1 \leq a_i \leq n $ so that all remaining tests are correct.

In addition to finding $ r $ , Farmer John wants you to count the number of arrays $ [a_1, a_2,\ldots,a_n] $ with $ 1 \leq a_i \leq n $ such that there exists a way to remove exactly $ r $ tests so that all the remaining tests are correct. Since this number may be very large, please find it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \leq m \leq n \leq 3 \cdot 10^5 $ ) denoting the number of the array and the number of tests.

The following $ m $ lines each contain two integers, describing the tests. The $ i $ -th line contains two integers $ x_i $ and $ k_i $ ( $ 1 \leq x_i, k_i \leq n $ ) denoting the index and value of the test. It is guaranteed all $ x_i $ are distinct and all $ k_i $ are distinct.

It is guaranteed the sum of $ n $ across all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output two integers, $ r $ — the minimum of tests removed so that there exists an array so that all remaining tests are correct, and the number of arrays such that it is possible to remove $ r $ tests to make all remaining tests correct modulo $ 998\,244\,353 $ .

## 说明/提示

Consider the first example.

In the first test case, the array $ [1,2,2,3,4] $ satisfies all $ m $ tests, so the minimum number of tests Bessie has to remove is $ 0 $ . Note that this is also the only array that satisfies all $ m $ tests.

In the second test case, the minimum number of tests Bessie has to remove is $ 1 $ . The only test Bessie can remove is $ (2,5) $ . If Bessie removes test $ (2,5) $ , then the arrays satisfying the remaining $ m-1 $ tests are $ [2,2,3,1,4] $ , $ [2,2,3,2,4] $ , $ [2,2,3,3,4] $ .

## 样例 #1

### 输入

```
2
5 4
1 1
2 2
4 3
5 4
5 4
5 4
2 5
1 2
3 3
```

### 输出

```
0 1
1 3
```

## 样例 #2

### 输入

```
3
6 6
1 3
2 5
3 1
4 2
5 4
6 6
30 8
19 22
6 12
12 1
28 27
3 4
14 25
29 14
11 15
300000 1
5 10
```

### 输出

```
3 78
3 839271911
0 702730519
```



---

---
title: "Trophic Balance Species"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2041K
tag: ['动态规划 DP', '强连通分量']
---

# Trophic Balance Species

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041K/3f57ffd2f2e31a820fdb012c2016af22cc748377.png) 图像由 ChatGPT 4o 生成。在一项跨学科的合作中，一位生态系统科学家与一位计算机科学家联手，通过计算方法分析复杂生态系统的结构。生态系统科学家将整个系统建模成一个有向图 $D = (V, A)$，其中每个物种用一个节点 $v \in V$ 表示，每一对捕食关系由从被捕食者 $x$ 到捕食者 $y$ 的有向边 $(x, y) \in A$ 表示。这种图的结构可以用来模拟生态系统中能量在不同物种间的流动。

在这个系统中，有两个重要概念：

- **独立营养群**：如果集合 $S$ 中的任何物种 $x \in S$ 无法通过一系列有向捕食关系到达集合 $S$ 中的其他物种 $y \in S$（其中 $y \ne x$），那么这个集合 $S$ 就是一个独立营养群，即从 $x$ 到 $y$ 没有有向路径。

- **营养平衡物种**：一个物种如果它受到的影响来自直接或间接捕食者的数量（可以通过有向路径到达的物种，不包括自身）和来自直接或间接被捕食者的数量（可以通过有向路径达到该物种，不包括自身）之间的差值在所有物种中最小，就称为营养平衡物种。

考虑一个含有 $n = 4$ 个物种和 $m = 3$ 条捕食关系的生态系统：

- 物种 1：草（节点 1）
- 物种 2：兔子（节点 2）
- 物种 3：狐狸（节点 3）
- 物种 4：鹰（节点 4）

捕食关系用以下有向边表示：

- $(1, 2)$：草被兔子吃掉。
- $(2, 3)$：兔子被狐狸吃掉。
- $(2, 4)$：兔子也被鹰吃掉。

现在，考虑集合 $S = \{3, 4\}$（狐狸和鹰）。在节点 3（狐狸）和节点 4（鹰）之间没有有向路径；狐狸无法到达鹰，而鹰也无法到达狐狸。因此，这个集合符合独立营养群的定义。

接下来看各物种情况：

- 物种 1（草）：
  - 能到达的物种数：3（兔子、狐狸、鹰）
  - 能被到达的物种数：0（无）
  - 绝对差值：$|3 - 0| = 3$

- 物种 2（兔子）：
  - 能到达的物种数：2（狐狸、鹰）
  - 能被到达的物种数：1（草）
  - 绝对差值：$|2 - 1| = 1$

- 物种 3（狐狸）：
  - 能到达的物种数：0（无）
  - 能被到达的物种数：2（来自草和兔子）
  - 绝对差值：$|0 - 2| = 2$

- 物种 4（鹰）：
  - 能到达的物种数：0（无）
  - 能被到达的物种数：2（来自草和兔子）
  - 绝对差值：$|0 - 2| = 2$

在这些物种中，兔子的绝对差值最小，为 1，因此，兔子被认为是该生态系统的营养平衡物种。

题目已知生态系统中任何独立营养群的大小最多为 $k$。你的任务是找到生态系统中所有的营养平衡物种。

## 输入格式

第一行包含两个整数 $n$ 和 $m$，其中 $n$ 代表节点数，$m$ 代表边数。这些节点是编号为 $1, 2, \ldots, n$ 的物种。接下来的 $m$ 行，每一行包含两个整数 $x_i$ 和 $y_i$，表示有一条从节点 $x_i$ 指向节点 $y_i$ 的有向边。

- $1 \le n \le 2 \times 10^5$
- $0 \le m \le \min\{n(n-1), 4 \times 10^5\}$
- $k$ 不是输入数据，但保证 $1 \le k \le 16$
- 对于每一个 $i$（$1 \le i \le m$），$1 \le x_i, y_i \le n$ 且 $x_i \ne y_i$
- 在输入中，任意有序对 $(x_i, y_i)$ 最大只出现一次

## 输出格式

在一行上输出所有营养平衡物种的节点编号，��升序排列。节点编号之间用空格分隔。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4 3
1 2
2 3
2 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 5
1 2
1 3
1 4
2 3
3 2
```

### 输出

```
2 3 4
```



---

---
title: "Aquatic Dragon"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2045D
tag: ['动态规划 DP', '线段树']
---

# Aquatic Dragon

## 题目描述

你居住在一个由 $N$ 个岛屿组成的群岛中，这些岛屿排列成一条直线。岛屿从 $1$ 开始依次编号到 $N$。相邻的岛屿 $i$ 和 $i+1$ 之间有单向水下隧道：一条从岛 $i$ 到 $i+1$，另一条反向。而每条隧道只能走一次。

你和一条龙同行。龙的耐力以非负整数表示，用来施展游泳和飞行能力。初始时，其耐力为 $0$。

每个岛上都有一个魔法神社，当你第一次到达某岛时，会立即将龙的耐力增加 $P_i$（无论龙身处何地）。这个过程无需时间。

在某个岛上，你可以做以下三种移动：

- 如果你和你的龙在同一岛上，可以让龙游到相邻岛屿，前提是龙的耐力至少是 $D$。该操作会消耗耐力 $D$，耗时 $T_s$ 秒。
- 如果你和你的龙在同一岛上，可以让龙飞到相邻岛屿，前提是龙的耐力不为零。此举会将耐力归零，耗时 $T_f$ 秒。
- 你可以单独通过水下隧道步行到相邻岛屿，这需要花费 $T_w$ 秒。一旦你通过这条隧道，就不能再次使用。

请注意，游泳和飞行时不使用隧道。

你和龙当前在岛屿 $1$ 上。你的任务是带着龙到达岛屿 $N$，请计算出任务完成的最短时间。

## 输入格式

第一行包含五个整数 $N$、$D$、$T_s$、$T_f$ 和 $T_w$，其中 $2 \leq N \leq 200,000$，$1 \leq D, T_s, T_f, T_w \leq 200,000$。  
第二行包含 $N$ 个整数 $P_i$，满足 $1 \leq P_i \leq 200,000$。

## 输出格式

输出一个整数，为到达岛屿 $N$ 的最短时间。

## 说明/提示

### 示例解释 #1

以下是完成任务的最短事件序列：

1. 在岛 $1$ 的神社将龙的耐力增加到 $1$。
2. 带龙飞到岛 $2$，神社令龙的耐力增至 $2$。
3. 单独走到岛 $3$，神社令龙的耐力增至 $6$。
4. 单独走到岛 $4$，神社令龙的耐力增至 $8$。
5. 单独走回岛 $3$。
6. 单独走回岛 $2$。
7. 带龙游回岛 $3$，此时龙的耐力为 $4$。
8. 带龙游到岛 $4$，此时龙的耐力为 $0$。
9. 单独走到岛 $5$，神社令龙的耐力增至 $1$。
10. 单独走回岛 $4$。
11. 带龙飞到岛 $5$。

### 示例解释 #2

对于 $1 \leq i < 5$，重复以下过程：在岛 $i$ 的神社增加龙的耐力，然后带龙飞到岛 $i+1$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5 4 2 9 1
1 2 4 2 1
```

### 输出

```
28
```

## 样例 #2

### 输入

```
5 4 2 1 1
1 2 4 2 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3 4 2 10 1
3 1 2
```

### 输出

```
16
```



---

---
title: "Yandex Cuneiform (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2046F2
tag: ['动态规划 DP', '动态规划优化', '凸包']
---

# Yandex Cuneiform (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in this version, there is no restriction on the number of question marks. You can hack only if you solved all versions of this problem.

For a long time, no one could decipher Sumerian cuneiform. However, it has finally succumbed to pressure! Today, you have the chance to decipher Yandex cuneiform.

Yandex cuneiform is defined by the following rules:

1. An empty string is a Yandex cuneiform.
2. If you insert exactly one copy of each of the three letters 'Y', 'D', and 'X' into a Yandex cuneiform in such a way that no two adjacent letters become equal after the operation, you obtain a Yandex cuneiform.
3. If a string can't be obtained using the above rules, it is not a Yandex cuneiform.

You are given a template. A template is a string consisting of the characters 'Y', 'D', 'X', and '?'.

You need to check whether there exists a way to replace each question mark with 'Y', 'D', or 'X' to obtain a Yandex cuneiform, and if it exists, output any of the matching options, as well as a sequence of insertion operations to obtain the resulting cuneiform.

In this version of the problem, the number of question marks in the template can be arbitrary.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5 \cdot 10^4 $ ). The description of the test cases follows.

Each test case consists of a single line containing a template of length $ n $ ( $ 3 \leq n < 2 \cdot 10^5 $ , $ n \bmod 3 = 0 $ ), consisting only of characters 'Y', 'D', 'X', and '?'.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line containing 'NO' if it is not possible to obtain a cuneiform from the given template.

Otherwise, output 'YES' on the first line, and on the second line, any obtainable cuneiform. After that, you need to output the sequence of operations that leads to the cuneiform you printed.

A sequence of operations is described by $ \frac{n}{3} $ triples of pairs. A pair has the form c p, where $ c $ is one of the letters 'Y', 'D', or 'X', and $ p $ is the position at which the letter $ c $ should be inserted. The insertion position is the number of letters to skip from the beginning of the string for the insertion. For example, after inserting the character 'D' into the string "YDX" with $ p=3 $ , the result is "YDXD", and with $ p=0 $ , it is "DYDX". Note that the index cannot exceed the current length of the string.

The operations are applied from top to bottom, left to right. After inserting each triple to the string, there should be no two adjacent identical characters.

## 说明/提示

In the second example, the string is transformed like this: $ "" \to \mathtt{YDX} \to \mathtt{YDXDYX} $ .

## 样例 #1

### 输入

```
4
???
Y??D?X
???
D??DXYXYX
```

### 输出

```
YES
YDX
X 0 D 0 Y 0 
YES
YDXDYX
X 0 Y 0 D 1
X 2 D 3 Y 4
YES
YDX
Y 0 D 1 X 2
NO
```



---

---
title: "Kevin and Strange Operation"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2048H
tag: ['动态规划 DP', '树状数组']
---

# Kevin and Strange Operation

## 题目描述

Kevin is exploring problems related to binary strings in Chinatown. When he was at a loss, a stranger approached him and introduced a peculiar operation:

- Suppose the current binary string is $  t  $ , with a length of $  \vert t \vert  $ . Choose an integer $  1 \leq p \leq \vert t \vert  $ . For all $  1 \leq i < p  $ , simultaneously perform the operation $  t_i = \max(t_i, t_{i+1})  $ , and then delete $  t_p  $ .

For example, suppose the current binary string is 01001, and you choose $  p = 4  $ . Perform $  t_i = \max(t_i, t_{i+1})  $ for $ t_1 $ , $ t_2 $ , and $  t_3  $ , transforming the string into 11001, then delete $  t_4  $ , resulting in 1101.

Kevin finds this strange operation quite interesting. Thus, he wants to ask you: Given a binary string $  s  $ , how many distinct non-empty binary strings can you obtain through any number of operations (possibly zero)?

Since the answer may be very large, you only need to output the result modulo $ 998\,244\,353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t \le 10^4 $ ) — the number of test cases.

For each test case, the only line contains a binary string $  s  $ ( $  1 \le \lvert s \rvert \le 10^6  $ ).

It is guaranteed that the sum of $ \lvert s \rvert $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print a single integer in the only line of the output — the number of distinct non-empty binary strings you can obtain, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, all the binary strings you can obtain are: 11001, 1001, 1101, 001, 101, 111, 01, 11, and 1. There are $  9  $ in total.

## 样例 #1

### 输入

```
2
11001
000110111001100
```

### 输出

```
9
73
```



---

---
title: "Curse"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2066F
tag: ['动态规划 DP']
---

# Curse

## 题目描述

给定两个整数数组 $a_1, a_2, \ldots, a_n$ 和 $b_1, b_2, \ldots, b_m$。

你需要判断是否可以通过若干次（可能为零）如下操作将数组 $a$ 转换为数组 $b$。

- 在所有 $a$ 的非空子数组$^{\text{∗}}$中，选择一个具有最大和的子数组，并将该子数组替换为任意非空整数数组。

如果可能，你需要构造任意可行的操作序列。约束条件：你的答案中，所有操作使用的替换数组的长度之和不得超过 $n + m$。所有数字的绝对值不得超过 $10^9$。

$^{\text{∗}}$ 如果数组 $a$ 可以通过从数组 $b$ 的开头和结尾删除若干（可能为零或全部）元素得到，则称 $a$ 是 $b$ 的子数组。


## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 200$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含两个整数 $n, m$（$1 \le n, m \le 500$）——数组 $a$ 和 $b$ 的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$-10^6 \le a_i \le 10^6$）——数组 $a$ 的元素。

每个测试用例的第三行包含 $m$ 个整数 $b_1, b_2, \ldots, b_m$（$-10^6 \le b_i \le 10^6$）——数组 $b$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $500$。

保证所有测试用例的 $m$ 之和不超过 $500$。

## 输出格式

对于每个测试用例，如果无法将数组 $a$ 转换为数组 $b$，则输出 $-1$。

否则，在第一行输出操作次数 $0 \leq q \leq n + m$。接下来按执行顺序输出操作，格式如下：

每个操作的第一行输出三个数字 $l, r, k$（$1 \leq l \leq r \leq |a|$）。第二行输出 $k$ 个整数 $c_1 \ldots c_k$，表示将子数组 $a_l, \ldots, a_r$ 替换为数组 $c_1, \ldots, c_k$。

所有操作的 $k$ 之和不得超过 $n + m$。此外，必须满足 $-10^9 \leq c_i \leq 10^9$。

你不需要最小化操作次数。

## 说明/提示

在第一个测试用例中，初始数组按以下方式修改：

$$ [2, -3, 2, 0] \to [2, -3, -3] \to [-3, -3, -3] \to [-3, -7, -3] \to [-3, -7, 0] $$

你可以选择输出空行或不输出。示例中的空行仅为方便阅读添加。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4 3
2 -3 2 0
-3 -7 0
2 1
-2 -2
2
5 4
-5 9 -3 5 -9
-6 6 -1 -9
```

### 输出

```
4
3 4 1
-3 

1 1 1
-3 

2 2 1
-7 

3 3 1
0
 
-1

3
2 4 1
-5 

1 1 1
-6 

2 2 2
6 -1
```



---

---
title: "Quantifier"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2081E
tag: ['动态规划 DP', '组合数学']
---

# Quantifier

## 题目描述

给定一棵包含 $n+1$ 个节点的有根树，节点编号为 $0$ 到 $n$，其中根节点为 $0$，其唯一的子节点是 $1$。现有 $m$ 个不同芯片，编号为 $1$ 到 $m$，每个芯片颜色为黑色或白色。初始时，这些芯片按编号升序从上到下排列在边 $(0,1)$ 上。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2081E/58bf900e143672111ffad5778f71f85a1474d17a.png) 

芯片的初始位置。树节点以蓝色显示。你可以按任意顺序执行以下操作任意次（包括零次）：
1. 选择两条边 $(u,v)$ 和 $(v,w)$，其中 $u$ 是 $v$ 的父节点，$v$ 是 $w$ 的父节点，且边 $(u,v)$ 上至少有一个芯片。将边 $(u,v)$ 上的最底部芯片移动到边 $(v,w)$ 的最顶部位置（即置于该边所有现有芯片之上）。
2. 选择两条边 $(u,v)$ 和 $(v,w)$，其中 $u$ 是 $v$ 的父节点，$v$ 是 $w$ 的父节点，且边 $(v,w)$ 上至少有一个芯片。将边 $(v,w)$ 上的最顶部芯片移动到边 $(u,v)$ 的最底部位置（即置于该边所有现有芯片之下）。
3. 选择同一边上两个相邻的同色芯片，交换它们的位置。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2081E/6b3fd794319ff8c895e98bf884db81759bf5fe7e.png) 

允许的操作。每个芯片 $i$ 有一个移动范围，定义为从根节点到节点 $d_i$ 的简单路径上的所有边。操作过程中必须确保没有芯片被移动到其移动范围之外的边上。

最终，你需要将所有芯片移回边 $(0,1)$。可以发现芯片的顺序可能发生变化。请计算最终边 $(0,1)$ 上芯片排列的可能方案数对 $998\,244\,353$ 取模的结果。

芯片的排列定义为从顶到底的芯片编号组成的长度为 $m$ 的序列。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 5000$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 5000$）——树的大小减一（即树有 $n+1$ 个节点）和芯片数量。

第二行包含 $n$ 个整数 $p_1, p_2, \ldots, p_n$（$0 \le p_i < i$）——节点 $1$ 到 $n$ 的父节点。保证当且仅当 $i=1$ 时 $p_i = 0$（根的唯一子节点是 $1$）。

第三行包含 $m$ 个整数 $c_1, c_2, \ldots, c_m$（$c_i \in \{0, 1\}$）——每个芯片的颜色（$0$ 表示黑色，$1$ 表示白色）。

第四行包含 $m$ 个整数 $d_1, d_2, \ldots, d_m$（$1 \le d_i \le n$）——每个芯片的移动范围。

保证所有测试用例的 $n$ 总和不超过 $5000$，$m$ 总和不超过 $5000$。

## 输出格式

对于每个测试用例，输出一个整数——可能排列数对 $998\,244\,353$ 取模的结果。


## 说明/提示

第一个测试用例中，可以达成 $2$ 种排列：(1,2) 和 (2,1)。

第二个测试用例中，可以达成 $8$ 种排列：(1,2,3,4)、(1,2,4,3)、(1,3,2,4)、(1,3,4,2)、(1,4,2,3)、(1,4,3,2)、(2,1,3,4) 和 (2,1,4,3)。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3 2
0 1 1
0 1
2 3
4 4
0 1 1 2
0 0 1 1
1 2 3 3
6 6
0 1 1 1 4 5
0 0 0 0 1 1
5 6 1 2 4 3
16 15
0 1 1 3 1 3 4 3 3 7 1 6 11 5 8 10
1 0 1 1 0 1 1 1 1 0 1 1 0 0 0
12 14 13 10 9 16 11 14 13 15 16 10 2 2 5
```

### 输出

```
2
8
108
328459046
```



---

---
title: "Wish Upon a Satellite (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2084G2
tag: ['动态规划 DP', '平衡树', '动态规划优化']
---

# Wish Upon a Satellite (Hard Version)

## 题目描述

这是该问题的简单版本。与困难版本的区别在于，本版本中 $t \le 10^4$、$n \le 5 \times 10^5$ 且所有测试用例的 $n$ 之和不超过 $5\times 10^5$。只有当你解决了该问题的所有版本时才能进行 hack。

对于一个长度为 $k$ 的非空序列 $c$，定义 $f(c)$ 如下：

- Turtle 和 Piggy 正在一个序列上玩游戏。他们被给定序列 $c_1, c_2, \ldots, c_k$，由 Turtle 先手。Turtle 和 Piggy 轮流进行操作（Turtle 第一步，Piggy 第二步，Turtle 第三步，依此类推）。
- 游戏规则如下：
  - 设当前序列长度为 $m$。如果 $m = 1$，游戏结束。
  - 如果游戏未结束且轮到 Turtle，Turtle 必须选择一个整数 $i$（$1 \le i \le m - 1$），将 $c_i$ 设为 $\min(c_i, c_{i + 1})$，并删除 $c_{i + 1}$。
  - 如果游戏未结束且轮到 Piggy，Piggy 必须选择一个整数 $i$（$1 \le i \le m - 1$），将 $c_i$ 设为 $\max(c_i, c_{i + 1})$，并删除 $c_{i + 1}$。
- Turtle 希望最终 $c_1$ 的值最大化，而 Piggy 希望最终 $c_1$ 的值最小化。
- $f(c)$ 表示双方都采取最优策略时，最终 $c_1$ 的值。

对于一个长度为 $n$ 的排列 $p$ $^{\text{∗}}$，Turtle 定义该排列的美观度为 $\sum\limits_{i = 1}^n \sum\limits_{j = i}^n f([p_i, p_{i + 1}, \ldots, p_j])$（即所有 $p$ 的非空子段 $^{\text{†}}$ $c$ 的 $f(c)$ 之和）。

Piggy 给 Turtle 一个长度为 $n$ 的排列 $a$，其中部分元素缺失（用 $0$ 表示）。

Turtle 请你确定一个排列 $b$，满足以下条件：

- $b$ 可以通过填充 $a$ 中缺失的元素得到（即对于所有 $1 \le i \le n$，如果 $a_i \ne 0$，则 $b_i = a_i$）。
- 排列 $b$ 的美观度最大化。

为了方便，你只需要找到这样的排列 $b$ 的最大美观度。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（因为 $n=3$ 但数组中包含 $4$）。

$^{\text{†}}$ 序列 $a$ 是序列 $b$ 的子段，当且仅当 $a$ 可以通过从 $b$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 5\times 10^5$）。  
第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \le a_i \le n$）。保证 $a$ 中非 $0$ 的元素互不相同。  
保证所有测试用例的 $n$ 之和不超过 $5\times 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——排列 $b$ 的最大美观度。


## 说明/提示

- 在第一个测试用例中，美观度最大的排列 $b$ 是 $[1, 2]$。$[1, 2]$ 的美观度为 $4$，因为 $f([1]) + f([2]) + f([1, 2]) = 1 + 2 + 1 = 4$。如果 $c = [1, 2]$，则 $f(c) = 1$，因为 Turtle 只能选择 $i = 1$，并将 $c_1$ 设为 $\min(c_1, c_2) = 1$。

- 在第二个测试用例中，美观度最大的排列之一是 $[3, 2, 1]$。$[3, 2, 1]$ 的美观度为 $12$，因为 $f([3]) + f([2]) + f([1]) + f([3, 2]) + f([2, 1]) + f([3, 2, 1]) = 3 + 2 + 1 + 2 + 1 + 3 = 12$。

- 在第三个测试用例中，美观度最大的排列之一是 $[2, 1, 3]$。

- 在第四个测试用例中，如果 $c = [3, 2, 4, 5, 1]$，则 $f(c) = 3$。一种可能的游戏过程如下：
  - Turtle 选择 $i = 3$，将 $c_3$ 设为 $\min(c_3, c_4) = 4$ 并删除 $c_4$。序列变为 $[3, 2, 4, 1]$。
  - Piggy 选择 $i = 1$，将 $c_1$ 设为 $\max(c_1, c_2) = 3$ 并删除 $c_2$。序列变为 $[3, 4, 1]$。
  - Turtle 选择 $i = 2$，将 $c_2$ 设为 $\min(c_2, c_3) = 1$ 并删除 $c_3$。序列变为 $[3, 1]$。
  - Piggy 选择 $i = 1$，将 $c_1$ 设为 $\max(c_1, c_2) = 3$ 并删除 $c_2$。序列变为 $[3]$。
  - 序列长度为 $1$，游戏结束。最终 $c_1$ 的值为 $3$。

- 在第五个测试用例中，美观度最大的排列之一是 $[1, 3, 2, 5, 6, 4, 7]$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
2
1 0
3
0 0 0
3
0 1 0
5
3 2 4 5 1
7
0 3 2 5 0 0 0
10
1 2 6 5 8 9 0 0 0 0
5
0 4 1 0 0
5
0 1 5 2 3
```

### 输出

```
4
12
11
44
110
300
45
40
```



---

---
title: "Turtle and Nediam 2"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2084H
tag: ['动态规划 DP', '动态规划优化']
---

# Turtle and Nediam 2

## 题目描述

[LGR-205-Div.1 C Turtle and Nediam](https://www.luogu.com.cn/problem/P11283)

给定一个长度为 $n$ 的二进制序列 $s$，仅由 $0$ 和 $1$ 组成。

你可以进行最多 $n - 2$ 次（可以是零次）以下操作：

- 设当前序列 $s$ 的长度为 $m$。选择一个整数 $i$ 满足 $1 \le i \le m - 2$。
- 设子数组 $[s_i, s_{i + 1}, s_{i + 2}]$ 的中位数 $^{\text{∗}}$ 为 $x$，并令 $j$ 为满足 $j \ge i$ 且 $s_j = x$ 的最小整数。
- 从序列中移除 $s_j$ 并将剩余部分拼接。换句话说，将 $s$ 替换为 $[s_1, s_2, \ldots, s_{j - 1}, s_{j + 1}, s_{j + 2}, \ldots, s_m]$。

注意每次操作后，序列 $s$ 的长度会减少 $1$。

求经过若干次操作后，可以得到的不同二进制序列的数量，结果对 $10^9 + 7$ 取模。

$^{\text{∗}}$ 长度为奇数 $k$ 的数组的中位数是指排序后的第 $\frac{k + 1}{2}$ 个元素。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$3 \le n \le 2 \cdot 10^6$）——二进制序列的长度。  
第二行包含一个长度为 $n$ 的字符串 $s$，仅由 $0$ 和 $1$ 组成。  

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^6$。

## 输出格式

对于每个测试用例，输出一个整数——可以得到的二进制序列的数量，对 $10^9 + 7$ 取模。


## 说明/提示

- 在第一个测试用例中，可以得到以下二进制序列：$[1, 1]$、$[1, 1, 1]$、$[1, 1, 1, 1]$、$[1, 1, 1, 1, 1]$。

- 在第二个测试用例中，可以得到以下二进制序列：$[0, 1]$、$[0, 1, 1]$、$[1, 0, 1]$、$[1, 0, 0, 1]$、$[1, 0, 1, 1]$、$[1, 0, 0, 0, 1]$、$[1, 0, 0, 1, 1]$、$[1, 0, 0, 0, 1, 1]$。例如，要得到 $[0, 1, 1]$，可以：
  - 选择 $i = 2$。子数组 $[0, 0, 0]$ 的中位数为 $0$。移除 $s_2$，序列变为 $[1, 0, 0, 1, 1]$。
  - 选择 $i = 1$。子数组 $[1, 0, 0]$ 的中位数为 $0$。移除 $s_2$，序列变为 $[1, 0, 1, 1]$。
  - 选择 $i = 1$。子数组 $[1, 0, 1]$ 的中位数为 $1$。移除 $s_1$，序列变为 $[0, 1, 1]$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
5
11111
6
100011
9
000111000
14
11001111111000
16
0010000110100011
```

### 输出

```
4
8
30
114
514
```



---

---
title: "Kia Bakes a Cake"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2101E
tag: ['动态规划 DP', '标签483']
---

# Kia Bakes a Cake

## 题目描述

给定一个长度为 $n$ 的二进制字符串 $s$ 和一棵包含 $n$ 个顶点的树 $T$。设 $k$ 为 $s$ 中字符 $\mathtt{1}$ 的数量。我们将按照以下规则构造一个包含 $k$ 个顶点的完全无向加权图：

- 对于每个满足 $s_i = \mathtt{1}$ 的 $1 \le i \le n$，创建一个标记为 $i$ 的顶点。
- 对于在上述步骤中创建的任意两个标记为 $u$ 和 $v$ 的顶点，定义它们之间的边权 $w(u, v)$ 为顶点 $u$ 和顶点 $v$ 在树 $T$ 中的距离 $^{\text{∗}}$。

一个依次访问标记为 $v_1, v_2, \ldots, v_m$ 的顶点的简单路径 $^{\text{†}}$ 被称为"优美的"，如果对于所有 $1 \le i \le m - 2$，满足条件 $2 \cdot w(v_i, v_{i + 1}) \le w(v_{i + 1}, v_{i + 2})$。换句话说，路径中每条边的权值必须至少是前一条边权值的两倍。注意对于所有 $1 \le i \le m$，必须满足 $s_{v_i} = \mathtt{1}$，否则将不存在对应标记的顶点。

对于完全无向加权图中每个标记为 $i$ 的顶点（$1 \le i \le n$ 且 $s_i = \mathtt{1}$），确定从该顶点出发的所有优美简单路径中包含顶点的最大数量。

$^{\text{∗}}$ 树中两个顶点 $a$ 和 $b$ 之间的距离等于顶点 $a$ 和顶点 $b$ 之间唯一简单路径上的边数。

$^{\text{†}}$ 路径是指顶点序列 $v_1, v_2, \ldots, v_m$，其中对于所有 $1 \le i \le m - 1$，$v_i$ 和 $v_{i + 1}$ 之间存在一条边。简单路径是指没有重复顶点的路径，即对于所有 $1 \le i < j \le m$，$v_i \neq v_j$。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 7 \cdot 10^4$）——二进制字符串 $s$ 的长度和树 $T$ 的顶点数。

第二行包含一个由 $n$ 个字符组成的二进制字符串 $s_1s_2\ldots s_n$（$s_i \in \{\mathtt{0}, \mathtt{1}\}$）——表示要在完全无向加权图中构造顶点的字符串。

接下来的 $n - 1$ 行，每行包含两个整数 $u$ 和 $v$（$1 \le u, v \le n$）——树 $T$ 的边的端点。

保证给定的边构成一棵树。

保证所有测试用例的 $n$ 之和不超过 $7 \cdot 10^4$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数，第 $i$ 个整数表示从标记为 $i$ 的顶点出发的所有优美简单路径中包含顶点的最大数量。如果不存在标记为 $i$ 的顶点（即 $s_i = \mathtt{0}$），则输出 $-1$。


## 说明/提示

在第一个测试用例中，树 $T$ 和构造的图如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2101E/928009e33bde2023c34e81d5bf874ec034e1fd20.png) 左侧是树 $T$，选中的节点标记为黄色。右侧是构造的完全图。图中展示的优美路径是 $3\rightarrow 4\rightarrow 2$。该路径是优美的，因为 $w(4, 2) = 2$ 至少是 $w(3, 4) = 1$ 的两倍。尝试用 $2\rightarrow 5$ 扩展路径是不可行的，因为 $w(2, 5) = 3$ 小于 $w(4, 2) = 2$ 的两倍。

在第二个测试用例中，树 $T$ 是一条长度为 $17$ 的简单路径。从标记为 $2$ 的顶点出发的一个优美路径示例是 $2\rightarrow 3\rightarrow 5\rightarrow 9\rightarrow 17$，其边权依次为 $1, 2, 4, 8$，每次翻倍。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
5
01111
1 2
2 3
3 4
4 5
17
01101011110101101
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 15
15 16
16 17
2
01
1 2
```

### 输出

```
-1 3 3 3 3 
-1 5 4 -1 4 -1 5 5 5 5 -1 4 -1 5 5 -1 3 
-1 1
```



---

---
title: "Sequence Transformation"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF280E
tag: ['动态规划 DP']
---

# Sequence Transformation

## 题目描述

You've got a non-decreasing sequence $ x_{1},x_{2},...,x_{n} $ $ (1<=x_{1}<=x_{2}<=...<=x_{n}<=q) $ . You've also got two integers $ a $ and $ b $ $ (a<=b; a·(n-1)<q) $ .

Your task is to transform sequence $ x_{1},x_{2},...,x_{n} $ into some sequence $ y_{1},y_{2},...,y_{n} $ $ (1<=y_{i}<=q; a<=y_{i+1}-y_{i}<=b) $ . The transformation price is the following sum: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF280E/179b07629f5c2880a487dce85a0ebc41e16d4717.png). Your task is to choose such sequence $ y $ that minimizes the described transformation price.

## 输入格式

The first line contains four integers $ n,q,a,b $ $ (2<=n<=6000; 1<=q,a,b<=10^{9}; a·(n-1)<q; a<=b) $ .

The second line contains a non-decreasing integer sequence $ x_{1},x_{2},...,x_{n} $ $ (1<=x_{1}<=x_{2}<=...<=x_{n}<=q) $ .

## 输出格式

In the first line print $ n $ real numbers — the sought sequence $ y_{1},y_{2},...,y_{n} $ $ (1<=y_{i}<=q; a<=y_{i+1}-y_{i}<=b) $ . In the second line print the minimum transformation price, that is, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF280E/179b07629f5c2880a487dce85a0ebc41e16d4717.png).

If there are multiple optimal answers you can print any of them.

The answer will be considered correct if the absolute or relative error doesn't exceed $ 10^{-6} $ .

## 样例 #1

### 输入

```
3 6 2 2
1 4 6

```

### 输出

```
1.666667 3.666667 5.666667 
0.666667

```

## 样例 #2

### 输入

```
10 100000 8714 9344
3378 14705 17588 22672 32405 34309 37446 51327 81228 94982

```

### 输出

```
1.000000 8715.000000 17429.000000 26143.000000 34857.000000 43571.000000 52285.000000 61629.000000 70973.000000 80317.000000 
797708674.000000

```



---

---
title: "Student's Camp"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF708E
tag: ['动态规划 DP', '排列组合']
---

# Student's Camp

## 题目描述

Alex studied well and won the trip to student camp Alushta, located on the seashore.

Unfortunately, it's the period of the strong winds now and there is a chance the camp will be destroyed! Camp building can be represented as the rectangle of $ n+2 $ concrete blocks height and $ m $ blocks width.

Every day there is a breeze blowing from the sea. Each block, except for the blocks of the upper and lower levers, such that there is no block to the left of it is destroyed with the probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/422afcf1e06a5628bae49992f52449e3f10a781f.png). Similarly, each night the breeze blows in the direction to the sea. Thus, each block (again, except for the blocks of the upper and lower levers) such that there is no block to the right of it is destroyed with the same probability $ p $ . Note, that blocks of the upper and lower level are indestructible, so there are only $ n·m $ blocks that can be destroyed.

The period of the strong winds will last for $ k $ days and $ k $ nights. If during this period the building will split in at least two connected components, it will collapse and Alex will have to find another place to spend summer.

Find the probability that Alex won't have to look for other opportunities and will be able to spend the summer in this camp.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=1500 $ ) that define the size of the destructible part of building.

The second line of the input contains two integers $ a $ and $ b $ ( $ 1<=a<=b<=10^{9} $ ) that define the probability $ p $ . It's guaranteed that integers $ a $ and $ b $ are coprime.

The third line contains a single integer $ k $ ( $ 0<=k<=100000 $ ) — the number of days and nights strong wind will blow for.

## 输出格式

Consider the answer as an irreducible fraction is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/80a3a0e00c79b470772b3be90efd3e0d2e457bd7.png). Print one integer equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/554b30b982e35fb63eb76dd412a37e11659c08f3.png). It's guaranteed that within the given constraints ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/7e61bb4a29a39d49b7ec2c70e2cceae658d627bd.png).

## 说明/提示

In the first sample, each of the four blocks is destroyed with the probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/fda96725ccc697b767e5edbf0d5cfb5ba17d9aa2.png). There are $ 7 $ scenarios that result in building not collapsing, and the probability we are looking for is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/dda8ba13f4feb6c7325a04d07cb771a7084c4ba2.png), so you should print ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/823f9bb4d7539823cd6e4037b4f9a35cb2e52f03.png)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/2ecb6c84ea76dfa6c7235391533a743f1c25b7f8.png)

## 样例 #1

### 输入

```
2 2
1 2
1

```

### 输出

```
937500007

```

## 样例 #2

### 输入

```
5 1
3 10
1

```

### 输出

```
95964640

```

## 样例 #3

### 输入

```
3 3
1 10
5

```

### 输出

```
927188454

```



---

---
title: "New Year and Binary Tree Paths"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF750G
tag: ['动态规划 DP', '线段树', '枚举']
---

# New Year and Binary Tree Paths

## 题目描述

The New Year tree is an infinite perfect binary tree rooted in the node $ 1 $ . Each node $ v $ has two children: nodes indexed $ (2·v) $ and $ (2·v+1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750G/5f3fba6843b56e8c74120fa68d53319463f26696.png)Polar bears love decorating the New Year tree and Limak is no exception. As he is only a little bear, he was told to decorate only one simple path between some pair of nodes. Though he was given an opportunity to pick the pair himself! Now he wants to know the number of unordered pairs of indices $ (u,v) $ ( $ u<=v $ ), such that the sum of indices of all nodes along the simple path between $ u $ and $ v $ (including endpoints) is equal to $ s $ . Can you help him and count this value?

## 输入格式

The only line of the input contains a single integer $ s $ ( $ 1<=s<=10^{15} $ ).

## 输出格式

Print one integer, denoting the number of unordered pairs of nodes indices defining simple paths with the sum of indices of vertices equal to $ s $ .

## 说明/提示

In sample test, there are $ 4 $ paths with the sum of indices equal to $ 10 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750G/c83b62a188e719702078b419fb6e934500dacd07.png)

## 样例 #1

### 输入

```
10

```

### 输出

```
4

```



---

---
title: "Pairs"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF81E
tag: ['动态规划 DP', '基环树']
---

# Pairs

## 题目描述

有 $n$ 个人，每个人都有自己最好的朋友，**但不保证 a 的最好朋友是 b 时，b 的最好朋友是 a**。

现在要把他们和自己最好的朋友两两分组，因为不一定全部人都能被分在一起，所以求在组数最多的情况下，男女组最多。

## 输入格式

第一行输入 $n$。

接下来 $n$ 行，每行两个整数，第 $i$ 行第一个数为编号为 $i$ 的最好的朋友，第二个数为他是男还是女。男用 $1$ 表示，女用 $2$ 表示。

## 输出格式

输出两个数，为最多组数和最多男女匹配组数。

然后将所有匹配成功的两个人的编号输出出来。

## 样例 #1

### 输入

```
5
5 2
3 2
5 1
2 1
4 2

```

### 输出

```
2 2
5 3
4 2

```

## 样例 #2

### 输入

```
6
5 2
3 2
5 1
2 1
4 2
3 1

```

### 输出

```
3 1
4 2
5 1
3 6

```

## 样例 #3

### 输入

```
8
2 2
3 2
5 1
3 1
6 1
5 1
8 2
7 1

```

### 输出

```
4 1
5 6
3 4
2 1
7 8

```



---

---
title: "Rainbow Balls"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF850F
tag: ['动态规划 DP', '枚举', '期望', '标签458']
---

# Rainbow Balls

## 题目描述

You have a bag of balls of $ n $ different colors. You have $ a_{i} $ balls of the $ i $ -th color.

While there are at least two different colored balls in the bag, perform the following steps:

- Take out two random balls without replacement one by one. These balls might be the same color.
- Color the second ball to the color of the first ball. You are not allowed to switch the order of the balls in this step.
- Place both balls back in the bag.
- All these actions take exactly one second.

Let $ M=10^{9}+7 $ . It can be proven that the expected amount of time needed before you stop can be represented as a rational number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850F/2c40be71c60fe708ee9e4e80e2cd7a26163f3bd6.png), where $ P $ and $ Q $ are coprime integers and where $ Q $ is not divisible by $ M $ . Return the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850F/a816c54f8859ee12f4e38a2cc4dba0d6f8dd5c0b.png).

## 输入格式

The first line of input will contain a single integer $ n $ ( $ 1<=n<=2500 $ ) — the number of colors.

The next line of input will contain $ n $ space separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{5} $ ) — the number of balls of each color.

## 输出格式

Print a single integer, the answer to the problem.

## 说明/提示

In the first sample, no matter what happens, the balls will become the same color after one step.

For the second sample, we have 6 balls. Let’s label the balls from 1 to 6, and without loss of generality, let’s say balls 1,2,3 are initially color 1, balls 4,5 are color 2, and ball 6 are color 3.

Here is an example of how these steps can go:

- We choose ball 5 and ball 6. Ball 6 then becomes color 2.
- We choose ball 4 and ball 5. Ball 5 remains the same color (color 2).
- We choose ball 1 and ball 5. Ball 5 becomes color 1.
- We choose ball 6 and ball 5. Ball 5 becomes color 2.
- We choose ball 3 and ball 4. Ball 4 becomes color 1.
- We choose ball 4 and ball 6. Ball 6 becomes color 1.
- We choose ball 2 and ball 5. Ball 5 becomes color 1.

 At this point, the game ends since all the balls are the same color. This particular sequence took 7 seconds.It can be shown that the answer to this case is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850F/9f76609d2f8aa0999ab074d70f32e2692cee15a9.png).

## 样例 #1

### 输入

```
2
1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
1 2 3

```

### 输出

```
750000026

```



---

