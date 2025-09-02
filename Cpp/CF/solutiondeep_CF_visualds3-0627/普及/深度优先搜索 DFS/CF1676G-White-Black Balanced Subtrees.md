# 题目信息

# White-Black Balanced Subtrees

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root is vertex $ 1 $ . There is also a string $ s $ denoting the color of each vertex: if $ s_i = \texttt{B} $ , then vertex $ i $ is black, and if $ s_i = \texttt{W} $ , then vertex $ i $ is white.

A subtree of the tree is called balanced if the number of white vertices equals the number of black vertices. Count the number of balanced subtrees.

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root. In this problem, all trees have root $ 1 $ .

The tree is specified by an array of parents $ a_2, \dots, a_n $ containing $ n-1 $ numbers: $ a_i $ is the parent of the vertex with the number $ i $ for all $ i = 2, \dots, n $ . The parent of a vertex $ u $ is a vertex that is the next vertex on a simple path from $ u $ to the root.

The subtree of a vertex $ u $ is the set of all vertices that pass through $ u $ on a simple path to the root. For example, in the picture below, $ 7 $ is in the subtree of $ 3 $ because the simple path $ 7 \to 5 \to 3 \to 1 $ passes through $ 3 $ . Note that a vertex is included in its subtree, and the subtree of the root is the entire tree.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676G/70fb6ac8a70942903450f21b07ea9969f086df2c.png) The picture shows the tree for $ n=7 $ , $ a=[1,1,2,3,3,5] $ , and $ s=\texttt{WBBWWBW} $ . The subtree at the vertex $ 3 $ is balanced.

## 说明/提示

The first test case is pictured in the statement. Only the subtrees at vertices $ 2 $ and $ 3 $ are balanced.

In the second test case, only the subtree at vertex $ 1 $ is balanced.

In the third test case, only the subtrees at vertices $ 1 $ , $ 3 $ , $ 5 $ , and $ 7 $ are balanced.

## 样例 #1

### 输入

```
3
7
1 1 2 3 3 5
WBBWWBW
2
1
BW
8
1 2 3 4 5 6 7
BWBWBWBW```

### 输出

```
2
1
4```

# AI分析结果



**唯一算法分类**  
DFS  

---

### **题解思路与算法要点**  
所有题解均采用 **DFS 后序遍历** 统计各子树的黑白节点数：  
1. **递归计算子树属性**：每个节点的黑白数目由其子节点累加，并加上自身颜色。  
2. **平衡判断**：若某子树的黑白数目相等，则计数。  
3. **优化技巧**：部分题解将颜色映射为 ±1 的权重，通过子树权重和为 0 快速判断平衡。  

**解决难点**：  
- **子树聚合顺序**：必须通过后序遍历确保子节点统计完成后再处理父节点。  
- **多测数据重置**：需清空邻接表和统计数组，避免数据残留。  

---

### **题解评分 (≥4星)**  
1. **a1co0av5ce5az1cz0ap_ (5星)**  
   - **亮点**：代码最简，利用 ±1 权重快速判断平衡，无需单独统计黑白数目。  
   - **代码可读性**：变量命名清晰，递归函数简洁。  
   ```cpp
   int co(int rt) {
       int sum = color[rt];
       for (auto child : v[rt]) sum += co(child);
       if (sum == 0) ans++;
       return sum;
   }
   ```  

2. **5k_sync_closer (4星)**  
   - **亮点**：使用紧凑数组 `s[x][0/1]` 存储黑白数目，代码简洁高效。  
   - **实践性**：邻接表构建与 DFS 分离，逻辑清晰。  
   ```cpp
   void dfs(int x) {
       for (int i = h[x]; i; i = e[i].t) {
           int v = e[i].v;
           dfs(v);
           s[x][0] += s[v][0], s[x][1] += s[v][1];
       }
       if (s[x][0] == s[x][1]) ++q;
   }
   ```  

3. **Deamer (4星)**  
   - **亮点**：结构体 `node` 存储黑白数目，代码自解释性强。  
   - **调试提示**：注释强调多测清空的重要性。  

---

### **最优思路与技巧提炼**  
- **后序遍历聚合子树属性**：DFS 递归返回时累加子节点数据，确保父节点统计正确。  
- **颜色映射优化**：将颜色转换为数值（如黑=1，白=-1），通过求和为 0 简化平衡判断。  
- **邻接表单向构建**：仅存储父→子关系，避免双向边干扰遍历。  

---

### **同类型题目与算法套路**  
1. **子树属性统计**：如节点数、路径和、最大值等。  
2. **通用模板**：  
   ```python
   def dfs(u, parent):
       for v in children[u]:
           if v != parent:
               dfs(v, u)
               merge(u, v)  # 聚合子节点数据
       check(u)            # 判断当前子树属性
   ```  

---

### **推荐相似题目**  
1. **P1040 [NOIP2003 提高组] 加分二叉树**（统计子树结构最优解）  
2. **P1120 子树大小**（直接统计子树节点数）  
3. **P1351 [NOIP2014 提高组] 联合权值**（树形 DP 统计子节点属性）  

---

### **个人心得摘录**  
- **输入处理陷阱**：父节点数组从 `a_2` 开始，需注意顶点编号与循环起始位置（题解 `_Revenge_`）。  
- **多测清空教训**：“忘记清空邻接表导致 WA 两次，血的教训！”（题解 `Jadebo1`）。  

---

### **可视化与算法演示**  
**动画设计**：  
1. **节点遍历**：  
   - **当前节点**：红色高亮，显示黑白数目。  
   - **子节点递归**：绿色箭头指示 DFS 进入子节点。  
   - **回溯聚合**：蓝色箭头表示子节点数据返回父节点。  
2. **平衡判定**：当子树和为 0 时，节点闪烁黄色并播放“达成”音效。  

**复古像素风格**：  
- **节点表示**：8x8 像素方块，黑色（#000000）与白色（#FFFFFF）区分颜色。  
- **音效设计**：  
  - 访问新节点：短促“滴”声（Square 波形，440Hz）。  
  - 平衡判定：上升琶音（C major 和弦）。  
- **Canvas 绘制**：  
  ```javascript
  function drawNode(x, y, color) {
      ctx.fillStyle = color;
      ctx.fillRect(x * 20, y * 20, 16, 16); // 20px 间隔，16x16 节点
  }
  ```  

**自动演示模式**：  
- **AI 控制**：按 DFS 顺序自动遍历，每步延迟 500ms，可暂停/加速。  
- **状态面板**：显示当前节点、子树和、已平衡子树数。  

---

**核心代码片段**  
```cpp
// 邻接表构建（题解 5k_sync_closer）
for (int i = 2; i <= n; ++i) {
    int t; cin >> t;
    add(t, i); // 仅添加父→子边
}

// DFS 与统计（题解 a1co0av5ce5az1cz0ap_）
int co(int rt) {
    int sum = color[rt];
    for (auto child : v[rt]) 
        sum += co(child);
    if (sum == 0) ans++;
    return sum;
}
```

---
处理用时：61.51秒