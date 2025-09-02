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
树的直径

---

**题解思路与核心难点**  
题目要求判断新图（原树中距离≥k的点相连）是否为二分图。关键在于检测新图中是否存在奇环。通过分析得出，若存在点到树直径两端的距离均≥k，则三点构成奇环。核心步骤如下：

1. **求树的直径**：两次DFS/BFS确定直径端点。
2. **计算距离**：遍历所有点，计算到两个端点的距离。
3. **条件检查**：存在任意点满足两端距离≥k，则存在奇环。

**解决难点**：直接建新图不可行，需通过树的直径性质将问题转化为高效的条件判断。

---

**题解评分 (≥4星)**  
1. **一只书虫仔 (5星)**  
   - 思路清晰，直接利用直径性质，代码简洁高效。  
   - 附带数学证明，深入解释正确性。  
   - 代码可读性强，适合快速理解核心逻辑。

2. **青鸟_Blue_Bird (4星)**  
   - 详细梳理证明过程，结合示意图辅助理解。  
   - 代码注释详尽，变量命名规范，便于调试。  
   - 优化了官方题解的代码结构，更易维护。

3. **HPXXZYY (4星)**  
   - 明确算法步骤与复杂度分析，适合竞赛场景。  
   - 提供暴力到正解的过渡，帮助理解优化思路。  
   - 代码使用BFS求直径，避免递归栈溢出风险。

---

**最优思路提炼**  
关键技巧：**利用树的直径性质，将奇环检测转化为点到两端的距离检查**。  
1. 直径是最长路径，确保极端情况被覆盖。  
2. 若点u到直径端点A、B的距离均≥k，则u-A-B构成三元奇环。  
3. 无需显式建新图，O(n)时间复杂度解决。

---

**同类型题与算法套路**  
- **套路**：树的直径用于解决最长路径相关问题，结合二分图性质需寻找特定结构（如三元环）。  
- **相似题目**：  
  - [P5536 【XR-3】核心城市](https://www.luogu.com.cn/problem/P5536)（树的直径与中继点选择）  
  - [P4381 [IOI2008] Island](https://www.luogu.com.cn/problem/P4381)（基环树直径）  
  - [CF455C Civilization](https://www.luogu.com.cn/problem/CF455C)（直径合并与查询）

---

**代码实现片段**  
```cpp
// 求树的直径端点
int findFarthest(int start, vector<int>& dist) {
    fill(dist.begin(), dist.end(), -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    int farthest = start;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& e : adj[u]) {
            if (dist[e.to] == -1) {
                dist[e.to] = dist[u] + e.w;
                q.push(e.to);
                if (dist[e.to] > dist[farthest]) farthest = e.to;
            }
        }
    }
    return farthest;
}

// 主逻辑
bool hasOddCycle(int k) {
    vector<int> distA(n+1), distB(n+1);
    int A = findFarthest(1, distA);
    int B = findFarthest(A, distA);
    findFarthest(B, distB); // distB存储到B的距离

    for (int u = 1; u <= n; ++u) {
        if (distA[u] >= k && distB[u] >= k)
            return true; // 存在奇环
    }
    return false;
}
```

---

**可视化设计思路**  
1. **像素风格树结构**：用Canvas绘制树节点，绿色表示直径路径，红色标记候选点。  
2. **动态距离显示**：遍历时高亮当前节点，显示其到两端的距离数值。  
3. **奇环动画**：发现满足条件的点时，触发闪烁特效并播放“发现”音效，连线形成三角环。  
4. **自动演示模式**：按步长自动遍历节点，速度可调，支持暂停/继续。  
5. **音效设计**：  
   - 步进音效：8-bit短促“滴”声。  
   - 发现奇环：经典FC过关音效。  
   - 无解：低音“哔”声。  

---

**复古游戏化实现要点**  
```javascript
// 示例：Canvas绘制树与高亮节点
function drawTree() {
    ctx.fillStyle = "#2C3E50"; // 背景色
    ctx.fillRect(0, 0, width, height);
    nodes.forEach(node => {
        ctx.fillStyle = node.isDiameter ? "#27AE60" : "#E74C3C";
        ctx.beginPath();
        ctx.arc(node.x, node.y, 5, 0, Math.PI * 2);
        ctx.fill();
        if (node.highlight) {
            ctx.strokeStyle = "#F1C40F";
            ctx.stroke();
        }
    });
}
// 触发音效
function playSound(effect) {
    const sfx = {
        found: new Audio('data:audio/wav;base64,UklGRl9...'), // 简短Base64编码音效
        step: new Audio('...')
    };
    sfx[effect].play();
}
```

---

**个人心得摘录**  
- **青鸟_Blue_Bird**：强调手动画图验证数学归纳步骤，避免纯理论推导的抽象性。  
- **HPXXZYY**：通过反例说明不能仅检查直径上的点，需全局遍历。  
- **调试经验**：初始未清空距离数组导致WA，提醒多组数据务必重置变量。  

---

**相似题目推荐**  
1. [P1099 树网的核](https://www.luogu.com.cn/problem/P1099)  
2. [P2491 [SDOI2011]消防](https://www.luogu.com.cn/problem/P2491)  
3. [P3629 [APIO2010]巡逻](https://www.luogu.com.cn/problem/P3629)

---
处理用时：90.64秒