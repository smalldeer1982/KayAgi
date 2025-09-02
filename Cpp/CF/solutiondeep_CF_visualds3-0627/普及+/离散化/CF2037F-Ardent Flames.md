# 题目信息

# Ardent Flames

## 题目描述

You have obtained the new limited event character Xilonen. You decide to use her in combat.

There are $ n $ enemies in a line. The $ i $ 'th enemy from the left has health $ h_i $ and is currently at position $ x_i $ . Xilonen has an attack damage of $ m $ , and you are ready to defeat the enemies with her.

Xilonen has a powerful "ground stomp" attack. Before you perform any attacks, you select an integer $ p $ and position Xilonen there ( $ p $ can be any integer position, including a position with an enemy currently). Afterwards, for each attack, she deals $ m $ damage to an enemy at position $ p $ (if there are any), $ m-1 $ damage to enemies at positions $ p-1 $ and $ p+1 $ , $ m-2 $ damage to enemies at positions $ p-2 $ and $ p+2 $ , and so on. Enemies that are at least a distance of $ m $ away from Xilonen take no damage from attacks.

Formally, if there is an enemy at position $ x $ , she will deal $ \max(0,m - |p - x|) $ damage to that enemy each hit. Note that you may not choose a different $ p $ for different attacks.

Over all possible $ p $ , output the minimum number of attacks Xilonen must perform to defeat at least $ k $ enemies. If it is impossible to find a $ p $ such that eventually at least $ k $ enemies will be defeated, output $ -1 $ instead. Note that an enemy is considered to be defeated if its health reaches $ 0 $ or below.

## 说明/提示

In the first testcase, it is optimal to select $ p=2 $ . Each attack, the first enemy takes $ 5-|2-1|=4 $ damage, the second enemy takes $ 5 $ damage, the third enemy takes $ 4 $ damage, the fourth enemy takes $ 3 $ damage, and the fifth enemy takes $ 2 $ damage. After $ 2 $ attacks, the first three enemies will be defeated. It can be shown that it is impossible to defeat $ 3 $ enemies in less than $ 2 $ attacks, no matter which $ p $ is selected.

In the second testcase, we must kill all $ 9 $ enemies. By selecting $ p=5 $ , all nine enemies will be defeated in $ 2 $ attacks.

In the third testcase, we must kill both enemies. However, it can be shown that no $ p $ selected will damage both enemies at the same time, so the answer is $ -1 $ .

In the fourth testcase, selecting $ p=1 $ will enable us to defeat the first enemy in $ 6969697 $ attacks.

In the fifth testcase, selecting $ p=10 $ will make each enemy take $ 1 $ damage per attack. Both enemies will be defeated in $ 15 $ attacks.

## 样例 #1

### 输入

```
6
5 5 3
7 7 7 7 7
1 2 3 4 5
9 5 9
2 4 6 8 10 8 6 4 2
1 2 3 4 5 6 7 8 9
2 10 2
1 1
1 20
2 10 1
69696969 420420420
1 20
2 10 2
10 15
1 19
2 2 2
1000000000 1
1 3```

### 输出

```
2
2
-1
6969697
15
1000000000```

# AI分析结果



---

### **唯一算法分类**
二分答案 + 扫描线/差分

---

### **综合分析与结论**

#### **核心思路**
1. **二分答案**：最小攻击次数具有单调性（攻击次数越多，越容易满足条件），因此二分攻击次数。
2. **区间覆盖问题**：对每个二分的攻击次数 `mid`，计算每个敌人能被击败的区间 `[x_i - d, x_i + d]`（其中 `d = m - ceil(h_i/mid)`），转化为判断是否存在一个点被至少 `k` 个区间覆盖。
3. **扫描线/差分**：将每个区间的起点和终点作为事件点，排序后扫描并维护当前覆盖数，若覆盖数 ≥k 则说明可行。

#### **解决难点**
- **推导区间公式**：需从攻击次数 `mid` 推导出每个敌人的有效覆盖区间。
- **高效验证覆盖**：使用扫描线或差分数组避免暴力遍历所有可能的坐标。

#### **可视化设计**
- **动画方案**：展示二分过程（调整 `mid` 范围），生成区间事件点，扫描时动态显示覆盖数的变化。
- **颜色标记**：高亮当前扫描的事件点和覆盖数变化的关键步骤。
- **复古像素风格**：用 8 位色块表示事件点，扫描线移动时播放音效，覆盖数达标时显示成功动画。
- **交互功能**：支持单步执行、调整扫描速度，显示当前 `mid` 值和覆盖数。

---

### **题解清单（评分 ≥4星）**

1. **题解作者：1234567890sjx（4星）**  
   **亮点**：简洁的扫描线实现，事件点排序逻辑清晰，代码可读性高。  
   **关键代码**：事件点排序后前缀和判断覆盖数。

2. **题解作者：Melo_DDD（4星）**  
   **亮点**：代码结构清晰，事件点用 `pair` 存储，直接排序处理。  
   **关键代码**：动态维护覆盖数，避免离散化。

3. **题解作者：AtomAlpaca（4.5星）**  
   **亮点**：使用双队列分别存储区间起止点，扫描时合并处理，逻辑高效。  
   **关键代码**：`deque` 排序后交替扫描起止点。

---

### **最优思路与代码片段**

#### **核心思路**
- **二分框架**：`l=1, r=1e9`，检查 `mid` 是否可行。
- **事件点处理**：对每个敌人计算区间 `[L, R]`，转化为事件点 `(L, +1)` 和 `(R+1, -1)`。
- **扫描线验证**：排序事件点后遍历，维护前缀和判断覆盖数 ≥k。

#### **代码实现（关键逻辑）**
```cpp
bool check(int mid) {
    vector<pair<int, int>> events;
    for (int i = 1; i <= n; ++i) {
        int d = (h[i] + mid - 1) / mid;  // 计算 ceil(h_i / mid)
        if (d > m) continue;
        int len = m - d;
        int L = x[i] - len, R = x[i] + len;
        events.emplace_back(L, 1);
        events.emplace_back(R + 1, -1);
    }
    sort(events.begin(), events.end());
    int cnt = 0;
    for (auto [pos, val] : events) {
        cnt += val;
        if (cnt >= k) return true;
    }
    return false;
}
```

---

### **同类型题目与算法套路**
- **通用解法**：二分答案 + 区间覆盖/扫描线。
- **类似题目**：
  1. **洛谷 P1873**：砍树（二分答案求最大高度）。
  2. **洛谷 P1316**：丢瓶盖（最小距离最大化）。
  3. **洛谷 P4344**：[SHOI2015] 脑洞治疗仪（区间覆盖与统计）。

---

### **个人心得摘录**
- **调试教训**：区间端点 `R+1` 的 `+1` 易漏，需仔细验证边界。
- **顿悟点**：将敌人转化为区间后，问题转化为经典覆盖问题。

---

### **复古游戏化动画设计**
1. **像素风格**：  
   - **事件点**：绿色方块（起点）+1，红色方块（终点）-1。
   - **扫描线**：黄色箭头从左到右移动，覆盖数显示为顶部计数器。
2. **音效设计**：  
   - **扫描移动**：每步播放“滴”声。
   - **覆盖达标**：播放胜利音效（8-bit 短旋律）。
3. **AI 自动演示**：自动调整 `mid` 并展示扫描过程，速度可调。
4. **交互面板**：  
   - 滑块控制二分范围和扫描速度。
   - 按钮：单步扫描、重置、自动播放。

```javascript
// 伪代码：事件点扫描动画
function animateScan(events) {
    let cnt = 0;
    events.sort((a, b) => a[0] - b[0]);
    for (let [pos, val] of events) {
        cnt += val;
        drawPixel(pos, color);  // 绘制事件点
        playSound(val > 0 ? "plus" : "minus");
        if (cnt >= k) {
            playSound("win");
            highlightPosition(pos);
            break;
        }
    }
}
```

---

**总结**：通过二分和扫描线的结合，将复杂的位置选择问题转化为经典的区间覆盖问题，是解决此类优化问题的典型思路。

---
处理用时：63.31秒