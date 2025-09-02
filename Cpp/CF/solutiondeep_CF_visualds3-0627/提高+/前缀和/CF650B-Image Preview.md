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

### **唯一算法分类**  
**双指针（滑动窗口）** 结合 **环形处理**

---

### **综合分析与结论**  
**核心思路**：  
1. 将环形数组复制成 2n 长度线性数组，便于处理环形移动。  
2. 使用双指针维护当前能查看的照片区间，动态计算总时间。  
3. 总时间包括滑动时间、方向调整时间、查看时间，需满足 T 限制。  

**解决难点**：  
- **环形移动** → 通过数组复制转化为线性问题。  
- **时间计算** → 滑动时间根据区间长度计算，方向调整时间预处理为数组。  
- **最优区间选择** → 双指针动态调整左右边界，寻找最大合法区间。  

**可视化设计**：  
- **Canvas 动画**：  
  - 绘制 2n 长度的照片序列，用不同颜色表示已查看/未查看照片。  
  - 高亮左右指针（红蓝方块），步进展示指针移动与区间扩展。  
  - 右侧面板实时显示总时间消耗和当前照片数。  
- **音效设计**：  
  - 指针移动时播放“滴”声，区间调整时播放“咔嗒”声。  
  - 超过时间限制时触发短促警报音。  
- **复古风格**：  
  - 使用 8-bit 像素字体和 16 色调色板（如 NES 经典配色）。  
  - 背景循环播放低音量芯片音乐（如《超级马里奥》地下城 BGM）。  

---

### **题解清单 (≥4星)**  
1. **chufuzhe（★★★★☆）**  
   - **亮点**：环形转线性 + 双指针滑动窗口，时间复杂度 O(n)。  
   - **代码简析**：通过复制数组处理环形，滑动窗口动态计算时间。  
   - **关键代码**：  
     ```cpp
     while (l <= n && r < 2 * n) {
         s += q[r]; r++;
         while (条件不满足) { s -= q[l]; l++; }
         ans = max(ans, r - l);
     }
     ```  

2. **tzc_wk（★★★★☆）**  
   - **亮点**：二分答案 + 前缀和优化，时间复杂度 O(n logn)。  
   - **代码简析**：枚举查看照片数，利用前缀和快速计算不同路径时间。  
   - **关键判断**：  
     ```cpp
     lint sum1 = w[i] + (w[n] - w[n - (m - i)]);
     lint sum2 = min((i-1)*a*2 + (m-i)*a, (i-1)*a + (m-i)*a*2);
     ```  

---

### **最优思路与技巧提炼**  
1. **环形转线性**：复制数组为 2n 长度，消除环形移动的复杂性。  
2. **双指针滑动窗口**：维护当前窗口的总时间，动态调整左右边界。  
3. **时间拆分计算**：  
   - 滑动时间 = (窗口长度 - 1) * a  
   - 查看时间 = 预处理的方向调整时间之和  
4. **数学优化**：最小化滑动路径（如先左后右 vs 先右后左）。  

---

### **同类型题推荐**  
1. **滑动窗口经典题**：洛谷 P1886（滑动窗口极值）  
2. **环形处理**：洛谷 P3405（环形公路旅行）  
3. **时间限制优化**：洛谷 P1419（段落分割问题）  

---

### **核心代码实现**  
以 **chufuzhe 的题解**为例：  
```cpp
int main() {
    // ... 输入处理与预处理 ...
    for (int i = 0; i < n; i++) {
        q[i] = q[i + n] = (c[i] == 'w') ? (b + 1) : 1;
        if (i != 0) s += q[i];
    }
    int l = 1, r = n;
    while (l <= n && r < 2 * n) {
        s += q[r++];
        while (r - l > n || s + (r - l - 1 + min(r - n - 1, n - l)) * a > t) {
            s -= q[l++];
        }
        ans = max(ans, r - l);
    }
    cout << ans << endl;
}
```

---

### **可视化算法演示**  
1. **初始化阶段**：  
   - 绘制 2n 长度的照片序列，第 1 张高亮为绿色（初始位置）。  
2. **指针移动**：  
   - 右指针 `r` 向右扩展（蓝色方块），累加时间。  
   - 时间超限时，左指针 `l` 右移（红色方块），减少时间。  
3. **动态统计**：  
   - 顶部显示当前查看照片数 `ans` 和剩余时间 `T - total_time`。  
4. **音效触发**：  
   - 每次指针移动播放“滴”声，区间更新时播放“叮”声。  

---

**总结**：双指针滑动窗口是本题最优解，结合环形转线性技巧，能在 O(n) 时间内高效求解。通过预处理方向调整时间，动态维护窗口总时间，是解决此类滑动时间限制问题的通用思路。

---
处理用时：69.52秒