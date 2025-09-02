# 题目信息

# Dima and Staircase

## 题目描述

Dima's got a staircase that consists of $ n $ stairs. The first stair is at height $ a_{1} $ , the second one is at $ a_{2} $ , the last one is at $ a_{n} $ ( $ 1<=a_{1}<=a_{2}<=...<=a_{n} $ ).

Dima decided to play with the staircase, so he is throwing rectangular boxes at the staircase from above. The $ i $ -th box has width $ w_{i} $ and height $ h_{i} $ . Dima throws each box vertically down on the first $ w_{i} $ stairs of the staircase, that is, the box covers stairs with numbers $ 1,2,...,w_{i} $ . Each thrown box flies vertically down until at least one of the two following events happen:

- the bottom of the box touches the top of a stair;
- the bottom of the box touches the top of a box, thrown earlier.

We only consider touching of the horizontal sides of stairs and boxes, at that touching with the corners isn't taken into consideration. Specifically, that implies that a box with width $ w_{i} $ cannot touch the stair number $ w_{i}+1 $ .

You are given the description of the staircase and the sequence in which Dima threw the boxes at it. For each box, determine how high the bottom of the box after landing will be. Consider a box to fall after the previous one lands.

## 说明/提示

The first sample are shown on the picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF272C/141a6409b5823a4a8bdecfcecc6a55967701b504.png)

## 样例 #1

### 输入

```
5
1 2 3 6 6
4
1 1
3 1
1 1
4 3
```

### 输出

```
1
3
4
6
```

## 样例 #2

### 输入

```
3
1 2 3
2
1 1
3 1
```

### 输出

```
1
3
```

## 样例 #3

### 输入

```
1
1
5
1 2
1 10
1 10
1 10
1 10
```

### 输出

```
1
3
13
23
33
```

# AI分析结果



### 题目中文翻译
# Dima 和楼梯

## 题目描述

Dima 有一个由 $n$ 级台阶组成的楼梯。第一级台阶高度为 $a_1$，第二级为 $a_2$，最后一级为 $a_n$（满足 $1 \leq a_1 \leq a_2 \leq ... \leq a_n$）。

Dima 决定用矩形盒子从上方投向楼梯。第 $i$ 个盒子的宽度为 $w_i$，高度为 $h_i$。每个盒子会垂直下落到楼梯的前 $w_i$ 级台阶上（即覆盖台阶 1 到 $w_i$）。盒子下落时会触发以下任一条件后停止：
- 盒子底部接触台阶顶部；
- 盒子底部接触之前落下的盒子顶部。

求每个盒子停止后的底部高度（每个盒子落下后立即输出对应高度）。

---

**算法分类**：模拟

---

### 题解分析与结论

所有题解的核心思路均基于楼梯高度单调递增的特性。由于台阶高度非递减，每次处理箱子时只需考虑以下两种情况：
1. 当前箱子覆盖范围内的最高台阶（即 $a_{w_i}$，因为 $a$ 单调递增）；
2. 之前所有箱子累积的最高高度。

通过维护一个全局变量记录当前最高高度，每个箱子处理时间复杂度为 $O(1)$，整体复杂度 $O(m)$。

---

### 高分题解推荐

#### 1. 作者：_Haoomff_（5星）
**关键亮点**：
- 利用单调性直接取 $a[w]$ 作为基准高度。
- 代码简洁高效，维护全局最高点 `res`，清晰展示核心逻辑。

**核心代码**：
```cpp
ll n, a[100005], m, res = 0;
while (m--) {
    cin >> w >> h;
    res = max(res, a[w]);
    cout << res << "\n";
    res += h;
}
```

#### 2. 作者：Gao_l（4星）
**关键亮点**：
- 强调数据范围需用 `long long`，避免溢出。
- 代码结构清晰，变量命名直观。

**核心代码**：
```cpp
int ans = 0;
while (q--) {
    ans = max(ans, a[x]);
    cout << ans << "\n";
    ans += y;
}
```

#### 3. 作者：xujingyu（4星）
**个人心得**：
- 初始暴力解法 TLE 后，通过观察优化为 $O(1)$ 操作。
- 验证了利用单调性优化复杂度的可行性。

**核心代码**：
```cpp
big = max(big, a[w]);
cout << big << "\n";
big += h;
```

---

### 关键思路总结
- **利用单调性**：由于楼梯高度非递减，覆盖前 $w_i$ 级的最高台阶必为 $a[w_i]$。
- **维护全局最高点**：用变量记录历史累积高度，每次只需比较当前台阶高度与历史高度。
- **时间复杂度优化**：将暴力 $O(m \cdot w)$ 优化至 $O(m)$。

---

### 拓展与相似题目
1. **P2947 [USACO09MAR] Look Up S**（单调性应用）
2. **P1901 发射站**（维护局部极值）
3. **P1090 合并果子**（贪心+优先队列）

---

### 代码实现技巧
- **全局变量维护状态**：避免重复计算，直接更新当前最高点。
- **输入输出优化**：使用 `ios::sync_with_stdio(0)` 加速 IO。
- **数据类型选择**：必须使用 `long long` 防止溢出。

---
处理用时：69.53秒