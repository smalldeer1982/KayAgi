# [NERC 2021] Kingdom Partition

## 题目描述

国王已逝。在国王统治结束后，王国中的所有道路都已年久失修，需要修复。国王的三个孩子 Adrian、Beatrice 和 Cecilia 正在商议如何将王国划分为三个区域。

Adrian 和 Beatrice 彼此不和，未来也不打算维持任何关系。Cecilia 与他们两人关系良好。此外，王国的大多数工人都支持 Cecilia，因此她拥有更好的资源和更多机会来修复基础设施并发展经济。

Cecilia 提议将王国划分为三个区域：A（Adrian 的领地）、B（Beatrice 的领地）和 C（Cecilia 的领地），并让 Adrian 和 Beatrice 协商选择他们希望纳入各自领地的城镇，并商定如何将王国划分为三个区域。

Adrian 的城堡位于城镇 $a$，Beatrice 的城堡位于城镇 $b$。因此，Adrian 和 Beatrice 希望他们的城堡分别位于区域 A 和 B。Cecilia 没有城堡，因此区域 C 可以没有城镇。

Adrian 和 Beatrice 在选择城镇时面临一个问题：他们需要承担道路修复的费用。

一条长度为 $l$ 的道路的修复成本为 $2l$ 金币。然而，Adrian 和 Beatrice 不必承担全部修复费用。根据道路连接的城镇所属区域，他们需要承担的费用如下：

- 对于连接两个区域 A 内城镇的道路，Adrian 需要支付 $2l$ 金币；
- 对于连接两个区域 B 内城镇的道路，Beatrice 需要支付 $2l$ 金币；
- 对于连接区域 A 和区域 C 城镇的道路，Adrian 需要支付 $l$ 金币，Cecilia 承担剩余费用；
- 对于连接区域 B 和区域 C 城镇的道路，Beatrice 需要支付 $l$ 金币，Cecilia 承担剩余费用。

连接区域 A 和区域 B 城镇的道路不会被修复，因为 Adrian 和 Beatrice 不打算使用它们，因此无人支付其费用。Cecilia 会自行修复连接区域 C 内城镇的道路，因此 Adrian 和 Beatrice 也不需承担这些道路的修复费用。

Adrian 和 Beatrice 希望最小化他们在道路修复上的总支出。请找出他们划分王国为三个区域的最经济方案。

## 说明/提示

下图展示了示例的划分方案。Adrian 和 Beatrice 无需为虚线道路支付费用，为粗线道路支付 $2l$，为实线道路支付 $l$。

因此，总成本为 $2 \cdot 5 + 3 + 3 = 16$。

Adrian 和 Beatrice 的城堡位于加粗的城镇中。

![](https://cdn.luogu.com.cn/upload/image_hosting/11ffx3k7.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6 7
1 3
1 2 10
2 3 5
1 3 7
4 5 3
3 6 100
4 6 3
5 6 8```

### 输出

```
16
ABBCBA```

