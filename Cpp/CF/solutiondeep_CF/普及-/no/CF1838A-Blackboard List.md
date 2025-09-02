# 题目信息

# Blackboard List

## 题目描述

Two integers were written on a blackboard. After that, the following step was carried out $ n-2 $ times:

- Select any two integers on the board, and write the absolute value of their difference on the board.

After this process was complete, the list of $ n $ integers was shuffled. You are given the final list. Recover one of the initial two numbers. You do not need to recover the other one.

You are guaranteed that the input can be generated using the above process.

## 说明/提示

For the first test case, $ a $ can be produced by starting with either $ 9 $ and $ 2 $ , and then writing down $ |9-2|=7 $ , or starting with $ 9 $ and $ 7 $ and writing down $ |9-7|=2 $ . So $ 2 $ , $ 7 $ , and $ 9 $ are all valid answers, because they all appear in at least one valid pair.

For the second test case, we can show that the two initial numbers must have been $ -4 $ and $ 11 $ .

For the fourth test case, the starting numbers could have been either $ 3 $ and $ 3 $ , or $ 3 $ and $ 0 $ , so $ 3 $ and $ 0 $ are both valid answers.

For the fifth test case, we can show that the starting numbers were $ 8 $ and $ 16 $ .

## 样例 #1

### 输入

```
9
3
9 2 7
3
15 -4 11
4
-9 1 11 -10
5
3 0 0 0 3
7
8 16 8 0 8 16 8
4
0 0 0 0
10
27 1 24 28 2 -1 26 25 28 27
6
600000000 800000000 0 -200000000 1000000000 800000000
3
0 -1000000000 1000000000```

### 输出

```
9
11
-9
3
8
0
-1
600000000
0```

# AI分析结果

【中文重写】
# 黑板上的数字列表

## 题目描述
黑板上最初写有两个整数。之后，进行了 $n - 2$ 次以下操作：
- 选择黑板上的任意两个整数，将它们差的绝对值写在黑板上。

完成这个过程后，这 $n$ 个整数的列表被打乱。现在给定最终的列表，需要还原出最初的两个数字中的一个，不需要还原另一个。

保证输入的列表可以通过上述过程生成。

## 说明/提示
对于第一个测试用例，$a$ 可以由 $9$ 和 $2$ 开始生成，先写下 $|9 - 2| = 7$；也可以由 $9$ 和 $7$ 开始，写下 $|9 - 7| = 2$。所以 $2$、$7$ 和 $9$ 都是有效的答案，因为它们都至少出现在一组有效的初始数字对中。

对于第二个测试用例，可以证明最初的两个数字一定是 $-4$ 和 $11$。

对于第四个测试用例，最初的数字可能是 $3$ 和 $3$，也可能是 $3$ 和 $0$，所以 $3$ 和 $0$ 都是有效的答案。

对于第五个测试用例，可以证明最初的数字是 $8$ 和 $16$。

## 样例 #1

### 输入
```
9
3
9 2 7
3
15 -4 11
4
-9 1 11 -10
5
3 0 0 0 3
7
8 16 8 0 8 16 8
4
0 0 0 0
10
27 1 24 28 2 -1 26 25 28 27
6
600000000 800000000 0 -200000000 1000000000 800000000
3
0 -1000000000 1000000000
```

### 输出
```
9
11
-9
3
8
0
-1
600000000
0
```

【算法分类】
数学

【综合分析与结论】
由于暂无题解，我们从题目本身分析。本题的核心在于根据最终的数字列表还原出最初的两个数字中的一个。关键在于理解每次操作是取两个数差的绝对值，且最终列表是由最初两个数经过多次这样的操作并打乱得到的。难点在于如何从打乱的列表中找到最初的数字。通用的思路可以是分析数字之间的差值关系，可能需要对数字进行排序等操作来辅助分析。

【通用建议与扩展思路】
通用建议：可以先对输入的数字列表进行排序，然后尝试分析相邻数字或数字之间的差值关系，看是否能找到规律来确定最初的数字。
扩展思路：同类型的题目可能会有不同的操作规则，比如不是取差的绝对值，而是其他运算，但核心都是根据最终结果反推最初的状态。可以尝试从简单的情况入手，分析数字变化的规律，利用数学性质来解决问题。

【推荐洛谷题目】
1. P1047 [NOIP2005 普及组] 校门外的树：考察对数学规律的分析和应用。
2. P1003 [NOIP2011 提高组] 铺地毯：需要分析坐标和覆盖关系，与本题分析数字关系有相似之处。
3. P1014 [NOIP1999 普及组] Cantor 表：需要通过数学推理找到数字的排列规律。 

---
处理用时：22.47秒