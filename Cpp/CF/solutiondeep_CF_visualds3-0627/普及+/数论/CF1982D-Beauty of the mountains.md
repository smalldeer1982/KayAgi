# 题目信息

# Beauty of the mountains

## 题目描述

Nikita loves mountains and has finally decided to visit the Berlyand mountain range! The range was so beautiful that Nikita decided to capture it on a map. The map is a table of $ n $ rows and $ m $ columns, with each cell containing a non-negative integer representing the height of the mountain.

He also noticed that mountains come in two types:

- With snowy caps.
- Without snowy caps.

Nikita is a very pragmatic person. He wants the sum of the heights of the mountains with snowy caps to be equal to the sum of the heights of the mountains without them. He has arranged with the mayor of Berlyand, Polikarp Polikarpovich, to allow him to transform the landscape.

Nikita can perform transformations on submatrices of size $ k \times k $ as follows: he can add an integer constant $ c $ to the heights of the mountains within this area, but the type of the mountain remains unchanged. Nikita can choose the constant $ c $ independently for each transformation. Note that $ c $ can be negative.

Before making the transformations, Nikita asks you to find out if it is possible to achieve equality of the sums, or if it is impossible. It doesn't matter at what cost, even if the mountains turn into canyons and have negative heights.

If only one type of mountain is represented on the map, then the sum of the heights of the other type of mountain is considered to be zero.

## 说明/提示

The mountain array from the first test case looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/c2cad4d039daa4458ac8328be539df0f39115b35.png)Initially, the sum of the heights of the mountains with snowy caps is $ 11 + 3 + 4 + 3 + 0 + 1 + 15 = 37 $ , and without them is $ 7 + 2 = 9 $ .

To equalize these sums, we can perform two transformations:

First transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/26401332927c782774104130bd94cec3d8dea8ef.png)Note that the constant $ c $ can be negative.

After the first transformation, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/8985a2e394a22468e2807bb57386a8c62bc3f888.png)Second transformation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/83de4303ed287bb4d20cf33c8ab2494ed765c011.png)As a result, the mountain array looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1982D/1dfddde2b777b3b24d753c3d41d8fe42319ee24e.png)The sum of the heights of the mountains with snowy caps is $ 17 + 9 + 9 - 16 - 20 - 19 + 15 = -5 $ , and without them is $ 7 - 12 = -5 $ , thus the answer is YES.

## 样例 #1

### 输入

```
8
3 3 2
7 11 3
4 2 3
0 1 15
100
010
000
4 4 3
123 413 24 233
123 42 0 216
22 1 1 53
427 763 22 6
0101
1111
1010
0101
3 3 2
2 1 1
1 1 2
1 5 4
010
101
010
3 3 2
2 1 1
1 1 2
1 5 3
010
101
010
3 4 3
46 49 50 1
19 30 23 12
30 25 1 46
1000
0100
0010
5 4 4
39 30 0 17
22 42 30 13
10 44 46 35
12 19 9 39
21 0 45 40
1000
1111
0011
0111
1100
2 2 2
3 4
6 7
00
00
2 2 2
0 0
2 0
01
00```

### 输出

```
YES
NO
YES
NO
YES
NO
YES
YES```

# AI分析结果



## 唯一算法分类  
**数学（裴蜀定理） + 二维前缀和**

---

## 题解思路、算法要点与解决难点  
### **核心思路**  
1. **初始差值计算**：统计有雪盖（1类）和无雪盖（0类）山的总高度差 `delta = sum(1类) - sum(0类)`，最终需使 `delta = 0`。  
2. **操作影响分析**：对每个 `k×k` 子矩阵操作，其贡献系数为 `2s - k²`（`s` 为子矩阵中 1 类数量）。  
3. **裴蜀定理应用**：将所有子矩阵的贡献系数求最大公约数 `g`，若 `g` 能整除 `delta`，则有解。  

### **算法实现**  
- **二维前缀和**：快速计算每个子矩阵的 1 类数量 `s`。  
- **贡献系数计算**：每个子矩阵的系数为 `2s - k²`。  
- **GCD 计算**：所有系数的最大公约数决定方程是否有解。  

### **解决难点**  
- **贡献系数转换**：将动态操作转化为线性组合问题，需理解操作对总差的数学影响。  
- **边界处理**：枚举子矩阵时需注意矩阵范围 `i + k - 1 <= n` 和 `j + k - 1 <= m`。  

---

## 题解评分 (≥4星)  
1. **SnapYust (4.5星)**  
   - 思路清晰，完整推导裴蜀定理的应用。  
   - 代码逻辑简洁，合理利用二维前缀和。  
   - 个人心得：通过方程形式直接说明核心变量关系。  

2. **xhhhh36 (4星)**  
   - 代码简洁，直接计算绝对值差。  
   - 优化了贡献系数的计算方式，减少变量冗余。  

3. **Targanzqq (4星)**  
   - 详细注释前缀和矩阵计算过程，便于理解。  
   - 明确分离 0/1 类统计，增强代码可读性。  

---

## 最优思路或技巧提炼  
1. **数学建模**：将动态操作转化为静态线性方程，通过系数差分析问题。  
2. **前缀和优化**：用 `O(1)` 时间计算子矩阵的 1 类数量，避免暴力枚举。  
3. **裴蜀定理降维**：将多元方程有解问题简化为 GCD 判断，复杂度从指数级降至线性。  

---

## 同类型题或类似算法套路  
- **裴蜀定理应用**：如洛谷 P4549（求解多元线性方程的最小非负解）。  
- **子矩阵统计**：如二维前缀和计算、滑动窗口优化。  

---

## 推荐相似题目  
1. **P4549** - 裴蜀定理的经典应用。  
2. **P1719** - 二维前缀和求最大子矩阵和。  
3. **CF702C** - 数学建模与边界条件处理。  

---

## 可视化与算法演示  
### **动画方案**  
1. **矩阵高亮**：用不同颜色标记当前枚举的 `k×k` 子矩阵，显示其 1 类数量 `s`。  
2. **贡献系数显示**：在子矩阵旁动态显示 `2s - k²` 的计算过程。  
3. **GCD 更新轨迹**：右侧面板实时显示当前所有系数的最大公约数。  

### **复古游戏化设计**  
- **像素风格**：用 8-bit 像素块表示矩阵，子矩阵操作时播放经典音效（如《超级玛丽》金币声）。  
- **自动演示模式**：按步展示前缀和构建、子矩阵枚举、GCD 计算流程。  
- **音效触发**：  
  - 成功/失败时播放 8-bit 胜利/失败音效。  
  - 每步操作触发“滴答”声，增强交互感。  

---

## 核心代码实现  
```cpp
// 二维前缀和预处理
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        sum[i][j] = c[i][j-1]-'0' + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
    }
}

// 枚举所有 k×k 子矩阵并计算贡献系数
int g = 0;
for (int i = 1; i + k - 1 <= n; i++) {
    for (int j = 1; j + k - 1 <= m; j++) {
        int s = sum[i+k-1][j+k-1] - sum[i-1][j+k-1] - sum[i+k-1][j-1] + sum[i-1][j-1];
        int coeff = 2 * s - k * k;
        g = gcd(g, abs(coeff));
    }
}

// 判断解的存在性
if (delta == 0 || (g != 0 && delta % g == 0)) {
    cout << "YES";
} else {
    cout << "NO";
}
```

---

## 个人心得摘录  
> “操作贡献的线性组合特性是关键，裴蜀定理将看似复杂的动态问题转化为静态数学判断。” —— SnapYust  
> “二维前缀和是子矩阵统计的利器，边界处理需特别细心。” —— Targanzqq

---
处理用时：97.45秒