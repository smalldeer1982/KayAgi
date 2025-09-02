# 题目信息

# Kefa and Watch

## 题目描述

One day Kefa the parrot was walking down the street as he was on the way home from the restaurant when he saw something glittering by the road. As he came nearer he understood that it was a watch. He decided to take it to the pawnbroker to earn some money.

The pawnbroker said that each watch contains a serial number represented by a string of digits from $ 0 $ to $ 9 $ , and the more quality checks this number passes, the higher is the value of the watch. The check is defined by three positive integers $ l $ , $ r $ and $ d $ . The watches pass a check if a substring of the serial number from $ l $ to $ r $ has period $ d $ . Sometimes the pawnbroker gets distracted and Kefa changes in some substring of the serial number all digits to $ c $ in order to increase profit from the watch.

The seller has a lot of things to do to begin with and with Kefa messing about, he gave you a task: to write a program that determines the value of the watch.

Let us remind you that number $ x $ is called a period of string $ s $ ( $ 1<=x<=|s| $ ), if $ s_{i}=s_{i+x} $ for all $ i $ from 1 to $ |s|-x $ .

## 说明/提示

In the first sample test two checks will be made. In the first one substring "12" is checked on whether or not it has period 1, so the answer is "NO". In the second one substring "88", is checked on whether or not it has period 1, and it has this period, so the answer is "YES".

In the second statement test three checks will be made. The first check processes substring "3493", which doesn't have period 2. Before the second check the string looks as "334334", so the answer to it is "YES". And finally, the third check processes substring "8334", which does not have period 1.

## 样例 #1

### 输入

```
3 1 2
112
2 2 3 1
1 1 3 8
2 1 2 1
```

### 输出

```
NO
YES
```

## 样例 #2

### 输入

```
6 2 3
334934
2 2 5 2
1 4 4 3
2 1 6 3
1 2 3 8
2 3 6 1
```

### 输出

```
NO
YES
NO
```

# AI分析结果



**算法分类**  
线段树 + 字符串哈希

---

### **题解思路、算法要点与解决难点**

1. **核心结论**  
   判断子串 `[l, r]` 是否存在周期 `d`，只需比较 `[l, r-d]` 与 `[l+d, r]` 是否相等。  
   - **数学推导**：若每个字符满足 `s[i] = s[i+d]`，则错位后的两段子串必然完全相同。

2. **数据结构选择**  
   - **线段树**：支持区间赋值与区间哈希查询。  
   - **哈希优化**：通过预处理 `base` 的幂次和前 `k` 项和，快速计算区间哈希值。

3. **关键实现难点**  
   - **哈希合并**：左子树的哈希值需乘 `base^右子树长度` 后与右子树哈希相加。  
   - **懒标记处理**：区间赋值时，哈希值需更新为 `c * Σ(base^i)`，利用预处理的 `sp` 数组优化计算。  
   - **双哈希防碰撞**：部分题解使用双模数或双哈希避免自然溢出导致错误。

---

### **题解评分 (≥4星)**

1. **作者：子归 (5星)**  
   - **亮点**：详细推导哈希合并逻辑，代码结构清晰，预处理 `sp` 数组优化效率。  
   - **代码片段**：  
     ```cpp
     void pushup(int x) {
         kano[x].h = (kano[x<<1].h * Pow[kano[x<<1|1].r - kano[x<<1|1].l + 1] + kano[x<<1|1].h) % mod;
     }
     ```

2. **作者：FriedrichC (5星)**  
   - **亮点**：数学归纳法证明循环节结论，注释详细，双哈希实现严谨。  
   - **代码片段**：  
     ```cpp
     ull ask(int p, int l, int r) {
         if (l > r) return 0;
         if (l <= l(p) && r >= r(p)) return h(p);
         spread(p);
         // 分治合并哈希值
     }
     ```

3. **作者：顾z (4星)**  
   - **亮点**：简化线段树结构，预处理 `val` 数组优化区间赋值，代码可读性强。  
   - **代码片段**：  
     ```cpp
     inline void Upd(int u, int v) {
         tr[u].h = v * sp[tr[u].len] % mod;
     }
     ```

---

### **最优思路或技巧提炼**

1. **循环节判断公式**  
   `s[l..r-d] == s[l+d..r]` 是核心结论，避免暴力检查每个字符。

2. **哈希合并的数学表达**  
   - 左子树哈希 `h_left` 需乘 `base^len_right`，再与右子树哈希 `h_right` 相加。

3. **区间赋值的哈希计算**  
   - 预处理 `sp[i] = base^0 + base^1 + ... + base^(i-1)`，快速计算全相同字符的哈希值。

---

### **同类型题推荐**

1. **CF633C**  
   - 利用哈希处理字符串匹配与动态拼接。

2. **P3370 字符串哈希**  
   - 基础哈希应用，判断不同字符串的唯一性。

3. **P3372 线段树区间修改**  
   - 线段树基础操作，理解区间更新与懒标记。

---

### **可视化与算法演示**

1. **像素化线段树动画**  
   - **Canvas 绘制**：线段树节点显示区间范围及哈希值，懒标记用红色高亮。  
   - **颜色标记**：修改区间时，该区间变为黄色；查询时，比较的子串区域闪烁蓝色。  
   - **音效**：赋值操作播放“滴”声，查询成功播放“叮咚”声，失败播放“嘟”声。

2. **复古游戏界面**  
   - **8位风格**：绿色背景网格，线段树节点用像素方块表示，哈希值以16进制显示。  
   - **自动演示模式**：按空格键逐步执行操作，ESC键切换自动/手动模式。

---

### **代码实现（核心逻辑）**

```cpp
// 线段树节点结构体
struct Node {
    int l, r, lazy;
    ull hash;
};

// 预处理 sp 数组
sp[0] = 1;
for (int i = 1; i <= n; i++) {
    sp[i] = (sp[i-1] * base + 1) % mod;
}

// 线段树合并哈希
void pushup(int p) {
    int len_r = tree[rs].r - tree[rs].l + 1;
    tree[p].hash = (tree[ls].hash * pow_base[len_r] + tree[rs].hash) % mod;
}

// 区间赋值
void update(int p, int l, int r, int val) {
    if (覆盖当前区间) {
        tree[p].hash = val * sp[tree[p].r - tree[p].l + 1] % mod;
        tree[p].lazy = val;
        return;
    }
    // 递归更新子节点
}
```

---

**总结**：线段树维护哈希值结合数学结论是本题的最优解，兼顾效率与正确性。复古像素动画可直观展示哈希合并与懒标记传递过程，增强学习趣味性。

---
处理用时：76.56秒