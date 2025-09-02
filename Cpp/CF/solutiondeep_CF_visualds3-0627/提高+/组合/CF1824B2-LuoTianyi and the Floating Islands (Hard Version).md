# 题目信息

# LuoTianyi and the Floating Islands (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ k\le n $ . You can make hacks only if both versions of the problem are solved.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B2/12896184a3f823fcd8518f46dc5b68823c932f0f.png) Chtholly and the floating islands.LuoTianyi now lives in a world with $ n $ floating islands. The floating islands are connected by $ n-1 $ undirected air routes, and any two of them can reach each other by passing the routes. That means, the $ n $ floating islands form a tree.

One day, LuoTianyi wants to meet her friends: Chtholly, Nephren, William, .... Totally, she wants to meet $ k $ people. She doesn't know the exact positions of them, but she knows that they are in pairwise distinct islands. She define an island is good if and only if the sum of the distances $ ^{\dagger} $ from it to the islands with $ k $ people is the minimal among all the $ n $ islands.

Now, LuoTianyi wants to know that, if the $ k $ people are randomly set in $ k $ distinct of the $ n $ islands, then what is the expect number of the good islands? You just need to tell her the expect number modulo $ 10^9+7 $ .

 $ ^{\dagger} $ The distance between two islands is the minimum number of air routes you need to take to get from one island to the other.

## 说明/提示

In the first example the air routes form the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B2/f98245759af7851bb13c350e387c9b296063f10a.png) If the people are in the islands $ 1 $ and $ 2 $ , then islands $ 1 $ and $ 2 $ will be good.

The sum of the distances from island $ 1 $ or $ 2 $ to all the people is $ 1+0=1 $ , which is the minimal. While the sum of the distances from island $ 3 $ to all the people is $ 2+1=3 $ , which is greater than $ 1 $ .

Like this, when the people are in island $ 1 $ and $ 3 $ , then islands $ 1,2 $ and $ 3 $ will be good.

When the people are in islands $ 1 $ and $ 4 $ , then islands $ 1,2,3 $ and $ 4 $ will be good.

When the people are in islands $ 2 $ and $ 3 $ , then islands $ 2 $ and $ 3 $ will be good.

When the people are in islands $ 2 $ and $ 4 $ , then islands $ 2,3 $ and $ 4 $ will be good.

When the people are in islands $ 3 $ and $ 4 $ , then islands $ 3 $ and $ 4 $ will be good.

So the expect of the number of the good islands is $ \frac{16}{6} $ , which equals to $ 666666674 $ modulo $ 10^9+7 $ .

In the second example the air routes form the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B2/2f411e079090512cd14c27f9186226921a07c282.png)We can see that there is one person in each island, and only the island $ 3 $ is good. So the expect number is $ 1 $ .

## 样例 #1

### 输入

```
4 2
1 2
2 3
3 4```

### 输出

```
666666674```

## 样例 #2

### 输入

```
5 5
1 2
2 3
3 4
3 5```

### 输出

```
1```

# AI分析结果



## 算法分类
组合数学 / 树形结构

---

## 题解思路与核心难点分析

### 核心思路
1. **奇偶性分类**  
   - 当 $k$ 为奇数时，所有题解均证明**存在且仅存在 1 个好点**，直接输出 $1$。
   - 当 $k$ 为偶数时，重点在于**计算每条边的贡献**：若边的两侧各有 $k/2$ 个被选点，则该边为"好边"，最终期望数为好边数+1。

2. **组合数学实现**  
   - 预处理阶乘与逆元加速组合数计算：$C(n,k) = \frac{n!}{k!(n-k)!} \mod 10^9+7$  
   - DFS 遍历树，计算子树大小 $sz[u]$，枚举每条边计算贡献 $\sum C(sz[u],k/2) \cdot C(n-sz[u],k/2)$

---

## 题解评分（≥4星）

### 题解1：Reunite (5星)
- **亮点**：  
  - 明确分类奇偶性，数学推导严谨  
  - 代码简洁，预处理阶乘+逆元实现组合数 $O(1)$ 查询  
  - 核心逻辑仅需一次DFS，时间复杂度 $O(n)$

### 题解2：Register_int (5星)
- **亮点**：  
  - 详细证明好点唯一性，解释"好边"与连通块关系  
  - 代码包含完整注释，变量命名清晰（如 `sz[v]` 表示子树大小）

### 题解3：Un1quAIoid (4星)  
- **亮点**：  
  - 提出容斥思路，通过递推优化组合数求和  
  - 代码实现递推公式，展示不同角度的数学推导

---

## 最优思路提炼

### 关键步骤
1. **奇偶特判**：奇数直接返回1，避免多余计算  
2. **组合数优化**：预处理阶乘逆元，实现 $O(1)$ 组合数查询  
3. **树遍历统计**：DFS计算子树大小，枚举边计算贡献  
4. **模运算处理**：使用快速幂求逆元，避免除法误差

### 代码片段
```cpp
void dfs(int u, int fa) {
    siz[u] = 1;
    for (int v : e[u]) {
        if (v == fa) continue;
        dfs(v, u);
        siz[u] += siz[v];
        ans = (ans + C(siz[v], k/2) * C(n-siz[v], k/2)) % mod;
    }
}
```

---

## 同类型题目推荐
1. **P1351 [NOIP2014 提高组] 联合权值**  
   - 树中距离为2的节点权值积，类似树遍历与组合统计

2. **P2607 [ZJOI2008] 骑士**  
   - 树形DP结合组合选择问题

3. **CF342E Xenia and Tree**  
   - 树结构动态更新与距离计算

---

## 可视化算法演示

### 核心流程设计
1. **树形结构展示**  
   - 使用Canvas绘制树形图，节点以圆点表示，边以线段连接

2. **动态DFS过程**  
   - **颜色标记**：当前遍历的节点显示为红色，已处理子树显示为绿色  
   - **数值标注**：每个节点显示 `sz[u]`，边显示贡献值 $C(sz,k/2) \cdot C(n-sz,k/2)$

3. **组合数计算高亮**  
   - 当计算某条边时，左右子树以不同背景色区分（如左蓝右黄）  
   - 弹出公式提示：$C(4,1) \times C(2,1) = 4 \times 2 = 8$

### 复古像素风格
- **调色板**：16色（深绿背景，亮蓝节点，红色高亮）  
- **音效设计**：  
  - 节点遍历时播放8-bit "哔"声  
  - 贡献计算成功时播放上升音阶  
- **自动演示**：按DFS顺序自动播放，速度可调

---

## 结论
本题解通过树遍历与组合数学，将问题转化为边的贡献统计。关键点在于**奇偶分类**与**组合数优化计算**，时间复杂度 $O(n)$，适合大规模数据。可视化设计通过动态树遍历与公式标注，直观展示算法核心逻辑。

---
处理用时：63.58秒