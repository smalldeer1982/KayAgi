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
树形动态规划（树形DP） / 子树重心性质

---

## 综合分析与结论

### 核心算法流程
1. **预处理子树大小**：通过DFS计算每个节点的子树大小（`size`）和最大子树（`mx`）。
2. **重心推导**：对于每个节点，其子树重心要么在重儿子的子树中，要么是自身。从重儿子的重心出发，向上跳直到满足条件：剩余子树大小不超过总大小的一半。
3. **动态更新**：利用贪心策略，每个节点仅需访问一次，时间复杂度O(n)。

### 解决难点
- **高效定位重心**：利用树的重心必在重链上的性质，避免全树遍历。
- **跳跃优化**：通过向上跳跃时及时终止（当不再更优时），确保线性时间复杂度。

### 可视化设计
1. **动画流程**：
   - **颜色标记**：当前处理的节点（红色）、重儿子路径（蓝色）、候选重心（绿色）。
   - **步进控制**：展示从重儿子的重心向上跳的过程，高亮每个跳跃步骤的条件判断。
   - **子树大小显示**：在节点旁实时显示`size`和`mx`值。
2. **复古像素风格**：
   - 用8位像素网格表示树结构，节点用不同颜色方块区分。
   - 音效：跳跃时播放“点击”音效，找到重心时播放“确认”音效。

---

## 题解清单（≥4星）

### 1. mrsrz（★★★★★）
- **亮点**：清晰的贪心策略，代码简洁高效，利用子重心跳跃优化时间复杂度。
- **关键代码**：
  ```cpp
  for(int i=head[now];i;i=e[i].nxt){
    int it=rt[e[i].to];
    while(fa[it]!=now){
      it=fa[it]; // 向上跳跃
      if (更优) 更新重心 else break;
    }
  }
  ```

### 2. chen_z（★★★★☆）
- **亮点**：直接利用子树大小与重儿子关系，逻辑直观。
- **关键代码**：
  ```cpp
  if ((son[res] << 1) > son[x]){
    int temp = ans[res];
    while ((son[x] - son[temp] << 1) > son[x]) 
      temp = fa[temp];
    ans[x] = temp;
  }
  ```

### 3. CYZZ（★★★★☆）
- **亮点**：结合重链剖分，通过DFS序二分快速定位重心。
- **关键代码**：
  ```cpp
  int l=dfn[a], r=dfn[a]+len[a]-1;
  while(l<=r){ // 在重链上二分
    if (sz[rnk[mid]]*2 > sz[a]) l=mid+1;
    else r=mid-1;
  }
  ```

---

## 最优思路提炼
1. **重链跳跃法**：从重儿子的重心向上跳，直到剩余子树大小满足条件。
2. **预处理优化**：提前计算子树大小和重儿子，减少重复计算。
3. **线性时间复杂度**：每个节点仅访问一次，跳跃过程保证O(n)。

---

## 同类型题与算法套路
- **通用解法**：子树重心问题通常结合树形DP和贪心策略，预处理子树信息后通过性质推导。
- **类似题目**：
  1. **P1395 会议**：求树的重心及其深度和。
  2. **P1364 医院设置**：类似重心问题，计算最小距离和。
  3. **CF708C Centroids**：动态调整树结构后的重心判断。

---

## 推荐洛谷题目
1. **P1395**（基础重心性质）
2. **P1364**（距离和优化）
3. **CF708C**（动态树重心）

---

## 个人心得摘录
- **调试教训**：初始暴力DFS会超时，需利用树的性质优化（如作者くろねこ的优化过程）。
- **顿悟点**：发现重心必在重链上，减少搜索空间（如mrsrz的跳跃策略）。

---

## 可视化与算法演示
### 核心步骤动画设计
1. **树结构绘制**：用Canvas绘制树形图，节点按层次布局。
2. **动态跳跃**：
   - **当前节点**：红色高亮。
   - **重儿子路径**：蓝色线条。
   - **候选重心**：绿色闪烁，逐步上跳至黄色（最终重心）。
3. **音效与交互**：
   - **点击节点**：播放选择音效。
   - **自动演示**：按步播放，可调节速度。

### 复古风格实现
```javascript
// 示例：Canvas绘制节点
function drawNode(x, y, color) {
  ctx.fillStyle = color;
  ctx.fillRect(x * 30, y * 30, 20, 20); // 8位像素风格
}
// 音效触发
function playSound(effect) {
  const sfx = { jump: 'blip.mp3', confirm: 'success.wav' };
  new Audio(sfx[effect]).play();
}
```

---

## 代码实现（mrsrz核心逻辑）
```cpp
void dfs(int now) {
  sz[now] = 1;
  for (int i = head[now]; i; i = e[i].nxt) {
    dfs(e[i].to);
    sz[now] += sz[e[i].to];
    mx[now] = max(mx[now], sz[e[i].to]); // 计算最大子树
  }
  int id = now;
  for (int i = head[now]; i; i = e[i].nxt) {
    int it = rt[e[i].to]; // 子节点的重心
    while (fa[it] != now) {
      it = fa[it];
      if (更优条件) 更新id; else break; // 关键跳跃
    }
  }
  rt[now] = id; // 记录当前重心
}
```

---
处理用时：116.66秒