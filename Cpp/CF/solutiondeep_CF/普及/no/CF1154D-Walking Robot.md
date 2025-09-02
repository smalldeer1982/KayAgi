# 题目信息

# Walking Robot

## 题目描述

There is a robot staying at $ X=0 $ on the $ Ox $ axis. He has to walk to $ X=n $ . You are controlling this robot and controlling how he goes. The robot has a battery and an accumulator with a solar panel.

The $ i $ -th segment of the path (from $ X=i-1 $ to $ X=i $ ) can be exposed to sunlight or not. The array $ s $ denotes which segments are exposed to sunlight: if segment $ i $ is exposed, then $ s_i = 1 $ , otherwise $ s_i = 0 $ .

The robot has one battery of capacity $ b $ and one accumulator of capacity $ a $ . For each segment, you should choose which type of energy storage robot will use to go to the next point (it can be either battery or accumulator). If the robot goes using the battery, the current charge of the battery is decreased by one (the robot can't use the battery if its charge is zero). And if the robot goes using the accumulator, the current charge of the accumulator is decreased by one (and the robot also can't use the accumulator if its charge is zero).

If the current segment is exposed to sunlight and the robot goes through it using the battery, the charge of the accumulator increases by one (of course, its charge can't become higher than it's maximum capacity).

If accumulator is used to pass some segment, its charge decreases by 1 no matter if the segment is exposed or not.

You understand that it is not always possible to walk to $ X=n $ . You want your robot to go as far as possible. Find the maximum number of segments of distance the robot can pass if you control him optimally.

## 说明/提示

In the first example the robot can go through the first segment using the accumulator, and charge levels become $ b=2 $ and $ a=0 $ . The second segment can be passed using the battery, and charge levels become $ b=1 $ and $ a=1 $ . The third segment can be passed using the accumulator, and charge levels become $ b=1 $ and $ a=0 $ . The fourth segment can be passed using the battery, and charge levels become $ b=0 $ and $ a=1 $ . And the fifth segment can be passed using the accumulator.

In the second example the robot can go through the maximum number of segments using battery two times and accumulator one time in any order.

## 样例 #1

### 输入

```
5 2 1
0 1 0 1 0
```

### 输出

```
5
```

## 样例 #2

### 输入

```
6 2 1
1 0 0 1 0 1
```

### 输出

```
3
```

# AI分析结果

### 题目内容重写

#### 行走的机器人

**题目描述**

有一个机器人位于 $Ox$ 轴上的 $X=0$ 处。它需要走到 $X=n$ 处。你控制这个机器人，并决定它如何移动。机器人有一个电池和一个带有太阳能板的蓄能器。

路径的第 $i$ 段（从 $X=i-1$ 到 $X=i$）可能暴露在阳光下或不被暴露。数组 $s$ 表示哪些段暴露在阳光下：如果第 $i$ 段暴露在阳光下，则 $s_i = 1$，否则 $s_i = 0$。

机器人有一个容量为 $b$ 的电池和一个容量为 $a$ 的蓄能器。对于每一段，你需要选择机器人使用哪种能量存储来移动到下一个点（可以是电池或蓄能器）。如果机器人使用电池移动，电池的当前电量减少一（如果电池电量为零，则不能使用电池）。如果机器人使用蓄能器移动，蓄能器的当前电量减少一（如果蓄能器电量为零，则不能使用蓄能器）。

如果当前段暴露在阳光下且机器人使用电池通过该段，则蓄能器的电量增加一（当然，蓄能器的电量不能超过其最大容量）。

如果使用蓄能器通过某一段，无论该段是否暴露在阳光下，蓄能器的电量都会减少一。

你明白，机器人并不总是能够走到 $X=n$ 处。你希望机器人尽可能走得更远。找出在最优控制下，机器人能够通过的最大段数。

**说明/提示**

在第一个例子中，机器人可以通过第一段使用蓄能器，电量变为 $b=2$ 和 $a=0$。第二段可以使用电池，电量变为 $b=1$ 和 $a=1$。第三段可以使用蓄能器，电量变为 $b=1$ 和 $a=0$。第四段可以使用电池，电量变为 $b=0$ 和 $a=1$。第五段可以使用蓄能器。

在第二个例子中，机器人可以通过最多段数使用电池两次和蓄能器一次，顺序不限。

**样例 #1**

**输入**

```
5 2 1
0 1 0 1 0
```

**输出**

```
5
```

**样例 #2**

**输入**

```
6 2 1
1 0 0 1 0 1
```

**输出**

```
3
```

### 算法分类

贪心

### 题解分析与结论

本题的核心在于如何在不同条件下选择使用电池或蓄能器，以最大化机器人能够行走的段数。所有题解都采用了贪心算法，但在具体实现细节上有所不同。以下是各题解的对比：

1. **灵乌路空**：提出了明确的贪心策略，代码简洁且易于理解。评分：4星。
2. **first_fan**：虽然思路清晰，但代码冗长且部分逻辑重复。评分：3星。
3. **一扶苏一**：提供了严谨的证明，代码简洁且高效。评分：5星。
4. **Disjoint_cat**：思路清晰，代码简洁，但缺乏对复杂情况的深入分析。评分：4星。
5. **Pretharp**：代码简短，但缺乏对策略的详细解释。评分：3星。

### 所选高分题解

#### 一扶苏一 (5星)

**关键亮点**：提供了严谨的贪心策略证明，代码简洁且高效。

**代码核心实现**：
```cpp
int main() {
  freopen("1.in", "r", stdin);
  qr(n); qr(a); qr(b);
  int x = a, y = b;
  for (int i = 1; i <= n; ++i) qr(MU[i]);
  for (int i = 1; i <= n; ++i) {
    if ((x | y) == 0) {
      qw(i - 1, '\n', true);
      return 0;
    } else {
      if (MU[i]) {
        if ((y == b) || (x == 0)) {
          --y;
        } else {
          --x; ++y;
        }
      } else {
        if (y == 0) --x;
        else --y;
      }
    }
  }
  qw(n, '\n', true);
  return 0;
}
```

**核心思想**：优先使用蓄能器，只有在蓄能器满或无法使用时才使用电池，并在有阳光时尽可能为蓄能器充电。

### 最优关键思路

1. **优先使用蓄能器**：因为蓄能器可以充电，优先使用蓄能器可以保留电池的电量以备不时之需。
2. **在有阳光时使用电池**：在有阳光时使用电池可以为蓄能器充电，增加总电量。
3. **避免浪费充电机会**：在蓄能器满时，避免使用电池充电，而是直接使用蓄能器。

### 可拓展之处

类似的问题可以出现在资源分配、路径规划等领域，贪心算法在这些问题中常常能提供高效的解决方案。

### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得总结

在解决贪心问题时，明确每一步的最优选择是关键。通过模拟和验证，可以确保策略的正确性和高效性。

---
处理用时：37.16秒