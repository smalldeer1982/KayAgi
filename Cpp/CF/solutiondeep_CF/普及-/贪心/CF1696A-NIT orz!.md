# 题目信息

# NIT orz!

## 题目描述

NIT, the cleaver, is new in town! Thousands of people line up to orz him. To keep his orzers entertained, NIT decided to let them solve the following problem related to $ \operatorname{or} z $ . Can you solve this problem too?

You are given a 1-indexed array of $ n $ integers, $ a $ , and an integer $ z $ . You can do the following operation any number (possibly zero) of times:

- Select a positive integer $ i $ such that $ 1\le i\le n $ . Then, simutaneously set $ a_i $ to $ (a_i\operatorname{or} z) $ and set $ z $ to $ (a_i\operatorname{and} z) $ . In other words, let $ x $ and $ y $ respectively be the current values of $ a_i $ and $ z $ . Then set $ a_i $ to $ (x\operatorname{or}y) $ and set $ z $ to $ (x\operatorname{and}y) $ .

Here $ \operatorname{or} $ and $ \operatorname{and} $ denote the [bitwise operations OR and AND](https://en.wikipedia.org/wiki/Bitwise_operation) respectively.

Find the maximum possible value of the maximum value in $ a $ after any number (possibly zero) of operations.

## 说明/提示

In the first test case of the sample, one optimal sequence of operations is:

- Do the operation with $ i=1 $ . Now $ a_1 $ becomes $ (3\operatorname{or}3)=3 $ and $ z $ becomes $ (3\operatorname{and}3)=3 $ .
- Do the operation with $ i=2 $ . Now $ a_2 $ becomes $ (4\operatorname{or}3)=7 $ and $ z $ becomes $ (4\operatorname{and}3)=0 $ .
- Do the operation with $ i=1 $ . Now $ a_1 $ becomes $ (3\operatorname{or}0)=3 $ and $ z $ becomes $ (3\operatorname{and}0)=0 $ .

After these operations, the sequence $ a $ becomes $ [3,7] $ , and the maximum value in it is $ 7 $ . We can prove that the maximum value in $ a $ can never exceed $ 7 $ , so the answer is $ 7 $ .

In the fourth test case of the sample, one optimal sequence of operations is:

- Do the operation with $ i=1 $ . Now $ a_1 $ becomes $ (7\operatorname{or}7)=7 $ and $ z $ becomes $ (7\operatorname{and}7)=7 $ .
- Do the operation with $ i=3 $ . Now $ a_3 $ becomes $ (30\operatorname{or}7)=31 $ and $ z $ becomes $ (30\operatorname{and}7)=6 $ .
- Do the operation with $ i=5 $ . Now $ a_5 $ becomes $ (27\operatorname{or}6)=31 $ and $ z $ becomes $ (27\operatorname{and}6)=2 $ .

## 样例 #1

### 输入

```
5
2 3
3 4
5 5
0 2 4 6 8
1 9
10
5 7
7 15 30 29 27
3 39548743
10293834 10284344 13635445```

### 输出

```
7
13
11
31
48234367```

# AI分析结果



# NIT orz!

## 题目描述

NIT 是一位新来到镇上的聪明人！成千上万的人排队要 orz 他。为了让他的 orzers 保持娱乐，NIT 决定让他们解决以下与 $ \operatorname{or} z $ 相关的问题。你也能解决这个问题吗？

给定一个下标从 1 开始的包含 $ n $ 个整数的数组 $ a $ 和一个整数 $ z $。你可以进行任意次数（包括零次）的如下操作：

- 选择一个正整数 $ i $ 满足 $ 1 \le i \le n $。然后同时将 $ a_i $ 设为 $ (a_i \operatorname{or} z) $，并将 $ z $ 设为 $ (a_i \operatorname{and} z) $。换句话说，令 $ x $ 和 $ y $ 分别为当前的 $ a_i $ 和 $ z $，然后将 $ a_i $ 设为 $ (x \operatorname{or} y) $，并将 $ z $ 设为 $ (x \operatorname{and} y) $。

求经过任意次数（包括零次）的操作后，数组 $ a $ 中可能的最大值的最大值。

## 样例 #1

### 输入
```
5
2 3
3 4
5 5
0 2 4 6 8
1 9
10
5 7
7 15 30 29 27
3 39548743
10293834 10284344 13635445
```

### 输出
```
7
13
11
31
48234367
```

---

## 题解分析与结论

### 关键思路总结
所有题解的核心观察是：每次操作后，z 的二进制中 1 的位数**不会增加**（可能减少）。这是因为与运算（AND）只能保留或减少 1 的位数。因此：
1. 对每个元素最多操作一次即可得到最大可能值（多次操作不会更优）
2. 最终答案等价于所有 $ a_i \operatorname{or} z $ 的最大值

### 最优题解推荐

#### 1. 作者：Prms_Prmt（★★★★★）
**核心亮点**：
- 用集合论视角分析位运算特性，证明 z 的二进制集合单调递减
- 代码简洁高效，时间复杂度 O(n)

#### 2. 作者：zhicheng（★★★★☆）
**核心亮点**：
- 明确指出 z 的单调递减性，并通过位运算定义解释原因
- 代码逻辑清晰，变量命名规范

#### 3. 作者：Dry_ice（★★★★☆）
**个人心得**：
> "作为 Global Round 的第一题还是有一定难度的。思维想通了代码很容易。"  
总结：强调思维转换的关键性，适合算法竞赛训练

### 核心代码实现
```cpp
int main() {
    int T, n, z;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &z);
        int max_val = 0;
        for (int i = 0, a; i < n; ++i) {
            scanf("%d", &a);
            max_val = std::max(max_val, a | z);
        }
        printf("%d\n", max_val);
    }
    return 0;
}
```

### 拓展建议
同类问题可关注以下特性：
- 操作中某变量的单调性（如本题 z 的递减性）
- 位运算的贪心性质（高位优先决策）

### 推荐练习题
1. [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)  
   位运算贪心经典题，需构造最优操作序列
2. [P1879 [USACO06NOV]Corn Fields G](https://www.luogu.com.cn/problem/P1879)  
   状态压缩与位运算结合
3. [P5653 基础最优化练习题](https://www.luogu.com.cn/problem/P5653)  
   位运算与贪心策略结合

---
处理用时：47.30秒