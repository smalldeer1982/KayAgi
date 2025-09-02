# 题目信息

# Wine Factory (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ c_i $ and $ z $ . You can make hacks only if both versions of the problem are solved.

There are three arrays $ a $ , $ b $ and $ c $ . $ a $ and $ b $ have length $ n $ and $ c $ has length $ n-1 $ . Let $ W(a,b,c) $ denote the liters of wine created from the following process.

Create $ n $ water towers. The $ i $ -th water tower initially has $ a_i $ liters of water and has a wizard with power $ b_i $ in front of it. Furthermore, for each $ 1 \le i \le n - 1 $ , there is a valve connecting water tower $ i $ to $ i + 1 $ with capacity $ c_i $ .

For each $ i $ from $ 1 $ to $ n $ in this order, the following happens:

1. The wizard in front of water tower $ i $ removes at most $ b_i $ liters of water from the tower and turns the removed water into wine.
2. If $ i \neq n $ , at most $ c_i $ liters of the remaining water left in water tower $ i $ flows through the valve into water tower $ i + 1 $ .

There are $ q $ updates. In each update, you will be given integers $ p $ , $ x $ , $ y $ and $ z $ and you will update $ a_p := x $ , $ b_p := y $ and $ c_p := z $ . After each update, find the value of $ W(a,b,c) $ . Note that previous updates to arrays $ a $ , $ b $ and $ c $ persist throughout future updates.

## 说明/提示

The first update does not make any modifications to the arrays.

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 5 $ liters of water in tower 2 and $ 4 $ liters of water is turned into wine. The remaining $ 1 $ liter of water flows into tower 3.
- When $ i = 3 $ , there are $ 4 $ liters of water in tower 3 and $ 2 $ liters of water is turned into wine. The remaining $ 2 $ liters of water flows into tower 4.
- When $ i = 4 $ , there are $ 5 $ liters of water in tower 4. All $ 5 $ liters of water are turned into wine.

Hence, $ W(a,b,c)=1 + 4 + 2 + 5 = 12 $ after the first update.

The second update modifies the arrays to $ a = [3, 5, 3, 3] $ , $ b = [1, 1, 2, 8] $ , and $ c = [10^{18}, 10^{18}, 10^{18}] $ .

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 7 $ liters of water in tower 2 and $ 1 $ liter of water is turned into wine. The remaining $ 6 $ liters of water flow into tower 3.
- When $ i = 3 $ , there are $ 9 $ liters of water in tower 3 and $ 2 $ liters of water is turned into wine. The remaining $ 7 $ liters of water flow into tower 4.
- When $ i = 4 $ , there are $ 10 $ liters of water in tower 4. Only $ 8 $ liters of water is turned into wine.

Hence, $ W(a,b,c)=1 + 1 + 2 + 8 = 12 $ after the second update.

The third update modifies the arrays to $ a = [3, 5, 0, 3] $ , $ b = [1, 1, 0, 8] $ , and $ c = [10^{18}, 10^{18}, 10^{18}] $ .

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 7 $ liters of water in tower 2 and $ 1 $ liter of water is turned into wine. The remaining $ 6 $ liters of water flow into tower 3.
- When $ i = 3 $ , there are $ 6 $ liters of water in tower 3 and $ 0 $ liters of water is turned into wine. The remaining $ 6 $ liters of water flow into tower 4.
- When $ i = 4 $ , there are $ 9 $ liters of water in tower 4. Only $ 8 $ liters of water is turned into wine.

Hence, $ W(a,b,c)=1 + 1 + 0 + 8 = 10 $ after the third update.

## 样例 #1

### 输入

```
4 3
3 3 3 3
1 4 2 8
1000000000000000000 1000000000000000000 1000000000000000000
4 3 8 1000000000000000000
2 5 1 1000000000000000000
3 0 0 1000000000000000000```

### 输出

```
12
12
10```

## 样例 #2

### 输入

```
5 5
10 3 8 9 2
3 4 10 8 1
1000000000000000000 1000000000000000000 1000000000000000000 1000000000000000000
5 4 9 1000000000000000000
1 1 1 1000000000000000000
2 7 4 1000000000000000000
4 1 1 1000000000000000000
1 8 3 1000000000000000000```

### 输出

```
34
25
29
21
27```

# AI分析结果



---

### **唯一算法分类**
线段树

---

### **题解思路与算法要点**
在Easy Version中，所有阀门容量极大，剩余水可完全传递。总酒量等于所有巫师法力总和减去水的浪费量。浪费量由前缀和最小值决定：

1. **数学推导**  
   每个塔处理后，剩余水传递到下一个塔。总酒量等于初始总水量（`sum(a)`）减去最终剩余水量。通过推导，最终剩余水量为 `max(0, sum_total - min_prefix)`，其中 `sum_total = sum(a_i - b_i)`，`min_prefix` 是前缀和的最小值（含初始0）。

2. **线段树维护**  
   用线段树维护 `a_i - b_i` 的前缀和最小值。每个节点存储区间和 `sum` 与最小前缀和 `ans`。合并时，父节点的 `ans` 是左右子节点 `ans` 的最小值或左子节点 `sum` 加右子节点 `ans` 的最小值。

3. **动态更新**  
   每次更新 `a[p]` 或 `b[p]` 时，修改线段树对应位置的值，并重新计算前缀和最小值。总酒量公式为 `sum(b_i) + min(0, min_prefix)`。

---

### **题解评分 (≥4星)**
1. **sunnygreen (5星)**  
   - **思路清晰**：推导简洁，利用前缀和最小值直接计算浪费量。  
   - **代码高效**：线段树实现维护前缀和的最小值，支持单点更新和全局查询。  
   - **关键代码**：线段树节点合并逻辑清晰。

2. **LKY928261 (4星)**  
   - **函数化思路**：用线段树维护剩余水量的转移函数，动态合并区间操作。  
   - **创新点**：通过矩阵乘法合并区间转移函数，直观展示水流传递过程。

3. **dxbt (4星)**  
   - **简化推导**：直接维护前缀和的最大值，代码简洁。  
   - **可读性高**：线段树实现区间修改和查询，逻辑简明。

---

### **最优思路提炼**
- **核心公式**：总酒量 = `sum(b_i) + min(0, 前缀和最小值)`。  
- **线段树优化**：维护区间前缀和的最小值，合并时考虑左子区间对右子区间的影响。  
- **动态更新**：每次单点修改后，仅需更新相关线段树节点。

---

### **同类型题与算法套路**
- **前缀和极值维护**：如最大子段和、滑动窗口最小值。  
- **动态区间查询**：线段树或树状数组维护区间属性（和、极值）。  
- **矩阵结合律优化**：将递推转化为矩阵乘法，利用结合律加速（如斐波那契数列）。

---

### **推荐题目**
1. **P3372 线段树1**（模板题，区间和查询与更新）  
2. **P4513 小白逛公园**（动态维护区间最大子段和）  
3. **P5490 扫描线**（线段树在几何问题中的应用）

---

### **可视化算法演示**
**步骤动画设计**：  
1. **初始状态**：显示所有塔的 `a_i` 和 `b_i`，水流传递方向。  
2. **线段树更新**：高亮修改的塔，展示线段树节点从叶子到根的更新路径。  
3. **前缀和计算**：动态绘制前缀和折线图，标记当前最小值。  
4. **最终结果**：显示总酒量公式中的各组成部分（`sum(b_i)` 和 `min_prefix`）。

**复古像素风格**：  
- **颜色方案**：绿色表示 `a_i`，红色表示 `b_i`，蓝色表示剩余水。  
- **音效**：线段树更新时播放“滴答”声，计算完成时播放胜利音效。  
- **自动演示**：模拟水流传递过程，自动步进展示每个塔的处理步骤。

---

### **代码实现（关键片段）**
```cpp
// 线段树节点结构（sunnygreen题解）
struct node {
    lr sum, ans; // 区间和与最小前缀和
    node operator+(const node &b) const {
        return {sum + b.sum, min(ans, sum + b.ans)};
    }
} tr[N << 2];

// 线段树更新
void Modify(int k, int l, int r, int x, int v) {
    if (l == r) {
        tr[k] = {v, min(v, 0)}; // 单点修改
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) Modify(ls, x, v);
    else Modify(rs, x, v);
    tr[k] = tr[k<<1] + tr[k<<1|1]; // 合并子节点
}

// 总酒量计算
cout << Min(0ll, tr[1].ans) + sumb << '\n';
```

---

### **个人心得摘录**
- **推导陷阱**：初始认为总剩余等于前缀和最大值，实际需结合水流传递特性重新推导。  
- **线段树合并**：通过合并左右子区间的最小前缀和，确保全局最优解。  
- **边界处理**：前缀和需包含初始0，避免遗漏初始状态。

---
处理用时：260.64秒