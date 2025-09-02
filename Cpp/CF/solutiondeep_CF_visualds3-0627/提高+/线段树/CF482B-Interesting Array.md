# 题目信息

# Interesting Array

## 题目描述

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 样例 #1

### 输入

```
3 1
1 3 3
```

### 输出

```
YES
3 3 3
```

## 样例 #2

### 输入

```
3 2
1 3 3
1 3 2
```

### 输出

```
NO
```

# AI分析结果



---

**算法分类**：线段树 / 差分前缀和

---

### 题解思路与核心分析

#### 核心算法逻辑
1. **强制满足必须为1的位**：对于每个约束条件，将区间内所有数的二进制位上与q_i相同的位设为1（通过线段树的区间或操作，或差分数组的逐位覆盖）。
2. **验证约束条件**：在所有位设置完成后，再次检查每个约束区间的按位与结果是否等于q_i。

#### 解决难点与关键点
- **必须位的强制设置**：通过区间或操作（线段树）或差分前缀和（逐位处理）确保所有约束中的1位被覆盖。
- **冲突检测**：若某约束要求某位为0，但该位在强制设置后全为1，则无解。
- **数据结构选择**：线段树支持高效区间修改和查询，差分数组则通过逐位处理降低复杂度。

---

### 高分题解推荐（≥4★）

1. **wanggk（5★）**  
   - **亮点**：线段树实现简洁，pushdown逻辑清晰，利用线段树的区间或操作与按位与查询完美契合题意。  
   - **代码可读性**：结构分明，变量命名规范，注释详细。

2. **TKXZ133（4.5★）**  
   - **亮点**：线段树封装为类，代码模块化程度高，支持多种操作（或、与查询）。  
   - **优化点**：通过结构体封装线段树节点，提升代码复用性。

3. **CaiXY06（4★）**  
   - **亮点**：差分前缀和逐位处理，时间复杂度更低（$O(n \log q)$），空间占用小。  
   - **创新点**：避免线段树的复杂实现，通过位拆分和前缀和快速判断冲突。

---

### 最优思路提炼
- **线段树核心代码逻辑**：
  ```cpp
  void update(int o, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        tree[o] |= val;  // 关键操作：区间或
        lazy[o] |= val;
        return;
    }
    pushdown(o);
    if (ql <= mid) update(lson, ql, qr, val);
    if (qr > mid) update(rson, ql, qr, val);
    pushup(o);
  }
  ```
  - **作用**：将区间内所有数的指定二进制位强制设为1。

- **差分前缀和核心逻辑**：
  ```cpp
  void check(int x) {
    memset(c, 0, sizeof(c));
    for (每个约束条件i) {
        if (q_i的x位为1) {
            c[l_i]++; c[r_i+1]--;  // 差分标记必须为1的位
        }
    }
    for (前缀和计算实际覆盖情况) {
        if (覆盖) a[i] |= x;
    }
  }
  ```
  - **作用**：通过差分数组快速统计每个位是否被完全覆盖。

---

### 同类题目推荐
1. **CF242E**：区间异或与区间求和。
2. **洛谷P3372**：线段树区间加与求和（基础线段树练习）。
3. **洛谷P5490**：扫描线算法求矩形面积并（区间覆盖与合并）。

---

### 可视化设计思路
1. **线段树操作动画**：
   - **颜色标记**：被修改的区间节点标为红色，查询时路径标为蓝色。
   - **步进控制**：单步展示区间或操作和懒标记下推。
   - **音效**：区间修改时播放"滴"声，冲突检测失败时播放"错误"音效。

2. **差分数组像素风格演示**：
   - **8位像素网格**：每个格子代表数组的一个元素，颜色深浅表示二进制位的1/0状态。
   - **自动演示**：逐位处理时，对应位被覆盖的区间闪烁黄色，验证时冲突位标为闪烁红色。

---

### 代码实现（线段树核心部分）
```cpp
// 线段树节点定义
struct Node {
    int sum;  // 区间按位与结果
    int lazy; // 懒标记（累积或操作）
};

void update(int o, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        tree[o].sum |= val;
        tree[o].lazy |= val;
        return;
    }
    pushdown(o);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(lson, l, mid, ql, qr, val);
    if (qr > mid) update(rson, mid+1, r, ql, qr, val);
    pushup(o);
}

int query(int o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[o].sum;
    pushdown(o);
    int res = (1 << 30) - 1; // 初始化为全1
    if (ql <= mid) res &= query(lson, l, mid, ql, qr);
    if (qr > mid) res &= query(rson, mid+1, r, ql, qr);
    return res;
}
```

---

**总结**：线段树通过区间或和按位与查询直接满足题意，差分方法则通过逐位处理优化空间。两种方法均需二次验证约束条件，确保构造的数组合法。

---
处理用时：65.87秒