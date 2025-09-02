# 题目信息

# Monsters Attack!

## 题目描述

You are playing a computer game. The current level of this game can be modeled as a straight line. Your character is in point $ 0 $ of this line. There are $ n $ monsters trying to kill your character; the $ i $ -th monster has health equal to $ a_i $ and is initially in the point $ x_i $ .

Every second, the following happens:

- first, you fire up to $ k $ bullets at monsters. Each bullet targets exactly one monster and decreases its health by $ 1 $ . For each bullet, you choose its target arbitrary (for example, you can fire all bullets at one monster, fire all bullets at different monsters, or choose any other combination). Any monster can be targeted by a bullet, regardless of its position and any other factors;
- then, all alive monsters with health $ 0 $ or less die;
- then, all alive monsters move $ 1 $ point closer to you (monsters to the left of you increase their coordinates by $ 1 $ , monsters to the right of you decrease their coordinates by $ 1 $ ). If any monster reaches your character (moves to the point $ 0 $ ), you lose.

Can you survive and kill all $ n $ monsters without letting any of them reach your character?

## 说明/提示

In the first example, you can act as follows:

- during the $ 1 $ -st second, fire $ 1 $ bullet at the $ 1 $ -st monster and $ 1 $ bullet at the $ 3 $ -rd monster. Then the $ 1 $ -st monster dies, the $ 2 $ -nd and the $ 3 $ -rd monster move closer;
- during the $ 2 $ -nd second, fire $ 2 $ bullets at the $ 2 $ -nd monster. Then the $ 2 $ -nd monster dies, the $ 3 $ -rd monster moves closer;
- during the $ 3 $ -rd second, fire $ 2 $ bullets at the $ 3 $ -rd monster. Then the $ 3 $ -rd monster dies.

In the second example, you can fire only $ 1 $ bullet, so you can kill only one of the two monsters during the $ 1 $ -st second. Then, the remaining monster moves closer and kills your character.

## 样例 #1

### 输入

```
5
3 2
1 2 3
-1 2 3
2 1
1 1
-1 1
4 10
3 4 2 5
-3 -2 1 3
5 3
2 1 3 2 5
-3 -2 3 4 5
2 1
1 2
1 2```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果



# 算法分类
贪心算法

# 题解思路、算法要点与解决难点

**核心思路**：优先击杀距离原点最近的怪物。将每个怪物的坐标转换为绝对值后，按距离从小到大处理。使用桶统计每个距离位置上的总血量，模拟每秒的子弹积累与消耗过程。

**关键步骤**：
1. 将所有怪物的坐标转换为绝对值，统计每个距离对应的总血量。
2. 按距离从小到大遍历，计算每秒可用子弹数（每秒累加k发）。
3. 若某时刻累计子弹数不足以消灭对应距离的怪物总和，则判定失败。

**解决难点**：
- **时间窗口判断**：怪物在距离d时，必须在d秒内被完全消灭。通过将绝对值转换为距离，直接建立时间与位置的对应关系。
- **子弹累计机制**：每秒的子弹可累积使用，但必须满足每个时间窗口的击杀需求。

# 题解评分 (≥4星)

1. **Hacker_Cracker（4.5星）**  
   - 亮点：使用桶统计距离总血量，代码简洁高效。  
   - 关键代码：`t[abs(x)] += a` 实现距离聚合，`sum += k - t[i]` 实现子弹累计检查。

2. **2huk（4星）**  
   - 亮点：详细说明怪物移动与时间的对应关系，提出"剩余子弹传递"概念。  
   - 核心逻辑：`sum += k` 累计子弹，`sum -= s[i]` 扣减当前距离怪物血量。

3. **Elhaithan（4星）**  
   - 亮点：按距离排序后动态计算子弹需求，引入`d*k`子弹消耗模型。  
   - 代码特色：`mon[i].a -= k * (mon[i].x - mon[i-1].x)` 显式处理时间差。

# 最优思路或技巧提炼

**核心技巧**：
1. **绝对值转换**：将坐标转换为绝对值，消除方向差异，直接建立距离与时间的映射。
2. **桶统计优化**：用数组下标直接表示距离，O(1)时间复杂度聚合怪物血量。
3. **子弹累计模型**：`sum += k` 模拟子弹随时间积累，`sum -= t[i]` 模拟击杀消耗。

**代码实现要点**：
```cpp
// 核心逻辑片段（Hacker_Cracker版本）
for (int i = 1; i <= n; i++) {
    sum = sum + k - t[i]; // 累计子弹并扣除当前距离的怪物总血量
    if (sum < 0) return false;
}
```

# 同类型题及算法套路

**常见变式**：
- 资源时间窗口分配：在截止时间前分配固定资源完成任务。
- 移动目标拦截：计算在目标抵达某位置前的最少拦截次数。

**通用解法**：
1. 按截止时间排序任务
2. 动态维护可用资源
3. 贪心分配资源

# 推荐练习题

1. **P1080 国王游戏**（贪心排序+大数处理）
2. **P1090 合并果子**（优先队列贪心）
3. **P1223 排队接水**（时间窗口贪心）

# 可视化与算法演示

**动画设计**：
1. **数轴显示**：左侧为原点，右侧显示不同距离的怪物血条（红色方块高度表示血量）。
2. **时间步进**：每秒触发以下动作：
   - 黄色子弹图标从原点飞向各个怪物，数量等于k
   - 血条根据子弹命中动态减少
   - 幸存怪物向原点移动一格
3. **失败高亮**：当某怪物移动到原点时，屏幕闪烁红光并播放爆炸音效。

**复古像素风格**：
- 使用16色调色板：原点为蓝色方块，怪物为红色像素块，子弹为黄色光点。
- 音效设计：
  - 子弹发射：8-bit "pew" 音效
  - 怪物死亡：短促爆炸声
  - 游戏失败：低沉警报声

**交互控制**：
- 空格键暂停/继续
- 方向键调整动画速度
- F键触发"AI自动演示"

# 个人心得摘录

> "开long long是这类题目的保命符，坐标绝对值转换后问题立即简化" —— Hacker_Cracker  
> "将移动时间转化为距离的绝对值，问题就变成经典的时间窗口资源分配" —— 2huk

# 核心算法代码（Hacker_Cracker版）

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
ll t[N], a[N], p[N];

int main() {
    ll T;
    cin >> T;
    while (T--) {
        int n, k, f = 1;
        cin >> n >> k;
        fill(t, t + n + 2, 0); // 初始化桶数组
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            t[abs(p[i])] += a[i]; // 关键：绝对值转换+桶统计
        }
        ll sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += k - t[i]; // 子弹累计与消耗
            if (sum < 0) { f = 0; break; }
        }
        cout << (f ? "YES" : "NO") << endl;
    }
    return 0;
}
```

---
处理用时：81.04秒