# 题目信息

# System Testing

## 题目描述

Vasya likes taking part in Codeforces contests. When a round is over, Vasya follows all submissions in the system testing tab.

There are $ n $ solutions, the $ i $ -th of them should be tested on $ a_i $ tests, testing one solution on one test takes $ 1 $ second. The solutions are judged in the order from $ 1 $ to $ n $ . There are $ k $ testing processes which test solutions simultaneously. Each of them can test at most one solution at a time.

At any time moment $ t $ when some testing process is not judging any solution, it takes the first solution from the queue and tests it on each test in increasing order of the test ids. Let this solution have id $ i $ , then it is being tested on the first test from time moment $ t $ till time moment $ t + 1 $ , then on the second test till time moment $ t + 2 $ and so on. This solution is fully tested at time moment $ t + a_i $ , and after that the testing process immediately starts testing another solution.

Consider some time moment, let there be exactly $ m $ fully tested solutions by this moment. There is a caption "System testing: $ d $ %" on the page with solutions, where $ d $ is calculated as

 $ $$$d = round\left(100\cdot\frac{m}{n}\right), $ $ </p><p>where  $ round(x) = \\lfloor{x + 0.5}\\rfloor $  is a function which maps every real to the nearest integer.</p><p>Vasya calls a submission <span class="tex-font-style-it">interesting</span> if there is a time moment (possibly, non-integer) when the solution is being tested on some test  $ q $ , and the caption says "System testing:  $ q$$$%". Find the number of interesting solutions.

Please note that in case when multiple processes attempt to take the first submission from the queue at the same moment (for instance, at the initial moment), the order they take the solutions does not matter.

## 说明/提示

Consider the first example. At time moment $ 0 $ both solutions start testing. At time moment $ 49 $ the first solution is fully tested, so at time moment $ 49.5 $ the second solution is being tested on the test $ 50 $ , and the caption says "System testing: $ 50 $ %" (because there is one fully tested solution out of two). So, the second solution is interesting.

Consider the second example. At time moment $ 0 $ the first and the second solutions start testing. At time moment $ 32 $ the first solution is fully tested, the third solution starts testing, the caption says "System testing: $ 25 $ %". At time moment $ 32 + 24.5 = 56.5 $ the third solutions is being tested on test $ 25 $ , the caption is still the same, thus this solution is interesting. After that the third solution is fully tested at time moment $ 32 + 33 = 65 $ , the fourth solution is fully tested at time moment $ 65 + 1 = 66 $ . The captions becomes "System testing: $ 75 $ %", and at time moment $ 74.5 $ the second solution is being tested on test $ 75 $ . So, this solution is also interesting. Overall, there are two interesting solutions.

## 样例 #1

### 输入

```
2 2
49 100
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 2
32 100 33 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
14 5
48 19 6 9 50 20 3 42 38 43 36 21 44 6
```

### 输出

```
5
```

# AI分析结果


### 💡 Kay的C++算法解析：System Testing 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：模拟（Simulation）与枚举（Enumeration）  
🗣️ **初步分析**：
> 这道题就像指挥一支像素游戏中的多人工厂流水线！想象有`k`个像素小人在同时组装玩具（测试代码），每个玩具需要`a_i`个组装步骤（测试点），每秒完成一步。核心是模拟流水线运行过程，并在特定时刻检查「有趣条件」：当某个玩具正在组装第`q`步时，系统进度显示恰好为`q%`。  
> - **核心思路**：离散化时间，每秒检查所有进行中的任务状态，动态更新完成数和系统进度`d`，并验证当前时刻是否满足有趣条件  
> - **可视化重点**：用不同颜色像素块表示测试点，高亮满足条件的测试点并触发音效，进度条实时显示`d`值  
> - **复古设计**：8-bit风格流水线界面，每完成一个测试点播放「滴」声，满足有趣条件时触发「叮！」音效和高亮闪烁，支持调速滑块控制模拟速度  

---

#### 2. 精选优质题解参考
**题解一（来源：__LiChangChao__）**  
* **点评**：  
  思路清晰度：⭐️⭐️⭐️⭐️ 直接枚举每一秒状态，避免复杂调度逻辑，符合直觉  
  代码规范性：⭐️⭐️⭐️ 变量名可读性一般（如`tj`, `nw`），但结构工整  
  算法有效性：⭐️⭐️⭐️⭐️ 时间复杂度O(maxT×n)≈1.5e8，C++可AC，利用时间离散化巧妙转化非整数时刻条件  
  实践价值：⭐️⭐️⭐️⭐️ 边界处理严谨（`ed=min(ed,n)`），可直接用于竞赛  
  亮点：用`start[]`数组隐式管理进程状态，避免显式队列操作  

---

#### 3. 核心难点辨析与解题策略
1. **难点1：非整数时刻条件转化**  
   *分析*：有趣条件需在任意实数时刻检查，但题解发现只需在**整数秒**检查「已运行时间=系统进度d」即可等价。因测试第`q`点发生在`[t+q-1, t+q)`区间，而`d`在区间内恒定，取右端点`t+q`时必然满足`运行时间=q`且`d=q`  
   💡 学习笔记：连续条件可离散化为关键时间点验证  

2. **难点2：多进程状态同步**  
   *分析*：不显式跟踪`k`个进程，而用`start[]`记录任务开始时间，`ed`跟踪已调度任务数。当任务完成时，`ed += nw`等效释放进程并接新任务  
   💡 学习笔记：用全局计数替代个体状态，简化并行逻辑  

3. **难点3：避免重复计数**  
   *分析*：`tj[]`数组确保每个任务只标记一次有趣，防止同一任务在不同秒触发多次  
   💡 学习笔记：状态标记数组是防重的常用技巧  

##### ✨ 解题技巧总结
- **离散化转换**：将实数时刻条件转化为离散时间点验证  
- **隐式状态管理**：用开始时间`start[i]`和完成数`finish`代替复杂进程调度  
- **边界防御**：`ed=min(ed,n)`防止数组越界，`i<=maxt`控制枚举上界  

---

#### 4. C++核心代码实现赏析
**通用核心实现**  
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1005, MAXT = 150000;

int main() {
    int n, k, a[MAXN], ans = 0, finish = 0, ed = k;
    bool ok[MAXN]{}, counted[MAXN]{};
    int start[MAXN]{}; // 记录开始时间

    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    
    for (int t = 1; t <= MAXT; ++t) {
        int d = round(100.0 * finish / n); // 四舍五入
        int completed = 0;

        for (int j = 1; j <= min(ed, n); ++j) {
            if (ok[j]) continue;
            
            // 检查有趣条件（先于完成检查）
            if (t - start[j] == d && !counted[j]) {
                ans++; 
                counted[j] = true;
            }
            // 检查是否完成
            if (t - start[j] == a[j]) {
                ok[j] = true;
                completed++;
            }
        }

        finish += completed;
        ed += completed; // 释放进程并接新任务
        
        // 为新任务设置开始时间
        for (int j = k + 1; j <= ed && j <= n; ++j)
            if (!start[j]) start[j] = t;
    }
    cout << ans;
}
```
* **代码解读概要**：  
  1. 初始化时前`k`个任务`start=0`  
  2. 每秒遍历所有任务：  
     - 先检查「已运行时间 == 系统进度d」⇒ 标记有趣  
     - 再检查「已运行时间 == 总测试数」⇒ 标记完成  
  3. 完成的任务释放进程，`ed`增加并初始化新任务`start`时间  

**题解一片段赏析**  
```cpp
if (i - start[j] == d && !tj[j]) { 
    ans++; tj[j] = 1; 
}
if (i - start[j] == a[j]) { 
    ok[j] = 1, nw++; 
}
```
* **亮点**：双条件顺序确保完成瞬间仍可触发有趣  
* **代码解读**：  
  - `i-start[j]`是任务`j`已运行秒数（即完成测试点数）  
  - **关键顺序**：先有趣判定后完成检查，避免漏掉`运行时间=a[j]=d`的边界情况  
  - `tj[]`防重：确保每个任务仅统计一次  
* 💡 学习笔记：状态检查顺序可能影响边界条件处理  

---

### 5. 算法可视化：像素动画演示  
**主题**：8-bit流水线工厂  
**核心演示**：用像素工人并行测试代码，实时显示进度条，高亮触发有趣条件的测试点  

**动画设计**：  
1. **场景布局**（FC红白机风格）  
   - 顶部进度条：显示`d = round(100×m/n)`  
   - 中部流水线：`k`个工位，每个含：  
     * 像素小人（工人）  
     * 进度带：`a_i`个灰色方块（未测）→ 绿色（已测）  
   - 底部队列：等待的代码（带`a_i`标签）  

2. **动态流程**（速度可调）  
   ```plaintext
   帧 0: [工人A] [  ] [  ]...   [工人B] [  ] [  ]...  → d=0%
   帧 t: [工人A] [✔][✔][X]...   [工人B] [✔][ ]...  → d=round(100m/n)
         (X:当前测试点，满足条件时闪烁)
   ```  
   - **测试点填充**：每秒将当前测试点染绿，播放「滴」声  
   - **有趣条件触发**：当`已测点数 == d`时：  
     * 当前测试点闪烁3次（红→黄→绿）  
     * 播放「叮！」音效  
     * 左侧计数器`+1`  

3. **控制面板**  
   - 速度滑块：调整每秒帧数  
   - 单步/暂停/重置按钮  
   - 「AI演示」模式：自动运行并高亮所有有趣点  

4. **音效设计**  
   - 背景：8-bit循环音乐  
   - 事件音：  
     * 测试点完成：短促「滴」  
     * 有趣条件触发：「叮！」  
     * 任务完成：「哔~」上升音阶  

---

### 6. 拓展练习与相似问题  
**相似思维题**：  
1. **洛谷 P1540** 机器翻译  
   → 模拟缓存淘汰，维护固定容量队列  
2. **洛谷 P2058** 海港  
   → 时间窗口统计，动态更新队列  
3. **洛谷 P1538** 迎春舞会  
   → 复杂状态模拟与输出控制  

---

### 7. 学习心得与经验分享  
> **作者调试经验**：  
> *“最初未考虑完成检查与有趣检查的顺序，导致边界条件漏判”*  
>   
> **Kay总结**：  
> 状态检查顺序对边界处理至关重要！建议在模拟题中：  
> 1. 用打印中间状态验证时序  
> 2. 对`t=a[j]`等边界值单独测试  

---  
**本次解析结束！** 关键收获：掌握「离散化验证」技巧，善用`start[]`简化并行模拟。尝试用像素动画工具重现流水线过程吧！🎮

---
处理用时：317.14秒