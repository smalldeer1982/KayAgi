# 题目信息

# [USACO10MAR] Great Cow Gathering G

## 题目描述

Bessie 正在计划一年一度的奶牛大集会，来自全国各地的奶牛将来参加这一次集会。当然，她会选择最方便的地点来举办这次集会。

每个奶牛居住在 $N$ 个农场中的一个，这些农场由 $N-1$ 条道路连接，并且从任意一个农场都能够到达另外一个农场。道路 $i$ 连接农场 $A_i$ 和 $B_i$，长度为 $L_i$。集会可以在 $N$ 个农场中的任意一个举行。另外，每个牛棚中居住着 $C_i$ 只奶牛。

在选择集会的地点的时候，Bessie 希望最大化方便的程度（也就是最小化不方便程度）。比如选择第 $X$ 个农场作为集会地点，它的不方便程度是其它牛棚中每只奶牛去参加集会所走的路程之和（比如，农场 $i$ 到达农场 $X$ 的距离是 $20$，那么总路程就是 $C_i\times 20$）。帮助 Bessie 找出最方便的地点来举行大集会。

## 说明/提示

$1\leq N\leq 10^5$，$1\leq A_i\leq B_i\leq N$，$0 \leq C_i,L_i \leq 10^3$。

## 样例 #1

### 输入

```
5 
1 
1 
0 
0 
2 
1 3 1 
2 3 2 
3 4 3 
4 5 3 
```

### 输出

```
15 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕树形 DP 来解决问题，核心思路是先以一个点为根节点计算出该点的不方便程度，再通过状态转移方程递推出其他点的不方便程度，最后找出最小值。部分题解尝试使用树的重心来解决，但发现有边权的树的答案不一定在重心上。

### 所选题解
- **作者：yybyyb（5 星）**
    - **关键亮点**：思路清晰，先指出暴力枚举会超时，然后详细阐述如何通过两次 DFS 进行优化，代码注释详细，易于理解。
    - **个人心得**：无
- **作者：xfydemx（4 星）**
    - **关键亮点**：对状态转移方程的推导有简单说明，代码结构清晰，是典型的树形 DP 解法。
    - **个人心得**：无
- **作者：James_Brady（4 星）**
    - **关键亮点**：将子树内和子树外的情况分开考虑，思路明确，代码实现简洁。
    - **个人心得**：无

### 重点代码
#### yybyyb 的题解
```cpp
// 第一遍 DFS 以任意点为根节点计算一遍
// dis[i] 表示以 i 为根的子树到根的距离之和 
ll DFS(ll u, ll ff) {
    ll tot = 0;
    for (ll i = h[u]; i; i = e[i].next) {
        ll v = e[i].v;
        if (v != ff) {
            ll s = DFS(v, u); // 子树上牛的数量 
            dis[u] += dis[v] + e[i].w * s; // 统计 
            tot += s; // 牛的个数
        }
    }
    return Q[u] = tot + C[u];
}

// 第二遍计算偏移后的值
// 先可以假设走到当前节点的父节点
// 再让当前自己点所有牛退回来，父节点的所有牛走过去即可 
void DFS2(ll u, ll ff) {
    for (ll i = h[u]; i; i = e[i].next) {
        ll v = e[i].v;
        if (v != ff) {
            ll ss = e[i].w;
            f[v] = f[u] - Q[v] * ss + (Sum - Q[v]) * ss;
            DFS2(v, u);
        }
    }
}
```
**核心实现思想**：第一遍 DFS 计算以 1 为根节点时，每个子树到根节点的距离之和以及子树中牛的数量；第二遍 DFS 根据状态转移方程递推出其他节点的不方便程度。

#### xfydemx 的题解
```cpp
inline void dfs (int u, int fa) {
    siz[u] = c[u];
    for (int i = head[u]; i; i = a[i].nxt) {
        int v = a[i].to;
        if (v == fa) continue;
        dfs(v, u);
        siz[u] += siz[v];
        f[u] = f[u] + f[v] + siz[v] * a[i].w;
    }
}

inline void dp (int u, int fa) {
    for (int i = head[u]; i; i = a[i].nxt) {
        int v = a[i].to;
        if (v == fa) continue;
        d[v] = 1LL * d[u] - siz[v] * a[i].w + (cnt - siz[v]) * a[i].w;
        ans = min(ans, d[v]);
        dp(v, u);
    }
}
```
**核心实现思想**：第一遍 DFS 计算以 1 为根节点时，每个子树到根节点的距离之和以及子树中牛的数量；第二遍 DFS 根据状态转移方程递推出其他节点的不方便程度，并更新最小值。

#### James_Brady 的题解
```cpp
void dfs(int u, int fa) { // 计算子树内的 dp 值
    siz[u] = val[u];
    for (int i = h[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        ll w = e[i].w;
        if (v == fa) continue;
        dfs(v, u);
        siz[u] += siz[v];
        dp1[u] += dp1[v] + siz[v] * w;
    }
}

void dfs1(int u, int fa) { // 计算子树外的 dp 值
    for (int i = h[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        ll w = e[i].w;
        if (v == fa) continue;
        dp2[v] = dp2[u] + dp1[u] - (dp1[v] + siz[v] * w) + (siz[1] - siz[v]) * w;
        dfs1(v, u);
    }
}
```
**核心实现思想**：第一遍 DFS 计算子树内的 dp 值，即每个子树到根节点的距离之和；第二遍 DFS 计算子树外的 dp 值，根据状态转移方程递推出其他节点的不方便程度。

### 最优关键思路或技巧
- **树形 DP**：通过两次 DFS 实现树形 DP，第一次 DFS 计算以某个点为根节点时的初始状态，第二次 DFS 根据状态转移方程递推出其他节点的状态。
- **状态转移方程**：通过分析节点之间的关系，得到状态转移方程，从而避免了暴力枚举的高时间复杂度。

### 可拓展之处
同类型题或类似算法套路：
- **树的重心相关问题**：虽然本题中树的重心不一定是答案，但树的重心的性质在其他问题中可能会有应用。
- **换根 DP**：本题的解法本质上是换根 DP，通过先固定一个根节点计算初始状态，再通过状态转移方程递推出其他根节点的状态。

### 推荐题目
- [P1364 医院设置](https://www.luogu.com.cn/problem/P1364)
- [P2986 [USACO10MAR] Great Cow Gathering G](https://www.luogu.com.cn/problem/P2986)
- [P3478 [POI2008]STA-Station](https://www.luogu.com.cn/problem/P3478)

### 个人心得摘录与总结
- **welen**：先写出暴力算法，拿到部分分，再根据暴力算法的思路，结合老师的提示，推导出状态转移方程，最终实现 O(N) 复杂度的 DP 算法。同时，要注意答案的初始值要足够大，否则可能会导致答案错误。
- **TheShadow**：做题一定要算好数据范围，确定好是使用 int 还是用 long long，不然会因为数据范围问题导致答案错误。
- **Caiyy**：在做 DP 题时，要注意数据类型的使用，避免 int 和 long long 相加导致的错误。

---
处理用时：52.72秒