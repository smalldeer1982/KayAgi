# 题目信息

# Cupboards

## 题目描述

One foggy Stockholm morning, Karlsson decided to snack on some jam in his friend Lillebror Svantenson's house. Fortunately for Karlsson, there wasn't anybody in his friend's house. Karlsson was not going to be hungry any longer, so he decided to get some food in the house.

Karlsson's gaze immediately fell on $ n $ wooden cupboards, standing in the kitchen. He immediately realized that these cupboards have hidden jam stocks. Karlsson began to fly greedily around the kitchen, opening and closing the cupboards' doors, grab and empty all the jars of jam that he could find.

And now all jars of jam are empty, Karlsson has had enough and does not want to leave traces of his stay, so as not to let down his friend. Each of the cupboards has two doors: the left one and the right one. Karlsson remembers that when he rushed to the kitchen, all the cupboards' left doors were in the same position (open or closed), similarly, all the cupboards' right doors were in the same position (open or closed). Karlsson wants the doors to meet this condition as well by the time the family returns. Karlsson does not remember the position of all the left doors, also, he cannot remember the position of all the right doors. Therefore, it does not matter to him in what position will be all left or right doors. It is important to leave all the left doors in the same position, and all the right doors in the same position. For example, all the left doors may be closed, and all the right ones may be open.

Karlsson needs one second to open or close a door of a cupboard. He understands that he has very little time before the family returns, so he wants to know the minimum number of seconds $ t $ , in which he is able to bring all the cupboard doors in the required position.

Your task is to write a program that will determine the required number of seconds $ t $ .

## 样例 #1

### 输入

```
5
0 1
1 0
0 1
1 1
0 1
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# Cupboards

## 题目描述
在一个大雾弥漫的斯德哥尔摩的早晨，卡尔松决定在他朋友 Lillebror Svantenson 的家里吃点果酱。幸运的是，他朋友家里没有人。卡尔松再也不想挨饿了，所以他决定在家里找点吃的。

卡尔松的目光立刻落在了厨房里的 $n$ 个木橱柜上。他立刻意识到这些橱柜里藏着果酱。卡尔松开始贪婪地在厨房里飞来飞去，打开和关闭橱柜的门，抓起并清空他能找到的所有果酱罐。

现在所有的果酱罐都空了，卡尔松吃饱了，并且不想留下他来过的痕迹，以免让他的朋友失望。每个橱柜都有两扇门：左边一扇和右边一扇。卡尔松记得，当他冲进厨房时，所有橱柜的左边门都处于相同的位置（开或关），同样，所有橱柜的右边门也都处于相同的位置（开或关）。卡尔松希望在这家人回来的时候，门也能满足这个条件。卡尔松不记得所有左边门的位置，也不记得所有右边门的位置。因此，对他来说，所有左边门或右边门处于什么位置并不重要。重要的是让所有左边门处于相同的位置，并且所有右边门处于相同的位置。例如，所有左边门可以是关闭的，而所有右边门可以是打开的。

卡尔松打开或关闭一个橱柜的一扇门需要一秒钟。他知道在这家人回来之前他的时间非常少，所以他想知道他能够将所有橱柜门调整到所需位置的最短时间 $t$ 是多少秒。

你的任务是编写一个程序来确定所需的时间 $t$ 。

## 样例 #1
### 输入
```
5
0 1
1 0
0 1
1 1
0 1
```
### 输出
```
3
```
• **算法分类**：数学
• **综合分析与结论**：这些题解思路基本一致，都是将问题转化为分别统计两列01数组中0和1的个数，然后取每列中0和1个数的较小值，最后将两列的较小值相加得到最小操作次数。题解的主要区别在于代码实现方式，如变量命名、输入处理方式、是否使用函数等细节方面。
• **通用建议与扩展思路**：此类题目核心在于理解将问题简化为统计与比较01个数。对于类似题目，可尝试从数据特征出发，寻找简化问题的方法。同类型题可涉及更多不同条件限制下的状态调整与最小操作次数计算，如对状态有多种取值，或操作存在不同代价等。
• **洛谷相似题目**：
  - P1036 [选数](https://www.luogu.com.cn/problem/P1036)
  - P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)
  - P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)

---
处理用时：17.41秒