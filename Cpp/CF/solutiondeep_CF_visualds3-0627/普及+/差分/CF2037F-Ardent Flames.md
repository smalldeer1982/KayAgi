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



**唯一算法分类**：二分答案 + 扫描线

---

### **题解思路与核心难点**
- **核心思路**：二分攻击次数，每次判断是否存在位置 `p` 使得至少 `k` 个敌人被击败。对于每个攻击次数 `mid`，计算每个敌人能被击败的区间 `[x_i - len, x_i + len]`，转化为区间覆盖问题。
- **解决难点**：如何快速判断多个区间是否存在至少覆盖 `k` 次的点。通过扫描线算法（差分+排序）处理所有区间的起点和终点，维护当前覆盖次数。
- **关键变量**：
  - `len = m - ceil(h_i / mid)`：敌人 `i` 允许的位置区间半长。
  - 事件点：每个区间的起点 `+1`，终点后一位 `-1`。
- **数据结构**：事件点用 `vector<pair<int, int>>` 存储，排序后扫描前缀和。

---

### **题解评分**
1. **1234567890sjx（4星）**  
   - **亮点**：代码结构清晰，事件点处理简洁，逻辑完整。
2. **AtomAlpaca（4星）**  
   - **亮点**：使用双队列分别处理起点和终点，优化事件扫描。
3. **Melo_DDD（4星）**  
   - **亮点**：代码可读性强，逻辑分步明确，注释详细。

---

### **最优思路提炼**
1. **二分框架**：攻击次数具有单调性，最小次数通过二分确定。
2. **区间转换**：将每个敌人的击败条件转化为 `p` 的可行区间。
3. **扫描线算法**：将区间拆分为事件点，排序后扫描求最大覆盖次数。

**关键公式**：  
对敌人 `i`，其可行区间为：  
`[x_i - (m - ceil(h_i / mid)), x_i + (m - ceil(h_i / mid))]`  
若 `ceil(h_i / mid) > m`，则无法击败。

---

### **同类型题与算法套路**
- **同类问题**：区间覆盖问题（如会议室安排、最大重叠区间）。
- **通用解法**：二分答案 + 扫描线/差分数组判断可行性。

---

### **推荐题目**
1. **P1886 滑动窗口**（区间覆盖与极值）  
2. **CF817F MEX Queries**（扫描线处理动态区间）  
3. **P3740 贴海报**（区间覆盖与离散化）

---

### **代码片段（核心逻辑）**
```cpp
bool check(int mid) {
    vector<pair<int, int>> events;
    for (int i = 0; i < n; ++i) {
        int dmg = (h[i] + mid - 1) / mid; // 向上取整
        if (dmg > m) continue;
        int len = m - dmg;
        int L = x[i] - len, R = x[i] + len;
        events.emplace_back(L, 1);
        events.emplace_back(R + 1, -1);
    }
    sort(events.begin(), events.end());
    int cnt = 0, max_cnt = 0;
    for (auto [pos, val] : events) {
        cnt += val;
        max_cnt = max(max_cnt, cnt);
    }
    return max_cnt >= k;
}
```

---

### **可视化设计**
- **像素风格动画**：  
  - **Canvas 绘制**：敌人显示为红色方块，可行区间为绿色线段，扫描线为黄色竖线。  
  - **音效**：扫描线移动时播放“滴”声，覆盖次数达到 `k` 时播放胜利音效。  
  - **自动演示**：按二分步骤逐步展示 `mid` 值变化，每次 `check` 时动态生成区间并扫描。  
  - **交互控制**：支持暂停/继续，调节动画速度，高亮当前覆盖次数。

**示例动效**：  
1. 初始化显示所有敌人位置和血量。  
2. 二分过程中，显示当前 `mid` 值和对应区间生成。  
3. 扫描线移动时，实时显示覆盖次数，达到 `k` 时区域闪烁。

---
处理用时：55.68秒