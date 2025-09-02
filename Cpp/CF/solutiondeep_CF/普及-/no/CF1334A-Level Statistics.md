# 题目信息

# Level Statistics

## 题目描述

Polycarp has recently created a new level in this cool new game Berlio Maker 85 and uploaded it online. Now players from all over the world can try his level.

All levels in this game have two stats to them: the number of plays and the number of clears. So when a player attempts the level, the number of plays increases by $ 1 $ . If he manages to finish the level successfully then the number of clears increases by $ 1 $ as well. Note that both of the statistics update at the same time (so if the player finishes the level successfully then the number of plays will increase at the same time as the number of clears).

Polycarp is very excited about his level, so he keeps peeking at the stats to know how hard his level turns out to be.

So he peeked at the stats $ n $ times and wrote down $ n $ pairs of integers — $ (p_1, c_1), (p_2, c_2), \dots, (p_n, c_n) $ , where $ p_i $ is the number of plays at the $ i $ -th moment of time and $ c_i $ is the number of clears at the same moment of time. The stats are given in chronological order (i.e. the order of given pairs is exactly the same as Polycarp has written down).

Between two consecutive moments of time Polycarp peeked at the stats many players (but possibly zero) could attempt the level.

Finally, Polycarp wonders if he hasn't messed up any records and all the pairs are correct. If there could exist such a sequence of plays (and clears, respectively) that the stats were exactly as Polycarp has written down, then he considers his records correct.

Help him to check the correctness of his records.

For your convenience you have to answer multiple independent test cases.

## 说明/提示

In the first test case at the third moment of time the number of clears increased but the number of plays did not, that couldn't have happened.

The second test case is a nice example of a Super Expert level.

In the third test case the number of plays decreased, which is impossible.

The fourth test case is probably an auto level with a single jump over the spike.

In the fifth test case the number of clears decreased, which is also impossible.

Nobody wanted to play the sixth test case; Polycarp's mom attempted it to make him feel better, however, she couldn't clear it.

## 样例 #1

### 输入

```
6
3
0 0
1 1
1 2
2
1 0
1000 3
4
10 1
15 2
10 2
15 2
1
765 432
2
4 4
4 3
5
0 0
1 0
1 0
1 0
1 0```

### 输出

```
NO
YES
NO
YES
NO
YES```

# AI分析结果

### 题目内容
# 关卡统计

## 题目描述
Polycarp 最近在一款超酷的新游戏《Berlio Maker 85》中创建了一个新关卡，并上传到了网上。现在，世界各地的玩家都可以尝试他设计的关卡。

这款游戏中所有关卡都有两个统计数据：游玩次数和通关次数。每当有玩家尝试该关卡时，游玩次数就会增加 1。如果玩家成功完成关卡，那么通关次数也会增加 1。请注意，这两个统计数据是同时更新的（也就是说，如果玩家成功通关，游玩次数和通关次数会同时增加）。

Polycarp 对自己设计的关卡非常兴奋，所以他不时查看统计数据，想知道这个关卡的难度究竟如何。

他查看了统计数据 $n$ 次，并记录下了 $n$ 对整数 —— $(p_1, c_1), (p_2, c_2), \dots, (p_n, c_n)$，其中 $p_i$ 表示在第 $i$ 个时间点的游玩次数，$c_i$ 表示在同一时间点的通关次数。这些统计数据是按时间顺序给出的（即给出的数对顺序与 Polycarp 记录的顺序完全相同）。

在 Polycarp 两次查看统计数据的间隔时间内，可能有许多玩家（也可能是零个玩家）尝试了该关卡。

最后，Polycarp 想知道自己是否记录有误，所有记录的数对是否都正确。如果存在这样一个游玩（以及相应通关）的序列，使得统计数据与 Polycarp 记录的完全一致，那么他认为自己的记录是正确的。

请帮助他检查记录的正确性。

为了方便你解题，本题需要回答多个独立的测试用例。

## 说明/提示
在第一个测试用例中，在第三个时间点，通关次数增加了，但游玩次数没有增加，这是不可能发生的。

第二个测试用例是一个超级专家级关卡的很好例子。

在第三个测试用例中，游玩次数减少了，这是不可能的。

第四个测试用例可能是一个只需跳过一个尖刺的自动关卡。

在第五个测试用例中，通关次数减少了，这也是不可能的。

没有人想玩第六个测试用例；Polycarp 的妈妈为了让他感觉好一些尝试了一下，但她没能通关。

## 样例 #1
### 输入
```
6
3
0 0
1 1
1 2
2
1 0
1000 3
4
10 1
15 2
10 2
15 2
1
765 432
2
4 4
4 3
5
0 0
1 0
1 0
1 0
1 0
```

### 输出
```
NO
YES
NO
YES
NO
YES
```

• **算法分类**：模拟
• **综合分析与结论**：这些题解的核心思路都是通过判断游玩次数和通关次数的关系来确定记录是否正确。要点在于明确游玩次数不能小于通关次数，且两者都不能随时间减少，每次游玩次数的增加量要大于等于通关次数的增加量。各题解在实现上略有不同，有的使用打标记的方式避免提前输出影响输入，有的通过数组存储数据后统一判断，有的则直接在输入过程中进行判断。解决难点主要在于全面考虑所有可能导致记录错误的情况，避免遗漏。
• **通用建议与扩展思路**：此类模拟题关键在于准确梳理题目中的逻辑关系，将实际场景转化为代码中的条件判断。对于类似题目，要仔细分析数据之间的内在联系和变化规律，确保考虑全面。可拓展到其他具有类似统计性质的场景，如比赛的参与人数和获胜人数统计等，同样需关注数量的增减关系及大小比较。
• **推荐题目**：
  - [P1035 级数求和](https://www.luogu.com.cn/problem/P1035)
  - [P1425 小鱼的游泳时间](https://www.luogu.com.cn/problem/P1425)
  - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909) 

---
处理用时：32.59秒