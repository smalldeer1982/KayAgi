# 题目信息

# Ingenuity-2

## 题目描述

Let's imagine the surface of Mars as an infinite coordinate plane. Initially, the rover Perseverance-2 and the helicopter Ingenuity-2 are located at the point with coordinates $ (0, 0) $ . A set of instructions $ s $ consisting of $ n $ instructions of the following types was specially developed for them:

- N: move one meter north (from point $ (x, y) $ to $ (x, y + 1) $ );
- S: move one meter south (from point $ (x, y) $ to $ (x, y - 1) $ );
- E: move one meter east (from point $ (x, y) $ to $ (x + 1, y) $ );
- W: move one meter west (from point $ (x, y) $ to $ (x - 1, y) $ ).

Each instruction must be executed either by the rover or by the helicopter. Moreover, each device must execute at least one instruction. Your task is to distribute the instructions in such a way that after executing all $ n $ instructions, the helicopter and the rover end up at the same point, or determine that this is impossible.

## 说明/提示

Let's consider the first example: the string $ S = \texttt{NENSNE} $ . One of the possible solutions, shown in the figure below, is $ p = \texttt{RRHRRH} $ , using which both the rover and the helicopter will end up one meter north and one meter east.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974D/6e8d0f788b954d2ceff54878d55afda06efd52c8.png)For WWW, the solution is impossible.

## 样例 #1

### 输入

```
10
6
NENSNE
3
WWW
6
NESSWS
2
SN
2
WE
4
SSNN
4
WESN
2
SS
4
EWNN
4
WEWE```

### 输出

```
RRHRRH
NO
HRRHRH
NO
NO
RHRH
RRHH
RH
RRRH
RRHH```

# AI分析结果

### 题目内容重写（中文）

让我们将火星表面想象为一个无限的坐标平面。最初，火星车“毅力号-2”和直升机“机智号-2”都位于坐标点 $(0, 0)$。为它们开发了一组指令 $s$，包含 $n$ 条指令，指令类型如下：

- N：向北移动一米（从点 $(x, y)$ 移动到 $(x, y + 1)$）；
- S：向南移动一米（从点 $(x, y)$ 移动到 $(x, y - 1)$）；
- E：向东移动一米（从点 $(x, y)$ 移动到 $(x + 1, y)$）；
- W：向西移动一米（从点 $(x, y)$ 移动到 $(x - 1, y)$）。

每条指令必须由火星车或直升机执行。此外，每个设备必须至少执行一条指令。你的任务是以某种方式分配指令，使得在执行完所有 $n$ 条指令后，直升机和火星车最终位于同一点，或者确定这是不可能的。

### 综合分析与结论

这道题的核心在于如何合理分配指令，使得两个设备最终到达同一个位置。难点在于如何确保每个设备至少执行一条指令，并且在分配指令时保持两个设备的移动步数一致。题解中主要采用了贪心算法和模拟的方法来解决这个问题。

### 所选高星题解

#### 题解1：作者：Weekoder (赞：7)
- **星级**：5星
- **关键亮点**：采用贪心算法，通过判断当前指令的方向和两个设备的位置关系，动态分配指令给设备。代码简洁且逻辑清晰，处理了每个设备至少执行一条指令的约束。
- **个人心得**：在处理指令分配时，优先考虑未执行过指令的设备，确保每个设备至少执行一条指令。
- **核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    if (s[i] == 'N') {
        if (Y1 > Y2 || Y1 == Y2 && !f2)
            Y2++, ans += 'H', f2 = 1;
        else
            Y1++, ans += 'R', f1 = 1; 
    } 
    // 其他方向类似处理
}
```

#### 题解2：作者：Eddie08012025 (赞：6)
- **星级**：4星
- **关键亮点**：通过统计每个方向的指令数量，判断是否可以将指令平均分配给两个设备。处理了指令数量为奇数时的特殊情况，确保每个设备至少执行一条指令。
- **核心代码**：
```cpp
if (z['N'] == 1 && z['S'] == 1 && z['E'] == 0 && z['W'] == 0 || 
    z['N'] == 0 && z['S'] == 0 && z['E'] == 1 && z['W'] == 1 || 
    z['N'] % 2 != z['S'] % 2 || z['E'] % 2 != z['W'] % 2) {
    cout << "NO\n";
    continue;
}
```

#### 题解3：作者：gu51yo (赞：5)
- **星级**：4星
- **关键亮点**：通过判断指令的奇偶性，动态分配指令给设备。代码简洁，逻辑清晰，处理了每个设备至少执行一条指令的约束。
- **核心代码**：
```cpp
for (int i = 0; i < n; i++) {
    cout << "HR"[(a[i] + b[a[i]]++) % 2];
}
```

### 最优关键思路或技巧

1. **贪心算法**：通过动态判断当前指令的方向和设备的位置关系，优先分配给能够使两个设备位置更接近的设备。
2. **指令统计与分配**：统计每个方向的指令数量，确保指令可以平均分配给两个设备，处理指令数量为奇数时的特殊情况。
3. **奇偶性判断**：通过判断指令数量的奇偶性，确保两个设备的移动步数一致。

### 可拓展之处

这类问题可以拓展到多个设备的指令分配问题，或者扩展到三维空间中的移动问题。类似的算法思路也可以应用于其他需要动态分配资源的场景。

### 推荐相似题目

1. [P2689 东南西北](https://www.luogu.com.cn/problem/P2689)
2. [P1979 华容道](https://www.luogu.com.cn/problem/P1979)
3. [P1046 火星探险](https://www.luogu.com.cn/problem/P1046)

### 个人心得总结

在处理指令分配问题时，优先考虑未执行过指令的设备，确保每个设备至少执行一条指令。此外，通过统计指令数量和判断奇偶性，可以有效简化问题的复杂度。

---
处理用时：35.97秒