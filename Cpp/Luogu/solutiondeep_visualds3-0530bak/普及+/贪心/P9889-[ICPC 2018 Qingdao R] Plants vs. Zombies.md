# 题目信息

# [ICPC 2018 Qingdao R] Plants vs. Zombies

## 题目描述

BaoBao and DreamGrid are playing the game $\textit{Plants vs. Zombies}$. In the game, DreamGrid grows plants to defend his garden against BaoBao's zombies.

![](https://cdn.luogu.com.cn/upload/image_hosting/9tyl9ix3.png)

$\textit{Plants vs. Zombies(?)} \\
\textit{(Image from pixiv. ID: 21790160; Artist: socha)}$

There are $n$ plants in DreamGrid's garden arranged in a line. From west to east, the plants are numbered from 1 to $n$ and the $i$-th plant lies $i$ meters to the east of DreamGrid's house. The $i$-th plant has a defense value of $d_i$ and a growth speed of $a_i$. Initially, $d_i = 0$ for all $1 \le i \le n$. 

DreamGrid uses a robot to water the plants. The robot is in his house initially. In one step of watering, DreamGrid will choose a direction (east or west) and the robot moves exactly 1 meter along the direction. After moving, if the $i$-th plant is at the robot's position, the robot will water the plant and $a_i$ will be added to $d_i$. Because the water in the robot is limited, at most $m$ steps can be done.

The defense value of the garden is defined as $\min\{d_i | 1 \le i \le n\}$. DreamGrid needs your help to maximize the garden's defense value and win the game.

- Each time the robot MUST move before watering a plant;
- It's OK for the robot to move more than $n$ meters to the east away from the house, or move back into the house, or even move to the west of the house.

## 说明/提示

In the explanation below, `E` indicates that the robot moves exactly 1 meter to the east from his current position, and `W` indicates that the robot moves exactly 1 meter to the west from his current position.

For the first test case, a candidate direction sequence is $\{E, E, W, E, E, W, E, E\}$, so that we have $d = \{6,6,12,6\}$ after the watering.

For the second test case, a candidate direction sequence is $\{E, E, E, E, W, E, W, E, W\}$, so that we have $d = \{10, 10, 4\}$ after the watering.

## 样例 #1

### 输入

```
2
4 8
3 2 6 6
3 9
10 10 1```

### 输出

```
6
4```

# AI分析结果



# [ICPC 2018 Qingdao R] Plants vs. Zombies 题解分析

## 题解思路与算法要点

### 核心思路
1. **二分答案**：利用答案的单调性，确定最大可能的防御值最小值。
2. **贪心策略**：从左到右处理每个植物，每次优先满足当前植物所需浇水次数，并将多余浇水次数传递给右侧植物，减少后续步数需求。

### 解决难点
- **贪心正确性证明**：需证明从左到右处理并传递次数的策略是最优的。Alex_Wei的题解通过路径调整法证明了任何最优路径都可转换为该贪心路径。
- **步数计算**：每处理一个植物i，需计算步数`2*c_i-1`，并将`c_i-1`次浇水传递给i+1。
- **边界处理**：处理最后一个植物时不需要额外移动。

## 题解评分（≥4星）

1. **Alex_Wei（5星）**  
   - 思路清晰，包含详细的贪心正确性证明。  
   - 代码结构简洁，变量命名合理，可读性强。  
   - 使用二分+贪心，时间复杂度O(n log V)。

2. **灵茶山艾府（4星）**  
   - 开区间二分优化减少计算次数。  
   - 代码中`check`函数通过`pre`变量传递浇水次数，逻辑清晰。  
   - 附带视频讲解链接，增强理解。

3. **_sh1kong_（4星）**  
   - 代码简洁，直接模拟贪心过程。  
   - 核心逻辑用`t`变量传递次数，代码可读性较好。  
   - 处理最后一个植物时优化判断。

## 最优思路提炼
1. **二分框架**：确定答案上下界，通过`check`函数验证。
2. **贪心实现**：
   - 对每个植物i计算所需次数`c_i = ceil(h/a_i)`。
   - 从左到右处理，传递`c_i-1`次到i+1，减少后续需求。
   - 步数累加公式：总步数 += `2*c_i-1`，若超限则提前返回。

## 同类型题目套路
- **二分答案+贪心验证**：如[P2216 理想的正方形](https://www.luogu.com.cn/problem/P2216)、[P4344 SHOI2015 脑洞治疗仪](https://www.luogu.com.cn/problem/P4344)。
- **区间覆盖/调度**：如[P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803)。

## 推荐洛谷题目
1. P2216 理想的正方形（二分+二维滑动窗口）
2. P4344 SHOI2015 脑洞治疗仪（二分+贪心模拟）
3. P1803 线段覆盖（贪心选择结束最早的区间）

## 个人心得摘录
- **Alex_Wei**：强调正确性证明的重要性，避免不求甚解。
- **CaiZi**：注意`ans`可能溢出`long long`，需及时终止计算。

---

## 核心代码实现（以Alex_Wei为例）
```cpp
bool check(ll x) {
  ll nxt = 0, res = 0;
  for(int i = 1; i <= n; i++) {
    ll cnt = (x - 1) / a[i] + 1 - nxt;
    if(cnt > 0 || i < n) res++, cnt--;
    cnt = max(cnt, 0ll);
    res += cnt * 2, nxt = cnt;
    if(res > m) return 0;
  }
  return 1;
}
```

---

## 可视化与算法演示设计
### 动画方案
- **像素风格**：用Canvas绘制植物为绿色方块，机器人为红色像素点。
- **步进控制**：按空格单步执行，显示当前植物c_i和步数消耗。
- **颜色标记**：当前处理植物高亮黄色，传递次数后右侧植物变浅绿。

### 交互功能
- **速度调节**：滑动条控制动画速度（100ms~2s）。
- **音效**：移动时播放“滴”声，超限时播放警报音。
- **自动模式**：AI自动执行贪心策略，展示最优路径。

### 复古游戏化
- **8位音效**：使用Web Audio生成方波音效。
- **积分系统**：正确完成每个植物浇水得10分，连击加倍。
- **关卡制**：每关增加植物数量或限制步数，增强挑战性。

---

**示例代码（JS伪代码）**  
```javascript
// 初始化Canvas
const canvas = document.getElementById('game');
const ctx = canvas.getContext('2d');

// 绘制植物和机器人
function drawPlants(plants) {
  plants.forEach((p, i) => {
    ctx.fillStyle = p.active ? '#FF0' : '#0F0';
    ctx.fillRect(i*30, 100, 20, 20);
  });
}

// 贪心动画循环
function animateStep(h) {
  let step = 0, currentPlant = 0;
  while (step < m && currentPlant < n) {
    const needed = Math.ceil(h / a[currentPlant]);
    // 计算步数并更新界面
    step += 2*needed -1;
    drawStep(currentPlant, needed);
    currentPlant++;
  }
}
```

---

通过上述设计，学习者可直观理解贪心策略的执行过程与步数计算，结合游戏化元素提升学习兴趣。

---
处理用时：79.14秒