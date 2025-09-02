# 题目信息

# [USACO11JAN] Dividing the Gold S

## 题目描述

Bessie and Canmuu found a sack of N (1 <= N <= 250) gold coins that they wish to divide as evenly as possible. Coin i has value v\_i (1 <= V\_i <= 2,000). The cows would like to split the pile as evenly as they can, but that is not always possible. What is the smallest difference between the values of the two piles?

In addition, the Bessie and Canmuu have found that there might be multiple ways to split the piles with that minimum difference. They would also like to know the number of ways to split the coins as fairly as possible. If it isn't possible to split the piles evenly, Bessie will get the higher-valued pile.

By way of example, consider a sack of five coins of values: 2, 1, 8, 4, and 16. Bessie and Canmuu split the coins into two piles, one pile with one coin worth 16, and the other pile with the remaining coins worth 1+2+4+8=15. Therefore the difference is 16-15 = 1.  This is the only way for them to split the coins this way, so the number of ways to split it evenly is just 1.

Note that same-valued coins can be switched among the piles to increase the number of ways to perform an optimal split. Thus, the set of coins {1, 1, 1, 1} has six different ways to split into two optimal partitions, each with two coins.

## 样例 #1

### 输入

```
5 
2 
1 
8 
4 
16 
```

### 输出

```
1 
1 
```

# AI分析结果

### 综合分析与结论
这些题解均围绕将金币尽可能均匀分成两堆，求解最小差值及对应方案数展开，核心思路均是将问题转化为 01 背包问题。各题解在实现细节和代码风格上有所差异，但本质相同。

### 所选题解
- **作者：妖怪i（5星）**
    - **关键亮点**：思路清晰，分步解决两个问题，代码可读性高，注释详细。
    - **核心代码**：
```cpp
for(int i=1;i<=n;i++)
    for(int j=sum;j>=a[i];j--)
        f[j]=max(f[j],f[j-a[i]]+a[i]);
printf("%d\n",tot-2*f[sum]);
dp[0]=1;
for(int i=1;i<=n;i++)
    for(int j=tot;j>=a[i];j--)
        dp[j]=(dp[j]+dp[j-a[i]])%mod;
printf("%lld",dp[f[sum]]);
```
    - **核心思想**：先通过 01 背包求出金币价值最多能达到总价值一半的多少，得到最小差值；再用 01 背包求该价值的方案数。

- **作者：happy_zero（4星）**
    - **关键亮点**：思路明确，对状态数组的定义和转移解释清晰，代码简洁。
    - **核心代码**：
```cpp
for(int i=1;i<=n;i++){
    for(int j=sum/2;j>=a[i];j--){
        dp[j]=(dp[j]+dp[j-a[i]])%Mod; 
        vis[j]=vis[j]||vis[j-a[i]];
    }
}
for(int i=sum/2;i>=0;i--){
    if(vis[i]){
        cout<<sum-i*2<<endl; 
        cout<<dp[i]%Mod;
        return 0;
    }
}
```
    - **核心思想**：使用 `vis` 数组记录能否取到正好价值为 `i` 的物品，`dp` 数组记录取到该价值的方案数，最后从总价值一半开始向下找可行解。

- **作者：Usada_Pekora（4星）**
    - **关键亮点**：对两个问题的分析简洁明了，代码实现直接。
    - **核心代码**：
```cpp
for (int i = 1; i <= n; i++)
    for (int j = sum / 2; j >= a[i]; j--)
        f[j] = max(f[j], f[j - a[i]] + a[i]);
cout << sum - 2 * f[sum / 2] << endl;
F[0]=1;
for (int i = 1; i <= n; i++)
    for (int j = sum / 2; j >= a[i]; j--)
        F[j] = (F[j] + F[j - a[i]]) % 1000000;
cout << F[f[sum / 2]] << endl;
```
    - **核心思想**：先通过 01 背包求出最小差值，再用 01 背包求该差值下的方案数。

### 最优关键思路或技巧
- **问题转化**：将求金币分成两堆的最小差值问题转化为 01 背包问题，求背包容量为总价值一半时的最大价值。
- **方案数统计**：在 01 背包的基础上，使用额外数组记录达到每个价值的方案数。

### 拓展思路
同类型题可考虑不同物品数量限制（如多重背包、完全背包）下的均分问题，或增加其他约束条件（如分组限制）。类似算法套路可用于解决资源分配、组合优化等问题。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：基础 01 背包问题。
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题。
- [P1776 宝物筛选](https://www.luogu.com.cn/problem/P1776)：多重背包问题。

### 个人心得
- **作者：荣耀南冥**：原代码 91 分，遇到 Hack 数据 `2 1 3` 输出错误，原因是最终结果未正确转移，解决方案是计算每个 $w[i]$ 的最大值，使用 $mid$ 与 $k$ 的 $max$。总结为在处理边界情况时要考虑周全，避免结果转移出错。 

---
处理用时：28.09秒