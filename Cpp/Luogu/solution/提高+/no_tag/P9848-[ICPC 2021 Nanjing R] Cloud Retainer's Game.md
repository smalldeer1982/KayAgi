# [ICPC 2021 Nanjing R] Cloud Retainer's Game

## 题目描述

云堇，青云峰上云中居的建造者，对机械非常感兴趣。虽然距离璃月的海灯节还有一个多月的时间，她已经开始为其设计一个游戏活动。

游戏主要是关于释放弹珠以获得尽可能高的分数。它在二维平面上进行，平面上有两条水平直线 $y = 0$ 和 $y = H$。在这两条直线之间，有 $n$ 块小木板和 $m$ 个硬币，两者都可以视为单个点。第 $i$ 块木板位于 $(x_i, y_i)$，而第 $i$ 个硬币位于 $(x'_i, y'_i)$。

玩家从 $(10^{-9}, 10^{-9})$ 处释放一个弹珠。设 $\overrightarrow{v} = (v_x, v_y)$ 为弹珠的速度（也就是说，如果弹珠当前位于 $(x, y)$，则在 $\epsilon$ 秒后它将移动到 $(x + v_x\epsilon, y + v_y\epsilon)$）。初始时 $\overrightarrow{v} = (1, 1)$。

当弹珠撞到木板或两条水平直线之一时，$v_y$ 将被取反（即 $v_y$ 变为 $-v_y$），而 $v_x$ 保持不变。如果弹珠撞到硬币，玩家的分数增加 $1$，弹珠的速度保持不变。

为了获得更高的分数，玩家可以选择在释放弹珠之前移除任意数量的木板。也可以不移除任何木板。云堇希望你帮助她通过计算在最佳策略下经过 $10^{10^{10^{10^{10}}}}$ 秒后玩家可以获得的最高分数来估计游戏的难度。

## 说明/提示

下面显示了两个示例测试用例。实心菱形表示剩余的木板，空心菱形表示被移除的木板，圆点表示硬币。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
4
3
1 1
2 2
6 2
4
3 1
3 3
5 1
7 3
3
1
4 2
3
1 1
6 2
9 1
```

### 输出

```
3
3
```

# 题解

## 作者：xiezheyuan (赞：2)

## 简要题意

平面直角坐标系上有两个无限长的直线镜子，一个是 $y=0$，一个是 $y=H$。

有 $m$ 个硬币，第 $i$ 个硬币位于 $(x_i^{'},y_i^{'})$。有 $n$ 个可调节盒子，第 $i$ 个盒子位于 $(x_i,y_i)$。你可以将一个可调节盒子调节为镜子模式或默认模式。

有一束光从 $(0,0)$ 处以 $\frac{1}{4}\pi$ 弧度射出，光会穿过硬币和默认模式的盒子，碰到镜子或镜子模式的盒子后，会发生反射（遵循反射定律）。

你需要最大化光线碰到的硬币数量。

$T$ 组数据。$1\leq n,m\leq 10^5,1\leq \sum n,\sum m \leq 5 \times 10^5,2\leq H\leq 10^9,1\leq x_i,x^{'}_i\leq 10^9,1\leq y_i,y^{'}_i\leq H$

## 代码

理清题意后其实是一个简单题。

首先有一个平凡的 dp，即 $f(i,j,k)$ 表示点 $(i,j)$ 开始（包含这个点），光线方向为 $k$（$\frac{1}{4}\pi$ 或 $\frac{7}{4}\pi$）。转移就是如果这个点是硬币，那么找到后继节点然后加上 $1$，如果这个点是盒子，枚举这个盒子是哪一种盒子分别找后继即可。

这个转移没有问题，关键在于如何找后继。

我们可以让 $y$ 轴上的某一个点 $(0,i)$ 以 $\frac{1}{4}\pi$ 或 $\frac{7}{4}\pi$ 弧度发射的光线，为标准光线（考虑镜子，不考虑镜子模式的盒子），则发现无论如何反射，得到的光线都是由若干段标准光线得到的。

同样我们可以求出经过一个点以一定弧度的光线的标准光线是什么。所以我们可以对标准光线开一个 `map`，里面存 `vector`，按照 $x$ 升序存储这条光线可以经过的点的坐标，找后继的时候在上面二分即可。

时间复杂度单次 $O(n\log n)$ 可以通过本题。

## 代码

由于一开始代码没有构思好，写得比较丑，而且常数不小，反正能过就行了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 5;
int H, n, m;

struct position {
    int x, y;
    bool operator<(const position& rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
} p[N][2];

struct line {
    int k, b;
    bool operator<(const line& rhs) const { return k == rhs.k ? b < rhs.b : k < rhs.k; }
    bool operator==(const line& rhs) const { return k == rhs.k && b == rhs.b; }
};

map<line,vector<pair<int,int> > > mp;
int f[N][2][2];

auto cmp = [](const pair<int,int>& lhs, const pair<int,int>& rhs){ return p[lhs.first][lhs.second] < p[rhs.first][rhs.second]; };

line line1(position pos){
    if(pos.x < pos.y) return line{1, pos.y - pos.x};
    int x = (pos.x - pos.y) % (H << 1);
    if(x == 0) return line{1, 0};
    if(x <= H) return line{0, x};
    else return line{1, ((H << 1) - x)};
}

line line2(position pos){
    int x = (pos.x + pos.y) % (H << 1);
    if(x == 0) return line{1, 0};
    if(x <= H) return line{0, x};
    else return line{1, ((H << 1) - x)};
}

int dp(int i, int j, int k){// p[i][j], direction: k: line1(1) / line2(0)
    if(f[i][j][k] != -1) return f[i][j][k];
    if(j){// coin
        line l;
        if(k) l = line1(p[i][j]);
        else l = line2(p[i][j]);
        auto ite = upper_bound(mp[l].begin(), mp[l].end(), make_pair(i, j), cmp);
        if(ite == mp[l].end()) return f[i][j][k] = 1;
        if(line1(p[ite->first][ite->second]) == l) return f[i][j][k] = dp(ite->first, ite->second, 1) + 1;
        else return f[i][j][k] = dp(ite->first, ite->second, 0) + 1;
    }
    else{// board
        line l1, l2;
        if(k) l1 = line1(p[i][j]), l2 = line2(p[i][j]);
        else l1 = line2(p[i][j]), l2 = line1(p[i][j]);
        auto ite1 = upper_bound(mp[l1].begin(), mp[l1].end(), make_pair(i, j), cmp);
        auto ite2 = upper_bound(mp[l2].begin(), mp[l2].end(), make_pair(i, j), cmp);
        f[i][j][k] = 0;
        if(ite1 != mp[l1].end()){
            if(line1(p[ite1->first][ite1->second]) == l1) f[i][j][k] = max(f[i][j][k], dp(ite1->first, ite1->second, 1));
            else f[i][j][k] = max(f[i][j][k], dp(ite1->first, ite1->second, 0));
        }
        if(ite2 != mp[l2].end()){
            if(line1(p[ite2->first][ite2->second]) == l2) f[i][j][k] = max(f[i][j][k], dp(ite2->first, ite2->second, 1));
            else f[i][j][k] = max(f[i][j][k], dp(ite2->first, ite2->second, 0));
        }
        return f[i][j][k];
    }
}

void solve(){
    cin >> H >> n;
    p[0][1] = {0, 0}; mp[{1, 0}].push_back(make_pair(0, 1));
    for(int i=1;i<=n;i++){
        cin >> p[i][0].x >> p[i][0].y;
        mp[line1(p[i][0])].emplace_back(make_pair(i, 0));
        mp[line2(p[i][0])].emplace_back(make_pair(i, 0));
    }
    cin >> m;
    for(int i=1;i<=m;i++){
        cin >> p[i][1].x >> p[i][1].y;
        mp[line1(p[i][1])].emplace_back(make_pair(i, 1));
        mp[line2(p[i][1])].emplace_back(make_pair(i, 1));
    }
    for(auto& i : mp) sort(i.second.begin(), i.second.end(), cmp);
    for(int i=0;i<=max(n, m);i++){
        for(int j=0;j<=1;j++) f[i][j][0] = f[i][j][1] = -1;
    }
    cout << (dp(0, 1, 1) - 1) << '\n';
    mp.clear();
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：WZwangchongming (赞：1)

云堇可爱捏！但是没有芙芙可爱！


---

Solution：

首先我们可以假设不存在挡板。

找规律可以发现，弹球往右下移动的轨迹中每个点都满足 $x+y \equiv k \pmod{2H}$，往右上移动的轨迹中每个点都满足 $x-y \equiv k \pmod{2H}$。其中 $k$ 是一个常数。

初始的时候就只有 $k=0$ 的情况，所以挡板的作用就是增加更多的 $k$。

设 $f_k$ 表示特征值为 $k$ 的轨迹的最大得分，那么我们只需要按 $x$ 坐标从小到大枚举关键点。令 $p=x+y \bmod 2H$，$q=x-y \bmod 2H$。

- 如果是硬币，$f_p$ 和 $f_q$ 均加一。
- 如果是挡板，$f_p$ 和 $f_q$ 均变为两者中较大值。

具体实现只需要开个 map 就可以。

时间复杂度是 $O(n \log n)$，可以通过本题。

---

Main code：

```cpp
void solve() {
	H = read(), n = read(), H <<= 1;
	for(int i = 1; i <= n; i++) 
		a[i].x = read(), a[i].y = read(), a[i].type = 0;
	m = read();
	for(int i = n + 1; i <= n + m; i++) 
		a[i].x = read(), a[i].y = read(), a[i].type = 1;
	sort(a + 1, a + 1 + n + m, [&](node p, node q) { return p.x < q.x; });
	mp.clear(), mp[0] = 0;
	for(int i = 1; i <= n + m; i++) {
		int p = (a[i].x + a[i].y) % H, q = ((long long)a[i].x % H - a[i].y + H) % H;
		if(a[i].type == 0) {
			int mx = -1;
			if(mp.count(p)) mx = mp[p];
			if(mp.count(q)) mx = max(mx, mp[q]);
			if(~mx) mp[p] = mp[q] = mx;
		} 
		else {
			if(mp.count(p)) mp[p]++;
			if(mp.count(q)) mp[q]++;
		}
	}
	int ans = 0;
	for(auto &[v, f] : mp) ans = max(ans, f);
	printf("%d\n", ans);
}
```

---

## 作者：happy_zero (赞：1)

首先肯定先将所有点按 $x$ 从小到大排个序。

比较容易想到一个 dp 定义：设 $f_i$ 表示到第 $i$ 块木板的最大分数。

到了当前木板，可以通过选/不选当前木板来改变/不改变方向，因此在任意木板都可以以 $\overrightarrow{v}=(1,1)$ 或 $\overrightarrow{v}=(1,-1)$ 出发。同时，在到达下一个木板之前，只会在 $y=0,y=H$ 的位置改变 $v_y$。

从 $(x,y)$ 出发有两种轨道：往上或往下。如何判断 $(x,y)$ 经过是否能到达 $(x',y')$？如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6pz91pos.png?x-oss-process=image/resize,m_lfit,h_510,w_675)

经过 $(x,y)$ 往上的直线与 $y=0$ 交于 $(x-y,0)$，往下的直线与 $y=0$ 交于 $(x+y,0)$。

不难发现，$(x,y)$ 能到达 $(x',y')$ 等价于 $x+y/x-y\equiv x'+y'/x'-y'\pmod {2H}$。图中的情况即 $x+y\equiv x'-y'\pmod{2H}$，$(x,y)$ 往下走，到达 $(x',y')$ 时是在往上走。

于是思路就比较明朗了：预处理出从每个点（包括木板和硬币，下同）往上/下出发到达的下一个点，转移时从 $i$ 出发一直跳知道跳到下一个木板 $j$（如果 $j$ 不存在就直接更新答案），记录一下中间经过了多少个硬币来更新 $f_j$。之后就可以直接退出循环了，因为之后的路径用 $f_j$ 来更新一定不劣。

dp 部分和预处理部分是线性的（预处理可以用 `unordered_map`），时间复杂度瓶颈在于排序。

```cpp
#include <bits/stdc++.h>
#define pii pair <int, int> 
#define fi first
#define se second
using namespace std;
const int N = 2e5 + 5;
struct node { int x, y, op; } a[N];
bool cmp(node x, node y) { return x.x < y.x; }
unordered_map <int, pii> mx;
int f[N];
pii nxt[N][2];
inline void chmax(int &x, int y) { if (x < y) x = y; }
void solve() {
	int H, n; cin >> H >> n; int P = H << 1, ts = 0; 
    a[++ts] = {0, 0, 0}; mx.clear();
	for (int i = 1; i <= n; i++)
		ts++, cin >> a[ts].x >> a[ts].y, a[ts].op = 0;
	int m; cin >> m;
	for (int i = 1; i <= m; i++)
		ts++, cin >> a[ts].x >> a[ts].y, a[ts].op = 1;
	sort(a + 1, a + 1 + ts, cmp);
    memset(f, -0x3f, sizeof(f)); f[1] = 0;
	for (int i = 1; i <= ts; i++) {
        pii &x = mx[(a[i].x + a[i].y) % P];
        nxt[x.fi][x.se] = {i, 0}, x = {i, 0};
		pii &y = mx[(a[i].x - a[i].y + P) % P];
		nxt[y.fi][y.se] = {i, 1}, y = {i, 1};
	}
	int ans = 0;
	for (int i = 1; i <= ts; i++) 
		if (!a[i].op) 
            for (int j = 0; j < 2; j++) {
                 int cnt = 0; pii now = nxt[i][j];
                while (now.fi && a[now.fi].op) 
                    cnt++, now = nxt[now.fi][now.se];
                chmax(now.fi ? f[now.fi] : ans, f[i] + cnt); 
            }
    cout << ans << '\n';
    for (int i = 1; i <= ts; i++)
        nxt[i][0] = nxt[i][1] = {0, 0};
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：紊莫 (赞：1)

题意简述：  

参考题中所给图片，有上下两根直线，之间的距离为 $H$，还有 $n$ 个镜子，可以反射光线，也可以让其穿过，有 $m$ 个物品，一开始有一束从原点出发四十五度向右上方射出的一条光线，请你控制每个镜子的开关，求这条光线最多能经过几个物品。  

我们考虑能经过一个点 $(a,b)$ 的光线只可能是 $y=x+k_1$ 或者 $y=-x+k_2$ 的形式，而光线反射后相对于原来的光线是向右平移了 $2H$ 的长度，如图所示。  

![](https://cdn.luogu.com.cn/upload/image_hosting/e9udhmny.png)  

也就是直线从 $y=x+k_1$ 变成了 $y=x+k_1-2H$，换言之，则有 $\Delta k\equiv k_1\pmod{2H}$，所以只要在模 $2H$ 意义下一样的数字，就可认为是同一条直线。

然后考虑两种点的本质，因为镜子可以改变或不改变方向，所以就是在两条直线中取最大值，而物品可以让两条直线对应的最大值加一，所以就有一点动归的样子了，考虑到 $H$ 较大，我们可以使用 ``unordered_map`` 作为动态规划数组。对于两种点排序后考虑即可。  

---

