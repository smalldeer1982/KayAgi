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

### 题目中文重写
## 炽热火焰

### 题目描述
你获得了新的限定活动角色希洛嫩（Xilonen）。你决定让她参与战斗。

有 $n$ 个敌人排成一行。从左往右数第 $i$ 个敌人的生命值为 $h_i$，当前位于位置 $x_i$。希洛嫩的攻击伤害为 $m$，你准备用她击败这些敌人。

希洛嫩拥有强大的“大地践踏”攻击。在进行任何攻击之前，你选择一个整数 $p$ 并将希洛嫩放置在该位置（$p$ 可以是任意整数位置，包括当前有敌人的位置）。此后，每次攻击时，她会对位置 $p$ 处的敌人造成 $m$ 点伤害，对位置 $p - 1$ 和 $p + 1$ 处的敌人造成 $m - 1$ 点伤害，对位置 $p - 2$ 和 $p + 2$ 处的敌人造成 $m - 2$ 点伤害，依此类推。与希洛嫩距离至少为 $m$ 的敌人不会受到攻击伤害。

形式上，如果有一个敌人位于位置 $x$，她每次攻击会对该敌人造成 $\max(0, m - |p - x|)$ 点伤害。请注意，你不能为不同的攻击选择不同的 $p$。

对于所有可能的 $p$，输出希洛嫩为击败至少 $k$ 个敌人必须进行的最少攻击次数。如果无法找到一个 $p$ 使得最终至少有 $k$ 个敌人被击败，则输出 $-1$。注意，当一个敌人的生命值降至 $0$ 或更低时，该敌人被视为被击败。

### 说明/提示
在第一个测试用例中，最优选择是 $p = 2$。每次攻击时，第一个敌人受到 $5 - |2 - 1| = 4$ 点伤害，第二个敌人受到 $5$ 点伤害，第三个敌人受到 $4$ 点伤害，第四个敌人受到 $3$ 点伤害，第五个敌人受到 $2$ 点伤害。经过 $2$ 次攻击后，前三个敌人将被击败。可以证明，无论选择哪个 $p$，都不可能在少于 $2$ 次攻击内击败 $3$ 个敌人。

在第二个测试用例中，我们必须击败所有 $9$ 个敌人。选择 $p = 5$ 时，所有九个敌人将在 $2$ 次攻击内被击败。

在第三个测试用例中，我们必须击败两个敌人。然而，可以证明，无论选择哪个 $p$，都无法同时对两个敌人造成伤害，因此答案为 $-1$。

在第四个测试用例中，选择 $p = 1$ 将使我们能够在 $6969697$ 次攻击内击败第一个敌人。

在第五个测试用例中，选择 $p = 10$ 将使每个敌人每次攻击受到 $1$ 点伤害。两个敌人将在 $15$ 次攻击内被击败。

### 样例 #1
#### 输入
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
1 3
```

#### 输出
```
2
2
-1
6969697
15
1000000000
```

### 题解综合分析与结论
这些题解的核心思路均为二分查找最小攻击次数，通过二分枚举攻击次数，再检查该次数下是否存在一个位置 $p$ 能使至少 $k$ 个敌人被击败。

#### 算法要点
- **二分查找**：利用答案的单调性，不断缩小攻击次数的范围，找到最小的满足条件的攻击次数。
- **区间计算**：对于每个敌人，根据当前二分的攻击次数计算出能将其击败的位置 $p$ 的区间。
- **区间覆盖检查**：判断是否存在一个点被至少 $k$ 个区间覆盖，常见方法有扫描线算法和离散化差分。

#### 解决难点
- **区间计算**：根据攻击伤害公式和敌人生命值，推导出能击败敌人的位置区间。
- **区间覆盖检查**：高效地判断是否存在一个点被至少 $k$ 个区间覆盖，避免暴力枚举。

### 题解评分与选择
|作者|评分|亮点|
|----|----|----|
|1234567890sjx|4星|思路清晰，结合故事性描述，代码规范，详细说明了二分和扫描线的应用过程。|
|postpone|4星|思路简洁明了，代码简洁，复杂度分析清晰。|
|Melo_DDD|4星|思路清晰，对区间覆盖检查的原理进行了详细解释，代码可读性高。|

### 重点代码及核心思想
#### 1234567890sjx
```cpp
while (l <= r) {
    int mid = l + r >> 1;
    vector<pair<int, int>> event;
    for (int i = 1; i <= n; ++i) {
        int pwk = (h[i] + mid - 1) / mid;
        if (pwk <= m) {
            int L = x[i] - (m - pwk), R = x[i] + (m - pwk);
            event.eb(L, 1), event.eb(R + 1, -1);
        }
    }
    sort(event.begin(), event.end(), [&](auto l, auto r) {
        return l.first < r.first || l.first == r.first && l.second < r.second;
    });
    int pref = 0, ok = 0;
    for (auto &[pos, vx] : event) {
        if ((pref += vx) >= k) {
            ok = 1;
            break;
        }
    }
    if (ok) {
        best = mid, r = mid - 1;
    } else {
        l = mid + 1;
    }
}
```
核心思想：二分攻击次数，对于每个攻击次数，计算每个敌人能被击败的位置区间，将区间拆分为左右端点事件，排序后扫描，统计前缀和判断是否存在一个点被至少 $k$ 个区间覆盖。

#### postpone
```cpp
auto check = [&](int c) {
    vector<array<int, 2>> e;
    for (int i = 0; i < n; i++) {
        if (1ll * m * c < h[i]) {
            continue;
        }
        int d = (h[i] + c - 1) / c;
        int l = x[i] - m + d;
        int r = x[i] + m - d;
        e.push_back({l, 1});
        e.push_back({r + 1, -1});
    }
    ranges::sort(e);
    int s{};
    for (auto [_, i] : e) {
        s += i;
        if (s >= k) {
            return true;
        }
    }
    return false;
};

int lo = 0, hi = inf + 1;
while (lo < hi) {
    int mi = (lo + hi) / 2;
    if (check(mi)) {
        hi = mi;
    } else {
        lo = mi + 1;
    }
}
```
核心思想：定义检查函数，计算每个敌人能被击败的位置区间，将区间拆分为左右端点事件，排序后扫描，统计前缀和判断是否存在一个点被至少 $k$ 个区间覆盖。二分查找最小攻击次数。

#### Melo_DDD
```cpp
inline bool check (ll cur) {
    v.clear () ;
    f (i,1,n,1) {
        ll val = ceil (h[i],cur) ;
        if (val <= m) {
            v.emplace_back (std :: make_pair (x[i] - (m - val),1)) ;
            v.emplace_back (std :: make_pair (x[i] + (m - val) + 1,- 1)) ; 
        }
    }
    std :: sort (v.begin (), v.end ()) ;
    std :: vector < std :: pair < ll,ll > > :: iterator it ;
    static int tot ; tot = 0ll ;
    for (it = v.begin () ; it!= v.end () ; it ++) {
        tot += it -> second ;
        if (tot >= k) return true ;
    }
    return false ;
} 
ll l = 1ll, r = (ll) 1e9, ans = 0ll ;
while (l <= r) {
    if (check (mid)) r = (ans = mid) - 1 ;
    else l = mid + 1 ;
}
```
核心思想：定义检查函数，计算每个敌人能被击败的位置区间，将区间拆分为左右端点事件，排序后扫描，统计前缀和判断是否存在一个点被至少 $k$ 个区间覆盖。二分查找最小攻击次数。

### 最优关键思路与技巧
- **二分查找**：利用答案的单调性，将求解最小攻击次数的问题转化为判定性问题，降低时间复杂度。
- **扫描线算法**：将区间覆盖问题转化为对区间端点的扫描，通过维护前缀和高效判断是否存在一个点被至少 $k$ 个区间覆盖。

### 可拓展之处
同类型题或类似算法套路：
- 区间覆盖问题：如线段覆盖、区间选点等问题，可使用扫描线算法或离散化差分解决。
- 二分查找应用：在具有单调性的问题中，可通过二分查找将求解问题转化为判定性问题。

### 洛谷相似题目推荐
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：二分查找答案，检查可行性。
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：二分查找最小跳跃距离，检查可行性。
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：二分查找最大间距，检查可行性。

### 个人心得摘录与总结
- **1234567890sjx**：作者以故事形式描述解题过程，提到看到题目时的惊慌，冷静思考后发现是二分题目，在解决区间覆盖问题时得到班花提示使用扫描线算法，最后成功解题，但最后发现是一场梦，反映出作者在解题过程中的心态变化和对题目的思考过程。

---
处理用时：56.10秒