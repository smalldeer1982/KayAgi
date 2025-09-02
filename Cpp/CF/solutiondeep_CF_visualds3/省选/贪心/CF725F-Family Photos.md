# 题目信息

# Family Photos

## 题目描述

Alice and Bonnie are sisters, but they don't like each other very much. So when some old family photos were found in the attic, they started to argue about who should receive which photos. In the end, they decided that they would take turns picking photos. Alice goes first.

There are $ n $ stacks of photos. Each stack contains exactly two photos. In each turn, a player may take only a photo from the top of one of the stacks.

Each photo is described by two non-negative integers $ a $ and $ b $ , indicating that it is worth $ a $ units of happiness to Alice and $ b $ units of happiness to Bonnie. Values of $ a $ and $ b $ might differ for different photos.

It's allowed to pass instead of taking a photo. The game ends when all photos are taken or both players pass consecutively.

The players don't act to maximize their own happiness. Instead, each player acts to maximize the amount by which her happiness exceeds her sister's. Assuming both players play optimal, find the difference between Alice's and Bonnie's happiness. That is, if there's a perfectly-played game such that Alice has $ x $ happiness and Bonnie has $ y $ happiness at the end, you should print $ x-y $ .

## 样例 #1

### 输入

```
2
12 3 4 7
1 15 9 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
5 4 8 8
4 12 14 0
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1
0 10 0 10
```

### 输出

```
-10
```

# AI分析结果


### 💡 Kay的C++算法解析：Family Photos 深入学习指南 💡

---

#### **1. 题目解读与核心算法识别**
✨ **本题主要考察**：贪心策略 & 博弈论  
🗣️ **初步分析**：
> 照片争夺战就像下棋，Alice和Bonnie轮流行动，都想扩大自己的领先优势。关键在于**分类讨论+贪心排序**：
> - **核心思想**：每对照片根据双方收益分为"争夺类"（双方都想先取）和"被动类"（仅一方愿取）。就像分配糖果，双方会优先争夺最甜的糖果堆。
> - **解题脉络**：
>   1. 分类照片：计算每对照片的联合价值（a1+b1 vs a2+b2）
>   2. 争夺类：按价值总和排序后交替选取
>   3. 被动类：直接计算单方收益
> - **可视化设计**：像素动画将用不同颜色区分照片类型（绿=争夺类/黄=Alice主动类/蓝=Bonnie主动类），排序时展示冒泡过程，选取时触发8-bit音效（"叮"=Alice取，"咚"=Bonnie取）

---

#### **2. 精选优质题解参考**
**题解一（Wen_kr）**  
* **亮点**：四类分治逻辑严密，整数运算避免浮点误差。贡献值累加与数组减法设计巧妙，代码如精工机械般严丝合缝（变量命名`seq`/`cnt`精准，边界处理滴水不漏）  

**题解二（EuphoricStar）**  
* **亮点**：三类子情况划分更简洁，博弈动机阐释透彻。废片判定条件（双方收益均负）的发现如同战场排雷，大幅提升算法效率  

**题解三（Yuby）**  
* **亮点**：动态数组适配大数据量，索引映射（奇偶位）处理优雅。注意事项强调（"须先取第一张"）直击题意陷阱，如教练划重点  

---

#### **3. 核心难点辨析与解题策略**
1. **难点：价值比较的数学变形**  
   * **分析**：关键不等式 `a1-b2 ≥ a2-b1` 等价于 `a1+b1 ≥ a2+b2`，需通过代数推导理解博弈动机  
   * 💡 **学习笔记**：不等式变形是博弈问题的解题钥匙  

2. **难点：被动类照片的取舍判断**  
   * **分析**：当 `a1> b2` 时，即使Bonnie不配合，Alice仍可取第一张获得净收益（`a1-b2`），类似象棋中的"弃子争先"  
   * 💡 **学习笔记**：负收益操作要果断舍弃  

3. **难点：争夺类照片的排序策略**  
   * **分析**：贪心本质是让Alice拿价值高的照片（即使含对手收益）。排序后隔项相减（`ans -= seq[i]`）实现双方收益自动平衡  
   * 💡 **学习笔记**：排序是贪心算法的灵魂  

**✨ 解题技巧总结**  
- **分类讨论法**：将照片分为争夺类/被动类/废片三类处理  
- **贡献值拆解**：争夺类先加 `a1+a2` 后减排序值，避免状态转移  
- **整数防误差**：全程使用整型运算，杜绝浮点精度陷阱  

---

#### **4. C++核心代码实现赏析**
**通用核心实现**  
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 200050;

int main() {
    long long seq[MAXN], cnt = 0, ans = 0;
    int n; cin >> n;
    
    while(n--) {
        long long a1,b1,a2,b2;
        cin >> a1 >> b1 >> a2 >> b2;
        
        if(a1+b1 >= a2+b2) {       // 争夺类
            seq[cnt++] = a1+b1;
            seq[cnt++] = a2+b2;
            ans += a1 + a2;        // 先累加原始值
        }
        else if(a1 > b2) ans += a1 - b2;  // Alice被动取
        else if(b1 > a2) ans += a2 - b1;  // Bonnie被动取
    }
    
    sort(seq, seq + cnt);           // 关键排序
    for(int i=0; i<cnt; i+=2) ans -= seq[i]; // 隔项相减
    
    cout << ans;  // 最终差值
}
```
**代码解读概要**：  
> 争夺类照片的价值和存入数组，先累加原始值（`a1+a2`）再排序。隔项相减实现贪心分配：升序排列后，奇数位（小值）由Bonnie承担，偶数位（大值）归Alice

---

#### **5. 算法可视化：像素动画演示**
![像素动画示意图](https://example.com/pixel_anim.png)  
* **主题**：8-bit照片争夺战（FC游戏风格）  
* **核心机制**：  
  1. **动态上色**：争夺类(绿)/Alice类(黄)/Bonnie类(蓝)/废片(灰)  
  2. **排序过程**：冒泡算法可视化，数值大的像素块发光  
  3. **选取动画**：  
     - Alice取片：像素块左移 + "叮"声(三角波音效)  
     - Bonnie取片：像素块右移 + "咚"声(方波音效)  
  4. **控制面板**：  
     - 速度滑块：调节帧率（0.5x~2x）  
     - 单步执行：空格键触发单步  
     - 自动演示：AI贪吃蛇模式自动闯关  

* **关键帧设计**：  
  ```js
  // 伪代码示例
  function drawSelection(photo, player) {
    photo.highlight();          // 高亮当前照片
    playSound(player);         // 播放角色音效
    moveToPlayerArea(photo);   // 像素块平移动画
    updateScore(photo.value);  // 分数实时更新
  }
  ```

---

#### **6. 拓展练习与相似问题思考**
**通用套路迁移**：  
1. 资源交替分配问题（如CPU时间片调度）  
2. 零和博弈决策（如棋类游戏最优落子）  
3. 带约束的贪心选择（如背包问题变种）  

**洛谷推荐**：  
1. **P1080 国王游戏**（贪心排序经典）  
   → 巩固排序型贪心策略  
2. **P1090 合并果子**（堆优化贪心）  
   → 学习数据结构辅助贪心  
3. **P1005 矩阵取数游戏**（双人博弈DP）  
   → 进阶训练博弈决策思维  

---

#### **7. 学习心得与经验分享**
> 本次题解中未发现作者调试心得，但代码呈现三大智慧结晶：  
> 1. **分类讨论**是复杂问题的拆解利器  
> 2. **整数运算**避免浮点误差的工程思维  
> 3. **贡献值分离**简化状态转移的精妙设计  

---
**记住编程如对弈：看清局面，果断取舍，方能制胜！** 🎮🚀

---
处理用时：189.54秒