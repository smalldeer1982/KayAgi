# 题目信息

# [USACO07NOV] Sunscreen G

## 题目描述

To avoid unsightly burns while tanning, each of the C (1 ≤ C ≤ 2500) cows must cover her hide with sunscreen when they're at the beach. Cow i has a minimum and maximum SPF rating (1 ≤ minSPFi ≤ 1,000; minSPFi ≤ maxSPFi ≤ 1,000) that will work. If the SPF rating is too low, the cow suffers sunburn; if the SPF rating is too high, the cow doesn't tan at all........

The cows have a picnic basket with L (1 ≤ L ≤ 2500) bottles of sunscreen lotion, each bottle i with an SPF rating SPFi (1 ≤ SPFi ≤ 1,000). Lotion bottle i can cover coveri cows with lotion. A cow may lotion from only one bottle.

What is the maximum number of cows that can protect themselves while tanning given the available lotions?

有C个奶牛去晒太阳 (1 <=C <= 2500)，每个奶牛各自能够忍受的阳光强度有一个最小值和一个最大值，太大就晒伤了，太小奶牛没感觉。

而刚开始的阳光的强度非常大，奶牛都承受不住，然后奶牛就得涂抹防晒霜，防晒霜的作用是让阳光照在身上的阳光强度固定为某个值。

那么为了不让奶牛烫伤，又不会没有效果。

给出了L种防晒霜。每种的数量和固定的阳光强度也给出来了

每个奶牛只能抹一瓶防晒霜，最后问能够享受晒太阳的奶牛有几个。


## 样例 #1

### 输入

```
3 2
3 10
2 5
1 5
6 2
4 1```

### 输出

```
2```

# AI分析结果


### 💡 Kay的C++算法解析：Sunscreen G 深入学习指南 💡

> 今天我们来分析USACO07NOV的"Sunscreen G"题目。这道题考察如何为奶牛分配防晒霜以最大化享受阳光的奶牛数量。本指南将帮助你掌握贪心算法的核心思想与实现技巧，并通过像素动画直观理解算法执行过程。

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`贪心算法` (区间覆盖类问题)

🗣️ **初步分析**：
> 我们可以把每头奶牛看作一条区间[minSPF, maxSPF]，防晒霜看作点值SPF。问题转化为：如何用给定的点覆盖最多的区间？贪心算法就像聪明的园丁，优先处理最难满足的花朵。

- **核心思路**：两种主流贪心策略：
  1. 奶牛按minSPF降序排序 + 防晒霜按SPF降序排序（优先满足要求高的奶牛）
  2. 奶牛按maxSPF升序排序 + 防晒霜按SPF升序排序（优先满足要求宽松的奶牛）
- **算法流程**：
  - 排序预处理
  - 双重循环匹配：对每头奶牛寻找可用防晒霜
  - 匹配成功则消耗防晒霜并计数
- **可视化设计**：在像素动画中将奶牛显示为彩色区间条，防晒霜显示为光点。匹配时高亮区间和光点，播放"叮"音效。奶牛匹配后变为笑脸，防晒霜减少时显示数字变化。

---

## 2. 精选优质题解参考

### 题解一：翼德天尊（赞167）
* **亮点**： 
  - 用生动的反例证明按右端点(maxSPF)排序的正确性
  - 代码规范（变量名`cow[i].a/b`清晰，边界处理严谨）
  - 实践价值高：30行完整实现，可直接用于竞赛
  > "反例证明：三条线段[1,6]、[2,3]、[3,4]与防晒霜3和5。按左端点排序只能匹配1头，按右端点排序可匹配2头"

### 题解二：陷语（赞16）
* **亮点**：
  - 严谨证明贪心策略（按minSPF降序+选最大SPF）
  - 解释变量作用：`b[j].a`存储SPF值，`b[j].b`存储数量
  > "选择SPF最大的防晒霜：若两瓶都符合，大的SPF更可能被浪费，应优先使用"

### 题解三：RoRoyyy（赞2）
* **亮点**：
  - 使用平衡树(map)优化到O(n log n)
  - 将防晒霜存入map自动排序，通过`lower_bound`快速匹配
  > "核心技巧：用map的自动排序特性，通过`lower_bound`找到≤maxSPF的最大SPF值"

---

## 3. 核心难点辨析与解题策略

### 难点1：排序策略的选择
* **分析**：两种排序策略均可，但按minSPF降序更易理解。关键是将奶牛和防晒霜按相同规则排序（同升/同降），确保可比较性
* 💡 **学习笔记**：排序是贪心的灵魂，方向决定效率

### 难点2：匹配效率优化
* **分析**：双重循环O(n²)在2500数据下可接受，但可用优先队列优化。将奶牛按minSPF排序后，用堆维护可用防晒霜
* 💡 **学习笔记**：当n较大时，优先队列/平衡树可提升效率

### 难点3：边界条件处理
* **分析**：需注意防晒霜数量为0时跳过，奶牛无可用防晒霜时跳过
* 💡 **学习笔记**：每次匹配后break避免重复使用奶牛

### ✨ 解题技巧总结
- **问题转化**：将生物问题抽象为区间覆盖模型
- **贪心选择**：优先处理约束强的元素（高minSPF奶牛）
- **调试技巧**：打印中间匹配过程，验证排序正确性

---

## 4. C++核心代码实现赏析

**通用核心实现**（按minSPF降序）：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 2505;

struct Cow { int minSPF, maxSPF; };
struct Lotion { int SPF, cover; };

bool cmpCow(Cow a, Cow b) { return a.minSPF > b.minSPF; }
bool cmpLotion(Lotion a, Lotion b) { return a.SPF > b.SPF; }

int main() {
    int C, L, ans = 0;
    Cow cows[MAXN]; Lotion lotions[MAXN];
    // 输入数据
    sort(cows, cows + C, cmpCow);
    sort(lotions, lotions + L, cmpLotion);
    
    for (int i = 0; i < C; i++) {
        for (int j = 0; j < L; j++) {
            if (lotions[j].cover > 0 
                && lotions[j].SPF >= cows[i].minSPF 
                && lotions[j].SPF <= cows[i].maxSPF) {
                lotions[j].cover--;
                ans++;
                break;
    } } }
    cout << ans;
}
```

**题解一核心片段赏析**（翼德天尊）：
```cpp
sort(cow+1, cow+c+1, cmp); // 按maxSPF升序
sort(fss+1, fss+l+1, cmp1); // 按SPF升序
for (int i=1; i<=c; i++) {
    for (int j=1; j<=l; j++) {
        if (fss[j].b>0 && fss[j].a>=cow[i].a 
            && fss[j].a<=cow[i].b) {
            fss[j].b--, ans++;
            break;
} } }
```
> **解读**： 
> - 外层循环遍历每头牛
> - 内层循环查找第一个可用的防晒霜
> - `break`确保每头牛只用一瓶
> 💡 **学习笔记**：升序排序时，找到即退出避免浪费

---

## 5. 算法可视化：像素动画演示

![](https://cdn.luogu.com.cn/upload/image_hosting/hreks9kl.png)

* **主题**：牧场防晒霜分配大作战（8位像素风格）
* **核心演示**：
  1. 左侧：奶牛队列（按minSPF降序排列，显示[min,max]区间条）
  2. 右侧：防晒霜架（按SPF降序排列，显示SPF值和剩余瓶数）
  3. 匹配动画：
     - 当前奶牛闪烁黄色边框
     - 合格防晒霜显示绿色光晕
     - 选中时播放"叮"音效，奶牛变笑脸
* **交互控制**：
  - 步进/自动模式（速度可调）
  - 实时数据显示：已匹配奶牛数
* **游戏化设计**：
  - 成功匹配：+10分，播放欢快音效
  - 匹配失败：奶牛哭泣，播放提示音
  - 关卡设计：每5头牛为一个小关，过关放烟花

---

## 6. 拓展练习与相似问题

* **通用技巧迁移**：
  1. 区间覆盖问题（如任务调度）
  2. 资源分配问题（如会议室安排）
  3. 二分图匹配问题

* **洛谷推荐**：
  1. P2883 [USACO07MAR]Tilting Cows  
     > 同类区间覆盖问题，巩固贪心思路
  2. P2949 [USACO09OPEN]Work Scheduling  
     > 强化贪心+优先队列的应用
  3. P1230 智力大冲浪  
     > 变形题：带惩罚的任务调度

---

## 7. 学习心得与经验分享

> **翼德天尊的调试经验**：  
> "最初用左端点排序只能过样例，通过构造[1,6][2,3][3,4]的反例才发现排序问题"
>
> **Kay总结**：构造极端测试数据是验证算法正确性的关键。建议用：  
> - 全区间相同的数据  
> - 完全无交集的数据  
> - 完全包含的数据  

---

通过本次分析，我们掌握了区间覆盖类问题的贪心解法核心。记住：好的排序策略是成功的一半，而可视化调试能帮你直观理解算法本质。继续加油！💪

---
处理用时：130.10秒