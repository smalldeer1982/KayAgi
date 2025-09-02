# 题目信息

# Vasya and Robot

## 题目描述

Vasya has got a robot which is situated on an infinite Cartesian plane, initially in the cell $ (0, 0) $ . Robot can perform the following four kinds of operations:

- U — move from $ (x, y) $ to $ (x, y + 1) $ ;
- D — move from $ (x, y) $ to $ (x, y - 1) $ ;
- L — move from $ (x, y) $ to $ (x - 1, y) $ ;
- R — move from $ (x, y) $ to $ (x + 1, y) $ .

Vasya also has got a sequence of $ n $ operations. Vasya wants to modify this sequence so after performing it the robot will end up in $ (x, y) $ .

Vasya wants to change the sequence so the length of changed subsegment is minimum possible. This length can be calculated as follows: $ maxID - minID + 1 $ , where $ maxID $ is the maximum index of a changed operation, and $ minID $ is the minimum index of a changed operation. For example, if Vasya changes RRRRRRR to RLRRLRL, then the operations with indices $ 2 $ , $ 5 $ and $ 7 $ are changed, so the length of changed subsegment is $ 7 - 2 + 1 = 6 $ . Another example: if Vasya changes DDDD to DDRD, then the length of changed subsegment is $ 1 $ .

If there are no changes, then the length of changed subsegment is $ 0 $ . Changing an operation means replacing it with some operation (possibly the same); Vasya can't insert new operations into the sequence or remove them.

Help Vasya! Tell him the minimum length of subsegment that he needs to change so that the robot will go from $ (0, 0) $ to $ (x, y) $ , or tell him that it's impossible.

## 说明/提示

In the first example the sequence can be changed to LULUU. So the length of the changed subsegment is $ 3 - 1 + 1 = 3 $ .

In the second example the given sequence already leads the robot to $ (x, y) $ , so the length of the changed subsegment is $ 0 $ .

In the third example the robot can't end his path in the cell $ (x, y) $ .

## 样例 #1

### 输入

```
5
RURUU
-2 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
RULR
1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
UUU
100 100
```

### 输出

```
-1
```

# AI分析结果



**唯一算法分类**：二分答案

---

### **综合分析与结论**

**核心思路**：
- **前缀和预处理**：记录每个操作后的累计坐标，便于快速计算任意区间的位移。
- **二分答案**：确定最小修改区间长度。若长度 `len` 可行，则更大长度必然可行，满足单调性。
- **条件判断**：对于候选区间 `[l, r]`，计算剩余位移到目标的曼哈顿距离 `d`。若 `len ≥ d` 且 `(len - d) % 2 == 0`，则可通过修改此区间达到目标。

**难点与解决**：
- **快速计算剩余位移**：通过前缀和数组在 `O(1)` 时间内计算任意区间的位移。
- **奇偶性匹配**：确保剩余步数能通过往返移动覆盖差距。

**可视化设计**：
- **Canvas网格动画**：绘制机器人路径，当前检查的区间高亮为红色，剩余位移用箭头表示。
- **像素风格**：8位复古UI，机器人移动时播放方向键音效，成功时播放通关音效。
- **步进控制**：展示二分过程中 `mid` 的变化，可行区间显示为绿色，不可行显示红色。

---

### **题解清单（≥4星）**

1. **JMercury的题解（5星）**  
   - **亮点**：代码结构清晰，变量命名明确，处理了所有边界条件，可读性高。
   - **关键代码**：利用前缀和快速计算剩余位移，判断条件简洁。

2. **yeshubo_qwq的题解（4星）**  
   - **亮点**：思路详细，包含样例分析，适合初学者理解。
   - **关键代码**：二分框架与 `check` 函数分离，逻辑分明。

3. **Zechariah的题解（4星）**  
   - **亮点**：代码简洁高效，包含奇偶性判断的优化。
   - **关键代码**：前缀和预处理与二分结合紧密。

---

### **核心代码实现**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;

int n, x_goal, y_goal;
int sum_x[maxn], sum_y[maxn];
string s;

bool check(int len) {
    for (int l = 1, r = len; r <= n; l++, r++) {
        int x_remain = sum_x[n] - (sum_x[r] - sum_x[l-1]);
        int y_remain = sum_y[n] - (sum_y[r] - sum_y[l-1]);
        int d = abs(x_goal - x_remain) + abs(y_goal - y_remain);
        if (d <= len && (len - d) % 2 == 0) return true;
    }
    return false;
}

int main() {
    cin >> n >> s >> x_goal >> y_goal;
    for (int i = 1; i <= n; i++) {
        sum_x[i] = sum_x[i-1];
        sum_y[i] = sum_y[i-1];
        switch(s[i-1]) {
            case 'U': sum_y[i]++; break;
            case 'D': sum_y[i]--; break;
            case 'L': sum_x[i]--; break;
            case 'R': sum_x[i]++; break;
        }
    }
    
    int l = 0, r = n, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

### **同类型题目推荐**

1. **CF1110B Tape**  
   - 利用二分答案寻找最小覆盖区间。
2. **LeetCode 209. Minimum Size Subarray Sum**  
   - 滑动窗口或二分法求最短子数组。
3. **洛谷P1182 数列分段**  
   - 二分答案判断可行性。

---

### **个人心得摘录**

- **调试经历**：原题解中多位作者提到，初次未正确处理奇偶性导致WA，强调条件判断的严谨性。
- **优化顿悟**：通过前缀和将时间复杂度从 `O(n^2)` 优化至 `O(n logn)`，是典型的空间换时间策略。

---

### **可视化与游戏化设计**

**动画方案**：
- **网格绘制**：机器人路径显示为网格，每个操作对应箭头。
- **区间高亮**：当前二分检查的区间用红色边框标记，成功时变绿。
- **音效反馈**：移动时播放方向音效，成功时播放8-bit胜利音效。

**复古风格**：
- **16色调色板**：使用经典FC颜色（如#FF0000表错误，#00FF00表成功）。
- **自动演示模式**：AI自动调整二分区间，用户可暂停观察中间状态。

**交互控制**：
- **速度调节**：滑动条控制动画速度（慢速学习/快速浏览）。
- **单步执行**：逐步展示二分过程，观察条件判断细节。

---
处理用时：154.69秒