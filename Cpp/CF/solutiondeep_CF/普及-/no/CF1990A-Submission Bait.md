# 题目信息

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

# AI分析结果

### 题目内容中文重写
# 提交诱饵

## 题目描述
爱丽丝（Alice）和鲍勃（Bob）正在一个长度为 $n$ 的数组 $a$ 上玩游戏。

他们轮流进行操作，爱丽丝先开始。无法进行操作的玩家将输掉游戏。起初，变量 $mx$ 被设为 $0$。

在一次操作中，玩家可以进行以下操作：
- 选择一个索引 $i$（$1 \le i \le n$），使得 $a_{i} \geq mx$，然后将 $mx$ 设为 $a_{i}$。接着，将 $a_{i}$ 设为 $0$。

判断爱丽丝是否有获胜策略。

## 说明/提示
在第一个测试用例中，爱丽丝可以选择 $i = 1$，因为 $a_1 = 2 \ge mx = 0$。

在爱丽丝操作之后，$a = [0, 1]$ 且 $mx = 2$。鲍勃无法进行任何操作。爱丽丝获胜。

在第二个测试用例中，爱丽丝没有获胜策略。

例如，如果爱丽丝选择 $i = 1$，在爱丽丝操作之后：$a = [0, 1]$ 且 $mx = 1$。然后，鲍勃可以选择 $i = 2$，因为 $a_2 = 1 \ge mx = 1$。在鲍勃操作之后：$a = [0, 0]$ 且 $mx = 1$。爱丽丝无法进行任何操作。鲍勃获胜。

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
1 2 2 2
```

### 输出
```
YES
NO
YES
NO
YES
```

### 算法分类
模拟

### 综合分析与结论
由于暂无题解，我们可以先分析题目核心思路。该游戏的核心在于模拟爱丽丝和鲍勃轮流操作的过程，根据数组元素和当前 $mx$ 的值来判断是否能进行操作，最终确定爱丽丝是否有获胜策略。关键在于对每一轮操作的模拟以及对数组元素状态的更新。

### 通用建议与扩展思路
- **通用建议**：在模拟过程中，要注意每一轮操作后数组元素和 $mx$ 值的更新，仔细判断是否还有可进行的操作。可以使用循环来模拟轮流操作的过程，直到无法进行操作为止。
- **扩展思路**：同类型的题目可能会改变游戏规则，例如改变操作的条件、增加更多的变量或改变胜负判定条件等。类似的算法套路就是通过模拟游戏的每一步操作，根据规则来判断最终结果。可以将本题的思路扩展到其他回合制游戏的模拟中。

### 推荐洛谷题目
1. P1217 [USACO1.5] 回文质数 Prime Palindromes
2. P1036 选数
3. P1042 乒乓球 

---
处理用时：16.95秒