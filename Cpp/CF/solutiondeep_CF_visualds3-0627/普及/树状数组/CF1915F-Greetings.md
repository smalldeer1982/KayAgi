# 题目信息

# Greetings

## 题目描述

There are $ n $ people on the number line; the $ i $ -th person is at point $ a_i $ and wants to go to point $ b_i $ . For each person, $ a_i < b_i $ , and the starting and ending points of all people are distinct. (That is, all of the $ 2n $ numbers $ a_1, a_2, \dots, a_n, b_1, b_2, \dots, b_n $ are distinct.)

All the people will start moving simultaneously at a speed of $ 1 $ unit per second until they reach their final point $ b_i $ . When two people meet at the same point, they will greet each other once. How many greetings will there be?

Note that a person can still greet other people even if they have reached their final point.

## 说明/提示

In the first test case, the two people will meet at point $ 3 $ and greet each other.

## 样例 #1

### 输入

```
5
2
2 3
1 4
6
2 6
3 9
4 5
1 8
7 10
-2 100
4
-10 10
-5 5
-12 12
-13 13
5
-4 9
-2 5
3 4
6 7
8 10
4
1 2
3 4
5 6
7 8```

### 输出

```
1
9
6
4
0```

# AI分析结果



## 唯一算法分类
逆序对 / 二维偏序

---

## 综合分析与结论

### 核心思路
当两人 $i,j$ 满足 $a_i < a_j$ 且 $b_i > b_j$ 时，$i$ 的路径完全覆盖 $j$ 的路径，此时 $j$ 到达终点后，$i$ 会在 $b_j$ 处与之相遇。将所有区间按起点排序后，问题等价于求终点数组的逆序对数目。

### 算法流程
1. **排序**：将所有人按起点 $a_i$ 升序排列。
2. **逆序对统计**：对排序后的终点数组 $b_i$，计算其逆序对数目。
   - **归并排序法**：在归并过程中统计逆序对。
   - **树状数组法**：离散化后，动态维护已处理元素的分布，通过查询快速统计。

### 可视化设计
- **动画演示**：在 Canvas 中绘制数轴，用不同颜色线段表示每个人的移动路径。当两人路径满足包含关系时，高亮相遇点。
- **归并排序步骤**：分步展示数组分割、合并过程，用颜色标记比较元素和逆序对统计。
- **树状数组操作**：可视化离散化后的值域，动态显示插入和查询操作，突出统计逻辑。
- **8-bit 风格**：用像素块表示元素，合并时播放经典音效，背景音乐采用复古芯片音乐。

---

## 题解清单 (≥4星)

### foryou_（⭐⭐⭐⭐⭐）
- **亮点**：思路简洁，直接指出逆序对本质，归并排序实现代码短小精悍。
- **代码**：无需离散化，适合原生逆序对场景。

### ThySecret（⭐⭐⭐⭐）
- **亮点**：详细推导思路，树状数组结合离散化，适合处理大范围数据。
- **调试提示**：强调所有 $2n$ 点需离散化，避免值域错误。

### wxzzzz（⭐⭐⭐⭐）
- **亮点**：明确转化为二维偏序问题，树状数组维护动态前缀和。
- **优化点**：离散化后逆序查询，代码结构清晰。

---

## 核心代码实现

### 归并排序法（foryou_）
```cpp
void mergesort(int bg, int ed) {
    if (bg == ed) return;
    int mid = (bg + ed) / 2, i = bg, j = mid + 1, k = bg;
    mergesort(bg, mid), mergesort(mid + 1, ed);
    while (i <= mid && j <= ed) {
        if (a[i] <= a[j]) c[k++] = a[i++];
        else c[k++] = a[j++], ans += mid - i + 1; // 统计逆序
    }
    while (i <= mid) c[k++] = a[i++];
    while (j <= ed) c[k++] = a[j++];
    for (int l = bg; l <= ed; l++) a[l] = c[l];
}
```

### 树状数组法（ThySecret）
```cpp
sort(tmp + 1, tmp + 1 + n); // 按起点排序
for (int i = 1; i <= n; i++) a[i] = tmp[i].r; // 提取终点
// 离散化终点数组
mergesort(1, n); // 归并统计逆序对
```

---

## 相似题目推荐
1. **P1908 逆序对** - 模板题，练习基础逆序对统计。
2. **P1966 火柴排队** - 通过逆序对优化匹配问题。
3. **P3374 树状数组** - 掌握动态维护前缀和的技巧。

---

## 个人心得摘录
- **离散化空间**：树状数组需开两倍空间，否则会越界（DrAlfred 的教训）。
- **排序方向**：按起点升序后，终点逆序对直接对应答案，无需额外处理（wxzzzz 的关键推导）。

---

## 可视化方案
- **像素动画**：用 16 色块表示不同区间的终点，归并时分裂合并展示。
- **音效设计**：每次逆序对统计时播放 8-bit 点击声，完成时播放胜利音效。
- **交互控制**：允许暂停观察当前合并状态，调整动画速度理解分治细节。

---
处理用时：145.58秒