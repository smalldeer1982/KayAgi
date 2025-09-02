# 题目信息

# 「MXOI Round 1」城市

## 题目描述

小 C 是 F 国的总统，尽管这个国家仅存在于网络游戏中，但他确实是这个国家的总统。

F 国由 $n$ 个城市构成，这 $n$ 个城市之间由 $n-1$ 条双向道路互相连接。保证从任意一个城市出发，都能通过这 $n-1$ 条双向道路，到达任意一个城市。

当然，通过这些双向道路是要收费的。通过第 $i$ 条双向道路，需要花费 $c_i$ 元。我们称 $c_i$ 为第 $i$ 条双向道路的费用。

我们定义 $cost(x,y)$ 表示从城市 $x$ 到城市 $y$ 的简单路径上，所有经过的双向道路的费用之和。特殊地，当 $x=y$ 时，$cost(x,y)=0$。

为了促进 F 国发展，小 C 新建了一个城市 $n+1$。现在他需要再新建一条双向道路，使得城市 $n+1$ 也可以通过这 $n$ 条双向道路到达任意一个城市。

他共有 $q$ 个新建道路的方案，每个方案会给定两个参数 $k_i,w_i$；对于每一个方案，你需要求出在新建一条连接城市 $k_i$ 和城市 $n+1$ 且费用为 $w_i$ 的双向道路后，所有 $cost(i,j)$ 之和，即 $\sum\limits_{i=1}^{n+1} \sum\limits_{j=1}^{n+1} cost(i,j)$。

由于答案可能很大，所以你只需要输出答案对 $998244353$ 取模的结果。

**方案之间相互独立**，也就是说所有方案不会影响现有的道路，这些方案不会真正被施行。

## 说明/提示

#### 【样例解释 #1】

在新建一条连接城市 $1$ 和城市 $5$ 且费用为 $2$ 的双向道路后，F 国的道路如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/j871257i.png)

例如，此时 $cost(4,5)=9$，$cost(1,3)=5$。

容易求得此时 $\sum\limits_{i=1}^{n+1} \sum\limits_{j=1}^{n+1} cost(i,j)=100$。

#### 【样例 #3】

见附加文件中的 `city/city3.in` 与 `city/city3.ans`。

该样例满足测试点 $4$ 的限制。

#### 【样例 #4】

见附加文件中的 `city/city4.in` 与 `city/city4.ans`。

该样例满足测试点 $11$ 的限制。

#### 【样例 #5】

见附加文件中的 `city/city5.in` 与 `city/city5.ans`。

该样例满足测试点 $14$ 的限制。

#### 【样例 #6】

见附加文件中的 `city/city6.in` 与 `city/city6.ans`。

该样例满足测试点 $20$ 的限制。

#### 【数据范围】

对于 $100\%$ 的数据，$2 \le n \le 2\times10^5$，$1 \le q \le 2\times10^5$，$1 \le u_i,v_i,k_i \le n$，$1 \le c_i,w_i \le 10^6$，保证从任意一个城市出发，都能通过原本存在的 $n-1$ 条双向道路，到达任意一个城市。

|测试点编号|$n \le$|$q \le$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1\sim3$|$80$|$80$|无|
|$4\sim7$|$5000$|$5000$|无|
|$8\sim10$|$5000$|$2\times10^5$|无|
|$11\sim13$|$2\times10^5$|$2\times10^5$|A|
|$14\sim16$|$2\times10^5$|$2\times10^5$|B|
|$17\sim20$|$2\times10^5$|$2\times10^5$|无|

特殊性质 A：保证对于所有的 $1 \le i \lt n$，都有 $u_i=i,v_i=i+1$。

特殊性质 B：保证对于所有的 $1 \le i \le q$，都有 $k_i=1$。

## 样例 #1

### 输入

```
4 2
2 1 3
3 2 2
4 2 4
1 2
2 2```

### 输出

```
100
88```

## 样例 #2

### 输入

```
9 5
2 3 6
6 1 4
5 2 10
2 4 1
9 1 9
2 8 3
1 2 3
7 4 8
4 9
7 3
6 1
9 7
2 1
```

### 输出

```
1050
1054
970
1148
896```

# AI分析结果



## 算法分类
换根 DP

## 题解思路与算法要点

### 核心思路
所有题解的核心思路可归纳为两步：
1. **预处理原树的贡献**：计算原树中所有点对的距离和
2. **快速处理新增边的影响**：利用树的结构特性，在 O(1) 时间内计算新边带来的增量贡献

### 关键算法实现
#### 换根 DP 法（最优思路）
1. **距离和计算**：  
   - 通过两次 DFS 计算每个节点到其他所有节点的距离和  
   - `dfs1` 计算子树内距离和（自底向上）  
   - `dfs2` 计算整棵树距离和（自顶向下）  
   - 转移方程：`f[v] = f[u] + (n - 2 * sz[v]) * w`  
   - 其中 `sz[v]` 为子树大小，`w` 为边权

2. **新增边计算**：  
   - 新增边贡献为 `2 * (f[k] + n * w)`  
   - `f[k]` 表示原树中所有点到 k 的距离和  
   - `n * w` 表示新边被经过的总次数

#### 边贡献分析法
1. **边贡献公式**：  
   - 对边 `u-v`，贡献为 `2 * sz[v] * (n - sz[v]) * w`  
   - 新增边后，k 的祖先路径上的边贡献会发生变化  
   - 预处理路径前缀和实现 O(1) 查询

### 解决难点
1. **距离和转移的数学推导**：通过父节点到子节点的距离变化推导出递推式  
2. **负数取模处理**：在转移方程中可能出现负数，需通过 `(x % mod + mod) % mod` 处理  
3. **大规模数据优化**：将 O(n^2) 的暴力计算优化为 O(n) 预处理 + O(1) 查询

## 高分题解推荐 (≥4★)

### 1. iiiiuyang（5★）
**亮点**：  
- 最简洁的换根 DP 实现（仅 30 行核心代码）  
- 清晰的两次 DFS 结构  
- 直接给出最终答案公式 `ans + (f[k] + n * w) * 2`

```cpp
auto dfs1=[&](auto dfs1,int now,int father)->void {
    siz[now]=1;
    for(auto [to,val]:G[now]) 
        if(to!=father) 
            dfs1(dfs1,to,now), siz[now]+=siz[to], Madd(f[1],dis[to]);
};

auto dfs2=[&](auto dfs2,int now,int father)->void {
    Madd(ans,f[now]);
    for(auto [to,val]:G[now])
        if(to!=father)
            f[to]=Cadd(f[now],Cmul(val,((siz[1]-2*siz[to])%Mod+Mod)%Mod)),
            dfs2(dfs2,to,now);
};
```

### 2. Night_sea_64（4.5★）
**亮点**：  
- 包含详细的换根推导过程说明  
- 处理负数取模的规范化实现  
- 添加调试注释提醒关键点

```cpp
void dfs2(int x,int fa){
    for(auto [to,val]:G[x]){
        if(to!=fa){
            f[to]=(f[x]+val*(n-2*siz[to]))%mod;
            dfs2(to,x);
        }
    }
}
```

### 3. _Spectator_（4★）
**亮点**：  
- 使用 `Mod()` 函数统一处理取模  
- 分离子树内/外贡献计算  
- 完整展示预处理到查询的全流程

```cpp
void dfs2(int x,int fa){
    for(auto [to,w]:G[x]){
        if(to!=fa){
            f[to] = (f[x] + w*(n-2*siz[to])%mod + mod) % mod;
            dfs2(to,x);
        }
    }
}
```

## 最优技巧提炼

### 换根 DP 模板
1. **第一次 DFS**：计算子树大小 `sz[]` 和根节点距离和  
2. **第二次 DFS**：通过父节点递推所有节点的全局距离和  
3. **递推公式**：`f[v] = f[u] + w * (n - 2 * sz[v])`

### 快速增量计算
新增边贡献 = 原树到 k 的总距离 * 2 + 新边权值 * 2n  
公式：`ans_total = ans_original + 2*(f[k] + n*w)`

## 同类题目推荐
1. [P3478 [POI2008] STA-Station](https://www.luogu.com.cn/problem/P3478)  
   （换根 DP 模板题，求最大深度和）
2. [P3041 [USACO12FEB] Video Game G](https://www.luogu.com.cn/problem/P3041)  
   （结合树结构的动态规划）
3. [P2986 [USACO10MAR] Great Cow Gathering G](https://www.luogu.com.cn/problem/P2986)  
   （带权重的换根 DP 变种）

## 算法可视化设计

### 动画演示方案
1. **树结构绘制**：  
   - 使用 Canvas 绘制初始树，边权标注在连线旁  
   - 节点按层排列，根节点在顶部

2. **换根过程演示**：  
   - 用红色高亮当前计算的节点  
   - 动态显示 `f[]` 数组的更新过程：  
     ```
     更新节点5: f[5] = f[2] + 3*(7-2*2) 
               = 15 + 3*3 = 24
     ```

3. **新增边效果**：  
   - 闪烁显示新添加的边  
   - 用绿色标注受影响的路径  
   - 显示增量计算公式：`+2*(24 + 7*2)`

### 交互功能
1. **步进控制**：  
   - 按钮：播放/暂停/单步  
   - 拖拽进度条查看任意步骤

2. **数据面板**：  
   - 实时显示 `sz[]` 和 `f[]` 的值  
   - 高亮当前计算的数学表达式

3. **复古风格**：  
   - 8-bit 像素字体  
   - 芯片音效：  
     - 节点更新时播放 "哔" 声  
     - 计算完成时播放经典 FC 过关音效

## 核心代码实现
完整换根 DP 解法（iiiiuyang 改进版）：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5, mod=998244353;

vector<pair<int,int>> G[N];
int n,q,siz[N],f[N],ans;

void dfs1(int u,int fa){
    siz[u]=1;
    for(auto [v,w]:G[u]){
        if(v==fa) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        f[u]=(f[u]+f[v]+w*siz[v])%mod;
    }
}

void dfs2(int u,int fa){
    for(auto [v,w]:G[u]){
        if(v==fa) continue;
        f[v]=(f[u]+w*(n-2*siz[v])%mod+mod)%mod;
        dfs2(v,u);
    }
}

signed main(){
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int u,v,w; cin>>u>>v>>w;
        G[u].emplace_back(v,w);
        G[v].emplace_back(u,w);
    }
    
    dfs1(1,0);
    dfs2(1,0);
    
    for(int i=1;i<=n;i++) ans=(ans+f[i])%mod;
    
    while(q--){
        int k,w; cin>>k>>w;
        cout<<(ans + 2*(f[k] + n*w%mod))%mod <<endl;
    }
}
```

该实现通过两个 DFS 完成换根 DP 计算，核心亮点：
1. 使用 `emplace_back` 优化邻接表存储  
2. 模运算内嵌在状态转移中  
3. 最终答案公式直观体现增量计算

---
处理用时：93.21秒