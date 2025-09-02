# [JOI 2023 Final] 迷宫 / Maze

## 题目描述

总统 K 喜欢解迷宫。他找到了可以用来创建迷宫的格子。这些格子是一个有 $R$ 行和 $C$ 列的矩形网格。每个格子要么是白色，要么是黑色。位于从上到下第 $i$ 行（$1 \leqslant i \leqslant R$）和从左到右第 $j$ 列（$1 \leqslant j \leqslant C$）的格子称为格子 $(i, j)$。

总统 K 将在可以通过白色格子而不能通过黑色格子的条件下解迷宫。更具体地，他将按以下方式解迷宫。

1. 在白色格子中，他将选择格子 $(S_r, S_c)$ 作为迷宫的起始格子，以及格子 $(G_r, G_c)$ 作为迷宫的目标格子。
2. 可以从一个格子移动到相邻的白色格子，方向可以是四个方向之一（上、下、左或右）。通过重复这个过程，他将找到从起始格子到目标格子的路径。

总统 K 已经固定了起始格子和目标格子。然而，他注意到在某些格子的颜色情况下，可能不存在一条仅由白色格子组成的从起始格子到目标格子的路径。他有一个大小为 $N \times N$ 的印章。他将多次执行以下**操作**，以便存在一条仅由白色格子组成的从起始格子到目标格子的路径。

**操作。** 他选择一个 $N \times N$ 的正方形区域，并将该区域内的格子涂成白色。更具体地，他选择整数 $a, b$ 满足 $1 \leqslant a \leqslant R - N + 1$ 和 $1 \leqslant b \leqslant C - N + 1$，对于每对整数 $(i, j)$ 满足 $a \leqslant i \leqslant a + N - 1$ 和 $b \leqslant j \leqslant b + N - 1$，他将格子 $(i, j)$ 涂成白色。

由于使用印章会弄脏他的手，他希望最小化操作次数。给定格子的颜色信息、印章的大小以及起始格子和目标格子的位置，编写一个程序计算他必须执行的最小操作次数，以便存在一条仅由白色格子组成的从起始格子到目标格子的路径。

## 说明/提示

#### 【样例解释 #1】

如果他选择 $(a, b) = (1, 2)$ 并执行一次操作，格子 $(1, 2), (1, 3), (2, 2), (2, 3)$ 变成白色。然后将存在一条仅由白色格子组成的从起始格子到目标格子的路径。例如，路径 $(1, 1) \to (1, 2) \to (1, 3) \to (2, 3) \to (2, 4)$ 满足条件。

如果他不执行任何操作，则不存在一条仅由白色格子组成的从起始格子到目标格子的路径。因此，输出 $1$。

该样例满足子任务 $2, 3, 4, 5, 6, 7, 8$ 的限制。

#### 【样例解释 #2】

该样例满足所有子任务的限制。

#### 【样例解释 #3】

该样例满足子任务 $2, 3, 4, 5, 6, 7, 8$ 的限制。

#### 【样例解释 #4】

即使他不执行任何操作，也可能存在一条仅由白色格子组成的从起始格子到目标格子的路径。

该样例满足所有子任务的限制。

#### 【数据范围】

对于所有测试数据，满足 $1 \leqslant N \leqslant R \leqslant C$，$R \times C \leqslant 6 \times 10^6$，$1 \leqslant S_r \leqslant R$，$1 \leqslant S_c \leqslant C$，$1 \leqslant G_r \leqslant R$，$1 \leqslant G_c \leqslant C$，$(S_r, S_c) 
eq (G_r, G_c)$。

保证 $A_i (1 \leqslant i \leqslant R)$ 是一个长度为 $C$ 且只由 `.` 或 `#` 构成的字符串。保证格子 $(S_r, S_c)$ 和格子 $(G_r, G_c)$ 均为白色。

保证 $R, C, N, S_r, S_c, G_r, G_c$ 均为整数。

| 子任务编号 | 分值 | 限制 |
| :-: | :-: | :-: |
| $1$ | $8$ | $N = 1, R \times C \leqslant 1.5 \times 10^6$ |
| $2$ | $19$ | $R \times C \leqslant 10^3$ |
| $3$ | $16$ | 答案不超过 $10$，$R \times C \leqslant 1.5 \times 10^6$ |
| $4$ | $19$ | $R \times C \leqslant 6 \times 10^4$ |
| $5$ | $5$ | $R \times C \leqslant 1.5 \times 10^5$ |
| $6$ | $19$ | $R \times C \leqslant 1.5 \times 10^6$ |
| $7$ | $8$ | $R \times C \leqslant 3 \times 10^6$ |
| $8$ | $6$ | 无 |

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2 4 2
1 1
2 4
.###
###.
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 6 1
1 6
6 1
..#.#.
##.###
####.#
...###
##.##.
.#.###
```

### 输出

```
4
```

## 样例 #3

### 输入

```
6 7 6
6 4
3 1
..#.#.#
##.##..
.######
#..#.#.
.######
..#.##.
```

### 输出

```
1
```

## 样例 #4

### 输入

```
1 15 1
1 15
1 1
...............
```

### 输出

```
0
```

# 题解

## 作者：0x3F (赞：20)

注意到，如果我们现在处于 $(x,y)$，则我们可以花费 $1$ 单位的代价，到达以 $(x,y)$ 为中心的，边长为 $2N+1$ 的正方形区域内的任意一个格子（四个角除外）。若 $(x,y)$ 为白格，则还可以不花费任何代价，到达与 $(x,y)$ 四连通的格子。

其中第一种移动方式还可以拆分成一次向四连通格子移动和 $N-1$ 次向八连通格子移动。我们可以添加高度维，等价转化为以下模型：

初始时位于起点，高度为 $0$。

若当前高度为 $0$ 且位于白格，则可以不花费任何代价，向四连通格移动，高度仍为 $0$。

若当前高度为 $0$ 且位于黑格，则可以花费 $1$ 单位的代价，向四连通格移动，并且高度变为 $N-1$。

若当前高度不为 $0$，则可以不花费任何代价，向八连通格移动，高度减少 $1$。

问需要多少代价到达终点，高度不限。

我们以代价（从小到大）为第一关键字，高度（从高到低）为第二关键字，跑 01 BFS 即可。

时间复杂度为 $\mathcal{O}(rc)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int dx4[4] = {-1, 0, 0, 1};
const int dy4[4] = {0, -1, 1, 0};
const int dx8[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
const int _ = 6e6 + 10;
int n, m, k, sx, sy, tx, ty;
bool arr[_], vis[_];
inline bool check(int x, int y) {
    return (x >= 1 && x <= n && y >= 1 && y <= m);
}
inline int id(int x, int y) {
    return (x - 1) * m + y;
}
struct node {
    int x, y, t, h;
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    cin >> sx >> sy;
    cin >> tx >> ty;
    for (int i = 1; i <= n; i++) {
        string str;
        cin >> str;
        for (int j = 1; j <= m; j++) {
            arr[id(i, j)] = (str[j-1] == '#');
        }
    }
    deque<node> Q(1, (node){sx, sy, 0, 0});
    while (true) {
        node N = Q.front();
        Q.pop_front();
        int x = N.x;
        int y = N.y;
        int t = N.t;
        int h = N.h;
        if (vis[id(x, y)]) continue;
        vis[id(x, y)] = true;
        if (x == tx && y == ty) {
            cout << t << endl;
            return 0;
        }
        if (h) {
            for (int d = 0; d <= 7; d++) {
                int xx = x + dx8[d];
                int yy = y + dy8[d];
                if (check(xx, yy) && !vis[id(xx, yy)]) {
                    Q.push_back((node){xx, yy, t, h-1});
                }
            }
        } else {
            for (int d = 0; d <= 3; d++) {
                int xx = x + dx4[d];
                int yy = y + dy4[d];
                if (check(xx, yy) && !vis[id(xx, yy)]) {
                    if (arr[id(xx, yy)]) {
                        Q.push_back((node){xx, yy, t+1, k-1});
                    } else {
                        Q.push_front((node){xx, yy, t, 0});
                    }
                }
            }
        }
    }
}
```

---

## 作者：HHH6666666666 (赞：12)

结论 $1$：若已到达一个点 $(x,y)$，那么对于任意满足 $\min(|x' - x|, |y' - y|) \leq k-1$ 且 $\max(|x' - x|, |y' - y|) \leq k$ 的点均能通过一次额外操作到达。

说人话就是：

![](https://cdn.luogu.com.cn/upload/image_hosting/2b5ws08s.png)

以图中 $k=3$ 为例，红色框起来的部分都可以如蓝色正方形内部的格子一样通过一次操作到达。

根据这个结论可以进行 $O(rcn^2)$ 的 `0-1bfs`。然而 $n$ 的范围太大，仍然不可过。继续观察。

结论 $2$：若到达当前节点后终点不在结论 $1$ 的范围内，则这个点到终点的任意一条路径必然至少经过一个结论 $1$ 图中边界上的 $4 \times (2n-1)$ 个点。

![](https://cdn.luogu.com.cn/upload/image_hosting/rgiuh59b.png)

如图， $T$ 为终点，涂色部分为必经点。

这条结论确实是废话，但由它可以得知我们在转移时只需要关注这些边界点，因为经过内部点的路径都一定会经过它们。除非当前节点与边界无障碍连通，否则由当前节点更新边界点的距离时至少要经过一次操作。因此在进行边权为 $1$ 即进行了一次操作的转移时并不需要更新除它们以外的节点的状态，因为不会更优。

于是可以做到 $O(rcn)$。

如果每行与每列用并查集来快速查询当前节点后第一个没被删除的节点，复杂度即可降为 $O(rc\alpha(r))$，可以通过。

代码中 $n,m,k$ 分别代表题目中的 $r,c,n$。

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
#define ef emplace_front
#define eb emplace_back

using namespace std;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int n, m, k;
int sx, sy, tx, ty;

#define ingrid(x, y) ((x) >= 0 && (x) < n && (y) >= 0 && (y) < m)
#define enc(x, y) ((x) * m + (y))
#define dec(x) mp((x) / m, (x) % m)

// ingrid(x, y): 查询 (x, y) 是否超出网格边界.
// enc(x, y): 将二维坐标转化为一维标号,方便使用并查集.
// dec(x, y): enc 的逆操作.

int find(int x, int *pa) {
    while (x != pa[x]) x = pa[x] = pa[pa[x]];
    return x;
}
void merge(int x, int y, int *parow, int *pacol) {
    // 在并查集中删除节点
    int id = enc(x, y);
    if (x + 1 < n && find(id, parow) == id) parow[id] = find(enc(x + 1, y), parow);
    if (y + 1 < m && find(id, pacol) == id) pacol[id] = find(enc(x, y + 1), pacol);
    return;
}
void solve() {
    cin >> n >> m >> k;
    cin >> sx >> sy >> tx >> ty;
    --sx, --sy, --tx, --ty;
    char c[n * m + 10];
    int dis[n * m + 10]; memset(dis, 0x3f, sizeof dis);
    int parow[n * m + 10], pacol[n * m + 10];
    iota(parow, parow + n * m, 0), iota(pacol, pacol + n * m, 0);
    bool upd[n * m + 10] = {};
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) cin >> c[enc(i, j)];
    // 0-1 bfs
    deque<int> q; q.eb(enc(sx, sy)), dis[enc(sx, sy)] = 0;
    merge(sx, sy, parow, pacol);
    int ans = INT_MAX;
    while (!q.empty()) {
        int x, y; tie(x, y) = dec(q.front()), q.pop_front();
        int p = enc(x, y), d = dis[p];
        if (upd[p]) continue;
        upd[p] = true;
        // 更新答案 (注意第二种情况不能 continue, 因为当前点可能与终点连通)
        if (x == tx && y == ty) {
            ans = min(ans, d);
            continue;
        }
        else if (min(abs(x - tx), abs(y - ty)) <= k - 1 && max(abs(x - tx), abs(y - ty)) <= k) ans = min(ans, d + 1);
        // 不操作
        for (int i = 0; i < 4; ++i) {
            int xx = x + dx[i], yy = y + dy[i];
            int id = enc(xx, yy);
            if (!ingrid(xx, yy) || dis[id] <= d || c[id] == '#') continue;
            dis[id] = d, q.ef(id), merge(xx, yy, parow, pacol);
        }
        // 上边界
        int xx, yy; xx = max(0, x - k);
        for (yy = max(0, y - k + 1); yy < y + k && yy < m; ++yy) {
            yy = dec(find(enc(xx, yy), pacol)).se;
            int id = enc(xx, yy);
            if (dis[id] <= d + 1 || yy >= y + k) continue;
            dis[id] = d + 1, q.eb(id), merge(xx, yy, parow, pacol);
        }
        // 下边界
        xx = min(n - 1, x + k);
        for (yy = max(0, y - k + 1); yy < y + k && yy < m; ++yy) {
            yy = dec(find(enc(xx, yy), pacol)).se;
            int id = enc(xx, yy);
            if (dis[id] <= d + 1 || yy >= y + k) continue;
            dis[id] = d + 1, q.eb(id), merge(xx, yy, parow, pacol);
        }
        // 左边界
        yy = max(0, y - k);
        for (xx = max(0, x - k + 1); xx < x + k && xx < n; ++xx) {
            xx = dec(find(enc(xx, yy), parow)).fi;
            int id = enc(xx, yy);
            if (dis[id] <= d + 1 || xx >= x + k) continue;
            dis[id] = d + 1, q.eb(id), merge(xx, yy, parow, pacol);
        }
        // 右边界
        yy = min(m - 1, y + k);
        for (xx = max(0, x - k + 1); xx < x + k && xx < n; ++xx) {
            xx = dec(find(enc(xx, yy), parow)).fi;
            int id = enc(xx, yy);
            if (dis[id] <= d + 1 || xx >= x + k) continue;
            dis[id] = d + 1, q.eb(id), merge(xx, yy, parow, pacol);
        }
    }
    cout << ans << endl;
    return;
}

int main() {
    ios:: sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}

```

---

## 作者：dyc2022 (赞：9)

绝世好题！
***
题意：给一个 $r \times c$ 的网格图，有一些障碍物。每次操作可以打通一个 $n \times n$ 的正方形，求将输入的起点和终点四联通的最小操作步数。
***
我们可以先思考一个 $O(rcn^2)$ 的简单做法。

我们可以从起点开始 BFS，走到一个点可以：

- 走到与该格子四联通的一个非障碍物位置，花费 $0$ 代价。
- 走到与该格子四联通的一个障碍物位置，花费 $1$ 代价并直接传送到该格子所在的 $n \times n$ 正方形中的任意一格。

我们发现瓶颈在于传送到 $n \times n$ 正方形的任一格子这一步。

我们可以画一个图，看一下从一个格子传送一次最远能够走到哪里。最极端的情况就是我当前所在的格子和我要传送到的格子正好在这个正方形对角线的两端。因此，我们容易发现：我们能够传送到的点，恰好就是从当前格子走 $n-1$ 步八联通的点。

想到这里，正解也就呼之欲出了。我们依然可以 01BFS，在每个节点存当前坐标，当前代价和还能走多少步八联通。复杂度为 $O(rc)$，代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define N 6000006
using namespace std;
int n,m,k,sx,sy,ex,ey;
vector<int> mp[N],vis[N];
struct Node{int x,y,dis,lef;};
deque<Node> dq;
char ch[N];
int dx[]={0,0,1,-1,1,1,-1,-1};
int dy[]={-1,1,0,0,1,-1,1,-1};
main()
{
	scanf("%lld%lld%lld%lld%lld%lld%lld",&n,&m,&k,&sx,&sy,&ex,&ey);
	for(int i=1;i<=n;i++)
	{
		mp[i].push_back(0),vis[i].push_back(0);
		scanf("%s",ch+1);
		for(int j=1;j<=m;j++)mp[i].push_back(ch[j]=='#'),vis[i].push_back(0);
	}
	dq.push_back({sx,sy,0,0});
	while(dq.size())
	{
		Node now=dq.front();dq.pop_front();
		if(vis[now.x][now.y])continue;
		if(now.x==ex&&now.y==ey)return printf("%lld\n",now.dis),0;
		vis[now.x][now.y]=1;
		if(now.lef)
		{
			for(int i=0;i<8;i++)
			{
				int tx=now.x+dx[i],ty=now.y+dy[i];
				if(tx>0&&ty>0&&tx<=n&&ty<=m&&!vis[tx][ty])
					dq.push_back({tx,ty,now.dis,now.lef-1});
			}
		}
		else
		{
			for(int i=0;i<4;i++)
			{
				int tx=now.x+dx[i],ty=now.y+dy[i];
				if(tx>0&&ty>0&&tx<=n&&ty<=m&&!vis[tx][ty])
				{
					if(mp[tx][ty])dq.push_back({tx,ty,now.dis+1,k-1});
					else dq.push_front({tx,ty,now.dis,0});
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：ECEG (赞：5)

### [JOI 2023 Final] Maze题解

[第一篇题解](https://www.luogu.com.cn/article/2ebq7vol)的高度真的太妙了，也讲得很好，这里来讲一下 01bfs 的正确性。

定义操作一为：若当前高度为 $0$ 且位于白格，则可以不花费任何代价，向四连通格移动，高度仍为 $0$。

定义操作二为：若当前高度为 $0$ 且位于黑格，则可以花费 $1$ 单位的代价，向四连通格移动，并且高度变为 $N-1$。

定义操作三为：若当前高度不为 $0$，则可以不花费任何代价，向八连通格移动，高度减少 $1$。

如何满足代价（从小到大）为第一关键字，高度（从高到低）为第二关键字？

先想一想正常 01bfs 的正确性。

其实就是把 dijkstra 换了。对于最短路最小的点的出边松弛时，若边权为0，那肯定也是最短路最小的点，若为1，那其实可以想，因为上面那种操作，他会把最小的最短路长度全部便利完（后面也不会出现），然后再去弄次小的最短路长度，那说明什么？队列里顶多就两种最短路权值。

回到原问题，如何满足代价（从小到大）为第一关键字，高度（从高到低）为第二关键字？

因为当要增加代价的时候是高度为 $0$（操作二），那说明高度更大的已经没有了。推出当队列有高度大于 $0$ 的点时，那肯定当前队列全是代价一样的点，且高度只能两种（和 01bfs 差不多）。

那说明调用操作一时，只有当前代价且高度为 $0$ 和代价加一且高度最大，那放前面是绝对没有问题的。操作二同理。操作三就和正常 01bfs 一样了。

评价：妙+妙！

```cpp
signed main(){
	read(r,c,n,x1,y1,x2,y2);x1--;y1--;x2--;y2--;
	for(int i=0;i<r*c;++i)dis[i]=r*c;
	for(int i=0;i<r;++i){
		scanf("%s",jk);
		for(int j=0;j<c;++j)a[i*c+j]=(jk[j]=='.');
	}
	que.emplace_back(x1*c+y1,0);dis[x1*c+y1]=0;
	for(;que.size();){
		auto[x,high]=que.front();que.pop_front();int fi=x/c,se=x%c;
		if(vis[x])continue;
		vis[x]=1;
		if(high){
			for(int k=0;k<8;++k)if(check(fi+dx[k],se+dy[k])&&dis[x+dx[k]*c+dy[k]]>dis[x])
				dis[x+dx[k]*c+dy[k]]=dis[x],que.emplace_back(x+dx[k]*c+dy[k],high-1);
		}
		else{
			if(a[x]){
				for(int k=0;k<4;++k)if(check(fi+dx[k],se+dy[k])&&dis[x+dx[k]*c+dy[k]]>dis[x])
					dis[x+dx[k]*c+dy[k]]=dis[x],que.emplace_front(x+dx[k]*c+dy[k],0);
			}
			else{
				for(int k=0;k<4;++k)if(check(fi+dx[k],se+dy[k])&&dis[x+dx[k]*c+dy[k]]>dis[x])
					dis[x+dx[k]*c+dy[k]]=dis[x]+1,que.emplace_back(x+dx[k]*c+dy[k],n-1);
			}
		}
	}
	write(dis[x2*c+y2]);
	return 0;
}
```

---

## 作者：yuanruiqi (赞：2)

对于部分分 $N=1$，则等价于朴素 01BFS。对于一般情况，一种考虑是优化建图，但是处理较为繁琐。考虑将框选矩形的操作下放到过程中，考虑从一个点出发，在四周框选的一个矩形的覆盖范围，相当于先向四周走一步，再向八连通方向走至多 $N-1$ 步。所以可以重新定义到一个点的距离为 $(x,y)$ 表示进行 $x$ 次操作，还剩下 $y$ 次免费的八联通移动。

---

## 作者：comcopy (赞：2)

题意略。

发现对于一次的正方形覆盖来说，必然是挨着上一次覆盖以后能经过的点的。

所以我们通过上一次覆盖的点先列后行地拓展矩形，枚举矩形覆盖次数，对每次矩形覆盖打上时间戳。

很显然按这样子拓展，每次覆盖完的正方形必然是与起点联通的，故最终答案就是结束位置的时间戳。

由于每个点只会被覆盖一次，均摊下来 $O(rc)$ 的。

```cpp
#include<bits/stdc++.h>
#define mi make_pair
#define pii pair<int,int>
//#define debug
using namespace std;

const int N=6e6+10,inf=0x3f3f3f3f;
int ffy[N],fyf[N];
pii fyy[N];
int d[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
int *a[N];
char op[N];
int r,c,n;
int *id[N];
pii *dp[N];
struct node{
	int x,y,v;
	int id;
	inline friend bool operator<(node a,node b){
		return a.v<b.v;
	}
	inline friend bool operator>(node a,node b){
		return a.v>b.v;
	}
};

inline bool check(int x,int y){
	return x>0&&x<=r&&y>0&&y<=c;
}

int ans;
inline void bfs(pair<int,int>be,pair<int,int>ed){
	vector<pair<int,int> > q[3];
	for(int i=1;i<=r;++i)	
		for(int j=1;j<=c;++j) dp[i][j]=mi(inf,inf);//第一维存的是时间戳，第几次覆盖 第二维存的是拓展了几行、几列 
	dp[be.first][be.second]=mi(0,n);//表示第 0 个矩形，已经拓展了 n 行 
	q[0].emplace_back(be.first,be.second);
	int nowdis=0;
	while(!q[0].empty()){//最外面套的枚举正方形覆盖次数 
		int nxtdis=nowdis+1;
		#ifdef debug
			cout<<nxtdis<<":::"<<endl;
		#endif
		for(int i=0,x,y;i<(int)q[0].size();++i){//拓展出当前能走的所有点 
			x=q[0][i].first,y=q[0][i].second;
			pii ndis=dp[x][y];
			for(int j=0,tx,ty;j<4;++j)
				if(check(tx=x+d[j][0],ty=y+d[j][1])&&dp[tx][ty]==mi(inf,inf)&&!a[tx][ty])
					q[0].emplace_back(tx,ty),dp[tx][ty]=ndis;
			#ifdef debug
				cout<<"1       "<<x<<' '<<y<<' '<<ndis.first<<' '<<ndis.second<<endl;
			#endif
		}
		for(pii i:q[0]) q[1].push_back(i);
		for(int i=0,x,y;i<(int)q[1].size();++i){ //优先拓展列，宽度 
			x=q[1][i].first,y=q[1][i].second;
			pii ndis=dp[x][y];
			for(int j=0,tx,ty;j<2;++j)
				if(check(tx=x+d[j][0],ty=y+d[j][1])&&dp[tx][ty]==mi(inf,inf)){
					if(ndis.first==nowdis)	dp[tx][ty]=mi(nxtdis,1); //新开的矩形，当前宽度为 1
					else if(ndis.second+1<=n) dp[tx][ty]=mi(nxtdis,ndis.second+1); //已有矩形拓展宽度
					else continue;
					q[1].emplace_back(tx,ty);
				}
			#ifdef debug
				cout<<"2       "<<x<<' '<<y<<' '<<ndis.first<<' '<<ndis.second<<endl;
			#endif
		}
		for(pii i:q[1]) q[2].push_back(i);
		for(int i=0,x,y;i<(int)q[2].size();++i){//接着拓展行，长度 
			x=q[2][i].first,y=q[2][i].second;
			pii ndis=dp[x][y];
			for(int j=2,tx,ty;j<4;++j)
				if(check(tx=x+d[j][0],ty=y+d[j][1])&&dp[tx][ty]==mi(inf,inf)){
					if(ndis.first==nowdis) dp[tx][ty]=mi(nxtdis,n+1); //新开矩形，长度为 1
					else if(ndis.first==nxtdis && ndis.second<n && n+1<=(n<<1)) dp[tx][ty]=mi(nxtdis,n+1); //如果宽度没有跑满 n，与新开没什么区别
					else if(ndis.first==nxtdis && ndis.second==n && n+2<=(n<<1)) dp[tx][ty]=mi(nxtdis,n+2);//跑满 n，说明原来的算在新矩形内，也要算上一行
					else if(ndis.first==nxtdis && ndis.second>n && ndis.second+1<=(n<<1)) dp[tx][ty]=mi(nxtdis,ndis.second+1); //拓展新行  
					else continue;
					q[2].emplace_back(tx,ty);
				}
			#ifdef debug
				cout<<"3       "<<x<<' '<<y<<' '<<ndis.first<<' '<<ndis.second<<endl;
			#endif	
		}
		q[0].clear();
		for(pii i:q[2]) (dp[i.first][i.second].first==nxtdis)&&(q[0].push_back(i),1);
		q[1].clear();q[2].clear();
		nowdis=nxtdis;
	}
	printf("%d\n",dp[ed.first][ed.second].first); 
}

signed main(){
	scanf("%d%d%d",&r,&c,&n);
	pair<int,int>be,ed;
	scanf("%d%d",&be.first,&be.second);
	scanf("%d%d",&ed.first,&ed.second);
	for(int i=1;i<=r;++i){
		a[i]=ffy+(i-1)*c+1;
		dp[i]=fyy+(i-1)*c+1;
		id[i]=fyf+(i-1)*c+1;
		scanf("%s",op+1);
		for(int j=1;j<=c;++j) a[i][j]=(op[j]=='#');
	}
	bfs(be,ed);
	return(0-0);
}
```

---

## 作者：kevinZ99 (赞：1)

考虑使用 01bfs 即可。但其实我更喜欢称它为大步小步 bfs 即将一个大步骤拆成若干小步骤进行 bfs 可以达到减少“边”的数量的作用。

简单的首先我们考虑若涂改了一次正方形会有什么影响，首先我们在这个 $ n \times n $ 的正方形中可以随便走动，且只可以上下左右走动 $ 2 \times ( n - 1 ) $ 次，为什么呢？

因为在正方形内可以随意地走动，且“回头”没有意义，因为反复走过相同地位置是属于刷微信步数行为，对走到终点没有帮助，除非终点在正方形内。

因此我们考虑将一次涂改，转化为 $ n - 1 $ 次随意地走动，注意这里地随意走动是可以斜着走的，也就是说在 $ n - 1 $ 次内必然走出正方形。

所以这里的一大步就是涂改正方形，一小步就是在正方形内的走动。

在考虑如何将涂改的次数减少到最小，相信对于聪明的你们应该都会了吧！

我们考虑使用一个双端队列，若需要新涂改一个正方形那么就放到队尾，若不涂改就放到对头，每一次 bfs 中的扩展取出对头进行扩展，若位置达到终点就找到了答案！

# code

```cpp
//Author:Kevin Z K Y
#include <bits/stdc++.h>
#define up(a,b,c) for(int (a)=(b);(a)<=(c);(a)++)
#define dn(a,b,c) for(int (a)=(b);(a)>=(c);(a)--)
#define fst first
#define sed second
using namespace std;
using us = unsigned short ;using ldb = long double ;
using ull = unsigned long long ;using ui = unsigned int ;
using ll = long long ;using hint = __int128 ;
using pii = pair<int,int> ;using pll = pair<ll,ll> ;
using pil = pair<int,ll> ;using vpil = vector<pil> ;
using vi = vector<int> ;using vl = vector<ll> ;
using vpi = vector<pii> ;using vpl = vector<pll> ;
using db = double ;namespace mystl{
	#define gc() getchar()
	#define Max(x,y) (((x)>(y))?(x):(y))
	#define Min(x,y) (((x)<(y))?(x):(y))
	#define Abs(x) (((x)<0)?(-(x)):(x))
	#define putline() cout<<"------------------------------\n"
	ll qpow(ll a , ll b , ll p) { if (a==0ll) return 0ll; ll c=1ll;
		while(b) { if(b & 1) c=a*c%p; a=a*a%p; b>>=1; } return c; }
	void exgcd(ll a,ll b,ll &cx,ll &cy){if(a % b ==0)cx = 0,cy = 1;
		else { exgcd( b , a % b , cy , cx) ; cy -= a / b * cx ; } }
	ll lcm ( ll x , ll y ){return x / std :: __gcd( x , y ) * y ; }
	template<typename T>void read(T&x) {x=0; bool f=false; char ch;
		ch = gc(); while(ch<'0'||ch>'9') f |= ( ch=='-') , ch=gc();
		while(ch>='0'&&ch<='9') x=x*10+ch-'0' , ch=gc(); x=f?-x:x;}
	template<typename T>void write(T x){char s[40];short d=0;T y=x;
		if(x<0) putchar('-'),y=-y;if(x==0){ putchar('0'); return; }
		while(y){s[++d]=y%10+'0';y/=10;}while(d>0)putchar(s[d--]);}
	template<typename T>void wris(T x,char c){write(x);putchar(c);}
}using namespace mystl;
const db eps=1e-6,PI=acos(-1);
namespace my{
	const int N=(int)(6e6+5);
	const int inf=(int)(1e9);
	bool s[N],vis[N];
	#define get(x,y) (((x)-1)*m+y)
	int n,m,k,sx,sy,ex,ey;
	struct node{
		int x,y,s,f;
	};
	const int dx[]={0,0,1,-1,1,1,-1,-1};
	const int dy[]={1,-1,0,0,-1,1,-1,1};
	void solve(){
		cin>>n>>m>>k>>sx>>sy>>ex>>ey;
		up(i,1,n)up(j,1,m){
			char c;cin>>c;
			s[get(i,j)]=((c=='#')?(1):(0));
		}deque<node>q;
		q.push_back({sx,sy,0,0});
		while(!q.empty()){
			node p=q.front();q.pop_front();
			if(p.x==ex&&p.y==ey){
				cout<<p.s<<'\n';
				return ;
			}if(vis[get(p.x,p.y)])continue;
			vis[get(p.x,p.y)]=true;
			if(p.f){
				up(i,0,7){
					int x=p.x+dx[i];
					int y=p.y+dy[i];
					if(x<=0||y<=0||x>n||y>m||vis[get(x,y)])continue;
					q.push_back({x,y,p.s,p.f-1});
				}
			}else {
				up(i,0,3){
					int x=p.x+dx[i];
					int y=p.y+dy[i];
					if(x<=0||y<=0||x>n||y>m||vis[get(x,y)])continue;
					if(s[get(x,y)])q.push_back({x,y,p.s+1,k-1});
					else q.push_front({x,y,p.s,0});
				}
			}
		}
	}
}
int main(){
//  freopen("","r",stdin);
//  freopen("","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	int _=1;while(_--)my::solve();return 0;
}

```

---

## 作者：Jorisy (赞：1)

好题。

操作等价于在 $(x,y)$ 走向 $([x-n,x+n],[y-n,y+n])$ 时均花费 $1$ 的代价。

若当前点存在于某个受操作子正方形内，则让其先走出这个正方形，这里可以记 $h$ 表示当前位置与操作中心 $(x,y)$ 的 **切比雪夫距离**。若从 $(x,y)$ 往外每走一步就 $-1$，$h=0$ 就表示不被某个受操作的子正方形所包含。

那么就要考虑枚举上下左右，如何向前走。

若枚举到的坐标 $(x',y')$ 有 $a_{x',y'}=\tt .$，那么直接往下走；否则，若  $a_{x',y'}=\tt \#$，那么就对以 $(x',y')$ 为中心的这个子正方形操作，并往下走。

由于操作时恰好位置上是 $\tt\#$，并且太多操作对答案不优，故 01 bfs 即可。
```cpp
#include<bits/stdc++.h>
#define N 6000005
#define id(POSX,POSY) ((POSX-1)*m+POSY)
using namespace std;

const int X[]={1,0,-1,0,1,1,-1,-1};
const int Y[]={0,1,0,-1,-1,1,-1,1};
struct node{
    int x,y,s,h;
}q[N<<1];
int n,m,k,sx,sy,tx,ty,a[N],vis[N],hd,tl;

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin>>n>>m>>k>>sx>>sy>>tx>>ty;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            char c;
            cin>>c;
            a[id(i,j)]=c=='#';
        }
    }
    q[hd=tl=n*m]={sx,sy,0,0};
    vis[id(sx,sy)]=1;
    while(hd<=tl)
    {
        int x=q[hd].x,y=q[hd].y,s=q[hd].s,h=q[hd].h,pos=id(x,y);
        hd++;
        // cerr<<x<<" "<<y<<' '<<s<<' '<<h<<endl;
        if(x==tx&&y==ty)
        {
            cout<<s;
            return 0;
        }
        if(h)
        {
            for(int i=0;i<8;i++)
            {
                int x_=x+X[i],y_=y+Y[i];
                if(x_<1||y_<1||x_>n||y_>m) continue;
                int pos_=id(x_,y_);
                if(vis[pos_]) continue;
                q[++tl]={x_,y_,s,h-1};
                vis[pos_]=1;
            }
            continue;
        }
        for(int i=0;i<4;i++)
        {
            int x_=x+X[i],y_=y+Y[i];
            if(x_<1||y_<1||x_>n||y_>m) continue;
            int pos_=id(x_,y_);
            if(vis[pos_]) continue;
            if(a[pos_]) q[++tl]={x_,y_,s+1,k-1};
            else q[--hd]={x_,y_,s,0};
            vis[pos_]=1;
        }
    }
    return 0;
}
```

---

## 作者：DengDuck (赞：1)

史诗级好题，真的不知道这个 Trick 怎么想到。

最短路具有以下性质：不走回头路。所以我们只需要求出来起点到每个点的最短路就行了。

不难想到操作相当于可以把一个人空降到相邻的 $n\times n$ 的矩形中的某一位置，我们可以直接上 01 BFS。

吗？

不行，因为这样时间复杂度吃不消，我们需要找个转换来代替“空降到相邻的 $n\times n$ 的矩形中的某一位置”的操作。

这里很天才的想法是，在接下来的 $n$ 次操作中，我们的走法可以从四联通变成八联通。

原理是：

- 切比雪夫距离等价于可以八连通地走。
- 然后某个方向切比雪夫距离在 $n$ 之内的点相当于一个 $n\times n$ 的正方形的范围。
- 所以跳到一个 $n\times n$ 的正方形的范围中的某一点就相当于可以八连通走 $n$ 步啦！

捋清楚这件事之后我们考虑怎么维护，还是用 01 BFS，如果能直接走那必然是直接走的，否则我们考虑用一次操作。

这时我们的代价加一，同时记录一下“我接下来的 $n$ 步可以走八连通”。

如果对于当前点还存在可以走八连通的步数，咱们就走八连通就行了，同时步数减一。

注意到这样首先步数一定是单调的，而且在步数一样的时候“可以走八连通的步数”也是一样的，原因是走八连通不产生费用，所以当我们当前点是可以走八连通的点时所有点的步数肯定都是一样的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Dx[8]={0,0,1,-1,1,1,-1,-1};
const int Dy[8]={-1,1,0,0,1,-1,1,-1};
const int N=6e6+5;
vector<int>A[N],Vis[N];
int n,m,k,Sx,Sy,Ex,Ey;
inline bool In(int x,int y){return (1<=x&&x<=n&&1<=y&&y<=m);}
struct Node{int x,y,D,H;};
char C[N];
int main()
{
	scanf("%d%d%d%d%d%d%d",&n,&m,&k,&Sx,&Sy,&Ex,&Ey);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",C+1);
		A[i].resize(m+5),Vis[i].resize(m+5);
		for(int j=1;j<=m;j++)A[i][j]=C[j]=='#';
	}
	deque<Node>Q;Q.push_back({Sx,Sy,0,0});
	while(!Q.empty())
	{
		Node t=Q.front();Q.pop_front();
		int x=t.x,y=t.y,D=t.D,H=t.H;
		if(Vis[x][y])continue;
		Vis[x][y]=1;
		if(x==Ex&&y==Ey)return printf("%d",D),0;
		if(H)
		{
			for(int i=0;i<8;i++)
			{
				int X=x+Dx[i],Y=y+Dy[i];
				if(In(X,Y)&&!Vis[X][Y])Q.push_back({X,Y,D,H-1});
			}
		}
		else
		{
			for(int i=0;i<4;i++)
			{
				int X=x+Dx[i],Y=y+Dy[i];
				if(In(X,Y)&&!Vis[X][Y])
				{
					if(A[X][Y])Q.push_back({X,Y,D+1,k-1});
					else Q.push_front({X,Y,D,0});
				}
			}
		}
	}
}
```

---

## 作者：gdf_yhm (赞：1)

[P9351](https://www.luogu.com.cn/problem/P9351)

### 思路

观察到一次覆盖操作相当于 $(u,v)$ 向 $(u,v)$ 为中心的一个矩形挖去四个角中每个点连代价为 $1$ 的边。

因为 $r\le c$，$r\le \sqrt {rc}$。暴力是 01bfs，到每个点处理覆盖操作时枚举行一边，用 $n$ 个并查集维护每行没有被删去的后继。对于每个点需要枚举 $\min(2\times n,r)$ 行，每个点只被入队一次。复杂度 $O(rc\sqrt {rc})$。

瓶颈在于枚举一行时有可能整行都没有要入队的点。

观察发现，除了最后一次覆盖操作以外，每一次覆盖操作都只让矩形边界上的点入队一定不劣。如果通过覆盖操作到达矩形边界内一个点有意义，那一定有一个原来的白连通块从这个点跨到矩形外面去，那这样之前通过覆盖操作到达矩形和连通块相交的位置即可。

这样每次一个点向 $4$ 条边中的点连边，维护每行每列的未操作后缀的并查集。复杂度 $O(rc)$

### code

```cpp
int n,m,d;
int sx,sy,ex,ey;
char s[maxn];
vector<vector<int>> a,dis;
int fx[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
vector<vector<int>> f;
int fd(int id,int x){
	if(x==f[id][x])return x;
	return f[id][x]=fd(id,f[id][x]);
}
pii q[maxn];int h=1,t=0;
pii st[maxn];int tp;
int ans;
void work(){
	n=read(),m=read(),d=read();
	a.resize(n+1),dis.resize(n+1);
	for(int i=1;i<=n;i++){
		a[i].resize(m+1),dis[i].resize(m+1);
		for(int j=1;j<=m;j++)dis[i][j]=inf;
	}
	f.resize(n+m+1);
	for(int i=1;i<=n;i++){
		f[i].resize(m+2);f[i][m+1]=m+1;
		for(int j=1;j<=m;j++)f[i][j]=j;
	}
	for(int i=n+1;i<=n+m;i++){
		f[i].resize(n+2);f[i][n+1]=n+1;
		for(int j=1;j<=n;j++)f[i][j]=j;
	}
	sx=read(),sy=read(),ex=read(),ey=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)a[i][j]=(s[j]=='.');
	}
	dis[sx][sy]=0,q[++t]={sx,sy};
	int cnt=0;ans=inf;
	while(h<=t){
		tp=0;
		while(h<=t){
			int u=q[h].fi,v=q[h].se;h++;
			if(abs(u-ex)<=d+1&&abs(v-ey)<=d+1&&abs(u-ex)+abs(v-ey)<=2*d)ans=min(ans,dis[u][v]+1);
			f[u][v]=fd(u,v+1);f[v+n][u]=fd(v+n,u+1);
			if(1){	
				int i=max(1,u-d);
				int l=max(1,(i==u-d||i==u+d)?v-d+1:v-d);
				int r=min(m,(i==u-d||i==u+d)?v+d-1:v+d);
				for(int j=fd(i,l);j<=r;j=fd(i,j)){
					if(dis[i][j]>dis[u][v]+1){
						dis[i][j]=dis[u][v]+1;
						st[++tp]={i,j};
					}
					f[i][j]=fd(i,j+1);f[j+n][i]=fd(j+n,i+1);
				}
			}
			if(1){	
				int i=min(n,u+d);
				int l=max(1,(i==u-d||i==u+d)?v-d+1:v-d);
				int r=min(m,(i==u-d||i==u+d)?v+d-1:v+d);
				for(int j=fd(i,l);j<=r;j=fd(i,j)){
					if(dis[i][j]>dis[u][v]+1){
						dis[i][j]=dis[u][v]+1;
						st[++tp]={i,j};
					}
					f[i][j]=fd(i,j+1);f[j+n][i]=fd(j+n,i+1);
				}
			}
			if(1){	
				int i=max(1,v-d);
				int l=max(1,(i==v-d||i==v+d)?u-d+1:u-d);
				int r=min(n,(i==v-d||i==v+d)?u+d-1:u+d);
				for(int j=fd(i+n,l);j<=r;j=fd(i+n,j)){
					if(dis[j][i]>dis[u][v]+1){
						dis[j][i]=dis[u][v]+1;
						st[++tp]={j,i};
					}
					f[i+n][j]=fd(i+n,j+1);f[j][i]=fd(j,i+1);
				}
			}
			if(1){	
				int i=min(m,v+d);
				int l=max(1,(i==v-d||i==v+d)?u-d+1:u-d);
				int r=min(n,(i==v-d||i==v+d)?u+d-1:u+d);
				for(int j=fd(i+n,l);j<=r;j=fd(i+n,j)){
					if(dis[j][i]>dis[u][v]+1){
						dis[j][i]=dis[u][v]+1;
						st[++tp]={j,i};
					}
					f[i+n][j]=fd(i+n,j+1);f[j][i]=fd(j,i+1);
				}
			}
			for(int i=0;i<4;i++){
				int nx=u+fx[i][0],ny=v+fx[i][1];
				if(nx<=0||nx>n||ny<=0||ny>m)continue;
				if(!a[nx][ny])continue;
				if(dis[nx][ny]>dis[u][v]){
					dis[nx][ny]=dis[u][v],q[++t]={nx,ny};
				}
			}
		}
		h=1,t=0;
		cnt++;
		if(dis[ex][ey]!=inf||ans==cnt)break;
		for(int i=1;i<=tp;i++){
			pii p=st[i];
			if(dis[p.fi][p.se]!=cnt)continue;
			q[++t]=p;
		}
	}
	printf("%d\n",min(ans,dis[ex][ey]));
}
```

---

## 作者：xxxyz (赞：1)

[P9351](https://www.luogu.com.cn/problem/P9351)。

这题对于 $n=1$ 就是直接 0-1bfs 即可。

这题的暴力是 $O(rcn^2)$ 的 0-1bfs，直接建 $(x, y)$ 向可行范围里每一个点连价值为 $1$ 的边，其他就是价值为 $0$ 的四联通边。

然后发现其实只需要对可行范围最外面一圈的边连边就可以了，因为你往正方形内部连边本质上还是要走向可行范围的边界，不如直接连上去。这样就是 $O(rcn)$ 的了，由于 $n=\sqrt{rc}$，所以相当于 $rc\sqrt{rc}$。这样就大概能过前六个点了。

而正解呢非常的有教育意义！

当我们走到一个正方形时，剩下的 $n$ 步可以八联通的走。

原理是：
- 切比雪夫距离等价于可以八连通地走。
-  然后某个方向切比雪夫距离在 $n$ 之内的点相当于一个 $n×n$ 的正方形的范围。
- 所以跳到一个 $n×n$ 的正方形的范围中的某一点就相当于可以八连通走 $n$ 步。

发现这样走是可以覆盖可行范围内所有点的，所以在 0-1bfs 的时候多记一维四（八）联通即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
const int Dy[8] = {-1, 1, 0, 0, 1, -1, 1, -1};
const int N = 6e6 + 5;
vector<int> A[N], Vis[N];
int n, m, k, Sx, Sy, Ex, Ey;
inline bool In(int x, int y) { return (1 <= x && x <= n && 1 <= y && y <= m); }
struct Node {
  int x, y, D, H;
};
char C[N];
signed main() {
  //freopen("maze.in", "r", stdin);
  //freopen("maze.out", "w", stdout);
  ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
  cin >> n >> m >> k >> Sx >> Sy >> Ex >> Ey;
  for (int i = 1; i <= n; i++) {
    cin >> (C + 1);
    A[i].resize(m + 5), Vis[i].resize(m + 5);
    for (int j = 1; j <= m; j++)
      A[i][j] = C[j] == '#';
  }
  deque<Node> Q;
  Q.push_back({Sx, Sy, 0, 0});
  while (!Q.empty()) {
    Node t = Q.front();
    Q.pop_front();
    int x = t.x, y = t.y, D = t.D, H = t.H;
    if (Vis[x][y])
      continue;
    Vis[x][y] = 1;
    if (x == Ex && y == Ey)
      return cout << D << '\n', 0;
    if (H) {
      for (int i = 0; i < 8; i++) {
        int X = x + Dx[i], Y = y + Dy[i];
        if (In(X, Y) && !Vis[X][Y])
          Q.push_back({X, Y, D, H - 1});
      }
    } else {
      for (int i = 0; i < 4; i++) {
        int X = x + Dx[i], Y = y + Dy[i];
        if (In(X, Y) && !Vis[X][Y]) {
          if (A[X][Y])
            Q.push_back({X, Y, D + 1, k - 1});
          else
            Q.push_front({X, Y, D, 0});
        }
      }
    }
  }
}
```

---

