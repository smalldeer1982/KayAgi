# 题目信息

# Very Suspicious

## 题目描述

Sehr Sus is an infinite hexagonal grid as pictured below, controlled by MennaFadali, ZerooCool and Hosssam.

They love equilateral triangles and want to create $ n $ equilateral triangles on the grid by adding some straight lines. The triangles must all be empty from the inside (in other words, no straight line or hexagon edge should pass through any of the triangles).

You are allowed to add straight lines parallel to the edges of the hexagons. Given $ n $ , what is the minimum number of lines you need to add to create at least $ n $ equilateral triangles as described?

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1670D/5491a1c977b08c3202f038f487f2a32d813abedc.png)Adding two red lines results in two new yellow equilateral triangles.

## 说明/提示

In the first and second test cases only 2 lines are needed. After adding the first line, no equilateral triangles will be created no matter where it is added. But after adding the second line, two more triangles will be created at once.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1670D/22d6faf1616d600d29aaaff5a040ccd6f3af5678.png)In the third test case, the minimum needed is 3 lines as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1670D/2b991947c4bc515f58f281666fad74ef0d33ed67.png)

## 样例 #1

### 输入

```
4
1
2
3
4567```

### 输出

```
2
2
3
83```

# AI分析结果



# Very Suspicious 的题目翻译

## 题目描述

Sehr Sus 是一个由 MennaFadali、ZerooCool 和 Hosssam 控制的无限六边形网格，如下图所示。

他们喜欢等边三角形，希望通过添加直线在网格上创建至少 $n$ 个内部空的等边三角形（即三角形内部不能有任何直线或六边形边穿过）。

允许添加与六边形边平行的直线。给定 $n$，求创建至少 $n$ 个符合条件的等边三角形所需添加的最少直线数。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1670D/5491a1c977b08c3202f038f487f2a32d813abedc.png)  
*添加两条红色直线后生成两个黄色等边三角形*

## 说明/提示

- 第一、二个测试用例只需 2 条直线。第一条直线无法生成三角形，但第二条会立即生成两个。
- 第三个测试用例需要 3 条直线，如下所示。
- 直线只能有三种方向：水平、60°、120°。

## 样例 #1

### 输入
```
4
1
2
3
4567
```

### 输出
```
2
2
3
83
```

---

# 题解分析与结论

## 关键思路总结

### 核心观察
1. **方向平衡策略**：添加的直线应尽可能均匀分布在三个方向（水平、60°、120°），以最大化交点数。
2. **交点数与三角形关系**：每个交点生成 2 个三角形，总三角形数为 $2 \times (xy + yz + zx)$，其中 $x,y,z$ 是三个方向的直线数。
3. **数学优化**：最优解可通过二分法验证，或直接通过公式 $x = \lceil \sqrt{1.5n} \rceil$ 快速计算。

### 最优解法
1. **数学公式法**（loser_seele 题解）：
   - 时间复杂度：$O(1)$，直接计算。
   - 公式推导：当直线数 $x$ 满足 $\frac{2x^2}{3} \geq n$ 时，最小 $x$ 即为答案。
   - 实现要点：对 $\sqrt{\frac{3n}{2}}$ 向上取整。

2. **二分法验证**（I_am_Accepted 题解）：
   - 时间复杂度：$O(T \log n)$，适用于通用场景。
   - 核心函数：通过二分查找确定最小直线数，每次验证时计算三个方向的直线分布。

---

# 精选题解

## 题解1：loser_seele（★★★★★）
**关键亮点**：
- **数学公式直接计算**，时间复杂度最优。
- 推导出 $x = \lceil \sqrt{1.5n} \rceil$，实现简洁高效。

**代码核心**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int f(double a) {
    return ceil(sqrt(a * 3 / 2));
}
signed main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        cout << f(n) << '\n';
    }
    return 0;
}
```

---

## 题解2：I_am_Accepted（★★★★★）
**关键亮点**：
- **严格的方向平衡证明**，确保交点数最大化。
- 通过二分法精确求解，代码清晰易懂。

**代码核心**：
```cpp
#include<bits/stdc++.h>
using namespace std;

inline int check(int x) {
    int a = x/3 + (x%3 > 0);
    int b = x/3 + (x%3 > 1);
    int c = x/3;
    return 2 * (a*b + b*c + c*a);
}

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int l = 1, r = 2e5, ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid) >= n) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

# 拓展与练习

## 相似知识点题目
1. **P2735 [USACO3.4]网 Electric Fences**  
   *几何模型与数学优化*
2. **P1873 砍树**  
   *二分法应用*
3. **P1226 快速幂**  
   *数学公式优化*

## 关键技巧总结
- **方向平衡**：在涉及多方向交点的几何问题中，均匀分布往往能最大化交点数。
- **数学建模**：将问题转化为数学公式可极大优化时间复杂度。
- **二分验证**：当直接公式难以推导时，二分法结合验证函数是通用解决方案。

---
处理用时：147.13秒