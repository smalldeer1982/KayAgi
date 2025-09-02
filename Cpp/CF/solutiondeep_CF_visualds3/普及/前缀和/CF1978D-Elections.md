# 题目信息

# Elections

## 题目描述

Elections are taking place in Berland. There are $ n $ candidates participating in the elections, numbered from $ 1 $ to $ n $ . The $ i $ -th candidate has $ a_i $ fans who will vote for him. Additionally, there are $ c $ people who are undecided about their favorite candidate, let's call them undecided. Undecided people will vote for the candidate with the lowest number.

The candidate who receives the maximum number of votes wins the elections, and if multiple candidates receive the same maximum number of votes, the candidate with the lowest number among them wins.

You found these elections too boring and predictable, so you decided to exclude some candidates from them. If you do not allow candidate number $ i $ to participate in the elections, all $ a_i $ of his fans will become undecided, and will vote for the candidate with the lowest number.

You are curious to find, for each $ i $ from $ 1 $ to $ n $ , the minimum number of candidates that need to be excluded from the elections for candidate number $ i $ to win the elections.

## 说明/提示

In the first test case:

- If all candidates are allowed, candidate number $ 1 $ will receive $ 3 $ votes ( $ 1 $ undecided person will vote for him), candidate number $ 2 $ will receive $ 0 $ votes, and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 1 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 0 $ .
- If candidate number $ 1 $ is not allowed, his $ 2 $ fans will become undecided. Then candidate number $ 2 $ will receive $ 3 $ votes ( $ 3 $ undecided people will vote for him) and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 2 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 1 $ .
- If candidates with numbers $ 1 $ and $ 2 $ are not allowed, candidate number $ 3 $ wins, so the answer for him is $ 2 $ .

In the second test case, candidate number $ 1 $ will win if candidate number $ 2 $ is not allowed to participate.

## 样例 #1

### 输入

```
5
3 1
2 0 3
2 3
0 10
5 3
5 4 3 2 1
4 5
3 10 7 1
6 0
2 2 2 3 3 3```

### 输出

```
0 1 2
1 0
0 1 2 3 4
1 0 2 3
1 1 2 0 4 5```

# AI分析结果


### 💡 Kay的C++算法解析：Elections 深入学习指南 💡

> 欢迎各位编程小将！今天我们一起挑战「选举」问题，学习如何用贪心策略高效解决竞赛难题。我会用像素游戏风格拆解算法，配合生动比喻帮助大家理解。准备好开始这场算法冒险了吗？🎮

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心策略 + 预处理优化（前缀和/后缀最大值）  
🗣️ **初步分析**：
> 选举问题就像一场像素塔防游戏：每个候选人是一座塔（高度=票数），c个未定选民是流动资源。贪心策略的核心是 **“精准爆破”** —— 为让特定塔最高，先炸掉前面所有塔（资源流向目标塔），再判断是否要炸后面最高的威胁塔。  
> - **题解思路**：所有优质解法都遵循 **“双阶段贪心”**：① 排除i前所有候选使票集中 ② 若i票数仍<后面最大值，则排除最大威胁者
> - **可视化设计**：像素塔高度动态增长（票数增加），爆破特效伴随8-bit音效。高亮 **“当前操作塔”** 和 **“最大威胁塔”** ，自动演示模式如塔防AI逐步通关
> - **复古元素**：FC红白机画风，塔爆破时像素粒子飞溅，过关时播放《超级玛丽》胜利音效

---

## 2. 精选优质题解参考

<eval_intro>
从思路清晰性、代码规范性和算法优化度三维度筛选，推荐以下3份≥4★题解：
</eval_intro>

**题解一（hh弟中弟）**  
* **亮点**：  
  ① **逻辑直白**：用`sum[i]`精准计算i获得的总票数  
  ② **后缀最大值优化**：`max[i]`高效定位后方威胁  
  ③ **边界严谨**：`max[n+1]=0`避免越界，竞赛级健壮性  
  ④ 变量名`st`巧妙标记首个最大值（避免重复计算）

**题解二（szh_AK_all）**  
* **亮点**：  
  ① **动态前缀和**：用`qian`变量替代数组，节省空间  
  ② **问题分析透彻**：逐步推导“为何必须排除前i-1人”  
  ③ **实战提示**：提醒注意比赛时间分配（作者赛时未完成）

**题解三（KSCD_）**  
* **亮点**：  
  ① **极致简洁**：单行三元表达式完成核心逻辑  
  ② **洞察本质**：直接比较`sum[i]`与全局最大值（非后缀最大值）  
  ③ **教学友好**：20行完整实现，适合初学者理解框架

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题需突破三重关卡，结合优质题解提炼破关秘籍：
</difficulty_intro>

1. **关卡1：如何确保目标候选人获得足够票数？**  
   * **破关分析**：必须排除所有编号更小的候选人！因为未定票永远流向 **最小编号存活者**（像素塔防中资源自动流向最左塔）。优质解用`前缀和`计算总票数：`sum[i]=a[1]+...+a[i]+c`
   * 💡 **学习笔记**：选票流向规则是贪心策略的基石，就像水流永远往低处走

2. **关卡2：如何快速判断后方威胁？**  
   * **破关分析**：排除前i-1人后，需O(1)时间判断i票数是否≥后方最大值。优质解用 **后缀最大值数组**：`max[i]=max(a[i],max[i+1])`（从后往前计算）
   * 💡 **学习笔记**：后缀最大值是处理“后方威胁”的雷达扫描器

3. **关卡3：如何最小化排除人数？**  
   * **破关分析**：当`sum[i] < max[i+1]`时，只需再排除 **后方最大值所在位置**（而非所有更大者）。因为排除该人后其票数会加到i上（此时i必成最大）
   * 💡 **学习笔记**：贪心不是蛮干——精准打击关键目标才是最优策略

### ✨ 解题技巧总结
<summary_best_practices>
从像素战场中提炼的通用作战手册：
</summary_best_practices>
- **🎯 贪心双阶段法**：集中资源（阶段1）→ 消灭关键威胁（阶段2）  
- **📊 预处理加速器**：前缀和/后缀最大值将O(n²)优化为O(n)  
- **⚠️ 边界防御工事**：首位候选人初始加c票，数组边界设防护值（如`max[n+1]=0`）  
- **🔍 变量追踪术**：用`st`标记首个最大值，避免同一最大值多次处理

---

## 4. C++核心代码实现赏析

<code_intro_overall>
先看战场全局布阵图——综合优质解法的通用实现：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：融合前缀和+后缀最大值的最佳实践，完整展示贪心双阶段策略
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; long long c;
        cin >> n >> c;
        vector<long long> a(n+1), sum(n+1), suf_max(n+2);
        
        // 核心初始化：首位加c票
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            if (i == 1) a[i] += c;
            sum[i] = sum[i-1] + a[i]; // 前缀和计算
        }

        // 后缀最大值雷达扫描（从后往前）
        suf_max[n+1] = 0;
        for (int i = n; i >= 1; --i) 
            suf_max[i] = max(a[i], suf_max[i+1]);

        // 定位全局最大值（冠军候选人）
        int win_id = 1;
        for (int i = 1; i <= n; ++i)
            if (a[i] > a[win_id]) win_id = i;

        // 贪心双阶段作战
        for (int i = 1; i <= n; ++i) {
            if (i == win_id) cout << 0 << " ";      // 已是冠军
            else if (sum[i] >= suf_max[i+1])        // 阶段1达标
                cout << i-1 << " ";
            else                                    // 需阶段2
                cout << i << " ";
        }
        cout << '\n';
    }
    return 0;
}
```
* **代码解读概要**：  
  > ① **战场布置**：`a[]`存储兵力（票数），`sum[]`为集中火力的弹药库（前缀和），`suf_max[]`是敌情雷达（后缀最大值）  
  > ② **擒贼先擒王**：定位初始冠军`win_id`（无需任何操作）  
  > ③ **双阶段作战**：对每个候选人i——先检查是否已是王（输出0）；再检查集中前i人火力后（`sum[i]`）能否压制后方（`suf_max[i+1]`）；若不能则追加精准打击（+1次排除）

---
<code_intro_selected>
现在拆解三位指挥官的精锐部队：
</code_intro_selected>

**题解一（hh弟中弟）**
* **亮点**：用`st`标记首个最大值，避免重复处理同一最大值
* **核心代码片段**：
```cpp
int st = 0;
for (int i = 1; i <= n; ++i) {
    if (a[i] == max[1] && st < max[1]) { // 首遇最大值
        cout << 0 << ' ';
        st = max[1]; // 标记已处理
    } else {
        int ans = i - 1;                 // 阶段1
        if (sum[i] < max[i + 1]) ans++;  // 阶段2
        cout << ans << ' ';
    }
}
```
* **代码解读**：  
  > `st`如同勋章系统——首次遇到最大值时授予冠军勋章（输出0），后续遇到相同值不再重复授勋。`max[1]`是全局最大兵力值，`sum[i]`是i集结的兵力。当i兵力<后方最大威胁(`max[i+1]`)时，需增派一次打击（ans++）
* 💡 **学习笔记**：用变量标记状态变化是避免重复计算的常用技巧

**题解二（szh_AK_all）**
* **亮点**：动态更新前缀和，节省内存空间
* **核心代码片段**：
```cpp
int qian = 0; // 动态弹药库
for (int i = 1; i <= n; ++i) {
    if (i == maxn) cout << 0;            // 已是冠军
    else if (a[i] + qian >= hou[i + 1])  // 当前兵力+弹药≥威胁
        cout << i - 1;
    else                                 // 弹药不足需增援
        cout << i;
    qian += a[i]; // 实时扩充弹药
    cout << " ";
}
```
* **代码解读**：  
  > `qian`是移动弹药车，随部队推进（i++）实时收集资源（`qian += a[i]`）。决策时直接计算 **当前兵力+已有弹药** 能否压制后方威胁（`hou[i+1]`）。优势在于 **免预处理**，用单变量替代前缀和数组
* 💡 **学习笔记**：动态更新替代预存储是空间优化的利刃

**题解三（KSCD_）**
* **亮点**：极致简洁的三元表达式
* **核心代码片段**：
```cpp
for (int i = 1; i <= n; ++i) 
    cout << (i == mx ? 0 : (s[i] >= a[mx] ? i - 1 : i)) << ' ';
```
* **代码解读**：  
  > 将双阶段贪心浓缩为 **三重决策链**：  
  > ① `i == mx` → 已是冠军？输出0  
  > ② `s[i] >= a[mx]` → 集结兵力≥原冠军？输出i-1  
  > ③ 否则输出i（需追加打击）  
  > 注意：此处用 **全局最大值**`a[mx]`替代后缀最大值，因排除最大威胁后i必成新冠军
* 💡 **学习笔记**：简洁代码源于深刻理解问题本质

---

## 5. 算法可视化：像素动画演示

<visualization_intro>
**🎮 游戏名称**：《像素选战：贪心指挥官》  
**🎯 核心演示**：双阶段贪心策略如何通过精准爆破助目标候选人逆转战局  
**🕹️ 设计思路**：用FC红白机像素风降低理解门槛，音效强化关键操作记忆（如爆破声=排除候选人，胜利音效=目标当选）
</visualization_intro>

### 🎞️ 动画帧步骤详解
1. **战场初始化（8-bit像素风）**  
   - 候选人 → 颜色各异的像素塔（高度=票数）  
   - 首位塔顶显示`+c`气泡，塔体闪烁（初始加成）  
   - 控制面板：▶️ 开始/⏸️ 暂停/⏩ 单步/🔄 重置/🎚️ 速度滑块

2. **阶段1：集结兵力（排除前i-1人）**  
   ```plaintext
   [ 塔1 ] → 爆炸动画 → 碎片飞向目标塔i → 目标塔增高
        旁白："排除1号！票数转移至5号塔！"
   ```
   - **特效**：被炸塔像素粒子化，目标塔生长动画 + “叮”音效  
   - **数据可视化**：目标塔顶显示`+X票`（X=转移票数）

3. **阶段2：歼灭威胁（排除后方最大值）**  
   ```plaintext
   扫描后方 → 最高威胁塔红色高亮 → 爆炸 → 碎片飞向目标塔
        旁白："检测到8号塔威胁！实施精准打击！"
   ```
   - **逻辑演示**：比较目标塔(当前高度)与威胁塔高度条  
   - **音效**：威胁警报声 → 爆炸声 → 目标塔增长声

4. **胜利判定**  
   - 目标塔成全场最高 → 放烟花 + 播放《超级玛丽》过关音效  
   - 显示：「候选人i获胜！排除人数：X」

5. **自动演示模式（AI指挥官）**  
   - 点击🤖按钮：自动按i=1~n演示，速度可调  
   - 每关结束显示：「第i关通关！★✩✩」（根据排除人数评分）  
   - **游戏化激励**：连续通关解锁像素勋章（如“贪心大师”）

### 🎨 技术实现关键
```javascript
// 伪代码：爆破特效实现
function explode(tower) {
  playSound("blast_8bit.wav");     // 爆破音效
  particles = createPixels(tower); // 塔像素化
  animate(particles.moveTo(targetTower)); 
  targetTower.height += tower.votes; 
}
```

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握贪心双阶段法后，你已获得攻克三类战略关卡的密钥：
</similar_problems_intro>

1. **资源调度问题**：在限定操作次数下最大化收益（如排除候选人=操作，票数=收益）  
2. **障碍清除问题**：最小代价移除障碍使目标达成（如排除候选人=清除障碍）  
3. **动态区间最值**：快速响应变化环境中的极值查询（如后缀最大值实时查询）

**🏹 洛谷实战推荐**：
1. **P1115 最大子段和**  
   → 🗣️ *用前缀和+贪心找连续区间最大和，巩固预处理技巧*  
2. **P1886 滑动窗口**  
   → 🗣️ *单调队列维护动态极值，升级版“后缀最大值”训练*  
3. **P1090 合并果子**  
   → 🗣️ *贪心策略经典应用，理解“优先消除最大威胁”本质*  

---

## 7. 学习心得与经验分享

<insights_intro>
摘录战场老兵的经验笔记，助你避开雷区：
</insights_intro>

> **经验1（CarroT1212）**  
> “后缀max一定要从后往前算！我比赛时从前往后算直接崩盘，痛失87分”  
> → 💡 **Kay点评**：预处理的方向决定成败！后缀操作必须 **逆序扫描**，这是铁律  

> **经验2（hh弟中弟）**  
> “C题比D题难？理解题意才是王道”  
> → 💡 **Kay点评**：竞赛中冷静审题比急于编码更重要，建议先手算样例验证理解  

---

<conclusion>
本次选战之旅到此结束！记住：贪心策略的精髓是 **“精准决策，不做多余操作”**。多练习前缀和/后缀最大值这对黄金组合，下次竞赛你也能成为贪心指挥官！🚀  
**→ 行动任务**：在洛谷P1115用今日所学实现最大子段和，评论区打卡你的战绩！
</conclusion>
```

---
处理用时：327.04秒