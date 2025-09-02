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

**唯一算法分类**: 无算法分类

---

### **题解思路、算法要点与解决难点**

**核心思路**:  
所有题解均采用「离散化+差分」处理降雨的叠加影响，将降雨建模为斜率为±1的折线叠加。通过维护两个极值条件：$max(a_j+x_j)$ 和 $max(a_j-x_j)$，判断消除某次降雨后是否满足全局约束。

**关键步骤**:  
1. **差分处理**: 将每个降雨拆分为左右两个区间，用差分数组维护斜率和截距的变化。
2. **极值计算**: 离散化所有关键点后，遍历计算每个位置的最终积水值。
3. **条件判断**: 维护全局最大值 $mx1 = max(a_j - x_j)$ 和 $mx2 = max(a_j + x_j)$，消除第 $i$ 次降雨后需满足 $p_i - x_i + m \geq mx1$ 且 $p_i + x_i + m \geq mx2$。

**解决难点**:  
- **高效处理无限范围**: 离散化将无限位置压缩到有限关键点。
- **避免暴力检查**: 通过极值预处理将判断复杂度从 $O(n^2)$ 降至 $O(n)$。

---

### **题解评分 (≥4星)**

1. **ethan_zhou (5星)**:  
   - 思路清晰，利用几何直观解释极值条件。
   - 代码简洁，仅用单次遍历完成差分计算和极值维护。
   - 关键代码段仅需 20 行，可读性强。

2. **enucai (4星)**:  
   - 明确预处理每个降水中心的影响区间。
   - 使用二分查找确定左右边界，逻辑严谨。
   - 代码中差分数组处理稍显复杂，但注释清晰。

3. **览遍千秋 (4星)**:  
   - 详细推导不等式条件，逐步拆解问题。
   - 代码中维护多个差分数组，适合教学。
   - 多测清空逻辑明确，避免常见错误。

---

### **最优思路或技巧提炼**

1. **极值转化**: 将「所有位置 ≤ m」转化为两个全局极值的约束，避免逐点检查。
2. **差分建模**: 将降雨影响拆解为斜率和截距的差分事件，高效计算每个位置积水。
3. **离散化压缩**: 仅处理关键点（如降雨中心和影响边界），降低计算量。

---

### **同类型题或类似算法套路**

1. **区间叠加问题**: 如矩形面积并（扫描线算法）。
2. **极值约束优化**: 类似「最大子数组和」的变形，通过预处理极值避免重复计算。
3. **差分数组应用**: 适用于区间增减操作，如 CF1555E Boring Segments。

---

### **推荐相似题目**

1. **洛谷 P5490**: 扫描线求矩形面积并（离散化+差分）。
2. **洛谷 P1904**: 天际线问题（极值维护与事件驱动）。
3. **LeetCode 218**: The Skyline Problem（差分处理与极值）。

---

### **个人心得摘录**

- **多测清空**: 差分数组需清空到 $n+1$，否则残留数据导致错误（览遍千秋题解）。
- **极值初始化**: 初始值应设为 $-∞$，避免漏判正数极值（enucai题解）。
- **几何直观**: 将不等式转化为几何覆盖条件，简化代码逻辑（ethan_zhou题解）。

---

### **可视化与算法演示**

**核心动画设计**:  
1. **像素化网格**: 用 Canvas 绘制数轴，离散化后的关键点以像素块表示。
2. **差分事件展示**: 每次降雨的左右区间以不同颜色高亮，动态叠加斜率变化。
3. **极值标记**: 实时显示 $mx1$ 和 $mx2$ 的当前值，判断条件是否满足。

**复古游戏化要素**:  
- **音效设计**:  
  - 更新差分事件时播放 8-bit "点击" 音效。
  - 极值更新时播放上升音调，条件满足时播放成功音效。
- **自动演示模式**: 按步执行离散化、差分计算、极值判断，每步附带文字说明。
- **积分与连击**: 正确跳过冗余检查步骤奖励连击分，极值优化实现加速积分。

**交互控制**:  
- **速度调节**: 滑动条控制动画帧率（1x~10x）。
- **单步调试**: 逐步展示差分处理、极值计算、条件判断。

---

### **核心代码实现**

**ethan_zhou 的差分处理与极值判断**:  
```cpp
// 差分事件处理
map<ll, ll> delt;
for (ll i = 1; i <= n; i++) {
    cin >> x[i] >> p[i];
    delt[x[i] - p[i] + 1]++;
    delt[x[i] + 1] -= 2;
    delt[x[i] + p[i] + 1]++;
}

// 遍历计算极值
ll b = 0, k = 0, lastx = -INF;
ll b_1 = -INF, b1 = -INF;
for (auto it : delt) {
    b += k * (it.fi - lastx);
    k += it.se;
    if (b > m) {
        umx(b1, b - it.fi + 1);  // 维护 max(a_j - x_j)
        umx(b_1, b + it.fi - 1); // 维护 max(a_j + x_j)
    }
    lastx = it.fi;
}

// 判断每个降雨是否可行
for (ll i = 1; i <= n; i++) 
    cout << ((p[i]+m -x[i] >=b1) && (p[i]+m +x[i] >=b_1));
```

---
处理用时：83.00秒