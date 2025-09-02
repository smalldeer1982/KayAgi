---
title: "Gift"
layout: "post"
diff: 省选/NOI-
pid: CF76A
tag: ['排序', '生成树', '栈']
---

# Gift

## 题目描述

The kingdom of Olympia consists of $ N $ cities and $ M $ bidirectional roads. Each road connects exactly two cities and two cities can be connected with more than one road. Also it possible that some roads connect city with itself making a loop.

All roads are constantly plundered with bandits. After a while bandits became bored of wasting time in road robberies, so they suggested the king of Olympia to pay off. According to the offer, bandits want to get a gift consisted of gold and silver coins. Offer also contains a list of restrictions: for each road it is known $ g_{i} $ — the smallest amount of gold and $ s_{i} $ — the smallest amount of silver coins that should be in the gift to stop robberies on the road. That is, if the gift contains $ a $ gold and $ b $ silver coins, then bandits will stop robberies on all the roads that $ g_{i}<=a $ and $ s_{i}<=b $ .

Unfortunately kingdom treasury doesn't contain neither gold nor silver coins, but there are Olympian tugriks in it. The cost of one gold coin in tugriks is $ G $ , and the cost of one silver coin in tugriks is $ S $ . King really wants to send bandits such gift that for any two cities there will exist a safe path between them. Your task is to find the minimal cost in Olympian tugriks of the required gift.

## 输入格式

The first line of the input contains two integers $ N $ and $ M $ ( $ 2<=N<=200 $ , $ 1<=M<=50000 $ ) — the number of cities and the number of roads, respectively. The second line contains two integers $ G $ and $ S $ ( $ 1<=G,S<=10^{9} $ ) — the prices of gold and silver coins in tugriks. The following $ M $ lines contain information about the offer. Each of the records in list is given as four integers $ x_{i},y_{i},g_{i},s_{i} $ , where $ x_{i} $ and $ y_{i} $ are the numbers of cities that the road connects and $ g_{i} $ , $ s_{i} $ are minimal gold and silver coins requirements for the $ i $ -th road ( $ 1<=x_{i},y_{i}<=N $ , $ 1<=g_{i},s_{i}<=10^{9} $ ). Cities are numbered from $ 1 $ to $ N $ . It is possible that there are more than one road between a pair of cities. It is possible that a road connects the city with itself.

## 输出格式

The output should contain the minimal cost of the gift in Olympian tugriks. If there is no gift that satisfies the given requirements output ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF76A/843ffcb025f9d699cf4e412e21508ca44c9ae26c.png).

## 样例 #1

### 输入

```
3 3
2 1
1 2 10 15
1 2 4 20
1 3 5 1

```

### 输出

```
30

```

