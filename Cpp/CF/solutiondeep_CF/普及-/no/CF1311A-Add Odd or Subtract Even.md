# 题目信息

# Add Odd or Subtract Even

## 题目描述

You are given two positive integers $ a $ and $ b $ .

In one move, you can change $ a $ in the following way:

- Choose any positive odd integer $ x $ ( $ x > 0 $ ) and replace $ a $ with $ a+x $ ;
- choose any positive even integer $ y $ ( $ y > 0 $ ) and replace $ a $ with $ a-y $ .

You can perform as many such operations as you want. You can choose the same numbers $ x $ and $ y $ in different moves.

Your task is to find the minimum number of moves required to obtain $ b $ from $ a $ . It is guaranteed that you can always obtain $ b $ from $ a $ .

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case, you can just add $ 1 $ .

In the second test case, you don't need to do anything.

In the third test case, you can add $ 1 $ two times.

In the fourth test case, you can subtract $ 4 $ and add $ 1 $ .

In the fifth test case, you can just subtract $ 6 $ .

## 样例 #1

### 输入

```
5
2 3
10 10
2 4
7 4
9 3```

### 输出

```
1
0
2
2
1```

# AI分析结果

### 题目内容
# 加奇数或减偶数

## 题目描述
给定两个正整数 \(a\) 和 \(b\) 。
在一步操作中，你可以按以下方式改变 \(a\) ：
 - 选择任意正奇数 \(x\)（\(x > 0\)），并将 \(a\) 替换为 \(a + x\) ；
 - 选择任意正偶数 \(y\)（\(y > 0\)），并将 \(a\) 替换为 \(a - y\) 。
你可以根据需要执行任意多次这样的操作。在不同的操作中，你可以选择相同的数字 \(x\) 和 \(y\) 。
你的任务是找出从 \(a\) 得到 \(b\) 所需的最少操作次数。保证你总能从 \(a\) 得到 \(b\) 。
你必须回答 \(t\) 个独立的测试用例。

## 说明/提示
在第一个测试用例中，你可以直接加 \(1\) 。
在第二个测试用例中，你无需做任何操作。
在第三个测试用例中，你可以加 \(1\) 两次。
在第四个测试用例中，你可以减去 \(4\) 再加 \(1\) 。
在第五个测试用例中，你可以直接减去 \(6\) 。

## 样例 #1
### 输入
```
5
2 3
10 10
2 4
7 4
9 3
```
### 输出
```
1
0
2
2
1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过对 \(a\) 和 \(b\) 的大小关系以及它们差值的奇偶性进行分类讨论，来确定将 \(a\) 变为 \(b\) 所需的最少操作次数。所有题解都基于数学推理，通过列举不同条件下的操作方式得出结论。不同题解在表述和代码实现风格上有所差异，但本质算法相同。

### 通用建议与扩展思路
对于此类题目，关键在于抓住操作对数字性质（本题为奇偶性）的影响，通过细致的分类讨论得出结论。可以拓展到更多复杂的数字变换规则题目，同样从分析操作对数字性质的改变入手，进行分类求解。

### 洛谷题目推荐
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过比较不同购买方案的价格，选择最优方案，涉及简单的数学计算与比较。
- [P1035 级数求和](https://www.luogu.com.cn/problem/P1035)：根据给定的条件进行数学计算，确定满足条件的项数，考查数学运算与逻辑判断。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：利用数学方法找出连续自然数相加等于给定数的所有情况，需要对数学关系有较好的理解和运用。 

---
处理用时：31.94秒