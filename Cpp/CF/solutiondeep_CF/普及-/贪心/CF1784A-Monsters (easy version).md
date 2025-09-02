# 题目信息

# Monsters (easy version)

## 题目描述

This is the easy version of the problem. In this version, you only need to find the answer once. In this version, hacks are not allowed.

In a computer game, you are fighting against $ n $ monsters. Monster number $ i $ has $ a_i $ health points, all $ a_i $ are integers. A monster is alive while it has at least $ 1 $ health point.

You can cast spells of two types:

1. Deal $ 1 $ damage to any single alive monster of your choice.
2. Deal $ 1 $ damage to all alive monsters. If at least one monster dies (ends up with $ 0 $ health points) as a result of this action, then repeat it (and keep repeating while at least one monster dies every time).

Dealing $ 1 $ damage to a monster reduces its health by $ 1 $ .

Spells of type 1 can be cast any number of times, while a spell of type 2 can be cast at most once during the game.

What is the smallest number of times you need to cast spells of type 1 to kill all monsters?

## 说明/提示

In the first test case, the initial health points of the monsters are $ [3, 1, 2] $ . It is enough to cast a spell of type 2:

- Monsters' health points change to $ [2, 0, 1] $ . Since monster number $ 2 $ dies, the spell is repeated.
- Monsters' health points change to $ [1, 0, 0] $ . Since monster number $ 3 $ dies, the spell is repeated.
- Monsters' health points change to $ [0, 0, 0] $ . Since monster number $ 1 $ dies, the spell is repeated.
- Monsters' health points change to $ [0, 0, 0] $ .

Since it is possible to use no spells of type 1 at all, the answer is $ 0 $ .

In the second test case, the initial health points of the monsters are $ [4, 1, 5, 4, 1, 1] $ . Here is one of the optimal action sequences:

- Using a spell of type 1, deal $ 1 $ damage to monster number $ 1 $ . Monsters' health points change to $ [3, 1, 5, 4, 1, 1] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 4 $ . Monsters' health points change to $ [3, 1, 5, 3, 1, 1] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 4 $ again. Monsters' health points change to $ [3, 1, 5, 2, 1, 1] $ .
- Use a spell of type 2:
  - Monsters' health points change to $ [2, 0, 4, 1, 0, 0] $ . Since monsters number $ 2 $ , $ 5 $ , and $ 6 $ die, the spell is repeated.
  - Monsters' health points change to $ [1, 0, 3, 0, 0, 0] $ . Since monster number $ 4 $ dies, the spell is repeated.
  - Monsters' health points change to $ [0, 0, 2, 0, 0, 0] $ . Since monster number $ 1 $ dies, the spell is repeated.
  - Monsters' health points change to $ [0, 0, 1, 0, 0, 0] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 3 $ . Monsters' health points change to $ [0, 0, 0, 0, 0, 0] $ .

Spells of type 1 are cast $ 4 $ times in total. It can be shown that this is the smallest possible number.

## 样例 #1

### 输入

```
2
3
3 1 2
6
4 1 5 4 1 1```

### 输出

```
0
4```

# AI分析结果



# Monsters (easy version)

## 题目描述

这是该问题的简单版本。在此版本中，你只需计算一次答案，且不允许使用hack。

在一款电脑游戏中，你需要对抗 $n$ 个怪物。第 $i$ 个怪物有 $a_i$ 点生命值，所有 $a_i$ 均为整数。当怪物生命值至少为 $1$ 时视为存活。

你可以施放两种类型的法术：

1. 对任意单个存活怪物造成 $1$ 点伤害。
2. 对所有存活怪物造成 $1$ 点伤害。若此次攻击导致至少一个怪物死亡（生命值变为 $0$），则立即重复施放该法术（只要每次施法都有怪物死亡就持续重复）。

类型1的法术可以无限次施放，而类型2的法术整局游戏最多只能施放一次。

求消灭所有怪物所需的最小类型1法术次数。

## 样例 #1

### 输入
```
2
3
3 1 2
6
4 1 5 4 1 1
```

### 输出
```
0
4
```

---

### 题解综合分析

#### 关键算法思路
1. **排序预处理**：所有题解均先对怪物血量排序，为后续处理奠定基础
2. **阶梯式调整**：核心策略是将排序后的血量调整为形如 1,2,3... 的阶梯序列，确保每次类型2攻击都能触发连锁反应
3. **差值累加**：通过计算每个元素与理想阶梯值的差值之和，得到类型1的最小使用次数

#### 解决难点
- 类型2的连锁触发条件需要精确的血量分布
- 必须保证类型2使用后所有怪物都能被后续连锁攻击消灭
- 处理原始序列中存在多个相同值或跳跃值的情况

#### 最优解法总结
1. 将怪物血量升序排序
2. 维护一个期望值变量（初始为1或前一个处理过的值+1）
3. 遍历排序后的数组：
   ```python
   for i in 1..n:
       expected = min(expected + 1, a[i])
       ans += a[i] - expected
   ```
4. 最终答案为所有差值之和

---

### 高分题解推荐（≥4★）

#### 1. hellolin 题解（4★）
**亮点**：
- 使用直观的相邻差值判断，逻辑清晰易懂
- 代码结构简洁，包含详细的注释说明
- 明确处理了初始值为1的特殊情况

**核心代码**：
```cpp
sort(a+1, a+1+n);
for(int i=1; i<=n; i++) {
    if(a[i]-a[i-1]>1) {
        ans += a[i]-a[i-1]-1;
        a[i] = a[i-1]+1;
    }
}
```

#### 2. Alex_Wei 题解（4★）
**亮点**：
- 从操作后状态逆向推导，数学证明严谨
- 引入交换法证明操作顺序的最优性
- 时间复杂度分析全面（包含桶排优化）

**核心思路**：
```cpp
sort(a.begin(), a.end());
int c = 0, ans = 0;
for(int x : a) {
    c = min(c + 1, x);
    ans += x - c;
}
```

#### 3. yinhy09 题解（4★）
**亮点**：
- 采用动态更新期望值的方式，避免数组修改
- 代码实现最简，空间复杂度优化到 O(1)
- 正确处理了连续相同值的情况

**核心代码**：
```cpp
sort(a+1, a+n+1);
int cnt = 1;
for(int i=1; i<=n; i++) {
    if(a[i] > cnt) {
        ans += a[i] - cnt;
        cnt++;
    }
}
```

---

### 关键技巧总结
1. **贪心排序**：排序是处理这类阶梯问题的通用预处理手段
2. **差值累积**：通过维护期望序列的差值总和来优化计算
3. **连锁触发条件**：确保每次群体攻击至少消灭一个怪物（即阶梯严格递增）
4. **空间优化**：无需实际修改数组，动态维护期望值即可

---

### 拓展训练
1. **类似题目推荐**：
   - P1090 [NOIP2004 提高组] 合并果子（贪心+优先队列）
   - P1223 排队接水（排序贪心）
   - P1803 凌乱的yyy / 线段覆盖（活动选择问题）

2. **思维扩展**：
   - 当类型2可使用多次时，问题将转化为完全不同的动态规划问题
   - 若怪物有不同抗性（每次攻击伤害不同），需结合背包问题思路

---

### 题解心得摘录
1. _zzzzzzy_ 调试经历：
   > "最初没有处理全1的情况，导致WA。后来添加了cnt变量动态维护期望值，而不是简单比较相邻元素"

2. Supernova_empire 踩坑教训：
   > "意识到不能直接让第i个元素等于i，必须考虑前序元素的影响，否则会错误处理重复值"

3. c20231020 优化经验：
   > "发现无需实际修改数组元素，只需计算差值之和，将空间复杂度从O(n)降到O(1)"

---
处理用时：49.29秒