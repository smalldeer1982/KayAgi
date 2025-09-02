# 题目信息

# Bouquet (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version, instead of listing the number of petals for each flower, the number of petals and the quantity of flowers in the store is set for all types of flowers.

A girl is preparing for her birthday and wants to buy the most beautiful bouquet. There are a total of $ n $ different types of flowers in the store, each of which is characterized by the number of petals and the quantity of this type of flower. A flower with $ k $ petals costs $ k $ coins. The girl has decided that the difference in the number of petals between any two flowers she will use to decorate her cake should not exceed one. At the same time, the girl wants to assemble a bouquet with the maximum possible number of petals. Unfortunately, she only has $ m $ coins, and she cannot spend more. What is the maximum total number of petals she can assemble in the bouquet?

## 说明/提示

In the first test case, some valid bouquets are $ (1, 1, 2, 2), (2, 2, 3), (1, 1), (2, 2) $ . The maximum over all valid bouquets not greater than $ 10 $ is $ 7 $ for $ (2, 2, 3) $ . In the second test case, you can assemble a valid bouquet with $ (206, 206, 207, 207, 207) $ with a sum of $ 1033 $ , which is the maximum number of petals the girl can buy. In the third test case, you can assemble a valid bouquet with $ (5, 5, 5, 4) $ with a sum of $ 19 $ . It can be seen that no valid bouquet can have $ 20 $ petals.

## 样例 #1

### 输入

```
7
3 10
1 2 3
2 2 1
3 1033
206 207 1000
3 4 1
6 20
4 2 7 5 6 1
1 2 1 3 1 7
8 100000
239 30 610 122 24 40 8 2
12 13123 112 1456 124 100 123 10982
6 13
2 4 11 1 3 5
2 2 1 2 2 1
8 10330
206 210 200 201 198 199 222 1000
9 10 11 12 13 14 15 16
2 10000000000
11 12
87312315 753297050```

### 输出

```
7
1033
19
99990
13
10000
9999999999```

# AI分析结果



### 题目翻译
# Bouquet（困难版）

## 题目描述

这是该问题的困难版本。唯一区别在于，此版本中所有类型的花的花瓣数和数量都是预设的，而不是逐个列举每朵花的花瓣数。

一个女孩准备生日，想购买最美丽的花束。花店共有 $n$ 种不同类型的花，每种类型的花具有固定的花瓣数和数量。一朵有 $k$ 片花瓣的花价值 $k$ 枚硬币。女孩决定，花束中任意两朵花的花瓣数之差不得超过 1。同时，她希望花束的花瓣总数尽可能大。她只有 $m$ 枚硬币，不能超支。她最多能获得多少片花瓣？

## 说明/提示

样例说明详见原题。

---

### 题解分析与结论

#### 关键思路总结
1. **排序预处理**：将所有花按花瓣数升序排序，便于处理相邻花瓣数的情况。
2. **单一种类处理**：对每种花单独计算最大购买量（全选该类型）。
3. **相邻花瓣数组合**：对每个相邻花瓣数对（$x$ 和 $x+1$），通过贪心策略：
   - 先尽可能多买低价花（$x$），剩余资金买高价花（$x+1$）。
   - 替换优化：用剩余资金将部分 $x$ 的花替换为 $x+1$ 的花（每次替换增加 1 花瓣，需花费 1 硬币）。

#### 最优解核心逻辑
- **贪心购买**：优先填满低价花，再用剩余资金购买高价花。
- **替换次数计算**：替换次数受限于三个因素：已购 $x$ 花数量、剩余高价花数量、剩余资金。

---

### 高星题解推荐

#### 1. 作者：Eraine（★★★★☆）
**亮点**：精炼的调整策略分析，提出替换思想。
**思路**：先填满 $x$ 的花，再调整替换为 $x+1$ 的花。通过剩余资金和库存限制计算替换次数。
```cpp
// 核心替换逻辑
int sum0 = min(可用x花数量, m/x的购买上限);
int sum1 = min(可用x+1花数量, (m - sum0*x)/(x+1));
int rem = m - sum0*x - sum1*(x+1);
int replace_times = min({sum0, (x+1花总数 - sum1), rem});
最终值 = sum0*x + sum1*(x+1) + replace_times;
```

#### 2. 作者：ANDER_（★★★★☆）
**亮点**：代码清晰，完整处理相邻对情况。
**核心代码**：
```cpp
for (auto i : vec) {
    if (相邻花瓣差为1) {
        int tmp = min(当前x库存, m/x价格); // 购买x花
        int tmp2 = m - tmp * x价格; 
        int tmp1 = min(x+1库存, tmp2/(x+1价格)); // 购买x+1花
        tmp2 -= tmp1 * (x+1价格);
        // 计算替换次数并更新结果
        res = max(res, m - tmp2 + min({tmp2, x+1剩余库存, tmp}));
    }
}
```

#### 3. 作者：nightwatch.ryan（★★★☆☆）
**亮点**：使用map简化数据管理，直观处理替换。
```cpp
for (auto [x, y] : mp) {
    int ans = x * min(y, m/x); // 单买x花
    if (存在x+1花) {
        int remain = m - ans;
        int cnt = min(剩余钱/(x+1), x+1库存);
        ans += cnt*(x+1);
        ans += min({已买x花数量, x+1剩余库存, remain - cnt*(x+1)});
    }
}
```

---

### 相似题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心+优先队列。
2. [P1209 修理牛棚](https://www.luogu.com.cn/problem/P1209) - 贪心处理区间覆盖。
3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995) - 贪心排序+交替选择。

---
处理用时：85.09秒