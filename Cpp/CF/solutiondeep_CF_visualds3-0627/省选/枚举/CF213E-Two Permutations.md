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



## 【唯一算法分类】  
哈希 & 滑动窗口

---

## 【综合分析与结论】  

**核心思路**：  
通过哈希预处理排列 `a`，利用滑动窗口维护 `b` 中当前值域区间对应的位置序列的哈希值，动态比较与 `a+x` 的哈希值是否一致。关键难点在于高效维护动态插入/删除操作的哈希值，平衡树或线段树用于维护有序位置序列的哈希。

**核心流程**：  
1. **预处理哈希**：计算 `a` 的哈希 `ha`，并预计算 `a+x` 的哈希增量公式（`ha + x * ΣB^i`）。  
2. **滑动窗口初始化**：将 `b` 中值域 `[1, n]` 的位置插入数据结构，计算初始哈希。  
3. **窗口移动**：每次 `x` 增1，删除旧值 `x`，插入新值 `n+x`，更新哈希并与 `a+x` 比较。  

**可视化设计**：  
- **Canvas 网格**：将 `b` 序列以像素块展示，当前窗口值域区间高亮。  
- **动态插入/删除**：用颜色标记插入（绿色）和删除（红色）的位置，平衡树/线段树节点显示哈希值变化。  
- **音效触发**：哈希匹配时播放成功音效，否则失败音效。  
- **复古风格**：8-bit 像素字体，背景音乐循环播放，步进控制面板采用复古 UI。  

---

## 【题解清单 (≥4星)】  

### 1. 作者：ywy_c_asm (5星)  
- **亮点**：平衡树维护滑动窗口的哈希，双哈希避免碰撞，代码结构清晰。  
- **关键代码**：利用平衡树动态插入/删除节点，维护哈希值。  

### 2. 作者：MorsLin (4.5星)  
- **亮点**：线段树维护动态哈希，预处理基数的幂次，逻辑简洁。  
- **核心代码**：线段树区间乘法和单点更新结合，高效计算哈希。  

### 3. 作者：Link_Cut_Y (4星)  
- **亮点**：自然溢出哈希避免取模，权值线段树实现更易调试。  
- **心得**：强调哈希参数选择的重要性，自然溢出在实践中表现更优。  

---

## 【最优思路提炼】  

1. **双滑动哈希**：  
   - 预处理 `a` 的哈希 `ha`，`a+x` 的哈希为 `ha + x * ΣB^(i-1)`。  
   - 维护 `b` 中当前值域窗口的位置序列哈希，与 `a+x` 比较。  

2. **动态数据结构选择**：  
   - **平衡树**：天然支持有序序列的插入/删除，直接维护哈希（如题解1）。  
   - **线段树**：通过 `pos` 数组将值域映射到位置，区间乘法维护哈希权重（如题解2）。  

3. **哈希参数优化**：  
   - 双哈希（模数不同）或自然溢出避免碰撞，后者代码更简洁（如题解3）。  

---

## 【同类型题拓展】  
- **通用解法**：子序列哈希匹配问题，可通过滑动窗口+动态哈希解决。  
- **类似题目**：字符串循环匹配、动态区间相似性判断。  

---

## 【推荐题目】  
1. P3370 【模板】字符串哈希  
2. P1381 单词背诵（滑动窗口+哈希计数）  
3. P4551 最长异或路径（哈希与位运算结合）  

---

## 【代码片段与可视化实现】  

**核心代码（线段树维护哈希）**：  
```cpp  
// 线段树节点定义（题解2）
struct node {
    int l, r;
    ull hash, tot; // hash为当前哈希，tot为有效节点数
} tree[N << 2];

void up(int l, int r, int p) {
    tree[p].tot = tree[ls].tot + tree[rs].tot;
    tree[p].hash = tree[ls].hash * qpow[tree[rs].tot] + tree[rs].hash;
}

void update(int l, int r, int pos, int p, int k) {
    if (l == r) {
        tree[p].tot = (k != 0);
        tree[p].hash = k;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(l, mid, pos, ls, k);
    else update(mid+1, r, pos, rs, k);
    up(l, r, p);
}
```

**复古动画设计（JS伪代码）**：  
```javascript  
// Canvas 初始化
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');
const GRID_SIZE = 20;

function drawBlock(x, val, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x * GRID_SIZE, 0, GRID_SIZE, GRID_SIZE);
    ctx.fillStyle = 'black';
    ctx.fillText(val, x * GRID_SIZE + 2, GRID_SIZE - 2);
}

// 播放插入动画
function playInsert(pos, val) {
    drawBlock(pos, val, '#00ff00'); // 绿色高亮
    setTimeout(() => drawBlock(pos, val, '#cccccc'), 200);
}

// 自动演示循环
let x = 0;
function autoPlay() {
    if (x > m - n) return;
    updateHash(x);
    if (hashMatch()) playSuccessSound();
    x++;
    setTimeout(autoPlay, 1000);
}
```

---

## 【调试心得摘录】  
- **作者：Link_Cut_Y**：尝试15个模数后改用自然溢出，强调哈希参数的重要性。  
- **作者：CaoXian**：最初误判子序列为子串，调整后采用动态插入策略。  

---

**可视化总结**：  
通过像素块动态展示 `b` 序列的滑动窗口，绿色/红色标记插入删除，右侧面板显示当前哈希值对比。8-bit 音效增强反馈，步进控制支持学习节奏调整。

---
处理用时：73.86秒