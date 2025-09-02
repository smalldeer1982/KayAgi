# 题目信息

# Amr and Chemistry

## 题目描述

Amr loves Chemistry, and specially doing experiments. He is preparing for a new interesting experiment.

Amr has $ n $ different types of chemicals. Each chemical $ i $ has an initial volume of $ a_{i} $ liters. For this experiment, Amr has to mix all the chemicals together, but all the chemicals volumes must be equal first. So his task is to make all the chemicals volumes equal.

To do this, Amr can do two different kind of operations.

- Choose some chemical $ i $ and double its current volume so the new volume will be $ 2a_{i} $
- Choose some chemical $ i $ and divide its volume by two (integer division) so the new volume will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558C/2af906789c62f9845274f856d2f941f2357aa169.png)

Suppose that each chemical is contained in a vessel of infinite volume. Now Amr wonders what is the minimum number of operations required to make all the chemicals volumes equal?

## 说明/提示

In the first sample test, the optimal solution is to divide the second chemical volume by two, and multiply the third chemical volume by two to make all the volumes equal $ 4 $ .

In the second sample test, the optimal solution is to divide the first chemical volume by two, and divide the second and the third chemical volumes by two twice to make all the volumes equal $ 1 $ .

## 样例 #1

### 输入

```
3
4 8 2
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
3 5 6
```

### 输出

```
5```

# AI分析结果

### 题目翻译
# Amr 和化学

## 题目描述
Amr 热爱化学，尤其喜欢做实验。他正在为一个新的有趣实验做准备。

Amr 有 $n$ 种不同类型的化学物质。每种化学物质 $i$ 初始体积为 $a_{i}$ 升。为了进行这个实验，Amr 必须将所有化学物质混合在一起，但在此之前所有化学物质的体积必须相等。所以他的任务是让所有化学物质的体积相等。

为了实现这一目标，Amr 可以进行两种不同的操作：
- 选择某种化学物质 $i$ 并将其当前体积翻倍，新体积将变为 $2a_{i}$。
- 选择某种化学物质 $i$ 并将其体积除以 2（整数除法），新体积将变为 $\lfloor \frac{a_{i}}{2}\rfloor$。

假设每种化学物质都装在一个体积无限的容器中。现在 Amr 想知道，使所有化学物质体积相等所需的最少操作次数是多少？

## 说明/提示
在第一个样例测试中，最优解决方案是将第二种化学物质的体积除以 2，并将第三种化学物质的体积乘以 2，使所有体积都等于 4。

在第二个样例测试中，最优解决方案是将第一种化学物质的体积除以 2，并将第二种和第三种化学物质的体积分别除以 2 两次，使所有体积都等于 1。

## 样例 #1
### 输入
```
3
4 8 2
```
### 输出
```
2
```

## 样例 #2
### 输入
```
3
3 5 6
```
### 输出
```
5
```

### 综合分析与结论
这些题解主要围绕如何找到使 $n$ 个数通过乘 2 或除 2 操作后相等的最少操作次数展开。不同题解的思路和方法各有不同，主要分为以下几类：
- **01 - Trie 树与换根 dp**：将数的操作转化为 01 - Trie 树上的节点移动，通过换根 dp 计算所有节点到某个点的最小距离。
- **桶计数与枚举**：维护每个数的所有变换状态，用桶记录状态出现次数和操作步数，枚举交集元素求最小值。
- **贪心算法**：先找公共前缀，再通过调整末尾 0 的个数来确定最终相等的数。

### 所选题解
- **IkunTeddy（4星）**
  - **关键亮点**：思路清晰，将数的操作与 01 - Trie 树结合，通过换根 dp 巧妙地解决了问题，代码实现较为规范。
  - **核心代码**：
```cpp
void insert(int &v,int x,int p,int id,int d){
    if(!v)v=++cnt;
    dep[v]=d;
    tree[v].cnt++;
    if(!p){
        node[id]=v;
        return ;
    }
    int c=(x>>p-1)&1;
    insert(tree[v].son[c],x,p-1,id,d+1);
}
int dp[maxn];
int ans=0x3f3f3f3f;
void dfs(int u){
    ans=min(ans,dp[u]);
    for(int i=0;i<1;i++){
        int v=tree[u].son[i];
        if(!v)continue;
        dp[v]=dp[u]+n-2*tree[v].cnt;
        dfs(v);
    }
}
```
  - **核心思想**：`insert` 函数将数插入 01 - Trie 树，记录节点深度和节点计数。`dfs` 函数进行换根 dp，更新每个节点的 dp 值，找到最小的操作次数。

- **DennyQi（4星）**
  - **关键亮点**：通过桶计数的方式避免了使用 `set` 带来的高复杂度，同时对重复状态的处理思路巧妙，代码简洁。
  - **核心代码**：
```cpp
for(int i = 1; i <= n; ++i){
    x = a[i];
    int j = 0, k = 0, las = -1;
    while(x > 0){
        if(las == 0){
            ++b[x];
            sum[x] += j;
            las = (x&1);
            x >>= 1;
            ++j;
            continue;
        }
        y = x;
        k = 0;
        while(y <= lim){
            ++b[y];
            sum[y] += j+k;				
            y <<= 1;
            ++k;
        }
        las = (x&1);
        x >>= 1;
        ++j;
    }
}
ans = INF;
for(int i = 0; i <= lim; ++i){
    if(b[i] >= n){
        ans = min(ans, sum[i]);
    }
}
```
  - **核心思想**：遍历每个数，将其所有可能的变换状态用桶 `b` 记录出现次数，用 `sum` 记录到达该状态的操作步数。最后枚举所有状态，找到出现次数不少于 $n$ 的状态中操作步数最小的。

- **KokiNiwa（4星）**
  - **关键亮点**：提出了将数转化为二进制串插入字典树的思路，对根节点的分析准确，并且提到了优化方法。
  - **核心代码**：
```cpp
void dfs(int now) {
    if (now > maxVal) return ;
    int lson = now << 1, rson = now << 1 | 1;
    dfs(lson), dfs(rson);
    sze[now] = mark[now];
    if (lson <= maxVal) sze[now] += sze[lson];
    if (rson <= maxVal) sze[now] += sze[rson];
    return ;
}
for (reg int id = root << 1; id <= maxVal; id = id << 1)
    allDis[id] = allDis[id >> 1] + (totN - sze[id]) - sze[id];
```
  - **核心思想**：`dfs` 函数计算每个节点子树中加粗节点（表示给定数的节点）的个数。通过换根操作，更新每个节点的 `allDis` 值，即所有加粗节点到该节点的距离和。

### 最优关键思路或技巧
- **二进制与树结构结合**：将数的乘 2 和除 2 操作转化为二进制的位操作，进而对应到树结构（如 01 - Trie 树、完全二叉树）上的节点移动，利用树的性质解决问题。
- **换根 dp**：通过换根操作，避免了枚举所有可能的目标节点，降低了时间复杂度。
- **桶计数**：用桶记录状态出现次数和操作步数，避免了使用复杂数据结构带来的高复杂度，同时可以方便地处理重复状态。

### 可拓展之处
同类型题目可能会有不同的操作规则或限制条件，但可以借鉴本题的思路，将操作转化为某种数据结构上的操作，再利用相应的数据结构和算法（如树、图、动态规划等）解决问题。例如，可能会有更多种操作方式，或者对最终相等的数有额外的限制条件。

### 推荐题目
1. [P2580 于是他错误的点名开始了](https://www.luogu.com.cn/problem/P2580)：考察 Trie 树的基本应用。
2. [P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)：涉及树的遍历和异或运算，与本题的树结构和位运算有一定关联。
3. [P1481 魔族密码](https://www.luogu.com.cn/problem/P1481)：可以用 Trie 树解决字符串相关问题，与本题的 Trie 树应用思路类似。

### 个人心得摘录与总结
- **KokiNiwa**：提到在使用 Trie 树时要记住考虑一个字符串出现多次的情况，自己已经在这里栽了两回，提醒大家在使用 Trie 树时要注意这种细节问题。

---
处理用时：53.76秒