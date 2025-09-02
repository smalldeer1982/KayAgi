# 题目信息

# Polycarp's New Job

## 题目描述

题意简述

维护一个初始为空的点集，支持两种操作：

$+\ x\ y$：向点集中加入$(x,y)$

$?\ h\ w$：查询是否对于点集中的所有点都满足$x  \leq h \&\& y \leq w$或者$x \leq w \&\& y \leq h$

## 样例 #1

### 输入

```
9
+ 3 2
+ 2 3
? 1 20
? 3 3
? 2 3
+ 1 5
? 10 10
? 1 5
+ 1 1
```

### 输出

```
NO
YES
YES
YES
NO
```

# AI分析结果



# 题目中文翻译

## 题目名称：Polycarp的新工作

### 题目描述

维护一个初始为空的点集，支持两种操作：

1. `+ x y`：向点集中加入点 $(x, y)$。
2. `? h w`：查询是否对于点集中的所有点都满足 $(x \leq h \text{ 且 } y \leq w)$ 或者 $(x \leq w \text{ 且 } y \leq h)$。

## 样例 #1

### 输入

```
9
+ 3 2
+ 2 3
? 1 20
? 3 3
? 2 3
+ 1 5
? 10 10
? 1 5
+ 1 1
```

### 输出

```
NO
YES
YES
YES
NO
```

---

**算法分类**：贪心

---

## 题解分析与结论

### 核心思路
所有点及查询的坐标对 $(x, y)$ 统一调整为 $(min(x,y), max(x,y))$，维护两个全局最大值：所有点的较小值的最大值 `max_x` 和较大值的最大值 `max_y`。查询时只需比较调整后的 $(h, w)$ 是否满足 `max_x ≤ h` 且 `max_y ≤ w`。

### 高分题解推荐

#### 作者：xuchuhan（★★★★★）
**关键亮点**：
- 统一预处理坐标顺序，简化判断逻辑。
- 代码简洁高效，时间复杂度 $O(1)$ 每次操作。

**核心代码**：
```cpp
if (op == '+') {
    maxx = max(maxx, x);
    maxy = max(maxy, y);
} else {
    if (maxx <= x && maxy <= y) cout << "YES\n";
    else cout << "NO\n";
}
```

#### 作者：activeO（★★★★★）
**关键亮点**：
- 输入时即时交换坐标，逻辑清晰。
- 直接维护关键最大值，无需额外存储。

**核心代码**：
```cpp
if (op == '+') {
    maxx = max(maxx, x);
    maxy = max(maxy, y);
} else {
    puts((maxx <= x && maxy <= y) ? "YES" : "NO");
}
```

#### 作者：decoqwq（★★★★★）
**关键亮点**：
- 显式处理输入顺序，确保逻辑正确性。
- 代码结构对称，易读性强。

**核心代码**：
```cpp
if (opt[0] == '+') {
    if (x > y) swap(x, y);
    maxx = max(maxx, x);
    maxy = max(maxy, y);
} else {
    if (x >= maxx && y >= maxy) printf("YES\n");
    else printf("NO\n");
}
```

---

## 关键思路总结
- **坐标归一化**：始终将坐标对调整为较小值在前、较大值在后的形式。
- **极值维护**：通过维护全局最大值避免遍历所有点，极大优化时间复杂度。
- **边界一致性**：查询时用相同的规则处理输入，确保逻辑正确。

---

## 拓展与相似题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)  
   （动态维护数据特性，利用树状数组/归并排序）
2. [CF1101E Polycarp's New Job](https://www.luogu.com.cn/problem/CF1101E)  
   （本题，巩固极值维护技巧）
3. [P3374 树状数组模板](https://www.luogu.com.cn/problem/P3374)  
   （动态维护前缀和，类似极值维护思想）

---
处理用时：179.18秒