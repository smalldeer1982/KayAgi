# 题目信息

# Zrz_orz Loves Secondary Element

## 题目背景

zrz_orz赘喜欢二次元辣！！

## 题目描述

众所周知的是，zrz_orz是全机房最强的死宅。~~他甚至使用嘴遁使得Samcompu不得不在自己的网站上挂上时崎狂三~~。(话说Samcompu好像醒悟了又把狂三给去掉了。)作为新一代死宅的一员，从电脑壁纸到输入法皮肤，到处都是二次元的痕迹。所以，他经常在梦里梦见一些二次元的角色。

zrz_orz的梦，是由$n$个点和$n-1$条边构成的连通图。其中有$m$个节点上有一个二次元的角色。对于zrz_orz来说，每一个二次元的角色都有一个对应的$pos_i$和$val_i$表示这个角色在图上的哪一个节点以及与之聊天对zrz_orz来说会增加多少愉悦值。(由于某种原因，聊天的过程可以不用计入时间。)可惜的是，zrz_orz每一次做梦都只会做$tim_i$个单位时间。现在请你告诉他，他每一次做梦最多能获得多少愉悦值。

注：

1.zrz_orz每一次做梦都只会从1号节点开始走！

2.每一次做梦后zrz_orz梦境中的图都不会改变！

**3.每一次做完梦之后zrz_orz就必须要回到1号节点，否则他就会迷失在梦境里！**

## 说明/提示

![](https://cdn.luogu.com.cn/upload/pic/25600.png)

第一天哪里都去不了。

第二天1->3->6->7->6->3->1获得最大愉悦值为7。

第三天所有的地方都可以走一遍。

Subtask 1(20 pts): 

$ 1 \leqslant T \leqslant 10 \qquad 1 \leqslant N \leqslant 1000 \qquad 1 \leqslant M \leqslant 20 \qquad 1 \leqslant  tim_k \leqslant 1000$

Subtask 2(40 pts):

$ 1 \leqslant T \leqslant 10^5 \qquad 1 \leqslant N \leqslant 10^5 \qquad 1 \leqslant M \leqslant 20 \qquad 1 \leqslant  tim_k \leqslant 10^5$

Subtask 3(40 pts):

$ 1 \leqslant T \leqslant 5*10^4 \qquad 1 \leqslant N \leqslant 5000 \qquad 1 \leqslant M \leqslant 100 \qquad 1 \leqslant  tim_k \leqslant 100 \qquad 1 \leqslant w_i \leqslant 5$

For all test points:

$ 1 \leqslant pos_j,u_i,v_i \leqslant N \qquad 1 \leqslant \sum val_j \leqslant 2e9 \qquad 1 \leqslant w_i \leqslant 20 \qquad 1 \leqslant tim_k \leqslant 10^5 $

注意: 标记的分数就是这个Subtask的分数，每一个Subtask必须全对才能得分。Subtask 2的时限为1.5s。

$$ \color{white} \text{NOIP 2合1} $$

## 样例 #1

### 输入

```
7 3 3
1 2 2
1 3 1
2 4 1
2 5 10
3 6 1
6 7 2
4 5
5 50
7 7
1
10
100
```

### 输出

```
0
7
62```

# AI分析结果



# 算法分类  
树形动态规划、虚树、状压枚举

---

## 题解思路与难点对比

### 核心算法流程
1. **边权处理**：所有边权乘以2（往返路径），转化为无需返回的路径问题  
2. **分层处理**：  
   - **小m场景(m≤20)**：构建虚树或枚举所有角色组合（状压），预处理所有可能路径的时间与价值  
   - **大m场景**：树形DP维护子树的最优价值，时间限制较小（≤100）时采用分组背包合并子树  

### 关键实现步骤
- **虚树构建**：通过LCA合并关键节点，保留对价值计算有影响的节点，边权为原树中的距离  
- **树上背包DP**：  
  ```python
  for u的每个子节点v:
      for 时间j从大到小:
          for 分配给v的时间k:
              dp[u][j] = max(dp[u][j], dp[u][j-k-w] + dp[v][k])
  ```
- **状压预处理**：枚举所有角色组合，计算路径总时间（需处理LCA与重复路径）  

### 解决难点
1. **路径时间计算**：通过虚树/状压预处理LCA，避免重复计算公共路径  
2. **时间复杂度控制**：  
   - 虚树将规模压缩至O(m)，树上背包复杂度降为O(mV)  
   - 状压通过二进制枚举，复杂度O(2^m)但m≤20时可行  

---

## 题解评分（≥4星）

### CQ_Bob（★★★★☆）
- **亮点**：虚树优化+树上背包DP，处理Subtask2的高效实现  
- **优化点**：预处理前缀最大值实现O(1)查询  
- **代码片段**：  
  ```cpp
  // 虚树上背包合并
  for(re int w=min(M,siz[u]+v.y+siz[v.x]);w>=0;--w)
    for(re int x=0;x<=min(w-v.y,siz[u]);++x)
      dp1[u][w]=max(dp1[u][w], dp1[u][x]+dp1[v.x][w-v.y-x]);
  ```

### mrsrz（★★★★☆）
- **亮点**：分情况处理+新树重构，统一处理不同规模数据  
- **特殊技巧**：按dfn序排序后合并子节点，保证LCA计算的正确性  

### ztlh（★★★★☆）
- **亮点**：状压预处理+二分查找优化查询，代码结构清晰  
- **关键代码**：  
  ```cpp
  // 枚举子集并计算时间
  for(int s=1;s<(1<<m);s++){
    int new_node = lb(s);
    int lca = GetLCA(new_node, existing_nodes);
    total_time += 2 * GetDis(new_node, lca);
  }
  ```

---

## 最优思路提炼
1. **虚树压缩**：仅保留关键节点与LCA，极大降低计算规模  
2. **时间-价值分离**：预处理所有可能路径的时间与价值，通过排序实现O(1)查询  
3. **分组背包合并**：树形DP中按子树分配时间，保证连通性约束  

---

## 同类题型推荐
1. **P2014 [CTSC1997]选课**（树形背包）  
2. **P3177 [HAOI2015]树上染色**（边权贡献计算）  
3. **P3313 [SDOI2014]旅行**（虚树+树链剖分）  

---

## 可视化设计
### 复古像素动画方案
1. **树结构绘制**：  
   - 8位风格节点（绿色：已访问，红色：未访问）  
   - 边权以像素数字显示（如"▲5"表示边权5）  
2. **背包更新动画**：  
   - 当前处理的子树节点闪烁黄色  
   - 时间槽（横向格子）从左到右填充，颜色深浅表示价值高低  
3. **音效设计**：  
   - 选中角色时播放"叮"声，路径更新时播放"咔"声  
   - 最优解更新时触发8-bit胜利旋律  

### 关键代码（Canvas绘制）
```javascript
function drawTree(node, x, y) {
  ctx.fillStyle = node.visited ? '#00FF00' : '#FF0000';
  ctx.fillRect(x, y, 20, 20); // 绘制节点方块
  node.children.forEach((child, i) => {
    let childX = x + (i - 0.5) * 50;
    drawEdge(x+10, y+20, childX, child.y); // 绘制边
    drawTree(child, childX, child.y);
  });
}
```

---

## 个人心得摘录
> "虚树的构建需要特别注意LCA的重复计算，按dfn序排序后合并可避免错误" —— CQ_Bob  
> "枚举子集时利用lowbit快速定位新增节点，极大优化了LCA计算" —— ztlh  

---

## 核心算法代码（树形DP）
```cpp
void dfs(int u, int fa) {
  for (auto& e : edges[u]) {
    int v = e.to, w = e.w * 2; // 往返边权乘2
    if (v == fa) continue;
    dfs(v, u);
    for (int j = max_time; j >= 0; j--) {
      for (int k = 0; k <= j - w; k++) {
        dp[u][j] = max(dp[u][j], dp[u][j - w - k] + dp[v][k]);
      }
    }
  }
  dp[u][0] += val[u]; // 当前节点价值
}
```

---
处理用时：71.70秒