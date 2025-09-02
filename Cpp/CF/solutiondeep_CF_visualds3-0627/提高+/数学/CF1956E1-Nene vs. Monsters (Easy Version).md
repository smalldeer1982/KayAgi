# 题目信息

# Nene vs. Monsters (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the versions is the constraints on $ a_i $ . You can make hacks only if both versions of the problem are solved.

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



**唯一算法分类**  
组合数学

---

**综合分析与结论**  
题目要求确定在无限次攻击后存活的怪物。直接模拟不可行，需通过数学观察找到稳定状态的条件。核心思路是攻击过程中，三个连续非零怪物会被逐步破坏，最终形成稳定结构。此时，存活的条件为：怪物非零且其前驱为零（无法被攻击）。

**关键推导**：  
1. **三个连续非零的破坏性**：攻击会使得中间或右侧怪物能量快速衰减，最终无法保持三个连续非零。  
2. **稳定状态的结构**：剩余非零块长度≤2。对长度为2的块，攻击方存活，防御方被消灭。  

**可视化设计**：  
- **动画方案**：用像素风格展示每轮攻击，高亮当前攻击的怪物对，实时更新能量值。  
- **颜色标记**：红色表示攻击方，蓝色表示防御方，绿色标出最终存活怪物。  
- **步进控制**：允许单步执行观察每轮攻击后的状态变化，自动播放时可调整速度。

---

**题解清单 (≥4星)**  
1. **FFTotoro（5星）**  
   - **亮点**：通过模拟消除三连非零块，利用前驱为零的条件筛选存活者，时间复杂度优。  
   - **代码清晰**：直接处理攻击逻辑，特判n=2情况。  

2. **ReTF（4星）**  
   - **亮点**：暴力模拟固定轮次后处理剩余块，思路简洁。  
   - **数学推导**：证明经过O(√V)轮后系统稳定，适合Easy版本。

---

**最优思路提炼**  
关键技巧在于**模拟终止条件**的设定：当不存在三个连续非零怪物时，剩余结构中每个存活怪物必满足其前驱为零。通过有限次模拟即可达到稳定状态，避免无限循环。

**代码核心片段**（FFTotoro）：  
```cpp
while ([&]() { // 检查是否存在三个连续非零
    for (int i = 0; i < n; i++)
        if (a[i] && a[(i+1)%n] && a[(i+2)%n]) return true;
    return false;
}()) {
    for (int i = 0; i < n; i++) // 模拟一轮攻击
        a[(i+1)%n] = max(0, a[(i+1)%n] - a[i]);
}
// 收集存活怪物：a[i]非零且前驱为零
for (int i = 0; i < n; i++)
    if (a[i] && !a[(i+n-1)%n]) r.push_back(i+1);
```

---

**同类型题套路**  
类似问题通常涉及循环操作下的状态收敛性分析，常见解法包括：  
1. 寻找不变量或终止条件（如能量单调递减）。  
2. 分阶段处理：暴力模拟到稳定态后快速求解。  

**推荐题目**  
1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)  
2. [P1037 产生数](https://www.luogu.com.cn/problem/P1037)  
3. [P1516 青蛙的约会](https://www.luogu.com.cn/problem/P1516)  

---

**复古游戏化动画实现要点**  
- **像素风格**：用16色块表示怪物能量，攻击时闪烁攻击方和防御方。  
- **音效触发**：攻击时播放8-bit音效，存活怪物出现时播放胜利音调。  
- **自动演示**：模拟攻击过程，每步延迟100ms，展示能量变化。  

```javascript
// 伪代码示例：Canvas绘制攻击过程
function drawAttack(attacker, defender, newEnergy) {
    ctx.fillStyle = '#FF0000'; // 攻击方红色
    drawMonster(attacker);
    ctx.fillStyle = '#0000FF'; // 防御方蓝色
    drawMonster(defender);
    playSound('attack.wav');
    updateEnergy(defender, newEnergy); // 更新防御方能量
}
```

**交互设计**：  
- **控制面板**：开始/暂停/重置按钮，速度滑块。  
- **连击积分**：每正确预测一个存活怪物得10分，增加挑战性。

---
处理用时：203.58秒