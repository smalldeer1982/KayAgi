# 题目信息

# Load Balancing

## 题目描述

In the school computer room there are $ n $ servers which are responsible for processing several computing tasks. You know the number of scheduled tasks for each server: there are $ m_{i} $ tasks assigned to the $ i $ -th server.

In order to balance the load for each server, you want to reassign some tasks to make the difference between the most loaded server and the least loaded server as small as possible. In other words you want to minimize expression $ m_{a}-m_{b} $ , where $ a $ is the most loaded server and $ b $ is the least loaded one.

In one second you can reassign a single task. Thus in one second you can choose any pair of servers and move a single task from one server to another.

Write a program to find the minimum number of seconds needed to balance the load of servers.

## 说明/提示

In the first example two seconds are needed. In each second, a single task from server #2 should be moved to server #1. After two seconds there should be 3 tasks on server #1 and 4 tasks on server #2.

In the second example the load is already balanced.

A possible sequence of task movements for the third example is:

1. move a task from server #4 to server #1 (the sequence $ m $ becomes: 2 2 3 3 5);
2. then move task from server #5 to server #1 (the sequence $ m $ becomes: 3 2 3 3 4);
3. then move task from server #5 to server #2 (the sequence $ m $ becomes: 3 3 3 3 3).

The above sequence is one of several possible ways to balance the load of servers in three seconds.

## 样例 #1

### 输入

```
2
1 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
10 11 10 11 10 11 11
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
1 2 3 4 5
```

### 输出

```
3
```

# AI分析结果


### 💡 Kay的C++算法解析：Load Balancing 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：贪心算法/数学模拟  
🗣️ **初步分析**：  
> 解决负载均衡问题如同分配糖果：n个孩子（服务器）有不同糖果数（任务），每次移动一颗糖果（任务）使所有孩子糖果数尽量接近。核心策略是计算总糖果数sum，最终状态为：  
> - 大部分服务器任务数 = sum/n  
> - 剩余 sum%n 台服务器任务数 = sum/n +1  
> 通过排序服务器任务数，前n-rem台调整为avg，后rem台调整为avg+1，最小化调整量。总操作次数为调整量绝对值之和除以2（每次移动影响两台服务器）。  

**可视化设计思路**：  
采用8位像素风格动画：  
- 服务器显示为彩色像素塔（高度=任务数），排序后从左到右递增排列  
- 目标状态：前n-rem座塔高度=avg（蓝色），后rem座高度=avg+1（金色）  
- 移动动画：多余任务从高塔飞向低塔（像素块+轨迹），伴随"叮"音效  
- 控制面板：单步执行/自动播放（调速滑块）/重置，完成时播放胜利音效+塔闪光  

---

#### 2. 精选优质题解参考
**题解一：yuheng_wang080904**  
* **点评**：思路清晰直击核心——计算总和、余数后排序，前n-rem台用avg调整，后rem台用avg+1。代码简洁规范（变量名`sum`/`rem`含义明确），边界处理严谨（绝对值计算），实践价值高（可直接用于竞赛）。亮点：用整除和模运算精准确定目标状态。

**题解二：The_Lost_09**  
* **点评**：结构严谨，注释详细。通过`s1`/`s2`明确划分调整区间，自定义绝对值函数增强可读性。算法有效性高（严格数学推导），特别适合初学者理解余数分配原理。亮点：变量命名`b1`(avg)/`b2`(avg+1)直观体现数学关系。

**题解三：Dry_ice**  
* **点评**：极致简洁的典范。仅20行代码完成核心逻辑，利用位运算`ans>>1`高效替代除法。排序和循环边界处理干净利落，适合追求代码简洁性的学习者。亮点：用`p`/`rem`变量精准控制调整区间。

---

#### 3. 核心难点辨析与解题策略
1. **难点：确定最终状态**  
   *分析*：总任务数不可整除时，需明确avg与avg+1的服务器数量（余数rem）。优质解法则用`sum%n`计算余数，`n-rem`为avg台数。  
   💡 学习笔记：最终状态由`sum%n`唯一决定，最大最小差≤1。

2. **难点：最小化调整量**  
   *分析*：排序后让较小任务服务器优先成为avg，较大任务服务器成为avg+1（升序：前n-rem→avg；降序：前rem→avg+1）。关键变量`rem`划分调整区间。  
   💡 学习笔记：排序保证调整量最小，避免交叉调整。

3. **难点：计算操作次数**  
   *分析*：每次移动同时改变两台服务器状态，总调整量=绝对差之和÷2。代码中需严格用`abs()`计算差值再除2。  
   💡 学习笔记：操作次数=Σ|当前值-目标值|÷2。

**✨ 解题技巧总结**  
- **数学建模**：用整除/余数将问题转化为目标状态计算  
- **贪心排序**：升序排列后分段处理，保证局部最优即全局最优  
- **边界防御**：用绝对值函数避免正负抵消错误  
- **代码优化**：位运算`>>1`替代除法提升效率  

---

#### 4. C++核心代码实现赏析
**通用核心实现参考**  
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int n, a[100005];
    long long sum = 0;
    cin >> n;
    for(int i=0; i<n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    int avg = sum / n, rem = sum % n; // 关键变量
    sort(a, a+n); // 升序排序
    long long ans = 0;
    for(int i=0; i<n-rem; ++i) ans += abs(a[i] - avg);     // 前n-rem→avg
    for(int i=n-rem; i<n; ++i) ans += abs(a[i] - (avg+1));// 后rem→avg+1
    cout << ans/2 << endl; // 操作次数=总调整量/2
    return 0;
}
```
* **说明**：综合优质题解的精髓，清晰体现贪心策略与数学推导  
* **代码解读概要**：  
  1. 读入数据并计算总和`sum`  
  2. 关键变量`avg`(sum/n)和`rem`(sum%n)确定目标状态  
  3. 升序排序后分段计算调整量  
  4. 输出总调整量的一半即为答案  

**题解一核心片段**  
```cpp
sort(m+1, m+n+1);
for(int i=1; i<=n-sum%n; i++) ans += abs(m[i]-sum/n);
for(int i=n-sum%n+1; i<=n; i++) ans += abs(m[i]-(sum/n+1));
cout << ans/2;
```
* **亮点**：直接通过余数划分区间，无冗余计算  
* **学习笔记**：数组从1开始存储时，排序范围需对应调整  

**题解二核心片段**  
```cpp
b1=sum/n; b2=b1+1; s2=sum%n; s1=n-s2;
for(int i=0; i<s1; ++i) ans += abs(a[i]-b1);
for(int i=s1; i<n; ++i) ans += abs(a[i]-b2);
printf("%d\n", ans/2);
```
* **亮点**：显式命名b1(avg)/b2(avg+1)增强可读性  
* **学习笔记**：变量名应准确反映数学含义  

**题解三核心片段**  
```cpp
int p = sum / n, rem = sum % n;
sort(a, a+n);
for(int i=0; i<n-rem; ++i) ans += abs(a[i]-p);
for(int i=n-rem; i<n; ++i) ans += abs(a[i]-p-1);
cout << ans/2;
```
* **亮点**：极简变量名(p/rem)与位运算优化  
* **学习笔记**：`ans>>1`可替代除法但需确保整数运算  

---

#### 5. 算法可视化：像素动画演示  
**主题**：像素塔平衡大冒险（8-bit风格）  

**动画流程**：  
1. **初始化**：  
   - 像素塔按初始任务数生成（高度随机），塔底显示数值  
   - 控制面板：开始/暂停、单步、速度滑块、重置按钮  
   - 背景播放8-bit芯片音乐  

2. **排序阶段**：  
   - 塔从左到右按高度升序滑动重组（伴随"刷"音效）  
   - 显示目标状态：前n-rem塔顶标蓝色(avg)，后rem标金色(avg+1)  

3. **调整阶段**：  
   - **单步演示**：点击后当前塔闪烁，从高塔飞出像素块（带轨迹）到低塔  
   - **自动模式**：AI自动移动任务块（类似贪吃蛇AI），速度可调  
   - **音效反馈**：移动时"叮"，错误操作"哔"，完成时胜利旋律  

4. **动态显示**：  
   - 实时统计：总移动次数（屏幕顶栏）  
   - 塔调整后：新高度数值闪绿光更新  
   - 完成效果：所有塔按目标高度对齐，放烟花庆祝  

**设计解析**：  
- **像素美学**：16色调色盘，塔用马赛克方块堆叠  
- **教学强化**：移动时显示当前操作对应代码行（如`ans+=abs(a[i]-avg)`）  
- **游戏化**：每完成5次移动得1颗星，满3星通关  

---

#### 6. 拓展练习与相似问题思考
**通用技巧迁移**：  
- 余数分配模型：适用于所有"均分+余数"场景（如资源分配/负载调度）  
- 排序贪心法：解决最小化差异问题时，排序往往是最优策略  
- 绝对值应用：处理双向调整量的标准工具  

**洛谷推荐**：  
1. **P1031 均分纸牌**  
   🗣️ 直线均分基础版，巩固目标状态计算  
2. **P2512 [HAOI2008] 糖果传递**  
   🗣️ 环形均分进阶，训练数学推导能力  
3. **P3156 均分玩具**  
   🗣️ 本题变种，数据规模更大考验优化能力  

---

#### 7. 学习心得与经验分享
> **参考经验**：多位作者强调"总调整量需除以2"的易错点  
> **点评**：调试时可打印中间变量（如`avg`/`rem`），验证目标状态再计算调整量。切记移动操作的双向性！  

---
> 掌握负载均衡的核心在于数学建模与贪心策略的结合。通过本指南，希望大家不仅学会本题解法，更能理解"排序分段处理"的通用模式。下次遇到类似问题，记得先算avg和rem哦！ 🚀

---
处理用时：247.36秒