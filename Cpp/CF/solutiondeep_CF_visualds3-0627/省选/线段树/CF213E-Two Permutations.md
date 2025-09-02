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



## 算法分类
哈希、平衡树/线段树

---

## 题解思路与核心分析

### 核心逻辑
1. **哈希预处理**  
   - 计算排列a的哈希值H，当每个元素加d时，哈希值变为H + d*S（S为基数各次幂的和）
2. **滑动窗口维护**  
   - 将b的值域视为滑动窗口，当d变化时窗口右移，移除旧元素pos[d]，加入新元素pos[d+n]
3. **动态哈希维护**  
   - 使用平衡树或线段树动态维护窗口中所有元素的位置顺序，并计算其哈希值

### 解决难点
- **高效判断子序列**：传统O(n)比对无法处理大规模数据，转化为哈希值的快速比对
- **动态数据结构**：通过平衡树/线段树维护位置序列的哈希值，支持插入删除操作时快速更新

---

## 最优题解评分（≥4星）

### 题解1（作者：ywy_c_asm）⭐⭐⭐⭐⭐
- **亮点**：平衡树维护哈希，滑动窗口处理，双哈希避免冲突
- **代码**：使用带旋转操作的平衡树，动态维护哈希值

### 题解2（作者：MorsLin）⭐⭐⭐⭐
- **亮点**：线段树维护哈希，预处理幂次简化计算
- **代码**：权值线段树实现，代码简洁高效

### 题解3（作者：Link_Cut_Y）⭐⭐⭐⭐
- **亮点**：自然溢出哈希，权值线段树实现，避免取模运算
- **代码**：使用unsigned long long自然溢出，代码可读性强

---

## 关键思路与技巧

### 核心算法流程
1. **哈希初始化**：计算a的哈希值H及增量系数S=Σ(base^i)
2. **窗口初始化**：将b中值1~n的位置插入平衡树
3. **滑动窗口处理**：
   ```python
   for d in 0..m-n:
       if 当前树哈希 == H + d*S: ans++
       删除pos[d+1], 插入pos[d+n+1]
   ```

### 可视化设计
- **动画方案**：  
  - 左侧展示a序列+d的变化，右侧展示b的滑动窗口  
  - 高亮当前插入/删除的位置，同步显示哈希值变化  
- **复古像素风**：用8位色块表示平衡树节点，旋转时播放“咔哒”音效  
- **自动演示**：AI按d递增自动运行，按键可暂停/步进

---

## 代码片段（平衡树实现）

```cpp
struct Node {
    int ls, rs, val, pos, sz;
    ull h1, h2; // 双哈希值
} t[N];

void update(int u) {
    sz = t[ls].sz + t[rs].sz + 1;
    h1 = t[ls].h1 * pw[t[rs].sz+1] + val * pw[t[rs].sz] + t[rs].h1;
    h2 = t[ls].h2 * pw2[t[rs].sz+1] + val * pw2[t[rs].sz] + t[rs].h2;
}

void insert(int &u, int pos, int val) {
    if (!u) { u = newNode(pos, val); return; }
    if (pos < t[u].pos) {
        insert(t[u].ls, pos, val);
        if (rand() < RAND_MAX/2) rotateRight(u);
    } else {
        insert(t[u].rs, pos, val);
        if (rand() < RAND_MAX/2) rotateLeft(u); 
    }
    update(u);
}
```

---

## 相似题目
1. **P3370 字符串哈希**（哈希基础）  
2. **P3834 静态区间第k小**（平衡树/权值线段树）  
3. **P3960 列队**（动态维护序列操作）

---

## 总结
本题巧妙将子序列匹配转化为哈希值维护问题，通过动态数据结构高效处理窗口变化。平衡树与线段树的实现各有优劣，核心在于理解哈希的增量计算与滑动窗口的结合。掌握此类问题对处理大规模序列匹配具有重要意义。

---
处理用时：63.24秒