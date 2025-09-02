# 题目信息

# Toss a Coin to Your Graph...

## 题目描述

One day Masha was walking in the park and found a graph under a tree... Surprised? Did you think that this problem would have some logical and reasoned story? No way! So, the problem...

Masha has an oriented graph which $ i $ -th vertex contains some positive integer $ a_i $ . Initially Masha can put a coin at some vertex. In one operation she can move a coin placed in some vertex $ u $ to any other vertex $ v $ such that there is an oriented edge $ u \to v $ in the graph. Each time when the coin is placed in some vertex $ i $ , Masha write down an integer $ a_i $ in her notebook (in particular, when Masha initially puts a coin at some vertex, she writes an integer written at this vertex in her notebook). Masha wants to make exactly $ k - 1 $ operations in such way that the maximum number written in her notebook is as small as possible.

## 说明/提示

Graph described in the first and the second examples is illustrated below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679D/f21a10b2a32ca5315b6d3233f4e3f1d967d3f865.png)In the first example Masha can initially put a coin at vertex $ 1 $ . After that she can perform three operations: $ 1 \to 3 $ , $ 3 \to 4 $ and $ 4 \to 5 $ . Integers $ 1, 2, 3 $ and $ 4 $ will be written in the notepad.

In the second example Masha can initially put a coin at vertex $ 2 $ . After that she can perform $ 99 $ operations: $ 2 \to 5 $ , $ 5 \to 6 $ , $ 6 \to 2 $ , $ 2 \to 5 $ , and so on. Integers $ 10, 4, 5, 10, 4, 5, \ldots, 10, 4, 5, 10 $ will be written in the notepad.

In the third example Masha won't be able to perform $ 4 $ operations.

## 样例 #1

### 输入

```
6 7 4
1 10 2 3 4 5
1 2
1 3
3 4
4 5
5 6
6 2
2 5```

### 输出

```
4```

## 样例 #2

### 输入

```
6 7 100
1 10 2 3 4 5
1 2
1 3
3 4
4 5
5 6
6 2
2 5```

### 输出

```
10```

## 样例 #3

### 输入

```
2 1 5
1 1
1 2```

### 输出

```
-1```

## 样例 #4

### 输入

```
1 0 1
1000000000```

### 输出

```
1000000000```

# AI分析结果



# 算法分类  
**二分**

---

# 综合分析与结论  

## 核心思路与算法要点  
题目要求找到路径最大点权的最小可能值，采用**二分答案**策略。关键点如下：  
1. **二分区间**：左边界取最小点权，右边界取最大点权或更大值（如1e9+10）。  
2. **条件判断**：对于当前二分值 `mid`，构建仅包含点权≤`mid`的点和边的子图。  
   - **环检测**：若子图存在环，则合法（可无限绕环满足任意k）。  
   - **最长路计算**：若无环且为DAG，计算最长路径长度是否≥k。  
3. **拓扑排序**：同时处理环检测与最长路动态规划，时间复杂度 O(n+m)。  

## 解决难点  
1. **高效判断条件**：拓扑排序既能检测环，又能通过动态规划计算最长路径，避免多次遍历图。  
2. **大规模数据处理**：每次二分后的子图处理需线性时间复杂度，适应n,m≤2e5的约束。  

## 可视化设计思路  
- **区间变化动画**：用滑动条展示 `left`、`right`、`mid` 的收缩过程，高亮当前判断的 `mid`。  
- **子图状态**：用颜色区分环存在（绿色）或最长路达标（蓝色），失败则标红。  
- **复古像素风格**：  
  - 用8-bit网格显示二分区间，`mid` 位置用闪烁方块突出。  
  - 音效：成功时播放8-bit音阶上升音效，失败时播放低沉音效。  
- **AI自动演示**：模拟二分过程，单步展示区间收缩逻辑，按空格键暂停/继续。  

---

# 题解清单（≥4星）  

1. **Hovery（5星）**  
   - **亮点**：代码结构清晰，变量命名规范，逻辑紧凑。通过拓扑排序同时处理环检测和最长路计算，注释明确。  
   - **关键代码**：  
     ```cpp  
     bool check(int need) {  
         // 建图与拓扑排序逻辑  
         if (cnt != sum) return 1; // 存在环  
         return max(dis[...]) >= k;  
     }  
     ```  

2. **Komorebi_03（4星）**  
   - **亮点**：代码简洁，处理入度与最长路的逻辑与Hovery相似，可读性较好。  
   - **优化**：采用更紧凑的输入输出函数，适应大规模数据。  

3. **sgl654321（4星）**  
   - **亮点**：使用记忆化搜索处理最长路，代码风格独特。适合理解DFS思路。  
   - **核心代码**：  
     ```cpp  
     bool dfs(int u, int p) {  
         if (p == k) return true;  
         // 递归搜索与环检测  
     }  
     ```  

---

# 最优思路提炼  

1. **二分条件设计**  
   - 确定 `mid` 后，仅保留点权≤`mid`的点和边，将问题转化为子图可达性判断。  

2. **拓扑排序双用途**  
   - **环检测**：若拓扑排序后仍有未访问节点，说明存在环。  
   - **最长路计算**：动态规划更新每个节点的最长路径长度。  

3. **边界处理技巧**  
   - 初始右边界设为1e9+10以覆盖极端情况，最终检查是否未修改初始右边界（输出-1）。  

---

# 同类型题与算法套路  

- **通用二分答案套路**：  
  1. 确定答案的单调性（如本题最大值随允许值增大而可行）。  
  2. 设计高效的条件判断函数（如本题的拓扑排序）。  

- **类似题目**：  
  1. **洛谷P1462**：二分+最短路，判断路径费用是否可行。  
  2. **洛谷P3199**：二分答案+SPFA判负环。  
  3. **LeetCode 778**：二分答案+BFS/DFS，判断能否到达终点。  

---

# 推荐题目  

1. **P1462 通往奥格瑞玛的道路**  
   - 二分城市费用最大值，结合最短路径计算。  

2. **P3199 [HNOI2009]最小圈**  
   - 二分答案找平均权值最小的环，SPFA检测负环。  

3. **CF1354F Summon the Curse**  
   - 二分答案结合贪心策略，判断特定条件下的最大得分。  

---

# 个人心得摘录  

- **调试教训**：需注意k=1时无需移动，直接判断点权是否合法。  
- **思维顿悟**：若子图存在环，无论k多大都合法，极大简化条件判断。  
- **代码优化**：避免每次check时全量清空数组，改用局部变量或动态内存。  

---

# 核心代码片段（Hovery题解）  

```cpp  
bool check(int need) {
    for (int i = 1; i <= n; i++) G[i].clear(), du[i] = dis[i] = vis[i] = 0;
    for (int i = 1; i <= m; i++) {
        if (a[x[i]] <= need && a[y[i]] <= need) {
            G[x[i]].push_back(y[i]);
            du[y[i]]++;
            vis[x[i]] = vis[y[i]] = 1;
        }
    }
    queue<int> q;
    int cnt = 0, sum = 0;
    for (int i = 1; i <= n; i++) {
        if (!du[i] && vis[i]) q.push(i), sum++;
        else sum += vis[i];
    }
    while (!q.empty()) {
        int x = q.front(); q.pop(); cnt++;
        for (auto i : G[x]) {
            du[i]--;
            dis[i] = max(dis[i], dis[x] + 1);
            if (!du[i]) q.push(i);
        }
    }
    if (cnt != sum) return 1; // 存在环
    return *max_element(dis + 1, dis + n + 1) >= k;
}
```

---

# 可视化代码（伪代码）  

```javascript  
// 8-bit风格二分动画核心逻辑  
function binarySearchAnimation() {
    let left = 1, right = 1e9, mid;
    while (left <= right) {
        mid = Math.floor((left + right) / 2);
        drawGrid(left, mid, right); // Canvas绘制区间
        playSound('mid_beep'); // 播放mid更新音效
        const isValid = check(mid); // 检查子图状态
        if (isValid) {
            right = mid - 1;
            highlight(mid, 'green'); // 合法区间高亮
        } else {
            left = mid + 1;
            highlight(mid, 'red'); // 非法区间标红
        }
    }
    playSound(isValid ? 'success' : 'fail'); // 最终结果音效
}
```

---
处理用时：108.23秒