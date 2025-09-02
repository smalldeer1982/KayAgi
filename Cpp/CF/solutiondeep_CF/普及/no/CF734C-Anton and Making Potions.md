# 题目信息

# Anton and Making Potions

## 题目描述

Anton is playing a very interesting computer game, but now he is stuck at one of the levels. To pass to the next level he has to prepare $ n $ potions.

Anton has a special kettle, that can prepare one potions in $ x $ seconds. Also, he knows spells of two types that can faster the process of preparing potions.

1. Spells of this type speed up the preparation time of one potion. There are $ m $ spells of this type, the $ i $ -th of them costs $ b_{i} $ manapoints and changes the preparation time of each potion to $ a_{i} $ instead of $ x $ .
2. Spells of this type immediately prepare some number of potions. There are $ k $ such spells, the $ i $ -th of them costs $ d_{i} $ manapoints and instantly create $ c_{i} $ potions.

Anton can use no more than one spell of the first type and no more than one spell of the second type, and the total number of manapoints spent should not exceed $ s $ . Consider that all spells are used instantly and right before Anton starts to prepare potions.

Anton wants to get to the next level as fast as possible, so he is interested in the minimum number of time he needs to spent in order to prepare at least $ n $ potions.

## 说明/提示

In the first sample, the optimum answer is to use the second spell of the first type that costs $ 10 $ manapoints. Thus, the preparation time of each potion changes to $ 4 $ seconds. Also, Anton should use the second spell of the second type to instantly prepare $ 15 $ potions spending $ 80 $ manapoints. The total number of manapoints used is $ 10+80=90 $ , and the preparation time is $ 4·5=20 $ seconds ( $ 15 $ potions were prepared instantly, and the remaining $ 5 $ will take $ 4 $ seconds each).

In the second sample, Anton can't use any of the spells, so he just prepares $ 20 $ potions, spending $ 10 $ seconds on each of them and the answer is $ 20·10=200 $ .

## 样例 #1

### 输入

```
20 3 2
10 99
2 4 3
20 10 40
4 15
10 80
```

### 输出

```
20
```

## 样例 #2

### 输入

```
20 3 2
10 99
2 4 3
200 100 400
4 15
100 800
```

### 输出

```
200
```

# AI分析结果



# Anton and Making Potions

## 题目描述

Anton 正在玩一款有趣的电脑游戏，但他现在卡在了一个关卡。为了进入下一关，他需要制备至少 $n$ 瓶药水。

Anton 有一个特殊的水壶，每制备一瓶药水需要 $x$ 秒。此外，他掌握两种咒语可以加速制备过程：

1. **第一类咒语**：缩短单瓶药水的制备时间。共有 $m$ 种此类咒语，第 $i$ 个咒语消耗 $b_i$ 点法力，将每瓶药水制备时间改为 $a_i$ 秒。
2. **第二类咒语**：立即制备若干瓶药水。共有 $k$ 种此类咒语，第 $i$ 个咒语消耗 $d_i$ 点法力，直接生成 $c_i$ 瓶药水。

Anton 最多各使用一个咒语（第一类和第二类各至多一个），且总法力消耗不能超过 $s$。所有咒语在使用后立即生效。求制备至少 $n$ 瓶药水所需的最短时间。

## 说明/提示

样例 1 中，最优策略是使用第二个第一类咒语（时间变为 4 秒）和第二个第二类咒语（直接生成 15 瓶），剩余 5 瓶需 4×5=20 秒。

样例 2 中，无法使用任何咒语，直接制备 20×10=200 秒。

## 算法分类
**二分**

---

## 题解分析与结论

### 核心思路
1. **预处理第二类咒语**：按法力消耗排序并维护前缀最大生成量。
2. **枚举第一类咒语**（包括不使用的情况），计算剩余可用法力。
3. **二分查找第二类咒语**：在剩余法力限制下找到最大生成量。
4. **组合计算时间**：考虑所有情况（只用第一类、只用第二类、组合使用）取最小值。

### 关键难点
- 第二类咒语需要排序后预处理前缀最大值，否则无法高效找到最优解。
- 法力消耗的边界条件处理（如剩余法力不足以使用任何咒语时需回退到基础方案）。

### 最优技巧
- **双指针预处理**：对第二类咒语按法力消耗排序后，维护前缀最大生成量数组，使得二分时可以快速获取最优解。
- **组合枚举与二分**：通过枚举一类操作，配合二分另一类操作，将时间复杂度优化至 $O(m \log k)$。

---

## 推荐题目
1. P1083 [NOIP2012 提高组] 借教室（二分+差分验证）
2. P1678 烦恼的高考志愿（二分找最接近值）
3. P2678 [NOIP2015 提高组] 跳石头（二分答案+贪心验证）

---
处理用时：191.75秒