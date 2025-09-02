# 题目信息

# Yasya and the Mysterious Tree

## 题目描述

Yasya was walking in the forest and accidentally found a tree with $ n $ vertices. A tree is a connected undirected graph with no cycles.

Next to the tree, the girl found an ancient manuscript with $ m $ queries written on it. The queries can be of two types.

The first type of query is described by the integer $ y $ . The weight of each edge in the tree is replaced by the [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng) of the weight of that edge and the integer $ y $ .

The second type is described by the vertex $ v $ and the integer $ x $ . Yasya chooses a vertex $ u $ ( $ 1 \le u \le n $ , $ u \neq v $ ) and mentally draws a bidirectional edge of weight $ x $ from $ v $ to $ u $ in the tree.

Then Yasya finds a simple cycle in the resulting graph and calculates the [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng) of all the edges in it. She wants to choose a vertex $ u $ such that the calculated value is maximum. This calculated value will be the answer to the query. It can be shown that such a cycle exists and is unique under the given constraints (independent of the choice of $ u $ ). If an edge between $ v $ and $ u $ already existed, a simple cycle is the path $ v \to u \to v $ .

Note that the second type of query is performed mentally, meaning the tree does not change in any way after it.

Help Yasya answer all the queries.

## 样例 #1

### 输入

```
2
3 7
1 2 1
3 1 8
^ 5
? 2 9
^ 1
? 1 10
^ 6
? 3 1
? 2 9
5 6
1 2 777
3 2 2812
4 1 16
5 3 1000000000
^ 4
? 3 123
? 5 1000000000
^ 1000000000
? 1 908070
? 2 1```

### 输出

```
13 15 11 10 
1000000127 2812 999756331 999999756```

## 样例 #2

### 输入

```
3
8 4
8 6 3
6 3 4
2 5 4
7 6 2
7 1 10
4 1 4
5 1 2
^ 4
^ 7
? 7 8
? 4 10
5 6
3 1 4
2 3 9
4 3 6
5 2 10
? 5 7
^ 1
^ 8
? 4 10
? 1 9
? 3 6
4 2
2 1 4
4 3 5
2 3 4
^ 13
? 1 10```

### 输出

```
14 13 
13 8 11 11 
10```

# AI分析结果



# 算法分类  
**Trie树、树上DFS/BFS、异或性质应用**

---

## 题解思路与核心算法分析

### 核心思路
1. **预处理每个节点到根的异或值**：通过DFS/BFS计算每个节点到根节点的路径异或和（`dis`数组），并记录节点深度的奇偶性。
2. **分层维护Trie树**：根据深度奇偶性将节点分为两组，分别存入两个Trie树。全局异或操作通过懒标记`k`处理，奇偶层节点受`k`的影响不同。
3. **查询优化**：查询时，根据当前节点深度奇偶性选择对应的Trie树，并动态调整查询值（是否异或`k`），利用Trie树快速找到最大异或对。

### 解决难点
- **全局异或的高效处理**：通过懒标记`k`和奇偶分层，避免每次操作遍历所有节点。偶数层节点的`dis`值实际为`dis_real ^ k`，奇数层保持不变。
- **确保查询正确性**：查询前需暂时移除当前节点`u`的`dis`值（因`u≠v`），查询后恢复，防止自环干扰。

### 算法流程
1. **预处理阶段**  
   - BFS/DFS遍历树，计算`dis[i]`和深度奇偶性`h[i]`。
   - 将`dis[i]`按奇偶性插入对应的Trie树。
2. **处理操作**  
   - `^ x`：更新懒标记`k ^= x`。
   - `? v x`：  
     ① 从对应Trie树中移除`dis[v]`。  
     ② 计算目标值`target = dis[v] ^ x`（奇层）或`target ^ k`（偶层）。  
     ③ 在两棵Trie树中查询与`target`异或后的最大值。  
     ④ 恢复`dis[v]`到Trie树。

---

## 题解评分与亮点（≥4星）

### 题解1（yx666）★★★★☆  
- **亮点**：代码结构清晰，预处理使用BFS，注释详细，变量命名规范。
- **核心代码**：  
  ```cpp
  // 分层插入Trie树
  for(int i=1; i<=n; ++i) trie[h[i]].insert(dis[i], 1);
  // 查询时动态调整目标值
  ans = max(trie[h[u]].query(dis[u]^x), trie[!h[u]].query(dis[u]^x^k));
  ```

### 题解2（yshpdyt）★★★★☆  
- **亮点**：推导过程详细，代码使用深度优先搜索预处理，实现简洁。
- **核心代码**：  
  ```cpp
  // 动态计算目标值并查询
  ll w = ((dep[x]&1) ? f[x] : (f[x]^k));
  ll p = max(T[0].qr(..., w^val^k), T[1].qr(..., w^val));
  ```

### 题解3（lfxxx）★★★★☆  
- **亮点**：思路简洁直击要害，代码实现高效，适合快速理解核心逻辑。
- **核心代码**：  
  ```cpp
  // 直接分层维护Trie
  T[dep[x]&1].ins(f[x]); 
  // 查询时处理懒标记影响
  max_query = trie[奇层].query(dis_v ^ x ^ k) 
  ```

---

## 最优思路与技巧提炼

### 关键技巧
1. **奇偶分层优化**：将节点按深度奇偶性分组，全局异操作仅影响偶层节点，减少计算量。
2. **懒标记永久化**：用`k`累计所有异或操作，查询时动态计算实际值，避免频繁修改Trie树。
3. **Trie树动态维护**：查询前暂时移除当前节点值，确保结果合法性。

### 同类型题推荐
1. [洛谷P4551] 最长异或路径：Trie树求树上最大异或路径。
2. [洛谷P4592] 动态查询子树异或特征：结合DFS序与Trie树。
3. [Codeforces 665E] 前缀异或与Trie结合。

---

## 可视化与算法演示设计

### 动画方案
1. **树结构展示**：Canvas绘制树形结构，节点按奇偶层用不同颜色标记（如蓝色奇层、红色偶层）。
2. **Trie树操作**：  
   - **插入/删除**：动态显示节点值插入对应Trie树的过程，删除时高亮对应路径。
   - **查询路径**：逐位展示Trie树中贪心选择路径（如选择相反位时显示绿色箭头）。
3. **懒标记影响**：全局异或后，偶层节点数值旁显示`⊕k`的动画效果。

### 复古像素风格
- **颜色方案**：8位色板（深蓝、亮红、黄、白），节点用像素方块表示，Trie树路径用格子动画。
- **音效设计**：  
  - **插入成功**：短促“哔”声。  
  - **查询最大值**：成功时播放胜利音效。  
  - **全局异或**：金属碰撞声。

### 交互功能
- **步进控制**：允许暂停/继续，调整动画速度观察Trie树逐位查询。
- **自动演示模式**：AI自动执行操作序列，展示查询如何动态调整目标值。

---

## 核心代码实现（yx666题解关键部分）

```cpp
// 预处理BFS计算dis和奇偶层
void bfs(int root) {
    queue<int> q;
    q.push(root);
    h[root] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &e : edges[u]) {
            int v = e.to;
            if (!h[v]) {
                h[v] = !h[u];
                dis[v] = dis[u] ^ e.val;
                q.push(v);
            }
        }
    }
}

// 查询处理
void handle_query(int u, int x) {
    trie[h[u]].remove(dis[u]); // 暂时移除当前节点
    int target = dis[u] ^ x;
    if (h[u] % 2 == 0) target ^= k; // 偶层需异或k
    int ans = trie[!h[u]].query(target);
    trie[h[u]].insert(dis[u]); // 恢复节点
    cout << ans << " ";
}
```

---

## 个人心得摘录
- **调试教训**：插入Trie树后忘记恢复节点，导致后续查询错误。需严格保证操作后数据一致性。
- **思维突破**：意识到全局异或对奇偶层影响不同，是优化时间复杂度的关键。
- **代码优化**：将深度奇偶性用位运算判断（`h[i]&1`），提升效率。

---
处理用时：105.10秒