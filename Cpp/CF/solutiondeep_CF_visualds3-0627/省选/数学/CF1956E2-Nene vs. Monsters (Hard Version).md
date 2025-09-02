# 题目信息

# Nene vs. Monsters (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference between the versions is the constraints on $ a_i $ . You can make hacks only if both versions of the problem are solved.

Nene is fighting with $ n $ monsters, located in a circle. These monsters are numbered from $ 1 $ to $ n $ , and the $ i $ -th ( $ 1 \le i \le n $ ) monster's current energy level is $ a_i $ .

Since the monsters are too strong, Nene decided to fight with them using the Attack Your Neighbour spell. When Nene uses this spell, the following actions happen in the following order one by one:

- The $ 1 $ -st monster attacks the $ 2 $ -nd monster;
- The $ 2 $ -nd monster attacks the $ 3 $ -rd monster;
- $ \ldots $
- The $ (n-1) $ -th monster attacks the $ n $ -th monster;
- The $ n $ -th monster attacks the $ 1 $ -st monster.

When the monster with energy level $ x $ attacks the monster with the energy level $ y $ , the energy level of the defending monster becomes $ \max(0, y-x) $ (the energy level of the attacking monster remains equal to $ x $ ).

Nene is going to use this spell $ 10^{100} $ times and deal with the monsters that will still have a non-zero energy level herself. She wants you to determine which monsters will have a non-zero energy level once she will use the described spell $ 10^{100} $ times.

## 说明/提示

In the first test case, the following actions happen during the first $ 3 $ uses of the spell in this order:

- Nene uses the Attack Your Neighbour spell for the first time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 5-2)=3 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 3-3)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ ;
- Nene uses the Attack Your Neighbour spell for the second time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 3-2)=1 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 0-1)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ ;
- Nene uses the Attack Your Neighbour spell for the third time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 1-2)=0 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 0-0)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ .

After each of the next uses of the spell, energy levels of monsters do not change. Thus, only the $ 1 $ -st monster has a non-zero energy level in the end.

In the second test case, both monsters initially have zero energy level.

## 样例 #1

### 输入

```
5
3
2 5 3
2
0 0
4
1 5 7 2
4
4 2 1 2
13
1 1 4 5 1 4 1 9 1 9 8 1 0```

### 输出

```
1
1 
0

1
1 
2
1 3 
6
1 3 6 8 10 12```

# AI分析结果



## 唯一算法分类
**无算法分类**

---

## 综合分析与结论

### 核心思路
1. **暴力模拟阶段**：利用数学观察，经过约 O(³√max(a_i)) 次攻击后，存活怪物形成的连续段长度 ≤3，此时暴力模拟足够次数。
2. **数学分析阶段**：对剩余存活段进行数学推导，判断最终存活怪物。关键点包括：
   - 连续四只怪物攻击时，第四只受到 O(t³) 伤害，必有一死。
   - 对长度为3的存活段，计算攻击次数的等差数列和，判断最终血量。

### 关键公式推导
- **等差数列求和**：当存活段为 `0, x, y, z`，x 攻击 y 的次数为 `k = y // x`，总伤害为 `(y-x + y%x) * k / 2`。若 `z > 总伤害`，则 z 存活。

### 可视化设计
- **动画方案**：用环形排列像素方块表示怪物，攻击时高亮攻击方向，动态显示血量变化。稳定后，用不同颜色标记存活怪物。
- **复古游戏化**：8位风格血条，攻击时播放“攻击音效”，存活怪物最终闪烁。控制面板支持步进观察攻击次数与伤害计算。

---

## 题解清单 (≥4星)

1. **ReTF题解（4.5星）**  
   - **亮点**：提出暴力模拟次数与连通块长度关系，数学分析清晰。代码逻辑简洁，但需注意long long处理。  
   - **心得**：强调数据范围对变量类型的影响（未开long long导致WA）。

2. **jianhe题解（4.5星）**  
   - **亮点**：详细推导连续四只怪物的数学处理，代码结构清晰，注释完整。  
   - **关键代码**：等差数列求和函数 `calc()` 直接对应数学公式。

3. **SkyLines题解（4星）**  
   - **亮点**：时间复杂度分析到位，处理首尾相连的细节准确。  
   - **优化**：手动处理开头，避免环状结构导致的边界问题。

---

## 代码实现与核心逻辑

### 关键代码片段（jianhe题解）
```cpp
ll calc(ll s, ll e, ll n) { 
    return (s + e) * n / 2; 
}
// 处理连续四只怪物：0, x, y, z
if (a[i1] == 0 && a[i2] && a[i3] && a[i4]) {
    ll k = a[i3] / a[i2]; // 攻击次数
    ll total_damage = calc(a[i3] - a[i2], a[i3] % a[i2], k);
    if (a[i4] > total_damage) 
        ans.push_back(i4 + 1);
}
```

### 完整代码逻辑
1. **暴力模拟**：循环至无连续四只存活怪物。
2. **单次攻击处理**：遍历每个怪物，攻击下一个。
3. **数学判断存活**：对每个 `0` 后的存活段，计算总伤害并判断后续怪物是否存活。

---

## 同类型题与套路

### 常见套路
- **循环节与数学归纳**：在无法直接模拟时，寻找循环节或稳定状态。
- **等差数列/等比数列求和**：处理多次累积伤害或资源消耗问题。
- **复杂度均摊**：通过数学分析减少暴力次数，如本题的 O(³√n) 优化。

### 推荐题目
1. **P1965 转圈游戏**（数论，快速幂求循环节）
2. **P1516 青蛙的约会**（扩展欧几里得，线性同余方程）
3. **P2426 删数游戏**（动态规划与数学推导结合）

---

## 个人心得摘录

- **ReTF**：未开long long导致WA，强调大数据范围下的变量类型检查。
- **Purslane**：处理五只以上连续怪物时复杂度爆炸，需合理剪枝。
- **jianhe**：手动处理环状结构首尾相连的细节，避免遗漏边界情况。

---

## 可视化与复古游戏化设计

### 像素动画方案
1. **环形布局**：怪物用像素方块环形排列，攻击时箭头高亮，血量用数字/血条显示。
2. **攻击音效**：每次攻击播放8位“哔”声，怪物死亡时播放低沉音效。
3. **自动演示模式**：按步骤展示暴力模拟和数学分析阶段，支持暂停/继续。

### 关键交互
- **步进控制**：用户可逐步观察每轮攻击后的血量变化。
- **伤害计算演示**：高亮当前处理的存活段，动态显示等差数列求和过程。

### 复古风格
- **调色板**：16色，怪物用红/绿/蓝区分存活状态。
- **Canvas绘制**：攻击动画用像素粒子效果，血条渐变减少。

---
处理用时：63.71秒