# 题目信息

# Escape

## 题目描述

The princess is going to escape the dragon's cave, and she needs to plan it carefully.

The princess runs at $ v_{p} $ miles per hour, and the dragon flies at $ v_{d} $ miles per hour. The dragon will discover the escape after $ t $ hours and will chase the princess immediately. Looks like there's no chance to success, but the princess noticed that the dragon is very greedy and not too smart. To delay him, the princess decides to borrow a couple of bijous from his treasury. Once the dragon overtakes the princess, she will drop one bijou to distract him. In this case he will stop, pick up the item, return to the cave and spend $ f $ hours to straighten the things out in the treasury. Only after this will he resume the chase again from the very beginning.

The princess is going to run on the straight. The distance between the cave and the king's castle she's aiming for is $ c $ miles. How many bijous will she need to take from the treasury to be able to reach the castle? If the dragon overtakes the princess at exactly the same moment she has reached the castle, we assume that she reached the castle before the dragon reached her, and doesn't need an extra bijou to hold him off.

## 说明/提示

In the first case one hour after the escape the dragon will discover it, and the princess will be 1 mile away from the cave. In two hours the dragon will overtake the princess 2 miles away from the cave, and she will need to drop the first bijou. Return to the cave and fixing the treasury will take the dragon two more hours; meanwhile the princess will be 4 miles away from the cave. Next time the dragon will overtake the princess 8 miles away from the cave, and she will need the second bijou, but after this she will reach the castle without any further trouble.

The second case is similar to the first one, but the second time the dragon overtakes the princess when she has reached the castle, and she won't need the second bijou.

## 样例 #1

### 输入

```
1
2
1
1
10
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1
2
1
1
8
```

### 输出

```
1
```

# AI分析结果



【中文重写题目】
# 逃离龙穴

## 题目描述

公主计划逃离龙穴，需要精心策划逃脱方案。

公主的奔跑速度为每小时 $v_p$ 英里，龙的飞行速度为每小时 $v_d$ 英里。龙将在公主逃跑 $t$ 小时后发现，并立即开始追击。看似毫无胜算，但公主注意到龙非常贪婪且不够聪明。为了拖延时间，公主决定从龙穴宝库中借取若干珍宝。每当龙追上公主时，她会丢下一颗珍宝分散其注意力。此时龙会停下拾取珍宝，返回龙穴并花费 $f$ 小时整理宝库，之后才会重新开始追击。

公主沿直线逃跑。龙穴到目标城堡的距离为 $c$ 英里。她需要带多少珍宝才能成功抵达城堡？若龙追上公主的时刻恰逢她抵达城堡，视为公主先到达，无需额外珍宝。

## 说明/提示

样例1中：公主逃跑1小时后被发现，此时距离龙穴1英里。2小时后龙在2英里处追上，需要第一个珍宝。龙返回并整理2小时后，公主已跑至4英里处。第二次追上需第二个珍宝，之后公主安全抵达。

样例2中：第二次追上时公主刚好到达城堡，无需第二个珍宝。

## 样例 #1

### 输入
```
1 2 1 1 10
```

### 输出
```
2
```

## 样例 #2

### 输入
```
1 2 1 1 8
```

### 输出
```
1
```

【算法分类】数学

【题解分析与结论】
所有题解均采用数学模拟追及过程的思路，核心步骤为：
1. 特判公主速度≥龙时直接返回0
2. 循环计算每次追及所需时间
3. 更新公主与龙的位置
4. 判断是否到达终点决定珍宝数量

各解法差异主要在变量命名和循环条件处理上，核心数学模型一致。难点在于正确处理追及时刻与城堡位置的边界条件（如样例2情况）。

【优质题解推荐】
1. 作者：_LSA_（★★★★☆）
- 亮点：清晰的变量命名，正确处理边界条件（如样例2的判断顺序）
- 关键代码：
```cpp
while(s1 < c){
    t += (s1-s2)/(vd-vp);  // 追及时间计算
    s1 = s2 = t*vp;        // 更新位置
    if(s1 >= c) break;     // 先判断是否到达终点
    ans++;
    t += s2/vd + f;        // 龙返回耗时
    s1 = vp*t;             // 更新公主新位置
    s2 = 0;                // 龙重新出发
}
```
- 个人心得：强调判断到达城堡的代码必须写在ans++之前，否则会导致多计数（如样例2的情况）

2. 作者：dfgz（★★★☆☆）
- 亮点：简化变量计算，使用速度差概念
- 核心逻辑：
```cpp
tt = x/v;              // v为速度差
x += tt*vp;            // 更新公主位置
if(x >= c) break;      // 边界判断
x += (f+tt)*vp;        // 处理龙返回期间公主移动
```

【最优思路提炼】
关键技巧：使用追及公式 $t = \Delta s / \Delta v$ 循环模拟每次相遇，需注意：
1. 使用浮点数精确计算相遇时刻
2. 在增加宝石计数前必须先判断是否到达终点
3. 每次龙返回后要累加其整理时间到总时间

【拓展建议】
类似问题可考虑：多次相遇问题（如两物体往返运动）、带中断条件的循环模拟（如游戏回合计算）。推荐练习：
1. P1036 选数 - 数学组合问题
2. P1518 两只塔姆沃斯牛 - 追及模拟
3. P1563 玩具谜题 - 循环位置计算

---
处理用时：55.43秒