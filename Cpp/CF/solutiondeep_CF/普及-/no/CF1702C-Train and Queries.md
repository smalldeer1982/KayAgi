# 题目信息

# Train and Queries

## 题目描述

Along the railroad there are stations indexed from $ 1 $ to $ 10^9 $ . An express train always travels along a route consisting of $ n $ stations with indices $ u_1, u_2, \dots, u_n $ , where ( $ 1 \le u_i \le 10^9 $ ). The train travels along the route from left to right. It starts at station $ u_1 $ , then stops at station $ u_2 $ , then at $ u_3 $ , and so on. Station $ u_n $ — the terminus.

It is possible that the train will visit the same station more than once. That is, there may be duplicates among the values $ u_1, u_2, \dots, u_n $ .

You are given $ k $ queries, each containing two different integers $ a_j $ and $ b_j $ ( $ 1 \le a_j, b_j \le 10^9 $ ). For each query, determine whether it is possible to travel by train from the station with index $ a_j $ to the station with index $ b_j $ .

For example, let the train route consist of $ 6 $ of stations with indices \[ $ 3, 7, 1, 5, 1, 4 $ \] and give $ 3 $ of the following queries:

- $ a_1 = 3 $ , $ b_1 = 5 $ It is possible to travel from station $ 3 $ to station $ 5 $ by taking a section of the route consisting of stations \[ $ 3, 7, 1, 5 $ \]. Answer: YES.
- $ a_2 = 1 $ , $ b_2 = 7 $ You cannot travel from station $ 1 $ to station $ 7 $ because the train cannot travel in the opposite direction. Answer: NO.
- $ a_3 = 3 $ , $ b_3 = 10 $ It is not possible to travel from station $ 3 $ to station $ 10 $ because station $ 10 $ is not part of the train's route. Answer: NO.

## 说明/提示

The first test case is explained in the problem statement.

## 样例 #1

### 输入

```
3


6 3
3 7 1 5 1 4
3 5
1 7
3 10


3 3
1 2 1
2 1
1 2
4 5


7 5
2 1 1 1 2 4 4
1 3
1 4
2 1
4 1
1 2```

### 输出

```
YES
NO
NO
YES
YES
NO
NO
YES
YES
NO
YES```

# AI分析结果

### 题目内容
# 火车与查询

## 题目描述
沿着铁路分布着编号从1到\(10^9\)的车站。一列特快列车始终沿着由\(n\)个车站组成的路线行驶，这些车站的编号为\(u_1, u_2, \dots, u_n\) ，其中\(1 \le u_i \le 10^9\)。火车沿着路线从左向右行驶。它从车站\(u_1\)出发，然后停靠在车站\(u_2\)，接着是\(u_3\)，依此类推。车站\(u_n\)为终点站。

火车有可能多次经过同一个车站。也就是说，在\(u_1, u_2, \dots, u_n\)这些值中可能存在重复。

给定\(k\)个查询，每个查询包含两个不同的整数\(a_j\)和\(b_j\) (\(1 \le a_j, b_j \le 10^9\))。对于每个查询，判断是否能够乘坐火车从编号为\(a_j\)的车站到达编号为\(b_j\)的车站。

例如，假设火车路线由6个车站组成，编号为\[3, 7, 1, 5, 1, 4\]，并给出以下3个查询：
 - \(a_1 = 3\)，\(b_1 = 5\)。可以通过乘坐由车站\[3, 7, 1, 5\]组成的路线部分从车站3到达车站5。答案：是。
 - \(a_2 = 1\)，\(b_2 = 7\)。由于火车不能反向行驶，所以无法从车站1到达车站7。答案：否。
 - \(a_3 = 3\)，\(b_3 = 10\)。由于车站10不在火车的路线上，所以无法从车站3到达车站10。答案：否。

## 说明/提示
第一个测试用例在题目描述中有解释。

## 样例 #1
### 输入
```
3

6 3
3 7 1 5 1 4
3 5
1 7
3 10

3 3
1 2 1
2 1
1 2
4 5

7 5
2 1 1 1 2 4 4
1 3
1 4
2 1
4 1
1 2
```
### 输出
```
YES
NO
NO
YES
YES
NO
NO
YES
YES
NO
YES
```

### 算法分类
无算法分类

### 综合分析与结论
所有题解思路基本一致，核心都是利用映射（map）记录每个车站编号首次和末次出现的位置，通过比较询问中两个车站编号首次和末次出现位置来判断能否从一个车站到达另一个车站。难点在于数据范围大，不能直接开数组存储，需使用映射。各题解质量相近，都清晰阐述思路并给出实现代码，但在代码风格、细节处理上有差异。

### 通用建议与扩展思路
 - **思路优化**：核心思路已较为简洁高效，可进一步思考在数据量更大时，是否有更优的数据结构或算法。例如，若数据量远超当前范围，可研究是否有更高效的映射结构替代map，以降低时间复杂度。
 - **代码优化**：部分题解使用cin/cout输入输出，在大数据量下可能因速度慢导致超时，可像部分题解一样取消同步或使用scanf/printf等更快的输入输出方式。还可考虑减少不必要的变量定义和中间计算，优化代码空间复杂度。
 - **拓展应用**：此类题目可拓展到其他具有单向顺序关系的场景，如单向链表节点间的可达性判断、按顺序执行任务的可行性判断等。解题思路类似，关键在于记录关键元素的顺序位置信息。

### 相似知识点洛谷题目
 - **P1308 统计单词数**：涉及字符串处理和位置查找，与本题记录位置信息判断关系类似。
 - **P1970 花匠**：需分析序列元素间关系做出决策，和本题判断车站间可达关系思路有相通处。
 - **P2678 [NOIP2015 提高组] 跳石头**：同样是在给定序列上进行判断操作，可类比本题对序列元素位置关系的处理方式。 

---
处理用时：32.85秒