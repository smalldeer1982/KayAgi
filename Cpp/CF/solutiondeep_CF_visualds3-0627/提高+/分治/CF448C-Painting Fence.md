# 题目信息

# Painting Fence

## 题目描述

Bizon the Champion isn't just attentive, he also is very hardworking.

Bizon the Champion decided to paint his old fence his favorite color, orange. The fence is represented as $ n $ vertical planks, put in a row. Adjacent planks have no gap between them. The planks are numbered from the left to the right starting from one, the $ i $ -th plank has the width of $ 1 $ meter and the height of $ a_{i} $ meters.

Bizon the Champion bought a brush in the shop, the brush's width is $ 1 $ meter. He can make vertical and horizontal strokes with the brush. During a stroke the brush's full surface must touch the fence at all the time (see the samples for the better understanding). What minimum number of strokes should Bizon the Champion do to fully paint the fence? Note that you are allowed to paint the same area of the fence multiple times.

## 说明/提示

In the first sample you need to paint the fence in three strokes with the brush: the first stroke goes on height 1 horizontally along all the planks. The second stroke goes on height 2 horizontally and paints the first and second planks and the third stroke (it can be horizontal and vertical) finishes painting the fourth plank.

In the second sample you can paint the fence with two strokes, either two horizontal or two vertical strokes.

In the third sample there is only one plank that can be painted using a single vertical stroke.

## 样例 #1

### 输入

```
5
2 2 1 2 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
2 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1
5
```

### 输出

```
1
```

# AI分析结果



# 算法分类
分治算法 + 贪心策略

---

# 题解思路与核心难点

**核心思路**  
所有题解均采用分治+贪心策略。核心步骤为：  
1. 在区间中找到最小高度，横涂该高度（贪心选择最优操作）  
2. 将区间分割为若干子区间（由最低点分割）  
3. 递归处理子问题，并比较横涂总次数与全竖涂次数  

**解决难点**  
- **区间分割**：需正确处理横涂后产生的非连续子区间，如样例1中横涂高度1后分割为[2,2]、[1]、[2,1]  
- **决策比较**：需动态比较横涂与竖涂的优劣，如样例2中两种涂法等价  
- **复杂度优化**：部分题解（如线段树解法）优化了最小值查找的复杂度  

**可视化设计要点**  
1. **动画流程**：  
   - 红色高亮当前处理的区间  
   - 黄色横向笔刷表示横涂操作，高度为当前区间最小值  
   - 递归分割时用虚线框标记子区间  
   - 右侧面板动态显示两种策略的计数值  
2. **复古风格**：  
   - 栅栏用8位像素风格绘制，高度映射为不同颜色块  
   - 横涂时播放类似《超级马里奥》金币音效，竖涂时用短促按键音  
   - 每次递归分割时，屏幕边缘闪烁提示当前层级  

---

# 题解评分

1. **wmy_goes_to_thu** (★★★★☆)  
   亮点：代码简洁，递归边界处理清晰  
   不足：未显式处理分割后的子区间合并  

2. **colemak** (★★★★★)  
   亮点：详细注释、显式子区间分割逻辑  
   技巧：使用`minh-hi`避免重复计算已涂部分  

3. **crh1272336175** (★★★★☆)  
   亮点：线段树优化最小值查询至O(n log n)  
   创新：完全避免递归分割的冗余扫描  

---

# 最优思路提炼

**关键步骤**  
```cpp
int solve(int l, int r, int base) {
    if (l > r) return 0;
    int minh = find_min(l, r);      // 步骤1：找当前区间最小值
    int ans = minh - base;          // 横涂当前层的次数
    for (分割后的每个子区间)        // 步骤2：处理分割产生的子问题
        ans += solve(sub_l, sub_r, minh);
    return min(ans, r - l + 1);     // 步骤3：比较两种策略
}
```

**思维突破点**  
- 将竖涂视为每个栅独立操作，总次数为区间长度  
- 横涂次数=当前层高度差 + 子问题递归解  

---

# 类似题目

1. **积木大赛** (NOIP2018D1T1, P5019)  
   核心：每次操作覆盖连续区间的最优解  

2. **合并果子** (P1090)  
   关联：贪心选择当前最小代价  

3. **Segment Painting** (CF52C)  
   扩展：区间操作与分治结合  

---

# 代码实现片段

**线段树优化版核心逻辑**  
```cpp
int query_min(int l, int r) { /* 返回区间最小值位置 */ }

int dfs(int l, int r, int base_h) {
    if (l > r) return 0;
    int pos = query_min(l, r);
    int minh = h[pos];
    int hor = (minh - base_h) 
        + dfs(l, pos-1, minh) 
        + dfs(pos+1, r, minh);
    return min(hor, r - l + 1);
}
```

---

# 可视化算法演示

**Canvas动画关键帧**  
1. 初始状态：所有栅栏显示为白色  
2. 第一帧：红色框选中整个区间，显示最小高度为1  
3. 横涂动画：黄色横线从下至上覆盖高度1区域  
4. 分割效果：被涂区域分裂为三个子区间，虚线框高亮  
5. 递归过程：对每个子区间重复上述步骤  

**音效设计**  
- `横涂音效`: 8-bit风格短笛音，持续时长与涂刷宽度相关  
- `竖涂音效`: 类似激光枪的单音阶提示音  
- `决策比较`: 当选择更优策略时播放金币收集声  

**自动演示模式**  
- 按空格键暂停/继续  
- 方向键控制动画速度  
- F键切换横/竖涂的高亮显示  

---

**注**：完整实现代码与交互式Demo需结合具体前端框架开发，此处为核心算法逻辑与可视化设计说明。

---
处理用时：74.04秒