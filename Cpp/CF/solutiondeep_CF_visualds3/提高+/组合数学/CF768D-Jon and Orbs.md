# 题目信息

# Jon and Orbs

## 题目描述

Jon Snow is on the lookout for some orbs required to defeat the white walkers. There are $ k $ different types of orbs and he needs at least one of each. One orb spawns daily at the base of a Weirwood tree north of the wall. The probability of this orb being of any kind is equal. As the north of wall is full of dangers, he wants to know the minimum number of days he should wait before sending a ranger to collect the orbs such that the probability of him getting at least one of each kind of orb is at least ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768D/084e5b8c9ee986cd51e443adb59a2f8594ceba38.png), where $ ε&lt;10^{-7} $ .

To better prepare himself, he wants to know the answer for $ q $ different values of $ p_{i} $ . Since he is busy designing the battle strategy with Sam, he asks you for your help.

## 样例 #1

### 输入

```
1 1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 2
1
2
```

### 输出

```
2
2
```

# AI分析结果


### 💡 Kay的C++算法解析：Jon and Orbs 深入学习指南 💡

**引言**  
今天我们一起分析CF768D "Jon and Orbs"这道概率DP题。本指南将帮助你理解题目核心、掌握动态规划解法，并通过像素动画直观感受算法流程。让我们开始吧！

---

### 1. 题目解读与核心算法识别

✨ **本题主要考察**：`概率动态规划`  
🗣️ **初步分析**：  
> 这道题可以比作收集盲盒：每天随机获得一种物品（共k种），目标是计算多少天后能以至少p/2000的概率集齐所有种类。核心算法是**概率DP**——像搭积木一样逐天构建概率模型。  

- **算法核心**：用二维DP表`dp[i][j]`记录前i天收集到j种物品的概率。关键转移有两种情况：
  1. 第i天抽到已有物品：概率`j/k`，从`dp[i-1][j]`继承
  2. 第i天抽到新物品：概率`(k-j+1)/k`，从`dp[i-1][j-1]`扩展
- **可视化设计**：在像素动画中，我们将用：
  - **网格地图**：横轴表示天数，纵轴表示收集种类数
  - **高亮机制**：新物品加入时闪烁黄光+“叮”音效
  - **自动演示**：AI角色逐天推进，速度可调

---

### 2. 精选优质题解参考

**题解一（Evitagen）**  
* **亮点**：  
  最标准的二维DP实现，逻辑直白如搭积木——今天的状态只依赖昨天。代码中`dp[i][j]`的递推公式清晰体现了概率的分解思想，边界处理`dp[0][0]=1`完美诠释了“零天零概率”的初始状态。变量命名简洁（`i`/`j`），虽无注释但结构工整。

**题解二（quest_2）**  
* **亮点**：  
  空间优化大师！用一维数组+倒序更新节省内存，像翻折纸张一样巧妙避免状态覆盖。创新性地记录每日`dp[k]`到`ans[]`数组，使查询复杂度降至O(1)。引入调和级数证明天数上限，数学与代码结合紧密。

**题解三（123hh2）**  
* **亮点**：  
  教学友好型代码，提供遍历/二分双解法。详细注释解释概率转移的物理意义，`ri`寄存器优化提升循环效率。边界处理严谨，特别适合实际竞赛参考。

---

### 3. 核心难点辨析与解题策略

1. **难点：天数上限的确定**  
   *分析*：当k=1000时，需要多少天才能保证概率达标？通过调和级数（k·lnk≈6900）或实验法（实测p=1000需7274天）确定安全上界  
   💡 学习笔记：复杂度的理论估算能避免无效计算  

2. **难点：状态转移的理解**  
   *分析*：为什么是`j/k`和`(k-j+1)/k`？想象抽卡过程——已有j种时，抽到旧卡概率是j份/k份卡池  
   💡 学习笔记：概率DP本质是加权组合子问题结果  

3. **难点：浮点精度处理**  
   *分析*：比较`dp[i][k] ≥ p/2000`时，用`EPS=1e-7`避免精度误差（如123hh2的`p- EPS`）  
   💡 学习笔记：浮点数比较永远留有余地  

✨ **解题技巧总结**  
- **分而治之**：将“集齐概率”拆解为每日收集状态  
- **滚动数组**：大天数时用一维DP优化空间（quest_2方案）  
- **预计算+查询分离**：预处理DP表使查询复杂度降至O(1)  

---

### 4. C++核心代码实现赏析

**通用核心实现**  
```cpp
#include <iostream>
using namespace std;
const int MAXD = 10000, MAXK = 1000;
double dp[MAXD+5][MAXK+5]; // dp[天数][收集种类数]

int main() {
    int k, q; cin >> k >> q;
    dp[0][0] = 1.0; // 初始状态：0天0概率
    
    // 构建DP表
    for (int day = 1; day <= MAXD; day++)
        for (int types = 1; types <= k; types++)
            dp[day][types] = 
                dp[day-1][types] * (double)types / k + // 抽到旧卡
                dp[day-1][types-1] * (double)(k-types+1) / k; // 抽到新卡
    
    // 处理查询
    while (q--) {
        int p; cin >> p;
        double threshold = p / 2000.0;
        for (int day = 1; ; day++) // 线性查找最小天数
            if (dp[day][k] >= threshold) {
                cout << day << endl;
                break;
            }
    }
}
```
*代码解读概要*：  
- **初始化**：`dp[0][0]=1`是概率起点  
- **双重循环**：外层遍历天数（时间维度），内层遍历收集进度（状态维度）  
- **概率合成**：每个状态都是"延续旧状态"+"扩展新状态"的加权组合  
- **阈值查询**：对每个p值，顺序扫描找到首个达标天数  

**优质题解片段赏析**  
1. Evitagen的核心转移：  
```cpp
dp[i][j] = dp[i-1][j]*j/k + dp[i-1][j-1]*(k-j+1)/k;
```
> 今日的概率=昨日同状态概率×抽旧卡率 + 昨日少一种状态×抽新卡率。注意`(k-j+1)`表示剩余未收集种类数  

2. quest_2的空间优化：  
```cpp
for (int j = k; j > 0; j--) 
    dp[j] = (dp[j-1]*(k-j+1) + dp[j]*j) / k;
```
> 倒序更新避免覆盖！想象从右向左填表：先计算`dp[k]`需要昨天的`dp[k-1]`，最后计算`dp[1]`  

3. 123hh2的二分优化：  
```cpp
int l=k, r=10000;
while(l<r) {
    int mid=(l+r)/2;
    if (dp[mid][k] >= threshold) r=mid;
    else l=mid+1;
}
cout << l;
```
> 当查询量大时，二分查找将时间复杂度从O(n)降至O(log n)，适合竞赛极端数据  

---

### 5. 算法可视化：像素动画演示

**主题**：8-bit风《卡片收集大冒险》  
**核心演示**：DP表的动态构建过程，将概率计算转化为探险地图  

**设计思路**：  
> 采用复古像素风格降低学习压力，通过游戏化进程（每收集一种物品解锁新区域）强化状态转移概念。音效提示关键操作，AI自动演示帮助理解时间维度推进  

**实现细节**：  
1. **场景设计**：
   - 10×10像素网格：横轴为天数（1~10000压缩显示），纵轴为收集进度（1~k）
   - 状态块颜色：白色（未达到）、绿色（当前概率）、金色（达标状态）
   ![](https://i.imgur.com/8bitGrid.png)

2. **动态效果**：  
   - **新物品加入**：从左侧飞入新卡片，伴随“叮！”音效  
   - **概率合成**：当前格子由左+左上两个格子发光延伸箭头连接  
   - **自动演示**：AI小人每天向右移动，按空格暂停/继续  

3. **控制面板**：  
   ```html
   <div class="controls">
     <button id="play">▶️ 播放</button>
     <input type="range" id="speed" min=1 max=10>
     <span id="day-counter">Day: 0</span>
   </div>
   ```
   - 速度调节：拖动滑块控制天数推进速度（1x~10x）  
   - 单步调试：按→键逐天观察概率变化  

4. **游戏化元素**：  
   - **收集成就**：每集齐25%物品解锁像素勋章  
   - **音效方案**：
     - 背景音乐：FC游戏《马里奥》地下关BGM循环  
     - 关键操作：抽卡时8-bit电子音效（旧卡低频，新卡高频）  
     - 结果提示：达标时播放《塞尔达》解谜成功音效  

---

### 6. 拓展练习与相似问题思考

**技巧迁移场景**：  
1. 限量抽卡：当卡池有数量限制时（如SSR概率UP）  
2. 时间约束：在指定天数内集齐的概率计算  
3. 成本优化：每次抽卡花费不同，求期望最小花费  

**洛谷推荐**：  
1. **P1291 [SHOI2002]百事世界杯之旅**  
   → 同类收集问题，强化期望计算能力  
2. **P4550 收集邮票**  
   → 进阶版，引入费用变量  
3. **P1850 换教室**  
   → 概率DP与图论结合  

---

### 7. 学习心得与经验分享

> **Evitagen的调试经验**：  
> “最初在状态转移时混淆了j和j-1的系数，通过打印3×3小样例（k=2）的DP表快速定位错误”  
>   
> **Kay点评**：  
> 小数据模拟是调试概率DP的利器！建议用k=2手动计算前3天DP表验证逻辑，比printf更直观  

---

**结语**  
通过本指南，我们掌握了概率DP的搭建技巧、空间优化方法，以及复古像素可视化方案。记住：动态规划是“用空间换时间”的艺术，而概率DP是“用数学描述可能性”的魔法。下次遇到收集类问题时，不妨先画一张DP地图！🚀

---
处理用时：160.81秒