# 题目信息

# Exposition

## 题目描述

There are several days left before the fiftieth birthday of a famous Berland's writer Berlbury. In this connection the local library decided to make an exposition of the works of this famous science-fiction writer. It was decided as well that it is necessary to include into the exposition only those books that were published during a particular time period. It is obvious that if the books differ much in size, the visitors will not like it. That was why the organizers came to the opinion, that the difference between the highest and the lowest books in the exposition should be not more than $ k $ millimeters.

The library has $ n $ volumes of books by Berlbury, arranged in chronological order of their appearance. The height of each book in millimeters is know, it is $ h_{i} $ . As Berlbury is highly respected in the city, the organizers want to include into the exposition as many books as possible, and to find out what periods of his creative work they will manage to cover. You are asked to help the organizers cope with this hard task.

## 样例 #1

### 输入

```
3 3
14 12 10
```

### 输出

```
2 2
1 2
2 3
```

## 样例 #2

### 输入

```
2 0
10 10
```

### 输出

```
2 1
1 2
```

## 样例 #3

### 输入

```
4 5
8 19 10 13
```

### 输出

```
2 1
3 4
```

# AI分析结果



## 算法分类
双指针/滑动窗口（结合单调队列）

---

## 综合分析与结论

### 核心思路与难点
1. **核心算法流程**：使用双指针维护滑动窗口，通过两个单调队列分别维护窗口内的最大值和最小值候选。右指针扩展时维护队列单调性，左指针收缩时弹出过期的队列元素。
2. **关键数据结构**：
   - `que_max`：单减队列，队首为当前窗口最大值
   - `que_min`：单增队列，队首为当前窗口最小值
3. **复杂度优化**：通过单调队列将时间复杂度优化至 O(n)，是本题最优解法
4. **难点突破**：在滑动过程中动态维护极差，需正确处理队列中元素的过期问题

---

## 题解评分（≥4星）

1. **zrzring（5星）**
   - 使用双指针+单调队列，时间复杂度最优
   - 代码结构清晰，包含完整答案收集逻辑
   - 关键代码段：
     ```cpp
     while (h1 <= t1 && a[x] >= a[q1[t1]]) t1--;
     q1[++t1] = x; // 维护最大值队列
     while (h2 <= t2 && a[x] <= a[q2[t2]]) t2--;
     q2[++t2] = x; // 维护最小值队列
     ```

2. **kczno1（4星）**
   - 同样使用单调队列但代码可读性稍弱
   - 包含对错误思路的反思（子序列vs子串）
   - 个人心得："如果是子串的话...时间O(n)" 体现了算法选择的关键

3. **小闸蟹（4星）**
   - 使用multiset维护极差，代码最简洁
   - 时间复杂度O(n log n)稍逊但更易实现
   - 关键逻辑：
     ```cpp
     while (*s.rbegin() - *s.begin() > k) {
         s.erase(s.find(a[l++]));
     }
     ```

---

## 最优思路实现（zrzring题解核心代码）

```cpp
int q1[N], q2[N]; // 最大值队列、最小值队列
int h1 = 0, t1 = -1, h2 = 0, t2 = -1;

void ins(int x) {
    // 维护最大值队列（单减）
    while (h1 <= t1 && a[x] >= a[q1[t1]]) t1--;
    q1[++t1] = x;
    // 维护最小值队列（单增）
    while (h2 <= t2 && a[x] <= a[q2[t2]]) t2--;
    q2[++t2] = x;
}

int main() {
    int l = 1, max_len = 0;
    for (int r = 1; r <= n; ++r) {
        ins(r); // 右指针右移
        // 收缩左指针直到窗口合法
        while (a[q1[h1]] - a[q2[h2]] > k) {
            if (q1[h1] == l) h1++;
            if (q2[h2] == l) h2++;
            l++;
        }
        // 更新答案
        max_len = max(max_len, r - l + 1);
    }
}
```

---

## 可视化设计

### 动画方案（8位像素风格）
1. **界面元素**：
   - 顶部：数组元素用16x16像素块表示，当前窗口高亮为绿色边框
   - 中部：两个单调队列用不同颜色（红-最大值队列，蓝-最小值队列）的滑动方块表示
   - 底部：控制面板（暂停/继续/步进）和统计信息

2. **关键动画**：
   - 右指针右移时：
     - 新元素闪烁黄色
     - 最大值队列弹出较小元素（红色方块爆炸特效）
     - 插入新元素到队列尾部
   - 窗口不合法时：
     - 左指针右移，原左端元素变灰
     - 队列头部元素爆炸（若过期）

3. **音效设计**：
   - 元素入队：8-bit "哔"声（不同音高对应最大/最小队列）
   - 窗口更新：成功音效（上升音阶）
   - 队列弹出："噗"声（低频噪声）

4. **自动演示模式**：
   ```javascript
   function autoPlay() {
       if (r < n) {
           moveRight();
           setTimeout(autoPlay, 500);
       } else {
           playSuccessMusic();
       }
   }
   ```

---

## 同类型题目
1. **P1886 滑动窗口**（单调队列模板题）
2. **P1714 切蛋糕**（前缀和+单调队列）
3. **P1440 求m区间内的最小值**（单调队列变形）

---

## 个人心得摘录
> "如果是子串的话，就是枚举左端点l，维护r=max(i)...时间O(n)" —— kczno1  
> 体现了算法选择时对问题性质（连续子串）的关键理解

> "这样做稍微有一点点尺取法的味道" —— 小闸蟹  
> 道出了滑动窗口与双指针算法的内在联系

---

## 举一反三
当遇到「连续子区间极值」问题时，可优先考虑：
1. 滑动窗口+单调队列维护极值
2. 预处理ST表后二分查找
3. 平衡树维护动态集合（适用于非连续子序列）

根据数据规模（n=1e5优先选O(n)算法）和实现复杂度灵活选择。

---
处理用时：78.09秒