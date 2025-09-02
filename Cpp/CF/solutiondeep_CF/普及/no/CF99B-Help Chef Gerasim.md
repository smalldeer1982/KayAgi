# 题目信息

# Help Chef Gerasim

## 题目描述

In a far away kingdom young pages help to set the table for the King. As they are terribly mischievous, one needs to keep an eye on the control whether they have set everything correctly. This time the royal chef Gerasim had the impression that the pages have played a prank again: they had poured the juice from one cup to another. Now Gerasim wants to check his hypothesis. The good thing is that chef Gerasim always pour the same number of milliliters of juice to all cups in the royal kitchen. Having thoroughly measured the juice in each cup, Gerasim asked you to write a program that will determine from which cup juice was poured to which one; otherwise, the program should determine that this time the pages set the table diligently.

To simplify your task we shall consider the cups to be bottomless so that the juice never overfills a cup and pours out, however much it can be. Besides, by some strange reason in a far away kingdom one can only pour to a cup or from one cup to another an integer number of milliliters of juice.

## 样例 #1

### 输入

```
5
270
250
250
230
250
```

### 输出

```
20 ml. from cup #4 to cup #1.
```

## 样例 #2

### 输入

```
5
250
250
250
250
250
```

### 输出

```
Exemplary pages.
```

## 样例 #3

### 输入

```
5
270
250
249
230
250
```

### 输出

```
Unrecoverable configuration.
```

# AI分析结果



# Help Chef Gerasim

## 题目描述

在一个遥远的王国里，年轻的侍从帮助国王布置餐桌。由于他们非常淘气，需要时刻检查他们是否正确地布置了所有东西。这次，皇家厨师 Gerasim 感觉侍从们又恶作剧了：他们把果汁从一个杯子倒到了另一个杯子。现在 Gerasim 想验证他的假设。幸运的是，Gerasim 总是向所有杯子倒入相同毫升数的果汁。通过精确测量每个杯子的果汁量，Gerasim 请你编写一个程序判断是否发生了倒果汁的操作（若发生，需输出具体操作），或者是否需要输出其他情况。

## 样例

### 样例 #1
输入：
```
5
270
250
250
230
250
```
输出：
```
20 ml. from cup #4 to cup #1.
```

### 样例 #2
输入：
```
5
250
250
250
250
250
```
输出：
```
Exemplary pages.
```

### 样例 #3
输入：
```
5
270
250
249
230
250
```
输出：
```
Unrecoverable configuration.
```

## 算法分类
模拟

---

## 题解分析与结论

### 核心思路
1. **总和检查**：所有杯子的果汁总量必须能被杯子数量整除，否则无法平均分配。
2. **统计差异**：只有恰好两个杯子的值与平均数不同，且它们的差值绝对值相等（一个多 `k`，一个少 `k`）。
3. **操作方向**：输出从值较小的杯子（倒入后减少的杯子）到值较大的杯子（倒入后增加的杯子）。

### 解决难点
- **方向矛盾**：样例输出看似与直觉相反，但题目要求输出导致当前状态的倒操作方向（即从原来源杯子到目标杯子，而非调整后的方向）。
- **边界处理**：需处理所有杯子相同、总和不可整除、差异数量不合法等情况。

---

## 精选题解

### 题解作者：hereiszd（★★★★☆）
**关键亮点**：
- 直接通过遍历找出最大值和最小值，简化了差异统计。
- 利用结构体记录索引，避免重复遍历。
- 明确输出格式，正确处理差值计算和方向。

**代码核心**：
```cpp
int main() {
    // ... 输入处理 ...
    int pj = sum / n;
    for (int i = 0; i < n; i++) {
        if (f[i] != pj) flag++;
    }
    if (flag == 0) {
        cout << "Exemplary pages.\n";
    } else if (flag > 2) {
        cout << "Unrecoverable configuration.\n";
    } else {
        printf("%d ml. from cup #%d to cup #%d.\n", 
               (maxn.data - minn.data)/2, minn.num+1, maxn.num+1);
    }
}
```

---

### 题解作者：BushHuang（★★★★☆）
**关键亮点**：
- 使用双变量记录差异杯子的索引，减少遍历次数。
- 通过条件判断确保输出方向正确。

**代码核心**：
```cpp
int main() {
    // ... 输入处理 ...
    for (int i = 1; i <= n; i++) {
        if (a[i] != avg && y) {
            cout << "Unrecoverable configuration.\n";
            return 0;
        } else if (a[i] != avg) {
            y = x; x = i;
        }
    }
    if (a[x] < a[y]) swap(x, y);
    cout << abs(a[x]-a[y])/2 << " ml. from cup #" << y << " to cup #" << x << ".\n";
}
```

---

### 题解作者：_wjr_（★★★★☆）
**关键亮点**：
- 直接通过遍历确定差异杯子的位置，逻辑简洁。
- 显式处理倒量计算，避免方向混淆。

**代码核心**：
```cpp
int main() {
    // ... 输入处理 ...
    for (int i = 1; i <= n; i++) {
        if (a[i] > m) x1 = i;
        else if (a[i] < m) x2 = i;
    }
    cout << (a[x1] - a[x2])/2 << " ml. from cup #" << x2 << " to cup #" << x1 << ".";
}
```

---

## 关键技巧总结
- **总和检查优先**：避免无效计算。
- **差异统计与方向**：通过记录最大值和最小值的索引，直接确定倒操作方向。
- **输出格式**：严格按照题目要求处理杯子编号（从1开始）。

## 拓展与同类题目
- **类似问题**：涉及数组状态变化的模拟题，如 [CF714B](https://www.luogu.com.cn/problem/CF714B)。
- **推荐练习**：
  1. [P5716 找最小值](https://www.luogu.com.cn/problem/P5716)
  2. [P1152 欢乐的跳](https://www.luogu.com.cn/problem/P1152)
  3. [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)

---
处理用时：431.97秒