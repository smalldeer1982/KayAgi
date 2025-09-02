# 题目信息

# [USACO19DEC] Tree Depth P

## 题目背景

For the new year, Farmer John decided to give his cows a festive binary search tree
(BST)! 

To generate the BST, FJ starts with a permutation $a=\{a_1,a_2,\ldots,a_N\}$
of the integers $1\ldots N$, where $N\le 300$.  He then runs the following
pseudocode with arguments $1$ and $N.$

```
generate(l,r):
  if l > r, return empty subtree;
  x = argmin_{l <= i <= r} a_i; // index of min a_i in {a_l,...,a_r}
  return a BST with x as the root, 
    generate(l,x-1) as the left subtree,
    generate(x+1,r) as the right subtree;
```
For example, the permutation $\{3,2,5,1,4\}$ generates the following BST:

```
    4
   / \
  2   5
 / \ 
1   3
```
Let $d_i(a)$ denote the depth of node $i$ in the tree corresponding to $a,$ 
meaning the number of nodes on the path from $a_i$ to the root. In the above
example, $d_4(a)=1, d_2(a)=d_5(a)=2,$ and $d_1(a)=d_3(a)=3.$

The number of inversions of $a$ is equal to the number of pairs of integers
$(i,j)$ such that $1\le i<j\le N$ and $a_i>a_j.$ The cows know that the $a$ that
FJ will use to generate the BST has exactly $K$ inversions
$(0\le K\le \frac{N(N-1)}{2})$.  Over all $a$ satisfying this condition, compute
the remainder when $\sum_ad_i(a)$ is divided by $M$ for each $1\le i\le N.$

## 题目描述

为了迎接新年，Farmer John 决定给他的奶牛们一个节日二叉搜索树！

为了生成这个二叉搜索树，Farmer John 从一个 $1 \dots N$ 的排列 $a= \{1,2, \dots ,N\}$ 开始，然后以参数 $l$ 和 $r$ 开始运行如下的伪代码：
```
generate(l,r):
  if l > r, return empty subtree;
  x = argmin_{l <= i <= r} a_i; // index of min a_i in {a_l,...,a_r}
  return a BST with x as the root, 
    generate(l,x-1) as the left subtree,
    generate(x+1,r) as the right subtree;
```
例如，排列 $\{ 3,2,5,1,4 \}$ 将产生如下的二叉搜索树：

![](https://cdn.luogu.com.cn/upload/image_hosting/gw6ursc0.png)

令 $d_i(a)$ 表示节点 $i$ 在用排列 $a$ 生成的二叉搜索树中的深度。深度定义为这个节点到根节点的路径上的点数。在上述例子中，$d_4(a)=1,d_2(a)=d_5(a)=2,d_1(a)=d_3(a)=3$。

$a$ 中的逆序对数等于满足 $1 \le i<j \le N$ 且 $a_i>a_j$ 的数对 $(i,j)$ 的个数。奶牛们知道 Farmer John 用来生成二叉搜索树的排列 $a$ 中恰好有 $K$ 个逆序对。对于所有满足条件的 $a$，请计算对于每个 $1 \le i \le N$，$\sum_a d_i(a)$ 对 $M$ 取模后的结果。

## 说明/提示

#### 样例解释 1

对于这个样例，唯一满足条件的排列为 $a=\{1,2,3\}$。

#### 样例解释 2

对于这个样例，满足条件的两个排列分别为 $a=\{1,3,2\}$ 和 $a=\{2,1,3\}$。

#### 数据范围

对于全部数据，$1\le N\le 300$，$0\le K\le \frac{N(N-1)}{2}$，保证 $M$ 是一个 $\left[ 10^8,10^9+9 \right]$ 范围中的质数。

对于测试点 $3,4$，满足 $N \le 8$；

对于测试点 $5-7$，满足 $N \le 20$；

对于测试点 $8-10$，满足 $N \le 50$。

USACO 2019 December 铂金组T3

## 样例 #1

### 输入

```
3 0 192603497
```

### 输出

```
1 2 3
```

## 样例 #2

### 输入

```
3 1 144408983
```

### 输出

```
3 4 4
```

# AI分析结果



# 唯一算法分类  
动态规划 + 组合计数

---

## 题解思路与算法要点  
### 核心思路  
将深度转化为祖先数量，通过动态规划预处理逆序对方案数，并利用撤销操作快速计算特定条件下的贡献。关键要点如下：  
1. **深度拆解**：每个节点深度等于其祖先数+1，转化为统计所有排列中每个节点作为其他节点祖先的次数。
2. **逆序对DP**：定义 `f[i][j]` 表示前i个数形成j个逆序对的方案数，通过分组背包模型递推。  
3. **撤销操作**：对于每个位置差t，撤销该位置的逆序对贡献，计算剩余部分的方案数。  
4. **差值分组**：根据节点间位置差将贡献分组，相同差值的贡献合并计算，避免O(N²)枚举。  

### 解决难点  
- **动态规划撤销**：通过前缀和优化实现逆过程，快速调整DP状态。  
- **组合条件转化**：将祖先条件转化为区间最小值约束，并映射到逆序对数的调整。  

---

## 题解评分  
### 7KByte (5星)  
- **亮点**：高效撤销操作实现，滚动数组优化空间，代码简洁无冗余乘法取模。  
- **关键代码**：  
  ```cpp
  void undo(int x) {
      memset(g, 0, sizeof(g));
      int cur = P - 1; g[0] = 1;
      rp(i, sz - x) {
          if(i > x) ad(cur, g[i - x - 1]);
          su(cur, g[i] = ck(f[n & 1][i] + cur));
      }
  }
  ```

### Karry5307 (4星)  
- **亮点**：生成函数视角清晰，多项式操作直观体现逆序对贡献。  
- **关键片段**：  
  ```cpp
  inline void mul(ll d) { // 添加差值为d的贡献
      for(int i=fd; i<fd+d; i++) f[i]=0;
      fd += d;
      // ...前缀和更新
  }
  ```

### Lgx_Q (4星)  
- **亮点**：分组背包与前后缀分离，思路清晰易于扩展。  
- **核心逻辑**：  
  ```cpp
  for(int l=2; l<=n; l++) {
      del(l); // 撤销差值为l的贡献
      res[l][0] = f[k]; // 处理u < v的情况
      if(l-2 <k) res[l][1] = f[k-(l-2)-1]; // u > v
      add(l); // 恢复
  }
  ```

---

## 最优思路提炼  
1. **祖先贡献转化**：`depth(u) = ∑[v是u的祖先] + 1`，将问题转化为统计所有祖先对。  
2. **区间最小值约束**：v是u祖先等价于`a_v`是区间`[min(u,v), max(u,v)]`的最小值。  
3. **逆序对调整**：  
   - 当v在u右侧时，强制该段贡献t个逆序对。  
   - 通过撤销背包中对应的分组贡献，快速计算条件约束下的方案数。  

---

## 同类型题推荐  
1. **P1521 逆序对计数**（基础逆序对DP）  
2. **P5854 笛卡尔树计数**（相似树结构统计）  
3. **P3759 逆序对排列计数**（动态规划优化进阶）  

---

## 可视化设计  
### 动态规划撤销过程动画  
**核心元素**：  
- **网格视图**：横轴为逆序对数（0~K），纵轴为当前元素个数，每个格子亮度表示方案数。  
- **高亮操作**：  
  - 红框标出当前处理的差值t。  
  - 黄色流动箭头表示撤销操作时的前缀和逆向传播。  
**交互控制**：  
- **步进按钮**：单步执行撤销与恢复操作。  
- **差值选择器**：滑动条选择t值，实时更新贡献计算。  

### 复古像素风格实现  
**Canvas绘制**：  
1. **16色调色板**：深蓝背景，绿色格子表示方案数，红色表示当前操作位置。  
2. **音效触发**：  
   - 撤销操作：8-bit "哔"声。  
   - 贡献累加：上升音阶。  
3. **自动演示**：  
   - 按差值从小到大自动播放撤销过程，右下角显示当前处理的t值。  

---

## 核心代码实现  
### 7KByte题解关键部分  
```cpp
#define N 305
int n, k, f[2][M], s[M], g[M], sz, ans[N];
void undo(int x) {
    memset(g, 0, sizeof(g));
    int cur = P - 1; g[0] = 1;
    for (int i=1; i<=sz-x; ++i) {
        if (i > x) cur = (cur + g[i-x-1]) % P;
        cur = (P - g[i] + cur) % P;
        g[i] = (f[n%2][i] + cur) % P;
    }
}
int main() {
    // 初始化DP...
    rp(t, n-1) {
        undo(t);
        rp(i, n - t) { // 处理所有差值为t的(u,v)
            if (t <= k) ans[i] += g[k - t];
            ans[i + t] += g[k];
        }
    }
}
```

---
处理用时：97.67秒