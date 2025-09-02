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
    - 思路：各题解均通过模拟操作过程来计算侧面积。每次操作先将新堆叠方块的侧面积（\(4z\)）加到总侧面积中，再减去与相邻方块重叠部分的面积，以此更新总侧面积。
    - 算法要点：使用 `map` 来存储每个坐标位置上方块的高度，以解决坐标范围大导致数组无法存储的问题。计算重叠面积时，考虑当前位置与相邻四个位置方块高度的比较。
    - 解决难点：一是处理大坐标范围的存储问题，二是准确计算每次操作后因方块相邻而减少的侧面积。各题解在计算重叠面积的细节处理上略有不同，但核心思路一致。
    - 总体来看，各题解思路清晰，但在代码可读性和优化程度上存在差异。

所选的题解：
  - 作者：chen_zhe (5星)
    - 关键亮点：思路阐述清晰，先提出无相邻柱子时的侧面积公式，再说明处理相邻情况的方法，对维护 \(G\) 数组的方式提供多种思路，代码简洁明了。
    - 重点代码核心实现思想：通过 `map<int, map<int, long long>> G` 存储每个坐标的方块高度，每次操作遍历四个相邻位置，若相邻位置高度大于当前位置原高度，则减去重叠面积，最后更新当前位置高度并累加新方块侧面积。
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
  - 作者：FXT1110011010OI (4星)
    - 关键亮点：思路表述详细，对增加部分和重叠部分分别阐述，代码结构清晰，使用 `typedef` 简化类型书写。
    - 重点代码核心实现思想：用 `map<PII, ll> now` 存储每个坐标的方块高度，每次操作先累加新方块侧面积，再遍历四个相邻位置，根据高度差计算并减去重叠面积，最后更新当前位置高度。
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
  - 作者：wangzl (4星)
    - 关键亮点：核心思路明确，对使用 `map` 和 `pair` 结合代替二维数组、数据类型选择及重叠面积计算要点都有清晰说明，代码简洁紧凑。
    - 重点代码核心实现思想：利用 `map<pair<int, int>, long long>q` 存储方块高度，每次操作先累加新方块侧面积，再分别计算四个相邻位置的重叠面积并从总侧面积中减去，最后更新当前位置高度。
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
        ans += z * 4,
        ans -= 2 * Min(z, q[{x - 1, y}] - q[{x, y}]),
        ans -= 2 * Min(z, q[{x, y - 1}] - q[{x, y}]),
        ans -= 2 * Min(z, q[{x + 1, y}] - q[{x, y}]),
        ans -= 2 * Min(z, q[{x, y + 1}] - q[{x, y}]);
        q[{x, y}] += z;
        printf("%llu\n", ans);
    }
    return 0; 
}
```

最优关键思路或技巧：
    - **数据结构选择**：使用 `map` 来存储方块高度信息，解决了因坐标范围大无法使用常规数组存储的问题，且 `map` 的查找和修改操作时间复杂度为 \(O(\log n)\)，能满足本题需求。
    - **计算重叠面积**：通过比较当前位置与相邻位置方块的高度，准确计算每次操作后重叠部分的面积，避免重复计算或计算不足。

可拓展思路：
此类题目属于模拟与几何结合的问题，类似套路是分析每次操作对目标值（如面积、体积等）的影响，先计算操作带来的直接变化，再考虑与周围元素的相互作用导致的变化。对于大坐标范围问题，除 `map` 外，还可考虑离散化等方法。

推荐题目：
    - [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)：涉及在方格上进行操作并计算得分，与本题在处理方格数据上有相似之处。
    - [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：通过动态规划解决在一定限制下的选择问题，与本题分析操作对结果影响的思路类似。
    - [P1240 诸侯安置](https://www.luogu.com.cn/problem/P1240)：在棋盘上进行放置操作并满足一定条件，与本题在方格上进行操作并计算相关值有相似的思考方式。

个人心得摘录：
  - FXT1110011010OI：提到题目名更改，感慨比赛时没做出该题，写题解纪念。总结了自身不足，有反思学习的态度。 

---
处理用时：60.05秒