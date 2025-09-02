# 题目信息

# Labyrinth

## 题目描述

In a dream, Lucy found herself in a labyrinth. This labyrinth consists of $ n $ rooms, connected by $ m $ passages ( $ i $ -th passage is $ w_i $ cm wide). Each passage can be traversed in both directions. It is guaranteed that it is possible to get from any room to any other room. But this is not an ordinary labyrinth — each room in this labyrinth contains a magic candy. When Lucy eats this magic candy, she is getting wider. Specifically, if she eats candy from room $ i $ she becomes wider by $ c_i $ cm. Note that she is not obliged to eat candy the first time she visits a particular room, but she can eat each candy only once.

Unfortunately, passages in this labyrinth are pretty narrow, so after eating some candy, Lucy can get too wide and will not be able to traverse them — her width should not be greater than the width of the corresponding passage.

Lucy starts her journey in a room number $ 1 $ . She wants to eat all the candies. After that, she will just wake up, so she does not have to be able to return to the room $ 1 $ . She realizes that with her current width, she may not be able to do so, so she plans a workout before embarking on her journey. Lucy wants to know if it is possible to start with some positive width and still eat all the candies. If yes, then what is the maximal starting width with which it is possible.

## 样例 #1

### 输入

```
3 3
1 2 3
1 2 4
1 3 4
2 3 6```

### 输出

```
3```

## 样例 #2

### 输入

```
2 1
1 1
1 2 1```

### 输出

```
-1```

# AI分析结果



---

## **算法分类**  
**Kruskal重构树 + 动态规划**

---

## **题解思路与核心难点**  

### **核心思路**  
1. **最大生成树建模**：将迷宫视为图，建立最大生成树，保证路径选择时优先使用更宽的边，为初始宽度提供最大可能值。  
2. **Kruskal重构树**：在构建生成树时建立重构树，每个非叶子节点代表一条边，其子节点为合并的两棵子树。  
3. **动态规划递推**：对每个子树，通过比较先吃左子树或右子树的两种策略，计算该子树下能支持的最大初始宽度。  

### **关键步骤**  
1. **边权排序**：按边权降序排列，确保每次合并的两棵子树之间边权最小（即当前合并后的子树边权下限）。  
2. **合并策略**：合并子树时，计算两种情况的最优解：  
   - 先吃左子树，需满足 `min(当前边权 - 左子树糖果总和, 右子树所需初始宽度 - 左子树糖果总和)`  
   - 先吃右子树，需满足 `min(当前边权 - 右子树糖果总和, 左子树所需初始宽度 - 右子树糖果总和)`  
   取两者的最大值作为当前子树的最优解。  

### **解决难点**  
- **动态宽度限制**：通过重构树自底向上递推，将动态的吃糖顺序转化为静态的子树合并问题。  
- **最优子结构**：每个子树的最优解仅依赖其左右子树的最优解，保证动态规划的正确性。  

---

## **题解评分 (≥4星)**  

### **1. namelessgugugu (5星)**  
- **亮点**：代码简洁，递推代替递归，清晰展示合并策略。  
- **关键代码**：  
  ```cpp  
  f[k] = std::max(std::min(w - sum[x], f[y] - sum[x]),  
                  std::min(w - sum[y], f[x] - sum[y]));  
  ```  

### **2. _fairytale_ (4星)**  
- **亮点**：详细证明先吃完一棵子树的策略最优性，适合理论推导。  
- **关键注释**：  
  ```  
  // 先吃完子树a的糖果，保证通过边e时的宽度最小  
  ```  

### **3. Z1qqurat (4星)**  
- **亮点**：正向思维拆解问题，结合贪心与动态规划。  
- **核心公式**：  
  $$  
  f(u) = \max\left(\min(w - s_l, f_r - s_l),\ \min(w - s_r, f_l - s_r)\right)  
  $$  

---

## **最优思路与技巧**  

### **关键技巧**  
1. **Kruskal重构树**：将边权信息编码为树结构，便于后续递归处理。  
2. **自底向上递推**：在合并子树时直接计算最优解，避免显式递归。  
3. **动态规划状态设计**：`f[u]` 表示子树 `u` 下能支持的最大初始宽度，`sum[u]` 表示子树总糖果数。  

### **思维角度**  
- **逆向思维**：将吃糖导致宽度增长的限制转化为边断开顺序问题。  
- **子树隔离**：通过断边分割子树，保证合并时两子树内部已满足约束。  

---

## **相似题目推荐**  
1. **洛谷 P1967 货车运输**（最大生成树 + 路径最小值查询）  
2. **Codeforces 1578L**（本题原型，需处理动态限制）  
3. **LeetCode 778. Swim in Rising Water**（边权递增的最早可达时间）  

---

## **代码实现核心片段**  
```cpp  
// Kruskal重构树与动态规划合并  
for (int i = 1; i <= m; ++i) {  
    int x = find(E[i].x), y = find(E[i].y);  
    if (x != y) {  
        int k = i + n;  
        fa[x] = fa[y] = k;  
        ll w = E[i].w;  
        f[k] = max(  
            min(w - sum[x], f[y] - sum[x]),  
            min(w - sum[y], f[x] - sum[y])  
        );  
        sum[k] = sum[x] + sum[y];  
    }  
}  
```  

---

## **可视化设计**  

### **动画方案**  
1. **像素风格构建**：  
   - **颜色方案**：使用8位复古色，边权用绿色渐变（深绿→浅绿表示边权从小到大）。  
   - **网格绘制**：每个节点以方块表示，边权显示在方块连接线上。  
2. **合并过程高亮**：  
   - **当前合并边**：红色闪烁显示，播放“连接音效”。  
   - **子树统计**：左子树蓝色，右子树黄色，合并后紫色。  
3. **动态规划数值更新**：  
   - 每个节点上方显示 `f[u]` 和 `sum[u]`，合并时数值变化以放大动画呈现。  

### **交互设计**  
- **步进控制**：按空格键单步执行合并操作，按`A`键自动播放。  
- **音效反馈**：  
  - **成功合并**：播放 `8-bit 上升音阶`。  
  - **无解**：播放 `8-bit 错误音效`。  

---

## **总结**  
本题通过最大生成树建模与动态规划递推，将复杂的动态路径约束转化为静态子树合并问题。Kruskal重构树的应用是关键突破口，其自底向上的合并特性完美适配动态规划的最优子结构需求。掌握此类“化图为树 + 递推合并”的思维模式，可高效解决多种路径约束优化问题。

---
处理用时：82.49秒