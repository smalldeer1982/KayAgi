# 题目信息

# Rats

## 题目描述

Rats have bred to hundreds and hundreds in the basement of the store, owned by Vasily Petrovich. Vasily Petrovich may have not noticed their presence, but they got into the habit of sneaking into the warehouse and stealing food from there. Vasily Petrovich cannot put up with it anymore, he has to destroy the rats in the basement. Since mousetraps are outdated and do not help, and rat poison can poison inattentive people as well as rats, he chose a radical way: to blow up two grenades in the basement (he does not have more).

In this problem, we will present the shop basement as a rectangular table of $ n×m $ cells. Some of the cells are occupied by walls, and the rest of them are empty. Vasily has been watching the rats and he found out that at a certain time they go to sleep, and all the time they sleep in the same places. He wants to blow up a grenade when this convenient time comes. On the plan of his basement, he marked cells with sleeping rats in them. Naturally, these cells are not occupied by walls.

Grenades can only blow up in a cell that is not occupied by a wall. The blast wave from a grenade distributes as follows. We assume that the grenade blast occurs at time 0. During this initial time only the cell where the grenade blew up gets 'clear'. If at time $ t $ some cell is clear, then at time $ t+1 $ those side-neighbouring cells which are not occupied by the walls get clear too (some of them could have been cleared before). The blast wave distributes for exactly $ d $ seconds, then it dies immediately.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF254D/b144e2334a4b3ed6e085b2980cabe248fcd67fba.png)An example of a distributing blast wave: Picture 1 shows the situation before the blast, and the following pictures show "clear" cells by time 0,1,2,3 and 4. Thus, the blast wave on the picture distributes for $ d=4 $ seconds.Vasily Petrovich wonders, whether he can choose two cells to blast the grenades so as to clear all cells with sleeping rats. Write the program that finds it out.

## 样例 #1

### 输入

```
4 4 1
XXXX
XR.X
X.RX
XXXX
```

### 输出

```
2 2 2 3
```

## 样例 #2

### 输入

```
9 14 5
XXXXXXXXXXXXXX
X....R...R...X
X..R.........X
X....RXR..R..X
X..R...X.....X
XR.R...X.....X
X....XXR.....X
X....R..R.R..X
XXXXXXXXXXXXXX
```

### 输出

```
2 3 6 9
```

## 样例 #3

### 输入

```
7 7 1
XXXXXXX
X.R.R.X
X.....X
X..X..X
X..R..X
X....RX
XXXXXXX
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# Rats

## 题目描述
在瓦西里·彼得罗维奇所拥有商店的地下室里，老鼠已经繁殖到了成百上千只。瓦西里·彼得罗维奇可能一直没注意到它们的存在，但老鼠们养成了溜进仓库偷吃食物的习惯。瓦西里·彼得罗维奇再也无法忍受了，他必须消灭地下室里的老鼠。由于捕鼠器已经过时且不起作用，而老鼠药可能会误毒到粗心的人，他选择了一种激进的方法：在地下室引爆两枚手榴弹（他只有两枚）。

在这个问题中，我们将商店地下室表示为一个 $n×m$ 的矩形网格。一些网格被墙壁占据，其余的则是空的。瓦西里一直在观察老鼠，他发现老鼠在特定时间会睡觉，并且一直睡在相同的地方。他想在这个方便的时间引爆炸弹。在地下室的平面图上，他标记出了有老鼠睡觉的网格。当然，这些网格没有被墙壁占据。

手榴弹只能在没有被墙壁占据的网格中引爆。手榴弹的爆炸波传播方式如下。我们假设手榴弹在时间 $t = 0$ 时爆炸。在这个初始时刻，只有手榴弹爆炸的网格被“清理”。如果在时间 $t$ 时某个网格被清理，那么在时间 $t + 1$ 时，那些与之相邻且没有被墙壁占据的网格也会被清理（其中一些网格可能之前已经被清理过）。爆炸波恰好传播 $d$ 秒，然后立即消失。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF254D/b144e2334a4b3ed6e085b2980cabe248fcd67fba.png)
爆炸波传播的一个示例：图1显示了爆炸前的情况，接下来的图片按时间 $0,1,2,3$ 和 $4$ 显示了“被清理”的网格。因此，图中的爆炸波传播了 $d = 4$ 秒。

瓦西里·彼得罗维奇想知道，他是否可以选择两个网格来引爆炸弹，从而清理所有有老鼠睡觉的网格。编写程序来找出答案。

## 样例 #1
### 输入
```
4 4 1
XXXX
XR.X
X.RX
XXXX
```
### 输出
```
2 2 2 3
```

## 样例 #2
### 输入
```
9 14 5
XXXXXXXXXXXXXX
X....R...R...X
X..R.........X
X....RXR..R..X
X..R...X.....X
XR.R...X.....X
X....XXR.....X
X....R..R.R..X
XXXXXXXXXXXXXX
```
### 输出
```
2 3 6 9
```

## 样例 #3
### 输入
```
7 7 1
XXXXXXX
X.R.R.X
X.....X
X..X..X
X..R..X
X....RX
XXXXXXX
```
### 输出
```
-1
```

### 算法分类
搜索（广度优先搜索 BFS）

### 题解综合分析与结论
- **思路**：这几道题解均利用 BFS 解决问题，核心思路是通过限制手榴弹爆炸波及范围（与 $d$ 相关）来缩小搜索空间，避免暴力枚举所有可能的手榴弹放置位置导致的高复杂度。
- **算法要点**：利用 BFS 计算手榴弹爆炸波在 $d$ 秒内能够波及的范围，以此来判断能否炸到所有老鼠。同时，不同题解利用老鼠数量和 $d$ 的关系进行特判，减少不必要的计算。
- **解决难点**：难点在于如何优化搜索过程，避免 $O(n^4d^2)$ 的暴力枚举复杂度。题解通过先确定第一枚手榴弹能炸到某只老鼠的范围（$O(d^2)$），再在此基础上枚举第二枚手榴弹的位置，将复杂度降低到 $O(d^6)$。

### 所选的题解
- **作者：Rushmush（5星）**
    - **关键亮点**：思路清晰，先指出暴力枚举两个炸弹位置的假思路及其复杂度问题，再阐述通过 BFS 缩小炸弹位置枚举范围的真思路，详细说明了 4 个 BFS 的具体用途，代码实现中对各种边界情况（如老鼠数量小于 2、可放炸弹位置数小于 2 等）考虑全面。
    - **个人心得**：吐槽题目恶心，可能是因为实现过程中细节较多。
    - **核心代码片段**：
```cpp
void solve() {
    scanf("%d%d%d", &n, &m, &d);
    rep(i, n) {
        scanf("%s", c[i]);
        rep(j, m) {
            if (c[i][j] == 'R')r.pb(mp(i, j)), emp++;
            if (c[i][j] == '.')emp++;
        }
    }
    if (r.size() > 8 * d * d || emp < 2) {
        printf("-1");
        return;
    }
    // 省略部分代码
    queue<pair<pair<int, int>, int > >q;
    q.push(mp(mp(r[0].fi, r[0].se), 0));
    while (!q.empty()) {
        tmp = q.front();
        q.pop();
        if (tmp.se > d || c[tmp.fi.fi][tmp.fi.se] == 'X' || vis[tmp.fi.fi][tmp.fi.se])continue;
        vis[tmp.fi.fi][tmp.fi.se] = 1;
        q.push(mp(mp(tmp.fi.fi - 1, tmp.fi.se), tmp.se + 1));
        q.push(mp(mp(tmp.fi.fi + 1, tmp.fi.se), tmp.se + 1));
        q.push(mp(mp(tmp.fi.fi, tmp.fi.se - 1), tmp.se + 1));
        q.push(mp(mp(tmp.fi.fi, tmp.fi.se + 1), tmp.se + 1));
    }
    // 后续 BFS 代码省略
}
```
核心实现思想：先读入数据并进行特判，然后从第一只老鼠位置开始 BFS，标记能炸到该老鼠的位置，后续通过多次 BFS 确定两枚手榴弹能否炸到所有老鼠。
- **作者：AquariusZhao（4星）**
    - **关键亮点**：代码结构清晰，对思路的阐述结合图表，便于理解。通过预处理移动方位，利用多个 BFS 函数分别实现不同功能，如记录手榴弹炸到的老鼠数、枚举手榴弹位置等，并且对时间复杂度进行了分析。
    - **核心代码片段**：
```cpp
int bfs4(int X, int Y) {
    int res = 0;
    queue<node> q;
    memset(vis[4], 0, sizeof(vis[4]));
    q.push({X, Y, 0});
    vis[4][X][Y] = true;
    while (!q.empty()) {
        node cur = q.front();
        q.pop();
        if (!vis[2][cur.x][cur.y])
            res += s[cur.x][cur.y] == 'R';
        if (cur.p >= d)
            continue;
        for (int i = 0; i < 4; i++) {
            int tx = cur.x + pos[i][0], ty = cur.y + pos[i][1];
            if (1 < tx && tx < n && 1 < ty && ty < m &&!vis[4][tx][ty] && s[tx][ty]!= 'X') {
                q.push({tx, ty, cur.p + 1});
                vis[4][tx][ty] = true;
            }
        }
    }
    return res;
}
// 省略其他 BFS 函数
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m >> d;
    for (int i = 1; i <= n; i++) {
        scanf("%s", s[i] + 1);
        for (int j = 1; j <= m; j++)
            if (s[i][j] == 'R')
                mice.push_back({i, j});
    }
    if (mice.size() <= 4 * d * d + 4 * d + 2 && bfs1(mice[0].first, mice[0].second))
        printf("%d %d %d %d\n", a.first, a.second, b.first, b.second);
    else
        puts("-1");
    return 0;
}
```
核心实现思想：通过多个 BFS 函数分工合作，`bfs1` 枚举第一枚手榴弹位置，`bfs2` 记录第一枚手榴弹炸到的老鼠数并查找未被炸到的老鼠，`bfs3` 枚举第二枚手榴弹位置找到能炸到最多剩余老鼠的位置，`bfs4` 记录第二枚手榴弹炸到的老鼠数。
- **作者：沉石鱼惊旋（4星）**
    - **关键亮点**：从 $d$ 很小这一特点出发，提出较为巧妙的思路，通过曼哈顿距离确定两个炸弹的候选点范围，然后枚举候选点组合并用 BFS 判断是否能炸到所有老鼠，对复杂度分析清晰，且提到了自己被卡常的经历及解决办法。
    - **个人心得**：认为题目分析后并不难写，分享了被 `std::map` 卡常的调试经历。
    - **核心代码片段**：
```cpp
void bfs(int x, int y) {
    col++;
    queue<array<int, 3>> q;
    q.push({x, y, 0});
    while (!q.empty()) {
        auto [x, y, d] = q.front();
        q.pop();
        if (vis[x][y] == col)
            continue;
        vis[x][y] = col;
        if (mp[x][y] == 'R')
            s.insert({x, y});
        if (d == k)
            continue;
        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (in(tx, ty) && mp[tx][ty]!= 'X')
                q.push({tx, ty, d + 1});
        }
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            cin >> mp[i][j];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j] == 'R')
                vec.push_back({i, j});
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j]!= 'X' && abs(i - vec[0][0]) + abs(j - vec[0][1]) <= k)
                v1.push_back({i, j});
        }
    }
    // 省略部分代码
    for (auto [ax, ay] : v1) {
        for (auto [bx, by] : v2) {
            if (ax == bx && ay == by)
                continue;
            s.clear();
            bfs(ax, ay);
            bfs(bx, by);
            if (s.size() == vec.size())
                return cout << ax << ' ' << ay << ' ' << bx << ' ' << by << '\n', 0;
        }
    }
    cout << -1 << '\n';
    return 0;
}
```
核心实现思想：先读入数据并找到老鼠位置，通过曼哈顿距离确定两个炸弹的候选点范围，对每对候选点组合进行两次 BFS，判断是否能炸到所有老鼠。

### 最优关键思路或技巧
利用 BFS 计算爆炸波范围，并结合数据范围特点（$d$ 较小），通过先确定一枚手榴弹能炸到某只老鼠的范围来缩小搜索空间，从而优化算法复杂度。同时，利用老鼠数量和 $d$ 的关系进行特判，减少不必要的计算。

### 可拓展思路
此类题目属于网格图上的搜索问题，拓展方向可考虑增加手榴弹数量、改变爆炸波传播规则（如斜向传播、非均匀传播等）、增加地图元素（如障碍物类型多样化）等。类似算法套路是在网格图问题中，若某些参数范围较小（如本题的 $d$），可尝试以此为突破口，缩小搜索空间，优化暴力搜索算法。

### 洛谷相似题目推荐
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：同样是网格图问题，涉及到对特定区域的标记和搜索，可锻炼 BFS 在网格图上的应用。
- [P1332 血色先锋队](https://www.luogu.com.cn/problem/P1332)：网格图中带有条件限制的搜索问题，与本题类似，需要合理利用搜索算法解决问题。
- [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)：通过 BFS 求解迷宫问题，与本题在搜索方式和对网格图的处理上有相似之处。 

---
处理用时：117.79秒