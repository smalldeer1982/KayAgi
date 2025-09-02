# 题目信息

# [USACO07DEC] Charm Bracelet S

## 题目描述

Bessie has gone to the mall's jewelry store and spies a charm bracelet. Of course, she'd like to fill it with the best charms possible from the N (1 ≤ N ≤ 3,402) available charms. Each charm i in the supplied list has a weight Wi (1 ≤ Wi ≤ 400), a 'desirability' factor Di (1 ≤ Di ≤ 100), and can be used at most once. Bessie can only support a charm bracelet whose weight is no more than M (1 ≤ M ≤ 12,880).

Given that weight limit as a constraint and a list of the charms with their weights and desirability rating, deduce the maximum possible sum of ratings.

有 $N$ 件物品和一个容量为 $M$ 的背包。第 $i$ 件物品的重量是 $W_i$，价值是 $D_i$。求解将哪些物品装入背包可使这些物品的重量总和不超过背包容量，且价值总和最大。

## 样例 #1

### 输入

```
4 6
1 4
2 6
3 12
2 7```

### 输出

```
23```

# AI分析结果



### 综合分析与结论
本题是01背包基础题，核心在于空间优化。所有题解均围绕一维数组状态压缩展开，关键点包括逆序更新、滚动数组技巧、输入优化等。最优解法时间复杂度为 O(NM)，空间复杂度 O(M)。核心难点在于理解逆序更新的必要性（防止重复计算）和状态转移方程的推导。

---

### 高分题解推荐

#### 1. 作者：wxwyx（5星）
**关键亮点**  
- 最标准的01背包一维解法，代码简洁易读  
- 明确说明逆序更新的必要性（"从后向前找不会有影响"）  
- 注释清晰，变量命名规范（w/v数组命名优于c/w混淆）

**核心代码**  
```cpp
for(int i=1;i<=n;i++) {
    for(int j=m;j>=w[i];j--) {
        f[j]=max(f[j-w[i]]+v[i],f[j]);
    }
}
```

#### 2. 作者：Right（5星）
**关键亮点**  
- 极致空间优化（在线处理输入，不存重量价值数组）  
- 代码仅用3层循环，时间复杂度相同但空间更优  
- 提供两个版本代码（精简版与可读版）

**核心代码**  
```cpp
for(scanf("%d%d",&n,&m),i=1; i<=n; ++i)
    for(scanf("%d%d",&c,&w),j=m; j>=c; --j)
        f[j]=max(f[j],f[j-c]+w);
```

#### 3. 作者：theHermit（4星）
**关键亮点**  
- 详细推导二维转滚动数组的过程，适合理解原理  
- 给出完整的条件分支逻辑（if-else结构）  
- 数学公式与代码结合，便于理论学习

**个人心得**  
> "递推式只用到了上一行的数据，因此只需要开2行" —— 清晰点明滚动数组本质

---

### 最优技巧总结
1. **一维数组逆序更新**：确保每个物品只选一次，j从m到w[i]倒序遍历  
2. **状态转移方程**：`f[j] = max(f[j], f[j-w]+v)` 体现拿与不拿的决策  
3. **在线处理输入**：读入物品后立即处理，节省存储空间  
4. **滚动数组思维**：二维数组仅保留相邻两行（`i%2`技巧）

---

### 拓展训练推荐
1. **P1048 采药** - 完全相同的01背包模型（输入顺序不同）  
2. **P1060 开心的金明** - 价值计算变式（价格×重要度）  
3. **P1156 垃圾陷阱** - 背包与时间维度结合的变式题  

---

### 重点代码片段
**一维标准解法**（wxwyx）：
```cpp
int f[13000];
for(int i=1; i<=n; i++) {
    for(int j=m; j>=w[i]; j--) {
        f[j] = max(f[j-w[i]]+v[i], f[j]);
    }
}
```
**在线处理优化**（Right）：
```cpp
int c, w; // 无需数组存储
for(int i=1; i<=n; ++i) {
    scanf("%d%d", &c, &w);
    for(int j=m; j>=c; --j) {
        f[j] = max(f[j], f[j-c]+w);
    }
}
```

---
处理用时：44.30秒