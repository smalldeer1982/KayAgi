# 题目信息

# Two Permutations

## 题目描述

Rubik is very keen on number permutations.

A permutation $ a $ with length $ n $ is a sequence, consisting of $ n $ different numbers from 1 to $ n $ . Element number $ i $ $ (1<=i<=n) $ of this permutation will be denoted as $ a_{i} $ .

Furik decided to make a present to Rubik and came up with a new problem on permutations. Furik tells Rubik two number permutations: permutation $ a $ with length $ n $ and permutation $ b $ with length $ m $ . Rubik must give an answer to the problem: how many distinct integers $ d $ exist, such that sequence $ c $ $ (c_{1}=a_{1}+d,c_{2}=a_{2}+d,...,c_{n}=a_{n}+d) $ of length $ n $ is a subsequence of $ b $ .

Sequence $ a $ is a subsequence of sequence $ b $ , if there are such indices $ i_{1},i_{2},...,i_{n} $ $ (1<=i_{1}&lt;i_{2}&lt;...&lt;i_{n}<=m) $ , that $ a_{1}=b_{i1} $ , $ a_{2}=b_{i2} $ , $ ... $ , $ a_{n}=b_{in} $ , where $ n $ is the length of sequence $ a $ , and $ m $ is the length of sequence $ b $ .

You are given permutations $ a $ and $ b $ , help Rubik solve the given problem.

## 样例 #1

### 输入

```
1 1
1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1 2
1
2 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 3
2 3 1
1 2 3
```

### 输出

```
0
```

# AI分析结果


### 💡 Kay的C++算法解析：Two Permutations 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`哈希 + 线段树/平衡树`  
🗣️ **初步分析**：  
> 这道题要求判断排列 `a` 平移后是否在排列 `b` 中作为子序列出现。想象你在玩拼图游戏：`a` 是一块固定形状的拼图，`b` 是一块大画布。你需要找到所有能让 `a` 拼图完美嵌入 `b` 画布的位置（平移量 `d`）。核心技巧是**哈希快速比对**和**动态维护序列**：
> - **哈希**：将 `a` 序列转化为数字指纹，`a+d` 的哈希可通过预计算快速更新
> - **线段树/平衡树**：动态维护 `b` 中值域区间 `[1+d, n+d]` 内的数字序列，按出现顺序存储并计算哈希
> 
> **可视化设计思路**：
> - 像素网格展示 `b` 序列，用不同颜色标记激活/未激活位置
> - 高亮当前 `d` 值对应的值域区间 `[1+d, n+d]`
> - 当 `d` 增加时，左侧数字变暗（移出），右侧新数字亮起（加入）
> - 实时显示线段树哈希值和 `a+d` 哈希值的计算过程

---

#### 2. 精选优质题解参考
**题解一（作者：MorsLin）**  
* **点评**：  
  思路清晰——用线段树动态维护值域区间序列的哈希值。代码简洁高效：  
  - 变量命名规范（`hasha`, `qpow` 含义明确）  
  - 算法优化到位（`O(m log m)` 复杂度，空间优化）  
  - 关键技巧：哈希公式 `tree[p].a = tree[ls].a * qpow[tree[rs].tot] + tree[rs].a` 优雅处理序列合并  
  - 实践价值：代码可直接用于竞赛，边界处理严谨（`d>=0` 才判断）

**题解二（作者：ywy_c_asm）**  
* **点评**：  
  采用平衡树维护序列，亮点在哈希碰撞处理：  
  - 双哈希（`MOD1=998244353`, `MOD2=1000000007`）避免错误  
  - 内存管理精细（节点复用机制）  
  - 作者心得提到“平衡树维护哈希是平凡的”，突显对数据结构的深刻理解  

---

#### 3. 核心难点辨析与解题策略
1. **难点：动态维护子序列哈希**  
   * **分析**：`d` 变化时需快速更新 `b` 的激活序列哈希。线段树通过 `tree[p].tot` 记录激活节点数，合并时左子树哈希乘 `base^{右子树节点数}` 保持位置顺序。
   * 💡 **学习笔记**：线段树合并时维护子树大小，可动态计算幂次权重。

2. **难点：平移后哈希的增量计算**  
   * **分析**：`a+d` 的哈希 = 原哈希 + `d × (base^{n-1} + ... + base^0)`。预计算几何级数和 `sum` 避免每次重算。
   * 💡 **学习笔记**：多项式哈希中全局加法等价于加上 `d` 乘以基数的等比数列和。

3. **难点：值域区间与位置的映射**  
   * **分析**：用 `pos[]` 数组记录每个值在 `b` 中的位置，实现 `O(1)` 激活/禁用位置。
   * 💡 **学习笔记**：排列的唯一性保证了值到位置的双射，是算法成立的关键前提。

### ✨ 解题技巧总结
- **哈希技巧**：双哈希（不同基数/模数）避免碰撞  
- **数据结构选择**：线段树比平衡树更易写，但平衡树更通用  
- **边界处理**：`d` 的有效范围为 `[0, m-n]`，注意负数索引防护  
- **预处理优化**：幂次数组 `qpow[]` 和位置映射 `pos[]` 预计算  

---

#### 4. C++核心代码实现赏析
**通用核心实现（基于MorsLin的线段树）**  
```cpp
#include <iostream>
#define ULL unsigned long long
using namespace std;

const int N = 2e5 + 10;
int n, m, ans, pos[N];
ULL hasha, qpow[N] = {1}, sum; // 哈希基数为23

struct Node { ULL a, tot; } tree[N << 2]; // 四倍空间线段树

void update(int l, int r, int p, int pos, int val) {
    if (l == r) {
        tree[p].tot = val ? 1 : 0;
        tree[p].a = val; // 激活时存储数值本身
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(l, mid, p << 1, pos, val);
    else update(mid + 1, r, p << 1 | 1, pos, val);
    
    // 合并哈希：左子树 * base^右子树大小 + 右子树
    tree[p].a = tree[p << 1].a * qpow[tree[p << 1 | 1].tot] + tree[p << 1 | 1].a;
    tree[p].tot = tree[p << 1].tot + tree[p << 1 | 1].tot;
}

int main() {
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        hasha = hasha * 23 + x;       // 计算a的哈希
        qpow[i] = qpow[i - 1] * 23;   // 预计算幂次
        sum += qpow[i - 1];           // 基数的等比数列和
    }
    for (int i = 1, x; i <= m; i++) {
        cin >> x;
        pos[x] = i; // 记录值x在b中的位置
    }
    for (int i = 1; i <= m; i++) {
        if (i > n) update(1, m, 1, pos[i - n], 0); // 移出旧值
        update(1, m, 1, pos[i], i);                // 加入新值
        int d = i - n;
        if (d >= 0 && tree[1].a == hasha + d * sum) ans++;
    }
    cout << ans;
}
```
**代码解读概要**：  
1. **预处理阶段**：计算 `a` 的哈希 `hasha` 和基数等比和 `sum`  
2. **位置映射**：`pos[x]` 记录值 `x` 在 `b` 中的位置  
3. **滑动窗口**：枚举 `i` 时动态维护值域区间 `[i-n+1, i]` 的激活序列  
4. **哈希比对**：当激活序列哈希 = `hasha + d * sum` 时计数  

---

#### 5. 算法可视化：像素动画演示
![Two Permutations算法演示](https://art.pixellib.com/algorithm_anim.gif)  
* **设计思路**：  
  采用 **8位像素风格** 模拟FC游戏界面，左侧控制面板含步进按钮和速度滑块，右侧网格展示 `b` 序列。

* **动画流程**：  
  1. **初始化**：`b` 序列显示为灰色方块，控制面板启动8-bit背景音乐  
  2. **激活/移出**：  
     - 值域区间 `[1+d, n+d]` 内方块变亮，并显示数值  
     - `d` 增加时左侧方块变暗（移出音效），右侧新方块亮起（加入音效）  
  3. **哈希计算**：  
     - 当前激活序列下方显示实时哈希值  
     - `a+d` 序列显示在顶部，与激活序列比对时高亮相同/不同  
  4. **匹配成功**：当哈希值匹配，激活序列闪烁绿色，播放胜利音效  
  5. **单步控制**：支持步进/暂停/重置，速度滑块调节演示速度  

* **技术实现**：  
  Canvas绘制网格，颜色标记状态（灰=未激活，黄=激活，红=移出）。音效使用Web Audio API，关键操作触发8-bit音效。

---

#### 6. 拓展练习与相似问题思考
1. **洛谷 P1430** - 序列匹配  
   * 🗣️ **推荐理由**：同样需判断子序列匹配，但需处理非排列情况，巩固哈希技巧的变形应用。

2. **洛谷 P2757** - 等差子序列  
   * 🗣️ **推荐理由**：在序列中寻找等差子序列，练习值域区间动态维护的进阶应用。

3. **洛谷 P4212** - 外太空旅行  
   * 🗣️ **推荐理由**：结合图论与序列哈希，训练多算法融合能力。

> **通用技巧迁移**：哈希+线段树的组合可解决任何需**动态维护序列指纹**的问题，如最长回文子串、区间重复检测等。

---
处理用时：242.08秒