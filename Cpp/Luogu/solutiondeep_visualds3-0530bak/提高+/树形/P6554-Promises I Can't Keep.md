# 题目信息

# Promises I Can't Keep

## 题目背景

>I had so much certainty  
Til that moment I lost control  
And I've tried but it never was up to me  
I've got no worse enemy  
Than the fear of what's still unknown  
And the time's come to realize there will be  
Promises I can't keep

## 题目描述

RFMC 给了你一个电路，一个电源，他希望你能把电源接在电路的某一个节点上，让电流流通，并答应给你电路显示屏上的数那么多钱。

这个电路有 $n$ 个节点，每个节点有一个权值 $val_i$，以 $n-1$ 条导线互相连通。你可以把电源接在任意一个起点上。接着，电流从这个节点开始流。若当前电源接到了一个节点 $u$，则接下来电流会**等概率**且**不重复经过一个点地**流向**一个叶子节点**，电流流过的所有节点的权值即为电路显示屏上的数（叶子节点即为 **除了 $u$** 的度数为 1 的节点）。

现在你有 $n$ 种接电源的选择，你希望接上电源以后期望得分越高越好，所以你现在就要在规定的时间内求出这 $n$ 种期望值中最大的的一个。

## 说明/提示

样例一的解释：

电源接在 5 号节点时有两种情况：$5\rightarrow 1\rightarrow 2\rightarrow 3$ 或 $5\rightarrow 1\rightarrow 2\rightarrow 4$，两种情况得分分别为 8 和 6，期望值即为 7，可以证明没有其他节点接通电源的期望值比 7 大。

---

**本题采用捆绑测试，每一档部分分对应一个 subtask。**

对于 $30\%$ 的数据，保证 $2<n\le 10^3$。  
对于另外 $20\%$ 的数据，保证是一条链。  
对于所有的数据，保证 $2<n\le 5\times10^5,\  |val_i|\le10^4$。

本题的 special judge 代码已经在附件中给出。

附：本题数据量较大，可以采用更快的读入方法。（标程在用 ```scanf``` 的情况下可以通过）

~~后记：按照题目名称，RFMC 是不会遵守诺言的（大雾~~

题目名其实是一首歌名啦。

## 样例 #1

### 输入

```
5
1 2
1 5
2 3
2 4
2 3 1 -1 2```

### 输出

```
7.0000```

# AI分析结果



## 【唯一算法分类】
换根DP

## 【题解思路与解决难点】

### 核心思路
题目要求每个节点作为电流起点时的期望路径和最大值。采用**换根DP**策略，通过两次DFS实现：

1. **预处理子树信息**（第一次DFS）：
   - `cnt[u]`：以u为根的子树中叶子数量
   - `g[u]`：子树路径和总和（乘叶子数避免精度误差）

2. **换根计算全局信息**（第二次DFS）：
   - `f[u]`：以u为根的整体期望（乘总叶子数）
   - 通过父节点信息推导子节点，公式分叶子/非叶子两种情况

### 关键难点与解决
1. **叶子节点动态变化**：
   - 当根切换时，原根可能变为叶子或非叶子，需要动态调整叶子计数
   - 通过`cnt[root] - lef[i]`实现动态分母计算

2. **状态转移方程推导**：
   - 非叶子节点转移公式：`f[v] = f[u] - cnt[v]*val[u] + (总叶子数 - cnt[v])*val[v]`
   - 叶子节点特殊处理：`f[v] = f[u] - val[u] + val[v]*(总叶子数-2)`

3. **精度优化**：
   - 所有计算使用整数避免浮点误差，最后统一除法

## 【题解评分（≥4星）】

1. **UltiMadow（5星）**
   - 清晰定义状态变量和转移方程
   - 完整处理叶子节点和非叶子节点的分类讨论
   - 代码结构简洁，注释明确

2. **pomelo_nene（4星）**
   - 补充链状特判逻辑，增强鲁棒性
   - 提供链状情况的数学推导公式
   - 代码包含实用调试信息

3. **BzhH（4星）**
   - 使用位运算优化叶子判断
   - 公式推导过程详细注释
   - 代码变量命名直观易懂

## 【最优思路提炼】

**换根DP核心步骤**：
1. 第一次DFS自底向上计算子树信息：
   ```python
   def dfs1(u, fa):
       for v in children[u]:
           if v != fa:
               dfs1(v, u)
               cnt[u] += cnt[v]
               g[u] += g[v]
       g[u] += val[u] * cnt[u]
       if not cnt[u]:  # 叶子节点
           cnt[u], g[u] = 1, val[u]
   ```

2. 第二次DFS自顶向下换根：
   ```python
   def dfs2(u, fa):
       for v in children[u]:
           if v != fa:
               if is_leaf(v):
                   f[v] = f[u] - val[u] + val[v]*(total_leaf-2)
               else:
                   f[v] = f[u] - cnt[v]*val[u] + val[v]*(total_leaf - cnt[v])
               dfs2(v, u)
   ```

**优化技巧**：
- 预处理总叶子数`total_leaf = cnt[root]`
- 最终期望计算时动态处理分母：`ans = max(f[i] / (total_leaf - is_leaf(i)))`

## 【相似题目推荐】

1. **P3047 [USACO12FEB]Nearby Cows G**  
   - 换根DP经典题，求每个点附近k层节点权值和

2. **P3478 [POI2008]STA-Station**  
   - 换根求最长路径端点，需要维护深度信息

3. **P2986 [USACO10MAR]Great Cow Gathering G**  
   - 带权换根DP，结合边权与子树规模计算

## 【可视化设计】

**动画方案**：
1. **树结构绘制**：
   - 使用Canvas绘制节点（圆形）和边（连线）
   - 初始根节点标记为红色，其他节点为蓝色

2. **第一次DFS过程**：
   - 自底向上遍历时，当前处理节点高亮为黄色
   - 实时显示`cnt`和`g`值在节点旁
   ```javascript
   // 伪代码示例
   function drawNode(u) {
       ctx.fillStyle = u == current ? '#FFD700' : '#1E90FF';
       drawCircle(u.x, u.y);
       drawText(`cnt=${u.cnt}`, u.x, u.y-15);
       drawText(`g=${u.g}`, u.x, u.y+15);
   }
   ```

3. **换根过程**：
   - 根节点切换时播放"click"音效
   - 展示公式推导过程（如f[v]计算）
   - 用箭头动画表示状态转移方向

4. **8位像素风格**：
   - 使用16色调色板（红、蓝、黄、绿）
   - 节点绘制为8x8像素块，边用1像素宽线段
   - 状态更新时像素块闪烁3帧

**交互功能**：
- 速度滑块控制动画速度（0.5x~3x）
- 空格键暂停/继续
- 右键单步执行换根过程

## 【核心代码实现】

以UltiMadow的代码为例，关键片段：
```cpp
void dp1(int u,int fa) { // 第一次DFS
    for(int v : Edge[u]) {
        if(v == fa) continue;
        dp1(v, u);
        cnt[u] += cnt[v];
        g[u] += g[v];
    }
    g[u] += val[u] * cnt[u];
    if(!cnt[u]) { // 叶子节点初始化
        cnt[u] = 1;
        g[u] = val[u];
    }
}

void dp2(int u,int fa) { // 第二次DFS
    for(int v : Edge[u]) {
        if(v == fa) continue;
        if(leaf[v]) 
            f[v] = f[u] - val[u] + val[v]*(total_leaf-2);
        else
            f[v] = f[u] - cnt[v]*val[u] + val[v]*(total_leaf - cnt[v]);
        dp2(v, u);
    }
}
```

完整代码见题解区UltiMadow提交。

---
处理用时：81.75秒