# 题目信息

# Solution for Cube

## 题目描述

During the breaks between competitions, top-model Izabella tries to develop herself and not to be bored. For example, now she tries to solve Rubik's cube 2x2x2.

It's too hard to learn to solve Rubik's cube instantly, so she learns to understand if it's possible to solve the cube in some state using 90-degrees rotation of one face of the cube in any direction.

To check her answers she wants to use a program which will for some state of cube tell if it's possible to solve it using one rotation, described above.

Cube is called solved if for each face of cube all squares on it has the same color.

<a>https://en.wikipedia.org/wiki/Rubik's\_Cube</a>

## 说明/提示

In first test case cube looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF887C/73004469d714c2206d92e2fac016d4fc092e2426.png)In second test case cube looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF887C/37b512d2c715516faa04a8cfe0023b26918d7893.png)It's possible to solve cube by rotating face with squares with numbers 13, 14, 15, 16.

## 样例 #1

### 输入

```
2 5 4 6 1 3 6 2 5 5 1 2 3 5 3 1 1 2 4 6 6 4 3 4
```

### 输出

```
NO```

## 样例 #2

### 输入

```
5 3 5 3 2 5 2 5 6 2 6 2 4 4 4 4 1 1 1 1 6 3 6 3
```

### 输出

```
YES```

# AI分析结果



【中文重写题目】
# 魔方解法

## 题目描述

在比赛间隙，顶尖模特 Izabella 尝试通过解 2x2x2 魔方来提升自己。她想知道某个魔方状态是否可以通过单次（任意方向的）90度面旋转变为已解状态。

魔方被称为已解状态当且仅当每个面的所有方块颜色相同。

## 输入输出样例

（样例内容与原文保持一致）

---

**算法分类**：枚举

---

### 题解综合分析

各题解核心思路均为枚举所有可能的单次旋转情况，通过预判旋转后的颜色分布来验证可行性。难点在于正确建立旋转操作与颜色位置的映射关系，不同解法差异主要体现在：

1. 状态表示方式（一维数组 vs 二维结构）
2. 判断逻辑设计（直接硬编码有效条件 vs 模拟旋转过程）
3. 剪枝策略（通过固定两面优化判断）

---

### 精选题解（评分≥4星）

#### 1. 流绪（⭐⭐⭐⭐⭐）
**亮点**：
- 一维数组简化索引计算
- 硬编码所有可能有效状态，通过组合判断代替实际旋转模拟
- 六种情况覆盖所有可能旋转方向

**核心思路**：
```cpp
// 检查六个面是否满足特定组合条件
if(check(13,14,15,16)&&check(17,18,19,20)&&check(2,4,22,24)&&...)
```

#### 2. OIerZhang（⭐⭐⭐⭐）
**亮点**：
- 显式模拟六个方向的旋转操作
- 通过复制数组进行状态转移验证
- 模块化检查函数增强可读性

**核心实现**：
```cpp
// 示例：第一个旋转方向的模拟
t[5] = a[1], t[7] = a[3], t[9] = a[5], t[11] = a[7];
t[24] = a[9], t[22] = a[11], t[1] = a[24], t[3] = a[22];
```

#### 3. kimi0705（⭐⭐⭐⭐）
**亮点**：
- 基于相对面已解的假设进行剪枝
- 分情况讨论减少判断次数
- 代码结构清晰易于调试

---

### 关键技巧总结
1. **一维化存储**：将魔方各面展开为一维数组，通过预定义索引映射关系简化计算
2. **状态硬编码**：针对2x2魔方的特性，预先推导所有可能的有效颜色分布组合
3. **对称性利用**：通过相对面的固定减少需要判断的情况数
4. **模块化验证**：将颜色检查封装为独立函数提升代码复用性

---

### 同类题目推荐
1. [P2470 魔方](https://www.luogu.com.cn/problem/P2470) - 三维结构模拟
2. [P2677 魔方游戏](https://www.luogu.com.cn/problem/P2677) - 状态变换优化
3. [P1215 旋转游戏](https://www.luogu.com.cn/problem/P1215) - 旋转操作模拟

---

### 题解心得摘录
流绪：
> "改成一维数组，感觉世界都清晰多了..."  
> —— 说明数据结构的选择对问题简化至关重要

过氧化氢_syq0057：
> "刚开始觉得这种写法更简单，但写到最后反而需要特判..."  
> —— 验证了前期分析充分性的重要性，避免后期陷入修补逻辑的困境

---
处理用时：51.02秒