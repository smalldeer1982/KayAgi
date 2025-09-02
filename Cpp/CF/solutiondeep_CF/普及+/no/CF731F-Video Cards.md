# 题目信息

# Video Cards

## 题目描述

Little Vlad is fond of popular computer game Bota-2. Recently, the developers announced the new add-on named Bota-3. Of course, Vlad immediately bought only to find out his computer is too old for the new game and needs to be updated.

There are $ n $ video cards in the shop, the power of the $ i $ -th video card is equal to integer value $ a_{i} $ . As Vlad wants to be sure the new game will work he wants to buy not one, but several video cards and unite their powers using the cutting-edge technology. To use this technology one of the cards is chosen as the leading one and other video cards are attached to it as secondary. For this new technology to work it's required that the power of each of the secondary video cards is divisible by the power of the leading video card. In order to achieve that the power of any secondary video card can be reduced to any integer value less or equal than the current power. However, the power of the leading video card should remain unchanged, i.e. it can't be reduced.

Vlad has an infinite amount of money so he can buy any set of video cards. Help him determine which video cards he should buy such that after picking the leading video card and may be reducing some powers of others to make them work together he will get the maximum total value of video power.

## 说明/提示

In the first sample, it would be optimal to buy video cards with powers $ 3 $ , $ 15 $ and $ 9 $ . The video card with power $ 3 $ should be chosen as the leading one and all other video cards will be compatible with it. Thus, the total power would be $ 3+15+9=27 $ . If he buys all the video cards and pick the one with the power $ 2 $ as the leading, the powers of all other video cards should be reduced by $ 1 $ , thus the total power would be $ 2+2+14+8=26 $ , that is less than $ 27 $ . Please note, that it's not allowed to reduce the power of the leading video card, i.e. one can't get the total power $ 3+1+15+9=28 $ .

In the second sample, the optimal answer is to buy all video cards and pick the one with the power $ 2 $ as the leading. The video card with the power $ 7 $ needs it power to be reduced down to $ 6 $ . The total power would be $ 8+2+2+6=18 $ .

## 样例 #1

### 输入

```
4
3 2 15 9
```

### 输出

```
27
```

## 样例 #2

### 输入

```
4
8 2 2 7
```

### 输出

```
18
```

# AI分析结果

### 题目内容
#### Video Cards
#### 题目描述
小弗拉德热衷于流行的电脑游戏《Bota - 2》。最近，开发者宣布了名为《Bota - 3》的新扩展包。当然，弗拉德立刻购买了，结果却发现他的电脑太旧，无法运行新游戏，需要进行升级。

商店里有 $n$ 张显卡，第 $i$ 张显卡的性能值等于整数值 $a_{i}$ 。由于弗拉德想确保新游戏能够运行，他不想只买一张显卡，而是想买几张显卡，并使用尖端技术将它们的性能联合起来。为了使用这项技术，需要选择其中一张显卡作为主显卡，其他显卡作为从显卡连接到它上面。为了使这项新技术能够工作，要求每张从显卡的性能值都能被主显卡的性能值整除。为了达到这个要求，任何一张从显卡的性能值都可以降低到任何小于或等于当前性能值的整数值。然而，主显卡的性能值应该保持不变，即不能降低。

弗拉德有无限的钱，所以他可以购买任何一组显卡。帮助他确定应该购买哪些显卡，以便在选择主显卡并可能降低其他显卡的性能值以使它们协同工作后，他能获得最大的显卡总性能值。
#### 说明/提示
在第一个样例中，最优的选择是购买性能值为 $3$、$15$ 和 $9$ 的显卡。应该选择性能值为 $3$ 的显卡作为主显卡，所有其他显卡都将与它兼容。因此，总性能值将是 $3 + 15 + 9 = 27$ 。如果他购买所有显卡并选择性能值为 $2$ 的显卡作为主显卡，那么所有其他显卡的性能值都应该降低 $1$ ，因此总性能值将是 $2 + 2 + 14 + 8 = 26$ ，这小于 $27$ 。请注意，不允许降低主显卡的性能值，即不能得到总性能值 $3 + 1 + 15 + 9 = 28$ 。

在第二个样例中，最优答案是购买所有显卡并选择性能值为 $2$ 的显卡作为主显卡。性能值为 $7$ 的显卡需要将其性能值降低到 $6$ 。总性能值将是 $8 + 2 + 2 + 6 = 18$ 。
#### 样例 #1
##### 输入
```
4
3 2 15 9
```
##### 输出
```
27
```
#### 样例 #2
##### 输入
```
4
8 2 2 7
```
##### 输出
```
18
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于对题目中条件的数学转化。题目要求找出以某个数为基准，使其他数调整后与基准数满足整除关系下的最大总和。各题解都发现了对于固定的基准数 $a_i$，在区间 $[a_i\cdot x,a_i\cdot (x + 1)-1]$ 内的数对总和的贡献是固定的这一规律。通过统计每个数出现的次数（利用桶），并结合前缀和优化，来快速计算不同基准数下的总和。不同之处在于部分题解使用线段树维护，部分直接用前缀和；有的题解在枚举时进行了小优化，跳过不必要的枚举。整体来说，这些题解都是围绕如何高效计算不同基准数下的总和来展开。

### 所选的题解
- **作者：RainFestival（5星）**
    - **关键亮点**：思路清晰，先将问题转化为数学表达式，利用前缀和 $O(q)$ 预处理实现 $O(1)$ 查询，时间复杂度分析准确，代码简洁明了。
    - **核心代码**：
```cpp
#include<cstdio>
#include<algorithm>
#define cnt 200000
int n,f[500005],g[500005],val[500005];
long long ans;
int solve(int l,int r){return g[r]-(l!=0?g[l-1]:0);}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&f[i]),++val[f[i]];
    for (int i=1;i<=cnt*2;i++) g[i]=g[i-1]+val[i];
    for (int i=1;i<=cnt;i++)
    {
        if (!val[i]) continue;
        long long s=0;
        for (int j=0;i*j<=cnt;j++) s=s+1ll*i*j*solve(i*j,i*(j+1)-1);
        ans=std::max(ans,s);
    }
    printf("%lld\n",ans);
}
```
    - **核心实现思想**：先统计每个数出现的次数存于 `val` 数组，通过前缀和数组 `g` 预处理，枚举所有可能的基准数 `i`，对于每个基准数，枚举其倍数 `j`，利用 `solve` 函数快速计算每个区间内数的个数，进而计算总和并更新最大值。
- **作者：ModestCoder_（4星）**
    - **关键亮点**：代码简洁，直接利用桶和前缀和，清晰地实现了对每个数作为基数时总和的计算。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define maxn 200010
#define LL long long
using namespace std;
const LL N = 200000;
LL n, sum[maxn];

inline int read(){
    int s = 0, w = 1;
    char c = getchar();
    for (;!isdigit(c); c = getchar()) if (c == '-') w = -1;
    for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
    return s * w;
}

int main(){
    n = read();
    for (int i = 1; i <= n; ++i){
        int x = read();
        ++sum[x];
    }
    for (int i = 1; i <= N; ++i) sum[i] += sum[i - 1];
    LL ans = 0;
    for (LL i = 1; i <= N; ++i)
        if (sum[i]!= sum[i - 1]){
            LL s = 0;
            for (LL j = 1; i * j <= N; ++j) s += i * j * (sum[min(N, i * (j + 1) - 1LL)] - sum[i * j - 1]);
            ans = max(ans, s);
        }
    printf("%lld\n", ans);
    return 0;
}
```
    - **核心实现思想**：读入数据时统计每个数出现次数存于 `sum` 数组，再求前缀和。枚举所有可能的基数 `i`，对于每个基数，枚举其倍数 `j`，通过前缀和计算每个区间内数的个数，从而计算总和并更新最大值。
- **作者：Dream__Sky（4星）**
    - **关键亮点**：先对式子进行化简，逻辑清晰，同样利用桶和前缀和来实现高效计算。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m=2e5,a[200010],v[200010],ans,daan;
signed main()
{
    cin>>n;
    for(int i=1,x;i<=n;i++){
        cin>>x;
        a[x]++,v[x]=1;
    }
    for(int i=1;i<=m;i++) a[i]+=a[i-1];

    for(int i=1;i<=m;i++){
        if(!v[i]) continue;
        ans=0;
        for(int k=1;k*i<=m;k++)
            ans+=k*(a[min(m,(k+1)*i-1)]-a[k*i-1]);
        daan=max(daan,ans*i);
    }
    cout<<daan;
    return 0;
}
```
    - **核心实现思想**：读入数据时统计每个数出现次数存于 `a` 数组并求前缀和，`v` 数组标记出现过的数。枚举所有可能的数 `i`，对于每个数，枚举其倍数 `k`，通过前缀和计算每个区间内数的个数，进而计算总和并更新最大值。

### 最优关键思路或技巧
利用桶来统计每个性能值出现的次数，再通过前缀和优化，快速计算以某个性能值为基准时，不同区间内数的个数，从而高效计算出不同基准下的总性能值。在枚举基准值时，注意跳过未出现过的性能值，减少不必要的计算。

### 可拓展之处
同类型题通常围绕数论中的整除、取模等关系，结合数据统计与优化来设计。类似算法套路是在涉及到数的分组、倍数关系等问题时，考虑利用桶和前缀和进行优化计算，同时注意对数据范围和特性的利用，减少枚举量。

### 洛谷题目推荐
- [P1447 能量采集](https://www.luogu.com.cn/problem/P1447)：涉及数论中最大公约数相关知识，通过统计不同最大公约数出现的次数来计算答案，与本题利用桶和数学关系求解思路类似。
- [P2522 [HAOI2011]Problem b](https://www.luogu.com.cn/problem/P2522)：同样是数论问题，通过容斥原理和数论分块来解决，对数论知识和优化技巧的运用有一定要求，与本题在数论分析和优化计算上有相似点。
- [P3455 [POI2007]ZAP-Queries](https://www.luogu.com.cn/problem/P3455)：该题也是关于数论分块的应用，通过对给定区间内数对的统计来求解，与本题在利用数论性质优化计算方面思路相似。 

---
处理用时：93.06秒