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



## 算法分类
**二分答案**

---

## 题解思路与算法分析

### 核心思路
1. **二分答案框架**：通过二分可能的最小修改区间长度，判断是否存在长度为 `mid` 的区间满足条件。
2. **前缀和优化**：预处理前缀和数组，快速计算移除任意区间后的剩余坐标。
3. **曼哈顿距离与奇偶性条件**：判断剩余坐标与目标点的曼哈顿距离是否满足 `距离 ≤ 区间长度` 且 `差值偶`。

### 解决难点
- **快速计算剩余坐标**：通过前缀和数组 `sum_x` 和 `sum_y`，在 O(1) 时间内得到移除区间 `[l, r]` 后的坐标。
- **条件判断的数学推导**：修改区间内的操作可以任意调整，因此需满足剩余步数的奇偶性与曼哈顿距离一致。

---

## 题解评分（≥4星）

### 题解1：yeshubo_qwq（4.5星）
- **亮点**：代码简洁，注释清晰，前缀和与二分逻辑完整。
- **代码示例**：
```cpp
bool check(int l) {
    for (int i = 1; i + l - 1 <= n; i++) {
        int nx = sum_x[n] - (sum_x[i+l-1] - sum_x[i-1]);
        int ny = sum_y[n] - (sum_y[i+l-1] - sum_y[i-1]);
        int need = abs(nx - x) + abs(ny - y);
        if (l >= need && (l - need) % 2 == 0) return true;
    }
    return false;
}
```

### 题解2：JMercury（4星）
- **亮点**：代码规范，变量命名清晰，特判逻辑严谨。
- **关键代码**：
```cpp
if (len >= abs(x - nx) + abs(y - ny) && (len - (abs(x - nx) + abs(y - ny))) % 2 == 0)
    return true;
```

### 题解3：Zechariah（4星）
- **亮点**：代码高效，输入处理优化，条件判断简洁。
- **核心逻辑**：
```cpp
if (abs(x - fx) + abs(y - fy) <= mid && !(abs(x + y + fx + fy + mid) & 1))
    return true;
```

---

## 最优思路提炼
1. **前缀和预处理**：计算每一步的累积坐标，快速排除区间影响。
2. **二分条件验证**：对每个候选长度，枚举所有可能区间，验证是否满足曼哈顿距离和奇偶性条件。
3. **数学优化**：利用曼哈顿距离与剩余步数的奇偶性关系，避免暴力枚举所有可能的修改方式。

---

## 相似题目推荐
1. **CF1110B Tape**（二分答案 + 区间覆盖）
2. **P1147 连续自然数和**（滑动窗口求子段和）
3. **P1638 逛画展**（最短覆盖区间问题）

---

## 可视化设计思路

### 算法演示动画
1. **网格路径绘制**：用 Canvas 绘制机器人原始路径，每个操作对应一个网格移动。
2. **区间高亮**：用红色矩形框标注当前检查的修改区间 `[l, r]`。
3. **坐标对比**：显示剩余坐标与目标点的曼哈顿距离，动态更新条件判断结果。
4. **音效反馈**：成功时播放 8-bit 胜利音效，失败时播放低沉提示音。

### 复古像素风格
- **颜色方案**：使用 16 色调色板，路径为绿色，目标点为金色，当前区间为红色闪烁。
- **自动演示模式**：按空格键切换自动/手动步进，展示二分过程与区间验证。

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, x, y, sum_x[N], sum_y[N];
string s;

bool check(int len) {
    for (int l = 1, r = len; r <= n; l++, r++) {
        int nx = sum_x[n] - (sum_x[r] - sum_x[l-1]);
        int ny = sum_y[n] - (sum_y[r] - sum_y[l-1]);
        int need = abs(nx - x) + abs(ny - y);
        if (len >= need && (len - need) % 2 == 0) return true;
    }
    return false;
}

int main() {
    cin >> n >> s >> x >> y;
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
        int mid = (l + r) >> 1;
        if (check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << (ans != -1 && check(ans) ? ans : -1);
    return 0;
}
```

---

## 个人心得
- **调试教训**：初始代码未处理原序列已满足条件的情况，导致错误。
- **思维突破**：通过奇偶性条件简化判断，避免遍历所有可能的修改方式。

---
处理用时：125.86秒