# [GCJ 2019 #1C] Bacterial Tactics

## 题目描述

Becca 和 Terry 是微生物学家，他们之间有着友好的竞争。当他们需要从研究中休息时，会一起玩一个游戏。该游戏在一个由 $\mathbf{R}$ 行 $\mathbf{C}$ 列组成的单元格矩阵上进行。最初，每个格子要么是空的，要么含有放射性物质。

每位玩家轮流行动，如果矩阵中没有空格子，则该玩家输掉游戏。否则，玩家选择一个空格子并在其中放置一个细菌菌落。细菌菌落有两种类型：H（代表“水平”）和 V（代表“垂直”）。

- 当在一个空格子中放置 H 型菌落时，它会占据该格子（使其变为非空），并尝试向西边（如果有）和东边（如果有）的相邻格子扩散。
- 当在一个空格子中放置 V 型菌落时，它会占据该格子（使其变为非空），并尝试向南边（如果有）和北边（如果有）的相邻格子扩散。

每当菌落（无论哪种类型）尝试扩散到某个格子时：

- 如果该格子含有放射性物质，菌落发生变异，放置该菌落的玩家输掉游戏。
- 如果该格子为空，菌落占据该格子（使其变为非空），然后再次触发上述规则（即菌落会继续尝试扩散）。
- 如果该格子已经含有细菌（任意类型），菌落不会扩散到该格子。

注意，可能存在玩家所有可选的行动都会导致自己输掉游戏的情况，因此该玩家注定失败。下面的样例解释中有关于游戏玩法的示例。

Becca 先手，然后两位玩家轮流行动，直到其中一方输掉游戏。如果双方都采取最优策略，谁会获胜？如果 Becca 会获胜，她有多少种不同的必胜开局？（只有当使用的格子不同，或菌落类型不同，或两者都不同，两个开局才算作不同。）

## 说明/提示

**样例解释**

在样例 1 中，Becca 不能在西南角的空格子放置 H 型菌落，也不能在东北角的空格子放置 V 型菌落，因为那样会扩散到放射性格子，Becca 会输。她只有两种不会立即输掉的策略：

1. 在西北角或东北角的空格子放置 H 型菌落。该菌落还会扩散到另一个角的空格子。
2. 在西北角或西南角的空格子放置 V 型菌落。该菌落还会扩散到另一个角的空格子。

如果 Becca 选择策略 1，Terry 可以在西南角的空格子放置 V 型菌落。如果 Becca 选择策略 2，Terry 可以在东北角的空格子放置 H 型菌落。无论哪种情况，Becca 下一轮都没有空格可选，因此她会输，Terry 获胜。

在样例 2 中，Becca 的任何开局都会导致变异。

在样例 3 中，Becca 有 5 种可能的开局会导致变异，但另外 7 种是必胜的。她可以在第二行的任意格子放置 H 型菌落，或者在第二列的任意格子放置 V 型菌落。无论哪种情况，她都会留下两个不相连的 1 或 2 个格子的集合。在每个集合中，只能放置一种类型的菌落，且放置后会消耗掉该集合内所有空格。因此，无论 Terry 选择消耗哪一个集合，Becca 都可以消耗另一个集合，使 Terry 无法行动。

在样例 4 中，Becca 的两种不同开局都是必胜的。

在样例 5 中，Becca 没有可行的开局。

**数据范围**

$1 \leq \mathbf{T} \leq 100$。

**测试点 1（可见）**

- $1 \leq \mathbf{R} \leq 4$。
- $1 \leq \mathbf{C} \leq 4$。

**测试点 2（隐藏）**

- $1 \leq \mathbf{R} \leq 15$。
- $1 \leq \mathbf{C} \leq 15$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
2 2
..
.#
4 4
.#..
..#.
#...
...#
3 4
#.##
....
#.##
1 1
.
1 2
##```

### 输出

```
Case #1: 0
Case #2: 0
Case #3: 7
Case #4: 2
Case #5: 0```

# 题解

## 作者：SegmentTree_ (赞：9)

下文中 $n,m$ 分别表示行数和列数。  
看到博弈，可以考虑 SG 函数。  
有一个明显的暴力做法：枚举在哪一行或哪一列操作，就能分成两个小矩形，直接递归下去，最后把这些小情况合并。$n$ 和 $m$ 同阶，加上记忆化后时间复杂度为 $O(n^5)$。因为数据范围很小，所以可以直接做。  
设 $f_x$ 表示矩形 $x$ 的 sg 值。可以得到 $f_x=\operatorname{mex}\{f_{x_1}\oplus f_{x_2}\}$，$x_1,x_2$ 表示 $x$ 经过一次合法操作后分成的两个小矩形。判断是不是合法操作，可以预处理出每个点向上和向左有多少个连续的 `.`。对于求 $\operatorname{mex}$，可以开一个数组，记录下每个数有没有出现过，因为一个矩阵最多有 $n+m$ 种不同的合法操作，所以只用开到 $2\times15=30$。  
题目要求先手必胜的第一步有多少种。可以枚举在整个矩形的第一步，如果这一步合法，并且这一步分出的两个小矩形的 sg 值的异或和等于 $0$，就把这一步算到答案里。  
一定要记得加记忆化，不然会 TLE。  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
typedef pair<int, int> pii;
namespace tianyu{
    int sg[16][16][16][16];
    bool vis[16][16][16][16];
    char mp[16][16];
    int up[16][16], left[16][16], ans;
    int n, m;
    int get(int a, int b, int c, int d){
        if (a > c || b > d) return 0;
        if (vis[a][b][c][d]) return sg[a][b][c][d];
        bool v[30] = {};
        int cnt = 0;
        for (int i = a;i <= c;i++){
            auto [x, y] = pii{i, d};
            if (left[x][y] >= d - b){
                auto [gx, gy] = pii{get(a, b, i - 1, d), get(i + 1, b, c, d)};
                if ((gx ^ gy) <= 29) v[gx ^ gy] = 1;
                if (gx == gy){
                    cnt += d - b + 1;
                }
            }
        }
        for (int i = b;i <= d;i++){
            auto [x, y] = pii{c, i};
            if (up[x][y] >= c - a){
                auto [gx, gy] = pii{get(a, b, c, i - 1), get(a, i + 1, c, d)};
                if ((gx ^ gy) <= 29) v[gx ^ gy] = 1;
                if (gx == gy){
                    cnt += c - a + 1;
                }
            }
        }
        int res = 0;
        for (int i = 0;;i++) if (!v[i]){
            res = i;
            break;
        }
        if (a == 1 && b == 1 && c == n && d == m){
            if (res) ans = cnt;
        }
        vis[a][b][c][d] = 1;
        return sg[a][b][c][d] = res;
    }
    int testcase;
	void awa(){
        memset(vis, 0, sizeof vis);
        memset(up, 0, sizeof up);
        memset(left, 0, sizeof left);
        cin >> n >> m;
        ans = 0;
        for (int i = 1;i <= n;i++){
            for (int j = 1;j <= m;j++){
                cin >> mp[i][j];
                if (mp[i][j] == '#'){
                    up[i][j] = left[i][j] = -1;
                    continue;
                }
                if (i > 1 && mp[i - 1][j] != '#') up[i][j] = up[i - 1][j] + 1;
                if (j > 1 && mp[i][j - 1] != '#') left[i][j] = left[i][j - 1] + 1;
            }
        }
        get(1, 1, n, m);
        cout << "Case #" << ++testcase << ": " << ans << '\n';
	}
}
signed main(){
	int T = 1;
    cin >> T;
	while (T--) tianyu::awa();
	return 0;
}
```

---

## 作者：sqrtqwq (赞：4)

被 wisdua 秒了。

[不知道怎么样的阅读体验](https://www.cnblogs.com/Carousel/p/19024110)。

[in Luogu](https://www.luogu.com.cn/problem/P13114)。

-----------

其实并非困难。

考虑直接暴力定义 $dp_{i,j,x,y}$ 表示左上角为 $(j,y)$ 右下角为 $(i,x)$ 的矩阵的 SG 值。转移就是考虑我每一次删掉哪行或者那列。但是这样我们在每次转移的时候还要花 $\mathrm O(n)$ 的时间去判断能否转移。那么此时考虑对于每一个点去维护在你上面的点中，离你最近的障碍的距离。那么这样我们就可以 $\mathrm O(n+m)$ 的时间内完成所有的转移。总的复杂度为 $\mathrm O(n^5)$（$n,m$ 同阶）。

```cpp
cin >> n >> m;
for(int i = 1;i <= n;i++)for(int j = 1;j <= m;j++)cin >> ch[i][j];
for(int i = 1;i <= n;i++)for(int j = 1;j <= m;j++)U[i][j] = (ch[i][j] == '#' ? 0 : U[i - 1][j] + 1);
for(int i = 1;i <= n;i++)for(int j = 1;j <= m;j++)L[i][j] = (ch[i][j] == '#' ? 0 : L[i][j - 1] + 1);
memset(dp,0,sizeof(dp));
for(int i = n;i >= 1;i--)
{
    for(int j = i;j <= n;j++)
    {
        for(int x = m;x >= 1;x--)
        {
            for(int y = x;y <= m;y++)
            {
                memset(cnt,0,sizeof(cnt));
                for(int p = i;p <= j;p++)if(L[p][y] >= y - x + 1)cnt[dp[i][p - 1][x][y] ^ dp[p + 1][j][x][y]]++;
                for(int p = x;p <= y;p++)if(U[j][p] >= j - i + 1)cnt[dp[i][j][x][p - 1] ^ dp[i][j][p + 1][y]]++;
                while(cnt[dp[i][j][x][y]])dp[i][j][x][y]++;
            }
        }
    }
}
int ans = 0;
for(int i = 1;i <= n;i++)if(L[i][m] >= m)ans += !(dp[1][i - 1][1][m] ^ dp[i + 1][n][1][m]) * m;
for(int i = 1;i <= m;i++)if(U[n][i] >= n)ans += !(dp[1][n][1][i - 1] ^ dp[1][n][i + 1][m]) * n;
cout << "Case #" << P << ": " << ans << '\n';
```

---

## 作者：newtocpp (赞：0)

### 题意
有一个 $n\times m$ 的网格，两个玩家轮流往格子里放细菌，细菌可以选择向上下或者向左右一直扩散，直到碰到其他细菌时停止，碰到一些特定的格子会输。求先手第一步有多少种放细菌的方法能赢。

***
考虑左上角为 $(i_1, j_1)$，右下角为 $(i_2, j_2)$ 的子矩阵，观察到合法地放一次细菌相当于删掉子矩阵这一行或者这一列，然后使原矩阵分裂成两个矩阵。

看到 $n,m\le15$ 可以考虑dp。

设 $f_{i_1,j_1,i_2,j_2}$ 为左上角是 $(i_1, j_1)$ 右下角是 $(i_2, j_2)$ 的子矩阵的SG值。

对于每个子矩阵，枚举删掉哪一行或者哪一列，不能碰到放射性的格子，从分裂成的两个子矩阵转移。

每一个格子上下左右走到的第一个放射性的格子可以预处理得到。

最后直接枚举第一步放的细菌统计。

复杂度 $O(Tn^2m^2(n + m))$。

Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 20;
int T, n, m, l[N][N], r[N][N], u[N][N], d[N][N];
bool rad[N][N];
ll f[N][N][N][N];
int main()
{
    scanf("%d", &T);
    for(int TT = 1; TT <= T; TT++)
    {
        memset(f, 0, sizeof(f));
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i++)
        {
            getchar();
            for(int j = 1; j <= m; j++) rad[i][j] = getchar() == '#';
        }
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                int z = i;
                while(z <= n && !rad[z][j]) ++z;
                d[i][j] = z;

                z = i;
                while(z && !rad[z][j]) --z;
                u[i][j] = z;

                z = j;
                while(z <= m && !rad[i][z]) ++z;
                r[i][j] = z;

                z = j;
                while(z && !rad[i][z]) --z;
                l[i][j] = z;
            }
        }
        for(int i1 = n; i1 >= 1; i1--)
        {
            for(int j1 = m; j1 >= 1; j1--)
            {
                for(int i2 = i1; i2 <= n; i2++)
                {
                    for(int j2 = j1; j2 <= m; j2++)
                    {
                        set<int> s;
                        for(int i = i1; i <= i2; i++) //删行
                        {
                            if(r[i][j1] <= j2) continue;
                            s.insert(f[i1][j1][i - 1][j2] ^ f[i + 1][j1][i2][j2]);
                        }
                        for(int j = j1; j <= j2; j++) //删列
                        {
                            if(d[i1][j] <= i2) continue;
                            s.insert(f[i1][j1][i2][j - 1] ^ f[i1][j + 1][i2][j2]);
                        }
                        for(int i = 0; i <= n + m; i++) //mex
                        {
                            if(!s.count(i))
                            {
                                f[i1][j1][i2][j2] = i;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if(!f[1][1][n][m]) printf("Case #%d: 0\n", TT);
        else
        {
            int ans = 0;
            for(int i = 1; i <= n; i++)
            {
                for(int j = 1; j <= m; j++)
                {
                    if(!u[i][j] && d[i][j] > n && !(f[1][1][n][j - 1] ^ f[1][j + 1][n][m])) ++ans;
                    if(!l[i][j] && r[i][j] > m && !(f[1][1][i - 1][m] ^ f[i + 1][1][n][m])) ++ans;
                }
            }
            printf("Case #%d: %d\n", TT, ans);
        }
    }
    return 0;
}
```

---

