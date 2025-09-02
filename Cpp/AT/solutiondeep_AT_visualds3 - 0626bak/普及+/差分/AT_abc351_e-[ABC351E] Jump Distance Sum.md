# 题目信息

# [ABC351E] Jump Distance Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc351/tasks/abc351_e

座標平面上に $ N $ 個の点 $ P_1,P_2,\ldots,P_N $ があり、点 $ P_i $ の座標は $ (X_i,Y_i) $ です。  
$ 2 $ つの点 $ A,B $ の距離 $ \text{dist}(A,B) $ を次のように定義します。

> 最初、ウサギが点 $ A $ にいる。  
> $ (x,y) $ にいるウサギは $ (x+1,y+1) $, $ (x+1,y-1) $, $ (x-1,y+1) $, $ (x-1,y-1) $ のいずれかに $ 1 $ 回のジャンプで移動することができる。  
> 点 $ A $ から点 $ B $ まで移動するために必要なジャンプの回数の最小値を $ \text{dist}(A,B) $ として定義する。  
> ただし、何度ジャンプを繰り返しても点 $ A $ から点 $ B $ まで移動できないとき、$ \text{dist}(A,B)=0 $ とする。

$ \displaystyle\sum_{i=1}^{N-1}\displaystyle\sum_{j=i+1}^N\ \text{dist}(P_i,P_j) $ を求めてください。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 0\leq\ X_i,Y_i\leq\ 10^8 $
- $ i\neq\ j $ ならば $ (X_i,Y_i)\neq\ (X_j,Y_j) $
- 入力はすべて整数

### Sample Explanation 1

$ P_1,P_2,P_3 $ の座標はそれぞれ $ (0,0) $, $ (1,3) $, $ (5,6) $ です。 $ P_1 $ から $ P_2 $ へはウサギは $ (0,0)\to\ (1,1)\to\ (0,2)\to\ (1,3) $ と $ 3 $ 回で移動でき、$ 2 $ 回以下では $ P_1 $ から $ P_2 $ まで移動できないため、 $ \text{dist}(P_1,P_2)=3 $ です。 $ P_1 $ から $ P_3 $ および $ P_2 $ から $ P_3 $ へはウサギは移動できないため、$ \text{dist}(P_1,P_3)=\text{dist}(P_2,P_3)＝0 $ となります。 よって、答えは $ \displaystyle\sum_{i=1}^{2}\displaystyle\sum_{j=i+1}^3\text{dist}(P_i,P_j)=\text{dist}(P_1,P_2)+\text{dist}(P_1,P_3)+\text{dist}(P_2,P_3)=3+0+0=3 $ となります。

## 样例 #1

### 输入

```
3
0 0
1 3
5 6```

### 输出

```
3```

## 样例 #2

### 输入

```
5
0 5
1 7
2 9
3 8
4 6```

### 输出

```
11```

# AI分析结果



## 算法分类
数学优化、坐标转换

---

## 题解思路与核心难点

### 核心思路
- **可达性判断**：两点的曼哈顿距离奇偶性决定是否可达。当且仅当 $(x_i + y_i) \equiv (x_j + y_j) \pmod{2}$ 时，两点间存在路径。
- **坐标转换**：将原坐标 $(x, y)$ 转换为新坐标系 $(u, v) = (\frac{x-y}{2}, \frac{x+y}{2})$，使得原题的跳跃距离等价于新坐标的曼哈顿距离。
- **分组处理**：按奇偶性分组后，分别计算每组内的曼哈顿距离总和。

### 解决难点
1. **奇偶分组**：将点按 $(x+y)$ 奇偶性分为两组，确保组内点对可达。
2. **高效计算曼哈顿距离总和**：通过排序和前缀和技巧，将时间复杂度优化至 $O(n \log n)$。

### 算法流程
1. **输入处理**：读取所有点并按奇偶性分组。
2. **坐标转换**：对新坐标系中的 $u$ 和 $v$ 分别排序。
3. **前缀和计算**：对排序后的坐标分别计算每个维度上的贡献，累加得到总距离。

---

## 题解评分 (≥4星)

### 1. 作者：weitianyi (⭐⭐⭐⭐⭐)
- **亮点**：思路清晰，代码简洁高效，坐标转换和奇偶分组处理明确。
- **代码**：通过排序和前缀和快速计算曼哈顿距离总和。

### 2. 作者：zrl123456 (⭐⭐⭐⭐)
- **亮点**：类似核心思路，转换公式略有不同，代码同样高效。
- **优化**：直接使用 STL 排序和前缀和，可读性高。

### 3. 作者：james1BadCreeper (⭐⭐⭐⭐)
- **亮点**：无脑转换切比雪夫距离，代码简短，正确性验证充分。

---

## 最优思路提炼
1. **坐标旋转法**：将原问题转换为曼哈顿距离计算，避免直接处理对角线移动。
2. **奇偶分组**：通过调整奇数组坐标统一处理，简化计算。
3. **前缀和优化**：排序后线性时间计算贡献，避免暴力枚举。

---

## 相似题目推荐
1. **P3964 [TJOI2013] 松鼠聚会**（切比雪夫距离转曼哈顿）
2. **AT_abc351_e**（同题）
3. **P5098 [USACO04OPEN] Cave Cows 3**（曼哈顿距离最大点对）

---

## 代码片段（核心逻辑）

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int solve(vector<pair<int, int>> points) {
    // 坐标转换
    for (auto &p : points) {
        int x = p.first, y = p.second;
        p = {(x - y) / 2, (x + y) / 2};
    }
    
    // 计算x轴贡献
    sort(points.begin(), points.end(), [](auto a, auto b) {
        return a.first < b.first;
    });
    int sum_x = 0, ans_x = 0, cnt = 0;
    for (auto p : points) {
        ans_x += p.first * cnt - sum_x;
        sum_x += p.first;
        cnt++;
    }
    
    // 计算y轴贡献
    sort(points.begin(), points.end(), [](auto a, auto b) {
        return a.second < b.second;
    });
    int sum_y = 0, ans_y = 0;
    cnt = 0;
    for (auto p : points) {
        ans_y += p.second * cnt - sum_y;
        sum_y += p.second;
        cnt++;
    }
    
    return ans_x + ans_y;
}

signed main() {
    int n; cin >> n;
    vector<pair<int, int>> even, odd;
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        if ((x + y) % 2) odd.emplace_back(x, y + 1);
        else even.emplace_back(x, y);
    }
    cout << solve(even) + solve(odd);
}
```

---

## 可视化设计

### 动画方案
1. **坐标转换演示**：展示原点到新坐标系的映射，用箭头表示旋转45度后的网格。
2. **排序过程**：动态显示点在新坐标系中按x和y排序的过程。
3. **贡献计算**：高亮当前处理点，显示其与前面点的距离累加过程。

### 复古像素风格
- **颜色方案**：原坐标用绿色，转换后坐标用蓝色，贡献计算时用红色高亮。
- **音效**：排序完成时播放升级音效，计算贡献时播放点击声。

### 交互功能
- **步进控制**：允许单步执行排序和前缀和计算。
- **自动模式**：以2倍速自动演示坐标转换和贡献累加。

---
处理用时：97.89秒