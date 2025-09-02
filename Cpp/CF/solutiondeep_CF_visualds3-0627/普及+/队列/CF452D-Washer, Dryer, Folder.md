# 题目信息

# Washer, Dryer, Folder

## 题目描述

You have $ k $ pieces of laundry, each of which you want to wash, dry and fold. You are at a laundromat that has $ n_{1} $ washing machines, $ n_{2} $ drying machines and $ n_{3} $ folding machines. Each machine can process only one piece of laundry at a time. You can't dry a piece of laundry before it is washed, and you can't fold it before it is dried. Moreover, after a piece of laundry is washed, it needs to be immediately moved into a drying machine, and after it is dried, it needs to be immediately moved into a folding machine.

It takes $ t_{1} $ minutes to wash one piece of laundry in a washing machine, $ t_{2} $ minutes to dry it in a drying machine, and $ t_{3} $ minutes to fold it in a folding machine. Find the smallest number of minutes that is enough to wash, dry and fold all the laundry you have.

## 说明/提示

In the first example there's one instance of each machine, each taking 5 minutes to complete. You have only one piece of laundry, so it takes 15 minutes to process it.

In the second example you start washing first two pieces at moment $ 0 $ . If you start the third piece of laundry immediately, then by the time it is dried, there will be no folding machine available, so you have to wait, and start washing third piece at moment $ 2 $ . Similarly, you can't start washing next piece until moment $ 5 $ , since otherwise there will be no dryer available, when it is washed. Start time for each of the eight pieces of laundry is $ 0,0,2,5,10,10,12 $ and $ 15 $ minutes respectively. The last piece of laundry will be ready after $ 15+10+5+2=32 $ minutes.

## 样例 #1

### 输入

```
1 1 1 1 5 5 5
```

### 输出

```
15
```

## 样例 #2

### 输入

```
8 4 3 2 10 5 2
```

### 输出

```
32
```

# AI分析结果



1. **唯一算法分类**  
   贪心算法

2. **综合分析与结论**  
   - 核心思路是循环分配机器资源，并维护各机器完成时间。每件衣服需经历三个阶段（洗/烘/折），每个阶段选取对应机器后，计算三个阶段的最晚完成时间作为总完成时间。
   - 难点在于处理阶段间的连续性约束：烘干必须紧跟洗涤完成时开始，折叠必须紧跟烘干完成时开始。
   - 可视化设计：用三组颜色块表示洗衣机、烘干机、折叠机的占用时间轴。每分配一件衣服时，高亮对应机器的时间段，并动态显示三个阶段的时间衔接关系。复古像素动画中，用不同颜色像素块表示机器忙碌状态，音效在机器释放时触发。

3. **题解清单 (≥4星)**  
   - 灵茶山艾府（★★★★★）：循环分配+时间维护，时间复杂度最优，代码简洁。
   - zhoukangyang（★★★★★）：动态规划巧妙建模资源约束，状态转移简洁高效。
   - enyyyyyyy（★★★★☆）：优先队列显式调度，直观展示资源分配过程。

4. **最优思路提炼**  
   - **循环分配**：对第i件衣服，用i mod n选择对应阶段的机器，实现负载均衡。
   - **时间衔接公式**：总完成时间取三阶段最晚时间，确保流程无阻塞。
   - **动态维护**：用数组或优先队列记录每台机器的下次可用时间。

```cpp
// 灵茶山艾府解法核心代码
vector<int> f1(n1), f2(n2), f3(n3);
for (int i = 0; i < k; ++i) {
    int m1 = i % n1, m2 = i % n2, m3 = i % n3;
    int finish = max({f1[m1] + t1 + t2 + t3, 
                     f2[m2] + t2 + t3, 
                     f3[m3] + t3});
    f1[m1] = finish - t2 - t3; // 更新洗衣机下次可用时间
    f2[m2] = finish - t3;      // 更新烘干机下次可用时间
    f3[m3] = finish;           // 更新折叠机下次可用时间
}
```

5. **同类型题与算法套路**  
   - 流水线调度（如 Johnson's rule）
   - 资源受限项目调度（RCPSP）
   - 多阶段任务分配问题

6. **推荐题目**  
   - P1541 机器工厂（资源动态分配）
   - P1080 国王游戏（贪心策略）
   - P1880 石子合并（动态规划）

7. **个人心得摘录**  
   > "当洗衣机未满时，直接放入；否则需等待最早完成的机器" —— AK_400的模拟思路体现了贪心的本质。

8. **可视化方案**  
   - **像素动画**：用横向色块表示每台机器的时间轴，色块长度对应任务时间。新任务分配时，从当前时间点延伸色块。
   - **音效设计**：洗涤完成时播放水滴声，烘干完成时吹风声，折叠完成时布料声。
   - **自动演示**：按时间步推进，高亮当前处理的衣服和各阶段机器状态。

---
处理用时：97.51秒