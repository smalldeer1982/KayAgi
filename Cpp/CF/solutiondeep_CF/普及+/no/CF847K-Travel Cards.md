# 题目信息

# Travel Cards

## 题目描述

In the evening Polycarp decided to analyze his today's travel expenses on public transport.

The bus system in the capital of Berland is arranged in such a way that each bus runs along the route between two stops. Each bus has no intermediate stops. So each of the buses continuously runs along the route from one stop to the other and back. There is at most one bus running between a pair of stops.

Polycarp made $ n $ trips on buses. About each trip the stop where he started the trip and the the stop where he finished are known. The trips follow in the chronological order in Polycarp's notes.

It is known that one trip on any bus costs $ a $ burles. In case when passenger makes a transshipment the cost of trip decreases to $ b $ burles ( $ b&lt;a $ ). A passenger makes a transshipment if the stop on which he boards the bus coincides with the stop where he left the previous bus. Obviously, the first trip can not be made with transshipment.

For example, if Polycarp made three consecutive trips: "BerBank" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847K/355fee5161a1808ee95ea5dc6d815d4071657131.png) "University", "University" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847K/355fee5161a1808ee95ea5dc6d815d4071657131.png) "BerMall", "University" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847K/355fee5161a1808ee95ea5dc6d815d4071657131.png) "BerBank", then he payed $ a+b+a=2a+b $ burles. From the BerBank he arrived to the University, where he made transshipment to the other bus and departed to the BerMall. Then he walked to the University and returned to the BerBank by bus.

Also Polycarp can buy no more than $ k $ travel cards. Each travel card costs $ f $ burles. The travel card for a single bus route makes free of charge any trip by this route (in both directions). Once purchased, a travel card can be used any number of times in any direction.

What is the smallest amount of money Polycarp could have spent today if he can buy no more than $ k $ travel cards?

## 说明/提示

In the first example Polycarp can buy travel card for the route "BerBank ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847K/020e46f55824918e845cf09cdcf9e4d7853d3223.png) University" and spend $ 8 $ burles. Note that his second trip "University" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847K/355fee5161a1808ee95ea5dc6d815d4071657131.png) "BerMall" was made after transshipment, so for this trip Polycarp payed $ 3 $ burles. So the minimum total sum equals to $ 8+3=11 $ burles.

In the second example it doesn't make sense to buy travel cards. Note that each of Polycarp trip (except the first) was made with transshipment. So the minimum total sum equals to $ 2+1+1+1=5 $ burles.

## 样例 #1

### 输入

```
3 5 3 1 8
BerBank University
University BerMall
University BerBank
```

### 输出

```
11
```

## 样例 #2

### 输入

```
4 2 1 300 1000
a A
A aa
aa AA
AA a
```

### 输出

```
5
```

# AI分析结果

### 题目内容
# 旅行卡

## 题目描述
晚上，Polycarp决定分析他今天乘坐公共交通的旅行费用。

Berland首都的公交系统是这样安排的：每辆公交车都在两个站点之间的路线上运行。每辆公交车没有中间站点。所以每辆公交车都在两个站点之间不断往返运行。任意两个站点之间最多只有一辆公交车运行。

Polycarp乘坐公交车进行了 $n$ 次出行。关于每次出行，他开始出行的站点和结束出行的站点都是已知的。这些出行在Polycarp的记录中按时间顺序排列。

已知乘坐任何一辆公交车出行一次需要花费 $a$ 卢布。如果乘客进行换乘，出行费用会降低到 $b$ 卢布（$b < a$）。当乘客登上公交车的站点与他离开前一辆公交车的站点重合时，就进行了换乘。显然，第一次出行不能进行换乘。

例如，如果Polycarp连续进行三次出行：“BerBank”→“University”，“University”→“BerMall”，“University”→“BerBank”，那么他需要支付 $a + b + a = 2a + b$ 卢布。他从BerBank到达University，在那里换乘到另一辆公交车并前往BerMall。然后他走到University，再乘坐公交车回到BerBank。

此外，Polycarp最多可以购买 $k$ 张旅行卡。每张旅行卡的价格为 $f$ 卢布。一张针对某条公交路线的旅行卡可以免费乘坐这条路线上的任何行程（双向）。一旦购买，旅行卡可以在任何方向上使用任意次数。

如果Polycarp最多可以购买 $k$ 张旅行卡，那么他今天最少可能花费多少钱？

## 说明/提示
在第一个示例中，Polycarp可以购买“BerBank↔University”路线的旅行卡，花费8卢布。注意，他的第二次出行“University”→“BerMall”是在换乘后进行的，所以这次出行Polycarp支付了3卢布。所以最小总花费等于 $8 + 3 = 11$ 卢布。

在第二个示例中，购买旅行卡没有意义。注意，Polycarp的每次出行（除了第一次）都是在换乘后进行的。所以最小总花费等于 $2 + 1 + 1 + 1 = 5$ 卢布。

## 样例 #1
### 输入
```
3 5 3 1 8
BerBank University
University BerMall
University BerBank
```
### 输出
```
11
```

## 样例 #2
### 输入
```
4 2 1 300 1000
a A
A aa
aa AA
AA a
```
### 输出
```
5
```

### 算法分类
贪心

### 题解综合分析与结论
- **思路**：两题解思路一致，都是先模拟整个旅行过程，计算出每条路线的花费，再将花费按从大到小排序，优先对花费多的路线使用特价券，以达到最小花费。
- **算法要点**：用 `map` 存储站点组合及其对应的总花费，模拟过程中根据是否换乘计算每次行程花费并累加到对应站点组合的总花费中。最后遍历 `map`，将总花费大于特价券价格 `f` 的差值加入数组，排序后取前 `k` 个差值从总花费中减去。
- **解决难点**：如何处理站点名称以及不同行程花费的计算和整合，通过 `map` 结合字符串处理站点名称，根据换乘规则准确计算花费。

### 通用建议与扩展思路
对于此类贪心问题，关键在于找到合理的贪心策略，即优先处理花费大的路线使用特价券。在实现时，注意数据结构的选择，本题使用 `map` 处理站点与花费关系较为合适。类似题目可能会在行程规则、优惠策略等方面进行变化，可通过深入理解本题贪心策略本质来举一反三。

### 相似知识点洛谷题目
1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1948 种地](https://www.luogu.com.cn/problem/P1948)

---
处理用时：31.81秒