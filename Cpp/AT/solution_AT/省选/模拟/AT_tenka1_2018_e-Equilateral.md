# Equilateral

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2018/tasks/tenka1_2018_e

$ xy $ 平面上にコインがいくつかあります。 コインの配置は $ H $ 行 $ W $ 列のグリッドを用いて表され、グリッドの $ i $ 行 $ j $ 列目の文字 $ s_{ij} $ が `#` のとき座標 $ (i,j) $ にコインがひとつあることを、 `.` のとき座標 $ (i,j) $ にコインがないことを表します。 その他に $ xy $ 平面上にコインは存在しません。

相異なるコインの $ 3 $ つ組であって、以下の条件を満たすものの個数を求めてください。

- $ 3 $ つのうちどの $ 2 $ つのコインをとっても、それらの存在する座標の間のマンハッタン距離が一定である

ただし、座標 $ (x,y),(x',y') $ の間のマンハッタン距離は、$ |x-x'|+|y-y'| $ で表されます。 また、コインの順番を入れ替えただけの組は同じものとみなします。

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 300 $
- $ s_{ij} $ は `#` または `.` である

### Sample Explanation 1

$ ((1,1),(1,3),(2,2)),((1,1),(2,2),(3,1)),((1,3),(3,1),(4,4)) $ が条件を満たします。

## 样例 #1

### 输入

```
5 4
#.##
.##.
#...
..##
...#```

### 输出

```
3```

## 样例 #2

### 输入

```
13 27
......#.........#.......#..
#############...#.....###..
..............#####...##...
...#######......#...#######
...#.....#.....###...#...#.
...#######....#.#.#.#.###.#
..............#.#.#...#.#..
#############.#.#.#...###..
#...........#...#...#######
#..#######..#...#...#.....#
#..#.....#..#...#...#.###.#
#..#######..#...#...#.#.#.#
#..........##...#...#.#####```

### 输出

```
870```

# 题解

## 作者：tder (赞：1)

> You can view the [English version](https://www.luogu.com/article/oth85fqt/) of this solution.

> 图片托管于 Github，若加载失败请使用加速器。

考虑画出三个点的哈夫曼距离。

![](https://raw.githubusercontent.com/tder6/Img/refs/heads/main/Sol/AT_tenka1_2018_e/img.png)

则有 $a+b+c=a+b+d=c+d$，即 $a+b=c=d$。这也就是说，$\overline{BC}$ 的斜率为 $\pm1$，而 $A$ 在与之平行的一条线上。

我们不妨 $\mathcal{O}(n^2)$ 枚举 $B$，$\mathcal{O}(n)$ 枚举 $C$，通过差分 $\mathcal{O}(1)$ 计算合法的 $A$ 的数量。复杂度 $\mathcal{O}(n^3)$，有较大常数。

具体的，我们枚举 $(i,j)$ 和 $k<i$，问题转化为求四条线上 $a_{x,y}=1$ 的个数。对每条斜率为 $\pm1$ 的直线预处理出前缀和即可。

![](https://raw.githubusercontent.com/tder6/Img/refs/heads/main/Sol/AT_tenka1_2018_e/type.png)

需要注意，为了避免算重，不妨将特殊的端点位置单独计算。

[Code.](https://atcoder.jp/contests/tenka1-2018/submissions/60270468)

---

## 作者：Nuyoah_awa (赞：0)

### 题目大意

给定一个矩阵，让你从中找到 $3$ 个点，使得这三个点两两曼哈顿距离相等。

### 题目分析

对于暴力一点的做法，我们直接枚举哪三个点，然后判断，时间复杂度 $\mathcal O(T^3)$。

很明显直接暴力是过不去的，于是我们来考虑如何优化。

我们需要尽可能少的枚举东西，所以，我们不妨只枚举两个点，然后我们就知道了这三点两两的曼哈顿距离了，对于一个点，与之曼哈顿距离为定值的点的集合可视为一个菱形，如下图。

![AT_tenka1_2018_e-1](https://z1.ax1x.com/2023/12/11/piW3HIO.png)

然后，我们就可以对于两个矩形计算交点处有多少个 `#`。

但是，时间复杂度依旧是 $\mathcal O(T^2 \times n)$ 的。

于是我们可以考虑将一个三角形拆分如下：

![AT_tenka1_2018_e-2](https://z1.ax1x.com/2023/12/11/piW3qiD.png)

容易得出：$a + b = b + c + d = a + c + d$。

于是，我们可以得出 $a = b = c + d$。即两个点及其垂线所组成的三角形一定是一个等腰直角三角形。所以我们枚举两个点的时间复杂度就优化成了 $\mathcal O(T \times n)$ 了。

然后我们再来观察根据两点找第三点。

![AT_tenka1_2018_e-3](https://z1.ax1x.com/2023/12/11/piW3LJe.png)

根据上述分析，范围为两个菱形，我们很容易找到第三点可能的区域，即两个一次函数上的一段，于是我们依旧可以 $\mathcal O(n)$ 枚举，$\mathcal O(1)$ 判断。

于是，算法的总时间复杂度就优化到了 $\mathcal O(T \times n^2)$，即 $\mathcal O(n ^ 4)$。这样就很接近标准时间复杂度了，可惜还是过不去。（我赛时就是这么写的，卡了一下上下界，加点剪枝，学校数据和测评机 $O(n^4)$ 放我过了，但是原题过不了）

我们再回到上一步，发现我们要做的事情实际上是第三个点所在区域中有多少个 `#`，而且这个区域只可能是 $y = x + b$ 或 $y = -x + b$ 上的一段，于是我们只需要开两个斜着的前缀和就可以了，$\mathcal O(n^2)$ 预处理，总的时间复杂度 $\mathcal O(n ^ 3)$。

总的来讲，一道有些难度的思维题，思维难度蓝，代码难度绿，算是一道挺有意思的下位紫吧。

### code
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 3e2 + 5;
int n, m, ans, line1[N][N], line2[N][N];
string s[N];

inline bool check(int x, int y)
{
    if(x > n || x < 1 || y > m || y < 1)
        return false;
    return (s[x][y] == '#');
}

int main()
{
    scanf("%d %d", &n, &m);
    for(register int i = 1;i <= n;i++)
    {
        cin >> s[i];
        s[i] = "#" + s[i];
    }
    for(int i = 1;i <= n;i++)
    {
    	for(int j = 1;j <= m;j++)
    	{
    		line1[i][j] = line1[i-1][j-1] + (s[i][j] == '#');
    		line2[i][j] = line2[i-1][j+1] + (s[i][j] == '#');
		}
	}
    for(register int x1 = 1;x1 <= n;x1++)
    {
        for(register int y1 = 1;y1 <= m;y1++)
        {
            if(s[x1][y1] == '.')    continue;
            for(register int D = 1;D < min(n, m);D++)
            {
                register int x2 = x1 + D, y2 = y1 + D, x3, y3, x4, y4;
                if(check(x2, y2))
                {
                    x3 = x1 - D, y4 = y2 + D;
                    x3 = max(x3, 1), y4 = min(y4, m);
                    int b = y2 - x1 + D;
                    y3 = x3 + b;
                    x4 = y4 - b;
                    if(x3 <= x4)
                    	ans += line1[x4][y4] - line1[x3-1][y3-1];
//                    printf("%d %d %d %d %d %d %d %d %d\n", x1, y1, x2, y2, x3, y3, x4, y4, ans);
                    y3 = y1 - D, x4 = x2 + D;
                    y3 = max(y3, 1), x4 = min(x4, n);
                    b = y1 - D - x2;
                    x3 = y3 - b;
                    y4 = x4 + b;
                    if(x3 <= x4)
                    	ans += line1[x4][y4] - line1[x3-1][y3-1];
//                    printf("%d %d %d %d %d %d %d %d %d\n", x1, y1, x2, y2, x3, y3, x4, y4, ans);
                }
                //1
                x2 = x1 + D, y2 = y1 - D;
                if(check(x2, y2))
                {
                    x3 = x1 - D + 1, y4 = y2 - D + 1;
                    x3 = max(1, x3), y4 = max(1, y4);
                    int b = x1 - D + y2;
                    y3 = b - x3, x4 = b - y4;
                    if(x3 <= x4)
                    	ans += line2[x4][y4] - line2[x3-1][y3+1];
                    y3 = y1 + D - 1, x4 = x2 + D - 1;
                    y3 = min(y3, m), x4 = min(x4, n);
                    b = x2 + y1 + D;
                    x3 = b - y3, y4 = b - x4;
                    if(x3 <= x4)
                    	ans += line2[x4][y4] - line2[x3-1][y3+1];
                }
                //2
            }
            //printf("%d %d %d\n", x1, y1, ans);
        }
    }
    printf("%d", ans);
    return 0;
}
```

---

