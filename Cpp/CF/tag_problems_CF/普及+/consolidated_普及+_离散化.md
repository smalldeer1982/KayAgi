---
title: "Ardent Flames"
layout: "post"
diff: 普及+/提高
pid: CF2037F
tag: ['二分', '离散化', '差分']
---

# Ardent Flames

## 题目描述

You have obtained the new limited event character Xilonen. You decide to use her in combat.

There are $ n $ enemies in a line. The $ i $ 'th enemy from the left has health $ h_i $ and is currently at position $ x_i $ . Xilonen has an attack damage of $ m $ , and you are ready to defeat the enemies with her.

Xilonen has a powerful "ground stomp" attack. Before you perform any attacks, you select an integer $ p $ and position Xilonen there ( $ p $ can be any integer position, including a position with an enemy currently). Afterwards, for each attack, she deals $ m $ damage to an enemy at position $ p $ (if there are any), $ m-1 $ damage to enemies at positions $ p-1 $ and $ p+1 $ , $ m-2 $ damage to enemies at positions $ p-2 $ and $ p+2 $ , and so on. Enemies that are at least a distance of $ m $ away from Xilonen take no damage from attacks.

Formally, if there is an enemy at position $ x $ , she will deal $ \max(0,m - |p - x|) $ damage to that enemy each hit. Note that you may not choose a different $ p $ for different attacks.

Over all possible $ p $ , output the minimum number of attacks Xilonen must perform to defeat at least $ k $ enemies. If it is impossible to find a $ p $ such that eventually at least $ k $ enemies will be defeated, output $ -1 $ instead. Note that an enemy is considered to be defeated if its health reaches $ 0 $ or below.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) – the number of test cases.

The first line of each test case contains three integers $ n $ , $ m $ , and $ k $ ( $ 1 \leq k \leq n \leq 10^5 $ , $ 1 \leq m \leq 10^9 $ ).

The following line contains $ n $ integers $ h_1, h_2, ..., h_n $ ( $ 1 \leq h_i \leq 10^9 $ ).

The last line of each testcase contains $ n $ integers $ x_1, x_2, ..., x_n $ ( $ 1\leq x_i \leq 10^9 $ , $ x_i < x_{i+1} $ for all $ 1 \leq i < n $ )

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output an integer on a new line, the minimum number of attacks that must be performed to defeat at least $ k $ enemies. If it is impossible to find a $ p $ such that eventually at least $ k $ enemies will be defeated, output $ -1 $ instead.

## 说明/提示

In the first testcase, it is optimal to select $ p=2 $ . Each attack, the first enemy takes $ 5-|2-1|=4 $ damage, the second enemy takes $ 5 $ damage, the third enemy takes $ 4 $ damage, the fourth enemy takes $ 3 $ damage, and the fifth enemy takes $ 2 $ damage. After $ 2 $ attacks, the first three enemies will be defeated. It can be shown that it is impossible to defeat $ 3 $ enemies in less than $ 2 $ attacks, no matter which $ p $ is selected.

In the second testcase, we must kill all $ 9 $ enemies. By selecting $ p=5 $ , all nine enemies will be defeated in $ 2 $ attacks.

In the third testcase, we must kill both enemies. However, it can be shown that no $ p $ selected will damage both enemies at the same time, so the answer is $ -1 $ .

In the fourth testcase, selecting $ p=1 $ will enable us to defeat the first enemy in $ 6969697 $ attacks.

In the fifth testcase, selecting $ p=10 $ will make each enemy take $ 1 $ damage per attack. Both enemies will be defeated in $ 15 $ attacks.

## 样例 #1

### 输入

```
6
5 5 3
7 7 7 7 7
1 2 3 4 5
9 5 9
2 4 6 8 10 8 6 4 2
1 2 3 4 5 6 7 8 9
2 10 2
1 1
1 20
2 10 1
69696969 420420420
1 20
2 10 2
10 15
1 19
2 2 2
1000000000 1
1 3
```

### 输出

```
2
2
-1
6969697
15
1000000000
```



---

