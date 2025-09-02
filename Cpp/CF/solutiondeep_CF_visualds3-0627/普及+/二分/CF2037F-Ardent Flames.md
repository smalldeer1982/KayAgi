# 题目信息

# Ardent Flames

## 题目描述

You have obtained the new limited event character Xilonen. You decide to use her in combat.

There are $ n $ enemies in a line. The $ i $ 'th enemy from the left has health $ h_i $ and is currently at position $ x_i $ . Xilonen has an attack damage of $ m $ , and you are ready to defeat the enemies with her.

Xilonen has a powerful "ground stomp" attack. Before you perform any attacks, you select an integer $ p $ and position Xilonen there ( $ p $ can be any integer position, including a position with an enemy currently). Afterwards, for each attack, she deals $ m $ damage to an enemy at position $ p $ (if there are any), $ m-1 $ damage to enemies at positions $ p-1 $ and $ p+1 $ , $ m-2 $ damage to enemies at positions $ p-2 $ and $ p+2 $ , and so on. Enemies that are at least a distance of $ m $ away from Xilonen take no damage from attacks.

Formally, if there is an enemy at position $ x $ , she will deal $ \max(0,m - |p - x|) $ damage to that enemy each hit. Note that you may not choose a different $ p $ for different attacks.

Over all possible $ p $ , output the minimum number of attacks Xilonen must perform to defeat at least $ k $ enemies. If it is impossible to find a $ p $ such that eventually at least $ k $ enemies will be defeated, output $ -1 $ instead. Note that an enemy is considered to be defeated if its health reaches $ 0 $ or below.

## 说明/提示

In the first testcase, it is optimal to select $ p=2 $ . Each attack, the first enemy takes $ 5-|2-1|=4 $ damage, the second enemy takes $ 5 $ damage, the third enemy takes $ 4 $ damage, the fourth enemy takes $ 3 $ damage, and the fifth enemy takes $ 2 $ damage. After $ 2 $ attacks, the first three enemies will be defeated. It can be shown that it is impossible to defeat $ 3 $ enemies in less than $ 2 $ attacks, no matter which $ p $ is selected.

In the second testcase, we must kill all $ 9 $ enemies. By selecting $ p=5 $ , all nine enemies will be defeated in $ 2 $ attacks.

In the third testcase, we must kill both enemies. However, it can be shown that no $ p $ selected will damage both enemies at the same time, so the answer is $ -1 $ .

In the fourth testcase, selecting $ p=1 $ will enable us to defeat the first enemy in $ 6969697 $ attacks.

In the fifth testcase, selecting $ p=10 $ will make each enemy take $ 1 $ damage per attack. Both enemies will be defeated in $ 15 $ attacks.

## 样例 #1

### 输入

```
6
5 5 3
7 7 7 7 7
1 2 3 4 5
9 5 9
2 4 6 8 10 8 6 4 2
1 2 3 4 5 6 7 8 9
2 10 2
1 1
1 20
2 10 1
69696969 420420420
1 20
2 10 2
10 15
1 19
2 2 2
1000000000 1
1 3```

### 输出

```
2
2
-1
6969697
15
1000000000```

# AI分析结果



**算法分类**: 二分

---

### **题解思路与算法要点**
1. **核心思路**：  
   - **二分答案**：攻击次数越少，击败敌人难度越大，具有单调性。通过二分确定最小攻击次数 `t`。  
   - **区间覆盖问题**：对每个敌人，计算其能被击败的 `p` 的区间 `[x_i - len, x_i + len]`，其中 `len = m - ceil(h_i/t)`。  
   - **扫描线算法**：将所有区间的起点和终点作为事件点，排序后扫描，统计覆盖次数，判断是否存在覆盖≥k次的点。

2. **二分实现细节**：  
   - **初始区间**：`left=1`, `right=1e9`（最大可能攻击次数）。  
   - **收缩条件**：若当前 `mid` 可满足覆盖≥k次，收缩右边界；否则收缩左边界。  
   - **边界处理**：使用闭区间 `[left, right]`，循环条件 `left <= right`，避免死循环。

3. **解决难点**：  
   - **数学转换**：将攻击次数与位置关系转化为区间覆盖问题。  
   - **事件点排序**：相同位置时，结束事件（`-1`）优先处理，确保区间右端点正确性。

---

### **题解评分 (≥4星)**
1. **1234567890sjx (4.5星)**  
   - **亮点**：代码简洁，事件处理清晰，排序逻辑正确，边界处理完整。  
   - **引用**：“扫描线”思路直接解决覆盖问题。

2. **Melo_DDD (4星)**  
   - **亮点**：使用 `std::pair` 存储事件，代码可读性高，逻辑流畅。  
   - **引用**：“问题转化为古典 DS 题”简化复杂度。

3. **AtomAlpaca (4星)**  
   - **亮点**：离散化与差分结合，避免大范围坐标处理，优化空间复杂度。  

---

### **最优思路提炼**
1. **二分答案框架**：  
   - **循环条件**：`while (left <= right)` 确保完全覆盖所有可能值。  
   - **中间值计算**：`mid = (left + right) >> 1` 避免溢出。  
   - **收缩策略**：根据覆盖结果调整左右边界，优先缩小右边界以寻找最小值。

2. **区间事件处理**：  
   - **事件生成**：每个区间生成 `(L, +1)` 和 `(R+1, -1)` 事件。  
   - **排序规则**：按坐标升序，相同坐标时结束事件优先。

3. **数学转换技巧**：  
   - **伤害计算**：`ceil(h_i/t)` 等价于 `(h_i + t - 1) // t`。  
   - **无效区间过滤**：若 `m < ceil(h_i/t)`，跳过该敌人。

---

### **同类型题与算法套路**
- **通用二分答案模板**：  
  1. 确定单调性。  
  2. 设计 `check(mid)` 函数验证可行性。  
  3. 根据 `check` 结果收缩区间。  
- **类似题目**：  
  - **洛谷 P1873**（砍树找最大高度）  
  - **LeetCode 410**（分割数组最大值最小化）  
  - **Codeforces 689C**（二分桶容量）

---

### **可视化与算法演示**
**动画设计**：  
1. **二分过程**：  
   - **Canvas 网格**：横轴表示攻击次数区间 `[left, right]`，纵轴显示当前 `mid`。  
   - **颜色标记**：`mid` 用红色高亮，满足条件时区间变绿，否则变灰。  
   - **音效触发**：每次更新 `mid` 播放“点击”音效，找到答案时播放成功音效。  

2. **扫描线演示**：  
   - **事件点流动**：从左到右扫描事件点，覆盖次数动态变化。  
   - **覆盖高亮**：当覆盖次数≥k时，对应位置闪烁黄色。  

**复古风格实现**：  
- **8位像素网格**：坐标轴用像素块表示，事件点用不同颜色方块。  
- **自动演示模式**：AI按帧逐步展示二分收缩与扫描过程。  

---

### **代码片段**
```cpp
// 二分框架示例 (1234567890sjx 题解)
int l = 1, r = inf, best = -1;
while (l <= r) {
    int mid = l + r >> 1;
    vector<pair<int, int>> event;
    for (int i = 1; i <= n; ++i) {
        int pwk = (h[i] + mid - 1) / mid; // ceil(h_i/mid)
        if (pwk <= m) {
            int L = x[i] - (m - pwk), R = x[i] + (m - pwk);
            event.eb(L, 1), event.eb(R + 1, -1);
        }
    }
    sort(event.begin(), event.end(), [&](auto l, auto r) {
        return l.first < r.first || (l.first == r.first && l.second < r.second);
    });
    int pref = 0, ok = 0;
    for (auto &[pos, vx] : event) {
        pref += vx;
        if (pref >= k) { ok = 1; break; }
    }
    if (ok) best = mid, r = mid - 1;
    else l = mid + 1;
}
cout << best << '\n';
```

---

### **个人心得摘录**
> “**二分答案的关键在于设计高效的 `check` 函数**。本题通过区间覆盖的转换，将复杂的位置选择问题转化为经典的扫描线问题，极大简化了实现难度。” —— 1234567890sjx  

> “**离散化处理坐标**可以有效避免大范围数据的内存问题，差分数组则是统计覆盖次数的利器。” —— KaruAWA

---
处理用时：88.71秒