# 题目信息

# [USACO08JAN] Cell Phone Network G

## 题目描述

Farmer John has decided to give each of his cows a cell phone in hopes to encourage their social interaction. This, however, requires him to set up cell phone towers on his N (1 ≤ N ≤ 10,000) pastures (conveniently numbered 1..N) so they can all communicate.

Exactly N-1 pairs of pastures are adjacent, and for any two pastures A and B (1 ≤ A ≤ N; 1 ≤ B ≤ N; A ≠ B) there is a sequence of adjacent pastures such that A is the first pasture in the sequence and B is the last. Farmer John can only place cell phone towers in the pastures, and each tower has enough range to provide service to the pasture it is on and all pastures adjacent to the pasture with the cell tower.

Help him determine the minimum number of towers he must install to provide cell phone service to each pasture.

Farmer John 想让他的所有牛用上手机以便相互交流。他需要建立几座信号塔在 $N$ 块草地中。已知与信号塔相邻的草地能收到信号。给你 $N-1$ 个草地 $(A,B)$ 的相邻关系，问：最少需要建多少个信号塔能实现所有草地都有信号。


## 样例 #1

### 输入

```
5
1 3
5 2
4 3
3 5
```

### 输出

```
2
```

# AI分析结果



### 综合分析与结论
本题是典型的树形最小覆盖问题，核心解法集中在树形DP与贪心策略。树形DP通过三状态（自覆盖/父覆盖/子覆盖）确保最优解，贪心通过深度优先选择父节点建塔实现高效覆盖。树形DP解法更严谨，贪心解法更高效但需正确性验证。

---

### 精选题解分析

#### 1. zbwer（五星）
**亮点**：  
- 标准三状态树形DP（自覆盖/父覆盖/子覆盖），状态定义清晰  
- 详细推导状态转移方程，特别处理"子覆盖必须选至少一个儿子"的难点  
- 优化计算差值避免暴力枚举，时间复杂度O(n)

**核心代码**：
```cpp
void dfs(int x,int fa) {
    int special_son = 0; f[x][0] = 1;
    for(int i=head[x];i;i=Next[i]) {
        int y = ver[i];
        if(y == fa) continue;
        dfs(y, x);
        f[x][0] += min(f[y][0], min(f[y][1], f[y][2]));
        f[x][2] += min(f[y][0], f[y][1]);
        if((f[special_son][0]-min(f[special_son][0], f[special_son][1])) > (f[y][0]-min(f[y][0], f[y][1])))
            special_son = y;
    }
    f[x][1] = f[special_son][0];
    // 其他子节点处理...
}
```

#### 2. loceaner（四星半）
**亮点**：  
- 完整的状态转移方程推导，配有详细注释  
- 反悔机制处理必须覆盖的情况，用排序优化选择  
- 代码结构清晰，适合学习树形DP框架

**核心思路**：  
- `f[i][0]`自覆盖：累加所有子节点三种状态的最小值  
- `f[i][2]`子覆盖：累加`min(son自覆盖, son子覆盖)`后，若全选子覆盖则强制选一个最优自覆盖

---

### 关键技巧总结
1. **三状态树形DP**：  
   - `dp[u][0]`：u自建塔，覆盖自身及相邻  
   - `dp[u][1]`：u不建塔，由父节点覆盖  
   - `dp[u][2]`：u不建塔，至少一个子节点覆盖  
2. **反悔机制**：  
   当计算子覆盖时，先假设所有子节点选择子覆盖，通过差值计算强制替换最优子节点为自覆盖  
3. **贪心策略**：  
   按深度倒序处理，未覆盖节点强制在父节点建塔，覆盖三代节点  

---

### 拓展练习
1. [P2279 消防局的设立](https://www.luogu.com.cn/problem/P2279)（覆盖距离2的树形覆盖）  
2. [P2458 保安站岗](https://www.luogu.com.cn/problem/P2458)（带权值的三状态树形DP）  
3. [UVA1218 完美服务](https://www.luogu.com.cn/problem/UVA1218)（单覆盖条件下的最小节点选择）  

---

### 代码实现建议
树形DP标准模板：
```cpp
void dfs(int u, int fa) {
    dp[u][0] = 1; // 自覆盖
    int sum = 0, diff = INF;
    for(int v : G[u]) {
        if(v == fa) continue;
        dfs(v, u);
        dp[u][0] += min({dp[v][0], dp[v][1], dp[v][2]});
        dp[u][1] += min(dp[v][0], dp[v][2]); // 父覆盖
        sum += min(dp[v][0], dp[v][2]);
        diff = min(diff, dp[v][0] - min(dp[v][0], dp[v][2]));
    }
    dp[u][2] = sum + (diff > 0 ? diff : 0); // 子覆盖反悔机制
}
```

---
处理用时：57.80秒