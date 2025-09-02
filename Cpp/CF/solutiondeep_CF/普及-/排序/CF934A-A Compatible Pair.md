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
年是一种生活在深海中的怪物。每年，它都会出现在陆地上，吞噬牲畜甚至人类。为了赶走这个怪物，人们用红色、灯光和噼里啪啦的声音装点他们的村庄，这些都能把怪物吓跑，让它不敢再来。

小汤米有 $n$ 个灯笼，大班班有 $m$ 个灯笼。汤米的灯笼亮度分别为 $a_{1},a_{2},\cdots,a_{n}$，班班的灯笼亮度分别为 $b_{1},b_{2},\cdots,b_{m}$。

汤米打算藏起他的一个灯笼，然后班班从汤米未藏起的灯笼中选一个，再从自己的灯笼中选一个，组成一对。这对灯笼的亮度将是两个灯笼亮度的乘积。

汤米想让这个乘积尽可能小，而班班则想让它尽可能大。

如果他们都做出最优选择，请求出所选灯笼对的亮度。

### 综合分析与结论
这些题解主要围绕如何解决在给定两个数列，从一个数列中删除一个元素后，求剩余元素与另一个数列元素两两相乘所得最大值的最小值这一问题展开。
- **思路对比**：大部分题解采用暴力枚举的思路，通过枚举要删除的元素，再计算剩余元素两两相乘的最大值，最后取这些最大值中的最小值。而 Tweetuzki 的题解采用贪心算法，通过分析得出对答案有贡献的元素只可能是两个数列中的最大和最小元素，将时间复杂度优化到 $O(n + m)$。
- **算法要点**：暴力枚举的题解主要是通过多层嵌套循环实现，而贪心算法的题解则是在输入时找出数列的最大值、次大值、最小值、次小值，然后分别计算拿走最大值和最小值后的结果，取较小值。
- **解决难点**：主要难点在于处理可能出现的负数乘法以及数据范围较大可能导致的溢出问题，大部分题解都通过使用 `long long` 类型来解决溢出问题。

### 所选题解
- **StudyingFather（4星）**
    - **关键亮点**：思路清晰，代码简洁，通过简单的枚举实现了题目要求，使用 `#define INF 0x7fffffffffffffff` 来表示无穷大，方便后续比较。
- **Tweetuzki（5星）**
    - **关键亮点**：采用贪心算法，将时间复杂度从 $O(n^2m)$ 优化到 $O(n + m)$，通过分析得出对答案有贡献的元素只可能是两个数列中的最大和最小元素，大大提高了效率。
- **feicheng（4星）**
    - **关键亮点**：代码注释详细，思路清晰，提醒了可能爆 `int` 的问题，使用 `long long` 类型避免溢出。

### 重点代码
#### StudyingFather
```cpp
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
```
**核心实现思想**：通过三层循环，外层循环枚举要删除的元素，内层两层循环计算剩余元素两两相乘的最大值，最后取这些最大值中的最小值。

#### Tweetuzki
```cpp
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
```
**核心实现思想**：在输入时找出数列的最大值、次大值、最小值、次小值，然后分别计算拿走最大值和最小值后的结果，取较小值。

#### feicheng
```cpp
for(ri i = 1;i <= n;++i) {
    Mx = -9223372036854775807;
    for(ri j = 1;j <= n;++j) {
        if(j == i) continue;
        for(ri k = 1;k <= m;++k)  
            Mx = std::max(Mx,a[j]*b[k]);
    }
    ans = std::min(Mx,ans);
}
```
**核心实现思想**：通过三层循环，外层循环枚举要删除的元素，内层两层循环计算剩余元素两两相乘的最大值，最后取这些最大值中的最小值。

### 最优关键思路或技巧
- 当数据范围较小时，可以优先考虑暴力枚举的方法，通过多层嵌套循环来解决问题。
- 对于一些问题，可以通过分析问题的性质，找出对答案有贡献的关键元素，从而采用贪心算法来优化时间复杂度。
- 处理可能出现的大数乘法时，要使用 `long long` 类型来避免溢出。

### 可拓展之处
同类型题可以是在多个集合中进行元素的选择和操作，求满足某种条件的最优解。类似算法套路可以是枚举、贪心、动态规划等。

### 推荐洛谷题目
- P1002 [过河卒](https://www.luogu.com.cn/problem/P1002)
- P1048 [采药](https://www.luogu.com.cn/problem/P1048)
- P1216 [数字三角形](https://www.luogu.com.cn/problem/P1216)

### 个人心得
- **happybob**：原本想用贪心去做，但是因为涉及到负数乘法，麻烦一些，只好暴力了。
**总结**：在解决问题时，贪心算法虽然高效，但可能不适用于所有情况，当遇到复杂情况时，暴力枚举也是一种可行的方法。

---
处理用时：40.77秒