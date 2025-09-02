# 题目信息

# [USACO14JAN] Recording the Moolympics S

## 题目描述

Being a fan of all cold-weather sports (especially those involving cows),Farmer John wants to record as much of the upcoming winter Moolympics as possible.


The television schedule for the Moolympics consists of N different programs(1 <= N <= 150), each with a designated starting time and ending time.  FJ has a dual-tuner recorder that can record two programs simultaneously.

Please help him determine the maximum number of programs he can record in total.

农民约翰热衷于所有寒冷天气的运动（尤其是涉及到牛的运动）， 农民约翰想录下尽可能多的电视节目。 moolympics 的节目时间表有 $N$ 个不同的节目 （$1\le N\le 150$），每个节目给定开始时间和结束时间。FJ 有一个双调谐器录音机，可以同时录制两个节目。 请帮助他确定他能录制的节目的最大数量。


## 说明/提示

INPUT DETAILS:


The Moolympics broadcast consists of 6 programs.  The first runs from time 0 to time 3, and so on.


OUTPUT DETAILS:


FJ can record at most 4 programs.  For example, he can record programs 1 and 3 back-to-back on the first tuner, and programs 2 and 4 on the second tuner.


Source: USACO 2014 January Contest, Silver


## 样例 #1

### 输入

```
6
0 3
6 7
3 10
1 5
2 8
1 9```

### 输出

```
4```

# AI分析结果



## 算法分类
**贪心算法**

---

## 题解思路与核心难点
### 核心思路
1. **贪心策略**：按节目结束时间升序排序，优先处理结束早的节目。
2. **双调谐器维护**：维护两个调谐器的结束时间，每次尽可能将节目放入结束时间较大的调谐器中，保留较小的结束时间以适配后续节目。
3. **动态交换优化**：每次使用调谐器后交换顺序，确保优先级较高的调谐器始终保留较小的结束时间。

### 解决难点
- **正确选择调谐器**：通过动态交换调谐器顺序，保证优先处理结束时间较晚的调谐器，从而最大化后续节目安排的可能性。
- **证明贪心正确性**：需证明每次选择不影响全局最优解，通过保留较小的结束时间保证后续最优子结构。

---

## 题解评分（≥4星）
1. **shadowice1984（5星）**  
   - **亮点**：代码简洁高效，通过交换调谐器顺序优化选择逻辑，思路清晰易理解。
2. **BFSBFSBFSBFS（4星）**  
   - **亮点**：详细推导贪心策略的正确性，代码注释明确。
3. **A_Đark_Horcrux（4星）**  
   - **亮点**：结合经典贪心问题对比，代码实现简洁且附带双倍经验提示。

---

## 最优思路提炼
- **关键步骤**：  
  1. 按结束时间排序所有节目。  
  2. 维护两个变量 `t1` 和 `t2` 表示调谐器的结束时间。  
  3. 遍历节目，若当前节目可放入任一调谐器，则选择放入结束时间较大的调谐器，并交换调谐器顺序。  
- **代码片段**（shadowice1984的核心逻辑）：  
  ```cpp
  for(int i=0;i<n;i++) {
      if(now1<=mis[i].st) { // 放入第一调谐器
          res++;now1=mis[i].ed;
      } else if(now2<=mis[i].st) { // 放入第二调谐器
          res++;now2=mis[i].ed;
          swap(now1,now2); // 交换顺序优化
      }
  }
  ```

---

## 同类题目推荐
1. **P1803 凌乱的yyy/线段覆盖**（单调谐器基础贪心）  
2. **UVA1347 Tour**（双调谐器动态规划扩展）  
3. **P2970 自私的放牧**（相似贪心策略，单资源调度）

---

## 可视化与算法演示
### 动画设计
1. **排序过程**：以时间轴展示节目按结束时间排序后的顺序。  
2. **调谐器状态**：  
   - 用两条水平时间线表示 `t1` 和 `t2`，颜色区分（如红色和蓝色）。  
   - 当前处理节目高亮为黄色，若可放入调谐器，对应时间线延伸并播放音效。  
3. **交换操作**：当使用第二调谐器时，两条时间线颜色互换，体现优先级变化。  

### 复古像素风格
- **像素元素**：节目显示为绿色方块，调谐器时间线用8-bit风格箭头表示。  
- **音效设计**：  
  - 成功放置：短促“滴”声（Web Audio模拟FC音效）。  
  - 无法放置：低音“嘟”声。  
- **自动演示**：按空格键切换手动/自动模式，自动模式下算法逐步执行，速度可调。

---

## 核心代码实现
```cpp
#include <algorithm>
#include <stdio.h>
using namespace std;

struct Program { int st, ed; };
Program mis[155];
int now1 = -1, now2 = -1, res = 0;

bool cmp(Program a, Program b) { return a.ed < b.ed; }

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d", &mis[i].st, &mis[i].ed);
    sort(mis, mis + n, cmp); // 按结束时间排序
    for (int i = 0; i < n; i++) {
        if (now1 <= mis[i].st) { // 优先放入第一调谐器
            res++;
            now1 = mis[i].ed;
        } else if (now2 <= mis[i].st) { // 次选第二调谐器
            res++;
            now2 = mis[i].ed;
            swap(now1, now2); // 交换以保证下次优先处理较小的结束时间
        }
    }
    printf("%d", res);
    return 0;
}
```

---

## 个人心得摘录
- **BFSBFSBFSBFS**：通过证明每一步贪心选择的最优性，强化对策略的理解。  
- **meowla**：尝试动态规划解法虽复杂，但拓展了多资源调度问题的解决思路。  
- **调试经验**：多组测试数据发现排序需同时处理结束时间相同但开始时间不同的情况。

---
处理用时：98.64秒