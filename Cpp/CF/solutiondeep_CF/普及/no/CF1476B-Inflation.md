# 题目信息

# Inflation

## 题目描述

You have a statistic of price changes for one product represented as an array of $ n $ positive integers $ p_0, p_1, \dots, p_{n - 1} $ , where $ p_0 $ is the initial price of the product and $ p_i $ is how the price was increased during the $ i $ -th month.

Using these price changes you are asked to calculate the inflation coefficients for each month as the ratio of current price increase $ p_i $ to the price at the start of this month $ (p_0 + p_1 + \dots + p_{i - 1}) $ .

Your boss said you clearly that the inflation coefficients must not exceed $ k $ %, so you decided to increase some values $ p_i $ in such a way, that all $ p_i $ remain integers and the inflation coefficients for each month don't exceed $ k $ %.

You know, that the bigger changes — the more obvious cheating. That's why you need to minimize the total sum of changes.

What's the minimum total sum of changes you need to make all inflation coefficients not more than $ k $ %?

## 说明/提示

In the first test case, you can, for example, increase $ p_0 $ by $ 50 $ and $ p_1 $ by $ 49 $ and get array $ [20150, 50, 202, 202] $ . Then you get the next inflation coefficients:

1. $ \frac{50}{20150} \le \frac{1}{100} $ ;
2. $ \frac{202}{20150 + 50} \le \frac{1}{100} $ ;
3. $ \frac{202}{20200 + 202} \le \frac{1}{100} $ ;

In the second test case, you don't need to modify array $ p $ , since the inflation coefficients are already good:

1. $ \frac{1}{1} \le \frac{100}{100} $ ;
2. $ \frac{1}{1 + 1} \le \frac{100}{100} $ ;

## 样例 #1

### 输入

```
2
4 1
20100 1 202 202
3 100
1 1 1```

### 输出

```
99
0```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

你有一个产品的价格变化统计，表示为一个包含 $n$ 个正整数的数组 $p_0, p_1, \dots, p_{n - 1}$，其中 $p_0$ 是产品的初始价格，$p_i$ 是第 $i$ 个月的价格增加量。

使用这些价格变化，你需要计算每个月的通货膨胀系数，即当前价格增加量 $p_i$ 与本月开始时价格 $(p_0 + p_1 + \dots + p_{i - 1})$ 的比值。

你的老板明确表示，通货膨胀系数不能超过 $k\%$，因此你决定增加某些 $p_i$ 的值，使得所有 $p_i$ 仍为整数，且每个月的通货膨胀系数不超过 $k\%$。

你知道，改动越大，作弊越明显。因此，你需要最小化所有改动的总和。

你需要计算出使所有通货膨胀系数不超过 $k\%$ 的最小改动总和。

#### 说明/提示

在第一个测试用例中，你可以将 $p_0$ 增加 $50$，$p_1$ 增加 $49$，得到数组 $[20150, 50, 202, 202]$。然后你得到以下通货膨胀系数：

1. $\frac{50}{20150} \le \frac{1}{100}$；
2. $\frac{202}{20150 + 50} \le \frac{1}{100}$；
3. $\frac{202}{20200 + 202} \le \frac{1}{100}$；

在第二个测试用例中，你不需要修改数组 $p$，因为通货膨胀系数已经满足要求：

1. $\frac{1}{1} \le \frac{100}{100}$；
2. $\frac{1}{1 + 1} \le \frac{100}{100}$；

#### 样例 #1

##### 输入

```
2
4 1
20100 1 202 202
3 100
1 1 1
```

##### 输出

```
99
0
```

### 算法分类
贪心

### 题解分析与结论

#### 题解对比
1. **henrytb**：通过前缀和计算，发现不满足条件的 inflation coefficients 时，将 $p_0$ 增大，以最小化总改动。时间复杂度为 $O(n)$。
2. **_shine_**：提出二分法，通过二分 $p_0$ 的增量来满足条件。时间复杂度为 $O(n \log M)$，其中 $M$ 是 $p_0$ 的最大增量。
3. **云浅知处**：使用贪心策略，每次发现不满足条件的 $p_i$ 时，直接修改 $p_0$，并维护树状数组来计算前缀和。时间复杂度为 $O(n \log n)$。
4. **Иɔlɔ**：与 henrytb 类似，通过前缀和计算，发现不满足条件时，直接修改 $p_0$。时间复杂度为 $O(n)$。
5. **Remake_**：提出二分法，通过二分 $p_0$ 的增量来满足条件。时间复杂度为 $O(n \log M)$。

#### 最优题解
- **henrytb**（4星）：思路清晰，代码简洁，直接通过前缀和和贪心策略解决问题，时间复杂度较低。
- **Иɔlɔ**（4星）：与 henrytb 类似，思路清晰，代码简洁，时间复杂度较低。

#### 关键思路与技巧
1. **贪心策略**：通过修改 $p_0$ 来满足所有 inflation coefficients 的条件，因为 $p_0$ 的修改可以影响所有后续的计算。
2. **前缀和**：通过维护前缀和，快速计算每个月的初始价格，从而判断是否需要修改 $p_0$。
3. **二分法**：通过二分 $p_0$ 的增量，可以更高效地找到满足条件的最小增量。

#### 可拓展之处
- 类似的问题可以通过贪心策略和前缀和来解决，尤其是在需要满足多个条件的情况下，优先修改影响最大的部分。

#### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)
3. [P1044 栈](https://www.luogu.com.cn/problem/P1044)

#### 个人心得
- **henrytb**：通过修改 $p_0$ 来满足所有条件，避免了复杂的后续计算，思路清晰。
- **云浅知处**：使用树状数组维护前缀和，虽然增加了复杂度，但提供了更多的灵活性。

### 核心代码片段
```cpp
int ned = 0;
per(i, n, 2) {
    if (p[i] * 100 > sum[i - 1] * k) 
        ned = max(ned, (p[i] * 100 - sum[i - 1] * k + k - 1) / k);
}
printf("%lld\n", ned);
```
**核心思想**：通过遍历数组，计算每个 inflation coefficients，发现不满足条件时，计算需要增加的 $p_0$ 的值，并取最大值作为最终结果。

---
处理用时：38.09秒