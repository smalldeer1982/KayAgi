---
title: "Counting Is Not Fun (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2063F2
tag: []
---

# Counting Is Not Fun (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in this version, the limits on $ t $ and $ n $ are bigger. You can hack only if you solved all versions of this problem.

 Now Little John is rich, and so he finally buys a house big enough to fit himself and his favorite bracket sequence. But somehow, he ended up with a lot of brackets! Frustrated, he penetrates through the ceiling with the "buddha palm".A bracket sequence is called balanced if it can be constructed by the following formal grammar.

1. The empty sequence $ \varnothing $ is balanced.
2. If the bracket sequence $ A $ is balanced, then $ \mathtt{(}A\mathtt{)} $ is also balanced.
3. If the bracket sequences $ A $ and $ B $ are balanced, then the concatenated sequence $ A B $ is also balanced.

For example, the sequences "(())()", "()", "(()(()))", and the empty sequence are balanced, while "(()" and "(()))(" are not.

Given a balanced bracket sequence $ s $ , a pair of indices $ (i,j) $ ( $ i<j $ ) is called a good pair if $ s_i $ is '(', $ s_j $ is ')', and the two brackets are added simultaneously with respect to Rule 2 while constructing the sequence $ s $ . For example, the sequence "(())()" has three different good pairs, which are $ (1,4) $ , $ (2,3) $ , and $ (5,6) $ . One can show that any balanced bracket sequence of $ 2n $ brackets contains exactly $ n $ different good pairs, and using any order of rules to construct the same bracket sequence will yield the same set of good pairs.

Emily will play a bracket guessing game with John. The game is played as follows.

Initially, John has a balanced bracket sequence $ s $ containing $ n $ different good pairs, which is not known to Emily. John tells Emily the value of $ n $ and asks Emily to guess the sequence.

Throughout $ n $ turns, John gives Emily the following kind of clue on each turn.

- $ l\;r $ : The sequence $ s $ contains a good pair $ (l,r) $ .

The clues that John gives Emily are pairwise distinct and do not contradict each other.

At a certain point, Emily can be certain that the balanced bracket sequence satisfying the clues given so far is unique. For example, assume Emily knows that $ s $ has $ 3 $ good pairs, and it contains the good pair $ (2,5) $ . Out of $ 5 $ balanced bracket sequences with $ 3 $ good pairs, there exists only one such sequence "((()))" with the good pair $ (2,5) $ . Therefore, one can see that Emily does not always need $ n $ turns to guess $ s $ .

To find out the content of $ s $ as early as possible, Emily wants to know the number of different balanced bracket sequences that match the clues after each turn. Surely, this is not an easy job for Emily, especially when she is given so many good pairs. Now it is your turn to help Emily. Given the clues, you must find the answer before and after each turn. As the answers may be huge, you need to find them modulo $ 998\,244\,353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 2 \le n \le 3 \cdot 10^5 $ ) — the number of good pairs.

Then, each of the $ n $ following lines contains two integers $ l_i $ and $ r_i $ representing the $ i $ -th clue ( $ 1 \le l_i < r_i \le 2n $ ).

The clues in one test case are pairwise distinct and do not contradict each other.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n+1 $ integers on a separate line:

- The first integer is the answer before all clues, modulo $ 998\,244\,353 $ .
- For all $ i \ge 1 $ , the $ i+1 $ -th integer is the answer after the $ i $ -th clue, modulo $ 998\,244\,353 $ .

## 说明/提示

The first test case of the example is explained in the problem description.

The third test case of the example is explained as follows. It can be shown that there are $ 132 $ balanced bracket sequences with $ 6 $ good pairs. The answers after each clue are given as follows:

1. You are given the good pair $ (2,3) $ . There are $ 42 $ balanced bracket sequences having the good pair $ (2,3) $ .
2. You are given the good pair $ (1,6) $ . There are $ 5 $ balanced bracket sequences having good pairs $ (2,3) $ , $ (1,6) $ .
3. You are given the good pair $ (7,8) $ . There are $ 2 $ balanced bracket sequences having the three good pairs. The strings are "(()())()(())" and "(()())()()()", respectively.
4. You are given the good pair $ (9,12) $ . There is only one balanced bracket sequence having the four good pairs. The content of $ s $ is therefore the only string, which is "(()())()(())".

Then, the number of bracket sequences after the fifth and the sixth clue are both $ 1 $ as you already know the content of $ s $ .

## 样例 #1

### 输入

```
3
3
2 5
1 6
3 4
4
1 6
7 8
2 3
4 5
6
2 3
1 6
7 8
9 12
10 11
4 5
```

### 输出

```
5 1 1 1
14 2 2 1 1
132 42 5 2 1 1 1
```

