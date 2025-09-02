# 题目信息

# Seating Arrangements (easy version)

## 题目描述

It is the easy version of the problem. The only difference is that in this version $ n = 1 $ .

In the cinema seats can be represented as the table with $ n $ rows and $ m $ columns. The rows are numbered with integers from $ 1 $ to $ n $ . The seats in each row are numbered with consecutive integers from left to right: in the $ k $ -th row from $ m (k - 1) + 1 $ to $ m k $ for all rows $ 1 \le k \le n $ .

  $ 1 $

 $ 2 $  $ \cdots $  $ m - 1 $  $ m $  $ m + 1 $

 $ m + 2 $  $ \cdots $  $ 2 m - 1 $  $ 2 m $  $ 2m + 1 $

 $ 2m + 2 $  $ \cdots $  $ 3 m - 1 $  $ 3 m $  $ \vdots $

 $ \vdots $  $ \ddots $  $ \vdots $  $ \vdots $  $ m (n - 1) + 1 $

 $ m (n - 1) + 2 $  $ \cdots $  $ n m - 1 $  $ n m $ The table with seats indicesThere are $ nm $ people who want to go to the cinema to watch a new film. They are numbered with integers from $ 1 $ to $ nm $ . You should give exactly one seat to each person.

It is known, that in this cinema as lower seat index you have as better you can see everything happening on the screen. $ i $ -th person has the level of sight $ a_i $ . Let's define $ s_i $ as the seat index, that will be given to $ i $ -th person. You want to give better places for people with lower sight levels, so for any two people $ i $ , $ j $ such that $ a_i < a_j $ it should be satisfied that $ s_i < s_j $ .

After you will give seats to all people they will start coming to their seats. In the order from $ 1 $ to $ nm $ , each person will enter the hall and sit in their seat. To get to their place, the person will go to their seat's row and start moving from the first seat in this row to theirs from left to right. While moving some places will be free, some will be occupied with people already seated. The inconvenience of the person is equal to the number of occupied seats he or she will go through.

Let's consider an example: $ m = 5 $ , the person has the seat $ 4 $ in the first row, the seats $ 1 $ , $ 3 $ , $ 5 $ in the first row are already occupied, the seats $ 2 $ and $ 4 $ are free. The inconvenience of this person will be $ 2 $ , because he will go through occupied seats $ 1 $ and $ 3 $ .

Find the minimal total inconvenience (the sum of inconveniences of all people), that is possible to have by giving places for all people (all conditions should be satisfied).

## 说明/提示

In the first test case, there is a single way to arrange people, because all sight levels are distinct. The first person will sit on the first seat, the second person will sit on the second place, the third person will sit on the third place. So inconvenience of the first person will be $ 0 $ , inconvenience of the second person will be $ 1 $ and inconvenience of the third person will be $ 2 $ . The total inconvenience is $ 0 + 1 + 2 = 3 $ .

In the second test case, people should sit as follows: $ s_1 = 2 $ , $ s_2 = 1 $ , $ s_3 = 5 $ , $ s_4 = 4 $ , $ s_5 = 3 $ . The total inconvenience will be $ 6 $ .

## 样例 #1

### 输入

```
4
1 3
1 2 3
1 5
2 1 5 3 3
1 2
2 1
1 6
2 3 2 1 1 1```

### 输出

```
3
6
0
1```

# AI分析结果

### 题目内容
# 座位安排（简单版）

## 题目描述
这是该问题的简单版本。唯一的区别在于，在这个版本中\(n = 1\)。

在电影院中，座位可以表示为一个\(n\)行\(m\)列的表格。行用从\(1\)到\(n\)的整数编号。每行中的座位从左到右用连续的整数编号：对于所有\(1 \leq k \leq n\)的行，在第\(k\)行中，从\(m(k - 1) + 1\)到\(mk\)。

  \(1\)

 \(2\)  \( \cdots\)  \(m - 1\)  \(m\)  \(m + 1\)

 \(m + 2\)  \( \cdots\)  \(2m - 1\)  \(2m\)  \(2m + 1\)

 \(2m + 2\)  \( \cdots\)  \(3m - 1\)  \(3m\)  \( \vdots\)

 \( \vdots\)  \( \ddots\)  \( \vdots\)  \( \vdots\)  \(m(n - 1) + 1\)

 \(m(n - 1) + 2\)  \( \cdots\)  \(nm - 1\)  \(nm\)  带有座位索引的表格

有\(nm\)个人想去电影院看一部新电影。他们用从\(1\)到\(nm\)的整数编号。你应该给每个人恰好安排一个座位。

已知在这个电影院中，座位索引越小，你就越能清楚地看到屏幕上发生的一切。第\(i\)个人有视力水平\(a_i\)。我们定义\(s_i\)为将分配给第\(i\)个人的座位索引。你想给视力水平较低的人安排更好的座位，所以对于任意两个人\(i\)，\(j\)，如果\(a_i < a_j\)，则应该满足\(s_i < s_j\)。

在你给所有人安排好座位后，他们将开始前往自己的座位。按照从\(1\)到\(nm\)的顺序，每个人将进入大厅并坐在自己的座位上。为了到达自己的位置，这个人将走到自己座位所在的行，并从该行的第一个座位开始从左到右移动。在移动过程中，一些座位将是空的，一些座位将被已经就座的人占据。这个人的不便程度等于他或她将经过的已被占据的座位数。

让我们考虑一个例子：\(m = 5\)，这个人在第一行的座位是\(4\)，第一行的座位\(1\)、\(3\)、\(5\)已经被占据，座位\(2\)和\(4\)是空的。这个人的不便程度将是\(2\)，因为他将经过已被占据的座位\(1\)和\(3\)。

找到在给所有人安排座位时（所有条件都应满足）可能出现的最小总不便程度（所有人不便程度的总和）。

## 说明/提示
在第一个测试用例中，由于所有视力水平都不同，所以只有一种安排人的方式。第一个人将坐在第一个座位上，第二个人将坐在第二个座位上，第三个人将坐在第三个座位上。所以第一个人的不便程度将是\(0\)，第二个人的不便程度将是\(1\)，第三个人的不便程度将是\(2\)。总不便程度是\(0 + 1 + 2 = 3\)。

在第二个测试用例中，人们应该如下就座：\(s_1 = 2\)，\(s_2 = 1\)，\(s_3 = 5\)，\(s_4 = 4\)，\(s_5 = 3\)。总不便程度将是\(6\)。

## 样例 #1
### 输入
```
4
1 3
1 2 3
1 5
2 1 5 3 3
1 2
2 1
1 6
2 3 2 1 1 1
```
### 输出
```
3
6
0
1
```
### 算法分类
贪心

### 题解综合分析与结论
所有题解都基于贪心策略，利用\(n = 1\)的条件简化问题为一维数组处理。思路核心是让视力差（视力值小）的人尽量靠前坐，统计每个人就座时经过已坐人的座位数（即前面视力比自己差的人数）来计算总不便值。各题解主要差异在于代码实现的细节，如变量命名、输入输出方式、代码风格等，整体算法复杂度均为\(O(m^2t)\)，未做优化。

### 通用建议与扩展思路
通用建议：在实现时注意变量初始化、边界条件处理，增强代码可读性。
扩展思路：若取消\(n = 1\)的限制，可考虑用树状数组优化每行的统计过程，降低时间复杂度。也可进一步拓展到更复杂的座位布局和人员安排条件。

### 相似知识点洛谷题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略解决合并问题，与本题贪心思想类似。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：利用贪心思路对排队顺序进行优化，与本题优化总代价思路一致。
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：同样是基于贪心算法，分析不同元素排列顺序对结果的影响。 

---
处理用时：59.74秒