---
title: "Dora and Search"
layout: "post"
diff: 普及/提高-
pid: CF1793C
tag: ['贪心', '双指针 two-pointer']
---

# Dora and Search

## 题目描述

As you know, the girl Dora is always looking for something. This time she was given a permutation, and she wants to find such a subsegment of it that none of the elements at its ends is either the minimum or the maximum of the entire subsegment. More formally, you are asked to find the numbers $ l $ and $ r $ $ (1 \leq l \leq r \leq n) $ such that $ a_l \neq \min(a_l, a_{l + 1}, \ldots, a_r) $ , $ a_l \neq \max(a_l, a_{l + 1}, \ldots, a_r) $ and $ a_r \neq \min(a_l, a_{l + 1}, \ldots, a_r) $ , $ a_r \neq \max(a_l, a_{l + 1}, \ldots, a_r) $ .

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

Help Dora find such a subsegment, or tell her that such a subsegment does not exist.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Description of the test cases follows.

For each test case, the first line contains one integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of permutation.

The second line contains $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq n $ ) — the elements of permutation.

It is guarented that the sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ -1 $ if the desired subsegment does not exist.

Otherwise, output two indexes $ l, r $ such that $ [a_{l}, a_{l + 1}, \ldots, a_{r}] $ satisfies all conditions.

If there are several solutions, then output any of them.

## 说明/提示

In the first and fourth test cases, it can be shown that there are no desired subsegments.

In the second test case, the subsegment $ [1, 4] $ satisfies all the conditions, because $ \max(a_1, a_2, a_3, a_4) = 4, \min(a_1, a_2, a_3, a_4) = 1 $ , as we see, all the conditions are met.

In the third test case, the subsegment $ [2, 6] $ also satisfies all the conditions described.

## 样例 #1

### 输入

```
4
3
1 2 3
4
2 1 4 3
7
1 3 2 4 6 5 7
6
2 3 6 5 4 1
```

### 输出

```
-1
1 4
2 6
-1
```



---

---
title: "Equalize"
layout: "post"
diff: 普及/提高-
pid: CF1928B
tag: ['排序', '双指针 two-pointer']
---

# Equalize

## 题目描述

Vasya has two hobbies — adding permutations $ ^{\dagger} $ to arrays and finding the most frequently occurring element. Recently, he found an array $ a $ and decided to find out the maximum number of elements equal to the same number in the array $ a $ that he can obtain after adding some permutation to the array $ a $ .

More formally, Vasya must choose exactly one permutation $ p_1, p_2, p_3, \ldots, p_n $ of length $ n $ , and then change the elements of the array $ a $ according to the rule $ a_i := a_i + p_i $ . After that, Vasya counts how many times each number occurs in the array $ a $ and takes the maximum of these values. You need to determine the maximum value he can obtain.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 2 \cdot 10^4 $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single number — the maximum number of elements equal to the same number after the operation of adding a permutation.

## 说明/提示

In the first test case, it is optimal to choose $ p = [2, 1] $ . Then after applying the operation, the array $ a $ will be $ [3, 3] $ , in which the number $ 3 $ occurs twice, so the answer is $ 2 $ .

In the second test case, one of the optimal options is $ p = [2, 3, 1, 4] $ . After applying the operation, the array $ a $ will be $ [9, 4, 5, 5] $ . Since the number $ 5 $ occurs twice, the answer is $ 2 $ .

## 样例 #1

### 输入

```
7
2
1 2
4
7 1 4 1
3
103 102 104
5
1 101 1 100 1
5
1 10 100 1000 1
2
3 1
3
1000000000 999999997 999999999
```

### 输出

```
2
2
3
2
1
1
2
```



---

---
title: "Inaccurate Subsequence Search"
layout: "post"
diff: 普及/提高-
pid: CF1955D
tag: ['双指针 two-pointer']
---

# Inaccurate Subsequence Search

## 题目描述

Maxim has an array $ a $ of $ n $ integers and an array $ b $ of $ m $ integers ( $ m \le n $ ).

Maxim considers an array $ c $ of length $ m $ to be good if the elements of array $ c $ can be rearranged in such a way that at least $ k $ of them match the elements of array $ b $ .

For example, if $ b = [1, 2, 3, 4] $ and $ k = 3 $ , then the arrays $ [4, 1, 2, 3] $ and $ [2, 3, 4, 5] $ are good (they can be reordered as follows: $ [1, 2, 3, 4] $ and $ [5, 2, 3, 4] $ ), while the arrays $ [3, 4, 5, 6] $ and $ [3, 4, 3, 4] $ are not good.

Maxim wants to choose every subsegment of array $ a $ of length $ m $ as the elements of array $ c $ . Help Maxim count how many selected arrays will be good.

In other words, find the number of positions $ 1 \le l \le n - m + 1 $ such that the elements $ a_l, a_{l+1}, \dots, a_{l + m - 1} $ form a good array.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ m $ , and $ k $ ( $ 1 \le k \le m \le n \le 2 \cdot 10^5 $ ) — the number of elements in arrays $ a $ and $ b $ , the required number of matching elements.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^6 $ ) — the elements of array $ a $ . Elements of the array $ a $ are not necessarily unique.

The third line of each test case contains $ m $ integers $ b_1, b_2, \dots, b_m $ ( $ 1 \le b_i \le 10^6 $ ) — the elements of array $ b $ . Elements of the array $ b $ are not necessarily unique.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Similarly, it is guaranteed that the sum of $ m $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the number of good subsegments of array $ a $ on a separate line.

## 说明/提示

In the first example, all subsegments are good.

In the second example, good subsegments start at positions $ 1 $ , $ 2 $ , and $ 3 $ .

In the third example, good subsegments start at positions $ 1 $ and $ 2 $ .

## 样例 #1

### 输入

```
5
7 4 2
4 1 2 3 4 5 6
1 2 3 4
7 4 3
4 1 2 3 4 5 6
1 2 3 4
7 4 4
4 1 2 3 4 5 6
1 2 3 4
11 5 3
9 9 2 2 10 9 7 6 3 6 3
6 9 7 8 10
4 1 1
4 1 5 6
6
```

### 输出

```
4
3
2
4
1
```



---

---
title: "Boring Day"
layout: "post"
diff: 普及/提高-
pid: CF1982C
tag: ['双指针 two-pointer']
---

# Boring Day

## 题目描述

On another boring day, Egor got bored and decided to do something. But since he has no friends, he came up with a game to play.

Egor has a deck of $ n $ cards, the $ i $ -th card from the top has a number $ a_i $ written on it. Egor wants to play a certain number of rounds until the cards run out. In each round, he takes a non-zero number of cards from the top of the deck and finishes the round. If the sum of the numbers on the cards collected during the round is between $ l $ and $ r $ , inclusive, the round is won; otherwise, it is lost.

Egor knows by heart the order of the cards. Help Egor determine the maximum number of rounds he can win in such a game. Note that Egor is not required to win rounds consecutively.

## 输入格式

Each test consists of several test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^{4} $ ) — the number of test cases. This is followed by a description of the test cases.

The first line of each test case contains three integers $ n $ , $ l $ , and $ r $ ( $ 1 \le n \le 10^{5} $ , $ 1 \le l \le r \le 10^9 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the numbers on the cards from top to bottom.

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 2 \cdot 10^{5} $ .

## 输出格式

For each test case, output a single number — the maximum number of rounds Egor can win.

## 说明/提示

In the first test case, Egor can win $ 3 $ rounds:

- In the first round, take the top $ 2 $ cards with values $ 2 $ and $ 1 $ and win, as their sum is $ 3 $ . After this, the deck will look like this: $ [11, 3, 7] $ .
- In the second round, take the top card and lose, as its value $ 11 $ is greater than $ r = 10 $ . After this, the deck will look like this: $ [3, 7] $ .
- In the third round, take the top card with value $ 3 $ and win. After this, the deck will look like this: $ [7] $ .
- After this, in the fourth round, Egor only has to take the last card in the deck with value $ 7 $ and win again.

In the second test case, Egor cannot win any rounds, no matter how hard he tries.

In the third test case, you can take one card in each round, then the first and third rounds will be losing, and the second round will be winning.

In the fourth test case, you can take two cards in each round and always win.

## 样例 #1

### 输入

```
8
5 3 10
2 1 11 3 7
10 1 5
17 8 12 11 7 11 21 13 10 8
3 4 5
3 4 2
8 12 25
10 7 5 13 8 9 12 7
2 3 3
5 2
9 7 9
2 10 5 1 3 7 6 2 3
1 8 10
9
5 5 6
1 4 2 6 4
```

### 输出

```
3
0
1
4
0
3
1
2
```



---

---
title: "Yunli's Subarray Queries (easy version)"
layout: "post"
diff: 普及/提高-
pid: CF2009G1
tag: ['双指针 two-pointer']
---

# Yunli's Subarray Queries (easy version)

## 题目描述

**这是该问题的简单版本。保证所有问题中，$r=l+k-1$ 。**

### 题面描述

对于任意数组 $b$，可以多次执行以下操作：

- 选择一个下标 $i$，令 $b_i=x$， 其中 $x$ 为任意整数（不限于区间 $[1,n]$ ）。

记 $f(b)$ 为数组 $b$ 中，存在一个长度至少为 $k$ 的连续子数组$^*$ 的最小操作次数。

给出一个大小为 $n$ 的数组 $a$，然后询问 $q$ 个问题。在每个问题中，你必须输出 $∑_{j=l+k-1}^r f([a_l,a_{l+1},…,a_j])$。注意在该题中，只被要求输出$f([a_l,a_{l+1},…,a_j])$。


------------
$^*$ 如果存在一个长度为 $k$ 的连续子数组，且开始于下标 $i$ $(1≤i≤|b|−k+1)$，则对于所有$i<j≤i+k−1$，满足 $b_j=b_{j−1}+1$。

## 输入格式

第一行包含 $t$ $ (1≤t≤10^4
) $ ——样例的组数。

每组样例的第一行包含三个整数 $n,k$，和 $q$ $(1≤k≤n≤2⋅10^5
, 1≤q≤2⋅10^5
) $ ——数组的长度、连续子数组的长度和问题的个数。

接下去一行包含 $n$ 个整数 $a_1,a_2,…,a_n$ $(1≤a_i≤n
)$。

接下去 $q$ 行包含两个整数 $l$ 和 $r$ $(1≤l≤r≤n
, r=l+k−1

## 输出格式

对于每个问题，输出仅一行—— $∑_{j=l+k-1}^r f([a_l,a_{l+1},…,a_j])$。

## 说明/提示

保证在所有样例中，$n$ 的总和不超过 $2⋅10^5$，$q$ 的总和不超过$2⋅10^5$。


在第一个样例的第一个问题中，$b=[1,2,3,2,1]$。可以执行两次操作以构造一个长度为 $5$ 的连续子数组：

- 令$b_4=4$；
- 令$b_5=5$。

经过以上操作后，$b=[1,2,3,4,5]$。

在第一个样例的第二个问题中，$b=[2,3,2,1,2]$。可以执行三次操作以构造一个长度为 $5$ 的连续子数组：

- 令$b_3=0$；
- 令$b_2=-1$；
- 令$b_1=-2$。

经过以上操作后，$b=[-2,-1,0,1,2]$。

翻译提供：[zhoujy1209](https://www.luogu.com.cn/user/946085)。

## 样例 #1

### 输入

```
3
7 5 3
1 2 3 2 1 2 3
1 5
2 6
3 7
8 4 2
4 3 1 1 2 4 3 2
3 6
2 5
5 4 2
4 5 1 2 3
1 4
2 5
```

### 输出

```
2
3
2
2
2
2
1
```



---

---
title: "New Game"
layout: "post"
diff: 普及/提高-
pid: CF2025C
tag: ['双指针 two-pointer']
---

# New Game

## 题目描述

There's a new game Monocarp wants to play. The game uses a deck of $ n $ cards, where the $ i $ -th card has exactly one integer $ a_i $ written on it.

At the beginning of the game, on the first turn, Monocarp can take any card from the deck. During each subsequent turn, Monocarp can take exactly one card that has either the same number as on the card taken on the previous turn or a number that is one greater than the number on the card taken on the previous turn.

In other words, if on the previous turn Monocarp took a card with the number $ x $ , then on the current turn he can take either a card with the number $ x $ or a card with the number $ x + 1 $ . Monocarp can take any card which meets that condition, regardless of its position in the deck.

After Monocarp takes a card on the current turn, it is removed from the deck.

According to the rules of the game, the number of distinct numbers written on the cards that Monocarp has taken must not exceed $ k $ .

If, after a turn, Monocarp cannot take a card without violating the described rules, the game ends.

Your task is to determine the maximum number of cards that Monocarp can take from the deck during the game, given that on the first turn he can take any card from the deck.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 200\,000 $ ) — the number of cards in the deck and the maximum number of distinct numbers that can be written on the cards that Monocarp takes.

The second line contains a sequence of integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^{9} $ ), where $ a_i $ is the number written on the $ i $ -th card.

Additional constraint of the input: the sum of $ n $ over all test cases doesn't exceed $ 200\,000 $ .

## 输出格式

For each test case, print the maximum number of cards that Monocarp can take from the deck during the game, given that on the first turn he can take any card from the deck.

## 说明/提示

In the first example, Monocarp needs to take any of the cards with the number $ 3 $ . On the next two turns, he needs to take the two remaining cards with the number $ 3 $ . On the next three turns, he needs to take three cards with the number $ 4 $ . After that, Monocarp will not be able to take any more cards from the deck, and he will have $ 6 $ cards.

## 样例 #1

### 输入

```
4
10 2
5 2 4 3 4 3 4 5 3 2
5 1
10 11 10 11 10
9 3
4 5 4 4 6 5 4 4 6
3 2
1 3 1
```

### 输出

```
6
3
9
2
```



---

---
title: "Alice's Adventures in Cutting Cake"
layout: "post"
diff: 普及/提高-
pid: CF2028C
tag: ['二分', '双指针 two-pointer']
---

# Alice's Adventures in Cutting Cake

## 题目描述

爱丽丝参加了疯帽子的茶话会！有一块长长的蛋糕，由 $n$ 个部分组成，每个部分的美味度值为 $a_1, a_2, \ldots, a_n$ 。茶话会上共有 $m$ 个生物，但不包括爱丽丝。

爱丽丝将把蛋糕切成 $m + 1$ 块。正式地说，她将把蛋糕分成 $m + 1$ 个子串，每个子串由一定数量的相邻部分组成。一块蛋糕的美味度是其各部分美味度的总和。之后，她会将这些 $m + 1$ 块蛋糕分给 $m$ 个生物和她自己（她的那块蛋糕可以是空的）。但是，只有当每个 $m$ 个生物的蛋糕美味度达到或超过 $v$ 时，它们才会感到高兴。

Alice 想要确保每个生物都快乐。受此条件限制，她还想最大化自己的那块食物的美味程度。你能帮助 Alice 找到她的那块食物可以达到的最大美味程度吗？如果没有办法确保每个生物都快乐，则输出 $-1$ 。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 10^4$ )。测试用例的描述如下。

每个测试用例的第一行包含三个整数 $n, m, v$ ( $1\le m\le n\le 2\cdot 10^5$ ; $1\le v\le 10^9$ ) — 分别表示部分数量、生物数量和生物对美味的最低要求。

下一行包含 $n$ 个空格分隔的整数 $a_1, a_2, \ldots, a_n$ ( $1 \le a_i \le 10^9$ ) — 部分美味程度。

所有测试用例的总和 $n$ 不超过 $2\cdot 10^5$ 。

## 输出格式

对于每个测试用例，输出 Alice 可以达到的最大美味程度，或者如果没有办法确保每个生物都开心，则输出 $-1$ 。
### 样例解释

对于第一个测试案例，爱丽丝可以将第一和第二部分作为自己的部分，然后将剩余的 $10 + 1 + 1 + 10 = 22$ 美味度留给自己。我们可以证明她不能做得更好。

对于第二个测试案例，爱丽丝可以将第一和第二部分作为一个部分，将第六部分作为一个部分。然后她可以为自己拿走剩余的 $10 + 1 + 1 = 12$ 美味度。我们可以证明她不能做得更好。

对于第七个测试案例，爱丽丝不能给每个生物至少 $12$ 美味度的部分。

## 样例 #1

### 输入

```
7
6 2 1
1 1 10 1 1 10
6 2 2
1 1 10 1 1 10
6 2 3
1 1 10 1 1 10
6 2 10
1 1 10 1 1 10
6 2 11
1 1 10 1 1 10
6 2 12
1 1 10 1 1 10
6 2 12
1 1 1 1 10 10
```

### 输出

```
22
12
2
2
2
0
-1
```



---

---
title: "Trinity"
layout: "post"
diff: 普及/提高-
pid: CF2032C
tag: ['二分', '双指针 two-pointer']
---

# Trinity

## 题目描述

给定 $n$ 个元素的数组 $a_1, a_2, \ldots, a_n$。 

你可以进行如下操作任意次（包括 0 次）：

- 选择两个下标 $i, j\ (1 \le i, j \le n)$，令 $a_i := a_j$。

现请你求出使数组 $a$ 满足下列条件所需的最少操作次数。

- 对每个下标三元组 $(x, y, z)\ (1 \le x, y, z \le n, x \neq y, y \neq z, z \neq x)$ ，都有以 $a_x, a_y, a_z$ 为长度的三条线段可以构成一个非退化三角形。

## 输入格式

**题目有多组数据**。

第一行有一个整数 $T\ (1 \le T \le 10^4)$ ，表示测试数据组数。

对每一组数据，

第一行包括一个整数 $n \ (3 \le n \le 2 \times 10^5)$ 表示数组 $a$ 的元素个数。

第二行有 $n$ 个整数 $a_1, a_2, \ldots, a_n \ (1 \le a_i \le 10^9)$ 表示数组 $a$ 的元素。

保证所有 $n$ 的和不超过 $2 \times 10^5$。

## 输出格式

对每一组数据，输出一个整数表示最少操作次数。

## 说明/提示

对第一组样例，一种可能的操作方式如下：

- 令 $a_1 := a_4 = 4$，数组变为 $[4, 2, 3, 4, 5, 6, 7]$。
- 令 $a_2 := a_5 = 5$，数组变为 $[4, 5, 3, 4, 5, 6, 7]$。
- 令 $a_7 := a_4 = 4$，数组变为 $[4, 5, 3, 4, 5, 6, 4]$。

可以证明最终的数组符合条件，并且 3 次操作是最少的。

对第二组样例，我们令 $a_1 := a_2 = 3$ 使数组变为 $a = [3, 3, 2]$ 即可。

对第三组样例，既然 $3, 4, 5$ 已经可以构成三角形的三条边，我们并不需要进行任何操作。

## 样例 #1

### 输入

```
4
7
1 2 3 4 5 6 7
3
1 3 2
3
4 5 3
15
9 3 8 1 6 5 3 8 2 1 4 2 9 4 7
```

### 输出

```
3
1
0
8
```



---

---
title: "Sakurako's Field Trip"
layout: "post"
diff: 普及/提高-
pid: CF2033C
tag: ['动态规划 DP', '双指针 two-pointer', '分类讨论']
---

# Sakurako's Field Trip

## 题目描述

Even in university, students need to relax. That is why Sakurakos teacher decided to go on a field trip. It is known that all of the students will be walking in one line. The student with index $ i $ has some topic of interest which is described as $ a_i $ . As a teacher, you want to minimise the disturbance of the line of students.

The disturbance of the line is defined as the number of neighbouring people with the same topic of interest. In other words, disturbance is the number of indices $ j $ ( $ 1 \le j < n $ ) such that $ a_j = a_{j + 1} $ .

In order to do this, you can choose index $ i $ ( $ 1\le i\le n $ ) and swap students at positions $ i $ and $ n-i+1 $ . You can perform any number of swaps.

Your task is to determine the minimal amount of disturbance that you can achieve by doing the operation described above any number of times.

## 输入格式

The first line contains one integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

Each test case is described by two lines.

- The first line contains one integer $ n $ ( $ 2 \le n \le 10^5 $ ) — the length of the line of students.
- The second line contains $ n $ integers $ a_i $ ( $ 1\le a_i\le n $ ) — the topics of interest of students in line.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output the minimal possible disturbance of the line that you can achieve.

## 说明/提示

In the first example, it is necessary to apply the operation to $ i=2 $ , thus the array will become $ [1, \textbf{2}, 1, \textbf{1}, 3] $ , with the bold elements indicating those that have swapped places. The disturbance of this array is equal to $ 1 $ .

In the fourth example, it is sufficient to apply the operation to $ i=3 $ , thus the array will become $ [2, 1, \textbf{2}, \textbf{1}, 2, 4] $ . The disturbance of this array is equal to $ 0 $ .

In the eighth example, it is sufficient to apply the operation to $ i=3 $ , thus the array will become $ [1, 4, \textbf{1}, 5, \textbf{3}, 1, 3] $ . The disturbance of this array is equal to $ 0 $ .

## 样例 #1

### 输入

```
9
5
1 1 1 2 3
6
2 1 2 2 1 1
4
1 2 1 1
6
2 1 1 2 2 4
4
2 1 2 3
6
1 2 2 1 2 1
5
4 5 5 1 5
7
1 4 3 5 1 1 3
7
3 1 3 2 2 3 3
```

### 输出

```
1
2
1
0
0
1
1
0
2
```



---

---
title: "Coloring Game"
layout: "post"
diff: 普及/提高-
pid: CF2112C
tag: ['二分', '枚举', '双指针 two-pointer']
---

# Coloring Game

## 题目描述

Alice 和 Bob 使用一个长度为 $n$ 的数列 $a$ 进行游戏。

初始时，任何数列中的数字都没有被染色。首先，Alice 选择 $3$ 个 $a$ 中的元素并将它们染为红色。然后 Bob 将选择一个任意元素并将它染为蓝色（如果这个元素原本是红色的，那么蓝色将覆盖掉红色）。Alice 获胜当且仅当剩余的红色的数字之和严格大于蓝色的数字。

你需要计算 Alice 有多少种选择 $3$ 个元素染色的方案使得无论 Bob 如何操作 Alive 都将获胜。

## 输入格式

多组数据。第一行一个整数 $t$ ($1\le t\le 1000$) 表示数据组数。

对于每组数据，第一行一个整数 $n$ ($3\le n\le 5000$)。\
第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n$ ($1\le a_1\le a_2\le \cdots\le a_n\le 10^5$)。

保证单个测试点内 $\sum n\le 5000$。

## 输出格式

对于每组数据，输出一行一个整数表示答案。

## 说明/提示

**样例解释**

对于前两组数据，无论 Alice 怎么选择元素，Bob 总有办法选择元素使得 Alice 不能获胜。

对于第三组数据，Alice 可以选择任意的三个元素。如果 Bob 选择对红色的某个元素染色，红色数字的和将为 $14$，蓝色数字的和将为 $7$；如果 Bob 选择对某个未染色的元素染色，红色数字的和将为 $21$，蓝色数字的和将为 $7$。

对于第四组数据，Alice 可以选择 $a_1,a_3,a_4$ 或 $a_2,a_3,a_4$。

## 样例 #1

### 输入

```
6
3
1 2 3
4
1 1 2 4
5
7 7 7 7 7
5
1 1 2 2 4
6
2 3 3 4 5 5
5
1 1 1 1 3
```

### 输出

```
0
0
10
2
16
0
```



---

