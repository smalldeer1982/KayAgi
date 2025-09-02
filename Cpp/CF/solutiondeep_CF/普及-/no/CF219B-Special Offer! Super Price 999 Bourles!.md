# 题目信息

# Special Offer! Super Price 999 Bourles!

## 题目描述

Polycarpus is an amateur businessman. Recently he was surprised to find out that the market for paper scissors is completely free! Without further ado, Polycarpus decided to start producing and selling such scissors.

Polycaprus calculated that the optimal celling price for such scissors would be $ p $ bourles. However, he read somewhere that customers are attracted by prices that say something like "Special Offer! Super price 999 bourles!". So Polycarpus decided to lower the price a little if it leads to the desired effect.

Polycarpus agrees to lower the price by no more than $ d $ bourles so that the number of nines at the end of the resulting price is maximum. If there are several ways to do it, he chooses the maximum possible price.

Note, Polycarpus counts only the trailing nines in a price.

## 样例 #1

### 输入

```
1029 102
```

### 输出

```
999
```

## 样例 #2

### 输入

```
27191 17
```

### 输出

```
27189
```

# AI分析结果

### 题目重述
# 特别优惠！超级价格999布尔！

## 题目描述
波利亚科普斯是个业余商人。最近，他惊讶地发现，纸剪刀市场完全没有竞争！波利亚科普斯毫不犹豫地决定开始生产和销售这种剪刀。

波利亚科普斯计算出，这种剪刀的最优封顶价格为$p$布尔。然而，他在某个地方读到，像 “特别优惠！超级价格999布尔！” 这样的价格会吸引顾客。所以，如果降价能达到预期效果，波利亚科普斯决定稍微降低一下价格。

波利亚科普斯同意降价不超过$d$布尔，以便使最终价格末尾的9的数量最多。如果有几种方法可以做到这一点，他会选择尽可能高的价格。

注意，波利亚科普斯只计算价格末尾的9。

## 样例 #1
### 输入
```
1029 102
```
### 输出
```
999
```

## 样例 #2
### 输入
```
27191 17
```
### 输出
```
27189
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是通过枚举末尾9的个数，结合贪心策略来解决问题，判断在降价不超过$d$的情况下，找到末尾9最多且价格最高的方案。主要区别在于实现细节和代码的优化程度。
1. **思路**：多数题解通过枚举末尾9的个数，从低位到高位或从高位到低位，计算要达到该末尾9个数所需的降价幅度，判断是否满足不超过$d$的条件。
2. **算法要点**：利用取模运算获取末尾数字，通过与$10$的幂运算相关操作，计算调整价格使其末尾为9的方案。
3. **解决难点**：核心是在$O(\log p)$时间复杂度内，高效地找到满足条件的最优价格。难点在于准确计算出每个可能的末尾9的方案对应的价格调整值，并判断是否在允许的降价范围内。

### 所选的题解
- **作者：loser_seele (5星)**
    - **关键亮点**：思路清晰，代码简洁高效。通过预处理$10$的次幂，$O(1)$计算最接近的末尾有若干个9的数，时间复杂度$O(\log p)$。
    - **重点代码**：
```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
int power[20];
signed main()
{
    int p = 0, d = 0;
    cin >> p >> d;
    power[0] = 10;
    for (int i = 1; i <= 19; i++)
        power[i] = power[i - 1] * 10;
    int ans = p, numof9 = 0;
    for (int i = 1; i < 19; i++)
    {
        int p0w = power[i - 1];
        int cur = p - p % p0w + p0w - 1;
        if (cur > p)
        {
            int times = (cur - p) / p0w + ((cur - p) % p0w!= 0);
            cur -= times * p0w;
        }
        if (cur >= 0 && p - cur <= d && i > numof9)
        {
            numof9 = i;
            ans = cur;
        }
    }
    cout << ans;
}
```
    - **核心实现思想**：先预处理$10$的幂次方数组`power`，然后枚举末尾9的个数`i`，计算当前价格`p`调整为末尾有`i`个9的最接近价格`cur`，若`cur`满足条件则更新答案`ans`。
- **作者：qwasd (4星)**
    - **关键亮点**：代码简洁，从大到小枚举末尾9的个数，通过封装函数`gg`计算最少减去的值，逻辑清晰。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll p, d;
inline ll gg(int x) {
    static ll p10[20];
    if (!p10[0]) {
        p10[0] = 1;
        for (int i{1}; i <= 18; ++i) p10[i] = p10[i - 1] * 10LL;
    }
    if (p < p10[x] - 1) return -1;
    if (p % p10[x] == p10[x] - 1) {
        return p;
    }
    else {
        return (p / p10[x] - 1LL) * p10[x] + (p10[x] - 1LL);
    }
}
signed main() {
    cin >> p >> d;
    for (int i{18}; i >= 0; --i) {
        ll t = gg(i);
        if (p - t <= d) {
            cout << t;
            break;
        }
    }
    return 0;
}
```
    - **核心实现思想**：`gg`函数计算使价格`p`末尾有`x`个9最少减去的值，主函数从大到小枚举`x`，判断是否满足降价不超过`d`的条件，满足则输出结果。
- **作者：ylch (4星)**
    - **关键亮点**：通过表格辅助理解，详细解释了枚举和贪心的过程，代码实现简单易懂，包含了必要的特判。
    - **重点代码**：
```cpp
#include <algorithm>
#include <iostream>
using namespace std;

signed main()
{
    long long p, d, m = 0;
    cin >> p >> d;
    if (p < 10) {
        cout << p << endl;
        return 0;
    }
    for (long long i = 10; i <= p; i *= 10) {
        if (p % i + 1 == i) {}
        else {
            if (p % i + 1 <= d) m = p % i + 1;
            else break;
        }
    }
    cout << p - m << endl;
    return 0;
}
```
    - **核心实现思想**：从低位开始枚举，通过取模运算判断当前位是否需要调整为9，若需要且调整差值在`d`范围内则记录差值，最后输出`p`减去差值后的结果。

### 最优关键思路或技巧
1. **利用10的幂运算**：通过预处理$10$的幂次方数组，方便计算价格调整值，优化时间复杂度。
2. **贪心策略**：在满足降价不超过$d$的前提下，优先选择末尾9最多的价格，并且在多种满足条件的情况下选择最大价格。

### 同类型题或类似算法套路拓展
此类题目通常围绕贪心策略展开，在价格、数量等场景下，通过枚举关键参数（如本题中末尾9的个数），结合限制条件（如本题中的降价幅度限制），找到最优解。解题时要明确贪心的方向和判断条件，合理利用数学运算简化计算。

### 洛谷相似题目推荐
1. **P1080 [NOIP2012 提高组] 国王游戏**：通过合理排序，运用贪心策略解决分配问题。
2. **P1199 [NOIP2010 普及组] 三国游戏**：同样是贪心策略的应用，需要分析游戏规则找到最优策略。
3. **P1248 加工生产调度**：利用贪心思想对生产调度进行优化，提高生产效率。 

---
处理用时：65.21秒