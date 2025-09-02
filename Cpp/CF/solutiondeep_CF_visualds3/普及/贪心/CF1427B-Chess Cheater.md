# 题目信息

# Chess Cheater

## 题目描述

You like playing chess tournaments online.

In your last tournament you played $ n $ games. For the sake of this problem, each chess game is either won or lost (no draws). When you lose a game you get $ 0 $ points. When you win you get $ 1 $ or $ 2 $ points: if you have won also the previous game you get $ 2 $ points, otherwise you get $ 1 $ point. If you win the very first game of the tournament you get $ 1 $ point (since there is not a "previous game").

The outcomes of the $ n $ games are represented by a string $ s $ of length $ n $ : the $ i $ -th character of $ s $ is W if you have won the $ i $ -th game, while it is L if you have lost the $ i $ -th game.

After the tournament, you notice a bug on the website that allows you to change the outcome of at most $ k $ of your games (meaning that at most $ k $ times you can change some symbol L to W, or W to L). Since your only goal is to improve your chess rating, you decide to cheat and use the bug.

Compute the maximum score you can get by cheating in the optimal way.

## 说明/提示

Explanation of the first testcase. Before changing any outcome, the score is $ 2 $ . Indeed, you won the first game, so you got $ 1 $ point, and you won also the third, so you got another $ 1 $ point (and not $ 2 $ because you lost the second game).

An optimal way to cheat is to change the outcomes of the second and fourth game. Doing so, you end up winning the first four games (the string of the outcomes becomes WWWWL). Hence, the new score is $ 7=1+2+2+2 $ : $ 1 $ point for the first game and $ 2 $ points for the second, third and fourth game.

Explanation of the second testcase. Before changing any outcome, the score is $ 3 $ . Indeed, you won the fourth game, so you got $ 1 $ point, and you won also the fifth game, so you got $ 2 $ more points (since you won also the previous game).

An optimal way to cheat is to change the outcomes of the first, second, third and sixth game. Doing so, you end up winning all games (the string of the outcomes becomes WWWWWW). Hence, the new score is $ 11 = 1+2+2+2+2+2 $ : $ 1 $ point for the first game and $ 2 $ points for all the other games.

## 样例 #1

### 输入

```
8
5 2
WLWLL
6 5
LLLWWL
7 1
LWLWLWL
15 5
WWWLLLWWWLLLWWW
40 7
LLWLWLWWWLWLLWLWWWLWLLWLLWLLLLWLLWWWLWWL
1 0
L
1 1
L
6 1
WLLWLW```

### 输出

```
7
11
6
26
46
0
1
6```

# AI分析结果


### 💡 Kay的C++算法解析：Chess Cheater 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`贪心策略`  
🗣️ **初步分析**：
> 解决"Chess Cheater"的关键在于**识别得分规律并优化操作顺序**。想象你在玩一局像素风贪吃蛇：每次吃到苹果（W）会得分，连续吃到则分更高。贪心策略就是优先吃掉小间隙的障碍物（L），让蛇身（连续W段）更长！  
> - 核心公式：`最终得分 = 2×(总W数) - 连续W段数`  
> - 难点在于：如何用k次操作最小化段数？  
> - 可视化设计：用8位像素网格展示W/L，黄色方块代表W，灰色为L。填充间隙时播放"叮"音效，连接两段时触发像素闪光动画，自动演示模式像贪吃蛇AI逐步吞噬障碍物。

---

#### 2. 精选优质题解参考
**题解一（作者：houzhiyuan）**  
* **点评**：思路直击核心——用公式`(cnt+k)*2-x`量化得分（cnt=原始W数，x=段数）。代码规范：  
  - 用`a[]`存储间隙长度，排序实现贪心  
  - 边界处理严谨（如全L时`cnt+k>=n`直接输出`2n-1`）  
  - 推导清晰：每填满一个间隙段数减1，体现在`x=tot-i+2`的精妙计算中

**题解二（作者：钓鱼王子）**  
* **点评**：通过动态加分过程深化理解：  
  - 每改L为W固定加2分（基础1分+相邻加成）  
  - 填满间隙段时额外+1分（段数减少）  
  - 亮点：用`ans += max(0, (ll?m*2:m*2-1))`优雅处理全L特例

**题解三（作者：7KByte）**  
* **点评**：创新性区分中间段与首尾段：  
  - 只处理能连接两段W的中间间隙（`i=2 to n-1`）  
  - 填充中间段时触发"超级连接"特效（`+2*c[i]+1`）  
  - 首尾段单独处理，避免无效段数减少

---

#### 3. 核心难点辨析与解题策略
1. **难点1：得分规则抽象化**  
   *分析*：胜局分1分，连胜额外+1分 → 转化为`得分=2×总W数-段数`。关键变量`段数x`需通过合并连续W最小化  
   💡 **学习笔记**：好算法=精准建模+变量关系挖掘

2. **难点2：操作优先级决策**  
   *分析*：贪心策略证明：填充小间隙性价比最高。用`vector`存间隙长度并排序，数学证明时间复杂度O(n log n)最优  
   💡 **学习笔记**：排序预处理是贪心算法的黄金搭档

3. **难点3：边界条件处理**  
   *分析*：三种特殊情况：  
   - 全L时：首个W仅+1分 → `k=0输出0`  
   - 可全改W时：得分=`2n-1`  
   - 首尾间隙：填充时不减少段数 → 单独处理  
   💡 **学习笔记**：边界是代码健壮性的试金石

✨ **解题技巧总结**  
- **技巧1：公式先行**：先数学推导得分模型再编码  
- **技巧2：间隙分类**：中间段(连接两W) vs 首尾段  
- **技巧3：贪心验证**：小间隙优先填，填满即停  

---

#### 4. C++核心代码实现赏析
**通用核心实现**  
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, k, cnt = 0; 
        string s; cin >> n >> k >> s;
        for (char c : s) if (c == 'W') cnt++;
        
        // 特例1：可全改W
        if (cnt + k >= n) { 
            cout << 2 * n - 1 << endl; 
            continue; 
        }
        
        // 计算初始得分
        int score = 0, lastW = -1;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'W') {
                score += (i > 0 && s[i-1] == 'W') ? 2 : 1;
            }
        }

        // 记录间隙并排序
        vector<int> gaps;
        for (int i = 0, p = -1; i < n; i++) {
            if (s[i] == 'W') {
                if (p != -1 && i - p > 1) 
                    gaps.push_back(i - p - 1);
                p = i;
            }
        }
        sort(gaps.begin(), gaps.end());

        // 填充间隙
        for (int gap : gaps) {
            if (k >= gap) {
                k -= gap;
                score += 2 * gap + 1; // 填满段额外+1
            } else break;
        }
        score += 2 * k; // 处理剩余操作
        cout << score << endl;
    }
    return 0;
}
```
**代码解读概要**：  
1. 特例处理全W场景  
2. 遍历计算初始得分（核心：连续W判断）  
3. 间隙探测：用`p`标记上一个W位置  
4. 贪心填充：小间隙优先，每填满段触发`+1`奖励  
5. 剩余操作直接加`2×k`分

---

#### 5. 算法可视化：像素动画演示
**主题**：《像素贪吃蛇：连胜之路》  
**核心演示**：  
```mermaid
graph LR
    A[8位像素网格] --> B[W=黄块 L=灰块]
    B --> C[间隙高亮闪烁]
    C --> D[填充时播放'叮'声]
    D --> E[连接两段时触发闪光]
```

**动画流程**：  
1. **初始化**：FC风格界面，控制面板含速度滑块/单步/自动演示  
2. **间隙标记**：W间灰块变紫闪烁，长度数字悬浮显示  
3. **吞噬动画**：  
   - 自动模式：蛇形移动吞噬小间隙（每秒2步）  
   - 单步模式：按空格键逐步执行  
   - 音效：吞噬时"叮"，连接成功时"胜利旋律"  
4. **得分反馈**：实时显示分数增长（`+2`/+3`飘字特效）  
5. **终局庆祝**：全屏黄色闪烁 + 8-bit胜利BGM  

**设计意义**：像素块具象化段合并过程，音效强化操作记忆，游戏化提升理解乐趣

---

#### 6. 拓展练习与相似问题思考
**通用技巧迁移**：  
间隙处理贪心法适用于：  
1. 区间合并问题（如线段覆盖）  
2. 资源分配优化（如CPU任务调度）  
3. 路径压缩（如并查集优化）  

**洛谷推荐**：  
1. **P1090 合并果子**  
   🗣️ 巩固贪心排序思想，理解"小成本优先"本质  
2. **P1223 排队接水**  
   🗣️ 强化贪心策略证明能力，学习时间复杂度优化  
3. **P1803 线段覆盖**  
   🗣️ 进阶训练间隙处理，掌握右端点排序技巧  

---

#### 7. 学习心得与经验分享
> **经验摘录**："初始全L时，首W仅得1分——这个特例让我WA了3次"  
> **Kay点评**：调试时极端数据测试至关重要！建议：  
> 1. 全L（k=0/k>0）  
> 2. 单字符  
> 3. 无间隙连续W  

---

### 结语  
通过贪心策略将复杂问题转化为间隙填充模型，是本题精髓。记住：好算法=精准建模+严谨边界处理+可视化验证！下次挑战见！🚀

---
处理用时：206.01秒