# 题目信息

# [USACO12FEB] Nearby Cows G

## 题目描述

Farmer John has noticed that his cows often move between nearby fields. Taking this into account, he wants to plant enough grass in each of his fields not only for the cows situated initially in that field, but also for cows visiting from nearby fields.

Specifically, FJ's farm consists of N fields (1 <= N <= 100,000), where some pairs of fields are connected with bi-directional trails (N-1 of them in total).  FJ has designed the farm so that between any two fields i and j, there is a unique path made up of trails connecting between i and j. Field i is home to C(i) cows, although cows sometimes move to a different field by crossing up to K trails (1 <= K <= 20).

FJ wants to plant enough grass in each field i to feed the maximum number of cows, M(i), that could possibly end up in that field -- that is, the number of cows that can potentially reach field i by following at most K trails.  Given the structure of FJ's farm and the value of C(i) for each field i, please help FJ compute M(i) for every field i.

给你一棵 $n$ 个点的树，点带权，对于每个节点求出距离它不超过 $k$ 的所有节点权值和 $m_i$。

## 说明/提示

There are 6 fields, with trails connecting (5,1), (3,6), (2,4), (2,1), and (3,2).  Field i has C(i) = i cows.


Field 1 has M(1) = 15 cows within a distance of 2 trails, etc.

【数据范围】  
对于 $100\%$ 的数据：$1 \le n \le 10^5$，$1 \le k \le 20$，$0 \le c_i \le 1000$

## 样例 #1

### 输入

```
6 2 
5 1 
3 6 
2 4 
2 1 
3 2 
1 
2 
3 
4 
5 
6 
```

### 输出

```
15 
21 
16 
10 
8 
11 
```

# AI分析结果



## 算法分类  
树形DP + 容斥原理

---

## 综合分析与结论  
### 核心思路
所有题解均基于两次DFS的树形DP框架：  
1. **第一次DFS**（自底向上）：计算子树贡献  
   - `f[i][j]`表示节点i的子树中，距离i**恰好j步**的权值和  
   - 递推公式：`f[i][j] = Σ f[son][j-1]`  
2. **第二次DFS**（自顶向下）：计算父系贡献  
   - 通过父节点`fa`的`f[fa][j-1]`推导子节点贡献  
   - 关键容斥操作：`f[son][j] -= f[son][j-2]` 避免重复计算子树部分  

### 可视化设计要点
1. **树结构动态绘制**  
   - 用Canvas绘制树结构，节点按层级排列，边用线条连接  
   - 第一次DFS时，用绿色高亮当前子树，逐步向上填充蓝色表示累加过程  
   - 第二次DFS时，用红色箭头表示父节点向子节点的信息传递，黄色闪烁标出容斥步骤  
2. **数据标记**  
   - 每个节点旁显示`f[i][0]`到`f[i][k]`的数值，随操作实时更新  
   - 当触发容斥时，在对应`j-2`层级显示红色负号动画  
3. **8位像素风格**  
   - 树节点用16x16像素方块表示，DFS移动时播放经典"滴"声效  
   - 完成全部计算时播放FC游戏通关音效，失败时播放短促"哔"声  

---

## 题解清单（4星及以上）  
### 1. asuldb（4.5★）  
**核心亮点**：  
- 最简洁的双向DFS结构  
- 注释明确容斥原理（`f[k][j] -= f[k][j-2]`）  
- 完整代码仅40行，变量命名清晰  

**关键代码片段**：  
```cpp
void build(int r){ // 第一次DFS
    for(re int j=1;j<=k;j++)
        f[r][j] += f[e[i].v][j-1];
}

void dfs(int r){ // 第二次DFS
    for(re int j=k;j>=2;j--)
        f[e[i].v][j] -= f[e[i].v][j-2];
    for(re int j=1;j<=k;j++)
        f[e[i].v][j] += f[r][j-1];
}
```

### 2. Yuyuanqi（4.2★）  
**核心亮点**：  
- 明确定义`d[i][j]`和`f[i][j]`的双数组结构  
- 详细注释说明父子关系转移  
- 完整处理边界条件（`j-2 >=0`的判断）  

**个人心得摘录**：  
> "这类树上DP的题，每个节点的答案与父亲和儿子都有关，两次DFS遍历顺序不同是关键"

### 3. juruo_zjc（4.0★）  
**核心亮点**：  
- 手绘示意图辅助理解容斥原理  
- 用循环倒序处理避免状态覆盖  
- 代码中`for(int j=k;j>=2;j--)`强调执行顺序重要性  

---

## 核心算法实现  
### 标准实现代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5, K=25;
vector<int> G[N];
int f[N][K], n, k;

void dfs1(int u, int fa){
    for(int v : G[u]){
        if(v == fa) continue;
        dfs1(v, u);
        for(int j=1; j<=k; j++) 
            f[u][j] += f[v][j-1];
    }
}

void dfs2(int u, int fa){
    for(int v : G[u]){
        if(v == fa) continue;
        // 容斥：减去子树重复部分
        for(int j=k; j>=2; j--)
            f[v][j] -= f[v][j-2];
        // 继承父节点贡献
        for(int j=1; j<=k; j++)
            f[v][j] += f[u][j-1];
        dfs2(v, u);
    }
}

int main(){
    cin >> n >> k;
    for(int i=1; i<n; i++){
        int u, v; cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    for(int i=1; i<=n; i++) 
        cin >> f[i][0]; // 初始化0步
        
    dfs1(1, -1);
    dfs2(1, -1);
    
    for(int i=1; i<=n; i++){
        int sum = 0;
        for(int j=0; j<=k; j++)
            sum += f[i][j];
        cout << sum << "\n";
    }
}
```

---

## 同类型题拓展  
1. **HDU 2196** - 求树中每个节点的最远距离  
2. **POJ 3107** - 求树的重心（删除某点后最大子树最小）  
3. **CF 1092F** - 带权树的路径统计  

---

## 推荐洛谷题目  
1. **P1272 重建道路** - 树形DP+背包思想  
2. **P2015 二叉苹果树** - 树形DP保留特定边  
3. **P2585 三色二叉树** - 状态转移与树结构结合  

---

## 学习启示  
1. **容斥时序**：必须先处理子树再处理父节点，第二次DFS的倒序循环是关键  
2. **空间优化**：k≤20时可用滚动数组，但本题n较大直接开二维更清晰  
3. **调试技巧**：对样例手工模拟j=1和j=2的情况，验证容斥是否正确  

---

通过将树形DP与容斥原理结合，此类问题能在O(nk)时间复杂度内高效解决，其核心思想可拓展至各类需要同时考虑子树和父系贡献的树结构问题。

---
处理用时：96.62秒