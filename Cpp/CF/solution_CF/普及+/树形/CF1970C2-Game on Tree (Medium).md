# Game on Tree (Medium)

## 题目描述

This is the medium version of the problem. The difference in this version is that $ t=1 $ and we work on trees.

Ron and Hermione are playing a game on a tree of $ n $ nodes that are initially inactive. The game consists of $ t $ rounds, each of which starts with a stone on exactly one node, which is considered as activated. A move consists of picking an inactive neighbor of the node with a stone on it and moving the stone there (thus activating this neighbor). Ron makes the first move, after which he alternates with Hermione until no valid move is available. The player that cannot make a move loses the round. If both players play optimally, who wins each round of this game?

Note that all the rounds are played with the same tree; only the starting node changes. Moreover, after each round, all active nodes are considered inactive again.

## 样例 #1

### 输入

```
5 1
1 2
1 3
3 4
3 5
1```

### 输出

```
Ron```

# 题解

## 作者：shicj (赞：1)

# CF1970C2 Game on Tree (Medium) 题解

## 0x00 题目大意

给出一棵树，在一个点上放一个棋子，两人轮流移动棋子到相邻位置，不可重复经过某个点，两人决策最优，问谁获胜。

## 0x01 初步分析

看一下样例，画个图分析一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/0io4uryf.png)

然后看一下可以怎样移动：

![](https://cdn.luogu.com.cn/upload/image_hosting/zfpmlecn.png)

发现每一条路径都去往叶子节点，显而易见，每个叶子节点的状态是确定的：

![](https://cdn.luogu.com.cn/upload/image_hosting/m74g6b5a.png)

这个状态可以很快求出，接下来研究如何向上转移。

## 0x02 深入分析

由于叶子节点状态已知，所以考虑自底向上分析。

在这里，每一个节点上由谁选择（移到下一个点）很重要，我们用绿色字体标出每个节点上由谁选择：

![](https://cdn.luogu.com.cn/upload/image_hosting/rzxr6l98.png)

可以看出，由谁选择取决于节点的深度。

易得，在最优决策中，总是要选择可以使得自己获胜的点，如果没有，则在这一点上出发对方获胜，否则自己获胜。

于是可以自底向上标出每一个点上的获胜者：

![](https://cdn.luogu.com.cn/upload/image_hosting/o61pt5b6.png)

这时看一看起始节点上谁获胜就行了。

# 0x03 具体实现

在代码中，可以如图中用字符表示状态（这样直观但代码量大），但更推荐用布尔值来实现，这样可以把判断获胜者的运算转化为深度模 $2$ 和逻辑运算，具体的写法可以自己琢磨。

求获胜者的步骤可以直接写在搜索的回溯部分，这样便于实现。

# 0x04 正确代码

建议略过这部分，自己思考。

[link](https://codeforces.com/problemset/submission/1970/272718480)

---

