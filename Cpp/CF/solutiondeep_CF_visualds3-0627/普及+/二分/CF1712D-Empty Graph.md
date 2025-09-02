# 题目信息

# Empty Graph

## 题目描述

— Do you have a wish?



 — I want people to stop gifting each other arrays.

O_o and Another Young Boy



An array of $ n $ positive integers $ a_1,a_2,\ldots,a_n $ fell down on you from the skies, along with a positive integer $ k \le n $ .

You can apply the following operation at most $ k $ times:

- Choose an index $ 1 \le i \le n $ and an integer $ 1 \le x \le 10^9 $ . Then do $ a_i := x $ (assign $ x $ to $ a_i $ ).

Then build a [complete](https://en.wikipedia.org/wiki/Complete_graph) undirected weighted graph with $ n $ vertices numbered with integers from $ 1 $ to $ n $ , where edge $ (l, r) $ ( $ 1 \le l < r \le n $ ) has weight $ \min(a_{l},a_{l+1},\ldots,a_{r}) $ .

You have to find the maximum possible diameter of the resulting graph after performing at most $ k $ operations.

The diameter of a graph is equal to $ \max\limits_{1 \le u < v \le n}{\operatorname{d}(u, v)} $ , where $ \operatorname{d}(u, v) $ is the length of the shortest path between vertex $ u $ and vertex $ v $ .

## 说明/提示

In the first test case, one of the optimal arrays is $ [2,4,5] $ .

The graph built on this array:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1712D/6f5937a14546fd0344ab2a7ad56768b75a98a230.png) $ \operatorname{d}(1, 2) = \operatorname{d}(1, 3) = 2 $ and $ \operatorname{d}(2, 3) = 4 $ , so the diameter is equal to $ \max(2,2,4) = 4 $ .

## 样例 #1

### 输入

```
6
3 1
2 4 1
3 2
1 9 84
3 1
10 2 6
3 2
179 17 1000000000
2 1
5 9
2 2
4 2```

### 输出

```
4
168
10
1000000000
9
1000000000```

# AI分析结果



# 算法分类  
**二分**

---

## 题解思路与算法要点  
### 核心思路  
题目要求最大化图的直径，即所有点对间最短路径的最大值。通过分析发现：  
1. 两点间最短路径可能有两种情况：  
   - 直连路径的区间最小值  
   - 经过全局最小值点的两倍最小值路径  
2. **二分答案**：确定一个候选直径 `mid`，验证是否可以通过 `k` 次操作达成目标  

### 二分算法关键步骤  
1. **搜索区间**：`left=1`, `right=1e9`（值域范围）  
2. **条件判断**：对于候选值 `mid`，检查：  
   - 所有 `2*a[i] < mid` 的元素必须被修改为 `1e9`，统计修改次数 `cnt`  
   - 剩余次数 `k-cnt` 需满足相邻元素的最小值 ≥ `mid`  
3. **区间收缩**：若满足条件则扩大 `left`，否则缩小 `right`  

### 解决难点  
1. **全局与局部约束**：需同时满足全局最小值两倍 ≥ `mid` 和相邻元素的最小值 ≥ `mid`  
2. **高效统计修改次数**：通过前缀和/后缀和预处理需要修改的区域  

---

## 题解评分（≥4星）  
1. **Dregen_Yor（5星）**  
   - 思路清晰，通过二分+贪心统计修改次数  
   - 代码简洁，逻辑覆盖全面  
   - 核心代码片段：  
     ```cpp  
     bool check(int mid) {  
         int cnt = 0;  
         for(int i=1; i<=n; ++i)  
             if(2*a[i]<mid) cnt++, a[i]=1e9;  
         if(cnt > k) return false;  
         // 检查相邻元素  
     }  
     ```  

2. **Jr_Zlw（4.5星）**  
   - 预处理前缀和优化统计  
   - 使用 `cntl` 和 `cntr` 数组快速计算修改次数  
   - 关键实现：  
     ```cpp  
     int sum = pre[i-1] + sub[i+2] + (a[i]<mid) + (a[i+1]<mid);  
     ```  

3. **Symbolize（4星）**  
   - 通过动态规划思想维护前后缀  
   - 结合像素动画设计思路，代码可读性强  

---

## 最优思路提炼  
1. **二分答案框架**：将最值问题转化为可行性验证问题  
2. **双重约束处理**：全局最小值两倍和相邻元素最小值分开统计  
3. **前缀和优化**：快速计算需要修改的区域，避免重复扫描数组  

---

## 类似算法题目  
1. **P2678 跳石头**（二分答案+最小距离最大化）  
2. **P2440 木材加工**（二分最大切割长度）  
3. **P4343 [SHOI2015]自动刷题机**（二分答案验证可行性）  

---

## 可视化与算法演示  
### 动画设计  
1. **区间动态展示**：  
   - 用 Canvas 绘制 `[left, right]` 区间，高亮当前 `mid`  
   - 颜色标记：`left`（蓝色），`right`（红色），`mid`（黄色）  
2. **修改统计演示**：  
   - 数组元素以条形图展示，`2*a[i]<mid` 的元素闪烁并变为 `1e9`  
   - 相邻元素用连线标注，满足条件时显示绿色，否则红色  
3. **音效与交互**：  
   - 更新 `mid` 时播放“哔”声，找到解时播放成功音效  
   - 支持暂停/步进，调整动画速度  

### 复古像素风格  
- **8-bit 主题**：使用 NES 调色板（深蓝、品红、青绿）  
- **网格绘制**：区间以方块表示，收缩时动态擦除  
- **音效设计**：  
  - 移动区间：8-bit 点击声  
  - 验证成功：经典马里奥金币音  

---

## 核心代码实现  
```cpp  
bool check(int mid) {
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] * 2 < mid) cnt++, a[i] = 1e9;
    }
    if (cnt > k) return false;
    int need = 2; // 剩余次数处理相邻
    for (int i = 1; i < n; ++i) {
        if (min(a[i], a[i+1]) >= mid) need = 0;
        else if (max(a[i], a[i+1]) >= mid) need = min(need, 1);
    }
    return cnt + need <= k;
}
```

---

## 个人心得  
- **边界陷阱**：注意 `mid` 计算时整数溢出，使用 `mid = l + (r-l)/2`  
- **贪心转化**：将前 `k-1` 小元素置为 `1e9` 的观察是关键突破口  
- **调试技巧**：构造极端测试数据（如全1数组）验证逻辑  

通过二分框架统一处理复杂约束，结合高效统计方法，是解决此类最优化问题的通用范式。

---
处理用时：77.61秒