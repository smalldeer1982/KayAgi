# 题目信息

# Kay and Snowflake

## 题目描述

After the piece of a devilish mirror hit the Kay's eye, he is no longer interested in the beauty of the roses. Now he likes to watch snowflakes.

Once upon a time, he found a huge snowflake that has a form of the tree (connected acyclic graph) consisting of $ n $ nodes. The root of tree has index $ 1 $ . Kay is very interested in the structure of this tree.

After doing some research he formed $ q $ queries he is interested in. The $ i $ -th query asks to find a centroid of the subtree of the node $ v_{i} $ . Your goal is to answer all queries.

Subtree of a node is a part of tree consisting of this node and all it's descendants (direct or not). In other words, subtree of node $ v $ is formed by nodes $ u $ , such that node $ v $ is present on the path from $ u $ to root.

Centroid of a tree (or a subtree) is a node, such that if we erase it from the tree, the maximum size of the connected component will be at least two times smaller than the size of the initial tree (or a subtree).

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF685B/821209b858c843715556bbbb66f001612969fa03.png)The first query asks for a centroid of the whole tree — this is node $ 3 $ . If we delete node $ 3 $ the tree will split in four components, two of size $ 1 $ and two of size $ 2 $ .

The subtree of the second node consists of this node only, so the answer is $ 2 $ .

Node $ 3 $ is centroid of its own subtree.

The centroids of the subtree of the node $ 5 $ are nodes $ 5 $ and $ 6 $ — both answers are considered correct.

## 样例 #1

### 输入

```
7 4
1 1 3 3 5 3
1
2
3
5
```

### 输出

```
3
2
3
6
```

# AI分析结果



# 算法分类  
**DFS**  

---

# 题解思路与算法分析  

## 核心思路  
所有题解均基于树的重心性质：**重心一定在最大子树的重心链上**。通过一次DFS预处理每个节点的子树大小和重儿子，再通过动态调整从重儿子重心向上跳转，找到满足条件的节点。  

## 解决难点  
1. **高效预处理**：DFS计算子树大小和重儿子（O(n)时间）  
2. **重心链跳跃**：利用重心的单调性，从重儿子的重心向上跳转至第一个满足条件的节点（每个节点最多跳转一次，O(n)时间）  
3. **多查询处理**：通过预处理结果实现O(1)查询  

## 算法对比  
| 题解作者       | 核心优化                          | 数据结构         | 时间复杂度 |
|----------------|-----------------------------------|------------------|------------|
| mrsrz          | 从重儿子重心向上跳转，动态比较    | 邻接表           | O(n)       |
| Ryan_          | 直接比较父节点与当前节点的条件    | 前向星           | O(n)       |
| くろねこ       | 位运算优化与重链回溯              | 前向星+位运算    | O(n)       |
| chen_z         | 重链剖分+二分查找                 | 重链剖分         | O(n + q log n) |  

---

# 题解评分（≥4星）  

1. **mrsrz（★★★★★）**  
   - 思路清晰，代码简洁  
   - 动态跳转逻辑最直观体现重心链性质  
   - 代码可读性强，无冗余操作  

2. **Ryan_（★★★★☆）**  
   - 利用重心的两倍大小性质直接判断  
   - 代码结构清晰，但缺少详细注释  

3. **chen_z（★★★★☆）**  
   - 创新性重链剖分+二分实现  
   - 适合处理更大规模数据，但代码复杂度较高  

---

# 最优思路提炼  

1. **重心链跳跃**  
   ```cpp
   int it = rt[son]; // 从重儿子的重心开始
   while (fa[it] != now) {
       it = fa[it]; // 向上跳转父节点
       if (new_value < prev_value) update;
       else break; // 不再优化则停止
   }
   ```  
2. **重儿子预处理**  
   ```cpp
   void dfs(int u) {
       sz[u] = 1;
       for (auto v : children[u]) {
           dfs(v);
           sz[u] += sz[v];
           if (sz[v] > sz[hson[u]]) hson[u] = v; // 记录重儿子
       }
   }
   ```  

---

# 同类题目推荐  
1. **P1395 会议** - 求树的重心及距离和  
2. **CF1324F Maximum White Subtree** - 树形DP与子树统计  
3. **P2633 Count on a tree** - 树剖分与二分结合  

---

# 可视化设计  

## 动画方案  
1. **树结构展示**  
   - 用Canvas绘制树形结构，根节点在顶端  
   - 节点颜色：  
     - 红色：当前处理节点  
     - 蓝色：已计算的重心链  
     - 绿色：最终重心  

2. **重心跳转演示**  
   ```javascript
   function animateJump(node) {
       let current = node.heavyChild.center;
       while (true) {
           highlight(current); // 高亮当前节点
           if (checkCondition(current)) break; // 判断是否满足条件
           current = current.parent; // 向上跳转
       }
   }
   ```  

3. **复古像素风格**  
   - 8-bit风格节点：16x16像素方块  
   - 音效设计：  
     - 节点跳转：8-bit "beep" 音效  
     - 找到重心：胜利音效（类似超级马里奥金币声）  

---

# 核心代码实现（mrsrz版）  

```cpp
void dfs(int now) {
    sz[now] = 1;
    for (auto child : children[now]) {
        dfs(child);
        sz[now] += sz[child];
        if (sz[child] > sz[hson[now]]) 
            hson[now] = child; // 记录重儿子
    }
    
    int candidate = hson[now] ? rt[hson[now]] : now; // 从重儿子的重心开始
    while (true) {
        int max_part = max(sz[candidate], sz[now] - sz[candidate]);
        if (max_part * 2 <= sz[now]) break; // 检查条件
        candidate = fa[candidate]; // 向上跳转
    }
    rt[now] = candidate; // 记录结果
}
```  

---

# 个人心得摘录  
> "发现重心只能在重链上跳跃后，代码复杂度从O(n²)降到O(n)，这是典型的树结构性质利用。" —— mrsrz  
> "调试时发现必须严格判断两倍大小条件，漏掉等号会WA第7个测试点" —— くろねこ  

---

# 算法演示（Web实现要点）  
1. **Canvas初始化**  
   ```javascript
   const canvas = document.getElementById('tree-canvas');
   ctx.fillStyle = '#8B00FF'; // 复古紫色调
   ```  
2. **自动演示模式**  
   ```javascript
   function autoPlay() {
       let node = root;
       while (node) {
           animateJump(node);
           node = nextNodeByDFS(node); // 按DFS顺序访问
       }
   }
   ```  
3. **音效触发**  
   ```javascript
   function playSound(effect) {
       const audio = new Audio(`sfx/${effect}.wav`);
       audio.play(); // 8-bit音效文件
   }
   ```

---
处理用时：89.69秒