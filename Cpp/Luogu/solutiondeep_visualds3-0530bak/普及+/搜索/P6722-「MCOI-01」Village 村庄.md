# 题目信息

# 「MCOI-01」Village 村庄

## 题目背景

今天，珂爱善良的0x3喵酱骑着一匹小马来到了一个村庄。

“诶，这个村庄的布局 ……”   
“好像之前我玩 Ciste 的地方啊 qwq”

0x3喵酱有一个地图，地图有着这个村庄的信息。

然后0x3喵酱要通过这张地图来判断 Ciste 有解无解啦 ~

注：Ciste 是《请问您今天要来点兔子吗》中的一种藏宝图游戏

## 题目描述

村庄被简化为一个 $n$ 个节点（编号为 $1$ 到 $n$）和 $n-1$ 条边构成的无向连通图。

0x3喵酱认为这个无向图里的信息跟满足以下条件的新图有关：

- 新图的点集与原图相同
- 在新图中 $u,v$ 之间有无向边 是 在原图中 $dis(u,v) \ge k$ 的**充分必要条件** （$k$ 为给定常量，$dis(u,v)$ 表示编号为 $u$ 的点到编号为 $v$ 的点最短路的长度）

0x3喵酱还认为这个"新图"如果为二分图，则 Ciste "有解"，如果"新图"不是二分图这个 Ciste "无解"。（如果您不知道二分图请翻到提示）

那么0x3喵酱想请您判断一下这个 Ciste 是否"有解"。

## 说明/提示

#### 样例解析

对于样例中的 **第一组** 数据：

原图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9f9zh4b2.png)
新图：

![](https://cdn.luogu.com.cn/upload/image_hosting/dg4es91e.png)

新图不为二分图，故输出 `Baka Chino`。

对于 **第三组** 数据：

原图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mku4v6uo.png)

新图：

![](https://cdn.luogu.com.cn/upload/image_hosting/15o3x3zz.png)

新图为二分图，故输出 `Yes`。

#### 数据规模与约定

**本题采用捆绑测试**。

- Subtask 1（16 pts）$\ $ ：$n \le 10$。
- Subtask 2（24 pts）$\ $ ：$n \le 100$。
- Subtask 3（8 pts）$\ $ ：$n \le 1000$。
- Subtask 4（28 pts）：图退化成一条链。
- Subtask 5（24 pts）：无特殊限制。

对于 $100\%$ 的数据，$n \le 10^5$，$T \le 10$，$v \le 1000$，$k \le 1000000$。

本题数据使用 [CYaRon](https://www.luogu.org/discuss/show?postid=11410) 生成。

#### 提示


**二分图** 又称作二部图，是图论中的一种特殊模型。设 $G=(V,E)$ 是一个无向图，如果顶点 $V$ 可分割为两个互不相交的子集 $(A,B)$，并且图中的每条边 $(i,j)$ 所关联的两个顶点 $i$ 和 $j$ 分别属于这两个不同的顶点集 $(i \in A,j \in B)$，则称图 $G$ 为一个二分图。（摘自[百度百科](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E5%9B%BE/9089095?fr=aladdin)）

#### 说明

Minecraft OI Round 1 A

- Idea：0x3喵酱
- Solution/Std：0x3喵酱
- Data：0x3喵酱
- Tester：tarjin

## 样例 #1

### 输入

```
5
5 2
1 2 1
2 3 1
3 4 1
4 5 1
5 3
1 2 1
2 3 1
3 4 1
4 5 1
5 8
1 3 3
1 2 1
2 4 6
2 5 2
5 2
1 3 3
1 2 1
2 4 6
2 5 2
7 4
1 2 3
1 3 3
2 5 3
2 6 3
3 7 3
2 4 2```

### 输出

```
Baka Chino
Yes
Yes
Baka Chino
Baka Chino```

# AI分析结果



**唯一算法分类**  
DFS

---

**综合分析与结论**  
**核心思路**：  
通过两次 DFS 确定树的直径端点，再检查所有节点到这两个端点的距离是否同时 ≥ k。若存在这样的节点，说明新图存在奇环，否则是二分图。

**难点与解决**：  
1. **显式构建新图不可行**：直接计算所有节点对距离的复杂度为 O(n²)，无法处理 n=1e5 的规模。  
2. **奇环存在性等价转换**：利用树的直径性质，将奇环存在性问题转换为「存在点到两端距离均 ≥k」的判定。  
3. **高效验证条件**：两次 DFS 找直径的时间复杂度为 O(n)，后续遍历验证条件仅需 O(n)。

**搜索过程可视化设计**：  
1. **直径查找阶段**：用不同颜色高亮当前遍历路径，动态显示端点的变化。  
2. **距离验证阶段**：为每个节点标记到两端的距离值，若同时 ≥k 则标红闪烁。  
3. **像素动画**：用 8 位风格绘制树形结构，访问节点时播放电子音效，找到直径端点时触发欢呼音效。

---

**题解清单 (≥4星)**  
1. **作者：一只书虫仔 (5星)**  
   - 关键亮点：数学归纳法严谨证明奇环等价条件，给出完整理论推导  
   - 代码亮点：标准直径求法，代码简洁易维护  

2. **作者：HPXXZYY (5星)**  
   - 关键亮点：通过子树性质推导结论，提供反例验证算法正确性  
   - 代码亮点：BFS 实现直径查找，内存管理清晰  

3. **作者：Zenith_Yeh (4星)**  
   - 关键亮点：换根 DP 记录多维度距离，适用于更复杂场景  
   - 代码亮点：动态维护最远三个子树距离，处理边界条件精细  

---

**最优思路代码片段**  
```cpp
// 求树的直径核心代码
void dfs(int u, int fa, int* dis) {
    for (auto& e : G[u]) {
        int v = e.to, w = e.w;
        if (v == fa) continue;
        dis[v] = dis[u] + w;
        dfs(v, u, dis);
    }
}

// 主逻辑
int main() {
    dfs(1, 0, dis1); // 第一次DFS找端点s1
    s2 = max_element(dis1+1, dis1+n+1) - dis1;
    dfs(s2, 0, dis2); // 第二次DFS计算到s2的距离
    bool flag = false;
    for (int i=1; i<=n; i++) 
        if (dis1[i]>=k && dis2[i]>=k) flag = true;
    puts(flag ? "Baka Chino" : "Yes");
}
```

---

**同类型题推荐**  
1. P1099 [树网的核]（树的直径性质）  
2. P5536 [核心城市]（树的最远距离计算）  
3. P4381 [Island]（基环树与直径结合）

---

**可视化与复古动画实现**  
```html
<canvas id="treeCanvas"></canvas>
<script>
// 树结构数据与像素绘制
const tree = {nodes: [[100,50], [200,150], ...], edges: [...]};
const colors = ['#FF6B6B', '#4ECDC4', '#45B7D1']; // 复古配色

function drawPixelNode(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x-4, y-4, 8, 8); // 8x8 像素方块
}

// DFS 动画演示
let visited = new Set();
function animateDFS(u) {
    drawPixelNode(...tree.nodes[u], '#FF6B6B');
    playSound('bleep'); // 触发音效
    for (let v of tree.edges[u]) {
        if (!visited.has(v)) {
            visited.add(v);
            setTimeout(() => animateDFS(v), 500);
        }
    }
}
</script>
```

**复古效果说明**：  
- **音效**：节点访问时播放 8-bit 短音，找到直径端点时播放胜利音效  
- **动画**：节点扩展时产生像素粒子特效，直径路径高亮为金色  
- **自动演示**：按空格键启动/暂停，方向键调节动画速度  

---

**总结**  
本题通过树的直径性质将问题转化为线性验证，避免显式处理 O(n²) 边数。DFS 的高效应用与数学等价转换是解题关键，适合作为树形结构性质分析的经典案例。

---
处理用时：58.04秒