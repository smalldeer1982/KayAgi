# 题目信息

# Triangular Paths

## 题目描述

考虑一个多层的“无穷三角形”，每层自上向下从一开始编号。第 $k$ 层有 $k$ 个节点，自左向右从一开始编号。三角形上每个点由坐标 $(r,c)$ 表示，其中前一个坐标表示层，后一个坐标表示序号。对于每个节点 $(r,c)$ 连两条**有向**边到点 $(r+1,c)$ 和 $(r+1,c+1)$，但是只有其中一条边被激活。如果 $r+c$ 是偶数，则到 $(r+1,c)$ 的边被激活。否则到 $(r+1,c+1)$ 的边被激活。如果您不能理解可以看题图理解。图中“被激活的边”为黑色，其他边为灰色。如果可以沿着被激活的边自 $(r_1,c_1)$ 到 $(r_2,c_2)$，称这两个点连通。例如，$(1,1)$ 和 $(3,2)$ 连通，但 $(2,1)$ 和 $(1,1)$ 不连通。

一开始，你在 $1,1$。每一步可以：

- 改变激活性。例如，您可以将本来到 $(r+1,c)$ 的激活边去激活并使得到 $(r+1,c+1)$ 的边被激活。这个操作花费 $1$ 的代价。

- 顺着激活的边到达下一层，无需消耗代价。

现在你被给出一个“无穷三角形”上的点的序列 $Q={r_i,c_i}$，现在请你找到花费最小的方式，使得你顺利经过这些点，不必考虑顺序。

## 说明/提示

$1\leqslant\sum n\leqslant2\times10^5,1\leqslant c_i\leqslant r_i \leqslant 10^9,1\leqslant t\leqslant10^4$

## 样例 #1

### 输入

```
4
3
1 4 2
1 3 1
2
2 4
2 3
2
1 1000000000
1 1000000000
4
3 10 5 8
2 5 2 4```

### 输出

```
0
1
999999999
2```

# AI分析结果

### 题目分类
图论

### 综合分析与结论
这几道题解都围绕如何计算在给定的无穷三角形图中从 `(1, 1)` 出发经过所有给定点的最小花费展开。各题解的主要区别在于对两点间路径花费的计算思路和实现方式。
- **rong_nian**：通过对两点 `r - c` 是否相同进行分类讨论，利用边的奇偶性特点计算花费，思路清晰，代码实现简洁。
- **Warriors_Cat**：将问题转化为从 `(1, 1)` 或 `(2, 1)` 出发到新坐标的问题，同样进行分类讨论计算花费，时间复杂度为 $O(n\log n)$。
- **Prms_Prmt**：把原图旋转转化为网格图，贪心策略是尽量在 `r - c` 为奇数的行上走，统计偶行的贡献并分类讨论行之间的代价。
- **__Deng_Rui_Song__**：按行排序后，根据 `r - c` 是否相等以及其奇偶性进行分类讨论计算花费。

### 所选题解
- **rong_nian（5星）**：
  - **关键亮点**：思路清晰，对图形的特点分析透彻，分类讨论明确，代码简洁易懂。
- **Warriors_Cat（4星）**：
  - **关键亮点**：将问题进行转化，便于理解和计算，代码结构清晰，注释丰富。
- **__Deng_Rui_Song__（4星）**：
  - **关键亮点**：通过旋转图形找到规律，分类讨论合理，代码实现简洁。

### 重点代码
#### rong_nian
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 2e5 + 5;
int n;
struct poi {
    int r, c;
} e[N];
bool cmp(poi a, poi b) {
    return a.r < b.r;
}
LL ans;

int main() {
    int t; scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        int pos = -1;
        for (int i = 1; i <= n; ++i) {
            scanf ("%d", &e[i].r);
            if (e[i].r == 1) pos = i;
        }
        for (int i = 1; i <= n; ++i) {
            scanf ("%d", &e[i].c);
            if (e[i].c == 1 && pos == i) pos = 0;
        }
        if (pos != 0) {
            n++;
            e[n].r = e[n].c = 1;
        }
        sort(e + 1, e + n + 1, cmp);
        ans = 0;
        for (int i = 2; i <= n; ++i) {
            if (e[i].r - e[i].c == e[i - 1].r - e[i - 1].c) {
                if ((e[i].c + e[i].r) % 2 == 0) {
                    ans += e[i].r - e[i - 1].r;
                }
            } else {
                int r = e[i].r - e[i - 1].r + 1, c = e[i].c - e[i - 1].c + 1;
                if ((e[i - 1].r + e[i - 1].c) % 2 == 0) {
                    ans += (r - c) / 2;
                } else ans += (r - c + 1) / 2;
            }
        }
        printf ("%lld\n", ans);
    }
    return 0;
}
```
**核心实现思想**：先将所有点按 `r` 排序，然后遍历相邻两点，根据 `r - c` 是否相同以及 `r + c` 的奇偶性分类计算两点间的花费，最后累加得到总花费。

#### Warriors_Cat
```cpp
inline int calc1(int x, int y){
    if(x == y) return x - 1;
    return (x - y) / 2;
}
inline int calc2(int x, int y){
    if(x == y + 1) return 0;
    return (x - y) / 2;
}
inline void mian(){
    n = read(); a[0].x = a[0].y = 1;
    rep(i, 1, n) a[i].x = read();
    rep(i, 1, n) a[i].y = read();
    sort(a, a + n + 1); ll ans = 0;
    rep(i, 1, n){
        int x1 = a[i - 1].x, x2 = a[i].x, y1 = a[i - 1].y, y2 = a[i].y;
        if((x1 & 1) == (y1 & 1)) ans += calc1(x2 - x1 + 1, y2 - y1 + 1);
        else ans += calc2(x2 - x1 + 2, y2 - y1 + 1);
    }
    printf("%lld\n", ans);
}
```
**核心实现思想**：定义两个计算函数 `calc1` 和 `calc2` 分别处理不同情况，将所有点按 `x` 排序，遍历相邻两点，根据起点的奇偶性选择相应的计算函数计算花费并累加。

#### __Deng_Rui_Song__
```cpp
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i].first;
  for (int i = 1; i <= n; i++) cin >> a[i].second;
  sort(a + 1, a + n + 1);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int tmp = ans, x1 = a[i - 1].first, y1 = a[i - 1].second, x2 = a[i].first, y2 = a[i].second;
    if (x1 - y1 == x2 - y2)
      ans += ((x1 - y1) % 2 ? 0 : x2 - x1);
    else {
      if ((x1 - y1) % 2)
        ans += (x2 - x1 - y2 + y1 + 1) / 2;
      else
        ans += (x2 - x1 - y2 + y1) / 2;
    }
  }
  cout << ans << '\n';
}
```
**核心实现思想**：将所有点按行排序，遍历相邻两点，根据 `r - c` 是否相等以及其奇偶性分类计算两点间的花费，最后输出总花费。

### 最优关键思路或技巧
- 对图形进行观察和分析，发现 `r - c` 相同的点在同一条链上，利用边的奇偶性特点进行分类讨论。
- 可以通过旋转图形将问题转化为更易处理的形式，如转化为网格图。

### 拓展思路
同类型题可能会改变图形结构或边的激活规则，但解题的关键仍然是分析图形特点，找到点与点之间的路径规律，通过分类讨论计算花费。类似算法套路包括对图形进行转化、利用奇偶性分类讨论等。

### 推荐题目
- [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)
- [P1346 电车](https://www.luogu.com.cn/problem/P1346)
- [P2829 信用卡凸包](https://www.luogu.com.cn/problem/P2829)

### 个人心得
- __Deng_Rui_Song__：提到把头顺时针旋转 45° 发现规律，强调了从不同角度观察问题的重要性。 

---
处理用时：52.99秒