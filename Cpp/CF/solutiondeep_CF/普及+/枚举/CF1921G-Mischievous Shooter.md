# 题目信息

# Mischievous Shooter

## 题目描述

Once the mischievous and wayward shooter named Shel found himself on a rectangular field of size $ n \times m $ , divided into unit squares. Each cell either contains a target or not.

Shel only had a lucky shotgun with him, with which he can shoot in one of the four directions: right-down, left-down, left-up, or right-up. When fired, the shotgun hits all targets in the chosen direction, the Manhattan distance to which does not exceed a fixed constant $ k $ . The Manhattan distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is equal to $ |x_1 - x_2| + |y_1 - y_2| $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/07ae9ceed185244b94a445086f5cae84fbf84168.png) Possible hit areas for $ k = 3 $ .Shel's goal is to hit as many targets as possible. Please help him find this value.

## 说明/提示

Possible optimal shots for the examples in the statement:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/027b9a5a762b96357d7642f8eac1d4cf8d7ae93a.png)

## 样例 #1

### 输入

```
4
3 3 1
.#.
###
.#.
2 5 3
###..
...##
4 4 2
..##
###.
#..#
####
2 1 3
#
#```

### 输出

```
3
4
5
2```

# AI分析结果

### 题目重写
# 调皮的射手

## 题目描述
曾经，有个调皮任性的射手谢尔，发现自己身处一个大小为 \(n \times m\) 的矩形场地，该场地被划分为多个单位正方形。每个单元格要么有目标，要么没有。

谢尔只带了一把幸运猎枪，他可以朝四个方向之一射击：右下、左下、左上或右上。开枪时，猎枪会击中所选方向上所有与射击点曼哈顿距离不超过固定常数 \(k\) 的目标。两点 \((x_1, y_1)\) 和 \((x_2, y_2)\) 之间的曼哈顿距离等于 \(|x_1 - x_2| + |y_1 - y_2|\) 。

![可能的命中区域，k = 3](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/07ae9ceed185244b94a445086f5cae84fbf84168.png)

谢尔的目标是击中尽可能多的目标。请帮他找出这个最大值。

## 说明/提示
题目中示例的可能最优射击方案：

![示例的可能最优射击方案](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/027b9a5a762b96357d7642f8eac1d4cf8d7ae93a.png)

## 样例 #1
### 输入
```
4
3 3 1
.#.
###
.#.
2 5 3
###..
...##
4 4 2
..##
###.
#..#
####
2 1 3
#
#
```
### 输出
```
3
4
5
2
```

### 综合分析与结论
这些题解主要围绕如何高效计算在四个方向射击时能击中的最多目标数展开，思路可分为基于差分和基于前缀和两类：
 - **差分思路**：通过枚举四个方向，对每个 `#` 考虑其在特定方向上满足曼哈顿距离限制的位置，利用差分维护该位置区间的贡献变化，如对每行进行差分操作，时间复杂度为 \(\mathcal O(nm)\)。
 - **前缀和思路**：利用类似二维前缀和的方法，将问题转化为求三角形、梯形、长方形等图形的前缀和。通过旋转矩阵，只处理一个方向（如右上），再对答案取 \(\max\)。在实现中，有的题解通过递推公式计算三角形前缀和，有的题解通过分治处理楼梯形状的区域。

解决难点主要在于如何准确处理不同方向上的攻击范围以及如何高效地计算这些范围内的目标数量。部分题解在边界条件处理、数组大小设置和旋转矩阵操作上需特别注意，否则易导致错误或复杂度退化。

### 所选的题解
1. **作者：sunkuangzheng (赞：8)  星级：5星**
    - **关键亮点**：思路清晰简洁，利用差分巧妙解决问题，时间复杂度达到最优的 \(\mathcal O(nm)\)，并详细指出了实现过程中的易错点，如数组大小设置、旋转矩阵后 \(n,m\) 的交换及 resize 操作等。
    - **个人心得**：提到赛时因数组设置、旋转矩阵相关操作的细节问题吃了九发罚时，强调了这些细节的重要性。
    - **核心代码片段**：（无具体代码粘贴需求，思路关键在于差分操作描述）
2. **作者：_yi_ (赞：1)  星级：4星**
    - **关键亮点**：通过旋转矩阵只考虑一个方向（左上），通过维护二维数组 \(f(i, j)\) 表示从点 \((i, j)\) 向左上方向射击能击中的目标数量，并通过预处理两个数组简化计算，思路清晰，时间复杂度为 \(O(nm)\)。
    - **核心代码片段**：
```cpp
void prework() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            s[i][j] = s[i - 1][j] + calc0(i, j) - calc0(i - k, j);
            if (j!= m) {
                c[i][j] = c[i - 1][j + 1] + calc0(i, j - k) - calc0(i - k, j);
            } else {
                c[i][j] = 0;
                int x = i, y = m - k;
                if (y < 1) {
                    x = x + m - k - 1;
                    y = 1;
                }
                while (x >= 1 && y < m) {
                    c[i][j] += flag[x][y];
                    x--;
                    y++;
                }
            }
        }
    }
}
int solve() {
    prework();
    int ans = 0, temp = 0;
    for (int i = 1; i <= n; i++) {
        temp = 0;
        for (int j = 1; j <= m; j++) {
            temp = temp - c[i][j] + s[i][j];
            ans = max(ans, temp);
        }
    }
    return ans;
}
```
核心实现思想：`prework` 函数预处理两个数组 \(s\) 和 \(c\)，用于后续计算 \(f(i, j)\)。`solve` 函数通过遍历计算每个点的 \(f(i, j)\) 并找出最大值。
3. **作者：Segment_Treap (赞：2)  星级：4星**
    - **关键亮点**：将攻击范围转化为三角形，通过旋转地图，利用二维前缀和的思想，将绿色三角形（攻击范围）表示为大三角形 - 红色梯形 - 蓝色梯形 + 黄色长方形，通过分别计算长方形、梯形前缀和来解决问题，时间复杂度为 \(O(24NM)\)。
    - **核心代码片段**：
```cpp
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        xd1[i][j] = xd1[i][j - 1];
        xd2[i][j] = xd2[i - 1][j];
        if (str[i][j] == '#') {
            xd1[i][j]++;
            xd2[i][j]++;
        }
    }
}
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        tx1[i][j] = tx1[i - 1][min(m, j + 1)] + xd1[i][j];
    }
}
for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
        tx2[j][i] = tx2[min(n, j + 1)][i - 1] + xd2[j][i];
    }
}
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        jx[i][j] = jx[i - 1][j] + jx[i][j - 1] - jx[i - 1][j - 1];
        if (str[i][j] == '#') {
            jx[i][j]++;
        }
    }
}
```
核心实现思想：先计算线段前缀和 `xd1`、`xd2`，再基于此计算梯形前缀和 `tx1`、`tx2` 以及矩形前缀和 `jx`，最后通过这些前缀和计算攻击范围内目标数量。

### 最优关键思路或技巧
 - **方向处理**：通过旋转矩阵，将四个方向的射击问题转化为只处理一个方向，减少重复计算，提高效率。
 - **差分与前缀和**：利用差分维护位置区间的贡献变化，或通过前缀和计算特定形状区域内的目标数量，优化时间复杂度。

### 可拓展之处
同类型题通常围绕在特定区域内，按某种距离规则统计元素数量或计算元素总和。类似算法套路包括利用前缀和、差分处理二维区域问题，通过旋转、翻转等操作简化多方向计算。

### 推荐洛谷题目
 - **P1387 最大正方形**：在给定的矩阵中寻找最大的全为 1 的正方形，可利用动态规划结合前缀和思想解决。
 - **P2004 领地选择**：在二维平面上选择一个子矩形，使子矩形内元素和最大，考察二维前缀和的应用。
 - **P1719 最大加权矩形**：与上一题类似，同样是在二维矩阵中寻找加权和最大的矩形区域，可通过前缀和优化暴力枚举。 

---
处理用时：42.58秒