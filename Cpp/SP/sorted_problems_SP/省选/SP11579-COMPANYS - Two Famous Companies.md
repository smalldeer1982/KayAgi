---
title: "COMPANYS - Two Famous Companies"
layout: "post"
diff: 省选/NOI-
pid: SP11579
tag: []
---

# COMPANYS - Two Famous Companies

## 题目描述

In China, there are two companies which offer the internet service for the people from all cities: China Telecom and China Unicom. They both are planning to build cables between cities. The government wants to connect all the cities in minimum costs of course. So the minister of finance Mr. B wants to choose some of the cable plans from the two companies and calculate the minimum cost needed to connect all the cities. Mr. B knows that there are **N**-1 cables should be built in order to connect all **N** cities of China. For some political reason, Mr. B should choose **K** cables from the China Telecom and the rest **N**-1-**K** cables from the China Unicom. Your job is to help Mr. B determine which cables should be built and the minimum cost to build them. You may assume that the solution always exists.

## 输入格式

Each test case starts with a line containing the number of cities **N** (1 <= **N** <= 50,000), number of cable plans **M** (**N**-1 <= **M** <= 100,000) and the number of required cables from China Telecom **K** (0 <= **K** <= **N**-1). This is followed by **M** lines, each containing four integers **a**, **b**, **c**, **x** (0 <= **a**, **b** <= N-1, **a** != **b**, 1 <= **c** <= 100, **x**=\[0,1\]) indicating the pair of cities this cable will connect, the cost to build this cable and the company this cable plan belongs to. **x**=0 denotes this cable plan belongs to China Telecom and **x**=1 denotes this cable plan is from China Unicom.

## 输出格式

For each test case, display the case number and the minimum cost of the cable building plan.

## 样例 #1

### 输入

```
2 2 1
0 1 1 1
0 1 2 0
2 2 0
0 1 1 1
0 1 2 0
```

### 输出

```
Case 1: 2
Case 2: 1
```

