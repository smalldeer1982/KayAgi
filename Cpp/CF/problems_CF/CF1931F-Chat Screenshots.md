---
title: "Chat Screenshots"
layout: "post"
diff: 普及/提高-
pid: CF1931F
tag: ['拓扑排序']
---

# Chat Screenshots

## 题目描述

There are $ n $ people in the programming contest chat. Chat participants are ordered by activity, but each person sees himself at the top of the list.

For example, there are $ 4 $ participants in the chat, and their order is $ [2, 3, 1, 4] $ . Then

- $ 1 $ -st user sees the order $ [1, 2, 3, 4] $ .
- $ 2 $ -nd user sees the order $ [2, 3, 1, 4] $ .
- $ 3 $ -rd user sees the order $ [3, 2, 1, 4] $ .
- $ 4 $ -th user sees the order $ [4, 2, 3, 1] $ .

 $ k $ people posted screenshots in the chat, which show the order of participants shown to this user. The screenshots were taken within a short period of time, and the order of participants has not changed.

Your task is to determine whether there is a certain order that all screenshots correspond to.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of input test cases. The descriptions of test cases follow.

The first line of the description of each test case contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 2 \cdot 10^5, n \cdot k \le 2 \cdot 10^5 $ ) — the number of chat participants and the number of participants who posted screenshots.

The following $ k $ lines contain descriptions of screenshots posted by the participants.

The $ i $ -th row contains $ n $ integers $ a_{ij} $ each ( $ 1 \le a_{ij} \le n $ , all $ a_{ij} $ are different) — the order of participants shown to the participant $ a_{i0} $ , where $ a_{i0} $ — the author of the screenshot. You can show that in the screenshot description it will always be at the top of the list.

It is guaranteed that the sum of $ n \cdot k $ for all test cases does not exceed $ 2 \cdot 10^5 $ . It is also guaranteed that all the authors of the screenshots are different.

## 输出格式

Output $ t $ lines, each of which is the answer to the corresponding test case. As an answer, output "YES" if there exists at least one order of participants, under which all $ k $ screenshots could have been obtained. Otherwise, output "NO".

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 样例 #1

### 输入

```
10
5 1
1 2 3 4 5
4 4
1 2 3 4
2 3 1 4
3 2 1 4
4 2 3 1
6 2
1 3 5 2 4 6
6 3 5 2 1 4
3 3
1 2 3
2 3 1
3 2 1
10 2
1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1
1 1
1
5 2
1 2 3 5 4
2 1 3 5 4
3 3
3 1 2
2 3 1
1 3 2
5 4
3 5 1 4 2
2 5 1 4 3
1 5 4 3 2
5 1 4 3 2
3 3
1 3 2
2 1 3
3 2 1
```

### 输出

```
YES
YES
YES
YES
NO
YES
YES
YES
YES
NO
```

