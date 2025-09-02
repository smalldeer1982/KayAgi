# 题目信息

# [Aya Round 1 E] 乙（two）

## 题目描述

定义由若干个边长为 $1$ 的正方体方块搭成的立体图形的「侧面积」为：对于所有方块，若它的前、后、左或右面没有紧贴着另一个方块，则该面计入侧面积。

维护长宽均无限的矩形地面，地面被划分为若干个边长为 $1$ 的格子。$n$ 次操作，每次选择一个格子 $(x_i,y_i)$ 在该位置向上堆叠 $z_i$ 个边长为 $1$ 的正方体方块。每次操作后，输出整个立体图形的「侧面积」。

## 说明/提示

### 样例 1 解释

如图所示，建立空间直角坐标系。注意这里的空间直角坐标系和数学上常用的略有区别，其 $x$-轴向南、$y$-轴向东、$z$-轴向上。限于技术原因，此处仅给出斜二测画法的立体图形，请读者自行脑补立体图形其他角度的模样。图中绿色部分即为立体图形的侧面。

第一次操作后，在 $(1,1)$ 位置放入了一个高度为 $2$ 的立体图形，侧面积为 $8$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ncd21a4f.png)

第二次操作后，在 $(1,3)$ 位置放入了一个高度为 $3$ 的立体图形，侧面积为 $12$。由于两个立体图形没有接触，因此可以直接加上第一次放上的立体图形的侧面积，总侧面积为 $20$。

![](https://cdn.luogu.com.cn/upload/image_hosting/hl9f45rq.png)

第三次操作后，在 $(1,2)$ 位置放入了一个高度为 $4$ 的立体图形。由于某些面发生了接触，这些面对应的面积不计入侧面积的计算范围内。容易发现，总侧面积为 $26$。

![](https://cdn.luogu.com.cn/upload/image_hosting/j8x2mtc8.png)

---

再强调下，每次堆叠操作是在对应位置上再加上 $z_i$ 个方块。例如下图，是先执行了 $\verb!2 2 1!$，再执行了 $\verb!2 2 3!$ 的结果。

![](https://cdn.luogu.com.cn/upload/image_hosting/3lgipl4z.png)

### 附加样例

- 样例 $3$ 见下发文件中的 $\textbf{\textit{two3.in/two3.ans}}$。该样例满足测试点 $4$ 的限制。
- 样例 $4$ 见下发文件中的 $\textbf{\textit{two4.in/two4.ans}}$。该样例满足测试点 $7$ 的限制。
- 样例 $5$ 见下发文件中的 $\textbf{\textit{two5.in/two5.ans}}$。该样例满足测试点 $10$ 的限制。
- 样例 $6$ 见下发文件中的 $\textbf{\textit{two6.in/two6.ans}}$。该样例满足测试点 $13$ 的限制。
- 样例 $7$ 见下发文件中的 $\textbf{\textit{two7.in/two7.ans}}$。该样例满足测试点 $20$ 的限制。

### 数据范围

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c||c|c|c|c|c|} \hline
\textbf{\textsf{\#}} & \bm{{n \le }} & \bm{{x,y \le}} & \bm{{z \le}} & \textbf{\textsf{特殊性质}} &
\textbf{\textsf{\#}} & \bm{{n \le }} & \bm{{x,y \le}} & \bm{{z \le}} & \textbf{\textsf{特殊性质}} \cr\hline
1 & 1 & 1 & 10 & - &
14 & 10^3 & 10^3 & 10^3 & - \cr\hline
2 & 2 & 5 & 10 & - &
15 & 10^3 & 10^3 & 10^9 & - \cr\hline
3 & 10 & 5 & 10 & - &
16 & 10^3 & 10^9 & 10^9 & - \cr\hline
4 & 100 & 100 & 100 & - &
17 & 10^5 & 10^9 & 10^9 & \textbf{AB} \cr\hline
5 & 10^3 & 10^3 & 10^3 & \textbf{AB} &
18 & 10^5 & 10^9 & 10^9 & \textbf{A} \cr\hline
6 & 10^3 & 10^3 & 10^9 & \textbf{AB} &
19 & 10^5 & 10^9 & 10^9 & \textbf{B} \cr\hline
7 & 10^3 & 10^9 & 10^9 & \textbf{AB} &
20 & 10^5 & 10^9 & 10^9 & - \cr\hline
8 & 10^3 & 10^3 & 10^3 & \textbf{A} &
21 & 2\times 10^5 & 10^9 & 10^9 & - \cr\hline
9 & 10^3 & 10^3 & 10^9 & \textbf{A} &
22 & 2\times 10^5 & 10^9 & 10^{12} & - \cr\hline
10 & 10^3 & 10^9 & 10^9 & \textbf{A} &
23 & 2\times 10^5 & 10^9 & 10^{13} & \textbf{A} \cr\hline
11 & 10^3 & 10^3 & 10^3 & \textbf{B} &
24 & 2\times 10^5 & 10^9 & 10^{13} & - \cr\hline
12 & 10^3 & 10^3 & 10^9 & \textbf{B} &
25 & 3\times 10^5 & 10^9 & 10^{13} & - \cr\hline
13 & 10^3 & 10^9 & 10^9 & \textbf{B} &&&&&\cr\hline
\end{array}
$$

- 特殊限制 $\bf A$：$\forall 1 \le i\le j \le n$，有 $x_i=x_j$。
- 特殊限制 $\bf B$：$\forall 1 \le i\le j \le n$，有 $(x_i,y_i) \ne (x_j,y_j)$。

对于 $100\%$ 的数据，保证 $1 \le n \le 3 \times 10^5$，$1 \le x,y \le 10^9$，$1\le z \le 10^{13}$。

## 样例 #1

### 输入

```
3
1 1 2
1 3 3
1 2 4```

### 输出

```
8
20
26```

## 样例 #2

### 输入

```
6
1 2 1
2 1 4
2 3 8
3 2 6
2 2 2
2 2 11```

### 输出

```
4
20
52
76
70
90```

# AI分析结果

• 综合分析与结论：
    - 思路：各题解思路一致，均是在每次堆叠方块操作时，先计算新增方块侧面积（\(4z\)），再考虑与相邻方块重叠部分，减去重叠导致减少的侧面积，以此更新总侧面积。
    - 算法要点：使用 `map` 来存储每个坐标位置上方块的高度信息，以应对 \(x\)、\(y\) 范围大无法用常规数组存储的问题。
    - 解决难点：准确计算重叠部分面积。当相邻方块高度大于当前方块原高度时，需减去重叠部分面积，计算时要考虑当前新增方块高度 \(z\) 与相邻方块和当前方块原高度差的关系，避免减多或减少。同时注意答案会超出 `long long` 范围，需用 `unsigned long long`。
    - 整体而言，各题解思路清晰，但在代码可读性、优化程度上有差异。

  - 所选的题解：
    - 作者：chen_zhe (5星)
      - 关键亮点：思路阐述清晰，先点明无相邻柱子时答案形式，再详细说明处理柱子相邻情况的方法，对维护 `G` 数组的两种方式及数据范围导致的类型选择都有说明，代码简洁明了。
      - 重点代码：
```cpp
#include <iostream>
#include <map>
using namespace std;
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};
map <int,map<int,long long>> G;
unsigned long long ans;
int main()
{
    int n;
    cin >> n;
    for (int i=1;i<=n;i++)
    {
        int x,y;
        long long z;
        cin >> x >> y >> z;
        for (int j=0;j<4;j++)
        {
            int nx=x+dx[j],ny=y+dy[j];
            if (G[nx][ny]>G[x][y])
                ans-=2ull*min(z,G[nx][ny]-G[x][y]);
        }
        G[x][y]+=z;
        ans+=4ull*z;
        cout << ans << endl;
    }
    return 0;
}
```
      - 核心实现思想：每次读入操作的坐标 \(x\)、\(y\) 和堆叠高度 \(z\)，遍历四个相邻位置，若相邻位置高度大于当前位置原高度，则减去重叠部分面积（\(2\times\)当前新增高度与相邻和当前原高度差的较小值），然后更新当前位置高度，并加上新增方块侧面积，输出当前总侧面积。

    - 作者：FXT1110011010OI (4星)
      - 关键亮点：思路清晰，分增加部分和重叠部分阐述，代码简洁，使用 `typedef` 简化类型书写，注释详细。
      - 重点代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
map<PII, ll> now;
int main()
{
    int n;
    ull res = 0;
    scanf("%d", &n);
    while (n -- )
    {
        int x, y;
        ll z;
        scanf("%d%d%lld", &x, &y, &z);
        res += z * 4;
        for (int i = 0; i < 4; i ++ )
        {
            int tx = x + dx[i], ty = y + dy[i];
            res -= 2 * min(z, max(0ll, now[{tx, ty}] - now[{x, y}]));
        }
        now[{x, y}] += z;
        printf("%llu\n", res);
    }
    return 0;
}
```
      - 核心实现思想：每次操作先给结果加上新增方块侧面积 \(z\times4\)，遍历四个相邻位置，计算并减去重叠部分面积（\(2\times\)当前新增高度与相邻和当前原高度差（与0取max）的较小值），更新当前位置方块高度，输出结果。

    - 作者：wangzl (4星)
      - 关键亮点：核心思路明确，对使用 `map` 和 `pair` 结合代替二维数组、数据范围导致类型选择及重叠面积计算需乘2的要点都有强调。
      - 重点代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int mod = 1e9 + 7;
int n;
ull ans;
map<pair<int, int>, long long>q;
long long Min(long long x,long long y) {return min(x, max(y, (long long)0)); }
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x, y; long long z;
        scanf("%d%d%llu", &x, &y, &z);
        ans += z * 4;
        ans -= 2 * Min(z, q[{x - 1, y}] - q[{x, y}]);
        ans -= 2 * Min(z, q[{x, y - 1}] - q[{x, y}]);
        ans -= 2 * Min(z, q[{x + 1, y}] - q[{x, y}]);
        ans -= 2 * Min(z, q[{x, y + 1}] - q[{x, y}]);
        q[{x, y}] += z;
        printf("%llu\n", ans);
    }
    return 0; 
}
```
      - 核心实现思想：每次操作先加上新增方块侧面积 \(z\times4\)，分别对四个相邻位置计算并减去重叠部分面积（\(2\times\)当前新增高度与相邻和当前原高度差（经Min函数处理）的值），更新当前位置方块高度，输出总侧面积。

• 最优关键思路或技巧：
    - 数据结构：利用 `map` 存储方块高度信息，解决坐标范围大无法用常规数组存储的问题。
    - 思维方式：采用先加新增侧面积，再减重叠部分面积的容斥思想，简化计算过程。

• 可拓展思路：此类题目属于空间图形表面积计算与动态更新问题，类似套路是分析每次操作对结果的影响，利用合适数据结构存储关键信息。同类型题可能会改变图形形状、操作方式或限制条件，如改变方块形状、增加删除操作等。

• 推荐题目：
    - P1002 [NOIP2002 普及组] 过河卒：涉及路径规划与状态转移，与本题利用数据结构存储信息并动态更新结果有相似之处。
    - P1162 填涂颜色：关于图形的填充与状态判断，和本题对空间图形的处理有类似思考方向。
    - P2704 [NOI2001] 炮兵阵地：涉及在特定地形上放置元素并满足条件，需分析状态变化，与本题动态更新侧面积思路类似。

• 个人心得摘录与总结：
    - 作者FXT1110011010OI提到比赛时没做出该题，写题解纪念，反映出通过写题解总结经验的学习方法。
    - 作者血色黄昏表示原以为不会做，写完其他题再做发现简单，说明考试时合理安排做题顺序及克服畏难心理的重要性。 

---
处理用时：36.29秒