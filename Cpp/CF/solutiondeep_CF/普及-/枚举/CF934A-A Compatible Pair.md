# 题目信息

# A Compatible Pair

## 题目描述

Nian is a monster which lives deep in the oceans. Once a year, it shows up on the land, devouring livestock and even people. In order to keep the monster away, people fill their villages with red colour, light, and cracking noise, all of which frighten the monster out of coming.

Little Tommy has $ n $ lanterns and Big Banban has $ m $ lanterns. Tommy's lanterns have brightness $ a_{1},a_{2},...,a_{n} $ , and Banban's have brightness $ b_{1},b_{2},...,b_{m} $ respectively.

Tommy intends to hide one of his lanterns, then Banban picks one of Tommy's non-hidden lanterns and one of his own lanterns to form a pair. The pair's brightness will be the product of the brightness of two lanterns.

Tommy wants to make the product as small as possible, while Banban tries to make it as large as possible.

You are asked to find the brightness of the chosen pair if both of them choose optimally.

## 说明/提示

In the first example, Tommy will hide $ 20 $ and Banban will choose $ 18 $ from Tommy and $ 14 $ from himself.

In the second example, Tommy will hide $ 3 $ and Banban will choose $ 2 $ from Tommy and $ 1 $ from himself.

## 样例 #1

### 输入

```
2 2
20 18
2 14
```

### 输出

```
252
```

## 样例 #2

### 输入

```
5 3
-1 0 1 2 3
-1 0 1
```

### 输出

```
2
```

# AI分析结果

### 题目翻译
### 兼容的一对

#### 题目描述
“年”是一种生活在深海中的怪物。每年，它都会出现在陆地上，吞噬牲畜甚至人类。为了赶走怪物，人们用红色、灯光和噼里啪啦的声音填满村庄，这些都能把怪物吓跑。

小汤米有 $n$ 个灯笼，大班班有 $m$ 个灯笼。汤米的灯笼亮度分别为 $a_{1},a_{2},\cdots,a_{n}$，班班的灯笼亮度分别为 $b_{1},b_{2},\cdots,b_{m}$。

汤米打算藏起他的一个灯笼，然后班班从汤米未藏起的灯笼中选一个，再从自己的灯笼中选一个，组成一对。这对灯笼的亮度将是两个灯笼亮度的乘积。

汤米想让这个乘积尽可能小，而班班则想让它尽可能大。

如果他们都做出最优选择，请求出所选灯笼对的亮度。

#### 说明/提示
在第一个样例中，汤米会藏起亮度为 $20$ 的灯笼，班班会从汤米的灯笼中选亮度为 $18$ 的，从自己的灯笼中选亮度为 $14$ 的。

在第二个样例中，汤米会藏起亮度为 $3$ 的灯笼，班班会从汤米的灯笼中选亮度为 $2$ 的，从自己的灯笼中选亮度为 $1$ 的。

#### 样例 #1
##### 输入
```
2 2
20 18
2 14
```
##### 输出
```
252
```

#### 样例 #2
##### 输入
```
5 3
-1 0 1 2 3
-1 0 1
```
##### 输出
```
2
```

### 综合分析与结论
这些题解主要围绕如何解决从数列 $a$ 中删除一个元素后，使得剩余元素与数列 $b$ 中元素两两相乘结果的最大值最小的问题。主要有暴力枚举和贪心两种思路。
- **暴力枚举思路**：由于 $n$ 和 $m$ 的范围较小（均不超过 50），多数题解采用了枚举 $a$ 中要删除的元素，然后将剩余元素与 $b$ 中元素两两相乘，找出每次删除元素后的最大值，最后取这些最大值中的最小值。
- **贪心思路**：Tweetuzki 的题解提出了 $O(n + m)$ 的贪心算法。先分析不删除元素时，对答案有贡献的元素只有 $A$、$B$ 中最大和最小的元素，证明了最大值只可能是 $\max(Max_A \cdot Max_B, Max_A \cdot Min_B, Min_A \cdot Max_B, Min_A \cdot Min_B)$。再考虑删除情况，拿走 $A$ 中的最大值或最小值，用次大值或次小值代替，分别计算并取较小值作为答案。

### 所选题解
- **作者：StudyingFather（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用宏定义 `INF` 方便处理最大值和最小值，注释虽少但代码逻辑易懂。
    - **核心代码**：
```cpp
#include <iostream>
#include <algorithm>
#define INF 0x7fffffffffffffff
using namespace std;
long long a[55],b[55];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=m;i++)
        cin>>b[i];
    long long res=INF;
    for(int i=1;i<=n;i++)
    {
        long long now=-INF;
        for(int j=1;j<=n;j++)
            if(j!=i)
                for(int k=1;k<=m;k++)
                    now=max(now,a[j]*b[k]);
        res=min(res,now);
    }
    cout<<res;
    return 0;
}
```
核心实现思想：通过三层循环，外层循环枚举要删除的元素，内层两层循环计算剩余元素与 $b$ 中元素两两相乘的最大值，最后取这些最大值的最小值。

- **作者：Tweetuzki（5星）**
    - **关键亮点**：提出了时间复杂度为 $O(n + m)$ 的贪心算法，对问题进行了详细的分类讨论和证明，优化程度高。
    - **核心代码**：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

typedef long long llt;

const llt INF = 0x7F7F7F7F7F7F7F7F;

int n, m;
llt Max1 = -INF, Maxer1 = -INF, Min1 = INF, Miner1 = INF, Max2 = -INF, Min2 = INF;

void solve() {
    for (int i = 1; i <= n; ++i) {
        llt x;
        scanf("%lld", &x);
        if (x > Max1) {
            Maxer1 = Max1;
            Max1 = x;
        } else if (x > Maxer1)
            Maxer1 = x;
        if (x < Min1) {
            Miner1 = Min1;
            Min1 = x;
        } else if (x < Miner1)
            Miner1 = x;
    }
    for (int i = 1; i <= m; ++i) {
        llt x;
        scanf("%lld", &x);
        Min2 = min(Min2, x);
        Max2 = max(Max2, x);
    }
    llt ans1 = max( max(Maxer1 * Max2, Maxer1 * Min2), max(Min1 * Max2, Min1 * Min2) );
    llt ans2 = max( max(Max1 * Max2, Max1 * Min2), max(Miner1 * Max2, Miner1 * Min2) );
    llt ans = min(ans1, ans2);
    printf("%lld\n", ans);
}

int main() {
    scanf("%d %d", &n, &m);
    solve();
    return 0;
}
```
核心实现思想：先在输入时找出 $A$ 中的最大值、次大值、最小值、次小值和 $B$ 中的最大值、最小值，然后分别计算拿走 $A$ 中最大值和最小值后的最大值，最后取较小值作为答案。

### 最优关键思路或技巧
- 当数据范围较小时，暴力枚举是一种简单直接的解题方法，代码实现相对容易。
- 对于可以优化的问题，通过数学分析和分类讨论，找出问题的关键因素，采用贪心算法可以降低时间复杂度。

### 拓展思路
同类型题可以是在多个集合中进行元素选择或删除操作，使得某些组合的结果满足特定条件（如最大值最小、最小值最大等）。类似算法套路包括枚举、贪心、动态规划等。

### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：涉及路径规划和动态规划，与枚举和最优选择相关。
2. [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：动态规划经典题目，需要在三角形中选择路径使得和最大，与本题的最优选择思想类似。
3. [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题，通过枚举和状态转移找到最优解，与本题的枚举和求最优值思路有一定关联。

### 个人心得
- **作者：happybob**：原本想用贪心去做，但因为涉及到负数乘法，情况较复杂，最终选择了暴力枚举。这提醒我们在解题时要考虑到问题的复杂性，当贪心算法难以处理时，暴力枚举也是一种可行的方法。

---
处理用时：39.81秒