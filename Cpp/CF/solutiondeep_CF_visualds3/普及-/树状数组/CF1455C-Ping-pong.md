# 题目信息

# Ping-pong

## 题目描述

Alice and Bob play ping-pong with simplified rules.

During the game, the player serving the ball commences a play. The server strikes the ball then the receiver makes a return by hitting the ball back. Thereafter, the server and receiver must alternately make a return until one of them doesn't make a return.

The one who doesn't make a return loses this play. The winner of the play commences the next play. Alice starts the first play.

Alice has $ x $ stamina and Bob has $ y $ . To hit the ball (while serving or returning) each player spends $ 1 $ stamina, so if they don't have any stamina, they can't return the ball (and lose the play) or can't serve the ball (in this case, the other player serves the ball instead). If both players run out of stamina, the game is over.

Sometimes, it's strategically optimal not to return the ball, lose the current play, but save the stamina. On the contrary, when the server commences a play, they have to hit the ball, if they have some stamina left.

Both Alice and Bob play optimally and want to, firstly, maximize their number of wins and, secondly, minimize the number of wins of their opponent.

Calculate the resulting number of Alice's and Bob's wins.

## 说明/提示

In the first test case, Alice serves the ball and spends $ 1 $ stamina. Then Bob returns the ball and also spends $ 1 $ stamina. Alice can't return the ball since she has no stamina left and loses the play. Both of them ran out of stamina, so the game is over with $ 0 $ Alice's wins and $ 1 $ Bob's wins.

In the second test case, Alice serves the ball and spends $ 1 $ stamina. Bob decides not to return the ball — he loses the play but saves stamina. Alice, as the winner of the last play, serves the ball in the next play and spends $ 1 $ more stamina. This time, Bob returns the ball and spends $ 1 $ stamina. Alice doesn't have any stamina left, so she can't return the ball and loses the play. Both of them ran out of stamina, so the game is over with $ 1 $ Alice's and $ 1 $ Bob's win.

In the third test case, Alice serves the ball and spends $ 1 $ stamina. Bob returns the ball and spends $ 1 $ stamina. Alice ran out of stamina, so she can't return the ball and loses the play. Bob, as a winner, serves the ball in the next $ 6 $ plays. Each time Alice can't return the ball and loses each play. The game is over with $ 0 $ Alice's and $ 7 $ Bob's wins.

## 样例 #1

### 输入

```
3
1 1
2 1
1 7```

### 输出

```
0 1
1 1
0 7```

# AI分析结果


### 💡 Kay的C++算法解析：Ping-pong 深入学习指南 💡

#### 题目解读与核心算法识别
✨ **本题主要考察**：`策略优化`  
🗣️ **初步分析**：
> 本题本质是策略博弈问题，如同两位棋手对弈，每一步都选择最有利的走法。Alice和Bob的目标都是**最大化自身胜场**并**最小化对手胜场**。核心策略在于：Bob会故意放弃前(x-1)个回合保存体力，在Alice体力耗尽时反击获胜，随后用剩余体力连续得分。
> - **核心难点**：理解为什么Alice只能赢(x-1)场而Bob能赢y场？关键在于Bob的"战略性放弃"策略。
> - **可视化设计**：像素动画将展示Alice发球→Bob放弃/回击的决策过程，体力条实时更新，关键决策点触发音效（放弃：低沉音；回击：清脆音）。
> - **复古游戏化**：采用FC红白机风格，Alice和Bob化为像素小人，球桌顶部显示体力条。每回合生成"策略选择界面"，Bob放弃时显示"SAVE"图标，回击时显示"ATTACK"动画。

---

#### 精选优质题解参考
**题解一（Thomas_Cat）**  
* **点评**：思路直击本质——通过分析发球权转换和体力消耗，直接推导出公式`(x-1, y)`。代码简洁规范（变量名`a,b`清晰），实践价值极高（可直接用于竞赛）。亮点在于用数学归纳法证明结论，帮助理解策略必然性。

**题解二（Tenshi）**  
* **点评**：通过具体案例（如a=100,b=3）生动演示策略，极具启发性。代码同样高效规范，突出"保存体力"的核心思想。亮点是用体育类比（"毫无体育精神但有效"）加深理解。

**题解三（想不好名字）**  
* **点评**：详细拆解比赛阶段（发球→回击→胜负判定），逻辑清晰。代码完整包含边界处理，特别强调"Alice最后一球必败"的关键点，对初学者友好。

---

#### 核心难点辨析与解题策略
1. **难点1：为何Alice只能赢(x-1)场？**  
   * **分析**：Alice作为首局发球方，前(x-1)局中Bob最优策略是放弃→让Alice消耗体力且无法转换发球权。
   * 💡 **学习笔记**：首局发球方实际处于被动，胜利数=体力值-1。

2. **难点2：为何Bob能赢y场？**  
   * **分析**：Bob在Alice体力=1时回击使其失败，夺得发球权后，Alice无体力回击，Bob连胜(y-1)局，加上首局胜利共y场。
   * 💡 **学习笔记**：后手方可通过"精准反击"实现体力价值最大化。

3. **难点3：如何证明策略最优？**  
   * **分析**：若Bob提前回击，会消耗体力导致后续胜场减少；若Alice保留体力，则直接丧失胜利机会。
   * 💡 **学习笔记**：博弈中"延迟满足"往往是最优策略。

### ✨ 解题技巧总结
- **策略模拟法**：用小规模数据（如x=2,y=1）推演过程
- **关键状态识别**：发球权转换和体力枯竭点为胜负关键
- **数学归纳**：从特例推导通用公式`(x-1, y)`

---

#### C++核心代码实现赏析
**通用核心代码**  
```cpp
#include <iostream>
using namespace std;
int main() {
    int t, x, y;
    cin >> t;
    while (t--) {
        cin >> x >> y;
        cout << x-1 << " " << y << endl;
    }
    return 0;
}
```
* **说明**：综合优质题解的最简实现，时间复杂度O(t)
* **解读概要**：  
  1. 读取测试数据量`t`  
  2. 对每组数据：  
     - 读Alice体力`x`、Bob体力`y`  
     - 直接输出公式结果`(x-1, y)`

**题解一（Thomas_Cat）片段**  
```cpp
while(t--){
    int a,b;
    cin>>a>>b;
    cout<<a-1<<' '<<b<<endl;
}
```
* **亮点**：用最简代码实现核心公式
* **解读**：  
  > `a-1`对应Alice胜场：她需保留1体力应对发球义务  
  > `b`对应Bob胜场：他可在最佳时机使用全部体力  
* 💡 **学习笔记**：复杂博弈可能蕴含极简数学解

---

### 算法可视化：像素动画演示
![](https://via.placeholder.com/800x400/000000/FFFFFF?text=Pixel+Animation+Preview)  
* **主题**：FC红白机风格《策略乒乓球》  
* **核心演示**：Bob的"保存体力→精准反击"策略  

**动画关键帧**：  
1. **初始化**（8-bit音效）：  
   - 像素球桌分割为Alice(红)/Bob(蓝)区域  
   - 顶部体力条：Alice[x] ▮▮▮... Bob[y] ▮▮▮...

2. **Alice发球阶段**：  
   - 前(x-1)球：Bob头顶显示"❌放弃"（低沉音效），Alice分数+1  
   - 第x球：Bob头顶显示"💥回击"（清脆音效），球拍击球动画  

3. **胜负翻转**：  
   - Alice体力枯竭→角色变灰，Bob得分+1  
   - 发球权移交Bob，触发"🚩发球权转换"动画  

4. **Bob连胜**：  
   - 剩余(y-1)球：Alice静止，Bob直接得分（连续得分触发Combo音效）  

**交互设计**：  
- **控制面板**：步进执行▶️/调速滑块⏱️/AI自动演示🤖  
- **游戏化元素**：  
  - 每赢1球得10分，完美策略奖励"💯战术大师"成就  
  - 通关动画：Bob举起像素奖杯，播放8-bit胜利音乐  

---

### 拓展练习与相似问题
**通用技巧迁移**：  
1. 回合制资源管理（如卡牌游戏法力优化）  
2. 博弈论中的"后手优势"场景  
3. 状态转换型问题（如自动机模型）  

**洛谷推荐**：  
1. **P1288 取数游戏II**  
   → 分析：同样存在"最优路径选择"策略  
2. **P1199 三国游戏**  
   → 分析：多人博弈中的联盟策略  
3. **P1247 取火柴游戏**  
   → 分析：经典Nim博弈，强化策略思维  

---

### 学习心得与经验分享
> **Tenshi的调试经验**：  
> *"最初用动态规划过度复杂化问题，后通过小规模模拟（x=2,y=1）发现规律"*  
>  
> **Kay点评**：  
> 这印证了重要原则：  
> 1. 先尝试小规模暴力模拟  
> 2. 观察输入输出寻找隐藏规律  
> 3. 避免对简单问题过度工程化  

---

通过本次分析，我们揭示了博弈问题的核心思维：**最优策略往往隐藏在状态转换的临界点**。记住：在编程竞赛中，数学洞察力有时比复杂算法更重要！下次遇到类似问题，不妨先拿起纸笔模拟小规模场景哦~ 🎮

---
处理用时：121.91秒