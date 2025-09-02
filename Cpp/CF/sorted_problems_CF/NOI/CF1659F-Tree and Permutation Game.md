---
title: "Tree and Permutation Game"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1659F
tag: []
---

# Tree and Permutation Game

## 题目描述

There is a tree of $ n $ vertices and a permutation $ p $ of size $ n $ . A token is present on vertex $ x $ of the tree.

Alice and Bob are playing a game. Alice is in control of the permutation $ p $ , and Bob is in control of the token on the tree. In Alice's turn, she must pick two distinct numbers $ u $ and $ v $ (not positions; $ u \neq v $ ), such that the token is neither at vertex $ u $ nor vertex $ v $ on the tree, and swap their positions in the permutation $ p $ . In Bob's turn, he must move the token to an adjacent vertex from the one it is currently on.

Alice wants to sort the permutation in increasing order. Bob wants to prevent that. Alice wins if the permutation is sorted in increasing order at the beginning or end of her turn. Bob wins if he can make the game go on for an infinite number of moves (which means that Alice is never able to get a sorted permutation). Both players play optimally. Alice makes the first move.

Given the tree, the permutation $ p $ , and the vertex $ x $ on which the token initially is, find the winner of the game.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of each test case follows.

The first line of each test case has two integers $ n $ and $ x $ ( $ 3 \leq n \leq 2 \cdot 10^5 $ ; $ 1 \leq x \leq n $ ).

Each of the next $ n-1 $ lines contains two integers $ a $ and $ b $ ( $ 1 \le a, b \le n $ , $ a \neq b $ ) indicating an undirected edge between vertex $ a $ and vertex $ b $ . It is guaranteed that the given edges form a tree.

The next line contains $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ) — the permutation $ p $ .

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output one line containing Alice or Bob — the winner of the game. The output is case-sensitive.

## 说明/提示

Here is the explanation for the first example:

In the first test case, there is a way for Alice to win. Here is a possible sequence of moves:

1. Alice swaps $ 5 $ and $ 6 $ , resulting in $ [2,1,3,5,4,6] $ .
2. Bob moves the token to vertex $ 5 $ .
3. Alice swaps $ 1 $ and $ 2 $ , resulting in $ [1,2,3,5,4,6] $ .
4. Bob moves the token to vertex $ 3 $ .
5. Alice swaps $ 4 $ and $ 5 $ , resulting in $ [1,2,3,4,5,6] $ , and wins.

In the second test case, Alice cannot win since Bob can make the game go on forever. Here is the sequence of moves:

1. Alice can only swap $ 1 $ and $ 3 $ , resulting in $ [3,1,2] $ .
2. Bob moves the token to vertex $ 1 $ .
3. Alice can only swap $ 2 $ and $ 3 $ , resulting in $ [2,1,3] $ .
4. Bob moves the token to vertex $ 2 $ .
5. Alice can only swap $ 1 $ and $ 3 $ , resulting in $ [2,3,1] $ .
6. Bob moves the token to vertex $ 3 $ .
7. Alice can only swap $ 1 $ and $ 2 $ , resulting in $ [1,3,2] $ .
8. Bob moves the token to vertex $ 2 $ .

 And then the sequence repeats forever.In the third test case, Alice wins immediately since the permutation is already sorted.

## 样例 #1

### 输入

```
3
6 3
1 3
3 2
4 3
3 6
5 3
2 1 3 6 4 5
3 2
1 2
3 2
1 3 2
3 2
1 2
3 2
1 2 3
```

### 输出

```
Alice
Bob
Alice
```

## 样例 #2

### 输入

```
1
11 4
3 11
5 9
10 3
4 8
2 4
1 8
6 8
8 7
4 5
5 11
7 4 9 8 6 5 11 10 2 3 1
```

### 输出

```
Alice
```

