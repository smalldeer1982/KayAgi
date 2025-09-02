---
title: "Cheops and a Contest (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2046E2
tag: ['贪心', '构造']
---

# Cheops and a Contest (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in this version, $ m $ is arbitrary. You can hack only if you solved all versions of this problem.

There is a problem-solving competition in Ancient Egypt with $ n $ participants, numbered from $ 1 $ to $ n $ . Each participant comes from a certain city; the cities are numbered from $ 1 $ to $ m $ . There is at least one participant from each city.

The $ i $ -th participant has strength $ a_i $ , specialization $ s_i $ , and wisdom $ b_i $ , so that $ b_i \ge a_i $ . Each problem in the competition will have a difficulty $ d $ and a unique topic $ t $ . The $ i $ -th participant will solve the problem if

- $ a_i \ge d $ , i.e., their strength is not less than the problem's difficulty, or
- $ s_i = t $ , and $ b_i \ge d $ , i.e., their specialization matches the problem's topic, and their wisdom is not less than the problem's difficulty.

Cheops wants to choose the problems in such a way that each participant from city $ i $ will solve strictly more problems than each participant from city $ j $ , for all $ i < j $ .

Please find a set of at most $ 5n $ problems, where the topics of all problems are distinct, so that Cheops' will is satisfied, or state that it is impossible.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ T $ ( $ 1 \le T \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ m $ ( $ 2 \le m \le n \le 3 \cdot {10}^5 $ ) — the number of participants and the number of cities.

The following $ n $ lines describe the participants. The $ i $ -th line contains three integers — $ a_i $ , $ b_i $ , $ s_i $ ( $ 0 \le a_i, b_i, s_i \le {10}^9 $ , $ a_i \le b_i $ ) — strength, wisdom, and specialization of the $ i $ -th participant, respectively.

The next $ m $ lines describe the cities. In the $ i $ -th line, the first number is an integer $ k_i $ ( $ 1 \le k_i \le n $ ) — the number of participants from the $ i $ -th city. It is followed by $ k_i $ integers $ q_{i, 1}, q_{i, 2}, \ldots, q_{i, k_i} $ — ( $ 1 \le q_{i, j} \le n $ , $ 1 \le j \le k_i $ ) — the indices of the participants from this city. It is guaranteed that each participant is mentioned exactly once.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, if there exists a set of problems that satisfies Cheops' conditions, then in the first line output a single integer $ p $ ( $ 1 \le p \le 5n $ ) — the number of problems in your solution.

Then output $ p $ lines, each containing two integers $ d $ and $ t $ ( $ 0 \le d, t \le {10}^9 $ ) — the difficulty and topic of the respective problem. The topics must be distinct.

If there is no set of problems that meets Cheops' wishes, print $ -1 $ instead.

## 样例 #1

### 输入

```
2
5 2
5 7 1
6 7 2
3 9 2
5 10 3
4 4 1
2 1 2
3 3 4 5
2 2
1 2 1
1 2 1
1 2
1 1
```

### 输出

```
7
6 4
6 5
5 6
5 7
4 8
4 9
7 1
-1
```

