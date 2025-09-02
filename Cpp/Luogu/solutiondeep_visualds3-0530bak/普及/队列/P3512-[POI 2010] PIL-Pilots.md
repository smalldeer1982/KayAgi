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



### 算法分类
单调队列（滑动窗口）

---

### 题解思路与核心难点

#### 题目核心
在长度为 $n$ 的序列中，找到最长的连续子段，使得该子段的最大值与最小值之差不超过 $k$。

#### 算法要点
1. **双指针+双单调队列**  
   - 维护两个单调队列：递增队列（存最小值候选）和递减队列（存最大值候选）。
   - 右指针向右扩展时，将当前元素加入队列，并弹出破坏单调性的元素。
   - 当最大最小值差超过 $k$ 时，移动左指针，并调整队列头（优先弹出索引更小的队列头）。

2. **核心难点**  
   - **动态维护窗口最值**：需快速获取当前窗口的极值，并保证队列中元素的索引连续性。
   - **高效调整窗口**：当差值超标时，需快速确定哪个队列的头部元素更靠前，从而移动左指针到该元素后一位。

#### 对比题解差异
- **alksdjhfg 题解**：通过 `pre` 记录当前窗口左端点，比较两个队列头的索引，移动更小的。
- **天梦题解**：当差值超标时，判断哪个队列只剩一个元素，优先删除另一队列的头部。
- **Godzilla 题解**：使用 `max(s1[h1-1], s2[h2-1])` 快速计算有效窗口长度。

---

### 题解评分（≥4星）

| 题解作者     | 星级 | 关键亮点                          |
|--------------|------|-----------------------------------|
| alksdjhfg    | ⭐⭐⭐⭐ | 逻辑清晰，代码简洁，双队列调整策略直观 |
| LightningUZ  | ⭐⭐⭐⭐ | 代码高度优化，变量命名规范，注释明确   |
| 天梦          | ⭐⭐⭐⭐ | 处理差值超标时优化逻辑，减少冗余操作   |

---

### 最优思路提炼

1. **双队列维护极值**  
   使用两个单调队列分别维护当前窗口的最大值（递减队列）和最小值（递增队列），确保队列头即为当前极值。

2. **差值超标调整策略**  
   当 `max_val - min_val > k` 时，比较两个队列头的索引：  
   - 若最大值队列头索引更小，则弹出该头，左指针移动到 `max_idx + 1`。  
   - 反之同理。确保窗口左端点始终有效。

3. **复杂度控制**  
   每个元素最多入队和出队一次，时间复杂度严格 $O(n)$，空间复杂度 $O(n)$。

---

### 同类型题与算法套路

1. **滑动窗口极值问题**  
   - 核心：通过单调队列快速维护窗口内的极值。
   - 变种：求所有固定长度窗口的极值（如 LeetCode 239）。

2. **双指针+极值维护**  
   - 适用于需要动态调整窗口边界，且极值计算频繁的场景。

---

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)（单调队列模板题）
2. [LeetCode 239. 滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/)
3. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)

---

### 关键代码片段

```cpp
// 核心逻辑（基于 alksdjhfg 题解）
int pre = 1, len = 0;
deque<int> q_max, q_min;
for (int i = 1; i <= n; i++) {
    // 维护递减队列（最大值候选）
    while (!q_max.empty() && a[q_max.back()] < a[i]) q_max.pop_back();
    q_max.push_back(i);
    // 维护递增队列（最小值候选）
    while (!q_min.empty() && a[q_min.back()] > a[i]) q_min.pop_back();
    q_min.push_back(i);
    
    // 调整窗口左端点
    while (a[q_max.front()] - a[q_min.front()] > k) {
        if (q_max.front() < q_min.front()) {
            pre = q_max.front() + 1;
            q_max.pop_front();
        } else {
            pre = q_min.front() + 1;
            q_min.pop_front();
        }
    }
    len = max(len, i - pre + 1);
}
```

---

### 可视化设计

#### 动画方案
1. **数据结构展示**  
   - **主数组**：横向排列，当前右指针高亮为绿色，左指针为红色。
   - **单调队列**：悬浮在主数组上方，队列元素用不同颜色区分（最大值队列用暖色，最小值队列用冷色）。

2. **关键操作高亮**  
   - **元素入队**：新元素从右侧滑入队列，破坏单调性的元素以闪烁效果被弹出。
   - **窗口调整**：当差值超标时，更小的队列头元素爆炸消失，左指针跳跃到新位置。

3. **复古像素风格**  
   - 8-bit 音效：元素入队（短促“滴”声），队列弹出（低沉“砰”声），窗口更新（跳跃音效）。
   - Canvas 绘制：主数组为像素方块，队列元素用不同色块表示，移动时带拖影效果。

#### 交互功能
- **步进控制**：支持暂停/继续，单步执行观察队列变化。
- **速度调节**：拖动条控制动画速度（0.5x~5x）。
- **自动演示模式**：AI 自动运行，右侧状态栏显示当前窗口长度和极值差。

---

### 个人心得摘录
> "维护双队列时，必须同步记录元素索引，否则无法判断是否需要弹出队头。调试时曾因索引更新错误导致死循环，最终通过逐行打印队列内容定位问题。" —— alksdjhfg

---
处理用时：101.20秒