# 题目信息

# Machine Learning

## 题目描述

You come home and fell some unpleasant smell. Where is it coming from?

You are given an array $ a $ . You have to answer the following queries:

1. You are given two integers $ l $ and $ r $ . Let $ c_{i} $ be the number of occurrences of $ i $ in $ a_{l:r} $ , where $ a_{l:r} $ is the subarray of $ a $ from $ l $ -th element to $ r $ -th inclusive. Find the Mex of $ {c_{0},c_{1},...,c_{10^{9}}} $
2. You are given two integers $ p $ to $ x $ . Change $ a_{p} $ to $ x $ .

The Mex of a multiset of numbers is the smallest non-negative integer not in the set.

Note that in this problem all elements of $ a $ are positive, which means that $ c_{0} $ = 0 and $ 0 $ is never the answer for the query of the second type.

## 说明/提示

The subarray of the first query consists of the single element — $ 1 $ .

The subarray of the second query consists of four $ 2 $ s, one $ 3 $ and two $ 1 $ s.

The subarray of the fourth query consists of three $ 1 $ s, three $ 2 $ s and one $ 3 $ .

## 样例 #1

### 输入

```
10 4
1 2 3 1 1 2 2 2 9 9
1 1 1
1 2 8
2 7 1
1 2 8
```

### 输出

```
2
3
2
```

# AI分析结果



# 算法分类
**带修莫队**

---

## 综合分析与结论
### 核心思路与难点
1. **带修莫队框架**：在普通莫队基础上增加时间轴，处理单点修改。每次查询需维护当前区间和修改时间戳。
2. **离散化**：元素值域极大（1e9），需将所有数值离散化为连续整数，避免使用 `map` 导致性能问题。
3. **暴力求 mex 的合理性**：mex 值的理论最大为 O(√n)，暴力枚举的复杂度为 O(√n)，不影响总复杂度 O(n^(5/3))。
4. **高效维护出现次数**：用 `cnt[x]` 记录数值 x 的出现次数，`tot[y]` 记录出现次数为 y 的数值个数，动态更新。

### 可视化设计思路
1. **动画流程**：
   - **指针移动**：左右指针移动时，用高亮色块标记当前元素，更新 `cnt` 和 `tot` 数组。
   - **时间轴修改**：展示修改操作的回滚与推进，交换元素时用闪烁动画突出变化。
   - **mex 计算**：逐格扫描 `tot` 数组，高亮当前检查的数值，找到第一个缺失值。
2. **复古像素风格**：
   - **颜色方案**：使用 8-bit 色系（红、蓝、绿）区分元素类型（原数组、cnt、tot）。
   - **Canvas 网格**：将数组元素绘制为像素块，每次操作触发块颜色变化，配以 8-bit 音效（如“哔”声提示 mex 更新）。
3. **交互功能**：步进控制面板支持暂停/继续，调整动画速度；自动演示模式模拟算法流程，可观察指针与时间轴同步变化。

---

## 题解清单（评分 ≥4星）
1. **ouuan（★★★★★）**
   - **亮点**：代码简洁，离散化处理彻底；用 `tot` 数组维护出现次数的出现次数，暴力 mex 查询高效。
   - **核心代码**：
     ```cpp
     void add(int x) { --tot[cnt[x]]; ++tot[++cnt[x]]; }
     void del(int x) { --tot[cnt[x]]; ++tot[--cnt[x]]; }
     mex查询: for (ans=1; tot[ans]; ++ans);
     ```

2. **juju527（★★★★☆）**
   - **亮点**：严格证明 mex 的 O(√n) 上界，提供理论依据；代码结构清晰，变量命名规范。
   - **关键注释**：`mex 最大为 (-1+sqrt(1+8n))/2`，预处理离散化数组时一并处理修改值。

3. **BFqwq（★★★★☆）**
   - **亮点**：严格复杂度分析，强调离散化必要性；代码中 `cnt1` 和 `cnt2` 命名清晰，逻辑易读。
   - **优化点**：`ans` 变量实时维护当前 mex，减少查询时的循环次数。

---

## 核心代码实现
### 带修莫队主循环
```cpp
int l=1, r=0, now=0;
for (int i=1; i<=qcnt; ++i) {
    while (l > q[i].l) add(a[--l]);
    while (r < q[i].r) add(a[++r]);
    while (l < q[i].l) del(a[l++]);
    while (r > q[i].r) del(a[r--]);
    while (now < q[i].t) modify(++now, i); // 处理后续修改
    while (now > q[i].t) modify(now--, i); // 回滚到历史版本
    ans[q[i].id] = 1;
    while (tot[ans[q[i].id]]) ++ans[q[i].id];
}
```

### 离散化处理
```cpp
sort(b, b+len);
len = unique(b, b+len) - b;
for (int i=1; i<=n; ++i)
    a[i] = lower_bound(b, b+len, a[i]) - b;
for (修改操作 c) 
    c.val = lower_bound(b, b+len, c.val) - b;
```

---

## 同类型题与推荐
1. **P1903 [国家集训队] 数颜色 / 维护队列**：带修莫队模板题，维护不同颜色数量。
2. **P4137 Rmq Problem / mex**：静态区间 mex 查询，可用回滚莫队。
3. **P4074 [WC2013] 糖果公园**：树上带修莫队，结合树上路径查询。

---

## 个人心得摘录
- **ouuan**：强调离散化必须包含修改后的值，否则会导致越界。
- **juju527**：调试时发现未处理修改值的离散化导致 RE，提醒全面性。
- **Strelitzia**：初始使用 `unordered_map` 导致 TLE，改用数组后 AC。

---

## 可视化示例（复古像素风格）
```javascript
// 伪代码：Canvas绘制元素出现次数
function drawBlocks() {
    ctx.fillStyle = '#8B0000'; // 深红背景
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    // 绘制原数组
    for (let i=0; i<n; ++i) {
        ctx.fillStyle = getColor(a[i]); // 根据离散化值映射颜色
        ctx.fillRect(i*10, 50, 8, 8);
    }
    // 绘制cnt数组
    for (let i=0; i<maxCnt; ++i) {
        ctx.fillStyle = cnt[i] ? '#00FF00' : '#0000FF'; // 绿：存在，蓝：不存在
        ctx.fillRect(i*10, 100, 8, 8);
    }
    // 播放音效
    if (step % 2 == 0) beep(440, 50); // 指针移动音效
}
```

---
处理用时：67.51秒