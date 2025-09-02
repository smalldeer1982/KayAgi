# Submission Bait

## 题目描述

Alice and Bob are playing a game in an array $ a $ of size $ n $ .

They take turns to do operations, with Alice starting first. The player who can not operate will lose. At first, a variable $ mx $ is set to $ 0 $ .

In one operation, a player can do:

- Choose an index $ i $ ( $ 1 \le i \le n $ ) such that $ a_{i} \geq mx $ and set $ mx $ to $ a_{i} $ . Then, set $ a_{i} $ to $ 0 $ .

Determine whether Alice has a winning strategy.

## 说明/提示

In the first test case, Alice can choose $ i=1 $ since $ a_1=2 \ge mx=0 $ .

After Alice's operation, $ a=[0,1] $ and $ mx=2 $ . Bob can not do any operation. Alice wins.

In the second test case, Alice doesn't have a winning strategy.

For example, if Alice chooses $ i=1 $ , after Alice's operation: $ a=[0,1] $ and $ mx=1 $ . Then, Bob can choose $ i=2 $ since $ a_2=1 \ge mx=1 $ . After Bob's operation: $ a=[0,0] $ and $ mx=1 $ . Alice can not do any operation. Bob wins.

## 样例 #1

### 输入

```
5
2
2 1
2
1 1
3
3 3 3
4
3 3 4 4
4
1 2 2 2```

### 输出

```
YES
NO
YES
NO
YES```

