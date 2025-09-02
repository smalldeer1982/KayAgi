# 题目信息

# Unique Bid Auction

## 题目描述

There is a game called "Unique Bid Auction". You can read more about it here: <a>https://en.wikipedia.org/wiki/Unique\_bid\_auction</a> (though you don't have to do it to solve this problem).

Let's simplify this game a bit. Formally, there are $ n $ participants, the $ i $ -th participant chose the number $ a_i $ . The winner of the game is such a participant that the number he chose is unique (i. e. nobody else chose this number except him) and is minimal (i. e. among all unique values of $ a $ the minimum one is the winning one).

Your task is to find the index of the participant who won the game (or -1 if there is no winner). Indexing is $ 1 $ -based, i. e. the participants are numbered from $ 1 $ to $ n $ .

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
6
2
1 1
3
2 1 3
4
2 2 2 3
1
1
5
2 3 2 4 2
6
1 1 5 5 4 4```

### 输出

```
-1
2
4
1
2
-1```

# AI分析结果

### 题目内容
# 唯一出价拍卖

## 题目描述
有一个叫做“唯一出价拍卖”的游戏。你可以在这里阅读更多关于它的信息：<a>https://en.wikipedia.org/wiki/Unique_bid_auction</a> （不过解决这个问题你不必这么做）。

让我们稍微简化一下这个游戏。正式地说，有 $n$ 个参与者，第 $i$ 个参与者选择了数字 $a_i$ 。游戏的获胜者是这样一个参与者：他选择的数字是唯一的（即除了他之外没有其他人选择这个数字）并且是最小的（即在所有唯一的 $a$ 值中，最小的那个是获胜的）。

你的任务是找到赢得游戏的参与者的索引（如果没有获胜者则为 -1）。索引从 1 开始，即参与者从 1 到 $n$ 编号。

你必须回答 $t$ 个独立的测试用例。

## 样例 #1
### 输入
```
6
2
1 1
3
2 1 3
4
2 2 2 3
1
1
5
2 3 2 4 2
6
1 1 5 5 4 4
```
### 输出
```
-1
2
4
1
2
-1
```
### 算法分类
无算法分类
### 综合分析与结论
这些题解的核心思路都是先统计每个数字出现的次数，然后找出出现次数为1且值最小的数字对应的下标。不同题解在实现方式上有所差异，有的使用数组统计，有的使用`map`，有的使用结构体等。在优化方面，部分题解通过记录最大值来减少遍历范围，有的使用优先队列来自动排序等。

### 通用建议与扩展思路
通用建议：在实现时，要注意数据结构的选择对时间复杂度的影响，比如`map`的查找和插入时间复杂度在平均情况下较好，但在最坏情况下不如数组直接寻址。同时要注意边界条件的处理，如所有数字都不唯一时输出 -1。

扩展思路：同类型题可以考虑增加更多限制条件，比如获胜者的数字不仅要唯一且最小，还需要满足其他条件，如数字必须是偶数等。类似的算法套路可以应用在其他需要统计元素出现次数并根据特定条件查找元素的场景中。

### 洛谷题目推荐
1. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)：涉及数组统计和条件判断查找，与本题统计数字出现次数并按条件查找有相似之处。
2. [P1131 海战](https://www.luogu.com.cn/problem/P1131)：需要统计特定形状的元素出现情况，与本题统计数字出现次数类似。
3. [P1970 花匠](https://www.luogu.com.cn/problem/P1970)：同样是对数组元素进行统计和根据条件查找，不过条件更复杂一些，可以锻炼类似的思维。 

---
处理用时：25.95秒