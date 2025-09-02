# Award Ceremony

## 题目描述

All-Berland programming contest comes to an end. In total, $ n $ teams participated in it. Like in ACM-ICPC, current results stopped refreshing one hour before the contest ends. So at the Award Ceremony, results are partially known. For each team the value $ a_{i} $ is given — the number of points the $ i $ -th team has earned before the last hour of the contest. Besides that, the Jury has evaluated all submissions sent during the last hour and knows values $ d_{i} $ — the number of points earned by the $ i $ -th team during the last hour (these values can be negative, which means that a team can lose points).

Before the contest, each team got unique id from 1 to $ n $ . According to the contest rules, a team with more points takes a higher place. If two or more teams have equal number of points, the team with lower id will take the higher place. So no two teams can share the same place.

The Award Ceremony proceeds in the following way. At the beginning of the ceremony, a large screen shows the results for the time moment "one hour before the end", which means that the $ i $ -th team has $ a_{i} $ points. Then the Jury unfreezes results of the teams one by one in some order. When result of the $ j $ -th team is unfrozen, its score changes from $ a_{j} $ to $ a_{j}+d_{j} $ . At this time the table of results is modified and the place of the team can change. The unfreezing of the $ j $ -th team is followed by the applause from the audience with duration of $ |x_{j}-y_{j}| $ seconds, where $ x_{j} $ is the place of the $ j $ -th team before unfreezing and $ y_{j} $ is the place right after the unfreezing. For example, if the team does not change the place, there is no applause from the audience. As you can see, during the Award Ceremony, each team will be unfrozen exactly once.

Your task is to find such an order to unfreeze all the teams that the total duration of applause is maximum possible.

## 说明/提示

In the first example the initial standings are:

1. Team 2, 52 points
2. Team 1, 17 points
3. Team 4, 6 points
4. Team 3, 1 point

Here any order of unfreezing the teams leads to 4 seconds of applause in total. For example, let's unfreeze teams in their order from the Team 1 to the Team 4.

After the Team 1 became unfrozen the standings are:

1. Team 2, 52 points
2. Team 4, 6 points
3. Team 1, 3 points
4. Team 3, 1 point

So there is 1 second of applause, because the difference between old and new places $ |2-3|=1 $ .

After the Team 2 became unfrozen the standings are:

1. Team 2, 47 points
2. Team 4, 6 points
3. Team 1, 3 points
4. Team 3, 1 point

The place of the Team 2 has not changed, so no applause during unfreezing.

After the Team 3 became unfrozen the standings are:

1. Team 3, 53 point
2. Team 2, 47 points
3. Team 4, 6 points
4. Team 1, 3 points

The place of the Team 3 has changed from 4 to 1, so the duration of applause is $ |4-1|=3 $ .

The unfreezing of the Team 4 has not changed any place because $ d_{4}=0 $ .

Therefore, the total duration of applause is $ 1+0+3+0=4 $ seconds.

## 样例 #1

### 输入

```
4
17 -14
52 -5
1 52
6 0
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
4 5
3 2
5 -3
6 -2
4 3
```

### 输出

```
14
```

# 题解

## 作者：聊机 (赞：1)

去外地训练时讲到的题，很有意思的拓扑排序。

首先注意题面，按照积分从大到小排序，如果积分相等就按 $id$ 从小到大排序，所以任意两个队伍任意时刻一定有大小关系（后文我们就直接用 $a$ 来比较了）。

数据量很小，所以我们考虑任意两个队伍之间的揭榜顺序，对于队伍 $i$，$j$，我们假设 $a[i]>a[j]$，如果揭榜顺序不影响排名变化次数就不用管。剩下就分类讨论就好了。

我们按照 $d$ 同号和异号来考虑。

如果 $d$ 同号，我们就只以加为例，如果 $a[j]+d[j]>a[i]$ 并且 $a[i]+d[i]>a[i]+d[j]$ 那么显然必须让 $i$ 先揭榜，这样排名变化两次，而其他情况不管谁先揭榜，排名变化次数都是一样的，读者可自行思考。$d$ 为负同理。

剩下的就是两个 $d$ 异号，如果小的变小，大的变大显然怎么揭榜排名都不会变，只有小的变大大的变小才有可能变化排名，我们发现，不管是什么顺序如果会变化排名也最多只会变化一次，且与揭榜的顺序无关。

于是拓扑关系确定了，只有同号且会变化两次时需要连边，显然无环。

这题都不用实际连边拓扑，枚举任意两个点，看看有没有先后顺序然后直接计算代价就可以了。

~~不要像我一样傻不拉几还开个链式前向星建图连边，然后“规范”地拓扑，再按顺序模拟计算答案。~~



---

