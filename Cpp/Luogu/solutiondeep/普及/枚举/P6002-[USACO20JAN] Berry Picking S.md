# 题目信息

# [USACO20JAN] Berry Picking S

## 题目描述

Bessie 和她的妹妹 Elsie 正在 Farmer John 的浆果园里采浆果。Farmer John 的浆果园里有 $N$ 棵浆果树（$1 \leq N \leq 1000$）；树 $i$ 上有 $B_i$ 个浆果（$1 \leq B_i \leq 1000$）。Bessie 有 $K$ 个篮子（$1 \leq K \leq 1000$，$K$ 为偶数）。每个篮子里可以装同一棵树上采下的任意多个浆果，但是不能装来自于不同的树上的浆果，因为它们的口味可能不同。篮子里也可以不装浆果。

Bessie 想要使得她得到的浆果数量最大。但是，Farmer John 希望 Bessie 与她的妹妹一同分享，所以 Bessie 必须将浆果数量较多的 $K/2$ 个篮子给 Elsie。这表示 Elsie 很有可能最后比 Bessie 得到更多的浆果，这十分不公平，然而姐妹之间往往就是这样。

帮助 Bessie 求出她最多可以得到的浆果数量。

## 说明/提示

### 样例解释

如果 Bessie 在

- 一个篮子里装树 2 的 6 个浆果
- 两个篮子里每个装树 3 的 4 个浆果
- 一个篮子里装树 4 的 4 个浆果

那么她能够得到两个各装有 4 个浆果的篮子，总共 8 个浆果。

### 子任务

- 测试点 $1 \sim 4$ 满足 $K \leq 10$。
- 测试点 $5 \sim 11$ 没有额外限制。

## 样例 #1

### 输入

```
5 4
3 6 8 4 2```

### 输出

```
8```

# AI分析结果

### 综合分析与结论
这些题解思路大致相同，均基于暴力枚举来解决问题。核心思路是假设Elsie拿的篮子里果子数最小值为 \( m \)，枚举 \( m \) 从 \( 1 \) 到 \( \max_{i = 1}^{N}{B_i} \)，计算每种情况下Bessie能获得的浆果数，取最大值作为答案。在计算Bessie的浆果数时，需根据能装满 \( m \) 个果子的篮子数 \( L \) 进行分类讨论：
 - \( L < \frac{K}{2} \)：无法满足Elsie篮子的最小条件，停止当前 \( m \) 的枚举。
 - \( L \geq K \)：Bessie能拿到 \( \frac{mK}{2} \) 个果子。
 - \( \frac{K}{2} \leq L < K \)：Bessie拿的果子数为 \( m \cdot (L - \frac{K}{2}) + \sum_{i = 1}^{K - L}{({B'}_i \bmod m)} \)，即先计算装满的篮子给Bessie的部分，再从剩余不满的篮子中贪心选取最多的给Bessie。

各题解主要差异在于代码实现细节和表述清晰度，部分题解提到了优化思路如二分答案，但未给出具体实现。

### 所选的题解
- **作者：Zvelig1205 (赞：22)  星级：4星**
    - **关键亮点**：思路清晰，对核心代码逐行解释，详细说明了每一步操作的意义，如对篮子数的判断条件以及优先队列的使用目的。
    - **个人心得**：提到曾因 \( K \) 为偶数，\( \frac{K}{2} \) 是整数这一条件专门询问同学，强调了理解题意细节的重要性。
    - **核心代码**：
```cpp
for(int i=1;;i++)
{
    priority_queue<int>h;
    basket=0;
    for(int j=1;j<=n;j++)
    {
        basket+=a[j]/i;
        h.push(a[j]%i);
    }
    if(basket>k)continue;
    if(basket<(k>>1))break;
    mei=(k>>1)*i;
    jie=(basket-(k>>1))*i;
    for(int ii=basket-(k>>1)+1;ii<=(k>>1);ii++)
        jie+=h.top(),h.pop();
    ans=max(ans,jie);
}
```
    - **核心实现思想**：枚举篮子装果子的上限 \( i \)，计算需要的篮子数 \( basket \)，判断其是否在合理范围。若合理，计算妹妹能拿到的果子数 \( mei \) 和姐姐能拿到的果子数 \( jie \)，姐姐的果子数通过优先队列从剩余不满篮子中贪心选取最大的部分累加得到，最后更新姐姐能得到的最多浆果数 \( ans \)。
- **作者：gznpp (赞：15)  星级：4星**
    - **关键亮点**：逻辑严谨，分类讨论清晰，代码简洁明了，通过自定义比较函数对剩余果子数进行排序处理。
    - **核心代码**：
```cpp
const int maxn = 1005;
int n, k, a[maxn], mx, mod, ans;

inline bool cmp(int p, int q) {
    return p % mod > q % mod;
}

signed main() {
    orh::useios();

    cin >> n >> k;
    for (rg int i = 1; i <= n; ++i) {
        cin >> a[i];
        up(mx, a[i]);
    }

    for (rg int t = 1; t <= mx; ++t) {
        int full = 0;
        for (rg int i = 1; i <= n; ++i)
            full += a[i] / t;
        if (full < (k >> 1)) break;
        if (full >= k) {
            up(ans, t * k >> 1);
            continue;
        }

        mod = t;
        sort(a + 1, a + n + 1, cmp);
        int tmp = (full - (k >> 1)) * t;
        for (rg int i = 1; i <= n && i + full <= k; ++i)
            tmp += a[i] % t;
        up(ans, tmp); 
    }

    cout << ans << endl;

    return 0;
}
```
    - **核心实现思想**：枚举 \( t \) 作为Elsie篮子里果子数最小值，计算能装满 \( t \) 个果子的篮子数 \( full \) 并分类讨论。当 \( full \) 满足不同条件时，计算Bessie能拿到的果子数并更新答案 \( ans \)，其中在 \( \frac{K}{2} \leq full < K \) 时，通过自定义比较函数对剩余果子数排序，贪心计算Bessie能获得的果子数。
- **作者：KaisuoShutong (赞：8)  星级：4星**
    - **关键亮点**：对题目分析透彻，简洁明了地阐述了为使Bessie获得最多浆果，应使最多的 \( \frac{m}{2} \) 篮果子数目相同这一关键思路，代码实现紧凑。
    - **核心代码**：
```cpp
signed main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++) MAX=max(MAX,b[i]=read());
    std::sort(b+1,b+1+n);
    for(int i=1;i<=MAX;i++)
    {
        std::priority_queue<int> q;int ans=0;
        for(int j=1;j<=n;j++) ans+=b[j]/i,q.push(b[j]%i);
        if(ans<k>>1) continue;
        else if(ans<k)
        {
            int t=ans-(k>>1),cr=t*i;t=(k>>1)-t;
            while(t--) cr+=q.top(),q.pop();
            res=max(res,cr);
        }
        else res=max(res,(k>>1)*i);
    }
    printf("%d\n",res);
    return 0;
}
```
    - **核心实现思想**：枚举取的果子数 \( i \)，计算整篮数 \( ans \) 并根据 \( ans \) 与 \( k \) 和 \( \frac{k}{2} \) 的关系分类讨论。当 \( ans \geq k \) 时，直接计算Bessie能拿到的果子数；当 \( \frac{k}{2} \leq ans < k \) 时，通过优先队列从剩余不满篮子中贪心选取最大的部分累加给Bessie，更新Bessie能得到的最多浆果数 \( res \)。

### 最优关键思路或技巧
 - **枚举策略**：由于树上浆果数范围较小，枚举Elsie篮子中果子数最小值 \( m \)，以此为基础计算Bessie能获得的浆果数，是解决本题的关键。
 - **贪心策略**：在计算Bessie的浆果数时，对于剩余不满篮子的情况，通过优先队列（大顶堆）或排序从剩余果子中选取最大的部分给Bessie，保证Bessie利益最大化。

### 可拓展之处
此类题目属于基于条件枚举和贪心策略的组合优化问题。类似套路可应用于资源分配、背包问题的变体等场景，关键在于找到合适的枚举变量，并根据题目条件进行合理的贪心选择。

### 相似知识点洛谷题目推荐
 - **P1094 [NOIP2007 普及组] 纪念品分组**：通过合理分组，运用贪心策略解决问题，与本题在贪心思想运用上相似。
 - **P1199 [NOIP2010 普及组] 三国游戏**：涉及到对数据的分析和策略选择，需要通过枚举和比较来确定最优解，与本题思路有相通之处。
 - **P1223 排队接水**：同样是基于贪心思想的题目，根据不同条件对数据进行处理以达到最优结果，与本题在算法思维上类似。 

---
处理用时：44.08秒