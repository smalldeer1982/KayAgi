# 题目信息

# Dolce Vita

## 题目描述

Turbulent times are coming, so you decided to buy sugar in advance. There are $ n $ shops around that sell sugar: the $ i $ -th shop sells one pack of sugar for $ a_i $ coins, but only one pack to one customer each day. So in order to buy several packs, you need to visit several shops.

Another problem is that prices are increasing each day: during the first day the cost is $ a_i $ , during the second day cost is $ a_i + 1 $ , during the third day — $ a_i + 2 $ and so on for each shop $ i $ .

On the contrary, your everyday budget is only $ x $ coins. In other words, each day you go and buy as many packs as possible with total cost not exceeding $ x $ . Note that if you don't spend some amount of coins during a day, you can't use these coins during the next days.

Eventually, the cost for each pack will exceed $ x $ , and you won't be able to buy even a single pack. So, how many packs will you be able to buy till that moment in total?

## 说明/提示

In the first test case,

- Day 1: prices are $ [2, 1, 2] $ . You can buy all $ 3 $ packs, since $ 2 + 1 + 2 \le 7 $ .
- Day 2: prices are $ [3, 2, 3] $ . You can't buy all $ 3 $ packs, since $ 3 + 2 + 3 > 7 $ , so you buy only $ 2 $ packs.
- Day 3: prices are $ [4, 3, 4] $ . You can buy $ 2 $ packs with prices $ 4 $ and $ 3 $ .
- Day 4: prices are $ [5, 4, 5] $ . You can't buy $ 2 $ packs anymore, so you buy only $ 1 $ pack.
- Day 5: prices are $ [6, 5, 6] $ . You can buy $ 1 $ pack.
- Day 6: prices are $ [7, 6, 7] $ . You can buy $ 1 $ pack.
- Day 7: prices are $ [8, 7, 8] $ . You still can buy $ 1 $ pack of cost $ 7 $ .
- Day 8: prices are $ [9, 8, 9] $ . Prices are too high, so you can't buy anything.

 In total, you bought $ 3 + 2 + 2 + 1 + 1 + 1 + 1 = 11 $ packs.In the second test case, prices are too high even at the first day, so you can't buy anything.

In the third test case, you can buy only one pack at day one.

In the fourth test case, you can buy $ 2 $ packs first $ 500 $ days. At day $ 501 $ prices are $ [501, 501] $ , so you can buy only $ 1 $ pack the next $ 500 $ days. At day $ 1001 $ prices are $ [1001, 1001] $ so can't buy anymore. In total, you bought $ 500 \cdot 2 + 500 \cdot 1 = 1500 $ packs.

## 样例 #1

### 输入

```
4
3 7
2 1 2
5 9
10 20 30 40 50
1 1
1
2 1000
1 1```

### 输出

```
11
0
1
1500```

# AI分析结果

### 题目内容重写
**题目描述**

动荡的时代即将到来，因此你决定提前购买糖。周围有 $n$ 家商店出售糖：第 $i$ 家商店每天出售一包糖，价格为 $a_i$ 元，但每个顾客每天只能购买一包。因此，为了购买多包糖，你需要访问多家商店。

另一个问题是，糖的价格每天都在上涨：第一天每包糖的价格为 $a_i$，第二天为 $a_i + 1$，第三天为 $a_i + 2$，依此类推。

然而，你每天的预算只有 $x$ 元。换句话说，每天你都会去购买尽可能多的糖包，且总花费不超过 $x$ 元。注意，如果你某天没有花完预算，剩余的钱不能留到第二天。

最终，每包糖的价格都会超过 $x$ 元，你将无法再购买任何糖包。那么，在此之前，你一共能购买多少包糖？

### 算法分类
贪心、前缀和

### 题解分析与结论
该题的核心在于如何高效计算在糖价每天上涨的情况下，每天能购买的糖包数量，并累加总购买量。由于糖价每天上涨，且每家商店的糖价涨幅相同，因此可以通过贪心策略和前缀和来优化计算。

### 精选题解
1. **作者：Rnfmabj (5星)**
   - **关键亮点**：通过排序和前缀和，从后往前计算每天能购买的糖包数量，避免了暴力模拟的高时间复杂度。代码清晰，逻辑严谨。
   - **核心代码**：
     ```cpp
     for(ll i=n;i>=1;i--){
         if(b[i]+sum*i>x) continue;
         ll res=(x-b[i]-sum*i)/i+1;
         ans+=res*i;
         sum+=res;
     }
     ```
   - **实现思想**：从后往前遍历商店，计算在当前天数下能购买的前 $i$ 家商店的糖包数量，并累加天数。

2. **作者：Henry_C (4星)**
   - **关键亮点**：使用前缀和和贪心策略，从大到小枚举商店数量，计算每种情况下能购买的天数，并累加购买量。代码结构清晰，优化了时间复杂度。
   - **核心代码**：
     ```cpp
     for(int i=n; i>=1; i--){
         LL res = x - preSum.getRange(1, i);
         if(res<0) continue;
         else{
             LL day = res/i + 1;
             sum += (day - lastDay)*i;
             lastDay = day;
         }
     }
     ```
   - **实现思想**：从大到小枚举商店数量，计算在当前前缀和和预算下能购买的天数，并累加购买量。

3. **作者：zcxxnqwq (4星)**
   - **关键亮点**：通过贪心和前缀和，计算每天能购买的糖包数量，并利用公式直接计算能持续购买的天数，避免了逐天模拟。代码简洁，逻辑清晰。
   - **核心代码**：
     ```cpp
     for(int i=1 ; i<=n; i++) {
         s[i] = s[i - 1] + a[i];
         if (s[i] > x && now == -1) now = i - 1;
     }
     ```
   - **实现思想**：通过前缀和计算初始状态下能购买的糖包数量，并利用公式计算能持续购买的天数。

### 最优关键思路
1. **排序与前缀和**：首先对糖价进行排序，并计算前缀和，以便快速计算任意区间内的糖价总和。
2. **从后往前计算**：从后往前遍历商店，计算在当前天数下能购买的前 $i$ 家商店的糖包数量，并累加天数。
3. **公式计算天数**：利用公式直接计算能持续购买的天数，避免了逐天模拟的高时间复杂度。

### 可拓展之处
该题的贪心策略和前缀和优化可以应用于类似的动态规划问题，尤其是涉及价格随时间变化的问题。例如，计算在预算限制下，如何最大化购买某种商品的数量。

### 推荐题目
1. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：30.12秒