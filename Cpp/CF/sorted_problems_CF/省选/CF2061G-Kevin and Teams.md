---
title: "Kevin and Teams"
layout: "post"
diff: 省选/NOI-
pid: CF2061G
tag: []
---

# Kevin and Teams

## 题目描述

This is an interactive problem.

Kevin has $ n $ classmates, numbered $ 1, 2, \ldots, n $ . Any two of them may either be friends or not friends.

Kevin wants to select $ 2k $ classmates to form $ k $ teams, where each team contains exactly $ 2 $ people. Each person can belong to at most one team.

Let $ u_i $ and $ v_i $ be two people in the $ i $ -th team. To avoid potential conflicts during team formation, the team members must satisfy one of the following two conditions:

- For all $ i $ ( $ 1\leq i \leq k $ ), classmate $ u_i $ and $ v_i $ are friends.
- For all $ i $ ( $ 1\leq i \leq k $ ), classmate $ u_i $ and $ v_i $ are not friends.

Kevin wants to determine the maximum $ k $ such that, regardless of the friendship relationships among the $ n $ people, he can always find $ 2k $ people to form the teams. After that, he needs to form $ k $ teams. But asking whether two classmates are friends is awkward, so Kevin wants to achieve this while asking about the friendship status of no more than $ n $ pairs of classmates.

The interactor is adaptive. It means that the hidden relationship between classmates is not fixed before the interaction and will change during the interaction.

## 输出格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains one positive integer $ n $ ( $ 2\leq n \leq 10^5 $ ) — the number of classmates.

First, you should output an integer $ k $ ( $ 1\leq k\leq \frac{n}2 $ ) — the maximum number of teams you can form.

You can make queries in the following way — print one line of the form $ ?\;u\;v $ where $ 1\leq u\neq v \leq n $ . After that, read a single integer: $ 0 $ or $ 1 $ indicating whether they are friends. $ 1 $ means they are friends while $ 0 $ means not.

If you want to print the answer, output $ !\;u_1\;v_1\;u_2\;v_2\;\ldots\;u_k\;v_k $ . You should output exactly $ 2k $ distinct numbers. Then, the interaction continues with the next test case.

You can make at most $ n $ queries. Printing the answer does not count towards the number of queries made.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

After printing each query do not forget to output the end of line and flush $ ^{\text{∗}} $ the output. Otherwise, you will get Idleness limit exceeded verdict.

If, at any interaction step, you read $ -1 $ instead of valid data, your solution must exit immediately. This means that your solution will reveive Wrong answer because of an invalid query or any other mistake. Failing to exit can result in an arbitrary verdict because your solution will continue to read from a closed stream.

Hacks

The interactor for hacks is not adaptive. To make a hack, use the following format.

The first line contains the word "manual".

The second line contains a single integer $ t $ ( $ 1\leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 2\leq n \leq 10^5 $ ) — the number of classmates.

The second line of each test case contains a string $ s $ consisting of '0' and '1' of length $ \frac{n(n - 1)}{2} $ — indicating the relationship between $ (1, 2) $ , $ (1, 3) $ , $ \ldots $ , $ (1, n) $ , $ (2, 3) $ , $ (2, 4) $ , $ \ldots $ , $ (2, n) $ , $ \ldots $ , $ (n - 1, n) $ . '1' means being friends and '0' means not being friends.

The following is the input of example.

```
<pre class="verbatim"><br></br>manual<br></br>2<br></br>3<br></br>011<br></br>5<br></br>1011101011<br></br>
```

The sum of $ n $ over all test cases must not exceed $ 10^5 $ .

There is an additional constraint for hacks: The sum of $ \frac{n(n-1)}{2} $ over all test cases must not exceed $ 10^7 $ .

 $ ^{\text{∗}} $ To flush, use:

- fflush(stdout) or cout.flush() in C++;
- sys.stdout.flush() in Python;
- see the documentation for other languages.

## 说明/提示

In the first test case:

Kevin claims he can form $ 1 $ team regardless of the friendship relationships among the $ 3 $ people.

Kevin asks about the friendship relationship between people $ 1 $ and $ 2 $ . The jury responds that they are friends.

Kevin answers that he can form a team with people $ 1 $ and $ 2 $ .

In the second test case:

Kevin claims he can form $ 2 $ teams regardless of the friendship relationships among the $ 5 $ people.

Kevin asks about the friendship relationship between people $ (1, 2), (3, 4), (3, 5), (1, 3), (2, 4) $ . The jury responds with $ 1, 0, 1, 0, 0 $ .

Kevin answers that he can form two teams with people $ (1, 2) $ and $ (3, 5) $ .

It is also possible to form two teams with people $ (1, 3) $ and $ (2, 4) $ , since they are both not friends.

## 样例 #1

### 输入

```
2
3


1

5


1

0

1

0

0
```

### 输出

```
1
? 1 2

! 1 2

2
? 1 2

? 3 4

? 3 5

? 1 3

? 2 4

! 1 2 3 5
```

