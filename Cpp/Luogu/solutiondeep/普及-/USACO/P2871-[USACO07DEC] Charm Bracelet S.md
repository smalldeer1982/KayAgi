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
本题是标准的01背包问题，所有题解均基于动态规划思想。核心优化在于使用一维数组降低空间复杂度（O(M)），通过逆序遍历避免重复选择。最优解法的关键点包括：
1. **一维数组状态压缩**：用`f[j] = max(f[j], f[j-w]+v)`替代二维数组
2. **逆序枚举容量**：从M到w[i]逆序更新，保证物品仅选一次
3. **在线处理输入**：边读入物品数据边处理，减少内存占用

### 高星题解推荐

#### 1. 作者：Right（5星）
**关键亮点**：
- 极致优化的代码（仅3行核心逻辑）
- 在线处理输入，无需存储物品数组
- 使用宏定义简化比较运算
```cpp
for (scanf("%d%d",&n,&m),i=1; i<=n; ++i)
    for (scanf("%d%d",&c,&w),j=m; j>=c; --j)
        f[j]=max(f[j],f[j-c]+w);
```
**技巧总结**：输入与计算同步进行，内存占用最小化

#### 2. 作者：wxwyx（4星）
**关键亮点**：
- 清晰的变量命名和注释
- 基础教学向代码，适合新手理解
- 强调逆序更新原理
```cpp
for(int i=1;i<=n;i++)
    for(int j=m;j>=w[i];j--)
        f[j]=max(f[j-w[i]]+v[i],f[j]);
```
**个人心得**："从后向前找不会有其它影响" 点明逆序关键

#### 3. 作者：CodinPnda（4星）
**关键亮点**：
- 对比二维与一维解法差异
- 给出完整状态转移方程推导
- 代码包含错误陷阱警示（需读者仔细检查）
```cpp
for(int j = 0; j <= n; j++) // 故意写反的循环结构
    for(int i = m; i >= w[j]; i--)
        f[i] = max(f[i], f[i-w[j]]+c[j]);
```
**踩坑警示**：循环顺序错误会导致完全背包效果

### 最优关键思路提炼
1. **状态定义**：`f[j]`表示容量为j时的最大价值
2. **转移方程**：`f[j] = max(f[j], f[j-w]+v)`
3. **逆序原理**：保证每个物品仅被计算一次
4. **空间优化**：一维数组替代二维，空间复杂度O(M)
5. **输入优化**：在线处理省去物品存储空间

### 拓展与相似题目推荐
1. **P1048 采药** - 完全相同的01背包模型（输入顺序不同）
2. **P1616 疯狂的采药** - 完全背包问题（可重复选择）
3. **P1060 开心的金明** - 01背包变种（价值计算方式变化）

### 有价值的个人心得摘录
1. theHermit："滚动数组只用存储两行，虽然不如一维高效，但更易理解二维逻辑"
2. CodinPnda："在代码中留明显错误，防止抄袭者直接复制"
3. 不存在之人："自己写完代码后对比验证，发现思路正确时成就感满满"
4. fashoint："学信竞第一道DP就是01背包，理解后很多问题都能转化为背包模型"

---
处理用时：50.70秒