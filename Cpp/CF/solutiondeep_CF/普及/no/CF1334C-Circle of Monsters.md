# 题目信息

# Circle of Monsters

## 题目描述

You are playing another computer game, and now you have to slay $ n $ monsters. These monsters are standing in a circle, numbered clockwise from $ 1 $ to $ n $ . Initially, the $ i $ -th monster has $ a_i $ health.

You may shoot the monsters to kill them. Each shot requires exactly one bullet and decreases the health of the targeted monster by $ 1 $ (deals $ 1 $ damage to it). Furthermore, when the health of some monster $ i $ becomes $ 0 $ or less than $ 0 $ , it dies and explodes, dealing $ b_i $ damage to the next monster (monster $ i + 1 $ , if $ i < n $ , or monster $ 1 $ , if $ i = n $ ). If the next monster is already dead, then nothing happens. If the explosion kills the next monster, it explodes too, damaging the monster after it and possibly triggering another explosion, and so on.

You have to calculate the minimum number of bullets you have to fire to kill all $ n $ monsters in the circle.

## 样例 #1

### 输入

```
1
3
7 15
2 14
5 3```

### 输出

```
6```

# AI分析结果

### 题目内容重写
# 怪兽圈

## 题目描述

你在玩一款电脑游戏，现在你需要消灭 $n$ 只怪兽。这些怪兽围成一个圈，顺时针编号从 $1$ 到 $n$。初始时，第 $i$ 只怪兽有 $a_i$ 点生命值。

你可以通过射击怪兽来消灭它们。每次射击需要消耗一颗子弹，并减少目标怪兽的 $1$ 点生命值（造成 $1$ 点伤害）。此外，当某只怪兽 $i$ 的生命值变为 $0$ 或负数时，它会死亡并爆炸，对下一只怪兽（即怪兽 $i + 1$，如果 $i < n$，否则是怪兽 $1$）造成 $b_i$ 点伤害。如果下一只怪兽已经死亡，则不会发生任何事情。如果爆炸导致下一只怪兽死亡，它也会爆炸，并对之后的怪兽造成伤害，依此类推。

你需要计算消灭所有 $n$ 只怪兽所需的最少子弹数。

## 样例 #1

### 输入

```
1
3
7 15
2 14
5 3
```

### 输出

```
6
```

### 算法分类
贪心

### 题解分析与结论
各题解的核心思路都是通过贪心策略，尽量利用怪兽爆炸的连锁反应来减少子弹的使用。主要思路是：
1. 预处理每个怪兽被前一个怪兽爆炸后剩余的血量。
2. 枚举第一个被直接打死的怪兽，计算总子弹数。
3. 选择总子弹数最小的方案。

### 精选题解
#### 题解1：作者：rouxQ (赞：17)
- **星级**：5星
- **关键亮点**：思路清晰，代码简洁，预处理和枚举的思路非常直观。
- **核心代码**：
```cpp
for (int i = 1; i <= n; i++)Min = min(Min, sum - c[i] + a[i]);
```
- **实现思想**：通过预处理每个怪兽被炸后剩余的血量，然后枚举第一个被直接打死的怪兽，计算总子弹数，取最小值。

#### 题解2：作者：AutumnKite (赞：1)
- **星级**：4星
- **关键亮点**：通过取最小值优化了爆炸伤害的计算，思路简洁。
- **核心代码**：
```cpp
for (int i = 1; i <= n; ++i) {
    b[i] = std::min(b[i], a[i % n + 1]);
    mn = std::min(mn, b[i]);
    sum -= b[i];
}
```
- **实现思想**：将爆炸伤害与下一个怪兽的生命值取最小值，避免不必要的计算，然后选择最小的爆炸伤害作为手动打死的怪兽。

#### 题解3：作者：SmileMask (赞：1)
- **星级**：4星
- **关键亮点**：预处理和枚举的思路清晰，代码结构良好。
- **核心代码**：
```cpp
for(int i=1;i<=n;i++) ans=min(ans,sum-c[i]+a[i]);
```
- **实现思想**：预处理每个怪兽被炸后剩余的血量，然后枚举第一个被直接打死的怪兽，计算总子弹数，取最小值。

### 最优关键思路
1. **预处理**：计算每个怪兽被前一个怪兽爆炸后剩余的血量，减少重复计算。
2. **枚举**：枚举第一个被直接打死的怪兽，利用爆炸的连锁反应减少子弹数。
3. **优化**：通过取最小值优化爆炸伤害的计算，避免不必要的子弹消耗。

### 拓展思路
类似的问题可以通过预处理和枚举的思路来解决，尤其是在环形结构中，通常需要找到一个起点，然后利用某种性质（如爆炸的连锁反应）来优化计算。

### 推荐题目
1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)
3. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)

---
处理用时：27.55秒