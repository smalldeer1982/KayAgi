# 题目信息

# Segments

## 题目描述

You are given $ n $ segments on the Ox-axis. You can drive a nail in any integer point on the Ox-axis line nail so, that all segments containing this point, are considered nailed down. If the nail passes through endpoint of some segment, this segment is considered to be nailed too. What is the smallest number of nails needed to nail all the segments down?

## 样例 #1

### 输入

```
2
0 2
2 5
```

### 输出

```
1
2 ```

## 样例 #2

### 输入

```
5
0 3
4 2
4 8
8 10
7 7
```

### 输出

```
3
7 10 3
```

# AI分析结果



### 题目中文重写

#### 题目描述

在 Ox 轴上给定 $n$ 条线段。你可以在轴的任意整数点钉钉子，使得所有包含该点的线段被视为被固定。若钉子恰好位于某线段的端点，该线段也被视为固定。求固定所有线段所需的最小钉子数量。

#### 输入格式

输入第一行为线段数 $n$。接下来 $n$ 行每行两个整数，表示线段的起点和终点。

#### 输出格式

第一行输出最小钉子数 $k$，第二行按任意顺序输出 $k$ 个钉子的位置。

#### 样例 #1

**输入**
```
2
0 2
2 5
```

**输出**
```
1
2
```

#### 样例 #2

**输入**
```
5
0 3
4 2
4 8
8 10
7 7
```

**输出**
```
3
7 10 3
```

---

### 算法分类
**贪心**

---

### 题解对比与结论

#### 题解核心思路总结
所有题解均采用贪心策略，但实现方式略有差异：
1. **按右端点排序**：将线段按右端点从小到大排序，每次选择当前未被覆盖线段的右端点作为钉子，跳过所有被此钉子覆盖的线段。
2. **动态维护钉子位置**：按左端点排序时，维护当前钉子位置，若后续线段右端点更小则更新钉子位置以覆盖更多线段。

#### 最优关键思路
**按右端点排序 + 贪心选点**：将线段按右端点排序后，每次选择当前未被覆盖线段的右端点钉钉子。此方法能保证每个钉子覆盖尽可能多的后续线段，是最优贪心策略。

---

### 高星题解推荐

#### 1. Mistybranch（5星）
**亮点**  
- 思路清晰，代码简洁高效。
- 直接按右端点排序，通过遍历一次线段即可确定所有钉子位置。
- 处理线段端点交换的细节完善。

**核心代码**
```cpp
sort(segList + 1, segList + n + 1, [](seg a, seg b) {
    return a.r < b.r;
});
vector<int> res;
for (int i = 1; i <= n; i++) {
    if (res.empty() || segList[i].l > res.back()) {
        res.push_back(segList[i].r);
    }
}
```

#### 2. xiaoPanda（4星）
**亮点**  
- 通过双重循环跳过已覆盖线段，逻辑直观。
- 代码中处理了端点顺序交换的情况。

**注意点**  
循环中需谨慎处理索引越界问题。

**核心代码**
```cpp
sort(id+1, id+n+1, [](auto& a, auto& b) { return a.y < b.y; });
for (int i=1; i<=n; ) {
    int k = id[i].y;
    ans++;
    i++;
    while (i <=n && id[i].x <=k) i++;
}
```

#### 3. Allanljx（4星）
**亮点**  
- 按左端点排序但动态调整钉子位置。
- 通过维护 `rr` 变量优化覆盖范围。

**核心代码**
```cpp
sort(a+1, a+n+1, [](node a, node b) { return a.l < b.l; });
int rr = a[1].r;
for (int i=2; i<=n; i++) {
    if (a[i].l > rr) {
        ans++;
        rr = a[i].r;
    } else if (a[i].r < rr) {
        rr = a[i].r;
    }
}
```

---

### 推荐相似题目
1. [P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803)  
   **标签**：贪心、区间排序  
2. [CF1584B Chess Club](https://codeforces.com/problemset/problem/1584/B)  
   **标签**：贪心、区间覆盖  
3. [P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230)  
   **标签**：贪心、截止时间排序  

---

### 个人心得摘录
- **端点顺序处理**：输入线段端点可能未按大小排序，需先交换处理。（Mistybranch）
- **贪心策略证明**：选择右端点能覆盖更多后续线段，确保全局最优。（xiaoPanda）
- **动态调整技巧**：按左端点排序时，通过调整钉子位置减少后续需要的钉子数。（Allanljx）

---
处理用时：181.65秒