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



【题目翻译】
# 炽热之焰

## 题目描述

你获得了新限定活动角色希洛宁，并决定在战斗中使用她。

战场上有 $n$ 个排成一列的敌人，从左数第 $i$ 个敌人拥有生命值 $h_i$ 且当前位于坐标 $x_i$。希洛宁的攻击伤害为 $m$，你准备用她来击败敌人。

希洛宁拥有强大的"地裂践踏"技能。在发起任何攻击前，你需要选择一个整数坐标 $p$ 作为她的站位（$p$ 可以是任意整数坐标，包括已有敌人的位置）。此后每次攻击，她会：
- 对位于 $p$ 的敌人造成 $m$ 点伤害
- 对 $p-1$ 和 $p+1$ 位置的敌人造成 $m-1$ 点伤害
- 对 $p-2$ 和 $p+2$ 位置的敌人造成 $m-2$ 点伤害
- 依此类推，距离超过 $m$ 的敌人不受伤害

形式化地说，位于坐标 $x$ 的敌人每次受到 $\max(0, m - |p - x|)$ 点伤害。注意不同攻击中 $p$ 不可改变。

求在所有可能的 $p$ 中选择时，希洛宁击败至少 $k$ 个敌人所需的最小攻击次数。若不存在这样的 $p$，输出 $-1$（敌人生命值 ≤0 即视为击败）。

---

### 综合题解分析
各题解核心思路一致：**二分攻击次数**，转化为**区间覆盖问题**。关键步骤：
1. **二分框架**：确定答案的单调性（攻击次数越多越可能满足条件）
2. **区间计算**：对每个敌人计算可击败它的位置区间
3. **覆盖检测**：使用扫描线或差分数组判断是否存在被至少k个区间覆盖的点

### 精选题解

#### 1. 作者：1234567890sjx（⭐⭐⭐⭐⭐）
**核心亮点**：
- 清晰的扫描线实现，事件点处理高效
- 正确处理区间端点顺序（同坐标时+1事件优先）
- 代码简洁，逻辑连贯

**关键代码**：
```cpp
int best = -1;
while (l <= r) {
    int mid = (l + r) >> 1;
    vector<pair<int, int>> event;
    for (每个敌人) {
        int 所需次数 = ceil(血量/mid);
        if (所需次数 <= m) {
            生成区间事件 [L, R]
            event添加(L, +1) 和 (R+1, -1)
        }
    }
    sort(event); // 按坐标排序，同坐标时+1优先
    int 覆盖数 = 0, 是否满足 = 0;
    for (事件 : event) {
        覆盖数 += 事件.second;
        if (覆盖数 >= k) { 满足条件; break; }
    }
    if (满足) 更新最优解
}
```

#### 2. 作者：AtomAlpaca（⭐⭐⭐⭐）
**核心亮点**：
- 使用双队列处理事件点，避免全排序
- 代码结构简洁，包含重要注释

**关键优化**：
```cpp
std::deque<int> p, q; // 存储区间端点
std::sort(p); std::sort(q);
// 双指针扫描，线性复杂度
while (!p.empty() && !q.empty()) {
    if (p.front() < q.front()) 处理左端点 
    else 处理右端点
    维护当前覆盖数
}
```

#### 3. 作者：Melo_DDD（⭐⭐⭐⭐）
**核心亮点**：
- 完整处理离散化过程
- 包含详细边界条件注释

**关键实现**：
```cpp
// 离散化处理
tot = unique(c+1,c+tot+1) - c - 1; 
for (每个区间) {
    l = lower_bound找到离散化后的左端点
    r = lower_bound找到离散化后的右端点+1
    差分数组b[l]++, b[r]-- 
}
前缀和统计覆盖数
```

---

### 最优解法总结
**关键步骤**：
1. **二分攻击次数**：在 [1, 1e9] 范围内二分
2. **区间生成**：对每个敌人计算 $d = \lceil h_i / mid \rceil$，生成有效区间 $[x_i - (m-d), x_i + (m-d)]$
3. **区间覆盖检测**：
   - **方法1**（推荐）：生成 (L,+1) 和 (R+1,-1) 事件点，排序后扫描统计
   - **方法2**：离散化坐标后用差分数组统计

**易错点**：
- 计算 $d$ 时必须向上取整（使用 `(h + mid -1) / mid`）
- 处理相同坐标的事件点时，+1事件需优先处理
- 排除 $d > m$ 的无效区间

---

### 拓展练习
1. [CF689D - Friends and Subsequences](https://codeforces.com/problemset/problem/689/D)（二分+区间匹配）
2. [P1712 [NOI2016] 区间](https://www.luogu.com.cn/problem/P1712)（扫描线经典题）
3. [CF1029D Concatenated Multiples](https://codeforces.com/problemset/problem/1029/D)（预处理+区间统计）

---
处理用时：57.44秒