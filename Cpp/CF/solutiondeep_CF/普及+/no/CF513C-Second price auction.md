# 题目信息

# Second price auction

## 题目描述

Nowadays, most of the internet advertisements are not statically linked to a web page. Instead, what will be shown to the person opening a web page is determined within 100 milliseconds after the web page is opened. Usually, multiple companies compete for each ad slot on the web page in an auction. Each of them receives a request with details about the user, web page and ad slot and they have to respond within those 100 milliseconds with a bid they would pay for putting an advertisement on that ad slot. The company that suggests the highest bid wins the auction and gets to place its advertisement. If there are several companies tied for the highest bid, the winner gets picked at random.

However, the company that won the auction does not have to pay the exact amount of its bid. In most of the cases, a second-price auction is used. This means that the amount paid by the company is equal to the maximum of all the other bids placed for this ad slot.

Let's consider one such bidding. There are $ n $ companies competing for placing an ad. The $ i $ -th of these companies will bid an integer number of microdollars equiprobably randomly chosen from the range between $ L_{i} $ and $ R_{i} $ , inclusive. In the other words, the value of the $ i $ -th company bid can be any integer from the range $ [L_{i},R_{i}] $ with the same probability.

Determine the expected value that the winner will have to pay in a second-price auction.

## 说明/提示

Consider the first example. The first company bids a random integer number of microdollars in range $ [4,7] $ ; the second company bids between $ 8 $ and $ 10 $ , and the third company bids $ 5 $ microdollars. The second company will win regardless of the exact value it bids, however the price it will pay depends on the value of first company's bid. With probability $ 0.5 $ the first company will bid at most $ 5 $ microdollars, and the second-highest price of the whole auction will be $ 5 $ . With probability $ 0.25 $ it will bid $ 6 $ microdollars, and with probability $ 0.25 $ it will bid $ 7 $ microdollars. Thus, the expected value the second company will have to pay is $ 0.5·5+0.25·6+0.25·7=5.75 $ .

## 样例 #1

### 输入

```
3
4 7
8 10
5 5
```

### 输出

```
5.7500000000
```

## 样例 #2

### 输入

```
3
2 5
3 4
1 6
```

### 输出

```
3.5000000000
```

# AI分析结果

### 题目内容
# 第二价格拍卖

## 题目描述
如今，大多数互联网广告并非静态链接到网页。相反，在网页打开后的100毫秒内，将向打开网页的人展示的内容才会确定。通常，多家公司会在拍卖中竞争网页上的每个广告位。每家公司都会收到一个包含用户、网页和广告位详细信息的请求，并且它们必须在这100毫秒内回复愿意为在该广告位投放广告支付的出价。出价最高的公司赢得拍卖并获得投放广告的机会。如果有几家公司出价相同且都是最高出价，则随机选择获胜者。

然而，赢得拍卖的公司不必支付其出价的准确金额。在大多数情况下，会使用第二价格拍卖。这意味着公司支付的金额等于为该广告位所出的所有其他出价中的最大值。

让我们考虑这样一场竞拍。有 $n$ 家公司竞争投放广告。第 $i$ 家公司将以等概率随机选择一个介于 $L_{i}$ 和 $R_{i}$（含）之间的微美元整数出价。换句话说，第 $i$ 家公司的出价可以是范围 $[L_{i},R_{i}]$ 内的任何整数，且概率相同。

确定在第二价格拍卖中获胜者需要支付的期望值。

## 说明/提示
考虑第一个示例。第一家公司出价的微美元数是在范围 $[4,7]$ 内的随机整数；第二家公司出价在 $8$ 到 $10$ 之间，第三家公司出价 $5$ 微美元。无论第二家公司确切出价多少，它都会获胜，但是它将支付的价格取决于第一家公司的出价。第一家公司出价至多 $5$ 微美元的概率为 $0.5$，此时整个拍卖的第二高价格将是 $5$。它出价 $6$ 微美元的概率为 $0.25$，出价 $7$ 微美元的概率为 $0.25$。因此，第二家公司需要支付的期望值为 $0.5×5 + 0.25×6 + 0.25×7 = 5.75$。

## 样例 #1
### 输入
```
3
4 7
8 10
5 5
```
### 输出
```
5.7500000000
```
## 样例 #2
### 输入
```
3
2 5
3 4
1 6
```
### 输出
```
3.5000000000
```

### 算法分类
概率论

### 题解综合分析与结论
题解 TTpandaS 的思路是通过转换思路，将直接求 $i$ 作为次大值的概率 $p_i$ 转换为求次大值不低于 $i$ 的概率 $f_i$，利用动态规划的思想，通过状态转移方程 $dp_{i,j}= dp_{i - 1,j - 1} \cdot P + dp_{i - 1,j} \cdot (1 - P)$ 来计算 $f_i$，进而得到 $p_i$ 并计算出最终的期望值。该题解思路清晰，利用概率和动态规划结合的方式解决问题，难点在于状态的定义和状态转移方程的推导。

### 所选的题解
- **星级**：4星
- **关键亮点**：巧妙地将求次大值概率转换为求次大值不低于某值的概率，通过动态规划求解。
- **核心实现思想简述**：定义 $dp_{i,j}$ 表示前 $i$ 个人中有 $j$ 个人出价不低于 $k$ 的概率，根据第 $i$ 个人出价不低于 $k$ 的概率 $P$ 进行状态转移，最终通过 $f_k = \sum_{j = 1}^{n}dp_{n,j}$ 及 $p_i = f_i - f_{i + 1}$ 计算出期望值。

### 核心代码片段
```cpp
// 以下为伪代码示意核心逻辑
// 假设已有输入 n, l[i], r[i]
// 假设 maxr 为所有 r[i] 中的最大值
double f[maxr + 2];
for (int k = 1; k <= maxr; k++) {
    double dp[n + 1][n + 1] = {0};
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        double P = (r[i] - max(l[i], k) + 1.0) / (r[i] - l[i] + 1.0);
        for (int j = 0; j <= i; j++) {
            if (j > 0) dp[i][j] += dp[i - 1][j - 1] * P;
            dp[i][j] += dp[i - 1][j] * (1 - P);
        }
    }
    for (int j = 1; j <= n; j++) {
        f[k] += dp[n][j];
    }
}
double ans = 0;
for (int i = 1; i <= maxr; i++) {
    ans += i * (f[i] - f[i + 1]);
}
```

### 最优关键思路或技巧
将直接求次大值概率转化为求次大值不低于某值的概率，运用动态规划的思想，通过合理定义状态和状态转移方程来解决复杂的概率计算问题。

### 可拓展之处
此类题目属于概率与动态规划结合的问题，类似套路可用于解决其他涉及概率计算且状态可递推的问题，例如一些博弈类问题中涉及概率的情况。

### 洛谷相似题目推荐
- P1291 [SHOI2002]百事世界杯之旅 （涉及概率期望的计算）
- P4316 绿豆蛙的归宿 （图上的概率期望问题）
- P4550 收集邮票 （概率期望与递推结合问题）

---
处理用时：64.48秒