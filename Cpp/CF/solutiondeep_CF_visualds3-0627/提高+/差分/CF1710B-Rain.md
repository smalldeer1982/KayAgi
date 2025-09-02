# 题目信息

# Rain

## 题目描述

You are the owner of a harvesting field which can be modeled as an infinite line, whose positions are identified by integers.

It will rain for the next $ n $ days. On the $ i $ -th day, the rain will be centered at position $ x_i $ and it will have intensity $ p_i $ . Due to these rains, some rainfall will accumulate; let $ a_j $ be the amount of rainfall accumulated at integer position $ j $ . Initially $ a_j $ is $ 0 $ , and it will increase by $ \max(0,p_i-|x_i-j|) $ after the $ i $ -th day's rain.

A flood will hit your field if, at any moment, there is a position $ j $ with accumulated rainfall $ a_j>m $ .

You can use a magical spell to erase exactly one day's rain, i.e., setting $ p_i=0 $ . For each $ i $ from $ 1 $ to $ n $ , check whether in case of erasing the $ i $ -th day's rain there is no flood.

## 说明/提示

In the first test case, if we do not use the spell, the accumulated rainfall distribution will be like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710B/40bd9aae46d3e796ba1ad418de0578aa41ab0c1c.png)If we erase the third day's rain, the flood is avoided and the accumulated rainfall distribution looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710B/d422db8867ffc7f0ea195742c50ffb3752e7d523.png)In the second test case, since initially the flood will not happen, we can erase any day's rain.

In the third test case, there is no way to avoid the flood.

## 样例 #1

### 输入

```
4
3 6
1 5
5 5
3 4
2 3
1 3
5 2
2 5
1 6
10 6
6 12
4 5
1 6
12 5
5 5
9 7
8 3```

### 输出

```
001
11
00
100110```

# AI分析结果



---

## **算法分类**
**差分数组与极值分析**

---

## **综合分析与结论**

### **核心思路**
1. **极值点分析**：洪水发生的最高点必为某次降雨的中心，只需检查这些点。
2. **数学变换**：将问题转化为不等式条件，维护两个全局最大值 `max(a_j - x_j)` 和 `max(a_j + x_j)`。
3. **差分优化**：通过差分数组高效计算每个位置的积水量，避免暴力遍历。

### **难点与解决**
- **难点1**：如何处理区间降雨的影响？  
  **解决**：将每次降雨拆分为斜率变化的区间，用差分数组记录斜率和截距的变化。
- **难点2**：如何快速判断消除某天降雨后的条件？  
  **解决**：预处理全局最大值，判断每个降雨是否满足 `p_i - x_i ≥ max(a_j - x_j)` 和 `p_i + x_i ≥ max(a_j + x_j)`。

### **可视化设计**
- **动画效果**：  
  - **像素风格**：用方格表示降雨中心，颜色深浅表示积水量。超过 `m` 时闪烁红色。  
  - **动态差分**：展示差分数组如何逐步叠加，形成积水量曲线。  
  - **消除效果**：点击某天降雨后，重新绘制积水量，高亮满足/不满足条件的位置。  
- **音效**：  
  - **成功**：清脆提示音（未超限）。  
  - **失败**：低沉音效（存在超限）。  
- **交互控制**：支持暂停、单步执行，查看每一步的斜率和截距变化。

---

## **题解清单 (≥4星)**
1. **ethan_zhou (5星)**  
   - **亮点**：图形化分析、差分数组高效实现。  
   - **核心代码**：通过差分计算斜率和截距，维护全局最大值。  
   - **代码片段**：  
     ```cpp
     // 差分处理
     delt[x[i] - p[i] + 1]++;
     delt[x[i] + 1] -= 2;
     delt[x[i] + p[i] + 1]++;
     ```

2. **enucai (4星)**  
   - **亮点**：二分确定影响区间，维护前缀/后缀最大值。  
   - **核心代码**：  
     ```cpp
     // 维护最大值
     mx1 = max(mx1, a[i] - x[i]);
     mx2 = max(mx2, a[i] + x[i]);
     ```

3. **Jeefy (4星)**  
   - **亮点**：线段树动态更新，离散化处理。  
   - **核心代码**：  
     ```cpp
     // 线段树区间更新
     s.update(l, now, Tag{p[i]-x[i], 1});
     s.update(now+1, r, Tag{p[i]+x[i], -1});
     ```

---

## **最优思路与代码**
### **关键思路**
1. **差分预处理**：将每次降雨的影响拆分为两个等差数列，记录斜率和截距的差分。  
2. **极值计算**：扫描所有事件点，计算每个位置的积水量，维护两个全局最大值。  
3. **条件判断**：对每个降雨 `i`，验证其是否覆盖所有可能的极值点。

### **核心代码实现**
```cpp
// 差分处理与极值计算
map<ll, ll> delt;
for (ll i = 1; i <= n; i++) {
    cin >> x[i] >> p[i];
    delt[x[i] - p[i] + 1]++;
    delt[x[i] + 1] -= 2;
    delt[x[i] + p[i] + 1]++;
}

ll b = 0, k = 0, lastx = -INF;
ll b_1 = -INF, b1 = -INF;
for (auto it : delt) {
    b += k * (it.fi - lastx);
    k += it.se;
    if (b > m) {
        umx(b1, b - it.fi + 1);
        umx(b_1, b + it.fi - 1);
    }
    lastx = it.fi;
}

// 判断条件
for (ll i = 1; i <= n; i++) 
    cout << ((p[i] + m - x[i] >= b1) && (p[i] + m + x[i] >= b_1));
```

---

## **相似题目推荐**
1. **P3372 线段树区间修改**（差分数组与线段树应用）  
2. **P5482 差分约束系统**（极值分析与不等式转化）  
3. **CF1000F 区间极值覆盖**（极值维护与条件判断）

---

## **个人心得摘录**
- **顿悟**：“极值点必为降雨中心”简化了问题，避免处理无限位置。  
- **调试**：离散化后需注意区间端点处理，否则差分结果错误。  
- **优化**：线段树的标记下传需完全，避免残留影响后续操作。

---

## **可视化与复古动画设计**
### **Canvas 实现**
1. **像素网格**：  
   - 每个降雨中心为绿色方块，积水量随高度渐变。  
   - 超过 `m` 时显示红色边框。  
2. **差分过程**：  
   - 左侧面板展示差分数组的更新，右侧绘制积水量曲线。  
   - 每次点击“Next Step”，高亮当前处理的差分事件。  
3. **音效触发**：  
   - 成功时播放 `success.wav`（8-bit 音效）。  
   - 失败时播放 `error.wav`。  

### **自动演示模式**
- **AI 控制**：自动按天消除降雨，显示结果。  
- **关卡设计**：  
  - Level 1：单次降雨消除。  
  - Level 2：复杂多雨叠加情况。  
  - 每关通过后解锁更高难度，积分奖励机制。  

---

**答案输出完毕**

---
处理用时：76.20秒