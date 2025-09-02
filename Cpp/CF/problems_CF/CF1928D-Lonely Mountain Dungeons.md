---
title: "Lonely Mountain Dungeons"
layout: "post"
diff: 普及+/提高
pid: CF1928D
tag: []
---

# Lonely Mountain Dungeons

## 题目描述

Once, the people, elves, dwarves, and other inhabitants of Middle-earth gathered to reclaim the treasures stolen from them by Smaug. In the name of this great goal, they rallied around the powerful elf Timothy and began to plan the overthrow of the ruler of the Lonely Mountain.

The army of Middle-earth inhabitants will consist of several squads. It is known that each pair of creatures of the same race, which are in different squads, adds $ b $ units to the total strength of the army. But since it will be difficult for Timothy to lead an army consisting of a large number of squads, the total strength of an army consisting of $ k $ squads is reduced by $ (k - 1) \cdot x $ units. Note that the army always consists of at least one squad.

It is known that there are $ n $ races in Middle-earth, and the number of creatures of the $ i $ -th race is equal to $ c_i $ . Help the inhabitants of Middle-earth determine the maximum strength of the army they can assemble.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains three integers $ n $ , $ b $ , and $ x $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le b \le 10^6, 0 \le x \le 10^9 $ ) — the number of races and the constants $ b $ and $ x $ described above.

The second line of each test case contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 1 \le c_i \le 2 \cdot 10^5 $ ) — the number of creatures of each of the $ n $ races.

It is guaranteed that the sum of the values $ c_1 + c_2 + \ldots + c_n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum strength of the army that the inhabitants of Middle-earth can assemble.

## 说明/提示

In the first test case, the inhabitants of Middle-earth can form $ 3 $ squads. Since $ x = 0 $ , the army's strength will not decrease due to the number of squads. The inhabitants can be distributed among the squads as follows:

- The single representative of the first species can be sent to the first squad.
- The first representative of the second species can be sent to the first squad, the second representative of the second species can be sent to the second squad. Then the total strength of the army will increase by $ b = 1 $ .
- The first representative of the third species can be sent to the first squad, the second representative of the third species can be sent to the second squad, the third representative of the third species can be sent to the third squad. Then the total strength of the army will increase by $ 3 \cdot b = 3 $ , as they form three pairs in different squads.

Thus, the total strength of the army is $ 4 $ .

In the second test case, the inhabitants of Middle-earth can form $ 3 $ squads. Since $ x = 10 $ , the army's strength will decrease by $ 20 $ . The inhabitants can be distributed among the squads as follows:

- The first representative of the first species can be sent to the first squad, the second representative of the first species can be sent to the second squad. Then the total strength of the army will increase by $ b = 5 $ .
- The first and second representatives of the second species can be sent to the first squad, the third and fourth representatives of the second species can be sent to the second squad, the fifth representative of the third species can be sent to the third squad. Then the total strength of the army will increase by $ 8 \cdot b = 40 $ .
- The first representative of the third species can be sent to the first squad, the second representative of the third species can be sent to the second squad, the third representative of the third species can be sent to the third squad. Then the total strength of the army will increase by $ 3 \cdot b = 15 $ , as they form three pairs in different squads.

Thus, the total strength of the army is $ 5 + 40 + 15 - 20 = 40 $ .

## 样例 #1

### 输入

```
5
3 1 0
1 2 3
3 5 10
2 5 3
4 3 3
3 2 1 2
4 1 0
4 1 4 2
4 1 10
4 1 4 2
```

### 输出

```
4
40
9
13
0
```

