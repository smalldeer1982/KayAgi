# 题目信息

# Almost Acyclic Graph

## 题目描述

You are given a [directed graph](https://en.wikipedia.org/wiki/Directed_graph) consisting of $ n $ vertices and $ m $ edges (each edge is directed, so it can be traversed in only one direction). You are allowed to remove at most one edge from it.

Can you make this graph [acyclic](https://en.wikipedia.org/wiki/Directed_acyclic_graph) by removing at most one edge from it? A directed graph is called acyclic iff it doesn't contain any cycle (a non-empty path that starts and ends in the same vertex).

## 说明/提示

In the first example you can remove edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png), and the graph becomes acyclic.

In the second example you have to remove at least two edges (for example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/7480c546ca7ee72615c3ded7d769355b1c864f93.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF915D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png)) in order to make the graph acyclic.

## 样例 #1

### 输入

```
3 4
1 2
2 3
3 2
3 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 6
1 2
2 3
3 2
3 1
2 1
4 5
```

### 输出

```
NO
```

# AI分析结果



---

## **算法分类**
拓扑排序

---

## **题解思路与核心难点**

### **核心思路**
删除一条边的实质是令目标顶点的入度减1。通过枚举每个顶点，将其入度临时减1后执行拓扑排序，若结果无环则可行。将时间复杂度从$O(m^2)$优化至$O(n(n+m))$。

### **解决难点**
1. **入度副本管理**：每次尝试需备份原始入度数组，确保后续操作不受前次影响。
2. **拓扑判环机制**：通过统计拓扑序列长度是否等于顶点数判断环的存在。
3. **剪枝优化**：仅对入度≥1的顶点进行尝试，避免无效操作。

---

## **题解评分 (≥4星)**

1. **青烟绕指柔 (⭐⭐⭐⭐⭐)**  
   - **亮点**：代码极简，备份入度数组逻辑清晰，队列实现高效。
   - **优化**：使用`vector`邻接表存储图，`queue`实现拓扑排序。
2. **CharlesZiy (⭐⭐⭐⭐)**  
   - **亮点**：详细注释与变量命名规范，双重备份入度数组避免污染。
   - **心得**：强调拓扑排序中入度副本的重要性。
3. **Nukumizu_Kaju (⭐⭐⭐⭐)**  
   - **亮点**：独立封装拓扑函数，逻辑模块化，可读性强。

---

## **最优思路提炼**
1. **关键变量**：`in[]`保存原始入度，`cop[]`为每次尝试的临时副本。
2. **核心步骤**：
   - 遍历顶点，若`in[i] > 0`则减1。
   - 执行拓扑排序，若成功则立即返回。
   - 恢复入度数组继续下一轮。
3. **拓扑判环**：队列处理顶点并统计访问数，最终判断是否等于n。

---

## **类似题目推荐**
1. **课程表 II（LeetCode 210）**  
   - 求拓扑序列，需处理环的存在。
2. **确定比赛名次（HDU 1285）**  
   - 基本拓扑排序应用，要求最小字典序输出。
3. **洛谷 P1113 杂务**  
   - 结合拓扑排序与动态规划的最长路径问题。

---

## **代码实现片段**
```cpp
bool topo(int n, vector<int> g[], int in_backup[], int test_node) {
    int cop[n+1];
    memcpy(cop, in_backup, sizeof(cop)); // 拷贝原始入度
    if (cop[test_node] > 0) cop[test_node]--; // 模拟删除边
    
    queue<int> q;
    int cnt = 0;
    for (int i=1; i<=n; i++)
        if (cop[i] == 0) q.push(i);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cnt++;
        for (int v : g[u]) {
            if (--cop[v] == 0) 
                q.push(v);
        }
    }
    return cnt == n; // 无环当且仅当访问所有节点
}
```

---

## **可视化设计**
### **动画方案**
- **数据结构**：顶点用像素方块表示，边用箭头连接。
- **关键帧**：
  1. **顶点高亮**：当前尝试入度减1的顶点闪烁黄色。
  2. **队列操作**：队列内顶点显示为绿色，出队后变灰。
  3. **入度更新**：邻接顶点的入度数值动态减少，颜色渐变。
- **交互功能**：
  - **步进控制**：空格键单步执行，右键调整速度。
  - **自动模式**：AI自动遍历顶点，成功时播放胜利音效。

### **复古风格**
- **调色板**：16色FC风格，背景深蓝，顶点红/绿/黄。
- **音效**：
  - **入队**：8-bit "beep" 短音。
  - **成功**：经典《超级玛丽》过关旋律片段。
  - **失败**：低音爆破声效。

---

## **总结**
通过拓扑排序的入度优化策略，将问题转化为顶点枚举，大幅降低时间复杂度。可视化设计结合复古元素与关键步骤高亮，直观展示算法核心流程。

---
处理用时：94.21秒