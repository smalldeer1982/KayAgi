# 题目信息

# Order Book

## 题目描述

In this task you need to process a set of stock exchange orders and use them to create order book.

An order is an instruction of some participant to buy or sell stocks on stock exchange. The order number $ i $ has price $ p_{i} $ , direction $ d_{i} $ — buy or sell, and integer $ q_{i} $ . This means that the participant is ready to buy or sell $ q_{i} $ stocks at price $ p_{i} $ for one stock. A value $ q_{i} $ is also known as a volume of an order.

All orders with the same price $ p $ and direction $ d $ are merged into one aggregated order with price $ p $ and direction $ d $ . The volume of such order is a sum of volumes of the initial orders.

An order book is a list of aggregated orders, the first part of which contains sell orders sorted by price in descending order, the second contains buy orders also sorted by price in descending order.

An order book of depth $ s $ contains $ s $ best aggregated orders for each direction. A buy order is better if it has higher price and a sell order is better if it has lower price. If there are less than $ s $ aggregated orders for some direction then all of them will be in the final order book.

You are given $ n $ stock exhange orders. Your task is to print order book of depth $ s $ for these orders.

## 说明/提示

Denote (x, y) an order with price $ x $ and volume $ y $ . There are 3 aggregated buy orders (10, 3), (20, 4), (25, 10) and two sell orders (50, 8), (40, 1) in the sample.

You need to print no more than two best orders for each direction, so you shouldn't print the order (10 3) having the worst price among buy orders.

## 样例 #1

### 输入

```
6 2
B 10 3
S 50 2
S 40 1
S 50 6
B 20 4
B 25 10
```

### 输出

```
S 50 8
S 40 1
B 25 10
B 20 4
```

# AI分析结果



# 订单簿

## 题目描述

你需要处理一组证券交易所的订单，并创建订单簿。

订单是参与者在证券交易所买卖股票的指令。第 $i$ 个订单包含价格 $p_i$、方向 $d_i$（买入或卖出）和数量 $q_i$，表示参与者愿意以每股 $p_i$ 的价格买入或卖出 $q_i$ 股。$q_i$ 也称为订单量。

所有相同价格 $p$ 和方向 $d$ 的订单将合并为一个聚合订单，其数量为原始订单数量之和。

订单簿包含两部分：第一部分是卖单按价格升序排列（但输出时需降序输出前 $s$ 个最优卖单），第二部分是买单按价格降序排列的前 $s$ 个最优订单。最优卖单指价格最低的订单，最优买单指价格最高的订单。

给定 $n$ 个订单，输出深度为 $s$ 的订单簿。

## 输入样例

```
6 2
B 10 3
S 50 2
S 40 1
S 50 6
B 20 4
B 25 10
```

## 输出样例

```
S 50 8
S 40 1
B 25 10
B 20 4
```

---

**算法分类**：模拟

---

## 题解综合分析

### 关键思路总结
1. **桶式存储**：利用数组下标直接表示价格，合并同类订单（如 `s[p] += q`）
2. **双阶段处理**：
   - 卖单按价格升序收集前s个，逆序输出实现降序效果
   - 买单直接按价格降序取前s个
3. **边界处理**：注意价格可能为0的情况，以及订单数不足s时的截断

### 最优题解亮点

#### 题解作者：某某某同学（⭐⭐⭐⭐⭐）
**核心思路**：
- 使用两个数组 `s[]` 和 `b[]` 分别存储卖单和买单的聚合数量
- 卖单从价格0开始正向遍历，收集前s个有效订单后逆序输出
- 买单从最高价格反向遍历直接输出前s个订单

**代码片段**：
```cpp
int s[100005], b[100005]; // 价格范围0-1e5
struct out { int cost, num; } sout[1005];

// 处理卖单输出
for(int i=0; i<=100000; i++) {
    if(s[i] != 0 && s1 > 0) {
        sout[s1--] = {i, s[i]}; // 正向收集，逆序存储
    }
}
for(int i=s1+1; i<=s2; i++) {
    cout << "S " << sout[i].cost << " " << sout[i].num << endl;
}

// 处理买单输出
for(int i=100000; i >=0; i--) {
    if(b[i] !=0 && s1-- >0) {
        cout << "B " << i << " " << b[i] << endl;
    }
}
```

#### 题解作者：Fkxxx（⭐⭐⭐⭐）
**核心思路**：
- 使用栈和队列分别处理卖单和买单的输出顺序
- 卖单正向遍历存入栈实现逆序输出，买单反向遍历存入队列

**优化点**：
- 利用STL容器简化逆序逻辑
- 显式处理价格遍历范围（1-1e5）

---

## 拓展建议
1. **同类题目推荐**：
   - [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（优先队列模拟）
   - [P1177 快速排序](https://www.luogu.com.cn/problem/P1177)（排序算法实践）
   - [P1603 斯诺登的密码](https://www.luogu.com.cn/problem/P1603)（多条件排序）

2. **调试技巧**：
   - 特别注意价格0的处理（如样例中可能存在的0元卖单）
   - 使用可视化调试输出中间聚合结果

3. **算法变式**：
   - 若价格范围极大（如1e18），可改用`map`自动排序
   - 若要求实时更新订单簿，需结合优先队列实现

---
处理用时：61.41秒