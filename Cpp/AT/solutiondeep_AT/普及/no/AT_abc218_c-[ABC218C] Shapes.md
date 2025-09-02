# 题目信息

# [ABC218C] Shapes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc218/tasks/abc218_c

$ 2 $ 次元グリッド上に $ 2 $ つの図形 $ S $ と $ T $ があります。グリッドは正方形のマスからなります。

$ S $ は $ N $ 行 $ N $ 列のグリッド内にあり、$ S_{i,j} $ が `#` であるようなマス全体からなります。  
 $ T $ も $ N $ 行 $ N $ 列のグリッド内にあり、$ T_{i,j} $ が `#` であるようなマス全体からなります。

$ S $ と $ T $ を $ 90 $ 度回転及び平行移動の繰り返しによって一致させることができるか判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200 $
- $ S,T $ は `#` と `.` のみからなる
- $ S,T $ は $ 1 $ つ以上 `#` を含む

### Sample Explanation 1

$ S $ を左回りに $ 90 $ 度回転させ、平行移動することで $ T $ に一致させることができます。

### Sample Explanation 2

$ 90 $ 度回転と平行移動の繰り返しによって一致させることはできません。

### Sample Explanation 3

$ S $ 及び $ T $ は連結とは限りません。

### Sample Explanation 4

回転や移動の操作は連結成分ごとにできるわけではなく、$ S,T $ 全体に対して行うことに注意してください。

## 样例 #1

### 输入

```
5

.....

..#..

.###.

.....

.....

.....

.....

....#

...##

....#```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5

#####

##..#

#..##

#####

.....

#####

#..##

##..#

#####

.....```

### 输出

```
No```

## 样例 #3

### 输入

```
4

#...

..#.

..#.

....

#...

#...

..#.

....```

### 输出

```
Yes```

## 样例 #4

### 输入

```
4

#...

.##.

..#.

....

##..

#...

..#.

....```

### 输出

```
No```

# AI分析结果



# [ABC218C] Shapes

## 题目描述

在二维网格上有两个形状 $S$ 和 $T$。网格由正方形的单元格组成。

$S$ 位于 $N$ 行 $N$ 列的网格内，由所有 $S_{i,j}$ 为 `#` 的单元格构成。  
$T$ 同样位于 $N$ 行 $N$ 列的网格内，由所有 $T_{i,j}$ 为 `#` 的单元格构成。

判断 $S$ 和 $T$ 是否可以通过 90 度旋转及平移操作相互重合。

## 说明/提示

### 制約

- $1 \leq N \leq 200$
- $S$ 和 $T$ 仅包含 `#` 和 `.`
- $S$ 和 $T$ 至少包含一个 `#`

### 样例说明

样例1：将 $S$ 逆时针旋转 90 度后平移可匹配 $T$  
样例2：无法通过旋转和平移匹配  
样例3：形状无需连通  
样例4：操作需作用于整体而非局部组件

## 算法分类
模拟

---

### 综合分析与结论
题目要求判断两个形状是否可通过旋转（0/90/180/270度）和平移重合。核心思路是枚举所有旋转情况，将每个旋转后的形状标准化（平移至原点对齐）后与目标形状比较。

### 关键思路与技巧
1. **坐标旋转公式**：  
   对于点 $(i,j)$，四种旋转后的坐标分别为：
   - 0度：$(i,j)$
   - 90度：$(j, N-1-i)$
   - 180度：$(N-1-i, N-1-j)$
   - 270度：$(N-1-j, i)$

2. **形状标准化**：  
   将所有单元格坐标平移，使得最小横纵坐标均为0，消除平移差异。

3. **集合比较**：  
   将标准化后的坐标排序后直接比较集合是否相同。

### 示例代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<string> S(N), T(N);
    for (auto &s : S) cin >> s;
    for (auto &t : T) cin >> t;

    vector<pair<int, int>> s_points, t_points;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (S[i][j] == '#') s_points.emplace_back(i, j);
            if (T[i][j] == '#') t_points.emplace_back(i, j);
        }
    }

    if (s_points.size() != t_points.size()) {
        cout << "No\n";
        return 0;
    }

    auto normalize = [](vector<pair<int, int>> pts) {
        int min_x = INT_MAX, min_y = INT_MAX;
        for (auto &p : pts) {
            min_x = min(min_x, p.first);
            min_y = min(min_y, p.second);
        }
        for (auto &p : pts) {
            p.first -= min_x;
            p.second -= min_y;
        }
        sort(pts.begin(), pts.end());
        return pts;
    };

    auto t_norm = normalize(t_points);

    for (int k = 0; k < 4; ++k) {
        vector<pair<int, int>> rotated;
        for (auto [i, j] : s_points) {
            int ni, nj;
            if (k == 0) ni = i, nj = j;
            else if (k == 1) ni = j, nj = N - 1 - i;
            else if (k == 2) ni = N - 1 - i, nj = N - 1 - j;
            else ni = N - 1 - j, nj = i;
            rotated.emplace_back(ni, nj);
        }
        auto s_norm = normalize(rotated);
        if (s_norm == t_norm) {
            cout << "Yes\n";
            return 0;
        }
    }

    cout << "No\n";
}
```

### 举一反三
1. **相似题目**  
   - [洛谷 P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：坐标变换与状态比较  
   - [洛谷 P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)：二维网格中的移动与坐标处理  
   - [洛谷 P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：网格形状分析与变换

---
处理用时：180.86秒