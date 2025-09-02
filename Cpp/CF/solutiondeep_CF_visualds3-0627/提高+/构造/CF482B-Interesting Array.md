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



**唯一算法分类**：线段树/差分数组

---

### **综合分析与结论**

**核心思路**：  
本题需构造数组满足多个区间按位与约束。核心在于：  
1. **满足所有约束的“必须为1”的位**：通过区间或操作强制置1，确保按位与结果包含q的二进制1位。  
2. **验证约束的“必须存在0”的位**：检查处理后数组的区间按位与是否等于q，排除冲突。

**难点与解决方案**：  
- **高效区间操作**：线段树支持区间或修改和区间与查询，时间复杂度O(m log n)。  
- **逐位处理冲突**：差分数组逐位统计必须置1的区间，再通过前缀和检查0位是否合法，时间复杂度O(30n)。

**可视化设计**：  
- **线段树操作动画**：  
  - **颜色标记**：区间或操作时高亮对应区间，绿色表示置1的位，红色表示验证时的冲突区间。  
  - **步进控制**：分步展示每个约束的修改与验证，动态显示线段树节点状态和懒标记下推。  
- **差分数组演示**：  
  - **逐位显示**：按二进制位分层展示差分数组的前缀和过程，红色高亮必须全1的区间。  
  - **冲突检测**：用闪烁提示某一位的非法全1情况。

---

### **题解清单 (≥4星)**

1. **TKXZ133（4.5星）**  
   - **亮点**：结构体封装线段树，代码清晰易读，支持区间或和区间与查询。  
   - **关键代码**：维护`sum`（区间与值）和`t`（懒标记），通过`or_all`和`and_all`实现核心逻辑。

2. **CaiXY06（4星）**  
   - **亮点**：差分逐位处理，节省空间，逻辑简洁。  
   - **关键代码**：用差分数组标记必1位，前缀和验证0位合法性。

3. **ljc20020730（4星）**  
   - **亮点**：差分前缀和优化，时间复杂度O(n log n)，代码高效。  
   - **关键代码**：对每bit单独处理，`c[i][j]`记录差分，`s[i]`统计0位数量。

---

### **最优思路提炼**

**线段树核心逻辑**：  
```cpp
void modify(int u, int l, int r, int ql, int qr, int k) {
    if (ql <= l && r <= qr) {
        tree[u] |= k;  // 区间或操作
        lazy[u] |= k;
        return;
    }
    push_down(u);
    int mid = (l + r) >> 1;
    if (ql <= mid) modify(lson, l, mid, ql, qr, k);
    if (qr > mid) modify(rson, mid+1, r, ql, qr, k);
    push_up(u);
}

int query(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[u];
    push_down(u);
    int mid = (l + r) >> 1, res = (1<<30)-1;
    if (ql <= mid) res &= query(lson, l, mid, ql, qr);
    if (qr > mid) res &= query(rson, mid+1, r, ql, qr);
    return res;
}
```

**差分数组核心逻辑**：  
```cpp
for (int bit = 0; bit <= 30; bit++) {
    memset(diff, 0, sizeof(diff));
    // 标记必须为1的区间
    for (auto &q : queries) {
        if (q.val & (1 << bit)) {
            diff[q.l]++;
            diff[q.r + 1]--;
        }
    }
    // 计算前缀和
    for (int i = 1; i <= n; i++) {
        diff[i] += diff[i-1];
        if (diff[i] > 0) a[i] |= (1 << bit);
    }
    // 检查0位冲突
    for (auto &q : queries) {
        if (!(q.val & (1 << bit)) && (区间全1)) return false;
    }
}
```

---

### **同类型题与算法套路**

- **区间更新+验证**：如[CF817F](https://codeforces.com/problemset/problem/817/F)（动态区间统计）。  
- **位运算+差分**：[洛谷P5057](https://www.luogu.com.cn/problem/P5057)（位操作与异或前缀和）。  
- **线段树复杂操作**：[洛谷P3373](https://www.luogu.com.cn/problem/P3373)（乘加混合标记下推）。

---

### **推荐题目**

1. **P3372** - 线段树区间加和查询（基础线段树）。  
2. **P5490** - 扫描线求矩形面积并（复杂区间操作）。  
3. **P2574** - 异或操作与区间翻转（位运算与线段树结合）。

---

### **个人心得摘录**

- **wanggk**：调试中发现懒标记未及时下推，导致查询结果错误，强调`pushdown`的必要性。  
- **CaiXY06**：通过逐位处理避免线段树的复杂维护，顿悟“分治每一位”的简洁性。  
- **Styx**：初始暴力建30棵线段树TLE，改用压位后代码量减半。

---

### **可视化与复古游戏设计**

**像素动画设计**：  
- **Canvas 网格**：每个单元格表示数组元素，颜色深浅表示二进制位的1/0。  
- **操作高亮**：线段树区间修改时，对应区间闪烁黄色；验证时非法区间闪烁红色。  
- **音效**：  
  - **置1操作**：8-bit “哔”声；  
  - **验证成功**：胜利音效；  
  - **冲突**：低沉错误音。  

**自动演示模式**：  
```javascript
function autoPlay() {
    for (let q of queries) {
        highlightInterval(q.l, q.r, 'yellow');
        modifySegmentTree(q);
        playSound('beep');
        wait(500);
    }
    for (let q of queries) {
        if (checkConflict(q)) {
            flashRed(q.l, q.r);
            playSound('error');
            return;
        }
    }
    showSuccessAnimation();
}
```

---
处理用时：97.48秒