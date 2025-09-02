# 题目信息

# Propagating tree

## 题目描述

很久以前，有一棵神橡树(oak)，上面有$n$个节点，从$1$~$n$编号，由$n-1$条边相连。它的根是$1$号节点。  

这棵橡树每个点都有一个权值，你需要完成这两种操作：
$1$ $u$ $val$ 表示给$u$节点的权值增加$val$  
$2$ $u$ 表示查询$u$节点的权值   

但是这不是普通的橡树，它是神橡树。  
所以它还有个神奇的性质：当某个节点的权值增加$val$时，它的子节点权值都增加$-val$，它子节点的子节点权值增加$-(-val)$...... 如此一直进行到树的底部。

## 说明/提示

$1\le n,m \le 2\times 10^5$  
$1\le a_i,val \le 1000$  
$1\le u,v \le n$

## 样例 #1

### 输入

```
5 5
1 2 1 1 2
1 2
1 3
2 4
2 5
1 2 3
1 1 2
2 1
2 2
2 4
```

### 输出

```
3
3
0
```

# AI分析结果



## 算法分类
DFS序 + 树状数组

---

## 题解分析与结论

### 核心算法流程
1. **DFS序转换**：通过DFS遍历将树结构转化为线性序列，记录每个节点管辖的子树区间[L[u], R[u]]
2. **奇偶分层标记**：记录每个节点的深度奇偶性，修改时根据根节点奇偶性确定符号
3. **差分树状数组**：利用差分思想将子树区间修改转化为两次单点修改，单点查询转化为前缀和计算

### 解决难点对比
| 题解方案              | 数据结构       | 奇偶处理策略                      | 时间复杂度  | 空间复杂度  |
|---------------------|-------------|-----------------------------|--------|--------|
| 树状数组+符号调整（lzjsy） | 单树状数组       | 根据根节点奇偶性确定整段修改的符号          | O(mlogn) | O(n)   |
| 线段树+懒标记（K2sen）   | 线段树         | 维护统一符号，查询时根据节点奇偶性调整结果     | O(mlogn) | O(4n)  |
| 双树状数组（cirnovsky） | 两独立树状数组     | 分开维护奇偶层修改                   | O(mlogn) | O(2n)  |
| 符号化线段树（SSerxhs）  | 单线段树        | 根据根节点奇偶性确定整段修改的符号，查询时符号转换 | O(mlogn) | O(4n)  |

### 最优思路提炼
1. **DFS序区间化**：将子树操作转化为区间操作
2. **奇偶符号推导**：发现修改传播规律为 (-1)^(depth) 交替变化
3. **差分树状数组**：利用差分数组公式：
   - 修改区间[L, R]：add(L, val), add(R+1, -val)
   - 查询点x：sum(1..x)
4. **符号统一处理**：根节点为奇时，其子树的奇偶层符号按层交替；根节点为偶时整体符号取反

---

## 高分题解推荐（≥4星）

### 1. lzjsy（★★★★☆）
**核心亮点**：
- 单树状数组实现，通过深度奇偶性符号调整统一处理
- 差分优化将区间操作降为O(1)次树状数组操作
- 代码简洁（仅50行），适合算法竞赛场景

**关键代码**：
```cpp
void dfs(int u, int fa) {
    L[u] = ++cnt; // DFS序起点
    for (auto v : edges[u]) {
        if (v != fa) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }
    R[u] = cnt; // DFS序终点
}

void update(int u, int val) {
    int sign = (dep[u] % 2) ? 1 : -1;
    add(L[u], sign * val);
    add(R[u]+1, -sign * val);
}

int query(int u) {
    int sum = get_sum(L[u]);
    return original_val[u] + (dep[u]%2 ? sum : -sum);
}
```

### 2. SSerxhs（★★★★☆）
**核心亮点**：
- 符号永久化线段树，免除pushdown操作
- 直接存储符号化后的值，查询无需额外计算
- 处理2e5数据仅需30ms级别

**关键优化**：
```cpp
void update(int o, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        tree[o] += (l==r) ? (dep[id[l]]%2 ? val : -val) : val;
        return;
    }
    // 符号永久化，无pushdown
    if (ql <= mid) update(lson, ql, qr, val);
    if (qr > mid) update(rson, ql, qr, val);
}
```

### 3. cirnovsky（★★★★☆）
**核心亮点**：
- 双树状数组分别处理奇偶层
- 逻辑对称清晰，修改时直接操作对应层数组
- 查询时差值计算直观

**差分公式**：
```cpp
void modify(int u, int val) {
    int layer = dep[u] % 2;
    bit[layer].add(L[u], val);
    bit[layer].add(R[u]+1, -val);
}

int query(int u) {
    int layer = dep[u] % 2;
    return original[u] + bit[layer].sum(L[u]) - bit[1-layer].sum(L[u]);
}
```

---

## 可视化设计

### 动画方案设计
1. **DFS序生成动画**：
   - 展示DFS遍历过程，用不同颜色标记奇偶层
   - 动态生成L[u]和R[u]区间标记

2. **修改操作动画**：
   ```python
   def visualize_update(u, val):
       highlight_node(u, color='red')
       show_subtree(u, border='dashed')
       for node in subtree(u):
           depth = get_depth(node)
           delta = val * (-1) ** (depth - dep[u])
           animate_value_change(node, delta)
       update_bit(L[u], R[u], val)
   ```

3. **树状数组更新**：
   - 高亮被修改的差分点（L[u]和R[u]+1）
   - 展示前缀和计算时的跳跃过程

### 复古像素风格实现
1. **8位色板**：
   - 奇数层：蓝绿色（#00FFFF）
   - 偶数层：品红色（#FF00FF）
   - 修改特效：黄色闪烁（#FFFF00）

2. **Canvas绘制**：
   ```javascript
   function drawNode(x, y, depth) {
       ctx.fillStyle = depth % 2 ? '#00FFFF' : '#FF00FF';
       ctx.fillRect(x*20, y*20, 18, 18); // 像素方块
       if (updated) ctx.globalAlpha = 0.5; // 修改闪烁特效
   }
   ```

3. **音效设计**：
   - 修改操作：8-bit "blip" 音效（频率 800Hz）
   - 查询操作：短促 "beep" 音效（频率 1200Hz）
   - 错误操作：低频噪音（200Hz）

---

## 相似题目推荐
1. [CF343D Water Tree](https://www.luogu.com.cn/problem/CF343D)  
   （树剖+线段树维护子树状态）
2. [洛谷P3384 树链剖分](https://www.luogu.com.cn/problem/P3384)  
   （树结构转线性区间标准题）
3. [CF877E Danil and a Part-time Job](https://www.luogu.com.cn/problem/CF877E)  
   （子树异或操作+二进制特性）

---

## 核心代码实现（lzjsy方案）
```cpp
#include <vector>
using namespace std;

const int N = 2e5+5;
vector<int> G[N];
int L[N], R[N], dep[N], bit[N], val[N];
int n, m, cnt;

void dfs(int u, int fa) {
    L[u] = ++cnt;
    for (int v : G[u]) 
        if (v != fa) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    R[u] = cnt;
}

void add(int x, int v) {
    for (; x <= n; x += x&-x) bit[x] += v;
}

int query(int x) {
    int res = 0;
    for (; x; x -= x&-x) res += bit[x];
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i=1; i<=n; ++i) scanf("%d", val+i);
    for (int i=1,u,v; i<n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);
    while (m--) {
        int op, u, x;
        scanf("%d%d", &op, &u);
        if (op == 1) {
            scanf("%d", &x);
            int sign = (dep[u]%2) ? 1 : -1;
            add(L[u], sign*x);
            add(R[u]+1, -sign*x);
        } else {
            int sum = query(L[u]);
            printf("%d\n", val[u] + (dep[u]%2 ? sum : -sum));
        }
    }
}
```

---
处理用时：96.79秒