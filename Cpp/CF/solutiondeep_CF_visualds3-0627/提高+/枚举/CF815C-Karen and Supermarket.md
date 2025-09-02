# 题目信息

# Karen and Supermarket

## 题目描述

On the way home, Karen decided to stop by the supermarket to buy some groceries.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815C/155b4f0d440b0d3ff60763603980cf23ed9ae97d.png)She needs to buy a lot of goods, but since she is a student her budget is still quite limited. In fact, she can only spend up to $ b $ dollars.

The supermarket sells $ n $ goods. The $ i $ -th good can be bought for $ c_{i} $ dollars. Of course, each good can only be bought once.

Lately, the supermarket has been trying to increase its business. Karen, being a loyal customer, was given $ n $ coupons. If Karen purchases the $ i $ -th good, she can use the $ i $ -th coupon to decrease its price by $ d_{i} $ . Of course, a coupon cannot be used without buying the corresponding good.

There is, however, a constraint with the coupons. For all $ i>=2 $ , in order to use the $ i $ -th coupon, Karen must also use the $ x_{i} $ -th coupon (which may mean using even more coupons to satisfy the requirement for that coupon).

Karen wants to know the following. What is the maximum number of goods she can buy, without exceeding her budget $ b $ ?

## 说明/提示

In the first test case, Karen can purchase the following $ 4 $ items:

- Use the first coupon to buy the first item for $ 10-9=1 $ dollar.
- Use the third coupon to buy the third item for $ 12-2=10 $ dollars.
- Use the fourth coupon to buy the fourth item for $ 20-18=2 $ dollars.
- Buy the sixth item for $ 2 $ dollars.

The total cost of these goods is $ 15 $ , which falls within her budget. Note, for example, that she cannot use the coupon on the sixth item, because then she should have also used the fifth coupon to buy the fifth item, which she did not do here.

In the second test case, Karen has enough money to use all the coupons and purchase everything.

## 样例 #1

### 输入

```
6 16
10 9
10 5 1
12 2 1
20 18 3
10 2 3
2 1 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 10
3 1
3 1 1
3 1 2
3 1 3
3 1 4
```

### 输出

```
5
```

# AI分析结果



**唯一算法分类**  
树形动态规划（树形DP）

---

### **综合分析与结论**

**题目核心**：  
优惠券使用条件形成树形依赖结构，需在满足依赖的前提下，选择最多商品且总花费≤预算。  

**算法思路**：  
- **状态设计**：`dp[u][j][0/1]` 表示以节点 `u` 为根的子树中选 `j` 件商品，且 `u` 是否使用优惠券的最小花费。  
- **转移方程**：  
  - 若 `u` 未使用优惠券，子节点必须不选优惠券：  
    `dp[u][i+j][0] = min(dp[u][i][0] + dp[v][j][0])`  
  - 若 `u` 使用优惠券，子节点可选或不选：  
    `dp[u][i+j][1] = min(dp[u][i][1] + min(dp[v][j][0], dp[v][j][1]))`  
- **优化**：按子树大小合并，倒序枚举已处理节点数，确保时间复杂度为 O(n²)。  

**难点与解决**：  
- **树形依赖建模**：通过父节点 `x_i` 建树，确保转移时满足依赖条件。  
- **空间优化**：部分题解使用动态数组（如 `vector`）减少内存占用。  

---

### **题解清单 (≥4星)**

1. **Fireworks_Rise (4.5星)**  
   - **亮点**：代码结构清晰，强调子树合并的顺序优化，注释详细。  
   - **关键代码**：  
     ```cpp
     for(int i = sz[x]; i >= 0; i--) 
         for(int j = 0; j <= sz[v]; j++) {
             f[x][i+j][0] = min(f[x][i+j][0], f[x][i][0] + f[v][j][0]);
             f[x][i+j][1] = min(f[x][i+j][1], f[x][i][1] + min(f[v][j][1], f[v][j][0]));
         }
     sz[x] += sz[v];
     ```

2. **神眷之樱花 (4星)**  
   - **亮点**：明确初始化边界条件，处理 `dp[u][0][1]` 无效情况。  
   - **关键代码**：  
     ```cpp
     dp[x][0][0] = 0;
     dp[x][1][0] = c[x];
     dp[x][1][1] = c[x] - d[x];
     ```

3. **chihik (4星)**  
   - **亮点**：代码简洁，使用 `min` 函数简化状态转移。  
   - **关键代码**：  
     ```cpp
     dp[u][j+k][1] = min(dp[u][j+k][1], dp[u][j][1] + min(dp[v][k][0], dp[v][k][1]));
     ```

---

### **最优思路与技巧提炼**

1. **状态压缩**：使用 `dp[u][j][0/1]` 区分父节点状态，确保依赖条件满足。  
2. **子树合并优化**：按子树大小倒序枚举，确保每对节点仅处理一次。  
3. **边界处理**：初始化 `dp[u][0][0] = 0`，其他状态设为极大值避免干扰。  

---

### **同类题型与洛谷推荐**

1. **P2014 [CTSC1997] 选课**：树形背包，选课依赖父节点。  
2. **P1273 有线电视网**：树形DP统计收益。  
3. **P2585 [ZJOI2006] 三色二叉树**：树形结构上的状态转移。  

---

### **可视化与算法演示**

**动画设计**：  
1. **树形结构**：以根节点为起点，逐步展开子树，节点颜色区分是否使用优惠券。  
2. **合并过程**：显示父节点与子节点的合并步骤，高亮当前处理的子树和状态转移。  
3. **复古像素风**：  
   - **颜色方案**：绿色表示选中，红色未选，黄色为当前操作节点。  
   - **音效**：合并时播放“滴”声，成功找到解时播放胜利音效。  
4. **交互控制**：支持暂停/继续、调整合并速度，单步观察状态更新。  

**代码片段（伪代码）**：  
```javascript
function drawTree(node, x, y) {
    drawPixelSquare(x, y, node.selected ? 0x00FF00 : 0xFF0000);
    node.children.forEach((child, i) => {
        drawLine(x, y, x + i*50, y + 50);
        drawTree(child, x + i*50, y + 50);
    });
}
```

---

**总结**：通过树形DP建模依赖关系，合理设计状态与转移，结合子树合并优化时间复杂度，是解决此类问题的核心思路。

---
处理用时：83.84秒