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



# Ardent Flames

## 题目描述

你获得了新限定角色 Xilonen，准备用她战斗。战场上有 $n$ 个排成一列的敌人，第 $i$ 个敌人的血量为 $h_i$，坐标为 $x_i$。Xilonen 的攻击伤害为 $m$。

Xilonen 的"践踏"攻击机制如下：选定一个整数位置 $p$ 后，每次攻击会对 $p$ 周围敌人造成递减伤害。具体来说，距离 $p$ 为 $d$ 的敌人受到 $\max(0, m-d)$ 点伤害。要求找出一个 $p$，使得击败至少 $k$ 个敌人所需的最少攻击次数最小。若无法满足条件，输出 $-1$。

## 样例说明

样例 1 中选择 $p=2$，两次攻击可击败前三个敌人。样例 3 中因无法同时攻击两个敌人返回 $-1$。

---

## 题解分析与结论

所有题解均采用**二分答案+区间覆盖判断**的核心思路：

1. **二分攻击次数**：答案具有单调性，攻击次数越多，击败敌人的可能性越大。
2. **区间转换**：将每个敌人转换为能被击败的 $p$ 值区间 $[x_i - (m-\lceil h_i/t \rceil), x_i + (m-\lceil h_i/t \rceil)]$。
3. **扫描线判断**：将所有区间端点视为事件点排序，通过前缀和统计覆盖次数，判断是否存在覆盖 $k$ 次的点。

### 精选题解

#### 题解1：1234567890sjx （★★★★☆）
**亮点**：代码结构清晰，直接用事件点排序处理，无需离散化。
```cpp
int check(int mid) {
    vector<pair<int, int>> event;
    for (每个敌人) {
        int pwk = (h[i] + mid - 1) / mid; // 计算需要的最小伤害次数
        if (pwk <= m) { // 可被击败
            int L = x[i] - (m - pwk), R = x[i] + (m - pwk);
            event.emplace_back(L, 1);    // 区间开始
            event.emplace_back(R + 1, -1); // 区间结束
        }
    }
    sort(event.begin(), event.end()); // 按坐标排序
    int pref = 0;
    for (遍历事件) {
        pref += 事件值;
        if (pref >= k) return 1;
    }
    return 0;
}
```

#### 题解2：zhouruoheng （★★★★☆）
**亮点**：使用离散化处理大范围坐标，减少内存消耗。
```cpp
bool check(int q) {
    vector<int> events;
    for (每个敌人) {
        int t = (h[i] + q - 1) / q;
        if (t > m) continue;
        int l = x[i] - (m - t), r = x[i] + (m - t);
        events.push_back(l);     // 离散化处理
        events.push_back(r + 1);
    }
    // 离散化后差分统计覆盖次数
}
```

#### 题解3：Melo_DDD （★★★★☆）
**亮点**：事件处理逻辑简洁，直接双端队列排序。
```cpp
bool check(ll q) {
    deque<int> p, q; // 分别存储区间起点和终点+1
    for (每个敌人) {
        ll dmg = ceil(h[i], q);
        p.push_back(x[i] - (m - dmg));
        q.push_back(x[i] + (m - dmg) + 1);
    }
    sort(p); sort(q);
    while (双队列非空) { // 类似归并排序的合并过程
        // 统计当前覆盖数
    }
}
```

---

## 关键思路总结
1. **二分框架**：将最优化问题转化为判定问题。
2. **区间转换公式**：$\lceil h_i/t \rceil$ 表示每次攻击至少需要造成的伤害，推导出位置区间。
3. **扫描线优化**：通过事件点排序和前缀和，将区间覆盖问题的时间复杂度降至 $O(n \log n)$。

---

## 相似题目推荐
1. [P3740 静态区间覆盖](https://www.luogu.com.cn/problem/P3740) - 区间覆盖统计
2. [P1904 天际线](https://www.luogu.com.cn/problem/P1904) - 扫描线处理重叠区间
3. [CF817F MEX Queries](https://codeforces.com/problemset/problem/817/F) - 动态区间覆盖与查询

---
处理用时：56.20秒