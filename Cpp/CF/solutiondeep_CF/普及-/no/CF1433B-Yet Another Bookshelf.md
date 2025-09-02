# 题目信息

# Yet Another Bookshelf

## 题目描述

There is a bookshelf which can fit $ n $ books. The $ i $ -th position of bookshelf is $ a_i = 1 $ if there is a book on this position and $ a_i = 0 $ otherwise. It is guaranteed that there is at least one book on the bookshelf.

In one move, you can choose some contiguous segment $ [l; r] $ consisting of books (i.e. for each $ i $ from $ l $ to $ r $ the condition $ a_i = 1 $ holds) and:

- Shift it to the right by $ 1 $ : move the book at index $ i $ to $ i + 1 $ for all $ l \le i \le r $ . This move can be done only if $ r+1 \le n $ and there is no book at the position $ r+1 $ .
- Shift it to the left by $ 1 $ : move the book at index $ i $ to $ i-1 $ for all $ l \le i \le r $ . This move can be done only if $ l-1 \ge 1 $ and there is no book at the position $ l-1 $ .

Your task is to find the minimum number of moves required to collect all the books on the shelf as a contiguous (consecutive) segment (i.e. the segment without any gaps).

For example, for $ a = [0, 0, 1, 0, 1] $ there is a gap between books ( $ a_4 = 0 $ when $ a_3 = 1 $ and $ a_5 = 1 $ ), for $ a = [1, 1, 0] $ there are no gaps between books and for $ a = [0, 0,0] $ there are also no gaps between books.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, you can shift the segment $ [3; 3] $ to the right and the segment $ [4; 5] $ to the right. After all moves, the books form the contiguous segment $ [5; 7] $ . So the answer is $ 2 $ .

In the second test case of the example, you have nothing to do, all the books on the bookshelf form the contiguous segment already.

In the third test case of the example, you can shift the segment $ [5; 5] $ to the left and then the segment $ [4; 4] $ to the left again. After all moves, the books form the contiguous segment $ [1; 3] $ . So the answer is $ 2 $ .

In the fourth test case of the example, you can shift the segment $ [1; 1] $ to the right, the segment $ [2; 2] $ to the right, the segment $ [6; 6] $ to the left and then the segment $ [5; 5] $ to the left. After all moves, the books form the contiguous segment $ [3; 4] $ . So the answer is $ 4 $ .

In the fifth test case of the example, you can shift the segment $ [1; 2] $ to the right. After all moves, the books form the contiguous segment $ [2; 5] $ . So the answer is $ 1 $ .

## 样例 #1

### 输入

```
5
7
0 0 1 0 1 0 1
3
1 0 0
5
1 1 0 0 1
6
1 0 0 0 0 1
5
1 1 0 1 1```

### 输出

```
2
0
2
4
1```

# AI分析结果

### 题目内容
# 又一个书架

## 题目描述
有一个可以放$n$本书的书架。如果书架的第$i$个位置有书，则$a_i = 1$，否则$a_i = 0$。保证书架上至少有一本书。

在一次移动中，你可以选择一段连续的由书组成的区间$[l; r]$（即对于从$l$到$r$的每个$i$，都满足$a_i = 1$），并且：
- 向右移动$1$位：将索引$i$处的书移动到$i + 1$处，对于所有$l \leq i \leq r$。仅当$r + 1 \leq n$且位置$r + 1$没有书时，才能进行此移动。
- 向左移动$1$位：将索引$i$处的书移动到$i - 1$处，对于所有$l \leq i \leq r$。仅当$l - 1 \geq 1$且位置$l - 1$没有书时，才能进行此移动。

你的任务是找出将书架上所有的书收集成一个连续（相邻）区间（即没有任何间隙的区间）所需的最少移动次数。

例如，对于$a = [0, 0, 1, 0, 1]$，书之间有间隙（$a_4 = 0$，而$a_3 = 1$且$a_5 = 1$）；对于$a = [1, 1, 0]$，书之间没有间隙；对于$a = [0, 0, 0]$，书之间也没有间隙。

你必须回答$t$个独立的测试用例。

## 说明/提示
在示例的第一个测试用例中，你可以将区间$[3; 3]$向右移动，将区间$[4; 5]$向右移动。经过所有移动后，书形成连续区间$[5; 7]$。所以答案是$2$。

在示例的第二个测试用例中，你无需做任何操作，书架上所有的书已经形成连续区间。

在示例的第三个测试用例中，你可以将区间$[5; 5]$向左移动，然后再将区间$[4; 4]$向左移动。经过所有移动后，书形成连续区间$[1; 3]$。所以答案是$2$。

在示例的第四个测试用例中，你可以将区间$[1; 1]$向右移动，将区间$[2; 2]$向右移动，将区间$[6; 6]$向左移动，然后再将区间$[5; 5]$向左移动。经过所有移动后，书形成连续区间$[3; 4]$。所以答案是$4$。

在示例的第五个测试用例中，你可以将区间$[1; 2]$向右移动。经过所有移动后，书形成连续区间$[2; 5]$。所以答案是$1$。

## 样例 #1
### 输入
```
5
7
0 0 1 0 1 0 1
3
1 0 0
5
1 1 0 0 1
6
1 0 0 0 0 1
5
1 1 0 1 1
```
### 输出
```
2
0
2
4
1
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路基本一致，都基于贪心策略，即每次移动最多使两段连续的1之间的0的数量减少1 ，贪心地将连续的1从左向右聚拢，最终答案为最左面的1和最右面的1之间的0的数量。各题解的主要差异在于代码实现细节和对输入输出的优化。

### 通用建议与扩展思路
对于此类题目，关键在于理解移动操作对书的分布影响，通过分析操作的性质得出贪心策略。在实现时，注意边界条件的处理以及代码的简洁性和可读性。类似的题目通常围绕如何通过有限操作达到某种特定排列或状态，可通过分析操作对目标状态的影响找到规律。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：同样考查贪心策略，需分析操作对结果的影响并找出最优策略。
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及贪心思想，在多种选择中找到最优决策。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：通过贪心算法解决排队时间优化问题，与本题思路类似。 

---
处理用时：36.72秒