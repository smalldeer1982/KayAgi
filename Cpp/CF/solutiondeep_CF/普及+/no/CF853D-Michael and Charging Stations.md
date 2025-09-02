# 题目信息

# Michael and Charging Stations

## 题目描述

Michael has just bought a new electric car for moving across city. Michael does not like to overwork, so each day he drives to only one of two his jobs.

Michael's day starts from charging his electric car for getting to the work and back. He spends $ 1000 $ burles on charge if he goes to the first job, and $ 2000 $ burles if he goes to the second job.

On a charging station he uses there is a loyalty program that involves bonus cards. Bonus card may have some non-negative amount of bonus burles. Each time customer is going to buy something for the price of $ x $ burles, he is allowed to pay an amount of $ y $ ( $ 0<=y<=x $ ) burles that does not exceed the bonus card balance with bonus burles. In this case he pays $ x-y $ burles with cash, and the balance on the bonus card is decreased by $ y $ bonus burles.

If customer pays whole price with cash (i.e., $ y=0 $ ) then 10% of price is returned back to the bonus card. This means that bonus card balance increases by ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF853D/b63fc695c9b8ab1ed954e5b28e2ca9818fa92a5c.png) bonus burles. Initially the bonus card balance is equal to 0 bonus burles.

Michael has planned next $ n $ days and he knows how much does the charge cost on each of those days. Help Michael determine the minimum amount of burles in cash he has to spend with optimal use of bonus card. Assume that Michael is able to cover any part of the price with cash in any day. It is not necessary to spend all bonus burles at the end of the given period.

## 说明/提示

In the first sample case the most optimal way for Michael is to pay for the first two days spending 3000 burles and get 300 bonus burles as return. After that he is able to pay only 700 burles for the third days, covering the rest of the price with bonus burles.

In the second sample case the most optimal way for Michael is to pay the whole price for the first five days, getting 1000 bonus burles as return and being able to use them on the last day without paying anything in cash.

## 样例 #1

### 输入

```
3
1000 2000 1000
```

### 输出

```
3700
```

## 样例 #2

### 输入

```
6
2000 2000 2000 2000 2000 1000
```

### 输出

```
10000
```

# AI分析结果

### 题目内容
#### Michael和充电站
#### 题目描述
Michael刚买了一辆新的电动汽车用于在城市中出行。Michael不喜欢过度劳累，所以他每天只去两份工作中的一份。
Michael的一天从为电动汽车充电开始，以便去工作并返回。如果他去第一份工作，充电花费1000卢布；如果他去第二份工作，充电花费2000卢布。
在他使用的充电站有一个会员忠诚度计划，涉及积分卡。积分卡可能有一些非负的积分卢布。每次顾客打算购买价值x卢布的东西时，他可以用不超过积分卡余额的积分卢布支付y（0 <= y <= x）卢布。在这种情况下，他用现金支付x - y卢布，积分卡上的余额减少y积分卢布。
如果顾客用现金支付全部价格（即y = 0），那么价格的10%会返还到积分卡上。这意味着积分卡余额增加![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF853D/b63fc695c9b8ab1ed954e5b28e2ca9818fa92a5c.png)积分卢布。最初，积分卡余额为0积分卢布。
Michael已经计划好了接下来的n天，并且他知道在这些天中每天的充电费用是多少。帮助Michael确定在最优使用积分卡的情况下，他必须用现金支付的最小卢布数。假设Michael在任何一天都可以用现金支付价格的任何部分。在给定时间段结束时，不一定要用完所有积分。
#### 说明/提示
在第一个样例中，对Michael来说最优化的方式是支付前两天的费用，花费3000卢布，并获得300积分卢布作为返还。之后，他在第三天只需支付700卢布，用积分卢布支付其余的价格。
在第二个样例中，对Michael来说最优化的方式是支付前五天的全部价格，获得1000积分卢布作为返还，并能够在最后一天使用这些积分，无需支付任何现金。
#### 样例 #1
**输入**
```
3
1000 2000 1000
```
**输出**
```
3700
```
#### 样例 #2
**输入**
```
6
2000 2000 2000 2000 2000 1000
```
**输出**
```
10000
```
### 算法分类
贪心、动态规划
### 题解综合分析与结论
这些题解主要分为贪心和动态规划两种思路。
- **贪心思路要点**：为使奖励的钱尽量凑一起使用，将22000视为一组（20000现金与2000奖励）。同时存在两种特殊情况需要特判：总价不超过11000且最后一个商品是2000元；所有商品价格全是2000元。另外，将所有钱数除以100简化计算。
- **动态规划思路要点**：记$dp_{i,j}$表示考虑充前$i$次电，积分卡中剩余$j$元时的最小花费。转移方程分使用与不使用积分卡两种情况。由于积分卡余额不会大于40（否则提前使用更优），实际时间复杂度为$O(NV'^2)$（$V' = 40$），空间复杂度为$O(NV')$，空间复杂度还可用滚动数组优化到$O(V')$。
- **难点对比**：贪心算法难点在于发现分组规律以及特殊情况的准确判断；动态规划难点在于状态定义与转移方程的推导，同时要考虑积分卡余额上限来优化复杂度。

### 所选的题解
- **作者：activeO (赞：2) - 5星**
    - **关键亮点**：思路清晰简洁，直接抓住贪心本质，通过将价格分组并特判特殊情况解决问题，代码简短高效。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10;
int a[maxn];
int main() {
    int n, sum = 0, cnt = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += a[i] / 1000;
        if (a[i] == 1000) cnt++;
    }
    int tmp = sum * 10 / 11;
    if (sum <= 11) tmp = sum - a[n] / 1000;
    if ((cnt == 0) && (tmp & 1)) tmp--;
    printf("%d\n", sum * 1000 - tmp * 100);
    return 0;
}
```
    - **核心实现思想**：先统计总价格和1000元价格的数量，根据贪心策略计算出理论上可获得的积分对应的花费减少量tmp，再对两种特殊情况进行调整，最后得出最小现金花费。
- **作者：GaryH (赞：1) - 4星**
    - **关键亮点**：详细阐述动态规划思路，从暴力DP到根据积分卡余额上限优化复杂度，逻辑连贯，对状态转移方程解释清晰。
    - **核心代码**：
```cpp
const int V(40);
const int N(3e5 + 10);
int n, dp[N][V + 5];
signed main() {
    n = read();
    rep(i, 0, n) rep(j, 0, V) dp[i][j] = 1e9;
    dp[0][0] = 0;
    rep(i, 1, n) {
        int x = read() / 100, t = x / 10;
        rep(j, t, V) ckmin(dp[i][j], dp[i - 1][j - t] + x);
        rep(j, 0, V) rep(k, 0, x) if (j + k < V)
            ckmin(dp[i][j], dp[i - 1][j + k] + x - k);
    }
    int ans = 1e9;
    rep(i, 0, V) ckmin(ans, dp[n][i]);
    return cout << ans * 100, 0;
}
```
    - **核心实现思想**：初始化DP数组，对每次充电操作，分别考虑不使用积分卡（更新`dp[i][j]`）和使用积分卡（通过枚举使用积分卡的金额k更新`dp[i][j]`）的情况，最后从最终状态的DP数组中找出最小花费。
- **作者：仗剑_天涯 (赞：1) - 4星**
    - **关键亮点**：与activeO思路类似，同样采用贪心策略，表述通俗易懂，代码简洁明了。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, t, s, coun, a[300010];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        s += a[i] / 1000;
        if (a[i] == 1000) {
            coun++;
        }
    }
    t = s * 10 / 11;
    if (s <= 11) {
        t = s - a[n] / 1000;
    }
    if (coun == 0 && (t & 1)) {
        t--;
    }
    cout << s * 1000 - t * 100;
    return 0;
} 
```
    - **核心实现思想**：统计总价格和1000元价格的数量，依据贪心计算理论积分对应的花费减少量t，对特殊情况调整后得出最小现金花费。

### 最优关键思路或技巧
- **贪心角度**：敏锐发现价格组合规律，将22000作为一组处理，简化问题求解过程。同时准确识别并处理特殊情况，保证结果正确性。
- **动态规划角度**：合理定义状态与转移方程，并且通过分析积分卡余额上限来优化复杂度，避免无效计算。

### 拓展
- **同类型题**：此类题目通常围绕资源分配与最优策略选择，特点是当前决策会影响后续状态。例如一些消费返现、购物优惠组合等问题。
- **算法套路**：遇到此类问题，可先尝试寻找贪心策略，若难以直接确定贪心正确性，再考虑动态规划。动态规划要准确分析状态与转移关系，同时关注是否存在可优化的边界条件。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：01背包问题，与本题类似，需合理规划资源以获取最大价值，考察动态规划。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：通过贪心策略解决排队顺序问题，使总等待时间最小，与本题贪心思路有相似处。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：需要寻找合适的贪心策略对皇后进行排序，以满足题目要求的最优解，考察贪心策略的运用。 

---
处理用时：75.74秒