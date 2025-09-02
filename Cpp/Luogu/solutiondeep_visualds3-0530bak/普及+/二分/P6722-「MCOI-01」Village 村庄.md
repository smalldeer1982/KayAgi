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



### **唯一算法分类**  
无算法分类  

---

### **题解思路与核心难点**  
**核心思路**：新图存在奇环的充要条件是存在一个点，其到树直径两端的距离均≥k。  
**算法流程**：  
1. 通过两次DFS找到树的直径端点  
2. 计算所有节点到两端点的距离  
3. 检查是否存在节点满足双端距离≥k  

**解决难点**：  
1. **数学归纳法证明奇环必然存在三元环**  
   - 若存在奇环，则环中最远两点u、v必存在中间点w，使得dis(u,w)≥k且dis(w,v)≥k  
   - 由此推导只需检查三元环存在性  
2. **树的直径性质**  
   - 任何点到直径端点的距离是该点在树中的最长路径  
   - 若某点双端距离≥k，则必与两端构成三元环  

---

### **题解评分（≥4星）**  
1. **一只书虫仔（5星）**  
   - 思路清晰，完整证明三元环存在性  
   - 代码简洁（两遍DFS求直径+距离计算）  
   - 关键代码片段注释明确  

2. **青鸟_Blue_Bird（5星）**  
   - 详细修复官方题解的LATEX排版问题  
   - 提供完整数学推导流程图  
   - 代码含指针传参优化空间  

3. **Zenith_Yeh（4星）**  
   - 换根DP记录子树最远距离  
   - 判断条件 `len+dp[now][2]>=k` 较为巧妙  
   - 代码稍复杂，但注释清晰  

---

### **最优思路与技巧**  
**关键优化点**：  
1. **两次DFS求直径**  
   - 第一次DFS从任意点出发找到最远点u  
   - 第二次DFS从u出发找到最远点v，u-v即为直径  
2. **距离预计算**  
   - 从u出发计算所有点到u的距离（dis1数组）  
   - 从v出发计算所有点到v的距离（dis2数组）  
3. **O(n)遍历判断**  
   ```cpp
   for(int i=1; i<=n; i++) 
       if(dis1[i]>=k && dis2[i]>=k) return 无解;
   ```

**避免的陷阱**：  
- 树的边权需累加（非固定1），DFS时用 `dis[v] = dis[u] + edge_w`  
- 直径端点必须通过两次动态DFS确定，不能假设固定为1号点  

---

### **同类型题目推荐**  
1. [P5536【XR-3】核心城市](https://www.luogu.com.cn/problem/P5536)（树的直径性质）  
2. [P3385【模板】负环](https://www.luogu.com.cn/problem/P3385)（环存在性判断）  
3. [P2862 [USACO06JAN]Corral the Cows](https://www.luogu.com.cn/problem/P2862)（距离约束下的二分答案）  

---

### **可视化设计**  
**动画演示方案**：  
1. **像素风格直径查找**  
   - 用16色像素块表示树节点，绿色块表示当前DFS访问点  
   - 直径端点标记为红色，路径用黄色高亮  
2. **距离计算动效**  
   - 从直径端点u扩散蓝色波纹表示dis1计算  
   - 从端点v扩散红色波纹表示dis2计算  
   - 满足 `dis1[i]+dis2[i]≥2k` 的节点闪烁警告  
3. **音效交互**  
   - DFS移动时播放8-bit脚步声  
   - 发现非法节点时播放《Minecraft》熔岩音效  

**Canvas实现核心逻辑**：  
```javascript
// 伪代码：绘制节点距离
function drawNode(node, dis1, dis2) {
  if (dis1 >= k && dis2 >= k) {
    ctx.fillStyle = '#FF0000'; // 红色表示非法
    playSound('error.wav');
  } else {
    ctx.fillStyle = '#00FF00'; // 绿色表示合法
  }
  ctx.fillRect(node.x, node.y, 10, 10);
}
```

---

### **代码实现（标准解法）**  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct Edge { int to, w; };
vector<Edge> G[N];
int dis_u[N], dis_v[N], n, k;

void dfs(int u, int fa, int* dis) {
    for (auto e : G[u]) {
        if (e.to != fa) {
            dis[e.to] = dis[u] + e.w;
            dfs(e.to, u, dis);
        }
    }
}

int findFarthest(int start, int* dis) {
    memset(dis, 0, sizeof(dis));
    dfs(start, -1, dis);
    return max_element(dis+1, dis+n+1) - dis;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> k;
        for (int i=1; i<=n; i++) G[i].clear();
        for (int i=1; i<n; i++) {
            int u, v, w; cin >> u >> v >> w;
            G[u].push_back({v, w});
            G[v].push_back({u, w});
        }
        
        int u = findFarthest(1, dis_u);
        int v = findFarthest(u, dis_u);
        findFarthest(v, dis_v);
        
        bool ok = true;
        for (int i=1; i<=n; i++) {
            if (dis_u[i] >= k && dis_v[i] >= k) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "Yes" : "Baka Chino") << endl;
    }
    return 0;
}
```

---
处理用时：74.38秒