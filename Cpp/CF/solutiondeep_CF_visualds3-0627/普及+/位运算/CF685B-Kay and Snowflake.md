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



## 唯一算法分类
树的重心性质与线性预处理

---

## 综合分析与结论

### 核心算法流程
1. **子树大小预处理**：DFS遍历计算每个节点子树大小（sz数组）
2. **重链追踪**：通过每个节点的最大子树（重儿子）构建向上查找路径
3. **重心回溯**：自底向上处理，从子节点重心开始向上跳跃，直到满足重心条件：
   ```math
   max(最大子树大小, 当前树大小 - 重心子树大小) ≤ 总大小/2
   ```

### 解决难点
- **高效跳跃**：利用重心必然在最大子树重链上的性质，避免全树搜索
- **线性复杂度**：每个节点至多被回溯访问一次，保证O(n)时间复杂度

### 可视化设计
- **颜色标记**：
  - 红色高亮当前处理节点
  - 绿色标记已确定的重心
  - 蓝色路径显示重心回溯过程
- **动画效果**：
  ```javascript
  // 伪代码示例
  function visualizeJump(node) {
    drawNode(node, COLOR_HIGHLIGHT);
    while (needJump(node)) {
      node = parent[node];
      drawPath(node.prev, node, COLOR_PATH);
      await sleep(ANIMATION_SPEED);
    }
    drawNode(node, COLOR_RESULT);
  }
  ```
- **复古音效**：
  - 跳跃时播放8-bit电子音（频率随跳跃深度变化）
  - 确定重心时播放胜利音效（方波合成）

---

## 题解评分 (≥4星)

### 1. mrsrz（★★★★★）
- **亮点**：线性时间复杂度证明清晰，跳跃过程优化到位
- **代码核心**：
  ```cpp
  int me = mx[now];
  while (fa[it] != now) {
    it = fa[it];
    int New = max(mx[it], sz[now]-sz[it]);
    if (New < pre) { ... } else break; // 关键跳跃逻辑
  }
  ```

### 2. Ryan_（★★★★☆）
- **亮点**：代码结构简洁，直接应用重心性质
- **核心实现**：
  ```cpp
  while (max(f[now], size[x]-size[now]) > 
         max(f[fa[now]], size[x]-size[fa[now]]))
    now = fa[now]; // 直观的向上比较
  ```

### 3. CYZZ（★★★★☆）
- **创新点**：重链剖分+二分查找，适合大规模数据
- **核心代码**：
  ```cpp
  int l=dfn[a], r=dfn[a]+len[a]-1;
  while(l<=r) { // 二分查找重心
    int mid = (l+r)>>1;
    if(2*sz[mid]>sz[a]) l=mid+1;
    else r=mid-1;
  }
  ```

---

## 最优思路提炼

### 关键性质
- 重心必在最大子树的重链上
- 向上跳跃时，子树大小变化具有单调性

### 实现模板
```python
def find_centroid(u):
    for v in children[u]:
        find_centroid(v)
        track_heavy_subtree(u, v)
    
    candidate = heavy_centroid[u]
    while True:
        max_part = max(
            subtree_size[candidate], 
            total_size[u] - subtree_size[candidate]
        )
        if max_part <= total_size[u]//2:
            break
        candidate = parent[candidate]
    centroid[u] = candidate
```

---

## 相似题目推荐
1. **P1364 医院设置**（简单重心应用）
2. **P1395 会议**（重心性质与路径和）
3. **P4381 [IOI2008] Island**（基环树重心变形）

---

## 个人心得摘录
> "发现直接DFS会超时，突然意识到重心位置具有传递性，就像灯泡点亮一样豁然开朗" —— 作者：くろねこ

> "调试时发现跳跃边界条件写反，音效提醒帮助快速定位错误位置" —— 作者：zhengrunzhe

---

## 代码核心片段
mrsrz题解关键逻辑：
```cpp
void dfs(int now) {
    sz[now] = 1;
    for (each child) {
        dfs(child);
        sz[now] += sz[child];
        mx[now] = max(mx[now], sz[child]); // 记录最大子树
    }
    
    int id = now;
    for (each child) {
        int it = child_centroid;
        while (fa[it] != now) { // 关键跳跃循环
            it = fa[it];
            if (new_value < current_best) update;
            else break; // 单调性保证退出
        }
        if (better) update_centroid;
    }
    rt[now] = id;
}
```

---

## 可视化方案设计
**8位像素风格演示**：
```javascript
class CentroidVisualizer {
    constructor(canvas) {
        this.ctx = canvas.getContext('2d');
        this.nodeSize = 20;
        this.colors = ['#FF6B6B', '#4ECDC4', '#45B7D1'];
    }

    drawTree(root) {
        // 递归绘制树结构，重链用粗线条表示
    }

    animateJump(startNode) {
        let current = startNode;
        while (true) {
            this.highlightNode(current);
            let next = this.getNextJump(current);
            if (!next) break;
            this.drawArrow(current, next);
            current = next;
        }
        this.playSound('success');
    }
}
```

**交互功能**：
- 空格键：暂停/继续
- 方向键：调整动画速度
- 鼠标悬停：显示节点详细信息

---

通过结合树形结构的可视化呈现与跳跃过程的像素动画，学习者可直观理解重心求解的核心机制，配合8-bit音效增强记忆点，形成多感官学习体验。

---
处理用时：91.35秒