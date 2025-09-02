# 题目信息

# Image Preview

## 题目描述

Vasya's telephone contains $ n $ photos. Photo number 1 is currently opened on the phone. It is allowed to move left and right to the adjacent photo by swiping finger over the screen. If you swipe left from the first photo, you reach photo $ n $ . Similarly, by swiping right from the last photo you reach photo $ 1 $ . It takes $ a $ seconds to swipe from photo to adjacent.

For each photo it is known which orientation is intended for it — horizontal or vertical. Phone is in the vertical orientation and can't be rotated. It takes $ b $ second to change orientation of the photo.

Vasya has $ T $ seconds to watch photos. He want to watch as many photos as possible. If Vasya opens the photo for the first time, he spends $ 1 $ second to notice all details in it. If photo is in the wrong orientation, he spends $ b $ seconds on rotating it before watching it. If Vasya has already opened the photo, he just skips it (so he doesn't spend any time for watching it or for changing its orientation). It is not allowed to skip unseen photos.

Help Vasya find the maximum number of photos he is able to watch during $ T $ seconds.

## 说明/提示

In the first sample test you can rotate the first photo (3 seconds), watch the first photo (1 seconds), move left (2 second), rotate fourth photo (3 seconds), watch fourth photo (1 second). The whole process takes exactly 10 seconds.

Note that in the last sample test the time is not enough even to watch the first photo, also you can't skip it.

## 样例 #1

### 输入

```
4 2 3 10
wwhw
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 2 4 13
hhwhh
```

### 输出

```
4
```

## 样例 #3

### 输入

```
5 2 4 1000
hhwhh
```

### 输出

```
5
```

## 样例 #4

### 输入

```
3 1 100 10
whw
```

### 输出

```
0
```

# AI分析结果



---

**算法分类选择**  
滑动窗口/尺取法

---

**题解思路、算法要点与解决难点**  

**核心思路对比**  
1. **尺取法（题解一）**  
   - **环形展开**：将原数组复制一份拼接成 2n 长度，解决环形移动问题。  
   - **双指针维护窗口**：左指针 `l` 和右指针 `r` 维护当前可行区间，确保总时间不超过 `T`。  
   - **时间计算**：  
     - 照片处理时间：预处理为 `q[i] = 1`（无需调整）或 `b+1`（需调整）。  
     - 移动时间：结合窗口长度和绕行路径的最短选择 `min(r-n-1, n-l)`。  
   - **难点**：正确推导移动时间的组合计算式，确保环形路径的最优性。

2. **二分法（题解二）**  
   - **二分答案**：枚举最大可看照片数 `m`，验证是否存在可行方案。  
   - **前缀和优化**：预处理照片处理时间前缀和，快速计算区间总和。  
   - **移动路径选择**：对每个 `m`，枚举左右分配，取最小移动时间（顺时针或逆时针）。  
   - **难点**：枚举左右分配时的边界处理，确保不遗漏可能的路径组合。

**精炼结论**  
最优解法为 **尺取法**，时间复杂度 `O(n)`，核心在于将环形问题转化为线性滑动窗口，结合双指针动态调整窗口，并正确计算移动和处理时间的组合。

---

**题解评分（≥4星）**  
1. **题解一（chufuzhe）**  
   - **思路清晰度**：★★★★☆  
   - **代码可读性**：★★★☆☆（变量命名可优化）  
   - **算法优化**：★★★★★（线性复杂度）  
   - **实践可操作性**：★★★★☆  
   - **总评**：★★★★☆  

2. **题解二（tzc_wk）**  
   - **思路清晰度**：★★★★☆  
   - **代码可读性**：★★★★☆（结构清晰）  
   - **算法优化**：★★★★☆（对数复杂度）  
   - **实践可操作性**：★★★★☆  
   - **总评**：★★★★☆  

---

**最优思路或技巧提炼**  
1. **环形展开**：将 `n` 长数组复制为 `2n`，简化环形移动为线性区间问题。  
2. **双指针动态窗口**：维护窗口 `[l, r)`，通过调整 `l` 和 `r` 确保总时间合法。  
3. **移动时间优化**：取绕行路径的最短移动次数，公式为 `min(r-n-1, n-l)`。  

---

**同类型题或类似算法套路**  
- **环形数组问题**：如「环形加油站问题」「循环队列设计」。  
- **滑动窗口优化**：如「最小覆盖子串」「最长无重复子串」。  

---

**推荐洛谷题目**  
1. P1886 滑动窗口（模板题）  
2. P3403 跳楼机（环形+最短路）  
3. P1091 合唱队形（环形动态规划）  

---

**个人心得摘录**  
- **环形处理**：复制数组是常见技巧，但需注意索引转换。  
- **时间计算**：移动和处理时间的组合容易出错，需多次验证。  

---

**可视化与算法演示**  
**动画设计**：  
1. **环形展开**：将原数组复制并拼接为两倍长度，高亮复制部分。  
2. **双指针移动**：  
   - 初始窗口 `[1, n)`，包含原数组起点。  
   - `r` 右移时，高亮新增照片的处理时间（红色）。  
   - `l` 左移时，灰色标记被排除的照片，动态更新总时间。  
3. **路径选择**：用不同颜色箭头表示顺时针/逆时针移动，实时显示最短路径。  

**复古像素风格**：  
- **颜色方案**：照片状态用 8 色调色板（绿：已处理，红：新增，灰：排除）。  
- **音效触发**：指针移动时播放「滴」声，总时间超限时播放「错误」音效。  

**核心代码片段（题解一）**  
```cpp
int main() {
    // 预处理照片处理时间
    for (int i = 0; i < n; i++) {
        q[i] = q[i+n] = (c[i] == 'w') ? b+1 : 1;
        if (i != 0) s += q[i];
    }
    int l = 1, r = n, ans = 0;
    while (l <= n && r < 2*n) {
        s += q[r++]; // 扩展右边界
        // 调整左边界直到时间合法
        while (r-l > n || s + (r-l-1 + min(r-n-1, n-l)) * a > t) {
            s -= q[l++];
        }
        ans = max(ans, r - l);
    }
    cout << ans;
}
```

---

**可视化设计要点**  
- **Canvas 绘制**：用网格表示照片，指针移动时动态更新颜色。  
- **自动演示**：按步长自动扩展 `r` 和调整 `l`，展示窗口变化。  
- **音效触发**：每次移动播放 8-bit 音效，成功时播放胜利旋律。  

---

---
处理用时：308.23秒