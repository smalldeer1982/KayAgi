# 题目信息

# Berland Fair

## 题目描述

XXI Berland Annual Fair is coming really soon! Traditionally fair consists of $ n $ booths, arranged in a circle. The booths are numbered $ 1 $ through $ n $ clockwise with $ n $ being adjacent to $ 1 $ . The $ i $ -th booths sells some candies for the price of $ a_i $ burles per item. Each booth has an unlimited supply of candies.

Polycarp has decided to spend at most $ T $ burles at the fair. However, he has some plan in mind for his path across the booths:

- at first, he visits booth number $ 1 $ ;
- if he has enough burles to buy exactly one candy from the current booth, then he buys it immediately;
- then he proceeds to the next booth in the clockwise order (regardless of if he bought a candy or not).

Polycarp's money is finite, thus the process will end once he can no longer buy candy at any booth.

Calculate the number of candies Polycarp will buy.

## 说明/提示

Let's consider the first example. Here are Polycarp's moves until he runs out of money:

1. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 33 $ ;
2. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 31 $ ;
3. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 26 $ ;
4. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 21 $ ;
5. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 19 $ ;
6. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 14 $ ;
7. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 9 $ ;
8. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 7 $ ;
9. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 2 $ ;
10. Booth $ 1 $ , buys no candy, not enough money;
11. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 0 $ .

No candy can be bought later. The total number of candies bought is $ 10 $ .

In the second example he has $ 1 $ burle left at the end of his path, no candy can be bought with this amount.

## 样例 #1

### 输入

```
3 38
5 2 5
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 21
2 4 100 2 6
```

### 输出

```
6
```

# AI分析结果

### 题目中文重写
# 伯兰集市

## 题目描述
第 21 届伯兰年度集市即将来临！传统上，集市由 $n$ 个摊位组成，这些摊位围成一个圆圈。摊位按顺时针方向从 1 到 $n$ 编号，其中第 $n$ 个摊位与第 1 个摊位相邻。第 $i$ 个摊位以 $a_i$ 伯尔（货币单位）的单价出售糖果，且每个摊位的糖果供应无限。

波利卡普决定在集市上最多花费 $T$ 伯尔。不过，他在集市中的行走路线有如下计划：
- 首先，他前往第 1 个摊位；
- 如果他有足够的钱恰好从当前摊位购买一颗糖果，他会立即购买；
- 然后，他按顺时针方向前往下一个摊位（无论是否购买了糖果）。

由于波利卡普的钱是有限的，当他在任何摊位都无法再购买糖果时，这个过程就会结束。

请计算波利卡普将购买的糖果数量。

## 说明/提示
让我们考虑第一个样例。以下是波利卡普在钱花完之前的行动步骤：
1. 摊位 1，花费 5 伯尔购买糖果，剩余 $T = 33$ 伯尔；
2. 摊位 2，花费 2 伯尔购买糖果，剩余 $T = 31$ 伯尔；
3. 摊位 3，花费 5 伯尔购买糖果，剩余 $T = 26$ 伯尔；
4. 摊位 1，花费 5 伯尔购买糖果，剩余 $T = 21$ 伯尔；
5. 摊位 2，花费 2 伯尔购买糖果，剩余 $T = 19$ 伯尔；
6. 摊位 3，花费 5 伯尔购买糖果，剩余 $T = 14$ 伯尔；
7. 摊位 1，花费 5 伯尔购买糖果，剩余 $T = 9$ 伯尔；
8. 摊位 2，花费 2 伯尔购买糖果，剩余 $T = 7$ 伯尔；
9. 摊位 3，花费 5 伯尔购买糖果，剩余 $T = 2$ 伯尔；
10. 摊位 1，因钱不够未购买糖果；
11. 摊位 2，花费 2 伯尔购买糖果，剩余 $T = 0$ 伯尔。

之后无法再购买糖果。总共购买的糖果数量为 10 颗。

在第二个样例中，他在行走结束后还剩下 1 伯尔，但这笔钱无法购买任何糖果。

## 样例 #1
### 输入
```
3 38
5 2 5
```
### 输出
```
10
```

## 样例 #2
### 输入
```
5 21
2 4 100 2 6
```
### 输出
```
6
```

### 综合分析与结论
这些题解的核心思路都是先计算出转一圈能购买的糖果数量和所需的钱数，然后通过取模的方式快速计算出能完整转的圈数，减少不必要的模拟。不同题解在具体实现和优化上有所差异，如使用树状数组、线段树进行二分查找，用优先队列维护权值，或用链表删除无法购买的摊位等。

### 所选题解
- **作者：信息向阳花木（5星）**
    - **关键亮点**：思路清晰，代码简洁易懂，通过变量清晰地表示当前走一圈能买的糖果数、所需钱数和剩余钱数，利用取模操作快速计算答案。
    - **核心代码**：
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 200010;

typedef unsigned long long LL;

LL n;
LL t, res, sum, cnt;
LL a[N];

int main()
{
    scanf ("%llu%llu", &n, &t);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%llu", &a[i]);
        if(t - sum >= a[i])
        {
            sum += a[i];
            cnt ++;
        }
    }
    while (sum > 0 && t > 0)
    {
        res += t / sum * cnt; 
        t %= sum;
        sum = 0; cnt = 0;
        for (int i = 1; i <= n; i ++ )
        {
            if(t - sum >= a[i])
            {
                sum += a[i];
                cnt ++;
            }
        }
    }
    printf("%llu\n", res);

    return 0;
}
```
核心实现思想：先计算初始一圈能买的糖果数和花费，然后不断用剩余钱数除以一圈花费得到圈数并累加答案，再取模更新剩余钱数，重新计算一圈的情况，直到无法购买。

- **作者：一扶苏一（4星）**
    - **关键亮点**：提供了两种解法，解法一使用树状数组和二分查找优化，解法二通过取模次数的分析优化复杂度，对算法复杂度有深入分析。
    - **核心代码（解法二）**：
```cpp
// 前面模板代码省略
const int maxn = 200010;

int n;
ll t, ans;
int MU[maxn];
ll tree[maxn], val[maxn];

// 树状数组相关函数省略

signed main() {
    qr(n); qr(t);
    for (rg int i = 1; i <= n; ++i) {qr(MU[i]); update(tree, i, MU[i]); update(val, i, 1);}
    ll s = ask(tree, n); int cnt = n;
    while (cnt) {
        if (!t) break;
        ans += t / s * cnt; t %= s;
        int k = 0;
        do {
            int pre = k;
            k = check(k, t);
            if (k > n) {
                t -= ask(tree, n) - ask(tree, pre);
                ans += ask(val, n) - ask(val, pre);
                break;
            };
            update(tree, k, -MU[k]); update(val, k, -1); --cnt;
            t -= ask(tree, k - 1) - ask(tree, pre);
            s -= MU[k];
            ans += ask(val, k) - ask(val, pre);
        } while (cnt && t);
    }
    qw(ans, '\n', true);
}
```
核心实现思想：先计算初始一圈的花费和可购买数量，用剩余钱数取模后，通过二分查找确定能连续购买的位置，删除无法购买的摊位，更新花费和可购买数量，直到无法购买。

- **作者：傅思维666（4星）**
    - **关键亮点**：详细记录了自己的思考过程，从最初的暴力思路逐步优化，使用标记数组跳过无法购买的摊位，优化了时间复杂度。
    - **核心代码**：
```c++
#include<cstdio>
#define ll long long
using namespace std;
const int maxn=1e5*2+1;
ll n,k;
ll a[maxn];
bool v[maxn];
ll sum,ans,tot;
int main()
{
    scanf("%lld%lld",&n,&k);
    tot=n;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        sum+=a[i];
    }
    while(1)
    {
        ans+=tot*(k/sum);
        k%=sum;
        int flag=0;
        for(int i=1;i<=n;i++)
        {
            if(v[i])
                continue;
            if(k>=a[i])
            {
                ans++;
                k-=a[i];
                flag=1;
            }
            else
            {
                v[i]=1;
                sum-=a[i];
                tot--;
            }
        }
        if(flag==0)
            break;
    }
    printf("%lld",ans);
    return 0;
}
```
核心实现思想：先计算初始一圈的花费，用剩余钱数取模后，遍历摊位，标记无法购买的摊位并更新一圈的花费和可购买数量，直到无法购买。

### 最优关键思路或技巧
- 取模优化：通过计算转一圈的花费，用总钱数对其取模，快速计算出能完整转的圈数，减少不必要的模拟。
- 标记删除：如果某个摊位在某一轮无法购买，那么后续也无法购买，可以将其标记并从计算中删除，减少后续的计算量。

### 拓展思路
同类型题可能会有不同的场景，如环形路径上的资源收集、循环任务的执行等。类似算法套路包括通过取模减少重复计算、使用数据结构（如树状数组、线段树）优化查找和更新操作等。

### 推荐题目
- [P1198 [JSOI2008] 最大数](https://www.luogu.com.cn/problem/P1198)：涉及线段树的区间查询和单点更新。
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)：树状数组的基础应用，用于单点修改和区间查询。
- [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)：使用单调队列优化区间最值查询。

### 个人心得摘录与总结
- **傅思维666**：最初的暴力代码虽然在弱数据下能通过，但在强数据下会超时。通过优化，如不用前缀和数组、用乘法替代多次减法、使用标记数组跳过无法购买的摊位等，提高了代码效率。总结是要对暴力算法进行深入分析，寻找可优化的点。
- **一扶苏一**：提到自己两个 $\log$ 的算法比一个 $\log$ 的跑得还快，说明实际运行效率可能受多种因素影响，不能仅根据理论复杂度判断。 

---
处理用时：53.87秒