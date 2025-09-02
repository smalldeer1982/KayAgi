# 题目信息

# I.O.U.

## 题目描述

Imagine that there is a group of three friends: A, B and С. A owes B 20 rubles and B owes C 20 rubles. The total sum of the debts is 40 rubles. You can see that the debts are not organized in a very optimal manner. Let's rearrange them like that: assume that A owes C 20 rubles and B doesn't owe anything to anybody. The debts still mean the same but the total sum of the debts now equals 20 rubles.

This task is a generalisation of a described example. Imagine that your group of friends has $ n $ people and you know the debts between the people. Optimize the given debts without changing their meaning. In other words, finally for each friend the difference between the total money he should give and the total money he should take must be the same. Print the minimum sum of all debts in the optimal rearrangement of the debts. See the notes to the test samples to better understand the problem.

## 说明/提示

In the first sample, you can assume that person number 1 owes 8 rubles to person number 2, 1 ruble to person number 3 and 1 ruble to person number 4. He doesn't owe anybody else anything. In the end, the total debt equals 10.

In the second sample, there are no debts.

In the third sample, you can annul all the debts.

## 样例 #1

### 输入

```
5 3
1 2 10
2 3 1
2 4 1
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 3
1 2 1
2 3 1
3 1 1
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# I.O.U.
## 题目描述
想象有一个三人小组：A、B 和 C。A 欠 B 20 卢布，B 欠 C 20 卢布。债务总和是 40 卢布。可以看到，这些债务的组织方式不是很优化。让我们重新安排一下：假设 A 欠 C 20 卢布，B 不欠任何人钱。债务的实际意义仍然相同，但现在债务总和等于 20 卢布。

这个任务是上述示例的一般化。想象你的朋友小组有 $n$ 个人，并且你知道人们之间的债务关系。在不改变债务实际意义的情况下优化给定的债务。换句话说，最终对于每个朋友，他应该给出的总金额与他应该收到的总金额之间的差值必须保持不变。打印优化债务后的最小债务总和。查看测试样例的注释以更好地理解问题。
## 说明/提示
在第一个样例中，可以假设 1 号人欠 2 号人 8 卢布，欠 3 号人 1 卢布，欠 4 号人 1 卢布。他不欠其他人任何东西。最后，总债务等于 10。
在第二个样例中，没有债务。
在第三个样例中，可以取消所有债务。
## 样例 #1
### 输入
```
5 3
1 2 10
2 3 1
2 4 1
```
### 输出
```
10
```
## 样例 #2
### 输入
```
3 0
```
### 输出
```
0
```
## 样例 #3
### 输入
```
4 3
1 2 1
2 3 1
3 1 1
```
### 输出
```
0
```

### 算法分类
数学

### 综合分析与结论
这些题解思路基本一致，都是通过一个数组记录每个人的债务情况，每当有债务输入，就对相应两人的债务进行增减操作。难点在于理解债务关系的转化，即通过数组记录和更新债务，能自动实现债务的抵消与优化。最后统计数组中正数之和（或负数绝对值之和）得到最小债务总和。不同题解在代码实现上有些许差异，如输入方式、变量命名等，但核心算法相同。

### 通用建议与扩展思路
通用建议：在处理这类债务关系优化问题时，关键是清晰地建立债务记录模型，理解债务在不同人之间的转移和抵消逻辑。可拓展思路：类似题目可能会增加人数、债务关系的复杂性，或者改变债务抵消的规则。可以进一步思考如何在更复杂场景下快速准确地计算优化后的债务总和。例如，在大规模数据下，如何优化算法的时间和空间复杂度，是否可以利用更高效的数据结构来存储和处理债务关系。

### 洛谷相似题目推荐
 - [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：通过递推的方式解决棋盘上棋子移动路径数量问题，涉及到类似的状态记录与更新思想。
 - [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：需要通过枚举和数学计算来解决火柴棒组成等式的问题，锻炼对数字关系和计算逻辑的处理能力。
 - [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)：利用递推方法解决楼梯步数计算问题，与本题在逻辑推导和状态记录上有相似之处。 

---
处理用时：30.86秒