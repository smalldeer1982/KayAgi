# 题目信息

# [POI 2010] PIL-Pilots

## 题目描述

In the Byteotian Training Centre, the pilots prepare for missions requiring extraordinary precision and control.

One measure of a pilot's capability is the duration he is able to fly along a desired route without deviating too much -    simply put, whether he can fly steadily. This is not an easy task, as the simulator is so sensitive that it registers    even a slightest move of the yoke1.

At each moment the simulator stores a single parameter describing the yoke's position.

Before each training session a certain tolerance level ![](http://main.edu.pl/images/OI17/pil-en-tex.1.png) is set.

The pilots' task then is to fly as long as they can in such a way that all the yoke's position measured during the    flight differ by at most ![](http://main.edu.pl/images/OI17/pil-en-tex.2.png). In other words, a fragment of the flight starting at time ![](http://main.edu.pl/images/OI17/pil-en-tex.3.png) and ending at time ![](http://main.edu.pl/images/OI17/pil-en-tex.4.png)    is within tolerance level ![](http://main.edu.pl/images/OI17/pil-en-tex.5.png) if the position measurements, starting with ![](http://main.edu.pl/images/OI17/pil-en-tex.6.png)-th and ending with ![](http://main.edu.pl/images/OI17/pil-en-tex.7.png)-th,    form such a sequence ![](http://main.edu.pl/images/OI17/pil-en-tex.8.png) that for all elements ![](http://main.edu.pl/images/OI17/pil-en-tex.9.png) of this sequence, the inequality ![](http://main.edu.pl/images/OI17/pil-en-tex.10.png) holds.

Your task is to write a program that, given a number ![](http://main.edu.pl/images/OI17/pil-en-tex.11.png) and the sequence of yoke's position measurements,    determines the length of the longest fragment of the flight that is within the tolerance level ![](http://main.edu.pl/images/OI17/pil-en-tex.12.png).

给定 $n, k$ 和一个长度为 $n$ 的序列，求最长的最大值最小值相差不超过 $k$ 的子段。

## 说明/提示

样例解释：$5, 8, 6, 6$ 和 $8, 6, 6, 9$ 都是满足条件长度为 $4$ 的子段。

## 样例 #1

### 输入

```
3 9
5 1 3 5 8 6 6 9 10```

### 输出

```
4```

# AI分析结果



### 唯一算法分类
**单调队列（双队列维护最大最小值）**

---

### 题解思路与核心难点
**核心问题**：如何在 O(n) 时间内找到最长子段，使得其最大值与最小值之差不超过 k。  
**关键思路**：  
1. **双单调队列**：维护两个队列，一个递减（保存最大值候选），一个递增（保存最小值候选）。
2. **滑动窗口**：右端点遍历数组，左端点动态调整以保证差值合法。
3. **快速调整窗口**：当最大值-最小值超过 k 时，弹出队首中索引更小的元素，确保窗口尽可能大。

**解决难点**：  
- **如何同步维护两个队列**：需保证队列中的元素属于当前窗口，且单调性正确。
- **窗口左端点更新策略**：比较两个队列的队首索引，弹出较小的索引以缩小区间。

---

### 题解评分（≥4星）
1. **alksdjhfg（5星）**  
   - **亮点**：数组模拟队列效率高，逻辑清晰。通过 `pre` 变量直接计算窗口长度，避免双指针冗余操作。  
   - **代码片段**：  
     ```cpp
     while(a[q_mx[head_mx]] - a[q_mn[head_mn]] > k) {
         if(q_mx[head_mx] < q_mn[head_mn]) { 
             pre = q_mx[head_mx] + 1; head_mx++; 
         } else { 
             pre = q_mn[head_mn] + 1; head_mn++; 
         }
     }
     len = max(len, i - pre + 1);
     ```

2. **LightningUZ（4星）**  
   - **亮点**：简洁的宏定义提升可读性，通过 `pre` 统一管理窗口起点。  
   - **关键实现**：  
     ```cpp
     #define Fn (Qn[hn])
     #define Fx (Qx[hx])
     while(a[Fx] - a[Fn] > k) {
         if (Fx < Fn) { pre = Fx + 1; hx++; }
         else { pre = Fn + 1; hn++; }
     }
     ```

3. **Durancer（4星）**  
   - **亮点**：双指针明确分离窗口左右端点，适合理解滑动窗口模型。  
   - **核心逻辑**：  
     ```cpp
     while(a[qm[frontm]] - a[qn[frontn]] > k) {
         if(qnid[frontn] < qmid[frontm]) 
             id = qnid[frontn] + 1, ++frontn;
         else 
             id = qmid[frontm] + 1, ++frontm;
     }
     ```

---

### 最优思路与技巧提炼
1. **双队列维护极值**：  
   - 最大值队列保持递减，最小值队列保持递增。
   - **入队操作**：遍历元素时，先弹出队尾所有破坏单调性的元素，再入队当前索引。
2. **动态调整窗口**：  
   - 当差值超过 k 时，选择弹出索引更小的队首，快速缩小窗口。
3. **计算窗口长度**：通过 `当前右端点 - 左端点 + 1` 实时更新最长长度。

---

### 同类型题与算法套路
- **滑动窗口极值问题**：如滑动窗口最大值（LeetCode 239）、最小覆盖子串（LeetCode 76）。
- **双指针+单调性优化**：当问题涉及区间极值约束时，考虑单调队列维护候选值。

---

### 推荐相似题目
1. **P1886 滑动窗口**（模板题，练习单调队列基础）  
2. **P1440 求m区间内的最小值**（单调队列变形）  
3. **LeetCode 1438. 绝对差不超过限制的最长连续子数组**（同一问题模型）

---

### 可视化与算法演示
**动画设计**：  
1. **队列状态高亮**：  
   - 红色框表示最大值队列，蓝色框表示最小值队列。  
   - 当前右端点移动时，动态展示队列元素弹出与加入。  
2. **差值超限处理**：  
   - 当差值超过 k 时，用闪烁效果提示弹出较小索引的队首，并更新左端点位置。  
3. **复古像素风格**：  
   - 使用 8-bit 风格颜色区分队列元素，背景播放循环芯片音乐。  
   - 每次弹出/加入队列时触发“哔”声，找到最长窗口时播放胜利音效。

**交互控制**：  
- **速度调节**：滑块控制动画速度，支持暂停/继续。  
- **AI自动模式**：自动展示算法流程，类似贪吃蛇自动寻路。

---

### 代码实现（核心逻辑）
```cpp
#include <iostream>
using namespace std;

const int MAXN = 3e6 + 5;
int k, n, a[MAXN], q_max[MAXN], q_min[MAXN];
int h_max = 0, t_max = -1, h_min = 0, t_min = -1;

int main() {
    ios::sync_with_stdio(false);
    cin >> k >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    int left = 0, max_len = 0;
    for (int right = 0; right < n; ++right) {
        // 维护最大值队列（递减）
        while (h_max <= t_max && a[q_max[t_max]] <= a[right]) t_max--;
        q_max[++t_max] = right;
        // 维护最小值队列（递增）
        while (h_min <= t_min && a[q_min[t_min]] >= a[right]) t_min--;
        q_min[++t_min] = right;
        
        // 调整左端点直到差值合法
        while (a[q_max[h_max]] - a[q_min[h_min]] > k) {
            if (q_max[h_max] < q_min[h_min]) left = q_max[h_max++] + 1;
            else left = q_min[h_min++] + 1;
        }
        
        max_len = max(max_len, right - left + 1);
    }
    cout << max_len << endl;
    return 0;
}
```

---
处理用时：121.40秒