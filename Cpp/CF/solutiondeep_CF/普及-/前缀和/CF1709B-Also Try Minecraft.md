# 题目信息

# Also Try Minecraft

## 题目描述

You are beta testing the new secret Terraria update. This update will add quests to the game!

Simply, the world map can be represented as an array of length $ n $ , where the $ i $ -th column of the world has height $ a_i $ .

There are $ m $ quests you have to test. The $ j $ -th of them is represented by two integers $ s_j $ and $ t_j $ . In this quest, you have to go from the column $ s_j $ to the column $ t_j $ . At the start of the quest, you are appearing at the column $ s_j $ .

In one move, you can go from the column $ x $ to the column $ x-1 $ or to the column $ x+1 $ . In this version, you have Spectre Boots, which allow you to fly. Since it is a beta version, they are bugged, so they only allow you to fly when you are going up and have infinite fly duration. When you are moving from the column with the height $ p $ to the column with the height $ q $ , then you get some amount of fall damage. If the height $ p $ is greater than the height $ q $ , you get $ p - q $ fall damage, otherwise you fly up and get $ 0 $ damage.

For each of the given quests, determine the minimum amount of fall damage you can get during this quest.

## 样例 #1

### 输入

```
7 6
10 8 9 6 8 12 7
1 2
1 7
4 6
7 1
3 5
4 2```

### 输出

```
2
10
0
7
3
1```

# AI分析结果



# Also Try Minecraft

## 题目描述

你正在测试 Terraria 新的秘密更新。该更新将在游戏中添加任务系统！

简而言之，世界地图可以表示为一个长度为 $n$ 的数组，其中第 $i$ 列的高度为 $a_i$。

你需要测试 $m$ 个任务。第 $j$ 个任务由两个整数 $s_j$ 和 $t_j$ 表示。在此任务中，你需要从第 $s_j$ 列移动到第 $t_j$ 列。任务开始时，你会出现在第 $s_j$ 列。

每次移动时，你可以从第 $x$ 列走到第 $x-1$ 列或第 $x+1$ 列。此版本中你拥有幽灵靴，允许你在上升时无限飞行。但存在bug：当从高度为 $p$ 的列移动到高度为 $q$ 的列时：
- 如果 $p > q$，会受到 $p - q$ 的坠落伤害
- 如果 $p \leq q$，不会受到伤害

请为每个任务计算可能受到的最小坠落伤害总和。

---

## 题解分析与结论

### 核心思路
所有题解均采用**双前缀和**预处理：
1. 左到右前缀和数组 `s1[i]`：存储从第1列到第i列的总坠落伤害
2. 右到左前缀和数组 `s2[i]`：存储从第n列到第i列的总坠落伤害
3. 查询时根据起点终点方向选择对应前缀和数组计算差值

### 解决难点
1. **方向处理**：通过两个独立的前缀和数组巧妙处理双向移动问题
2. **时间复杂度**：预处理O(n)，查询O(1)，满足大数据量要求
3. **边界处理**：正确计算相邻列间的坠落差值，注意数组索引边界

### 最优思路总结
1. **双前缀和预处理**：分别维护两个方向的坠落伤害累加值
2. **方向判断查询**：根据s_j和t_j的大小关系选择对应前缀和差值
3. **数据范围处理**：使用long long类型避免整型溢出

---

## 高分题解推荐

### 1. dengziyue（⭐⭐⭐⭐⭐）
**关键亮点**：
- 代码简洁高效，逻辑清晰
- 数组命名规范易懂（s1/s2）
- 预处理循环边界处理准确

```cpp
// 预处理核心代码
s1[1] = s2[n] = 0;
for(int i=2; i<=n; ++i) 
    s1[i] = s1[i-1] + max(a[i-1]-a[i], 0ll);
for(int i=n-1; i>=1; --i)
    s2[i] = s2[i+1] + max(a[i+1]-a[i], 0ll);

// 查询处理
if(x < y) printf("%lld\n", s1[y]-s1[x]);
else printf("%lld\n", s2[y]-s2[x]);
```

### 2. Starw（⭐⭐⭐⭐）
**关键亮点**：
- 变量命名直观（sum1/sum2）
- 预处理逻辑简明易懂
- 完整包含输入输出处理

```cpp
for(int i=2; i<=n; i++) 
    sum1[i] = sum1[i-1] + max(0, a[i-1]-a[i]);
for(int i=n-1; i>=1; i--)
    sum2[i] = sum2[i+1] + max(0, a[i+1]-a[i]);
```

### 3. _Ad_Astra_（⭐⭐⭐⭐）
**亮点总结**：
- 数学公式辅助说明
- 详细注释预处理逻辑
- 代码包含防溢出处理

```cpp
for(int i=2; i<=n; i++)
    prel[i] = prel[i-1] + max(0LL, a[i-1]-a[i]);
for(int i=n-1; i>=1; i--)
    prer[i] = prer[i+1] + max(0LL, a[i+1]-a[i]);
```

---

## 关键技巧与拓展
1. **双前缀和应用**：适用于需要处理双向移动的区间和问题
2. **方向分离思想**：将不同移动方向的逻辑解耦处理
3. **数据类型选择**：大数据量累加时使用long long避免溢出

### 类似题目推荐
1. [P8218 求区间和](https://www.luogu.com.cn/problem/P8218) - 基础前缀和应用
2. [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367) - 差分数组与区间修改
3. [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719) - 二维前缀和进阶应用

---

## 调试心得摘录
1. **long long陷阱**：多个题解强调必须使用long long类型（如HarryKane的"不开long long见祖宗"）
2. **方向判断顺序**：注意处理x=y时的特例（虽然题目保证s≠t）
3. **预处理边界**：如smallfang代码中的i=1和i=n的初始化处理
4. **数组索引对齐**：部分题解使用i和i+1的差值计算，需确保数组访问不越界

---
处理用时：48.46秒