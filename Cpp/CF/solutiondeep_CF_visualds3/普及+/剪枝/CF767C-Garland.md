# 题目信息

# Garland

## 题目描述

Once at New Year Dima had a dream in which he was presented a fairy garland. A garland is a set of lamps, some pairs of which are connected by wires. Dima remembered that each two lamps in the garland were connected directly or indirectly via some wires. Furthermore, the number of wires was exactly one less than the number of lamps.

There was something unusual about the garland. Each lamp had its own brightness which depended on the temperature of the lamp. Temperatures could be positive, negative or zero. Dima has two friends, so he decided to share the garland with them. He wants to cut two different wires so that the garland breaks up into three parts. Each part of the garland should shine equally, i. e. the sums of lamps' temperatures should be equal in each of the parts. Of course, each of the parts should be non-empty, i. e. each part should contain at least one lamp.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/c2b0d1858f505d34921dc11648298e7a84c2f7b5.png)Help Dima to find a suitable way to cut the garland, or determine that this is impossible.

While examining the garland, Dima lifted it up holding by one of the lamps. Thus, each of the lamps, except the one he is holding by, is now hanging on some wire. So, you should print two lamp ids as the answer which denote that Dima should cut the wires these lamps are hanging on. Of course, the lamp Dima is holding the garland by can't be included in the answer.

## 说明/提示

The garland and cuts scheme for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/578d2b3356505b1b3987876ed70f57ef1ae0c5b0.png)

## 样例 #1

### 输入

```
6
2 4
0 5
4 2
2 1
1 1
4 2
```

### 输出

```
1 4
```

## 样例 #2

### 输入

```
6
2 4
0 6
4 2
2 1
1 1
4 2
```

### 输出

```
-1
```

# AI分析结果


### 💡 Kay的C++算法解析：Garland 深入学习指南 💡

**题目解读与核心算法识别**  
✨ **本题主要考察**：`树形动态规划/DFS遍历`  
🗣️ **初步分析**：  
> 解决Garland问题的核心在于**树形动态规划**。想象这棵树是一串葡萄（节点），每颗葡萄有不同的甜度（权值）。我们要切两刀，分成三串甜度相同的葡萄串（子树权和相等）。  
> - 核心思路：DFS遍历计算每个子树的权值和，当子树和等于总和的1/3时，记录该子树根节点并重置其和为0（避免重复切割）。  
> - 难点：需确保切割位置不重叠，且不能选择整棵树的根节点。  
> - 可视化设计：在像素动画中，用不同颜色表示节点权值，高亮当前DFS节点。当找到合法子树时，播放“叮”音效并改变子树颜色（如绿色），控制面板支持单步执行和速度调节。  

---

### 2. 精选优质题解参考
**题解一（作者：maniac!）**  
* **点评**：思路清晰直击核心——DFS计算子树和，遇到和为总和的1/3时立即记录并重置。代码简洁规范（如`tem[x]`明确存储子树和），边界处理严谨（先判断总和模3）。亮点在于用`ans[++cnt]=x`直接记录解，实践价值高（可直接用于竞赛）。  

**题解二（作者：试试事实上吗）**  
* **点评**：通过图示形象解释子树切割逻辑，代码中`t[u]=0`巧妙避免重叠解。变量名`sum/3`增强可读性，算法有效性高（严格O(n)）。特别亮点：详细分析了链式结构的特例，强化了读者对边界情况的理解。  

**题解三（作者：良月澪二）**  
* **点评**：采用`vector`存图更符合C++最佳实践，`size[fr] += size[v[fr][i]]`体现标准树形DP实现。代码模块化优秀（分离DFS和主逻辑），`pre`数组显式存储父节点避免重复访问，是学习树遍历的典范。  

---

### 3. 核心难点辨析与解题策略
1. **难点：如何高效计算子树和并确保切割不重叠**  
   * **分析**：DFS后序遍历（自底向上）计算子树和，当子树和等于`sum/3`时，立即将其重置为0。这样上层计算不会包含已切割的子树。  
   * 💡 **学习笔记**：重置子树和是避免重叠解的关键技巧！  

2. **难点：识别合法切割点并排除根节点**  
   * **分析**：在DFS中记录子树根节点编号，但需跳过整棵树的根节点（题目要求切割边悬挂的节点不能是根）。  
   * 💡 **学习笔记**：用`if (pre[fr])`排除根节点，确保答案合法性。  

3. **难点：边界条件与无解情况处理**  
   * **分析**：若总和不是3的倍数直接输出-1；若合法子树数不足2，即使重置后也无法满足三部分，同样输出-1。  
   * 💡 **学习笔记**：预先判断`sum%3 !=0`可节省不必要的DFS计算。  

✨ **解题技巧总结**  
- **问题分解**：将“三等分树”拆解为“计算子树和”+“寻找两棵独立子树”。  
- **状态重置**：找到合法子树后立即置零其和，确保上层计算正确。  
- **边界测试**：测试单链树、负权值、总和为0等边界情况。  

---

### 4. C++核心代码实现赏析
**本题通用核心C++实现参考**  
* **说明**：综合优质题解思路，DFS遍历+子树重置，代码简洁高效。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <vector>
  using namespace std;
  const int MAXN = 1e6+5;

  vector<int> graph[MAXN];
  int weight[MAXN], total, cnt, root;
  int subtree_sum[MAXN];
  vector<int> solutions;

  void dfs(int node, int parent) {
      subtree_sum[node] = weight[node];
      for (int child : graph[node]) {
          if (child == parent) continue;
          dfs(child, node);
          subtree_sum[node] += subtree_sum[child];
      }
      if (subtree_sum[node] == total) {
          solutions.push_back(node);
          subtree_sum[node] = 0; // 重置子树和
      }
  }

  int main() {
      int n; cin >> n;
      for (int i=1; i<=n; i++) {
          int parent; 
          cin >> parent >> weight[i];
          total += weight[i];
          if (parent == 0) root = i;
          else graph[parent].push_back(i);
      }
      if (total % 3 != 0) cout << "-1\n";
      else {
          total /= 3;
          dfs(root, 0);
          if (solutions.size() >= 2) 
              cout << solutions[0] << " " << solutions[1] << "\n";
          else cout << "-1\n";
      }
      return 0;
  }
  ```
* **代码解读概要**：  
  > 1. 读入树结构并计算权值总和`total`。  
  > 2. 若`total`非3的倍数直接输出-1。  
  > 3. DFS遍历：计算每个节点的子树和，遇到和等于`total`时记录节点并重置子树和为0。  
  > 4. 若找到至少两个解，输出前两个。  

**题解一（maniac!）核心片段赏析**  
* **亮点**：简洁高效，用`tem[x]=0`重置子树和避免重叠。  
* **核心代码**：  
  ```cpp
  void dfs(int x, int y) {
      tem[x] = t[x];
      for (int i=head[x]; i; i=next[i]) {
          int v = ver[i];
          if (v != y) {
              dfs(v, x);
              tem[x] += tem[v]; // 累加子树和
          }
      }
      if (tem[x] == sum) {
          ans[++cnt] = x;
          tem[x] = 0; // 关键重置操作
      }
  }
  ```
* **代码解读**：  
  > - `dfs`参数`x`为当前节点，`y`为父节点（防回环）。  
  > - `tem[x] = t[x]`初始化当前节点权值。  
  > - 遍历子节点累加子树和，遇到`tem[x]==sum`时记录答案并重置。  
  > 💡 **学习笔记**：后序遍历确保子节点先被处理。  

**题解二（试试事实上吗）核心片段赏析**  
* **亮点**：图示化解释子树切割，强调重置必要性。  
* **核心代码**：  
  ```cpp
  if (treesum[now] == sum/3) {
      ans[++num_ans] = now;
      treesum[now] = 0; // 显式重置
  }
  ```
* **代码解读**：  
  > - 当子树和等于目标值时，记录节点并置零。  
  > - 重置后上层计算`treesum[parent]`不会包含此子树。  
  > 💡 **学习笔记**：重置操作使子树独立，是算法的核心精妙之处。  

**题解三（良月澪二）核心片段赏析**  
* **亮点**：`vector`存图更现代，`pre`数组显式处理父节点。  
* **核心代码**：  
  ```cpp
  for (int i=0; i<v[fr].size(); i++) {
      if (v[fr][i] != pre[fr]) {
          dfs(v[fr][i], fr);
          size[fr] += size[v[fr][i]]; 
      }
  }
  ```
* **代码解读**：  
  > - `vector`存储邻接节点，遍历更安全。  
  > - `pre[fr]`跳过父节点避免回环。  
  > 💡 **学习笔记**：显式存储父节点是树遍历的通用技巧。  

---

### 5. 算法可视化：像素动画演示
**主题**：像素风“葡萄切割”模拟器  
**核心演示内容**：  
- 树结构以**8位像素风**呈现，节点为彩色方块（权值越大颜色越深）。  
- DFS遍历时当前节点**闪烁白光**，子树和实时显示在节点上方。  
- 当子树和等于`sum/3`时，播放“叮”音效，子树变绿色并脱离原树。  

**动画关键帧设计**：  
1. **初始化**：  
   - 像素网格展示树形结构，根节点居中（金色方块）。  
   - 控制面板：开始/暂停、单步、速度滑块。  
   - 背景播放8位风格BGM。  

2. **DFS过程**：  
   ```mermaid
   graph LR
   A[当前节点闪烁] --> B[递归子节点]
   B --> C[更新子树和显示]
   C --> D{和=sum/3?}
   D -- 是 --> E[播放音效+变绿色]
   D -- 否 --> A
   ```

3. **成功判定**：  
   - 找到两个解时，两棵子树**脉冲闪烁**，播放胜利音效。  
   - 若失败，播放低沉音效并显示红色“-1”。  

**交互设计**：  
- **单步执行**：按步观察子树和计算过程。  
- **自动演示**：AI自动执行DFS（速度可调），类似贪吃蛇AI寻路。  
- **游戏化**：每找到一个合法子树视为“过关”，奖励像素星星+积分。  

---

### 6. 拓展练习与相似问题
**通用技巧迁移**：  
树形DP/子树和技巧还可用于：  
1. 树的重心（平衡子树大小）  
2. 子树统计问题（如满足条件的子树数量）  
3. 树链权重平衡（如CF Round #Pi的Tree and Queries）  

**洛谷练习推荐**：  
1. **P2014 [CTSC1997]选课**  
   🗣️ **推荐理由**：树形DP经典题，理解状态定义如何影响子树计算。  

2. **P1364 医院设置**  
   🗣️ **推荐理由**：结合子树和与树的重心，拓展权值计算思路。  

3. **P1271 重建道路**  
   🗣️ **推荐理由**：切割子树的高级应用，强化树形DP边界处理。  

---

### 7. 学习心得与经验分享
> **参考经验（来自 maniac!）**：  
> “最初在边界处理卡了很久，后来通过打印中间变量发现重置子树和是避免重叠的关键。”  
>  
> **Kay点评**：  
> 作者的经验极具普适性——**重置子树和**是本算法的核心技巧。在树形DP中，类似的状态重置思想（如回溯法）可推广至更多场景。调试时输出中间状态（如`tem[x]`）能快速定位逻辑漏洞。  

---

本次解析就到这里！树形DP的关键在于**自底向上计算+状态定义清晰**。多练习子树和问题，你也能成为“剪葡萄高手”！下次挑战再见！ 💪

---
处理用时：136.95秒