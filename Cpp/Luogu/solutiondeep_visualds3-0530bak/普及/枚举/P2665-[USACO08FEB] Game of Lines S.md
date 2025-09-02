# 题目信息

# [USACO08FEB] Game of Lines S

## 题目背景

Farmer John 最近发明了一个游戏，来考验自命不凡的贝茜。


## 题目描述

Farmer John has challenged Bessie to the following game: FJ has a board with dots marked at N (2 ≤ N ≤ 200) distinct lattice points. Dot i has the integer coordinates Xi and Yi (-1,000 ≤ Xi ≤ 1,000; -1,000 ≤ Yi ≤ 1,000).

Bessie can score a point in the game by picking two of the dots and drawing a straight line between them; however, she is not allowed to draw a line if she has already drawn another line that is parallel to that line. Bessie would like to know her chances of winning, so she has asked you to help find the maximum score she can obtain.

游戏开始的时 候，FJ 会给贝茜一块画着 $N (2 \le N \le 200)$ 个不重合的点的木板，其中第 $i$ 个点的横、纵坐标分别为 $X_i$ 和 $Y_i (-1000 \le X_i \le 1000, -1000 \le Y_i \le 1000)$。

贝茜可以选两个点画一条过它们的直线，当且仅当平面上不存在与画出直线 平行的直线。游戏结束时贝茜的得分，就是她画出的直线的总条数。为了在游戏中胜出，贝茜找到了你，希望你帮她计算一下最大可能得分。


## 说明/提示

贝茜能画出以下 $4$ 种斜率的直线：$-1$，$0$，$\dfrac{1}{3}$ 以及 $1$。

## 样例 #1

### 输入

```
4 
-1 1 
-2 0 
0 0 
1 1```

### 输出

```
4 ```

# AI分析结果



### **算法分类**
数学（几何）、哈希表应用

---

### **题解思路与解决难点**
**核心思路**：遍历所有点对，计算其斜率并去重。  
**关键步骤**：
1. **斜率计算**：对每两点计算斜率，注意垂直线（x相同）和水平线（y相同）的特判。
2. **去重方法**：通过排序+遍历去重、集合（`set`/`map`）自动去重，或分数约分法避免浮点误差。
3. **浮点精度问题**：用分数的最简形式（分子分母约分）代替浮点数，或通过特殊值标记垂直线/水平线。

**难点对比**：
- **浮点法**：需处理垂直线/水平线，可能因精度导致错误判重。
- **分数约分法**：直接处理整数，避免精度问题，但需额外处理符号和特例。

---

### **题解评分（≥4星）**
1. **taoran的题解（5星）**  
   - **亮点**：用分数约分法解决浮点精度问题，通过哈希表记录最简分数，正确处理所有边界情况。
   - **代码片段**：
     ```cpp
     int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
     // 核心：dx和dy约分后存入哈希表
     if (dx == 0) ans += !dl, dl = 1; // 垂直线
     else if (dy == 0) ans += !ddl, ddl = 1; // 水平线
     else {
         int dd = gcd(dx, dy);
         if (!a[dx/dd + 2100][dy/dd + 2100]) ans++;
     }
     ```

2. **hmh13951417981的题解（4星）**  
   - **亮点**：使用 `map` 去重，代码简洁，用 `10000` 标记垂直线，适用于整数坐标范围。
   - **代码片段**：
     ```cpp
     if (x[i] == x[j]) x = 10000; // 垂直线
     else x = (y[i] - y[j]) / (x[i] - x[j]);
     if (!map[x]) ans++, map[x] = 1;
     ```

3. **planche的题解（4星）**  
   - **亮点**：利用 `set` 自动去重，用 `INF` 标记垂直线，代码简洁高效。
   - **代码片段**：
     ```cpp
     if (x[i] == x[j]) k.insert(INF); // 垂直线
     else k.insert((y[i] - y[j]) / (x[i] - x[j]));
     ```

---

### **最优思路提炼**
1. **分数约分法**：将斜率表示为最简分数 `(dx/dd, dy/dd)`，避免浮点误差，确保唯一性。
2. **哈希表优化**：用二维数组或 `unordered_map` 记录已存在的斜率，时间复杂度为 $O(n^2)$。
3. **特殊值标记**：用极大值（如 `INF`）标记垂直线，与普通斜率区分。

---

### **同类型题目推荐**
1. **P1355 图形面积**（计算几何，判断点线关系）
2. **P2789 直线交点数**（数学，枚举不同斜率）
3. **CF598C Nearest vectors**（极角排序，处理浮点精度）

---

### **可视化算法演示**
**动画设计**：
1. **网格绘制**：在 Canvas 上绘制坐标系，标出所有输入点。
2. **动态连线**：逐步生成点对，高亮当前计算的直线。
3. **斜率标记**：
   - **红色**：垂直线（标记为 `INF`）。
   - **蓝色**：水平线（斜率为 `0`）。
   - **绿色**：普通斜率，显示分数形式。
4. **去重提示**：若斜率已存在，显示“重复”提示并跳过计数。

**复古风格**：
- **像素效果**：用 8-bit 风格绘制点和线，背景音乐为 8-bit 音效。
- **音效反馈**：成功去重时播放“滴”声，发现新斜率时播放“叮”声。

---

### **核心代码实现（分数约分法）**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 2100;
bool dl, ddl; // 标记垂直线/水平线是否已存在
int a[MAX*2][MAX*2]; // 哈希表，偏移量避免负数

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    int n, x[205], y[205], ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int dx = x[i] - x[j], dy = y[i] - y[j];
            if (dx == 0) { // 垂直线
                if (!dl) ans++, dl = 1;
            } else if (dy == 0) { // 水平线
                if (!ddl) ans++, ddl = 1;
            } else {
                int dd = gcd(abs(dx), abs(dy));
                dx /= dd, dy /= dd;
                if (dx < 0) dx = -dx, dy = -dy; // 统一符号
                if (!a[dx + MAX][dy + MAX]) {
                    a[dx + MAX][dy + MAX] = 1;
                    ans++;
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
```

---
处理用时：260.93秒