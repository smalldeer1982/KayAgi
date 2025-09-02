# 题目信息

# [传智杯 #4 决赛] [yLOI2021] 生活在树上（hard version）

## 题目背景

**本题是 P8200 的较难版本，两道题目的解法略有不同。本题和 P8200 在题意上的区别在于本题给定树上的点权，而不是边权。**

小智生活在「传智国」，这是一个有 $n$ 个城市的国家，各个城市由 $n-1$ 条道路相连。

每个城市都有一个财富指数 $w_i$ ，我们定义，小智从城市 $a$ 走到城市 $b$ 的代价是 $\mathrm{dis}_{a, b} = \bigoplus \limits_{u \in \mathrm{path}\left(a, b\right)} w_u$，其中 $\bigoplus$ 表示**按位异或**（如果你不知道什么是**按位异或**，请参见题目下方的提示/说明），$\mathrm{path}\left(a,b\right)$ 表示 $a$ 到 $b$ 的简单路径上的点集（包括 $a$ 和 $b$）。也即 $\mathrm{dis}_{a, b}$ 表示将 $a$ 与 $b$ 的简单路径上所有点写作 $u_1, u_2, u_3, \dots$ 后，求 $w_{u_1} \bigoplus w_{u_2}\bigoplus w_{u_3} \dots$ 的结果。

有一天，小智获得了去参加传智杯的机会，他在前往比赛地的路上想到了一个问题，但他好像不会做，于是他把这个题告诉了你。聪明的同学，你可以帮帮他吗？

## 题目描述

小智说：「由于我们的国家只有 $n$ 个城市和 $n-1$ 条道路，那么我们的国家就相当于是一棵树。我在想，在我们的国家中，是否存在城市满足『到城市 $a$ 的代价和到城市 $b$ 的代价的异或等于 $k$』。好难哦，我想不出来，你能帮帮我吗？」

也就是说，给定城市 $a, b$ 和整数 $k$，请你计算是否存在城市 $t$ 满足 $\mathrm{dis}_{t, a} \bigoplus \mathrm{dis}_{t, b} = k$。

## 说明/提示

### 相关概念解释
「树」：树是一个有 $n$ 个结点和 $n-1$ 条边的无向简单连通图。

「按位异或」：按位异或是一个二元运算，步骤是将两个数的二进制位按位比较，相同为 $0$，不同为 $1$ 。例如：$3 \bigoplus 5 = (011)_2 \bigoplus (101)_2 = (110)_2 = 6$。
### 样例 1 解释
下图为传智国的地图。

$\forall t \in \{1, 2, 3, 4, 5\}$，都不可能有 $\mathrm{dis} _{t,1} \bigoplus \mathrm{dis}_{t, 2} = 4$，$\mathrm{dis}_{t, 2} \bigoplus \mathrm{dis}_{t, 3} = 12$，于是输出 `No`；

而取 $t=4$，有 $\mathrm{dis}_{t, 2} \bigoplus \mathrm{dis}_{t, 3} = 10$，于是输出 `Yes`。

![](https://cdn.luogu.com.cn/upload/image_hosting/d3phj9di.png)
### 数据规模与约定
对于所有测试点，保证 $1 < n \leq 5 \times 10^5$，$1 \leq m \leq 5 \times 10^5$，$0 \leq w_i \leq 1\times 10^7$。

对于每次询问，保证 $1 \leq a,b \leq n$ 且 $a \neq b$，$0 \leq k \leq 1\times 10^7$。
### 提示
- 请注意常数因子对程序效率造成的影响。
- 对于两个 $x, y \leq 10^7$，$x \bigoplus y$ 可能大于 $10^7$，请特别注意这一点。

## 样例 #1

### 输入

```
5 3
2 6 8 1 5
1 2
1 3
2 4
2 5
1 2 4
2 3 12
2 3 10```

### 输出

```
nO
No
YeS```

## 样例 #2

### 输入

```
5 10
93 97 100 93 93
2 1
3 2
4 3
5 1
5 2 93
4 1 93
3 2 100
3 2 100
2 3 9999998
1 2 93
2 3 97
1 2 93
2 3 97
4 3 93```

### 输出

```
no
nO
yEs
yEs
No
yEs
yeS
YES
yES
yes```

# AI分析结果



## 唯一算法分类
树上差分 + 离线LCA

---

## 综合分析与结论

### 核心思路与算法流程
1. **问题转化**：  
   通过异或性质推导，发现所求等价于在a到b的路径上寻找点t，使得w_t = k ^ dis(a,b)。其中dis(a,b)是a到b路径的总异或值。
   
2. **路径分解**：  
   使用LCA将路径拆分为a到LCA和b到LCA两部分，通过树上差分将路径查询转化为四个端点的到根路径的叠加。

3. **离线处理**：  
   预处理所有查询，在DFS遍历时用全局桶记录当前路径的权值出现次数。通过两次DFS（求LCA+统计权值）完成高效离线查询。

### 可视化设计思路
1. **动画演示**：  
   - 用不同颜色标记当前DFS访问的节点  
   - 动态显示桶数组的计数变化（如红色表示当前权值的计数增加）  
   - 高亮LCA节点和查询路径的拆分过程  

2. **复古像素风格**：  
   - 用16色像素方块表示树节点，绿色方块表示当前访问节点  
   - 路径绘制使用黄色连线，LCA节点用闪烁特效  
   - 执行关键操作时播放8-bit音效（如节点访问时的"哔"声）

---

## 题解清单（≥4星）

### 一扶苏一（★★★★★）
- **亮点**：  
  ① 巧妙的离线差分思路，时间复杂度O(nα(n))  
  ② 利用Tarjan求LCA降低常数  
  ③ 全局桶配合DFS实现高效统计  

### Claysonleet（★★★★☆）
- **亮点**：  
  ① 清晰的思路转化表述  
  ② 完整代码实现差分思路  
  ③ 包含调试经验（处理特殊边界）  

### zzxLLL（★★★★）
- **亮点**：  
  ① 树剖+动态开点线段树的创新解法  
  ② 处理大值域时直接映射权值  
  ③ 代码结构清晰易扩展  

---

## 核心代码实现

### 一扶苏一题解关键片段
```cpp
void dfs2(const int u) {
  ++bk[a[u]]; // 进入节点时记录权值
  for (auto [i, w] : QQ[u]) { // 处理当前节点的所有查询
    ans[i] += w * bk[k[i]];
  }
  for (auto v : e[u]) if (v != fa[u]) {
    dfs2(v);
  }
  --bk[a[u]]; // 回溯时撤销记录
}
```

### 可视化关键逻辑（JavaScript伪代码）
```javascript
class TreeVisualizer {
  dfsStep(node) {
    this.highlightNode(node, COLOR_GREEN); 
    this.updateBucket(node.value, +1); 
    playSound('beep1');
    
    node.queries.forEach(q => {
      const cnt = this.bucket[q.targetValue];
      this.updateAnswer(q.id, cnt * q.coeff); 
    });
    
    node.children.forEach(child => {
      if(child != parent) this.dfsStep(child);
    });
    
    this.highlightNode(node, COLOR_DEFAULT);
    this.updateBucket(node.value, -1);
    playSound('beep2');
  }
}
```

---

## 相似题目推荐
1. **P2633 Count on a tree**  
   （树上路径第k小，主席树应用）
   
2. **P3304 [SDOI2013] 直径**  
   （树的性质与路径处理）

3. **P4556 雨天的尾巴**  
   （树上差分+权值统计）

---

## 个人心得摘录
> "比赛时大家好像都在树剖，没见到几个写差分的 —— 一扶苏一"  
> 调试时发现LCA处理错误导致差分项错误，添加fa[lca]的查询修正 —— Claysonleet  
> 首次尝试树剖套哈希表被卡常，改用离散化平衡树优化通过 —— zzxLLL  

---

## 复古游戏化设计
1. **视觉方案**：  
   - 树节点呈现为16x16像素方块，用色：  
     - 当前节点：荧光绿  
     - 已访问节点：深蓝  
     - LCA节点：闪烁红黄交替

2. **音效设计**：  
   - 节点进入：NES风格的短促"滴"声（Web Audio合成方波）  
   - 查询命中：经典马里奥金币音  
   - 回溯时：低沉鼓点

3. **自动演示模式**：  
   ```javascript
   class AutoPlayer {
     run() {
       this.steps = extractAlgorithmSteps();
       this.timer = setInterval(() => {
         if(this.steps.length > 0) {
           const step = this.steps.shift();
           this.viz.executeStep(step);
         } else {
           clearInterval(this.timer);
         }
       }, 1000); // 可调节速度
     }
   }
   ```

---
处理用时：66.32秒